/* Structure to hold Audit Control related information */
typedef struct gAuditControlInfo
{
        gDateTimeLong                   EarliestCallTimeStamp;
        gDateTimeLong                   LatestCallTimeStamp;
        double                          TotalCharge;
        long                            TotalChargeRefund;
        long                            TotalTaxRefund;
        double                          TotalTaxValue;
        long                            TotalDiscountValue;
        long                            TotalDiscountRefund;
        gTotalAdvisedChargeValueList    TotalAdvisedChargeValue[TOTAL_ACV];
        long                            CallEventDetailsCount;
        int                             TotalACValue;
}gAuditControlInfo;

typedef struct gAuditControlInfoA
{
        int                             AuditControlInfo;
        gDateTimeLongA			EarliestCallTimeStamp;
        gDateTimeLongA			LatestCallTimeStamp;
        double                          TotalCharge;
        int                             TotalChargeRefund;
        int                             TotalTaxRefund;
        double                          TotalTaxValue;
        int                             TotalDiscountValue;
        int                             TotalDiscountRefund;
        int                             TotalAdvisedChargeValueList;
        gTotalAdvisedChargeValueListA	TotalAdvisedChargeValue[TOTAL_ACV];
        int                             CallEventDetailsCount;
}gAuditControlInfoA;
