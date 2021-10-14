//-----------------------------------------------------------------------------
// File Name   : TitanInstrumentHandler
// Author      : junlei
// Date        : 11/4/2020 11:03:27 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using ThmCommon.Handlers;
using ThmCommon.Models;
using ThmCommon.Utilities;
using ThmTitanIntegrator.Models;

namespace ThmTitanIntegrator.TitanHandler {
    public class TitanInstrumentHandler : InstrumentHandlerBase {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        protected override AlgoHandlerBase AlgoHandler => _algoHandler;
        protected override TradeHandlerBase TradeHandler => _tradeHandler;

        private readonly TitanTradeHandler _tradeHandler;
        private readonly TitanAlgoHandler _algoHandler;

        private const string DT_FORMAT = "yyyy-MM-dd HH:mm:ss.fffffff";
        private MarketDepthData _curMarketDepthData;

        public TitanInstrumentHandler(string instrumentID, string acount) {
            InstrumentInfo = new ThmInstrumentInfo {
                Provider = EProviderType.TITAN, // "Titan",
                Exchange = "SGX",
                ProductType = "Future",
                Product = instrumentID.Substring(0, instrumentID.Length - 3),
                //Product = instrumentID,
                InstrumentID = instrumentID, // "FEFH21"
                Contract = instrumentID
            };

            CurAccount = acount;
            Accounts = new List<string> { acount };

            _tradeHandler = new TitanTradeHandler(this);
            _algoHandler = new TitanAlgoHandler(_tradeHandler);
        }

        public override bool Start() {
            Logger.Info($"Subscribing contract {InstrumentInfo.InstrumentID}");
            DllHelper.SubscribeContract(InstrumentInfo.InstrumentID);

            return true;
        }

        public override void Stop() {
            Logger.Info($"Unsubscribing contract {InstrumentInfo.InstrumentID}");
            DllHelper.UnsubscribeContract(InstrumentInfo.InstrumentID);
        }

        public override int GetPosition() {
            return _tradeHandler.GetPosition();
        }

        internal void ParseInstrumentInfo(TitanInstrumentInfo instrumentInfo) {
            InstrumentInfo.TickSize = instrumentInfo.TickSize;
            Logger.Info($"Ticksize for instrument {instrumentInfo.Symbol} is {InstrumentInfo.TickSize}");
        }

        internal void ParseMarketData(TitanDepthData depthDataMsg) {
            BuildDepthData(depthDataMsg);
            UpdateMarketData(_curMarketDepthData);
        }

        private MarketDepthData BuildDepthData(TitanDepthData mdMsg) {
            if (_curMarketDepthData == null) {
                _curMarketDepthData = new MarketDepthData() {
                    Provider = mdMsg.Provider,
                    Exchange = mdMsg.Exchange,
                    ProductType = mdMsg.ProductType,
                    Product = mdMsg.InstrumentID.Substring(0, mdMsg.InstrumentID.Length - 3), // "FEFH01"
                    Contract = mdMsg.InstrumentID, //mdMsg.Contract,
                    InstrumentID = mdMsg.InstrumentID,
                };
            }

            _curMarketDepthData.DateTime = TimeUtil.String2DateTime(mdMsg.DateTime.Substring(0, DT_FORMAT.Length), DT_FORMAT);
            _curMarketDepthData.LocalDateTime = DateTime.Now; // TimeUtil.MilliSeconds2DateTime(atpMDMsg.LocalTime);

            _curMarketDepthData.HighPrice = mdMsg.HighPrice;
            _curMarketDepthData.LowPrice = mdMsg.LowPrice;
            _curMarketDepthData.OpenPrice = mdMsg.OpenPrice;
            _curMarketDepthData.TotalTradedQuantity = mdMsg.Volume;
            //CurMarketDepthData.LastTradedQuantity = atpObj.Volume;
            _curMarketDepthData.LastTradedPrice = mdMsg.LastPrice;
            _curMarketDepthData.SettlementPrice = mdMsg.SettlementPrice;

            _curMarketDepthData.DirectAskPrice = mdMsg.DirectAskPrice;
            _curMarketDepthData.DirectAskQty = mdMsg.DirectAskQty;
            _curMarketDepthData.DirectBidPrice = mdMsg.DirectBidPrice;
            _curMarketDepthData.DirectBidQty = mdMsg.DirectBidQty;

            _curMarketDepthData.AskPrice1 = mdMsg.AskPrice1;
            _curMarketDepthData.AskPrice2 = mdMsg.AskPrice2;
            _curMarketDepthData.AskPrice3 = mdMsg.AskPrice3;
            _curMarketDepthData.AskPrice4 = mdMsg.AskPrice4;
            _curMarketDepthData.AskPrice5 = mdMsg.AskPrice5;

            _curMarketDepthData.AskQty1 = mdMsg.AskQty1;
            _curMarketDepthData.AskQty2 = mdMsg.AskQty2;
            _curMarketDepthData.AskQty3 = mdMsg.AskQty3;
            _curMarketDepthData.AskQty4 = mdMsg.AskQty4;
            _curMarketDepthData.AskQty5 = mdMsg.AskQty5;

            _curMarketDepthData.BidPrice1 = mdMsg.BidPrice1;
            _curMarketDepthData.BidPrice2 = mdMsg.BidPrice2;
            _curMarketDepthData.BidPrice3 = mdMsg.BidPrice3;
            _curMarketDepthData.BidPrice4 = mdMsg.BidPrice4;
            _curMarketDepthData.BidPrice5 = mdMsg.BidPrice5;

            _curMarketDepthData.BidQty1 = mdMsg.BidQty1;
            _curMarketDepthData.BidQty2 = mdMsg.BidQty2;
            _curMarketDepthData.BidQty3 = mdMsg.BidQty3;
            _curMarketDepthData.BidQty4 = mdMsg.BidQty4;
            _curMarketDepthData.BidQty5 = mdMsg.BidQty5;

            return _curMarketDepthData;
        }

        internal void ParseOrderData(TitanOrderData titanOrder) {
            UpdateOrderData(_tradeHandler.BuildOrderData(titanOrder));
        }

        public override void Dispose() {
            _tradeHandler.Dispose();
            _algoHandler.Dispose();
        }
    }
}
