#include "PM_ReadRawCdrs.h"
#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "PM_Job.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "ABL_CacheManager.h"
#include "ABL_DateTime.h"
#include "ABL_Date.h"
#include "ABL_DbDate.h"
#include "string.h"
#include "sstream"
#include "vector"
#include "iostream"
#include "stdio.h"
#include <stdlib.h>
#include <sys/stat.h>



extern "C" {EXPORT 
Base_Registry* gb_getPM_ReadRawCdrs()
{
	return ( (Base_Registry*) new PM_ReadRawCdrs);
}
}

PM_ReadRawCdrs::PM_ReadRawCdrs()
{
	//
}

PM_ReadRawCdrs::~PM_ReadRawCdrs()
{
	//
}

PM_ReadRawCdrs::PM_ReadRawCdrs(const PM_ReadRawCdrs& p_copyObject)
{	
	
	this->m_ABL_ServicePtr				=	p_copyObject.m_ABL_ServicePtr;

	this->ms_Stopsignalfile				=	p_copyObject.ms_Stopsignalfile;

	this->ms_directoryName				=	p_copyObject.ms_directoryName;
	this->ms_rawCdrFileName				=	p_copyObject.ms_rawCdrFileName;
	this->ms_ProcessedFilePath			=	p_copyObject.ms_ProcessedFilePath;
	this->ms_BackupFlag					=	p_copyObject.ms_BackupFlag;
	this->ms_ErrorFilePath				=	p_copyObject.ms_ErrorFilePath;
        this->ms_DuplicateFilePath                      =       p_copyObject.ms_DuplicateFilePath;

}

Base_Registry* PM_ReadRawCdrs::mb_clone()
{
	return ( (Base_Registry*) new PM_ReadRawCdrs );
}

ABL_Process* PM_ReadRawCdrs::mb_createCopy()
{
	return ( new PM_ReadRawCdrs (*this));
}

bool PM_ReadRawCdrs::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{
	
	try
	{
		m_ABL_ServicePtr			= p_ABL_ServicePtr;
		p_ABL_AgentCommunicatorPtr->mb_getParameter("STOP_FILE",ms_Stopsignalfile);
		p_ABL_AgentCommunicatorPtr->mb_getParameter("FilesDir",ms_directoryName);
		p_ABL_AgentCommunicatorPtr->mb_getParameter("BackupFlag",ms_BackupFlag);
		p_ABL_AgentCommunicatorPtr->mb_getParameter("ProcessFilesDir",ms_ProcessedFilePath);
		p_ABL_AgentCommunicatorPtr->mb_getParameter("ErrorFilesDir",ms_ErrorFilePath);
                p_ABL_AgentCommunicatorPtr->mb_getParameter("BackUpFilesDir",ms_DuplicateFilePath);
                

		
	 }   
	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;	
		 ABL_String ls_command("touch ");
		 ls_command +=ms_Stopsignalfile;
		 system(ls_command.c_str());  
		 return false;
	}
	catch(...)
	{
		ABL_String ls_command("touch ");
		ls_command +=ms_Stopsignalfile;
		 system(ls_command.c_str()); 	
		*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}

 	return true;
}

bool PM_ReadRawCdrs::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	return true;
}

bool PM_ReadRawCdrs::mb_process(ABL_Job* &p_ABL_JobPtr)
{

	PM_Job* lo_PMJobPtr    = (PM_Job*)p_ABL_JobPtr;	
	gr_RatingLog lr_RatingLog;	
	ABL_String		ms_rawCdr;
	ABL_DateTime ld_onDate;
	ABL_DateTime ld_ReceivedDate;
	ABL_String ls_CdrValue ;	
	int  ln_dupFileIndex  = -1;
	int  ln_dupFileIndexnew  = -1;
	//modified as per the LTE usage for 4.3 release
	//char lc_strCDRValue [1000];	
	char lc_strCDRValue [1500];
	//end
	

	ABL_Connection	*lo_ABLConnectionPtr;
	ABL_Statement	lo_ABLStatement;
	ABL_ResultSet	lo_ABLResultSet;
	ABL_String	    ls_sql;	
	
	//ABL_Connection  *lo_ABLConnection;
    //ABL_ResultSet 	lo_ABLResultSet;
	//ABL_String	ls_sql;

	struct stat lo_statbuffer;
    	int ln_status;
	struct tm * lo_tmTimeinfo;
	char lc_FileReceivedDate[15];
	int rc=0;
	try
	{
            lo_PMJobPtr->gs_FileStatus = "S";


			if(lo_PMJobPtr->gs_IsGPRSFile=="YES")
			{
				return true;
			}

			*m_ABL_ServicePtr << DEBUG << "Start :" <<lo_PMJobPtr->gs_fileName << Endl;

			if (lo_PMJobPtr->gs_BackupFlag=="")
			{
				lo_PMJobPtr->gs_BackupFlag=ms_BackupFlag;
			}

			if(lo_PMJobPtr->gs_ErrorFile_Path=="")
			{
				lo_PMJobPtr->gs_ErrorFile_Path=ms_ErrorFilePath;
				lo_PMJobPtr->gs_ErrorFile_Path+=lo_PMJobPtr->gs_fileName;
			}

			if(lo_PMJobPtr->gs_SourceFilePath=="")
			{
				ms_rawCdrFileName=ms_directoryName;
				ms_rawCdrFileName+=lo_PMJobPtr->gs_fileName;
				lo_PMJobPtr->gs_SourceFilePath=ms_rawCdrFileName;

			}
			if(lo_PMJobPtr->gs_ProcessedFilePath=="")
			{

				lo_PMJobPtr->gs_ProcessedFilePath=ms_ProcessedFilePath;
				lo_PMJobPtr->gs_ProcessedFilePath+=lo_PMJobPtr->gs_fileName;
			}

                        lo_PMJobPtr->gs_DuplicateFilePath=ms_DuplicateFilePath;
                        lo_PMJobPtr->gs_DuplicateFilePath+=lo_PMJobPtr->gs_fileName;

				ld_onDate.mb_fromSysDate();
		    /* Checking  for Duplication of the file.*/
			lo_ABLConnectionPtr = lo_PMJobPtr->mb_getConnection();
			ls_sql				=	"select COUNT(1)   FROM PM_RATING_LOG  WHERE (CDR_FILE_NAME=:1) ";
			lo_ABLStatement		=	lo_ABLConnectionPtr->mb_createStatement(ls_sql);		
			lo_ABLStatement.mb_setString(1,(lo_PMJobPtr)->gs_fileName );
			lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
			lo_ABLResultSet.mb_fetch();
			ln_dupFileIndex= lo_ABLResultSet.mb_getInt(1);
			lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
			lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement);
			if ( ln_dupFileIndex >= 1 )
			{
			
				/* Move the Duplicate file which is processed. */		
				try
				{	
					                 *m_ABL_ServicePtr <<CRITICAL<< "The file : " << (lo_PMJobPtr)->gs_fileName << " is already rated."  << Endl;
                                        *m_ABL_ServicePtr <<CRITICAL<< "Moving file to : "<<lo_PMJobPtr->gs_DuplicateFilePath.c_str()<< Endl;
                                        rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_DuplicateFilePath.c_str());
										lo_PMJobPtr->gs_FileStatus = "D";
										lo_PMJobPtr->gs_FileMessage = "Duplicate File";                                     
					                    
										//Imam's code changes for the inserting rating error log
										//return true;
										
										ls_sql     =       "select COUNT(1) FROM PM_RATING_ERROR_FILES  WHERE (CDR_FILE_NAME=:1 and STATUS=:2) ";
										lo_ABLStatement         =       lo_ABLConnectionPtr->mb_createStatement(ls_sql);
										lo_ABLStatement.mb_setString(1,(lo_PMJobPtr)->gs_fileName );
										lo_ABLStatement.mb_setString(2,lo_PMJobPtr->gs_FileStatus);
										lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
										lo_ABLResultSet.mb_fetch();
										ln_dupFileIndexnew= lo_ABLResultSet.mb_getInt(1);
										lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
										lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement);

                        if ( ln_dupFileIndexnew >= 1 )
                        {

								ls_sql = "UPDATE PM_RATING_ERROR_FILES SET REPROCESSED_TIME=SYSDATE,ERROR_MESSAGE=:1 WHERE CDR_FILE_NAME=:2 AND STATUS=:3 ";
                                        lo_ABLStatement = lo_ABLConnectionPtr->mb_createStatement(ls_sql);
                                        lo_ABLStatement.mb_setString(1,lo_PMJobPtr->gs_FileMessage );
										lo_ABLStatement.mb_setString(2,(lo_PMJobPtr)->gs_fileName);
										lo_ABLStatement.mb_setString(3,lo_PMJobPtr->gs_FileStatus);
                                        lo_ABLStatement.mb_executeUpdate();
                                        lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement);
                        }
                        else
                         {
                                ls_sql = "INSERT INTO PM_RATING_ERROR_FILES (CDR_FILE_NAME,STATUS,PROCESSED_TIME,ERROR_MESSAGE) VALUES (:1,:2,SYSDATE,:3)";
                                        lo_ABLStatement = lo_ABLConnectionPtr->mb_createStatement(ls_sql);
                                        lo_ABLStatement.mb_setString(1,(lo_PMJobPtr)->gs_fileName);
                                        lo_ABLStatement.mb_setString(2,lo_PMJobPtr->gs_FileStatus);
                                        lo_ABLStatement.mb_setString(3, lo_PMJobPtr->gs_FileMessage);
										lo_ABLStatement.mb_executeUpdate();
                                        lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement);
                         }

						lo_ABLConnectionPtr->mb_commit();
                         return  false;
						 
						 // Imam's code change ends here for the rating_errror_files insert 
				}		
				catch(ABL_Exception &e)
				{
					rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
					*m_ABL_ServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;
					 ABL_String ls_command("touch ");
					ls_command +=ms_Stopsignalfile;
					lo_PMJobPtr->gs_FileStatus = "D";
					lo_PMJobPtr->gs_FileMessage = e.mb_getMessage();                    
					system(ls_command.c_str());  
					return true;
				}
				catch(...)
				{
					rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
					ABL_String ls_command("touch ");
					ls_command +=ms_Stopsignalfile;
					 system(ls_command.c_str()); 
					 *m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
					lo_PMJobPtr->gs_FileStatus = "D";
					lo_PMJobPtr->gs_FileMessage = strerror(errno);                    
					return true;
				}

			}

			/*********************************************************/
			memset(lc_FileReceivedDate,'\0',sizeof(lc_FileReceivedDate));
		   ln_status=stat(lo_PMJobPtr->gs_SourceFilePath.c_str(), &lo_statbuffer);
		   /* Get File Received Date */
		   ctime ( &lo_statbuffer.st_ctime );
		   lo_tmTimeinfo = localtime ( &lo_statbuffer.st_ctime );
		   strftime (lc_FileReceivedDate,15,"%G%m%d%H%M%S.",lo_tmTimeinfo);
		     if(lo_statbuffer.st_size<=0)
		  {
			   rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
			 *m_ABL_ServicePtr<<DEBUG<<lo_PMJobPtr->gs_SourceFilePath<< ":: Empty file. Skip processing" <<Endl;
			 return false;
		  }
			/* Read next CDR from  raw cdr file.*/	
/*			ls_sql							=	"select pm_rating_file_seq.nextval from dual";
			lo_ABLStatement					=	lo_ABLConnectionPtr->mb_createStatement(ls_sql);		
			lo_ABLResultSet					=   lo_ABLStatement.mb_executeQuery();
			lo_ABLResultSet.mb_fetch();		
			lo_PMJobPtr->gn_InPutFileId     =   lo_ABLResultSet.mb_getInt(1);
			lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
			lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement);  */

                          double l_seq[1];

		 
			/* Read next CDR from  raw cdr file.*/	
			ls_sql							=       "select pm_rating_file_seq.nextval from dual";
			lo_ABLStatement				         	=	lo_ABLConnectionPtr->mb_createStatement(ls_sql);		
			lo_ABLResultSet					        =       lo_ABLStatement.mb_executeQuery();
			lo_ABLResultSet.mb_setBulkCount(1);
                        lo_ABLResultSet<<l_seq;
		        while(lo_ABLResultSet.mb_fetch())
                        {
                         int records = lo_ABLResultSet.mb_getNumArrayRows();
                        for(int i = 0; i < records ; i++)
                        {
                        lo_PMJobPtr->gn_InPutFileId =  l_seq[i];
		        }
         	        }
		  	lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
			lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement);


			/* Till end of the file read all the cdrs one by one .*/
			lo_PMJobPtr->ga_RawCDRSVector.clear();
			std::ifstream inFiles; 
			inFiles.open(lo_PMJobPtr->gs_SourceFilePath.c_str(),std::ios::in);
			if(inFiles.is_open())
				{
				 while (!inFiles.eof())
			//while(inFiles.getline(lc_strCDRValue,READ_STRING_SIZE))
                                        {
                                                //added as per LTE
                                                rc++;
                                                //end
                                                memset (lc_strCDRValue,'\0',sizeof(lc_strCDRValue));
						if(inFiles.eof()) break;
                                                inFiles.getline(lc_strCDRValue,READ_STRING_SIZE);
                                                ls_CdrValue=lc_strCDRValue;
						lo_PMJobPtr->ga_RawCDRSVector.push_back(ls_CdrValue);
					}						
					inFiles.close();
				}
			else
				{	
			   		rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
					*m_ABL_ServicePtr<<DEBUG<<lo_PMJobPtr->gs_SourceFilePath<< "::Error opening file or check record no."<<rc<<" lenth" <<Endl;
			  		inFiles.close();
					lo_PMJobPtr->gs_FileStatus = "F";
		            lo_PMJobPtr->gs_FileMessage = "Error While opening file";     

										//Imam's code changes for the inserting rating error log
										//return true;
										
										ls_sql     =       "select COUNT(1) FROM PM_RATING_ERROR_FILES  WHERE (CDR_FILE_NAME=:1 and STATUS=:2) ";
										lo_ABLStatement         =       lo_ABLConnectionPtr->mb_createStatement(ls_sql);
										lo_ABLStatement.mb_setString(1,(lo_PMJobPtr)->gs_fileName );
										lo_ABLStatement.mb_setString(2,lo_PMJobPtr->gs_FileStatus);
										lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
										lo_ABLResultSet.mb_fetch();
										ln_dupFileIndexnew= lo_ABLResultSet.mb_getInt(1);
										lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
										lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement);

                        if ( ln_dupFileIndexnew >= 1 )
                        {

								ls_sql = "UPDATE PM_RATING_ERROR_FILES SET REPROCESSED_TIME=SYSDATE,ERROR_MESSAGE=:1 WHERE CDR_FILE_NAME=:2 AND STATUS=:3 ";
                                        lo_ABLStatement = lo_ABLConnectionPtr->mb_createStatement(ls_sql);
                                        lo_ABLStatement.mb_setString(1,lo_PMJobPtr->gs_FileMessage );
										lo_ABLStatement.mb_setString(2,(lo_PMJobPtr)->gs_fileName);
										lo_ABLStatement.mb_setString(3,lo_PMJobPtr->gs_FileStatus);
                                        lo_ABLStatement.mb_executeUpdate();
                                        lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement);
                        }
                        else
                         {
                                ls_sql = "INSERT INTO PM_RATING_ERROR_FILES (CDR_FILE_NAME,STATUS,PROCESSED_TIME,ERROR_MESSAGE) VALUES (:1,:2,SYSDATE,:3)";
                                        lo_ABLStatement = lo_ABLConnectionPtr->mb_createStatement(ls_sql);
                                        lo_ABLStatement.mb_setString(1,(lo_PMJobPtr)->gs_fileName);
                                        lo_ABLStatement.mb_setString(2,lo_PMJobPtr->gs_FileStatus);
                                        lo_ABLStatement.mb_setString(3, lo_PMJobPtr->gs_FileMessage);
										lo_ABLStatement.mb_executeUpdate();
                                        lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement);
                         }

						lo_ABLConnectionPtr->mb_commit();
                         return  false;			
				}
			ld_ReceivedDate.mb_fromText(lc_FileReceivedDate);
			lr_RatingLog.gs_CdrFileName				=	lo_PMJobPtr->gs_fileName;						
			lr_RatingLog.gd_ReceivedOn				=	ld_ReceivedDate;	
			lr_RatingLog.gd_ProcessStartTime.mb_fromSysDate();
			lr_RatingLog.gs_Processed				=	"N";		
			lr_RatingLog.gn_FileId					=	lo_PMJobPtr->gn_InPutFileId ;
			lr_RatingLog.gn_ProcessingTimeInSecs	=	0;
			lr_RatingLog.gs_Chrono					=	"";
			lr_RatingLog.gs_EdChrono				=	"";
			lr_RatingLog.gn_TotalEvents				=	0;
			lr_RatingLog.gn_IncTotalEvents			=	0;
			lr_RatingLog.gn_IncRatedEvents			=	0;
			lr_RatingLog.gn_IncDroppedEvents		=	0;
			lr_RatingLog.gn_IncRejectedEvents		=   0;
			lr_RatingLog.gn_OutTotalEvents			=	0;
			lr_RatingLog.gn_OutRatedEvents			=	0;
			lr_RatingLog.gn_OutDroppedEvents		=	0;
			lr_RatingLog.gn_OutRejectedEvents		=	0;
			lr_RatingLog.gs_Processed				=	"Y";
			lo_PMJobPtr->ga_RatingLog.push_back(lr_RatingLog);	
			*m_ABL_ServicePtr <<DEBUG<<"End  :" << lo_PMJobPtr->gs_fileName <<": "<<lo_PMJobPtr->ga_RawCDRSVector.size()<< Endl;
	}
    catch(ABL_Exception &e)
	{
		rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
		*m_ABL_ServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;
		 ABL_String ls_command("touch ");
		 ls_command +=ms_Stopsignalfile;
		 system(ls_command.c_str());  
		 lo_PMJobPtr->gs_FileStatus = "F";
		 lo_PMJobPtr->gs_FileMessage = e.mb_getMessage();                                     
		return true;
	}
	catch(...)
	{
		rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
		ABL_String ls_command("touch ");
		ls_command +=ms_Stopsignalfile;
		 system(ls_command.c_str()); 	
		*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		lo_PMJobPtr->gs_FileStatus = "F";
		 lo_PMJobPtr->gs_FileMessage = strerror(errno);                                     
		return true;
	}

	return true;
}

bool PM_ReadRawCdrs::mb_stop()
{
	return true;
}
