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
using ThmCommon.Models;
using ThmServices;

namespace ThmServerAdapter.Services {
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

        internal async Task<string> ConnectAsync(EProviderType providerType, LoginCfgBase loginCfg) {
            ConnectReq connectReq = new() {
                ProviderType = (PROVIDER_TYPE)providerType,
                Account = loginCfg.Account,
                CustomerInfo = loginCfg.CustomerInfo ?? "",
            };

            var rsp = await _client.ConnectAsync(connectReq);
            return rsp.Message;
        }

        internal Dictionary<EProviderType, List<ExchangeCfg>> GetProviders() {
            Dictionary<EProviderType, List<ExchangeCfg>> providers = new();

            var rsp = _client.GetProviders(new GetProvidersReq());
            foreach (var provider in rsp.Providers) {
                var providerType = (EProviderType)provider.ProviderType;
                if (!providers.ContainsKey(providerType)) {
                    providers[providerType] = new List<ExchangeCfg>();
                }

                foreach (var exch in provider.Exchanges) {
                    ExchangeCfg exchangeCfg = new() {
                        Market = exch.Market,
                        Type = exch.Type
                    };

                    foreach (var prod in exch.Products) {
                        ProductCfg rspProd = new() {
                            Name = prod.Name
                        };

                        foreach (var contract in prod.Contracts) {
                            rspProd.Contracts.Add(contract);
                        };

                        exchangeCfg.Products.Add(rspProd);
                    }

                    providers[providerType].Add(exchangeCfg);
                }
            }

            return providers;
        }

        internal bool ChangePassword(EProviderType providerType, string curPwd, string newPwd) {
            throw new System.NotImplementedException();
        }
    }
}
