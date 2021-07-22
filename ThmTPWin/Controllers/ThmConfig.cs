//-----------------------------------------------------------------------------
// File Name   : ThmConfig
// Author      : junlei
// Date        : 2/26/2020 5:03:20 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Newtonsoft.Json;
using ThmCommon.Config;

namespace ThmTPWin.Controllers {
    /// <summary>
    /// setting for ThmConfig
    /// </summary>
    public class ThmConfig : IConfig {
        public ThmLogin Login { get; set; }
        public bool Enabled { get; set; } = true;

        [JsonProperty("Save2DB")]
        public bool Save2DB { get; set; } = false;

        [JsonProperty("Notification")]
        public bool EnableNofification { get; set; } = false;

        [JsonProperty("AtpEnabled")]
        public bool AtpEnabled { get; set; } = false;
        [JsonProperty("TTEnabled")]
        public bool TTEnabled { get; set; } = false;
        [JsonProperty("TitanEnabled")]
        public bool TitanEnabled { get; set; } = false;

        public bool IsValid(ref string err) { // login authentication
            if (AtpEnabled || TTEnabled || TitanEnabled) {
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
