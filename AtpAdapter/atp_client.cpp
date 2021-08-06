//-----------------------------------------------------------------------------
// File Name   : atp_client.cpp
// Author      : junlei
// Date        : 9/17/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "atp_client.h"

using namespace std;

AtpClient::AtpClient(const char* md_server,
    const char* td_server,
    const char* brokerId,
    const char* userId,
    const char* userPwd,
    const char* investorId,
    const char* appId,
    const char* authCode,
    const char* stream_data_addr,
    const char* stream_trade_addr)
    : md_zmq_(make_shared<ZmqHelper>(stream_data_addr, 1))
    , td_zmq_(make_shared<ZmqHelper>(stream_trade_addr, 2)) {

    md_client_ = make_unique<MarketDataClient>(md_server, brokerId, userId, userPwd, md_zmq_);
    md_client_->Connect();

    UpdateTradeClient(td_server, brokerId, userId, userPwd, investorId, appId, authCode);
}

bool AtpClient::Init() {
    if (!cfg_helper_.Load()) {
        return false;
    }

    StartMarket();
    StartTrade();

    return true;
}


void AtpClient::StartMarket() {
}

void AtpClient::StartTrade() {
}

void AtpClient::UpdateTradeClient(const char* td_server, const char* brokerId, const char* userId, const char* password,
    const char* investorId, const char* appId, const char* authCode) {
    cur_acc_ = userId; //string id(string(brokerID) + "-" + userID);
    if (trade_client_map_.find(cur_acc_) == trade_client_map_.end()) {
        auto tradeClient = make_shared<TraderClient>(td_server, brokerId, userId, password,
            investorId, appId, authCode, td_zmq_);

        tradeClient->Connect();

        trade_client_map_[cur_acc_] = tradeClient;
    }
}
