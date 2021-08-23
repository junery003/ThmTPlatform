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
using ThmServerAdapter.Services;

namespace ThmServerAdapter {
    public static class ThmClient {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private static GrpcChannel _channel;

        private static Dictionary<EProviderType, List<ExchangeCfg>> _providers;
        private static readonly ISet<ThmInstrumentInfo> _instruments = new HashSet<ThmInstrumentInfo>();

        public static event Action<MarketDepthData> OnMarketDataUpdate;
        public static event Action<OrderData> OnOrderDataUpdate;

        #region Connection
        private static GreetService _greetService; // test
        private static ConnectionService _connService;

        public static async Task<string> LoginAsync(string serverAddr, string userName, string password) {
            _channel = GrpcChannel.ForAddress(serverAddr);

            await TestAsync();

            _connService = new ConnectionService(_channel);
            var call = await _connService.LoginAsync(userName, password);
            if (call.Status == 0) {
                return null;
            }

            return call.Message;
        }

        private static async Task TestAsync() {
            _greetService = new GreetService(_channel);
            var callTest = await _greetService.TestAsync();
            Logger.Info("GRPC testing OK. " + callTest);
        }

        public static async Task<string> ConnectAsync(EProviderType providerType, LoginCfgBase loginCfg) {
            return await _connService.ConnectAsync(providerType, loginCfg);
        }

        public static Dictionary<EProviderType, List<ExchangeCfg>> GetProviders() {
            _providers = _connService.GetProviders();
            return _providers;
        }

        public static List<ExchangeCfg> GetExchanges(EProviderType providerType) {
            return _providers[providerType];
        }

        #endregion // Connection

        #region Market Data
        private static MarketDataService _marketService;

        public static Task SubscibeInstrument(ThmInstrumentInfo instrument) {
            _instruments.Add(instrument);

            if (_marketService == null) {
                _marketService = new MarketDataService(_channel);
            }

            return _marketService.Subscribe(instrument, OnMarketDataUpdate);
        }

        public static void UnubscibeInstrument(ThmInstrumentInfo instrument) {
            _marketService.Unsubscribe(instrument);
        }

        #endregion

        #region Order 
        private static OrderService _orderService;

        public static Task SubscribeOrderData(ThmInstrumentInfo instrument) {
            if (_orderService == null) {
                _orderService = new OrderService(_channel);
            }

            return _orderService.Subscribe(instrument, OnOrderDataUpdate);
        }

        public static async Task<string> SendOrder() {
            if (_orderService == null) {
                _orderService = new OrderService(_channel);
            }

            return await _orderService.SendAsync();
        }

        public static async Task<string> DeleteOrder() {
            if (_orderService == null) {
                _orderService = new OrderService(_channel);
            }

            return await _orderService.CancelAsync();
        }

        public static async Task<string> UpdateOrder() {
            if (_orderService == null) {
                _orderService = new OrderService(_channel);
            }

            return await _orderService.UpdateAsync();
        }

        #endregion // Order

        #region Others
        public static async Task<string> ChangePasswordAsync(EProviderType providerType, string curPwd, string newPwd) {
            return await _connService.ChangePasswordAsync(providerType, curPwd, newPwd);
        }

        #endregion // Others

        public static void Close() {
            _channel?.Dispose();
        }
    }
}
