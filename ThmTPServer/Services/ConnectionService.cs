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
using System.IO;
using System.Threading.Tasks;
using ThmAtpIntegrator.AtpHandler;
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

            if (!conn.Connect(new ThmCommon.Config.LoginCfgBase() {
                Account = req.Account,
                CustomerInfo = req.CustomerInfo,
            })) {
                return Task.FromResult(new ConnectRsp {
                    Message = conn == null ? "Error" : ""
                });
            }

            return Task.FromResult(new ConnectRsp {
                Message = ""
            });
        }
    }
}
