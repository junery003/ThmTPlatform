//-----------------------------------------------------------------------------
// File Name   : InstrumentHandlerBase
// Author      : junlei
// Date        : 5/29/2020 11:10:20 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using ThmCommon.Models;

namespace ThmCommon.Handlers {
    public abstract class InstrumentHandlerBase : IDisposable {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        public static bool EnableSave2DB { get; set; } = true;

        public ThmInstrumentInfo InstrumentInfo { get; protected set; }
        public List<string> Accounts { get; protected set; } = new List<string>();
        public string CurAccount { get; protected set; }

        public virtual MarketDepthData CurMarketDepthData { get; protected set; }
        protected abstract AlgoHandlerBase GetAlgoHandler();
        protected abstract TradeHandlerBase GetTradeHandler();

        public abstract bool Start();
        public abstract void Stop();

        public abstract int GetPosition();

        public void SetAccount(string accountInfo) {
            CurAccount = accountInfo;
            GetTradeHandler().SetAccount(accountInfo);
        }

        #region data update
        public event Action OnMarketDataUpdated;
        public void UpdateMarketData() {
            var task1 = Task.Run(() => {
                ProcessWorkingAlgos(CurMarketDepthData.CurBestQuot);
            });
            var task2 = Task.Run(async () => {
                //DataProcessor.RedisNotify(CurMarketDepthData);
                _ = await SaveDataAsync(CurMarketDepthData);
            });
            var task3 = Task.Run(() => {
                OnMarketDataUpdated?.Invoke();
            });

            _ = Task.WhenAll(task1, task2, task3).ConfigureAwait(false);
        }

        public static event Action<OrderData> OnOrderDataUpdated;
        public static void UpdateOrderData(OrderData orderData) {
            OnOrderDataUpdated?.Invoke(orderData);
        }

        #endregion

        #region Order
        // return order ID
        public void SendOrder(EBuySell buySell, decimal price, int qty, string tag, string text = null) {
            GetTradeHandler().SendNewOrder(buySell, price, qty, tag, text);
        }

        public void UpdateOrder(string orderID, decimal price, int qty) {
            GetTradeHandler().SendUpdateOrder(orderID, price, qty);
        }

        public void DeleteOrder(string orderID, bool isBuy) {
            GetTradeHandler().SendDeleteOrder(orderID, isBuy);
        }
        #endregion

        #region Algo
        /// <summary>
        ///     Process algo in intrument level
        /// </summary>
        /// <param name="algo"></param>
        /// <returns>1 if added successfully but not being executed; 
        ///          0 if added and then executed; 
        ///         -1 if not added</returns>
        public int ProcessAlgo(AlgoData algo) {
            if (algo.Type == EAlgoType.InterTrigger) {
                if (0 == algo.RefInstrumentHandler.CheckInterTrigger(algo, this, algo.RefInstrumentHandler.CurMarketDepthData.CurBestQuot)) {
                    return 0;
                }

                algo.RefInstrumentHandler._interTriggers.Add(new Tuple<AlgoData, InstrumentHandlerBase>(algo, this));
                return 1;
            }

            return GetAlgoHandler().ProcessAlgo(algo, CurMarketDepthData);
        }

        private readonly object _algoLock = new object();
        public void ProcessWorkingAlgos(BestQuot md) {
            lock (_algoLock) {
                for (int i = 0; i < _interTriggers.Count; ++i) {
                    var tmp = _interTriggers[i];
                    if (CheckInterTrigger(tmp.Item1, tmp.Item2, md) == 0) {
                        tmp.Item2.GetTradeHandler().DeleteAlgoOrder(tmp.Item1.AlgoID, EOrderStatus.AlgoFired);
                        //_interTriggers.Remove(tmp);
                        _interTriggers.RemoveAt(i--);

                        Logger.Info("Filled inter-trigger ");
                    }
                }

                GetAlgoHandler().ProcessWorkingAlgos(md);
            }
        }

        public void DeleteAllAlgos() {
            var ids = GetTradeHandler().GetAllAlgoOrderIDs();
            if (ids != null) {
                foreach (var id in ids) {
                    DeleteAlgo(id);
                }
            }

            _interTriggers.Clear();
        }

        public bool DeleteAlgo(string algoID) {
            GetTradeHandler().DeleteAlgoOrder(algoID, EOrderStatus.Canceled);
            return GetAlgoHandler().DeleteAlgo(algoID);
        }

        public void DeleteAlgosByPrice(decimal price) {
            var orderData = GetAlgoHandler().GetAlgosByPrice(price);
            if (orderData.Count < 1) {
                Logger.Warn($"No algo found at {price} for {InstrumentInfo.InstrumentID}");
                return;
            }

            orderData.ForEach(x => {
                DeleteAlgo(x.AlgoID);
            });
        }

        #endregion

        #region Inter-trigger algo
        private readonly List<Tuple<AlgoData, InstrumentHandlerBase>> _interTriggers = new List<Tuple<AlgoData, InstrumentHandlerBase>>();

        /// <summary>
        /// check for Inter-Trigger algo
        /// </summary>
        /// <param name="algo">algo</param>
        /// <param name="instrumentHandler">orig</param>
        /// <param name="md">depth data of ref instrument</param>
        /// <returns>
        /// return 0 if executed; 
        ///     else return 1 and add for further process
        /// </returns>
        public int CheckInterTrigger(AlgoData algo, InstrumentHandlerBase instrumentHandler, BestQuot md) {
            if (algo.TriggerPriceType == EPriceType.Bid) {
                if ((algo.TriggerOperator == EOperator.LessET && md.BidPrice1 <= algo.TriggerPrice)
                    || (algo.TriggerOperator == EOperator.GreaterET && md.BidPrice1 >= algo.TriggerPrice)) {
                    instrumentHandler.SendOrder(algo.BuyOrSell, algo.Price, algo.Qty, algo.Type.ToString(), algo.Tag);
                    return 0;
                }
                else {
                    return 1;
                }
            }
            else if (algo.TriggerPriceType == EPriceType.Ask) {
                if ((algo.TriggerOperator == EOperator.LessET && md.AskPrice1 <= algo.TriggerPrice)
                    || (algo.TriggerOperator == EOperator.GreaterET && md.AskPrice1 >= algo.TriggerPrice)) {
                    instrumentHandler.SendOrder(algo.BuyOrSell, algo.Price, algo.Qty, algo.Type.ToString(), algo.Tag);
                    return 0;
                }
                else {
                    return 1;
                }
            }
            else {
                Logger.Warn("Inter-trigger algo price type is not supported: " + algo.TriggerPriceType);
                return -1;
            }
        }
        #endregion

        #region db
        private static readonly DataProcessor _dataProcessor = new DataProcessor();
        public async Task<bool> SaveDataAsync(MarketDepthData depthData) {
            try {
                if (EnableSave2DB) {
                    return await _dataProcessor.SaveDataAsync(depthData);
                }
            }
            catch (Exception ex) {
                Logger.Error(ex);
            }

            return true;
        }

        public async Task<bool> SaveDataAsync(TimeSalesData tsData) {
            try {
                if (EnableSave2DB) {
                    return await _dataProcessor.SaveDataAsync(tsData);
                }
            }
            catch (Exception ex) {
                Logger.Error(ex);
            }

            return true;
        }

        #endregion

        public virtual void Dispose() {
        }
    }
}
