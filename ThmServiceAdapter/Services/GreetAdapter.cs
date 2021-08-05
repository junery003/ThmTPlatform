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
        private readonly Greeter.GreeterClient _client;

        internal GreetAdapter(GrpcChannel channel) {
            _client = new Greeter.GreeterClient(channel);
        }

        public async Task<string> Test() {
            string user = "client1";
            var reply = await _client.SayHelloAsync(new HelloRequest { Name = user });

            string rlt;
            rlt = reply.Message;
            //Console.WriteLine("Greeting: " + reply.Message);

            reply = await _client.SayHelloAAsync(new HelloRequest { Name = user });
            //Console.WriteLine("Greeting: " + reply.Message);
            rlt += "\r\n" + reply.Message;

            return rlt;
        }
    }
}
