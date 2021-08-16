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

const string ConfigHelper::kConfigPath{ "/config/titan.json" };

// -----------------------------------------------------------------------------------------------;
// json functions
// -----------------------------------------------------------------------------------------------;
void from_json(const json& j, TitanAccount::ItchConfig& cfg) {
    j.at("Server").get_to(cfg.server);
    j.at("Port").get_to(cfg.port);
}

void from_json(const json& j, TitanAccount::GlimpseConfig& cfg) {
    j.at("Server").get_to(cfg.server);
    j.at("Port").get_to(cfg.port);
    j.at("UserID").get_to(cfg.ID);
    j.at("Password").get_to(cfg.password);
    j.at("Heartbeat").get_to(cfg.heartbeat);
}

void from_json(const json& j, TitanAccount::OuchConfig& cfg) {
    j.at("Server").get_to(cfg.server);
    j.at("Port").get_to(cfg.port);
    j.at("Server2").get_to(cfg.server2);
    j.at("Port2").get_to(cfg.port2);
    j.at("UserID").get_to(cfg.ID);
    j.at("Password").get_to(cfg.password);
    j.at("Account").get_to(cfg.account);
    j.at("CustomerInfo").get_to(cfg.customer_info);
    j.at("Heartbeat").get_to(cfg.heartbeat);
}

void from_json(const json& j, TitanAccount::OMnetConfig& cfg) {
    j.at("Server").get_to(cfg.server);
    j.at("Port").get_to(cfg.port);
    //j.at("UserID").get_to(cfg.ID);
    //j.at("Password").get_to(cfg.password);
}

void from_json(const json& j, TitanAccount& cfg) {
    j.at("ItchCfg").get_to(cfg.itch);
    j.at("GlimpseCfg").get_to(cfg.glipmse);
    j.at("OuchCfg").get_to(cfg.ouch);
    j.at("OMnetCfg").get_to(cfg.omnet);
}

void from_json(const json& j, ProductConfig& cfg) {
    j.at("Name").get_to(cfg.name);
    j.at("Contracts").get_to<std::set<std::string>>(cfg.contracts);
}

void from_json(const json& j, ExchangeConfig& cfg) {
    j.at("Enabled").get_to(cfg.is_enabled);
    j.at("Market").get_to(cfg.market);
    j.at("Type").get_to(cfg.type);
    j.at("Products").get_to<std::vector<ProductConfig>>(cfg.products);
}

void from_json(const json& j, TitanConfig& cfg) {
    j.at("StreamDataServer").get_to(cfg.md_stream_server);
    j.at("StreamTradeServer").get_to(cfg.td_stream_server);
    j.at("Account").get_to(cfg.account);
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

        config = json::parse(data).get<TitanConfig>();

        Logger::Log()->info("Setting log level: {}", config.log_level);
        Logger::SetLevel(config.log_level);

        return true;
    }
    catch (exception& e) {
        Logger::Log()->error("[{}:{}] Failed to init Titan config. {}", __func__, __LINE__, e.what());
        return false;
    }
}
