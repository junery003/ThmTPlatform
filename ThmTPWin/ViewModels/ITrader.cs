//-----------------------------------------------------------------------------
// File Name   : ITrader
// Author      : junlei
// Date        : 9/21/2021 9:01:45 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

using System;
using ThmCommon.Handlers;
using ThmCommon.Models;

namespace ThmTPWin.ViewModels {
    public interface ITrader : IDisposable {
        InstrumentHandlerBase InstrumentHandler { get; }

        bool CheckQty(EBuySell dir);
        void SetPosition(int position);

        //void UpdateAlgoType(EAlgoType algoType);

        void DeleteOrder(string orderID, bool isBuy);

        void ProcessAlgo(EBuySell dir, decimal price);
        void IncreaseAlgo(decimal price);
        void DecreaseAlgo(decimal price);

        void DeleteAlgo(string algoID);
        void DeleteAlgosByPrice(decimal price);
        void DeleteAllAlgos();
    }
}
