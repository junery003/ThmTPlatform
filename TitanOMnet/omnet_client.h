//-----------------------------------------------------------------------------
// File Name   : omnet_client.h
// Author      : junlei
// Date        : 12/4/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __OMNET_CLIENT_H__
#define __OMNET_CLIENT_H__

#include <string>

#define DLLEXPORT __declspec(dllexport)

class DLLEXPORT OMnetClient {
public:
    static OMnetClient& Instance() {
        static OMnetClient client;
        return client;
    }

private:
    OMnetClient() {}

public:
    bool ChangePassword(const char* host, uint32_t port,
        const char* usr,
        const char* cur_pwd,
        const char* new_pwd);

private:
    bool Login(const char* usr, const char* pwd);
    void Logout();

    std::string GeneratePassword();

private:
    static const char* const kAppID;

    char server_[128]{ 0 };
    uint32_t port_;
    char user_[32]{ 0 };
    char pwd_[32]{ 0 };

    void* session_{ nullptr };  // omniapi_session_handle session_{ nullptr };
};

#endif // !__OMNET_CLIENT_H__
