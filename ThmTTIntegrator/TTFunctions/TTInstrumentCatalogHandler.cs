//-----------------------------------------------------------------------------
// File Name   : TTInstrumentCatalogHandler
// Author      : junlei
// Date        : 1/27/2020 3:57:14 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using tt_net_sdk;

namespace ThmTTIntegrator.TTFunctions {
    internal class TTInstrumentCatalogHandler : IDisposable {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private InstrumentCatalog _instrmentCatalog = null;

        private readonly ProductKey _productKey;

        private IReadOnlyList<Account> _accounts;
        private string _initAccountName;

        public Dictionary<Instrument, TTInstrumentHandler> InstrumentHandlerDic { get; } = new Dictionary<Instrument, TTInstrumentHandler>();

        private const int totalCount = 15;

        private readonly Dictionary<ulong, ProductKey> _instrumentProductDic;
        public TTInstrumentCatalogHandler(ProductKey productKey, Dictionary<ulong, ProductKey> instrumentProductDic) {
            _productKey = productKey;
            _instrumentProductDic = instrumentProductDic;
        }

        internal void Start(IReadOnlyList<Account> accounts, string initAccountName) {
            _accounts = accounts;
            _initAccountName = initAccountName;

            if (_instrmentCatalog == null) {
                _instrmentCatalog = new InstrumentCatalog(_productKey.MarketId, _productKey.Type, _productKey.Name, Dispatcher.Current);
                _instrmentCatalog.OnData += InstrumentCatalogOnData;
                _instrmentCatalog.GetAsync();
            }
        }

        internal bool Start(string instrumentID) {
            foreach (var inst in InstrumentHandlerDic) {
                if (inst.Key.Key.Alias.ToString() == instrumentID) {
                    inst.Value.Start();

                    return true;
                }
            }

            return false;
        }

        internal bool Stop(string instrumentID) {
            //InstrumentHandlerDic[instrument] = new TTInstrumentHandler;
            //var instId = ulong.Parse(instrumentID);
            //var key = _instrumentProductDic[instId];
            //InstrumentHandlerDic[instrument].Stop();

            Logger.Info("Stopping instrument: {}", instrumentID);
            return true;
        }

        private void InstrumentCatalogOnData(object sender, InstrumentCatalogEventArgs e) {
            if (e.Event != ProductDataEvent.Found) {
                Logger.Warn("Cannot find product: " + _productKey.Name + " - " + e.Message);
                return;
            }

            foreach (Instrument instrument in e.InstrumentCatalog.Instruments.Values) {
                if (instrument.ToString().StartsWith("LME CA")) {
                    if (instrument.InstrumentDetails.Alias == "CA 3M") {
                        AddInstrument(instrument);
                    }
                }
                else if (instrument.ToString().StartsWith("LME AH")) {
                    if (instrument.InstrumentDetails.Alias == "AH 3M") {
                        AddInstrument(instrument);
                    }
                }
                else {
                    DateTime exprieDate = instrument.InstrumentDetails.ExpirationDate.GetValueOrDefault();
                    if (exprieDate != null) {
                        var now = DateTime.Now;
                        if (12 * (exprieDate.Year - now.Year) + exprieDate.Month - now.Month <= totalCount) {
                            AddInstrument(instrument);
                        }
                    }
                }
            }
        }

        private void AddInstrument(Instrument instrument) {
            InstrumentHandlerDic[instrument] = new TTInstrumentHandler(instrument, _accounts, _initAccountName,
                Dispatcher.Current);
            _instrumentProductDic[instrument.Key.InstrumentId] = _productKey;

            InstrumentHandlerDic[instrument].Start();
        }

        public TTInstrumentHandler GetInstrumentHandler(Instrument instrument) {
            return InstrumentHandlerDic[instrument];
        }

        public void Dispose() {
            if (_instrmentCatalog != null) {
                _instrmentCatalog.OnData -= InstrumentCatalogOnData;
                _instrmentCatalog.Dispose();
                _instrmentCatalog = null;
            }

            foreach (var hanlder in InstrumentHandlerDic.Values) {
                hanlder.Dispose();
            }
            InstrumentHandlerDic.Clear();
        }
    }
}
