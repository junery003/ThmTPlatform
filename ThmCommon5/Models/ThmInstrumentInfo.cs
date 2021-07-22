//-----------------------------------------------------------------------------
// File Name   : ThmInstrumentInfo
// Author      : junlei
// Date        : 12/28/2020 9:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

namespace ThmCommon.Models {
    public sealed class ThmInstrumentInfo {
        public string Provider { get; set; } = "TTP"; // Provider;
        public string Exchange { get; set; } = "TTP"; // market
        public string Type { get; set; } = "Future"; // "Option",  "Future", ..., "Synthetic"
        public string Product { get; set; }  // FEF
        public string Contract { get; set; } // Jan21
        public string InstrumentID { get; set; } // symbol: eg. "FEF Jan21", "FEFH21"
        public decimal TickSize { get; set; } = decimal.Zero;

        public override bool Equals(object obj) {
            if (obj == null || !GetType().Equals(obj.GetType())) {
                return false;
            }

            var o = (ThmInstrumentInfo)obj;
            return Exchange == o.Exchange && Type == o.Type && InstrumentID == o.InstrumentID;
        }

        public override int GetHashCode() {
            return (Exchange.GetHashCode() << 2) ^ (InstrumentID.GetHashCode());
        }
    }
}
