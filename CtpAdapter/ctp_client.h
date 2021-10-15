//-----------------------------------------------------------------------------
// File Name   : ctp_client.h
// Author      : junlei
// Date        : 8/25/2021 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __CTP_CLIENT_H__
#define __CTP_CLIENT_H__

#include "config_helper.h"
#include "market_data_client.h"
#include "trader_client.h"

#include <unordered_map>

class CtpClient {
public:
    CtpClient();
    ~CtpClient() {}

public:
    bool Init();

    void UpdateTradeClient(const char* userId = nullptr, const char* password = nullptr);

    int Subscribe(const char* symbol, const char* exchangeID) {
        trade_client_map_.cbegin()->second->QueryInstrument(symbol, exchangeID);
        return md_client_->SubscribeContract(symbol);
    }

    void Unsubscribe(const char* symbol) {
        md_client_->UnsubscribeContract(symbol);
    }

    void SetAccountID(const char* id) {
        cur_acc_ = id;
    }

    int InsertOrder(const char* symbol, bool isBuy, double price, int volume, const char* orderTag) {
        return trade_client_map_[cur_acc_]->InsertOrder(symbol, isBuy, price, volume, orderTag);
    }

    int ModifyOrder(const char* exchangeId, const char* orderId, double price, int qty) {
        return trade_client_map_[cur_acc_]->ModifyOrder(exchangeId, orderId, price, qty);
    }

    int CancelOrder(const char* exchangeId, const char* orderId) {
        return trade_client_map_[cur_acc_]->CancelOrder(exchangeId, orderId);
    }

    void QueryOrder(const char* symbol) {
        trade_client_map_[cur_acc_]->QueryOrder(symbol);
    }

    void QueryTrade(const char* symbol) {
        trade_client_map_[cur_acc_]->QueryTrade(symbol);
    }

    void QueryInvestorPosition(const char* symbol) {
        trade_client_map_[cur_acc_]->QueryInvestorPosition(symbol);
    }

private:
    ConfigHelper cfg_helper_;

    std::shared_ptr<ZmqHelper> md_zmq_;
    std::shared_ptr<ZmqHelper> td_zmq_;

    std::string cur_acc_;
    std::unique_ptr<MarketDataClient> md_client_ = nullptr;
    std::unordered_map<std::string, std::shared_ptr<TraderClient>> trade_client_map_;
};

#endif // __CTP_CLIENT_H__
