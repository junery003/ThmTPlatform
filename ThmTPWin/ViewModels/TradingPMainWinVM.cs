//-----------------------------------------------------------------------------
// File Name   : TradingPMainWinVM
// Author      : junlei
// Date        : 4/22/2020 5:03:58 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Prism.Commands;
using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Timers;
using System.Windows.Input;
using ThmCommon.Handlers;
using ThmCommon.Models;
using ThmTPWin.Models;

namespace ThmTPWin.ViewModels {
    public class TradingPMainWinVM : BindableBase, IDisposable {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private DateTime _currentTime = DateTime.Now;
        public DateTime CurrentTime {
            get => _currentTime;
            set => SetProperty(ref _currentTime, value);
        }

        private bool _isTitanEnabled;
        public bool IsTitanEnabled {
            get => _isTitanEnabled;
            set => SetProperty(ref _isTitanEnabled, value);
        }

        private ITraderTabItm _selectedTradeTabItm;
        public ITraderTabItm SelectedTradeTabItm {
            get => _selectedTradeTabItm;
            set => SetProperty(ref _selectedTradeTabItm, value);
        }
        public static ObservableCollection<ITraderTabItm> TradeWidgetTabItms { get; } = new();

        public TradingPMainWinVM() {
            InitTimer();

            OrderBookCmd = new DelegateCommand(OpenOrderBook);
            AuditTrailCmd = new DelegateCommand(OpenAuditTrail);
            FillsCmd = new DelegateCommand(OpenFills);
        }

        internal void AddMDTrader(ThmInstrumentInfo instrumentInfo) {
            if (decimal.Compare(instrumentInfo.TickSize, decimal.Zero) == 0) {
                Logger.Error(instrumentInfo.InstrumentID + ": Tick size not initialised");
                return;
            }

            var mdTrader = TradeWidgetTabItms.FirstOrDefault(x => x.InstrumentInfo.Equals(instrumentInfo));
            if (mdTrader == null) {
                mdTrader = new MDTraderVM(instrumentInfo);
                TradeWidgetTabItms.Add(mdTrader);
            }

            SelectedTradeTabItm = mdTrader;

            Logger.Info("MDTrader opened for {}", instrumentInfo.InstrumentID);
        }

        internal void AddASTrader(AutospeaderParas asItem, bool openWithLegs) {
            asItem.IsEnabled = false;

            var asTrader = TradeWidgetTabItms.FirstOrDefault(x => x.InstrumentInfo.Equals(asItem.InstrumentInfo));

            if (asTrader == null) {
                asTrader = new ASTraderVM(asItem);
                TradeWidgetTabItms.Add(asTrader);
            }

            if (openWithLegs) {
                foreach (var leg in asItem.ASLegs) {
                    AddMDTrader(leg.InstrumentInfo);
                }
            }

            SelectedTradeTabItm = asTrader;
        }

        internal void CancelOrders(IEnumerable<OrderAlgoDataView> aovs) {
            if (aovs == null) {
                return;
            }

            foreach (var aov in aovs.ToList()) {
                CancelOrder(aov);
            }
        }

        private void CancelOrder(OrderAlgoDataView aov) {
            var trader = TradeWidgetTabItms.FirstOrDefault(x => x.InstrumentInfo.Equals(aov.InstrumentInfo));

            if (trader == null) {
                Logger.Error("No instrument handler found for " + aov.InstrumentInfo.InstrumentID);
                return;
            }

            if (aov.IsAlgo) {
                trader.DeleteAlgo(aov.AlgoID);
            }
            else {
                trader.DeleteOrder(aov.OrderID, aov.BuySell == EBuySell.Buy);
            }
        }


        internal void DecreaseAlgo(string instrumentID, decimal price) {
            var trader = TradeWidgetTabItms.FirstOrDefault(x => x.InstrumentInfo.InstrumentID == instrumentID);
            if (trader == null) {
                Logger.Error("No instrument handler found for " + instrumentID);
                return;
            }

            trader.DecreaseAlgo(price);
        }

        internal void UpdateNetPosition(string instrumentID) {
            var trader = TradeWidgetTabItms.FirstOrDefault(x => x.InstrumentInfo.InstrumentID == instrumentID);
            if (trader == null) {
                Logger.Error("No instrument handler found for " + instrumentID);
                return;
            }
            //trader.SetPosition(trader.InstrumentHandler.GetPosition());
        }

        internal static int GetProductPosition(string product) {
            var traders = TradeWidgetTabItms.Where(x => x.InstrumentInfo.Product == product);
            if (traders == null || !traders.Any()) {
                Logger.Error("No instrument handler found for " + product);
                return 0;
            }

            var pos = 0;
            foreach (var pair in traders) {
                //pos += pair.InstrumentHandler.GetPosition();
            }

            return pos;
        }

        #region orderbook/fills etc.

        public ICommand OrderBookCmd { get; }
        public ICommand AuditTrailCmd { get; }
        public ICommand FillsCmd { get; }

        private IOrdersTabItm _selectedOrderTabItm;
        public IOrdersTabItm SelectedOrderTabItm {
            get => _selectedOrderTabItm;
            set => SetProperty(ref _selectedOrderTabItm, value);
        }
        public ObservableCollection<IOrdersTabItm> OrdersTabItms { get; } = new ObservableCollection<IOrdersTabItm>();

        internal void InitOrdersTabItms() {
            OpenOrderBook();
            OpenFills();
            OpenAuditTrail();

            InstrumentHandlerBase.OnOrderDataUpdated += InstrumentHandlerBase_OnOrderDataUpdated;
        }

        private void InstrumentHandlerBase_OnOrderDataUpdated(OrderData orderData) {
            foreach (var itm in OrdersTabItms) {
                itm.OnOrderDataUpdated(orderData);
            }
        }

        private void OpenFills() {
            var itm = OrdersTabItms.FirstOrDefault(x => x.Header == FillsVM.ID);
            if (itm == null) {
                itm = new FillsVM(this);
                OrdersTabItms.Add(itm);
            }

            SelectedOrderTabItm = itm;
        }

        private void OpenAuditTrail() {
            var itm = OrdersTabItms.FirstOrDefault(x => x.Header == AuditTrailVM.ID);
            if (itm == null) {
                itm = new AuditTrailVM();
                OrdersTabItms.Add(itm);
            }

            SelectedOrderTabItm = itm;
        }

        private void OpenOrderBook() {
            var itm = OrdersTabItms.FirstOrDefault(x => x.Header == OrderBookVM.ID);
            if (itm == null) {
                itm = new OrderBookVM(this);
                OrdersTabItms.Add(itm);
            }

            SelectedOrderTabItm = itm;
        }

        #endregion orderbook/fills etc.

        private void InitTimer() {
            var timer = new Timer() {
                Interval = 1000,
                Enabled = true
            };

            timer.Elapsed += (object sender, ElapsedEventArgs e) => {
                CurrentTime = DateTime.Now;
            };
        }

        public void Dispose() {
            InstrumentHandlerBase.OnOrderDataUpdated -= InstrumentHandlerBase_OnOrderDataUpdated;
            foreach (var trade in TradeWidgetTabItms) {
                trade.Dispose();
            }

            ThmServerAdapter.ThmClient.Close();
        }
    }

    public interface IOrdersTabItm {
        string Header { get; }
        void OnOrderDataUpdated(OrderData orderData);
    }

    public interface ITraderTabItm : IDisposable {
        ThmInstrumentInfo InstrumentInfo { get; } // redundant

        bool CheckQty(EBuySell dir);
        void SetPosition(int position);

        void DeleteOrder(string orderID, bool isBuy);

        void ProcessAlgo(EBuySell dir, decimal price);
        void IncreaseAlgo(decimal price);
        void DecreaseAlgo(decimal price);

        void DeleteAlgo(string algoID);
        void DeleteAlgosByPrice(decimal price);
        void DeleteAllAlgos();
    }
}
