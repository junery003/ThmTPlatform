//-----------------------------------------------------------------------------
// File Name   : AutospreaderSettingWin
// Author      : junlei
// Date        : 10/12/2020 02:26:14 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.ComponentModel;
using System.Windows;
using System.Windows.Input;
using ThmTPWin.ViewModels;

namespace ThmTPWin.Views {
    /// <summary>
    /// Interaction logic for AutospreaderSettingWin.xaml
    /// </summary>
    public partial class AutospreaderSettingWin : Window {
        public AutospeaderParas SelectedAS => _vm.SelectedASPara;
        public bool OpenWithLegs { get; private set; } = false;

        private readonly AutospreaderSettingVM _vm = new AutospreaderSettingVM();
        internal AutospreaderSettingWin() {
            InitializeComponent();

            DataContext = _vm;
        }

        private void AutospeadersDg_MouseDoubleClick(object sender, MouseButtonEventArgs e) {
            EditBtn_Click(null, null);
        }

        private void EditBtn_Click(object sender, RoutedEventArgs e) {
            if (_vm.SelectedASPara == null) {
                return;
            }

            var legEditor = new AutospreaderEditorWin(_vm.SelectedASPara) {
                Owner = this
            };

            var rlt = legEditor.ShowDialog();
            if (rlt.Value) {

            }
        }

        private void CloseBtn_Click(object sender, RoutedEventArgs e) {
            DialogResult = false;
        }

        private void OpenBtn_Click(object sender, RoutedEventArgs e) {
            if (!_vm.Check(out string err)) {
                MessageBox.Show(err, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            OpenWithLegs = false;
            DialogResult = true;
        }

        private void OpenWithLegsBtn_Click(object sender, RoutedEventArgs e) {
            if (!_vm.Check(out string err)) {
                MessageBox.Show(err, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            OpenWithLegs = true;
            DialogResult = true;
        }

        private void Window_Closing(object sender, CancelEventArgs e) {
            Hide();
        }
    }
}
