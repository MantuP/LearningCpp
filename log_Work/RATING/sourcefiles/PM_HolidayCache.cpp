#include "PM_HolidayCache.h"
#include "ABL_Service.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "CHashTable.h"
#include "ABL_Exception.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_HolidayCache()
{
	return ( (Base_Registry*) new PM_HolidayCache);}
}

bool PM_HolidayCache:: mb_isEqual(CBase* pCBaseptr)
{
	if(((PM_HolidayCache*)pCBaseptr)->ms_TariffPlanCode == ms_TariffPlanCode && (((PM_HolidayCache*)pCBaseptr)->md_HolidayDate == md_HolidayDate) )
	{
			return true;
	}
	else
	{
		return false;
	}
}

PM_HolidayCache::PM_HolidayCache(const PM_HolidayCache& pcopyObject)
{
	this->md_HolidayDate			=	pcopyObject.md_HolidayDate;
	this->ms_DayCode				=	pcopyObject.ms_DayCode;
	this->ms_TariffPlanCode			=	pcopyObject.ms_TariffPlanCode;
        this->ms_HolidayId                      =   pcopyObject.ms_HolidayId;
}

CBase* PM_HolidayCache::mb_createCopy()
{
	return ((CBase*)new PM_HolidayCache(*this));
}

bool PM_HolidayCache::mb_loadData(data_container *pcontainer, ABL_Service *pABLServiceptr,ABL_String pfilterClause)
{
	ABL_Service 	*lo_ABLServicePtr = pABLServiceptr;

	ABL_DbDate  	la_HolidayDate[10];
	ABL_String	la_DayCode[10];
	ABL_String	la_TariffPlanCode[10];	
        ABL_String      la_HolidayId[10];       
	
	ABL_Connection 	lo_ABLConnection;
	ABL_Statement 	lo_ABLStatement;
	ABL_ResultSet 	lo_ABLResultSet;
	ABL_String	ls_query;
	*lo_ABLServicePtr<<DEBUG<<"Start PM_HolidayCache Loading"<<Endl;
	 ABL_String		ls_ErrorMessage="";
	try
	{
		lo_ABLConnection.mb_createConnection(*pABLServiceptr);

		ls_query="SELECT COUNT(*) as TotalCount  FROM PM_HOLIDAY";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_fetch();
		pcontainer->mb_resize(lo_ABLResultSet.mb_getInt64(1));
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);

		ls_query ="SELECT  NVL(HOLIDAY_DATE, sysdate),NVL(DAY_CODE, ' '),NVL(TARIFF_PLAN_CODE, ' '),NVL(HOLIDAY_ID,' ') ";
		ls_query+=" FROM PM_HOLIDAY";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();		
		lo_ABLResultSet.mb_setBulkCount(10);
		lo_ABLResultSet	<<la_HolidayDate;
		lo_ABLResultSet	<<la_DayCode;
		lo_ABLResultSet	<<la_TariffPlanCode;
                lo_ABLResultSet <<la_HolidayId;		

		while(lo_ABLResultSet.mb_fetch())
		{
			int records = lo_ABLResultSet.mb_getNumArrayRows();
			for(int i = 0; i < records ; i++)
			{
				ls_ErrorMessage="";
				ls_ErrorMessage= "Error came while inserting the following data  in the cache : Tariff Plan Code=>";
				ls_ErrorMessage+=la_TariffPlanCode[i];
				ls_ErrorMessage+=",Date code=>";
				ls_ErrorMessage+=la_DayCode[i];
				ls_ErrorMessage+=",Holiday Date=>";
				ls_ErrorMessage+=la_HolidayDate[i].mb_toString();

				pcontainer->mb_insert((CBase*) new PM_HolidayCache(la_HolidayDate[i],la_DayCode[i],la_TariffPlanCode[i],la_HolidayId[i]));
					
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
	*lo_ABLServicePtr<<DEBUG<<"PM_HolidayCache Loaded"<<Endl;
	return true;
}
