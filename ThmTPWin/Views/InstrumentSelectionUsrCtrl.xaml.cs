//-----------------------------------------------------------------------------
// File Name   : InstrumentSelectionUsrCtrl
// Author      : junlei
// Date        : 4/23/2020 13:15:13 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Windows.Controls;
using ThmCommon.Models;
using ThmTPWin.ViewModels;

namespace ThmTPWin.Views {
    /// <summary>
    /// Interaction logic for InstrumentSelectionUsrCtrl.xaml
    /// </summary>
    public partial class InstrumentSelectionUsrCtrl : UserControl {
        private readonly InstrumentSelectionVM _vm;
        public InstrumentSelectionUsrCtrl() {
            InitializeComponent();

            _vm = new InstrumentSelectionVM();
            DataContext = _vm;
        }

        public ThmInstrumentInfo Select(out string err) {
            var instrumentInfo = _vm.GetInstrument(out err);
            if (instrumentInfo == null) {
                err = "Instrument not initialized: " + err;
                return null;
            }

            return instrumentInfo;
        }
    }
}
