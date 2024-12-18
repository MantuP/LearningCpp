/* Modified on 11-02-2010 by Yogesh to store Reprice Amount as "unsigned long" */
#include "PM_GetMsisdn.h"
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
	Base_Registry* gb_getPM_GetMsisdn()
	{
		return ( (Base_Registry*) new PM_GetMsisdn);
	}
}

PM_GetMsisdn::PM_GetMsisdn()
{
//
}

PM_GetMsisdn::~PM_GetMsisdn()
{
//
}


PM_GetMsisdn::PM_GetMsisdn(const PM_GetMsisdn& p_copyObject)
{
	this->m_ABL_ServicePtr      =       p_copyObject.m_ABL_ServicePtr ;
	this->UTCOffset             =       p_copyObject.UTCOffset     ;
	this->DataFilesDir          =       p_copyObject.DataFilesDir     ;
	this->SuccessFilesDir       =       p_copyObject.SuccessFilesDir  ;
	this->TouchFileFlag         =       p_copyObject.TouchFileFlag    ;
	this->Lockfilepath          =       p_copyObject.Lockfilepath     ;
	this->Stopsignalpath        =       p_copyObject.Stopsignalpath   ;
	this->g_TapCdrs             =       p_copyObject.g_TapCdrs      ; 
}

Base_Registry* PM_GetMsisdn::mb_clone()
{
	return ( (Base_Registry*) new PM_GetMsisdn);
}

ABL_Process* PM_GetMsisdn::mb_createCopy()
{
	return ( new PM_GetMsisdn(*this));
}


bool PM_GetMsisdn::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
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

bool PM_GetMsisdn::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	return true;
}

bool PM_GetMsisdn::mb_process(ABL_Job* &p_ABL_JobPtr)
{
	ABL_Connection  *l_ABL_ConnectionPtr  ;
	ABL_Statement   l_ABL_Statement,l_ABL_Statement1       ;
	ABL_ResultSet   l_ABL_ResultSet,l_ABL_ResultSet1       ;
	ABL_String      l_sql,l_subsql        ;
	long            l_totalCdrCount   =0    ;
	long            l_prepaidCount   =0 ;
	FILE            *l_dataFilePtr = NULL ;            /* BSOUT File Pointer */
	long            l_cdrError = 0        ;
	int             l_retValue = 0        ;
	long            i; 
	long            l_AccountLinkCode;
	ABL_String      l_CallDateTime     ;
	ABL_String      l_FileName;
	ABL_String      l_CountryDiallingCode  ;
	int             l_CountryCodeLength = 0 ;
	char            l_MsisdnPrefix[6] ;
	char            l_TempMsisdnPrefix[6] ;
	char            l_TempCdrMsisdn[16] ;
	char            l_CdrMsisdn[16] ;
	l_FileName = "";
	long l_FileSeqNo = 0;   /* added by lavanya on 25-apr-2013 to update status (sent_to_bs) in pm_tap_cdrs table*/
	ABL_String      l_HplmnCode;
	ABL_String      l_VplmnCode;
	int  l_CdrSeq = 0;

	l_HplmnCode ="";
	l_VplmnCode ="";


	PM_Job* l_PM_Job_Ptr = (PM_Job*)p_ABL_JobPtr;

	try
	{
		*m_ABL_ServicePtr<<INFO<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<" :: Get MSISDN from @billity, if it is not in International Format"<<Endl;

		/**********************************************************************/
		/* Get the CDRs Details for the BSOUT File */

		l_ABL_ConnectionPtr = ((PM_Job*)p_ABL_JobPtr)->mb_getConnection();
		l_SettCallEvents=  0  ;

		// l_SettCallEvents=  ((PM_Job*)p_ABL_JobPtr)->m_SettCallEvents   ;
		l_SettCallEvents= l_PM_Job_Ptr->m_TotalCdrsMsisdn;


		/* Get Country Code for the Application Owner */
		l_sql="SELECT NVL(TRIM(COUNTRY_DIALLING_CODE),' '),LENGTH(TRIM(COUNTRY_DIALLING_CODE)) FROM PM_APP_PREFERENCE WHERE ROWNUM = 1";

		l_ABL_Statement   =   l_ABL_ConnectionPtr->mb_createStatement(l_sql) ;

		l_ABL_ResultSet   =   l_ABL_Statement.mb_executeQuery()          ;

		l_ABL_ResultSet.mb_fetch();

		l_CountryDiallingCode	=	l_ABL_ResultSet.mb_getString(1) ;
		l_CountryCodeLength	=	l_ABL_ResultSet.mb_getInt(2) ;

	


		l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet)       ;
		l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement)  ;


		for(i=0;i<l_SettCallEvents;i++ )
		{
			InitialiseTAPCdrsParameters();
			g_TapCdrs.gFileTranDir        =     l_PM_Job_Ptr->TAPCdrs[i].gFileTranDir       ;
			g_TapCdrs.gHplmnCode          =     l_PM_Job_Ptr->TAPCdrs[i].gHplmnCode         ;
			g_TapCdrs.gVplmnCode          =     l_PM_Job_Ptr->TAPCdrs[i].gVplmnCode         ;
			g_TapCdrs.gFileTypeInd        =     l_PM_Job_Ptr->TAPCdrs[i].gFileTypeInd       ;
			g_TapCdrs.gFileSeqNum         =     l_PM_Job_Ptr->TAPCdrs[i].gFileSeqNum        ;
			g_TapCdrs.gCallType           =     l_PM_Job_Ptr->TAPCdrs[i].gCallType          ;
			g_TapCdrs.gImsiNum            =     l_PM_Job_Ptr->TAPCdrs[i].gImsiNum           ;
			g_TapCdrs.gCalledCallingNum   =     l_PM_Job_Ptr->TAPCdrs[i].gCalledCallingNum  ;
			g_TapCdrs.gCallDate           =     l_PM_Job_Ptr->TAPCdrs[i].gCallDate          ;
			g_TapCdrs.gCallTime           =     l_PM_Job_Ptr->TAPCdrs[i].gCallTime          ;
			g_TapCdrs.gDuration           =     l_PM_Job_Ptr->TAPCdrs[i].gDuration          ;
			g_TapCdrs.gCallAmount         =     l_PM_Job_Ptr->TAPCdrs[i].gCallAmount        ;
			g_TapCdrs.gSurchargeAmount    =     l_PM_Job_Ptr->TAPCdrs[i].gSurchargeAmount   ;
			g_TapCdrs.gCdrSeqNum          =     l_PM_Job_Ptr->TAPCdrs[i].gCdrSeqNum         ;
			g_TapCdrs.gBasicServType      =     l_PM_Job_Ptr->TAPCdrs[i].gBasicServType     ;
			g_TapCdrs.gBasicServCode      =     l_PM_Job_Ptr->TAPCdrs[i].gBasicServCode     ;
			g_TapCdrs.gDataVolumeIncoming =     l_PM_Job_Ptr->TAPCdrs[i].gDataVolumeIncoming;
			g_TapCdrs.gDataVolumeOutgoing =     l_PM_Job_Ptr->TAPCdrs[i].gDataVolumeOutgoing;
			g_TapCdrs.gAccessPointNameNI  =     l_PM_Job_Ptr->TAPCdrs[i].gAccessPointNameNI ;
			g_TapCdrs.gPDPAddress         =     l_PM_Job_Ptr->TAPCdrs[i].gPDPAddress        ;
			g_TapCdrs.gLocalDateTime      =     l_PM_Job_Ptr->TAPCdrs[i].gLocalDateTime     ;
			g_TapCdrs.gCamelUsedFlag      =     l_PM_Job_Ptr->TAPCdrs[i].gCamelUsedFlag     ;
			g_TapCdrs.gCdrRepriceflag     =     l_PM_Job_Ptr->TAPCdrs[i].gCdrRepriceflag    ;
			g_TapCdrs.gMsisdn             =     l_PM_Job_Ptr->TAPCdrs[i].gMsisdn            ;
			g_TapCdrs.gSentToBs           =     l_PM_Job_Ptr->TAPCdrs[i].gSentToBs          ;

			sprintf(l_CdrMsisdn,"%s",g_TapCdrs.gMsisdn.c_str()) ;

			l_PM_Job_Ptr->TAPCdrs[i].gSentToBs = "P" ;

			sub_str(l_CdrMsisdn,l_MsisdnPrefix,1,l_CountryCodeLength) ;
	
			if ((g_TapCdrs.gMsisdn == " ") || (strcmp(l_MsisdnPrefix,l_CountryDiallingCode.c_str()) != 0))
			{
				//  g_TapCdrs.gMsisdn = " " ;
				l_CallDateTime = g_TapCdrs.gCallDate ;
				l_CallDateTime += g_TapCdrs.gCallTime ;
			
				l_subsql="SELECT nvl(TRIM(MOBL_NUM_VOICE_V),'') FROM GSM_SERVICE_MAST@ICB_ABL  WHERE IMSI_NUM_N = :1 AND IMSI_ACTIVE_DATE_D <= TO_DATE(:2,'YYYYMMDDHH24MISS')";

				l_ABL_Statement1	=	l_ABL_ConnectionPtr->mb_createStatement(l_subsql) ;
				l_ABL_Statement1.mb_setString (1,g_TapCdrs.gImsiNum)   ;
				l_ABL_Statement1.mb_setString (2,l_CallDateTime)   ;

			//	*m_ABL_ServicePtr<<INFO<<"Getting MSISDN Data For the each CDR : "<<Endl;
				l_ABL_ResultSet1	=	l_ABL_Statement1.mb_executeQuery()          ;
		

				while(l_ABL_ResultSet1.mb_fetch()) 
				{
					g_TapCdrs.gMsisdn	=	l_ABL_ResultSet1.mb_getString(1);
				
				}  
				
				l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement1);
			
				if (g_TapCdrs.gMsisdn == "" || g_TapCdrs.gMsisdn == " ")
				{
				
					l_AccountLinkCode =0;
					l_subsql="SELECT nvl(ACCOUNT_LINK_CODE_N ,0) FROM GSM_IMSI_HISTORY@ICB_ABL  WHERE OLD_IMSI_NUM_N  = :1 AND OLD_IMSI_ACTIVATION_DATE_DT  <=  TO_DATE(:2,'YYYYMMDDHH24MISS') AND ROWNUM = 1";

					l_ABL_Statement1               =   l_ABL_ConnectionPtr->mb_createStatement(l_subsql) ;
					l_ABL_Statement1.mb_setString (1,g_TapCdrs.gImsiNum)   ;
					l_ABL_Statement1.mb_setString (2,l_CallDateTime)   ;
			
					l_ABL_ResultSet1	=	l_ABL_Statement1.mb_executeQuery();
				
					while(l_ABL_ResultSet1.mb_fetch())
					{
						l_AccountLinkCode	=	l_ABL_ResultSet1.mb_getInt64(1);
					
					}

					l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement1);

					if(l_AccountLinkCode != 0)
					{
					
						l_subsql="SELECT nvl(MOBL_NUM_VOICE_V,'') FROM GSM_SERVICE_MAST@ICB_ABL  WHERE ACCOUNT_LINK_CODE_N = :1";

						l_ABL_Statement1	=	l_ABL_ConnectionPtr->mb_createStatement(l_subsql);
						l_ABL_Statement1.mb_setInt64(1,l_AccountLinkCode);
					
						l_ABL_ResultSet1	=	l_ABL_Statement1.mb_executeQuery();
					

						while(l_ABL_ResultSet1.mb_fetch())
						{
							g_TapCdrs.gMsisdn	=	l_ABL_ResultSet1.mb_getString(1);
						}
						l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement1);
					
					}
					else
					{
					
						*m_ABL_ServicePtr<<DEBUG<<"Account Link Code Not found for IMSI: "<<g_TapCdrs.gImsiNum<<" Call Date: "<<l_CallDateTime<<Endl;
					}
				}
			}

			if (g_TapCdrs.gMsisdn == " " || g_TapCdrs.gMsisdn == "")
			{
				l_PM_Job_Ptr->TAPCdrs[i].gSentToBs	= "P";
				*m_ABL_ServicePtr<<DEBUG<<"MSISDN Number is Null for the CDR::IMSI: "<<g_TapCdrs.gImsiNum<<" CallDate :"<<g_TapCdrs.gCallDate<<g_TapCdrs.gCallTime<<Endl;
				continue;
			}
			else
			{  
				if (g_TapCdrs.gMsisdn.mb_subStr(0,1) == "0" && strcmp(g_TapCdrs.gMsisdn.mb_subStr(0,2).c_str(),"00")!=0  )
				{
					g_TapCdrs.gMsisdn = g_TapCdrs.gMsisdn.mb_subStr(1,g_TapCdrs.gMsisdn.mb_length());
				}
				else if ( g_TapCdrs.gMsisdn.mb_subStr(0,2) == "00" )
				{
					g_TapCdrs.gMsisdn = g_TapCdrs.gMsisdn.mb_subStr(2,g_TapCdrs.gMsisdn.mb_length());
				}

				sprintf(l_CdrMsisdn,"%s",g_TapCdrs.gMsisdn.c_str()) ;
				sub_str(l_CdrMsisdn,l_TempMsisdnPrefix,1,l_CountryCodeLength); 

				if(strcmp(l_TempMsisdnPrefix,l_CountryDiallingCode.c_str())==0)
				{
					l_PM_Job_Ptr->TAPCdrs[i].gMsisdn = g_TapCdrs.gMsisdn;
				}
				else
				{		
					l_PM_Job_Ptr->TAPCdrs[i].gMsisdn = l_CountryDiallingCode + g_TapCdrs.gMsisdn ;
				}

				l_PM_Job_Ptr->TAPCdrs[i].gSentToBs	= "S";
				l_FileSeqNo = l_PM_Job_Ptr->TAPCdrs[i].gFileSeqNum        ;
				l_HplmnCode = l_PM_Job_Ptr->TAPCdrs[i].gHplmnCode         ;
				l_VplmnCode = l_PM_Job_Ptr->TAPCdrs[i].gVplmnCode         ;
				l_CdrSeq    = l_PM_Job_Ptr->TAPCdrs[i].gCdrSeqNum         ;
			}
		}

		l_ABL_ConnectionPtr->mb_commit();
		*m_ABL_ServicePtr<<INFO<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<" :: Process Completed Validation of MSISDN Number"<<Endl;
	} 

	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr<<CRITICAL<<"PM_GetMsisdn::Exception : "<<e.mb_getMessage()<<Endl;
		*m_ABL_ServicePtr<<INFO<<"Updated Sent to BS Status in PM_TAP_FILE_SUMRY :: "<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<Endl;
		l_ABL_ConnectionPtr->mb_rollback();
		l_sql	=	"UPDATE PM_TAP_FILE_SUMRY SET SENT_TO_BS = 'F',SENT_DATE = SYSDATE WHERE(FILE_NAME=:1)";
		l_ABL_Statement	=	l_ABL_ConnectionPtr->mb_createStatement(l_sql);
		l_ABL_Statement.mb_setString (1,((PM_Job*)p_ABL_JobPtr)->m_fileName);
		l_ABL_Statement.mb_executeUpdate();
		l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
		l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);
		l_ABL_ConnectionPtr->mb_commit();
		return false;
	}
	return true;
}

bool PM_GetMsisdn::mb_stop()
{
	/* std::cout << "PM_GetMsisdn111 Stopped " << std::endl; */
	return true;
}

void PM_GetMsisdn::replace_str(char *sou,char *sval,int st_ps,int no_ch,char pad_ch) 
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

/***************************************************************************************************************
Function Name : sub_str

Description : Copies the given total number of character from given starting position of source string
into destination string

Parameter 1 : Source String
Parameter 2 : Destination String
Parameter 3 : Starting position in the Source String
Parameter 4 : No of Characters from the Starting position
***************************************************************************************************************/
void PM_GetMsisdn::sub_str(char *so,char *tr,int st_ps,int no_ch)
{
	int i=0;
	*tr=0;

	while(i<st_ps-1 && *so){so++;i++;}

	i=0;
	while(i<no_ch && *so)
	{
		*tr++=*so++;i++;
	}
	*tr=0;
}

void PM_GetMsisdn::InitialiseTAPCdrsParameters()
{
	g_TapCdrs.gFileTranDir        =   "" ;
	g_TapCdrs.gHplmnCode          =   "" ;
	g_TapCdrs.gVplmnCode          =   "" ;
	g_TapCdrs.gFileTypeInd        =   "" ;
	g_TapCdrs.gFileSeqNum         =   0  ;
	g_TapCdrs.gCallType           =   0  ;
	g_TapCdrs.gImsiNum            =   "" ;
	g_TapCdrs.gCalledCallingNum   =   "" ;
	g_TapCdrs.gCallDate           =   "" ;
	g_TapCdrs.gCallTime           =   "" ;
	g_TapCdrs.gDuration           =   0  ;
	g_TapCdrs.gCallAmount         =   0  ;
	g_TapCdrs.gSurchargeAmount    =   0  ;
	g_TapCdrs.gCdrSeqNum          =   0  ;
	g_TapCdrs.gBasicServType      =   "" ;
	g_TapCdrs.gBasicServCode      =   "" ;
	g_TapCdrs.gDataVolumeIncoming =   "" ;
	g_TapCdrs.gDataVolumeOutgoing =   "" ;
	g_TapCdrs.gAccessPointNameNI  =   "" ;
	g_TapCdrs.gPDPAddress         =   "" ;
	g_TapCdrs.gLocalDateTime      =   "" ;
	g_TapCdrs.gCamelUsedFlag      =   0  ;
	g_TapCdrs.gCdrRepriceflag     =   "" ;
	g_TapCdrs.gMsisdn             =   "" ;
	g_TapCdrs.gSentToBs           =   "" ;
}
