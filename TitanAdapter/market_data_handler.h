//-----------------------------------------------------------------------------
// File Name   : market_data_handler.h
// Author      : junlei
// Date        : 11/26/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __MARKET_DATA_HANDLER_H__
#define __MARKET_DATA_HANDLER_H__

#include "account.h"
#include "glimpse_client.h"
#include "itch_client.h"
#include "zmq_helper.h"

#include <memory>

class MarketDataHandler {
public:
    MarketDataHandler(const std::string& md_server,
        TitanAccount::GlimpseConfig& glipmse_login, TitanAccount::ItchConfig& itch_login)
        : md_zmq_(std::make_shared<ZmqHelper>(md_server, 1))
        , glimpse_client_(std::make_unique<GlimpseClient>(glimpse_io_contxt_, glipmse_login, md_zmq_))
        , itch_client_(std::make_unique<ItchClient>(itch_io_contxt_, itch_login, md_zmq_)) {
    }

public:
    bool Start();
    void Stop();

    void Subscribe(const char* instrument_id);
    void Unsubscribe(const char* instrument_id);

    bool IsGlimpseDone() const {
        return is_glimpse_done_;
    }

    bool IsStopped() const {
        return is_itch_stopped_;
    }

private:
    std::shared_ptr<ZmqHelper> md_zmq_;

    boost::asio::io_context glimpse_io_contxt_;
    boost::asio::io_context itch_io_contxt_;

    std::unique_ptr<GlimpseClient> glimpse_client_;
    std::unique_ptr<ItchClient> itch_client_;

    bool is_glimpse_done_{ false };
    bool is_itch_stopped_{ true };
};

#endif // !__MARKET_DATA_HANDLER_H__
