#include "PM_TapinFiles.h"
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

extern "C" EXPORT
{
	Base_Registry* gb_getPM_TapinFiles()
	{
		return ( (Base_Registry*) new PM_TapinFiles);
	}
}

PM_TapinFiles::PM_TapinFiles()
{
//
}

PM_TapinFiles::~PM_TapinFiles()
{
//
}

PM_TapinFiles::PM_TapinFiles(const PM_TapinFiles& p_copyObject)
{
	this->m_ABL_ServicePtr  =       p_copyObject.m_ABL_ServicePtr ;
	this->DataFilesDir      =       p_copyObject.DataFilesDir     ;
	this->SuccessFilesDir   =       p_copyObject.SuccessFilesDir  ;
	this->TouchFileFlag     =       p_copyObject.TouchFileFlag    ;
	this->Lockfilepath      =       p_copyObject.Lockfilepath     ;
	this->Stopsignalpath    =       p_copyObject.Stopsignalpath   ;
}

Base_Registry* PM_TapinFiles::mb_clone()
{
	return ( (Base_Registry*) new PM_TapinFiles);
}

ABL_Process* PM_TapinFiles::mb_createCopy()
{
	return ( new PM_TapinFiles(*this));
}

bool PM_TapinFiles::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{
	m_ABL_ServicePtr = p_ABL_ServicePtr;

	try
	{
		p_ABL_AgentCommunicatorPtr->mb_getParameter("DataFilesDir",DataFilesDir);
		p_ABL_AgentCommunicatorPtr->mb_getParameter("SuccessFilesDir",SuccessFilesDir) ;
		p_ABL_AgentCommunicatorPtr->mb_getParameter("TouchFileFlag",TouchFileFlag);
		p_ABL_AgentCommunicatorPtr->mb_getParameter("LockFile",Lockfilepath);
		p_ABL_AgentCommunicatorPtr->mb_getParameter("STOP_FILE",Stopsignalpath);
	}
	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
	}
	return true;
}


bool PM_TapinFiles::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	return true;
}


bool PM_TapinFiles::mb_process(ABL_Job* &p_ABL_JobPtr)
{

	ABL_Connection  *l_ABL_ConnectionPtr ;
	ABL_Statement   l_ABL_Statement      ;
	ABL_ResultSet   l_ABL_ResultSet      ;
	ABL_String      l_sql                ;
	long            l_totalCdrCount      ;

	PM_Job* l_PM_Job_Ptr = (PM_Job*)p_ABL_JobPtr;

	try
	{
		*m_ABL_ServicePtr << INFO << "-------------------------------------------------------------------" <<Endl;
		*m_ABL_ServicePtr<<INFO<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<" :: Started processing file"<<Endl;

		InitialisePartnerDetails() ;
		l_ABL_ConnectionPtr = ((PM_Job*)p_ABL_JobPtr)->mb_getConnection();


		l_sql ="SELECT NVL(B.FILE_TRANSFER_DIRECTION,' '), NVL(B.HPLMN_CODE,' '), NVL(B.VPLMN_CODE,' '), NVL(B.FILE_TYPE_INDICATOR,' '), NVL(B.FILE_SEQUENCE_NUMBER,'0'), NVL(B.SETTLEMENT_CALL_EVENTS,'0'), NVL(B.FILE_NAME,' '), B.SURCHARGE_PERCENTAGE, NVL(C.PARTNER_CODE,' '), NVL(C.PARTNER_NAME,' '), NVL(A.MOBL_PRFX_V,'0'), NVL(A.REPRICE, 'N'), NVL(A.RATE_IDD,'N'), NVL(A.CAMEL_FILTER_FLAG, 'N') FROM PM_ROAM_PARTNER_ADDN_INFO A, PM_TAP_FILE_SUMRY B, PM_PARTNER C WHERE B.FILE_TRANSFER_DIRECTION  = 'I' AND B.SENT_TO_BS = 'I' AND B.DATA_TYPE_INDICATOR = 'D' AND A.PARTNER_CODE = B.PARTNER_CODE AND A.PARTNER_CODE = C.PARTNER_CODE AND B.FILE_NAME = :1";

		l_ABL_Statement               =   l_ABL_ConnectionPtr->mb_createStatement(l_sql) ;
		l_ABL_Statement.mb_setString (1,((PM_Job*)p_ABL_JobPtr)->m_fileName);
		l_ABL_ResultSet               =   l_ABL_Statement.mb_executeQuery()          ;
		l_ABL_ResultSet.mb_fetch();

		stPartFileInfo.FileTranDir      =  l_ABL_ResultSet.mb_getString(1) ;
		stPartFileInfo.HplmnCode        =  l_ABL_ResultSet.mb_getString(2) ;
		stPartFileInfo.VplmnCode        =  l_ABL_ResultSet.mb_getString(3) ;
		stPartFileInfo.FileTypeInd      =  l_ABL_ResultSet.mb_getString(4) ;
		stPartFileInfo.FileSeqNum       =  l_ABL_ResultSet.mb_getInt64(5)  ;
		stPartFileInfo.SettCallEvents   =  l_ABL_ResultSet.mb_getInt64(6)  ;
		stPartFileInfo.FileName         =  l_ABL_ResultSet.mb_getString(7) ;
		stPartFileInfo.Surchperc        =  l_ABL_ResultSet.mb_getFloat(8)  ;
		stPartFileInfo.PartnerCode      =  l_ABL_ResultSet.mb_getString(9) ;
		stPartFileInfo.PartnerDesc      =  l_ABL_ResultSet.mb_getString(10);
		stPartFileInfo.DialingCode      =  l_ABL_ResultSet.mb_getString(11);
		stPartFileInfo.Repriceflag      =  l_ABL_ResultSet.mb_getString(12);
		stPartFileInfo.RateIDDFlag      =  l_ABL_ResultSet.mb_getString(13);
		stPartFileInfo.CamelFilterFlag  =  l_ABL_ResultSet.mb_getString(14);

		l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
		l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);

		l_PM_Job_Ptr->m_FileTranDir    =  stPartFileInfo.FileTranDir    ;
		l_PM_Job_Ptr->m_HplmnCode      =  stPartFileInfo.HplmnCode      ;
		l_PM_Job_Ptr->m_VplmnCode      =  stPartFileInfo.VplmnCode      ;
		l_PM_Job_Ptr->m_FileTypeInd    =  stPartFileInfo.FileTypeInd    ;
		l_PM_Job_Ptr->m_FileSeqNum     =  stPartFileInfo.FileSeqNum     ;
		l_PM_Job_Ptr->m_SettCallEvents =  stPartFileInfo.SettCallEvents ;
		l_PM_Job_Ptr->m_FileName       =  stPartFileInfo.FileName       ;
		l_PM_Job_Ptr->m_Surchperc      =  stPartFileInfo.Surchperc      ;
		l_PM_Job_Ptr->m_PartnerCode    =  stPartFileInfo.PartnerCode    ;
		l_PM_Job_Ptr->m_PartnerDesc    =  stPartFileInfo.PartnerDesc    ;
		l_PM_Job_Ptr->m_DialingCode    =  stPartFileInfo.DialingCode    ;
		l_PM_Job_Ptr->m_Repriceflag    =  stPartFileInfo.Repriceflag    ;
		l_PM_Job_Ptr->m_RateIDDFlag    =  stPartFileInfo.RateIDDFlag    ;
		l_PM_Job_Ptr->m_CamelFilterFlag=  stPartFileInfo.CamelFilterFlag;
		l_PM_Job_Ptr->m_RepriceAgent   =  "N"    ;
		*m_ABL_ServicePtr<<INFO<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<" :: Partner Code  :: "<<stPartFileInfo.PartnerCode<<Endl;

		l_totalCdrCount = 0;
		l_sql="SELECT COUNT (*) FROM PM_TAP_CDRS WHERE FILE_TRANSFER_DIRECTION = :1 AND HPLMN_CODE = :2 AND VPLMN_CODE = :3 AND FILE_TYPE_INDICATOR = :4 AND FILE_SEQUENCE_NUMBER = :5 AND PARTNER_CODE = :6 AND CALL_TYPE IN(1,2,3,4) ";
		l_ABL_Statement               =   l_ABL_ConnectionPtr->mb_createStatement(l_sql) ;
		l_ABL_Statement.mb_setString (1,stPartFileInfo.FileTranDir);
		l_ABL_Statement.mb_setString (2,stPartFileInfo.HplmnCode);
		l_ABL_Statement.mb_setString (3,stPartFileInfo.VplmnCode);
		l_ABL_Statement.mb_setString (4,stPartFileInfo.FileTypeInd);
		l_ABL_Statement.mb_setInt    (5,stPartFileInfo.FileSeqNum);
		l_ABL_Statement.mb_setString (6,stPartFileInfo.PartnerCode);
		l_ABL_ResultSet               =   l_ABL_Statement.mb_executeQuery()          ;
		l_ABL_ResultSet.mb_fetch() ;
		l_totalCdrCount               =       l_ABL_ResultSet.mb_getInt64(1);
		l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
		l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);

		if (l_totalCdrCount != stPartFileInfo.SettCallEvents)
		{
			*m_ABL_ServicePtr<<INFO<<"Cdrs number not matching in  PM_TAP_FILE_SUMRY and PM_TAP_CDRS"<<Endl;
			l_sql   =       "UPDATE PM_TAP_FILE_SUMRY SET SENT_TO_BS = 'F',SENT_DATE = SYSDATE WHERE(FILE_NAME=:1)";
			l_ABL_Statement  =    l_ABL_ConnectionPtr->mb_createStatement(l_sql);
			l_ABL_Statement.mb_setString (1,((PM_Job*)p_ABL_JobPtr)->m_fileName);
			l_ABL_Statement.mb_executeUpdate();
			l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
			l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);
			l_ABL_ConnectionPtr->mb_commit();
			return false ;
		}
		else if(stPartFileInfo.SettCallEvents == 0)
		{
			*m_ABL_ServicePtr<<INFO<<"Cdrs Count is Zero for Data File in PM_TAP_FILE_SUMRY"<<Endl;
			l_sql   =       "UPDATE PM_TAP_FILE_SUMRY SET SENT_TO_BS = 'F',SENT_DATE = SYSDATE WHERE(FILE_NAME=:1)";
			l_ABL_Statement  =    l_ABL_ConnectionPtr->mb_createStatement(l_sql);
			l_ABL_Statement.mb_setString (1,((PM_Job*)p_ABL_JobPtr)->m_fileName);
			l_ABL_Statement.mb_executeUpdate();
			l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
			l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);
			l_ABL_ConnectionPtr->mb_commit();
			return false ;
		}
		*m_ABL_ServicePtr<<INFO<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<" :: Total CDRs :: " << l_totalCdrCount<<Endl;
	} 
	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr<<CRITICAL<<"PM_TapinFiles::Exception : "<<e.mb_getMessage()<<Endl;
		*m_ABL_ServicePtr<<INFO<<"Updates Sent to BS Status as Failure fo the File :: "<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<Endl;
		l_sql   =       "UPDATE PM_TAP_FILE_SUMRY SET SENT_TO_BS = 'F',SENT_DATE = SYSDATE WHERE(FILE_NAME=:1)";
		l_ABL_Statement  =    l_ABL_ConnectionPtr->mb_createStatement(l_sql);
		l_ABL_Statement.mb_setString (1,((PM_Job*)p_ABL_JobPtr)->m_fileName);
		l_ABL_Statement.mb_executeUpdate();
		l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
		l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);
		l_ABL_ConnectionPtr->mb_commit();

		return false;
	}
	/* *m_ABL_ServicePtr<<INFO<<"Successfully Processed the File: "<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<Endl; */
	return true;
}

bool PM_TapinFiles::mb_stop()
{
	std::cout << "PM_TapinFiles Stopped " << std::endl;
	return true;
}

void PM_TapinFiles::InitialisePartnerDetails()
{
	stPartFileInfo.FileTranDir      =  "" ;
	stPartFileInfo.HplmnCode        =  "" ;
	stPartFileInfo.VplmnCode        =  "" ;
	stPartFileInfo.FileTypeInd      =  "" ;
	stPartFileInfo.FileSeqNum       =  0  ;
	stPartFileInfo.SettCallEvents   =  0  ;
	stPartFileInfo.FileName         =  "" ;
	stPartFileInfo.Surchperc        =  0.0;
	stPartFileInfo.PartnerCode      =  "" ;
	stPartFileInfo.PartnerDesc      =  "" ;
	stPartFileInfo.DialingCode      =  "" ;
	stPartFileInfo.Repriceflag      =  "" ;
	stPartFileInfo.RateIDDFlag      =  "" ;
	stPartFileInfo.CamelFilterFlag  =  "" ;
}
