//-----------------------------------------------------------------------------
// File Name   : Program
// Author      : junlei
// Date        : 1/20/2020 10:57:14 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Threading.Tasks;
using ThmTTIntegrator.TTHandler;

namespace ThmTTIntegrator {
    internal static class Program {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        internal static void Main() {
            try {
                //if (config.ThmConfig.TTConfig.OptionMMConfig != null && config.ThmConfig.TTConfig.OptionMMConfig.Enabled) {
                //    OptionMMAlgo.Initialize(config.TTConfig.OptionMMConfig);
                //}

                Logger.Info("========== Starting to run TT ...");
                var ttConn = new TTConnector();
                try {
                    ttConn.Connect();

                    bool quit = false;
                    while (!quit) {
                        Task.Delay(200).Wait();

                        var input = Console.ReadLine().Trim().ToLower();
                        switch (input) {
                            case "q":
                                quit = true;
                                break;
                            case "r":  // tbd: reload contracts
                                break;
                            /*
                            case "o1": {
                                    OptionMMAlgo.ClipSize = 1;
                                    OptionMMAlgo.StartStop = true;
                                }
                                break;
                            case "o10": {
                                    OptionMMAlgo.ClipSize = 10;
                                    OptionMMAlgo.StartStop = true;
                                }
                                break;
                            case "o0": {
                                    OptionMMAlgo.ClipSize = 0;
                                    OptionMMAlgo.StartStop = false;
                                }
                                break;
                            */
                            default:
                                break;
                        }
                    }
                }
                catch (Exception ex) {
                    Logger.Error(ex);
                }
                finally {
                    ttConn.Dispose();
                }
            }
            catch (Exception ex) {
                Logger.Error("Error: " + ex.Message);
            }

            Console.ReadKey();
        }
    }
}
