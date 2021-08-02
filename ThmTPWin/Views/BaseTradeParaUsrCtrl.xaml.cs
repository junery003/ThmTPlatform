//-----------------------------------------------------------------------------
// File Name   : BaseTradeParaUsrCtrl
// Author      : junlei
// Date        : 10/12/2020 6:34:00 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using ThmCommon.Models;
using ThmTPWin.ViewModels;
using ThmTPWin.Views.AlgoViews;

namespace ThmTPWin.Views {
    /// <summary>
    /// Interaction logic for BaseTradeParaUsrCtrl.xaml
    /// </summary>
    public partial class BaseTradeParaUsrCtrl : UserControl {
        private TriggerWin _triggerWin = null;
        private InterTriggerWin _interTriggerWin = null;

        public BaseTradeParaUsrCtrl() {
            InitializeComponent();
        }

        private void Quantity_Click(object sender, RoutedEventArgs e) {
            var vm = DataContext as BaseTradeParaVM;
            var btn = (Button)sender;
            if (btn.Content.ToString() == "CLR") {
                vm.Quantity = 0;
            }
            else if (int.TryParse(btn.Content.ToString(), out var qty)) {
                vm.Quantity += qty;
            }
        }

        private void NumberOnlyTxtb_PreviewTextInput(object sender, TextCompositionEventArgs e) {
            e.Handled = System.Text.RegularExpressions.Regex.IsMatch(e.Text, "[^0-9]+");
        }

        private void AlgoCmbox_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            var vm = DataContext as BaseTradeParaVM;
            switch (vm.SelectedAlgoType) {
            case EAlgoType.Trigger: {
                ShowTrigger();
                break;
            }
            //case EAlgoType.PreOpen: {
            //    if (_preopenWin == null) {
            //        _preopenWin = new PreopenWin() {
            //            Owner = Window.GetWindow(this),
            //        };
            //    }
            //    _preopenWin.Show();
            //    break;
            //}
            case EAlgoType.Sniper: {
                break;
            }
            case EAlgoType.InterTrigger: {
                ShowInterTrigger();
                break;
            }
            default:
                break;
            }
        }

        internal void ShowTrigger() {
            var vm = DataContext as BaseTradeParaVM;
            vm.SelectedAlgoType = EAlgoType.Trigger;
            if (_triggerWin == null) {
                _triggerWin = new TriggerWin(vm.TriggerVm) {
                    Owner = Window.GetWindow(this),
                };
            }
            _triggerWin.Show();
        }

        internal void ShowInterTrigger() {
            var vm = DataContext as BaseTradeParaVM;
            vm.SelectedAlgoType = EAlgoType.InterTrigger;
            if (_interTriggerWin == null) {
                _interTriggerWin = new InterTriggerWin(vm.InterTriggerVm) {
                    Owner = Window.GetWindow(this),
                };
            }
            _interTriggerWin.Show();
        }
    }
}
