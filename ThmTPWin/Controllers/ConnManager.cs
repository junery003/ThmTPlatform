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
using System.Threading.Tasks;
using ThmCommon.Config;
using ThmCommon.Handlers;
using ThmServiceAdapter.Services;

namespace ThmTPWin.Controllers {
    internal static class ConnManager {
        private static readonly NLog.ILogger _logger = NLog.LogManager.GetCurrentClassLogger();

        private static ConnectionService ConnMgr { get; } = new();

        static ConnManager() {
            var tmp = ConnMgr.Test();

            _logger.Info(tmp.Result);
            //ConnMgr.Load();
        }

        internal static async Task<IConnector> InitConnection(EProviderType providerType, ILoginCfg loginCfg) {
            return await ConnMgr.InitConnection(providerType, loginCfg);
        }

        internal static IConnector GetConnector(EProviderType providerType) {
            //return ConnMgr.GetConnector(providerType);
            
            return null;
        }

        internal static List<EProviderType> GetProviders() {
            return ConnMgr.GetProviders().Result;
        }

        internal static List<ExchangeCfg> GetExchanges(EProviderType providerType) {
            //return ConnMgr.GetExchanges(providerType);
            return null;
        }

        public static void Close() {
            ConnMgr.Dispose();
        }
    }
}
