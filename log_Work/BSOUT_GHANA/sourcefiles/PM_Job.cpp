#include "PM_Job.h"

PM_Job::PM_Job()
{
//
}

PM_Job::PM_Job(ABL_String& p_fileName) : m_fileName(p_fileName) ,m_FileTranDir(""),m_HplmnCode(""), m_VplmnCode(""), m_FileTypeInd (""), m_FileSeqNum(0), m_SettCallEvents(0), m_FileName(""), m_Surchperc(0.0),m_PartnerCode(""),m_PartnerDesc(""),m_DialingCode(""),m_Repriceflag(""),m_RateIDDFlag(""),m_CamelFilterFlag(""),m_RepriceAgent(""),m_TotalCdrsMsisdn(0) 
{
//m_processStartTime.mb_fromSysDate(); 
}

PM_Job::~PM_Job()
{
	std::cerr << "Deleting job for " << m_fileName.c_str() << std::endl;
}

Base_Registry* PM_Job::mb_clone()
{
	return ( (Base_Registry*) new PM_Job);
}

ABL_String PM_Job::mb_getJobDetails()
{
	return m_fileName;
}

void PM_Job::mb_revertJob()
{
//
}
