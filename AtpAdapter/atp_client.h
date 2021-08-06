//-----------------------------------------------------------------------------
// File Name   : atp_client.h
// Author      : junlei
// Date        : 9/17/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __ATP_CLIENT_H__
#define __ATP_CLIENT_H__

#include "config_helper.h"
#include "market_data_client.h"
#include "trader_client.h"

#include <unordered_map>

class AtpClient {
public:
    AtpClient(const char* md_server,
        const char* td_server,
        const char* brokerId,
        const char* userId,
        const char* userPwd,
        const char* investorId,
        const char* appId,
        const char* authCode,
        const char* streamDataAddr,
        const char* streamTradeAddr);

    ~AtpClient() {}

public:
    void UpdateTradeClient(const char* td_server,
        const char* brokerId,
        const char* userId,
        const char* password,
        const char* investorId,
        const char* appId,
        const char* authCode);

    int Subscribe(const char* symbol) {
        trade_client_map_.cbegin()->second->QueryInstrument(symbol);
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
    bool Init();

    void StartMarket();
    void StartTrade();

private:
    ConfigHelper cfg_helper_;

    std::shared_ptr<ZmqHelper> md_zmq_;
    std::shared_ptr<ZmqHelper> td_zmq_;

    std::string cur_acc_;
    std::unique_ptr<MarketDataClient> md_client_ = nullptr;
    std::unordered_map<std::string, std::shared_ptr<TraderClient>> trade_client_map_;
};

#endif // __ATP_CLIENT_H__
