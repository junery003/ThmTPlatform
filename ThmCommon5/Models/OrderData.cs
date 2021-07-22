//-----------------------------------------------------------------------------
// File Name   : OrderData
// Author      : junlei
// Date        : 3/5/2020 9:29:28 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;

namespace ThmCommon.Models {
    [Serializable]
    public sealed class OrderData {
        //eg. for ATP: $"{Exchange}|{OrderID}|{OrderRef}";
        public string ID { get; private set; }

        public string Provider { get; set; } //ATP, TT, etc.
        public string Exchange { get; set; } //CME, SGX, etc.
        public string ProductType { get; set; } //FUT etc
        public string Product { get; set; } //        
        public string Contract { get; set; }
        public string InstrumentID { get; set; } // Instrument alias: Given full provider ID already e.g. FEF1905-SGX

        public string Account { get; set; }

        // the algo ID is IsAlgo==true; else order ID
        public string OrderID { get; set; }
        public string Type { get; set; }
        public EOrderStatus Status { get; set; }
        public string OrderRef { get; set; }

        public EBuySell BuyOrSell { get; set; }
        public int Qty { get; set; }
        public int FillQty { get; set; }
        public DateTime DateTime { get; set; } // TradeDateTime
        public DateTime LocalDateTime { get; set; }

        public decimal EntryPrice { get; set; }
        public decimal AverageFillPrice { get; set; }

        //public string MaturityOrExpiry { get; set; } //Mar19
        //public double Strike { get; set; } //-1 or 155.5 etc

        public int? TriggerQty { get; set; }
        public decimal? TriggerPrice { get; set; }

        public string Tag { get; set; }
        public string Text { get; set; } // eg. CustomizedAlgoName, OrderPurpose, Outright, Leg, Bracket
        public string TIF { get; set; }

        public bool IsAlgo { get; }
        //public List<OrderData> AttachedOrders { get; private set; } //as part of a leg or bracket order

        public OrderData(string id, bool isAlgo = false) {
            ID = id;
            IsAlgo = isAlgo;
        }

        public OrderData(AlgoData algo) {
            IsAlgo = true;
            ID = algo.AlgoID;

            Provider = algo.Provider;
            Product = algo.Product;
            Exchange = algo.ExchangeID;
            InstrumentID = algo.InstrumentID;
            Contract = algo.Contract;

            OrderID = algo.AlgoID; // algo ID
            Account = algo.Account;
            BuyOrSell = algo.BuyOrSell;

            Status = EOrderStatus.New;
            EntryPrice = algo.Price;
            Qty = algo.Qty;

            TriggerPrice = algo?.TriggerPrice;
            TriggerQty = algo?.TriggerQty;

            Tag = algo.Type.ToString();

            LocalDateTime = algo.LocalDateTime;
            DateTime = algo.DateTime;
        }
    }
}
