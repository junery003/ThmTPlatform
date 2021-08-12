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
using System.Collections.Generic;
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

        internal async Task<string> Connect(EProviderType providerType, LoginCfgBase loginCfg) {
            ConnectReq connectReq = new() {
                ProviderType = (PROVIDER_TYPE)providerType,
                Account = loginCfg.Account,
                CustomerInfo = loginCfg.CustomerInfo ?? "",
            };

            var rsp = await _client.ConnectAsync(connectReq);
            return rsp.Message;
        }

        internal async Task<GetProvidersRsp> GetProvidersAsync() {
            return await _client.GetProvidersAsync(new GetProvidersReq());
        }

        internal Dictionary<EProviderType, List<ExchangeCfg>> GetProviders() {
            var rsp = _client.GetProviders(new GetProvidersReq());

            Dictionary<EProviderType, List<ExchangeCfg>> providers = new();

            //foreach (var type in rsp.ProviderTypes) {
            //    switch (type) {
            //        case PROVIDER_TYPE.Atp: {
            //                providers.Add(EProviderType.ATP);
            //                break;
            //            }
            //        case PROVIDER_TYPE.Tt: {
            //                providers.Add(EProviderType.TT);
            //                break;
            //            }
            //        case PROVIDER_TYPE.Titan: {
            //                providers.Add(EProviderType.TITAN);
            //                break;
            //            }
            //        default: {
            //                break;
            //            }
            //    }
            //}

            return providers;
        }
    }
}
