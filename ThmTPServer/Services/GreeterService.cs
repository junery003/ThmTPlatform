//-----------------------------------------------------------------------------
// File Name   : GreeterService
// Author      : junlei
// Date        : 6/1/2021 1:44:24 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

using Grpc.Core;
using Microsoft.Extensions.Logging;
using System.Threading.Tasks;
using ThmServices;

namespace ThmTPService.Services {
    /// <summary>
    /// GreeterService
    /// </summary>
    public class GreeterService : Greeter.GreeterBase {
        private readonly ILogger<GreeterService> _logger;
        public GreeterService(ILogger<GreeterService> logger) {
            _logger = logger;
        }

        public override Task<HelloReply> SayHello(HelloRequest req, ServerCallContext context) {
            _logger.LogInformation("Sending hello reply to " + req.Name);

            return Task.FromResult(new HelloReply {
                Message = "Hello " + req.Name
            });
        }
    }
}
