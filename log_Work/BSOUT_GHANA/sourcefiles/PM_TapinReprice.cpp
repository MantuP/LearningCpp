#include "PM_TapinReprice.h"
#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "PM_Job.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include <iostream>
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

#include <stdio.h>



extern "C" EXPORT
{
	Base_Registry* gb_getPM_TapinReprice()
	{
		return ( (Base_Registry*) new PM_TapinReprice);
	}
}

PM_TapinReprice::PM_TapinReprice()
{
//
}

PM_TapinReprice::~PM_TapinReprice()
{
//
}

PM_TapinReprice::PM_TapinReprice(const PM_TapinReprice& p_copyObject)
{
	this->m_ABL_ServicePtr      =       p_copyObject.m_ABL_ServicePtr ;
	this->Lockfilepath          =       p_copyObject.Lockfilepath     ;
	this->Stopsignalpath        =       p_copyObject.Stopsignalpath   ;
}

Base_Registry* PM_TapinReprice::mb_clone()
{
	return ( (Base_Registry*) new PM_TapinReprice);
}

ABL_Process* PM_TapinReprice::mb_createCopy()
{
	return ( new PM_TapinReprice(*this));
}

bool PM_TapinReprice::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{
	m_ABL_ServicePtr = p_ABL_ServicePtr;
	try
	{
		p_ABL_AgentCommunicatorPtr->mb_getParameter("LockFile",Lockfilepath);
		p_ABL_AgentCommunicatorPtr->mb_getParameter("STOP_FILE",Stopsignalpath);

	}
	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
	}
	return true;
}

bool PM_TapinReprice::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	return true;
}

bool PM_TapinReprice::mb_process(ABL_Job* &p_ABL_JobPtr)
{
	ABL_Connection  *l_ABL_ConnectionPtr  ;
	ABL_Statement   l_ABL_Statement       ;
	ABL_ResultSet   l_ABL_ResultSet       ;
	ABL_String      l_sql                 ;
	char            l_CreateStopSignal[500] ;

	PM_Job* l_PM_Job_Ptr = (PM_Job*)p_ABL_JobPtr;

	try
	{
		l_ABL_ConnectionPtr = ((PM_Job*)p_ABL_JobPtr)->mb_getConnection();
		InitialisePartnerDetails();

		l_FileTranDir             =  l_PM_Job_Ptr->m_FileTranDir      ;
		l_HplmnCode               =  l_PM_Job_Ptr->m_HplmnCode        ;
		l_VplmnCode               =  l_PM_Job_Ptr->m_VplmnCode        ;
		l_FileTypeInd             =  l_PM_Job_Ptr->m_FileTypeInd      ;
		l_FileSeqNum              =  l_PM_Job_Ptr->m_FileSeqNum       ;
		l_SettCallEvents          =  l_PM_Job_Ptr->m_SettCallEvents   ;
		l_FileName                =  l_PM_Job_Ptr->m_FileName         ;
		l_Surchperc               =  l_PM_Job_Ptr->m_Surchperc        ;
		l_PartnerCode             =  l_PM_Job_Ptr->m_PartnerCode      ;
		l_PartnerDesc             =  l_PM_Job_Ptr->m_PartnerDesc      ;
		l_DialingCode             =  l_PM_Job_Ptr->m_DialingCode      ;
		l_Repriceflag             =  l_PM_Job_Ptr->m_Repriceflag      ;
		l_RateIDDFlag             =  l_PM_Job_Ptr->m_RateIDDFlag      ;
		l_CamelFilterFlag         =  l_PM_Job_Ptr->m_CamelFilterFlag  ;
		l_PM_Job_Ptr->m_RepriceAgent = "Y"                            ;


		/**************************************************************************/
		/* Call the TAPIN Reprice Procedure */

		if(strcmp(l_Repriceflag.c_str(),"Y") == 0)
		{
			*m_ABL_ServicePtr<< INFO <<l_FileName<<" :: Reprice the File"<<Endl;

			l_sql = "BEGIN Pr_Tapin_Reprice(:1, :2, :3, :4, :5, :6); END;";
			l_ABL_Statement  = l_ABL_ConnectionPtr->mb_createStatement(l_sql);
			l_ABL_Statement.mb_setString(1,l_PartnerCode)          ;
			l_ABL_Statement.mb_setInt64(2,l_FileSeqNum)            ;
			l_ABL_Statement.mb_setString(3,l_FileTypeInd)          ;
			l_ABL_Statement.mb_registerOutParam(4,_INT,sizeof(int));
			l_ABL_Statement.mb_registerOutParam(5,_STRING,51)     ;
			l_ABL_Statement.mb_registerOutParam(6,_STRING,201)    ;
			l_ABL_Statement.mb_executeQuery();
			op_ExecStatus=l_ABL_Statement.mb_getInt(4);
			op_ErrCode=l_ABL_Statement.mb_getString(5);
			op_ErrMesg=l_ABL_Statement.mb_getString(6);
			l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);

			if(op_ExecStatus == 0)
			{
				*m_ABL_ServicePtr<<INFO<<l_FileName<<" :: Procedure return status is =>" <<op_ExecStatus<<",Error Code =>"<<op_ErrCode <<Endl;
				*m_ABL_ServicePtr<<INFO<<l_FileName<<" :: File is Successfully Repriced "<<Endl;
			}
			else
			{
				*m_ABL_ServicePtr<<CRITICAL<<l_FileName<<" :: Procedure return status is =>" <<op_ExecStatus<<", Error Code =>"<<op_ErrCode <<Endl;
				*m_ABL_ServicePtr<<CRITICAL<<l_FileName<<" :: "<<op_ErrMesg<<Endl;
				l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);

				l_sql   =  "UPDATE PM_TAP_FILE_SUMRY SET SENT_TO_BS = 'F',SENT_DATE = SYSDATE WHERE(FILE_NAME=:1)";

				l_ABL_Statement  =    l_ABL_ConnectionPtr->mb_createStatement(l_sql);
				l_ABL_Statement.mb_setString (1,l_FileName);
				l_ABL_Statement.mb_executeUpdate();
				l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
				l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);
				l_ABL_ConnectionPtr->mb_commit();
				*m_ABL_ServicePtr<<CRITICAL<<l_FileName<<" :: Updated File status to Failure"<<Endl;
				*m_ABL_ServicePtr << INFO << "-------------------------------------------------------------------" <<Endl;

				return false;
			}
		}
		else
		{
			*m_ABL_ServicePtr<<INFO<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<" :: Not Reprice the File "<<Endl;
		}
	} 
	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr<<CRITICAL<<"PM_TapinReprice::Exception : "<<e.mb_getMessage()<<Endl;
		*m_ABL_ServicePtr<<INFO<<"Errorin Repricing:Updated Sent to BS Status as Failure :: "<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<Endl;
		l_ABL_ConnectionPtr->mb_rollback();
		l_sql   =       "UPDATE PM_TAP_FILE_SUMRY SET SENT_TO_BS = 'F',SENT_DATE = SYSDATE WHERE(FILE_NAME=:1)";
		l_ABL_Statement         =       l_ABL_ConnectionPtr->mb_createStatement(l_sql);
		l_ABL_Statement.mb_setString (1,((PM_Job*)p_ABL_JobPtr)->m_fileName);
		l_ABL_Statement.mb_executeUpdate();
		l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
		l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);
		l_ABL_ConnectionPtr->mb_commit();
		return false;
	}
	return true;
}

bool PM_TapinReprice::mb_stop()
{
	/* std::cout << "PM_TapinReprice111 Stopped " << std::endl; */
	return true;
}

void PM_TapinReprice::InitialisePartnerDetails()
{
	l_FileTranDir             =  "" ;
	l_HplmnCode               =  "" ;
	l_VplmnCode               =  "" ;
	l_FileTypeInd             =  "" ;
	l_FileSeqNum              =  0  ;
	l_SettCallEvents          =  0  ;
	l_FileName                =  "" ;
	l_Surchperc               =  0  ;
	l_PartnerCode             =  "" ;
	l_PartnerDesc             =  "" ;
	l_DialingCode             =  "" ;
	l_Repriceflag             =  "" ;
	l_RateIDDFlag             =  "" ;
	l_CamelFilterFlag         =  "" ;
}
