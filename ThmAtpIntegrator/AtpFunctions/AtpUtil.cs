//-----------------------------------------------------------------------------
// File Name   : AtpUtil
// Author      : junlei
// Date        : 8/19/2020 6:39:09 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.Generic;

namespace ThmAtpIntegrator.AtpFunctions {
    public static class AtpUtil {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        /// <summary>
        /// for ATP: extract info: exchangeID, product, contract from instrumentID
        /// </summary>
        /// <param name="instrumentID"></param>
        /// <returns></returns>
        public static Tuple<string, string, string> ExtractContract(string instrumentID) {
            if (string.IsNullOrWhiteSpace(instrumentID)) {
                Logger.Error($"Invalid instrumentID: {instrumentID}");
                return new Tuple<string, string, string>(null, null, null);
            }

            var leftRight = instrumentID.Split('-');
            if (leftRight.Length != 2) { // should not happen
                Logger.Error($"Invalid instrumentID: {instrumentID}");
                return new Tuple<string, string, string>(null, null, null);
            }

            string product;
            string contract;
            var leftHalf = leftRight[0];
            if (leftHalf.Length > 4) { // normally: "CPF2005-APEX"
                product = leftHalf.Substring(0, leftHalf.Length - 4);
                contract = leftHalf.Substring(leftHalf.Length - 4);
            }
            else { // eg. "CU3M-LME"
                int idx = 0;
                for (; idx < leftHalf.Length; ++idx) {
                    if (leftHalf[idx] > '0' && leftHalf[idx] < '9') {
                        break;
                    }
                }

                product = leftHalf.Substring(0, idx);
                contract = leftHalf.Substring(idx);
            }

            return new Tuple<string, string, string>(leftRight[1], product, contract);
        }


        //Give a list of contract code and year with its exchange e.g. FEF19-SGX, this function will populate the rest of the months
        public static List<string> GenerateInstrumentIDS(int fromMonth, int fromYear, int toYear, List<string> codes) {
            List<string> output = new List<string>();

            foreach (string c in codes) {
                string[] strArr = c.Split('-');
                string contractYear = strArr[0];
                string exh = strArr[1];

                for (int month = fromMonth; month <= 12; month++) {
                    string pad = "0";
                    if (month < 10) {
                        pad += month;
                    }
                    else {
                        pad = "" + month;
                    }

                    output.Add(contractYear + pad + "-" + exh);
                }
            }
            return output;
        }
    }
}
