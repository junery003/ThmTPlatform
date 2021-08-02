//-----------------------------------------------------------------------------
// File Name   : FillsVM
// Author      : junlei
// Date        : 4/29/2020 8:50:53 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Collections.ObjectModel;
using System.Windows.Data;
using Prism.Mvvm;
using ThmCommon.Models;
using ThmTPWin.Controllers;
using ThmTPWin.Models;

namespace ThmTPWin.ViewModels {
    public class FillsVM : BindableBase, IOrdersTabItm {
        public const string ID = "Fills";
        public string Header => ID;

        private readonly string _filledSound = "./sounds/shotgun.wav";
        public ObservableCollection<OrderAlgoDataView> OrderViewList { get; } = new ObservableCollection<OrderAlgoDataView>();

        private readonly TradingPMainWinVM _parent;
        private readonly object _lock = new object();
        public FillsVM(TradingPMainWinVM parent) {
            BindingOperations.EnableCollectionSynchronization(OrderViewList, _lock);

            _parent = parent;
        }

        public void OnOrderDataUpdated(OrderData orderData) {
            switch (orderData.Status) {
            case EOrderStatus.Filled:
            case EOrderStatus.PartiallyFilled: {
                Util.Sound(_filledSound);

                _parent.UpdateNetPosition(orderData.InstrumentID);

                AddRecord(orderData);
                return;
            }
            default:
                return;
            }
        }

        internal void AddRecord(OrderData orderData) {
            if (OrderViewList.Count >= 100000) {  // keep 10,000 record only
                OrderViewList.RemoveAt(OrderViewList.Count - 1);
            }

            OrderViewList.Insert(0, new OrderAlgoDataView(orderData));
        }
    }
}
