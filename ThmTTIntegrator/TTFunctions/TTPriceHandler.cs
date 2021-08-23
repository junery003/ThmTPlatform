//-----------------------------------------------------------------------------
// File Name   : TTPriceHandler
// Author      : junlei
// Date        : 1/27/2020 9:14:36 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using ThmCommon.Models;
using ThmCommon.Utilities;
using tt_net_sdk;

namespace ThmTTIntegrator.TTFunctions {
    /// <summary>
    /// market depth data, time sales data
    /// </summary>
    public sealed class TTPriceHandler : IDisposable {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private MarketDepthData _curMarketData;
        private TimeSalesData _curTimeSalesData = null;

        private readonly PriceSubscription _mdPriceSubsciption = null;
        private readonly TimeAndSalesSubscription _tsSubscription = null;

        private readonly Instrument _ttInstrument;
        private readonly TTInstrumentHandler _instrumentHandler;

        public TTPriceHandler(TTInstrumentHandler instrumentHandler, Instrument instrument) {
            _instrumentHandler = instrumentHandler;
            _ttInstrument = instrument;

            _mdPriceSubsciption = new PriceSubscription(_ttInstrument, Dispatcher.Current) {
                Settings = new PriceSubscriptionSettings(PriceSubscriptionType.MarketDepth)
            };
            _mdPriceSubsciption.FieldsUpdated += MDPriceSubscription_FieldsUpdated;
            _mdPriceSubsciption.Start();

            _tsSubscription = new TimeAndSalesSubscription(_ttInstrument, Dispatcher.Current);
            _tsSubscription.Update += TSSubscription_Update;
            _tsSubscription.Start();
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Market Depth Event notification for price update. </summary>
        /// <param name="sender"> Source of the event. </param>
        /// <param name="e">      Fields updated event information. </param>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        private void MDPriceSubscription_FieldsUpdated(object sender, FieldsUpdatedEventArgs e) {
            if (e.Error != null) { // Error has occured - the subscription is no longer active
                Logger.Error(e.Fields.Instrument + " MarketDepth Price Subscription error: " + e.Error.Message);
                //((PriceSubscription)sender).Dispose();
                return;
            }

            BuildDepthData(e.Fields, e.UpdateType);

            _instrumentHandler.UpdateMarketData(_curMarketData);
            /*
            if (false) { //enable option MM
                GetTradeDataNow(e.Fields);
                OptionMMAlgo.Run();
            } */
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Event notification for Time & Sales update. </summary>
        /// <param name="sender">   Source of the event. </param>
        /// <param name="e">        Time & Sales event information. </param>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        private void TSSubscription_Update(object sender, TimeAndSalesEventArgs e) {
            if (e.Error != null) {
                Logger.Error($"{e.Instrument} Time&Sales Subscription error: {e.Error.Message}");
                //((TimeAndSalesSubscription)sender).Dispose();
                return;
            }

            if (e.Data.Count < 1) {
                Logger.Warn($"{e.Instrument}: No time and sales data.");
                return;
            }

            // TT Update TimeSales data
            if (_curTimeSalesData == null) {
                _curTimeSalesData = new TimeSalesData() {
                    Provider = "TT",
                    Product = _ttInstrument.Product.Name,
                    ProductType = _ttInstrument.Product.Type.ToString(),
                    Exchange = _ttInstrument.Key.MarketId.ToString(),
                    Contract = _ttInstrument.Key.Alias.Split(' ')[1],

                    //InstrumentId = _ttInstrument.InstrumentDetails.Id.ToString()
                    InstrumentId = _ttInstrument.Key.Alias
                };
            }

            // More than one LTP/LTQ may be received in a single event
            foreach (TimeAndSalesData ts in e.Data) {
                _curTimeSalesData.ExchangeDateTime = ts.TimeStamp;
                _curTimeSalesData.LocalTime = DateTime.Now;

                switch (ts.Direction) {
                    case TradeDirection.Take:
                        _curTimeSalesData.BuySell = EBuySell.Buy;
                        break;
                    case TradeDirection.Hit:
                        _curTimeSalesData.BuySell = EBuySell.Sell;
                        break;
                    default:
                        _curTimeSalesData.BuySell = EBuySell.Unknown;
                        break;
                }

                _curTimeSalesData.Price = ts.TradePrice.Value;
                _curTimeSalesData.Qty = (int)ts.TradeQuantity.Value;

                _ = _instrumentHandler.SaveDataAsync(_curTimeSalesData);
            }
        }

        private bool BuildDepthData(PriceSubscriptionFields fields, UpdateType updateType) {
            if (_curMarketData == null) {
                Logger.Info("Initialised " + _ttInstrument.InstrumentDetails.Alias);
                _curMarketData = new MarketDepthData() {
                    Provider = EProviderType.TT,
                    Product = _ttInstrument.Product.Name,
                    ProductType = _ttInstrument.Product.Type.ToString(),
                    Exchange = _ttInstrument.Key.MarketId.ToString(),
                    Contract = _ttInstrument.Key.Alias.Split(' ')[1],
                    //InstrumentID = _ttInstrument.InstrumentDetails.Id.ToString()
                    InstrumentID = _ttInstrument.Key.Alias
                };
            }

            _curMarketData.LocalDateTime = DateTime.Now;
            _curMarketData.DateTime = TimeUtil.NanoSeconds2DateTime((long)fields.ExchangeRecvTime);

            // Received a market data snapshot: the snapshot event can come multiple times
            if (updateType == UpdateType.Snapshot) {
                //Debug.WriteLine("\nSnapshot Update...");
                foreach (FieldId id in fields.GetFieldIds()) {
                    //Debug.WriteLine("    {0} : {1}", id.ToString(), e.Fields[id].FormattedValue);
                    UpdateDepthData(_curMarketData, fields, id);
                }
            }
            else // Only some fields have changed
            {
                //Debug.WriteLine("\nTT Depth Data Incremental Update...");
            }

            //Debug.WriteLine("Top and level 0 field(s):");
            foreach (FieldId id in fields.GetChangedFieldIds()) {
                //Debug.WriteLine("    {0} : {1}", id.ToString(), e.Fields[id].FormattedValue);
                UpdateDepthData(_curMarketData, fields, id);
            }

            int depthLevels = Math.Min(fields.GetMaxDepthLevel(), MarketDepthData.MaxLevel);  // tt max levels : 40
            bool isDepthDataUpdated = false;
            for (int i = 0; i < depthLevels; ++i) { // when i=0, level 0 updated already
                var fieldIds = fields.GetChangedFieldIds(i);
                if (fieldIds.Length > 0) {
                    //Debug.WriteLine("Level={0}", i);
                    foreach (FieldId id in fieldIds) {
                        isDepthDataUpdated = true;
                        //Debug.WriteLine("    {0}: {1}", id.ToString(), e.Fields[id, i].FormattedValue);
                        UpdateDepthLevel(_curMarketData, i, fields[id, i].FormattedValue, id);
                    }
                }
            }

            return isDepthDataUpdated;
        }

        private static void UpdateDepthLevel(MarketDepthData depthObj, int level, string formattedValue, FieldId id) {
            switch (id) {
                case FieldId.BestBidPrice:
                    //if (double.TryParse(formattedValue, out tmpD)) {
                    //    depthObj.BestBidPrice = tmpD;
                    //}
                    if (ExtractPrice(formattedValue, out decimal tmpD)) {
                        switch (level) {
                            case 0:
                                depthObj.BidPrice1 = tmpD;
                                break;
                            case 1:
                                depthObj.BidPrice2 = tmpD;
                                break;
                            case 2:
                                depthObj.BidPrice3 = tmpD;
                                break;
                            case 3:
                                depthObj.BidPrice4 = tmpD;
                                break;
                            case 4:
                                depthObj.BidPrice5 = tmpD;
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                case FieldId.BestBidQuantity:
                    //_ = int.TryParse(formattedValue, out tmpI);
                    //depthObj.BestBidQuantity = tmpI;
                    _ = int.TryParse(formattedValue, out int tmpI);
                    switch (level) {
                        case 0:
                            depthObj.BidQty1 = tmpI;
                            break;
                        case 1:
                            depthObj.BidQty2 = tmpI;
                            break;
                        case 2:
                            depthObj.BidQty3 = tmpI;
                            break;
                        case 3:
                            depthObj.BidQty4 = tmpI;
                            break;
                        case 4:
                            depthObj.BidQty5 = tmpI;
                            break;
                        default:
                            break;
                    }
                    break;
                case FieldId.DirectBidPrice:
                    /*
                    if (double.TryParse(formattedValue, out tmpD)) {
                        switch (level) {
                            case 0:
                                depthObj.BidPrice1 = tmpD; break;
                            case 1:
                                depthObj.BidPrice2 = tmpD; break;
                            case 2:
                                depthObj.BidPrice3 = tmpD; break;
                            case 3:
                                depthObj.BidPrice4 = tmpD; break;
                            case 4:
                                depthObj.BidPrice5 = tmpD; break;
                            default: break;
                        }
                    }
                    */
                    break;
                case FieldId.DirectBidQuantity:
                    /*
                    _ = int.TryParse(formattedValue, out tmpI);
                    switch (level) {
                        case 0:
                            depthObj.BidQuantity1 = tmpI; break;
                        case 1:
                            depthObj.BidQuantity2 = tmpI; break;
                        case 2:
                            depthObj.BidQuantity3 = tmpI; break;
                        case 3:
                            depthObj.BidQuantity4 = tmpI; break;
                        case 4:
                            depthObj.BidQuantity5 = tmpI; break;
                        default: break;
                    }*/
                    break;
                case FieldId.ImpliedBidQuantity:
                    //_ = int.TryParse(formattedValue, out tmpI);
                    //    oneLevel.ImpliedBidQuantity = tmpI;
                    break;
                case FieldId.MergedBidCount:
                    //_ = UInt64.TryParse(formattedValue, out  UInt64 tmpI64);
                    //    oneLevel.MergedBidCount = tmpI64;
                    break;
                case FieldId.BestAskPrice:
                    //_ = double.TryParse(formattedValue, out tmpD);
                    //    oneLevel.BestAskPrice = tmpD;
                    if (ExtractPrice(formattedValue, out tmpD)) {
                        switch (level) {
                            case 0:
                                depthObj.AskPrice1 = tmpD;
                                break;
                            case 1:
                                depthObj.AskPrice2 = tmpD;
                                break;
                            case 2:
                                depthObj.AskPrice3 = tmpD;
                                break;
                            case 3:
                                depthObj.AskPrice4 = tmpD;
                                break;
                            case 4:
                                depthObj.AskPrice5 = tmpD;
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                case FieldId.BestAskQuantity:
                    //_ = int.TryParse(formattedValue, out tmpI);
                    //    oneLevel.BestAskQuantity = tmpI;
                    _ = int.TryParse(formattedValue, out tmpI);
                    switch (level) {
                        case 0:
                            depthObj.AskQty1 = tmpI;
                            break;
                        case 1:
                            depthObj.AskQty2 = tmpI;
                            break;
                        case 2:
                            depthObj.AskQty3 = tmpI;
                            break;
                        case 3:
                            depthObj.AskQty4 = tmpI;
                            break;
                        case 4:
                            depthObj.AskQty5 = tmpI;
                            break;
                        default:
                            break;
                    }
                    break;
                case FieldId.DirectAskPrice:
                    /*
                    if (double.TryParse(formattedValue, out tmpD)) {
                        switch (level) {
                            case 0:
                                depthObj.AskPrice1 = tmpD; break;
                            case 1:
                                depthObj.AskPrice2 = tmpD; break;
                            case 2:
                                depthObj.AskPrice3 = tmpD; break;
                            case 3:
                                depthObj.AskPrice4 = tmpD; break;
                            case 4:
                                depthObj.AskPrice5 = tmpD; break;
                            default: break;
                        }
                    }*/
                    break;
                case FieldId.DirectAskQuantity:
                    /*
                    _ = int.TryParse(formattedValue, out tmpI);
                    switch (level) {
                        case 0:
                            depthObj.AskQuantity1 = tmpI; break;
                        case 1:
                            depthObj.AskQuantity2 = tmpI; break;
                        case 2:
                            depthObj.AskQuantity3 = tmpI; break;
                        case 3:
                            depthObj.AskQuantity4 = tmpI; break;
                        case 4:
                            depthObj.AskQuantity5 = tmpI; break;
                        default: break;
                    }*/
                    break;
                case FieldId.ImpliedAskQuantity:
                    //_ = int.TryParse(formattedValue, out tmpI);
                    //    oneLevel.ImpliedAskQuantity = tmpI;
                    break;
                case FieldId.MergedAskCount:
                    //_ = UInt64.TryParse(formattedValue, out tmpI64);
                    //    oneLevel.MergedAskCount = tmpI64;
                    break;
                default:
                    break;
            }
        }

        private static bool ExtractPrice(string formattedValue, out decimal tmpD) {
            string tmp = formattedValue.Trim();
            if (string.IsNullOrEmpty(tmp)) {
                tmpD = 0;
                return false;
            }

            int idx = tmp.IndexOf('\'');
            if (idx >= 0) {
                string sub = tmp.Substring(idx);
                if (sub.Length == 2) //eg. '2
                {
                    switch (sub) {
                        case "'0":
                            tmp = tmp.Replace(sub, ".0");
                            break;
                        case "'2":
                            tmp = tmp.Replace(sub, ".25");
                            break;
                        case "'4":
                            tmp = tmp.Replace(sub, ".5");
                            break;
                        case "'6":
                            tmp = tmp.Replace(sub, ".75");
                            break;
                        default: // 1 tick == '005 == 0.015625 => 001 = 0.003125
                            Logger.Error($"Error format {tmp}");
                            break;
                    }
                }
                else if (sub.Length == 4) // eg. '140
                {
                    decimal right = decimal.Parse(sub.Substring(1)) * (decimal)0.003125;
                    tmp = tmp.Replace(sub, right.ToString());
                }
                else {
                    Logger.Error($"Error format {tmp}");
                }
            }

            return decimal.TryParse(tmp, out tmpD);
        }

        private static void UpdateDepthData(MarketDepthData depthObj, PriceSubscriptionFields fields, FieldId id) {
            switch (id) {
                case FieldId.BestAskPrice:
                    //if (ExtractPrice(fields.GetBestAskPriceField().FormattedValue, out decimal tmpD)) {
                    //    depthObj.BestAskPrice = tmpD;
                    //    depthObj.AskPrice1 = tmpD;
                    //}
                    break;
                case FieldId.BestAskQuantity:
                    //_ = int.TryParse(fields.GetBestAskQuantityField().FormattedValue, out int tmpI); {
                    //    depthObj.BestAskQty = tmpI;
                    //    depthObj.AskQty1 = tmpI;
                    //}
                    break;
                case FieldId.AskMarketQuantity:
                    //_ = double.TryParse(fields.GetAskMarketQuantityField().FormattedValue, out tmpD);
                    //    depthObj.AskMarketQuantity = tmpD;
                    break;
                case FieldId.BestAskId:
                    //UInt64 tmp64 = 0;
                    //_  = UInt64.TryParse(fields.GetBestAskIdField().FormattedValue, out tmp64);
                    //    depthObj.BestAskId = tmp64;
                    break;
                case FieldId.BestBidId:
                    //_  =int.TryParse(fields.GetBestBidIdField().FormattedValue, out tmpI);
                    //    depthObj.BestBidId = tmpI;
                    break;
                case FieldId.BestBidPrice:
                    //if (ExtractPrice(fields.GetBestBidPriceField().FormattedValue, out tmpD)) {
                    //    depthObj.BestBidPrice = tmpD;
                    //    depthObj.BidPrice1 = tmpD;
                    //}
                    break;
                case FieldId.BestBidQuantity:
                    //_ = int.TryParse(fields.GetBestBidQuantityField().FormattedValue, out tmpI); {
                    //    depthObj.BestBidQty = tmpI;
                    //    depthObj.BidQty1 = tmpI;
                    //}
                    break;
                case FieldId.BidMarketQuantity:
                    //_  = int.TryParse(fields.GetBidMarketQuantityField().FormattedValue, out tmpI);
                    //    depthObj.BidMarketQuantity = tmpI;
                    break;
                case FieldId.ClosePrice:
                    if (ExtractPrice(fields.GetClosePriceField().FormattedValue, out decimal tmpD)) {
                        depthObj.ClosePrice = tmpD;
                    }
                    break;
                case FieldId.DirectAskCount:
                    //_ = long.TryParse(fields.GetDirectAskCountField().FormattedValue, out long tmpL);
                    //depthObj.DirectAskCount = tmpL;
                    break;
                case FieldId.DirectAskPrice:
                    if (ExtractPrice(fields.GetDirectAskPriceField().FormattedValue, out tmpD)) {
                        depthObj.DirectAskPrice = tmpD;
                    }
                    break;
                case FieldId.DirectAskQuantity:
                    _ = int.TryParse(fields.GetDirectAskQuantityField().FormattedValue, out int tmpI);
                    depthObj.DirectAskQty = tmpI;
                    break;
                case FieldId.DirectBidCount:
                    //_ = long.TryParse(fields.GetDirectBidCountField().FormattedValue, out tmpL);
                    //depthObj.DirectBidCount = tmpL;
                    break;
                case FieldId.DirectBidPrice:
                    if (ExtractPrice(fields.GetDirectBidPriceField().FormattedValue, out tmpD)) {
                        depthObj.DirectBidPrice = tmpD;
                    }
                    break;
                case FieldId.DirectBidQuantity:
                    _ = int.TryParse(fields.GetDirectBidQuantityField().FormattedValue, out tmpI);
                    depthObj.DirectBidQty = tmpI;
                    break;
                case FieldId.DirectAskCounterparty:
                    //depthObj.DirectAskCounterparty = double.Parse(fields.GetDirectAskCounterpartyField().FormattedValue);
                    break;
                case FieldId.DirectBidCounterparty:
                    //depthObj.DirectBidCounterparty = double.Parse(fields.GetDirectAskCounterpartyField().FormattedValue);
                    break;
                case FieldId.HighPrice:
                    if (ExtractPrice(fields.GetHighPriceField().FormattedValue, out tmpD)) {
                        depthObj.HighPrice = tmpD;
                    }
                    break;
                case FieldId.ImbalanceQuantity:
                    //depthObj.ImbalanceQuantity = int.Parse(fields.GetImbalanceQuantityField().FormattedValue);
                    break;
                case FieldId.ImpliedAskPrice:
                    //_  = double.TryParse(fields.GetImpliedAskPriceField().FormattedValue, out tmpD);
                    //    depthObj.ImpliedAskPrice = tmpD;
                    break;
                case FieldId.ImpliedAskQuantity:
                    //_  = int.TryParse(fields.GetImpliedAskQuantityField().FormattedValue, out tmpI);
                    //    depthObj.ImpliedAskQuantity = tmpI;
                    break;
                case FieldId.ImpliedBidPrice:
                    //_ = double.TryParse(fields.GetImpliedBidPriceField().FormattedValue, out tmpD);
                    //    depthObj.ImpliedBidPrice = tmpD;
                    break;
                case FieldId.ImpliedBidQuantity:
                    //_ = int.TryParse(fields.GetImpliedBidQuantityField().FormattedValue, out tmpI);
                    //    depthObj.ImpliedBidQuantity = tmpI;
                    break;
                case FieldId.IndicativeAskPrice:
                    //_ = double.TryParse(fields.GetIndicativeAskPriceField().FormattedValue, out tmpD);
                    //    depthObj.IndicativeAskPrice = tmpD;
                    break;
                case FieldId.IndicativeBidPrice:
                    //_ = double.TryParse(fields.GetIndicativeBidPriceField().FormattedValue, out tmpD);
                    //    depthObj.IndicativeBidPrice = tmpD;
                    break;
                case FieldId.IndicativeSettlPrc:
                    //depthObj.IndicativeSettlPrc = int.Parse(fields.GetIndicativeSettlPrcField().FormattedValue);
                    break;
                case FieldId.LastTradedPrice:
                    if (ExtractPrice(fields.GetLastTradedPriceField().FormattedValue, out tmpD)) {
                        depthObj.LastTradedPrice = tmpD;
                    }
                    break;
                case FieldId.LastTradedQuantity:
                    //_ = int.TryParse(fields.GetLastTradedQuantityField().FormattedValue, out tmpI);
                    //depthObj.LastTradedQuantity = tmpI;
                    break;
                case FieldId.LowPrice:
                    if (ExtractPrice(fields.GetLowPriceField().FormattedValue, out tmpD)) {
                        depthObj.LowPrice = tmpD;
                    }
                    break;
                case FieldId.MarketSide:
                    //_ = int.TryParse(fields.GetMarketSideField().FormattedValue, out tmpI);
                    //depthObj.MarketSide = tmpI;
                    break;
                case FieldId.MergedAskCount:
                    //_ = UInt64.TryParse(fields.GetMergedAskCountField().FormattedValue, out tmp64);
                    //    depthObj.MergedAskCount = tmp64;
                    break;
                case FieldId.MergedBidCount:
                    //_ = UInt64.TryParse(fields.GetMergedBidCountField().FormattedValue, out tmp64);
                    //    depthObj.MergedBidCount = tmp64;
                    break;
                case FieldId.OpenPrice:
                    if (ExtractPrice(fields.GetOpenPriceField().FormattedValue, out tmpD)) {
                        depthObj.OpenPrice = tmpD;
                    }
                    break;
                case FieldId.OtcTradePrice:
                    //_ = double.TryParse(fields.GetOtcTradePriceField().FormattedValue, out tmpD);
                    //depthObj.OtcTradePrice = tmpD;
                    break;
                case FieldId.OtcTradeQuantity:
                    //_ = int.TryParse(fields.GetOtcTradeQuantityField().FormattedValue, out tmpI);
                    //depthObj.OtcTradeQuantity = tmpI;
                    break;
                case FieldId.SeriesStatus:
                    //depthObj.SeriesStatus = int.Parse(fields.GetSeriesStatusField().FormattedValue);
                    break;
                case FieldId.SettlementPrice:
                    if (ExtractPrice(fields.GetSettlementPriceField().FormattedValue, out tmpD)) {
                        depthObj.SettlementPrice = tmpD;
                    }
                    break;
                case FieldId.TotalTradedQuantity: //total traded is how many where traded for that trading day.
                    _ = int.TryParse(fields.GetTotalTradedQuantityField().FormattedValue, out tmpI);
                    depthObj.TotalTradedQuantity = tmpI;
                    break;
                case FieldId.WorkupPrice:
                    //if (double.TryParse(fields.GetWorkupPriceField().FormattedValue, out tmpD);
                    //    depthObj.WorkupPrice = tmpD;
                    break;
                case FieldId.WorkupState:
                    //depthObj.WorkupState = int.Parse(fields.GetWorkupStateField().FormattedValue);
                    break;
                case FieldId.CumulativeTradedQuantity:
                    //depthObj.CumulativeTradedQuantity = int.Parse(fields.GetCumulativeTradedQuantityField().FormattedValue);
                    break;
                case FieldId.OpenInterst:
                    break;
                case FieldId.IndicativeQuantity:
                    //depthObj.IndicativeQuantity = int.Parse(fields.GetIndicativeQuantityField().FormattedValue);
                    break;
                case FieldId.IndicativePrice:
                    //depthObj.IndicativePrice = int.Parse(fields.GetIndicativePriceField().FormattedValue);
                    break;
                default:
                    break;
            }
        }

        public void Dispose() {
            if (_tsSubscription != null) {
                _tsSubscription.Update -= TSSubscription_Update;
                _tsSubscription.Dispose();
            }

            if (_mdPriceSubsciption != null) {
                _mdPriceSubsciption.FieldsUpdated -= MDPriceSubscription_FieldsUpdated;
                _mdPriceSubsciption.Dispose();
            }
        }
    }
}
