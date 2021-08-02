//-----------------------------------------------------------------------------
// File Name   : ASTraderUsrCtrl
// Author      : junlei
// Date        : 10/12/2020 05:03:17 PM
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
    /// Interaction logic for ASTraderUsrCtrl.xaml
    /// </summary>
    public partial class ASTraderUsrCtrl : UserControl {
        public ASTraderUsrCtrl() {
            InitializeComponent();
        }

        private void RecenterMenuItem_Click(object sender, RoutedEventArgs e) {
            LadderUsrCtrl.RecenterPriceLadder();
        }

        private void NumberOnlyTxtb_PreviewTextInput(object sender, TextCompositionEventArgs e) {
            e.Handled = System.Text.RegularExpressions.Regex.IsMatch(e.Text, "[^0-9]+");
        }
    }
}
