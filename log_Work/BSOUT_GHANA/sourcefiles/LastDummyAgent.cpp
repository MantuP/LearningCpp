#include "LastDummyAgent.h"
#include <sys/stat.h>
#include <time.h>
#define INIT_STR(vc_x) (memset(vc_x,'\0',sizeof(vc_x)));
#ifdef WIN32
#include <io.h>
#else
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

extern "C" 
{
	EXPORT Base_Registry* gb_getLastDummyAgent()
	{
		return ( (Base_Registry*) new LastDummyAgent);
	}
}

LastDummyAgent::LastDummyAgent()
{
	//
}

LastDummyAgent::~LastDummyAgent()
{
	//
}

LastDummyAgent::LastDummyAgent(const LastDummyAgent& p_copyObject)
{
	this->m_ABL_ServicePtr        =       p_copyObject.m_ABL_ServicePtr;
	this->Lockfilepath		=	p_copyObject.Lockfilepath;
	this->Stopsignalpath	=	p_copyObject.Stopsignalpath;
}

Base_Registry* LastDummyAgent::mb_clone()
{
	return ( (Base_Registry*) new LastDummyAgent );
}

ABL_Process* LastDummyAgent::mb_createCopy()
{
	return ( (ABL_Process*)new LastDummyAgent (*this));
}

bool LastDummyAgent::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{
	m_ABL_ServicePtr = p_ABL_ServicePtr;

	try
	{				
		p_ABL_AgentCommunicatorPtr->mb_getParameter("STOP_FILE",Stopsignalpath);
		p_ABL_AgentCommunicatorPtr->mb_getParameter("LockFile",Lockfilepath);
	}

	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
	}

	return true;
}

bool LastDummyAgent::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{	
	return true;
}

bool LastDummyAgent::mb_process(ABL_Job* &p_ABL_JobPtr)
{
	return true;
}

bool LastDummyAgent::mb_stop()
{
	//std::cout<<"Stopping LastDummyAgent"<<std::endl;
	try
	{
		unlink(Stopsignalpath.c_str());
		unlink(Lockfilepath.c_str());
		ABL_Connection	l_ABL_Connection;
		l_ABL_Connection.mb_createConnection(*m_ABL_ServicePtr);
		UpdateProcess(5,"S",&l_ABL_Connection );
	}
	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
		return true;
	}
	return true;
}

void LastDummyAgent:: UpdateProcess(int ProcessId,ABL_String Status,ABL_Connection *l_ABL_ConnectionPtrs)
{
	ABL_Connection *l_ABL_ConnectionPtr;
	ABL_Statement l_ABL_Statement;
	ABL_ResultSet l_ABL_ResultSet;
	ABL_String l_sql;

	try
	{
		l_ABL_ConnectionPtr = l_ABL_ConnectionPtrs;
		l_sql = "UPDATE PM_PROCESSES SET START_STOP_FLG = 'I',PROCESS_STATUS = :1, PROCESS_LAST_START_DATE= SYSDATE WHERE(PROCESS_ID=:2)"; 
		l_ABL_Statement = l_ABL_ConnectionPtr->mb_createStatement(l_sql);
		l_ABL_Statement.mb_setString (1,Status);
		l_ABL_Statement.mb_setInt(2,ProcessId);
		l_ABL_Statement.mb_executeUpdate();
		l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
		l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);
		l_ABL_ConnectionPtr->mb_commit();
	}

	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr<<CRITICAL<<"RATE-1.2"<<":"<<"Main: Error Updating PM_PROCESSES for the ProcessId "<< ProcessId <<Endl;
		*m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
	}
}
