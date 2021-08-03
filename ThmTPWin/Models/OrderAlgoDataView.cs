//-----------------------------------------------------------------------------
// File Name   : OrderAlgoDataView
// Author      : junlei
// Date        : 8/20/2020 9:10:49 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Prism.Mvvm;
using System;
using ThmCommon.Models;
using ThmCommon.Utilities;

namespace ThmTPWin.Models {
    public sealed class OrderAlgoDataView : BindableBase, IEquatable<OrderAlgoDataView> {
        private bool _isChecked = false;
        public bool IsChecked {
            get => _isChecked;
            set => SetProperty(ref _isChecked, value);
        }

        public ThmInstrumentInfo InstrumentInfo { get; set; }

        public string Account { get; set; }

        public string OrderID { get; set; }
        public string OrderRef { get; set; }
        public bool IsAlgo { get; }
        public string AlgoID { get; set; }

        public EBuySell BuySell { get; set; }

        private string _transactionTime;
        public string TransactionTime {
            get => _transactionTime;
            set => SetProperty(ref _transactionTime, value);
        }

        private string _localTime;
        public string LocalTime {
            get => _localTime;
            set => SetProperty(ref _localTime, value);
        }

        private decimal _entryPrice;
        public decimal EntryPrice {
            get => _entryPrice;
            set => SetProperty(ref _entryPrice, value);
        }

        private int _orderQty;
        public int OrderQty {
            get => _orderQty;
            set => SetProperty(ref _orderQty, value);
        }

        private int _fillQty;
        public int FillQty {
            get => _fillQty;
            set => SetProperty(ref _fillQty, value);
        }

        private EOrderStatus _status;
        public EOrderStatus Status {
            get => _status;
            set => SetProperty(ref _status, value);
        }

        private string _type;
        public string Type {
            get => _type;
            set => SetProperty(ref _type, value);
        }

        private decimal? _triggerPrice;
        public decimal? TriggerPrice {
            get => _triggerPrice;
            set => SetProperty(ref _triggerPrice, value);
        }

        private int? _triggerQty;
        public int? TriggerQty {
            get => _triggerQty;
            set => SetProperty(ref _triggerQty, value);
        }

        private string _tag;
        public string Tag {
            get => _tag;
            set => SetProperty(ref _tag, value);
        }

        private string _text;
        public string Text {
            get => _text;
            set => SetProperty(ref _text, value);
        }

        // IsAlgo ? $"{InstrumentInfo.Exchange}|{AlgoID}|{OrderRef}" : $"{InstrumentInfo.Exchange}|{OrderID}|{OrderRef}";
        public string ID { get; private set; }
        public OrderAlgoDataView(OrderData orderData, bool isChecked = false) {
            ID = orderData.ID;
            IsAlgo = orderData.IsAlgo;
            if (IsAlgo) {
                AlgoID = orderData.OrderID;
            }
            else {
                OrderID = orderData.OrderID;
            }

            IsChecked = isChecked;
            InstrumentInfo = new ThmInstrumentInfo {
                Provider = orderData.Provider,
                Exchange = orderData.Exchange,
                InstrumentID = orderData.InstrumentID,
                Product = orderData.Product,
                Contract = orderData.Contract,
            };

            Account = orderData.Account;
            OrderRef = orderData.OrderRef;

            TransactionTime = orderData.DateTime.ToString(TimeUtil.DatetimeMilliSFormat);
            LocalTime = orderData.LocalDateTime.ToString(TimeUtil.DatetimeMilliSFormat);

            BuySell = orderData.BuyOrSell;
            EntryPrice = orderData.EntryPrice;
            FillQty = orderData.FillQty;
            OrderQty = orderData.Qty;

            TriggerQty = orderData.TriggerQty;
            TriggerPrice = orderData.TriggerPrice;

            Type = orderData.Type;
            Status = orderData.Status;
            Tag = orderData.Tag;
            Text = orderData.Text;
        }

        public bool Equals(OrderAlgoDataView other) {
            return other != null && ID == other.ID;
        }

        public override int GetHashCode() {
            return ID.GetHashCode();
        }
    }
}
