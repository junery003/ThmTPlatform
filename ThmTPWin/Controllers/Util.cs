//-----------------------------------------------------------------------------
// File Name   : Util
// Author      : junlei
// Date        : 4/10/2020 10:50:13 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using NAudio.Wave;
using System;
using System.Media;
using System.Threading.Tasks;

namespace ThmTPWin.Controllers {
    public static class Util {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        public static async void Sound(string path) {
            await Task.Run(() => PlaySound(path)).ConfigureAwait(false);
        }

        private static void PlaySound(string path) {
            try {
                if (path != null && path.ToLower().EndsWith(".mp3")) {
                    using (var outputDevice = new WaveOutEvent()) { // WaveOutEvent
                        using (var auReader = new AudioFileReader(path)) {
                            outputDevice.Init(auReader);
                            outputDevice.Play();
                        }
                    }

                    return;
                }

                using (var player = new SoundPlayer(path)) {
                    player.LoadAsync();
                    player.Play();
                }
            }
            catch (Exception e) {
                Logger.Warn("Could not play sound: {} :{}", path, e);
            }
        }
    }
}
