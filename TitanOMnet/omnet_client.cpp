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
