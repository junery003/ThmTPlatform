//-----------------------------------------------------------------------------
// File Name   : PriceLadderVM
// Author      : junlei
// Date        : 10/12/2020 05:03:17 PM
// Description : 
// Version     : 1.0.0
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Windows.Data;
using System.Windows.Media;
using Prism.Mvvm;
using ThmCommon.Models;
using ThmTPWin.Models;

namespace ThmTPWin.ViewModels {
    public class PriceLadderVM : BindableBase {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        #region algo
        public int _workingAlgoCount = 0;
        public int WorkingAlgoCount {
            get => _workingAlgoCount;
            set => SetProperty(ref _workingAlgoCount, value);
        }

        private string _cancelAlgoBtnContent = "CXL Algo(s)";
        public string CancelAlgoBtnContent {
            get => _cancelAlgoBtnContent;
            set => SetProperty(ref _cancelAlgoBtnContent, value);
        }

        private bool _isCancelEnabled = true;
        public bool IsCancelEnabled {
            get => _isCancelEnabled;
            set => SetProperty(ref _isCancelEnabled, value);
        }

        #endregion algo

        #region HLOV
        private string _netChange;
        public string NetChange {
            get => _netChange;
            set => SetProperty(ref _netChange, value);
        }

        private Brush _netChangeForeColor;
        public Brush NetChangeForeColor {
            get => _netChangeForeColor;
            set => SetProperty(ref _netChangeForeColor, value);
        }

        private decimal _highPrice;
        public decimal HighPrice {
            get => _highPrice;
            set => SetProperty(ref _highPrice, value);
        }

        private decimal _lowPrice;
        public decimal LowPrice {
            get => _lowPrice;
            set => SetProperty(ref _lowPrice, value);
        }

        private decimal _openPrice;
        public decimal OpenPrice {
            get => _openPrice;
            set => SetProperty(ref _openPrice, value);
        }

        private int _volumn;
        public int Volumn {
            get => _volumn;
            set => SetProperty(ref _volumn, value);
        }
        #endregion HLOV

        public ObservableCollection<MarketDataView> MarketData { get; } = new ObservableCollection<MarketDataView>();

        private readonly decimal _tickSize;
        private readonly decimal _ladderSteps;
        private readonly object _lock = new object();
        public PriceLadderVM(decimal tickSize) {
            BindingOperations.EnableCollectionSynchronization(MarketData, _lock);

            _tickSize = tickSize;
            _ladderSteps = 1000 * _tickSize + 100;
        }

        internal void PopulateHLOV(MarketDepthData data) {
            HighPrice = data.HighPrice;
            LowPrice = data.LowPrice;
            OpenPrice = data.OpenPrice;
            Volumn = data.TotalTradedQuantity;

            var netChange = data.LastTradedPrice - data.SettlementPrice;
            NetChange = netChange.ToString("+0;-#");
            NetChangeForeColor = netChange >= 0 ? Brushes.Green : Brushes.Red;
        }

        private readonly Dictionary<decimal, MarketDataView> _priceLadderDic = new Dictionary<decimal, MarketDataView>(); // price, row
        private readonly Dictionary<decimal, bool> _previousLevelDic = new Dictionary<decimal, bool>(); // price, is Ask price?
        private int _bestAskIdx = 0;
        private int _bestBidIdx = 0;
        internal void PopulateMarketData(MarketDepthData depthData) {
            if (MarketData.Count <= 0) { // first time only
                _priceLadderDic[0] = new MarketDataView(0);

                decimal low = depthData.BidPrice1 - _ladderSteps;
                for (decimal price = depthData.AskPrice1 + _ladderSteps; decimal.Compare(price, low) >= 0; price -= _tickSize) {
                    var dom = new MarketDataView(price);
                    MarketData.Add(dom);
                    _priceLadderDic[price] = dom;
                }
            }
            else {
                decimal high = depthData.AskPrice1 + _ladderSteps;
                if (decimal.Compare(MarketData[0].Price, high) <= 0) {
                    for (var price = MarketData[0].Price + _tickSize; decimal.Compare(price, high) <= 0; price += _tickSize) {
                        var dom = new MarketDataView(price);
                        MarketData.Insert(0, dom);

                        _priceLadderDic[price] = dom;
                    }
                }

                decimal low = depthData.BidPrice1 - _ladderSteps;
                if (decimal.Compare(MarketData[MarketData.Count - 1].Price, low) >= 0) {
                    for (var price = MarketData[MarketData.Count - 1].Price - _tickSize; decimal.Compare(price, low) >= 0; price -= _tickSize) {
                        var dom = new MarketDataView(price);
                        MarketData.Add(dom);

                        _priceLadderDic[price] = dom;
                    }
                }
            }

            // set all the data to null first
            foreach (var kv in _previousLevelDic) {
                if (kv.Value) { // ask price
                    _priceLadderDic[kv.Key].Asks = null;
                }
                else {
                    _priceLadderDic[kv.Key].Bids = null;
                }
            }
            //_previousLevels.Clear();

            if (depthData.AskQty1 == 0) {
                _priceLadderDic[depthData.AskPrice1].Asks = null;
            }
            else {
                _priceLadderDic[depthData.AskPrice1].Asks = depthData.AskQty1;
                _previousLevelDic[depthData.AskPrice1] = true;

                _bestAskIdx = MarketData.IndexOf(_priceLadderDic[depthData.AskPrice1]);
            }

            if (depthData.AskQty2 == 0) {
                _priceLadderDic[depthData.AskPrice2].Asks = null;
            }
            else {
                _priceLadderDic[depthData.AskPrice2].Asks = depthData.AskQty2;
                _previousLevelDic[depthData.AskPrice2] = true;
            }

            if (depthData.AskQty3 == 0) {
                _priceLadderDic[depthData.AskPrice3].Asks = null;
            }
            else {
                _priceLadderDic[depthData.AskPrice3].Asks = depthData.AskQty3;
                _previousLevelDic[depthData.AskPrice3] = true;
            }

            if (depthData.AskQty4 == 0) {
                _priceLadderDic[depthData.AskPrice4].Asks = null;
            }
            else {
                _priceLadderDic[depthData.AskPrice4].Asks = depthData.AskQty4;
                _previousLevelDic[depthData.AskPrice4] = true;
            }

            if (depthData.AskQty5 == 0) {
                _priceLadderDic[depthData.AskPrice5].Asks = null;
            }
            else {
                _priceLadderDic[depthData.AskPrice5].Asks = depthData.AskQty5;
                _previousLevelDic[depthData.AskPrice5] = true;
            }

            if (depthData.BidQty1 == 0) {
                _priceLadderDic[depthData.BidPrice1].Bids = null;
            }
            else {
                _priceLadderDic[depthData.BidPrice1].Bids = depthData.BidQty1;
                _previousLevelDic[depthData.BidPrice1] = false;

                _bestBidIdx = MarketData.IndexOf(_priceLadderDic[depthData.BidPrice1]);
            }

            if (depthData.BidQty2 == 0) {
                _priceLadderDic[depthData.BidPrice2].Bids = null;
            }
            else {
                _priceLadderDic[depthData.BidPrice2].Bids = depthData.BidQty2;
                _previousLevelDic[depthData.BidPrice2] = false;
            }

            if (depthData.BidQty3 == 0) {
                _priceLadderDic[depthData.BidPrice3].Bids = null;
            }
            else {
                _priceLadderDic[depthData.BidPrice3].Bids = depthData.BidQty3;
                _previousLevelDic[depthData.BidPrice3] = false;
            }

            if (depthData.BidQty4 == 0) {
                _priceLadderDic[depthData.BidPrice4].Bids = null;
            }
            else {
                _priceLadderDic[depthData.BidPrice4].Bids = depthData.BidQty4;
                _previousLevelDic[depthData.BidPrice4] = false;
            }

            if (depthData.BidQty5 == 0) {
                _priceLadderDic[depthData.BidPrice5].Bids = null;
            }
            else {
                _priceLadderDic[depthData.BidPrice5].Bids = depthData.BidQty5;
                _previousLevelDic[depthData.BidPrice5] = false;
            }
        }

        internal void IncreaseAlgo(decimal price) {
            _priceLadderDic[price].IncreaseAlgoCount();
            ++WorkingAlgoCount;

            CancelAlgoBtnContent = $"Cancel Algo(s) {WorkingAlgoCount}";
        }

        internal void DecreaseAlgo(decimal price) {
            if (!_priceLadderDic.ContainsKey(price)) {
                Logger.Warn($"Price {price} not in the price ladder");
                return;
            }

            if (_priceLadderDic[price].DecreaseAlgoCount()) {
                if (--WorkingAlgoCount <= 0) {
                    CancelAlgoBtnContent = $"Cancel Algo(s)";
                }
            }
        }

        internal int GetCenterIndex() {
            return (_bestAskIdx + _bestBidIdx) / 2;
        }
    }
}
