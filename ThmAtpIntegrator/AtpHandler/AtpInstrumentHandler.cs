//-----------------------------------------------------------------------------
// File Name   : AtpInstrumentHandler
// Author      : junlei
// Date        : 5/29/2020 5:10:34 PM
// Description : 
// Version     : 1.0.0
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using ThmAtpIntegrator.AtpFunctions;
using ThmAtpIntegrator.Models;
using ThmCommon.Handlers;
using ThmCommon.Models;
using ThmCommon.Utilities;

namespace ThmAtpIntegrator.AtpHandler {
    public class AtpInstrumentHandler : InstrumentHandlerBase {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private MarketDepthData _curDepthData;
        protected override AlgoHandlerBase AlgoHandler => _algoHandler;
        protected override TradeHandlerBase TradeHandler => _tradeHandler;

        private readonly AtpTradeHandler _tradeHandler;
        private readonly AtpAlgoHandler _algoHandler;
        public AtpInstrumentHandler(string instrumentID) {
            InstrumentInfo = new ThmInstrumentInfo {
                Provider = EProviderType.ATP, // "ATP",
                Type = "Future",
                InstrumentID = instrumentID
            };
            (InstrumentInfo.Exchange, InstrumentInfo.Product, InstrumentInfo.Contract) = AtpUtil.ExtractContract(instrumentID);

            _tradeHandler = new AtpTradeHandler(this);
            _algoHandler = new AtpAlgoHandler(_tradeHandler);
        }

        public override bool Start() {
            Logger.Info("Starting instrument: {}", InstrumentInfo.InstrumentID);
            if (DllHelper.SubscribeContract(InstrumentInfo.InstrumentID) != 0) {
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

        internal void ParseInstrumentInfo(AtpInstrumentInfo instrumentInfo) {
            InstrumentInfo.TickSize = instrumentInfo.PriceTick;
            Logger.Info($"Ticksize for instrument {instrumentInfo.InstrumentID} is {InstrumentInfo.TickSize}");
        }

        internal void ParseMarketDepthData(AtpDepthData depthDataMsg) {
            BuildDepthData(depthDataMsg);

            UpdateMarketData(_curDepthData);
        }

        private MarketDepthData BuildDepthData(AtpDepthData mdMsg) {
            if (_curDepthData == null) {
                _curDepthData = new MarketDepthData() {
                    Provider = mdMsg.Provider,  // ATP
                    Exchange = mdMsg.Exchange,
                    ProductType = "Future",   // by default //Product.Type,
                    Product = mdMsg.Product,  //Product.Name,                
                    Contract = mdMsg.Contract, //Product.Alias
                    InstrumentID = mdMsg.InstrumentID,
                };
            }

            _curDepthData.DateTime = TimeUtil.String2DateTime(mdMsg.DateTime);
            _curDepthData.LocalDateTime = DateTime.Now; // TimeUtil.MilliSeconds2DateTime(atpMDMsg.LocalTime);

            _curDepthData.HighPrice = mdMsg.HighPrice;
            _curDepthData.LowPrice = mdMsg.LowPrice;
            _curDepthData.OpenPrice = mdMsg.OpenPrice;
            _curDepthData.TotalTradedQuantity = mdMsg.Volume;
            _curDepthData.LastTradedPrice = mdMsg.LastPrice;
            _curDepthData.SettlementPrice = mdMsg.SettlementPrice;

            _curDepthData.DirectAskPrice = mdMsg.DirectAskPrice;
            _curDepthData.DirectAskQty = mdMsg.DirectAskQty;
            _curDepthData.DirectBidPrice = mdMsg.DirectBidPrice;
            _curDepthData.DirectBidQty = mdMsg.DirectBidQty;

            _curDepthData.AskPrice1 = mdMsg.AskPrice1;
            _curDepthData.AskPrice2 = mdMsg.AskPrice2;
            _curDepthData.AskPrice3 = mdMsg.AskPrice3;
            _curDepthData.AskPrice4 = mdMsg.AskPrice4;
            _curDepthData.AskPrice5 = mdMsg.AskPrice5;

            _curDepthData.AskQty1 = mdMsg.AskQty1;
            _curDepthData.AskQty2 = mdMsg.AskQty2;
            _curDepthData.AskQty3 = mdMsg.AskQty3;
            _curDepthData.AskQty4 = mdMsg.AskQty4;
            _curDepthData.AskQty5 = mdMsg.AskQty5;

            _curDepthData.BidPrice1 = mdMsg.BidPrice1;
            _curDepthData.BidPrice2 = mdMsg.BidPrice2;
            _curDepthData.BidPrice3 = mdMsg.BidPrice3;
            _curDepthData.BidPrice4 = mdMsg.BidPrice4;
            _curDepthData.BidPrice5 = mdMsg.BidPrice5;

            _curDepthData.BidQty1 = mdMsg.BidQty1;
            _curDepthData.BidQty2 = mdMsg.BidQty2;
            _curDepthData.BidQty3 = mdMsg.BidQty3;
            _curDepthData.BidQty4 = mdMsg.BidQty4;
            _curDepthData.BidQty5 = mdMsg.BidQty5;

            return _curDepthData;
        }

        internal void ParseOrderData(AtpOrderData orderMsg) {
            UpdateOrderData(_tradeHandler.BuildOrderData(orderMsg));
        }

        public override void Dispose() {
            //Stop();
            _tradeHandler.Dispose();
            _algoHandler.Dispose();
        }
    }
}
