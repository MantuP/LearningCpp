#ifndef PM_ApplyRatingRules_H
#define PM_ApplyRatingRules_H

#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "PM_Job.h"

#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "ABL_DateTime.h"
#include "ABL_Date.h"
#include "ABL_DbDate.h"
#include "string.h"
#include "sstream"
#include "vector"
#include "iostream"
#include "stdio.h"
#include <stdlib.h>
#include "ABL_Process.h"
#include "ABL_String.h"
#include "CHashTable.h"
#include "ABL_CacheManager.h"
#include "PM_RatingRulesCache.h"


class PM_RatingRulesCache;
class PM_ApplyRatingRules : public ABL_Process
{
public:
	PM_ApplyRatingRules();
	virtual ~PM_ApplyRatingRules();
	PM_ApplyRatingRules(const PM_ApplyRatingRules&);
	virtual Base_Registry* mb_clone();
	virtual ABL_Process* mb_createCopy();
    virtual bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr = NULL);     
	virtual bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
	virtual bool mb_process(ABL_Job* &p_ABL_JobPtr);
	void update_CallTypeCounts(PM_Job * &p_ABL_JobPtr, ABL_String AgreementType, int CallType, double CallDuration, ABL_String CallDirection);
	void update_CallTypeCountsTot(PM_Job * &p_ABL_JobPtr, ABL_String AgreementType, int CallType, double CallDuration);
	void update_ATypeRatingLog(PM_Job * &p_ABL_JobPtr, ABL_String AgreementType);
	virtual bool mb_stop();	
	void mb_trim(std::string &p_string);
	int GetFrom_Pos( ABL_String str,int nthoccurence );
	int GetTo_Pos( ABL_String str,int nthoccurence );

protected:

		PM_RatingRulesCache  *mo_ApplyRatingRulesCachePtr;
		ABL_Service					*mo_ABLServicePtr;
		data_container              *mo_ApplyRatingRulescacheContainer;
		ABL_String                  ms_Stopsignalfile;
		std::vector<gr_ControlParams>ma_ControlParams;
		std::vector<gr_AgreementType>ma_AgreementType;
		std::vector<int>ma_CallType;     

};

extern "C" {EXPORT Base_Registry* gb_getPM_ApplyRatingRules();}

#endif
