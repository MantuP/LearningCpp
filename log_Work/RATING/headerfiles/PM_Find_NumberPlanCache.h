#ifndef PM_Find_NumberPlanCache_H
#define PM_Find_NumberPlanCache_H

#include "ABL_DataCache.h"
#include "ABL_String.h"
#include "ABL_DateTime.h"
#include "ABL_DbDate.h"
#include "Base_Registry.h"

class PM_Find_NumberPlanCache : public ABL_DataCache
{
public:
	PM_Find_NumberPlanCache(){}
	PM_Find_NumberPlanCache(ABL_DateTime pd_Valid_From,ABL_DateTime pd_Valid_To,ABL_String ps_NumberPlanCode = "",ABL_String ps_NumberPlanType = "", ABL_String ps_AgreementType="",ABL_String ps_PartnerCode="",ABL_String ps_POI="",ABL_String ps_BrokerCountryCode="") : md_Valid_From(pd_Valid_From),md_Valid_To(pd_Valid_To),ms_NumberPlanCode(ps_NumberPlanCode), ms_NumberPlanType(ps_NumberPlanType), ms_AgreementType(ps_AgreementType), ms_PartnerCode(ps_PartnerCode) , ms_POI(ps_POI), ms_BrokerCountryCode(ps_BrokerCountryCode) {}
	PM_Find_NumberPlanCache(const PM_Find_NumberPlanCache& p_copyObject);
	virtual ~PM_Find_NumberPlanCache(){}
	virtual Base_Registry* mb_clone() { return ((Base_Registry*) new PM_Find_NumberPlanCache()); }
	virtual long		   mb_getSize(ABL_Service *p_ABL_ServicePtr, ABL_String p_filterCaluse) { return 1; }
	bool mb_isEqual(CBase* p_CBase_ptr);
    unsigned int mb_hash();
	CBase* mb_createCopy();
	bool mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause) ; 
	void trim(ABL_String *ls_sIn) ;

	void mb_setNumberPlanCode(ABL_String ps_NumberPlanCode) { ms_NumberPlanCode = ps_NumberPlanCode; }
	void mb_setNumberPlanType(ABL_String ps_NumberPlanType) { ms_NumberPlanType = ps_NumberPlanType; }
	void mb_setAgreementType(ABL_String ps_AgreementType) { ms_AgreementType = ps_AgreementType; }
	void mb_setPartnerCode(ABL_String ps_PartnerCode) { ms_PartnerCode = ps_PartnerCode; }
	void mb_setPOI(ABL_String ps_POI) { ms_POI = ps_POI; }
	void mb_setBrokerCountryCode(ABL_String ps_BrokerCountryCode) { ms_BrokerCountryCode = ps_BrokerCountryCode; }

	void mb_setValid_From(ABL_DateTime pd_Valid_From) { md_Valid_From = pd_Valid_From; }
	void mb_setValid_To(ABL_DateTime pd_Valid_To) { md_Valid_To = pd_Valid_To; }
	

	ABL_String		mb_getNumberPlanCode() { return ms_NumberPlanCode; }
	ABL_String		mb_getNumberPlanType() { return ms_NumberPlanType; }
	ABL_String		mb_getAgreementType() { return ms_AgreementType; }
	ABL_String		mb_getPartnerCode() { return ms_PartnerCode; }
	ABL_String		mb_getPOI() { return ms_POI; }
	ABL_String		mb_getBrokerCountryCode() { return ms_BrokerCountryCode; }
	ABL_DateTime	mb_getValid_From() { return md_Valid_From; }
	ABL_DateTime	mb_getValid_To() { return md_Valid_To; }
	
protected:
	ABL_String		ms_NumberPlanCode;
	ABL_String		ms_NumberPlanType;
	ABL_String		ms_AgreementType;
	ABL_String		ms_PartnerCode;
	ABL_String		ms_POI;
	ABL_DateTime	md_Valid_From ;
	ABL_DateTime	md_Valid_To ;
	ABL_String		ms_BrokerCountryCode;
};

extern "C" {EXPORT Base_Registry* gb_getPM_Find_NumberPlanCache();}

#endif
