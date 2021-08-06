//-----------------------------------------------------------------------------
// File Name   : ZmqHelper
// Author      : junlei
// Date        : 12/21/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Threading.Tasks;
using NetMQ;
using NetMQ.Sockets;
using Newtonsoft.Json;
using ThmTitanIntegrator.Models;

namespace ThmTitanIntegrator.TitanHandler {
    internal class ZmqHelper {
        private static readonly NLog.ILogger Logger = NLog.LogManager.GetCurrentClassLogger();

        private bool _isStopped = false;
        private readonly TitanConnector _connector;

        internal ZmqHelper(TitanConnector connector, string streamDataSvr, string streamTradeSvr) {
            _connector = connector;

            var task1 = Task.Run(() => MarketServer(streamDataSvr));
            var task2 = Task.Run(() => TradeServer(streamTradeSvr));

            _ = Task.WhenAll(task1, task2).ConfigureAwait(false);
        }

        private void MarketServer(string serverAddress) {
            using (var server = new PairSocket()) {
                Logger.Info("Titan - ZServer(Market Data) Running: {}...", serverAddress);
                server.Bind(serverAddress);   //server.Subscribe("B");

                while (!_isStopped) {
                    ProcessMarketData(server.ReceiveFrameString());
                }
            }
        }

        private void TradeServer(string serverAddress) {
            using (var responder = new PairSocket()) {
                Logger.Info("Titan - ZServer(Trade) Running: {}...", serverAddress);
                responder.Bind(serverAddress);

                while (!_isStopped) {
                    ProcessTradeData(responder.ReceiveFrameString());
                }
            }
        }

        private void ProcessMarketData(string msg) {
            if (msg.Contains("BidPrice1")) {
                var data = JsonConvert.DeserializeObject<TitanDepthData>(msg);
                _connector.InstrumentHandlerDic[data.InstrumentID].ParseMarketData(data);
            }
            else if (msg.Contains("TickSize")) { // instrument
                var data = JsonConvert.DeserializeObject<TitanInstrumentInfo>(msg);
                _connector.InstrumentHandlerDic[data.Symbol].ParseInstrumentInfo(data);
            }
            else if (msg.StartsWith("DISCONNECTED")) {
                Logger.Warn("Titan MD DISCONNECTED");
                //Task.Delay(1000).Wait();
                _connector.MarketDataDisconnected();
            }
            else if (msg.StartsWith("CONNECTED")) {
                Logger.Info("Titan MD CONNECTED");
                _connector.MarketDataConnected();
            }
        }

        private void ProcessTradeData(string msg) {
            if (msg.Contains("OrderToken")) { // order update or a trade
                var data = JsonConvert.DeserializeObject<TitanOrderData>(msg);
                _connector.InstrumentHandlerDic[data.InstrumentID].ParseOrderData(data);
            }
            else if (msg.Contains("Position")) {
            }
            else if (msg.StartsWith("DISCONNECTED")) {
                Logger.Warn("Titan TD DISCONNECTED");
                //_connector.TradeDisconnected();
            }
            else if (msg.StartsWith("CONNECTED")) {
                Logger.Info("Titan TD CONNECTED");
                //_connector.TradeConnected();
            }
        }

        public void Dispose() {
            _isStopped = true;
            DllHelper.Dismental();
        }
    }
}
