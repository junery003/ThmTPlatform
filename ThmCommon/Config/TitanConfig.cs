//-----------------------------------------------------------------------------
// File Name   : TitanConfig
// Author      : junlei
// Date        : 11/4/2020 10:48:04 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Collections.Generic;

namespace ThmCommon.Config {
    public class TitanConfig : IConfig {
        public bool Enabled { get; set; } = false;
        public string Provider { get; set; } = "Titan";

        public string StreamDataServer { get; set; }
        public string StreamTradeServer { get; set; }

        public TitanAcount Account { get; set; }
        public List<ExchangeCfg> Exchanges { get; } = new List<ExchangeCfg>();

        public bool IsValid(ref string err) {
            return true;
        }
    }

    public class TitanAcount {
        public ItchConfig ItchCfg { get; set; }
        public GlimpseConfig GlimpseCfg { get; set; }
        public OuchConfig OuchCfg { get; set; }
        public OMnetConfig OMnetCfg { get; set; }

        public string UserId { get => OuchCfg.UserID; set { } }
    }

    public class ItchConfig {
        public string Server { get; set; }
        public int Port { get; set; }
    }

    public class OuchConfig {
        public string Server { get; set; }
        public int Port { get; set; }
        public string UserID { get; set; }
        public string Password { get; set; }
        public string Account { get; set; }
        public string CustomerInfo { get; set; }
        public int Heartbeat { get; set; } // in seconds
    }

    public class GlimpseConfig {
        public string Server { get; set; }
        public int Port { get; set; }
        public string UserID { get; set; }
        public string Password { get; set; }
        public int Heartbeat { get; set; } // in seconds
    }

    public class OMnetConfig {
        public string Server { get; set; }
        public int Port { get; set; }
    }
}
