//-----------------------------------------------------------------------------
// File Name   : DataProcessor
// Author      : junlei
// Date        : 1/24/2020 3:5:34 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Threading.Tasks;
using ThmCommon.Database;
using ThmCommon.Models;

namespace ThmCommon.Handlers {
    /// <summary>
    /// DataProcessor
    /// </summary>
    public class DataProcessor : IDataHandler {
        private readonly DataController _dataController = new DataController();
        //private readonly RedisHelper _redisHandler = new RedisHelper();

        /// <summary>
        /// notify all users the updated info
        /// </summary>
        /// <param name="depthObj"></param>
        public void RedisNotify(MarketDepthData depthObj) {
            //_redisHandler.Publish(depthObj.ContractDetail, JsonConvert.SerializeObject(depthObj));
        }

        /// <summary>
        /// save market depth data to DB
        /// </summary>
        /// <param name="depthObj"></param>
        public async Task<bool> SaveDataAsync(MarketDepthData depthObj) {
            return await _dataController.InsertAsync(depthObj);
        }

        /// <summary>
        /// save time sales data to DB
        /// </summary>
        /// <param name="tsObj"></param>
        public async Task<bool> SaveDataAsync(TimeSalesData tsObj) {
            return await _dataController.InsertAsync(tsObj);
        }

        /// <summary>
        /// notify all users the updated info
        /// </summary>
        /// <param name="orderObj"></param>
        public void Notify(OrderData orderObj) {
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="tdObj"></param>
        public void Notify(TimeSalesData tdObj) {
            //_redisHandler.Publish(tdObj.ContractDetail, JsonConvert.SerializeObject(tdObj));
        }
    }
}
