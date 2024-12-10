#include "PM_Job.h"

PM_Job::PM_Job()
{
	//
}


PM_Job::PM_Job(ABL_String& p_fileName) : gs_fileName(p_fileName),gn_InPutFileId(0),gs_isNationalNum(""),gn_TotalCDRS_In_File(0),gn_RepriceSeqNo(0),gs_AgreementType(""),gs_IsGPRSFile("NO"),gs_SourceFilePath(""),gs_ProcessedFilePath(""),gs_BackupFlag(""),gs_ErrorFile_Path(""),gn_Files_In_Rerate_Reprice_seq_no(0),gs_Ratinglog("Y")
{

}

PM_Job::~PM_Job()
{
	try
	{
		
	
		ga_RatedCdrs.clear();
		ga_RejectedCdrs.clear();
		ga_RatingLog.clear();
		ga_ControlParams.clear();
		ga_AgreementType.clear();
		ga_DroppedCdr.clear();
		ga_RawCDRSVector.clear();
		ga_ATypeLogMap.clear();
		ga_CallTypeCountsMap.clear();
	}
	catch (...)
	{
		std::cout<<"Error in pm_job destructor: "<<std::endl;
	}
}
	
Base_Registry* PM_Job::mb_clone()
{
	return ( (Base_Registry*) new PM_Job);
}
	
ABL_String PM_Job::mb_getJobDetails()
{
	return gs_fileName;
}
	
void PM_Job::mb_revertJob()
{

}
