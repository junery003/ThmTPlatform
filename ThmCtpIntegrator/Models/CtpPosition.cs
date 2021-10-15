namespace ThmCtpIntegrator.Models {
    public class CtpPosition { // PositionUpdate
        public string Provider { get; } = "CTP";

        //[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 31)]
        public string InstrumentID { get; set; }
        //[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 11)]
        public string BrokerID { get; set; }

        public double PositionCost { get; set; }
        public int Position { get; set; }
        public long Time { get; set; }
    }
}
