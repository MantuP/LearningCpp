/* Structure to hold Accounting related information */
typedef struct gAccountingInfo
{
        gTaxationList           Taxation[TOTAL_TAX];
        gDiscountingList        Discounting[TOTAL_DISCOUNT];
        char                    LocalCurrency[4];                               /* AsnOcts */
        char                    TapCurrency[4];                                 /* AsnOcts */
        gCurrencyConversionList CurrencyConversionInfo[TOTAL_CURRENCY];
        int                     TapDecimalPlaces;                               /* AsnInt  */
        double                  TotalTax;
        int                     TotalDiscount;
        int                     TotalCurrency;
}gAccountingInfo;

typedef struct gAccountingInfoA
{
        int                             AccountingInfo;
        int                             TaxationList;
        gTaxationListA			Taxation[TOTAL_TAX];
        int                             DiscountingList;
        gDiscountingListA		Discounting[TOTAL_DISCOUNT];
        int                             LocalCurrency;
        int                             TapCurrency;
        int                             CurrencyConversionList;
        gCurrencyConversionListA	CurrencyConversionInfo[TOTAL_CURRENCY];
        int                             TapDecimalPlaces;
}gAccountingInfoA;
