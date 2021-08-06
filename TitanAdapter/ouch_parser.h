//-----------------------------------------------------------------------------
// File Name   : ouch_parser.h
// Author      : junlei
// Date        : 11/5/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __OUCH_PARSER_H__
#define __OUCH_PARSER_H__

#include "ouch_msgs.h"
#include "soup_bin_tcp_parser.h"
#include "zmq_helper.h"

using namespace ouch_msg;

class OuchParser : public ProtocolBase {
public:
    OuchParser(std::shared_ptr<ZmqHelper> td_zmq)
        : td_zmq_(td_zmq) {
    }

public:
    bool Start() override;
    void Stop() override {
        lower_layer_->Stop();
    }

    // ------------------------------------------------------------------------------------------------;
    // inbound messages:  client --> server
    //void EnterOrder(EntryOrderMsg* msg);
    //void ReplaceOrder(ReplaceOrderMsg* msg);
    //void CancelOrder(CancelOrderMsg* msg);
    //void CancelOrderByID(CancelByOrderIDMsg* msg);

public:
    bool Parse(const char* msg, const int msg_len) override;
    void SetUpperLayer(std::shared_ptr<ProtocolBase> upper_layer) override {}
    void SetLowerLayer(std::shared_ptr<ProtocolBase> lower_layer) override {
        lower_layer_ = std::dynamic_pointer_cast<SoupBinTcpParser>(lower_layer);
    }

    void UnsequencedData(const char* data, const uint16_t data_len) {
        lower_layer_->UnsequencedData(data, data_len);
    }

private:
    // ------------------------------------------------------------------------------------------------;
    // outbound messages
    void OrderAccepted(const char* msg);
    void OrderRejected(const char* msg);
    void OrderReplaced(const char* msg);
    void OrderCanceled(const char* msg);
    void OrderExecuted(const char* msg);

private:
    inline static std::string ParseOrderState(uint8_t state) {
        switch (state) {
        case 1:  return "New";
        case 2:  return "Accepted";
        case 4:  return "Inactive";
        case 99: return "Ownership Lost";
        default: return "Undefined";
        }
    }

    inline static std::string ParseOrderType(char type) {
        switch (type) {
        case 'Y': return "Limit";
        case 'H': return "Half Tick";
        default:  return "Undefined";
        }
    }

private:
    std::shared_ptr<ZmqHelper> td_zmq_;

    std::shared_ptr<SoupBinTcpParser> lower_layer_;
};

#endif // !__OUCH_PARSER_H__
