//-----------------------------------------------------------------------------
// File Name   : atp_export.h
// Author      : junlei
// Date        : 1/27/2020 10:19:13 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __ATP_EXPORT_H__
#define __ATP_EXPORT_H__

#define DLLEXPORT __declspec(dllexport)

extern "C" {
    DLLEXPORT void InitExport(const char* md_server,
        const char* td_server,
        const char* brokerId,
        const char* userId,
        const char* userPwd,
        const char* investorId,
        const char* appId,
        const char* authCode,
        const char* streamDataAddr,
        const char* streamTradeAddr);

    DLLEXPORT void UpdateTradeClientExport(const char* td_server, const char* brokerId,
        const char* userId, const char* userPwd, const char* investorId,
        const char* appId, const char* authCode);

    DLLEXPORT void DismentalExport();

    // market data
    DLLEXPORT int SubscribeContractExport(const char* symbol);
    DLLEXPORT void UnsubcribeContractExport(const char* symbol); // instrumentId

    // trade data
    DLLEXPORT void SetAccountID(const char* id);

    DLLEXPORT int SendOrderExport(const char* symbol, bool isBuy, double price, int volume,
        const char* orderTag);
    DLLEXPORT int ModifyOrderExport(const char* exchangeId, const char* orderId,
        double price, int qtyChg);
    DLLEXPORT int CancelOrderExport(const char* exchangeId, const char* orderId);

    DLLEXPORT void ReqQueryOrderExport(const char* symbol);
    DLLEXPORT void ReqQueryTradeExport(const char* symbol);
    DLLEXPORT void ReqQueryInvestorPositionExport(const char* symbol);
}

#endif //__ATP_EXPORT_H__
