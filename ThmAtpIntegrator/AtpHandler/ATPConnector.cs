//-----------------------------------------------------------------------------
// File Name   : AtpConnector
// Author      : junlei
// Date        : 1/20/2020 5:03:18 PM
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
using ThmAtpIntegrator.AtpFunctions;
using ThmCommon.Config;
using ThmCommon.Handlers;

namespace ThmAtpIntegrator.AtpHandler {
    /// <summary>
    /// AtpConnector
    /// </summary>
    public class AtpConnector : IConnector {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        // instrumentID, handler
        internal Dictionary<string, AtpInstrumentHandler> InstrumentHandlerDic { get; } = new();

        private ZmqHelper _zmqHelper;
        private readonly AtpConfigHelper _atpConfigHelper;

        private readonly List<ExchangeCfg> _exchanges = new();
        private readonly List<string> _allAccounts = new();

        public bool IsConnected { get; set; } = false;  // MarketDataConnected
        //private bool _tradeConnected;

        private Timer _mdReconnTimer = null;

        public AtpConnector() {
            _atpConfigHelper = new AtpConfigHelper();
        }

        public bool Connect(LoginCfgBase loginCfg = null) {
            if (!Init(loginCfg)) {
                return false;
            }

            //var accounts = _atpConfig.AtpLogin.Where(x => x.Enabled).ToArray();
            var account = AtpConfigHelper.Config.Account;
            DllHelper.InitConfig(account.MDServer,
                account.TradeServer,
                account.BrokerId,
                account.UserId,
                account.Password,
                account.UserId,
                account.AppId,
                account.AuthCode,
                AtpConfigHelper.Config.StreamDataServer,
                AtpConfigHelper.Config.StreamTradeServer);
            Task.Delay(200).Wait();

            DllHelper.UpdateTradeClient(account.TradeServer,
                account.BrokerId,
                account.UserId,
                account.Password,
                account.UserId,
                account.AppId,
                account.AuthCode);

            return true;
        }

        private bool Init(LoginCfgBase loginCfg = null) {
            if (!_atpConfigHelper.LoadConfig()) {
                Logger.Error("ATP failed to load config.");
                return false;
            }

            if (AtpConfigHelper.Config == null || AtpConfigHelper.Config.Account == null) {
                Logger.Error("Atp Login information is not correct.");
                return false;
            }

            if (loginCfg == null) { // default
                //var accounts = _atpConfig.AtpLogin.Where(x => x.Enabled).ToArray();
                //foreach (var acc in accounts) {
                //    _allAccounts.Add(acc.UserId);
                //}
            }

            AtpConfigHelper.Config.Exchanges?.ForEach(x => {
                if (x.Enabled) {
                    _exchanges.Add(x);

                    x.Products.ForEach(x => {
                        x.Contracts.ToList().ForEach(c => { // instrumentID: ("CPF2006-APEX");
                            Logger.Info("Add contract: " + c);
                            InstrumentHandlerDic.Add(c, new AtpInstrumentHandler(c));
                        });
                    });
                }
            });

            Task.Delay(200).Wait();

            _zmqHelper = new ZmqHelper(this,
                AtpConfigHelper.Config.StreamDataServer,
                AtpConfigHelper.Config.StreamTradeServer);

            return true;
        }

        public bool StartContract(string instrumentID) {
            if (!InstrumentHandlerDic.ContainsKey(instrumentID)) {
                InstrumentHandlerDic[instrumentID] = new AtpInstrumentHandler(instrumentID);
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
            return _atpConfigHelper;
        }

        public InstrumentHandlerBase GetInstrumentHandler(string market, string productType, string product, string instrument) {
            foreach (var pair in InstrumentHandlerDic) {
                var info = pair.Value.InstrumentInfo;
                var (exch, prod, contract) = AtpUtil.ExtractContract(instrument);
                if (info.Exchange == exch && info.Type == productType
                    && info.Product == prod && info.Contract == contract) {
                    return InstrumentHandlerDic[pair.Key];
                }
            }

            return null;
        }

        public List<string> GetInstruments(string market, string productType, string product) {
            foreach (var ex in _exchanges) {
                if (ex.Market == market && ex.Type == productType) {
                    foreach (var p in ex.Products) {
                        if (p.Name == product) {
                            return p.Contracts.ToList();
                        }
                    }
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
            Logger.Info("Reconnecting ATP...");

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

        public bool ChangePassword(string curPwd, string newPwd) {
            return false;
        }

        public void Dispose() {
            Logger.Info("ATP connection closed");

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
