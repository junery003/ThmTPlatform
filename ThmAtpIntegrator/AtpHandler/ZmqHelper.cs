//-----------------------------------------------------------------------------
// File Name   : ZmqHelper
// Author      : junlei
// Date        : 1/21/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Threading.Tasks;
using NetMQ;
using NetMQ.Sockets;
using Newtonsoft.Json;
using ThmAtpIntegrator.Models;

namespace ThmAtpIntegrator.AtpHandler {
    internal class ZmqHelper {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private bool _isStopped = false;
        private readonly AtpConnector _atpConnector;

        internal ZmqHelper(AtpConnector atpConnector, string streamDataSvr, string streamTradeSvr) {
            _atpConnector = atpConnector;

            var task1 = Task.Run(() => MarketServer(streamDataSvr));
            var task2 = Task.Run(() => TradeServer(streamTradeSvr));

            Task.WhenAll(task1, task2).ConfigureAwait(false);
        }

        private void MarketServer(string serverAddress) {
            using (var server = new PairSocket()) {
                Logger.Info("ATP - ZServer(Market Data) Running: {}...", serverAddress);
                server.Bind(serverAddress);

                while (!_isStopped) {
                    ProcessMarketData(server.ReceiveFrameString());
                }
            }
        }

        private void TradeServer(string serverAddress) {
            using (var server = new PairSocket()) {
                Logger.Info("ATP - ZServer(Trade) Running: {}...", serverAddress);
                server.Bind(serverAddress);

                while (!_isStopped) {
                    ProcessTradeData(server.ReceiveFrameString());
                }
            }
        }

        private void ProcessMarketData(string msg) {
            if (msg.Contains("BidPrice1")) {
                var data = JsonConvert.DeserializeObject<AtpDepthData>(msg);
                _atpConnector.InstrumentHandlerDic[data.InstrumentID].ParseMarketDepthData(data);
            }
            else if (msg.StartsWith("DISCONNECTED")) {
                Logger.Warn("ATP MD DISCONNECTED");
                _atpConnector.MarketDataDisconnected();
            }
            else if (msg.StartsWith("CONNECTED")) {
                Logger.Info("ATP MD CONNECTED");
                _atpConnector.MarketDataConnected();
            }
        }

        private void ProcessTradeData(string msg) {
            if (msg.Contains("FillPrice") || msg.Contains("LimitPrice")) { // order //determine if order update or a trade
                var data = JsonConvert.DeserializeObject<AtpOrderData>(msg);
                _atpConnector.InstrumentHandlerDic[data.InstrumentID].ParseOrderData(data);
            }
            else if (msg.Contains("PriceTick")) { // instrument
                var data = JsonConvert.DeserializeObject<AtpInstrumentInfo>(msg);
                _atpConnector.InstrumentHandlerDic[data.InstrumentID].ParseInstrumentInfo(data);
            }
            else if (msg.Contains("Position")) {
                //var obj = JsonConvert.DeserializeObject<AtpPosition>(msg);
                //AtpPosData posObj = AtpDataStream1.PosBuffer[sequenceNo];
                //ThemeUtil.Copy(obj, posObj);
                //posObj.instrumentID = obj.instrumentID;
                //posObj.provider = obj.provider;
            }
            else if (msg.StartsWith("DISCONNECTED")) {
                Logger.Warn("ATP TD DISCONNECTED");
                _atpConnector.TradeDisconnected();
            }
            else if (msg.StartsWith("CONNECTED")) {
                Logger.Info("ATP TD CONNECTED");
                _atpConnector.TradeConnected();
            }
        }

        public void Dispose() {
            _isStopped = true;
            DllHelper.Dismental();
        }
    }
}
