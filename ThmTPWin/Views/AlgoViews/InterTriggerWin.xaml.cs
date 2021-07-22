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
using System.Windows.Controls;
using System.Windows.Input;
using ThmCommon.Handlers;
using ThmTPWin.ViewModels.AlgoViewModels;

namespace ThmTPWin.Views.AlgoViews {
    /// <summary>
    /// Interaction logic for InterTriggerWin.xaml
    /// </summary>
    public partial class InterTriggerWin : Window {
        public InstrumentHandlerBase RefInstrumentHandler { get; private set; }

        private readonly MDTraderUsrCtrl _parent;
        private readonly InterTriggerVM _vm;
        internal InterTriggerWin(MDTraderUsrCtrl mdTraderUsrCtrl, InterTriggerVM vm) {
            InitializeComponent();

            _parent = mdTraderUsrCtrl;

            _vm = vm;
            DataContext = _vm;
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e) {
            e.Cancel = true;
            Hide();
        }

        private void OKBtn_Click(object sender, RoutedEventArgs e) {
            if (!Check(out string err)) {
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
            if (!instrumentSelectionUsrCtrl.Select(out string err)) {
                MessageBox.Show(err);

                return;
            }

            var tmp = instrumentSelectionUsrCtrl.InstrumentHandler;
            if (!_vm.UpdateRefInstrument(tmp.InstrumentInfo.InstrumentID, out err)) {
                MessageBox.Show("Failed to set reference instrument: " + err);
                return;
            }

            RefInstrumentHandler = tmp;
        }

        internal bool Check(out string err) {
            if (RefInstrumentHandler == null) {
                err = "The reference instrument is not specified";
                return false;
            }

            if (!_vm.Check(out err)) {
                return false;
            }

            return true;
        }

        private void PriceTypeCmb_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            if (_parent == null) {
                return;
            }

            _parent.RefPriceTypeCmb.SelectedValue = (sender as ComboBox).SelectedValue;
        }

        private void OperatorCmb_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            if (_parent == null) {
                return;
            }

            _parent.RefOperatorCmb.SelectedValue = (sender as ComboBox).SelectedValue;
        }

        private void RefPriceTxt_TextChanged(object sender, TextChangedEventArgs e) {
            if (_parent == null) {
                return;
            }

            var txtb = (sender as TextBox).Text;
            if (!decimal.TryParse(txtb, out var _)) {
                txtb = "0";
            }

            _parent.RefPriceTxt.Text = txtb;
        }
    }
}
