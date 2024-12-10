/* Modified on 11-02-2010 by Yogesh to store CallAmount, Surcharge Amount as "unsigned long" */
#ifndef PM_WriteToFile_H
#define PM_WriteToFile_H
#include "ABL_Process.h"
#include "ABL_String.h"
#include "PM_Job.h"

class PM_WriteToFile : public ABL_Process
{
	public:
		PM_WriteToFile();
		virtual ~PM_WriteToFile();
		PM_WriteToFile(const PM_WriteToFile &PM_WriteToFile);
		Base_Registry* mb_clone();
		ABL_Process* mb_createCopy();
		bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr,ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr,ABL_Service *p_ABL_ServicePtr = NULL); 
		bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
		bool mb_process(ABL_Job* &p_ABL_JobPtr);
		bool mb_stop();		
		void InitialiseTAPCdrsParameters();
		void PrepareGsmLine (char *p_lineBufferPtr);
		void PrepareGprsCDRs(char *p_lineBufferPtr);
		void replace_str(char *sou,char *sval,int st_ps,int no_ch,char pad_ch) ;
		void InitialisePartnerDetails();
		void InitialiseCdrsParameters();

	protected:
		/* ABL_String	m_directoryName; */
		struct StTAPCdrs       g_TapCdrs;
		ABL_String   UTCOffset       ;
		ABL_String   DataFilesDir    ;    	
		ABL_String   SuccessFilesDir ;    	
		ABL_String   TouchFileFlag   ;
		ABL_String   Lockfilepath    ;
		ABL_String   Stopsignalpath  ;

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
		ABL_String   l_CdrRepriceflag ;
};

extern "C" 
{
	EXPORT Base_Registry* gb_getPM_WriteToFile();
}

#endif
