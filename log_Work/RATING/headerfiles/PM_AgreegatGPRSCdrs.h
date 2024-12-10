#ifndef PM_AgreegatGPRSCdrs_H
#define PM_AgreegatGPRSCdrs_H
#include "PM_Job.h"
#include "ABL_Process.h"
#include "ABL_String.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>

#include <sys/stat.h>
#include <cstdlib>
#include <time.h>
#include <ctype.h>
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
#include <sys/stat.h>



#ifdef WIN32
#include <windows.h>
#include <io.h>
#else
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif


class PM_AgreegatGPRSCdrs : public ABL_Process
{
public:
	PM_AgreegatGPRSCdrs();
	virtual ~PM_AgreegatGPRSCdrs();
	PM_AgreegatGPRSCdrs(const PM_AgreegatGPRSCdrs&);
	virtual Base_Registry* mb_clone();
	virtual ABL_Process* mb_createCopy();
	virtual bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr = NULL); 
	virtual bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
	virtual bool mb_process(ABL_Job* &p_ABL_JobPtr);
	virtual bool mb_stop();
	void   fnRemTrailSpaces (char *pszBuffer);
protected:	
	ABL_String		ms_Stopsignalfile;
	ABL_String		ms_directoryName;	
	ABL_String		ms_rawCdrFileName;	
	ABL_String		ms_ProcessedFilePath;
	ABL_String		ms_BackupFlag;
	ABL_String		ms_ErrorFilePath;
        ABL_String              ms_lastAgreegated;
	int                     mi_CheckFreqToHit;
	int                     mi_NumDatesAgreegate;
        ABL_String              mi_Appimsi;
};
extern "C" {EXPORT Base_Registry* gb_getPM_AgreegatGPRSCdrs();}
#endif

