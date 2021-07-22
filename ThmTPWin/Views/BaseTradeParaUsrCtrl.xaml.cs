//-----------------------------------------------------------------------------
// File Name   : BaseTradeParaUsrCtrl
// Author      : junlei
// Date        : 10/12/2020 6:34:00 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using ThmCommon.Handlers;
using ThmCommon.Models;
using ThmTPWin.Controllers;
using ThmTPWin.ViewModels;

namespace ThmTPWin.Views {
    /// <summary>
    /// Interaction logic for BaseTradeParaUsrCtrl.xaml
    /// </summary>
    public partial class BaseTradeParaUsrCtrl : UserControl {
        public EAlgoType SelectedAlgoType {
            get => _vm.SelectedAlgoType;
            set => _vm.SelectedAlgoType = value;
        }

        public int Quantity {
            get => _vm.Quantity;
            set => _vm.Quantity = value;
        }

        public string QtyTip {
            get => _vm.QtyTip;
            set => _vm.QtyTip = value;
        }

        public Brush QtyBackground {
            get => _vm.QtyBackground;
            set => _vm.QtyBackground = value;
        }

        public int Position {
            get => _vm.Position;
            set => _vm.Position = value;
        }

        private ITrader _parent;
        private BaseTradeParaVM _vm;
        public BaseTradeParaUsrCtrl() {
            InitializeComponent();
        }

        internal void Init(ITrader parent, List<EAlgoType> algos, InstrumentHandlerBase instrumentHandler) {
            _parent = parent;

            _vm = new BaseTradeParaVM(algos, instrumentHandler);
            DataContext = _vm;
        }

        internal void ResetQuantity() {
            Quantity = _vm.MinQuantity;
        }

        private void Quantity_Click(object sender, RoutedEventArgs e) {
            var btn = (Button)sender;
            if (btn.Content.ToString() == "CLR") {
                _vm.Quantity = 0;
            }
            else if (int.TryParse(btn.Content.ToString(), out var qty)) {
                _vm.Quantity += qty;
            }
        }

        private void AlgoCmbox_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            _parent.DispalyAlgoView(_vm.SelectedAlgoType);
        }

        private void NumberOnlyTxtb_PreviewTextInput(object sender, TextCompositionEventArgs e) {
            e.Handled = System.Text.RegularExpressions.Regex.IsMatch(e.Text, "[^0-9]+$");
        }
    }
}
