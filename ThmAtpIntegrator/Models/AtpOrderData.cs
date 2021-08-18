//-----------------------------------------------------------------------------
// File Name   : AtpOrderData
// Author      : junlei
// Date        : 1/22/2020 5:03:18 PM
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
    public sealed class AtpOrderData {
        public string ID => $"{Exchange}|{OrderID}|{OrderRef}";

        public EProviderType Provider { get; } = EProviderType.ATP; //"ATP";
        public AtpOrderData(string instrumentID) {
            InstrumentID = instrumentID;
            (Exchange, Product, Contract) = AtpFunctions.AtpUtil.ExtractContract(instrumentID);
        }

        public string BrokerID { set; get; }
        public string Account { get; set; }

        public string Exchange { get; private set; }
        public string Product { get; private set; }
        public string Contract { get; private set; }

        public string InstrumentID { get; private set; }  //FOR ATP, FEF1903-SGX

        public string OrderID { set; get; }
        public string OrderRef { get; set; }
        public string BuyOrSell { get; set; } // Direction: 0: buy; 1: sell

        public string DateTime { get; set; } // Trade datetime
        public string LocalDateTime { get; set; }

        public double LimitPrice { get; set; }
        public int FillQty { get; set; }
        public int TotalOrderQty { get; set; }

        public string OrderType { get; set; }
        public string OrderStatus { get; set; }

        public string OrderTag { get; set; }
        public string Text { get; set; }

        //[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 31)]
        //public string prodType;

        //[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 31)]
        //public string orderType;
        ////order type? LMT, STOP, MKT

        //[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 31)]
        //public string tif;

        //[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 31)]
        //public string orderPurpose;

        //[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 31)]
        //public string month;

        //THOST_FTDC_OST_AllTraded              '0'  All traded.
        //THOST_FTDC_OST_PartTradedQueueing     '1'  Partial trade and still queueing.
        //THOST_FTDC_OST_PartTradedNotQueueing  '2'  Partial trade and not in the queue.
        //THOST_FTDC_OST_NoTradeQueueing        '3'  No trade and still queueing.
        //THOST_FTDC_OST_NoTradeNotQueueing     '4'  No trade and not in the queue.
        //THOST_FTDC_OST_Canceled               '5'  Order canceled.
        //THOST_FTDC_OST_Unknown                'a'  Unknown.
        //THOST_FTDC_OST_NotTouched             'b'  Not touched.
        //THOST_FTDC_OST_Touched                'c'  Touched.
        private string ToUniversalStatus() {
            switch (OrderStatus) {
                case "0":
                    return "F"; //fully filled
                case "1":
                    return "U"; //partial trade and still queuing
                case "2":
                    return "U"; //partial trade, no longer queuing
                case "3":
                    return "A"; //queuing (no trade and still queuing)
                case "4":
                    return "A"; //accepted (no trade and not in queue)
                case "5":
                    return "D"; //cancel
                case "a":
                    return "Q"; //unknown
                case "b":
                    return "T"; //unknown
                case "c":
                    return "T"; //unknown
                case "A":
                    return "Q"; //Rejected
                case "36":
                    return "T"; //Trade response
                default:
                    return "Q"; //unknown
            }
        }

        internal EBuySell GetDirection() {
            if (BuyOrSell == "0") {
                return EBuySell.Buy;
            }
            else if (BuyOrSell == "1") {
                return EBuySell.Sell;
            }

            return EBuySell.Unknown;
        }

        /* //e.g. FEF1903-SGX;
        public string ToInstrumentID() {
            if (Contract != null) {
                return Contract;
            }
            else {
                return Product + MaturityOrExpiry + "-" + ExchangeID;
            }
        } */
    }
}
