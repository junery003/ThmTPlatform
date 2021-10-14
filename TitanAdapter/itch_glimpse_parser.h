//-----------------------------------------------------------------------------
// File Name   : itch_glimpse_parser.h
// Author      : junlei
// Date        : 11/5/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __ITCHGLIMPSE_PARSER_H__
#define __ITCHGLIMPSE_PARSER_H__

#include "itch_glimpse_msgs.h"
#include "protocol_base.h"
#include "zmq_helper.h"

#include <string>
#include <memory>

using namespace itch_msg;

class ItchGlimpseParser : public ProtocolBase {
public:
    ItchGlimpseParser(std::shared_ptr<ZmqHelper> md_zmq)
        : md_zmq_(md_zmq) {
    }

public:
    void SetUpperLayer(std::shared_ptr<ProtocolBase> upper_layer) override {}
    void SetLowerLayer(std::shared_ptr<ProtocolBase> lower_layer) override {
        lower_layer_ = lower_layer;
    }

    bool Start() override;
    void Stop() override;

    bool Parse(const char* msg, const int msg_len) override;

    inline void SetInitSeqNumber(uint64_t seq_num) {
        //sequence_num_ = seq_num;
        lower_layer_->SetInitSeqNumber(seq_num);
    }
    inline uint64_t GetSeqNumber() const {
        return sequence_num_;
    }

private:
    // market by order msgs
    bool AddOrder(const char* msg, const int msg_len);
    bool OrderExecutedWPrice(const char* msg, const int msg_len); // order executed with Price
    bool OrderDelete(const char* msg, const int msg_len);
    bool OrderExecuted(const char* msg, const int msg_len);
    bool OrderReplace(const char* msg, const int msg_len); // no use

    bool OrderBookDirectory(const char* msg, const int msg_len);
    bool CombinationOrderBookLeg(const char* msg, const int msg_len);
    bool TickSize(const char* msg, const int msg_len);

    bool Seconds(const char* msg, const int msg_len);
    bool SystemEvent(const char* msg, const int msg_len);
    bool OrderBookState(const char* msg, const int msg_len);

    bool TradeMessageIdentifier(const char* msg, const int msg_len);
    bool EquilibriumPriceUpdate(const char* msg, const int msg_len);

    // glimpse only
    bool EndOfSnapshot(const char* msg, const int msg_len);

private:
    std::shared_ptr<ZmqHelper> md_zmq_;
    std::string cur_time_; // every second will udpate the time
    uint64_t sequence_num_{ 1 };

    std::shared_ptr<ProtocolBase> lower_layer_;
};

#endif // !__ITCHGLIMPSE_PARSER_H__
