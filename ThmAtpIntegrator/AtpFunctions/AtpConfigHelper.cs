//-----------------------------------------------------------------------------
// File Name   : AtpConfigHelper
// Author      : junlei
// Date        : 12/9/2020 5:03:18 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.IO;
using Newtonsoft.Json;
using ThmCommon.Config;

namespace ThmAtpIntegrator.AtpFunctions {
    public class AtpConfigHelper : IConfigHelper {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        internal static AtpConfig Config { get; private set; }
        private static readonly string AtpConfigPath = Directory.GetCurrentDirectory() + "/config/atp.json";

        public bool LoadConfig() {
            Config = JsonConvert.DeserializeObject<AtpConfig>(File.ReadAllText(AtpConfigPath));
            string err = string.Empty;
            if (!Config.IsValid(ref err)) {
                Logger.Error("atp.json is not valid: {}", err);
                return false;
            }

            return true;
        }

        public void SaveConfig() {
            var rlt = JsonConvert.SerializeObject(Config, Formatting.Indented);
            if (File.Exists(AtpConfigPath)) {
                File.Move(AtpConfigPath, $"{AtpConfigPath}_{DateTime.Now}.bk");
            }

            using (var sw = new StreamWriter(AtpConfigPath)) {
                sw.Write(rlt);
            }
        }

        public IConfig GetConfig() {
            return Config;
        }
    }
}
