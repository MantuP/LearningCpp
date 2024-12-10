#ifndef PM_FindDestinationRateZone_H
#define PM_FindDestinationRateZone_H
#include "PM_Job.h"
#include "ABL_Process.h"
#include "ABL_String.h"
#include <string.h>
#include "PM_DestinationCache.h"
#include "PM_FindPartnerShortCodesCache.h"
#include "PM_DestinationCache.h"
//#include "PM_NumberPlanCache.h"
#include "CHashTable.h"
#include "ABL_CacheManager.h"
#include <stdlib.h>

struct DestinationMaxMin_Length
{
	int m_MinLength;
	int m_MaxLength;
};

class PM_FindDestinationRateZone : public ABL_Process
{
public:
	PM_FindDestinationRateZone();
	virtual ~PM_FindDestinationRateZone();
	PM_FindDestinationRateZone(const PM_FindDestinationRateZone&);
	virtual Base_Registry* mb_clone();
	virtual ABL_Process* mb_createCopy();
	virtual bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr = NULL); 
	virtual bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
	virtual bool mb_process(ABL_Job* &p_ABL_JobPtr);
	virtual bool mb_stop();	
	ABL_String  fnAnalyseNumber(PM_Job * &p_ABL_JobPtr,ABL_String destination_number);

protected:

	PM_DestinationCache*	mo_DestinationCachePtr; 	
	PM_FindPartnerShortCodesCache*	mo_FindPartnerShortCodesCachePtr; 
	data_container*			mo_DestinationCachecacheContainer;	
	data_container*			mo_PartnerShortCodesCachecacheContainer;
	ABL_Service*			mo_ABLServicePtr;
	ABL_String              ms_Stopsignalfile;
	std::map<ABL_String, DestinationMaxMin_Length >mm_DestMaxMinLengthMap;
};

extern "C" {EXPORT Base_Registry* gb_getPM_FindDestinationRateZone();}

#endif
