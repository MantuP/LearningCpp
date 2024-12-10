#include "PM_FetchCdrFile.h"

#include <sys/stat.h>
#include <time.h>
#define INIT_STR(vc_x) (memset(vc_x,'\0',sizeof(vc_x)));
#ifdef WIN32
#include <io.h>
#else
//#include <dir.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

#include<stdio.h>
#include <stdlib.h>

DIR*   DirPtr;

extern "C" 
{
	EXPORT Base_Registry* gb_getPM_FetchCdrFile()
	{
		return ( (Base_Registry*) new PM_FetchCdrFile);
	}
}

PM_FetchCdrFile::PM_FetchCdrFile()
{
//
}

PM_FetchCdrFile::~PM_FetchCdrFile()
{
//
}

PM_FetchCdrFile::PM_FetchCdrFile(const PM_FetchCdrFile& p_copyObject)
{
	this->m_ABL_ServicePtr  = p_copyObject.m_ABL_ServicePtr;
	/*this->m_directoryName   = p_copyObject.m_directoryName; */
	this->m_fileNames	= p_copyObject.m_fileNames;
	this->m_stopFileName	= p_copyObject.m_stopFileName; 
	/*this->gStMasterdata	=	p_copyObject.gStMasterdata;
	this->l_processId	=	p_copyObject.l_processId;*/
}

Base_Registry* PM_FetchCdrFile::mb_clone()
{
	return ( (Base_Registry*) new PM_FetchCdrFile );
}

ABL_Process* PM_FetchCdrFile::mb_createCopy()
{
	return ( new PM_FetchCdrFile (*this));
}

bool PM_FetchCdrFile::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{
	m_ABL_ServicePtr = p_ABL_ServicePtr ;
	ABL_Connection     l_ABL_Connection ;
	ABL_Statement      l_ABL_Statement  ;
	ABL_ResultSet      l_ABL_ResultSet  ;
	ABL_String         l_sql            ;
	ABL_String         BackupFlag       ;
	ABL_String         TouchFileFlag    ;
	ABL_String         UTCOffset        ;

	char  DataFilesDir[250]      ;
	char  ProcessFilesDir[250]   ;
	char  ErrorFilesDir[250]     ;
	char  SuccessFilesDir[250]   ;
	char  BackupFilesDir[250]    ;
	char  StopSignalDir[150]     ;
	int   l_ProcessCount         ;
	int   l_ProcessDetailsCount  ;
	FILE  *lockfp = NULL         ;

	/*******************************************************************************/
	/* Create the DB Connection */

	l_ABL_Connection.mb_createConnection(*m_ABL_ServicePtr);

	try
	{
		gUnixPid = 0 ;
		gUnixPid = getpid() ;

		/*
		gProcessStartDate = "" ;
		l_sql="SELECT TO_CHAR(CURRENT_DATE,'YYYYMMDDHH24MISS') FROM DUAL" ;

		l_ABL_Statement   =   l_ABL_Connection.mb_createStatement(l_sql) ;
		l_ABL_ResultSet   =   l_ABL_Statement.mb_executeQuery()          ;
		l_ABL_ResultSet.mb_fetch();

		gProcessStartDate =   l_ABL_ResultSet.mb_getString(1) ;

		l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet)       ;
		l_ABL_Connection.mb_terminateStatement(l_ABL_Statement)  ;
		*/

		/***************************************************************************/
		/* Get UTC_OFFSET from PM_ROAMING_PREFERENCES */

		l_sql="SELECT substr(UTC_OFFSET,1,3)||':'||substr(UTC_OFFSET,4,5) FROM PM_ROAMING_PREFERENCES WHERE HOME_OPERATOR_CODE = 1";

		l_ABL_Statement   =   l_ABL_Connection.mb_createStatement(l_sql) ;
		l_ABL_ResultSet   =   l_ABL_Statement.mb_executeQuery()          ;
		l_ABL_ResultSet.mb_fetch();

		UTCOffset         =   l_ABL_ResultSet.mb_getString(1) ;

		l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet)       ;
		l_ABL_Connection.mb_terminateStatement(l_ABL_Statement)  ;

		/***************************************************************************/
		/* Check the entry in PM_PROCESSES and PM_PROCESS_DETAILS Table */

		InitialiseProcessVar() ;
		l_ProcessCount        = 0;
		l_ProcessDetailsCount = 0;

		INIT_STR(DataFilesDir)   ;
		INIT_STR(ProcessFilesDir);
		INIT_STR(ErrorFilesDir)  ;
		INIT_STR(SuccessFilesDir);
		INIT_STR(BackupFilesDir) ;
		INIT_STR(StopSignalDir)  ;

		l_sql="SELECT COUNT(*) FROM PM_PROCESSES WHERE PROCESS_ID =7";

		l_ABL_Statement   =   l_ABL_Connection.mb_createStatement(l_sql) ;
		l_ABL_ResultSet   =   l_ABL_Statement.mb_executeQuery()          ;
		l_ABL_ResultSet.mb_fetch();

		l_ProcessCount    =   l_ABL_ResultSet.mb_getInt(1) ;

		l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet)       ;
		l_ABL_Connection.mb_terminateStatement(l_ABL_Statement)  ;

		if(l_ProcessCount == 0)
		{
			*m_ABL_ServicePtr<<CRITICAL<<"There is no Details in PM_PROCESSES Table.Exiting from the Process"<<Endl;
			*m_ABL_ServicePtr << INFO << "-------------------------------------------------------------------" <<Endl;
			return false ;
		}

		l_sql="SELECT COUNT(*) FROM PM_PROCESS_DETAILS WHERE PROCESS_ID =7";

		l_ABL_Statement               =   l_ABL_Connection.mb_createStatement(l_sql) ;
		l_ABL_ResultSet               =   l_ABL_Statement.mb_executeQuery()          ;
		l_ABL_ResultSet.mb_fetch();

		l_ProcessDetailsCount  =   l_ABL_ResultSet.mb_getInt(1) ;

		l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet)       ;
		l_ABL_Connection.mb_terminateStatement(l_ABL_Statement)  ;

		if(l_ProcessDetailsCount == 0)
		{
			*m_ABL_ServicePtr<<CRITICAL<<"There is no Details in PM_PROCESS_DETAILS Table. Exiting from the Process"<<Endl;
			*m_ABL_ServicePtr << INFO << "-------------------------------------------------------------------" <<Endl;
			return false ;
		}

		/***************************************************************************/
		/* Get the Lock File and Stop File directory path from PM_PROCESSES Table and Validate them */

		l_sql="SELECT NVL(TRIM(LOCK_FILE_PATH),' '),NVL(TRIM(STOP_SIGNAL_DIR),' '),NVL(TRIM(STOP_SIGNAL_FILE),' '),NVL(TRIM(FILE_TYPE_INDICATOR),' ') FROM PM_PROCESSES WHERE PROCESS_ID =7";

		l_ABL_Statement      =   l_ABL_Connection.mb_createStatement(l_sql) ;
		l_ABL_ResultSet      =   l_ABL_Statement.mb_executeQuery()          ;
		l_ABL_ResultSet.mb_fetch();

		gStMasterdata.LockFileDir        =   l_ABL_ResultSet.mb_getString(1) ;
		gStMasterdata.StopSignDir        =   l_ABL_ResultSet.mb_getString(2) ;
		gStMasterdata.StopSignFile       =   l_ABL_ResultSet.mb_getString(3) ;
		gStMasterdata.FileTypeIndicator  =   l_ABL_ResultSet.mb_getString(4) ;

		l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet)       ;
		l_ABL_Connection.mb_terminateStatement(l_ABL_Statement)  ;

		sprintf(StopSignalDir,"%s",gStMasterdata.StopSignDir.c_str()) ;  

		/* Form the Stop Signal Directory */
		if(StopSignalDir[strlen(StopSignalDir)-1]=='/')
		{
			StopSignalDir[strlen(StopSignalDir)-1]='\0';
		}
		sprintf(StopSignalDir,"%s/",StopSignalDir);

		/* Check for lock file and exit from the Process if already running */
		lockfp = fopen(gStMasterdata.LockFileDir.c_str(),"r") ;
		int IsBsoutRunning = 0;
		IsBsoutRunning=access(gStMasterdata.LockFileDir.c_str(),F_OK);

		if (IsBsoutRunning == 0)
		{
			*m_ABL_ServicePtr<<CRITICAL<<"Lock signal found. "<<gStMasterdata.LockFileDir<<"lock status : "<<IsBsoutRunning <<Endl;
			*m_ABL_ServicePtr<<CRITICAL<<"Process is Already Running..." <<Endl;
			*m_ABL_ServicePtr << INFO << "-------------------------------------------------------------------" <<Endl;
			return false;
		}

		/* Create a Lock File for the Process and Update the Process Status as Running */
		ABL_String l_command("echo .> ");
		l_command +=gStMasterdata.LockFileDir;
		system(l_command.c_str());
		/*
		sprintf(gErrorMessage,"%s","Normal Exit"); 
		UpdateProcess(7,"R",&l_ABL_Connection );
		*/

		/***************************************************************************/
		/* Get the Files, Success Directory Path from the PM_PROCESS_DETAILS  and Do the Validation */

		l_sql="SELECT NVL(TRIM(HOME_DIR_FLG),' '),NVL(TRIM(TOUCHFILES_FLG),' '),NVL(TRIM(BACKUP_FILES_FLG),' '),NVL(TRIM(HOME_DIR),' '),NVL(TRIM(FILES_DIR),' '),NVL(TRIM(PROCESS_FILES_DIR),' '),NVL(TRIM(ERROR_FILES_DIR),' '),NVL(TRIM(BACKUP_FILES_DIR),' '),NVL(TRIM(SUCCESS_FILES_DIR),' ') FROM PM_PROCESS_DETAILS WHERE PROCESS_ID=7";

		l_ABL_Statement               =   l_ABL_Connection.mb_createStatement(l_sql) ;
		l_ABL_ResultSet               =   l_ABL_Statement.mb_executeQuery()          ;
		l_ABL_ResultSet.mb_fetch() ;

		gStMasterdata.HomeDirFlag     =   l_ABL_ResultSet.mb_getString(1) ;
		gStMasterdata.TouchFilesFlag  =   l_ABL_ResultSet.mb_getString(2) ;
		gStMasterdata.BackupFilesFlag =   l_ABL_ResultSet.mb_getString(3) ;
		gStMasterdata.HomeDir         =   l_ABL_ResultSet.mb_getString(4) ;
		gStMasterdata.FilesDir        =   l_ABL_ResultSet.mb_getString(5) ;
		gStMasterdata.ProcessFilesDir =   l_ABL_ResultSet.mb_getString(6) ;
		gStMasterdata.ErrorFilesDir   =   l_ABL_ResultSet.mb_getString(7) ;
		gStMasterdata.BackupFilesDir  =   l_ABL_ResultSet.mb_getString(8) ;
		gStMasterdata.SuccessFilesDir =   l_ABL_ResultSet.mb_getString(9) ;

		l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet)      ;
		l_ABL_Connection.mb_terminateStatement(l_ABL_Statement) ;

		m_directoryName=gStMasterdata.HomeDir;
		m_directoryName+=gStMasterdata.FilesDir;

		/* Check Home Directory Flag('Y' or 'N') and Select Directories Path Based on Home Directory Flag */
		if (strcmp(gStMasterdata.HomeDirFlag.c_str(),"Y")==0)
		{
			sprintf(DataFilesDir,"%s%s",gStMasterdata.HomeDir.c_str(),gStMasterdata.FilesDir.c_str()) ;
			sprintf(ProcessFilesDir,"%s%s",gStMasterdata.HomeDir.c_str(),gStMasterdata.ProcessFilesDir.c_str()) ;
			sprintf(ErrorFilesDir,"%s%s",gStMasterdata.HomeDir.c_str(),gStMasterdata.ErrorFilesDir.c_str()) ;
			sprintf(SuccessFilesDir,"%s%s",gStMasterdata.HomeDir.c_str(), gStMasterdata.SuccessFilesDir.c_str()) ;
			sprintf(BackupFilesDir,"%s%s",gStMasterdata.HomeDir.c_str(), gStMasterdata.BackupFilesDir.c_str()) ;
		}
		else if (strcmp(gStMasterdata.HomeDirFlag.c_str(),"N")==0)
		{
			sprintf(DataFilesDir,"%s",gStMasterdata.FilesDir.c_str());
			sprintf(ProcessFilesDir,"%s",gStMasterdata.ProcessFilesDir.c_str());
			sprintf(ErrorFilesDir,"%s",gStMasterdata.ErrorFilesDir.c_str());
			sprintf(SuccessFilesDir,"%s",gStMasterdata.SuccessFilesDir.c_str());
			sprintf(BackupFilesDir,"%s",gStMasterdata.BackupFilesDir.c_str());
		}

		BackupFlag=gStMasterdata.BackupFilesFlag;

		/*  Form the Files Directory */
		if(DataFilesDir[strlen(DataFilesDir)-1]=='/')
		{
			DataFilesDir[strlen(DataFilesDir)-1]='\0';
		}
		sprintf(DataFilesDir,"%s/",DataFilesDir); 

		/* Form the Success Directory */
		if(SuccessFilesDir[strlen(SuccessFilesDir)-1]=='/')
		{
			SuccessFilesDir[strlen(SuccessFilesDir)-1]='\0';
		}
		sprintf(SuccessFilesDir,"%s/",SuccessFilesDir); 

		*m_ABL_ServicePtr << INFO << "UTC OffSet         :: " << UTCOffset                       <<Endl;
		*m_ABL_ServicePtr << INFO << "Data Files dir     :: " << DataFilesDir                    <<Endl;
		*m_ABL_ServicePtr << INFO << "Success Files Dir  :: " << SuccessFilesDir                 <<Endl;
		*m_ABL_ServicePtr << INFO << "Lock File Dir      :: " << gStMasterdata.LockFileDir       <<Endl;
		*m_ABL_ServicePtr << INFO << "Stop Signal Dir    :: " << StopSignalDir                   <<Endl;
		*m_ABL_ServicePtr << INFO << "Stop signal file   :: " << gStMasterdata.StopSignFile      <<Endl;
		*m_ABL_ServicePtr << INFO << "File Type Indicator:: " << gStMasterdata.FileTypeIndicator <<Endl;

		/****************************************************************************************/
		/* Check for Valid Stop Signal Directory Path */

		if(strcmp(StopSignalDir," ")==0 || strlen(StopSignalDir) < 3)
		{
			*m_ABL_ServicePtr << CRITICAL << "ERROR  : FILES_DIR in PM_PROCESS_DETAILS is null" <<Endl;
			*m_ABL_ServicePtr << CRITICAL << "main   : Exiting from the Process" <<Endl;
			*m_ABL_ServicePtr << INFO << "-------------------------------------------------------------------" <<Endl;
			sprintf(gErrorMessage,"%s","ERROR  : FILES_DIR in PM_PROCESS_DETAILS is null"); 
			UpdateProcess(7,"S",&l_ABL_Connection );
			unlink(gStMasterdata.LockFileDir.c_str()) ;
			return false;
		}

		DirPtr = NULL;
		DirPtr = opendir(StopSignalDir);

		/* Check if the Directory specified is Valid */
		if(!DirPtr)
		{
			*m_ABL_ServicePtr << CRITICAL <<  "ERROR : Invalid BSOUT Signal directory Specified in PM_PROCESS_DETAILS table"       << Endl;
			*m_ABL_ServicePtr << CRITICAL <<  "Stop Signal Directory Directory :" << StopSignalDir     << Endl;
			*m_ABL_ServicePtr << CRITICAL <<  "main   : Exiting from the Process"     << Endl;
			*m_ABL_ServicePtr << INFO << "-------------------------------------------------------------------" <<Endl;
			sprintf(gErrorMessage,"%s-%s-","ERROR : Invalid BSOUT Signal directory Specified in PM_PROCESS_DETAILS table",StopSignalDir); 
			UpdateProcess(7,"S",&l_ABL_Connection );
			unlink(gStMasterdata.LockFileDir.c_str()) ;
			return false ;
		}

		/* Close the Directory */
		closedir(DirPtr);
		DirPtr = NULL;

		/****************************************************************************************/
		/* Check for Valid Files Directory Path */
		if(strcmp(DataFilesDir," ")==0 || strlen(DataFilesDir) < 3)
		{
			*m_ABL_ServicePtr << CRITICAL << "ERROR  : FILES_DIR in PM_PROCESS_DETAILS is null" <<Endl;
			*m_ABL_ServicePtr << CRITICAL << "main   : Exiting from the Process" <<Endl;
			*m_ABL_ServicePtr << INFO << "-------------------------------------------------------------------" <<Endl;
			sprintf(gErrorMessage,"%s","ERROR  : FILES_DIR in PM_PROCESS_DETAILS is null"); 
			UpdateProcess(7,"S",&l_ABL_Connection );
			unlink(gStMasterdata.LockFileDir.c_str()) ;
			return false ;
		}


		DirPtr = NULL;
		DirPtr = opendir(DataFilesDir);

		/* Check if the Directory specified is Valid */
		if(!DirPtr)
		{            
			*m_ABL_ServicePtr << CRITICAL <<  "ERROR : Invalid BSOUT Files directory Specified in PM_PROCESS_DETAILS table"       << Endl;
			*m_ABL_ServicePtr << CRITICAL <<  "Files Directory :" << DataFilesDir     << Endl;
			*m_ABL_ServicePtr << CRITICAL <<  "main   : Exiting from the Process"     << Endl;
			*m_ABL_ServicePtr << INFO << "-------------------------------------------------------------------" <<Endl;
			sprintf(gErrorMessage,"%s-%s-","ERROR : Invalid BSOUT Files directory Specified in PM_PROCESS_DETAILS table",DataFilesDir); 
			UpdateProcess(7,"S",&l_ABL_Connection );
			unlink(gStMasterdata.LockFileDir.c_str()) ;
			return false ;
		}

		/* Close the Directory */
		closedir(DirPtr);
		DirPtr = NULL;

		/* *m_ABL_ServicePtr << INFO << "Files  Directory of BSOUT Files         :: " << DataFilesDir      << Endl; */
		if(strcmp(gStMasterdata.TouchFilesFlag.c_str(), "Y") == 0)
		{
			if(strcmp(SuccessFilesDir," ")==0 || strlen(SuccessFilesDir) < 3)
			{
				*m_ABL_ServicePtr << CRITICAL << "ERROR  : SUCCESS_DIRECTORY in PM_PROCESS_DETAILS is null" <<Endl;
				*m_ABL_ServicePtr << CRITICAL << "main   : Exiting from the Process" <<Endl;
				*m_ABL_ServicePtr << INFO << "-------------------------------------------------------------------" <<Endl;
				sprintf(gErrorMessage,"%s","ERROR  : SUCCESS_DIRECTORY in PM_PROCESS_DETAILS is null"); 
				UpdateProcess(7,"S",&l_ABL_Connection );
				unlink(gStMasterdata.LockFileDir.c_str()) ;
				return false ;
			}

			DirPtr = NULL;
			DirPtr = opendir(SuccessFilesDir);

			/* Check if the Directory specified is Valid */
			if(!DirPtr)
			{
				*m_ABL_ServicePtr << CRITICAL <<  "ERROR : Invalid BSOUT Success directory Specified in PM_PROCESS_DETAILS table"       << Endl;
				*m_ABL_ServicePtr << CRITICAL <<  "Success Directory :" << SuccessFilesDir     << Endl;
				*m_ABL_ServicePtr << CRITICAL <<  "main   : Exiting from the Process"     << Endl;
				*m_ABL_ServicePtr << INFO << "-------------------------------------------------------------------" <<Endl;
				sprintf(gErrorMessage,"%s-%s-","ERROR : Invalid BSOUT Success directory Specified in PM_PROCESS_DETAILS table",SuccessFilesDir); 
				UpdateProcess(7,"S",&l_ABL_Connection );
				unlink(gStMasterdata.LockFileDir.c_str()) ;
				return false ;
			}
			/* Close the Directory */
			closedir(DirPtr);
			DirPtr = NULL;
		}
		else
		{
			*m_ABL_ServicePtr << INFO <<  "Process will not Generate Success files" << Endl;
			*m_ABL_ServicePtr << INFO <<  "Make TOUCHFILES_FLG = 'Y' in PM_PROCESS_DETAILS to Generate Success Files" << Endl;
		}

		/* *m_ABL_ServicePtr << INFO << "Success  Directory of          :: " << SuccessFilesDir      << Endl; */
		try
		{
			p_ABL_AgentCommunicatorPtr->mb_setParameter("UTCOffset",UTCOffset);
			p_ABL_AgentCommunicatorPtr->mb_setParameter("DataFilesDir",DataFilesDir);
			p_ABL_AgentCommunicatorPtr->mb_setParameter("SuccessFilesDir",SuccessFilesDir);
			p_ABL_AgentCommunicatorPtr->mb_setParameter("TouchFileFlag",gStMasterdata.TouchFilesFlag.c_str());
			p_ABL_AgentCommunicatorPtr->mb_setParameter("LockFile",gStMasterdata.LockFileDir.c_str());
		}
		catch(ABL_Exception &e)
		{
			*m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
			sprintf(gErrorMessage,"%s-%s-","Exception",e.mb_getMessage().c_str()); 
			UpdateProcess(7,"S",&l_ABL_Connection );
			unlink(gStMasterdata.LockFileDir.c_str()) ;
			return false;
		}
	}
	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
		return false;
	}

	try
	{
		m_directoryName   = DataFilesDir   ;
		m_stopFileName    = StopSignalDir  ;
		m_stopFileName   += gStMasterdata.StopSignFile ;
		/* p_ABL_AgentCommunicatorPtr->mb_setParameter("FILES_FOLDER",m_directoryName); */
		p_ABL_AgentCommunicatorPtr->mb_setParameter("STOP_FILE",m_stopFileName);
	}
	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr<<CRITICAL<<"Exception ::PM_FetchCdrFile "<<e.mb_getMessage()<<Endl;
		*m_ABL_ServicePtr<<CRITICAL<<"mb_initProcess "<<e.mb_getMessage()<<Endl;
		sprintf(gErrorMessage,"%s-%s-","Exception",e.mb_getMessage().c_str()); 
		UpdateProcess(7,"S",&l_ABL_Connection );
		unlink(gStMasterdata.LockFileDir.c_str()) ;
		return false;
	}

	ABL_String  l_FileTypeIndicator1 ;
	ABL_String  l_FileTypeIndicator2 ;
	ABL_String  l_FileName[10000]    ;
	long l_partnerCount;

	try
	{
		if(strcmp(gStMasterdata.FileTypeIndicator.c_str(),"B") == 0)
		{
			l_FileTypeIndicator1 = "C" ;
			l_FileTypeIndicator2 = "T" ;
		}
		else if(strcmp(gStMasterdata.FileTypeIndicator.c_str(),"C") == 0)
		{
			l_FileTypeIndicator1 = "C" ;
			l_FileTypeIndicator2 = "C" ;
		}
		else
		{
			l_FileTypeIndicator1 = "T" ;
			l_FileTypeIndicator2 = "T" ;
		}

		/****************************************************************************************/
		/* Get the Count of Pending BSOUT Files  - modified by lavanya to consider files with "H" status. On 25-apr-2013*/
		l_sql="SELECT COUNT(*) FROM  PM_TAP_FILE_SUMRY A WHERE A.FILE_TRANSFER_DIRECTION = 'I' AND A.SENT_TO_BS IN ( 'N','H')  AND A.FILE_TYPE_INDICATOR IN(:1,:2) AND A.DATA_TYPE_INDICATOR = 'D' ";
		l_ABL_Statement	=	l_ABL_Connection.mb_createStatement(l_sql) ;
		l_ABL_Statement.mb_setString(1,l_FileTypeIndicator1) ;
		l_ABL_Statement.mb_setString(2,l_FileTypeIndicator2) ;
		l_ABL_ResultSet	=	l_ABL_Statement.mb_executeQuery();
		l_ABL_ResultSet.mb_fetch() ;
		l_partnerCount	=	l_ABL_ResultSet.mb_getInt(1);

		l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
		l_ABL_Connection.mb_terminateStatement(l_ABL_Statement);

		if (l_partnerCount == 0)
		{
			*m_ABL_ServicePtr<<INFO<<"main : No new records in PM_TAP_FILE_SUMRY "<<Endl;
			/* UpdateProcess(7,"S",&l_ABL_Connection ); */
			ABL_String l_command("echo .> ");
			l_command +=m_stopFileName.c_str();
			system(l_command.c_str());
			return false;
		}

		*m_ABL_ServicePtr << INFO <<"main : Number of files in PM_TAP_FILE_SUMRY::"<<l_partnerCount<<Endl;
		/****************************************************************************************/
		/* Get the BSOUT File Names - modified by lavanya to fetch files with "H" status as well. On 25/04/2013 */

		l_sql ="SELECT NVL(A.FILE_NAME,' ') FROM  PM_TAP_FILE_SUMRY A WHERE A.FILE_TRANSFER_DIRECTION = 'I' AND A.SENT_TO_BS IN( 'N','H') AND A.FILE_TYPE_INDICATOR IN(:1,:2) AND A.DATA_TYPE_INDICATOR = 'D' ORDER BY A.VPLMN_CODE,A.FILE_SEQUENCE_NUMBER";
		l_ABL_Statement               =   l_ABL_Connection.mb_createStatement(l_sql) ;
		l_ABL_Statement.mb_setString(1,l_FileTypeIndicator1) ;
		l_ABL_Statement.mb_setString(2,l_FileTypeIndicator2) ;
		l_ABL_ResultSet               =   l_ABL_Statement.mb_executeQuery()          ;
		l_ABL_ResultSet.mb_setBulkCount(100) ;
		l_ABL_ResultSet     << l_FileName       ;

		while(l_ABL_ResultSet.mb_fetch())
		{
			int records = l_ABL_ResultSet.mb_getNumArrayRows();
			for(int i = 0; i < records ; i++)
			{
				m_fileNames.push(l_FileName[i]);
			}
		}

		l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
		l_ABL_Connection.mb_terminateStatement(l_ABL_Statement);
		/****************************************************************************************/
		/* Update the File Name Status to I for the Job Created File  */

	}
	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr<<CRITICAL<<"Exception ::PM_FetchCdrFile "<<e.mb_getMessage()<<Endl;
		*m_ABL_ServicePtr<<CRITICAL<<"mb_initProcess "<<e.mb_getMessage()<<Endl;
		sprintf(gErrorMessage,"%s-%s-","Exception",e.mb_getMessage().c_str());
		UpdateProcess(7,"S",&l_ABL_Connection );
		unlink(gStMasterdata.LockFileDir.c_str()) ;
		return false;
	}
	*m_ABL_ServicePtr << INFO << "-------------------------------------------------------------------" <<Endl;
	return true;
}

bool PM_FetchCdrFile::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	return true;
}

bool PM_FetchCdrFile::mb_process(ABL_Job* &p_ABL_JobPtr)
{
	ABL_Connection  l_ABL_Connection ;
	ABL_Statement   l_ABL_Statement  ;
	ABL_ResultSet   l_ABL_ResultSet  ;

	ABL_String  l_sql ;
	// ABL_String  l_FileTypeIndicator1 ;
	// ABL_String  l_FileTypeIndicator2 ;
	ABL_String  l_FileName[10000]    ;

	long l_partnerCount;

	/* ABL_String l_SuccessFilePath=m_directoryName; */

	try
	{
		l_ABL_Connection.mb_createConnection(*m_ABL_ServicePtr);
		/* l_partnerCount       = 0  ;
		l_FileTypeIndicator1 = "" ;
		l_FileTypeIndicator2 = "" ;

		l_ABL_Connection.mb_createConnection(*m_ABL_ServicePtr);*/

		if(m_fileNames.empty())
		{
			*m_ABL_ServicePtr<<INFO<<"main : No new records in PM_TAP_FILE_SUMRY "<<Endl;
			ABL_String l_command("echo .> ");
			l_command +=m_stopFileName.c_str();
			system(l_command.c_str());				   
			return false;
		}
		else
		{
			ABL_String BsoutFile =  m_fileNames.front() ;
			p_ABL_JobPtr = new PM_Job(m_fileNames.front()); 

			/****************************************************************************************/
			/* Update the File Name Status to I for the Job Created File  */
			l_sql           =       "UPDATE PM_TAP_FILE_SUMRY SET SENT_TO_BS = 'I'WHERE(FILE_NAME=:1)";

			l_ABL_Statement =       l_ABL_Connection.mb_createStatement(l_sql);
			l_ABL_Statement.mb_setString (1,BsoutFile);
			l_ABL_Statement.mb_executeUpdate();
			l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
			l_ABL_Connection.mb_terminateStatement(l_ABL_Statement);

			l_ABL_Connection.mb_commit();
			m_fileNames.pop();
		}
	}
	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr<<CRITICAL<<"Exception :PM_FetchCdrFile:: "<<e.mb_getMessage()<<Endl;
		return false;
	}
	return true;
}

bool PM_FetchCdrFile::mb_stop()
{
	/*  std::cout<<"PM_FetchCdrFile::mb_stop"<<std::endl; */
	return true;
}

void PM_FetchCdrFile::UpdateProcess(int ProcessId,ABL_String  Status,ABL_Connection *l_ABL_ConnectionPtrs)
{
	ABL_Connection  *l_ABL_ConnectionPtr;
	ABL_Statement   l_ABL_Statement;
	ABL_ResultSet   l_ABL_ResultSet;
	ABL_String              l_sql;

	try
	{
		l_ABL_ConnectionPtr = l_ABL_ConnectionPtrs;

		if (strcmp(Status.c_str(),"R") == 0)
		{
			l_sql  ="UPDATE PM_PROCESSES SET START_STOP_FLG = 'I',PROCESS_STATUS = :1, PROCESS_LAST_START_DATE= CURRENT_DATE WHERE(PROCESS_ID=:2)";
			l_ABL_Statement         =       l_ABL_ConnectionPtr->mb_createStatement(l_sql);
			l_ABL_Statement.mb_setString (1,Status);
			l_ABL_Statement.mb_setInt(2,ProcessId);
			l_ABL_Statement.mb_executeUpdate();
			l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
			l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);
			l_ABL_ConnectionPtr->mb_commit();
			l_sql  ="INSERT INTO PM_PROCESS_STATUS (PROCESS_ID, UNIX_PID, START_TIME) VALUES (:1,:2,TO_DATE(:3,'YYYYMMDDHH24MISS'))";
			l_ABL_Statement	=	l_ABL_ConnectionPtr->mb_createStatement(l_sql);
			l_ABL_Statement.mb_setInt(1,ProcessId);
			l_ABL_Statement.mb_setInt(2,gUnixPid);
			l_ABL_Statement.mb_setString(3,gProcessStartDate);
			l_ABL_Statement.mb_executeUpdate();
			l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
			l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);
			l_ABL_ConnectionPtr->mb_commit();
			sprintf(gErrorMessage,"%s","Normal Exit");

		}
		else if (strcmp(Status.c_str(),"S") == 0)
		{
			l_sql ="UPDATE PM_PROCESSES SET START_STOP_FLG = 'I',PROCESS_STATUS = :1, PROCESS_LAST_STOP_DATE= CURRENT_DATE WHERE(PROCESS_ID=:2)";
			l_ABL_Statement         =       l_ABL_ConnectionPtr->mb_createStatement(l_sql);
			l_ABL_Statement.mb_setString (1,Status);
			l_ABL_Statement.mb_setInt(2,ProcessId);
			l_ABL_Statement.mb_executeUpdate();
			l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
			l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);
			l_ABL_ConnectionPtr->mb_commit();
			/* l_sql  ="UPDATE PM_PROCESS_STATUS SET STOP_TIME = CURRENT_DATE,ELAPSED_TIME = (CURRENT_DATE - TO_DATE(:1,'YYYYMMDDHH24MISS'))*60*60*24, REMARKS      = :2 WHERE (PROCESS_ID=:3 AND UNIX_PID = :4 AND START_TIME = TO_DATE(:5,'YYYYMMDDHH24MISS'))";  */
			l_sql  ="UPDATE PM_PROCESS_STATUS SET STOP_TIME = CURRENT_DATE,ELAPSED_TIME = (CURRENT_DATE - TO_DATE(TO_CHAR(START_TIME,'YYYYMMDDHH24MISS'),'YYYYMMDDHH24MISS'))*60*60*24, REMARKS      = :2 WHERE (PROCESS_ID=:3 AND UNIX_PID = :4)"; 
			l_ABL_Statement         =       l_ABL_ConnectionPtr->mb_createStatement(l_sql);
			/* l_ABL_Statement.mb_setString(1,gProcessStartDate); */
			l_ABL_Statement.mb_setString (1,gErrorMessage);
			l_ABL_Statement.mb_setInt(2,ProcessId);
			l_ABL_Statement.mb_setInt(3,gUnixPid);
			/* l_ABL_Statement.mb_setString(5,gProcessStartDate); */
			l_ABL_Statement.mb_executeUpdate();
			l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
			l_ABL_ConnectionPtr->mb_terminateStatement(l_ABL_Statement);
			l_ABL_ConnectionPtr->mb_commit();
		}
	}
	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr<<CRITICAL<<"UpdateProcess: Error Updating PM_PROCESSES for the ProcessId  "<<  ProcessId  <<Endl;
		*m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
	}
}

void PM_FetchCdrFile::InitialiseProcessVar()
{
	gStMasterdata.LockFileDir       = "" ;
	gStMasterdata.StopSignDir       = "" ;
	gStMasterdata.StopSignFile      = "" ;
	gStMasterdata.FileTypeIndicator = "" ;
	gStMasterdata.LockFileDir       = "" ;
	gStMasterdata.HomeDirFlag       = "" ;
	gStMasterdata.TouchFilesFlag    = "" ;
	gStMasterdata.BackupFilesFlag   = "" ;
	gStMasterdata.HomeDir           = "" ; 
	gStMasterdata.FilesDir          = "" ;
	gStMasterdata.ProcessFilesDir   = "" ; 
	gStMasterdata.ErrorFilesDir     = "" ;
	gStMasterdata.BackupFilesDir    = "" ;
	gStMasterdata.SuccessFilesDir   = "" ;
}
