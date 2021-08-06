//-----------------------------------------------------------------------------
// File Name   : time_utils.h
// Author      : junlei
// Date        : 11/15/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

#ifndef __TIME_UTILS_HPP__
#define __TIME_UTILS_HPP__

#include <chrono>
#include <sstream>
#include <iomanip>

class TimeUtils {
public:
    inline static std::string FromUnixTime(const time_t second) {
        std::tm t;
        gmtime_s(&t, &second);

        char buffer[50]{ 0 };
        strftime(buffer, sizeof buffer, "%F %T", &t);
        return buffer;
    }

    inline static std::string FromNanoSecond(uint64_t nanoseconds) {
        const static auto ratio = (uint32_t)pow(10, 9);

        //#include <format>
        //return std::format("{}.{:09}", FromUnixTime(nanoseconds / ratio), nanoseconds % ratio);

        std::stringstream ss;
        ss << FromUnixTime(nanoseconds / ratio) << "." << std::setfill('0') << std::setw(9) << nanoseconds % ratio;
        return ss.str();
    }

    inline static std::string GetNow() {
        auto now{ std::chrono::system_clock::now() };
        return FromNanoSecond(std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count());
    }
};

#endif // !__TIME_UTILS_HPP__
