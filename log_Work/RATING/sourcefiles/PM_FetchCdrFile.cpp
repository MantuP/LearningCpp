#include "PM_FetchCdrFile.h"

#define INIT_STR(vc_x) (memset(vc_x,'\0',sizeof(vc_x)));

#ifdef WIN32
#include <io.h>
#else
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif



extern "C" {EXPORT 
Base_Registry* gb_getPM_FetchCdrFile()
{
	return ( (Base_Registry*) new PM_FetchCdrFile);
}
}

/*** Default constructor for the input agent */

PM_FetchCdrFile::PM_FetchCdrFile()
{
	//
}


/***  Default destructor for the input agent */
PM_FetchCdrFile::~PM_FetchCdrFile()
{
	//
}

/*** overwrite default constructor for the input agent */
PM_FetchCdrFile::PM_FetchCdrFile(const PM_FetchCdrFile& p_copyObject)
{
	this->m_ABL_ServicePtr				=	p_copyObject.m_ABL_ServicePtr;
	this->ms_directoryName				=	p_copyObject.ms_directoryName;
	this->mq_fileNames				=	p_copyObject.mq_fileNames;
	this->ms_stopFileName				=	p_copyObject.ms_stopFileName;
	this->mobj_Masterdata				=	p_copyObject.mobj_Masterdata;
	this->mn_NumFilesToRead				=	p_copyObject.mn_NumFilesToRead;
	this->ms_FileNamePattern			=	p_copyObject.ms_FileNamePattern;
	this->mn_ProcessID				=	p_copyObject.mn_ProcessID;
        this->ms_LastAgreegated                        =       p_copyObject.ms_LastAgreegated;
}

/*deep copy constructor of input agent */

Base_Registry* PM_FetchCdrFile::mb_clone()
{
	return ( (Base_Registry*) new PM_FetchCdrFile );
}

/* copy constructor of the input agent */
ABL_Process* PM_FetchCdrFile::mb_createCopy()
{
	return ( new PM_FetchCdrFile (*this));
}

/**
**	@fn SigIntHandler
**	@brief Function to handle singals
*/
/*static void SigIntHandler(int signum)
{
		std::cout<<"Signal handled: "<<std::endl;
		
}*///SigIntHandler


/*  Init process of the input agent it will fire after the constructor and it f will file once in life time of the application. */
bool PM_FetchCdrFile::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{
	m_ABL_ServicePtr	= p_ABL_ServicePtr;
	DIR*				lo_DirPtr;
    ABL_Connection		lo_ABLConnection;
    ABL_Statement		lo_ABLStatement;
    ABL_ResultSet		lo_ABLResultSet;
    ABL_String			ls_sql;
	ABL_String			ls_LatestApplicationVersion;	
    char				*lc_LockDir;
    int					ln_ProcessCount;     
    char				lc_LockSignalDir[1024];
    char				lc_StopSignalDir[1024];
    char				lc_StopSignalfile[1024];
	char				lc_Backupflag[2];
    char*lc_lockfp		=  NULL;      

    try
    {
		ms_FileNamePattern="";
		mn_NumFilesToRead=m_ABL_ServicePtr->mb_getInt("NUM_FILES_TO_READ");
		ms_FileNamePattern=m_ABL_ServicePtr->mb_getParameterValue("FILE_NAME_PATTERN");
		if(ms_FileNamePattern=="")
			ms_FileNamePattern="*";


        /* Create the DB Connection.*/
	    lo_ABLConnection.mb_createConnection(*m_ABL_ServicePtr);

	    mn_ProcessID= m_ABL_ServicePtr->mb_getInt("PROCESS_ID");
		
             ls_sql="select to_char(sysdate,'YYYYMMDDHH24MISS') from dual";
                        lo_ABLStatement   =   lo_ABLConnection.mb_createStatement(ls_sql) ;
                        lo_ABLResultSet   =   lo_ABLStatement.mb_executeQuery();
                        if(lo_ABLResultSet.mb_fetch())
                        ms_LastAgreegated    =   lo_ABLResultSet.mb_getString(1) ;



                        lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet)       ;
                        lo_ABLConnection.mb_terminateStatement(lo_ABLStatement)  ;

                        p_ABL_AgentCommunicatorPtr->mb_setParameter("ToAgreegate",ms_LastAgreegated.c_str());




		/* Get Latest Application Version from PM_APP_RELEASE Table and  log it */

			 /* Check the entry in PM_PROCESSES Table.*/
			 ls_LatestApplicationVersion="";
			ls_sql="select nvl(APP_VERSION_NO,0)||'.'||nvl(APP_RELEASE_NO,0)||'.'||nvl(APP_REVISION_NO,0) from PM_APP_RELEASES where is_latest='Y'";
			lo_ABLStatement   =   lo_ABLConnection.mb_createStatement(ls_sql) ;
			lo_ABLResultSet   =   lo_ABLStatement.mb_executeQuery();
			if(lo_ABLResultSet.mb_fetch())
			ls_LatestApplicationVersion    =   lo_ABLResultSet.mb_getString(1) ;

			lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet)       ;
			lo_ABLConnection.mb_terminateStatement(lo_ABLStatement)  ;
			if(ls_LatestApplicationVersion=="")
			{
				*m_ABL_ServicePtr<<DEBUG<<"There is no Latest Application Version in PM_APP_RELEASE kindly check it :"<< mn_ProcessID<<Endl;
			}
			else
			{
				*m_ABL_ServicePtr<<DEBUG<<"Latest Application Version is:"<< ls_LatestApplicationVersion<<Endl;
			}


	    *m_ABL_ServicePtr<<DEBUG<<"Process id :"<< mn_ProcessID<<Endl;
        InitialiseProcessVar()   ;
        INIT_STR(lc_StopSignalDir)  ;            
        INIT_STR(lc_LockSignalDir)  ;
	*m_ABL_ServicePtr<<DEBUG<<"before select: 142 4.4release"<< mn_ProcessID<<Endl;
        /* Check the entry in PM_PROCESSES Table.*/
        ls_sql="SELECT COUNT(*) FROM PM_PROCESSES WHERE PROCESS_ID =:1";
	*m_ABL_ServicePtr<<DEBUG<<"after select: 145 4.4release"<< mn_ProcessID<<Endl;
        lo_ABLStatement   =   lo_ABLConnection.mb_createStatement(ls_sql) ;
	    lo_ABLStatement.mb_setDouble(1,mn_ProcessID);
        lo_ABLResultSet   =   lo_ABLStatement.mb_executeQuery();
        if(lo_ABLResultSet.mb_fetch())
        ln_ProcessCount    =   lo_ABLResultSet.mb_getInt(1) ;
        lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet)       ;
        lo_ABLConnection.mb_terminateStatement(lo_ABLStatement)  ;
        if(ln_ProcessCount == 0)
        {
           *m_ABL_ServicePtr << DEBUG << "There are no Details in PM_PROCESSES Table.Exiting from the Process" << Endl;
           *m_ABL_ServicePtr << DEBUG << "-------------------------------------------------------------------" << Endl;		
           return false ;
        }

        /* Get Lock File and Stop File directory paths from PM_PROCESSES Table and Validate them.*/   
        ls_sql="SELECT NVL(TRIM(LOCK_FILE_PATH),' '),NVL(TRIM(STOP_SIGNAL_DIR),' '),NVL(TRIM(STOP_SIGNAL_FILE),' ') FROM PM_PROCESSES WHERE PROCESS_ID =:1";
	lo_ABLStatement					 =   lo_ABLConnection.mb_createStatement(ls_sql) ;
	    lo_ABLStatement.mb_setDouble(1,mn_ProcessID);
        lo_ABLResultSet					 =   lo_ABLStatement.mb_executeQuery()          ;
        lo_ABLResultSet.mb_fetch();
        mobj_Masterdata.ms_lockfiledir        =   lo_ABLResultSet.mb_getString(1) ;
        mobj_Masterdata.ms_stopSignDir        =   lo_ABLResultSet.mb_getString(2) ;
        mobj_Masterdata.ms_stopSignFile       =   lo_ABLResultSet.mb_getString(3) ;  
        lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet)       ;
        lo_ABLConnection.mb_terminateStatement(lo_ABLStatement)  ;
        sprintf(lc_StopSignalDir,"%s",mobj_Masterdata.ms_stopSignDir.c_str()) ;
	    sprintf(lc_LockSignalDir,"%s",mobj_Masterdata.ms_lockfiledir.c_str()) ;  
        /* Form  Stop signal directory.*/
        if(lc_StopSignalDir[strlen(lc_StopSignalDir)-1] == '/')
        {
           lc_StopSignalDir[strlen(lc_StopSignalDir)-1] = '\0';
        }
        sprintf(lc_StopSignalDir,"%s/",lc_StopSignalDir);
        lc_LockDir=lc_LockSignalDir;
        lc_lockfp= dirname (lc_LockDir);          
        int ln_LockDir=0;
        ln_LockDir=access(lc_lockfp,F_OK);
        if (ln_LockDir!=0)
        {
            *m_ABL_ServicePtr<< DEBUG << "Lock signal dir is not valid"<< lc_lockfp  << Endl; 	      
            *m_ABL_ServicePtr<< DEBUG << "Main : Exiting from the Process" << Endl;
            *m_ABL_ServicePtr<< DEBUG << "-------------------------------------------------------------------" <<Endl;
	        return false;
         }

         int ln_RatingRunning = 0;
         ln_RatingRunning=access(mobj_Masterdata.ms_lockfiledir.c_str(),F_OK);
         if (ln_RatingRunning == 0)
         {
             *m_ABL_ServicePtr<< DEBUG << "Lock signal found. " << mobj_Masterdata.ms_lockfiledir <<" lock status : "<< ln_RatingRunning << Endl;
             *m_ABL_ServicePtr<< DEBUG << "Process is Already Running..." << Endl;
             *m_ABL_ServicePtr<< DEBUG << "-------------------------------------------------------------------" << Endl;
		     return false;
         }

         /* Create a Lock file for the process */ 
         ABL_String ls_command("echo .> ");
         ls_command +=mobj_Masterdata.ms_lockfiledir;
		 system(ls_command.c_str());
         UpdateProcess(mn_ProcessID,"R",&lo_ABLConnection );   
         /* Check for valid Stop signal directory path.*/
         if(strcmp(lc_StopSignalDir," ") == 0)
         {
             *m_ABL_ServicePtr<< DEBUG << "ERROR : Stop signal dir in PM_PROCESSES table is null"<< Endl;
             *m_ABL_ServicePtr<< DEBUG << "Main : Exiting from the Process" << Endl;
             *m_ABL_ServicePtr<< DEBUG << "-------------------------------------------------------------------"<< Endl;
             return false;
         }

	    lo_DirPtr = NULL;
        lo_DirPtr = opendir(lc_StopSignalDir);

        /* Check if the Stop signal directory specified is valid.*/
        if(!lo_DirPtr)
        {
             *m_ABL_ServicePtr << DEBUG <<  "ERROR : Invalid Stop signal directory Specified in PM_PROCESSES table" << Endl;
             *m_ABL_ServicePtr << DEBUG <<  "Stop Signal Directory: " << lc_StopSignalDir << Endl;
             *m_ABL_ServicePtr << DEBUG <<  "Main : Exiting from the Process" << Endl;
             *m_ABL_ServicePtr << DEBUG <<  "-------------------------------------------------------------------" << Endl;
             return false ;
        }

        /* Close the Directory.*/
        closedir(lo_DirPtr);
        lo_DirPtr = NULL;               
        ln_ProcessCount =0; 
        lo_ABLConnection.mb_createConnection(*m_ABL_ServicePtr);
        ls_sql="SELECT COUNT(*) FROM PM_PROCESS_DETAILS WHERE PROCESS_ID =:1";
        lo_ABLStatement   =   lo_ABLConnection.mb_createStatement(ls_sql) ;
	    lo_ABLStatement.mb_setDouble(1,mn_ProcessID);
        lo_ABLResultSet   =   lo_ABLStatement.mb_executeQuery()          ;
        lo_ABLResultSet.mb_fetch();
        ln_ProcessCount    =   lo_ABLResultSet.mb_getInt(1) ;
        lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet)       ;
        lo_ABLConnection.mb_terminateStatement(lo_ABLStatement)  ;
        if(ln_ProcessCount == 0)
        {
             *m_ABL_ServicePtr<< DEBUG << "There are no Details in PM_PROCESS_DETAILS Table. Exiting from the Process" << Endl;
             *m_ABL_ServicePtr<< DEBUG << "-------------------------------------------------------------------" << Endl;
             return false ;
        }

		/* Fetching flags and directories paths from pm_process_details table.*/

  	   // ls_sql="SELECT NVL(TRIM(HOME_DIR_FLG),' '),NVL(TRIM(TOUCHFILES_FLG),' '),NVL(TRIM(BACKUP_FILES_FLG),' '),NVL(TRIM(HOME_DIR),' '),NVL(TRIM(FILES_DIR),' '),NVL(TRIM(PROCESS_FILES_DIR),' '),NVL(TRIM(ERROR_FILES_DIR),' '),NVL(TRIM(BACKUP_FILES_DIR),' '),NVL(TRIM(SUCCESS_FILES_DIR),' ') FROM PM_PROCESS_DETAILS WHERE PROCESS_ID=:1";
	   ls_sql="SELECT NVL(TRIM(HOME_DIR_FLG),' '),NVL(TRIM(TOUCHFILES_FLG),' '),NVL(TRIM(BACKUP_FILES_FLG),' '),NVL(TRIM(HOME_DIR),' '),decode(HOME_DIR_FLG,'Y',TRIM(HOME_DIR)||TRIM(FILES_DIR),TRIM(FILES_DIR)) AS FILES_DIR,decode(HOME_DIR_FLG,'Y',TRIM(HOME_DIR)||TRIM(PROCESS_FILES_DIR),TRIM(PROCESS_FILES_DIR)) AS PROCESS_FILES_DIR,decode(HOME_DIR_FLG,'Y',TRIM(HOME_DIR)||TRIM(ERROR_FILES_DIR),TRIM(ERROR_FILES_DIR)) AS ERROR_FILES_DIR,decode(HOME_DIR_FLG,'Y',TRIM(HOME_DIR)||TRIM(BACKUP_FILES_DIR),TRIM(BACKUP_FILES_DIR))AS BACKUP_FILES_DIR,decode(HOME_DIR_FLG,'Y',TRIM(HOME_DIR)||TRIM(SUCCESS_FILES_DIR),TRIM(SUCCESS_FILES_DIR)) AS SUCCESS_FILES_DIR FROM PM_PROCESS_DETAILS WHERE PROCESS_ID=:1";
	     
	    lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_sql);
        lo_ABLStatement.mb_setDouble(1,mn_ProcessID);
	    lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
	    lo_ABLResultSet.mb_fetch();	

	    mobj_Masterdata.ms_homeDirFlag	     =   lo_ABLResultSet.mb_getString(1);
	    mobj_Masterdata.ms_touchFilesFlag     =   lo_ABLResultSet.mb_getString(2);
	    mobj_Masterdata.ms_backupFilesFlag	 =   lo_ABLResultSet.mb_getString(3);
	    mobj_Masterdata.ms_homeDir			 =   lo_ABLResultSet.mb_getString(4);
	    mobj_Masterdata.ms_filesDir			 =	 lo_ABLResultSet.mb_getString(5);
        mobj_Masterdata.ms_processFilesDir	 =	 lo_ABLResultSet.mb_getString(6);
	    mobj_Masterdata.ms_errorFilesDir		 =	 lo_ABLResultSet.mb_getString(7);
	    mobj_Masterdata.ms_backupFilesDir	 =	 lo_ABLResultSet.mb_getString(8);
	    mobj_Masterdata.ms_successFilesDir	 =	 lo_ABLResultSet.mb_getString(9);
	    lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
	    lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);

	   

		sprintf(lc_Backupflag,"%s",mobj_Masterdata.ms_backupFilesFlag.c_str()) ; 			
        //sprintf(HomeDirectory,"%s",mobj_Masterdata.ms_homeDir.c_str()) ; 
        /* Check Home directory flag('Y' or 'N') and select Directories path based on Home directory flag.*/

        if (strcmp(mobj_Masterdata.ms_homeDirFlag.c_str(),"Y") == 0)
        {
          	if(strcmp(mobj_Masterdata.ms_homeDir.c_str()," ") == 0)
           	{
           		*m_ABL_ServicePtr<< DEBUG << "ERROR : Home directory in PM_PROCESS_DETAILS table is null" << Endl;
           		*m_ABL_ServicePtr<< DEBUG << "Main : Exiting from the Process" << Endl;
           		*m_ABL_ServicePtr<< DEBUG << "-------------------------------------------------------------------" << Endl;
              	return false;
            }

		}
            lo_DirPtr = NULL;
            lo_DirPtr = opendir(mobj_Masterdata.ms_homeDir.c_str());

            /* Check if the Home directory specified is valid.*/
           	if(!lo_DirPtr)
            {
            	*m_ABL_ServicePtr << DEBUG <<  "ERROR : Home directory specified in PM_PROCESS_DETAILS table is not valid :" << mobj_Masterdata.ms_homeDir << Endl;
            	*m_ABL_ServicePtr << DEBUG <<  "Main : Exiting from the Process" << Endl;
            	*m_ABL_ServicePtr << DEBUG <<  "-------------------------------------------------------------------" << Endl;
            	return false ;
            }
            /* Close the Directory.*/
            closedir(lo_DirPtr);
           	lo_DirPtr = NULL;

		/* Check if the Files directory is specified in the table or not.*/
        if(strcmp(mobj_Masterdata.ms_filesDir.c_str()," ") == 0)
        {
            *m_ABL_ServicePtr << DEBUG << "ERROR : Files dir in PM_PROCESS_DETAILS table is null" <<Endl;
            *m_ABL_ServicePtr << DEBUG << "Main : Exiting from the Process" <<Endl;
            *m_ABL_ServicePtr << DEBUG << "-------------------------------------------------------------------" <<Endl;
            return false;
         }

         lo_DirPtr = NULL;
         lo_DirPtr = opendir(mobj_Masterdata.ms_filesDir.c_str());

         /* Check if the Files directory specified is valid.*/
         if(!lo_DirPtr)
         {
			*m_ABL_ServicePtr << DEBUG << "ERROR : Invalid Files directory specified in PM_PROCESS_DETAILS table :" << mobj_Masterdata.ms_filesDir << Endl;
            *m_ABL_ServicePtr << DEBUG << "Main : Exiting from the Process" << Endl;
            *m_ABL_ServicePtr << DEBUG << "-------------------------------------------------------------------" << Endl;
            return false ;
         }

         /* Close the Directory */
         closedir(lo_DirPtr);
         lo_DirPtr = NULL;   
    
         *m_ABL_ServicePtr<<DEBUG<<"Files dir : "<< mobj_Masterdata.ms_filesDir << Endl;
		 
		  /* Check if the Prcessed files directory specified in the table or not.*/
         if(strcmp(mobj_Masterdata.ms_processFilesDir.c_str()," ") == 0)
            {
               *m_ABL_ServicePtr << DEBUG << "ERROR : Processed files directory specified in PM_PROCESS_DETAILS table is null" << Endl;
               *m_ABL_ServicePtr << DEBUG << "Main : Exiting from the Process" << Endl;
               *m_ABL_ServicePtr << DEBUG << "-------------------------------------------------------------------" << Endl;
               return false;
            }

            lo_DirPtr = NULL;
            lo_DirPtr = opendir(mobj_Masterdata.ms_processFilesDir.c_str());

            /* Check if the Prcessed files directory specified is valid.*/
            if(!lo_DirPtr)
            {
               *m_ABL_ServicePtr << DEBUG << "ERROR : Invalid Processed files directory specified in PM_PROCESS_DETAILS table " << mobj_Masterdata.ms_processFilesDir << Endl;
               *m_ABL_ServicePtr << DEBUG << "Main : Exiting from the Process" << Endl;
               *m_ABL_ServicePtr << DEBUG << "-------------------------------------------------------------------" << Endl;
               return false ;
            }

            /* Close the Directory.*/
            closedir(lo_DirPtr);
            lo_DirPtr = NULL;       
            *m_ABL_ServicePtr << DEBUG << "Processed Files dir : " << mobj_Masterdata.ms_processFilesDir << Endl;
            if(strcmp(mobj_Masterdata.ms_errorFilesDir.c_str()," ") == 0)
            {
               *m_ABL_ServicePtr << DEBUG << "ERROR : Error files directory specified in PM_PROCESS_DETAILS table is null" << Endl;
               *m_ABL_ServicePtr << DEBUG << "Main : Exiting from the Process" << Endl;
               *m_ABL_ServicePtr << DEBUG << "-------------------------------------------------------------------" << Endl;
               return false;
            }

            lo_DirPtr = NULL;
            lo_DirPtr = opendir(mobj_Masterdata.ms_errorFilesDir.c_str());

            /* Check if the Directory specified is Valid.*/
            if(!lo_DirPtr)
            {
               *m_ABL_ServicePtr << DEBUG << "ERROR : Invalid Error Files directory specified in PM_PROCESS_DETAILS table " << mobj_Masterdata.ms_errorFilesDir << Endl;
               *m_ABL_ServicePtr << DEBUG << "main : Exiting from the Process" << Endl;
               *m_ABL_ServicePtr << DEBUG << "-------------------------------------------------------------------" << Endl;
               return false ;
            }

            /* Close the Directory.*/
            closedir(lo_DirPtr);
            lo_DirPtr = NULL;       
            *m_ABL_ServicePtr << DEBUG << "Error Files dir : " << mobj_Masterdata.ms_errorFilesDir << Endl;

            if(strcmp(mobj_Masterdata.ms_successFilesDir.c_str()," ") == 0)
            {
               *m_ABL_ServicePtr << DEBUG << "ERROR : Success Files directory specified in PM_PROCESS_DETAILS table is null" << Endl;
               *m_ABL_ServicePtr << DEBUG << "Main : Exiting from the Process" << Endl;
               *m_ABL_ServicePtr << DEBUG << "-------------------------------------------------------------------" << Endl;
               return false;
            }

            lo_DirPtr = NULL;
            lo_DirPtr = opendir(mobj_Masterdata.ms_successFilesDir.c_str());

            /* Check if the Success files directory specified is valid. */
            if(!lo_DirPtr)
            {
				*m_ABL_ServicePtr << DEBUG << "ERROR : Invalid Success Files directory Specified in PM_PROCESS_DETAILS table :" << mobj_Masterdata.ms_successFilesDir << Endl;
				*m_ABL_ServicePtr << DEBUG << "Main : Exiting from the Process" << Endl;
                *m_ABL_ServicePtr << DEBUG << "-------------------------------------------------------------------" << Endl;
				return false ;
            }

			char filename[200];
            INIT_STR(filename);
            INIT_STR(lc_StopSignalfile);
		    sprintf(lc_StopSignalfile,"%s",mobj_Masterdata.ms_stopSignDir.c_str());               
			strcat(lc_StopSignalfile,mobj_Masterdata.ms_stopSignFile.c_str());
			
			/* Close the Directory. */
            closedir(lo_DirPtr);
            lo_DirPtr = NULL;       
            *m_ABL_ServicePtr<<DEBUG<<"Success Files dir : "<< mobj_Masterdata.ms_successFilesDir << Endl;  
			ms_stopFileName=lc_StopSignalfile;
			p_ABL_AgentCommunicatorPtr->mb_setParameter("STOP_FILE",lc_StopSignalfile);		   
		    p_ABL_AgentCommunicatorPtr->mb_setParameter("CDR_FOLDER",mobj_Masterdata.ms_successFilesDir.c_str());			
			p_ABL_AgentCommunicatorPtr->mb_setParameter("FilesDir",mobj_Masterdata.ms_filesDir.c_str());
			p_ABL_AgentCommunicatorPtr->mb_setParameter("ProcessFilesDir",mobj_Masterdata.ms_processFilesDir.c_str());
			p_ABL_AgentCommunicatorPtr->mb_setParameter("ErrorFilesDir",mobj_Masterdata.ms_errorFilesDir.c_str());
			p_ABL_AgentCommunicatorPtr->mb_setParameter("BackUpFilesDir",mobj_Masterdata.ms_backupFilesDir.c_str());
			p_ABL_AgentCommunicatorPtr->mb_setParameter("LockFile",mobj_Masterdata.ms_lockfiledir.c_str());
			p_ABL_AgentCommunicatorPtr->mb_setParameter("PROCESS_ID",m_ABL_ServicePtr->mb_getParameterValue("PROCESS_ID")); 
			p_ABL_AgentCommunicatorPtr->mb_setParameter("BackupFlag",mobj_Masterdata.ms_backupFilesFlag.c_str());
			ms_directoryName=mobj_Masterdata.ms_successFilesDir;
			
    }
    catch(ABL_Exception &e)
    {
        *m_ABL_ServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;
        UpdateProcess(mn_ProcessID,"S",&lo_ABLConnection ); 
        return false;
     }
	catch(...)
	{
		*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}	

     return true;     
}

/* loading the cache  function of the input agent */

bool PM_FetchCdrFile::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	return true;
}

// 
bool PM_FetchCdrFile::mb_process(ABL_Job* &p_ABL_JobPtr)
{
	
	try
	{
		if(mq_fileNames.empty())
		{
			while(!fnReadFilesFfromFolder())
			{		
				sleep(1);
				std::ifstream inFile;  
				inFile.open(ms_stopFileName.c_str(),std::ios::in);
				if (inFile.is_open()) 
				{
					inFile.close();
					return false ;
				}	
			}
				
		}
		ABL_String ls_SuccessFilePath=ms_directoryName;	
		ls_SuccessFilePath+=mq_fileNames.front();
		p_ABL_JobPtr = new PM_Job(mq_fileNames.front());
		unlink(ls_SuccessFilePath.c_str());
		mq_fileNames.pop();	
	}
	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;
		return false;
	} 
	catch(...)
	{
		*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}	
	

	return true;
}

bool PM_FetchCdrFile::mb_stop()
{

	if(mq_fileNames.empty())
	{
		try
		{

			ABL_Connection	lo_ABLConnection;
			lo_ABLConnection.mb_createConnection(*m_ABL_ServicePtr);
			UpdateProcess(mn_ProcessID,"S",&lo_ABLConnection ); 
			unlink(ms_stopFileName.c_str());
			unlink(mobj_Masterdata.ms_lockfiledir.c_str());
		}
		catch(ABL_Exception &e)
		{
			*m_ABL_ServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;
			return false;
		}
		catch(...)
		{
			*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
			return false;
		}	

	}	
	
	return true;
}
bool PM_FetchCdrFile::fnReadFilesFfromFolder()
{
	
	#ifndef WIN32

	ABL_DirectoryReader lo_dirptr;
   ABL_SearchOptions lo_searoptn;
	ABL_String ls_tempbuf;
	char  *lc_pstr;
	int ln_index;
	ABL_String ls_ParentDir;
	ABL_String ls_FilePath;
	struct dirent *lo_dp = NULL;
	struct stat lo_statbuf;
	int ln_fil_cnt=0;
	std::vector<std::string> la_InputFiles;

	lo_searoptn.mb_setSortCriteria('C','A');
	lo_searoptn.mb_setPatternCriteria(ms_FileNamePattern.c_str());

	if (ms_directoryName.mb_empty())
	{
		return true;
	} 
	
	lo_dirptr.mb_listDir( la_InputFiles,ms_directoryName.c_str(),lo_searoptn,false,mn_NumFilesToRead);

        int ln_i;

	//*m_ABL_ServicePtr<<DEBUG<<"After reading the files folder:"<<Endl;
	for( ln_i=0;ln_i<la_InputFiles.size();ln_i++)
     {
			mq_fileNames.push(la_InputFiles[ln_i]);              

     }

	la_InputFiles.clear();
	if(mq_fileNames.size()>0)	
		return true;
	else
		return false;
#else 
	struct _finddata_t fileinfo;
	ABL_String filespec;
//	int ctr,fileexists;
	int handle=0;

	filespec =  ms_directoryName;
	
	filespec += "*";


	if((handle=_findfirst(filespec.c_str(),&fileinfo)) == -1)
		return false;
	if(_findnext(handle,&fileinfo))
		return false;

	while( !_findnext(handle,&fileinfo))
	{
		mq_fileNames.push(ABL_String(fileinfo.name));
	}

	_findclose(handle);

	if (mq_fileNames.size()>0)
	{
		return true;
	}
	else
	{
		return false;
	}
	
#endif

}

void PM_FetchCdrFile:: UpdateProcess(int ProcessId,ABL_String  Status,ABL_Connection *l_ABL_ConnectionPtrs)
{
	ABL_Connection	*lo_ABLConnectionPtr;
	ABL_Statement	lo_ABLStatement;
	ABL_ResultSet	lo_ABLResultSet;
	ABL_String		ls_sql;   
   try
   {
		lo_ABLConnectionPtr = l_ABL_ConnectionPtrs;
		ls_sql		        =	"UPDATE PM_PROCESSES SET START_STOP_FLG = 'I',PROCESS_STATUS = :1,  PROCESS_LAST_START_DATE= SYSDATE WHERE(PROCESS_ID=:2)";			
		lo_ABLStatement     =	lo_ABLConnectionPtr->mb_createStatement(ls_sql);	
		lo_ABLStatement.mb_setString (1,Status);
		lo_ABLStatement.mb_setInt(2,ProcessId);
		lo_ABLStatement.mb_executeUpdate();
		lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement);
		lo_ABLConnectionPtr->mb_commit();
   }
   catch(ABL_Exception &e)
   {
		*m_ABL_ServicePtr << CRITICAL << "Main: Error while updating PM_PROCESSES table for the ProcessId : " << ProcessId << Endl;
		*m_ABL_ServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;	
   }
	catch(...)
	{
		*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;

	}	
 }

void PM_FetchCdrFile::InitialiseProcessVar()
{
      mobj_Masterdata.ms_lockfiledir       =  "" ;
      mobj_Masterdata.ms_stopSignDir       =  "" ;
      mobj_Masterdata.ms_stopSignFile      =  "" ;
      mobj_Masterdata.ms_homeDirFlag	      =  "" ;		
	  mobj_Masterdata.ms_touchFilesFlag    =  "" ;		
      mobj_Masterdata.ms_backupFilesFlag   =  "" ;		
      mobj_Masterdata.ms_homeDir	          =  "" ;		
	  mobj_Masterdata.ms_filesDir	      =  "" ;		
	  mobj_Masterdata.ms_processFilesDir   =  "" ;		
	  mobj_Masterdata.ms_errorFilesDir	  =  "" ;	  	
	  mobj_Masterdata.ms_successFilesDir   =  "" ;		  
}
