#include "PM_Tariffplan_DayCodeCache.h"
#include "ABL_Service.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "CHashTable.h"
#include "ABL_Exception.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_Tariffplan_DayCodeCache()
{
	return ( (Base_Registry*) new PM_Tariffplan_DayCodeCache);}
}

bool PM_Tariffplan_DayCodeCache:: mb_isEqual(CBase* pCBaseptr)
{
	
	if( (((PM_Tariffplan_DayCodeCache*)pCBaseptr)->ms_DayCode == ms_DayCode) && ((PM_Tariffplan_DayCodeCache*)pCBaseptr)->ms_TariffPlanCode == ms_TariffPlanCode )
	{
			return true;
	}
	else
	{
		return false;
	}
}

PM_Tariffplan_DayCodeCache::PM_Tariffplan_DayCodeCache(const PM_Tariffplan_DayCodeCache& pcopyObject)
{
	
	this->ms_DayCode			=	pcopyObject.ms_DayCode;
	this->ms_TariffPlanCode		=	pcopyObject.ms_TariffPlanCode;
}

CBase* PM_Tariffplan_DayCodeCache::mb_createCopy()
{
	return ((CBase*)new PM_Tariffplan_DayCodeCache(*this));
}

bool PM_Tariffplan_DayCodeCache::mb_loadData(data_container *pcontainer, ABL_Service *pABLServiceptr,ABL_String pfilterClause)
{
	ABL_Service *lo_ABLServicePtr = pABLServiceptr;
	ABL_Connection	lo_ABLConnection;
	ABL_Statement	lo_ABLStatement;
	ABL_ResultSet	lo_ABLResultSet;
	ABL_String		ls_query;

	ABL_String	la_DayCode[10];
	ABL_String	la_TariffPlanCode[10];	
	
	*lo_ABLServicePtr<<DEBUG<<"Start PM_Tariffplan_DayCodeCache Loading"<<Endl;
	 ABL_String		ls_ErrorMessage="";
	try
	{
		lo_ABLConnection.mb_createConnection(*pABLServiceptr);

		ls_query="SELECT COUNT(*) as TotalCount from pm_day_code";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_fetch();
		pcontainer->mb_resize(lo_ABLResultSet.mb_getInt64(1));
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);

		ls_query ="select NVL(DAY_CODE,' '),NVL(TARIFF_PLAN_CODE,' ') from pm_day_code";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();		
		lo_ABLResultSet.mb_setBulkCount(10);	

		lo_ABLResultSet	<<la_DayCode;
		lo_ABLResultSet	<<la_TariffPlanCode;		
		while(lo_ABLResultSet.mb_fetch())
		{
			int records = lo_ABLResultSet.mb_getNumArrayRows();
			for(int i = 0; i < records ; i++)
			{
				ls_ErrorMessage="";
				ls_ErrorMessage= "Error came while inserting the following data  in the cache : Tariff Plan Code=>";
				ls_ErrorMessage+=la_TariffPlanCode[i];
				ls_ErrorMessage+=",Day Code=>";
				ls_ErrorMessage+=la_DayCode[i];

				pcontainer->mb_insert((CBase*) new PM_Tariffplan_DayCodeCache(la_DayCode[i],la_TariffPlanCode[i]));
				
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

	*lo_ABLServicePtr<<DEBUG<<"PM_Tariffplan_DayCodeCache Loaded"<<Endl;
	return true;
}
