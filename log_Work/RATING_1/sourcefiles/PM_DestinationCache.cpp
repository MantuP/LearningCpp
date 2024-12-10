#include "PM_DestinationCache.h"
#include "ABL_Service.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "CHashTable.h"
#include "ABL_Exception.h"
#include "ABL_String.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_DestinationCache()
{
	return ( (Base_Registry*) new PM_DestinationCache);
}
}

bool PM_DestinationCache:: mb_isEqual(CBase* p_CBase_ptr)
{

	if(((PM_DestinationCache*)p_CBase_ptr)->ms_Destination == ms_Destination  && ((PM_DestinationCache*)p_CBase_ptr)->ms_NumberPlanCode == ms_NumberPlanCode  && ((PM_DestinationCache*)p_CBase_ptr)->ms_DestinationType == ms_DestinationType &&  (((PM_DestinationCache*)p_CBase_ptr)->md_Valid_From <= md_Valid_From)  && (((PM_DestinationCache*)p_CBase_ptr)->md_Valid_To >= md_Valid_To))
	{
			return true;
	}
	else
	{
		return false;
	}

}


PM_DestinationCache::PM_DestinationCache(const PM_DestinationCache& p_copyObject)
{
	
	
	this->ms_Destination				=	p_copyObject.ms_Destination;
	this->ms_DestinationType			=	p_copyObject.ms_DestinationType;
	this->ms_RateZone					=	p_copyObject.ms_RateZone;
	this->ms_NumberPlanCode				=	p_copyObject.ms_NumberPlanCode;
	this->ms_DestinationSubType			=	p_copyObject.ms_DestinationSubType;
	this->ms_Poi						=	p_copyObject.ms_Poi;
	this->md_Valid_From					=	p_copyObject.md_Valid_From;
	this->md_Valid_To					=	p_copyObject.md_Valid_To;	
	this->ms_Calltypelevel3				=	p_copyObject.ms_Calltypelevel3 ;
	//Added as per LTE usage for 4.3 release
	this->ms_TrafficType				=	p_copyObject.ms_TrafficType;
	//modification end

}

CBase* PM_DestinationCache::mb_createCopy()
{
	return ((CBase*)new PM_DestinationCache(*this));
}

unsigned int PM_DestinationCache::mb_hash()
{ 
	return(ms_NumberPlanCode.mb_hash() * 10+ ms_DestinationType.mb_hash() * 20 +ms_Destination.mb_hash() * 30);

}

bool PM_DestinationCache::mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause)
{
	ABL_Service *lo_ABLServicePtr = p_ABL_Service_ptr;
	ABL_Connection	lo_ABLConnection;
	ABL_Statement	lo_ABLStatement;
	ABL_ResultSet	lo_ABLResultSet;

	ABL_DbDate	la_Valid_From[500];
	ABL_DbDate	la_Valid_To[500];
	ABL_String la_Destination[500];
	ABL_String la_DestinationType[500];
	ABL_String la_RateZone[500];
	ABL_String la_NumberPlanCode[500];
	ABL_String la_DestinationSubType[500];
	//added as per LTE usage for 4.3 release
	ABL_String la_POI[500];
	//modification end
	ABL_String	la_Calltypelevel3[500];
	
	//added as per LTE usage for 4.3 release
	ABL_String la_TrafficType[500];
	//modification end
	*lo_ABLServicePtr<<DEBUG<<"Start PM_DestinationCache Loading"<<Endl;
	ABL_String		ls_ErrorMessage="";
	try
	{

		lo_ABLConnection.mb_createConnection(*p_ABL_Service_ptr);

		ABL_String	ls_query;

		ls_query="SELECT count(*) FROM PM_DESTINATION ";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_fetch();
		p_container->mb_resize(lo_ABLResultSet.mb_getInt64(1));	
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);		
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);

		//added TRAFFIC_TYPE to select statement for LTE 4.3 release
		ls_query ="SELECT VALID_FROM , VALID_TO ,NVL(DESTINATION, ' '),NVL(DESTINATION_TYPE,' '),NVL(NUMBER_PLAN_CODE, ' '),NVL(RATE_ZONE, ' '),NVL(DESTINATION_SUB_TYPE, ' '),NVL(POI, ' '),NVL(call_type_level3,' '),NVL(TRAFFIC_TYPE,' ') ";
		ls_query +="FROM PM_DESTINATION ORDER BY DESTINATION,DESTINATION_TYPE,NUMBER_PLAN_CODE"; 
		//modification end
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_setBulkCount(500);

		lo_ABLResultSet	<< la_Valid_From;
		lo_ABLResultSet	<< la_Valid_To;		
		lo_ABLResultSet	<< la_Destination;
		lo_ABLResultSet	<< la_DestinationType;
		lo_ABLResultSet	<< la_NumberPlanCode;
		lo_ABLResultSet	<< la_RateZone;		
		lo_ABLResultSet	<< la_DestinationSubType;
		//added as per LTE usage for 4.3 release
		lo_ABLResultSet << la_POI;
		//modification end
		lo_ABLResultSet	<< la_Calltypelevel3;
		//added as per LTE usage for 4.3 release
		lo_ABLResultSet << la_TrafficType;
		//modification end

		while(lo_ABLResultSet.mb_fetch())
		{
			int records = lo_ABLResultSet.mb_getNumArrayRows();
			for(int i = 0; i < records ; i++)
			{
				ls_ErrorMessage="";
				ls_ErrorMessage= "Error came while inserting the following data  in the cache : Destination=>";
				ls_ErrorMessage+=la_Destination[i];
				ls_ErrorMessage+=",Number Plan=>";
				ls_ErrorMessage+=la_NumberPlanCode[i];
				ls_ErrorMessage+=",Destination type=>";
				ls_ErrorMessage+=la_DestinationType[i];
				ls_ErrorMessage+=",Valid from date=>";
				ls_ErrorMessage+=la_Valid_From[i].mb_toString();
				ls_ErrorMessage+=",Valid to date=>";
				ls_ErrorMessage+=la_Valid_To[i].mb_toString();		
					
				//added la_TrafficType to mb_insert for LTE 4.3 release	
				p_container->mb_insert((CBase*) new PM_DestinationCache(la_Valid_From[i],la_Valid_To[i],la_Destination[i],la_DestinationType[i],la_NumberPlanCode[i],la_RateZone[i],la_DestinationSubType[i],la_POI[i],la_Calltypelevel3[i],la_TrafficType[i]));
				//modification end
				
			}
		}
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);		
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);
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
	*lo_ABLServicePtr<<DEBUG<<"PM_DestinationCache Loaded Successfully"<<Endl;
	return true;
}
