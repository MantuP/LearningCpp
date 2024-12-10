/***********************************************************
************************************************************
************************************************************
Agent Name:  PM_DeriveService.cpp
Module Name: FrameWork Rating
Dated: 21/01/2010
************************************************************
************************************************************
***********************************************************/
#include "PM_DeriveService.h"
#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "PM_Job.h"
#include "string"
#include "ABL_CacheManager.h"
#include "ABL_DbDate.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_DeriveService()
{
	return ( (Base_Registry*) new PM_DeriveService);
}
}

PM_DeriveService::PM_DeriveService()
{
	//
}

PM_DeriveService::~PM_DeriveService()
{
	//
}

PM_DeriveService::PM_DeriveService(const PM_DeriveService& p_copyObject)
{
	this->mo_ABLServicePtr							=	p_copyObject.mo_ABLServicePtr;
	this->mo_DeriveServicesCachecacheContainer		=	p_copyObject.mo_DeriveServicesCachecacheContainer;	
	this->mo_DeriveServicesCachePtr				=	(PM_DeriveServicesCache*)p_copyObject.mo_DeriveServicesCachePtr->mb_createCopy();
	this->ms_Stopsignalfile							=	p_copyObject.ms_Stopsignalfile;
}
Base_Registry* PM_DeriveService::mb_clone()
{
	return ( (Base_Registry*) new PM_DeriveService );
}

ABL_Process* PM_DeriveService::mb_createCopy()
{
	return ( new PM_DeriveService (*this));
}

bool PM_DeriveService::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{	
	try
	{
		mo_ABLServicePtr = p_ABL_ServicePtr;
		p_ABL_AgentCommunicatorPtr->mb_getParameter("STOP_FILE",ms_Stopsignalfile);
	}
	catch(ABL_Exception &e)
	{
		*mo_ABLServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;
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

bool PM_DeriveService::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	try
	{
		mo_DeriveServicesCachePtr	        =     (PM_DeriveServicesCache*)mo_ABLServicePtr->mb_getObject("PM_DeriveServicesCache")->mb_clone();
		mo_DeriveServicesCachecacheContainer	=	p_ABL_CacheManagerPtr->mb_getCache("PM_DeriveServicesCache");
	}
	catch(ABL_Exception &e)
	{
		*mo_ABLServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;
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

bool PM_DeriveService::mb_process(ABL_Job* &p_ABL_JobPtr)
{
	PM_Job* lo_PMJobPtr = (PM_Job*)p_ABL_JobPtr;	
	ABL_String	ls_DroppCdr;
	
	ABL_String ls_dropCode;
	ABL_String ls_dropValue;
	ABL_String ls_dropMessage;
	PM_DeriveServicesCache      *lo_PM_DeriveServicesCachePtr; 	

	try
	{  

		// if the array with events to rate is empty (ratedEventArr), then insert the rejected 
		// and dropped cdrs into database and finish rating for the agreement type

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
			*mo_ABLServicePtr << DEBUG <<"  No Cdrs for finding the partner's services for the file   : " <<lo_PMJobPtr->gs_fileName<<Endl;	
			return true;          
			}
		}

		*mo_ABLServicePtr << DEBUG << "Start :" <<lo_PMJobPtr->gs_fileName <<" : "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;

		if (mo_DeriveServicesCachecacheContainer->mb_size()==0)
		{
			return true;
		}

		
		//	get the partner code [and poi] from the
		//	1. inc route or out route in case of interconnect
		//	2. imsi in case of roaming	

		for (int i=0; i<lo_PMJobPtr->ga_RatedCdrs.size(); i++ )
		{
			if(lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus=="D" || lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus=="R")
			{
				continue;
			}

            mo_DeriveServicesCachePtr->mb_setOperatorCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode);
			mo_DeriveServicesCachePtr->mb_setPoi(lo_PMJobPtr->ga_RatedCdrs[i].gs_Poi);
            mo_DeriveServicesCachePtr->mb_setCallDirection(lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection);
			mo_DeriveServicesCachePtr->mb_setbasic_service(lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode);	
			mo_DeriveServicesCachePtr->mb_setANumber(lo_PMJobPtr->ga_RatedCdrs[i].gs_ANumber);
			mo_DeriveServicesCachePtr->mb_setBNumber(lo_PMJobPtr->ga_RatedCdrs[i].gs_BNumber);
			mo_DeriveServicesCachePtr->mb_setCamel(lo_PMJobPtr->ga_RatedCdrs[i].gs_CamelFlag);
			mo_DeriveServicesCachePtr->mb_setValid_From(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
			mo_DeriveServicesCachePtr->mb_setValid_To(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
			
    		
			
			if(mo_DeriveServicesCachecacheContainer->mb_get((CBase*)mo_DeriveServicesCachePtr,(CBase*&)lo_PM_DeriveServicesCachePtr))
			{
			
				if (lo_PM_DeriveServicesCachePtr->mb_getDefaultratezone()=="Y") 
				{
					 lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection   ="R";
				}
				else
				{
					lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection   	 =   	lo_PM_DeriveServicesCachePtr->mb_getRateDirection();
				}

				    lo_PMJobPtr->ga_RatedCdrs[i].gs_PaymentDirection=       lo_PM_DeriveServicesCachePtr->mb_getPaymentDirection();
					lo_PMJobPtr->ga_RatedCdrs[i].gs_RateUnit	=       lo_PM_DeriveServicesCachePtr->mb_getRateUnit();
					lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationType	=       lo_PM_DeriveServicesCachePtr->mb_getDestinationtype();
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceType	=       lo_PM_DeriveServicesCachePtr->mb_getServiceType();
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode	=       lo_PM_DeriveServicesCachePtr->mb_getServiceCode();
					lo_PMJobPtr->ga_RatedCdrs[i].gs_DerivedServiceCode	= lo_PM_DeriveServicesCachePtr->mb_getbasic_service();
					lo_PMJobPtr->ga_RatedCdrs[i].gs_destination_traffic_type = lo_PM_DeriveServicesCachePtr->mb_getTrafficType();
					lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginDestinationType   =     lo_PM_DeriveServicesCachePtr->mb_getDestinationtype();
				
			
					
				if ((lo_PM_DeriveServicesCachePtr->mb_gettest_Start_Date() <= lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate)  && 
					(lo_PM_DeriveServicesCachePtr->mb_gettest_end_date() >= lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate) )
				{								
					lo_PMJobPtr->ga_RatedCdrs[i].gs_DataTypeIndicator = "T";
						
				}
				else
				{		
			
					lo_PMJobPtr->ga_RatedCdrs[i].gs_DataTypeIndicator = "C";
				}

				if ( lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection =="O") 
				{
                  lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginRateZone          =      lo_PM_DeriveServicesCachePtr->mb_getRateZone();
				}
				else
                {
                  lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationRateZone     =      lo_PM_DeriveServicesCachePtr->mb_getRateZone();
				}

                std::string ls_Ratezone=lo_PM_DeriveServicesCachePtr->mb_getRateZone().c_str();
				mb_trim(ls_Ratezone);
				if ( lo_PM_DeriveServicesCachePtr->mb_getDefaultratezone()=="Y" && ls_Ratezone=="")
				{
                    			lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage       = "Cannot check default rate for Partner =>||" ;  
                    			lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage      += lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode ;  
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode="RATE-SERVPARAM-NF";
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue= lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode ;
					lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="R";
					continue;
				}
				
			   	   if (lo_PM_DeriveServicesCachePtr->mb_getRateDirection()=="N")
			   	   {
					
                                        lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode="DROP-009";
                                        lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode;
                                        lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage="Rate Configured as N for the Service Code: " ;
                                        lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage += lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode;
                                        lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="D";
                                        continue;

			   	   }

		  	}

		} 

		*mo_ABLServicePtr<<DEBUG<<"End  :" << lo_PMJobPtr->gs_fileName <<": "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;
        }
        catch(ABL_Exception &e)
        {
		rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
		*mo_ABLServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;
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

bool PM_DeriveService::mb_stop()
{
        return true;
}

void PM_DeriveService::mb_trim(std::string &p_string)
{
                bool l_leftSpace = false;
        bool l_rightSpace = false;

        for(size_t l_icount = 0;l_icount < p_string.size(); ++l_icount)
        {
                if(' ' != p_string[l_icount]/* && '\t' != p_string[l_icount] && '\r' != p_string[l_icount]*/)
                {
                        p_string = p_string.substr(l_icount);
                        l_leftSpace = true;
                        break;
                }
        }

        for(int l_icount = (int)(p_string.size() - 1); l_icount >= 0; --l_icount)
        {
                if(' ' != p_string[l_icount]/* && '\t' != p_string[l_icount] && '\r' != p_string[l_icount]*/)
                {
                        p_string = p_string.substr(0, l_icount+1);
                        l_rightSpace = true;
                        break;
                }
        }

        if( l_leftSpace == false && l_rightSpace == false)
        {

                p_string = p_string.substr(0,1);
                                p_string="";
        }

}
