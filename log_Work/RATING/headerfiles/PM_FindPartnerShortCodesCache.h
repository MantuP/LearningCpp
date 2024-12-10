#ifndef PM_FindPartnerShortCodesCache_H
#define PM_FindPartnerShortCodesCache_H

#include "ABL_DataCache.h"
#include "ABL_String.h"
#include "ABL_Date.h"
#include "ABL_DateTime.h"
#include "ABL_DbDate.h"
#include "Base_Registry.h"


class PM_FindPartnerShortCodesCache : public ABL_DataCache
{
public:
	PM_FindPartnerShortCodesCache(ABL_String ps_PartnerCode="",ABL_String ps_ShortCode="",ABL_String ps_TranslatedNumber="") :  ms_PartnerCode(ps_PartnerCode), ms_ShortCode(ps_ShortCode), ms_TranslatedNumber(ps_TranslatedNumber) {}
	PM_FindPartnerShortCodesCache(const PM_FindPartnerShortCodesCache& p_copyObject);
	virtual ~PM_FindPartnerShortCodesCache(){}
	virtual Base_Registry* mb_clone() { return ((Base_Registry*) new PM_FindPartnerShortCodesCache()); }
	virtual long  mb_getSize(ABL_Service *p_ABL_ServicePtr, ABL_String p_filterCaluse) { return 1; }
	bool mb_isEqual(CBase* p_CBase_ptr);
	unsigned int mb_hash(){ return ms_ShortCode.mb_hash(); }
	CBase* mb_createCopy();
	bool mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause) ; 
	void trim(ABL_String *ls_sIn) ;	

	void mb_setPartnerCode(ABL_String ps_PartnerCode) { ms_PartnerCode = ps_PartnerCode; }
	void mb_setShortCode(ABL_String ps_ShortCode) { ms_ShortCode = ps_ShortCode; }
	void mb_setTranslatedNumber(ABL_String ps_TranslatedNumber) { ms_TranslatedNumber = ps_TranslatedNumber; }

	ABL_String  mb_getPartnerCode() { return ms_PartnerCode; }
	ABL_String  mb_getShortCode() { return ms_ShortCode; }
	ABL_String  mb_getTranslatedNumber() { return ms_TranslatedNumber; }
	
	
protected:
	ABL_String		ms_PartnerCode;
	ABL_String		ms_ShortCode;
	ABL_String		ms_TranslatedNumber;
	
};

extern "C" {EXPORT Base_Registry* gb_getPM_FindPartnerShortCodesCache();}

#endif
