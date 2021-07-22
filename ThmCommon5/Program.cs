//-----------------------------------------------------------------------------
// File Name   : Program
// Author      : junlei
// Date        : 3/9/2020 2:03:26 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using ThmCommon.Database;

namespace ThmCommon {
    class Program {
        static void Main() {
            List<string> all = new List<string>{
                            "6A",
                            "6J",
                            "AU",
                            "BRN",
                            "BU",
                            "CL",
                            "CN",
                            "CPF",
                            "CU",
                            "FCPO",
                            "FEF",
                            "FU",
                            "GC",
                            "GDU",
                            "HG",
                            "I",
                            "JAU",
                            "JM",
                            "LUC",
                            "OI",
                            "P",
                            "RU",
                            "SC",
                            "SI",
                            "UC",
                            "Y",
                            "ZN" };

            all.ForEach(x => {
                var k = RouteRule.GetTableNameIndex(x, DateTime.Now);
                Console.WriteLine(x + " : " + k);
            });

            /*
            for (int i = 0; i < 26; ++i)
            {
                string tmp1 = ('a' + i).ToString();
                for (int j = 0; j < 26; ++j)
                {
                    string tmp2 = ('a' + j).ToString();

                    //all.Add(tmp1 + tmp2);

                    for (int k = 0; k < 26; ++k)
                    {
                        string tmp3 = ('a' + k).ToString();
                        all.Add(tmp1 + tmp2 + tmp3);

                        for (int l = 0; l < 26; ++l)
                        {
                            string tmp4 = ('a' + l).ToString();
                            all.Add(tmp1 + tmp2 + tmp3 + tmp4);
                        }
                    }
                }
            }

            Dictionary<string, int> coutDic = new Dictionary<string, int>();
            foreach (var x in all)
            {
                var k = RouteRule.Instance.GetTableNameIndex(x);
                if (!coutDic.ContainsKey(k))
                {
                    coutDic[k] = 1;
                }
                else
                {
                    ++coutDic[k];
                }

            }
            foreach (var tmp in coutDic)
            {
                Console.WriteLine("key: " + tmp.Key + ", count: " + tmp.Value);
            }
            */

            Console.ReadLine();
        }
    }
}

