#include "PM_FindTimeType.h"
#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "ABL_DateTime.h"
#include "ABL_Date.h"
#include "ABL_DbDate.h"
#include "ABL_CacheManager.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_FindTimeType()
{
	return ( (Base_Registry*) new PM_FindTimeType);
}
}

PM_FindTimeType::PM_FindTimeType()
{
	//
}

PM_FindTimeType::~PM_FindTimeType()
{
	//
}

PM_FindTimeType::PM_FindTimeType(const PM_FindTimeType& p_copyObject)
{
	this->mo_ABLServicePtr						=	p_copyObject.mo_ABLServicePtr;	
	this->mo_HolidayCacheContainer				=	p_copyObject.mo_HolidayCacheContainer;		
	this->mo_TimeTypeCacheContainer				=	p_copyObject.mo_TimeTypeCacheContainer;	
	this->mo_DayCodeCacheContainer				=	p_copyObject.mo_DayCodeCacheContainer;	
	this->mo_HolidayCachePtr					=	(PM_HolidayCache*)p_copyObject.mo_HolidayCachePtr->mb_createCopy();
	this->mo_TimeTypeCachePtr					=	(PM_Partners_Time_TypeCache*)p_copyObject.mo_TimeTypeCachePtr->mb_createCopy();
	this->mo_DayCodeCachePtr					=	(PM_Tariffplan_DayCodeCache*)p_copyObject.mo_DayCodeCachePtr->mb_createCopy();
	this->ms_Stopsignalfile						=	p_copyObject.ms_Stopsignalfile;
}

Base_Registry* PM_FindTimeType::mb_clone()
{
	return ( (Base_Registry*) new PM_FindTimeType );
}

ABL_Process* PM_FindTimeType::mb_createCopy()
{
	return ( new PM_FindTimeType (*this));
}

bool PM_FindTimeType::mb_initProcess(ABL_CacheManager* pABLCacheManagerPtr, ABL_AgentCommunicator *pABLAgentCommunicatorPtr, ABL_Service *pABLServicePtr)
{	
	try
	{
		
		mo_ABLServicePtr = pABLServicePtr;
		pABLAgentCommunicatorPtr->mb_getParameter("STOP_FILE",ms_Stopsignalfile);
	}
	catch(ABL_Exception &e)
	{
		*mo_ABLServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
		ABL_String ls_command("touch ");
		 ls_command +=ms_Stopsignalfile;
		 system(ls_command.c_str());  
		return false;
	}
	catch(...)
	{
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str()); 	
		*mo_ABLServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}	

	return true;
}

bool PM_FindTimeType::mb_getCache(ABL_CacheManager* pABLCacheManagerPtr)
{
	try
	{
		
		mo_HolidayCacheContainer		=	pABLCacheManagerPtr->mb_getCache("PM_HolidayCache");
		mo_TimeTypeCacheContainer		=	pABLCacheManagerPtr->mb_getCache("PM_Partners_Time_TypeCache");		
		mo_DayCodeCacheContainer		=	pABLCacheManagerPtr->mb_getCache("PM_Tariffplan_DayCodeCache");

		mo_HolidayCachePtr		=	(PM_HolidayCache*)mo_ABLServicePtr->mb_getObject("PM_HolidayCache")->mb_clone();
		mo_TimeTypeCachePtr		=	(PM_Partners_Time_TypeCache*)mo_ABLServicePtr->mb_getObject("PM_Partners_Time_TypeCache")->mb_clone();
		mo_DayCodeCachePtr		=	(PM_Tariffplan_DayCodeCache*)mo_ABLServicePtr->mb_getObject("PM_Tariffplan_DayCodeCache")->mb_clone();


	}
	catch(ABL_Exception &e)
	{
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str()); 	
		*mo_ABLServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
		return false;
	}
	catch(...)
	{
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str()); 	
		*mo_ABLServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}	

	return true;
}

bool PM_FindTimeType::mb_process(ABL_Job* &pABLJobPtr)
{
	PM_Job* lo_PMJobPtr			=   (PM_Job*)pABLJobPtr;
	ABL_String						ls_RejMesg ;
	ABL_String						ls_sql;	
	ABL_String						ls_StartTime[1] ;
	ABL_String						ls_EndTime[1] ;
	ABL_String						ls_TimeType[1];
	double							ln_TtDuration[1];
	PM_HolidayCache*                lo_HolidayCachePtr;
	PM_Partners_Time_TypeCache*     lo_TimeTypeCachePtr;
	PM_Tariffplan_DayCodeCache*     lo_DayCodeCachePtr;
	ABL_String						ls_ErrorCode;
	ABL_DateTime 					ld_EventTime;
	try
	{
		ls_RejMesg 	=	"";



		if (lo_PMJobPtr->ga_RatedCdrs.size()== 0) 
		{
			if (lo_PMJobPtr->gs_IsGPRSFile=="YES")
			{
				return true;
			}
                        else
			{
				*mo_ABLServicePtr << DEBUG <<" No Cdrs to find Time Type for the file: " <<lo_PMJobPtr->gs_fileName<<Endl;	
				return true;          
			}
		}

		*mo_ABLServicePtr << DEBUG << "Start :" <<lo_PMJobPtr->gs_fileName <<" : "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;
       // if the array with events to rate is empty (ratedEventArr), then insert the rejected 
       // and dropped cdrs into database and finish rating for the agreement type

	   if (mo_TimeTypeCacheContainer->mb_size()==0)
		{
		   rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
			*mo_ABLServicePtr << INFO << " There is no records in PM_TIME_TYPE   Rating is  stopping...: "  << Endl;	
			ABL_String ls_command("touch ");
			ls_command +=ms_Stopsignalfile;
			system(ls_command.c_str()); 
			return false;
		}

		if (mo_DayCodeCacheContainer->mb_size()==0)
		{
			rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
			*mo_ABLServicePtr << INFO << " There is no records in PM_DAY_CODE  Rating is  stopping...: "  << Endl;	
			ABL_String ls_command("touch ");
			ls_command +=ms_Stopsignalfile;
			system(ls_command.c_str()); 
			return false;
		}

       
		for(int i = 0;i<lo_PMJobPtr->ga_RatedCdrs.size();i++)
		{
			
			try
			{
				if(lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus=="D" || lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus=="R")
				{
					continue;
				}

				ls_ErrorCode="";
				if (lo_PMJobPtr->ga_ControlParams[0].gs_RatingType == "E")
				{	
						ld_EventTime = lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate;
						ld_EventTime.mb_addSeconds((int)lo_PMJobPtr->ga_RatedCdrs[i].gn_CallDuration);									} 
				else
				{
					ld_EventTime = lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate;
				}

				
				/****** check whether call date is a holiday or not *******/
				if (mo_HolidayCacheContainer->mb_size() >0)
				{
					ls_RejMesg = "Error while determining if ";
					ls_RejMesg += ld_EventTime.mb_toString();
					ls_RejMesg +=" is a holiday";
					mo_HolidayCachePtr->mb_setHolidayDate(ld_EventTime);
					mo_HolidayCachePtr->mb_setTariffPlanCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_TariffPlanCode);				
					if(mo_HolidayCacheContainer->mb_get((CBase*)mo_HolidayCachePtr,(CBase*&)lo_HolidayCachePtr))
					{	
						lo_PMJobPtr->ga_RatedCdrs[i].gs_HolidayId=lo_HolidayCachePtr->mb_getHolidayId();
					}
				}
			
				if(lo_PMJobPtr->ga_RatedCdrs[i].gs_DayCode == "")
				{
					ls_RejMesg = "Error determining day code for call date=> ";
					ls_RejMesg += ld_EventTime.mb_toString();
					ls_RejMesg +=" for tariff plan=> ";
					ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_TariffPlanCode;
					ls_RejMesg +="Partner Code => ";
					ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
					//ls_ErrorCode  = "DAYCODE-NF"; commented as per LTE usage for 4.3 release
					ls_ErrorCode  = "RATE-TIMETYPE-NF";
					mo_DayCodeCachePtr->mb_setDayCode(get_dayCodeStr(ld_EventTime.mb_getDayOfWeek()));
					mo_DayCodeCachePtr->mb_setTariffPlanCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_TariffPlanCode);
					if(mo_DayCodeCacheContainer->mb_get((CBase*)mo_DayCodeCachePtr,(CBase*&)lo_DayCodeCachePtr))
					{		
						lo_PMJobPtr->ga_RatedCdrs[i].gs_DayCode = lo_DayCodeCachePtr->mb_getDayCode();
					}
				
					if (lo_PMJobPtr->ga_RatedCdrs[i].gs_DayCode=="")
					{
						throw  ABL_Exception(1,ls_RejMesg .c_str());
					}
				}

				/*****************************************************
				Now when the day code is found, get the time type for the dayCode's time zone
				******************************************************/
				ls_RejMesg = "No Time Type found for partner = =>";
				ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
				ls_RejMesg +=",Tariff Plan Type => ";
				ls_RejMesg += lo_PMJobPtr->ga_RatedCdrs[i].gs_PaymentDirection ;	
				ls_ErrorCode="RATE-TIMETYPE-NF";

				mo_TimeTypeCachePtr->mb_setDayCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_DayCode);
				mo_TimeTypeCachePtr->mb_setStartTime(ld_EventTime.mb_toString(YYYYMMDDHH24MISS).mb_subStr(8,6));
				mo_TimeTypeCachePtr->mb_setEndTime(ld_EventTime.mb_toString(YYYYMMDDHH24MISS).mb_subStr(8,6));
				mo_TimeTypeCachePtr->mb_setTariffPlanCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_TariffPlanCode);
				if(mo_TimeTypeCacheContainer->mb_get((CBase*)mo_TimeTypeCachePtr,(CBase*&)lo_TimeTypeCachePtr))
				{
					lo_PMJobPtr->ga_RatedCdrs[i].gs_TimeType =lo_TimeTypeCachePtr->mb_getTimeType();
				}
				else
				{
					throw  ABL_Exception(1,ls_RejMesg .c_str());
				}

            }// End Try
            catch(ABL_Exception &e)
            {
				//REJECTED:			
				if(e.mb_getErrorCode()== 1)
				{
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode=ls_ErrorCode;
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage=ls_RejMesg ; 
					lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="R";

				}
				else
				{
					*mo_ABLServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
					std::cout<<"TIMETYPE NOT FOUND FOR THE : "<<ls_RejMesg<<std::endl;

				}
		
			}//End For Catch
			catch(...)
			{
				rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
				std::cout<<"TIMETYPE NOT FOUND FOR THE : "<<ls_RejMesg<<std::endl;
				ABL_String l_command("touch ");
				l_command +=ms_Stopsignalfile;
				system(l_command.c_str()); 	
				*mo_ABLServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
				return false;
			}	
		}//End for For Loop		
		
		*mo_ABLServicePtr<<DEBUG<<" End of processing for the file : "<< lo_PMJobPtr->gs_fileName <<Endl;

	}//End of Try
	catch(ABL_Exception &e)
	{
		rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str()); 	
		*mo_ABLServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
		
	    return false;
	}
	catch(...)
	{
		rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str()); 	
		*mo_ABLServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}	
	 return true;
	   
}//End of Function
 
bool PM_FindTimeType::mb_stop()
{
	return true;
}

ABL_String PM_FindTimeType :: get_dayCodeStr(int dayofweek)
{
		ABL_String  gdayCodeStr[8] ;
		gdayCodeStr[0] = "SUN";
		gdayCodeStr[1] = "MON";
		gdayCodeStr[2] = "TUE";
		gdayCodeStr[3] = "WED";
		gdayCodeStr[4] = "THU";
		gdayCodeStr[5] = "FRI";
		gdayCodeStr[6] = "SAT";
		gdayCodeStr[7] = "SUN";
		return gdayCodeStr[dayofweek];
}
