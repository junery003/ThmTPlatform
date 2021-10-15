//-----------------------------------------------------------------------------
// File Name   : IConnector
// Author      : junlei
// Date        : 5/29/2020 9:50:20 AM
// Description : 
// Version     : 1.0.0
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using ThmCommon.Config;

namespace ThmCommon.Handlers {
    public interface IConnector : IDisposable {
        bool IsConnected { get; }
        bool Connect(LoginCfgBase loginCfg = null);
        //IAccount GetAccount();
        bool StartContract(string instrumentID, string exchange = null);
        bool StopContract(string instrumentID);
        void StartContracts();

        //InstrumentHandlerBase GetInstrumentHandler(string market, string productType, string product, string contract);
        InstrumentHandlerBase GetInstrumentHandler(string instrumentID);

        List<string> GetInstruments(string market, string productType, string product);
        IConfigHelper GetConfigHelper();

        bool ChangePassword(string usrId, string curPwd, string newPwd);
    }
}
