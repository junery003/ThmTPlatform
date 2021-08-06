//-----------------------------------------------------------------------------
// File Name   : combination_order_book.h
// Author      : junlei
// Date        : 2/26/2021 2:05:03 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __COMBINATION_ORDER_BOOK_H__
#define __COMBINATION_ORDER_BOOK_H__

#include "dt_utils.h"
#include <unordered_map>
#include <memory>

// synthetic
class CombinationOrderBook {
public:
    struct LegInfo {
        uint32_t leg_order_book_id{ 0 }; // real instruments
        char leg_side{ 0 };
        uint32_t leg_ratio{ 0 };
    };

public:
    CombinationOrderBook(uint32_t combination_order_book_id)
        : combination_order_book_id_(combination_order_book_id) {
    }

    void SetLegInfo(uint32_t leg_order_book_id,
        char leg_side,
        uint32_t leg_ratio,
        const std::string& timestamp);

private:
    uint32_t combination_order_book_id_;
    LegInfo leg_info_;
    std::string timestamp_;

    // <leg order book id, leg info>
    std::unordered_map<uint32_t, std::shared_ptr<LegInfo>> legs_;
};

#endif //!__COMBINATION_ORDER_BOOK_H__
