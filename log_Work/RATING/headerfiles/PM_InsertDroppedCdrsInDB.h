#ifndef PM_InsertDroppedCdrsInDB_H
#define PM_InsertDroppedCdrsInDB_H
#include "PM_Job.h"
#include "ABL_Process.h"
#include "ABL_String.h"
#include "CHashTable.h"
#include "ABL_CacheManager.h"
#include <stdlib.h>



class PM_InsertDroppedCdrsInDB : public ABL_Process
{
public:
	PM_InsertDroppedCdrsInDB();
	virtual ~PM_InsertDroppedCdrsInDB();
	PM_InsertDroppedCdrsInDB(const PM_InsertDroppedCdrsInDB&);
	virtual Base_Registry* mb_clone();
	virtual ABL_Process* mb_createCopy();
	virtual bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr = NULL); 
	virtual bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
	virtual bool mb_process(ABL_Job* &p_ABL_JobPtr);
	virtual bool mb_stop();	
	bool InsertCallTypeCounts(int iTotalRecords,PM_Job * &p_ABL_JobPtr);	
	bool InsertRatingALog(int iTotalRecords,PM_Job * &p_ABL_JobPtr);
	bool UpdateDroppedCdrs(int iTotalRecords,PM_Job * &p_ABL_JobPtr);
	void update_ATypeRatingLog(PM_Job * &p_ABL_JobPtr, ABL_String AgreementType);
	void update_CallTypeCounts(PM_Job * &p_ABL_JobPtr, ABL_String AgreementType, int CallType, double CallDuration, ABL_String CallDirection);	

protected:
	ABL_String      ms_Stopsignalfile;
	unsigned int	mn_DB_BULK_INSERT_COUNT;
};

extern "C" {EXPORT Base_Registry* gb_getPM_InsertDroppedCdrsInDB();}

#endif
