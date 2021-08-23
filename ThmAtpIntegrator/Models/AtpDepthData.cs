//-----------------------------------------------------------------------------
// File Name   : AtpDepthData
// Author      : junlei
// Date        : 1/26/2020 11:02:26 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using ThmCommon.Models;

namespace ThmAtpIntegrator.Models {
    [Serializable]
    //[StructLayout(LayoutKind.Sequential, Pack = 1)]
    public sealed class AtpDepthData {
        public AtpDepthData(string instrumentID) {
            InstrumentID = instrumentID;
            (Exchange, Product, Contract) = AtpFunctions.AtpUtil.ExtractContract(instrumentID);
        }

        public EProviderType Provider { get; } = EProviderType.ATP;

        //[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 9)]
        public string Exchange { get; private set; }
        public string Product { get; private set; }
        public string Contract { get; private set; }
        public string InstrumentID { get; private set; }

        public string DateTime { get; set; }  // Exchange datetime
        public long LocalDateTime { get; set; } // millisecond

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

        //public decimal BestBidPrice { get; set; }
        //public decimal BestAskPrice { get; set; }
        //public int BestBidQty { get; set; }
        //public int BestAskQty { get; set; }

        //public double impliedBidPrice { get; set; }
        //public double impliedAskPrice { get; set; }
        //public int impliedBidQty { get; set; }
        //public int impliedAskQty { get; set; }

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
