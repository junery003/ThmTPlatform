//-----------------------------------------------------------------------------
// File Name   : MarketDataView
// Author      : junlei
// Date        : 3/13/2020 2:30:27 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Prism.Mvvm;

namespace ThmTPWin.Models {
    public sealed class MarketDataView : BindableBase {
        private decimal _price = 0;
        public decimal Price {
            get => _price;
            set => SetProperty(ref _price, value);
        }

        private int? _bids = null;
        public int? Bids {
            get => _bids;
            set => SetProperty(ref _bids, value);
        }

        private int? _asks = null;
        public int? Asks {
            get => _asks;
            set => SetProperty(ref _asks, value);
        }

        private int? _algoCount = null;
        public int? AlgoCount {
            get => _algoCount;
            set => SetProperty(ref _algoCount, value); 
        }

        private int? _ltq = null;
        public int? LTQ {
            get => _ltq;
            set => SetProperty(ref _ltq, value); 
        }

        public MarketDataView(decimal price, int? bids = null, int? asks = null) {
            Price = price;
            Bids = bids;
            Asks = asks;
        }

        internal void IncreaseAlgoCount() {
            if (AlgoCount == null) {
                AlgoCount = 1;
            }
            else {
                AlgoCount += 1;
            }
        }

        internal bool DecreaseAlgoCount() {
            if (AlgoCount == null || AlgoCount <= 0) {
                return false;
            }

            AlgoCount -= 1;
            if (AlgoCount <= 0) {
                AlgoCount = null;
            }

            return true;
        }
    }
}
