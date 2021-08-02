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
    public interface ILoginCfg {
        bool Enabled { get; set; }
    }

    public class AtpLoginCfg : ILoginCfg {
        public bool Enabled { get; set; }

        public string BrokerId { get; set; }
        public string UserId { get; set; }
        public string Password { get; set; }
        public string InvestorId { get; set; }  // investorId is userId
        public string AppId { get; set; }
        public string AuthCode { get; set; }
        public bool IsAuth { get; set; } = true;
    }

    public class TTLoginCfg : ILoginCfg {
        public bool Enabled { get; set; }
        public string Account { get; set; }
    }

    public class TitanLoginCfg : ILoginCfg {
        public bool Enabled { get; set; }
        public string Account { get; set; }
        public string CustomerInfo { get; set; }
    }
}
