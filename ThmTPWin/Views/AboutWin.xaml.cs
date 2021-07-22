using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Navigation;
using ThmTPWin.ViewModels;

namespace ThmTPWin.Views {
    /// <summary>
    /// Interaction logic for AboutWin.xaml
    /// </summary>
    public partial class AboutWin : Window {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();
        private readonly AboutVM _vm = new AboutVM();
        public AboutWin() {
            InitializeComponent();

            DataContext = _vm;
        }

        private void Hyperlink_RequestNavigate(object sender, RoutedEventArgs e) {
            try {
                Process.Start(new ProcessStartInfo {
                    FileName = _vm.HyperlinkText,
                    UseShellExecute = true
                });
            }
            catch (Exception ex) {
                Logger.Error($"Failed to open {_vm.HyperlinkText}: " + ex.Message);
            }
        }

        private void OnNavigate_Email(object sender, RequestNavigateEventArgs e) {
            try {
                Process.Start(e.Uri.AbsoluteUri);
                e.Handled = true;
            }
            catch (Exception ex) {
                Logger.Error("Failed to open email: " + ex.Message);
            }
        }

        private void OKBtn_click(object sender, RoutedEventArgs e) {
            DialogResult = true;
        }
    }
}
