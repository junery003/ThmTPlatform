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
    public class GreetClient {
        public async Task<string> Start() {
            // The port number(5001) must match the port of the gRPC server.
            using var channel = GrpcChannel.ForAddress("https://localhost:5001");
            var client = new Greeter.GreeterClient(channel);

            string user = "client1";
            var reply = await client.SayHelloAsync(new HelloRequest { Name = user });

            string rlt;
            rlt = reply.Message;
            //Console.WriteLine("Greeting: " + reply.Message);

            reply = await client.SayHelloAAsync(new HelloRequest { Name = user });
            //Console.WriteLine("Greeting: " + reply.Message);
            rlt += "\r\n" + reply.Message;

            return rlt;
        }
    }
}
