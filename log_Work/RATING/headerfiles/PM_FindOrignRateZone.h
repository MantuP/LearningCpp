#ifndef PM_FindOrignRateZone_H
#define PM_FindOrignRateZone_H
#include "PM_Job.h"
#include "ABL_Process.h"
#include "ABL_String.h"
#include "CHashTable.h"
#include "ABL_CacheManager.h"
#include "PM_DestinationCache.h"
#include "PM_Find_NumberPlanCache.h"
#include <stdlib.h>

struct DestinationMaxMin_Length
{
	int m_MinLength;
	int m_MaxLength;
};
class PM_FindOrignRateZone : public ABL_Process
{
public:
	PM_FindOrignRateZone();
	virtual ~PM_FindOrignRateZone();
	PM_FindOrignRateZone(const PM_FindOrignRateZone&);
	virtual Base_Registry* mb_clone();
	virtual ABL_Process* mb_createCopy();
	virtual bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr = NULL); 
	virtual bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
	virtual bool mb_process(ABL_Job* &p_ABL_JobPtr);
	virtual bool mb_stop();	
	ABL_String  fnAnalyseNumber(PM_Job * &p_ABL_JobPtr,ABL_String destination_number);
protected:
	PM_DestinationCache*	mo_DestinationCachePtr; 
	data_container*			mo_DestinationCachecacheContainer;	
	ABL_String              ms_Stopsignalfile;
	std::map<ABL_String, DestinationMaxMin_Length >mm_DestMaxMinLengthMap;
	ABL_Service*			mo_ABLServicePtr;

	data_container*		mo_NumberPlanCachecacheContainer;
	PM_Find_NumberPlanCache *mo_NumberPlanCachePtr;
};

extern "C" {EXPORT Base_Registry* gb_getPM_FindOrignRateZone();}

#endif
