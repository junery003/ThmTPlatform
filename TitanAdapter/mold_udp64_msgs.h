//-----------------------------------------------------------------------------
// File Name   : mold_udp64_msgs.h
// Author      : junlei
// Date        : 11/5/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __MOLD_UPD64_MSGS_H__
#define __MOLD_UPD64_MSGS_H__

#include "dt_utils.h"

//#pragma pack(1)
#pragma pack(push,1)

//-------------------------------------------------------------------------------------------------;
// Downstream Packet
//-------------------------------------------------------------------------------------------------;
struct MoldUDP64Header {
    char session[10]{ 0 };   // Indicates the session to which this packet belongs 
    uint64_t sequence_num{ 0 };  // The sequence number of the first message in the packet
    uint16_t message_count{ 0 }; // 0: hearbeat; 0xFFFF: end of session
}; // 20 bytes

struct MoldUDP64Body {
    uint16_t length{ 0 };  // can be 0
    char* data{ 0 };
};

//sent to request the retransmission of a particular message or group of messages
struct RequestPkt {
    char session[10]{ ' ' };
    uint64_t sequence_num{ 1 };  // The sequence number of the first message in the packet
    uint16_t requested_message_count{ 0 };  //The number of messages requested for retransmission
}; // 20 bytes

#pragma pack(pop)

#endif //!__MOLD_UPD64_MSGS_H__
