//-----------------------------------------------------------------------------
// File Name   : market_data_handler.cpp
// Author      : junlei
// Date        : 11/26/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "market_data_handler.h"
#include "order_book_manager.h"
#include "logger.h"

bool MarketDataHandler::Start() {
    if (!glimpse_client_->Start()) {
        return false;
    }
    glimpse_io_contxt_.run();
    is_glimpse_done_ = true;
    Logger::Log()->info("[{}:{}] Glimpse messages finished", __func__, __LINE__);

    itch_client_->SetInitSeqNumber(glimpse_client_->GetSeqNumber());
    if (!itch_client_->Start()) {
        return false;
    }
    is_itch_stopped_ = false;
    itch_io_contxt_.run();
    is_itch_stopped_ = true;
    Logger::Log()->warn("[{}:{}] ITCH messages stopped", __func__, __LINE__);

    return true;
}

void MarketDataHandler::Stop() {
    if (!is_glimpse_done_) {
        glimpse_client_->Stop();
        glimpse_io_contxt_.stop();
    }

    if (!is_itch_stopped_) {
        itch_client_->Stop();
        itch_io_contxt_.stop();
    }
}

void MarketDataHandler::Subscribe(const char* instrument_id) {
    OrderBookManager::Instance().Subscribe(instrument_id);
}

void MarketDataHandler::Unsubscribe(const char* instrument_id) {
    OrderBookManager::Instance().Unsubscribe(instrument_id);
}
