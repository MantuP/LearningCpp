/***********************************************************
************************************************************
************************************************************
Agent Name:  PM_FetchPartners_ServicesParametersCache.h
Module Name: FrameWork Rating
Dated: 21/01/2010


************************************************************
************************************************************
***********************************************************/

#ifndef PM_FetchPartners_ServicesParametersCache_H
#define PM_FetchPartners_ServicesParametersCache_H

#include "ABL_DataCache.h"
#include "ABL_String.h"
#include "ABL_DateTime.h"
#include "ABL_DbDate.h"
#include "ABL_Date.h"
#include "Base_Registry.h"

class PM_FetchPartners_ServicesParametersCache : public ABL_DataCache
{
public:
		PM_FetchPartners_ServicesParametersCache(){}

		PM_FetchPartners_ServicesParametersCache(ABL_String  ps_PartnerCode,ABL_String  ps_ServiceCode="",ABL_String  ps_Poi="", ABL_String  ps_CallDirection="",ABL_Date pd_ValidFrom="",ABL_Date pd_ValidTill="",ABL_String ps_ApplyDefaultRate="",ABL_String ps_RateDirection="",ABL_String ps_PaymentDirection = "",ABL_String ps_RateZone = "",ABL_String ps_DestinationType = "",ABL_Date pd_TestStartDate="",ABL_Date pd_TestEndDate="",ABL_String ps_RateUnit = "",ABL_String ps_ServiceType = "",ABL_String ps_RateAction="") : ms_PartnerCode(ps_PartnerCode),ms_ServiceCode(ps_ServiceCode),ms_Poi(ps_Poi),ms_CallDirection(ps_CallDirection),md_ValidFrom(pd_ValidFrom),md_ValidTill(pd_ValidTill),ms_ApplyDefaultRate(ps_ApplyDefaultRate),ms_RateDirection(ps_RateDirection),ms_PaymentDirection(ps_PaymentDirection),ms_RateZone(ps_RateZone),ms_DestinationType(ps_DestinationType),md_TestStartDate(pd_TestStartDate),md_TestEndDate(pd_TestEndDate),ms_RateUnit(ps_RateUnit),ms_ServiceType(ps_ServiceType),ms_RateAction(ps_RateAction){}
		PM_FetchPartners_ServicesParametersCache(const PM_FetchPartners_ServicesParametersCache& p_copyObject);
		virtual ~PM_FetchPartners_ServicesParametersCache(){}
		virtual Base_Registry* mb_clone() { return ((Base_Registry*) new PM_FetchPartners_ServicesParametersCache()); }
		virtual long  mb_getSize(ABL_Service *p_ABL_ServicePtr, ABL_String p_filterCaluse) { return 1; }
		bool mb_isEqual(CBase* p_CBase_ptr);
		unsigned int mb_hash();
		CBase* mb_createCopy();
		bool mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause) ;
		void trim(ABL_String *ls_sIn) ;

		void mb_setPartnerCode(ABL_String ps_PartnerCode) { ms_PartnerCode = ps_PartnerCode; }
		void mb_setServiceCode(ABL_String ps_ServiceCode) { ms_ServiceCode = ps_ServiceCode; }
		void mb_setPoi(ABL_String ps_Poi) { ms_Poi = ps_Poi; }
		void mb_setCallDirection(ABL_String ps_CallDirection) { ms_CallDirection = ps_CallDirection; }

		void mb_setValidFrom(ABL_Date pd_ValidFrom) { md_ValidFrom = pd_ValidFrom; }
		void mb_setValidTill(ABL_Date pd_ValidTill) { md_ValidTill = pd_ValidTill; }

		void mb_setTestStartDate(ABL_Date pd_TestStartDate) { md_TestStartDate = pd_TestStartDate; }
		void mb_setTestEndDate(ABL_Date pd_TestEndDate) { md_TestEndDate = pd_TestEndDate; }

		void mb_setApplyDefaultRate(ABL_String ps_ApplyDefaultRate) { ms_ApplyDefaultRate = ps_ApplyDefaultRate; }
		void mb_setRateDirection(ABL_String ps_RateDirection) { ms_RateDirection = ps_RateDirection; }
		void mb_setPaymentDirection(ABL_String ps_PaymentDirection) { ms_PaymentDirection = ps_PaymentDirection; }
		void mb_setRateZone(ABL_String ps_RateZone) { ms_RateZone = ps_RateZone; }
		void mb_setDestinationType(ABL_String ps_DestinationType) { ms_DestinationType = ps_DestinationType; }
        void mb_setRateUnit(ABL_String ps_RateUnit) { ms_RateUnit = ps_RateUnit; }
        void mb_setServiceType(ABL_String ps_ServiceType) { ms_ServiceType = ps_ServiceType; }
		void mb_setRateAction(ABL_String ps_RateAction) { ms_RateAction = ps_RateAction; }



		ABL_String  mb_getPartnerCode() { return ms_PartnerCode; }
		ABL_String  mb_getServiceCode() { return ms_ServiceCode; }
		ABL_String  mb_getPoi() { return ms_Poi; }
		ABL_String  mb_getCallDirection() { return ms_CallDirection; }
		ABL_Date    mb_getValidFrom() { return md_ValidFrom; }
		ABL_Date    mb_getValidTill() { return md_ValidTill; }
		ABL_Date    mb_getTestStartDate() { return md_TestStartDate; }
		ABL_Date    mb_getTestEndDate() { return md_TestEndDate; }


		ABL_String  mb_getApplyDefaultRate() { return ms_ApplyDefaultRate;}
		ABL_String  mb_getRateDirection() { return ms_RateDirection;}
		ABL_String  mb_getPaymentDirection() { return ms_PaymentDirection;}
		ABL_String  mb_getRateZone() { return ms_RateZone;}
		ABL_String  mb_getDestinationType() { return ms_DestinationType;}
        ABL_String  mb_getRateUnit() { return ms_RateUnit;}
        ABL_String  mb_getServiceType() { return ms_ServiceType;}
		ABL_String  mb_getRateAction() { return ms_RateAction;}


protected:
  
	
		ABL_String      ms_PartnerCode;
		ABL_String      ms_ServiceCode;
		ABL_String      ms_Poi;
		ABL_String      ms_CallDirection;
		ABL_Date        md_ValidFrom;
		ABL_Date        md_ValidTill;
		ABL_String      ms_ApplyDefaultRate;
		ABL_String      ms_RateDirection;
		ABL_String      ms_PaymentDirection;
		ABL_String      ms_RateZone;
		ABL_String      ms_DestinationType;
		ABL_Date        md_TestStartDate;
		ABL_Date        md_TestEndDate;
        ABL_String      ms_RateUnit;
        ABL_String      ms_ServiceType;
		ABL_String      ms_RateAction;
};

extern "C" {EXPORT Base_Registry* gb_getPM_FetchPartners_ServicesParametersCache();}

#endif
                                                               
