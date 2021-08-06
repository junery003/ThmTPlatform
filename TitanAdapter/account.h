//-----------------------------------------------------------------------------
// File Name   : account.h
// Author      : junlei
// Date        : 11/15/2020 12:05:03 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

#include <string>

struct TitanAccount {
    struct ItchConfig {
        std::string server;
        int port{ -1 };
        //std::string ID;
        //std::string password;
    } itch;

    struct GlimpseConfig {
        std::string server;
        int port{ -1 };
        std::string ID;
        std::string password;
        int heartbeat{ 15 }; // in seconds
    } glipmse;

    struct OuchConfig {
        std::string server;
        int port{ -1 };
        std::string server2; // fault redundancy
        int port2{ -1 };     // fault redundancy
        std::string ID;
        std::string password;
        std::string account;
        std::string customer_info;
        int heartbeat{ 15 };
    } ouch;

    struct OMnetConfig {
        std::string server;
        int port{ -1 };
        //std::string ID;
        //std::string password;
    } omnet;
};

#endif //!__ACCOUNT_H__