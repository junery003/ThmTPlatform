//-----------------------------------------------------------------------------
// File Name   : trader_client.h
// Author      : junlei
// Date        : 8/27/2021 9:19:13 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __CTPTRADER_H__
#define __CTPTRADER_H__

#include "zmq_helper.h"
#include "thost_se/ThostFtdcTraderApi.h"

#include <string>

class TraderClient : public CThostFtdcTraderSpi {
public:
    TraderClient(const char* server, const char* brokerID,
        const char* userID, const char* password,
        const char* invectorID,
        const char* appID, const char* authCode,
        std::shared_ptr<ZmqHelper> zmq);

    ~TraderClient() {
        trade_api_->RegisterSpi(nullptr);
        trade_api_->Release();
    }

public:
    void Connect();
    void QueryInstrument(const char* symbol, const char* exchangeID);

    int InsertOrder(const char* instrument, bool isBuy, double price, int volume, const char* orderTag);
    int ModifyOrder(const char* exchangeId, const char* orderId, double price, int volume);
    int CancelOrder(const char* exchangeId, const char* orderId); // delete

    int QueryOrder(const char* symbol);
    void QueryTrade(const char* symbol);
    void QueryInvestorPosition(const char* symbol);

    void EnsureLogon();

protected:
    virtual void OnFrontConnected();
    virtual void OnFrontDisconnected(int nReason);

    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspOrderInsert(CThostFtdcInputOrderField* pInputOrder, CThostFtdcRspInfoField* pRspInfo,
        int nRequestID, bool bIsLast);
    virtual void OnRspOrderAction(CThostFtdcInputOrderActionField* pInputOrderAction,
        CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField* pOrderAction, CThostFtdcRspInfoField* pRspInfo);
    virtual void OnRtnOrder(CThostFtdcOrderField* pOrder);
    virtual void OnRtnTrade(CThostFtdcTradeField* pTrade);

    virtual void OnRspQryTrade(CThostFtdcTradeField* pTrade, CThostFtdcRspInfoField* pRspInfo,
        int nRequestID, bool bIsLast);
    virtual void OnRspQryOrder(CThostFtdcOrderField* pOrder, CThostFtdcRspInfoField* pRspInfo,
        int nRequestID, bool bIsLast);
    virtual void OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo,
        int nRequestID, bool bIsLast);
    virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField* pInvestorPosition,
        CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

private:
    void DoLogin();
    void DoAuthenticate();

    int NextRequestID() { return ++request_id_; }
    int NextOrderRef() { return order_ref_++; }

    static std::string FormatOrderStatus(const char status);
    static std::string FormatOrderType(const char type);

private:
    std::shared_ptr<ZmqHelper> zmq_helper_;

    std::string trade_server_;
    std::string broker_ID_;
    std::string user_ID_;
    std::string user_password_;
    std::string investor_ID_;
    std::string app_ID_;
    std::string auth_code_;
    bool is_auth_{ true };

    enum class LogonState {
        LOGON_SUCCEED = 0,
        LOGON_FAILED = 1,
        LOGON_ABORTED = 2,
        UNINITIALIZED_STATE = 3
    };

    volatile LogonState logon_state_{ LogonState::UNINITIALIZED_STATE };

    int request_id_{ 0 };
    int front_id_{ 0 };
    int session_id_{ 0 };
    int order_ref_{ 0 };
    CThostFtdcTraderApi* trade_api_{ nullptr };
};

#endif // __CTPTRADER_H__
