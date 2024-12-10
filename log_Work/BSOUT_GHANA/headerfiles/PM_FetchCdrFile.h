#ifndef PM_FetchCdrFile_H
#define PM_FetchCdrFile_H
#include "ABL_Process.h"
#include "ABL_String.h"
#include <queue>

#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "PM_Job.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>

class PM_FetchCdrFile : public ABL_Process
{
	public:
		PM_FetchCdrFile();
		virtual ~PM_FetchCdrFile();
		PM_FetchCdrFile(const PM_FetchCdrFile &PM_FetchCdrFile);
		Base_Registry* mb_clone();
		ABL_Process* mb_createCopy();
		bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr,ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr,ABL_Service *p_ABL_ServicePtr = NULL); 
		bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
		bool mb_process(ABL_Job* &p_ABL_JobPtr);
		bool mb_stop();
		void UpdateProcess(int ProcessId,ABL_String  Status,ABL_Connection *l_ABL_ConnectionPtrs);
		void InitialiseProcessVar() ;

		ABL_String gProcessStartDate ;
		long   gUnixPid;
		char   gErrorMessage[200] ;

		struct Masterdata
		{
			ABL_String LockFileDir         ;
			ABL_String StopSignDir         ;
			ABL_String StopSignFile        ;
			ABL_String FileTypeIndicator   ;
			ABL_String HomeDirFlag         ;
			ABL_String TouchFilesFlag      ;
			ABL_String BackupFilesFlag     ;
			ABL_String HomeDir             ;
			ABL_String FilesDir            ;
			ABL_String ProcessFilesDir     ;
			ABL_String ErrorFilesDir       ;
			ABL_String BackupFilesDir      ;
			ABL_String SuccessFilesDir     ;
			ABL_String StopSignPath        ;
			ABL_String RemoveStopSignalCmd ;
		};

	protected:
		ABL_String	m_directoryName    ;
		ABL_String	m_stopFileName     ;
		std::queue<ABL_String> m_fileNames ;
		long     l_processId               ; 
		struct Masterdata  gStMasterdata   ; 
};

extern "C" 
{
	EXPORT Base_Registry* gb_getPM_FetchCdrFile();
}

#endif
