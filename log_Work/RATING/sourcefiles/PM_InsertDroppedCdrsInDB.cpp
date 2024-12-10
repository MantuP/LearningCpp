#include "PM_InsertDroppedCdrsInDB.h"
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
Base_Registry* gb_getPM_InsertDroppedCdrsInDB()
{
	return ( (Base_Registry*) new PM_InsertDroppedCdrsInDB);
}
}

PM_InsertDroppedCdrsInDB::PM_InsertDroppedCdrsInDB()
{
	//
}

PM_InsertDroppedCdrsInDB::~PM_InsertDroppedCdrsInDB()
{
	//
}

PM_InsertDroppedCdrsInDB::PM_InsertDroppedCdrsInDB(const PM_InsertDroppedCdrsInDB& p_copyObject)
{
	this->m_ABL_ServicePtr			=	p_copyObject.m_ABL_ServicePtr;
	this->mn_DB_BULK_INSERT_COUNT	=	p_copyObject.mn_DB_BULK_INSERT_COUNT;	
	this->ms_Stopsignalfile			=	p_copyObject.ms_Stopsignalfile;	
	
}

Base_Registry* PM_InsertDroppedCdrsInDB::mb_clone()
{
	return ( (Base_Registry*) new PM_InsertDroppedCdrsInDB );
}

ABL_Process* PM_InsertDroppedCdrsInDB::mb_createCopy()
{
	return ( new PM_InsertDroppedCdrsInDB (*this));
}

bool PM_InsertDroppedCdrsInDB::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
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

bool PM_InsertDroppedCdrsInDB::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	
	return true;
}
bool PM_InsertDroppedCdrsInDB::mb_stop()
{
	return true;
}

bool PM_InsertDroppedCdrsInDB::mb_process(ABL_Job* &p_ABL_JobPtr)
{	
	
	PM_Job* lo_PMJobPtr = (PM_Job*)p_ABL_JobPtr;		
	*m_ABL_ServicePtr<<DEBUG<<"Start :" <<lo_PMJobPtr->gs_fileName <<" : "<<lo_PMJobPtr->ga_DroppedCdr.size()<< Endl;
	if(lo_PMJobPtr->ga_DroppedCdr.size()==0)
	{
		*m_ABL_ServicePtr<<DEBUG<<"End  :"<< lo_PMJobPtr->gs_fileName <<": "<<lo_PMJobPtr->ga_DroppedCdr.size()<< Endl;
			return true;
	}

	ABL_Connection	*lo_ABLConnection;
	ABL_Statement	lo_ABLStatement;
	ABL_ResultSet	lo_AB_ResultSet;
	ABL_String	ls_sql;
	ABL_String      ls_SQlQuery;
	ABL_String	ls_TempDate;
	ABL_String	ls_TempConvert; 
	int		ln_insec;
	int		ln_ErrorNums=0;

	try
	{
	
			
			lo_ABLConnection = lo_PMJobPtr->mb_getConnection();		
			
			//Insert Dropped CDR into DataBase.
			double ln_CallDuration;
			int ln_DroopedCount=0;	
			int ln_TOTAL_DROPPED_CDRS=100;
			if(mn_DB_BULK_INSERT_COUNT>0)
			{
				ln_TOTAL_DROPPED_CDRS=mn_DB_BULK_INSERT_COUNT;

			}

			if(mn_DB_BULK_INSERT_COUNT>0)
			{
				if(lo_PMJobPtr->ga_DroppedCdr.size()>mn_DB_BULK_INSERT_COUNT)
				{
						ln_TOTAL_DROPPED_CDRS=mn_DB_BULK_INSERT_COUNT;
				}
				else
				{
					ln_TOTAL_DROPPED_CDRS=lo_PMJobPtr->ga_DroppedCdr.size();

				}
			}

			{
				double			ln_InputFileId[ln_TOTAL_DROPPED_CDRS];
				double  		ln_RecordNo[ln_TOTAL_DROPPED_CDRS];
				ABL_String      ls_ErrorCode[ln_TOTAL_DROPPED_CDRS];
				ABL_String      ls_ErrorMessage[ln_TOTAL_DROPPED_CDRS];
				ABL_String      ls_ErrorValue[ln_TOTAL_DROPPED_CDRS];
				ABL_DbDate		ld_DroppedDate[ln_TOTAL_DROPPED_CDRS];
				ABL_String		ls_Status[ln_TOTAL_DROPPED_CDRS];
				ABL_String      ls_DroppedCdr[ln_TOTAL_DROPPED_CDRS];
				ABL_String		ls_AgreementType[ln_TOTAL_DROPPED_CDRS];
				int				ln_CallType[ln_TOTAL_DROPPED_CDRS];
				ABL_String		ls_CallDirection[ln_TOTAL_DROPPED_CDRS];
				ABL_String		ls_Necode[ln_TOTAL_DROPPED_CDRS];
				ABL_String		ls_Partneridentifier[ln_TOTAL_DROPPED_CDRS];
				ABL_String		ls_PartnerCode[ln_TOTAL_DROPPED_CDRS];
				ABL_String		ls_Poi[ln_TOTAL_DROPPED_CDRS];
				ABL_String		ls_ServiceCode[ln_TOTAL_DROPPED_CDRS];
				ABL_String		ls_RateDirection[ln_TOTAL_DROPPED_CDRS];
				ABL_String		ls_PaymentDirection[ln_TOTAL_DROPPED_CDRS];
				ABL_String		ls_UnitRate[ln_TOTAL_DROPPED_CDRS];
				int				ln_UnitQty[ln_TOTAL_DROPPED_CDRS];
				ABL_String		ls_NumberPlanCode[ln_TOTAL_DROPPED_CDRS];
				ABL_String		ls_TariffPlanCode[ln_TOTAL_DROPPED_CDRS];
				ABL_String		ls_ANumber[ln_TOTAL_DROPPED_CDRS];
				ABL_String		ls_OriginRateZone[ln_TOTAL_DROPPED_CDRS];
				ABL_String		ls_BNumber[ln_TOTAL_DROPPED_CDRS];
				ABL_String		ls_DestionRateZone[ln_TOTAL_DROPPED_CDRS];
				ABL_DbDate		ld_CallDate[ln_TOTAL_DROPPED_CDRS];
				ABL_String		ls_DayCode[ln_TOTAL_DROPPED_CDRS];
				ABL_String		ls_Timetype[ln_TOTAL_DROPPED_CDRS];
				int				ln_RerateSeqNumber[ln_TOTAL_DROPPED_CDRS];
				ABL_String		ls_DropCode[ln_TOTAL_DROPPED_CDRS];
				double          ln_CallDuration[ln_TOTAL_DROPPED_CDRS];
				
				//Added as per LTE usage for 4.3 release
				ABL_String              ls_AUserId[ln_TOTAL_DROPPED_CDRS];
                		ABL_String              ls_BUserId[ln_TOTAL_DROPPED_CDRS];
				//modification end

				if(ln_TOTAL_DROPPED_CDRS==0)
					ln_TOTAL_DROPPED_CDRS=10;
				ls_sql="INSERT INTO PM_DROPPED_CDRS VALUES (:1,:2,:3,:4,:5,:6,:7,:8,:9,:10,:11,:12,:13,:14,:15,:16,:17,:18,:19,:20,:21,:22,:23,:24,:25,:26,:27,:28,:29,:30,:31,:32,:33,:34)";
				lo_ABLStatement		=	lo_ABLConnection->mb_createStatement(ls_sql);
				lo_ABLStatement.mb_setUpdateCount(ln_TOTAL_DROPPED_CDRS);
				lo_ABLStatement << ln_InputFileId;
				lo_ABLStatement << ln_RecordNo;
				lo_ABLStatement.mb_setStringArray(ls_ErrorCode,250);
				lo_ABLStatement.mb_setStringArray(ls_ErrorMessage,200);
				lo_ABLStatement.mb_setStringArray(ls_ErrorValue,50);
				lo_ABLStatement << ld_DroppedDate;
				lo_ABLStatement.mb_setStringArray(ls_Status,10); 
				lo_ABLStatement.mb_setStringArray(ls_DroppedCdr,1050); 
				lo_ABLStatement.mb_setStringArray(ls_AgreementType,1);
				lo_ABLStatement<< ln_CallType;
				lo_ABLStatement.mb_setStringArray(ls_CallDirection,1);
				lo_ABLStatement.mb_setStringArray(ls_Necode,45);
				lo_ABLStatement.mb_setStringArray(ls_Partneridentifier,30);
				lo_ABLStatement.mb_setStringArray(ls_PartnerCode,3);
				lo_ABLStatement.mb_setStringArray(ls_Poi,3);
				lo_ABLStatement.mb_setStringArray(ls_ServiceCode,3);
				lo_ABLStatement.mb_setStringArray(ls_RateDirection,1);
				lo_ABLStatement.mb_setStringArray(ls_PaymentDirection,1);
				lo_ABLStatement.mb_setStringArray(ls_UnitRate,1);
				lo_ABLStatement << ln_UnitQty;
				lo_ABLStatement.mb_setStringArray(ls_NumberPlanCode,5);
				lo_ABLStatement.mb_setStringArray(ls_TariffPlanCode,5);
				lo_ABLStatement.mb_setStringArray(ls_ANumber,25);
				lo_ABLStatement.mb_setStringArray(ls_OriginRateZone,5);
				lo_ABLStatement.mb_setStringArray(ls_BNumber,25);
				lo_ABLStatement.mb_setStringArray(ls_DestionRateZone,5);
				lo_ABLStatement << ld_CallDate;
				lo_ABLStatement.mb_setStringArray(ls_DayCode,3);
				lo_ABLStatement.mb_setStringArray(ls_Timetype,3);
				lo_ABLStatement << ln_RerateSeqNumber;
				lo_ABLStatement.mb_setStringArray(ls_DropCode,15);
				lo_ABLStatement << ln_CallDuration;

				//Added as per LTE usage for 4.3 release
				lo_ABLStatement.mb_setStringArray(ls_AUserId,65);
				lo_ABLStatement.mb_setStringArray(ls_BUserId,65);
				//modification end

				for(int i=0; i<lo_PMJobPtr->ga_DroppedCdr.size();i++)
				{
                                    //std::cout<<"ga_DroppedCdr.size()"<<lo_PMJobPtr->ga_DroppedCdr.size()<<std::endl;
					update_CallTypeCounts(lo_PMJobPtr, lo_PMJobPtr->ga_DroppedCdr[i].gs_AgreementType,lo_PMJobPtr->ga_DroppedCdr[i].gn_CallType,lo_PMJobPtr->ga_DroppedCdr[i].gn_CallDuration,lo_PMJobPtr->ga_DroppedCdr[i].gs_CallDirection);
					update_ATypeRatingLog(lo_PMJobPtr, lo_PMJobPtr->ga_DroppedCdr[i].gs_AgreementType);

					if(lo_PMJobPtr->ga_DroppedCdr[i].gs_StoreDroppedCdr == "Y")
					{
						ln_InputFileId[ln_DroopedCount]			=  lo_PMJobPtr->ga_DroppedCdr[i].gn_InputFileId;
						ln_RecordNo[ln_DroopedCount]			=	i;//lo_PMJobPtr->ga_DroppedCdr[i].gn_RecordNo;
						ls_ErrorCode[ln_DroopedCount]			=  lo_PMJobPtr->ga_DroppedCdr[i].gs_ErrorCode;
						ls_ErrorMessage[ln_DroopedCount]		=  lo_PMJobPtr->ga_DroppedCdr[i].gs_ErrorMessage;
						ls_ErrorValue[ln_DroopedCount]			=  lo_PMJobPtr->ga_DroppedCdr[i].gs_ErrorValue;
						ld_DroppedDate[ln_DroopedCount]			=  lo_PMJobPtr->gd_DbTimeStamp;//lo_PMJobPtr->ga_DroppedCdr[i].gd_DroppedDate;
						ls_Status[ln_DroopedCount]				=  lo_PMJobPtr->ga_DroppedCdr[i].gs_Status;
						ls_DroppedCdr[ln_DroopedCount]			=  lo_PMJobPtr->ga_DroppedCdr[i].gs_DroppedCdr;
						ls_AgreementType[ln_DroopedCount]		=  lo_PMJobPtr->ga_DroppedCdr[i].gs_AgreementType;
						ln_CallType[ln_DroopedCount]			=  lo_PMJobPtr->ga_DroppedCdr[i].gn_CallType;
						ls_CallDirection[ln_DroopedCount]		=  lo_PMJobPtr->ga_DroppedCdr[i].gs_CallDirection;
						ls_Necode[ln_DroopedCount]				=  lo_PMJobPtr->ga_DroppedCdr[i].gs_Necode;
						ls_Partneridentifier[ln_DroopedCount]	=  lo_PMJobPtr->ga_DroppedCdr[i].gs_Partneridentifier;
						ls_PartnerCode[ln_DroopedCount]			=  lo_PMJobPtr->ga_DroppedCdr[i].gs_PartnerCode;
						ls_Poi[ln_DroopedCount]					=  lo_PMJobPtr->ga_DroppedCdr[i].gs_Poi;
						ls_ServiceCode[ln_DroopedCount]			=  lo_PMJobPtr->ga_DroppedCdr[i].gs_ServiceCode;
						ls_RateDirection[ln_DroopedCount]		=  lo_PMJobPtr->ga_DroppedCdr[i].gs_RateDirection;
						ls_PaymentDirection[ln_DroopedCount]	=  lo_PMJobPtr->ga_DroppedCdr[i].gs_PaymentDirection;
						ls_UnitRate[ln_DroopedCount]			=	lo_PMJobPtr->ga_DroppedCdr[i].gs_UnitRate;
						ln_UnitQty[ln_DroopedCount]				=  lo_PMJobPtr->ga_DroppedCdr[i].gn_UnitQty;
						ls_NumberPlanCode[ln_DroopedCount]		=  lo_PMJobPtr->ga_DroppedCdr[i].gs_NumberPlanCode;
						ls_TariffPlanCode[ln_DroopedCount]		=  lo_PMJobPtr->ga_DroppedCdr[i].gs_TariffPlanCode;
						ls_ANumber[ln_DroopedCount]				=  lo_PMJobPtr->ga_DroppedCdr[i].gs_ANumber;
						ls_OriginRateZone[ln_DroopedCount]		=  lo_PMJobPtr->ga_DroppedCdr[i].gs_OriginRateZone;
						ls_BNumber[ln_DroopedCount]				=  lo_PMJobPtr->ga_DroppedCdr[i].gs_BNumber;
						ls_DestionRateZone[ln_DroopedCount]		=  lo_PMJobPtr->ga_DroppedCdr[i].gs_DestionRateZone;
						ld_CallDate[ln_DroopedCount]			=  lo_PMJobPtr->ga_DroppedCdr[i].gd_CallDate;
						ls_DayCode[ln_DroopedCount]				=  lo_PMJobPtr->ga_DroppedCdr[i].gs_DayCode;
						ls_Timetype[ln_DroopedCount]			=  lo_PMJobPtr->ga_DroppedCdr[i].gs_Timetype;
						ln_RerateSeqNumber[ln_DroopedCount]		= 0;
						ls_DropCode[ln_DroopedCount]			=  lo_PMJobPtr->ga_DroppedCdr[i].gs_DropCode;
						ln_CallDuration[ln_DroopedCount]		=  lo_PMJobPtr->ga_DroppedCdr[i].gn_CallDuration;

						//Added as per LTE usage for 4.3 release
						ls_AUserId[ln_DroopedCount]			= lo_PMJobPtr->ga_DroppedCdr[i].gs_AUserId;
						ls_BUserId[ln_DroopedCount]			= lo_PMJobPtr->ga_DroppedCdr[i].gs_BUserId;
						//modification end
						
						ln_DroopedCount=ln_DroopedCount+1;

						if( (ln_DroopedCount>0) && (ln_DroopedCount>=ln_TOTAL_DROPPED_CDRS))
						{
                                                 
							ST_ERROR_DETAILS lr_ErrorDetail[ln_DroopedCount+1];
							try
							{		
								
								ln_ErrorNums=ln_DroopedCount;

								lo_ABLStatement.mb_setUpdateCount(ln_DroopedCount);

								//lo_ABLStatement.mb_executeArrayUpdate();
								//std::cout<<"came"<<std::endl;
								lo_ABLStatement.mb_executeArrayUpdate(&ln_ErrorNums,lr_ErrorDetail);
								ln_DroopedCount=0;
							}
							catch(ABL_Exception &e)
							{
								lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);

								*m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;		

								if(ln_ErrorNums!=0)
								{
                                                                //std::cout<<ln_ErrorNums<<std::endl;
									for(int n=0;n<ln_ErrorNums;n++)
									{

											ABL_String lc_ErrorMsg = lr_ErrorDetail[n].m_arrErrorMsg;
											

											if((lc_ErrorMsg.mb_subStr(0,9)) == "ORA-00001")
											{
                                                                                         *m_ABL_ServicePtr<<CRITICAL<<"Unique index error :Ignored"<<Endl;
											}
											else
											{
                                                                       //std::cout<<ln_ErrorNums<<std::endl;
                   						rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
                                                                *m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<lc_ErrorMsg<<Endl;												
                                                                                        ABL_String ls_command("touch ");
											ls_command +=ms_Stopsignalfile;
												system(ls_command.c_str());  
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
								lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
								*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
								return false;
							}
							ln_DroopedCount=0;

						}

				}
			}       
		/*if( ln_DroopedCount>0 && ln_DroopedCount<=ln_TOTAL_DROPPED_CDRS)
		{				
			try
			{
				ln_ErrorNums=ln_DroopedCount;
				lo_ABLStatement.mb_setUpdateCount(ln_DroopedCount);

				lo_ABLStatement.mb_executeArrayUpdate();
				lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
				ln_DroopedCount=0;
			}
			catch(ABL_Exception &e)
			{
				rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
				lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
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
				lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
				*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
				return false;
			}

		} */
		lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
	}
		
	*m_ABL_ServicePtr<<DEBUG<<"End  :"<< lo_PMJobPtr->gs_fileName <<": "<<lo_PMJobPtr->ga_DroppedCdr.size()<< Endl;
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

void PM_InsertDroppedCdrsInDB::update_ATypeRatingLog(PM_Job * &p_ABL_JobPtr, ABL_String AgreementType)
{

		PM_Job* l_PM_Job_Local = (PM_Job*)p_ABL_JobPtr;
		l_PM_Job_Local->gi_ATypeLogMapIterator=l_PM_Job_Local->ga_ATypeLogMap.find(AgreementType);
		if(l_PM_Job_Local->gi_ATypeLogMapIterator!=l_PM_Job_Local->ga_ATypeLogMap.end())
		{			
			l_PM_Job_Local->gi_ATypeLogMapIterator->second.gn_TotalDropped=l_PM_Job_Local->gi_ATypeLogMapIterator->second.gn_TotalDropped+1;			
		}

}
void PM_InsertDroppedCdrsInDB::update_CallTypeCounts(PM_Job * &p_ABL_JobPtr, ABL_String AgreementType, int CallType, double  CallDuration, ABL_String CallDirection)
{
	PM_Job* l_PM_Job_Local = (PM_Job*)p_ABL_JobPtr;	


		ABL_String	ls_TempConvert="";
		ABL_String  l_agreementtype_calltype=AgreementType;
		ls_TempConvert.mb_fromDouble(CallType);
		l_agreementtype_calltype+=ls_TempConvert;
		l_PM_Job_Local->gi_CallTypeCountsMapIterator=l_PM_Job_Local->ga_CallTypeCountsMap.find(l_agreementtype_calltype);
		if(l_PM_Job_Local->gi_CallTypeCountsMapIterator!=l_PM_Job_Local->ga_CallTypeCountsMap.end())
		{

			if(CallDirection=="I")
			{
				l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalIncDropCount=l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalIncDropCount+1;
				l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalIncDropDuration=l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalIncDropDuration +CallDuration;               
			}
			else if(CallDirection=="O")
			{
				l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalOutDropCount =l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalOutDropCount+1;
				l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalOutDropDuration=l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalOutDropDuration+CallDuration;
			}
			else
			{
				*m_ABL_ServicePtr<<DEBUG<<"Call Direction is not present: "<<Endl;
			}
			
		}
		else
		{
		//	std::cout<<"not found record for  gn_TotalIncDropCount and  gn_TotalOutDropCount in ga_CallTypeCountsMap: "<<l_agreementtype_calltype<<std::endl;
		}
}
