//-----------------------------------------------------------------------------
// File Name   : AlgoHandlerBase
// Author      : junlei
// Date        : 8/5/2020 5:41:32 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using ThmCommon.Models;

namespace ThmCommon.Handlers {
    public abstract class AlgoHandlerBase : IDisposable {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        // working algos: <algoType, <algoData.algoID, algoData>>
        private readonly Dictionary<EAlgoType, Dictionary<string, AlgoData>> _algoDic
            = new Dictionary<EAlgoType, Dictionary<string, AlgoData>>() {
                [EAlgoType.Trigger] = new Dictionary<string, AlgoData>(),
                [EAlgoType.Sniper] = new Dictionary<string, AlgoData>()
            };

        private readonly TradeHandlerBase _tradeHandler;
        public AlgoHandlerBase(TradeHandlerBase tradeHandler) {
            _tradeHandler = tradeHandler;
        }

        /// <summary>
        ///  Process algo for execution
        /// </summary>
        /// <param name="algoData"></param>
        /// <returns>1 if added successfully but not being executed; 
        ///          0 if added and executed; 
        ///         -1 if not added</returns>
        public int ProcessAlgo(AlgoData algoData, MarketDepthData depthData) {
            switch (algoData.Type) {
            case EAlgoType.PreOpen: {
                AddAlgo(algoData);
                return 1;
            }
            case EAlgoType.Limit: {
                _tradeHandler.SendNewOrder(algoData.BuyOrSell, algoData.Price, algoData.Qty,
                    algoData.Type.ToString(), algoData.Tag);
                return 0;
            }
            case EAlgoType.Market:
                Logger.Warn("Market order not supported yet");
                return 0;
            case EAlgoType.Trigger: {
                if (Trigger(algoData, depthData.CurBestQuot)) { // executed 
                    return 0;
                }
                AddTrigger(algoData, depthData);
                return 1;
            }
            case EAlgoType.Sniper: {
                if (Snipe(algoData, depthData.CurBestQuot)) {
                    return 0;
                }
                AddSniper(algoData, depthData);
                return 1;
            }
            case EAlgoType.InterTrigger: {
                AddInterTrigger(algoData, depthData);
                return 1;
            }
            default: {
                Logger.Error("Algo not supported: {}-{}", algoData.AlgoID, algoData.Type);
                return -1;
            }
            }
        }

        private void AddInterTrigger(AlgoData algoData, MarketDepthData depthData) {
            algoData.Provider = depthData.Provider;
            algoData.Product = depthData.Product;
            algoData.ExchangeID = depthData.Exchange;
            algoData.InstrumentID = depthData.InstrumentID;
            algoData.Contract = depthData.Contract;

            AddAlgo(algoData);
            _tradeHandler.AddOrUpdateAlgoOrder(algoData);

            Logger.Info($"Added algo: {algoData.Type} {algoData.AlgoID} - {algoData.BuyOrSell} {algoData.Qty}@{algoData.Price} ");
        }

        private void AddSniper(AlgoData algoData, MarketDepthData depthData) {
            algoData.Provider = depthData.Provider;
            algoData.Product = depthData.Product;
            algoData.ExchangeID = depthData.Exchange;
            algoData.InstrumentID = depthData.InstrumentID;
            algoData.Contract = depthData.Contract;

            AddAlgo(algoData);
            _tradeHandler.AddOrUpdateAlgoOrder(algoData);

            Logger.Info($"Added algo: {algoData.Type} {algoData.AlgoID} - {algoData.BuyOrSell} {algoData.Qty}@{algoData.Price} ");
        }

        private void AddTrigger(AlgoData algoData, MarketDepthData depthData) {
            algoData.Provider = depthData.Provider;
            algoData.Product = depthData.Product;
            algoData.ExchangeID = depthData.Exchange;
            algoData.InstrumentID = depthData.InstrumentID;
            algoData.Contract = depthData.Contract;

            AddAlgo(algoData);
            _tradeHandler.AddOrUpdateAlgoOrder(algoData);

            Logger.Info($"Added algo: {algoData.Type} {algoData.AlgoID} - {algoData.BuyOrSell} {algoData.Qty}@{algoData.Price} "
                + $"triggerQty: {algoData.TriggerQty}");
        }

        #region algos generic operations
        private void AddAlgo(AlgoData algoData) {
            if (!_algoDic.ContainsKey(algoData.Type)) {
                _algoDic[algoData.Type] = new Dictionary<string, AlgoData>();
            }

            _algoDic[algoData.Type].Add(algoData.AlgoID, algoData);
        }

        public AlgoData GetAlgo(string algoID) {
            foreach (var tmp in _algoDic.Values) {
                if (tmp.ContainsKey(algoID)) {
                    return tmp[algoID];
                }
            }

            return null;
        }

        public IEnumerable<AlgoData> GetAlgosByType(EAlgoType type) {
            return _algoDic.ContainsKey(type) ? _algoDic[type].Values : null;
        }

        internal List<AlgoData> GetAlgosByPrice(decimal price) {
            var algos = new List<AlgoData>();
            foreach (var tmp in _algoDic.Values) {
                foreach (var algo in tmp.Values) {
                    if (decimal.Compare(algo.Price, price) == 0) {
                        algos.Add(algo);
                    }
                }
            }

            return algos;
        }

        public bool DeleteAlgo(string algoID) {
            foreach (var tmp in _algoDic.Values) {
                if (tmp.ContainsKey(algoID)) {
                    Logger.Info("Algo removed: " + algoID);
                    return tmp.Remove(algoID);
                }
            }

            return false;
        }
        #endregion algos

        #region working algos
        public void ProcessWorkingAlgos(BestQuot md) {
            var triggerTask = Task.Run(() => {
                var algos = _algoDic[EAlgoType.Trigger];
                foreach (var key in algos.Keys.ToList()) {
                    if (Trigger(algos[key], md)) {
                        _tradeHandler.DeleteAlgoOrder(key, EOrderStatus.AlgoFired);
                        algos.Remove(key);
                    }
                }
            });

            var sniperTask = Task.Run(() => {
                var algos = _algoDic[EAlgoType.Sniper];
                foreach (var key in algos.Keys.ToList()) {
                    if (Snipe(algos[key], md)) {
                        _tradeHandler.DeleteAlgoOrder(key, EOrderStatus.AlgoFired);
                        algos.Remove(key);
                    }
                }
            });

            _ = Task.WhenAll(sniperTask, triggerTask).ConfigureAwait(false);
        }

        #endregion working algos

        // return true if trigger conditions satisfied and executed successfully
        private bool Trigger(AlgoData algo, BestQuot md) {
            if (algo.BuyOrSell == EBuySell.Buy) {
                switch (algo.TriggerPriceType) {
                case EPriceType.OppositeSide: {
                    if (algo.Price == md.AskPrice1) {
                        if ((algo.TriggerOperator == EOperator.LessET && md.AskQty1 <= algo.TriggerQty)
                            || (algo.TriggerOperator == EOperator.GreaterET && md.AskQty1 >= algo.TriggerQty)) {
                            //TradeHandler.AddOrder(BuySell.Buy, algo.Price, Math.Min(qty, algo.Qty), algo.Type.ToString());
                            _tradeHandler.SendNewOrder(EBuySell.Buy, algo.Price, algo.Qty, algo.Type.ToString());

                            Logger.Info("Trigger: {} {}-'{}'@'{}'", algo.AlgoID, algo.BuyOrSell, algo.Qty, algo.Price);
                            return true;
                        }
                    }
                    else if (algo.Price < md.AskPrice1) {
                        //orderId = _tradeHandler.SendInsertOrder(EBuySell.Buy, algo.Price, algo.Qty, algo.Type.ToString());
                        return false;
                    }

                    return false;
                }
                case EPriceType.SameSide: {
                    if (algo.Price == md.BidPrice1) {
                        if ((algo.TriggerOperator == EOperator.LessET && md.BidQty1 <= algo.TriggerQty)
                            || (algo.TriggerOperator == EOperator.GreaterET && md.BidQty1 >= algo.TriggerQty)) {
                            _tradeHandler.SendNewOrder(EBuySell.Buy, algo.Price, algo.Qty, algo.Type.ToString());

                            Logger.Info("Trigger: {} {}-'{}'@'{}'", algo.AlgoID, algo.BuyOrSell, algo.Qty, algo.Price);
                            return true;
                        }
                    }
                    else if (algo.Price < md.BidPrice1) {
                        //orderId = _tradeHandler.SendInsertOrder(EBuySell.Buy, algo.Price, algo.Qty, algo.Type.ToString());
                        return false;
                    }

                    return false;
                }
                default: {
                    break;
                }
                }
            }
            else if (algo.BuyOrSell == EBuySell.Sell) {
                switch (algo.TriggerPriceType) {
                case EPriceType.OppositeSide: {
                    if (algo.Price == md.BidPrice1) { // for best price 
                        if ((algo.TriggerOperator == EOperator.LessET && md.BidQty1 <= algo.TriggerQty)
                            || (algo.TriggerOperator == EOperator.GreaterET && md.BidQty1 >= algo.TriggerQty)) {
                            //orderId = TradeHandler.AddOrder(BuySell.Sell, algo.Price, Math.Min(qty, algo.Qty), algo.Type.ToString());
                            _tradeHandler.SendNewOrder(EBuySell.Sell, algo.Price, algo.Qty, algo.Type.ToString());

                            Logger.Info("Trigger: {} {}-'{}'@'{}'", algo.AlgoID, algo.BuyOrSell, algo.Qty, algo.Price);
                            return true;
                        }
                    }
                    else if (algo.Price > md.BidPrice1) {
                        //orderId = _tradeHandler.SendInsertOrder(EBuySell.Sell, algo.Price, algo.Qty, algo.Type.ToString());
                        return false;
                    }

                    return false;
                }
                case EPriceType.SameSide: {
                    if (algo.Price == md.AskPrice1) { // for best price 
                        if ((algo.TriggerOperator == EOperator.LessET && md.AskQty1 <= algo.TriggerQty)
                            || (algo.TriggerOperator == EOperator.GreaterET && md.AskQty1 >= algo.TriggerQty)) {
                            _tradeHandler.SendNewOrder(EBuySell.Sell, algo.Price, algo.Qty, algo.Type.ToString());

                            Logger.Info("Trigger: {} {}-'{}'@'{}'", algo.AlgoID, algo.BuyOrSell, algo.Qty, algo.Price);
                            return true;
                        }
                    }
                    else if (algo.Price > md.AskPrice1) {
                        //orderId = _tradeHandler.SendInsertOrder(EBuySell.Sell, algo.Price, algo.Qty, algo.Type.ToString());
                        return false;
                    }

                    return false;
                }
                default: {
                    break;
                }
                }
            }

            return false;
        }

        // return true, if snipe executed successfully
        private bool Snipe(AlgoData algo, BestQuot md) {
            if (algo.BuyOrSell == EBuySell.Buy) {
                if (md.AskPrice1 <= algo.Price) {
                    int qty = Math.Min(algo.Qty, md.AskQty1);
                    _tradeHandler.SendNewOrder(algo.BuyOrSell, algo.Price, qty, algo.Type.ToString());
                    algo.Qty -= qty;

                    Logger.Info("Snipe: {} {}-'{}'@'{}'", algo.AlgoID, algo.BuyOrSell, qty, algo.Price);
                    return algo.Qty == 0;
                }

                return false;
            }

            if (algo.BuyOrSell == EBuySell.Sell) {
                if (md.BidPrice1 >= algo.Price) {
                    int qty = Math.Min(algo.Qty, md.BidQty1);
                    _tradeHandler.SendNewOrder(algo.BuyOrSell, algo.Price, qty, algo.Type.ToString());
                    algo.Qty -= qty;

                    Logger.Info("Snipe: {} {}-'{}'@'{}'", algo.AlgoID, algo.BuyOrSell, algo.Qty, algo.Price);
                    return algo.Qty == 0;
                }
                return false;
            }

            Logger.Error("Sniper should not be here");
            return false;
        }

        public virtual void Dispose() {
        }
    }
}
