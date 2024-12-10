#include "LastDummyAgent.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>

#include <sys/stat.h>
#include <time.h>
#ifdef WIN32
#include <io.h>
#else
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif



extern "C" {EXPORT 
Base_Registry* gb_getLastDummyAgent()
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
	this->m_ABL_ServicePtr			=   p_copyObject.m_ABL_ServicePtr;
	this->ms_Lockfilepath			=	p_copyObject.ms_Lockfilepath;
	this->ms_Stopsignalfile			=	p_copyObject.ms_Stopsignalfile;
	this->mn_ProcessID				=	p_copyObject.mn_ProcessID;
}

Base_Registry* LastDummyAgent::mb_clone()
{
	return ( (Base_Registry*) new LastDummyAgent );
}

ABL_Process* LastDummyAgent::mb_createCopy()
{
	return ( new LastDummyAgent (*this));
}

bool LastDummyAgent::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{

	m_ABL_ServicePtr = p_ABL_ServicePtr;	
	try
	{				
				p_ABL_AgentCommunicatorPtr->mb_getParameter("STOP_FILE",ms_Stopsignalfile);
				p_ABL_AgentCommunicatorPtr->mb_getParameter("LockFile",ms_Lockfilepath);
				mn_ProcessID= m_ABL_ServicePtr->mb_getInt("PROCESS_ID");

	}
	catch(ABL_Exception &e)
	{
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str()); 	
		*m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
	}
	catch(...)
	{
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str()); 	
		*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}	
	return true;
}

bool LastDummyAgent::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{	
	return true;
}

bool LastDummyAgent::mb_process(ABL_Job* &p_ABL_JobPtr)
{
	PM_Job* lo_PMJobPtr = (PM_Job*)p_ABL_JobPtr;

	 return true;
}

bool LastDummyAgent::mb_stop()
{

        //ABL_Job* &p_ABL_JobPtr;
        //PM_Job* lo_PMJobPtr = (PM_Job*)p_ABL_JobPtr;


	try
	{
        //std::cout<<" lo_PMJobPtr->gs_SourceFilePath.c_str() :" <<lo_PMJobPtr->gs_SourceFilePath.c_str()<<std::endl;
		unlink(ms_Stopsignalfile.c_str());
		unlink(ms_Lockfilepath.c_str());
		ABL_Connection	l_ABL_Connection;
		l_ABL_Connection.mb_createConnection(*m_ABL_ServicePtr);
		UpdateProcess(mn_ProcessID,"S",&l_ABL_Connection );

	}
	catch(ABL_Exception &e)
	{
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str()); 	
		*m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
		return true;
	}
	catch(...)
	{
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str()); 			
		*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}		

	return true;
}

void LastDummyAgent:: UpdateProcess(int ProcessId,ABL_String Status,ABL_Connection *l_ABL_ConnectionPtrs)

{
	ABL_Connection *l_ABL_ConnectionPtr;
	ABL_Statement l_ABL_Statement;
	ABL_String l_sql;

	try
	{
		l_ABL_ConnectionPtr = l_ABL_ConnectionPtrs;

		//update PM_PROCESSES table.
		l_sql = "UPDATE PM_PROCESSES SET START_STOP_FLG = 'I',PROCESS_STATUS = :1, PROCESS_LAST_START_DATE= SYSDATE WHERE(PROCESS_ID=:2)"; 
		l_ABL_Statement = l_ABL_ConnectionPtr->mb_createStatement(l_sql); 
		l_ABL_Statement.mb_setString (1,Status);
		l_ABL_Statement.mb_setInt(2,ProcessId);
		l_ABL_Statement.mb_executeUpdate();
		l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);

		//update pm_process_status table.
		l_sql = "update PM_PROCESS_STATUS set STOP_TIME=sysdate, ELAPSED_TIME=0, REMARKS='Normal stop after detecting the stop signal' where(PROCESS_ID=:1 and UNIX_PID=:2)"; 
		l_ABL_Statement = l_ABL_ConnectionPtr->mb_createStatement(l_sql); 
		l_ABL_Statement.mb_setInt (1,ProcessId);
		l_ABL_Statement.mb_setInt(2,getpid());
		l_ABL_Statement.mb_executeUpdate();
		l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);
		l_ABL_ConnectionPtr->mb_commit();
	}

	catch(ABL_Exception &e)
	{
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str()); 	
		*m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
	}
	catch(...)
	{
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str()); 	
		*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
	}	

}




