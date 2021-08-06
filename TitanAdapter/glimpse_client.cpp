//-----------------------------------------------------------------------------
// File Name   : glimpse_client.cpp
// Author      : junlei
// Date        : 12/14/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "glimpse_client.h"
#include "soup_bin_tcp_parser.h"
#include "logger.h"

using namespace std;

GlimpseClient::GlimpseClient(boost::asio::io_context& io_contxt,
    TitanAccount::GlimpseConfig& glipmse_login,
    shared_ptr<ZmqHelper> md_zmq)
    : io_contxt_(io_contxt)
    , glipmse_login_(glipmse_login)
    , glimse_parser_(make_shared<ItchGlimpseParser>(md_zmq)) {

    Logger::Log()->info("[{}:{}] Starting Glimpse-{}:{}, user:{}, pwd:{}, heartbeat:{}",
        __func__, __LINE__, glipmse_login_.server, glipmse_login_.port,
        glipmse_login_.ID, glipmse_login_.password, glipmse_login_.heartbeat);

    auto conn{ make_shared<TcpConnection>(io_contxt_, 1,
        glipmse_login_.server,
        glipmse_login_.port)
    };

    auto soupbintcp_parser_{ make_shared<SoupBinTcpParser>(glipmse_login_.ID,
        glipmse_login_.password,
        glipmse_login_.heartbeat) };

    soupbintcp_parser_->SetUpperLayer(glimse_parser_);
    soupbintcp_parser_->SetLowerLayer(dynamic_pointer_cast<ProtocolBase>(conn));
}

bool GlimpseClient::Start() {
    return glimse_parser_->Start();
}

void GlimpseClient::Stop() {
    Logger::Log()->warn("[{}:{}] Stopping Glimpse Client", __func__, __LINE__);
    glimse_parser_->Stop();
}
