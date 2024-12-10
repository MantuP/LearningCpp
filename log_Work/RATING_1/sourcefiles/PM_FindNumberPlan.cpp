#include "PM_FindNumberPlan.h"
#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "ABL_DateTime.h"
#include "ABL_Date.h"
#include "ABL_DbDate.h"
#include "PM_Find_NumberPlanCache.h"
extern "C" {EXPORT 
Base_Registry* gb_getPM_FindNumberPlan()
{
	return ( (Base_Registry*) new PM_FindNumberPlan);
}
}

PM_FindNumberPlan::PM_FindNumberPlan()
{
	//
}

PM_FindNumberPlan::~PM_FindNumberPlan()
{
	//
}

PM_FindNumberPlan::PM_FindNumberPlan(const PM_FindNumberPlan& p_copyObject)
{
	this->mo_ABLServicePtr                      =	p_copyObject.mo_ABLServicePtr;
	this->mo_NumberPlanCachecacheContainer		=	p_copyObject.mo_NumberPlanCachecacheContainer;	
	this->mo_NumberPlanCachePtr					=	(PM_Find_NumberPlanCache*)p_copyObject.mo_NumberPlanCachePtr->mb_createCopy();
	this->ms_Stopsignalfile						=	p_copyObject.ms_Stopsignalfile;

}

Base_Registry* PM_FindNumberPlan::mb_clone()
{
	return ( (Base_Registry*) new PM_FindNumberPlan );
}

ABL_Process* PM_FindNumberPlan::mb_createCopy()
{
	return ( new PM_FindNumberPlan (*this));
}

bool PM_FindNumberPlan::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{	
	try
	{

		mo_ABLServicePtr = p_ABL_ServicePtr;
		p_ABL_AgentCommunicatorPtr->mb_getParameter("STOP_FILE",ms_Stopsignalfile);

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

bool PM_FindNumberPlan::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	try
	{
		mo_NumberPlanCachePtr					=	(PM_Find_NumberPlanCache*)mo_ABLServicePtr->mb_getObject("PM_Find_NumberPlanCache")->mb_clone();
		mo_NumberPlanCachecacheContainer		=	p_ABL_CacheManagerPtr->mb_getCache("PM_Find_NumberPlanCache");
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

bool PM_FindNumberPlan::mb_process(ABL_Job* &p_ABL_JobPtr)
{
	PM_Job* lo_PMJobPtr = (PM_Job*)p_ABL_JobPtr;	
	ABL_String ls_RejMesg="" ;


	ABL_String			ls_NumberPlanReq;	
	ABL_String			ls_NumberPlanType;

	int					i;

	PM_Find_NumberPlanCache *lo_PM_Find_NumberPlanCachePtr;

	try
	{

               if ( lo_PMJobPtr->gs_FileStatus == "D" || lo_PMJobPtr->gs_FileStatus == "F" )
                        {
                                return true;
                        }


		if (lo_PMJobPtr->ga_RatedCdrs.size()== 0) 
		{
			if (lo_PMJobPtr->gs_IsGPRSFile=="YES")
			{
				return true;
			}
                        else
			{
				*mo_ABLServicePtr << DEBUG <<"  No Cdrs for finding Number Plan for the file    : " <<lo_PMJobPtr->gs_fileName<<Endl;	
				return true;          
			}
		}

		*mo_ABLServicePtr << DEBUG << "Start :" <<lo_PMJobPtr->gs_fileName <<" : "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;


       // if the array with events to rate is empty (ratedEventArr), then insert the rejected 
       // and dropped cdrs into database and finish rating for the agreement type

		if (mo_NumberPlanCachecacheContainer->mb_size()==0)
		{
			rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
			*mo_ABLServicePtr << INFO << " There is no records in PM_NUMBER_PLAN or PM_PARTNER_NUMBER_PLAN   Rating is  stopping...: "  << Endl;	
			ABL_String ls_command("touch ");
			ls_command +=ms_Stopsignalfile;
			system(ls_command.c_str()); 
			return false;
		}

		
       

		for(i=0 ;i<lo_PMJobPtr->ga_RatedCdrs.size();i++)
		{
										
			if(lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus=="D" || lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus=="R")
			{
				continue;
			}

			//derive the rate zone only if the rate direction is not default rate zone
			if (lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection=="R" )
			{
				continue;
			}

			ls_NumberPlanReq="";
			ls_NumberPlanType="";
			if (lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection=="D" || lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection=="B" )
			{
				ls_NumberPlanReq="Y";
			}
			else if (lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection=="O" )
			{
				ls_NumberPlanReq="N";
			}

				 //derive the number plan code to find the Destination rate zone
				
				if (lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType=="I" )
				{


					if (lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection == "I")  //incoming
					{	
						ls_NumberPlanType = "O";
					}
					else if (lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection == "O") //Outgoing
					{
						ls_NumberPlanType = "P";
					}

					ls_RejMesg= "Cannot find Number Plan for Partner => ";
					ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
					ls_RejMesg+=", Call Date => ";
					ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();
					ls_RejMesg+=", Call Dir => ";
					ls_RejMesg+=	lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection;
					ls_RejMesg+=", Rate Dir => ";
					ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection;
					ls_RejMesg+=", POI => ";
					ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_Poi;
					ls_RejMesg+=", Num Plan Type => ";
					ls_RejMesg+=ls_NumberPlanType;
				}
				else
				{
					if (lo_PMJobPtr->ga_RatedCdrs[i].gs_PaymentDirection == "R" || lo_PMJobPtr->ga_RatedCdrs[i].gs_PaymentDirection == "" ||lo_PMJobPtr->ga_RatedCdrs[i].gs_PaymentDirection == " ")
					{	
						ls_NumberPlanType = "O";
					}
					else
					{
						ls_NumberPlanType = "P";
					}

					ls_RejMesg= "Cannot find Number Plan for Partner => ";
					ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
					ls_RejMesg+=", Call Date => ";
					ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();
					ls_RejMesg+=", Call Dir => ";
					ls_RejMesg+=	lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection;
					ls_RejMesg+=", Rate Dir => ";
					ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection;
					ls_RejMesg+=", Num Plan Type => ";
					ls_RejMesg+=ls_NumberPlanType;
				}
				

				mo_NumberPlanCachePtr->mb_setNumberPlanType(ls_NumberPlanType);
				mo_NumberPlanCachePtr->mb_setPartnerCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode);
				mo_NumberPlanCachePtr->mb_setAgreementType(lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType);
				mo_NumberPlanCachePtr->mb_setPOI(lo_PMJobPtr->ga_RatedCdrs[i].gs_Poi);					
				mo_NumberPlanCachePtr->mb_setValid_From(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
				mo_NumberPlanCachePtr->mb_setValid_To(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
				if(mo_NumberPlanCachecacheContainer->mb_get((CBase*)mo_NumberPlanCachePtr,(CBase*&)lo_PM_Find_NumberPlanCachePtr))
				{		
						lo_PMJobPtr->ga_RatedCdrs[i].gs_NumberPlanCode="";
						lo_PMJobPtr->ga_RatedCdrs[i].gs_NumberPlanCode =lo_PM_Find_NumberPlanCachePtr->mb_getNumberPlanCode();					
						lo_PMJobPtr->ga_RatedCdrs[i].gs_BrokerCountryCode =lo_PM_Find_NumberPlanCachePtr->mb_getBrokerCountryCode();


				}
				else
				{		
					if(ls_NumberPlanReq=="Y" )
					{

							ls_RejMesg					= "Cannot find Number Plan for Partner =>";
							ls_RejMesg					+=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
							ls_RejMesg					+=", Call Date => ";
							ls_RejMesg					+= lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toCharText() ;
							ls_RejMesg					+=", Call Dir => ";
							ls_RejMesg					+= lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection;
							ls_RejMesg					+=", Rate Dir => " ;
							ls_RejMesg					+=lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection;
							ls_RejMesg					+=", Num Plan Type => ";
							ls_RejMesg					+= ls_NumberPlanType;						
							lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode="RATE-NUMPLAN-NF";
							lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode  ;
							lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage=ls_RejMesg; 
							lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="R";
					}
			}

		}		
		

		*mo_ABLServicePtr<<DEBUG<<"End  :" << lo_PMJobPtr->gs_fileName <<": "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;
	}
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

		
}

bool PM_FindNumberPlan::mb_stop()
{
	return true;
}


