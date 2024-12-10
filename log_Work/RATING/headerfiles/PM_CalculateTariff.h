#ifndef PM_CalculateTariff_H
#define PM_CalculateTariff_H
#include "ABL_Service.h"
#include "ABL_Exception.h"

#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "PM_Job.h"
#include "ABL_DateTime.h"
#include "ABL_Date.h"
#include "ABL_DbDate.h"


#include "ABL_Process.h"
#include "ABL_String.h"
#include "CHashTable.h"
#include "ABL_CacheManager.h"
#include "PM_Partner_TariffCache.h"
#include "PM_TariffSlabCache.h"
#include <iostream>
#include <math.h>
#include <iomanip>
#include <stdlib.h>
/*#include <sstream>



#include <strstream>*/
using namespace std;

class PM_CalculateTariff : public ABL_Process
{
public:
	PM_CalculateTariff();
	virtual ~PM_CalculateTariff();
	PM_CalculateTariff(const PM_CalculateTariff&);
	virtual Base_Registry* mb_clone();
	virtual ABL_Process* mb_createCopy();
	virtual bool mb_initProcess(ABL_CacheManager* pABLCacheManagerPtr, ABL_AgentCommunicator *pABLAgentCommunicatorPtr, ABL_Service *pABLServicePtr = NULL); 
	virtual bool mb_getCache(ABL_CacheManager* pABLCacheManagerPtr);
	virtual bool mb_process(ABL_Job* &pABLJobPtr);
	virtual bool mb_stop();
	double fnRoundValue(double in_Value,int in_precesion_value);
	long fn_Rev_Power(long Param1,long param2);
protected:
	ABL_Service					*mo_ABLServicePtr;
	data_container*				mo_TariffCacheContainer; 
	data_container*				mo_TariffSlabCacheContainer;	
	ABL_String					ms_Stopsignalfile;
	PM_Partner_TariffCache*		mo_PMTariffCachePtr; 
	PM_TariffSlabCache*			mo_PMTariffSlabCachePtr;
	ABL_String                  Rounding_fac_I;
	ABL_String                  Rounding_fac_R;

};

extern "C" {EXPORT Base_Registry* gb_getPM_CalculateTariff();}

#endif
