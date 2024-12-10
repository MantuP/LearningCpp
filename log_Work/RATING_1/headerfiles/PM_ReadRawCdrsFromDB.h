#ifndef PM_ReadRawCdrsFromDB_H
#define PM_ReadRawCdrsFromDB_H
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


class PM_ReadRawCdrsFromDB : public ABL_Process
{
public:
	PM_ReadRawCdrsFromDB();
	virtual ~PM_ReadRawCdrsFromDB();
	PM_ReadRawCdrsFromDB(const PM_ReadRawCdrsFromDB&);
	virtual Base_Registry* mb_clone();
	virtual ABL_Process* mb_createCopy();
	virtual bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr = NULL); 
	virtual bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
	virtual bool mb_process(ABL_Job* &p_ABL_JobPtr);
	virtual bool mb_stop();
	void tokenize(const std::string& in_str,std::vector<std::string>& lv_tokens,const std::string& in_delimiters );
protected:	
	ABL_String		ms_directoryName;
	ABL_String		ms_cdrFileName;  
	ABL_String		ms_rawCdrFileName;
	ABL_String		ms_rawCdr;
	ABL_String		ms_Stopsignalfile;
};
extern "C" {EXPORT Base_Registry* gb_getPM_ReadRawCdrsFromDB();}
#endif

