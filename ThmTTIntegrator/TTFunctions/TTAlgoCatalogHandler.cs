//-----------------------------------------------------------------------------
// File Name   : TTAlgoCatalogHandler
// Author      : junlei
// Date        : 2/27/2020 2:01:51 PM
// Description : 
// Version     : 1.0.0
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using tt_net_sdk;

namespace ThmTTIntegrator.TTFunctions {
    /// <summary>
    /// TTAlgoCatalogHandler
    /// </summary>
    internal class TTAlgoCatalogHandler : IDisposable {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();
        private AlgoCatalog _algoCat = null;

        internal TTAlgoCatalogHandler() {
        }

        internal void Start() {
            _algoCat = new AlgoCatalog(Dispatcher.Current);
            _algoCat.OnData += AlgoCat_OnData;
            _algoCat.GetAsync();
        }

        private void AlgoCat_OnData(object sender, AlgoCatalogEventArgs e) {
            if (e.Event == ProductDataEvent.Found) { // Algos were found
                foreach (AlgoInfo ai in _algoCat.Algos) {
                    Logger.Info($"Name = {ai.Alias}");
                }
            }
            else { // Algos were not found
                Logger.Info($"Cannot find algos: {e.Message}");
            }
        }

        public void Dispose() {
            if (_algoCat != null) {
                _algoCat.OnData -= AlgoCat_OnData;
                _algoCat.Dispose();
                _algoCat = null;
            }
        }
    }
}
