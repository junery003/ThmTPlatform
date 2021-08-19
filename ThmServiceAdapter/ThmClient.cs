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
using System.Collections.Generic;
using System.Threading.Tasks;
using ThmCommon.Config;
using ThmCommon.Models;
using ThmServiceAdapter.Services;

namespace ThmServiceAdapter {
    public static class ThmClient {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private static string _host;
        private static int _port;
        private static GrpcChannel _channel;

        private static Dictionary<EProviderType, List<ExchangeCfg>> _providers;
        private static readonly ISet<ThmInstrumentInfo> _instruments = new HashSet<ThmInstrumentInfo>();

        private static GreetService _greetService; // test

        private static ConnectionService _connService;
        private static MarketDataService _marketService;
        private static OrderService _orderService;

        public static async Task<string> LoginAsync(string userName, string password,
            string host = "localhost", int port = 15001) {
            _host = host;
            _port = port;

            _channel = GrpcChannel.ForAddress($"http://{_host}:{_port}");

            if (_greetService == null) {
                _greetService = new GreetService(_channel);
            }
            var tmp = await _greetService.Test();
            Logger.Info("GRPC testing OK. " + tmp);

            if (_connService == null) {
                _connService = new ConnectionService(_channel);
            }
            var rsp = await _connService.LoginAsync(userName, password);
            if (rsp.Status == 0) {
                return null;
            }

            return rsp.Message;
        }

        public static async Task<string> ConnectAsync(EProviderType providerType, LoginCfgBase loginCfg) {
            if (_connService == null) {
                _connService = new ConnectionService(_channel);
            }
            return await _connService.ConnectAsync(providerType, loginCfg);
        }

        public static Dictionary<EProviderType, List<ExchangeCfg>> GetProviders() {
            _providers = _connService.GetProviders();
            return _providers;
        }

        public static List<ExchangeCfg> GetExchanges(EProviderType providerType) {
            return _providers[providerType];
        }

        #region Market Data
        public static void SubscibeInstrument(ThmInstrumentInfo instrument) {
            _instruments.Add(instrument);

            if (_marketService == null) {
                _marketService = new MarketDataService(_channel);
            }

            _marketService.Subscribe(instrument);
        }

        public static void UnubscibeInstrument(ThmInstrumentInfo instrument) {
            _marketService.Unsubscribe(instrument);
        }

        #endregion

        #region Order 
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

        public static bool ChangePassword(EProviderType providerType, string curPwd, string newPwd) {
            return _connService.ChangePassword(providerType, curPwd, newPwd);
        }

        public static void Close() {
            _channel.Dispose();
        }
    }
}
