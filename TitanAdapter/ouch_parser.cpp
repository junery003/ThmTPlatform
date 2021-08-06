//-----------------------------------------------------------------------------
// File Name   : ouch_parser.cpp
// Author      : junlei
// Date        : 11/5/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "ouch_parser.h"
#include "order_book_manager.h"
#include "logger.h"
#include "time_utils.hpp"

#include "nlohmann/json.hpp"
//#include <WinSock2.h>
#include <string>

using namespace std;

bool OuchParser::Start() {
    return lower_layer_->Start();
}

// ------------------------------------------------------------------------------------------------;
// outbound messages: server -->> client
// ------------------------------------------------------------------------------------------------;
bool OuchParser::Parse(const char* msg, const int msg_len) {
    char type = *((char*)msg);
    //Logger::Log()->info("[{}:{}] OUCH-msg type='{}'", __func__, __LINE__, type);
    switch (type) {
    case 'A':
        OrderAccepted(msg);
        break;
    case 'C':
        OrderCanceled(msg);
        break;
    case 'E':
        OrderExecuted(msg);
        break;
    case 'J':
        OrderRejected(msg);
        break;
    case 'U':
        OrderReplaced(msg);
        break;
    default:
        Logger::Log()->error("[{}:{}] OUCH-msg type='{}' not supported", __func__, __LINE__, type);
        return false;
    }

    return true;
}

// outbound messages
void OuchParser::OrderAccepted(const char* msg) {
    OrderAcceptedMsg* data = (OrderAcceptedMsg*)msg;

    data->order_book_id = ntohl(data->order_book_id);
    auto ord_book = OrderBookManager::Instance().GetOrderBook(data->order_book_id);
    if (ord_book == nullptr) {
        Logger::Log()->error("[{}:{}] order book not found: {}", __func__, __LINE__, data->order_book_id);
        return;
    }

    nlohmann::json j;
    j["Status"] = ParseOrderState(data->order_state);

    j["Symbol"] = ord_book->GetSymbol();

    string ord_token{ ParseFieldRightPadding(data->order_token, sizeof(data->order_token)) };
    j["OrderToken"] = ord_token;
    j["OrderBookID"] = data->order_book_id;
    OrderBookManager::Instance().SetOrderToken2ID(ord_token, data->order_book_id);

    j["Side"] = GetSide(data->side);
    j["OrderID"] = ntohll(data->order_id);

    j["Qty"] = ntohll(data->qty);

    data->price = ntohl(data->price);
    j["Price"] = ord_book->ParsePrice(data->price);  // 

    j["TIF"] = data->time_in_force;
    j["OpenClose"] = data->open_close;
    j["Account"] = ParseFieldRightPadding(data->client_account, sizeof(data->client_account));
    j["State"] = data->order_state;

    j["CustomerInfo"] = ParseFieldRightPadding(data->customer_info, sizeof(data->customer_info));
    j["ExchangeInfo"] = ParseFieldRightPadding(data->exchange_info, sizeof(data->exchange_info));
    j["PreTradeQty"] = ntohll(data->pretrade_qty);
    j["DisplayQty"] = ntohll(data->display_qty);
    j["StpKey"] = ntohs(data->stp_key);
    j["OrderType"] = ParseOrderType(data->ouch_order_type);

    j["DateTime"] = TimeUtils::FromNanoSecond(ntohll(data->timestamp_nanoseconds));

    td_zmq_->Send(j.dump());

    Logger::Log()->info("[{}:{}] OUCH-msg A: {}", __func__, __LINE__, j.dump());
}

void OuchParser::OrderRejected(const char* msg) {
    OrderRejectedMsg* data = (OrderRejectedMsg*)msg;

    nlohmann::json j;
    j["Status"] = "Rejected";
    j["DateTime"] = TimeUtils::FromNanoSecond(ntohll(data->timestamp_nanoseconds));

    string ord_token{ ParseFieldRightPadding(data->order_token, sizeof(data->order_token)) };
    j["OrderToken"] = ord_token;

    data->reject_code = ntohl(data->reject_code);
    j["RejectCode"] = data->reject_code;

    auto ord_book = OrderBookManager::Instance().GetOrderBook(ord_token);
    if (ord_book != nullptr) {
        j["Symbol"] = ord_book->GetSymbol();
    }
    else {
        Logger::Log()->error("[{}:{}] OUCH-msg J: order not found: Order token:'{}', Rejected code:{}",
            __func__, __LINE__, ord_token, data->reject_code);
        return;
    }

    td_zmq_->Send(j.dump());

    Logger::Log()->warn("[{}:{}] OUCH-msg J: {}", __func__, __LINE__, j.dump());
}

// U
void OuchParser::OrderReplaced(const char* msg) {
    OrderReplacedMsg* data = (OrderReplacedMsg*)msg;

    data->order_book_id = ntohl(data->order_book_id);
    auto ord_book = OrderBookManager::Instance().GetOrderBook(data->order_book_id);
    if (ord_book == nullptr) {
        Logger::Log()->error("[{}:{}] OUCH-msg U: order book not found: {}", __func__, __LINE__, data->order_book_id);
        return;
    }

    nlohmann::json j;
    if (data->order_state == 2) {  // TODO
        j["Status"] = "Canceled";
    }
    else {
        j["Status"] = "Replaced";
    }

    j["OrderBookID"] = data->order_book_id;
    j["Symbol"] = ord_book->GetSymbol();
    j["DateTime"] = TimeUtils::FromNanoSecond(ntohll(data->timestamp_nanoseconds));

    // current new order token
    j["ReplacementOrderToken"] = ParseFieldRightPadding(data->replacement_order_token, sizeof(data->replacement_order_token));

    j["OrderToken"] = ParseFieldRightPadding(data->previous_order_token, sizeof(data->previous_order_token));

    j["Side"] = GetSide(data->side);
    j["OrderID"] = ntohll(data->order_id);

    j["Qty"] = ntohll(data->qty);

    data->price = ntohl(data->price);
    j["Price"] = ord_book->ParsePrice(data->price); //

    j["TIF"] = data->time_in_force;
    j["OpenClose"] = data->open_close;

    j["Account"] = ParseFieldRightPadding(data->client_account, sizeof(data->client_account));

    j["CustomerInfo"] = ParseFieldRightPadding(data->customer_info, sizeof(data->customer_info));
    j["ExchangeInfo"] = ParseFieldRightPadding(data->exchange_info, sizeof(data->exchange_info));

    j["PretradeQty"] = ntohll(data->pretrade_qty);
    j["DisplayQty"] = ntohll(data->display_qty);
    j["StpKey"] = ntohs(data->stp_key);

    j["OrderState"] = data->order_state;

    td_zmq_->Send(j.dump());

    Logger::Log()->info("[{}:{}] OUCH-msg U: {}", __func__, __LINE__, j.dump());
}

void OuchParser::OrderCanceled(const char* msg) {
    OrderCanceledMsg* data = (OrderCanceledMsg*)msg;
    data->order_book_id = ntohl(data->order_book_id);
    auto ord_book = OrderBookManager::Instance().GetOrderBook(data->order_book_id);
    if (ord_book == nullptr) {
        Logger::Log()->error("[{}:{}] order book not found: {}", __func__, __LINE__, data->order_book_id);
        return;
    }

    nlohmann::json j;
    j["DateTime"] = TimeUtils::FromNanoSecond(ntohll(data->timestamp_nanoseconds));
    j["Status"] = "Canceled";

    j["OrderToken"] = ParseFieldRightPadding(data->order_token, sizeof(data->order_token));
    j["OrderBookID"] = data->order_book_id;

    j["Symbol"] = ord_book->GetSymbol();

    j["Side"] = GetSide(data->side);
    j["OrderID"] = ntohll(data->order_id);

    j["Text"] = OrderCanceledMsg::FormatReason(data->reason);

    td_zmq_->Send(j.dump());

    Logger::Log()->info("[{}:{}] OUCH-msg C: {}", __func__, __LINE__, j.dump());
}

void OuchParser::OrderExecuted(const char* msg) {
    OrderExecutedMsg* data = (OrderExecutedMsg*)msg;
    data->order_book_id = ntohl(data->order_book_id);

    auto ord_book = OrderBookManager::Instance().GetOrderBook(data->order_book_id);
    if (ord_book == nullptr) {
        Logger::Log()->error("[{}:{}] order book not found: {}", __func__, __LINE__, data->order_book_id);
        return;
    }

    nlohmann::json j;
    j["Status"] = "Filled";
    j["Symbol"] = ord_book->GetSymbol();

    j["OrderToken"] = ParseFieldRightPadding(data->order_token, sizeof(data->order_token));
    j["OrderBookID"] = data->order_book_id;

    j["TradedQty"] = ntohll(data->traded_qty);

    data->trade_price = ntohl(data->trade_price);
    j["Price"] = ord_book->ParsePrice(data->trade_price); // 

    //j["MatchID"] = std::format("{:x}{:x}", data->match_id.execution_number, data->match_id.match_group_number);

    j["DateTime"] = TimeUtils::FromNanoSecond(ntohll(data->timestamp_nanoseconds));

    td_zmq_->Send(j.dump());

    Logger::Log()->info("[{}:{}] OUCH-msg E: {}", __func__, __LINE__, j.dump());
}
