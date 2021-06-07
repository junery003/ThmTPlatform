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
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Prism.Mvvm;
using ThmTPClient;

namespace ThmTPWin.ViewControllers {
    internal class TtpMainWinVM : BindableBase {

        private readonly GreetClient _client;

        internal TtpMainWinVM() {
            _client = new GreetClient();

            Task.Delay(1000).Wait();
            Start();
        }

        private string _test;
        public string Test {
            get => _test;
            set => SetProperty(ref _test, value);
        }

        internal async Task Start() {
            Test = await _client.Start();
        }
    }
}
