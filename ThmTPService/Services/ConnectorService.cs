//-----------------------------------------------------------------------------
// File Name   : ConnectorService
// Author      : junlei
// Date        : 8/1/2021 1:44:24 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

using Grpc.Core;
using Microsoft.Extensions.Logging;
using System.Threading.Tasks;

namespace ThmTPService.Services {
    public class ConnectorService : Connector.ConnectorBase {
        private readonly ILogger<ConnectorService> _logger;
        public ConnectorService(ILogger<ConnectorService> logger) {
            _logger = logger;
        }

        public override Task<LoginRsp> Login(LoginReq req, ServerCallContext context) {
            return Task.FromResult(new LoginRsp {
                Message = ""
            });
        }

        public override Task<ConnectRsp> InitConnection(ConnectReq req, ServerCallContext context) {
            return Task.FromResult(new ConnectRsp {
            });
        }
    }
}
