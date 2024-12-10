#ifndef PM_Partner_TariffCache_H
#define PM_Partner_TariffCache_H

#include "ABL_DataCache.h"
#include "ABL_String.h"
#include "Base_Registry.h"
#include "ABL_DateTime.h"
#include "ABL_DbDate.h"
#include "ABL_Date.h"


class PM_Partner_TariffCache : public ABL_DataCache
{
public:	
	PM_Partner_TariffCache(ABL_DateTime pd_ValidFrom,ABL_DateTime pd_ValidTo,double pn_TariffId = 0,ABL_String ps_TariffPlanCode = "",ABL_String ps_ServiceCode = "" ,ABL_String ps_RateZone = "",ABL_String ps_TimeType = "",ABL_String ps_CallDirection = "",int pn_InitialFreeUnit = 0,int pn_MinChargebleUnit = 0,double pn_InitialFlatAmt = 0,double pn_MinAmount = 0,double pn_UnitRate = 0,double pn_TaxPercent = 0,ABL_String ps_ChargeType = "",int pn_QtyPerUnit = 0,ABL_String ps_RoundUnits="",ABL_String ps_CurrencyCode="",ABL_String ps_Invoice="",ABL_String ps_TariffType="",int ps_RevenueShare = 0,ABL_String ps_DayCode="", ABL_String ps_Tier="") :  md_ValidFrom(pd_ValidFrom),md_ValidTo(pd_ValidTo),mn_TariffId(pn_TariffId),ms_TariffPlanCode(ps_TariffPlanCode),ms_ServiceCode(ps_ServiceCode),ms_RateZone(ps_RateZone),ms_TimeType(ps_TimeType),ms_CallDirection(ps_CallDirection),mn_InitialFreeUnit(pn_InitialFreeUnit),mn_MinChargebleUnit(pn_MinChargebleUnit),mn_InitialFlatAmt(pn_InitialFlatAmt),mn_MinAmount(pn_MinAmount),mn_UnitRate(pn_UnitRate),mn_TaxPercent(pn_TaxPercent),ms_ChargeType(ps_ChargeType),mn_QtyPerUnit(pn_QtyPerUnit),ms_RoundUnits(ps_RoundUnits),ms_CurrencyCode(ps_CurrencyCode),ms_Invoice(ps_Invoice), ms_TariffType(ps_TariffType),ms_RevenueShare(ps_RevenueShare),ms_DayCode(ps_DayCode),ms_Tier(ps_Tier) {}
	PM_Partner_TariffCache(){}
	PM_Partner_TariffCache(const PM_Partner_TariffCache& pcopyObject);
	virtual ~PM_Partner_TariffCache(){}
	virtual Base_Registry* mb_clone() { return ((Base_Registry*) new PM_Partner_TariffCache()); }
	virtual long   mb_getSize(ABL_Service *pABLServicePtr, ABL_String pfilterCaluse) { return 1; }
	bool mb_isEqual(CBase* pCBase_ptr);
	unsigned int mb_hash(){ return ms_RateZone.mb_hash(); }
	CBase* mb_createCopy();
	bool mb_loadData(data_container *pcontainer, ABL_Service *pABLServiceptr,ABL_String pfilterClause) ; 
	void trim(ABL_String *ls_sIn) ;
	
	void mb_setTariffPlanCode(ABL_String ps_TariffPlanCode) { ms_TariffPlanCode = ps_TariffPlanCode; }
	void mb_setCallDirection(ABL_String ps_CallDirection) { ms_CallDirection = ps_CallDirection; }
	void mb_setServiceCode(ABL_String ps_ServiceCode) { ms_ServiceCode = ps_ServiceCode; }
	void mb_setTimeType(ABL_String ps_TimeType) { ms_TimeType = ps_TimeType; }
	void mb_setRateZone(ABL_String ps_RateZone) { ms_RateZone = ps_RateZone; }
	void mb_setDayCode(ABL_String ps_DayCode) { ms_DayCode = ps_DayCode; }
	
	void mb_setValid_From(ABL_DateTime pd_ValidFrom) { md_ValidFrom = pd_ValidFrom; }
	void mb_setValid_To(ABL_DateTime pd_ValidTo) { md_ValidTo = pd_ValidTo; }
	void mb_setTier(ABL_String ps_Tier) { ms_Tier = ps_Tier; }

	double mb_getTariffId() { return mn_TariffId; }
	ABL_String mb_getTariffPlanCode() { return ms_TariffPlanCode; }
	ABL_String mb_getServiceCode() { return ms_ServiceCode;}
	ABL_String mb_getRateZone() { return ms_RateZone;}
	ABL_String mb_getTimeType() { return ms_TimeType;}
	ABL_String mb_getCallDirection() { return ms_CallDirection;}
	int mb_getInitialFreeUnit() { return mn_InitialFreeUnit;}
	int mb_getMinChargebleUnit() { return mn_MinChargebleUnit;}
	double mb_getInitialFlatAmt() { return mn_InitialFlatAmt;}
	double mb_getMinAmount() { return mn_MinAmount;}
	double mb_getUnitRate() { return mn_UnitRate;}
	double mb_getTaxPercent() { return mn_TaxPercent;}
	ABL_String mb_getChargeType() { return ms_ChargeType;}
	ABL_String mb_getRoundUnits() { return ms_RoundUnits;}
	ABL_String mb_getCurrencyCode() { return ms_CurrencyCode;}
	ABL_String mb_getInvoice() { return ms_Invoice;}
	ABL_String mb_getTariffType() { return ms_TariffType;}
        ABL_String  mb_getDayCode(){return ms_DayCode;}
     ABL_String  mb_getTier(){return ms_Tier;}

	
	int mb_getQtyPerUnit() { return mn_QtyPerUnit;}
	ABL_DateTime  mb_getValid_From() { return md_ValidFrom; }
	ABL_DateTime  mb_getValid_To() { return md_ValidTo; }
  	int mb_getRevenueShare() { return ms_RevenueShare;}

protected:		
		double			mn_TariffId;
		ABL_String		ms_TariffPlanCode;
		ABL_String		ms_ServiceCode;
		ABL_String		ms_RateZone;
		ABL_String		ms_TimeType;
		ABL_String		ms_CallDirection;
		int				mn_InitialFreeUnit;
		int				mn_MinChargebleUnit;
		double			mn_InitialFlatAmt;
		double			mn_MinAmount;
		double			mn_UnitRate;
		double			mn_TaxPercent;
		ABL_String		ms_ChargeType;
		int				mn_QtyPerUnit;
		ABL_String		ms_RoundUnits;
		ABL_String		ms_CurrencyCode;
		ABL_String		ms_Invoice;
		ABL_String		ms_TariffType;
		ABL_DateTime	md_ValidFrom ;
		ABL_DateTime	md_ValidTo ;
	    int             ms_RevenueShare;
		ABL_String      ms_DayCode;
		ABL_String      ms_Tier;
	

};

extern "C" {EXPORT Base_Registry* gb_getPM_Partner_TariffCache();}

#endif
