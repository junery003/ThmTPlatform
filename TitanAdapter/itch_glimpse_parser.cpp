//-----------------------------------------------------------------------------
// File Name   : itch_glimpse_parser.cpp
// Author      : junlei
// Date        : 11/5/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "itch_glimpse_parser.h"
#include "order_book_manager.h"
#include "logger.h"
#include "time_utils.hpp"

#include "nlohmann/json.hpp"
#include <WinSock2.h>

using namespace std;

bool ItchGlimpseParser::Start() {
    if (lower_layer_->Start()) {
        md_zmq_->Send("CONNECTED");
        return true;
    }

    return false;
}

void ItchGlimpseParser::Stop() {
    lower_layer_->Stop();
    //md_zmq_->Send("DISCONNECTED");
}

bool ItchGlimpseParser::Parse(const char* msg, const int msg_len) {
    char type = *msg;
    //Logger::Log()->info("[{}:{}] ITCH/Glimpse-msg type='{}'", __func__, __LINE__, type);
    switch (type) {
    case 'A':
        AddOrder(msg, msg_len);
        break;
    case 'C':
        OrderExecutedWPrice(msg, msg_len); // order executed with Price
        break;
    case 'D':
        OrderDelete(msg, msg_len);
        break;
    case 'E':
        OrderExecuted(msg, msg_len);
        break;
    case 'G': // glimpse only
        EndOfSnapshot(msg, msg_len);
        break;
    case 'L':
        TickSize(msg, msg_len);
        break;
    case 'M':
        CombinationOrderBookLeg(msg, msg_len);
        break;
    case 'O':
        OrderBookState(msg, msg_len);
        break;
    case 'P':
        TradeMessageIdentifier(msg, msg_len);
        break;
    case 'R':
        OrderBookDirectory(msg, msg_len);
        break;
    case 'S':
        SystemEvent(msg, msg_len);
        break;
    case 'T':
        Seconds(msg, msg_len);
        break;
    case 'U':
        OrderReplace(msg, msg_len);
        break;
    case 'Z':
        EquilibriumPriceUpdate(msg, msg_len);
        break;
    default: // not supported or error
        Logger::Log()->warn("[{}:{}] ITCH/Glimpse-not supported msg='{}', msg_len={}",
            __func__, __LINE__, type, msg_len);
        return false;
    }

    return true;
}

// A:
bool ItchGlimpseParser::AddOrder(const char* msg, const int msg_len) {
    OrderAddMsg* data = (OrderAddMsg*)msg;
    const static auto len = sizeof(*data);
    if (msg_len < len) {
        Logger::Log()->warn("[{}:{}] ITCH/Glimpse-msg:'{}', error len:{} ",
            __func__, __LINE__, data->type, msg_len);
        return false;
    }

    data->order_book_id = ntohl(data->order_book_id);
    auto order_book = OrderBookManager::Instance().GetOrderBook(data->order_book_id);
    if (order_book == nullptr) { // ignored
        return true;
    }
    //Logger::Log()->info("[{}:{}] ITCH/Glimpse A: OrderBookID:{}", __func__, __LINE__, data->order_book_id);

    order_book->AddOrder({ data->side, ntohll(data->order_id) },
        data->order_book_id,
        ntohl(data->order_book_position),
        ntohl(data->price),
        ntohll(data->qty),
        ntohs(data->oder_attributes),
        data->lot_type,
        cur_time_ + '.' + to_string(ntohl(data->timestamp_nanoseconds)));

    md_zmq_->Send(order_book->UpdateMarketData());

    return true;
}

// C: order executed with Price
bool ItchGlimpseParser::OrderExecutedWPrice(const char* msg, const int msg_len) {
    OrderExecutedWPriceMsg* data = (OrderExecutedWPriceMsg*)msg;
    const static auto len = sizeof(*data);
    if (msg_len < len) {
        Logger::Log()->warn("[{}:{}] ITCH/Glimpse-msg:'{}', error len:{} ",
            __func__, __LINE__, data->type, msg_len);
        return false;
    }

    data->order_book_id = ntohl(data->order_book_id);
    auto order_book = OrderBookManager::Instance().GetOrderBook(data->order_book_id);
    if (order_book == nullptr) { // ignored
        return true;
    }
    //Logger::Log()->info("[{}:{}] ITCH/Glimpse C: OrderBookID:{}", __func__, __LINE__, data->order_book_id);

    if (!data->printable) {  // ignore non-printable to prevent double counting
        Logger::Log()->warn("[{}:{}] OrderBookID:{} ignored non-printable", __func__,
            __LINE__, data->order_book_id);
        return true;
    }

    order_book->ExecuteOrder(order_id_t{ data->side, ntohll(data->order_id) },
        ntohl(data->trade_price),
        ntohll(data->executed_qty),
        OrderStatus::Filled,
        ntohll(data->match_id),
        ntohl(data->combo_group_id),
        cur_time_ + "." + to_string(ntohl(data->timestamp_nanoseconds)),
        true);

    md_zmq_->Send(order_book->UpdateMarketData());

    return true;
}

// D:
bool ItchGlimpseParser::OrderDelete(const char* msg, const int msg_len) {
    OrderDeleteMsg* data = (OrderDeleteMsg*)msg;
    const static auto len = sizeof(*data);
    if (msg_len < len) {
        Logger::Log()->warn("[{}:{}] ITCH/Glimpse-msg:'{}', error len:{} ",
            __func__, __LINE__, data->type, msg_len);
        return false;
    }

    data->order_book_id = ntohl(data->order_book_id);
    auto order_book = OrderBookManager::Instance().GetOrderBook(data->order_book_id);
    if (order_book == nullptr) { // ignored
        return true;
    }
    //Logger::Log()->info("[{}:{}] ITCH/Glimpse D: OrderBookID:{}", __func__, __LINE__, data->order_book_id);

    order_book->DeleteOrder({ data->side, ntohll(data->order_id) },
        cur_time_ + "." + to_string(ntohl(data->timestamp_nanoseconds)));

    md_zmq_->Send(order_book->UpdateMarketData());
    return true;
}

// E: order executed in whole or in part
bool ItchGlimpseParser::OrderExecuted(const char* msg, const int msg_len) {
    OrderExecutedMsg* data = (OrderExecutedMsg*)msg;
    const static auto len = sizeof(*data);
    if (msg_len < len) {
        Logger::Log()->warn("[{}:{}] ITCH/Glimpse-msg:'{}', error len:{} ",
            __func__, __LINE__, data->type, msg_len);
        return false;
    }

    data->order_book_id = ntohl(data->order_book_id);
    auto order_book = OrderBookManager::Instance().GetOrderBook(data->order_book_id);
    if (order_book == nullptr) { // ignored
        return true;
    }
    //Logger::Log()->info("[{}:{}] ITCH/Glimpse E: OrderBookID:{}", __func__, __LINE__, data->order_book_id);

    order_book->ExecuteOrder(order_id_t{ data->side, ntohll(data->order_id) },
        0, ntohll(data->executed_qty),
        OrderStatus::Filled,
        ntohll(data->match_id),
        ntohl(data->combo_group_id),
        cur_time_ + "." + to_string(ntohl(data->timestamp_nanoseconds)),
        false);

    md_zmq_->Send(order_book->UpdateMarketData());
    return true;
}

// L
bool ItchGlimpseParser::TickSize(const char* msg, const int msg_len) {
    TickSizeMsg* data = (TickSizeMsg*)msg;
    const static auto len = sizeof(*data);
    if (msg_len < len) {
        Logger::Log()->warn("[{}:{}] ITCH/Glimpse-msg:'{}', error len:{} ",
            __func__, __LINE__, data->type, msg_len);
        return false;
    }

    data->order_book_id = ntohl(data->order_book_id);
    auto order_book = OrderBookManager::Instance().GetOrderBook(data->order_book_id);
    if (order_book == nullptr) { // ignored
        return true;
    }
    //Logger::Log()->info("[{}:{}] ITCH/Glimpse L: OrderBookID:{}", __func__, __LINE__, data->order_book_id);

    order_book->SetTickSize(ntohll(data->tick_size),
        ntohl(data->price_from),
        ntohl(data->price_to),
        cur_time_ + "." + to_string(ntohl(data->timestamp_nanoseconds)));

    md_zmq_->Send(order_book->UpdateInstrumentInfo());
    return true;
}

// M: synthetic instruments
bool ItchGlimpseParser::CombinationOrderBookLeg(const char* msg, const int msg_len) {
    CombinationOrderBookLegMsg* data = (CombinationOrderBookLegMsg*)msg;
    const static auto len = sizeof(*data);
    if (msg_len < len) {
        Logger::Log()->warn("[{}:{}] ITCH/Glimpse-msg:'{}', error len:{} ",
            __func__, __LINE__, data->type, msg_len);
        return false;
    }

    data->leg_order_book_id = ntohl(data->leg_order_book_id);
    auto leg_order_book = OrderBookManager::Instance().GetOrderBook(data->leg_order_book_id);
    if (leg_order_book == nullptr) { // ignored
        return true;
    }
    Logger::Log()->info("[{}:{}] ITCH/Glimpse M: Combination order leg OrderBookID:{}, side:{}",
        __func__, __LINE__, data->leg_order_book_id, data->leg_side);

    // synthetic instrument
    OrderBookManager::Instance().UpdateCombinationOrderBook(ntohl(data->combination_order_book_id),
        ntohl(data->leg_order_book_id),
        data->leg_side,
        ntohl(data->leg_ratio),
        cur_time_ + "." + to_string(ntohl(data->timestamp_nanoseconds)));

    return true;
}

// O:
bool ItchGlimpseParser::OrderBookState(const char* msg, const int msg_len) {
    OrderBookStateMsg* data = (OrderBookStateMsg*)msg;
    const static auto len = sizeof(*data);
    if (msg_len < len) {
        Logger::Log()->warn("[{}:{}] ITCH/Glimpse-msg:'{}', error len:{} ",
            __func__, __LINE__, data->type, msg_len);
        return false;
    }

    data->order_book_id = ntohl(data->order_book_id);
    auto order_book = OrderBookManager::Instance().GetOrderBook(data->order_book_id);
    if (order_book == nullptr) { // ignored
        return true;
    }
    //Logger::Log()->info("[{}:{}] ITCH/Glimpse O: OrderBookID:{}", __func__, __LINE__, data->order_book_id);

    order_book->SetState(ParseFieldRightPadding(data->state_name, sizeof(data->state_name)),
        cur_time_ + "." + to_string(ntohl(data->timestamp_nanoseconds)));

    return true;
}

// P:
bool ItchGlimpseParser::TradeMessageIdentifier(const char* msg, const int msg_len) {
    return true;
    TradeMsg* data = (TradeMsg*)msg;
    const static auto len = sizeof(*data);
    if (msg_len < len) {
        Logger::Log()->warn("[{}:{}] ITCH/Glimpse-msg:'{}', error len:{} ",
            __func__, __LINE__, data->type, msg_len);
        return false;
    }

    data->order_book_id = ntohl(data->order_book_id);
    auto order_book = OrderBookManager::Instance().GetOrderBook(data->order_book_id);
    if (order_book == nullptr) { // ignored
        return true;
    }
    //Logger::Log()->info("[{}:{}] ITCH/Glimpse P: OrderBookID:{}", __func__, __LINE__, data->order_book_id);

    data->match_id = ntohll(data->match_id);
    data->combo_group_id = ntohl(data->combo_group_id);

    data->trade_price = ntohl(data->trade_price);

    auto order = order_book->GetOrder(order_id_t{ data->side, data->match_id });

    data->qty = ntohll(data->qty);
    string timestamp{ cur_time_ + '.' + to_string(ntohl(data->timestamp_nanoseconds)) };

    Logger::Log()->info("[{}:{}] ITCH/Glimpse P: order book id:{}, match id:{:x}, combo group id:{:x}, "
        "side:{}, trade price:{}, qty:{}, time:{}",
        __func__, __LINE__, data->order_book_id, data->match_id, data->combo_group_id,
        data->side, data->trade_price, data->qty, timestamp);

    //order->AddExecuted() // data->trade_price;
    //md_zmq_->Send(order->UpdateOrderInfo());

    return true;
}

// R:
bool ItchGlimpseParser::OrderBookDirectory(const char* msg, const int msg_len) {
    OrderBookDirectoryMsg* data = (OrderBookDirectoryMsg*)msg;
    const static auto len = sizeof(*data);
    if (msg_len < len) {
        Logger::Log()->warn("[{}:{}] ITCH/Glimpse-msg:'{}', error len:{} ",
            __func__, __LINE__, data->type, msg_len);
        return false;
    }

    data->order_book_id = ntohl(data->order_book_id);
    string symbol{ ParseFieldRightPadding(data->symbol, sizeof(data->symbol)) };
    //Logger::Log()->info("symbol: {} - orderBookID: {}", symbol, data->order_book_id);
    if (!OrderBookManager::Instance().InitSubsription(symbol, data->order_book_id)) { // ignored
        return true;
    }

    //Logger::Log()->info("[{}:{}] ITCH/Glimpse R: OrderBookID:{}", __func__, __LINE__, data->order_book_id);
    auto order_book = OrderBookManager::Instance().GetOrderBook(data->order_book_id);

    order_book->Init(symbol,
        ParseFieldRightPadding(data->long_name, sizeof(data->long_name)),
        ParseFieldRightPadding(data->ISIN, sizeof(data->ISIN)),
        data->ParseFinancialProduct(),
        ParseFieldRightPadding(data->currency, sizeof(data->currency)),
        ntohl(data->odd_lot_size),
        ntohl(data->round_lot_size),
        ntohl(data->block_lot_size),
        ntohl(data->expiration_date),
        ntohs(data->decimal_num_in_price),
        ntohll(data->nominal_value),
        ntohs(data->decimal_num_in_nominal_value),
        ntohs(data->decimal_num_in_strike_price),
        data->leg_num,
        ntohl(data->commodity_code),
        ntohl(data->strike_price),
        data->ParsePutOrCall(),
        cur_time_ + "." + to_string(ntohl(data->timestamp_nanoseconds))
    );

    return true;
}

// S:
bool ItchGlimpseParser::SystemEvent(const char* msg, const int msg_len) {
    SystemEventMsg* data = (SystemEventMsg*)msg;
    const static auto len = sizeof(*data);
    if (msg_len < len) {
        Logger::Log()->warn("[{}:{}] ITCH/Glimpse-msg:'{}', error len:{} ",
            __func__, __LINE__, data->type, msg_len);
        return false;
    }

    //data->timestamp_nanoseconds = ntohl(data->timestamp_nanoseconds);
    switch (data->event_code) {
    case 'O': // start of the msg
        Logger::Log()->info("[{}:{}] ITCH/Glimpse S: Start of the msg", __func__, __LINE__);
        break;
    case 'C': // end of the msg
        Logger::Log()->info("[{}:{}] ITCH/Glimpse S: End of the msg", __func__, __LINE__);
        break;
    default: // not supported
        Logger::Log()->error("ITCH/Glimpse S: system event not defined: {}", data->event_code);
        break;
    }

    return true;
}

// T:
bool ItchGlimpseParser::Seconds(const char* msg, const int msg_len) {
    SecondMsg* data = (SecondMsg*)msg;
    const static auto len = sizeof(*data);
    if (msg_len < len) {
        Logger::Log()->warn("[{}:{}] ITCH/Glimpse-msg:'{}', error len:{} ",
            __func__, __LINE__, data->type, msg_len);
        return false;
    }

    cur_time_ = TimeUtils::FromUnixTime(ntohl(data->second));
    //Logger::Log()->info("T: Second: {}", cur_time_);
    return true;
}

// U: There will be no Order Replace Message seen in ITCH Feed.
bool ItchGlimpseParser::OrderReplace(const char* msg, const int msg_len) {
    return true;
    OrderReplaceMsg* data = (OrderReplaceMsg*)msg;
    const static auto len = sizeof(*data);
    if (msg_len < len) {
        Logger::Log()->warn("[{}:{}] ITCH/Glimpse-msg:'{}', error len:{} ",
            __func__, __LINE__, data->type, msg_len);
        return false;
    }

    data->order_book_id = ntohl(data->order_book_id);
    auto order_book = OrderBookManager::Instance().GetOrderBook(data->order_book_id);
    if (order_book == nullptr) { // ignored
        return true;
    }
    //Logger::Log()->info("[{}:{}] ITCH/Glimpse U: OrderBookID:{}", __func__, __LINE__, data->order_book_id);

    data->timestamp_nanoseconds = ntohl(data->timestamp_nanoseconds);

    data->order_id = ntohll(data->order_id);

    data->new_order_book_position = ntohl(data->new_order_book_position);

    data->qty = ntohll(data->qty);
    data->price = ntohl(data->price);

    data->other_attributes[0] = ntohs(data->other_attributes[0]);
    data->other_attributes[1] = ntohs(data->other_attributes[1]);

    md_zmq_->Send(order_book->UpdateMarketData());
    return true;
}

//Z:  Auction messages
bool ItchGlimpseParser::EquilibriumPriceUpdate(const char* msg, const int msg_len) {
    EquilibriumPriceUpdateMsg* data = (EquilibriumPriceUpdateMsg*)msg;
    const static auto len = sizeof(*data);
    if (msg_len < len) {
        Logger::Log()->warn("[{}:{}] ITCH/Glimpse-msg:'{}', error len:{} ",
            __func__, __LINE__, data->type, msg_len);
        return false;
    }

    data->order_book_id = ntohl(data->order_book_id);
    auto order_book = OrderBookManager::Instance().GetOrderBook(data->order_book_id);
    if (order_book == nullptr) { // ignored
        return true;
    }
    Logger::Log()->info("[{}:{}] ITCH/Glimpse Z: OrderBookID:{}", __func__, __LINE__, data->order_book_id);

    md_zmq_->Send(order_book->UpdateEquilibriumPrice(ntohll(data->available_bid_qty),
        ntohll(data->available_ask_qty),
        ntohl(data->best_bid_price),
        ntohl(data->best_ask_price),
        ntohll(data->best_bid_qty),
        ntohll(data->best_ask_qty),
        ntohl(data->equilibrium_price),
        cur_time_ + "." + to_string(ntohl(data->timestamp_nanoseconds)))
    );

    return true;
}

// ------------------------------------------------------------------------------------------------;
// Glimpse only
// G:
bool ItchGlimpseParser::EndOfSnapshot(const char* msg, const int msg_len) {
    EndOfSnapshotMsg* data = (EndOfSnapshotMsg*)msg;
    const static auto len = sizeof(*data);
    if (msg_len < len) {
        Logger::Log()->warn("[{}:{}] ITCH/Glimpse-msg:'{}', error len:{} ",
            __func__, __LINE__, data->type, msg_len);
        return false;
    }

    sequence_num_ = std::stoull(ParseFieldRightPadding(data->sequence_number, sizeof(data->sequence_number)));
    Logger::Log()->info("[{}:{}] Glimpse G: seqNum:{}", __func__, __LINE__, sequence_num_);

    lower_layer_->SetConnection(false);  // end of the session

    return true;
}
