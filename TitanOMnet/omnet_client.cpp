//-----------------------------------------------------------------------------
// File Name   : omnet_client.h
// Author      : junlei
// Date        : 12/4/2020 10:05:03 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#include "pch.h"
#include "omnet_client.h"
#include "logger.h"

#include "omex/omn_om_inttypes.h"
#include "omex/omnifact.h"
#include "omex/omni.h"
#include "omex/omex.h"
#include "omex/omniapi.h"

#include <iostream>
#include <fstream>

using namespace std;

const char* const OMnetClient::kAppID{ "ThmOMnetClient01" };

bool OMnetClient::Login(const char* usr, const char* pwd) {
    Logger::Log()->info("[{}:{}] OMnetClient Logining", __func__, __LINE__);

    session_ = (void**)omniapi_create_session();

    omni_login_t login_message;
    memset(&login_message, 0, sizeof(login_message));
    strncpy_s(login_message.gateway_node_s, server_, sizeof(login_message.gateway_node_s));
    login_message.port_u = port_;
    strncpy_s(login_message.user_s, usr, sizeof(login_message.user_s));
    strncpy_s(login_message.pass_s, pwd, sizeof(login_message.pass_s));
    strncpy_s(login_message.appl_ident_s, kAppID, sizeof(login_message.appl_ident_s));

    int32_t tx_status;
    int32_t completion_status = omniapi_login_ex(session_, &tx_status, &login_message);
    if (completion_status == OMNIAPI_SUCCESS) {
        Logger::Log()->info("OMnet login successfully");
        return true;
    }
    else if (completion_status > 0) {
        Logger::Log()->info("Successfully logged in OMnet with completion status={}", completion_status);
        if (completion_status == OMNIAPI_PWD_CHANGE_REQ) {
            Logger::Log()->warn("OMnet Password expired {} {}, {}", session_, completion_status, tx_status);
        }
        else if (completion_status == OMNIAPI_PWD_IMPEND_EXP) {
            Logger::Log()->warn("OMnet login succeeded, but password expiration is impending:{}, {}, {}",
                session_, completion_status, tx_status);
        }

        return true;
    }
    else {
        Logger::Log()->error("Failed to login: {}, status: {}, {}", session_, completion_status, tx_status);
    }

    return false;
}

void OMnetClient::Logout() {
    int32_t tx_status;
    int32_t completion_status = omniapi_logout_ex(session_, &tx_status);
    if (completion_status == OMNIAPI_SUCCESS) {
        Logger::Log()->info("[{}:{}] OMnet logout Successfully.", __func__, __LINE__);
    }
    else {
        Logger::Log()->error("[{}:{}] Failed to logout: {} {}", __func__, __LINE__, completion_status, tx_status);
    }

    omniapi_close_session(session_);
}

int32_t OMnetClient::GetIDBySymbol(const std::string& symbol) {
    auto it = symbol_id_mapping_->find(symbol);
    if (it != symbol_id_mapping_->end()) {
        Logger::Log()->info("[{}:{}] symbol={}, id={}", __func__, __LINE__, symbol, it->second);
        return it->second;
    }

    return 0;
}

std::string OMnetClient::GetSymbolByID(int32_t instrument_id) {
    auto it = id_symbol_mapping_->find(instrument_id);
    if (it != id_symbol_mapping_->end()) {
        Logger::Log()->info("[{}:{}] id={}, symbol={}", __func__, __LINE__, instrument_id, it->second);
        return it->second;
    }

    return  "";
}

bool OMnetClient::InitInstruments(const char* host, uint32_t port, const char* user, const char* pwd) {
    Logger::Log()->info("[{}:{}] Init all instruments..", __func__, __LINE__);

    try {
        memcpy(server_, host, strlen(host));
        port_ = port;

        if (!Login(user, pwd)) {
            return false;
        }

        int32_t ep0;
        if (!GetFacilityType(OMNI_INFTYP_FACTYP_E0, "EP0", &ep0)) {
            throw "Failed to get facility type EP0";
        }

        const char* dp = "DQ124"; //"DQ2"; 
        if (!QueryDelta(ep0, dp)) {
            throw "Failed to get the instrument/order book id mapping";
        }

        Logout();
        return true;  // succsesfully
    }
    catch (const std::exception& e) {
        Logger::Log()->error(e.what());
        Logout();
        return false;
    }
}

/*
This shows the value of a facility type (EP0 or IP0).

Input parameters:
   session              read   Session handle
   facility_type        read   Key for the facility type to read, OMNI_INFTYP_FACTYP_E0 or OMNI_INFTYP_FACTYP_I0
   facility_type_name   read   "EP0" or "IP0"
   facility_type_value  write  The actual value

Return value:
   true if Completion status is sucessful, else false
*/
bool OMnetClient::GetFacilityType(int32_t facility_type, const char* facility_type_name, int32_t* facility_type_value) {
    Logger::Log()->info("[{}:{}] Getting the value of '{}'", __func__, __LINE__, facility_type_name);

    uint32_t factype_size = sizeof(facility_type);
    int32_t tx_status;
    int32_t completion_status = omniapi_get_info_ex(session_,
        &tx_status,
        facility_type,
        &factype_size,
        facility_type_value);

    PUTLONG(*facility_type_value, *facility_type_value);

    if (completion_status == OMNIAPI_SUCCESS) {
        Logger::Log()->info("[{}:{}] Successfully get the value {}={}", __func__, __LINE__,
            facility_type_name, *facility_type_value);
        return true;
    }

    Logger::Log()->error("[{}:{}] Failed to get the value: {}, {}, {}", __func__, __LINE__,
        session_, completion_status, tx_status);
    return false;
}

/*
This function tests the omniapi_query_ex by sending a series query
and just verify that it receives an answer whitout any error

Input parameters:
   session  read  Session handle
   ep0      read  External facility
   dq       read  Name of the series query. E.g. DQ2, DQ152.

Return value:
   The completion status.
*/
// Delta instrument Series query: DQ124 (DQ126) ->> DA124
bool OMnetClient::QueryDelta(int32_t ep0, const char* dq) {
    Logger::Log()->info("[{}:{}] ep0={}, dp={}", __func__, __LINE__, ep0, dq);

    static char rcv_buf[MAX_RESPONSE_SIZE]{ 0 };

    query_delta_t query_data;
    memset(&query_data, 0, sizeof(query_data));

    query_data.transaction_type.central_module_c = std::toupper(dq[0]);
    query_data.transaction_type.server_type_c = std::toupper(dq[1]);
    query_data.transaction_type.transaction_number_n = (uint16_t)atoi(dq + 2);
    PUTSHORT(query_data.transaction_type.transaction_number_n, query_data.transaction_type.transaction_number_n);

    query_data.segment_number_n = 1;
    PUTSHORT(query_data.segment_number_n, query_data.segment_number_n);

    query_data.download_ref_number_q = -1;
    PUTQUAD(query_data.download_ref_number_q, query_data.download_ref_number_q);

    uint32_t rcv_len = sizeof(rcv_buf);
    int32_t tx_status;
    int32_t completion_status = SendQuery(&query_data, sizeof(query_data), ep0, &tx_status, rcv_buf, &rcv_len);
    Logger::Log()->info("[{}:{}] Query status={}.", __func__, __LINE__, completion_status);

    uint16_t segment_number = 1;
    while (completion_status == OMNIAPI_SUCCESS && tx_status >= OMNIAPI_SUCCESS && segment_number > 0) {
        char* msg = (char*)rcv_buf;
        answer_segment_hdr_t* seg_hdr = (answer_segment_hdr_t*)msg;
        msg += sizeof(answer_segment_hdr_t);

        PUTSHORT(seg_hdr->segment_number_n, seg_hdr->segment_number_n);
        PUTSHORT(seg_hdr->items_n, seg_hdr->items_n);
        PUTSHORT(seg_hdr->size_n, seg_hdr->size_n);

        for (int i = 0; i < seg_hdr->items_n; ++i) {
            ParseItem(msg);
        }

        segment_number = seg_hdr->segment_number_n;
        if (segment_number > 0) {
            query_data.segment_number_n = segment_number + 1;
            rcv_len = sizeof(rcv_buf);
            completion_status = SendQuery(&query_data, sizeof(query_data), ep0, &tx_status, rcv_buf, &rcv_len);
        }
    }

    if (completion_status != OMNIAPI_SUCCESS) {
        Logger::Log()->error("[{}:{}] Query failed: completion_status={}, tx_status={}", __func__, __LINE__,
            completion_status, tx_status);

        return false;
    }

    return true;
}

// return the 
void OMnetClient::ParseItem(char*& msg) {
    item_hdr_t* itm_hdr = (item_hdr_t*)msg;
    PUTSHORT(itm_hdr->size_n, itm_hdr->size_n);
    PUTSHORT(itm_hdr->items_n, itm_hdr->items_n);

    msg += sizeof(item_hdr_t);

    int32_t order_book_id{ 0 };
    std::string symbol;

    for (int j = 0; j < itm_hdr->items_n; ++j) {
        sub_item_hdr_t* sub_itm_hdr = (sub_item_hdr*)msg;

        msg += sizeof(sub_item_hdr_t);
        PUTSHORT(sub_itm_hdr->named_struct_n, sub_itm_hdr->named_struct_n);

        switch (sub_itm_hdr->named_struct_n) {
        case 37001:
        { // 
            ns_delta_header_t* delta_hdr = (ns_delta_header_t*)msg;
            PUTQUAD(delta_hdr->download_ref_number_q, delta_hdr->download_ref_number_q);

            download_ref_num_ = delta_hdr->download_ref_number_q;

            msg += sizeof(ns_delta_header_t);
            //ParseItem(msg);

            break;
        }
        case 37002:
        {
            ns_remove_t* remove = (ns_remove*)msg;
            msg += sizeof(ns_remove_t);
            break;
        }
        case 37301:
        { //
            ns_inst_series_basic* series_basic = (ns_inst_series_basic*)msg;
            FormatStr(series_basic->ins_id_s, sizeof(series_basic->ins_id_s), symbol);

            msg += sizeof(ns_inst_series_basic);
            break;
        }
        case 37302:
        {
            ns_inst_series_basic_single_t* basic_single = (ns_inst_series_basic_single_t*)msg;
            msg += sizeof(ns_inst_series_basic_single_t);
            break;
        }
        case 37303:
        {
            ns_inst_series_power_t* power = (ns_inst_series_power_t*)msg;
            msg += sizeof(ns_inst_series_power_t);
            break;
        }
        case 37305:
        {
            ns_inst_series_ext1_t* ext1 = (ns_inst_series_ext1_t*)msg;
            msg += sizeof(ns_inst_series_ext1_t);
            break;
        }
        case 37310:
        { //
            ns_inst_series_id_t* inst_id = (ns_inst_series_id*)msg;
            PUTLONG(inst_id->orderbook_id_i, inst_id->orderbook_id_i);
            order_book_id = inst_id->orderbook_id_i;
            msg += sizeof(ns_inst_series_id_t);
            break;
        }
        default: // skipped and the next sub-item header parsed
        {
            Logger::Log()->warn("[{}:{}] skipped {} (for DA124)", __func__, __LINE__,
                sub_itm_hdr->named_struct_n);
            //msg += sub_itm_hdr->size_n;
            break;
        }
        }
    }

    if (symbol.empty() || order_book_id == 0) {
        //Logger::Log()->info("[{}:{}] no match: order book id {} - symbol '{}'", __func__, __LINE__, order_book_id, symbol);
    }
    else {
        //Logger::Log()->info("[{}:{}] instrument: {} - {}", __func__, __LINE__, symbol, order_book_id);

        id_symbol_mapping_->insert({ order_book_id, symbol });
        symbol_id_mapping_->insert({ symbol , order_book_id });
    }
}

void OMnetClient::FormatStr(char* src, int len, string& dst) {
    for (int i = len - 1; i >= 0; --i) {
        if (src[i] != '\0' && src[i] != ' ') {
            dst = src[i] + dst;
        }
    }
}

// wrapper fun for omniapi_query_ex()
int32_t OMnetClient::SendQuery(void* query_buf, uint32_t query_len, uint32_t facility_type,
    int32_t* tx_status, void* rcv_buf, uint32_t* rcv_len) {
    //Logger::Log()->info("[{}:{}]", __func__, __LINE__);

    static char send_buf[MAX_REQUEST_SIZE]{ 0 };

    omni_message* query_message = (omni_message*)send_buf;
    memcpy(&send_buf[0], &query_len, sizeof(query_len));
    memcpy(&send_buf[sizeof(query_len)], query_buf, query_len);

    uint32_t tx_id[2]{ 0 };
    uint32_t dummy_order_id[2]{ 0 };
    return omniapi_query_ex(session_,
        tx_status,
        facility_type,
        query_message,
        1,            // TRUE == yes, want a reply
        (char*)rcv_buf,
        rcv_len,
        &tx_id[0],
        dummy_order_id);
}

bool OMnetClient::ChangePassword(const char* host, uint32_t port, const char* usr,
    const char* cur_pwd, const char* new_pwd) {

    memcpy(server_, host, strlen(host));
    port_ = port;

    Login(usr, cur_pwd);

    omni_set_password_t set_pwd_data;
    memset(&set_pwd_data, 0, sizeof(set_pwd_data));

    strncpy_s(set_pwd_data.pass_s, cur_pwd, sizeof(set_pwd_data.pass_s));
    strncpy_s(set_pwd_data.new_pass_s, new_pwd, sizeof(set_pwd_data.new_pass_s));

    int32_t tx_status;
    int32_t completion_status = omniapi_set_newpwd_ex(session_, &tx_status, &set_pwd_data);
    Logout();

    if (completion_status != OMNIAPI_SUCCESS) {
        Logger::Log()->error("[{}:{}] Failed to set new password: {}", __func__, __LINE__, completion_status);
        return false;
    }

    Logger::Log()->info("[{}:{}] Successfully set a new password.", __func__, __LINE__);
    return true;
}

// passwords must contain at least one alphabetic character, one special character and one digit character.
// Passwords must not have special characters such as(eg.asterisk, percentage or backslash) or duplicate characters.
// Passwords are not case-sensitive. the length at least 10 
std::string OMnetClient::GeneratePassword() {
    return "";
}
