//-----------------------------------------------------------------------------
// File Name   : OrderBookUsrCtrl
// Author      : junlei
// Date        : 4/23/2020 13:05:13 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using ThmCommon.Models;
using ThmTPWin.ViewModels;

namespace ThmTPWin.Views {
    /// <summary>
    /// Interaction logic for OrderBookUsrCtrl.xaml
    /// </summary>
    public partial class OrderBookUsrCtrl : UserControl {
        public static string ID => "Order Book";

        private readonly OrderBookVM _vm = new OrderBookVM();
        private readonly TradingPMainWin _parent;
        public OrderBookUsrCtrl(TradingPMainWin parent) {
            InitializeComponent();
            DataContext = _vm;

            _parent = parent;
        }

        private void RowSelected(object sender, RoutedEventArgs e) {
            _vm.SelectAll(false);

            var orderData = ((DataGridRow)sender).DataContext as Models.OrderAlgoDataView;
            orderData.IsChecked = true;
            _vm.IsCancelEnabled = true;
        }

        private void SelectAll_Click(object sender, RoutedEventArgs e) {
            var ckbox = sender as CheckBox;
            if (ckbox.IsChecked != null) {
                _vm.SelectAll(ckbox.IsChecked.Value);
            }
        }

        private void CancelSelectedOrders_Click(object sender, RoutedEventArgs e) {
            _parent.CancelOrders(_vm.GetAll(true));
        }

        private void CancelBuyOrders_Click(object sender, RoutedEventArgs e) {
            _parent.CancelOrders(_vm.GetAll(EBuySell.Buy));
        }

        private void CancelSellOrders_Click(object sender, RoutedEventArgs e) {
            _parent.CancelOrders(_vm.GetAll(EBuySell.Sell));
        }

        private void CancelAllOrders_Click(object sender, RoutedEventArgs e) {
            _parent.CancelOrders(_vm.GetAll(false));
        }

        internal void OnOrderDataUpdated(OrderData orderData) {
            _vm.UpdateFields(orderData);

            if (orderData.IsAlgo &&
                (orderData.Status == EOrderStatus.AlgoFired || orderData.Status == EOrderStatus.Canceled)) {
                _parent.DecreaseAlgo(orderData.InstrumentID, orderData.EntryPrice);
            }
        }

        private void DataGridOrders_MouseRightButtonDown(object sender, MouseButtonEventArgs e) {
            if (((DataGrid)sender).CurrentItem is Models.OrderAlgoDataView orderData) {
                orderData.IsChecked = true;
            }
        }
    }
}
