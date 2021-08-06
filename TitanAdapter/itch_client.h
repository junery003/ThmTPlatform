//-----------------------------------------------------------------------------
// File Name   : itch_client.cpp
// Author      : junlei
// Date        : 12/14/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __ITCH_CLIENT_H__
#define __ITCH_CLIENT_H__

#include "account.h"
#include "itch_glimpse_parser.h"
#include "zmq_helper.h"

#include "boost/asio.hpp"

class ItchClient : public ClientBase {
public:
    // neither user nor pwd is necessary
    ItchClient(boost::asio::io_context& io_contxt,
        TitanAccount::ItchConfig& itch_login,
        std::shared_ptr<ZmqHelper> md_zmq);

public:
    bool Start() override;
    void Stop() override;

    void SetInitSeqNumber(uint64_t seq_num) {
        itch_parser_->SetInitSeqNumber(seq_num);
    }

private:
    TitanAccount::ItchConfig& itch_login_;
    boost::asio::io_context& io_contxt_;

    std::shared_ptr<ItchGlimpseParser> itch_parser_;
};

#endif //! __ITCH_CLIENT_H__
