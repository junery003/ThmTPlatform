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

namespace ThmServiceAdapter {
    internal class Program {
        internal static async Task Main(string[] args) {
            Console.WriteLine("Hello World!");

            await ThmClient.LoginAsync("http://localhost:5001", "UserID", "Password");
        }
    }
}
