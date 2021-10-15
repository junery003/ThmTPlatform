//-----------------------------------------------------------------------------
// File Name   : CtpConfig
// Author      : junlei
// Date        : 8/20/2021 10:05:03 AM
// Description : 
// Version     : 1.0.0
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Collections.Generic;

namespace ThmCommon.Config {
    public class CtpConfig : IConfig {
        public bool Enabled { get; set; } = false;
        public string Provider { get; set; } = "CTP";
        public bool SaveData { get; set; } = false;

        public string StreamDataServer { get; set; }
        public string StreamTradeServer { get; set; }

        public CtpAcount Account { get; } = new();
        public List<ExchangeCfg> Exchanges { get; } = new();

        public bool IsValid(ref string err) {
            return true;
        }
    }

    public class CtpAcount {
        public string MDServer { get; set; }
        public string TradeServer { get; set; }

        public string BrokerId { get; set; }
        public string UserId { get; set; }
        public string Password { get; set; }
        public string InvestorId { get; set; }  // investorId is userId
        public string AppId { get; set; }
        public string AuthCode { get; set; }
        public bool IsAuth { get; set; } = true;
    }
}
