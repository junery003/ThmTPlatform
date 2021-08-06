//-----------------------------------------------------------------------------
// File Name   : MonitorMM
// Author      : junlei
// Date        : 5/19/2020 4:15:03 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;

namespace ThmTTIntegrator.TTHandler {
    public class MonitorMM {
        public string Product { get; set; }
        public string Contract { get; set; }
        public TimeSpan StartTime { get; set; } // "08:00:00"
        public TimeSpan EndTime { get; set; }
        public decimal BidAskSpread { get; set; }
        public int BidQty { get; set; }
        public int AskQty { get; set; }
    }
}
