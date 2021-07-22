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
using ThmTitanIntegrator.TitanFunctions;

namespace ThmTPWin.ViewModels.TitanViewModels {
    public class LoginTitanVM : BindableBase {
        private string _itchServer;
        public string ITCHServer {
            get => _titanLogin.ItchCfg.Server;
            set {
                if (SetProperty(ref _itchServer, value)) {
                    _titanLogin.ItchCfg.Server = value;
                }
            }
        }

        private int _itchPort;
        public int ITCHPort {
            get => _titanLogin.ItchCfg.Port;
            set {
                if (SetProperty(ref _itchPort, value)) {
                    _titanLogin.ItchCfg.Port = value;
                }
            }
        }

        private string _glimpseServer;
        public string GlimpseServer {
            get => _titanLogin.GlimpseCfg.Server;
            set {
                if (SetProperty(ref _glimpseServer, value)) {
                    _titanLogin.GlimpseCfg.Server = value;
                }
            }
        }

        private int _glimpsePort;
        public int GlimpsePort {
            get => _titanLogin.GlimpseCfg.Port;
            set {
                if (SetProperty(ref _glimpsePort, value)) {
                    _titanLogin.GlimpseCfg.Port = value;
                }
            }
        }

        private string _glimpseUserID;
        public string GlimpseUserID {
            get => _titanLogin.GlimpseCfg.UserID;
            set {
                if (SetProperty(ref _glimpseUserID, value)) {
                    _titanLogin.GlimpseCfg.UserID = value;
                }
            }
        }

        private string _glimpsePassword;
        public string GlimpsePassword {
            get => _titanLogin.GlimpseCfg.Password;
            set {
                if (SetProperty(ref _glimpsePassword, value)) {
                    _titanLogin.GlimpseCfg.Password = value;
                }
            }
        }


        private string _ouchServer;
        public string OUCHServer {
            get => _titanLogin.OuchCfg.Server;
            set {
                if (SetProperty(ref _ouchServer, value)) {
                    _titanLogin.OuchCfg.Server = value;
                }
            }
        }

        private int _ouchPort;
        public int OUCHPort {
            get => _titanLogin.OuchCfg.Port;
            set {
                if (SetProperty(ref _ouchPort, value)) {
                    _titanLogin.OuchCfg.Port = value;
                }
            }
        }

        private string _ouchUserID;
        public string OUCHUserID {
            get => _titanLogin.OuchCfg.UserID;
            set {
                if (SetProperty(ref _ouchUserID, value)) {
                    _titanLogin.OuchCfg.UserID = value;
                }
            }
        }

        private string _ouchPassword;
        public string OUCHPassword {
            get => _titanLogin.OuchCfg.Password;
            set {
                if (SetProperty(ref _ouchPassword, value)) {
                    _titanLogin.OuchCfg.Password = value;
                }
            }
        }

        private string _account;
        public string Account {
            get => _titanLogin.OuchCfg.Account;
            set {
                if (SetProperty(ref _account, value)) {
                    _titanLogin.OuchCfg.Account = value;
                }
            }
        }

        private string _customerInfo;
        public string CustomerInfo {
            get => _titanLogin.OuchCfg.CustomerInfo;
            set {
                if(SetProperty(ref _customerInfo, value)) {
                    _titanLogin.OuchCfg.CustomerInfo = value;
                }
            }
        }

        private string _omnetServer;
        public string OMnetServer {
            get => _titanLogin.OMnetCfg.Server;
            set {
                if (SetProperty(ref _omnetServer, value)) {
                    _titanLogin.OMnetCfg.Server = value;
                }
            }
        }

        private int _omnetPort;
        public int OMnetPort {
            get => _titanLogin.OMnetCfg.Port;
            set {
                if (SetProperty(ref _omnetPort, value)) {
                    _titanLogin.OMnetCfg.Port = value;
                }
            }
        }

        private string _omnetUserID;
        public string OMnetUserID {
            get => _titanLogin.OMnetCfg.UserID;
            set {
                if (SetProperty(ref _omnetUserID, value)) {
                    _titanLogin.OMnetCfg.UserID = value;
                }
            }
        }

        private string _omnetPassword;
        public string OMnetPassword {
            get => _titanLogin.OMnetCfg.Password;
            set {
                if (SetProperty(ref _omnetPassword, value)) {
                    _titanLogin.OMnetCfg.Password = value;
                }
            }
        }

        private readonly TitanAcount _titanLogin;
        public LoginTitanVM(TitanAcount titanLogin) {
            _titanLogin = titanLogin;
        }

        internal string Check() {
            if (string.IsNullOrWhiteSpace(ITCHServer)) {
                return $"Please specify the ITCH server";
            }

            return "";
        }
    }
}
