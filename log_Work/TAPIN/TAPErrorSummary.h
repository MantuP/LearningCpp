
#define MAX_REJECTED_CDRS 4999 
#define REJECTEDCDRS 4999 
#define MAX_IOT_CDRS 4999

/* Structure Defined to Hold RAP Related Error Details */
typedef struct stTAPErrorInfo
{
   int  ERROR_CODE[REJECTEDCDRS]                 ;
   char ERROR_TYPE[REJECTEDCDRS][8]              ;
   char ERROR_CONTEXT_DETAILS[REJECTEDCDRS][101] ;
   int  APPLICATION_TAG[REJECTEDCDRS]            ;
   char ERROR_FIELD_NAME[REJECTEDCDRS][51]       ;
   char CONTEXT_NAME[REJECTEDCDRS][51]           ;
   char ERROR_MESSAGE[REJECTEDCDRS][501]         ;
   char ERROR_VALUE[REJECTEDCDRS][101]           ;
}stTAPErrorInfo;

typedef struct stTAPIOTError
{
   long CallSequence[200001] ; 
}stTAPIOTError;

/*Structure defined to hold IOT RAP values */
typedef struct PM_RAP_DETAILS
{
      long   CALL_SEQUENCE;
      char   ERROR_TYPE[9];
      int    APPLICATION_TAG;
      char   ERROR_FIELD_NAME[51];
      int    ERROR_CODE;
      char   ERROR_MESSAGE[501];
      char   ERROR_CONTEXT_DETAILS[101];
      char   CONTEXT_NAME[51];
      long   ERROR_SEQUENCE;
      int    ERROR_NODE;
      char   RAP_STATUS[2];
	  long IOT_CHARGE;
	  char   IOT_DATE[16];
	  char   IOT_CALCULATION[101]; 
	  char   ROWID[20];
}PM_RAP_DETAILS; 



/* Structure Defined to hold Rap Context Value */

typedef struct stErrorContext
{
        char   CallEventDetails[21]             ;
        char   CallEventType[30]                ;
        char   BasicCallInformation[40]         ;
        char   ChargeableSubscriber[50]         ;
        char   Destination[50]                  ;
        char   CallEventStartTimeStamp[50]      ;
        char   LocationInformation[40]          ;
        char   BasicServiceUsed[40]             ;
        char   BasicService[50]                 ;
        char   ChargingTimeStamp[50]            ;
        char   ChargeInformation[50]            ;
        char   CallTypeGroup[60]                ;
        char   ChargeDetail[60]                 ;
        char   TaxInformation[60]               ;
        char   DiscountInformation[60]          ;
        char   CamelServiceUsed[40]             ;
        char   CamelTaxInformation[50]          ;
        char   CamelDiscountInformation[50]     ;
        char   CallOriginator[50]               ;
        char   GprsDestination[50]              ;
        char   GprsServiceUsed[50]              ;
        char   SupplServiceUsed[50]             ;
        char   ThreeGcamelDestination[50]       ;
        char   CamelDestinationNumber[60]       ;
        char   GprsNetworkLocation[50]          ;
		char   ChargedParty[40]                 ;
		char   ServiceStartTimestamp[40]        ;
		char   NonChargedParty[40]              ;
        char   SessionChargeInformation[40]     ;
		char   RecEntityCodeList[40]            ;
		char   NetworkElement[40]              ;
}stErrorContext;

typedef struct PM_TMP_TAP_CDRS 
{
         char   FILE_TRANSFER_DIRECTION[2]    ;
         char   HPLMN_CODE[6]                 ;
         char   VPLMN_CODE[6]                 ;
         char   PARTNER_CODE[4]               ;
         char   FILE_TYPE_INDICATOR[2]        ;
         int    FILE_SEQUENCE_NUMBER          ;
         int    CALL_SEQUENCE                 ;
         int    CALL_TYPE                     ;
         char   SERVICE_CODE[4]               ;
         double IMSI                          ;
         char   MSISDN[26]                    ;
         char   CALLED_CALLING_NUMBER[87]     ;
         char   DIALLED_DIGITS[87]            ;
         char   CALL_DATE[15]                 ;
         double CALL_DURATION                 ;
         char   BASIC_SERVICE_TYPE[2]         ;
         char   BASIC_SERVICE_CODE[4]         ;
         char   CHARGED_ITEM[4]               ;
         double CHARGEABLE_UNITS              ;
         double CHARGED_UNITS                 ;
         double CHARGE                        ;
         long   TAX_INFORMATION_COUNT         ;
         long   TAX_CODE                      ;
         double TAX_VALUE                     ;
         double TAXABLE_AMOUNT                ;
         long   DISCOUNT_INFORMATION_COUNT    ;
         long   DISCOUNT_CODE                 ;
         double DISCOUNT                      ;
         double DISCOUNTABLE_AMT              ;
         double TAP_EXCHANGE_RATE             ;
         long   TAP_EXCHANGE_RATE_DECIMAL     ;
         double DATA_VOLUME_INCOMING          ;
         double DATA_VOLUME_OUTGOING          ;
         double HOME_CURNCY_CHARGE            ;
         double HOME_CURNCY_TAX               ; 
         double HOME_CURNCY_DISCOUNT          ;
         double CAMEL_INVOCATION_FEE          ;
         long   CALL_TYPE_LEVEL1              ;
         double IOT_CHARGE                    ;
         double IOT_TAX                       ;
         double IOT_DISCOUNT                  ;
         long   TARIFF_ID                     ;
         int    CDR_ERROR_FLAG                ;
         char   CHARGE_CONTEXT[80]            ;
         char   TAX_CONTEXT[80]               ;
         char   DISCOUNT_CONTEXT[80]          ;
         int    ERROR_NODE                    ;
	     char   A_USERID[66]                  ;
	     char   B_USERID[66]                  ;
	     char   EVENT_REFERENCE[31]           ;
		 char   IOT_DATE[15]                  ;
		 char   IOT_CALCULATION[100]          ;
         char   ROWID[20]                     ;
}PM_TMP_TAP_CDRS;

/* Bulk CDR Variable for error Details  */
   char     ER_FILE_TRANSFER_DIRECTION[MAX_REJECTED_CDRS][2]      ;
   char     ER_HPLMN_CODE[MAX_REJECTED_CDRS][6]                   ;
   char     ER_VPLMN_CODE[MAX_REJECTED_CDRS][6]                   ;
   char     ER_PARTNER_CODE[MAX_REJECTED_CDRS][4]                 ;
   char     ER_FILE_TYPE_INDICATOR[MAX_REJECTED_CDRS][2]          ;
   long     ER_FILE_SEQUENCE_NUMBER[MAX_REJECTED_CDRS]            ;
   long     ER_RAP_SEQUENCE_NUMBER[MAX_REJECTED_CDRS]             ;
   long     ER_CALL_SEQUENCE[MAX_REJECTED_CDRS]                   ;
   long     ER_ERROR_SEQUENCE[MAX_REJECTED_CDRS]                  ;
   char     ER_CALLS_TYPE_INDICATOR[MAX_REJECTED_CDRS][2]         ;
   long     ER_CALL_TYPE[MAX_REJECTED_CDRS]                       ;
   char     ER_SERVICE_CODE[MAX_REJECTED_CDRS][4]                 ;
   double   ER_IMSI[MAX_REJECTED_CDRS]                            ; 
   char     ER_MSISDN[MAX_REJECTED_CDRS][26]                      ;
   char     ER_CALLED_CALLING_NUMBER[MAX_REJECTED_CDRS][87]       ;
   char     ER_DIALLED_DIGITS[MAX_REJECTED_CDRS][87]              ;
   long     ER_CLIR_INDICATOR[MAX_REJECTED_CDRS]                  ;
   char     ER_DESTINATION_NETWORK[MAX_REJECTED_CDRS][7]          ;
   char     ER_CALL_DATE[MAX_REJECTED_CDRS][15]                   ;
   long     ER_UTC_OFFSET_CODE[MAX_REJECTED_CDRS]                 ;
   char     ER_UTC_OFFSET[MAX_REJECTED_CDRS][6]                   ;
   double   ER_CALL_DURATION[MAX_REJECTED_CDRS]                   ;
   char     ER_SIM_TOOLKIT_INDICATOR[MAX_REJECTED_CDRS][2]        ;
   long     ER_RECORDING_ENTITY_CODE[MAX_REJECTED_CDRS]           ;
   long     ER_RECORDING_ENTITY_TYPE[MAX_REJECTED_CDRS]           ;
   char     ER_RECORDING_ENTITY_ID[MAX_REJECTED_CDRS][46]         ;
   char     ER_CALL_REFERENCE[MAX_REJECTED_CDRS][21]              ;
   double   ER_LOCATION_AREA[MAX_REJECTED_CDRS]                   ;
   double   ER_CELLID[MAX_REJECTED_CDRS]                          ;
   char     ER_SERVING_NETWORK[MAX_REJECTED_CDRS][6]              ;
   char     ER_IMEI[MAX_REJECTED_CDRS][21]                        ;
   char     ER_BASIC_SERVICE_TYPE[MAX_REJECTED_CDRS][2]           ;
   char     ER_BASIC_SERVICE_CODE[MAX_REJECTED_CDRS][4]           ;
   long     ER_TRANSPARENCY_INDICATOR[MAX_REJECTED_CDRS]          ;
   double   ER_FNUR[MAX_REJECTED_CDRS]                            ;
   double   ER_USER_PROTOCOL_INDICATOR[MAX_REJECTED_CDRS]         ;
   char     ER_GUARANTEED_BIT_RATE[MAX_REJECTED_CDRS][6]          ;
   char     ER_MAXIMUM_BIT_RATE[MAX_REJECTED_CDRS][6]             ;
   char     ER_HSCSD_INDICATOR[MAX_REJECTED_CDRS][4]              ;
   char     ER_SUPPLIMENTARY_SERVICE_CODE[MAX_REJECTED_CDRS][21]  ;
   long     ER_SUPPLIMENTARY_ACTION_CODE[MAX_REJECTED_CDRS]       ;
   char     ER_SUPPLIMENTARY_SERVICE_PARAMS[MAX_REJECTED_CDRS][46];
   char     ER_THIRD_PARTY_NUMBER[MAX_REJECTED_CDRS][87]          ;
   long     ER_THIRD_PARTY_CLIR_INDICATOR[MAX_REJECTED_CDRS]      ;
   long     ER_CAMEL_USED_FLAG[MAX_REJECTED_CDRS]                 ;
   double   ER_CAMEL_SERVICE_LEVEL[MAX_REJECTED_CDRS]             ;
   double   ER_CAMEL_SERVICE_KEY[MAX_REJECTED_CDRS]               ;
   double   ER_CAMEL_DEFAULT_CALL_HANDLING[MAX_REJECTED_CDRS]     ;
   long     ER_CAMEL_EXCHANGE_RATE_CODE[MAX_REJECTED_CDRS]        ;
   double   ER_CAMEL_INVOCATION_FEE[MAX_REJECTED_CDRS]            ;
   long     ER_CAMEL_DISCOUNT_CODE[MAX_REJECTED_CDRS]             ;
   double   ER_CAMEL_DISCOUNT[MAX_REJECTED_CDRS]                  ;
   double   ER_CAMEL_DISCOUNTABLE_AMT[MAX_REJECTED_CDRS]          ;
   long     ER_CAMEL_TAX_INFORMATION_COUNT[MAX_REJECTED_CDRS]     ;
   long     ER_CAMEL_TAX_CODE[MAX_REJECTED_CDRS]                  ;
   double   ER_CAMEL_TAX_VALUE[MAX_REJECTED_CDRS]                 ;
   double   ER_CAMEL_TAXABLE_AMOUNT[MAX_REJECTED_CDRS]            ;
   char     ER_CAMEL_DESTINATION_NUMBER[MAX_REJECTED_CDRS][87]    ;
   long     ER_CALL_TYPE_LEVEL1[MAX_REJECTED_CDRS]                ;
   long     ER_CALL_TYPE_LEVEL2[MAX_REJECTED_CDRS]                ;
   long     ER_CALL_TYPE_LEVEL3[MAX_REJECTED_CDRS]                ;
   long     ER_CHARGE_INFORMATION_COUNT[MAX_REJECTED_CDRS]        ;       /* 1-single, >1 multiple */
   char     ER_CHARGED_ITEM[MAX_REJECTED_CDRS][4]                 ;                /* to be considered only when single charge information */
   char     ER_CHARGE_TYPE[MAX_REJECTED_CDRS][4]                  ;                 /* always indicates 00 - total charge */
   double   ER_CHARGEABLE_UNITS[MAX_REJECTED_CDRS]                ;               /* always indicates for total charge */
   double   ER_CHARGED_UNITS[MAX_REJECTED_CDRS]                   ;
   double   ER_CHARGE[MAX_REJECTED_CDRS]                          ;                         /* always indicates total charge */
   long     ER_TAX_INFORMATION_COUNT[MAX_REJECTED_CDRS]           ;          /* 1-single, >1 multiple */
   long     ER_TAX_CODE[MAX_REJECTED_CDRS]                        ;
   double   ER_TAX_VALUE[MAX_REJECTED_CDRS]                       ;                      /* Always Indicates total Tax */
   double   ER_TAXABLE_AMOUNT[MAX_REJECTED_CDRS]                  ;                 /* Always Indicates total taxable Amount */
   long     ER_DISCOUNT_INFORMATION_COUNT[MAX_REJECTED_CDRS]      ;     /* 1-SINLGE, >1 MULTIPLE */
   long     ER_DISCOUNT_CODE[MAX_REJECTED_CDRS]                   ;
   double   ER_DISCOUNT[MAX_REJECTED_CDRS]                        ;                       /* Always Indicates total Discount */
   double   ER_DISCOUNTABLE_AMT[MAX_REJECTED_CDRS]                ;               /* Always Indicates total Discountable Amount */
   long     ER_TAP_EXCHANGE_RATE_CODE[MAX_REJECTED_CDRS]          ;
   double   ER_TAP_EXCHANGE_RATE[MAX_REJECTED_CDRS]               ;
   long     ER_TAP_EXCHANGE_RATE_DECIMAL[MAX_REJECTED_CDRS]       ;
   char     ER_TAP_TAX_TYPE_RATE[MAX_REJECTED_CDRS][601]          ;
   char     ER_NETWORK_ACCESS_IDENTIFER[MAX_REJECTED_CDRS][31]    ;
   char     ER_PDP_ADDRESS[MAX_REJECTED_CDRS][46]                 ;
   char     ER_APN_NI[MAX_REJECTED_CDRS][66]                      ;
   char     ER_APN_OI[MAX_REJECTED_CDRS][66]                      ;
   long     ER_CAUSE_FOR_TERMINATION[MAX_REJECTED_CDRS]           ;
   char     ER_PARTIAL_TYPE_INDICATOR[MAX_REJECTED_CDRS][2]       ;
   double   ER_CHARGING_ID[MAX_REJECTED_CDRS]                     ;
   char     ER_SERVING_LOCATION_DESC[MAX_REJECTED_CDRS][46]       ;
   double   ER_DATA_VOLUME_INCOMING[MAX_REJECTED_CDRS]            ;
   double   ER_DATA_VOLUME_OUTGOING[MAX_REJECTED_CDRS]            ;
   long     ER_SGSN_RECORDING_ENTITY_CODE1[MAX_REJECTED_CDRS]     ;
   char     ER_SGSN_RECORDING_ENTITY_ID1[MAX_REJECTED_CDRS][46]   ;
   long     ER_SGSN_RECORDING_ENTITY_CODE2[MAX_REJECTED_CDRS]     ;
   char     ER_SGSN_RECORDING_ENTITY_ID2[MAX_REJECTED_CDRS][46]   ;
   long     ER_SGSN_RECORDING_ENTITY_CODE3[MAX_REJECTED_CDRS]     ;
   char     ER_SGSN_RECORDING_ENTITY_ID3[MAX_REJECTED_CDRS][46]   ;
   char     ER_CAMEL_APN_NI[MAX_REJECTED_CDRS][66]                ;
   char     ER_CAMEL_APN_OI[MAX_REJECTED_CDRS][66]                ;
   int      ER_ERROR_CODE[MAX_REJECTED_CDRS]                      ;
   char     ER_ERROR_TYPE[MAX_REJECTED_CDRS][8]                   ;
   char     ER_ERROR_CONTEXT_DETAILS[MAX_REJECTED_CDRS][101]      ;
   int      ER_APPLICATION_TAG[MAX_REJECTED_CDRS]                 ;
   char     ER_CONTEXT_NAME[MAX_REJECTED_CDRS][51]                ;
   char     ER_ERROR_FIELD_NAME[MAX_REJECTED_CDRS][51]            ;
   char     ER_ERROR_MESSAGE[MAX_REJECTED_CDRS][501]              ;
   char     ER_ERROR_VALUE[MAX_REJECTED_CDRS][101]                ;
   int      ER_ERROR_NODE[MAX_REJECTED_CDRS]                      ;
   char     ER_RAP_STATUS[MAX_REJECTED_CDRS][101]                 ;
   char     ER_FILE_CREATION_TIME[MAX_REJECTED_CDRS][15]          ;
   char     ER_FILE_TRANSFER_TIME[MAX_REJECTED_CDRS][15]          ;
   char     ER_FILE_AVAILABLE_TIME[MAX_REJECTED_CDRS][15]         ;
   char     ER_CHARGING_TIME_STAMP[MAX_REJECTED_CDRS][15]         ;
   char     ER_LOCAL_CURRENCY_CODE[MAX_REJECTED_CDRS][4]          ;
   char     ER_TAP_CURRENCY_CODE[MAX_REJECTED_CDRS][4]            ;
   long     ER_TAP_DECIMAL_PLACES[MAX_REJECTED_CDRS]              ;
   long     ER_TARIFF_ID[MAX_REJECTED_CDRS]                       ;
   double   ER_IOT_CHARGE[MAX_REJECTED_CDRS]                      ;
   double   ER_IOT_TAX[MAX_REJECTED_CDRS]                         ;
   double   ER_IOT_DISCOUNT[MAX_REJECTED_CDRS]                    ;
   char     ER_DATA_TYPE_INDICATOR[MAX_REJECTED_CDRS][2]          ;
   char     ER_A_USERID[MAX_REJECTED_CDRS][66];
   char     ER_B_USERID[MAX_REJECTED_CDRS][66];
   char     ER_EVENT_REFERENCE[MAX_REJECTED_CDRS][66];
   long     ER_NETWORK_ELEMENT_TYPE1[MAX_REJECTED_CDRS];
   long     ER_NETWORK_ELEMENT_TYPE2[MAX_REJECTED_CDRS];
   char     ER_NETWORK_ELEMENT_ID1[MAX_REJECTED_CDRS][46];
   char     ER_NETWORK_ELEMENT_ID2[MAX_REJECTED_CDRS][46];
   long     ER_SGSN_RECORDING_ENTITY_TYPE1[MAX_REJECTED_CDRS];
   long     ER_SGSN_RECORDING_ENTITY_TYPE2[MAX_REJECTED_CDRS];
   char     ER_IOT_DATE[MAX_REJECTED_CDRS][15]               ;
   char     ER_IOT_CALCULATION[MAX_REJECTED_CDRS][100]       ;
   double   ER_EXP_EXCHANGE_RATE[MAX_REJECTED_CDRS];



/* Bulk CDR Variable for IOT Details  */
   char     IOT_FILE_TRANSFER_DIRECTION[MAX_IOT_CDRS][2]      ;
   char     IOT_HPLMN_CODE[MAX_IOT_CDRS][6]                   ;
   char     IOT_VPLMN_CODE[MAX_IOT_CDRS][6]                   ;
   char     IOT_PARTNER_CODE[MAX_IOT_CDRS][4]                 ;
   char     IOT_FILE_TYPE_INDICATOR[MAX_IOT_CDRS][2]          ;
   long     IOT_FILE_SEQUENCE_NUMBER[MAX_IOT_CDRS]            ;
   long     IOT_CALL_SEQUENCE[MAX_IOT_CDRS]                   ;
   long     IOT_CALL_TYPE[MAX_IOT_CDRS]                       ;
   char     IOT_SERVICE_CODE[MAX_IOT_CDRS][4]                 ;
   double   IOT_IMSI[MAX_IOT_CDRS]                            ;
   char     IOT_MSISDN[MAX_IOT_CDRS][26]                      ;
   char     IOT_CALLED_CALLING_NUMBER[MAX_IOT_CDRS][87]       ;
   char     IOT_DIALLED_DIGITS[MAX_IOT_CDRS][87]              ;
   char     IOT_CALL_DATE[MAX_IOT_CDRS][15]                   ;
   double   IOT_CALL_DURATION[MAX_IOT_CDRS]                   ;
   char     IOT_BASIC_SERVICE_TYPE[MAX_IOT_CDRS][2]           ;
   char     IOT_BASIC_SERVICE_CODE[MAX_IOT_CDRS][4]           ;
   long     IOT_CALL_TYPE_LEVEL1[MAX_IOT_CDRS]                ;
   char     IOT_CHARGED_ITEM[MAX_IOT_CDRS][4]                 ;      
   char     IOT_CHARGE_TYPE[MAX_IOT_CDRS][4]                  ;   
   double   IOT_CHARGEABLE_UNITS[MAX_IOT_CDRS]                ; 
   double   IOT_CHARGED_UNITS[MAX_IOT_CDRS]                   ;
   double   IOT_CHARGE[MAX_IOT_CDRS]                          ; 
   long     IOT_TAX_INFORMATION_COUNT[MAX_IOT_CDRS]           ;  
   long     IOT_TAX_CODE[MAX_IOT_CDRS]                        ;
   double   IOT_TAX_VALUE[MAX_IOT_CDRS]                       ; 
   double   IOT_TAXABLE_AMOUNT[MAX_IOT_CDRS]                  ;
   long     IOT_DISCOUNT_INFORMATION_COUNT[MAX_IOT_CDRS]      ;     
   long     IOT_DISCOUNT_CODE[MAX_IOT_CDRS]                   ;
   double   IOT_DISCOUNT[MAX_IOT_CDRS]                        ;        
   double   IOT_DISCOUNTABLE_AMT[MAX_IOT_CDRS]                ;        
   double   IOT_TAP_EXCHANGE_RATE[MAX_IOT_CDRS]               ;
   long     IOT_TAP_EXCHANGE_RATE_DECIMAL[MAX_IOT_CDRS]       ;
   double   IOT_DATA_VOLUME_INCOMING[MAX_IOT_CDRS]            ;
   double   IOT_DATA_VOLUME_OUTGOING[MAX_IOT_CDRS]            ;
   double   IOT_HOME_CURNCY_CHARGE[MAX_IOT_CDRS]              ;
   double   IOT_HOME_CURNCY_TAX[MAX_IOT_CDRS]                 ;
   double   IOT_HOME_CURNCY_DISCOUNT[MAX_IOT_CDRS]            ;
   double   IOT_CAMEL_INVOCATION_FEE[MAX_IOT_CDRS]            ;
   int      CDR_ERROR_FLAG[MAX_IOT_CDRS]                      ;
   char     IOT_CHARGE_CONTEXT[MAX_IOT_CDRS][80]              ;
   char     IOT_TAX_CONTEXT[MAX_IOT_CDRS][80]                 ;
   char     IOT_DISCOUNT_CONTEXT[MAX_IOT_CDRS][80]            ;
   char     IOT_A_USERID[MAX_IOT_CDRS][66]                    ;
   char     IOT_B_USERID[MAX_IOT_CDRS][66]                    ;
   char     IOT_EVENT_REFERENCE[MAX_IOT_CDRS][31]             ;
   char     IOT_DATE[MAX_IOT_CDRS][15]                        ;
   char     IOT_CALCULATION[MAX_IOT_CDRS][100]                ;
   int      IOT_ERROR_NODE[MAX_IOT_CDRS]                      ;
   
