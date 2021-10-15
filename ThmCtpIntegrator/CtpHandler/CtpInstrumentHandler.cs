//-----------------------------------------------------------------------------
// File Name   : CtpInstrumentHandler
// Author      : junlei
// Date        : 5/29/2020 5:10:34 PM
// Description : 
// Version     : 1.0.0
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using ThmCommon.Handlers;
using ThmCommon.Models;
using ThmCommon.Utilities;
using ThmCtpIntegrator.CtpFunctions;
using ThmCtpIntegrator.Models;

namespace ThmCtpIntegrator.CtpHandler {
    public class CtpInstrumentHandler : InstrumentHandlerBase {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        protected override AlgoHandlerBase AlgoHandler => _algoHandler;
        protected override TradeHandlerBase TradeHandler => _tradeHandler;

        private readonly CtpTradeHandler _tradeHandler;
        private readonly CtpAlgoHandler _algoHandler;
        public CtpInstrumentHandler(string instrumentID, string exchange) {
            InstrumentInfo = new ThmInstrumentInfo {
                Provider = EProviderType.CTP,
                Exchange = exchange,
                InstrumentID = instrumentID
            };
            (InstrumentInfo.Product, InstrumentInfo.Contract) = CtpUtil.ExtractContract(instrumentID);

            _tradeHandler = new CtpTradeHandler(this);
            _algoHandler = new CtpAlgoHandler(_tradeHandler);
        }

        public override bool Start() {
            Logger.Info("Starting instrument: {}", InstrumentInfo.InstrumentID);
            if (DllHelper.SubscribeContract(InstrumentInfo.InstrumentID, InstrumentInfo.Exchange) != 0) {
                Logger.Error($"Failed to subscribe contract {InstrumentInfo.InstrumentID}");

                return false;
            }

            return true;
        }

        public override void Stop() {
            Logger.Info("Stopping instrument {}", InstrumentInfo.InstrumentID);
            DllHelper.UnsubcribeContract(InstrumentInfo.InstrumentID);
        }

        public override int GetPosition() {
            return _tradeHandler.GetPosition();
        }

        internal void ParseInstrumentInfo(CtpInstrumentInfo instrumentInfo) {
            InstrumentInfo.TickSize = instrumentInfo.PriceTick;
            Logger.Info($"Ticksize for instrument {instrumentInfo.InstrumentID} is {InstrumentInfo.TickSize}");
        }

        internal void ParseMarketDepthData(CtpDepthData depthDataMsg) {
            BuildDepthData(depthDataMsg);

            UpdateMarketData();
        }

        private MarketDepthData BuildDepthData(CtpDepthData mdMsg) {
            if (CurMarketDepthData == null) {
                CurMarketDepthData = new MarketDepthData() {
                    Provider = mdMsg.Provider,  // "CTP"
                    Exchange = string.IsNullOrEmpty(mdMsg.Exchange) ? InstrumentInfo.Exchange : mdMsg.Exchange,
                    ProductType = "Future",  // by default //_instrument.Product.Type.ToString(),
                    Product = mdMsg.Product, //obj.Product.Name,
                    Contract = mdMsg.Contract, //_instrument.Product.Alias
                    InstrumentID = mdMsg.InstrumentID,
                };
            }

            CurMarketDepthData.DateTime = TimeUtil.String2DateTime(mdMsg.DateTime);
            CurMarketDepthData.LocalDateTime = DateTime.Now; // TimeUtil.MilliSeconds2DateTime(atpMDMsg.LocalTime);

            CurMarketDepthData.HighPrice = (decimal)(mdMsg.HighPrice == double.MaxValue ? 0 : mdMsg.HighPrice);
            CurMarketDepthData.LowPrice = (decimal)(mdMsg.LowPrice == double.MaxValue ? 0 : mdMsg.LowPrice);
            CurMarketDepthData.OpenPrice = (decimal)(mdMsg.OpenPrice == double.MaxValue ? 0 : mdMsg.OpenPrice);
            CurMarketDepthData.TotalTradedQuantity = mdMsg.Volume;
            //CurDepthData.LastTradedQuantity = atpObj.Volume;
            CurMarketDepthData.LastTradedPrice = (decimal)mdMsg.LastPrice;
            CurMarketDepthData.SettlementPrice = (decimal)(mdMsg.SettlementPrice == double.MaxValue ? 0 : mdMsg.SettlementPrice);

            CurMarketDepthData.DirectAskPrice = (decimal)mdMsg.DirectAskPrice;
            CurMarketDepthData.DirectAskQty = mdMsg.DirectAskQty;
            CurMarketDepthData.DirectBidPrice = (decimal)mdMsg.DirectBidPrice;
            CurMarketDepthData.DirectBidQty = mdMsg.DirectBidQty;

            CurMarketDepthData.AskPrice1 = (decimal)(mdMsg.AskPrice1 == double.MaxValue ? 0 : mdMsg.AskPrice1);
            CurMarketDepthData.AskPrice2 = (decimal)mdMsg.AskPrice2;
            CurMarketDepthData.AskPrice3 = (decimal)mdMsg.AskPrice3;
            CurMarketDepthData.AskPrice4 = (decimal)mdMsg.AskPrice4;
            CurMarketDepthData.AskPrice5 = (decimal)mdMsg.AskPrice5;

            CurMarketDepthData.AskQty1 = mdMsg.AskQty1;
            CurMarketDepthData.AskQty2 = mdMsg.AskQty2;
            CurMarketDepthData.AskQty3 = mdMsg.AskQty3;
            CurMarketDepthData.AskQty4 = mdMsg.AskQty4;
            CurMarketDepthData.AskQty5 = mdMsg.AskQty5;

            CurMarketDepthData.BidPrice1 = (decimal)(mdMsg.BidPrice1 == double.MaxValue ? 0 : mdMsg.BidPrice1);
            CurMarketDepthData.BidPrice2 = (decimal)mdMsg.BidPrice2;
            CurMarketDepthData.BidPrice3 = (decimal)mdMsg.BidPrice3;
            CurMarketDepthData.BidPrice4 = (decimal)mdMsg.BidPrice4;
            CurMarketDepthData.BidPrice5 = (decimal)mdMsg.BidPrice5;

            CurMarketDepthData.BidQty1 = mdMsg.BidQty1;
            CurMarketDepthData.BidQty2 = mdMsg.BidQty2;
            CurMarketDepthData.BidQty3 = mdMsg.BidQty3;
            CurMarketDepthData.BidQty4 = mdMsg.BidQty4;
            CurMarketDepthData.BidQty5 = mdMsg.BidQty5;

            return CurMarketDepthData;
        }

        internal void ParseOrderData(CtpOrderData orderMsg) {
            UpdateOrderData(_tradeHandler.BuildOrderData(orderMsg));
        }

        public override void Dispose() {
            //Stop();
            _tradeHandler.Dispose();
            _algoHandler.Dispose();
        }
    }
}
