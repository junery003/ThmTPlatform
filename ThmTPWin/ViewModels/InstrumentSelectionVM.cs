//-----------------------------------------------------------------------------
// File Name   : InstrumentSelectionVM
// Author      : junlei
// Date        : 4/22/2020 5:02:32 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Prism.Mvvm;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using ThmCommon.Config;
using ThmCommon.Handlers;
using ThmTPWin.Controllers;

namespace ThmTPWin.ViewModels {
    public class InstrumentSelectionVM : BindableBase {
        public List<EProviderType> Providers { get; }

        private EProviderType _selectedProvider;
        public EProviderType SelectedProvider {
            get => _selectedProvider;
            set {
                if (SetProperty(ref _selectedProvider, value)) {
                    Exchanges.Clear();
                    ConnManager.GetExchanges(_selectedProvider)?.ForEach(x => {
                        if (x.Enabled) {
                            Exchanges.Add(x);
                        }
                    });
                }
            }
        }

        public ObservableCollection<ExchangeCfg> Exchanges { get; } = new ObservableCollection<ExchangeCfg>();

        private ExchangeCfg _selectedExchange;
        public ExchangeCfg SelectedExchange {
            get => _selectedExchange;
            set {
                if (SetProperty(ref _selectedExchange, value)) {
                    ProductTypes.Clear();
                    if (_selectedExchange != null) {
                        ProductTypes.Add(_selectedExchange.Type);
                    }
                }
            }
        }

        public ObservableCollection<string> ProductTypes { get; } = new ObservableCollection<string>();

        private string _selectedProductType;
        public string SelectedProductType {
            get => _selectedProductType;
            set {
                if (SetProperty(ref _selectedProductType, value)) {
                    Products.Clear();
                    SelectedExchange?.Contracts.ToList().ForEach(x => {
                        Products.Add(x);
                    });
                }
            }
        }

        public ObservableCollection<string> Products { get; } = new ObservableCollection<string>();

        private string _selectedProduct;
        public string SelectedProduct {
            get => _selectedProduct;
            set {
                if (SetProperty(ref _selectedProduct, value)) {
                    Contracts.Clear();

                    _curConn = ConnManager.GetConnector(SelectedProvider);
                    if (_curConn != null && SelectedExchange != null && SelectedProductType != null && _selectedProduct != null) {
                        var instruments = _curConn.GetInstruments(SelectedExchange.Market, SelectedProductType, _selectedProduct);

                        instruments?.ForEach(x => {
                            Contracts.Add(x);
                        });
                    }
                }
            }
        }

        public ObservableCollection<string> Contracts { get; } = new ObservableCollection<string>();

        private string _selectedContract;
        public string SelectedContract {
            get => _selectedContract;
            set => SetProperty(ref _selectedContract, value);
        }

        private IConnector _curConn;
        internal InstrumentSelectionVM() {
            Providers = ConnManager.GetProviders();
        }

        internal InstrumentHandlerBase GetInstrumentHandler(out string err) {
            if (SelectedExchange == null || SelectedProduct == null || SelectedContract == null) {
                err = "No contract was selected.";
                return null;
            }

            if (_curConn != null && SelectedExchange != null) {
                err = string.Empty;
                return _curConn.GetInstrumentHandler(SelectedExchange.Market, SelectedProductType,
                    SelectedProduct, SelectedContract);
            }

            err = "No instruement handler found.";
            return null;
        }
    }
}
