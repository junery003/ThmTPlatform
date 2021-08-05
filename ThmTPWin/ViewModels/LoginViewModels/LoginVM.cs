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
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Threading.Tasks;
using System.Windows.Data;
using ThmCommon.Config;
using ThmTPWin.Controllers;

namespace ThmTPWin.ViewModels.LoginViewModels {
    public class LoginVM : BindableBase {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        public ObservableCollection<ILoginTabItm> LoginTabItms { get; } = new ObservableCollection<ILoginTabItm>();
        public ObservableCollection<Status> ProcessLogs { get; } = new ObservableCollection<Status>();

        private ILoginTabItm _selectedItm;
        public ILoginTabItm SelectedItm {
            get => _selectedItm;
            set => SetProperty(ref _selectedItm, value);
        }

        private readonly object _lock = new object();
        internal LoginVM() {
            BindingOperations.EnableCollectionSynchronization(ProcessLogs, _lock);
        }

        internal bool Init(out string err) {
            err = string.Empty;

            if (!ConfigHelper.Valid()) {
                err = "config file is invalid";
                return false;
            }

            if (ConfigHelper.LoginCfg.AtpLogin.Enabled) { // not enebaled
                LoginTabItms.Add(new LoginAtpVM(ConfigHelper.LoginCfg.AtpLogin) {
                    IsChecked = true
                });
            }

            if (ConfigHelper.LoginCfg.TTLogin.Enabled) {
                LoginTabItms.Add(new LoginTTVM(ConfigHelper.LoginCfg.TTLogin) {
                    IsChecked = true
                });
            }

            if (ConfigHelper.LoginCfg.TitanLogin.Enabled) {
                LoginTabItms.Add(new LoginTitanVM(ConfigHelper.LoginCfg.TitanLogin) {
                    IsChecked = true
                });
            }

            if (LoginTabItms.Count <= 0) {
                AddProgess("No Provider Enabled");
                return false;
            }

            SelectedItm = LoginTabItms[0];

            AddProgess("Program started");
            return true;
        }

        internal bool IsChecked(EProviderType providerType) {
            foreach (var itm in LoginTabItms) {
                if (itm.Provider == providerType) {
                    return itm.IsChecked;
                }
            }

            return false;
        }

        internal bool IsValid(out string err) {
            int selected = 0;
            foreach (var itm in LoginTabItms) {
                if (itm.IsChecked) {
                    AddProgess($"Checking {itm.Provider} login info...");

                    if (!itm.Check(out err)) {
                        err = $"{itm.Provider} Error: {err}";
                        return false;
                    }
                    ++selected;
                }
            }

            if (selected == 0) {
                err = "Please select at least one provider";
                return false;
            }

            AddProgess("Initializing connection(s)...");

            err = string.Empty;
            return true;
        }

        internal async Task<bool> StartAsync() {
            var tasks = new List<Task>();
            foreach (var itm in LoginTabItms) {
                if (itm.IsChecked) {
                    var tsk = Start(itm.Provider);
                    if (tsk != null) {
                        tasks.Add(tsk);
                    }
                }
                else {
                    //ConnMgr.Enable(itm.Provider, false);
                }
            }

            await Task.WhenAll(tasks);
            AddProgess("Finishing initialization...");
            Task.Delay(1000).Wait();

            return true;
        }

        private Task Start(EProviderType providerType) {
            return Task.Run(async () => {
                AddProgess($"Initializing {providerType} connection...");

                ILoginCfg loginCfg = null;
                switch (providerType) {
                    case EProviderType.ATP:
                        loginCfg = ConfigHelper.LoginCfg.AtpLogin;
                        break;
                    case EProviderType.TT:
                        loginCfg = ConfigHelper.LoginCfg.TTLogin;
                        break;
                    case EProviderType.TITAN:
                        loginCfg = ConfigHelper.LoginCfg.TitanLogin;
                        break;
                    default: // wrong
                        return;
                };

                var conn = await ConnManager.InitConnection(providerType, loginCfg);
                if (conn == null) {
                    AddProgess($"Failed to init {providerType} connection");
                    return;
                }

                if (!conn.Connect()) {
                    AddProgess($"{providerType}: Failed to connect");
                    return;
                }

                Task.Delay(8000).Wait();
                AddProgess($"{providerType} connection initialized");
            });
        }

        internal void AddProgess(string message) {
            ProcessLogs.Add(new Status { DateTime = DateTime.Now, Message = message, });
        }

        internal void Dispose() {

        }
    }

    public class Status {
        public DateTime DateTime { get; set; }
        public string Message { get; set; }
    }

    public interface ILoginTabItm {
        EProviderType Provider { get; }
        bool IsChecked { get; set; }
        bool Check(out string err);
    }
}
