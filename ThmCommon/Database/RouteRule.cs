//-----------------------------------------------------------------------------
// File Name   : RouteRule
// Author      : junlei
// Date        : 2/18/2020 12:18:03 PM
// Description : RouteRule for DB - WARNING : DONOT CHANGE THIS CLASS
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Linq;

namespace ThmCommon.Database {
    /// <summary>
    /// DONOT CHANGE THIS CLASS
    /// </summary>
    public static class RouteRule {
        public static List<string> ExchangeList => exchangeIdxDic.Keys.ToList();
        public static int TABLECOUNT { get; } = 5;

        private static readonly Dictionary<string, int> exchangeIdxDic = new()
        {
            { "SGX",  0},
            { "HKE",  0},
            { "HKEX", 0}, // added on Mar. 11, 2020, same as HKE(for ATP)

            { "APEX", 1},
            { "CME",  1},
            { "TCE",  1},

            { "BMD", 2},
            { "DC",  2},  //DCE, no need to add {"DCE", 2} as ATP finds the contract directly(while TT finds by market and product)
            { "ICE", 2},

            { "CBT", 3},
            { "NYM", 3},
            { "SH",  3},   // SHFE
            { "EUREX", 3}, // added on Jul, 2021

            { "INE", 4},
            { "LME", 4},
            { "ZC",  4},
            { "TOCOM", 4}, // added on Mar. 11, 2020
            { "OSE", 4},   // added on July 28, 2020, meanwhile TOCOM will be invalid
        };

        /// <summary>
        /// Get database index
        /// </summary>
        /// <param name="exchange"></param>
        /// <returns></returns>
        public static string GetDbNameIndex(string exchange) {
            if (exchangeIdxDic.TryGetValue(exchange.ToUpper(), out int idx)) {
                return "_" + idx.ToString();
            }

            throw new Exception("Exchange not supported: " + exchange);
        }

        /// <summary>
        /// Get tablename index
        /// </summary>
        /// <param name="product"></param>
        /// <param name="recordDateTime"></param>
        /// <returns></returns>
        public static string GetTableNameIndex(string product, DateTime recordDateTime) {
            return GetTablePrefix(recordDateTime) + "_"
                + (GetDeterministicHashCode(product.ToUpper()) % TABLECOUNT).ToString();
        }

        private static int GetDeterministicHashCode(string str) {
            unchecked {
                int hash1 = (5381 << 16) + 5381;
                int hash2 = hash1;

                for (int i = 0; i < str.Length; i += 2) {
                    hash1 = ((hash1 << 5) + hash1) ^ str[i];
                    if (i == str.Length - 1) {
                        break;
                    }

                    hash2 = ((hash2 << 5) + hash2) ^ str[i + 1];
                }

                return Math.Abs(hash1 + (hash2 * 1566083941));
            }
        }

        public static string GetTablePrefix(DateTime recordDateTime) {
            // before May 1, 2020, the table idx have no prefix
            if (recordDateTime < DateTime.ParseExact("20200501", "yyyyMMdd", null)) {
                return "";
            }

            string qurt = "0";
            switch (recordDateTime.Month) {
            case 1:
            case 2:
            case 3:
            case 4:
                qurt = "1";
                break;
            case 5:
            case 6:
            case 7:
            case 8:
                qurt = "2";
                break;
            case 9:
            case 10:
            case 11:
            case 12:
                qurt = "3";
                break;
            default:
                break;
            }

            return recordDateTime.ToString("yyyy") + qurt;
        }
    }
}
