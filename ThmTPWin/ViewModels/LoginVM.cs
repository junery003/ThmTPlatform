//-----------------------------------------------------------------------------
// File Name   : LoginVM
// Author      : junlei
// Date        : 5/29/2020 12:53:20 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Prism.Mvvm;
using System;
using System.Collections.ObjectModel;
using System.Windows.Data;

namespace ThmTPWin.ViewModels.LoginViewModels {
    public class LoginVM : BindableBase {
        public ObservableCollection<Status> ProcessLogs { get; } = new ObservableCollection<Status>();

        private readonly object _lock = new object();
        internal LoginVM() {
            BindingOperations.EnableCollectionSynchronization(ProcessLogs, _lock);
        }

        private int _loginCount = 0;
        public int LoginCount {
            get => _loginCount;
            set {
                if (SetProperty(ref _loginCount, value)) {
                    LoginEnabled = value > 0;
                }
            }
        }

        private bool _loginEnabled = false;
        public bool LoginEnabled {
            get => _loginEnabled;
            set => SetProperty(ref _loginEnabled, value);
        }

        internal void AddProgess(string message) {
            ProcessLogs.Add(new Status { DateTime = DateTime.Now, Message = message, });
        }
    }

    public class Status {
        public DateTime DateTime { get; set; }
        public string Message { get; set; }
    }
}
