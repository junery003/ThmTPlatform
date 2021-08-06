//-----------------------------------------------------------------------------
// File Name   : DllHelper
// Author      : junlei
// Date        : 1/13/2020 3:18:05 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Runtime.InteropServices;
using System.Security;

namespace ThmAtpIntegrator.AtpHandler {
    /// <summary>
    /// call functions from AtpBridge.dll 
    /// </summary>
    public static class DllHelper {
        private const string DLL = @"AtpAdapter.dll";

        [DllImport(DLL, CallingConvention = CallingConvention.StdCall), SuppressUnmanagedCodeSecurity]
        private static extern void InitExport([MarshalAs(UnmanagedType.LPStr)] string mdServer,
            [MarshalAs(UnmanagedType.LPStr)] string tradeServer,
            [MarshalAs(UnmanagedType.LPStr)] string brokerId,
            [MarshalAs(UnmanagedType.LPStr)] string userId,
            [MarshalAs(UnmanagedType.LPStr)] string userPwd,
            [MarshalAs(UnmanagedType.LPStr)] string investorId,
            [MarshalAs(UnmanagedType.LPStr)] string appId,
            [MarshalAs(UnmanagedType.LPStr)] string authCode,
            [MarshalAs(UnmanagedType.LPStr)] string streamDataAddr,
            [MarshalAs(UnmanagedType.LPStr)] string streamTradeAddr);
        public static void InitConfig([MarshalAs(UnmanagedType.LPStr)] string mdServer,
            [MarshalAs(UnmanagedType.LPStr)] string tradeServer,
            [MarshalAs(UnmanagedType.LPStr)] string brokerId,
            [MarshalAs(UnmanagedType.LPStr)] string userId,
            [MarshalAs(UnmanagedType.LPStr)] string userPwd,
            [MarshalAs(UnmanagedType.LPStr)] string investorId,
            [MarshalAs(UnmanagedType.LPStr)] string appId,
            [MarshalAs(UnmanagedType.LPStr)] string authCode,
            [MarshalAs(UnmanagedType.LPStr)] string streamDataAddr,
            [MarshalAs(UnmanagedType.LPStr)] string streamTradeAddr) {
            InitExport(mdServer, tradeServer, brokerId, userId, userPwd, investorId, appId,
                authCode, streamDataAddr, streamTradeAddr);
        }

        // ----------------------------------------------------------------------------------------------------;
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl), SuppressUnmanagedCodeSecurity]
        private static extern void UpdateTradeClientExport([MarshalAs(UnmanagedType.LPStr)] string tradeServer,
            [MarshalAs(UnmanagedType.LPStr)] string brokerId,
            [MarshalAs(UnmanagedType.LPStr)] string userId,
            [MarshalAs(UnmanagedType.LPStr)] string userPwd,
            [MarshalAs(UnmanagedType.LPStr)] string investorId,
            [MarshalAs(UnmanagedType.LPStr)] string appId,
            [MarshalAs(UnmanagedType.LPStr)] string authCode);
        public static void UpdateTradeClient([MarshalAs(UnmanagedType.LPStr)] string tradeServer,
            [MarshalAs(UnmanagedType.LPStr)] string brokerId,
            [MarshalAs(UnmanagedType.LPStr)] string userId,
            [MarshalAs(UnmanagedType.LPStr)] string userPwd,
            [MarshalAs(UnmanagedType.LPStr)] string investorId,
            [MarshalAs(UnmanagedType.LPStr)] string appId,
            [MarshalAs(UnmanagedType.LPStr)] string authCode) {
            UpdateTradeClientExport(tradeServer, brokerId, userId, userPwd, investorId, appId, authCode);
        }

        //Subscribe to contract
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl), SuppressUnmanagedCodeSecurity]
        private static extern int SubscribeContractExport([MarshalAs(UnmanagedType.LPStr)] string contract);
        public static int SubscribeContract([MarshalAs(UnmanagedType.LPStr)] string contract) {
            return SubscribeContractExport(contract);
        }

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl), SuppressUnmanagedCodeSecurity]
        private static extern void UnsubcribeContractExport([MarshalAs(UnmanagedType.LPStr)] string contract);
        public static void UnsubcribeContract([MarshalAs(UnmanagedType.LPStr)] string contract) {
            UnsubcribeContractExport(contract);
        }

        // Trading
        [DllImport(DLL, CallingConvention = CallingConvention.StdCall), SuppressUnmanagedCodeSecurity]
        private static extern void SetAccountExport([MarshalAs(UnmanagedType.LPStr)] string account);
        public static void SetAccount(string accountID) {
            SetAccountExport(accountID);
        }

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode), SuppressUnmanagedCodeSecurity]
        private static extern int SendOrderExport([MarshalAs(UnmanagedType.LPStr)] string instrument, bool isBuy,
            double price, int qty, [MarshalAs(UnmanagedType.LPStr)] string orderTag);
        public static int SendOrder([MarshalAs(UnmanagedType.LPStr)] string instrumentID, bool isBuy,
            double price, int qty, [MarshalAs(UnmanagedType.LPStr)] string orderTag, int tif) {
            return SendOrderExport(instrumentID, isBuy, price, qty, orderTag);
        }

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl), SuppressUnmanagedCodeSecurity]
        private static extern int ModifyOrderExport([MarshalAs(UnmanagedType.LPStr)] string exchangeID,
            [MarshalAs(UnmanagedType.LPStr)] string orderID, double price, int qty);
        public static int ModifyOrder([MarshalAs(UnmanagedType.LPStr)] string exchangeID,
            [MarshalAs(UnmanagedType.LPStr)] string orderID, double price, int qty) {
            return ModifyOrderExport(exchangeID, orderID, price, qty);
        }

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl), SuppressUnmanagedCodeSecurity]
        private static extern int CancelOrderExport([MarshalAs(UnmanagedType.LPStr)] string exchangeID,
            [MarshalAs(UnmanagedType.LPStr)] string orderID);
        public static int CancelOrder([MarshalAs(UnmanagedType.LPStr)] string exchangeID,
            [MarshalAs(UnmanagedType.LPStr)] string orderID) {
            return CancelOrderExport(exchangeID, orderID);
        }

        //Request query ATP Order
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl), SuppressUnmanagedCodeSecurity]
        private static extern void ReqQueryOrderExport([MarshalAs(UnmanagedType.LPStr)] string instrumentID);
        public static void ReqQueryOrder([MarshalAs(UnmanagedType.LPStr)] string instrumentID) {
            ReqQueryOrderExport(instrumentID);
        }

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl), SuppressUnmanagedCodeSecurity]
        private static extern void ReqQueryInvestorPositionExport([MarshalAs(UnmanagedType.LPStr)] string instrumentID);
        public static void ReqPositionUpdate([MarshalAs(UnmanagedType.LPStr)] string instrumentID) {
            ReqQueryInvestorPositionExport(instrumentID);
        }

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl), SuppressUnmanagedCodeSecurity]
        private static extern void ReqQueryTradeExport([MarshalAs(UnmanagedType.LPStr)] string instrumentID);
        public static void ReqQueryTrade([MarshalAs(UnmanagedType.LPStr)] string intrumentID) {
            ReqQueryTradeExport(intrumentID);
        }

        [DllImport(DLL, CallingConvention = CallingConvention.StdCall), SuppressUnmanagedCodeSecurity]
        private static extern void DismentalExport();
        public static void Dismental() {
            DismentalExport();
        }
    }
}
