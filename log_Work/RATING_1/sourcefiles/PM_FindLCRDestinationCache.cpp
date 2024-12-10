#include "PM_FindLCRDestinationCache.h"
#include "ABL_Service.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "CHashTable.h"
#include "ABL_Exception.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_FindLCRDestinationCache()
{
	return ( (Base_Registry*) new PM_FindLCRDestinationCache);}
}

bool PM_FindLCRDestinationCache:: mb_isEqual(CBase* p_CBase_ptr)
{
	
	if(((PM_FindLCRDestinationCache*)p_CBase_ptr)->ms_LCR_destination == ms_LCR_destination)
	{
			return true;
	}
	else
	{
		return false;
	}
}

PM_FindLCRDestinationCache::PM_FindLCRDestinationCache(const PM_FindLCRDestinationCache& p_copyObject)
{
	this->ms_LCR_destination				=	p_copyObject.ms_LCR_destination;	
}

CBase* PM_FindLCRDestinationCache::mb_createCopy()
{
	return ((CBase*)new PM_FindLCRDestinationCache(*this));
}

bool PM_FindLCRDestinationCache::mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause)
{
	ABL_Service *lo_ABLServicePtr = p_ABL_Service_ptr;
	ABL_String			la_LCRdestination[10];	
	ABL_String			ls_query;
	ABL_Statement		lo_ABLStatement;
	ABL_Connection		lo_ABLConnection;
	ABL_ResultSet		lo_ABLResultSet;
	ABL_String			ls_ErrorMessage="";
	*lo_ABLServicePtr<<DEBUG<<"Start PM_FindLCRDestinationCache Loading"<<Endl;
	try
	{
		
		lo_ABLConnection.mb_createConnection(*p_ABL_Service_ptr);

		ls_query="SELECT COUNT(*) as TotalCount  FROM PM_LCR_DESTINATIONS ";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_fetch();
		p_container->mb_resize(lo_ABLResultSet.mb_getInt64(1));
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);

		
		ls_query ="SELECT NVL(lcr_destination,' ')  FROM PM_LCR_DESTINATIONS";
		
		
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_setBulkCount(10);
		lo_ABLResultSet	<<la_LCRdestination;
		while(lo_ABLResultSet.mb_fetch())
		{
			int records = lo_ABLResultSet.mb_getNumArrayRows();
			for(int i = 0; i < records ; i++)
			{
				ls_ErrorMessage="";
				ls_ErrorMessage= "Error came while inserting the following data  in the cache for : LCR Destination=>";
				ls_ErrorMessage+=la_LCRdestination[i];
				p_container->mb_insert((CBase*) new PM_FindLCRDestinationCache(la_LCRdestination[i]));
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
	*lo_ABLServicePtr<<DEBUG<<"PM_FindLCRDestinationCache Loaded"<<Endl;
	return true;
}
