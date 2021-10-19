//-----------------------------------------------------------------------------
// File Name   : market_data_client.cpp
// Author      : junlei
// Date        : 8/27/2021 9:19:13 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "market_data_client.h"
#include "logger.h"

#include "nlohmann/json.hpp"
#include <thread>
#include <filesystem>

using json = nlohmann::json;
using namespace std;

MarketDataClient::MarketDataClient(const char* server,
    const char* broderID,
    const char* userID, const char* password,
    std::shared_ptr<ZmqHelper> zmq)
    : md_server_(server)
    , broker_ID_(broderID)
    , user_ID_(userID)
    , user_password_(password)
    , zmq_helper_(zmq) {
}

void MarketDataClient::Connect() {
    string tmpFolder("ctp-md/");
    if (!filesystem::exists(tmpFolder)) {
        filesystem::create_directory(tmpFolder);
    }

    md_api_ = CThostFtdcMdApi::CreateFtdcMdApi(tmpFolder.c_str());

    md_api_->RegisterSpi(this);
    md_api_->RegisterFront((char*)md_server_.c_str());
    md_api_->Init(); // Start connecting

    Logger::Log()->info("[{}:{}] CTP MD Initial client: serverUri={}, broker={}, user={}", __func__, __LINE__,
        md_server_.c_str(), broker_ID_.c_str(), user_ID_.c_str());

    this_thread::sleep_for(3s);
}

void MarketDataClient::OnFrontConnected() {
    Logger::Log()->info("[{}:{}] CTP MD Front connected.", __func__, __LINE__);

    DoLogin();
}

void MarketDataClient::DoLogin() {
    CThostFtdcReqUserLoginField field;
    memset(&field, 0, sizeof(field));
    strcpy_s(field.BrokerID, broker_ID_.c_str());
    strcpy_s(field.UserID, user_ID_.c_str());
    strcpy_s(field.Password, user_password_.c_str());

    int rtnCode = md_api_->ReqUserLogin(&field, NextRequestID());
    if (rtnCode != 0) {
        Logger::Log()->error("[{}:{}] CTP MD Login Request failed: code={}", __func__, __LINE__, rtnCode);
        //this_thread::sleep_for(5s);
        //doLogin();
    }
    else {
        Logger::Log()->info("[{}:{}] CTP MD Login request successfully.", __func__, __LINE__);
    }
}

void MarketDataClient::OnFrontDisconnected(int nReason) {
    Logger::Log()->error("[{}:{}] CTP MD Front disconnected: reasonCode={}", __func__, __LINE__, nReason);

    zmq_helper_->Send("DISCONNECTED");

    this_thread::sleep_for(3s); // better to have a delay before next retry of connecting.
}

void MarketDataClient::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin,
    CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
    if (pRspInfo == nullptr) {
        Logger::Log()->error("[{}:{}] CTP MD Logon failed with no reason.", __func__, __LINE__);
        return;
    }

    if (pRspInfo->ErrorID != 0) {
        Logger::Log()->error("[{}:{}] CTP MD Failed to login, ErrorCode={}, ErrorMsg={}, RequestID={}, Chain={}", __func__, __LINE__,
            pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast);
        return;
    }

    Logger::Log()->info("[{}:{}] CTP MD Login successfully: broker={}, user={}, sessionId={}, tradingDay={}", __func__, __LINE__,
        pRspUserLogin->BrokerID, pRspUserLogin->UserID, pRspUserLogin->SessionID, pRspUserLogin->TradingDay);

    // do other things, e.g. subscribe contract.
    //SubscribeContract("CU3M-LME");  // "FEM-HKE"

    zmq_helper_->Send("CONNECTED");
}

int MarketDataClient::SubscribeContract(const char* symbol) {
    //validateLogon();

    char* instruments[] = { (char*)symbol };
    int rtnCode = md_api_->SubscribeMarketData(instruments, sizeof(instruments) / sizeof(char*));
    if (rtnCode != 0) {
        Logger::Log()->error("[{}:{}] CTP subscribe contract {} request failed: code={}", __func__, __LINE__, symbol, rtnCode);
    }
    else {
        Logger::Log()->info("[{}:{}] CTP Requested to subscribe market data: instrumentID={}.", __func__, __LINE__, symbol);
    }

    return rtnCode;
}

int MarketDataClient::SubscribeContract(std::vector<char*> symbols) {
    char** ppInstID = new char* [symbols.size()];

    int cnt = 0;
    for (auto sym : symbols) {
        ppInstID[cnt] = sym;
        ++cnt;
    }

    int rtnCode = md_api_->SubscribeMarketData(ppInstID, cnt);
    if (rtnCode != 0) {
        Logger::Log()->error("[{}:{}] CTP subscribe contracts {} request failed: code={}", __func__, __LINE__, cnt, rtnCode);
    }
    else {
        Logger::Log()->info("[{}:{}] CTP Requested to subscribe market data: total={}.", __func__, __LINE__, cnt);
    }

    delete[] ppInstID;
    return rtnCode;
}

void MarketDataClient::OnRspSubMarketData(CThostFtdcSpecificInstrumentField* inst,
    CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
    if (pRspInfo != nullptr && pRspInfo->ErrorID != 0) {
        Logger::Log()->error("[{}:{}] CTP Market data subscribe failed: symbol={}, errorCode={}, msg={}", __func__, __LINE__,
            inst == nullptr ? "nullptr" : inst->InstrumentID, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        return;
    }

    if (inst == nullptr) { // Should not happen
        Logger::Log()->error("[{}:{}] CTP MD Invalid server response, got null pointer of instrument info.", __func__, __LINE__);
        return;
    }

    Logger::Log()->info("[{}:{}] Subscribed market data: instrumentID={}.", __func__, __LINE__, inst->InstrumentID);
}

void MarketDataClient::UnsubscribeContract(const char* symbol) {
    char* instrumentIDs[] = { (char*)symbol };
    int rtnCode = md_api_->UnSubscribeMarketData(instrumentIDs, sizeof(instrumentIDs) / sizeof(char*));
    if (rtnCode != 0) {
        Logger::Log()->error("[{}:{}] CTP unsubscribeContract Request failed for {}: code={}.", __func__, __LINE__, symbol, rtnCode);
    }
    else {
        Logger::Log()->info("[{}:{}] Requested to unsubscribe market data: instrumentID={}.", __func__, __LINE__, symbol);
    }
}

void MarketDataClient::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField* inst,
    CThostFtdcRspInfoField* status, int requestID, bool isLast) {
    if (status != nullptr && status->ErrorID != 0) {
        Logger::Log()->error("[{}:{}] CTP Failed to unsubscribe market data: instrumentID={}, errorID={}, errorMsg={}",
            __func__, __LINE__, inst == nullptr ? "nullptr" : inst->InstrumentID, status->ErrorID, status->ErrorMsg);
        return;
    }

    if (inst == nullptr) { // Should not happen
        Logger::Log()->error("[{}:{}] Invalid server response, got null pointer of instrument info.", __func__, __LINE__);
        return;
    }

    Logger::Log()->info("[{}:{}] Unsubscribed market data: instrumentID={}.", __func__, __LINE__,
        inst->InstrumentID);
}

// handle market data
void MarketDataClient::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* data) {
    if (data == nullptr) {
        Logger::Log()->error("[{}:{}] Unexpected nullptr pointer.", __func__, __LINE__);
        return;
    }

    json j;
    //j["Provider"] = "CTP";
    j["Exchange"] = data->ExchangeID;
    j["InstrumentID"] = data->InstrumentID;

    stringstream ss;
    ss << data->TradingDay << " " << setfill('0') << setw(6) << data->UpdateTime << '.'
        << setfill('0') << setw(3) << data->UpdateMillisec;
    j["DateTime"] = ss.str();  //ExchangeDateTime
    //j["LocalDateTime"] = time(nullptr);

    j["HighPrice"] = data->HighestPrice;
    j["LowPrice"] = data->LowestPrice;
    j["OpenPrice"] = data->OpenPrice;
    j["Volume"] = data->Volume;
    j["LastPrice"] = data->LastPrice;
    j["SettlementPrice"] = data->SettlementPrice;

    j["Turnover"] = data->Turnover;
    j["OpenInterest"] = data->OpenInterest;
    j["PreOpenInterest"] = data->PreOpenInterest;

    j["BidPrice1"] = data->BidPrice1;
    j["BidPrice2"] = data->BidPrice2;
    j["BidPrice3"] = data->BidPrice3;
    j["BidPrice4"] = data->BidPrice4;
    j["BidPrice5"] = data->BidPrice5;

    j["BidQty1"] = data->BidVolume1;
    j["BidQty2"] = data->BidVolume2;
    j["BidQty3"] = data->BidVolume3;
    j["BidQty4"] = data->BidVolume4;
    j["BidQty5"] = data->BidVolume5;

    j["AskPrice1"] = data->AskPrice1;
    j["AskPrice2"] = data->AskPrice2;
    j["AskPrice3"] = data->AskPrice3;
    j["AskPrice4"] = data->AskPrice4;
    j["AskPrice5"] = data->AskPrice5;

    j["AskQty1"] = data->AskVolume1;
    j["AskQty2"] = data->AskVolume2;
    j["AskQty3"] = data->AskVolume3;
    j["AskQty4"] = data->AskVolume4;
    j["AskQty5"] = data->AskVolume5;

    zmq_helper_->Send(j.dump());
}
