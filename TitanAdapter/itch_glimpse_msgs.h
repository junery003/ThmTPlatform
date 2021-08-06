//-----------------------------------------------------------------------------
// File Name   : itch_glimpse_msgs.h
// Author      : junlei
// Date        : 11/5/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __ITCH_GLIMPSE_MSGS_H__
#define __ITCH_GLIMPSE_MSGS_H__

#include "dt_utils.h"
#include <string>

namespace itch_msg {

    //#pragma pack(1)
#pragma pack(push, 1)

// ------------------------------------------------------------------------------------------------;
// ITCH
// ------------------------------------------------------------------------------------------------;
/*
Code  message type
  A     Add Order
  C     Order Executed
  D     Order Delete
  E     Order Executed
  L     Tick Size
  M     Combination Order Book Directory
  O     Order Book State
  P     Trade message Identifier
  R     Order Book Directory
  S     System Event
  T     Seconds
  U     Order Replace
  Z     Equilibrium price Update
*/
    struct SecondMsg {
        char type{ 'T' }; //
        uint32_t second{ 0 }; // Unix time(number of seconds since the start of 1970-01-01 00:00:00 UTC)
    };

    struct OrderBookDirectoryMsg {
        char type{ 'R' };
        uint32_t timestamp_nanoseconds{ 0 };  //Nanoseconds portion of the timestamp
        uint32_t order_book_id{ 0 };
        char symbol[32];
        char long_name[32];
        char ISIN[12];
        char financial_product;
        char currency[3];
        uint16_t decimal_num_in_price{ 0 }; //
        uint16_t decimal_num_in_nominal_value{ 0 };
        uint32_t odd_lot_size{ 0 };
        uint32_t round_lot_size{ 0 };
        uint32_t block_lot_size{ 0 };
        uint64_t nominal_value{ 0 };
        char leg_num{ 0 };
        uint32_t commodity_code;
        price_t strike_price{ 0 }; // 4
        date_t expiration_date; // 4 Only applicable for derivative instruments except for combinations.
        uint16_t decimal_num_in_strike_price{ 0 }; // 2
        // 1: Call; 
        // 2: Put, 
        // 0: indicates that Put or Call is undefined for the order book.
        char put_or_call;

        static std::string GetFinancialProduct(char finprod) {
            switch (finprod) {
            case 1: return "Option";
            case 2: return "Forward";
            case 3: return "Future";
            case 4: return "FRA";
            case 5: return "Cash";
            case 6: return "Payment";
            case 7: return "Exchange Rate";
            case 8: return "Interest Rate Swap";
            case 9: return "REPO";
            case 10: return "Synthetic Box Leg/Reference";
            case 11: return "Standard Combination";
            case 12: return "Guarantee";
            case 13: return "OTC General";
            case 14: return "Equity Warrent";
            case 15: return "Security Lending";
            default: return "Not defined";
            }
        }
    };

    struct CombinationOrderBookLegMsg {
        char type{ 'M' }; //
        uint32_t timestamp_nanoseconds{ 0 };
        uint32_t combination_order_book_id;
        uint32_t leg_order_book_id;
        /*  B = As Defined
            C = Opposite
        */
        char leg_side;
        uint32_t leg_ratio;
    };

    struct OrderBookStateMsg {
        char type{ 'O' };//
        uint32_t timestamp_nanoseconds{ 0 };
        uint32_t order_book_id;
        char state_name[20];
    };

    struct EquilibriumPriceUpdateMsg {
        char type{ 'Z' };
        uint32_t timestamp_nanoseconds{ 0 };
        uint32_t order_book_id{ 0 };
        // qty at equilibrium price on the bid side
        uint64_t available_bid_qty{ 0 };
        uint64_t available_ask_qty{ 0 };
        price_t equilibrium_price{ 0 };
        price_t best_bid_price{ 0 };
        price_t best_ask_price{ 0 };
        uint64_t best_bid_qty{ 0 };
        uint64_t best_ask_qty{ 0 };
    };

    struct OrderAddMsg {
        char type{ 'A' };//
        uint32_t timestamp_nanoseconds{ 0 };
        uint64_t order_id{ 0 };
        uint32_t order_book_id{ 0 };

        /* B = Buy order
           S = Sell order
        */
        char side;
        uint32_t order_book_position{ 0 };
        uint64_t qty{ 0 };
        price_t price{ 0 };

        /*  Additional order attributes Values:
            0 = Not applicable
            8192 = Bait/implied order
        */
        uint16_t oder_attributes{ 0 };
        /*Lot type Values:
            2 = Round Lot
        */
        uint8_t lot_type;
    };

    struct OrderExecutedMsg {
        char type{ 'E' };
        uint32_t timestamp_nanoseconds{ 0 };
        uint64_t order_id{ 0 };
        uint32_t order_book_id{ 0 };
        /*  B = Buy order
            S = Sell order
        */
        char side;
        uint64_t executed_qty{ 0 };
        uint64_t match_id{ 0 };
        uint32_t combo_group_id{ 0 };
        char reserved1[7];
        char reserved2[7];
    };

    struct OrderExecutedWPriceMsg {
        char type{ 'C' };
        uint32_t timestamp_nanoseconds{ 0 };
        uint64_t order_id{ 0 };
        uint32_t order_book_id{ 0 };
        /*  B = Buy order
            S = Sell order
        */
        char side;
        uint64_t executed_qty{ 0 };
        uint64_t match_id{ 0 };
        uint32_t combo_group_id{ 0 };
        char reserved1[7];
        char reserved2[7];
        price_t trade_price;
        /*  Y = Yes
            N = No
        */
        char occurred_at_cross;
        char printable;
    };

    struct OrderReplaceMsg {
        char type{ 'U' };
        uint32_t timestamp_nanoseconds{ 0 };
        uint64_t order_id{ 0 };
        uint32_t order_book_id{ 0 };
        /*  B = Buy order
            S = Sell order
        */
        char side;
        uint32_t new_order_book_position{ 0 };
        uint64_t qty{ 0 };
        price_t price{ 0 };
        /* 0 = Not applicable
           8192 = Bait/implied order
        */
        uint16_t other_attributes[2]{ 0 };
    };

    struct OrderDeleteMsg {
        char type{ 'D' };
        uint32_t timestamp_nanoseconds{ 0 };
        uint64_t order_id{ 0 };
        uint32_t order_book_id{ 0 };
        /*  B = Buy order
            S = Sell order
        */
        char side;
    };

    struct SystemEventMsg {
        char type{ 'S' };
        uint32_t timestamp_nanoseconds{ 0 }; //
        /*  'O' Start of Messages
            'C' End of Messages
        */
        char event_code; //
    };

    struct TickSizeMsg {
        char type{ 'L' };
        uint32_t timestamp_nanoseconds{ 0 };
        uint32_t order_book_id{ 0 };
        uint64_t tick_size{ 0 };
        price_t price_from{ 0 };
        price_t price_to{ 0 };
    };

    struct TradeMsg {
        char type{ 'P' };
        uint32_t timestamp_nanoseconds{ 0 };
        uint64_t match_id{ 0 };
        uint32_t combo_group_id{ 0 };
        char side;
        uint64_t qty{ 0 };
        uint32_t order_book_id{ 0 };
        price_t trade_price{ 0 };
        char reserved1[7];
        char reserved2[7];
        /*Y, N*/
        char printable;
        /*Y, N*/
        char occurred_at_cross;
    };

    // --------------------------------------------------------------------------------------------;
    // Glimpse uses a subset of ITCH messages. 
    // Glimpse uses all messages used by ITCH to describe the current price of the book, 
    //      with the exception of those messages that change the picture of 
    //      the Order Book (e.g Delete, Execute and Trade).
    // --------------------------------------------------------------------------------------------;
    struct EndOfSnapshotMsg {
        char type{ 'G' };
        char sequence_number[20]; //
    };

#pragma pack(pop)
}

#endif // !__ITCH_GLIMPSE_MSGS_H__
