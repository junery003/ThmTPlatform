//-----------------------------------------------------------------------------
// File Name   : config_helper.h
// Author      : junlei
// Date        : 12/11/2020 10:02:26 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __CONFIG_HELPER_H__
#define __CONFIG_HELPER_H__

#include "account.h"

#include <set>
#include <vector>

struct ExchangeConfig {
    bool is_enabled{ true };
    std::string market{ "SGX" };
    std::string type{ "Future" };
    std::set<std::string> contracts;
};

struct TitanConfig {
    std::string md_stream_server;
    std::string td_stream_server;
    TitanAccount account;
    std::vector<ExchangeConfig> exchanges;
    int log_level{ 1 };
};

struct ConfigHelper {
    TitanConfig config;
    bool Load();

private:
    static const std::string kConfigPath;
};

#endif // !__CONFIG_HELPER_H__
