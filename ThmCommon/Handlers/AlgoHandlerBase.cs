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
        public int ProcessAlgo(AlgoData algoData, BestQuot bestQuot) {
            switch (algoData.Type) {
                case EAlgoType.PreOpen: {
                        AddAlgo(algoData);
                        return 1;
                    }
                case EAlgoType.Limit: {
                        _tradeHandler.SendNewOrder(algoData.BuyOrSell,
                            algoData.Price,
                            algoData.Qty,
                            algoData.Type.ToString());
                        return 0;
                    }
                case EAlgoType.Market:
                    Logger.Warn("Market order not supported yet");
                    return 0;
                case EAlgoType.Trigger: {
                        if (Trigger(algoData, bestQuot) > 0) { // executed 
                            return 0;
                        }
                    AddWorkingAlgo(algoData);
                        return 1;
                    }
                case EAlgoType.Sniper: {
                        if (Snipe(algoData, bestQuot) >= algoData.Qty) { // finished
                            return 0;
                        }
                    AddWorkingAlgo(algoData);
                        return 1;
                    }
                //case EAlgoType.InterTrigger: {
                //        AddWorkingAlgo(algoData);
                //        return 1;
                //    }
                default: {
                        Logger.Error("Algo not supported: {}-{}", algoData.AlgoID, algoData.Type);
                        return -1;
                    }
            }
        }

        internal void AddWorkingAlgo(AlgoData algoData) {
            algoData.Provider = _tradeHandler.InstrumentHandler.InstrumentInfo.Provider;
            algoData.Product = _tradeHandler.InstrumentHandler.InstrumentInfo.Product;
            algoData.ExchangeID = _tradeHandler.InstrumentHandler.InstrumentInfo.Exchange;
            algoData.InstrumentID = _tradeHandler.InstrumentHandler.InstrumentInfo.InstrumentID;
            algoData.Contract = _tradeHandler.InstrumentHandler.InstrumentInfo.Contract;

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
                    Logger.Info("Algo Deleted: " + algoID);
                    return tmp.Remove(algoID);
                }
            }

            return false;
        }
        #endregion algos

        #region working algos
        private readonly object _triggerLock = new();
        private readonly object _sniperLock = new();
        public void ProcessWorkingAlgos(BestQuot md) {
            var triggerTask = Task.Run(() => {
                lock (_triggerLock) {
                    var algos = _algoDic[EAlgoType.Trigger];
                    foreach (var key in algos.Keys.ToList()) {
                        var qty = Trigger(algos[key], md);
                        if (qty > 0) {
                            _tradeHandler.DeleteAlgoOrder(key, EOrderStatus.AlgoFired, qty);

                            if (algos.Remove(key)) {
                                Logger.Info("Algo Trigger {} removed from {}", key, algos.Count);
                            }
                            else {
                                Logger.Error("Algo Trigger {} removed already; {} left", key, algos.Count);
                            }
                        }
                    }
                }
            });

            var sniperTask = Task.Run(() => {
                lock (_sniperLock) {
                    var algos = _algoDic[EAlgoType.Sniper];
                    foreach (var key in algos.Keys.ToList()) {
                        var algo = algos[key];
                        var qty = Snipe(algo, md);
                        if (qty > 0) { // executed some qty
                            if (algo.FillQty >= algo.Qty) { // algo done: no qty left
                                _tradeHandler.DeleteAlgoOrder(key, EOrderStatus.AlgoFired, qty);

                                if (algos.Remove(key)) {
                                    Logger.Info("Algo Sniper {} removed from {}", key, algos.Count);
                                }
                                else {
                                    Logger.Error("Algo Sniper {} removed already; {} left", key, algos.Count);
                                }
                            }
                            else {
                                _tradeHandler.AddOrUpdateAlgoOrder(algo);
                            }
                        }
                    }
                }
            });

            _ = Task.WhenAll(sniperTask, triggerTask).ConfigureAwait(false);
        }

        #endregion working algos

        // return the executed qty if trigger conditions satisfied and executed successfully
        private int Trigger(AlgoData algo, BestQuot md) {
            if (algo.BuyOrSell == EBuySell.Buy) {
                switch (algo.TriggerPriceType) {
                    case EPriceType.OppositeSide: {
                            if (algo.Price == md.AskPrice1) {
                                if ((algo.TriggerOperator == EOperator.LessET && md.AskQty1 <= algo.TriggerQty)
                                    || (algo.TriggerOperator == EOperator.GreaterET && md.AskQty1 >= algo.TriggerQty)) {
                                    //TradeHandler.AddOrder(BuySell.Buy, algo.Price, Math.Min(qty, algo.Qty), algo.Type.ToString());
                                    _tradeHandler.SendNewOrder(EBuySell.Buy, algo.Price, algo.Qty, algo.Type.ToString());

                                    Logger.Info("Trigger: {} {}-'{}'@'{}'", algo.AlgoID, algo.BuyOrSell, algo.Qty, algo.Price);
                                    return algo.Qty;
                                }
                            }
                            else if (algo.Price < md.AskPrice1) {
                                //orderId = _tradeHandler.SendInsertOrder(EBuySell.Buy, algo.Price, algo.Qty, algo.Type.ToString());
                                return 0;
                            }

                            return 0;
                        }
                    case EPriceType.SameSide: {
                            if (algo.Price == md.BidPrice1) {
                                if ((algo.TriggerOperator == EOperator.LessET && md.BidQty1 <= algo.TriggerQty)
                                    || (algo.TriggerOperator == EOperator.GreaterET && md.BidQty1 >= algo.TriggerQty)) {
                                    _tradeHandler.SendNewOrder(EBuySell.Buy, algo.Price, algo.Qty, algo.Type.ToString());

                                    Logger.Info("Trigger: {} {}-'{}'@'{}'", algo.AlgoID, algo.BuyOrSell, algo.Qty, algo.Price);
                                    return algo.Qty;
                                }
                            }
                            else if (algo.Price < md.BidPrice1) {
                                //orderId = _tradeHandler.SendInsertOrder(EBuySell.Buy, algo.Price, algo.Qty, algo.Type.ToString());
                                return 0;
                            }

                            return 0;
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
                                    return algo.Qty;
                                }
                            }
                            else if (algo.Price > md.BidPrice1) {
                                //orderId = _tradeHandler.SendInsertOrder(EBuySell.Sell, algo.Price, algo.Qty, algo.Type.ToString());
                                return 0;
                            }

                            return 0;
                        }
                    case EPriceType.SameSide: {
                            if (algo.Price == md.AskPrice1) { // for best price 
                                if ((algo.TriggerOperator == EOperator.LessET && md.AskQty1 <= algo.TriggerQty)
                                    || (algo.TriggerOperator == EOperator.GreaterET && md.AskQty1 >= algo.TriggerQty)) {
                                    _tradeHandler.SendNewOrder(EBuySell.Sell, algo.Price, algo.Qty, algo.Type.ToString());

                                    Logger.Info("Trigger: {} {}-'{}'@'{}'", algo.AlgoID, algo.BuyOrSell, algo.Qty, algo.Price);
                                    return algo.Qty;
                                }
                            }
                            else if (algo.Price > md.AskPrice1) {
                                //orderId = _tradeHandler.SendInsertOrder(EBuySell.Sell, algo.Price, algo.Qty, algo.Type.ToString());
                                return 0;
                            }

                            return 0;
                        }
                    default: {
                            break;
                        }
                }
            }

            return 0;
        }

        // return qty executed
        private int Snipe(AlgoData algo, BestQuot md) {
            if (algo.BuyOrSell == EBuySell.Buy) {
                if (md.AskQty1 > 0 && md.AskPrice1 <= algo.Price) {
                    var qtyLeft = algo.Qty - algo.FillQty;
                    _tradeHandler.SendNewOrder(algo.BuyOrSell, algo.Price, qtyLeft, algo.Type.ToString(), ETIF.FAK);

                    var qty = Math.Min(qtyLeft, md.AskQty1);
                    algo.FillQty += qty;

                    Logger.Info("Snipe: {} {}-'{}/{}'@'{}'", algo.AlgoID, algo.BuyOrSell, qty, qtyLeft, algo.Price);

                    return qty;
                }

                return 0;
            }

            if (algo.BuyOrSell == EBuySell.Sell) {
                if (md.BidQty1 > 0 && md.BidPrice1 >= algo.Price) {
                    var qtyLeft = algo.Qty - algo.FillQty;
                    _tradeHandler.SendNewOrder(algo.BuyOrSell, algo.Price, qtyLeft, algo.Type.ToString(), ETIF.FAK);

                    var qty = Math.Min(qtyLeft, md.BidQty1);
                    algo.FillQty += qty;

                    Logger.Info("Snipe: {} {}-'{}/{}'@'{}'", algo.AlgoID, algo.BuyOrSell, qty, qtyLeft, algo.Price);
                    return qty;
                }
                return 0;
            }

            Logger.Error("Sniper should not be here");
            return 0;
        }

        public virtual void Dispose() {
        }
    }
}
