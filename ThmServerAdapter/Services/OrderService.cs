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
using System.Collections.Generic;
using System.Threading.Tasks;
using ThmCommon.Models;
using ThmServices;

namespace ThmServerAdapter.Services {
    internal class OrderService {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private readonly Order.OrderClient _client;

        private event Action<OrderData> OnOrderUpdate;

        private readonly Dictionary<string, OrderData> _orderData = new();

        internal OrderService(GrpcChannel channel) {
            _client = new Order.OrderClient(channel);
        }

        public async Task Subscribe(ThmInstrumentInfo instrument, Action<OrderData> onOrderDataUpdate) {
            OnOrderUpdate = onOrderDataUpdate;

            Logger.Info("Subscribing orders ");
            using var call = _client.Subscribe(new SubscribeReq {
                Exchange = instrument.Exchange,
                Provider = (PROVIDER_TYPE)instrument.Provider,
                Symbol = instrument.InstrumentID
            });

            await foreach (var msg in call.ResponseStream.ReadAllAsync()) {
                OnOrderUpdate?.Invoke(ParseOrderData(msg));
            }
        }

        private OrderData ParseOrderData(SubscribeRsp msg) {
            string id = msg.Exchange + msg.Type + msg.Symbol + msg.Provider;
            var orderData = _orderData[id];
            if (orderData == null) {
                orderData = new OrderData(id) {
                    Provider = (EProviderType)msg.Provider,
                    Exchange = msg.Exchange,
                    ProductType = msg.Type,
                    Type = msg.OrderType
                };
            }

            orderData.LocalDateTime = DateTime.Now;
            orderData.BuyOrSell = msg.IsBuy ? EBuySell.Buy : EBuySell.Sell;
            orderData.EntryPrice = (decimal)msg.Price;
            orderData.Qty = (int)msg.Qty;

            return orderData;
        }

        public async Task<string> SendAsync() {
            var call = await _client.SendOrderAsync(new SendOrderReq {

            });

            return call.Message;
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

        internal int GetPosition(ThmInstrumentInfo instrument) {
            throw new NotImplementedException();
        }
    }
}
