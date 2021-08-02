//-----------------------------------------------------------------------------
// File Name   : InterTriggerVM
// Author      : junlei
// Date        : 9/8/2020 6:09:29 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Prism.Mvvm;
using ThmCommon.Handlers;
using ThmCommon.Models;

namespace ThmTPWin.ViewModels.AlgoViewModels {
    public class InterTriggerVM : BindableBase {
        private string _refInstrument;
        public string RefInstrument {
            get => _refInstrument;
            set => SetProperty(ref _refInstrument, value);
        }

        public string Instrument { get; }

        // support ask/bid only
        public static EPriceType[] PriceTypes { get; } = { EPriceType.Bid, EPriceType.Ask };

        private EPriceType _refPriceType = EPriceType.Bid;
        public EPriceType RefPriceType {
            get => _refPriceType;
            set => SetProperty(ref _refPriceType, value);
        }

        public EOperator RefTriggerOp => RefOperator == ">=" ? EOperator.GreaterET : EOperator.LessET;
        public static string[] Operators { get; } = { ">=", "<=" };
        private string _refOperator = Operators[0];
        public string RefOperator {
            get => _refOperator;
            set => SetProperty(ref _refOperator, value);
        }

        private decimal _refPrice;
        public decimal RefPrice {
            get => _refPrice;
            set => SetProperty(ref _refPrice, value);
        }

        public InstrumentHandlerBase RefInstrumentHandler { get; set; }

        public InterTriggerVM(string instrument) {
            Instrument = instrument;
        }

        internal bool UpdateRefInstrument(string refInstrument, out string err) {
            err = string.Empty;
            if (!string.IsNullOrWhiteSpace(Instrument) && Instrument == refInstrument) {
                err = "Instrument and reference instrument cannot be the same";
                return false;
            }

            RefInstrument = refInstrument;
            return true;
        }

        internal bool Check(out string err) {
            if (RefInstrumentHandler == null) {
                err = "The reference instrument is not specified";
                return false;
            }

            err = string.Empty;
            if (decimal.Compare(RefPrice, 0) <= 0) {
                err = "The ref price is not correct";
                return false;
            }

            return true;
        }
    }
}
