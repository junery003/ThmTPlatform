//-----------------------------------------------------------------------------
// File Name   : App
// Author      : junlei
// Date        : 4/12/2020 13:14:13 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

using System.Threading;
using System.Windows;

namespace ThmTPWin {
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application {
        private static Mutex _mutex;
        protected override void OnStartup(StartupEventArgs e) {
            const string thisApp = "themeTP";

            _mutex = new Mutex(true, thisApp, out bool createdNew);
            if (!createdNew) {
                MessageBox.Show("ThemeTradingP is running already.");
                Current.Shutdown();
            }

            base.OnStartup(e);
        }
    }
}
