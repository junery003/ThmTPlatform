﻿//-----------------------------------------------------------------------------
// File Name   : ConnectionService
// Author      : junlei
// Date        : 8/5/2021 12:22:35 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Grpc.Net.Client;
using System;
using System.Threading.Tasks;
using ThmCommon.Config;
using ThmCommon.Handlers;
using ThmServices;

namespace ThmServiceAdapter.Services {
    public class ConnectionService : IDisposable {
        private readonly string _host;
        private readonly int _port;

        private readonly GrpcChannel _channel;

        private GreetAdapter _adapter;
        private ConnectorAdapter _connectorAdapter;
        public ConnectionService(string host = "localhost", int port = 5001) {
            _host = host;
            _port = port;

            _channel = GrpcChannel.ForAddress($"https://{host}:{port}");
        }

        public async Task<string> Test() {
            if (_adapter == null) {
                _adapter = new GreetAdapter(_channel);
            }

            return await _adapter.Test();
        }

        public async Task<IConnector> InitConnection(EProviderType providerType, ILoginCfg loginCfg) {
            if (_connectorAdapter == null) {
                _connectorAdapter = new ConnectorAdapter(_channel);
            }

            ConnectRsp rsp = await _connectorAdapter.InitConnection(providerType, loginCfg);
            IConnector connector;
            switch (providerType) {
                case EProviderType.ATP:
                    connector = new AtpConnection();
            }

        }

        public void Dispose() {
            _channel.Dispose();
        }
    }
}
