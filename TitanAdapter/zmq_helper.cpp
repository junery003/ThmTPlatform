//-----------------------------------------------------------------------------
// File Name   : zmq_helper.h
// Author      : junlei
// Date        : 11/23/2020 11:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "zmq_helper.h"

#include "logger.h"

ZmqHelper::ZmqHelper(const std::string& server, int cntxt)
    : contxt_(cntxt)
    , socket_(std::make_unique<zmq::socket_t>(contxt_, ZMQ_PAIR)) {
    Logger::Log()->info("[{}:{}] ZMQ connecting: {}", __func__, __LINE__, server);
    socket_->connect(server);
}
