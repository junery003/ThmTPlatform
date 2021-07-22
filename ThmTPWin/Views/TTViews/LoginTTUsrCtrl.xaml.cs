//-----------------------------------------------------------------------------
// File Name   : LoginTTUsrCtrl
// Author      : junlei
// Date        : 5/20/2020 9:04:37 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Windows.Controls;
using ThmTPWin.ViewModels.TTViewModels;
using ThmTTIntegrator.TTHandler;

namespace ThmTPWin.Views.TTViews {
    /// <summary>
    /// Interaction logic for LoginWin.xaml
    /// </summary>
    public partial class LoginTTUsrCtrl : UserControl {
        private readonly LoginTTVM _vm;

        public LoginTTUsrCtrl(TTAccount ttAccount) {
            InitializeComponent();

            _vm = new LoginTTVM(ttAccount);
            DataContext = _vm;
        }

        internal bool Check(out string err) {
            return _vm.Check(out err);
        }
    }
}
