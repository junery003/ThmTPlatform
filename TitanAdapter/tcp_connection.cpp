//-----------------------------------------------------------------------------
// File Name   : tcp_connection.h
// Author      : junlei
// Date        : 11/5/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "tcp_connection.h"
#include "logger.h"

using namespace boost::asio;
using namespace std;

bool TcpConnection::Start() {
    Connect();
    return true;
}

void TcpConnection::Connect(bool is_primary) {
    auto endpt{ endpt_ };
    if (!is_primary && !endpt2_.address().is_unspecified()) {
        endpt = endpt2_;
    }

    Logger::Log()->info("TCP{} Connecting to {}:{}...", id_, endpt.address(), endpt.port());

    skt_.async_connect(endpt,
        [this](const error_code& ec) {
            if (ec) {
                Logger::Log()->error("TCP{} failed to connect: {}-{}", id_, ec, system_error(ec).what());

                if (retry_times_ <= 3) {
                    Logger::Log()->info("TCP{} Trying to reconnect...", id_);
                    Connect(retry_times_ % 2 == 0);
                    ++retry_times_;
                    this_thread::sleep_for(3s);
                }

                return;
            }

            Logger::Log()->info("TCP{} connected successfully", id_);
            is_connected_ = true;
            retry_times_ = 0;

            upper_layer_->Login();
            Receive();
        }
    );
}

void TcpConnection::Disconnect() {
    Logger::Log()->warn("[{}:{}] TCP{} disconnected", __func__, __LINE__, id_);

    is_connected_ = false;
    if (skt_.is_open()) {
        skt_.close();
    }
}

void TcpConnection::Send(const char* msg, size_t len) {
    if (len < 1) {
        Logger::Log()->warn("[{}:{}] TCP{} msg is empty", __func__, __LINE__, id_);
        return;
    }

    skt_.async_write_some(buffer(msg, len),
        [this](const error_code& ec, size_t length) {
            if (ec) {
                Logger::Log()->error("TCP{} write error : {}-{}", id_, ec, system_error(ec).what());
                return;
            }

            Logger::Log()->info("TCP{} sent successfully, len:{}.", id_, length);
        }
    );
}

void TcpConnection::Receive() {
    skt_.async_read_some(buffer(read_buf_, kReadLenMax),
        [this](const error_code& ec, size_t length) {
            if (ec) {
                is_connected_ = false;
                Logger::Log()->error("TCP{} Failed to read msg: {}-{}", id_, ec, system_error(ec).what());

                Connect();
                return;
            }

            //Logger::Log()->info("TCP{} msg received, len:{}", id_, length);
            Parse(read_buf_, (int)length);

            if (!is_connected_) {
                Logger::Log()->warn("TCP{} msg stop receiving", id_);
                return;
            }

            Receive();
        }
    );
}

// start from SoupbinTCP
bool TcpConnection::Parse(const char* msg, const int msg_len) {
    return upper_layer_->Parse(msg, msg_len);
}
