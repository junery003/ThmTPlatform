//-----------------------------------------------------------------------------
// File Name   : TTInstrumentHandler
// Author      : junlei
// Date        : 1/27/2020 3:57:14 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Collections.Generic;
using ThmCommon.Handlers;
using ThmCommon.Models;
using tt_net_sdk;

namespace ThmTTIntegrator.TTFunctions {
    public sealed class TTInstrumentHandler : InstrumentHandlerBase {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        public override MarketDepthData CurMarketDepthData => _priceHandler.CurMarketData;

        protected override TradeHandlerBase TradeHandler => _tradeHandler;
        protected override AlgoHandlerBase AlgoHandler => _algoHandler;

        private readonly IReadOnlyList<Account> _ttAccounts;

        private readonly Instrument _ttInstrument;

        private InstrumentLookup _instrLookupRequest = null;

        private TTPriceHandler _priceHandler = null;
        private TTTradeHandler _tradeHandler;
        private TTAlgoHandler _algoHandler;

        private readonly Dispatcher _dispatcher;

        public TTInstrumentHandler(Instrument instrument, IReadOnlyList<Account> accounts, string initAccountName, Dispatcher current) {
            _ttInstrument = instrument;
            _dispatcher = current;

            InstrumentInfo = new ThmInstrumentInfo {
                Provider = "TT",
                Exchange = _ttInstrument.Key.MarketId.ToString(),
                //Type = TTInstrument.Key.ProductKey.Type.ToString(),

                //InstrumentID = _ttInstrument.InstrumentDetails.Id.ToString(),
                InstrumentID = _ttInstrument.Key.Alias,

                Product = _ttInstrument.Product.Name,
                Contract = _ttInstrument.Key.Alias.Split(' ')[1],

                TickSize = _ttInstrument.InstrumentDetails.TickSize
            };

            _ttAccounts = accounts;
            foreach (var acc in _ttAccounts) {
                Accounts.Add(acc.AccountName);

                if (acc.AccountName == initAccountName) {
                    CurAccount = acc.AccountName;
                }
            }
        }

        public override bool Start() {
            if (_instrLookupRequest == null) {
                _instrLookupRequest = new InstrumentLookup(_dispatcher, _ttInstrument.Key); // Dispatcher.Current
                //_instrLookupRequest = new InstrumentLookup(Dispatcher.Current, _ttInstrument.Key);
                _instrLookupRequest.OnData += InstrumentLookupRequest_OnData;
                _instrLookupRequest.GetAsync();
            }

            return true;
        }

        public override void Stop() {
        }

        public override int GetPosition() {
            return _tradeHandler.GetPosition();
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Event notification for instrument lookup. </summary>
        /// <param name="sender">   Source of the event. </param>
        /// <param name="e">        Instrument lookup subscription event information. </param>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        private void InstrumentLookupRequest_OnData(object sender, InstrumentLookupEventArgs e) {
            if (e.Event == ProductDataEvent.Found) {
                //TTInstrument = e.InstrumentLookup.Instrument;
                Logger.Info("Found: " + _ttInstrument);

                _priceHandler = new TTPriceHandler(this, _ttInstrument);

                _tradeHandler = new TTTradeHandler(this, _ttInstrument, _ttAccounts);
                _algoHandler = new TTAlgoHandler(_tradeHandler);

                // Check Futures All Subscribed
                if (_ttInstrument.Product.Type == ProductType.Future) {
                    //if (Data.Total_Futures_Contract == Data.InstrKey_Instrument.Count)
                    //    FutureReadyEvent.GenerateEvent("Future", "");
                }
                else if (_ttInstrument.Product.Type == ProductType.Option) {
                    //if (Data.Total_Futures_Contract + Options1.Total_Options_Contract == Data.InstrKey_Instrument.Count)
                    //    FutureReadyEvent.GenerateEvent("Option", "");
                }
            }
            else if (e.Event == ProductDataEvent.NotAllowed) {
                Logger.Warn("Not Allowed : Please check your Token access");
            }
            else if (e.Event == ProductDataEvent.MarketUpdated) {
                Logger.Info("Product Market MarketUpdated");
            }
            else { // Instrument was not found and TT API has given up looking for it
                Logger.Error("Cannot find instrument: " + e.Message);
            }
        }

        /*
        private readonly MonitorMM _monitorMM = null;
        private void ScreenMM() {
            int count = 0; // if current one second is valid, the count +1
            while (true) {
                if (((TTOrderbookHandler)OrderbookHandler).ScreenMM(_monitorMM)) {
                    ++count;
                }

                Task.Delay(1000).Wait();
            }

            // todo: the count is valid?
        }
        */

        public override void Dispose() {
            if (_instrLookupRequest != null) {
                _instrLookupRequest.OnData -= InstrumentLookupRequest_OnData;
                _instrLookupRequest.Dispose();
                _instrLookupRequest = null;
            }

            Stop();
            _priceHandler?.Dispose();
            _tradeHandler?.Dispose();
        }
    }
}
