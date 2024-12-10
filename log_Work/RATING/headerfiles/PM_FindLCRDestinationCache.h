#ifndef PM_FindLCRDestinationCache_H
#define PM_FindLCRDestinationCache_H

#include "ABL_DataCache.h"
#include "ABL_String.h"
#include "ABL_Date.h"
#include "ABL_DateTime.h"
#include "ABL_DbDate.h"
#include "Base_Registry.h"


class PM_FindLCRDestinationCache : public ABL_DataCache
{
public:
	PM_FindLCRDestinationCache(ABL_String p_stLCR_destination="") :  ms_LCR_destination(p_stLCR_destination) {}
	PM_FindLCRDestinationCache(const PM_FindLCRDestinationCache& p_copyObject);
	virtual ~PM_FindLCRDestinationCache(){}
	virtual Base_Registry* mb_clone() { return ((Base_Registry*) new PM_FindLCRDestinationCache()); }
	virtual long  mb_getSize(ABL_Service *p_ABL_ServicePtr, ABL_String p_filterCaluse) { return 1; }
	bool mb_isEqual(CBase* p_CBase_ptr);
	unsigned int mb_hash(){ return ms_LCR_destination.mb_hash(); }
	CBase* mb_createCopy();
	bool mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause) ; 	
	void trim(ABL_String *ls_sIn) ;

	void mb_setLCRDestination(ABL_String p_stLCR_destination) { ms_LCR_destination = p_stLCR_destination; }
	ABL_String  mb_getLCRDestination() { return ms_LCR_destination; }
	
	
protected:
	ABL_String		ms_LCR_destination;
	
};

extern "C" {EXPORT Base_Registry* gb_getPM_FindLCRDestinationCache();}

#endif
