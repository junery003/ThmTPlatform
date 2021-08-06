//-----------------------------------------------------------------------------
// File Name   : TitanOrderData
// Author      : junlei
// Date        : 11/24/2020 2:05:03 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using ThmCommon.Models;

namespace ThmTitanIntegrator.Models {
    internal class TitanOrderData {
        //id: {Side}|{OrderID} or OrderToken
        public TitanOrderData(string symbol) {
            Product = symbol.Substring(0, symbol.Length - 3); // "FEF"
            Contract = symbol;
            InstrumentID = symbol;  // "FEFH21"            
        }

        public string Provider { get; } = "Titan";
        public string Exchange { get; } = "SGX";
        public string ProductType { get; private set; } = "Future";
        public string Product { get; private set; }
        public string Contract { get; private set; }
        public string InstrumentID { get; set; } // Symbol

        public string BrokerID { set; get; }
        public string Account { get; set; }

        public char Side { get; set; } // Direction: B: buy; S: sell
        public string OrderID { set; get; }
        public string OrderToken { get; set; } // Order Token

        public string DateTime { get; set; } // exchange datetime
        public string LocalDateTime { get; set; }

        public decimal Price { get; set; }
        public int Qty { get; set; }
        public int TradedQty { get; set; }  // current traded Qty
        public int FillQty { get; set; } // not supported

        public string TIF { get; set; }
        public string OrderType { get; set; }
        public string Status { get; set; }

        public string OrderTag { get; set; }
        public string Text { get; set; }

        internal EBuySell GetDirection() {
            return Side == 1 ? EBuySell.Buy : Side == 2 ? EBuySell.Sell : EBuySell.Unknown;
        }
    }
}
