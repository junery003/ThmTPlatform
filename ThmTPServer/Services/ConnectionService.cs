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
            return Task.FromResult(new LoginRsp {
                Message = ""
            });
        }

        public override Task<ConnectRsp> Connect(ConnectReq req, ServerCallContext context) {
            EProviderType providerType = EProviderType.Unknown;
            switch (req.ProviderType) {
                case PROVIDER_TYPE.Atp:
                    providerType = EProviderType.ATP;
                    break;
                case PROVIDER_TYPE.Tt:
                    providerType = EProviderType.TT;
                    break;
                case PROVIDER_TYPE.Titan:
                    providerType = EProviderType.TITAN;
                    break;
            }

            if (_connectors.ContainsKey(providerType)) {
                return Task.FromResult(new ConnectRsp {
                    Message = "" //
                });
            }

            IConnector conn = null;
            switch (req.ProviderType) {
                case PROVIDER_TYPE.Atp:
                    conn = new AtpConnector();
                    break;
                case PROVIDER_TYPE.Tt:
                    //conn = new TTConnector();
                    break;
                case PROVIDER_TYPE.Titan:
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
            List<PROVIDER_TYPE> providers = new();

            if (IsEnabled(EProviderType.ATP)) {
                providers.Add(PROVIDER_TYPE.Atp);
            }

            if (IsEnabled(EProviderType.TT)) {
                providers.Add(PROVIDER_TYPE.Tt);
            }

            if (IsEnabled(EProviderType.TITAN)) {
                providers.Add(PROVIDER_TYPE.Titan);
            }

            GetProvidersRsp rsp = new();
            //rsp.Providers.AddRange(providers);
            return Task.FromResult(rsp);
        }

        private static bool IsEnabled(EProviderType provider) {
            return _connectors.ContainsKey(provider)
                 && _connectors[provider].GetConfigHelper().GetConfig().Enabled;
        }
    }
}
