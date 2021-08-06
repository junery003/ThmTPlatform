//-----------------------------------------------------------------------------
// File Name   : mold_udp64_parser.h
// Author      : junlei
// Date        : 11/18/2020 10:02:26 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __MOLDUDP64_PARSER_H__
#define __MOLDUDP64_PARSER_H__

#include "protocol_base.h"
#include "udp_connection.h"

#include <string>
#include <memory>

// MoldUDP64 can theoretically handle individual messages from zero bytes up to 64KB in length
class MoldUdp64Parser : public ProtocolBase, public std::enable_shared_from_this<MoldUdp64Parser> {
public:
    MoldUdp64Parser() {}

public:
    void SetUpperLayer(std::shared_ptr<ProtocolBase> upper_layer) override {
        upper_layer_ = upper_layer;
        upper_layer->SetLowerLayer(shared_from_this());
    }
    void SetLowerLayer(std::shared_ptr<ProtocolBase> lower_layer) override {
        conn_ = std::dynamic_pointer_cast<UdpConnection>(lower_layer);
        lower_layer->SetUpperLayer(shared_from_this());
    }

    bool Start() override {
        conn_->Start();
        return true;
    }
    void Stop() override {
        conn_->Stop();
    }

    void SetInitSeqNumber(uint64_t seq_num) override;
    bool Parse(const char* msg, const int msg_len) override;

private:
    void Request(const char* sess, uint64_t seq_num, uint16_t count);  // data and its length

private:
    //std::string cur_session_;
    uint64_t init_seq_num_{ 0 }; //indicates the sequence number of the first message in the packet
    bool is_init_conn_{ true };

    std::shared_ptr<ProtocolBase> upper_layer_;
    std::shared_ptr<UdpConnection> conn_;

    char write_buf_[kWriteLenMax]{ 0 };
};

#endif  //!__MOLDUDP64_PARSER_H__
