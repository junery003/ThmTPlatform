//-----------------------------------------------------------------------------
// File Name   : protocol_base.h
// Author      : junlei
// Date        : 11/5/2020 10:02:26 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __PROTOCOL_BASE_H__
#define __PROTOCOL_BASE_H__

#include "dt_utils.h"
#include "client_base.h"

#include <string>
#include <memory>

class ProtocolBase : public ClientBase {
public:
    virtual ~ProtocolBase() = default;

    virtual void SetUpperLayer(std::shared_ptr<ProtocolBase> upper_layer) = 0;
    virtual void SetLowerLayer(std::shared_ptr<ProtocolBase> lower_layer) = 0;

    // msg and its len; return successfully if msg len is correct
    virtual bool Parse(const char* msg, const int msg_len) = 0;

    virtual void Login() {}
    virtual void SetConnection(bool is_connected) {}
    virtual void SetInitSeqNumber(uint64_t seq_num) {}

public:
    inline static OrderSide GetSide(char side) {
        switch (side) {
        case 'B':
            return OrderSide::BUY;
        case 'S':
            return OrderSide::SELL;
        default: // should not happen        
            return OrderSide::UNKNOWN;
        }
    }

    // format left field with padding space(' ')
    inline static void FormatFieldLeftPadding(char* dst, const char* src, int dst_len, char padding = ' ') {
        int src_len = (int)strlen(src);
        for (int i = dst_len - 1, j = src_len - 1; i >= 0 || j >= 0; --i) {
            if (j >= 0) {
                dst[i] = src[j];
                --j;
            }
            else {
                dst[i] = padding;
            }
        }
    }

    inline static std::string ParseFieldRightPadding(const char* src, int src_len) {
        for (int idx = src_len - 1; idx >= 0; --idx) {
            if (src[idx] != ' ' && src[idx] != '\0') {
                return std::string(src, (size_t)idx + 1);
            }
        }

        return "";
    }

protected:
    enum {
        kReadLenMax = 1024 * 128,
        kWriteLenMax = 1024 * 8
    };
};

#endif // !__PROTOCOL_BASE_H__
