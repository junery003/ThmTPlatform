//-----------------------------------------------------------------------------
// File Name   : LoginCtpVM
// Author      : junlei
// Date        : 8/27/2021 8:55:48 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Prism.Mvvm;
using System.Collections.ObjectModel;
using ThmCommon.Config;
using ThmCommon.Models;

namespace ThmTPWin.ViewModels.LoginViewModels {
    public class LoginCtpVM : BindableBase, ILoginTabItm {
        public EProviderType Provider { get; } = EProviderType.CTP;

        private bool _isChecked = true;
        public bool IsChecked {
            get => _isChecked;
            set => SetProperty(ref _isChecked, value);
        }

        private string _userId;
        public string UserId {
            get => _userId;
            set => SetProperty(ref _userId, value);
        }

        private string _password;
        public string Password {
            get => _password;
            set { SetProperty(ref _password, value); }
        }

        private CtpLoginCfg _selectedAccount;
        public CtpLoginCfg SelectedAccount {
            get => _selectedAccount;
            set {
                if (SetProperty(ref _selectedAccount, value)) {
                    UserId = _selectedAccount.UserId;
                    Password = _selectedAccount.Password;
                }
            }
        }

        public ObservableCollection<CtpLoginCfg> AllAccounts { get; }
        public LoginCtpVM(CtpLoginCfg ctpLogin) {
            AllAccounts = new ObservableCollection<CtpLoginCfg> {
                ctpLogin
            };

            SelectedAccount = ctpLogin;
        }

        public bool Check(out string err) {
            if (SelectedAccount.Enabled) {
                if (string.IsNullOrWhiteSpace(UserId)) {
                    err = $"{SelectedAccount.UserId} Please specify the User ID";
                    return false;
                }

                if (string.IsNullOrWhiteSpace(Password)) {
                    err = $"{SelectedAccount.UserId} Please specify the Password";
                    return false;
                }
            }

            err = string.Empty;
            return true;
        }
    }
}
