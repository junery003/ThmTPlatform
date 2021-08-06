//-----------------------------------------------------------------------------
// File Name   : ouch_client.cpp
// Author      : junlei
// Date        : 12/14/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "ouch_client.h"
#include "soup_bin_tcp_parser.h"
#include "logger.h"

#include "order_book_manager.h"

using namespace std;

OuchClient::OuchClient(boost::asio::io_context& io_contxt,
    TitanAccount::OuchConfig& ouch_login,
    shared_ptr<ZmqHelper> td_zmq)
    : io_contxt_(io_contxt)
    , ouch_login_(ouch_login)
    , cur_account_(ouch_login.account)
    , cur_customer_info_(ouch_login.customer_info)
    , ouch_parser_(make_shared<OuchParser>(td_zmq)) {
}

void OuchClient::SetAccount(const std::string& acc) {
    Logger::Log()->info("[{}:{}] OUCH Client set account: {}", __func__, __LINE__, acc);
    cur_account_ = acc;
}

bool OuchClient::Start() {
    Logger::Log()->info("[{}:{}] Starting OUCH-ip:{}:{}, ip2:{}:{}, "
        "user:{}, pwd:{}, heartbeat:{}",
        __func__, __LINE__, ouch_login_.server, ouch_login_.port, ouch_login_.server2, ouch_login_.port2,
        ouch_login_.ID, ouch_login_.password, ouch_login_.heartbeat);

    auto conn{ make_shared<TcpConnection>(io_contxt_, 2,
        ouch_login_.server,
        ouch_login_.port,
        ouch_login_.server2,
        ouch_login_.port2)
    };

    auto soupbintcp_parser{ make_shared<SoupBinTcpParser>(ouch_login_.ID,
        ouch_login_.password,
        ouch_login_.heartbeat)
    };

    //ouch_parser_->SetLowerLayer(soupbintcp_parser);
    soupbintcp_parser->SetUpperLayer(ouch_parser_);
    soupbintcp_parser->SetLowerLayer(dynamic_pointer_cast<ProtocolBase>(conn));

    return ouch_parser_->Start();
}

void OuchClient::Stop() {
    Logger::Log()->warn("[{}:{}] Stopping OUCH Client", __func__, __LINE__);
    ouch_parser_->Stop();
}

void OuchClient::EnterOrder(const char* symbol, char side, double price, uint64_t qty, int tif) {
    EnterOrderMsg msg(Utils::GetUniqueStr(13).c_str());

    auto order_book_id{ OrderBookManager::Instance().GetOrderbookID(symbol) };

    msg.side = side;
    msg.price = OrderBookManager::Instance().GetOrderBook(order_book_id)->FormatPrice(price);

    msg.order_book_id = htonl(order_book_id);
    msg.price = htonl(msg.price);
    msg.qty = htonll(qty);
    msg.time_in_force = (uint8_t)tif;

    memcpy(msg.client_account, cur_account_.c_str(), cur_account_.size());
    memcpy(msg.customer_info, cur_customer_info_.c_str(), cur_customer_info_.size());

    ouch_parser_->UnsequencedData((char*)&msg, sizeof(msg));

    Logger::Log()->info("[{}:{}] OUCH-msg O: Add order token:'{}', symbol:{}, order book id:{}, "
        "{}-{}@{}, TIF:{}, "
        "Client/Account:{}, customer info:{}, display qty:{}, STP Key:{}, order type:{}",
        __func__, __LINE__, string(msg.order_token).substr(0, 14), symbol, order_book_id,
        side, qty, price, msg.time_in_force,
        cur_account_, cur_customer_info_, msg.display_qty, msg.stp_key, msg.ouch_order_type);
}

// U:
void OuchClient::ReplaceOrder(const char* symbol, const char* existing_token, double price, uint64_t qty) {
    ReplaceOrderMsg msg(existing_token, Utils::GetUniqueStr(13).c_str());  // need update orderbook with new token

    auto order_book_id{ OrderBookManager::Instance().GetOrderbookID(symbol) };

    msg.price = OrderBookManager::Instance().GetOrderBook(order_book_id)->FormatPrice(price);

    msg.price = htonl(msg.price);
    msg.qty = htonll(qty);

    memcpy(msg.client_account, cur_account_.c_str(), cur_account_.size());

    ouch_parser_->UnsequencedData((char*)&msg, sizeof(msg));

    Logger::Log()->info("[{}:{}] OUCH-msg U: Replace order: symbol:{}, token:'{}', replacement order token:'{}' {}@{}, "
        "open close:{}, client/account:{}, display qty:{}, stp key:{}",
        __func__, __LINE__, symbol, existing_token, msg.replacement_order_token, qty, price,
        msg.open_close, cur_account_, msg.display_qty, msg.stp_key);
}

void OuchClient::CancelOrder(const char* order_token) {
    CancelOrderMsg msg(order_token);

    ouch_parser_->UnsequencedData((char*)&msg, sizeof(msg));

    Logger::Log()->info("[{}:{}] OUCH-msg X: Cancel order by token:'{}'", __func__, __LINE__, order_token);
}

void OuchClient::CancelByOrderID(const char* symbol, char side, uint64_t order_id) {
    CancelByOrderIDMsg msg(side);

    msg.order_id = htonll(order_id);

    msg.order_book_id = htonl(OrderBookManager::Instance().GetOrderbookID(symbol));

    ouch_parser_->UnsequencedData((char*)&msg, sizeof(msg));

    Logger::Log()->info("[{}:{}] OUCH-msg Y: Cancel order by ID: order book id:{}, "
        "symbol:{}, order id {}:{}",
        __func__, __LINE__, msg.order_book_id,
        symbol, side, order_id);
}
