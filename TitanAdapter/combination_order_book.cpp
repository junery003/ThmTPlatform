//-----------------------------------------------------------------------------
// File Name   : combination_order_book.cpp
// Author      : junlei
// Date        : 2/26/2021 2:05:03 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "combination_order_book.h"

#include "logger.h"

void CombinationOrderBook::SetLegInfo(uint32_t leg_order_book_id,
    char leg_side,
    uint32_t leg_ratio,
    const std::string& timestamp) {
    Logger::Log()->info("Comb order book id:{}, leg order book id:{}, leg side:{}, leg ratio:{}, time:{}",
        combination_order_book_id_, leg_order_book_id, leg_side, leg_ratio, timestamp);

    timestamp_ = timestamp;

    auto it = legs_.find(leg_order_book_id);
    if (it == legs_.end()) {
        legs_[leg_order_book_id] = std::make_shared<LegInfo>(leg_order_book_id, leg_side, leg_ratio);
        return;
    }

    it->second->leg_order_book_id = leg_order_book_id;
    it->second->leg_side = leg_side;
    it->second->leg_ratio = leg_ratio;
}
