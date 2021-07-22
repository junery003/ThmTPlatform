
// not used
namespace ThmCommon.Model {
    public class DomDisplay {
        public string Provider { get; private set; }
        public string Exchange { get; private set; } //e.g. SGX, DC

        public int ImpliedBidSize { get; private set; }
        public int BidSize { get; private set; }
        public double Level { get; set; }
        public int AskSize { get; private set; }
        public int ImpliedAskSize { get; private set; }

        public int LastTradedQty { get; set; }
        //public bool isLastTrade = false;
        //public bool isMidRate = false;

        public int WorkingQty { get; set; }
        public int PartialFillQty { get; set; }
        public int WorkingAlgos { get; set; }

        private int resetTimes = 0;
        public void ResetSizes() {
            if (resetTimes % 3 == 0) {
                BidSize = (0);
                AskSize = (0);

                WorkingAlgos = 0;
                WorkingQty = 0;
                PartialFillQty = 0;
            }
            else {
                resetTimes += 1;
            }
        }

        //public void ResetLevels() {
        //    this.isLastTrade = false;
        //    this.isMidRate = false;
        //}
    }
}

