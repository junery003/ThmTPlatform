//-----------------------------------------------------------------------------
// File Name   : Program
// Author      : junlei
// Date        : 8/20/2021 5:13:18 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Threading.Tasks;
using ThmCtpIntegrator.CtpHandler;

namespace ThmCtpIntegrator {
    internal class Program {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        internal static void Main(string[] args) {
            try {
                Logger.Info("Start to run CTP...");
                var conn = new CtpConnector();
                try {
                    if (!conn.Connect()) {
                        return;
                    }

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
                    conn?.Dispose();
                }
            }
            catch (Exception ex) {
                Logger.Error("Error: " + ex.Message);
            }

            Console.ReadKey();
        }
    }
}
