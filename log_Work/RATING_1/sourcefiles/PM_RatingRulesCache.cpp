#include "PM_RatingRulesCache.h"
#include "ABL_Service.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "CHashTable.h"
#include "ABL_Exception.h"
#include "ABL_Date.h"
//added as per LTE
//#include <stdlib.h>
//#include <string.h>
//#include <stdio.h>
//modification end

extern "C" {EXPORT 
Base_Registry* gb_getPM_RatingRulesCache()
{
	return ( (Base_Registry*) new PM_RatingRulesCache);}
}

bool PM_RatingRulesCache::mb_isEqual(CBase* p_CBase_ptr)
{ 
	if( ms_AgreementType  == ((PM_RatingRulesCache*)p_CBase_ptr)->ms_AgreementType &&  ms_ServiceCode == ((PM_RatingRulesCache*)p_CBase_ptr)->ms_ServiceCode && ms_SubscriberType == ((PM_RatingRulesCache*)p_CBase_ptr)->ms_SubscriberType && mn_CallType == ((PM_RatingRulesCache*)p_CBase_ptr)->mn_CallType)
//added as per LTE
/*char stCallType[2];
char stCallType1[2];
itoa(this->mn_CallType,stCallType,10);
itoa(((PM_RatingRulesCache*)p_CBase_ptr)->mn_CallType, stCallType1, 10);
if( ms_AgreementType  == ((PM_RatingRulesCache*)p_CBase_ptr)->ms_AgreementType &&  ms_ServiceCode == ((PM_RatingRulesCache*)p_CBase_ptr)->ms_ServiceCode && ms_SubscriberType == ((PM_RatingRulesCache*)p_CBase_ptr)->ms_SubscriberType && (strcmp(stCallType,stCallType1)==0))
//modification end.*/
	{
		return true;
	}
	else
	{
		return false;
	}
}
	
PM_RatingRulesCache::PM_RatingRulesCache(const PM_RatingRulesCache& p_copyObject)
{
	this->ms_AgreementType		=	p_copyObject.ms_AgreementType;
	this->ms_ServiceCode		=	p_copyObject.ms_ServiceCode;
	this->ms_SubscriberType		=	p_copyObject.ms_SubscriberType;
	this->mn_CallType			=	p_copyObject.mn_CallType;
	this->ms_ConsiderIncLeg		=	p_copyObject.ms_ConsiderIncLeg;
	this->ms_IncLegAction		=	p_copyObject.ms_IncLegAction;
	this->ms_ConsiderOutLeg		=	p_copyObject.ms_ConsiderOutLeg;
	this->ms_OutLegAction		=	p_copyObject.ms_OutLegAction;
	this->ms_PartialSearch		=	p_copyObject.ms_PartialSearch;

}

unsigned int PM_RatingRulesCache::mb_hash()
{
	return (ms_AgreementType.mb_hash()*10+ms_ServiceCode.mb_hash()*20+ms_SubscriberType.mb_hash()*30); 
}

CBase* PM_RatingRulesCache::mb_createCopy()
{
	 return ((CBase*)new PM_RatingRulesCache(*this));
}

bool PM_RatingRulesCache::mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause)
{
 
  ABL_Service *lo_ABLServicePtr = p_ABL_Service_ptr;
	*lo_ABLServicePtr<<DEBUG<<"Rating Rules Cache Loading."<<Endl;
  
  ABL_String		ls_query;

  ABL_Statement		lo_ABLStatement;
  ABL_Connection	lo_ABLConnection;
  ABL_ResultSet		lo_ABLResultSet;

  ABL_String		la_AgreementType[10];
  ABL_String		la_ServiceCode[10];
  ABL_String		la_SubscriberType[10];
  int				la_CallType[10];
  ABL_String		la_ConsiderIncLeg[10];
  ABL_String		la_IncLegAction[10];
  ABL_String		la_ConsiderOutLeg[10];
  ABL_String		la_OutLegAction[10];
  ABL_String		ls_ErrorMessage="";
  ABL_String		ls_Tempmessage	="";
  ABL_String            la_PartialSearch[10];
  int                   la_count;

  
  try
  {
		lo_ABLConnection.mb_createConnection(*p_ABL_Service_ptr);

		ls_query="SELECT COUNT(*) as TotalCount  FROM PM_RATING_RULES ";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_fetch();
		p_container->mb_resize(lo_ABLResultSet.mb_getInt64(1));
                la_count = lo_ABLResultSet.mb_getInt64(1);
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);

        ls_query = "SELECT    NVL (AGREEMENT_TYPE, ' '),NVL (SERVICE_CODE, ' '),NVL (SUBSCRIBER_TYPE, ' '),NVL (CALL_TYPE, 0),NVL (CONSIDER_INC_LEG, 'Y'),NVL (INC_LEG_ACTION, ' '),NVL (CONSIDER_OUT_LEG, 'Y'),NVL (OUT_LEG_ACTION, ' '),NVL(IDENTIFIER_PARTIAL_SEARCH,'N') ";
		ls_query+="FROM PM_RATING_RULES ";	
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();	
		lo_ABLResultSet.mb_setBulkCount(10);		
		lo_ABLResultSet	<<la_AgreementType;
		lo_ABLResultSet	<<la_ServiceCode;
		lo_ABLResultSet	<<la_SubscriberType;
		lo_ABLResultSet	<<la_CallType;
		lo_ABLResultSet	<<la_ConsiderIncLeg;
		lo_ABLResultSet	<<la_IncLegAction;
		lo_ABLResultSet	<<la_ConsiderOutLeg;
		lo_ABLResultSet	<<la_OutLegAction;
	    lo_ABLResultSet	<<la_PartialSearch;
		while(lo_ABLResultSet.mb_fetch())
		{
			int records = lo_ABLResultSet.mb_getNumArrayRows();
			for(int i = 0; i < records ; i++)
			{
				ls_ErrorMessage="";
				ls_Tempmessage	="";
				ls_ErrorMessage= "Error came while inserting the following data  in the cache : AgreementType=>";
				ls_ErrorMessage+=la_AgreementType[i];
				ls_ErrorMessage+=",Service Code=>";
				ls_ErrorMessage+=la_ServiceCode[i];
				ls_ErrorMessage+=",Subscriber type=>";
				ls_ErrorMessage+=la_SubscriberType[i];
				ls_ErrorMessage+=",Call TYpe=>";
				ls_Tempmessage.mb_fromInt(la_CallType[i]);
				ls_ErrorMessage+=ls_Tempmessage;
				p_container->mb_insert((CBase*) new PM_RatingRulesCache(la_AgreementType[i],la_ServiceCode[i],la_SubscriberType[i], la_CallType[i], la_ConsiderIncLeg[i],la_IncLegAction[i],la_ConsiderOutLeg[i],la_OutLegAction[i],la_PartialSearch[i]));
			}			
		}
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);
                 *lo_ABLServicePtr<<DEBUG<<"Rating Rules Cache Loaded successfully."<<la_count<<Endl;
	}
	catch(ABL_Exception &e)
	{
		*lo_ABLServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<" : "<<ls_ErrorMessage<<Endl;
		return false;
	}
	catch(...)
	{
		*lo_ABLServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}
	return true;
}
