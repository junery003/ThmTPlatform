//-----------------------------------------------------------------------------
// File Name   : OrderBookVM
// Author      : junlei
// Date        : 4/29/2020 8:50:53 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows.Data;
using System.Windows.Input;
using Prism.Commands;
using Prism.Mvvm;
using ThmCommon.Models;
using ThmCommon.Utilities;
using ThmTPWin.Models;

namespace ThmTPWin.ViewModels {
    public class OrderBookVM : BindableBase, IOrdersTabItm {
        public const string ID = "Order Book";
        public string Header => ID;

        private bool _isCancelEnabled = false;
        public bool IsCancelEnabled {
            get => _isCancelEnabled;
            set => SetProperty(ref _isCancelEnabled, value);
        }

        public ICommand SelectAllCmd { get; }
        public ICommand RowSelectedCmd { get; }
        public ICommand CancelSelectedOrdersCmd { get; }
        public ICommand CancelBuyOrdersCmd { get; }
        public ICommand CancelSellOrdersCmd { get; }
        public ICommand CancelAllOrdersCmd { get; }

        private OrderAlgoDataView _selectedOrder;
        public OrderAlgoDataView SelectedOrder {
            get => _selectedOrder;
            set => SetProperty(ref _selectedOrder, value);
        }

        public ObservableCollection<OrderAlgoDataView> OrderViewList { get; } = new();

        private readonly TradingPMainWinVM _parent;
        private readonly object _lock = new();
        public OrderBookVM(TradingPMainWinVM parent) {
            BindingOperations.EnableCollectionSynchronization(OrderViewList, _lock);

            _parent = parent;

            SelectAllCmd = new DelegateCommand(SelectAll);
            RowSelectedCmd = new DelegateCommand(RowSelected);

            CancelSelectedOrdersCmd = new DelegateCommand(CancelSelectedOrders);
            CancelBuyOrdersCmd = new DelegateCommand(CancelBuyOrders);
            CancelSellOrdersCmd = new DelegateCommand(CancelSellOrders);
            CancelAllOrdersCmd = new DelegateCommand(CancelAllOrders);
        }

        public void OnOrderDataUpdated(OrderData orderData) {
            UpdateFields(orderData);

            if (orderData.IsAlgo &&
                (orderData.Status == EOrderStatus.AlgoFired || orderData.Status == EOrderStatus.Canceled)) {
                _parent.DecreaseAlgo(orderData.InstrumentID, orderData.EntryPrice);
            }
        }

        private void SelectAll() {
            foreach (var it in OrderViewList) {
                if (!it.IsChecked) {
                    it.IsChecked = true;
                }
            }
        }

        private void RowSelected() {
            SelectAll(false);

            //var orderData = ((DataGridRow)sender).DataContext as Models.OrderAlgoDataView;
            //orderData.IsChecked = true;
            //_vm.IsCancelEnabled = true;
        }

        public void SelectAll(bool isSelected) {
            if (!OrderViewList.Any()) {
                IsCancelEnabled = false;
                return;
            }

            IsCancelEnabled = isSelected;
            foreach (var ov in OrderViewList) {
                ov.IsChecked = isSelected;
            }
        }

        private void CancelSelectedOrders() {
            _parent.CancelOrders(GetAll(true));
        }

        private void CancelBuyOrders() {
            _parent.CancelOrders(GetAll(EBuySell.Buy));
        }

        private void CancelSellOrders() {
            _parent.CancelOrders(GetAll(EBuySell.Sell));
        }

        private void CancelAllOrders() {
            _parent.CancelOrders(GetAll(false));
        }

        /// <summary>
        /// if isChecked is true, then return all checked rows, else return all rows
        /// </summary>
        /// <param name="isChecked"></param>
        /// <returns></returns>
        private IEnumerable<OrderAlgoDataView> GetAll(bool isChecked = false) {
            return isChecked ? OrderViewList.Where(x => x.IsChecked) : OrderViewList;
        }

        internal IEnumerable<OrderAlgoDataView> GetAll(EBuySell buySell) {
            return OrderViewList.Where(x => buySell == x.BuySell);
        }

        internal bool UpdateFields(OrderData orderData) {
            var orderView = OrderViewList.FirstOrDefault(x => x.ID == orderData.ID);

            switch (orderData.Status) {
            case EOrderStatus.New:
            case EOrderStatus.Pending:
            case EOrderStatus.Replaced:
            case EOrderStatus.PartiallyFilled: {
                if (orderView == null) {
                    orderView = new OrderAlgoDataView(orderData, IsCancelEnabled);
                }
                else {
                    orderView.TransactionTime = orderData.DateTime.ToString(TimeUtil.DatetimeMilliSFormat);
                    orderView.LocalTime = orderData.LocalDateTime.ToString(TimeUtil.DatetimeMilliSFormat);

                    orderView.EntryPrice = orderData.EntryPrice;
                    orderView.OrderQty = orderData.Qty;
                    orderView.FillQty = orderData.FillQty;
                    orderView.Status = orderData.Status;
                    orderView.Tag = orderData.Tag;
                    orderView.Text = orderData.Text;

                    OrderViewList.Remove(orderView);
                }

                OrderViewList.Insert(0, orderView);

                return true;
            }
            default: {
                if (orderView != null) {
                    OrderViewList.Remove(orderView);
                }
                return false;
            }
            }
        }
    }
}
