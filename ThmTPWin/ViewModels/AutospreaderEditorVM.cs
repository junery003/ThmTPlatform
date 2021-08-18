//-----------------------------------------------------------------------------
// File Name   : AutospreaderEditorVM
// Author      : junlei
// Date        : 5/03/2021 5:47:05 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Prism.Mvvm;
using System.Collections.ObjectModel;
using ThmCommon.Models;

namespace ThmTPWin.ViewModels {
    internal class AutospreaderEditorVM : BindableBase {
        public ObservableCollection<AutospeaderLeg> ASLegs { get; }
        public AutospreaderEditorVM(string asName, bool isEnabled, ObservableCollection<AutospeaderLeg> asLegs) {
            SpreadName = asName;
            IsEnabled = isEnabled;
            ASLegs = asLegs;
        }

        private string _spreadName;
        public string SpreadName {
            get => _spreadName;
            set => SetProperty(ref _spreadName, value);
        }

        private bool _isEnabled;
        public bool IsEnabled {
            get => _isEnabled;
            set => SetProperty(ref _isEnabled, value);
        }
    }

    // autospreader paremeters
    public class AutospeaderLeg : BindableBase {
        private string _name;
        public string Name {
            get => _name;
            set => SetProperty(ref _name, value);
        }

        private ThmInstrumentInfo _instrumentHandler;  // contract
        public ThmInstrumentInfo InstrumentHandler {
            get => _instrumentHandler;
            set { SetProperty(ref _instrumentHandler, value); }
        }

        private decimal _ratio = 1;
        public decimal Ratio {
            get => _ratio;
            set => SetProperty(ref _ratio, value);
        }

        private decimal _multiplier = 1;
        public decimal Multiplier {
            get => _multiplier;
            set => SetProperty(ref _multiplier, value);
        }

        private bool _isActiveQuoting = true;
        public bool IsActiveQuoting {
            get => _isActiveQuoting;
            set => SetProperty(ref _isActiveQuoting, value);
        }

        private int _payupTicks = 0;
        public int PayupTicks {
            get => _payupTicks;
            set => SetProperty(ref _payupTicks, value);
        }
    }
}
