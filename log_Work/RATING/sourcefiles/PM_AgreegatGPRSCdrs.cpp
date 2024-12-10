#include "PM_AgreegatGPRSCdrs.h"



extern "C" {EXPORT 
Base_Registry* gb_getPM_AgreegatGPRSCdrs()
{
	return ( (Base_Registry*) new PM_AgreegatGPRSCdrs);
}
}

PM_AgreegatGPRSCdrs::PM_AgreegatGPRSCdrs()
{
	//
}

PM_AgreegatGPRSCdrs::~PM_AgreegatGPRSCdrs()
{
	//
}

PM_AgreegatGPRSCdrs::PM_AgreegatGPRSCdrs(const PM_AgreegatGPRSCdrs& p_copyObject)
{	
	
	this->m_ABL_ServicePtr				=	p_copyObject.m_ABL_ServicePtr;
	this->ms_Stopsignalfile				=	p_copyObject.ms_Stopsignalfile;
	
	this->ms_directoryName				=	p_copyObject.ms_directoryName;
	this->ms_rawCdrFileName				=	p_copyObject.ms_rawCdrFileName;
	this->ms_ProcessedFilePath			=	p_copyObject.ms_ProcessedFilePath;
	this->ms_BackupFlag					=	p_copyObject.ms_BackupFlag;
	this->ms_ErrorFilePath				=	p_copyObject.ms_ErrorFilePath;
	this->ms_lastAgreegated             =   p_copyObject.ms_lastAgreegated;
	this->mi_CheckFreqToHit             =   p_copyObject.mi_CheckFreqToHit;
	this->mi_NumDatesAgreegate          =   p_copyObject.mi_NumDatesAgreegate;
	
}

Base_Registry* PM_AgreegatGPRSCdrs::mb_clone()
{
	return ( (Base_Registry*) new PM_AgreegatGPRSCdrs );
}

ABL_Process* PM_AgreegatGPRSCdrs::mb_createCopy()
{
	return ( new PM_AgreegatGPRSCdrs (*this));
}

bool PM_AgreegatGPRSCdrs::mb_initProcess(ABL_CacheManager* p_ABL_CacheManagerPtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr, ABL_Service *p_ABL_ServicePtr)
{
	
	try
	{
		m_ABL_ServicePtr			= p_ABL_ServicePtr;
		p_ABL_AgentCommunicatorPtr->mb_getParameter("STOP_FILE",ms_Stopsignalfile);
		p_ABL_AgentCommunicatorPtr->mb_getParameter("FilesDir",ms_directoryName);
		p_ABL_AgentCommunicatorPtr->mb_getParameter("BackupFlag",ms_BackupFlag);
		p_ABL_AgentCommunicatorPtr->mb_getParameter("ProcessFilesDir",ms_ProcessedFilePath);
		p_ABL_AgentCommunicatorPtr->mb_getParameter("ErrorFilesDir",ms_ErrorFilePath);
		p_ABL_AgentCommunicatorPtr->mb_getParameter("ToAgreegate",ms_lastAgreegated);
		mi_CheckFreqToHit           = m_ABL_ServicePtr->mb_getInt("CHECK_AGREEGATED_DB");
		mi_NumDatesAgreegate        = m_ABL_ServicePtr->mb_getInt("NUM_DATED_TO_AGREEGATE");
		mi_Appimsi                  = m_ABL_ServicePtr->mb_getParameterValue("IMSI");

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

bool PM_AgreegatGPRSCdrs::mb_getCache(ABL_CacheManager* p_ABL_CacheManagerPtr)
{
	return true;
}

bool PM_AgreegatGPRSCdrs::mb_process(ABL_Job* &p_ABL_JobPtr)
{

	PM_Job* lo_PMJobPtr    = (PM_Job*)p_ABL_JobPtr;	
	*m_ABL_ServicePtr << INFO << "Start processing  for file : " <<lo_PMJobPtr->gs_fileName << Endl;

	gr_RatingLog lr_RatingLog;	

	ABL_DateTime ls_CreateFile;
	ABL_DateTime ld_ReceivedDate;
	ABL_String ls_CdrValue ;	
	int  ln_dupFileIndex  = -1;
	char lc_strCDRValue [1000];	

	ABL_Connection	*lo_ABLConnectionPtr;
	ABL_Statement	lo_ABLStatement;
	ABL_ResultSet	lo_ABLResultSet;
	ABL_String	    ls_sql;	
	ABL_String		ms_rawCdr;
	struct stat lo_statbuffer;
    int ln_status;
	struct tm * lo_tmTimeinfo;
	char lc_FileReceivedDate[15];
	char strValue[1000];
	ABL_String		l_sql;
	ABL_String ld_TodayDate;
	ABL_DateTime ld_onDate;
	unsigned int ln_seNo=0;
	ABL_String ls_TempRawCdrs;
	//added as per LTE
	int LTEDATA;
        int ln_ErrorNums=0;
	//end

	try
	{
		
			lo_PMJobPtr->gs_IsGPRSFile="NO";
			lo_PMJobPtr->gs_AgreementType="";
			lo_PMJobPtr->gn_InPutFileId =0;
			lo_PMJobPtr->gn_RepriceSeqNo=0;

			lo_PMJobPtr->gs_BackupFlag="";
			lo_PMJobPtr->gs_ErrorFile_Path="";
			lo_PMJobPtr->gs_SourceFilePath="";
			lo_PMJobPtr->gs_ProcessedFilePath="";

			ms_rawCdrFileName=ms_directoryName;
			ms_rawCdrFileName+=lo_PMJobPtr->gs_fileName;
			lo_PMJobPtr->gs_BackupFlag=ms_BackupFlag;
			lo_PMJobPtr->gs_SourceFilePath=ms_rawCdrFileName;
			lo_PMJobPtr->gs_ErrorFile_Path=ms_ErrorFilePath;
			lo_PMJobPtr->gs_ErrorFile_Path+=lo_PMJobPtr->gs_fileName;
			lo_PMJobPtr->gs_ProcessedFilePath=ms_ProcessedFilePath;
			lo_PMJobPtr->gs_ProcessedFilePath+=lo_PMJobPtr->gs_fileName;

			ld_onDate.mb_fromSysDate();

		    /* Checking  for Duplication of the file.*/
			
			lo_ABLConnectionPtr = lo_PMJobPtr->mb_getConnection();
			ls_sql				=	"select COUNT(1)   FROM PM_PRERATING_FILES  WHERE (FILE_NAME=:1) ";
			lo_ABLStatement		=	lo_ABLConnectionPtr->mb_createStatement(ls_sql);		
			lo_ABLStatement.mb_setString(1,lo_PMJobPtr->gs_fileName );
			lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
			lo_ABLResultSet.mb_fetch();
			ln_dupFileIndex= lo_ABLResultSet.mb_getInt(1);
			lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
			lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement);
			
			if ( ln_dupFileIndex >= 1 )
			{
			
				/* Move the Duplicate file which is processed. */		
				try
				{	
					*m_ABL_ServicePtr <<INFO<< "The file : " << lo_PMJobPtr->gs_fileName << " is already rated."  << Endl;
					 rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
					return false;
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

			}

			/*********************************************************/
			memset(lc_FileReceivedDate,'\0',sizeof(lc_FileReceivedDate));

		   ln_status=stat(ms_rawCdrFileName.c_str(), &lo_statbuffer);
		   /* Get File Received Date */
		   ctime ( &lo_statbuffer.st_ctime );
		   lo_tmTimeinfo = localtime ( &lo_statbuffer.st_ctime );
		   strftime (lc_FileReceivedDate,15,"%G%m%d%k%M%S.",lo_tmTimeinfo);
		   if(lo_statbuffer.st_size<=0)
		  {
			   rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
			 *m_ABL_ServicePtr<<CRITICAL<<ms_rawCdrFileName<< ":: Empty file. Skip processing" <<Endl;
			 return false;
		  }

			/*********************************************************/
			std::ifstream inFile; 
			/* Loop through the file. */			
			inFile.open(ms_rawCdrFileName.c_str(),std::ios::in);
			if (!inFile) 
			{
				try
				{	
					rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());

					*m_ABL_ServicePtr <<CRITICAL<<"File: "<<ms_rawCdrFileName<<" not able to open" << Endl;
					inFile.close();	
					return false ;
				}		
				catch(ABL_Exception &e)
				{
					rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
					*m_ABL_ServicePtr <<CRITICAL<< "Exception :  " << e.mb_getMessage() << Endl;
					return false;
				}
			}

			while (!inFile.eof())
			{
				inFile.getline(lc_strCDRValue,READ_STRING_SIZE);
				ls_TempRawCdrs="";
				fnRemTrailSpaces(lc_strCDRValue);
				ls_TempRawCdrs=lc_strCDRValue;
				if (ls_TempRawCdrs.mb_length () == 0)
					continue;
				//modified as per LTE
				//if(ls_TempRawCdrs.mb_subStr(2, 3)=="005")
				LTEDATA=0;
				if(ls_TempRawCdrs.mb_subStr(2, 3)=="005" || ls_TempRawCdrs.mb_subStr(2, 3)=="305")
				//end
				{
					lo_PMJobPtr->gs_IsGPRSFile="YES";
					//added as per LTE
					if(ls_TempRawCdrs.mb_subStr(2, 3)=="305")
						LTEDATA=1;
					//end
				}
				else
				{
					lo_PMJobPtr->gs_IsGPRSFile="NO";

				}
				
				break;


			}
			inFile.close();
			if(lo_PMJobPtr->gs_IsGPRSFile=="NO")
			{
				return true;
			}
			
			/* Read next CDR from  raw cdr file.*/	
			/*ls_sql							=	"select pm_prerate_seq.nextval from dual";
			lo_ABLStatement					=	lo_ABLConnectionPtr->mb_createStatement(ls_sql);		
			lo_ABLResultSet					=   lo_ABLStatement.mb_executeQuery();
			lo_ABLResultSet.mb_fetch();		
			lo_PMJobPtr->gn_InPutFileId     =   lo_ABLResultSet.mb_getInt(1);
			lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
			lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement);

*/

                         double l_seq[1];

                        /* Read next CDR from  raw cdr file.*/
                        ls_sql                                          =   "select pm_prerate_seq.nextval from dual";
                        lo_ABLStatement                                 =   lo_ABLConnectionPtr->mb_createStatement(ls_sql);
                        lo_ABLResultSet                                 =   lo_ABLStatement.mb_executeQuery();
                        lo_ABLResultSet.mb_setBulkCount(1);
                        lo_ABLResultSet<<l_seq;
                       while(lo_ABLResultSet.mb_fetch())
                     {
                         int records = lo_ABLResultSet.mb_getNumArrayRows();
                         for(int i_s = 0; i_s < records ; i_s++)
                         {
                             lo_PMJobPtr->gn_InPutFileId =  l_seq[i_s];
                         }
                    }
                        lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
                        lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement);


			ls_sql							=	"INSERT INTO PM_PRERATING_FILES VALUES(:1,:2,systimestamp,systimestamp,null,null,'N')";
			lo_ABLStatement					=	lo_ABLConnectionPtr->mb_createStatement(ls_sql);
			lo_ABLStatement.mb_setInt (1,lo_PMJobPtr->gn_InPutFileId);
			lo_ABLStatement.mb_setString(2,lo_PMJobPtr->gs_fileName);
			lo_ABLStatement.mb_executeUpdate();
			lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement);


			int BULK_CDRS_COUNT=1000;
			/* Till end of the file read all the cdrs one by one .*/
			{
					unsigned int	ln_FileID[BULK_CDRS_COUNT] ;   
					unsigned int	ln_CdrSeqNo[BULK_CDRS_COUNT] ;
					ABL_String		ls_RrawCdr[BULK_CDRS_COUNT] ;
					ABL_String		ls_ChargingID[BULK_CDRS_COUNT] ;
					ABL_DbDate		ld1_CallDate[BULK_CDRS_COUNT];
					ABL_DateTime    ld_TempCallDate;
					ABL_String		ls_PartialInd[BULK_CDRS_COUNT] ;
					ABL_String      ls_PartialSeq[BULK_CDRS_COUNT] ;
					ABL_String		ls_Aggregated[BULK_CDRS_COUNT] ;
                    ABL_String      ls_IMSI[BULK_CDRS_COUNT];

                    unsigned int	ln_FileID_Dup;   
					unsigned int	ln_CdrSeqNo_Dup;
					ABL_String		ls_RrawCdr_Dup;
					ABL_String		ls_ChargingID_Dup;
					ABL_DbDate		ld1_CallDate_Dup;
					ABL_String		ls_PartialInd_Dup;
                    ABL_String      ls_PartialSeq_Dup;
					ABL_String		ls_Aggregated_Dup;
					


					int i = 0;
					std::ifstream lo_Files; 
					lo_Files.open(ms_rawCdrFileName.c_str(),std::ios::in);
					
					while (!lo_Files.eof())
					{
						
						lo_Files.getline(lc_strCDRValue,READ_STRING_SIZE);
						ls_TempRawCdrs="";
						fnRemTrailSpaces(lc_strCDRValue);
						ls_TempRawCdrs=lc_strCDRValue;
						if (ls_TempRawCdrs.mb_length () == 0)
						continue;

						ln_seNo ++;
						ln_FileID[i]=lo_PMJobPtr->gn_InPutFileId;
						ln_CdrSeqNo[i]=ln_seNo;
						ls_RrawCdr[i]=ls_TempRawCdrs;

						//added as per LTE
						std::stringstream l_stringStream(ls_TempRawCdrs.c_str());
						std::string ls_tokenString="";
                                        	int l=0;
                                        	const std::string ls_delimit="|";
						while(std::getline(l_stringStream,ls_tokenString,ls_delimit[0]))
                					{
                        					//mb_trim(ls_tokenString);
                        					switch(l)
                       	 					{
								case 0 : break;case 1 : break;case 2 : break;case 3 : break;case 4 : break;
								case 5 : 
								      ls_IMSI[i] = ls_tokenString;
								break;
								case 6 : break;case 7 : break;case 8 : break;case 9 : break;
								case 10 : break;case 11 : break;
								case 12:
								//	ls_CallDate[i] = ls_tokenString;
								ld_TempCallDate.mb_fromText(ls_tokenString.c_str(),YYYYMMDDHH24MISS);
						        ld1_CallDate[i] =  ld_TempCallDate;
                                                			break;
								case 13 : break;case 14 : break;case 15 : break;case 16 : break;case 17 : break;
                                                                case 18 : break;case 19 : break;case 20 : break;case 21 : break;case 22 : break;
                                                                case 23 : break;case 24 : break;case 25 : break;case 26 : break;case 27 : break;
                                                                case 28 : break;case 29 : break;case 30 : break;
								case 31:
									ls_PartialInd[i] = ls_tokenString;
									break;
								case 32 :
								    ls_PartialSeq[i] = ls_tokenString;
								    break;
								case 33 : break;case 34 : break;
								case 35:
									ls_ChargingID[i] = ls_tokenString;
									break;
								case 36 : break;case 37 : break;case 38 : break;case 39 : break;case 40 : break;
								case 41 : break;case 42 : break;case 43 : break;case 44 : break;case 45 : break;
                                                                case 46 : break;case 47 : break;case 48 : break;case 49 : break;case 50 : break;
                                        			}
								l++;
							}
						//ls_ChargingID[i]=ls_TempRawCdrs.mb_subStr(596, 10); 
						//ls_CallDate[i]=ls_TempRawCdrs.mb_subStr( 356, 14);
						//ls_PartialInd[i] =ls_TempRawCdrs.mb_subStr(544, 1);
						//end
						ls_Aggregated[i]="N"; 


                       if (strcmp(ls_IMSI[i].mb_subStr(0,5).c_str(),mi_Appimsi.c_str())==0)
                       {
						   continue;
                       }

						i++;		

						if (i==BULK_CDRS_COUNT)
						{
							ST_ERROR_DETAILS lr_ErrorDetail[i+1];
						        ln_ErrorNums =i;
							try
				    	{	
				 			// bulk insert the batch of 500 cdrs into PM_RAW_CDRS
							l_sql = "INSERT INTO PM_PRERATING_CDRS VALUES (:1,:2,:3,:4,:5,:6,:7,NULL,:8)";
							lo_ABLStatement = lo_ABLConnectionPtr->mb_createStatement(l_sql);	
							lo_ABLStatement.mb_setUpdateCount(i);
							lo_ABLStatement <<ln_FileID;
							lo_ABLStatement <<ln_CdrSeqNo;
							lo_ABLStatement <<ls_RrawCdr;
							lo_ABLStatement <<ls_ChargingID;
							lo_ABLStatement <<ld1_CallDate;
							lo_ABLStatement <<ls_PartialInd;
							lo_ABLStatement <<ls_Aggregated;
							lo_ABLStatement <<ls_PartialSeq;
							lo_ABLStatement.mb_executeArrayUpdate(&ln_ErrorNums,lr_ErrorDetail); 
							lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement);
							i = 0;
						 }				
				  	catch(ABL_Exception &e)
					{
					
						//std::cout<<e.mb_getMessage()<<" total cdrs got error: " <<ln_ErrorNums<<std::endl;
                          i=0;
							if(ln_ErrorNums!=0)
							{
								for(int n=0;n<ln_ErrorNums;n++)
								{
								//	std::cout<<"ln_ErrorNums : "<<ln_ErrorNums<<std::endl;

									ABL_String lc_ErrorMsg = lr_ErrorDetail[n].m_arrErrorMsg;
								//	ABL_String ltemp="";
								//	ltemp=lc_ErrorMsg.mb_subStr(0,9);
								//	std::cout<<n<<":"<<ltemp<<":"<<lc_ErrorMsg<<"Record No: "<<lr_ErrorDetail[n].m_irowNum<<std::endl;

									

									if((lc_ErrorMsg.mb_subStr(0,9)) == "ORA-00001")
									{
									ABL_String l_sql1;
                                 	ln_FileID_Dup=ln_FileID[lr_ErrorDetail[n].m_irowNum];   
						            ln_CdrSeqNo_Dup=ln_CdrSeqNo[lr_ErrorDetail[n].m_irowNum];;
						            ls_RrawCdr_Dup=ls_RrawCdr[lr_ErrorDetail[n].m_irowNum];
						            ls_ChargingID_Dup=ls_ChargingID[lr_ErrorDetail[n].m_irowNum];
						            ld1_CallDate_Dup=ld1_CallDate[lr_ErrorDetail[n].m_irowNum];
					                ls_PartialInd_Dup=ls_PartialInd[lr_ErrorDetail[n].m_irowNum];
						            ls_Aggregated_Dup=ls_Aggregated[lr_ErrorDetail[n].m_irowNum];
									ls_PartialSeq_Dup=ls_PartialSeq[lr_ErrorDetail[n].m_irowNum];




							l_sql1 = "INSERT  INTO PM_PRERATING_CDRS_DUPLICATE VALUES (:1,:2,:3,:4,:5,:6,:7,NULL,:8)";
							lo_ABLStatement = lo_ABLConnectionPtr->mb_createStatement(l_sql1);	
							lo_ABLStatement.mb_setInt(1,ln_FileID_Dup);
			                lo_ABLStatement.mb_setInt(2,ln_CdrSeqNo_Dup);
							lo_ABLStatement.mb_setString (3,ls_RrawCdr_Dup);
			                lo_ABLStatement.mb_setString(4,ls_ChargingID_Dup);
							lo_ABLStatement.mb_setDate (5,ld1_CallDate_Dup);
			                lo_ABLStatement.mb_setString(6,ls_PartialInd_Dup);
		                 	lo_ABLStatement.mb_setString (7,ls_Aggregated_Dup);		
							lo_ABLStatement.mb_setString (8,ls_PartialSeq_Dup);	
							lo_ABLStatement.mb_executeUpdate();
							lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement);
              			}	
									else 
									{
										 rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
							             *m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
							             *m_ABL_ServicePtr<<INFO<<"Stop signal Create in the path  :: : "<<ms_Stopsignalfile.c_str() <<Endl;
							             ABL_String l_command("echo .> ");
					                     l_command +=ms_Stopsignalfile.c_str();			
							             system(l_command.c_str());
							             return false;
									}
								}
					 }

					}
						 
					catch(...)
					{
						rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
						ABL_String ls_command("touch ");
						ls_command +=ms_Stopsignalfile;
						 system(ls_command.c_str()); 	
						*m_ABL_ServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
						lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement);
						return false;
					}	 
						 }				
				  
				  }  //END reading file
               

				  lo_Files.close();
				  if(i>0 && i<BULK_CDRS_COUNT)
					{
						  ST_ERROR_DETAILS lr_ErrorDetail[i+1];
						  ln_ErrorNums=i;
					  	 try
						 {
							l_sql = "INSERT INTO PM_PRERATING_CDRS  VALUES (:1,:2,:3,:4,:5,:6,:7,NULL,:8)";
							lo_ABLStatement = lo_ABLConnectionPtr->mb_createStatement(l_sql);
							lo_ABLStatement.mb_setUpdateCount(i);
							lo_ABLStatement <<ln_FileID;
							lo_ABLStatement <<ln_CdrSeqNo;
							lo_ABLStatement <<ls_RrawCdr;
							lo_ABLStatement <<ls_ChargingID;
							lo_ABLStatement <<ld1_CallDate;
							lo_ABLStatement <<ls_PartialInd;
							lo_ABLStatement <<ls_Aggregated;
							lo_ABLStatement <<ls_PartialSeq;
							lo_ABLStatement.mb_executeArrayUpdate(&ln_ErrorNums,lr_ErrorDetail); 
							lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement);
							i = 0;         
						 }
	                 catch(ABL_Exception &e)
					{
						i=0;
						//std::cout<<e.mb_getMessage()<<" total cdrs got error: " <<ln_ErrorNums<<std::endl;
							if(ln_ErrorNums!=0)
							{
								for(int n=0;n<ln_ErrorNums;n++)
								{

									ABL_String lc_ErrorMsg = lr_ErrorDetail[n].m_arrErrorMsg;
									/*ABL_String ltemp="";
									ltemp=lc_ErrorMsg.mb_subStr(0,9);
									std::cout<<n<<":"<<ltemp<<":"<<lc_ErrorMsg<<"Record No: "<<lr_ErrorDetail[n].m_irowNum<<std::endl;*/

									if((lc_ErrorMsg.mb_subStr(0,9)) == "ORA-00001")
									{
						        	ABL_String l_sql1;
                                 	ln_FileID_Dup=ln_FileID[lr_ErrorDetail[n].m_irowNum];   
						            ln_CdrSeqNo_Dup=ln_CdrSeqNo[lr_ErrorDetail[n].m_irowNum];;
						            ls_RrawCdr_Dup=ls_RrawCdr[lr_ErrorDetail[n].m_irowNum];
						            ls_ChargingID_Dup=ls_ChargingID[lr_ErrorDetail[n].m_irowNum];
						            ld1_CallDate_Dup=ld1_CallDate[lr_ErrorDetail[n].m_irowNum];
					                ls_PartialInd_Dup=ls_PartialInd[lr_ErrorDetail[n].m_irowNum];
						            ls_Aggregated_Dup=ls_Aggregated[lr_ErrorDetail[n].m_irowNum];
									ls_PartialSeq_Dup=ls_PartialSeq[lr_ErrorDetail[n].m_irowNum];


     						l_sql1 = "INSERT  INTO PM_PRERATING_CDRS_DUPLICATE VALUES (:1,:2,:3,:4,:5,:6,:7,NULL,:8)";
							lo_ABLStatement = lo_ABLConnectionPtr->mb_createStatement(l_sql1);	
							lo_ABLStatement.mb_setInt(1,ln_FileID_Dup);
			                lo_ABLStatement.mb_setInt(2,ln_CdrSeqNo_Dup);
							lo_ABLStatement.mb_setString (3,ls_RrawCdr_Dup);
			                lo_ABLStatement.mb_setString(4,ls_ChargingID_Dup);
							lo_ABLStatement.mb_setDate (5,ld1_CallDate_Dup);
			                lo_ABLStatement.mb_setString(6,ls_PartialInd_Dup);
		                 	lo_ABLStatement.mb_setString (7,ls_Aggregated_Dup);	
							lo_ABLStatement.mb_setString (8,ls_PartialSeq_Dup);	
							lo_ABLStatement.mb_executeUpdate();
							lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement);
							}	
									else 
									{
										 rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
							             *m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
							             *m_ABL_ServicePtr<<INFO<<"Stop signal Create in the path  :: : "<<ms_Stopsignalfile.c_str() <<Endl;
							             ABL_String l_command("echo .> ");
					                     l_command +=ms_Stopsignalfile.c_str();			
							             system(l_command.c_str());
								        return false;
									}
								}
					 }
                  	}

						 catch(ABL_Exception &e)
						 {
							 rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
							*m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
							*m_ABL_ServicePtr<<INFO<<"Stop signal Create in the path  :: : "<<ms_Stopsignalfile.c_str() <<Endl;
							ABL_String l_command("echo .> ");
							l_command +=ms_Stopsignalfile.c_str();			
							system(l_command.c_str());
							return false;
						 }
					}
			}
	
                        *m_ABL_ServicePtr << DEBUG <<"File Name insertion Done :"<<lo_PMJobPtr->gs_fileName<<" File Id :"<<lo_PMJobPtr->gn_InPutFileId << Endl;
			lo_ABLConnectionPtr->mb_commit();
			
			if(lo_PMJobPtr->gs_BackupFlag=="Y")
				{
						rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ProcessedFilePath.c_str());				
				}
				else
				{		
						unlink(lo_PMJobPtr->gs_SourceFilePath.c_str());				
				}

				//fetch all cdrs to aggregate
				lo_PMJobPtr->gn_InPutFileId =0;
				unsigned int ln_OriCdrCount=0;
				unsigned int ln_AggCdrCount=0;
				ABL_String ls_CreateFile = "Y";
				ABL_String ls_NewRawCdr="";
				//added as per LTE
				ABL_String ls_NewRawCdr1="";
				ABL_String ls_NewRawCdr2="";
				//end
				ABL_String	ls_ErrCode="";
				ABL_String	ls_ErrMesg="";

				ABL_String ls_chargingID[500];
				ABL_DbDate ld_CallDate[500];
				unsigned int ln_PartialCount[500];
				ABL_DbDate ld_MinCallDate[500];
				ABL_DbDate ld_MaxCallDate[500];
				/*unsigned int ln_Duration[100];
				unsigned int ln_TotalIncVolume[100];
				unsigned int ln_TotalOutVolume[100];		*/
				double ln_Duration[500];
                                double ln_TotalIncVolume[500];
                                double ln_TotalOutVolume[500];
				int ChkMinFreq;
				ABL_String ld_MinParCallDate ="";
                                ABL_String  ld_Partition[50];

                        ls_sql="select (to_date(to_char(sysdate,'YYYYMMDDHH24MISS'),'YYYYMMDDHH24MISS') - to_date(:1,'YYYYMMDDHH24MISS'))*24*60 from dual";
			lo_ABLStatement   =   lo_ABLConnectionPtr->mb_createStatement(ls_sql) ;
			lo_ABLStatement.mb_setString(1,ms_lastAgreegated);
			lo_ABLResultSet   =   lo_ABLStatement.mb_executeQuery();
			if(lo_ABLResultSet.mb_fetch())
			ChkMinFreq    =   lo_ABLResultSet.mb_getInt(1) ;
			lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet)       ;
			lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement)  ;

                        ls_sql="SELECT NVL(TO_CHAR(MIN(CALL_DATE),'YYYYMMDD'),'N') FROM PM_PRERATING_CDRS WHERE AGGREGATED='N' AND CALL_DATE>SYSDATE -:1 AND CALL_DATE<TRUNC(SYSDATE)";
                        lo_ABLStatement   =   lo_ABLConnectionPtr->mb_createStatement(ls_sql) ;
                        lo_ABLStatement.mb_setInt(1,mi_NumDatesAgreegate);
                        lo_ABLResultSet   =   lo_ABLStatement.mb_executeQuery();
                        if(lo_ABLResultSet.mb_fetch())
                        ld_MinParCallDate    =   lo_ABLResultSet.mb_getString(1) ;
                        lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet)       ;
                        lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement)  ;



             if((ChkMinFreq>mi_CheckFreqToHit || ChkMinFreq ==0) && (strcmp(ld_MinParCallDate.c_str(),"N")!=0))
				{	

            *m_ABL_ServicePtr << DEBUG <<"Starting to Agreegate non Agreegated Cdrs"<< Endl;
                  
	 
	    	ls_sql="select to_char(sysdate-1/1000,'YYYYMMDDHH24MISS') from dual";
			lo_ABLStatement   =   lo_ABLConnectionPtr->mb_createStatement(ls_sql) ;
			lo_ABLResultSet   =   lo_ABLStatement.mb_executeQuery();
			if(lo_ABLResultSet.mb_fetch())
			ms_lastAgreegated    =   lo_ABLResultSet.mb_getString(1) ;	
			lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet)       ;
			lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement)  ;
	


			ABL_Statement	lo_ABLParStatement;
            ABL_ResultSet	lo_ABLParResultSet;


			ls_sql="SELECT TO_CHAR(TO_DATE (:1, 'YYYYMMDD') + ROWNUM - 1,'YYYYMMDD') dt   FROM DUAL where rownum<2  CONNECT BY LEVEL <=(sysdate-1) - TO_DATE (:1, 'YYYYMMDD')+ 1";
			lo_ABLParStatement   =   lo_ABLConnectionPtr->mb_createStatement(ls_sql) ;
			lo_ABLParStatement.mb_setString(1,ld_MinParCallDate);
			lo_ABLParResultSet   =   lo_ABLParStatement.mb_executeQuery();
            lo_ABLParResultSet.mb_setBulkCount(50);
            lo_ABLParResultSet	<<  ld_Partition;
			while(lo_ABLParResultSet.mb_fetch())
				{
				    int records_l = lo_ABLParResultSet.mb_getNumArrayRows();
					for(int i_l = 0; i_l < records_l ; i_l++)
					{
					  try
						  {


		    /*modified as per LTE
				ls_sql				=	" SELECT   charging_id,TRUNC (TO_DATE (call_date, 'YYYYMMDDHH24MISS')) call_date,COUNT (*) partial_count, MIN (call_date) min_call_date,MAX (call_date) max_call_date,SUM (SUBSTR (raw_cdr, 372, 10)) DURATION,SUM (SUBSTR (raw_cdr, 383, 10)) total_inc_volume,SUM (SUBSTR (raw_cdr, 394, 10)) total_out_volume FROM pm_prerating_cdrs WHERE aggregated = 'N' AND charging_id > RPAD (' ', 10) ";
				ls_sql				+=	" AND TO_DATE (call_date, 'YYYYMMDDHH24MISS') < TRUNC (SYSDATE) GROUP BY charging_id, TRUNC (TO_DATE (call_date, 'YYYYMMDDHH24MISS'))";  
			*/

				ls_sql                          =       " SELECT * FROM (SELECT  /*+ index(PM_PRERATE_CDRS_N$PERF) */  charging_id,TRUNC(call_date) call_date,COUNT (*) partial_count, MIN (call_date) min_call_date,MAX (call_date) max_call_date,SUM (substr(raw_cdr, INSTR(raw_cdr,'|',1,13)+1, INSTR(raw_cdr,'|',1,14)- INSTR(raw_cdr,'|',1,13)-1)) DURATION,SUM (substr(raw_cdr, INSTR(raw_cdr,'|',1,14)+1, INSTR(raw_cdr,'|',1,15)- INSTR(raw_cdr,'|',1,14)-1)) total_inc_volume,SUM (substr(raw_cdr, INSTR(raw_cdr,'|',1,15)+1, INSTR(raw_cdr,'|',1,16)- INSTR(raw_cdr,'|',1,15)-1)) total_out_volume FROM pm_prerating_cdrs WHERE aggregated = 'N' ";
				ls_sql                          +=      " AND call_date >=TO_DATE(:1 || '000000','YYYYMMDDHH24MISS') AND call_date <= TO_DATE(:1 || '235959','YYYYMMDDHH24MISS') AND charging_id > 0  GROUP BY charging_id, TRUNC (call_date),aggregated ) where rownum < 200001";
				//end
				lo_ABLStatement		=	lo_ABLConnectionPtr->mb_createStatement(ls_sql);
                lo_ABLStatement.mb_setString(1,ld_Partition[i_l]);
                lo_ABLResultSet	=lo_ABLStatement.mb_executeQuery();
				lo_ABLResultSet.mb_setBulkCount(500);
				lo_ABLResultSet	<<ls_chargingID;
				lo_ABLResultSet	<<ld_CallDate;
				lo_ABLResultSet	<<ln_PartialCount;
				lo_ABLResultSet	<<ld_MinCallDate;
				lo_ABLResultSet	<<ld_MaxCallDate;
				lo_ABLResultSet	<<ln_Duration;
				lo_ABLResultSet	<<ln_TotalIncVolume;
				lo_ABLResultSet	<<ln_TotalOutVolume;
				while(lo_ABLResultSet.mb_fetch())
				{
					int records = lo_ABLResultSet.mb_getNumArrayRows();
					for(int i = 0; i < records ; i++)
					{
			
						  try
						  {
		  					 ln_OriCdrCount = ln_OriCdrCount +ln_PartialCount[i];
							 if (ls_CreateFile == "Y")
							  {
								ls_CreateFile= "N";
								// make file and insert into raw cdrs table for further rating
								ABL_String ls_filename=lo_PMJobPtr->gs_fileName;
								ld_TodayDate="";
								ld_TodayDate=ld_onDate.mb_toString(YYYYMMDDHH24MISS);
								lo_PMJobPtr->gs_fileName="";
								//added as per LTE
								if(LTEDATA==1)
								{
									lo_PMJobPtr->gs_fileName= "DATA_";
								}
								else
								{
								//end
									lo_PMJobPtr->gs_fileName= "GPRS_";
								}
								lo_PMJobPtr->gs_fileName+=ls_filename;
								lo_PMJobPtr->gs_fileName+="_";
								lo_PMJobPtr->gs_fileName+= ld_TodayDate;

								ABL_Statement	lo_FIleSeqABLStatement;
								ABL_ResultSet	lo_FIleSeqABLResultSet;

						/*		ls_sql							=	"select pm_rating_file_seq.nextval from dual";
								lo_FIleSeqABLStatement					=	lo_ABLConnectionPtr->mb_createStatement(ls_sql);		
								lo_FIleSeqABLResultSet					=   lo_FIleSeqABLStatement.mb_executeQuery();
								lo_FIleSeqABLResultSet.mb_fetch();		
								lo_PMJobPtr->gn_InPutFileId     =   lo_FIleSeqABLResultSet.mb_getInt(1);
								lo_FIleSeqABLStatement.mb_closeResultSet(lo_FIleSeqABLResultSet);
								lo_ABLConnectionPtr->mb_terminateStatement(lo_FIleSeqABLStatement); */

								double l_seq1[1];

								ls_sql							=	"select pm_rating_file_seq.nextval from dual";
								lo_FIleSeqABLStatement					=	lo_ABLConnectionPtr->mb_createStatement(ls_sql);		
								lo_FIleSeqABLResultSet					=   lo_FIleSeqABLStatement.mb_executeQuery();
								lo_FIleSeqABLResultSet.mb_setBulkCount(1);
                                lo_FIleSeqABLResultSet<<l_seq1;
   		                        while(lo_FIleSeqABLResultSet.mb_fetch())
                                {
                                int record = lo_FIleSeqABLResultSet.mb_getNumArrayRows();
                                for(int s_j = 0; s_j < record ; s_j++)
                                {
                                lo_PMJobPtr->gn_InPutFileId  =  l_seq1[s_j];
				                }
		                        }
		  						lo_FIleSeqABLStatement.mb_closeResultSet(lo_FIleSeqABLResultSet);
								lo_ABLConnectionPtr->mb_terminateStatement(lo_FIleSeqABLStatement);
							  }

							ln_AggCdrCount= ln_AggCdrCount + 1;

							//get the first cdr for the day
							ABL_Statement	lo_RawABLStatement;
							ABL_ResultSet	lo_RawABLResultSet;
							ABL_String		ls_RawCdr="";
							ls_NewRawCdr	="";

							ls_sql	="select raw_cdr from pm_prerating_cdrs  where charging_id=:1 and call_date = :2 and rownum = 1";
							lo_RawABLStatement		=	lo_ABLConnectionPtr->mb_createStatement(ls_sql);
							lo_RawABLStatement.mb_setString(1,ls_chargingID[i]);
							lo_RawABLStatement.mb_setDate(2,ld_MinCallDate[i]);

							lo_RawABLResultSet	=lo_RawABLStatement.mb_executeQuery();
							lo_RawABLResultSet.mb_fetch();		
							ls_RawCdr=lo_RawABLResultSet.mb_getString(1);
							lo_RawABLStatement.mb_closeResultSet(lo_RawABLResultSet);
							lo_ABLConnectionPtr->mb_terminateStatement(lo_RawABLStatement);
							 //do the aggregation only if count > 1
							 if (ln_PartialCount[i] > 1) 
							  {
								/* make a new cdr for the charging id, by replacing 
								--    * duration = sum of call duration for the date of aggregation
								--    * data vol inc = sum of total inc vol for the date of aggregation
								--    * data vol out = sum of total out vol for the date of aggregation
								--    * partial indicator = null , added on 12 Aug 2010.
							   -- ls_NewRawCdr := substr(ls_RawCdr,1,371)||rpad(to_char(c_Cdrs.Duration),10)||'|'||rpad(to_char(c_Cdrs.Total_Inc_Volume),10)||'|'||rpad(to_char(c_Cdrs.Total_Out_Volume),10)||'|'||substr(ls_RawCdr,405,235);*/
								char ls_TempCdrs[ls_RawCdr.mb_length()];
								memset(ls_TempCdrs,'\0',sizeof(ls_TempCdrs));
								ABL_String ls_TempCdrConvert="";
								
								//added as per LTE
                                                		std::stringstream l_stringStream(ls_RawCdr.c_str());
                                                		std::string ls_tokenString="";
                                                		int l=1;
                                                		const std::string ls_delimit="|";
								ls_NewRawCdr="";
								ls_NewRawCdr1="";
								ls_NewRawCdr2="";
								/*changes done to rand number of columns from rating.conf file*/
								int cdr_file_col1=m_ABL_ServicePtr->mb_getInt("NUMBER_OF_COLUMNS_IN_FILE");
								while(l<=cdr_file_col1)
									{
                                                				std::getline(l_stringStream,ls_tokenString,ls_delimit[0]);
										if(l>=1&&l<=13)
                                                        				ls_NewRawCdr += ls_tokenString+"|";
										else if(l>=17&&l<=31)
											ls_NewRawCdr1 += ls_tokenString+"|";	
										else if(l>=33&&l<=cdr_file_col1)
											ls_NewRawCdr2 +=ls_tokenString+"|";
                                                                		l++;
                                                        		}
								
								ls_TempCdrConvert.mb_fromDouble(ln_Duration[i]);
								ls_NewRawCdr+=ls_TempCdrConvert+"|";
								//ls_TempCdrConvert.mb_fromInt64(ln_TotalIncVolume[i]);
								ls_TempCdrConvert.mb_fromDouble(ln_TotalIncVolume[i]);								
								ls_NewRawCdr+=ls_TempCdrConvert+"|";
								ls_TempCdrConvert.mb_fromDouble(ln_TotalOutVolume[i]);
								ls_NewRawCdr+=ls_TempCdrConvert+"|";
								ls_NewRawCdr+=ls_NewRawCdr1+"| ";
								ls_NewRawCdr+=ls_NewRawCdr2;
								//end
							  }
							 else if (ln_PartialCount[i] = 1)
							  {
								//do not replace the duration/data volume if single cdr
								ls_NewRawCdr = ls_RawCdr;
							  }

							 //insert into raw cdrs array
							lo_PMJobPtr->ga_RawCDRSVector.push_back(ls_NewRawCdr);

							ABL_Statement	lo_UpdateABLStatement;
							unsigned int ln_RowsUpdated=0;

							 //update rows in pm_prerating_cdrs table with the generated file id
							ls_sql	= "update /*+ index(PM_PRERATE_CDRS_N$PERF) */ pm_prerating_cdrs set aggregated = 'Y',rating_file_id = :1 where charging_id = :2 ";
							ls_sql	+=" and trunc(call_date) = :3 and aggregated = 'N'";
							lo_UpdateABLStatement		=	lo_ABLConnectionPtr->mb_createStatement(ls_sql);
							lo_UpdateABLStatement.mb_setInt(1,lo_PMJobPtr->gn_InPutFileId);
							lo_UpdateABLStatement.mb_setString(2,ls_chargingID[i]);
							lo_UpdateABLStatement.mb_setDate(3,ld_CallDate[i]);
							lo_UpdateABLStatement.mb_executeUpdate();
							ln_RowsUpdated=lo_UpdateABLStatement.mb_getAffectedRowsCount ();							
							lo_ABLConnectionPtr->mb_terminateStatement(lo_UpdateABLStatement);
							 if (ln_RowsUpdated != ln_PartialCount[i])
							  {
								 ABL_String ls_TempConvert="";
								ls_ErrCode = "GPRS-1.3";
								ls_ErrMesg = "Count of cdrs for charging id => ";
								ls_ErrMesg +=ls_chargingID[i];
								ls_ErrMesg +="(";
								ls_TempConvert.mb_fromInt(ln_PartialCount[i]);
								ls_ErrMesg +=ls_TempConvert;
								ls_ErrMesg +=") not equal to count of rows updated (";
								ls_TempConvert="";
								ls_TempConvert.mb_fromInt(ln_RowsUpdated);
								ls_ErrMesg +=ls_TempConvert;
								ls_ErrMesg+=")";
								throw   ABL_Exception(1,ls_ErrMesg.c_str());
							  }
							}
						  catch (ABL_Exception &e)
						  {
							  rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
								ABL_String ls_command("touch ");
								ls_command +=ms_Stopsignalfile;
								system(ls_command.c_str()); 	
								*m_ABL_ServicePtr<<CRITICAL<<"error code : "<<e.mb_getErrorCode() <<" error description: "<<e.mb_getMessage()  <<Endl;
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
					}
			}

            lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet)       ;
			lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLStatement)  ;
		}
            
                         catch (ABL_Exception &e)
						  {
							  rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
								ABL_String ls_command("touch ");
								ls_command +=ms_Stopsignalfile;
								system(ls_command.c_str()); 	
								*m_ABL_ServicePtr<<CRITICAL<<"error code : "<<e.mb_getErrorCode() <<" error description: "<<e.mb_getMessage()  <<Endl;
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
	}
}
	       lo_ABLParStatement.mb_closeResultSet(lo_ABLParResultSet)       ;
			lo_ABLConnectionPtr->mb_terminateStatement(lo_ABLParStatement)  ;





			}
			if(lo_PMJobPtr->ga_RawCDRSVector.size()>0)
			{
				//'GPRS_'||to_char(sysdate,'YYYYMMDDHH24MISS
				//lr_RatingLog.gs_CdrFileName				=	lo_PMJobPtr->gs_fileName;						
				//added as per LTE
				 if(LTEDATA==1)
                                 {
					lr_RatingLog.gs_CdrFileName                             =       "DATA_";
                                 }
                                 else
                                 {
                                 	lr_RatingLog.gs_CdrFileName                             =       "GPRS_";
                                 }
				//end
				//lr_RatingLog.gs_CdrFileName				=	"GPRS_";
				lr_RatingLog.gs_CdrFileName				+=	ld_onDate.mb_toString();
				lr_RatingLog.gd_ReceivedOn				=	ld_onDate;	
				lr_RatingLog.gd_ProcessStartTime.mb_fromSysDate();
				lr_RatingLog.gs_Processed				=	"N";		
				lr_RatingLog.gn_FileId					=	lo_PMJobPtr->gn_InPutFileId ;
				lr_RatingLog.gn_ProcessingTimeInSecs	=	0;
				lr_RatingLog.gs_Chrono			     	=	"";
				lr_RatingLog.gs_EdChrono				=	"";
				lr_RatingLog.gn_TotalEvents				=	0;
				lr_RatingLog.gn_IncTotalEvents			=	0;
				lr_RatingLog.gn_IncRatedEvents			=	0;
				lr_RatingLog.gn_IncDroppedEvents		=	0;
				lr_RatingLog.gn_IncRejectedEvents		=   0;
				lr_RatingLog.gn_OutTotalEvents			=	0;
				lr_RatingLog.gn_OutRatedEvents			=	0;
				lr_RatingLog.gn_OutDroppedEvents		=	0;
				lr_RatingLog.gn_OutRejectedEvents		=	0;
				lr_RatingLog.gs_Processed				=	"Y";
				lo_PMJobPtr->ga_RatingLog.push_back(lr_RatingLog);				
			}

			*m_ABL_ServicePtr << DEBUG << "End of processing for file : " << lo_PMJobPtr->gs_fileName <<" Total gprs cdrs: "<<lo_PMJobPtr->ga_RawCDRSVector.size()<<" GPRS Flag: "<<lo_PMJobPtr->gs_IsGPRSFile<< Endl;
			lo_ABLConnectionPtr->mb_commit();
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

bool PM_AgreegatGPRSCdrs::mb_stop()
{
	return true;
}

/* remove trailing spaces from the string */
void  PM_AgreegatGPRSCdrs :: fnRemTrailSpaces (char *pszBuffer)
{
   int Index = 0;
   char szTempBuf[4096] = {'\0'};

   /*
   ** Check if input buffer is null
   */

   if (!pszBuffer)
   {
   /*
   ** Buffer is null
   */
      return;
   }

   Index = strlen(pszBuffer) -1;
   for ( ; Index >= 0 ; --Index)
   {
      if (pszBuffer[Index] != ' ')
      {
         break;
      }
   }

   if (Index < 0)
   {
      /*
      ** No white spaces found at end
      */
      return;
   }

   /*
   ** Terminate the buffer
   */
   pszBuffer[Index+1] = '\0';
      return;

}/* RemoveWhiteSpaceatEnd */
