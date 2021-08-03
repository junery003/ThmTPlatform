using Microsoft.Extensions.Logging;

namespace ThmTPService.Services {
    public class MarketDataService : MarketData.MarketDataBase {
        private readonly ILogger<MarketDataService> _logger;
        public MarketDataService(ILogger<MarketDataService> logger) {
            _logger = logger;
        }
    }
}
