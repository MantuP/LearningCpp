#include "PM_FindRecordingentityTypeCache.h"
#include "ABL_Service.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "CHashTable.h"
#include "ABL_Exception.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_FindRecordingentityTypeCache()
{
	return ( (Base_Registry*) new PM_FindRecordingentityTypeCache);}
}

bool PM_FindRecordingentityTypeCache:: mb_isEqual(CBase* p_CBase_ptr)
{
	
	if(((PM_FindRecordingentityTypeCache*)p_CBase_ptr)->ms_RecordingEntityDesc == ms_RecordingEntityDesc)
	{
			return true;
	}
	else
	{
		return false;
	}
}

unsigned int PM_FindRecordingentityTypeCache::mb_hash()
{
	return (ms_RecordingEntityDesc.mb_hash()); 
}
PM_FindRecordingentityTypeCache::PM_FindRecordingentityTypeCache(const PM_FindRecordingentityTypeCache& p_copyObject)
{
	this->ms_RecordingEntityDesc=	p_copyObject.ms_RecordingEntityDesc;	
	this->mn_RecoringEntityType	=	p_copyObject.mn_RecoringEntityType;	
}

CBase* PM_FindRecordingentityTypeCache::mb_createCopy()
{
	return ((CBase*)new PM_FindRecordingentityTypeCache(*this));
}

bool PM_FindRecordingentityTypeCache::mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause)
{
	ABL_Service *lo_ABLServicePtr = p_ABL_Service_ptr;
	ABL_String			la_RECORDINGENTITYDESC[10];	
	unsigned int		la_RECORDINGENTITYTYPE[10];	
	ABL_String			ls_query;
	ABL_Statement		lo_ABLStatement;
	ABL_Connection		lo_ABLConnection;
	ABL_ResultSet		lo_ABLResultSet;
	ABL_String			ls_ErrorMessage="";
	*lo_ABLServicePtr<<DEBUG<<"Start PM_FindRecordingentityTypeCache Loading"<<Endl;
	try
	{
		
		lo_ABLConnection.mb_createConnection(*p_ABL_Service_ptr);

		ls_query="SELECT COUNT(*) as TotalCount  FROM pm_recording_entities ";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_fetch();
		p_container->mb_resize(lo_ABLResultSet.mb_getInt64(1));
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);

		
		ls_query ="SELECT NVL(RECORDING_ENTITY_DESC,' '),RECORDING_ENTITY_TYPE  FROM pm_recording_entities";
		
		
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_setBulkCount(10);
		lo_ABLResultSet	<<la_RECORDINGENTITYDESC;
		lo_ABLResultSet	<<la_RECORDINGENTITYTYPE;
		while(lo_ABLResultSet.mb_fetch())
		{
			int records = lo_ABLResultSet.mb_getNumArrayRows();
			for(int i = 0; i < records ; i++)
			{
				ls_ErrorMessage="";
				ls_ErrorMessage= "Error came while inserting the following data  in the cache for : Recording entity=>";
				ls_ErrorMessage+=la_RECORDINGENTITYDESC[i];
				p_container->mb_insert((CBase*) new PM_FindRecordingentityTypeCache(la_RECORDINGENTITYDESC[i],la_RECORDINGENTITYTYPE[i]));
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
	*lo_ABLServicePtr<<DEBUG<<"PM_FindRecordingentityTypeCache Loaded"<<Endl;
	return true;
}
