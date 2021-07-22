//-----------------------------------------------------------------------------
// File Name   : ITrader
// Author      : junlei
// Date        : 10/14/2020 5:20:31 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using ThmCommon.Handlers;
using ThmCommon.Models;

namespace ThmTPWin.Controllers {
    internal interface ITrader {
        InstrumentHandlerBase GetInstrumentHandler();
        bool CheckQty(EBuySell dir);
        void SetPosition(int position);

        void DeleteOrder(string orderID, bool isBuy);
        void DispalyAlgoView(EAlgoType selectedAlgoType);

        void DeleteAlgo(string algoID);
        void DeleteAlgosByPrice(decimal price);
        void DeleteAllAlgos();

        void ProcessAlgo(EBuySell dir, decimal price);
        void IncreaseAlgo(decimal price);
        void DecreaseAlgo(decimal price);
    }
}
