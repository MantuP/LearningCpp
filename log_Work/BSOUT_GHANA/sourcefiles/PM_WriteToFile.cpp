/* Modified on 11-02-2010 by Yogesh to store Reprice Amount as "unsigned long" */
/* Modified on 30-12-2020 by Prabina to write CallAmount as decimal number as per DEFECT-14954 */
#include "PM_WriteToFile.h"
#include "ABL_Service.h"
#include "ABL_DbDate.h"
#include "ABL_Exception.h"
#include "PM_Job.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "ABL_DateTime.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <stdlib.h>

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
	Base_Registry* gb_getPM_WriteToFile()
	{
		return ( (Base_Registry*) new PM_WriteToFile);
	}
}

PM_WriteToFile::PM_WriteToFile()
{
//
}

PM_WriteToFile::~PM_WriteToFile()
{
//
}


PM_WriteToFile::PM_WriteToFile(const PM_WriteToFile& p_copyObject)
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

Base_Registry* PM_WriteToFile::mb_clone()
{
	return ( (Base_Registry*) new PM_WriteToFile);
}

ABL_Process* PM_WriteToFile::mb_createCopy()
{
	return ( new PM_WriteToFile(*this));
}


bool PM_WriteToFile::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
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


bool PM_WriteToFile::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	return true;
}

bool PM_WriteToFile::mb_process(ABL_Job* &p_ABL_JobPtr)
{
	ABL_Connection  *l_ABL_ConnectionPtr  ;
	ABL_Statement   l_ABL_Statement,l_ABL_Statement1       ;
	ABL_ResultSet   l_ABL_ResultSet,l_ABL_ResultSet1       ;
	ABL_String      l_sql,l_subsql        ;
	long            l_totalCdrCount   =0    ;
	long            l_prepaidCount   =0 ;
	ABL_String      l_GsmBsoutFileName       ;
	ABL_String      l_GsmFileName;
	ABL_String      l_GprsFileName;
	ABL_String      l_GsmBsoutSuccessFile    ;
	ABL_String      l_GprsBsoutFileName       ;
	ABL_String      l_GprsBsoutSuccessFile    ;
	char            l_toRatingCdr[233]    ; 
	char            l_toBillingGprs[319]  ;
	FILE            *l_GsmdataFilePtr = NULL ;            /* BSOUT File Pointer */
	FILE            *l_GprsdataFilePtr = NULL ;            /* BSOUT File Pointer */
	long            l_cdrError = 0        ;
	int             l_retValue = 0        ;
	char            l_GsmCreateSuccessFile[500] ;
	char            l_GsmRemoveDataFile[500] ;
	char            l_GsmRemoveSuccessFile[500] ;
	char            l_GprsCreateSuccessFile[500] ;
	char            l_GprsRemoveDataFile[500] ;
	char            l_GprsRemoveSuccessFile[500] ;
	unsigned long   l_RepriceAmount = 0   ;
	long            l_BsoutCdrCount   =0    ;
	long            i; 
	long            l_GsmCdrCount = 0 ;
	long            l_GprsCdrCount = 0 ;
	long            l_SentToBsCount =0 ; // by Lavanya to count the cdrs containing MSISDN
	long            l_FileCdrsCount =0 ;
	ABL_String      l_VplnCode ;
	ABL_String      l_HplmnCode;
	long            l_TotalCount=0;
	ABL_String      l_DateStr ;
	ABL_DbDate	   lDbDate;		  // Added by Maneesh to convert timestamp in ABL dateforamt

	/* Variables are Declared to Check file Size */
	struct stat buffer             ;
	int file_status=0              ;

	PM_Job* l_PM_Job_Ptr = (PM_Job*)p_ABL_JobPtr;
	l_ABL_ConnectionPtr = ((PM_Job*)p_ABL_JobPtr)->mb_getConnection();

	try
	{
		l_GsmBsoutFileName    = ""    ;
		l_GsmBsoutSuccessFile = ""    ;
		l_GprsBsoutFileName    = ""   ;
		l_GprsBsoutSuccessFile = ""   ;
		l_HplmnCode            = ""   ;
		l_VplnCode             = ""   ;
		l_DateStr              = ""   ;
		l_GsmFileName          = ""   ;
		l_GprsFileName         = ""   ;
		l_FileTranDir             =  ((PM_Job*)p_ABL_JobPtr)->m_FileTranDir      ;
		l_HplmnCode               =  ((PM_Job*)p_ABL_JobPtr)->m_HplmnCode        ;
		l_VplmnCode               =  ((PM_Job*)p_ABL_JobPtr)->m_VplmnCode        ;
		l_FileTypeInd             =  ((PM_Job*)p_ABL_JobPtr)->m_FileTypeInd      ;
		l_FileSeqNum              =  ((PM_Job*)p_ABL_JobPtr)->m_FileSeqNum       ;
		// l_SettCallEvents          =  ((PM_Job*)p_ABL_JobPtr)->m_SettCallEvents   ;
		l_FileCdrsCount          =  ((PM_Job*)p_ABL_JobPtr)->m_SettCallEvents   ;
		l_SettCallEvents          =  ((PM_Job*)p_ABL_JobPtr)->m_TotalCdrsMsisdn  ;
		l_FileName                =  ((PM_Job*)p_ABL_JobPtr)->m_FileName         ;
		l_Surchperc               =  ((PM_Job*)p_ABL_JobPtr)->m_Surchperc        ;
		l_PartnerCode             =  ((PM_Job*)p_ABL_JobPtr)->m_PartnerCode      ;
		l_PartnerDesc             =  ((PM_Job*)p_ABL_JobPtr)->m_PartnerDesc      ;
		l_DialingCode             =  ((PM_Job*)p_ABL_JobPtr)->m_DialingCode      ;
		l_Repriceflag             =  ((PM_Job*)p_ABL_JobPtr)->m_Repriceflag      ;
		l_RateIDDFlag             =  ((PM_Job*)p_ABL_JobPtr)->m_RateIDDFlag      ;
		l_CamelFilterFlag         =  ((PM_Job*)p_ABL_JobPtr)->m_CamelFilterFlag  ;
		l_RepriceAgent            =  ((PM_Job*)p_ABL_JobPtr)->m_RepriceAgent     ;

		l_sql="SELECT TO_CHAR(CURRENT_DATE,'YYYYMMDDHH24MISS') FROM DUAL" ;

		l_DateStr              =""   ;

		l_ABL_Statement   =   l_ABL_ConnectionPtr->mb_createStatement(l_sql) ;
		l_ABL_ResultSet  =l_ABL_Statement.mb_executeQuery()          ;
		l_ABL_ResultSet.mb_fetch();

		l_DateStr=   l_ABL_ResultSet.mb_getString(1) ;

		l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet)       ;
		l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);

		l_FileName += "_";
		l_FileName += l_DateStr;
		l_GsmFileName +=l_FileName + "_GSM";
		l_GprsFileName+=l_FileName + "_GPRS";


		l_GsmBsoutFileName    += DataFilesDir + l_FileName    ;
		l_GsmBsoutSuccessFile += SuccessFilesDir + l_FileName ;

		l_GprsBsoutFileName    += DataFilesDir + l_FileName    ;
		l_GprsBsoutSuccessFile += SuccessFilesDir + l_FileName ;

		l_GsmBsoutFileName    += "_GSM" ;
		l_GsmBsoutSuccessFile += "_GSM" ;

		l_GprsBsoutFileName    += "_GPRS" ;
		l_GprsBsoutSuccessFile += "_GPRS" ;

		sprintf(l_GsmCreateSuccessFile,"touch %s",l_GsmBsoutSuccessFile.c_str()) ;
		sprintf(l_GsmRemoveDataFile,"rm %s",l_GsmBsoutFileName.c_str()) ;
		sprintf(l_GsmRemoveSuccessFile,"rm %s",l_GsmBsoutSuccessFile.c_str()) ;

		sprintf(l_GprsCreateSuccessFile,"touch %s",l_GprsBsoutSuccessFile.c_str()) ;
		sprintf(l_GprsRemoveDataFile,"rm %s",l_GprsBsoutFileName.c_str()) ;
		sprintf(l_GprsRemoveSuccessFile,"rm %s",l_GprsBsoutSuccessFile.c_str()) ;
		memset (l_toRatingCdr,' ',sizeof (l_toRatingCdr));
		l_toRatingCdr [sizeof (l_toRatingCdr) - 1] = '\0';

		memset (l_toBillingGprs,' ',sizeof (l_toBillingGprs));
		l_toBillingGprs [sizeof (l_toBillingGprs) - 1] = '\0';

		if ((l_GsmdataFilePtr = fopen (l_GsmBsoutFileName.c_str(),"w")) == NULL)
		{
			*m_ABL_ServicePtr<<INFO<<"Unable to open GSM file for writing:: "<<l_GsmBsoutFileName<<Endl;
			return false;
		}

		if ((l_GprsdataFilePtr = fopen (l_GprsBsoutFileName.c_str(),"w")) == NULL)
		{
			*m_ABL_ServicePtr<<INFO<<"Unable to open GPRS file for writing:: "<<l_GprsBsoutFileName<<Endl;
			return false;
		}

		/**********************************************************************/
		/* Get the CDRs Details for the BSOUT File */
		*m_ABL_ServicePtr<<INFO<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<" :: Writing CDRs details into the File,Camel Flag :"<<l_CamelFilterFlag.c_str()<<Endl;

		for(i=0;i<l_SettCallEvents;i++ )
		{
			InitialiseTAPCdrsParameters();
			char lvalue[100]={0};	  // Added by Maneesh to convert timestamp in ABL dateforamt


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
			g_TapCdrs.gServiceCode        =     l_PM_Job_Ptr->TAPCdrs[i].gServiceCode       ;
			g_TapCdrs.gSentToBs           =     l_PM_Job_Ptr->TAPCdrs[i].gSentToBs          ;
			
			*m_ABL_ServicePtr<<INFO<<"Total Duration : "<<g_TapCdrs.gDuration<<" A CallAmount: "<< g_TapCdrs.gCallAmount <<" B CdrSeqNum " <<g_TapCdrs.gCdrSeqNum <<Endl;

			// Added on 3rd Dec'13 by Maneesh to concatenate callDate and call_time
			strcat (lvalue,g_TapCdrs.gCallDate.c_str());
			strcat (lvalue,g_TapCdrs.gCallTime.c_str());   

			lDbDate.mb_fromText(lvalue);
			l_totalCdrCount = l_totalCdrCount +1;

			if ((g_TapCdrs.gCamelUsedFlag != 0) && (strcmp(l_CamelFilterFlag.c_str(),"Y") == 0))
			{
				l_prepaidCount = l_prepaidCount +1;
				l_sql="";
				l_sql ="UPDATE PM_TAP_CDRS SET TAP_FILE_NAME =:1,SENT_TO_BS = 'FL' WHERE (FILE_SEQUENCE_NUMBER =:2 AND VPLMN_CODE =:3 AND HPLMN_CODE =:4 AND  CALL_SEQUENCE=:5 AND CALL_DATE=:6)";
				l_ABL_Statement         =       l_ABL_ConnectionPtr->mb_createStatement(l_sql);
				l_ABL_Statement.mb_setString (1,l_GsmFileName);	
				l_ABL_Statement.mb_setInt (2,g_TapCdrs.gFileSeqNum);
				l_ABL_Statement.mb_setString (3,g_TapCdrs.gVplmnCode);
				l_ABL_Statement.mb_setString (4, g_TapCdrs.gHplmnCode);
				l_ABL_Statement.mb_setInt (5,g_TapCdrs.gCdrSeqNum);
				l_ABL_Statement.mb_setDate (6,lDbDate);
				l_ABL_Statement.mb_executeUpdate();
				l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);
				continue;
			}

			if(g_TapCdrs.gSentToBs == "S")
			{
				l_SentToBsCount = l_SentToBsCount + 1;

				if(g_TapCdrs.gCallType == 2 && (g_TapCdrs.gServiceCode == "005" ||  g_TapCdrs.gServiceCode == "305")) //Added by Sangram for 305 calls
				{
					PrepareGprsCDRs (l_toBillingGprs);
					/* Write  Each cdr's detail into the BSOUT file */
					l_retValue = 0 ;

					if ((l_retValue = fprintf (l_GprsdataFilePtr,"%s\n",l_toBillingGprs)) != (strlen (l_toBillingGprs) + 1))
					{
						*m_ABL_ServicePtr<<INFO<<"main : Error in writing to file :: "<<l_GprsBsoutFileName<<Endl;
						l_cdrError=1;
						break;
					}

					if(l_cdrError == 0)
					{ 
						l_sql   =       "UPDATE PM_TAP_CDRS SET TAP_FILE_NAME = :1,SENT_TO_BS = 'S'  WHERE (FILE_SEQUENCE_NUMBER =:2 AND VPLMN_CODE = :3 AND HPLMN_CODE = :4  AND CALL_SEQUENCE=:5 AND CALL_DATE=:6)";
						l_ABL_Statement         =       l_ABL_ConnectionPtr->mb_createStatement(l_sql);
						l_ABL_Statement.mb_setString(1,l_GprsFileName);
						l_ABL_Statement.mb_setInt (2,g_TapCdrs.gFileSeqNum);
						l_ABL_Statement.mb_setString (3,g_TapCdrs.gVplmnCode);
						l_ABL_Statement.mb_setString (4, g_TapCdrs.gHplmnCode);
						l_ABL_Statement.mb_setInt (5,g_TapCdrs.gCdrSeqNum);
						l_ABL_Statement.mb_setDate (6,lDbDate);
						l_ABL_Statement.mb_executeUpdate();
						l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);
						l_ABL_ConnectionPtr->mb_commit();
					}
					++l_GprsCdrCount ;
				}
				else
				{
					PrepareGsmLine(l_toRatingCdr);

					/* Write  Each cdr's detail into the BSOUT file */
					l_retValue = 0 ;

					if ((l_retValue = fprintf (l_GsmdataFilePtr,"%s\n",l_toRatingCdr)) != (strlen (l_toRatingCdr) + 1))
					{
						*m_ABL_ServicePtr<<INFO<<"main : Error in writing to file :: "<<l_GsmBsoutFileName<<Endl;
						l_cdrError=1;
						break;
					}

					if(l_cdrError==0)
					{
						/*  UpdateTapCdrs(l_GsmBsoutFileName);*/
						l_sql="";
						l_sql ="UPDATE PM_TAP_CDRS SET TAP_FILE_NAME =:1,SENT_TO_BS = 'S' WHERE (FILE_SEQUENCE_NUMBER =:2 AND VPLMN_CODE =:3 AND HPLMN_CODE =:4 AND  CALL_SEQUENCE=:5 AND CALL_DATE=:6)";
						l_ABL_Statement         =       l_ABL_ConnectionPtr->mb_createStatement(l_sql);
						l_ABL_Statement.mb_setString (1,l_GsmFileName);	
						l_ABL_Statement.mb_setInt (2,g_TapCdrs.gFileSeqNum);
						l_ABL_Statement.mb_setString (3,g_TapCdrs.gVplmnCode);
						l_ABL_Statement.mb_setString (4, g_TapCdrs.gHplmnCode);
						l_ABL_Statement.mb_setInt (5,g_TapCdrs.gCdrSeqNum);
						l_ABL_Statement.mb_setDate (6,lDbDate);
						l_ABL_Statement.mb_executeUpdate();
						l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);
					}

					++l_GsmCdrCount ;
				}
			}
			else
			{
				continue;
			}
		}

		l_ABL_ConnectionPtr->mb_commit();

		if(l_cdrError==1)
		{
			l_cdrError = 0;
			fclose (l_GsmdataFilePtr);
			system (l_GsmRemoveDataFile);
			fclose (l_GprsdataFilePtr);
			system (l_GprsRemoveDataFile);
			return false;
		}

		fclose (l_GsmdataFilePtr);
		fclose (l_GprsdataFilePtr);


		/****************************************************************/
		/* Check the CDRs Count */
		*m_ABL_ServicePtr<<INFO<<"Total CDRs Count : "<<l_totalCdrCount<<" Prepaid CDRs: "<< l_prepaidCount <<" GSM: " <<l_GsmCdrCount << " GPRS: " <<l_GprsCdrCount<<Endl;

		if(l_FileCdrsCount == l_prepaidCount)
		{
			*m_ABL_ServicePtr<<INFO<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<" i: File has to be removed as it contains only PREPAID CALLS"<<Endl;
			*m_ABL_ServicePtr<<INFO<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<" :: Updated Sent to BS Status as Success for the File"<<Endl;
			*m_ABL_ServicePtr<< INFO << "-------------------------------------------------------------------" <<Endl;
			l_sql   =       "UPDATE PM_TAP_FILE_SUMRY SET SENT_TO_BS = 'Y',SENT_DATE = CURRENT_TIMESTAMP WHERE(FILE_NAME=:1)";

			l_ABL_Statement         =       l_ABL_ConnectionPtr->mb_createStatement(l_sql);
			l_ABL_Statement.mb_setString (1,((PM_Job*)p_ABL_JobPtr)->m_fileName);
			l_ABL_Statement.mb_executeUpdate();
			l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
			l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);

			l_ABL_ConnectionPtr->mb_commit();

			system(l_GsmRemoveDataFile) ;
			system(l_GprsRemoveDataFile) ;
			return true ;
		}

		if(l_GsmCdrCount == 0 && l_GprsCdrCount > 0)
		{
			system(l_GsmRemoveDataFile) ;
		}

		if(l_GprsCdrCount == 0 && l_GsmCdrCount > 0)
		{
			system(l_GprsRemoveDataFile) ;
		}

		if(l_GprsCdrCount ==0 && l_GsmCdrCount ==0 && l_FileCdrsCount == l_totalCdrCount)
		{
			*m_ABL_ServicePtr<<INFO<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<" :: Remove the File Because GSM and GPRS CDRs Counts are zero"<<Endl;
			*m_ABL_ServicePtr<<INFO<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<" :: Updated Sent to BS Status as Failure for the File"<<Endl;
			*m_ABL_ServicePtr << INFO << "-------------------------------------------------------------------" <<Endl;
			l_sql   =       "UPDATE PM_TAP_FILE_SUMRY SET SENT_TO_BS = 'F',SENT_DATE = CURRENT_TIMESTAMP WHERE(FILE_NAME=:1)";
			l_ABL_Statement         =       l_ABL_ConnectionPtr->mb_createStatement(l_sql);
			l_ABL_Statement.mb_setString (1,((PM_Job*)p_ABL_JobPtr)->m_fileName);
			l_ABL_Statement.mb_executeUpdate();
			l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
			l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);
			l_ABL_ConnectionPtr->mb_commit();
			system(l_GsmRemoveDataFile) ;
			system(l_GprsRemoveDataFile) ;
			return false ;
		}

		//if gsm and gprs counts are zero and file is a half processed file (file with status "H" ) 
		if(l_GprsCdrCount ==0 && l_GsmCdrCount ==0 &&  l_totalCdrCount>0)
		{
			*m_ABL_ServicePtr<<INFO<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<" :: Remove the File Because GSM and GPRS CDRs Counts are zero"<<Endl;
			*m_ABL_ServicePtr<<INFO<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<" :: Updated Sent to BS Status as H for the File"<<Endl;
			*m_ABL_ServicePtr << INFO << "-------------------------------------------------------------------" <<Endl;
			l_sql   =       "UPDATE PM_TAP_FILE_SUMRY SET SENT_TO_BS = 'H',SENT_DATE = CURRENT_TIMESTAMP WHERE(FILE_NAME=:1)";
			l_ABL_Statement         =       l_ABL_ConnectionPtr->mb_createStatement(l_sql);
			l_ABL_Statement.mb_setString (1,((PM_Job*)p_ABL_JobPtr)->m_fileName);
			l_ABL_Statement.mb_executeUpdate();
			l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
			l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);
			l_ABL_ConnectionPtr->mb_commit();
			system(l_GsmRemoveDataFile) ;
			system(l_GprsRemoveDataFile) ;
			return false ;
		}

		/****************************************************************/
		/* Added to remove 0 byte File */
		file_status = 0;
		buffer.st_size = 0 ;
		file_status = stat(l_GsmBsoutFileName.c_str(),&buffer);
		*m_ABL_ServicePtr<<INFO<<l_GsmBsoutFileName<<" Size  :: "<<(long int)buffer.st_size<<Endl;
		if ((long int)buffer.st_size==0 && (file_status==0)&& (l_GsmCdrCount > 0))
		{
			*m_ABL_ServicePtr<<INFO<<l_GsmBsoutFileName<<" :: Remove the File Because of Zero byte"<<Endl;
			*m_ABL_ServicePtr<<INFO<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<" :: Updated Sent to BS Status as Failure for the File"<<Endl;
			*m_ABL_ServicePtr << INFO << "-------------------------------------------------------------------" <<Endl;
			l_sql   =       "UPDATE PM_TAP_FILE_SUMRY SET SENT_TO_BS = 'F',SENT_DATE = CURRENT_TIMESTAMP WHERE(FILE_NAME=:1)";
			l_ABL_Statement         =       l_ABL_ConnectionPtr->mb_createStatement(l_sql);
			l_ABL_Statement.mb_setString (1,((PM_Job*)p_ABL_JobPtr)->m_fileName);
			l_ABL_Statement.mb_executeUpdate();
			l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
			l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);
			l_ABL_ConnectionPtr->mb_commit();
			system(l_GsmRemoveDataFile) ;
			system(l_GprsRemoveDataFile) ;
			return false ;
		}

		/****************************************************************/
		/* Added to remove 0 byte GPRS File */
		file_status = 0;
		buffer.st_size = 0 ;
		file_status = stat(l_GprsBsoutFileName.c_str(),&buffer);

		*m_ABL_ServicePtr<<INFO<<l_GprsBsoutFileName<<" Size :: "<<(long int)buffer.st_size<<Endl;

		if ((long int)buffer.st_size==0 && (file_status==0)&& (l_GprsCdrCount > 0))
		{
			*m_ABL_ServicePtr<<INFO<<l_GprsBsoutFileName<<" :: Remove the File Because of Zero byte"<<Endl;
			*m_ABL_ServicePtr<<INFO<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<" :: Updated Sent to BS Status as Failure for the File"<<Endl;
			*m_ABL_ServicePtr << INFO << "-------------------------------------------------------------------" <<Endl;
			l_sql   =       "UPDATE PM_TAP_FILE_SUMRY SET SENT_TO_BS = 'F',SENT_DATE = CURRENT_TIMESTAMP WHERE(FILE_NAME=:1)";

			l_ABL_Statement         =       l_ABL_ConnectionPtr->mb_createStatement(l_sql);
			l_ABL_Statement.mb_setString (1,((PM_Job*)p_ABL_JobPtr)->m_fileName);
			l_ABL_Statement.mb_executeUpdate();
			l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
			l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);

			l_ABL_ConnectionPtr->mb_commit();

			system(l_GprsRemoveDataFile) ;
			system(l_GsmRemoveDataFile) ;
			return false ;
		}
		// by lavanya to update tap_file_sumry with status "H" 

		if (l_FileCdrsCount == l_SentToBsCount)
		{

			l_sql   =       "UPDATE PM_TAP_FILE_SUMRY SET SENT_TO_BS = 'Y',SENT_DATE = CURRENT_TIMESTAMP WHERE(FILE_NAME=:1)";

			l_ABL_Statement         =       l_ABL_ConnectionPtr->mb_createStatement(l_sql);
			l_ABL_Statement.mb_setString (1,((PM_Job*)p_ABL_JobPtr)->m_fileName);
			l_ABL_Statement.mb_executeUpdate();
			l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
			l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);

			l_ABL_ConnectionPtr->mb_commit();

			if(strcmp(TouchFileFlag.c_str(),"Y") == 0)
			{
				if(l_GsmCdrCount > 0)
				{
					system(l_GsmCreateSuccessFile);
				} 

				if(l_GprsCdrCount > 0)
				{
					system(l_GprsCreateSuccessFile);
				}
			} 
		}
		else if (l_FileCdrsCount > l_SentToBsCount && l_SentToBsCount>0) 
		{
			*m_ABL_ServicePtr<<DEBUG<<" MSISDN is missing for few of the cdrs. Hence File Status is updated to Half Done"<<Endl; 
			l_sql   =       "UPDATE PM_TAP_FILE_SUMRY SET SENT_TO_BS = 'H',SENT_DATE = CURRENT_TIMESTAMP WHERE(FILE_NAME=:1)";

			l_ABL_Statement         =       l_ABL_ConnectionPtr->mb_createStatement(l_sql);
			l_ABL_Statement.mb_setString (1,((PM_Job*)p_ABL_JobPtr)->m_fileName);
			l_ABL_Statement.mb_executeUpdate();
			l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
			l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);

			l_ABL_ConnectionPtr->mb_commit();

			if(strcmp(TouchFileFlag.c_str(),"Y") == 0)
			{
				if(l_GsmCdrCount > 0)
				{
					system(l_GsmCreateSuccessFile);
				} 

				if(l_GprsCdrCount > 0)
				{
					system(l_GprsCreateSuccessFile);
				}
			}
		}

		l_sql = "SELECT COUNT(*) from PM_TAP_CDRS where FILE_SEQUENCE_NUMBER = :1 AND HPLMN_CODE = :2 AND VPLMN_CODE = :3 AND SENT_TO_BS IN( 'S','FL')";
		l_ABL_Statement         =       l_ABL_ConnectionPtr->mb_createStatement(l_sql);
		l_ABL_Statement.mb_setInt (1,l_FileSeqNum);
		l_ABL_Statement.mb_setString (2,l_HplmnCode);
		l_ABL_Statement.mb_setString (3,l_VplmnCode);
		l_ABL_ResultSet               =   l_ABL_Statement.mb_executeQuery()          ;

		l_ABL_ResultSet.mb_fetch();
		l_TotalCount            =      l_ABL_ResultSet.mb_getInt64(1);
		l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
		l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);

		if(l_FileCdrsCount == l_TotalCount)
		{
			*m_ABL_ServicePtr<<INFO<<" File Successfully processed and File Status is updated to Success"<<Endl;
			l_sql   =       "UPDATE PM_TAP_FILE_SUMRY SET SENT_TO_BS = 'Y',SENT_DATE = CURRENT_TIMESTAMP WHERE(FILE_NAME=:1)";
			l_ABL_Statement         =       l_ABL_ConnectionPtr->mb_createStatement(l_sql);
			l_ABL_Statement.mb_setString (1,((PM_Job*)p_ABL_JobPtr)->m_fileName);
			l_ABL_Statement.mb_executeUpdate();
			l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
			l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);

			l_ABL_ConnectionPtr->mb_commit();

			if(strcmp(TouchFileFlag.c_str(),"Y") == 0)
			{
				if(l_GsmCdrCount > 0)
				{
					system(l_GsmCreateSuccessFile);
				}

				if(l_GprsCdrCount > 0)
				{
					system(l_GprsCreateSuccessFile);
				}
			}
		}  
		*m_ABL_ServicePtr<<INFO<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<" :: Successfully Processed the File"<<Endl;
	} 

	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr<<CRITICAL<<"PM_WriteToFile::Exception : "<<e.mb_getMessage()<<Endl;
		*m_ABL_ServicePtr<<INFO<<((PM_Job*)p_ABL_JobPtr)->m_fileName<<"Updated Sent to BS Status as Failure fo the File :: "<<Endl;
		l_ABL_ConnectionPtr->mb_rollback();
		l_sql   =       "UPDATE PM_TAP_FILE_SUMRY SET SENT_TO_BS = 'F',SENT_DATE = CURRENT_TIMESTAMP WHERE(FILE_NAME=:1)";
		l_ABL_Statement         =       l_ABL_ConnectionPtr->mb_createStatement(l_sql);
		l_ABL_Statement.mb_setString (1,((PM_Job*)p_ABL_JobPtr)->m_fileName);
		l_ABL_Statement.mb_executeUpdate();
		l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
		l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);
		l_ABL_ConnectionPtr->mb_commit();
		system(l_GsmRemoveDataFile) ;
		return false;
	}
	return true;
}

bool PM_WriteToFile::mb_stop()
{
	return true;
}


void PM_WriteToFile::PrepareGsmLine(char *p_lineBufferPtr)
{
	char       l_tempBuffer [100];
	long       l_calltype = 0 ;
	ABL_String       l_chronoNum ;
	int        l_surcharge ;

	/**********************************************************************/
	/* CDR Type:: 1(MT-GSM),2(MO-GSM),3(SS-GSM),4(GPRS) */
	sprintf (l_tempBuffer,"%-2ld",g_TapCdrs.gCallType);
	replace_str (p_lineBufferPtr,l_tempBuffer,1,2,' ');
	p_lineBufferPtr [1 + 2 - 1] = CDR_FIELD_DELIMITER; 

	/**********************************************************************/
	/* Call Type:: GSM: 11- Voice Call, 21 - SMSMT, 22- SMSMO */
	if(strcmp(g_TapCdrs.gBasicServType.c_str(), "B") == 0)                /* Bearer Service Codes */
	{
		/* Video Telephony Calls */
		if(strcmp(g_TapCdrs.gBasicServCode.c_str() , "37") == 0) 
		{
			if(g_TapCdrs.gCallType == 2)
			{
				l_calltype = 81 ;
			}
			else if(g_TapCdrs.gCallType == 1)
			{
				l_calltype = 82 ;
			}
		}
       else
       {
			if(g_TapCdrs.gCallType == 2)
			{
				l_calltype = 71 ;
			}
			else if(g_TapCdrs.gCallType == 1)
			{
				l_calltype = 72 ;
			}
		}
	}
	else if(strcmp(g_TapCdrs.gBasicServType.c_str(), "T") == 0)/* Tele Service Codes */
	{
		if(g_TapCdrs.gCallType == 2)
		{
			if(strcmp(g_TapCdrs.gBasicServCode.c_str() , "22") == 0 || strcmp(g_TapCdrs.gBasicServCode.c_str() , "20") == 0)
			{
				l_calltype = 75 ;	/* GSM-SMSMO */
			}
			else
			{
				l_calltype = 71 ;	/* GSM-MO Voice Call */
			}
         }
		else if(g_TapCdrs.gCallType == 1)
		{
			if(strcmp(g_TapCdrs.gBasicServCode.c_str() ,"21") == 0 || strcmp(g_TapCdrs.gBasicServCode.c_str() , "20") == 0)
			{
				l_calltype = 76 ;	/* GSM-SMSMT */
			}
			else
			{
				l_calltype = 72 ;	/* GSM-MT Voice Call */
			}
		}
	}

	/*if(g_TapCdrs.gCallType == 3)*/
	if(g_TapCdrs.gCallType == 2 && g_TapCdrs.gServiceCode == "006")
	{	
		l_calltype = 73 ;	/*GSM-SS(Suplimentary Service */
	}

	/**********************************************************************/
	/* Call Type(Hard Code)::71(MO Voice Call),75(SMSMO),72(MT Voice Call),76(SMSMT),80(GPRS),73(SS-GSM) */
	sprintf (l_tempBuffer,"%.3ld",l_calltype);
	replace_str (p_lineBufferPtr,l_tempBuffer,4,3,' ');
	p_lineBufferPtr [4 + 3 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Chrono Number */
	/*
	sprintf(l_chronoNum,"%s%s%.5ld",g_TapCdrs.gCallDate.c_str(),g_TapCdrs.gCallTime.c_str(),g_TapCdrs.gCdrSeqNum) ;
	sprintf (l_tempBuffer,"%-20s",l_chronoNum);
	replace_str (p_lineBufferPtr,l_tempBuffer,8,20,' ');  */
	p_lineBufferPtr [8 + 20 - 1 ] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* IMSI Number */
	sprintf (l_tempBuffer,"%-16s",g_TapCdrs.gImsiNum.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,29,16,' ');
	p_lineBufferPtr [29 + 16 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Called Calling Number */
	sprintf (l_tempBuffer,"%-20s",g_TapCdrs.gCalledCallingNum.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,46,20,' ');
	p_lineBufferPtr [46 + 20 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Call Date (VPLMN local Date) */
	sprintf (l_tempBuffer,"%-8s",g_TapCdrs.gCallDate.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,67,8, ' ');
	p_lineBufferPtr [67 + 8 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Call Time (VPLMN local Time) */
	sprintf (l_tempBuffer,"%-6s",g_TapCdrs.gCallTime.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,76,6, ' ');
	p_lineBufferPtr [76 + 6 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Call Duration */
	sprintf (l_tempBuffer,"%-8ld",g_TapCdrs.gDuration);
	replace_str (p_lineBufferPtr,l_tempBuffer,83,8, ' ');
	p_lineBufferPtr [83 + 8 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Destination Country Code */
	/* sprintf (l_tempBuffer,"%-6s",g_TapCdrs.gCalledCallingNum);
	replace_str (p_lineBufferPtr,l_tempBuffer,92,6, ' '); */
	p_lineBufferPtr [92 + 6 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Roaming Partner Dialling Code */
	sprintf (l_tempBuffer,"%-16s",l_DialingCode.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,99,16, ' ');
	p_lineBufferPtr [99 + 16 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Roaming Partner(VPLMN) Description */
	sprintf (l_tempBuffer,"%-40s",l_PartnerDesc.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,116,40,' ');
	p_lineBufferPtr [116 + 40 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Roaming Partner Country Code */
	/* sprintf (l_tempBuffer,"%-6s",g_TapCdrs.gCountryCode);
	replace_str (p_lineBufferPtr,l_tempBuffer,157,6, ' ');  */
	p_lineBufferPtr [157 + 6 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Partner PLMN(VPLMN) Code */
	sprintf (l_tempBuffer,"%-14s",g_TapCdrs.gVplmnCode.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,164,14, ' ');
	p_lineBufferPtr [164 + 14 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Call Amount::Home Currency Charge + Home Currency Tax */
	//sprintf (l_tempBuffer,"%-12ld",g_TapCdrs.gCallAmount );
	//sprintf (l_tempBuffer,"%-12e",g_TapCdrs.gCallAmount ); //exponential format
	/*Added by Prabina to write CallAmount as decimal number as per DEFECT-14954 */
	sprintf (l_tempBuffer,"%-12lf",g_TapCdrs.gCallAmount ); 
	replace_str (p_lineBufferPtr,l_tempBuffer,179,12, ' ');
	p_lineBufferPtr [179 + 12 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Surcharge Percentage */
	l_surcharge = (int)( l_Surchperc * 100 );
	sprintf (l_tempBuffer,"%-5d",l_surcharge);
	replace_str (p_lineBufferPtr,l_tempBuffer,192,5,' ');
	p_lineBufferPtr [192 + 5 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Local CallDateTime::Call Date + (HPLMN Utc Offset - VPLMN Utc Offset) */
	sprintf (l_tempBuffer,"%-15s",g_TapCdrs.gLocalDateTime.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,198,14, ' ');
	p_lineBufferPtr [198 + 14 - 1] = CDR_FIELD_DELIMITER;
	/* p_lineBufferPtr [g_gsmFieldMappingPtr1->fieldStartPos + g_gsmFieldMappingPtr1->length - 1] = CDR_FIELD_DELIMITER; */

	/**********************************************************************/
	/* Reprice : Added to specify whether to reprice TAPIN cdrs or not */
	sprintf (l_tempBuffer,"%-1s",g_TapCdrs.gCdrRepriceflag.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,213,1, ' ');
	p_lineBufferPtr [213 + 1 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Rate IDD : Added to specify MSRN Reprice Flag */
	sprintf (l_tempBuffer,"%-1s",l_RateIDDFlag.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,215,1, ' ');
	p_lineBufferPtr [215 + 1 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* MSISDN Number */
	sprintf (l_tempBuffer,"%-15s",g_TapCdrs.gMsisdn.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,217,15,' ');
	p_lineBufferPtr [217 + 15 - 1] = CDR_FIELD_DELIMITER;
}

void  PM_WriteToFile::PrepareGprsCDRs (char *p_lineBufferPtr)
{
	char       l_tempBuffer [100];
	long       l_calltype = 0 ;
	char       l_chronoNum[21] ;
	int        l_surcharge ;

	/**********************************************************************/
	/* CDR Type:: 4(GPRS) */
	sprintf (l_tempBuffer,"%-2ld",g_TapCdrs.gCallType);
	replace_str (p_lineBufferPtr,l_tempBuffer,1,2,' ');
	p_lineBufferPtr [1 + 2 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Call Type:: GPRS-080 */
	//if(g_TapCdrs.gCallType == 4)

	if(g_TapCdrs.gCallType == 2 && g_TapCdrs.gServiceCode == "005")
	{
		l_calltype = 80 ;	/* GPRS Call */
	}
	else if (g_TapCdrs.gCallType == 2 && g_TapCdrs.gServiceCode == "305") //Added by Sangram for LTE DATA */
	{
		l_calltype = 95;
	}

	sprintf (l_tempBuffer,"%.3ld",l_calltype);
	replace_str (p_lineBufferPtr,l_tempBuffer,4,3,' ');
	p_lineBufferPtr [4 + 3 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Chrono Number */
	/*
	sprintf(l_chronoNum,"%s%s%.5ld",g_TapCdrs.gCallDate,g_TapCdrs.gCallTime,g_TapCdrs.gCdrSeqNum) ;
	sprintf (l_tempBuffer,"%-20s",l_chronoNum);
	replace_str (p_lineBufferPtr,l_tempBuffer,8,20,' ');  */
	p_lineBufferPtr [8 + 20 - 1 ] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* IMSI Number */
	sprintf (l_tempBuffer,"%-16s",g_TapCdrs.gImsiNum.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,29,16,' ');
	p_lineBufferPtr [29 + 16 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Called Calling Number */
	/*  sprintf (l_tempBuffer,"%-20s",g_TapCdrs.gCalledCallingNum);
	replace_str (p_lineBufferPtr,l_tempBuffer,46,20,' ');        */
	p_lineBufferPtr [46 + 20 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Call Date (VPLMN local Date) */
	sprintf (l_tempBuffer,"%-8s",g_TapCdrs.gCallDate.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,67,8, ' ');
	p_lineBufferPtr [67 + 8 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Call Time (VPLMN local Time) */
	sprintf (l_tempBuffer,"%-6s",g_TapCdrs.gCallTime.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,76,6, ' ');
	p_lineBufferPtr [76 + 6 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Call Duration */
	sprintf (l_tempBuffer,"%-8ld",g_TapCdrs.gDuration);
	replace_str (p_lineBufferPtr,l_tempBuffer,83,8, ' ');
	p_lineBufferPtr [83 + 8 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Destination Country Code */
	/* sprintf (l_tempBuffer,"%-6s",g_TapCdrs.gCalledCallingNum);
	replace_str (p_lineBufferPtr,l_tempBuffer,92,6, ' '); */
	p_lineBufferPtr [92 + 6 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/*DataVolumeIncoming :It identifies the number of incoming octets (bytes) within
	an occurrence of GPRS Service Used or Content Service Used.*/
	sprintf (l_tempBuffer,"%-14s",g_TapCdrs.gDataVolumeIncoming.c_str());
	//sprintf (l_tempBuffer,"%-14lf",g_TapCdrs.gDataVolumeIncoming);
	replace_str (p_lineBufferPtr,l_tempBuffer,99,14,' ');
	p_lineBufferPtr [99 + 14 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/*DataVolumeOutgoing :It identifies the number of outgoing octets (bytes) within
	an occurrence of GPRS Service Used or Content Service Used.*/
	sprintf (l_tempBuffer,"%-14s",g_TapCdrs.gDataVolumeOutgoing.c_str());
	//sprintf (l_tempBuffer,"%-14lf",g_TapCdrs.gDataVolumeOutgoing);
	replace_str (p_lineBufferPtr,l_tempBuffer,114,14,' ');
	p_lineBufferPtr [114 + 14 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/*APN NI:The logical Access Point Name (APN) used to determine the actual
	connected access point for a GPRS connection */
	sprintf (l_tempBuffer,"%-63s",g_TapCdrs.gAccessPointNameNI.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,129,63,' ');
	p_lineBufferPtr [129 + 63 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Roaming Partner Dialling Code */
	sprintf (l_tempBuffer,"%-8s",l_DialingCode.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,193,8, ' ');
	p_lineBufferPtr [193 + 8 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Roaming Partner(VPLMN) Description */
	sprintf (l_tempBuffer,"%-40s",l_PartnerDesc.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,202,40,' ');
	p_lineBufferPtr [202 + 40 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Roaming Partner Country Code */
	/* sprintf (l_tempBuffer,"%-8s",g_TapCdrs.gCountryCode);
	replace_str (p_lineBufferPtr,l_tempBuffer,243,6, ' ');  */
	p_lineBufferPtr [243 + 6 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Partner PLMN(VPLMN) Code */
	sprintf (l_tempBuffer,"%-14s",g_TapCdrs.gVplmnCode.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,250,14, ' ');
	p_lineBufferPtr [250 + 14 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Call Amount::Home Currency Charge + Home Currency Tax */
	sprintf (l_tempBuffer,"%-12ld",g_TapCdrs.gCallAmount);
	replace_str (p_lineBufferPtr,l_tempBuffer,265,12, ' ');
	p_lineBufferPtr [265 + 12 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Surcharge Percentage */
	l_surcharge = (int) (l_Surchperc * 100) ;

	sprintf (l_tempBuffer,"%-5d",l_surcharge);
	replace_str (p_lineBufferPtr,l_tempBuffer,278,5,' ');
	p_lineBufferPtr [278 + 5 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Local CallDateTime::Call Date + (HPLMN Utc Offset - VPLMN Utc Offset) */
	sprintf (l_tempBuffer,"%-15s",g_TapCdrs.gLocalDateTime.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,284,14, ' ');
	p_lineBufferPtr [284 + 14 - 1] = CDR_FIELD_DELIMITER;

	/* p_lineBufferPtr [g_gsmFieldMappingPtr1->fieldStartPos + g_gsmFieldMappingPtr1->length - 1] = CDR_FIELD_DELIMITER; */
	/**********************************************************************/
	/*PDP Address:An address (served) used with a Packet Data Protocol context of a GPRS connection */
	/*
	sprintf (l_tempBuffer,"%-11s",g_TapCdrs.gPDPAddress);
	replace_str (p_lineBufferPtr,l_tempBuffer,234,31,' ');
	p_lineBufferPtr [234 + 31 - 1] = CDR_FIELD_DELIMITER;
	*/
	/**********************************************************************/
	/* Reprice : Added to specify whether to reprice TAPIN cdrs or not */
	sprintf (l_tempBuffer,"%-1s",g_TapCdrs.gCdrRepriceflag.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,299,1, ' ');
	p_lineBufferPtr [299 + 1 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* Rate IDD : Added to specify MSRN Reprice Flag */
	sprintf (l_tempBuffer,"%-1s",l_RateIDDFlag.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,301,1, ' ');
	p_lineBufferPtr [301 + 1 - 1] = CDR_FIELD_DELIMITER;

	/**********************************************************************/
	/* MSISDN Number */
	sprintf (l_tempBuffer,"%-15s",g_TapCdrs.gMsisdn.c_str());
	replace_str (p_lineBufferPtr,l_tempBuffer,303,15,' ');
	p_lineBufferPtr [303 + 15 - 1] = CDR_FIELD_DELIMITER;

}

void PM_WriteToFile::replace_str(char *sou,char *sval,int st_ps,int no_ch,char pad_ch) 
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

void PM_WriteToFile::InitialisePartnerDetails()
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

void PM_WriteToFile::InitialiseTAPCdrsParameters()
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
	g_TapCdrs.gDataVolumeOutgoing =   "";
	g_TapCdrs.gAccessPointNameNI  =   "" ;
	g_TapCdrs.gPDPAddress         =   "" ;
	g_TapCdrs.gLocalDateTime      =   "" ;
	g_TapCdrs.gCamelUsedFlag      =   0  ;
	g_TapCdrs.gCdrRepriceflag     =   "" ;
	g_TapCdrs.gMsisdn             =   "" ;
	g_TapCdrs.gServiceCode        =   "" ;
}

