//-----------------------------------------------------------------------------
// File Name   : titan_apis.h
// Author      : junlei
// Date        : 11/18/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __TITAN_APIS_H__
#define __TITAN_APIS_H__

#include "config_helper.h"
#include "omnet_client.h"
#include "market_data_handler.h"
#include "trade_handler.h"

#include <memory>
#include <thread>

class TitanClient {
public:
    TitanClient();
    ~TitanClient() {
    }

public:
    bool Start();
    void Stop();

    void Subscribe(const char* instrument_id);
    void Unsubscribe(const char* instrument_id);

    bool ChangePassword(const char* usr, const char* cur_pwd, const char* new_pwd) {
        const auto& omnet = cfg_helper_.config.account.omnet;
        auto client = std::make_unique<OMnetClient>();
        return client->ChangePassword(omnet.server.c_str(), omnet.port, usr, cur_pwd, new_pwd);
    }

    void SetAccount(const char* account);
    void AddOrder(const char* instrument, bool is_buy, double price, uint32_t qty, int tif = 0);
    void ReplaceOrder(const char* instrument, const char* ori_order_token, double price, uint32_t qty);
    void CancelOrder(const char* order_token);
    void CancelOrderByID(const char* instrument, bool is_buy, uint64_t order_id);

private:
    void StartMarket();
    void StartTrade();

private:
    ConfigHelper cfg_helper_;

    std::unique_ptr<MarketDataHandler> market_data_handler_;
    std::unique_ptr<TradeHanlder> trade_handler_;

    std::jthread market_thd_;
    std::jthread trade_thd_;
};

#endif //!__TITAN_APIS_H__
