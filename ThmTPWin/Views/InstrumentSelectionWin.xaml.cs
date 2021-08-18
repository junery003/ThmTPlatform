//-----------------------------------------------------------------------------
// File Name   : InstrumentSelectionWin
// Author      : junlei
// Date        : 4/23/2020 13:15:13 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Windows;
using ThmCommon.Models;

namespace ThmTPWin.Views {
    /// <summary>
    /// Interaction logic for InstrumentSelectionWin.xaml
    /// </summary>
    public partial class InstrumentSelectionWin : Window {
        internal ThmInstrumentInfo SelectedInstrumentHandler => InstrumentSelection.InstrumentInfo;

        internal InstrumentSelectionWin() {
            InitializeComponent();
        }

        private void SelectButton_Click(object sender, RoutedEventArgs e) {
            Cursor = System.Windows.Input.Cursors.Wait;

            if (!InstrumentSelection.Select(out var err)) {
                MessageBox.Show(err);
                return;
            }

            DialogResult = true;
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e) {
            DialogResult = false;
        }
    }
}
