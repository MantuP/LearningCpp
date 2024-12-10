#ifndef LastLastDummyAgent_H
#define LastDummyAgent_H
#include "ABL_Process.h"
#include "ABL_String.h"

#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "PM_Job.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include <stdlib.h>

class LastDummyAgent : public ABL_Process
{
public:
	LastDummyAgent();
	virtual ~LastDummyAgent();
	LastDummyAgent(const LastDummyAgent&);
	Base_Registry* mb_clone();
	ABL_Process* mb_createCopy();
	bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr = NULL); 
	bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
	bool mb_process(ABL_Job* &p_ABL_JobPtr);
	bool mb_stop();	
	void UpdateProcess(int ProcessId,ABL_String Status,ABL_Connection *l_ABL_ConnectionPtrs);
protected:   
	ABL_String     ms_Lockfilepath ;
	ABL_String		ms_Stopsignalfile;
	int				mn_ProcessID;
	
};

extern "C" {EXPORT Base_Registry* gb_getLastDummyAgent();}

#endif
