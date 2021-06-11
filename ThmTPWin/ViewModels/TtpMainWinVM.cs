//-----------------------------------------------------------------------------
// File Name   : TtpMainWinVM
// Author      : junlei
// Date        : 6/7/2021 12:32:49 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Timers;
using Prism.Commands;
using Prism.Mvvm;
using ThmTPClient.ServiceAdapters;

namespace ThmTPWin.ViewModels {
    internal class TtpMainWinVM : BindableBase {

        private readonly GreetClient _client;

        public DelegateCommand TestCmd { get; }

        private string _test;
        public string Test {
            get => _test;
            set => SetProperty(ref _test, value);
        }

        private DateTime _currentTime = DateTime.Now;
        public DateTime CurrentTime {
            get => _currentTime;
            set => SetProperty(ref _currentTime, value);
        }

        public TtpMainWinVM() {
            _client = new GreetClient();
            TestCmd = new DelegateCommand(Start);

            var timer = new Timer() {
                Interval = 1000,
                Enabled = true
            };

            timer.Elapsed += (object sender, ElapsedEventArgs e) => {
                CurrentTime = DateTime.Now;
            };
        }

        internal async void Start() {
            Test = await _client.Start();
        }
    }
}
