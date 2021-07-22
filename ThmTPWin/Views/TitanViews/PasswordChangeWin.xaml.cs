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
using ThmTPWin.ViewModels.TitanViewModels;

namespace ThmTPWin.Views.TitanViews {
    /// <summary>
    /// Interaction logic for PasswordChangeWin.xaml
    /// </summary>
    public partial class PasswordChangeWin : Window {

        private readonly PasswordChangeVM _vm;
        public PasswordChangeWin(ThmTitanIntegrator.TitanHandler.TitanConnector connector) {
            InitializeComponent();

            _vm = new PasswordChangeVM(connector, txtbCurPwd.BorderBrush);
            DataContext = _vm;
        }

        private void OK_Click(object sender, RoutedEventArgs e) {
            if (_vm.ChangePassword()) {
                MessageBox.Show("Change OUCH password successfully.");
                DialogResult = true;
            }
            else {
                MessageBox.Show("Failed to change password");
            }
        }

        private void Cancel_Click(object sender, RoutedEventArgs e) {
            DialogResult = false;
        }
    }
}
