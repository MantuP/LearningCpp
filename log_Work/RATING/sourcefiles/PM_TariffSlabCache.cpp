#include "PM_TariffSlabCache.h"
#include "ABL_Service.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "CHashTable.h"
#include "ABL_Exception.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_TariffSlabCache()
{
	return ( (Base_Registry*) new PM_TariffSlabCache);
}
}
bool PM_TariffSlabCache:: mb_isEqual(CBase* pCBaseptr)
{
        if((unsigned int)(((PM_TariffSlabCache*)pCBaseptr)->mn_TariffId) == (unsigned int)mn_TariffId  && (unsigned int)(((PM_TariffSlabCache*)pCBaseptr)->mn_SlabFrom)<=(unsigned int)mn_SlabFrom && (unsigned int)(((PM_TariffSlabCache*)pCBaseptr)->mn_SlabTo) >=(unsigned int)mn_SlabTo)
	{
			return true;
	}
	else
	{
		return false;
	}

}

PM_TariffSlabCache::PM_TariffSlabCache(const PM_TariffSlabCache& pcopyObject)
{
	this->mn_TariffId						=	pcopyObject.mn_TariffId;
	this->mn_SlabFrom						=	pcopyObject.mn_SlabFrom;
	this->mn_SlabTo							=	pcopyObject.mn_SlabTo;
	this->mn_QtyPerUnit						=	pcopyObject.mn_QtyPerUnit;
	this->mn_AmountPerUnit					=	pcopyObject.mn_AmountPerUnit;
	this->mn_TariffSlabSearchString			=	pcopyObject.mn_TariffSlabSearchString;	
}

unsigned int PM_TariffSlabCache::mb_hash()
{
		return ((unsigned int)mn_TariffId);
}

CBase* PM_TariffSlabCache::mb_createCopy()
{
	return ((CBase*)new PM_TariffSlabCache(*this));
}

bool PM_TariffSlabCache::mb_loadData(data_container *pcontainer, ABL_Service *pABLServiceptr,ABL_String pfilterClause)
{
	ABL_Service *lo_ABLServicePtr = pABLServiceptr;
	ABL_Connection	lo_ABLConnection;
	ABL_Statement	lo_ABLStatement;
	ABL_ResultSet	lo_ABLResultSet;
	ABL_String		ls_query;
	
	double	la_TariffId[10];
	double	la_SlabFrom[10];
	double	la_SlabTo[10];
	double	la_QtyPerUnit[10];
	double	la_AmountPerUnit[10];
	double	la_TariffSlabSearchString[10];

	*lo_ABLServicePtr<<DEBUG<<"Start PM_TariffSlabCache Loading"<<Endl;
	 ABL_String		ls_ErrorMessage="";
	 ABL_String		ls_Tempmessage	="";
	try
	{
		
		lo_ABLConnection.mb_createConnection(*pABLServiceptr);

		ls_query="SELECT COUNT(*) as TotalCount  FROM PM_TARIFF_SLAB";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_fetch();
		pcontainer->mb_resize(lo_ABLResultSet.mb_getInt64(1));
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);
		
		ls_query = "SELECT  NVL(TARIFF_ID, 0 ),NVL(SLAB_FROM, 0),NVL(SLAB_TO, 999999),NVL(QTY_PER_UNIT, 0),NVL(AMOUNT_PER_UNIT, 0),NVL(TO_CHAR(DECODE(SLAB_FROM,1,1,0))||TO_CHAR(TARIFF_ID), ' ') ";
		ls_query +=" FROM PM_TARIFF_SLAB ORDER BY TARIFF_ID,SLAB_FROM";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();		
		lo_ABLResultSet.mb_setBulkCount(10);
		lo_ABLResultSet	<<la_TariffId;
		lo_ABLResultSet	<<la_SlabFrom;
		lo_ABLResultSet	<<la_SlabTo;
		lo_ABLResultSet	<<la_QtyPerUnit;
		lo_ABLResultSet	<<la_AmountPerUnit;
		lo_ABLResultSet	<<la_TariffSlabSearchString;

		while(lo_ABLResultSet.mb_fetch())
		{
			int records = lo_ABLResultSet.mb_getNumArrayRows();
			for(int i = 0; i < records ; i++)
			{
				ls_ErrorMessage="";
				ls_Tempmessage	="";
				ls_Tempmessage.mb_fromDouble(la_TariffId[i]);
				ls_ErrorMessage= "Error came while inserting the following data  in the cache : Tariff ID=>";
				ls_ErrorMessage+=ls_Tempmessage;
				ls_Tempmessage="";
				ls_Tempmessage.mb_fromDouble(la_SlabFrom[i]);
				ls_ErrorMessage+=",From Slab=>";
				ls_ErrorMessage+=ls_Tempmessage;
				ls_Tempmessage="";
				ls_Tempmessage.mb_fromDouble(la_SlabTo[i]);
				ls_ErrorMessage+=",To Slab=>";
				ls_ErrorMessage+=ls_Tempmessage;

				pcontainer->mb_insert((CBase*) new PM_TariffSlabCache(la_TariffId[i], la_SlabFrom[i], la_SlabTo[i],la_QtyPerUnit[i],la_AmountPerUnit[i],la_TariffSlabSearchString[i]));
				//pcontainer->mb_insert((CBase*) new PM_TariffSlabCache(la_TariffId[i],vector<Onj>)
			//ob.la_SlabFrommobj.la_SlabTo,obj.la_QtyPerUnit
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

	*lo_ABLServicePtr<<DEBUG<<"PM_TariffSlabCache Loaded"<<Endl;
	return true;
}

