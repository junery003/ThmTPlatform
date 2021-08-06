//-----------------------------------------------------------------------------
// File Name   : TTAlgoHandler
// Author      : junlei
// Date        : 2/27/2020 1:57:14 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using ThmCommon.Handlers;
using ThmCommon.Models;
using tt_net_sdk;

namespace ThmTTIntegrator.TTFunctions {
    /// <summary>
    /// TTAlgoHandler
    /// </summary>
    internal class TTAlgoHandler : AlgoHandlerBase {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private AlgoLookupSubscription _algoLookupSubscription = null;
        private AlgoTradeSubscription _algoTradeSubscription = null;

        private Algo _algo = null;

        internal TTAlgoHandler(TradeHandlerBase tradeHandler) : base(tradeHandler) {
        }

        internal void SubscribeAlgo(string algoName) {
            if (_algoLookupSubscription == null) {
                _algoLookupSubscription = new AlgoLookupSubscription(Dispatcher.Current, algoName);
                _algoLookupSubscription.OnData += AlgoLookupSubscription_OnData;
                _algoLookupSubscription.GetAsync();
                //_algoLookupSubscription.Start();
            }
        }

        private void AlgoLookup_OnData(object sender, AlgoLookupEventArgs e) {
            if (e.Event == ProductDataEvent.Found) { // Algo was found
                Logger.Info("Algo Found: " + e.AlgoLookup.Algo.Alias);
            }
            else {  // Algo was not found
                Logger.Error("Cannot find algo: " + e.Message);
            }
        }

        private void AlgoLookupSubscription_OnData(object sender, AlgoLookupEventArgs e) {
            if (e.Event == ProductDataEvent.Found) {
                Logger.Info("Algo Instrument Found: " + e.AlgoLookup.Algo.Alias);
                _algo = e.AlgoLookup.Algo;

                // Create an Algo TradeSubscription to listen for order / fill events only for orders submitted through it
                _algoTradeSubscription = new AlgoTradeSubscription(Dispatcher.Current, _algo);
                _algoTradeSubscription.OrderUpdated += AlgoTradeSubscription_OrderUpdated;
                _algoTradeSubscription.OrderAdded += AlgoTradeSubscription_OrderAdded;
                _algoTradeSubscription.OrderDeleted += AlgoTradeSubscription_OrderDeleted;
                _algoTradeSubscription.OrderFilled += AlgoTradeSubscription_OrderFilled;
                _algoTradeSubscription.OrderRejected += AlgoTradeSubscription_OrderRejected;
                _algoTradeSubscription.OrderBookDownload += AlgoTradeSubscription_OrderBookDownload;
                _algoTradeSubscription.ExportValuesUpdated += AlgoTradeSubscription_ExportValuesUpdated;
                _algoTradeSubscription.AlertsFired += AlgoTradeSubscription_AlertsUpdated;
                _algoTradeSubscription.Start();
            }
            else if (e.Event == ProductDataEvent.NotAllowed) {
                Logger.Error("Not Allowed : Please check your Token access");
            }
            else { // Algo Instrument was not found and TT API has given up looking for it
                Logger.Error("Cannot find Algo instrument: " + e.Message);
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Event notification for order book download complete. </summary>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        private void AlgoTradeSubscription_OrderBookDownload(object sender, OrderBookDownloadEventArgs e) {
            Logger.Info("Algo Trade Subscription Orderbook downloaded...");
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Event notification for order rejection. </summary>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        private void AlgoTradeSubscription_OrderRejected(object sender, OrderRejectedEventArgs e) {
            Logger.Warn("Algo Order Rejected for {0}: {1} ", e.Order.SiteOrderKey, e.Message);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Event notification for order fills. </summary>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        private void AlgoTradeSubscription_OrderFilled(object sender, OrderFilledEventArgs e) {
            if (e.FillType == FillType.Full) {
                Logger.Info("Algo Order FullyFilled [{0}]: {1}@{2}", e.Fill.SiteOrderKey, e.Fill.Quantity, e.Fill.MatchPrice);
            }
            else {
                Logger.Info("Order PartiallyFilled [{0}]: {1}@{2}", e.Fill.SiteOrderKey, e.Fill.Quantity, e.Fill.MatchPrice);
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Event notification for order deletion. </summary>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        private void AlgoTradeSubscription_OrderDeleted(object sender, OrderDeletedEventArgs e) {
            Logger.Warn("Algo Order Deleted [{0}] , Message : {1}", e.OldOrder.SiteOrderKey, e.Message);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Event notification for order addition. </summary>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        private void AlgoTradeSubscription_OrderAdded(object sender, OrderAddedEventArgs e) {
            if (e.Order.IsSynthetic) {
                Logger.Info("PARENT Algo OrderAdded [{0}] for Algo : {1} with Synthetic Status : {2} ",
                    e.Order.SiteOrderKey, e.Order.Algo.Alias, e.Order.SyntheticStatus.ToString());
            }
            else {
                Logger.Info("CHILD Algo OrderAdded [{0}] {1}: {2}",
                    e.Order.SiteOrderKey, e.Order.BuySell, e.Order.ToString());
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Event notification for order update. </summary>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        private void AlgoTradeSubscription_OrderUpdated(object sender, OrderUpdatedEventArgs e) {
            if (e.NewOrder.ExecutionType == ExecType.Restated) {
                Logger.Info("Algo Order Restated [{0}] for Algo : {1} with Synthetic Status : {2} ",
                    e.NewOrder.SiteOrderKey, e.NewOrder.Algo.Alias, e.NewOrder.SyntheticStatus.ToString());
            }
            else {
                Logger.Info("Algo Order Updated [{0}] {1}: {2}",
                    e.NewOrder.SiteOrderKey, e.NewOrder.BuySell, e.NewOrder.ToString());
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Event notification for Algo ExportedValue update. </summary>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        private void AlgoTradeSubscription_ExportValuesUpdated(object sender, ExportValuesUpdatedEventArgs e) {
            foreach (string key in e.ExportValues.Keys) {
                Logger.Info("Algo EVU: Parameter Name = {0} and Parameter Value = {1}", key, e.ExportValues[key]);
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Event notification for Algo Alert update. </summary>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        private void AlgoTradeSubscription_AlertsUpdated(object sender, AlertsFiredEventArgs e) {
            foreach (string key in e.Alerts.Keys) {
                Logger.Info("Algo ALERTs Fired: Name = {0} and Alert Value = {1}", key, e.Alerts[key]);
            }
        }

        /*
        public bool StartAlgo(double triggerPrice, int triggerQty, double price, int qty, BuySell buySell) {
            while (_algo == null) {
                _mre.WaitOne();
            }

            // may not be the right palce ?
            switch (_algo.Alias) {
                case "TT Stop":
                    return TriggerTTStop(triggerQty, price, qty, buySell);
                case "TT Iceberg":
                    return TriggerTTIceberg(price, qty, buySell);
                default:
                    break;
            }

            return false;
        }

        private bool TriggerTTStop(int triggerQty, double price, int qty, BuySell buySell) {
            /*: OK:
            Dictionary<string, object> userparams = new Dictionary<string, object>
            {
                {"TriggerPriceType", tt_net_sdk.tt_stop.TriggerPriceType.Ltp }, //.OppositeSide
                {"ChildTIF" ,        TimeInForce.Day  },
                {"ParentTIF" ,       tt_net_sdk.tt_stop.ParentTIF.Day },
            };

            //OrderProfile op = _algoLookupSubscription.Algo.GetOrderProfile(_instrument);
            var op = _algo.GetOrderProfile(_instrument);  // ??
            op.UserParameters = userparams;

            //op.CoLocation = MarketId.CME;
            op.AccountName = _instrumentHandler.Account?.AccountName; // "LEIJUN SIM";
            op.Side = OrderSide.Buy; // OrderSide.Opposite;
            op.OrderType = OrderType.Limit; // OrderType.Stop;
            op.OrderQuantity = Quantity.FromDecimal(_instrument, 8);
            op.TriggerPrice = Price.FromString(_instrument, "82.39");
            op.LimitPrice = Price.FromString(_instrument, "82.41");
            * /

        Dictionary<string, object> userparams = new Dictionary<string, object> {
                { "TriggerPriceType",   tt_net_sdk.tt_stop.TriggerPriceType.OppositeSide }, //.OppositeSide
                { "TriggerQtyType",     tt_net_sdk.tt_stop.TriggerQtyType.Qty },
                { "TriggerQtyCompare",  tt_net_sdk.tt_stop.TriggerQtyCompare.LTE },
                { "TriggerQty",         triggerQty },
                { "ChildTIF" ,          TimeInForce.Day},
                { "ParentTIF" ,         tt_net_sdk.tt_stop.ParentTIF.Day },
                //{ "SecondTriggerPriceType", tt_net_sdk.tt_stop.SecondTriggerPriceType.OppositeSide},
                //{ "WaitingOption",      tt_net_sdk.tt_stop.WaitingOption.Now },
            };

            //OrderProfile op = _algoLookupSubscription.Algo.GetOrderProfile(_instrument);
            var op = _algo.GetOrderProfile(_instrument);
            op.UserParameters = userparams;

            //op.CoLocation = MarketId.CME;
            op.Account = _instrumentHandler.Account; // "LEIJUN SIM";            
            op.OrderType = OrderType.Limit; // OrderType.Stop;
            op.OrderQuantity = Quantity.FromDecimal(_instrument, qty);
            op.TextB = "Jun Test";
            if (buySell == BuySell.Buy) {
                op.Side = OrderSide.Sell;
            }
            else {
                op.Side = OrderSide.Buy;
            }
            op.TriggerPrice = Price.FromString(_instrument, price.ToString());

            if (!_algoTradeSubscription.SendOrder(op)) {
                Logger.Error("Launch algo Failed.");
                return false;
            }
            else {
                Logger.Info("Launched new algo: " + " SOK=" + op.SiteOrderKey);
                return true;
            }
        }*/

        /*
        private bool TriggerTTIceberg(double price, int qty, BuySell buySell) {
            //To retrieve the list of parameters valid for the Algo you can call
            //algo.AlgoParameters;

            //For an Iceberg Synthetic order here is the list of parameters you can set.
            /***************************************************************************
                Strategy: TT_Iceberg
                ***************************************************************************
            ----------------------------------------------------------------------------------------------
            ORDER PROFILE PROPERTIES
            Name Type                                       Required                Updateable
            ----------------------------------------------------------------------------------------------
            OrderInstrumentID                                 true                     false
            OrderQty                                          true                     true
            OrderSide                                         true                     false
            OrderAccount                                      true                     false
            OrderType                                         true                     false
            LimitPrice                                        true                     true

            ----------------------------------------------------------------------------------------------------------------------
            USER PARAMETER PROPERTIES
            Name                        Type                Required         Updateable   Algo Specific Enum
            -----------------------------------------------------------------------------------------------------------------------
            ChildTIF                    Int_t               true            false
            ParentTIF                   Int_t               true            false         tt_net_sdk.tt_iceberg.ParentTIF
            DiscVal                     Qty_t               true            true         
            DiscValType                 Int_t               true            true          tt_net_sdk.tt_iceberg.DiscValType
            Variance                    Int_t               false           false          
            LimitTicksAway              Int_t               false           true        
            LimitPriceType              Int_t               false           false         tt_net_sdk.tt_iceberg.LimitPriceType
            TriggerType                 Int_t               false           false         tt_net_sdk.tt_iceberg.TriggerType
            TriggerPriceType            Int_t               false           false         tt_net_sdk.tt_iceberg.TriggerPriceType
            IsTrlTrg                    Boolean_t           false           false         
            TriggerTicksAway            Int_t               false           true
            WithATickType               Int_t               false           false         tt_net_sdk.tt_iceberg.WithATickType
            WithATick                   Qty_t               false           true         
            STime                       UTCTimestamp_t      false           true
            ETime                       UTCTimestamp_t      false           true
            ETimeAct                    Int_t               false           false         tt_net_sdk.tt_iceberg.ETimeAct
            AutoResubExpiredGTD         Boolean_t           false           false
            ----------------------------------------------------------------------------------------------------------------------- * /
            //Construct a dictionary of the parameters and the values to send out 
            Dictionary<string, object> iceberg_userparams = new Dictionary<string, object> {
                {"DiscVal",     5},
                {"DiscValType", tt_net_sdk.tt_iceberg.DiscValType.Qty},
                {"ChildTIF" ,   tt_net_sdk.TimeInForce.Day},
                {"ParentTIF" ,  tt_net_sdk.tt_iceberg.ParentTIF.Day},
                {"ETimeAct",    tt_net_sdk.tt_iceberg.ETimeAct.Cancel},
                {"STime",      TimeUtil.EpochTimeUtc(30)},
                {"ETime",      TimeUtil.EpochTimeUtc(60)},
            };

            var lines = iceberg_userparams.Select(kvp => kvp.Key + ": " + kvp.Value.ToString());
            Logger.Info(string.Join(Environment.NewLine, lines));

            OrderProfile iceberg_op = _algo.GetOrderProfile(_instrument);
            iceberg_op.LimitPrice = Price.FromString(_instrument, price.ToString()); // _instrumentHandler.PriceHandler.TradeDataNow.BestBidPrice - 1;
            iceberg_op.Account = _instrumentHandler.Account;
            if (buySell == BuySell.Buy) {
                iceberg_op.Side = OrderSide.Buy;
            }
            else {
                iceberg_op.Side = OrderSide.Sell;
            }
            iceberg_op.OrderType = OrderType.Limit;
            iceberg_op.OrderQuantity = Quantity.FromDecimal(_instrument, qty);
            iceberg_op.TimeInForce = TimeInForce.Day;

            iceberg_op.UserParameters = iceberg_userparams;
            iceberg_op.UserTag = "IcebergAlgoUsertag";
            iceberg_op.OrderTag = "IcebergAlgoOrderTag";
            if (!_algoTradeSubscription.SendOrder(iceberg_op)) {
                Logger.Error("Failed to send order.");
                return false;
            }
            else {
                Logger.Info("Order sent : SOK=" + iceberg_op.SiteOrderKey);
                return true;
            }
        }*/

        public override void Dispose() {
            if (_algoLookupSubscription != null) {
                _algoLookupSubscription.OnData -= AlgoLookupSubscription_OnData;
                _algoLookupSubscription.Dispose();
                _algoLookupSubscription = null;
            }

            if (_algoTradeSubscription != null) {
                _algoTradeSubscription.OrderUpdated -= AlgoTradeSubscription_OrderUpdated;
                _algoTradeSubscription.OrderAdded -= AlgoTradeSubscription_OrderAdded;
                _algoTradeSubscription.OrderDeleted -= AlgoTradeSubscription_OrderDeleted;
                _algoTradeSubscription.OrderFilled -= AlgoTradeSubscription_OrderFilled;
                _algoTradeSubscription.OrderRejected -= AlgoTradeSubscription_OrderRejected;
                _algoTradeSubscription.ExportValuesUpdated -= AlgoTradeSubscription_ExportValuesUpdated;
                _algoTradeSubscription.AlertsFired -= AlgoTradeSubscription_AlertsUpdated;
                _algoTradeSubscription.Dispose();
                _algoTradeSubscription = null;
            }
        }
    }
}
