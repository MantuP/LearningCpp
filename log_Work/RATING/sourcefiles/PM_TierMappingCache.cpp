#include "PM_TierMappingCache.h"
#include "ABL_Service.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "CHashTable.h"
#include "ABL_Exception.h"
#include "ABL_String.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_TierMappingCache()
{
	return ( (Base_Registry*) new PM_TierMappingCache);
}
}

bool PM_TierMappingCache:: mb_isEqual(CBase* p_CBase_ptr)
{

	if(((PM_TierMappingCache*)p_CBase_ptr)->ms_OriginZone == ms_OriginZone  && ((PM_TierMappingCache*)p_CBase_ptr)->ms_DestinationZone == ms_DestinationZone  && ((PM_TierMappingCache*)p_CBase_ptr)->ms_PartnerCode == ms_PartnerCode)
	{
			return true;
	}
	else
	{
		return false;
	}

}


PM_TierMappingCache::PM_TierMappingCache(const PM_TierMappingCache& p_copyObject)
{
	
	
	this->ms_OriginZone				=	p_copyObject.ms_OriginZone;
	this->ms_DestinationZone			=	p_copyObject.ms_DestinationZone;
	this->ms_PartnerCode					=	p_copyObject.ms_PartnerCode;
	this->ms_Tier				=	p_copyObject.ms_Tier;
	//modification end
}

CBase* PM_TierMappingCache::mb_createCopy()
{
	return ((CBase*)new PM_TierMappingCache(*this));
}

unsigned int PM_TierMappingCache::mb_hash()
{ 
	return(ms_OriginZone.mb_hash() * 10+ ms_DestinationZone.mb_hash() * 20 +ms_PartnerCode.mb_hash() * 30);

}

bool PM_TierMappingCache::mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause)
{
	ABL_Service *lo_ABLServicePtr = p_ABL_Service_ptr;
	ABL_Connection	lo_ABLConnection;
	ABL_Statement	lo_ABLStatement;
	ABL_ResultSet	lo_ABLResultSet;

        ABL_String	la_OriginZone[500];
	ABL_String	la_DestinationZone[500];
	ABL_String la_PartnerCode[500];
	ABL_String la_Tier[500];
	//modification end
	*lo_ABLServicePtr<<DEBUG<<"Start PM_TierMappingCache Loading"<<Endl;
	ABL_String		ls_ErrorMessage="";


  	try
	{

		lo_ABLConnection.mb_createConnection(*p_ABL_Service_ptr);

		ABL_String	ls_query;

		ls_query="SELECT count(*) FROM PM_PARTNER_TIER_DETAILS ";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_fetch();
		p_container->mb_resize(lo_ABLResultSet.mb_getInt64(1));	
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);		
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);

		//added TRAFFIC_TYPE to select statement for LTE 4.3 release
		ls_query ="SELECT NVL(ORIGIN, ''),NVL(DESTINATION, ''),NVL(PARTNER_CODE, ''),NVL(TIER, '')";
		ls_query +="  FROM PM_PARTNER_TIER_DETAILS ORDER BY ORIGIN,DESTINATION,PARTNER_CODE,TIER"; 
		//modification end
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_setBulkCount(500);

		lo_ABLResultSet	<< la_OriginZone;
		lo_ABLResultSet	<< la_DestinationZone;		
		lo_ABLResultSet	<< la_PartnerCode;
		lo_ABLResultSet	<< la_Tier;
		//modification end

		while(lo_ABLResultSet.mb_fetch())
		{
			int records = lo_ABLResultSet.mb_getNumArrayRows();
			for(int i = 0; i < records ; i++)
			{
				ls_ErrorMessage="";
				ls_ErrorMessage= "Error came while inserting the following data  in the cache : ORIGIN RATE ZONE=>";
				ls_ErrorMessage+=la_OriginZone[i];
				ls_ErrorMessage+=",DEST RATE ZONE=>";
				ls_ErrorMessage+=la_DestinationZone[i];
				ls_ErrorMessage+=",PARTNER CODE=>";
				ls_ErrorMessage+=la_PartnerCode[i];
				ls_ErrorMessage+=",ZONE MAP ID=>";
				ls_ErrorMessage+=la_Tier[i];
				
				//added la_TrafficType to mb_insert for LTE 4.3 release	
				p_container->mb_insert((CBase*) new PM_TierMappingCache(la_OriginZone[i],la_DestinationZone[i],la_PartnerCode[i],la_Tier[i]));
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
	*lo_ABLServicePtr<<DEBUG<<"PM_TierMappingCache Loaded Successfully"<<Endl;
	return true;
}
