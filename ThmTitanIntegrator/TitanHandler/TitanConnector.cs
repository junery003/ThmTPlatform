//-----------------------------------------------------------------------------
// File Name   : TitanConnector
// Author      : junlei
// Date        : 12/9/2020 2:26:10 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Linq;
using System.Timers;
using ThmCommon.Config;
using ThmCommon.Handlers;
using ThmTitanIntegrator.TitanFunctions;

namespace ThmTitanIntegrator.TitanHandler {
    public class TitanConnector : IConnector {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        public TitanConfig TitanCfg { get; private set; }

        // instrumentID, handler?
        internal Dictionary<string, TitanInstrumentHandler> InstrumentHandlerDic { get; } = new();

        private ZmqHelper _zmqHelper;
        private readonly TitanConfigHelper _titanCfgHelper;

        private readonly List<ExchangeCfg> _exchanges = new();
        private string _account;
        public bool IsConnected { get; private set; } = false;  // MarketDataConnected

        private Timer _mdReconnTimer = null;

        public TitanConnector() {
            _titanCfgHelper = new TitanConfigHelper();
        }

        public bool Connect(LoginCfgBase loginCfg = null) {
            if (!Init(loginCfg)) {
                return false;
            }

            if (!DllHelper.Init()) {
                Logger.Error("Failed to login Titan");
                return false;
            }

            _zmqHelper = new ZmqHelper(this, TitanCfg.StreamDataServer, TitanCfg.StreamTradeServer);
            return true;
        }

        private bool Init(LoginCfgBase loginCfg = null) {
            if (!_titanCfgHelper.LoadConfig()) {
                throw new Exception("Titan failed to load config.");
            }

            TitanCfg = _titanCfgHelper.GetConfig() as TitanConfig;

            if (loginCfg == null) { // default
                _account = TitanCfg.Account.OuchCfg.Account;
            }
            else {
                _account = loginCfg.Account;
            }

            TitanCfg.Exchanges?.ForEach(exch => {
                if (exch.Enabled) {
                    _exchanges.Add(exch);

                    exch.Products.ForEach(prod => prod.Contracts.ToList().ForEach(c => { // instrumentID: "FEFH21";
                        Logger.Info("Add contract: " + c);
                        InstrumentHandlerDic.Add(c, new TitanInstrumentHandler(c, _account));
                    }));
                }
            });

            return true;
        }


        // for Titan, not here!
        public void StartContracts() {
            if (!IsConnected) {
                Logger.Warn("Not connected to market yet.");
                return;
            }

            // for Titan, in in adapter
            /*
            foreach (var handler in InstrumentHandlerDic.Values) {
                handler.Start();
            }
            */
        }

        public bool StartContract(string instrumentID, string exchange = null) {
            if (!InstrumentHandlerDic.ContainsKey(instrumentID)) {
                InstrumentHandlerDic[instrumentID] = new TitanInstrumentHandler(instrumentID, _account);
            }

            return InstrumentHandlerDic[instrumentID].Start();
        }

        public bool StopContract(string instrumentID) {
            if (!InstrumentHandlerDic.ContainsKey(instrumentID)) {
                Logger.Warn("{} not start yet. cannot stop it.", instrumentID);
                return false;
            }

            Logger.Info("Stopping instrument: {}", instrumentID);
            InstrumentHandlerDic[instrumentID].Stop();
            return InstrumentHandlerDic.Remove(instrumentID);
        }

        public IConfigHelper GetConfigHelper() {
            return _titanCfgHelper;
        }

        public InstrumentHandlerBase GetInstrumentHandler(string instrumentID) {
            if (!InstrumentHandlerDic.ContainsKey(instrumentID)) {
                Logger.Error("Instrument not found: {}", instrumentID);
                return null;
            }

            return InstrumentHandlerDic[instrumentID];
        }

        public InstrumentHandlerBase GetInstrumentHandler(string market, string productType, string product, string contract) {
            foreach (var pair in InstrumentHandlerDic) {
                var info = pair.Value.InstrumentInfo;
                if (info.Exchange == market
                    // && info.Type == productType
                    // && info.Product == product
                    && info.Contract == contract) {
                    return InstrumentHandlerDic[pair.Key];
                }
            }

            return null;
        }

        public List<string> GetInstruments(string market, string productType, string product) {
            foreach (var ex in _exchanges) {
                if (ex.Market == market && ex.Type == productType) {
                    foreach (var prod in ex.Products) {
                        if (prod.Name == product) {
                            return prod.Contracts.ToList();
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

        private void ReconnectTimer_Elapsed(object sender, ElapsedEventArgs e) {
            Logger.Info("Reconnecting Titan...");

            StartContracts();
        }

        public bool ChangePassword(string usrId, string curPwd, string newPwd) {
            return DllHelper.ChangePassword(TitanCfg.Account.OuchCfg.UserID, curPwd, newPwd);
        }

        public void Dispose() {
            foreach (var handler in InstrumentHandlerDic.Values) {
                handler.Dispose();
            }

            _zmqHelper?.Dispose();
        }
    }
}
