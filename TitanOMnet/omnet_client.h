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
#include <unordered_map>

#define DLLEXPORT __declspec(dllexport)

class DLLEXPORT OMnetClient {
public:
    static OMnetClient& Instance() {
        static OMnetClient client;
        return client;
    }

private:
    OMnetClient() {}

    ~OMnetClient() {
        delete id_symbol_mapping_;
        delete symbol_id_mapping_;
        //Logout();
    }

public:
    bool ChangePassword(const char* host, uint32_t port, const char* usr, const char* cur_pwd,
        const char* new_pwd);

private:
    bool InitInstruments(const char* host, uint32_t port, const char* user, const char* pwd);

    int32_t GetIDBySymbol(const std::string& symbol);
    std::string GetSymbolByID(int32_t instrument_id);

private:
    bool Login(const char* usr, const char* pwd);
    void Logout();

    int32_t SendQuery(void* query_buf, uint32_t query_len, uint32_t facility_type,
        int32_t* tx_status, void* rcv_buf, uint32_t* rcv_len);
    bool QueryDelta(int32_t ep0, const char* dq);

    bool GetFacilityType(int32_t facility_type, const char* facility_type_name,
        int32_t* facility_type_value);

    std::string GeneratePassword();

    int64_t NextDownloadRefNum() {
        return ++download_ref_num_;
    }

    void ParseItem(char*& msg);

    static void FormatStr(char* src, int len, std::string& dst);

private:
    static const char* const kAppID;

    char server_[128]{ 0 };
    uint32_t port_;
    char user_[32]{ 0 };
    char pwd_[32]{ 0 };

    void* session_{ nullptr };  // omniapi_session_handle session_{ nullptr };
    int64_t download_ref_num_{ 0 };

    std::unordered_map<int32_t, std::string>* id_symbol_mapping_{ new std::unordered_map<int32_t, std::string>() };
    std::unordered_map<std::string, int32_t>* symbol_id_mapping_{ new std::unordered_map<std::string, int32_t>() };
};

#endif // !__OMNET_CLIENT_H__
