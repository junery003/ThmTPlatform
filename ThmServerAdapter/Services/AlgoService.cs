//-----------------------------------------------------------------------------
// File Name   : AlgoService
// Author      : junlei
// Date        : 8/23/2021 12:22:35 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Grpc.Net.Client;
using System.Threading.Tasks;
using ThmCommon.Models;
using ThmServices;

namespace ThmServerAdapter.Services {
    internal class AlgoService {
        private readonly Algo.AlgoClient _client;
        internal AlgoService(GrpcChannel channel) {
            _client = new Algo.AlgoClient(channel);
        }

        internal async Task<int> Process(AlgoData algoData) {
            var call = await _client.ProcessAsync(new ProcessReq() {
                Provider = (ProviderType)algoData.Provider,
                Exchange = algoData.ExchangeID,
                Symbol = algoData.InstrumentID,
                Price = (double)algoData.Price,
                Qty = algoData.Qty,
                BuySell = (BuySell)algoData.BuyOrSell,
                Tag = algoData.Tag
            });

            return call.Result;
        }
    }
}
