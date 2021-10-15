//-----------------------------------------------------------------------------
// File Name   : MarketDataService
// Author      : junlei
// Date        : 8/5/2021 1:12:16 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Threading.Tasks;
using Google.Protobuf.WellKnownTypes;
using Grpc.Core;
using Microsoft.Extensions.Logging;
using ThmCommon.Models;
using ThmServices;

namespace ThmTPServer.Services {
    /// <summary>
    /// MarketDataService
    /// </summary>
    public class MarketDataService : MarketData.MarketDataBase {
        private readonly ILogger<MarketDataService> _logger;
        public MarketDataService(ILogger<MarketDataService> logger) {
            _logger = logger;
        }

        public override async Task Subscribe(DepthDataSubscribeReq request,
            IServerStreamWriter<DepthDataSubscribeRsp> responseStream,
            ServerCallContext context) {
            _logger.LogInformation("Sending to Subscribe " + request.Symbol);

            var conn = ConnectionService.GetConnector((EProviderType)request.Provider);
            var instHandler = conn.GetInstrumentHandler(request.Symbol);

            instHandler.OnMarketDataUpdated += delegate () {
                responseStream.WriteAsync(BuildRsp(instHandler.CurMarketDepthData));
            };

            while (true) {
                await responseStream.WriteAsync(new DepthDataSubscribeRsp() {
                });
                await Task.Delay(1000);
            }
        }

        private DepthDataSubscribeRsp BuildRsp(MarketDepthData data) {
            return new DepthDataSubscribeRsp {
                Provider = (ProviderType)data.Provider,
                Exchange = data.Exchange,
                ProductType = data.ProductType,
                Symbol = data.InstrumentID,

                AQty1 = data.AskQty1,
                AQty2 = data.AskQty2,
                AQty3 = data.AskQty3,
                AQty4 = data.AskQty4,
                AQty5 = data.AskQty5,

                Ask1 = (double)data.AskPrice1,
                Ask2 = (double)data.AskPrice2,
                Ask3 = (double)data.AskPrice3,
                Ask4 = (double)data.AskPrice4,
                Ask5 = (double)data.AskPrice5,

                BQty1 = data.BidQty1,
                BQty2 = data.BidQty2,
                BQty3 = data.BidQty3,
                BQty4 = data.BidQty4,
                BQty5 = data.BidQty5,

                Bid1 = (double)data.BidPrice1,
                Bid2 = (double)data.BidPrice2,
                Bid3 = (double)data.BidPrice3,
                Bid4 = (double)data.BidPrice4,
                Bid5 = (double)data.BidPrice5,

                DateTime = data.DateTime.ToTimestamp(),
            };
        }
    }
}
