//-----------------------------------------------------------------------------
// File Name   : LoginTitanUsrCtrl
// Author      : junlei
// Date        : 12/9/2020 2:26:37 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Windows.Controls;
using ThmTitanIntegrator.TitanFunctions;
using ThmTPWin.ViewModels.TitanViewModels;

namespace ThmTPWin.Views.TitanViews {
    /// <summary>
    /// Interaction logic for LoginTitanUsrCtrl.xaml
    /// </summary>
    public partial class LoginTitanUsrCtrl : UserControl {
        private readonly LoginTitanVM _vm;
        public LoginTitanUsrCtrl(TitanAcount titanLogin) {
            InitializeComponent();

            _vm = new LoginTitanVM(titanLogin);
            DataContext = _vm;
        }

        internal bool Check(out string err) {
            err = string.Empty;
            return true;
        }
    }
}
