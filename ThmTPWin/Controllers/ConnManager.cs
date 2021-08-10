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
using ThmServiceAdapter;

namespace ThmTPWin.Controllers {
    internal static class ConnManager {
        private static readonly NLog.ILogger _logger = NLog.LogManager.GetCurrentClassLogger();

        private static ThmClient _client;

        internal static async Task<string> Login(string server, int port, string userName, string password) {
            _client = new ThmClient(server, port);
            var tmp = await _client.Test();

            _logger.Info(tmp);
            //ConnMgr.Load();

            return await _client.Login(userName, password);
        }

        internal static async Task<string> Connect(EProviderType providerType, LoginCfgBase loginCfg) {
            return await _client.Connect(providerType, loginCfg);
        }

        internal static IConnector GetConnector(EProviderType providerType) {
            //return ConnMgr.GetConnector(providerType);

            return null;
        }

        internal static List<EProviderType> GetProviders() {
            return _client.GetProviders().Result;
        }

        internal static List<ExchangeCfg> GetExchanges(EProviderType providerType) {
            //return ConnMgr.GetExchanges(providerType);
            return null;
        }

        public static void Close() {
            _client.Dispose();
        }
    }
}
