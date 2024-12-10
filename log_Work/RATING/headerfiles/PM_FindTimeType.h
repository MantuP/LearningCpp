#ifndef PM_FindTimeType_H
#define PM_FindTimeType_H

//#include <tchar.h>
#include "PM_Job.h"
#include "ABL_Process.h"
#include "ABL_String.h"
#include "CHashTable.h"
#include "ABL_CacheManager.h"
#include "PM_HolidayCache.h"
#include "PM_Partners_Time_TypeCache.h"
#include "PM_Tariffplan_DayCodeCache.h"
#include <stdlib.h>
/*class PM_HolidayCache;
class PM_Partners_Time_TypeCache;
class PM_Tariffplan_DayCodeCache;*/


class PM_FindTimeType : public ABL_Process
{
public:
	PM_FindTimeType();
	virtual ~PM_FindTimeType();
	PM_FindTimeType(const PM_FindTimeType&);
	virtual Base_Registry* mb_clone();
	virtual ABL_Process* mb_createCopy();
	virtual bool mb_initProcess(ABL_CacheManager* pABLCacheManagerPtr, ABL_AgentCommunicator *pABLAgentCommunicatorPtr, ABL_Service *pABLServicePtr = NULL); 
	virtual bool mb_getCache(ABL_CacheManager* pABLCacheManagerPtr);
	virtual bool mb_process(ABL_Job* &pABLJobPtr);
	virtual bool mb_stop();
	ABL_String get_dayCodeStr(int dayofweek);	
protected:	
	ABL_Service*					mo_ABLServicePtr;
	PM_HolidayCache*				mo_HolidayCachePtr;
	PM_Partners_Time_TypeCache*		mo_TimeTypeCachePtr;
	PM_Tariffplan_DayCodeCache*		mo_DayCodeCachePtr;

	data_container*					mo_HolidayCacheContainer;
	data_container*					mo_TimeTypeCacheContainer;
	data_container*					mo_DayCodeCacheContainer;

	ABL_String						ms_Stopsignalfile;	
};

extern "C" {EXPORT Base_Registry* gb_getPM_FindTimeType();}

#endif
