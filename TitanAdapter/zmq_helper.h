//-----------------------------------------------------------------------------
// File Name   : zmq_helper.h
// Author      : junlei
// Date        : 11/23/2020 11:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __ZMQ_HELPER_H__
#define __ZMQ_HELPER_H__

#include "zmq.hpp"
#include <string>
#include <memory>

class ZmqHelper {
public:
    ZmqHelper(const std::string& server, int cntxt = 1);

public:
    inline void Send(const std::string& msg) {
        socket_->send(zmq::message_t(msg.data(), msg.size()), zmq::send_flags::none);
    }

private:
    zmq::context_t contxt_;
    std::unique_ptr<zmq::socket_t> socket_;
};

#endif // !__ZMQ_HELPER_H__
