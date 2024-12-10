/***********************************************************
************************************************************
************************************************************
Agent Name:  PM_ValidServicesCache.cpp
Module Name: FrameWork Rating
Dated: 21/01/2010


************************************************************
************************************************************
***********************************************************/

#include "PM_ValidServicesCache.h"
#include "ABL_Service.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "CHashTable.h"
#include "ABL_Exception.h"
#include "ABL_Date.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_ValidServicesCache()
{
	return ( (Base_Registry*) new PM_ValidServicesCache);
}
	   }

bool PM_ValidServicesCache:: mb_isEqual(CBase* p_CBase_ptr )
{
	if( ((PM_ValidServicesCache*)p_CBase_ptr)->ms_ServiceCode == ms_ServiceCode  && (((PM_ValidServicesCache*)p_CBase_ptr)->md_Valid_From <= md_Valid_From)  && (((PM_ValidServicesCache*)p_CBase_ptr)->md_Valid_To >= md_Valid_To) )
	{			
		return true;
	}	
	else
	{
		return false;
	}
}

PM_ValidServicesCache::PM_ValidServicesCache(const PM_ValidServicesCache& p_copyObject)
{
    this->md_Valid_From                    =       p_copyObject.md_Valid_From;
	this->md_Valid_To                      =       p_copyObject.md_Valid_To;
    this->md_test_Start_Date               =       p_copyObject.md_test_Start_Date;
    this->md_test_end_date                 =       p_copyObject.md_test_end_date;

    this->ms_ServiceCode                   =       p_copyObject.ms_ServiceCode;
    this->ms_OperatorCode                  =       p_copyObject.ms_OperatorCode;
    this->ms_IncRateDirection              =       p_copyObject.ms_IncRateDirection;
    this->ms_OutRateDirection              =       p_copyObject.ms_OutRateDirection;
    this->ms_IncDefaultratezone            =       p_copyObject.ms_IncDefaultratezone;
    this->ms_OutDefaultratezone            =       p_copyObject.ms_OutDefaultratezone;
    this->ms_IncRateIntrConnect            =       p_copyObject.ms_IncRateIntrConnect;
    this->ms_OutRateIntrConnect            =       p_copyObject.ms_OutRateIntrConnect;
    this->ms_IncPaymentDirection           =       p_copyObject.ms_IncPaymentDirection;
    this->ms_OutPaymentDirection           =       p_copyObject.ms_OutPaymentDirection;
    this->ms_IncUnit                       =       p_copyObject.ms_IncUnit;
    this->mn_IncQtyUnit                    =       p_copyObject.mn_IncQtyUnit;
    this->ms_OutUnit                       =       p_copyObject.ms_OutUnit;
    this->mn_OutQtyUnit                    =       p_copyObject.mn_OutQtyUnit;
    this->ms_IncDestinationtype            =       p_copyObject.ms_IncDestinationtype;
    this->ms_OutDestinationtype            =       p_copyObject.ms_OutDestinationtype;
    this->ms_ServiceType                   =       p_copyObject.ms_ServiceType;
    this->ms_DataTypeIndicator             =       p_copyObject.ms_DataTypeIndicator;
    this->ms_basic_service                 =       p_copyObject.ms_basic_service;
	//added as per LTE usage for 4.3 release
    	this->ms_IncTrafficType		=	p_copyObject.ms_IncTrafficType;
	this->ms_OutTrafficType		=	p_copyObject.ms_OutTrafficType;
	//modification end
}

CBase* PM_ValidServicesCache::mb_createCopy()
{
	return ((CBase*)new PM_ValidServicesCache(*this));
}

bool PM_ValidServicesCache::mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause)
{
    ABL_Service *lo_ABLServicePtr = p_ABL_Service_ptr;	
    ABL_Connection	lo_ABLConnection;
    ABL_Statement	lo_ABLStatement;
    ABL_ResultSet	lo_ABLResultSet;
	ABL_String		ls_query;
    ABL_DbDate		la_Valid_From[10];
    ABL_DbDate		la_Valid_To[10];
    ABL_DbDate		la_test_Start_Date[10];
    ABL_DbDate		la_test_end_date[10];
    ABL_String		la_ServiceCode[10];
    ABL_String		la_OperatorCode[10];
    ABL_String		la_IncRateDirection[10];
    ABL_String		la_OutRateDirection[10];
    ABL_String		la_IncDefaultratezone[10];
    ABL_String		la_OutDefaultratezone[10];
    ABL_String		la_IncRateIntrConnect[10];
    ABL_String		la_OutRateIntrConnect[10];
    ABL_String		la_IncPaymentDirection[10];
    ABL_String		la_OutPaymentDirection[10];
    ABL_String		la_IncUnit[10];
    int				la_IncQtyUnit[10];
    ABL_String		la_OutUnit[10];
    int				la_OutQtyUnit[10];
    ABL_String		la_IncDestinationtype[10];
    ABL_String		la_OutDestinationtype[10];
    ABL_String		la_ServiceType[10];
    ABL_String		la_DataTypeIndicator[10];
    ABL_String		la_BasicService[10];	
	//added as per LTE usage for 4.3 release
	ABL_String 	la_IncTrafficType[10];
	ABL_String	la_OutTrafficType[10];
	//modification end
	*lo_ABLServicePtr<<DEBUG<<" PM_ValidServicesCache loading"<<Endl;
	 ABL_String		ls_ErrorMessage="";
	try
	{
		lo_ABLConnection.mb_createConnection(*p_ABL_Service_ptr);
		ls_query="SELECT COUNT(*) as TotalCount FROM PM_SERVICE";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_fetch();
		p_container->mb_resize(lo_ABLResultSet.mb_getInt64(1));
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);

	ls_query ="SELECT valid_from,valid_to,NVL (test_start_date, SYSDATE),NVL (test_end_date, SYSDATE),NVL (service_code, ' '),NVL (partner_code, ' '),NVL (inc_rate_direction, ' '),NVL (out_rate_direction, ' '),NVL (inc_default_rate_zone, ' '),NVL (out_default_rate_zone, ' '),NVL (inc_rate_intrconnect, ' '),NVL (out_rate_interconnect, ' '),NVL (inc_payment_direction, ' '),NVL (out_payment_direction, ' '),NVL (inc_rate_unit, ' '),NVL (inc_unit_qty, 0),NVL (out_rate_unit, ' '),NVL (out_unit_qty, 0),NVL (inc_destination_type, ' '),NVL (out_destination_type, ' '),NVL (service_type, ' '), 'C' AS data_type_indicator,NVL (basic_service, ' '),NVL(inc_traffic_type,' '),NVL(out_traffic_type,' ')  FROM pm_service";	
	lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);
        lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
        lo_ABLResultSet.mb_setBulkCount(10);
    	lo_ABLResultSet << la_Valid_From;
        lo_ABLResultSet << la_Valid_To;
        lo_ABLResultSet << la_test_Start_Date;
        lo_ABLResultSet << la_test_end_date;
        lo_ABLResultSet << la_ServiceCode;
		lo_ABLResultSet << la_OperatorCode;
        lo_ABLResultSet << la_IncRateDirection;
		lo_ABLResultSet << la_OutRateDirection;
		lo_ABLResultSet << la_IncDefaultratezone;
        lo_ABLResultSet << la_OutDefaultratezone;
        lo_ABLResultSet << la_IncRateIntrConnect;
		lo_ABLResultSet << la_OutRateIntrConnect;              
        lo_ABLResultSet << la_IncPaymentDirection;
		lo_ABLResultSet << la_OutPaymentDirection;
        lo_ABLResultSet << la_IncUnit;
        lo_ABLResultSet << la_IncQtyUnit;
		lo_ABLResultSet << la_OutUnit;
        lo_ABLResultSet << la_OutQtyUnit;
		lo_ABLResultSet << la_IncDestinationtype;
        lo_ABLResultSet << la_OutDestinationtype;             
        lo_ABLResultSet << la_ServiceType;
        lo_ABLResultSet << la_DataTypeIndicator;
		lo_ABLResultSet << la_BasicService;
	//added as per LTE usage for 4.3 release
	lo_ABLResultSet << la_IncTrafficType;
	lo_ABLResultSet << la_OutTrafficType;
	//modification end

		while(lo_ABLResultSet.mb_fetch())
		{
			int records = lo_ABLResultSet.mb_getNumArrayRows();
			for(int i = 0; i < records ; i++)
			{
				ls_ErrorMessage="";
				ls_ErrorMessage= "Error came while inserting the following data  in the cache : Service Code=>";
				ls_ErrorMessage+=la_ServiceCode[i];
				ls_ErrorMessage+=",Valid from date=>";
				ls_ErrorMessage+=la_Valid_From[i].mb_toString();
				ls_ErrorMessage+=",Valid to date=>";
				ls_ErrorMessage+=la_Valid_To[i].mb_toString();
			//added la_IncTrafficType and la_OutTrafficType as per LTE for 4.3 release
				p_container->mb_insert((CBase*) new PM_ValidServicesCache(la_Valid_From[i],la_Valid_To[i],la_test_Start_Date[i],la_test_end_date[i],la_ServiceCode[i],la_OperatorCode[i],la_IncRateDirection[i],la_OutRateDirection[i],la_IncDefaultratezone[i],la_OutDefaultratezone[i],la_IncRateIntrConnect[i],la_OutRateIntrConnect[i],la_IncPaymentDirection[i],la_OutPaymentDirection[i],la_IncUnit[i],la_IncQtyUnit[i],la_OutUnit[i],la_OutQtyUnit[i],la_IncDestinationtype[i],la_OutDestinationtype[i],la_ServiceType[i],la_DataTypeIndicator[i],la_BasicService[i],la_IncTrafficType[i],la_OutTrafficType[i]));
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

	*lo_ABLServicePtr<<DEBUG<<"PM_ValidCache Loaded"<<Endl;
	return true;
}


