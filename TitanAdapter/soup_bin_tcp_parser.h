//-----------------------------------------------------------------------------
// File Name   : soup_bin_tcp_parser.h
// Author      : junlei
// Date        : 11/5/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __SOUPBIN_TCP_PARSER_H__
#define __SOUPBIN_TCP_PARSER_H__

#include "protocol_base.h"
#include "soup_bin_tcp_msgs.h"
#include "tcp_connection.h"

#include "boost/asio.hpp"
#include <memory>
#include <string>

class SoupBinTcpParser : public ProtocolBase, public std::enable_shared_from_this<SoupBinTcpParser> {
public:
    SoupBinTcpParser(const std::string& user_name, const std::string& password, int heartbeat_interval)
        : user_name_(user_name)
        , password_(password)
        , heartbeat_interval_(heartbeat_interval) {
    }

    ~SoupBinTcpParser() {
        is_connected_ = false;
    }

public:
    void SetLowerLayer(std::shared_ptr<ProtocolBase> lower_layer) override {
        conn_ = std::dynamic_pointer_cast<TcpConnection>(lower_layer);
        lower_layer->SetUpperLayer(shared_from_this());
    }

    void SetUpperLayer(std::shared_ptr<ProtocolBase> upper_layer) override {
        upper_layer_ = upper_layer;
        upper_layer->SetLowerLayer(shared_from_this());
    }

public:
    bool Start() override {
        return conn_->Start();
    }
    void Stop() override {
        LogoutReq();
    }
    bool Parse(const char* msg, const int msg_len) override;

    void SetConnection(bool is_connected) override {
        is_connected_ = is_connected;
        conn_->SetConnection(is_connected_);
    }

    void Login() override {
        LoginReq();
    }

public: // to server
    void LoginReq();  //L
    void LogoutReq(); //O
    void Heartbeat(); //R
    void UnsequencedData(const char* data, const uint16_t data_len); //U

private: // from server
    void LoginAccepted(const char* msg);
    void LoginRejected(const char* msg);
    void SequencedData(const char* msg);
    void ServerHeartbeat(const char* msg);
    void EndOfSession(const char* msg);

    // msg_len, the rest length of the msg
    // return the actual length of the one msg parsed
    int ParseMsgs(const char* msg, int msg_len);

private:
    inline uint64_t NextSeqNum() { return ++sequence_num_; }
    void HeartbeatThread();

    void ResetElapse() {
        elapsed_seconds_ = 0;
    }

private:
    std::shared_ptr<ProtocolBase> upper_layer_;
    std::shared_ptr<TcpConnection> conn_;

    uint64_t sequence_num_{ 1 };

    std::string user_name_;
    std::string password_;

    bool is_connected_{ false };  // disconnected or end of session

    std::jthread heartbeat_thd_;
    int heartbeat_interval_{ 10 };
    int elapsed_seconds_{ 0 };

    char write_buf_[kWriteLenMax]{ 0 };
    boost::circular_buffer<char> cc_read_buf_{ kReadLenMax * 2 }; // for segmented msg
    char seg_tmp_buf_[kReadLenMax * 2]{ 0 };

    char heartbeat_write_buf_[20]{ 0 };
};

#endif // !__SOUPBIN_TCP_PARSER_H__
