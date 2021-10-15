//-----------------------------------------------------------------------------
// File Name   : CtpUtil
// Author      : junlei
// Date        : 8/19/2021 6:39:09 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.Generic;

namespace ThmCtpIntegrator.CtpFunctions {
    public static class CtpUtil {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        /// <summary>
        /// for CTP: extract info: product, contract from instrumentID
        /// </summary>
        /// <param name="instrumentID">eg. "C2111"</param>
        /// <returns></returns>
        public static Tuple<string, string> ExtractContract(string instrumentID) {
            if (string.IsNullOrWhiteSpace(instrumentID)) {
                Logger.Error($"Invalid instrumentID: {instrumentID}");
                return new Tuple<string, string>(null, null);
            }

            string product;
            string contract;
            if (instrumentID.Length > 4) { // normally: "CPF2005"
                product = instrumentID.Substring(0, instrumentID.Length - 4);
                contract = instrumentID.Substring(instrumentID.Length - 4);
            }
            else { // eg. "CU3M"
                int idx = 0;
                for (; idx < instrumentID.Length; ++idx) {
                    if (instrumentID[idx] > '0' && instrumentID[idx] < '9') {
                        break;
                    }
                }

                product = instrumentID.Substring(0, idx);
                contract = instrumentID.Substring(idx);
            }

            return new Tuple<string, string>(product, contract);
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
