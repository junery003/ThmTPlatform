//-----------------------------------------------------------------------------
// File Name   : ConnectorManager
// Author      : junlei
// Date        : 12/9/2020 5:03:20 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using ThmAtpIntegrator.AtpFunctions;
using ThmCommon.Config;
using ThmCommon.Handlers;
using ThmTitanIntegrator.TitanFunctions;
using ThmTTIntegrator.TTHandler;

namespace ThmTPWin.Controllers {
    internal class ConnectorManager : IDisposable {
        internal ThmConfigHelper ThmCfgHelper { get; } = new ThmConfigHelper();
        internal ThmConfig ThmCfg => (ThmConfig)ThmCfgHelper.GetConfig();

        private readonly Dictionary<EProviderType, IConnector> _connectors = new Dictionary<EProviderType, IConnector>();

        internal ConnectorManager() {
        }

        internal void Load() {
            if (!ThmCfgHelper.LoadConfig()) {
                throw new Exception("Failed to load config file or user is not valid.");
            }
        }

        // one provide should have one connection
        internal bool AddConnector(EProviderType provider, IConnector connector) {
            if (_connectors.ContainsKey(provider)) {
                return false;
            }

            _connectors[provider] = connector;
            return true;
        }

        internal IConnector GetConnector(EProviderType provider) {
            if (!_connectors.ContainsKey(provider)) {
                throw new Exception("No provider specified: " + provider);
            }

            return _connectors[provider];
        }

        internal IConfig GetConfig(EProviderType provider) {
            if (_connectors.ContainsKey(provider)) {
                return _connectors[provider].GetConfigHelper().GetConfig();
            }

            throw new Exception("No config was defined");
        }

        internal List<EProviderType> GetProviders() {
            var providers = new List<EProviderType>();

            if (IsEnabled(EProviderType.ATP)) {
                providers.Add(EProviderType.ATP);
            }

            if (IsEnabled(EProviderType.TT)) {
                providers.Add(EProviderType.TT);
            }

            if (IsEnabled(EProviderType.TITAN)) {
                providers.Add(EProviderType.TITAN);
            }

            return providers;
        }

        internal bool IsEnabled(EProviderType provider) {
            if (_connectors.ContainsKey(provider)
                 && _connectors[provider].GetConfigHelper().GetConfig().Enabled) {
                return true;
            }

            return false;
        }

        internal void Enable(EProviderType provider, bool enabled = true) {
            if (_connectors.ContainsKey(provider)) {
                _connectors[provider].GetConfigHelper().GetConfig().Enabled = enabled;
            }
        }

        internal List<ExchangeCfg> GetExchanges(EProviderType provider) {
            var conn = _connectors[provider].GetConfigHelper();
            switch (provider) {
            case EProviderType.TT: {
                return ((TTConfig)conn.GetConfig()).Exchanges;
            }
            case EProviderType.ATP: {
                return ((AtpConfig)conn.GetConfig()).Exchanges;
            }
            case EProviderType.TITAN: {
                return ((TitanConfig)conn.GetConfig()).Exchanges;
            }
            default: {
                return null;
            }
            }
        }

        internal void SaveConfig() {
            foreach (var conn in _connectors.Values) {
                conn.GetConfigHelper().SaveConfig();
            }
        }

        public void Dispose() {
            foreach (var conn in _connectors.Values) {
                conn.Dispose();
            }
        }
    }
}
