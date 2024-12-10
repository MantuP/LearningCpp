#include "PM_Partners_Time_TypeCache.h"
#include "ABL_Service.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "CHashTable.h"
#include "ABL_Exception.h"

extern "C" 
{	EXPORT 
	Base_Registry* gb_getPM_Partners_Time_TypeCache()
	{
	return ( (Base_Registry*) new PM_Partners_Time_TypeCache);
	}
}

bool PM_Partners_Time_TypeCache:: mb_isEqual(CBase* pCBaseptr)
{
	if(((PM_Partners_Time_TypeCache*)pCBaseptr)->ms_TariffPlanCode == ms_TariffPlanCode && ((PM_Partners_Time_TypeCache*)pCBaseptr)->ms_DayCode == ms_DayCode && (((PM_Partners_Time_TypeCache*)pCBaseptr)->ms_StartTime.mb_compare(ms_StartTime)<=0) && (((PM_Partners_Time_TypeCache*)pCBaseptr)->ms_EndTime.mb_compare(ms_EndTime) >=0) )
	{
		//std::cout<<"Tariff Plan Code: "<<((PM_Partners_Time_TypeCache*)pCBaseptr)->ms_TariffPlanCode<<" : "<<ms_TariffPlanCode <<"Day Code: "<<((PM_Partners_Time_TypeCache*)pCBaseptr)->ms_DayCode<<" : "<<ms_DayCode<<" Start Time: "<<((PM_Partners_Time_TypeCache*)pCBaseptr)->ms_StartTime<<" : "<<ms_StartTime<<" End Time : "<<((PM_Partners_Time_TypeCache*)pCBaseptr)->ms_EndTime<<" : "<< ms_EndTime<<std::endl;
			return true;
	}
	else
	{
		return false;
	}
}

PM_Partners_Time_TypeCache::PM_Partners_Time_TypeCache(const PM_Partners_Time_TypeCache& pcopyObject)
{
	this->ms_DayCode				=	pcopyObject.ms_DayCode;
	this->ms_TimeType				=	pcopyObject.ms_TimeType;	
	this->ms_TariffPlanCode			=	pcopyObject.ms_TariffPlanCode;
	this->ms_StartTime				=	pcopyObject.ms_StartTime;
	this->ms_EndTime				=	pcopyObject.ms_EndTime;

}

CBase* PM_Partners_Time_TypeCache::mb_createCopy()
{
	return ((CBase*)new PM_Partners_Time_TypeCache(*this));
}

bool PM_Partners_Time_TypeCache::mb_loadData(data_container *pcontainer, ABL_Service *pABLServiceptr,ABL_String pfilterClause)
{
	ABL_Service *lo_ABLServicePtr = pABLServiceptr;
	ABL_String		la_StartTime[10];
	ABL_String		la_EndTime[10];
	ABL_String		la_DayCode[10];
	ABL_String		la_TimeType[10];
	ABL_String		la_TariffPlanCode[10];
	ABL_String		ls_query;
	ABL_Connection  lo_ABLConnection;
	ABL_Statement   lo_ABLStatement;
	ABL_ResultSet   lo_ABLResultSet;
	*lo_ABLServicePtr<<DEBUG<<"Start PM_Partners_Time_TypeCache Loading"<<Endl;
	 ABL_String		ls_ErrorMessage="";
	try
	{
		
		lo_ABLConnection.mb_createConnection(*pABLServiceptr);

		ls_query="SELECT COUNT(*) as TotalCount  FROM PM_TIME_ZONE";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_fetch();
		pcontainer->mb_resize(lo_ABLResultSet.mb_getInt64(1));
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);
		
		ls_query ="SELECT TO_CHAR(TO_DATE(START_TIME,'HH24:MI:SS'),'HH24MISS'),TO_CHAR(TO_DATE(END_TIME,'HH24:MI:SS'),'HH24MISS') , NVL(DAY_CODE,' '), NVL(TIME_TYPE,' '), NVL(TARIFF_PLAN_CODE,' ')  FROM PM_TIME_ZONE ";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();	
		lo_ABLResultSet.mb_setBulkCount(10);
		lo_ABLResultSet	<<la_StartTime;
		lo_ABLResultSet	<<la_EndTime;
		lo_ABLResultSet	<<la_DayCode;
		lo_ABLResultSet	<<la_TimeType;		
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
				ls_ErrorMessage+=",Start Time=>";
				ls_ErrorMessage+=la_StartTime[i];
				ls_ErrorMessage+=",End Time=>";
				ls_ErrorMessage+=la_EndTime[i];
				
				pcontainer->mb_insert((CBase*) new PM_Partners_Time_TypeCache(la_StartTime[i],la_EndTime[i],la_DayCode[i], la_TimeType[i],la_TariffPlanCode[i]));
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

	*lo_ABLServicePtr<<DEBUG<<"PM_Partners_Time_TypeCache Loaded"<<Endl;
	return true;
}
