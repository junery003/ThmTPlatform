//-----------------------------------------------------------------------------
// File Name   : CtpConnector
// Author      : junlei
// Date        : 8/20/2021 5:03:18 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Timers;
using ThmCommon.Config;
using ThmCommon.Handlers;
using ThmCtpIntegrator.CtpFunctions;

namespace ThmCtpIntegrator.CtpHandler {
    /// <summary>
    /// AtpConnector
    /// </summary>
    public class CtpConnector : IConnector {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        // instrumentID, handler
        internal Dictionary<string, CtpInstrumentHandler> InstrumentHandlerDic { get; } = new Dictionary<string, CtpInstrumentHandler>();

        private ZmqHelper _zmqHelper;
        private readonly CtpConfigHelper _cfgHelper;

        private readonly List<ExchangeCfg> _exchanges = new List<ExchangeCfg>();
        private readonly List<string> _allAccounts = new List<string>();

        public bool IsConnected { get; set; } = false;  // MarketDataConnected
        //private bool _tradeConnected;

        private Timer _mdReconnTimer = null;

        public CtpConnector() {
            _cfgHelper = new CtpConfigHelper();
        }

        public bool Connect(LoginCfgBase loginCfg = null) {
            if (!Init(loginCfg)) {
                return false;
            }
            InstrumentHandlerBase.EnableSaveData = _cfgHelper.GetConfig().SaveData;
            Task.Delay(200).Wait();

            _zmqHelper = new ZmqHelper(this,
                CtpConfigHelper.Config.StreamDataServer,
                CtpConfigHelper.Config.StreamTradeServer);

            Task.Delay(300).Wait();

            //var accounts = _atpConfig.AtpLogin.Where(x => x.Enabled).ToArray();
            //var account = CtpConfigHelper.Config.Account;
            if (!DllHelper.Init()) {
                Logger.Error("Failed to init CTP client.");
                return false;
            }

            Task.Delay(300).Wait();

            //DllHelper.UpdateTradeClient(account.UserId, account.Password);
            return true;
        }

        private bool Init(LoginCfgBase loginCfg = null) {
            if (!_cfgHelper.LoadConfig()) {
                Logger.Error("CTP failed to load config.");
                return false;
            }

            if (CtpConfigHelper.Config == null || CtpConfigHelper.Config.Account == null) {
                Logger.Error("Ctp Login information is not correct.");
                return false;
            }

            if (loginCfg == null) { // default
                //var accounts = _atpConfig.AtpLogin.Where(x => x.Enabled).ToArray();
                //foreach (var acc in accounts) {
                //    _allAccounts.Add(acc.UserId);
                //}
            }

            CtpConfigHelper.Config.Exchanges?.ForEach(x => {
                if (x.Enabled) {
                    _exchanges.Add(x);

                    //x.Contracts?.ToList().ForEach(c => { // instrumentID: ("CPF2006-APEX");
                    //    Logger.Info("Add contract: " + c);
                    //    InstrumentHandlerDic.Add(c, new CtpInstrumentHandler(c, x.Market));
                    //});
                }
            });
            return true;
        }

        public bool StartContract(string instrumentID, string exchange = null) {
            if (!InstrumentHandlerDic.ContainsKey(instrumentID)) {
                InstrumentHandlerDic[instrumentID] = new CtpInstrumentHandler(instrumentID, exchange);
            }

            return InstrumentHandlerDic[instrumentID].Start();
        }

        public bool StopContract(string instrumentID) {
            if (!InstrumentHandlerDic.ContainsKey(instrumentID)) {
                Logger.Warn("{} not started. Cannot stop it.", instrumentID);
                return false;
            }

            Logger.Info("Stop instrument {}", instrumentID);
            InstrumentHandlerDic[instrumentID].Stop();
            return InstrumentHandlerDic.Remove(instrumentID);
        }

        public InstrumentHandlerBase GetInstrumentHandler(string instrumentID) {
            if (!InstrumentHandlerDic.ContainsKey(instrumentID)) {
                Logger.Error("No instrument found {0}", instrumentID);
                return null;
            }

            return InstrumentHandlerDic[instrumentID];
        }

        public void StartContracts() {
            if (!IsConnected) {
                Logger.Warn("Not connected to market yet.");
                return;
            }

            foreach (var handler in InstrumentHandlerDic.Values) {
                handler.Start();
            }
        }

        public IConfigHelper GetConfigHelper() {
            return _cfgHelper;
        }

        public InstrumentHandlerBase GetInstrumentHandler(string market, string productType, string product, string instrument) {
            foreach (var pair in InstrumentHandlerDic) {
                var info = pair.Value.InstrumentInfo;
                var (prod, contract) = CtpUtil.ExtractContract(instrument);
                if (info.Exchange == market
                    && info.ProductType == productType
                    && info.Product == prod
                    && info.Contract == contract) {
                    return InstrumentHandlerDic[pair.Key];
                }
            }

            return null;
        }

        public List<string> GetInstruments(string market, string productType, string product) {
            foreach (var ex in _exchanges) {
                if (ex.Market == market && ex.Type == productType) {
                    //return ex.Contracts.ToList();
                }
            }

            return null;
        }

        internal void MarketDataConnected() {
            if (_mdReconnTimer != null) {
                _mdReconnTimer.Stop();
                _mdReconnTimer.Dispose();
                _mdReconnTimer = null;
            }

            IsConnected = true;

            StartContracts();
        }

        internal void MarketDataDisconnected() {
            IsConnected = false;

            if (_mdReconnTimer == null) {
                _mdReconnTimer = new Timer(3 * 60 * 1000) {
                    AutoReset = true,
                    Enabled = true
                };
                _mdReconnTimer.Elapsed += ReconnectTimer_Elapsed;
            }
        }

        internal void TradeConnected() {
            //_tradeConnected = true;
        }

        internal void TradeDisconnected() {
            //_tradeConnected = false;
        }

        private void ReconnectTimer_Elapsed(object sender, ElapsedEventArgs e) {
            Logger.Info("Reconnecting CTP...");

            StartContracts();
        }

        //private void ReqQueryOrder(string contract) {
        //    DllHelper.ReqQueryOrder(contract); // all order under this contract/instrumentID             
        //}

        //private void ReqQueryTrade(string contract) {
        //    DllHelper.ReqQueryTrade(contract);
        //}

        //private void ReqPosUpdate(string contract) {
        //    DllHelper.ReqPositionUpdate(contract);
        //}

        public bool ChangePassword(string usrId, string curPwd, string newPwd) {
            return false;
        }

        public void Dispose() {
            Logger.Info("CTP connection closed");

            foreach (var hanlder in InstrumentHandlerDic.Values) {
                hanlder.Dispose();
            }

            _zmqHelper?.Dispose();

            if (_mdReconnTimer != null) {
                _mdReconnTimer.Stop();
                _mdReconnTimer.Dispose();
                _mdReconnTimer = null;
            }
        }
    }
}
