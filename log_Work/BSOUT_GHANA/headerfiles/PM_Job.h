#ifndef PM_JOB_H
#define PM_JOB_H
#include "ABL_Job.h"
#include "ABL_DateTime.h"
#define TOTAL_TAP_CDRS           200000

struct StTAPCdrs
{
	ABL_String    gFileTranDir       ;
	ABL_String    gHplmnCode         ;
	ABL_String    gVplmnCode         ;
	ABL_String    gFileTypeInd       ;
	long          gFileSeqNum        ;
	int           gCallType          ;
	ABL_String    gImsiNum           ;
	ABL_String    gCalledCallingNum  ;
	ABL_String    gCallDate          ;
	ABL_String    gCallTime          ;
	double          gDuration          ;
	double	 gCallAmount        ;
	double gSurchargeAmount   ;
	long          gCdrSeqNum         ;
	ABL_String    gBasicServType     ;
	ABL_String    gBasicServCode     ;
	ABL_String    gDataVolumeIncoming;
	ABL_String    gDataVolumeOutgoing;
	ABL_String    gAccessPointNameNI ;
	ABL_String    gPDPAddress        ;
	ABL_String    gLocalDateTime     ;
	int           gCamelUsedFlag     ;
	ABL_String    gCdrRepriceflag   ;
	ABL_String    gMsisdn   ;
	/* Added service code for segregating GSM and GPRS calls*/
	ABL_String    gServiceCode   ;
	ABL_String    gSentToBs;
};

class PM_Job : public ABL_Job
{
	public:
		PM_Job();
		PM_Job(ABL_String& p_fileName);
		virtual ~PM_Job();
		Base_Registry* mb_clone();
		virtual ABL_String mb_getJobDetails();
		virtual void mb_revertJob();
		ABL_String	m_fileName;
		//ABL_DateTime m_processStartTime;
		//ABL_DateTime m_fileCreatedDate;	
		long	m_numberOfEvents;
		double	FileSeQNo;

		std::vector<StTAPCdrs> TAPCdrs;

		ABL_String m_FileTranDir   ;
		ABL_String m_HplmnCode      ;
		ABL_String m_VplmnCode      ;
		ABL_String m_FileTypeInd    ;
		int        m_FileSeqNum     ;
		long       m_SettCallEvents ;
		ABL_String m_FileName       ;
		float      m_Surchperc      ;
		ABL_String m_PartnerCode    ;
		ABL_String m_PartnerDesc    ;
		ABL_String m_DialingCode    ;
		ABL_String m_Repriceflag    ;
		ABL_String m_RateIDDFlag    ;
		ABL_String m_CamelFilterFlag;
		ABL_String m_RepriceAgent   ;
		int        m_TotalCdrsMsisdn;
};

#endif
