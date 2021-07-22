//-----------------------------------------------------------------------------
// File Name   : TimeSalesData
// Author      : junlei
// Date        : 2/5/2020 11:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;

namespace ThmCommon.Models {
    /// <summary>
    /// TimeSalesData
    /// </summary>
    public sealed class TimeSalesData {
        public string Provider { get; set; }  // ATP/TT etc.
        public string Exchange { get; set; }  // SGX, etc.
        public string ProductType { get; set; }
        public string Product { get; set; }
        public string Contract { get; set; }
        public string InstrumentId { get; set; }

        public DateTime ExchangeDateTime { get; set; }
        public DateTime LocalTime { get; set; }

        public EBuySell BuySell { get; set; }
        public decimal Price { get; set; }
        public int Qty { get; set; }

        //public int OrderBookId { get; set; }
        //public int OrderId { get; set; }

        //public int MatchId { get; set; }
        //public int ComboGroupId { get; set; }
        //public int Side { get; set; }
        //public int DealType { get; set; }
        //public int TradeCondition { get; set; }
        //public DateTime TadeTime { get; set; }
    }
}
