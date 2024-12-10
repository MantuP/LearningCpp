typedef struct TAPFileSummary
{
 	char	FILE_TRANSFER_DIRECTION[2];
	char	HPLMN_CODE[6];
	char	VPLMN_CODE[7];
	char	FILE_TYPE_INDICATOR[2];
	long    FILE_SEQUENCE_NUMBER;
	char	FILE_NAME[18];
	char	DATA_TYPE_INDICATOR[2];
	char	CALLS_TYPE_INDICATOR[2];
	char	FILE_CREATION_TIME[15];
	char	FILE_CREATION_TIME_UTC_OFFSET[6];
	char	FILE_TRANSFER_TIME[15];
	char	FILE_TRANSFER_TIME_UTC_OFFSET[6];
	char	FILE_AVAILABLE_TIME[15];
	char	FILE_AVAILABLE_TIME_UTC_OFFSET[6];
	int	TAP_SPECIFICATION_VERSION;
	int	TAP_RELEASE_VERSION;
	char	ISO_PLMN_CURNCY_CODE[4];
	char	TAP_CURNCY_CODE[6];
	int	TAP_CURNCY_DECIMAL_PLACES;
	double  TAP_CURNCY_MULT_FACT;
	int	TAP_CURNCY_ROUNDOFF_DECIMAL ;
	int	HOME_CURNCY_ROUNDOFF_DECIMAL;
	char	FILE_PROCESS_DATE[15];
	char	FILE_PROCESSED_BY_USER_ID[51];
	char	FILE_PROCESS_STATUS[2];
	char	EARLIEST_CALL_TIME[15];
	char	EARLIEST_CALL_TIME_UTC_OFFSET[6];
	char	LATEST_CALL_TIME[15];
	char	LATEST_CALL_TIME_UTC_OFFSET[6];
	long	TOTAL_CALL_EVENTS;
	long	TOTAL_CALL_EVENTS_PROCESSED;
	long	TOTAL_PREPAID_CALL_EVENTS;
	long	TOTAL_POSTPAID_CALL_EVENTS;
	double  TOTAL_DURATION;
	double	TOTAL_OUTGOING_VOLUME;
	double	TOTAL_INCOMING_VOLUME;
	double	TAP_CURNCY_CHARGE;
	double	TAP_CURNCY_TAX;
	double	TAP_CURNCY_DISCOUNT;
	double	HOME_CURNCY_CHARGE;
	double	HOME_CURNCY_TAX;
	double	HOME_CURNCY_DISCOUNT;
	double	HOME_CURNCY_SURCHARGE;
 	double  SURCHARGE_PERCENTAGE;
        long    REJECTED_CALL_EVENTS;
        double  REJECTED_DURATION;
        double  REJECTED_OUTGOING_VOLUME;
        double  REJECTED_INCOMING_VOLUME;
        double  REJECTED_TAP_CURNCY_CHARGE;
        double  REJECTED_HOME_CURNCY_CHARGE;
	long	SETTLEMENT_CALL_EVENTS;
	double  SETTLEMENT_DURATION;
	double	SETTLEMENT_OUTGOING_VOLUME;
	double	SETTLEMENT_INCOMING_VOLUME;
	double	SETTLEMENT_TAP_CURNCY_CHARGE;
	double	SETTLEMENT_TAP_CURNCY_TAX;
	double	SETTLEMENT_TAP_CURNCY_DISCOUNT;
	double	SETTLEMENT_LOCAL_CHARGE;
	double	SETTLEMENT_LOCAL_TAX;
	double	SETTLEMENT_LOCAL_DISCOUNT;
	long	YEAR_MONTH;
        char    PARTNER_CODE[4];
        int     UTC_OFFSET_COUNT;
        int     REC_ENTITY_COUNT;
        int     TAX_COUNT;
        int     DISCOUNT_COUNT;
        int     CURRENCY_COUNT;
        char    RAP_FILE_NAME[18];
        int     RAP_FILE_SEQUENCE_NUMBER;
        int     RAP_SPECIFICATION_VERSION;
        int     RAP_RELEASE_VERSION;
        char    FILE_CLEARING_STATUS[2];
}TAPFileSummary;


typedef struct TAPSummary
{
        char    FILE_TRANSFER_DIRECTION[2];
        char    HPLMN_CODE[6];
        char    VPLMN_CODE[7];
        char    FILE_TYPE_INDICATOR[2];
        long     FILE_SEQUENCE_NUMBER;
        char    FILE_NAME[18];
        char    DATA_TYPE_INDICATOR[2];
        char    CALLS_TYPE_INDICATOR[2];
        char    FILE_CREATION_TIME[15];
        char    FILE_CREATION_TIME_UTC_OFFSET[6];
        char    FILE_TRANSFER_TIME[15];
        char    FILE_TRANSFER_TIME_UTC_OFFSET[6];
        char    FILE_AVAILABLE_TIME[15];
        char    FILE_AVAILABLE_TIME_UTC_OFFSET[6];
        int     TAP_SPECIFICATION_VERSION;
        int     TAP_RELEASE_VERSION;
        char    ISO_PLMN_CURNCY_CODE[4];
        char    TAP_CURNCY_CODE[6];
        int     TAP_CURNCY_DECIMAL_PLACES;
        int     TAP_CURNCY_MULT_FACT;
        int     TAP_CURNCY_ROUNDOFF_DECIMAL ;
        int     HOME_CURNCY_ROUNDOFF_DECIMAL;
        char    FILE_PROCESS_DATE[15];
        char    FILE_PROCESSED_BY_USER_ID[51];
        char    FILE_PROCESS_STATUS[2];
        char    EARLIEST_CALL_TIME[15];
        char    EARLIEST_CALL_TIME_UTC_OFFSET[6];
        char    LATEST_CALL_TIME[15];
        char    LATEST_CALL_TIME_UTC_OFFSET[6];
        long    TOTAL_CALL_EVENTS;
        long    TOTAL_CALL_EVENTS_PROCESSED;
        long    TOTAL_PREPAID_CALL_EVENTS;
        long    TOTAL_POSTPAID_CALL_EVENTS;
        long    TOTAL_DURATION;
        double  TOTAL_OUTGOING_VOLUME;
        double  TOTAL_INCOMING_VOLUME;
        double  TAP_CURNCY_CHARGE;
        double  TAP_CURNCY_TAX;
        double  TAP_CURNCY_DISCOUNT;
        double  HOME_CURNCY_CHARGE;
        double  HOME_CURNCY_TAX;
        double  HOME_CURNCY_DISCOUNT;
        double  HOME_CURNCY_SURCHARGE;
        double  SURCHARGE_PERCENTAGE;
        long    REJECTED_CALL_EVENTS;
        double  REJECTED_DURATION;
        double  REJECTED_OUTGOING_VOLUME;
        double  REJECTED_INCOMING_VOLUME;
        double  REJECTED_TAP_CURNCY_CHARGE;
        double  REJECTED_HOME_CURNCY_CHARGE;
        long    SETTLEMENT_CALL_EVENTS;
        long    SETTLEMENT_DURATION;
        double  SETTLEMENT_OUTGOING_VOLUME;
        double  SETTLEMENT_INCOMING_VOLUME;
        double  SETTLEMENT_TAP_CURNCY_CHARGE;
        double  SETTLEMENT_TAP_CURNCY_TAX;
        double  SETTLEMENT_TAP_CURNCY_DISCOUNT;
        double  SETTLEMENT_LOCAL_CHARGE;
        double  SETTLEMENT_LOCAL_TAX;
        double  SETTLEMENT_LOCAL_DISCOUNT;
        long    YEAR_MONTH;
        char    PARTNER_CODE[4];
        int     UTC_OFFSET_COUNT;
        int     REC_ENTITY_COUNT;
        int     TAX_COUNT;
        int     DISCOUNT_COUNT;
        int     CURRENCY_COUNT;
        char    ROWID[20];
        char    USE_GLOBAL_PARAMS_FLG[2];
        char    FILES_DIRECTORY[101];
        char    SUCCESS_DIRECTORY[101];
}TAPSummary;

typedef struct PM_RATED_CDRS
{
	int	CALL_TYPE;
	char    SERVICE_CODE[4];
	char	NE_CODE[46];
 	char	IN_ROUTE[31];
	char	OUT_ROUTE[31];
	double  IMSI; /* N15 */
	char	SGSN_ADDRESS[46];
	char	A_NUMBER[26];
	char	B_NUMBER[26];
	char	C_NUMBER[26];
	char	APN_ADDRESS[66]; 
	char	PDP_ADDRESS[46];
	char	CALL_DATE[15];
	long	CALL_DURATION;
	long	DATA_VOLUME_INC;
	long	DATA_VOLUME_OUT;
	char	TELESERVICE[3];
	char	BEARERSERVICE[3];
	char	CAMEL_FLAG[2];
	int	CAMEL_SERVICE_LEVEL;
	int	CAMEL_SERVICE_KEY;
	int	CAMEL_DEFAULT_CALL_HANDLING;
	char	CAMEL_SERVER_ADDRESS[25];
	char	CAMEL_MSC_ADDRESS[25];
	char	CAMEL_CALL_REF_NUM[17];
	int	CAMEL_INIT_CF_INDICATOR;
	char	CAMEL_DESTINATION_NUM[25];
	char	CAMEL_MODIFICATION[5];
  	char	SUPPLIMENTARY_NUM[3];
	long	NETWORK_TIME;
	long	REASON_FOR_CLEARDOWN;
	long	PARTIAL_INDICATOR;
	long	PARTIAL_SEQ_NUM;
	char	IMEI_NUM[21];
	char	CHRONO_NUM[21];
	double	CHARGING_ID;
	char	SUBSCRIBER_TYPE[2];
	char	AGREEMENT_TYPE[2];
	char	PARTNER_CODE[4];
	char	CALL_DIRECTION[2];
	char	POI[4];
	char	ORIGIN_RATE_ZONE[6];
	char	DESTINATION_RATE_ZONE[6];
	char	DAY_CODE[4];
	char	TIME_TYPE[4];
	char	TARIFF_PLAN_CODE[6];
	long	TARIFF_ID;
	double  UNIT_RATE;
	double  CHARGEABLE_UNITS;
	double  CHARGED_UNITS;
	double  CHARGE_AMOUNT;
	double  TAX_AMOUNT;
	double  SUMMARY_SEQ_NO;
	char	RATED_ON[15];
	double  ADC;
	char	STATUS[16];
	double  REPRICE_SEQ_NO;
	char	NUMBER_PLAN_CODE[6];
	char	RATE_DIRECTION[2];
	char	PAYMENT_DIRECTION[2];
	double  INPUT_FILE_ID;
	char	RATE_UNIT[2];
	char	PARTNER_IDENTIFIER[31];
	char	ROAMING_STATUS[2];
	long	TEMP_SEQUENCE_NUMBER;
	long	FILE_SEQUENCE_NUMBER;
	char    CELL_ID[21];
	char    DATA_TYPE_INDICATOR[2];
	double  DISCOUNT_AMOUNT;
	double  CHARGE_SDR;
	double  DISCOUNT_SDR;
	double  TAX_SDR;
	double  CAMEL_FEE;
	double  CAMEL_FEE_SDR;
	double  CAMEL_TAX_AMOUNT;
	double  CAMEL_TAX_SDR;
	double  CAMEL_DISCOUNT_AMOUNT;
	double  CAMEL_DISCOUNT_SDR;
	char	DESTINATION_TYPE[4];
	char	DESTINATION_SUB_TYPE[4];
	int	RECORDING_ENTITY_TYPE;
	char	CHARGE_TYPE[3];
	char	SERVICE_TYPE[2];
	char	ROAMING_ERROR_CODE[16];
	char	CALL_TYPE_LEVEL3[4];
	double  HOME_EXCHANGE_RATE_CODE;
	int     TAP_EXCHANGE_RATE_CODE;
	double  TAP_EXCHANGE_RATE;
	int     TAP_EXCHANGE_RATE_DECIMAL;
        char    TAP_TAX_TYPE_RATE[601]; 
	double  EXCHANGE_RATE;
	int     TAP_TAX_CODE;
	int     TAP_DISCOUNT_CODE;
	int	TAP_RECORDING_ENTITY_CODE;
	int	TAP_UTC_OFFSET_CODE;
	double  DISCOUNTABLE_AMOUNT;
	double  DISCOUNTABLE_AMOUNT_SDR;
	double  TOTAL_UNITS;
	int	SUPPLIMENTARY_ACTION_CODE;
        char    ROWID[20];
}PM_RATED_CDRS;


typedef struct ROAM_CDRS
{
        int     CALL_TYPE;
        char    NE_CODE[46];
        double  IMSI; /* N15 */
        char    SGSN_ADDRESS[46];
        char    A_NUMBER[26];
        char    B_NUMBER[26];
        char    C_NUMBER[26];
        char    APN_ADDRESS[66];
        char    PDP_ADDRESS[46];
        char    CALL_DATE[15];
        long    CALL_DURATION;
        long    DATA_VOLUME_INC;
        long    DATA_VOLUME_OUT;
        char    TELESERVICE[3];
        char    BEARERSERVICE[3];
        char    CAMEL_FLAG[2];
        int     CAMEL_SERVICE_LEVEL;
        int     CAMEL_SERVICE_KEY;
        int     CAMEL_DEFAULT_CALL_HANDLING;
        char    CAMEL_SERVER_ADDRESS[25];
        char    CAMEL_MSC_ADDRESS[25];
        char    CAMEL_CALL_REF_NUM[17];
        int     CAMEL_INIT_CF_INDICATOR;
        char    CAMEL_DESTINATION_NUM[25];
        char    CAMEL_MODIFICATION[5];
        char    SUPPLIMENTARY_NUM[3];
        long    PARTIAL_INDICATOR;
        long    PARTIAL_SEQ_NUM;
        char    IMEI_NUM[21];
        char    CHRONO_NUM[21];
        double  CHARGING_ID;
        char    AGREEMENT_TYPE[2];
        char    PARTNER_CODE[4];
        double  CHARGEABLE_UNITS;
        double  CHARGED_UNITS;
        char    ROAMING_STATUS[2];
        long    TEMP_SEQUENCE_NUMBER;
        long    FILE_SEQUENCE_NUMBER;
        char    CELL_ID[21];
        char    DATA_TYPE_INDICATOR[2];
        double  CHARGE_SDR;
        double  DISCOUNT_SDR;
        double  TAX_SDR;
        double  CAMEL_FEE_SDR;
        double  CAMEL_TAX_SDR;
        double  CAMEL_DISCOUNT_SDR;
        char    DESTINATION_TYPE[4];
        char    DESTINATION_SUB_TYPE[4];
        int     RECORDING_ENTITY_TYPE;
        char    CHARGE_TYPE[3];
        char    SERVICE_TYPE[2];
        char    CALL_TYPE_LEVEL3[4];
        int     TAP_EXCHANGE_RATE_CODE;
        double  TAP_EXCHANGE_RATE;
	int     TAP_EXCHANGE_RATE_DECIMAL;
        char    TAP_TAX_TYPE_RATE[601]; 
        int     TAP_TAX_CODE;
        int     TAP_DISCOUNT_CODE;
        int     TAP_RECORDING_ENTITY_CODE;
        int     TAP_UTC_OFFSET_CODE;
        double  DISCOUNTABLE_AMOUNT_SDR;
        int     SUPPLIMENTARY_ACTION_CODE;
        char    RATE_UNIT[2];
        char    ROWID[20];
}ROAM_CDRS;
