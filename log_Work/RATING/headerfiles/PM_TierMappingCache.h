#ifndef PM_TierMappingCache_H
#define PM_TierMappingCache_H

#include "ABL_DataCache.h"
#include "ABL_String.h"
#include "ABL_DateTime.h"
#include "ABL_DbDate.h"
#include "ABL_Date.h"
#include "Base_Registry.h"

class PM_TierMappingCache : public ABL_DataCache
{
public:
	//added TrafficType to constructor for LTE usage for 4.3 release
	PM_TierMappingCache(ABL_String ps_OriginZone = "" ,ABL_String ps_DestinationZone = "",ABL_String ps_PartnerCode = "",ABL_String ps_Tier = ""): ms_OriginZone(ps_OriginZone),ms_DestinationZone(ps_DestinationZone),ms_PartnerCode(ps_PartnerCode),ms_Tier(ps_Tier){}
	//modification end
	PM_TierMappingCache(const PM_TierMappingCache& p_copyObject);
	virtual ~PM_TierMappingCache(){}
	virtual Base_Registry* mb_clone() { return ((Base_Registry*) new PM_TierMappingCache()); }
	virtual long  mb_getSize(ABL_Service *p_ABL_ServicePtr, ABL_String p_filterCaluse) { return 1; }
	bool mb_isEqual(CBase* p_CBase_ptr);

	unsigned int mb_hash();/*{ return m_Destination.mb_hash(); }	*/
	CBase* mb_createCopy();

	bool mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause) ; 	
	void trim(ABL_String *ls_sIn) ;

	void mb_setOriginZone(ABL_String ps_OriginZone) { ms_OriginZone = ps_OriginZone; }
	void mb_setDestinationZone(ABL_String ps_DestinationZone) { ms_DestinationZone = ps_DestinationZone; }
	void mb_setPartnerCode(ABL_String ps_PartnerCode) { ms_PartnerCode = ps_PartnerCode; }
	void mb_setTier(ABL_String ps_Tier) { ms_Tier = ps_Tier; }
	//modification end


	ABL_String		mb_getOriginZone() { return ms_OriginZone; }
	ABL_String		mb_getDestinationZone() { return ms_DestinationZone;}
	ABL_String		mb_getPartnerCode() { return ms_PartnerCode;}	
	ABL_String		mb_getTier() { return ms_Tier;}
	//modification end
	
protected:	
	
	ABL_String		ms_OriginZone;
	ABL_String		ms_DestinationZone;	
	ABL_String		ms_PartnerCode;
	ABL_String		ms_Tier;
	
	//modification end
	
};

extern "C" {EXPORT Base_Registry* gb_getPM_TierMappingCache();}

#endif
