//-----------------------------------------------------------------------------
// File Name   : ConfigHelper
// Author      : junlei
// Date        : 7/30/2021 1:26:07 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

using System;
using System.IO;
using Newtonsoft.Json;
using ThmCommon.Config;

namespace ThmTPWin.Controllers {
    internal static class ConfigHelper {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        public static LoginConfig LoginCfg { get; set; }

        private static readonly string ConfigPath = Directory.GetCurrentDirectory() + "/config/config.json";
        static ConfigHelper() {
            LoginCfg = JsonConvert.DeserializeObject<LoginConfig>(File.ReadAllText(ConfigPath));
        }

        internal static bool Valid() {
            var err = string.Empty;
            if (!LoginCfg.IsValid(ref err)) {
                Logger.Error("Config file is not valid: " + err);
                return false;
            }

            /* disable 
            if (!MongoUtil.Auth(Config.Login.UserID, Config.Login.Password)) {
                Logger.Error("Thm not valid user:{}", Config.Login.UserID);
                return false;
            }
            */

            return true;
        }

        public static void SaveConfig() {
            var rlt = JsonConvert.SerializeObject(ConfigPath, Formatting.Indented);
            if (File.Exists(ConfigPath)) {
                File.Move(ConfigPath, $"{ConfigPath}_{DateTime.Now}.bk");
            }

            using (var sw = new StreamWriter(ConfigPath)) {
                sw.Write(rlt);
            }
        }
    }

    internal class LoginConfig {
        public ThmLogin Login { get; set; }
        public AtpLoginCfg AtpLogin { get; set; }
        public TTLoginCfg TTLogin { get; set; }
        public TitanLoginCfg TitanLogin { get; set; }

        public bool IsValid(ref string err) { // login account
            if (AtpLogin.Enabled || TTLogin.Enabled || TitanLogin.Enabled) {
                return true;
            }

            err = "Please enabled at least one provider.";
            return false;
        }
    }

    public class ThmLogin {
        public string UserID { get; set; }
        public string Password { get; set; }
    }
}
