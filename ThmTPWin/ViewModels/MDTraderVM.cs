//-----------------------------------------------------------------------------
// File Name   : MDTraderVM
// Author      : junlei
// Date        : 4/22/2020 5:02:14 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using Prism.Mvvm;
using ThmCommon.Handlers;
using ThmCommon.Models;

namespace ThmTPWin.ViewModels {
    public class MDTraderVM : BindableBase, IDisposable {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        internal MarketDepthData MarketData => _instrumentHandler.CurMarketDepthData;
        internal string InstrumentID => _instrumentHandler.InstrumentInfo.InstrumentID;

        private readonly InstrumentHandlerBase _instrumentHandler;
        public MDTraderVM(InstrumentHandlerBase instrumentHandler) {
            _instrumentHandler = instrumentHandler;
        }

        internal int ProcessSniper(EBuySell dir, decimal price, int qty) {
            return _instrumentHandler.ProcessAlgo(new AlgoData(EAlgoType.Sniper) {
                BuyOrSell = dir,
                Price = price,
                Qty = qty,

                LocalDateTime = DateTime.Now,
                Account = _instrumentHandler.CurAccount
            });
        }

        internal int ProcessLimit(EBuySell dir, decimal price, int qty) {
            return _instrumentHandler.ProcessAlgo(new AlgoData(EAlgoType.Limit) {
                BuyOrSell = dir,
                Price = price,
                Qty = qty,
            });
        }

        internal int ProcessTrigger(EBuySell dir, decimal price, int qty,
            EPriceType triggerPriceType,
            EOperator triggerOperator,
            int triggerQty) {
            return _instrumentHandler.ProcessAlgo(new AlgoData(EAlgoType.Trigger) {
                BuyOrSell = dir,
                Price = price,
                Qty = qty,

                TriggerPriceType = triggerPriceType,
                TriggerOperator = triggerOperator,
                TriggerQty = triggerQty,

                LocalDateTime = DateTime.Now,
                Account = _instrumentHandler.CurAccount
            });
        }

        internal int ProcessInterTrigger(EBuySell dir, decimal price, int qty,
            InstrumentHandlerBase refInstrumentHandler,
            EPriceType refTiggerPriceType,
            EOperator refTriggerOperator,
            decimal refTriggerPrice) {
            return _instrumentHandler.ProcessAlgo(new AlgoData(EAlgoType.InterTrigger) {
                BuyOrSell = dir,
                Price = price,
                Qty = qty,

                RefInstrumentHandler = refInstrumentHandler,
                TriggerPriceType = refTiggerPriceType,
                TriggerOperator = refTriggerOperator,
                TriggerPrice = refTriggerPrice,

                LocalDateTime = DateTime.Now,
                Account = _instrumentHandler.CurAccount
            });
        }

        internal void DeleteAlgosByPrice(decimal price) {
            _instrumentHandler.DeleteAlgosByPrice(price);
        }

        internal void DeleteAllAlgos() {
            Logger.Info("Delete all algos.");
            _instrumentHandler.DeleteAllAlgos();
        }

        internal void DeleteOrder(string ordID, bool isBuy) {
            _instrumentHandler.DeleteOrder(ordID, isBuy);
        }

        internal bool DeleteAlgo(string algoID) {
            return _instrumentHandler.DeleteAlgo(algoID);
        }

        public void Dispose() {
            _instrumentHandler.Stop();
        }
    }
}
