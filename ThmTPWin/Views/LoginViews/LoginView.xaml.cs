//-----------------------------------------------------------------------------
// File Name   : LoginView
// Author      : junlei
// Date        : 5/29/2020 8:35:13 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Windows;
using ThmCommon.Models;
using ThmTPWin.ViewModels.LoginViewModels;

namespace ThmTPWin.Views.LoginViews {
    /// <summary>
    /// Interaction logic for LoginView.xaml
    /// </summary>
    public partial class LoginView : Window {
        private readonly LoginVM _vm;
        public LoginView() {
            InitializeComponent();
            _vm = new LoginVM();
            DataContext = _vm;
        }

        internal bool Init(out string err) {
            return _vm.Init(out err);
        }

        public bool IsChecked(EProviderType providerType) {
            return _vm.IsChecked(providerType);
        }

        private async void BtnOK_Click(object sender, RoutedEventArgs e) {
            Cursor = System.Windows.Input.Cursors.Wait;

            if (!_vm.IsValid(out var err)) {
                Cursor = null;
                MessageBox.Show($"Error: {err}", "Login", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            var rlt = await _vm.StartAsync();
            if (rlt) {
                DialogResult = true;
                //_connMgr.SaveConfig();
            }

            Cursor = null;
        }

        private void BtnCancel_Click(object sender, RoutedEventArgs e) {
            DialogResult = false;
        }

        internal void Dispose() {
            _vm.Dispose();
        }
    }
}
