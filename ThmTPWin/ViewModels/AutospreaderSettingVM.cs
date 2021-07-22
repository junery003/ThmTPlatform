//-----------------------------------------------------------------------------
// File Name   : AutospreaderSettingVM
// Author      : junlei
// Date        : 10/15/2020 9:47:05 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.ObjectModel;
using Prism.Commands;
using Prism.Mvvm;
using ThmCommon.Models;
using ThmCommon.Utilities;

namespace ThmTPWin.ViewModels {
    public class AutospreaderSettingVM : BindableBase {
        public static ObservableCollection<AutospeaderParas> ASParaList { get; } = new ObservableCollection<AutospeaderParas>();

        private static int _count = 0;

        private AutospeaderParas _selectedASPara;
        public AutospeaderParas SelectedASPara {
            get => _selectedASPara;
            set => SetProperty(ref _selectedASPara, value);
        }

        public DelegateCommand CreateCmd { get; }
        public DelegateCommand DeleteCmd { get; }
        public AutospreaderSettingVM() {
            CreateCmd = new DelegateCommand(CreateAutospreader);
            DeleteCmd = new DelegateCommand(DeleteAutospreader);
        }

        internal bool Check(out string err) {
            if (SelectedASPara == null) {
                err = "Please select an autospreader to continue.";
                return false;
            }

            return SelectedASPara.Check(out err);
        }

        internal void CreateAutospreader() {
            ASParaList.Add(new AutospeaderParas() {
                Name = $"autospreader {++_count}"
            });
        }

        internal void DeleteAutospreader() {
            if (SelectedASPara != null) {
                ASParaList.Remove(SelectedASPara);
            }
        }
    }

    // autospreader item infor
    public class AutospeaderParas : BindableBase {
        private string _name;
        public string Name {
            get => _name;
            set => SetProperty(ref _name, value);
        }

        public DateTime DateTime { get; }

        private string _info;
        public string Info {
            get => _info;
            set => SetProperty(ref _info, value);
        }

        // if not enabled, cannot changed the ASParaDetails
        private bool _isEnabled = true;
        public bool IsEnabled {
            get => _isEnabled;
            set => SetProperty(ref _isEnabled, value);
        }

        public ObservableCollection<AutospeaderLeg> ASLegs { get; } // only two

        private readonly ThmInstrumentInfo _instrumentInfo;
        public ThmInstrumentInfo InstrumentInfo {
            get {
                ComposeInfo();
                return _instrumentInfo;
            }
        }

        private void ComposeInfo() {
            var id = string.Empty;
            foreach (var leg in ASLegs) {
                if (leg.InstrumentHandler == null) {
                    continue;
                }

                if (leg.IsActiveQuoting) {
                    id += $"{leg.Multiplier}x{leg.InstrumentHandler.InstrumentInfo.InstrumentID}v ";
                }
                else {
                    id += $"{leg.Multiplier}x{leg.InstrumentHandler.InstrumentInfo.InstrumentID} ";
                }
            }

            _instrumentInfo.InstrumentID = id.Trim();
        }

        public AutospeaderParas() {
            _instrumentInfo = new ThmInstrumentInfo {
                Provider = "TTP",
                Exchange = "TTP",
                Type = "Synthetic",
                InstrumentID = ThmUtil.GenerateGUID()
            };

            // only support two by far
            ASLegs = new ObservableCollection<AutospeaderLeg>() {
                new AutospeaderLeg() {
                    Name = "Leg 1",
                    Multiplier = 1,
                    Ratio = 1,
                    IsActiveQuoting = true
                },
                new AutospeaderLeg() {
                    Name = "Leg 2",
                    Multiplier = -1,
                    Ratio = -1,
                    IsActiveQuoting = false
                }
            };

            DateTime = DateTime.Now;
        }

        public bool Check(out string err) {
            if (ASLegs.Count != 2) {
                err = "Only two legs supported.";
                return false;
            }

            var para1 = ASLegs[0];
            var para2 = ASLegs[1];
            if (para1.InstrumentHandler == null || para2.InstrumentHandler == null) {
                err = "Please specify a contract for each leg.";
                return false;
            }

            if (para1.InstrumentHandler.InstrumentInfo.InstrumentID == para2.InstrumentHandler.InstrumentInfo.InstrumentID) {
                err = "Please specify different contracts.";
                return false;
            }

            if (para1.IsActiveQuoting == para2.IsActiveQuoting) {
                err = "One and only one leg has to be Active Quoting";
                return false;
            }

            Info = InstrumentInfo.InstrumentID;
            err = string.Empty;
            return true;
        }
    }
}
