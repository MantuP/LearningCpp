#include "PM_Partner_TariffCache.h"
#include "ABL_Service.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "CHashTable.h"
#include "ABL_Exception.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_Partner_TariffCache()
{
	return ( (Base_Registry*) new PM_Partner_TariffCache);
}
}
bool PM_Partner_TariffCache:: mb_isEqual(CBase* pCBaseptr)
{ 
	try
	{
	if(((PM_Partner_TariffCache*)pCBaseptr)->ms_TariffPlanCode == ms_TariffPlanCode  && ((PM_Partner_TariffCache*)pCBaseptr)->ms_CallDirection == ms_CallDirection  && ((PM_Partner_TariffCache*)pCBaseptr)->ms_ServiceCode == ms_ServiceCode && ((PM_Partner_TariffCache*)pCBaseptr)->ms_TimeType == ms_TimeType && ((PM_Partner_TariffCache*)pCBaseptr)->ms_RateZone == ms_RateZone && ((PM_Partner_TariffCache*)pCBaseptr)->ms_DayCode == ms_DayCode   &&  (((PM_Partner_TariffCache*)pCBaseptr)->md_ValidFrom <= md_ValidFrom)  && (((PM_Partner_TariffCache*)pCBaseptr)->md_ValidTo >= md_ValidTo) && ((PM_Partner_TariffCache*)pCBaseptr)->ms_Tier == ms_Tier )
	{
			return true;
	}
	else
	{
		return false;
	}
	}
	catch(ABL_Exception &e)
	{
		std::cout <<  "Erorr while loading tariff : " <<e.mb_getMessage() <<std::endl;
		return true;
	}
}

PM_Partner_TariffCache::PM_Partner_TariffCache(const PM_Partner_TariffCache& pcopyObject)
{
	
	this->mn_TariffId				=	pcopyObject.mn_TariffId;
	this->ms_TariffPlanCode			=	pcopyObject.ms_TariffPlanCode;
	this->ms_ServiceCode			=	pcopyObject.ms_ServiceCode;
	this->ms_RateZone				=	pcopyObject.ms_RateZone;
	this->ms_TimeType				=	pcopyObject.ms_TimeType;
	this->ms_CallDirection			=	pcopyObject.ms_CallDirection;
	this->mn_InitialFreeUnit		=	pcopyObject.mn_InitialFreeUnit;
	this->mn_MinChargebleUnit		=	pcopyObject.mn_MinChargebleUnit;
	this->mn_InitialFlatAmt			=	pcopyObject.mn_InitialFlatAmt;
	this->mn_MinAmount				=	pcopyObject.mn_MinAmount;
	this->mn_UnitRate				=	pcopyObject.mn_UnitRate;
	this->mn_TaxPercent				=	pcopyObject.mn_TaxPercent;
	this->ms_ChargeType				=	pcopyObject.ms_ChargeType;
	this->mn_QtyPerUnit				=	pcopyObject.mn_QtyPerUnit;
	this->md_ValidFrom				=	pcopyObject.md_ValidFrom;
	this->md_ValidTo				=	pcopyObject.md_ValidTo;
	this->ms_RoundUnits				=	pcopyObject.ms_RoundUnits;
	this->ms_CurrencyCode			=	pcopyObject.ms_CurrencyCode;
	this->ms_Invoice				=	pcopyObject.ms_Invoice;
        this->ms_DayCode                                =       pcopyObject.ms_DayCode;
	
}

CBase* PM_Partner_TariffCache::mb_createCopy()
{
	return ((CBase*)new PM_Partner_TariffCache(*this));
}

bool PM_Partner_TariffCache::mb_loadData(data_container *pcontainer, ABL_Service *pABLServiceptr,ABL_String pfilterClause)
{
	ABL_Service *lo_ABServicePtr = pABLServiceptr;
	ABL_String		ls_query;
	ABL_Connection	lo_ABLConnection;
	ABL_Statement	lo_ABLStatement;
	ABL_ResultSet	lo_ABLResultSet;


	ABL_DbDate		la_ValidFrom[10];
	ABL_DbDate		la_ValidTo[10];
	double			la_TariffId[10];
	ABL_String		la_TariffPlanCode[10];
	ABL_String		la_ServiceCode[10];
	ABL_String		la_RateZone[10];
	ABL_String		la_TimeType[10];
	ABL_String		la_CallDirection[10];
	int				la_InitialFreeUnit[10];
	int				la_MinChargebleUnit[10];
	double			la_InitialFlatAmt[10];
	double			la_MinAmount[10];
	double			la_UnitRate[10];
	double			la_TaxPercent[10];
	ABL_String		la_ChargeType[10];
	int				la_QtyPerUnit[10];
	ABL_String		la_RoundUnits[10];
	ABL_String		la_CurrencyCode[10];
	ABL_String		la_Invoice[10];
	ABL_String		la_TariffType[10];
	int             la_RevenueSahre[10];  
        ABL_String              la_DayCode[10];
     ABL_String              la_Tier[10];

	*lo_ABServicePtr<<DEBUG<<"Start PM_Partner_TariffCache Loading"<<Endl;
	 ABL_String		ls_ErrorMessage="";
	try
	{
		lo_ABLConnection.mb_createConnection(*pABLServiceptr);

		ls_query="SELECT COUNT(*) as TotalCount  FROM PM_TARIFF";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_fetch();
		pcontainer->mb_resize(lo_ABLResultSet.mb_getInt64(1));
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);
		ls_query = "SELECT VALID_FROM , VALID_TO, TARIFF_ID,NVL(TARIFF_PLAN_CODE,' '),NVL(SERVICE_CODE,' '),NVL(RATE_ZONE,' '),	NVL(TIME_TYPE,' '),	NVL(CALL_DIRECTION,' '),NVL(INITIAL_FREE_UNIT, 0),NVL(MIN_CHARGEBLE_UNIT,0),NVL(INITIAL_FLAT_AMT,0),NVL(MIN_AMOUNT,0),NVL(UNIT_RATE,0),NVL(TAX_PERCENT,0),NVL(CHARGE_TYPE, ' '),decode(qty_per_unit,0,1,null,1,qty_per_unit) qty_per_unit, NVL(ROUND_UNITS,' '),	NVL(CURRENCY_CODE,' '),	NVL(INVOICE,' '),NVL(TARIFF_TYPE,' '),NVL(REVENUE_SHARE,0),NVL(DAY_CODE,' '),NVL(TIER_ID,' ') ";
		ls_query+= "FROM PM_TARIFF ORDER BY TARIFF_PLAN_CODE, CALL_DIRECTION, DAY_CODE, SERVICE_CODE, TIME_TYPE, RATE_ZONE";
		
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_setBulkCount(10);

		lo_ABLResultSet	<< la_ValidFrom;
		lo_ABLResultSet	<< la_ValidTo;
		lo_ABLResultSet	<< la_TariffId;
		lo_ABLResultSet	<< la_TariffPlanCode;
		lo_ABLResultSet	<< la_ServiceCode;
		lo_ABLResultSet	<< la_RateZone;
		lo_ABLResultSet	<< la_TimeType;
		lo_ABLResultSet	<< la_CallDirection;
		lo_ABLResultSet	<< la_InitialFreeUnit;
		lo_ABLResultSet	<< la_MinChargebleUnit;
		lo_ABLResultSet	<< la_InitialFlatAmt;
		lo_ABLResultSet	<< la_MinAmount;
		lo_ABLResultSet	<< la_UnitRate;
		lo_ABLResultSet	<< la_TaxPercent;
		lo_ABLResultSet	<< la_ChargeType;
		lo_ABLResultSet	<< la_QtyPerUnit;
		lo_ABLResultSet	<< la_RoundUnits;
		lo_ABLResultSet	<< la_CurrencyCode;
		lo_ABLResultSet	<< la_Invoice;
		lo_ABLResultSet	<< la_TariffType;
		lo_ABLResultSet	<< la_RevenueSahre;
                lo_ABLResultSet << la_DayCode;
				lo_ABLResultSet	<< la_Tier;

		while(lo_ABLResultSet.mb_fetch())
		{
			int records = lo_ABLResultSet.mb_getNumArrayRows();
			for(int i = 0; i < records ; i++)
			{

				ls_ErrorMessage="";
				ls_ErrorMessage= "Error came while inserting the following data  in the cache : Tariff Plan code=>";
				ls_ErrorMessage+=la_TariffPlanCode[i];
				ls_ErrorMessage+=",Service Code=>";
				ls_ErrorMessage+=la_ServiceCode[i];
				ls_ErrorMessage+=",Rate Zone =>";
				ls_ErrorMessage+=la_RateZone[i];
                                ls_ErrorMessage+=", Tier Id =>";
                                ls_ErrorMessage+=la_Tier[i];
				ls_ErrorMessage+=",Time Type=>";
				ls_ErrorMessage+=la_TimeType[i];
				ls_ErrorMessage+=",Call Direction=>";
				ls_ErrorMessage+=la_CallDirection[i];
				ls_ErrorMessage+=",Valid from date=>";
				ls_ErrorMessage+=la_ValidFrom[i].mb_toString();
				ls_ErrorMessage+=",Valid to date=>";
				ls_ErrorMessage+=la_ValidTo[i].mb_toString();

				pcontainer->mb_insert((CBase*) new PM_Partner_TariffCache(la_ValidFrom[i],la_ValidTo[i],la_TariffId[i],la_TariffPlanCode[i],la_ServiceCode[i],la_RateZone[i],la_TimeType[i],la_CallDirection[i],la_InitialFreeUnit[i],la_MinChargebleUnit[i],la_InitialFlatAmt[i],la_MinAmount[i],la_UnitRate[i],la_TaxPercent[i],la_ChargeType[i],la_QtyPerUnit[i],la_RoundUnits[i],la_CurrencyCode[i],la_Invoice[i],la_TariffType[i],la_RevenueSahre[i],la_DayCode[i],la_Tier[i]));
			}
		
		}
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);
	}
	catch(ABL_Exception &e)
	{
		*lo_ABServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<" : "<<ls_ErrorMessage<<Endl;
		return false;
	}
	catch(...)
	{
		*lo_ABServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}
	*lo_ABServicePtr<<DEBUG<<"PM_Partner_TariffCache Loaded"<<Endl;
	return true;
}
