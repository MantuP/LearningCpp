/**********************************************************
************************************************************
************************************************************
Agent Name:  PM_FetchPartners_ServicesParametersCache.cpp
Module Name: FrameWork Rating
Dated: 21/01/2010


************************************************************
************************************************************
***********************************************************/

#include "PM_FetchPartners_ServicesParametersCache.h"
#include "ABL_Service.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "CHashTable.h"
#include "ABL_Exception.h"
#include "ABL_Date.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_FetchPartners_ServicesParametersCache()
{
	return ( (Base_Registry*) new PM_FetchPartners_ServicesParametersCache);
}
}

bool PM_FetchPartners_ServicesParametersCache::mb_isEqual(CBase* p_CBase_ptr)
{ 
	if(((PM_FetchPartners_ServicesParametersCache*)p_CBase_ptr)->ms_PartnerCode == ms_PartnerCode  && ((PM_FetchPartners_ServicesParametersCache*)p_CBase_ptr)->ms_ServiceCode == ms_ServiceCode && ((PM_FetchPartners_ServicesParametersCache*)p_CBase_ptr)->ms_Poi == ms_Poi && ((PM_FetchPartners_ServicesParametersCache*)p_CBase_ptr)->ms_CallDirection == ms_CallDirection && (((PM_FetchPartners_ServicesParametersCache*)p_CBase_ptr)->md_ValidFrom <= md_ValidFrom) && (((PM_FetchPartners_ServicesParametersCache*)p_CBase_ptr)->md_ValidTill >= md_ValidTill))
	{
		return true;
	}
	else
	{
		return false;
	}
}
	
PM_FetchPartners_ServicesParametersCache::PM_FetchPartners_ServicesParametersCache(const PM_FetchPartners_ServicesParametersCache& p_copyObject)
{
	this->ms_PartnerCode		=	p_copyObject.ms_PartnerCode;
	this->ms_ServiceCode		=	p_copyObject.ms_ServiceCode;
	this->ms_Poi		        =	p_copyObject.ms_Poi;
	this->ms_CallDirection		=	p_copyObject.ms_CallDirection;
	this->md_ValidFrom	        =	p_copyObject.md_ValidFrom;
	this->md_ValidTill	        =	p_copyObject.md_ValidTill;
	this->ms_ApplyDefaultRate	=	p_copyObject.ms_ApplyDefaultRate;
	this->ms_RateDirection		=	p_copyObject.ms_RateDirection;
	this->ms_PaymentDirection	=	p_copyObject.ms_PaymentDirection;
	this->ms_RateZone	        =	p_copyObject.ms_RateZone;
	this->ms_DestinationType	=	p_copyObject.ms_DestinationType;
	this->md_TestStartDate		=	p_copyObject.md_TestStartDate;
	this->md_TestEndDate		=	p_copyObject.md_TestEndDate;
    this->ms_RateUnit	        =	p_copyObject.ms_RateUnit;
    this->ms_ServiceType        =   p_copyObject.ms_ServiceType;
	this->ms_RateAction         =   p_copyObject.ms_RateAction;

}

CBase* PM_FetchPartners_ServicesParametersCache::mb_createCopy()
{
	 return ((CBase*)new PM_FetchPartners_ServicesParametersCache(*this));
}

unsigned int PM_FetchPartners_ServicesParametersCache:: mb_hash()
{
	return(ms_CallDirection.mb_hash()*10+ms_ServiceCode.mb_hash()*20+ms_Poi.mb_hash()*30);
}

bool PM_FetchPartners_ServicesParametersCache::mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause)
{
 
	ABL_Service *lo_ABLServicePtr = p_ABL_Service_ptr;	
	ABL_String		ls_query;
	ABL_Statement	lo_ABLStatement;
	ABL_Connection	lo_ABLConnection;
	ABL_ResultSet	lo_ABLResultSet;

	ABL_String	la_PartnerCode[10];
	ABL_String	la_ServiceCode[10];
	ABL_String	la_Poi[10];
	ABL_String	la_CallDirection[10];
	ABL_DbDate	la_ValidFrom[10];
	ABL_DbDate	la_ValidTill[10];
	ABL_String	la_ApplyDefaultRate[10];
	ABL_String	la_RateDirection[10];
	ABL_String	la_PaymentDirection[10];
	ABL_String	la_RateZone[10];
	ABL_String	la_DestinationType[10];  
	ABL_DbDate	la_TestStartDate[10];
	ABL_DbDate	la_TestEndDate[10];
    ABL_String	la_RateUnit[10];
    ABL_String      la_ServiceType[10];
	ABL_String  la_RateAction[10];

	*lo_ABLServicePtr<<DEBUG<<"Start PM_FetchPartners_ServicesParametersCache::mb_loadData"<<Endl;
	ABL_String		ls_ErrorMessage="";
	try
	{
		lo_ABLConnection.mb_createConnection(*p_ABL_Service_ptr);

		ls_query="SELECT COUNT(*) as TotalCount  FROM PM_SERVICE_POI ";

		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_fetch();
		p_container->mb_resize(lo_ABLResultSet.mb_getInt64(1));
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);

        ls_query = "SELECT  nvl(PARTNER_CODE,' '),nvl(SERVICE_CODE,' '),nvl(POI,' '),nvl(CALL_DIRECTION,' '),VALID_FROM,VALID_TILL,nvl(APPLY_DEFAULT_RATE,' '),nvl(RATE_DIRECTION,' '),nvl(PAYMENT_DIRECTION,' '),nvl(RATE_ZONE,' '),nvl(DESTINATION_TYPE,' '),nvl(TEST_START_DATE,sysdate),nvl(TEST_END_DATE,sysdate),nvl(RATE_UNIT,' '),nvl(SERVICE_TYPE,' '),nvl(RATE_ACTION,'R') ";
		ls_query+=" FROM PM_SERVICE_POI ";
	
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();	
		lo_ABLResultSet.mb_setBulkCount(10);		
		lo_ABLResultSet	<<la_PartnerCode;
		lo_ABLResultSet	<<la_ServiceCode;
		lo_ABLResultSet	<<la_Poi;
		lo_ABLResultSet	<<la_CallDirection;
		lo_ABLResultSet	<<la_ValidFrom;
		lo_ABLResultSet	<<la_ValidTill;
		lo_ABLResultSet	<<la_ApplyDefaultRate;
		lo_ABLResultSet	<<la_RateDirection;
		lo_ABLResultSet	<<la_PaymentDirection;
		lo_ABLResultSet	<<la_RateZone;
		lo_ABLResultSet	<<la_DestinationType;
		lo_ABLResultSet	<<la_TestStartDate;
		lo_ABLResultSet	<<la_TestEndDate;
    	lo_ABLResultSet	<<la_RateUnit;
        lo_ABLResultSet <<la_ServiceType;
	    lo_ABLResultSet	<<la_RateAction;				

		while(lo_ABLResultSet.mb_fetch())
		{
			int records = lo_ABLResultSet.mb_getNumArrayRows();
			for(int i = 0; i < records ; i++)
			{
				ls_ErrorMessage="";
				ls_ErrorMessage= "Error came while inserting the following data  in the cache : Partner code=>";
				ls_ErrorMessage+=la_PartnerCode[i];
				ls_ErrorMessage+=",Service Code=>";
				ls_ErrorMessage+=la_ServiceCode[i];
				ls_ErrorMessage+=",Poi =>";
				ls_ErrorMessage+=la_Poi[i];
				ls_ErrorMessage+=",Call Direction=>";
				ls_ErrorMessage+=la_CallDirection[i];
				ls_ErrorMessage+=",Valid from date=>";
				ls_ErrorMessage+=la_ValidFrom[i].mb_toString();
				ls_ErrorMessage+=",Valid to date=>";
				ls_ErrorMessage+=la_ValidTill[i].mb_toString();				
				p_container->mb_insert((CBase*) new PM_FetchPartners_ServicesParametersCache(la_PartnerCode[i],la_ServiceCode[i],la_Poi[i], la_CallDirection[i], la_ValidFrom[i],la_ValidTill[i],la_ApplyDefaultRate[i],la_RateDirection[i],la_PaymentDirection[i],la_RateZone[i],la_DestinationType[i],la_TestStartDate[i],la_TestEndDate[i],la_RateUnit[i],la_ServiceType[i],la_RateAction[i]));
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
	*lo_ABLServicePtr<<DEBUG<<"end of PM_FetchPartners_ServicesParametersCache::mb_loadData "<<Endl;
	return true;
}


