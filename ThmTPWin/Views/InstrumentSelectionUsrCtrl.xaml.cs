//-----------------------------------------------------------------------------
// File Name   : InstrumentSelectionUsrCtrl
// Author      : junlei
// Date        : 4/23/2020 13:15:13 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.ComponentModel;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using ThmCommon.Handlers;
using ThmTPWin.ViewModels;

namespace ThmTPWin.Views {
    /// <summary>
    /// Interaction logic for InstrumentSelection.xaml
    /// </summary>
    public partial class InstrumentSelectionUsrCtrl : UserControl {
        internal InstrumentHandlerBase InstrumentHandler { get; private set; }

        private readonly InstrumentSelectionVM _vm;
        public InstrumentSelectionUsrCtrl() {
            InitializeComponent();

            _vm = new InstrumentSelectionVM(TradingPMainWin.ConnMgr);
            DataContext = _vm;
        }

        private void Win_Loaded(object sender, RoutedEventArgs e) {
            lstbProvider.Items.SortDescriptions.Add(new SortDescription("", ListSortDirection.Ascending));
        }

        public bool Select(out string err) {
            InstrumentHandler = _vm.GetInstrumentHandler(out err);
            if (InstrumentHandler == null) {
                err = "Instrument not initialized: " + err;
                return false;
            }

            InstrumentHandler.Start();
            Task.Delay(500).Wait();

            return true;
        }
    }
}
