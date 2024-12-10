#ifndef PM_FindTariffPlan_H
#define PM_FindTariffPlan_H
#include "PM_Job.h"
#include "ABL_Process.h"
#include "ABL_String.h"
#include "CHashTable.h"
#include "ABL_CacheManager.h"
#include "PM_Partners_TariffPlanCache.h"
#include <stdlib.h>
class PM_Partners_TariffPlanCache;
class PM_FindTariffPlan : public ABL_Process
{
public:
	PM_FindTariffPlan();
	virtual ~PM_FindTariffPlan();
	PM_FindTariffPlan(const PM_FindTariffPlan&);
	virtual Base_Registry* mb_clone();
	virtual ABL_Process* mb_createCopy();
	virtual bool mb_initProcess(ABL_CacheManager* pABLCacheManagerPtr, ABL_AgentCommunicator *pABLAgentCommunicatorPtr, ABL_Service *pABLServicePtr = NULL); 
	virtual bool mb_getCache(ABL_CacheManager* pABLCacheManagerPtr);
	virtual bool mb_process(ABL_Job* &pABLJobPtr);
	virtual bool mb_stop();	
protected:
	ABL_Service						*mo_ABLServicePtr;
	PM_Partners_TariffPlanCache*	mo_TariffPlanCachePtr; 
	data_container*					mo_TariffPlanCacheContainer;	
	ABL_String						ms_Stopsignalfile;
};

extern "C" {EXPORT Base_Registry* gb_getPM_FindTariffPlan();}

#endif
