#ifndef PM_HolidayCache_H
#define PM_HolidayCache_H

#include "ABL_DataCache.h"
#include "ABL_String.h"
#include "ABL_Date.h"
#include "ABL_DateTime.h"
#include "ABL_DbDate.h"
#include "Base_Registry.h"


class PM_HolidayCache : public ABL_DataCache
{
public:
	PM_HolidayCache(ABL_DateTime pd_HolidayDate ,ABL_String ps_DayCode = "", ABL_String ps_TariffPlanCode="", ABL_String ps_HolidayId="") : md_HolidayDate(pd_HolidayDate), ms_DayCode(ps_DayCode), ms_TariffPlanCode(ps_TariffPlanCode),ms_HolidayId(ps_HolidayId)  {}
	PM_HolidayCache(){}
	PM_HolidayCache(const PM_HolidayCache& pcopyObject);
	virtual ~PM_HolidayCache(){}
	virtual Base_Registry* mb_clone() { return ((Base_Registry*) new PM_HolidayCache()); }
	virtual long  mb_getSize(ABL_Service *pABLServicePtr, ABL_String pfilterCaluse) { return 1; }
	bool mb_isEqual(CBase* pCBaseptr);
	unsigned int mb_hash(){ return ms_TariffPlanCode.mb_hash(); }
	CBase* mb_createCopy();
	bool mb_loadData(data_container *pcontainer, ABL_Service *pABLServiceptr,ABL_String pfilterClause) ; 	
	void mb_setHolidayDate(ABL_DateTime  pd_HolidayDate) { md_HolidayDate = pd_HolidayDate; }
	void mb_setDayCode(ABL_String pstDayCode) { ms_DayCode = pstDayCode; }
	void mb_setTariffPlanCode(ABL_String ps_TariffPlanCode) { ms_TariffPlanCode = ps_TariffPlanCode; }
        void mb_setHolidayId(ABL_String ps_HolidayId) {ms_HolidayId = ps_HolidayId;}
	void trim(ABL_String *ls_sIn) ;

	ABL_DateTime  mb_getHolidayDate() { return md_HolidayDate; }
	ABL_String  mb_getDayCode() { return ms_DayCode; }
	ABL_String  mb_getTariffPlanCode() { return ms_TariffPlanCode; }
        ABL_String  mb_getHolidayId() { return ms_HolidayId;}
	
protected:
	ABL_DateTime	md_HolidayDate;
	ABL_String		ms_DayCode;
	ABL_String		ms_TariffPlanCode;
        ABL_String              ms_HolidayId;
};

extern "C" {EXPORT Base_Registry* gb_getPM_HolidayCache();}

#endif
