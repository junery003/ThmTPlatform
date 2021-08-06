//-----------------------------------------------------------------------------
// File Name   : market_data_client.h
// Author      : junlei
// Date        : 1/27/2020 9:19:13 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __ATPMARKETDATA_H__
#define __ATPMARKETDATA_H__

#include "zmq_helper.h"
#include "thost/ThostFtdcMdApi.h"

#include <string>

class MarketDataClient : public CThostFtdcMdSpi {
public:
    MarketDataClient(const char* server, const char* broderID,
        const char* userID, const char* password,
        std::shared_ptr<ZmqHelper> zmq);

    ~MarketDataClient() {
        // Destroy the instance and release resources.  
        md_api_->RegisterSpi(nullptr);
        md_api_->Release();
    }

public:
    void Connect();
    int SubscribeContract(const char* symbol);
    void UnsubscribeContract(const char* symbol);

protected:
    virtual void OnFrontConnected() override;
    virtual void OnFrontDisconnected(int nReason) override;

    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin,
        CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField* inst,
        CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField* inst,
        CThostFtdcRspInfoField* status, int requestID, bool isLast);

    virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* data);

private:
    void DoLogin();
    int NextRequestID() { return request_id_++; }

private:
    std::shared_ptr<ZmqHelper> zmq_helper_;

    std::string md_server_;
    std::string broker_ID_;
    std::string user_ID_;
    std::string user_password_;

    CThostFtdcMdApi* md_api_{ nullptr };
    int request_id_{ 1 };
};

#endif //ATPmarketdata_H__
