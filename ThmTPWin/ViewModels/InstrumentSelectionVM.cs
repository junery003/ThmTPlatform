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
        public List<EProviderType> Providers { get; } = new();

        private EProviderType _selectedProvider;
        public EProviderType SelectedProvider {
            get => _selectedProvider;
            set {
                if (SetProperty(ref _selectedProvider, value)) {
                    Exchanges.Clear();
                    ConnManager.GetExchanges(_selectedProvider)?.ForEach(exch => {
                        Exchanges.Add(exch);
                    });
                }
            }
        }

        public ObservableCollection<ExchangeCfg> Exchanges { get; } = new();

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

        public ObservableCollection<string> ProductTypes { get; } = new();

        private string _selectedProductType;
        public string SelectedProductType {
            get => _selectedProductType;
            set {
                if (SetProperty(ref _selectedProductType, value)) {
                    Products.Clear();
                    SelectedExchange?.Products.ForEach(x => {
                        if (SelectedExchange.Type == _selectedProductType) {
                            Products.Add(x);
                        }
                    });
                }
            }
        }

        public ObservableCollection<ProductCfg> Products { get; } = new();

        private ProductCfg _selectedProduct;
        public ProductCfg SelectedProduct {
            get => _selectedProduct;
            set {
                if (SetProperty(ref _selectedProduct, value)) {
                    Contracts.Clear();

                    foreach (var cntrct in _selectedProduct.Contracts) {
                        Contracts.Add(cntrct);
                    }
                }
            }
        }

        public ObservableCollection<string> Contracts { get; } = new();

        private string _selectedContract;
        public string SelectedContract {
            get => _selectedContract;
            set => SetProperty(ref _selectedContract, value);
        }

        internal InstrumentSelectionVM() {
            ConnManager.GetProviders()?.Keys?.ToList().ForEach(x => Providers.Add(x));
        }

        internal InstrumentHandlerBase GetInstrumentHandler(out string err) {
            if (SelectedExchange == null || SelectedProduct == null || SelectedContract == null) {
                err = "No contract was selected.";
                return null;
            }

            err = string.Empty;
            return ConnManager.GetInstrumentHandler(SelectedExchange.Market,
                SelectedProductType,
                SelectedProduct.Name,
                SelectedContract);
        }
    }
}
