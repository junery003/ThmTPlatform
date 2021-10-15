//-----------------------------------------------------------------------------
// File Name   : CtpInstrumentInfo
// Author      : junlei
// Date        : 8/31/2021 9:30:11 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

namespace ThmCtpIntegrator.Models {
    /// <summary>
    /// Query instrument info from API
    /// </summary>
    internal class CtpInstrumentInfo {
        public string Exchange { get; set; }
        public string InstrumentID { get; set; }
        public decimal PriceTick { get; set; }
        public decimal PriceFrom { get; set; }
        public decimal PriceTo { get; set; }
    }
}
