#include "PM_FindDestinationRateZone.h"
#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "ABL_DateTime.h"
#include "ABL_Date.h"
#include "ABL_DbDate.h"

/* remove_whitespace  added by prabina for the defect and revenue loss. on 06092023 */

extern "C" {EXPORT 
Base_Registry* gb_getPM_FindDestinationRateZone()
{
	return ( (Base_Registry*) new PM_FindDestinationRateZone);
}
}

PM_FindDestinationRateZone::PM_FindDestinationRateZone()
{
	//
}

PM_FindDestinationRateZone::~PM_FindDestinationRateZone()
{
	//
}

PM_FindDestinationRateZone::PM_FindDestinationRateZone(const PM_FindDestinationRateZone& p_copyObject)
{
	this->mo_ABLServicePtr							=	p_copyObject.mo_ABLServicePtr;
	this->mo_DestinationCachecacheContainer			=	p_copyObject.mo_DestinationCachecacheContainer;	
	this->mo_PartnerShortCodesCachecacheContainer	=	p_copyObject.mo_PartnerShortCodesCachecacheContainer;	
	this->mo_DestinationCachePtr					=	(PM_DestinationCache*)p_copyObject.mo_DestinationCachePtr->mb_createCopy();
	this->mo_FindPartnerShortCodesCachePtr			=	(PM_FindPartnerShortCodesCache*)p_copyObject.mo_FindPartnerShortCodesCachePtr->mb_createCopy();
	this->mm_DestMaxMinLengthMap					=	p_copyObject.mm_DestMaxMinLengthMap;
	this->ms_Stopsignalfile							=	p_copyObject.ms_Stopsignalfile;
}

Base_Registry* PM_FindDestinationRateZone::mb_clone()
{
	return ( (Base_Registry*) new PM_FindDestinationRateZone );
}

ABL_Process* PM_FindDestinationRateZone::mb_createCopy()
{
	return ( new PM_FindDestinationRateZone (*this));
}

bool PM_FindDestinationRateZone::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{	
	
	mo_ABLServicePtr = p_ABL_ServicePtr;

	ABL_Connection	lo_ABLConnection;
	ABL_Statement	lo_ABLStatement;
	ABL_ResultSet	lo_ABLResultSet;
	ABL_String		ls_sql;

try
	{
		p_ABL_AgentCommunicatorPtr->mb_getParameter("STOP_FILE",ms_Stopsignalfile);
		
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

bool PM_FindDestinationRateZone::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	try
	{
		mo_DestinationCachePtr                =   (PM_DestinationCache*)mo_ABLServicePtr->mb_getObject("PM_DestinationCache")->mb_clone();		
		mo_FindPartnerShortCodesCachePtr	    =   (PM_FindPartnerShortCodesCache*)mo_ABLServicePtr->mb_getObject("PM_FindPartnerShortCodesCache")->mb_clone();

		mo_DestinationCachecacheContainer       =    p_ABL_CacheManagerPtr->mb_getCache("PM_DestinationCache");		
		mo_PartnerShortCodesCachecacheContainer	=    p_ABL_CacheManagerPtr->mb_getCache("PM_FindPartnerShortCodesCache");		

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

bool PM_FindDestinationRateZone::mb_process(ABL_Job* &p_ABL_JobPtr)
{	

	PM_Job* lo_PMJobPtr				=	(PM_Job*)p_ABL_JobPtr;	
	ABL_String								ls_destinationType;
	ABL_String								ls_destinationNumber;
	ABL_String								ls_RejMesg ;
	lo_PMJobPtr->gs_isNationalNum			="";
	ABL_String								ls_NumberPlanCode ;
	ABL_String								ls_BrokerCountryCode;	
	int										ln_found=0;	
	int										ln_MaxLength;
	int										ln_MinLength;
	std::map<ABL_String, DestinationMaxMin_Length >::iterator li_DestMaxMinIterator;
	PM_DestinationCache*				lobj_PM_DestinationCachePtr;
	PM_FindPartnerShortCodesCache*		lobj_PM_FindPartnerShortCodesCachePtr;

	try
	{
	
		if (lo_PMJobPtr->ga_RatedCdrs.size()== 0) 
		{
			if (lo_PMJobPtr->gs_IsGPRSFile=="YES")
			{
				return true;
			}
			else
			{
				*mo_ABLServicePtr << DEBUG <<"  No Cdrs for finding the Destination  Rate Zone  of the file: " <<lo_PMJobPtr->gs_fileName<<Endl;	
				return true;          
			}
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


		for(int i=0 ;i<lo_PMJobPtr->ga_RatedCdrs.size();i++)
		{	
			try
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


				
				// for outgoing calls (includes transit and forwarded calls, take B# as the origin number.in case of incoming calls, take A# as origin number.

				ls_destinationNumber=	lo_PMJobPtr->ga_RatedCdrs[i].gs_BNumber;
				//added as per LTE usage for 4.3 release
                                //Check if ANumber is null then take AUserId.
                                if(ls_destinationNumber=="" && (lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode == "300"
                                                                || lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode == "301"
								|| lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode == "302"))
                                        ls_destinationNumber=   lo_PMJobPtr->ga_RatedCdrs[i].gs_BUserId;
                                //modification end
			
				if (!(mo_PartnerShortCodesCachecacheContainer->mb_size()==0))
				{
					mo_FindPartnerShortCodesCachePtr->mb_setPartnerCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode);
					mo_FindPartnerShortCodesCachePtr->mb_setShortCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_BNumber);
				
					if(mo_PartnerShortCodesCachecacheContainer->mb_get((CBase*)mo_FindPartnerShortCodesCachePtr,(CBase*&)lobj_PM_FindPartnerShortCodesCachePtr))
					{
						if ((!(lobj_PM_FindPartnerShortCodesCachePtr->mb_getTranslatedNumber()==" ")) && (!(lobj_PM_FindPartnerShortCodesCachePtr->mb_getTranslatedNumber()=="")))
						{
							lo_PMJobPtr->ga_RatedCdrs[i].gs_BNumber = lobj_PM_FindPartnerShortCodesCachePtr->mb_getTranslatedNumber();
                                                ls_destinationNumber=   lo_PMJobPtr->ga_RatedCdrs[i].gs_BNumber;

						}
						
					}
				}
			

				//  for in-roamer SMS cdrs, rate based on the SMSC id
				if (lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode == "003" && lo_PMJobPtr->ga_RatedCdrs[i].gs_Charge_SMSMO_SMSC_flg == "Y") 
				{
					if (lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection == "O")
					{
						ls_destinationNumber = lo_PMJobPtr->ga_RatedCdrs[i].gs_OutRoute;
					}
					else if (lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection == "I")
					{
						ls_destinationNumber = lo_PMJobPtr->ga_RatedCdrs[i].gs_InRoute;
					}
				}   


           
				ls_RejMesg= "Cannot find Dest Rate Zone for => ";
				ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
				ls_RejMesg+=", Call Date => ";
				ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();
				ls_RejMesg+=", Call Dir => ";
				ls_RejMesg+=	lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection;
				ls_RejMesg+=", Rate Dir => ";
				ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection;
				ls_RejMesg+=",  Number Plan => ";
				ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_NumberPlanCode;
				ls_RejMesg+=",B# => ";
				ls_RejMesg+=ls_destinationNumber;



				 /* if the B# is null and rate direction = D (Destination), then reject cdr */
				if (ls_destinationNumber == "" &&  lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection == "D") 
				{
					throw  ABL_Exception(1,ls_RejMesg.c_str());
				}
					// analyse the number

				lo_PMJobPtr->gs_isNationalNum="N";

				ls_destinationNumber=fnAnalyseNumber(lo_PMJobPtr,ls_destinationNumber);


				if (ls_destinationNumber == "")
				{

					throw ABL_Exception(1,ls_RejMesg.c_str());

				}

           if (!lo_PMJobPtr->ga_RatedCdrs[i].gs_Mnp.mb_empty())
                {
                ls_destinationNumber=lo_PMJobPtr->ga_RatedCdrs[i].gs_Mnp+ls_destinationNumber;
				ls_destinationNumber = remove_whitespace(ls_destinationNumber.c_str());
											                 
			    }

				if (lo_PMJobPtr->gs_isNationalNum=="Y")
				{
					ls_destinationType = "1";
				}
				else
				{
					ls_destinationType = "2";
				}


				ls_RejMesg= "Cannot find Dest Rate Zone for => ";
				ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
				ls_RejMesg+=", Call Date => ";
				ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();
				ls_RejMesg+=", Call Dir => ";
				ls_RejMesg+=	lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection;
				ls_RejMesg+=", Rate Dir => ";
				ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection;
				ls_RejMesg+=",  Number Plan => ";
				ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_NumberPlanCode;
				ls_RejMesg+=",  B# =>  ";
				ls_RejMesg+=ls_destinationNumber;
				ls_RejMesg+=",  Is National Num =>  ";
				ls_RejMesg+=lo_PMJobPtr->gs_isNationalNum;
			 
				/*assumption is that the number will always be in the international format.only short codes will not be in international number format.*/					
				ln_found=0;
				ln_MaxLength=0;
				ln_MinLength=0;
				ln_MaxLength=ls_destinationNumber.mb_length();
				li_DestMaxMinIterator=mm_DestMaxMinLengthMap.find(lo_PMJobPtr->ga_RatedCdrs[i].gs_NumberPlanCode);
				if(li_DestMaxMinIterator!=mm_DestMaxMinLengthMap.end())
				{
					if (li_DestMaxMinIterator->second.m_MaxLength<ln_MaxLength)
					{
						ln_MaxLength=li_DestMaxMinIterator->second.m_MaxLength;
					}
					 ln_MinLength= li_DestMaxMinIterator->second.m_MinLength;
				}
					ABL_String ls_Destionation="";

				for(int j=ln_MaxLength;j>=ln_MinLength-1;j--)
				{

					ls_Destionation="";
					ls_Destionation=ls_destinationNumber.mb_subStr(0,j);
					mo_DestinationCachePtr->mb_setDestination(ls_Destionation);
					mo_DestinationCachePtr->mb_setNumberPlanCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_NumberPlanCode);
					mo_DestinationCachePtr->mb_setDestinationType(ls_destinationType);
					mo_DestinationCachePtr->mb_setValid_From(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
					mo_DestinationCachePtr->mb_setValid_To(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
					
					//*mo_ABLServicePtr<<DEBUG<<"Dest  :"<< ls_Destionation <<" : "<<ls_destinationType<<" : " <<lo_PMJobPtr->ga_RatedCdrs[i].gs_NumberPlanCode.c_str() <<Endl;

					if(mo_DestinationCachecacheContainer->mb_get((CBase*)mo_DestinationCachePtr,(CBase*&)lobj_PM_DestinationCachePtr))
					{
						ln_found=1;
						lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationRateZone=lobj_PM_DestinationCachePtr->mb_getRateZone();
						if ((!(ls_BrokerCountryCode =="")) && lobj_PM_DestinationCachePtr->mb_getDestination().mb_subStr(0,ls_BrokerCountryCode.mb_length()) == ls_BrokerCountryCode)
						{
							lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationType = "1";
						}
						else
						{
							lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationType=lobj_PM_DestinationCachePtr->mb_getDestinationType();
						}              
						lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationSubType = lobj_PM_DestinationCachePtr->mb_getDestinationSubType();
						//added as per LTE usage for 4.3 release
                                                lo_PMJobPtr->ga_RatedCdrs[i].gs_destination_traffic_type = lobj_PM_DestinationCachePtr->mb_getTrafficType();
                                                //modification end
						
						break;
					}
				}	


				if(ln_found == 0)
				{
					if(lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection =="D" && lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationRateZone.mb_length()<=1)
					{
					
						throw  ABL_Exception(1,ls_RejMesg.c_str());
					}
				}

		}
		catch(ABL_Exception &e)
		{
			if (!(ls_RejMesg==""))
			{
				ls_RejMesg					="Cannot find Dest Rate Zone for => ";
				ls_RejMesg					+=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
				ls_RejMesg					+=", Call Date => ";
				ls_RejMesg					+=lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();
				ls_RejMesg					+=", Call Dir => ";
				ls_RejMesg					+=	lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection;
				ls_RejMesg					+=", Rate Dir => ";
				ls_RejMesg					+=lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection;
				ls_RejMesg					+=",  Number Plan => ";
				ls_RejMesg					+=lo_PMJobPtr->ga_RatedCdrs[i].gs_NumberPlanCode;
				ls_RejMesg					+=",  B# =>  ";
				ls_RejMesg					+=ls_destinationNumber;
				ls_RejMesg					+=",  Is National Num =>  ";
				ls_RejMesg					+=lo_PMJobPtr->gs_isNationalNum ;
			}

			lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode="RATE-DESTRZ-NF";
			lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=ls_destinationNumber;
			lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage=ls_RejMesg;
			lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="R";

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
	
	*mo_ABLServicePtr<<DEBUG<<"End  :"<< lo_PMJobPtr->gs_fileName <<": "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;
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

/* Function Name : fnDestinationRateZone()
** Purpose       : Get the Destination Rate Zone for the destination number
*/
ABL_String PM_FindDestinationRateZone :: fnAnalyseNumber(PM_Job * &p_ABL_JobPtr, ABL_String in_destination_number)
{	//std::cout<<"Inside Function"<<std::endl;
	int i=0;
	PM_Job* lobj_PMJobTempPtr = (PM_Job*)p_ABL_JobPtr;
	ABL_String ls_tempdestinationnumber;
	try
	{
		//std::cout<<"Inside Try"<<std::endl;
		/**** Copy the Original Destination number to the temp variable ****/
			ls_tempdestinationnumber="";
			ls_tempdestinationnumber=in_destination_number;
			/*Check if the country code is present	If present then remove the country code from the number*/
			if (ls_tempdestinationnumber.mb_subStr(0,2)== "00") 
			{
				ls_tempdestinationnumber = ls_tempdestinationnumber.mb_subStr(2,ls_tempdestinationnumber.mb_length()-2);
			}
			else
			{
				if (ls_tempdestinationnumber.mb_subStr(0,1) == "0") 
				  ls_tempdestinationnumber = ls_tempdestinationnumber.mb_subStr(1,ls_tempdestinationnumber.mb_length()-1);
				
			}
			//Commented as per Ghana 4.1
			//if((ls_tempdestinationnumber.mb_subStr(0,lobj_PMJobTempPtr->ga_ControlParams[0].gs_CountryDiallingCode.mb_length())==lobj_PMJobTempPtr->ga_ControlParams[0].gs_CountryDiallingCode)||(ls_tempdestinationnumber.mb_length()<=lobj_PMJobTempPtr->ga_ControlParams[0].gn_NationalNumberLength))
			if((ls_tempdestinationnumber.mb_subStr(0,lobj_PMJobTempPtr->ga_ControlParams[0].gs_CountryDiallingCode.mb_length())==lobj_PMJobTempPtr->ga_ControlParams[0].gs_CountryDiallingCode))
				lobj_PMJobTempPtr->gs_isNationalNum="Y";
			else
				lobj_PMJobTempPtr->gs_isNationalNum="N";

			
			return (ls_tempdestinationnumber);
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
bool PM_FindDestinationRateZone::mb_stop()
{
	return true;
}

/*Fuction to remove the leading n trailing spaces in a string.*/
void PM_FindDestinationRateZone::mb_trim(std::string &p_string)
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


std::string PM_FindDestinationRateZone::remove_whitespace(std::string string) {
  //"""Removes all white space from a string."""
  std::string no_whitespace;

  for (int i = 0; i < string.length(); i++) {
    char c = string[i];
    if (!std::isspace(c)) {
      no_whitespace += c;
    }
  }
  return no_whitespace;
}

