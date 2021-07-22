//-----------------------------------------------------------------------------
// File Name   : LoginAtpVM
// Author      : junlei
// Date        : 5/27/2020 8:55:48 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Collections.Generic;
using System.Collections.ObjectModel;
using Prism.Mvvm;
using ThmAtpIntegrator.AtpFunctions;

namespace ThmTPWin.ViewModels.AtpViewModels {
    public class LoginAtpVM : BindableBase {
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

        private AtpAcount _selectedAccount;
        public AtpAcount SelectedAccount {
            get => _selectedAccount;
            set {
                if (SetProperty(ref _selectedAccount, value)) {
                    BrokerId = _selectedAccount.BrokerID;
                    UserId = _selectedAccount.UserID;
                    Password = _selectedAccount.Password;
                    AppId = _selectedAccount.AppID;
                    AuthCode = _selectedAccount.AuthCode;
                }
            }
        }

        public ObservableCollection<AtpAcount> AllAccounts { get; } = new ObservableCollection<AtpAcount>();
        public LoginAtpVM(List<AtpAcount> atpLogins) {
            atpLogins.ForEach(x => {
                AllAccounts.Add(x);
            });

            SelectedAccount = AllAccounts[0];
        }

        internal string Check() {
            bool isSelected = false;
            foreach (var acc in AllAccounts) {
                isSelected = isSelected || acc.Enabled;

                if (acc.Enabled) {
                    if (string.IsNullOrWhiteSpace(BrokerId)) {
                        return $"{acc.DisplayedID} Please specify the Broker ID";
                    }

                    if (string.IsNullOrWhiteSpace(UserId)) {
                        return $"{acc.DisplayedID} Please specify the User ID";
                    }

                    if (string.IsNullOrWhiteSpace(Password)) {
                        return $"{acc.DisplayedID} Please specify the Password";
                    }

                    if (string.IsNullOrWhiteSpace(AppId)) {
                        return $"{acc.DisplayedID} Please specify the App ID";
                    }

                    if (string.IsNullOrWhiteSpace(AuthCode)) {
                        return $"{acc.DisplayedID} Please specify the AuthCode";
                    }
                }
            }

            return !isSelected ? "Please select an accout for ATP" : null;
        }
    }
}
