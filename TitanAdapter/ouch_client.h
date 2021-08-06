//-----------------------------------------------------------------------------
// File Name   : ouch_client.h
// Author      : junlei
// Date        : 12/14/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __OUCH_CLIENT_H__
#define __OUCH_CLIENT_H__

#include "account.h"
#include "ouch_parser.h"

#include "boost/asio.hpp"

class OuchClient : public ClientBase {
public:
    OuchClient(boost::asio::io_context& io_contxt,
        TitanAccount::OuchConfig& ouch_login,
        std::shared_ptr<ZmqHelper> td_zmq);

    ~OuchClient() {
    }

public:
    bool Start() override;
    void Stop() override;

    void EnterOrder(const char* symbol, char side, double price, uint64_t qty, int tif = 0);
    void ReplaceOrder(const char* symbol, const char* existing_token, double price, uint64_t qty);
    void CancelOrder(const char* order_token);
    void CancelByOrderID(const char* symbol, char side, uint64_t order_id);

    void SetAccount(const std::string& acc);

private:
    TitanAccount::OuchConfig& ouch_login_;
    std::string cur_account_; // for trading
    std::string cur_customer_info_;

    boost::asio::io_context& io_contxt_;

    std::shared_ptr<OuchParser> ouch_parser_;
};

#endif //!__OUCH_CLIENT_H__
