/* Modified on 11-02-2010 by Yogesh to store CallAmount, Surcharge Amount as "unsigned long" */
#ifndef PM_GetMsisdn_H
#define PM_GetMsisdn_H
#include "ABL_Process.h"
#include "ABL_String.h"
#include "PM_Job.h"

class PM_GetMsisdn : public ABL_Process
{
	public:
		PM_GetMsisdn();
		virtual ~PM_GetMsisdn();
		PM_GetMsisdn(const PM_GetMsisdn &PM_GetMsisdn);
		Base_Registry* mb_clone();
		ABL_Process* mb_createCopy();
		bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr,ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr,ABL_Service *p_ABL_ServicePtr = NULL); 
		bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
		bool mb_process(ABL_Job* &p_ABL_JobPtr);
		bool mb_stop();		
		void InitialiseTAPCdrsParameters();
		void replace_str(char *sou,char *sval,int st_ps,int no_ch,char pad_ch) ;
		void sub_str(char *so,char *tr,int st_ps,int no_ch);
		void InitialiseCdrsParameters();

	protected:
		/* ABL_String	m_directoryName; */
		struct StTAPCdrs       g_TapCdrs;
		long         l_SettCallEvents ;
		ABL_String   UTCOffset       ;
		ABL_String   DataFilesDir    ;    	
		ABL_String   SuccessFilesDir ;    	
		ABL_String   TouchFileFlag   ;
		ABL_String   Lockfilepath    ;
		ABL_String   Stopsignalpath  ;
};

extern "C" 
{
	EXPORT Base_Registry* gb_getPM_GetMsisdn();
}

#endif
