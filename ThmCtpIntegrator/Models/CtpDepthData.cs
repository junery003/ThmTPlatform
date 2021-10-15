//-----------------------------------------------------------------------------
// File Name   : CtpDepthData
// Author      : junlei
// Date        : 8/26/2021 11:02:26 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using ThmCommon.Models;

namespace ThmCtpIntegrator.Models {
    public sealed class CtpDepthData {
        public CtpDepthData(string instrumentID) {
            InstrumentID = instrumentID;
            (Product, Contract) = CtpFunctions.CtpUtil.ExtractContract(instrumentID);
        }

        public EProviderType Provider { get; } = EProviderType.CTP; // "CTP";

        //[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 9)]
        public string Exchange { get; private set; }
        public string Product { get; private set; }
        public string Contract { get; private set; }
        public string InstrumentID { get; private set; }

        public string DateTime { get; set; }  // Exchange datetime
        public long LocalDateTime { get; set; } // millisecond

        public double HighPrice { get; set; }
        public double LowPrice { get; set; }
        public double OpenPrice { get; set; }
        public int Volume { get; set; } // total trade qty
        public double LastPrice { get; set; }
        public double SettlementPrice { get; set; }

        public double PreOpenInterest { get; set; }
        public double OpenInterest { get; set; }
        public double Turnover { get; set; }
        public int LastTradeQty { get; set; }

        public double DirectBidPrice { get; set; }
        public double DirectAskPrice { get; set; }
        public int DirectBidQty { get; set; }
        public int DirectAskQty { get; set; }

        public double BidPrice1 { get; set; }
        public double BidPrice2 { get; set; }
        public double BidPrice3 { get; set; }
        public double BidPrice4 { get; set; }
        public double BidPrice5 { get; set; }
        public int BidQty1 { get; set; }
        public int BidQty2 { get; set; }
        public int BidQty3 { get; set; }
        public int BidQty4 { get; set; }
        public int BidQty5 { get; set; }

        public double AskPrice1 { get; set; }
        public double AskPrice2 { get; set; }
        public double AskPrice3 { get; set; }
        public double AskPrice4 { get; set; }
        public double AskPrice5 { get; set; }
        public int AskQty1 { get; set; }
        public int AskQty2 { get; set; }
        public int AskQty3 { get; set; }
        public int AskQty4 { get; set; }
        public int AskQty5 { get; set; }
    }
}
