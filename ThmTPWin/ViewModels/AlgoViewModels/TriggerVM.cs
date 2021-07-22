//-----------------------------------------------------------------------------
// File Name   : TriggerVM
// Author      : junlei
// Date        : 4/28/2020 12:27:30 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using Prism.Mvvm;
using ThmCommon.Models;
using ThmCommon.Utilities;

namespace ThmTPWin.ViewModels.AlgoViewModels {
    internal class TriggerVM : BindableBase {
        public EOperator Operator => SelectedOperator == ">=" ? EOperator.GreaterET : EOperator.LessET;
        //public EOrderDirection BuySell => SelectedBuyOrSell == "Buy" ? EOrderDirection.Buy : EOrderDirection.Sell;

        public EPriceType PriceType => (EPriceType)Enum.Parse(typeof(EPriceType), SelectedPriceType, true);

        public static string[] PriceTypes => ThmUtil.EnumItems2Strings<EPriceType>();

        private string _selectedPriceType = ThmUtil.Enum2String(EPriceType.OppositeSide);
        public string SelectedPriceType {
            get => _selectedPriceType;
            set => SetProperty(ref _selectedPriceType, value);
        }

        public static string[] QtyOrOthers { get; } = { "Qty" };

        private string _selectedQtyOrOther = QtyOrOthers[0];
        public string SelectedQtyOrOther {
            get => _selectedQtyOrOther;
            set => SetProperty(ref _selectedQtyOrOther, value);
        }

        public static string[] Operators { get; } = { "<=", ">=" };

        private string _selectedOperator = Operators[0];
        public string SelectedOperator {
            get => _selectedOperator;
            set => SetProperty(ref _selectedOperator, value);
        }

        private int _qty = 20;
        public int Qty {
            get => _qty;
            set => SetProperty(ref _qty, value);
        }
    }
}
