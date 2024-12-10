#ifndef PM_Partners_Time_TypeCache_H
#define PM_Partners_Time_TypeCache_H

#include "ABL_DataCache.h"
#include "ABL_String.h"
#include "ABL_Date.h"
#include "ABL_DateTime.h"
#include "ABL_DbDate.h"
#include "Base_Registry.h"


class PM_Partners_Time_TypeCache : public ABL_DataCache
{
public:
	PM_Partners_Time_TypeCache(ABL_String ps_StartTime="",ABL_String ps_EndTime="",ABL_String ps_DayCode="" ,ABL_String ps_TimeType = "", ABL_String ps_TariffPlanCode="") :  ms_StartTime(ps_StartTime), ms_EndTime(ps_EndTime),ms_DayCode(ps_DayCode), ms_TimeType(ps_TimeType), ms_TariffPlanCode(ps_TariffPlanCode) {}
	PM_Partners_Time_TypeCache(const PM_Partners_Time_TypeCache& pcopyObject);
	virtual ~PM_Partners_Time_TypeCache(){}
	virtual Base_Registry* mb_clone() { return ((Base_Registry*) new PM_Partners_Time_TypeCache()); }
	virtual long  mb_getSize(ABL_Service *pABLServicePtr, ABL_String pfilterCaluse) { return 1; }
	bool mb_isEqual(CBase* pCBaseptr);
	unsigned int mb_hash(){ return ms_DayCode.mb_hash(); }
	CBase* mb_createCopy();
	bool mb_loadData(data_container *pcontainer, ABL_Service *pABLServiceptr,ABL_String pfilterClause) ; 	
	void trim(ABL_String *ls_sIn) ;

	void mb_setDayCode(ABL_String ps_DayCode) { ms_DayCode = ps_DayCode; }
	void mb_setTimeType(ABL_String  ps_TimeType) { ms_TimeType = ps_TimeType; }
	void mb_setTariffPlanCode(ABL_String ps_TariffPlanCode) { ms_TariffPlanCode = ps_TariffPlanCode; }
	void mb_setStartTime(ABL_String ps_StartTime) { ms_StartTime = ps_StartTime; }
	void mb_setEndTime(ABL_String ps_EndTime) { ms_EndTime = ps_EndTime; }

	ABL_String  mb_getDayCode() { return ms_DayCode; }
	ABL_String  mb_getTimeType() { return ms_TimeType; }	
	ABL_String  mb_getTariffPlanCode() { return ms_TariffPlanCode; }

	ABL_String  mb_getStartTime() { return ms_StartTime; }
	ABL_String  mb_getEndTime() { return ms_EndTime; }
	
	
protected:
	ABL_String		ms_DayCode;
	ABL_String		ms_TimeType;	
	ABL_String		ms_TariffPlanCode;
	ABL_String		ms_StartTime;
	ABL_String		ms_EndTime;
};

extern "C" {EXPORT Base_Registry* gb_getPM_Partners_Time_TypeCache();}

#endif
