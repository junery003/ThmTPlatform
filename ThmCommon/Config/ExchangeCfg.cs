//-----------------------------------------------------------------------------
// File Name   : ExchangeCfg
// Author      : junlei
// Date        : 2/26/2020 5:03:30 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Collections.Generic;

namespace ThmCommon.Config {
    /// <summary>
    /// exchange config
    /// </summary>
    public class ExchangeCfg {
        public bool Enabled { get; set; } = true;
        public string Market { get; set; }
        public string Type { get; set; } // Future, Option
        public ISet<string> Contracts { get; } = new HashSet<string>();
    }
}
