//-----------------------------------------------------------------------------
// File Name   : LoginTTVM
// Author      : junlei
// Date        : 5/26/2020 8:55:48 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Prism.Mvvm;
using ThmTTIntegrator.TTHandler;

namespace ThmTPWin.ViewModels.TTViewModels {
    public class LoginTTVM : BindableBase {
        public static string[] Environments { get; } = { "ProdSim", "ProdLive" };

        private string _selectedEnv = Environments[0];
        public string SelectedEnv {
            get => _ttAccount.Environment;
            set {
                if (SetProperty(ref _selectedEnv, value)) {
                    _ttAccount.Environment = value;
                }
            }
        }

        private string _apiKey;
        public string APIKey {
            get => _ttAccount.AppKey;
            set {
                if (SetProperty(ref _apiKey, value)) {
                    _ttAccount.AppKey = value;
                }
            }
        }

        private string _accountName;
        public string AccountName {
            get => _ttAccount.AccountName;
            set {
                if (SetProperty(ref _accountName, value)) {
                    _ttAccount.AccountName = value;
                }
            }
        }

        private readonly TTAccount _ttAccount;
        public LoginTTVM(TTAccount ttAccount) {
            _ttAccount = ttAccount;
        }

        internal bool Check(out string err) {
            err = string.Empty;
            if (APIKey.Trim().Length != 73) {
                err = "Please make sure TT API key is correct.";
                return false;
            }

            return true;
        }
    }
}
