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
using ThmTPWin.ViewModels.AlgoViewModels;

namespace ThmTPWin.Views.AlgoViews {
    /// <summary>
    /// Interaction logic for TriggerWin.xaml
    /// </summary>
    public partial class TriggerWin : Window {
        private readonly TriggerVM _vm;
        internal TriggerWin(TriggerVM vm) {
            InitializeComponent();

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

        private void CancelBtn_Click(object sender, RoutedEventArgs e) {
            Hide();
        }

        private void Qty_PreviewTextInput(object sender, System.Windows.Input.TextCompositionEventArgs e) {
            e.Handled = System.Text.RegularExpressions.Regex.IsMatch(e.Text, "[^0-9]+$");
        }
    }
}
