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

#include <string>
#include <set>
#include <vector>

struct AtpAccount {
    std::string md_server;
    std::string trade_server;

    std::string broker_ID;
    std::string user_ID;
    std::string user_password;
    std::string investor_ID; // investorId is userId
    std::string app_ID;
    std::string auth_code;
    bool is_auth;
};

struct ProductConfig {
    std::string name;
    std::set<std::string> contracts;
};

struct ExchangeConfig {
    bool is_enabled{ true };
    std::string market;
    std::string type{ "Future" };
    std::vector<ProductConfig> products;
};

struct AtpConfig {
    std::string md_stream_server;
    std::string td_stream_server;
    AtpAccount account;
    std::vector<ExchangeConfig> exchanges;
    int log_level{ 1 };
};

struct ConfigHelper {
    AtpConfig config;
    bool Load();

private:
    static const std::string kConfigPath;
};

#endif // !__CONFIG_HELPER_H__
