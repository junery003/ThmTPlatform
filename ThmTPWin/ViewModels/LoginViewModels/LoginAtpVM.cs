﻿//-----------------------------------------------------------------------------
// File Name   : LoginAtpVM
// Author      : junlei
// Date        : 5/27/2020 8:55:48 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Collections.ObjectModel;
using Prism.Mvvm;
using ThmCommon.Config;

namespace ThmTPWin.ViewModels.LoginViewModels {
    public class LoginAtpVM : BindableBase, ILoginTabItm {
        public EProviderType Provider => EProviderType.ATP;

        private bool _isChecked = true;
        public bool IsChecked {
            get => _isChecked;
            set => SetProperty(ref _isChecked, value);
        }

        private string _brokerId;
        public string BrokerId {
            get => _brokerId;
            set => SetProperty(ref _brokerId, value);
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

        private string _appId;
        public string AppId {
            get => _appId;
            set => SetProperty(ref _appId, value);
        }

        private string _authCode;
        public string AuthCode {
            get => _authCode;
            set => SetProperty(ref _authCode, value);
        }

        private AtpLoginCfg _selectedAccount;
        public AtpLoginCfg SelectedAccount {
            get => _selectedAccount;
            set {
                if (SetProperty(ref _selectedAccount, value)) {
                    BrokerId = _selectedAccount.BrokerId;
                    UserId = _selectedAccount.UserId;
                    Password = _selectedAccount.Password;
                    AppId = _selectedAccount.AppId;
                    AuthCode = _selectedAccount.AuthCode;
                }
            }
        }

        public ObservableCollection<AtpLoginCfg> AllAccounts { get; } = new ObservableCollection<AtpLoginCfg>();
        public LoginAtpVM(AtpLoginCfg atpLogin) {
            AllAccounts.Add(atpLogin);
            SelectedAccount = atpLogin;
        }

        public bool Check(out string err) {
            if (SelectedAccount.Enabled) {
                if (string.IsNullOrWhiteSpace(BrokerId)) {
                    err = $"{SelectedAccount.UserId} Please specify the Broker ID";
                    return false;
                }

                if (string.IsNullOrWhiteSpace(UserId)) {
                    err = $"{SelectedAccount.UserId} Please specify the User ID";
                    return false;
                }

                if (string.IsNullOrWhiteSpace(Password)) {
                    err = $"{SelectedAccount.UserId} Please specify the Password";
                    return false;
                }

                if (string.IsNullOrWhiteSpace(AppId)) {
                    err = $"{SelectedAccount.UserId} Please specify the App ID";
                    return false;
                }

                if (string.IsNullOrWhiteSpace(AuthCode)) {
                    err = $"{SelectedAccount.UserId} Please specify the AuthCode";
                    return false;
                }
            }

            err = string.Empty;
            return true;
        }
    }
}