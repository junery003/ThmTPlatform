//-----------------------------------------------------------------------------
// File Name   : PasswordChangeVM
// Author      : junlei
// Date        : 1/14/2021 11:55:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Windows.Media;
using Prism.Mvvm;
using ThmTitanIntegrator.TitanHandler;

namespace ThmTPWin.ViewModels.TitanViewModels {
    class PasswordChangeVM : BindableBase {
        public string CurUserID { get; }

        private string _curPwd;
        public string CurPwd {
            get => _curPwd;
            set => SetProperty(ref _curPwd, value);
        }

        private string _newPwd;
        public string NewPwd {
            get => _newPwd;
            set {
                if (SetProperty(ref _newPwd, value)) {
                    if (_newPwd.Length != 10 || _newPwd == _curPwd) {
                        NewPwdBoardColor = Brushes.Red;
                    }
                    else {
                        NewPwdBoardColor = _defaultColor;
                    }
                }
            }
        }

        private string _confirmPwd;
        public string ConfirmPwd {
            get => _confirmPwd;
            set {
                if (SetProperty(ref _confirmPwd, value)) {
                    ConfirmPwdBoardColor = _confirmPwd != _newPwd ? Brushes.Red : _defaultColor;
                }
            }
        }

        private Brush _newPwdBoardColor;
        public Brush NewPwdBoardColor {
            get => _newPwdBoardColor;
            set => SetProperty(ref _newPwdBoardColor, value);
        }

        private Brush _confirmPwdBoardColor;
        public Brush ConfirmPwdBoardColor {
            get => _confirmPwdBoardColor;
            set => SetProperty(ref _confirmPwdBoardColor, value);
        }

        private readonly TitanConnector _connector;
        private readonly Brush _defaultColor;
        public PasswordChangeVM(TitanConnector connector, Brush defaultColor) {
            _defaultColor = defaultColor;
            _newPwdBoardColor = defaultColor;
            _confirmPwdBoardColor = defaultColor;

            _connector = connector;
            CurUserID = connector.TitanCfg.TitanLogin.OuchCfg.UserID;
        }

        public bool ChangePassword() {
            return _connector.ChangePassword(_curPwd, _newPwd);
        }
    }
}
