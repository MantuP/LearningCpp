#include "PM_Partners_TariffPlanCache.h"
#include "ABL_Service.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "CHashTable.h"
#include "ABL_Exception.h"
#include "string.h"
#include "stdlib.h"

extern "C" 
{	EXPORT 
	Base_Registry* gb_getPM_Partners_TariffPlanCache()
	{
		return ( (Base_Registry*) new PM_Partners_TariffPlanCache);
	}
}

bool PM_Partners_TariffPlanCache:: mb_isEqual(CBase* pCBaseptr)
{

	if(((PM_Partners_TariffPlanCache*)pCBaseptr)->ms_AgreementType==ms_AgreementType && ((PM_Partners_TariffPlanCache*)pCBaseptr)->ms_TariffPlanType==ms_TariffPlanType  && ((PM_Partners_TariffPlanCache*)pCBaseptr)->ms_PartnerCode==ms_PartnerCode &&((PM_Partners_TariffPlanCache*)pCBaseptr)->md_ValidFrom<=md_ValidFrom &&((PM_Partners_TariffPlanCache*)pCBaseptr)->md_ValidTo>=md_ValidTo)
	{
			return true;
	}
	else
	{
		return false;
	}
	
}

unsigned int PM_Partners_TariffPlanCache::mb_hash()
{

	return(ms_AgreementType.mb_hash()+ms_PartnerCode.mb_hash()+ms_TariffPlanType.mb_hash());
      
}

PM_Partners_TariffPlanCache::PM_Partners_TariffPlanCache(const PM_Partners_TariffPlanCache& pcopyObject)
{
	this->ms_TariffPlanCode		=	pcopyObject.ms_TariffPlanCode;
	this->ms_TariffPlanType		=	pcopyObject.ms_TariffPlanType;
	this->ms_AgreementType		=	pcopyObject.ms_AgreementType;
	this->ms_PartnerCode		=	pcopyObject.ms_PartnerCode;
	this->md_ValidFrom			=	pcopyObject.md_ValidFrom;
	this->md_ValidTo			=	pcopyObject.md_ValidTo;
}

CBase* PM_Partners_TariffPlanCache::mb_createCopy()
{
	return ((CBase*)new PM_Partners_TariffPlanCache(*this));
}

bool PM_Partners_TariffPlanCache::mb_loadData(data_container *pcontainer, ABL_Service *pABLServiceptr,ABL_String pfilterClause)
{
	ABL_Service *lo_ABLServicePtr = pABLServiceptr;

	ABL_DbDate	la_ValidFrom[10];
	ABL_DbDate	la_ValidTo[10];
	ABL_String	la_TariffPlanCode[10];
	ABL_String	la_TariffPlanType[10];
	ABL_String	la_AgreementType[10];
	ABL_String	la_PartnerCode[10];

	ABL_Connection  lo_ABLConnection;
	ABL_Statement   lo_ABLStatement;
	ABL_ResultSet   lo_ABLResultSet;
	ABL_String		ls_query;

	*lo_ABLServicePtr<<DEBUG<<"Start PM_Partners_TariffPlanCache Loading"<<Endl;
	 ABL_String		ls_ErrorMessage="";

	try
	{
		

		lo_ABLConnection.mb_createConnection(*pABLServiceptr);

		ls_query="SELECT COUNT(*) as TotalCount  FROM PM_TARIFF_PLAN a, PM_PARTNER_TARIFF_PLAN b	WHERE a.TARIFF_PLAN_CODE = b.TARIFF_PLAN_CODE";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_fetch();
		pcontainer->mb_resize(lo_ABLResultSet.mb_getInt64(1));
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);

		ls_query ="SELECT  b.VALID_FROM , b.VALID_TO ,NVL(a.TARIFF_PLAN_CODE, ' '),NVL(a.TARIFF_PLAN_TYPE, ' '),NVL(a.AGREEMENT_TYPE, ' '),NVL(b.PARTNER_CODE, ' ') ";
		ls_query+="FROM PM_TARIFF_PLAN a, PM_PARTNER_TARIFF_PLAN b	WHERE a.TARIFF_PLAN_CODE = b.TARIFF_PLAN_CODE ORDER BY a.AGREEMENT_TYPE,a.TARIFF_PLAN_TYPE,b.PARTNER_CODE";
		
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();		
		lo_ABLResultSet.mb_setBulkCount(10);

		lo_ABLResultSet	<<la_ValidFrom;
		lo_ABLResultSet	<<la_ValidTo;
		lo_ABLResultSet	<<la_TariffPlanCode;
		lo_ABLResultSet	<<la_TariffPlanType;
		lo_ABLResultSet	<<la_AgreementType;
		lo_ABLResultSet	<<la_PartnerCode;
		
		while(lo_ABLResultSet.mb_fetch())
		{
			int records = lo_ABLResultSet.mb_getNumArrayRows();
			for(int i = 0; i < records ; i++)
			{
				ls_ErrorMessage="";
				ls_ErrorMessage= "Error came while inserting the following data  in the cache : Partner Code=>";
				ls_ErrorMessage+=la_PartnerCode[i];
				ls_ErrorMessage+=",Tariff Plan Type=>";
				ls_ErrorMessage+=la_TariffPlanType[i];
				ls_ErrorMessage+=",Agreement type=>";
				ls_ErrorMessage+=la_AgreementType[i];
				ls_ErrorMessage+=",Valid from date=>";
				ls_ErrorMessage+=la_ValidFrom[i].mb_toString();
				ls_ErrorMessage+=",Valid to date=>";
				ls_ErrorMessage+=la_ValidTo[i].mb_toString();

				pcontainer->mb_insert((CBase*) new PM_Partners_TariffPlanCache(la_ValidFrom[i],la_ValidTo[i],la_TariffPlanCode[i],la_TariffPlanType[i],la_AgreementType[i],la_PartnerCode[i]));
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

	*lo_ABLServicePtr<<DEBUG<<"PM_Partners_TariffPlanCache Loaded"<<Endl;
	return true;
}
