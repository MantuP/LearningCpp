#ifndef PM_RatingRulesCache_H
#define PM_RatingRulesCache_H

#include "ABL_DataCache.h"
#include "ABL_String.h"
#include "ABL_DateTime.h"
#include "ABL_DbDate.h"
#include "ABL_Date.h"
#include "Base_Registry.h"

class PM_RatingRulesCache : public ABL_DataCache
{
public:
	PM_RatingRulesCache(){}
    PM_RatingRulesCache(ABL_String  ps_AgreementType, ABL_String ps_ServiceCode="", ABL_String ps_SubscriberType= "", int pn_CallType= 0, ABL_String ps_ConsiderIncLeg="", ABL_String ps_IncLegAction="", ABL_String ps_ConsiderOutLeg="", ABL_String ps_OutLegAction="", ABL_String ps_PartialSearch="N") : ms_AgreementType(ps_AgreementType), ms_ServiceCode(ps_ServiceCode), ms_SubscriberType(ps_SubscriberType), mn_CallType(pn_CallType), ms_ConsiderIncLeg(ps_ConsiderIncLeg), ms_IncLegAction(ps_IncLegAction), ms_ConsiderOutLeg(ps_ConsiderOutLeg), ms_OutLegAction(ps_OutLegAction), ms_PartialSearch(ps_PartialSearch) {}
	PM_RatingRulesCache(const PM_RatingRulesCache& p_copyObject);
	virtual ~PM_RatingRulesCache(){}
	virtual Base_Registry* mb_clone() { return ((Base_Registry*) new PM_RatingRulesCache()); }		
	virtual long  mb_getSize(ABL_Service *p_ABL_ServicePtr, ABL_String p_filterCaluse) { return 1; }
	bool mb_isEqual(CBase* p_CBase_ptr);
	unsigned int mb_hash();//{ return ms_AgreementType.mb_hash(); }
	CBase* mb_createCopy();
	bool mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause) ;
	void trim(ABL_String *ls_sIn) ;
	
	void mb_setAgreementType(ABL_String ps_AgreementType) { ms_AgreementType = ps_AgreementType; }
	void mb_setServiceCode(ABL_String ps_ServiceCode) { ms_ServiceCode = ps_ServiceCode; }
	void mb_setSubscriberType(ABL_String ps_SubscriberType) {ms_SubscriberType = ps_SubscriberType; }
	void mb_setCallType(int pn_CallType) {mn_CallType = pn_CallType; }
	void mb_setConsiderIncLeg(ABL_String ps_ConsiderIncLeg) {ms_ConsiderIncLeg = ps_ConsiderIncLeg; }
	void mb_setIncLegAction(ABL_String ps_IncLegAction) {ms_IncLegAction = ps_IncLegAction; }

	//added as per LTE
	char* itoa(int value, char* result, int base) {
		// check that the base if valid
		if (base < 2 || base > 36) { *result = '\0'; return result; }
	
		char* ptr = result, *ptr1 = result, tmp_char;
		int tmp_value;
	
		do {
			tmp_value = value;
			value /= base;
			*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
		} while ( value );
	
		// Apply negative sign
		if (tmp_value < 0) *ptr++ = '-';
		*ptr-- = '\0';
		while(ptr1 < ptr) {
			tmp_char = *ptr;
			*ptr--= *ptr1;
			*ptr1++ = tmp_char;
		}
		return result;
	}
	//modification end
    void mb_setConsiderOutLeg(ABL_String ps_ConsiderOutLeg) {ms_ConsiderOutLeg = ps_ConsiderOutLeg; }
	void mb_setOutLegAction(ABL_String ps_OutLegAction) {ms_OutLegAction = ps_OutLegAction; }
	void mb_setPartialSearch(ABL_String ps_PartialSearch) {ms_PartialSearch = ps_PartialSearch; }
    

	ABL_String  mb_getAgreementType() { return ms_AgreementType; }
	ABL_String  mb_getServiceCode() { return ms_ServiceCode; }
	ABL_String  mb_getSubscriberType() {return ms_SubscriberType; }
	int         mb_getCallType() {return mn_CallType; }
	ABL_String  mb_getConsiderIncLeg() {return  ms_ConsiderIncLeg; }
	ABL_String  mb_getIncLegAction() {return ms_IncLegAction; }
	ABL_String  mb_getConsiderOutLeg() {return ms_ConsiderOutLeg; }
	ABL_String  mb_getOutLegAction() {return ms_OutLegAction; }
   	ABL_String  mb_getPartialSearch() {return ms_PartialSearch; }
	
	protected:

	ABL_String	ms_AgreementType;
    ABL_String  ms_ServiceCode;
    ABL_String  ms_SubscriberType;
    int         mn_CallType;
	ABL_String  ms_ConsiderIncLeg;
	ABL_String  ms_IncLegAction;
	ABL_String  ms_ConsiderOutLeg;
	ABL_String  ms_OutLegAction;
	ABL_String  ms_PartialSearch;

};

extern "C" {EXPORT Base_Registry* gb_getPM_RatingRulesCache();}

#endif
