//-----------------------------------------------------------------------------
// File Name   : main.cpp
// Author      : junlei
// Date        : 1/27/2020 9:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "trader_client.h"
#include "market_data_client.h"

int testTrade();
int testMarketData();

int main() {
    //testTrade();
    //testMarketData();
}

int testTrade() {
    //const char* flowPath = "trader-0";
    // distinct flow path is needed for each api instance.
    /*
    auto tradeClient = new TraderClient(nullptr, nullptr); // should not be null

    this_thread::sleep_for(1s);
    tradeClient->QueryInstrument("CU3M-LME");
    this_thread::sleep_for(1s);
    tradeClient->InsertOrder("CU3M-LME", true, 3900.0, 3, "");
    this_thread::sleep_for(1s);
    tradeClient->QueryOrder("CU3M-LME");
    //this_thread::sleep_for(1s);
    //tradeClient->replaceOrder("1", 3950.0, 5);
    //this_thread::sleep_for(1s);
    //tradeClient->cancelOrder("1");
    this_thread::sleep_for(1s);
    tradeClient->QueryTrade("CU3M-LME");
    this_thread::sleep_for(1s);
    tradeClient->QueryInvestorPosition("");
    this_thread::sleep_for(1s);

    // Destroy the instance and release resources.
    delete tradeClient;
    */
    return 0;
};


int testMarketData() {
    /*
    auto mdClient = new MarketDataClient(nullptr, nullptr); // wrong: should not be null

    std::this_thread::sleep_for(1s);
    char* symbol = (char*)"CU3M-LME";
    mdClient->SubscribeContract(symbol);
    std::this_thread::sleep_for(1s);
    mdClient->UnsubscribeContract(symbol);
    std::this_thread::sleep_for(10s);

    // Destroy the instance and release resources.
    delete mdClient;
    */
    return 0;
}
