#include "PM_FindPartner.h"
#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "ABL_DateTime.h"
#include "ABL_Date.h"
#include "ABL_DbDate.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_FindPartner()
{
	return ( (Base_Registry*) new PM_FindPartner);
}
}

PM_FindPartner::PM_FindPartner()
{
	//
}

PM_FindPartner::~PM_FindPartner()
{
	//
}

PM_FindPartner::PM_FindPartner(const PM_FindPartner& p_copyObject)
{
	this->mo_ABLServicePtr				= p_copyObject.mo_ABLServicePtr;
	this->mo_IdentifierCachecacheContainer		= p_copyObject.mo_IdentifierCachecacheContainer;
	this->mo_RoamingIdentifierCachecacheContainer	= p_copyObject.mo_RoamingIdentifierCachecacheContainer;
	this->mo_RecordingentityTypecacheContainer	= p_copyObject.mo_RecordingentityTypecacheContainer;

	this->mn_MinTrunkLength				= p_copyObject.mn_MinTrunkLength;
	this->mn_MaxTrunkLength				= p_copyObject.mn_MaxTrunkLength;
	this->ms_Stopsignalfile				= p_copyObject.ms_Stopsignalfile;
	this->mo_IdentifierCachePtr			= (PM_Partners_IdentifierCache*)p_copyObject.mo_IdentifierCachePtr->mb_createCopy();
	this->mo_RoamingIdentifierCachePtr		= (PM_Partners_RoamingIdentifierCache*)p_copyObject.mo_RoamingIdentifierCachePtr->mb_createCopy();
	this->mo_RecordingentityTypeCachePtr		= (PM_FindRecordingentityTypeCache*)p_copyObject.mo_RecordingentityTypeCachePtr->mb_createCopy();
}

Base_Registry* PM_FindPartner::mb_clone()
{
	return ( (Base_Registry*) new PM_FindPartner );
}

ABL_Process* PM_FindPartner::mb_createCopy()
{
	return ( new PM_FindPartner (*this));
}

bool PM_FindPartner::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{	
	try
	{

		mo_ABLServicePtr = p_ABL_ServicePtr;
		p_ABL_AgentCommunicatorPtr->mb_getParameter("STOP_FILE",ms_Stopsignalfile);

		ABL_Connection	l_ABL_Connection;
		ABL_Statement	l_ABL_Statement;
		ABL_ResultSet	l_ABL_ResultSet;
		ABL_String		l_sql;
		//1. Load the all the folders information

		l_ABL_Connection.mb_createConnection(*mo_ABLServicePtr);
		l_sql="select min(length(i.trunk_code)) , max(length(i.trunk_code))  FROM PM_PARTNER_IDENTIFIER I,PM_PARTNER P WHERE I.PARTNER_CODE = P.PARTNER_CODE";
		l_ABL_Statement = l_ABL_Connection.mb_createStatement(l_sql);		
		l_ABL_ResultSet = l_ABL_Statement.mb_executeQuery();
		l_ABL_ResultSet.mb_fetch();	
		mn_MinTrunkLength=l_ABL_ResultSet.mb_getInt64(1);
		mn_MaxTrunkLength=l_ABL_ResultSet.mb_getInt64(2);			
		l_ABL_Statement.mb_closeResultSet(l_ABL_ResultSet);
		l_ABL_Connection.mb_terminateStatement(l_ABL_Statement);
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


bool PM_FindPartner::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	try
	{
		mo_IdentifierCachecacheContainer	=	   p_ABL_CacheManagerPtr->mb_getCache("PM_Partners_IdentifierCache");
		mo_RoamingIdentifierCachecacheContainer =	   p_ABL_CacheManagerPtr->mb_getCache("PM_Partners_RoamingIdentifierCache");
		mo_RecordingentityTypecacheContainer	=	   p_ABL_CacheManagerPtr->mb_getCache("PM_FindRecordingentityTypeCache");
		mo_IdentifierCachePtr=(PM_Partners_IdentifierCache*)mo_ABLServicePtr->mb_getObject("PM_Partners_IdentifierCache")->mb_clone();
		mo_RoamingIdentifierCachePtr=(PM_Partners_RoamingIdentifierCache*)mo_ABLServicePtr->mb_getObject("PM_Partners_RoamingIdentifierCache")->mb_clone();
		mo_RecordingentityTypeCachePtr=(PM_FindRecordingentityTypeCache*)mo_ABLServicePtr->mb_getObject("PM_FindRecordingentityTypeCache")->mb_clone();
	}
	catch(ABL_Exception &e)
	{
		*mo_ABLServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;
		ABL_String ls_command("touch ");
		ls_command +=ms_Stopsignalfile;
		system(ls_command.c_str());  
		return true;
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

bool PM_FindPartner::mb_process(ABL_Job* &p_ABL_JobPtr)
{	

	PM_Job* lo_PMJobPtr = (PM_Job*)p_ABL_JobPtr;
	int ln_MaxLength=0;
	PM_Partners_IdentifierCache		*lo_PMIdentifierCachePtr;
	PM_Partners_RoamingIdentifierCache	*lo_PMRoamingIdentifierCachePtr;
	PM_FindRecordingentityTypeCache		*lo_PMPM_FindRecordingentityTypeCachePtr;
	ABL_String ls_dropCode;
	ABL_String ls_dropValue;
	ABL_String ls_dropMessage;
	ABL_String ls_RejMesg="";		
	ABL_Date ld_TempDate;
	ABL_String ls_Temp,ls_TrunkCode;
	int ln_found=0;		
	int j=0;

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
				*mo_ABLServicePtr << DEBUG <<" No Cdrs for finding the partners for the file: " <<lo_PMJobPtr->gs_fileName<<Endl;	
				return true;          
			}
		}

		*mo_ABLServicePtr << DEBUG<< "Start :" <<lo_PMJobPtr->gs_fileName <<" : "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;

		if (mo_RecordingentityTypecacheContainer->mb_size()==0 )
		{
			rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
			*mo_ABLServicePtr << INFO << " There is no records in PM_RECORDING_ENTITIES rating has stopped. "<<Endl;
			ABL_String ls_command("touch ");
			ls_command +=ms_Stopsignalfile;
			system(ls_command.c_str()); 
			return false;
		}					
		
		/* Loop through rated cdrs. */
		for(int i=0; i < lo_PMJobPtr->ga_RatedCdrs.size(); i++)		
		{
		ls_dropCode="";
		ls_dropValue="";
		ls_dropMessage="";
		

		char limiter[5] = { '/','_',' ' };
		std::string  ls_tokenStringValue="";
		std::string ls_tokenString="";
		std::stringstream l_stringStream(lo_PMJobPtr->ga_RatedCdrs[i].gs_NeCode.c_str());
		std::getline(l_stringStream,ls_tokenString,limiter[0]);
		ls_tokenStringValue=ls_tokenString;
		ls_tokenString="";

		std::stringstream l_stringStream1(ls_tokenStringValue);
		std::getline(l_stringStream1,ls_tokenString,limiter[1]);
		ls_tokenStringValue=ls_tokenString;
		ls_tokenString="";
		std::stringstream l_stringStream2(ls_tokenStringValue);
		std::getline(l_stringStream2,ls_tokenString,limiter[2]);
		lo_PMJobPtr->ga_RatedCdrs[i].gs_NeCode="";
		lo_PMJobPtr->ga_RatedCdrs[i].gs_NeCode=ls_tokenString;
		lo_PMJobPtr->ga_RatingLog[0].gs_NeCode=ls_tokenString;
		
		//Added as per LTE usage for 4.3 release
		//populate recording entity type with either 3 for 005 calls or 7 for 305/300/301/302 calls
		mo_RecordingentityTypeCachePtr->mb_setRecordingEntityDesc(lo_PMJobPtr->ga_RatedCdrs[i].gs_NeCode);					
		if(mo_RecordingentityTypecacheContainer->mb_get((CBase*)mo_RecordingentityTypeCachePtr,(CBase*&)lo_PMPM_FindRecordingentityTypeCachePtr))
		{
			lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordingEntityType	=  lo_PMPM_FindRecordingentityTypeCachePtr->mb_getRecoringEntityType();
			
		}

		if(lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode == "005")
		{
			lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordingEntityType_SGSN = 4; 
			 //populate recording entity type with either 3 for 005 call
			if(lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordingEntityType == 0)
			{
				lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordingEntityType =3;
			}
		}
		
		if(lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode == "305")
                {
                        lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordingEntityType_SGSN = 8;
			//populate recording entity type with 7 for 305 call
                        if(lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordingEntityType == 0)
                        {
                                lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordingEntityType =7;
                        }
                }	
		
		if(lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode == "300" || 
				lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode == "301" || 
				lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode == "302")
		{
			//populate recording entity type SGSN
			lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordingEntityType_SGSN  = 8;

			//populate recording entity PCSCF
			lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordingEntityTypePCSCF  = 9;

                        //populate recording entity type with 7 for 300/301/302 call
                        if(lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordingEntityType == 0)
                        {
                                lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordingEntityType =7;
                        }
		}
		
		//populate network element type1 and type2 for messaging event
		if(lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode == "301")
		{
		if(lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection == "I") //for MT calls
		{
			mo_RecordingentityTypeCachePtr->mb_setRecordingEntityDesc(lo_PMJobPtr->ga_RatedCdrs[i].gs_InRoute);
                	if(mo_RecordingentityTypecacheContainer->mb_get((CBase*)mo_RecordingentityTypeCachePtr,(CBase*&)lo_PMPM_FindRecordingentityTypeCachePtr))
                        {
                        	if(lo_PMPM_FindRecordingentityTypeCachePtr->mb_getRecoringEntityType() == 2)
				{
					lo_PMJobPtr->ga_RatedCdrs[i].gn_NetworkElementType1 = 1;
					lo_PMJobPtr->ga_RatedCdrs[i].gn_NetworkElementType2 = 3;
				}
				if(lo_PMPM_FindRecordingentityTypeCachePtr->mb_getRecoringEntityType()== 81)
                             	{
                                     	lo_PMJobPtr->ga_RatedCdrs[i].gn_NetworkElementType1 = 3;
                                        lo_PMJobPtr->ga_RatedCdrs[i].gn_NetworkElementType2 = 1;
                                }
				if(lo_PMPM_FindRecordingentityTypeCachePtr->mb_getRecoringEntityType() == 82)
                                {
                                     	lo_PMJobPtr->ga_RatedCdrs[i].gn_NetworkElementType1 = 2;
                                        lo_PMJobPtr->ga_RatedCdrs[i].gn_NetworkElementType2 = 2;
                                }
			
                        }
		}
		
                if(lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection == "O") //for MO calls
                {
			mo_RecordingentityTypeCachePtr->mb_setRecordingEntityDesc(lo_PMJobPtr->ga_RatedCdrs[i].gs_OutRoute);
                	if(mo_RecordingentityTypecacheContainer->mb_get((CBase*)mo_RecordingentityTypeCachePtr,(CBase*&)lo_PMPM_FindRecordingentityTypeCachePtr))
                        {
                        	if(lo_PMPM_FindRecordingentityTypeCachePtr->mb_getRecoringEntityType()== 2)
                            	{
                                      	lo_PMJobPtr->ga_RatedCdrs[i].gn_NetworkElementType1 = 3;
                                        lo_PMJobPtr->ga_RatedCdrs[i].gn_NetworkElementType2 = 1;
                                }
                        	if(lo_PMPM_FindRecordingentityTypeCachePtr->mb_getRecoringEntityType()== 81)
                                {
                                      	lo_PMJobPtr->ga_RatedCdrs[i].gn_NetworkElementType1 = 1;
                                        lo_PMJobPtr->ga_RatedCdrs[i].gn_NetworkElementType2 = 3;
                                }
                        	if(lo_PMPM_FindRecordingentityTypeCachePtr->mb_getRecoringEntityType() == 82)
                                {
                                      	lo_PMJobPtr->ga_RatedCdrs[i].gn_NetworkElementType1 = 2;
                                        lo_PMJobPtr->ga_RatedCdrs[i].gn_NetworkElementType2 = 2;
                                }
                        }
		}
		}
		//modification end
		
		//Added Rated  or not rate condition 
		if (lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType == "I" and lo_PMJobPtr->ga_RatedCdrs[i].gs_Rate == "Y" )
			{
				try
				{				
						
					ln_found=0;

					if (mo_IdentifierCachecacheContainer->mb_size()==0 )
					{
						rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
						*mo_ABLServicePtr << INFO << " There is no records in PM_PARTNER_IDENTIFIER  for this Agreement : "  <<lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType<<" So Rating has stopped "<<Endl;
						ABL_String ls_command("touch ");
						ls_command +=ms_Stopsignalfile;
						system(ls_command.c_str()); 
						return false;
					}

					if (lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection =="I")
					{
						lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier= lo_PMJobPtr->ga_RatedCdrs[i].gs_InRoute ;
						ls_RejMesg = "Cannot find the partner code for in route =>  ";
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_InRoute ;
						ls_RejMesg += "     NE =>  ";
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_NeCode ;

						ls_RejMesg += "     Transfer type =>  ";
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection ;

						ls_RejMesg += "     Call Date =>  ";						
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();
					}
					else
					{
						lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier= lo_PMJobPtr->ga_RatedCdrs[i].gs_OutRoute ;
						ls_RejMesg = "Cannot find the partner code for out route =>  ";
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_OutRoute ;
						ls_RejMesg += "     NE =>  ";
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_NeCode ;	
						ls_RejMesg += "     Transfer type =>  ";
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection ;						
						ls_RejMesg += "     Call Date =>  ";
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();					
					}	
				
					ln_MaxLength=0;
					ln_MaxLength = lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier.mb_length();
					if (mn_MaxTrunkLength<ln_MaxLength)
					{
							ln_MaxLength=mn_MaxTrunkLength;
					}

		
					for(j=ln_MaxLength;j>=mn_MinTrunkLength;j--)
					{
						ls_TrunkCode="";
						ls_TrunkCode=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier.mb_subStr(0,j);


						mo_IdentifierCachePtr->mb_setAgreementType(lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType);				
						mo_IdentifierCachePtr->mb_setTransferType(lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection);		
						mo_IdentifierCachePtr->mb_setTrunkCode(ls_TrunkCode);			
						mo_IdentifierCachePtr->mb_setNeCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_NeCode);			
						mo_IdentifierCachePtr->mb_setValid_From(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
						mo_IdentifierCachePtr->mb_setValid_To(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);		
						if(mo_IdentifierCachecacheContainer->mb_get((CBase*)mo_IdentifierCachePtr,(CBase*&)lo_PMIdentifierCachePtr))
						{
							lo_PMJobPtr->ga_RatedCdrs[i].gs_AppOwner = lo_PMIdentifierCachePtr->mb_getAppOwner();
							lo_PMJobPtr->ga_RatedCdrs[i].gs_AllowIcTraffic	= lo_PMIdentifierCachePtr->mb_getAllowIcTraffic();	
							lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier = lo_PMIdentifierCachePtr->mb_getTrunkCode();
							lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode	=	lo_PMIdentifierCachePtr->mb_getPartnerCode();
							lo_PMJobPtr->ga_RatedCdrs[i].gs_Poi		=	lo_PMIdentifierCachePtr->mb_getPOICode();
							lo_PMJobPtr->ga_RatedCdrs[i].gs_tobe_rated	=	lo_PMIdentifierCachePtr->mb_getTobeRated();							  
							ln_found=1;
							break;
						}
					}
					if (ln_found == 0)
					{
						throw   ABL_Exception(1,ls_RejMesg.c_str());
					}
					else
					{
					/*	if(lo_PMJobPtr->ga_RatedCdrs[i].gs_tobe_rated=="N")
						{
							ls_dropCode="DROP-005";
							ls_dropMessage= "To be Rated configured as N for the Partner Code: ";
							ls_dropMessage+= lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
							ls_dropValue = lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
							throw   ABL_Exception(2,ls_dropMessage.c_str());
						}
                                        */
						if(lo_PMJobPtr->ga_RatedCdrs[i].gs_AppOwner=="Y" && lo_PMJobPtr->ga_RatedCdrs[i].gs_AllowIcTraffic == "Y")
						{
							ls_RejMesg="";
							if(lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection == "I")
							{
								//Below if condition added by harish to take MNP into consideration 
								if (!lo_PMJobPtr->ga_RatedCdrs[i].gs_Mnp.mb_empty())
									{    
									    lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier=lo_PMJobPtr->ga_RatedCdrs[i].gs_Mnp+lo_PMJobPtr->ga_RatedCdrs[i].gs_ANumber;
								    }
                                else
									{
										lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier = lo_PMJobPtr->ga_RatedCdrs[i].gs_ANumber;
									}
								
							//	lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier = lo_PMJobPtr->ga_RatedCdrs[i].gs_ANumber;
								ls_RejMesg = "Cannot find the partner code for in route =>";
								ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_ANumber ;
								ls_RejMesg += "     NE =>  ";
								ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_NeCode ;
								ls_RejMesg += "     Call Date =>  ";
								ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();					
							}
							else
							{
								//Below if condition added by harish to take MNP into consideration 
								if (!lo_PMJobPtr->ga_RatedCdrs[i].gs_Mnp.mb_empty())
                                    {
										lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier=lo_PMJobPtr->ga_RatedCdrs[i].gs_Mnp+lo_PMJobPtr->ga_RatedCdrs[i].gs_BNumber;								                 
			                        } 
								else
									{
										lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier = lo_PMJobPtr->ga_RatedCdrs[i].gs_BNumber;
									}
									
								//lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier = lo_PMJobPtr->ga_RatedCdrs[i].gs_BNumber;
								ls_RejMesg = "Cannot find the partner code for out route =>  ";
								ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_BNumber ;
								ls_RejMesg += "     NE =>  ";
								ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_NeCode ;			
								ls_RejMesg += "     Call Date =>  ";
								ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();					
							}

							ln_MaxLength=0;
							ln_MaxLength = lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier.mb_length();
							if (mn_MaxTrunkLength<ln_MaxLength)
							{
									ln_MaxLength=mn_MaxTrunkLength;
							}
							ln_found=0;
							for(j=ln_MaxLength;j>=mn_MinTrunkLength;j--)
							{
								ls_TrunkCode="";
								ls_TrunkCode=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier.mb_subStr(0,j);
								mo_IdentifierCachePtr->mb_setAgreementType(lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType);
								mo_IdentifierCachePtr->mb_setTransferType(lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection);		
								mo_IdentifierCachePtr->mb_setTrunkCode(ls_TrunkCode);			
								mo_IdentifierCachePtr->mb_setNeCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_NeCode);			
								mo_IdentifierCachePtr->mb_setValid_From(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
								mo_IdentifierCachePtr->mb_setValid_To(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
							    lo_PMIdentifierCachePtr=NULL;
								if(mo_IdentifierCachecacheContainer->mb_get((CBase*)mo_IdentifierCachePtr,(CBase*&)lo_PMIdentifierCachePtr))
								{
								ln_found=1;
								lo_PMJobPtr->ga_RatedCdrs[i].gs_AppOwner					="";
								lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier=lo_PMIdentifierCachePtr->mb_getTrunkCode();
								lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode = lo_PMIdentifierCachePtr->mb_getPartnerCode();
								lo_PMJobPtr->ga_RatedCdrs[i].gs_Poi = lo_PMIdentifierCachePtr->mb_getPOICode();
								lo_PMJobPtr->ga_RatedCdrs[i].gs_tobe_rated=lo_PMIdentifierCachePtr->mb_getTobeRated();
						/*		if(lo_PMIdentifierCachePtr->mb_getTobeRated()=="N")
									{
										ls_dropCode="DROP-006";
										ls_dropMessage= "To be Rated configured as N for the Partner Code: ";
										ls_dropMessage+= lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
										ls_dropValue = lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
										throw   ABL_Exception(2,ls_dropMessage.c_str());
									}
                                                 */
									break;
								}
						  	}

						   if (ln_found == 0)
							{
								throw   ABL_Exception(1,ls_RejMesg.c_str());
							}


						}//End App owner trunk
						//Drop the cdr after analysing the right owner of the Call based on TRUNK or A/B-Number 
                                               if(lo_PMJobPtr->ga_RatedCdrs[i].gs_tobe_rated=="N")
                                                {
                                                        ls_dropCode="DROP-005";
                                                        ls_dropMessage= "To be Rated configured as N for the Partner Code: ";
                                                        ls_dropMessage+= lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
                                                        ls_dropValue = lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
                                                        throw   ABL_Exception(2,ls_dropMessage.c_str());
                                               }

					}//End Trunk Found											
				}//End Try			
				catch(ABL_Exception &e)
				{
			  
				// Populate rejection details.
					if(e.mb_getErrorCode() == 2)
					{
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode=ls_dropCode;
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage=ls_dropMessage; 
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=ls_dropValue;
						lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="D";
						continue;
					}
					else if(e.mb_getErrorCode() == 1)
					{
						// Populate rejection details.	
						if (lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection == "I")
						{
							 //lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode = "INCTRUNK-NF"; commented as per LTE usage 4.3 release
							 lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode   = "RATE-PARTNER-NF";
							 lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=lo_PMJobPtr->ga_RatedCdrs[i].gs_InRoute;
						}
						else if (lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection == "O")
						{
						//lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode= "OUTTRUNK-NF"; commented as per LTE usage for 4.3 release 
							 lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode   = "RATE-PARTNER-NF";
							 lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=lo_PMJobPtr->ga_RatedCdrs[i].gs_OutRoute;
						} 						   
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage=ls_RejMesg; 
						lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="R";
						continue;
					}
					else
					{
						if (lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection == "I")
						{
						//lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode   = "INCTRUNK-NF"; commented as per LTE usage for 4.3 release
							lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode   = "RATE-PARTNER-NF";
							lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=lo_PMJobPtr->ga_RatedCdrs[i].gs_InRoute;
						}
						else if (lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection == "O")
						{
						//lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode   = "OUTTRUNK-NF"; commented as per LTE usage for 4.3 release
							lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode   = "RATE-PARTNER-NF";
							lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=lo_PMJobPtr->ga_RatedCdrs[i].gs_OutRoute;
						} 						   
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage=ls_RejMesg; 
						lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="R";
						continue;
					}							
				}//End Catch
			}//End Agreement Type "I"
			
			else if ( lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType == "R" and lo_PMJobPtr->ga_RatedCdrs[i].gs_Rate=="Y")
			{			
				try
				{


					if (mo_RoamingIdentifierCachecacheContainer->mb_size()==0 )
					{
						rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
						*mo_ABLServicePtr << INFO << " There is no records in PM_PARTNER_IDENTIFIER  for this Agreement : "  <<lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType<<" So Rating has stopped "<<Endl;
						ABL_String ls_command("touch ");
						ls_command +=ms_Stopsignalfile;
						system(ls_command.c_str()); 
						return false;
					}

					ln_found=0;
					ls_RejMesg ="Cannot find partner for identifier =>";
					ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier;
					ls_RejMesg+=" Agreement Type => ";
					ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType;
					ls_RejMesg+=" Call Direction => ";
					ls_RejMesg+=lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection;
					ls_RejMesg+=" Call Date => ";
					ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();
					ln_MaxLength=0;

			
					ln_MaxLength =lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier.mb_length();
					if (mn_MaxTrunkLength<ln_MaxLength)
					{
							ln_MaxLength=mn_MaxTrunkLength;
					}

					ln_found=0;
					for(j=ln_MaxLength;j>=mn_MinTrunkLength;j--)
					{
						ls_TrunkCode="";
						ls_TrunkCode=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier.mb_subStr(0,j);										     mo_RoamingIdentifierCachePtr->mb_setTransferType(lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection);
						mo_RoamingIdentifierCachePtr->mb_setTrunkCode(ls_TrunkCode);	
						mo_RoamingIdentifierCachePtr->mb_setValid_From(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
						mo_RoamingIdentifierCachePtr->mb_setValid_To(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
						if(mo_RoamingIdentifierCachecacheContainer->mb_get((CBase*)mo_RoamingIdentifierCachePtr,(CBase*&)lo_PMRoamingIdentifierCachePtr))
						{
							ln_found=1;
							lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier=lo_PMRoamingIdentifierCachePtr->mb_getTrunkCode();
							lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode = lo_PMRoamingIdentifierCachePtr->mb_getPartnerCode();
							lo_PMJobPtr->ga_RatedCdrs[i].gs_Poi	=	lo_PMRoamingIdentifierCachePtr->mb_getPOICode();
							break;
						}
					}
					if(ln_found==1)
					{
						if(lo_PMRoamingIdentifierCachePtr->mb_getTobeRated()=="N")
						{
							ls_dropCode="DROP-007";
							ls_dropMessage= "To be Rated configured as N for the Partner Code: ";
							ls_dropMessage+= lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
							ls_dropValue = lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
							throw   ABL_Exception(2,ls_dropMessage.c_str());
						}							
					}
					else
					{
						throw  ABL_Exception(1,ls_RejMesg.c_str());
					}
			    }
			    catch(ABL_Exception &e)
			    {
				// Populate rejection details.
					if(e.mb_getErrorCode() == 2)
					{
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode=ls_dropCode;
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage=ls_dropMessage; 
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=ls_dropValue;
						lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="D";
						continue;
					}
					else if(e.mb_getErrorCode() == 1)
					{
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode   = "RATE-PARTNER-NF";						 						
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage=ls_RejMesg; 
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier;
						lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="R";						
						 continue;
					}
					else
					{
						
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode   = "RATE-PARTNER-NF";						
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage=ls_RejMesg; 
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier;
						lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="R";

						 continue;
					}
				}//End Catch
			}//End Agreement Type R

else if (lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType == "V" and lo_PMJobPtr->ga_RatedCdrs[i].gs_Rate == "Y" )
			{
				try
				{				
						
					ln_found=0;

					if (mo_IdentifierCachecacheContainer->mb_size()==0 )
					{
						rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
						*mo_ABLServicePtr << INFO << " There is no records in PM_PARTNER_IDENTIFIER  for this Agreement : "  <<lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType<<" So Rating has stopped "<<Endl;
						ABL_String ls_command("touch ");
						ls_command +=ms_Stopsignalfile;
						system(ls_command.c_str()); 
						return false;
					}

					if (lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection =="I")
					{
						lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier= lo_PMJobPtr->ga_RatedCdrs[i].gs_ANumber ;
						ls_RejMesg = "Cannot find the partner code for in route =>  ";
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_ANumber ;
						ls_RejMesg += "     NE =>  ";
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_NeCode ;

						ls_RejMesg += "     Transfer type =>  ";
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection ;

						ls_RejMesg += "     Call Date =>  ";						
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();
					}
					else
					{
						lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier= lo_PMJobPtr->ga_RatedCdrs[i].gs_BNumber ;
						ls_RejMesg = "Cannot find the partner code for out route =>  ";
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_BNumber ;
						ls_RejMesg += "     NE =>  ";
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_NeCode ;	
						ls_RejMesg += "     Transfer type =>  ";
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection ;						
						ls_RejMesg += "     Call Date =>  ";
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();					
					}	
				
							
						ls_TrunkCode="";
						ls_TrunkCode=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier;

						mo_IdentifierCachePtr->mb_setAgreementType(lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType);				
						mo_IdentifierCachePtr->mb_setTransferType(lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection);		
						mo_IdentifierCachePtr->mb_setTrunkCode(ls_TrunkCode);			
						mo_IdentifierCachePtr->mb_setNeCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_NeCode);			
						mo_IdentifierCachePtr->mb_setValid_From(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
						mo_IdentifierCachePtr->mb_setValid_To(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);		
						if(mo_IdentifierCachecacheContainer->mb_get((CBase*)mo_IdentifierCachePtr,(CBase*&)lo_PMIdentifierCachePtr))
						{
							lo_PMJobPtr->ga_RatedCdrs[i].gs_AppOwner = lo_PMIdentifierCachePtr->mb_getAppOwner();
							lo_PMJobPtr->ga_RatedCdrs[i].gs_AllowIcTraffic	= lo_PMIdentifierCachePtr->mb_getAllowIcTraffic();			
							lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier = lo_PMIdentifierCachePtr->mb_getTrunkCode();
							lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode	=	lo_PMIdentifierCachePtr->mb_getPartnerCode();
							lo_PMJobPtr->ga_RatedCdrs[i].gs_Poi		=	lo_PMIdentifierCachePtr->mb_getPOICode();
							lo_PMJobPtr->ga_RatedCdrs[i].gs_tobe_rated	=	lo_PMIdentifierCachePtr->mb_getTobeRated();		
							ln_found=1;
						}
					
					if (ln_found == 0)
					{
						    ls_dropCode="DROP-009";
							ls_dropMessage= "To be Rated configured as N for the Content Code: ";
							ls_dropMessage+= ls_TrunkCode;
							ls_dropValue = ls_TrunkCode;
							throw   ABL_Exception(2,ls_dropMessage.c_str());
					}
				}//End Try			
				catch(ABL_Exception &e)
				{
			  
				// Populate rejection details.
					if(e.mb_getErrorCode() == 2)
					{
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode=ls_dropCode;
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage=ls_dropMessage; 
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=ls_dropValue;
						lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="D";
						continue;
					}
					else if(e.mb_getErrorCode() == 1)
					{
						// Populate rejection details.	
						if (lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection == "I")
						{
							 //lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode = "INCTRUNK-NF"; commented as per LTE usage 4.3 release
							 lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode   = "RATE-PARTNER-NF";
							 lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=lo_PMJobPtr->ga_RatedCdrs[i].gs_InRoute;
						}
						else if (lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection == "O")
						{
						//lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode= "OUTTRUNK-NF"; commented as per LTE usage for 4.3 release 
							 lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode   = "RATE-PARTNER-NF";
							 lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=lo_PMJobPtr->ga_RatedCdrs[i].gs_OutRoute;
						} 						   
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage=ls_RejMesg; 
						lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="R";
						continue;
					}
					else
					{
						if (lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection == "I")
						{
						//lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode   = "INCTRUNK-NF"; commented as per LTE usage for 4.3 release
							lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode   = "RATE-PARTNER-NF";
							lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=lo_PMJobPtr->ga_RatedCdrs[i].gs_InRoute;
						}
						else if (lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection == "O")
						{
						//lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode   = "OUTTRUNK-NF"; commented as per LTE usage for 4.3 release
							lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode   = "RATE-PARTNER-NF";
							lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=lo_PMJobPtr->ga_RatedCdrs[i].gs_OutRoute;
						} 						   
						lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage=ls_RejMesg; 
						lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="R";
						continue;
					}							
				}//End Catch
			}//End Agreement Type "V"
		
                      if(lo_PMJobPtr->ga_RatedCdrs[i].gs_tobe_rated=="N")
						{
							ls_dropCode="DROP-005";
							ls_dropMessage= "To be Rated configured as N for the Partner Code: ";
							ls_dropMessage+= lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
							ls_dropValue = lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
							throw   ABL_Exception(2,ls_dropMessage.c_str());
						} 

		}//End Loop

		*mo_ABLServicePtr <<DEBUG<<"End  :" << lo_PMJobPtr->gs_fileName <<": "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;
	}
	catch(ABL_Exception &e)
	{
		rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
		*mo_ABLServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() <<Endl;
		ABL_String ls_command("touch ");
		ls_command +=ms_Stopsignalfile;
		system(ls_command.c_str());  
		return false;
	}	
	    return true;		
}

bool PM_FindPartner::mb_stop()
{
	return true;
}
