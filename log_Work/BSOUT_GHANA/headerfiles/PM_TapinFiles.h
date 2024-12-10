#ifndef PM_TapinFiles_H
#define PM_TapinFiles_H
#include "ABL_Process.h"
#include "ABL_String.h"

class PM_TapinFiles : public ABL_Process
{
	public:
		PM_TapinFiles();
		virtual ~PM_TapinFiles();
		PM_TapinFiles(const PM_TapinFiles &PM_TapinFiles);
		Base_Registry* mb_clone();
		ABL_Process* mb_createCopy();
		bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr,ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr,ABL_Service *p_ABL_ServicePtr = NULL); 
		bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
		bool mb_process(ABL_Job* &p_ABL_JobPtr);
		bool mb_stop();		
		void InitialisePartnerDetails() ;

		struct PartnerInfo
		{
			ABL_String FileTranDir    ;
			ABL_String HplmnCode      ;
			ABL_String VplmnCode      ;
			ABL_String FileTypeInd    ;
			int        FileSeqNum     ;
			long       SettCallEvents ;
			ABL_String FileName       ;
			float     Surchperc      ;
			ABL_String PartnerCode    ;
			ABL_String PartnerDesc    ;
			ABL_String DialingCode    ;
			ABL_String Repriceflag    ;
			ABL_String RateIDDFlag    ; 
			ABL_String CamelFilterFlag;
		};

	protected:
		/*	ABL_String	m_directoryName; 
		ABL_String lc_BsoutType;
		ABL_String lc_CountryCode;
		int lc_AgrTypeCount;*/

		struct PartnerInfo   stPartFileInfo;
		/****************************************************************************/
		/* Variables Declared to store Directories Path Based on Home Directory Flag */
		ABL_String     DataFilesDir ;    	
		ABL_String     SuccessFilesDir ;    	
		ABL_String     TouchFileFlag ;
		ABL_String     Lockfilepath ;
		ABL_String     Stopsignalpath ;
};

extern "C" 
{
	EXPORT Base_Registry* gb_getPM_TapinFiles();
}

#endif
