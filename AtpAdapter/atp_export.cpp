//-----------------------------------------------------------------------------
// File Name   : atp_export.cpp
// Author      : junlei
// Date        : 1/27/2020 10:19:13 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "atp_export.h"
#include "atp_client.h"

#include <memory>

// the ATP client
std::unique_ptr<AtpClient> kAtpClient = nullptr;
////////////////////////////////////////////////////////////////////////////////////
void InitExport(const char* md_server,
    const char* td_server,
    const char* brokerId,
    const char* userId,
    const char* userPwd,
    const char* investorId,
    const char* appId,
    const char* authCode,
    const char* streamDataAddr,
    const char* streamTradeAddr) {
    if (kAtpClient == nullptr) {
        kAtpClient = std::make_unique<AtpClient>(md_server, td_server, brokerId, userId, userPwd,
            investorId, appId, authCode, streamDataAddr, streamTradeAddr);
    }
}

void UpdateTradeClientExport(const char* td_server,
    const char* brokerId,
    const char* userId,
    const char* userPwd,
    const char* investorId,
    const char* appId,
    const char* authCode) {
    kAtpClient->UpdateTradeClient(td_server, brokerId, userId, userPwd, investorId, appId, authCode);
}

////////////////////////////////////////////////////////////////////////////////////
int SubscribeContractExport(const char* symbol) {
    return kAtpClient->Subscribe(symbol);
}

void UnsubcribeContractExport(const char* symbol) { // instrumentId
    kAtpClient->Unsubscribe(symbol);
}

////////////////////////////////////////////////////////////////////////////////////
void SetAccountID(const char* id) {
    kAtpClient->SetAccountID(id);
}

int SendOrderExport(const char* symbol, bool isBuy, double price, int volume, const char* orderTag) {
    return kAtpClient->InsertOrder(symbol, isBuy, price, volume, orderTag);
}

int ModifyOrderExport(const char* exchangeId, const char* orderId, double price, int qtyChg) {
    return kAtpClient->ModifyOrder(exchangeId, orderId, price, qtyChg);
}

int CancelOrderExport(const char* exchangeId, const char* orderId) {
    return kAtpClient->CancelOrder(exchangeId, orderId);
}

void ReqQueryOrderExport(const char* symbol) {
    kAtpClient->QueryOrder(symbol);
}

void ReqQueryTradeExport(const char* symbol) {
    kAtpClient->QueryTrade(symbol);
}

void ReqQueryInvestorPositionExport(const char* symbol) {
    kAtpClient->QueryInvestorPosition(symbol);
}

void DismentalExport() {

}
