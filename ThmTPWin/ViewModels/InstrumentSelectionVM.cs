//-----------------------------------------------------------------------------
// File Name   : InstrumentSelectionVM
// Author      : junlei
// Date        : 4/22/2020 5:02:32 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using Prism.Mvvm;
using ThmCommon.Config;
using ThmCommon.Handlers;
using ThmTPWin.Controllers;

namespace ThmTPWin.ViewModels {
    public class InstrumentSelectionVM : BindableBase {
        public List<EProviderType> Providers { get; private set; }

        private EProviderType _selectedProvider;
        public EProviderType SelectedProvider {
            get => _selectedProvider;
            set {
                if (SetProperty(ref _selectedProvider, value)) {
                    Exchanges.Clear();
                    _connMgr.GetExchanges(_selectedProvider)?.ForEach(x => {
                        if (x.Enabled) {
                            Exchanges.Add(x);
                        }
                    });
                }
            }
        }

        private ObservableCollection<ExchangeCfg> _exchanges = new ObservableCollection<ExchangeCfg>();
        public ObservableCollection<ExchangeCfg> Exchanges {
            get => _exchanges;
            set => SetProperty(ref _exchanges, value);
        }

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

        private ObservableCollection<string> _productTypes = new ObservableCollection<string>();
        public ObservableCollection<string> ProductTypes {
            get => _productTypes;
            set => SetProperty(ref _productTypes, value);
        }

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

        private ObservableCollection<string> _products = new ObservableCollection<string>();
        public ObservableCollection<string> Products {
            get => _products;
            set => SetProperty(ref _products, value);
        }

        private string _selectedProduct;
        public string SelectedProduct {
            get => _selectedProduct;
            set {
                if (SetProperty(ref _selectedProduct, value)) {
                    Contracts.Clear();

                    _curConn = _connMgr.GetConnector(SelectedProvider);
                    if (_curConn != null && SelectedExchange != null && SelectedProductType != null && _selectedProduct != null) {
                        var instruments = _curConn.GetInstruments(SelectedExchange.Market, SelectedProductType, _selectedProduct);

                        instruments?.ForEach(x => {
                            Contracts.Add(x);
                        });
                    }
                }
            }
        }

        private ObservableCollection<string> _contracts = new ObservableCollection<string>();
        public ObservableCollection<string> Contracts {
            get => _contracts;
            set => SetProperty(ref _contracts, value);
        }

        private string _selectedContract;
        public string SelectedContract {
            get => _selectedContract;
            set => SetProperty(ref _selectedContract, value);
        }

        private readonly ConnectorManager _connMgr;
        private IConnector _curConn;
        internal InstrumentSelectionVM(ConnectorManager connMgr) {
            _connMgr = connMgr;

            Providers = connMgr.GetProviders();
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
