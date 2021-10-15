//-----------------------------------------------------------------------------
// File Name   : CtpTradeHandler
// Author      : junlei
// Date        : 8/27/2020 3:38:47 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using ThmCommon.Handlers;
using ThmCommon.Models;
using ThmCommon.Utilities;
using ThmCtpIntegrator.Models;

namespace ThmCtpIntegrator.CtpHandler {
    public class CtpTradeHandler : TradeHandlerBase {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private int _position = 0;
        public CtpTradeHandler(CtpInstrumentHandler instrumentHandler) : base(instrumentHandler) {
        }

        public override void SetAccount(string accountID) {
            DllHelper.SetAccount(accountID);
            Logger.Info("Set account ID {}", accountID);
        }

        public override int GetPosition() {
            return _position;
        }

        public override void SendNewOrder(EBuySell buySell, decimal price, int qty, string tag, ETIF tif = ETIF.Day) {
            DllHelper.SendOrder(InstrumentHandler.InstrumentInfo.InstrumentID,
                buySell == EBuySell.Buy,
                (double)price, qty,
                tag,
                FormatTIF(tif));
            Logger.Info($"Adding order {InstrumentHandler.InstrumentInfo.InstrumentID}: {buySell} {qty}@{price}");
        }

        public override void SendUpdateOrder(string orderID, decimal price, int qty) {
            DllHelper.ModifyOrder(InstrumentHandler.InstrumentInfo.Exchange, orderID, (double)price, qty);
            Logger.Info($"Updating order {InstrumentHandler.InstrumentInfo.InstrumentID}: {orderID}");
        }

        public override void SendDeleteOrder(string orderID, bool isBuy) {
            DllHelper.CancelOrder(InstrumentHandler.InstrumentInfo.Exchange, orderID);
            Logger.Info($"Canceling order {InstrumentHandler.InstrumentInfo.InstrumentID}: {orderID}");
        }

        internal OrderData BuildOrderData(CtpOrderData orderMsg) {
            string id = orderMsg.Exchange + orderMsg.OrderID + orderMsg.OrderRef;
            OrderData orderData;
            if (string.IsNullOrWhiteSpace(orderMsg.OrderID) || orderMsg.OrderStatus.StartsWith(EOrderStatus.Failed.ToString())) {
                orderData = new OrderData(id) {
                    Provider = orderMsg.Provider,  // "CTP"
                    Exchange = orderMsg.Exchange,
                    Product = orderMsg.Product,
                    Contract = orderMsg.Contract,
                    InstrumentID = orderMsg.InstrumentID,
                    Account = orderMsg.Account,

                    OrderID = orderMsg.OrderID,
                    OrderRef = orderMsg.OrderRef,
                    DateTime = TimeUtil.String2DateTime(orderMsg.DateTime),
                    LocalDateTime = DateTime.Now, //orderMsg.Time,

                    //orderData.MaturityOrExpiry = orderMsg.Month;
                    //orderData.Strike = orderMsg.strike;
                    BuyOrSell = orderMsg.GetDirection(),
                    Qty = orderMsg.TotalOrderQty,
                    EntryPrice = (decimal)orderMsg.LimitPrice,
                    FillQty = orderMsg.FillQty,

                    Type = orderMsg.OrderType,

                    Status = FormatOrderStatus(orderMsg.OrderStatus),
                    //orderData.Tif = orderMsg.tif,

                    Tag = orderMsg.OrderTag,
                    Text = orderMsg.Text
                };
            }
            else {
                orderData = GetOrder(id);
                if (orderData == null) {
                    orderData = new OrderData(id) {
                        Provider = orderMsg.Provider,  // "CTP"
                        Exchange = orderMsg.Exchange,
                        Product = orderMsg.Product,
                        //ProductType = _instrument.Product.Type.ToString(), // orderMsg.prodType,
                        Contract = orderMsg.Contract,
                        InstrumentID = orderMsg.InstrumentID,

                        Account = orderMsg.Account,

                        OrderID = orderMsg.OrderID,
                        OrderRef = orderMsg.OrderRef,
                    };

                    AddOrder(orderData);
                }

                orderData.DateTime = TimeUtil.String2DateTime(orderMsg.DateTime);
                orderData.LocalDateTime = DateTime.Now;  //orderMsg.Time;

                //orderData.MaturityOrExpiry = orderMsg.Month;
                //orderData.Strike = orderMsg.strike;
                orderData.BuyOrSell = orderMsg.GetDirection();
                orderData.Qty = orderMsg.TotalOrderQty;
                orderData.EntryPrice = (decimal)orderMsg.LimitPrice;
                orderData.FillQty = orderMsg.FillQty;

                orderData.Type = orderMsg.OrderType;

                orderData.Status = FormatOrderStatus(orderMsg.OrderStatus);
                //orderData.Tif = orderMsg.tif;

                orderData.Tag = orderMsg.OrderTag;
                orderData.Text = orderMsg.Text;
            }

            //_position += orderData.BuyOrSell == EBuySell.Buy ? orderMsg.FillQty : -orderMsg.FillQty;

            return orderData;
        }

        //Status = (EOrderStatus)Enum.Parse(typeof(EOrderStatus), orderMsg.OrderStatus, true);
        private EOrderStatus FormatOrderStatus(string orderStatus) {
            switch (orderStatus.ToLower()) {
                case "new":
                    return EOrderStatus.New;
                case "pending":
                    return EOrderStatus.Pending;
                case "canceled":
                    return EOrderStatus.Canceled;
                case "filled":
                    return EOrderStatus.Filled;
                case "partiallyfilled":
                    return EOrderStatus.PartiallyFilled;
                case "failed":
                    return EOrderStatus.Failed;
                case "rejected":
                    return EOrderStatus.Rejected;
                case "unknown":
                default:
                    return EOrderStatus.Unknown;
            }
        }

        // not used by CTP
        private static int FormatTIF(ETIF tif) {
            switch (tif) {
                case ETIF.Day:
                default:
                    return 0;
            }
        }
    }
}
