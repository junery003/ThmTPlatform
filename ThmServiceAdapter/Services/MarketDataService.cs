//-----------------------------------------------------------------------------
// File Name   : MarketDataService
// Author      : junlei
// Date        : 8/5/2021 12:22:35 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Grpc.Core;
using Grpc.Net.Client;
using System;
using System.Threading;
using System.Threading.Tasks;
using ThmCommon.Models;
using ThmServices;

namespace ThmServiceAdapter.Services {
    internal class MarketDataService {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private readonly MarketData.MarketDataClient _client;

        internal MarketDataService(GrpcChannel channel) {
            _client = new MarketData.MarketDataClient(channel);
        }

        public event Action<MarketDepthData> OnMarketDataUpdate;

        internal async void Subscribe(ThmInstrumentInfo instrument) {
            Logger.Info("Subscribing instrument: " + instrument.InstrumentID);

            var cts = new CancellationTokenSource();

            var call = _client.Subscribe(new DepthDataSubscribeReq() {
                Provider = (PROVIDER_TYPE)instrument.Provider,
                Exchange = instrument.Exchange,
                Symbol = instrument.InstrumentID
            },
            cancellationToken: cts.Token);

            var watchTsk = Task.Run(async () => {
                try {
                    await foreach (var rsp in call.ResponseStream.ReadAllAsync()) {
                        OnMarketDataUpdate?.Invoke(ParseDepthData(rsp));
                    }
                }
                catch (RpcException ex) when (ex.StatusCode == StatusCode.Cancelled) {
                    Logger.Warn("insutrument Cancelled");
                }
            });

            cts.Cancel();
            await watchTsk;
        }

        private MarketDepthData ParseDepthData(DepthDataSubscribeRsp rsp) {
            throw new NotImplementedException();
        }

        internal void Unsubscribe(ThmInstrumentInfo instrument) {
            Logger.Info("Unsubscribing instrument: " + instrument.InstrumentID);

            _client.Unsubscribe(new DepthDataUnscribeReq() {
                Provider = (PROVIDER_TYPE)instrument.Provider,
                Exchange = instrument.Exchange,
                Symbol = instrument.InstrumentID
            });
        }
    }
}
