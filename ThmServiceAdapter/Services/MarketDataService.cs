//-----------------------------------------------------------------------------
// File Name   : MarketDataService
// Author      : junlei
// Date        : 8/5/2021 12:22:35 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Grpc.Net.Client;
using ThmCommon.Models;
using ThmServices;

namespace ThmServiceAdapter.Services {
    internal class MarketDataService {
        private readonly MarketData.MarketDataClient _client;

        internal MarketDataService(GrpcChannel channel) {
            _client = new MarketData.MarketDataClient(channel);
        }

        internal void Subscribe(ThmInstrumentInfo instrument) {
            _client.Subscribe(new DepthDataSubscribeReq() {
                Provider = (PROVIDER_TYPE)instrument.Provider,
                Exchange = instrument.Exchange,
                Symbol = instrument.InstrumentID
            });
        }
    }
}
