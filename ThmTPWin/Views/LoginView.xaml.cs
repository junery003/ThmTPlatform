//-----------------------------------------------------------------------------
// File Name   : LoginView
// Author      : junlei
// Date        : 5/29/2020 8:35:13 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using ThmAtpIntegrator.AtpFunctions;
using ThmAtpIntegrator.AtpHandler;
using ThmCommon.Config;
using ThmTitanIntegrator.TitanFunctions;
using ThmTitanIntegrator.TitanHandler;
using ThmTPWin.Controllers;
using ThmTPWin.ViewModels.LoginViewModels;
using ThmTPWin.Views.AtpViews;
using ThmTPWin.Views.TitanViews;
using ThmTPWin.Views.TTViews;
using ThmTTIntegrator.TTHandler;

namespace ThmTPWin.Views {
    /// <summary>
    /// Interaction logic for LoginView.xaml
    /// </summary>
    public partial class LoginView : Window {
        internal static ConnectorManager ConnMgr { get; } = new ConnectorManager();

        private readonly Dictionary<EProviderType, TabItem> _loginUsrCtrls = new Dictionary<EProviderType, TabItem>();
        
        private readonly LoginVM _vm = new LoginVM();
        internal LoginView() {
            InitializeComponent();
            DataContext = _vm;

            Closed += LoginView_Closed;
            _vm.ProcessLogs.CollectionChanged += ProcessLogs_CollectionChanged;
        }

        internal bool Init(out string err) {
            err = string.Empty;

            if (ConnMgr.ThmCfg.AtpEnabled) {
                if (!InitAtp(ref err)) {
                    return false;
                }
            }

            if (ConnMgr.ThmCfg.TTEnabled) {
                if (!InitTt(ref err)) {
                    return false;
                }
            }

            if (ConnMgr.ThmCfg.TitanEnabled) {
                if (!InitTitan(ref err)) {
                    return false;
                }
            }

            _vm.AddProgess("Program started");
            return true;
        }

        private bool InitAtp(ref string err) {
            var atpConn = new AtpConnector();
            if (!atpConn.Init()) {
                err = "ATP config not valid";
                return false;
            }
            ConnMgr.AddConnector(EProviderType.ATP, atpConn);

            AtpConfig cfg = ConnMgr.GetConfig(EProviderType.ATP) as AtpConfig;
            var header = new CheckBox {
                Content = "ATP",
                IsChecked = cfg.Enabled
            };
            header.Click += ChkboxATP_Click;

            var loginTabItm = new TabItem {
                Header = header,
                Content = new LoginAtpUsrCtrl(cfg.AtpLogins)
            };

            tabLogin.Items.Add(loginTabItm);
            _loginUsrCtrls[EProviderType.ATP] = loginTabItm;
            _vm.LoginCount++;
            return true;
        }

        private bool InitTt(ref string err) {
            var ttConn = new TTConnector();
            if (!ttConn.Init()) {
                err = "TT config not valid";
                return false;
            }
            ConnMgr.AddConnector(EProviderType.TT, ttConn);

            var cfg = ConnMgr.GetConfig(EProviderType.TT) as TTConfig;

            var header = new CheckBox {
                Content = "TT",
                IsChecked = cfg.Enabled
            };
            header.Click += ChkboxTT_Click;

            var loginTabItm = new TabItem {
                Header = header,
                Content = new LoginTTUsrCtrl(cfg.TTLogin)
            };

            tabLogin.Items.Add(loginTabItm);

            _loginUsrCtrls[EProviderType.TT] = loginTabItm;
            _vm.LoginCount++;
            return true;
        }

        private bool InitTitan(ref string err) {
            var titanConn = new TitanConnector();
            if (!titanConn.Init()) {
                err = "Titan config not valid";
                return false;
            }
            ConnMgr.AddConnector(EProviderType.TITAN, titanConn);

            var cfg = ConnMgr.GetConfig(EProviderType.TITAN) as TitanConfig;

            var header = new CheckBox {
                Content = "Titan",
                IsChecked = cfg.Enabled
            };
            header.Click += ChkboxTitan_Click;

            var loginTabItm = new TabItem {
                Header = header,
                Content = new LoginTitanUsrCtrl(cfg.TitanLogin)
            };

            tabLogin.Items.Add(loginTabItm);
            _loginUsrCtrls[EProviderType.TITAN] = loginTabItm;
            _vm.LoginCount++;
            return true;
        }

        private void LoginView_Closed(object sender, EventArgs e) {
            _vm.ProcessLogs.CollectionChanged -= ProcessLogs_CollectionChanged;
        }

        private void ProcessLogs_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e) {
            if (DGProgress.Items.Count > 0) {
                DGProgress.ScrollIntoView(DGProgress.Items[DGProgress.Items.Count - 1]);
                DGProgress.UpdateLayout();
            }
        }

        private void ChkboxATP_Click(object sender, RoutedEventArgs e) {
            var tabItm = _loginUsrCtrls[EProviderType.ATP];
            bool isChecked = ((CheckBox)tabItm.Header).IsChecked.Value;
            if (isChecked) {
                tabLogin.SelectedItem = tabItm;
            }

            ((UserControl)tabItm.Content).IsEnabled = isChecked;
            ConnMgr.Enable(EProviderType.ATP, isChecked);

            if (isChecked) {
                ++_vm.LoginCount;
            }
            else {
                --_vm.LoginCount;
            }
        }

        private void ChkboxTT_Click(object sender, RoutedEventArgs e) {
            var tabItm = _loginUsrCtrls[EProviderType.TT];
            bool isChecked = ((CheckBox)tabItm.Header).IsChecked.Value;
            if (isChecked) {
                tabLogin.SelectedItem = tabItm;
            }

            ((UserControl)tabItm.Content).IsEnabled = isChecked;
            ConnMgr.Enable(EProviderType.TT, isChecked);

            if (isChecked) {
                ++_vm.LoginCount;
            }
            else {
                --_vm.LoginCount;
            }
        }

        private void ChkboxTitan_Click(object sender, RoutedEventArgs e) {
            var tabItm = _loginUsrCtrls[EProviderType.TITAN];
            bool isChecked = ((CheckBox)tabItm.Header).IsChecked.Value;
            if (isChecked) {
                tabLogin.SelectedItem = tabItm;
            }

            ((UserControl)tabItm.Content).IsEnabled = isChecked;
            ConnMgr.Enable(EProviderType.TITAN, isChecked);

            if (isChecked) {
                ++_vm.LoginCount;
            }
            else {
                --_vm.LoginCount;
            }
        }

        private async void BtnOK_Click(object sender, RoutedEventArgs e) {
            _vm.LoginEnabled = false;
            Cursor = System.Windows.Input.Cursors.Wait;

            if (!IsValid()) {
                Cursor = null;
                return;
            }

            _vm.AddProgess("Initializing connection(s)...");

            var rlt = await InitAsync();
            if (rlt) {
                DialogResult = true;
                //_connMgr.SaveConfig();
            }

            Cursor = null;
        }

        private bool IsValid() {
            if (ConnMgr.IsEnabled(EProviderType.ATP)) {
                _vm.AddProgess("Checking ATP login info...");
                if (!((LoginAtpUsrCtrl)_loginUsrCtrls[EProviderType.ATP].Content).Check(out string err)) {
                    MessageBox.Show($"Error: {err}");
                    return false;
                }
            }

            if (ConnMgr.IsEnabled(EProviderType.TT)) {
                _vm.AddProgess("Checking TT login info...");
                if (!((LoginTTUsrCtrl)_loginUsrCtrls[EProviderType.TT].Content).Check(out string err)) {
                    MessageBox.Show($"Error: {err}");
                    return false;
                }
            }

            if (ConnMgr.IsEnabled(EProviderType.TITAN)) {
                _vm.AddProgess("Checking Titan login info...");
                if (!((LoginTitanUsrCtrl)_loginUsrCtrls[EProviderType.TITAN].Content).Check(out string err)) {
                    MessageBox.Show($"Error: {err}");
                    return false;
                }
            }

            return true;
        }

        private async Task<bool> InitAsync() {
            bool rlt = true;
            var tasks = new List<Task>();
            var tsk = Start(EProviderType.ATP);
            if (tsk != null) {
                tasks.Add(tsk);
            }

            tsk = Start(EProviderType.TT);
            if (tsk != null) {
                tasks.Add(tsk);
            }

            tsk = Start(EProviderType.TITAN);
            if (tsk != null) {
                tasks.Add(tsk);
            }

            await Task.WhenAll(tasks);
            if (rlt) {
                _vm.AddProgess("Finishing initialization...");
                Task.Delay(1000).Wait();
            }

            return rlt;
        }

        private Task Start(EProviderType providerType) {
            if (!ConnMgr.IsEnabled(providerType)) {
                return null;
            }

            return Task.Run(() => {
                UpdateProgress($"Initializing {providerType} connection...");
                if (!ConnMgr.GetConnector(providerType).Connect()) {
                    UpdateProgress($"Failed to init {providerType} connection");
                    return;
                }

                Task.Delay(8000).Wait();
                UpdateProgress($"{providerType} connection initialized");
            });
        }

        private void UpdateProgress(string msg) {
            Dispatcher.Invoke(() => _vm.AddProgess(msg));
            Task.Delay(100).Wait();
        }

        private void BtnCancel_Click(object sender, RoutedEventArgs e) {
            DialogResult = false;
        }
    }
}
