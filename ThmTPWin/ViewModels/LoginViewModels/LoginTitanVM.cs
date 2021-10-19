//-----------------------------------------------------------------------------
// File Name   : LoginTitanVM
// Author      : junlei
// Date        : 5/27/2020 8:55:48 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Prism.Mvvm;
using ThmCommon.Config;
using ThmCommon.Models;

namespace ThmTPWin.ViewModels.LoginViewModels {
    public class LoginTitanVM : BindableBase, ILoginTabItm {
        public EProviderType Provider { get; } = EProviderType.TITAN;

        private bool _isChecked = true;
        public bool IsChecked {
            get => _isChecked;
            set => SetProperty(ref _isChecked, value);
        }

        private string _account;
        public string Account {
            get => _titanLogin.Account;
            set {
                if (SetProperty(ref _account, value)) {
                    _titanLogin.Account = value;
                }
            }
        }

        private string _customerInfo;
        public string CustomerInfo {
            get => _titanLogin.CustomerInfo;
            set {
                if (SetProperty(ref _customerInfo, value)) {
                    _titanLogin.CustomerInfo = value;
                }
            }
        }

        private readonly TitanLoginCfg _titanLogin;
        public LoginTitanVM(TitanLoginCfg titanLogin) {
            _titanLogin = titanLogin;
        }

        public bool Check(out string err) {
            err = string.Empty;
            return true;
        }
    }
}
