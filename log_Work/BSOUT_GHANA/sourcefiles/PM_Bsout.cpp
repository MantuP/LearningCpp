#include<ABL_Service.h>
#include<ABL_String.h>
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "ABL_Date.h"
#include "ABL_Framework.h"
#include "ABL_Exception.h"

#include <signal.h>

ABL_Service l_ABL_Service;
ABL_String l_configFileName;

ABL_String p_applicationName;
void gb_signalHandler(int p_isignal);
void UpdateProcess(int ProcessId,ABL_String Status);
long   gUnixPid;
char gErrorMessage[200] ;
int    gSignalProcessId = 7 ;
ABL_String gProcessStartDate ;

int main(int p_argc, char *argv[])
{
	// Assign the function pointers for handling signals
	if(signal(SIGABRT, gb_signalHandler) == SIG_ERR);
	if(signal(SIGTSTP,      gb_signalHandler) == SIG_ERR);
	if(signal(SIGINT,       gb_signalHandler) == SIG_ERR);
	if(signal(SIGSEGV,      gb_signalHandler) == SIG_ERR);
	if(signal(SIGTERM,      gb_signalHandler) == SIG_ERR);
	if(signal(SIGBUS,       gb_signalHandler) == SIG_ERR);
	if(signal(SIGSYS,       gb_signalHandler) == SIG_ERR);
	if(signal(SIGQUIT,      gb_signalHandler) == SIG_ERR);

	try
	{
		p_applicationName="";
		p_applicationName=argv[0];
		l_configFileName="../conf/";
		l_configFileName += p_applicationName;
		l_configFileName += ".conf";

		if(!l_ABL_Service.mb_initServices(l_configFileName))
		{
			throw ABL_Exception(1,"Error in loading configuration file");
		}

		/* UpdateProcess("I", "Start."); */
		UpdateProcess(gSignalProcessId,"R");
		ABL_Framework(p_argc, argv);
		sprintf(gErrorMessage,"%s","Normal Exit.");
		UpdateProcess(gSignalProcessId,"S");
	}
	catch(ABL_Exception &e)
	{
		std::cout<<"control came here 1: "<<std::endl;
		std::cerr<< "ABL Exception Generated "<<e.mb_getErrorCode()<<":"<<e.mb_getMessage().c_str()<<std::endl;
	}
	catch(std::exception &ex)
	{
		std::cout<<"control came here 2: "<<std::endl;
		std::cerr<< "Std Exception Generated "<<ex.what()<<std::endl;
	}
	catch(...)
	{
		std::cout<<"control came here 4: "<<std::endl;
		std::cerr<< "Unknown Exception Generated "<<std::endl;
	}
	return 0;
}

void gb_signalHandler(int p_isignal)
{
	printf("gb_signalHandler\n") ;
	switch(p_isignal)
	{
		case SIGABRT:
		{
			sprintf(gErrorMessage,"%s","SIGABRT:Abort Signal Generated.");
			UpdateProcess(gSignalProcessId,"S");
			std::cerr<< " Abort Signal Generated. " << std::endl; exit(1);
		}
		case SIGINT:
		{
			sprintf(gErrorMessage,"%s","SIGINT:Terminal interrupt signal.");
			UpdateProcess(gSignalProcessId,"S");
			std::cerr<< " Terminal interrupt signal. " << std::endl; exit(1);
		}
		case SIGQUIT:
		{
			sprintf(gErrorMessage,"%s","SIGQUIT:Terminal quit signal encountered.");
			UpdateProcess(gSignalProcessId,"S");
			std::cerr<< " Terminal quit signal encountered. " << std::endl; exit(1);
		}
		case SIGSEGV:
		{
			sprintf(gErrorMessage,"%s","SIGSEGV:Segmentation Fault encountered. Invalid memory referenced.");
			UpdateProcess(gSignalProcessId,"S");
			std::cerr<< " Segmentation Fault encountered. Invalid memory referenced. " << std::endl; exit(1);
		}
		case SIGTERM:
		{
			sprintf(gErrorMessage,"%s","SIGTERM:Termination signal encountered. Exiting from the process.");
			UpdateProcess(gSignalProcessId,"S");
			std::cerr<< " Termination signal encountered. Exiting from the process. " << std::endl; exit(1);
		}
		case SIGTSTP:
		{
			sprintf(gErrorMessage,"%s","SIGTSTP:Terminal stop signal.");
			UpdateProcess(gSignalProcessId,"S");
			std::cerr<< " Terminal stop signal. "<< std::endl; exit(1);
		}
		case SIGBUS:
		{
			sprintf(gErrorMessage,"%s","SIGBUS:Bus error encountered. Process will be stopped.");
			UpdateProcess(gSignalProcessId,"S");
			std::cerr<<"Bus error encountered. Process will be stopped. "<< std::endl; exit(1);
		}
		case SIGSYS:
		{
			sprintf(gErrorMessage,"%s","SIGSYS:Bad system call. Process will be stopped.");
			UpdateProcess(gSignalProcessId,"S");
			std::cerr<<"Bad system call. Process will be stopped."<< std::endl; exit(1);
		}
	}
}

void UpdateProcess(int ProcessId,ABL_String Status)
{
	/* ABL_Service l_ABL_Service; */
	ABL_Connection  lo_ABLConnectionPtr;
	ABL_Statement   lo_ABLStatement;
	ABL_ResultSet   lo_ABLResultSet;
	ABL_String              l_sql;

	try
	{
		/* int ProcessId= l_ABL_Service.mb_getInt("PROCESS_ID"); */
		int ProcessId= gSignalProcessId;
		lo_ABLConnectionPtr.mb_createConnection(l_ABL_Service);
		//ABL_String      l_dbId = l_ABL_Service.mb_getParameterValue("WBS_DB_ID");
		//lo_ABLConnectionPtr.mb_createConnection(l_ABL_Service,false,false,l_dbId);

		if (strcmp(Status.c_str(),"R") == 0)
		{
			gProcessStartDate = "" ;

			l_sql="SELECT TO_CHAR(CURRENT_DATE,'YYYYMMDDHH24MISS') FROM DUAL" ;

			lo_ABLStatement   =   lo_ABLConnectionPtr.mb_createStatement(l_sql) ;
			lo_ABLResultSet  =lo_ABLStatement.mb_executeQuery()          ;
			/* lo_ABLStatement   =   lo_ABLStatement.mb_executeQuery()          ;*/
			lo_ABLResultSet.mb_fetch();

			gProcessStartDate =   lo_ABLResultSet.mb_getString(1) ;

			lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet)       ;
			lo_ABLConnectionPtr.mb_terminateStatement(lo_ABLStatement);


			l_sql  ="UPDATE PM_PROCESSES SET START_STOP_FLG = 'I',PROCESS_STATUS = :1, PROCESS_LAST_START_DATE= CURRENT_DATE WHERE(PROCESS_ID=:2)";
			lo_ABLStatement =       lo_ABLConnectionPtr.mb_createStatement(l_sql);
			lo_ABLStatement.mb_setString (1,Status);
			lo_ABLStatement.mb_setInt(2,ProcessId);
			lo_ABLStatement.mb_executeUpdate();
			lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
			lo_ABLConnectionPtr.mb_terminateStatement(lo_ABLStatement);
			lo_ABLConnectionPtr.mb_commit();
			l_sql  ="INSERT INTO PM_PROCESS_STATUS (PROCESS_ID, UNIX_PID, START_TIME) VALUES (:1,:2,CURRENT_DATE)";
			lo_ABLStatement =       lo_ABLConnectionPtr.mb_createStatement(l_sql);
			lo_ABLStatement.mb_setInt(1,ProcessId);
			lo_ABLStatement.mb_setInt(2,getpid());
			lo_ABLStatement.mb_executeUpdate();
			lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
			lo_ABLConnectionPtr.mb_terminateStatement(lo_ABLStatement);
			lo_ABLConnectionPtr.mb_commit();
		}
		else if (strcmp(Status.c_str(),"S") == 0)
		{
			l_sql ="UPDATE PM_PROCESSES SET START_STOP_FLG = 'I',PROCESS_STATUS = :1, PROCESS_LAST_STOP_DATE= CURRENT_DATE WHERE(PROCESS_ID=:2)";
			lo_ABLStatement =       lo_ABLConnectionPtr.mb_createStatement(l_sql);
			lo_ABLStatement.mb_setString (1,Status);
			lo_ABLStatement.mb_setInt(2,ProcessId);
			lo_ABLStatement.mb_executeUpdate();
			lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
			lo_ABLConnectionPtr.mb_terminateStatement(lo_ABLStatement);
			lo_ABLConnectionPtr.mb_commit();

			l_sql  ="UPDATE PM_PROCESS_STATUS SET STOP_TIME = CURRENT_DATE,ELAPSED_TIME = (CURRENT_DATE - TO_DATE(:1,'YYYYMMDDHH24MISS'))*60*60*24, REMARKS      = :2 WHERE (PROCESS_ID=:3 AND UNIX_PID = :4 AND START_TIME = TO_DATE(:5,'YYYYMMDDHH24MISS'))"; 
			lo_ABLStatement =       lo_ABLConnectionPtr.mb_createStatement(l_sql);
			lo_ABLStatement.mb_setString(1,gProcessStartDate);
			lo_ABLStatement.mb_setString (2,gErrorMessage);
			lo_ABLStatement.mb_setInt(3,ProcessId);
			lo_ABLStatement.mb_setInt(4,getpid());
			lo_ABLStatement.mb_setString(5,gProcessStartDate); 
			lo_ABLStatement.mb_executeUpdate();
			lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
			lo_ABLConnectionPtr.mb_terminateStatement(lo_ABLStatement);
			lo_ABLConnectionPtr.mb_commit();
		}
	}
	catch(ABL_Exception &e)
	{
		std::cerr<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		std::cerr<<"UpdateProcess: Error Updating PM_PROCESSES"<<Endl;
	}

	catch(...)
	{
		std::cerr<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
	}
}

