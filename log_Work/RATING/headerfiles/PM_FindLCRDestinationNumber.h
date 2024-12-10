#ifndef PM_FindLCRDestinationNumber_H
#define PM_FindLCRDestinationNumber_H
#include "PM_Job.h"
#include "ABL_Process.h"
#include "ABL_String.h"
#include "CHashTable.h"
#include "ABL_CacheManager.h"
#include "PM_FindLCRDestinationCache.h"
#include <stdlib.h>

class PM_FindLCRDestinationNumber : public ABL_Process
{
public:
	PM_FindLCRDestinationNumber();
	virtual ~PM_FindLCRDestinationNumber();
	PM_FindLCRDestinationNumber(const PM_FindLCRDestinationNumber&);
	virtual Base_Registry* mb_clone();
	virtual ABL_Process* mb_createCopy();
	virtual bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr = NULL); 
	virtual bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
	virtual bool mb_process(ABL_Job* &p_ABL_JobPtr);
	virtual bool mb_stop();		
protected:
	PM_FindLCRDestinationCache*		mo_LCRDestinationCachePtr; 
	data_container*					mo_LCRDestinationCachecacheContainer;
	ABL_String						ms_Stopsignalfile;
	int								mn_MinLength;
	int								mn_MaxLength;
	ABL_Service*			mo_ABLServicePtr;
};

extern "C" {EXPORT Base_Registry* gb_getPM_FindLCRDestinationNumber();}

#endif
