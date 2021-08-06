//-----------------------------------------------------------------------------
// File Name   : ConnectionService
// Author      : junlei
// Date        : 8/5/2021 12:22:35 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Grpc.Net.Client;
using System.Threading.Tasks;
using ThmCommon.Config;
using ThmServices;

namespace ThmServiceAdapter.Services {
    internal class ConnectorAdapter {
        private readonly Connector.ConnectorClient _client;
        internal ConnectorAdapter(GrpcChannel channel) {
            _client = new Connector.ConnectorClient(channel);
        }

        internal async Task<LoginRsp> LoginAsync(string userName, string password) {
            return await _client.LoginAsync(new LoginReq() {
                UserId = userName,
                Password = password
            });
        }

        internal async Task<ConnectRsp> InitConnectionAsync(EProviderType providerType, ILoginCfg loginCfg) {
            ConnectReq connectReq = new() {

            };

            return await _client.InitConnectionAsync(connectReq);
        }

        internal async Task<GetProvidersRsp> GetProvidersAsync() {
            return await _client.GetProvidersAsync(new GetProvidersReq());
        }

    }
}
