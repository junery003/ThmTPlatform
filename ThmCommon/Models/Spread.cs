using System.Collections.Concurrent;
using System.Collections.Generic;

// not used
namespace ThmCommon.Models {
    public enum LegOrderState {
        FormulaOnly = 0,
        NotSent = 1,
        Sent = 2,

        PartiallyFilled = 3,

        FirstFilled = 4,
        FullyFilled = 5,
        OverFill = 6,
    }

    public enum SpreadState {
        Unknown = 0,
        Reset = 1,
        MainNotSent = 2,
        MainSent = 3,
        MainError = 4,

        MainFirstFullLeanNotsent = 5,
        MainFirstFullLeanSent = 6,
        MainFirstFullLeanPartial = 7,

        //To keep tracking new fill orders from main partial
        MainPartialLeanToContinueLeanNotSent = 8,
        MainPartialLeanToContinueLeanSent = 9,
        MainPartialLeanToContinueLeanPartial = 10,
        MainPartialLeanToContinueLeanFull = 11,

        //caters for last lean leg to fulfill
        MainFullLeanToContinueLeanNotSent = 12,
        MainFullLeanToContinueLeanSent = 13,
        MainFullLeanToContinueLeanPartial = 14,
        //MainFull_LeanToContinue_LeanFull = 15, //this does not exist, as main full means lean does not need to continue.

        MainFullLeanFull = 15, //END
        MainFirstFullLeanFull = 16, //END
    }

    public class Spread {
        public int OrderQty { get; set; }
        public string OrderTag { get; set; }
        public string Equation { get; set; }
        public string Condition { get; set; }
        public int RoundSigfig { get; set; }
        public int Dir { get; set; }
        public SpreadState State { get; set; }
        public bool SniperMode { get; set; } = false;
        public List<SpreadLeg> OrderedLegs { get; set; }

        public bool IsExchangeVSExchange { get; set; } = false;
        public bool Cal { get; set; } = false;

        public ConcurrentDictionary<string, SpreadLeg> LegTracker { get; set; }

        public Spread() {

        }

        public void Reset() {
            State = SpreadState.Reset;
            //this.orderTag = "";
            //this.spread_equation = "";

            foreach (var leg in LegTracker.Values) {
                leg.Reset();
            }
        }
    }

    public class SpreadLeg {
        //used for initialization
        public string leg_key;
        public bool hadPartialFill = false;

        public string equationCode;
        public string provider;
        public string instrumentID;
        public string orderID;
        public int dir;
        public string orderTag;

        public int lastFilledQty = 0;
        public int remaining_leg_qty = 0; //temporary
        public int leg_order_qty = 0;

        public LegOrderState state = LegOrderState.NotSent;

        public int weightedQtyConfig = 0;
        public string bidOrAsk;
        public bool toTrade = false;
        public bool orderSent = false;
        public int fills = 0;
        public OrderData uo;
        public string legType;
        public double bidAskSpread;
        public double tickVal;

        public bool keepUpdating = true;

        public double entryPrice = -1;
        public double prevPrice = -1; //of bid or ask, or weighted version
        public int prevSize = -1;
        public double prevWeightedPrice = -1;
        public int reqWeightLevel = 1;

        public int prevWeight = -1;
        public int prevISize = -1;
        public int sigfig = 1;

        public SpreadLeg() {
        }

        public SpreadLeg(string equationCode, string provider, string instrumentID, int leg_qty,
            int weight, string bidAsk, OrderData uo, string legType, int sigfig) {
            this.equationCode = equationCode;
            this.provider = provider;
            this.instrumentID = instrumentID;
            this.leg_order_qty = leg_qty;
            this.weightedQtyConfig = weight;
            this.bidOrAsk = bidAsk;
            this.uo = uo;
            this.legType = legType;
            this.sigfig = sigfig;

            this.orderTag = equationCode + " " + legType;
        }

        public void Reset() {
            this.fills = 0;
            this.state = LegOrderState.NotSent;
            this.orderSent = false;
            this.keepUpdating = true;
            //this.uo.orderTag = "";
            //this.uo.legInfo = "";
            //this.equationCode = "";

            this.orderID = "";
        }
    }
}
