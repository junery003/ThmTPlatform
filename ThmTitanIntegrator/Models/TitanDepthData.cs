//-----------------------------------------------------------------------------
// File Name   : TitanAlgoHandler
// Author      : junlei
// Date        : 11/24/2020 1:05:03 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

using ThmCommon.Models;

namespace ThmTitanIntegrator.Models {
    internal class TitanDepthData {
        public TitanDepthData(string symbol) {
            InstrumentID = symbol;
            Product = symbol.Substring(0, symbol.Length - 3); // "FEFH21"
            Contract = symbol;
        }

        public EProviderType Provider { get; } = EProviderType.TITAN;

        public string Exchange { get; private set; } = "SGX";
        public string ProductType { get; private set; } = "Future";
        public string Product { get; private set; }
        public string Contract { get; private set; } // == Symbol
        public string InstrumentID { get; set; } // Symbol

        public string DateTime { get; set; }
        public string LocalDateTime { get; set; } // nano-second

        public decimal HighPrice { get; set; }
        public decimal LowPrice { get; set; }
        public decimal OpenPrice { get; set; }
        public int Volume { get; set; } // total trade qty
        public decimal LastPrice { get; set; }
        public decimal SettlementPrice { get; set; }
        public double PreOpenInterest { get; set; }
        public double OpenInterest { get; set; }
        public double Turnover { get; set; }
        public int LastTradeQty { get; set; }

        public decimal DirectBidPrice { get; set; }
        public decimal DirectAskPrice { get; set; }
        public int DirectBidQty { get; set; }
        public int DirectAskQty { get; set; }

        public decimal BidPrice1 { get; set; }
        public decimal BidPrice2 { get; set; }
        public decimal BidPrice3 { get; set; }
        public decimal BidPrice4 { get; set; }
        public decimal BidPrice5 { get; set; }
        public int BidQty1 { get; set; }
        public int BidQty2 { get; set; }
        public int BidQty3 { get; set; }
        public int BidQty4 { get; set; }
        public int BidQty5 { get; set; }

        public decimal AskPrice1 { get; set; }
        public decimal AskPrice2 { get; set; }
        public decimal AskPrice3 { get; set; }
        public decimal AskPrice4 { get; set; }
        public decimal AskPrice5 { get; set; }
        public int AskQty1 { get; set; }
        public int AskQty2 { get; set; }
        public int AskQty3 { get; set; }
        public int AskQty4 { get; set; }
        public int AskQty5 { get; set; }
    }
}
