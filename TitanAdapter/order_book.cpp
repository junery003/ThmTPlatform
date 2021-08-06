//-----------------------------------------------------------------------------
// File Name   : order_book.cpp
// Author      : junlei
// Date        : 11/5/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "order_book.h"
#include "time_utils.hpp"
#include "logger.h"

#include "nlohmann/json.hpp"
#include <algorithm>

using namespace std;

void OrderBook::Init(const std::string& symbol,
    const std::string& long_name,
    const std::string& isin,
    const std::string& financial_product,
    const std::string& currency,
    const uint32_t odd_lot_size,
    const uint32_t round_lot_size,
    const uint32_t block_lot_size,
    const date_t expiration_date,
    const uint16_t decimal_num_in_price,
    const uint64_t nominal_value,
    const uint16_t decimal_num_in_nominal_value,
    const uint16_t decimal_num_in_strike_price,
    uint8_t number_of_legs,
    const uint32_t commodity_code,
    const price_t strike_price,
    const std::string& put_or_call,
    const std::string& timestamp) {
    symbol_ = symbol;
    long_name_ = long_name;
    isin_ = isin;
    financial_product_ = financial_product;
    currency_ = currency;
    commodity_code_ = commodity_code;
    odd_lot_size_ = odd_lot_size;
    round_lot_size_ = round_lot_size;
    block_lot_size_ = block_lot_size;
    expiration_date_ = expiration_date;

    decimal_num_in_price_ = decimal_num_in_price;
    nominal_value_ = nominal_value;
    //number_of_legs_ = number_of_legs,
    decimal_num_in_nominal_value_ = decimal_num_in_nominal_value;
    decimal_num_in_strike_price_ = decimal_num_in_strike_price;
    strike_price_ = strike_price;

    timestamp_ = timestamp;

    Logger::Log()->info("[{}:{}] Order book dictionary: order book id:{}, symbol:{}, long name:{}, isin:{}, "
        "financial product:{}, currency:{}, price decimal number:{}, nominal decimal number:{}, "
        "odd lot size:{}, round lot size:{}, block lot size:{}, nominal value:{}, number of legs:{}, "
        "commodity code:{}, strike price:{}, expiration date={}, strike price decimal number:{}, "
        "put or call:{}, time:{}",
        __func__, __LINE__, order_book_id_, symbol, long_name, isin,
        financial_product, currency, decimal_num_in_price, decimal_num_in_nominal_value,
        odd_lot_size, round_lot_size, block_lot_size, nominal_value, number_of_legs,
        commodity_code, strike_price, expiration_date, decimal_num_in_strike_price,
        put_or_call, timestamp);
}

void OrderBook::SetTickSize(uint64_t tick_size, price_t from, price_t to,
    const std::string& timestamp) {
    tick_size_ = tick_size;
    price_from_ = from;
    price_to_ = to;
    timestamp_ = timestamp;

    Logger::Log()->info("[{}:{}] Tick Size:{}, from:{}, to:{}, time:{}",
        __func__, __LINE__, tick_size, from, to, timestamp);
}

void OrderBook::SetState(const std::string& state, const std::string& timestamp) {
    state_ = state;
    timestamp_ = timestamp;

    Logger::Log()->info("[{}:{}] State: order book id:{}, state:{}, time:{}",
        __func__, __LINE__, order_book_id_, state, timestamp);
    //if (state == "TRANSITION" || state == "REMOVE_DAY_ORDERS") {
    //    Purge();
    //}
}

// new order 
bool OrderBook::AddOrder(const order_id_t& id,
    uint32_t order_book_id,
    uint32_t order_book_position,
    price_t price, uint64_t qty,
    uint16_t other_attributes,
    uint8_t lot_type,
    const string& timestamp) {
    Logger::Log()->info("[{}:{}] Add order: order id {}-{}, order book id:{}, order book position:{}, "
        "price:{}, qty:{}, other attributes:{}, lot type:{}, time:{}",
        __func__, __LINE__, id.first, id.second, order_book_id, order_book_position,
        price, qty, other_attributes, lot_type, timestamp);

    if (all_orders_.contains(id)) { // should not happen?
        Logger::Log()->error("[{}:{}] Orderbook-Order already exists: {}-{}", __func__, __LINE__,
            id.first, id.second);
        return false;
    }

    auto order = make_shared<Order>(id,
        order_book_id, symbol_,
        order_book_position,
        price, qty,
        other_attributes,
        lot_type,
        timestamp);
    all_orders_[id] = order;

    if (id.first == 'B') {
        bid_orders_[price].emplace_back(order);
        return true;
    }
    if (id.first == 'S') {
        ask_orders_[price].emplace_back(order);
        return true;
    }

    Logger::Log()->error("[{}:{}] should not happen: order id {}-{} ",
        __func__, __LINE__, id.first, id.second);
    return false;
}

// eg. order executed: filled or partial filled
void OrderBook::ExecuteOrder(const order_id_t& id,
    price_t trade_price, // used when is_price_valid is true
    uint64_t executed_qty,
    const OrderStatus status,
    uint64_t match_id,
    uint32_t combo_grp_id,
    const string& timestamp,
    bool is_price_valid) {
    auto it = all_orders_.find(id);
    if (it == all_orders_.end()) {
        Logger::Log()->error("[{}:{}] Orderbook-order doest not exist: {}-{}", __func__, __LINE__,
            id.first, id.second);
        return;
    }

    // update ori price
    if (is_price_valid) {
        ChangeOrderPrice(id, it->second->GetPrice(), trade_price);
    }

    Logger::Log()->info("[{}:{}] Order Executed: order book id:{}, order id {}-{}, "
        "trade price:{}, executed qty:{}, match id:{:x}, combo grp id:{:x}, "
        "time:{}, price valid:{}",
        __func__, __LINE__, order_book_id_, id.first, id.second,
        trade_price, executed_qty, match_id, combo_grp_id,
        timestamp, is_price_valid);

    it->second->AddExecuted(executed_qty, timestamp);
    if (it->second->GetQty() == 0) {
        Logger::Log()->warn("[{}:{}] Order fullfilled: {}-{} qty=0", __func__, __LINE__, id.first, id.second);
        DeleteOrder(id, TimeUtils::GetNow());
    }
}

void OrderBook::ChangeOrderPrice(const order_id_t& id, price_t old_price, price_t new_price) {
    Logger::Log()->info("[{}:{}] Order {}-{}, price changed from {} to {}",
        __func__, __LINE__, id.first, id.second, old_price, new_price);

    if (old_price == new_price) {
        return;
    }

    if (id.first == 'B') {
        auto& orders = bid_orders_[old_price];
        for (auto it = orders.begin(); it != orders.end(); ++it) {
            if ((*it)->GetID() == id) {
                shared_ptr<Order> order{ *it };
                orders.erase(it);

                order->UpdatePrice(new_price); // new price
                bid_orders_[new_price].emplace_back(order);

                Logger::Log()->info("[{}:{}] Order {}-{}, price change done", __func__, __LINE__, id.first, id.second);
                return;
            }
        }

        Logger::Log()->error("[{}:{}] Order {}-{} price not found:{}", __func__, __LINE__, id.first, id.second, old_price);
        return;
    }

    if (id.first == 'S') {
        auto& orders = ask_orders_[old_price];
        for (auto it = orders.begin(); it != orders.end(); ++it) {
            if ((*it)->GetID() == id) {
                shared_ptr<Order> order{ *it };
                orders.erase(it);

                order->UpdatePrice(new_price); // new price
                ask_orders_[new_price].emplace_back(order);

                Logger::Log()->info("[{}:{}] Order {}-{}, price change done", __func__, __LINE__, id.first, id.second);
                return;
            }
        }

        Logger::Log()->error("[{}:{}] Order {}-{} price not found:{}", __func__, __LINE__, id.first, id.second, old_price);
        return;
    }

    // side error // should not happen        
    Logger::Log()->error("[{}:{}] Order {}-{} side error", __func__, __LINE__, id.first, id.second);
}

void OrderBook::UpdateOrder(const std::string& order_token,
    price_t trade_price, uint64_t executed_qty,
    const OrderStatus status, uint64_t match_id, uint32_t combo_grp_id,
    const std::string& timestamp,
    bool is_price_valid) {
    ExecuteOrder(token_order_id_[order_token],
        trade_price,
        executed_qty,
        status,
        match_id,
        combo_grp_id,
        timestamp,
        is_price_valid);
}

// deleted
void OrderBook::DeleteOrder(const order_id_t& id, const string& timestamp) {
    if (!all_orders_.contains(id)) { // should not happen
        Logger::Log()->error("[{}:{}] Orderbook-Order does not exist: {}-{}",
            __func__, __LINE__, id.first, id.second);
        return;
    }

    Logger::Log()->info("[{}:{}] Delete Order: order id {}-{}, time:{}",
        __func__, __LINE__, id.first, id.second, timestamp);

    const auto& order = all_orders_[id];
    //order->UpdateState(OrderStatus::Canceled, timestamp);

    auto price{ order->GetPrice() };
    all_orders_.erase(id);

    if (id.first == 'B') {
        auto& orders = bid_orders_[price];
        for (auto it = orders.begin(); it != orders.end(); ++it) {
            if ((*it)->GetID() == id) {
                orders.erase(it);

                Logger::Log()->info("[{}:{}] Order Deleted {}-{}", __func__, __LINE__, id.first, id.second);
                break;
            }
        }

        if (orders.empty()) {
            bid_orders_.erase(price);
        }
        return;
    }
    if (id.first == 'S') {
        auto& orders = ask_orders_[price];
        for (auto it = orders.begin(); it != orders.end(); ++it) {
            if ((*it)->GetID() == id) {
                orders.erase(it);

                Logger::Log()->info("[{}:{}] Order Deleted {}-{}", __func__, __LINE__, id.first, id.second);
                break;
            }
        }

        if (orders.empty()) {
            ask_orders_.erase(price);
        }
        return;
    }

    // should not be here
    Logger::Log()->error("[{}:{}] order book side wrong", __func__, __LINE__);
}

string OrderBook::UpdateInstrumentInfo() {
    nlohmann::json j;
    j["Symbol"] = symbol_;
    j["TickSize"] = ParsePrice(tick_size_);
    j["PriceFrom"] = ParsePrice(price_from_);
    j["PriceTo"] = ParsePrice(price_to_);

    return j.dump();
}

string OrderBook::UpdateMarketData() {
    nlohmann::json j;
    j["Symbol"] = symbol_;
    j["DateTime"] = timestamp_;
    j["LocalDateTime"] = TimeUtils::GetNow();

    int i = 0;
    for (auto it = bid_orders_.begin(); i < kDepthLevel && it != bid_orders_.end(); ++it) {
        size_t qty = 0;
        for (auto it2 = bid_orders_[it->first].cbegin(); it2 != bid_orders_[it->first].cend(); ++it2) {
            qty += (*it2)->GetQty();
        }

        if (qty > 0) {
            string idx{ to_string(i + 1) };
            j["BidPrice" + idx] = ParsePrice(it->first);
            j["BidQty" + idx] = qty;
            ++i;
        }
    }

    i = 0;
    for (auto it = ask_orders_.begin(); i < kDepthLevel && it != ask_orders_.end(); ++it) {
        size_t qty = 0;
        for (auto it2 = ask_orders_[it->first].cbegin(); it2 != ask_orders_[it->first].cend(); ++it2) {
            qty += (*it2)->GetQty();
        }

        if (qty > 0) {
            string idx{ to_string(i + 1) };
            j["AskPrice" + idx] = ParsePrice(it->first);
            j["AskQty" + idx] = qty;
            ++i;
        }
    }

    //Logger::Log()->info("[{}:{}] MarketData-{}", __func__, __LINE__, j.dump()); // test only
    return j.dump();
}

string OrderBook::UpdateEquilibriumPrice(uint64_t available_bid_qty,
    uint64_t available_ask_qty,
    price_t best_bid_price,
    price_t best_ask_price,
    uint64_t best_bid_qty,
    uint64_t best_ask_qty,
    price_t equilibrium_price,
    const string& timestamp) {

    nlohmann::json j;

    j["Symbol"] = symbol_;
    j["BidQtyAvailable"] = available_bid_qty;
    j["AskQtyAvailable"] = available_ask_qty;
    j["Price"] = ParsePrice(equilibrium_price);
    j["BestBidPrice"] = ParsePrice(best_bid_price);
    j["BestAskPrice"] = ParsePrice(best_ask_price);
    j["BestBidQty"] = best_bid_qty;
    j["BestAskQty"] = best_ask_qty;
    j["DateTime"] = timestamp;

    Logger::Log()->info("[{}:{}] Equilibrium Price: Order Book ID:{}, symbol:{}, "
        "available_bid_qty:{}, available_ask_qty:{}, equilibrium_price:{}, "
        "best_bid_price:{}, best_ask_price:{}, best_bid_qty:{}, best_ask_qty:{}, timestamp:{}",
        __func__, __LINE__, order_book_id_, symbol_,
        available_bid_qty, available_ask_qty, equilibrium_price,
        best_bid_price, best_ask_price, best_bid_qty, best_ask_qty, timestamp);

    return j.dump();
}
