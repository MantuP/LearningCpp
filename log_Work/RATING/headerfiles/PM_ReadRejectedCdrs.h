#ifndef PM_ReadRejectedCdrs_H
#define PM_ReadRejectedCdrs_H
#include "ABL_Process.h"
#include "ABL_String.h"

#include "ABL_Service.h"
#include "ABL_Exception.h"
#include "PM_Job.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "ABL_CacheManager.h"
#include "ABL_DateTime.h"
#include "ABL_Date.h"
#include "ABL_DbDate.h"
#include "string.h"
#include "sstream"
#include "vector"
#include "iostream"
#include "stdio.h"
#include <stdlib.h>

#include <sys/stat.h>

#include <iostream>
#include <iomanip>
#include <fstream>

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

class PM_ReadRejectedCdrs : public ABL_Process
{
public:
	PM_ReadRejectedCdrs();
	virtual ~PM_ReadRejectedCdrs();
	PM_ReadRejectedCdrs(const PM_ReadRejectedCdrs&);
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
extern "C" {EXPORT Base_Registry* gb_PM_ReadRejectedCdrs();}
#endif

