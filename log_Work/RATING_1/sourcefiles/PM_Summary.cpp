#include "PM_Summary.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <string.h>

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



extern "C" {EXPORT 
Base_Registry* gb_getPM_Summary()
{
		return ( (Base_Registry*) new  PM_Summary);
}
}

PM_Summary:: PM_Summary()
{
		//
}

PM_Summary::~ PM_Summary()
{
		//
}

PM_Summary:: PM_Summary(const  PM_Summary& p_copyObject)
{
	
	this->m_ABL_ServicePtr	        =	p_copyObject.m_ABL_ServicePtr;
	this->op_ExecStatus		=	p_copyObject.op_ExecStatus;
        this->op_ErrCode		=	p_copyObject.op_ErrCode;
	this->op_ErrMesg		=	p_copyObject.op_ErrMesg;
	this->ms_Stopsignalfile	        =	p_copyObject.ms_Stopsignalfile;

}

Base_Registry*  PM_Summary::mb_clone()
{
	
	return ( (Base_Registry*) new  PM_Summary );
	
}

ABL_Process*  PM_Summary::mb_createCopy()
{
	
	return ( new  PM_Summary (*this));
	
}

bool  PM_Summary::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{
	m_ABL_ServicePtr = p_ABL_ServicePtr;	
	try
	{

				

				p_ABL_AgentCommunicatorPtr->mb_getParameter("STOP_FILE",ms_Stopsignalfile);	

			

	}
	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
		return false;
			
	}	
		return true;
}

bool  PM_Summary::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{	
	return true;
}

bool  PM_Summary::mb_process(ABL_Job* &p_ABL_JobPtr)
{
   	ABL_Connection	*l_ABL_ConnectionPtr;
	ABL_Statement	l_ABL_Statement;
	ABL_ResultSet	l_ABL_ResultSet;
	ABL_String		l_sql;

	
	PM_Job* lo_PMJobPtr = (PM_Job*)p_ABL_JobPtr;	


	*m_ABL_ServicePtr<<DEBUG<< "Summary Started fro the file :" <<lo_PMJobPtr->gs_fileName<< Endl;

	
	try
	{	
		if (lo_PMJobPtr->ga_RatedCdrs.size()== 0) 
		{
			if (lo_PMJobPtr->gs_IsGPRSFile=="YES")
			{
				*m_ABL_ServicePtr<<DEBUG<<"End of Summary for the file  :"<<lo_PMJobPtr->gs_fileName << Endl;
				return true;
			}
			
		}

		*m_ABL_ServicePtr << DEBUG << "Start :" <<lo_PMJobPtr->gs_fileName <<" : "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;

		l_ABL_ConnectionPtr = lo_PMJobPtr->mb_getConnection();
		l_sql = "BEGIN PR_GENERATE_SUMMARY(:1,:2,:3,:4); END;";
		l_ABL_Statement  = l_ABL_ConnectionPtr->mb_createStatement(l_sql);
		l_ABL_Statement.mb_setDouble(1,lo_PMJobPtr->gn_InPutFileId);
		l_ABL_Statement.mb_registerOutParam(2,_INT,sizeof(int));
		l_ABL_Statement.mb_registerOutParam(3,_STRING,200);
		l_ABL_Statement.mb_registerOutParam(4,_STRING,200);
		l_ABL_Statement.mb_executeQuery();
		op_ExecStatus=l_ABL_Statement.mb_getInt(2);
		if(op_ExecStatus == 1)
		{
			op_ErrCode = l_ABL_Statement.mb_getString(3);
			op_ErrMesg = l_ABL_Statement.mb_getString(4);
			*m_ABL_ServicePtr<<CRITICAL<<op_ErrCode<<":"<<op_ErrMesg<<Endl;
			ABL_String l_command("echo .> ");
			l_command += ms_Stopsignalfile .c_str();			
			system(l_command.c_str());
			 return false;
        }		
			
	
		l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);
		*m_ABL_ServicePtr<<DEBUG<<"End of Summary for the file  :"<<lo_PMJobPtr->gs_fileName << Endl;
	}

	catch(ABL_Exception &e)
	{
	/* Eorror while rating then move file to error directory and remove the file from success directory */
		*m_ABL_ServicePtr<<INFO<<"Stop signal Create in the path :: : "<<ms_Stopsignalfile.c_str() <<Endl;			
			ABL_String l_command("echo .> ");
			l_command +=ms_Stopsignalfile.c_str();			
			system(l_command.c_str());			
		*m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;		
	    return false;
	}		
	 return true;
}

bool  PM_Summary::mb_stop()
{
	
	
	return true;
}




