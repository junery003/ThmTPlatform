//-----------------------------------------------------------------------------
// File Name   : MarketDepthData
// Author      : junlei
// Date        : 2/5/2020 11:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Linq;

namespace ThmCommon.Models {
    /// <summary>
    /// MarketDepthData
    /// </summary>
    public sealed class MarketDepthData {
        public const int MaxLevel = 5;

        public string ID => Exchange + ProductType + InstrumentID + Provider;

        public EProviderType Provider { get; set; }
        public string Exchange { get; set; }
        public string ProductType { get; set; } = "Future";
        public string Product { get; set; }
        public string Contract { get; set; }
        public string InstrumentID { get; set; }

        public DateTime DateTime { get; set; } // exchange datetime
        public DateTime LocalDateTime { get; set; }

        public decimal DirectAskPrice { get; set; }  // top level 0
        public int DirectAskQty { get; set; }
        //public long DirectAskCount { get; set; }
        //public long DirectBidCount { get; set; }
        public decimal DirectBidPrice { get; set; }
        public int DirectBidQty { get; set; }
        //public double DirectAskCounterparty { get; set; }
        //public double DirectBidCounterparty { get; set; }

        public decimal OpenPrice { get; set; }
        public decimal ClosePrice { get; set; }
        public decimal HighPrice { get; set; }
        public decimal LowPrice { get; set; }
        public decimal LastTradedPrice { get; set; }
        //public int LastTradedQuantity { get; set; }
        public decimal SettlementPrice { get; set; }
        public int TotalTradedQuantity { get; set; }

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

        public (decimal, int) GetBestPriceQty(EBuySell buySell) {
            return GetPriceQtyByLevel(1, buySell);
        }

        public (decimal, int) GetPriceQtyByLevel(int level, EBuySell buySell = EBuySell.Buy) {
            if (buySell == EBuySell.Buy) {
                switch (level) {
                    case 1:
                        return (BidPrice1, BidQty1);
                    case 2:
                        return (BidPrice2, BidQty2);
                    case 3:
                        return (BidPrice3, BidQty3);
                    case 4:
                        return (BidPrice4, BidQty4);
                    case 5:
                        return (BidPrice5, BidQty5);
                }
            }
            else if (buySell == EBuySell.Sell) {
                switch (level) {
                    case 1:
                        return (AskPrice1, AskQty1);
                    case 2:
                        return (AskPrice2, AskQty2);
                    case 3:
                        return (AskPrice3, AskQty3);
                    case 4:
                        return (AskPrice4, AskQty4);
                    case 5:
                        return (AskPrice5, AskQty5);
                }
            }

            throw new Exception("Not supported.");
        }

        public void SetPriceQtyByLevel(decimal price, int qty, int level, EBuySell buySell = EBuySell.Buy) {
            if (buySell == EBuySell.Buy) {
                switch (level) {
                    case 1:
                        (BidPrice1, BidQty1) = (price, qty);
                        return;
                    case 2:
                        (BidPrice2, BidQty2) = (price, qty);
                        return;
                    case 3:
                        (BidPrice3, BidQty3) = (price, qty);
                        return;
                    case 4:
                        (BidPrice4, BidQty4) = (price, qty);
                        return;
                    case 5:
                        (BidPrice5, BidQty5) = (price, qty);
                        return;
                }
            }
            else if (buySell == EBuySell.Sell) { // offer
                switch (level) {
                    case 1:
                        (AskPrice1, AskQty1) = (price, qty);
                        return;
                    case 2:
                        (AskPrice2, AskQty2) = (price, qty);
                        return;
                    case 3:
                        (AskPrice3, AskQty3) = (price, qty);
                        return;
                    case 4:
                        (AskPrice4, AskQty4) = (price, qty);
                        return;
                    case 5:
                        (AskPrice5, AskQty5) = (price, qty);
                        return;
                }
            }

            throw new Exception("Not supported.");
        }

        public void UpdateDepthData(MarketDepthData md) {
            (AskPrice1, AskQty1) = (md.AskPrice1, md.AskQty1);
            (AskPrice2, AskQty2) = (md.AskPrice2, md.AskQty2);
            (AskPrice3, AskQty3) = (md.AskPrice3, md.AskQty3);
            (AskPrice4, AskQty4) = (md.AskPrice4, md.AskQty4);
            (AskPrice5, AskQty5) = (md.AskPrice5, md.AskQty5);

            (BidPrice1, BidQty1) = (md.BidPrice1, md.BidQty1);
            (BidPrice2, BidQty2) = (md.BidPrice2, md.BidQty2);
            (BidPrice3, BidQty3) = (md.BidPrice3, md.BidQty3);
            (BidPrice4, BidQty4) = (md.BidPrice4, md.BidQty4);
            (BidPrice5, BidQty5) = (md.BidPrice5, md.BidQty5);
        }

        private readonly BestQuot _curBestQuot = new BestQuot();
        public BestQuot CurBestQuot {
            get {
                (_curBestQuot.AskPrice1, _curBestQuot.AskQty1, _curBestQuot.BidPrice1, _curBestQuot.BidQty1)
                    = (AskPrice1, AskQty1, BidPrice1, BidQty1);

                return _curBestQuot;
            }
        }

        //Turn depthdata vertical prices to horizontal
        //bid prices, ask quantities, ask prices, bid quantites
        public static List<Tuple<double, int, int>> GetBidsAndAsks(MarketDepthData depthdata, double tickSize) {
            List<double> all_prices = TransposePrices(depthdata);
            List<Tuple<double, int, int>> returnObj = new List<Tuple<double, int, int>>();

            List<double> generated_prices = new List<double>();
            double lowest = all_prices.Min();
            generated_prices.Add(lowest);
            while (generated_prices.Max() < all_prices.Max()) {
                lowest += tickSize;
                generated_prices.Add(lowest);
            }

            foreach (var p in generated_prices) {
                int bidSize = 0;
                int askSize = 0;
                /*
                if (p == depthdata.bid1) {
                    bidSize = depthdata.bv1;
                }
                else if (p == depthdata.bid2) {
                    bidSize = depthdata.bv2;
                }
                else if (p == depthdata.bid3) {
                    bidSize = depthdata.bv3;
                }
                else if (p == depthdata.bid4) {
                    bidSize = depthdata.bv4;
                }
                else if (p == depthdata.bid5) {
                    bidSize = depthdata.bv5;
                }
                if (p == depthdata.ask1) {
                    askSize = depthdata.av1;
                }
                else if (p == depthdata.ask2) {
                    askSize = depthdata.av2;
                }
                else if (p == depthdata.ask3) {
                    askSize = depthdata.av3;
                }
                else if (p == depthdata.ask4) {
                    askSize = depthdata.av4;
                }
                else if (p == depthdata.ask5) {
                    askSize = depthdata.av5;
                }
                */

                returnObj.Add(Tuple.Create(p, bidSize, askSize));
            }

            return returnObj;
        }

        public static List<double> TransposePrices(MarketDepthData data) {
            var prices = new List<double>();
            //data.Levels.ForEach(x => prices.Add(x.BidPrice));
            //data.Levels.ForEach(x => prices.Add(x.AskPrice));

            return prices;
        }
    };

    public class BestQuot {
        public decimal AskPrice1 { get; set; }
        public decimal BidPrice1 { get; set; }
        public int AskQty1 { get; set; }
        public int BidQty1 { get; set; }
    };
}
