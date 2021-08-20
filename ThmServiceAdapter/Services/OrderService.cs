//-----------------------------------------------------------------------------
// File Name   : OrderService
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
using System.Threading.Tasks;
using ThmCommon.Models;
using ThmServices;

namespace ThmServiceAdapter.Services {
    internal class OrderService {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private readonly Order.OrderClient _client;

        public event Action<OrderData> OnOrderUpdate;

        internal OrderService(GrpcChannel channel) {
            _client = new Order.OrderClient(channel);
        }

        public async Task Subscribe() {
            Logger.Info("Subscribing orders ");
            using var call = _client.Subscribe(new SubscribeReq {

            });

            await foreach (var msg in call.ResponseStream.ReadAllAsync()) {
                OnOrderUpdate?.Invoke(ParseOrderData(msg));
            }
        }

        private OrderData ParseOrderData(object msg) {
            throw new NotImplementedException();
        }

        public async Task<string> SendAsync() {
            using var call = _client.SendOrderAsync(new SendOrderReq {

            });

            var rsp = await call.ResponseAsync;
            return rsp.Message;
        }

        public async Task<string> CancelAsync() {
            using var call = _client.DeleteOrderAsync(new DeleteOrderReq {

            });

            var rsp = await call.ResponseAsync;
            return rsp.Message;
        }

        public async Task<string> UpdateAsync() {
            using var call = _client.UpdateOrderAsync(new UpdateOrderReq {

            });

            var rsp = await call.ResponseAsync;
            return rsp.Message;
        }

    }
}
