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
using System.Windows;
using ThmCommon.Models;
using ThmTPWin.ViewModels;
using ThmTPWin.Views;
using ThmTPWin.Views.LoginViews;

namespace ThmTPWin {
    /// <summary>
    /// Interaction logic for TradingPMainWin.xaml
    /// </summary>
    public partial class TradingPMainWin : Window {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private readonly TradingPMainWinVM _vm;
        public TradingPMainWin() {
            InitializeComponent();

            _vm = new TradingPMainWinVM();
            DataContext = _vm;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e) {
            _vm.InitOrdersTabItms();

            if (!Login()) {
                Close();
            }
        }

        private static LoginView _loginView;
        private bool Login() {
            try {
                if (_loginView == null) {
                    _loginView = new LoginView() {
                        Owner = this,
                    };
                }

                if (!_loginView.Init(out var err)) {
                    MessageBox.Show("Error: " + err);
                    return false;
                }

                var rlt = _loginView.ShowDialog();
                if (rlt.Value) {
                    _vm.IsTitanEnabled = _loginView.IsChecked(EProviderType.TITAN);
                    return true;
                }

                return false;
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
                _vm.AddMDTrader(cfgWin.SelectedInstrument);
            }
        }

        private void Autospreader_Click(object sender, RoutedEventArgs e) {
            var cfgWin = new AutospreaderSettingWin() {
                Owner = this,
            };

            var rlt = cfgWin.ShowDialog();
            if (rlt.Value) {
                _vm.AddASTrader(cfgWin.SelectedAS, cfgWin.OpenWithLegs);
            }
        }

        private void TradeWdigetClose_Click(object sender, RoutedEventArgs e) {
            TradingPMainWinVM.TradeWidgetTabItms.Remove(_vm.SelectedTradeTabItm);
        }

        private void TitanChangePassword_Click(object sender, RoutedEventArgs e) {
            var dlg = new PasswordChangeWin() {
                Owner = this,
            };

            var rlt = dlg.ShowDialog();
            if (rlt.Value) {
                Logger.Info("Changed password for Titan");
                MessageBox.Show("Change OUCH password successfully.");
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
            _loginView?.Dispose();

            _vm?.Dispose();
        }
    }
}
