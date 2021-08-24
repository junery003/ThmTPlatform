//-----------------------------------------------------------------------------
// File Name   : ConnectionService
// Author      : junlei
// Date        : 8/1/2021 1:44:24 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

using Grpc.Core;
using Microsoft.Extensions.Logging;
using Newtonsoft.Json;
using System.Collections.Generic;
using System.IO;
using System.Threading.Tasks;
using ThmAtpIntegrator.AtpHandler;
using ThmCommon.Config;
using ThmCommon.Handlers;
using ThmCommon.Models;
using ThmServices;
using ThmTitanIntegrator.TitanHandler;

namespace ThmTPService.Services {
    /// <summary>
    /// ConnectionService
    /// </summary>
    public class ConnectionService : Connection.ConnectionBase {
        private readonly ILogger<ConnectionService> _logger;

        private static readonly string ServerConfigPath = Directory.GetCurrentDirectory() + "/config/server_config.json";
        private static ServerConfig Config;

        private static readonly Dictionary<EProviderType, IConnector> _connectors = new();

        public ConnectionService(ILogger<ConnectionService> logger) {
            _logger = logger;

            Config = JsonConvert.DeserializeObject<ServerConfig>(File.ReadAllText(ServerConfigPath));
            InstrumentHandlerBase.EnableSaveData = Config.SaveData;
        }

        public override Task<LoginRsp> Login(LoginReq req, ServerCallContext context) {
            _logger.LogInformation("Login: " + req.UserId);
            return Task.FromResult(new LoginRsp {
                Message = ""
            });
        }

        public override Task<LogoutRsp> Logout(LogoutReq req, ServerCallContext context) {
            return base.Logout(req, context);
        }

        public override Task<ConnectRsp> Connect(ConnectReq req, ServerCallContext context) {
            _logger.LogInformation("Connect " + req.Account);

            var providerType = EProviderType.Unknown;
            switch (req.Provider) {
                case ProviderType.Atp:
                    providerType = EProviderType.ATP;
                    break;
                case ProviderType.Tt:
                    providerType = EProviderType.TT;
                    break;
                case ProviderType.Titan:
                    providerType = EProviderType.TITAN;
                    break;
            }

            if (_connectors.ContainsKey(providerType)) {
                return Task.FromResult(new ConnectRsp {
                    Message = "" //
                });
            }

            IConnector conn = null;
            switch (req.Provider) {
                case ProviderType.Atp:
                    conn = new AtpConnector();
                    break;
                case ProviderType.Tt:
                    //conn = new TTConnector();
                    break;
                case ProviderType.Titan:
                    conn = new TitanConnector();
                    break;
            }

            if (conn == null) {
                return Task.FromResult(new ConnectRsp {
                    Message = conn == null ? "Error" : ""
                });
            }

            if (!conn.Connect(new LoginCfgBase() {
                Account = req.Account,
                CustomerInfo = req.CustomerInfo,
            })) {
                return Task.FromResult(new ConnectRsp {
                    Message = conn == null ? "Error" : ""
                });
            }

            _connectors[providerType] = conn;  // one provide should have one connection

            return Task.FromResult(new ConnectRsp {
                Message = ""
            });
        }

        public override Task<GetProvidersRsp> GetProviders(GetProvidersReq req, ServerCallContext context) {
            List<Provider> providers = new();

            if (IsEnabled(EProviderType.ATP)) {
                providers.Add(BuildProvider(EProviderType.ATP));
            }

            if (IsEnabled(EProviderType.TT)) {
                providers.Add(BuildProvider(EProviderType.TT));
            }

            if (IsEnabled(EProviderType.TITAN)) {
                providers.Add(BuildProvider(EProviderType.TITAN));
            }

            GetProvidersRsp rsp = new();
            rsp.Providers.AddRange(providers);
            return Task.FromResult(rsp);
        }

        private static Provider BuildProvider(EProviderType providerType) {
            Provider provider = new() {
                ProviderType = (ProviderType)providerType,
            };

            var exchanges = _connectors[providerType].GetConfigHelper().GetConfig().Exchanges;
            foreach (var exch in exchanges) {
                var rspExchange = new Exchange {
                    Type = exch.Type,
                    Market = exch.Market,
                };

                foreach (var prod in exch.Products) {
                    var rspProd = new Product {
                        Name = prod.Name,
                    };
                    foreach (var c in prod.Contracts) {
                        rspProd.Contracts.Add(c);
                    }

                    rspExchange.Products.Add(rspProd);
                }

                provider.Exchanges.Add(rspExchange);
            }

            return provider;
        }

        private static bool IsEnabled(EProviderType provider) {
            return _connectors.ContainsKey(provider)
                 && _connectors[provider].GetConfigHelper().GetConfig().Enabled;
        }

        public static IConnector GetConnector(EProviderType provider) {
            if (_connectors.ContainsKey(provider)) {
                return _connectors[provider];
            }

            return null;
        }

        public override Task<UpdateTitanPasswrodRsp> UpdateTitanPasswrod(UpdateTitanPasswrodReq req, ServerCallContext context) {
            var rlt = GetConnector(EProviderType.TITAN)?.ChangePassword(req.CurPassword, req.NewPassword);

            return Task.FromResult(new UpdateTitanPasswrodRsp() {
                Message = rlt.Value ? null : "Failed to chang password"
            }); ;
        }
    }
}
