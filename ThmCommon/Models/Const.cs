//-----------------------------------------------------------------------------
// File Name   : Const info for order/algo/trade
// Author      : junlei
// Date        : 10/26/2020 2:53:33 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

namespace ThmCommon.Models {
    public enum EBuySell {
        Unknown = 0,
        Buy = 1,  // Take from TT
        Sell = 2  // Hit from TT
    }

    public enum EOrderStatus {
        Unknown = 0,
        New = 1,
        Pending = 2,
        Replaced = 5,
        Filled = 7,
        PartiallyFilled = 8,
        Accepted = 10,
        Canceled = 12,
        Rejected = 14,
        Failed = 16,
        Expired = 18,
        Inactive = 19,
        AlgoFired = 20,
    };

    public enum EAlgoType {
        Limit = 0,
        Market = 1,
        Trigger = 3,
        Sniper = 5,
        PreOpen = 7,
        //TTStop = 3,
        InterTrigger = 10,
    }

    public enum EOperator {
        LessET = 1,    // <=
        GreaterET = 2, // >=
    }

    public enum EPriceType {
        SameSide = 2,
        OppositeSide = 3,
        //LTP = 1,  // not supported yet
        Bid = 5,
        Ask = 6,
    }

    /*
    public enum OrdStatus {
        NotSet = 0,
        New = 1,
        PartiallyFilled = 2,
        Filled = 3,
        DoneForDay = 4,
        Canceled = 5,
        Cancel = 6,
        Stopped = 7,
        Rejected = 8,
        Suspended = 9,
        PendingNew = 10,
        Calculated = 11,
        Expired = 12,
        AcceptedForBidding = 13,
        PendingReplace = 14,
        Unknown = 16,
        Inactive = 17,
        Planned = 18
    }

    public enum OrderType {
        NotSet = 0,
        Market = 1,
        Limit = 2,
        Stop = 3,
        StopLimit = 4,
        MarketWithLeftOverAsLimit = 20,
        MarketLimitMarketLeftOverAsLimit = 21,
        StopMarketToLimit = 30,
        IfTouchedMarket = 31,
        IfTouchedLimit = 32,
        IfTouchedMarketToLimit = 33,
        LimitPostOnly = 37,
        MarketCloseToday = 38,
        LimitCloseToday = 39,
        LimitReduceOnly = 40,
        MarketReduceOnly = 41,
        Unknown = 100
    }
    */
}
