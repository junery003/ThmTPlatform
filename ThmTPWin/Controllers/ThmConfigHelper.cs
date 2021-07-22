//-----------------------------------------------------------------------------
// File Name   : ThmConfigHelper
// Author      : junlei
// Date        : 2/26/2020 5:03:10 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.IO;
using Newtonsoft.Json;
using ThmCommon.Config;
using ThmCommon.Handlers;

namespace ThmTPWin.Controllers {
    /// <summary>
    /// ThmConfigHelper
    /// </summary>
    public class ThmConfigHelper : IConfigHelper {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private static readonly string ThmConfigPath = Directory.GetCurrentDirectory() + "/config/config.json";
        private static ThmConfig Config;

        public bool LoadConfig() {
            Config = JsonConvert.DeserializeObject<ThmConfig>(File.ReadAllText(ThmConfigPath));

            string err = string.Empty;
            if (!Config.IsValid(ref err)) {
                Logger.Error("Config file is not valid: " + err);
                return false;
            }

            /* disable 
            if (!MongoUtil.Auth(Config.Login.UserID, Config.Login.Password)) {
                Logger.Error("Thm not valid user:{}", Config.Login.UserID);
                return false;
            }
            */

            InstrumentHandlerBase.EnableSave2DB = Config.Save2DB;
            return true;
        }

        public void SaveConfig() {
            var rlt = JsonConvert.SerializeObject(Config, Formatting.Indented);
            if (File.Exists(ThmConfigPath)) {
                File.Move(ThmConfigPath, $"{ThmConfigPath}_{DateTime.Now}.bk");
            }

            using (var sw = new StreamWriter(ThmConfigPath)) {
                sw.Write(rlt);
            }
        }

        public IConfig GetConfig() {
            return Config;
        }
    }
}
