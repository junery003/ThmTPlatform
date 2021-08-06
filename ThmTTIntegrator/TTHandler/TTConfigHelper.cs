//-----------------------------------------------------------------------------
// File Name   : TTConfigHelper
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

namespace ThmTTIntegrator.TTHandler {
    public class TTConfigHelper : IConfigHelper {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private static TTConfig Config;
        private static readonly string TTConfigPath = Directory.GetCurrentDirectory() + "/config/tt.json";

        public bool LoadConfig() {
            Config = JsonConvert.DeserializeObject<TTConfig>(File.ReadAllText(TTConfigPath));

            string err = string.Empty;
            if (!Config.IsValid(ref err)) {
                Logger.Error("TT Config file is not valid: " + err);
                return false;
            }

            return true;
        }

        public void SaveConfig() {
            var rlt = JsonConvert.SerializeObject(Config, Formatting.Indented);
            if (File.Exists(TTConfigPath)) {
                File.Move(TTConfigPath, $"{TTConfigPath}_{DateTime.Now}.bk");
            }

            using (var sw = new StreamWriter(TTConfigPath)) {
                sw.Write(rlt);
            }
        }

        public IConfig GetConfig() {
            return Config;
        }
    }
}
