//-----------------------------------------------------------------------------
// File Name   : PasswordChangeWin
// Author      : junlei
// Date        : 1/14/2021 2:26:05 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Windows;
using ThmTPWin.ViewModels.LoginViewModels;

namespace ThmTPWin.Views.LoginViews {
    /// <summary>
    /// Interaction logic for PasswordChangeWin.xaml
    /// </summary>
    public partial class PasswordChangeWin : Window {

        private readonly PasswordChangeVM _vm;
        public PasswordChangeWin() {
            InitializeComponent();

            _vm = new PasswordChangeVM(txtbCurPwd.BorderBrush);
            DataContext = _vm;
        }

        private async void OK_Click(object sender, RoutedEventArgs e) {
            string rlt = await _vm.ChangePasswordAsync();
            if (!string.IsNullOrEmpty(rlt)) {
                MessageBox.Show("Failed to change password: " + rlt);
                return;
            }

            DialogResult = true;
        }

        private void Cancel_Click(object sender, RoutedEventArgs e) {
            DialogResult = false;
        }
    }
}
