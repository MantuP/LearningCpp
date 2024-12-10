/***********************************************************
************************************************************
************************************************************
Agent Name:  PM_DeriveServicesCache.h
Module Name: FrameWork Rating
Dated: 21/01/2010


************************************************************
************************************************************
***********************************************************/

#ifndef PM_DeriveServicesCache_H
#define PM_DeriveServicesCache_H

#include "ABL_DataCache.h"
#include "ABL_String.h"
#include "ABL_DateTime.h"
#include "ABL_DbDate.h"
#include "ABL_Date.h"
#include "Base_Registry.h"


class PM_DeriveServicesCache : public ABL_DataCache
{
	public:
		PM_DeriveServicesCache(){}
		//PM_DeriveServicesCache(ABL_Date  p_Valid_From ,ABL_Date  p_Valid_To ,ABL_Date  p_test_Start_Date,ABL_Date  p_test_end_date,ABL_String p_ServiceCode ,ABL_String p_OperatorCode , ABL_String p_IncRateDirection = "",ABL_String p_OutRateDirection = "",ABL_String p_IncDefaultratezone = "",ABL_String p_OutDefaultratezone = "",ABL_String p_IncRateIntrConnect = "",ABL_String p_OutRateIntrConnect = "",ABL_String p_IncUnit = "",int p_IncQtyUnit = 0,ABL_String p_OutUnit = "",int p_OutQtyUnit = 0,ABL_String p_IncPaymentDirection = "",ABL_String p_OutPaymentDirection = "",ABL_String p_IncDestinationtype = "",ABL_String p_OutDestinationtype = "",ABL_String p_ServiceType = "",ABL_String p_DataTypeIndicator = "",ABL_String p_basic_service="",ABL_String p_identify_using="",ABL_String p_string_position="",ABL_String p_search_ring="",int p_search_ring_length=0): m_Valid_From(p_Valid_From),m_Valid_To(p_Valid_To),m_test_Start_Date(p_test_Start_Date),m_test_end_date(p_test_end_date), m_ServiceCode(p_ServiceCode),m_basic_service(p_basic_service),m_identify_using(p_identify_using),m_search_ring(p_search_ring),m_search_ring_length(p_search_ring_length){}
		PM_DeriveServicesCache(ABL_Date  pd_Valid_From ,ABL_Date  pd_Valid_To ,ABL_Date  pd_test_Start_Date,ABL_Date  pd_test_end_date,ABL_String ps_ServiceCode ,ABL_String ps_OperatorCode , ABL_String ps_RateDirection = "",ABL_String ps_Defaultratezone = "",ABL_String ps_RateZone = "",ABL_String ps_RateUnit = "",int pn_QtyUnit = 0,ABL_String ps_PaymentDirection = "",ABL_String ps_Destinationtype = "",ABL_String ps_ServiceType = "",ABL_String ps_basic_service="",ABL_String ps_identify_using="",ABL_String ps_string_position="",ABL_String ps_search_ring="",int pn_search_ring_length=0,ABL_String ps_TrafficType = "", ABL_String ps_Poi = "",ABL_String ps_CallDirection = ""): md_Valid_From(pd_Valid_From) , md_Valid_To (pd_Valid_To) ,md_test_Start_Date(pd_test_Start_Date),md_test_end_date(pd_test_end_date),ms_ServiceCode(ps_ServiceCode),ms_OperatorCode(ps_OperatorCode) ,ms_RateDirection(ps_RateDirection),ms_Defaultratezone(ps_Defaultratezone),ms_RateZone(ps_RateZone),ms_RateUnit(ps_RateUnit),mn_QtyUnit(pn_QtyUnit),ms_PaymentDirection(ps_PaymentDirection),ms_Destinationtype(ps_Destinationtype),ms_ServiceType(ps_ServiceType),ms_basic_service(ps_basic_service),ms_identify_using(ps_identify_using),ms_string_position(ps_string_position),ms_search_ring(ps_search_ring),mn_search_ring_length(pn_search_ring_length),ms_TrafficType(ps_TrafficType),ms_Poi(ps_Poi),ms_CallDirection(ps_CallDirection){}
		PM_DeriveServicesCache(const PM_DeriveServicesCache& p_copyObject);
		virtual ~PM_DeriveServicesCache(){}
		virtual Base_Registry* mb_clone() { return ((Base_Registry*) new PM_DeriveServicesCache()); }
		virtual long  mb_getSize(ABL_Service *p_ABL_ServicePtr, ABL_String p_filterCaluse) { return 1; }
		bool mb_isEqual(CBase* p_CBase_ptr);
		unsigned int mb_hash();
		CBase* mb_createCopy();
		bool mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause) ; 	
		void trim(ABL_String *ls_sIn) ;

		void mb_setValid_From(ABL_Date pd_Valid_From) { md_Valid_From = pd_Valid_From; }
		void mb_setValid_To(ABL_Date pd_Valid_To) { md_Valid_To = pd_Valid_To; }
		void mb_settest_Start_Date(ABL_Date pd_test_Start_Date) { md_test_Start_Date = pd_test_Start_Date; }
		void mb_settest_end_date(ABL_Date pd_test_end_date) { md_test_end_date = pd_test_end_date; }

		void mb_setServiceCode(ABL_String ps_ServiceCode) { ms_ServiceCode = ps_ServiceCode; }
		void mb_setOperatorCode(ABL_String ps_OperatorCode) { ms_OperatorCode = ps_OperatorCode; }

		void mb_setRateDirection(ABL_String ps_RateDirection) { ms_RateDirection = ps_RateDirection; }
		void mb_setDefaultratezone(ABL_String ps_Defaultratezone) { ms_Defaultratezone = ps_Defaultratezone; }
		void mb_setRateZone(ABL_String ps_RateZone) { ms_RateZone = ps_RateZone; }
		void mb_setPaymentDirection(ABL_String ps_PaymentDirection) { ms_PaymentDirection = ps_PaymentDirection; }	
		void mb_setRateUnit(ABL_String ps_RateUnit) { ms_RateUnit = ps_RateUnit; }
		void mb_setQtyUnit(int pn_QtyUnit) { mn_QtyUnit = pn_QtyUnit; }

		void mb_setDestinationtype(ABL_String ps_Destinationtype) { ms_Destinationtype = ps_Destinationtype; }
		void mb_setServiceType(ABL_String ps_ServiceType) { ms_ServiceType = ps_ServiceType; }
		void mb_setbasic_service(ABL_String ps_basic_service) { ms_basic_service = ps_basic_service; }
		void mb_setidentify_using(ABL_String ps_identify_using) { ms_identify_using = ps_identify_using; }
		void mb_setstring_position(ABL_String ps_string_position) { ms_string_position = ps_string_position; }
		void mb_setsearch_ring(ABL_String ps_search_ring) { ms_search_ring = ps_search_ring; }
		void mb_setsearch_ring_length(int pn_search_ring_length) { mn_search_ring_length = pn_search_ring_length; }

		void mb_setANumber(ABL_String ps_ANumber) { ms_ANumber = ps_ANumber; }
		void mb_setBNumber(ABL_String ps_BNumber) { ms_BNumber = ps_BNumber; }
		void mb_setCamel(ABL_String ps_Camel) { ms_Camel = ps_Camel; }
		 //added as per LTE usage for 4.3 release
        	void mb_setTrafficType(ABL_String ps_TrafficType) {ms_TrafficType = ps_TrafficType;}
        	void mb_setPoi(ABL_String ps_Poi) {ms_Poi = ps_Poi;}
		void mb_setCallDirection(ABL_String ps_CallDirection) {ms_CallDirection = ps_CallDirection;}
        	//modification end



		ABL_Date  mb_getValid_From() { return md_Valid_From; }
		ABL_Date  mb_getValid_To() { return md_Valid_To; }
		ABL_Date  mb_gettest_Start_Date() { return md_test_Start_Date; }
		ABL_Date  mb_gettest_end_date() { return md_test_end_date; }


		ABL_String mb_getServiceCode() { return ms_ServiceCode; }
		ABL_String mb_getOperatorCodet() { return ms_OperatorCode;}

		ABL_String mb_getRateDirection() { return ms_RateDirection;}


		ABL_String mb_getDefaultratezone() { return ms_Defaultratezone;}
		ABL_String mb_getRateZone() { return ms_RateZone;}

	
		ABL_String mb_getPaymentDirection() { return ms_PaymentDirection;}
	
		ABL_String mb_getRateUnit() { return ms_RateUnit;}
		int mb_getQtyUnit() { return mn_QtyUnit;}

		ABL_String mb_getDestinationtype() { return ms_Destinationtype;}
	
		ABL_String mb_getServiceType() { return ms_ServiceType;}
	
		ABL_String mb_getbasic_service() { return ms_basic_service;}
		ABL_String mb_getidentify_using() { return ms_identify_using;}
		ABL_String mb_getstring_position() { return ms_string_position;}
		ABL_String mb_getsearch_ring() { return ms_search_ring;}
		int mb_getsearch_ring_length() { return mn_search_ring_length;}

		ABL_String mb_getANumber() { return ms_ANumber;}
		ABL_String mb_getBNumber() { return ms_BNumber;}
		ABL_String mb_getCamel() { return ms_Camel;}
		//added as per LTE usage
        	ABL_String mb_getTrafficType() { return ms_TrafficType;}
        	ABL_String mb_getPoi() { return ms_Poi;}
			ABL_String mb_getCallDirection() { return ms_CallDirection;}
        	//modification end



protected:	
		ABL_Date        md_Valid_From ;
        ABL_Date        md_Valid_To ;
        ABL_Date        md_test_Start_Date ;
        ABL_Date        md_test_end_date;

        ABL_String      ms_ServiceCode;
		ABL_String      ms_OperatorCode;

        ABL_String      ms_RateDirection;

		ABL_String      ms_Defaultratezone;
        ABL_String      ms_RateZone;

        ABL_String      ms_PaymentDirection;

        ABL_String      ms_RateUnit;
        int             mn_QtyUnit;
		ABL_String      ms_Destinationtype;
       
        ABL_String      ms_ServiceType;
        ABL_String      ms_basic_service;
        ABL_String      ms_identify_using;
        ABL_String      ms_string_position;
        ABL_String      ms_search_ring;
        int             mn_search_ring_length;


        ABL_String		ms_ANumber;
        ABL_String		ms_BNumber;
		ABL_String		ms_Camel;
	 //added as per LTE usage for 4.3 release
        ABL_String ms_TrafficType;
        ABL_String ms_Poi;
		ABL_String ms_CallDirection;
        //modification end
	
};

extern "C" {EXPORT Base_Registry* gb_getPM_DeriveServicesCache();}

#endif
