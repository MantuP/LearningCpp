/***********************************************************
************************************************************
************************************************************
Agent Name:  PM_DeriveServicesCache.h
Module Name: FrameWork Rating
Dated: 21/01/2010


************************************************************
************************************************************
***********************************************************/

#include "PM_DeriveServicesCache.h"
#include "ABL_Service.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "CHashTable.h"
#include "ABL_Exception.h"
#include "ABL_Date.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_DeriveServicesCache()
{
	return ( (Base_Registry*) new PM_DeriveServicesCache);
	  }
}
bool PM_DeriveServicesCache:: mb_isEqual(CBase* p_CBase_ptr )
{


	if(((PM_DeriveServicesCache*)p_CBase_ptr)->ms_OperatorCode == ms_OperatorCode && ((PM_DeriveServicesCache*)p_CBase_ptr)->ms_Poi == ms_Poi && ((PM_DeriveServicesCache*)p_CBase_ptr)->ms_CallDirection == ms_CallDirection  && ((PM_DeriveServicesCache*)p_CBase_ptr)->ms_basic_service == ms_basic_service &&  ((PM_DeriveServicesCache*)p_CBase_ptr)->ms_identify_using == "A" && (((PM_DeriveServicesCache*)p_CBase_ptr)->ms_string_position=="P" && ((PM_DeriveServicesCache*)p_CBase_ptr)->ms_search_ring==ms_ANumber.mb_subStr(0, ((PM_DeriveServicesCache*)p_CBase_ptr)->mn_search_ring_length)) || (((PM_DeriveServicesCache*)p_CBase_ptr)->ms_string_position=="S" && ((PM_DeriveServicesCache*)p_CBase_ptr)->ms_search_ring==ms_ANumber.mb_subStr((ms_ANumber.mb_length()-((PM_DeriveServicesCache*)p_CBase_ptr)->mn_search_ring_length+1),((PM_DeriveServicesCache*)p_CBase_ptr)->mn_search_ring_length))  && (((PM_DeriveServicesCache*)p_CBase_ptr)->md_Valid_From <= md_Valid_From && ((PM_DeriveServicesCache*)p_CBase_ptr)->md_Valid_To >= md_Valid_To) )
	{
					 return true;
	}
	else if(((PM_DeriveServicesCache*)p_CBase_ptr)->ms_OperatorCode == ms_OperatorCode && ((PM_DeriveServicesCache*)p_CBase_ptr)->ms_Poi == ms_Poi && ((PM_DeriveServicesCache*)p_CBase_ptr)->ms_CallDirection == ms_CallDirection && ((PM_DeriveServicesCache*)p_CBase_ptr)->ms_basic_service == ms_basic_service && ((PM_DeriveServicesCache*)p_CBase_ptr)->ms_identify_using == "B" && (((PM_DeriveServicesCache*)p_CBase_ptr)->ms_string_position=="P" && ((PM_DeriveServicesCache*)p_CBase_ptr)->ms_search_ring==ms_BNumber.mb_subStr(0, ((PM_DeriveServicesCache*)p_CBase_ptr)->mn_search_ring_length)) || (((PM_DeriveServicesCache*)p_CBase_ptr)->ms_string_position=="S" && ((PM_DeriveServicesCache*)p_CBase_ptr)->ms_search_ring==ms_BNumber.mb_subStr((ms_BNumber.mb_length()-((PM_DeriveServicesCache*)p_CBase_ptr)->mn_search_ring_length + 1),((PM_DeriveServicesCache*)p_CBase_ptr)->mn_search_ring_length)) && (((PM_DeriveServicesCache*)p_CBase_ptr)->md_Valid_From <= md_Valid_From && ((PM_DeriveServicesCache*)p_CBase_ptr)->md_Valid_To >= md_Valid_To) )
	{
		return true;
	}
	else if(((PM_DeriveServicesCache*)p_CBase_ptr)->ms_OperatorCode == ms_OperatorCode && ((PM_DeriveServicesCache*)p_CBase_ptr)->ms_Poi == ms_Poi && ((PM_DeriveServicesCache*)p_CBase_ptr)->ms_CallDirection == ms_CallDirection && ((PM_DeriveServicesCache*)p_CBase_ptr)->ms_basic_service == ms_basic_service &&  (((PM_DeriveServicesCache*)p_CBase_ptr)->ms_identify_using == "C" && ((PM_DeriveServicesCache*)p_CBase_ptr)->ms_search_ring==ms_Camel.mb_subStr(0, 1)) && ((PM_DeriveServicesCache*)p_CBase_ptr)->md_Valid_From <= md_Valid_From && ((PM_DeriveServicesCache*)p_CBase_ptr)->md_Valid_To >= md_Valid_To && ((PM_DeriveServicesCache*)p_CBase_ptr)->ms_Poi == ms_Poi && ((PM_DeriveServicesCache*)p_CBase_ptr)->ms_CallDirection == ms_CallDirection )
	{
		return true;
	}

	return false;
}

PM_DeriveServicesCache::PM_DeriveServicesCache(const PM_DeriveServicesCache& p_copyObject)
{
	this->md_Valid_From                    =       p_copyObject.md_Valid_From;
	this->md_Valid_To                      =       p_copyObject.md_Valid_To;
	this->md_test_Start_Date               =       p_copyObject.md_test_Start_Date;
	this->md_test_end_date                 =       p_copyObject.md_test_end_date;
	this->ms_ServiceCode                   =       p_copyObject.ms_ServiceCode;
	this->ms_OperatorCode                  =       p_copyObject.ms_OperatorCode;
	this->ms_RateDirection                 =       p_copyObject.ms_RateDirection;
	this->ms_Defaultratezone               =       p_copyObject.ms_Defaultratezone;
	this->ms_RateZone                      =       p_copyObject.ms_RateZone;
	this->ms_RateUnit                      =       p_copyObject.ms_RateUnit;
	this->mn_QtyUnit                       =       p_copyObject.mn_QtyUnit;
	this->ms_PaymentDirection              =       p_copyObject.ms_PaymentDirection;
	this->ms_Destinationtype               =       p_copyObject.ms_Destinationtype;
	this->ms_ServiceType                   =       p_copyObject.ms_ServiceType;
	this->ms_basic_service                 =       p_copyObject.ms_basic_service;
    
	this->ms_identify_using				   =      p_copyObject.ms_identify_using;
	this->ms_string_position			   =      p_copyObject.ms_string_position;
	this->ms_search_ring				   =      p_copyObject.ms_search_ring;
	this->mn_search_ring_length			   =      p_copyObject.mn_search_ring_length;
	this->ms_ANumber					   =      p_copyObject.ms_ANumber;
	this->ms_BNumber					   =      p_copyObject.ms_BNumber;
	this->ms_Camel					       =      p_copyObject.ms_Camel;
	this->ms_TrafficType            	   =	  p_copyObject.ms_TrafficType;
	this->ms_Poi 		                   =      p_copyObject.ms_Poi;
	this->ms_CallDirection                 =      p_copyObject.ms_CallDirection;
	//modification end
       
	
}

CBase* PM_DeriveServicesCache::mb_createCopy()
{
	return ((CBase*)new PM_DeriveServicesCache(*this));
}

unsigned int PM_DeriveServicesCache::mb_hash()
{
	return (ms_OperatorCode.mb_hash()*10 + ms_basic_service.mb_hash()*20); 
}


bool PM_DeriveServicesCache::mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause)
{
	ABL_Service *lo_ABLServicePtr = p_ABL_Service_ptr;	

	ABL_Connection			lo_ABLConnection;
	ABL_Statement			lo_ABLStatement;
	ABL_ResultSet			lo_ABLResultSet;

	ABL_String				ls_query;

	ABL_DbDate				la_Valid_From[10];
	ABL_DbDate				la_Valid_To[10];
	ABL_DbDate				la_test_Start_Date[10];
	ABL_DbDate				la_test_end_date[10];
	ABL_String				la_ServiceCode[10];
	ABL_String				la_OperatorCode[10];

	ABL_String				la_RateDirection[10];
	ABL_String				la_Defaultratezone[10];
	ABL_String              la_RateZone[10];

	ABL_String				la_PaymentDirection[10];
	ABL_String				la_RateUnit[10];
	int						la_QtyUnit[10];
	ABL_String				la_Destinationtype[10];
	ABL_String				la_ServiceType[10];
	ABL_String				la_BasicService[10];
	ABL_String				la_IdentifyUsing[10];
	ABL_String				la_StringPosition[10];
	ABL_String				la_SearchString[10];
	int						la_searchStringLength[10];
	//added as per LTE usage for 4.3 release
    ABL_String              la_TrafficType[10];
    ABL_String              la_Poi[10];
    ABL_String              la_CallDirection[10];
   //modification end



	*lo_ABLServicePtr<<DEBUG<<"Start PM_DeriveServicesCache Loading"<<Endl;
	try
	{
		

		lo_ABLConnection.mb_createConnection(*p_ABL_Service_ptr);

		ls_query="SELECT COUNT(*) as TotalCount FROM PM_SERVICE_POI";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_fetch();
		p_container->mb_resize(lo_ABLResultSet.mb_getInt64(1));
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);

 		//ls_query = "SELECT valid_from,valid_to,NVL (test_start_date, SYSDATE),NVL (test_end_date, SYSDATE),NVL (service_code, ' '),NVL (partner_code, ' '),NVL (inc_rate_direction, ' '),NVL (out_rate_direction, ' '),NVL (inc_default_rate_zone, ' '),NVL (out_default_rate_zone, ' '),NVL (inc_rate_intrconnect, ' '),NVL (out_rate_interconnect, ' '),NVL (inc_rate_unit, ' '),NVL (inc_unit_qty, 0),NVL (out_rate_unit, ' '),NVL (out_unit_qty, 0),NVL (inc_payment_direction, ' '),NVL (out_payment_direction, ' '),NVL (inc_destination_type, ' '),NVL (out_destination_type, ' '),NVL (service_type, ' '), 'C' AS data_type_indicator,NVL (basic_service, ' ')  FROM pm_service";		
		
//added inc_traffic_type and out_traffic_type as per LTE usage for 4.3 release
ls_query="SELECT valid_from,valid_till,NVL (test_start_date, SYSDATE),NVL (test_end_date, SYSDATE),NVL (service_code, ' '),NVL (partner_code, ' '),NVL (rate_direction, ' '),NVL (APPLY_DEFAULT_RATE, ' '),NVL(RATE_ZONE, ' '),NVL (rate_unit, ' '),NVL (QTY_PER_UNIT, 0),NVL (payment_direction, ' '),NVL (destination_type, ' '),NVL (service_type, ' '),NVL (basic_service, ' '),nvl(identify_using,' '),nvl(string_position,0),nvl(search_string,' '),nvl(length(search_string),0),nvl(traffic_type,' '),NVL(POI, ' '),NVL(CALL_DIRECTION,' ') FROM pm_service_poi where (basic_service is not null and search_string is not null)";

		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_setBulkCount(10);


		lo_ABLResultSet<<la_Valid_From;
		lo_ABLResultSet<<la_Valid_To;
		lo_ABLResultSet<<la_test_Start_Date;
		lo_ABLResultSet<<la_test_end_date;
		lo_ABLResultSet<<la_ServiceCode;
		lo_ABLResultSet<<la_OperatorCode;
		lo_ABLResultSet<<la_RateDirection;
		lo_ABLResultSet<<la_Defaultratezone;
        lo_ABLResultSet<<la_RateZone;
		lo_ABLResultSet<<la_RateUnit;
		lo_ABLResultSet<<la_QtyUnit;
		lo_ABLResultSet<<la_PaymentDirection;
		lo_ABLResultSet<<la_Destinationtype;
		lo_ABLResultSet<<la_ServiceType;
		lo_ABLResultSet<<la_BasicService;
		lo_ABLResultSet<<la_IdentifyUsing;
		lo_ABLResultSet<<la_StringPosition;
		lo_ABLResultSet<<la_SearchString;
		lo_ABLResultSet<<la_searchStringLength;
	   	lo_ABLResultSet<<la_TrafficType;
       	lo_ABLResultSet<<la_Poi;
       	lo_ABLResultSet<<la_CallDirection;


		while(lo_ABLResultSet.mb_fetch())
		{
			int records = lo_ABLResultSet.mb_getNumArrayRows();
			for(int i = 0; i < records ; i++)
			{
			//added la_IncTrafficType and la_OutTrafficType as per LTE usage for 4.3 release
				p_container->mb_insert((CBase*) new PM_DeriveServicesCache(la_Valid_From[i],la_Valid_To[i],la_test_Start_Date[i],la_test_end_date[i],la_ServiceCode[i],la_OperatorCode[i],la_RateDirection[i],la_Defaultratezone[i],la_RateZone[i],la_RateUnit[i],la_QtyUnit[i],la_PaymentDirection[i],la_Destinationtype[i], la_ServiceType[i],la_BasicService[i],la_IdentifyUsing[i],la_StringPosition[i],la_SearchString[i],la_searchStringLength[i],la_TrafficType[i],la_Poi[i],la_CallDirection[i]));
			}			
		}
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);
	}
	catch(ABL_Exception &e)
	{
		*lo_ABLServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
		return false;
	}
	catch(...)
	{
		*lo_ABLServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}
     *lo_ABLServicePtr<<DEBUG<<"PM_DeriveServicesCache Loaded"<<Endl;
	return true;
}

