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
using ThmCommon.Models;
using ThmTPWin.Models;
using ThmTPWin.ViewModels;

namespace ThmTPWin.Views {
    /// <summary>
    /// Interaction logic for PriceLadderUsrCtrl.xaml
    /// </summary>
    public partial class PriceLadderUsrCtrl : UserControl {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();
        private PriceLadderVM _vm;
        private PriceLadderVM VM {
            get {
                if (_vm == null) {
                    _vm = (PriceLadderVM)DataContext;
                }
                return _vm;
            }
        }

        public PriceLadderUsrCtrl() {
            InitializeComponent();
        }

        internal void RecenterPriceLadder() {
            int centerIdx = VM.GetCenterIndex();
            Dispatcher.BeginInvoke(new Action(() => {
                //Task.Delay(500).Wait();
                if (centerIdx > 0 && centerIdx < DepthDataGrid.Items.Count) {
                    DepthDataGrid.UpdateLayout();
                    DepthDataGrid.ScrollIntoView(DepthDataGrid.Items[centerIdx]);
                }
            }));
        }

        private void DeleteAllAlgos_Click(object sender, RoutedEventArgs e) {
            VM.DeleteAllAlgos();
        }

        private void CancelAlgos_Click(object sender, RoutedEventArgs e) {
            var curRow = ((MenuItem)sender).DataContext as MarketDataView;
            if (curRow.AlgoCount >= 1) {
                var vm = DataContext as PriceLadderVM;
                vm.DeleteAlgosByPrice(curRow.Price);
            }
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

            var curMDView = (MarketDataView)curCellInfo.Item;
            VM.ProcessAlgo(dir, curMDView.Price);
        }
    }
}
