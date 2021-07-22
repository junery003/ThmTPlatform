//-----------------------------------------------------------------------------
// File Name   : MDTraderUsrCtrl
// Author      : junlei
// Date        : 4/21/2020 12:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using ThmCommon.Handlers;
using ThmCommon.Models;
using ThmTPWin.Business;
using ThmTPWin.Controllers;
using ThmTPWin.ViewModels;
using ThmTPWin.ViewModels.AlgoViewModels;
using ThmTPWin.Views.AlgoViews;

namespace ThmTPWin.Views {
    /// <summary>
    /// Interaction logic for MDTraderUsrCtrl.xaml
    /// </summary>
    public partial class MDTraderUsrCtrl : UserControl, ITrader {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private static readonly List<EAlgoType> Algos = new List<EAlgoType> {
            EAlgoType.Limit,
            EAlgoType.Trigger,
            EAlgoType.Sniper,
            EAlgoType.InterTrigger
        };

        private readonly MDTraderVM _vm;

        private TriggerWin _triggerWin = null;
        private TriggerVM _triggerVm;

        private InterTriggerWin _interTriggerWin = null;
        private InterTriggerVM _interTriggerVm;

        private readonly InstrumentHandlerBase _instrumentHandler;
        internal MDTraderUsrCtrl(InstrumentHandlerBase instrumentHandler) {
            InitializeComponent();

            _instrumentHandler = instrumentHandler;

            _vm = new MDTraderVM(instrumentHandler);
            DataContext = _vm;

            BaseTradeParas.Init(this, Algos, instrumentHandler);
            if (decimal.Compare(instrumentHandler.InstrumentInfo.TickSize, decimal.Zero) == 0) {
                Logger.Error(instrumentHandler.InstrumentInfo.InstrumentID + ": Tick size not initialised");
            }
            else {
                PriceLadder.Init(this, instrumentHandler.InstrumentInfo.TickSize);

                Logger.Info("MDTrader opened for {}", instrumentHandler.InstrumentInfo.InstrumentID);
                instrumentHandler.OnMarketDataUpdated += InstrumentHandler_OnMarketDataUpdated;
            }
        }

        private readonly object _lock = new object();
        private void InstrumentHandler_OnMarketDataUpdated() {
            lock (_lock) {
                PriceLadder.PopulateMarketData(_vm.MarketData);
            }
        }

        public InstrumentHandlerBase GetInstrumentHandler() {
            return _instrumentHandler;
        }

        public bool CheckQty(EBuySell dir) {
            if (BaseTradeParas.Quantity <= 0) {
                BaseTradeParas.QtyBackground = Brushes.Red;

                return false;
            }

            if (BaseTradeParas.Quantity > RiskManager.MaxSizePerTrade) {
                BaseTradeParas.QtyBackground = Brushes.Red;
                BaseTradeParas.QtyTip = "Qty larger than Max Size per trade: " + RiskManager.MaxSizePerTrade;

                return false;
            }

            var prodPos = TradingPMainWin.GetProductPosition(_instrumentHandler.InstrumentInfo.Product);
            var prodQty = (dir == EBuySell.Buy ? BaseTradeParas.Quantity : -BaseTradeParas.Quantity) + prodPos;
            if (Math.Abs(prodQty) > RiskManager.MaxPosPerProduct) {
                BaseTradeParas.QtyBackground = Brushes.Red;
                BaseTradeParas.QtyTip = "Position " + prodQty + " larger than Max Size per product: "
                    + RiskManager.MaxPosPerProduct;

                return false;
            }

            return true;
        }

        public void SetPosition(int position) {
            BaseTradeParas.Position = position;
        }

        public void DispalyAlgoView(EAlgoType algoType) {
            switch (algoType) {
            case EAlgoType.Trigger: {
                TriggerBtn_Click(null, null);
                break;
            }
            //case EAlgoType.PreOpen: {
            //    if (_preopenWin == null) {
            //        _preopenWin = new PreopenWin() {
            //            Owner = Window.GetWindow(this),
            //        };
            //    }
            //    _preopenWin.Show();
            //    break;
            //}
            case EAlgoType.Sniper: {
                break;
            }
            case EAlgoType.InterTrigger: {
                InterTriggerBtn_Click(null, null);
                break;
            }
            default:
                break;
            }
        }

        public void ProcessAlgo(EBuySell dir, decimal price) {
            var qty = BaseTradeParas.Quantity;
            switch (BaseTradeParas.SelectedAlgoType) {
            case EAlgoType.Limit: {
                var rlt = _vm.ProcessLimit(dir, price, qty);
                if (rlt == 0) {
                    //_ = int.TryParse(row.Cells[3].Value?.ToString(), out int algoCnt);
                    //row.Cells[3].Value = algoCnt + 1;
                }
                break;
            }
            case EAlgoType.Trigger: {
                if (_triggerVm.Qty <= 0) {
                    TriggerQtyTxtb.Background = Brushes.Red;
                    return;
                }

                var rlt = _vm.ProcessTrigger(dir, price, qty,
                    _triggerVm.PriceType,
                    _triggerVm.Operator,
                    _triggerVm.Qty);

                if (rlt == 1) {
                    IncreaseAlgo(price);
                }
                break;
            }
            case EAlgoType.Sniper: {
                var rlt = _vm.ProcessSniper(dir, price, qty);
                if (rlt == 1) {
                    IncreaseAlgo(price);
                }
                break;
            }
            case EAlgoType.InterTrigger: {
                if (!_interTriggerWin.Check(out var err)) {
                    MessageBox.Show($"Inter-Trigger error: {err}");
                    BaseTradeParas.SelectedAlgoType = EAlgoType.Limit;
                    return;
                }

                var rlt = _vm.ProcessInterTrigger(dir, price, qty,
                    _interTriggerWin.RefInstrumentHandler,
                    _interTriggerVm.RefPriceType,
                    _interTriggerVm.RefTriggerOp,
                    _interTriggerVm.RefPrice);

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
                MessageBox.Show($"Algo type not supported: {BaseTradeParas.SelectedAlgoType}");
                break;
            }
            }

            BaseTradeParas.ResetQuantity();
        }

        public void DeleteOrder(string ordID, bool isBuy) {
            _vm.DeleteOrder(ordID, isBuy);
        }

        public void DeleteAlgo(string algoID) {
            _vm.DeleteAlgo(algoID);
        }

        public void DeleteAlgosByPrice(decimal price) {
            _vm.DeleteAlgosByPrice(price);
        }

        public void DeleteAllAlgos() {
            _vm.DeleteAllAlgos();
        }

        public void IncreaseAlgo(decimal price) {
            PriceLadder.IncreaseAlgo(price);
        }

        public void DecreaseAlgo(decimal price) {
            PriceLadder.DecreaseAlgo(price);
        }

        private void RecenterMenuItem_Click(object sender, RoutedEventArgs e) {
            PriceLadder.RecenterPriceLadder();
        }

        #region Trigger
        private void TriggerBtn_Click(object sender, RoutedEventArgs e) {
            BaseTradeParas.SelectedAlgoType = EAlgoType.Trigger;
            if (_triggerWin == null) {
                _triggerVm = new TriggerVM();
                _triggerWin = new TriggerWin(this, _triggerVm) {
                    Owner = Window.GetWindow(this),
                };
            }
            _triggerWin.Show();
            TriggerQtyTxtb.Text = _triggerVm.Qty.ToString();
        }

        private void TriggerQty_TextChanged(object sender, TextChangedEventArgs e) {
            if (int.TryParse(TriggerQtyTxtb.Text, out var rlt)) {
                TriggerQtyTxtb.Background = Brushes.White;
                if (_triggerWin != null) {
                    _triggerVm.Qty = rlt;
                }
            }
            else {
                TriggerQtyTxtb.Background = Brushes.Red;
            }
        }

        #endregion

        #region Inter-trigger
        private void InterTriggerBtn_Click(object sender, RoutedEventArgs e) {
            BaseTradeParas.SelectedAlgoType = EAlgoType.InterTrigger;
            if (_interTriggerWin == null) {
                _interTriggerVm = new InterTriggerVM(_vm.InstrumentID);
                _interTriggerWin = new InterTriggerWin(this, _interTriggerVm) {
                    Owner = Window.GetWindow(this),
                };

                RefPriceTypeCmb.ItemsSource = InterTriggerVM.PriceTypes;
                RefOperatorCmb.ItemsSource = InterTriggerVM.Operators;
            }

            _interTriggerWin.Show();

            RefPriceTypeCmb.SelectedValue = _interTriggerVm.RefPriceType;
            RefOperatorCmb.SelectedValue = _interTriggerVm.RefOperator;
            RefPriceTxt.Text = _interTriggerVm.RefPrice.ToString();
        }

        private void RefPriceTypeCmb_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            if (RefPriceTypeCmb.SelectedValue != null) {
                _interTriggerVm.RefPriceType = (EPriceType)RefPriceTypeCmb.SelectedValue;
            }
        }

        private void RefOperatorCmb_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            if (RefOperatorCmb.SelectedValue != null) {
                _interTriggerVm.RefOperator = (string)RefOperatorCmb.SelectedValue;
            }
        }

        private void RefPriceTxt_TextChanged(object sender, TextChangedEventArgs e) {
            if (decimal.TryParse(RefPriceTxt.Text, out var rlt)) {
                RefPriceTxt.Background = Brushes.White;
                if (_interTriggerWin != null) {
                    _interTriggerVm.RefPrice = rlt;
                }
            }
            else {
                RefPriceTxt.Background = Brushes.Red;
            }
        }

        private void Price_PreViewKeyDown(object sender, KeyEventArgs e) {
        }

        private void Price_PreviewTextInput(object sender, TextCompositionEventArgs e) {
        }
        #endregion Inter-trigger

        private void NumberOnlyTxtb_PreviewTextInput(object sender, TextCompositionEventArgs e) {
            e.Handled = System.Text.RegularExpressions.Regex.IsMatch(e.Text, "[^0-9]+$");
        }

        public void Dispose() {
            Logger.Info("Closed MDTrader for {}", _instrumentHandler.InstrumentInfo.InstrumentID);
            _instrumentHandler.OnMarketDataUpdated -= InstrumentHandler_OnMarketDataUpdated;

            _vm.Dispose();
        }
    }
}
