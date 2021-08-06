//-----------------------------------------------------------------------------
// File Name   : trade_handler.h
// Author      : junlei
// Date        : 1/22/2021 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __TRADE_HANDLER_H__
#define __TRADE_HANDLER_H__

#include "account.h"
#include "ouch_client.h"
#include "order_book_manager.h"
#include "zmq_helper.h"

class TradeHanlder {
public:
    TradeHanlder(const std::string& td_server, TitanAccount::OuchConfig& ouch_login)
        : td_zmq_(std::make_shared<ZmqHelper>(td_server, 2))
        , ouch_client_(std::make_unique<OuchClient>(io_contxt_, ouch_login, td_zmq_)) {
    }

public:
    bool Start();
    void Stop() {
        ouch_client_->Stop();
        io_contxt_.stop();
    }

    bool IsStopped() const {
        return is_stopped_;
    }

    void EnterOrder(const char* symbol, char side, double price, uint64_t qty, int tif = 0) {
        ouch_client_->EnterOrder(symbol, side, price, qty, tif);
    }

    void ReplaceOrder(const char* symbol, const char* ori_order_token, double price, uint64_t qty) {
        ouch_client_->ReplaceOrder(symbol, ori_order_token, price, qty);
    }

    void CancelOrder(const char* order_token) {
        ouch_client_->CancelOrder(order_token);
    }

    void CancelByOrderID(const char* symbol, char side, uint64_t order_id) {
        ouch_client_->CancelByOrderID(symbol, side, order_id);
    }

    uint32_t GetOrderbookID(const char* instrument_id) {
        return OrderBookManager::Instance().GetOrderbookID(instrument_id);
    }

    void SetAccount(const std::string& acc) {
        ouch_client_->SetAccount(acc);
    }

private:
    std::shared_ptr<ZmqHelper> td_zmq_;

    boost::asio::io_context io_contxt_;
    std::unique_ptr<OuchClient> ouch_client_;

    bool is_stopped_{ true };
};

#endif //!__TRADE_HANDLER_H__
