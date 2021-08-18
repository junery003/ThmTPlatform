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

        //public override MarketDepthData CurMarketDepthData { get; protected set; }

        protected override AlgoHandlerBase AlgoHandler => _algoHandler;
        protected override TradeHandlerBase TradeHandler => _tradeHandler;

        private readonly TitanTradeHandler _tradeHandler;
        private readonly TitanAlgoHandler _algoHandler;
        private const string DT_FORMAT = "yyyy-MM-dd HH:mm:ss.fffffff";
        public TitanInstrumentHandler(string instrumentID, string acount) {
            InstrumentInfo = new ThmInstrumentInfo {
                Provider = EProviderType.TITAN, // "Titan",
                Exchange = "SGX",
                Type = "Future",
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
            UpdateMarketData();
        }

        private MarketDepthData BuildDepthData(TitanDepthData mdMsg) {
            if (CurMarketDepthData == null) {
                CurMarketDepthData = new MarketDepthData() {
                    Provider = mdMsg.Provider,
                    Exchange = mdMsg.Exchange,
                    ProductType = mdMsg.ProductType,
                    Product = mdMsg.InstrumentID.Substring(0, mdMsg.InstrumentID.Length - 3), // "FEFH01"
                    Contract = mdMsg.InstrumentID, //mdMsg.Contract,
                    InstrumentID = mdMsg.InstrumentID,
                };
            }

            CurMarketDepthData.DateTime = TimeUtil.String2DateTime(mdMsg.DateTime.Substring(0, DT_FORMAT.Length), DT_FORMAT);
            CurMarketDepthData.LocalDateTime = DateTime.Now; // TimeUtil.MilliSeconds2DateTime(atpMDMsg.LocalTime);

            CurMarketDepthData.HighPrice = mdMsg.HighPrice;
            CurMarketDepthData.LowPrice = mdMsg.LowPrice;
            CurMarketDepthData.OpenPrice = mdMsg.OpenPrice;
            CurMarketDepthData.TotalTradedQuantity = mdMsg.Volume;
            //CurMarketDepthData.LastTradedQuantity = atpObj.Volume;
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

        internal void ParseOrderData(TitanOrderData titanOrder) {
            UpdateOrderData(_tradeHandler.BuildOrderData(titanOrder));
        }

        public override void Dispose() {
            _tradeHandler.Dispose();
            _algoHandler.Dispose();
        }
    }
}
