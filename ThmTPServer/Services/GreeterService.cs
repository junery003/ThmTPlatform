//-----------------------------------------------------------------------------
// File Name   : GreeterService
// Author      : junlei
// Date        : 6/1/2021 1:44:24 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

using System.Threading.Tasks;
using Grpc.Core;
using Microsoft.Extensions.Logging;
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
            return Task.FromResult(new HelloReply {
                Message = "Hello " + req.Name
            });
        }

        public override Task<HelloReply> SayHelloA(HelloRequest req, ServerCallContext context) {
            return Task.FromResult(new HelloReply {
                Message = "Hello-async " + req.Name
            });
        }
    }
}
