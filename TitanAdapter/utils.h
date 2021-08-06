//-----------------------------------------------------------------------------
// File Name   : utils.h
// Author      : junlei
// Date        : 11/15/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <random>
#include <algorithm>

class Utils {
public:
    static std::string GetUniqueStr(int len) {
        std::string chars{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890" };
        std::random_device rd;
        std::mt19937 generator(rd());
        std::shuffle(chars.begin(), chars.end(), generator);

        len = std::min(len, (int)chars.size());
        return chars.substr(0, len);
    }

    inline static char GetMonthCode(const char month) {
        switch (month) {
        case 1: return 'F';
        case 2: return 'G';
        case 3: return 'H';
        case 4: return 'J';
        case 5: return 'K';
        case 6: return 'M';
        case 7: return 'N';
        case 8: return 'Q';
        case 9: return 'U';
        case 10: return 'V';
        case 11: return 'X';
        case 12: return 'Z';
        default: return '\0';
        }
    }

    inline static char GetMonthByCode(const char code) {
        switch (code) {
        case 'F': return 1;
        case 'G': return 2;
        case 'H': return 3;
        case 'J': return 4;
        case 'K': return 5;
        case 'M': return 6;
        case 'N': return 7;
        case 'Q': return 8;
        case 'U': return 9;
        case 'V': return 10;
        case 'X': return 11;
        case 'Z': return 12;
        default: return '\0';
        }
    }
};

#endif // !__TIME_UTILS_H__
