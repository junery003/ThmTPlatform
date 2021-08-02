//-----------------------------------------------------------------------------
// File Name   : TTConfig
// Author      : junlei
// Date        : 5/25/2020 4:13:15 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Collections.Generic;

namespace ThmCommon.Config {
    public class TTConfig : IConfig {
        public bool Enabled { get; set; } = false;
        public string Provider { get; set; } = "TT";

        public TTAccount Account { get; set; }
        public List<ExchangeCfg> Exchanges { get; } = new List<ExchangeCfg>();

        public bool IsValid(ref string err) {
            return Enabled && Account.IsValid();
        }
    }

    /// <summary>
    /// TT account 
    /// </summary>
    public class TTAccount {
        public string Mode { get; set; } // server/client
        public string Environment { get; set; } // ProdSim/ProdLive
        public string AppKey { get; set; }
        public string Account { get; set; }

        public bool IsValid() {
            return true; // AppKey.Trim().Length == 73;
        }
    }
}
