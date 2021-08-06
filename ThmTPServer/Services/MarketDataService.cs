//-----------------------------------------------------------------------------
// File Name   : MarketDataService
// Author      : junlei
// Date        : 8/5/2021 1:12:16 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Microsoft.Extensions.Logging;
using ThmServices;

namespace ThmTPService.Services {
    /// <summary>
    /// MarketDataService
    /// </summary>
    public class MarketDataService : MarketData.MarketDataBase {
        private readonly ILogger<MarketDataService> _logger;
        public MarketDataService(ILogger<MarketDataService> logger) {
            _logger = logger;
        }
    }
}
