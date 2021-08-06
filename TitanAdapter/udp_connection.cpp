//-----------------------------------------------------------------------------
// File Name   : udp_client.h
// Author      : junlei
// Date        : 11/5/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "udp_connection.h"
#include "mold_udp64_parser.h"
#include "logger.h"

using namespace boost::asio;
using namespace std;

UdpConnection::UdpConnection(io_context& io_contxt, const std::string& server, int port)
    : skt_(io_contxt)
    , endpt_(ip::address::from_string(server), port) {
    ip::address listen_addr(ip::address_v4::any()); // ip::address::from_string("10.42.98.253")); // Fine
    ip::address multicast_addr(ip::address::from_string(server));

    ip::udp::endpoint listen_endpt(listen_addr, port);

    skt_.open(listen_endpt.protocol());
    skt_.set_option(ip::udp::socket::reuse_address(true));
    //skt_.set_option(ip::multicast::enable_loopback(false));
    skt_.bind(listen_endpt);
    //skt_.bind(ip::udp::endpoint(multicast_addr, port));  // not working

    skt_.set_option(ip::multicast::join_group(multicast_addr));
    //skt_.set_option(ip::multicast::join_group(multicast_addr.to_v4(), listen_addr.to_v4())); // working
}

bool UdpConnection::Start() {
    Receive();
    return true;
}

void UdpConnection::Connect() { // not necessary for UDP
    skt_.async_connect(endpt_,
        [this](const error_code& ec) {
            if (ec) {
                Logger::Log()->error("UDP failed to connect: {}-{}", ec, system_error(ec).what());
                return;
            }

            Logger::Log()->info("UDP connected successfully");

            Receive();
        }
    );
}

void UdpConnection::Disconnect() {
    Logger::Log()->warn("[{}:{}] UDP disconnected", __func__, __LINE__);

    if (skt_.is_open()) {
        skt_.close();
    }
}

void UdpConnection::Send(const char* msg, size_t len) {
    if (len < 1) {
        Logger::Log()->warn("[{}:{}] UDP sending msg is empty", __func__, __LINE__);
        return;
    }

    skt_.async_send_to(buffer(msg, len), endpt_,
        [this](const error_code& ec, size_t length) {
            if (ec) {
                Logger::Log()->error("UDP error sending msg: {}-{}", ec, system_error(ec).what());
                return;
            }

            Logger::Log()->info("UDP msg sent successfully: len:{}", length);
        }
    );
}

void UdpConnection::Receive() {
    skt_.async_receive_from(buffer(read_buf_, kReadLenMax), sender_endpt_,
        [this](const error_code& ec, size_t length) {
            if (ec) {
                Logger::Log()->error("UDP read error: {}-{}", ec, system_error(ec).what());
                return;
            }

            if (length < 1) {
                Logger::Log()->warn("UDP read empty");
                return;
            }

            //Logger::Log()->info("UDP msg received, len:{}", length);
            Parse(read_buf_, (int)length);

            Receive();
        }
    );
}

// start from MoldUDP64 protocol
bool UdpConnection::Parse(const char* msg, const int msg_len) {
    return upper_layer_->Parse(msg, msg_len);
}
