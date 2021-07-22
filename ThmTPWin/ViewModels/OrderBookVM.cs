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
using Prism.Mvvm;
using ThmCommon.Models;
using ThmCommon.Utilities;
using ThmTPWin.Models;

namespace ThmTPWin.ViewModels {
    public class OrderBookVM : BindableBase {
        public ObservableCollection<OrderAlgoDataView> OrderViewList { get; } = new ObservableCollection<OrderAlgoDataView>();

        private bool _isCancelEnabled = false;
        public bool IsCancelEnabled {
            get => _isCancelEnabled;
            set => SetProperty(ref _isCancelEnabled, value);
        }

        private readonly object _lock = new object();
        public OrderBookVM() {
            BindingOperations.EnableCollectionSynchronization(OrderViewList, _lock);
        }

        public void SelectAll(bool isSelected = true) {
            if (!OrderViewList.Any()) {
                IsCancelEnabled = false;
                return;
            }

            IsCancelEnabled = isSelected;
            foreach (var ov in OrderViewList) {
                ov.IsChecked = isSelected;
            }
        }

        /// <summary>
        /// if isChecked is true, then return all checked rows, else return all rows
        /// </summary>
        /// <param name="isChecked"></param>
        /// <returns></returns>
        internal IEnumerable<OrderAlgoDataView> GetAll(bool isChecked = false) {
            return isChecked ? OrderViewList?.Where(x => x.IsChecked) : OrderViewList;
        }

        internal IEnumerable<OrderAlgoDataView> GetAll(EBuySell buySell) {
            return OrderViewList?.Where(x => buySell == x.BuySell);
        }

        internal bool UpdateFields(OrderData orderData) {
            var orderView = OrderViewList?.FirstOrDefault(x => x.ID == orderData.ID);

            switch (orderData.Status) {
            case EOrderStatus.New:
            case EOrderStatus.Pending:
            case EOrderStatus.Replaced:
            case EOrderStatus.PartiallyFilled: {
                if (orderView == null) {
                    orderView = new OrderAlgoDataView(orderData, IsCancelEnabled);
                }
                else {
                    orderView.TransactionTime = orderData.DateTime.ToString(TimeUtil.DatetimeMSFormat);
                    orderView.LocalTime = orderData.LocalDateTime.ToString(TimeUtil.DatetimeMSFormat);

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
