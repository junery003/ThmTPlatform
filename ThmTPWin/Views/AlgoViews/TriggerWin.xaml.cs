//-----------------------------------------------------------------------------
// File Name   : TriggerWin
// Author      : junlei
// Date        : 4/22/2020 4:03:05 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Windows;
using System.Windows.Controls;
using ThmTPWin.ViewModels.AlgoViewModels;

namespace ThmTPWin.Views.AlgoViews {
    /// <summary>
    /// Interaction logic for TriggerWin.xaml
    /// </summary>
    public partial class TriggerWin : Window {
        private readonly MDTraderUsrCtrl _parent;
        private readonly TriggerVM _vm;
        internal TriggerWin(MDTraderUsrCtrl mdTraderUsrCtrl, TriggerVM vm) {
            InitializeComponent();

            _parent = mdTraderUsrCtrl;
            _vm = vm;
            DataContext = _vm;
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e) {
            e.Cancel = true;
            Visibility = Visibility.Hidden;
        }

        private void OKBtn_Click(object sender, RoutedEventArgs e) {
            Hide();
        }

        private void Qty_TextChanged(object sender, TextChangedEventArgs e) {
            if (_parent == null) {
                return;
            }

            var txtb = (sender as TextBox).Text;
            if (!int.TryParse(txtb, out var _)) {
                txtb = "0";
            }

            _parent.TriggerQtyTxtb.Text = txtb;
        }

        private void Qty_PreviewTextInput(object sender, System.Windows.Input.TextCompositionEventArgs e) {
            e.Handled = System.Text.RegularExpressions.Regex.IsMatch(e.Text, "[^0-9]+$");
        }
    }
}
