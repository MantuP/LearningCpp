/***********************************************************
************************************************************
************************************************************
Agent Name:  PM_DeriveService.h
Module Name: FrameWork Rating
Dated: 21/01/2010


************************************************************
************************************************************
***********************************************************/
#ifndef PM_DeriveService_H
#define PM_DeriveService_H

//#include <tchar.h>
#include "PM_Job.h"
#include "ABL_Process.h"
#include "ABL_String.h"
#include "CHashTable.h"
#include "ABL_CacheManager.h"
#include "PM_DeriveServicesCache.h"
#include <stdlib.h>

class PM_DeriveServicesCache;


class PM_DeriveService : public ABL_Process
{
public:
	PM_DeriveService();
	virtual ~PM_DeriveService();
	PM_DeriveService(const PM_DeriveService&);
	virtual Base_Registry* mb_clone();
	virtual ABL_Process* mb_createCopy();
	virtual bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr = NULL); 
	virtual bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
	virtual bool mb_process(ABL_Job* &p_ABL_JobPtr);
	virtual bool mb_stop();
	ABL_String fnGetDateTime();
        void mb_trim(std::string &p_string);	
	
protected:
	data_container				*mo_DeriveServicesCachecacheContainer;	
	ABL_String                   ms_Stopsignalfile;
	PM_DeriveServicesCache      *mo_DeriveServicesCachePtr;
	ABL_Service*				mo_ABLServicePtr;
	
};

extern "C" {EXPORT Base_Registry* gb_getPM_DeriveService();}

#endif
