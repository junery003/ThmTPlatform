//-----------------------------------------------------------------------------
// File Name   : AlgoService
// Author      : junlei
// Date        : 8/23/2021 1:23:25 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

using Grpc.Core;
using Microsoft.Extensions.Logging;
using System.Threading.Tasks;
using ThmServices;

namespace ThmTPServer.Services {
    public class AlgoService : Algo.AlgoBase {
        private readonly ILogger<AlgoService> _logger;

        public AlgoService(ILogger<AlgoService> logger) {
            _logger = logger;

        }

        public override Task<ProcessRsp> Process(ProcessReq request, ServerCallContext context) {
            return base.Process(request, context);
        }
    }
}
