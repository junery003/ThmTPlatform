//-----------------------------------------------------------------------------
// File Name   : titan_apis.cpp
// Author      : junlei
// Date        : 11/18/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "titan_client.h"
#include "logger.h"

using namespace std;

TitanClient::TitanClient() {
}

// -----------------------------------------------------------------------------------------------;
bool TitanClient::Start() {
    if (!cfg_helper_.Load()) {  // config file
        Logger::Log()->error("[{}:{}] failed to load Titan config", __func__, __LINE__);
        return false;
    }

    Logger::Log()->info("[{}:{}] Starting Titan Clients", __func__, __LINE__);
    StartMarket();
    StartTrade();

    return true;
}

// ITCH/Glimpse
void TitanClient::StartMarket() {
    if (market_data_handler_ == nullptr) {
        market_data_handler_ = make_unique<MarketDataHandler>(cfg_helper_.config.md_stream_server,
            cfg_helper_.config.account.glipmse,
            cfg_helper_.config.account.itch);
        const auto& contracts = cfg_helper_.config.exchanges;
        for (const auto& it : contracts) {
            if (it.is_enabled) {
                for (const auto& prod : it.products) {
                    for (const auto& contract : prod.contracts) {
                        Subscribe(contract.c_str());
                    }
                }
            }
        }
    }

    if (market_data_handler_->IsStopped()) {
        market_thd_ = std::jthread{ [this] {
            if (!market_data_handler_->Start()) {
                Logger::Log()->error("[{}:{}] Failed to start market data.", __func__, __LINE__);
            }
        } };
    }

    while (!market_data_handler_->IsGlimpseDone()) {
        this_thread::sleep_for(3s);
    }
}

// OUCH
void TitanClient::StartTrade() {
    if (trade_handler_ == nullptr) {
        trade_handler_ = make_unique<TradeHanlder>(cfg_helper_.config.td_stream_server,
            cfg_helper_.config.account.ouch);
    }

    if (trade_handler_->IsStopped()) {
        trade_thd_ = std::jthread{ [this] {
            if (!trade_handler_->Start()) {
                Logger::Log()->error("[{}:{}] Failed to start trade data", __func__, __LINE__);
            }
        } };
    }

    this_thread::sleep_for(3s);
}

void TitanClient::Stop() {
    Logger::Log()->warn("Stopping Titan client");

    market_data_handler_->Stop();
    trade_handler_->Stop();
}

// -----------------------------------------------------------------------------------------------;
// market data
// -----------------------------------------------------------------------------------------------;
void TitanClient::Subscribe(const char* instrument_id) {
    Logger::Log()->info("[{}:{}] subsrcibing {}", __func__, __LINE__, instrument_id);

    market_data_handler_->Subscribe(instrument_id);
}

void TitanClient::Unsubscribe(const char* instrument_id) {
    Logger::Log()->info("[{}:{}] unsubsrcibing {}", __func__, __LINE__, instrument_id);

    market_data_handler_->Unsubscribe(instrument_id);
}

// -----------------------------------------------------------------------------------------------;
// trade
// -----------------------------------------------------------------------------------------------;
void TitanClient::SetAccount(const char* account) {
    trade_handler_->SetAccount(account);
}

void TitanClient::AddOrder(const char* instrument, bool is_buy, double price, uint32_t qty, int tif) {
    trade_handler_->EnterOrder(instrument, is_buy ? 'B' : 'S', price, qty, tif);
}

void TitanClient::ReplaceOrder(const char* instrument, const char* ori_order_token,
    double price, uint32_t qty) {
    trade_handler_->ReplaceOrder(instrument, ori_order_token, price, qty);
}

void TitanClient::CancelOrder(const char* order_token) {
    trade_handler_->CancelOrder(order_token);
}

void TitanClient::CancelOrderByID(const char* instrument, bool is_buy, uint64_t order_id) {
    trade_handler_->CancelByOrderID(instrument, is_buy ? 'B' : 'S', order_id);
    return;
}
