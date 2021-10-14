//-----------------------------------------------------------------------------
// File Name   : mold_udp64_parser.cpp
// Author      : junlei
// Date        : 11/18/2020 10:02:26 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "mold_udp64_msgs.h"
#include "mold_udp64_parser.h"
#include "logger.h"

#include <WinSock2.h>

using namespace std;

bool MoldUdp64Parser::Parse(const char* msg, const int msg_len) {
    MoldUDP64Header* header = (MoldUDP64Header*)msg;

    auto cur_seq_num = ntohll(header->sequence_num);
    if (is_init_conn_) {
        is_init_conn_ = false;
        if (init_seq_num_ != cur_seq_num) {
            Logger::Log()->warn("[{}:{}] session:{}, seqNum gap: {}={}-{}", __func__, __LINE__,
                header->session, cur_seq_num - init_seq_num_, cur_seq_num, init_seq_num_);
            Request(header->session, init_seq_num_, (uint16_t)(cur_seq_num - init_seq_num_));
        }
    }

    const auto msg_count = ntohs(header->message_count);
    switch (msg_count) {
        case 0: { // heartbeat
        //Logger::Log()->info("[{}:{}] MoldUDP64-Heartbeat, sequenceNum:{}", __func__, __LINE__, cur_seq_num);
        break;
    }
        case 0xFFFF: { // end of session
        Logger::Log()->info("[{}:{}] MoldUDP64-End of session, sequenceNum:{}", __func__, __LINE__, cur_seq_num);
        break;
    }
        default: { // message block        
        //Logger::Log()->info("[{}:{}] MoldUDP64-Message block, seqNum:{}, msg count:{}, session:{}", __func__, __LINE__, cur_seq_num, msg_count, header->session);

        const static auto header_len = sizeof(*header);
        msg += header_len; // 20
        int left_len = msg_len - header_len;
        if (left_len <= 0) {
            Logger::Log()->error("[{}:{}] msg length:{}, count:{}", __func__, __LINE__, msg_len, msg_count);
            return false;
        }

        for (int i = 0; i < msg_count; ++i) {
            uint16_t len = *((uint16_t*)msg);  // message length
            len = ntohs(len);
            msg += 2;

            upper_layer_->Parse(msg, len); // message data
            msg += len;
        }

        break;
    }
    }

    return true;
}

void MoldUdp64Parser::Request(const char* sess, uint64_t seq_num, uint16_t count) {
    Logger::Log()->info("[{}:{}] MoldUDP64-msg session:{}, seqNum:{}, count:{}",
        __func__, __LINE__, sess, seq_num, count);

    RequestPkt pkg;
    FormatFieldLeftPadding(pkg.session, sess, sizeof(pkg.session)); // ' ' 
    pkg.sequence_num = htonll(seq_num);
    pkg.requested_message_count = htons(count);

    static auto len = sizeof(pkg);

    memcpy(write_buf_, (char*)&pkg, len);

    conn_->Send(write_buf_, len);
}

void MoldUdp64Parser::SetInitSeqNumber(uint64_t seq_num) {
    Logger::Log()->info("[{}:{}] seqNum:{}", __func__, __LINE__, seq_num);
    init_seq_num_ = seq_num;
}
