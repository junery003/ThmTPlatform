//-----------------------------------------------------------------------------
// File Name   : AlgoData
// Author      : junlei
// Date        : 3/9/2020 4:03:26 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using ThmCommon.Utilities;

namespace ThmCommon.Models {
    public sealed class AlgoData {
        public EProviderType Provider { get; set; } //ATP, TT
        public string Exchange { get; set; } //CME, SGX, etc.
        public string Product { get; set; } //i.e. contract, instrument
        public string ProductType { get; set; } //FUT etc
        public string Contract { get; set; }
        public string InstrumentID { get; set; } // Instrument alias: Given full provider ID already e.g. FEF1905-SGX
        public string Account { get; set; }

        public string AlgoID { get; }
        public EAlgoType Type { get; }
        public EBuySell BuyOrSell { get; set; }
        public string Status { get; set; }
        public decimal Price { get; set; }
        public int Qty { get; set; }
        public int FillQty { get; set; }
        public DateTime DateTime { get; set; } // TradeDateTime
        public DateTime LocalDateTime { get; set; }

        #region Trigger
        public EPriceType? TriggerPriceType { get; set; }
        public EOperator? TriggerOperator { get; set; }
        public int? TriggerQty { get; set; }
        public decimal? TriggerPrice { get; set; }

        #region Inter-Trigger
        public ThmInstrumentInfo RefInstrument { get; set; }
        #endregion

        #endregion

        public string Tag { get; set; }

        public AlgoData(EAlgoType type) {
            AlgoID = ThmUtil.GenerateGUID();
            Type = type;
        }

        public override int GetHashCode() {
            return AlgoID.GetHashCode();
        }

        public override bool Equals(object obj) {
            return Equals(obj as AlgoData);
        }

        public bool Equals(AlgoData para) {
            return para != null && para.AlgoID == AlgoID;
        }
    }
}
