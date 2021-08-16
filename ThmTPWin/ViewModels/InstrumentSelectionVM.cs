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
using ThmCommon.Config;
using ThmCommon.Handlers;
using ThmTPWin.Controllers;

namespace ThmTPWin.ViewModels {
    public class InstrumentSelectionVM : BindableBase {
        public List<EProviderType> Providers { get; } = new();

        private EProviderType _selectedProvider;
        public EProviderType SelectedProvider {
            get => _selectedProvider;
            set {
                if (SetProperty(ref _selectedProvider, value)) {
                    Exchanges.Clear();
                    _providers[_selectedProvider]?.ForEach(x => {
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
                    SelectedExchange?.Products.ForEach(x => {
                        Products.Add(x);
                    });
                }
            }
        }

        public ObservableCollection<ProductCfg> Products { get; } = new();

        private string _selectedProduct;
        public string SelectedProduct {
            get => _selectedProduct;
            set {
                if (SetProperty(ref _selectedProduct, value)) {
                    Contracts.Clear();

                    foreach (var prod in Products) {
                        if (prod.Name == SelectedProduct) {
                            foreach (var cntrct in prod.Contracts) {
                                Contracts.Add(cntrct);
                            }
                            break;
                        }
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
        private readonly Dictionary<EProviderType, List<ExchangeCfg>> _providers;
        internal InstrumentSelectionVM() {
            _providers = ConnManager.GetProviders();
            foreach (var p in _providers) {
                Providers.Add(p.Key);
            }
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
