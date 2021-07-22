//-----------------------------------------------------------------------------
// File Name   : AboutVM
// Author      : junlei
// Date        : 7/30/2020 5:12:48 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Reflection;
using Prism.Mvvm;

namespace ThmTPWin.ViewModels {
    internal class AboutVM : BindableBase {
        public string AppTitle { get; }
        public string Description { get; }

        private string _version;
        public string Version {
            get {
                if (IsSemanticVersioning) {
                    var tmp = _version.Split('.');
                    return $"{tmp[0]}.{tmp[1]}.{tmp[2]}.{tmp[3]}";
                }

                return _version;
            }
            set => SetProperty(ref _version, value);
        }

        private bool _isSemanticVersioning;
        public bool IsSemanticVersioning {
            get => _isSemanticVersioning;
            set => SetProperty(ref _isSemanticVersioning, value);
        }

        public string Copyright { get; }
        public string HyperlinkText { get; }
        public string Company { get; }

        public AboutVM() {
            IsSemanticVersioning = true;
            var assembly = Assembly.GetEntryAssembly();
            Version = assembly.GetName().Version.ToString();
            AppTitle = "TTP"; // assembly.GetName().Name;
            Copyright = assembly.GetCustomAttribute<AssemblyCopyrightAttribute>().Copyright;
            //Description = assembly.GetCustomAttribute<AssemblyDescriptionAttribute>().Description;
            Company = assembly.GetCustomAttribute<AssemblyCompanyAttribute>().Company;

            HyperlinkText = "http://www.themeinternationaltrading.com";
        }
    }
}
