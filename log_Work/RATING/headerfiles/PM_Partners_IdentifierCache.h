#ifndef PM_Partners_IdentifierCache_H
#define PM_Partners_IdentifierCache_H

#include "ABL_DataCache.h"
#include "ABL_String.h"
#include "ABL_DateTime.h"
#include "ABL_DbDate.h"
#include "ABL_Date.h"
#include "Base_Registry.h"


class PM_Partners_IdentifierCache : public ABL_DataCache
{
public:
	PM_Partners_IdentifierCache(){}
	PM_Partners_IdentifierCache(ABL_Date pd_Valid_From,ABL_Date pd_Valid_To,ABL_String  ps_AgreementType="",ABL_String ps_TransferType="" ,ABL_String ps_PartnerCode="", ABL_String ps_POICode="",ABL_String ps_TrunkCode="",ABL_String ps_TobeRated="",ABL_String ps_RateZone="",ABL_String ps_NeCode="",ABL_String ps_OperationalDomain="", int  pn_RecordingEntityType = 0,ABL_String ps_AppOwner="",ABL_String ps_AllowIcTraffic="",int  pn_PiLen= 0) : md_Valid_From(pd_Valid_From),md_Valid_To(pd_Valid_To),ms_AgreementType(ps_AgreementType), ms_TransferType(ps_TransferType),ms_PartnerCode(ps_PartnerCode), ms_POICode(ps_POICode), ms_TrunkCode(ps_TrunkCode) , ms_TobeRated(ps_TobeRated), ms_RateZone(ps_RateZone), ms_NeCode(ps_NeCode),  ms_OperationalDomain(ps_OperationalDomain), mn_RecordingEntityType(pn_RecordingEntityType),ms_AppOwner(ps_AppOwner),ms_AllowIcTraffic(ps_AllowIcTraffic),mn_PiLen(pn_PiLen)  {}	
	PM_Partners_IdentifierCache(const PM_Partners_IdentifierCache& p_copyObject);
	virtual ~PM_Partners_IdentifierCache(){}
	virtual Base_Registry* mb_clone() { return ((Base_Registry*) new PM_Partners_IdentifierCache()); }
	virtual long  mb_getSize(ABL_Service *p_ABL_ServicePtr, ABL_String p_filterCaluse) { return 1; }
	bool mb_isEqual(CBase* p_CBase_ptr);
	unsigned int mb_hash();
	CBase* mb_createCopy();
	bool mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause) ; 
	void trim(ABL_String *ls_sIn) ;

	
	void mb_setAgreementType(ABL_String ps_AgreementType) { ms_AgreementType = ps_AgreementType; }
	void mb_setTransferType(ABL_String ps_TransferType) { ms_TransferType = ps_TransferType; }
	void mb_setPartnerCode(ABL_String ps_PartnerCode) { ms_PartnerCode = ps_PartnerCode; }
	void mb_setPOICode(ABL_String ps_POICode) { ms_POICode = ps_POICode; }
	void mb_setTrunkCode(ABL_String ps_TrunkCode) { ms_TrunkCode = ps_TrunkCode; }
	void mb_setTobeRated(ABL_String ps_TobeRated) { ms_TobeRated = ps_TobeRated; }
	void mb_setRateZone(ABL_String ps_RateZone) { ms_RateZone = ps_RateZone; }
	void mb_setNeCode(ABL_String ps_NeCode) { ms_NeCode = ps_NeCode; }
	void mb_setOperationalDomain(ABL_String ps_OperationalDomain){ ms_OperationalDomain = ps_OperationalDomain; }
	void mb_setRecordingEntityType(int pn_RecordingEntityType) { mn_RecordingEntityType = pn_RecordingEntityType; }
	void mb_setAppOwner(ABL_String ps_AppOwner)   { ms_AppOwner = ps_AppOwner; } 
	void mb_setAllowIcTraffic(ABL_String ps_AllowIcTraffic) { ms_AllowIcTraffic = ps_AllowIcTraffic; } 
	void mb_setPiLen(int pn_PiLen) { mn_PiLen = pn_PiLen; }
	void mb_setValid_To(ABL_Date pd_Valid_To) { md_Valid_To = pd_Valid_To; }
	void mb_setValid_From(ABL_Date pd_Valid_From) { md_Valid_From = pd_Valid_From; }
	
	ABL_Date	mb_getValid_From() { return md_Valid_From; }
	ABL_String  mb_getAgreementType() { return ms_AgreementType; }

	ABL_String  mb_getTransferType() { return ms_TransferType; }
	ABL_String  mb_getPartnerCode() { return ms_PartnerCode; }
	ABL_String	mb_getPOICode() { return ms_POICode; }
	ABL_String  mb_getTrunkCode() { return ms_TrunkCode; }
	ABL_String  mb_getTobeRated() { return ms_TobeRated; }
	ABL_String  mb_getRateZone() { return ms_RateZone; }
	ABL_String  mb_getNeCode() { return ms_NeCode; }
	ABL_String  mb_getOperationalDomain() { return ms_OperationalDomain; }
	int			mb_getRecordingEntityType() { return mn_RecordingEntityType; }
	ABL_String  mb_getAppOwner() { return ms_AppOwner; }
	ABL_String  mb_getAllowIcTraffic() { return ms_AllowIcTraffic; }
	int			mb_getPiLen() { return mn_PiLen; }
	ABL_Date	mb_getValid_To() { return md_Valid_To; }

protected:

	ABL_String	ms_AgreementType;
	ABL_String	ms_TransferType;
	ABL_String	ms_POICode; 
	ABL_String  ms_TrunkCode;
	ABL_String  ms_TobeRated;
	ABL_String  ms_RateZone;
	ABL_String  ms_NeCode;
	ABL_String  ms_PartnerCode;
	ABL_String  ms_OperationalDomain;
	int 		mn_RecordingEntityType;
	ABL_String  ms_AppOwner;
	ABL_String  ms_AllowIcTraffic;
	int			mn_PiLen;
	ABL_Date	md_Valid_From ;
	ABL_Date	md_Valid_To ;
};

extern "C" {EXPORT Base_Registry* gb_getPM_Partners_IdentifierCache();}

#endif
