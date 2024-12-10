#ifndef  PM_Summary_H
#define  PM_Summary_H
#include "ABL_Process.h"
#include "ABL_String.h"
#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "PM_Job.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"

class PM_Summary : public ABL_Process
{
public:
	PM_Summary();
	virtual ~PM_Summary();
	PM_Summary(const PM_Summary&);
	Base_Registry* mb_clone();
	ABL_Process* mb_createCopy();
	bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr = NULL); 
	bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
	bool mb_process(ABL_Job* &p_ABL_JobPtr);
	bool mb_stop();		
	
protected:
		ABL_String		ms_Stopsignalfile ;	
    	int				op_ExecStatus ;
    	ABL_String		op_ErrCode ;
		ABL_String		op_ErrMesg;
	
	
};

extern "C" {EXPORT Base_Registry* gb_getPM_Summary();}
#endif
