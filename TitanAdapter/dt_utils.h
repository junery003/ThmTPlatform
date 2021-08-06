//-----------------------------------------------------------------------------
// File Name   : dt_utils.h
// Author      : junlei
// Date        : 11/5/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __DT_UTILS_H__
#define __DT_UTILS_H__

#include <stdint.h>
#include <utility>

// Prices are signed integer fields. 
// Number of decimals is specified in the Order Book Directory message
typedef int32_t price_t;

//Four byte integer value derived from the Numeric data type. 
//The decoded value represents a Date in YYYYMMDD-format.
typedef uint32_t date_t; //

// 8 bytes: UNIX Time (number of nanoseconds since 1970-01-01 00:00:00 UTC)
typedef uint64_t timestamp_t;

enum class OrderSide : uint8_t {
    UNKNOWN = 0,
    BUY = 1,
    SELL = 2
};

enum class OrderStatus : uint8_t {
    Unknown = 0,
    New = 1,             // Pending; newly added
    Replaced = 3,
    Canceled = 4,        // Deleted(or Canceled")
    Rejected = 5,
    Filled = 8,          //"Filled"; // : All traded"
    PartiallyFilled = 9, //"PartiallyFilled"
};

enum class OrderType : uint8_t {
    Market,
    Limit,
    Stop,
    StopLimit,
};

// 
struct PairHash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        return std::hash<T1>{}(pair.first) ^ std::hash<T2>{}(pair.second);
    }
};

// order identifier: <side, order id>
typedef std::pair<char, uint64_t> order_id_t;

#endif //!__DT_UTILS_H__
