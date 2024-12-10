#ifndef PM_FindTierId_H
#define PM_FindTierId_H

//#include <tchar.h>
#include "PM_Job.h"
#include "ABL_Process.h"
#include "ABL_String.h"
#include "CHashTable.h"
#include "ABL_CacheManager.h"
#include "PM_TierMappingCache.h"
#include <stdlib.h>


class PM_FindTierId : public ABL_Process
{
public:
	PM_FindTierId();
	virtual ~PM_FindTierId();
	PM_FindTierId(const PM_FindTierId&);
	virtual Base_Registry* mb_clone();
	virtual ABL_Process* mb_createCopy();
	virtual bool mb_initProcess(ABL_CacheManager* pABLCacheManagerPtr, ABL_AgentCommunicator *pABLAgentCommunicatorPtr, ABL_Service *pABLServicePtr = NULL); 
	virtual bool mb_getCache(ABL_CacheManager* pABLCacheManagerPtr);
	virtual bool mb_process(ABL_Job* &pABLJobPtr);
	virtual bool mb_stop();
	
protected:	
	ABL_Service*					mo_ABLServicePtr;
	PM_TierMappingCache*    		mo_TierCachePtr;

	data_container*					mo_TierCacheContainer;
	
	ABL_String						ms_Stopsignalfile;	
};

extern "C" {EXPORT Base_Registry* gb_getPM_FindTierId();}

#endif
