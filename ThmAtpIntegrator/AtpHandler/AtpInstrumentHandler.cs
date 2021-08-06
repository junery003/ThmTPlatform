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

        protected override AlgoHandlerBase AlgoHandler => _algoHandler;
        protected override TradeHandlerBase TradeHandler => _tradeHandler;

        private readonly AtpTradeHandler _tradeHandler;
        private readonly AtpAlgoHandler _algoHandler;
        public AtpInstrumentHandler(string instrumentID) {
            InstrumentInfo = new ThmInstrumentInfo {
                Provider = "ATP",
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

            UpdateMarketData();
        }

        private MarketDepthData BuildDepthData(AtpDepthData mdMsg) {
            if (CurMarketDepthData == null) {
                CurMarketDepthData = new MarketDepthData() {
                    Provider = mdMsg.Provider,  // "ATP"
                    Exchange = mdMsg.Exchange,
                    ProductType = "Future",  // by default //_instrument.Product.Type.ToString(),
                    Product = mdMsg.Product, //obj.Product.Name,                
                    Contract = mdMsg.Contract, //_instrument.Product.Alias
                    InstrumentID = mdMsg.InstrumentID,
                };
            }

            CurMarketDepthData.DateTime = TimeUtil.String2DateTime(mdMsg.DateTime);
            CurMarketDepthData.LocalDateTime = DateTime.Now; // TimeUtil.MilliSeconds2DateTime(atpMDMsg.LocalTime);

            CurMarketDepthData.HighPrice = mdMsg.HighPrice;
            CurMarketDepthData.LowPrice = mdMsg.LowPrice;
            CurMarketDepthData.OpenPrice = mdMsg.OpenPrice;
            CurMarketDepthData.TotalTradedQuantity = mdMsg.Volume;
            //CurDepthData.LastTradedQuantity = atpObj.Volume;
            CurMarketDepthData.LastTradedPrice = mdMsg.LastPrice;
            CurMarketDepthData.SettlementPrice = mdMsg.SettlementPrice;

            CurMarketDepthData.DirectAskPrice = mdMsg.DirectAskPrice;
            CurMarketDepthData.DirectAskQty = mdMsg.DirectAskQty;
            CurMarketDepthData.DirectBidPrice = mdMsg.DirectBidPrice;
            CurMarketDepthData.DirectBidQty = mdMsg.DirectBidQty;

            CurMarketDepthData.AskPrice1 = mdMsg.AskPrice1;
            CurMarketDepthData.AskPrice2 = mdMsg.AskPrice2;
            CurMarketDepthData.AskPrice3 = mdMsg.AskPrice3;
            CurMarketDepthData.AskPrice4 = mdMsg.AskPrice4;
            CurMarketDepthData.AskPrice5 = mdMsg.AskPrice5;

            CurMarketDepthData.AskQty1 = mdMsg.AskQty1;
            CurMarketDepthData.AskQty2 = mdMsg.AskQty2;
            CurMarketDepthData.AskQty3 = mdMsg.AskQty3;
            CurMarketDepthData.AskQty4 = mdMsg.AskQty4;
            CurMarketDepthData.AskQty5 = mdMsg.AskQty5;

            CurMarketDepthData.BidPrice1 = mdMsg.BidPrice1;
            CurMarketDepthData.BidPrice2 = mdMsg.BidPrice2;
            CurMarketDepthData.BidPrice3 = mdMsg.BidPrice3;
            CurMarketDepthData.BidPrice4 = mdMsg.BidPrice4;
            CurMarketDepthData.BidPrice5 = mdMsg.BidPrice5;

            CurMarketDepthData.BidQty1 = mdMsg.BidQty1;
            CurMarketDepthData.BidQty2 = mdMsg.BidQty2;
            CurMarketDepthData.BidQty3 = mdMsg.BidQty3;
            CurMarketDepthData.BidQty4 = mdMsg.BidQty4;
            CurMarketDepthData.BidQty5 = mdMsg.BidQty5;

            return CurMarketDepthData;
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
