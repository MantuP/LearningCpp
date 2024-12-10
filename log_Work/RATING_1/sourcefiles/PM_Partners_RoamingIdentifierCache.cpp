#include "PM_Partners_RoamingIdentifierCache.h"
#include "ABL_Service.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "CHashTable.h"
#include "ABL_Exception.h"
#include "ABL_Date.h"


extern "C" {EXPORT 
Base_Registry* gb_getPM_Partners_RoamingIdentifierCache()
{
	return ( (Base_Registry*) new PM_Partners_RoamingIdentifierCache);}
}
bool PM_Partners_RoamingIdentifierCache::mb_isEqual(CBase* p_CBase_ptr)
{ 
	try
	{
			if(((PM_Partners_RoamingIdentifierCache*)p_CBase_ptr)->ms_TransferType == ms_TransferType  && ((PM_Partners_RoamingIdentifierCache*)p_CBase_ptr)->ms_TrunkCode == ms_TrunkCode && (((PM_Partners_RoamingIdentifierCache*)p_CBase_ptr)->md_Valid_From <= md_Valid_From) && (((PM_Partners_RoamingIdentifierCache*)p_CBase_ptr)->md_Valid_To >= md_Valid_To) )
			{
				return true;
			}
			else
			{
				return false;
			}
	}
	catch (...)
	{
		std::cout<<"Exception has occured  while searching the roaming partner in chacne."<<std::endl;
	}
}
PM_Partners_RoamingIdentifierCache::PM_Partners_RoamingIdentifierCache(const PM_Partners_RoamingIdentifierCache& p_copyObject)
{
	this->ms_TransferType			=	p_copyObject.ms_TransferType;
	this->ms_POICode				=	p_copyObject.ms_POICode;
	this->ms_TrunkCode				=	p_copyObject.ms_TrunkCode;
	this->ms_TobeRated				=	p_copyObject.ms_TobeRated;
	this->ms_RateZone				=	p_copyObject.ms_RateZone;
	this->ms_PartnerCode			=	p_copyObject.ms_PartnerCode;
	this->ms_OperationalDomain		=   p_copyObject.ms_OperationalDomain;
	this->mn_RecordingEntityType	=	p_copyObject.mn_RecordingEntityType;	
	this->ms_AppOwner				=	p_copyObject.ms_AppOwner;
	this->ms_AllowIcTraffic			=	p_copyObject.ms_AllowIcTraffic;
	this->mn_PiLen					=	p_copyObject.mn_PiLen;	
	this->md_Valid_From				=	p_copyObject.md_Valid_From;
	this->md_Valid_To				=	p_copyObject.md_Valid_To;
}

unsigned int PM_Partners_RoamingIdentifierCache::mb_hash()
{ 
		return (ms_TrunkCode.mb_hash() * 10 + ms_TransferType.mb_hash() * 20 );


}

CBase* PM_Partners_RoamingIdentifierCache::mb_createCopy()
{
	return ((CBase*)new PM_Partners_RoamingIdentifierCache(*this));
}

bool PM_Partners_RoamingIdentifierCache::mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause)
{
	ABL_Service *lo_ABLServicePtr = p_ABL_Service_ptr;	
	ABL_String		ls_query;
	ABL_Statement   lo_ABLStatement;
	ABL_Connection  lo_ABLConnection;
	ABL_ResultSet   lo_ABLResultSet;

	ABL_DbDate	la_Valid_From[10];
	ABL_DbDate	la_Valid_To[10];
	ABL_String	la_TransferType[10];
	ABL_String	la_POICode[10];
	ABL_String	la_TrunkCode[10];
	ABL_String	la_TobeRated[10];
	ABL_String	la_RateZone[10];
	ABL_String	la_PartnerCode[10];
	ABL_String	la_OperationalDomain[10];
	int         la_RecordingEntityType[10];
	ABL_String	la_AppOwner[10];
	ABL_String	la_AllowIcTraffic[10];
	int         la_PiLen[110];
	*lo_ABLServicePtr<<DEBUG<<"Start PM_Partners_RoamingIdentifierCache Loading"<<Endl;
	ABL_String		ls_ErrorMessage="";
	try
	{
		
		lo_ABLConnection.mb_createConnection(*p_ABL_Service_ptr);

		ls_query="SELECT COUNT(*) as TotalCount  FROM PM_PARTNER_IDENTIFIER I,PM_PARTNER P WHERE I.PARTNER_CODE = P.PARTNER_CODE AND P.AGREEMENT_TYPE='R'";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_fetch();
		p_container->mb_resize(lo_ABLResultSet.mb_getInt64(1));
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);

		ls_query ="SELECT I.VALID_FROM , I.VALID_TO,NVL (I.TRANSFER_TYPE, ' '),NVL (I.PARTNER_CODE, ' '),NVL (I.POI_CODE, ' '),NVL (I.TRUNK_CODE, ' '),NVL (I.TOBE_RATED, ' '),NVL (I.RATE_ZONE, ' '), ";
		ls_query+="nvl(p.operational_domain,'N') OperationalDomain,NVL((select recording_entity_type from pm_recording_entities a where a.recording_entity_desc = i.ne_code),0)as recording_entity_type, " ;  
		ls_query+="p.app_owner,i.allow_ic_traffic, LENGTH(i.trunk_code) Pi_Len " ;  
		ls_query+=" FROM PM_PARTNER_IDENTIFIER I,PM_PARTNER P WHERE I.PARTNER_CODE = P.PARTNER_CODE  AND P.AGREEMENT_TYPE='R' ORDER BY 1 desc ";
	
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();	
		lo_ABLResultSet.mb_setBulkCount(10);
		lo_ABLResultSet	<<la_Valid_From;
		lo_ABLResultSet	<<la_Valid_To;
		lo_ABLResultSet	<<la_TransferType;
		lo_ABLResultSet	<<la_PartnerCode;
		lo_ABLResultSet	<<la_POICode;
		lo_ABLResultSet	<<la_TrunkCode;
		lo_ABLResultSet	<<la_TobeRated;
		lo_ABLResultSet	<<la_RateZone;
		lo_ABLResultSet	<<la_OperationalDomain;
		lo_ABLResultSet	<<la_RecordingEntityType;	
		lo_ABLResultSet	<<la_AppOwner;	
		lo_ABLResultSet	<<la_AllowIcTraffic;	
		lo_ABLResultSet	<<la_PiLen;	
		while(lo_ABLResultSet.mb_fetch())
		{

			int records = lo_ABLResultSet.mb_getNumArrayRows();
			for(int i = 0; i < records ; i++)
			{
		
				ls_ErrorMessage="";
				ls_ErrorMessage= "Error came while inserting the following data  in the cache : ";
				ls_ErrorMessage+=",Transfer Type=>";
				ls_ErrorMessage+=la_TransferType[i];
				ls_ErrorMessage+=",Trunk Code=>";
				ls_ErrorMessage+=la_TrunkCode[i];
				ls_ErrorMessage+=",Valid from date=>";
				ls_ErrorMessage+=la_Valid_From[i].mb_toString();
				ls_ErrorMessage+=",Valid to date=>";
				ls_ErrorMessage+=la_Valid_To[i].mb_toString();
				p_container->mb_insert((CBase*) new PM_Partners_RoamingIdentifierCache(la_Valid_From[i],la_Valid_To[i],la_TransferType[i],la_PartnerCode[i],la_POICode[i],la_TrunkCode[i],la_TobeRated[i],la_RateZone[i],la_OperationalDomain[i],la_RecordingEntityType[i],la_AppOwner[i],la_AllowIcTraffic[i],la_PiLen[i]));					
		
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
	*lo_ABLServicePtr<<DEBUG<<"PM_Partners_RoamingIdentifierCache Loaded"<<Endl;
	return true;
}
