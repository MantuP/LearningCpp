#include "PM_ParseRawEvent.h"
#include <limits>

extern "C" 
{
	EXPORT Base_Registry* gb_getPM_ParseRawEvent()
	{
		return ( (Base_Registry*) new PM_ParseRawEvent);
	}
}

PM_ParseRawEvent::PM_ParseRawEvent()
{
//
}

PM_ParseRawEvent::~PM_ParseRawEvent()
{
//
}

PM_ParseRawEvent::PM_ParseRawEvent(const PM_ParseRawEvent& p_copyObject)
{
	this->m_ABL_ServicePtr				=	p_copyObject.m_ABL_ServicePtr;
	this->md_MinCallDate				=	p_copyObject.md_MinCallDate	;
	this->md_MaxCallDate				=	p_copyObject.md_MaxCallDate;
	this->ms_Stopsignalfile				=	p_copyObject.ms_Stopsignalfile;
	this->ms_NeCode						=	p_copyObject.ms_NeCode;
}

Base_Registry* PM_ParseRawEvent::mb_clone()
{
	return ( (Base_Registry*) new PM_ParseRawEvent );
}

ABL_Process* PM_ParseRawEvent::mb_createCopy()
{
	return ( new PM_ParseRawEvent (*this));
}

bool PM_ParseRawEvent::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{
	try
	{
		m_ABL_ServicePtr			= p_ABL_ServicePtr;
		p_ABL_AgentCommunicatorPtr->mb_getParameter("STOP_FILE",ms_Stopsignalfile);
	}   
	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;	
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
		*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}
	return true;
}

bool PM_ParseRawEvent::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	return true;
}

bool PM_ParseRawEvent::mb_process(ABL_Job* &p_ABL_JobPtr)
{
	PM_Job* lo_PMJobPtr    = (PM_Job*)p_ABL_JobPtr;
	ABL_String ls_CdrValue ;
	lo_PMJobPtr->gn_TotalCDRS_In_File=0;			
	try
	{
		ms_NeCode="";
		if (lo_PMJobPtr->ga_RawCDRSVector.size()== 0) 
		{
			if (lo_PMJobPtr->gs_IsGPRSFile=="YES")
			{
				return true;
			}
			else
			{
				*m_ABL_ServicePtr << DEBUG <<" There are no cdrs to parse: " <<lo_PMJobPtr->gs_fileName<<Endl;	
				return false;          
			}
		}
		*m_ABL_ServicePtr << DEBUG<< "Start :" <<lo_PMJobPtr->gs_fileName <<" : "<<lo_PMJobPtr->ga_RawCDRSVector.size()<< Endl;

		ABL_String lmaxdate="00010101000000";
		md_MinCallDate.mb_fromSysDate();
		md_MaxCallDate.mb_fromText(lmaxdate.c_str(),YYYYMMDDHH24MISS);

		for(int ln_cdrCount=0;ln_cdrCount<lo_PMJobPtr->ga_RawCDRSVector.size() ;ln_cdrCount++)
		{
			ls_CdrValue="";
			ls_CdrValue=lo_PMJobPtr->ga_RawCDRSVector[ln_cdrCount];
			fnValidateCdr(lo_PMJobPtr,ls_CdrValue,ln_cdrCount+1,lo_PMJobPtr->gn_InPutFileId);
		}

		lo_PMJobPtr->gn_TotalCDRS_In_File=lo_PMJobPtr->ga_RawCDRSVector.size();

		if(md_MaxCallDate.mb_toString()=="")
		{
			lo_PMJobPtr->ga_RatingLog[0].gd_LastCallDtTime.mb_fromSysDate();
		}
		else
		{
			lo_PMJobPtr->ga_RatingLog[0].gd_LastCallDtTime  =  md_MaxCallDate;	
		}

		if(md_MinCallDate.mb_toString()=="")
		{
			lo_PMJobPtr->ga_RatingLog[0].gd_FirstCallDtTime.mb_fromSysDate();
		}
		else
		{
			lo_PMJobPtr->ga_RatingLog[0].gd_FirstCallDtTime =  md_MinCallDate;  
		}

		//lo_PMJobPtr->ga_RawCDRSVector.clear();
		*m_ABL_ServicePtr<<DEBUG<<"End  :" << lo_PMJobPtr->gs_fileName <<": "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;
	}
	catch(ABL_Exception &e)
	{
		rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
		*m_ABL_ServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;
		ABL_String ls_command("touch ");
		ls_command +=ms_Stopsignalfile;
		system(ls_command.c_str());  
		return false;
	}
	catch(...)
	{
		rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
		ABL_String ls_command("touch ");
		ls_command +=ms_Stopsignalfile;
		system(ls_command.c_str()); 	
		*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}
	return true;
}

bool PM_ParseRawEvent::mb_stop()
{
	return true;
}

int  PM_ParseRawEvent :: fnValidateCdr(PM_Job * &p_ABL_JobPtr,ABL_String in_RawCdr,long in_RecordNo,unsigned int in_FileID)
{
	ABL_String		ls_ParseIncLeg = "Y";
	ABL_String		ls_ParseOutLeg = "Y";
	ABL_String		ls_RejCode = "";
	ABL_String		ls_RejMesg = "";	
	ABL_String		ls_TempMesg = "";

	gr_RatedCdr		lr_RawCdr;
	gr_RejectedCdr		lr_RejectedCdr;
	ABL_String		ls_Agreement="";

	const char *ls_StrPos;
	/* Fields are separated by the delimitor character. in this case it is |.*/
	/* Fetch the field value between two pipes.*/

	const std::string ls_delimit="|";
	int l=0;
	std::vector<std::string> lv_tokens;

	try
	{	
		if(in_RawCdr.mb_length() <=0 )
		{
			return false;
		}

		lr_RawCdr.gn_CallType=0;
		lr_RawCdr.gs_ServiceCode="";
		lr_RawCdr.gs_NeCode ="";
		lr_RawCdr.gs_InRoute="";
		lr_RawCdr.gs_OutRoute="";
		lr_RawCdr.gs_Imsi="";
		lr_RawCdr.gs_SgsnAddress="";
		lr_RawCdr.gs_ANumber="";
		lr_RawCdr.gs_BNumber="";
		lr_RawCdr.gs_CNumber="";
		lr_RawCdr.gs_ApnAddress="";
		lr_RawCdr.gs_PdpAddress="";
		lr_RawCdr.gd_CallDate;		
		lr_RawCdr.gn_CallDuration=0;
		lr_RawCdr.gn_DataVolume_inc=0;
		lr_RawCdr.gn_DataVolume_out=0;
		lr_RawCdr.gs_Teleservice="";
		lr_RawCdr.gs_Bearerservice="";
		lr_RawCdr.gs_CamelFlag="";
		lr_RawCdr.gn_CamelService_level="";
		lr_RawCdr.gn_CamelService_key="";
		lr_RawCdr.gn_CamelDefault_call_handling="";
		lr_RawCdr.gs_CamelServer_address="";
		lr_RawCdr.gs_CamelMsc_address="";
		lr_RawCdr.gs_CamelCall_ref_num="";
		lr_RawCdr.gn_CamelInit_cf_indicator="";
		lr_RawCdr.gs_CamelDestination_num="";
		lr_RawCdr.gs_CamelModification="";
		lr_RawCdr.gs_SupplimentaryNum="";
		lr_RawCdr.gn_NetworkTime=0;
		lr_RawCdr.gn_ReasonForCleardown=0;
		lr_RawCdr.gs_PartialIndicator="";
		lr_RawCdr.gn_PartialSeqNum=0;
		lr_RawCdr.gs_ImeiNum="";
		lr_RawCdr.gs_ChronoNum="";
		lr_RawCdr.gn_ChargingId="";
		lr_RawCdr.gs_SubscriberType="";
		lr_RawCdr.gs_AgreementType="";
		lr_RawCdr.gs_PartnerCode="";
		lr_RawCdr.gs_CallDirection="";
		lr_RawCdr.gs_Poi="";
		lr_RawCdr.gs_OriginRateZone="";
		lr_RawCdr.gs_DestinationRateZone="";
		lr_RawCdr.gs_DayCode="";
		lr_RawCdr.gs_TimeType="";
		lr_RawCdr.gs_TariffPlanCode="";
		lr_RawCdr.gn_TariffId=0;
		lr_RawCdr.gn_Unit_rate=0;
		lr_RawCdr.gn_ChargeableUnits=0;
		lr_RawCdr.gn_ChargedUnits=0;
		lr_RawCdr.gn_ChargeAmount=0.10;
		lr_RawCdr.gn_TaxAmount=0;
		lr_RawCdr.gn_SummarySeqNo=0;
		lr_RawCdr.gd_RatedOn.mb_fromSysDate();
		lr_RawCdr.gn_RevenueAmount=0;
		lr_RawCdr.gs_Status="";
		lr_RawCdr.gn_RepriceSeqNo=0;
		lr_RawCdr.gs_NumberPlanCode="";
		lr_RawCdr.gs_RateDirection="";
		lr_RawCdr.gs_PaymentDirection="";
		lr_RawCdr.gn_InputFileId=0;
		lr_RawCdr.gs_RateUnit="";
		lr_RawCdr.gs_PartnerIdentifier="";
		lr_RawCdr.gs_RoamingStatus="";
		lr_RawCdr.gn_TempSequenceNumber=0;
		lr_RawCdr.gn_FileSequenceNumber=0;
		lr_RawCdr.gs_CellId="";
		lr_RawCdr.gs_DataTypeIndicator="";
		lr_RawCdr.gn_DiscountAmount=0;
		lr_RawCdr.gn_ChargeSdr=0;
		lr_RawCdr.gn_DiscountSdr=0;
		lr_RawCdr.gn_TaxSdr=0;
		lr_RawCdr.gn_CamelFee=0;
		lr_RawCdr.gn_CamelFeeSdr=0;
		lr_RawCdr.gn_CamelTaxAmount=0;
		lr_RawCdr.gn_CamelTaxSdr=0;
		lr_RawCdr.gn_CamelDiscountAmount=0;
		lr_RawCdr.gn_CamelDiscountSdr=0;
		lr_RawCdr.gs_DestinationType="";
		lr_RawCdr.gs_DestinationSubType="";
		lr_RawCdr.gn_RecordingEntityType=0;
		lr_RawCdr.gs_ChargeType="00";
		lr_RawCdr.gs_ServiceType="";
		lr_RawCdr.gs_RoamingErrorCode="";
		lr_RawCdr.gs_CallTypeLevel3="";
		lr_RawCdr.gn_HomeExchangeRateCode=0;
		lr_RawCdr.gn_TapExchangeRateCode=0;
		lr_RawCdr.gn_ExchangeRate=0;
		lr_RawCdr.gn_TapTaxCode="";
		lr_RawCdr.gn_TapDiscountCode="";
		lr_RawCdr.gn_TapRecordingEntityCode="";
		lr_RawCdr.gn_TapUtcOffsetCode="";
		lr_RawCdr.gn_DiscountableAmount="";
		lr_RawCdr.gn_DiscountableAmountSdr="";
		lr_RawCdr.gn_TotalUnits=0; 
		lr_RawCdr.gn_SupplemantryActionCode=0; 
		lr_RawCdr.gs_SupplimentaryActionCode="";
		lr_RawCdr.gs_OriginDestinationType="";               
		lr_RawCdr.gs_rate="";
		lr_RawCdr.gn_unitQty=0;		
		lr_RawCdr.gs_BrokerCountryCode="";
		lr_RawCdr.gs_AppOwner	="";
		lr_RawCdr.gs_AllowIcTraffic="";
		lr_RawCdr.gs_ApplyDflRate_rate_on_trunk="";
		lr_RawCdr.gs_tobe_rated="";
		lr_RawCdr.gn_InitialFreeUnits=0;
		lr_RawCdr.gn_MinChargeableUnits=0;
		lr_RawCdr.gn_InitialFlatAmt=0;
		lr_RawCdr.gn_MinAmt=0;              
		lr_RawCdr.gs_DialledDigits="";
		lr_RawCdr.gn_RecordingEntityType_SGSN=0;
		lr_RawCdr.gn_TapRecordingEntityCode_SGSN=0;
		lr_RawCdr.gs_DerivedServiceCode="";
		lr_RawCdr.gs_CurrencyCode="";
		lr_RawCdr.gs_InvoiceEvent="";
		lr_RawCdr.gn_RecordNo=0;
		lr_RawCdr.gs_LcrDestination="";
		lr_RawCdr.gs_ErrorCode ="";
		lr_RawCdr.gs_ErrorMessage="";		
		lr_RawCdr.gs_RawCdr="";			
		lr_RawCdr.gs_Charge_SMSMO_SMSC_flg="";
		lr_RawCdr.gs_RatingType="";
		lr_RawCdr.gs_time_type_temp="";
		lr_RawCdr.gs_duration_tmp ="";
		lr_RawCdr.gs_UtcOffset="";
		lr_RawCdr.gs_PartnerIdentifierKey="";
		lr_RawCdr.gs_StoreDroppedCdr="";
		lr_RawCdr.gn_MultFactor=0;
		ls_Agreement="I";
		lr_RawCdr.gs_ErrorCode="";
		lr_RawCdr.gs_ErrorMessage=""; 
		lr_RawCdr.gs_ErrorValue="";
		lr_RawCdr.gs_RDStatus="";
		lr_RawCdr.gs_Rate="";
		lr_RawCdr.gs_Mnp="";

		//added as per LTE usage for 4.3 release
		lr_RawCdr.gs_AUserId="";
		lr_RawCdr.gs_BUserId="";
		lr_RawCdr.gs_EventReference="";
		lr_RawCdr.gs_APN_OperatorId="";
		lr_RawCdr.gs_PCSCF_Address="";
		lr_RawCdr.gn_NetworkElementType1=0;
		lr_RawCdr.gn_NetworkElementType2=0;
		lr_RawCdr.gn_RecordingEntityTypePCSCF=0;
		lr_RawCdr.gn_TAP_RecordingEntityCodePCSCF=0;

		lr_RawCdr.gs_origin_sub_type="";
		lr_RawCdr.gs_origin_traffic_type="";
		lr_RawCdr.gs_destination_traffic_type="";
		lr_RawCdr.gs_Network_Call_Ref="";
		//modification end

		/* *m_ABL_ServicePtr << DEBUG << "Before Tokenizing Raw CDR for the file : " << lo_PMJobPtr->gs_fileName << Endl;*/
		std::vector<std::string>l_tokens;
		tokenize(in_RawCdr.c_str(),l_tokens,ls_delimit);		
		int cdr_file_col=m_ABL_ServicePtr->mb_getInt("NUMBER_OF_COLUMNS_IN_FILE");
		int token_size=l_tokens.size();

		//Added as per LTE usage for 4.3 release
		/*if(cdr_file_col!=l_tokens.size())
		{
			ls_RejMesg="File format not correct,Kindly check the cdr lenght";
			*m_ABL_ServicePtr << DEBUG << "CDR file columns "<<cdr_file_col<<" Token size "<<l_tokens.size()<<"in_RawCdr.mb_length "<<in_RawCdr.mb_length()<< Endl;
			throw  ABL_Exception(-3,ls_RejMesg.c_str());
		} */

		std::stringstream l_stringStream(in_RawCdr.c_str());
		std::string ls_tokenStringDataVol;
		std::size_t pos_of_dot;
		std::string ls_tokenString;
		std::string ls_tempValue;
		l=0;

		while(std::getline(l_stringStream,ls_tokenString,ls_delimit[0]))
		{
			mb_trim(ls_tokenString);
			//std::cout<<" Value : "<<ls_tokenString<<" value of field: "<<l<<std::endl;
			switch(l)
			{
				//check call type
				case 0:						
					lr_RawCdr.gn_CallType=atoi(ls_tokenString.c_str());
					ls_TempMesg.mb_fromInt(lr_RawCdr.gn_CallType);

					//default values
					if(lr_RawCdr.gn_CallType == 1)
					{
						lr_RawCdr.gs_CallDirection = "I";
					}
					else
					{
						lr_RawCdr.gs_CallDirection ="O";
					}

					//if(ls_TempMesg.mb_length()>2)
					//added as per LTE usage for 4.3 release. Call type must not be empty
					if((ls_TempMesg.mb_length()>1) || (lr_RawCdr.gn_CallType == 0))
					//modification end
					{
						ls_RejMesg="Invalid or null value for Call Type - ";
						ls_TempMesg= "";
						ls_RejMesg+=ls_TempMesg;
						throw ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get service code
				case 1:
					lr_RawCdr.gs_ServiceCode  = ls_tokenString;	
					//service code must not be empty. servicecode will always 3 chars long			
					//if(lr_RawCdr.gs_ServiceCode == " " || lr_RawCdr.gs_ServiceCode.mb_length() > 3)
					//added as per LTE usage for 4.3 release
					if(lr_RawCdr.gs_ServiceCode.mb_length() != 3)
					//modification end
					{
						ls_RejMesg="Invalid value for Service Code - ";
						ls_RejMesg+=lr_RawCdr.gs_ServiceCode;	
						throw  ABL_Exception(-1,ls_RejMesg.c_str());	
					}
					break;

				//get ne code
				case 2:
					lr_RawCdr.gs_NeCode  = ls_tokenString;			
					ls_StrPos=strchr(lr_RawCdr.gs_NeCode.c_str(),' ');
					lr_RawCdr.gs_NeCode=lr_RawCdr.gs_NeCode.mb_subStr(0,ls_StrPos-lr_RawCdr.gs_NeCode.c_str());
					//if(lr_RawCdr.gs_NeCode.mb_length() > 45)
					//added as per LTE usage for 4.3 release. Ne_code must not be empty
					if((lr_RawCdr.gs_NeCode.mb_length() > 45)|| (ls_tokenString == ""))
					//modification end
					{
						ls_RejMesg="Invalid or null value for Network Element Code- ";
						ls_RejMesg+=lr_RawCdr.gs_NeCode;					
						throw  ABL_Exception(-1,ls_RejMesg.c_str());	
					}

					break;

				//get inroute
				case 3:
					lr_RawCdr.gs_InRoute =ls_tokenString;
					//Added as per LTE usage for 4.3 release
					//if(lr_RawCdr.gs_InRoute.mb_length() > 30)
					if(lr_RawCdr.gs_InRoute.mb_length() > 63)
					//modification end
					{
						ls_RejMesg="Invalid value for Incoming Route - ";
						ls_RejMesg+=lr_RawCdr.gs_InRoute;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get outroute
				case 4:
					lr_RawCdr.gs_OutRoute  = ls_tokenString;					
					//Added as per LTE usage for 4.3 release
					//if(lr_RawCdr.gs_OutRoute.mb_length() > 30)
					if(lr_RawCdr.gs_OutRoute.mb_length() > 63)
					//modificaton end
					{
						ls_RejMesg="Invalid value for Outgoing Route - ";
						ls_RejMesg+=lr_RawCdr.gs_OutRoute;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get imsi
				case 5:
				lr_RawCdr.gs_Imsi  = ls_tokenString;
				if(lr_RawCdr.gs_Imsi.mb_length() > 20)
				{
					ls_RejMesg="Invalid value for IMSI - ";
					ls_RejMesg+=lr_RawCdr.gs_Imsi;
					throw  ABL_Exception(-1,ls_RejMesg.c_str());
				}
				break;

				//get SGSN
				case 6:
					lr_RawCdr.gs_SgsnAddress  =  ls_tokenString;				
					//modified as per LTE usage for 4.3 release
					//if(lr_RawCdr.gs_SgsnAddress.mb_length() > 45)
					if((lr_RawCdr.gs_SgsnAddress.mb_length() > 45)||
					(lr_RawCdr.gs_SgsnAddress.mb_length()==0 &&
					(lr_RawCdr.gs_ServiceCode=="300" ||
					lr_RawCdr.gs_ServiceCode=="301" ||
					lr_RawCdr.gs_ServiceCode=="302" )))
					{
						ls_RejMesg="Invalid or null value for SGSN Address- ";
						ls_RejMesg+=lr_RawCdr.gs_SgsnAddress;	
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get A number
				case 7:
					lr_RawCdr.gs_ANumber  =  ls_tokenString;													
					if(lr_RawCdr.gs_ANumber.mb_length() > 25)
					{
						ls_RejMesg="Invalid value for A# - ";
						ls_RejMesg+=lr_RawCdr.gs_ANumber;			
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get B number
				case 8:
					lr_RawCdr.gs_BNumber=ls_tokenString;					
					if(lr_RawCdr.gs_BNumber.mb_length() > 25)
					{
						ls_RejMesg="Invalid value for B# - ";
						ls_RejMesg+=lr_RawCdr.gs_BNumber;	
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get C number
				case 9:
					lr_RawCdr.gs_CNumber=ls_tokenString;				
					if(lr_RawCdr.gs_CNumber.mb_length() > 25)
					{
						ls_RejMesg="Invalid value for C# - ";
						ls_RejMesg+=lr_RawCdr.gs_CNumber;	
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get APN address 
				case 10:
					lr_RawCdr.gs_ApnAddress=ls_tokenString;				
					if(lr_RawCdr.gs_ApnAddress.mb_length() > 65)
					{
						ls_RejMesg="Invalid value for APN - ";
						ls_RejMesg+=lr_RawCdr.gs_ApnAddress;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get PDP address
				case 11:
					lr_RawCdr.gs_PdpAddress  =ls_tokenString;				
					if(lr_RawCdr.gs_PdpAddress.mb_length() > 30)
					{
						ls_RejMesg="Invalid value for PDP - ";
						ls_RejMesg+=lr_RawCdr.gs_PdpAddress;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get call date
				case 12:
					{
						ABL_String ls_TempCallDate=ls_tokenString;
						if(ls_TempCallDate=="")
						{
							ls_RejMesg="Invalid value for Call Date - ";
							ls_RejMesg+=ls_TempMesg;
							throw  ABL_Exception(-1,ls_RejMesg.c_str());
						}

						lr_RawCdr.gd_CallDate.mb_fromText(ls_TempCallDate.c_str(),YYYYMMDDHH24MISS);				
						ls_TempMesg=lr_RawCdr.gd_CallDate.mb_toString();				
						if(ls_TempMesg.mb_length()!= 14)
						{
							ls_RejMesg="Invalid value for Call Date - ";
							ls_RejMesg+=ls_TempMesg;
							throw  ABL_Exception(-1,ls_RejMesg.c_str());
						}
						break;
					}

				//get call duration
				case 13:
					lr_RawCdr.gn_CallDuration  =  atoi(ls_tokenString.c_str());
					ls_TempMesg.mb_fromInt(lr_RawCdr.gn_CallDuration);
					if(ls_TempMesg.mb_length()>10)
					{
						ls_RejMesg="Invalid value for Call Duration - ";
						ls_RejMesg+=ls_TempMesg;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get data volume incoming 
				case 14:
					lr_RawCdr.gn_DataVolume_inc  =  atof(ls_tokenString.c_str());
					ls_TempMesg.mb_fromDouble(lr_RawCdr.gn_DataVolume_inc);
					ls_tokenStringDataVol = ls_TempMesg.c_str();
					pos_of_dot= ls_tokenStringDataVol.find(".");
					ls_tokenStringDataVol=ls_tokenStringDataVol.substr (0,pos_of_dot-1);
					if(ls_tokenStringDataVol.length()>15)
					{
						ls_RejMesg="Invalid value for Data Volume Incoming - ";
						ls_RejMesg+=ls_TempMesg;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get data volume outgoing
				case 15:
					lr_RawCdr.gn_DataVolume_out  =  atof(ls_tokenString.c_str());
					ls_TempMesg.mb_fromDouble(lr_RawCdr.gn_DataVolume_out);
					ls_tokenStringDataVol = ls_TempMesg.c_str();
					pos_of_dot= ls_tokenStringDataVol.find(".");
					ls_tokenStringDataVol=ls_tokenStringDataVol.substr (0,pos_of_dot-1);
					if(ls_tokenStringDataVol.length()>15)
					{
						ls_RejMesg="Invalid value for Data Volume Outgoing - ";
						ls_RejMesg+=ls_TempMesg;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get teleservice 
				case 16:
					lr_RawCdr.gs_Teleservice=ls_tokenString;
					if(lr_RawCdr.gs_Teleservice.mb_length() > 2)
					{
						ls_RejMesg="Invalid value for Teleservice - ";
						ls_RejMesg+=lr_RawCdr.gs_Teleservice;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get bearer service 
				case 17:
					lr_RawCdr.gs_Bearerservice=ls_tokenString;
					if(lr_RawCdr.gs_Bearerservice.mb_length() > 2)
					{
						ls_RejMesg="Invalid value for Bearer Service - ";
						ls_RejMesg+=lr_RawCdr.gs_Bearerservice;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get camel flag
				case 18:
					lr_RawCdr.gs_CamelFlag=ls_tokenString;
					if(lr_RawCdr.gs_CamelFlag.mb_length() > 1)
					{
						ls_RejMesg="Invalid value for CAMEL flag - ";
						ls_RejMesg+=lr_RawCdr.gs_CamelFlag;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get camel service level
				case 19:
					lr_RawCdr.gn_CamelService_level	 =	ls_tokenString;

					ls_tempValue="";//=lr_RawCdr.gn_CamelService_level.mb_getSTLString ();
					ls_tempValue=lr_RawCdr.gn_CamelService_level.mb_getSTLString ();
					mb_trim(ls_tempValue);
					lr_RawCdr.gn_CamelService_level=ls_tempValue;
					if(lr_RawCdr.gs_CamelFlag =="Y"  &&  lr_RawCdr.gn_CamelService_level=="") 
					{
						lr_RawCdr.gn_CamelService_level= "0";
					}			

					if(lr_RawCdr.gn_CamelService_level.mb_length() >6)
					{
						ls_RejMesg="Invalid value for CAMEL Service Level - ";
						ls_RejMesg+=ls_TempMesg;
						//throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get camel service key 
				case 20:
					lr_RawCdr.gn_CamelService_key		 = ls_tokenString;	
					if(lr_RawCdr.gn_CamelService_key.mb_length() > 10)
					{
						ls_RejMesg="Invalid value for CAMEL Service Key - ";
						ls_RejMesg+=ls_TempMesg;
						//throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get camel default call handling
				case 21:
					lr_RawCdr.gn_CamelDefault_call_handling=	ls_tokenString;

					ls_tempValue="";//=lr_RawCdr.gn_CamelService_level.mb_getSTLString ();
					ls_tempValue=lr_RawCdr.gn_CamelDefault_call_handling.mb_getSTLString ();
					mb_trim(ls_tempValue);
					lr_RawCdr.gn_CamelDefault_call_handling=ls_tempValue;

					if(lr_RawCdr.gs_CamelFlag =="Y"  &&  lr_RawCdr.gn_CamelDefault_call_handling=="") 
					{
						lr_RawCdr.gn_CamelDefault_call_handling= "0";
					}	

					if(lr_RawCdr.gn_CamelDefault_call_handling.mb_length() > 1)
					{
						ls_RejMesg="Invalid value for CAMEL Default Call Handling - ";
						ls_RejMesg+=ls_TempMesg;
						//throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get camel service address
				case 22:
					lr_RawCdr.gs_CamelServer_address=ls_tokenString;
					if(lr_RawCdr.gs_CamelServer_address.mb_length() > 24)
					{
						ls_RejMesg="Invalid value for CAMEL Server Address - ";
						ls_RejMesg+=lr_RawCdr.gs_CamelServer_address;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get camel msc address
				case 23:
					lr_RawCdr.gs_CamelMsc_address=ls_tokenString;
					if(lr_RawCdr.gs_CamelMsc_address.mb_length() > 24)
					{
						ls_RejMesg="Invalid value for CAMEL MSC Address - ";
						ls_RejMesg+=lr_RawCdr.gs_CamelMsc_address;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get camel call ref number
				case 24:
					lr_RawCdr.gs_CamelCall_ref_num =ls_tokenString;
					if(lr_RawCdr.gs_CamelCall_ref_num.mb_length() > 16)
					{
						ls_RejMesg="Invalid value for CAMEL Reference Number - ";
						ls_RejMesg+=lr_RawCdr.gs_CamelCall_ref_num;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get camel init call forward indicator
				case 25:
					lr_RawCdr.gn_CamelInit_cf_indicator  =  ls_tokenString;

					if(lr_RawCdr.gn_CamelInit_cf_indicator.mb_length() > 1)
					{
						ls_RejMesg="Invalid value for CAMEL INIT Call Forward Indicator - ";
						ls_RejMesg+=ls_TempMesg;
						//throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get camel destination number
				case 26:
					lr_RawCdr.gs_CamelDestination_num=ls_tokenString;
					if(lr_RawCdr.gs_CamelDestination_num.mb_length() > 24)
					{
						ls_RejMesg="Invalid value for CAMEL Destination Number - ";
						ls_RejMesg+=lr_RawCdr.gs_CamelDestination_num;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get camel modification
				case 27:
					lr_RawCdr.gs_CamelModification=ls_tokenString;
					if(lr_RawCdr.gs_CamelModification.mb_length() > 4)
					{
						ls_RejMesg="Invalid value for CAMEL Modification - ";
						ls_RejMesg+=lr_RawCdr.gs_CamelModification;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get supplimentary number 
				case 28:
					lr_RawCdr.gs_SupplimentaryNum=ls_tokenString;
					if(lr_RawCdr.gs_SupplimentaryNum.mb_length() > 2)
					{
						ls_RejMesg="Invalid value for Supplementary Number - ";
						ls_RejMesg+=lr_RawCdr.gs_SupplimentaryNum;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get network time
				case 29:
					lr_RawCdr.gn_NetworkTime   =  atoi(ls_tokenString.c_str());									
					ls_TempMesg.mb_fromInt(lr_RawCdr.gn_NetworkTime);

					if(ls_TempMesg.mb_length() > 4)
					{
						ls_RejMesg="Invalid value for Network Time-  ";
						ls_RejMesg+=ls_TempMesg;
						//throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get reason for clear down
				case 30:
					lr_RawCdr.gn_ReasonForCleardown  =  atoi(ls_tokenString.c_str());
					ls_TempMesg.mb_fromInt(lr_RawCdr.gn_ReasonForCleardown);

					if(ls_TempMesg.mb_length() > 4)
					{
						ls_RejMesg="Invalid value for Cleardown Reason-  ";
						ls_RejMesg+=ls_TempMesg;
						//throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get partial indicator

				case 31:
					lr_RawCdr.gs_PartialIndicator=ls_tokenString;
					if(lr_RawCdr.gs_PartialIndicator.mb_length() > 1)
					{
						ls_RejMesg="Invalid value for Partial Type Indicator - ";
						ls_RejMesg+=lr_RawCdr.gs_PartialIndicator;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get partial sequence number
				case 32:
					lr_RawCdr.gn_PartialSeqNum  =  atoi(ls_tokenString.c_str());
					ls_TempMesg.mb_fromInt(lr_RawCdr.gn_PartialSeqNum);
					//if(ls_TempMesg.mb_length() > 2)
					// Changed the length of partial seq no to 3 for Congo
					if(ls_TempMesg.mb_length() > 5)
					{
						ls_RejMesg="Invalid value for Partial Sequence Number - ";
						ls_RejMesg+=ls_TempMesg;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}

					if(lr_RawCdr.gn_PartialSeqNum==0)
					{
						lr_RawCdr.gn_PartialSeqNum=1;
					}
					break;

				//get imei number 
				case 33:
					lr_RawCdr.gs_ImeiNum=ls_tokenString;
					if(lr_RawCdr.gs_ImeiNum.mb_length() > 25)
					{
						ls_RejMesg="Invalid value for IMEI - ";
						ls_RejMesg+=lr_RawCdr.gs_ImeiNum;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get chrono number
				case 34:
					lr_RawCdr.gs_ChronoNum  =ls_tokenString;
					if(lr_RawCdr.gs_ChronoNum.mb_length() > 20)
					{
						ls_RejMesg="Invalid value for Chrono Number - ";
						ls_RejMesg+=lr_RawCdr.gs_ChronoNum;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get charging ID
				case 35:
					lr_RawCdr.gn_ChargingId  =  ls_tokenString;

					if(lr_RawCdr.gn_ChargingId.mb_length() > 10)
					{
						ls_RejMesg="Invalid value for Charging Id - ";
						ls_RejMesg+=ls_TempMesg;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get subscriber type
				case 36:
					lr_RawCdr.gs_SubscriberType  =ls_tokenString;

					if(lr_RawCdr.gs_SubscriberType=="")
						lr_RawCdr.gs_SubscriberType="O";

					if(lr_RawCdr.gs_SubscriberType.mb_length() > 1)
					{
						ls_RejMesg="Invalid value for Subscriber Type - ";
						ls_RejMesg+=lr_RawCdr.gs_SubscriberType;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get dialled digits
				case 37:
					lr_RawCdr.gs_DialledDigits  =ls_tokenString;
					if(lr_RawCdr.gs_DialledDigits.mb_length() > 25)
					{
						ls_RejMesg="Invalid value for Dialled Digits - ";
						ls_RejMesg+=lr_RawCdr.gs_DialledDigits;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get supplementary action code
				case 38:
					lr_RawCdr.gn_SupplemantryActionCode	=	atoi(ls_tokenString.c_str());
					ls_TempMesg.mb_fromFloat(lr_RawCdr.gn_SupplemantryActionCode);

					if(ls_TempMesg.mb_length() > 2)
					{
						ls_RejMesg="Invalid value for Supplementary Action Code - ";
						ls_RejMesg+=ls_TempMesg;
						//throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get cell id 
				case 39:
					lr_RawCdr.gs_CellId   =  ls_tokenString;
					if(lr_RawCdr.gs_CellId.mb_length() > 20)
					{
						ls_RejMesg="Invalid value for Cell Id - ";
						ls_RejMesg+=lr_RawCdr.gs_CellId;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get UTC off set 
				case 40:
					//lr_RawCdr.gs_UtcOffset  =  lv_tokens[40];
					//trim( &lr_RawCdr.gs_UtcOffset);
					lr_RawCdr.gs_UtcOffset  = ls_tokenString;
					if(lr_RawCdr.gs_UtcOffset.mb_length() > 5)
					{
						ls_RejMesg="Invalid value for UTC offset - ";
						ls_RejMesg+=lr_RawCdr.gs_UtcOffset;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get MNP CODE
				case 41:
					lr_RawCdr.gs_Mnp   =  ls_tokenString;

					if(lr_RawCdr.gs_Mnp.mb_length() > 25)
					{
						ls_RejMesg="Invalid value for MNP CODE - ";
						ls_RejMesg+=lr_RawCdr.gs_Mnp;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;


				//Get Network Call Reference
				case 42:
					lr_RawCdr.gs_Network_Call_Ref   =  ls_tokenString;

					if(lr_RawCdr.gs_Network_Call_Ref.mb_length() > 25)
					{
						ls_RejMesg="Invalid value for Netwrok Call Ref CODE - ";
						ls_RejMesg+=lr_RawCdr.gs_Network_Call_Ref;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;
				/*
				//get P-CSCF address	
				case 42:
					lr_RawCdr.gs_PCSCF_Address   =  ls_tokenString;

					if((lr_RawCdr.gs_PCSCF_Address.mb_length() > 45)||
					(lr_RawCdr.gs_PCSCF_Address.mb_length()==0 &&
					(lr_RawCdr.gs_ServiceCode=="300" ||
					lr_RawCdr.gs_ServiceCode=="301" ||
					lr_RawCdr.gs_ServiceCode=="302" )))
					{
						ls_RejMesg="Invalid or null value for P-CSCF address - ";
						ls_RejMesg+=lr_RawCdr.gs_PCSCF_Address;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get AUserId
				case 43:
					lr_RawCdr.gs_AUserId   =  ls_tokenString;

					if(lr_RawCdr.gs_AUserId.mb_length() > 65)
					{
						ls_RejMesg="Invalid value for A UserId - ";
						ls_RejMesg+=lr_RawCdr.gs_AUserId;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get BUserId
				case 44:
					lr_RawCdr.gs_BUserId   =  ls_tokenString;

					if(lr_RawCdr.gs_BUserId.mb_length() > 65)
					{
						ls_RejMesg="Invalid value for B UserId - ";
						ls_RejMesg+=lr_RawCdr.gs_BUserId;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get event reference
				case 45:
					lr_RawCdr.gs_EventReference   =  ls_tokenString;

					if((lr_RawCdr.gs_EventReference.mb_length() > 30)||
					(lr_RawCdr.gs_EventReference.mb_length()==0 &&
					(lr_RawCdr.gs_ServiceCode=="300" ||
					lr_RawCdr.gs_ServiceCode=="301" ||
					lr_RawCdr.gs_ServiceCode=="302" )))
					{
						ls_RejMesg="Invalid or null value for event reference - ";
						ls_RejMesg+=lr_RawCdr.gs_EventReference;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				//get APN Operator Id
				case 46:
					lr_RawCdr.gs_APN_OperatorId   =  ls_tokenString;
					if(lr_RawCdr.gs_APN_OperatorId.mb_length() > 37)
					{
						ls_RejMesg="Invalid value for APN Operator Id - ";
						ls_RejMesg+=lr_RawCdr.gs_APN_OperatorId;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;

				case 47:
					break;

				case 48:
					break;

				case 49:
					break;

				case 50:
					break;

				case 51:
					lr_RawCdr.gs_Network_Call_Ref   =  ls_tokenString;

					if(lr_RawCdr.gs_Network_Call_Ref.mb_length() > 30)
					{
						ls_RejMesg="Invalid value for Nwtwork Call Reference - ";
						ls_RejMesg+=lr_RawCdr.gs_Network_Call_Ref;
						throw  ABL_Exception(-1,ls_RejMesg.c_str());
					}
					break;*/
				
				default:
					break;
			}
			l=l+1;
		}

		if(lr_RawCdr.gd_CallDate<md_MinCallDate) 
			md_MinCallDate = lr_RawCdr.gd_CallDate;

		if (lr_RawCdr.gd_CallDate > md_MaxCallDate)
			md_MaxCallDate = lr_RawCdr.gd_CallDate;

		lr_RawCdr.gn_InputFileId	=in_FileID;
		lr_RawCdr.gn_RecordNo		=in_RecordNo;
		lr_RawCdr.gs_Status             ="NEW";

		if(lr_RawCdr.gs_DestinationSubType=="")
			lr_RawCdr.gs_DestinationSubType="0";

		//added as per LTE usage for 4.3 release
		//if (lr_RawCdr.gs_ServiceCode == "005")
		if (lr_RawCdr.gs_ServiceCode == "005" || lr_RawCdr.gs_ServiceCode == "305")
		//modification end
			lr_RawCdr.gs_DestinationSubType = "0";

		lr_RawCdr.gn_RecordingEntityType_SGSN=4;
		lr_RawCdr.gn_TapRecordingEntityCode_SGSN=0;
		lr_RawCdr.gs_RawCdr		=in_RawCdr;
		p_ABL_JobPtr->ga_RatedCdrs.push_back(lr_RawCdr);	
	}

	catch(ABL_Exception &e)
	{
		lr_RejectedCdr.gn_FileId=0;
		lr_RejectedCdr.gn_RecordNo=0;
		lr_RejectedCdr.gs_ErrorCode="";
		lr_RejectedCdr.gs_ErrorMessage="";
		lr_RejectedCdr.gs_ErrorValue="";
		lr_RejectedCdr.gd_RejectedDate.mb_fromSysDate();
		lr_RejectedCdr.gs_Status=""; 
		lr_RejectedCdr.gs_ErrorCdr=""; 
		lr_RejectedCdr.gs_AgreementType="";
		lr_RejectedCdr.gn_CallType=0;
		lr_RejectedCdr.gs_CallDirection="";
		lr_RejectedCdr.gs_NeCode="";
		lr_RejectedCdr.gs_PartnerIdentifier="";
		lr_RejectedCdr.gs_PartnerCode="";
		lr_RejectedCdr.gs_Poi="";
		lr_RejectedCdr.gs_ServiceCode="";
		lr_RejectedCdr.gs_RateDirection="";
		lr_RejectedCdr.gs_PaymentDirection="";
		lr_RejectedCdr.gs_RateUnit="";
		lr_RejectedCdr.gn_UnitQty=0;
		lr_RejectedCdr.gs_NumberPlanCode="";
		lr_RejectedCdr.gs_TariffPlanCode="";
		lr_RejectedCdr.gs_ALong="";
		lr_RejectedCdr.gs_OriginRateZone="";
		lr_RejectedCdr.gs_BLong="";
		lr_RejectedCdr.gs_DestRateZone="";

		//Added as per LTE usage
		//lr_RejectedCdr.gd_CallDate.mb_fromSysDate();
		std::stringstream l_stringStream1(in_RawCdr.c_str());
		std::string ls_tokenString1="";
		ABL_String ls_TempMesg1="";
		int i=0;
		while(std::getline(l_stringStream1,ls_tokenString1,ls_delimit[0]))
		{
			mb_trim(ls_tokenString1);
			i=i+1;
			if(i==13) break;
		}

		if(ls_tokenString1.size()==14)
		{
			lr_RejectedCdr.gd_CallDate.mb_fromText(ls_tokenString1.c_str(),YYYYMMDDHH24MISS);
			ls_TempMesg1=lr_RejectedCdr.gd_CallDate.mb_toString();
			if((ls_TempMesg1.mb_length()!= 14)|| (ls_TempMesg1=="")) 
			lr_RejectedCdr.gd_CallDate.mb_fromSysDate();
			//modification end
		}
		else
		{
			lr_RejectedCdr.gd_CallDate.mb_fromSysDate();
		}
		
		lr_RejectedCdr.gs_DayCode="";
		lr_RejectedCdr.gs_TimeType="";
		lr_RejectedCdr.gn_RerateSeqNo=0;
		lr_RejectedCdr.gn_CallDuration=0;
		lr_RejectedCdr.gs_ChronoNum=lr_RawCdr.gs_ChronoNum;
		lr_RejectedCdr.gn_PartialSeqNum=lr_RawCdr.gn_PartialSeqNum;

		//Added as per LTE usage for 4.3 release
		if(lr_RawCdr.gs_AUserId.mb_length()>65)
			lr_RejectedCdr.gs_AUserId="";
		else
			lr_RejectedCdr.gs_AUserId=lr_RawCdr.gs_AUserId;

		if(lr_RawCdr.gs_BUserId.mb_length()>65)
			lr_RejectedCdr.gs_BUserId="";
		else
			lr_RejectedCdr.gs_BUserId=lr_RawCdr.gs_BUserId;
		//modification end

		//std::cout<<"Error Message in Parse event: "<<e.mb_getMessage() <<" Eror code: "<<e.mb_getErrorCode()<<std::endl;
		if(e.mb_getErrorCode()== -1)
		{
			lr_RejectedCdr.gs_AgreementType			=ls_Agreement;
			lr_RejectedCdr.gn_FileId				=in_FileID;
			lr_RejectedCdr.gn_RecordNo				=in_RecordNo;
			lr_RejectedCdr.gs_ErrorCdr				=in_RawCdr;
			//modified as per LTE usage for 4.3 release
			//lr_RejectedCdr.gs_ErrorCode				="PARSEERROR";
			lr_RejectedCdr.gs_ErrorCode                          ="RATE-PARSEERROR";
			//modification end
			lr_RejectedCdr.gs_ErrorMessage				=ls_RejMesg;
			lr_RejectedCdr.gd_RejectedDate.mb_fromSysDate();
			lr_RejectedCdr.gs_Status				="NEW";
			//Added as per LTE usage for 4.3 release
			*m_ABL_ServicePtr << DEBUG << "Exception : "<< e.mb_getMessage() << Endl;
			//modification end
			p_ABL_JobPtr->ga_RejectedCdrs.push_back(lr_RejectedCdr);
		}
		else if(e.mb_getErrorCode()== -3)
		{
			ls_RejMesg="File format not correct,Kindly check the cdr lenght";	
			throw  ABL_Exception(-3,ls_RejMesg.c_str());
		}
		else
		{
			//populate rejection details.
			//modified as per LTE usage for 4.3 release
			//lr_RejectedCdr.gs_ErrorCode                          ="PARSEERROR";
			lr_RejectedCdr.gs_ErrorCode                          ="RATE-PARSEERROR";
			//modification end
			lr_RejectedCdr.gs_ErrorMessage				=ls_RejMesg;
			lr_RejectedCdr.gn_FileId				=in_FileID;
			lr_RejectedCdr.gn_RecordNo				=in_RecordNo;
			lr_RejectedCdr.gs_AgreementType				=ls_Agreement;
			lr_RejectedCdr.gs_CallDirection				="X";
			lr_RejectedCdr.gs_ErrorCdr				=in_RawCdr;
			lr_RejectedCdr.gd_RejectedDate.mb_fromSysDate();	
			lr_RejectedCdr.gs_Status                 		="NEW";
			//Added as per LTE usage for 4.3 release
			*m_ABL_ServicePtr << DEBUG << "Exception : "<<e.mb_getMessage() << Endl;
			//modification end
			p_ABL_JobPtr->ga_RejectedCdrs.push_back(lr_RejectedCdr);
		}
	}
	catch(...)
	{
		rename(p_ABL_JobPtr->gs_SourceFilePath.c_str(),p_ABL_JobPtr->gs_ErrorFile_Path.c_str());
		ABL_String ls_command("touch ");
		ls_command +=ms_Stopsignalfile;
		system(ls_command.c_str()); 	
		*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}
	return true;
}

/*Fuction to tokenize a string.*/
/*void PM_ParseRawEvent::tokenize(const std::string& in_str,std::vector<std::string>& lv_tokens,const std::string& in_delimiters )
{
	std::stringstream l_stringStream(in_str);
	std::string ls_tokenString;
	lv_tokens.clear();
	int cdr_file_col=m_ABL_ServicePtr->mb_getInt("NUMBER_OF_COLUMNS_IN_FILE");
	int x=1;

	while(std::getline(l_stringStream,ls_tokenString,in_delimiters[0]))
	{
		if(x>cdr_file_col) break;
			lv_tokens.push_back(ls_tokenString);

		//	*m_ABL_ServicePtr << DEBUG << "counter value : "<<x <<"Value: "<<ls_tokenString<< Endl;
		x++;

	}
} */


void PM_ParseRawEvent::tokenize(const std::string& in_str,std::vector<std::string>& lv_tokens,const std::string& in_delimiters )
{
	std::stringstream l_stringStream(in_str);
	std::string ls_tokenString;

	while(std::getline(l_stringStream,ls_tokenString,in_delimiters[0]))
	{
		lv_tokens.push_back(ls_tokenString);
	}
}




/*Fuction to remove the leading n trailing spaces in a string.*/
void PM_ParseRawEvent::mb_trim(std::string &p_string)
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


/* Function to remove zeroes. */
void PM_ParseRawEvent::fnRemoveZeros(ABL_String *in_str)
{
	ABL_String ls_ptr = "";
	ABL_String ls_ptr_temp = "";
	ls_ptr = *in_str;
	int ln_strLen=0;
	int ln_TempCount=0;
	ln_strLen=ls_ptr.mb_length();

	for(int i=0;i<=ln_strLen;i++)
	{	
		if (i==0)
			ln_TempCount=0;
		else
			ln_TempCount=i-1;
		if (ls_ptr.mb_subStr(ln_TempCount,i)=="0")
			ls_ptr_temp=ls_ptr.mb_subStr((i+1),(ln_strLen-i+1));
		else
			break;
	}	
	if(ls_ptr_temp=="")
		ls_ptr_temp=ls_ptr;    
	in_str=&ls_ptr_temp;
}

