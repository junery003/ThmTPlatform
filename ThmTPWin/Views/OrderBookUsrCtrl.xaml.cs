//-----------------------------------------------------------------------------
// File Name   : OrderBookUsrCtrl
// Author      : junlei
// Date        : 4/23/2020 13:05:13 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Windows.Controls;

namespace ThmTPWin.Views {
    /// <summary>
    /// Interaction logic for OrderBookUsrCtrl.xaml
    /// </summary>
    public partial class OrderBookUsrCtrl : UserControl {
        public OrderBookUsrCtrl() {
            InitializeComponent();
        }

        private void SelectAllChkbox_Click(object sender, System.Windows.RoutedEventArgs e) {
            var vm = DataContext as ViewModels.OrderBookVM;
            var ckbox = sender as CheckBox;
            vm.SelectAll(ckbox.IsChecked.Value);
        }
    }
}
