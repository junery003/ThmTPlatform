//-----------------------------------------------------------------------------
// File Name   : logger.cpp
// Author      : junlei
// Date        : 11/17/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "logger.h"

#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

using namespace std;

Logger::Logger() {
    spdlog::level::level_enum lvl{ spdlog::level::info };

    auto console_sink = make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(lvl);
    //console_sink->set_pattern("[atp] [%^%l%$] %v");

    auto file_sink = make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/atp.log", 1048576 * 20, 10);
    file_sink->set_level(lvl);

    log_ = std::make_shared<spdlog::logger>("atp", spdlog::sinks_init_list{ console_sink , file_sink });
    log_->flush_on(lvl);
}

void Logger::SetLevel(int lvl) {
    switch (lvl) {
    case 0:
        Log()->set_level(spdlog::level::off);
        return;
    case 2:
        Log()->set_level(spdlog::level::debug);
        return;
    case 3:
        Log()->set_level(spdlog::level::warn);
        return;
    case 4:
        Log()->set_level(spdlog::level::err);
        return;
    case 5:
        Log()->set_level(spdlog::level::critical);
        return;
    case 1:
    default:
        Log()->set_level(spdlog::level::info);
        return;
    }
}