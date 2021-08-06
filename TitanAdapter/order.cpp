//-----------------------------------------------------------------------------
// File Name   : order.cpp
// Author      : junlei
// Date        : 11/26/2020 2:05:03 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "order.h"

#include "nlohmann/json.hpp"

std::string Order::UpdateOrderInfo() {
    return ""; // TBD

    nlohmann::json j;
    j["Symbol"] = symbol_;
    j["OrderID"] = id_.second;
    j["Side"] = id_.first;
    j["OrderToken"] = order_token_;
    j["DateTime"] = timestamp_;
    j["LocalTime"] = local_time_;
    j["Position"] = order_book_position_;
    j["Qty"] = open_qty_ + filled_qty_;
    j["FilledQty"] = filled_qty_;
    j["Price"] = price_;
    j["Status"] = status_;

    return j.dump();
}
