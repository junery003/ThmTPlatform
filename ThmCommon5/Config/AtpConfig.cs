//-----------------------------------------------------------------------------
// File Name   : AtpConfig
// Author      : junlei
// Date        : 1/20/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Collections.Generic;

namespace ThmCommon.Config {
    public class AtpConfig : IConfig {
        public bool Enabled { get; set; } = false;
        public string Provider { get; set; } = "ATP";

        public string StreamDataServer { get; set; }
        public string StreamTradeServer { get; set; }

        public AtpAcount Account { get; } = new AtpAcount();
        public List<ExchangeCfg> Exchanges { get; } = new List<ExchangeCfg>();

        public bool IsValid(ref string err) {
            return true;
        }
    }

    public class AtpAcount {
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
