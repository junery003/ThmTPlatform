//-----------------------------------------------------------------------------
// File Name   : TradingPMainWinVM
// Author      : junlei
// Date        : 4/22/2020 5:03:58 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Timers;
using Prism.Mvvm;
using ThmTPWin.Controllers;

namespace ThmTPWin.ViewModels {
    public class TradingPMainWinVM : BindableBase {
        private DateTime _currentTime = DateTime.Now;
        public DateTime CurrentTime {
            get => _currentTime;
            set => SetProperty(ref _currentTime, value);
        }

        private bool _isTitanEnabled = false;
        public bool IsTitanEnabled {
            get => _isTitanEnabled;
            set => SetProperty(ref _isTitanEnabled, value);
        }

        public TradingPMainWinVM(ThmConfig cfg) {
            InitTimer();

            _isTitanEnabled = cfg.TitanEnabled;
        }

        private void InitTimer() {
            var timer = new Timer() {
                Interval = 1000,
                Enabled = true
            };

            timer.Elapsed += (object sender, ElapsedEventArgs e) => {
                CurrentTime = DateTime.Now;
            };
        }
    }
}
