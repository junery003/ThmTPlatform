//-----------------------------------------------------------------------------
// File Name   : titan_export.cpp
// Author      : junlei
// Date        : 12/3/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "titan_export.h"
#include "titan_client.h"

#include <memory>
using namespace std;

unique_ptr<TitanClient> kClient = nullptr;
bool InitExport() {
    if (kClient == nullptr) {
        kClient = make_unique<TitanClient>();
    }

    return kClient->Start();
}

void DismentalExport() {
    kClient->Stop();
}

bool ChangePasswordExport(const char* usr, const char* cur_pwd, const char* new_pwd) {
    return kClient->ChangePassword(usr, cur_pwd, new_pwd);
}

// -----------------------------------------------------------------------------------------------;
void SubscribeContractExport(const char* symbol) {
    kClient->Subscribe(symbol);
}

void UnsubscribeContractExport(const char* symbol) {
    kClient->Unsubscribe(symbol);
}

void SetAccountExport(const char* account) {
    kClient->SetAccount(account);
}

// -----------------------------------------------------------------------------------------------;
// add order
void AddOrderExport(const char* symbol, bool is_buy, double price, int qty, int tif) {
    kClient->AddOrder(symbol, is_buy, price, qty, tif);
}

// -----------------------------------------------------------------------------------------------;
// replace order
void ReplaceOrderExport(const char* symbol, const char* ori_order_token, int qty, double price) {
    kClient->ReplaceOrder(symbol, ori_order_token, price, qty);
}

// cancel order
void CancelOrderExport(const char* order_token) {
    kClient->CancelOrder(order_token);
}

// cancel order by ID
void CancelOrderByIDExport(const char* symbol, bool is_buy, uint64_t order_id) {
    kClient->CancelOrderByID(symbol, is_buy, order_id);
}
