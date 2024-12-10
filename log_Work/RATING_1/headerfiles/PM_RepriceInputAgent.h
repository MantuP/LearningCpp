#ifndef PM_RepriceInputAgent_H
#define PM_RepriceInputAgent_H

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


#include <queue>


class PM_RepriceInputAgent : public ABL_Process
{
public:
	PM_RepriceInputAgent();
	virtual ~PM_RepriceInputAgent();
	PM_RepriceInputAgent(const PM_RepriceInputAgent&);
	Base_Registry* mb_clone();
	ABL_Process* mb_createCopy();
	bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr = NULL); 
	bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
	bool mb_process(ABL_Job* &p_ABL_JobPtr);
	bool mb_stop();
	bool fnReadRepriceData();
	int LoadMasterData(int ProcessId) ;
	void UpdateProcess(int ProcessId,ABL_String  Status,ABL_Connection *l_ABL_ConnectionPtrs);
	int fnFilePresent(ABL_String szFileName);
	void InitialiseProcessVar();
	void tokenize(const std::string& in_str,std::vector<std::string>& lv_tokens,const std::string& in_delimiters );
	bool UpdatePMRepriceLog(ABL_String in_FileName);
protected:
	unsigned int mn_total_files_In_rerate_reprice_seq_no;

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
	
};

extern "C" {EXPORT Base_Registry* gb_getPM_RepriceInputAgent();}

#endif
