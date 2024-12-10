#include "PM_ReadRawCdrsFromDB.h"
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



extern "C" {EXPORT
Base_Registry* gb_getPM_ReadRawCdrsFromDB()
{
        return ( (Base_Registry*) new PM_ReadRawCdrsFromDB);
}
}

PM_ReadRawCdrsFromDB::PM_ReadRawCdrsFromDB()
{
        //
}

PM_ReadRawCdrsFromDB::~PM_ReadRawCdrsFromDB()
{
        //
}

PM_ReadRawCdrsFromDB::PM_ReadRawCdrsFromDB(const PM_ReadRawCdrsFromDB& p_copyObject)
{

        this->m_ABL_ServicePtr                          =       p_copyObject.m_ABL_ServicePtr;
        this->ms_directoryName                          =       p_copyObject.ms_directoryName;
this->ms_cdrFileName                            =       p_copyObject.ms_cdrFileName;
        this->ms_rawCdrFileName                         =       p_copyObject.ms_rawCdrFileName;
        this->ms_rawCdr                                         =       p_copyObject.ms_rawCdr;
        this->ms_Stopsignalfile                         =       p_copyObject.ms_Stopsignalfile;



}

Base_Registry* PM_ReadRawCdrsFromDB::mb_clone()
{
        return ( (Base_Registry*) new PM_ReadRawCdrsFromDB );
}

ABL_Process* PM_ReadRawCdrsFromDB::mb_createCopy()
{
        return ( new PM_ReadRawCdrsFromDB (*this));
}

bool PM_ReadRawCdrsFromDB::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{

        try
        {
                m_ABL_ServicePtr                        = p_ABL_ServicePtr;
                p_ABL_AgentCommunicatorPtr->mb_getParameter("STOP_FILE",ms_Stopsignalfile);
                ms_directoryName = m_ABL_ServicePtr->mb_getParameterValue("CDR_FOLDER");
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

bool PM_ReadRawCdrsFromDB::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
        return true;
}

bool PM_ReadRawCdrsFromDB::mb_process(ABL_Job* &p_ABL_JobPtr)
{

        PM_Job* lo_PMJobPtr    = (PM_Job*)p_ABL_JobPtr;
        *m_ABL_ServicePtr << DEBUG << "Getting cdrs from the PM_RATED_CDRS Table : " << Endl;



        gr_RatingLog lr_RatingLog;


        ABL_String ls_CdrValue ;
        lo_PMJobPtr->gn_TotalCDRS_In_File=0;


        ABL_Connection  *lo_ABLConnection;
        ABL_Statement   lo_ABLStatement;
        ABL_ResultSet   lo_ABLResultSet;
        ABL_String          ls_sql;
        ABL_String              ls_ErrCode;
        ABL_String              ls_ErrMesg;



        const std::string ls_delimit="|";
        std::vector<std::string> lv_tokens;
        ABL_String ls_RepriceLevel="";
        ABL_String ls_backupoldcdrs="";
        ABL_String ls_Agreementtype="";
        unsigned int ln_RatedCdrCount=0;

        try
        {

                        lo_PMJobPtr->gs_AgreementType="";
                        lo_PMJobPtr->gn_InPutFileId =0;
			                        lo_PMJobPtr->gn_RepriceSeqNo=0;

                        lo_ABLConnection=lo_PMJobPtr->mb_getConnection();
                        tokenize(lo_PMJobPtr->gs_fileName.c_str(),lv_tokens,ls_delimit);
                          lo_PMJobPtr->gs_FileStatus="S";
                        for(int i=4;i<lv_tokens.size();i++)
                        {

                                        unsigned int ln_FileID=atoi(lv_tokens[i].c_str());
                                        unsigned int ln_RepriceSeqNo=atoi(lv_tokens[0].c_str());

                                        ls_RepriceLevel="";
                                        ls_backupoldcdrs="";
                                        ls_Agreementtype="";
                                        ls_RepriceLevel=lv_tokens[1];
                                        ls_backupoldcdrs=lv_tokens[2];
                                        ls_Agreementtype=lv_tokens[3];
                                        lo_PMJobPtr->gn_InPutFileId =ln_FileID;
                                        lo_PMJobPtr->gn_RepriceSeqNo=ln_RepriceSeqNo;
                                        lo_PMJobPtr->gs_AgreementType=ls_Agreementtype;

                                        ls_sql="select CDR_FILE_NAME ,RECEIVED_ON,PROCESS_START_TIME,PROCESS_END_TIME,PROCESSING_TIME_IN_SECS,ST_CHRONO,ED_CHRONO,";
                                        ls_sql+="FIRST_CALL_DT_TIME ,LAST_CALL_DT_TIME,TOTAL_EVENTS,INC_TOTAL_EVENTS,INC_RATED_EVENTS,INC_DROPPED_EVENTS,";
                                        ls_sql+="INC_REJECTED_EVENTS,OUT_TOTAL_EVENTS,OUT_RATED_EVENTS,OUT_DROPPED_EVENTS,OUT_REJECTED_EVENTS,PROCESSED,FILE_ID,";
                                        ls_sql+="SUMMARISED,RECONCILED from pm_rating_log where file_id = :1";

                                        lo_ABLStatement         =       lo_ABLConnection->mb_createStatement(ls_sql);
                                        lo_ABLStatement.mb_setUInt(1,ln_FileID);
                                        lo_ABLResultSet =lo_ABLStatement.mb_executeQuery();
                                        while(lo_ABLResultSet.mb_fetch())
                                        {
                                                lr_RatingLog.gs_CdrFileName                             =       lo_ABLResultSet.mb_getString(1);
                                                lo_PMJobPtr->gs_fileName                                =       lr_RatingLog.gs_CdrFileName;
                                                lr_RatingLog.gd_ReceivedOn                              =       lo_ABLResultSet.mb_getDate(2);
                                                //lr_RatingLog.gd_ProcessStartTime        =     lo_ABLResultSet.mb_getDate(3);
                                                //lr_RatingLog.gd_ProcessEndTime                        =       lo_ABLResultSet.mb_getDate(4);
                                                //lr_RatingLog.gn_ProcessingTimeInSecs  =       lo_ABLResultSet.mb_getInt64(5);
                                                lr_RatingLog.gs_Chrono                                  =       lo_ABLResultSet.mb_getString(6);
                                                lr_RatingLog.gs_EdChrono                                =       lo_ABLResultSet.mb_getString(7);
                                                lr_RatingLog.gd_FirstCallDtTime                 =       lo_ABLResultSet.mb_getDate(8);
                                                lr_RatingLog.gd_LastCallDtTime                  =       lo_ABLResultSet.mb_getDate(9);
                                                lr_RatingLog.gn_TotalEvents                             =       lo_ABLResultSet.mb_getInt64(10);
                                                lr_RatingLog.gn_IncTotalEvents                  =       lo_ABLResultSet.mb_getInt64(11);
                                                lr_RatingLog.gn_IncRatedEvents                  =       lo_ABLResultSet.mb_getInt64(12);
                                                lr_RatingLog.gn_IncDroppedEvents                =       lo_ABLResultSet.mb_getInt64(13);
                                                lr_RatingLog.gn_IncRejectedEvents               =   lo_ABLResultSet.mb_getInt64(14);
                                                lr_RatingLog.gn_OutTotalEvents                  =       lo_ABLResultSet.mb_getInt64(15);
                                                lr_RatingLog.gn_OutRatedEvents                  =       lo_ABLResultSet.mb_getInt64(16);
                                                lr_RatingLog.gn_OutDroppedEvents                =       lo_ABLResultSet.mb_getInt64(17);
                                                lr_RatingLog.gn_OutRejectedEvents               =       lo_ABLResultSet.mb_getInt64(18);
                                                lr_RatingLog.gs_Processed                               =       lo_ABLResultSet.mb_getString(19);
                                                lr_RatingLog.gn_FileId                                  =       lo_ABLResultSet.mb_getInt64(20);
                                                lr_RatingLog.gs_Summarised                              =       "N";
                                                lr_RatingLog.gs_Reconciled                              =       "N";
                                                lo_PMJobPtr->ga_RatingLog.push_back(lr_RatingLog);
                                        }
                                        lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
                                        lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
                                        lo_PMJobPtr->ga_RatingLog[0].gd_ProcessStartTime.mb_fromSysDate();
                                        //get file details
                                        ls_ErrCode = "REPRICE-3.13";
                                        ls_ErrMesg = "..File id => ";
                                        ls_ErrMesg+=lv_tokens[i];
                                        ls_ErrMesg+=":File Name => ";
                                        ls_ErrMesg+=lr_RatingLog.gs_CdrFileName;
                                        ls_ErrMesg+=", First Call Date => ";
                                        ls_ErrMesg+=lr_RatingLog.gd_FirstCallDtTime.mb_toString(YYYYMMDDHH24MISS);
                                        ls_ErrMesg+=", Last Call Date => ";
                                        ls_ErrMesg+=lr_RatingLog.gd_LastCallDtTime.mb_toString(YYYYMMDDHH24MISS);
                                        *m_ABL_ServicePtr <<INFO<<"ErrCode: "<< ls_ErrCode<<" ErrMesg: "<<ls_ErrMesg<< Endl;
                                   /*****************************************************************
                                        * step 2: bulk fetch all the rated cdrs for the file id
                                        *         which are submitted for repricing
                                        *****************************************************************/
                                        ls_ErrCode = "REPRICE-3.14";
                                        ls_ErrMesg = "....File Id => ";
                                        ls_ErrMesg+=lv_tokens[i];
                                        ls_ErrMesg+=":Fetch cdrs between ";
                                        ls_ErrMesg+=lr_RatingLog.gd_FirstCallDtTime.mb_toString(YYYYMMDDHH24MISS);
                                        ls_ErrMesg+=" and ";
                                        ls_ErrMesg+=lr_RatingLog.gd_LastCallDtTime.mb_toString(YYYYMMDDHH24MISS);
                                        *m_ABL_ServicePtr <<INFO<<"ErrCode: "<< ls_ErrCode<<" ErrMesg: "<<ls_ErrMesg<< Endl;

                                        double ln_TotalUnits[100];
                                        double ln_TotalBytes[100];
                                        double ln_ChargedAmount[100];
                                        double ln_ChargeAmountWithMulti[100];
                                        double ln_CallDuration[100];
                                        double ln_DataVolumeOut[100];
                                        double ln_DataVolumeIn[100];
                                        double ln_ChargeSdr[100];
                                        double ln_TaxSdr[100];
                                        double ln_DiscountSdr[100];
                                        double ln_TaxAmount[100];
                                        double ln_DiscountAmount[100];
                                        ABL_String ls_PartnerCode[100];
                                        unsigned int ln_FileSequenceNumber[100];
                                        ABL_String ls_DataTypeIndicator[100];
                                        unsigned int ln_SummarySeqNo[100];
                                        ABL_String ls_RawCdr[100];

                                        ls_sql="SELECT NVL(total_units,0),(NVL(data_volume_inc,0) + NVL(data_volume_out,0)),(NVL(charge_amount,0) / (SELECT multi_factor FROM pm_agreement_type WHERE agreement_type = pm_rated_cdrs.agreement_type)) AS charge_amount_nomult, ";
                                        ls_sql+="NVL(charge_amount,0), DECODE (service_code, '003', 0, NVL(call_duration,0)),DECODE (service_code, '005', NVL(data_volume_out,0), 0),DECODE (service_code, '005', NVL(data_volume_inc,0), 0), ";
                                        ls_sql+="NVL(charge_sdr,0), NVL(tax_sdr,0),NVL(discount_sdr,0), NVL(tax_amount,0), NVL(discount_amount,0), partner_code,NVL(file_sequence_number,0), NVL(data_type_indicator,' '),NVL(Summary_Seq_No,0),";
					//removed extra spaces from raw cdr as per LTE usage for 4.3 release
                                        ls_sql+="(call_type||'|'";
                                        ls_sql+="||service_code||'|'";
                                        ls_sql+="||ne_code||'|'";
                                        ls_sql+="||NVL(TO_CHAR(in_route),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(out_route),' ')||'|'";
                                        ls_sql+="||nvl(to_char(IMSI),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(SGSN_ADDRESS),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(a_number),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(b_number),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(c_number),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(apn_address),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(pdp_address),' ')||'|'";
                                        ls_sql+="||TO_CHAR(call_date,'YYYYMMDDHH24MISS')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(call_duration),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(data_volume_inc),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(data_volume_out),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(teleservice),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(bearerservice),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(camel_flag),'N')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(camel_service_level),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(camel_service_key),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(camel_default_call_handling),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(CAMEL_SERVER_ADDRESS),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(CAMEL_MSC_ADDRESS),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(CAMEL_CALL_REF_NUM),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(CAMEL_INIT_CF_INDICATOR),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(CAMEL_DESTINATION_NUM),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(CAMEL_MODIFICATION),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(SUPPLIMENTARY_NUM),' ')||'|'";
                                        ls_sql+="||TO_CHAR(nvl(NETWORK_TIME,0))||'|'";
                                        ls_sql+="||TO_CHAR(nvl(REASON_FOR_CLEARDOWN,0))||'|'";
                                        ls_sql+="||NVL(TO_CHAR(PARTIAL_INDICATOR),' ')||'|'";
                                        ls_sql+="||LPAD(TO_CHAR(PARTIAL_SEQ_NUM),2,'01')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(IMEI_NUM),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(CHRONO_NUM),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(CHARGING_ID),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(SUBSCRIBER_TYPE),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(dialled_digits),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(SUPPLIMENTARY_ACTION_CODE),' ')||'|'";
                                        ls_sql+="||NVL(TO_CHAR(CELL_ID), ' ')||'|'";
                                        ls_sql+="||LPAD(('+0000'),5)||'|'";
										ls_sql+="||LPAD(NVL(MNP_ROUTING_ID, ' '),25)||'|'";
										ls_sql+="||LPAD(NVL(NETWORK_CALL_REF, ' '),25)||'|') as RAWCDR ,ROWID ";
										ls_sql+="FROM pm_rated_cdrs where input_file_id=:1 AND reprice_seq_no=:2";
                                        lo_ABLStatement         =       lo_ABLConnection->mb_createStatement(ls_sql);
                                        lo_ABLStatement.mb_setUInt(1,ln_FileID);
                                        lo_ABLStatement.mb_setUInt(2,ln_RepriceSeqNo);
                                        lo_ABLResultSet =lo_ABLStatement.mb_executeQuery();
                                        lo_ABLResultSet.mb_setBulkCount(100);
                                        lo_ABLResultSet <<ln_TotalUnits;
                                        lo_ABLResultSet <<ln_TotalBytes;
                                        lo_ABLResultSet <<ln_ChargedAmount;
                                        lo_ABLResultSet <<ln_ChargeAmountWithMulti;
                                        lo_ABLResultSet <<ln_CallDuration;
                                        lo_ABLResultSet <<ln_DataVolumeOut;
                                        lo_ABLResultSet <<ln_DataVolumeIn;
                                        lo_ABLResultSet <<ln_ChargeSdr;
                                        lo_ABLResultSet <<ln_TaxSdr;
                                        lo_ABLResultSet <<ln_DiscountSdr;
                                        lo_ABLResultSet <<ln_TaxAmount;
                                        lo_ABLResultSet <<ln_DiscountAmount;
                                        lo_ABLResultSet <<ls_PartnerCode;
                                        lo_ABLResultSet <<ln_FileSequenceNumber;
                                        lo_ABLResultSet <<ls_DataTypeIndicator;
                                        lo_ABLResultSet <<ln_SummarySeqNo;
                                        lo_ABLResultSet <<ls_RawCdr;
                                        while(lo_ABLResultSet.mb_fetch())
                                        {
                                                int records = lo_ABLResultSet.mb_getNumArrayRows();
                                                for(int i = 0; i < records ; i++)
                                                {
                                                                unsigned int ln_summary_seq_no=ln_SummarySeqNo[i];
                                                                ABL_String ls_partnerCode=ls_PartnerCode[i];

                                                                if(ls_RepriceLevel=="C" && ln_summary_seq_no>0)
                                                                {
                                                                        try
                                                                        {

                                                                                ls_sql="UPDATE pm_summary s SET s.total_units = total_units-:1, s.total_duration = total_duration-:2,";
                                                                                ls_sql+="s.total_bytes = total_bytes-:3,s.total_count = total_count-1,s.total_amount= total_amount-:4";
                                                                                ls_sql+="WHERE s.summary_seq_no = :5";
                                                                                ABL_Statement   lo_UpSummary_ABLStatement;
                                                                                lo_UpSummary_ABLStatement               =       lo_ABLConnection->mb_createStatement(ls_sql);
                                                                                lo_UpSummary_ABLStatement.mb_setDouble(1,ln_TotalUnits[i]);
                                                                                                                                                                                                                          lo_UpSummary_ABLStatement.mb_setDouble(2,ln_CallDuration[i]);
                                                                                lo_UpSummary_ABLStatement.mb_setDouble(3,ln_TotalBytes[i]);
                                                                                lo_UpSummary_ABLStatement.mb_setDouble(4,ln_ChargedAmount[i]);
                                                                                lo_UpSummary_ABLStatement.mb_setUInt(5,ln_summary_seq_no);
                                                                                lo_UpSummary_ABLStatement.mb_executeUpdate();
                                                                                lo_ABLConnection->mb_terminateStatement(lo_UpSummary_ABLStatement);
                                                                        }
                                                                        catch(ABL_Exception &e)
                                                                        {
                                                                                        *m_ABL_ServicePtr << CRITICAL << "Exception : " << e.mb_getMessage() << Endl;
                                                                                         ABL_String ls_command("touch ");
                                                                                         ls_command +=ms_Stopsignalfile;
                                                                                         system(ls_command.c_str());
                                                                                        return false;
                                                                        }
                                                                }

                                                                if(ln_FileSequenceNumber[i]>0)
                                                                {
                                                                        ls_sql="update pm_tap_file_sumry set TOTAL_CALL_EVENTS = total_call_events - 1,";
                                                                        ls_sql+="TOTAL_CALL_EVENTS_PROCESSED = total_call_events_processed - 1,";
                                                                        ls_sql+="TOTAL_DURATION = total_duration - :1,";
                                                                        ls_sql+="TOTAL_OUTGOING_VOLUME = total_outgoing_volume -:2,";
                                                                        ls_sql+="TOTAL_INCOMING_VOLUME = total_incoming_volume - :3,";
                                                                        ls_sql+="TAP_CURNCY_CHARGE = tap_curncy_charge - :4,";
                                                                        ls_sql+="TAP_CURNCY_TAX = tap_curncy_tax - :5,";
                                                                        ls_sql+="TAP_CURNCY_DISCOUNT = tap_curncy_discount - :6,";
                                                                        ls_sql+="HOME_CURNCY_CHARGE = home_curncy_charge - :7,";
                                                                        ls_sql+="HOME_CURNCY_TAX = home_curncy_tax -:8,";
                                                                        ls_sql+="HOME_CURNCY_DISCOUNT = home_curncy_discount -:9,";
                                                                        ls_sql+="SETTLEMENT_CALL_EVENTS = total_call_events - 1,";
                                                                        ls_sql+="SETTLEMENT_DURATION = total_duration - :10,";
                                                                        ls_sql+="SETTLEMENT_OUTGOING_VOLUME = total_outgoing_volume - :11,";
                                                                        ls_sql+="SETTLEMENT_INCOMING_VOLUME = total_incoming_volume - :12,";
                                                                        ls_sql+="SETTLEMENT_TAP_CURNCY_CHARGE = tap_curncy_charge - :13,";
                                                                        ls_sql+="SETTLEMENT_TAP_CURNCY_TAX = tap_curncy_tax -:14,";
                                                                        ls_sql+="SETTLEMENT_TAP_CURNCY_DISCOUNT = tap_curncy_discount - :15,";
                                                                        ls_sql+="SETTLEMENT_LOCAL_CHARGE = home_curncy_charge - :16,";
                                                                        ls_sql+="SETTLEMENT_LOCAL_TAX = home_curncy_tax - :17,";
                                                                        ls_sql+="SETTLEMENT_LOCAL_DISCOUNT = home_curncy_discount - :18";
                                                                        ls_sql+="where partner_code=:19";
                                                                        ls_sql+="and file_sequence_number=:20";                             
                                                                        ls_sql+="and file_type_indicator=:21";
                                                                        ls_sql+="and file_transfer_direction='O'";
                                                                        ABL_Statement   lo_UpTapSummary_ABLStatement;
                                                                        lo_UpTapSummary_ABLStatement=lo_ABLConnection->mb_createStatement(ls_sql);
                                                                        lo_UpTapSummary_ABLStatement.mb_setDouble(1,ln_CallDuration[i]);
                                                                        lo_UpTapSummary_ABLStatement.mb_setDouble(2,ln_DataVolumeOut[i]);
                                                                        lo_UpTapSummary_ABLStatement.mb_setDouble(3,ln_DataVolumeIn[i]);
                                                                        lo_UpTapSummary_ABLStatement.mb_setDouble(4,ln_ChargeSdr[i]);
                                                                        lo_UpTapSummary_ABLStatement.mb_setDouble(5,ln_TaxSdr[i]);
                                                                        lo_UpTapSummary_ABLStatement.mb_setDouble(6,ln_DiscountSdr[i]);
                                                                        lo_UpTapSummary_ABLStatement.mb_setDouble(7,ln_ChargeAmountWithMulti[i]);
                                                                        lo_UpTapSummary_ABLStatement.mb_setDouble(8,ln_TaxAmount[i]);
                                                                        lo_UpTapSummary_ABLStatement.mb_setDouble(9,ln_DiscountAmount[i]);
                                                                        lo_UpTapSummary_ABLStatement.mb_setDouble(10,ln_CallDuration[i]);
                                                                        lo_UpTapSummary_ABLStatement.mb_setDouble(11,ln_DataVolumeOut[i]);
                                                                        lo_UpTapSummary_ABLStatement.mb_setDouble(12,ln_DataVolumeIn[i]);
                                                                        lo_UpTapSummary_ABLStatement.mb_setDouble(13,ln_ChargeSdr[i]);
                                                                        lo_UpTapSummary_ABLStatement.mb_setDouble(14,ln_TaxSdr[i]);
                                                                        lo_UpTapSummary_ABLStatement.mb_setDouble(15,ln_DiscountSdr[i]);
                                                                        lo_UpTapSummary_ABLStatement.mb_setDouble(16,ln_ChargeAmountWithMulti[i]);
                                                                        lo_UpTapSummary_ABLStatement.mb_setDouble(17,ln_TaxAmount[i]);
                                                                        lo_UpTapSummary_ABLStatement.mb_setDouble(18,ln_DiscountAmount[i]);
                                                                        lo_UpTapSummary_ABLStatement.mb_setString(19,ls_PartnerCode[i]);
                                                                        lo_UpTapSummary_ABLStatement.mb_setUInt(20,ln_FileSequenceNumber[i]);
                                                                        lo_UpTapSummary_ABLStatement.mb_setString(21,ls_DataTypeIndicator[i]);               
                                                                        lo_UpTapSummary_ABLStatement.mb_executeUpdate();
                                                                        lo_ABLConnection->mb_terminateStatement(lo_UpTapSummary_ABLStatement);
                                                                }
                                                                lo_PMJobPtr->ga_RawCDRSVector.push_back(ls_RawCdr[i]);
                                                        }//end of  for loop
                                                }//end of while loop
                                                lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
                                                lo_ABLConnection->mb_terminateStatement(lo_ABLStatement);
                                                if (lo_PMJobPtr->ga_RawCDRSVector.size()== 0)
                                                {
                                                        ls_ErrCode = "REPRICE-3.25";
                                                   ls_ErrMesg = "....File Id => ";
                                                   ls_ErrMesg+=lv_tokens[i];
                                                   ls_ErrMesg+=":No cdrs to reprice. Skip file.";
                                                        *m_ABL_ServicePtr <<INFO<<"ErrCode: "<< ls_ErrCode<<" ErrMesg: "<<ls_ErrMesg<< Endl;
                                                        return false;
                                                }

                                                ABL_String ls_tempValueofnumeric="";
                                                                                                                                           
                                                ls_ErrCode = "REPRICE-3.15";
                                                ls_ErrMesg = "....File Id => ";
                                                ls_ErrMesg+=lv_tokens[i];
                                                ls_ErrMesg+=":Fetched ";
                                                ls_tempValueofnumeric.mb_fromInt64(lo_PMJobPtr->ga_RawCDRSVector.size());
                                                ls_ErrMesg+=ls_tempValueofnumeric;
                                                ls_ErrMesg+=" cdrs for repricing";
                                                *m_ABL_ServicePtr <<INFO<<"ErrCode: "<< ls_ErrCode<<" ErrMesg: "<<ls_ErrMesg<< Endl;

                                                // take a backup of the cdrs to be repriced.
                                                if (ls_backupoldcdrs== "Y")
                                                {

                                                   ls_ErrCode = "REPRICE-3.28";
                                                   ls_ErrMesg = "....File Id => ";
                                                   ls_ErrMesg+=lv_tokens[i];
                                                   ls_ErrMesg+=":Backup cdrs being repriced";
                                                        *m_ABL_ServicePtr <<INFO<<"ErrCode: "<< ls_ErrCode<<" ErrMesg: "<<ls_ErrMesg<< Endl;

                                                        ls_sql="INSERT INTO PM_REPRICE_CDRS  SELECT *    FROM PM_RATED_CDRS where input_file_id=:1 AND reprice_seq_no=:2";
                                                        ABL_Statement   lo_Backupcdrs_ABLStatement;
                                                        lo_Backupcdrs_ABLStatement              =       lo_ABLConnection->mb_createStatement(ls_sql);
                                                        lo_Backupcdrs_ABLStatement.mb_setUInt(1,ln_FileID);
                                                        lo_Backupcdrs_ABLStatement.mb_setUInt(2,ln_RepriceSeqNo);
                                                        lo_Backupcdrs_ABLStatement.mb_executeUpdate();
                                                        lo_ABLConnection->mb_terminateStatement(lo_Backupcdrs_ABLStatement);


                                                }

                                                // delete the rated cdrs

                                                        ls_sql="delete from pm_rated_cdrs  where input_file_id=:1  AND reprice_seq_no=:2";
                                                        ABL_Statement   lo_Deletecdrs_ABLStatement;
                                                        lo_Deletecdrs_ABLStatement              =       lo_ABLConnection->mb_createStatement(ls_sql);
                                                        lo_Deletecdrs_ABLStatement.mb_setUInt(1,ln_FileID);
                                                        lo_Deletecdrs_ABLStatement.mb_setUInt(2,ln_RepriceSeqNo);
                                                        lo_Deletecdrs_ABLStatement.mb_executeUpdate();

                                                        ln_RatedCdrCount=lo_Deletecdrs_ABLStatement.mb_getAffectedRowsCount ();
                                                        lo_ABLConnection->mb_terminateStatement(lo_Deletecdrs_ABLStatement);

                                                        if (ln_RatedCdrCount != lo_PMJobPtr->ga_RawCDRSVector.size())
                                                                                                                                           
                                                        {

                                                                ls_ErrCode = "REPRICE-3.16";
                                                                ls_ErrMesg = "....File Id => ";
                                                                ls_ErrMesg+=lv_tokens[i];
                                                                ls_ErrMesg+=":Rows submitted for repricing (";
                                                                ls_tempValueofnumeric.mb_fromInt64(lo_PMJobPtr->ga_RawCDRSVector.size());
                                                                ls_ErrMesg+=ls_tempValueofnumeric;
                                                                ls_ErrMesg+=") is not equal to rows deleted (";
                                                                ls_tempValueofnumeric.mb_fromInt64(ln_RatedCdrCount);
                                                                ls_ErrMesg+=ls_tempValueofnumeric;
                                                                ls_ErrMesg+=")";
                                                                *m_ABL_ServicePtr <<INFO<<"ErrCode: "<< ls_ErrCode<<" ErrMesg: "<<ls_ErrMesg<< Endl;

                                                                return false;
                                                        }

                                                        ls_ErrCode = "REPRICE-3.17";
                                                        ls_ErrMesg = "......File Id => ";
                                                        ls_ErrMesg+=lv_tokens[i];
                                                        ls_ErrMesg+=":Deleted ";
                                                        ls_tempValueofnumeric.mb_fromInt64(ln_RatedCdrCount);
                                                        ls_ErrMesg+=ls_tempValueofnumeric;
                                                        ls_ErrMesg+=" cdrs for Reprice seq no => ";
                                                        ls_ErrMesg+=lv_tokens[0];

                                                        *m_ABL_ServicePtr <<INFO<<"ErrCode: "<< ls_ErrCode<<" ErrMesg: "<<ls_ErrMesg<< Endl;
                                                        ls_sql=" update pm_rating_atype_log set total_rated_cdrs=total_rated_cdrs-:1";
                                                        ls_sql+=" where file_id = :2 and agreement_type = :3";

                                                        ABL_Statement   lo_UpdateAtypelog_ABLStatement;
                                                        lo_UpdateAtypelog_ABLStatement          =       lo_ABLConnection->mb_createStatement(ls_sql);

                                                        lo_UpdateAtypelog_ABLStatement.mb_setUInt(1,ln_RatedCdrCount);
                                                        lo_UpdateAtypelog_ABLStatement.mb_setUInt(2,ln_FileID);
                                                        lo_UpdateAtypelog_ABLStatement.mb_setString(3,ls_Agreementtype);
                                                        lo_UpdateAtypelog_ABLStatement.mb_executeUpdate();
                                                        lo_ABLConnection->mb_terminateStatement(lo_UpdateAtypelog_ABLStatement);


                                                }//end of loop




                        *m_ABL_ServicePtr << DEBUG << "End of Getting cdrs from the PM_RATED_CDRS Table Total cdrs : " << lo_PMJobPtr->ga_RawCDRSVector.size()<< Endl;
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

bool PM_ReadRawCdrsFromDB::mb_stop()
{
        return true;
}

/*Fuction to tokenize a string.*/
void PM_ReadRawCdrsFromDB::tokenize(const std::string& in_str,std::vector<std::string>& lv_tokens,const std::string& in_delimiters )
{
        std::stringstream l_stringStream(in_str);
        std::string ls_tokenString;
        while(std::getline(l_stringStream,ls_tokenString,in_delimiters[0]))
        {
                lv_tokens.push_back(ls_tokenString);
        }
}

