//-----------------------------------------------------------------------------
// File Name   : ctp_client.cpp
// Author      : junlei
// Date        : 8/25/2021 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "ctp_client.h"

using namespace std;

CtpClient::CtpClient() {}

bool CtpClient::Init() {
    if (!cfg_helper_.Load()) {
        return false;
    }

    const auto& acct{ cfg_helper_.config.account };

    td_zmq_ = make_shared<ZmqHelper>(cfg_helper_.config.td_stream_server, 2);
    UpdateTradeClient();

    md_zmq_ = make_shared<ZmqHelper>(cfg_helper_.config.md_stream_server, 1);
    md_client_ = make_unique<MarketDataClient>(acct.md_server.c_str(),
        acct.broker_ID.c_str(), acct.user_ID.c_str(), acct.user_password.c_str(),
        md_zmq_);

    md_client_->Connect();
    return true;
}

void CtpClient::UpdateTradeClient(const char* userId, const char* password) {
    CtpAccount acct{ cfg_helper_.config.account };

    if (userId == nullptr) {
        if (!cur_acc_.empty()) {
            return;
        }

        cur_acc_ = cfg_helper_.config.account.user_ID;
    }
    else {
        //const auto& accts{ cfg_helper_.config.account }; // find user_ID == userId
        //acct = accts[0];
        cur_acc_ = userId;
    }

    if (!trade_client_map_.contains(cur_acc_)) {
        auto tradeClient = make_shared<TraderClient>(acct.trade_server.c_str(),
            acct.broker_ID.c_str(), acct.user_ID.c_str(), acct.user_password.c_str(),
            acct.investor_ID.c_str(), acct.app_ID.c_str(), acct.auth_code.c_str(),
            td_zmq_);

        tradeClient->Connect();

        trade_client_map_[cur_acc_] = tradeClient;
    }
}
