//-----------------------------------------------------------------------------
// File Name   : TtpMainWinVM
// Author      : junlei
// Date        : 6/7/2021 12:32:49 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using ThmTPWin.ViewControllers;

namespace ThmTPWin.Views {
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class TtpMainWin : Window {
        private readonly TtpMainWinVM _vm;
        public TtpMainWin() {
            InitializeComponent();

            _vm = new TtpMainWinVM();
            DataContext = _vm;
        }
    }
}
