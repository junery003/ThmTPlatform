//-----------------------------------------------------------------------------
// File Name   : OrderService
// Author      : junlei
// Date        : 8/5/2021 12:22:35 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Grpc.Net.Client;
using ThmServices;

namespace ThmServiceAdapter.Services {
    internal class OrderService {
        private readonly Order.OrderClient _client;

        internal OrderService(GrpcChannel channel) {
            _client = new Order.OrderClient(channel);
        }

        internal void SendOrder() {
        }

        internal void Cancel() {

        }

    }
}
