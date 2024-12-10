#include "PM_InsertRejectedCdrsInDB.h"
#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "ABL_DateTime.h"
#include "ABL_String.h"
#include "ABL_Date.h"
#include "ABL_DbDate.h"
#include "ABL_Blob.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_InsertRejectedCdrsInDB()
{
	return ( (Base_Registry*) new PM_InsertRejectedCdrsInDB);
}
}

PM_InsertRejectedCdrsInDB::PM_InsertRejectedCdrsInDB()
{
	//
}

PM_InsertRejectedCdrsInDB::~PM_InsertRejectedCdrsInDB()
{
	//
}

PM_InsertRejectedCdrsInDB::PM_InsertRejectedCdrsInDB(const PM_InsertRejectedCdrsInDB& p_copyObject)
{
	
	this->m_ABL_ServicePtr			=  	p_copyObject.m_ABL_ServicePtr;	
	this->mn_DB_BULK_INSERT_COUNT	=	p_copyObject.mn_DB_BULK_INSERT_COUNT;	
	this->ms_Stopsignalfile			=	p_copyObject.ms_Stopsignalfile;	

}

Base_Registry* PM_InsertRejectedCdrsInDB::mb_clone()
{
	return ( (Base_Registry*) new PM_InsertRejectedCdrsInDB );
}

ABL_Process* PM_InsertRejectedCdrsInDB::mb_createCopy()
{
	return ( new PM_InsertRejectedCdrsInDB (*this));
}

bool PM_InsertRejectedCdrsInDB::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{	
	try
	{

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

bool PM_InsertRejectedCdrsInDB::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	
	return true;
}
bool PM_InsertRejectedCdrsInDB::mb_stop()
{
	return true;
}

bool PM_InsertRejectedCdrsInDB::mb_process(ABL_Job* &p_ABL_JobPtr)
{	

	PM_Job* lo_PMJobPtr = (PM_Job*)p_ABL_JobPtr;	
	*m_ABL_ServicePtr<<DEBUG<< "Start :" <<lo_PMJobPtr->gs_fileName <<" : "<<lo_PMJobPtr->ga_RejectedCdrs.size()<< Endl;
	if(lo_PMJobPtr->ga_RejectedCdrs.size()==0)
	{
		return true;
	}
	
	ABL_Connection	*lo_ABLConnection;
	ABL_Statement	lo_ABLStatement;
	ABL_ResultSet	lo_ABLResultSet;
	ABL_String		ls_sql;
	int ln_Total_Rej_CDRS=0;
	gr_CallTypeCounts   lr_CallTypeCounts;
	int ln_ErrorNums=0;	
	try
	{
		lo_ABLConnection = lo_PMJobPtr->mb_getConnection();		
		ln_Total_Rej_CDRS=0;
		int ln_TOTAL_REJECTED_CDRS=512;
		if(mn_DB_BULK_INSERT_COUNT>0)
		{
			if(lo_PMJobPtr->ga_RejectedCdrs.size()>mn_DB_BULK_INSERT_COUNT)
			{
					ln_TOTAL_REJECTED_CDRS=mn_DB_BULK_INSERT_COUNT;
			}
			else
			{
				ln_TOTAL_REJECTED_CDRS=lo_PMJobPtr->ga_RejectedCdrs.size();

			}
		}


		{
			double			ln_FileId[ln_TOTAL_REJECTED_CDRS]; 
			double			ln_RecordNo[ln_TOTAL_REJECTED_CDRS]; 
			ABL_String		ls_ErrorCode[ln_TOTAL_REJECTED_CDRS];
			ABL_String		ls_ErrorMessage[ln_TOTAL_REJECTED_CDRS];
			ABL_String		ls_ErrorValue[ln_TOTAL_REJECTED_CDRS];
			ABL_DbDate		ld_RejectedDate[ln_TOTAL_REJECTED_CDRS]; 
			ABL_String		ls_Status[ln_TOTAL_REJECTED_CDRS]; 
			ABL_String		ls_ErrorCdr[ln_TOTAL_REJECTED_CDRS]; 
			ABL_String		ls_AgreementType[ln_TOTAL_REJECTED_CDRS];
			ABL_String		ls_CallType[ln_TOTAL_REJECTED_CDRS];
			ABL_String		ls_CallDirection[ln_TOTAL_REJECTED_CDRS];
			ABL_String		ls_NeCode[ln_TOTAL_REJECTED_CDRS];
			ABL_String		ls_PartnerIdentifier[ln_TOTAL_REJECTED_CDRS];
			ABL_String		ls_PartnerCode[ln_TOTAL_REJECTED_CDRS];
			ABL_String		ls_Poi[ln_TOTAL_REJECTED_CDRS];
			ABL_String		ls_ServiceCode[ln_TOTAL_REJECTED_CDRS];
			ABL_String		ls_RateDirection[ln_TOTAL_REJECTED_CDRS];
			ABL_String		ls_PaymentDirection[ln_TOTAL_REJECTED_CDRS];
			ABL_String		ls_RateUnit[ln_TOTAL_REJECTED_CDRS];
			double			ln_UnitQty[ln_TOTAL_REJECTED_CDRS];
			ABL_String		ls_NumberPlanCode[ln_TOTAL_REJECTED_CDRS];
			ABL_String		ls_TariffPlanCode[ln_TOTAL_REJECTED_CDRS];
			ABL_String		ls_ALong[ln_TOTAL_REJECTED_CDRS];
			ABL_String		ls_OriginRateZone[ln_TOTAL_REJECTED_CDRS];
			ABL_String		ls_BLong[ln_TOTAL_REJECTED_CDRS];
			ABL_String		ls_DestRateZone[ln_TOTAL_REJECTED_CDRS];
			ABL_DbDate		ld_CallDate[ln_TOTAL_REJECTED_CDRS];
			ABL_String		ls_DayCode[ln_TOTAL_REJECTED_CDRS];
			ABL_String		ls_TimeType[ln_TOTAL_REJECTED_CDRS];
			double			ln_RerateSeqNo[ln_TOTAL_REJECTED_CDRS];
			double          ln_CallDuration[ln_TOTAL_REJECTED_CDRS];

			ABL_String      ls_ChronoNum[ln_TOTAL_REJECTED_CDRS];
			double          ln_PartialSeqNum[ln_TOTAL_REJECTED_CDRS];
			
			//Added as per the LTE usage for 4.3 release
			ABL_String	ls_AUserId[ln_TOTAL_REJECTED_CDRS];
			ABL_String	ls_BUserId[ln_TOTAL_REJECTED_CDRS];
			//modification end
			//Added A_USERID, B_USERID into the insert statement as per LTE usage for 4.3 release
			
			ls_sql="INSERT INTO PM_REJECTED_CDRS (FILE_ID,RECORD_NO,ERROR_CODE,ERROR_MESSAGE,ERROR_VALUE,REJECTED_DATE,STATUS,ERROR_CDR,AGREEMENT_TYPE,CALL_TYPE,CALL_DIRECTION,NE_CODE,PARTNER_IDENTIFIER,PARTNER_CODE,POI,SERVICE_CODE,RATE_DIRECTION,PAYMENT_DIRECTION,RATE_UNIT,UNIT_QTY,NUMBER_PLAN_CODE,TARIFF_PLAN_CODE,A_NUMBER,ORIGIN_RATE_ZONE,B_NUMBER,DEST_RATE_ZONE,CALL_DATE,DAY_CODE,TIME_TYPE,RERATE_SEQ_NO,CALL_DURATION,CHRONO_NUM,PARTIAL_SEQ_NUM,A_USERID,B_USERID) VALUES (:1,:2,:3,:4,:5,:6,:7,:8,:9,:10,:11,:12,:13,:14,:15,:16,:17,:18,:19,:20,:21,:22,:23,:24,:25,:26,:27,:28,:29,:30,:31,:32,:33,:34,:35)";
			
			lo_ABLStatement		=	lo_ABLConnection->mb_createStatement(ls_sql);
			lo_ABLStatement.mb_setUpdateCount(ln_TOTAL_REJECTED_CDRS);
			lo_ABLStatement << ln_FileId;
			lo_ABLStatement << ln_RecordNo;
			lo_ABLStatement.mb_setStringArray(ls_ErrorCode,21);
			lo_ABLStatement.mb_setStringArray(ls_ErrorMessage,201);
			lo_ABLStatement.mb_setStringArray(ls_ErrorValue,51);
			lo_ABLStatement << ld_RejectedDate;
			lo_ABLStatement.mb_setStringArray(ls_Status,11); 
			lo_ABLStatement.mb_setStringArray(ls_ErrorCdr,1001); 
			lo_ABLStatement.mb_setStringArray(ls_AgreementType,2);//
			lo_ABLStatement.mb_setStringArray(ls_CallType,2);//
			lo_ABLStatement.mb_setStringArray(ls_CallDirection,2);//
			lo_ABLStatement.mb_setStringArray(ls_NeCode,46);
			lo_ABLStatement.mb_setStringArray(ls_PartnerIdentifier,31);
			lo_ABLStatement.mb_setStringArray(ls_PartnerCode,4);
			lo_ABLStatement.mb_setStringArray(ls_Poi,4);
			lo_ABLStatement.mb_setStringArray(ls_ServiceCode,4);
			lo_ABLStatement.mb_setStringArray(ls_RateDirection,2);//
			lo_ABLStatement.mb_setStringArray(ls_PaymentDirection,2);//
			lo_ABLStatement.mb_setStringArray(ls_RateUnit,2);//
			lo_ABLStatement << ln_UnitQty;
			lo_ABLStatement.mb_setStringArray(ls_NumberPlanCode,6);
			lo_ABLStatement.mb_setStringArray(ls_TariffPlanCode,6);
			lo_ABLStatement.mb_setStringArray(ls_ALong,26);
			lo_ABLStatement.mb_setStringArray(ls_OriginRateZone,6);
			lo_ABLStatement.mb_setStringArray(ls_BLong,26);
			lo_ABLStatement.mb_setStringArray(ls_DestRateZone,6);
			lo_ABLStatement << ld_CallDate;
			lo_ABLStatement.mb_setStringArray(ls_DayCode,4);
			lo_ABLStatement.mb_setStringArray(ls_TimeType,4);
			lo_ABLStatement << ln_RerateSeqNo;
			lo_ABLStatement << ln_CallDuration;

			lo_ABLStatement.mb_setStringArray(ls_ChronoNum,21);
			lo_ABLStatement << ln_PartialSeqNum;

			//Added as per LTE usage for 4.3 release
			lo_ABLStatement.mb_setStringArray(ls_AUserId,66);
			lo_ABLStatement.mb_setStringArray(ls_BUserId,66);
			//modification end

			for(int i=0; i<lo_PMJobPtr->ga_RejectedCdrs.size();i++)
			{
				ln_FileId[ln_Total_Rej_CDRS]=0.0; 
				ln_RecordNo[ln_Total_Rej_CDRS]=0.0; 
				ls_ErrorCode[ln_Total_Rej_CDRS]=" ";
				ls_ErrorMessage[ln_Total_Rej_CDRS]=" ";
				ls_ErrorValue[ln_Total_Rej_CDRS]=" ";
				ls_Status[ln_Total_Rej_CDRS]=" "; 
				ls_ErrorCdr[ln_Total_Rej_CDRS]=" "; 
				ls_AgreementType[ln_Total_Rej_CDRS]=" ";
				ls_CallType[ln_Total_Rej_CDRS]=" ";
				ls_CallDirection[ln_Total_Rej_CDRS]=" ";
				ls_NeCode[ln_Total_Rej_CDRS]=" ";
				ls_PartnerIdentifier[ln_Total_Rej_CDRS]=" ";
				ls_PartnerCode[ln_Total_Rej_CDRS]=" ";
				ls_Poi[ln_Total_Rej_CDRS]=" ";
				ls_ServiceCode[ln_Total_Rej_CDRS]=" ";
				ls_RateDirection[ln_Total_Rej_CDRS]=" ";
				ls_PaymentDirection[ln_Total_Rej_CDRS]=" ";
				ls_RateUnit[ln_Total_Rej_CDRS]=" ";
				ln_UnitQty[ln_Total_Rej_CDRS]=0.0; 
				ls_NumberPlanCode[ln_Total_Rej_CDRS]=" ";
				ls_TariffPlanCode[ln_Total_Rej_CDRS]=" ";
				ls_ALong[ln_Total_Rej_CDRS]=" ";
				ls_OriginRateZone[ln_Total_Rej_CDRS]=" ";
				ls_BLong[ln_Total_Rej_CDRS]=" ";
				ls_DestRateZone[ln_Total_Rej_CDRS]=" ";
				ls_DayCode[ln_Total_Rej_CDRS]=" ";
				ls_TimeType[ln_Total_Rej_CDRS]=" ";
				ln_RerateSeqNo[ln_Total_Rej_CDRS]=0.0; 
				ln_CallDuration[ln_Total_Rej_CDRS]=0.0;

				ls_ChronoNum[ln_Total_Rej_CDRS]=" ";
				ln_PartialSeqNum[ln_Total_Rej_CDRS]=0.0;

				//Added as per LTE usage for 4.3 release
				ls_AUserId[ln_Total_Rej_CDRS]=" ";
				ls_BUserId[ln_Total_Rej_CDRS]=" ";
				//modification end

				ln_FileId[ln_Total_Rej_CDRS]					=	lo_PMJobPtr->ga_RejectedCdrs[i].gn_FileId;
				ln_RecordNo[ln_Total_Rej_CDRS]					=	lo_PMJobPtr->ga_RejectedCdrs[i].gn_RecordNo;
				ls_ErrorCode[ln_Total_Rej_CDRS]					=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_ErrorCode;
				if(ls_ErrorCode[ln_Total_Rej_CDRS]=="")
				{				
					ls_ErrorCode[ln_Total_Rej_CDRS]				=	"ICB";
				}
				
				if(ls_ErrorMessage[ln_Total_Rej_CDRS]=="")
				{					
					ls_ErrorMessage[ln_Total_Rej_CDRS]			=	"";
				}	
				ls_ErrorMessage[ln_Total_Rej_CDRS]				=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_ErrorMessage;
				ls_ErrorValue[ln_Total_Rej_CDRS]				=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_ErrorValue;
				ld_RejectedDate[ln_Total_Rej_CDRS]				=	lo_PMJobPtr->gd_DbTimeStamp;
				
				ls_Status[ln_Total_Rej_CDRS]					=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_Status;
				ls_ErrorCdr[ln_Total_Rej_CDRS]					=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_ErrorCdr	;

				ls_AgreementType[ln_Total_Rej_CDRS]				=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_AgreementType;
                		
				ls_CallType[ln_Total_Rej_CDRS].mb_fromInt(lo_PMJobPtr->ga_RejectedCdrs[i].gn_CallType);								
				ls_CallDirection[ln_Total_Rej_CDRS]				=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_CallDirection;
				ls_NeCode[ln_Total_Rej_CDRS]					=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_NeCode;

				lo_PMJobPtr->ga_RejectedCdrs[i].gs_PartnerIdentifier[lo_PMJobPtr->ga_RejectedCdrs[i].gs_PartnerIdentifier.mb_length()]='\0';

				ls_PartnerIdentifier[ln_Total_Rej_CDRS]				=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_PartnerIdentifier;
				ls_PartnerCode[ln_Total_Rej_CDRS]				=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_PartnerCode;
				ls_Poi[ln_Total_Rej_CDRS]					=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_Poi;
				ls_ServiceCode[ln_Total_Rej_CDRS]				=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_ServiceCode;
				

				ls_RateDirection[ln_Total_Rej_CDRS]				=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_RateDirection;
				ls_PaymentDirection[ln_Total_Rej_CDRS]				=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_PaymentDirection;
				ls_RateUnit[ln_Total_Rej_CDRS]					=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_RateUnit;
				if(lo_PMJobPtr->ga_RejectedCdrs[i].gn_UnitQty<=0)
				{
					ln_UnitQty[ln_Total_Rej_CDRS]				=	0;
				}
				else
				{
					ln_UnitQty[ln_Total_Rej_CDRS]				=	lo_PMJobPtr->ga_RejectedCdrs[i].gn_UnitQty;
				}
				
				ls_NumberPlanCode[ln_Total_Rej_CDRS]				=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_NumberPlanCode;
				ls_TariffPlanCode[ln_Total_Rej_CDRS]				=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_TariffPlanCode;
				ls_ALong[ln_Total_Rej_CDRS]					=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_ALong;
				ls_OriginRateZone[ln_Total_Rej_CDRS]				=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_OriginRateZone;
				ls_BLong[ln_Total_Rej_CDRS]							=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_BLong;
				ls_DestRateZone[ln_Total_Rej_CDRS]				=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_DestRateZone;				
				ld_CallDate[ln_Total_Rej_CDRS]					=	lo_PMJobPtr->ga_RejectedCdrs[i].gd_CallDate;
				ls_DayCode[ln_Total_Rej_CDRS]					=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_DayCode;
				ls_TimeType[ln_Total_Rej_CDRS]					=	lo_PMJobPtr->ga_RejectedCdrs[i].gs_TimeType;
				if (lo_PMJobPtr->gn_RepriceSeqNo<=0)
				{
					ln_RerateSeqNo[ln_Total_Rej_CDRS]			=	0;
				}
				else
				{
					ln_RerateSeqNo[ln_Total_Rej_CDRS]			=	lo_PMJobPtr->gn_RepriceSeqNo;					
				}
				if(lo_PMJobPtr->ga_RejectedCdrs[i].gn_CallDuration<=0)
				{
					ln_CallDuration[ln_Total_Rej_CDRS]=0;
				}
				else
				{
					ln_CallDuration[ln_Total_Rej_CDRS]			=	lo_PMJobPtr->ga_RejectedCdrs[i].gn_CallDuration;
				}
                               ls_ChronoNum[ln_Total_Rej_CDRS]                                  =  lo_PMJobPtr->ga_RejectedCdrs[i].gs_ChronoNum;
                               ln_PartialSeqNum[ln_Total_Rej_CDRS]                              =  lo_PMJobPtr->ga_RejectedCdrs[i].gn_PartialSeqNum;
   			       
				//Added as per LTE usage for 4.3 release
			       	ls_AUserId[ln_Total_Rej_CDRS]					=  lo_PMJobPtr->ga_RejectedCdrs[i].gs_AUserId;
				ls_BUserId[ln_Total_Rej_CDRS]                                   =  lo_PMJobPtr->ga_RejectedCdrs[i].gs_BUserId;	
				//modification end

				 update_CallTypeCounts(lo_PMJobPtr, lo_PMJobPtr->ga_RejectedCdrs[i].gs_AgreementType,lo_PMJobPtr->ga_RejectedCdrs[i].gn_CallType,lo_PMJobPtr->ga_RejectedCdrs[i].gn_CallDuration,lo_PMJobPtr->ga_RejectedCdrs[i].gs_CallDirection);				
				 update_ATypeRatingLog(lo_PMJobPtr, lo_PMJobPtr->ga_RejectedCdrs[i].gs_AgreementType,lo_PMJobPtr->ga_RejectedCdrs[i].gs_ErrorCode);

				ln_Total_Rej_CDRS=ln_Total_Rej_CDRS+1;
				if((ln_Total_Rej_CDRS>0) && (ln_Total_Rej_CDRS>=ln_TOTAL_REJECTED_CDRS))
				{	
					ST_ERROR_DETAILS lr_ErrorDetail[ln_Total_Rej_CDRS+1];	 
					try
					{			
						//Integer number indicating the size of the error details structure		
						ln_ErrorNums=ln_Total_Rej_CDRS;      
						
						lo_ABLStatement.mb_setUpdateCount(ln_Total_Rej_CDRS);						
						lo_ABLStatement.mb_executeArrayUpdate(&ln_ErrorNums,lr_ErrorDetail);									
					}
					catch(ABL_Exception &e)
					{
						*m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;	
						if(ln_ErrorNums!=0)
						{
							for(int n=0;n<ln_ErrorNums;n++)
							{
									ABL_String lc_ErrorMsg = lr_ErrorDetail[n].m_arrErrorMsg;
											
									if((lc_ErrorMsg.mb_subStr(0,9)) == "ORA-00001")
									{
											//not do anything
									}
									else
									{
										rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
										*m_ABL_ServicePtr<<CRITICAL<<"Total Error in Rejected CDRS: " <<ln_ErrorNums<<" Error Message:"<<e.mb_getMessage()<<":"<<lr_ErrorDetail[n].m_arrErrorMsg<<Endl;
										ABL_String ls_command("touch ");
										ls_command +=ms_Stopsignalfile;
										system(ls_command.c_str()); 
										lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);						

										return false;
									}
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
							lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
							return false;
						}
						ln_Total_Rej_CDRS=0;
					}
				}
		
		if((ln_Total_Rej_CDRS>0) && (ln_Total_Rej_CDRS<=ln_TOTAL_REJECTED_CDRS))
		{
			ST_ERROR_DETAILS lr_ErrorDetail[ln_Total_Rej_CDRS+1];	 
			try
			{
				
				//Integer number indicating the size of the error details structure		
				ln_ErrorNums=ln_Total_Rej_CDRS;      
				lo_ABLStatement.mb_setUpdateCount(ln_Total_Rej_CDRS);
				lo_ABLStatement.mb_executeArrayUpdate(&ln_ErrorNums,lr_ErrorDetail);							
				
			}
			catch(ABL_Exception &e)
			{				
				if(ln_ErrorNums!=0)
				{
						for(int n=0;n<ln_ErrorNums;n++)
						{
									ABL_String lc_ErrorMsg = lr_ErrorDetail[n].m_arrErrorMsg;
															
									if((lc_ErrorMsg.mb_subStr(0,9)) == "ORA-00001")
									{
										//not do anything.
											
									}
									else
									{
										rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
										*m_ABL_ServicePtr<<CRITICAL<<"Total Error in Rejected CDRS: " <<ln_ErrorNums<<" Error Message:"<<e.mb_getMessage()<<":"<<lr_ErrorDetail[n].m_arrErrorMsg<<Endl;
										ABL_String ls_command("touch ");
										ls_command +=ms_Stopsignalfile;
										system(ls_command.c_str());  
										lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
										return false;

									}
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
						lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
						return false;
					}

		}

		lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);	
	}//end of block {
		
		*m_ABL_ServicePtr<<DEBUG<<"End  :"<<lo_PMJobPtr->gs_fileName <<": "<<lo_PMJobPtr->ga_RejectedCdrs.size()<< Endl;
										
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

void PM_InsertRejectedCdrsInDB::update_CallTypeCounts(PM_Job * &p_ABL_JobPtr, ABL_String AgreementType, int CallType, double CallDuration, ABL_String CallDirection)
{
		PM_Job* l_PM_Job_Local = (PM_Job*)p_ABL_JobPtr;	

		ABL_String	ls_TempConvert="";
		ABL_String  ls_agreementtype_calltype=AgreementType;
		ls_TempConvert.mb_fromDouble(CallType);
		ls_agreementtype_calltype+=ls_TempConvert;
		l_PM_Job_Local->gi_CallTypeCountsMapIterator=l_PM_Job_Local->ga_CallTypeCountsMap.find(ls_agreementtype_calltype);
		if(l_PM_Job_Local->gi_CallTypeCountsMapIterator!=l_PM_Job_Local->ga_CallTypeCountsMap.end())
		{

			if(CallDirection=="I")
			{
				l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalIncRejCount=l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalIncRejCount+1;
				l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalIncRejDuration=l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalIncRejDuration +CallDuration;               
			}
			else if(CallDirection=="O")
			{
				l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalOutRejCount =l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalOutRejCount+1;
				l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalOutRejDuration=l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalOutRejDuration+CallDuration;
			}
			else
			{
				*m_ABL_ServicePtr<<DEBUG<<"Call Direction is not present: "<<Endl;
			}
			
		}
		else
		{
			//std::cout<<"not found record for  gn_TotalIncRejCount and  gn_TotalOutRejCount in ga_CallTypeCountsMap: "<<ls_agreementtype_calltype<<std::endl;
		}

}

void PM_InsertRejectedCdrsInDB::update_ATypeRatingLog(PM_Job * &p_ABL_JobPtr, ABL_String AgreementType,ABL_String pError_code)
{
		PM_Job* l_PM_Job_Local = (PM_Job*)p_ABL_JobPtr;
		l_PM_Job_Local->gi_ATypeLogMapIterator=l_PM_Job_Local->ga_ATypeLogMap.find(AgreementType);
		if(l_PM_Job_Local->gi_ATypeLogMapIterator!=l_PM_Job_Local->ga_ATypeLogMap.end())
		{			
			l_PM_Job_Local->gi_ATypeLogMapIterator->second.gn_TotalRejected=l_PM_Job_Local->gi_ATypeLogMapIterator->second.gn_TotalRejected+1;			
		}
		if(pError_code=="RATE-DUPEVENT")
		{
			l_PM_Job_Local->gi_ATypeLogMapIterator->second.gn_TotalDuplicate=l_PM_Job_Local->gi_ATypeLogMapIterator->second.gn_TotalDuplicate+1;			
		}


}
