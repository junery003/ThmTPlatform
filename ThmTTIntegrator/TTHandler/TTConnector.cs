//-----------------------------------------------------------------------------
// File Name   : TTConnector
// Author      : junlei
// Date        : 1/20/2020 3:50:10 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using ThmCommon.Config;
using ThmCommon.Handlers;
using ThmTTIntegrator.TTFunctions;
using tt_net_sdk;

namespace ThmTTIntegrator.TTHandler {
    /// <summary>
    /// Connect to TT 
    /// </summary>
    public class TTConnector : IConnector {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        public bool IsConnected { get; set; }

        private readonly TTConfigHelper _ttConfigHelper;

        private TTConfig _ttConfig;

        private IReadOnlyList<Account> _accounts;
        private string _initAccountName;

        private TTAPI _ttApi = null; // Declare the API objects

        // <instrumentID, productID>
        private readonly Dictionary<ulong, ProductKey> _instrumentProductDic = new();

        // <productID, instrumentCatalogHandler>
        private readonly Dictionary<ProductKey, TTInstrumentCatalogHandler> _instrumentCatalogHandlerDic = new();

        public TTConnector() {
            _ttConfigHelper = new TTConfigHelper();
        }

        public bool Connect(LoginCfgBase loginCfg = null) {
            if (!Init(loginCfg)) {
                return false;
            }
            InstrumentHandlerBase.EnableSaveData = _ttConfig.SaveData;

            var ttAccount = _ttConfig.Account;
            ServiceEnvironment environment; // UatCert;
            switch (ttAccount.Environment.ToUpper()) {
                case "PRODLIVE":
                    Logger.Info($"Environment: TT ProdLive-{ttAccount.Mode}");
                    environment = ServiceEnvironment.ProdLive;
                    break;
                case "UATCERT":
                    Logger.Info($"Environment: TT UatCert-{ttAccount.Mode}");
                    environment = ServiceEnvironment.UatCert;
                    break;
                case "PRODSIM":
                default:
                    Logger.Info($"Environment: TT ProdSim-{ttAccount.Mode}");
                    environment = ServiceEnvironment.ProdSim;
                    break;
            }

            TTAPIOptions apiConfig;
            if (ttAccount.Mode.ToUpper() == "SERVER") {
                apiConfig = new TTAPIOptions(TTAPIOptions.SDKMode.Server, environment, ttAccount.AppKey, 5000) {
                    EnablePriceLogging = false,
                };
            }
            else {
                apiConfig = new TTAPIOptions(environment, ttAccount.AppKey, 5000) {
                    EnablePriceLogging = false,
                };
            }

            Task.Run(() => {
                var disp = Dispatcher.AttachWorkerDispatcher();
                disp.DispatchAction(() => {
                    apiConfig.AlgoUserDisconnectAction = UserDisconnectAction.Cancel;
                    TTAPI.CreateTTAPI(Dispatcher.Current, apiConfig, new ApiInitializeHandler(TTNetApiInitHandler));
                });
                disp.Run();
            }).ConfigureAwait(false);

            return true;
        }

        private bool Init(LoginCfgBase loginCfg = null) {
            if (!_ttConfigHelper.LoadConfig()) {
                throw new Exception("TT failed to load config.");
            }

            _ttConfig = _ttConfigHelper.GetConfig() as TTConfig;
            if (_ttConfig == null || _ttConfig.Account == null) {
                throw new Exception("Loading TT config file failed.");
            }

            if (_ttConfig.Exchanges == null || !_ttConfig.Exchanges.Any()) {
                throw new Exception("No TT instance was defined.");
            }

            if (loginCfg != null) {
                _initAccountName = loginCfg.Account; // 
            }
            else {
                _initAccountName = _ttConfig.Account.Account; // default
            }

            _ttConfig.Exchanges?.ForEach(exch => {
                if (exch.Enabled) {
                    //AddInstrumentCatalog("CME", "Future", "OQB");
                    //AddInstrument("SGX", "Future", "FEF", "FEF Apr20");

                    exch.Products.ForEach(product => {
                        Logger.Info("Add product: " + product.Name);

                        MarketId marketKey = Market.GetMarketIdFromName(exch.Market);
                        ProductType productType = Product.GetProductTypeFromName(exch.Type);
                        var productKey = new ProductKey(marketKey, productType, product.Name);

                        _instrumentCatalogHandlerDic[productKey] = new TTInstrumentCatalogHandler(productKey, _instrumentProductDic);
                    });
                }
            });

            return true;
        }

        public bool StartContract(string instrumentID, string exchange = null) {
            if (!IsConnected) {
                Logger.Warn("Not connected to market yet.");
                return false;
            }

            var instID = ulong.Parse(instrumentID);
            if (!_instrumentProductDic.ContainsKey(instID)) {
                Logger.Error("{0} not in the product dic", instID);
                return false;
            }

            _instrumentCatalogHandlerDic[_instrumentProductDic[instID]].Start(instrumentID);

            return true;
        }

        public bool StopContract(string instrumentID) {
            ulong instID = ulong.Parse(instrumentID);
            if (!_instrumentProductDic.ContainsKey(instID)) {
                Logger.Warn("{0} not start, cannot stop", instID);
                return false;
            }

            Logger.Info("Stopping instrument {}", instrumentID);
            _instrumentCatalogHandlerDic[_instrumentProductDic[instID]].Stop(instrumentID);
            _instrumentCatalogHandlerDic.Remove(_instrumentProductDic[instID]);
            _instrumentProductDic.Remove(instID);

            return true;
        }

        public void StartContracts() {
            if (!IsConnected) {
                Logger.Warn("Not connected to market yet.");
                return;
            }

            foreach (var handler in _instrumentCatalogHandlerDic.Values) {
                handler.Start(_accounts, _initAccountName);
            }
        }

        public void TTNetApiInitHandler(TTAPI api, ApiCreationException ex) {
            if (ex == null) {
                Logger.Info("TT.NET SDK Initialization Complete");
                // Authenticate your credentials
                _ttApi = api;

                _ttApi.TradingEnabledChanged += TTApi_TradingEnabledChanged;
                if (_ttApi.MarketCatalog != null) {
                    _ttApi.MarketCatalog.TradingEnabledChanged += MarketCatalog_TradingEnabledChanged;
                }

                _ttApi.TTAPIStatusUpdate += TTApi_TTAPIStatusUpdate;
                _ttApi.Start();
            }
            else if (ex.IsRecoverable) {
                Logger.Warn("TT.NET SDK Initialization failed but retry is in progress: " + ex.Message);
            }
            else {
                Logger.Warn("TT.NET SDK Initialization Failed: " + ex.Message);
                Dispose();
            }
        }

        private void TTApi_TradingEnabledChanged(object sender, MarketStatusEventArgs e) {
            Logger.Info("Market: {0}, IsTradingEnabled: {1}", e.Market, e.IsTradingEnabled);
        }

        private void MarketCatalog_TradingEnabledChanged(object sender, MarketStatusEventArgs e) {
            Logger.Info("MarketCatalog Market: {0}, IsTradingEnabled: {1}", e.Market, e.IsTradingEnabled);
        }

        internal void TTApi_TTAPIStatusUpdate(object sender, TTAPIStatusUpdateEventArgs e) {
            Logger.Info("TT.NET SDK Status: " + e);
            if (!e.IsReady) {
                IsConnected = false;
                Logger.Warn("Cannot connect to TT.NET server.");
                return;
            }

            Logger.Info("TT.NET SDK Authenticated"); // connection to TT is established

            _accounts = _ttApi.Accounts?.ToList();
            if (!_accounts.Any(x => x.AccountName == _initAccountName)) {
                Logger.Warn("No account was specified. Will using the first default account.");

                _initAccountName = _accounts[0].AccountName;
            }

            Logger.Info("Current Account: " + _initAccountName);

            IsConnected = true;

            StartContracts();

            // TODO: Do any connection up processing here
            //       note: can happen multiple times with your application life cycle
            //AddInstrument(_market, _prodType, _product, _alias);
        }

        public IConfigHelper GetConfigHelper() {
            return _ttConfigHelper;
        }

        public bool DeleteInstrumentCatalog(string market, string prodType, string product) {
            MarketId marketKey = Market.GetMarketIdFromName(market);
            ProductType productType = Product.GetProductTypeFromName(prodType);
            ProductKey pk = new ProductKey(marketKey, productType, product);

            if (_instrumentCatalogHandlerDic.ContainsKey(pk)) {
                _instrumentCatalogHandlerDic[pk].Dispose();

                _instrumentCatalogHandlerDic.Remove(pk);

                return true;
            }

            return false;
        }

        /*
        public void AddInstrument(string market, string prodType, string product, string alias) {
            MarketId marketKey = Market.GetMarketIdFromName(market);
            ProductType productType = Product.GetProductTypeFromName(prodType);

            var ik = new InstrumentKey(marketKey, productType, product, alias);
            if (!_instrumentHandlerDic.ContainsKey(ik)) {
                if (IsConnected) {
                    var instrumentHandler = new InstrumentHandler(ik, _account);
                    instrumentHandler.Start();

                    _instrumentHandlerDic.Add(ik, instrumentHandler);
                }
                else {
                    _instrumentHandlerDic.Add(ik, null);
                }
            }
        }

        public bool DeleteInstrument(string market, string prodType, string product, string alias) {
            MarketId marketKey = Market.GetMarketIdFromName(market);
            ProductType productType = Product.GetProductTypeFromName(prodType);
            var ik = new InstrumentKey(marketKey, productType, product, alias);

            if (_instrumentHandlerDic.ContainsKey(ik)) {
                _instrumentHandlerDic[ik].Dispose();

                _instrumentHandlerDic.Remove(ik);

                return true; // delete successfully
            }

            return true; // no del
        } */

        public InstrumentHandlerBase GetInstrumentHandler(string instrumentID) {
            foreach (var catalogHandler in _instrumentCatalogHandlerDic.Values.ToList()) {
                foreach (var pair in catalogHandler.InstrumentHandlerDic) {
                    if (instrumentID == pair.Key.Key.Alias) {
                        return pair.Value;
                    }
                }
            }

            return null;
        }

        public InstrumentHandlerBase GetInstrumentHandler(string market, string prodType, string product, string contract) {
            MarketId marketKey = Market.GetMarketIdFromName(market);
            ProductType productType = Product.GetProductTypeFromName(prodType);
            var pk = new ProductKey(marketKey, productType, product);

            foreach (var pair in _instrumentCatalogHandlerDic[pk].InstrumentHandlerDic) {
                if (contract == pair.Key.Key.Alias) {
                    return pair.Value;
                }
            }

            return null;
        }

        public List<string> GetInstruments(string market, string prodType, string product) {
            MarketId marketKey = Market.GetMarketIdFromName(market);
            ProductType productType = Product.GetProductTypeFromName(prodType);
            var pk = new ProductKey(marketKey, productType, product);

            var instruments = new List<string>();
            foreach (var tmp in _instrumentCatalogHandlerDic[pk].InstrumentHandlerDic.Keys) {
                instruments.Add(tmp.Key.Alias);
            }

            return instruments;
        }

        public bool ChangePassword(string usrId, string curPwd, string newPwd) {
            return false;
        }

        public void Dispose() {
            foreach (var tmp in _instrumentCatalogHandlerDic.Values) {
                tmp?.Dispose();
            }
            _instrumentCatalogHandlerDic.Clear();

            /*
            foreach (var tmp in _instrumentHandlerDic.Values) {
                tmp?.Dispose();
            }
            _instrumentHandlerDic.Clear(); */

            TTAPI.ShutdownCompleted += TTAPI_ShutdownCompleted;
            TTAPI.Shutdown();
        }

        internal void TTAPI_ShutdownCompleted(object sender, EventArgs e) {
            Logger.Info("TTAPI Shutdown completed");
        }
    }
}
