//-----------------------------------------------------------------------------
// File Name   : CtpConfigHelper
// Author      : junlei
// Date        : 8/9/2021 5:03:18 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Newtonsoft.Json;
using System;
using System.IO;
using ThmCommon.Config;

namespace ThmCtpIntegrator.CtpFunctions {
    public class CtpConfigHelper : IConfigHelper {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        internal static CtpConfig Config { get; private set; }
        private static readonly string CtpConfigPath = Directory.GetCurrentDirectory() + "/config/ctp.json";

        public bool LoadConfig() {
            Config = JsonConvert.DeserializeObject<CtpConfig>(File.ReadAllText(CtpConfigPath));
            string err = string.Empty;
            if (!Config.IsValid(ref err)) {
                Logger.Error("atp.json is not valid: {}", err);
                return false;
            }

            return true;
        }

        public void SaveConfig() {
            var rlt = JsonConvert.SerializeObject(Config, Formatting.Indented);
            if (File.Exists(CtpConfigPath)) {
                File.Move(CtpConfigPath, $"{CtpConfigPath}_{DateTime.Now}.bk");
            }

            using (var sw = new StreamWriter(CtpConfigPath)) {
                sw.Write(rlt);
            }
        }

        public IConfig GetConfig() {
            return Config;
        }
    }
}
