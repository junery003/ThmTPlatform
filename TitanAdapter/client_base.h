//-----------------------------------------------------------------------------
// File Name   : client_base.h
// Author      : junlei
// Date        : 11/15/2020 12:05:03 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
#ifndef __CLIENT_BASE_H__
#define __CLIENT_BASE_H__

class ClientBase {
public:
    virtual ~ClientBase() = default;

    virtual bool Start() = 0;
    virtual void Stop() = 0;
};

#endif //!__CLIENT_BASE_H__
