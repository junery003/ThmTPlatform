//-----------------------------------------------------------------------------
// File Name   : Program
// Author      : junlei
// Date        : 6/7/2021 12:32:49 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Threading.Tasks;
using ThmServiceAdapter.Services;

namespace ThmServiceAdapter {
    internal class Program {
        internal static async Task Main(string[] args) {
            Console.WriteLine("Hello World!");
            var client = new GreetAdapter();
            Console.WriteLine(await client.Start());
        }
    }
}
