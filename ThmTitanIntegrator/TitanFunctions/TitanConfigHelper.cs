//-----------------------------------------------------------------------------
// File Name   : ConfigHelper
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

namespace ThmTitanIntegrator.TitanFunctions {
    public class TitanConfigHelper : IConfigHelper {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private static TitanConfig Config;
        private static readonly string TitanConfigPath = Directory.GetCurrentDirectory() + "/config/titan.json";

        public bool LoadConfig() {
            Logger.Info("Loding config... " + TitanConfigPath);
            Config = JsonConvert.DeserializeObject<TitanConfig>(File.ReadAllText(TitanConfigPath));
            string err = string.Empty;
            if (!Config.IsValid(ref err)) {
                Logger.Error("Titan Config file is not valid: " + err);
                return false;
            }

            return true;
        }

        public IConfig GetConfig() {
            return Config;
        }

        public void SaveConfig() {
            var rlt = JsonConvert.SerializeObject(Config, Formatting.Indented);
            if (File.Exists(TitanConfigPath)) {
                File.Move(TitanConfigPath, $"{TitanConfigPath}_{DateTime.Now}.bk");
            }

            using (var sw = new StreamWriter(TitanConfigPath)) {
                sw.Write(rlt);
            }
        }
    }
}
