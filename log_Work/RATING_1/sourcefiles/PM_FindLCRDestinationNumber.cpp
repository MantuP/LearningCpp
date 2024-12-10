#include "PM_FindLCRDestinationNumber.h"
#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "ABL_DateTime.h"
#include "ABL_Date.h"
#include "ABL_DbDate.h"
extern "C" {EXPORT 
Base_Registry* gb_getPM_FindLCRDestinationNumber()
{
	return ( (Base_Registry*) new PM_FindLCRDestinationNumber);
}
}

PM_FindLCRDestinationNumber::PM_FindLCRDestinationNumber()
{
	//
}

PM_FindLCRDestinationNumber::~PM_FindLCRDestinationNumber()
{
	//
}

PM_FindLCRDestinationNumber::PM_FindLCRDestinationNumber(const PM_FindLCRDestinationNumber& p_copyObject)
{
	this->mo_ABLServicePtr						=	p_copyObject.mo_ABLServicePtr;
	this->mo_LCRDestinationCachePtr				=	(PM_FindLCRDestinationCache*)p_copyObject.mo_LCRDestinationCachePtr->mb_createCopy();
	this->mo_LCRDestinationCachecacheContainer	=	p_copyObject.mo_LCRDestinationCachecacheContainer;	
	this->mn_MinLength							=	p_copyObject.mn_MinLength;
	this->mn_MaxLength							=	p_copyObject.mn_MaxLength;
	this->ms_Stopsignalfile						=	p_copyObject.ms_Stopsignalfile;
}

Base_Registry* PM_FindLCRDestinationNumber::mb_clone()
{
	return ( (Base_Registry*) new PM_FindLCRDestinationNumber );
}

ABL_Process* PM_FindLCRDestinationNumber::mb_createCopy()
{
	return ( new PM_FindLCRDestinationNumber (*this));
}

bool PM_FindLCRDestinationNumber::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
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
			ls_sql="SELECT NVL(MIN (LENGTH (lcr_destination)),0), NVL(MAX (LENGTH (lcr_destination)),0)  FROM PM_LCR_DESTINATIONS";
			lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_sql);		
			lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
			lo_ABLResultSet.mb_fetch();
			mn_MinLength	=lo_ABLResultSet.mb_getInt64(1);
			mn_MaxLength	=lo_ABLResultSet.mb_getInt64(2);		
			lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
			lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);
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

bool PM_FindLCRDestinationNumber::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	try
	{

		this->mo_LCRDestinationCachecacheContainer		=	p_ABL_CacheManagerPtr->mb_getCache("PM_FindLCRDestinationCache");
		this->mo_LCRDestinationCachePtr			=	(PM_FindLCRDestinationCache*)mo_ABLServicePtr->mb_getObject("PM_FindLCRDestinationCache")->mb_clone();
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

bool PM_FindLCRDestinationNumber::mb_process(ABL_Job* &p_ABL_JobPtr)
{	
	PM_Job* lo_PMJobPtr	=(PM_Job*)p_ABL_JobPtr;
	int	ln_MaxLength;
	PM_FindLCRDestinationCache*		lo_PM_LCRDestinationCachePtr;
	ABL_String ls_NumberPrefix;
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
				*mo_ABLServicePtr << DEBUG <<"  No Cdrs for finding the LCR Destination for the file: " <<lo_PMJobPtr->gs_fileName<<Endl;	
				return true;          
			}
		}

		*mo_ABLServicePtr << DEBUG << "Start :" <<lo_PMJobPtr->gs_fileName <<" : "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;
		if (mo_LCRDestinationCachecacheContainer->mb_size()==0)
		{
			return true;
		}


		for (int i=0;i<lo_PMJobPtr->ga_RatedCdrs.size();i++)
		{	
			if(lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus=="D" || lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus=="R")
			{
				continue;
			}

			
			if( (strcmp(lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType.c_str(),"I")!=0) && (strcmp(lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType.c_str(),"R")!=0) )
			{
				continue;
			}

             ls_NumberPrefix = "";

                for (int l=0; l<2;l++)
                  {


			 if(l==0)
			{
                                ls_NumberPrefix = lo_PMJobPtr->ga_RatedCdrs[i].gs_ANumber;
				
			}
			else
			{
				ls_NumberPrefix = lo_PMJobPtr->ga_RatedCdrs[i].gs_BNumber;
			}

			ln_MaxLength= ls_NumberPrefix.mb_length();
				if(mn_MaxLength<ln_MaxLength)
				{
					ln_MaxLength=mn_MaxLength;
				}


				

				for(int j=ln_MaxLength;j>=mn_MinLength;j--)
				{
					mo_LCRDestinationCachePtr->mb_setLCRDestination(ls_NumberPrefix.mb_subStr(0,j));
					if(mo_LCRDestinationCachecacheContainer->mb_get((CBase*)mo_LCRDestinationCachePtr,(CBase*&)lo_PM_LCRDestinationCachePtr))
					{
                                               if (l==0)
                                                {
                                                lo_PMJobPtr->ga_RatedCdrs[i].gs_LcrOrigin=lo_PM_LCRDestinationCachePtr->mb_getLCRDestination();
                                                }
                                               else
                                                {
						lo_PMJobPtr->ga_RatedCdrs[i].gs_LcrDestination=lo_PM_LCRDestinationCachePtr->mb_getLCRDestination();
                                                }
						break;
							
					}
				}
                      }
		}

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

	*mo_ABLServicePtr<<DEBUG<<"End  :"<<lo_PMJobPtr->gs_fileName <<": "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;
	return true;
}
bool PM_FindLCRDestinationNumber::mb_stop()
{
	return true;
}

