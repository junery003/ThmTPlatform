//-----------------------------------------------------------------------------
// File Name   : BaseTradeParaVM
// Author      : junlei
// Date        : 10/12/2020 6:34:00 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Collections.Generic;
using System.Windows.Media;
using Prism.Mvvm;
using ThmCommon.Models;
using ThmTPWin.Controllers;
using ThmTPWin.ViewModels.AlgoViewModels;

namespace ThmTPWin.ViewModels {
    public class BaseTradeParaVM : BindableBase {
        public List<EAlgoType> AllAlgos { get; }
        public List<string> Accounts { get; }

        public TriggerVM TriggerVm { get; }
        public InterTriggerVM InterTriggerVm { get; }

        private string _selectedAccount;
        public string SelectedAccount {
            get => _selectedAccount;
            set {
                if (SetProperty(ref _selectedAccount, value)) {
                    if (_selectedAccount != null) {
                        _parent.InstrumentHandler.SetAccount(_selectedAccount);
                    }
                }
            }
        }

        private EAlgoType _selectedAlgoType = EAlgoType.Limit;
        public EAlgoType SelectedAlgoType {
            get => _selectedAlgoType;
            set {
                if (SetProperty(ref _selectedAlgoType, value)) {
                    //_parent.DispalyAlgoView(_selectedAlgoType);
                }
            }
        }

        private int _position = 0;
        public int Position {
            get => _position;
            set {
                if (SetProperty(ref _position, value)) {
                    if (_position == 0) {
                        PositionBackground = Brushes.White;
                        return;
                    }

                    PositionBackground = _position > 0 ? Brushes.DodgerBlue : Brushes.Crimson;
                }
            }
        }

        private Brush _positionBackground = Brushes.White;
        public Brush PositionBackground {
            get => _positionBackground;
            set => SetProperty(ref _positionBackground, value);
        }

        private int _qty;
        public int Quantity {
            get => _qty;
            set {
                if (SetProperty(ref _qty, value)) {
                    if (_qty > RiskManager.MaxSizePerTrade) {
                        QtyBackground = Brushes.OrangeRed;
                        QtyTip = "Max quantity is " + RiskManager.MaxSizePerTrade;
                    }
                    else {
                        QtyBackground = Brushes.White;
                        QtyTip = null;
                    }
                }
            }
        }

        private string _qtyTip;
        public string QtyTip {
            get => _qtyTip;
            set => SetProperty(ref _qtyTip, value);
        }

        private Brush _qtyBackground = Brushes.White;
        public Brush QtyBackground {
            get => _qtyBackground;
            set => SetProperty(ref _qtyBackground, value);
        }

        private int _minQty;
        public int MinQuantity {
            get => _minQty;
            set => SetProperty(ref _minQty, value);
        }

        public int _workingAlgoCount = 0;
        public int WorkingAlgoCount {
            get => _workingAlgoCount;
            set => SetProperty(ref _workingAlgoCount, value);
        }

        private string _cancelAlgoBtnContent = "CXL Algo(s)";
        public string CancelAlgoBtnContent {
            get => _cancelAlgoBtnContent;
            set => SetProperty(ref _cancelAlgoBtnContent, value);
        }

        private readonly ITraderTabItm _parent;
        internal BaseTradeParaVM(ITraderTabItm parent, List<EAlgoType> algos) {
            _parent = parent;

            Accounts = parent.InstrumentHandler.Accounts;
            SelectedAccount = parent.InstrumentHandler.CurAccount;

            TriggerVm = new TriggerVM();
            InterTriggerVm = new InterTriggerVM(parent.InstrumentInfo.InstrumentID);

            AllAlgos = algos;
            SelectedAlgoType = AllAlgos[0];
        }

        internal void ResetQuantity() {
            Quantity = MinQuantity;
        }
    }
}
