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
    /// Interaction logic for InstrumentSelection.xaml
    /// </summary>
    public partial class InstrumentSelectionUsrCtrl : UserControl {
        internal ThmInstrumentInfo InstrumentInfo { get; private set; }

        private readonly InstrumentSelectionVM _vm;
        public InstrumentSelectionUsrCtrl() {
            InitializeComponent();

            _vm = new InstrumentSelectionVM();
            DataContext = _vm;
        }

        public bool Select(out string err) {
            InstrumentInfo = _vm.GetInstrument(out err);
            if (InstrumentInfo == null) {
                err = "Instrument not initialized: " + err;
                return false;
            }

            //InstrumentHandler.Start();
            //Task.Delay(500).Wait();

            return true;
        }
    }
}
