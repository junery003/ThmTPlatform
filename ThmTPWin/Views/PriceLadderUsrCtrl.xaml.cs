//-----------------------------------------------------------------------------
// File Name   : PriceLadderUsrCtrl
// Author      : junlei
// Date        : 10/12/2020 05:03:17 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Threading;
using ThmCommon.Models;
using ThmTPWin.Controllers;
using ThmTPWin.Models;
using ThmTPWin.ViewModels;

namespace ThmTPWin.Views {
    /// <summary>
    /// Interaction logic for PriceLadderUsrCtrl.xaml
    /// </summary>
    public partial class PriceLadderUsrCtrl : UserControl {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private ITrader _parent;
        private PriceLadderVM _vm;
        public PriceLadderUsrCtrl() {
            InitializeComponent();
        }

        internal void Init(ITrader parent, decimal tickSize) {
            _parent = parent;
            _vm = new PriceLadderVM(tickSize);
            DataContext = _vm;
        }

        internal void PopulateMarketData(MarketDepthData marketData) {
            _vm.PopulateHLOV(marketData);
            _vm.PopulateMarketData(marketData);
        }

        internal void RecenterPriceLadder() {
            if (_vm == null) {
                Logger.Error("TickSize not init yet");
                return;
            }

            int centerIdx = _vm.GetCenterIndex();
            Dispatcher.BeginInvoke(new Action(() => {
                //Task.Delay(500).Wait();
                if (centerIdx > 0 && centerIdx < DepthDataGrid.Items.Count) {
                    DepthDataGrid.UpdateLayout();
                    DepthDataGrid.ScrollIntoView(DepthDataGrid.Items[centerIdx]);
                }
            }));
        }

        internal void IncreaseAlgo(decimal price) {
            _vm.IncreaseAlgo(price);
        }

        internal void DecreaseAlgo(decimal price) {
            _vm.DecreaseAlgo(price);
        }

        private void CancelAlgos_Click(object sender, RoutedEventArgs e) {
            var curRow = ((MenuItem)sender).DataContext as MarketDataView;
            if (curRow.AlgoCount >= 1) {
                _parent.DeleteAlgosByPrice(curRow.Price);
            }
        }

        private void CancelAllAlgos_Click(object sender, RoutedEventArgs e) {
            _parent.DeleteAllAlgos();
        }

        private void DepthDataGrid_Cell_MouseLeftButtonUp(object sender, MouseButtonEventArgs e) {
            var dg = (DataGrid)sender;
            var curCellInfo = dg.CurrentCell;
            if (curCellInfo == null) {
                return;
            }

            var curCol = dg.CurrentColumn;
            if (curCol == null) {
                return;
            }

            EBuySell dir;
            switch (curCol.Header.ToString()) {
            case "Bids":  // buy
                dir = EBuySell.Buy;
                break;
            case "Asks": // Sell
                dir = EBuySell.Sell;
                break;
            default:
                Logger.Warn($"Click col: '{curCol.Header}'");
                return;
            }

            if (!_parent.CheckQty(dir)) {
                return;
            }

            var curMDView = (MarketDataView)curCellInfo.Item;
            _parent.ProcessAlgo(dir, curMDView.Price);
        }
    }
}
