//-----------------------------------------------------------------------------
// File Name   : AtpInstrumentInfo
// Author      : junlei
// Date        : 8/31/2020 9:30:11 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

namespace ThmAtpIntegrator.Models {
    /// <summary>
    /// Query instrument info from ATP API
    /// </summary>
    class AtpInstrumentInfo {
        public string Exchange { get; set; }
        public string InstrumentID { get; set; }
        public decimal PriceTick { get; set; }
        public decimal PriceFrom { get; set; }
        public decimal PriceTo { get; set; }
    }
}
