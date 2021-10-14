//-----------------------------------------------------------------------------
// File Name   : udp_connection.h
// Author      : junlei
// Date        : 11/4/2020 2:30:27 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __UDP_CONNECTION_H__
#define __UDP_CONNECTION_H__

#include "protocol_base.h"
#include "boost/asio.hpp"

class UdpConnection : public ProtocolBase {
public:
    UdpConnection(boost::asio::io_context& io_contxt, const std::string& ip, int port);

    ~UdpConnection() {
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

    //void SetConnection(bool is_connected) override {}

private:
    void Connect();
    void Disconnect();
    void Receive();

private:
    char read_buf_[kReadLenMax]{ 0 };

    boost::asio::ip::udp::endpoint endpt_;
    boost::asio::ip::udp::socket skt_;

    boost::asio::ip::udp::endpoint sender_endpt_;

    std::shared_ptr<ProtocolBase> upper_layer_;
};

#endif // !__UDP_CONNECTION_H__
