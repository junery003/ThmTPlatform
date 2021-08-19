//-----------------------------------------------------------------------------
// File Name   : TradeHandlerBase
// Author      : junlei
// Date        : 8/27/2020 3:37:59 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Linq;
using ThmCommon.Models;

namespace ThmCommon.Handlers {
    public abstract class TradeHandlerBase : IDisposable {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        public InstrumentHandlerBase InstrumentHandler { get; private set; }
        public TradeHandlerBase(InstrumentHandlerBase instrumentHandler) {
            InstrumentHandler = instrumentHandler;
        }

        #region Order
        public abstract void SetAccount(string accountID);
        public abstract int GetPosition();

        //
        public abstract void SendNewOrder(EBuySell buySell, decimal price, int qty, string tag, ETIF tif = ETIF.Day);
        public abstract void SendUpdateOrder(string orderID, decimal price, int qty);
        public abstract void SendDeleteOrder(string orderID, bool isBuy);
        #endregion

        #region orders Dic updating
        // ID: for ATP: exchange+exchange+orderID+orderRef, 
        //      for TT: site order key        
        private readonly Dictionary<string, OrderData> _orderDic = new Dictionary<string, OrderData>();
        public virtual void AddOrder(OrderData orderData) {
            _orderDic[orderData.ID] = orderData;
        }

        public virtual OrderData GetOrder(string id) {
            return _orderDic.ContainsKey(id) ? _orderDic[id] : null;
        }

        public virtual void DeleteOrder(string id) {
            if (!_orderDic.Remove(id)) {
                Logger.Warn($"DeleteOrder: {id} does not exist.");
                return;
            }
        }

        #endregion Orders

        #region Algo Orders Dic
        // algoID for Algo Order
        private readonly Dictionary<string, OrderData> _algoOrderDic = new Dictionary<string, OrderData>();
        internal void AddOrUpdateAlgoOrder(AlgoData algo) {
            OrderData orderData;
            if (!_algoOrderDic.ContainsKey(algo.AlgoID)) {
                orderData = new OrderData(algo);
                _algoOrderDic[algo.AlgoID] = orderData;
            }
            else {
                orderData = _algoOrderDic[algo.AlgoID];
                //orderData.Status = algo.Status;
                orderData.FillQty = algo.FillQty;
            }

            InstrumentHandlerBase.UpdateOrderData(orderData);
        }

        internal void DeleteAlgoOrder(string algoID, EOrderStatus status, int executedQty) {
            if (!_algoOrderDic.ContainsKey(algoID)) {
                Logger.Error("Cannot delete algo: " + algoID);
                return;
            }

            var algoOrder = _algoOrderDic[algoID];
            algoOrder.Status = status;
            if (executedQty > 0) {
                algoOrder.FillQty = executedQty;
            }

            InstrumentHandlerBase.UpdateOrderData(algoOrder);
            if (_algoOrderDic.Remove(algoID)) {
                Logger.Info("Deleted algo: {} - status: {}", algoID, status);
            }
            else {
                Logger.Error("Failed to delete algo {} - status: {}", algoID, status);
            }
        }

        internal virtual IEnumerable<string> GetAllAlgoOrderIDs() {
            return _algoOrderDic.Keys.ToList();
        }
        #endregion Algo Orders

        public virtual void Dispose() {
        }
    }
}
