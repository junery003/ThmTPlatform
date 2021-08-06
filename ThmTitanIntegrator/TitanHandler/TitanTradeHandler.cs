//-----------------------------------------------------------------------------
// File Name   : TitanTradeHandler
// Author      : junlei
// Date        : 11/24/2020 12:02:26 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using ThmCommon.Handlers;
using ThmCommon.Models;
using ThmCommon.Utilities;
using ThmTitanIntegrator.Models;

namespace ThmTitanIntegrator.TitanHandler {
    internal class TitanTradeHandler : TradeHandlerBase {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private const string DT_FORMAT = "yyyy-MM-dd HH:mm:ss.fffffff";

        private int _position = 0;
        public TitanTradeHandler(InstrumentHandlerBase instrumentHandler) : base(instrumentHandler) {
        }

        internal OrderData BuildOrderData(TitanOrderData titanOrder) {
            // id :orderToken
            var id = titanOrder.OrderToken;
            var orderData = GetOrder(id);
            if (orderData == null) {
                orderData = new OrderData(id) {
                    Provider = titanOrder.Provider, // "Titan"
                    Exchange = titanOrder.Exchange,
                    ProductType = titanOrder.ProductType,
                    Product = titanOrder.Product,
                    Contract = titanOrder.Contract,
                    InstrumentID = titanOrder.InstrumentID,

                    Account = string.IsNullOrEmpty(titanOrder.Account) ? InstrumentHandler.CurAccount : titanOrder.Account,

                    BuyOrSell = titanOrder.GetDirection(),
                    OrderID = titanOrder.OrderID,
                    OrderRef = titanOrder.OrderToken,
                    TIF = titanOrder.TIF,
                    Type = titanOrder.OrderType,

                    EntryPrice = titanOrder.Price,
                    Qty = titanOrder.Qty,
                };

                AddOrder(orderData);
            }

            //"2021-03-11 03:18:16.617304484"
            orderData.DateTime = TimeUtil.String2DateTime(titanOrder.DateTime.Substring(0, DT_FORMAT.Length), DT_FORMAT);
            orderData.LocalDateTime = DateTime.Now;  //orderMsg.Time;

            //orderData.MaturityOrExpiry = orderMsg.Month;
            //orderData.Strike = orderMsg.strike;

            if (0 != decimal.Compare(titanOrder.Price, decimal.Zero)) {
                orderData.EntryPrice = titanOrder.Price;
            }

            if (titanOrder.Qty != 0) {
                orderData.Qty = titanOrder.Qty;
            }

            orderData.Status = (EOrderStatus)Enum.Parse(typeof(EOrderStatus), titanOrder.Status, true);
            if (orderData.Status == EOrderStatus.Filled) {
                //orderData.FillQty = titanOrder.FillQty;
                orderData.FillQty += titanOrder.TradedQty;

                switch (orderData.BuyOrSell) {
                case EBuySell.Buy:
                    _position += titanOrder.TradedQty;
                    break;
                case EBuySell.Sell:
                    _position -= titanOrder.TradedQty;
                    break;
                default:
                    Logger.Warn("BuySell Side not supported: {}", titanOrder.Side);
                    break;
                }

                //if (orderData.FillQty == orderData.Qty) {
                //    DeleteOrder(id);
                //}
            }
            else if (orderData.Status == EOrderStatus.Canceled) {
                DeleteOrder(id);
            }
            else {
                Logger.Info("Order status: {}", orderData.Status);
            }

            if (!string.IsNullOrEmpty(titanOrder.Account)) {
                orderData.Account = titanOrder.Account;
            }

            orderData.Tag = titanOrder.OrderTag;
            orderData.Text = titanOrder.Text;

            return orderData;
        }

        public override void SetAccount(string accountID) {
            DllHelper.SetAccount(accountID);
        }

        public override int GetPosition() {
            return _position;
        }

        public override void SendNewOrder(EBuySell buySell, decimal price, int qty, string tag, ETIF tif = ETIF.Day) {
            DllHelper.EnterOrder(InstrumentHandler.InstrumentInfo.InstrumentID,
                buySell == EBuySell.Buy,
                price, qty, FormatTIF(tif));
            Logger.Info("New order {}: {} {}@{}", InstrumentHandler.InstrumentInfo.InstrumentID, buySell, qty, price);
        }

        public override void SendUpdateOrder(string orderID, decimal price, int qty) {
            DllHelper.UpdateOrder(InstrumentHandler.InstrumentInfo.InstrumentID, orderID, (double)price, qty);
            Logger.Info("Update order {}: {}@{}", InstrumentHandler.InstrumentInfo.InstrumentID, orderID, qty, price);
        }

        public override void SendDeleteOrder(string orderID, bool isBuy) {
            DllHelper.CancelOrderByID(InstrumentHandler.InstrumentInfo.InstrumentID, isBuy, orderID);
            Logger.Info("Cancel order {}: {}-{}", InstrumentHandler.InstrumentInfo.InstrumentID, isBuy ? "B" : "S", orderID);
        }

        public void SendDeleteOrder(string orderToken) {
            DllHelper.CancelOrder(orderToken);
            Logger.Info("Cancel order {}: {}", InstrumentHandler.InstrumentInfo.InstrumentID, orderToken);
        }

        private static int FormatTIF(ETIF tif) {
            switch (tif) {
            case ETIF.Day:
                return 0;
            case ETIF.FAK:
                return 3;
            case ETIF.FOK:
                return 4;
            default:
                return 0;
            }
        }
    }
}
