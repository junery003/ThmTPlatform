//-----------------------------------------------------------------------------
// File Name   : ASTraderVM
// Author      : junlei
// Date        : 1/12/2020 5:03:17 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Windows.Media;
using ThmCommon.Handlers;
using ThmCommon.Models;
using ThmCommon.Utilities;

namespace ThmTPWin.ViewModels {
    public class ASTraderVM : BindableBase, ITraderTabItm {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private static readonly List<EAlgoType> Algos = new List<EAlgoType> { EAlgoType.Limit };

        public ThmInstrumentInfo InstrumentInfo => _syntheticHandler.InstrumentInfo;
        public BaseTradeParaVM TradeParaVM { get; }
        public PriceLadderVM LadderVM { get; }

        private readonly AutospeaderLeg _asLeg1;
        private readonly AutospeaderLeg _asLeg2;

        private readonly decimal _tickSize = decimal.Zero;
        private readonly MarketDepthData _combinedData = new();

        // first order for each autospreader pair: <tagKey, order>
        private readonly Dictionary<string, AutospreaderOrder> _orderDic = new();

        private readonly AutospeaderParas _asItem;
        private readonly SytheticInstrumentHandler _syntheticHandler = new();
        public ASTraderVM(AutospeaderParas asItem) {
            _asItem = asItem;

            _asLeg1 = asItem.ASLegs[0];
            _asLeg2 = asItem.ASLegs[1];

            decimal tickSize = decimal.Zero;
            foreach (var para in asItem.ASLegs) {
                //_syntheticHandler.AddHandler(para.InstrumentHandler);

                //para.InstrumentHandler.OnMarketDataUpdated += InstrumentHandler_OnMarketDataUpdated;
                //para.InstrumentHandler.OnOrderDataUpdated += InstrumentHandler_OnOrderDataUpdated;

                if (tickSize == decimal.Zero) {
                    tickSize = para.InstrumentHandler.TickSize;
                }
            }

            if (tickSize == decimal.Zero) {
                Logger.Error("Tick size is 0");
            }
            else {
                TradeParaVM = new BaseTradeParaVM(this, Algos);
                LadderVM = new PriceLadderVM(this);

                _tickSize = LadderVM.TickSize;
            }
        }

        private readonly object _mdLock = new object();
        private void InstrumentHandler_OnMarketDataUpdated() {
            lock (_mdLock) {
                LadderVM.UpdateMarketData(CombineMarketData());
            }
        }

        private readonly object _orderLock = new object();
        private void InstrumentHandler_OnOrderDataUpdated(OrderData ordData) {
            lock (_orderLock) {
                OnOrderDataUpdated(ordData);
            }
        }

        public bool CheckQty(EBuySell dir) {
            if (TradeParaVM.Quantity <= 0) {
                TradeParaVM.QtyBackground = Brushes.Red;
                return false;
            }

            return true;
        }

        public void SetPosition(int position) {
            TradeParaVM.Position = position;
        }

        public void ProcessAlgo(EBuySell dir, decimal price) {
            switch (TradeParaVM.SelectedAlgoType) {
                case EAlgoType.Limit: {
                        ProcessLimit(new AutospreaderOrder {
                            BuySell = dir,
                            ASPrice = price,
                            Qty = TradeParaVM.Quantity,
                        });

                        break;
                    }
                case EAlgoType.Sniper: {
                        ProcessSniper(dir, price);
                        break;
                    }
                default: {
                        Logger.Warn($"Algo type not supported: {TradeParaVM.SelectedAlgoType}");
                        break;
                    }
            }

            TradeParaVM.ResetQuantity();
        }

        private void ProcessSniper(EBuySell dir, decimal price) {
            //var algo = new AlgoData(EAlgoType.Sniper) {
            //    BuyOrSell = dir,
            //    Price = price,
            //    Qty = _vm.Quantity
            //};
            //var rlt = InstrumentHandler.AddAlgo(algo);
            //if (rlt == 1) {
            //    IncreaseAlgo(price);
            //}
        }

        public void DeleteOrder(string ordID, bool isBuy) {
            //_instrumentHandlers.ForEach(x => x.DeleteOrder(ordID));
        }

        public void DeleteAlgo(string algoID) {
            //_instrumentHandlers.ForEach(x => x.DeleteAlgo(algoID));            
        }

        public void IncreaseAlgo(decimal price) {
            LadderVM.IncreaseAlgo(price);
        }

        public void DecreaseAlgo(decimal price) {
            LadderVM.DecreaseAlgo(price);
        }

        public void DeleteAlgosByPrice(decimal price) { }
        public void DeleteAllAlgos() { }

        #region combined market data
        internal MarketDepthData CombineMarketData() {
            //var depthData1 = _asLeg1.InstrumentHandler.CurMarketDepthData;
            //var depthData2 = _asLeg2.InstrumentHandler.CurMarketDepthData;

            //GenerateBids(depthData1, depthData2);
            //GenerateOffers(depthData1, depthData2);

            // update price accrodingly
            Task.Run(() => {
                foreach (var ord in _orderDic.Values) {
                    ProcessLimit(ord);
                }
            }).ConfigureAwait(false);

            return _combinedData;
        }

        private void GenerateBids(MarketDepthData depthData1, MarketDepthData depthData2, int bsLeft = 0,
            int combineLevel = 1, int bLevel = 1, int sLevel = 1) {
            if (combineLevel > 5) {
                return;
            }

            var (bPrice, bQty) = depthData1.GetPriceQtyByLevel(bLevel);
            var (sPrice, sQty) = depthData2.GetPriceQtyByLevel(sLevel, EBuySell.Sell);

            int combineQty;
            int diff;
            if (bsLeft > 0) {
                diff = bsLeft - sQty;
                combineQty = diff >= 0 ? sQty : bsLeft;
            }
            else if (bsLeft < 0) {
                diff = bQty + bsLeft;
                combineQty = diff >= 0 ? -bsLeft : bQty;
            }
            else {
                diff = bQty - sQty;
                combineQty = diff >= 0 ? sQty : bQty;
            }

            _combinedData.SetPriceQtyByLevel(bPrice - sPrice, combineQty, combineLevel, EBuySell.Buy);

            if (diff > 0) {
                GenerateBids(depthData1, depthData2, diff, combineLevel + 1, bLevel, sLevel + 1);
            }
            else if (diff < 0) {
                GenerateBids(depthData1, depthData2, diff, combineLevel + 1, bLevel + 1, sLevel);
            }
            else {
                GenerateBids(depthData1, depthData2, diff, combineLevel + 1, bLevel + 1, sLevel + 1);
            }
        }

        private void GenerateOffers(MarketDepthData depthData1, MarketDepthData depthData2, int bsLeft = 0,
            int combineLevel = 1, int bLevel = 1, int sLevel = 1) {
            if (combineLevel > 5) {
                return;
            }

            var (sPrice, sQty) = depthData1.GetPriceQtyByLevel(sLevel, EBuySell.Sell);
            var (bPrice, bQty) = depthData2.GetPriceQtyByLevel(bLevel, EBuySell.Buy);

            int combineQty;
            int diff;
            if (bsLeft > 0) {
                diff = bsLeft - bQty;
                combineQty = diff >= 0 ? bQty : bsLeft;
            }
            else if (bsLeft < 0) {
                diff = sQty + bsLeft;
                combineQty = diff >= 0 ? -bsLeft : sQty;
            }
            else {
                diff = sQty - bQty;
                combineQty = diff >= 0 ? bQty : sQty;
            }

            _combinedData.SetPriceQtyByLevel(sPrice - bPrice, combineQty, combineLevel, EBuySell.Sell);

            if (diff > 0) {
                GenerateOffers(depthData1, depthData2, diff, combineLevel + 1, bLevel + 1, sLevel);
            }
            else if (diff < 0) {
                GenerateOffers(depthData1, depthData2, diff, combineLevel + 1, bLevel, sLevel + 1);
            }
            else {
                GenerateOffers(depthData1, depthData2, diff, combineLevel + 1, bLevel + 1, sLevel + 1);
            }
        }

        #endregion

        #region order update
        internal void OnOrderDataUpdated(OrderData ordData) {
            if (ordData.Tag == null || !_orderDic.ContainsKey(ordData.Tag)) {
                Logger.Warn($"{ordData.ID} - {ordData.Status}: order Tag is null or not in orderDic: {ordData.Tag}");
                return;
            }

            var asOrder = _orderDic[ordData.Tag];
            if (asOrder.OrderID == null) {
                asOrder.OrderID = ordData.OrderID;
            }

            if (asOrder.OrderID != ordData.OrderID) {
                Logger.Warn($"orderID {asOrder.OrderID} is not valid: {ordData.OrderID} - {ordData.Status}");
            }

            switch (ordData.Status) {
                case EOrderStatus.New:
                case EOrderStatus.Pending: {
                        break;
                    }
                //case EOrderStatus.PartiallyFilled: // avoid partially filled
                case EOrderStatus.Filled: {
                        // first order filled, send the second order
                        var qty = ordData.FillQty;
                        var buySell = asOrder.BuySell == EBuySell.Buy ? EBuySell.Sell : EBuySell.Buy;
                        var tag = "as" + (int)(asOrder.ASPrice * 100);

                        if (_asLeg1.IsActiveQuoting) {
                            decimal payup = _asLeg2.PayupTicks * (buySell == EBuySell.Buy ? _tickSize : -_tickSize);
                            var price = asOrder.Price - asOrder.ASPrice + payup;
                            //_asLeg2.InstrumentHandler.SendOrder(buySell, price, qty, tag);
                        }
                        else if (_asLeg2.IsActiveQuoting) {
                            decimal payup = _asLeg1.PayupTicks * (buySell == EBuySell.Buy ? _tickSize : -_tickSize);
                            var price = asOrder.Price + asOrder.ASPrice + payup;
                            //_asLeg1.InstrumentHandler.SendOrder(buySell, price, qty, tag);
                        }

                        asOrder.WorkingQty -= qty;  // order.FilledQty >= order.Qty
                        if (asOrder.WorkingQty <= 0) {
                            _orderDic.Remove(ordData.Tag);
                        }

                        break;
                    }
                case EOrderStatus.Canceled: {
                        asOrder.WorkingQty -= ordData.Qty;

                        if (asOrder.WorkingQty <= 0) {
                            _orderDic.Remove(ordData.Tag);
                        }
                        break;
                    }
                default: {
                        break;
                    }
            }

            Logger.Info($"OnOrderDataUpdated: Order status {ordData.ID} - {ordData.Status}");
        }
        #endregion

        #region algo
        internal void ProcessLimit(AutospreaderOrder asOrder) {
            if (_asLeg1.IsActiveQuoting) {
                var price = asOrder.ASPrice
                    //+ GetValidPrice(asOrder.Qty, asOrder.BuySell, _asLeg2.InstrumentHandler.CurMarketDepthData)
                    ;

                if (asOrder.TagKey == null || !_orderDic.ContainsKey(asOrder.TagKey)) {
                    asOrder.InstrumentHandler = _asLeg1.InstrumentHandler;
                    asOrder.Price = price;
                    asOrder.WorkingQty = asOrder.Qty;

                    var tagKey = SendOrder(asOrder);
                    _orderDic[tagKey] = asOrder;
                }
                else { // udpate price according to best price
                    if (price.CompareTo(asOrder.Price) != 0) {
                        asOrder.Price = price;
                        //asOrder.InstrumentHandler.UpdateOrder(asOrder.OrderID, price, asOrder.WorkingQty);
                    }
                }
            }
            else if (_asLeg2.IsActiveQuoting) {
                if (asOrder.TagKey == null || !_orderDic.ContainsKey(asOrder.TagKey)) {
                    asOrder.BuySell = asOrder.BuySell == EBuySell.Buy ? EBuySell.Sell : EBuySell.Buy;

                    //asOrder.Price = GetValidPrice(asOrder.Qty, asOrder.BuySell, _asLeg1.InstrumentHandler.CurMarketDepthData)
                    //    - asOrder.ASPrice;
                    asOrder.InstrumentHandler = _asLeg2.InstrumentHandler;
                    asOrder.WorkingQty = asOrder.Qty;

                    var tagKey = SendOrder(asOrder);
                    _orderDic[tagKey] = asOrder;
                }
                else {
                    //var price = GetValidPrice(asOrder.Qty, asOrder.BuySell, _asLeg1.InstrumentHandler.CurMarketDepthData)
                    //    - asOrder.ASPrice;
                    //if (price.CompareTo(asOrder.Price) != 0) {
                    //    asOrder.Price = price;
                    //    asOrder.InstrumentHandler.UpdateOrder(asOrder.OrderID, price, asOrder.WorkingQty);
                    //}
                }
            }
        }

        // return the price codsidering the QTY trying to aviod partially filled
        private decimal GetValidPrice(int asOrderQty, EBuySell asOrderBuySell, MarketDepthData asLegMD) {
            decimal price = 0;
            int qty;
            for (int total = asOrderQty, level = 1; level <= MarketDepthData.MaxLevel; ++level) {
                (price, qty) = asLegMD.GetPriceQtyByLevel(level, asOrderBuySell);
                if (total <= qty || level == MarketDepthData.MaxLevel) {
                    break;
                }
                total -= qty;
            }

            return price;
        }

        #endregion algo

        private readonly RandomGenerator _randomG = new RandomGenerator();
        // use tagKey as the unique ID for each order (instead of OrderID)
        private string SendOrder(AutospreaderOrder asOrder) {
            asOrder.TagKey = $"as{(int)(asOrder.ASPrice * 100) % 10000}_{_randomG.GenerateUniqueID(9)}{DateTime.Now:fff}";
            //asOrder.InstrumentHandler.SendOrder(asOrder.BuySell, asOrder.Price, asOrder.Qty, asOrder.TagKey);
            return asOrder.TagKey; // used as uniuqe key for autospreader
        }

        public void Dispose() {
            _randomG.Dispose();

            _syntheticHandler.Dispose();
        }
    }

    public class AutospreaderOrder {
        public string TagKey { get; set; }
        public string OrderID { get; set; }
        public ThmInstrumentInfo InstrumentHandler { get; set; }
        public EBuySell BuySell { get; set; }
        public decimal ASPrice { get; set; } // price diff for autospreader
        public decimal Price { get; set; } // actual price for sending
        public int Qty { get; set; }  // times Ratio would be the actual order qty
        //public int FilledQty { get; set; } // if FilledQty==Qty, the order completed
        public int WorkingQty { get; set; } // if workingQty is 0, the order complete
    }
}
