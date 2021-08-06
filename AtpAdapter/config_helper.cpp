//-----------------------------------------------------------------------------
// File Name   : config_helper.cpp
// Author      : junlei
// Date        : 12/11/2020 10:02:26 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "config_helper.h"
#include "nlohmann/json.hpp"
#include "logger.h"

#include <fstream>
#include <filesystem>
#include <streambuf>

using json = nlohmann::json;
using namespace std;

const string ConfigHelper::kConfigPath{ "/config/atp.json" };

// -----------------------------------------------------------------------------------------------;
// json functions
// -----------------------------------------------------------------------------------------------;

void from_json(const json& j, AtpAccount& cfg) {
    j.at("MDServer").get_to(cfg.md_server);
    j.at("TradeServer").get_to(cfg.trade_server);
}

void from_json(const json& j, ExchangeConfig& cfg) {
    j.at("Enabled").get_to(cfg.is_enabled);
    j.at("Market").get_to(cfg.market);
    j.at("Type").get_to(cfg.type);
    j.at("Contracts").get_to<std::set<std::string>>(cfg.contracts);
}

void from_json(const json& j, AtpConfig& cfg) {
    j.at("StreamDataServer").get_to(cfg.md_stream_server);
    j.at("StreamTradeServer").get_to(cfg.td_stream_server);
    j.at("Acount").get_to(cfg.acount);
    j.at("Exchanges").get_to<std::vector<ExchangeConfig>>(cfg.exchanges);
    j.at("LogLevel").get_to(cfg.log_level);
}

// -----------------------------------------------------------------------------------------------;
bool ConfigHelper::Load() {
    try {
        auto path{ filesystem::current_path() };
        path += kConfigPath;

        Logger::Log()->info("====================================================================");
        Logger::Log()->info("Titan Init...\r\n[{}:{}] Init config file: {}", __func__, __LINE__, path);

        fstream fs(path);
        string data((istreambuf_iterator<char>(fs)), istreambuf_iterator<char>());

        config = json::parse(data).get<AtpConfig>();

        Logger::Log()->info("Setting log level: {}", config.log_level);
        Logger::SetLevel(config.log_level);

        return true;
    }
    catch (exception& e) {
        Logger::Log()->error("[{}:{}] Failed to init Titan config. {}", __func__, __LINE__, e.what());
        return false;
    }
}
