#ifndef PM_FindRecordingentityTypeCache_H
#define PM_FindRecordingentityTypeCache_H

#include "ABL_DataCache.h"
#include "ABL_String.h"
#include "ABL_Date.h"
#include "ABL_DateTime.h"
#include "ABL_DbDate.h"
#include "Base_Registry.h"


class PM_FindRecordingentityTypeCache : public ABL_DataCache
{
public:
	PM_FindRecordingentityTypeCache(){}
	PM_FindRecordingentityTypeCache(ABL_String p_stRecordingEntityDesc,unsigned int p_stRecoringEntityType) :  ms_RecordingEntityDesc(p_stRecordingEntityDesc),mn_RecoringEntityType(p_stRecoringEntityType) {}
	PM_FindRecordingentityTypeCache(const PM_FindRecordingentityTypeCache& p_copyObject);
	virtual ~PM_FindRecordingentityTypeCache(){}
	virtual Base_Registry* mb_clone() { return ((Base_Registry*) new PM_FindRecordingentityTypeCache()); }
	virtual long  mb_getSize(ABL_Service *p_ABL_ServicePtr, ABL_String p_filterCaluse) { return 1; }
	bool mb_isEqual(CBase* p_CBase_ptr);
	unsigned int mb_hash();
	CBase* mb_createCopy();
	bool mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause) ; 	
	void trim(ABL_String *ls_sIn) ;

	void mb_setRecordingEntityDesc(ABL_String p_stRecordingEntityDesc) { ms_RecordingEntityDesc = p_stRecordingEntityDesc; }
	ABL_String  mb_getRecordingEntityDesc() { return ms_RecordingEntityDesc; }

	void mb_setRecoringEntityType(unsigned int p_stRecoringEntityType) { mn_RecoringEntityType = p_stRecoringEntityType; }
	unsigned int  mb_getRecoringEntityType() { return mn_RecoringEntityType; }
	
	
protected:
	ABL_String		ms_RecordingEntityDesc;
	unsigned int	mn_RecoringEntityType;
	
};

extern "C" {EXPORT Base_Registry* gb_getPM_FindRecordingentityTypeCache();}

#endif
