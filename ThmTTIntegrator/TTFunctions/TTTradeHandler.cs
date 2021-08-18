//-----------------------------------------------------------------------------
// File Name   : TTTradeHandler
// Author      : junlei
// Date        : 1/27/2020 4:07:07 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using ThmCommon.Handlers;
using ThmCommon.Models;
using tt_net_sdk;

namespace ThmTTIntegrator.TTFunctions {
    /// <summary>
    /// trading data:
    /// A trade subscription represents a view of a subset of a trader’s orders and fills.
    /// </summary>
    internal sealed class TTTradeHandler : TradeHandlerBase {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private readonly IReadOnlyList<Account> _ttAccounts;
        private readonly Instrument _ttInstrument;
        private readonly InstrumentTradeSubscription _instruTradeSubscription = null;

        private readonly Dictionary<string, Order> _ttOrders = new Dictionary<string, Order>();
        private Account _curAccount;

        public TTTradeHandler(InstrumentHandlerBase instrumentHandler,
            Instrument instrument,
            IReadOnlyList<Account> ttAccounts) : base(instrumentHandler) {
            _ttInstrument = instrument;
            _ttAccounts = ttAccounts;

            _instruTradeSubscription = new InstrumentTradeSubscription(Dispatcher.Current, _ttInstrument);
            _instruTradeSubscription.OrderAdded += InstrumentTradeSubscription_OrderAdded;
            _instruTradeSubscription.OrderUpdated += InstrumentTradeSubscription_OrderUpdated;
            _instruTradeSubscription.OrderDeleted += InstrumentTradeSubscription_OrderDeleted;
            _instruTradeSubscription.OrderFilled += InstrumentTradeSubscription_OrderFilled;
            _instruTradeSubscription.OrderRejected += InstrumentTradeSubscription_OrderRejected;
            _instruTradeSubscription.OrderBookDownload += InstrumentTradeSubscription_OrderBookDownload;
            _instruTradeSubscription.Start();

            /*
            var tradeSubscription = new TradeSubscription(Dispatcher.Current, false);
            tradeSubscription.OrderAdded += new EventHandler<OrderAddedEventArgs>(tradesubscription_OrderAdded);
            tradeSubscription.OrderDeleted += new EventHandler<OrderDeletedEventArgs>(tradesubscription_OrderDeleted);
            tradeSubscription.OrderFilled += new EventHandler<OrderFilledEventArgs>(tradesubscription_OrderFilled);
            tradeSubscription.OrderRejected += new EventHandler<OrderRejectedEventArgs>(tradesubscription_OrderRejected);
            tradeSubscription.OrderUpdated += new EventHandler<OrderUpdatedEventArgs>(tradesubscription_OrderUpdated);
            tradeSubscription.OrderStatusUnknown += new EventHandler<OrderStatusUnknownEventArgs>(tradesubscription_OrderStatusUnknown);
            tradeSubscription.OrderTimeout += new EventHandler<OrderTimeoutEventArgs>(tradesubscription_OrderTimeout);            
            tradeSubscription.Start();
            */

            //if (_monitorMM != null) {
            //    Task.Run(() => ScreenMM()).ConfigureAwait(false);
            //}
        }

        public override int GetPosition() {
            return (int)_instruTradeSubscription.PositionStatistics.NetPosition;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>  Fired when the order book download is complete and the orders have been added to the TradeSubscription instance </summary>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        private void InstrumentTradeSubscription_OrderBookDownload(object sender, OrderBookDownloadEventArgs e) {
            Logger.Info("Trade Subscription Orderbook downloaded.");

            foreach (var ord in e?.Orders) {
                UpdateOrderData(ord);
                _ttOrders[ord.SiteOrderKey] = ord;
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Event notification for order rejection. </summary>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        private void InstrumentTradeSubscription_OrderRejected(object sender, OrderRejectedEventArgs e) {
            Logger.Warn("Trade Subscription Order Rejected [{0}]: {1}", e.Order.SiteOrderKey, e.Message);

            //OrderbookEvent.GenerateEvent(e.Order, "Rejected");
            UpdateOrderData(e.Order);
            if (_ttOrders.ContainsKey(e.Order.SiteOrderKey)) {
                _ttOrders.Remove(e.Order.SiteOrderKey);
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Event notification for order fills. </summary>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        private void InstrumentTradeSubscription_OrderFilled(object sender, OrderFilledEventArgs e) {
            //OrderbookEvent.GenerateEvent(e.Fill.Order, "Filled");
            var orderID = UpdateOrderData(e.Fill.Order);

            if (e.FillType == FillType.Full) {
                DeleteOrder(orderID);

                if (_ttOrders.ContainsKey(e.Fill.Order.SiteOrderKey)) {
                    _ttOrders.Remove(e.Fill.Order.SiteOrderKey);
                }

                Logger.Info($"Trade Subscription Order Fully Filled [{e.Fill.SiteOrderKey}]: {e.Fill.Quantity}@{e.Fill.MatchPrice}");
            }
            else {
                Logger.Info($"Trade Subscription Order Partially Filled [{e.Fill.SiteOrderKey}]: {e.Fill.Quantity}@{e.Fill.MatchPrice}");
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Event notification for order deletion. </summary>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        private void InstrumentTradeSubscription_OrderDeleted(object sender, OrderDeletedEventArgs e) {
            Logger.Warn($"Trade Subscription Order Deleted [{e.OldOrder.SiteOrderKey}], Message: {e.Message}");

            //OrderbookEvent.GenerateEvent(e.DeletedUpdate, "Deleted");
            //UpdateOrderData(e.OldOrder);
            var orderID = UpdateOrderData(e.DeletedUpdate);
            DeleteOrder(orderID);

            if (_ttOrders.ContainsKey(e.DeletedUpdate.SiteOrderKey)) {
                _ttOrders.Remove(e.DeletedUpdate.SiteOrderKey);
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>Fired when an acknowledgement is received from an exchange for a new order that was submitted</summary>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        private void InstrumentTradeSubscription_OrderAdded(object sender, OrderAddedEventArgs e) {
            Logger.Info("Trade Subscription Order Added [{0}] {1}: {2}", e.Order.SiteOrderKey, e.Order.BuySell, e.Order.ToString());

            //OrderbookEvent.GenerateEvent(e.Order, "Added");
            UpdateOrderData(e.Order);

            _ttOrders[e.Order.SiteOrderKey] = e.Order;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Event notification for order update. </summary>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        private void InstrumentTradeSubscription_OrderUpdated(object sender, OrderUpdatedEventArgs e) {
            Logger.Info("Trade Subscription OrderUpdated [{0}] with price={1}", e.NewOrder.SiteOrderKey, e.NewOrder.LimitPrice);

            //OrderbookEvent.GenerateEvent(e.NewOrder, "Updated");
            UpdateOrderData(e.NewOrder);

            _ttOrders[e.NewOrder.SiteOrderKey] = e.NewOrder;
        }

        //----------------------------------------------------------------------------------------;
        /// <summary>
        /// return orderdata ID
        /// </summary>
        /// <param name="ttOrder"></param>
        /// <returns></returns>
        private string UpdateOrderData(Order ttOrder) {
            var orderData = GetOrder(ttOrder.SiteOrderKey);
            if (orderData == null) {
                orderData = new OrderData(ttOrder.SiteOrderKey) {
                    Provider = EProviderType.TT, // "TT",
                    //OrderID = ttOrder.OrderId.ToString(), //SiteOrderKey = ttOrder.SiteOrderKey,
                    OrderID = ttOrder.SiteOrderKey,
                    Product = _ttInstrument.Product.Name,
                    ProductType = _ttInstrument.Product.Type.ToString(),
                    Exchange = _ttInstrument.Key.MarketId.ToString(),
                    Contract = _ttInstrument.Key.Alias.Split(' ')[1],

                    //InstrumentID = _ttInstrument.InstrumentDetails.Id.ToString(),
                    InstrumentID = _ttInstrument.Key.Alias,
                    Account = ttOrder.TTAccountName,
                };

                AddOrder(orderData);
            }
            else {
                orderData = GetOrder(orderData.OrderID);
            }

            orderData.DateTime = ttOrder.ExchTransactionTime;  //"2019-04-03 12:28:27.995"
            orderData.LocalDateTime = DateTime.Now;

            orderData.EntryPrice = ttOrder.LimitPrice.Value;
            orderData.Qty = (int)ttOrder.OrderQuantity.Value;
            if (ttOrder.FillQuantity.IsValid) {
                orderData.FillQty = (int)ttOrder.FillQuantity.Value;
            }
            //orderData.TriggerPrice = ttOrder.TriggerPrice.Value;

            orderData.BuyOrSell = ttOrder.BuySell == BuySell.Sell ? EBuySell.Sell : EBuySell.Buy;
            orderData.Type = ttOrder.OrderType.ToString();
            orderData.Status = FormatOrderStatus(ttOrder.OrdStatus);
            orderData.Tag = ttOrder.OrderTag; // save customized algo, UserTag
            orderData.Text = ttOrder.Text;

            InstrumentHandlerBase.UpdateOrderData(orderData);

            return orderData.OrderID;
        }

        // (EOrderStatus)Enum.Parse(typeof(EOrderStatus), ttOrder.OrdStatus.ToString(), true);
        private EOrderStatus FormatOrderStatus(tt_net_sdk.OrdStatus ordStatus) {
            switch (ordStatus) {
                case OrdStatus.New: // = 1,                
                case OrdStatus.PendingNew: // = 10,
                    return EOrderStatus.New;

                case OrdStatus.PartiallyFilled: // = 2,
                    return EOrderStatus.PartiallyFilled;

                case OrdStatus.Filled: //= 3,
                    return EOrderStatus.Filled;

                case OrdStatus.Canceled: // = 5,
                case OrdStatus.PendingCancel: //= 6,
                    return EOrderStatus.Canceled;

                case OrdStatus.Stopped: // = 7,
                case OrdStatus.Rejected: // = 8,
                    return EOrderStatus.Rejected;

                case OrdStatus.Expired: // = 12,
                    return EOrderStatus.Expired;

                case OrdStatus.Suspended: // = 9,
                case OrdStatus.Calculated: // = 11,

                case OrdStatus.AcceptedForBidding: // = 13,
                case OrdStatus.PendingReplace: // = 14,
                case OrdStatus.Unknown: // = 16,
                case OrdStatus.Inactive: // = 17,
                case OrdStatus.Planned: // = 18
                case OrdStatus.NotSet: // = 0,
                case OrdStatus.DoneForDay: // = 4,
                default:
                    return EOrderStatus.Unknown;
            }
        }

        //---------------------------------------------------------------------------------------;        
        public override void SetAccount(string accountID) {
            foreach (var acc in _ttAccounts) {
                if (acc.AccountName == accountID) {
                    _curAccount = acc;
                    return;
                }
            }

            _curAccount = null;
        }

        public override void SendNewOrder(EBuySell buySell, decimal price, int qty, string tag, ETIF tif = ETIF.Day) {
            SendOrder(buySell == EBuySell.Buy ? BuySell.Buy : BuySell.Sell, price, qty, tag, tif);
            Logger.Info($"Adding order {_ttInstrument.InstrumentDetails.Alias}: {buySell} {qty}@{price}");
        }

        private string SendOrder(BuySell buySellState, decimal price, int qty, string tag, ETIF tif) {
            return SendOrder(new OrderProfile(_ttInstrument) {
                Action = OrderAction.Add,
                OrderType = OrderType.Limit,
                BuySell = buySellState,
                Account = _curAccount,
                OrderQuantity = Quantity.FromDecimal(_ttInstrument, qty),
                LimitPrice = Price.FromString(_ttInstrument, price.ToString()),  //Price.FromDecimal(_instrument, price);
                OrderTag = tag,
                //TextB = text
                TimeInForce = FormatTIF(tif)
            });
        }

        private static TimeInForce FormatTIF(ETIF tif) {
            switch (tif) {
                case ETIF.Day:
                    return TimeInForce.Day;
                case ETIF.FAK:
                    return TimeInForce.ImmediateOrCancel;
                case ETIF.FOK:
                    return TimeInForce.FillOrKill;
                default:
                    return TimeInForce.Day;
            }
        }

        private string SendOrder(OrderProfile op) {
            if (!_instruTradeSubscription.SendOrder(op)) {
                Logger.Warn($"{_ttInstrument.Name}: Failed to {op.Action} order {op.SiteOrderKey}");
                return null;
            }

            Logger.Info($"{_ttInstrument.Name} Order: {op.Action} {op.BuySell} {op.OrderQuantity}@{op.LimitPrice}, SOK={op.SiteOrderKey}");
            return op.SiteOrderKey;
        }

        public override void SendUpdateOrder(string ttOrderID, decimal price, int qty) {
            if (ttOrderID == null) {
                Logger.Warn("ttOrderID is null");
                return;
            }

            if (!_ttOrders.ContainsKey(ttOrderID)) {
                Logger.Warn($"ChangeOrder: {ttOrderID} not found the order.");
                return;
            }

            // if exists
            var orderProfile = _ttOrders[ttOrderID].GetOrderProfile();

            orderProfile.Action = OrderAction.Change;
            orderProfile.LimitPrice = Price.FromDecimal(orderProfile.Instrument, price);
            orderProfile.OrderQuantity = Quantity.FromDecimal(orderProfile.Instrument, qty);

            SendOrder(orderProfile);
        }

        public override void SendDeleteOrder(string ttOrderID, bool isBuy) {
            if (!_ttOrders.ContainsKey(ttOrderID)) {
                Logger.Warn($"DeleteOrder: {ttOrderID} not found the order.");
                return;
            }

            // if exists
            var orderProfile = _ttOrders[ttOrderID].GetOrderProfile();
            orderProfile.Action = OrderAction.Delete;

            SendOrder(orderProfile);
        }

        public override void Dispose() {
            if (_instruTradeSubscription != null) {
                _instruTradeSubscription.OrderAdded -= InstrumentTradeSubscription_OrderAdded;
                _instruTradeSubscription.OrderUpdated -= InstrumentTradeSubscription_OrderUpdated;
                _instruTradeSubscription.OrderDeleted -= InstrumentTradeSubscription_OrderDeleted;
                _instruTradeSubscription.OrderFilled -= InstrumentTradeSubscription_OrderFilled;
                _instruTradeSubscription.OrderRejected -= InstrumentTradeSubscription_OrderRejected;
                _instruTradeSubscription.OrderBookDownload -= InstrumentTradeSubscription_OrderBookDownload;

                _instruTradeSubscription.Dispose();
            }
        }

        /*
        /// <summary>
        /// screen the current second MM is valid
        /// </summary>
        /// <param name="monitorMM"></param>
        /// <returns></returns>
        internal bool ScreenMM(MonitorMM monitorMM) {
            var now = DateTime.Now;
            if (now.TimeOfDay < monitorMM.StartTime || now.TimeOfDay > monitorMM.EndTime) {
                return false;
            }

            var orderKeys = _orderDic.Keys;
            decimal bestBidPrice = 0;
            decimal bestAskPrice = decimal.MaxValue;
            int bestBidQty = 0;
            int bestAskQty = 0;
            foreach (var key in orderKeys) {
                var order = _orderDic[key];
                if (order.BuyOrSell == EBuySell.Buy) {
                    if (decimal.Compare(order.EntryPrice, bestBidPrice) >= 0) {
                        bestBidPrice = order.EntryPrice;
                        bestBidQty = order.OrderQty;
                    }
                }
                else if (order.BuyOrSell == EBuySell.Sell) {
                    if (order.EntryPrice < bestAskPrice) {
                        bestAskPrice = order.EntryPrice;
                        bestAskQty = order.OrderQty;
                    }
                }
            }

            return (bestAskPrice <= bestBidPrice + monitorMM.BidAskSpread)
                && (bestBidQty > monitorMM.BidQty)
                && (bestAskQty > monitorMM.AskQty);
        }*/
    }
}
