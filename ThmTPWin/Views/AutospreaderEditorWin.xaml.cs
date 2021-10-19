//-----------------------------------------------------------------------------
// File Name   : AutospreaderEditorWin
// Author      : junlei
// Date        : 5/03/2021 5:47:05 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Windows;
using System.Windows.Controls;
using ThmTPWin.ViewModels;

namespace ThmTPWin.Views {
    /// <summary>
    /// Interaction logic for AutospreaderEditorWin.xaml
    /// </summary>
    public partial class AutospreaderEditorWin : Window {
        private readonly AutospreaderEditorVM _vm;
        private readonly AutospeaderParas _asParas;
        internal AutospreaderEditorWin(AutospeaderParas asParas) {
            InitializeComponent();

            _vm = new(asParas.Name, asParas.IsEnabled, asParas.ASLegs);
            DataContext = _vm;

            _asParas = asParas;
        }

        private void OKBtn_Click(object sender, RoutedEventArgs e) {
            if (!_asParas.Check(out string err)) {
                MessageBox.Show(err, "Error", MessageBoxButton.OK,
                    MessageBoxImage.Error);
                return;
            }

            DialogResult = true;
        }

        private void CancelBtn_Click(object sender, RoutedEventArgs e) {
            DialogResult = false;
        }

        private void SelectInstrument_Click(object sender, RoutedEventArgs e) {
            var dlg = new InstrumentSelectionWin() {
                Owner = this
            };

            var rlt = dlg.ShowDialog();
            if (rlt.Value) {
                var contxt = (sender as Button)?.DataContext as AutospeaderLeg;
                contxt.InstrumentInfo = dlg.SelectedInstrument;
            }
        }
    }
}
