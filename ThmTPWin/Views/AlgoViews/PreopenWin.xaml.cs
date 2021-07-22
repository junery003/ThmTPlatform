//-----------------------------------------------------------------------------
// File Name   : PreopenWin
// Author      : junlei
// Date        : 4/22/2020 4:13:05 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Windows;
using ThmTPWin.ViewModels.AlgoViewModels;
using ThmCommon.Models;

namespace ThmTPWin.Views.AlgoViews {
    /// <summary>
    /// Interaction logic for PreopenWin.xaml
    /// </summary>
    public partial class PreopenWin : Window {
        private readonly AlgoData _preopenPara = new AlgoData(EAlgoType.PreOpen);
        public AlgoData PreopenPara {
            get {
                _preopenPara.Price = _vm.Price;
                _preopenPara.Qty = _vm.Qty;
                //_preopenPara.Price2 = double.Parse(VM.Price2);
                //_preopenPara.Qty2 = int.Parse(VM.Qty2);

                return _preopenPara;
            }
            set { }
        }

        private readonly PreopenVM _vm;
        public PreopenWin() {
            InitializeComponent();

            _vm = new PreopenVM();
            DataContext = _vm;
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e) {
            e.Cancel = true;
            Hide(); //Visibility = Visibility.Hidden;
        }

        private void Close_Button_Click(object sender, RoutedEventArgs e) {
            Hide();
        }
    }
}
