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
using ThmServiceAdapter.Services;

namespace ThmServiceAdapter {
    public class ThmClient : IDisposable {
        private readonly string _host;
        private readonly int _port;

        private readonly GrpcChannel _channel;

        private GreetService _adapter;
        private ConnectionService _connAdapter;
        public ThmClient(string host = "localhost", int port = 15001) {
            _host = host;
            _port = port;

            _channel = GrpcChannel.ForAddress($"http://{host}:{port}");
        }

        public async Task<string> Test() {
            if (_adapter == null) {
                _adapter = new GreetService(_channel);
            }

            return await _adapter.Test();
        }

        public async Task<string> LoginAsync(string userName, string password) {
            if (_connAdapter == null) {
                _connAdapter = new ConnectionService(_channel);
            }

            var rsp = await _connAdapter.LoginAsync(userName, password);
            if (rsp.Status == 0) {
                return null;
            }

            return rsp.Message;
        }

        public async Task<string> ConnectAsync(EProviderType providerType, LoginCfgBase loginCfg) {
            if (_connAdapter == null) {
                _connAdapter = new ConnectionService(_channel);
            }

            return await _connAdapter.ConnectAsync(providerType, loginCfg);
        }

        public Dictionary<EProviderType, List<ExchangeCfg>> GetProviders() {
            if (_connAdapter == null) {
                _connAdapter = new ConnectionService(_channel);
            }

            return _connAdapter.GetProviders();
        }

        public void Dispose() {
            _channel.Dispose();
        }
    }
}
