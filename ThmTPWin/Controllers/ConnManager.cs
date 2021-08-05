//-----------------------------------------------------------------------------
// File Name   : ConnManager
// Author      : junlei
// Date        : 7/7/2021 12:22:35 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

using System.Collections.Generic;
using ThmCommon.Config;
using ThmCommon.Handlers;
using ThmServiceAdapter.Services;

namespace ThmTPWin.Controllers {
    internal static class ConnManager {
        private static ConnectionService ConnMgr { get; } = new();

        static ConnManager() {
            //ConnMgr.Load();
        }

        internal static IConnector InitConnection(EProviderType providerType, ILoginCfg loginCfg) {
            return ConnectionService.InitConnection(providerType, loginCfg);
        }

        internal static IConnector GetConnector(EProviderType providerType) {
            return ConnMgr.GetConnector(providerType);
        }

        internal static List<EProviderType> GetProviders() {
            return ConnMgr.GetProviders();
        }

        internal static List<ExchangeCfg> GetExchanges(EProviderType providerType) {
            return ConnMgr.GetExchanges(providerType);
        }

        public static void Close() {
            ConnMgr.Dispose();
        }
    }
}
