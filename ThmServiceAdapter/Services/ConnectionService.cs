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
    internal class ConnectionService {
        private readonly Connection.ConnectionClient _client;
        internal ConnectionService(GrpcChannel channel) {
            _client = new Connection.ConnectionClient(channel);
        }

        internal async Task<LoginRsp> LoginAsync(string userName, string password) {
            return await _client.LoginAsync(new LoginReq() {
                UserId = userName,
                Password = password
            });
        }

        internal async Task<ConnectRsp> InitAsync(EProviderType providerType, ILoginCfg loginCfg) {
            ConnectReq connectReq = new() {

            };

            return await _client.InitAsync(connectReq);
        }

        internal async Task<GetProvidersRsp> GetProvidersAsync() {
            return await _client.GetProvidersAsync(new GetProvidersReq());
        }
    }
}
