//-----------------------------------------------------------------------------
// File Name   : GreetClient
// Author      : junlei
// Date        : 6/1/2021 1:44:24 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

using System;
using System.Threading.Tasks;
using Grpc.Net.Client;

namespace ThmTPClient {
    class GreetClient {
        public async Task Start() {
            // The port number(5001) must match the port of the gRPC server.
            using var channel = GrpcChannel.ForAddress("https://localhost:5001");
            var client = new Greeter.GreeterClient(channel);
            var reply = await client.SayHelloAsync(new HelloRequest { Name = "GreeterClient" });
            Console.WriteLine("Greeting: " + reply.Message);

            Console.WriteLine("Press any key to exit...");
            Console.ReadKey();
        }
    }
}
