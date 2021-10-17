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
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;
using ThmCommon.Models;
using ThmServices;

namespace ThmServerAdapter.Services {
    internal class MarketDataService {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private readonly MarketData.MarketDataClient _client;

        private readonly Dictionary<string, MarketDepthData> _marketData = new();

        internal MarketDataService(GrpcChannel channel) {
            _client = new MarketData.MarketDataClient(channel);
        }

        private event Action<MarketDepthData> OnMarketDataUpdate;

        internal async Task SubscribeAsync(ThmInstrumentInfo instrument, Action<MarketDepthData> onMarketDataUpdate) {
            OnMarketDataUpdate = onMarketDataUpdate;

            _marketData.Add(instrument.ID, null);
            Logger.Info("Subscribing instrument: " + instrument.InstrumentID);

            var cts = new CancellationTokenSource();

            var call = _client.Subscribe(new DepthDataSubscribeReq() {
                Provider = (ProviderType)instrument.Provider,
                Exchange = instrument.Exchange,
                Symbol = instrument.InstrumentID
            },
            cancellationToken: cts.Token);

            await foreach (var rsp in call.ResponseStream.ReadAllAsync(cts.Token)) {
                OnMarketDataUpdate?.Invoke(ParseDepthData(rsp));
            }

            /*
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
            */
        }

        private MarketDepthData ParseDepthData(DepthDataSubscribeRsp msg) {
            string id = msg.Exchange + msg.ProductType + msg.Symbol + (EProviderType)msg.Provider;
            MarketDepthData depthData = _marketData[id];
            if (depthData == null) {
                depthData = new() {
                    Provider = (EProviderType)msg.Provider,
                    Exchange = msg.Exchange,
                    ProductType = msg.ProductType,
                    InstrumentID = msg.Symbol,
                };

                _marketData[id] = depthData;
            }

            depthData.DateTime = msg.DateTime.ToDateTime();
            depthData.LocalDateTime = DateTime.Now;

            depthData.AskPrice1 = (decimal)msg.Ask1;
            depthData.AskPrice2 = (decimal)msg.Ask2;
            depthData.AskPrice3 = (decimal)msg.Ask3;
            depthData.AskPrice4 = (decimal)msg.Ask4;
            depthData.AskPrice5 = (decimal)msg.Ask5;

            depthData.AskQty1 = msg.AQty1;
            depthData.AskQty2 = msg.AQty2;
            depthData.AskQty3 = msg.AQty3;
            depthData.AskQty4 = msg.AQty4;
            depthData.AskQty5 = msg.AQty5;

            depthData.BidPrice1 = (decimal)msg.Bid1;
            depthData.BidPrice2 = (decimal)msg.Bid2;
            depthData.BidPrice3 = (decimal)msg.Bid3;
            depthData.BidPrice4 = (decimal)msg.Bid4;
            depthData.BidPrice5 = (decimal)msg.Bid5;

            depthData.BidQty1 = msg.BQty1;
            depthData.BidQty2 = msg.BQty2;
            depthData.BidQty3 = msg.BQty3;
            depthData.BidQty4 = msg.BQty4;
            depthData.BidQty5 = msg.BQty5;

            return depthData;
        }

        internal void Unsubscribe(ThmInstrumentInfo instrument) {
            if (_marketData.Remove(instrument.ID)) {
                Logger.Info("Unsubscribed instrument: " + instrument.InstrumentID);
            }

            _client.Unsubscribe(new DepthDataUnscribeReq() {
                Provider = (ProviderType)instrument.Provider,
                Exchange = instrument.Exchange,
                Symbol = instrument.InstrumentID
            });
        }
    }
}
