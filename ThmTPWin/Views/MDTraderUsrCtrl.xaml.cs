//-----------------------------------------------------------------------------
// File Name   : MDTraderUsrCtrl
// Author      : junlei
// Date        : 4/21/2020 12:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace ThmTPWin.Views {
    /// <summary>
    /// Interaction logic for MDTraderUsrCtrl.xaml
    /// </summary>
    public partial class MDTraderUsrCtrl : UserControl {
        internal MDTraderUsrCtrl() {
            InitializeComponent();
        }

        private void RecenterMenuItem_Click(object sender, RoutedEventArgs e) {
            LadderUsrCtrl.RecenterPriceLadder();
        }

        private void TriggerBtn_Click(object sender, RoutedEventArgs e) {
            TradeParaUsrCtrl.ShowTrigger();
        }

        private void InterTriggerBtn_Click(object sender, RoutedEventArgs e) {
            TradeParaUsrCtrl.ShowInterTrigger();
        }

        private void Price_PreViewKeyDown(object sender, KeyEventArgs e) {
        }

        private void Price_PreviewTextInput(object sender, TextCompositionEventArgs e) {
        }

        private void NumberOnlyTxtb_PreviewTextInput(object sender, TextCompositionEventArgs e) {
            e.Handled = System.Text.RegularExpressions.Regex.IsMatch(e.Text, "[^0-9]+$");
        }
    }
}
