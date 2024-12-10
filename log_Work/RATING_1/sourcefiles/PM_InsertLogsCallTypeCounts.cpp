#include "PM_InsertLogsCallTypeCounts.h"
#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "ABL_DateTime.h"
#include "ABL_Date.h"
#include "ABL_DbDate.h"
#include "ABL_Blob.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_InsertLogsCallTypeCounts()
{
	return ( (Base_Registry*) new PM_InsertLogsCallTypeCounts);
}
}

PM_InsertLogsCallTypeCounts::PM_InsertLogsCallTypeCounts()
{
	//
}

PM_InsertLogsCallTypeCounts::~PM_InsertLogsCallTypeCounts()
{
	//
}

PM_InsertLogsCallTypeCounts::PM_InsertLogsCallTypeCounts(const PM_InsertLogsCallTypeCounts& p_copyObject)
{
	this->m_ABL_ServicePtr							=	p_copyObject.m_ABL_ServicePtr;
	this->mn_DB_BULK_INSERT_COUNT					=	p_copyObject.mn_DB_BULK_INSERT_COUNT;	
	this->ms_Stopsignalfile							=	p_copyObject.ms_Stopsignalfile;	
	this->mn_totalfiles_in_rerate_reprice_seq_no	=	p_copyObject.mn_totalfiles_in_rerate_reprice_seq_no;
	
}

Base_Registry* PM_InsertLogsCallTypeCounts::mb_clone()
{
	return ( (Base_Registry*) new PM_InsertLogsCallTypeCounts );
}

ABL_Process* PM_InsertLogsCallTypeCounts::mb_createCopy()
{
	return ( new PM_InsertLogsCallTypeCounts (*this));
}

bool PM_InsertLogsCallTypeCounts::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{	
	try
	{
			mn_totalfiles_in_rerate_reprice_seq_no=0;
			m_ABL_ServicePtr = p_ABL_ServicePtr;
			p_ABL_AgentCommunicatorPtr->mb_getParameter("STOP_FILE",ms_Stopsignalfile);
			mn_DB_BULK_INSERT_COUNT=0;
			mn_DB_BULK_INSERT_COUNT=m_ABL_ServicePtr->mb_getInt("DB_BULK_INSERT_COUNT");

	}
	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
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

bool PM_InsertLogsCallTypeCounts::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	
	return true;
}
bool PM_InsertLogsCallTypeCounts::mb_stop()
{
	return true;
}

bool PM_InsertLogsCallTypeCounts::mb_process(ABL_Job* &p_ABL_JobPtr)
{	
	
	PM_Job* lo_PMJobPtr = (PM_Job*)p_ABL_JobPtr;		
	ABL_Connection	*lo_ABLConnection;
	ABL_Statement	lo_ABLStatement;
	ABL_ResultSet	lo_AB_ResultSet;
	ABL_String	ls_sql;
	ABL_String      ls_SQlQuery;
	ABL_String	ls_TempDate;
	ABL_String	ls_TempConvert; 
	int         ln_dupFileIndex;
	unsigned int	ln_insec;
	int		ln_ErrorNums=0;
	try
	{
                   lo_ABLConnection = lo_PMJobPtr->mb_getConnection();

                   if ( lo_PMJobPtr->gs_FileStatus == "D" || lo_PMJobPtr->gs_FileStatus == "F" )
                        {
                         
	        ls_SQlQuery	=	"select COUNT(1) FROM PM_RATING_ERROR_FILES  WHERE (CDR_FILE_NAME=:1 and STATUS=:2) ";
			lo_ABLStatement		=	lo_ABLConnection->mb_createStatement(ls_SQlQuery);		
			lo_ABLStatement.mb_setString(1,lo_PMJobPtr->gs_fileName );
			lo_ABLStatement.mb_setString(2,lo_PMJobPtr->gs_FileStatus);
			lo_AB_ResultSet = lo_ABLStatement.mb_executeQuery();
			lo_AB_ResultSet.mb_fetch();
			ln_dupFileIndex= lo_AB_ResultSet.mb_getInt(1);
			lo_ABLStatement.mb_closeResultSet(lo_AB_ResultSet);
			lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
	
			if ( ln_dupFileIndex >= 1 )
			{

                    ls_SQlQuery = "UPDATE PM_RATING_ERROR_FILES SET REPROCESSED_TIME=SYSDATE,ERROR_MESSAGE=:1 WHERE CDR_FILE_NAME=:2 AND STATUS=:3 ";
					lo_ABLStatement = lo_ABLConnection->mb_createStatement(ls_SQlQuery);					
					lo_ABLStatement.mb_setString(1,lo_PMJobPtr->gs_FileMessage );
                    lo_ABLStatement.mb_setString(2,lo_PMJobPtr->gs_fileName);
			        lo_ABLStatement.mb_setString(3,lo_PMJobPtr->gs_FileStatus);
					lo_ABLStatement.mb_executeUpdate();			
					lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);		
			}
			else
			 {
    				ls_SQlQuery = "INSERT INTO PM_RATING_ERROR_FILES (CDR_FILE_NAME,STATUS,PROCESSED_TIME,ERROR_MESSAGE) VALUES (:1,:2,SYSDATE,:3)";
					lo_ABLStatement = lo_ABLConnection->mb_createStatement(ls_SQlQuery);					
					lo_ABLStatement.mb_setString(1,lo_PMJobPtr->gs_fileName);	
					lo_ABLStatement.mb_setString(2,lo_PMJobPtr->gs_FileStatus);
					lo_ABLStatement.mb_setString(3, lo_PMJobPtr->gs_FileMessage);
           			lo_ABLStatement.mb_executeUpdate();			
					lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);	  
			 }

             lo_ABLConnection->mb_commit();   
			 return  false;
			
			}


		if (lo_PMJobPtr->ga_RatedCdrs.size()== 0 && lo_PMJobPtr->ga_RejectedCdrs.size()==0 && lo_PMJobPtr->ga_DroppedCdr.size()==0) 
			{
				if (lo_PMJobPtr->gs_IsGPRSFile=="YES")
				{
					return true;
				}
				
			}

		*m_ABL_ServicePtr << DEBUG << "Start :" <<lo_PMJobPtr->gs_fileName<< Endl;

	
		if(lo_PMJobPtr->gn_RepriceSeqNo==0)
			{
				
				try
				{
					lo_PMJobPtr->ga_RatingLog[0].gn_TotalEvents=0;
					lo_PMJobPtr->ga_RatingLog[0].gn_TotalEvents=lo_PMJobPtr->gn_TotalCDRS_In_File;
					lo_PMJobPtr->ga_RatingLog[0].gn_ProcessingTimeInSecs=0;
					lo_PMJobPtr->ga_RatingLog[0].gs_Reconciled="N";
					lo_PMJobPtr->ga_RatingLog[0].gs_Summarised="N";
					lo_PMJobPtr->ga_RatingLog[0].gd_ProcessEndTime.mb_fromSysDate();
					ln_insec=lo_PMJobPtr->ga_RatingLog[0].gd_ProcessEndTime.mb_getJulianDateTime()-lo_PMJobPtr->ga_RatingLog[0].gd_ProcessStartTime.mb_getJulianDateTime();	//lo_PMJobPtr->ga_RatingLog[0].g_ProcessingTimeInSecs;	
					lo_PMJobPtr->ga_RatingLog[0].gn_ProcessingTimeInSecs=ln_insec;

					ls_SQlQuery = "INSERT INTO PM_RATING_LOG (CDR_FILE_NAME,RECEIVED_ON,PROCESS_START_TIME,PROCESS_END_TIME,PROCESSING_TIME_IN_SECS,ST_CHRONO,ED_CHRONO,FIRST_CALL_DT_TIME,LAST_CALL_DT_TIME,TOTAL_EVENTS,INC_TOTAL_EVENTS,INC_RATED_EVENTS,INC_DROPPED_EVENTS,INC_REJECTED_EVENTS,OUT_TOTAL_EVENTS,OUT_RATED_EVENTS,OUT_DROPPED_EVENTS,OUT_REJECTED_EVENTS,PROCESSED,FILE_ID,SUMMARISED,RECONCILED,NE_CODE) VALUES (:1,:2,:3,:4,:5,:6,:7,:8,:9,:10,:11,:12,:13,:14,:15,:16,:17,:18,:19,:20,:21,:22,:23)";
					lo_ABLStatement = lo_ABLConnection->mb_createStatement(ls_SQlQuery);					
					lo_ABLStatement.mb_setString(1,lo_PMJobPtr->ga_RatingLog[0].gs_CdrFileName);
					lo_ABLStatement.mb_setDate(2,lo_PMJobPtr->gd_DbTimeStamp);
					lo_ABLStatement.mb_setDate(3,lo_PMJobPtr->ga_RatingLog[0].gd_ProcessStartTime);
					lo_ABLStatement.mb_setDate(4,lo_PMJobPtr->ga_RatingLog[0].gd_ProcessEndTime);
					lo_ABLStatement.mb_setInt(5, lo_PMJobPtr->ga_RatingLog[0].gn_ProcessingTimeInSecs);
					lo_ABLStatement.mb_setString(6,lo_PMJobPtr->ga_RatingLog[0].gs_Chrono);
					lo_ABLStatement.mb_setString(7,lo_PMJobPtr->ga_RatingLog[0].gs_EdChrono);
					lo_ABLStatement.mb_setDate(8,lo_PMJobPtr->ga_RatingLog[0].gd_FirstCallDtTime);
					lo_ABLStatement.mb_setDate(9,lo_PMJobPtr->ga_RatingLog[0].gd_LastCallDtTime);
					lo_ABLStatement.mb_setDouble(10,lo_PMJobPtr->ga_RatingLog[0].gn_TotalEvents);
					lo_ABLStatement.mb_setDouble(11,lo_PMJobPtr->ga_RatingLog[0].gn_IncTotalEvents);
					lo_ABLStatement.mb_setDouble(12,lo_PMJobPtr->ga_RatingLog[0].gn_IncRatedEvents);
					lo_ABLStatement.mb_setDouble(13,lo_PMJobPtr->ga_RatingLog[0].gn_IncDroppedEvents);
					lo_ABLStatement.mb_setDouble(14,lo_PMJobPtr->ga_RatingLog[0].gn_IncRejectedEvents);
					lo_ABLStatement.mb_setDouble(15,lo_PMJobPtr->ga_RatingLog[0].gn_OutTotalEvents);
					lo_ABLStatement.mb_setDouble(16,lo_PMJobPtr->ga_RatingLog[0].gn_OutRatedEvents);
					lo_ABLStatement.mb_setDouble(17,lo_PMJobPtr->ga_RatingLog[0].gn_OutDroppedEvents);
					lo_ABLStatement.mb_setDouble(18,lo_PMJobPtr->ga_RatingLog[0].gn_OutRejectedEvents);
					lo_ABLStatement.mb_setString(19,lo_PMJobPtr->ga_RatingLog[0].gs_Processed); 
					lo_ABLStatement.mb_setDouble(20,lo_PMJobPtr->ga_RatingLog[0].gn_FileId);  
					lo_ABLStatement.mb_setString(21,lo_PMJobPtr->ga_RatingLog[0].gs_Summarised);
					lo_ABLStatement.mb_setString(22,lo_PMJobPtr->ga_RatingLog[0].gs_Reconciled);
					lo_ABLStatement.mb_setString(23,lo_PMJobPtr->ga_RatingLog[0].gs_NeCode);

					lo_ABLStatement.mb_executeUpdate();			
					lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);	

				}
				catch (ABL_Exception &e)
				{
					 std::string err1=e.mb_getMessage();
					 if (err1.compare(0,9,"ORA-00001")==0)
						 {
							*m_ABL_ServicePtr<<DEBUG<<"This file ::"<<lo_PMJobPtr->gs_fileName<<" already rated "<<Endl;
							return false;
						 }
					 else
						 {
							rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
							*m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<" for the file : "<<lo_PMJobPtr->gs_fileName<<Endl;
							*m_ABL_ServicePtr<<DEBUG<<"Stop signal Create in the path  :: : "<<ms_Stopsignalfile.c_str() <<Endl;
							ABL_String ls_command("echo .> ");
							ls_command +=ms_Stopsignalfile.c_str();
							system(ls_command.c_str());
							return false;
						 }
				}
				catch(...)
				{
					rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
					*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
					*m_ABL_ServicePtr<<DEBUG<<"Stop signal Create in the path  :: : "<<ms_Stopsignalfile.c_str() <<Endl;
					ABL_String ls_command("echo .> ");
					ls_command +=ms_Stopsignalfile.c_str();
					system(ls_command.c_str());
					return false;
				}
			}//end of inserting into pm_rating_log

		//Insert Rating A Log into DataBase.		
		int i=0;
		int ln_ErrorNums=0;
		try
		{
		
			int ln_TOT_LOG_COUNT=5;
			{
				double			ln_FileId[ln_TOT_LOG_COUNT];
				ABL_String		ls_AgreementType[ln_TOT_LOG_COUNT];
				double			ln_TotalCdrs[ln_TOT_LOG_COUNT];
				double			ln_TotalRated_cdrs[ln_TOT_LOG_COUNT];
				double			ln_TotalRejected[ln_TOT_LOG_COUNT];
				double			ln_TotalDropped[ln_TOT_LOG_COUNT];
				ABL_DbDate		ld_ProcessStartTime[ln_TOT_LOG_COUNT];
				ABL_DbDate		ld_ProcessEndTime[ln_TOT_LOG_COUNT];
				int			ln_ProcessingTime[ln_TOT_LOG_COUNT];
				int			ln_TotalDuplicate[ln_TOT_LOG_COUNT];	
					
				for(lo_PMJobPtr->gi_ATypeLogMapIterator=lo_PMJobPtr->ga_ATypeLogMap.begin();lo_PMJobPtr->gi_ATypeLogMapIterator!=lo_PMJobPtr->ga_ATypeLogMap.end();lo_PMJobPtr->gi_ATypeLogMapIterator++)
					{				

						lo_PMJobPtr->gi_ATypeLogMapIterator->second.gd_ProcessEndTime.mb_fromSysDate();
						ln_FileId[i]	=	lo_PMJobPtr->gi_ATypeLogMapIterator->second.gn_FileId;
						ls_AgreementType[i]	=	lo_PMJobPtr->gi_ATypeLogMapIterator->second.gs_AgreementType;
						ln_TotalCdrs[i]		=	lo_PMJobPtr->gi_ATypeLogMapIterator->second.gn_TotalCdrs;
						ln_TotalRated_cdrs[i]	=	lo_PMJobPtr->gi_ATypeLogMapIterator->second.gn_TotalRated_cdrs;
						ln_TotalRejected[i]	=	lo_PMJobPtr->gi_ATypeLogMapIterator->second.gn_TotalRejected;
						ln_TotalDropped[i]	=	lo_PMJobPtr->gi_ATypeLogMapIterator->second.gn_TotalDropped;
						ld_ProcessStartTime[i]	=	lo_PMJobPtr->gi_ATypeLogMapIterator->second.gd_ProcessStartTime;
						ld_ProcessEndTime[i]	=	lo_PMJobPtr->gi_ATypeLogMapIterator->second.gd_ProcessEndTime;
						ln_ProcessingTime[i]	=	lo_PMJobPtr->gi_ATypeLogMapIterator->second.gd_ProcessEndTime.mb_getJulianDateTime()-lo_PMJobPtr->gi_ATypeLogMapIterator->second.gd_ProcessStartTime.mb_getJulianDateTime();
						ln_TotalDuplicate[i]	=	lo_PMJobPtr->gi_ATypeLogMapIterator->second.gn_TotalDuplicate;
						i=i+1;
					}
				if (i>0)
					{
						ST_ERROR_DETAILS lr_ErrorDetail[i+1];		 
						ln_ErrorNums=i;
						try
						{	
							ls_sql="INSERT INTO pm_rating_atype_log (FILE_ID,AGREEMENT_TYPE,TOTAL_CDRS,TOTAL_RATED_CDRS,TOTAL_REJECTED,TOTAL_DROPPED,PROCESS_START_TIME,PROCESS_END_TIME,PROCESSING_TIME,TOTAL_DUPLICATE) VALUES (:1,:2,:3,:4,:5,:6,:7,:8,:9,:10)";
							lo_ABLStatement		=	lo_ABLConnection->mb_createStatement(ls_sql);
							lo_ABLStatement.mb_setUpdateCount(i);			
							lo_ABLStatement <<	ln_FileId;
							lo_ABLStatement <<	ls_AgreementType;
							lo_ABLStatement <<	ln_TotalCdrs;
							lo_ABLStatement <<	ln_TotalRated_cdrs;
							lo_ABLStatement <<	ln_TotalRejected;
							lo_ABLStatement <<	ln_TotalDropped;
							lo_ABLStatement <<	ld_ProcessStartTime;
							lo_ABLStatement <<	ld_ProcessEndTime;
							lo_ABLStatement <<	ln_ProcessingTime;
							lo_ABLStatement <<	ln_TotalDuplicate;
							lo_ABLStatement.mb_executeArrayUpdate(&ln_ErrorNums,lr_ErrorDetail);
							lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);							
						}
						catch(ABL_Exception &e)
						{
							lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
							for(int n=0;n<ln_ErrorNums;n++)
								{
									ABL_String lc_ErrorMsg = lr_ErrorDetail[n].m_arrErrorMsg;
									try
										{											
										
											ls_sql=" update pm_rating_atype_log ";
											ls_sql+=" set total_rated_cdrs = nvl(total_rated_cdrs,0) + :1,";
											ls_sql+=" total_rejected = nvl(total_rejected,0) + :2,";
											ls_sql+=" total_dropped = nvl(total_dropped,0) + :3,";
										ls_sql+=" total_duplicate = nvl(total_duplicate,0) + :4";	
  		                        					ls_sql+=" where file_id = :5 and agreement_type = :6";
											lo_ABLStatement	=lo_ABLConnection->mb_createStatement(ls_sql);
											double ln_totalcdrs=ln_TotalRated_cdrs[lr_ErrorDetail[n].m_irowNum]+ln_TotalRejected[lr_ErrorDetail[n].m_irowNum]+ln_TotalDropped[lr_ErrorDetail[n].m_irowNum]+ln_TotalDuplicate[lr_ErrorDetail[n].m_irowNum];										
											lo_ABLStatement.mb_setDouble(1,ln_totalcdrs);
											lo_ABLStatement.mb_setDouble(1,ln_TotalRated_cdrs[lr_ErrorDetail[n].m_irowNum]);
											lo_ABLStatement.mb_setDouble(2,ln_TotalRejected[lr_ErrorDetail[n].m_irowNum]);
											lo_ABLStatement.mb_setDouble(3,ln_TotalDropped[lr_ErrorDetail[n].m_irowNum]);
											lo_ABLStatement.mb_setInt(4,ln_TotalDuplicate[lr_ErrorDetail[n].m_irowNum]);
											lo_ABLStatement.mb_setDouble(5,ln_FileId[lr_ErrorDetail[n].m_irowNum]);
											lo_ABLStatement.mb_setString(6,ls_AgreementType[lr_ErrorDetail[n].m_irowNum]);
											lo_ABLStatement.mb_executeUpdate();
											lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
										}
									catch (ABL_Exception &e)
										{

											std::cout<<e.mb_getMessage()<<std::endl;;
											throw ABL_Exception(1,"Error has came while updating pm_rating_atype_log");
										}
								}
						}
						catch(...)
						{
							rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
							lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
							*m_ABL_ServicePtr<<CRITICAL<<"Exception while inserting record in PM_RATING_ATYPE_LOG : "<<Endl;	
							*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
							ABL_String ls_command("touch ");
							ls_command +=ms_Stopsignalfile;
							system(ls_command.c_str());  
							return false;


						}
					}
				else
					{
						std::cout<<"No reords to insert into PM_RATING_ATYPE_LOG: "<<std::endl;
					}
			}
		}
		catch(...)
		{
			rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
			ABL_String ls_command("touch ");
			ls_command +=ms_Stopsignalfile;
			system(ls_command.c_str()); 	
			*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
			return false;
		}
					
		i=0;

		try
		{
			int ln_TOT_CALLTYPE=30;
			{
	
				int		ln_FileId[ln_TOT_CALLTYPE];
				ABL_String      ls_AgreementType[ln_TOT_CALLTYPE];
				int             ln_CallTypeEvent[ln_TOT_CALLTYPE];

				int		ln_TotalCount[ln_TOT_CALLTYPE];
				double		ln_TotalDuration[ln_TOT_CALLTYPE];
				int             ln_TotalIncCount[ln_TOT_CALLTYPE];
				double          ln_TotalIncDuration[ln_TOT_CALLTYPE];
				int             ln_TotalIncRatedCount[ln_TOT_CALLTYPE];
				double          ln_TotalIncRatedDuration[ln_TOT_CALLTYPE];
				int             ln_TotalIncRejCount[ln_TOT_CALLTYPE];
				double          ln_TotalIncRejDuration[ln_TOT_CALLTYPE];
				int             ln_TotalIncDropCount[ln_TOT_CALLTYPE];
				double          ln_TotalIncDropDuration[ln_TOT_CALLTYPE];
				int             ln_TotalOutCount[ln_TOT_CALLTYPE];
				double          ln_TotalOutDuration[ln_TOT_CALLTYPE];
				int             ln_TotalOutRatedCount[ln_TOT_CALLTYPE];
				double          ln_TotalOutRatedDuration[ln_TOT_CALLTYPE];
				int		ln_TotalOutRejCount[ln_TOT_CALLTYPE];
				double          ln_TotalOutRejDuration[ln_TOT_CALLTYPE];
				int             ln_TotalOutDropCount[ln_TOT_CALLTYPE];
				double          ln_TotalOutDropDuration[ln_TOT_CALLTYPE];
				int             ln_TotalUnknownRejected[ln_TOT_CALLTYPE];
				int             ln_TotalUnknown[ln_TOT_CALLTYPE];

				for ( lo_PMJobPtr->gi_CallTypeCountsMapIterator=lo_PMJobPtr->ga_CallTypeCountsMap.begin() ; lo_PMJobPtr->gi_CallTypeCountsMapIterator != lo_PMJobPtr->ga_CallTypeCountsMap.end(); lo_PMJobPtr->gi_CallTypeCountsMapIterator++ )
				{


					if(lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gn_CallTypeEvent==0)
						{
							continue;
						}

					ln_FileId[i]				=   lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gn_FileId;
					ls_AgreementType[i]			=   lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gs_AgreementType;
					ln_CallTypeEvent[i]			=   lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gn_CallTypeEvent;
					ln_TotalCount[i]			=   lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gn_TotalCount;
					ln_TotalDuration[i]			=   lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gn_TotalDuration;
					ln_TotalIncCount[i]			=   lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gn_TotalIncCount;
					ln_TotalIncDuration[i]		=   lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gn_TotalIncDuration;
					ln_TotalIncRatedCount[i]    =   lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gn_TotalIncRatedCount;
					ln_TotalIncRatedDuration[i]	=   lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gn_TotalIncRatedDuration;
					ln_TotalIncRejCount[i]		=	lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gn_TotalIncRejCount;
					ln_TotalIncRejDuration[i]	=   lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gn_TotalIncRejDuration;
					ln_TotalIncDropCount[i]		=   lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gn_TotalIncDropCount;
					ln_TotalIncDropDuration[i]	=   lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gn_TotalIncDropDuration;
					ln_TotalOutCount[i]			=	lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gn_TotalOutCount;
					ln_TotalOutDuration[i]      =   lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gn_TotalOutDuration;
					ln_TotalOutRatedCount[i]    =	lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gn_TotalOutRatedCount;
					ln_TotalOutRatedDuration[i] =   lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gn_TotalOutRatedDuration;
					ln_TotalOutRejCount[i]		=   lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gn_TotalOutRejCount;
					ln_TotalOutRejDuration[i]	=   lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gn_TotalOutRejDuration;
					ln_TotalOutDropCount[i]     =   lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gn_TotalOutDropCount;
					ln_TotalOutDropDuration[i]  =   lo_PMJobPtr->gi_CallTypeCountsMapIterator->second.gn_TotalOutDropDuration;
					ln_TotalUnknownRejected[i]  =	0;
					ln_TotalUnknown[i]          =	0;				
					i=i+1;
				}
				if(i>0)
				{
					ST_ERROR_DETAILS lr_ErrorDetail[i+1];		 
					ln_ErrorNums=i;
					try
					{	
						ls_sql="INSERT INTO PM_FILEWISE_CALLTYPE_COUNTS (FILE_ID,AGREEMENT_TYPE,CALL_TYPE,TOTAL_COUNT,TOTAL_DURATION,TOTAL_INC_COUNT,TOTAL_INC_DURATION,TOTAL_INC_RATED_COUNT,TOTAL_INC_RATED_DURATION,TOTAL_INC_REJ_COUNT,TOTAL_INC_REJ_DURATION,TOTAL_INC_DROP_COUNT,TOTAL_INC_DROP_DURATION,TOTAL_OUT_COUNT,TOTAL_OUT_DURATION,TOTAL_OUT_RATED_COUNT,TOTAL_OUT_RATED_DURATION,TOTAL_OUT_REJ_COUNT,TOTAL_OUT_REJ_DURATION,TOTAL_OUT_DROP_COUNT,TOTAL_OUT_DROP_DURATION,TOTAL_UNK_REJECTED,TOTAL_UNK_DROPPED)  VALUES (:1,:2,:3,:4,:5,:6,:7,:8,:9,:10,:11,:12,:13,:14,:15,:16,:17,:18,:19,:20,:21,:22,:23)";
						lo_ABLStatement		=	lo_ABLConnection->mb_createStatement(ls_sql);
						lo_ABLStatement.mb_setUpdateCount(i);
						lo_ABLStatement<<ln_FileId;
						lo_ABLStatement<<ls_AgreementType;
						lo_ABLStatement<<ln_CallTypeEvent;
						lo_ABLStatement<<ln_TotalCount;
						lo_ABLStatement<<ln_TotalDuration;
						lo_ABLStatement<<ln_TotalIncCount;
						lo_ABLStatement<<ln_TotalIncDuration;
						lo_ABLStatement<<ln_TotalIncRatedCount;
						lo_ABLStatement<<ln_TotalIncRatedDuration;
						lo_ABLStatement<<ln_TotalIncRejCount;
						lo_ABLStatement<<ln_TotalIncRejDuration;			
						lo_ABLStatement<<ln_TotalIncDropCount;
						lo_ABLStatement<<ln_TotalIncDropDuration;
						lo_ABLStatement<<ln_TotalOutCount;
						lo_ABLStatement<<ln_TotalOutDuration;
						lo_ABLStatement<<ln_TotalOutRatedCount;
						lo_ABLStatement<<ln_TotalOutRatedDuration;
						lo_ABLStatement<<ln_TotalOutRejCount;
						lo_ABLStatement<<ln_TotalOutRejDuration;
						lo_ABLStatement<<ln_TotalOutDropCount;				
						lo_ABLStatement<<ln_TotalOutDropDuration;
						lo_ABLStatement<<ln_TotalUnknownRejected;
						lo_ABLStatement<<ln_TotalUnknown;
						lo_ABLStatement.mb_executeArrayUpdate(&ln_ErrorNums,lr_ErrorDetail);
						lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);			
					}
					catch(ABL_Exception &e)
					{
						lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
						for(int n=0;n<ln_ErrorNums;n++)
						{
							ABL_String lc_ErrorMsg = lr_ErrorDetail[n].m_arrErrorMsg;
							if((lc_ErrorMsg.mb_subStr(0,9)) == "ORA-00001")
							{
								try
								{
									ls_sql="update pm_filewise_calltype_counts a set total_inc_rated_count = nvl(total_inc_rated_count,0) + :1, ";
									ls_sql+="total_inc_rated_duration = nvl(total_inc_rated_duration,0) + :2,";
									ls_sql+="total_inc_rej_count = nvl(total_inc_rej_count,0) + :3,";
									ls_sql+="total_inc_rej_duration = nvl(total_inc_rej_duration,0) + :4,";
									ls_sql+="total_inc_drop_count = nvl(total_inc_drop_count,0) + :5,";
									ls_sql+="total_inc_drop_duration = nvl(total_inc_drop_duration,0) + :6,";
									ls_sql+="total_out_rated_count = nvl(total_out_rated_count,0) + :7, ";
									ls_sql+="total_out_rated_duration = nvl(total_out_rated_duration,0) + :8,";
									ls_sql+="total_out_rej_count = nvl(total_out_rej_count,0) + :9,";
									ls_sql+="total_out_rej_duration = nvl(total_out_rej_duration,0) + :10,";
									ls_sql+="total_out_drop_count = nvl(total_out_drop_count,0) + :11,";
									ls_sql+="total_out_drop_duration = nvl(total_out_drop_duration,0) + :12,";
									ls_sql+="total_unk_rejected = nvl(total_unk_rejected,0) + :13,";
									ls_sql+="total_unk_dropped = nvl(total_unk_dropped,0) + :14 ";
									ls_sql+=" where file_id = :15 and agreement_type = :16 and call_type = :17  ";
									lo_ABLStatement		=	lo_ABLConnection->mb_createStatement(ls_sql);
									lo_ABLStatement.mb_setDouble(1,ln_TotalIncRatedCount[lr_ErrorDetail[n].m_irowNum]);
								lo_ABLStatement.mb_setDouble(2,ln_TotalIncRatedDuration[lr_ErrorDetail[n].m_irowNum]);
									lo_ABLStatement.mb_setDouble(3,ln_TotalIncRejCount[lr_ErrorDetail[n].m_irowNum]);
									lo_ABLStatement.mb_setDouble(4,ln_TotalIncRejDuration[lr_ErrorDetail[n].m_irowNum]);
									lo_ABLStatement.mb_setDouble(5,ln_TotalIncDropCount[lr_ErrorDetail[n].m_irowNum]);
									lo_ABLStatement.mb_setDouble(6,ln_TotalOutDuration[lr_ErrorDetail[n].m_irowNum]);
									lo_ABLStatement.mb_setDouble(7,ln_TotalOutRatedCount[lr_ErrorDetail[n].m_irowNum]);
								lo_ABLStatement.mb_setDouble(8,ln_TotalOutRatedDuration[lr_ErrorDetail[n].m_irowNum]);
									lo_ABLStatement.mb_setDouble(9,ln_TotalOutRejCount[lr_ErrorDetail[n].m_irowNum]);
									lo_ABLStatement.mb_setDouble(10,ln_TotalOutRejDuration[lr_ErrorDetail[n].m_irowNum]);
									lo_ABLStatement.mb_setDouble(11,ln_TotalOutDropCount[lr_ErrorDetail[n].m_irowNum]);
								lo_ABLStatement.mb_setDouble(12,ln_TotalOutDropDuration[lr_ErrorDetail[n].m_irowNum]);
								lo_ABLStatement.mb_setDouble(13,ln_TotalUnknownRejected[lr_ErrorDetail[n].m_irowNum]);
									lo_ABLStatement.mb_setDouble(14,ln_TotalUnknown[lr_ErrorDetail[n].m_irowNum]);
									lo_ABLStatement.mb_setDouble(15,ln_FileId[lr_ErrorDetail[n].m_irowNum]);
									lo_ABLStatement.mb_setString(16,ls_AgreementType[lr_ErrorDetail[n].m_irowNum]);
									lo_ABLStatement.mb_setDouble(17,ln_CallTypeEvent[lr_ErrorDetail[n].m_irowNum]);
									lo_ABLStatement.mb_executeUpdate();
									lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);

								}
								catch (ABL_Exception &e)
								{
									rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
									std::cout<<e.mb_getMessage()<<std::endl;
									return false;
								}
							}
							else
							{
								rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
								*m_ABL_ServicePtr<<CRITICAL<<"Exception while inserting the PM_FILEWISE_CALLTYPE_COUNTS : "<<e.mb_getMessage()<<"for the file "<<lo_PMJobPtr->gs_fileName<<Endl;
								ABL_String ls_command("touch ");
								ls_command +=ms_Stopsignalfile;
								system(ls_command.c_str());  
								return false;
							}
						}

					}
					catch(...)
					{
						rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
						lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
						*m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<"Unknow error while inserting the record in the PM_FILEWISE_CALLTYPE_COUNTS for the file : "<<lo_PMJobPtr->gs_fileName <<Endl;
						*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
						ABL_String ls_command("touch ");
						ls_command +=ms_Stopsignalfile;
						system(ls_command.c_str());  
						return false;
					}				
				
				}
				else
				{
					//std::cout<<"No reords in =lo_PMJobPtr->ga_CallTypeCountsMap: "<<std::endl;
				}
			}
		}
		catch(...)
		{
			rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
			ABL_String ls_command("touch ");
			ls_command +=ms_Stopsignalfile;
			system(ls_command.c_str()); 	
			*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
			return false;
		}	

		
		if (lo_PMJobPtr->gn_RepriceSeqNo!=0) 
		{
			//update pm_reprice_files with the total count for the file
			ls_sql="update pm_reprice_files set total_rated_cdrs = nvl(total_rated_cdrs,0) + :1, "; //(lc_RatedCount-lc_DupCount)
			ls_sql+="total_rejected_cdrs = nvl(total_rejected_cdrs,0) + :2, ";//lc_RejectCount
			ls_sql+="total_dropped_cdrs = nvl(total_dropped_cdrs,0) + :3, "; //lc_DropCount
			ls_sql+="total_duplicate_cdrs = nvl(total_duplicate_cdrs,0) + :4 ";//lc_DupCount
			ls_sql+=" where reprice_seq_no = :5 and file_id = :6 and agreement_type =:7";
			lo_ABLStatement     =	lo_ABLConnection->mb_createStatement(ls_sql);
			lo_ABLStatement.mb_setUInt(1,lo_PMJobPtr->gn_Rated_count);
			lo_ABLStatement.mb_setUInt(2,lo_PMJobPtr->gn_Rejected_count);
			lo_ABLStatement.mb_setUInt(3,lo_PMJobPtr->gn_Dropped_count);
			lo_ABLStatement.mb_setUInt(4,lo_PMJobPtr->gn_Duplicate_count);
			lo_ABLStatement.mb_setUInt(5,lo_PMJobPtr->gn_RepriceSeqNo);
			lo_ABLStatement.mb_setUInt(6,lo_PMJobPtr->gn_InPutFileId);
			lo_ABLStatement.mb_setString(7,lo_PMJobPtr->gs_AgreementType);			
			lo_ABLStatement.mb_executeUpdate();			
			lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);

			ls_sql="update pm_reprice_log set total_rated_cdrs = nvl(total_rated_cdrs,0) + :1, "; //(lc_RatedCount-lc_DupCount)
			ls_sql+="total_rejected_cdrs = nvl(total_rejected_cdrs,0) + :2, ";//lc_RejectCount
			ls_sql+="total_dropped_cdrs = nvl(total_dropped_cdrs,0) + :3, "; //lc_DropCount
			ls_sql+="total_duplicate_cdrs = nvl(total_duplicate_cdrs,0) + :4 ";//lc_DupCount
			ls_sql+=" where reprice_seq_no = :5 ";
			lo_ABLStatement     =	lo_ABLConnection->mb_createStatement(ls_sql);
			lo_ABLStatement.mb_setUInt(1,lo_PMJobPtr->gn_Rated_count);
			lo_ABLStatement.mb_setUInt(2,lo_PMJobPtr->gn_Rejected_count);
			lo_ABLStatement.mb_setUInt(3,lo_PMJobPtr->gn_Dropped_count);
			lo_ABLStatement.mb_setUInt(4,lo_PMJobPtr->gn_Duplicate_count);
			lo_ABLStatement.mb_setUInt(5,lo_PMJobPtr->gn_RepriceSeqNo);
			lo_ABLStatement.mb_executeUpdate();			
			lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);			
			//Update pm_rating log

			ln_insec=0;
			lo_PMJobPtr->ga_RatingLog[0].gd_ProcessEndTime.mb_fromSysDate();
			

			ln_insec=lo_PMJobPtr->ga_RatingLog[0].gd_ProcessEndTime.mb_getJulianDateTime()-lo_PMJobPtr->ga_RatingLog[0].gd_ProcessStartTime.mb_getJulianDateTime();	//lo_PMJobPtr->ga_RatingLog[0].g_ProcessingTimeInSecs;	
			//std::cout<<"Start date: "<<lo_PMJobPtr->ga_RatingLog[0].gd_ProcessStartTime<<" end date: "<<lo_PMJobPtr->ga_RatingLog[0].gd_ProcessEndTime<<" duration: "<<ln_insec <<std::endl;

			ls_sql=	"UPDATE PM_RATING_LOG  SET PROCESS_END_TIME =:1,RECEIVED_ON=:2,PROCESSING_TIME_IN_SECS=:3,summarised=:4,PROCESSED=:5 WHERE CDR_FILE_NAME=:6";
			lo_ABLStatement     =	lo_ABLConnection->mb_createStatement(ls_sql);		
			lo_ABLStatement.mb_setDate(1,lo_PMJobPtr->ga_RatingLog[0].gd_ProcessEndTime);
			lo_ABLStatement.mb_setDate(2,lo_PMJobPtr->gd_DbTimeStamp);
			lo_ABLStatement.mb_setUInt(3,ln_insec);
			lo_ABLStatement.mb_setString(4,"N");
			lo_ABLStatement.mb_setString(5,"Y");
			lo_ABLStatement.mb_setString(6,lo_PMJobPtr->gs_fileName);

			lo_ABLStatement.mb_executeUpdate();			
			lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
			

			// finally update in pm_reprice_files
			lo_PMJobPtr->ga_RatingLog[0].gd_ProcessEndTime.mb_fromSysDate();		
			ln_insec=lo_PMJobPtr->ga_RatingLog[0].gd_ProcessEndTime.mb_getJulianDateTime()-lo_PMJobPtr->ga_RatingLog[0].gd_ProcessStartTime.mb_getJulianDateTime();	

            		ls_sql="update pm_reprice_files set reprice_status=:1,reprice_start_date =:2,reprice_end_date = sysdate,elapsed_time =:3  where reprice_seq_no =:4 and file_id = :5";
			lo_ABLStatement     =	lo_ABLConnection->mb_createStatement(ls_sql);		
			lo_ABLStatement.mb_setString(1,"D");
			lo_ABLStatement.mb_setDate(2,lo_PMJobPtr->ga_RatingLog[0].gd_ProcessStartTime);
			lo_ABLStatement.mb_setUInt(3,ln_insec);
			lo_ABLStatement.mb_setUInt(4,lo_PMJobPtr->gn_RepriceSeqNo);
			lo_ABLStatement.mb_setUInt(5,lo_PMJobPtr->gn_InPutFileId);
			lo_ABLStatement.mb_executeUpdate();			
			lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
			mn_totalfiles_in_rerate_reprice_seq_no=mn_totalfiles_in_rerate_reprice_seq_no+1;
			*m_ABL_ServicePtr<<DEBUG<<"number of files in in global : "<<lo_PMJobPtr->gn_Files_In_Rerate_Reprice_seq_no<<" no of files in local: "<<mn_totalfiles_in_rerate_reprice_seq_no<<Endl;
			if(lo_PMJobPtr->gn_Files_In_Rerate_Reprice_seq_no==mn_totalfiles_in_rerate_reprice_seq_no)
			{
				mn_totalfiles_in_rerate_reprice_seq_no=0;
				ls_sql="UPDATE pm_reprice_log SET status = 'PROC'  WHERE REPRICE_SEQ_NO=:1";
				lo_ABLStatement     =	lo_ABLConnection->mb_createStatement(ls_sql);			
				lo_ABLStatement.mb_setUInt(1,lo_PMJobPtr->gn_RepriceSeqNo);
				lo_ABLStatement.mb_executeUpdate();			
				lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
			}

		}
		else
		{

			lo_PMJobPtr->ga_RatingLog[0].gd_ProcessEndTime.mb_fromSysDate();		
			ln_insec=lo_PMJobPtr->ga_RatingLog[0].gd_ProcessEndTime.mb_getJulianDateTime()-lo_PMJobPtr->ga_RatingLog[0].gd_ProcessStartTime.mb_getJulianDateTime();	
			ls_TempConvert.mb_fromInt(ln_insec);
			ls_sql=	"UPDATE PM_RATING_LOG  SET PROCESS_END_TIME =:1,PROCESSING_TIME_IN_SECS=:2 WHERE CDR_FILE_NAME=:3";
			lo_ABLStatement     =	lo_ABLConnection->mb_createStatement(ls_sql);			
			lo_ABLStatement.mb_setDate(1,lo_PMJobPtr->ga_RatingLog[0].gd_ProcessEndTime);
			lo_ABLStatement.mb_setUInt(2,ln_insec);
			lo_ABLStatement.mb_setString(3,lo_PMJobPtr->gs_fileName);
			lo_ABLStatement.mb_executeUpdate();		
			lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);

		}

		if (lo_PMJobPtr->gs_IsGPRSFile=="NO")
		{
			if (lo_PMJobPtr->gn_RepriceSeqNo==0) 
			{
				if(lo_PMJobPtr->gs_BackupFlag=="Y")
				{
						rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ProcessedFilePath.c_str());
                                                ABL_String l_command("gzip -f ");
                                                l_command +=lo_PMJobPtr->gs_ProcessedFilePath.c_str();
                                                system(l_command.c_str());				
				}
				else
				{		
						unlink(lo_PMJobPtr->gs_SourceFilePath.c_str());				
				}	
			}
		}

      if ( lo_PMJobPtr->gs_FileStatus == "S" )
		{
		                      
	        ls_SQlQuery	=	"select COUNT(1) FROM PM_RATING_ERROR_FILES  WHERE (CDR_FILE_NAME=:1 and STATUS='F') ";
			lo_ABLStatement		=	lo_ABLConnection->mb_createStatement(ls_SQlQuery);		
			lo_ABLStatement.mb_setString(1,lo_PMJobPtr->gs_fileName );
			lo_AB_ResultSet = lo_ABLStatement.mb_executeQuery();
			lo_AB_ResultSet.mb_fetch();
			ln_dupFileIndex= lo_AB_ResultSet.mb_getInt(1);
			lo_ABLStatement.mb_closeResultSet(lo_AB_ResultSet);
			lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
	
			if ( ln_dupFileIndex >= 1 )
			{

                    ls_SQlQuery = "UPDATE PM_RATING_ERROR_FILES SET REPROCESSED_TIME=SYSDATE,ERROR_MESSAGE='Successfully Processed the file',STATUS='S' WHERE CDR_FILE_NAME=:1 AND STATUS='F'";
					lo_ABLStatement = lo_ABLConnection->mb_createStatement(ls_SQlQuery);					
			        lo_ABLStatement.mb_setString(1,lo_PMJobPtr->gs_fileName );
					lo_ABLStatement.mb_executeUpdate();			
					lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);		
			}


		}
     



		lo_ABLConnection->mb_commit();
		*m_ABL_ServicePtr<<DEBUG<<"End of processing for the  file : "<< lo_PMJobPtr->gs_fileName <<Endl;

	}
	catch(ABL_Exception &e)
	{
		rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
		*m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
		ABL_String ls_command("touch ");
		ls_command +=ms_Stopsignalfile;
		system(ls_command.c_str());  		
	    return false;
	}	
	catch(...)
	{
		rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
		ABL_String ls_command("touch ");
		ls_command +=ms_Stopsignalfile;
		system(ls_command.c_str()); 	
		*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}
	return true;		
}
