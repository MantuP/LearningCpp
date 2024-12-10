/***********************************************************
************************************************************
************************************************************
Agent Name:  "PM_FetchPartners_ServicesParameters.cpp
Module Name: FrameWork Rating
Dated: 21/01/2010

Last modified by Sangram Kesahari Satapathy for LTE usage for 4.3 release
Date: 12/06/2012
************************************************************
************************************************************
***********************************************************/

#include "PM_FetchPartners_ServicesParameters.h"
#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "ABL_DateTime.h"
#include "ABL_Date.h"
#include "ABL_DbDate.h"
extern "C" {EXPORT
Base_Registry* gb_getPM_FetchPartners_ServicesParameters()
{
        return ( (Base_Registry*) new PM_FetchPartners_ServicesParameters);
}
	   }

PM_FetchPartners_ServicesParameters::PM_FetchPartners_ServicesParameters()
{
        //
}

PM_FetchPartners_ServicesParameters::~PM_FetchPartners_ServicesParameters()
{
        //
}

PM_FetchPartners_ServicesParameters::PM_FetchPartners_ServicesParameters(const PM_FetchPartners_ServicesParameters& p_copyObject)
{
        this->mo_ABLServicePtr												=       p_copyObject.mo_ABLServicePtr;
        this->mo_FetchPartnersServicesParametersCacheContainer				=       p_copyObject.mo_FetchPartnersServicesParametersCacheContainer;
        this->mo_FetchPartnersServicesParametersCachePtr					=       (PM_FetchPartners_ServicesParametersCache*)p_copyObject.mo_FetchPartnersServicesParametersCachePtr->mb_createCopy();
		this->ms_Stopsignalfile												=		p_copyObject.ms_Stopsignalfile;					
}

Base_Registry* PM_FetchPartners_ServicesParameters::mb_clone()
{
        return ( (Base_Registry*) new PM_FetchPartners_ServicesParameters );
}

ABL_Process* PM_FetchPartners_ServicesParameters::mb_createCopy()
{
        return ( new PM_FetchPartners_ServicesParameters (*this));
}

bool PM_FetchPartners_ServicesParameters::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
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

bool PM_FetchPartners_ServicesParameters::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	try
	{
			mo_FetchPartnersServicesParametersCachePtr		= (PM_FetchPartners_ServicesParametersCache*)mo_ABLServicePtr->mb_getObject("PM_FetchPartners_ServicesParametersCache")->mb_clone();
			mo_FetchPartnersServicesParametersCacheContainer    = p_ABL_CacheManagerPtr->mb_getCache("PM_FetchPartners_ServicesParametersCache");
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

bool PM_FetchPartners_ServicesParameters::mb_process(ABL_Job* &p_ABL_JobPtr)
{
	PM_Job* lo_PMJobPtr = (PM_Job*)p_ABL_JobPtr;

	PM_FetchPartners_ServicesParametersCache   	*lo_PM_ServicesParametersCachePtr;
	//added as per LTE usage for 4.3 release
	gr_RejectedCdr          lr_RejectedCdrs;  //Creating an object of the structure Ic_Rejected_Cdr.
	ABL_String      ls_RejMesg="" ;
	ABL_String ls_CallType;
	ABL_String      ls_RateAction="";
	ABL_String		ls_DroppCdr;
	ABL_String		ls_dropCode;
	ABL_String		ls_dropValue;
	ABL_String		ls_dropMessage;
	//modification end

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
				*mo_ABLServicePtr << DEBUG <<"No Cdrs for finding the partner's services for the file   : " <<lo_PMJobPtr->gs_fileName<<Endl;	
				return true;          
			}
		}

		*mo_ABLServicePtr << DEBUG << "Start :" <<lo_PMJobPtr->gs_fileName <<" : "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;

		if (mo_FetchPartnersServicesParametersCacheContainer->mb_size()==0 )
		{
			rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
			*mo_ABLServicePtr << INFO << " There is no records in PM_SERVICE_POI rating has stopped. "<<Endl;
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

			ABL_String ls_DerivedServiceCode=lo_PMJobPtr->ga_RatedCdrs[i].gs_DerivedServiceCode;
			std::string ls_DServiceCode=ls_DerivedServiceCode.c_str();
			mb_trim(ls_DServiceCode);
			ls_DerivedServiceCode=ls_DServiceCode;
			if(strcmp(ls_DerivedServiceCode.c_str(),"")!=0)
			{
			 continue;
			}
			
			    	mo_FetchPartnersServicesParametersCachePtr->mb_setServiceCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode);
					mo_FetchPartnersServicesParametersCachePtr->mb_setPartnerCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode);
            		mo_FetchPartnersServicesParametersCachePtr->mb_setPoi(lo_PMJobPtr->ga_RatedCdrs[i].gs_Poi);
            		mo_FetchPartnersServicesParametersCachePtr->mb_setCallDirection(lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection);
            		mo_FetchPartnersServicesParametersCachePtr->mb_setValidFrom(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
            		mo_FetchPartnersServicesParametersCachePtr->mb_setValidTill(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
			

			if(mo_FetchPartnersServicesParametersCacheContainer->mb_get((CBase*)mo_FetchPartnersServicesParametersCachePtr,
			  (CBase*&)lo_PM_ServicesParametersCachePtr))
  			{
				if (lo_PM_ServicesParametersCachePtr->mb_getApplyDefaultRate()=="Y") 
				{
					 lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection   ="R";
				}
				else
				{
					lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection   	 =   	lo_PM_ServicesParametersCachePtr->mb_getRateDirection();
				}

				lo_PMJobPtr->ga_RatedCdrs[i].gs_PaymentDirection        =      lo_PM_ServicesParametersCachePtr->mb_getPaymentDirection();
				
				
				lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationType         =      lo_PM_ServicesParametersCachePtr->mb_getDestinationType();
				lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginDestinationType   =      lo_PM_ServicesParametersCachePtr->mb_getDestinationType();
				
			
                lo_PMJobPtr->ga_RatedCdrs[i].gs_RateUnit                =      lo_PM_ServicesParametersCachePtr->mb_getRateUnit();
				ls_RateAction                                           =      lo_PM_ServicesParametersCachePtr->mb_getRateAction();  

     			
				if ((lo_PM_ServicesParametersCachePtr->mb_getTestStartDate() <= lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate)  && 
					(lo_PM_ServicesParametersCachePtr->mb_getTestEndDate() >= lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate) )
				{								
					lo_PMJobPtr->ga_RatedCdrs[i].gs_DataTypeIndicator = "T";
						
				}
				else
				{		
			
					lo_PMJobPtr->ga_RatedCdrs[i].gs_DataTypeIndicator = "C";
				}

				if ( lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection =="O") 
				{
                  lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginRateZone          =      lo_PM_ServicesParametersCachePtr->mb_getRateZone();
				}
				else
                {
                  lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationRateZone     =      lo_PM_ServicesParametersCachePtr->mb_getRateZone();
				}
				
                                lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceType              =      lo_PM_ServicesParametersCachePtr->mb_getServiceType();
				std::string ls_Ratezone=lo_PM_ServicesParametersCachePtr->mb_getRateZone().c_str();
				mb_trim(ls_Ratezone);
				if ( lo_PM_ServicesParametersCachePtr->mb_getApplyDefaultRate()=="Y" && ls_Ratezone=="")
				{
                    			lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage       = "Cannot check default rate for Partner =>||" ;  
                    			lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage      += lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode ;  
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode="RATE-SERVPARAM-NF";
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue= lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode ;
					lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="R";
					continue;
				}
				
				ls_dropCode = "DROP-008";
                ls_dropMessage = "Rate Configured as N for the Service Code: " ;
				ls_dropMessage += lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode;
                ls_dropValue= lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode;
                
                
                if( ls_RateAction == "D")
				{
					    lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode=ls_dropCode;
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=ls_dropValue;
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage=ls_dropMessage; 
						lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="D";
					    continue;
				}  
				
				


			}
	else			
				{ 

					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode                      =       "RATE-SERVICE-POI-NF";
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage                   =       "Cannot find Service for Partner =>||" ;
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage                  +=      lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode  ;
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage                  +=      "||, Agreement Type =>|| ";
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage                  +=      lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType;
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage                  +=      "||, Call Date => ||";
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage                  +=      lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();
                    lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage                  +=      "||, POI => ||";
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage                  +=      lo_PMJobPtr->ga_RatedCdrs[i].gs_Poi;
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue                     =      lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode ;
					lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="R";

					
					continue;
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

bool PM_FetchPartners_ServicesParameters::mb_stop()
{
        return true;
}


/*Fuction to remove the leading n trailing spaces in a string.*/
void PM_FetchPartners_ServicesParameters::mb_trim(std::string &p_string)
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
