/***********************************************************
************************************************************
************************************************************
Agent Name:  PM_ValidateService.cpp
Module Name: FrameWork Rating
Dated: 21/01/2010


************************************************************
************************************************************
***********************************************************/
#include "PM_ValidateService.h"
#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "PM_Job.h"
#include "string"
#include "ABL_CacheManager.h"
#include "ABL_DbDate.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_ValidateService()
{
	return ( (Base_Registry*) new PM_ValidateService);
}
	   }

PM_ValidateService::PM_ValidateService()
{
	//
}

PM_ValidateService::~PM_ValidateService()
{
	//
}

PM_ValidateService::PM_ValidateService(const PM_ValidateService& p_copyObject)
{
	this->mo_ABLServicePtr					    =	p_copyObject.mo_ABLServicePtr;
	this->mo_ServicesCachecacheContainer		=	p_copyObject.mo_ServicesCachecacheContainer;
	this->mo_ServicesCachePtr				    =	(PM_ValidServicesCache*)p_copyObject.mo_ServicesCachePtr->mb_createCopy();
	this->ms_Stopsignalfile						=	p_copyObject.ms_Stopsignalfile;	
}
Base_Registry* PM_ValidateService::mb_clone()
{
	return ( (Base_Registry*) new PM_ValidateService );
}

ABL_Process* PM_ValidateService::mb_createCopy()
{
	return ( new PM_ValidateService (*this));
}

bool PM_ValidateService::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{	

	try
	{
		mo_ABLServicePtr = p_ABL_ServicePtr;
		p_ABL_AgentCommunicatorPtr->mb_getParameter("STOP_FILE",ms_Stopsignalfile);
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

bool PM_ValidateService::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	try
	{
		mo_ServicesCachePtr		=	(PM_ValidServicesCache*)mo_ABLServicePtr->mb_getObject("PM_ValidServicesCache")->mb_clone();
		mo_ServicesCachecacheContainer	=	p_ABL_CacheManagerPtr->mb_getCache("PM_ValidServicesCache");
	}
	catch(ABL_Exception &e)
	{
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
bool PM_ValidateService::mb_process(ABL_Job* &p_ABL_JobPtr)
{
	PM_Job* lo_PMJobPtr = (PM_Job*)p_ABL_JobPtr;	


	ABL_String		ls_DroppCdr;
	ABL_String		ls_dropCode;
	ABL_String		ls_dropValue;
	ABL_String		ls_dropMessage;
	PM_ValidServicesCache        	*lo_PMServicesCachePtr; 

	try
	{
      
       // if the array with events to rate is empty (ratedEventArr), then insert the rejected 
       // and dropped cdrs into database and finish rating for the agreement type

	   if (lo_PMJobPtr->ga_RatedCdrs.size()== 0) 
		{
			if (lo_PMJobPtr->gs_IsGPRSFile=="YES")
			{
				return true;
			}
                        else
			{
				*mo_ABLServicePtr << DEBUG <<" No Cdrs for finding the partner's services for the file : " <<lo_PMJobPtr->gs_fileName<<Endl;	
				return true;          
			}
		}
		*mo_ABLServicePtr << DEBUG << "Start :" <<lo_PMJobPtr->gs_fileName <<" : "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;

	   if (mo_ServicesCachecacheContainer->mb_size()==0)
		{
		   rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
			*mo_ABLServicePtr << INFO << " There is no records in PM_SERVICE  Rating is  stopping...: "  << Endl;	
			ABL_String ls_command("touch ");
			ls_command +=ms_Stopsignalfile;
			system(ls_command.c_str()); 

			return false;
		}

		for (int i=0; i<lo_PMJobPtr->ga_RatedCdrs.size();i++ )
		{

			if(lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus=="D" || lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus=="R")
			{
				continue;
			}
				mo_ServicesCachePtr->mb_setServiceCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode);
				mo_ServicesCachePtr->mb_setOperatorCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode);
				mo_ServicesCachePtr->mb_setValid_From(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
				mo_ServicesCachePtr->mb_setValid_To(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
				

				if(mo_ServicesCachecacheContainer->mb_get((CBase*)mo_ServicesCachePtr,(CBase*&)lo_PMServicesCachePtr))
				{
					if(lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection == "O")
					{	/* For outgoing call get outgoing variables from Service type */						
						lo_PMJobPtr->ga_RatedCdrs[i].gs_rate                =   lo_PMServicesCachePtr->mb_getOutRateIntrConnect() ;
						lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection	     =   lo_PMServicesCachePtr->mb_getOutRateDirection(); 
						lo_PMJobPtr->ga_RatedCdrs[i].gs_PaymentDirection    =   lo_PMServicesCachePtr->mb_getOutPaymentDirection(); 
						lo_PMJobPtr->ga_RatedCdrs[i].gs_RateUnit            =   lo_PMServicesCachePtr->mb_getOutUnit();
						lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationRateZone =	lo_PMServicesCachePtr->mb_getOutDefaultratezone();
						lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationType	 =	lo_PMServicesCachePtr->mb_getOutDestinationtype();
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceType		 =	lo_PMServicesCachePtr->mb_getServiceType();
						//added as per LTE usage for 4.3 release
						lo_PMJobPtr->ga_RatedCdrs[i].gs_destination_traffic_type = lo_PMServicesCachePtr->mb_getOutTrafficType();
						//modification end
					}
					else if (lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection == "I")
					{
						// For Incoming call get Incoming variables from Service type.
						lo_PMJobPtr->ga_RatedCdrs[i].gs_rate                   =  lo_PMServicesCachePtr->mb_getIncRateIntrConnect() ;
						lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection          =  lo_PMServicesCachePtr->mb_getIncRateDirection(); 
						lo_PMJobPtr->ga_RatedCdrs[i].gs_PaymentDirection       =  lo_PMServicesCachePtr->mb_getIncPaymentDirection(); 
						lo_PMJobPtr->ga_RatedCdrs[i].gs_RateUnit               =  lo_PMServicesCachePtr->mb_getIncUnit();
						lo_PMJobPtr->ga_RatedCdrs[i].gn_unitQty                =  lo_PMServicesCachePtr->mb_getIncQtyUnit();
						lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationRateZone    =  lo_PMServicesCachePtr->mb_getIncDefaultratezone();
						lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationType        =  lo_PMServicesCachePtr->mb_getIncDestinationtype();
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceType            =  lo_PMServicesCachePtr->mb_getServiceType();
						//added as per LTE usage for 4.3 release
                                                lo_PMJobPtr->ga_RatedCdrs[i].gs_origin_traffic_type = lo_PMServicesCachePtr->mb_getIncTrafficType();
                                                //modification end
					}

                                        if ((lo_PMServicesCachePtr->mb_gettest_Start_Date() <= lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate)  && (lo_PMServicesCachePtr->mb_gettest_end_date() >= lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate) )
						{								
							lo_PMJobPtr->ga_RatedCdrs[i].gs_DataTypeIndicator = "T";
						}
						else
						{								
							lo_PMJobPtr->ga_RatedCdrs[i].gs_DataTypeIndicator = "C";
						}
				}
				else			
				{ 

					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode                      =       "RATE-SERVICE-NF";
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage                   =       "Cannot find Service for Partner =>||" ;
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage                  +=      lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode  ;
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage                  +=      "||, Agreement Type =>|| ";
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage                  +=      lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType;
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage                  +=      "||, Call Date => ||";
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage                  +=      lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue                     =       lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode ;
					lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="R";

					
					continue;
				}
				
				ls_DroppCdr="";
				ls_dropCode="";
				ls_dropValue="";
				ls_dropMessage="";
				ls_dropCode = "DROP-008";
                ls_dropMessage = "Rate Configured as N for the Service Code: " ;
				ls_dropMessage += lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode;
                ls_dropValue= lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode;

				if(lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection == "O")
				{
					if (lo_PMServicesCachePtr->mb_getOutRateIntrConnect()=="N")
					{
						ls_DroppCdr="Y";
					}
				}
				else if (lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection == "I")
				{
					if (lo_PMServicesCachePtr->mb_getIncRateIntrConnect()=="N")
					{
						ls_DroppCdr="Y";
					}
				}
				if ( ls_DroppCdr=="Y")
				{
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode=ls_dropCode;
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=ls_dropValue;
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage=ls_dropMessage; 
						lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="D";
					continue;
				}
		}	



		*mo_ABLServicePtr <<DEBUG<<"End  :" << lo_PMJobPtr->gs_fileName <<": "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;
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
 
bool PM_ValidateService::mb_stop()
{
	return true;
}
