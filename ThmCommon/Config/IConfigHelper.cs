//-----------------------------------------------------------------------------
// File Name   : IConfigHelper
// Author      : junlei
// Date        : 12/9/2020 5:03:18 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

using System.Collections.Generic;

namespace ThmCommon.Config {
    public enum EProviderType {
        Unknown = 0,
        ATP = 1,
        TT = 2,
        TITAN = 3,
    };

    public interface IConfigHelper {
        bool LoadConfig();
        IConfig GetConfig();
        void SaveConfig();
    }

    public interface IConfig {
        bool Enabled { get; set; }
        List<ExchangeCfg> Exchanges { get; }
        bool IsValid(ref string err);
    }

    public class ExchangeCfg {
        public bool Enabled { get; set; } = true;
        public string Market { get; set; }
        public string Type { get; set; } // Future, Option
        public ISet<string> Contracts { get; } = new HashSet<string>();
    }
}
