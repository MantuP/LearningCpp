#ifndef PM_DestinationCache_H
#define PM_DestinationCache_H

#include "ABL_DataCache.h"
#include "ABL_String.h"
#include "ABL_DateTime.h"
#include "ABL_DbDate.h"
#include "ABL_Date.h"
#include "Base_Registry.h"

class PM_DestinationCache : public ABL_DataCache
{
public:
	//added TrafficType to constructor for LTE usage for 4.3 release
	PM_DestinationCache(ABL_DateTime pd_Valid_From,ABL_DateTime pd_Valid_To,ABL_String ps_Destination ,ABL_String ps_DestinationType,ABL_String ps_NumberPlanCode,ABL_String ps_RateZone = "",ABL_String ps_DestinationSubType = "", ABL_String ps_Poi = "", ABL_String ps_Calltypelevel3 = "",ABL_String ps_TrafficType = "",ABL_String ps_ZoneGroup = "",ABL_String ps_PrefixType = ""): md_Valid_From(pd_Valid_From),md_Valid_To(pd_Valid_To),ms_Destination(ps_Destination),ms_DestinationType(ps_DestinationType), ms_NumberPlanCode(ps_NumberPlanCode),ms_RateZone(ps_RateZone), ms_DestinationSubType(ps_DestinationSubType), ms_Poi(ps_Poi), ms_Calltypelevel3(ps_Calltypelevel3), ms_TrafficType(ps_TrafficType), ms_ZoneGroup(ps_ZoneGroup), ms_PrefixType(ps_PrefixType)  {}
	//modification end
	PM_DestinationCache(){}
	PM_DestinationCache(const PM_DestinationCache& p_copyObject);
	virtual ~PM_DestinationCache(){}
	virtual Base_Registry* mb_clone() { return ((Base_Registry*) new PM_DestinationCache()); }
	virtual long  mb_getSize(ABL_Service *p_ABL_ServicePtr, ABL_String p_filterCaluse) { return 1; }
	bool mb_isEqual(CBase* p_CBase_ptr);

	unsigned int mb_hash();/*{ return m_Destination.mb_hash(); }	*/
	CBase* mb_createCopy();

	bool mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause) ; 	
	void trim(ABL_String *ls_sIn) ;

	void mb_setDestination(ABL_String ps_Destination) { ms_Destination = ps_Destination; }
	void mb_setDestinationType(ABL_String ps_DestinationType) { ms_DestinationType = ps_DestinationType; }
	void mb_setRateZone(ABL_String ps_RateZone) { ms_RateZone = ps_RateZone; }
	void mb_setNumberPlanCode(ABL_String ps_NumberPlanCode) { ms_NumberPlanCode = ps_NumberPlanCode; }
	void mb_setDestinationSubType(ABL_String ps_DestinationSubType) { ms_DestinationSubType = ps_DestinationSubType; }
	void mb_setCalltypelevel3(ABL_String ps_Calltypelevel3) { ms_Calltypelevel3 = ps_Calltypelevel3; }
	void mb_setValid_From(ABL_DateTime pd_Valid_From) { md_Valid_From = pd_Valid_From; }
	void mb_setValid_To(ABL_DateTime pd_Valid_To) { md_Valid_To = pd_Valid_To; }
	void mb_setPoi(ABL_String		ps_Poi){ms_Poi = ps_Poi;}
	//added as per LTE usage for 4.3 release
	void mb_setTrafficType(ABL_String ps_TrafficType){ms_TrafficType = ps_TrafficType;}
	void mb_setZoneGroup(ABL_String ps_ZoneGroup){ms_ZoneGroup = ps_ZoneGroup;}
	void mb_setPrefixType(ABL_String ps_PrefixType){ms_TrafficType = ps_PrefixType;}
	//modification end


	ABL_String		mb_getDestination() { return ms_Destination; }
	ABL_String		mb_getDestinationType() { return ms_DestinationType;}
	ABL_String		mb_getRateZone() { return ms_RateZone;}	
	ABL_String		mb_getNumberPlanCode() { return ms_NumberPlanCode;}
	ABL_String		mb_getDestinationSubType() { return ms_DestinationSubType;}
	ABL_String		mb_getPoi() { return ms_Poi;}
	ABL_String		mb_getCalltypelevel3() { return ms_Calltypelevel3;}
	ABL_DateTime	mb_getValid_From() { return md_Valid_From; }
	ABL_DateTime	mb_getValid_To() { return md_Valid_To; }
	//added as per LTE usage for 4.3 release
	ABL_String	mb_getTrafficType(){ return ms_TrafficType; }
	ABL_String	mb_getZoneGroup(){ return ms_ZoneGroup; }
	ABL_String	mb_getPrefixType(){ return ms_PrefixType; }
	//modification end
	
protected:	
	
	ABL_String		ms_Destination;
	ABL_String		ms_DestinationType;	
	ABL_String		ms_RateZone;
	ABL_String		ms_NumberPlanCode;
	ABL_String		ms_DestinationSubType;
	ABL_String		ms_Poi;
	ABL_DateTime	md_Valid_From ;
	ABL_DateTime	md_Valid_To ;
	ABL_String		ms_Calltypelevel3;
	//added as per LTE usage 4.3 release
	ABL_String 	ms_TrafficType;
    ABL_String 	ms_ZoneGroup;
	ABL_String 	ms_PrefixType;
	//modification end
	
};

extern "C" {EXPORT Base_Registry* gb_getPM_DestinationCache();}

#endif
