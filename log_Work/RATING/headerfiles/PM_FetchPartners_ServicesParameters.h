#ifndef PM_FetchPartners_ServicesParameters_H
#define PM_FetchPartners_ServicesParameters_H

//#include <tchar.h>
#include "PM_Job.h"
#include "ABL_Process.h"
#include "ABL_String.h"
#include "CHashTable.h"
#include "ABL_CacheManager.h"
#include "PM_FetchPartners_ServicesParametersCache.h"
#include <stdlib.h>

class PM_FetchPartners_ServicesParametersCache;


class PM_FetchPartners_ServicesParameters : public ABL_Process
{
public:
        PM_FetchPartners_ServicesParameters();
        virtual ~PM_FetchPartners_ServicesParameters();
        PM_FetchPartners_ServicesParameters(const PM_FetchPartners_ServicesParameters&);
        virtual Base_Registry* mb_clone();
        virtual ABL_Process* mb_createCopy();
    virtual bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr = NULL);
        virtual bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
        virtual bool mb_process(ABL_Job* &p_ABL_JobPtr);
        virtual bool mb_stop();
	ABL_String fnGetDateTime();
	void mb_trim(std::string &p_string);
protected:


        PM_FetchPartners_ServicesParametersCache  	*mo_FetchPartnersServicesParametersCachePtr;
        data_container              			    *mo_FetchPartnersServicesParametersCacheContainer;
		ABL_String                                  ms_Stopsignalfile;
		ABL_Service*								mo_ABLServicePtr;
};

extern "C" {EXPORT Base_Registry* gb_getPM_FetchPartners_ServicesParameters();}

#endif

