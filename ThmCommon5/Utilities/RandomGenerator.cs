//-----------------------------------------------------------------------------
// File Name   : RandomGenerator
// Author      : junlei
// Date        : 10/27/2020 11:28:45 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Security.Cryptography;

namespace ThmCommon.Utilities {
    public sealed class RandomGenerator : IDisposable {
        private static readonly RNGCryptoServiceProvider _random = new RNGCryptoServiceProvider();

        // Generates a random string with a given size.    
        public string GenerateUniqueID(int length) {
            // We chose an encoding that fits 6 bits into every character,
            // so we can fit length*6 bits in total.
            // Each byte is 8 bits, so...
            int sufficientBufferSizeInBytes = (length * 6 + 7) / 8;

            var buffer = new byte[sufficientBufferSizeInBytes];
            _random.GetBytes(buffer);
            return Convert.ToBase64String(buffer).Substring(0, length);
        }

        public void Dispose() {
            _random.Dispose();
        }
    }
}
