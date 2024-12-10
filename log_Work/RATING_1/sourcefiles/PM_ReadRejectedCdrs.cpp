#include "PM_ReadRejectedCdrs.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_ReadRejectedCdrs()
{
	return ( (Base_Registry*) new PM_ReadRejectedCdrs);
}
}
/* Default constructor */
PM_ReadRejectedCdrs::PM_ReadRejectedCdrs()
{
	//
}
/* Default distructor */
PM_ReadRejectedCdrs::~PM_ReadRejectedCdrs()
{
	//
}

PM_ReadRejectedCdrs::PM_ReadRejectedCdrs(const PM_ReadRejectedCdrs& p_copyObject)
{	
	this->m_ABL_ServicePtr				=	p_copyObject.m_ABL_ServicePtr;
	this->ms_directoryName				=	p_copyObject.ms_directoryName;
	this->ms_cdrFileName				=	p_copyObject.ms_cdrFileName;
	this->ms_rawCdrFileName				=	p_copyObject.ms_rawCdrFileName;
	this->ms_rawCdr						=	p_copyObject.ms_rawCdr;
	this->ms_Stopsignalfile				=	p_copyObject.ms_Stopsignalfile;
}

Base_Registry* PM_ReadRejectedCdrs::mb_clone()
{
	return ( (Base_Registry*) new PM_ReadRejectedCdrs );
}

ABL_Process* PM_ReadRejectedCdrs::mb_createCopy()
{
	return ( new PM_ReadRejectedCdrs (*this));
}

bool PM_ReadRejectedCdrs::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{
	
	try
	{
		m_ABL_ServicePtr			= p_ABL_ServicePtr;
		p_ABL_AgentCommunicatorPtr->mb_getParameter("STOP_FILE",ms_Stopsignalfile);
		ms_directoryName = m_ABL_ServicePtr->mb_getParameterValue("CDR_FOLDER");	
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
		*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		ABL_String ls_command("touch ");
		ls_command +=ms_Stopsignalfile;
		system(ls_command.c_str()); 	
		return false;
	}

 	return true;
}

bool PM_ReadRejectedCdrs::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	return true;
}

bool PM_ReadRejectedCdrs::mb_process(ABL_Job* &p_ABL_JobPtr)
{

	PM_Job* lo_PMJobPtr    = (PM_Job*)p_ABL_JobPtr;	
	*m_ABL_ServicePtr << DEBUG << "Get cdrs rerate from the PM_REJECTED_CDRS Table : " << Endl;

	gr_RatingLog lr_RatingLog;	

	//ABL_String ls_CdrValue ;	
	lo_PMJobPtr->gn_TotalCDRS_In_File=0;
	
	ABL_Connection	*lo_ABLConnection;
	ABL_Statement	lo_ABLStatement;
	ABL_ResultSet	lo_ABLResultSet;
	ABL_String	    ls_sql;	
	ABL_String		ls_ErrCode;
	ABL_String		ls_ErrMesg;

	const std::string ls_delimit="|";
	std::vector<std::string> lv_tokens;
	ABL_String ls_RepriceLevel="";
	ABL_String ls_RerateSeqNo="";
	ABL_String ls_Agreementtype="";
    ABL_String ls_SourceType="";
	unsigned int ln_RejectedCdrCount=0;
	ABL_String ls_tempValueofnumeric = "";
	try
	{
		lo_PMJobPtr->gs_AgreementType="";
		lo_PMJobPtr->gn_InPutFileId =0;
		lo_PMJobPtr->gn_RepriceSeqNo=0;

		lo_ABLConnection=lo_PMJobPtr->mb_getConnection();
		tokenize(lo_PMJobPtr->gs_fileName.c_str(),lv_tokens,ls_delimit);

		char lc_TempCallDate[20];
		memset(lc_TempCallDate,'\0',sizeof(lc_TempCallDate));
		strcpy(lc_TempCallDate,lv_tokens[4].c_str());
		unsigned int ln_FileID=atoi(lv_tokens[3].c_str());
		unsigned int ln_RerateSeqNo=atoi(lv_tokens[0].c_str());

		ABL_DbDate	ld_FirstCalledDate(lc_TempCallDate,YYYYMMDDHH24MISS);
		memset(lc_TempCallDate,'\0',sizeof(lc_TempCallDate));
		strcpy(lc_TempCallDate,lv_tokens[5].c_str());
		ABL_DbDate		ld_LastCalledDate(lc_TempCallDate,YYYYMMDDHH24MISS);
		ls_SourceType = lv_tokens[6];

		ABL_DateTime ld_FirstCalledDateTime = ld_FirstCalledDate;
		ABL_DateTime ld_LastCalledDateTime = ld_LastCalledDate;

		ABL_String ls_FirstCalledDate = "";
		ABL_String ls_LastCalledDate = "";
		ls_RepriceLevel="";
		ABL_String ls_FileID = "";
		ls_Agreementtype="";
		ls_RepriceLevel=lv_tokens[1];

		ls_Agreementtype=lv_tokens[2];
		lo_PMJobPtr->gn_InPutFileId =ln_FileID;
		lo_PMJobPtr->gn_RepriceSeqNo=ln_RerateSeqNo;
		lo_PMJobPtr->gs_AgreementType=ls_Agreementtype;

	

		ls_sql="select CDR_FILE_NAME ,RECEIVED_ON,PROCESS_START_TIME,PROCESS_END_TIME,PROCESSING_TIME_IN_SECS,ST_CHRONO,ED_CHRONO,";
		ls_sql+="FIRST_CALL_DT_TIME ,LAST_CALL_DT_TIME,TOTAL_EVENTS,INC_TOTAL_EVENTS,INC_RATED_EVENTS,INC_DROPPED_EVENTS,";
		ls_sql+="INC_REJECTED_EVENTS,OUT_TOTAL_EVENTS,OUT_RATED_EVENTS,OUT_DROPPED_EVENTS,OUT_REJECTED_EVENTS,PROCESSED,FILE_ID,";
		ls_sql+="SUMMARISED,RECONCILED from pm_rating_log where file_id = :1";

		lo_ABLStatement		=	lo_ABLConnection->mb_createStatement(ls_sql);	
		lo_ABLStatement.mb_setUInt(1,ln_FileID);
		lo_ABLResultSet	=lo_ABLStatement.mb_executeQuery();
		while(lo_ABLResultSet.mb_fetch())
		{
			lr_RatingLog.gs_CdrFileName				=	lo_ABLResultSet.mb_getString(1);
			lo_PMJobPtr->gs_fileName				=	lr_RatingLog.gs_CdrFileName;
			lr_RatingLog.gd_ReceivedOn				=	lo_ABLResultSet.mb_getDate(2);	
			lr_RatingLog.gd_ProcessStartTime        =	lo_ABLResultSet.mb_getDate(3);
			lr_RatingLog.gd_ProcessEndTime			=	lo_ABLResultSet.mb_getDate(4);
			lr_RatingLog.gn_ProcessingTimeInSecs	=	lo_ABLResultSet.mb_getInt64(5);
			lr_RatingLog.gs_Chrono					=	lo_ABLResultSet.mb_getString(6);
			lr_RatingLog.gs_EdChrono				=	lo_ABLResultSet.mb_getString(7);
			lr_RatingLog.gd_FirstCallDtTime			=	lo_ABLResultSet.mb_getDate(8);
			lr_RatingLog.gd_LastCallDtTime			=	lo_ABLResultSet.mb_getDate(9);
			lr_RatingLog.gn_TotalEvents				=	lo_ABLResultSet.mb_getInt64(10);
			lr_RatingLog.gn_IncTotalEvents			=	lo_ABLResultSet.mb_getInt64(11);
			lr_RatingLog.gn_IncRatedEvents			=	lo_ABLResultSet.mb_getInt64(12);
			lr_RatingLog.gn_IncDroppedEvents		=	lo_ABLResultSet.mb_getInt64(13);
			lr_RatingLog.gn_IncRejectedEvents		=   lo_ABLResultSet.mb_getInt64(14);
			lr_RatingLog.gn_OutTotalEvents			=	lo_ABLResultSet.mb_getInt64(15);
			lr_RatingLog.gn_OutRatedEvents			=	lo_ABLResultSet.mb_getInt64(16);
			lr_RatingLog.gn_OutDroppedEvents		=	lo_ABLResultSet.mb_getInt64(17);
			lr_RatingLog.gn_OutRejectedEvents		=	lo_ABLResultSet.mb_getInt64(18);
			lr_RatingLog.gs_Processed				=	lo_ABLResultSet.mb_getString(19);
			lr_RatingLog.gn_FileId					=	lo_ABLResultSet.mb_getInt64(20); 
			lr_RatingLog.gs_Summarised				=	"N";
			lr_RatingLog.gs_Reconciled				=	"N";
			lo_PMJobPtr->ga_RatingLog.push_back(lr_RatingLog);		
		}	
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);

		ls_RerateSeqNo.mb_fromInt64(ln_RerateSeqNo);
		//get file details
		ls_ErrMesg = "Rerate Seq=> ";
		ls_ErrMesg+=ls_RerateSeqNo;
		ls_ErrMesg+=":File Name => ";
		ls_ErrMesg+=lr_RatingLog.gs_CdrFileName;
		ls_ErrMesg+=", First Call Date => ";
		ls_ErrMesg+=lr_RatingLog.gd_FirstCallDtTime.mb_toString(YYYYMMDDHH24MISS);
		ls_ErrMesg+=", Last Call Date => ";
		ls_ErrMesg+=lr_RatingLog.gd_LastCallDtTime.mb_toString(YYYYMMDDHH24MISS);
		*m_ABL_ServicePtr <<DEBUG<<ls_ErrMesg<< Endl;

		/* first call date time should not be > last call date time */

		if (lr_RatingLog.gd_FirstCallDtTime > lr_RatingLog.gd_LastCallDtTime)
		{
			*m_ABL_ServicePtr << CRITICAL<<"Rerate Seq no: "<<ls_RerateSeqNo<<" :Error - first call date "<<lr_RatingLog.gd_FirstCallDtTime.mb_toCharText(YYYYMMDDHH24MISS)<<" > than last call date "<<lr_RatingLog.gd_LastCallDtTime.mb_toCharText(YYYYMMDDHH24MISS)<<" . Ignore this file and rerate next file"<< Endl;
			return false;
		}

		if (lr_RatingLog.gd_FirstCallDtTime > ld_LastCalledDateTime || ld_FirstCalledDateTime > lr_RatingLog.gd_LastCallDtTime)
		{
			ls_ErrMesg = "Rerate Seq=> ";
			ls_ErrMesg+=ls_RerateSeqNo;
			ls_ErrMesg+=" :File call dates (First call time=> ";
			ls_ErrMesg+=lr_RatingLog.gd_FirstCallDtTime.mb_toString(YYYYMMDDHH24MISS);
			ls_ErrMesg+=";Last call time=> ";
			ls_ErrMesg+=lr_RatingLog.gd_LastCallDtTime.mb_toString(YYYYMMDDHH24MISS);
			ls_ErrMesg+=" beyond reprice call dates (First call time=> ";
			ls_ErrMesg+=ld_FirstCalledDate.mb_toString(YYYYMMDDHH24MISS);
			ls_ErrMesg+="; Last call time=> ";
			ls_ErrMesg+=ld_LastCalledDate.mb_toString(YYYYMMDDHH24MISS);
			*m_ABL_ServicePtr << CRITICAL<<ls_ErrMesg<< Endl;
			return false;
		}

	   /*****************************************************************
		* step 2: bulk fetch all the rejected cdrs for the file id
		*         which are submitted for rerating
		*****************************************************************/
		/*ls_ErrCode = "REPRICE-3.14";
		ls_ErrMesg = "....File Id => ";
		ls_ErrMesg+=ln_RepriceSeqNo;
		ls_ErrMesg+=":Fetch cdrs between ";
		ls_ErrMesg+=lr_RatingLog.gd_FirstCallDtTime.mb_toString(YYYYMMDDHH24MISS);
		ls_ErrMesg+=" and ";
		ls_ErrMesg+=lr_RatingLog.gd_LastCallDtTime.mb_toString(YYYYMMDDHH24MISS);
		*m_ABL_ServicePtr <<DEBUG<<"ErrCode: "<< ls_ErrCode<<" ErrMesg: "<<ls_ErrMesg<< Endl; */


              if(strcmp(ls_SourceType.c_str(),"R")==0)
			{
		ls_sql="SELECT ";
		ls_sql+=lv_tokens[3];
		ls_sql+=",rownum, error_cdr, 'N' from (SELECT * FROM PM_REJECTED_CDRS WHERE file_id = ";
		ls_sql+=lv_tokens[3];
		ls_sql+=" AND TO_DATE(TO_CHAR(CALL_DATE,'YYYYMMDDHH24MISS'),'YYYYMMDDHH24MISS') >= to_date(nvl('";
		ls_sql+=lr_RatingLog.gd_FirstCallDtTime.mb_toString(YYYYMMDDHH24MISS);
		ls_sql+="','";
		ls_sql+=ld_FirstCalledDate.mb_toString(YYYYMMDDHH24MISS);
		ls_sql+="'),'YYYYMMDDHH24MISS') AND TO_DATE(TO_CHAR(CALL_DATE,'YYYYMMDDHH24MISS'),'YYYYMMDDHH24MISS') <= to_date(nvl('";
		ls_sql+=lr_RatingLog.gd_LastCallDtTime.mb_toString(YYYYMMDDHH24MISS);
		ls_sql+="','";
		ls_sql+=ld_LastCalledDate.mb_toString(YYYYMMDDHH24MISS);
		ls_sql+="'),'YYYYMMDDHH24MISS')) WHERE RERATE_SEQ_NO = :1";
			}
			else
		{
    ls_sql="SELECT ";
		ls_sql+=lv_tokens[3];
		ls_sql+=",rownum, error_cdr, 'N' from (SELECT * FROM PM_DUPLICATE_CDRS WHERE file_id = ";
		ls_sql+=lv_tokens[3];
		ls_sql+=" AND TO_DATE(TO_CHAR(CALL_DATE,'YYYYMMDDHH24MISS'),'YYYYMMDDHH24MISS') >= to_date(nvl('";
		ls_sql+=lr_RatingLog.gd_FirstCallDtTime.mb_toString(YYYYMMDDHH24MISS);
		ls_sql+="','";
		ls_sql+=ld_FirstCalledDate.mb_toString(YYYYMMDDHH24MISS);
		ls_sql+="'),'YYYYMMDDHH24MISS') AND TO_DATE(TO_CHAR(CALL_DATE,'YYYYMMDDHH24MISS'),'YYYYMMDDHH24MISS') <= to_date(nvl('";
		ls_sql+=lr_RatingLog.gd_LastCallDtTime.mb_toString(YYYYMMDDHH24MISS);
		ls_sql+="','";
		ls_sql+=ld_LastCalledDate.mb_toString(YYYYMMDDHH24MISS);
		ls_sql+="'),'YYYYMMDDHH24MISS')) WHERE RERATE_SEQ_NO = :1";
		}

		lo_ABLStatement		=	lo_ABLConnection->mb_createStatement(ls_sql);	
		lo_ABLStatement.mb_setUInt(1,ln_RerateSeqNo);
		lo_ABLResultSet	=lo_ABLStatement.mb_executeQuery();
		/* step 2: insert into pm raw cdrs	*/
		ls_ErrMesg = "Rerate Seq=>";
		ls_ErrMesg+=ls_RerateSeqNo;
		ls_ErrMesg+=":File Id=>";
		ls_ErrMesg+=lv_tokens[3];
		ls_ErrMesg+=":Bulk submit rejected cdrs for rating from :";
		ls_ErrMesg+=lr_RatingLog.gs_CdrFileName;
		*m_ABL_ServicePtr <<DEBUG<<ls_ErrMesg<< Endl;

		while(lo_ABLResultSet.mb_fetch())
		{
			lo_PMJobPtr->ga_RawCDRSVector.push_back(lo_ABLResultSet.mb_getString(3));
		}

		if (lo_PMJobPtr->ga_RawCDRSVector.size()== 0) 
		{
		   ls_ErrMesg = "File Id => ";
		   ls_ErrMesg+=lv_tokens[3];
		   ls_ErrMesg+="..Rerate Seq=> ";
		   ls_ErrMesg+=ls_RerateSeqNo;
		   ls_ErrMesg+=" :No cdrs to rerate from ";
		   ls_ErrMesg+=lr_RatingLog.gs_CdrFileName.c_str();
		   *m_ABL_ServicePtr <<CRITICAL<<ls_ErrMesg<<": "<<ls_sql<< Endl;
			return false;          
		}

		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);

		// delete the rejected cdrs

           if(strcmp(ls_SourceType.c_str(),"R")==0)
			{
		ls_sql="delete from (select * from pm_rejected_cdrs where file_id=:1 ";
		ls_sql+="and call_date >= nvl(:2,:3) and call_date <= nvl(:4,:5) ";
		ls_sql+="and rerate_seq_no=:6)";
			}
			else
		{
        ls_sql="delete from (select * from pm_duplicate_cdrs where file_id=:1 ";
		ls_sql+="and call_date >= nvl(:2,:3) and call_date <= nvl(:4,:5) ";
		ls_sql+="and rerate_seq_no=:6)";
		}
 
		ABL_Statement	lo_Deletecdrs_ABLStatement;
		lo_Deletecdrs_ABLStatement = lo_ABLConnection->mb_createStatement(ls_sql);	
		lo_Deletecdrs_ABLStatement.mb_setUInt(1,ln_FileID);
		lo_Deletecdrs_ABLStatement.mb_setDate(2,lr_RatingLog.gd_FirstCallDtTime);
		lo_Deletecdrs_ABLStatement.mb_setDate(3,ld_FirstCalledDate);
		lo_Deletecdrs_ABLStatement.mb_setDate(4,lr_RatingLog.gd_LastCallDtTime);
		lo_Deletecdrs_ABLStatement.mb_setDate(5,ld_LastCalledDate);

		lo_Deletecdrs_ABLStatement.mb_setUInt(6,ln_RerateSeqNo);
		lo_Deletecdrs_ABLStatement.mb_executeUpdate();

		ln_RejectedCdrCount=lo_Deletecdrs_ABLStatement.mb_getAffectedRowsCount ();
		lo_ABLConnection->mb_terminateStatement(lo_Deletecdrs_ABLStatement);

		 if (ln_RejectedCdrCount != lo_PMJobPtr->ga_RawCDRSVector.size()) 
		{

			ls_ErrMesg = "Rerate Seq=> ";
			ls_ErrMesg+= ls_RerateSeqNo;
			ls_ErrMesg+= "....File Id => ";
			ls_ErrMesg+=lv_tokens[3];
			ls_ErrMesg+=":Rows submitted for Rerating (";
			ls_tempValueofnumeric.mb_fromInt64(lo_PMJobPtr->ga_RawCDRSVector.size());
			ls_ErrMesg+=") is not equal to rows deleted (";
			ls_tempValueofnumeric.mb_fromInt64(ln_RejectedCdrCount);
			ls_ErrMesg+=ls_tempValueofnumeric;
			ls_ErrMesg+=")";
			*m_ABL_ServicePtr <<CRITICAL<<ls_ErrMesg<< Endl;
			return false;

		}

		ls_ErrMesg = "File Id => ";
		ls_ErrMesg+=lv_tokens[3];
		ls_ErrMesg+=":Deleted ";
		ls_tempValueofnumeric.mb_fromInt64(ln_RejectedCdrCount);
		ls_ErrMesg+=ls_tempValueofnumeric;
		ls_ErrMesg+=" cdrs for Rerate seq no => ";
		ls_ErrMesg+=lv_tokens[0];

		*m_ABL_ServicePtr <<DEBUG<<ls_ErrMesg<< Endl;

		 if(strcmp(ls_SourceType.c_str(),"R")==0)
			{

	   /* Reuse the file id of the file processed earlier. */
		ls_sql=" update pm_rating_atype_log set total_rejected=total_rejected-:1";
		ls_sql+=" where file_id = :2 and agreement_type = :3";

			}
			else
		{
        /* Reuse the file id of the file processed earlier. */
		ls_sql=" update pm_rating_atype_log set total_dropped=total_dropped-:1";
		ls_sql+=" where file_id = :2 and agreement_type = :3";
		}

		try
		{
		ABL_Statement	lo_UpdateAtypelog_ABLStatement;
		lo_UpdateAtypelog_ABLStatement	=lo_ABLConnection->mb_createStatement(ls_sql);	
		
		lo_UpdateAtypelog_ABLStatement.mb_setUInt(1,ln_RejectedCdrCount);
		lo_UpdateAtypelog_ABLStatement.mb_setUInt(2,ln_FileID);
		lo_UpdateAtypelog_ABLStatement.mb_setString(3,ls_Agreementtype);
		lo_UpdateAtypelog_ABLStatement.mb_executeUpdate();
		lo_ABLConnection->mb_terminateStatement(lo_UpdateAtypelog_ABLStatement);
		
		}
		catch(ABL_Exception &e)
		{
			*m_ABL_ServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;	
			 ABL_String ls_command("touch ");
			 ls_command +=ms_Stopsignalfile;
			 system(ls_command.c_str());  
			 return false;
		}

		ls_sql=" select file_id, agreement_type, total_cdrs,total_rated_cdrs,total_rejected, total_dropped from pm_rating_atype_log";
		ls_sql+=" where file_id = :1 and agreement_type = :2";
		
		ABL_Statement	lo_SelectAtypelog_ABLStatement;
		ABL_ResultSet	lo_SelectAtypelog_ABLResultSet;
		lo_SelectAtypelog_ABLStatement		=	lo_ABLConnection->mb_createStatement(ls_sql);	
		
		lo_SelectAtypelog_ABLStatement.mb_setUInt(1,ln_FileID);
		lo_SelectAtypelog_ABLStatement.mb_setString(2,ls_Agreementtype);
		lo_SelectAtypelog_ABLResultSet = lo_SelectAtypelog_ABLStatement.mb_executeQuery();

		ABL_String ls_TotalCDRs ="";
		ABL_String ls_Total_Rated_CDRs ="";
		ABL_String ls_Total_Rejected ="";
		ABL_String ls_Total_Dropped ="";

		while (lo_SelectAtypelog_ABLResultSet.mb_fetch())
		{
			
			ls_TotalCDRs.mb_fromInt64(lo_SelectAtypelog_ABLResultSet.mb_getInt64(3));
			ls_Total_Rated_CDRs.mb_fromInt64(lo_SelectAtypelog_ABLResultSet.mb_getInt64(4));
			ls_Total_Rejected = lo_SelectAtypelog_ABLResultSet.mb_getString(5);
			ls_Total_Dropped.mb_fromInt64(lo_SelectAtypelog_ABLResultSet.mb_getInt64(6));
			
			ls_ErrMesg = "Rerate Seq=> ";
			ls_ErrMesg+= ls_RerateSeqNo;
			ls_ErrMesg+= "....File Id => ";
			ls_ErrMesg+=lv_tokens[3];
			ls_ErrMesg+=":Agreement Type=>";
			ls_ErrMesg+=ls_Agreementtype;
			ls_ErrMesg+=";Counts before rerating::";
			ls_ErrMesg+=";Total=>";
			ls_ErrMesg+=ls_TotalCDRs;
			ls_ErrMesg+=";Rated=>";
			ls_ErrMesg+=ls_Total_Rated_CDRs;
			ls_ErrMesg+=";Rejected=>";
			ls_ErrMesg+=ls_Total_Rejected;
			ls_ErrMesg+=";Dropped=>";
			ls_ErrMesg+=ls_Total_Dropped;
			*m_ABL_ServicePtr <<DEBUG<<ls_ErrMesg<< Endl;

		}
                lo_SelectAtypelog_ABLStatement.mb_closeResultSet(lo_SelectAtypelog_ABLResultSet)       ;
                lo_ABLConnection->mb_terminateStatement(lo_SelectAtypelog_ABLStatement);

		//lo_ABLConnection->mb_terminateStatement(lo_SelectAtypelog_ABLResultSet);

		*m_ABL_ServicePtr << DEBUG << "End of Getting rejected cdrs from the REJECTION/DUPICATE Table Total cdrs : " << lo_PMJobPtr->ga_RawCDRSVector.size()<< Endl;
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

bool PM_ReadRejectedCdrs::mb_stop()
{
	return true;
}

/*Fuction to tokenize a string.*/
void PM_ReadRejectedCdrs::tokenize(const std::string& in_str,std::vector<std::string>& lv_tokens,const std::string& in_delimiters )
{
	std::stringstream l_stringStream(in_str);
	std::string ls_tokenString;
	while(std::getline(l_stringStream,ls_tokenString,in_delimiters[0]))
	{
		lv_tokens.push_back(ls_tokenString);
	}
}
