//-----------------------------------------------------------------------------
// File Name   : main.cpp
// Author      : junlei
// Date        : 11/3/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "titan_client.h"
#include "logger.h"

#include <iostream>
#include <thread>

using namespace std;
void TestClient();

int main() {
    Logger::Log()->info("[{}:{}] starting", __func__, __LINE__);

    TestClient();

    std::cout << "exit\n";
    return 0;
}

void TestClient() {
    TitanClient client;

    if (!client.Start()) {
        return;
    }

    //client.ChangePassword("TEIT01", "Sunday@1234", "Sunday@124");

    while (true) {
        static int tmp = 10;
        this_thread::sleep_for(20s);
        //client.AddOrder("FEFJ21", false, 190.5 + tmp, 10 + tmp);
        cout << ".";
        tmp += 2;
    }
}

void TestThread() {
    std::jthread t{ []() {
        static int i = 0;
        while (true) {
            this_thread::sleep_for(300ms);
            std::cout << ++i << "\n";
        }
    } };

    t.join();
}

// ---------------------------------------------------;
#include "boost/asio.hpp"

//#include <coroutine>
#include <future>
#include <string>
using namespace boost;
using namespace boost::asio;

void TestIO() {
    std::promise<std::string> p;
    auto f = p.get_future();

    io_context io;
    io.post([&] { p.set_value("42"); });
    io.run();

    std::cout << f.get();
}
