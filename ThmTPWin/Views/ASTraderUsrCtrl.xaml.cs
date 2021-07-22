//-----------------------------------------------------------------------------
// File Name   : ASTraderUsrCtrl
// Author      : junlei
// Date        : 10/12/2020 05:03:17 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using ThmCommon.Handlers;
using ThmCommon.Models;
using ThmTPWin.Controllers;
using ThmTPWin.ViewModels;

namespace ThmTPWin.Views {
    /// <summary>
    /// Interaction logic for AutospreaderUsrCtrl.xaml
    /// </summary>
    public partial class ASTraderUsrCtrl : UserControl, ITrader {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private static readonly List<EAlgoType> Algos = new List<EAlgoType> { EAlgoType.Limit };

        private readonly ASTraderVM _vm;

        private readonly AutospeaderParas _asItem;

        private readonly SytheticInstrumentHandler _syntheticHandler = new SytheticInstrumentHandler();
        public ASTraderUsrCtrl(AutospeaderParas asItem) {
            InitializeComponent();

            _asItem = asItem;

            _vm = new ASTraderVM(asItem.Name, _asItem.ASLegs[0], _asItem.ASLegs[1]);
            DataContext = _vm;

            decimal tickSize = decimal.Zero;
            foreach (var para in _asItem.ASLegs) {
                _syntheticHandler.AddHandler(para.InstrumentHandler);

                para.InstrumentHandler.OnMarketDataUpdated += InstrumentHandler_OnMarketDataUpdated;
                //para.InstrumentHandler.OnOrderDataUpdated += InstrumentHandler_OnOrderDataUpdated;

                if (tickSize == decimal.Zero) {
                    tickSize = para.InstrumentHandler.InstrumentInfo.TickSize;
                }
            }

            BaseTradeParas.Init(this, Algos, _syntheticHandler);
            if (tickSize == decimal.Zero) {
                Logger.Error("Tick size is 0");
            }
            else {
                PriceLadder.Init(this, tickSize);
                _vm.Init(tickSize);
            }
        }

        private readonly object _mdLock = new object();
        private void InstrumentHandler_OnMarketDataUpdated() {
            lock (_mdLock) {
                PriceLadder.PopulateMarketData(_vm.CombineMarketData());
            }
        }

        private readonly object _orderLock = new object();
        private void InstrumentHandler_OnOrderDataUpdated(OrderData ordData) {
            lock (_orderLock) {
                _vm.OnOrderDataUpdated(ordData);
            }
        }

        public InstrumentHandlerBase GetInstrumentHandler() {
            return _syntheticHandler;
        }

        public void DispalyAlgoView(EAlgoType selectedAlgoType) {
        }

        public bool CheckQty(EBuySell dir) {
            if (BaseTradeParas.Quantity <= 0) {
                BaseTradeParas.QtyBackground = Brushes.Red;
                return false;
            }

            return true;
        }

        public void SetPosition(int position) {
            BaseTradeParas.Position = position;
        }

        public void ProcessAlgo(EBuySell dir, decimal price) {
            switch (BaseTradeParas.SelectedAlgoType) {
            case EAlgoType.Limit: {
                _vm.ProcessLimit(new AutospreaderOrder {
                    BuySell = dir,
                    ASPrice = price,
                    Qty = BaseTradeParas.Quantity,
                });

                break;
            }
            case EAlgoType.Sniper: {
                ProcessSniper(dir, price);
                break;
            }
            default: {
                MessageBox.Show($"Algo type not supported: {BaseTradeParas.SelectedAlgoType}");
                break;
            }
            }

            BaseTradeParas.ResetQuantity();
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
            PriceLadder.IncreaseAlgo(price);
        }

        public void DecreaseAlgo(decimal price) {
            PriceLadder.DecreaseAlgo(price);
        }

        private void RecenterMenuItem_Click(object sender, RoutedEventArgs e) {
            PriceLadder.RecenterPriceLadder();
        }

        private void NumberOnlyTxtb_PreviewTextInput(object sender, TextCompositionEventArgs e) {
            e.Handled = System.Text.RegularExpressions.Regex.IsMatch(e.Text, "[^0-9]+$");
        }

        public void DeleteAlgosByPrice(decimal price) { }
        public void DeleteAllAlgos() { }

        public void Dispose() {
            _vm.Dispose();
            _syntheticHandler.Dispose();
        }
    }
}
