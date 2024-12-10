#include "PM_FindTariffPlan.h"
#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "ABL_DateTime.h"
#include "ABL_Date.h"
#include "ABL_DbDate.h"
#include "ABL_CacheManager.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_FindTariffPlan()
{
	return ( (Base_Registry*) new PM_FindTariffPlan);
}
}

PM_FindTariffPlan::PM_FindTariffPlan()
{
	//
}

PM_FindTariffPlan::~PM_FindTariffPlan()
{
	//
}

PM_FindTariffPlan::PM_FindTariffPlan(const PM_FindTariffPlan& p_copyObject)
{
	this->mo_ABLServicePtr				=	p_copyObject.mo_ABLServicePtr;
	this->mo_TariffPlanCacheContainer		=	p_copyObject.mo_TariffPlanCacheContainer;
	this->mo_TariffPlanCachePtr			=	(PM_Partners_TariffPlanCache*)p_copyObject.mo_TariffPlanCachePtr->mb_createCopy();
	this->ms_Stopsignalfile				=	p_copyObject.ms_Stopsignalfile;
}

Base_Registry* PM_FindTariffPlan::mb_clone()
{
	return ( (Base_Registry*) new PM_FindTariffPlan );
}

ABL_Process* PM_FindTariffPlan::mb_createCopy()
{
	return ( new PM_FindTariffPlan (*this));
}

bool PM_FindTariffPlan::mb_initProcess(ABL_CacheManager* pABLCacheManagerPtr, ABL_AgentCommunicator *pABLAgentCommunicatorPtr, ABL_Service *pABLServicePtr)
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

bool PM_FindTariffPlan::mb_getCache(ABL_CacheManager* pABLCacheManagerPtr)
{
	try
	{
		mo_TariffPlanCachePtr	=	(PM_Partners_TariffPlanCache*)mo_ABLServicePtr->mb_getObject("PM_Partners_TariffPlanCache");//->mb_clone();
		mo_TariffPlanCacheContainer		=	pABLCacheManagerPtr->mb_getCache("PM_Partners_TariffPlanCache");
	
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

bool PM_FindTariffPlan::mb_process(ABL_Job* &pABLJobPtr)
{

	PM_Job* lo_PMJobPtr		=	(PM_Job*)pABLJobPtr;	
	ABL_String				ls_RejMesg,ls_date ;
	PM_Partners_TariffPlanCache*    lo_PMTariffPlanCachePtr; 
	try
	{

		// if the array with events to rate is empty (ratedEventArr), then insert the rejected 
       // and dropped cdrs into database and finish rating for the agreement type.
		if (lo_PMJobPtr->ga_RatedCdrs.size()== 0) 
		{
			if (lo_PMJobPtr->gs_IsGPRSFile=="YES")
			{
				return true;
			}
                        else
			{
				*mo_ABLServicePtr << DEBUG <<"  No Cdrs for finding the tariff plan for the file: " <<lo_PMJobPtr->gs_fileName<<Endl;	
				return true;          
			}
		}

		*mo_ABLServicePtr << DEBUG << "Start :" <<lo_PMJobPtr->gs_fileName <<" : "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;
		if (mo_TariffPlanCacheContainer->mb_size()==0)
		{
			rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
			*mo_ABLServicePtr << INFO << " There is no records in PM_TARIFF_PLAN or PM_PARTNER_TARIFF_PLAN   Rating is  stopping...: "  << Endl;	
			ABL_String ls_command("touch ");
			ls_command +=ms_Stopsignalfile;
			system(ls_command.c_str()); 
			return false;
		}

	
		for (int i=0;i<lo_PMJobPtr->ga_RatedCdrs.size();i++)
		{
			if(lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus=="D" || lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus=="R")
			{
				continue;
			}
			
			mo_TariffPlanCachePtr->mb_setAgreementType(lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType);
			mo_TariffPlanCachePtr->mb_setTariffPlanType(lo_PMJobPtr->ga_RatedCdrs[i].gs_PaymentDirection);	
			mo_TariffPlanCachePtr->mb_setPartnerCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode);
			mo_TariffPlanCachePtr->mb_setValid_From(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
			mo_TariffPlanCachePtr->mb_setValid_To(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
			if(mo_TariffPlanCacheContainer->mb_get((CBase*)mo_TariffPlanCachePtr,(CBase*&)lo_PMTariffPlanCachePtr))
			{ 

				lo_PMJobPtr->ga_RatedCdrs[i].gs_TariffPlanCode =lo_PMTariffPlanCachePtr->mb_getTariffPlanCode();

			}
			else
			{		
				ls_RejMesg											= "No tariff plan found for : partner =>";
				ls_RejMesg											+=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
				ls_RejMesg											+=",Call Date=> ";
				ls_RejMesg											+=lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();
				ls_RejMesg											+=",Call Direction=> ";
				ls_RejMesg											+=lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection;
				ls_RejMesg											+=",Payment Direction => ";
				ls_RejMesg											+= lo_PMJobPtr->ga_RatedCdrs[i].gs_PaymentDirection ;
				ls_RejMesg											+=",Tariff plan  Type => ";
				ls_RejMesg											+=lo_PMJobPtr->ga_RatedCdrs[i].gs_PaymentDirection;

				lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode="RATE-TARIFFPLAN-NF";
				lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
				lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage=ls_RejMesg ; 
				lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="R";

			}// End Else	
		}// End For		

		*mo_ABLServicePtr<<DEBUG<<"End  :"<<lo_PMJobPtr->gs_fileName <<": "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;
	}
	catch(ABL_Exception &e)
	{
		rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
		*mo_ABLServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
		 ABL_String ls_command("touch ");
		 ls_command +=ms_Stopsignalfile;
		 system(ls_command.c_str());  		
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

 
bool PM_FindTariffPlan::mb_stop()
{
	return true;
}


