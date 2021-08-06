//-----------------------------------------------------------------------------
// File Name   : Program
// Author      : junlei
// Date        : 1/20/2020 5:13:18 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Threading.Tasks;
using ThmAtpIntegrator.AtpHandler;

namespace ThmAtpIntegrator {
    internal class Program {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        internal static void Main(string[] args) {
            try {
                Logger.Info("Start to run ATP...");
                var atpConn = new AtpConnector();
                try {
                    atpConn.Connect();

                    bool quit = false;
                    while (!quit) {
                        Task.Delay(200).Wait();

                        string input = Console.ReadLine().Trim().ToLower();
                        switch (input) {
                        case "q":
                            quit = true;
                            break;
                        case "r":  // tbd: reload contracts
                            break;
                        default:
                            break;
                        }
                    }
                }
                catch (Exception ex) {
                    Logger.Error(ex);
                }
                finally {
                    atpConn?.Dispose();
                }
            }
            catch (Exception ex) {
                Logger.Error("Error: " + ex.Message);
            }

            Console.ReadKey();
        }
    }
}
