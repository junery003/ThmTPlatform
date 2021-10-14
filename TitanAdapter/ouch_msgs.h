//-----------------------------------------------------------------------------
// File Name   : ouch_msgs.h
// Author      : junlei
// Date        : 11/5/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __OUCH_MSGS_H__
#define __OUCH_MSGS_H__

#include "dt_utils.h"
#include <string>

namespace ouch_msg {

    //#pragma pack(1)
#pragma pack(push, 1)

/*
The OUCH message protocol utilises the following code references :
  Code       Message Type
    A       Order Accepted
    C       Order Canceled
    E       Order Executed
    J       Order Rejected
    O       Enter Order
    U       Replace Order / Order Replaced
    X       Cancel Order
    Y       Cancel Order by ID
*/
//-------------------------------------------------------------------------------------------------;
// Inbound messages: client -->> server
//-------------------------------------------------------------------------------------------------;
    struct EnterOrderMsg {
        char type{ 'O' };
        char order_token[14]{ 0 };
        uint32_t order_book_id{ 0 };
        /*  B = Buy Order
            S = Sell Order
            T = Short sell (not in use)
        */
        char side{ 0 };
        uint64_t qty{ 0 };
        price_t price{ 0 };
        /*  0 = Day
            3 = Immediate or Cancel (FAK)
            4 = Fill or Kill
            */
        uint8_t time_in_force{ 0 };
        /*  0 = Default for the account
            1 = Open
            2 = Close/Net
            3 = Mandatory close
            */
        uint8_t open_close{ 0 };

        char client_account[16]{ 0 };
        char customer_info[15]{ 0 };
        char exchange_info[32]{ 0 };
        uint64_t display_qty{ 0 };
        uint16_t stp_key{ 0 };
        /*  H = Half Tick Order
            Y = Limit Order
            */
        char ouch_order_type{ 'Y' };
        char reserved[5]{ 0 };

        EnterOrderMsg(const char* token) {
            memset(order_token, ' ', sizeof(order_token));
            memcpy(order_token, token, strlen(token));

            memset(client_account, ' ', sizeof(client_account));
            memset(customer_info, ' ', sizeof(customer_info));
            memset(exchange_info, ' ', sizeof(exchange_info));
        }
    };

    struct ReplaceOrderMsg {
        char type{ 'U' };
        char existing_order_token[14];
        char replacement_order_token[14];
        uint64_t qty{ 0 };
        price_t price{ 0 };  // 0 means "no change"
        /*  0 = Default for the account
            1 = Open
            2 = Close/Net
            3 = Mandatory close
            4 = Default for the account
            */
        uint8_t open_close{ '\0' }; // '\0' means "no change"
        char client_account[16]{ 0 };
        char customer_info[15]{ 0 };
        char exchange_info[32]{ 0 };
        uint64_t display_qty{ 0 };
        uint16_t stp_key{ 0 };
        char reserved[6]{ 0 };

        ReplaceOrderMsg(const char* existing_token, const char* token) {
            memset(existing_order_token, ' ', sizeof(existing_order_token));
            memcpy(existing_order_token, existing_token, strlen(existing_token));

            memset(replacement_order_token, ' ', sizeof(replacement_order_token));
            memcpy(replacement_order_token, token, strlen(token));

            memset(client_account, ' ', sizeof(client_account));
            memset(customer_info, ' ', sizeof(customer_info));
            memset(exchange_info, ' ', sizeof(exchange_info));
        }
    };

    struct CancelOrderMsg {
        char type{ 'X' };
        char order_token[14];  //Should be the Order Token from the original Enter Order

        CancelOrderMsg(const char* token) {
            memset(order_token, ' ', sizeof(order_token));
            memcpy(order_token, token, strlen(token));
        }
    };

    struct CancelByOrderIDMsg {
        char type{ 'Y' };
        uint32_t order_book_id{ 0 };
        /* B = Buy order
           S = Sell order
           */
        char side;
        uint64_t order_id{ 0 };

        CancelByOrderIDMsg(char buy_sell) : side(buy_sell) {
        }
    };

    //-------------------------------------------------------------------------------------------------;
    // Outbound messages: server -->> Client
    //-------------------------------------------------------------------------------------------------;
    struct OrderAcceptedMsg {
        char type{ 'A' };
        timestamp_t timestamp_nanoseconds{ 0 };
        char order_token[14];
        uint32_t order_book_id;
        char side;
        uint64_t order_id;
        uint64_t qty{ 0 };
        price_t price{ 0 };

        /*Values:
            0 = Day
            3 = Immediate or Cancel
            4 = Fill or Kill
            */
        uint8_t time_in_force;

        /*Defines the position update for the account
            Values:
            0 = No change
            1 = Open
            2 = Close/Net
            3 = Mandatory close
            4 = Default for the account
            */
        uint8_t open_close;

        char client_account[16];
        /*  1 = On book
            2 = Not on book
            4 = Inactive (due to price limit constraints)
        */
        uint8_t order_state;
        char customer_info[15];
        char exchange_info[32];
        uint64_t pretrade_qty{ 0 };
        uint64_t display_qty{ 0 };
        uint16_t stp_key{ 0 };
        /*  H = Half Tick Order
            Y = Limit Order
            */
        char ouch_order_type;
        char reserved[3];
    };

    struct OrderRejectedMsg {
        char type{ 'J' };
        timestamp_t timestamp_nanoseconds{ 0 };
        char order_token[14];
        int32_t reject_code;
    };

    struct OrderReplacedMsg {
        char type{ 'U' };
        timestamp_t timestamp_nanoseconds{ 0 };
        char replacement_order_token[14];
        char previous_order_token[14];
        uint32_t order_book_id;
        char side;
        uint64_t order_id;
        uint64_t qty{ 0 };
        /* Signed integer price
            Note : Number of decimals is given by the Order book Directory message in ITCH.
            This field also tells if the security is traded in fractions
            */
        price_t price{ 0 };
        /*  0 = Day
            3 = Immediate or Cancel
            4 = Fill or Kill
            */
        uint8_t time_in_force;
        /*  0 = No change
            1 = Open
            2 = Close/Net
            3 = Mandatory close
            4 = Default for the account
            */
        uint8_t open_close;
        char client_account[16];
        /*  1 = On book
            2 = Not on book
            4 = Inactive (due to price limit constraints)
            99 = OUCH order ownership lost
        */
        uint8_t order_state;

        char customer_info[15]{ 0 };
        char exchange_info[32]{ 0 };
        uint64_t pretrade_qty{ 0 };
        uint64_t display_qty{ 0 };
        uint16_t stp_key{ 0 };
        char reserved[2]{ 0 };
    };

    struct OrderCanceledMsg {
        char type{ 'C' };
        timestamp_t timestamp_nanoseconds{ 0 };
        char order_token[14]{ 0 };
        uint32_t order_book_id;
        char side;
        uint64_t order_id;
        char reason;

        std::string FormatReason() {
            switch (reason) {
            case 1:  return "Canceled by user";
            case 4:  return "Order inactivated";
            case 9:  return "Canceled by system";
            case 10: return "Canceled by proxy";
            case 15: return "Canceled due to price Limit change";
            case 19: return "Order Canceled by central system Order removed or changed by remove day or date orders flag";
            case 21: return "Inactivated due to ISS change";
            case 34: return "Canceled during Auction";
            case 42: return "Order deleted because trader is not allowed to trade with himself";
            default: return "Not supported:" + reason;
            }
        }
    };

    struct OrderExecutedMsg {
        char type{ 'E' };
        timestamp_t timestamp_nanoseconds{ 0 };
        char order_token[14];
        uint32_t order_book_id;
        uint64_t traded_qty{ 0 };
        price_t trade_price{ 0 };

        //char match_id[12];  //Numeric 12 Bytes
        struct StruMatchID {
            uint64_t execution_number{ 0 };
            uint32_t match_group_number{ 0 };
        } match_id;

        char reserved[16];
    };

#pragma pack(pop)
}

#endif // !__OUCH_MSGS_H__
