//-----------------------------------------------------------------------------
// File Name   : ctp_export.cpp
// Author      : junlei
// Date        : 8/27/2021 10:19:13 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "ctp_export.h"
#include "ctp_client.h"

#include <memory>

// the client
static std::unique_ptr<CtpClient> kCtpClient{ nullptr };
////////////////////////////////////////////////////////////////////////////////////
bool InitExport() {
    if (kCtpClient == nullptr) {
        kCtpClient = std::make_unique<CtpClient>();
    }

    if (!kCtpClient->Init()) {
        return false;
    }

    return true;
}

void UpdateTradeClientExport(const char* userId, const char* userPwd) {
    kCtpClient->UpdateTradeClient(userId, userPwd);
}

////////////////////////////////////////////////////////////////////////////////////
int SubscribeContractExport(const char* symbol, const char* exchangeID) {
    return kCtpClient->Subscribe(symbol, exchangeID);
}

void UnsubcribeContractExport(const char* symbol) { // instrumentId
    kCtpClient->Unsubscribe(symbol);
}

////////////////////////////////////////////////////////////////////////////////////
void SetAccountID(const char* id) {
    kCtpClient->SetAccountID(id);
}

int SendOrderExport(const char* symbol, bool isBuy, double price, int volume, const char* orderTag) {
    return kCtpClient->InsertOrder(symbol, isBuy, price, volume, orderTag);
}

int ModifyOrderExport(const char* exchangeId, const char* orderId, double price, int qtyChg) {
    return kCtpClient->ModifyOrder(exchangeId, orderId, price, qtyChg);
}

int CancelOrderExport(const char* exchangeId, const char* orderId) {
    return kCtpClient->CancelOrder(exchangeId, orderId);
}

void ReqQueryOrderExport(const char* symbol) {
    kCtpClient->QueryOrder(symbol);
}

void ReqQueryTradeExport(const char* symbol) {
    kCtpClient->QueryTrade(symbol);
}

void ReqQueryInvestorPositionExport(const char* symbol) {
    kCtpClient->QueryInvestorPosition(symbol);
}

void DismentalExport() {

}
