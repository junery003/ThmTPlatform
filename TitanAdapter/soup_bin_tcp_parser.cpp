//-----------------------------------------------------------------------------
// File Name   : soup_bin_tcp_parser.h
// Author      : junlei
// Date        : 11/5/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "soup_bin_tcp_parser.h"
#include "logger.h"

#include <thread>
#include <memory>
#include <WinSock2.h>

using namespace std;

void SoupBinTcpParser::HeartbeatThread() {
    do {
        std::this_thread::sleep_for(1s);
        if (!is_connected_) {
            Logger::Log()->info("[{}:{}] SoupBinTCP-Heartbeat thread stops", __func__, __LINE__);
            break;
        }

        if (++elapsed_seconds_ > heartbeat_interval_) {
            Heartbeat();
            ResetElapse();
        }
    } while (true);
}

// L
void SoupBinTcpParser::LoginReq() {
    LoginReqPkt pkg;
    const static auto len = sizeof(pkg);

    Logger::Log()->info("[{}:{}] SoupBinTCP L: LoginReq: usr name:{}, pwd:{}, "
        "seq num:{}, requested_session: {}",
        __func__, __LINE__, user_name_, password_,
        sequence_num_, "");

    pkg.length = len - sizeof(pkg.length);
    pkg.length = htons(pkg.length);

    memcpy(pkg.user_name, user_name_.c_str(), user_name_.size());
    memcpy(pkg.password, password_.c_str(), password_.size());

    FormatFieldLeftPadding(pkg.requested_sequence_number, to_string(sequence_num_).c_str(),
        sizeof(pkg.requested_sequence_number));

    memcpy(write_buf_, (void*)&pkg, len);
    conn_->Send(write_buf_, len);

    heartbeat_thd_ = std::jthread{ &SoupBinTcpParser::HeartbeatThread, this };
}

// R:
void SoupBinTcpParser::Heartbeat() {
    //Logger::Log()->info("[{}:{}] SoupBinTCP R: Sending Heartbeat", __func__, __LINE__);
    ClientHeartbeatPkt pkg;
    const static auto len = sizeof(pkg);

    pkg.length = len - sizeof(pkg.length);
    pkg.length = htons(pkg.length);

    memcpy(heartbeat_write_buf_, (void*)&pkg, len);
    conn_->Send(heartbeat_write_buf_, len);
}

// O:
void SoupBinTcpParser::LogoutReq() {
    Logger::Log()->info("[{}:{}] SoupBinTCP O: Sending Logout", __func__, __LINE__);

    LogoutReqPkt pkg;
    const static auto len = sizeof(pkg);

    pkg.length = len - sizeof(pkg.length);
    pkg.length = htons(pkg.length);

    memcpy(write_buf_, (void*)&pkg, len);
    conn_->Send(write_buf_, len);

    SetConnection(false);
}

// U: client --> server
void SoupBinTcpParser::UnsequencedData(const char* data, const uint16_t data_len) {
    UnsequencedDataPkt pkg;
    pkg.length = htons(1 + data_len);

    static const uint16_t head_len = 3;
    memcpy(write_buf_, (char*)&pkg, head_len);
    memcpy(write_buf_ + head_len, data, data_len);

    conn_->Send(write_buf_, head_len + data_len);

    ResetElapse();
}

// -----------------------------------------------------------------------------------------------;
/* Logical Packets Sent by a SoupBinTCP Server
Code    Packet Type
A       Login Accepted
H       Server Heartbeat
J       Login Rejected
S       Sequenced Data Packed
Z       End of Session
*/
bool SoupBinTcpParser::Parse(const char* msg, const int msg_len) {
    if (msg_len < kReadLenMax && cc_read_buf_.empty()) {
        int left = ParseMsgs(msg, msg_len);
        if (left > 0) {
            cc_read_buf_.insert(cc_read_buf_.end(), msg + msg_len - left, msg + msg_len);
        }

        return true;
    }

    cc_read_buf_.insert(cc_read_buf_.end(), msg, msg + msg_len);
    copy(cc_read_buf_.begin(), cc_read_buf_.end(), seg_tmp_buf_);

    int total_len = (int)cc_read_buf_.size();
    int left_len = ParseMsgs(seg_tmp_buf_, total_len);
    cc_read_buf_.erase_begin(total_len - left_len);

    return true;
}

int SoupBinTcpParser::ParseMsgs(const char* msg, int msg_len) {
    while (msg_len > 0) {
        uint16_t len = ntohs(*((uint16_t*)msg)) + 2;
        if (len > msg_len) { // not enough for a msg
            //Logger::Log()->info("[{}:{}] SoupBinTCP-msg segmented: {}<{}", __func__, __LINE__, msg_len, len);
            return msg_len;
        }

        char type = *(msg + 2);
        //Logger::Log()->info("[{}:{}] SoupBinTCP msg type:'{}', len:{}", __func__, __LINE__, type, len);
        switch (type) {
        case 'A':
            LoginAccepted(msg);
            break;
        case 'H':
            ServerHeartbeat(msg);
            break;
        case 'J':
            LoginRejected(msg);
            break;
        case 'S': // a single higher-level protocol msg
            NextSeqNum();
            SequencedData(msg);
            break;
        case 'Z':
            EndOfSession(msg);
            break;
        default: // unrecognized
            Logger::Log()->warn("[{}:{}] Unrecognized SoupBinTCP msg type:'{}', len:{}, msg:'{}'",
                __func__, __LINE__, type, len, msg);
            return 0;
        }

        msg += len;
        msg_len -= len;
    }

    return 0;
}

// A:
void SoupBinTcpParser::LoginAccepted(const char* msg) {
    is_connected_ = true;

    LoginAcceptedPkt* pkt = (LoginAcceptedPkt*)msg;
    sequence_num_ = std::stoull(pkt->sequence_number);
    Logger::Log()->info("[{}:{}] SoupBinTCP A: Login accepted: seqNum:{}", __func__, __LINE__, sequence_num_);
}

// J
void SoupBinTcpParser::LoginRejected(const char* msg) {
    LoginRejectedPkt* pkt = (LoginRejectedPkt*)msg;
    Logger::Log()->info("[{}:{}] SoupBinTCP J: Login rejected code:{}", __func__, __LINE__, pkt->reason_code);
}

// S
void SoupBinTcpParser::SequencedData(const char* msg) {
    SequencedDataPkt* pkt = (SequencedDataPkt*)msg;
    pkt->length = ntohs(pkt->length);
    if (pkt->length < 3) { // special end of session maker
        Logger::Log()->info("[{}:{}] SoupBinTCP S: Sequenced data-special End of session: len:{}",
            __func__, __LINE__, pkt->length);
        return;
    }

    upper_layer_->Parse(msg + 3, pkt->length); // OUCH or Glimpse
}

// H:
void SoupBinTcpParser::ServerHeartbeat(const char* msg) {
    //Logger::Log()->info("[{}:{}] SoupBinTCP H: Server Hearbeat", __func__, __LINE__);
}

// Z:
void SoupBinTcpParser::EndOfSession(const char* msg) {
    Logger::Log()->info("[{}:{}] SoupBinTCP Z: End of session", __func__, __LINE__);
    //EndOfSessionPkt* pkg = (EndOfSessionPkt*)msg;
    //LogoutReqPkt pkg;
    //LogoutReq(pkg);

    //SetConnection(false);
    LogoutReq();
}
