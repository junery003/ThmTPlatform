//-----------------------------------------------------------------------------
// File Name   : order_book_manager.h
// Author      : junlei
// Date        : 11/26/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __ORDER_BOOK_MANAGER_H__
#define __ORDER_BOOK_MANAGER_H__

#include "order_book.h"
#include "combination_order_book.h"

#include <memory>
#include <unordered_map>

class OrderBookManager { // all instruments 
public:
    //init mapping between instrument_id and order_book_id
    //  instrument_id_to_order_book_id_;
    //  order_book_id_to_instrument_id_;
    // init the order_book_ID and instrument symbol mapping from OMnet API
    static OrderBookManager& Instance() {
        static OrderBookManager ob_mgr;
        return ob_mgr;
    }

public:
    void Subscribe(const std::string& instrument_id);
    void Unsubscribe(const std::string& instrument_id);

    bool InitSubsription(const std::string& instrument_id, uint32_t order_book_id);

    uint32_t GetOrderbookID(const char* instrument_id) {
        auto it = symbol_id_mapping_.find(instrument_id);
        return it != symbol_id_mapping_.end() ? it->second : 0;
    }

    inline std::shared_ptr<OrderBook> GetOrderBook(const uint32_t order_book_id) {
        return subsribed_orderbook_.contains(order_book_id) ? subsribed_orderbook_[order_book_id] : nullptr;
    }

    std::shared_ptr<OrderBook> GetOrderBook(const std::string& token) {
        auto it = order_token_to_order_id_.find(token);
        return it != order_token_to_order_id_.end() ? GetOrderBook(it->second) : nullptr;
    }

    void UpdateCombinationOrderBook(uint32_t comb_order_book_id,
        uint32_t leg_order_book_id,
        char leg_side,
        uint32_t leg_ratio,
        const std::string& timestamp) {
        if (!combination_orderbook_.contains(comb_order_book_id)) {
            combination_orderbook_[comb_order_book_id] = std::make_shared<CombinationOrderBook>(comb_order_book_id);
        }

        combination_orderbook_[comb_order_book_id]->SetLegInfo(leg_order_book_id,
            leg_side,
            leg_ratio,
            timestamp);
    }

    void SetOrderToken2ID(const std::string& token, uint32_t id);

private:
    OrderBookManager() {}

private:
    std::unordered_map<std::string, int32_t> symbol_id_mapping_;

    // <order_book_id, order book>
    std::unordered_map<uint32_t, std::shared_ptr<OrderBook>> subsribed_orderbook_;

    // <order_book_id, comb order book>
    std::unordered_map<uint32_t, std::shared_ptr<CombinationOrderBook>> combination_orderbook_;

    // <order token, order ID>
    std::unordered_map<std::string, uint32_t> order_token_to_order_id_;
};

#endif //!__ORDER_BOOK_MANAGER_H__
