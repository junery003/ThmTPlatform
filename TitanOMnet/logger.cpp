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

Logger::Logger() {
    spdlog::level::level_enum lvl{ spdlog::level::info };

    // normal log
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(lvl);  // console_sink->set_pattern("[atp] [%^%l%$] %v");

    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/omnet.log", 1048576 * 30, 10);
    file_sink->set_level(lvl);

    log_ = std::make_shared<spdlog::logger>("omnet", spdlog::sinks_init_list{ console_sink , file_sink });
    log_->flush_on(lvl);
}
