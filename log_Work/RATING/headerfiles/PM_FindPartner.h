#ifndef PM_FindPartner_H
#define PM_FindPartner_H
#include "PM_Job.h"
#include "ABL_Process.h"
#include "ABL_String.h"
#include "CHashTable.h"
#include "ABL_CacheManager.h"
#include "PM_Partners_IdentifierCache.h"
#include "PM_Partners_RoamingIdentifierCache.h"
#include "PM_FindRecordingentityTypeCache.h"
#include <stdlib.h>

class PM_Partners_IdentifierCache;




class PM_FindPartner : public ABL_Process
{
public:
	PM_FindPartner();
	virtual ~PM_FindPartner();
	PM_FindPartner(const PM_FindPartner&);
	virtual Base_Registry* mb_clone();
	virtual ABL_Process* mb_createCopy();
	virtual bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr = NULL); 
	virtual bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
	virtual bool mb_process(ABL_Job* &p_ABL_JobPtr);
	virtual bool mb_stop();	
	bool   fnValidatePartnerIdentifier(PM_Job * &p_ABL_JobPtr ,PM_Partners_IdentifierCache* &Temp_PM_IdentifierCachePtr,ABL_String	lv_Agreement,ABL_String	lv_trunkCode,ABL_String	lv_NeCode,ABL_String lv_TransferType,ABL_Date lv_CallDate);
	void trim(ABL_String *sIn) ;
	
protected:
	ABL_Service*					mo_ABLServicePtr;
	PM_Partners_IdentifierCache		*mo_IdentifierCachePtr;
	data_container					*mo_IdentifierCachecacheContainer;

	PM_Partners_RoamingIdentifierCache	*mo_RoamingIdentifierCachePtr;
	data_container					*mo_RoamingIdentifierCachecacheContainer;

	PM_FindRecordingentityTypeCache	*mo_RecordingentityTypeCachePtr;
	data_container					*mo_RecordingentityTypecacheContainer;
	
	ABL_String                      ms_Stopsignalfile;
	int								mn_MinTrunkLength;
	int								mn_MaxTrunkLength;
};

extern "C" {EXPORT Base_Registry* gb_getPM_FindPartner();}

#endif
