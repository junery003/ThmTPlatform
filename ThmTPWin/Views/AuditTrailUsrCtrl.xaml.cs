//-----------------------------------------------------------------------------
// File Name   : AuditTrailUsrCtrl
// Author      : junlei
// Date        : 8/26/2020 15:05:13 PM
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
    /// Interaction logic for AuditTrailUsrCtrl.xaml
    /// </summary>
    public partial class AuditTrailUsrCtrl : UserControl {
        public static string ID => "Audit Trail";

        private readonly AuditTrailVM _vm = new AuditTrailVM();
        public AuditTrailUsrCtrl() {
            InitializeComponent();

            DataContext = _vm;
        }

        internal void OnOrderDataUpdated(OrderData orderData) {
            _vm.AddRecord(orderData);
        }
    }
}
