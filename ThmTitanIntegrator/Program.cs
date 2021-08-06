//-----------------------------------------------------------------------------
// File Name   : TitanAlgoHandler
// Author      : junlei
// Date        : 11/3/2020 12:05:03 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Threading.Tasks;
using ThmTitanIntegrator.TitanHandler;

namespace ThmTitanIntegrator {
    class Program {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();
        static void Main(string[] args) {
            try {
                Logger.Info("Start to run SGX TITAN...");
                var titanConn = new TitanConnector();
                try {
                    titanConn.Init();
                    titanConn.Connect();

                    bool quit = false;
                    while (!quit) {
                        Task.Delay(200).Wait();

                        string input = Console.ReadLine().Trim().ToLower();
                        switch (input) {
                        case "q":
                            quit = true;
                            break;
                        case "r":  // tbd: reload contracts not work
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
                    titanConn?.Dispose();
                }
            }
            catch (Exception ex) {
                Logger.Error("Error: " + ex.Message);
            }

            Console.ReadKey();
        }
    }
}
