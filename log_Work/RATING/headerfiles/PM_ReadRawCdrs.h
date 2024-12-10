#ifndef PM_ReadRawCdrs_H
#define PM_ReadRawCdrs_H
#include "PM_Job.h"
#include "ABL_Process.h"
#include "ABL_String.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>

#include <sys/stat.h>
#include <time.h>
#include <ctype.h>

#ifdef WIN32
#include <windows.h>
#include <io.h>
#else
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif


class PM_ReadRawCdrs : public ABL_Process
{
public:
	PM_ReadRawCdrs();
	virtual ~PM_ReadRawCdrs();
	PM_ReadRawCdrs(const PM_ReadRawCdrs&);
	virtual Base_Registry* mb_clone();
	virtual ABL_Process* mb_createCopy();
	virtual bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr = NULL); 
	virtual bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
	virtual bool mb_process(ABL_Job* &p_ABL_JobPtr);
	virtual bool mb_stop();
protected:	

	ABL_String		ms_Stopsignalfile;
	ABL_String		ms_directoryName;	
	ABL_String		ms_rawCdrFileName;	
	ABL_String		ms_ProcessedFilePath;
	ABL_String		ms_BackupFlag;
	ABL_String		ms_ErrorFilePath;
        ABL_String              ms_DuplicateFilePath;

};
extern "C" {EXPORT Base_Registry* gb_getPM_ReadRawCdrs();}
#endif

