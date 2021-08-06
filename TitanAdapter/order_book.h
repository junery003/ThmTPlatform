//-----------------------------------------------------------------------------
// File Name   : order_book.h
// Author      : junlei
// Date        : 11/5/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __ORDERBOOK_H__
#define __ORDERBOOK_H__

#include "order.h"
#include <string>
#include <unordered_map>
#include <map>
#include <memory>

class OrderBook { // = instrument
public:
    OrderBook(uint32_t order_book_id)
        : order_book_id_(order_book_id) {
    }

public:
    void Init(const std::string& symbol,
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
        const std::string& timestamp);

    void SetTickSize(uint64_t tick_size, price_t from, price_t to, const std::string& timestamp);

    void SetState(const std::string& state, const std::string& timestamp);

public:
    inline std::string GetSymbol() const { return symbol_; }

    // price_t to double: parse message to get the actually price
    template<class T>
    double ParsePrice(T price) const {
        auto ratio = (T)pow(10, decimal_num_in_price_);
        return (double)price / ratio;
    }

    // double to price_t: format price to send msg
    price_t FormatPrice(double price) const {
        auto ratio = (price_t)pow(10, decimal_num_in_price_);
        return (price_t)(price * ratio);
    }

    std::shared_ptr<Order> GetOrder(const order_id_t& id) {
        return all_orders_.contains(id) ? all_orders_[id] : nullptr;
    }

    //uint32_t GetOrderBookID(const order_id_t& id) {
    //    if (orders_.find(id) != orders_.end()) {
    //        return orders_[id]->GetOrderBookID();
    //    }
    //    return 0;
    //}

public:
    bool AddOrder(const order_id_t& id,
        uint32_t order_book_id,
        uint32_t order_book_position,
        price_t price, uint64_t qty,
        uint16_t other_attributes,
        uint8_t lot_type,
        const std::string& timestamp);

    void DeleteOrder(const order_id_t& id,
        const std::string& timestamp);

    void ExecuteOrder(const order_id_t& id,
        price_t trade_price,
        uint64_t executed_qty,
        const OrderStatus status,
        uint64_t match_id,
        uint32_t combo_grp_id,
        const std::string& timestamp,
        bool is_price_valid = true);

public:
    std::string UpdateInstrumentInfo();
    std::string UpdateMarketData();
    std::string UpdateEquilibriumPrice(uint64_t available_bid_qty,
        uint64_t available_ask_qty,
        price_t best_bid_price,
        price_t best_ask_price,
        uint64_t best_bid_qty,
        uint64_t best_ask_qty,
        price_t equilibrium_price,
        const std::string& timestamp);

private:
    void UpdateOrder(const std::string& order_token,
        price_t trade_price,
        uint64_t executed_qty,
        const OrderStatus status,
        uint64_t match_id,
        uint32_t combo_grp_id,
        const std::string& timestamp,
        bool is_price_valid = true);

    void ChangeOrderPrice(const order_id_t& id, price_t old_price, price_t new_price);

private:
    uint32_t order_book_id_; // id <--> symbol

    std::string symbol_;
    std::string long_name_;
    std::string isin_;
    std::string financial_product_;
    std::string currency_;
    uint16_t decimal_num_in_price_{ 0 };
    uint16_t decimal_num_in_nominal_value_{ 0 };
    uint32_t odd_lot_size_{ 0 };
    uint32_t round_lot_size_{ 0 };
    uint32_t block_lot_size_{ 0 };
    uint64_t nominal_value_{ 0 };
    char legs_number_{ 1 };  // combination instrument only
    uint32_t commodity_code_{ 0 };
    std::string expiration_date_;

    price_t strike_price_{ 0 }; // options only
    uint16_t decimal_num_in_strike_price_{ 0 };
    char put_call_{ 0 }; // option type: 1=Call; 2=Put

    uint64_t tick_size_{ 0 };
    price_t price_from_{ 0 };
    price_t price_to_{ 0 };

    std::string state_;

    std::string timestamp_;  // lasted update timestamp

private:
    //<<side, order ID>, order>
    std::unordered_map<order_id_t, std::shared_ptr<Order>, PairHash> all_orders_;
    // <order token, <side, order ID>>
    std::unordered_map<std::string, order_id_t> token_order_id_;

    std::map<price_t, std::list<std::shared_ptr<Order>>, std::greater<price_t>> bid_orders_; // descending
    std::map<price_t, std::list<std::shared_ptr<Order>>> ask_orders_; // ascending

    static constexpr int kDepthLevel{ 5 };
};

#endif // !__ORDERBOOK_H__
