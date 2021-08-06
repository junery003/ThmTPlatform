using System;

namespace ThmAtpIntegrator.Models {
    [Serializable]
    //[StructLayout(LayoutKind.Sequential, Pack = 1)] //if using these, memory goes off
    public class AtpPosition { // PositionUpdate
        public string Provider { get; } = "ATP";

        //[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 31)]
        public string InstrumentID { get; set; }
        //[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 11)]
        public string BrokerID { get; set; }

        public double PositionCost { get; set; }
        public int Position { get; set; }
        public long Time { get; set; }
    }
}
