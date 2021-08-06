using System;
using ThmAtpIntegrator.Models;

namespace ThmAtpIntegrator.AtpFunctions {
    public class DepthCalc {
        //Returns the weighted price, weightQty, and at which level of depth to reach the intended quantity (for Ordering purposes)
        public static Tuple<decimal, int, int> WeightedBidOrAsk(AtpDepthData dataObj, int weightQty, bool isBid, int roundSigFig) {
            if (weightQty == 0) {
                decimal ret_price = isBid == true ? dataObj.BidPrice1 : dataObj.AskPrice1;
                int ret_size = isBid == true ? dataObj.BidQty1 : dataObj.AskQty1;
                return Tuple.Create(Math.Round(ret_price, roundSigFig), ret_size, 1);
            }

            int qty_summation = 0;

            int total_bid_size = dataObj.BidQty1 + dataObj.BidQty2 + dataObj.BidQty3 + dataObj.BidQty4 + dataObj.BidQty5; // + dataObj.bv6 + dataObj.bv7 + dataObj.bv8 + dataObj.bv9 + dataObj.bv10;
            int total_ask_size = dataObj.AskQty1 + dataObj.AskQty2 + dataObj.AskQty3 + dataObj.AskQty4 + dataObj.AskQty5; // + dataObj.av6 + dataObj.av7 + dataObj.av8 + dataObj.av9 + dataObj.av10;

            int to_check = isBid == true ? total_bid_size : total_ask_size;

            if (to_check < weightQty) {
                weightQty = to_check;
            }

            decimal summation = 0M;

            int size = 0;
            decimal price;
            int count = 1;
            int qty_remaining = weightQty;


            while (qty_summation < weightQty && count < 11) {
                switch (count) {
                    case 1:
                        size = isBid == true ? dataObj.BidQty1 : dataObj.AskQty1;

                        price = isBid == true ? dataObj.BidPrice1 : dataObj.AskPrice1;
                        qty_summation += size;

                        if (size > qty_remaining) {
                            size = qty_remaining;
                        }


                        summation += (price * size);
                        break;

                    case 2:
                        size = isBid == true ? dataObj.BidQty2 : dataObj.AskQty2;
                        price = isBid == true ? dataObj.BidPrice2 : dataObj.AskPrice2;
                        qty_summation += size;
                        if (size > qty_remaining) {
                            size = qty_remaining;
                        }

                        summation += (price * size);
                        break;

                    case 3:
                        size = isBid == true ? dataObj.BidQty3 : dataObj.AskQty3;
                        price = isBid == true ? dataObj.BidPrice3 : dataObj.AskPrice3;
                        qty_summation += size;
                        if (size > qty_remaining) {
                            size = qty_remaining;
                        }

                        summation += (price * size);
                        break;

                    case 4:
                        size = isBid == true ? dataObj.BidQty4 : dataObj.AskQty4;
                        price = isBid == true ? dataObj.BidPrice4 : dataObj.AskPrice4;
                        qty_summation += size;
                        if (size > qty_remaining) {
                            size = qty_remaining;
                        }

                        summation += (price * size);
                        break;

                    case 5:
                        size = isBid == true ? dataObj.BidQty5 : dataObj.AskQty5;
                        price = isBid == true ? dataObj.BidPrice5 : dataObj.AskPrice5;
                        qty_summation += size;
                        if (size > qty_remaining) {
                            size = qty_remaining;
                        }

                        summation += (price * size);
                        break;
                    /*
                    case 6:
                        size = isBid == true ? dataObj.bv6 : dataObj.av6;
                        price = isBid == true ? dataObj.bid6 : dataObj.ask6;
                        qty_summation += size;
                        if (size > qty_remaining)
                        {
                            size = qty_remaining;
                        }

                        summation += (price * size); break;

                    case 7:
                        size = isBid == true ? dataObj.bv7 : dataObj.av7;
                        price = isBid == true ? dataObj.bid7 : dataObj.ask7;
                        qty_summation += size;
                        if (size > qty_remaining)
                        {
                            size = qty_remaining;
                        }

                        summation += (price * size); break;

                    case 8:
                        size = isBid == true ? dataObj.bv8 : dataObj.av8;
                        price = isBid == true ? dataObj.bid8 : dataObj.ask8;
                        qty_summation += size;
                        if (size > qty_remaining)
                        {
                            size = qty_remaining;
                        }

                        summation += (price * size); break;

                    case 9:
                        size = isBid == true ? dataObj.bv9 : dataObj.av9;
                        price = isBid == true ? dataObj.bid9 : dataObj.ask9;
                        if (size > qty_remaining)
                        {
                            size = qty_remaining;
                        }

                        summation += (price * size); break;

                    case 10:
                        size = isBid == true ? dataObj.bv10 : dataObj.av10;
                        price = isBid == true ? dataObj.bid10 : dataObj.ask10;
                        qty_summation += size;
                        if (size > qty_remaining)
                        {
                            size = qty_remaining;
                        }

                        summation += (price * size);
                        break;
                        */
                    default:
                        break;
                }

                qty_remaining -= size;
                count++;
            }

            return Tuple.Create(Math.Round(summation / weightQty, roundSigFig), weightQty, count - 1);
        }
    }
}
