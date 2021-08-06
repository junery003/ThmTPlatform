//-----------------------------------------------------------------------------
// File Name   : order_book_manager.cpp
// Author      : junlei
// Date        : 11/26/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "order_book_manager.h"

#include "logger.h"

bool OrderBookManager::InitSubsription(const std::string& instrument_id, uint32_t order_book_id) {
    if (symbol_id_mapping_.find(instrument_id) == symbol_id_mapping_.end()) {
        return false;
        //Subscribe(instrument_id);
    }

    symbol_id_mapping_[instrument_id] = order_book_id;
    if (subsribed_orderbook_.find(order_book_id) == subsribed_orderbook_.end()) {
        subsribed_orderbook_[order_book_id] = std::make_shared<OrderBook>(order_book_id);
    }

    return true;
}

void OrderBookManager::Subscribe(const std::string& instrument_id) {
    auto it = symbol_id_mapping_.find(instrument_id);
    if (it == symbol_id_mapping_.end()) {
        symbol_id_mapping_[instrument_id] = 0;
        //Logger::Log()->info("[{}:{}] Subscribed {}", __func__, __LINE__, instrument_id);
    }
    else {
        //Logger::Log()->info("[{}:{}] Already subscribed {}", __func__, __LINE__, instrument_id);
    }
}

void OrderBookManager::Unsubscribe(const std::string& instrument_id) {
    auto it = symbol_id_mapping_.find(instrument_id);
    if (it == symbol_id_mapping_.end()) {
        Logger::Log()->info("[{}:{}] {} not subsribed", __func__, __LINE__, instrument_id);
    }
    else {
        symbol_id_mapping_.erase(it);
        Logger::Log()->info("[{}:{}] Unsubscribed {}", __func__, __LINE__, instrument_id);
    }
}

void OrderBookManager::SetOrderToken2ID(const std::string& token, uint32_t id) {
    if (order_token_to_order_id_.find(token) == order_token_to_order_id_.end()) {
        order_token_to_order_id_[token] = id;
        return;
    }

    if (order_token_to_order_id_[token] != id) { // should not happen
        Logger::Log()->error("[{}:{}] {} order token and ID not correct: '{}' - {}",
            __func__, __LINE__, token, id);
    }
}