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
using ThmCommon.Handlers;
using ThmServices;

namespace ThmTPService.Services {
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

        public override Task<ConnectRsp> Init(ConnectReq req, ServerCallContext context) {
            return Task.FromResult(new ConnectRsp {
            });
        }

    }
}
