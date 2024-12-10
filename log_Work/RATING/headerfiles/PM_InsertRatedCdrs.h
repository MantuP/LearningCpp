#ifndef PM_InsertRatedCdrs_H
#define PM_InsertRatedCdrs_H

//#include <tchar.h>
#include "PM_Job.h"
#include "ABL_Process.h"
#include "ABL_String.h"
#include "CHashTable.h"
#include "ABL_CacheManager.h"
#include <stdlib.h>



class PM_InsertRatedCdrs : public ABL_Process
{
public:
	PM_InsertRatedCdrs();
	virtual ~PM_InsertRatedCdrs();
	PM_InsertRatedCdrs(const PM_InsertRatedCdrs&);
	virtual Base_Registry* mb_clone();
	virtual ABL_Process* mb_createCopy();
	virtual bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr = NULL); 
	virtual bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
	virtual bool mb_process(ABL_Job* &p_ABL_JobPtr);
	virtual bool mb_stop();	
	void update_CallTypeCounts(PM_Job * &p_ABL_JobPtr, ABL_String AgreementType, int CallType, double CallDuration, ABL_String CallDirection);
	bool UpdateRatedCdrs(int iTotalRecords,PM_Job * &p_ABL_JobPtr);
	void update_ATypeRatingLog(PM_Job * &p_ABL_JobPtr, ABL_String AgreementType, int a);

protected:
	ABL_String    ms_Stopsignalfile;
	unsigned int	mn_DB_BULK_INSERT_COUNT;
};

extern "C" {EXPORT Base_Registry* gb_getPM_InsertRatedCdrs();}

#endif
