//-----------------------------------------------------------------------------
// File Name   : ThmInstrumentInfo
// Author      : junlei
// Date        : 12/28/2020 9:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

using System.Collections.Generic;

namespace ThmCommon.Models {
    public sealed class ThmInstrumentInfo {
        public string ID => Exchange + ProductType + InstrumentID + Provider;

        public EProviderType Provider { get; set; } = EProviderType.TITAN; // Provider;
        public string Exchange { get; set; } = "SGX"; // market
        public string ProductType { get; set; } = "Future"; // "Option",  "Future", ..., "Synthetic"
        public string Product { get; set; }  // FEF
        public string Contract { get; set; } // Jan21
        public string InstrumentID { get; set; } // symbol: eg. "FEF Jan21", "FEFH21"

        public decimal TickSize { get; set; } = decimal.Zero;

        public List<string> Accounts { get; set; } = new List<string>();
        public string CurAccount { get; set; }

        public override bool Equals(object obj) {
            if (obj == null) {
                return false;
            }

            var o = obj as ThmInstrumentInfo;
            if (o == null) {
                return false;
            }

            return ID == o.ID;
        }

        public override int GetHashCode() {
            return ID.GetHashCode();
        }
    }

    public enum EProviderType {
        Unknown = 0,
        ATP = 1,
        TT = 2,
        TITAN = 3,
        CTP = 4
    };
}
