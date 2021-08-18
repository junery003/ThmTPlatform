//-----------------------------------------------------------------------------
// File Name   : ThmClient
// Author      : junlei
// Date        : 6/7/2021 12:32:49 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Grpc.Net.Client;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using ThmCommon.Config;
using ThmCommon.Models;
using ThmServiceAdapter.Services;

namespace ThmServiceAdapter {
    public class ThmClient : IDisposable {
        private readonly string _host;
        private readonly int _port;

        private readonly GrpcChannel _channel;

        private GreetService _greetService;
        private ConnectionService _connService;
        private MarketDataService _marketService;
        private OrderService _orderService;

        public ThmClient(string host = "localhost", int port = 15001) {
            _host = host;
            _port = port;

            _channel = GrpcChannel.ForAddress($"http://{host}:{port}");
        }

        public async Task<string> Test() {
            if (_greetService == null) {
                _greetService = new GreetService(_channel);
            }

            return await _greetService.Test();
        }

        public async Task<string> LoginAsync(string userName, string password) {
            if (_connService == null) {
                _connService = new ConnectionService(_channel);
            }

            var rsp = await _connService.LoginAsync(userName, password);
            if (rsp.Status == 0) {
                return null;
            }

            return rsp.Message;
        }

        public async Task<string> ConnectAsync(EProviderType providerType, LoginCfgBase loginCfg) {
            if (_connService == null) {
                _connService = new ConnectionService(_channel);
            }

            return await _connService.ConnectAsync(providerType, loginCfg);
        }

        public Dictionary<EProviderType, List<ExchangeCfg>> GetProviders() {
            if (_connService == null) {
                _connService = new ConnectionService(_channel);
            }

            return _connService.GetProviders();
        }

        public void SubscibeInstrument(ThmInstrumentInfo instrument) {
            if (_marketService == null) {
                _marketService = new MarketDataService(_channel);
            }

            _marketService.Subscribe(instrument);
        }

        #region Order 
        public void SendOrder() {
            _orderService.SendOrder();
        }

        #endregion // Order

        public void Dispose() {
            _channel.Dispose();
        }
    }
}
