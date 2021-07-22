namespace ThmTPWin.Models {
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
        MainPartial_LeanToContinue_LeanNotSent = 8,
        MainPartial_LeanToContinue_LeanSent = 9,
        MainPartial_LeanToContinue_LeanPartial = 10,
        MainPartial_LeanToContinue_LeanFull = 11,

        //caters for last lean leg to fulfill
        MainFull_LeanToContinue_LeanNotSent = 12,
        MainFull_LeanToContinue_LeanSent = 13,
        MainFull_LeanToContinue_LeanPartial = 14,
        //MainFull_LeanToContinue_LeanFull = 15, //this does not exist, as main full means lean does not need to continue.

        MainFullLeanFull = 15, //END
        MainFirstFullLeanFull = 16, //END
    }
}
