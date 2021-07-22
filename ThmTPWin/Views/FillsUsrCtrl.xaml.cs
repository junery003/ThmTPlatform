//-----------------------------------------------------------------------------
// File Name   : FillsUsrCtrl
// Author      : junlei
// Date        : 4/23/2020 13:05:13 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Windows.Controls;
using ThmCommon.Models;
using ThmTPWin.Controllers;
using ThmTPWin.ViewModels;

namespace ThmTPWin.Views {
    /// <summary>
    /// Interaction logic for FillsUsrCtrl.xaml
    /// </summary>
    public partial class FillsUsrCtrl : UserControl {
        public static string ID => "Fills";
        private readonly string _filledSound = "./sounds/shotgun.wav";

        private readonly TradingPMainWin _parent;
        private readonly FillsVM _vm = new FillsVM();

        public FillsUsrCtrl(TradingPMainWin parent) {
            InitializeComponent();

            DataContext = _vm;
            _parent = parent;
        }

        internal void OnOrderDataUpdated(OrderData orderData) {
            switch (orderData.Status) {
            case EOrderStatus.Filled:
            case EOrderStatus.PartiallyFilled: {
                Util.Sound(_filledSound);
                _parent.UpdateNetPosition(orderData.InstrumentID);
                _vm.AddRecord(orderData);
                return;
            }
            default:
                return;
            }
        }
    }
}
