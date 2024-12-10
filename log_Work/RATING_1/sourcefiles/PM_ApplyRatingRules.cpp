//Agent to apply RATING RULES for the cdrs.
#include "PM_ApplyRatingRules.h"
extern "C" {EXPORT 
Base_Registry* gb_getPM_ApplyRatingRules()
{
	return ( (Base_Registry*) new PM_ApplyRatingRules);
}
}

PM_ApplyRatingRules::PM_ApplyRatingRules()
{
	//
}

PM_ApplyRatingRules::~PM_ApplyRatingRules()
{
	//
}

PM_ApplyRatingRules::PM_ApplyRatingRules(const PM_ApplyRatingRules& p_copyObject)
{
	this->mo_ABLServicePtr					=	p_copyObject.mo_ABLServicePtr;
	this->mo_ApplyRatingRulesCachePtr		=   (PM_RatingRulesCache*)p_copyObject.mo_ApplyRatingRulesCachePtr->mb_createCopy();	
	this->mo_ApplyRatingRulescacheContainer =	p_copyObject.mo_ApplyRatingRulescacheContainer;
	this->ms_Stopsignalfile					=	p_copyObject.ms_Stopsignalfile;
	this->ma_CallType						=   p_copyObject.ma_CallType;
	this->ma_ControlParams					=	p_copyObject.ma_ControlParams;
	this->ma_AgreementType					=	p_copyObject.ma_AgreementType;
}

Base_Registry* PM_ApplyRatingRules::mb_clone()
{
        return ( (Base_Registry*) new PM_ApplyRatingRules );
}

ABL_Process* PM_ApplyRatingRules::mb_createCopy()
{
	return ( new PM_ApplyRatingRules (*this));
}

bool PM_ApplyRatingRules::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{	 
	ABL_Connection				lo_ABLConnection;
	ABL_Statement				lo_ABLStatement;
	ABL_ResultSet				lo_ABLResultSet;
	ABL_String					ls_sql;
	gr_AgreementType			lr_AgreementsType;	
	gr_ControlParams			lr_ControlParams;

		mo_ABLServicePtr = p_ABL_ServicePtr;

		try
		{
			p_ABL_AgentCommunicatorPtr->mb_getParameter("STOP_FILE",ms_Stopsignalfile);
			lo_ABLConnection.mb_createConnection(*mo_ABLServicePtr);

		/* Fetching values from pm_app_preference table. */


		ls_sql="SELECT  rating_type, NVL(mult_fact,1),country_dialling_code, national_number_length  FROM PM_APP_PREFERENCE  WHERE ROWNUM = 1";

		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_sql);		
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();

		ABL_String		la_RatingType[2];
		unsigned int	la_MultFactor[2];
		ABL_String		la_CountryDiallingCode[2];
		int				la_NationalNumberLength[2];

		lo_ABLResultSet.mb_setBulkCount(2);
		lo_ABLResultSet	<< la_RatingType;
		lo_ABLResultSet	<< la_MultFactor;
		lo_ABLResultSet	<< la_CountryDiallingCode;
		lo_ABLResultSet	<< la_NationalNumberLength;
        	while(lo_ABLResultSet.mb_fetch())
		{
			int records = lo_ABLResultSet.mb_getNumArrayRows();
			for(int i = 0; i < records ; i++)
			{						
				lr_ControlParams.gs_RatingType=la_RatingType[i];
				lr_ControlParams.gn_MultFactor=la_MultFactor[i];
				lr_ControlParams.gs_CountryDiallingCode=la_CountryDiallingCode[i];
				lr_ControlParams.gn_NationalNumberLength=la_NationalNumberLength[i];
				ma_ControlParams.push_back(lr_ControlParams);
			}
		}

		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);                                     
		
		/* Fetching agreement types from pm_agreement_type table.*/
		ls_sql ="select	AGREEMENT_TYPE,DESCRIPTION, PARTNER_IDENTIFIER_KEY, INVOICE, nvl(SPLIT_CALLS,'') as SPLIT_CALLS, CHARGE_SMSMO_ON_SMSCID, STORE_DROPPED_CDRS, RATE ,Multi_Factor,NVL(STORE_DUPLICATE_CDRS,'Y') FROM PM_AGREEMENT_TYPE where  rate = 'Y' ";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_sql);		
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();

		ABL_String		la_AgreementType[3];
		ABL_String		la_Description[3];
		ABL_String		la_PartnerIdentifierKey[3];
		ABL_String		la_Invoice[3];
		ABL_String		la_SplitCalls[3];
		ABL_String		la_Charge_SMSMO_On_SMSCID[3];
		ABL_String		la_Store_Dropped_Cdrs[3];
		ABL_String		la_Rate[3];
		unsigned int	        la_MultFactors[3];
		ABL_String		la_Store_Duplicate_Cdrs[3];
       //ABL_String              la_Partial_Search[3];

		lo_ABLResultSet.mb_setBulkCount(3);
		lo_ABLResultSet	<< la_AgreementType;
		lo_ABLResultSet	<< la_Description;
		lo_ABLResultSet	<< la_PartnerIdentifierKey;
		lo_ABLResultSet	<< la_Invoice;
		lo_ABLResultSet	<< la_SplitCalls;	
		lo_ABLResultSet	<< la_Charge_SMSMO_On_SMSCID;	
		lo_ABLResultSet	<< la_Store_Dropped_Cdrs;	
		lo_ABLResultSet	<< la_Rate;	
		lo_ABLResultSet << la_MultFactors;
		lo_ABLResultSet << la_Store_Duplicate_Cdrs;
     // lo_ABLResultSet << la_Partial_Search;
		
		while(lo_ABLResultSet.mb_fetch())
		{
			int records = lo_ABLResultSet.mb_getNumArrayRows();
			for(int i = 0; i < records ; i++)
			{						
				lr_AgreementsType.gs_AgreementType= la_AgreementType[i];
				lr_AgreementsType.gs_Description= la_Description[i];
				lr_AgreementsType.gs_PartnerIdentifierKey=la_PartnerIdentifierKey[i];
				lr_AgreementsType.gs_Invoice=la_Invoice[i];
				lr_AgreementsType.gs_SplitCalls= la_SplitCalls[i];	
				lr_AgreementsType.gs_Charge_SMSMO_On_SMSCID= la_Charge_SMSMO_On_SMSCID[i];	
				lr_AgreementsType.gs_Store_Dropped_Cdrs= la_Store_Dropped_Cdrs[i];	
				lr_AgreementsType.gs_Rate= la_Rate[i];
				lr_AgreementsType.gn_MultFactor= la_MultFactors[i];
				lr_AgreementsType.gs_Store_Duplicate_Cdrs=la_Store_Duplicate_Cdrs[i];
           //   lr_AgreementsType.gs_Partial_Search=la_Partial_Search[i];
				ma_AgreementType.push_back(lr_AgreementsType);
			}
		}				
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement); 

		/* Fetching Call event types from pm_call_event_type table. */
		ls_sql="Select nvl(CALL_EVENT_TYPE,0) FROM  PM_CALL_EVENT_TYPES";
		lo_ABLStatement = lo_ABLConnection.mb_createStatement(ls_sql);		
		lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();

		int la_CallType[16];
        	lo_ABLResultSet.mb_setBulkCount(8);
		lo_ABLResultSet	<<la_CallType;		
		while(lo_ABLResultSet.mb_fetch())
		{
			int TotalCallTypes = lo_ABLResultSet.mb_getNumArrayRows();
			for(int i = 0; i < TotalCallTypes ; i++)
			{						
             	ma_CallType.push_back(la_CallType[i]);
     		}

    	}
		lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
		lo_ABLConnection.mb_terminateStatement(lo_ABLStatement);
		
	 }   
	catch(ABL_Exception &e)
	{
		*mo_ABLServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;	
		 ABL_String ls_command("touch ");
		 ls_command +=ms_Stopsignalfile;
		 system(ls_command.c_str());  
		 return false;
	}
	catch(...)
	{
		ABL_String ls_command("touch ");
		ls_command +=ms_Stopsignalfile;
		 system(ls_command.c_str()); 	
		*mo_ABLServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}

	return true;
}

//Gets the Cache Handler.
bool PM_ApplyRatingRules::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	try
	{   
		mo_ApplyRatingRulesCachePtr		=	(PM_RatingRulesCache*)mo_ABLServicePtr->mb_getObject("PM_RatingRulesCache")->mb_clone();
		mo_ApplyRatingRulescacheContainer   =	p_ABL_CacheManagerPtr->mb_getCache("PM_RatingRulesCache");
	}
	catch(ABL_Exception &e)
	{
		*mo_ABLServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;
		ABL_String ls_command("touch ");
		ls_command +=ms_Stopsignalfile;
		system(ls_command.c_str());  
		return false;
	}
	catch(...)
	{
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str()); 	
		*mo_ABLServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}	
	return true;
}


bool PM_ApplyRatingRules::mb_process(ABL_Job* &p_ABL_JobPtr)
{	

	PM_Job* lo_PMJobPtr = (PM_Job*)p_ABL_JobPtr;	
	int i=0;
	gr_CallTypeCounts   lr_CallTypeCounts; //Creating an object of the structure Ic_CallTypeCounts.
	gr_RejectedCdr		lr_RejectedCdrs;  //Creating an object of the structure Ic_Rejected_Cdr.
	gr_DroppedCdr      lr_DroppedCdr;	  //Creating an object of the structure Ic_Dropped_Cdr.
	std::vector<gr_RatedCdr> la_RatedCdrs; //local rated cdrs vector

	ABL_String ls_CallType; 
	int ln_flag=0;

	ABL_String	ls_DropCode="";
	ABL_String ls_DropMesg="";
	ABL_String ls_DropValue="";
	ABL_String	ls_RejMesg="" ;

	// Local variables declaration.
	int ln_IncFieldNo   = 0;
	int ln_OutFieldNo   = 0;

	int ln_FromPosInField      = 0;
	int ln_ToPosInField       = 0;

	int ln_FromPosOutField      = 0;
	int ln_ToPosOutField        = 0;

	int ln_pos1			= 0;
	PM_RatingRulesCache   *lobj_Temp_PM_RatingRulesCachePtr;
	ABL_String ls_agreementtype_calltype="";		
	ABL_String ls_TempConvert="";
	


	try
	{
	
                   if ( lo_PMJobPtr->gs_FileStatus == "D" || lo_PMJobPtr->gs_FileStatus == "F" )
                        {
                                return true;
                        }
	
		if (lo_PMJobPtr->ga_RatedCdrs.size()== 0) 
		{
			if (lo_PMJobPtr->gs_IsGPRSFile=="YES")
			{
				return true;
			}
			else
			{
				*mo_ABLServicePtr << DEBUG <<" There are no cdrs to Apply rating rules: " <<lo_PMJobPtr->gs_fileName<<Endl;	
				return false;          
			}
		}
		*mo_ABLServicePtr << DEBUG<< "Start :" <<lo_PMJobPtr->gs_fileName <<" : "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;

		

		if (mo_ApplyRatingRulescacheContainer->mb_size()==0)
		{
			*mo_ABLServicePtr << CRITICAL << " There is no records in PM_RATING_RULES   Rating is  stopping...: "  << Endl;	
			ABL_String ls_command("touch ");
			ls_command +=ms_Stopsignalfile;
			system(ls_command.c_str()); 

			return false;
		}

		if (ma_AgreementType.size()==0)
		{
			rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
			*mo_ABLServicePtr << CRITICAL << "No agreement types are defined. Cannot continue with rating. Define Agreement Types and re-start rating" << Endl;
			return(false);
		}
		/* Copy values from local structure to a global structure.*/
		for ( int k=0;k<ma_ControlParams.size();k++)
		{
			lo_PMJobPtr->ga_ControlParams.push_back(ma_ControlParams[k]);	
		}


	for(int agr_no=0;agr_no< ma_AgreementType.size();agr_no++)
	{
		for(int j=0;j<ma_CallType.size();j++)
		{	
			
			//Commented below line,because the variable is already declared at top. LTE usage 
			//gr_CallTypeCounts	lr_CallTypeCounts; 
			lr_CallTypeCounts.gn_FileId=lo_PMJobPtr->gn_InPutFileId ;
			lr_CallTypeCounts.gs_AgreementType=ma_AgreementType[agr_no].gs_AgreementType;
			lr_CallTypeCounts.gn_CallTypeEvent=ma_CallType[j];
			lr_CallTypeCounts.gn_TotalCount=0;
			lr_CallTypeCounts.gn_TotalDuration=0;
			lr_CallTypeCounts.gn_TotalIncCount=0;
			lr_CallTypeCounts.gn_TotalIncDuration=0;
			lr_CallTypeCounts.gn_TotalIncRatedCount=0;
			lr_CallTypeCounts.gn_TotalIncRatedDuration=0;
			lr_CallTypeCounts.gn_TotalIncRejCount=0;
			lr_CallTypeCounts.gn_TotalIncRejDuration=0;
			lr_CallTypeCounts.gn_TotalIncDropCount=0;
			lr_CallTypeCounts.gn_TotalIncDropDuration=0;
			lr_CallTypeCounts.gn_TotalOutCount=0;
			lr_CallTypeCounts.gn_TotalOutDuration=0;
			lr_CallTypeCounts.gn_TotalOutRatedCount=0;
			lr_CallTypeCounts.gn_TotalOutRatedDuration=0;
			lr_CallTypeCounts.gn_TotalOutRejCount=0;
			lr_CallTypeCounts.gn_TotalOutRejDuration=0;
			lr_CallTypeCounts.gn_TotalOutDropCount=0;
			lr_CallTypeCounts.gn_TotalOutDropDuration=0;
			lr_CallTypeCounts.gn_TotalUnknownRejected=0;
			lr_CallTypeCounts.gn_TotalUnknown=0;
			ls_agreementtype_calltype="";
			ls_TempConvert="";
			ls_TempConvert.mb_fromDouble(lr_CallTypeCounts.gn_CallTypeEvent);
			ls_agreementtype_calltype=lr_CallTypeCounts.gs_AgreementType;
			ls_agreementtype_calltype+=ls_TempConvert;
			lo_PMJobPtr->ga_CallTypeCountsMap.insert(std::pair<ABL_String,gr_CallTypeCounts>(ls_agreementtype_calltype,lr_CallTypeCounts) );
		}
		gr_RatingATypeLog	lr_RatingAtypeLog;
		lr_RatingAtypeLog.gs_AgreementType=ma_AgreementType[agr_no].gs_AgreementType;
		lr_RatingAtypeLog.gn_FileId =lo_PMJobPtr->gn_InPutFileId;
		lr_RatingAtypeLog.gd_ProcessStartTime=lo_PMJobPtr->ga_RatingLog[0].gd_ProcessStartTime;

		lr_RatingAtypeLog.gn_TotalCdrs=0;						
		lr_RatingAtypeLog.gn_TotalRated_cdrs=0;
		lr_RatingAtypeLog.gn_TotalRejected=0;
		lr_RatingAtypeLog.gn_TotalDropped=0;
		lr_RatingAtypeLog.gd_ProcessingTime =0;
		lr_RatingAtypeLog.gn_TotalDuplicate =0;				
		lo_PMJobPtr->ga_ATypeLogMap.insert(std::pair<ABL_String,gr_RatingATypeLog>(ma_AgreementType[agr_no].gs_AgreementType,lr_RatingAtypeLog) );				

		ln_IncFieldNo=0;
		ln_OutFieldNo=0;
		std::string str=ma_AgreementType[agr_no].gs_PartnerIdentifierKey.mb_getSTLString ();				
		ln_pos1=str.find("|",0);

		//get partner identifier from raw cdr for incoming leg and agreement type.
		ln_IncFieldNo=atoi(ma_AgreementType[agr_no].gs_PartnerIdentifierKey.mb_subStr(0,ln_pos1).c_str());

		//get partner identifier from raw cdr for outgoing leg and agreement type.
		ln_OutFieldNo=atoi(ma_AgreementType[agr_no].gs_PartnerIdentifierKey.mb_subStr(ln_pos1+1,ma_AgreementType[agr_no].gs_PartnerIdentifierKey.mb_length()-(ln_pos1+1)).c_str());					 


		// This block will apply, rating rules for the cdrs.
		for(i=0; i<lo_PMJobPtr->ga_RatedCdrs.size();i++)  // Loop for getting cdr's values.  
		{
			lo_PMJobPtr->ga_RatedCdrs[i].gs_StoreDroppedCdr				=	ma_AgreementType[agr_no].gs_Store_Dropped_Cdrs;
			lo_PMJobPtr->ga_RatedCdrs[i].gs_StoreDuplicateCdr           =	ma_AgreementType[agr_no].gs_Store_Duplicate_Cdrs;
			lo_PMJobPtr->ga_RatedCdrs[i].gs_Charge_SMSMO_SMSC_flg		=	ma_AgreementType[agr_no].gs_Charge_SMSMO_On_SMSCID;
			lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType				=	ma_AgreementType[agr_no].gs_AgreementType;	
			lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifierKey		=	ma_AgreementType[agr_no].gs_PartnerIdentifierKey;
			lo_PMJobPtr->ga_RatedCdrs[i].gn_MultFactor					=	ma_AgreementType[agr_no].gn_MultFactor;
			lo_PMJobPtr->ga_RatedCdrs[i].gs_Rate						=	ma_AgreementType[agr_no].gs_Rate;
//          lo_PMJobPtr->ga_RatedCdrs[i].gs_Partial                    =    ma_AgreementType[agr_no].gs_Partial_Search;

			update_CallTypeCountsTot(lo_PMJobPtr, lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType,lo_PMJobPtr->ga_RatedCdrs[i].gn_CallType,lo_PMJobPtr->ga_RatedCdrs[i].gn_CallDuration);
			update_ATypeRatingLog(lo_PMJobPtr, lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType);
			try
			{

				//if(i==0) 
				if(i>=0) //modified to take variable length cdrs as per LTE usage and will populate  proper partner Identifiler .
				{
					if(ln_IncFieldNo == 1)
					{
						ln_FromPosInField = 0;
					 }
					 else
					 {
						ln_FromPosInField = GetFrom_Pos(lo_PMJobPtr->ga_RatedCdrs[i].gs_RawCdr.mb_getSTLString (),ln_IncFieldNo);
					 }
					 ln_ToPosInField = GetTo_Pos(lo_PMJobPtr->ga_RatedCdrs[i].gs_RawCdr.mb_getSTLString (),ln_IncFieldNo);  


					 
					if(ln_OutFieldNo == 1)
					{
						ln_FromPosOutField = 0;
					}
					else
					{
						ln_FromPosOutField = GetFrom_Pos(lo_PMJobPtr->ga_RatedCdrs[i].gs_RawCdr.mb_getSTLString (),ln_OutFieldNo);					
					}
					ln_ToPosOutField   = GetTo_Pos(lo_PMJobPtr->ga_RatedCdrs[i].gs_RawCdr.mb_getSTLString (),ln_OutFieldNo);
						 


				}
				
				//added as per LTE usage for 4.3 release
				//remove if any trailing spaces are there into following parameters
				std::string st1;
				st1="";
				std::string st2;
                                st2="";
				std::string st3;
                                st3="";
				st1=lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType.c_str();
				st2=lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode.c_str();
				st3=lo_PMJobPtr->ga_RatedCdrs[i].gs_SubscriberType.c_str();
				mb_trim(st1);
				mb_trim(st2);
				mb_trim(st3);
				lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType = st1;
				lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode = st2;
				lo_PMJobPtr->ga_RatedCdrs[i].gs_SubscriberType = st3;
				//modification end
				mo_ApplyRatingRulesCachePtr->mb_setAgreementType(lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType);
				mo_ApplyRatingRulesCachePtr->mb_setServiceCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode);		
				mo_ApplyRatingRulesCachePtr->mb_setSubscriberType(lo_PMJobPtr->ga_RatedCdrs[i].gs_SubscriberType);			
				mo_ApplyRatingRulesCachePtr->mb_setCallType(lo_PMJobPtr->ga_RatedCdrs[i].gn_CallType);

				//the function is used to retrieve the reference to an object, satisfying the criteria's set by the search object. The search *object should be filled with attributes that will be required for hash value calculation and those required by mb_isEqual() function.
				if(mo_ApplyRatingRulescacheContainer->mb_get((CBase*)mo_ApplyRatingRulesCachePtr,(CBase*&)lobj_Temp_PM_RatingRulesCachePtr))
				{
					if(lobj_Temp_PM_RatingRulesCachePtr->mb_getConsiderIncLeg()== "N" && lobj_Temp_PM_RatingRulesCachePtr->mb_getConsiderOutLeg()== "N")
					{

                           continue;
					}


					lo_PMJobPtr->ga_RatedCdrs[i].gs_Partial = lobj_Temp_PM_RatingRulesCachePtr->mb_getPartialSearch();

					//Processing for incoming leg.
					if(lobj_Temp_PM_RatingRulesCachePtr->mb_getConsiderIncLeg()== "Y")
					{
						 try
						{
							 ln_flag=1;
							lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection="I";

							//Function call for calculating Total count and Total duration. 
							update_CallTypeCounts(lo_PMJobPtr, lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType,lo_PMJobPtr->ga_RatedCdrs[i].gn_CallType,lo_PMJobPtr->ga_RatedCdrs[i].gn_CallDuration,lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection);
							
						
							/*drop the cdr if the
							1. inc trunk is not present in case of interconnect agreement type
							2. IMSI is not present in case of roaming agreement type*/
						
							if(lobj_Temp_PM_RatingRulesCachePtr->mb_getIncLegAction()== "D")
							{
								ln_flag=0;
								ls_DropCode = "DROP-001";
								ls_DropMesg = "Rating action configured as D for the Incoming Leg for the service code: ";
								ls_DropMesg+= lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode;
								ls_DropValue = lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode;
								throw   ABL_Exception(2,ls_DropMesg.c_str());																    
							}
							else if(lobj_Temp_PM_RatingRulesCachePtr->mb_getIncLegAction()== "J" || lobj_Temp_PM_RatingRulesCachePtr->mb_getIncLegAction()==" ")
							{
								ls_RejMesg ="Parser rule missing in cdr  for Service=>";
								ls_RejMesg+=	lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode;
								ls_RejMesg+=	"Agreement=>";
								ls_RejMesg+=	lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType;
								ls_CallType.mb_fromDouble(lo_PMJobPtr->ga_RatedCdrs[i].gn_CallType);
								ls_RejMesg+=	"Call Type=>";
								ls_RejMesg+=	ls_CallType;				
								ls_RejMesg+=	";Subs Type=>";
								ls_RejMesg+=	lo_PMJobPtr->ga_RatedCdrs[i].gs_SubscriberType;
								throw  ABL_Exception(1,ls_RejMesg.c_str());
							}


							 
							 // If partner identifier is null, then drop the cdr	

							 std::string ls_partnerIdentifiler=lo_PMJobPtr->ga_RatedCdrs[i].gs_RawCdr.mb_subStr(ln_FromPosInField,ln_ToPosInField-ln_FromPosInField).c_str();
							 mb_trim(ls_partnerIdentifiler);					
							 ls_partnerIdentifiler[ls_partnerIdentifiler.length()]='\0';
                             lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier = ls_partnerIdentifiler;
							
							if (lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerIdentifier =="" && strcmp(lo_PMJobPtr->ga_RatedCdrs[i].gs_SubscriberType.c_str(),"V") != 0)
							{ 
								ln_flag=0;

								ls_DropCode = "DROP-001";
								ls_DropMesg = "INC TRUNK Or IMSI not found for the Called Number: ";
								ls_DropMesg += lo_PMJobPtr->ga_RatedCdrs[i].gs_BNumber;
								ls_DropValue = lo_PMJobPtr->ga_RatedCdrs[i].gs_BNumber;
							    throw   ABL_Exception(2,ls_RejMesg.c_str());

							 }

							if(ln_flag==1)
							{
								
								la_RatedCdrs.push_back( lo_PMJobPtr->ga_RatedCdrs[i]);	 
							}
							

						}
						catch(ABL_Exception &e)
						{
							// Populate rejection details.
							if(e.mb_getErrorCode() == 2)
							{
							//	if(lo_PMJobPtr->ga_RatedCdrs[i].gs_StoreDroppedCdr == "Y")
							//{
									lr_DroppedCdr.gn_CallType			=	lo_PMJobPtr->ga_RatedCdrs[i].gn_CallType;
									lr_DroppedCdr.gs_CallDirection		=	lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection;
									lr_DroppedCdr.gs_AgreementType		=	lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType;
									lr_DroppedCdr.gn_InputFileId		=	lo_PMJobPtr->ga_RatedCdrs[i].gn_InputFileId;
									lr_DroppedCdr.gn_RecordNo			=	lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordNo;
									lr_DroppedCdr.gs_PartnerCode		=	"";
									lr_DroppedCdr.gs_DroppedCdr		=	lo_PMJobPtr->ga_RatedCdrs[i].gs_RawCdr;
									lr_DroppedCdr.gs_DropCode			=	ls_DropCode;
									lr_DroppedCdr.gn_CallDuration		=	lo_PMJobPtr->ga_RatedCdrs[i].gn_CallDuration;								
									lr_DroppedCdr.gs_ErrorMessage		=	ls_DropMesg;
									lr_DroppedCdr.gd_DroppedDate.mb_fromSysDate();
									lr_DroppedCdr.gd_CallDate			=	lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate;
									lr_DroppedCdr.gs_Status			=	"NEW";
									lr_DroppedCdr.gs_ErrorValue		=	ls_DropValue;
									lr_DroppedCdr.gs_UnitRate		=	"";
									lr_DroppedCdr.gs_StoreDroppedCdr	=	lo_PMJobPtr->ga_RatedCdrs[i].gs_StoreDroppedCdr;
									lo_PMJobPtr->ga_DroppedCdr.push_back(lr_DroppedCdr);
								//}
							}
							// Populate rejection details.
							else if(e.mb_getErrorCode() == 1)
							{
								lr_RejectedCdrs.gn_CallType		=	lo_PMJobPtr->ga_RatedCdrs[i].gn_CallType;
								lr_RejectedCdrs.gs_CallDirection	=	lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection;
								lr_RejectedCdrs.gs_AgreementType	=   lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType;
								lr_RejectedCdrs.gn_FileId			=   lo_PMJobPtr->ga_RatedCdrs[i].gn_InputFileId; 
								lr_RejectedCdrs.gn_RecordNo		=   lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordNo;
								lr_RejectedCdrs.gs_ErrorCdr		=	lo_PMJobPtr->ga_RatedCdrs[i].gs_RawCdr;
								//modified as per LTE usage for 4.3 release
                          					//lr_RejectedCdrs.gs_ErrorCode                =       "PARSEERROR";
                          					lr_RejectedCdrs.gs_ErrorCode          =       "RATE-RULES-NF";
                          					//modification end
								if(ls_RejMesg.mb_length()==0)
								 {
									lr_RejectedCdrs.gs_ErrorMessage=" error in apply rating rules. ";
								 }
								 else
								 {
									lr_RejectedCdrs.gs_ErrorMessage	=   ls_RejMesg;
								 }
								lr_RejectedCdrs.gd_RejectedDate.mb_fromSysDate();  
								lr_RejectedCdrs.gd_CallDate		=   lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate;
								lr_RejectedCdrs.gs_Status			=	"NEW";
								lr_RejectedCdrs.gs_ErrorValue		=   lo_PMJobPtr->ga_RatedCdrs[i].gs_BNumber;
								lr_RejectedCdrs.gn_CallDuration	=   lo_PMJobPtr->ga_RatedCdrs[i].gn_CallDuration;
								lr_RejectedCdrs.gs_ChronoNum	=   lo_PMJobPtr->ga_RatedCdrs[i].gs_ChronoNum;
								lr_RejectedCdrs.gn_PartialSeqNum  = lo_PMJobPtr->ga_RatedCdrs[i].gn_PartialSeqNum;

								lo_PMJobPtr->ga_RejectedCdrs.push_back(lr_RejectedCdrs);
							}
							// Populate rejection details.
							else
							{
								//modified as per LTE usage for 4.3 release
                          					//lr_RejectedCdrs.gs_ErrorCode                =       "PARSEERROR";
                          					lr_RejectedCdrs.gs_ErrorCode          =       "RATE-RULES-NF";
                          					//modification end
							if(ls_RejMesg.mb_length()==0)
							 {
								lr_RejectedCdrs.gs_ErrorMessage=" error in apply rating rules. ";
							 }
							 else
							 {
								lr_RejectedCdrs.gs_ErrorMessage	=   ls_RejMesg;
							 }
								lr_RejectedCdrs.gn_FileId			=   lo_PMJobPtr->ga_RatedCdrs[i].gn_InputFileId;
								lr_RejectedCdrs.gn_RecordNo		=   lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordNo;
								lr_RejectedCdrs.gs_AgreementType	=   lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType;
								lr_RejectedCdrs.gs_CallDirection	=	lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection;
								lr_RejectedCdrs.gs_ErrorCdr		=	lo_PMJobPtr->ga_RatedCdrs[i].gs_RawCdr;
								lr_RejectedCdrs.gd_RejectedDate.mb_fromSysDate();
								lr_RejectedCdrs.gs_Status			=	"NEW";
								lr_RejectedCdrs.gn_CallDuration	=   lo_PMJobPtr->ga_RatedCdrs[i].gn_CallDuration;
								lr_RejectedCdrs.gd_CallDate		=   lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate;
								lr_RejectedCdrs.gs_ChronoNum	=   lo_PMJobPtr->ga_RatedCdrs[i].gs_ChronoNum;
								lr_RejectedCdrs.gn_PartialSeqNum  = lo_PMJobPtr->ga_RatedCdrs[i].gn_PartialSeqNum;
								
								lo_PMJobPtr->ga_RejectedCdrs.push_back(lr_RejectedCdrs);
							}
						}
						catch(...)
						{
							rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
							ABL_String l_command("touch ");
							l_command +=ms_Stopsignalfile;
							system(l_command.c_str()); 	
							*mo_ABLServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
							return false;
						}	
					}

					
			     //Processing for Out going Leg.
				if(lobj_Temp_PM_RatingRulesCachePtr->mb_getConsiderOutLeg()== "Y")
				{
					std::vector<gr_RatedCdr>l_RatedCdrs_outleg;
					try
					{
						ln_flag=1;
						lo_PMJobPtr->ga_RatedCdrs[i].gs_Partial = lobj_Temp_PM_RatingRulesCachePtr->mb_getPartialSearch();
						
						// If ConsiderIncLeg field is "Y" then insert one more row into the g_RatedCdr vectror(which is holding cdr values).   
						
							//lo_PMJobPtr->ga_RatedCdrs.insert((lo_PMJobPtr->ga_RatedCdrs.begin()+i),lo_PMJobPtr->ga_RatedCdrs[i]);
							//i++;
							lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection="O";
							l_RatedCdrs_outleg.push_back(lo_PMJobPtr->ga_RatedCdrs[i]);						
							l_RatedCdrs_outleg[0].gs_CallDirection="O";
						//l_RatedCdrs_outleg[0].gs_CallDirection="0";
							update_CallTypeCounts(lo_PMJobPtr, l_RatedCdrs_outleg[0].gs_AgreementType,l_RatedCdrs_outleg[0].gn_CallType,l_RatedCdrs_outleg[0].gn_CallDuration,l_RatedCdrs_outleg[0].gs_CallDirection);
						
						// in case of call forward cdrs... move the b# in A# and C# into b#. Also set the dialled digits to C#
						if(!(l_RatedCdrs_outleg[0].gs_CNumber == "")) 
						{
							 if (lo_PMJobPtr->ga_RatedCdrs[i].gn_CallType == 3) 
							{			
							l_RatedCdrs_outleg[0].gs_ANumber		=	l_RatedCdrs_outleg[0].gs_BNumber;
							l_RatedCdrs_outleg[0].gs_BNumber		=	l_RatedCdrs_outleg[0].gs_CNumber;
							l_RatedCdrs_outleg[0].gs_DialledDigits	=	l_RatedCdrs_outleg[0].gs_CNumber;
							l_RatedCdrs_outleg[0].gs_CNumber	    =	"";
							}
						}
						// APN based rating. only when service code is 005 or 305
						//added as per LTE usage for 4.3 release
						//if(l_RatedCdrs_outleg[0].gs_ServiceCode=="005") 
						if((l_RatedCdrs_outleg[0].gs_ServiceCode=="005") || (l_RatedCdrs_outleg[0].gs_ServiceCode=="305"))
						//modifiction end
						{
							l_RatedCdrs_outleg[0].gs_BNumber = l_RatedCdrs_outleg[0].gs_ApnAddress.mb_subStr(0,25);
						}
						if(lobj_Temp_PM_RatingRulesCachePtr->mb_getOutLegAction()== "D")
						{
							ln_flag=0;
							
							ls_DropCode = "DROP-002";
							ls_DropMesg = "Rating action configured as D for the Outgoing Leg for the service code: ";
							ls_DropMesg +=l_RatedCdrs_outleg[0].gs_ServiceCode;
							ls_DropValue= l_RatedCdrs_outleg[0].gs_ServiceCode;

							throw  ABL_Exception(2,ls_DropMesg.c_str());																    
						}
						else if(lobj_Temp_PM_RatingRulesCachePtr->mb_getOutLegAction()== "J")
						{
							ls_RejMesg	=	"Parser rule missing in cdr  for Service=>";
							ls_RejMesg+=	l_RatedCdrs_outleg[0].gs_ServiceCode;
							ls_RejMesg+=	";Agreement=>";
							ls_RejMesg+=	l_RatedCdrs_outleg[0].gs_AgreementType;
							ls_CallType.mb_fromDouble(l_RatedCdrs_outleg[0].gn_CallType);
							ls_RejMesg+=	"Call Type=>";
							ls_RejMesg+=	ls_CallType;							
							ls_RejMesg+=	";Subs Type=>";
							ls_RejMesg+=	l_RatedCdrs_outleg[0].gs_SubscriberType; //Reject.
							throw   ABL_Exception(1,ls_RejMesg.c_str());
						}

						// if partner identifier is null, then drop the cdr								
						std::string ls_partnerIdentifiler= l_RatedCdrs_outleg[0].gs_RawCdr.mb_subStr(ln_FromPosOutField,ln_ToPosOutField-ln_FromPosOutField).c_str();
						mb_trim(ls_partnerIdentifiler);
						ls_partnerIdentifiler[ls_partnerIdentifiler.length()]='\0';
						l_RatedCdrs_outleg[0].gs_PartnerIdentifier =ls_partnerIdentifiler;		   
						if (l_RatedCdrs_outleg[0].gs_PartnerIdentifier =="" && strcmp(lo_PMJobPtr->ga_RatedCdrs[i].gs_SubscriberType.c_str(),"V") != 0)
						{ 
							  ln_flag=0;
							ls_DropCode = "DROP-002";
							ls_DropMesg = "OUT TRUNK Or IMSI not found for the Called Number: ";
							ls_DropMesg +=l_RatedCdrs_outleg[0].gs_BNumber;
							ls_DropValue = l_RatedCdrs_outleg[0].gs_BNumber;
							 throw   ABL_Exception(2,ls_DropMesg.c_str());
						}

						if(ln_flag==1)
						{
							la_RatedCdrs.push_back(l_RatedCdrs_outleg[0]);
						}
					}
					catch(ABL_Exception &e)
					{
						if(e.mb_getErrorCode() == 2)
			            {
							// Populate rejection details.
							//if(lo_PMJobPtr->ga_RatedCdrs[i].gs_StoreDroppedCdr== "Y")
							//{
								lr_DroppedCdr.gn_CallType			=	lo_PMJobPtr->ga_RatedCdrs[i].gn_CallType;
								lr_DroppedCdr.gs_CallDirection	=	lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection;
								lr_DroppedCdr.gs_AgreementType	=	lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType;
								lr_DroppedCdr.gn_InputFileId		=	lo_PMJobPtr->ga_RatedCdrs[i].gn_InputFileId;
								lr_DroppedCdr.gn_RecordNo			=	lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordNo;
								lr_DroppedCdr.gs_PartnerCode		=	"";
				  				lr_DroppedCdr.gs_DroppedCdr		=	lo_PMJobPtr->ga_RatedCdrs[i].gs_RawCdr;
				  				lr_DroppedCdr.gs_DropCode			=	ls_DropCode;
								lr_DroppedCdr.gn_CallDuration		=	lo_PMJobPtr->ga_RatedCdrs[i].gn_CallDuration;								
								lr_DroppedCdr.gs_ErrorMessage = ls_DropMesg;
								lr_DroppedCdr.gd_DroppedDate.mb_fromSysDate();
								lr_DroppedCdr.gd_CallDate =lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate;
								lr_DroppedCdr.gs_Status = "NEW";
								lr_DroppedCdr.gs_ErrorValue = ls_DropValue;
								lr_DroppedCdr.gs_UnitRate		=	"";
								lr_DroppedCdr.gs_StoreDroppedCdr	=	lo_PMJobPtr->ga_RatedCdrs[i].gs_StoreDroppedCdr;
								lo_PMJobPtr->ga_DroppedCdr.push_back(lr_DroppedCdr);
								//l_RatedCdrs_outleg.erase(l_RatedCdrs_outleg.begin(),l_RatedCdrs_outleg.end());
							//}
							continue;							
						 }
						 else if(e.mb_getErrorCode() == 1)
						 {
							// Populate rejection details.
							lr_RejectedCdrs.gn_CallType		=	l_RatedCdrs_outleg[0].gn_CallType;
							lr_RejectedCdrs.gs_CallDirection	=	l_RatedCdrs_outleg[0].gs_CallDirection;
							lr_RejectedCdrs.gs_AgreementType	=   l_RatedCdrs_outleg[0].gs_AgreementType;
							lr_RejectedCdrs.gn_FileId			=   l_RatedCdrs_outleg[0].gn_InputFileId; 
							lr_RejectedCdrs.gn_RecordNo		=   l_RatedCdrs_outleg[0].gn_RecordNo;
							lr_RejectedCdrs.gs_ErrorCdr		=	l_RatedCdrs_outleg[0].gs_RawCdr;
							//modified as per LTE usage for 4.3 release
                          				//lr_RejectedCdrs.gs_ErrorCode                =       "PARSEERROR";
                          				lr_RejectedCdrs.gs_ErrorCode          =       "RATE-RULES-NF";
                          				//modification end
							if(ls_RejMesg.mb_length()==0)
							 {
								lr_RejectedCdrs.gs_ErrorMessage=" error in apply rating rules. ";
							 }
							 else
							 {
								lr_RejectedCdrs.gs_ErrorMessage	=   ls_RejMesg;
							 }

							lr_RejectedCdrs.gd_RejectedDate.mb_fromSysDate();   
							lr_RejectedCdrs.gd_CallDate		=   l_RatedCdrs_outleg[0].gd_CallDate;
							lr_RejectedCdrs.gs_Status			=	"NEW";
							lr_RejectedCdrs.gs_ErrorValue		=   l_RatedCdrs_outleg[0].gs_BNumber;
                            				lr_RejectedCdrs.gn_CallDuration	=   l_RatedCdrs_outleg[0].gn_CallDuration;
							
							lr_RejectedCdrs.gs_ChronoNum	=   lo_PMJobPtr->ga_RatedCdrs[i].gs_ChronoNum;
							lr_RejectedCdrs.gn_PartialSeqNum  = lo_PMJobPtr->ga_RatedCdrs[i].gn_PartialSeqNum;
							lo_PMJobPtr->ga_RejectedCdrs.push_back(lr_RejectedCdrs);
							continue;
						 }
						 else
						 {
							// Populate rejection details.
							//modified as per LTE usage for 4.3 release
                          				//lr_RejectedCdrs.gs_ErrorCode                =       "PARSEERROR";
                          				lr_RejectedCdrs.gs_ErrorCode          =       "RATE-RULES-NF";
                          				//modification end
							if(ls_RejMesg.mb_length()==0)
							 {
								lr_RejectedCdrs.gs_ErrorMessage=" error in apply rating rules. ";
							 }
							 else
							 {
								lr_RejectedCdrs.gs_ErrorMessage	=   ls_RejMesg;
							 }
							lr_RejectedCdrs.gn_FileId			=   l_RatedCdrs_outleg[0].gn_InputFileId;
							lr_RejectedCdrs.gn_RecordNo		=   l_RatedCdrs_outleg[0].gn_RecordNo;
							lr_RejectedCdrs.gs_AgreementType	=   l_RatedCdrs_outleg[0].gs_AgreementType;
							lr_RejectedCdrs.gs_CallDirection	=	l_RatedCdrs_outleg[0].gs_CallDirection;
							lr_RejectedCdrs.gs_ErrorCdr		=	l_RatedCdrs_outleg[0].gs_RawCdr;
							lr_RejectedCdrs.gd_RejectedDate.mb_fromSysDate();  
							lr_RejectedCdrs.gs_Status			=	"NEW";
							lr_RejectedCdrs.gn_CallDuration	=   l_RatedCdrs_outleg[0].gn_CallDuration;
							lr_RejectedCdrs.gd_CallDate		=   l_RatedCdrs_outleg[0].gd_CallDate;
							lr_RejectedCdrs.gs_ChronoNum	=   lo_PMJobPtr->ga_RatedCdrs[i].gs_ChronoNum;
							lr_RejectedCdrs.gn_PartialSeqNum  = lo_PMJobPtr->ga_RatedCdrs[i].gn_PartialSeqNum;
							lo_PMJobPtr->ga_RejectedCdrs.push_back(lr_RejectedCdrs);						
							continue;
						 }

					}
					catch(...)
					{
						rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
						ABL_String l_command("touch ");
						l_command +=ms_Stopsignalfile;
						system(l_command.c_str()); 	
						*mo_ABLServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
						return false;
					}	
				 }
				 
			}
			else
			{
					ABL_String ls_RecordNo;
				// If rules are not present for the cdr then Reject the cdr
				ls_RejMesg	="Parser rule missing in cdr=>";
                ls_RecordNo.mb_fromDouble(lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordNo);
                ls_RejMesg+=	ls_RecordNo;
				ls_RejMesg+=	";For Service=>";
				ls_RejMesg+=	lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode;
			    ls_RejMesg+=	";Agreement=>";
				ls_RejMesg+=	lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType;
				ls_CallType.mb_fromDouble(lo_PMJobPtr->ga_RatedCdrs[i].gn_CallType);
                ls_RejMesg+=	"Call Type=>";
				ls_RejMesg+=ls_CallType;				
				ls_RejMesg+=	";Subs Type=>";
				ls_RejMesg+=	lo_PMJobPtr->ga_RatedCdrs[i].gs_SubscriberType;               
				throw   ABL_Exception(1,ls_RejMesg.c_str());
			}
    }		
    catch(ABL_Exception &e)
	{
		if(e.mb_getErrorCode() == 1)
        {
			  // Populate rejection details.
              lr_RejectedCdrs.gn_CallType			=	lo_PMJobPtr->ga_RatedCdrs[i].gn_CallType;
			  lr_RejectedCdrs.gs_CallDirection	=	lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection;
			  lr_RejectedCdrs.gs_AgreementType	=   lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType;
			  lr_RejectedCdrs.gn_FileId			=   lo_PMJobPtr->ga_RatedCdrs[i].gn_InputFileId; 
			  lr_RejectedCdrs.gn_RecordNo			=   lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordNo;
			  lr_RejectedCdrs.gs_ErrorCdr			=   lo_PMJobPtr->ga_RatedCdrs[i].gs_RawCdr;
			  //modified as per LTE usage for 4.3 release
			  //lr_RejectedCdrs.gs_ErrorCode		=	"PARSEERROR";
			  lr_RejectedCdrs.gs_ErrorCode          =       "RATE-RULES-NF";
			  //modification end
			if(ls_RejMesg.mb_length()==0)
			 {
				lr_RejectedCdrs.gs_ErrorMessage=" error in apply rating rules. ";
			 }
			 else
			 {
				lr_RejectedCdrs.gs_ErrorMessage	=   ls_RejMesg;
			 }
			  lr_RejectedCdrs.gd_RejectedDate.mb_fromSysDate();   
			  lr_RejectedCdrs.gd_CallDate			=   lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate;
			  lr_RejectedCdrs.gs_Status			=	"NEW";              
			  lr_RejectedCdrs.gs_ErrorValue		=   lo_PMJobPtr->ga_RatedCdrs[i].gs_BNumber;
        	  	  lr_RejectedCdrs.gn_CallDuration		=   lo_PMJobPtr->ga_RatedCdrs[i].gn_CallDuration;
			  lr_RejectedCdrs.gs_ChronoNum	=   lo_PMJobPtr->ga_RatedCdrs[i].gs_ChronoNum;
			  lr_RejectedCdrs.gn_PartialSeqNum  = lo_PMJobPtr->ga_RatedCdrs[i].gn_PartialSeqNum;
	  		  lo_PMJobPtr->ga_RejectedCdrs.push_back(lr_RejectedCdrs);
			 
		}	 
		else					
		{
			  // Populate rejection details.
			  lr_RejectedCdrs.gn_CallType			=	lo_PMJobPtr->ga_RatedCdrs[i].gn_CallType;
			  lr_RejectedCdrs.gs_CallDirection	=	lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection;
			  lr_RejectedCdrs.gs_AgreementType	=   lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType;
			  lr_RejectedCdrs.gn_FileId			=   lo_PMJobPtr->ga_RatedCdrs[i].gn_InputFileId; 
			  lr_RejectedCdrs.gn_RecordNo			=   lo_PMJobPtr->ga_RatedCdrs[i].gn_RecordNo;
			  lr_RejectedCdrs.gs_ErrorCdr			=	lo_PMJobPtr->ga_RatedCdrs[i].gs_RawCdr;
			  //modified as per LTE usage for 4.3 release
                          //lr_RejectedCdrs.gs_ErrorCode                =       "PARSEERROR";
                          lr_RejectedCdrs.gs_ErrorCode          =       "RATE-RULES-NF";
                          //modification end
				if(ls_RejMesg.mb_length()==0)
				 {
					lr_RejectedCdrs.gs_ErrorMessage=" error in apply rating rules. ";
				 }
				 else
				 {
					lr_RejectedCdrs.gs_ErrorMessage	=   ls_RejMesg;
				 }
			  lr_RejectedCdrs.gd_RejectedDate.mb_fromSysDate();
			  lr_RejectedCdrs.gd_CallDate			=   lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate;
			  lr_RejectedCdrs.gs_Status			=	"NEW";              
			  lr_RejectedCdrs.gs_ErrorValue		=   lo_PMJobPtr->ga_RatedCdrs[i].gs_BNumber;
              		  lr_RejectedCdrs.gn_CallDuration		=   lo_PMJobPtr->ga_RatedCdrs[i].gn_CallDuration;
	  		  lr_RejectedCdrs.gs_ChronoNum	=   lo_PMJobPtr->ga_RatedCdrs[i].gs_ChronoNum;
			  lr_RejectedCdrs.gn_PartialSeqNum  = lo_PMJobPtr->ga_RatedCdrs[i].gn_PartialSeqNum;
			  lo_PMJobPtr->ga_RejectedCdrs.push_back(lr_RejectedCdrs);
			 
		}
		
	}
	catch(...)
	{
		rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str()); 	
		*mo_ABLServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}	

 }//End of cdr for loop.
}//End of agreement for loop

 lo_PMJobPtr->ga_RatedCdrs.clear();
 lo_PMJobPtr->ga_RatedCdrs.insert(lo_PMJobPtr->ga_RatedCdrs.begin(), la_RatedCdrs.begin(), la_RatedCdrs.end()); 
 //la_RatedCdrs.clear();
 *mo_ABLServicePtr <<DEBUG<<"End  :" << lo_PMJobPtr->gs_fileName <<": "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;
}
catch(ABL_Exception &e)
{
	*mo_ABLServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;
	ABL_String ls_command("touch ");
	ls_command +=ms_Stopsignalfile;
	system(ls_command.c_str());  
	return false;
 }
catch(...)
{
			rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str()); 	
		*mo_ABLServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
}	
	return true;
}


bool PM_ApplyRatingRules::mb_stop()
{
	return true;
}

void PM_ApplyRatingRules::update_CallTypeCountsTot(PM_Job * &p_ABL_JobPtr, ABL_String AgreementType, int CallType, double CallDuration)
{
	PM_Job* l_PM_Job_Local = (PM_Job*)p_ABL_JobPtr;	

		ABL_String	ls_TempConvert="";
		ABL_String  ls_agreementtype_calltype=AgreementType;
		ls_TempConvert.mb_fromDouble(CallType);
		ls_agreementtype_calltype+=ls_TempConvert;
		l_PM_Job_Local->gi_CallTypeCountsMapIterator=l_PM_Job_Local->ga_CallTypeCountsMap.find(ls_agreementtype_calltype);
		if(l_PM_Job_Local->gi_CallTypeCountsMapIterator!=l_PM_Job_Local->ga_CallTypeCountsMap.end())
		{
			l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalCount = l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalCount + 1;				
			l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalDuration  = l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalDuration + CallDuration;			

		}
		
}


/*Function to calculate counts based on call type.*/
void PM_ApplyRatingRules::update_CallTypeCounts(PM_Job * &p_ABL_JobPtr, ABL_String AgreementType, int CallType, double CallDuration, ABL_String CallDirection)
{
	PM_Job* l_PM_Job_Local = (PM_Job*)p_ABL_JobPtr;	

	
		ABL_String	ls_TempConvert="";
		ABL_String  ls_agreementtype_calltype=AgreementType;
		ls_TempConvert.mb_fromDouble(CallType);
		ls_agreementtype_calltype+=ls_TempConvert;

		l_PM_Job_Local->gi_CallTypeCountsMapIterator=l_PM_Job_Local->ga_CallTypeCountsMap.find(ls_agreementtype_calltype);
		if(l_PM_Job_Local->gi_CallTypeCountsMapIterator!=l_PM_Job_Local->ga_CallTypeCountsMap.end())
		{
			if(CallDirection=="I")
			{
				l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalIncCount=l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalIncCount+1;
				l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalIncDuration=l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalIncDuration +CallDuration;               
			}
			else
			{
				l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalOutCount =l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalOutCount+1;
				l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalOutDuration=l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalOutDuration+CallDuration;
			}

			if(CallType == 5)
			{
				 l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalDuration  = l_PM_Job_Local->gi_CallTypeCountsMapIterator->second.gn_TotalIncDuration;
			}

		}

}
void PM_ApplyRatingRules::update_ATypeRatingLog(PM_Job * &p_ABL_JobPtr, ABL_String AgreementType)
{

		PM_Job* l_PM_Job_Local = (PM_Job*)p_ABL_JobPtr;
		l_PM_Job_Local->gi_ATypeLogMapIterator=l_PM_Job_Local->ga_ATypeLogMap.find(AgreementType);
		if(l_PM_Job_Local->gi_ATypeLogMapIterator!=l_PM_Job_Local->ga_ATypeLogMap.end())
		{
			l_PM_Job_Local->gi_ATypeLogMapIterator->second.gn_TotalCdrs=l_PM_Job_Local->gi_ATypeLogMapIterator->second.gn_TotalCdrs+1;
		}


}

/*Fuction to calculate the staring position based on search string(|) in a string to be seached (string to be searched is Raw Cdr).*/
int PM_ApplyRatingRules::GetFrom_Pos( ABL_String str,int nthoccurence )
{
    std::string ls_objstring=str.mb_getSTLString ();
	int ln_size =0;
	int ln_TempNum=0,ln_frompos=0,ln_temp=0;
    int ln_tempValue = 1;
    std::string ::size_type ln_pos = 0;
   		while(ln_tempValue<nthoccurence)
		{
		    ln_pos = ls_objstring.find( "|");
			ln_temp=ln_TempNum=ln_pos;
			ln_TempNum=ln_TempNum+1;
			if(ln_pos!=std::string::npos)
			{
                ln_frompos=ln_frompos+ln_TempNum;            
			}			
			ls_objstring=ls_objstring.substr(ln_temp+1,(ls_objstring.size()-ln_pos));
			ln_tempValue++;	   
		}		      
    return ln_frompos;
}

/*Fuction to calculate the staring position based on search string(|) in a string to be seached.*/
int PM_ApplyRatingRules::GetTo_Pos(  ABL_String str,int nthoccurence )
 {
	std::string ls_objstring=str.mb_getSTLString ();
	int ln_size =0;
	int ln_TempNum=0,topos=0,ln_temp=0;
    int ln_tempValue = 1;
    std::string ::size_type ln_pos = 0;
  		while(ln_tempValue<=nthoccurence)
		{
		    ln_pos = ls_objstring.find( "|");
			ln_temp=ln_TempNum=ln_pos;
			ln_TempNum=ln_TempNum+1;
			if(ln_pos!=std::string::npos)
			{
                topos=topos+ln_TempNum;            
			}			
			ls_objstring=ls_objstring.substr(ln_temp+1,(ls_objstring.size()-ln_pos));
			ln_tempValue++;	   
		}		      
    return topos-1;
}

/*Fuction to remove the leading n trailing spaces in a string.*/
void PM_ApplyRatingRules::mb_trim(std::string &p_string)
{
		bool l_leftSpace = false;
        bool l_rightSpace = false;

        for(size_t l_icount = 0;l_icount < p_string.size(); ++l_icount)
        {
                if(' ' != p_string[l_icount]/* && '\t' != p_string[l_icount] && '\r' != p_string[l_icount]*/)
                {
                        p_string = p_string.substr(l_icount);
                        l_leftSpace = true;
                        break;
                }
        }

        for(int l_icount = (int)(p_string.size() - 1); l_icount >= 0; --l_icount)
        {
                if(' ' != p_string[l_icount]/* && '\t' != p_string[l_icount] && '\r' != p_string[l_icount]*/)
                {
                        p_string = p_string.substr(0, l_icount+1);
                        l_rightSpace = true;
                        break;
                }
        }

        if( l_leftSpace == false && l_rightSpace == false)
        {

                p_string = p_string.substr(0,1);
				p_string="";
        }

}
