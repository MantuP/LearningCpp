#include "PM_RerateInputAgent.h"
#define INIT_STR(vc_x) (memset(vc_x,'\0',sizeof(vc_x)));

#ifdef WIN32
#include <io.h>
#else
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

extern "C" {EXPORT 
Base_Registry* gb_getPM_RerateInputAgent()
{
	return ( (Base_Registry*) new PM_RerateInputAgent);
}
}

/*** Default constructor for the input agent */

PM_RerateInputAgent::PM_RerateInputAgent()
{
	//
}


/***  Default destructor for the input agent */
PM_RerateInputAgent::~PM_RerateInputAgent()
{
	//
}

/*** overwrite default constructor for the input agent */
PM_RerateInputAgent::PM_RerateInputAgent(const PM_RerateInputAgent& p_copyObject)
{
	this->m_ABL_ServicePtr							=	p_copyObject.m_ABL_ServicePtr;
	this->ms_directoryName							=	p_copyObject.ms_directoryName;
	this->mq_fileNames								=	p_copyObject.mq_fileNames;
	this->ms_stopFileName							=	p_copyObject.ms_stopFileName;
	this->mobj_Masterdata							=	p_copyObject.mobj_Masterdata;
	this->mn_NumFilesToRead							=	p_copyObject.mn_NumFilesToRead;
	this->ms_FileNamePattern						=	p_copyObject.ms_FileNamePattern;
	this->mn_ProcessID								=	p_copyObject.mn_ProcessID;
	this->mn_total_files_In_rerate_reprice_seq_no	=	p_copyObject.mn_total_files_In_rerate_reprice_seq_no;

}

/*deep copy constructor of input agent */

Base_Registry* PM_RerateInputAgent::mb_clone()
{
	return ( (Base_Registry*) new PM_RerateInputAgent );
}

/* copy constructor of the input agent */
ABL_Process* PM_RerateInputAgent::mb_createCopy()
{
	return ( new PM_RerateInputAgent (*this));
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
bool PM_RerateInputAgent::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
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
    char*lc_lockfp		=  NULL;      
	bool lb_ProcessExists = false;
	
    try
    {
        /* Create the DB Connection.*/
	    lo_ABLConnection.mb_createConnection(*m_ABL_ServicePtr);

	    mn_ProcessID= m_ABL_ServicePtr->mb_getInt("PROCESS_ID");
		

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
        /* Check the entry in PM_PROCESSES Table.*/
        ls_sql="SELECT COUNT(*) FROM PM_PROCESSES WHERE PROCESS_ID =:1";
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
		/*while (lo_ABLResultSet.mb_fetch())
		{
			lb_ProcessExists = true;

		}*/
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
      

			char filename[200];
            INIT_STR(filename);
            INIT_STR(lc_StopSignalfile);
		    sprintf(lc_StopSignalfile,"%s",mobj_Masterdata.ms_stopSignDir.c_str());               
			strcat(lc_StopSignalfile,mobj_Masterdata.ms_stopSignFile.c_str());
			ms_stopFileName=lc_StopSignalfile;
			p_ABL_AgentCommunicatorPtr->mb_setParameter("STOP_FILE",lc_StopSignalfile);		   
			p_ABL_AgentCommunicatorPtr->mb_setParameter("LockFile",mobj_Masterdata.ms_lockfiledir.c_str());
			p_ABL_AgentCommunicatorPtr->mb_setParameter("PROCESS_ID",m_ABL_ServicePtr->mb_getParameterValue("PROCESS_ID")); 

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

bool PM_RerateInputAgent::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	return true;
}

// 
bool PM_RerateInputAgent::mb_process(ABL_Job* &p_ABL_JobPtr)
{
	//ABL_String ls_FileName;
	ABL_String ls_RerateRequest;

	try
	{
		if(mq_fileNames.empty())
		{
			while(!fnReadRerateData())
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

		if(!mq_fileNames.empty())
		{
			ls_RerateRequest="";
			ls_RerateRequest=mq_fileNames.front();
			// Create a job for the rerate sequence number
			p_ABL_JobPtr = new PM_Job(ls_RerateRequest);
			mq_fileNames.pop();					
			
			PM_Job* lo_PMJobPtr = (PM_Job*)p_ABL_JobPtr;
			lo_PMJobPtr->gn_Files_In_Rerate_Reprice_seq_no=	mn_total_files_In_rerate_reprice_seq_no;
			if(mq_fileNames.size()+1==mn_total_files_In_rerate_reprice_seq_no)
			{
				if(!UpdatePMRepriceLog(ls_RerateRequest))
				return false;
			}

		}

		
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

bool PM_RerateInputAgent::UpdatePMRepriceLog(ABL_String is_RerateRequest)
{	
	ABL_String	ls_sql;

	try
	{

			std::vector<std::string> lv_tokens;
			tokenize(is_RerateRequest.c_str(),lv_tokens,"|");

			unsigned int ln_RerateSeqNo=atoi(lv_tokens[0].c_str());
			ABL_Connection	lo_ABLConnection;
			ABL_Statement	lo_ABLStatement;
			ls_sql="";
			ls_sql="update pm_reprice_log SET  STATUS='INPRS' WHERE REPRICE_SEQ_NO=:1 AND status = 'NEW' AND process_type = 'R' ";
			lo_ABLConnection.mb_createConnection(*m_ABL_ServicePtr);
			lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_sql); 
			lo_ABLStatement.mb_setInt (1,ln_RerateSeqNo);
			lo_ABLStatement.mb_executeUpdate();
			lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);
			lo_ABLConnection.mb_commit();

	}
	catch(ABL_Exception &e)
	{
		std::cout<<"ABL error: "<<std::endl;
		*m_ABL_ServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;
		return false;
	} 
	catch(...)
	{
		std::cout<<"General  error came : "<<std::endl;
		*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}	

	return true;

}

bool PM_RerateInputAgent::mb_stop()
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
			return true;
		}
		catch(...)
		{
			*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
			return true;
		}
	}

	
	return true;
}

bool PM_RerateInputAgent::fnReadRerateData()
{
	ABL_Connection	lo_ABLConnection;
	ABL_Statement	lo_ABLStatement;
	ABL_ResultSet	lo_ABLResultSet;

	ABL_String		ls_sql;	

	unsigned int	ln_RerateSequenceNo;
	unsigned int	ln_TotalSummariesSubmitted;
	unsigned int	ln_TotalCdrsSubmitted;
	ABL_String		ls_ROWID;
	ABL_DbDate		ld_FirstCalledDate;
	ABL_DbDate		ld_LastCalledDate;
	ABL_String		ls_AgreementType;
	ABL_String		ls_SourceType;
	ABL_String		ls_Backupoldcdrs;

	ABL_String		ls_ErrCode;
	ABL_String		ls_ErrMesg;
	ABL_String		ls_RerateLevel;
	ABL_String		ls_TempRerateSequenceNo;


	int ln_TotalFiles = 0;
	int ln_CdrCount = 0;
	int ln_FileCount = 0;
	ABL_String			ls_FileID;
	ABL_String			ls_RerateSeqNo_FileID;
	try
	{
		mn_total_files_In_rerate_reprice_seq_no=0;
		lo_ABLConnection.mb_createConnection(*m_ABL_ServicePtr);
		ls_sql="SELECT reprice_seq_no, total_cdrs_submitted,to_date(to_char(first_call_date,'yyyymmddhh24miss'),'yyyymmddhh24miss') as first_call_date, to_date(to_char(last_call_date,'yyyymmddhh24miss'),'yyyymmddhh24miss') as last_call_date, agreement_type, ROWID,NVL(SOURCE_TYPE,'R') FROM pm_reprice_log  WHERE status = 'NEW' AND process_type = 'R' and rownum=1";
        lo_ABLStatement					 =   lo_ABLConnection.mb_createStatement(ls_sql) ;
        lo_ABLResultSet					 =   lo_ABLStatement.mb_executeQuery()          ;
        while(lo_ABLResultSet.mb_fetch())
		{
			ln_RerateSequenceNo=0;
			ln_TotalSummariesSubmitted=0;
			ln_TotalCdrsSubmitted=0;

			ln_RerateSequenceNo		=   lo_ABLResultSet.mb_getInt64(1) ;
			ln_TotalCdrsSubmitted		=   lo_ABLResultSet.mb_getInt64(2) ;

			ld_FirstCalledDate			=	lo_ABLResultSet.mb_getDate(3) ;
			ld_LastCalledDate			=	lo_ABLResultSet.mb_getDate(4) ;
			ls_AgreementType			=   lo_ABLResultSet.mb_getString(5) ;
			ls_ROWID					=	lo_ABLResultSet.mb_getString(6) ;
			ls_SourceType               =   lo_ABLResultSet.mb_getString(7) ;
			 // check mandatory parameters & other validations
		
                       if (ls_AgreementType=="")
				{
					*m_ABL_ServicePtr << CRITICAL<<"Rerate Seq=> " << ln_RerateSequenceNo << ": Agreement Type can not be null" << Endl;
					continue;
				}

			if (ld_FirstCalledDate.mb_toString(YYYYMMDDHH24MISS) =="")
				{
					*m_ABL_ServicePtr << DEBUG<<"Rerate Seq=> " << ln_RerateSequenceNo << ": First Call Date cannot be null" << Endl;
					continue;
				}
				/* Set End date to sysdate if null */
				ABL_Date ld_tempFirstCalledDate=ld_FirstCalledDate;
				ABL_Date ld_tempLastCalledDate=ld_LastCalledDate;

			if (ld_LastCalledDate.mb_toString(YYYYMMDDHH24MISS) =="")
				{
					*m_ABL_ServicePtr << DEBUG<<"Rerate Seq=> " << ln_RerateSequenceNo << ": End Call Date cannot be null" << Endl;
					continue;
					ABL_Date ld_LastCallDate;
					ld_LastCallDate.mb_fromSysDate(); 
					ld_LastCalledDate=ld_LastCallDate;

				}

			  if (ld_tempFirstCalledDate > ld_tempLastCalledDate)
				{
					*m_ABL_ServicePtr << DEBUG<<"Rerate Seq no: "<<ln_RerateSequenceNo<<" :Error - first call date "<<ld_FirstCalledDate.mb_toText(YYYYMMDDHH24MISS)<<" > than last call date "<<ld_LastCalledDate.mb_toText(YYYYMMDDHH24MISS)<< Endl;
					continue;
				}

				ln_TotalFiles = 0;
				ln_CdrCount = 0;
				ln_FileCount = 0;	
				

				ls_TempRerateSequenceNo="";
				ls_TempRerateSequenceNo.mb_fromInt64(ln_RerateSequenceNo);
					
				//fetch list of files that should be repriced.
				ABL_DbDate ld_StartDate; 
				ABL_Date ld_StDate;
				ld_StDate.mb_fromSysDate();
				ld_StartDate=ld_StDate;

				//start the repricing
				ls_ErrMesg = "..Fetch distinct files to rerate for Rerate seq no => ";
				ls_ErrMesg+=ls_TempRerateSequenceNo;
				ls_ErrMesg+=":Start date => ";
				ls_ErrMesg+=ld_StartDate.mb_toString(YYYYMMDDHH24MISS);
				*m_ABL_ServicePtr <<DEBUG<<ls_ErrMesg<< Endl;


                 if(strcmp(ls_SourceType.c_str(),"R")==0)
			{
				ls_sql="select rerate_seq_no,";
				//modified as per LTE
				//ls_sql+="file_id,agreement_type,sysdate,sysdate,0,'P',count(*),sum(substr(error_cdr,instr(error_cdr,'|',1,13)+1,10)),0,0,0,";
				ls_sql+="file_id,agreement_type,sysdate,sysdate,0,'P',count(*),sum(nvl(call_duration,0)),0,0,0,";
				//end
				ls_sql+="0,0,0,0,0,'' ";
				ls_sql+="from pm_rejected_cdrs where rerate_seq_no=:1 and call_date >= :2 and call_date <= :3 group by rerate_seq_no, file_id, agreement_type, sysdate";
            }
			else
			{
                ls_sql="select rerate_seq_no,";
				//modified as per LTE
				//ls_sql+="file_id,agreement_type,sysdate,sysdate,0,'P',count(*),sum(substr(error_cdr,instr(error_cdr,'|',1,13)+1,10)),0,0,0,";
				ls_sql+="file_id,agreement_type,sysdate,sysdate,0,'P',count(*),sum(nvl(call_duration,0)),0,0,0,";
				//end
				ls_sql+="0,0,0,0,0,'' ";
				ls_sql+="from pm_duplicate_cdrs where rerate_seq_no=:1 and call_date >= :2 and call_date <= :3 group by rerate_seq_no, file_id, agreement_type, sysdate";
           
			}
				ABL_Statement	lo_GetFilesList_Statement;
				ABL_ResultSet	lo_GetFilesList_ResultSet;
				
				lo_GetFilesList_Statement	=	lo_ABLConnection.mb_createStatement(ls_sql);
				lo_GetFilesList_Statement.mb_setUInt(1,ln_RerateSequenceNo);
				lo_GetFilesList_Statement.mb_setDate(2,ld_FirstCalledDate);
				lo_GetFilesList_Statement.mb_setDate(3,ld_LastCalledDate);
				lo_GetFilesList_ResultSet	=lo_GetFilesList_Statement.mb_executeQuery();

				ls_RerateSeqNo_FileID="";
				while(lo_GetFilesList_ResultSet.mb_fetch())
				{
					ABL_String ls_TempTotalFiles="";
					ln_TotalFiles=0;				
					ln_TotalFiles = lo_GetFilesList_ResultSet.mb_getInt64(8);
					ls_TempTotalFiles.mb_fromInt64(ln_TotalFiles);

					if (ln_TotalFiles ==0) 
					{
						ls_ErrMesg = "..No files to Rerate for Rerate seq no => ";
						ls_ErrMesg+=ls_TempRerateSequenceNo;
						*m_ABL_ServicePtr <<DEBUG<<ls_ErrMesg<< Endl;
						continue;
					}
					ABL_Statement	lo_PMRerateFiles_Statement;
					try
					{

						if (ln_TotalFiles > 0)
						{

							ls_sql="INSERT INTO PM_Reprice_Files VALUES(:1,:2,:3,:4,:5,:6,:7,:8,:9,:10,:11,:12,:13,:14,:15,:16,:17,:18)";
							lo_PMRerateFiles_Statement	=	lo_ABLConnection.mb_createStatement(ls_sql);

							lo_PMRerateFiles_Statement.mb_setUInt(1,lo_GetFilesList_ResultSet.mb_getInt64(1));
							lo_PMRerateFiles_Statement.mb_setUInt(2,lo_GetFilesList_ResultSet.mb_getInt64(2));
							lo_PMRerateFiles_Statement.mb_setString(3,lo_GetFilesList_ResultSet.mb_getString(3));
							lo_PMRerateFiles_Statement.mb_setDate(4,lo_GetFilesList_ResultSet.mb_getDate(4));							
							lo_PMRerateFiles_Statement.mb_setDate(5,lo_GetFilesList_ResultSet.mb_getDate(5));							
							lo_PMRerateFiles_Statement.mb_setUInt(6,lo_GetFilesList_ResultSet.mb_getInt64(6));							
							lo_PMRerateFiles_Statement.mb_setString(7,lo_GetFilesList_ResultSet.mb_getString(7));
							lo_PMRerateFiles_Statement.mb_setUInt(8,lo_GetFilesList_ResultSet.mb_getInt64(8));
							lo_PMRerateFiles_Statement.mb_setUInt(9,lo_GetFilesList_ResultSet.mb_getInt64(9));
							lo_PMRerateFiles_Statement.mb_setUInt(10,lo_GetFilesList_ResultSet.mb_getInt64(10));
							lo_PMRerateFiles_Statement.mb_setUInt(11,lo_GetFilesList_ResultSet.mb_getInt64(11));
							lo_PMRerateFiles_Statement.mb_setUInt(12,lo_GetFilesList_ResultSet.mb_getInt64(12));
							lo_PMRerateFiles_Statement.mb_setUInt(13,lo_GetFilesList_ResultSet.mb_getInt64(13));
							lo_PMRerateFiles_Statement.mb_setUInt(14,0);
							lo_PMRerateFiles_Statement.mb_setUInt(15,0);
							lo_PMRerateFiles_Statement.mb_setUInt(16,0);
							lo_PMRerateFiles_Statement.mb_setUInt(17,0);
							lo_PMRerateFiles_Statement.mb_setString(18,"");
							lo_PMRerateFiles_Statement.mb_executeUpdate();
							lo_ABLConnection.mb_terminateStatement(lo_PMRerateFiles_Statement);

							ls_FileID="";
							ls_RerateSeqNo_FileID="";
							ls_FileID.mb_fromInt64(lo_GetFilesList_ResultSet.mb_getInt64(2));
							ls_RerateSeqNo_FileID=ls_TempRerateSequenceNo;
							ls_RerateSeqNo_FileID+="|";
							ls_RerateSeqNo_FileID+=ls_RerateLevel;
							ls_RerateSeqNo_FileID+="|";
							ls_RerateSeqNo_FileID+=ls_AgreementType;
							ls_RerateSeqNo_FileID+="|";
							ls_RerateSeqNo_FileID+=ls_FileID;	
							ls_RerateSeqNo_FileID+="|";
							ls_RerateSeqNo_FileID+=ld_FirstCalledDate.mb_toString(YYYYMMDDHH24MISS);				
							ls_RerateSeqNo_FileID+="|";
							ls_RerateSeqNo_FileID+=ld_LastCalledDate.mb_toString(YYYYMMDDHH24MISS);	
							ls_RerateSeqNo_FileID+="|";
							ls_RerateSeqNo_FileID+=ls_SourceType;
							mq_fileNames.push(ls_RerateSeqNo_FileID);

						}

					}
					catch(ABL_Exception &e)
					{
						ABL_String ls_ErrorMessage=e.mb_getMessage();
						lo_ABLConnection.mb_terminateStatement(lo_PMRerateFiles_Statement);
							//when dup_val_on_index then
						if(ls_ErrorMessage.mb_subStr(0,9) == "ORA-00001")
						{
							lo_ABLConnection.mb_rollback();
							ls_ErrMesg = "..Rerate Seq=>";
							ls_ErrMesg+=ls_TempRerateSequenceNo;
							ls_ErrMesg+=":Duplicates entries encountered. Delete duplicate entries and re-insert";
							*m_ABL_ServicePtr <<DEBUG<<ls_ErrMesg<< Endl;

								 
							 ABL_Statement	lo_ErrorStatement;
							ls_sql="delete from pm_reprice_files where reprice_seq_no=:1";
							lo_ErrorStatement	=	lo_ABLConnection.mb_createStatement(ls_sql);
							lo_ErrorStatement.mb_setUInt(1,ln_RerateSequenceNo);
							int ln_DupRecords=lo_ErrorStatement.mb_executeUpdate();
							lo_ABLConnection.mb_terminateStatement(lo_ErrorStatement);
							if (ln_DupRecords == 0)
							{
								  ls_ErrMesg = "..Rerate Seq=>";
								  ls_ErrMesg+=ls_TempRerateSequenceNo;
								  ls_ErrMesg+=":No pending files to delete. Error while inserting";
								  *m_ABL_ServicePtr <<DEBUG<<ls_ErrMesg<< Endl;
								  return false;
							}


							ABL_Statement	lo_PMRerateFiles_Statement;
							ls_sql="INSERT INTO PM_Reprice_Files VALUES(:1,:2,:3,:4,:5,:6,:7,:8,:9,:10,:11,:12,:13,:14,:15,:16,:17,:18)";
							lo_PMRerateFiles_Statement	=	lo_ABLConnection.mb_createStatement(ls_sql);
							lo_PMRerateFiles_Statement.mb_setUInt(1,lo_GetFilesList_ResultSet.mb_getInt64(1));
							lo_PMRerateFiles_Statement.mb_setUInt(2,lo_GetFilesList_ResultSet.mb_getInt64(2));
							lo_PMRerateFiles_Statement.mb_setString(3,lo_GetFilesList_ResultSet.mb_getString(3));
							lo_PMRerateFiles_Statement.mb_setDate(4,lo_GetFilesList_ResultSet.mb_getDate(4));
							lo_PMRerateFiles_Statement.mb_setDate(5,lo_GetFilesList_ResultSet.mb_getDate(5));
							lo_PMRerateFiles_Statement.mb_setUInt(6,lo_GetFilesList_ResultSet.mb_getInt64(6));
							lo_PMRerateFiles_Statement.mb_setString(7,lo_GetFilesList_ResultSet.mb_getString(7));

							lo_PMRerateFiles_Statement.mb_setUInt(8,lo_GetFilesList_ResultSet.mb_getInt64(8));
							lo_PMRerateFiles_Statement.mb_setUInt(9,lo_GetFilesList_ResultSet.mb_getInt64(9));
							lo_PMRerateFiles_Statement.mb_setUInt(10,lo_GetFilesList_ResultSet.mb_getInt64(10));
							lo_PMRerateFiles_Statement.mb_setUInt(11,lo_GetFilesList_ResultSet.mb_getInt64(11));
							lo_PMRerateFiles_Statement.mb_setUInt(12,lo_GetFilesList_ResultSet.mb_getInt64(12));
							lo_PMRerateFiles_Statement.mb_setUInt(13,lo_GetFilesList_ResultSet.mb_getInt64(13));

							lo_PMRerateFiles_Statement.mb_setUInt(14,0);
							lo_PMRerateFiles_Statement.mb_setUInt(15,0);
							lo_PMRerateFiles_Statement.mb_setUInt(16,0);
							lo_PMRerateFiles_Statement.mb_setUInt(17,0);
							lo_PMRerateFiles_Statement.mb_setString(18,"");

							lo_PMRerateFiles_Statement.mb_executeUpdate();
							lo_ABLConnection.mb_terminateStatement(lo_PMRerateFiles_Statement);

							ls_FileID="";
							ls_RerateSeqNo_FileID="";
							ls_FileID.mb_fromInt64(lo_GetFilesList_ResultSet.mb_getInt64(2));
							ls_RerateSeqNo_FileID=ls_TempRerateSequenceNo;
							ls_RerateSeqNo_FileID+="|";
							ls_RerateSeqNo_FileID+=ls_RerateLevel;
							ls_RerateSeqNo_FileID+="|";
							ls_RerateSeqNo_FileID+=ls_AgreementType;
							ls_RerateSeqNo_FileID+="|";
							ls_RerateSeqNo_FileID+=ls_FileID;	
							ls_RerateSeqNo_FileID+="|";
							ls_RerateSeqNo_FileID+=ld_FirstCalledDate.mb_toString(YYYYMMDDHH24MISS);				
							ls_RerateSeqNo_FileID+="|";
							ls_RerateSeqNo_FileID+=ld_LastCalledDate.mb_toString(YYYYMMDDHH24MISS);	
							ls_RerateSeqNo_FileID+="|";
							ls_RerateSeqNo_FileID+=ls_SourceType;
							mq_fileNames.push(ls_RerateSeqNo_FileID);						}
						else
						{
							  ls_ErrMesg = ls_ErrorMessage;
						      *m_ABL_ServicePtr <<CRITICAL<<ls_ErrMesg<< Endl;
							  return false;

						}
					}
					catch(...)
					{
						std::cout<<"Errror while reading Rerate  detrails: "<<std::endl;

					}
					
				}

				lo_GetFilesList_Statement.mb_closeResultSet(lo_GetFilesList_ResultSet);
				lo_ABLConnection.mb_terminateStatement(lo_GetFilesList_Statement);
			 
		}
		lo_ABLConnection.mb_commit();
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet)       ;
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);

		mn_total_files_In_rerate_reprice_seq_no=mq_fileNames.size();
		if(mq_fileNames.empty())
		{
				return false;

		}
		else
		{
				return true;
		}
		
	}
	catch(ABL_Exception &e)
	{
			*m_ABL_ServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;
			return false;
	}
	catch (...)
	{
		*m_ABL_ServicePtr << CRITICAL << "Exception fnReadRerateData function"<< Endl;
		return false;

	}

}
/*Fuction to tokenize a string.*/
void PM_RerateInputAgent::tokenize(const std::string& in_str,std::vector<std::string>& lv_tokens,const std::string& in_delimiters )
{
	std::stringstream l_stringStream(in_str);
	std::string ls_tokenString;
	while(std::getline(l_stringStream,ls_tokenString,in_delimiters[0]))
	{
		lv_tokens.push_back(ls_tokenString);
	}
}

void PM_RerateInputAgent:: UpdateProcess(int ProcessId,ABL_String  Status,ABL_Connection *l_ABL_ConnectionPtrs)
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

		//update pm_process_status table.
		ls_sql = "update PM_PROCESS_STATUS set STOP_TIME=sysdate, ELAPSED_TIME=0, REMARKS='Normal stop after detecting the stop signal' where(PROCESS_ID=:1 and UNIX_PID=:2)"; 
		lo_ABLStatement = lo_ABLConnectionPtr->mb_createStatement(ls_sql); 
		lo_ABLStatement.mb_setInt (1,ProcessId);
		lo_ABLStatement.mb_setInt(2,getpid());
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

void PM_RerateInputAgent::InitialiseProcessVar()
{
      mobj_Masterdata.ms_lockfiledir       =  "" ;
      mobj_Masterdata.ms_stopSignDir       =  "" ;
      mobj_Masterdata.ms_stopSignFile      =  "" ;
}
