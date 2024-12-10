#include "PM_FindTierId.h"
#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "ABL_DateTime.h"
#include "ABL_Date.h"
#include "ABL_DbDate.h"
#include "ABL_CacheManager.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_FindTierId()
{
	return ( (Base_Registry*) new PM_FindTierId);
}
}

PM_FindTierId::PM_FindTierId()
{
	//
}

PM_FindTierId::~PM_FindTierId()
{
	//
}

PM_FindTierId::PM_FindTierId(const PM_FindTierId& p_copyObject)
{
	this->mo_ABLServicePtr						=	p_copyObject.mo_ABLServicePtr;	
	this->mo_TierCacheContainer				    =	p_copyObject.mo_TierCacheContainer;		
	this->mo_TierCachePtr					    =	(PM_TierMappingCache*)p_copyObject.mo_TierCachePtr->mb_createCopy();
	this->ms_Stopsignalfile						=	p_copyObject.ms_Stopsignalfile;
}

Base_Registry* PM_FindTierId::mb_clone()
{
	return ( (Base_Registry*) new PM_FindTierId );
}

ABL_Process* PM_FindTierId::mb_createCopy()
{
	return ( new PM_FindTierId (*this));
}

bool PM_FindTierId::mb_initProcess(ABL_CacheManager* pABLCacheManagerPtr, ABL_AgentCommunicator *pABLAgentCommunicatorPtr, ABL_Service *pABLServicePtr)
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

bool PM_FindTierId::mb_getCache(ABL_CacheManager* pABLCacheManagerPtr)
{
	try
	{
		
		mo_TierCacheContainer		=	pABLCacheManagerPtr->mb_getCache("PM_TierMappingCache");
		mo_TierCachePtr		        =	(PM_TierMappingCache*)mo_ABLServicePtr->mb_getObject("PM_TierMappingCache")->mb_clone();
		

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

bool PM_FindTierId::mb_process(ABL_Job* &pABLJobPtr)
{
	PM_Job* lo_PMJobPtr			=   (PM_Job*)pABLJobPtr;
	ABL_String						ls_RejMesg ;
	ABL_String						ls_sql;	
	ABL_String						ls_StartTime[1] ;
	ABL_String						ls_EndTime[1] ;
	ABL_String						ls_TimeType[1];
	double							ln_TtDuration[1];
	PM_TierMappingCache*            lo_TierCachePtr;
	ABL_String						ls_ErrorCode;
	int                             ln_found;
	try
	{
		ls_RejMesg 	=	"";

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
				*mo_ABLServicePtr << DEBUG <<" No Cdrs to find Tier Id for the file: " <<lo_PMJobPtr->gs_fileName<<Endl;	
				return true;          
			}
		}

		*mo_ABLServicePtr << DEBUG << "Start :" <<lo_PMJobPtr->gs_fileName <<" : "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;
       // if the array with events to rate is empty (ratedEventArr), then insert the rejected 
       // and dropped cdrs into database and finish rating for the agreement type


		       
		for(int i = 0;i<lo_PMJobPtr->ga_RatedCdrs.size();i++)
		{
			
			try
			{
				if(lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus=="D" || lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus=="R")
				{
					continue;
				}

				if (strcmp(lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection.c_str(),"B")!=0)
				{
					continue;
				}
                                
                                  if (mo_TierCacheContainer->mb_size()==0)
                {
                   rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
                        *mo_ABLServicePtr << INFO << " There is no records in PM_PARTNER_TIER_DETAILS Rating is  stopping...: "  << Endl;
                        ABL_String ls_command("touch ");
                        ls_command +=ms_Stopsignalfile;
                        system(ls_command.c_str());
                        return false;
                }


				ls_ErrorCode="RATE-TIERID-NF";

				ls_RejMesg= "Cannot find Tier Id => ";
                     ls_RejMesg+="for Origin Group => ";
			         ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginGroup;
                     ls_RejMesg+=", Destination Group => ";
				     ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_DestGroup;
				     ls_RejMesg+=", Partner Code => ";
				     ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
					 
				
				ln_found = 0;
				
				mo_TierCachePtr->mb_setOriginZone(lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginGroup);
				mo_TierCachePtr->mb_setDestinationZone(lo_PMJobPtr->ga_RatedCdrs[i].gs_DestGroup);
				mo_TierCachePtr->mb_setPartnerCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode);
				if(mo_TierCacheContainer->mb_get((CBase*)mo_TierCachePtr,(CBase*&)lo_TierCachePtr))
				{
					lo_PMJobPtr->ga_RatedCdrs[i].gs_Tierid =lo_TierCachePtr->mb_getTier();
					ln_found = 1;
				}

                if ( ln_found==0)
                {

    			mo_TierCachePtr->mb_setOriginZone(lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginGroup);
				mo_TierCachePtr->mb_setDestinationZone(lo_PMJobPtr->ga_RatedCdrs[i].gs_DestGroup);
				mo_TierCachePtr->mb_setPartnerCode("ALL");
				if(mo_TierCacheContainer->mb_get((CBase*)mo_TierCachePtr,(CBase*&)lo_TierCachePtr))
				{
					lo_PMJobPtr->ga_RatedCdrs[i].gs_Tierid =lo_TierCachePtr->mb_getTier();
					ln_found = 1;
				}
                }

				if ( ln_found==0)
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
					std::cout<<"TIER ID NOT FOUND FOR THE : "<<ls_RejMesg<<std::endl;

				}
		
			}//End For Catch
			catch(...)
			{
				rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
				std::cout<<"TIER ID NOT FOUND FOR THE : "<<ls_RejMesg<<std::endl;
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
 
bool PM_FindTierId::mb_stop()
{
	return true;
}
