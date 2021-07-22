//-----------------------------------------------------------------------------
// File Name   : TradingPMainWin
// Author      : junlei
// Date        : 4/21/2020 11:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using ThmCommon.Handlers;
using ThmCommon.Models;
using ThmTPWin.Controllers;
using ThmTPWin.Models;
using ThmTPWin.ViewModels;
using ThmTPWin.Views;

namespace ThmTPWin {
    /// <summary>
    /// Interaction logic for TradingPMainWin.xaml
    /// </summary>
    public partial class TradingPMainWin : Window {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        internal static ConnectorManager ConnMgr => LoginView.ConnMgr;

        // <instrument : UI>
        private static readonly Dictionary<ThmInstrumentInfo, ITrader> _tradeWidgetDic = new Dictionary<ThmInstrumentInfo, ITrader>();

        private static OrderBookUsrCtrl _orderbookUsrCtrl;
        private int _orderbookIdx = -1;

        private static AuditTrailUsrCtrl _auditTrailUsrCtrl;
        private int _auditTrailIdx = -1;

        private static FillsUsrCtrl _fillsUsrCtrl;
        private int _fillsIdx = -1;

        private readonly TradingPMainWinVM _vm;
        public TradingPMainWin() {
            InitializeComponent();

            try {
                ConnMgr.Load();

                _vm = new TradingPMainWinVM(ConnMgr.ThmCfg);
                DataContext = _vm;
            }
            catch (Exception ex) {
                MessageBox.Show("Error: " + ex.Message);
                Close();
            }
        }

        private void Window_Loaded(object sender, RoutedEventArgs e) {
            _orderbookUsrCtrl = new OrderBookUsrCtrl(this);
            _fillsUsrCtrl = new FillsUsrCtrl(this);
            _auditTrailUsrCtrl = new AuditTrailUsrCtrl();

            InstrumentHandlerBase.OnOrderDataUpdated += OnOrderDataUpdated;

            if (Login()) {
                OrderBook_Click(null, null);
                AuditTrail_Click(null, null);
                Fills_Click(null, null);
            }
            else {
                Close();
            }
        }

        private bool Login() {
            try {
                var login = new LoginView() {
                    Owner = this,
                };

                if (!login.Init(out var err)) {
                    MessageBox.Show("Error: " + err);
                    return false;
                }

                var rlt = login.ShowDialog();
                return rlt.Value;
            }
            catch (Exception ex) {
                MessageBox.Show("Error: " + ex.Message);
                return false;
            }
        }

        private void MDTrader_Click(object sender, RoutedEventArgs e) {
            var cfgWin = new InstrumentSelectionWin() {
                Owner = this,
            };

            var rlt = cfgWin.ShowDialog();
            if (rlt.Value) {
                OpenMDTrader(cfgWin.SelectedInstrumentHandler);
            }
        }

        private void OpenMDTrader(InstrumentHandlerBase instrumentHandler, bool shown = true) {
            if (!_tradeWidgetDic.ContainsKey(instrumentHandler.InstrumentInfo)
                || _tradeWidgetDic[instrumentHandler.InstrumentInfo] == null) {
                var usrCtrl = new MDTraderUsrCtrl(instrumentHandler);
                if (shown) {
                    var tabItem = new TabItem() {
                        Header = instrumentHandler.InstrumentInfo.InstrumentID,
                        Content = usrCtrl,
                    };

                    tradeTabCtrl.SelectedIndex = tradeTabCtrl.Items.Add(tabItem);
                }

                _tradeWidgetDic[instrumentHandler.InstrumentInfo] = usrCtrl;

                //UpdateNetPosition(instrumentHandler.InstrumentInfo.InstrumentID);
                usrCtrl.SetPosition(instrumentHandler.GetPosition());
            }
            else {
                int idx = TraderOpened(instrumentHandler.InstrumentInfo.InstrumentID, shown);
                if (idx < 0 && shown) {
                    var tabItem = new TabItem() {
                        Header = instrumentHandler.InstrumentInfo.InstrumentID,
                        Content = _tradeWidgetDic[instrumentHandler.InstrumentInfo],
                    };

                    tradeTabCtrl.SelectedIndex = tradeTabCtrl.Items.Add(tabItem);
                }
            }
        }

        private void Autospreader_Click(object sender, RoutedEventArgs e) {
            var cfgWin = new AutospreaderSettingWin() {
                Owner = this,
            };
            var rlt = cfgWin.ShowDialog();
            if (rlt.Value) {
                OpenAutospeaderTrader(cfgWin.SelectedAS, cfgWin.OpenWithLegs);
            }
        }

        private int TraderOpened(string instrumentID, bool shown = true) {
            for (int i = 0; i < tradeTabCtrl.Items.Count; ++i) {
                var tabItm = tradeTabCtrl.Items[i] as TabItem;
                if (tabItm.Header.ToString() == instrumentID) {
                    if (shown) {
                        tradeTabCtrl.SelectedIndex = i;
                        tabItm.Visibility = Visibility.Visible;
                    }

                    return i;
                }
            }

            return -1;
        }

        private void OpenAutospeaderTrader(AutospeaderParas asItem, bool isOpenWithLegs) {
            asItem.IsEnabled = false;

            int idx = TraderOpened(asItem.InstrumentInfo.InstrumentID, true);
            if (idx >= 0) {
                return;
            }

            if (!_tradeWidgetDic.ContainsKey(asItem.InstrumentInfo)) {
                var usrCtrl = new ASTraderUsrCtrl(asItem);
                var tabItem = new TabItem() {
                    Header = asItem.InstrumentInfo.InstrumentID,
                    Content = usrCtrl,
                };

                foreach (var leg in asItem.ASLegs) {
                    OpenMDTrader(leg.InstrumentHandler, isOpenWithLegs);
                }

                idx = tradeTabCtrl.Items.Add(tabItem);
                tradeTabCtrl.SelectedIndex = idx;

                _tradeWidgetDic[asItem.InstrumentInfo] = usrCtrl;
            }
            else {
                var tabItem = new TabItem() {
                    Header = asItem.InstrumentInfo.InstrumentID,
                    Content = _tradeWidgetDic[asItem.InstrumentInfo],
                };

                foreach (var leg in asItem.ASLegs) {
                    OpenMDTrader(leg.InstrumentHandler, isOpenWithLegs);
                }

                idx = tradeTabCtrl.Items.Add(tabItem);
                tradeTabCtrl.SelectedIndex = idx;
            }
        }

        public void OnOrderDataUpdated(OrderData orderData) {
            _orderbookUsrCtrl.OnOrderDataUpdated(orderData);
            _fillsUsrCtrl.OnOrderDataUpdated(orderData);
            _auditTrailUsrCtrl.OnOrderDataUpdated(orderData);
        }

        private void CloseTabItem_Click(object sender, RoutedEventArgs e) {
            var id = (string)(e.Source as Button).DataContext;

            for (int i = tradeTabCtrl.Items.Count - 1; i >= 0; --i) {
                var tabItm = tradeTabCtrl.Items[i] as TabItem;
                if (tabItm.Header.ToString() == id) {
                    //foreach (var pair in _tradeWidgetDic) {
                    //    if (pair.Key.InstrumentID == id) {
                    //        foreach (var handler in pair.Value.GetInstrumentHandlers()) {
                    //            RemoveOrderUpdateHandler(handler);
                    //        }
                    //        pair.Value.Dispose();
                    //        _tradeWidgetDic.Remove(pair.Key);
                    //        break;
                    //    }
                    //}

                    tradeTabCtrl.Items.RemoveAt(i);
                    //tabItm.Visibility = Visibility.Collapsed;
                    tradeTabCtrl.SelectedIndex = i - 1;
                    return;
                }
            }
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
            if (!_tradeWidgetDic.ContainsKey(aov.InstrumentInfo)) {
                Logger.Error("No instrument handler found for " + aov.InstrumentInfo.InstrumentID);
                return;
            }

            if (aov.IsAlgo) {
                _tradeWidgetDic[aov.InstrumentInfo].DeleteAlgo(aov.AlgoID);
            }
            else {
                _tradeWidgetDic[aov.InstrumentInfo].DeleteOrder(aov.OrderID, aov.BuySell == EBuySell.Buy);
            }
        }

        internal void IncreaseAlgo(string instrumentID, decimal price) {
            //_tradeWidgetDic[instrumentID].Item1.IncreaseAlgo(price);
        }

        internal void DecreaseAlgo(string instrumentID, decimal price) {
            foreach (var pair in _tradeWidgetDic) {
                if (pair.Key.InstrumentID == instrumentID) {
                    pair.Value.DecreaseAlgo(price);
                    return;
                }
            }
        }

        private void OrderBook_Click(object sender, RoutedEventArgs e) {
            if (_orderbookIdx <= -1) {
                var tabItem = new TabItem() {
                    Header = OrderBookUsrCtrl.ID,
                    Content = _orderbookUsrCtrl
                };

                _orderbookIdx = statusTabCtrl.Items.Add(tabItem);
            }
            statusTabCtrl.SelectedIndex = _orderbookIdx;
        }

        private void AuditTrail_Click(object sender, RoutedEventArgs e) {
            if (_auditTrailIdx <= -1) {
                var tabItm = new TabItem {
                    Header = AuditTrailUsrCtrl.ID,
                    Content = _auditTrailUsrCtrl
                };

                _auditTrailIdx = statusTabCtrl.Items.Add(tabItm);
            }

            statusTabCtrl.SelectedIndex = _auditTrailIdx;
        }

        private void Fills_Click(object sender, RoutedEventArgs e) {
            if (_fillsIdx < 0) {
                var tabItm = new TabItem {
                    Header = FillsUsrCtrl.ID,
                    Content = _fillsUsrCtrl,
                };

                _fillsIdx = statusTabCtrl.Items.Add(tabItm);
            }

            statusTabCtrl.SelectedIndex = _fillsIdx;
        }

        internal void UpdateNetPosition(string instrumentID) {
            foreach (var pair in _tradeWidgetDic) {
                if (pair.Key.InstrumentID == instrumentID) {
                    pair.Value.SetPosition(pair.Value.GetInstrumentHandler().GetPosition());
                    return;
                }
            }
        }

        internal static int GetProductPosition(string product) {
            var pos = 0;
            foreach (var pair in _tradeWidgetDic) {
                if (pair.Key.Product == product) {
                    pos += pair.Value.GetInstrumentHandler().GetPosition();
                }
            }

            return pos;
        }

        private void TitanChangePassword_Click(object sender, RoutedEventArgs e) {
            var conn = (ThmTitanIntegrator.TitanHandler.TitanConnector)ConnMgr.GetConnector(ThmCommon.Config.EProviderType.TITAN);
            if (conn == null || !conn.IsConnected) {
                MessageBox.Show("Titan not connected.");
                return;
            }

            var dlg = new Views.TitanViews.PasswordChangeWin(conn) {
                Owner = this,
            };

            var rlt = dlg.ShowDialog();
            if (rlt.Value) {
                Logger.Info("Changed password for Titan");
            }
        }

        private void Exit_Click(object sender, RoutedEventArgs e) {
            Close();
        }

        private void About_Click(object sender, RoutedEventArgs e) {
            new AboutWin() {
                Owner = this
            }.ShowDialog();
        }

        private void Window_Closed(object sender, EventArgs e) {
            InstrumentHandlerBase.OnOrderDataUpdated -= OnOrderDataUpdated;

            ConnMgr.Dispose();
        }
    }
}
