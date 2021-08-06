//-----------------------------------------------------------------------------
// File Name   : order.h
// Author      : junlei
// Date        : 11/26/2020 2:05:03 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __ORDER_H__
#define __ORDER_H__

#include "dt_utils.h"
#include "utils.h"
#include <string>

class Order {
public:
    Order(const order_id_t& id,
        uint32_t order_book_id, const std::string& symbol,
        uint32_t order_book_position,
        price_t price,
        uint64_t qty,
        uint16_t other_attributes,
        uint8_t lot_type,
        const std::string& timestamp,
        OrderStatus status = OrderStatus::New,
        const std::string& order_token = "")
        : id_(id)
        , order_book_id_(order_book_id)
        , symbol_(symbol)
        , order_book_position_(order_book_position)
        , timestamp_(timestamp)
        , price_(price)
        , open_qty_(qty)
        , other_attributes_(other_attributes)
        , lot_type_(lot_type)
        , status_(status)
        , order_token_(order_token) {
    }

public:
    order_id_t GetID() const { return id_; }
    //uint32_t GetOrderBookID() const { return order_book_id_; }
    const std::string& GetToken() const { return order_token_; }
    price_t GetPrice() const { return price_; }
    uint64_t GetQty() const { return open_qty_; }

public:
    void AddExecuted(const uint64_t executed_qty, const std::string& timestamp) {
        open_qty_ -= executed_qty;
        filled_qty_ += executed_qty;
        timestamp_ = timestamp;
    }

    void UpdateState(const OrderStatus status, const std::string& timestamp) {
        status_ = status;
        timestamp_ = timestamp;
    }

    void UpdatePrice(const price_t new_price) {
        price_ = new_price;
    }

    std::string UpdateOrderInfo();

private:
    order_id_t id_; // <side & order id>  // is only unique per Order Book and side

    std::string order_token_;

    uint32_t order_book_id_;
    std::string symbol_;
    uint32_t order_book_position_;

    price_t price_; // the actual price 
    uint64_t open_qty_;  // working qty
    uint64_t filled_qty_{ 0 };

    OrderStatus status_;
    std::string timestamp_;
    std::string local_time_;

    uint16_t other_attributes_{ 0 };
    uint8_t lot_type_{ 2 };
};

#endif //! __ORDER_H__
