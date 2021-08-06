//-----------------------------------------------------------------------------
// File Name   : logger.h
// Author      : junlei
// Date        : 11/17/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "spdlog/logger.h"
#include "spdlog/fmt/ostr.h"

#include <memory>

class Logger {
public:
    static std::shared_ptr<spdlog::logger> Log() {
        static Logger log;
        return log.log_;
    }

    static void SetLevel(int lvl);
private:
    Logger();
    ~Logger();

    Logger(const Logger& log) = delete;
    Logger& operator=(const Logger& log) = delete;

private:
    std::shared_ptr<spdlog::logger> log_;
};

#endif // !__LOGGER_H__
