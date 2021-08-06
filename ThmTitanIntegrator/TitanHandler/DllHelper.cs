//-----------------------------------------------------------------------------
// File Name   : DllHelper
// Author      : junlei
// Date        : 12/9/2020 9:19:08 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Runtime.InteropServices;
using System.Security;

namespace ThmTitanIntegrator.TitanHandler {
    internal static class DllHelper {
        private const string DLL = "TitanAdapter.dll";

        // ----------------------------------------------------------------------------------------;
        [DllImport(DLL, CallingConvention = CallingConvention.StdCall), SuppressUnmanagedCodeSecurity]
        private static extern bool InitExport();
        internal static bool Init() {
            return InitExport();
        }

        [DllImport(DLL, CallingConvention = CallingConvention.StdCall), SuppressUnmanagedCodeSecurity]
        private static extern void DismentalExport();
        internal static void Dismental() {
            DismentalExport();
        }

        // ----------------------------------------------------------------------------------------;
        // OMnet APIs
        [DllImport(DLL, CallingConvention = CallingConvention.StdCall), SuppressUnmanagedCodeSecurity]
        private static extern bool ChangePasswordExport([MarshalAs(UnmanagedType.LPStr)] string usr,
            [MarshalAs(UnmanagedType.LPStr)] string pwd,
            [MarshalAs(UnmanagedType.LPStr)] string newPwd);
        internal static bool ChangePassword(string usr, string pwd, string newPwd) {
            return ChangePasswordExport(usr, pwd, newPwd);
        }

        // ----------------------------------------------------------------------------------------;
        // ITCH APIs
        [DllImport(DLL, CallingConvention = CallingConvention.StdCall), SuppressUnmanagedCodeSecurity]
        private static extern void SubscribeContractExport([MarshalAs(UnmanagedType.LPStr)] string instrumentID);
        internal static void SubscribeContract(string instrumentID) {
            SubscribeContractExport(instrumentID);
        }

        [DllImport(DLL, CallingConvention = CallingConvention.StdCall), SuppressUnmanagedCodeSecurity]
        private static extern void UnsubscribeContractExport([MarshalAs(UnmanagedType.LPStr)] string instrumentID);
        internal static void UnsubscribeContract(string instrumentID) {
            UnsubscribeContractExport(instrumentID);
        }

        // ----------------------------------------------------------------------------------------;
        // OUCH APIs
        [DllImport(DLL, CallingConvention = CallingConvention.StdCall), SuppressUnmanagedCodeSecurity]
        private static extern void SetAccountExport([MarshalAs(UnmanagedType.LPStr)] string account);
        internal static void SetAccount(string account) {
            SetAccountExport(account);
        }

        [DllImport(DLL, CallingConvention = CallingConvention.StdCall), SuppressUnmanagedCodeSecurity]
        private static extern void AddOrderExport([MarshalAs(UnmanagedType.LPStr)] string symbol,
            bool isBuy, double price, int qty, int tif);
        internal static void EnterOrder(string symbol, bool isBuy, decimal price, int qty, int tif = 0, string tag = null) {
            AddOrderExport(symbol, isBuy, (double)price, qty, tif);
        }

        [DllImport(DLL, CallingConvention = CallingConvention.StdCall), SuppressUnmanagedCodeSecurity]
        private static extern void ReplaceOrderExport([MarshalAs(UnmanagedType.LPStr)] string symbol,
            [MarshalAs(UnmanagedType.LPStr)] string orderToken,
            double price, int qty,
            [MarshalAs(UnmanagedType.LPStr)] string account = null);
        internal static void UpdateOrder(string symbol, string orderToken, double price, int qty, string account = null) {
            ReplaceOrderExport(symbol, orderToken, price, qty, account);
        }

        [DllImport(DLL, CallingConvention = CallingConvention.StdCall), SuppressUnmanagedCodeSecurity]
        private static extern void CancelOrderExport([MarshalAs(UnmanagedType.LPStr)] string orderToken);
        internal static void CancelOrder(string orderToken) {
            CancelOrderExport(orderToken);
        }

        [DllImport(DLL, CallingConvention = CallingConvention.StdCall), SuppressUnmanagedCodeSecurity]
        private static extern void CancelOrderByIDExport([MarshalAs(UnmanagedType.LPStr)] string symbol,
            bool isBuy, ulong orderID);
        internal static void CancelOrderByID(string symbol, bool isBuy, string orderID) {
            CancelOrderByIDExport(symbol, isBuy, ulong.Parse(orderID));
        }
    }
}
