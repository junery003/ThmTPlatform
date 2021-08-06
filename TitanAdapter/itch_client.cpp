//-----------------------------------------------------------------------------
// File Name   : itch_client.cpp
// Author      : junlei
// Date        : 12/14/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "itch_client.h"
#include "mold_udp64_parser.h"
#include "logger.h"

using namespace std;

ItchClient::ItchClient(boost::asio::io_context& io_contxt,
    TitanAccount::ItchConfig& itch_login,
    shared_ptr<ZmqHelper> md_zmq)
    : io_contxt_(io_contxt)
    , itch_login_(itch_login)
    , itch_parser_(make_shared<ItchGlimpseParser>(md_zmq)) {
    Logger::Log()->info("[{}:{}] Starting ITCH-{}:{}", __func__, __LINE__,
        itch_login_.server, itch_login_.port);

    auto conn{ make_shared<UdpConnection>(io_contxt_,
        itch_login_.server,
        itch_login_.port) };

    auto moldudp64_parser{ make_shared<MoldUdp64Parser>() };

    moldudp64_parser->SetUpperLayer(itch_parser_);
    moldudp64_parser->SetLowerLayer(dynamic_pointer_cast<ProtocolBase>(conn));
}

bool ItchClient::Start() {
    return itch_parser_->Start();
}

void ItchClient::Stop() {
    Logger::Log()->warn("[{}:{}] Stopping ITCH client", __func__, __LINE__);

    itch_parser_->Stop();
}
