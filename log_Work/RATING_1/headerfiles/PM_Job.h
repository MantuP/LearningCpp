#ifndef PM_JOB_H
#define PM_JOB_H
#include<map>
#include "ABL_Job.h"
#include "ABL_DateTime.h"
#include "ABL_Date.h"
#include "ABL_DbDate.h"
#include "ABL_String.h"
#include<errno.h>

#define READ_STRING_SIZE        1400

struct gr_RatedCdr
	{
		int			gn_CallType;
		ABL_String		gs_ServiceCode;
		ABL_String		gs_NeCode ;
		ABL_String		gs_InRoute;
		ABL_String		gs_OutRoute;
		ABL_String		gs_Imsi;
		ABL_String		gs_SgsnAddress;
		ABL_String		gs_ANumber;
		ABL_String		gs_BNumber;
		ABL_String		gs_CNumber;
		ABL_String		gs_ApnAddress;
		ABL_String		gs_PdpAddress;
		ABL_DateTime		gd_CallDate;		
		unsigned int 		gn_CallDuration;
		double   		gn_DataVolume_inc;
		double   		gn_DataVolume_out;
		ABL_String		gs_Teleservice;
		ABL_String		gs_Bearerservice;
		ABL_String		gs_CamelFlag;

		ABL_String		gn_CamelService_level;
		ABL_String		gn_CamelService_key;
		ABL_String		gn_CamelDefault_call_handling;

		ABL_String		gs_CamelServer_address;
		ABL_String		gs_CamelMsc_address;
		ABL_String		gs_CamelCall_ref_num;
		ABL_String		gn_CamelInit_cf_indicator;
		ABL_String		gs_CamelDestination_num;
		ABL_String		gs_CamelModification;
		ABL_String		gs_SupplimentaryNum;
		unsigned int    	gn_NetworkTime;
		unsigned int    	gn_ReasonForCleardown;
		ABL_String		gs_PartialIndicator;
		unsigned int    	gn_PartialSeqNum;
		ABL_String		gs_ImeiNum;
		ABL_String		gs_ChronoNum;
		ABL_String		gn_ChargingId;
		ABL_String		gs_SubscriberType;
		ABL_String		gs_AgreementType;
		ABL_String		gs_PartnerCode;
		ABL_String		gs_CallDirection;
		ABL_String		gs_Poi;
		ABL_String		gs_OriginRateZone;
		ABL_String		gs_DestinationRateZone;
		ABL_String		gs_DayCode;
		ABL_String		gs_TimeType;
		ABL_String		gs_TariffPlanCode;
		unsigned int   		gn_TariffId;
		double			gn_Unit_rate;
		double			gn_ChargeableUnits;
		double			gn_ChargedUnits;
		double			gn_ChargeAmount;
		double			gn_TaxAmount;
		unsigned int		gn_SummarySeqNo;
		ABL_Date		gd_RatedOn;
		double   		gn_RevenueAmount;
		ABL_String		gs_Status;		/** default 'new' **/
		unsigned int		gn_RepriceSeqNo;
		ABL_String		gs_NumberPlanCode;
		ABL_String		gs_RateDirection;
		ABL_String		gs_PaymentDirection;
		unsigned int		gn_InputFileId;		/** not null **/
		ABL_String		gs_RateUnit;
		ABL_String		gs_PartnerIdentifier;
		ABL_String		gs_RoamingStatus;	/** default 'p' **/
		unsigned int		gn_TempSequenceNumber;
		unsigned int		gn_FileSequenceNumber;
		ABL_String		gs_CellId;
		ABL_String		gs_DataTypeIndicator;
		double			gn_DiscountAmount;		/** default 0 **/
		unsigned int		gn_ChargeSdr;		/** default 0 **/
		unsigned int		gn_DiscountSdr;		/** default 0 **/
		unsigned int		gn_TaxSdr;			/** default 0 **/
		unsigned int		gn_CamelFee;		/** default 0 **/
		unsigned int		gn_CamelFeeSdr;		/** default 0 **/
		unsigned int		gn_CamelTaxAmount;	/** default 0 **/
		unsigned int		gn_CamelTaxSdr;		/** default 0 **/
		unsigned int		gn_CamelDiscountAmount;	/** default 0 **/
		unsigned int		gn_CamelDiscountSdr;	/** default 0 **/
		ABL_String		gs_DestinationType;
		ABL_String		gs_DestinationSubType;
		unsigned int		gn_RecordingEntityType;
		ABL_String		gs_ChargeType;
		ABL_String		gs_ServiceType;
		ABL_String		gs_RoamingErrorCode;
		ABL_String		gs_CallTypeLevel3;
   		unsigned int		gn_HomeExchangeRateCode;	/** default 0 **/
		unsigned int		gn_TapExchangeRateCode;	/** default 0 **/
		unsigned int		gn_ExchangeRate;
		ABL_String		gn_TapTaxCode;		/** default 0  **/
		ABL_String		gn_TapDiscountCode;	/** default 0  **/
		ABL_String		gn_TapRecordingEntityCode; /** default 0  **/
		ABL_String		gn_TapUtcOffsetCode;	/** default 0 **/
		ABL_String		gn_DiscountableAmount;	/** default 0 **/
		ABL_String		gn_DiscountableAmountSdr;	/** default 0 **/
		double 			gn_TotalUnits; 
		unsigned int		gn_SupplemantryActionCode; 
                ABL_String		gs_SupplimentaryActionCode;
		ABL_String		gs_OriginDestinationType;               
		ABL_String		gs_rate;
		unsigned int  		gn_unitQty;		
		ABL_String		gs_BrokerCountryCode;
		ABL_String		gs_AppOwner	;
		ABL_String		gs_AllowIcTraffic;
		ABL_String		gs_ApplyDflRate_rate_on_trunk;
		ABL_String		gs_tobe_rated;
		double			gn_InitialFreeUnits;
		double			gn_MinChargeableUnits;
		double			gn_InitialFlatAmt;
		double			gn_MinAmt;              
		ABL_String		gs_DialledDigits;
		unsigned int    	gn_RecordingEntityType_SGSN;
		unsigned int    	gn_TapRecordingEntityCode_SGSN;
		ABL_String		gs_DerivedServiceCode;
		ABL_String		gs_CurrencyCode;
		ABL_String		gs_InvoiceEvent;
		unsigned int		gn_RecordNo;
		ABL_String		gs_LcrDestination;	
		ABL_String		gs_RawCdr;			
		ABL_String		gs_Charge_SMSMO_SMSC_flg;
		ABL_String		gs_RatingType;
		ABL_String		gs_time_type_temp;
		ABL_String		gs_duration_tmp ;
		ABL_String      	gs_UtcOffset;
       		ABL_String      	gs_PartnerIdentifierKey;
		ABL_String      	gs_StoreDroppedCdr;
		unsigned int		gn_MultFactor;
        	ABL_String              gs_Mnp;

		/*Added as per LTE usage for 4.3 release*/
		ABL_String		gs_AUserId;    
		ABL_String              gs_BUserId;
		ABL_String		gs_EventReference;
		ABL_String		gs_APN_OperatorId;
		ABL_String              gs_PCSCF_Address;

		unsigned int		gn_NetworkElementType1;
		unsigned int		gn_NetworkElementType2;
		unsigned int 		gn_RecordingEntityTypePCSCF;
		unsigned int		gn_TAP_RecordingEntityCodePCSCF;
		
		ABL_String		gs_origin_sub_type;
		ABL_String		gs_origin_traffic_type;
		ABL_String		gs_destination_traffic_type;
		ABL_String              gs_Network_Call_Ref;
                //modification end

		/******-Rejected or Dropped cdrs information -*****/
		ABL_String              gs_ErrorCode;
		ABL_String              gs_ErrorMessage; 
		ABL_String              gs_ErrorValue;
		ABL_String              gs_RDStatus; /* empty->rated,R->Rejected,D->dropped.*/
		ABL_String		gs_Rate;
		ABL_String      	gs_StoreDuplicateCdr;
        ABL_String              gs_HolidayId;
        ABL_String              gs_Partial;
        ABL_String              gs_OriginGroup;
        ABL_String              gs_DestGroup;
        ABL_String              gs_Tierid;
        ABL_String              gs_LcrOrigin;

	};

/*Rating Log */
struct gr_RatingLog
	{
		ABL_String              gs_CdrFileName; /** not null **/
		ABL_DateTime		gd_ReceivedOn;
		ABL_DateTime		gd_ProcessStartTime;
		ABL_DateTime		gd_ProcessEndTime;
		int                     gn_ProcessingTimeInSecs;
		ABL_String              gs_Chrono;
		ABL_String              gs_EdChrono;
		ABL_DateTime	        gd_FirstCallDtTime;
		ABL_DateTime	        gd_LastCallDtTime;
		double                  gn_TotalEvents;
		double                  gn_IncTotalEvents;
		double                  gn_IncRatedEvents;
		double                  gn_IncDroppedEvents;
		double                  gn_IncRejectedEvents;
		double                  gn_OutTotalEvents;
		double                  gn_OutRatedEvents;
		double                  gn_OutDroppedEvents;
		double                  gn_OutRejectedEvents;
		ABL_String              gs_Processed;  /** default 'n' not null **/
		double                  gn_FileId;  /** not null **/
		ABL_String              gs_Summarised;
		ABL_String              gs_Reconciled;
		ABL_String		gs_NeCode;
		ABL_String              gs_Mnp;

	};

/*Rating A-Type Log */
struct gr_RatingATypeLog
	{
		double                  gn_FileId; /** not null **/
		ABL_String              gs_AgreementType; /** not null **/
		double                  gn_TotalCdrs; /** not null **/
		double                  gn_TotalRated_cdrs; /** not null **/
		double                  gn_TotalRejected; /** not null**/
		double                  gn_TotalDropped; /** default 0 not null **/
		ABL_DateTime            gd_ProcessStartTime;
		ABL_DateTime            gd_ProcessEndTime;
		int                     gd_ProcessingTime;
		int                     gn_TotalDuplicate;
	};

/*Rejected CDRs structure */
struct gr_RejectedCdr
	{
		double                  gn_FileId; /** not null **/
		double                  gn_RecordNo; /** not null **/
		ABL_String              gs_ErrorCode; /** not null***/
		ABL_String              gs_ErrorMessage; /** not null **/
		ABL_String              gs_ErrorValue;
		ABL_DateTime            gd_RejectedDate; /** not null **/
		ABL_String              gs_Status; /** default 'new' not null **/
		ABL_String              gs_ErrorCdr; /** not null **/
		ABL_String              gs_AgreementType; /** not null **/
		int			gn_CallType;
		ABL_String              gs_CallDirection; /** not null **/
		ABL_String              gs_NeCode;
		ABL_String              gs_PartnerIdentifier;
		ABL_String              gs_PartnerCode;
		ABL_String              gs_Poi;
		ABL_String              gs_ServiceCode;
		ABL_String              gs_RateDirection;
		ABL_String              gs_PaymentDirection;
		ABL_String              gs_RateUnit;
		double                  gn_UnitQty;
		ABL_String              gs_NumberPlanCode;
		ABL_String              gs_TariffPlanCode;
		ABL_String              gs_ALong;
		ABL_String              gs_OriginRateZone;
		ABL_String              gs_BLong;
		ABL_String              gs_DestRateZone;
		ABL_DateTime	        gd_CallDate;
		ABL_String              gs_DayCode;
		ABL_String              gs_TimeType;
		double                  gn_RerateSeqNo;
        	double                  gn_CallDuration;
                ABL_String              gs_ChronoNum;
                double                  gn_PartialSeqNum;
		
		/*Added as per LTE usage for 4.3 release*/
                ABL_String              gs_AUserId;
                ABL_String              gs_BUserId;
		//modification end

		//ABL_String              gs_RawCdr;               		
	};


	/*Dupliate CDRs structure */
struct gr_DuplicateCdr
	{
		double                  gn_FileId; /** not null **/
		double                  gn_RecordNo; /** not null **/
		ABL_String              gs_ErrorCode; /** not null***/
		ABL_String              gs_ErrorMessage; /** not null **/
		ABL_String              gs_ErrorValue;
		ABL_DateTime            gd_RejectedDate; /** not null **/
		ABL_String              gs_Status; /** default 'new' not null **/
		ABL_String              gs_ErrorCdr; /** not null **/
		ABL_String              gs_AgreementType; /** not null **/
		ABL_String              gs_CallDirection; /** not null **/
		ABL_String              gs_PartnerCode;
		ABL_String              gs_ServiceCode;
		ABL_String              gs_ALong;
		ABL_String              gs_BLong;
		ABL_DateTime	        gd_CallDate;
		ABL_String              gs_TimeType;
		double                  gn_RerateSeqNo;
        double                  gn_CallDuration;
	    double          		gn_DataVolume_inc;
		double	            	gn_DataVolume_out;
		ABL_String		        gn_ChargingId;
        double                  gn_PartialSeqNum;
		ABL_String		        gs_StoreDuplicateCdr;
                ABL_String              gs_NetworkRef;
		               		
	};

/*Dropped CDRs structure*/
struct gr_DroppedCdr
	{
		double			gn_InputFileId;
		double  		gn_RecordNo;
		ABL_String      	gs_ErrorCode;
		ABL_String      	gs_ErrorMessage;
		ABL_String      	gs_ErrorValue;
		ABL_DateTime		gd_DroppedDate;
		ABL_String		gs_Status;
		ABL_String      	gs_DroppedCdr;
		ABL_String		gs_AgreementType ;
		int			gn_CallType;
		ABL_String		gs_CallDirection;
		ABL_String		gs_Necode;
		ABL_String		gs_Partneridentifier;
		ABL_String		gs_PartnerCode;
		ABL_String		gs_Poi;
		ABL_String		gs_ServiceCode;
		ABL_String		gs_RateDirection;
		ABL_String		gs_PaymentDirection;
		ABL_String		gs_UnitRate;
		int			gn_UnitQty;
		ABL_String		gs_NumberPlanCode;
		ABL_String		gs_TariffPlanCode;
		ABL_String		gs_ANumber;
		ABL_String		gs_OriginRateZone;
		ABL_String		gs_BNumber;
		ABL_String		gs_DestionRateZone;
		ABL_DateTime		gd_CallDate;
		ABL_String		gs_DayCode;
		ABL_String		gs_Timetype;
		int			gn_RerateSeqNumber;
		ABL_String		gs_DropCode;
		double          	gn_CallDuration;
		ABL_String		gs_StoreDroppedCdr;

		/*Added as per LTE usage for 4.3 release*/
                ABL_String              gs_AUserId;
                ABL_String              gs_BUserId;
		//modification end        
	};


/*** Control Parameters  ***/
struct gr_ControlParams
	{
		ABL_String		gs_RatingType;
		unsigned int		gn_MultFactor;
		ABL_String		gs_CountryDiallingCode;
		int			gn_NationalNumberLength;

	};

/*** Agreement Types ***/
struct gr_AgreementType
	{
		ABL_String		gs_AgreementType;
		ABL_String		gs_Description;
		ABL_String 		gs_PartnerIdentifierKey;
		ABL_String		gs_Invoice;
		ABL_String 		gs_SplitCalls;
		ABL_String		gs_Charge_SMSMO_On_SMSCID;
		ABL_String		gs_Store_Dropped_Cdrs;		
		ABL_String		gs_Rate;
		unsigned int		gn_MultFactor;
		ABL_String		gs_Store_Duplicate_Cdrs;
                ABL_String              gs_Partial_Search;
		
	};

struct gr_CallTypeCounts
	{   
		 int               gn_FileId;
		 ABL_String        gs_AgreementType;
		 int               gn_CallTypeEvent;
		 int               gn_TotalCount;
		 double            gn_TotalDuration;
		 int               gn_TotalIncCount;
		 double            gn_TotalIncDuration;
		 int               gn_TotalIncRatedCount;
		 double            gn_TotalIncRatedDuration;
		 int               gn_TotalIncRejCount;
		 double            gn_TotalIncRejDuration;
		 int               gn_TotalIncDropCount;
		 double            gn_TotalIncDropDuration;
		 int               gn_TotalOutCount;
		 double            gn_TotalOutDuration;
		 int               gn_TotalOutRatedCount;
		 double            gn_TotalOutRatedDuration;
		 int               gn_TotalOutRejCount;
		 double            gn_TotalOutRejDuration;
		 int               gn_TotalOutDropCount;
		 double            gn_TotalOutDropDuration;
		 int               gn_TotalUnknownRejected;
		 int               gn_TotalUnknown;
 };

class PM_Job : public ABL_Job
{
public:
	PM_Job();
	PM_Job(ABL_String& p_fileName);
	virtual ~PM_Job();
	Base_Registry* mb_clone();
	virtual ABL_String mb_getJobDetails();
	virtual void mb_revertJob();
	
	ABL_String	gs_fileName;	
	std::vector<gr_RatedCdr>ga_RatedCdrs;
	std::vector<gr_RejectedCdr>ga_RejectedCdrs;
	std::vector<gr_DuplicateCdr>ga_DuplicateCdrs;
	std::vector<gr_RatingLog>ga_RatingLog;
	std::vector<gr_ControlParams>ga_ControlParams;
	std::vector<gr_AgreementType>ga_AgreementType;
	std::vector<gr_DroppedCdr>ga_DroppedCdr;
	std::vector<ABL_String>ga_RawCDRSVector;

	std::map<ABL_String,	gr_RatingATypeLog >ga_ATypeLogMap;
	std::map<ABL_String,	gr_RatingATypeLog >::iterator gi_ATypeLogMapIterator;
	std::map<ABL_String,	gr_CallTypeCounts >ga_CallTypeCountsMap;
	std::map<ABL_String,	gr_CallTypeCounts >::iterator gi_CallTypeCountsMapIterator;	
	unsigned int			gn_TotalCDRS_In_File;
	unsigned int			gn_InPutFileId;
	unsigned int			gn_RepriceSeqNo;
	unsigned int			gn_Files_In_Rerate_Reprice_seq_no;
	ABL_String		    	gs_AgreementType;
	ABL_String			    gs_isNationalNum;
	ABL_String			    gs_IsGPRSFile;
    ABL_String              gs_Ratinglog;
	ABL_DateTime			gd_DbTimeStamp;

	ABL_String			gs_SourceFilePath;
	ABL_String			gs_ProcessedFilePath;
	ABL_String			gs_BackupFlag;
	ABL_String			gs_ErrorFile_Path;
    ABL_String          gs_DuplicateFilePath;
    unsigned int        gn_Rated_count;
    unsigned int        gn_Rejected_count;
	unsigned int        gn_Dropped_count;
	unsigned int        gn_Duplicate_count;
        ABL_String                 gs_FileStatus;
        ABL_String     gs_FileMessage;

};

#endif
