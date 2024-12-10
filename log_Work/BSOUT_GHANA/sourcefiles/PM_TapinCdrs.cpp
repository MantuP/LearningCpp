/* Modified on 11-02-2010 by Yogesh to store Reprice Amount as "unsigned long" */
#include "PM_TapinCdrs.h"
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


#define CDR_FIELD_DELIMITER             '|'


extern "C" EXPORT
{
	Base_Registry* gb_getPM_TapinCdrs()
	{
		return ( (Base_Registry*) new PM_TapinCdrs);
	}
}

PM_TapinCdrs::PM_TapinCdrs()
{
//
}

PM_TapinCdrs::~PM_TapinCdrs()
{
//
}

PM_TapinCdrs::PM_TapinCdrs(const PM_TapinCdrs& p_copyObject)
{
	this->m_ABL_ServicePtr      =       p_copyObject.m_ABL_ServicePtr ;
	this->UTCOffset             =       p_copyObject.UTCOffset     ;
	this->DataFilesDir          =       p_copyObject.DataFilesDir     ;
	this->SuccessFilesDir       =       p_copyObject.SuccessFilesDir  ;
	this->TouchFileFlag         =       p_copyObject.TouchFileFlag    ;
	this->Lockfilepath          =       p_copyObject.Lockfilepath     ;
	this->Stopsignalpath        =       p_copyObject.Stopsignalpath   ;
	this->g_TapinCdrs           =       p_copyObject.g_TapinCdrs      ; 
}

Base_Registry* PM_TapinCdrs::mb_clone()
{
	return ( (Base_Registry*) new PM_TapinCdrs);
}

ABL_Process* PM_TapinCdrs::mb_createCopy()
{
	return ( new PM_TapinCdrs(*this));
}

bool PM_TapinCdrs::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{

	m_ABL_ServicePtr = p_ABL_ServicePtr;
	try
	{
		p_ABL_AgentCommunicatorPtr->mb_getParameter("UTCOffset",UTCOffset);
		p_ABL_AgentCommunicatorPtr->mb_getParameter("DataFilesDir",DataFilesDir);
		p_ABL_AgentCommunicatorPtr->mb_getParameter("SuccessFilesDir",SuccessFilesDir);
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

bool PM_TapinCdrs::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	return true;
}

bool PM_TapinCdrs::mb_process(ABL_Job* &p_ABL_JobPtr)
{
	ABL_Connection  *l_ABL_ConnectionPtr  ;
	ABL_Statement   l_ABL_Statement,l_ABL_Statement1       ;
	ABL_ResultSet   l_ABL_ResultSet,l_ABL_ResultSet1       ;
	ABL_String      l_sql,l_subsql        ;
	long            l_totalCdrCount   =0    ;
	long            l_prepaidCount   =0 ;
	char            l_toRatingCdr[217]    ; 
	char            l_toBillingGprs[303]  ;
	FILE            *l_dataFilePtr = NULL ;            /* BSOUT File Pointer */
	long            l_cdrError = 0        ;
	int             l_retValue = 0        ;
	char            l_CreateSuccessFile[500] ;
	char            l_RemoveDataFile[500] ;
	char            l_RemoveSuccessFile[500] ;
	unsigned long   l_RepriceAmount = 0   ;
	long            l_BsoutCdrCount   =0    ;
	long            i; 
	int             l_RepriceCDRCount = 0 ;

	PM_Job* l_PM_Job_Ptr = (PM_Job*)p_ABL_JobPtr;

	try
	{
		InitialisePartnerDetails() ;

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
		l_RepriceAgent            =  l_PM_Job_Ptr->m_RepriceAgent     ;


		/**********************************************************************/
		/* Get the CDRs Details for the BSOUT File - modified by lavanya to fetch cdrs with status "P" . On 25-apr-2013*/
		*m_ABL_ServicePtr<<INFO<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<" :: Fetching CDRs details from the File"<<Endl;
		l_ABL_ConnectionPtr = ((PM_Job*)p_ABL_JobPtr)->mb_getConnection();

		//l_sql ="SELECT NVL(FILE_TRANSFER_DIRECTION,' '), NVL(HPLMN_CODE,' '), NVL(VPLMN_CODE,' '), NVL(FILE_TYPE_INDICATOR,' '), NVL(FILE_SEQUENCE_NUMBER,'0'), NVL(CALL_TYPE,'0'), NVL(TO_CHAR (IMSI),' '), NVL(CALLED_CALLING_NUMBER,' '), NVL(TO_CHAR (CALL_DATE,'YYYYMMDD','NLS_CALENDAR=Gregorian'),' '), NVL(TO_CHAR (CALL_DATE,'HH24MISS','NLS_CALENDAR=Gregorian'),' '), NVL(CALL_DURATION,'0'), NVL(HOME_CURNCY_CHARGE_WITH_TAX,'0'), NVL(HOME_CURNCY_SURCHARGE,'0'), NVL(CALL_SEQUENCE,'0'), NVL(BASIC_SERVICE_TYPE,' '), NVL(BASIC_SERVICE_CODE,' '), NVL(DATA_VOLUME_INCOMING,'0'), NVL(DATA_VOLUME_OUTGOING,'0'), NVL(APN_NI,' '), NVL(PDP_ADDRESS,' '), Convert_Utc_to_Local(to_timestamp(to_char(call_date,'mm/dd/yyyy hh24:mi:ss','NLS_CALENDAR=Gregorian'),'mm/dd/yyyy hh24:mi:ss'),SUBSTR(utc_offset_code,1,3)||':'||SUBSTR(utc_offset_code,4,5),:1),NVL(CAMEL_USED_FLAG,0),NVL(TRIM(MSISDN),' ') FROM PM_TAP_CDRS WHERE FILE_TRANSFER_DIRECTION = :2 AND HPLMN_CODE = :3 AND VPLMN_CODE = :4 AND FILE_TYPE_INDICATOR = :5 AND FILE_SEQUENCE_NUMBER = :6 AND PARTNER_CODE = :7 AND CALL_TYPE IN (1,2,3,4) ORDER BY CALL_SEQUENCE"  ;
		l_sql ="SELECT NVL(FILE_TRANSFER_DIRECTION,' '), NVL(HPLMN_CODE,' '), NVL(VPLMN_CODE,' '), NVL(FILE_TYPE_INDICATOR,' '), NVL(FILE_SEQUENCE_NUMBER,'0'), NVL(CALL_TYPE,'0'), NVL(TO_CHAR (IMSI),' '), NVL(CALLED_CALLING_NUMBER,' '), NVL(TO_CHAR (CALL_DATE,'YYYYMMDD','NLS_CALENDAR=Gregorian'),' '), NVL(TO_CHAR (CALL_DATE,'HH24MISS','NLS_CALENDAR=Gregorian'),' '), NVL(CALL_DURATION,'0'), NVL(HOME_CURNCY_CHARGE_WITH_TAX,'0'), NVL(HOME_CURNCY_SURCHARGE,'0'), NVL(CALL_SEQUENCE,'0'), NVL(BASIC_SERVICE_TYPE,' '), NVL(BASIC_SERVICE_CODE,' '), to_char(NVL(DATA_VOLUME_INCOMING,0)), to_char(NVL(DATA_VOLUME_OUTGOING,0)), NVL(APN_NI,' '), NVL(PDP_ADDRESS,' '), Convert_Utc_to_Local(to_timestamp(to_char(call_date,'mm/dd/yyyy hh24:mi:ss','NLS_CALENDAR=Gregorian'),'mm/dd/yyyy hh24:mi:ss'),SUBSTR(utc_offset_code,1,3)||':'||SUBSTR(utc_offset_code,4,5),:1),NVL(CAMEL_USED_FLAG,0),NVL(TRIM(MSISDN),' '),NVL(SERVICE_CODE,' '),SENT_TO_BS  FROM PM_TAP_CDRS WHERE FILE_TRANSFER_DIRECTION = :2 AND HPLMN_CODE = :3 AND VPLMN_CODE = :4 AND FILE_TYPE_INDICATOR = :5 AND FILE_SEQUENCE_NUMBER = :6 AND PARTNER_CODE = :7 AND CALL_TYPE IN (1,2,3,4) AND SENT_TO_BS ='P' ORDER BY CALL_SEQUENCE";
		l_ABL_Statement               =   l_ABL_ConnectionPtr->mb_createStatement(l_sql) ;


		l_ABL_Statement.mb_setString (1,UTCOffset);
		l_ABL_Statement.mb_setString (2,l_FileTranDir);
		l_ABL_Statement.mb_setString (3,l_HplmnCode);
		l_ABL_Statement.mb_setString (4,l_VplmnCode);
		l_ABL_Statement.mb_setString (5,l_FileTypeInd);
		l_ABL_Statement.mb_setInt    (6,l_FileSeqNum);
		l_ABL_Statement.mb_setString (7,l_PartnerCode);

		l_ABL_ResultSet               =   l_ABL_Statement.mb_executeQuery()          ;

		while(l_ABL_ResultSet.mb_fetch())
		{
			InitialiseCdrsParameters();
			g_TapinCdrs.gFileTranDir        =   l_ABL_ResultSet.mb_getString(1)  ;
			g_TapinCdrs.gHplmnCode          =   l_ABL_ResultSet.mb_getString(2)  ;
			g_TapinCdrs.gVplmnCode          =   l_ABL_ResultSet.mb_getString(3)  ;
			g_TapinCdrs.gFileTypeInd        =   l_ABL_ResultSet.mb_getString(4)  ;
			g_TapinCdrs.gFileSeqNum         =   l_ABL_ResultSet.mb_getInt64(5)   ;
			g_TapinCdrs.gCallType           =   l_ABL_ResultSet.mb_getInt64(6)   ;
			g_TapinCdrs.gImsiNum            =   l_ABL_ResultSet.mb_getString(7)  ;
			g_TapinCdrs.gCalledCallingNum   =   l_ABL_ResultSet.mb_getString(8)  ;
			g_TapinCdrs.gCallDate           =   l_ABL_ResultSet.mb_getString(9)  ;
			g_TapinCdrs.gCallTime           =   l_ABL_ResultSet.mb_getString(10) ;
			g_TapinCdrs.gDuration           =   l_ABL_ResultSet.mb_getDouble(11)  ;
			g_TapinCdrs.gCallAmount         =   l_ABL_ResultSet.mb_getDouble(12)  ;
			g_TapinCdrs.gSurchargeAmount    =   l_ABL_ResultSet.mb_getDouble(13)  ;
			g_TapinCdrs.gCdrSeqNum          =   l_ABL_ResultSet.mb_getInt64(14)  ;
			g_TapinCdrs.gBasicServType      =   l_ABL_ResultSet.mb_getString(15) ;
			g_TapinCdrs.gBasicServCode      =   l_ABL_ResultSet.mb_getString(16) ;
			g_TapinCdrs.gDataVolumeIncoming =   l_ABL_ResultSet.mb_getString(17) ;
			g_TapinCdrs.gDataVolumeOutgoing =   l_ABL_ResultSet.mb_getString(18) ;
			g_TapinCdrs.gAccessPointNameNI  =   l_ABL_ResultSet.mb_getString(19) ;
			g_TapinCdrs.gPDPAddress         =   l_ABL_ResultSet.mb_getString(20) ;
			g_TapinCdrs.gLocalDateTime      =   l_ABL_ResultSet.mb_getString(21) ;
			g_TapinCdrs.gCamelUsedFlag	=   l_ABL_ResultSet.mb_getInt64(22)  ;
			g_TapinCdrs.gMsisdn	=   l_ABL_ResultSet.mb_getString(23) ;
			g_TapinCdrs.gServiceCode	=   l_ABL_ResultSet.mb_getString(24) ;
			g_TapinCdrs.gSentToBs	=   l_ABL_ResultSet.mb_getString(25) ;

			l_RepriceAmount = 0 ;

			l_CdrRepriceflag = l_Repriceflag ;
			g_TapinCdrs.gSentToBs	= "S";

			if((strcmp(l_Repriceflag.c_str(),"Y") == 0) && (strcmp(l_RepriceAgent.c_str(),"Y") == 0 ))
			{
				l_RepriceCDRCount = 0 ;
				l_subsql="SELECT NVL(REPRICE_AMT,0) FROM PM_TAPIN_REPRICE_CDRS  WHERE HPLMN_CODE = :1 AND VPLMN_CODE = :2 AND FILE_TYPE_INDICATOR =:3 AND FILE_SEQUENCE_NUMBER = :4 AND CALL_SEQUENCE = :5 AND PARTNER_CODE = :6";
				l_ABL_Statement1	=	l_ABL_ConnectionPtr->mb_createStatement(l_subsql) ;
				l_ABL_Statement1.mb_setString (1,g_TapinCdrs.gHplmnCode)   ;
				l_ABL_Statement1.mb_setString (2,g_TapinCdrs.gVplmnCode)   ;
				l_ABL_Statement1.mb_setString (3,g_TapinCdrs.gFileTypeInd) ;
				l_ABL_Statement1.mb_setInt    (4,g_TapinCdrs.gFileSeqNum)  ;
				l_ABL_Statement1.mb_setInt    (5,g_TapinCdrs.gCdrSeqNum)   ;
				l_ABL_Statement1.mb_setString  (6,l_PartnerCode)            ;
				l_ABL_ResultSet1	=	l_ABL_Statement1.mb_executeQuery();
				l_ABL_ResultSet1.mb_fetch() ;
				l_RepriceAmount	=	l_ABL_ResultSet1.mb_getInt64(1); 
				l_ABL_Statement1.mb_closeResultSet(l_ABL_ResultSet1);
				l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement1);
				g_TapinCdrs.gCallAmount = l_RepriceAmount;
				l_CdrRepriceflag = "N" ;
			}
			g_TapinCdrs.gCdrRepriceflag      =   l_CdrRepriceflag;
			l_totalCdrCount = l_totalCdrCount +1;
			l_PM_Job_Ptr->TAPCdrs.push_back(g_TapinCdrs);
		}
		l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
		l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);
		l_ABL_ConnectionPtr->mb_commit();
		l_PM_Job_Ptr->m_TotalCdrsMsisdn  = l_totalCdrCount;
		*m_ABL_ServicePtr<<INFO<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<" :: Completed Fetching the CDRs Details with number of cdrs : "<<l_totalCdrCount<<Endl;

	} 
	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr<<CRITICAL<<"PM_TapinCdrs::Exception : "<<e.mb_getMessage()<<Endl;
		*m_ABL_ServicePtr<<INFO<<"Updated Sent to BS Status as Failure fo the File :: "<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<Endl;
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

bool PM_TapinCdrs::mb_stop()
{
	/* std::cout << "PM_TapinCdrs111 Stopped " << std::endl; */
	return true;
}

void PM_TapinCdrs::replace_str(char *sou,char *sval,int st_ps,int no_ch,char pad_ch) 
{
	int   ln=0,i=0;
	char  *frmpos;

	for(ln=0;sval[ln];++ln); /* to get the length */

	if(ln>no_ch) ln=no_ch;/* max len to be copied */

	frmpos=sou+(st_ps-1); /* padd spaces */

	if(pad_ch)
		for(i=0;i<no_ch-ln;++i)
			*frmpos++= pad_ch;

	/* frmpos = sou+(st_ps-1)+(no_ch - ln); */
	for(i=0;i<ln;++i) *frmpos++ = *sval++;

	if (!pad_ch)
	{
		for(i=0;i<no_ch-ln;++i)
			*frmpos++= ' ';
	}
}

void PM_TapinCdrs::InitialisePartnerDetails()
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

void PM_TapinCdrs::InitialiseCdrsParameters()
{
	g_TapinCdrs.gFileTranDir        =   "" ;
	g_TapinCdrs.gHplmnCode          =   "" ;
	g_TapinCdrs.gVplmnCode          =   "" ;
	g_TapinCdrs.gFileTypeInd        =   "" ;
	g_TapinCdrs.gFileSeqNum         =   0  ;
	g_TapinCdrs.gCallType           =   0  ;
	g_TapinCdrs.gImsiNum            =   "" ;
	g_TapinCdrs.gCalledCallingNum   =   "" ;
	g_TapinCdrs.gCallDate           =   "" ;
	g_TapinCdrs.gCallTime           =   "" ;
	g_TapinCdrs.gDuration           =   0  ;
	g_TapinCdrs.gCallAmount         =   0  ;
	g_TapinCdrs.gSurchargeAmount    =   0  ;
	g_TapinCdrs.gCdrSeqNum          =   0  ;
	g_TapinCdrs.gBasicServType      =   "" ;
	g_TapinCdrs.gBasicServCode      =   "" ;
	g_TapinCdrs.gDataVolumeIncoming =   "" ;
	g_TapinCdrs.gDataVolumeOutgoing =   "" ;
	g_TapinCdrs.gAccessPointNameNI  =   "" ;
	g_TapinCdrs.gPDPAddress         =   "" ;
	g_TapinCdrs.gLocalDateTime      =   "" ;
	g_TapinCdrs.gCamelUsedFlag      =   0  ;
	g_TapinCdrs.gCdrRepriceflag     =   "" ;
	g_TapinCdrs.gMsisdn             =   "" ;
	g_TapinCdrs.gServiceCode        =   "" ;
	g_TapinCdrs.gSentToBs           =   "";
	l_CdrRepriceflag               =   "" ;
}
