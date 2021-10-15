//-----------------------------------------------------------------------------
// File Name   : ZmqHelper
// Author      : junlei
// Date        : 8/21/2021 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using NetMQ;
using NetMQ.Sockets;
using Newtonsoft.Json;
using System.Threading.Tasks;
using ThmCtpIntegrator.Models;

namespace ThmCtpIntegrator.CtpHandler {
    internal class ZmqHelper {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private bool _isStopped = false;
        private readonly CtpConnector _conn;

        internal ZmqHelper(CtpConnector conn, string streamDataSvr, string streamTradeSvr) {
            _conn = conn;

            var task1 = Task.Run(() => MarketServer(streamDataSvr));
            var task2 = Task.Run(() => TradeServer(streamTradeSvr));

            Task.WhenAll(task1, task2).ConfigureAwait(false);
        }

        private void MarketServer(string serverAddress) {
            using (var server = new PairSocket()) {
                Logger.Info("CTP - ZServer(Market Data) Running: {}...", serverAddress);
                server.Bind(serverAddress);

                while (!_isStopped) {
                    ProcessMarketData(server.ReceiveFrameString());
                }
            }
        }

        private void TradeServer(string serverAddress) {
            using (var server = new PairSocket()) {
                Logger.Info("CTP - ZServer(Trade) Running: {}...", serverAddress);
                server.Bind(serverAddress);

                while (!_isStopped) {
                    ProcessTradeData(server.ReceiveFrameString());
                }
            }
        }

        private void ProcessMarketData(string msg) {
            if (msg.Contains("BidPrice1")) {
                var data = JsonConvert.DeserializeObject<CtpDepthData>(msg);
                _conn.InstrumentHandlerDic[data.InstrumentID].ParseMarketDepthData(data);
            }
            else if (msg.StartsWith("DISCONNECTED")) {
                Logger.Warn("CTP MD DISCONNECTED");
                _conn.MarketDataDisconnected();
            }
            else if (msg.StartsWith("CONNECTED")) {
                Logger.Info("CTP MD CONNECTED");
                _conn.MarketDataConnected();
            }
        }

        private void ProcessTradeData(string msg) {
            if (msg.Contains("FillPrice") || msg.Contains("LimitPrice")) { // order //determine if order update or a trade
                var data = JsonConvert.DeserializeObject<CtpOrderData>(msg);
                _conn.InstrumentHandlerDic[data.InstrumentID].ParseOrderData(data);
            }
            else if (msg.Contains("PriceTick")) { // instrument
                var data = JsonConvert.DeserializeObject<CtpInstrumentInfo>(msg);
                if (_conn.InstrumentHandlerDic.ContainsKey(data.InstrumentID)) {
                    _conn.InstrumentHandlerDic[data.InstrumentID].ParseInstrumentInfo(data);
                }
                else {
                    Logger.Warn($"{data.InstrumentID} not subscribed");
                }
            }
            else if (msg.Contains("Position")) {
                //var obj = JsonConvert.DeserializeObject<CTPPosition>(msg);
                //CTPPosData posObj = CTPDataStream1.PosBuffer[sequenceNo];
                //ThemeUtil.Copy(obj, posObj);
                //posObj.instrumentID = obj.instrumentID;
                //posObj.provider = obj.provider;
            }
            else if (msg.StartsWith("DISCONNECTED")) {
                Logger.Warn("CTP TD DISCONNECTED");
                _conn.TradeDisconnected();
            }
            else if (msg.StartsWith("CONNECTED")) {
                Logger.Info("CTP TD CONNECTED");
                _conn.TradeConnected();
            }
        }

        public void Dispose() {
            _isStopped = true;
            DllHelper.Dismental();
        }
    }
}
