#ifndef PM_Tariffplan_DayCodeCache_H
#define PM_Tariffplan_DayCodeCache_H

#include "ABL_DataCache.h"
#include "ABL_String.h"
#include "ABL_Date.h"
#include "ABL_DateTime.h"
#include "ABL_DbDate.h"
#include "Base_Registry.h"


class PM_Tariffplan_DayCodeCache : public ABL_DataCache
{
public:
	PM_Tariffplan_DayCodeCache(ABL_String ps_DayCode , ABL_String ps_TariffPlanCode="") :  ms_DayCode(ps_DayCode), ms_TariffPlanCode(ps_TariffPlanCode)  {}
	PM_Tariffplan_DayCodeCache(){}
	PM_Tariffplan_DayCodeCache(const PM_Tariffplan_DayCodeCache& pcopyObject);
	virtual ~PM_Tariffplan_DayCodeCache(){}
	virtual Base_Registry* mb_clone() { return ((Base_Registry*) new PM_Tariffplan_DayCodeCache()); }
	virtual long  mb_getSize(ABL_Service *pABLServicePtr, ABL_String pfilterCaluse) { return 1; }
	bool mb_isEqual(CBase* pCBaseptr);
	unsigned int mb_hash(){ return ms_DayCode.mb_hash(); }
	CBase* mb_createCopy();
	bool mb_loadData(data_container *pcontainer, ABL_Service *pABLServiceptr,ABL_String pfilterClause) ; 	
	void trim(ABL_String *ls_sIn) ;

	void mb_setDayCode(ABL_String ps_DayCode) { ms_DayCode = ps_DayCode; }
	void mb_setTariffPlanCode(ABL_String ps_TariffPlanCode) { ms_TariffPlanCode = ps_TariffPlanCode; }

	
	ABL_String  mb_getDayCode() { return ms_DayCode; }
	ABL_String  mb_getTariffPlanCode() { return ms_TariffPlanCode; }
	
protected:	
	ABL_String ms_DayCode;
	ABL_String ms_TariffPlanCode;
};

extern "C" {EXPORT Base_Registry* gb_getPM_Tariffplan_DayCodeCache();}

#endif
