#include "PM_Find_NumberPlanCache.h"
#include "ABL_Service.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "CHashTable.h"
#include "ABL_Exception.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_Find_NumberPlanCache()
{
	return ( (Base_Registry*) new PM_Find_NumberPlanCache);
}
}

bool PM_Find_NumberPlanCache:: mb_isEqual(CBase* p_CBase_ptr)
{


	//std::cout<<"@Number plan cache: "<<" number plan type: "<<ms_NumberPlanType<<" Agreement type : "<<ms_AgreementType<< " Partner Code: "<<ms_PartnerCode<<" POI: "<<ms_POI<<std::endl;
	
	if(((PM_Find_NumberPlanCache*)p_CBase_ptr)->ms_NumberPlanType == ms_NumberPlanType  && ((PM_Find_NumberPlanCache*)p_CBase_ptr)->ms_PartnerCode == ms_PartnerCode  && ((PM_Find_NumberPlanCache*)p_CBase_ptr)->ms_AgreementType == ms_AgreementType   && (((PM_Find_NumberPlanCache*)p_CBase_ptr)->ms_POI == ms_POI || ((PM_Find_NumberPlanCache*)p_CBase_ptr)->ms_POI=="")&& (((PM_Find_NumberPlanCache*)p_CBase_ptr)->md_Valid_From <= md_Valid_From)  && (((PM_Find_NumberPlanCache*)p_CBase_ptr)->md_Valid_To >= md_Valid_To) )
	{
		return true;
	}
	else
	{
		return false;
	}
		
	
}

PM_Find_NumberPlanCache::PM_Find_NumberPlanCache(const PM_Find_NumberPlanCache& p_copyObject)
{
	this->ms_NumberPlanCode			=	p_copyObject.ms_NumberPlanCode;
	this->ms_NumberPlanType			=	p_copyObject.ms_NumberPlanType;
	this->ms_AgreementType			=	p_copyObject.ms_AgreementType;
	this->ms_PartnerCode			=	p_copyObject.ms_PartnerCode;
	this->ms_POI			        =   p_copyObject.ms_POI;
	this->ms_BrokerCountryCode		=	p_copyObject.ms_BrokerCountryCode;
	this->md_Valid_From				=	p_copyObject.md_Valid_From;
	this->md_Valid_To				=   p_copyObject.md_Valid_To;

}

unsigned int PM_Find_NumberPlanCache:: mb_hash()
{
    return(ms_NumberPlanType.mb_hash() * 10 + ms_PartnerCode.mb_hash() * 20 + ms_AgreementType.mb_hash() * 30);
}



CBase* PM_Find_NumberPlanCache::mb_createCopy()
{
	return ((CBase*)new PM_Find_NumberPlanCache(*this));
}

bool PM_Find_NumberPlanCache::mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause)
{
	ABL_Service *lo_ABLServicePtr = p_ABL_Service_ptr;
	ABL_String			ls_query;
	ABL_Connection		lo_ABLConnection;
	ABL_Statement		lo_ABLStatement;
	ABL_ResultSet		lo_ABLResultSet;
	ABL_DbDate			la_Valid_From[10];
	ABL_DbDate			la_Valid_To[10];
	ABL_String			la_NumberPlanCode[10];
	ABL_String			la_NumberPlanType[10];
	ABL_String			la_AgreementType[10];
	ABL_String			la_PartnerCode[10];
	ABL_String			la_POI[10];	
	ABL_String			la_BrokerCountryCode[10];
	*lo_ABLServicePtr<<DEBUG<<"Start PM_Find_NumberPlanCache Loading"<<Endl;
	 ABL_String		ls_ErrorMessage="";
	try
	{
		
		lo_ABLConnection.mb_createConnection(*p_ABL_Service_ptr);
		ls_query="SELECT COUNT(*) as TotalCount  FROM PM_NUMBER_PLAN a, PM_PARTNER_NUMBER_PLAN b	WHERE a.NUMBER_PLAN_CODE = b.NUMBER_PLAN_CODE ";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_fetch();
		p_container->mb_resize(lo_ABLResultSet.mb_getInt64(1));
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);
		
		ls_query ="SELECT b.valid_from, b.valid_till,NVL(a.NUMBER_PLAN_CODE, ' '),NVL(a.NUMBER_PLAN_TYPE, ' '),NVL(a.AGREEMENT_TYPE, ' '),NVL(b.PARTNER_CODE, ' '),NVL(b.POI, ' '),nvl( a.BROKER_COUNTRY_CODE,' ') " ;
		ls_query +="	FROM PM_NUMBER_PLAN a, PM_PARTNER_NUMBER_PLAN b	WHERE a.NUMBER_PLAN_CODE = b.NUMBER_PLAN_CODE 	ORDER BY a.AGREEMENT_TYPE,a.NUMBER_PLAN_TYPE,b.PARTNER_CODE,b.POI";
				
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();		
		lo_ABLResultSet.mb_setBulkCount(10);
		lo_ABLResultSet	<<la_Valid_From;
		lo_ABLResultSet	<<la_Valid_To;
		lo_ABLResultSet	<<la_NumberPlanCode;
		lo_ABLResultSet	<<la_NumberPlanType;
		lo_ABLResultSet	<<la_AgreementType;
		lo_ABLResultSet	<<la_PartnerCode;
		lo_ABLResultSet	<<la_POI;
		lo_ABLResultSet	<<la_BrokerCountryCode;
		while(lo_ABLResultSet.mb_fetch())
		{
			int records = lo_ABLResultSet.mb_getNumArrayRows();
			for(int i = 0; i < records ; i++)
			{
				
				ls_ErrorMessage="";
				ls_ErrorMessage= "Error came while inserting the following data  in the cache : Partner Code=>";
				ls_ErrorMessage+=la_PartnerCode[i];
				ls_ErrorMessage+=",Number Plan Type=>";
				ls_ErrorMessage+=la_NumberPlanType[i];
				ls_ErrorMessage+=",Agreement type=>";
				ls_ErrorMessage+=la_AgreementType[i];
				ls_ErrorMessage+=",Poi=>";
				ls_ErrorMessage+=la_POI[i];
				ls_ErrorMessage+=",Valid from date=>";
				ls_ErrorMessage+=la_Valid_From[i].mb_toString();
				ls_ErrorMessage+=",Valid to date=>";
				ls_ErrorMessage+=la_Valid_To[i].mb_toString();

				trim(&la_NumberPlanCode[i]);
				trim(&la_NumberPlanType[i]);
				trim(&la_AgreementType[i]);
				trim(&la_PartnerCode[i]);
				trim(&la_POI[i]);
				trim(&la_BrokerCountryCode[i]);

				p_container->mb_insert((CBase*) new PM_Find_NumberPlanCache(la_Valid_From[i],la_Valid_To[i],la_NumberPlanCode[i],la_NumberPlanType[i],la_AgreementType[i],la_PartnerCode[i],la_POI[i],la_BrokerCountryCode[i]));
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
	*lo_ABLServicePtr<<DEBUG<<"PM_Find_NumberPlanCache Loaded successfully"<<Endl;
	return true;
}
/* Fuction to remove leading and trailing spaces in a string.*/
/*Fuction to remove the leading n trailing spaces in a string.*/
void PM_Find_NumberPlanCache::trim(ABL_String *ls_sIn) 
 {
	int i, ln_start = -1, ln_end = -1;
	int ln_isFullblank;
	ln_isFullblank=0;
	ABL_String ls_sIn_temp;
	ABL_String ls_sIn_tp;
	ls_sIn_temp=*ls_sIn;
	ls_sIn_tp=*ls_sIn;
	for(i = 0; i < ls_sIn_tp.mb_length(); i++) 
	{
		if(ls_sIn_tp[i] == ' ')
		{
			 ln_start = i;
			 ln_isFullblank=ln_isFullblank+1;
		}
		else 
		{
			ls_sIn_tp = ls_sIn_tp.mb_subStr(i, ls_sIn_tp.mb_length() - i);
			break;
		}
	}

	for(i = ls_sIn_tp.mb_length()-1; i >= 0; i--)
	{
		if(ls_sIn_tp[i] == ' ')
		ln_end = i;
		else
		{
			ls_sIn_tp = ls_sIn_tp.mb_subStr(0, i+1);
			break;
		}
	}
	if(ln_isFullblank==ls_sIn_temp.mb_length())
	{
		ls_sIn_tp="";
	}
	*ls_sIn=ls_sIn_tp;	
}
