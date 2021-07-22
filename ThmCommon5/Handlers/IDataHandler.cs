//-----------------------------------------------------------------------------
// File Name   : IDataHandler
// Author      : junlei
// Date        : 5/7/2020 1:31:28 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Threading.Tasks;
using ThmCommon.Models;

namespace ThmCommon.Handlers {
    public interface IDataHandler {
        Task<bool> SaveDataAsync(MarketDepthData depthObj);
        Task<bool> SaveDataAsync(TimeSalesData tsObj);

        void RedisNotify(MarketDepthData depthObj);
        void Notify(OrderData orderObj);
        void Notify(TimeSalesData tdObj);
    }
}
