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
using ThmServiceAdapter;

namespace ThmTPWin.Controllers {
    internal static class ConnManager {
        private static readonly NLog.ILogger _logger = NLog.LogManager.GetCurrentClassLogger();

        private static ThmClient _client;

        internal static async Task<string> LoginAsync(string server, int port, string userName, string password) {
            _client = new ThmClient(server, port);
            var tmp = await _client.Test();

            _logger.Info(tmp);
            //ConnMgr.Load();

            return await _client.LoginAsync(userName, password);
        }

        internal static async Task<string> ConnectAsync(EProviderType providerType, LoginCfgBase loginCfg) {
            return await _client.ConnectAsync(providerType, loginCfg);
        }

        internal static Dictionary<EProviderType, List<ExchangeCfg>> GetProviders() {
            return _client.GetProviders();
        }

        internal static bool ChangePassword(EProviderType tITAN, string curPwd, string newPwd) {
            throw new System.NotImplementedException();
        }

        public static void Close() {
            _client.Dispose();
        }
    }
}
