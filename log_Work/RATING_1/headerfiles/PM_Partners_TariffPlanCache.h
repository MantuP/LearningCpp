#ifndef PM_Partners_TariffPlanCache_H
#define PM_Partners_TariffPlanCache_H

#include "ABL_DataCache.h"
#include "ABL_String.h"
#include "Base_Registry.h"
#include "ABL_DateTime.h"
#include "ABL_DbDate.h"
#include "ABL_Date.h"


class PM_Partners_TariffPlanCache : public ABL_DataCache
{
public:
	PM_Partners_TariffPlanCache(){}
	PM_Partners_TariffPlanCache(ABL_DateTime pd_ValidFrom,ABL_DateTime pd_ValidTo,ABL_String ps_TariffPlanCode = "",ABL_String ps_TariffPlanType = "", ABL_String ps_AgreementType="",ABL_String ps_PartnerCode="") : md_ValidFrom(pd_ValidFrom),md_ValidTo(pd_ValidTo),ms_TariffPlanCode(ps_TariffPlanCode), ms_TariffPlanType(ps_TariffPlanType), ms_AgreementType(ps_AgreementType), ms_PartnerCode(ps_PartnerCode)  {}
	PM_Partners_TariffPlanCache(const PM_Partners_TariffPlanCache& pcopyObject);
	virtual ~PM_Partners_TariffPlanCache(){}
	virtual Base_Registry* mb_clone() { return ((Base_Registry*) new PM_Partners_TariffPlanCache()); }
	virtual long  mb_getSize(ABL_Service *pABLServicePtr, ABL_String pfilterClause) { return 1; }
	bool mb_isEqual(CBase* pCBaseptr);
	unsigned int mb_hash();
	CBase* mb_createCopy();
	bool mb_loadData(data_container *pcontainer, ABL_Service *pABLServiceptr,ABL_String pfilterClause) ; 	
	void trim(ABL_String *ls_sIn) ;

	void mb_setTariffPlanCode(ABL_String ps_TariffPlanCode) { ms_TariffPlanCode = ps_TariffPlanCode; }
	void mb_setTariffPlanType(ABL_String ps_TariffPlanType) { ms_TariffPlanType = ps_TariffPlanType; }
	void mb_setAgreementType(ABL_String ps_AgreementType) { ms_AgreementType = ps_AgreementType; }
	void mb_setPartnerCode(ABL_String ps_PartnerCode) { ms_PartnerCode = ps_PartnerCode; }
	void mb_setValid_From(ABL_DateTime pd_ValidFrom) { md_ValidFrom = pd_ValidFrom; }
	void mb_setValid_To(ABL_DateTime pd_ValidTo) { md_ValidTo = pd_ValidTo; }

	ABL_String mb_getTariffPlanCode() { return ms_TariffPlanCode; }
	ABL_String  mb_getTariffPlanType() { return ms_TariffPlanType; }
	ABL_String mb_getAgreementType() { return ms_AgreementType; }
	ABL_String  mb_getPartnerCode() { return ms_PartnerCode; }
	ABL_DateTime  mb_getValid_From() { return md_ValidFrom; }
	ABL_DateTime   mb_getValid_To() { return md_ValidTo; }
	
protected:
	ABL_String		ms_TariffPlanCode;
	ABL_String		ms_TariffPlanType;
	ABL_String		ms_AgreementType;
	ABL_String		ms_PartnerCode;
	ABL_DateTime	md_ValidFrom ;
	ABL_DateTime	md_ValidTo ;	

};

extern "C" {EXPORT Base_Registry* gb_getPM_Partners_TariffPlanCache();}

#endif
