//-----------------------------------------------------------------------------
// File Name   : zmq_helper.h
// Author      : junlei
// Date        : 9/11/2020 9:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __ZMQ_HELPER_H__
#define __ZMQ_HELPER_H__

#include "logger.h"
#include "zmq.hpp"

class ZmqHelper {
public:
    ZmqHelper(const std::string& server, int cntxt = 1)
        : contxt_(cntxt)
        , socket_(std::make_unique<zmq::socket_t>(contxt_, ZMQ_PAIR)) {
        Logger::Log()->info("[{}:{}] ZQM Connecting: {}", __func__, __LINE__, server);
        socket_->connect(server);
    }

public:
    inline void Send(const std::string& msg) {
        socket_->send(zmq::message_t(msg.data(), msg.size()), zmq::send_flags::none);
    }

private:
    zmq::context_t contxt_;
    std::unique_ptr<zmq::socket_t> socket_;
};

#endif //!__ZMQ_HELPER_H__
