/***********************************************************
************************************************************
************************************************************
Agent Name:  PM_ValidateService.h
Module Name: FrameWork Rating
Dated: 21/01/2010


************************************************************
************************************************************
***********************************************************/

#ifndef PM_ValidateService_H
#define PM_ValidateService_H

//#include <tchar.h>
#include "PM_Job.h"
#include "ABL_Process.h"
#include "ABL_String.h"
#include "CHashTable.h"
#include "ABL_CacheManager.h"
#include "PM_ValidServicesCache.h"
#include <stdlib.h>

class PM_ValidServicesCache;


class PM_ValidateService : public ABL_Process
{
public:
	PM_ValidateService();
	virtual ~PM_ValidateService();
	PM_ValidateService(const PM_ValidateService&);
	virtual Base_Registry* mb_clone();
	virtual ABL_Process* mb_createCopy();
	virtual bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr = NULL); 
	virtual bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
	virtual bool mb_process(ABL_Job* &p_ABL_JobPtr);
	virtual bool mb_stop();
	ABL_String fnGetDateTime();	
	
protected:
	
	data_container					*mo_ServicesCachecacheContainer;
	PM_ValidServicesCache        	*mo_ServicesCachePtr; 	
	ABL_String                      ms_Stopsignalfile;
	ABL_Service*					mo_ABLServicePtr;
	
};

extern "C" {EXPORT Base_Registry* gb_getPM_ValidateService();}

#endif
