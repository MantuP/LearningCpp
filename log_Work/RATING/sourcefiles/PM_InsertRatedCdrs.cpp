#include "PM_InsertRatedCdrs.h"
#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "ABL_DateTime.h"
#include "ABL_Date.h"
#include "cmath"
#include "ABL_DbDate.h"
#include "ABL_Blob.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_InsertRatedCdrs()
{
	return ( (Base_Registry*) new PM_InsertRatedCdrs);
}
}

PM_InsertRatedCdrs::PM_InsertRatedCdrs()
{
	//
}

PM_InsertRatedCdrs::~PM_InsertRatedCdrs()
{
	//
}

PM_InsertRatedCdrs::PM_InsertRatedCdrs(const PM_InsertRatedCdrs& p_copyObject)
{
	this->m_ABL_ServicePtr			=	p_copyObject.m_ABL_ServicePtr;
	this->mn_DB_BULK_INSERT_COUNT	=	p_copyObject.mn_DB_BULK_INSERT_COUNT;	
	this->ms_Stopsignalfile			=	p_copyObject.ms_Stopsignalfile;	

	
	}

Base_Registry* PM_InsertRatedCdrs::mb_clone()
{
	return ( (Base_Registry*) new PM_InsertRatedCdrs );
}

ABL_Process* PM_InsertRatedCdrs::mb_createCopy()
{
	return ( new PM_InsertRatedCdrs (*this));
}

bool PM_InsertRatedCdrs::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{	
	try
	{

		m_ABL_ServicePtr = p_ABL_ServicePtr;
		p_ABL_AgentCommunicatorPtr->mb_getParameter("STOP_FILE",ms_Stopsignalfile);
		mn_DB_BULK_INSERT_COUNT=0;
		mn_DB_BULK_INSERT_COUNT=m_ABL_ServicePtr->mb_getInt("DB_BULK_INSERT_COUNT");
	}
	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;
		 ABL_String ls_command("touch ");
		 ls_command +=ms_Stopsignalfile;
		 system(ls_command.c_str()); 
	    return false;
	}
	catch(...)
	{
		ABL_String ls_command("touch ");
		ls_command +=ms_Stopsignalfile;
		 system(ls_command.c_str()); 	
		*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}

	return true;
}

bool PM_InsertRatedCdrs::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	return true;
}
bool PM_InsertRatedCdrs::mb_stop()
{
	return true;
}

bool PM_InsertRatedCdrs::mb_process(ABL_Job* &p_ABL_JobPtr)
{	

	PM_Job* lo_PMJobPtr = (PM_Job*)p_ABL_JobPtr;	
	
	ABL_Connection	*lo_ABLConnection;
	ABL_Statement	lo_ABLStatement;
	ABL_ResultSet	lo_ABLResultSet;
	ABL_String		ls_sql,ls_date;

	ABL_String ls_RejMesg ="";
    ABL_String ls_DupMesg ="";
	gr_CallTypeCounts   lr_CallTypeCounts;
	gr_RejectedCdr lr_RejectedCdrs;
	gr_DuplicateCdr lr_DuplicateCdrs;
	gr_DroppedCdr      lr_DroppedCdr; 
	ABL_String ls_TempDate;
	ABL_String ls_TempConvert; 
	int ln_ErrorNums=0;
	int	ln_TotalRated_CDRS=0;
	int ln_TOTAL_CDRS=0;
	bool lb_IsVariableBinded=false;
	unsigned int ln_Rated_count=0;
	unsigned int ln_Rejected_count=0;
	unsigned int ln_Dropped_count=0;
	unsigned int ln_Duplicate_count=0;

	
	try
	{
                if ( lo_PMJobPtr->gs_FileStatus == "D" || lo_PMJobPtr->gs_FileStatus == "F" )
                        {
                                return true;
                        }

                *m_ABL_ServicePtr<<DEBUG<< "Start :" <<lo_PMJobPtr->gs_fileName <<" : "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;

		lo_ABLConnection = lo_PMJobPtr->mb_getConnection();
		ABL_DbDate			la_DbTimeStamp[2];
		lo_PMJobPtr->gn_Rated_count = 0;
        lo_PMJobPtr->gn_Rejected_count = 0;
	    lo_PMJobPtr->gn_Dropped_count = 0;
	    lo_PMJobPtr->gn_Duplicate_count = 0;


		//ls_sql="select systimestamp  from dual";
		ls_sql="select current_timestamp  from dual";
		lo_ABLStatement = lo_ABLConnection->mb_createStatement(ls_sql);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();		
		lo_ABLResultSet.mb_setBulkCount(2);
		lo_ABLResultSet	<<la_DbTimeStamp;
		while(lo_ABLResultSet.mb_fetch())
		{
			int records = lo_ABLResultSet.mb_getNumArrayRows();
			for(int i = 0; i < records ; i++)
			{
			
				lo_PMJobPtr->gd_DbTimeStamp=la_DbTimeStamp[i];	
			}			
		}//While Ends
				lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);	

		if(lo_PMJobPtr->ga_RatedCdrs.size()==0)
		{
			*m_ABL_ServicePtr<<DEBUG<<"End  :" << lo_PMJobPtr->gs_fileName <<": "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;
			return true;
		}

		ln_TotalRated_CDRS=0;
		
		ln_TOTAL_CDRS=512;
		if(mn_DB_BULK_INSERT_COUNT>0)
		{
			if(lo_PMJobPtr->ga_RatedCdrs.size()>mn_DB_BULK_INSERT_COUNT)
			{
				ln_TOTAL_CDRS=mn_DB_BULK_INSERT_COUNT;
			}
			else
			{
				ln_TOTAL_CDRS=lo_PMJobPtr->ga_RatedCdrs.size();
			}
		}



		//Scoping begins
		{
			int			ln_CallType[ln_TOTAL_CDRS];
			ABL_String              ls_RawCdr[ln_TOTAL_CDRS];
			ABL_String		ls_ServiceCode[ln_TOTAL_CDRS];
			ABL_String		ls_NeCode[ln_TOTAL_CDRS] ;
			ABL_String		ls_InRoute[ln_TOTAL_CDRS];
			ABL_String		ls_OutRoute[ln_TOTAL_CDRS];
			ABL_String  	ln_Imsi[ln_TOTAL_CDRS];
			ABL_String		ls_SgsnAddress[ln_TOTAL_CDRS];
			ABL_String		ls_ANumber[ln_TOTAL_CDRS];
			ABL_String		ls_BNumber[ln_TOTAL_CDRS];
			ABL_String		ls_CNumber[ln_TOTAL_CDRS];
			ABL_String		ls_ApnAddress[ln_TOTAL_CDRS];
			ABL_String		ls_PdpAddress[ln_TOTAL_CDRS];
			ABL_DbDate		ld_CallDate[ln_TOTAL_CDRS];
			double			ln_CallDuration[ln_TOTAL_CDRS];
			double			ln_DataVolume_inc[ln_TOTAL_CDRS];
			double			ln_DataVolume_out[ln_TOTAL_CDRS];
			ABL_String		ls_Teleservice[ln_TOTAL_CDRS];
			ABL_String		ls_Bearerservice[ln_TOTAL_CDRS];
			ABL_String		ls_CamelFlag[ln_TOTAL_CDRS];
			ABL_String		ls_CamelService_level[ln_TOTAL_CDRS];
			ABL_String		ls_CamelService_key[ln_TOTAL_CDRS];
			ABL_String		ls_CamelDefault_call_handling[ln_TOTAL_CDRS];

			ABL_String		ls_CamelServer_address[ln_TOTAL_CDRS];
			ABL_String		ls_CamelMsc_address[ln_TOTAL_CDRS];
			ABL_String		ls_CamelCall_ref_num[ln_TOTAL_CDRS];
			ABL_String		ls_CamelInit_cf_indicator[ln_TOTAL_CDRS];
			ABL_String		ls_CamelDestination_num[ln_TOTAL_CDRS];
			ABL_String		ls_CamelModification[ln_TOTAL_CDRS];
			ABL_String		ls_SupplimentaryNum[ln_TOTAL_CDRS];
			unsigned int	ln_NetworkTime[ln_TOTAL_CDRS];
			unsigned int	ln_ReasonForCleardown[ln_TOTAL_CDRS];
			ABL_String		ls_PartialIndicator[ln_TOTAL_CDRS];
			unsigned int	ln_PartialSeqNum[ln_TOTAL_CDRS];
			ABL_String		ls_ImeiNum[ln_TOTAL_CDRS];
			ABL_String		ls_ChronoNum[ln_TOTAL_CDRS];
			ABL_String		ls_ChargingId[ln_TOTAL_CDRS];
			ABL_String		ls_SubscriberType[ln_TOTAL_CDRS];
			ABL_String		ls_AgreementType[ln_TOTAL_CDRS];
			ABL_String		ls_PartnerCode[ln_TOTAL_CDRS];
			ABL_String		ls_CallDirection[ln_TOTAL_CDRS];
			ABL_String		ls_Poi[ln_TOTAL_CDRS];
			ABL_String		ls_OriginRateZone[ln_TOTAL_CDRS];
			ABL_String		ls_DestinationRateZone[ln_TOTAL_CDRS];
			ABL_String		ls_DayCode[ln_TOTAL_CDRS];
			ABL_String		ls_TimeType[ln_TOTAL_CDRS];
			ABL_String		ls_TariffPlanCode[ln_TOTAL_CDRS];
			unsigned int	ln_TariffId[ln_TOTAL_CDRS];
			double			ln_Unit_rate[ln_TOTAL_CDRS];
			double			ln_ChargeableUnits[ln_TOTAL_CDRS];
			double			ln_ChargedUnits[ln_TOTAL_CDRS];
			double 			ln_ChargeAmount[ln_TOTAL_CDRS];
			double			ln_TaxAmount[ln_TOTAL_CDRS];
			unsigned int 	ln_SummarySeqNo[ln_TOTAL_CDRS];
			ABL_DbDate		ld_RatedOn[ln_TOTAL_CDRS];
			double    		ln_RevenueAmount[ln_TOTAL_CDRS];
			ABL_String		ls_Status[ln_TOTAL_CDRS];		
			unsigned int	ln_RepriceSeqNo[ln_TOTAL_CDRS];
			ABL_String		ls_NumberPlanCode[ln_TOTAL_CDRS];
			ABL_String		ls_RateDirection[ln_TOTAL_CDRS];
			ABL_String		ls_PaymentDirection[ln_TOTAL_CDRS];
			unsigned int	ln_InputFileId[ln_TOTAL_CDRS];	
			ABL_String		ls_RateUnit[ln_TOTAL_CDRS];
			ABL_String		ls_PartnerIdentifier[ln_TOTAL_CDRS];
			ABL_String		ls_RoamingStatus[ln_TOTAL_CDRS];	
			unsigned int	ln_TempSequenceNumber[ln_TOTAL_CDRS];
			unsigned int	ln_FileSequenceNumber[ln_TOTAL_CDRS];
			ABL_String		ls_CellId[ln_TOTAL_CDRS];
			ABL_String		ls_DataTypeIndicator[ln_TOTAL_CDRS];
			double			ln_DiscountAmount[ln_TOTAL_CDRS];		
			unsigned int	ln_ChargeSdr[ln_TOTAL_CDRS];		
			unsigned int	ln_DiscountSdr[ln_TOTAL_CDRS];		
			unsigned int	ln_TaxSdr[ln_TOTAL_CDRS];			
			unsigned int	ln_CamelFee[ln_TOTAL_CDRS];		
			unsigned int	ln_CamelFeeSdr[ln_TOTAL_CDRS];		
			unsigned int	ln_CamelTaxAmount[ln_TOTAL_CDRS];	
			unsigned int	ln_CamelTaxSdr[ln_TOTAL_CDRS];		
			unsigned int	ln_CamelDiscountAmount[ln_TOTAL_CDRS];	
			unsigned int	ln_CamelDiscountSdr[ln_TOTAL_CDRS];	
			ABL_String		ls_DestinationType[ln_TOTAL_CDRS];
			ABL_String		ls_DestinationSubType[ln_TOTAL_CDRS];
			unsigned int	ln_RecordingEntityType[ln_TOTAL_CDRS];
			ABL_String		ls_ChargeType[ln_TOTAL_CDRS];
			ABL_String		ls_ServiceType[ln_TOTAL_CDRS];
			ABL_String		ls_RoamingErrorCode[ln_TOTAL_CDRS];
			ABL_String		ls_CallTypeLevel3[ln_TOTAL_CDRS];
			unsigned int	ln_HomeExchangeRateCode[ln_TOTAL_CDRS];	
			unsigned int	ln_TapExchangeRateCode[ln_TOTAL_CDRS];	
			unsigned int	ln_ExchangeRate[ln_TOTAL_CDRS];
			ABL_String		ls_TapTaxCode[ln_TOTAL_CDRS];		
			ABL_String		ls_TapDiscountCode[ln_TOTAL_CDRS];	
			ABL_String		ls_TapRecordingEntityCode[ln_TOTAL_CDRS]; 
			ABL_String		ls_TapUtcOffsetCode[ln_TOTAL_CDRS];	
			ABL_String		ls_DiscountableAmount[ln_TOTAL_CDRS];	
			ABL_String		ls_DiscountableAmountSdr[ln_TOTAL_CDRS];	
			double			ln_TotalUnits[ln_TOTAL_CDRS]; 
			ABL_String		ls_SupplimentaryActionCode[ln_TOTAL_CDRS];
			ABL_String		ls_OriginDestinationType[ln_TOTAL_CDRS];
			ABL_String		ls_DialledDigits[ln_TOTAL_CDRS];
			unsigned int	ln_RecordingEntityType_SGSN[ln_TOTAL_CDRS];
			unsigned int	ln_TapRecordingEntityCode_SGSN[ln_TOTAL_CDRS];
			ABL_String		ls_DerivedServiceCode[ln_TOTAL_CDRS];
			ABL_String		ls_CurrencyCode[ln_TOTAL_CDRS];
			ABL_String		ls_InvoiceEvent[ln_TOTAL_CDRS];
			unsigned int	ln_RecordNo[ln_TOTAL_CDRS];
			ABL_String		ls_LcrDestination[ln_TOTAL_CDRS];
			ABL_String		ls_NrtrdeFlag[ln_TOTAL_CDRS];
			unsigned int	ln_NrtrdeSequenceNumber[ln_TOTAL_CDRS];
            		ABL_String      ls_Mnp[ln_TOTAL_CDRS];
			
			//Added as per LTE usage for 4.3 release
                	ABL_String              ls_AUserId[ln_TOTAL_CDRS];
                	ABL_String              ls_BUserId[ln_TOTAL_CDRS];
                	ABL_String              ls_EventReference[ln_TOTAL_CDRS];
                	ABL_String              ls_APN_OperatorId[ln_TOTAL_CDRS];
			ABL_String              ls_PCSCF_Address[ln_TOTAL_CDRS];

                	unsigned int            ln_NetworkElementType1[ln_TOTAL_CDRS];
                	unsigned int            ln_NetworkElementType2[ln_TOTAL_CDRS];
                	unsigned int            ln_RecordingEntityTypePCSCF[ln_TOTAL_CDRS];
                	unsigned int            ln_TAP_RecordingEntityCodePCSCF[ln_TOTAL_CDRS];

			ABL_String		ls_origin_sub_type[ln_TOTAL_CDRS];
			ABL_String		ls_origin_traffic_type[ln_TOTAL_CDRS];
			ABL_String		ls_destination_traffic_type[ln_TOTAL_CDRS];
			ABL_String              ls_Net[ln_TOTAL_CDRS];
			ABL_String      ls_StoreDuplicate[ln_TOTAL_CDRS];
            ABL_String      ls_OriginGroup[ln_TOTAL_CDRS];
			ABL_String      ls_DestGroup[ln_TOTAL_CDRS];
			ABL_String      ls_Tierid[ln_TOTAL_CDRS];
                        ABL_String              ls_LcrOrigin[ln_TOTAL_CDRS];
			//Added all these above 9 fields into below insert statement 
			//starting from A_USERID (108) field to DESTINATION_TRAFFIC_TYPE (119) field.
			//modification end

			//Forming the Sql insert statement
			ls_sql="INSERT INTO PM_RATED_CDRS (CALL_TYPE,SERVICE_CODE,NE_CODE,IN_ROUTE,OUT_ROUTE,IMSI,SGSN_ADDRESS,A_NUMBER,B_NUMBER,C_NUMBER,APN_ADDRESS,PDP_ADDRESS,CALL_DATE,CALL_DURATION,DATA_VOLUME_INC,DATA_VOLUME_OUT,TELESERVICE,BEARERSERVICE,CAMEL_FLAG,CAMEL_SERVICE_LEVEL,CAMEL_SERVICE_KEY,CAMEL_DEFAULT_CALL_HANDLING,CAMEL_SERVER_ADDRESS,CAMEL_MSC_ADDRESS,CAMEL_CALL_REF_NUM,CAMEL_INIT_CF_INDICATOR,CAMEL_DESTINATION_NUM,    CAMEL_MODIFICATION,SUPPLIMENTARY_NUM,NETWORK_TIME,REASON_FOR_CLEARDOWN,PARTIAL_INDICATOR,PARTIAL_SEQ_NUM,IMEI_NUM,CHRONO_NUM,CHARGING_ID,SUBSCRIBER_TYPE,AGREEMENT_TYPE,PARTNER_CODE,CALL_DIRECTION,POI,ORIGIN_RATE_ZONE,DESTINATION_RATE_ZONE,DAY_CODE,TIME_TYPE,TARIFF_PLAN_CODE,TARIFF_ID,UNIT_RATE,CHARGEABLE_UNITS,CHARGED_UNITS,CHARGE_AMOUNT,TAX_AMOUNT,SUMMARY_SEQ_NO,RATED_ON,REVENUE_AMOUNT,STATUS,REPRICE_SEQ_NO,NUMBER_PLAN_CODE,RATE_DIRECTION,PAYMENT_DIRECTION,INPUT_FILE_ID,RATE_UNIT,PARTNER_IDENTIFIER,ROAMING_STATUS,TEMP_SEQUENCE_NUMBER,FILE_SEQUENCE_NUMBER,CELL_ID,DATA_TYPE_INDICATOR,DISCOUNT_AMOUNT,CHARGE_SDR,DISCOUNT_SDR,TAX_SDR,CAMEL_FEE,CAMEL_FEE_SDR,CAMEL_TAX_AMOUNT,CAMEL_TAX_SDR,CAMEL_DISCOUNT_AMOUNT,CAMEL_DISCOUNT_SDR,DESTINATION_TYPE,DESTINATION_SUB_TYPE,RECORDING_ENTITY_TYPE,CHARGE_TYPE,SERVICE_TYPE,ROAMING_ERROR_CODE,CALL_TYPE_LEVEL3,HOME_EXCHANGE_RATE_CODE,TAP_EXCHANGE_RATE_CODE,EXCHANGE_RATE,TAP_TAX_CODE,TAP_DISCOUNT_CODE,TAP_RECORDING_ENTITY_CODE,TAP_UTC_OFFSET_CODE,DISCOUNTABLE_AMOUNT,DISCOUNTABLE_AMOUNT_SDR,TOTAL_UNITS,SUPPLIMENTARY_ACTION_CODE,ORIGIN_DESTINATION_TYPE,DIALLED_DIGITS,RECORDING_ENTITY_TYPE_SGSN,TAP_RECORDING_ENTITY_CODE_SGSN,DERIVED_SERVICE_CODE,CURRENCY_CODE,INVOICE_EVENT,RECORD_NO,LCR_DESTINATION,NRTRDE_FLAG,NRTRDE_SEQUENCE_NUMBER,MNP_ROUTING_ID,A_USERID,B_USERID,EVENT_REFERENCE,APN_OPERATOR_ID,PCSCF_ADDRESS,NETWORK_ELEMENT_TYPE1,NETWORK_ELEMENT_TYPE2,RECORDING_ENTITY_TYPE_PCSCF,TAP_REC_ENTITY_CODE_PCSCF,ORIGIN_SUB_TYPE,ORIGIN_TRAFFIC_TYPE,DESTINATION_TRAFFIC_TYPE,ORIGIN_ZONE_GROUP,DEST_ZONE_GROUP,TIER_ID,LCR_ORIGIN,NETWORK_CALL_REF) VALUES (:1,:2,:3,:4,:5,TO_NUMBER(:6),:7,:8,:9,:10,:11,:12,:13,:14,:15,:16,:17,:18,:19,TO_NUMBER(:20),TO_NUMBER(:21),TO_NUMBER(:22),:23,:24,:25,TO_NUMBER(:26),:27,:28,:29,:30,:31,:32,:33,:34,:35,TO_NUMBER(:36),:37,:38,:39,:40,:41,:42,:43,:44,:45,:46,:47,nullif(:48,0),:49,:50,:51,:52,0,:54,TO_NUMBER(:55),:56,:57,:58,:59,:60,:61,:62,:63,:64,:65,:66,:67,:68,:69,:70,";
			ls_sql+=":71,:72,:73,:74,:75,:76,:77,:78,:79,:80,:81,:82,:83,:84,:85,:86,:87,:88,TO_NUMBER(:89),TO_NUMBER(:90),TO_NUMBER(:91),TO_NUMBER(:92), TO_NUMBER(:93),TO_NUMBER(:94),:95,:96,:97,:98,:99,:100,:101,:102,:103,:104,:105,:106,NULL,:107,:108,:109,:110,:111,:112,:113,:114,:115,:116,:117,:118,:119,:120,:121,:122,:123,:124)";


			//ls_sql="INSERT INTO PM_RATED_CDRS (CALL_TYPE,SERVICE_CODE,NE_CODE,IN_ROUTE,OUT_ROUTE,IMSI,SGSN_ADDRESS,A_NUMBER,B_NUMBER,C_NUMBER,APN_ADDRESS,PDP_ADDRESS,CALL_DATE,CALL_DURATION,DATA_VOLUME_INC,DATA_VOLUME_OUT,TELESERVICE,BEARERSERVICE,CAMEL_FLAG,CAMEL_SERVICE_LEVEL,CAMEL_SERVICE_KEY,CAMEL_DEFAULT_CALL_HANDLING,CAMEL_SERVER_ADDRESS,CAMEL_MSC_ADDRESS,CAMEL_CALL_REF_NUM,CAMEL_INIT_CF_INDICATOR,CAMEL_DESTINATION_NUM,CAMEL_MODIFICATION,SUPPLIMENTARY_NUM,NETWORK_TIME,REASON_FOR_CLEARDOWN,PARTIAL_INDICATOR,PARTIAL_SEQ_NUM,IMEI_NUM,CHRONO_NUM,CHARGING_ID,SUBSCRIBER_TYPE,AGREEMENT_TYPE,PARTNER_CODE,CALL_DIRECTION,POI,ORIGIN_RATE_ZONE,DESTINATION_RATE_ZONE,DAY_CODE,TIME_TYPE,TARIFF_PLAN_CODE,TARIFF_ID,UNIT_RATE,CHARGEABLE_UNITS,CHARGED_UNITS,CHARGE_AMOUNT,TAX_AMOUNT,SUMMARY_SEQ_NO,RATED_ON,ADC,STATUS,REPRICE_SEQ_NO,NUMBER_PLAN_CODE,RATE_DIRECTION,PAYMENT_DIRECTION,INPUT_FILE_ID,RATE_UNIT,PARTNER_IDENTIFIER,ROAMING_STATUS,TEMP_SEQUENCE_NUMBER,FILE_SEQUENCE_NUMBER,CELL_ID,DATA_TYPE_INDICATOR,DISCOUNT_AMOUNT,CHARGE_SDR,DISCOUNT_SDR,TAX_SDR,CAMEL_FEE,CAMEL_FEE_SDR,CAMEL_TAX_AMOUNT,CAMEL_TAX_SDR,CAMEL_DISCOUNT_AMOUNT,CAMEL_DISCOUNT_SDR,DESTINATION_TYPE,DESTINATION_SUB_TYPE,RECORDING_ENTITY_TYPE,CHARGE_TYPE,SERVICE_TYPE,ROAMING_ERROR_CODE,CALL_TYPE_LEVEL3,HOME_EXCHANGE_RATE_CODE,TAP_EXCHANGE_RATE_CODE,EXCHANGE_RATE,TAP_TAX_CODE,TAP_DISCOUNT_CODE,TAP_RECORDING_ENTITY_CODE,TAP_UTC_OFFSET_CODE,DISCOUNTABLE_AMOUNT,DISCOUNTABLE_AMOUNT_SDR,TOTAL_UNITS,SUPPLIMENTARY_ACTION_CODE,ORIGIN_DESTINATION_TYPE,DIALLED_DIGITS,RECORDING_ENTITY_TYPE_SGSN,TAP_RECORDING_ENTITY_CODE_SGSN,DERIVED_SERVICE_CODE,CURRENCY_CODE,INVOICE_EVENT,RECORD_NO,LCR_DESTINATION,NRTRDE_FLAG,NRTRDE_SEQUENCE_NUMBER ) VALUES (:1,:2,:3,:4,:5,TO_NUMBER(:6),:7,:8,:9,:10,:11,:12,:13,:14,:15,:16,:17,:18,:19,:20,:21,:22,:23,:24,:25,:26,:27,:28,:29,:30,:31,:32,:33,:34,:35,:36,:37,:38,:39,:40,:41,:42,:43,:44,:45,:46,:47,:48,:49,:50,:51,:52,:53,:54,:55,:56,:57,:58,:59,:60,:61,:62,:63,:64,:65,:66,:67,:68,:69,:70,";
			//ls_sql+=":71,:72,:73,:74,:75,:76,:77,:78,:79,:80,:81,:82,:83,:84,:85,:86,:87,:88,:89,:90,:91,:92,:93,:94,:95,:96,:97,:98,:99,:100,:101,:102,:103,:104,:105,:106,:107)";

			//Creating the ABL Statement
			lo_ABLStatement		=	lo_ABLConnection->mb_createStatement(ls_sql);
			lo_ABLStatement.mb_setUpdateCount(ln_TOTAL_CDRS);
			lo_ABLStatement<<ln_CallType;
			lo_ABLStatement.mb_setStringArray(ls_ServiceCode,4);
			lo_ABLStatement.mb_setStringArray(ls_NeCode,46) ;
			
			//Added as per LTE usage for 4.3 release
			//lo_ABLStatement.mb_setStringArray(ls_InRoute,31);
			//lo_ABLStatement.mb_setStringArray(ls_OutRoute,31);
			lo_ABLStatement.mb_setStringArray(ls_InRoute,64);
                        lo_ABLStatement.mb_setStringArray(ls_OutRoute,64);
			//modification end
			
			lo_ABLStatement.mb_setStringArray(ln_Imsi,15);
			lo_ABLStatement.mb_setStringArray(ls_SgsnAddress,46);
			lo_ABLStatement.mb_setStringArray(ls_ANumber,26);
			lo_ABLStatement.mb_setStringArray(ls_BNumber,26);
			lo_ABLStatement.mb_setStringArray(ls_CNumber,26);
			lo_ABLStatement.mb_setStringArray(ls_ApnAddress,66);
			lo_ABLStatement.mb_setStringArray(ls_PdpAddress,31);
			lo_ABLStatement<<ld_CallDate;
			lo_ABLStatement<<ln_CallDuration;
			lo_ABLStatement<<ln_DataVolume_inc;
			lo_ABLStatement<<ln_DataVolume_out;
			lo_ABLStatement.mb_setStringArray(ls_Teleservice,3);
			lo_ABLStatement.mb_setStringArray(ls_Bearerservice,3);
			lo_ABLStatement.mb_setStringArray(ls_CamelFlag,2);//
			lo_ABLStatement.mb_setStringArray(ls_CamelService_level,6);
			lo_ABLStatement.mb_setStringArray(ls_CamelService_key,10);
			lo_ABLStatement.mb_setStringArray(ls_CamelDefault_call_handling,2);
			lo_ABLStatement.mb_setStringArray(ls_CamelServer_address,25);
			lo_ABLStatement.mb_setStringArray(ls_CamelMsc_address,25);
			lo_ABLStatement.mb_setStringArray(ls_CamelCall_ref_num,17);
			lo_ABLStatement.mb_setStringArray(ls_CamelInit_cf_indicator,1);
			lo_ABLStatement.mb_setStringArray(ls_CamelDestination_num,25);
			lo_ABLStatement.mb_setStringArray(ls_CamelModification,5);
			lo_ABLStatement.mb_setStringArray(ls_SupplimentaryNum,3);
			lo_ABLStatement<<ln_NetworkTime;
			lo_ABLStatement<<ln_ReasonForCleardown;
			lo_ABLStatement.mb_setStringArray(ls_PartialIndicator,2);//
			lo_ABLStatement<<ln_PartialSeqNum;
			lo_ABLStatement.mb_setStringArray(ls_ImeiNum,21);
			lo_ABLStatement.mb_setStringArray(ls_ChronoNum,21);
			lo_ABLStatement.mb_setStringArray(ls_ChargingId,10);
			lo_ABLStatement.mb_setStringArray(ls_SubscriberType,2);//
			lo_ABLStatement.mb_setStringArray(ls_AgreementType,2);//
			lo_ABLStatement.mb_setStringArray(ls_PartnerCode,4);
			lo_ABLStatement.mb_setStringArray(ls_CallDirection,2);//
			lo_ABLStatement.mb_setStringArray(ls_Poi,5);
			lo_ABLStatement.mb_setStringArray(ls_OriginRateZone,6);
			lo_ABLStatement.mb_setStringArray(ls_DestinationRateZone,6);
			lo_ABLStatement.mb_setStringArray(ls_DayCode,4);
			lo_ABLStatement.mb_setStringArray(ls_TimeType,4);
			lo_ABLStatement.mb_setStringArray(ls_TariffPlanCode,6);
			lo_ABLStatement<<ln_TariffId;
			lo_ABLStatement<<ln_Unit_rate;
			lo_ABLStatement<<ln_ChargeableUnits;
			lo_ABLStatement<<ln_ChargedUnits;
			lo_ABLStatement<<ln_ChargeAmount;
			lo_ABLStatement<<ln_TaxAmount;
			//lo_ABLStatement<<ln_SummarySeqNo;
			lo_ABLStatement<<ld_RatedOn;
			lo_ABLStatement<<ln_RevenueAmount;
			lo_ABLStatement.mb_setStringArray(ls_Status,16);
			lo_ABLStatement<<ln_RepriceSeqNo;
			lo_ABLStatement.mb_setStringArray(ls_NumberPlanCode,6);
			lo_ABLStatement.mb_setStringArray(ls_RateDirection,2);//
			lo_ABLStatement.mb_setStringArray(ls_PaymentDirection,2);//
			lo_ABLStatement<<ln_InputFileId;	
			lo_ABLStatement.mb_setStringArray(ls_RateUnit,2);//
			lo_ABLStatement.mb_setStringArray(ls_PartnerIdentifier,31);
			lo_ABLStatement.mb_setStringArray(ls_RoamingStatus,2);//	
			lo_ABLStatement<<ln_TempSequenceNumber;
			lo_ABLStatement<<ln_FileSequenceNumber;
			lo_ABLStatement.mb_setStringArray(ls_CellId,21);
			lo_ABLStatement.mb_setStringArray(ls_DataTypeIndicator,3);//
			lo_ABLStatement<<ln_DiscountAmount;		
			lo_ABLStatement<<ln_ChargeSdr;		
			lo_ABLStatement<<ln_DiscountSdr;		
			lo_ABLStatement<<ln_TaxSdr;			
			lo_ABLStatement<<ln_CamelFee;		
			lo_ABLStatement<<ln_CamelFeeSdr;		
			lo_ABLStatement<<ln_CamelTaxAmount;	
			lo_ABLStatement<<ln_CamelTaxSdr;		
			lo_ABLStatement<<ln_CamelDiscountAmount;	
			lo_ABLStatement<<ln_CamelDiscountSdr;	
			lo_ABLStatement.mb_setStringArray(ls_DestinationType,4);
			lo_ABLStatement.mb_setStringArray(ls_DestinationSubType,4);
			lo_ABLStatement<<ln_RecordingEntityType;
			lo_ABLStatement.mb_setStringArray(ls_ChargeType,3);
			lo_ABLStatement.mb_setStringArray(ls_ServiceType,2);//
			lo_ABLStatement.mb_setStringArray(ls_RoamingErrorCode,16);
			lo_ABLStatement.mb_setStringArray(ls_CallTypeLevel3,4);
			lo_ABLStatement<<ln_HomeExchangeRateCode;	
			lo_ABLStatement<<ln_TapExchangeRateCode;	
			lo_ABLStatement<<ln_ExchangeRate;
			lo_ABLStatement.mb_setStringArray(ls_TapTaxCode,2);		
			lo_ABLStatement.mb_setStringArray(ls_TapDiscountCode,2);	
			lo_ABLStatement.mb_setStringArray(ls_TapRecordingEntityCode,5); 
			lo_ABLStatement.mb_setStringArray(ls_TapUtcOffsetCode,2);	
			lo_ABLStatement.mb_setStringArray(ls_DiscountableAmount,20);	
			lo_ABLStatement.mb_setStringArray(ls_DiscountableAmountSdr,20);	
			lo_ABLStatement<<ln_TotalUnits; 
			lo_ABLStatement.mb_setStringArray(ls_SupplimentaryActionCode,3);
			lo_ABLStatement.mb_setStringArray(ls_OriginDestinationType,2);//
			lo_ABLStatement.mb_setStringArray(ls_DialledDigits,26);
			lo_ABLStatement<<ln_RecordingEntityType_SGSN;
			lo_ABLStatement<<ln_TapRecordingEntityCode_SGSN;
			lo_ABLStatement.mb_setStringArray(ls_DerivedServiceCode,4);
			lo_ABLStatement.mb_setStringArray(ls_CurrencyCode,4);
			lo_ABLStatement.mb_setStringArray(ls_InvoiceEvent,2);//
			lo_ABLStatement<<ln_RecordNo;
			lo_ABLStatement.mb_setStringArray(ls_LcrDestination,26);
			lo_ABLStatement.mb_setStringArray(ls_NrtrdeFlag,2);//
			//lo_ABLStatement<<ln_NrtrdeSequenceNumber;
			lo_ABLStatement.mb_setStringArray(ls_Mnp,25);

			//Added as per LTE usage for 4.3 release
			lo_ABLStatement.mb_setStringArray(ls_AUserId,66);
			lo_ABLStatement.mb_setStringArray(ls_BUserId,66);
			lo_ABLStatement.mb_setStringArray(ls_EventReference,31);
			lo_ABLStatement.mb_setStringArray(ls_APN_OperatorId,38);
			lo_ABLStatement.mb_setStringArray(ls_PCSCF_Address,46);
			lo_ABLStatement<<ln_NetworkElementType1;
			lo_ABLStatement<<ln_NetworkElementType2;
			lo_ABLStatement<<ln_RecordingEntityTypePCSCF;
			lo_ABLStatement<<ln_TAP_RecordingEntityCodePCSCF;

			lo_ABLStatement.mb_setStringArray(ls_origin_sub_type,4);
			lo_ABLStatement.mb_setStringArray(ls_origin_traffic_type,2);
			lo_ABLStatement.mb_setStringArray(ls_destination_traffic_type,2);
			lo_ABLStatement.mb_setStringArray(ls_OriginGroup,15);
			lo_ABLStatement.mb_setStringArray(ls_DestGroup,15);
			lo_ABLStatement.mb_setStringArray(ls_Tierid,15);
                        lo_ABLStatement.mb_setStringArray(ls_LcrOrigin,26);
                        lo_ABLStatement.mb_setStringArray(ls_Net,30); //Imam changed to add the NETWORK_CALL_REF field to add into PM_RATED_CDRS table
			//modification end

		for(int i=0; i<lo_PMJobPtr->ga_RatedCdrs.size();i++)
		{
			 ln_Rated_count++;

			//Check for Rejected Cdrs and copy them accordingly to lr_RejectedCdrs and push them to ga_RejectedCdrs
			if(lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginRateZone==" ")
			{
							lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginRateZone="";
			}
			if(lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceType==" ")
			{
				lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceType="";
			}
			if(lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus=="R")
			{
                ln_Rejected_count++;
				lr_RejectedCdrs.gn_FileId=0.0;				
				lr_RejectedCdrs.gn_RecordNo=0.0;				
				lr_RejectedCdrs.gs_ErrorMessage	=" ";			
				lr_RejectedCdrs.gs_ErrorCode	=" ";			
				lr_RejectedCdrs.gs_ErrorValue=" ";				
				lr_RejectedCdrs.gd_RejectedDate.mb_fromSysDate();	
				lr_RejectedCdrs.gs_Status=" ";				
				lr_RejectedCdrs.gs_ErrorCdr=" ";
				lr_RejectedCdrs.gs_AgreementType=" ";			
				lr_RejectedCdrs.gn_CallType=0;				
				lr_RejectedCdrs.gs_CallDirection=" ";			
				lr_RejectedCdrs.gs_NeCode=" ";		
				lr_RejectedCdrs.gs_PartnerIdentifier=" ";
				lr_RejectedCdrs.gs_PartnerCode=" ";		
				lr_RejectedCdrs.gs_Poi=" ";			
				lr_RejectedCdrs.gs_ServiceCode=" ";
				lr_RejectedCdrs.gs_RateDirection=" ";			
				lr_RejectedCdrs.gs_PaymentDirection=" ";			
				lr_RejectedCdrs.gs_RateUnit=" ";				
				lr_RejectedCdrs.gn_UnitQty=0.0;				
				lr_RejectedCdrs.gs_NumberPlanCode=" ";			
				lr_RejectedCdrs.gs_TariffPlanCode=" ";		
				lr_RejectedCdrs.gs_ALong=" ";		
				lr_RejectedCdrs.gs_OriginRateZone=" ";
				lr_RejectedCdrs.gs_BLong=" ";		
				lr_RejectedCdrs.gs_DestRateZone	=" ";
				lr_RejectedCdrs.gs_DayCode=" ";
				lr_RejectedCdrs.gs_TimeType=" ";			
				lr_RejectedCdrs.gn_RerateSeqNo	=0;			
				lr_RejectedCdrs.gn_CallDuration	=0;		

				lr_RejectedCdrs.gn_FileId				=  lo_PMJobPtr->ga_RatedCdrs[i].gn_InputFileId;
				lr_RejectedCdrs.gn_RecordNo				=	lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordNo;
				lr_RejectedCdrs.gs_ErrorMessage				=	lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage;
				lr_RejectedCdrs.gs_ErrorCode				=	lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode;
				lr_RejectedCdrs.gs_ErrorValue				=	lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue;
				lr_RejectedCdrs.gd_RejectedDate.mb_fromSysDate();		
				lr_RejectedCdrs.gs_Status				=	"NEW";
				lr_RejectedCdrs.gs_ErrorCdr				=	lo_PMJobPtr->ga_RatedCdrs[i].gs_RawCdr;
				lr_RejectedCdrs.gs_AgreementType			=	lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType;
				lr_RejectedCdrs.gn_CallType				=	lo_PMJobPtr->ga_RatedCdrs[i].gn_CallType;
				lr_RejectedCdrs.gs_CallDirection			=	lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection;
				lr_RejectedCdrs.gs_NeCode				=	lo_PMJobPtr->ga_RatedCdrs[i].gs_NeCode;
				lr_RejectedCdrs.gs_PartnerIdentifier			=	lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier;
				lr_RejectedCdrs.gs_PartnerCode				=	lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
				lr_RejectedCdrs.gs_Poi					=	lo_PMJobPtr->ga_RatedCdrs[i].gs_Poi;
				lr_RejectedCdrs.gs_ServiceCode				=	lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode;
				lr_RejectedCdrs.gs_ServiceCode[lr_RejectedCdrs.gs_ServiceCode.mb_length()]='\0';
				lr_RejectedCdrs.gs_RateDirection			=	lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection;
				lr_RejectedCdrs.gs_PaymentDirection			=	lo_PMJobPtr->ga_RatedCdrs[i].gs_PaymentDirection;
				lr_RejectedCdrs.gs_RateUnit				=	lo_PMJobPtr->ga_RatedCdrs[i].gs_RateUnit;
				lr_RejectedCdrs.gn_UnitQty				=	0; 
				lr_RejectedCdrs.gs_NumberPlanCode			=	lo_PMJobPtr->ga_RatedCdrs[i].gs_NumberPlanCode;
				lr_RejectedCdrs.gs_TariffPlanCode			=	lo_PMJobPtr->ga_RatedCdrs[i].gs_TariffPlanCode;
				lr_RejectedCdrs.gs_ALong				=	lo_PMJobPtr->ga_RatedCdrs[i].gs_ANumber;
				lr_RejectedCdrs.gs_OriginRateZone			=	lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginRateZone;
				lr_RejectedCdrs.gs_BLong				=	lo_PMJobPtr->ga_RatedCdrs[i].gs_BNumber;
				lr_RejectedCdrs.gs_DestRateZone				=	lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationRateZone;

				lr_RejectedCdrs.gd_CallDate				=	lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate;

				lr_RejectedCdrs.gs_DayCode				=	lo_PMJobPtr->ga_RatedCdrs[i].gs_DayCode;
				lr_RejectedCdrs.gs_TimeType				=	lo_PMJobPtr->ga_RatedCdrs[i].gs_TimeType;
				lr_RejectedCdrs.gn_RerateSeqNo				=	0;
				lr_RejectedCdrs.gn_CallDuration				=	lo_PMJobPtr->ga_RatedCdrs[i].gn_CallDuration;
				lr_RejectedCdrs.gs_ChronoNum                		=   lo_PMJobPtr->ga_RatedCdrs[i].gs_ChronoNum;
				lr_RejectedCdrs.gn_PartialSeqNum            		=   lo_PMJobPtr->ga_RatedCdrs[i].gn_PartialSeqNum;

				//Added as per LTE usage for 4.3 release
				lr_RejectedCdrs.gs_AUserId            =   lo_PMJobPtr->ga_RatedCdrs[i].gs_AUserId;
                                lr_RejectedCdrs.gs_BUserId            =   lo_PMJobPtr->ga_RatedCdrs[i].gs_BUserId;
				//modification end

				lo_PMJobPtr->ga_RejectedCdrs.push_back(lr_RejectedCdrs);
				continue;
			}

			//Check for Dropped Cdrs and copy them accordingly to lr_DroppedCdr and push them to ga_DroppedCdr
			if(lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus=="D" )
			{
				       ln_Dropped_count++;
					
						lr_DroppedCdr.gn_CallType			=  lo_PMJobPtr->ga_RatedCdrs[i].gn_CallType;
						lr_DroppedCdr.gs_CallDirection			=  lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection;
						lr_DroppedCdr.gs_AgreementType			=  lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType;
						lr_DroppedCdr.gn_InputFileId			=  lo_PMJobPtr->ga_RatedCdrs[i].gn_InputFileId;
						lr_DroppedCdr.gn_RecordNo			=  lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordNo;
						lr_DroppedCdr.gs_PartnerCode			=  lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
						lr_DroppedCdr.gs_DroppedCdr			=  lo_PMJobPtr->ga_RatedCdrs[i].gs_RawCdr;
						lr_DroppedCdr.gs_DropCode			=  lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode;
						lr_DroppedCdr.gn_CallDuration			=  lo_PMJobPtr->ga_RatedCdrs[i].gn_CallDuration;
						lr_DroppedCdr.gs_ErrorMessage			=  lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage;
						lr_DroppedCdr.gd_DroppedDate.mb_fromSysDate();
						lr_DroppedCdr.gd_CallDate			=  lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate;
						lr_DroppedCdr.gs_Status				=  "NEW";
						lr_DroppedCdr.gs_ErrorValue			=	lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue;
						lr_DroppedCdr.gs_ANumber			=	lo_PMJobPtr->ga_RatedCdrs[i].gs_ANumber;
						lr_DroppedCdr.gs_BNumber			=	lo_PMJobPtr->ga_RatedCdrs[i].gs_BNumber;
						lr_DroppedCdr.gs_Necode				=	lo_PMJobPtr->ga_RatedCdrs[i].gs_NeCode;
						lr_DroppedCdr.gs_Poi				=	lo_PMJobPtr->ga_RatedCdrs[i].gs_Poi;
						lr_DroppedCdr.gs_Partneridentifier		=	lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier;
						lr_DroppedCdr.gs_StoreDroppedCdr		=	lo_PMJobPtr->ga_RatedCdrs[i].gs_StoreDroppedCdr;

						//Added as per LTE usage for 4.3 release
                                		lr_DroppedCdr.gs_AUserId            =   lo_PMJobPtr->ga_RatedCdrs[i].gs_AUserId;
                                		lr_DroppedCdr.gs_BUserId            =   lo_PMJobPtr->ga_RatedCdrs[i].gs_BUserId;
                                		//modification end
						
						lo_PMJobPtr->ga_DroppedCdr.push_back(lr_DroppedCdr);
					

					continue;
			}//Dropped cdrs if condition ends


				//Now Processing for the rated cdrs
			 	ln_CallType[ln_TotalRated_CDRS]					=		lo_PMJobPtr->ga_RatedCdrs[i].gn_CallType;
			 	ls_ServiceCode[ln_TotalRated_CDRS]				=		lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode;
			 	ls_NeCode[ln_TotalRated_CDRS]					=		lo_PMJobPtr->ga_RatedCdrs[i].gs_NeCode;
			 	ls_InRoute[ln_TotalRated_CDRS]					=		lo_PMJobPtr->ga_RatedCdrs[i].gs_InRoute;
			 	ls_OutRoute[ln_TotalRated_CDRS]					=		lo_PMJobPtr->ga_RatedCdrs[i].gs_OutRoute;
				ls_RawCdr[ln_TotalRated_CDRS]						=		lo_PMJobPtr->ga_RatedCdrs[i].gs_RawCdr; //Added By Maneesh
				/*if (lo_PMJobPtr->ga_RatedCdrs[i].gs_Imsi=="")
				{
					ln_Imsi[ln_TotalRated_CDRS]						=0;
				}
				else
				{
					ln_Imsi[ln_TotalRated_CDRS]						=		atof(lo_PMJobPtr->ga_RatedCdrs[i].gs_Imsi.c_str());
				}*/
				ln_Imsi[ln_TotalRated_CDRS]				=		lo_PMJobPtr->ga_RatedCdrs[i].gs_Imsi;
				ls_SgsnAddress[ln_TotalRated_CDRS]			=		lo_PMJobPtr->ga_RatedCdrs[i].gs_SgsnAddress;
				ls_ANumber[ln_TotalRated_CDRS]				=		lo_PMJobPtr->ga_RatedCdrs[i].gs_ANumber;
				ls_BNumber[ln_TotalRated_CDRS]				=		lo_PMJobPtr->ga_RatedCdrs[i].gs_BNumber;
			 	ls_CNumber[ln_TotalRated_CDRS]				=		lo_PMJobPtr->ga_RatedCdrs[i].gs_CNumber;
			 	ls_ApnAddress[ln_TotalRated_CDRS]			=		lo_PMJobPtr->ga_RatedCdrs[i].gs_ApnAddress;
			 	ls_PdpAddress[ln_TotalRated_CDRS]			=		lo_PMJobPtr->ga_RatedCdrs[i].gs_PdpAddress;
				ld_CallDate[ln_TotalRated_CDRS]				=		lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate;
				
				ln_CallDuration[ln_TotalRated_CDRS]			=		lo_PMJobPtr->ga_RatedCdrs[i].gn_CallDuration;				
			 	ln_DataVolume_inc[ln_TotalRated_CDRS]			=	 	lo_PMJobPtr->ga_RatedCdrs[i].gn_DataVolume_inc;				
				ln_DataVolume_out[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_DataVolume_out;
				ls_Teleservice[ln_TotalRated_CDRS]			=	 	lo_PMJobPtr->ga_RatedCdrs[i].gs_Teleservice;
				ls_Bearerservice[ln_TotalRated_CDRS]			=	 	lo_PMJobPtr->ga_RatedCdrs[i].gs_Bearerservice;
				ls_CamelFlag[ln_TotalRated_CDRS]			=	 	lo_PMJobPtr->ga_RatedCdrs[i].gs_CamelFlag;			
			    ls_CamelService_level[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_CamelService_level;
				ls_CamelService_key[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_CamelService_key;
				ls_CamelDefault_call_handling[ln_TotalRated_CDRS]  	= 	lo_PMJobPtr->ga_RatedCdrs[i].gn_CamelDefault_call_handling;
				ls_CamelServer_address[ln_TotalRated_CDRS]		= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_CamelServer_address;
				ls_CamelMsc_address[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_CamelMsc_address;
				ls_CamelCall_ref_num[ln_TotalRated_CDRS]		= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_CamelCall_ref_num;
				ls_CamelInit_cf_indicator[ln_TotalRated_CDRS]		= 	lo_PMJobPtr->ga_RatedCdrs[i].gn_CamelInit_cf_indicator;
				ls_CamelDestination_num[ln_TotalRated_CDRS]		=		lo_PMJobPtr->ga_RatedCdrs[i].gs_CamelDestination_num;
				ls_CamelModification[ln_TotalRated_CDRS]		= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_CamelModification;
				ls_SupplimentaryNum[ln_TotalRated_CDRS]			=		lo_PMJobPtr->ga_RatedCdrs[i].gs_SupplimentaryNum;
				ln_NetworkTime[ln_TotalRated_CDRS]			=	 	lo_PMJobPtr->ga_RatedCdrs[i].gn_NetworkTime;
				ln_ReasonForCleardown[ln_TotalRated_CDRS]		= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_ReasonForCleardown;
				ls_PartialIndicator[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_PartialIndicator;
				ln_PartialSeqNum[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_PartialSeqNum;
				ls_ImeiNum[ln_TotalRated_CDRS]				= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_ImeiNum;
				ls_ChronoNum[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_ChronoNum;
				ls_ChargingId[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargingId;
				ls_SubscriberType[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_SubscriberType;
				ls_AgreementType[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType;
				ls_PartnerCode[ln_TotalRated_CDRS]			=	 	lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
				ls_CallDirection[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection;
				ls_Poi[ln_TotalRated_CDRS]				=	 	lo_PMJobPtr->ga_RatedCdrs[i].gs_Poi;
				ls_OriginRateZone[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginRateZone;
				ls_DestinationRateZone[ln_TotalRated_CDRS]		=	 	lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationRateZone;
				ls_DayCode[ln_TotalRated_CDRS]				= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_DayCode;
				ls_TimeType[ln_TotalRated_CDRS]				= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_TimeType;
				ls_TariffPlanCode[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_TariffPlanCode;
				ln_TariffId[ln_TotalRated_CDRS]				=	 	lo_PMJobPtr->ga_RatedCdrs[i].gn_TariffId;
				ln_Unit_rate[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_Unit_rate;
				ln_ChargeableUnits[ln_TotalRated_CDRS]			=	 	lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeableUnits;
				ln_ChargedUnits[ln_TotalRated_CDRS]			=	 	lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits;				
				ln_ChargeAmount[ln_TotalRated_CDRS]			=	 	lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeAmount;				
				ln_TaxAmount[ln_TotalRated_CDRS]			=	 	lo_PMJobPtr->ga_RatedCdrs[i].gn_TaxAmount;
				ln_SummarySeqNo[ln_TotalRated_CDRS]			=		0;
				//ld_RatedOn[ln_TotalRated_CDRS]			=	 	lo_PMJobPtr->ga_RatedCdrs[i].gd_RatedOn;
				ld_RatedOn[ln_TotalRated_CDRS]				=	 	lo_PMJobPtr->gd_DbTimeStamp;				
				ln_RevenueAmount[ln_TotalRated_CDRS]	            	=	 	lo_PMJobPtr->ga_RatedCdrs[i].gn_RevenueAmount;
				ls_Status[ln_TotalRated_CDRS]				= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_Status;
				//ln_RepriceSeqNo[ln_TotalRated_CDRS]			=	 	lo_PMJobPtr->ga_RatedCdrs[i].gn_RepriceSeqNo;
				ln_RepriceSeqNo[ln_TotalRated_CDRS]			=	 	lo_PMJobPtr->gn_RepriceSeqNo;
				ls_NumberPlanCode[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_NumberPlanCode;
				ls_RateDirection[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection;
				ls_PaymentDirection[ln_TotalRated_CDRS]			=	 	lo_PMJobPtr->ga_RatedCdrs[i].gs_PaymentDirection;
				ln_InputFileId[ln_TotalRated_CDRS]			=	 	lo_PMJobPtr->ga_RatedCdrs[i].gn_InputFileId;
				ls_RateUnit[ln_TotalRated_CDRS]				=	 	lo_PMJobPtr->ga_RatedCdrs[i].gs_RateUnit;
				ls_PartnerIdentifier[ln_TotalRated_CDRS]		= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier;
				ls_RoamingStatus[ln_TotalRated_CDRS]			= 		"P";//lo_PMJobPtr->ga_RatedCdrs[i].gs_RoamingStatus;
				ln_TempSequenceNumber[ln_TotalRated_CDRS]		= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_TempSequenceNumber;
				ln_FileSequenceNumber[ln_TotalRated_CDRS]		= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_FileSequenceNumber;
				ls_CellId[ln_TotalRated_CDRS]				=	 	lo_PMJobPtr->ga_RatedCdrs[i].gs_CellId;
				ls_DataTypeIndicator[ln_TotalRated_CDRS]		= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_DataTypeIndicator;
				ln_DiscountAmount[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_DiscountAmount;
				ln_ChargeSdr[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeSdr;
				ln_DiscountSdr[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_DiscountSdr;
				ln_TaxSdr[ln_TotalRated_CDRS]				= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_TaxSdr;
				ln_CamelFee[ln_TotalRated_CDRS]				=	 	lo_PMJobPtr->ga_RatedCdrs[i].gn_CamelFee;
				ln_CamelFeeSdr[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_CamelFeeSdr;
				ln_CamelTaxAmount[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_CamelTaxAmount;
				ln_CamelTaxSdr[ln_TotalRated_CDRS]			=		lo_PMJobPtr->ga_RatedCdrs[i].gn_CamelTaxSdr;
				ln_CamelDiscountAmount[ln_TotalRated_CDRS]		= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_CamelDiscountAmount;
				ln_CamelDiscountSdr[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_CamelDiscountSdr;
				ls_DestinationType[ln_TotalRated_CDRS]			=	 	lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationType;
				ls_DestinationSubType[ln_TotalRated_CDRS]		= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationSubType;
				ln_RecordingEntityType[ln_TotalRated_CDRS]		=	 	lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordingEntityType;
				ls_ChargeType[ln_TotalRated_CDRS]			= 		"00";//lo_PMJobPtr->ga_RatedCdrs[i].gs_ChargeType;
				ls_ServiceType[ln_TotalRated_CDRS]			=	 	lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceType;
				ls_RoamingErrorCode[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_RoamingErrorCode;
				ls_CallTypeLevel3[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gs_CallTypeLevel3;
				ln_HomeExchangeRateCode[ln_TotalRated_CDRS]		=	 	lo_PMJobPtr->ga_RatedCdrs[i].gn_HomeExchangeRateCode;
				ln_TapExchangeRateCode[ln_TotalRated_CDRS]		= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_TapExchangeRateCode;
				ln_ExchangeRate[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_ExchangeRate;
				ls_TapTaxCode[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_TapTaxCode;
				ls_TapDiscountCode[ln_TotalRated_CDRS]			=	 	lo_PMJobPtr->ga_RatedCdrs[i].gn_TapDiscountCode;
				ls_TapRecordingEntityCode[ln_TotalRated_CDRS]		= 	lo_PMJobPtr->ga_RatedCdrs[i].gn_TapRecordingEntityCode;
				ls_TapUtcOffsetCode[ln_TotalRated_CDRS]			=	 	lo_PMJobPtr->ga_RatedCdrs[i].gn_TapUtcOffsetCode;
				ls_DiscountableAmount[ln_TotalRated_CDRS]		= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_DiscountableAmount;
				ls_DiscountableAmountSdr[ln_TotalRated_CDRS]		= 	lo_PMJobPtr->ga_RatedCdrs[i].gn_DiscountableAmountSdr;
				ln_TotalUnits[ln_TotalRated_CDRS]			= 		lo_PMJobPtr->ga_RatedCdrs[i].gn_TotalUnits;
				ls_SupplimentaryActionCode[ln_TotalRated_CDRS]		= 	lo_PMJobPtr->ga_RatedCdrs[i].gs_SupplimentaryActionCode;
				ls_OriginDestinationType[ln_TotalRated_CDRS]		=	lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginDestinationType;
				ls_DialledDigits[ln_TotalRated_CDRS]			= 	lo_PMJobPtr->ga_RatedCdrs[i].gs_DialledDigits;
				ln_RecordingEntityType_SGSN[ln_TotalRated_CDRS]		=	lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordingEntityType_SGSN;
				ln_TapRecordingEntityCode_SGSN[ln_TotalRated_CDRS]	=	lo_PMJobPtr->ga_RatedCdrs[i].gn_TapRecordingEntityCode_SGSN;
				ls_DerivedServiceCode[ln_TotalRated_CDRS]		= 	lo_PMJobPtr->ga_RatedCdrs[i].gs_DerivedServiceCode;
				ls_CurrencyCode[ln_TotalRated_CDRS]			=	 	lo_PMJobPtr->ga_RatedCdrs[i].gs_CurrencyCode;
				ls_InvoiceEvent[ln_TotalRated_CDRS]			=	 	lo_PMJobPtr->ga_RatedCdrs[i].gs_InvoiceEvent;
				ln_RecordNo[ln_TotalRated_CDRS]				=		lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordNo;
				ls_LcrDestination[ln_TotalRated_CDRS]			=		lo_PMJobPtr->ga_RatedCdrs[i].gs_LcrDestination;
				ls_NrtrdeFlag[ln_TotalRated_CDRS]			=		"";
				ln_NrtrdeSequenceNumber[ln_TotalRated_CDRS]		=		0;
				ls_Mnp[ln_TotalRated_CDRS]                          	=        lo_PMJobPtr->ga_RatedCdrs[i].gs_Mnp;

		
			
				

				//Added as per LTE usage for 4.3 release
				if(lo_PMJobPtr->ga_RatedCdrs[i].gs_AUserId == " ")
				{
					ls_AUserId[ln_TotalRated_CDRS] ="";
				}
		else{
					ls_AUserId[ln_TotalRated_CDRS]				=	lo_PMJobPtr->ga_RatedCdrs[i].gs_AUserId;
				}

				if(lo_PMJobPtr->ga_RatedCdrs[i].gs_BUserId == " ")
				{
					ls_BUserId[ln_TotalRated_CDRS] ="";
				}
				else{
					ls_BUserId[ln_TotalRated_CDRS]                         	=       lo_PMJobPtr->ga_RatedCdrs[i].gs_BUserId;
				}

				if(lo_PMJobPtr->ga_RatedCdrs[i].gs_EventReference ==" ")
				{
					ls_EventReference[ln_TotalRated_CDRS] = "";
				}
				else{
					ls_EventReference[ln_TotalRated_CDRS]                  	=       lo_PMJobPtr->ga_RatedCdrs[i].gs_EventReference;
				}

				if(lo_PMJobPtr->ga_RatedCdrs[i].gs_APN_OperatorId ==" ")
				{
					ls_APN_OperatorId[ln_TotalRated_CDRS]="";
				}
				else{
					ls_APN_OperatorId[ln_TotalRated_CDRS]                  	=       lo_PMJobPtr->ga_RatedCdrs[i].gs_APN_OperatorId;
				}

				if(lo_PMJobPtr->ga_RatedCdrs[i].gs_PCSCF_Address == " ")
				{
					ls_PCSCF_Address[ln_TotalRated_CDRS]="";
				}
				else{
					ls_PCSCF_Address[ln_TotalRated_CDRS]                    =       lo_PMJobPtr->ga_RatedCdrs[i].gs_PCSCF_Address;
				}
				ln_NetworkElementType1[ln_TotalRated_CDRS]              =       lo_PMJobPtr->ga_RatedCdrs[i].gn_NetworkElementType1;
				ln_NetworkElementType2[ln_TotalRated_CDRS]              =       lo_PMJobPtr->ga_RatedCdrs[i].gn_NetworkElementType2;
				ln_RecordingEntityTypePCSCF[ln_TotalRated_CDRS]         =       lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordingEntityTypePCSCF;
				ln_TAP_RecordingEntityCodePCSCF[ln_TotalRated_CDRS]     =       lo_PMJobPtr->ga_RatedCdrs[i].gn_TAP_RecordingEntityCodePCSCF;
				if(lo_PMJobPtr->ga_RatedCdrs[i].gs_origin_sub_type== " ")
				{
					ls_origin_sub_type[ln_TotalRated_CDRS]  ="";
				}
				else
				{
					ls_origin_sub_type[ln_TotalRated_CDRS]			=	lo_PMJobPtr->ga_RatedCdrs[i].gs_origin_sub_type;
				}
				
				if(lo_PMJobPtr->ga_RatedCdrs[i].gs_origin_traffic_type == " ")
				{
					ls_origin_traffic_type[ln_TotalRated_CDRS]     ="";
				}
				else
				{
					ls_origin_traffic_type[ln_TotalRated_CDRS]		=	lo_PMJobPtr->ga_RatedCdrs[i].gs_origin_traffic_type;
				}

				if(lo_PMJobPtr->ga_RatedCdrs[i].gs_destination_traffic_type == " ")
				{
					ls_destination_traffic_type[ln_TotalRated_CDRS]         ="";
				}
				else{
					ls_destination_traffic_type[ln_TotalRated_CDRS]		=	lo_PMJobPtr->ga_RatedCdrs[i].gs_destination_traffic_type;				       }
                                ls_Net[ln_TotalRated_CDRS]                          =        lo_PMJobPtr->ga_RatedCdrs[i].gs_Network_Call_Ref; //Imam changed for NETWORK_CALL_REF field data adding into the PM_RATED_CDRS table
								ls_StoreDuplicate[ln_TotalRated_CDRS]               =    lo_PMJobPtr->ga_RatedCdrs[i].gs_StoreDuplicateCdr;
                ls_OriginGroup[ln_TotalRated_CDRS]               =    lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginGroup;
				ls_DestGroup[ln_TotalRated_CDRS]                 =    lo_PMJobPtr->ga_RatedCdrs[i].gs_DestGroup;
				ls_Tierid[ln_TotalRated_CDRS]                    =    lo_PMJobPtr->ga_RatedCdrs[i].gs_Tierid;
                                ls_LcrOrigin[ln_TotalRated_CDRS]                   =               lo_PMJobPtr->ga_RatedCdrs[i].gs_LcrOrigin;
                  
				//modification end
				
				//By Prabina
				/**m_ABL_ServicePtr<<DEBUG<<"gn_CallType " <<lo_PMJobPtr->ga_RatedCdrs[i].gn_CallType<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_ServiceCode " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_NeCode" <<lo_PMJobPtr->ga_RatedCdrs[i].gs_NeCode.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_InRoute" <<lo_PMJobPtr->ga_RatedCdrs[i].gs_InRoute.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_OutRoute" <<lo_PMJobPtr->ga_RatedCdrs[i].gs_OutRoute.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_RawCdr " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_RawCdr.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_Imsi" <<lo_PMJobPtr->ga_RatedCdrs[i].gs_Imsi.c_str()<<Endl;
				
				*m_ABL_ServicePtr<<DEBUG<<"gs_ANumber " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_ANumber.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_BNumber " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_BNumber.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_CNumber " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_CNumber.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_ApnAddress " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_ApnAddress.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_PdpAddress " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_PdpAddress.c_str()<<Endl;
				
				*m_ABL_ServicePtr<<DEBUG<<"gd_CallDate " <<lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString(DDMMYYYYHHMISS).mb_getSTLString()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_Teleservice " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_Teleservice.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_Bearerservice" <<lo_PMJobPtr->ga_RatedCdrs[i].gs_Bearerservice.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_CamelFlag " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_CamelFlag.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_CamelServer_address " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_CamelServer_address.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_CamelMsc_address " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_CamelMsc_address.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_CamelCall_ref_num " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_CamelCall_ref_num.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_CamelDestination_num " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_CamelDestination_num.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_CamelModification " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_CamelModification.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_SupplimentaryNum " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_SupplimentaryNum.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_PartialSeqNum " <<lo_PMJobPtr->ga_RatedCdrs[i].gn_PartialSeqNum<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_ImeiNum " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_ImeiNum.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_ChronoNum " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_ChronoNum.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_SubscriberType " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_SubscriberType.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_AgreementType " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_PartnerCode " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_CallDirection " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_Poi " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_Poi.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_OriginRateZone " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginRateZone.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_DestinationRateZone " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationRateZone.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_DayCode" <<lo_PMJobPtr->ga_RatedCdrs[i].gs_DayCode.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_TimeType " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_TimeType.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_TariffPlanCode " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_TariffPlanCode.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_TariffId " <<lo_PMJobPtr->ga_RatedCdrs[i].gn_TariffId<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_Unit_rate " <<lo_PMJobPtr->ga_RatedCdrs[i].gn_Unit_rate<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_ChargeableUnits " <<lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeableUnits<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_ChargedUnits " <<lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"ln_SummarySeqNo 0 " <<Endl;
								
				*m_ABL_ServicePtr<<DEBUG<<"gn_CallDuration" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_CallDuration<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_DataVolume_inc" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_DataVolume_inc<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_DataVolume_out" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_DataVolume_out<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_CamelService_level" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_CamelService_level.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_CamelService_key" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_CamelService_key.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_CamelDefault_call_handling" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_CamelDefault_call_handling.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_CamelInit_cf_indicator" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_CamelInit_cf_indicator.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_NetworkTime" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_NetworkTime<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_ReasonForCleardown" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_ReasonForCleardown<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_PartialIndicator" <<lo_PMJobPtr->ga_RatedCdrs[i].gs_PartialIndicator.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_ChargingId" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargingId.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_TariffId" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_TariffId<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_Unit_rate" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_Unit_rate<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_ChargeableUnits" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeableUnits<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_ChargedUnits" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_ChargeAmount" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeAmount<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_TaxAmount" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_TaxAmount<<Endl;
				
				
				*m_ABL_ServicePtr<<DEBUG<<"gd_DbTimeStamp " <<lo_PMJobPtr->gd_DbTimeStamp.mb_toString(DDMMYYYYHHMISS).mb_getSTLString()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_Status " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_Status.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_RepriceSeqNo " <<lo_PMJobPtr->gn_RepriceSeqNo<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_NumberPlanCode " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_NumberPlanCode.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_RateDirection " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_PaymentDirection " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_PaymentDirection.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_RateUnit " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_RateUnit.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_PartnerIdentifier " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"ls_RoamingStatus  P" <<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_CellId " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_CellId.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_DataTypeIndicator " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_DataTypeIndicator.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_DestinationType " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationType.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_DestinationSubType " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationSubType.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"ls_ChargeType 00 " <<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_ServiceType " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceType.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_RoamingErrorCode" <<lo_PMJobPtr->ga_RatedCdrs[i].gs_RoamingErrorCode.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_CallTypeLevel3 " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_CallTypeLevel3.c_str()<<Endl;
				
				*m_ABL_ServicePtr<<DEBUG<<"gn_RevenueAmount" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_RevenueAmount<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_InputFileId" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_InputFileId<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_TempSequenceNumber" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_TempSequenceNumber<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_FileSequenceNumber" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_FileSequenceNumber<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_DiscountAmount" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_DiscountAmount<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_ChargeSdr" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeSdr<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_DiscountSdr" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_DiscountSdr<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_TaxSdr" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_TaxSdr<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_CamelFee" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_CamelFee<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_CamelFeeSdr" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_CamelFeeSdr<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_CamelTaxAmount" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_CamelTaxAmount<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_CamelTaxSdr" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_CamelTaxSdr<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_CamelDiscountAmount" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_CamelDiscountAmount<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_CamelDiscountSdr" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_CamelDiscountSdr<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_RecordingEntityType" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordingEntityType<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_HomeExchangeRateCode" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_HomeExchangeRateCode<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_TapExchangeRateCode" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_TapExchangeRateCode<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_ExchangeRate" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_ExchangeRate<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_TapTaxCode" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_TapTaxCode.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_TapDiscountCode" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_TapDiscountCode.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_TapRecordingEntityCode" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_TapRecordingEntityCode.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_TapUtcOffsetCode" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_TapUtcOffsetCode.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_DiscountableAmount" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_DiscountableAmount.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_DiscountableAmountSdr" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_DiscountableAmountSdr.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_TotalUnits" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_TotalUnits<<Endl;
				
				*m_ABL_ServicePtr<<DEBUG<<"gs_SupplimentaryActionCode " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_SupplimentaryActionCode.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_OriginDestinationType " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginDestinationType.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_DialledDigits " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_DialledDigits.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_DerivedServiceCode " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_DerivedServiceCode.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_CurrencyCode " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_CurrencyCode.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_InvoiceEvent " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_InvoiceEvent.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_LcrDestination " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_LcrDestination.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"ls_NrtrdeFlag  '' " <<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"ln_NrtrdeSequenceNumber 0" <<Endl;

				*m_ABL_ServicePtr<<DEBUG<<"gn_RecordingEntityType_SGSN" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordingEntityType_SGSN<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_TapRecordingEntityCode_SGSN" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_TapRecordingEntityCode_SGSN<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_RecordNo" <<lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordNo<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_Mnp" <<lo_PMJobPtr->ga_RatedCdrs[i].gs_Mnp.c_str()<<Endl;
				
				*m_ABL_ServicePtr<<DEBUG<<"gs_AUserId " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_AUserId.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_BUserId " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_BUserId.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_EventReference " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_EventReference.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_APN_OperatorId " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_APN_OperatorId.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_PCSCF_Address " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_PCSCF_Address.c_str()<<Endl;
				
				*m_ABL_ServicePtr<<DEBUG<<"gn_NetworkElementType1 " <<lo_PMJobPtr->ga_RatedCdrs[i].gn_NetworkElementType1<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_NetworkElementType2 " <<lo_PMJobPtr->ga_RatedCdrs[i].gn_NetworkElementType2<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_RecordingEntityTypePCSCF " <<lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordingEntityTypePCSCF<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gn_TAP_RecordingEntityCodePCSCF " <<lo_PMJobPtr->ga_RatedCdrs[i].gn_TAP_RecordingEntityCodePCSCF<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_origin_sub_type " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_origin_sub_type.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_origin_traffic_type " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_origin_traffic_type.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_destination_traffic_type " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_destination_traffic_type.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_Network_Call_Ref " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_Network_Call_Ref.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_StoreDuplicateCdr " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_StoreDuplicateCdr.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_OriginGroup " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginGroup.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_DestGroup " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_DestGroup.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_Tierid " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_Tierid.c_str()<<Endl;
				*m_ABL_ServicePtr<<DEBUG<<"gs_LcrOrigin " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_LcrOrigin.c_str()<<Endl; */
				
				//By Prabina End
				
				update_CallTypeCounts(lo_PMJobPtr, lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType,lo_PMJobPtr->ga_RatedCdrs[i].gn_CallType,lo_PMJobPtr->ga_RatedCdrs[i].gn_CallDuration,lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection);

				update_ATypeRatingLog(lo_PMJobPtr, lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType, 1);

				//Incrementing the rated cdrs count
				ln_TotalRated_CDRS++;

				
				// Now checking if the rated cdrs count has reached Maximum configured count(at configuation file)
				if((ln_TotalRated_CDRS > 0 ) && (ln_TotalRated_CDRS >= ln_TOTAL_CDRS))
				{
					ST_ERROR_DETAILS lr_ErrorDetail[ln_TotalRated_CDRS+1];
					try
					{	
						//Integer number indicating the size of the error details structure		
						ln_ErrorNums=ln_TotalRated_CDRS;
						lo_ABLStatement.mb_setUpdateCount(ln_TotalRated_CDRS);
						//Executing the statement now
						lo_ABLStatement.mb_executeArrayUpdate(&ln_ErrorNums,lr_ErrorDetail);
						ln_TotalRated_CDRS=0;						
					}
					catch(ABL_Exception &e)
					{
						ln_TotalRated_CDRS=0;
						//std::cout<<e.mb_getMessage()<<" total cdrs got error: " <<ln_ErrorNums<<std::endl;
							if(ln_ErrorNums!=0)
							{
							for(int n=0;n<ln_ErrorNums;n++)
							{

							ABL_String lc_ErrorMsg = lr_ErrorDetail[n].m_arrErrorMsg;
							/*ABL_String ltemp="";
							ltemp=lc_ErrorMsg.mb_subStr(0,9);
							std::cout<<n<<":"<<ltemp<<":"<<lc_ErrorMsg<<"Record No: "<<lr_ErrorDetail[n].m_irowNum<<std::endl;*/

							if((lc_ErrorMsg.mb_subStr(0,9)) == "ORA-00001")
							{
								ln_Duplicate_count++;
								lr_DuplicateCdrs.gn_FileId	=	ln_InputFileId[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gn_RecordNo	=	ln_RecordNo[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gs_ErrorCode	=	"RATE-DUPEVENT";
								ls_DupMesg			=	"Agreement Type=>";
								ls_DupMesg		+=	ls_AgreementType[lr_ErrorDetail[n].m_irowNum];						
								ls_DupMesg		+=	", Partner => ";
								ls_DupMesg		+=	ls_PartnerCode[lr_ErrorDetail[n].m_irowNum];
								ls_DupMesg		+=	", Call Dir=>";
								ls_DupMesg		+=	ls_CallDirection[lr_ErrorDetail[n].m_irowNum];
								ls_DupMesg		+=	", Service Code=>";
								ls_DupMesg		+=	ls_ServiceCode[lr_ErrorDetail[n].m_irowNum];
								ls_DupMesg		+=	", A#=>";
								ls_DupMesg		+=	ls_ANumber[lr_ErrorDetail[n].m_irowNum];
								ls_DupMesg		+=	", B#=>";
								ls_DupMesg		+=	ls_BNumber[lr_ErrorDetail[n].m_irowNum];
								ls_DupMesg		+=	", Call Date=>";
								ls_TempDate		=   ld_CallDate[lr_ErrorDetail[n].m_irowNum].mb_toString (); 
								ls_DupMesg		+=	ls_TempDate;
								ls_DupMesg		+=	", Time Type=>";
								ls_DupMesg		+=	ls_TimeType[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gs_ErrorMessage				=	ls_DupMesg;
								lr_DuplicateCdrs.gs_ErrorValue	=	ls_ChronoNum[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gd_RejectedDate.mb_fromSysDate();		
								lr_DuplicateCdrs.gs_Status				=	"NEW";
							    //lr_DuplicateCdrs.gs_ErrorCdr=	lo_PMJobPtr->ga_RatedCdrs[lr_ErrorDetail[n].m_irowNum].gs_RawCdr;
								lr_DuplicateCdrs.gs_ErrorCdr					=	ls_RawCdr[lr_ErrorDetail[n].m_irowNum];
						    	lr_DuplicateCdrs.gs_AgreementType	=	ls_AgreementType[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gs_CallDirection=ls_CallDirection[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gs_PartnerCode	=	ls_PartnerCode[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gs_ServiceCode	=	ls_ServiceCode[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gs_ALong		=	ls_ANumber[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gs_BLong	=	ls_BNumber[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gd_CallDate	=	ld_CallDate[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gs_TimeType	=	ls_TimeType[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gn_RerateSeqNo	=	0;
								lr_DuplicateCdrs.gn_CallDuration	=	ln_CallDuration[lr_ErrorDetail[n].m_irowNum];
                                lr_DuplicateCdrs.gn_DataVolume_inc  = ln_DataVolume_inc[lr_ErrorDetail[n].m_irowNum];	
								lr_DuplicateCdrs.gn_DataVolume_out  = ln_DataVolume_out[lr_ErrorDetail[n].m_irowNum];	
								lr_DuplicateCdrs.gn_ChargingId	    = ls_ChargingId[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gn_PartialSeqNum=	ln_PartialSeqNum[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gs_StoreDuplicateCdr = ls_StoreDuplicate[lr_ErrorDetail[n].m_irowNum];
                               // lr_DuplicateCdrs.gs_NetworkRef      = ls_Net[lr_ErrorDetail[n].m_irowNum];
								lo_PMJobPtr->ga_DuplicateCdrs.push_back(lr_DuplicateCdrs);
								update_ATypeRatingLog(lo_PMJobPtr, ls_AgreementType[lr_ErrorDetail[n].m_irowNum],2);		
							}	
							else 
							{
										rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
										ln_TotalRated_CDRS=0;
										ABL_String ls_command("touch ");
										ls_command +=ms_Stopsignalfile;
										system(ls_command.c_str()); 
										*m_ABL_ServicePtr<<CRITICAL<<e.mb_getMessage()<<": "<<lc_ErrorMsg<<Endl;
										lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
										return false;
							}
						}
					}
				}
					catch(...)
					{
						rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
						ABL_String ls_command("touch ");
						ls_command +=ms_Stopsignalfile;
						 system(ls_command.c_str()); 	
						*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
						lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
						return false;
					}
					
					ln_TotalRated_CDRS=0;
				}//If condition Ends - Checking the maximum count
			}//Outer For loop for total cdrs ends
			
			if((ln_TotalRated_CDRS>0) && (ln_TotalRated_CDRS<=ln_TOTAL_CDRS))
			{
				ST_ERROR_DETAILS lr_ErrorDetail[ln_TotalRated_CDRS+1];		 
				try
				{	
					
					//Integer number indicating the size of the error details structure		
					ln_ErrorNums=ln_TotalRated_CDRS;
					lo_ABLStatement.mb_setUpdateCount(ln_TotalRated_CDRS);
					lo_ABLStatement.mb_executeArrayUpdate(&ln_ErrorNums,lr_ErrorDetail);
					//lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);	
					
					
				}
				catch(ABL_Exception &e)
				{	
					//std::cout<<e.mb_getMessage()<<std::endl;
					if(ln_ErrorNums!=0)
					{
						for(int n=0;n<ln_ErrorNums;n++)
						{
							ABL_String lc_ErrorMsg = lr_ErrorDetail[n].m_arrErrorMsg;
							//std::cout<<"Exception in PM_InsertRatedCdrs::UpdateRatedCdrs : "<<lc_ErrorMsg<<"Record No: "<<lr_ErrorDetail[n].m_irowNum<<std::endl;						
							if((lc_ErrorMsg.mb_subStr(0,9)) == "ORA-00001")
							{
								ln_Duplicate_count++;
								lr_DuplicateCdrs.gn_FileId =	ln_InputFileId[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gn_RecordNo =	ln_RecordNo[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gs_ErrorCode		=	"RATE-DUPEVENT";
								ls_DupMesg	=	"Agreement Type=>";
								ls_DupMesg	+=	ls_AgreementType[lr_ErrorDetail[n].m_irowNum];						
								ls_DupMesg	+=	", Partner => ";
								ls_DupMesg	+=	ls_PartnerCode[lr_ErrorDetail[n].m_irowNum];
								ls_DupMesg	+=	", Call Dir=>";
								ls_DupMesg	+=	ls_CallDirection[lr_ErrorDetail[n].m_irowNum];
								ls_DupMesg	+=	", Service Code=>";
								ls_DupMesg	+=	ls_ServiceCode[lr_ErrorDetail[n].m_irowNum];
								ls_DupMesg	+=	", A#=>";
								ls_DupMesg	+=	ls_ANumber[lr_ErrorDetail[n].m_irowNum];
								ls_DupMesg	+=	", B#=>";
								ls_DupMesg	+=	ls_BNumber[lr_ErrorDetail[n].m_irowNum];
								ls_DupMesg	+=	", Call Date=>";
								ls_TempDate	=   ld_CallDate[lr_ErrorDetail[n].m_irowNum].mb_toString (); 
								ls_DupMesg	+=	ls_TempDate;
								ls_DupMesg	+=	", Time Type=>";
								ls_DupMesg	+=	ls_TimeType[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gs_ErrorMessage		=	ls_DupMesg;
								lr_DuplicateCdrs.gs_ErrorValue		=	ls_ChronoNum[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gd_RejectedDate.mb_fromSysDate();		
								lr_DuplicateCdrs.gs_Status="NEW";
								lr_DuplicateCdrs.gs_ErrorCdr		=	ls_RawCdr[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gs_AgreementType	=ls_AgreementType[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gs_CallDirection	=ls_CallDirection[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gs_PartnerCode		=ls_PartnerCode[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gs_ServiceCode		=ls_ServiceCode[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gs_ALong		=ls_ANumber[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gs_BLong		=ls_BNumber[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gd_CallDate		=ld_CallDate[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gs_TimeType		=ls_TimeType[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gn_RerateSeqNo		=	0;
								lr_DuplicateCdrs.gn_CallDuration		=ln_CallDuration[lr_ErrorDetail[n].m_irowNum];
                                lr_DuplicateCdrs.gn_DataVolume_inc  = ln_DataVolume_inc[lr_ErrorDetail[n].m_irowNum];	
								lr_DuplicateCdrs.gn_DataVolume_out  = ln_DataVolume_out[lr_ErrorDetail[n].m_irowNum];	
								lr_DuplicateCdrs.gn_ChargingId	    = ls_ChargingId[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gn_PartialSeqNum=	ln_PartialSeqNum[lr_ErrorDetail[n].m_irowNum];
								
								lr_DuplicateCdrs.gn_PartialSeqNum	=ln_PartialSeqNum[lr_ErrorDetail[n].m_irowNum];
								lr_DuplicateCdrs.gs_StoreDuplicateCdr = ls_StoreDuplicate[lr_ErrorDetail[n].m_irowNum];
							    //lr_DuplicateCdrs.gs_NetworkRef      = ls_Net[lr_ErrorDetail[n].m_irowNum];	
								lo_PMJobPtr->ga_DuplicateCdrs.push_back(lr_DuplicateCdrs);
								update_ATypeRatingLog(lo_PMJobPtr, ls_AgreementType[lr_ErrorDetail[n].m_irowNum],2);							
														
							
							}	
							else 
							{
								rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
								ln_TotalRated_CDRS=0;
								ABL_String ls_command("touch ");
								ls_command +=ms_Stopsignalfile;
								system(ls_command.c_str()); 
								*m_ABL_ServicePtr<<CRITICAL<<e.mb_getMessage()<<": "<<lc_ErrorMsg<<Endl;
								lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
								 return false;
							}

						}
					}
				}	
				catch(...)
				{
					rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
					ABL_String ls_command("touch ");
					ls_command +=ms_Stopsignalfile;
					 system(ls_command.c_str()); 	
					lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
					*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
					return false;
				}
			}			

		lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
	ln_Rated_count= ln_Rated_count-(ln_Duplicate_count + ln_Rejected_count + ln_Dropped_count);

	lo_PMJobPtr->gn_Rated_count = ln_Rated_count;
    lo_PMJobPtr->gn_Rejected_count = ln_Rejected_count;
	lo_PMJobPtr->gn_Dropped_count = ln_Dropped_count;
	lo_PMJobPtr->gn_Duplicate_count = ln_Duplicate_count;

	 }//end of scope
		*m_ABL_ServicePtr<<DEBUG<<"End  :" << lo_PMJobPtr->gs_fileName <<": "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;
	}
	catch(ABL_Exception &e)
	{					
		rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
		*m_ABL_ServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;
		ABL_String ls_command("touch ");
		ls_command +=ms_Stopsignalfile;
		system(ls_command.c_str()); 
		return false;						
	}
	catch(...)
	{
		rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
		ABL_String ls_command("touch ");
		ls_command +=ms_Stopsignalfile;
		 system(ls_command.c_str()); 	
		*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}

	return true;

}

	

void PM_InsertRatedCdrs::update_CallTypeCounts(PM_Job * &p_ABL_JobPtr, ABL_String AgreementType, int CallType, double CallDuration, ABL_String CallDirection)
{
	PM_Job* l_PM_Job_Local = (PM_Job*)p_ABL_JobPtr;	

		ABL_String	ls_TempConvert="";
		ABL_String  l_agreementtype_calltype=AgreementType;
		ls_TempConvert.mb_fromDouble(CallType);
		l_agreementtype_calltype+=ls_TempConvert;

		l_PM_Job_Local->gi_CallTypeCountsMapIterator=l_PM_Job_Local->ga_CallTypeCountsMap.find(l_agreementtype_calltype);
		if(l_PM_Job_Local->gi_CallTypeCountsMapIterator!=l_PM_Job_Local->ga_CallTypeCountsMap.end())
		{

			if(CallDirection=="I")
			{
				l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalIncRatedCount=l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalIncRatedCount+1;
				l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalIncRatedDuration=l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalIncRatedDuration +CallDuration;               
			}
			else
			{
				l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalOutRatedCount =l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalOutRatedCount+1;
				l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalOutRatedDuration=l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalOutRatedDuration+CallDuration;
			}			
		}
		else
		{
		//	std::cout<<"not found record for  TotalIncRatedCount and  TotalOutRatedCount in ga_CallTypeCountsMap: "<<l_agreementtype_calltype<<std::endl;
		}


}
void PM_InsertRatedCdrs::update_ATypeRatingLog(PM_Job * &p_ABL_JobPtr, ABL_String AgreementType, int a)
{
		PM_Job* l_PM_Job_Local = (PM_Job*)p_ABL_JobPtr;
	
		l_PM_Job_Local->gi_ATypeLogMapIterator=l_PM_Job_Local->ga_ATypeLogMap.find(AgreementType);
		if(l_PM_Job_Local->gi_ATypeLogMapIterator!=l_PM_Job_Local->ga_ATypeLogMap.end())
		{
			if (a==1)
			{
				l_PM_Job_Local->gi_ATypeLogMapIterator->second.gn_TotalRated_cdrs=l_PM_Job_Local->gi_ATypeLogMapIterator->second.gn_TotalRated_cdrs+1;
			}
			else if(a==2)
			{
				l_PM_Job_Local->gi_ATypeLogMapIterator->second.gn_TotalRated_cdrs=l_PM_Job_Local->gi_ATypeLogMapIterator->second.gn_TotalRated_cdrs-1;

			}
			
		}
}
