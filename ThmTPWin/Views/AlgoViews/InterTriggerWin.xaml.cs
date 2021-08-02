//-----------------------------------------------------------------------------
// File Name   : InterTriggerWin
// Author      : junlei
// Date        : 9/8/2020 6:01:29 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Windows;
using System.Windows.Input;
using ThmTPWin.ViewModels.AlgoViewModels;

namespace ThmTPWin.Views.AlgoViews {
    /// <summary>
    /// Interaction logic for InterTriggerWin.xaml
    /// </summary>
    public partial class InterTriggerWin : Window {
        private readonly InterTriggerVM _vm;
        internal InterTriggerWin(InterTriggerVM vm) {
            InitializeComponent();

            _vm = vm;
            DataContext = _vm;
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e) {
            e.Cancel = true;
            Hide();
        }

        private void OKBtn_Click(object sender, RoutedEventArgs e) {
            if (!_vm.Check(out var err)) {
                MessageBox.Show(err);
                return;
            }

            Hide();
        }

        private void CancelBtn_Click(object sender, RoutedEventArgs e) {
            Hide();
        }

        private void Price_PreviewTextInput(object sender, TextCompositionEventArgs e) {
            e.Handled = !System.Text.RegularExpressions.Regex.IsMatch(e.Text, @"[0-9.]");
        }

        private void Price_PreViewKeyDown(object sender, KeyEventArgs e) {
            e.Handled = e.Key == Key.Space;
        }

        private void SetAsRef_Click(object sender, RoutedEventArgs e) {
            if (!instrumentSelectionUsrCtrl.Select(out var err)) {
                MessageBox.Show(err);
                return;
            }

            var tmp = instrumentSelectionUsrCtrl.InstrumentHandler;
            if (!_vm.UpdateRefInstrument(tmp.InstrumentInfo.InstrumentID, out err)) {
                MessageBox.Show("Failed to set reference instrument: " + err);
                return;
            }

            _vm.RefInstrumentHandler = tmp;
        }
    }
}
