#ifndef PM_ParseRawEvent_H
#define PM_ParseRawEvent_H
#include "PM_Job.h"
#include "ABL_Process.h"
#include "ABL_String.h"
#include "ABL_Exception.h"
#include <stdlib.h>
#include "ABL_Service.h"
#include <string.h>

class PM_ParseRawEvent : public ABL_Process
{
public:
	PM_ParseRawEvent();
	virtual ~PM_ParseRawEvent();
	PM_ParseRawEvent(const PM_ParseRawEvent&);
	virtual Base_Registry* mb_clone();
	virtual ABL_Process* mb_createCopy();
	virtual bool mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr = NULL); 
	virtual bool mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr);
	virtual bool mb_process(ABL_Job* &p_ABL_JobPtr);
	void tokenize(const std::string& str,std::vector<std::string>& tokens,const std::string& delimiters );
	virtual bool mb_stop();
	int fnValidateCdr(PM_Job * &p_ABL_JobPtr,ABL_String in_RawCdr,long in_RecordNo,unsigned int in_FileID);
	void  fnRemoveZeros(ABL_String *str);
	void mb_trim(std::string &p_string);


protected:	

	ABL_DateTime  	md_MinCallDate;
    ABL_DateTime  	md_MaxCallDate;
	ABL_String		ms_Stopsignalfile;
	ABL_String		ms_NeCode;

};

extern "C" {EXPORT Base_Registry* gb_getPM_ParseRawEvent();}

#endif
