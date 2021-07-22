//-----------------------------------------------------------------------------
// File Name   : DataController
// Author      : junlei
// Date        : 1/31/2020 12:13:04 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Configuration;
using System.Threading.Tasks;
using ThmCommon.Models;
using ThmCommon.Utilities;

namespace ThmCommon.Database {
    /// <summary>
    /// DataController
    /// </summary>
    public sealed class DataController {
        private readonly string _connstr;
        private readonly DbController _dbCtrl;

        public DataController() {
            _connstr = ConfigurationManager.ConnectionStrings["MySqlConn"].ConnectionString;
            _dbCtrl = new DbController();
        }

        public async Task<bool> InsertAsync(MarketDepthData depthData) {
            if (depthData == null) {
                return false;
            }

            var dbIdx = RouteRule.GetDbNameIndex(depthData.Exchange);
            var tblIdx = RouteRule.GetTableNameIndex(depthData.Product, depthData.LocalDateTime);

            /*
            string sql = "INSERT INTO `themett`.`tbl_marketdepth` " +
                "(`Source`,`Exchange`,`Product`,`ProductType`,`Contract`,`InstrumentId`,"
                + "`ExchangeDateTime`,`LocalDateTime`,"
                + "`BidPrice1`,`BidPrice2`,`BidPrice3`,`BidPrice4`,`BidPrice5`,`BidQty1`,`BidQty2`,`BidQty3`,`BidQty4`,`BidQty5`"
                + ",`AskPrice1`,`AskPrice2`,`AskPrice3`,`AskPrice4`,`AskPrice5`,`AskQty1`,`AskQty2`,`AskQty3`,`AskQty4`,`AskQty5`) "
                + "VALUES('"
                + depthData.Provider + "','" + depthData.Exchange + "','" + depthData.Product + "','" + depthData.ProductType + "','" + depthData.Contract + "','" + depthData.InstrumentId + "','"
                + TimeUtil.DateTime2Seconds(depthData.ExchangeDateTime) + "','" + TimeUtil.DateTime2Seconds(depthData.LocalDateTime) + "',"
                + depthData.BidPrice1 + "," + depthData.BidPrice2 + "," + depthData.BidPrice3 + "," + depthData.BidPrice4 + "," + depthData.BidPrice5 + ","
                + depthData.BidQuantity1 + "," + depthData.BidQuantity2 + "," + depthData.BidQuantity3 + "," + depthData.BidQuantity4 + "," + depthData.BidQuantity5 + ","
                + depthData.AskPrice1 + "," + depthData.AskPrice2 + "," + depthData.AskPrice3 + "," + depthData.AskPrice4 + "," + depthData.AskPrice5 + ","
                + depthData.AskQuantity1 + "," + depthData.AskQuantity2 + "," + depthData.AskQuantity3 + "," + depthData.AskQuantity4 + "," + depthData.AskQuantity5 + ")";
                */

            string sql = "INSERT INTO `themett" + dbIdx + "`.`tbl_marketdepth" + tblIdx + "`"
                + "(`Source`,`Exchange`,`Product`,`ProductType`,`Contract`,`InstrumentId`,`ExchangeDateTime`,`LocalDateTime`,"
                + "`BidPrice1`,`BidPrice2`,`BidQty1`,`BidQty2`,`AskPrice1`,`AskPrice2`,`AskQty1`,`AskQty2`) VALUES('"
                + depthData.Provider + "','" + depthData.Exchange + "','" + depthData.Product + "','" + depthData.ProductType + "','" + depthData.Contract + "','" + depthData.InstrumentID + "','"
                + TimeUtil.DateTime2MilliSecondsString(depthData.DateTime) + "','" + TimeUtil.DateTime2MilliSecondsString(depthData.LocalDateTime) + "',"
                + depthData.BidPrice1 + "," + depthData.BidPrice2 + ","
                + depthData.BidQty1 + "," + depthData.BidQty2 + ","
                + depthData.AskPrice1 + "," + depthData.AskPrice2 + ","
                + depthData.AskQty1 + "," + depthData.AskQty2 + ")";

            return await _dbCtrl.InsertAsync(GetConnStr(dbIdx), sql);
        }

        private string GetConnStr(string dbIdx) {
            return string.Format(_connstr, dbIdx);
        }

        public async Task<bool> InsertAsync(TimeSalesData tsObj) {
            if (tsObj == null) {
                return false;
            }

            var dbIdx = RouteRule.GetDbNameIndex(tsObj.Exchange);
            var tblIdx = RouteRule.GetTableNameIndex(tsObj.Product, tsObj.LocalTime);

            string sql = "INSERT INTO `themett" + dbIdx + "`.`tbl_timesales" + tblIdx + "` "
                + "(`Source`,`Exchange`,`Product`,`ProductType`,`Contract`,`InstrumentId`,`ExchangeDateTime`,`LocalDateTime`,"
                + "`Direction`, `Price`,`Qty`) VALUES ('"
                + tsObj.Provider + "','" + tsObj.Exchange + "','" + tsObj.Product + "','" + tsObj.ProductType + "','" + tsObj.Contract + "','" + tsObj.InstrumentId + "','"
                + TimeUtil.DateTime2MilliSecondsString(tsObj.ExchangeDateTime) + "','" + TimeUtil.DateTime2MilliSecondsString(tsObj.LocalTime) + "',"
                + (sbyte)tsObj.BuySell + "," + tsObj.Price + "," + tsObj.Qty + ")";

            return await _dbCtrl.InsertAsync(GetConnStr(dbIdx), sql);
        }
    }
}
