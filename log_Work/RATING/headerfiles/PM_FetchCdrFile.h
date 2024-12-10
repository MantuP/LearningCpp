#ifndef PM_FetchCdrFile_H
#define PM_FetchCdrFile_H
#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "PM_Job.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"

#include "ABL_DirectoryReader.h"
#include "ABL_Exception.h"
#include "ABL_SearchOptions.h"
#include "ABL_String.h"
#include "ABL_DbDate.h"
#include "ABL_Process.h"
#include "ABL_String.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <libgen.h>
#include <sys/stat.h>
#include <time.h>



#include <queue>


class PM_FetchCdrFile : public ABL_Process
{
public:
	PM_FetchCdrFile();
	virtual ~PM_FetchCdrFile();
	PM_FetchCdrFile(const PM_FetchCdrFile&);
	Base_Registry* mb_clone();
	ABL_Process* mb_createCopy();
	bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr = NULL); 
	bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
	bool mb_process(ABL_Job* &p_ABL_JobPtr);
	bool mb_stop();
	bool fnReadFilesFfromFolder();
	int LoadMasterData(int ProcessId) ;
	void UpdateProcess(int ProcessId,ABL_String  Status,ABL_Connection *l_ABL_ConnectionPtrs);
	int fnFilePresent(ABL_String szFileName);
	void InitialiseProcessVar();

struct Masterdata
{
        ABL_String ms_lockfiledir ;
        ABL_String ms_stopSignDir ;
        ABL_String ms_stopSignFile ;
        ABL_String ms_homeDirFlag ;
        ABL_String ms_touchFilesFlag ;
        ABL_String ms_backupFilesFlag ;
        ABL_String ms_homeDir ;
        ABL_String ms_filesDir ;
        ABL_String ms_processFilesDir ;
        ABL_String ms_errorFilesDir ;
        ABL_String ms_backupFilesDir ;
        ABL_String ms_successFilesDir ;
};

protected:
	ABL_String			ms_directoryName;
	ABL_String			ms_stopFileName;
	std::queue<ABL_String> mq_fileNames;
        int				mn_NumFilesToRead;
	ABL_String		ms_FileNamePattern;
	int				mn_ProcessID;
	struct Masterdata  mobj_Masterdata;	
        ABL_String        ms_LastAgreegated;	
};

extern "C" {EXPORT Base_Registry* gb_getPM_FetchCdrFile();}

#endif
