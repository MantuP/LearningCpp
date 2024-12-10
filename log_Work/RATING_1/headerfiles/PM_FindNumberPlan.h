#ifndef PM_FindNumberPlan_H
#define PM_FindNumberPlan_H
#include "PM_Job.h"
#include "ABL_Process.h"
#include "ABL_String.h"
#include "CHashTable.h"
#include "ABL_CacheManager.h"
#include <stdlib.h>
class PM_Find_NumberPlanCache;


class PM_FindNumberPlan : public ABL_Process
{
public:
	PM_FindNumberPlan();
	virtual ~PM_FindNumberPlan();
	PM_FindNumberPlan(const PM_FindNumberPlan&);
	virtual Base_Registry* mb_clone();
	virtual ABL_Process* mb_createCopy();
	virtual bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr = NULL); 
	virtual bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
	virtual bool mb_process(ABL_Job* &p_ABL_JobPtr);
	virtual bool mb_stop();
protected:
	
	data_container*		mo_NumberPlanCachecacheContainer;
	PM_Find_NumberPlanCache *mo_NumberPlanCachePtr;
	ABL_String	ms_Stopsignalfile;
	ABL_Service*			mo_ABLServicePtr;
};

extern "C" {EXPORT Base_Registry* gb_getPM_FindNumberPlan();}

#endif
