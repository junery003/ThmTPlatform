//-----------------------------------------------------------------------------
// File Name   : glimpse_client.h
// Author      : junlei
// Date        : 12/14/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __GLIMPSE_CLIENT_H__
#define __GLIMPSE_CLIENT_H__

#include "account.h"
#include "itch_glimpse_parser.h"
#include "zmq_helper.h"

#include "boost/asio.hpp"
#include <string>

class GlimpseClient :public ClientBase {
public:
    GlimpseClient(boost::asio::io_context& io_contxt,
        TitanAccount::GlimpseConfig& glipmse_login,
        std::shared_ptr<ZmqHelper> md_zmq);

    ~GlimpseClient() {
    }

public:
    bool Start() override;
    void Stop() override;

    uint64_t GetSeqNumber() const {
        return glimse_parser_->GetSeqNumber();
    }

private:
    TitanAccount::GlimpseConfig& glipmse_login_;
    boost::asio::io_context& io_contxt_;

    std::shared_ptr<ItchGlimpseParser> glimse_parser_;
};

#endif // !__GLIMPSE_CLIENT_H__
