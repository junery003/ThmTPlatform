//-----------------------------------------------------------------------------
// File Name   : GreetClient
// Author      : junlei
// Date        : 6/1/2021 1:44:24 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

using Grpc.Net.Client;
using System.Threading.Tasks;
using ThmServices;

namespace ThmServiceAdapter.Services {
    internal class GreetAdapter {
        private static readonly NLog.ILogger _logger = NLog.LogManager.GetCurrentClassLogger();

        private readonly Greeter.GreeterClient _client;

        internal GreetAdapter(GrpcChannel channel) {
            _client = new Greeter.GreeterClient(channel);
        }

        public async Task<string> Test() {
            string user = "client1";
            var reply = await _client.SayHelloAsync(new HelloRequest { Name = user });

            string rlt = reply.Message;
            _logger.Info("Greeting: " + reply.Message);

            reply = await _client.SayHelloAAsync(new HelloRequest { Name = user });

            rlt += "\r\n" + reply.Message;
            _logger.Info("Greeting: " + reply.Message);

            return rlt;
        }
    }
}
