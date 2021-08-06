//-----------------------------------------------------------------------------
// File Name   : LoginConfig
// Author      : junlei
// Date        : 7/30/2021 6:08:07 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

namespace ThmCommon.Config {
    public class LoginCfgBase {
        public virtual bool Enabled { get; set; }
        public virtual string Account { get; set; }
        public virtual string CustomerInfo { get; set; }
    }

    public class AtpLoginCfg : LoginCfgBase {
        public override bool Enabled { get; set; }

        public string BrokerId { get; set; }
        public string UserId { get; set; }
        public string Password { get; set; }
        public string InvestorId { get; set; }  // investorId is userId
        public string AppId { get; set; }
        public string AuthCode { get; set; }
        public bool IsAuth { get; set; } = true;

        public override string Account { get => UserId; set { UserId = value; } }
        public override string CustomerInfo { get; set; }
    }

    public class TTLoginCfg : LoginCfgBase {
        public override bool Enabled { get; set; }
        public override string Account { get; set; }
        public override string CustomerInfo { get; set; }
    }

    public class TitanLoginCfg : LoginCfgBase {
        public override bool Enabled { get; set; }
        public override string Account { get; set; }
        public override string CustomerInfo { get; set; }
    }
}
