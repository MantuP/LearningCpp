#include "PM_FindPartnerShortCodesCache.h"
#include "ABL_Service.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "CHashTable.h"
#include "ABL_Exception.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_FindPartnerShortCodesCache()
{
	return ( (Base_Registry*) new PM_FindPartnerShortCodesCache);}
}
bool PM_FindPartnerShortCodesCache:: mb_isEqual(CBase* p_CBase_ptr)
{
	
	if(((PM_FindPartnerShortCodesCache*)p_CBase_ptr)->ms_PartnerCode == ms_PartnerCode && ((PM_FindPartnerShortCodesCache*)p_CBase_ptr)->ms_ShortCode == ms_ShortCode )
	{
			return true;
	}
	else
	{
		return false;
	}
}

PM_FindPartnerShortCodesCache::PM_FindPartnerShortCodesCache(const PM_FindPartnerShortCodesCache& p_copyObject)
{
	this->ms_PartnerCode				=	p_copyObject.ms_PartnerCode;
	this->ms_ShortCode					=	p_copyObject.ms_ShortCode;
	this->ms_TranslatedNumber			=	p_copyObject.ms_TranslatedNumber;
	
}

CBase* PM_FindPartnerShortCodesCache::mb_createCopy()
{
	return ((CBase*)new PM_FindPartnerShortCodesCache(*this));
}

bool PM_FindPartnerShortCodesCache::mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause)
{
	ABL_Service *lo_ABLServicePtr = p_ABL_Service_ptr;	
	ABL_String	ls_query;
	ABL_Statement lo_ABLStatement;
	ABL_Connection lo_ABLConnection;
	ABL_ResultSet lo_ABLResultSet;
	*lo_ABLServicePtr<<DEBUG<<"Start PM_FindPartnerShortCodesCache Loading"<<Endl;
	ABL_String		ls_ErrorMessage="";
	try
	{
		
		lo_ABLConnection.mb_createConnection(*p_ABL_Service_ptr);
		ls_query="SELECT COUNT(*) as TotalCount  FROM PM_ROAM_PARTNER_SHORT_CODES ";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_fetch();
		p_container->mb_resize(lo_ABLResultSet.mb_getInt64(1));
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);
		
		ls_query ="select nvl(PARTNER_CODE,' ') ,nvl(SHORT_CODE,' '), nvl(TRANSLATED_NUMBER,' ') from PM_ROAM_PARTNER_SHORT_CODES order by 1 asc";		
		
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();

		ABL_String	la_PartnerCode[10];
		ABL_String	la_ShortCode[10];
		ABL_String	la_TranslatedNumber[10];


		lo_ABLResultSet.mb_setBulkCount(10);
		lo_ABLResultSet	<<la_PartnerCode;
		lo_ABLResultSet	<<la_ShortCode;
		lo_ABLResultSet	<<la_TranslatedNumber;
		while(lo_ABLResultSet.mb_fetch())
		{
			int records = lo_ABLResultSet.mb_getNumArrayRows();
			for(int i = 0; i < records ; i++)
			{
				ls_ErrorMessage="";
				ls_ErrorMessage= "Error came while inserting the following data  in the cache : Partner Code=>";
				ls_ErrorMessage+=la_PartnerCode[i];
				ls_ErrorMessage+=",Short Code=>";
				ls_ErrorMessage+=la_ShortCode[i];
				ls_ErrorMessage+="Translation Number=>";
				ls_ErrorMessage+=la_TranslatedNumber[i];
				p_container->mb_insert((CBase*) new PM_FindPartnerShortCodesCache(la_PartnerCode[i],la_ShortCode[i],la_TranslatedNumber[i]));
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
	*lo_ABLServicePtr<<DEBUG<<"PM_FindPartnerShortCodesCache Loaded"<<Endl;
	return true;
}
