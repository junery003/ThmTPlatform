//-----------------------------------------------------------------------------
// File Name   : SytheticInstrumentHandler
// Author      : junlei
// Date        : 7/5/2021 10:52:15 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

using System;
using System.Collections.Generic;

namespace ThmCommon.Handlers {
    public class SytheticInstrumentHandler : InstrumentHandlerBase, IDisposable {
        private readonly List<InstrumentHandlerBase> _instrumentHandlers = new List<InstrumentHandlerBase>();
        protected override AlgoHandlerBase AlgoHandler { get => throw new NotImplementedException(); }
        protected override TradeHandlerBase TradeHandler { get => throw new NotImplementedException(); }

        public SytheticInstrumentHandler() {

        }

        public void AddHandler(InstrumentHandlerBase handler) {
            _instrumentHandlers.Add(handler);
        }

        public override bool Start() {
            throw new NotImplementedException();
        }

        public override void Stop() {
            throw new NotImplementedException();
        }

        public override int GetPosition() {
            return 0;
        }

        public override void Dispose() {
            _instrumentHandlers.ForEach(x => {
                x.Stop();
                x.Dispose();
            });
        }
    }
}
