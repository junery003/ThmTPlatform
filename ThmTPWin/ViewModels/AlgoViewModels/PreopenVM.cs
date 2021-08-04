//-----------------------------------------------------------------------------
// File Name   : PreopenVM
// Author      : junlei
// Date        : 4/28/2020 12:28:38 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

using Prism.Mvvm;

namespace ThmTPWin.ViewModels.AlgoViewModels {
    public class PreopenVM : BindableBase {
        private int _qty;
        public int Qty {
            get => _qty;
            set => SetProperty(ref _qty, value);
        }

        private decimal _price;
        public decimal Price {
            get => _price;
            set => SetProperty(ref _price, value);
        }

        private int _qty2;
        public int Qty2 {
            get => _qty2;
            set => SetProperty(ref _qty2, value);
        }

        private decimal _price2;
        public decimal Price2 {
            get => _price2;
            set => SetProperty(ref _price2, value);
        }

        public PreopenVM() {

        }
    }
}
