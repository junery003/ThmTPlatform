//-----------------------------------------------------------------------------
// File Name   : soup_bin_tcp_msgs.h
// Author      : junlei
// Date        : 11/5/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __SOUPBIN_TCP_MSGS_H__
#define __SOUPBIN_TCP_MSGS_H__

#include "dt_utils.h"
#include <string>

/*
Logical Packets Sent by a SoupBinTCP Server:
Code    Packet type
  A     Login Accepted
  H     Server Heartbeat
  J     Login Rejected
  S     Sequenced Data Packed
  Z     End of session

Logical Packets Sent by a SoupBinTCP Client
Code    Packet type
  L     Login Request
  O     Logout Request
  R     Client Heartbeat
  U     Unsequenced Data Packet
*/

//#pragma pack(1)
#pragma pack(push, 1)

struct DebugPkt {
    uint16_t length{ 0 };
    char type{ '+' };
    char* text;
};

struct LoginAcceptedPkt {
    uint16_t length{ 0 };
    char type{ 'A' };//
    char session[10];
    char sequence_number[20]; //
};

struct LoginRejectedPkt {
    uint16_t length{ 0 };
    char type{ 'J' };//
    /*  "A": Not Authorized. There was an invalid username and password combination in the Login Request message
        "S": session not available. The Requested session in the Login Request Packet was either invalid or not available
    */
    char reason_code;

    std::string RejectReason() {
        switch (reason_code) {
            case 'A':
                return "Not Authorized";
            case 'S':
                return "Session not available";
            default:
                return "unknown reason";
        }
    }
};

struct SequencedDataPkt {
    uint16_t length{ 0 };
    char type{ 'S' }; // sequenced data packed
    char* message;
};

struct ServerHeartbeatPkt {
    uint16_t length{ 0 };
    char type{ 'H' };
};

struct EndOfSessionPkt {
    uint16_t length{ 0 };
    char type{ 'Z' };
};

struct LoginReqPkt {
    uint16_t length{ 0 };
    char type{ 'L' };//
    char user_name[6];
    char password[10]; //
    char requested_session[10];   // Alphanumeric
    char requested_sequence_number[20]; //Numeric

    LoginReqPkt() {
        memset(user_name, ' ', sizeof(user_name));
        memset(password, ' ', sizeof(password));
        memset(requested_session, ' ', sizeof(requested_session));
        memset(requested_sequence_number, ' ', sizeof(requested_sequence_number));
    }
};

struct UnsequencedDataPkt {
    uint16_t length{ 0 };
    char type{ 'U' };
    char* message;
};

struct ClientHeartbeatPkt {
    uint16_t length{ 1 };
    char type{ 'R' };
};

struct LogoutReqPkt {
    uint16_t length{ 1 };
    char type{ 'O' };
};
#pragma pack(pop)

#endif // !__SOUPBIN_TCP_MSGS_H__
