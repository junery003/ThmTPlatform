﻿//-----------------------------------------------------------------------------
// File Name   : MDTraderVM
// Author      : junlei
// Date        : 4/22/2020 5:02:14 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Windows.Media;
using Prism.Mvvm;
using ThmCommon.Handlers;
using ThmCommon.Models;
using ThmTPWin.Controllers;

namespace ThmTPWin.ViewModels {
    public class MDTraderVM : BindableBase, ITraderTabItm {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private static readonly List<EAlgoType> Algos = new List<EAlgoType> {
            EAlgoType.Limit,
            EAlgoType.Trigger,
            EAlgoType.Sniper,
            EAlgoType.InterTrigger
        };

        public ThmInstrumentInfo InstrumentInfo => InstrumentHandler.InstrumentInfo;
        public InstrumentHandlerBase InstrumentHandler { get; }
        public BaseTradeParaVM TradeParaVM { get; }
        public PriceLadderVM LadderVM { get; }

        public MDTraderVM(InstrumentHandlerBase instrumentHandler) {
            InstrumentHandler = instrumentHandler;

            TradeParaVM = new BaseTradeParaVM(this, Algos);
            LadderVM = new PriceLadderVM(this);


            TradeParaVM.Position = instrumentHandler.GetPosition();

            instrumentHandler.OnMarketDataUpdated += InstrumentHandler_OnMarketDataUpdated;
        }

        private readonly object _marketDataUpdatelock = new object();
        private void InstrumentHandler_OnMarketDataUpdated() {
            lock (_marketDataUpdatelock) {
                LadderVM.UpdateMarketData(InstrumentHandler.CurMarketDepthData);
            }
        }

        public void ProcessAlgo(EBuySell dir, decimal price) {
            var qty = TradeParaVM.Quantity;
            switch (TradeParaVM.SelectedAlgoType) {
            case EAlgoType.Limit: {
                var rlt = ProcessLimit(dir, price, qty);
                if (rlt == 0) {
                    //_ = int.TryParse(row.Cells[3].Value?.ToString(), out int algoCnt);
                    //row.Cells[3].Value = algoCnt + 1;
                }
                break;
            }
            case EAlgoType.Trigger: {
                if (TradeParaVM.TriggerVm.Qty <= 0) {
                    //TriggerQtyTxtb.Background = Brushes.Red;
                    return;
                }

                var rlt = ProcessTrigger(dir, price, qty,
                    TradeParaVM.TriggerVm.PriceType,
                    TradeParaVM.TriggerVm.Operator,
                    TradeParaVM.TriggerVm.Qty);

                if (rlt == 1) {
                    IncreaseAlgo(price);
                }
                break;
            }
            case EAlgoType.Sniper: {
                var rlt = ProcessSniper(dir, price, qty);
                if (rlt == 1) {
                    IncreaseAlgo(price);
                }
                break;
            }
            case EAlgoType.InterTrigger: {
                if (!TradeParaVM.InterTriggerVm.Check(out var err)) {
                    Logger.Error($"Inter-Trigger error: {err}");
                    TradeParaVM.SelectedAlgoType = EAlgoType.Limit;
                    return;
                }

                var rlt = ProcessInterTrigger(dir, price, qty,
                    TradeParaVM.InterTriggerVm.RefInstrumentHandler,
                    TradeParaVM.InterTriggerVm.RefPriceType,
                    TradeParaVM.InterTriggerVm.RefTriggerOp,
                    TradeParaVM.InterTriggerVm.RefPrice);

                if (rlt == 1) {
                    IncreaseAlgo(price);
                }
                break;
            }
            case EAlgoType.Market: {
                break;
            }
            case EAlgoType.PreOpen: {
                break;
            }
            default: {
                Logger.Error($"Algo type not supported: {TradeParaVM.SelectedAlgoType}");
                break;
            }
            }

            TradeParaVM.ResetQuantity();
        }

        internal int ProcessSniper(EBuySell dir, decimal price, int qty) {
            return InstrumentHandler.ProcessAlgo(new AlgoData(EAlgoType.Sniper) {
                BuyOrSell = dir,
                Price = price,
                Qty = qty,

                LocalDateTime = DateTime.Now,
                Account = InstrumentHandler.CurAccount
            });
        }

        internal int ProcessLimit(EBuySell dir, decimal price, int qty) {
            return InstrumentHandler.ProcessAlgo(new AlgoData(EAlgoType.Limit) {
                BuyOrSell = dir,
                Price = price,
                Qty = qty,
            });
        }

        internal int ProcessTrigger(EBuySell dir, decimal price, int qty,
            EPriceType triggerPriceType,
            EOperator triggerOperator,
            int triggerQty) {
            return InstrumentHandler.ProcessAlgo(new AlgoData(EAlgoType.Trigger) {
                BuyOrSell = dir,
                Price = price,
                Qty = qty,

                TriggerPriceType = triggerPriceType,
                TriggerOperator = triggerOperator,
                TriggerQty = triggerQty,

                LocalDateTime = DateTime.Now,
                Account = InstrumentHandler.CurAccount
            });
        }

        internal int ProcessInterTrigger(EBuySell dir, decimal price, int qty,
            InstrumentHandlerBase refInstrumentHandler,
            EPriceType refTiggerPriceType,
            EOperator refTriggerOperator,
            decimal refTriggerPrice) {
            return InstrumentHandler.ProcessAlgo(new AlgoData(EAlgoType.InterTrigger) {
                BuyOrSell = dir,
                Price = price,
                Qty = qty,

                RefInstrumentHandler = refInstrumentHandler,
                TriggerPriceType = refTiggerPriceType,
                TriggerOperator = refTriggerOperator,
                TriggerPrice = refTriggerPrice,

                LocalDateTime = DateTime.Now,
                Account = InstrumentHandler.CurAccount
            });
        }

        public void DeleteAlgosByPrice(decimal price) {
            InstrumentHandler.DeleteAlgosByPrice(price);
        }

        public void DeleteAllAlgos() {
            Logger.Info("Delete all algos.");
            InstrumentHandler.DeleteAllAlgos();
        }

        public void DeleteOrder(string ordID, bool isBuy) {
            InstrumentHandler.DeleteOrder(ordID, isBuy);
        }

        public void DeleteAlgo(string algoID) {
            InstrumentHandler.DeleteAlgo(algoID);
        }

        public bool CheckQty(EBuySell dir) {
            if (TradeParaVM.Quantity <= 0) {
                TradeParaVM.QtyBackground = Brushes.Red;
                return false;
            }

            if (TradeParaVM.Quantity > RiskManager.MaxSizePerTrade) {
                TradeParaVM.QtyBackground = Brushes.Red;
                TradeParaVM.QtyTip = "Qty larger than Max Size per trade: " + RiskManager.MaxSizePerTrade;

                return false;
            }

            var prodPos = TradingPMainWinVM.GetProductPosition(InstrumentHandler.InstrumentInfo.Product);
            var prodQty = (dir == EBuySell.Buy ? TradeParaVM.Quantity : -TradeParaVM.Quantity) + prodPos;
            if (Math.Abs(prodQty) > RiskManager.MaxPosPerProduct) {
                TradeParaVM.QtyBackground = Brushes.Red;
                TradeParaVM.QtyTip = "Position " + prodQty + " larger than Max Size per product: "
                    + RiskManager.MaxPosPerProduct;

                return false;
            }

            return true;
        }

        public void SetPosition(int position) {
            TradeParaVM.Position = position;
        }

        public void IncreaseAlgo(decimal price) {
            LadderVM.IncreaseAlgo(price);
        }

        public void DecreaseAlgo(decimal price) {
            LadderVM.DecreaseAlgo(price);
        }

        public void Dispose() {
            Logger.Info("Closed MDTrader for {}", InstrumentHandler.InstrumentInfo.InstrumentID);

            InstrumentHandler.OnMarketDataUpdated -= InstrumentHandler_OnMarketDataUpdated;
            InstrumentHandler.Stop();
        }
    }
}