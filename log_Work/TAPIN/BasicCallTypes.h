/* Structure to Hold BasicCallTypes like MOC/MTC/SMSMO/SMSMT */
#define CDRCOUNT 500001

typedef struct gBasicCallTypes
{
	/* BasicCallInformation Start    */
           /* ChargeableSubscriber Start */
		char            Imsi[16];                       /* AddressStringDigits  	*/
		char            Msisdn[16];                     /* AddressStringDigits  	*/
	        char            Min[30];                        /* NumberString         	*/
	        char            Mdn[30];  
           /* ChargeableSubscriber End   */
	        int             RapFileSequenceNumber;
           /* Destination Start          */
	        char    	CalledNumber[86];               /* AddressStringDigits  	*/
	        char    	DialledDigits[86];              /* AsciiString          	*/
	        char    	CalledPlace[45];                /* AsciiString          	*/
	        char    	CalledRegion[45];               /* AsciiString          	*/
	        char    	SMSDestinationNumber[86];       /* AsciiString          	*/
           /* Destination End            */ 
	   /* Originator Start           */
                char    	CallingNumber[86];      	/* AddressStringDigits          */
                int     	ClirIndicator;
                char    	SMSOriginator[86];      	/* AsciiString                  */
           /* Origninator End            */
		char		CalledCallingNumber[86];	/* Called Or Calling Number	*/
		char		DialledDigitsSmsOriginator[86];	/* DialledDigits/SMSOriginator  */
                char		DestinationNetwork[6];	        /* PLMN Code			*/
        	gDateTimeLong   CallEventStartTimeStamp;
        	int             TotalCallEventDuration;         /* AsnInt        		*/
        	char            SimToolkitIndicator[2];         /* AsciiString   		*/
	/* BasicCallInformation End      */
	/* LocationInformation Start     */
           /* Network Location Start     */
        	int     	RecEntityCode;          	/* AsnInt               	*/
        	char    	CallReference[15];      	/* AsnOcts 6Octets      	*/
        	int     	LocationArea;           	/* AsnInt               	*/
        	int     	CellId;                 	/* AsnInt 00000 to 65535	*/
           /* Network Location End       */
           /* Home Location Start        */
	        char    	HomeBid[15];                    /* AsciiString Length Assumed 	*/
       	 	char    	HomeLocationDescription[25];    /* AsciiString Length Assumed 	*/
           /* Home Location End          */
           /* Geographical Location Start*/
        	char    	ServingNetwork[10];             /* AsciiString PLMN Code     	*/
        	char    	ServingBid[15];                 /* AsciiString Length Assumed 	*/
        	char    	ServingLocationDescription[25]; /* AsciiString Length Assumed 	*/
           /* Geographical Location End  */
        /* LocationInformation End       */
        /* EquipmentIdentifier Start     */
        	char    	Imei[16];			/* BCDString			*/
       		char 		Esn[20];			/* NumberString			*/
        /* EquipmentIdentifier End       */
        /* BasicServiceUsedList Start    */
	   /* BasicService Start	 */
        	char	        BasicServiceType;               /* T-teleservice, B-bearerservice */
        	char            BasicServiceCode[3];
		int		TransparencyIndicator;		/* AsnInt                       */
		int		Fnur;				/* AsnInt 			*/
		int		UserProtocolIndicator;		/* AsnInt                       */
		char		GuaranteedBitRate[3];		/* AsnOcts, Values 1 - 7	*/
		char		MaximumBitRate[3];		/* AsnOcts, Values 1 - 7	*/
	   /* BasicService End           */
		gDateTimeLong   ChargingTimeStamp;
		gChargeInfo	ChargeInformationList[HTotalChargeInfo];
                char		HSCSDIndicator[2];		/* AsciiString			*/
        /* BasicServiceUsedList End      */
		char		SupplServiceCode[3];		/* HexString 			*/
	/* ThirdPartyInformation Start   */
        	char		ThirdPartyNumber[86];   	/* AddressStringDigits 		*/
        	int     	ThirdPartyClirIndicator; 	/* AsnInt 			*/
	/* ThirdPartyInformation End     */
        /* CamelServiceUsed Start        */
		gCamelService	CamelServiceUsed;
        /* CamelServiceUsed End          */
		long		TotalCharge;
		long		TotalTax;
		long		TotalDiscount;
}gBasicCallTypes;

/* Structure to hold BasicCallType Availibility */
typedef struct gBasicCallTypesA
{
	/* BasicCallInformation Start    */
		int		BasicCallInformation;
           /* ChargeableSubscriber Start */
		int		ChargeableSubscriber;
		int		Imsi;
		int		Msisdn;
		int		Min;
		int		MinLen;
		int		Mdn;
		int		MdnLen;
           /* ChargeableSubscriber End   */
	        int             RapFileSequenceNumber;
           /* Destination Start          */
		int		Destination;
		int		CalledNumber;
		int		DialledDigits;
		int		CalledPlace;
		int		CalledPlaceLen;
		int		CalledRegion;
		int		CalledRegionLen;
		int		SMSDestinationNumber;
           /* Destination End            */ 
	   /* Originator Start           */
		int		Originator;
		int		CallingNumber;
		int		ClirIndicator;
		int		SMSOriginator;
           /* Origninator End            */
		int		DestinationNetwork;
		int		DestinationNetworkLen;
		int		CallEventStartTimeStamp;
		gDateTimeLongA	CallEventStartTime;
		int		TotalCallEventDuration;
		int		SimToolkitIndicator;
	/* BasicCallInformation End      */
	/* LocationInformation Start     */
		int		LocationInformation;
           /* Network Location Start     */
		int		NetworkLocation;
		int		RecEntityCode;
		int		CallReference;
		int		CallReferenceLen;
		int		LocationArea;
		int		CellId;
           /* Network Location End       */
           /* Home Location Start        */
		int		HomeLocationInformation;
		int		HomeBid;
		int		HomeLocationDescription;
           /* Home Location End          */
           /* Geographical Location Start*/
		int		GeographicalLocation;
		int		ServingNetwork;
		int		ServingNetworkLen;
		int		ServingBid;
		int		ServingBidLen;
		int		ServingLocationDescription;
		int		ServingLocationDescriptionLen;
           /* Geographical Location End  */
        /* LocationInformation End       */
        /* EquipmentIdentifier Start     */
		int		EquipmentIdentifier;
		int		Imei;
		int		ImeiLen;
		int		Esn;
		int		EsnLen;
        /* EquipmentIdentifier End       */
        /* BasicServiceUsedList Start    */
		int		BasicServiceUsedList;
        	int		TeleServiceCode;
        	int		BearerServiceCode;
		int		ChargingTimeStamp;
		gDateTimeLongA	ChargingTime;
		int		ChargeInformationList;
		gChargeInfoA	ChargeInformation[HTotalChargeInfo];
		int		HSCSDIndicator;
        /* BasicServiceUsedList End      */
		int		SupplServiceCode;
	/* ThirdPartyInformation Start   */
		int		ThirdPartyNumber;
		int		ThirdPartyClirIndicator;
	/* ThirdPartyInformation End     */
        /* CamelServiceUsed Start        */
		gCamelServiceA CamelServiceUsed;
        /* CamelServiceUsed End          */
}gBasicCallTypesA;


typedef struct PM_TAP_CDRS
{
	char		FILE_TRANSFER_DIRECTION[2];
	char		HPLMN_CODE[6];
	char		VPLMN_CODE[6];
	char		PARTNER_CODE[4];
	char		FILE_TYPE_INDICATOR[2];
	long		FILE_SEQUENCE_NUMBER;
	double      	CALL_SEQUENCE;
	char		CALLS_TYPE_INDICATOR[2];
	long		CALL_TYPE;
    	char        	SERVICE_CODE[4];
	double		IMSI;
	char        	MSISDN[26];
	long		RAPFILE_SEQUENCE_NUMBER;
	char		CALLED_CALLING_NUMBER[87];
	char		DIALLED_DIGITS[87];
	char		CALLED_PLACE[46];
	char		CALLED_REGION[46];
	long		CLIR_INDICATOR;
	char		DESTINATION_NETWORK[7];
	char		CALL_DATE[15];
	long		UTC_OFFSET_CODE;
	long		CALL_DURATION;
	char		SIM_TOOLKIT_INDICATOR[2];
	long		RECORDING_ENTITY_CODE;
	long		RECORDING_ENTITY_TYPE;
	char		RECORDING_ENTITY_ID[46];
	char		CALL_REFERENCE[21];
	double		LOCATION_AREA;
	double		CELLID;
	char		SERVING_NETWORK[6];
	char		IMEI[21];
	char		BASIC_SERVICE_TYPE[2];
	char		BASIC_SERVICE_CODE[4];
	long		TRANSPARENCY_INDICATOR;
	double		FNUR;
	long		USER_PROTOCOL_INDICATOR;
	char		GUARANTEED_BIT_RATE[6];
	char		MAXIMUM_BIT_RATE[6];
	char		HSCSD_INDICATOR[4];
	char		SUPPLIMENTARY_SERVICE_CODE[21];
	long		SUPPLIMENTARY_ACTION_CODE;
	char		SUPPLIMENTARY_SERVICE_PARAMS[46];
	char		THIRD_PARTY_NUMBER[87];
	long		THIRD_PARTY_CLIR_INDICATOR;
	long		CAMEL_USED_FLAG;
	double		CAMEL_SERVICE_LEVEL;
	double		CAMEL_SERVICE_KEY;
	double		CAMEL_DEFAULT_CALL_HANDLING;
	long		CAMEL_EXCHANGE_RATE_CODE;
	double		HOME_CAMEL_EXCHANGE_RATE;
	double		CAMEL_INVOCATION_FEE;
	long		CAMEL_DISCOUNT_CODE;
	double		CAMEL_DISCOUNT;
	double		CAMEL_DISCOUNTABLE_AMOUNT;
	long		CAMEL_TAX_INFORMATION_COUNT;
	long		CAMEL_TAX_CODE;
	double		CAMEL_TAX_VALUE;
	double		CAMEL_TAXABLE_AMOUNT;
	char		CAMEL_DESTINATION_NUMBER[87];
	long		CALL_TYPE_LEVEL1;
	long		CALL_TYPE_LEVEL2;
	long		CALL_TYPE_LEVEL3;
	long		CHARGE_INFORMATION_COUNT;	/* 1-single, >1 multiple */
	char		CHARGED_ITEM[4];		/* to be considered only when single charge information */
	char		CHARGE_TYPE[4];			/* always indicates 00 - total charge */
	double		CHARGEABLE_UNITS;		/* always indicates for total charge */
	double		CHARGED_UNITS;
	double		CHARGE;				/* always indicates total charge */
	long		TAX_INFORMATION_COUNT;		/* 1-single, >1 multiple */
	long		TAX_CODE;
	long 		TAX_VALUE;			/* Always Indicates total Tax */
	double		TAXABLE_AMOUNT;			/* Always Indicates total taxable Amount */	
	long		DISCOUNT_INFORMATION_COUNT;	/* 1-SINLGE, >1 MULTIPLE */
	long		DISCOUNT_CODE;
	double		DISCOUNT;			/* Always Indicates total Discount */
	long		DISCOUNTABLE_AMT;		/* Always Indicates total Discountable Amount */
	double      	HOME_CURNCY_CAMEL_FEE;	
    	double		HOME_CURNCY_CAMEL_TAX;
	double		HOME_CURNCY_CAMEL_DISCOUNT;
	double		HOME_CURNCY_CHARGE;
	double		HOME_CURNCY_TAX;
	double		HOME_CURNCY_DISCOUNT;
	double		HOME_CURNCY_SURCHARGE;
	double		HOME_CURNCY_CHARGE_WITH_TAX;	/* Charge with Tax */
	double		HOME_CURNCY_TOTAL_CHARGE;	/* Charge with Tax and Surcharge */
	double		HOME_EXCHANGE_RATE;
	long		TAP_EXCHANGE_RATE_CODE;
	double		TAP_EXCHANGE_RATE;
	int		TAP_EXCHANGE_RATE_DECIMAL;
    	char            TAP_TAX_TYPE_RATE[601]; 
	char            NETWORK_ACCESS_IDENTIFER[31];
	char            PDP_ADDRESS[46];
	char            APN_NI[66];
	char            APN_OI[66];
	long            CAUSE_FOR_TERMINATION;
	char            PARTIAL_TYPE_INDICATOR[2];
	double          CHARGING_ID;
	char            SERVING_LOCATION_DESC[46];
	double          DATA_VOLUME_INCOMING;
	double          DATA_VOLUME_OUTGOING;
	long            SGSN_RECORDING_ENTITY_CODE1;
	char            SGSN_RECORDING_ENTITY_ID1[46];
	long            SGSN_RECORDING_ENTITY_CODE2;
	char            SGSN_RECORDING_ENTITY_ID2[46];
	long            SGSN_RECORDING_ENTITY_CODE3;
	char            SGSN_RECORDING_ENTITY_ID3[46];
	char            CAMEL_APN_NI[66];
	char            CAMEL_APN_OI[66];
	char		CHARGING_TIME_STAMP[15];
	char           	A_USERID[66];
	char           	B_USERID[66];
	char           	EVENT_REFERENCE[31];
	int            	NETWORK_ELEMENT_TYPE1;
	int            	NETWORK_ELEMENT_TYPE2;
	char           	NETWORK_ELEMENT_ID1[46];
	char           	NETWORK_ELEMENT_ID2[46];
	int            	SGSN_RECORDING_ENTITY_TYPE1;
	int            	SGSN_RECORDING_ENTITY_TYPE2;
   /* Added by Imam as per the ghana specific tapin in-order to implement the LTE services */
	    char            CHARGE_TYPE1[4];                 /* always indicates 68 - total charge */
        double          CHARGEABLE_UNITS1;               /* always indicates original charge */
        double          CHARGED_UNITS1;
        double          CHARGE1;	
/* Imam's change ends here */
}PM_TAP_CDRS;	

typedef struct PM_TAP_CDR_CHARGE_INFO
{
	char		FILE_TRANSFER_DIRECTION[2];
	char		HPLMN_CODE[6];
	char		VPLMN_CODE[6];
	char		FILE_TYPE_INDICATOR[2];
	long		FILE_SEQUENCE_NUMBER;
	long		CALL_SEQUENCE;
	long		CHARGE_INFORMATION;
	char		CHARGED_ITEM[4];
	long		EXCHANGE_RATE_CODE;
	long		CALL_TYPE_LEVEL1;
	long		CALL_TYPE_LEVEL2;
	long		CALL_TYPE_LEVEL3;
	double		CHARGE_DETAIL;
	char		CHARGE_TYPE[4];
	double		CHARGE;
	double		CHARGEABLE_UNITS;
	double		CHARGED_UNITS;
/* Imam's change as per Ghana specific while implementinig the LTE */
	char            CHARGE_TYPE1[4];
    double          CHARGE1;
    double          CHARGEABLE_UNITS1;
    double          CHARGED_UNITS1;
}PM_TAP_CDR_CHARGE_INFO;


typedef struct PM_TAP_CDR_TAX_INFO
{
	char		FILE_TRANSFER_DIRECTION[2];
	char		HPLMN_CODE[6];
	char		VPLMN_CODE[6];
	char		FILE_TYPE_INDICATOR[2];
	long		FILE_SEQUENCE_NUMBER;
	long		CALL_SEQUENCE;
	long		CHARGE_INFORMATION;
	long		TAX_INFORMATION;
	long		TAX_CODE;
	long		TAX_VALUE;
	double		TAXABLE_AMOUNT;
}PM_TAP_CDR_TAX_INFO;

typedef struct PM_TAP_CDR_DISCOUNT_INFO
{
	char		FILE_TRANSFER_DIRECTION[2];
	char		HPLMN_CODE[6];
	char		VPLMN_CODE[6];
	char		FILE_TYPE_INDICATOR[2];
	long		FILE_SEQUENCE_NUMBER;
	long		CALL_SEQUENCE;
	long		CHARGE_INFORMATION;
	long		DISCOUNT_INFORMATION;
	long		DISCOUNT_CODE;
	double		DISCOUNT;
	long		DISCOUNTABLE_AMT;
}PM_TAP_CDR_DISCOUNT_INFO;


typedef struct PM_TAP_CDR_CAMEL_TAX_INFO
{
        char            FILE_TRANSFER_DIRECTION[2];
        char            HPLMN_CODE[6];
        char            VPLMN_CODE[6];
        char            FILE_TYPE_INDICATOR[2];
        long		FILE_SEQUENCE_NUMBER;
        long		CALL_SEQUENCE;
        long		TAX_INFORMATION;
        long		TAX_CODE;
        long          TAX_VALUE;
        double          TAXABLE_AMOUNT;
}PM_TAP_CDR_CAMEL_TAX_INFO;

/* Bulk CDR Variables */

        char            FILE_TRANSFER_DIRECTION[CDRCOUNT][2];
        char            HPLMN_CODE[CDRCOUNT][6];
        char            VPLMN_CODE[CDRCOUNT][6];
        char            PARTNER_CODE[CDRCOUNT][4];
        char            FILE_TYPE_INDICATOR[CDRCOUNT][2];
        long		FILE_SEQUENCE_NUMBER[CDRCOUNT];
        double		CALL_SEQUENCE[CDRCOUNT];
        char            CALLS_TYPE_INDICATOR[CDRCOUNT][2];
        long		CALL_TYPE[CDRCOUNT];
        char            SERVICE_CODE[CDRCOUNT][4];
        double          IMSI[CDRCOUNT];
        char            MSISDN[CDRCOUNT][26];
        long		RAPFILE_SEQUENCE_NUMBER[CDRCOUNT];
        char            CALLED_CALLING_NUMBER[CDRCOUNT][87];
        char            DIALLED_DIGITS[CDRCOUNT][87];
        char            CALLED_PLACE[CDRCOUNT][46];
        char            CALLED_REGION[CDRCOUNT][46];
        long		CLIR_INDICATOR[CDRCOUNT];
        char            DESTINATION_NETWORK[CDRCOUNT][7];
        char            CALL_DATE[CDRCOUNT][15];
        char		UTC_OFFSET_CODE[CDRCOUNT][6];
        long          	CALL_DURATION[CDRCOUNT];
        char            SIM_TOOLKIT_INDICATOR[CDRCOUNT][2];
        long		RECORDING_ENTITY_CODE[CDRCOUNT];
        long		RECORDING_ENTITY_TYPE[CDRCOUNT];
        char            RECORDING_ENTITY_ID[CDRCOUNT][46];
        char            CALL_REFERENCE[CDRCOUNT][21];
        double          LOCATION_AREA[CDRCOUNT];
        double          CELLID[CDRCOUNT];
        char            SERVING_NETWORK[CDRCOUNT][6];
        char            IMEI[CDRCOUNT][21];
        char            BASIC_SERVICE_TYPE[CDRCOUNT][2];
        char            BASIC_SERVICE_CODE[CDRCOUNT][4];
        long		TRANSPARENCY_INDICATOR[CDRCOUNT];
        double          FNUR[CDRCOUNT];
        double          USER_PROTOCOL_INDICATOR[CDRCOUNT];
        char            GUARANTEED_BIT_RATE[CDRCOUNT][6];
        char            MAXIMUM_BIT_RATE[CDRCOUNT][6];
        char            HSCSD_INDICATOR[CDRCOUNT][4];
        char            SUPPLIMENTARY_SERVICE_CODE[CDRCOUNT][21];
        long		SUPPLIMENTARY_ACTION_CODE[CDRCOUNT];
        char            SUPPLIMENTARY_SERVICE_PARAMS[CDRCOUNT][46];
        char            THIRD_PARTY_NUMBER[CDRCOUNT][87];
        long		THIRD_PARTY_CLIR_INDICATOR[CDRCOUNT];
        long		CAMEL_USED_FLAG[CDRCOUNT];
        double          CAMEL_SERVICE_LEVEL[CDRCOUNT];
        double          CAMEL_SERVICE_KEY[CDRCOUNT];
        double          CAMEL_DEFAULT_CALL_HANDLING[CDRCOUNT];
        long		CAMEL_EXCHANGE_RATE_CODE[CDRCOUNT];
        double          HOME_CAMEL_EXCHANGE_RATE[CDRCOUNT];
        double          CAMEL_INVOCATION_FEE[CDRCOUNT];
        long		CAMEL_DISCOUNT_CODE[CDRCOUNT];
        double          CAMEL_DISCOUNT[CDRCOUNT];
        double          CAMEL_DISCOUNTABLE_AMOUNT[CDRCOUNT];
        long		CAMEL_TAX_INFORMATION_COUNT[CDRCOUNT];
        long		CAMEL_TAX_CODE[CDRCOUNT];
        double          CAMEL_TAX_VALUE[CDRCOUNT];
        double          CAMEL_TAXABLE_AMOUNT[CDRCOUNT];
        char            CAMEL_DESTINATION_NUMBER[CDRCOUNT][87];
        long		CALL_TYPE_LEVEL1[CDRCOUNT];
        long		CALL_TYPE_LEVEL2[CDRCOUNT];
        long		CALL_TYPE_LEVEL3[CDRCOUNT];
        long		CHARGE_INFORMATION_COUNT[CDRCOUNT];       /* 1-single, >1 multiple */
        char            CHARGED_ITEM[CDRCOUNT][4];                /* to be considered only when single charge information */
        char            CHARGE_TYPE[CDRCOUNT][4];                 /* always indicates 00 - total charge */
        double          CHARGEABLE_UNITS[CDRCOUNT];               /* always indicates for total charge */
        double          CHARGED_UNITS[CDRCOUNT];
        double          CHARGE[CDRCOUNT];                         /* always indicates total charge */
        long		TAX_INFORMATION_COUNT[CDRCOUNT];          /* 1-single, >1 multiple */
        long		TAX_CODE[CDRCOUNT];
        long          TAX_VALUE[CDRCOUNT];                      /* Always Indicates total Tax */
        double          TAXABLE_AMOUNT[CDRCOUNT];                 /* Always Indicates total taxable Amount */
        long		DISCOUNT_INFORMATION_COUNT[CDRCOUNT];     /* 1-SINLGE, >1 MULTIPLE */
        long		DISCOUNT_CODE[CDRCOUNT];
        double          DISCOUNT[CDRCOUNT];                       /* Always Indicates total Discount */
        long          DISCOUNTABLE_AMT[CDRCOUNT];               /* Always Indicates total Discountable Amount */
        double          HOME_CURNCY_CAMEL_FEE[CDRCOUNT];
        double          HOME_CURNCY_CAMEL_TAX[CDRCOUNT];
        double          HOME_CURNCY_CAMEL_DISCOUNT[CDRCOUNT];
        double          HOME_CURNCY_CHARGE[CDRCOUNT];
        double          HOME_CURNCY_TAX[CDRCOUNT];
        double          HOME_CURNCY_DISCOUNT[CDRCOUNT];
        double          HOME_CURNCY_SURCHARGE[CDRCOUNT];
        double          HOME_CURNCY_CHARGE_WITH_TAX[CDRCOUNT];    /* Charge with Tax */
        double          HOME_CURNCY_TOTAL_CHARGE[CDRCOUNT];       /* Charge with Tax and Surcharge */
        double          HOME_EXCHANGE_RATE[CDRCOUNT];
        long		TAP_EXCHANGE_RATE_CODE[CDRCOUNT];
        double		TAP_EXCHANGE_RATE[CDRCOUNT];
	long		TAP_EXCHANGE_RATE_DECIMAL[CDRCOUNT];
        char            TAP_TAX_TYPE_RATE[CDRCOUNT][601]; 
        char            NETWORK_ACCESS_IDENTIFER[CDRCOUNT][31];
        char            PDP_ADDRESS[CDRCOUNT][46];
        char            APN_NI[CDRCOUNT][66];
        char            APN_OI[CDRCOUNT][66];
        long            CAUSE_FOR_TERMINATION[CDRCOUNT];
        char            PARTIAL_TYPE_INDICATOR[CDRCOUNT][2];
        double          CHARGING_ID[CDRCOUNT];
        char            SERVING_LOCATION_DESC[CDRCOUNT][46];
        double          DATA_VOLUME_INCOMING[CDRCOUNT];
        double          DATA_VOLUME_OUTGOING[CDRCOUNT];
        long            SGSN_RECORDING_ENTITY_CODE1[CDRCOUNT];
        char            SGSN_RECORDING_ENTITY_ID1[CDRCOUNT][46];
        long            SGSN_RECORDING_ENTITY_CODE2[CDRCOUNT];
        char            SGSN_RECORDING_ENTITY_ID2[CDRCOUNT][46];
        long            SGSN_RECORDING_ENTITY_CODE3[CDRCOUNT];
        char            SGSN_RECORDING_ENTITY_ID3[CDRCOUNT][46];
        char            CAMEL_APN_NI[CDRCOUNT][66];
        char            CAMEL_APN_OI[CDRCOUNT][66];

	  char           A_USERID[CDRCOUNT][66];
	  char           B_USERID[CDRCOUNT][66];
	  char           EVENT_REFERENCE[CDRCOUNT][31];
	  int            NETWORK_ELEMENT_TYPE1[CDRCOUNT];
	  int            NETWORK_ELEMENT_TYPE2[CDRCOUNT];
	  char           NETWORK_ELEMENT_ID1[CDRCOUNT][46];
	  char           NETWORK_ELEMENT_ID2[CDRCOUNT][46];
	  int            SGSN_RECORDING_ENTITY_TYPE1[CDRCOUNT];
	  int            SGSN_RECORDING_ENTITY_TYPE2[CDRCOUNT];
       

      long            GPRS_RECORDING_ENTITY_CODES[10];
      long            GPRS_REC_ENTITY_COUNT;
       
	  long            RECORDING_ENTITY_CODES[10];
      long            REC_ENTITY_COUNT;
 /* below 4 fields are Added as per the ghana specific tapin while implementing the LTE  */
	    char            CHARGE_TYPE1[CDRCOUNT][4];                 /* always indicates 00 - total charge */
        double          CHARGEABLE_UNITS1[CDRCOUNT];               /* always indicates for total charge */
        double          CHARGED_UNITS1[CDRCOUNT];
        double          CHARGE1[CDRCOUNT]; 

/* Bulk CDR Temporary Variables */

        char            TEMP_FILE_TRANSFER_DIRECTION[CDRCOUNT][2];
        char            TEMP_HPLMN_CODE[CDRCOUNT][6];
        char            TEMP_VPLMN_CODE[CDRCOUNT][6];
        char            TEMP_PARTNER_CODE[CDRCOUNT][4];
        char            TEMP_FILE_TYPE_INDICATOR[CDRCOUNT][2];
        long		TEMP_FILE_SEQUENCE_NUMBER[CDRCOUNT];
        double		TEMP_CALL_SEQUENCE[CDRCOUNT];
        char            TEMP_CALLS_TYPE_INDICATOR[CDRCOUNT][2];
        long		TEMP_CALL_TYPE[CDRCOUNT];
        char            TEMP_SERVICE_CODE[CDRCOUNT][4];
        double          TEMP_IMSI[CDRCOUNT];
        char            TEMP_MSISDN[CDRCOUNT][26];
        long		TEMP_RAPFILE_SEQUENCE_NUMBER[CDRCOUNT];
        char            TEMP_CALLED_CALLING_NUMBER[CDRCOUNT][87];
        char            TEMP_DIALLED_DIGITS[CDRCOUNT][87];
        char            TEMP_CALLED_PLACE[CDRCOUNT][46];
        char            TEMP_CALLED_REGION[CDRCOUNT][46];
        long		TEMP_CLIR_INDICATOR[CDRCOUNT];
        char            TEMP_DESTINATION_NETWORK[CDRCOUNT][7];
        char            TEMP_CALL_DATE[CDRCOUNT][15];
        char		TEMP_UTC_OFFSET_CODE[CDRCOUNT][6];
        long        TEMP_CALL_DURATION[CDRCOUNT];
        char            TEMP_SIM_TOOLKIT_INDICATOR[CDRCOUNT][2];
        long		TEMP_RECORDING_ENTITY_CODE[CDRCOUNT];
        long		TEMP_RECORDING_ENTITY_TYPE[CDRCOUNT];
        char            TEMP_RECORDING_ENTITY_ID[CDRCOUNT][46];
        char            TEMP_CALL_REFERENCE[CDRCOUNT][21];
        double          TEMP_LOCATION_AREA[CDRCOUNT];
        double          TEMP_CELLID[CDRCOUNT];
        char            TEMP_SERVING_NETWORK[CDRCOUNT][6];
        char            TEMP_IMEI[CDRCOUNT][21];
        char            TEMP_BASIC_SERVICE_TYPE[CDRCOUNT][2];
        char            TEMP_BASIC_SERVICE_CODE[CDRCOUNT][4];
        long		TEMP_TRANSPARENCY_INDICATOR[CDRCOUNT];
        double          TEMP_FNUR[CDRCOUNT];
        double          TEMP_USER_PROTOCOL_INDICATOR[CDRCOUNT];
        char            TEMP_GUARANTEED_BIT_RATE[CDRCOUNT][6];
        char            TEMP_MAXIMUM_BIT_RATE[CDRCOUNT][6];
        char            TEMP_HSCSD_INDICATOR[CDRCOUNT][4];
        char            TEMP_SUPPLIMENTARY_SERVICE_CODE[CDRCOUNT][21];
        long		TEMP_SUPPLIMENTARY_ACTION_CODE[CDRCOUNT];
        char            TEMP_SUPPLIMENTARY_SERVICE_PARAMS[CDRCOUNT][46];
        char            TEMP_THIRD_PARTY_NUMBER[CDRCOUNT][87];
        long		TEMP_THIRD_PARTY_CLIR_INDICATOR[CDRCOUNT];
        long		TEMP_CAMEL_USED_FLAG[CDRCOUNT];
        double          TEMP_CAMEL_SERVICE_LEVEL[CDRCOUNT];
        double          TEMP_CAMEL_SERVICE_KEY[CDRCOUNT];
        double          TEMP_CAMEL_DEFAULT_CALL_HANDLING[CDRCOUNT];
        long		TEMP_CAMEL_EXCHANGE_RATE_CODE[CDRCOUNT];
        double          TEMP_HOME_CAMEL_EXCHANGE_RATE[CDRCOUNT];
        double          TEMP_CAMEL_INVOCATION_FEE[CDRCOUNT];
        long		TEMP_CAMEL_DISCOUNT_CODE[CDRCOUNT];
        double          TEMP_CAMEL_DISCOUNT[CDRCOUNT];
        double          TEMP_CAMEL_DISCOUNTABLE_AMOUNT[CDRCOUNT];
        long		TEMP_CAMEL_TAX_INFORMATION_COUNT[CDRCOUNT];
        long		TEMP_CAMEL_TAX_CODE[CDRCOUNT];
        long          TEMP_CAMEL_TAX_VALUE[CDRCOUNT];
        double          TEMP_CAMEL_TAXABLE_AMOUNT[CDRCOUNT];
        char            TEMP_CAMEL_DESTINATION_NUMBER[CDRCOUNT][87];
        long		TEMP_CALL_TYPE_LEVEL1[CDRCOUNT];
        long		TEMP_CALL_TYPE_LEVEL2[CDRCOUNT];
        long		TEMP_CALL_TYPE_LEVEL3[CDRCOUNT];
        long		TEMP_CHARGE_INFORMATION_COUNT[CDRCOUNT];       /* 1-single, >1 multiple */
        char            TEMP_CHARGED_ITEM[CDRCOUNT][4];                /* to be considered only when single charge information */
        char            TEMP_CHARGE_TYPE[CDRCOUNT][4];                 /* always indicates 00 - total charge */
        double          TEMP_CHARGEABLE_UNITS[CDRCOUNT];               /* always indicates for total charge */
        double          TEMP_CHARGED_UNITS[CDRCOUNT];
        double          TEMP_CHARGE[CDRCOUNT];                         /* always indicates total charge */
        long		TEMP_TAX_INFORMATION_COUNT[CDRCOUNT];          /* 1-single, >1 multiple */
        long		TEMP_TAX_CODE[CDRCOUNT];
        long          TEMP_TAX_VALUE[CDRCOUNT];                      /* Always Indicates total Tax */
        double          TEMP_TAXABLE_AMOUNT[CDRCOUNT];                 /* Always Indicates total taxable Amount */
        long		TEMP_DISCOUNT_INFORMATION_COUNT[CDRCOUNT];     /* 1-SINLGE, >1 MULTIPLE */
        long		TEMP_DISCOUNT_CODE[CDRCOUNT];
        double          TEMP_DISCOUNT[CDRCOUNT];                       /* Always Indicates total Discount */
        long          TEMP_DISCOUNTABLE_AMT[CDRCOUNT];               /* Always Indicates total Discountable Amount */
        double          TEMP_HOME_CURNCY_CAMEL_FEE[CDRCOUNT];
        double          TEMP_HOME_CURNCY_CAMEL_TAX[CDRCOUNT];
        double          TEMP_HOME_CURNCY_CAMEL_DISCOUNT[CDRCOUNT];
        double          TEMP_HOME_CURNCY_CHARGE[CDRCOUNT];
        double          TEMP_HOME_CURNCY_TAX[CDRCOUNT];
        double          TEMP_HOME_CURNCY_DISCOUNT[CDRCOUNT];
        double          TEMP_HOME_CURNCY_SURCHARGE[CDRCOUNT];
        double          TEMP_HOME_CURNCY_CHARGE_WITH_TAX[CDRCOUNT];    /* Charge with Tax */
        double          TEMP_HOME_CURNCY_TOTAL_CHARGE[CDRCOUNT];       /* Charge with Tax and Surcharge */
        double          TEMP_HOME_EXCHANGE_RATE[CDRCOUNT];
        long		TEMP_TAP_EXCHANGE_RATE_CODE[CDRCOUNT];
        double		TEMP_TAP_EXCHANGE_RATE[CDRCOUNT];
	long		TEMP_TAP_EXCHANGE_RATE_DECIMAL[CDRCOUNT];
        char            TEMP_TAP_TAX_TYPE_RATE[CDRCOUNT][601]; 
        char            TEMP_NETWORK_ACCESS_IDENTIFER[CDRCOUNT][31];
        char            TEMP_PDP_ADDRESS[CDRCOUNT][46];
        char            TEMP_APN_NI[CDRCOUNT][66];
        char            TEMP_APN_OI[CDRCOUNT][66];
        long            TEMP_CAUSE_FOR_TERMINATION[CDRCOUNT];
        char            TEMP_PARTIAL_TYPE_INDICATOR[CDRCOUNT][2];
        double          TEMP_CHARGING_ID[CDRCOUNT];
        char            TEMP_SERVING_LOCATION_DESC[CDRCOUNT][46];
        double          TEMP_DATA_VOLUME_INCOMING[CDRCOUNT];
        double          TEMP_DATA_VOLUME_OUTGOING[CDRCOUNT];
        long            TEMP_SGSN_RECORDING_ENTITY_CODE1[CDRCOUNT];
        char            TEMP_SGSN_RECORDING_ENTITY_ID1[CDRCOUNT][46];
        long            TEMP_SGSN_RECORDING_ENTITY_CODE2[CDRCOUNT];
        char            TEMP_SGSN_RECORDING_ENTITY_ID2[CDRCOUNT][46];
        long            TEMP_SGSN_RECORDING_ENTITY_CODE3[CDRCOUNT];
        char            TEMP_SGSN_RECORDING_ENTITY_ID3[CDRCOUNT][46];
        char            TEMP_CAMEL_APN_NI[CDRCOUNT][66];
        char            TEMP_CAMEL_APN_OI[CDRCOUNT][66];

        long            GPRS_RECORDING_ENTITY_CODES[10];
        long            GPRS_REC_ENTITY_COUNT;

		char            TEMP_A_USERID[CDRCOUNT][66];
		char            TEMP_B_USERID[CDRCOUNT][66];
		char            TEMP_EVENT_REFERENCE[CDRCOUNT][31];
        long            TEMP_NETWORK_ELEMENT_TYPE1[CDRCOUNT];
		long            TEMP_NETWORK_ELEMENT_TYPE2[CDRCOUNT];
		char            TEMP_NETWORK_ELEMENT_ID1[CDRCOUNT][46];
		char            TEMP_NETWORK_ELEMENT_ID2[CDRCOUNT][46];
		long            TEMP_SGSN_RECORDING_ENTITY_TYPE1[CDRCOUNT];
		long            TEMP_SGSN_RECORDING_ENTITY_TYPE2[CDRCOUNT];

/* Below four fields are added as per the ghana tapin specific while implementing the LTE */
		char            TEMP_CHARGE_TYPE1[CDRCOUNT][4];                 /* always indicates 00 - total charge */
        double          TEMP_CHARGEABLE_UNITS1[CDRCOUNT];               /* always indicates for total charge */
        double          TEMP_CHARGED_UNITS1[CDRCOUNT];
        double          TEMP_CHARGE1[CDRCOUNT];


/*
MobileOriginatedCall:
Call is duplicate. Chargeable Subscriber, Recording Entity Type and Identification, Call Event Start Time, Called Number, Service Code and Total Call Duration match call record already processed and the call reference is identical in both call records.  If Called Number is not present Dialled Digits must be used.

	1.	ChargeableSubscriber
	2.	RecordingEntityType
	3.	RecordingEntityIdentification
	4.	CallEventStartTime
	5.	CalledNumber/DialledDigits
	6.	ServiceCode
	7.	TotalCallDuration
	8.	CallReferenceNumber

MobileTerminatedCall:
Call is duplicate. Chargeable subscriber, Recording Entity Type and Identification, call event start time, calling number, service code and total call duration match call record already processed and the call reference is identical in both call records.

	1.	ChargeableSubscriber
	2.	RecordingEntityType
        3.      RecordingEntityIdentification
        4.      CallEventStartTime
	5.	CallingNumber
	6.	ServiceCode
        7.      TotalCallDuration
        8.      CallReferenceNumber
*/
