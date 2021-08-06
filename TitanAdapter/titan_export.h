//-----------------------------------------------------------------------------
// File Name   : titan_export.h
// Author      : junlei
// Date        : 12/3/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __TITAN_EXPORT_H__
#define __TITAN_EXPORT_H__

#include <stdint.h>
#define DLLEXPORT __declspec(dllexport)

extern "C" {
    DLLEXPORT bool InitExport();
    DLLEXPORT void DismentalExport();

    // security 
    DLLEXPORT bool ChangePasswordExport(const char* usr, const char* cur_pwd, const char* new_pwd);

    // market data
    DLLEXPORT void SubscribeContractExport(const char* symbol);
    DLLEXPORT void UnsubscribeContractExport(const char* symbol);

    // orders
    DLLEXPORT void SetAccountExport(const char* account);

    DLLEXPORT void AddOrderExport(const char* symbol, bool is_buy, double price, int qty, int tif);
    DLLEXPORT void ReplaceOrderExport(const char* symbol, const char* ori_order_token, int qty, double price);
    DLLEXPORT void CancelOrderExport(const char* order_token);
    DLLEXPORT void CancelOrderByIDExport(const char* symbol, bool is_buy, uint64_t order_id);
};

#endif //!__TITAN_EXPORT_H__
