//-----------------------------------------------------------------------------
// File Name   : trade_handler.cpp
// Author      : junlei
// Date        : 1/22/2021 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "trade_handler.h"

bool TradeHanlder::Start() {
    if (!ouch_client_->Start()) {
        return false;
    }

    is_stopped_ = false;
    io_contxt_.run();
    is_stopped_ = true;

    return true;
}
