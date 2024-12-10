#include "PM_FindOrignRateZone.h"
#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "ABL_DateTime.h"
#include "ABL_Date.h"
#include "ABL_DbDate.h"


extern "C" {EXPORT 
Base_Registry* gb_getPM_FindOrignRateZone()
{
	return ( (Base_Registry*) new PM_FindOrignRateZone);
}
}

PM_FindOrignRateZone::PM_FindOrignRateZone()
{
	//
}

PM_FindOrignRateZone::~PM_FindOrignRateZone()
{
	//
}

PM_FindOrignRateZone::PM_FindOrignRateZone(const PM_FindOrignRateZone& p_copyObject)
{
	this->mo_ABLServicePtr					=	p_copyObject.mo_ABLServicePtr;
	this->mo_DestinationCachecacheContainer	=	p_copyObject.mo_DestinationCachecacheContainer;
	this->mm_DestMaxMinLengthMap				=	p_copyObject.mm_DestMaxMinLengthMap;
	this->mo_DestinationCachePtr			=	(PM_DestinationCache*)p_copyObject.mo_DestinationCachePtr->mb_createCopy();
	this->ms_Stopsignalfile					=	p_copyObject.ms_Stopsignalfile;

	this->mo_NumberPlanCachecacheContainer		=	p_copyObject.mo_NumberPlanCachecacheContainer;	
	this->mo_NumberPlanCachePtr					=	(PM_Find_NumberPlanCache*)p_copyObject.mo_NumberPlanCachePtr->mb_createCopy();
	

}
Base_Registry* PM_FindOrignRateZone::mb_clone()
{
	return ( (Base_Registry*) new PM_FindOrignRateZone );
}

ABL_Process* PM_FindOrignRateZone::mb_createCopy()
{
	return ( new PM_FindOrignRateZone (*this));
}

bool PM_FindOrignRateZone::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{	
		mo_ABLServicePtr = p_ABL_ServicePtr;
		p_ABL_AgentCommunicatorPtr->mb_getParameter("STOP_FILE",ms_Stopsignalfile);

		ABL_Connection	lo_ABLConnection;
		ABL_Statement	lo_ABLStatement;
		ABL_ResultSet	lo_ABLResultSet;
		ABL_String		ls_sql;
		try
		{
			lo_ABLConnection.mb_createConnection(*mo_ABLServicePtr);
			ls_sql="SELECT NUMBER_PLAN_CODE ,MIN(LENGTH(DESTINATION)),MAX(LENGTH(DESTINATION)) FROM PM_DESTINATION group by NUMBER_PLAN_CODE";
			lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_sql);		
			lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
			while(lo_ABLResultSet.mb_fetch())
			{

				DestinationMaxMin_Length lDestinationMaxMin_Length;
				lDestinationMaxMin_Length.m_MinLength=lo_ABLResultSet.mb_getInt64(2);
				lDestinationMaxMin_Length.m_MaxLength=lo_ABLResultSet.mb_getInt64(3);
				mm_DestMaxMinLengthMap.insert(std::pair<ABL_String,DestinationMaxMin_Length>(lo_ABLResultSet.mb_getString(1),lDestinationMaxMin_Length) );
			}
			lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
			lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);
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

bool PM_FindOrignRateZone::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	try
	{
		mo_DestinationCachePtr					=	(PM_DestinationCache*)mo_ABLServicePtr->mb_getObject("PM_DestinationCache")->mb_clone();
		mo_DestinationCachecacheContainer			=	p_ABL_CacheManagerPtr->mb_getCache("PM_DestinationCache");

		mo_NumberPlanCachePtr					=	(PM_Find_NumberPlanCache*)mo_ABLServicePtr->mb_getObject("PM_Find_NumberPlanCache")->mb_clone();
		mo_NumberPlanCachecacheContainer		=	p_ABL_CacheManagerPtr->mb_getCache("PM_Find_NumberPlanCache");

	}
	catch(ABL_Exception &e)
	{
		*mo_ABLServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str());  
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

bool PM_FindOrignRateZone::mb_process(ABL_Job* &p_ABL_JobPtr)
{	

	PM_Job* lo_PMJobPtr				=(PM_Job*)p_ABL_JobPtr;	
	
	int								ln_found=0;
	int								ln_MaxLength;
	int								ln_MinLength;
	ABL_String						ls_destinationType;
	ABL_String						ls_destinationNumber;
	ABL_String						ls_RejMesg ;
	lo_PMJobPtr->gs_isNationalNum	="";


	std::map<ABL_String, DestinationMaxMin_Length >::iterator li_OriginMaxMinIterator;
	PM_DestinationCache*	lo_PM_DestinationCachePtr; 
	
	ABL_String			ls_NumberPlanReq;	
	ABL_String			ls_NumberPlanType;
	ABL_String			ls_NumberPlanCode;
	int					i;
    
	PM_Find_NumberPlanCache *lo_PM_Find_NumberPlanCachePtr;

	try
	{

              if ( lo_PMJobPtr->gs_FileStatus == "D" || lo_PMJobPtr->gs_FileStatus == "F" )
                        {
                                return true;
                        }

               *mo_ABLServicePtr << DEBUG << "Start :" <<lo_PMJobPtr->gs_fileName <<" : "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;

		if (mo_DestinationCachecacheContainer->mb_size()==0)
		{
			rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
			*mo_ABLServicePtr << INFO << " There is no records in PM_DESTINATION   Rating is  stopping...: "  << Endl;	
			ABL_String ls_command("touch ");
			ls_command +=ms_Stopsignalfile;
			system(ls_command.c_str()); 
			return false;
		}

       // if the array with events to rate is empty (ratedEventArr), then insert the rejected 
       // and dropped cdrs into database and finish rating for the agreement type
        if (lo_PMJobPtr->ga_RatedCdrs.size()== 0) 
		{
			*mo_ABLServicePtr<<DEBUG<<" No Cdrs for finding the Orign Rate Zone  for the file   : "<<lo_PMJobPtr->gs_fileName  <<Endl;	
			return (true);          
		}

		if (mo_NumberPlanCachecacheContainer->mb_size()==0)
		{
			rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
			*mo_ABLServicePtr << INFO << " There is no records in PM_NUMBER_PLAN or PM_PARTNER_NUMBER_PLAN   Rating is  stopping...: "  << Endl;	
			ABL_String ls_command("touch ");
			ls_command +=ms_Stopsignalfile;
			system(ls_command.c_str()); 
			return false;
		}

         
		for(int i=0 ;i<lo_PMJobPtr->ga_RatedCdrs.size();i++)
		{	
			if(lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus=="D" || lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus=="R")
			{
				continue;
			}
                       
			try
			{
					ls_destinationType=	"";		
					ls_destinationNumber=	"";		
					ls_RejMesg	="";		
					/***** Select A# or B# based on the C# is present or not *****/
					/*if (lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection=="R" )
					{
						continue;
					}*/	
					ls_NumberPlanReq="";
					ls_NumberPlanType="";
					/*if (lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection=="D" )*/
					if (lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection=="O" || lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection=="B")
					{
						ls_NumberPlanReq="Y";
					}
					/*else if (lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection=="D" )*/
					else if (lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection=="D" )
					{
						ls_NumberPlanReq="N";
					}
					/* Changed to do number analysis even if the rate direction is set to 'R'(Default Rate Zone) */
					else if (lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection=="R" )
					{
						ls_NumberPlanReq="N";
					}
					if (lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType=="I" )
					{


							if (lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection == "I")  //incoming
							{	
								ls_NumberPlanType = "P";
							}
							else if (lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection == "O") //Outgoing
							{
								ls_NumberPlanType = "O";
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

				//lo_PMJobPtr->ga_RatedCdrs[i].gs_NumberPlanCode="";
				mo_NumberPlanCachePtr->mb_setNumberPlanType(ls_NumberPlanType);
				mo_NumberPlanCachePtr->mb_setPartnerCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode);
				mo_NumberPlanCachePtr->mb_setAgreementType(lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType);
				mo_NumberPlanCachePtr->mb_setPOI(lo_PMJobPtr->ga_RatedCdrs[i].gs_Poi);					
				mo_NumberPlanCachePtr->mb_setValid_From(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
				mo_NumberPlanCachePtr->mb_setValid_To(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
				if(mo_NumberPlanCachecacheContainer->mb_get((CBase*)mo_NumberPlanCachePtr,(CBase*&)lo_PM_Find_NumberPlanCachePtr))
				{	
						if(ls_NumberPlanReq=="Y" )
						{
							lo_PMJobPtr->ga_RatedCdrs[i].gs_NumberPlanCode =lo_PM_Find_NumberPlanCachePtr->mb_getNumberPlanCode();
						}
						ls_NumberPlanCode="";
						ls_NumberPlanCode=lo_PM_Find_NumberPlanCachePtr->mb_getNumberPlanCode();
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
							//lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode="RATE-NUMPLAN-NF"; commented as per LTE usage for 4.3 release
							lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode="RATE-ORIGINRZ-NF";
							lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode  ;
							lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage=ls_RejMesg; 
							lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="R";
					}
				}
					


				ls_destinationNumber=	lo_PMJobPtr->ga_RatedCdrs[i].gs_ANumber;
				//added as per LTE usage for 4.3 release
				//Check if ANumber is null then take AUserId.
				if(ls_destinationNumber=="" && (lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode == "300" 
								|| lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode == "301"
								|| lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode == "302"))
					ls_destinationNumber=   lo_PMJobPtr->ga_RatedCdrs[i].gs_AUserId;
				//modification end
			
				
				//check if rate direction is origin rate zone and A# is null. if A# is null, then revert to inc route
				if (ls_destinationNumber=="" && lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection== "O") 
				{
					ls_destinationNumber= lo_PMJobPtr->ga_RatedCdrs[i].gs_InRoute;
				}
					//If A# is null where rate direction is Destination, pass the CDR to the next agent and continue with another CDR
				else if (ls_destinationNumber=="" && lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection== "D")  
				{
					continue;
				}

				ls_RejMesg= "Cannot find Origin Rate Zone for => => ";
				ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
				ls_RejMesg+=", Call Date => ";
				ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();
				ls_RejMesg+=", Call Dir => ";
				ls_RejMesg+=	lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection;
				ls_RejMesg+=", Rate Dir => ";
				ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection;
				ls_RejMesg+=",  Number Plan => ";
				ls_RejMesg+=ls_NumberPlanCode;

				if (!(ls_destinationNumber==""))
				{     
					ls_RejMesg+=",  A# =>  ";
					ls_RejMesg+=ls_destinationNumber;
					ls_RejMesg+=",  Is National Num =>  ";
					ls_RejMesg+=lo_PMJobPtr->gs_isNationalNum;
				}
				else
				{      
					ls_RejMesg+=",  In Route =>  ";
					ls_RejMesg+=ls_destinationNumber;
				}
				 /* if the A# is null and rate direction = O (origin), then reject cdr */
				if (ls_destinationNumber=="" &&  lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection == "O") 
				{
					throw ABL_Exception(1,ls_RejMesg.c_str());
				}

				// analyse the number
				lo_PMJobPtr->gs_isNationalNum="N";
				ls_destinationNumber=fnAnalyseNumber(lo_PMJobPtr,ls_destinationNumber);
				//If error while analyzing the number
				/*if (ls_destinationNumber == "")
				{
					throw ABL_Exception(1,ls_RejMesg.c_str());
				}*/

				if (lo_PMJobPtr->gs_isNationalNum=="Y")
				{
					ls_destinationType = "1";
				}
				else
				{
					ls_destinationType = "2";
				}
				ls_RejMesg= "Cannot find Origin Rate Zone for => ";
				ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
				ls_RejMesg+=", Call Date => ";
				ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();
				ls_RejMesg+=", Call Dir => ";
				ls_RejMesg+=	lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection;
				ls_RejMesg+=", Rate Dir => ";
				ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection;
				ls_RejMesg+=",  Number Plan => ";
				ls_RejMesg+=ls_NumberPlanCode;
				ls_RejMesg+=",  A#e =>  ";
				ls_RejMesg+=ls_destinationNumber;
				ls_RejMesg+=",  Is National Num =>  ";
				ls_RejMesg+=lo_PMJobPtr->gs_isNationalNum;
		 
				/********************
				* assumption is that the number will always be in the international format.
				* only short codes will not be in international number format.
				 ********************/	

				ln_found=0;
				ln_MaxLength=0;
				ln_MinLength=0;
				ln_MaxLength=ls_destinationNumber.mb_length();
				li_OriginMaxMinIterator=mm_DestMaxMinLengthMap.find(ls_NumberPlanCode);
				if(li_OriginMaxMinIterator!=mm_DestMaxMinLengthMap.end())
				{
					if (li_OriginMaxMinIterator->second.m_MaxLength<ln_MaxLength)
					{
						ln_MaxLength=li_OriginMaxMinIterator->second.m_MaxLength;
					}
					 ln_MinLength= li_OriginMaxMinIterator->second.m_MinLength;
				}

				for(int j=ln_MaxLength;j>=ln_MinLength;j--)
				{
					mo_DestinationCachePtr->mb_setNumberPlanCode(ls_NumberPlanCode);
					mo_DestinationCachePtr->mb_setDestinationType(ls_destinationType);
					mo_DestinationCachePtr->mb_setDestination(ls_destinationNumber.mb_subStr(0,j));
					mo_DestinationCachePtr->mb_setValid_From(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
					mo_DestinationCachePtr->mb_setValid_To(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
					if(mo_DestinationCachecacheContainer->mb_get((CBase*)mo_DestinationCachePtr,(CBase*&)lo_PM_DestinationCachePtr))
					{
						lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginRateZone=lo_PM_DestinationCachePtr->mb_getRateZone();
						if(lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginRateZone==" ")
						{
							lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginRateZone="";
						}
						lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginDestinationType=lo_PM_DestinationCachePtr->mb_getDestinationType();
					
						
						//added as per LTE usage for 4.3 release
						lo_PMJobPtr->ga_RatedCdrs[i].gs_origin_sub_type = lo_PM_DestinationCachePtr->mb_getDestinationSubType();
						lo_PMJobPtr->ga_RatedCdrs[i].gs_origin_traffic_type = lo_PM_DestinationCachePtr->mb_getTrafficType();
                        lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginGroup   =  lo_PM_DestinationCachePtr->mb_getZoneGroup();
						//modification end
						ln_found=1;
						break;
					}
				}
				
				if (ln_found == 0)
				{
					if((lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection =="O" || lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection =="B")  && lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginRateZone.mb_length()<=1)
					{
						throw ABL_Exception(1,ls_RejMesg.c_str());
					}
				}

               if (lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection =="B" )
                {
                  if ( lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginGroup == "" || lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginGroup == " " )
                   {
                     ls_RejMesg= "Cannot find Origin Zone Group for => ";
                     ls_RejMesg+=", Rate Zone => ";
			         ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginRateZone;
                     ls_RejMesg+=",  Number Plan => ";
				     ls_RejMesg+=ls_NumberPlanCode;
				     ls_RejMesg+=", Call Date => ";
				     ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();
				     ls_RejMesg+=", Rate Dir => ";
				     ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection;
				     ls_RejMesg+=",  A#e =>  ";
				     ls_RejMesg+= ls_destinationNumber;
				     ls_RejMesg+=",  Is National Num =>  ";
				     ls_RejMesg+=lo_PMJobPtr->gs_isNationalNum;
					 
					 throw ABL_Exception(2,ls_RejMesg.c_str());
                   
			       }
			    }

			}// End Try
			catch(ABL_Exception &e)
			{
				if ((ls_RejMesg==""))
				{
					ls_RejMesg= "Cannot find Origin Rate Zone for => "; 
					ls_RejMesg+=ls_destinationNumber;
					ls_RejMesg+=",  not configured for Number Plan => => ";
					ls_RejMesg+= ls_NumberPlanCode  ;
				}

				if (e.mb_getErrorCode()== 1)
				{
				lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode="RATE-ORIGINRZ-NF";
				lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=ls_destinationNumber;
				lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage=ls_RejMesg; 
				lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="R";
				}
				else
                {
				lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode="RATE-ORIGINGR-NF";
				lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=ls_destinationNumber;
				lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage=ls_RejMesg; 
				lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="R";

				}


			}//End Catch
			catch(...)
			{
				rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
				ABL_String l_command("touch ");
				l_command +=ms_Stopsignalfile;
				system(l_command.c_str()); 	
				*mo_ABLServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
				return false;
			}	
			
		}//End Loop


		*mo_ABLServicePtr<<DEBUG<<"End  :" << lo_PMJobPtr->gs_fileName <<": "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;

	}//End Try
	catch(ABL_Exception &e)
	{
		rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
		*mo_ABLServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str());  		
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

ABL_String PM_FindOrignRateZone :: fnAnalyseNumber(PM_Job * &p_ABL_JobPtr, ABL_String destination_number)
{
	int i=0;
	PM_Job* l_PM_Job_Temp_Ptr = (PM_Job*)p_ABL_JobPtr;
	ABL_String l_tempdestinationnumber;
	try
	{
                       
			/**** Copy the Original Destination number to the temp variable ****/
			l_tempdestinationnumber="";
			l_tempdestinationnumber=destination_number;
			/*Check if the country code is present	If present then remove the country code from the number*/
		/*	if (l_tempdestinationnumber.mb_subStr(0,2)== "00") 
			{
				l_tempdestinationnumber = l_tempdestinationnumber.mb_subStr(2,l_tempdestinationnumber.mb_length()-2);
			}
			else
			{
				if (l_tempdestinationnumber.mb_subStr(0,1) == "0") 
				  l_tempdestinationnumber = l_tempdestinationnumber.mb_subStr(1,l_tempdestinationnumber.mb_length()-1);
				
			}	
              */
                                             
		//if((l_tempdestinationnumber.mb_subStr(0,l_PM_Job_Temp_Ptr->ga_ControlParams[0].gs_CountryDiallingCode.mb_length())==l_PM_Job_Temp_Ptr->ga_ControlParams[0].gs_CountryDiallingCode)||l_tempdestinationnumber.mb_length()<=l_PM_Job_Temp_Ptr->ga_ControlParams[0].gn_NationalNumberLength)
				if((l_tempdestinationnumber.mb_subStr(0,l_PM_Job_Temp_Ptr->ga_ControlParams[0].gs_CountryDiallingCode.mb_length())==l_PM_Job_Temp_Ptr->ga_ControlParams[0].gs_CountryDiallingCode))
				l_PM_Job_Temp_Ptr->gs_isNationalNum="Y";
			else
				l_PM_Job_Temp_Ptr->gs_isNationalNum="N";				
			return (l_tempdestinationnumber);

	}
	catch(ABL_Exception &e)
	{
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str()); 		
		*mo_ABLServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
		//p_ABL_JobPtr->gs_RejMesg = e.mb_getMessage();
		return "";
	}
	catch(...)
	{
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str()); 	
		*mo_ABLServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return "";
	}	
} 
bool PM_FindOrignRateZone::mb_stop()
{
	return true;
}


