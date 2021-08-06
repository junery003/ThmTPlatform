//-----------------------------------------------------------------------------
// File Name   : trader_client.cpp
// Author      : junlei
// Date        : 1/27/2020 9:19:13 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "trader_client.h"
#include "logger.h"
#include "nlohmann/json.hpp"

#include <thread>
#include <filesystem>

using json = nlohmann::json;
using namespace std;

TraderClient::TraderClient(const char* server, const char* brokerID,
    const char* userID, const char* password,
    const char* invectorID, const char* appID, const char* authCode,
    std::shared_ptr<ZmqHelper> zmq)
    : trade_server_(server)
    , broker_ID_(brokerID)
    , user_ID_(userID)
    , user_password_(password)
    , investor_ID_(invectorID)
    , app_ID_(appID)
    , auth_code_(authCode)
    , zmq_helper_(zmq) {
}

void TraderClient::Connect() {
    string tmpFolder("atp-trader/");
    if (!filesystem::exists(tmpFolder)) {
        filesystem::create_directory(tmpFolder);
    }

    // distinct flow path is needed for each api instance.
    trade_api_ = CThostFtdcTraderApi::CreateFtdcTraderApi(tmpFolder.c_str());

    trade_api_->RegisterSpi(this);
    trade_api_->RegisterFront((char*)trade_server_.c_str());

    trade_api_->SubscribePrivateTopic(THOST_TERT_RESTART);
    trade_api_->SubscribePublicTopic(THOST_TERT_RESTART);

    trade_api_->Init(); // Start connecting
    trade_api_->SubscribePrivateTopic(THOST_TERT_QUICK);

    Logger::Log()->info("[{}:{}] ATP TR Initial client: serverUri={}, broker={}, user={}", __func__, __LINE__,
        trade_server_.c_str(), broker_ID_.c_str(), user_ID_.c_str());

    this_thread::sleep_for(3s);
}

void TraderClient::OnFrontConnected() {
    Logger::Log()->info("[{}:{}] ATP TR Front connected.", __func__, __LINE__);

    is_auth_ ? DoAuthenticate() : DoLogin();
}

void TraderClient::OnFrontDisconnected(int nReason) {
    logon_state_ = LogonState::LOGON_ABORTED;

    Logger::Log()->error("[{}:{}] ATP TR Front disconnected: reasonCode={}", __func__, __LINE__, nReason);

    zmq_helper_->Send("DISCONNECTED");

    // better to have a delay before next retry of connecting.
    this_thread::sleep_for(3s);
    //doLogin();
}

void TraderClient::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin,
    CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
    if (pRspInfo != nullptr && pRspInfo->ErrorID != 0) {
        Logger::Log()->error("[{}:{}] ATP TR Failed to login, errorID={}, errorMsg={}",
            __func__, __LINE__, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        logon_state_ = LogonState::LOGON_FAILED;
        return;
    }

    if (pRspUserLogin == nullptr) { // Should not happen
        Logger::Log()->error("[{}:{}] ATP TR invalide server response, got null pointer of login info", __func__, __LINE__);
        logon_state_ = LogonState::LOGON_FAILED;
        return;
    }

    this->session_id_ = pRspUserLogin->SessionID;
    this->front_id_ = pRspUserLogin->FrontID;
    this->order_ref_ = atoi(pRspUserLogin->MaxOrderRef);

    Logger::Log()->info("[{}:{}] ATP TR Login successfully: broker={}, user={}, sessionId={}, tradingDay={}", __func__, __LINE__,
        pRspUserLogin->BrokerID, pRspUserLogin->UserID, pRspUserLogin->SessionID, pRspUserLogin->TradingDay);

    logon_state_ = LogonState::LOGON_SUCCEED;

    zmq_helper_->Send("CONNECTED");

    // do other things, e.g. add an order
    //insertOrder("A1809-DC", true, 3700.0, 5);
}

void TraderClient::OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField,
    CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
    if (pRspInfo != nullptr && pRspInfo->ErrorID != 0) {
        Logger::Log()->error("[{}:{}] ATP TR Failed to authenticate, errorID={}, errorMsg={}", __func__, __LINE__,
            pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        return;
    }

    if (pRspAuthenticateField == nullptr) {
        Logger::Log()->error("[{}:{}] ATP TR Invalid server response, got null pointer of authentication info.", __func__, __LINE__);
        return;
    }

    Logger::Log()->info("[{}:{}] ATP TR Authenticate succeed: brokerID={}, userID={}, appID={}, appType={}.",
        __func__, __LINE__, pRspAuthenticateField->BrokerID, pRspAuthenticateField->UserID,
        pRspAuthenticateField->AppID, pRspAuthenticateField->AppType);

    DoLogin();
}

int TraderClient::InsertOrder(const char* instrument, bool isBuy, double price, int volume, const char* orderTag) {
    EnsureLogon();

    CThostFtdcInputOrderField field;
    memset(&field, 0, sizeof(field));
    strcpy_s(field.BrokerID, broker_ID_.c_str());
    strcpy_s(field.InvestorID, investor_ID_.c_str());
    strcpy_s(field.UserID, user_ID_.c_str());
    strcpy_s(field.InstrumentID, instrument);
    sprintf_s(field.OrderRef, "%d", NextOrderRef());
    field.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
    field.Direction = isBuy ? THOST_FTDC_D_Buy : THOST_FTDC_D_Sell; // Direction
    field.CombOffsetFlag[0] = '\0'; // THOST_FTDC_OF_Open;
    field.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
    field.CombHedgeFlag[1] = '\0'; //'9'; // Enable this line to create market maker order.
    field.LimitPrice = price;      // Price
    field.VolumeTotalOriginal = volume; // Volume
    field.TimeCondition = THOST_FTDC_TC_GFD;
    strcpy_s(field.GTDDate, "");
    field.VolumeCondition = THOST_FTDC_VC_AV;
    field.MinVolume = 0;
    field.ContingentCondition = THOST_FTDC_CC_Immediately;
    field.StopPrice = 0.0;
    field.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
    field.IsAutoSuspend = 0;
    strcpy_s(field.BusinessUnit, orderTag); // Store customized data if necessary(needs to be a string).

    const int requestId = NextRequestID();
    field.RequestID = requestId;
    field.UserForceClose = 0;
    field.IsSwapOrder = 0;

    int rtnCode = trade_api_->ReqOrderInsert(&field, requestId);
    if (rtnCode != 0) {
        Logger::Log()->error("[{}:{}] Request failed: code={}", __func__, __LINE__, rtnCode);
    }
    else {
        Logger::Log()->info("[{}:{}] Requested to add new order: instrument={}, direction={}, volume={}, price={}, orderRef={}",
            __func__, __LINE__, instrument, isBuy ? "buy" : "sell", volume, price, field.OrderRef);
    }

    return rtnCode;
}

// for insert error only
void TraderClient::OnRspOrderInsert(CThostFtdcInputOrderField* pInputOrder, CThostFtdcRspInfoField* pRspInfo,
    int nRequestID, bool bIsLast) {
    if (pRspInfo != nullptr && pRspInfo->ErrorID != 0) {
        if (pInputOrder == nullptr) { // should not happen
            Logger::Log()->error("[{}:{}] Invalid server response, got null pointer of input order.", __func__, __LINE__);
            return;
        }

        Logger::Log()->error("[{}:{}] Failed to add new order: OrderRef={}, instrumentID={}, direction={}, volumeTotalOriginal={}, limitPrice={}, errorID={}, errorMsg={}", __func__, __LINE__, pInputOrder->OrderRef,
            pInputOrder->InstrumentID, pInputOrder->Direction == THOST_FTDC_D_Buy ? "buy" : "sell",
            pInputOrder->VolumeTotalOriginal, pInputOrder->LimitPrice, pRspInfo->ErrorID, pRspInfo->ErrorMsg);

        //return;
    }

    Logger::Log()->warn("[{}:{}] error happens when inserting order.", __func__, __LINE__);

    json j;
    //j["Provider"]= "ATP";
    j["BrokerID"] = pInputOrder->BrokerID;
    j["Account"] = pInputOrder->UserID;
    j["InstrumentID"] = pInputOrder->InstrumentID;
    j["OrderRef"] = pInputOrder->OrderRef;
    j["BuyOrSell"] = pInputOrder->Direction - '0';
    j["LimitPrice"] = pInputOrder->LimitPrice;
    j["OrderStatus"] = "Failed";
    j["OrderTag"] = pInputOrder->BusinessUnit;
    if (pRspInfo != nullptr) {
        j["Text"] = pRspInfo->ErrorMsg;
    }

    zmq_helper_->Send(j.dump());
}

int TraderClient::ModifyOrder(const char* exchangeId, const char* orderId, double price, int volume) {
    EnsureLogon();

    CThostFtdcInputOrderActionField field;
    memset(&field, 0, sizeof(field));
    strcpy_s(field.BrokerID, broker_ID_.c_str());
    strcpy_s(field.InvestorID, investor_ID_.c_str());
    strcpy_s(field.UserID, user_ID_.c_str());

    // Set FrontID, SessionID and OrderRef properly(or use ExchangeID+OrderSysID instead)
    //field.FrontID = front_ID_;
    //field.SessionID = session_ID_;
    //strcpy_s(field.OrderRef, orderRef);

    // Or use ExchangeID+OrderSysID to locate the order:
    strcpy_s(field.ExchangeID, exchangeId); // "LME"
    strcpy_s(field.OrderSysID, orderId);

    //field.OrderActionRef = THOST_FTDC_AF_Modify;
    field.ActionFlag = THOST_FTDC_AF_Modify;
    field.LimitPrice = price;
    field.VolumeChange = volume;

    int rtnCode = trade_api_->ReqOrderAction(&field, NextRequestID());
    if (rtnCode != 0) {
        Logger::Log()->error("[{}:{}] Request failed: code=[{}].", __func__, __LINE__, rtnCode);
    }
    else {
        Logger::Log()->info("[{}:{}] SENT Request: code={}.", __func__, __LINE__, rtnCode);
    }

    return rtnCode;
}

int TraderClient::CancelOrder(const char* exchangeId, const char* orderId) {
    EnsureLogon();

    CThostFtdcInputOrderActionField field;
    memset(&field, 0, sizeof(field));
    strcpy_s(field.BrokerID, broker_ID_.c_str());
    strcpy_s(field.InvestorID, investor_ID_.c_str());
    strcpy_s(field.UserID, user_ID_.c_str());

    // Use FrontID+SessionID+OrderRef to locate the order:
    //field.FrontID = front_ID_;    // FrontID can be got from CThostFtdcOrderField.FrontID
    //field.SessionID = session_ID_;  // SessionID can be got from CThostFtdcOrderField.SessionID
    //strcpy_s(field.OrderRef, orderRef);

    // Or use ExchangeID+OrderSysID to locate the order:
    strcpy_s(field.ExchangeID, exchangeId);
    strcpy_s(field.OrderSysID, orderId);

    field.ActionFlag = THOST_FTDC_AF_Delete;  // delete

    int rtnCode = trade_api_->ReqOrderAction(&field, NextRequestID());
    if (rtnCode != 0) {
        Logger::Log()->error("[{}:{}] Request failed: code={}.", __func__, __LINE__, rtnCode);
    }
    else {
        Logger::Log()->info("[{}:{}] Requested to cancel order: exchangeId={}, orderId={}.",
            __func__, __LINE__, exchangeId, orderId);
    }

    return rtnCode;
}

void TraderClient::OnRspOrderAction(CThostFtdcInputOrderActionField* pInputOrderAction,
    CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
    if (pRspInfo != nullptr && pRspInfo->ErrorID != 0) {
        if (pInputOrderAction == nullptr) { // should not happen
            Logger::Log()->error("[{}:{}] Invalid server response, got null pointer of input order action.",
                __func__, __LINE__);
            return;
        }

        Logger::Log()->error("[{}:{}] Failed to {} order: orderRef={}, orderSysID={}, instrumentID={}, volumeChange={}, limitPrice={}, errorID={}, errorMsg={}", __func__, __LINE__,
            pInputOrderAction->ActionFlag == THOST_FTDC_AF_Delete ? "delete" : "modify",
            pInputOrderAction->OrderRef, pInputOrderAction->OrderSysID, pInputOrderAction->InstrumentID,
            pInputOrderAction->VolumeChange, pInputOrderAction->LimitPrice, pRspInfo->ErrorID, pRspInfo->ErrorMsg);

        return;
    }

    json j;
    //j["Provider"] = "ATP";
    j["BrokerID"] = pInputOrderAction->BrokerID;
    j["Account"] = pInputOrderAction->UserID;

    j["InstrumentID"] = pInputOrderAction->InstrumentID;

    j["OrderID"] = pInputOrderAction->OrderSysID;
    j["OrderRef"] = pInputOrderAction->OrderRef;
    j["LimitPrice"] = pInputOrderAction->LimitPrice;
    j["TradedQty"] = pInputOrderAction->VolumeChange;

    j["FillPrice"] = 0.0;

    //j["OrderStatus"] = pInputOrderAction->ActionFlag == THOST_FTDC_AF_Delete ? "delete" : "modify";
    j["OrderStatus"] = pInputOrderAction->ActionFlag == THOST_FTDC_AF_Delete ? "Canceled" : "Replaced";

    //j["BuyOrSell"] = pInputOrderAction->;
    //j["totalOrderQty"] = pInputOrderAction->;

    if (pRspInfo != nullptr) {
        j["Text"] = pRspInfo->ErrorMsg;
    }

    zmq_helper_->Send(j.dump());
}

// order insertion failure
void TraderClient::OnErrRtnOrderAction(CThostFtdcOrderActionField* pOrderAction, CThostFtdcRspInfoField* pRspInfo) {
    Logger::Log()->error("[{}:{}] OnErrRtnOrderAction: ErrorID={},ErrorMsg={}", __func__, __LINE__,
        pRspInfo->ErrorID, pRspInfo->ErrorMsg);

    if (pOrderAction == nullptr) {
        Logger::Log()->error("[{}:{}] OnErrRtnOrderAction: action is null", __func__, __LINE__);
        return;
    }

    json j;
    //j["Provider"] = "ATP";
    j["BrokerID"] = pOrderAction->BrokerID;
    j["Account"] = pOrderAction->UserID;

    j["InstrumentID"] = pOrderAction->InstrumentID;

    j["OrderID"] = pOrderAction->OrderSysID;
    j["OrderRef"] = pOrderAction->OrderRef;
    j["LimitPrice"] = pOrderAction->LimitPrice;
    j["TradedQty"] = pOrderAction->VolumeChange;

    stringstream ss;
    ss << pOrderAction->ActionDate << ' ' << setfill('0') << setw(6)
        << pOrderAction->ActionTime << '.' << setfill('0') << setw(3) << 0;
    j["DateTime"] = ss.str();

    j["FillPrice"] = 0.0;

    //j["OrderStatus"] = pOrderAction->ActionFlag == THOST_FTDC_AF_Delete ? "delete" : "modify";
    j["OrderStatus"] = pOrderAction->ActionFlag == THOST_FTDC_AF_Delete ? "Canceled" : "Replaced";

    j["OrderTag"] = pOrderAction->StatusMsg;

    if (pRspInfo != nullptr) {
        j["Text"] = pRspInfo->ErrorMsg;
    }

    zmq_helper_->Send(j.dump());
}

void TraderClient::OnRtnOrder(CThostFtdcOrderField* pOrder) {
    if (pOrder == nullptr) {
        Logger::Log()->warn("[{}:{}] Order is nullptr.", __func__, __LINE__);
        return;
    }

    json j;
    //j["Provider", "ATP";
    j["BrokerID"] = pOrder->BrokerID;
    j["Account"] = pOrder->UserID;
    j["InstrumentID"] = pOrder->InstrumentID;
    //j["Exchange"] = pOrder->ExchangeID;

    j["OrderID"] = pOrder->OrderSysID;
    j["OrderRef"] = pOrder->OrderRef;
    j["BuyOrSell"] = pOrder->Direction - '0';

    stringstream ss;
    ss << pOrder->InsertDate << ' ' << setfill('0') << setw(6) << pOrder->InsertTime << '.'
        << setfill('0') << setw(3) << 0;
    j["DateTime"] = ss.str();

    j["LimitPrice"] = pOrder->LimitPrice;
    j["TotalOrderQty"] = pOrder->VolumeTotalOriginal;
    //j["TradedQty"] = pOrder->VolumeTraded;  
    j["FillQty"] = pOrder->VolumeTraded; //returns 36  
    //j["FillPrice"] = pOrder->LimitPrice;

    j["OrderStatus"] = FormatOrderStatus(pOrder->OrderStatus);

    j["OrderTag"] = pOrder->BusinessUnit;
    j["Text"] = pOrder->StatusMsg;

    zmq_helper_->Send(j.dump());
}

void TraderClient::OnRtnTrade(CThostFtdcTradeField* pTrade) {
    if (pTrade == nullptr) {
        Logger::Log()->warn("[{}:{}] pTrade is nullptr.", __func__, __LINE__);
        return;
    }

    json j;
    //j["Provider", "ATP";
    j["BrokerID"] = pTrade->BrokerID;
    j["Account"] = pTrade->UserID;

    j["InstrumentID"] = pTrade->InstrumentID;
    j["OrderID"] = pTrade->OrderSysID;
    j["OrderRef"] = pTrade->OrderRef;

    stringstream ss;
    ss << pTrade->TradeDate << ' ' << setfill('0') << setw(6) << pTrade->TradeTime << '.'
        << setfill('0') << setw(3) << 0;
    j["DateTime"] = ss.str();
    //j["LocalDateTime"] = time(nullptr);

    j["FillPrice"] = pTrade->Price;
    j["LimitPrice"] = pTrade->Price;
    j["BuyOrSell"] = pTrade->Direction - '0';
    j["FillQty"] = pTrade->Volume; //returns 36  
    //j["TradedQty"] = pTrade->Volume;

    j["OrderStatus"] = "Filled";
    j["OrderTag"] = pTrade->BusinessUnit;

    zmq_helper_->Send(j.dump());
}

//enter exchange, instrument ID, specific order ID, time tll time
int TraderClient::QueryOrder(const char* symbol) {
    EnsureLogon();

    CThostFtdcQryOrderField field;
    memset(&field, 0, sizeof(field));
    strcpy_s(field.BrokerID, broker_ID_.c_str());
    strcpy_s(field.InvestorID, investor_ID_.c_str());
    // Query all the CME orders with insertion time: [09:30, 15:00]
    strcpy_s(field.ExchangeID, ""); // exchangeId;
    strcpy_s(field.InstrumentID, symbol);
    strcpy_s(field.OrderSysID, ""); // OrderID);
    strcpy_s(field.InsertTimeStart, "");
    strcpy_s(field.InsertTimeEnd, "");

    int rtnCode = trade_api_->ReqQryOrder(&field, NextRequestID());
    if (rtnCode != 0) {
        Logger::Log()->error("[{}:{}] Request failed for {}: code=[{}].", __func__, __LINE__, symbol, rtnCode);
    }
    else {
        Logger::Log()->info("[{}:{}] Requested to query order info: instrumentID={}.", __func__, __LINE__, symbol);
    }

    this_thread::sleep_for(100ms);
    return rtnCode;
}

void TraderClient::OnRspQryOrder(CThostFtdcOrderField* pOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
    if (pOrder == nullptr) {
        Logger::Log()->warn("[{}:{}] pOrder is nullptr.", __func__, __LINE__);
        return;
    }

    json j;
    //j["Provider", "ATP";
    j["BrokerID"] = pOrder->BrokerID;
    j["Account"] = pOrder->UserID; // pOrder->AccountID; // UserID
    j["InstrumentID"] = pOrder->InstrumentID;

    j["OrderID"] = pOrder->OrderSysID;
    j["OrderRef"] = pOrder->OrderRef;
    j["BuyOrSell"] = pOrder->Direction - '0';

    j["LimitPrice"] = pOrder->LimitPrice;
    //j["TradedQty"] = pOrder->VolumeTraded;
    j["FillQty"] = pOrder->VolumeTraded;
    j["TotalOrderQty"] = pOrder->VolumeTotalOriginal;

    //j["LocalDateTime"] = time(nullptr);
    stringstream ss;
    ss << pOrder->TradingDay << ' ' << setfill('0') << setw(6) << pOrder->UpdateTime << '.' << setfill('0') << setw(3) << 0;
    j["DateTime"] = ss.str();

    j["OrderType"] = FormatOrderType(pOrder->OrderType);
    j["OrderStatus"] = FormatOrderStatus(pOrder->OrderStatus);

    if (pRspInfo != nullptr) {
        j["Text"] = pRspInfo->ErrorMsg;
    }

    zmq_helper_->Send(j.dump());
}

void TraderClient::QueryTrade(const char* symbol) {
    EnsureLogon();

    CThostFtdcQryTradeField field;
    memset(&field, 0, sizeof(field));
    strcpy_s(field.BrokerID, broker_ID_.c_str());
    strcpy_s(field.InvestorID, investor_ID_.c_str());
    strcpy_s(field.InstrumentID, symbol);
    strcpy_s(field.ExchangeID, "");
    strcpy_s(field.TradeID, "");
    strcpy_s(field.TradeTimeStart, "");  // The Format of TradeTimeStart: HH:mm:ss, e.g: 09:30:00
    strcpy_s(field.TradeTimeEnd, "");   // The Format of TradeTimeEnd : HH:mm:ss, e.g: 15:00:00

    int rtnCode = trade_api_->ReqQryTrade(&field, NextRequestID());
    if (rtnCode != 0) {
        Logger::Log()->error("[{}:{}] Request failed: code={}", __func__, __LINE__, rtnCode);
    }
    else {
        Logger::Log()->info("[{}:{}] Query trade info: broker={}, investor={}, instrument={}", __func__, __LINE__,
            field.BrokerID, field.InvestorID, field.InstrumentID);
    }
}

void TraderClient::OnRspQryTrade(CThostFtdcTradeField* pTrade, CThostFtdcRspInfoField* pRspInfo,
    int nRequestID, bool bIsLast) {
}

void TraderClient::QueryInvestorPosition(const char* symbol) {
    EnsureLogon();

    CThostFtdcQryInvestorPositionField field;
    memset(&field, 0, sizeof(field));
    strcpy_s(field.BrokerID, broker_ID_.c_str());
    strcpy_s(field.InvestorID, investor_ID_.c_str());
    strcpy_s(field.InstrumentID, symbol);

    int rtnCode = trade_api_->ReqQryInvestorPosition(&field, NextRequestID());
    if (rtnCode != 0) {
        Logger::Log()->error("[{}:{}] Request failed: code=[{}].", __func__, __LINE__, rtnCode);
    }
    else {
        Logger::Log()->info("[{}:{}] Requested to query investor position info: brokerID={}, investorID={}, instrumentID={}.",
            __func__, __LINE__, field.BrokerID, field.InvestorID, field.InstrumentID);
    }
}

void TraderClient::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField* pPositionFields,
    CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
    if (pPositionFields == nullptr) {
        Logger::Log()->warn("[{}:{}] pPositionFields is nullptr.", __func__, __LINE__);
        return;
    }

    json j;
    //j["Provider"]="ATP";
    j["BrokerID"] = pPositionFields->BrokerID;
    j["InstrumentID"] = pPositionFields->InstrumentID;

    //j["LocalDateTime"] = time(nullptr);
    j["Position"] = pPositionFields->Position;
    j["PositionCost"] = pPositionFields->PositionCost;

    zmq_helper_->Send(j.dump());
}

void TraderClient::QueryInstrument(const char* symbol) {
    EnsureLogon();

    CThostFtdcQryInstrumentField field;
    memset(&field, 0, sizeof(field));
    strcpy_s(field.ExchangeID, "");
    //strcpy_s(field.ExchangeInstID, "EVM"); // Enable this line to get CThostFtdcInstrumentField.VolumeMultiple with original currency
    strcpy_s(field.InstrumentID, symbol);
    strcpy_s(field.ProductID, "");

    int rtnCode = trade_api_->ReqQryInstrument(&field, NextRequestID());
    if (rtnCode != 0) {
        Logger::Log()->error("[{}:{}] Request failed for {}: code={}.", __func__, __LINE__,
            symbol, rtnCode);
    }
    else {
        Logger::Log()->info("[{}:{}] Requested to query instrument info: instrumentID={}.",
            __func__, __LINE__, field.InstrumentID);
    }

    this_thread::sleep_for(500ms);
}

void TraderClient::OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo,
    int nRequestID, bool bIsLast) {
    if (pRspInfo != nullptr && pRspInfo->ErrorID != 0) {
        Logger::Log()->error("[{}:{}] Failed to query instrument info: errorID={}, errorMsg={}",
            __func__, __LINE__, pRspInfo->ErrorID, pRspInfo->ErrorMsg);

        return;
    }

    if (pInstrument == nullptr) {
        if (pRspInfo == nullptr) { // should not happen
            Logger::Log()->error("[{}:{}] Invalid server response, got null pointer of instrument info.", __func__, __LINE__);
            return;
        }
        if (!bIsLast) { // should not happen
            Logger::Log()->error("[{}:{}] Invalid server response, got null pointer of instrument info.", __func__, __LINE__);
            return;
        }

        Logger::Log()->warn("[{}:{}] No matched instrument info found.", __func__, __LINE__);
        return;
    }

    json j;
    j["Exchange"] = pInstrument->ExchangeID;
    j["InstrumentID"] = pInstrument->InstrumentID;
    j["PriceTick"] = pInstrument->PriceTick;

    //j["IsTrading", pInstrument->IsTrading != 0 ? "true" : "false";
    //j["ExpireDate"] = pInstrument->ExpireDate;
    //j["VolumeMultiple"] = pInstrument->VolumeMultiple;
    //j["ExchangeInstID"] = pInstrument->ExchangeInstID;

    zmq_helper_->Send(j.dump());
}

void TraderClient::EnsureLogon() {
    const int MAX_ATTEMPT_TIMES = 100;
    int tryTimes = 0;
    while (logon_state_ == LogonState::UNINITIALIZED_STATE && tryTimes++ < MAX_ATTEMPT_TIMES) {
        this_thread::sleep_for(200ms);
    }

    if (logon_state_ != LogonState::LOGON_SUCCEED) {
        Logger::Log()->error("[{}:{}] ATP TR logon failed.", __func__, __LINE__);
    }
}

void TraderClient::DoLogin() {
    CThostFtdcReqUserLoginField field;
    memset(&field, 0, sizeof(field));
    strcpy_s(field.BrokerID, broker_ID_.c_str());
    strcpy_s(field.UserID, user_ID_.c_str());
    strcpy_s(field.Password, user_password_.c_str());

    int rtnCode = trade_api_->ReqUserLogin(&field, NextRequestID());
    if (rtnCode != 0) {
        Logger::Log()->info("[{}:{}] ATP TR Login Request failed: code={}", __func__, __LINE__, rtnCode);

        //this_thread::sleep_for(3s);
        //doLogin();
    }
    else {
        Logger::Log()->info("[{}:{}] ATP TR Login request successfully.", __func__, __LINE__);
    }
}

void TraderClient::DoAuthenticate() {
    CThostFtdcReqAuthenticateField field;
    memset(&field, 0, sizeof(field));
    strcpy_s(field.BrokerID, broker_ID_.c_str());
    strcpy_s(field.UserID, user_ID_.c_str());
    strcpy_s(field.AppID, app_ID_.c_str());
    strcpy_s(field.AuthCode, auth_code_.c_str());

    int rtnCode = trade_api_->ReqAuthenticate(&field, NextRequestID());
    if (rtnCode != 0) {
        Logger::Log()->error("[{}:{}] ATP TR Authenticate Request failed: code=[{}].", __func__, __LINE__, rtnCode);
    }
    else {
        Logger::Log()->info("[{}:{}] Request authenticate: broker={}, user={}, appID={}, authCode={}.",
            __func__, __LINE__, broker_ID_.c_str(), user_ID_.c_str(),
            app_ID_.c_str(), auth_code_.c_str());
    }
}

string TraderClient::FormatOrderStatus(const char status) {
    switch (status) {
    case '0':
        return "Filled"; // : All traded";
    case '1':
        return "PartiallyFilled"; // Partial trade and still queueing";
    case '2':
        return "Partial trade and not in the queue";
    case '3':
        return "Pending"; // : No trade and still queueing";
    case '4':
        return "No trade and not in the queue";
    case '5':
        return "Canceled";
    case 'a':
        return "Unknown";
    case 'b':
        return "Not touched";
    case 'c':
        return "Touched";
    default:
        return "Undefined";
    }
}

string TraderClient::FormatOrderType(const char type) {
    switch (type) {
    case '0':
        return "Normal";
    case '1':
        return "Derive from quote";
    case '2':
        return "Derive from combination";
    case '3':
        return "Combination order";
    case '4':
        return "Conditional order";
    case '5':
        return "Swap order";
    default:
        return "Undefined";
    }
}

/*
  enum OrdStatus {
    NotSet = 0,
    New = 1,
    PartiallyFilled = 2,
    Filled = 3,
    DoneForDay = 4,
    Canceled = 5,
    PendingCancel = 6,
    Stopped = 7,
    Rejected = 8,
    Suspended = 9,
    PendingNew = 10,
    Calculated = 11,
    Expired = 12,
    AcceptedForBidding = 13,
    PendingReplace = 14,
    Unknown = 16,
    Inactive = 17,
    Planned = 18
  }

  enum OrderType {
    NotSet = 0,
    Market = 1,
    Limit = 2,
    Stop = 3,
    StopLimit = 4,
    MarketWithLeftOverAsLimit = 20,
    MarketLimitMarketLeftOverAsLimit = 21,
    StopMarketToLimit = 30,
    IfTouchedMarket = 31,
    IfTouchedLimit = 32,
    IfTouchedMarketToLimit = 33,
    LimitPostOnly = 37,
    MarketCloseToday = 38,
    LimitCloseToday = 39,
    LimitReduceOnly = 40,
    MarketReduceOnly = 41,
    Unknown = 100
  }
  */
