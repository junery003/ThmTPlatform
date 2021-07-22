//-----------------------------------------------------------------------------
// File Name   : LoginAtpUsrCtrl
// Author      : junlei
// Date        : 5/27/2020 9:04:37 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Collections.Generic;
using System.Windows.Controls;
using ThmAtpIntegrator.AtpFunctions;
using ThmTPWin.ViewModels.AtpViewModels;

namespace ThmTPWin.Views.AtpViews {
    /// <summary>
    /// Interaction logic for LoginAtpWin.xaml
    /// </summary>
    public partial class LoginAtpUsrCtrl : UserControl {
        internal bool Enabled { get; }
        private readonly LoginAtpVM _vm;

        public LoginAtpUsrCtrl(List<AtpAcount> atpLogins) {
            InitializeComponent();

            _vm = new LoginAtpVM(atpLogins);
            DataContext = _vm;
        }

        internal bool Check(out string err) {
            err = _vm.Check();

            return err == null;
        }
    }
}
