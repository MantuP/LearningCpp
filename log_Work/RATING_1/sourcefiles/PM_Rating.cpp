#include<ABL_Service.h>
#include<ABL_String.h>
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "ABL_Date.h"
#include "ABL_Framework.h"
#include "ABL_Exception.h"
#include <signal.h>
ABL_String l_configFileName;
ABL_Service l_ABL_Service;
ABL_String p_applicationName;

void tokenize(const std::string& in_str,std::vector<std::string>& lv_tokens,const std::string& in_delimiters )
{
	std::stringstream l_stringStream(in_str);
	std::string ls_tokenString;
	while(std::getline(l_stringStream,ls_tokenString,in_delimiters[0]))
	{
		lv_tokens.push_back(ls_tokenString);
	}
}
void  UpdateProcess(ABL_String ps_TypeFlag ,ABL_String  ps_Remark)
{

	ABL_Connection	lo_ABLConnectionPtr;
	ABL_Statement	lo_ABLStatement;
	ABL_ResultSet	lo_ABLResultSet;
	ABL_String		ls_sql;   
   try
   {
	   

		int ProcessId= l_ABL_Service.mb_getInt("PROCESS_ID");
		lo_ABLConnectionPtr.mb_createConnection(l_ABL_Service);
  
		if(ps_TypeFlag=="U")
		{
			//update pm_process_status table.
			ls_sql = "update PM_PROCESS_STATUS set STOP_TIME=sysdate, ELAPSED_TIME=0, REMARKS=:1 where(PROCESS_ID=:2 and UNIX_PID=:3)"; 
			lo_ABLStatement = lo_ABLConnectionPtr.mb_createStatement(ls_sql); 
			lo_ABLStatement.mb_setString(1,ps_Remark);
			lo_ABLStatement.mb_setInt(2,ProcessId);
			lo_ABLStatement.mb_setInt(3,getpid());
	   }
	   else if(ps_TypeFlag=="I")
	   {
			ls_sql="INSERT INTO PM_PROCESS_STATUS (PROCESS_ID,UNIX_PID,START_TIME) values(:1,:2,sysdate)";
			lo_ABLStatement     =	lo_ABLConnectionPtr.mb_createStatement(ls_sql);	
			lo_ABLStatement.mb_setInt(1,ProcessId);
			lo_ABLStatement.mb_setInt(2,getpid());
	   }
	   else
	   {
			std::cout<<"Unknow type flag: "<<std::endl;
	   }

		lo_ABLStatement.mb_executeUpdate();
		lo_ABLConnectionPtr.mb_terminateStatement(lo_ABLStatement);
		lo_ABLConnectionPtr.mb_commit();
   }
   catch(ABL_Exception &e)
   {
		std::cerr<<"Exception Generated Outside:"<<e.mb_getErrorCode()<<":"<<e.mb_getMessage()<<std::endl;
   }
	catch(...)
	{
		std::cerr<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;

	}	
 }

void gb_signalHandler(int p_isignal)
{
	switch(p_isignal)
	{
		case SIGABRT:
		{
			UpdateProcess("U", "Abort Signal Generated.");
			std::cerr<< " Abort Signal Generated. " << std::endl; exit(1);
		}
		case SIGINT:
		{
			UpdateProcess("U", "Terminal interrupt signal.");
			std::cerr<< " Terminal interrupt signal. " << std::endl; exit(1);
		}

		case SIGQUIT:
		{
			UpdateProcess("U", " Terminal quit signal encountered.");
			std::cerr<< " Terminal quit signal encountered. " << std::endl; exit(1);
		}

		case SIGSEGV:
		{
			UpdateProcess("U", "Segmentation Fault encountered. Invalid memory referenced.");
			std::cerr<< " Segmentation Fault encountered. Invalid memory referenced. " << std::endl; exit(1);
		}

		case SIGTERM:
		{
			UpdateProcess("U", "Termination signal encountered. Exiting from the process.");
			std::cerr<< " Termination signal encountered. Exiting from the process. " << std::endl; exit(1);
		}

		case SIGTSTP:
		{
			UpdateProcess("U", "Terminal stop signal.");
			std::cerr<< " Terminal stop signal. "<< std::endl; exit(1);
		}
		case SIGBUS:
		{
			UpdateProcess("U", "Bus error encountered. Process will be stopped.");
			std::cerr<<"Bus error encountered. Process will be stopped. "<< std::endl; exit(1);
		}
		case SIGSYS:
		{
			UpdateProcess("U", "Bad system call. Process will be stopped.");
			std::cerr<<"Bad system call. Process will be stopped."<< std::endl; exit(1);
		}		
	}
}


int main(int p_argc, char *argv[])
{
	// Assign the function pointers for handling signals
	std::vector<std::string> lv_tokens;
	if(signal(SIGABRT, gb_signalHandler) == SIG_ERR);
	if(signal(SIGTSTP,	gb_signalHandler) == SIG_ERR);
	if(signal(SIGINT,	gb_signalHandler) == SIG_ERR);
	if(signal(SIGSEGV,	gb_signalHandler) == SIG_ERR);
	if(signal(SIGTERM,	gb_signalHandler) == SIG_ERR);
	if(signal(SIGBUS,	gb_signalHandler) == SIG_ERR); 
	if(signal(SIGSYS,	gb_signalHandler) == SIG_ERR);
	if(signal(SIGQUIT,	gb_signalHandler) == SIG_ERR);

	try
	{
		p_applicationName="";
		p_applicationName=argv[0];
		tokenize(p_applicationName.c_str(),lv_tokens,"/");
		//std::cout<<"Size of vector: "<<lv_tokens.size()<<": "<<argv[0]<<std::endl;
		if (lv_tokens.size()>2)
		{
			for(int i=0;i<lv_tokens.size()-1;i++)
			{
				l_configFileName+=lv_tokens[i];
				l_configFileName+="/";
	
			}

			l_configFileName+="../conf/";
			l_configFileName += lv_tokens[lv_tokens.size()-1];
			l_configFileName += ".conf";
	
		}
		else
		{
			l_configFileName="../conf/";
			l_configFileName+= p_applicationName;
			l_configFileName += ".conf";
		}
		//std::cout<<"Config file path: "<<l_configFileName<<std::endl;
		//std::cout<<"Before read: "<<std::endl;
		if(!l_ABL_Service.mb_initServices(l_configFileName))
		{
			throw ABL_Exception(1,"Error in loading configuration file");	
		}
		//		std::cout<<"After read: "<<std::endl;

		UpdateProcess("I", "Start.");
		//std::cout<<"Before load shared lib: "<<std::endl;
		//ABL_Framework(p_argc, argv);
		ABL_Framework(lv_tokens[lv_tokens.size()-1].c_str());
		//std::cout<<"After load shared lib: "<<std::endl;
		UpdateProcess("U", "Normallly stopped after detecting stop signal.");
	}
	catch(ABL_Exception &e)
	{
		std::cout<<"control came here 1: "<<std::endl;
		std::cerr<< "ABL Exception Generated "<<e.mb_getErrorCode()<<":"<<e.mb_getMessage().c_str()<<": "<<l_configFileName<<std::endl;
	}
	catch(std::exception &ex)
	{
		std::cout<<"control came here 2: "<<std::endl;
		std::cerr<< "Std Exception Generated "<<ex.what()<<": "<<l_configFileName<<std::endl;
	}
	catch(...)
	{
		std::cout<<"control came here 4: "<<": "<<l_configFileName<<std::endl;
		std::cerr<< "Unknown Exception Generated "<<": "<<l_configFileName<<std::endl;
	}

}



/*********************************************************************
#
#                 Copyright 2007 - 2008  
#                 Lifetree Convergence Ltd.
#
*********************************************************************/
