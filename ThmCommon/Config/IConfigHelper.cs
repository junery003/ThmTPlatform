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
    public interface IConfigHelper {
        bool LoadConfig();
        IConfig GetConfig();
        void SaveConfig();
    }

    public interface IConfig {
        bool Enabled { get; set; }
        bool SaveData { get; set; }
        List<ExchangeCfg> Exchanges { get; }
        bool IsValid(ref string err);
    }

    public class ExchangeCfg {
        public bool Enabled { get; set; } = true;
        public string Market { get; set; }
        public string Type { get; set; } // Future, Option
        public List<ProductCfg> Products { get; } = new();
    }

    public class ProductCfg {
        public string Name { get; set; }
        public ISet<string> Contracts { get; } = new HashSet<string>();
    }
}
