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
    bool Start() override;
    void Stop() override;
    bool Parse(const char* msg, const int msg_len) override;

    void SetUpperLayer(std::shared_ptr<ProtocolBase> upper_layer) override {}
    void SetLowerLayer(std::shared_ptr<ProtocolBase> lower_layer) override {
        lower_layer_ = lower_layer;
    }

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
    inline static std::string ParseFinancialProduct(char financial_product) {
        switch (financial_product) {
        case 1: return "Option";
        case 2: return "Forward";
        case 3: return "Future";
        case 4: return "FRA";
        case 5: return "Cash";
        case 6: return "Payment";
        case 7: return "Exchange Rate";
        case 8: return "Interest Rate Swap";
        case 9: return "REPO";
        case 10: return "Synthetic Box Leg/Reference";
        case 11: return "Standard Combination";
        case 12: return "Guarantee";
        case 13: return "OTC General";
        case 14: return "Equity Warrant";
        case 15: return "Security Lending";
        default: return "Not Supported";
        }
    }

    inline static std::string ParsePutOrCall(char put_or_call) {
        // Option type.Values:      
        switch (put_or_call) {
        case 1: return "Call";
        case 2: return "Put";
        case 0: return "Undefined";
        default: return "N/A";
        }
    }

private:
    std::shared_ptr<ZmqHelper> md_zmq_;
    std::string cur_time_; // every second will udpate the time
    uint64_t sequence_num_{ 1 };

    std::shared_ptr<ProtocolBase> lower_layer_;
};

#endif // !__ITCHGLIMPSE_PARSER_H__
