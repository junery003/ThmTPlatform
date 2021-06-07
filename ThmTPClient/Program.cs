using System;
using System.Threading.Tasks;

namespace ThmTPClient {
    class Program {
        static async Task Main(string[] args) {
            Console.WriteLine("Hello World!");
            var client = new GreetClient();
            Console.WriteLine(await client.Start());
        }
    }
}
