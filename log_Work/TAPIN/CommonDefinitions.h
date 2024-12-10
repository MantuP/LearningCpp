/* Structure to hold DateandTime with UTC Offset */
#define TOTAL_TAX       30
#define TOTAL_DISCOUNT  25
#define TOTAL_CURRENCY  20
#define TOTAL_UTC       20
#define TOTAL_REC       999
#define TOTAL_ACV       20
#define HTotalChargeInfo        10
#define HTotalChargeDetail      10
#define HTotalTaxes             10

#define FILE_OPEN_ERROR         10
#define FILE_READ_ERROR         11
#define FILE_DECODE_ERROR       12


#define TRANSFER_BATCH_ERR  1
#define NOTIFICATION_ERR    2
#define BATCH_CONTROL_ERR   4
#define ACC_INFO_ERR        5
#define NETWORK_INFO_ERR    6
#define AUDIT_CONTROL_ERR   15 
#define MOC_CALL_ERR        9
#define MTC_CALL_ERR        10
#define GPRS_CALL_ERR       14
#define SUP_CALL_ERR        11 
#define MSESS_CALL_ERR      434
#define MESG_CALL_ERR        433

/*****************************************************************************/
/* Structure to hold DateandTime with UTC Offset */

typedef struct gDateTimeLong
{
        char    LocalTimeStamp[15];
        char    UtcTimeOffset[6];
	int	UtcTimeOffsetCode;
}gDateTimeLong;

typedef struct gDateTimeLongA
{
        int     TimeStamp;
        int     LocalTimeStamp;
        int     UtcTimeOffset;
	int	UtcTimeOffsetCode;
}gDateTimeLongA;

/*****************************************************************************/
/* Structure to hold Tax related information */

typedef struct gTaxationList
{
        int     TaxCode;                /* INTEGER                                                    */
        char    TaxType[3];             /* AsciiString  --(SIZE(2))                                   */
        int     TaxRate;                /* NumberString --(SIZE(7)) [Values:  00.00000 thru 99.99999] */
        char    ChargeType[4];          /* NumberString --(SIZE(2..3))                                */
}gTaxationList;

typedef struct gTaxationListA
{
        int     TaxCode;
        int     TaxType;
        int     TaxRate;
        int     ChargeType;
}gTaxationListA;

/*****************************************************************************/
/* Structure to hold Discount related inforamtion */

typedef struct gDiscountingList
{
        int     DiscountCode;       /* AsnInt                     */
        char    DiscountType[2];       /* F for Fixed and R for Rate */
        int     FixedDiscountValue; /* AbsoluteAmount             */
        int     DiscountRate;       /* AbsoluteAmount             */
}gDiscountingList;

typedef struct gDiscountingListA
{
        int     DiscountCode;
        int     FixedDiscountValue;
        int     DiscountRate;
}gDiscountingListA;


/*****************************************************************************/
/* Structure to hold Currency related information */

typedef struct gCurrencyConversionList
{
        int     ExchangeRateCode;       /* AsnInt                     */
        int     NumberOfDecimalPlaces;  /* AsnInt                     */
        int     ExchangeRate;           /* AsnInt                     */
}gCurrencyConversionList;

typedef struct gCurrencyConversionListA
{
        int     ExchangeRateCode;
        int     NumberOfDecimalPlaces;
        int     ExchangeRate;
}gCurrencyConversionListA;

/*****************************************************************************/
/* Structure to hold UTC Offset related information */

typedef struct gUtcTimeOffsetInfoList
{
        int     UtcTimeOffsetCode;      /* INTEGER                 */
        char    UtcTimeOffset[6];       /* AsciiString --(SIZE(5)) */
}gUtcTimeOffsetInfoList;

typedef struct gUtcTimeOffsetInfoListA
{
        int     UtcTimeOffsetCode;
        int     UtcTimeOffset;
}gUtcTimeOffsetInfoListA;


/*****************************************************************************/
/* Structure to hold Recording Entity related information */

typedef struct gRecEntityInfoList
{
        int     RecEntityCode;          /* INTEGER     */
        int     RecEntityType;          /* AsnInt      */
        char    RecEntityId[46];        /* AsciiString Assumption*/
}gRecEntityInfoList;

typedef struct gRecEntityInfoListA
{
        int     RecEntityCode;
        int     RecEntityType;
        int     RecEntityId;
}gRecEntityInfoListA;

/*****************************************************************************/
/* Structure to hold Advised Charge related information */

typedef struct gTotalAdvisedChargeValueList
{
        char    AdvisedChargeCurrency[6];
        long    TotalAdvisedCharge;
        long    TotalAdvisedChargeRefund;
        long    TotalCommission;
        long    TotalCommissionRefund;
}gTotalAdvisedChargeValueList;

typedef struct gTotalAdvisedChargeValueListA
{
        int     AdvisedChargeCurrency;
        int     TotalAdvisedCharge;
        int     TotalAdvisedChargeRefund;
        int     TotalCommission;
        int     TotalCommissionRefund;
}gTotalAdvisedChargeValueListA;

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/* Structure to hold CallTypeGroup Details */
typedef struct gCallTypeGroup
{
        int     CallTypeLevel1;         /* AsnInt */
        int     CallTypeLevel2;         /* AsnInt */
        int     CallTypeLevel3;         /* AsnInt */
}gCallTypeGroup;

/* Structure to hold CallTypeGroup Availibility */
typedef struct gCallTypeGroupA
{
        int     CallTypeGroup;
        int     CallTypeLevel1;         /* AsnInt */
        int     CallTypeLevel2;         /* AsnInt */
        int     CallTypeLevel3;         /* AsnInt */
}gCallTypeGroupA;

/*****************************************************************************/
/* Structure to hold ChargeDetailList Details */
typedef struct gChargeDetail
{
        char            ChargeType[3];          /* NumberString */
        long            Charge;                 /* AbsoluteAmount */
        long            ChargeableUnits;        /* AsnInt */
        long            ChargedUnits;           /* AsnInt */
        gDateTimeLong   ChargeDetailTimeStamp;
}gChargeDetail;

/* Structure to hold ChargeDetailList Availibility */
typedef struct gChargeDetailA
{
        int             ChargeDetailList;
        int             ChargeType;
        int             Charge;
        int             ChargeableUnits;
        int             ChargedUnits;
        int             ChargeDetailTimeStamp;
        gDateTimeLongA  ChargeDetailTime;
}gChargeDetailA;

/*****************************************************************************/
/* Structure to hold TaxInformation Details */
typedef struct gTaxInformation
{
        int     TaxCode;        /* AsnInt */
        long    TaxValue;       /* AbsoluteAmount */
        long    TaxableAmount;  /* AbsoluteAmount */
}gTaxInformation;

/* Structure to hold TaxInformation Availibitlity */
typedef struct gTaxInformationA
{
        int     TaxInformationList;
        int     TaxCode;
        long    TaxValue;
        long    TaxableAmount;
}gTaxInformationA;

/*****************************************************************************/
/* Structure to hold DiscountInformation Details */
typedef struct gDiscountInformation
{
        int     DiscountCode;           /* AsnInt */
        long    Discount;               /* AbsoluteAmount */
        long    DiscountableAmount;     /* AbsoluteAmount */
}gDiscountInfo;

/* Structure to hold DiscountInformation Availibility */
typedef struct gDiscountInfoA
{
        int     DiscountInformation;
        int     DiscountCode;
        int     Discount;
        int     DiscountableAmount;
}gDiscountInfoA;

/*****************************************************************************/
/* Structure to hold ChargeInformation Details */
typedef struct gChargeInformation
{
        char                    ChargedItem[2];         /* AsciiString */
        int                     ExchangeRateCode;       /* AsnInt      */
        gCallTypeGroup          CallTypeGroup;
        gChargeDetail           ChargeDetailList[HTotalChargeDetail];
        gTaxInformation         TaxInformationList[HTotalTaxes];
        gDiscountInfo		DiscountInformation;
	int			TotalChargeDetailCount;
	int			TotalCharge;
	int			TotalTaxCount;
	int			TotalTax;
}gChargeInfo;

/* Structure to hold ChargeInformation Availibility */
typedef struct gChargeInfoA
{
        int             	ChargedItem;
        int             	ExchangeRateCode;
        int             	CallTypeGroup;
        gChargeDetailA		ChargeDetailList[HTotalChargeDetail];
        gTaxInformationA       	TaxInformationList;
        gDiscountInfoA  	DiscountInformation;
}gChargeInfoA;

/*****************************************************************************/
/*****************************************************************************/
/* Structure to hold GPRS Destination Details */
typedef struct gGprsDestination
{
        char    AccessPointNameNI[25];  /* AsciiString */
        char    AccessPointNameOI[25];  /* AsciiString */
}gGprsDestination;

/* Structure to hold GPRS Destination Availibiltiy */
typedef struct gGprsDestinationA
{
        int     AccessPointNameNI;
        int     AccessPointNameOI;
}gGprsDestinationA;

/*****************************************************************************/
/* Structure to hold ThreeGcamelDestination Details */
typedef struct gThreeGcamelDestination
{
        int              CAMELDESTINATIONNUMBER;
        int              GPRSDESTINATION;
        char             CamelDestinationNumber[86];    /* AddressStringDigits */
        gGprsDestination GprsDestination;
}gThreeGcamelDestination;

/* Structure to hold ThreeGcamelDestination Availibility */
typedef struct gThreeGcamelDestinationA
{
        int     CamelDestinationNumber;
        int     GprsDestination;
}gThreeGcamelDestinationA;

/*****************************************************************************/
/* Structure to hold CamelServiceUsed Details */
typedef struct gCamelService
{
        int                      CamelServiceLevel;             /* AsnInt */
        int                      CamelServiceKey;               /* AsnInt */
        int                      DefaultCallHandlingIndicator;  /* AsnInt */
        int                      ExchangeRateCode;
        gTaxInformation          TaxInformationList[HTotalTaxes];
        gDiscountInfo		 DiscountInformation;
        long                     CamelInvocationFee;            /* AbsoluteAmount */
        gThreeGcamelDestination  ThreeGcamelDestination;
        char                     CseInformation[30];            /* AsnOcts Lenght Assumed */
	int			 TotalTaxCount;
	int			 TotalTax;			/* Sum of Taxes */
}gCamelService;

/* Structure to hold CamelServiceUsed Availibility */
typedef struct gCamelServiceA
{
        int      CamelServiceLevel;
        int      CamelServiceKey;
        int      DefaultCallHandlingIndicator;
        int      ExchangeRateCode;
        int      TaxInformationList;
        int      DiscountInformation;
        int      CamelInvocationFee;
        int      ThreeGcamelDestination;
        int      CseInformation;
}gCamelServiceA;

/*****************************************************************************/
/* Structure to hold SupplimentaryServiceUsed Details */
typedef struct gSupplServiceUsed
{
	char            SupplServiceCode[3];            /* HexString                    */
        int             SupplServiceActionCode;         /* AsnInt                       */
        char            SsParameters[25];               /* AsciiString Length Assumed   */
        gDateTimeLong   ChargingTimeStamp;
        gChargeInfo     ChargeInformationList[HTotalChargeInfo];
        char            BasicServiceType;               /* T-teleservice, B-bearerservice */
        char            BasicServiceCode[3];
}gSupplServiceUsed;
