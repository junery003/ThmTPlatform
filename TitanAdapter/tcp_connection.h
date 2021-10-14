//-----------------------------------------------------------------------------
// File Name   : tcp_connection.h
// Author      : junlei
// Date        : 11/5/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __TCP_CONNECTION_H__
#define __TCP_CONNECTION_H__

#include "protocol_base.h"
#include "boost/asio.hpp"
#include "boost/circular_buffer.hpp"

#include <string>
#include <memory>

class TcpConnection : public ProtocolBase {
public:
    TcpConnection(boost::asio::io_context& io_contxt, int id,
        const std::string& ip, int port,
        const std::string& ip2 = "", int port2 = -1)
        : skt_(io_contxt), id_(id)
        , endpt_(boost::asio::ip::address::from_string(ip), port) {
        if (!ip2.empty() && port2 > 0) {
            endpt2_ = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip2), port2);
        }
    }

    ~TcpConnection() {
        Stop();
    }

public:
    void SetUpperLayer(std::shared_ptr<ProtocolBase> upper_layer) override {
        upper_layer_ = upper_layer;
    }
    void SetLowerLayer(std::shared_ptr<ProtocolBase> lower_layer) override {}

    bool Start() override;
    void Stop() override {
        Disconnect();
    }

    bool Parse(const char* msg, const int msg_len) override;

    void Send(const char* msg, size_t len);

    void SetConnection(bool is_connected) override {
        is_connected_ = is_connected;
    }

private:
    void Connect(bool is_primary = true);
    void Disconnect();

    void Receive();

private:
    char read_buf_[kReadLenMax]{ 0 };  // 

    boost::asio::ip::tcp::socket skt_;

    boost::asio::ip::tcp::endpoint endpt_;
    boost::asio::ip::tcp::endpoint endpt2_;

    std::shared_ptr<ProtocolBase> upper_layer_;

    bool is_connected_{ false };

    int id_{ 0 };
    int retry_times_{ 0 };
};

#endif // !__TCP_CONNECTION_H__
