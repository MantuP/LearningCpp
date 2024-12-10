#include "PM_Partners_IdentifierCache.h"
#include "ABL_Service.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "CHashTable.h"
#include "ABL_Exception.h"
#include "ABL_Date.h"


extern "C" {EXPORT 
Base_Registry* gb_getPM_Partners_IdentifierCache()
{
	return ( (Base_Registry*) new PM_Partners_IdentifierCache);}
}
bool PM_Partners_IdentifierCache::mb_isEqual(CBase* p_CBase_ptr)
{ 
	try
	{
		//if(((PM_Partners_IdentifierCache*)p_CBase_ptr)->ms_AgreementType == ms_AgreementType  &&  ((PM_Partners_IdentifierCache*)p_CBase_ptr)->ms_TransferType == ms_TransferType && ((PM_Partners_IdentifierCache*)p_CBase_ptr)->ms_NeCode == ms_NeCode && ((PM_Partners_IdentifierCache*)p_CBase_ptr)->ms_TrunkCode == ms_TrunkCode.mb_subStr(0,((PM_Partners_IdentifierCache*)p_CBase_ptr)->mn_PiLen)  && (((PM_Partners_IdentifierCache*)p_CBase_ptr)->md_Valid_From <= md_Valid_From) && (((PM_Partners_IdentifierCache*)p_CBase_ptr)->md_Valid_To >= md_Valid_To) )
		if(((PM_Partners_IdentifierCache*)p_CBase_ptr)->ms_AgreementType == ms_AgreementType  && ((PM_Partners_IdentifierCache*)p_CBase_ptr)->ms_TransferType == ms_TransferType && ((PM_Partners_IdentifierCache*)p_CBase_ptr)->ms_NeCode == ms_NeCode && ((PM_Partners_IdentifierCache*)p_CBase_ptr)->ms_TrunkCode == ms_TrunkCode && (((PM_Partners_IdentifierCache*)p_CBase_ptr)->md_Valid_From <= md_Valid_From) && (((PM_Partners_IdentifierCache*)p_CBase_ptr)->md_Valid_To >= md_Valid_To) )
		{
			
				return true;
		}
		else
		{
			return false;
		}
	}
	catch (...)
	{
		std::cout<<"Exception has occured  while searching the interconnect partner in chacne."<<std::endl;
	}
}


PM_Partners_IdentifierCache::PM_Partners_IdentifierCache(const PM_Partners_IdentifierCache& p_copyObject)
{
	this->ms_AgreementType			=	p_copyObject.ms_AgreementType;	
	this->ms_TransferType			=	p_copyObject.ms_TransferType;
	this->ms_POICode				=	p_copyObject.ms_POICode;
	this->ms_TrunkCode				=	p_copyObject.ms_TrunkCode;
	this->ms_TobeRated				=	p_copyObject.ms_TobeRated;
	this->ms_RateZone				=	p_copyObject.ms_RateZone;
	this->ms_NeCode					=	p_copyObject.ms_NeCode;
	this->ms_PartnerCode			=	p_copyObject.ms_PartnerCode;
	this->ms_OperationalDomain		=   p_copyObject.ms_OperationalDomain;
	this->mn_RecordingEntityType	=	p_copyObject.mn_RecordingEntityType;	
	this->ms_AppOwner				=	p_copyObject.ms_AppOwner;
	this->ms_AllowIcTraffic			=	p_copyObject.ms_AllowIcTraffic;
	this->mn_PiLen					=	p_copyObject.mn_PiLen;	
	this->md_Valid_From				=	p_copyObject.md_Valid_From;
	this->md_Valid_To				=	p_copyObject.md_Valid_To;
}

unsigned int PM_Partners_IdentifierCache::mb_hash()
{

	return(ms_TrunkCode.mb_hash() * 10 + ms_TransferType.mb_hash() * 20 +ms_AgreementType.mb_hash()*30+ms_NeCode.mb_hash()*40);
}

CBase* PM_Partners_IdentifierCache::mb_createCopy()
{
	return ((CBase*)new PM_Partners_IdentifierCache(*this));
}

bool PM_Partners_IdentifierCache::mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause)
{
	ABL_Service *lo_ABLServicePtr = p_ABL_Service_ptr;	
	ABL_String		ls_query;
	ABL_Statement   lo_ABLStatement;
	ABL_Connection  lo_ABLConnection;
	ABL_ResultSet   lo_ABLResultSet;

	ABL_DbDate	la_Valid_From[10];
	ABL_DbDate	la_Valid_To[10];
	ABL_String	la_AgreementType[10];
	ABL_String	la_TransferType[10];
	ABL_String	la_POICode[10];
	ABL_String	la_TrunkCode[10];
	ABL_String	la_TobeRated[10];
	ABL_String	la_RateZone[10];
	ABL_String	la_NeCode[10];
	ABL_String	la_PartnerCode[10];
	ABL_String	la_OperationalDomain[10];
	int         la_RecordingEntityType[10];
	ABL_String	la_AppOwner[10];
	ABL_String	la_AllowIcTraffic[10];
	int         la_PiLen[110];
	*lo_ABLServicePtr<<DEBUG<<"Start PM_Partners_IdentifierCache Loading"<<Endl;
	ABL_String		ls_ErrorMessage="";
	try
	{
		
		lo_ABLConnection.mb_createConnection(*p_ABL_Service_ptr);

		ls_query="SELECT COUNT(*) as TotalCount  FROM PM_PARTNER_IDENTIFIER I,PM_PARTNER P WHERE I.PARTNER_CODE = P.PARTNER_CODE  AND P.AGREEMENT_TYPE IN ('I','V')";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
		lo_ABLResultSet.mb_fetch();
		p_container->mb_resize(lo_ABLResultSet.mb_getInt64(1));
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);

		ls_query ="SELECT I.VALID_FROM , I.VALID_TO,NVL(P.AGREEMENT_TYPE,' '),NVL(I.TRANSFER_TYPE,' '),NVL (I.PARTNER_CODE, ' '),NVL (I.POI_CODE, ' '),NVL(I.TRUNK_CODE,' '),NVL (I.TOBE_RATED, ' '),NVL (I.RATE_ZONE, ' '),NVL(I.NE_CODE,' '), ";
		ls_query+="nvl(p.operational_domain,'N') OperationalDomain,NVL((select recording_entity_type from pm_recording_entities a where a.recording_entity_desc = i.ne_code),0)as recording_entity_type, " ;  
		ls_query+="nvl(p.app_owner,' '),nvl(i.allow_ic_traffic,' '), LENGTH(i.trunk_code) Pi_Len " ;  
		ls_query+=" FROM PM_PARTNER_IDENTIFIER I,PM_PARTNER P WHERE I.PARTNER_CODE = P.PARTNER_CODE  AND P.AGREEMENT_TYPE IN('I','V') ORDER BY 3 desc ";
	
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_query);	
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();	
		lo_ABLResultSet.mb_setBulkCount(10);
		lo_ABLResultSet	<<la_Valid_From;
		lo_ABLResultSet	<<la_Valid_To;
		lo_ABLResultSet	<<la_AgreementType;
		lo_ABLResultSet	<<la_TransferType;
		lo_ABLResultSet	<<la_PartnerCode;
		lo_ABLResultSet	<<la_POICode;
		lo_ABLResultSet	<<la_TrunkCode;
		lo_ABLResultSet	<<la_TobeRated;
		lo_ABLResultSet	<<la_RateZone;
		lo_ABLResultSet	<<la_NeCode;
		lo_ABLResultSet	<<la_OperationalDomain;
		lo_ABLResultSet	<<la_RecordingEntityType;	
		lo_ABLResultSet	<<la_AppOwner;	
		lo_ABLResultSet	<<la_AllowIcTraffic;	
		lo_ABLResultSet	<<la_PiLen;	
		while(lo_ABLResultSet.mb_fetch())
		{

			int records = lo_ABLResultSet.mb_getNumArrayRows();
			for(int i = 0; i < records ; i++)
			{
		
				ls_ErrorMessage="";
				ls_ErrorMessage= "Error came while inserting the following data  in the cache : Agreement Type=>";
				ls_ErrorMessage+=la_AgreementType[i];
				ls_ErrorMessage+=",Transfer Type=>";
				ls_ErrorMessage+=la_TransferType[i];
				ls_ErrorMessage+=",Poi=>";
				ls_ErrorMessage+=la_POICode[i];
				ls_ErrorMessage+=",Trunk Code=>";
				ls_ErrorMessage+=la_TrunkCode[i];
				ls_ErrorMessage+=",NE  Code=>";
				ls_ErrorMessage+=la_NeCode[i];

				ls_ErrorMessage+=",Valid from date=>";
				ls_ErrorMessage+=la_Valid_From[i].mb_toString();
				ls_ErrorMessage+=",Valid to date=>";
				ls_ErrorMessage+=la_Valid_To[i].mb_toString();

				//trim(&la_AgreementType[i]);
				//trim(&la_TransferType[i]);
				//trim(&la_PartnerCode[i]);
				trim(&la_POICode[i]);
				//trim(&la_TrunkCode[i]);
				//trim(&la_TobeRated[i]);
				//trim(&la_RateZone[i]);
				//trim(&la_NeCode[i]);
				//trim(&la_OperationalDomain[i]);
				//la_RecordingEntityType[i];
				//trim(&la_AppOwner[i]);
				//trim(&la_AllowIcTraffic[i]);

				p_container->mb_insert((CBase*) new PM_Partners_IdentifierCache(la_Valid_From[i],la_Valid_To[i],la_AgreementType[i],la_TransferType[i],la_PartnerCode[i],la_POICode[i],la_TrunkCode[i],la_TobeRated[i],la_RateZone[i],la_NeCode[i],la_OperationalDomain[i],la_RecordingEntityType[i],la_AppOwner[i],la_AllowIcTraffic[i],la_PiLen[i]));					
		
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
	*lo_ABLServicePtr<<DEBUG<<"PM_Partners_IdentifierCache Loaded"<<Endl;
	return true;
}
/* Fuction to remove leading and trailing spaces in a string.*/
/*Fuction to remove the leading n trailing spaces in a string.*/
void PM_Partners_IdentifierCache::trim(ABL_String *ls_sIn) 
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
