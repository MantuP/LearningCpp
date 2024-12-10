#ifndef PM_TapinReprice_H
#define PM_TapinReprice_H
#include "ABL_Process.h"
#include "ABL_String.h"

class PM_TapinReprice : public ABL_Process
{
	public:
		PM_TapinReprice();
		virtual ~PM_TapinReprice();
		PM_TapinReprice(const PM_TapinReprice &PM_TapinReprice);
		Base_Registry* mb_clone();
		ABL_Process* mb_createCopy();
		bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr,ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr,ABL_Service *p_ABL_ServicePtr = NULL); 
		bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
		bool mb_process(ABL_Job* &p_ABL_JobPtr);
		bool mb_stop();		
		void InitialisePartnerDetails();

	protected:
		/* ABL_String	m_directoryName; */
		ABL_String   Lockfilepath    ;
		ABL_String   Stopsignalpath  ;
		int          op_ExecStatus ;
		ABL_String   op_ErrCode    ;
		ABL_String   op_ErrMesg    ;
		ABL_String   l_FileTranDir    ;
		ABL_String   l_HplmnCode      ;
		ABL_String   l_VplmnCode      ;
		ABL_String   l_FileTypeInd    ;
		int          l_FileSeqNum     ;
		long         l_SettCallEvents ;
		ABL_String   l_FileName       ;
		float        l_Surchperc      ;
		ABL_String   l_PartnerCode    ;
		ABL_String   l_PartnerDesc    ;
		ABL_String   l_DialingCode    ;
		ABL_String   l_Repriceflag    ;
		ABL_String   l_RateIDDFlag    ;
		ABL_String   l_CamelFilterFlag;
		ABL_String   l_RepriceAgent   ;
};

extern "C" 
{
	EXPORT Base_Registry* gb_getPM_TapinReprice();
}

#endif
