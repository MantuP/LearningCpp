//Changed by Imam for the ghana LTE calls, to consider the cdrs with recording entity type 8 as LTE cdrs as recording entity type 7 is not coming in cdrs.
//Changed on 2019-Feb-08 by Imam for LTE issue
#include "global.h"
#include <asn-incl.h>
#include <sys/file.h>
#include <sys/stat.h>
#if HAVE_FCNTL_H
#include <fcntl.h>
#endif
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <c-lib/inc/sbuf.h>
#include <tap312.h>

#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <c-lib/inc/asn-incl.h>

#include <sqlca.h>
#include <string.h>
#include <sys/file.h>
#include <time.h>
#if HAVE_FCNTL_H
#include <fcntl.h>
#endif

#define INIT_STR(vc_x) (memset(vc_x,'\0',sizeof(vc_x)));

extern int   gExchangeRateCount ;
extern int   gTaxationCount ;
extern int   gDiscountingCount ;
extern int   gUTCOffsetCount ;
extern int   gRecEntityInfoCount ;
extern char  gFileVplmnCode[6] ;
extern char  gFileHplmnCode[6] ;
extern char  gFileSequenceNumber[6] ;
extern char  gSystemDate[15];
extern char  gLocalCurrencyCode[4];
extern long  gExchangeRate[10];
long         gBulkErrorDetailsIndex= 0 ;
extern int   gRejectedErrorNo  ; 
extern int   gErrorCDRsCount  ; 
extern double   gErrorCDRsCharge ; 
extern double   gErrorCDRsTax ; 
extern double   gErrorCDRsDiscount ; 
extern double   gErrorCDRsDuration; 
extern double   gErrorCDRsIncVolume; 
extern double   gErrorCDRsOutVolume; 
extern int    gCDRErrorFlag   ; 
extern int    gFileAge; 
extern char   gGenerateFilesFlg[2];
extern char   gIOTChargeContext[60];
extern char   gIOTTaxContext[60];
extern char   gIOTDiscountContext[60];
int    gErrorNode ;
int          gCurrencyConversionFlag = 0;
int          gTaxationFlag = 0;
int          gTaxListFlag  = 0;
int          gDiscountFlag = 0;
int          gExchangeRateCodeFlag = 0;
int          gDiscountCodeFlag = 0;
int          gRecordingEntityFlag = 0;
int          gUTCOffSetFlag = 0;
int          gDestinationFlag = 0;
int          gCalledNumberFlag = 0 ;
int          gDestNumberFlag = 0 ;
int          gCamelDestNumberFlag = 0 ;
int          gGPRSDestNumberFlag = 0;
int          gChargingTimeStamp = 0;
int          gDateDifference = 0 ;
extern int   gTotalCdrsCount;
extern char  gImsiPrefix[101];
extern long  gFatalErrorCount;
extern char  g_CdrStartDate[15];
extern char  gCheckCallAgeFlag[2]  ;
extern char  gCheckFileAgeFlag[2]  ;
extern char  gFileStartDate[15] ;
extern long gCdrsArrayCount ;
int          gValidateHPLMNPrefix  ;
int          gValidateVPLMNPrefix  ;
extern char  gMobilePrfx[7];
char CalledNumberPrefix[7];
extern int gTapSpecificationVersion;
extern int gTapReleaseVersion;
extern int gTapinTaxFlag;
int gNetworkEntityInfoCount =0;
int CalledFlag =0;
char lc_ChargeType[4];

/* Function Declarations */
int CheckFileType(char* p_szFileNamePtr);

int  ReadBCI();
int  ReadACC();
int  ReadNI();
int ValidateTBGroupInfo();
int ValidateNTGroupInfo();
int fnCheckPLMNPrefix(char FieldName[6]);

void InitialiseBasicCallType();

void  ReadChargeableSubscriber(struct ChargeableSubscriber *chargeableSubscriber);
void  ReadCallEventStartTimeStamp(CallEventStartTimeStamp *callEventStartTimeStamp);

int  ReadMOC(struct MobileOriginatedCall* mobileOriginatedCall);
void ReadMoBasicCallInformation(struct MoBasicCallInformation* basicCallInformation);
void ReadDestination(struct Destination* destination);

int  ReadMTC(struct MobileTerminatedCall* mobileTerminatedCall);
void ReadMtBasicCallInformation(struct MtBasicCallInformation* basicCallInformation);
void ReadCallOriginator(struct CallOriginator* callOriginator);

void ReadLocationInformation(struct LocationInformation* locationInformation);
void ReadBasicServiceUsed(BasicServiceUsed* basicServiceUsed);

void ReadBasicService(struct BasicService* basicService);
void ReadChargeInformationList(ChargeInformation *CI,int CICount);
void ReadThreeGcamelDestination(struct ThreeGcamelDestination* threeGcamelDestination);
void ReadDiscountInformation(struct DiscountInformation* discountInformation);
void ReadCamelServiceUsed(struct CamelServiceUsed* camelServiceUsed);

int  ReadSUP(struct SupplServiceEvent *supplServiceEvent);
void ReadSSE(struct SupplServiceEvent *supplServiceEvent);
void ReadSSU(struct ServiceCentreUsage* serviceCentreUsage);
int  ReadGprsCall(struct GprsCall* gprsCall);
void ReadGprsBasicCallInfo(struct GprsBasicCallInformation* gprsBasicCallInformation);
void ReadGprsLocationInfo(struct GprsLocationInformation* gprsLocationInformation);
void ReadGprsServiceUsed(struct GprsServiceUsed* gprsServiceUsed);

void ReadGprsBasicCallInformation(struct GprsBasicCallInformation* basicCallInformation);
void ReadGprsChargeableSubscriber(struct GprsChargeableSubscriber *chargeableSubscriber);
void ReadGprsLocationInformation(struct GprsLocationInformation* locationInformation);


void ReadContentTransaction(struct ContentTransaction* contentTransaction);
void ReadContentTransactionBasicInfo(struct ContentTransactionBasicInfo *BI);
void ReadChargedPartyInfo(struct ChargedPartyInformation* CPI);
void ReadServingPartyInfo(struct ServingPartiesInformation *PI);
void ReadContentServiceUsed(ContentServiceUsed *CSU);

void ReadLocationService(struct LocationService *LS);
void ReadTrackingCustomerInfo(struct TrackingCustomerInformation* TCI);
void ReadLCSSPInfo(struct LCSSPInformation* LSI);
void ReadTrackedCustomerInfo(struct TrackedCustomerInformation* TCI);
void ReadLocationServiceUsage(struct LocationServiceUsage* LSU);

int  ReadMSESS(struct MobileSession* mobileSession);
void ReadChargedParty(struct ChargedParty* chargedParty);
void ReadServiceStartTimestamp(ServiceStartTimestamp *serviceStartTimestamp);
void ReadNonChargedParty(NonChargedParty* nonChargedParty);
void ReadSessionChargeInformationList(SessionChargeInformation *SCI,int SCICount);
void ReadRecEntityCodeList(RecEntityCodeList* recEntityCodeList);
int fnValidateIPV4(char  FieldValue[46]) ;
int fnValidateIPV6(char FieldValue[46]);
int  ReadNotification();

int ReadMESG(struct MessagingEvent* messagingEvent);
void ReadNetworkElementList(NetworkElement *NE,int NECount);


void fnDconvhx (int, unsigned char* ,char*, char);
void fnRemTrailSpaces (char *pszBuffer);
int  fnCountryCodeCheck(char FieldName[85]);

void InitialiseACI();
int  ReadACI();
void PrintACI();


int fnCheckDialNumSyntax(char FieldName[100],char FieldType[3]);
int fnCheckSyntax(char FieldName[100],char FieldType[3]);
int fnDateRangeCheck(char FieldName[15]);
int fnUtcValueCheck(char FieldName[15]) ;
void fnItemLevel (char *String1);
int fnCheckCurrency(char FieldName[4]);
int fnImsiPrfxCheck(double FieldName);

/* Declare DataInterChange Structure Instance */
 extern DataInterChange DIC;
/* extern char *origData; */
 
int CheckFileType(char* p_szFileNamePtr)
{
    int         fd,val;
    char        *buf;
    long        decodedLen,totalElmtsLen;
    AsnTag      tagId;
    long        elmtLen=0,bytesDecoded;
    long        size;
    char        *origData; 
    struct stat sbuf;
    jmp_buf     env;

    /* Open the TAP File */
    fd = open (p_szFileNamePtr, O_RDONLY, 0);

    if(fd < 0)
    {
        perror ("main: fopen");
        return FILE_OPEN_ERROR;
    }

    /* Get the File Statistics */
    if(fstat (fd, &sbuf) < 0)
    {
        perror ("main: fstat");
                return FILE_OPEN_ERROR;
    }

    size = sbuf.st_size;
    origData = (char*)malloc (size);
    if (read (fd, origData, size) != size)
    {
        perror ("main: read");
                if (origData != NULL)
                free (origData);
        return FILE_READ_ERROR;
    }

    close (fd);

    /* set up min buf  */
    buf = origData;
        InitNibbleMem (512, 512);
    tagId = BDecTag (&buf, &totalElmtsLen, env);
    elmtLen = BDecLen (&buf, &totalElmtsLen, env);

/*printf("val= %d,env=%d\n",val,env);  */

    if ((val = setjmp (env)) == 0)
    {
        BDecDataInterChangeContent(&buf, tagId, elmtLen,&DIC,&bytesDecoded, env);
    }
    else
    {
    			 if (origData != NULL )	
				 {
				    free (origData);
                   ShutdownNibbleMem ();
				    return FILE_DECODE_ERROR; 
					}

    }
    

    /* Free the Memory */
    if (origData != NULL)
    free (origData);

    return 0;
}

int ReadBCI()
{
   char FileSequenceNumber[6];
   int  ReturnValue = 0 ;
   int  ErrorReturnValue = 0 ;
   int  FieldLength = 0      ;
   long SeqNuminFileName = 0 ;
   char TempNumtoChar [10]   ;
   int  ErrorCount = 0       ;
   int  lValidateFlag = 0    ;

   gRejectedErrorNo = 0;
   gErrorNode = 4 ;

   if(NOT_NULL(DIC.a.transferBatch->batchControlInfo))
   {
      /* Sender : AsciiString */
      if(ASNOCTS_PRESENT(&DIC.a.transferBatch->batchControlInfo->sender))
      {
         strcpy(BCI.Sender,DIC.a.transferBatch->batchControlInfo->sender.octs);
         fnRemTrailSpaces(BCI.Sender)     ;
         
         /* Sender : Syntax Error Check */
         ReturnValue = 0;
         ReturnValue = fnCheckSyntax(BCI.Sender,"BT") ;
         if(ReturnValue != 0)
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 196             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
             lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Sender") ;
                 /* strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;196:0:L;169:0:L") ; */
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;196:0:L") ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.Sender);
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0 ;
         }


         /* Sender : Value Out Of Range Error Check */
         FieldLength = 0 ;
         FieldLength = strlen(BCI.Sender) ;

         if(FieldLength != 5)
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 196             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
             lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Sender") ;
                 /* strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;196:0:L;169:0:L") ; */
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;196:0:L") ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.Sender);
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0 ;
         }

         /* Sender : Compare the BCI Sender with Sender on the FileName */
         if(strcmp(BCI.Sender,gFileVplmnCode) != 0)
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 100                 ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 196             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
             lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Sender") ;
                 /* strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;196:0:L;169:0:L") ; */
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;196:0:L") ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"The item does not match the Sender on the filename");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.Sender);
                 gRejectedErrorNo++ ;
             } 
             ReturnValue = 0 ;
         }

         if(strcmp(BCI.Sender,gFileVplmnCode) != 0)
         {
             gValidateVPLMNPrefix = 0 ;
             gValidateVPLMNPrefix = fnCheckPLMNPrefix(BCI.Sender) ;
             if(gValidateVPLMNPrefix != 0)
             {
                strcpy(BCI.Sender,gFileVplmnCode);
             }
         }
      }
      else
      {
          strcpy(BCI.Sender,gFileVplmnCode);

          REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 4                          ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
          lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"BatchControlInfo")      ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L")       ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Sender missing within group");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }

      /* Recipient : AsciiString */
      if(ASNOCTS_PRESENT(&DIC.a.transferBatch->batchControlInfo->recipient))
      {
          strcpy(BCI.Recipient,DIC.a.transferBatch->batchControlInfo->recipient.octs);

          fnRemTrailSpaces(BCI.Recipient) ;


          /* Recipient : Syntax Error Check */
          ReturnValue = fnCheckSyntax(BCI.Recipient,"BT") ;
          if(ReturnValue != 0)
          {
              REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 182             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Recipient") ;
                  /* strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;182:0:L;169:0:L") ; */
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;182:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.Recipient);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
          }


          /* Recipient : Value Out Of Range Error Check */
          FieldLength = 0 ;
          FieldLength = strlen(BCI.Recipient) ;

          if(FieldLength != 5)
          {
              REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 182             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Recipient") ;
                  /* strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;182:0:L;169:0:L") ; */
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;182:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.Recipient);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
          }


          /* Recipient : Compare the BCI Recipient with Recipient on the FileName */
          if(strcmp(BCI.Recipient,gFileHplmnCode) != 0)
          {
              REI.ERROR_CODE[gRejectedErrorNo]  = 100                 ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 182             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Recipient") ;
                  /* strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;182:0:L;169:0:L") ; */
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;182:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"The item does not match the Recipient on the filename");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.Recipient);
                  gRejectedErrorNo++ ;
              }

              ReturnValue = 0 ;
          }

         if(strcmp(BCI.Recipient,gFileHplmnCode) != 0)
         {
             gValidateHPLMNPrefix = 0 ;
             gValidateHPLMNPrefix = fnCheckPLMNPrefix(BCI.Recipient) ;
             if(gValidateHPLMNPrefix != 0)
             {
                strcpy(BCI.Recipient,gFileHplmnCode);
             }
         }


      }
      else
      {
          strcpy(BCI.Recipient,gFileHplmnCode);

          REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 4                          ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
          lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"BatchControlInfo")  ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L")       ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Recipient missing within group");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }


      /* FileTypeIndicator : AsciiString */
      if(ASNOCTS_PRESENT(&DIC.a.transferBatch->batchControlInfo->fileTypeIndicator))
      {
          strcpy(BCI.FileTypeIndicator,DIC.a.transferBatch->batchControlInfo->fileTypeIndicator.octs);
          fnRemTrailSpaces(BCI.FileTypeIndicator) ;


          /* FileTypeIndicator : Syntax Error Check */
          ReturnValue = fnCheckSyntax(BCI.FileTypeIndicator,"AL") ;
          if(ReturnValue != 0)
          {
              REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 110             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FileTypeIndicator") ;
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;110:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.FileTypeIndicator);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
          }


          /* Recipient : Value Out Of Range Error Check */
          FieldLength = 0 ;
          FieldLength = strlen(BCI.FileTypeIndicator) ;

          if(FieldLength != 1)
          {
              REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 110             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FileTypeIndicator") ;
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;110:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.FileTypeIndicator);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
          }

      }
      else
      {
          strcpy(BCI.FileTypeIndicator,"C");
      }


      /* FileSequenceNumber : NumberString */
      if(ASNOCTS_PRESENT(&DIC.a.transferBatch->batchControlInfo->fileSequenceNumber))
      {
          FileSequenceNumber[0]='\0';
          strcpy(FileSequenceNumber,DIC.a.transferBatch->batchControlInfo->fileSequenceNumber.octs);
          fnRemTrailSpaces(FileSequenceNumber) ;
    
          /* FileSequenceNumber : Syntax Error Check */
          ReturnValue = fnCheckSyntax(FileSequenceNumber,"DI") ;
          if(ReturnValue != 0)
          {
              REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 109             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FileSequenceNumber") ;
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;109:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],FileSequenceNumber);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
          }


          BCI.FileSequenceNumber = atol(FileSequenceNumber);

          if ((BCI.FileSequenceNumber <= 0) || (BCI.FileSequenceNumber > 99999))
          {
              REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 109             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FileSequenceNumber") ;
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;109:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],FileSequenceNumber);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
          }

          SeqNuminFileName = atol(gFileSequenceNumber) ;

          if(BCI.FileSequenceNumber != SeqNuminFileName)
          {
              REI.ERROR_CODE[gRejectedErrorNo]  = 100                 ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 109             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FileSequenceNumber") ;
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;109:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"The item does not match the File Sequence Number on the filename");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],FileSequenceNumber);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
          }

      }
      else
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 4                          ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
          lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"BatchControlInfo")      ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L")       ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item File Sequence Number missing within group");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }


      /* FileCreationTimeStamp : DateTimeLong */
      if(NOT_NULL(DIC.a.transferBatch->batchControlInfo->fileCreationTimeStamp))
      {
	  BCIA.FileCreationTimeStamp = 1;
 
          if(ASNOCTS_PRESENT(&DIC.a.transferBatch->batchControlInfo->fileCreationTimeStamp->localTimeStamp))
          {
              strcpy(BCI.FileCreationTimeStamp.LocalTimeStamp,
                    DIC.a.transferBatch->batchControlInfo->fileCreationTimeStamp->localTimeStamp.octs);
          }
            
          if(ASNOCTS_PRESENT(&DIC.a.transferBatch->batchControlInfo->fileCreationTimeStamp->utcTimeOffset))
          {
             strcpy(BCI.FileCreationTimeStamp.UtcTimeOffset,
                   DIC.a.transferBatch->batchControlInfo->fileCreationTimeStamp->utcTimeOffset.octs);   
          }
      }

      /* TransferCutOffTimeStamp : DateTimeLong */
      if(NOT_NULL(DIC.a.transferBatch->batchControlInfo->transferCutOffTimeStamp))
      {
          if(ASNOCTS_PRESENT(&DIC.a.transferBatch->batchControlInfo->transferCutOffTimeStamp->localTimeStamp))
          {
              strcpy(BCI.TransferCutOffTimeStamp.LocalTimeStamp,
                     DIC.a.transferBatch->batchControlInfo->transferCutOffTimeStamp->localTimeStamp.octs);

              ReturnValue = fnCheckSyntax(BCI.TransferCutOffTimeStamp.LocalTimeStamp,"DI") ;
              if(ReturnValue != 0)
              {
                 REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                 REI.APPLICATION_TAG[gRejectedErrorNo] = 227             ;
                 strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                 lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
                 if(lValidateFlag == 0)
                 {
                     strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                     strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TransferCutOffTimeStamp") ;
                     strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;227:0:L;16:0:L") ;
                     fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                     strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                     strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.TransferCutOffTimeStamp.LocalTimeStamp);
                     gRejectedErrorNo++ ;
                 }
                 ReturnValue = 0 ;
             }

             ReturnValue = fnDateRangeCheck(BCI.TransferCutOffTimeStamp.LocalTimeStamp);
             if(ReturnValue != 0)
             {
                 REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                 REI.APPLICATION_TAG[gRejectedErrorNo] = 227             ;
                 strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                 lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
                 if(lValidateFlag == 0)
                 {
                     strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                     strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TransferCutOffTimeStamp") ;
                     strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;227:0:L;16:0:L") ;
                     fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                     strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                     strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.TransferCutOffTimeStamp.LocalTimeStamp);
                     gRejectedErrorNo++ ;
                 }
                 ReturnValue = 0 ;
             }

         }
            
         if(ASNOCTS_PRESENT(&DIC.a.transferBatch->batchControlInfo->transferCutOffTimeStamp->utcTimeOffset))
         {
             strcpy(BCI.TransferCutOffTimeStamp.UtcTimeOffset,
                    DIC.a.transferBatch->batchControlInfo->transferCutOffTimeStamp->utcTimeOffset.octs);   
         }
         else
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 30                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 227             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TransferCutOffTimeStamp") ;
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;227:0:L") ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory associated item UTC Time Offset missing");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0 ;
         }
      }

      /* FileAvailableTimeStamp : DateTimeLong */
      if(NOT_NULL(DIC.a.transferBatch->batchControlInfo->fileAvailableTimeStamp))
      {
          if(ASNOCTS_PRESENT(&DIC.a.transferBatch->batchControlInfo->fileAvailableTimeStamp->localTimeStamp))
          {
              strcpy(BCI.FileAvailableTimeStamp.LocalTimeStamp,
                   DIC.a.transferBatch->batchControlInfo->fileAvailableTimeStamp->localTimeStamp.octs);

              /* FileAvailableTimeStamp : Syntax Error Check */
              ReturnValue = fnCheckSyntax(BCI.FileAvailableTimeStamp.LocalTimeStamp,"DI") ;
              if(ReturnValue != 0)
              {
                  REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                  REI.APPLICATION_TAG[gRejectedErrorNo] = 107             ;
                  strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                  lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                  if(lValidateFlag == 0)
                  {
                      strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                      strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FileAvailableTimeStamp") ;
                      strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;107:0:L;16:0:L") ;
                      fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                      strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                      strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.FileAvailableTimeStamp.LocalTimeStamp);
                      gRejectedErrorNo++ ;
                  }
                  ReturnValue = 0 ;
              }

              ReturnValue = fnDateRangeCheck(BCI.FileAvailableTimeStamp.LocalTimeStamp);
              if(ReturnValue != 0)
              {
                  REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                  REI.APPLICATION_TAG[gRejectedErrorNo] = 107             ;
                  strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                  lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                  if(lValidateFlag == 0)
                  {
                      strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                      strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FileAvailableTimeStamp") ;
                      strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;107:0:L;16:0:L") ;
                      fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                      strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                      strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.FileAvailableTimeStamp.LocalTimeStamp);
                      gRejectedErrorNo++ ;
                  }
                  ReturnValue = 0 ;
              }

              if(strcmp(BCI.FileAvailableTimeStamp.LocalTimeStamp,BCI.TransferCutOffTimeStamp.LocalTimeStamp) < 0)
              {
                  REI.ERROR_CODE[gRejectedErrorNo]  = 100                 ;
                  REI.APPLICATION_TAG[gRejectedErrorNo] = 107             ;
                  strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                  lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                  if(lValidateFlag == 0)
                  {
                      strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                      strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FileAvailableTimeStamp") ;
                      strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;107:0:L;16:0:L") ;
                      fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                      strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Timestamp is earlier than the Transfer Cut Off Timestamp");
                      strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.FileAvailableTimeStamp.LocalTimeStamp);
                      gRejectedErrorNo++ ;
                  }
                  ReturnValue = 0 ;
              }

              if(strcmp(BCI.FileAvailableTimeStamp.LocalTimeStamp,gSystemDate) > 0)
              {
                  REI.ERROR_CODE[gRejectedErrorNo]  = 104                 ;
                  REI.APPLICATION_TAG[gRejectedErrorNo] = 107             ;
                  strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                  lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                  if(lValidateFlag == 0)
                  {
                     strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                     strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FileAvailableTimeStamp") ;
                     strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;107:0:L;16:0:L") ;
                     fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                     strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Timestamp is after the file received time at the HPMN");
                     strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.FileAvailableTimeStamp.LocalTimeStamp);
                     gRejectedErrorNo++ ;
                  }
                  ReturnValue = 0 ;
              }

          }            
          if(ASNOCTS_PRESENT(&DIC.a.transferBatch->batchControlInfo->fileAvailableTimeStamp->utcTimeOffset))
          {
              strcpy(BCI.FileAvailableTimeStamp.UtcTimeOffset,
                     DIC.a.transferBatch->batchControlInfo->fileAvailableTimeStamp->utcTimeOffset.octs);   


              ReturnValue = fnCheckUtcSyntax(BCI.FileAvailableTimeStamp.UtcTimeOffset) ;
              if(ReturnValue != 0)
              {
                  REI.ERROR_CODE[gRejectedErrorNo]  = 14                  ;
                  REI.APPLICATION_TAG[gRejectedErrorNo] = 231             ;
                  strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                  lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                  if(lValidateFlag == 0)
                  {
                      strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                      strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"UtcTimeOffset") ;
                      strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;107:0:L;231:0:L") ;
                      fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                      strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error and associated item is File Available Timestamp");
                      strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.FileAvailableTimeStamp.UtcTimeOffset);
                      gRejectedErrorNo++ ;
                  }
                  ReturnValue = 0 ;
              }

              ReturnValue = fnUtcValueCheck(BCI.FileAvailableTimeStamp.UtcTimeOffset) ;
              if(ReturnValue != 0)
              {
                  REI.ERROR_CODE[gRejectedErrorNo]  = 24                  ;
                  REI.APPLICATION_TAG[gRejectedErrorNo] = 231             ;
                  strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                  lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                  if(lValidateFlag == 0)
                  {
                      strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                      strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"UtcTimeOffset") ;
                      strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;107:0:L;231:0:L") ;
                      fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                      strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range and associated item is File Available Timestamp");
                      strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.FileAvailableTimeStamp.UtcTimeOffset);
                      gRejectedErrorNo++ ;
                  }
                  ReturnValue = 0 ;
              }
          }
          else
          {
              REI.ERROR_CODE[gRejectedErrorNo]  = 30                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 107             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FileAvailableTimeStamp") ;
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;107:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory associated item UTC Time Offset missing");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
          }

      }
      else
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 33                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 4             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"BatchControlInfo") ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L") ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item File Available Timestamp missing within group");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
      }


      /* SpecificationVersionNumber : AsnInt */
      if(NOT_NULL(DIC.a.transferBatch->batchControlInfo->specificationVersionNumber))
      {
          BCI.SpecificationVersionNumber = *DIC.a.transferBatch->batchControlInfo->specificationVersionNumber;   

          sprintf (TempNumtoChar,"%d",BCI.SpecificationVersionNumber);

          ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
          if(ReturnValue != 0)
          {
              REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 201             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SpecificationVersionNumber") ;
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;201:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
          }

          /*Added by Anitha for 3.12
            Before if(BCI.SpecificationVersionNumber !=3)*/

          if(BCI.SpecificationVersionNumber != gTapSpecificationVersion)
          {
              REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 201             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SpecificationVersionNumber") ;
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;201:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
          }

      }
      else
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 34                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 4                          ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"BatchControlInfo")      ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L")       ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Specification Version Number missing within group");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }


      /* ReleaseVersionNumber : AsnInt */
      if(NOT_NULL(DIC.a.transferBatch->batchControlInfo->releaseVersionNumber))
      {
          BCI.ReleaseVersionNumber = *DIC.a.transferBatch->batchControlInfo->releaseVersionNumber;


          sprintf (TempNumtoChar,"%d",BCI.ReleaseVersionNumber);

          ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
          if(ReturnValue != 0)
          {
              REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 189             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ReleaseVersionNumber") ;
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;189:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
          }

         /*Added by Anitha for 3.12
           Before if(BCI.ReleaseVersionNumber != 11)*/
          if(BCI.ReleaseVersionNumber != gTapReleaseVersion)
          {
              REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 189             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ReleaseVersionNumber") ;
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L;189:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
          }

      }
      else
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 41                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 4                          ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"BatchControlInfo")      ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L")       ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Release Version Number missing within group");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }



      /* RapFileSequenceNumber : NumberString */
      if(ASNOCTS_PRESENT(&DIC.a.transferBatch->batchControlInfo->rapFileSequenceNumber))
      {
          BCI.RapFileSequenceNumber = atol(DIC.a.transferBatch->batchControlInfo->rapFileSequenceNumber.octs);
      }

   }
   else
   {
       REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
       REI.APPLICATION_TAG[gRejectedErrorNo] = 1                          ;
       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
       if(lValidateFlag == 0)
       {
           gErrorNode = REI.APPLICATION_TAG[gRejectedErrorNo] ;
           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"TransferBatch");
           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TransferBatch")     ;
           strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L")       ;
           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Batch Control Information missing within group");
           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
           gRejectedErrorNo++ ;
       }
   }


   if(NOT_NULL(DIC.a.transferBatch->auditControlInfo->callEventDetailsCount))
   {
         gCdrsArrayCount  = *DIC.a.transferBatch->auditControlInfo->callEventDetailsCount;
   }


   /* Get Recepient Name and File Sequence Number from File Name in case of Sender FATAL Error */
   ReturnValue = 0;
   ReturnValue = GetRAPPartnerInfo();

   if(ReturnValue != 0)
   {
       return -1;
   }


   if((gRejectedErrorNo > 0) && (strcmp(gGenerateFilesFlg,"N")!=0))
   {
       for(ErrorCount=0; ErrorCount<gRejectedErrorNo; ErrorCount++)
	          {
           ErrorReturnValue = SetBulkErrorDetails(gBulkErrorDetailsIndex, ErrorCount,gErrorNode)   ;
           if(ErrorReturnValue == -1)
           {
               return -1;
           }
       }
   }
 
   gRejectedErrorNo = 0;

   return 0 ;
}


int ReadACC()
{
   void *Pointer;
   int i=0;
   char TaxRate[10];
   char TempTaxRate[10]; 
   int  ReturnValue = 0 ;
   int  ErrorReturnValue = 0 ;
   char TempNumtoChar [10]   ;
   int  Var_length = 0 ;
   int  LdiscountApplied= 0;
   int  ErrorCount = 0       ;
   int  lValidateFlag = 0    ;
   
   gErrorNode = 5 ;

   Taxation           *pTaxation;
   Discounting        *pDiscounting;
   CurrencyConversion *pCurrencyConversion;

   gRejectedErrorNo        = 0 ;
   gCurrencyConversionFlag = 0 ;
   gTaxationFlag           = 0 ;
   gDiscountFlag           = 0 ;

   if(NOT_NULL(DIC.a.transferBatch->accountingInfo))
   {
       /**** Check for TaxationList ****/
       if(NOT_NULL(DIC.a.transferBatch->accountingInfo->taxation))
       {
           i = 0;
 
           FOR_EACH_LIST_ELMT(pTaxation,DIC.a.transferBatch->accountingInfo->taxation)
           {
               Var_length = 0 ;
               if(NOT_NULL(pTaxation->taxCode))			
               {
                   ACC.Taxation[i].TaxCode = *pTaxation->taxCode;   

            
                   /* TaxCode : Syntax Error Check */
                   sprintf (TempNumtoChar,"%d",ACC.Taxation[i].TaxCode);
                   ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
                   if(ReturnValue != 0)
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 212             ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxCode");
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;211:%d:L;216:0:L;212:0:L",i+1);
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                           gRejectedErrorNo++ ;
                       }
                       ReturnValue = 0 ;
                   }

                   /* TaxCode : Value out of range Error Check */
                   if ((ACC.Taxation[i].TaxCode < 0) || (ACC.Taxation[i].TaxCode > 999))
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 212             ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxCode") ;
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;211:%d:L;216:0:L;212:0:L",i+1);
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                           gRejectedErrorNo++ ;
                       }
                       ReturnValue = 0 ;
                   }

               }
               else
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 216                        ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"AccountingInfo")    ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;211:%d:L;216:0:L",i+1);
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Tax Rate Code missing within group");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                       gRejectedErrorNo++ ;
                   }
               }

               if(ASNOCTS_PRESENT(&pTaxation->taxType))	
               {
                   strcpy(ACC.Taxation[i].TaxType,pTaxation->taxType.octs);  

                   /* TaxType : Syntax Error Check */
                   ReturnValue = fnCheckSyntax(ACC.Taxation[i].TaxType,"AS") ;
                   if(ReturnValue != 0)
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 217             ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxType");
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;211:%d:L;216:0:L;217:0:L",i+1);
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],ACC.Taxation[i].TaxType);
                           gRejectedErrorNo++ ;
                       }
                       ReturnValue = 0 ;
                   }

                   /* TaxType : Value out of range Error Check : possible range of values as defined by TAP standard */
                   Pointer = NULL;
                   Pointer = strstr("01:02:03:04",ACC.Taxation[i].TaxType);
                   if(Pointer == NULL)
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 217             ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxType") ;
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;211:%d:L;216:0:L;217:0:L",i+1);
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],ACC.Taxation[i].TaxType);
                           gRejectedErrorNo++ ;
                       }
                       ReturnValue = 0 ;
                   }
               }
               else
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 216                        ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                      strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                      strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"AccountingInfo")    ;
                      sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;211:%d:L;216:0:L",i+1);
                      fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                      strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Tax Type missing within group");
                      strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                      gRejectedErrorNo++ ;
                   }
               }


               if(ASNOCTS_PRESENT(&pTaxation->taxRate))
               {
                   strcpy(TaxRate,pTaxation->taxRate.octs);
                   /* strncpy(TempTaxRate,TaxRate,2);
                   TempTaxRate[2]='\0'; */
 
                   strcpy(TempTaxRate,TaxRate);
                   fnRemTrailSpaces(TempTaxRate);
                   ACC.Taxation[i].TaxRate = atoi(TempTaxRate);
 
                   /* TaxRate : Syntax Error Check */
                   ReturnValue = fnCheckSyntax(TaxRate,"DI") ;
                   if(ReturnValue != 0)
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 215             ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxRate");
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;211:%d:L;216:0:L;215:0:L",i+1);
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TaxRate);
                           gRejectedErrorNo++ ;
                       }
                       ReturnValue = 0 ;
                   }

                   /* TaxRate : Value Out of Range */
 
                   if ((ACC.Taxation[i].TaxRate < 0) || (ACC.Taxation[i].TaxRate> 9999999))
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 215             ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxRate");
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;211:%d:L;216:0:L;215:0:L",i+1);
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TaxRate);
                           gRejectedErrorNo++ ;
                       }
                       ReturnValue = 0 ;
                   }

               }


               if(ASNOCTS_PRESENT(&pTaxation->chargeType))			
               {
                   strcpy(ACC.Taxation[i].ChargeType,pTaxation->chargeType.octs);

                   /* ChargeType : Syntax Error Check */
                   ReturnValue = fnCheckSyntax(ACC.Taxation[i].ChargeType,"DI") ;
                   if(ReturnValue != 0)
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 71              ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxRate");
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;211:%d:L;216:0:L;71:0:L",i+1);
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],ACC.Taxation[i].ChargeType);
                           gRejectedErrorNo++ ;
                       }
                       ReturnValue = 0 ;
                   }

                   /* ChargeType :Value Out Of Range */
  
                   Pointer = NULL;
                   Pointer = strstr("00:01:02:03:04:21:50",ACC.Taxation[i].ChargeType);
                   if(Pointer == NULL)
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 21                  ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 71              ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeType");
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;211:%d:L;216:0:L;71:0:L",i+1);
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],ACC.Taxation[i].ChargeType);
                           gRejectedErrorNo++ ;
                       }
                       ReturnValue = 0 ;
                   }

               }

               i++;
           }
           ACC.TotalTax   = i;
           gTaxationCount = i;
       }
       else
       {
          gTaxationFlag = 1;
       }


       /**** Check for Discounting ****/
       if(NOT_NULL(DIC.a.transferBatch->accountingInfo->discounting))
       {
           i = 0;
 
           FOR_EACH_LIST_ELMT(pDiscounting,DIC.a.transferBatch->accountingInfo->discounting)
           {
               LdiscountApplied = 0;
               if(NOT_NULL(pDiscounting->discountCode))
               {
                   ACC.Discounting[i].DiscountCode = *pDiscounting->discountCode;
 

                   /* DiscountCode : Syntax Error Check */
                   sprintf (TempNumtoChar,"%d",ACC.Discounting[i].DiscountCode);
                   ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
                   if(ReturnValue != 0)
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 91              ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DiscountCode");
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;95:%d:L;94:0:L;91:0:L",i+1) ;
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                           gRejectedErrorNo++ ;
                       }
                       ReturnValue = 0 ;
                   }

                   /* DiscountCode : Value out of range Error Check */
                   if ((ACC.Discounting[i].DiscountCode < 0) || (ACC.Discounting[i].DiscountCode > 99))
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 20                        ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 91                    ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")              ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DiscountCode") ;
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;95:%d:L;94:0:L;91:0:L",i+1) ;
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                           gRejectedErrorNo++ ;
                       }

                       ReturnValue = 0 ;
                   }
               }
               else
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 95                         ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Discounting")       ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;95:%d:L;94:0:L",i+1) ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Discount Code missing within group");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                       gRejectedErrorNo++ ;
                   }
               }


               if(pDiscounting->discountApplied->choiceId == DISCOUNTAPPLIED_FIXEDDISCOUNTVALUE)
               {
                   ACC.Discounting[i].FixedDiscountValue = pDiscounting->discountApplied->a.fixedDiscountValue;
                   strcpy(ACC.Discounting[i].DiscountType,"F");
                   LdiscountApplied = 1;
  
                   /* FixedDiscountValue : Syntax Error Check */
                   sprintf (TempNumtoChar,"%d",ACC.Discounting[i].FixedDiscountValue);
                   ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
                   if(ReturnValue != 0)
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 411             ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FixedDiscountValue");
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;95:%d:L;94:0:L;428:0:L;411:0:L",i+1) ;
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                           gRejectedErrorNo++ ;
                       }
                       ReturnValue = 0 ;
                   }

                   /* FixedDiscountValue : Value Out of Range */
  
                   if (ACC.Discounting[i].FixedDiscountValue < 0 )
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 411             ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FixedDiscountValue");
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;95:%d:L;94:0:L;428:0:L;411:0:L",i+1) ;
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                           gRejectedErrorNo++ ;
                       }
                       ReturnValue = 0 ;
                   }
               }
               else if(pDiscounting->discountApplied->choiceId == DISCOUNTAPPLIED_DISCOUNTRATE)
               {
                   ACC.Discounting[i].DiscountRate = pDiscounting->discountApplied->a.discountRate;
                   strcpy(ACC.Discounting[i].DiscountType,"D");
                   LdiscountApplied = 1;
  
                   /* DiscountRate : Syntax Error Check */
                   sprintf (TempNumtoChar,"%d",ACC.Discounting[i].DiscountRate);
                   ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
                   if(ReturnValue != 0)
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 92              ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DiscountRate");
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;95:%d:L;94:0:L;428:0:L;92:0:L",i+1) ;
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                           gRejectedErrorNo++ ;
                       }
                       ReturnValue = 0 ;
                   } 

                   /* TaxRate : Value Out of Range */
  
                   if ((ACC.Discounting[i].DiscountRate < 0) || (ACC.Discounting[i].DiscountRate> 10000))
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 92              ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DiscountRate");
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;95:%d:L;94:0:L;428:0:L;92:0:L",i+1) ;
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                           gRejectedErrorNo++ ;
                       }
                       ReturnValue = 0 ;
                   } 
               } 
           
               if(LdiscountApplied == 0)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 95                         ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Discounting")       ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;95:%d:L;94:0:L",i+1) ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Discount Applied missing within group");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                       gRejectedErrorNo++ ;
                   }
               }

               i++;
           }
           ACC.TotalDiscount = i;
           gDiscountingCount = i;
       }
       else
       {
          gDiscountFlag = 1;
       }


       /**** Check for LocalCurrency ****/
       if(ASNOCTS_PRESENT(&DIC.a.transferBatch->accountingInfo->localCurrency))
       {
           strcpy(ACC.LocalCurrency,DIC.a.transferBatch->accountingInfo->localCurrency.octs);
           fnRemTrailSpaces(ACC.LocalCurrency)     ;

           /* LocalCurrency :Syntax Error */

           ReturnValue = fnCheckSyntax(ACC.LocalCurrency,"AL") ;
           if(ReturnValue != 0)
           {
               REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 135             ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"LocalCurrency");
                   strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;135:0:L") ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],ACC.LocalCurrency);
                   gRejectedErrorNo++ ;
               }
               ReturnValue = 0 ;
           }


           /* LocalCurrency :Value Out Of Range */

           ReturnValue = fnCheckCurrency(ACC.LocalCurrency ) ;

           if(ReturnValue != 0)
           {
               REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 135              ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"LocalCurrency");
                   strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;135:0:L") ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range(not listed in ISO 4217 Currency Codes)");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],ACC.LocalCurrency);
                   gRejectedErrorNo++ ;
               }
               ReturnValue = 0 ;
           }
              /* Added by Anitha for WBS 4.3 */
     
		 if(strcmp(ACC.LocalCurrency,gLocalCurrencyCode) != 0)
		 {
           REI.ERROR_CODE[gRejectedErrorNo]  = 21                  ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 135              ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"LocalCurrency");
                   strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;135:0:L") ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value not as specified in the Sender’s Inter Operator Tariff (IOT).");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],ACC.LocalCurrency);
                   gRejectedErrorNo++ ;
               }
               ReturnValue = 0 ;
           }
 
       }
       else
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 5                          ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"AccountingInfo")    ;
               strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L")  ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Local Currency missing within group");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
               gRejectedErrorNo++ ;
           }
       }

       /**** Check for TapCurrency ****/
       if(ASNOCTS_PRESENT(&DIC.a.transferBatch->accountingInfo->tapCurrency))
       {
           strcpy(ACC.TapCurrency,DIC.a.transferBatch->accountingInfo->tapCurrency.octs);
           fnRemTrailSpaces(ACC.TapCurrency)     ;
           if(strcmp(ACC.TapCurrency,"XDR") != 0)
           {
               REI.ERROR_CODE[gRejectedErrorNo]  = 33                             ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 5                          ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"AccountingInfo")    ;
                   strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L")  ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Item TAP Currency not present and currency other than SDR specified in roaming agreement");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],ACC.TapCurrency);
                   gRejectedErrorNo++ ;
               }
           }

           /* TapCurrency :Syntax Error */

           ReturnValue = fnCheckSyntax(ACC.TapCurrency,"AL") ;
           if(ReturnValue != 0)
           {
               REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 210             ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TapCurrency");
                   strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;210:0:L") ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],ACC.TapCurrency);
                   gRejectedErrorNo++ ;
               }
               ReturnValue = 0 ;
           } 


           /* TapCurrency :Value Out Of Range */
           ReturnValue = fnCheckCurrency(ACC.TapCurrency ) ;
 
           if(ReturnValue != 0)
           {
               REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 210             ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TapCurrency");
                   strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;210:0:L") ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range(not listed in ISO 4217 Currency Codes)");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],ACC.TapCurrency);
                   gRejectedErrorNo++ ;
               }
               ReturnValue = 0 ;
           }
 
       }
       else
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 33                             ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 5                          ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"AccountingInfo")    ;
               strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L")  ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Item TAP Currency not present and currency other than SDR specified in roaming agreement");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
               gRejectedErrorNo++ ;
           }
       }


       /**** Check for CurrencyInfo ****/
       if(NOT_NULL(DIC.a.transferBatch->accountingInfo->currencyConversionInfo))
       {
           i = 0;
 
           FOR_EACH_LIST_ELMT(pCurrencyConversion,DIC.a.transferBatch->accountingInfo->currencyConversionInfo)
           {
               if(NOT_NULL(pCurrencyConversion->exchangeRateCode))
               {
                   ACC.CurrencyConversionInfo[i].ExchangeRateCode = *pCurrencyConversion->exchangeRateCode;
 

                   /* ExchangeRateCode : Syntax Error Check */
                   sprintf (TempNumtoChar,"%d",ACC.CurrencyConversionInfo[i].ExchangeRateCode);
                   ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
                   if(ReturnValue != 0)
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 105             ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ExchangeRateCode") ;
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;80:%d:L;106:0:L;105:0:L",i+1) ;
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                           gRejectedErrorNo++ ;
                      }
 
                       ReturnValue = 0 ;
                   }
 
                   /* ExchangeRateCode : Value Out of Range */

                   if ((ACC.CurrencyConversionInfo[i].ExchangeRateCode < 0) || (ACC.CurrencyConversionInfo[i].ExchangeRateCode > 99))
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 105             ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ExchangeRateCode") ;
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;80:%d:L;106:0:L;105:0:L",i+1) ;
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                           gRejectedErrorNo++ ;
                       }

                       ReturnValue = 0 ;
                   }

               }
               else
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 106                        ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CurrencyConversion");
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;80:%d:L;106:0:L",i+1) ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Exchange Rate Code missing within group");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                       gRejectedErrorNo++ ;
                   } 
               }

               if(NOT_NULL(pCurrencyConversion->numberOfDecimalPlaces))
               {
                   ACC.CurrencyConversionInfo[i].NumberOfDecimalPlaces = *pCurrencyConversion->numberOfDecimalPlaces;
 

                   /* NumberOfDecimalPlaces : Syntax Error Check */
                   sprintf (TempNumtoChar,"%d",ACC.CurrencyConversionInfo[i].NumberOfDecimalPlaces);
                   ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
                   if(ReturnValue != 0)
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 159             ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"NumberOfDecimalPlaces") ;
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;80:%d:L;106:0:L;159:0:L",i+1) ;
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                           gRejectedErrorNo++ ;
                       }

                       ReturnValue = 0 ;
                   }

                   /* NumberOfDecimalPlaces : Value Out of Range */
  
                   if (ACC.CurrencyConversionInfo[i].NumberOfDecimalPlaces < 0)
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 159             ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"NumberOfDecimalPlaces") ;
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;80:%d:L;106:0:L;159:0:L",i+1) ;
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                           gRejectedErrorNo++ ;
                       }
                       ReturnValue = 0 ;
                   }
               }
               else
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 106                        ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CurrencyConversion");
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;80:%d:L;106:0:L",i+1) ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Number Of Decimal Places missing within group");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                       gRejectedErrorNo++ ;
                   }
               }

               if(NOT_NULL(pCurrencyConversion->exchangeRate))
               {
                   ACC.CurrencyConversionInfo[i].ExchangeRate = *pCurrencyConversion->exchangeRate;
 

                   /* ExchangeRate : Syntax Error Check */
                   sprintf (TempNumtoChar,"%d",ACC.CurrencyConversionInfo[i].ExchangeRate);
                   ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
                   if(ReturnValue != 0)
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 104             ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ExchangeRate") ;
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;80:%d:L;106:0:L;104:0:L",i+1) ;
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                           gRejectedErrorNo++ ;
                       }
                       ReturnValue = 0 ;
                   }
               }
               else
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 106                        ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CurrencyConversion");
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;80:%d:L;106:0:L",i+1) ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Exchange Rate missing within group");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                       gRejectedErrorNo++ ;
                   }
               }

               i++;
           }


           ACC.TotalCurrency  = i;
           gExchangeRateCount = i;
	
       }
       else
       {
           gCurrencyConversionFlag = 1 ;
       }

       /**** Check for TapDecimalPlaces ****/
       if(NOT_NULL(DIC.a.transferBatch->accountingInfo->tapDecimalPlaces))
       {
           ACC.TapDecimalPlaces = *DIC.a.transferBatch->accountingInfo->tapDecimalPlaces;  


           /* TapDecimalPlaces : Syntax Error Check */
           sprintf (TempNumtoChar,"%d",ACC.TapDecimalPlaces);
           ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
           if(ReturnValue != 0)
           {
               REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 244             ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TapDecimalPlaces") ;
                   strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;244:0:L") ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                   gRejectedErrorNo++ ;
               } 
               ReturnValue = 0 ;
           }

           /* TapDecimalPlaces : Value Out of Range */
  
           if ((ACC.TapDecimalPlaces < 0) || (ACC.TapDecimalPlaces > 6))
           {
               REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 244             ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TapDecimalPlaces") ;
                   strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;244:0:L") ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                   gRejectedErrorNo++ ;
               } 
               ReturnValue = 0 ;
           }

       } 
       else
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 35                             ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 5                          ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"AccountingInfo")    ;
               strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L")  ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item TAP Decimal Places missing within group");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
               gRejectedErrorNo++ ;
           }
       } 

   }
   else
   {
       REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
       REI.APPLICATION_TAG[gRejectedErrorNo] = 1                          ;
       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
       if(lValidateFlag == 0)
       {
           gErrorNode = REI.APPLICATION_TAG[gRejectedErrorNo] ;
           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"TransferBatch");
           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TransferBatch")     ;
           strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L")       ;
           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Group Accounting Information not present and a charge is present within the Transfer Batch");
           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
           gRejectedErrorNo++ ;
       }
   }

   if((gRejectedErrorNo > 0) && (strcmp(gGenerateFilesFlg,"N")!=0))
   {
       for(ErrorCount=0; ErrorCount<gRejectedErrorNo; ErrorCount++)
       {
           ErrorReturnValue = SetBulkErrorDetails(gBulkErrorDetailsIndex, ErrorCount,gErrorNode)   ;
           if(ErrorReturnValue == -1)
           {
              return -1;
           }
       }
   }
   gRejectedErrorNo = 0;


   return 0;
}


int  ReadNI()
{
   int i=0;
   int  ReturnValue = 0 ;
   int  ErrorReturnValue = 0 ;
   char TempNumtoChar [10]   ;
   int  ErrorCount = 0       ;
   int  lValidateFlag = 0    ;

   gErrorNode = 6 ;

   UtcTimeOffsetInfo    *pUtcTimeOffsetInfo;
   RecEntityInformation *pRecEntityInformation;

   gRejectedErrorNo = 0;

   if(NOT_NULL(DIC.a.transferBatch->networkInfo))
   {
      if(NOT_NULL(DIC.a.transferBatch->networkInfo->utcTimeOffsetInfo))
      {
         i=0;
 
         FOR_EACH_LIST_ELMT(pUtcTimeOffsetInfo,DIC.a.transferBatch->networkInfo->utcTimeOffsetInfo)
         {
            if(NOT_NULL(pUtcTimeOffsetInfo->utcTimeOffsetCode))
            {
               NI.UtcTimeOffsetInfo[i].UtcTimeOffsetCode   = *pUtcTimeOffsetInfo->utcTimeOffsetCode;
             
               /* UtcTimeOffsetCode : Syntax Error Check */
               sprintf (TempNumtoChar,"%d", NI.UtcTimeOffsetInfo[i].UtcTimeOffsetCode);
               ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
               if(ReturnValue != 0)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 232             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkInformation");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"UtcTimeOffsetCode") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;6:0:L;234:%d:L;233:0:L;232:0:L",i+1) ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }
                   ReturnValue = 0 ;
               }

               /* UtcTimeOffsetCode : Value out of range Error Check */
               if ((NI.UtcTimeOffsetInfo[i].UtcTimeOffsetCode < 0) || (NI.UtcTimeOffsetInfo[i].UtcTimeOffsetCode > 99))
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 232             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkInformation");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"UtcTimeOffsetCode") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;6:0:L;234:%d:L;233:0:L;232:0:L",i+1) ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }
                   ReturnValue = 0 ;
               }
            }
            else
            {
               REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 6                          ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkInformation");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"UtcTimeOffsetInfo")       ;
                   sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;6:0:L;234:%d:L;233:0:L",i+1) ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item UTC Time Offset Code missing within group");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                   gRejectedErrorNo++ ;
               }
            }
 
            if(ASNOCTS_PRESENT(&pUtcTimeOffsetInfo->utcTimeOffset))
            {
               strcpy(NI.UtcTimeOffsetInfo[i].UtcTimeOffset,pUtcTimeOffsetInfo->utcTimeOffset.octs);


               /* UtcTimeOffset : Syntax Error Check */
               ReturnValue = fnCheckUtcSyntax(NI.UtcTimeOffsetInfo[i].UtcTimeOffset) ;
               if(ReturnValue != 0)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 231             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkInformation");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"UtcTimeOffset") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;6:0:L;234:%d:L;233:0:L;231:0:L",i+1) ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],NI.UtcTimeOffsetInfo[i].UtcTimeOffset);
                       gRejectedErrorNo++ ;
                   }

                   ReturnValue = 0 ;
               }

               /* UtcTimeOffset : Value out of range Error Check */

               ReturnValue = fnUtcValueCheck(NI.UtcTimeOffsetInfo[i].UtcTimeOffset) ;
               if(ReturnValue != 0)
               {
                     REI.ERROR_CODE[gRejectedErrorNo]  = 21                  ;
                     REI.APPLICATION_TAG[gRejectedErrorNo] = 231             ;
                     strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                     lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                     if(lValidateFlag == 0)
                     {
                         strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkInformation");
                         strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"UtcTimeOffset") ;
                         sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;6:0:L;234:%d:L;233:0:L;231:0:L",i+1) ;
                         fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                         strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                         strcpy(REI.ERROR_VALUE[gRejectedErrorNo],NI.UtcTimeOffsetInfo[i].UtcTimeOffset);
                         gRejectedErrorNo++ ;
                     }
                     ReturnValue = 0 ;
               }

            }
            else
            {
               REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 6                          ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkInformation");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"UtcTimeOffsetInfo")       ;
                   sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;6:0:L;234:%d:L;233:0:L",i+1) ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item UTC Time Offset missing within group");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                   gRejectedErrorNo++ ;
               }
            } 

            i++;
         }

         NI.TotalUtc     = i;
         gUTCOffsetCount = i;
      }
      else
      {
         REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
         REI.APPLICATION_TAG[gRejectedErrorNo] = 6                          ;
         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
         if(lValidateFlag == 0)
         {
             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkInformation");
             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"NetworkInfo")    ;
             strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;6:0:L")  ;
             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group UTC Time Offset Information missing within group");
             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
             gRejectedErrorNo++ ;
         }
      }

      if(NOT_NULL(DIC.a.transferBatch->networkInfo->recEntityInfo))
      {
         i=0;

         FOR_EACH_LIST_ELMT(pRecEntityInformation,DIC.a.transferBatch->networkInfo->recEntityInfo) 
         {
            if(NOT_NULL(pRecEntityInformation->recEntityCode))
            {
               NI.RecEntityInfo[i].RecEntityCode = *pRecEntityInformation->recEntityCode;


               /* RecEntityCode : Syntax Error Check */
               sprintf (TempNumtoChar,"%d", NI.RecEntityInfo[i].RecEntityCode);
               ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
               if(ReturnValue != 0)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 184             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkInformation");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityCode") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;6:0:L;188:%d:L;183:0:L;184:0:L",i+1) ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }

                   ReturnValue = 0 ;
               }

               /* RecEntityCode : Value out of range Error Check */
               if ((NI.RecEntityInfo[i].RecEntityCode < 0) || (NI.RecEntityInfo[i].RecEntityCode > 10000))
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 232             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkInformation");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityCode") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;6:0:L;188:%d:L;183:0:L;184:0:L",i+1) ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }

                   ReturnValue = 0 ;
               }
            }   
            else
            {
               REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 183                        ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkInformation");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityInfo")      ;
                   sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;6:0:L;188:%d:L;183:0:L",i+1) ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Recording Entity Code missing within group");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                   gRejectedErrorNo++ ;
               }
            }


            if(NOT_NULL(pRecEntityInformation->recEntityType))
            {
               NI.RecEntityInfo[i].RecEntityType = *pRecEntityInformation->recEntityType;

               /* RecEntityType : Syntax Error Check */

               sprintf (TempNumtoChar,"%d", NI.RecEntityInfo[i].RecEntityType);
               ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
               if(ReturnValue != 0)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 186             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkInformation");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityType") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;6:0:L;188:%d:L;183:0:L;186:0:L",i+1) ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }

                   ReturnValue = 0 ;
               }


               /* RecEntityType :Value Out Of Range */

               if ((NI.RecEntityInfo[i].RecEntityType < 0) || (NI.RecEntityInfo[i].RecEntityType > 9))
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 186             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkInformation");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityType") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;6:0:L;188:%d:L;183:0:L;186:0:L",i+1) ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }

                   ReturnValue = 0 ;
               }
            }   
            else
            {
               REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 183                        ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkInformation");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityInfo")      ;
                   sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;6:0:L;188:%d:L;183:0:L",i+1) ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Recording Entity Type missing within group");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                   gRejectedErrorNo++ ;
               }
            }


            if(ASNOCTS_PRESENT(&pRecEntityInformation->recEntityId))
            {
               strcpy(NI.RecEntityInfo[i].RecEntityId,pRecEntityInformation->recEntityId.octs);

               ReturnValue = fnCheckSyntax(NI.RecEntityInfo[i].RecEntityId,"AS") ;
               if(ReturnValue != 0)
               {
                    REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                    REI.APPLICATION_TAG[gRejectedErrorNo] = 400             ;
                    strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                    lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                    if(lValidateFlag == 0)
                    {
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkInformation");
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityId");
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;6:0:L;188:%d:L;183:0:L;400:0:L",i+1) ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],NI.RecEntityInfo[i].RecEntityId);
                        gRejectedErrorNo++ ;
                    }
                    ReturnValue = 0 ;
               }


            }   
            else
            {
               REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 183                        ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkInformation");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityInfo")      ;
                   sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;6:0:L;188:%d:L;183:0:L",i+1) ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Recording Entity Identification missing within group");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                   gRejectedErrorNo++ ;
               }
            }


            i++;
         }

         NI.TotalRecEntity   = i;
         gRecEntityInfoCount = i;
      }
      else
      {
         REI.ERROR_CODE[gRejectedErrorNo]  = 33                             ;
         REI.APPLICATION_TAG[gRejectedErrorNo] = 6                          ;
         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
         if(lValidateFlag == 0)
         {
             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkInformation");
             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"NetworkInfo")       ;
             strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;6:0:L")  ;
             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Group Recording Entity Information missing within group");
             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
             gRejectedErrorNo++ ;
         }

      }

   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 1                          ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          gErrorNode = REI.APPLICATION_TAG[gRejectedErrorNo] ;
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"TransferBatch");
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TransferBatch")     ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L")       ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Network Information missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }

   if((gRejectedErrorNo > 0) && (strcmp(gGenerateFilesFlg,"N")!=0))
   {
       for(ErrorCount=0; ErrorCount<gRejectedErrorNo; ErrorCount++)
       {
           ErrorReturnValue = SetBulkErrorDetails(gBulkErrorDetailsIndex, ErrorCount,gErrorNode)   ;
           if(ErrorReturnValue == -1)
           {
              return -1;
           }
       }
   }
   gRejectedErrorNo = 0;

   return 0;
}

int  ReadACI()
{
   int i;
   int  ReturnValue = 0 ;
   int  ErrorReturnValue = 0 ;
   char TempNumtoChar [10]   ;
   int  ErrorCount = 0       ;
   int  lValidateFlag = 0    ;
   TotalAdvisedChargeValue *pTotalAdvisedChargeValue;

   gErrorNode = 15 ;

   gRejectedErrorNo = 0;

   if(NOT_NULL(DIC.a.transferBatch->auditControlInfo))
   {
      /* Check for EarliestCallTimeStamp */
      if(NOT_NULL(DIC.a.transferBatch->auditControlInfo->earliestCallTimeStamp))
      {
         if(ASNOCTS_PRESENT(&DIC.a.transferBatch->auditControlInfo->earliestCallTimeStamp->localTimeStamp))
         {
            strcpy(ACI.EarliestCallTimeStamp.LocalTimeStamp,
                   DIC.a.transferBatch->auditControlInfo->earliestCallTimeStamp->localTimeStamp.octs);
         }

         if(ASNOCTS_PRESENT(&DIC.a.transferBatch->auditControlInfo->earliestCallTimeStamp->utcTimeOffset))
         {
            strcpy(ACI.EarliestCallTimeStamp.UtcTimeOffset,
                   DIC.a.transferBatch->auditControlInfo->earliestCallTimeStamp->utcTimeOffset.octs);
         }
      }

      /* Check for LatestCallTimeStamp */
      if(NOT_NULL(DIC.a.transferBatch->auditControlInfo->latestCallTimeStamp))
      {
         if(ASNOCTS_PRESENT(&DIC.a.transferBatch->auditControlInfo->latestCallTimeStamp->localTimeStamp))
         {
            strcpy(ACI.LatestCallTimeStamp.LocalTimeStamp,
                   DIC.a.transferBatch->auditControlInfo->latestCallTimeStamp->localTimeStamp.octs);
         }

         if(ASNOCTS_PRESENT(&DIC.a.transferBatch->auditControlInfo->latestCallTimeStamp->utcTimeOffset))
         {
            strcpy(ACI.LatestCallTimeStamp.UtcTimeOffset,
                   DIC.a.transferBatch->auditControlInfo->latestCallTimeStamp->utcTimeOffset.octs);
         }
      }

      /* Check for TotalCharge */
      if(NOT_NULL(DIC.a.transferBatch->auditControlInfo->totalCharge))
      {
         ACI.TotalCharge  = *DIC.a.transferBatch->auditControlInfo->totalCharge;

         /* TotalCharge : Syntax Error Check */
         sprintf (TempNumtoChar,"%d",ACI.TotalCharge);
         ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
         if(ReturnValue != 0)
         {
              REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 415             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AuditControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalCharge");
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;15:0:L;415:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
         }

         /* TotalCharge : Value out of range Error Check */
         if (ACI.TotalCharge < 0)
         {
              REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 415             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AuditControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalCharge");
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;15:0:L;415:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }

              ReturnValue = 0 ;
         }

      }
      else
      {
         REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
         REI.APPLICATION_TAG[gRejectedErrorNo] = 15                         ;
         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
         if(lValidateFlag == 0)
         {
             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AuditControlInformation");
             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"AuditControlInfo")  ;
             strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;15:0:L") ;
             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Total Charge missing within group");
             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
             gRejectedErrorNo++ ;
         }
      }


      /* Check for TotalChargeRefund */
      if(NOT_NULL(DIC.a.transferBatch->auditControlInfo->totalChargeRefund))
      {
         ACI.TotalChargeRefund  = *DIC.a.transferBatch->auditControlInfo->totalChargeRefund;

         /* TotalChargeRefund : Syntax Error Check */
         sprintf (TempNumtoChar,"%d",ACI.TotalChargeRefund);
         ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
         if(ReturnValue != 0)
         {
              REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 355             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AuditControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalChargeRefund");
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;15:0:L;355:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
         }

         /* TotalChargeRefund : Value out of range Error Check */
         if (ACI.TotalChargeRefund < 0)
         {
              REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 355             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AuditControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalChargeRefund");
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;15:0:L;355:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range (except zero)");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }

              ReturnValue = 0 ;
         }

         /* TotalChargeRefund : Value is Zero */
         if (ACI.TotalChargeRefund == 0)
         {
              REI.ERROR_CODE[gRejectedErrorNo]  = 21                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 355             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AuditControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalChargeRefund");
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;15:0:L;355:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Item Total Charge Refund has a value of zero");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }

              ReturnValue = 0 ;
         }


      }
      
      /* Check for TotalTaxRefund */
      if(NOT_NULL(DIC.a.transferBatch->auditControlInfo->totalTaxRefund))
      {
         ACI.TotalTaxRefund  = *DIC.a.transferBatch->auditControlInfo->totalTaxRefund;


         /* TotalTaxRefund : Syntax Error Check */
         sprintf (TempNumtoChar,"%d",ACI.TotalTaxRefund);
         ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
         if(ReturnValue != 0)
         {
              REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 353             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AuditControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalTaxRefund");
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;15:0:L;353:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
         }

         /* TotalTaxRefund : Value out of range Error Check */
         if (ACI.TotalTaxRefund <= 0)
         {
              REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 353             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AuditControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalTaxRefund");
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;15:0:L;353:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
         }

      }

      /* Check for TotalTaxValue */
      if(NOT_NULL(DIC.a.transferBatch->auditControlInfo->totalTaxValue))
      {
         ACI.TotalTaxValue  = *DIC.a.transferBatch->auditControlInfo->totalTaxValue;

         /* TotalTaxValue : Syntax Error Check */
         sprintf (TempNumtoChar,"%d",ACI.TotalTaxValue);
         ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
         if(ReturnValue != 0)
         {
              REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 226             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AuditControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalTaxValue");
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;15:0:L;226:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
         }

         /* TotalTaxValue : Value out of range Error Check */
         if (ACI.TotalTaxValue < 0)
         {
              REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 226             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AuditControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalTaxValue");
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;15:0:L;226:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }

              ReturnValue = 0 ;
         }

      }
      else
      {
         REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
         REI.APPLICATION_TAG[gRejectedErrorNo] = 15                         ;
         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
         if(lValidateFlag == 0)
         {
             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AuditControlInformation");
             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"AuditControlInfo")  ;
             strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;15:0:L") ;
             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Total Tax Value missing within group");
             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
             gRejectedErrorNo++ ;
         }
      }


      /* Check for TotalDiscountValue */
      if(NOT_NULL(DIC.a.transferBatch->auditControlInfo->totalDiscountValue))
      {
         ACI.TotalDiscountValue  = *DIC.a.transferBatch->auditControlInfo->totalDiscountValue;


         /* TotalDiscountValue : Syntax Error Check */
         sprintf (TempNumtoChar,"%d",ACI.TotalDiscountValue);
         ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
         if(ReturnValue != 0)
         {
              REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 225             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AuditControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalDiscountValue");
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;15:0:L;225:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
         }

         /* TotalDiscountValue : Value out of range Error Check */
         if (ACI.TotalDiscountValue < 0)
         {
              REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 225             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AuditControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalDiscountValue");
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;15:0:L;225:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }

              ReturnValue = 0 ;
         }

      }
      else
      {
         REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
         REI.APPLICATION_TAG[gRejectedErrorNo] = 15                         ;
         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
         if(lValidateFlag == 0)
         {
             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AuditControlInformation");
             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"AuditControlInfo")  ;
             strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;15:0:L") ;
             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Total Discount Value missing within group");
             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
             gRejectedErrorNo++ ;
         }
      }


      /* Check for TotalDiscountRefund */
      if(NOT_NULL(DIC.a.transferBatch->auditControlInfo->totalDiscountRefund))
      {
         ACI.TotalDiscountRefund  = *DIC.a.transferBatch->auditControlInfo->totalDiscountRefund;

         /* TotalDiscountRefund : Syntax Error Check */
         sprintf (TempNumtoChar,"%d",ACI.TotalDiscountRefund);
         ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
         if(ReturnValue != 0)
         {
              REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 354             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AuditControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalDiscountRefund");
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;15:0:L;354:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
         }

         /* TotalDiscountRefund : Value out of range Error Check */
         if (ACI.TotalDiscountRefund <= 0)
         {
              REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 354             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AuditControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalDiscountRefund");
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;15:0:L;354:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
         }

      }

      /* Check for TotalAdvisedChargeValue */
      /*
      if(NOT_NULL(DIC.a.transferBatch->auditControlInfo->totalAdvisedChargeValueList))
      {
         ACIA.TotalAdvisedChargeValueList = 1;
         i = 0;

         FOR_EACH_LIST_ELMT(pTotalAdvisedChargeValue,DIC.a.transferBatch->auditControlInfo->totalAdvisedChargeValueList)
         {
            if(ASNOCTS_PRESENT(&pTotalAdvisedChargeValue->advisedChargeCurrency))
            {
               strcpy(ACI.TotalAdvisedChargeValue[i].AdvisedChargeCurrency,
                      pTotalAdvisedChargeValue->advisedChargeCurrency.octs);
               ACIA.TotalAdvisedChargeValue[i].AdvisedChargeCurrency = 1;
            }
            if(NOT_NULL(pTotalAdvisedChargeValue->totalAdvisedCharge))
            {
               ACI.TotalAdvisedChargeValue[i].TotalAdvisedCharge  = *pTotalAdvisedChargeValue->totalAdvisedCharge;
               ACIA.TotalAdvisedChargeValue[i].TotalAdvisedCharge = 1;
            }
            if(NOT_NULL(pTotalAdvisedChargeValue->totalAdvisedChargeRefund))
            {
               ACI.TotalAdvisedChargeValue[i].TotalAdvisedChargeRefund = *pTotalAdvisedChargeValue->totalAdvisedChargeRefund; 
               ACIA.TotalAdvisedChargeValue[i].TotalAdvisedChargeRefund = 1;
            }
            if(NOT_NULL(pTotalAdvisedChargeValue->totalCommission))
            {
               ACI.TotalAdvisedChargeValue[i].TotalCommission  = *pTotalAdvisedChargeValue->totalCommission;
               ACIA.TotalAdvisedChargeValue[i].TotalCommission = 1;
            }
            if(NOT_NULL(pTotalAdvisedChargeValue->totalCommissionRefund))
            {
               ACI.TotalAdvisedChargeValue[i].TotalCommissionRefund  = *pTotalAdvisedChargeValue->totalCommissionRefund;
               ACIA.TotalAdvisedChargeValue[i].TotalCommissionRefund = 1;
            }

            i++;
         }

         ACI.TotalACValue = i;
      }
      */

      /* Check for CallEventDetailsCount */
      if(NOT_NULL(DIC.a.transferBatch->auditControlInfo->callEventDetailsCount))
      {
         ACI.CallEventDetailsCount  = *DIC.a.transferBatch->auditControlInfo->callEventDetailsCount;

         /* CallEventDetailsCount : Syntax Error Check */
         sprintf (TempNumtoChar,"%d",ACI.CallEventDetailsCount);
         ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
         if(ReturnValue != 0)
         {
              REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 43              ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AuditControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallEventDetailsCount");
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;15:0:L;43:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
         }

         /* CallEventDetailsCount : Value out of range Error Check */
         if (ACI.CallEventDetailsCount <= 0)
         {
              REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 43              ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AuditControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallEventDetailsCount");
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;15:0:L;43:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
         }


      }
      else
      {
         REI.ERROR_CODE[gRejectedErrorNo]  = 33                             ;
         REI.APPLICATION_TAG[gRejectedErrorNo] = 15                         ;
         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
         if(lValidateFlag == 0)
         {
             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AuditControlInformation");
             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"AuditControlInfo")  ;
             strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;15:0:L") ;
             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Call Event Details Count missing within group");
             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
             gRejectedErrorNo++ ;
         }
      }


   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 36                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 1                          ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          gErrorNode = REI.APPLICATION_TAG[gRejectedErrorNo] ;
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"TransferBatch")         ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TransferBatch")     ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L")        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Audit Control Information missing from group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }



   if((gRejectedErrorNo > 0) && (strcmp(gGenerateFilesFlg,"N")!=0))
   {
       for(ErrorCount=0; ErrorCount<gRejectedErrorNo; ErrorCount++)
       {
           ErrorReturnValue = SetBulkErrorDetails(gBulkErrorDetailsIndex, ErrorCount,gErrorNode)   ;
           if(ErrorReturnValue == -1)
           {
              return -1;
           }
       }
   }
   gRejectedErrorNo = 0;


   return 0;
}


int ValidateNTGroupInfo()
{
    int ErrorReturnValue = 0 ;
    int ReturnValue = 0;
    int SetError = 0;
    int ErrorCount = 0 ;
    int lValidateFlag = 0 ;


    if((strcmp(gCheckFileAgeFlag,"Y") == 0) && (strcmp(gFileStartDate,BCI.FileAvailableTimeStamp.LocalTimeStamp) > gFileAge))
    {
        REI.ERROR_CODE[gRejectedErrorNo]  = 263                            ;
        REI.APPLICATION_TAG[gRejectedErrorNo] = 2                          ;
        strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
        lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
        if(lValidateFlag == 0)
        {
            strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
            strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Notification")      ;
            strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L")       ;
            fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
            strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Difference between actual date/time file received and File Available Timestamp is greater than the Exceptional File Transmission Timescale as specified in BARG PRD BA.08");
            strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
            gRejectedErrorNo++ ;
        }
    } 


    if((gRejectedErrorNo > 0) && (strcmp(gGenerateFilesFlg,"N")!=0))
    {
       for(ErrorCount=0; ErrorCount<gRejectedErrorNo; ErrorCount++)
       {
           ErrorReturnValue = SetBulkErrorDetails(gBulkErrorDetailsIndex, ErrorCount,REI.APPLICATION_TAG[ErrorCount])   ;
           if(ErrorReturnValue == -1)
           {
              return -1;
           }
       }
    }
    gRejectedErrorNo = 0;


    return 0;

}

int ValidateTBGroupInfo()
{
    int ErrorReturnValue = 0 ;
    int ReturnValue = 0;
    int SetError = 0;
    int k,l;
    int ErrorCount = 0 ;
    int  lValidateFlag = 0    ;
    int ErrorNode[10000] ;
    char TempNumtoChar [10]   ;

    gRejectedErrorNo = 0;

 
    if((strcmp(gCheckFileAgeFlag,"Y") == 0) && (strcmp(gFileStartDate,BCI.FileAvailableTimeStamp.LocalTimeStamp) > gFileAge))
    { 
        ErrorNode[gRejectedErrorNo]           = 4        ;
        REI.ERROR_CODE[gRejectedErrorNo]      = 263      ;
        REI.APPLICATION_TAG[gRejectedErrorNo] = 4        ;
        strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL") ;
        lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
        if(lValidateFlag == 0)
        {
            strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"BatchControlInformation");
            strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"BatchControlInfo")      ;
            strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;4:0:L")       ;
            fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
            strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Difference between actual date/time file received and File Available Timestamp is greater than the Exceptional File Transmission Timescale as specified in BARG PRD BA.08");
            strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
            gRejectedErrorNo++ ;
        }
    }

    if ((gCurrencyConversionFlag == 1) && (ACI.TotalCharge > 0))
    {
        ErrorNode[gRejectedErrorNo]           = 5         ;
        REI.ERROR_CODE[gRejectedErrorNo]      = 34        ;
        REI.APPLICATION_TAG[gRejectedErrorNo] = 5         ;
        strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")  ;
        lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
        if(lValidateFlag == 0)
        {
            strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation") ;
            strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"AccountingInfo")    ;
            strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L")  ;
            fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
            strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Group Currency Conversion missing within group and the transfer includes one or more Charge greater than zero");
            strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
            gRejectedErrorNo++ ;
        }
    }


    if((gTaxationFlag == 1) && ( ACI.TotalTaxValue > 0))
    {
        ErrorNode[gRejectedErrorNo]           = 5           ;
        REI.ERROR_CODE[gRejectedErrorNo]      = 30          ;
        REI.APPLICATION_TAG[gRejectedErrorNo] = 5           ;
        strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")    ;
        lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
        if(lValidateFlag == 0)
        {
            strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation") ;
            strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"AccountingInfo")    ;
            strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L")  ;
            fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
            strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"No Taxation group present and batch contains taxes");
            strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
            gRejectedErrorNo++ ;
        }
    }


    if((gDiscountFlag == 1) && ( ACI.TotalDiscountValue > 0))
    {
        ErrorNode[gRejectedErrorNo]           = 5                 ;
        REI.ERROR_CODE[gRejectedErrorNo]      = 31                ;
        REI.APPLICATION_TAG[gRejectedErrorNo] = 5                 ;
        strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")          ;
        lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
        if(lValidateFlag == 0)
        {
            strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation") ;
            strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"AccountingInfo")    ;
            strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L")  ;
            fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
            strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"No Discounting group present and batch contains discounts");
            strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
            gRejectedErrorNo++ ;
        }
    }

 



    if(gExchangeRateCount > 1)
    {
        /* Loop through the Exchange Rate */
        gExchangeRateCodeFlag = 0;

        for(k=0; k<(gExchangeRateCount-1); k++)
        {
            for(l =k+1; l < gExchangeRateCount ; l++)
            {
                if(ACC.CurrencyConversionInfo[k].ExchangeRateCode == ACC.CurrencyConversionInfo[l].ExchangeRateCode)
                {
                     if((ACC.CurrencyConversionInfo[k].ExchangeRate == ACC.CurrencyConversionInfo[l].ExchangeRate) && 
                         (ACC.CurrencyConversionInfo[k].NumberOfDecimalPlaces == ACC.CurrencyConversionInfo[l].NumberOfDecimalPlaces))
                     {
                         gExchangeRateCodeFlag = 34;
                         ErrorNode[gRejectedErrorNo]           = 5             ;
                         REI.ERROR_CODE[gRejectedErrorNo]      = 34            ;
                         REI.APPLICATION_TAG[gRejectedErrorNo] = 106           ;
                         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")      ;
                         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CurrencyConversion");
                             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;80:%d:L;106:0:L",k+1) ;
                             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"More than one occurrence of group with same Exchange Rate Code where Number Of Decimal Places a                             nd Exchange Rate are the same (i.e. duplicate Currency Conversion table entry)");
                             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                             gRejectedErrorNo++ ;
                         }
                         break;
                     }
                     else
                     {
                         gExchangeRateCodeFlag = 33;
                         ErrorNode[gRejectedErrorNo]           = 5             ;
                         REI.ERROR_CODE[gRejectedErrorNo]      = 33            ;
                         REI.APPLICATION_TAG[gRejectedErrorNo] = 106           ;
                         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")      ;
                         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CurrencyConversion");
                             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;80:%d:L;106:0:L",k+1) ;
                             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"More than one occurrence of group with same Exchange Rate Code where Number Of Decimal Places and/or Exchange Rate are not the same");
                             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                             gRejectedErrorNo++ ;
                         }
                         break;
                     }

                     }
            }
        }


    }


    if(gDiscountingCount > 1)
    {
        /* Loop through the Exchange Rate */
        gDiscountCodeFlag = 0;

        for(k=0; k<(gDiscountingCount-1); k++)
        {
            for(l =k+1; l < gDiscountingCount ; l++)
            {
                if(ACC.Discounting[k].DiscountCode == ACC.Discounting[l].DiscountCode)
                {
                     if(ACC.Discounting[k].DiscountType == ACC.Discounting[l].DiscountType) 
                     {
                         gDiscountCodeFlag = 33;

                         ErrorNode[gRejectedErrorNo]           = 5               ;
                         REI.ERROR_CODE[gRejectedErrorNo]      = 33              ;
                         REI.APPLICATION_TAG[gRejectedErrorNo] = 95              ;
                         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Discounting")       ;
                             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;95:%d:L;94:0:L",k+1) ;
                             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"More than one occurrence of group with same Discount Code where group Discount Applied is the s                             ame(duplicate Discounting table entry)");
                             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                             gRejectedErrorNo++ ;
                         }

                         break;
                     }
                     else
                     {
                         gDiscountCodeFlag = 32;
                         ErrorNode[gRejectedErrorNo]           = 5             ;
                         REI.ERROR_CODE[gRejectedErrorNo]      = 32            ;
                         REI.APPLICATION_TAG[gRejectedErrorNo] = 95            ;
                         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")      ;
                         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Discounting")       ;
                             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;95:%d:L;94:0:L",k+1) ;
                             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"More than one occurrence of group with same Discount Code where group Discount Applied is  not                              the same");
                             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                             gRejectedErrorNo++ ;
                         }
                         break;
                     }
                }
            }
        }

    }


    if(gRecEntityInfoCount > 1)
    {
        /* Loop through the Exchange Rate */
        gRecordingEntityFlag = 0;

        for(k=0; k<(gRecEntityInfoCount-1); k++)
        {
            for(l =k+1; l < gRecEntityInfoCount ; l++)
            {
                if(NI.RecEntityInfo[k].RecEntityCode == NI.RecEntityInfo[l].RecEntityCode)
                {
                     if((NI.RecEntityInfo[k].RecEntityType == NI.RecEntityInfo[l].RecEntityType) &&
                         (NI.RecEntityInfo[k].RecEntityId == NI.RecEntityInfo[l].RecEntityId))
                     {
                         gRecordingEntityFlag = 34;

                         ErrorNode[gRejectedErrorNo]           = 6               ;
                         REI.ERROR_CODE[gRejectedErrorNo]      = 34              ;
                         REI.APPLICATION_TAG[gRejectedErrorNo] = 183             ;
                         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                            strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkInformation");
                            strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityInfo")      ;
                            sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;6:0:L;188:%d:L;183:0:L",l+1) ;
                            fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                            strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"More than one occurrence of group with same Recording Entity Code where Recording Entity Type an                            d Recording Entity Identification are the same (i.e. duplicate Recording Entity Information table entry)");
                            strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                            gRejectedErrorNo++ ;
                         }
                         break ;
                     }
                     else
                     {
                         gRecordingEntityFlag = 33;

                         ErrorNode[gRejectedErrorNo]           = 6                 ;
                         REI.ERROR_CODE[gRejectedErrorNo]      = 33                ;
                         REI.APPLICATION_TAG[gRejectedErrorNo] = 183               ;
                         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")          ;
                         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                            strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkInformation");
                            strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityInfo")      ;
                            sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;6:0:L;188:%d:L;183:0:L",l+1) ;
                            fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                            strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"More than one occurrence of group with same Recording Entity Code where Recording Entity Type and/or Recording Entity Identification are not the same");
                            strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                            gRejectedErrorNo++ ;
                         }
                         break ;
					}

		/*				 if(ACC.CurrencyConversionInfo[k].ExchangeRate>gExchangeRate[k])
                     {
                            gExchangeRateCodeFlag = 33;
                         ErrorNode[gRejectedErrorNo]           = 5             ;
                         REI.ERROR_CODE[gRejectedErrorNo]      = 200            ;
                         REI.APPLICATION_TAG[gRejectedErrorNo] = 106           ;
                         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")      ;
                         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CurrencyConversion");
                             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;80:%d:L;106:0:L",k+1) ;
                             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Exchange Rate higher than expected and applied to one or more Charges.");
                             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"ACC.CurrencyConversionInfo[k].ExchangeRate");
                             gRejectedErrorNo++ ;
                         }
                         break;
                     }


           else if(ACC.CurrencyConversionInfo[k].ExchangeRate<gExchangeRate[k])
                     {
                            gExchangeRateCodeFlag = 33;
                         ErrorNode[gRejectedErrorNo]           = 5             ;
                         REI.ERROR_CODE[gRejectedErrorNo]      = 200            ;
                         REI.APPLICATION_TAG[gRejectedErrorNo] = 106           ;
                         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")      ;
                         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CurrencyConversion");
                             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;80:%d:L;106:0:L",k+1) ;
                             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Exchange Rate less than expected (see BA.11) and applied to one or more Charges and at least one of the Charges the Exchange Rate is applied to is greater than zero..");
                             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"ACC.CurrencyConversionInfo[k].ExchangeRate");
                             gRejectedErrorNo++ ;
                         }
                         break;
                     }  */

                }

		 }
        }
    }


    if(gTaxationCount> 1)
    {
        /* Loop through the Exchange Rate */
        gTaxationFlag = 0;

        for(k=0; k<(gTaxationCount-1); k++)
        {
            for(l =k+1; l < gTaxationCount; l++)
            {
                if(ACC.Taxation[k].TaxCode == ACC.Taxation[l].TaxCode)
                {
                     if((ACC.Taxation[k].TaxType == ACC.Taxation[l].TaxType) && (ACC.Taxation[k].TaxRate == ACC.Taxation[l].TaxRate))
                     {
                         gTaxationFlag = 0;
                         break;
                     }
                     else
                     {
                         gTaxationFlag = 33;
                         ErrorNode[gRejectedErrorNo]           = 5              ;
                         REI.ERROR_CODE[gRejectedErrorNo]      = 33             ;
                         REI.APPLICATION_TAG[gRejectedErrorNo] = 216            ;
                         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")       ;
                         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Taxation")    ;
                             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;211:%d:L;216:0:L",k+1);
                             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"More than one occurrence of group with same Tax Rate Code where Tax Type,Tax Rate and/or ChargeType are not the same");
                             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                             gRejectedErrorNo++ ;
                         }
                         break;
                     }
                }
            }
        }

    }


    if(gUTCOffsetCount >1)
    {
        gUTCOffSetFlag = 0;

        for(k=0; k<(gUTCOffsetCount-1); k++)
        {
            for(l =k+1; l < gUTCOffsetCount; l++)
            {
                if(NI.UtcTimeOffsetInfo[k].UtcTimeOffsetCode ==  NI.UtcTimeOffsetInfo[l].UtcTimeOffsetCode)
                {
                     if(strcmp(NI.UtcTimeOffsetInfo[k].UtcTimeOffset,NI.UtcTimeOffsetInfo[l].UtcTimeOffset) == 0)
                     {
                         gUTCOffSetFlag = 33;

                         ErrorNode[gRejectedErrorNo]           = 6              ;
                         REI.ERROR_CODE[gRejectedErrorNo]      = 33             ;
                         REI.APPLICATION_TAG[gRejectedErrorNo] = 234            ;
                         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")       ;
                         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkInformation");
                             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"UtcTimeOffsetInfo")       ;
                             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;6:0:L;234:%d:L;233:0:L",k+1) ;
                             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"More than one occurrence of group with same UTC Time Offset Code where UTC Time Offset is the same");
                             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                             gRejectedErrorNo++ ;
                         }
                         break;
                     }
                     else
                     {
                         gUTCOffSetFlag = 32;
                         ErrorNode[gRejectedErrorNo]           = 6              ;
                         REI.ERROR_CODE[gRejectedErrorNo]      = 32             ;
                         REI.APPLICATION_TAG[gRejectedErrorNo] = 234            ;
                         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")       ;
                         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkInformation");
                              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"UtcTimeOffsetInfo")       ;
                              sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;6:0:L;234:%d:L;233:0:L",k+1) ;
                              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"More than one occurrence of group with same UTC Time Offset Code where UTC Time Offset is not the same");
                              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                              gRejectedErrorNo++ ;
                         }
                         break;
                     }
                }
            }
        }

    }

/* Added by Anitha for WBS 4.3 To check the Count of CallEvent Details */

sprintf (TempNumtoChar,"%d",ACI.CallEventDetailsCount);


         if(ACI.CallEventDetailsCount != gTotalCdrsCount)
         {    
		      ErrorNode[gRejectedErrorNo]           =15              ;
              REI.ERROR_CODE[gRejectedErrorNo]  = 100                 ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 43              ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AuditControlInformation");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallEventDetailsCount");
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;15:0:L;43:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value does not match the count of Call Event Details.(any rejected Call Event Details must be included)");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
         }


   if((gRejectedErrorNo > 0) && (strcmp(gGenerateFilesFlg,"N")!=0))
    {
       for(ErrorCount=0; ErrorCount<gRejectedErrorNo; ErrorCount++)
       {
           ErrorReturnValue = SetBulkErrorDetails(gBulkErrorDetailsIndex, ErrorCount,ErrorNode[ErrorCount])   ;
           if(ErrorReturnValue == -1)
           {
              return -1;
           }
       }
    }
    gRejectedErrorNo = 0;


    return 0;

}

int  ReadMOC(struct MobileOriginatedCall* mobileOriginatedCall)
{
   int i=0,j=0;
   unsigned char ThirdPartyNumber[87];  /* AddressStringDigits */
   unsigned char Imei[46];
   int CICount=0;                       /* ChargeInformation Count */
   int ErrorReturnValue = 0 ;
   int ReturnValue = 0;
   int SetError = 0;
   int  ErrorCount = 0       ;
   char TempNumtoChar [20]   ;
   int  lValidateFlag = 0    ;
   gCalledNumberFlag=0;
   BasicServiceUsed *BSU;
   ChargeInformation *CI;

   INIT_STR(stContext.CallEventType) ; 
   sprintf(stContext.CallEventType,"%s;9:0:L",stContext.CallEventDetails);
   fnRemTrailSpaces(stContext.CallEventType) ;

   BCT.CALL_TYPE = 2;
   gChargingTimeStamp = 0;
   gErrorNode = 9 ;

   if(NOT_NULL(mobileOriginatedCall->basicCallInformation))
   {
      ReadMoBasicCallInformation(mobileOriginatedCall->basicCallInformation);
   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 9                          ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC");
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MobileOriginatedCall") ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group MO Basic Call Information missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }

   if((strcmp(gCheckCallAgeFlag,"Y") == 0) && (strcmp(g_CdrStartDate,BCT.CALL_DATE) > 0))
   {

      REI.ERROR_CODE[gRejectedErrorNo]  = 261            ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 9         ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC");
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MobileOriginatedCall") ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)   ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Call older than allowed by BARG in 'Exceptional Situations' in BARG PRD BA.08");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CALL_DATE);
          gRejectedErrorNo++ ;
      }
   }


   if(NOT_NULL(mobileOriginatedCall->locationInformation))
   {
       ReadLocationInformation(mobileOriginatedCall->locationInformation);
   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 9                          ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MobileOriginatedCall")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MOC")               ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Location Information missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }


   if(NOT_NULL(mobileOriginatedCall->equipmentIdentifier))
   {
      if(mobileOriginatedCall->equipmentIdentifier->choiceId == IMEIORESN_IMEI)
      { 
         if(NOT_NULL(mobileOriginatedCall->equipmentIdentifier->a.imei))
         {
            fnDconvhx(mobileOriginatedCall->equipmentIdentifier->a.imei->octetLen,
                      mobileOriginatedCall->equipmentIdentifier->a.imei->octs,Imei,'S');
            fnRemTrailSpaces(Imei);
            strcpy(BCT.IMEI,Imei);
         }
      }
   }

   if(NOT_NULL(mobileOriginatedCall->basicServiceUsedList))
   {
      j = 0 ;
      FOR_EACH_LIST_ELMT(BSU,mobileOriginatedCall->basicServiceUsedList)
      {
         INIT_STR(stContext.BasicServiceUsed) ;
         sprintf(stContext.BasicServiceUsed,"%s;38:%d:L;39:0:L",stContext.CallEventType,j+1)        ;
         fnRemTrailSpaces(stContext.BasicServiceUsed) ;
         
         if(NOT_NULL(BSU->basicService))
         { 
              ReadBasicService(BSU->basicService);
         }
         else
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 39                          ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC")  ;
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"BasicServiceUsed")               ;
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.BasicServiceUsed)        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Basic Service missing within group");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                 gRejectedErrorNo++ ;
             }
         }


         if(NOT_NULL(BSU->chargingTimeStamp))
         {
             INIT_STR(stContext.ChargingTimeStamp) ;
             sprintf(stContext.ChargingTimeStamp,"%s;74:0:L",stContext.BasicServiceUsed) ;
             fnRemTrailSpaces(stContext.ChargingTimeStamp) ;
  
             gChargingTimeStamp = 1 ;

             if(ASNOCTS_PRESENT(&BSU->chargingTimeStamp->localTimeStamp))
             {
                 strcpy(BCT.CHARGING_TIME_STAMP,BSU->chargingTimeStamp->localTimeStamp.octs);

                 /* CallEventStartTimeStamp : Syntax Error Check */
                 ReturnValue = fnCheckSyntax(BCT.CHARGING_TIME_STAMP,"DI") ;
                 if(ReturnValue != 0)
                 {
                     REI.ERROR_CODE[gRejectedErrorNo]  = 10                   ;
                     REI.APPLICATION_TAG[gRejectedErrorNo] = 74               ;
                     strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                     lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                     if(lValidateFlag == 0)
                     {
                         strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                         strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargingTimeStamp") ;
                         sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargingTimeStamp,"16:0:L")   ;
                         fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                         strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                         strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CHARGING_TIME_STAMP);
                         gRejectedErrorNo++ ;
                     }
                     ReturnValue = 0 ;
                 }

                 /* CallEventStartTimeStamp : Value Out of Range Check */
                 ReturnValue = fnDateRangeCheck(BCT.CHARGING_TIME_STAMP);
                 if(ReturnValue != 0)
                 {
                     REI.ERROR_CODE[gRejectedErrorNo]  = 20             ;
                     REI.APPLICATION_TAG[gRejectedErrorNo] = 74         ;
                     strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")  ;
                     lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                     if(lValidateFlag == 0)
                     {
                         strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                         strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargingTimeStamp") ;
                         sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargingTimeStamp,"16:0:L")   ;
                         fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                         strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                         strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CHARGING_TIME_STAMP);
                         gRejectedErrorNo++ ;
                     }

                     ReturnValue = 0 ;
                 }

                 gDateDifference = 0 ;
                 gDateDifference = fnCheckDateDifference(BCT.CHARGING_TIME_STAMP,BCT.CALL_DATE) ;

                 if(gDateDifference > BCT.CALL_DURATION)
                 {
                     REI.ERROR_CODE[gRejectedErrorNo]  = 100            ;
                     REI.APPLICATION_TAG[gRejectedErrorNo] = 74         ;
                     strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")  ;
                     lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                     if(lValidateFlag == 0)
                     {
                         strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC");
                         strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargingTimeStamp") ;
                         sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargingTimeStamp,"16:0:L") ;
                         fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                         strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Charging Timestamp is later than end of call (Call Event Start Timestamp plus Total Call Event Duration)");
                         strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CHARGING_TIME_STAMP);
                         gRejectedErrorNo++ ;
                     }
                     ReturnValue = 0 ;
                 }

             }

             if(NOT_NULL(BSU->chargingTimeStamp->utcTimeOffsetCode))
             {

                 /* UtcTimeOffsetCode : Syntax Error Check */
                 sprintf (TempNumtoChar,"%d", *BSU->chargingTimeStamp->utcTimeOffsetCode);
                 ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
                 if(ReturnValue != 0)
                 {
                     REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
                     REI.APPLICATION_TAG[gRejectedErrorNo] = 232             ;
                     strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                     lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                     if(lValidateFlag == 0)
                     { 
                         strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                         strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"UtcTimeOffsetCode") ;
                         sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargingTimeStamp,"232:0:L")   ;
                         fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                         strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                         strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                         gRejectedErrorNo++ ;
                     }
                     ReturnValue = 0 ;
                 }
             }
             else
             {
                  REI.ERROR_CODE[gRejectedErrorNo]  = 30                  ;
                  REI.APPLICATION_TAG[gRejectedErrorNo] = 74              ;
                  strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                  lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                  if(lValidateFlag == 0)
                  {
                      strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                      strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargingTimeStamp") ;
                      strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargingTimeStamp)   ;
                      fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                      strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory associated item UTC Time Offset Code missing");
                      strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                      gRejectedErrorNo++ ;
                  }

                  ReturnValue = 0 ;
             }

 

         }


         if(NOT_NULL(BSU->chargeInformationList))
         {
            FOR_EACH_LIST_ELMT(CI,BSU->chargeInformationList)
            {
               CICount = 0;

               ReadChargeInformationList(CI,CICount);


               CICount++;
               BCT.CHARGE_INFORMATION_COUNT = CICount;
            }
         }
         else
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 39                          ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC")  ;
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"BasicServiceUsed")               ;
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.BasicServiceUsed)        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Charge Information missing within group");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                 gRejectedErrorNo++ ;
             }
         }


         if(ASNOCTS_PRESENT(&BSU->hSCSDIndicator))
         {
            strcpy(BCT.HSCSD_INDICATOR,BSU->hSCSDIndicator.octs);

            /* HSCSDIndicator : Syntax Error Check */
            ReturnValue = fnCheckSyntax(BCT.HSCSD_INDICATOR,"DI") ;
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 424             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"HSCSDIndicator");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicServiceUsed,"424:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.HSCSD_INDICATOR);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }

            /* HSCSDIndicator : Value Out of Range */

            if (strcmp(BCT.HSCSD_INDICATOR,"1") != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 424             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"HSCSDIndicator");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicServiceUsed,"424:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.HSCSD_INDICATOR);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }
         }

         j++ ;
      }


      if(j > 1)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 35                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 9                          ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MobileOriginatedCall")               ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"More than one occurrence of group Basic Service Used present within group");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }
   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 9                          ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MobileOriginatedCall")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MOC")               ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Basic Service Used missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }


   if(ASNOCTS_PRESENT(&mobileOriginatedCall->supplServiceCode))
   {
      strcpy(BCT.SUPPLIMENTARY_SERVICE_CODE,mobileOriginatedCall->supplServiceCode.octs); 
  
      if(strcmp(BCT.SUPPLIMENTARY_SERVICE_CODE,"FF") == 0)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 22              ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 209         ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")   ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC")    ;
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SupplServiceCode")               ;
              sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"209:0:L") ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value 'FF'")                        ;
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.SUPPLIMENTARY_SERVICE_CODE);
              gRejectedErrorNo++ ;
          }
      }
   }

    
   if(NOT_NULL(mobileOriginatedCall->camelServiceUsed))
   { 
       ReadCamelServiceUsed(mobileOriginatedCall->camelServiceUsed);
   }
  
   stMOC1 = mobileOriginatedCall;

/*   if((gRejectedErrorNo > 0) && (gFatalErrorCount == 0) && (strcmp(gGenerateFilesFlg,"N")!=0))
   {
       gErrorCDRsCount = gErrorCDRsCount + 1 ;
       gErrorCDRsCharge = gErrorCDRsCharge + BCT.CHARGE + BCT.CAMEL_INVOCATION_FEE ;
       gErrorCDRsTax = gErrorCDRsTax + BCT.TAX_VALUE  ;
       gErrorCDRsDiscount = gErrorCDRsDiscount + BCT.DISCOUNT  ;
       gErrorCDRsDuration = gErrorCDRsDuration + BCT.CALL_DURATION ;
       gCDRErrorFlag = 1 ;

       for(ErrorCount=0; ErrorCount<gRejectedErrorNo; ErrorCount++)
       {
           ErrorReturnValue = SetBulkErrorDetails(gBulkErrorDetailsIndex, ErrorCount,9)   ;
           if(ErrorReturnValue == -1)
           {
              return -1;
           }
       }
   }
   gRejectedErrorNo = 0;*/

   /*
   printf("   IMEI :-%s-\n",BCT.IMEI);
   printf("SupplimentaryService Code : -%s-\n");
   */

/* Modified By Anitha on 02-MAY-2012 to check the CALLED_CALLING_NUMBER is inline with CallTypeLevel1 or not  */

       if(NOT_NULL(BCT.CALLED_CALLING_NUMBER) && (gCalledNumberFlag ==1) )
		{
          ReturnValue = fnCountryCodeCheck(BCT.CALLED_CALLING_NUMBER) ;              
          fnRemTrailSpaces(gMobilePrfx);      
          if(strcmp(CalledNumberPrefix,gMobilePrfx)==0)
         {
  
          if(BCT.CALL_TYPE_LEVEL1!=1)
           {
                  REI.ERROR_CODE[gRejectedErrorNo]  = 201             ;
                REI.APPLICATION_TAG[gRejectedErrorNo] =407             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")      ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC")  ;
                             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CalledNumber")               ;
                             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.Destination,"407:0:L")      ;
                             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Called Number is not inline with CallTypeLevel1");
                             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CALLED_CALLING_NUMBER);
                             gRejectedErrorNo++ ;
                         }

                         ReturnValue = 0 ;
              }
            }
           
 else if (strcmp(CalledNumberPrefix,gMobilePrfx)!=0)
   {

  if(BCT.CALL_TYPE_LEVEL1!=2)
    {
            REI.ERROR_CODE[gRejectedErrorNo]  = 201                 ;
            REI.APPLICATION_TAG[gRejectedErrorNo] = 407             ;
            strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
            lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC")  ;
                             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CalledNumber")               ;
                             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.Destination,"407:0:L")      ;
                             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Called Number is not inline with CallTypeLevel1");
                             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CALLED_CALLING_NUMBER);
                             gRejectedErrorNo++ ;
                         }

                        ReturnValue = 0 ;
                     }
                  }
            }

if((gRejectedErrorNo > 0) && (gFatalErrorCount == 0) && (strcmp(gGenerateFilesFlg,"N")!=0))
   {
       gErrorCDRsCount = gErrorCDRsCount + 1 ;
       gErrorCDRsCharge = gErrorCDRsCharge + BCT.CHARGE + BCT.CAMEL_INVOCATION_FEE ;
       gErrorCDRsTax = gErrorCDRsTax + BCT.TAX_VALUE  ;
       gErrorCDRsDiscount = gErrorCDRsDiscount + BCT.DISCOUNT  ;
       gErrorCDRsDuration = gErrorCDRsDuration + BCT.CALL_DURATION ;
       gCDRErrorFlag = 1 ;

       for(ErrorCount=0; ErrorCount<gRejectedErrorNo; ErrorCount++)
       {
           ErrorReturnValue = SetBulkErrorDetails(gBulkErrorDetailsIndex, ErrorCount,9)   ;
           if(ErrorReturnValue == -1)
           {
              return -1;
           }
       }
   }
   gRejectedErrorNo = 0;


   return 0 ;
}

int ReadMTC(struct MobileTerminatedCall* mobileTerminatedCall)
{
   int i=0,j=0;
   unsigned char Imei[46];
   int CICount=0;                       /* ChargeInformation Count */
   int ErrorReturnValue = 0 ;
   int ReturnValue = 0;
   int SetError = 0;
   int  ErrorCount = 0       ;
   char TempNumtoChar [20]   ;
   int  lValidateFlag = 0    ;
   BasicServiceUsed *BSU;
   ChargeInformation *CI;

   gErrorNode = 10 ;


   INIT_STR(stContext.CallEventType) ;
   sprintf(stContext.CallEventType,"%s;10:0:L",stContext.CallEventDetails);
   fnRemTrailSpaces(stContext.CallEventType) ;


   BCT.CALL_TYPE = 1;
   gChargingTimeStamp = 0;

   if(NOT_NULL(mobileTerminatedCall->basicCallInformation))
   {
      ReadMtBasicCallInformation(mobileTerminatedCall->basicCallInformation);
   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 10                         ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MTC");
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MobileTerminatedCall") ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group MT Basic Call Information missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }


   if((strcmp(gCheckCallAgeFlag,"Y") == 0) && (strcmp(g_CdrStartDate,BCT.CALL_DATE) > 0))
   {

      REI.ERROR_CODE[gRejectedErrorNo]  = 261            ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 10         ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MTC");
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MobileTerminatedCall") ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)   ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Call older than allowed by BARG in 'Exceptional Situations' in BARG PRD BA.08");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CALL_DATE);
          gRejectedErrorNo++ ;
      }
   }

   if(NOT_NULL(mobileTerminatedCall->locationInformation))
   {
       ReadLocationInformation(mobileTerminatedCall->locationInformation);
   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 10                         ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MTC");
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MobileTerminatedCall") ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Location Information missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }


   if(NOT_NULL(mobileTerminatedCall->equipmentIdentifier))
   {
      if(mobileTerminatedCall->equipmentIdentifier->choiceId == IMEIORESN_IMEI)
      {
         if(NOT_NULL(mobileTerminatedCall->equipmentIdentifier->a.imei))
         {
            fnDconvhx(mobileTerminatedCall->equipmentIdentifier->a.imei->octetLen,
                      mobileTerminatedCall->equipmentIdentifier->a.imei->octs,Imei,'S');
            fnRemTrailSpaces(Imei);
            strcpy(BCT.IMEI,Imei);
         }
      }
   }

   if(NOT_NULL(mobileTerminatedCall->basicServiceUsedList))
   {
      j = 0;
      FOR_EACH_LIST_ELMT(BSU,mobileTerminatedCall->basicServiceUsedList)
      {
         INIT_STR(stContext.BasicServiceUsed) ;
         sprintf(stContext.BasicServiceUsed,"%s;38:%d:L;39:0:L",stContext.CallEventType,j+1)        ;
         fnRemTrailSpaces(stContext.BasicServiceUsed) ;

         if(NOT_NULL(BSU->basicService))
         {
              ReadBasicService(BSU->basicService);
         }
         else
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 39                          ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MTC")  ;
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"BasicServiceUsed")               ;
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.BasicServiceUsed)        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Basic Service missing within group");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
             }
             gRejectedErrorNo++ ;
         }


         if(NOT_NULL(BSU->chargingTimeStamp))
         {
             INIT_STR(stContext.ChargingTimeStamp) ;
             sprintf(stContext.ChargingTimeStamp,"%s;74:0:L",stContext.BasicServiceUsed) ;
             fnRemTrailSpaces(stContext.ChargingTimeStamp) ;

             gChargingTimeStamp = 1 ;

             if(ASNOCTS_PRESENT(&BSU->chargingTimeStamp->localTimeStamp))
             {
                 strcpy(BCT.CHARGING_TIME_STAMP,BSU->chargingTimeStamp->localTimeStamp.octs);

                 /* CallEventStartTimeStamp : Syntax Error Check */
                 ReturnValue = fnCheckSyntax(BCT.CHARGING_TIME_STAMP,"DI") ;
                 if(ReturnValue != 0)
                 {
                     REI.ERROR_CODE[gRejectedErrorNo]  = 10                   ;
                     REI.APPLICATION_TAG[gRejectedErrorNo] = 74               ;
                     strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                     lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                     if(lValidateFlag == 0)
                     {
                         strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                         strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargingTimeStamp") ;
                         sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargingTimeStamp,"16:0:L")   ;
                         fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                         strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                         strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CHARGING_TIME_STAMP);
                         gRejectedErrorNo++ ;
                     }
                     ReturnValue = 0 ;
                 }

                 /* CallEventStartTimeStamp : Value Out of Range Check */
                 ReturnValue = fnDateRangeCheck(BCT.CHARGING_TIME_STAMP);
                 if(ReturnValue != 0)
                 {
                     REI.ERROR_CODE[gRejectedErrorNo]  = 20             ;
                     REI.APPLICATION_TAG[gRejectedErrorNo] = 74         ;
                     strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")  ;
                     lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                     if(lValidateFlag == 0)
                     {
                         strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                         strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargingTimeStamp") ;
                         sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargingTimeStamp,"16:0:L")   ;
                         fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                         strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                         strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CHARGING_TIME_STAMP);
                         gRejectedErrorNo++ ;
                     }
                     ReturnValue = 0 ;
                 }

                 gDateDifference = 0 ;
                 gDateDifference = fnCheckDateDifference(BCT.CHARGING_TIME_STAMP,BCT.CALL_DATE) ;

                 if(gDateDifference > BCT.CALL_DURATION)
                 {
                     REI.ERROR_CODE[gRejectedErrorNo]  = 100            ;
                     REI.APPLICATION_TAG[gRejectedErrorNo] = 74         ;
                     strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")  ;
                     lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                     if(lValidateFlag == 0)
                     {
                         strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC");
                         strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargingTimeStamp") ;
                         sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargingTimeStamp,"16:0:L") ;
                         fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                         strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Charging Timestamp is later than end of call (Call Event Start Timestamp plus Total Call Event Duration)");
                         strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CHARGING_TIME_STAMP);
                         gRejectedErrorNo++ ;
                     }
                     ReturnValue = 0 ;
                 }

             }

             if(NOT_NULL(BSU->chargingTimeStamp->utcTimeOffsetCode))
             {

                 /* UtcTimeOffsetCode : Syntax Error Check */
                 sprintf (TempNumtoChar,"%d", *BSU->chargingTimeStamp->utcTimeOffsetCode);
                 ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
                 if(ReturnValue != 0)
                 {
                     REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
                     REI.APPLICATION_TAG[gRejectedErrorNo] = 232             ;
                     strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                     lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                     if(lValidateFlag == 0)
                     {
                         strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                         strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"UtcTimeOffsetCode") ;
                         sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargingTimeStamp,"232:0:L")   ;
                         fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                         strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                         strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                         gRejectedErrorNo++ ;
                     }
                     ReturnValue = 0 ;
                 }
             }
             else
             {
                  REI.ERROR_CODE[gRejectedErrorNo]  = 30                  ;
                  REI.APPLICATION_TAG[gRejectedErrorNo] = 74              ;
                  strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                  lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                  if(lValidateFlag == 0)
                  {
                      strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                      strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargingTimeStamp") ;
                      strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargingTimeStamp)   ;
                      fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                      strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory associated item UTC Time Offset Code missing");
                      strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                      gRejectedErrorNo++ ;
                   }

                  ReturnValue = 0 ;
             }
         }



         if(NOT_NULL(BSU->chargeInformationList))
         {
            FOR_EACH_LIST_ELMT(CI,BSU->chargeInformationList)
            {
               CICount = 0;

               ReadChargeInformationList(CI,CICount);


               CICount++;
               BCT.CHARGE_INFORMATION_COUNT = CICount;
            }
         }
         else
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 39                          ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MTC")  ;
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"BasicServiceUsed")               ;
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.BasicServiceUsed)        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Charge Information missing within group");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                 gRejectedErrorNo++ ;
             }
         }


         if(ASNOCTS_PRESENT(&BSU->hSCSDIndicator))
         {
            strcpy(BCT.HSCSD_INDICATOR,BSU->hSCSDIndicator.octs);

            /* HSCSDIndicator : Syntax Error Check */
            ReturnValue = fnCheckSyntax(BCT.HSCSD_INDICATOR,"DI") ;
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 424             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MTC");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"HSCSDIndicator");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicServiceUsed,"424:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.HSCSD_INDICATOR);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }

            /* HSCSDIndicator : Value Out of Range */

            if (strcmp(BCT.HSCSD_INDICATOR,"1") != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 424             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MTC");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"HSCSDIndicator");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicServiceUsed,"424:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.HSCSD_INDICATOR);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }

         }

         j++ ;
      }

      if(j > 1)
      {
           REI.ERROR_CODE[gRejectedErrorNo]  = 35                             ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 10                         ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MTC")  ;
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MobileTerminatedCall")               ;
               strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"More than one occurrence of group Basic Service Used present within group");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
               gRejectedErrorNo++ ;
           }
      }
   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 10                         ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MTC")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MobileTerminatedCall")               ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Basic Service Used missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }


   if(NOT_NULL(mobileTerminatedCall->camelServiceUsed))
   {
      ReadCamelServiceUsed(mobileTerminatedCall->camelServiceUsed);
   }

   stMTC1 = mobileTerminatedCall;

   if((gRejectedErrorNo > 0) && (gFatalErrorCount == 0)&& (strcmp(gGenerateFilesFlg,"N")!=0))
   {
       gErrorCDRsCount = gErrorCDRsCount + 1 ;
       gErrorCDRsCharge = gErrorCDRsCharge + BCT.CHARGE + BCT.CAMEL_INVOCATION_FEE ;
       gErrorCDRsTax = gErrorCDRsTax + BCT.TAX_VALUE  ;
       gErrorCDRsDiscount = gErrorCDRsDiscount + BCT.DISCOUNT  ;
       gErrorCDRsDuration = gErrorCDRsDuration + BCT.CALL_DURATION ;
       gCDRErrorFlag = 1 ;

       for(ErrorCount=0; ErrorCount<gRejectedErrorNo; ErrorCount++)
       {
           ErrorReturnValue = SetBulkErrorDetails(gBulkErrorDetailsIndex, ErrorCount,10)   ;
           if(ErrorReturnValue == -1)
           {
              return -1;
           }
       }
   }
   gRejectedErrorNo = 0;

   /*
   printf("   IMEI :-%s-\n",BCT.IMEI);
   */

   return 0;
}


void  ReadMoBasicCallInformation(struct MoBasicCallInformation* basicCallInformation) 
{
   void *Pointer;
   int ErrorReturnValue = 0 ;
   int SetError = 0 ;
   int ReturnValue = 0;
   char TempNumtoChar [10]   ;
   int  lValidateFlag = 0    ;
   gDestinationFlag = 0 ;

   INIT_STR(stContext.BasicCallInformation) ;
   sprintf(stContext.BasicCallInformation,"%s;147:0:L",stContext.CallEventType) ;
   fnRemTrailSpaces(stContext.BasicCallInformation) ;

   if(NOT_NULL(basicCallInformation->chargeableSubscriber))
   {
       ReadChargeableSubscriber(basicCallInformation->chargeableSubscriber);
   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 30                               ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 147                          ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MoBasicCallInformation")                 ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.BasicCallInformation)   ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Chargeable Subscriber missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }

/* Added by Anitha for Decoding rapfileSequence number in MO Call */
if(ASNOCTS_PRESENT(&basicCallInformation->rapFileSequenceNumber))
      {
         BCT.RAPFILE_SEQUENCE_NUMBER = atol(basicCallInformation->rapFileSequenceNumber.octs);
         sprintf (TempNumtoChar,"%d",BCT.RAPFILE_SEQUENCE_NUMBER );
         ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
         if(ReturnValue != 0)
           {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 181             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RapFileSequenceNumber") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"181:0:L")   ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }

                   ReturnValue = 0 ;
            }


         if(BCT.RAPFILE_SEQUENCE_NUMBER > 99999)
           {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 21                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 181             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RapFileSequenceNumber") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"436:0:L;181:0:L")   ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                    }

                   ReturnValue = 0 ;
          }
     }





   if(NOT_NULL(basicCallInformation->destination))
   {
      gDestinationFlag  =  1 ;
      ReadDestination(basicCallInformation->destination);
   }

   if(NOT_NULL(basicCallInformation->callEventStartTimeStamp))
   {
      ReadCallEventStartTimeStamp(basicCallInformation->callEventStartTimeStamp);
   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 31                               ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 147                          ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MoBasicCallInformation")                 ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.BasicCallInformation)   ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Call Event Start Timestamp missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }


   if(NOT_NULL(basicCallInformation->totalCallEventDuration))
   {
       BCT.CALL_DURATION = * basicCallInformation->totalCallEventDuration;

       /* TotalCallEventDuration : Syntax Error Check */
       sprintf (TempNumtoChar,"%d", BCT.CALL_DURATION);
       ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
       if(ReturnValue != 0)
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 223             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalCallEventDuration") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicCallInformation,"223:0:L")   ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
               gRejectedErrorNo++ ;
           }

           ReturnValue = 0 ;
       }


       /* TotalCallEventDuration : Value Out of Range */

       if (BCT.CALL_DURATION < 0 )
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 223             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalCallEventDuration") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicCallInformation,"223:0:L")   ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
               gRejectedErrorNo++ ;
           }
           ReturnValue = 0 ;
       }
   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 32                               ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 147                          ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MoBasicCallInformation")                 ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.BasicCallInformation)   ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Total Call Event Duration missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }


  
/* Cause for Term --Tap3.12 */

if(NOT_NULL(basicCallInformation->causeForTerm))
   {
       BCT.CAUSE_FOR_TERMINATION = *basicCallInformation->causeForTerm;
 
      /* CauseForTerm : Syntax Error Check */
       sprintf (TempNumtoChar,"%d",BCT.CAUSE_FOR_TERMINATION );
       ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
       if(ReturnValue != 0)
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 58             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CauseForTermination") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicCallInformation,"58:0:L")   ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
               gRejectedErrorNo++ ;
          }
           ReturnValue = 0 ;
       }

  
       Pointer = NULL;
       Pointer = strstr("3:4:5",TempNumtoChar);
       if(Pointer == NULL)
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 58             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CauseForTermination") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicCallInformation,"58:0:L")        ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
               gRejectedErrorNo++ ;
           }
               ReturnValue = 0 ;
       }

   }
}


void ReadMtBasicCallInformation(struct MtBasicCallInformation* basicCallInformation)
{
   void *Pointer;
   int ErrorReturnValue = 0 ;
   int SetError = 0 ;
   int ReturnValue = 0;
   char TempNumtoChar [15]   ;
   int  lValidateFlag = 0    ;


   INIT_STR(stContext.BasicCallInformation) ;
   sprintf(stContext.BasicCallInformation,"%s;153:0:L",stContext.CallEventType) ;
   fnRemTrailSpaces(stContext.BasicCallInformation) ;


   if(NOT_NULL(basicCallInformation->chargeableSubscriber))
   {
      ReadChargeableSubscriber(basicCallInformation->chargeableSubscriber);
   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 153                        ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MTC")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MtBasicCallInformation")               ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.BasicCallInformation)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Chargeable Subscriber missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }
/* Added by Anitha for Decoding Rap file sequence number in MT Call */

 if(ASNOCTS_PRESENT(&basicCallInformation->rapFileSequenceNumber))
      {
         BCT.RAPFILE_SEQUENCE_NUMBER = atol(basicCallInformation->rapFileSequenceNumber.octs);
         sprintf (TempNumtoChar,"%d",BCT.RAPFILE_SEQUENCE_NUMBER );
         ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
         if(ReturnValue != 0)
           {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 181             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RapFileSequenceNumber") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"181:0:L")   ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }

                   ReturnValue = 0 ;
            }


         if(BCT.RAPFILE_SEQUENCE_NUMBER > 99999)
           {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 21                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 181             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RapFileSequenceNumber") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"436:0:L;181:0:L")   ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                    }

                   ReturnValue = 0 ;
          }
     }


   if(NOT_NULL(basicCallInformation->callOriginator))
   {
      ReadCallOriginator(basicCallInformation->callOriginator);

   }

   if(NOT_NULL(basicCallInformation->callEventStartTimeStamp))
   {
      ReadCallEventStartTimeStamp(basicCallInformation->callEventStartTimeStamp);
   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 153                        ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MTC")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MtBasicCallInformation")               ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.BasicCallInformation)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Call Event Start Timestamp missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }


   if(NOT_NULL(basicCallInformation->totalCallEventDuration))
   {
       BCT.CALL_DURATION = * basicCallInformation->totalCallEventDuration;

       /* TotalCallEventDuration : Syntax Error Check */

       sprintf (TempNumtoChar,"%d", BCT.CALL_DURATION);
       ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
       if(ReturnValue != 0)
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 223             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MTC");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalCallEventDuration") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicCallInformation,"223:0:L")   ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
               gRejectedErrorNo++ ;
           }

           ReturnValue = 0 ;
       }


       /* TotalCallEventDuration : Value Out of Range */

       if (BCT.CALL_DURATION < 0 )
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 223             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MTC");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalCallEventDuration") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicCallInformation,"223:0:L")   ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
               gRejectedErrorNo++ ;
           }
           ReturnValue = 0 ;
       }

   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 153                        ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MTC")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MtBasicCallInformation")               ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.BasicCallInformation)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Total Call Event Duration missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }


   /*Cause for Term -- TAP 3.12 */

	if(NOT_NULL(basicCallInformation->causeForTerm))
	   {
       		BCT.CAUSE_FOR_TERMINATION = *basicCallInformation->causeForTerm;
 
      /* CauseForTerm : Syntax Error Check */
	       sprintf (TempNumtoChar,"%d",BCT.CAUSE_FOR_TERMINATION );
      	       ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
      	       if(ReturnValue != 0)
       		{
                  REI.ERROR_CODE[gRejectedErrorNo]  = 10  ;
           	  REI.APPLICATION_TAG[gRejectedErrorNo] = 58   ;
                  strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")    ;
                  lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                  if(lValidateFlag == 0)
                  {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MTC");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CauseForTermination") ;
                  sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicCallInformation,"58:0:L")   ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
                  }
                  ReturnValue = 0 ;
                }

  
                Pointer = NULL;
                Pointer = strstr("3:4:5",TempNumtoChar);
                if(Pointer == NULL)
                {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 20   ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 58   ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")  ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MTC");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CauseForTermination") ;
                   sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicCallInformation,"58:0:L")        ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                   gRejectedErrorNo++ ;
                   }
                   ReturnValue = 0 ;
                }

          }

}

int  ReadGprsCall(struct GprsCall* gprsCall)
{
   int CICount=0;                       /* ChargeInformation Count */
   int ErrorReturnValue = 0 ;
   int SetError = 0 ;
   int ReturnValue = 0;
   int ErrorCount = 0;
   char TempNumtoChar [15]   ;
   int  lValidateFlag = 0    ;
   GprsServiceUsed *BSU;
   ChargeInformation *CI;
   unsigned char Imei[16];
   int CDRSgsnFlag = 0 ;
   int CDRGgsnFlag = 0 ;
   int CDRWLANFlag = 0 ;
   int i=0,j=0;
   int GprsRecordingEntityFlag = 0;

   gErrorNode = 14 ;

   INIT_STR(stContext.CallEventType) ;
   sprintf(stContext.CallEventType,"%s;14:0:L",stContext.CallEventDetails);
   fnRemTrailSpaces(stContext.CallEventType) ;


   BCT.CALL_TYPE = 2;
   strcpy(BCT.SERVICE_CODE,"005") ;

   if(NOT_NULL(gprsCall->gprsBasicCallInformation))
   {
      ReadGprsBasicCallInformation(gprsCall->gprsBasicCallInformation);
   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 14                         ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsCall")               ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group GPRS Basic Call Information missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }

   if((strcmp(gCheckCallAgeFlag,"Y") == 0) && (strcmp(g_CdrStartDate,BCT.CALL_DATE) > 0))
   {

      REI.ERROR_CODE[gRejectedErrorNo]  = 261            ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 14         ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS");
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsCall") ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)   ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Call older than allowed by BARG in 'Exceptional Situations' in BARG PRD BA.08");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CALL_DATE);
         gRejectedErrorNo++ ;
      }
   }


   if(NOT_NULL(gprsCall->gprsLocationInformation))
   {
      ReadGprsLocationInformation(gprsCall->gprsLocationInformation);
   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 14                         ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsCall")               ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group GPRS Location Information missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }


   /* Read Equipment Identifier */
   if(NOT_NULL(gprsCall->equipmentIdentifier))
   {
      if(gprsCall->equipmentIdentifier->choiceId == IMEIORESN_IMEI)
      {
         if(NOT_NULL(gprsCall->equipmentIdentifier->a.imei))
         {
            fnDconvhx(gprsCall->equipmentIdentifier->a.imei->octetLen,
                      gprsCall->equipmentIdentifier->a.imei->octs,Imei,'S');
            fnRemTrailSpaces(Imei);
            strcpy(BCT.IMEI,Imei);
         }
      }
   }

   /* Read GprsServiceUsed */
   if(NOT_NULL(gprsCall->gprsServiceUsed))
   {
      INIT_STR(stContext.GprsServiceUsed) ;
      sprintf(stContext.GprsServiceUsed,"%s;121:0:L",stContext.CallEventType);
      fnRemTrailSpaces(stContext.GprsServiceUsed) ;
    
      if(NOT_NULL(gprsCall->gprsServiceUsed->dataVolumeIncoming))
      {
         BCT.DATA_VOLUME_INCOMING = *gprsCall->gprsServiceUsed->dataVolumeIncoming;


         /* DataVolumeIncoming : Syntax Error Check */
         sprintf (TempNumtoChar,"%d", BCT.DATA_VOLUME_INCOMING);
         ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
         if(ReturnValue != 0)
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 250             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS/Content");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DataVolumeIncoming") ;
                 sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"250:0:L")   ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                 gRejectedErrorNo++ ;
             }
 
             ReturnValue = 0 ;
         }


         /* DataVolumeIncoming : Value Out of Range */

         if (BCT.DATA_VOLUME_INCOMING < 0 )
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 250             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS/Content");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DataVolumeIncoming") ;
                 sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"250:0:L")   ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0 ;
         }

      }
      else
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 33                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 121                        ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsServiceUsed")               ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.GprsServiceUsed)        ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Data Volume Incoming missing within group");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }


      if(NOT_NULL(gprsCall->gprsServiceUsed->dataVolumeOutgoing))
      {
         BCT.DATA_VOLUME_OUTGOING = *gprsCall->gprsServiceUsed->dataVolumeOutgoing;


         /* DataVolumeOutgoing : Syntax Error Check */
         sprintf (TempNumtoChar,"%d", BCT.DATA_VOLUME_OUTGOING);
         ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
         if(ReturnValue != 0)
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 251             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS/Content");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DataVolumeOutgoing") ;
                 sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"251:0:L")   ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0 ;
         }


         /* DataVolumeIncoming : Value Out of Range */

         if (BCT.DATA_VOLUME_OUTGOING < 0 )
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 251             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS/Content");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DataVolumeOutgoing") ;
                 sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"251:0:L")   ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0 ;
         }


      }
      else
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 34                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 121                        ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsServiceUsed")               ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.GprsServiceUsed)        ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Data Volume Outgoing missing within group");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }


      if(NOT_NULL(gprsCall->gprsServiceUsed->chargeInformationList))
      {
         FOR_EACH_LIST_ELMT(CI,gprsCall->gprsServiceUsed->chargeInformationList)
         {
            CICount = 0;

            ReadChargeInformationList(CI,CICount);

            CICount++;
            BCT.CHARGE_INFORMATION_COUNT = CICount;
         }


         if(((strcmp(BCT.SERVICE_CODE,"005") == 0) ||  (strcmp(BCT.SERVICE_CODE,"305") == 0)) && (BCT.CALL_TYPE_LEVEL1 != 100))
         {
       

             for(j=0;j<GPRS_REC_ENTITY_COUNT;j++)
             {
                GprsRecordingEntityFlag = 0 ;
                INIT_STR(TempNumtoChar) ;
                for(i=0;i<gRecEntityInfoCount;i++)
                {
                    if(GPRS_RECORDING_ENTITY_CODES[j] == NI.RecEntityInfo[i].RecEntityCode)
                    {
                        GprsRecordingEntityFlag = 1 ;
                         break;
                    }
                }

                sprintf (TempNumtoChar,"%d", GPRS_RECORDING_ENTITY_CODES[j]);

                if((GprsRecordingEntityFlag == 1) && (NI.RecEntityInfo[i].RecEntityType != 4) && (NI.RecEntityInfo[i].RecEntityType != 3) && (NI.RecEntityInfo[i].RecEntityType != 7) && (NI.RecEntityInfo[i].RecEntityType != 8))
                {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 12                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 184             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityCode") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;185:%d:L;184:0:L",stContext.GprsNetworkLocation,j+1)        ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range for a GPRS call (except for WLAN network usage), i.e. the Recording Entity Code refers to a recording entity of a type other than GGSN or SGSN");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }
                }

             }
        }

        if(((strcmp(BCT.SERVICE_CODE,"005") == 0)|| (strcmp(BCT.SERVICE_CODE,"305") == 0)) && (BCT.CALL_TYPE_LEVEL1 == 100))
        {
            if(GPRS_REC_ENTITY_COUNT > 1)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 35                             ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 118                         ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsNetworkLocation")               ;
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.GprsNetworkLocation);
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"For WLAN network usage, more than one Recording Entity Code present within group");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                    gRejectedErrorNo++ ;
                }
            }
                 
            CDRWLANFlag = 0;


            for(j=0;j<GPRS_REC_ENTITY_COUNT;j++)
            {
                for(i=0;i<gRecEntityInfoCount;i++)
                {
                   if((GPRS_RECORDING_ENTITY_CODES[j] == NI.RecEntityInfo[i].RecEntityCode) && (NI.RecEntityInfo[i].RecEntityType == 6))
                   {
                      CDRWLANFlag =1 ;
                      break ;
                   }
                }
                
                if(CDRWLANFlag == 1)
                {
                    break ;
                }
            }

            if(CDRWLANFlag == 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 34                             ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 118                         ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsNetworkLocation")               ;
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.GprsNetworkLocation);
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"For WLAN network usage, no Recording Entity Code of type WLAN billing information recording entity present within group");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                    gRejectedErrorNo++ ;
                }
            }

             for(j=0;j<GPRS_REC_ENTITY_COUNT;j++)
             {
                GprsRecordingEntityFlag = 0 ;
                INIT_STR(TempNumtoChar) ;
                for(i=0;i<gRecEntityInfoCount;i++)
                {
                    if(GPRS_RECORDING_ENTITY_CODES[j] == NI.RecEntityInfo[i].RecEntityCode)
                    {
                        GprsRecordingEntityFlag = 1 ;
                        break;
                    }
                }

                sprintf (TempNumtoChar,"%d", GPRS_RECORDING_ENTITY_CODES[j]);

                if((GprsRecordingEntityFlag == 1) && (NI.RecEntityInfo[i].RecEntityType != 6))
                {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 13                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 184             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityCode") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;185:%d:L;184:0:L",stContext.GprsNetworkLocation,j+1)        ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range for a GPRS call (only for WLAN network usage), i.e. the Recording Entity Code refers to a recording entity of a type other than WLAN billing information recording entity");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }
                }
             }
        } 

     }
     else
     {
          REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 121                        ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsServiceUsed")               ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.GprsServiceUsed)        ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Charge Information missing within group");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
     }

   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 34                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 14                         ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GprsCall")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GPRS")               ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group GPRS Service Used missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }


   /* Read CamelServiceUsed */
   if(NOT_NULL(gprsCall->camelServiceUsed))
   {
      ReadCamelServiceUsed(gprsCall->camelServiceUsed);
   }

   stGC = gprsCall ;

   if((gRejectedErrorNo > 0) && (gFatalErrorCount == 0) && (strcmp(gGenerateFilesFlg,"N")!=0))
   {
       gErrorCDRsCount = gErrorCDRsCount + 1 ;
       gErrorCDRsCharge = gErrorCDRsCharge + BCT.CHARGE + BCT.CAMEL_INVOCATION_FEE ;
       gErrorCDRsTax = gErrorCDRsTax + BCT.TAX_VALUE  ;
       gErrorCDRsDiscount = gErrorCDRsDiscount + BCT.DISCOUNT  ;
       gErrorCDRsDuration = gErrorCDRsDuration + BCT.CALL_DURATION ;
       gErrorCDRsIncVolume = gErrorCDRsIncVolume + BCT.DATA_VOLUME_INCOMING ;
       gErrorCDRsOutVolume = gErrorCDRsOutVolume + BCT.DATA_VOLUME_OUTGOING ;
       gCDRErrorFlag = 1 ;

       for(ErrorCount=0; ErrorCount<gRejectedErrorNo; ErrorCount++)
       {
           ErrorReturnValue = SetBulkErrorDetails(gBulkErrorDetailsIndex, ErrorCount,14)   ;
           if(ErrorReturnValue == -1)
           {
              return -1;
           }
       }
   }
   gRejectedErrorNo = 0;

   return 0;
}

void ReadGprsBasicCallInformation(struct GprsBasicCallInformation* basicCallInformation)
{
  void *Pointer;
   char temp[20];
   int ErrorReturnValue = 0 ;
   int ReturnValue = 0;
   int SetError = 0;
   char TempNumtoChar [10]   ;
   int  lValidateFlag = 0    ;

   INIT_STR(stContext.BasicCallInformation) ;
   sprintf(stContext.BasicCallInformation,"%s;114:0:L",stContext.CallEventType) ;
   fnRemTrailSpaces(stContext.BasicCallInformation) ;


   if(NOT_NULL(basicCallInformation->gprsChargeableSubscriber))
   {
       ReadGprsChargeableSubscriber(basicCallInformation->gprsChargeableSubscriber);
   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 114                         ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsBasicCallInformation")               ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.BasicCallInformation)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group GPRS Chargeable Subscriber missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }

 /* Added bu Anitha for decoding Rap Sequence number for GPRS Calls */
   if(ASNOCTS_PRESENT(&basicCallInformation->rapFileSequenceNumber))
      {
         BCT.RAPFILE_SEQUENCE_NUMBER = atol(basicCallInformation->rapFileSequenceNumber.octs);
         sprintf (TempNumtoChar,"%d",BCT.RAPFILE_SEQUENCE_NUMBER );
         ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
         if(ReturnValue != 0)
           {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 181             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RapFileSequenceNumber") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"181:0:L")   ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }

                   ReturnValue = 0 ;
            }


         if(BCT.RAPFILE_SEQUENCE_NUMBER > 99999)
           {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 21                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 181             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RapFileSequenceNumber") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"436:0:L;181:0:L")   ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                    }

                   ReturnValue = 0 ;
          }
     }




   if(NOT_NULL(basicCallInformation->gprsDestination))
   {

      INIT_STR(stContext.GprsDestination);
      sprintf(stContext.GprsDestination,"%s;116:0:L",stContext.BasicCallInformation)        ;

      if(ASNOCTS_PRESENT(&basicCallInformation->gprsDestination->accessPointNameNI))
      {
          strcpy(BCT.APN_NI,basicCallInformation->gprsDestination->accessPointNameNI.octs);

          ReturnValue = fnCheckSyntax(BCT.APN_NI,"AS") ;
          if(ReturnValue != 0)
          {
              REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 261             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"AccessPointNameNI");
                  sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.GprsDestination,"261:0:L");
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error where group GPRS Destination occurs within group GPRS Basic Call Information");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.APN_NI);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
          }

      }
      else
      {
         REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
         REI.APPLICATION_TAG[gRejectedErrorNo] = 116                         ;
         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
         if(lValidateFlag == 0)
         {
             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsDestination")               ;
             strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.GprsDestination);
             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Access Point Name NI missing within group");
             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
             gRejectedErrorNo++ ;
         }
      }


      if(ASNOCTS_PRESENT(&basicCallInformation->gprsDestination->accessPointNameOI))
      {
          strcpy(BCT.APN_OI,basicCallInformation->gprsDestination->accessPointNameOI.octs);

          ReturnValue = fnCheckSyntax(BCT.APN_OI,"AS") ;
          if(ReturnValue != 0)
          {
              REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 262             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"AccessPointNameOI");
                  sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.GprsDestination,"262:0:L");
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error where group GPRS Destination occurs within group GPRS Basic Call Information");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.APN_OI);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
          }


      }
   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 114                         ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsBasicCallInformation")               ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.BasicCallInformation)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group GPRS Destination missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }


   if(NOT_NULL(basicCallInformation->callEventStartTimeStamp))
   {
       ReadCallEventStartTimeStamp(basicCallInformation->callEventStartTimeStamp);
   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 33                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 114                         ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsBasicCallInformation")               ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.BasicCallInformation)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Call Event Start Timestamp missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }


   if(NOT_NULL(basicCallInformation->totalCallEventDuration))
   {
      BCT.CALL_DURATION = *basicCallInformation->totalCallEventDuration;


       /* TotalCallEventDuration : Syntax Error Check */
       sprintf (TempNumtoChar,"%d", BCT.CALL_DURATION);
       ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
       if(ReturnValue != 0)
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 223             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalCallEventDuration") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicCallInformation,"223:0:L")   ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
               gRejectedErrorNo++ ;
           }

           ReturnValue = 0 ;
       }


       /* TotalCallEventDuration : Value Out of Range */

       if (BCT.CALL_DURATION < 0 )
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 223             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalCallEventDuration") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicCallInformation,"223:0:L")   ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
               gRejectedErrorNo++ ;
           }
           ReturnValue = 0 ;
       }

   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 34                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 114                         ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsBasicCallInformation")               ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.BasicCallInformation)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Total Call Event Duration missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }

   /* Cause For Term -  tap3.12 */

    if(NOT_NULL(basicCallInformation->causeForTerm))
    {
          BCT.CAUSE_FOR_TERMINATION = *basicCallInformation->causeForTerm;
 
 
      /* CauseForTerm : Syntax Error Check */
         sprintf (TempNumtoChar,"%d",BCT.CAUSE_FOR_TERMINATION );
         ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;

         if(ReturnValue != 0)
         {
            REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
            REI.APPLICATION_TAG[gRejectedErrorNo] = 58             ;
            strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
            lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
            if(lValidateFlag == 0)
            {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CauseForTermination") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicCallInformation,"58:0:L")   ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
               gRejectedErrorNo++ ;
           }
              ReturnValue = 0 ;
         }

   
            Pointer = NULL;
		   char CauseForTerm[3];
           sprintf(CauseForTerm,"%s%s",":",TempNumtoChar);
            Pointer = strstr(":4:5:20:21:24",CauseForTerm);
            if(Pointer == NULL)
            {
               REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 58             ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CauseForTermination") ;
                   sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicCallInformation,"58:0:L")        ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                   gRejectedErrorNo++ ;
               }
                   ReturnValue = 0 ;
            }
       }

   if(ASNOCTS_PRESENT(&basicCallInformation->partialTypeIndicator))
   {
      strcpy(BCT.PARTIAL_TYPE_INDICATOR,basicCallInformation->partialTypeIndicator.octs);

      /* PTI : Syntax Error Check */
       ReturnValue = fnCheckSyntax(BCT.PARTIAL_TYPE_INDICATOR,"AL") ;
       if(ReturnValue != 0)
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 166             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"PartialTypeIndicator") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicCallInformation,"166:0:L")   ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.PARTIAL_TYPE_INDICATOR);
               gRejectedErrorNo++ ;
           }

           ReturnValue = 0 ;
       }


        if((strcmp(BCT.PARTIAL_TYPE_INDICATOR,"F") != 0) && (strcmp(BCT.PARTIAL_TYPE_INDICATOR,"I") != 0) && (strcmp(BCT.PARTIAL_TYPE_INDICATOR, "L") != 0))
        {
           REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 166             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"PartialTypeIndicator") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicCallInformation,"166:0:L")   ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.PARTIAL_TYPE_INDICATOR);
               gRejectedErrorNo++ ;
           }

           ReturnValue = 0 ;

        }

   }


   if(NOT_NULL(basicCallInformation->chargingId))
   {
       BCT.CHARGING_ID = *basicCallInformation->chargingId;
       sprintf(temp,"%u",*basicCallInformation->chargingId);
	

       ReturnValue = fnCheckSyntax(temp,"DI") ;
       if(ReturnValue != 0)
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 72             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargingId") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicCallInformation,"72:0:L")   ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],temp);
               gRejectedErrorNo++ ;
           }

           ReturnValue = 0 ;
       }
	 

       if ((BCT.CHARGING_ID < 0) || (BCT.CHARGING_ID > 4294967295UL))
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 72             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargingId") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicCallInformation,"72:0:L")   ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],temp);
               gRejectedErrorNo++ ;
           }

           ReturnValue = 0 ;


       }  

   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 35                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 114                         ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsBasicCallInformation")               ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.BasicCallInformation)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Charging Id missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }


}

void ReadGprsChargeableSubscriber(struct GprsChargeableSubscriber *gprsSubscriber)
{
   unsigned char Imsi[16];      /* AddressStringDigits */
   unsigned char Msisdn[17];    /* AddressStringDigits */
   int ErrorReturnValue = 0 ;
   int ReturnValue = 0;
   int SetError = 0;
   int  lValidateFlag = 0    ;
   unsigned char Temp_Imsi[26];      /* AddressStringDigits */


   INIT_STR(stContext.ChargeableSubscriber) ;
   sprintf(stContext.ChargeableSubscriber,"%s;115:0:L;427:0:L",stContext.BasicCallInformation) ;
   fnRemTrailSpaces(stContext.ChargeableSubscriber) ;


   if(gprsSubscriber->chargeableSubscriber->choiceId == CHARGEABLESUBSCRIBER_SIMCHARGEABLESUBSCRIBER)
   {
      if(NOT_NULL(gprsSubscriber->chargeableSubscriber->a.simChargeableSubscriber))
      {
         if(ASNOCTS_PRESENT(&gprsSubscriber->chargeableSubscriber->a.simChargeableSubscriber->imsi))
         {
            fnDconvhx(gprsSubscriber->chargeableSubscriber->a.simChargeableSubscriber->imsi.octetLen,
                      gprsSubscriber->chargeableSubscriber->a.simChargeableSubscriber->imsi.octs,
                      Imsi,
                      'S');
            Imsi[15]='\0';
            fnRemTrailSpaces(Imsi);
            BCT.IMSI = atof(Imsi);


            ReturnValue = fnCheckSyntax(Imsi,"DI") ;
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 129             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Imsi") ;
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeableSubscriber,"199:0:L;129:0:L")   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],Imsi);
                    gRejectedErrorNo++ ;
                }

                ReturnValue = 0 ;
            }

            fnDconvhx(gprsSubscriber->chargeableSubscriber->a.simChargeableSubscriber->imsi.octetLen,
                      gprsSubscriber->chargeableSubscriber->a.simChargeableSubscriber->imsi.octs,
                      Temp_Imsi,
                      'S');
            fnRemTrailSpaces(Temp_Imsi);
            Temp_Imsi[strlen(Temp_Imsi)]='\0';


            if(strlen(Temp_Imsi) > 15)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 129             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Imsi") ;
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeableSubscriber,"199:0:L;129:0:L")   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],Temp_Imsi);
                    gRejectedErrorNo++ ;
                }

                ReturnValue = 0 ;
            }

            /* Validate the IMSI Prefix of the CDR */
            ReturnValue = fnImsiPrfxCheck(BCT.IMSI);

            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 200                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 129             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Imsi") ;
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeableSubscriber,"199:0:L;129:0:L")   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"First characters are different from home operators MCC + MNC, or not as bilaterally agreed");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],Imsi);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }

         }

         if(ASNOCTS_PRESENT(&gprsSubscriber->chargeableSubscriber->a.simChargeableSubscriber->msisdn))
         {
            fnDconvhx(gprsSubscriber->chargeableSubscriber->a.simChargeableSubscriber->msisdn.octetLen,
                      gprsSubscriber->chargeableSubscriber->a.simChargeableSubscriber->msisdn.octs,
                      Msisdn,
                      'S');
            fnRemTrailSpaces(Msisdn);
            strcpy(BCT.MSISDN,Msisdn);

            ReturnValue = fnCountryCodeCheck(BCT.MSISDN) ;
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  =   23                            ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 152                          ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/SS/GPRS")  ;
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Msisdn")                 ;
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeableSubscriber,"199:0:L;152:0:L")   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Number not represented in international format and MSISDN expected in accordance with roaming agreement");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.MSISDN);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0;
            }

         }
/*         else
         {
            REI.ERROR_CODE[gRejectedErrorNo]  = 32                               ;
            REI.APPLICATION_TAG[gRejectedErrorNo] = 427                          ;
            strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
            lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
            if(lValidateFlag == 0)
            {
                strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/SS/GPRS")         ;
                strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeableSubscriber") ;
                strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargeableSubscriber)   ;
                fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"MSISDN missing within group but expected in accordance with roaming agreement");
                strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                gRejectedErrorNo++ ;
            }
        }
*/
      }
   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 115                         ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsChargeableSubscriber")               ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargeableSubscriber)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Item Chargeable Subscriber missing within group and the GPRS Call is not representing a WLAN network usage");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }



   if(ASNOCTS_PRESENT(&gprsSubscriber->pdpAddress))
   {
      strcpy(BCT.PDP_ADDRESS,gprsSubscriber->pdpAddress.octs);
      fnRemTrailSpaces(BCT.PDP_ADDRESS);
   }

   if(ASNOCTS_PRESENT(&gprsSubscriber->networkAccessIdentifier)) 
   {
      strcpy(BCT.NETWORK_ACCESS_IDENTIFER,gprsSubscriber->networkAccessIdentifier.octs);
   }
   
}

void ReadGprsLocationInformation(struct GprsLocationInformation* locationInformation)
{
   RecEntityCode *REC;
   int i=0,j=0;
   GPRS_REC_ENTITY_COUNT = 0;
   int ErrorReturnValue = 0;
   int ReturnValue = 0;
   char TempNumtoChar [10]   ;
   int GgsnCount;
   int SgsnCount;
   int PgwCount;
   int SgwCount;
   int GprsRecordingEntityFlag = 0 ;
   int  lValidateFlag = 0    ;

   INIT_STR(stContext.LocationInformation);
   sprintf(stContext.LocationInformation,"%s;117:0:L",stContext.CallEventType) ;
   fnRemTrailSpaces(stContext.LocationInformation) ;

  
   if(NOT_NULL(locationInformation->gprsNetworkLocation))
   {
       INIT_STR(stContext.GprsNetworkLocation);
       sprintf(stContext.GprsNetworkLocation,"%s;118:0:L",stContext.LocationInformation) ;
       fnRemTrailSpaces(stContext.GprsNetworkLocation) ;
     

      if(NOT_NULL(locationInformation->gprsNetworkLocation->recEntity))
      {
         FOR_EACH_LIST_ELMT(REC,locationInformation->gprsNetworkLocation->recEntity)
         {
            GPRS_RECORDING_ENTITY_CODES[i] = *REC;
            i++;
         }
      }

      GPRS_REC_ENTITY_COUNT = i;

      for(j=0;j<GPRS_REC_ENTITY_COUNT;j++)
      {
          /* RecEntityCode : Syntax Error Check */
          sprintf (TempNumtoChar,"%d", GPRS_RECORDING_ENTITY_CODES[j]);
          ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
          if(ReturnValue != 0)
          {
              REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 184             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityCode") ;
                  sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;185:%d:L;184:0:L",stContext.GprsNetworkLocation,j+1)        ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
          }
      }


      for(j=0;j<GPRS_REC_ENTITY_COUNT;j++)
      {
          GprsRecordingEntityFlag = 0 ;
          INIT_STR(TempNumtoChar) ;
          for(i=0;i<gRecEntityInfoCount;i++)
          {
             if(GPRS_RECORDING_ENTITY_CODES[j] == NI.RecEntityInfo[i].RecEntityCode)
             {
                   GprsRecordingEntityFlag = 1 ;
                   break;
             }
          }

          sprintf (TempNumtoChar,"%d", GPRS_RECORDING_ENTITY_CODES[j]);

          if(GprsRecordingEntityFlag == 0)
          {
             REI.ERROR_CODE[gRejectedErrorNo]  = 100                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 184             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/SS/SCU/GPRS/LCS");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityCode") ;
                 sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;185:%d:L;184:0:L",stContext.GprsNetworkLocation,j+1)        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Specified recording entity code not defined in the Recording Entity Information");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0 ;
          }
      }

      GgsnCount = 0 ;
      PgwCount  = 0 ;
	  SgwCount  = 0;
	  SgsnCount = 0;


      for(j=0;j<GPRS_REC_ENTITY_COUNT;j++)
      {
          for(i=0;i<gRecEntityInfoCount;i++)
          {
              if((GPRS_RECORDING_ENTITY_CODES[j] == NI.RecEntityInfo[i].RecEntityCode) && (NI.RecEntityInfo[i].RecEntityType == 3))
              {
                  GgsnCount++ ;
              }
			 
			 else if ((GPRS_RECORDING_ENTITY_CODES[j] == NI.RecEntityInfo[i].RecEntityCode) && (NI.RecEntityInfo[i].RecEntityType == 4))
              {
                  SgsnCount++ ;
              }

             else if((GPRS_RECORDING_ENTITY_CODES[j] == NI.RecEntityInfo[i].RecEntityCode) && (NI.RecEntityInfo[i].RecEntityType == 7))
              { 
			      strcpy(BCT.SERVICE_CODE,"305");
                  PgwCount++ ;
              }

			     else if((GPRS_RECORDING_ENTITY_CODES[j] == NI.RecEntityInfo[i].RecEntityCode) && (NI.RecEntityInfo[i].RecEntityType == 8))
               {
				strcpy(BCT.SERVICE_CODE,"305"); // Added by Imam for the ghana specific LTE Tapin cdrs 
			       SgwCount++ ;
              }
          }
      }

      if(GgsnCount > 1)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 118                         ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsNetworkLocation")               ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.GprsNetworkLocation);
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"More than one Recording Entity Code is of type GGSN present within group");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }

    if  (PgwCount > 1)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 39                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 118                         ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsNetworkLocation")               ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.GprsNetworkLocation);
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"More than one Recording Entity Code is of type PGW present within group");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }

	
 
   if ((GgsnCount == 1)&&(PgwCount == 1))
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 40                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 118                         ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsNetworkLocation")               ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.GprsNetworkLocation);
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Recording Entity Codes of type GGSN and P-GW present within group.");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }


	  

if (( GgsnCount == 1 ) && (SgwCount == 1))
     {
          REI.ERROR_CODE[gRejectedErrorNo]  = 41                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 118                         ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsNetworkLocation")               ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.GprsNetworkLocation);
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Recording Entity Codes of type GGSN and S-GW present within group..");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }

   if (( GgsnCount == 0) &&(PgwCount == 0))
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 118                         ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsNetworkLocation")               ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.GprsNetworkLocation);
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"No Recording Entity Code of type GGSN and no Recording Entity Code of type P-GW present within group");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }
   if (( SgsnCount == 0) &&(SgwCount == 0))
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 33                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 118                         ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsNetworkLocation")               ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.GprsNetworkLocation);
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"No Recording Entity Code of type SGSN and no Recording Entity Code of type S-GW present within group");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }


   
      if(NOT_NULL(locationInformation->gprsNetworkLocation->locationArea))
      {
         BCT.LOCATION_AREA = *locationInformation->gprsNetworkLocation->locationArea;
      }

      if(NOT_NULL(locationInformation->gprsNetworkLocation->cellId))
      {
         BCT.CELLID = *locationInformation->gprsNetworkLocation->cellId;
      }
   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 138                         ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GprsLocationInformation")               ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.LocationInformation)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group GPRS Network Location missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }


   if(NOT_NULL(locationInformation->geographicalLocation))
   {
      if(ASNOCTS_PRESENT(&locationInformation->geographicalLocation->servingLocationDescription))
      {
         strcpy(BCT.SERVING_LOCATION_DESC,locationInformation->geographicalLocation->servingLocationDescription.octs);
      }
   }


}

void  ReadChargeableSubscriber(struct ChargeableSubscriber *chargeableSubscriber)
{
   unsigned char Imsi[16];	/* AddressStringDigits */
   unsigned char Msisdn[17];	/* AddressStringDigits */
   int ErrorReturnValue = 0;
   int ReturnValue =0;
   int  lValidateFlag = 0    ;

   unsigned char Temp_Imsi[16];	/* AddressStringDigits */

   INIT_STR(stContext.ChargeableSubscriber) ;
   sprintf(stContext.ChargeableSubscriber,"%s;427:0:L",stContext.BasicCallInformation) ;
   fnRemTrailSpaces(stContext.ChargeableSubscriber) ;

   if(chargeableSubscriber->choiceId == CHARGEABLESUBSCRIBER_SIMCHARGEABLESUBSCRIBER)
   {
      if(NOT_NULL(chargeableSubscriber->a.simChargeableSubscriber))
      {
         if(ASNOCTS_PRESENT(&chargeableSubscriber->a.simChargeableSubscriber->imsi))
         {
            fnDconvhx(chargeableSubscriber->a.simChargeableSubscriber->imsi.octetLen,
                      chargeableSubscriber->a.simChargeableSubscriber->imsi.octs,
                      Imsi,
                      'S');
            Imsi[15]='\0';
            fnRemTrailSpaces(Imsi);
            BCT.IMSI = atof(Imsi);

            ReturnValue = fnCheckSyntax(Imsi,"DI") ;
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 129             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Imsi") ;
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeableSubscriber,"199:0:L;129:0:L")   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],Imsi);
                    gRejectedErrorNo++ ;
                }

                ReturnValue = 0 ;
            }

            fnDconvhx(chargeableSubscriber->a.simChargeableSubscriber->imsi.octetLen,
                      chargeableSubscriber->a.simChargeableSubscriber->imsi.octs,
                      Temp_Imsi,
                      'S');
            fnRemTrailSpaces(Temp_Imsi);
            Temp_Imsi[strlen(Temp_Imsi)]='\0';


            if(strlen(Temp_Imsi) > 15)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 129             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Imsi") ;
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeableSubscriber,"199:0:L;129:0:L")   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],Temp_Imsi);
                    gRejectedErrorNo++ ;
                }

                ReturnValue = 0 ;
            }

            /* Validate the IMSI Prefix of the CDR */
            ReturnValue = fnImsiPrfxCheck(BCT.IMSI);

            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 200                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 129             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Imsi") ;
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeableSubscriber,"199:0:L;129:0:L")   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"First characters are different from home operators MCC + MNC, or not as bilaterally agreed");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],Imsi);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }

         }

         if(ASNOCTS_PRESENT(&chargeableSubscriber->a.simChargeableSubscriber->msisdn))
         {
            fnDconvhx(chargeableSubscriber->a.simChargeableSubscriber->msisdn.octetLen,
                      chargeableSubscriber->a.simChargeableSubscriber->msisdn.octs,
                      Msisdn,
                      'S');
            fnRemTrailSpaces(Msisdn);
            strcpy(BCT.MSISDN,Msisdn);

            ReturnValue = fnCountryCodeCheck(BCT.MSISDN) ;
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  =   23                            ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 152                          ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/SS/GPRS")  ;
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Msisdn")                 ;
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeableSubscriber,"199:0:L;152:0:L")   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Number not represented in international format and MSISDN expected in accordance with roaming agreement");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.MSISDN);
                    gRejectedErrorNo++ ;
                    ReturnValue = 0;
                }
            }

         }
   /*      else
         {
            REI.ERROR_CODE[gRejectedErrorNo]  = 32                               ;
            REI.APPLICATION_TAG[gRejectedErrorNo] = 427                          ;
            strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
            lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
            if(lValidateFlag == 0)
            {
                strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/SS/GPRS")         ;
                strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeableSubscriber") ;
                strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargeableSubscriber)   ;
                fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"MSISDN missing within group but expected in accordance with roaming agreement");
                strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                gRejectedErrorNo++ ;
            }
         }
 */
      }
   }

   /*
   printf("ChargeableSubscriber Details:\n");
   printf("   IMSI   :-%f-\n",BCT.IMSI);
   printf("   MSISDN :-%s-\n",BCT.MSISDN);
   */
}

void  ReadDestination(struct Destination* destination)
{
   unsigned char CalledNumber[87];  /* AddressStringDigits */
   int ReturnValue = 0;
   int ErrorReturnValue = 0 ;
   int  lValidateFlag = 0    ;
   gCalledNumberFlag = 0 ;
   gDestNumberFlag = 0 ;

   INIT_STR(stContext.Destination) ;
   sprintf(stContext.Destination,"%s;89:0:L",stContext.BasicCallInformation) ;
   fnRemTrailSpaces(stContext.Destination) ;

   if(ASNOCTS_PRESENT(&destination->calledNumber))
   {
      fnDconvhx(destination->calledNumber.octetLen,destination->calledNumber.octs,CalledNumber,'S');
      fnRemTrailSpaces(CalledNumber);

      gCalledNumberFlag = 1 ;

      strcpy(BCT.CALLED_CALLING_NUMBER,CalledNumber);
   }

   if(ASNOCTS_PRESENT(&destination->dialledDigits))
   {
      strcpy(BCT.DIALLED_DIGITS,destination->dialledDigits.octs);
      fnRemTrailSpaces(BCT.DIALLED_DIGITS);

      gDestNumberFlag = 1 ;

      /* DialledDigits : Syntax Error Check */
      ReturnValue = fnCheckDialNumSyntax(BCT.DIALLED_DIGITS,"DI") ;
      if(ReturnValue != 0)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 279             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DialledDigits") ;
              sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.Destination,"279:0:L")   ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.DIALLED_DIGITS);
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
      }

   }

   if(ASNOCTS_PRESENT(&destination->calledPlace))
   {
      strcpy(BCT.CALLED_PLACE,destination->calledPlace.octs);
      fnRemTrailSpaces(BCT.CALLED_PLACE);
   }

   if(ASNOCTS_PRESENT(&destination->calledRegion))
   {
      strcpy(BCT.CALLED_REGION,destination->calledRegion.octs);
      fnRemTrailSpaces(BCT.CALLED_REGION);
   }

   /* SMSDestinationNumber is available in case of SMS Originating Call */
   if(ASNOCTS_PRESENT(&destination->sMSDestinationNumber))
   {
      strcpy(BCT.DIALLED_DIGITS,destination->sMSDestinationNumber.octs);
      fnRemTrailSpaces(BCT.DIALLED_DIGITS);

      /* SMSDestination Number : Syntax Error Check */
      ReturnValue = fnCheckDialNumSyntax(BCT.DIALLED_DIGITS,"DI") ;
      if(ReturnValue != 0)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 419             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SmsDestinationNumber") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.Destination,"419:0:L")   ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.DIALLED_DIGITS);
               gRejectedErrorNo++ ;
          }

          ReturnValue = 0 ;
      }
   }

   /*
   printf("Destination Details:\n");
   printf("   CalledNumber   :-%s-\n",BCT.CALLED_CALLING_NUMBER);
   printf("  DialledDigits   :-%s-\n",BCT.DIALLED_DIGITS);
   printf("    CalledPlace   :-%s-\n",BCT.CALLED_PLACE);
   printf("   CalledRegion   :-%s-\n",BCT.CALLED_REGION);
   */
}

void ReadCallOriginator(struct CallOriginator* callOriginator)
{
   unsigned char CallingNumber[87];  /* AddressStringDigits */
   int  lValidateFlag = 0    ;

   INIT_STR(stContext.CallOriginator) ;
   sprintf(stContext.CallOriginator,"%s;41:0:L",stContext.BasicCallInformation) ;
   fnRemTrailSpaces(stContext.CallOriginator) ;


   if(ASNOCTS_PRESENT(&callOriginator->callingNumber))
   {
      fnDconvhx(callOriginator->callingNumber.octetLen,callOriginator->callingNumber.octs,CallingNumber,'S');
      strcpy(BCT.CALLED_CALLING_NUMBER,CallingNumber);
   }

   if(NOT_NULL(callOriginator->clirIndicator))
   {
      BCT.CLIR_INDICATOR = *callOriginator->clirIndicator;
      if((BCT.CLIR_INDICATOR != 0) && (BCT.CLIR_INDICATOR !=1))
      {
          BCT.CLIR_INDICATOR = 0;
      }
   }

   /* SMSOriginator is available in case of SMS Terminating Call and indicates the Originator of SMS */
   if(ASNOCTS_PRESENT(&callOriginator->sMSOriginator))
   {
      strcpy(BCT.DIALLED_DIGITS,callOriginator->sMSOriginator.octs);
   }

   /*
   printf("CallOriginator Details:\n");
   printf("   CalledNumber   :-%s-\n",BCT.CALLED_CALLING_NUMBER);
   printf("  DialledDigits   :-%s-\n",BCT.DIALLED_DIGITS);
   printf("  ClirIndicator   :-%d-\n",BCT.CLIR_INDICATOR);
   */
}

void ReadCallEventStartTimeStamp(CallEventStartTimeStamp *callEventStartTimeStamp)
{
   int ErrorReturnValue = 0;
   int ReturnValue = 0;
   char TempNumtoChar [10]   ;
   int  k=0;
   int  CDRUtcOffsetCode=0 ;
   int  lValidateFlag = 0    ;

   INIT_STR(stContext.CallEventStartTimeStamp) ;
   sprintf(stContext.CallEventStartTimeStamp,"%s;44:0:L",stContext.BasicCallInformation) ;
   fnRemTrailSpaces(stContext.CallEventStartTimeStamp) ;

   if(ASNOCTS_PRESENT(&callEventStartTimeStamp->localTimeStamp))
   {
      strcpy(BCT.CALL_DATE,callEventStartTimeStamp->localTimeStamp.octs);
      fnRemTrailSpaces(BCT.CALL_DATE) ;

      /* CallEventStartTimeStamp : Syntax Error Check */
      ReturnValue = fnCheckSyntax(BCT.CALL_DATE,"DI") ;
      if(ReturnValue != 0)
      {
         REI.ERROR_CODE[gRejectedErrorNo]  = 10                   ;
         REI.APPLICATION_TAG[gRejectedErrorNo] = 44               ;
         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
         if(lValidateFlag == 0)
         {
             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallEventStartTimeStamp") ;
             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventStartTimeStamp,"16:0:L")   ;
             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CALL_DATE);
             gRejectedErrorNo++ ;
         }

         ReturnValue = 0 ;
      }

      /* CallEventStartTimeStamp : Value Out of Range Check */
      ReturnValue = fnDateRangeCheck(BCT.CALL_DATE);
      if(ReturnValue != 0)
      {
         REI.ERROR_CODE[gRejectedErrorNo]  = 20             ;
         REI.APPLICATION_TAG[gRejectedErrorNo] = 44         ;
         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")  ;
         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
         if(lValidateFlag == 0)
         {
             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallEventStartTimeStamp") ;
             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventStartTimeStamp,"16:0:L")   ;
             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CALL_DATE);
             gRejectedErrorNo++ ;
         }

         ReturnValue = 0 ;
      }

   }

   if(NOT_NULL(callEventStartTimeStamp->utcTimeOffsetCode))
   {
      BCT.UTC_OFFSET_CODE = *callEventStartTimeStamp->utcTimeOffsetCode;


      /* UtcTimeOffsetCode : Syntax Error Check */
      sprintf (TempNumtoChar,"%d", BCT.UTC_OFFSET_CODE);
      ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
      if(ReturnValue != 0)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 232             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"UtcTimeOffsetCode") ;
              sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventStartTimeStamp,"232:0:L")   ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
      }

      CDRUtcOffsetCode = 0;

      for(k=0; k<gUTCOffsetCount; k++)
      {
          if(BCT.UTC_OFFSET_CODE == NI.UtcTimeOffsetInfo[k].UtcTimeOffsetCode)
          {
              CDRUtcOffsetCode = 1;
              break;
          }
      }

      if(CDRUtcOffsetCode==0)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 100                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 232             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"UtcTimeOffsetCode") ;
              sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventStartTimeStamp,"232:0:L")   ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Specified UTC Time Offset Code not defined in group UTC Time Offset Information");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
      }


   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 30                  ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 44              ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallEventStartTimeStamp") ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventStartTimeStamp)   ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory associated item UTC Time Offset Code missing");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }

      ReturnValue = 0 ;
   }


   /*
   printf("CallEventTime Details:\n");
   printf("   CallDate :-%s-\n",BCT.CALL_DATE);
   printf("    UTCCode :-%d-\n",BCT.UTC_OFFSET_CODE);  
   */

}

void ReadLocationInformation(struct LocationInformation* locationInformation)
{
   unsigned char CallReference[120];	/* AsnOcts 6Octs */
   char octetcr[41],octetCall[8],strcr[21] ;
   long k=0;
   int ErrorReturnValue = 0;
   int ReturnValue = 0;
   char TempNumtoChar [10]   ;
   int  CDRRecordEntityCode = 0;
   int i=0;
   int  lValidateFlag = 0    ;

   INIT_STR(stContext.LocationInformation);
   sprintf(stContext.LocationInformation,"%s;138:0:L",stContext.CallEventType) ;
   fnRemTrailSpaces(stContext.LocationInformation) ;
   

   if(NOT_NULL(locationInformation->networkLocation))
   {
      if(NOT_NULL(locationInformation->networkLocation->recEntityCode))
      {
         BCT.RECORDING_ENTITY_CODE = *locationInformation->networkLocation->recEntityCode;

         /* RecEntityCode : Syntax Error Check */
         sprintf (TempNumtoChar,"%d", BCT.RECORDING_ENTITY_CODE);
         ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
         if(ReturnValue != 0)
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 184             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/SS/SCU/GPRS/LCS");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityCode") ;
                 sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.LocationInformation,"156:0:L;184:0:L")        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0 ;
         }

         CDRRecordEntityCode = 0;

         for(i=0;i<gRecEntityInfoCount;i++)
         { 
             if(BCT.RECORDING_ENTITY_CODE == NI.RecEntityInfo[i].RecEntityCode)
             {
                CDRRecordEntityCode = 1;
                break;
             }
         }


         if(CDRRecordEntityCode == 0)
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 100                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 184             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/SS/SCU/GPRS/LCS");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityCode") ;
                 sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.LocationInformation,"156:0:L;184:0:L")        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Specified recording entity code not defined in the Recording Entity Information");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0 ;
         }


      }
      else
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 156                         ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          { 
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/SS")  ;
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"NetworkLocation")               ;
              sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.LocationInformation,"156:0:L")        ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Recording Entity Code missing within group");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }


      if(NOT_NULL(locationInformation->networkLocation->locationArea))
      {
         BCT.LOCATION_AREA = *locationInformation->networkLocation->locationArea;
      }

      if(NOT_NULL(locationInformation->networkLocation->cellId))
      {
         BCT.CELLID = *locationInformation->networkLocation->cellId;
      }
   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 138                         ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/SS")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"LocationInformation")               ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.LocationInformation)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Network Location missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
  }



   if(NOT_NULL(locationInformation->geographicalLocation))
   {
      if(ASNOCTS_PRESENT(&locationInformation->geographicalLocation->servingNetwork))
      {
         strcpy(BCT.SERVING_NETWORK,locationInformation->geographicalLocation->servingNetwork.octs);
         fnRemTrailSpaces(BCT.SERVING_NETWORK);
      }
   }

   /*
   printf("LocationInformation Details\n");
   printf("   RecordingEntityCode :-%d-\n",BCT.RECORDING_ENTITY_CODE);
   printf("         Location Area :-%f-\n",BCT.LOCATION_AREA);
   printf("                CellId :-%f-\n",BCT.CELLID);
   printf("        ServingNetowrk :-%s-\n",BCT.SERVING_NETWORK);
   */

}


void ReadBasicService(struct BasicService* basicService)
{
   void *Pointer;
   int ReturnValue = 0;
   int ErrorReturnValue = 0;
   char TempNumtoChar [10]   ;
   int  lValidateFlag = 0    ;

   INIT_STR(stContext.BasicService) ;
   sprintf(stContext.BasicService,"%s;36:0:L",stContext.BasicServiceUsed)        ;
   fnRemTrailSpaces(stContext.BasicService) ;


   if(NOT_NULL(basicService->serviceCode))
   {
      if(basicService->serviceCode->choiceId == BASICSERVICECODE_TELESERVICECODE)
      {
         if(ASNOCTS_PRESENT(basicService->serviceCode->a.teleServiceCode))
         {
            strcpy(BCT.BASIC_SERVICE_TYPE,"T");
            strcpy(BCT.BASIC_SERVICE_CODE,basicService->serviceCode->a.teleServiceCode->octs);

            /* Teleservice Code : Syntax Error Check */
            ReturnValue = fnCheckSyntax(BCT.BASIC_SERVICE_CODE,"DX") ;
            if(ReturnValue != 0)
            {
               REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 218             ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TeleServiceCode") ;
                   sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicService,"426:0:L;218:0:L")        ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.BASIC_SERVICE_CODE);
                   gRejectedErrorNo++ ;
               }
               ReturnValue = 0 ;
            }


            Pointer = NULL;
            Pointer = strstr("00:10:11:12:20:21:22:31:41:42:43:51:52:60:61:62:63:70:80",BCT.BASIC_SERVICE_CODE);
            if(Pointer == NULL)
            {
               REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 218             ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TeleServiceCode") ;
                   sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicService,"426:0:L;218:0:L")        ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.BASIC_SERVICE_CODE);
                   gRejectedErrorNo++ ;
               }
               ReturnValue = 0 ;
            }
 
            if((strcmp(BCT.BASIC_SERVICE_CODE,"22") == 0 ) || (strcmp(BCT.BASIC_SERVICE_CODE,"21") == 0))
            {
                if(BCT.CALL_DURATION > 0)
                {
                    REI.ERROR_CODE[gRejectedErrorNo]  = 100                  ;
                    REI.APPLICATION_TAG[gRejectedErrorNo] = 223             ;
                    strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                    lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                    if(lValidateFlag == 0)
                    {
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC");
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalCallEventDuration") ;
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicCallInformation,"223:0:L")   ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Total Call Event Duration is greater than 0 (zero) for SMS call");
                        sprintf (REI.ERROR_VALUE[gRejectedErrorNo],"%d", BCT.CALL_DURATION);
                        gRejectedErrorNo++ ;
                    }
                    ReturnValue = 0 ;
                }
            }


         }
      }

      if(basicService->serviceCode->choiceId == BASICSERVICECODE_BEARERSERVICECODE)
      {
         if(ASNOCTS_PRESENT(basicService->serviceCode->a.bearerServiceCode))
         {
            strcpy(BCT.BASIC_SERVICE_TYPE,"B");
            strcpy(BCT.BASIC_SERVICE_CODE,basicService->serviceCode->a.bearerServiceCode->octs);


            /* BearerService Code : Syntax Error Check */
            ReturnValue = fnCheckSyntax(BCT.BASIC_SERVICE_CODE,"DX") ;
            if(ReturnValue != 0)
            {
               REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 40             ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"BearerServiceCode") ;
                   sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicService,"426:0:L;40:0:L")        ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.BASIC_SERVICE_CODE);
                   gRejectedErrorNo++ ;
               }

               ReturnValue = 0 ;
            }


            Pointer = NULL;
            Pointer = strstr("00:20:21:22:23:24:25:26:27:30:32:34:35:36:37:40:41:42:43:44:45:46:47:50:54:55:56:57:60:61:62:63:64:65:66:70:72:74:75:76:80:81:82:83:84:85:86:90:92:94:95:96:A0:B0:C0:D0",BCT.BASIC_SERVICE_CODE);
            if(Pointer == NULL)
            {
               REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 40             ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"BearerServiceCode") ;
                   sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicService,"426:0:L;40:0:L")        ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.BASIC_SERVICE_CODE);
                   gRejectedErrorNo++ ;
               }

               ReturnValue = 0 ;

            }

         }
      }
   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 36                          ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"BasicService")               ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.BasicService)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Service Code missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }


   if((BCT.CALL_TYPE == 2) && (strcmp(BCT.BASIC_SERVICE_CODE,"12") != 0))
   {
       if(gDestinationFlag == 0) 
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 35                               ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 147                          ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC")  ;
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MoBasicCallInformation")                 ;
               strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.BasicCallInformation)   ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Group Destination missing and call is not for use of emergency service");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
               gRejectedErrorNo++ ;
           }
       }
       else
       {
            ReturnValue = fnCheckSyntax(BCT.CALLED_CALLING_NUMBER,"DI") ;
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 10                               ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 407                          ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC")  ;
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CalledNumber")                 ;
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;407:0:L",stContext.Destination)   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error and call does not represent an emergency call");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CALLED_CALLING_NUMBER);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0;
            }

            if(gCalledNumberFlag==1)
            {
                ReturnValue = fnCountryCodeCheck(BCT.CALLED_CALLING_NUMBER) ;
                if(ReturnValue != 0)
                {
                    REI.ERROR_CODE[gRejectedErrorNo]  = 20                               ;
                    REI.APPLICATION_TAG[gRejectedErrorNo] = 407                          ;
                    strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
                    lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                    if(lValidateFlag == 0)
                    {
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC")  ;
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CalledNumber")                 ;
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;407:0:L",stContext.Destination)   ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range or number does not start with a valid country code as listed in E.164 Assigned Country Codes");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CALLED_CALLING_NUMBER);
                        gRejectedErrorNo++ ;
                    }
                    ReturnValue = 0;
                }
            }


            if((gCalledNumberFlag==0) && (gDestNumberFlag==0))
            {

                REI.ERROR_CODE[gRejectedErrorNo]  = 39                               ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 89                          ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC")  ;
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Destination")                 ;
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.Destination)   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Neither item Called Number nor item Dialled Digits present within call and call does not represent an emergency call");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CALLED_CALLING_NUMBER);
                    gRejectedErrorNo++ ;
                }
            }

            if((gCalledNumberFlag==0) && strcmp(BCT.BASIC_SERVICE_CODE,"22") == 0) 
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 42                               ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 89                          ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC")  ;
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Destination")                 ;
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.Destination)   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Called Number not present and call represents SMS usage");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                    gRejectedErrorNo++ ;
                }
            }
       }
   }


   /* Derive Service Code for MOC and MTC Calls */

   if(strcmp(BCT.BASIC_SERVICE_TYPE,"T") == 0)
   {
       if((strcmp(BCT.BASIC_SERVICE_CODE,"22") == 0) || (strcmp(BCT.BASIC_SERVICE_CODE,"21") == 0) || (strcmp(BCT.BASIC_SERVICE_CODE,"20") == 0 ))
       {
          strcpy(BCT.SERVICE_CODE,"003") ;
       }
       else
       {
          strcpy(BCT.SERVICE_CODE,"000") ;
       }
   }
   else if(strcmp(BCT.BASIC_SERVICE_TYPE,"B") == 0)
   {
       if(strcmp(BCT.BASIC_SERVICE_CODE,"37") == 0)
       {
          strcpy(BCT.SERVICE_CODE,"008") ;
       }
       else
       {
          strcpy(BCT.SERVICE_CODE,"000") ;
       }
   }


   if(NOT_NULL(basicService->transparencyIndicator))
   {
      BCT.TRANSPARENCY_INDICATOR = *basicService->transparencyIndicator;


      /* TransparencyIndicator : Syntax Error Check */
      sprintf (TempNumtoChar,"%d",BCT.TRANSPARENCY_INDICATOR);
      ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
      if(ReturnValue != 0)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 228             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TransparencyIndicator") ;
              sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicService,"228:0:L")        ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
              gRejectedErrorNo++ ;
          }

          ReturnValue = 0 ;
      }


      if ((BCT.TRANSPARENCY_INDICATOR < 0) || (BCT.TRANSPARENCY_INDICATOR > 1))
      {

          REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 228             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TransparencyIndicator") ;
              sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicService,"228:0:L")        ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
              gRejectedErrorNo++ ;
          }

          ReturnValue = 0 ;
      }


   }

   if(NOT_NULL(basicService->fnur))
   {
      BCT.FNUR = *basicService->fnur;
   }

   if(NOT_NULL(basicService->userProtocolIndicator))
   {
      BCT.USER_PROTOCOL_INDICATOR = *basicService->userProtocolIndicator;


      /* UserProtocolIndicator : Syntax Error Check */

      sprintf (TempNumtoChar,"%d",BCT.USER_PROTOCOL_INDICATOR);
      ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
      if(ReturnValue != 0)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 280             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"UserProtocolIndicator") ;
              sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicService,"280:0:L")        ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
              gRejectedErrorNo++ ;
          }

          ReturnValue = 0 ;
      }


      if ((BCT.USER_PROTOCOL_INDICATOR < 0) || (BCT.USER_PROTOCOL_INDICATOR > 5))
      {

          REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 280             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"UserProtocolIndicator") ;
              sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicService,"280:0:L")        ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
              gRejectedErrorNo++ ;
          }

          ReturnValue = 0 ;
      }

   }

   if(ASNOCTS_PRESENT(&basicService->guaranteedBitRate))
   {
       strcpy(BCT.GUARANTEED_BIT_RATE,basicService->guaranteedBitRate.octs);

       /* GuaranteedBitRate : Syntax Error Check */

       ReturnValue = fnCheckSyntax(BCT.GUARANTEED_BIT_RATE,"DI") ;
       if(ReturnValue != 0)
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 420             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GuaranteedBitRate") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicService,"420:0:L")        ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.GUARANTEED_BIT_RATE);
               gRejectedErrorNo++ ;
           }

           ReturnValue = 0 ;
       }

       Pointer = NULL;
       Pointer = strstr("14400:28800:32000:33600:56000:57600:64000",BCT.GUARANTEED_BIT_RATE);
       if(Pointer == NULL)
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 420             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"GuaranteedBitRate") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicService,"420:0:L")        ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.GUARANTEED_BIT_RATE);
               gRejectedErrorNo++ ;
           }

           ReturnValue = 0 ;
       }

   }

   if(ASNOCTS_PRESENT(&basicService->maximumBitRate))
   {
      strcpy(BCT.MAXIMUM_BIT_RATE,basicService->maximumBitRate.octs);


       /* GuaranteedBitRate : Syntax Error Check */

       ReturnValue = fnCheckSyntax(BCT.MAXIMUM_BIT_RATE,"DI") ;
       if(ReturnValue != 0)
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 421             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MaximumBitRate") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicService,"421:0:L")        ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.MAXIMUM_BIT_RATE);
               gRejectedErrorNo++ ;
           }

           ReturnValue = 0 ;
       }

       Pointer = NULL;
       Pointer = strstr("14400:28800:32000:33600:56000:57600:64000",BCT.MAXIMUM_BIT_RATE);
       if(Pointer == NULL)
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 421             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MaximumBitRate") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.BasicService,"421:0:L")        ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.MAXIMUM_BIT_RATE);
               gRejectedErrorNo++ ;
           }

           ReturnValue = 0 ;
       }

   }
 
   /*
   printf("ServicType : -%s-\n",BCT.BASIC_SERVICE_TYPE);
   printf("TransparencyIndicator  -%d- \n",BCT.TRANSPARENCY_INDICATOR);
   */
   
}


void ReadChargeInformationList(ChargeInformation *CI,int CICount)
{
   int	CDLCount=0; 	/* Count for ChargeDetailList within ChargeInformation */
   int  TICount=0;  	/* Count for TaxInformation within ChargeInformation   */
   ChargeDetail   *CD;
   TaxInformation *TI;
   int k=0, i=0, j=0 ;
   void *Pointer;
   int ErrorReturnValue = 0;
   int ReturnValue = 0;
   char TempNumtoChar [10]   ;
   int lChargeableUnitsFlag ;
   int lChargeTypeFlag = 0 ;
   int CDRExchangerateFlag= 0;
   int CDRTaxCodeFlag = 0;
   int CDRDiscountCodeFlag = 0 ;
   int CDROtherTypeChargeFlag = 0 ;
   int CDROtherTypeCharge = 0    ;
   int  lValidateFlag = 0    ;
   int lExchangeRateCodeFlag = 0;
  


   if((strcmp(BCT.SERVICE_CODE,"005") == 0)|| (strcmp(BCT.SERVICE_CODE,"305") == 0))
   {
       INIT_STR(stContext.ChargeInformation) ;
       sprintf(stContext.ChargeInformation,"%s;70:%d:L;69:0:L",stContext.GprsServiceUsed,CICount+1);
       fnRemTrailSpaces(stContext.ChargeInformation) ;
   }
   else if(strcmp(BCT.SERVICE_CODE,"006") == 0) 
   {
       INIT_STR(stContext.ChargeInformation) ;
       sprintf(stContext.ChargeInformation,"%s;70:%d:L;69:0:L",stContext.SupplServiceUsed,CICount+1);
       fnRemTrailSpaces(stContext.ChargeInformation) ;
   }
   else
   {
       INIT_STR(stContext.ChargeInformation) ;
       sprintf(stContext.ChargeInformation,"%s;70:%d:L;69:0:L",stContext.BasicServiceUsed,CICount+1);
       fnRemTrailSpaces(stContext.ChargeInformation) ;
   }

   /* Read ChargedItem */
   if(ASNOCTS_PRESENT(&CI->chargedItem))
   {
       strcpy(BCT.CHARGED_ITEM,CI->chargedItem.octs);


       /* ChargedItem : Syntax Error Check */
       ReturnValue = fnCheckSyntax(BCT.CHARGED_ITEM,"AS") ;
       if(ReturnValue != 0)
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 66             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargedItem") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeInformation,"66:0:L")        ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CHARGED_ITEM);
               gRejectedErrorNo++ ;
           }

           ReturnValue = 0 ;
       }

       /* If the Call Type is 1 or 2 and Call event is otherthan SMS */
       
       if(strcmp(BCT.BASIC_SERVICE_TYPE,"T") == 0) 
       {
           if((strcmp(BCT.SERVICE_CODE,"000") == 0) || (strcmp(BCT.SERVICE_CODE,"008") == 0))
           {
                  Pointer = NULL;
                  Pointer = strstr("A:D:F",BCT.CHARGED_ITEM);
                  if(Pointer == NULL)
                  {
                     REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                     REI.APPLICATION_TAG[gRejectedErrorNo] = 66             ;
                     strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                     lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                     if(lValidateFlag == 0)
                     {
                         strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                         strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargedItem") ;
                         sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeInformation,"66:0:L")        ;
                         fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                         strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                         strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CHARGED_ITEM);
                         gRejectedErrorNo++ ;
                     }
                     ReturnValue = 0 ;
                  }
           }

           if(strcmp(BCT.SERVICE_CODE,"003") == 0)
           {
               if(strcmp(BCT.CHARGED_ITEM,"E") != 0)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 66             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargedItem") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeInformation,"66:0:L")        ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CHARGED_ITEM);
                       gRejectedErrorNo++ ;
                   }
                   ReturnValue = 0 ;
               }
           }
       }


       /* If Call Type is 3 */
       if(strcmp(BCT.SERVICE_CODE,"006") == 0) 
       {
           if(strcmp(BCT.CHARGED_ITEM,"E") != 0)
           {
               REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 66             ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargedItem") ;
                   sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeInformation,"66:0:L")        ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CHARGED_ITEM);
                   gRejectedErrorNo++ ;
               }
               ReturnValue = 0 ;
           }
       }


       /* If the Call Type is 4  */
       if((strcmp(BCT.SERVICE_CODE,"005") == 0)|| (strcmp(BCT.SERVICE_CODE,"305") == 0))
       {
           Pointer = NULL;
           Pointer = strstr("A:D:F:L:V:W:X",BCT.CHARGED_ITEM);
           if(Pointer == NULL)
           {
               REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 66             ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargedItem") ;
                   sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeInformation,"66:0:L")        ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CHARGED_ITEM);
                   gRejectedErrorNo++ ;
               }

               ReturnValue = 0 ;
           }
       }


   }
   else
   {
       REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
       REI.APPLICATION_TAG[gRejectedErrorNo] = 69                          ;
       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
       if(lValidateFlag == 0)
       {
           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeInformation")               ;
           strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargeInformation)        ;
           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Item Charged Item missing within group");
           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
           gRejectedErrorNo++ ;
       }
   }


   lExchangeRateCodeFlag = 1 ;

   /* Read ExchangeRateCode */
   if(NOT_NULL(CI->exchangeRateCode))
   {
       BCT.TAP_EXCHANGE_RATE_CODE      = *CI->exchangeRateCode;
   
       lExchangeRateCodeFlag = 0 ;


       /* ExchangeRateCode : Syntax Error Check */
       sprintf (TempNumtoChar,"%d",BCT.TAP_EXCHANGE_RATE_CODE);
       ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
       if(ReturnValue != 0)
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 105             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ExchangeRateCode") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeInformation,"105:0:L")        ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
               gRejectedErrorNo++ ;
           }
           ReturnValue = 0 ;
       }

        CDRExchangerateFlag = 0 ;

        /* Compare the CDR Exchange Rate Code with Group Currency Conversion */
        for(k=0; k<gExchangeRateCount; k++)
        {
           if(BCT.TAP_EXCHANGE_RATE_CODE == ACC.CurrencyConversionInfo[k].ExchangeRateCode)
           {
              CDRExchangerateFlag = 1 ;
              break;
           }
        }

        if(CDRExchangerateFlag == 0)
        {
           REI.ERROR_CODE[gRejectedErrorNo]  = 101                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 105             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ExchangeRateCode") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeInformation,"105:0:L")        ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Specified Exchange Rate Code not defined in group Currency Conversion");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
               gRejectedErrorNo++ ;
           }
           ReturnValue = 0 ;
        }


   }

    /* Modified by Anitha For TAP3.12 For MOC Calls 
      Before if((BCT.CALL_TYPE ==2) && (strcmp(BCT.SERVICE_CODE,"006") != 0))*/

   /* Call Type Group Should present for all the MO/GPRS Calls */
   if((BCT.CALL_TYPE == 2 || BCT.CALL_TYPE ==1) && (strcmp(BCT.SERVICE_CODE,"006") != 0))
   {
        /* Read CallTypeGroup */
        if(NOT_NULL(CI->callTypeGroup))
        {

            INIT_STR(stContext.CallTypeGroup) ;
            sprintf(stContext.CallTypeGroup,"%s;258:0:L",stContext.ChargeInformation);
            fnRemTrailSpaces(stContext.CallTypeGroup) ;


            if(NOT_NULL(CI->callTypeGroup->callTypeLevel1))
            {
                BCT.CALL_TYPE_LEVEL1          = *CI->callTypeGroup->callTypeLevel1;


                /* CallTypeLevel1 : Syntax Error Check */
                sprintf (TempNumtoChar,"%d",BCT.CALL_TYPE_LEVEL1);
                ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
                if(ReturnValue != 0)
                {
                    REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                    REI.APPLICATION_TAG[gRejectedErrorNo] = 259             ;
                    strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                    lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                    if(lValidateFlag == 0)
                    {
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/GPRS/MTC")  ;
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeLevel1")               ;
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallTypeGroup,"259:0:L")      ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                        gRejectedErrorNo++ ;
                    }

                    ReturnValue = 0 ;
                }


                if((strcmp(BCT.SERVICE_CODE,"005") != 0) && (strcmp(BCT.SERVICE_CODE,"305") != 0))
                {
                     Pointer = NULL;
					 
     		     if (BCT.CALL_TYPE ==1)
                 Pointer = strstr("0:1:2",TempNumtoChar);
		         else if(BCT.CALL_TYPE ==2)
		         Pointer = strstr("1:2",TempNumtoChar);

                     if(Pointer == NULL)
                     {
                         REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                         REI.APPLICATION_TAG[gRejectedErrorNo] = 259             ;
                         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC")  ;
                             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeLevel1")               ;
                             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallTypeGroup,"259:0:L")      ;
                             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                             gRejectedErrorNo++ ;
                         }

                         ReturnValue = 0 ;
                     }
                }
                else  
                { 
				    
                     Pointer = NULL; 
					 char DestType[3];
                     sprintf(DestType,"%s%s",":",TempNumtoChar);
                     Pointer = strstr(":10:11:12",DestType);
					   if(Pointer == NULL)
                       {
                         REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                         REI.APPLICATION_TAG[gRejectedErrorNo] = 259             ;
                         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
                             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeLevel1")               ;
                             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallTypeGroup,"259:0:L")      ;
                             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                             gRejectedErrorNo++ ;
                         }

                         ReturnValue = 0 ;
                     }
               }
			 }

            else
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 258                          ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/GPRS/MTC")  ;
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeGroup")               ;
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallTypeGroup)        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Call Type Level 1 missing within group");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                    gRejectedErrorNo++ ;
                }
            }


            if(NOT_NULL(CI->callTypeGroup->callTypeLevel2))
            {
                BCT.CALL_TYPE_LEVEL2          = *CI->callTypeGroup->callTypeLevel2;


                /* CallTypeLevel2 : Syntax Error Check */
                sprintf (TempNumtoChar,"%d",BCT.CALL_TYPE_LEVEL2);
                ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
                if(ReturnValue != 0)
                {
                    REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                    REI.APPLICATION_TAG[gRejectedErrorNo] = 255             ;
                    strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                    lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                    if(lValidateFlag == 0)
                    {
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/GPRS/MTC")  ;
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeLevel2")               ;
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallTypeGroup,"255:0:L")      ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                        gRejectedErrorNo++ ;
                    }

                    ReturnValue = 0 ;
                }

           if((strcmp(BCT.SERVICE_CODE,"005") != 0) && (strcmp(BCT.SERVICE_CODE,"305") != 0))
             {
                Pointer = NULL; 
				if(BCT.CALL_TYPE==1)
				Pointer = strstr("0:6:7",TempNumtoChar);
                if(BCT.CALL_TYPE ==2)
                Pointer = strstr("0:1:2:3:4:5",TempNumtoChar);
                if(Pointer == NULL)
                {
                    REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                    REI.APPLICATION_TAG[gRejectedErrorNo] = 255             ;
                    strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                    lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                    if(lValidateFlag == 0)
                    {
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC")  ;
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeLevel2")               ;
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallTypeGroup,"255:0:L")      ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                        gRejectedErrorNo++ ;
                    }

                    ReturnValue = 0 ;
                }
            }

		 else 
         {  
          Pointer = NULL; 
		  char DestSubType[3];
          sprintf(DestSubType,"%s%s",":",TempNumtoChar);
          Pointer = strstr(":0:10:11:12:13:14:15",DestSubType);
          if(Pointer == NULL)
                {
                    REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                    REI.APPLICATION_TAG[gRejectedErrorNo] = 255             ;
                    strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                    lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                    if(lValidateFlag == 0)
                    {
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeLevel2")               ;
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallTypeGroup,"255:0:L")      ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                        gRejectedErrorNo++ ;
                    }

                    ReturnValue = 0 ;
                }
            }

        }
            else
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 258                          ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/GPRS/MTC")  ;
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeGroup")               ;
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallTypeGroup)        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Call Type Level 2 missing within group");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                    gRejectedErrorNo++ ;
                }
            }


            if(NOT_NULL(CI->callTypeGroup->callTypeLevel3))
            {
                BCT.CALL_TYPE_LEVEL3          = *CI->callTypeGroup->callTypeLevel3;
 
                /* CallTypeLevel3 : Syntax Error Check */
                sprintf (TempNumtoChar,"%d",BCT.CALL_TYPE_LEVEL3);
                ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
                if(ReturnValue != 0)
                {
                    REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                    REI.APPLICATION_TAG[gRejectedErrorNo] = 256             ;
                    strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                    lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                    if(lValidateFlag == 0)
                    { 
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/GPRS/MTC")  ;
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeLevel3")               ;
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallTypeGroup,"256:0:L")      ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                        gRejectedErrorNo++ ;
                    }

                    ReturnValue = 0 ;
                }
            }
            else
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 258                          ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/GPRS/MTC")  ;
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeGroup")               ;
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallTypeGroup)        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Call Type Level 3 missing within group");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                    gRejectedErrorNo++ ;
                }
            }

        }
        else
        {
            REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
            REI.APPLICATION_TAG[gRejectedErrorNo] = 69                          ;
            strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
            lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
            if(lValidateFlag == 0)
            {
                strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC")  ;
                strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/GPRS/MTC")  ;
                strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargeInformation)        ;
                fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Item Call Type Group missing within group where the Charge Information relates to Basic Service Used or GPRS Service Used");
                strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                gRejectedErrorNo++ ;
            }
        }

   }
   /*
   printf("Charged Item   : -%s- \n",BCT.CHARGED_ITEM);
   printf("Exchange Rate  : -%d- \n",BCT.TAP_EXCHANGE_RATE_CODE);
   printf("CalltypeLevel1 : -%d- \n",BCT.CALL_TYPE_LEVEL1);
   printf("CalltypeLevel2 : -%d- \n",BCT.CALL_TYPE_LEVEL2);
   printf("CalltypeLevel3 : -%d- \n",BCT.CALL_TYPE_LEVEL3);
   */

   /* Loop through the ChargeDetailList */

   lChargeTypeFlag = 0 ;
   INIT_STR(gIOTChargeContext)    ;
   INIT_STR(gIOTTaxContext)       ;
   INIT_STR(gIOTDiscountContext)  ;
   if(NOT_NULL(CI->chargeDetailList))
   {
      FOR_EACH_LIST_ELMT(CD,CI->chargeDetailList)
      {
         CDLCount = 0;
         lChargeableUnitsFlag = 0;

         INIT_STR(stContext.ChargeDetail) ;
         sprintf(stContext.ChargeDetail,"%s;64:%d:L;63:0:L",stContext.ChargeInformation,CDLCount+1);
         fnRemTrailSpaces(stContext.ChargeDetail) ;

         strcpy(gIOTChargeContext,stContext.ChargeDetail);

         if(ASNOCTS_PRESENT(&CD->chargeType))
         {
			 //Charge type 1 Added as per the ghana specific while implementing the LTE for the ghana 
            //strcpy(BCT.CHARGE_TYPE,CD->chargeType.octs);
			strcpy(lc_ChargeType,CD->chargeType.octs);
            if(strcmp(lc_ChargeType,"68")==0)
            { 
               strcpy(BCT.CHARGE_TYPE1,lc_ChargeType);
            }
            else
            {
                 strcpy(BCT.CHARGE_TYPE,lc_ChargeType);
            }

            /* ChargeType : Syntax Error Check */
            ReturnValue = fnCheckSyntax(BCT.CHARGE_TYPE,"DI") ;
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 71              ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeType");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeDetail,"71:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CHARGE_TYPE);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }

            /* ChargeType :Value Out Of Range */

            Pointer = NULL;
            Pointer = strstr("00:01:02:03:04:21:50",BCT.CHARGE_TYPE);
            if(Pointer == NULL)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 71              ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeType");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeDetail,"71:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CHARGE_TYPE);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }


         }
         else
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 38                             ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 63                         ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeDetail")               ;
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargeDetail)        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Charge Type not present within group");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                 gRejectedErrorNo++ ;
             }
         }


         if(NOT_NULL(CD->charge))
         {
            /* Accumulate Charge for ChargeType '00' within the ChargeDetailList */
            if(strcmp(BCT.CHARGE_TYPE,"00")==0)
            {
               BCT.CHARGE = BCT.CHARGE + *CD->charge;

               lChargeTypeFlag = 1 ;
               /* Charge : Syntax Error Check */
               sprintf (TempNumtoChar,"%d",*CD->charge);
               ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
               if(ReturnValue != 0)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 62              ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Charge");
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeDetail,"62:0:L")        ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                        gRejectedErrorNo++ ;
                   }
                   ReturnValue = 0 ;
               }

               /* Charge : Value Out of Range */

               if (*CD->charge < 0) 
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 62              ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Charge");
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeDetail,"62:0:L")        ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }
                   ReturnValue = 0 ;
               }
            }
			else if(strcmp(lc_ChargeType,"68")==0)   // Added charge1 field as per the ghana specific tapin code while implementing the LTE
            {
                BCT.CHARGE1 = BCT.CHARGE1 + *CD->charge;
            }

            if((strcmp(BCT.CHARGE_TYPE,"01")==0) || (strcmp(BCT.CHARGE_TYPE,"03")==0) || (strcmp(BCT.CHARGE_TYPE,"04")==0) || (strcmp(BCT.CHARGE_TYPE,"21")==0))
            {
                CDROtherTypeChargeFlag = 1 ;
                CDROtherTypeCharge = CDROtherTypeCharge + *CD->charge ;
            }
     
         }
         else
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 39                             ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 63                         ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeDetail")               ;
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargeDetail)        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Charge not present within group");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                 gRejectedErrorNo++ ;
             }
         }



         if(NOT_NULL(CD->chargeableUnits))
         {
            lChargeableUnitsFlag = 1 ;
            /* Get the Chargeable Units for ChargeType '00' */
            if(strcmp(BCT.CHARGE_TYPE,"00")==0)
            {
               BCT.CHARGEABLE_UNITS = BCT.CHARGEABLE_UNITS + *CD->chargeableUnits;

               /* ChargeableUnits : Syntax Error Check */
               sprintf (TempNumtoChar,"%d",*CD->chargeableUnits);
               ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
               if(ReturnValue != 0)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 65              ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeableUnits");
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeDetail,"65:0:L")        ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }
                   ReturnValue = 0 ;
               }

               /* ChargeableUnits : Value Out of Range */

               if (*CD->chargeableUnits < 0)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 65              ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeableUnits");
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeDetail,"65:0:L")        ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                        gRejectedErrorNo++ ;
                   }
                   ReturnValue = 0 ;
               }
            }
			else if(strcmp(lc_ChargeType,"68")==0)
            { 
                       BCT.CHARGEABLE_UNITS1 = BCT.CHARGEABLE_UNITS1 + *CD->chargeableUnits;    
            }


            if((strcmp(BCT.CHARGED_ITEM,"D") ==0) && (*CD->chargeableUnits > BCT.CALL_DURATION))
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 100                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 65              ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeableUnits");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeDetail,"65:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Chargeable Units for Charge Type '00' are greater than Total Call Event Duration for Charged Item 'D'");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }

            if(((strcmp(BCT.SERVICE_CODE,"005") == 0) || (strcmp(BCT.SERVICE_CODE,"305") == 0))  && (strcmp(BCT.CHARGE_TYPE,"00")==0))
            {
               if(strcmp(BCT.CHARGED_ITEM,"X") ==0)
               {
                   if((*CD->chargeableUnits) > (BCT.DATA_VOLUME_INCOMING +BCT.DATA_VOLUME_OUTGOING))
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 101                  ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 65              ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeableUnits");
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeDetail,"65:0:L")        ;
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Chargeable Units for Charge Type '00' are greater than the sum of Data Volume Incoming and Data Volume Outgoing for Charged Item 'X'");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                           gRejectedErrorNo++ ;
                       }
                      ReturnValue = 0 ;
                   }

               }
               else if(strcmp(BCT.CHARGED_ITEM,"V") ==0)
               {
                   if(*CD->chargeableUnits > BCT.DATA_VOLUME_OUTGOING)
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 102                  ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 65              ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeableUnits");
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeDetail,"65:0:L")        ;
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Chargeable Units for Charge Type '00' are greater than Data Volume Outgoing for Charged Item 'V'");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                           gRejectedErrorNo++ ;
                       }
                       ReturnValue = 0 ;
                   }

               }
               else if(strcmp(BCT.CHARGED_ITEM,"W") ==0)
               {
                   if(*CD->chargeableUnits > BCT.DATA_VOLUME_INCOMING )
                   {
                       REI.ERROR_CODE[gRejectedErrorNo]  = 103                  ;
                       REI.APPLICATION_TAG[gRejectedErrorNo] = 65              ;
                       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                       if(lValidateFlag == 0)
                       {
                           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS");
                           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeableUnits");
                           sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeDetail,"65:0:L")        ;
                           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Chargeable Units for Charge Type '00' are greater than Data Volume Incoming for Charged Item 'W'");
                           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                           gRejectedErrorNo++ ;
                       }
                       ReturnValue = 0 ;
                   }

               }

            }

         }


         if((strcmp(BCT.CHARGED_ITEM,"D") ==0)||(strcmp(BCT.CHARGED_ITEM,"V") ==0)||(strcmp(BCT.CHARGED_ITEM,"W") ==0)||(strcmp(BCT.CHARGED_ITEM,"X") ==0))
         {
             if(lChargeableUnitsFlag == 0)
             {
                 REI.ERROR_CODE[gRejectedErrorNo]  = 33                             ;
                 REI.APPLICATION_TAG[gRejectedErrorNo] = 63                         ;
                 strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
                 lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                 if(lValidateFlag == 0)
                 {
                     strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
                     strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeDetail")               ;
                     strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargeDetail)        ;
                     fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                     strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Associated item Charged Item is one of D,V,W or X and item Chargeable Units not present");
                     strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                     gRejectedErrorNo++ ;
                 }
             }
         }

         if(NOT_NULL(CD->chargedUnits))
         {
            /* Get the ChargedUnits for ChargeType '00' 
            if(strcmp(BCT.CHARGE_TYPE,"00")==0)
            {
               BCT.CHARGED_UNITS = BCT.CHARGED_UNITS + *CD->chargedUnits;
            } */
			if(strcmp(lc_ChargeType,"00")==0)
            {
               BCT.CHARGED_UNITS = BCT.CHARGED_UNITS + *CD->chargedUnits;
            }
            else if(strcmp(lc_ChargeType,"68")==0)
            { 
               BCT.CHARGED_UNITS1 =BCT.CHARGED_UNITS1 + *CD->chargedUnits;
            }
         }
      }


      if((BCT.CHARGE > 0) && (lExchangeRateCodeFlag == 1))
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 69                          ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeInformation")               ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargeInformation)        ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Item Exchange Rate Code missing within group and one or more Charge within an associated Charge Detail is greater than zero");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }


      if(lChargeTypeFlag == 0)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 36                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 69                         ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeInformation")               ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargeInformation)        ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Occurrence of group Charge Detail containing Charge Type '00' missing within group");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }

      if((lChargeTypeFlag == 1) && (CDROtherTypeChargeFlag == 1))
      {
          if(BCT.CHARGE != CDROtherTypeCharge)
          {
              REI.ERROR_CODE[gRejectedErrorNo]  = 39                             ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 69                         ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeInformation")               ;
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargeInformation)        ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"In accordance with roaming agreement, charges are defined in individual Charge Types, but the Charge for Charge Type 00 does not equal sum of Charges for the other Charge Types as stated within roaming agreement.");
                  sprintf (REI.ERROR_VALUE[gRejectedErrorNo],"%d",BCT.CHARGE);
                  gRejectedErrorNo++ ;
              }
          }
      }
      /*
      printf("Charge Type : -%s- \n",BCT.CHARGE_TYPE);
      printf("Charge      : -%f- \n",BCT.CHARGE);
      printf("ChargableUnt: -%f- \n",BCT.CHARGEABLE_UNITS);
      printf("ChargedUnit : -%f- \n",BCT.CHARGED_UNITS);
      */
   }
   else
   {
       REI.ERROR_CODE[gRejectedErrorNo]  = 33                             ;
       REI.APPLICATION_TAG[gRejectedErrorNo] = 69                          ;
       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
       if(lValidateFlag == 0)
       {
           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeInformation")               ;
           strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargeInformation)        ;
           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Group Charge Detail missing within group");
           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
           gRejectedErrorNo++ ;
       }
   }


 gTaxListFlag=0;
   /* Loop through the TaxInformationList */
   if(NOT_NULL(CI->taxInformation))
   {
   gTaxListFlag=1;
      FOR_EACH_LIST_ELMT(TI,CI->taxInformation)
      {
         TICount = 0;


         INIT_STR(stContext.TaxInformation) ;
         sprintf(stContext.TaxInformation,"%s;214:%d:L;213:0:L",stContext.ChargeInformation,TICount+1);
         fnRemTrailSpaces(stContext.TaxInformation) ;


         strcpy(gIOTTaxContext,stContext.TaxInformation);

         if(NOT_NULL(TI->taxCode))
         {
             BCT.TAX_CODE = *TI->taxCode;

             /* TaxCode : Syntax Error Check */
             sprintf (TempNumtoChar,"%d",BCT.TAX_CODE);
             ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
             if(ReturnValue != 0)
             {
                 REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
                 REI.APPLICATION_TAG[gRejectedErrorNo] = 212             ;
                 strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                 lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                 if(lValidateFlag == 0)
                 {
                     strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                     strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxCode");
                     sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.TaxInformation,"212:0:L")        ;
                     fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                     strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                     strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                     gRejectedErrorNo++ ;
                 }
                 ReturnValue = 0 ;
             }

            CDRTaxCodeFlag = 0;

            for(i=0;i<gTaxationCount;i++)
            {
                if(BCT.TAX_CODE == ACC.Taxation[i].TaxCode)
                {
                   CDRTaxCodeFlag = 1;
                    break;
                }
            }

            if(CDRTaxCodeFlag==0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 100                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 212             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxCode");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.TaxInformation,"212:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Specified Tax Rate Code was not defined in the group Taxation");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }


         }
         else
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 213                          ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxInformation")               ;
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.TaxInformation)        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Tax Rate Code missing within group");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                 gRejectedErrorNo++ ;
             }
         }


         if(NOT_NULL(TI->taxValue))
         {
            /* Accumulate the TotalTax for the Call */
            BCT.TAX_VALUE = BCT.TAX_VALUE + *TI->taxValue;

            /* TaxValue : Syntax Error Check */
            sprintf (TempNumtoChar,"%d",BCT.TAX_VALUE);
            ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 397             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxValue");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.TaxInformation,"397:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }


            /* Taxvalue : Value Out of Range */

            if (BCT.TAX_VALUE < 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 397             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxValue");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.TaxInformation,"397:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }

         }
         else
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 31              ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 213         ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")   ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxInformation")               ;
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.TaxInformation)        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Tax Value missing within group");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                 gRejectedErrorNo++ ;
             }
         }


         if(NOT_NULL(TI->taxableAmount))
         {
            /* Accumulate the TotalTaxable amount for the Call */
            BCT.TAXABLE_AMOUNT = BCT.TAXABLE_AMOUNT + *TI->taxableAmount;

            /* TaxableAmount : Syntax Error Check */
            sprintf (TempNumtoChar,"%d",BCT.TAXABLE_AMOUNT);
            ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 398             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxableAmount");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.TaxInformation,"398:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }


            /* TaxableAmount : Value Out of Range */

            if (BCT.TAXABLE_AMOUNT <= 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 398             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxableAmount");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.TaxInformation,"398:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }


         }

         /* Added by Chetan on 14-May-2009 to store Tax Details */

         for(k=0; k<gTaxationCount; k++)
         {
            if((ACC.Taxation[k].TaxCode == BCT.TAX_CODE) && (BCT.TAX_VALUE > 0))
            {
               if(strlen(BCT.TAP_TAX_TYPE_RATE) < 100)
               {
                   sprintf(BCT.TAP_TAX_TYPE_RATE,"%s%s:%d;",BCT.TAP_TAX_TYPE_RATE,ACC.Taxation[k].TaxType,ACC.Taxation[k].TaxRate) ;
               }
               break ;
            }
         }

         TICount++;

         /* This count indicates if more than 1tax is present for the call */
         BCT.TAX_INFORMATION_COUNT    = BCT.TAX_INFORMATION_COUNT + 1;
      }

   }

 if(( BCT.TAX_INFORMATION_COUNT>0) && (gTapinTaxFlag ==0))
      	 {       
              REI.ERROR_CODE[gRejectedErrorNo]  = 40                 ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 69             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
              lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxGroup") ;
                   sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s",stContext.ChargeInformation)        ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Group Tax Information present within group but not expected in accordance with roaming agreement for the call/event and Tax Value referenced within the group is greater than 0 ");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                  gRejectedErrorNo++ ;
              }
         }


    	 if(( BCT.TAX_INFORMATION_COUNT==0) && (gTapinTaxFlag ==1) )
        	 {            
             
	   	          REI.ERROR_CODE[gRejectedErrorNo]  = 34                 ;
             	  REI.APPLICATION_TAG[gRejectedErrorNo] = 69             ;
             	  strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
             	  lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
             	 if(lValidateFlag == 0)
             	 {
                	 
                  	  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                 	  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxGroup") ;
                	   sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s",stContext.ChargeInformation)        ;
                 	  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                	  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Group Tax Information missing within group but expected in accordance with roaming agreement for that particular call. Tax Information group missing must be interpreted as Tax Value 0  ");
                 	  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                 	  gRejectedErrorNo++ ;
            	  }
        	}






   /* Read DiscountInformation */
   if(NOT_NULL(CI->discountInformation))
   {

      INIT_STR(stContext.DiscountInformation) ;
      sprintf(stContext.DiscountInformation,"%s;96:0:L",stContext.ChargeInformation);
      fnRemTrailSpaces(stContext.DiscountInformation) ;

      strcpy(gIOTDiscountContext,stContext.DiscountInformation);

      if(NOT_NULL(CI->discountInformation->discountCode))
      {
          BCT.DISCOUNT_CODE = *CI->discountInformation->discountCode;

          /* DiscountCode : Syntax Error Check */
          sprintf (TempNumtoChar,"%d",BCT.DISCOUNT_CODE);
          ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
          if(ReturnValue != 0)
          {
              REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 91             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DiscountCode");
                  sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.DiscountInformation,"91:0:L")        ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
          }


           CDRDiscountCodeFlag = 0;

            for(i=0;i<gDiscountingCount;i++)
            {
                if(BCT.DISCOUNT_CODE == ACC.Discounting[i].DiscountCode)
                {
                   CDRDiscountCodeFlag = 1;
                    break;
                }
            }

            if(CDRDiscountCodeFlag==0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 102                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 91               ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                { 
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DiscountCode");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.DiscountInformation,"91:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Specified discount code was not defined in group Discount Applied");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }

      }
      else
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 96                         ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DiscountInformation")               ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.DiscountInformation)        ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Discount Code missing within group");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }


      if(NOT_NULL(CI->discountInformation->discount))
      {
         /* Accumulate the Discount amount for the Call */
         BCT.DISCOUNT = BCT.DISCOUNT + *CI->discountInformation->discount;

         /* Discount : Syntax Error Check */
         sprintf (TempNumtoChar,"%d",BCT.DISCOUNT);
         ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
         if(ReturnValue != 0)
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 412             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Discount");
                 sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.DiscountInformation,"412:0:L")        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0 ;
         }


         /* Discount : Value Out of Range */

         if (BCT.DISCOUNT < 0)
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 412             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Discount");
                 sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.DiscountInformation,"412:0:L")        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0 ;
         }

      }
      else
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 96                         ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DiscountInformation")               ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.DiscountInformation)        ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Item Discount Value missing within group and Discount Code refers to a Discount Rate");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }


      if(NOT_NULL(CI->discountInformation->discountableAmount))
      {
         /* Accumulate the DiscountableAmount for the Call */
         BCT.DISCOUNTABLE_AMT = BCT.DISCOUNTABLE_AMT + *CI->discountInformation->discountableAmount;


         /* DiscountableAmount : Syntax Error Check */
         sprintf (TempNumtoChar,"%d",BCT.DISCOUNTABLE_AMT);
         ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
         if(ReturnValue != 0)
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 423             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DiscountableAmount");
                 sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.DiscountInformation,"423:0:L")        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0 ;
         }


         /* DiscountableAmount : Value Out of Range */

         if (BCT.DISCOUNTABLE_AMT <= 0)
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 423             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DiscountableAmount");
                 sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.DiscountInformation,"423:0:L")        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0 ;
         }

      }
      else
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 96                         ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DiscountInformation")               ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.DiscountInformation)        ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Item Discountable Amount missing within group and Discount Code refers to a Discount Rate");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }


      /* This indicates if more than 1discount is present for the call */
      BCT.DISCOUNT_INFORMATION_COUNT    = BCT.DISCOUNT_INFORMATION_COUNT + 1;
   }
}

void ReadThreeGcamelDestination(struct ThreeGcamelDestination* threeGcamelDestination)
{
   unsigned char CamelDestinationNumber[87];  /* AddressStringDigits */
   int ReturnValue = 0 ;
   int  lValidateFlag = 0    ;

   INIT_STR(stContext.ThreeGcamelDestination) ;
   sprintf(stContext.ThreeGcamelDestination,"%s;431:0:L",stContext.CamelServiceUsed);
   fnRemTrailSpaces(stContext.ThreeGcamelDestination) ;

   gCamelDestNumberFlag = 0 ;

   if(threeGcamelDestination->choiceId == THREEGCAMELDESTINATION_CAMELDESTINATIONNUMBER)
   {
      
       INIT_STR(stContext.CamelDestinationNumber) ;
       sprintf(stContext.CamelDestinationNumber,"%s;404:0:L",stContext.ThreeGcamelDestination);
       fnRemTrailSpaces(stContext.CamelDestinationNumber) ;

      if(NOT_NULL(threeGcamelDestination->a.camelDestinationNumber))
      {
         fnDconvhx(threeGcamelDestination->a.camelDestinationNumber->octetLen,
                   threeGcamelDestination->a.camelDestinationNumber->octs,
                   CamelDestinationNumber,'S');
         fnRemTrailSpaces(CamelDestinationNumber);
         strcpy(BCT.CAMEL_DESTINATION_NUMBER,CamelDestinationNumber);

         gCamelDestNumberFlag = 1 ;

         ReturnValue = fnCheckSyntax(BCT.CAMEL_DESTINATION_NUMBER,"DX") ;
         if(ReturnValue != 0)
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 10                               ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 404                          ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC")  ;
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CamelDestinationNumber")                 ;
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CamelDestinationNumber) ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CAMEL_DESTINATION_NUMBER);
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0;
         }

         ReturnValue = fnCountryCodeCheck(BCT.CAMEL_DESTINATION_NUMBER) ;
         if(ReturnValue != 0)
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 20                               ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 404                          ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC")  ;
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CamelDestinationNumber")                 ;
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CamelDestinationNumber) ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range or number does not start with a valid country code as listed in E.164 Assigned Country Codes");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CAMEL_DESTINATION_NUMBER);
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0;
         }

      fnRemTrailSpaces(gMobilePrfx);      
          if(strcmp(CalledNumberPrefix,gMobilePrfx)==0)
         {
  
          if(BCT.CALL_TYPE_LEVEL1!=1)
           {
                  REI.ERROR_CODE[gRejectedErrorNo]  = 201              ;
                REI.APPLICATION_TAG[gRejectedErrorNo] =407             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")      ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC")  ;
                             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CamelDestinationNumber")               ;
                             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallTypeGroup,"259:0:L")      ;
                             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Camel destination Number is not inline with CallTypeLevel1");
                             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CAMEL_DESTINATION_NUMBER);
                             gRejectedErrorNo++ ;
                         }

                         ReturnValue = 0 ;
              }
            }
           
 else if (strcmp(CalledNumberPrefix,gMobilePrfx)!=0)
   {

  if(BCT.CALL_TYPE_LEVEL1!=2)
    {
            REI.ERROR_CODE[gRejectedErrorNo]  = 201                  ;
            REI.APPLICATION_TAG[gRejectedErrorNo] = 407             ;
            strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
            lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC")  ;
                             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CamelDestinationNumber")               ;
                             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallTypeGroup,"259:0:L")      ;
                             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Camel destination Number is not inline with CallTypeLevel1");
                             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CAMEL_DESTINATION_NUMBER);
                             gRejectedErrorNo++ ;
                         }

                        ReturnValue = 0 ;
                     }
                  }



       if((BCT.CALL_TYPE == 2) && (strcmp(BCT.BASIC_SERVICE_CODE,"12") != 0) && (gDestinationFlag != 0))
         {
            if((gCamelDestNumberFlag==0) && (gCalledNumberFlag==0))
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 41                             ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 89                          ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC")  ;
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Destination")                 ;
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.Destination)   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Item Called Number not present and item CAMEL Destination Number not present");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                    gRejectedErrorNo++ ;
                }
            }

         }

      }
   }


   if((BCT.CALL_TYPE == 2) && (gCamelDestNumberFlag==0) && (strcmp(BCT.SERVICE_CODE,"005") != 0) && (strcmp(BCT.SERVICE_CODE,"305") != 0) )
   {
       REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
       REI.APPLICATION_TAG[gRejectedErrorNo] = 57                          ;
       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
       if(lValidateFlag == 0)
       {
           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC")  ;
           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CamelServiceUsed")                 ;
           strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CamelServiceUsed)   ;
           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"CAMEL Destination Number missing within group although number was modified by CAMEL (logical group 3G CAMEL Destination)");
           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
           gRejectedErrorNo++ ;
       }
   }

   if( ((strcmp(BCT.SERVICE_CODE,"005") == 0) || (strcmp(BCT.SERVICE_CODE,"305") != 0))  && (gCamelDestNumberFlag==1) )
   {
       REI.ERROR_CODE[gRejectedErrorNo]  = 36                             ;
       REI.APPLICATION_TAG[gRejectedErrorNo] = 57                          ;
       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
       if(lValidateFlag == 0)
       {
           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS")  ;
           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CamelServiceUsed")                 ;
           strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CamelServiceUsed)   ;
           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"CAMEL Destination Number present within group (logical group 3G CAMEL Destination)");
           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
           gRejectedErrorNo++ ;
       }
   }

   gGPRSDestNumberFlag = 0 ;

   if(threeGcamelDestination->choiceId == THREEGCAMELDESTINATION_GPRSDESTINATION)
   {
      gGPRSDestNumberFlag = 1 ;
      if(NOT_NULL(threeGcamelDestination->a.gprsDestination))
      {
         CSU.ThreeGcamelDestination.GPRSDESTINATION = 1;
         if(ASNOCTS_PRESENT(&threeGcamelDestination->a.gprsDestination->accessPointNameNI))
         {
            strcpy(BCT.CAMEL_APN_NI,threeGcamelDestination->a.gprsDestination->accessPointNameNI.octs);
         }

         if(ASNOCTS_PRESENT(&threeGcamelDestination->a.gprsDestination->accessPointNameOI))
         {
            strcpy(BCT.CAMEL_APN_OI,threeGcamelDestination->a.gprsDestination->accessPointNameOI.octs);
         }
      }
   }

   if((BCT.CALL_TYPE == 1) || (BCT.CALL_TYPE == 2)) 
   {
      if((gGPRSDestNumberFlag == 1) && (strcmp(BCT.SERVICE_CODE,"005") != 0) &&  (strcmp(BCT.SERVICE_CODE,"305") != 0) )
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 35                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 57                          ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC")  ;
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CamelServiceUsed")                 ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CamelServiceUsed)   ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"GPRS Destination present within group (logical group 3G CAMEL Destination)");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }
   }

}


/* CamelService can be invoked in MOC/MTC/SMSMO/SMSMT/GPRS */
void ReadCamelServiceUsed(struct CamelServiceUsed* camelServiceUsed)
{
   int  TICount=0;  /* Count for TaxInformation within ChargeInformation   */
   TaxInformation *TI;
   int ErrorReturnValue = 0 ;
   int SetError = 0 ;
   int ReturnValue = 0;
   char TempNumtoChar [10]   ;
   int CamelExchRateCodeFlag = 0 ;
   int CDRCamelServiceLevel = 0 ;
   int  lValidateFlag = 0    ;

   INIT_STR(stContext.CamelServiceUsed) ;
   sprintf(stContext.CamelServiceUsed,"%s;57:0:L",stContext.CallEventType);
   fnRemTrailSpaces(stContext.CamelServiceUsed) ;


   BCT.CAMEL_USED_FLAG = 1;

   if(NOT_NULL(camelServiceUsed->camelServiceLevel))
   {
       BCT.CAMEL_SERVICE_LEVEL = *camelServiceUsed->camelServiceLevel;

       CDRCamelServiceLevel = 1;

       /* CamelServiceLevel : Syntax Error Check */
       sprintf (TempNumtoChar,"%d", BCT.CAMEL_SERVICE_LEVEL);
       ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
       if(ReturnValue != 0)
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 56             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CamelServiceLevel") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CamelServiceUsed,"56:0:L")   ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
               gRejectedErrorNo++ ;
           }

           ReturnValue = 0 ;
       }


       /* TotalCallEventDuration : Value Out of Range */

       if ((BCT.CAMEL_SERVICE_LEVEL < 0 )  || (BCT.CAMEL_SERVICE_LEVEL > 3))
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 20             ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 56        ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")  ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CamelServiceLevel") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CamelServiceUsed,"56:0:L")   ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
               gRejectedErrorNo++ ;
           }
           ReturnValue = 0 ;
       }

   }

   if(NOT_NULL(camelServiceUsed->camelServiceKey))
   {
      BCT.CAMEL_SERVICE_KEY = *camelServiceUsed->camelServiceKey;
   }

   if(NOT_NULL(camelServiceUsed->defaultCallHandling))
   {
      BCT.CAMEL_DEFAULT_CALL_HANDLING = *camelServiceUsed->defaultCallHandling;

      if((BCT.CAMEL_DEFAULT_CALL_HANDLING != 0) && (BCT.CAMEL_DEFAULT_CALL_HANDLING !=1))
      {
         BCT.CAMEL_DEFAULT_CALL_HANDLING = 0;
      }
   }

   if(NOT_NULL(camelServiceUsed->exchangeRateCode))
   {
      BCT.CAMEL_EXCHANGE_RATE_CODE = *camelServiceUsed->exchangeRateCode;

      CamelExchRateCodeFlag = 1 ;


      /* ExchangeRateCode : Syntax Error Check */
      sprintf (TempNumtoChar,"%d",BCT.CAMEL_EXCHANGE_RATE_CODE);
      ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
      if(ReturnValue != 0)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 105             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ExchangeRateCode") ;
              sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CamelServiceUsed,"105:0:L")   ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
              gRejectedErrorNo++ ;
          }

          ReturnValue = 0 ;
      }

   }
    gTaxListFlag=0;
   /* Loop through the TaxInformationList */
   if(NOT_NULL(camelServiceUsed->taxInformation))
   {
     gTaxListFlag=1;
      FOR_EACH_LIST_ELMT(TI,camelServiceUsed->taxInformation)
      {
         TICount = 0;


         INIT_STR(stContext.CamelTaxInformation) ;
         sprintf(stContext.CamelTaxInformation,"%s;214:%d:L;213:0:L",stContext.CamelServiceUsed,TICount+1);
         fnRemTrailSpaces(stContext.CamelTaxInformation) ;


         if(NOT_NULL(TI->taxCode))
         {
             BCT.CAMEL_TAX_CODE          = *TI->taxCode;

             /* TaxCode : Syntax Error Check */
             sprintf (TempNumtoChar,"%d",BCT.CAMEL_TAX_CODE);
             ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
             if(ReturnValue != 0)
             {
                 REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
                 REI.APPLICATION_TAG[gRejectedErrorNo] = 212             ;
                 strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                 lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                 if(lValidateFlag == 0)
                 {
                     strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
                     strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxCode");
                     sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CamelTaxInformation,"212:0:L")   ;
                     fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                     strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                     strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                     gRejectedErrorNo++ ;
                 }
                 ReturnValue = 0 ;
             }

         }
         else
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 213                          ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxInformation")               ;
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CamelTaxInformation)   ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Tax Rate Code missing within group");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                 gRejectedErrorNo++ ;
             }
         }


         if(NOT_NULL(TI->taxValue))
         {
            BCT.CAMEL_TAX_VALUE         = BCT.CAMEL_TAX_VALUE + *TI->taxValue;


            /* TaxValue : Syntax Error Check */
            sprintf (TempNumtoChar,"%d",BCT.CAMEL_TAX_VALUE);
            ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 397             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxValue");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CamelTaxInformation,"397:0:L")   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }


            /* Taxvalue : Value Out of Range */

            if (BCT.CAMEL_TAX_VALUE < 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 397             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxValue");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CamelTaxInformation,"397:0:L")   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }

         }
         else
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 31              ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 213         ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")   ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxInformation")               ;
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CamelTaxInformation)   ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Tax Value missing within group");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                 gRejectedErrorNo++ ;
             }
         }


         if(NOT_NULL(TI->taxableAmount))
         {
            BCT.CAMEL_TAXABLE_AMOUNT    = BCT.CAMEL_TAXABLE_AMOUNT + *TI->taxableAmount;


            /* TaxableAmount : Syntax Error Check */
            sprintf (TempNumtoChar,"%d",BCT.CAMEL_TAXABLE_AMOUNT);
            ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 398             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxableAmount");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CamelTaxInformation,"398:0:L")   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }


            /* TaxableAmount : Value Out of Range */

            if (BCT.CAMEL_TAXABLE_AMOUNT <= 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 398             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxableAmount");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CamelTaxInformation,"398:0:L")   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }

         }

         TICount++;
      }

      /* Indicates total Tax applied on the Camel Invocation Fee */
      BCT.CAMEL_TAX_INFORMATION_COUNT = TICount;

   }

   if(NOT_NULL(camelServiceUsed->discountInformation))
   {

      INIT_STR(stContext.CamelDiscountInformation) ;
      sprintf(stContext.CamelDiscountInformation,"%s;96:0:L",stContext.CamelServiceUsed);
      fnRemTrailSpaces(stContext.CamelDiscountInformation) ;


      if(NOT_NULL(camelServiceUsed->discountInformation->discountCode))
      {
         BCT.CAMEL_DISCOUNT_CODE =
         *camelServiceUsed->discountInformation->discountCode;

          /* DiscountCode : Syntax Error Check */
          sprintf (TempNumtoChar,"%d",BCT.CAMEL_DISCOUNT_CODE);
          ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
          if(ReturnValue != 0)
          {
              REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 91             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DiscountCode");
                  sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CamelDiscountInformation,"91:0:L")   ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
          }

      }
      else
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 96                         ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DiscountInformation")               ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CamelDiscountInformation)   ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Discount Code missing within group");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }


      if(NOT_NULL(camelServiceUsed->discountInformation->discount))
      {
         BCT.CAMEL_DISCOUNT = *camelServiceUsed->discountInformation->discount;

         /* Discount : Syntax Error Check */
         sprintf (TempNumtoChar,"%d",BCT.CAMEL_DISCOUNT);
         ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
         if(ReturnValue != 0)
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 412             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Discount");
                 sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CamelDiscountInformation,"412:0:L")   ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0 ;
         }


         /* Discount : Value Out of Range */

         if (BCT.CAMEL_DISCOUNT < 0)
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 412             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Discount");
                 sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CamelDiscountInformation,"412:0:L")   ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0 ;
         }

      }
      else
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 96                         ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DiscountInformation")               ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CamelDiscountInformation)   ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Item Discount Value missing within group and Discount Code refers to a Discount Rate");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }


      if(NOT_NULL(camelServiceUsed->discountInformation->discountableAmount))
      {
         BCT.DISCOUNTABLE_AMT =
         *camelServiceUsed->discountInformation->discountableAmount;

         /* DiscountableAmount : Syntax Error Check */
         sprintf (TempNumtoChar,"%d",BCT.DISCOUNTABLE_AMT);
         ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
         if(ReturnValue != 0)
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 423             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DiscountableAmount");
                 sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CamelDiscountInformation,"423:0:L")   ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0 ;
         }


         /* DiscountableAmount : Value Out of Range */

         if (BCT.DISCOUNTABLE_AMT <= 0)
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 423             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DiscountableAmount");
                 sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CamelDiscountInformation,"423:0:L")   ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0 ;
         }

      }
      else
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 96                         ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"DiscountInformation")               ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CamelDiscountInformation)   ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Item Discountable Amount missing within group and Discount Code refers to a Discount Rate");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }


   }

   if(NOT_NULL(camelServiceUsed->camelInvocationFee))
   {
       BCT.CAMEL_INVOCATION_FEE = *camelServiceUsed->camelInvocationFee;

       /* CamelInvocationFee : Syntax Error Check */
       sprintf (TempNumtoChar,"%d",BCT.CAMEL_INVOCATION_FEE);
       ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
       if(ReturnValue != 0)
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 422             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CamelInvocationFee");
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CamelServiceUsed,"422:0:L")   ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
               gRejectedErrorNo++ ;
           }
           ReturnValue = 0 ;
       }


       /* Discount : Value Out of Range */

       if (BCT.CAMEL_INVOCATION_FEE < 0)
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 422             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CamelInvocationFee");
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CamelServiceUsed,"422:0:L")   ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
               gRejectedErrorNo++ ;
           }
           ReturnValue = 0 ;
       }


       if((CamelExchRateCodeFlag ==0) && (BCT.CAMEL_INVOCATION_FEE > 0))
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 40                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 57              ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CamelServiceUsed");
               strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CamelServiceUsed)   ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Exchange Rate Code missing within the group and CAMEL Invocation Fee is greater than zero");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
               gRejectedErrorNo++ ;
           }
       }

       if((CDRCamelServiceLevel == 0) && (BCT.CAMEL_INVOCATION_FEE > 0))
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 30                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 57              ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CamelServiceUsed");
               strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CamelServiceUsed)   ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Item CAMEL Service Level missing within group although CAMEL Invocation Fee is present and greater than zero");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
               gRejectedErrorNo++ ;
           }
       }
   }

   if(NOT_NULL(camelServiceUsed->threeGcamelDestination))
   {
      ReadThreeGcamelDestination(camelServiceUsed->threeGcamelDestination);
   }

}


int ReadSUP(struct SupplServiceEvent *supplServiceEvent)
{
   void *Pointer;
   BasicServiceCode *BSC;
   unsigned char Imsi[46];      /* AddressStringDigits */
   unsigned char Msisdn[17];    /* AddressStringDigits */
   unsigned char Imei[16];
   int ErrorReturnValue = 0 ;
   int SetError = 0 ;
   int ReturnValue = 0;
   char TempNumtoChar [40]   ;
   char SupplServCode[40] ;
   int  ErrorCount = 0       ;
   int  CDRRecordEntityCode = 0;
   int i=0 ;
   int  lValidateFlag = 0    ;
   unsigned char Temp_Imsi[26];      /* AddressStringDigits */

   gErrorNode = 11 ;


   INIT_STR(stContext.CallEventType) ;
   sprintf(stContext.CallEventType,"%s;11:0:L",stContext.CallEventDetails);
   fnRemTrailSpaces(stContext.CallEventType) ;


   BCT.CALL_TYPE = 2;
   strcpy(BCT.SERVICE_CODE,"006") ;

   /* Read Chargeable Subscriber */
   if(NOT_NULL(supplServiceEvent->chargeableSubscriber))
   {

      INIT_STR(stContext.ChargeableSubscriber) ;
      sprintf(stContext.ChargeableSubscriber,"%s;427:0:L",stContext.CallEventDetails) ;
      fnRemTrailSpaces(stContext.ChargeableSubscriber) ;

      if(supplServiceEvent->chargeableSubscriber->choiceId == CHARGEABLESUBSCRIBER_SIMCHARGEABLESUBSCRIBER)
      {
         if(NOT_NULL(supplServiceEvent->chargeableSubscriber->a.simChargeableSubscriber))
         {
            if(ASNOCTS_PRESENT(&supplServiceEvent->chargeableSubscriber->a.simChargeableSubscriber->imsi))
            {
               fnDconvhx(supplServiceEvent->chargeableSubscriber->a.simChargeableSubscriber->imsi.octetLen,
                         supplServiceEvent->chargeableSubscriber->a.simChargeableSubscriber->imsi.octs,
                         Imsi,
                         'S');
               Imsi[15]='\0';
               fnRemTrailSpaces(Imsi);
               BCT.IMSI = atof(Imsi);

               ReturnValue = fnCheckSyntax(Imsi,"DI") ;
               if(ReturnValue != 0)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 129             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Imsi") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeableSubscriber,"199:0:L;129:0:L")   ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],Imsi);
                       gRejectedErrorNo++ ;
                   }
  
                   ReturnValue = 0 ;
               }




               fnDconvhx(supplServiceEvent->chargeableSubscriber->a.simChargeableSubscriber->imsi.octetLen,
                      supplServiceEvent->chargeableSubscriber->a.simChargeableSubscriber->imsi.octs,
                      Temp_Imsi,
                      'S');
               fnRemTrailSpaces(Temp_Imsi);
               Temp_Imsi[strlen(Temp_Imsi)]='\0';

               if(strlen(Temp_Imsi) > 15)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 129             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   { 
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Imsi") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeableSubscriber,"199:0:L;129:0:L")   ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],Temp_Imsi);
                       gRejectedErrorNo++ ;
                   }
 
                   ReturnValue = 0 ;
               }

               ReturnValue = fnImsiPrfxCheck(BCT.IMSI);

               if(ReturnValue != 0)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 200                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 129             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Imsi") ;
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeableSubscriber,"199:0:L;129:0:L")   ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"First characters are different from home operators MCC + MNC, or not as bilaterally agreed");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],Imsi);
                        gRejectedErrorNo++ ;
                   }
                   ReturnValue = 0 ;
               }


            }

            if(ASNOCTS_PRESENT(&supplServiceEvent->chargeableSubscriber->a.simChargeableSubscriber->msisdn))
            {
               fnDconvhx(supplServiceEvent->chargeableSubscriber->a.simChargeableSubscriber->msisdn.octetLen,
                         supplServiceEvent->chargeableSubscriber->a.simChargeableSubscriber->msisdn.octs,
                         Msisdn,
                         'S');
               fnRemTrailSpaces(Msisdn);
               strcpy(BCT.MSISDN,Msisdn);

               ReturnValue = fnCountryCodeCheck(BCT.MSISDN) ;
               if(ReturnValue != 0)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  =   23                            ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 152                          ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/SS/GPRS")  ;
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Msisdn")                 ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeableSubscriber,"199:0:L;152:0:L")   ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Number not represented in international format and MSISDN expected in accordance with roaming agreement");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.MSISDN);
                       gRejectedErrorNo++ ;
                   }
                   ReturnValue = 0;
               }

            }
/*            else
            {
               REI.ERROR_CODE[gRejectedErrorNo]  = 32                               ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 427                          ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"SS")         ;
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeableSubscriber") ;
                   strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargeableSubscriber)   ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"MSISDN missing within group but expected in accordance with roaming agreement");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                   gRejectedErrorNo++ ;
               }
            }
*/
         }
      }
   }
   else
   {
       REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
       REI.APPLICATION_TAG[gRejectedErrorNo] = 11                         ;
       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
       if(lValidateFlag == 0)
       {
           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"SS")  ;
           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SupplServiceEvent")               ;
           strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargeableSubscriber)        ;
           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Chargeable Subscriber missing within group");
           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
           gRejectedErrorNo++ ;
       }
   }


   /* Read Location Information */
   if(NOT_NULL(supplServiceEvent->locationInformation))
   {

      INIT_STR(stContext.LocationInformation);
      sprintf(stContext.LocationInformation,"%s;138:0:L",stContext.CallEventType) ;
      fnRemTrailSpaces(stContext.LocationInformation) ;

      if(NOT_NULL(supplServiceEvent->locationInformation->networkLocation))
      {
         if(NOT_NULL(supplServiceEvent->locationInformation->networkLocation->recEntityCode))
         {
            BCT.RECORDING_ENTITY_CODE = *supplServiceEvent->locationInformation->networkLocation->recEntityCode;

            /* RecEntityCode : Syntax Error Check */
            sprintf (TempNumtoChar,"%d", BCT.RECORDING_ENTITY_CODE);
            ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 184             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                { 
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"SS");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityCode") ;
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.LocationInformation,"156:0:L;184:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }

                ReturnValue = 0 ;
            }

            CDRRecordEntityCode = 0;

            for(i=0;i<gRecEntityInfoCount;i++)
            {
                if(BCT.RECORDING_ENTITY_CODE == NI.RecEntityInfo[i].RecEntityCode)
                {
                   CDRRecordEntityCode = 1;
                    break;
                }
            }


            if(CDRRecordEntityCode == 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 100                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 184             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                { 
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/SS/SCU/GPRS/LCS");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityCode") ;
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.LocationInformation,"156:0:L;184:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Specified recording entity code not defined in the Recording Entity Information");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }

         }
         else
         {
            REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
            REI.APPLICATION_TAG[gRejectedErrorNo] = 156                         ;
            strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
            lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
            if(lValidateFlag == 0)
            { 
                strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"SS")  ;
                strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"NetworkLocation")               ;
                sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.LocationInformation,"156:0:L")        ;
                fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Recording Entity Code missing within group");
                strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                gRejectedErrorNo++ ;
            }
         }


         if(NOT_NULL(supplServiceEvent->locationInformation->networkLocation->locationArea))
         {
            BCT.LOCATION_AREA = *supplServiceEvent->locationInformation->networkLocation->locationArea;
         }

         if(NOT_NULL(supplServiceEvent->locationInformation->networkLocation->cellId))
         {
            BCT.CELLID = *supplServiceEvent->locationInformation->networkLocation->cellId;
         }
      }
      else
      {
         REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
         REI.APPLICATION_TAG[gRejectedErrorNo] = 138                         ;
         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
         if(lValidateFlag == 0)
         { 
             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"SS")  ;
             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"LocationInformation")               ;
             strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.LocationInformation)        ;
             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Network Location missing within group");
             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
             gRejectedErrorNo++ ;
         }
      }

   }
   else
   {
       REI.ERROR_CODE[gRejectedErrorNo]  = 33                             ;
       REI.APPLICATION_TAG[gRejectedErrorNo] = 11                         ;
       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
       if(lValidateFlag == 0)
       { 
           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"SS")  ;
           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SupplServiceEvent")               ;
           strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargeableSubscriber)        ;
           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Location Information missing within group");
           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
           gRejectedErrorNo++ ;
       }
   }


   /* Read Equipment Identifier */
   if(NOT_NULL(supplServiceEvent->equipmentIdentifier))
   {
      if(supplServiceEvent->equipmentIdentifier->choiceId == IMEIORESN_IMEI)
      {
         if(NOT_NULL(supplServiceEvent->equipmentIdentifier->a.imei))
         {
            fnDconvhx(supplServiceEvent->equipmentIdentifier->a.imei->octetLen,
                      supplServiceEvent->equipmentIdentifier->a.imei->octs,Imei,'S');
            fnRemTrailSpaces(Imei);
            strcpy(BCT.IMEI,Imei);
         }
      }
   }

   INIT_STR(stContext.SupplServiceUsed);
   sprintf(stContext.SupplServiceUsed,"%s;206:0:L",stContext.CallEventType) ;
   fnRemTrailSpaces(stContext.SupplServiceUsed) ;

   /* Read SupplimentaryServiceUsed */
   if(NOT_NULL(supplServiceEvent->supplServiceUsed))
   {

      if(ASNOCTS_PRESENT(&supplServiceEvent->supplServiceUsed->supplServiceCode))
      {
         strcpy(BCT.SUPPLIMENTARY_SERVICE_CODE,supplServiceEvent->supplServiceUsed->supplServiceCode.octs);

         //sprintf (TempNumtoChar,"%d", BCT.SUPPLIMENTARY_SERVICE_CODE);
	 /*Changed to consider alphanumeric supplementary service codes like 2A, 2B etc*/ 
         sprintf (TempNumtoChar,"%s", BCT.SUPPLIMENTARY_SERVICE_CODE);

         ReturnValue = fnCheckSyntax(TempNumtoChar,"BT") ;
         if(ReturnValue != 0)
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 209             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {  
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"SS");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SupplServiceCode");
                 sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.SupplServiceUsed,"209:0:L") ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0 ;
         }

         Pointer = NULL;
         Pointer = strstr("00:10:11:12:13:14:20:21:28:29:2A:2B:30:31:40:41:42:43:50:51:60:61:70:71:72:80:81:90:91:92:93:94:99:9A:9B:FF",TempNumtoChar);
         if(Pointer == NULL)
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 209             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {  
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"SS");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SupplServiceCode");
                 sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.SupplServiceUsed,"209:0:L") ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0 ;
         }

      }
      else
      {
         REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
         REI.APPLICATION_TAG[gRejectedErrorNo] = 206                        ;
         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
         if(lValidateFlag == 0)
         { 
             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"SS")  ;
             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SupplServiceUsed")               ;
             strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.LocationInformation)        ;
             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Supplementary Service Code missing within group");
             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
             gRejectedErrorNo++ ;
         }
      }


      if(NOT_NULL(supplServiceEvent->supplServiceUsed->supplServiceActionCode))
      {
         BCT.SUPPLIMENTARY_ACTION_CODE = *supplServiceEvent->supplServiceUsed->supplServiceActionCode;

         sprintf (TempNumtoChar,"%d", BCT.SUPPLIMENTARY_ACTION_CODE);

         ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
         if(ReturnValue != 0)
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 208             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             { 
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"SS");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SupplServiceActionCode");
                 sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.SupplServiceUsed,"208:0:L") ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                 gRejectedErrorNo++ ;
             }
             ReturnValue = 0 ;
         }

         sprintf (SupplServCode,"%d", BCT.SUPPLIMENTARY_SERVICE_CODE);

         if(strcmp(SupplServCode,"FF") != 0)
         {
            if((BCT.SUPPLIMENTARY_ACTION_CODE < 0) || (BCT.SUPPLIMENTARY_ACTION_CODE > 6))
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 208             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                { 
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"SS");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SupplServiceActionCode");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.SupplServiceUsed,"208:0:L") ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range for supplementary service where associated Supplementary Service Code is for a supplementary service");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }
         }
         else
         { 
            if(BCT.SUPPLIMENTARY_ACTION_CODE != 7)
            {
               REI.ERROR_CODE[gRejectedErrorNo]  = 22                  ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 208             ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               { 
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"SS");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SupplServiceActionCode");
                   sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.SupplServiceUsed,"208:0:L") ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range for USSD message where associated Supplementary Service Code is for USSD message");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                   gRejectedErrorNo++ ;
               }
               ReturnValue = 0 ;
             }
          }


      }
      else
      {
         REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
         REI.APPLICATION_TAG[gRejectedErrorNo] = 206                        ;
         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
         if(lValidateFlag == 0)
         { 
             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"SS")  ;
             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SupplServiceUsed")               ;
             strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.LocationInformation)        ;
             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Action Code missing within group");
             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
             gRejectedErrorNo++ ;
         }
      }


      if(NOT_NULL(supplServiceEvent->supplServiceUsed->chargingTimeStamp))
      {
         INIT_STR(stContext.CallEventStartTimeStamp) ;
         sprintf(stContext.CallEventStartTimeStamp,"%s;74:0:L",stContext.SupplServiceUsed) ;
         fnRemTrailSpaces(stContext.CallEventStartTimeStamp) ;

         if(ASNOCTS_PRESENT(&supplServiceEvent->supplServiceUsed->chargingTimeStamp->localTimeStamp))
         {
            strcpy(BCT.CALL_DATE,supplServiceEvent->supplServiceUsed->chargingTimeStamp->localTimeStamp.octs);

            /* CallEventStartTimeStamp : Syntax Error Check */
            ReturnValue = fnCheckSyntax(BCT.CALL_DATE,"DI") ;
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 10                   ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 74               ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                { 
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"SS");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargingTimeStamp") ;
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventStartTimeStamp,"16:0:L")   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CALL_DATE);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }

            /* CallEventStartTimeStamp : Value Out of Range Check */
            ReturnValue = fnDateRangeCheck(BCT.CALL_DATE);
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 20             ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 74         ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")  ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                { 
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"SS");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargingTimeStamp") ;
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventStartTimeStamp,"16:0:L")   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CALL_DATE);
                    gRejectedErrorNo++ ;
                }

                ReturnValue = 0 ;
            }

         }

         if(NOT_NULL(supplServiceEvent->supplServiceUsed->chargingTimeStamp->utcTimeOffsetCode))
         {
            BCT.UTC_OFFSET_CODE = *supplServiceEvent->supplServiceUsed->chargingTimeStamp->utcTimeOffsetCode;


            /* UtcTimeOffsetCode : Syntax Error Check */
            sprintf (TempNumtoChar,"%d", BCT.UTC_OFFSET_CODE);
            ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 232             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                { 
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"SS");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"UtcTimeOffsetCode") ;
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventStartTimeStamp,"232:0:L")   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }
         }
         else
         {
            REI.ERROR_CODE[gRejectedErrorNo]  = 30                  ;
            REI.APPLICATION_TAG[gRejectedErrorNo] = 74              ;
            strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
            lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
            if(lValidateFlag == 0)
            { 
                strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"SS");
                strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargingTimeStamp") ;
                strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventStartTimeStamp)   ;
                fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory associated item UTC Time Offset Code missing");
                strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                gRejectedErrorNo++ ;
            }

            ReturnValue = 0 ;
         }
      }
      else
      {
         REI.ERROR_CODE[gRejectedErrorNo]  = 36                             ;
         REI.APPLICATION_TAG[gRejectedErrorNo] = 206                        ;
         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
         if(lValidateFlag == 0)
         { 
             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"SS")  ;
             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SupplServiceUsed")               ;
             strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.LocationInformation)        ;
             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Item Charging Timestamp missing within group");
             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
             gRejectedErrorNo++ ;
         }
      }

   } 
   else
   {
       REI.ERROR_CODE[gRejectedErrorNo]  = 36                             ;
       REI.APPLICATION_TAG[gRejectedErrorNo] = 11                         ;
       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
       if(lValidateFlag == 0)
       { 
           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"SS")  ;
           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SupplServiceEvent")               ;
           strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargeableSubscriber)        ;
           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Supplementary Service Used missing within group");
           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
           gRejectedErrorNo++ ;
       }
   }

   if((strcmp(gCheckCallAgeFlag,"Y") == 0) && (strcmp(g_CdrStartDate,BCT.CALL_DATE) > 0))
   {

      REI.ERROR_CODE[gRejectedErrorNo]  = 261            ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 11         ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      { 
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"SS");
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SupplServiceEvent") ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)   ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Call older than allowed by BARG in 'Exceptional Situations' in BARG PRD BA.08");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CALL_DATE);
          gRejectedErrorNo++ ;
      }
   }



   /* Read Charge Information */
   if(NOT_NULL(supplServiceEvent->supplServiceUsed->chargeInformation))
   {
      ReadChargeInformationList(supplServiceEvent->supplServiceUsed->chargeInformation,0);

   }

   stSUP1 = supplServiceEvent;

   if((gRejectedErrorNo > 0) && (gFatalErrorCount == 0) && (strcmp(gGenerateFilesFlg,"N")!=0))
   {
       gErrorCDRsCount = gErrorCDRsCount + 1 ;
       gErrorCDRsCharge = gErrorCDRsCharge + BCT.CHARGE + BCT.CAMEL_INVOCATION_FEE ;
       gErrorCDRsTax = gErrorCDRsTax + BCT.TAX_VALUE  ;
       gErrorCDRsDiscount = gErrorCDRsDiscount + BCT.DISCOUNT  ;
       gErrorCDRsDuration = gErrorCDRsDuration + BCT.CALL_DURATION ;
       gCDRErrorFlag = 1 ;

       for(ErrorCount=0; ErrorCount<gRejectedErrorNo; ErrorCount++)
       {
           ErrorReturnValue = SetBulkErrorDetails(gBulkErrorDetailsIndex, ErrorCount,11)   ;
           if(ErrorReturnValue == -1)
           {
              return -1;
           }
       }
   }
   gRejectedErrorNo = 0;

   return 0;

}


int  ReadNotification()
{
   char FileSequenceNumber[6];
   int  FieldLength = 0      ;    
   int  ReturnValue = 0 ;
   long SeqNuminFileName = 0 ;
   char TempNumtoChar [10]   ;
   int  ErrorReturnValue = 0 ;
   int  i = 0                ; 
   int  ErrorCount = 0       ;
   int  lValidateFlag = 0    ;

   gErrorNode = 2;

 
   gRejectedErrorNo = 0;
   /* APPLICATION_TAG:ITEM_OCCURENCE:ITEM_LEVEL */


   /* Sender : AsciiString */
   if(ASNOCTS_PRESENT(&DIC.a.notification->sender))
   {
      strcpy(BCI.Sender,DIC.a.notification->sender.octs);
      fnRemTrailSpaces(BCI.Sender)     ;


      
      /* Sender : Syntax Error Check */
      ReturnValue = fnCheckSyntax(BCI.Sender,"BT") ;
      if(ReturnValue != 0)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 196             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
          lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Sender") ;
              /* strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;196:0:L;169:0:L") ;*/
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;196:0:L") ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.Sender);
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
      }

      /* Sender : Value Out Of Range Error Check */
      FieldLength = 0 ;
      FieldLength = strlen(BCI.Sender) ;
    
      if(FieldLength != 5)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 196             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
          lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Sender") ;
              /* strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;196:0:L;169:0:L") ;*/
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;196:0:L") ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.Sender);
              gRejectedErrorNo++ ;
          }

          ReturnValue = 0 ;
      }


      /* Sender : Compare the BCI Sender with Sender on the FileName */
      if(strcmp(BCI.Sender,gFileVplmnCode) != 0)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 100                 ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 196             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
          lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Sender") ;
              /* strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;196:0:L;169:0:L") ;*/
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;196:0:L") ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"The item does not match the Sender on the filename");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.Sender);
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
      }

      if(strcmp(BCI.Sender,gFileVplmnCode) != 0)
      {
         gValidateVPLMNPrefix = 0 ;
         gValidateVPLMNPrefix = fnCheckPLMNPrefix(BCI.Sender) ;
         if(gValidateVPLMNPrefix != 0)
         {
            strcpy(BCI.Sender,gFileVplmnCode);
         }
      }
      
   }
   else
   {
      strcpy(BCI.Sender,gFileVplmnCode);
      REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 2                          ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
      lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Notification")      ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L")       ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Sender missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }

   /* Recipient : AsciiString */
   if(ASNOCTS_PRESENT(&DIC.a.notification->recipient))
   {
      strcpy(BCI.Recipient,DIC.a.notification->recipient.octs);
      fnRemTrailSpaces(BCI.Recipient) ;


      /* Recipient : Syntax Error Check */
      ReturnValue = fnCheckSyntax(BCI.Recipient,"BT") ;
      if(ReturnValue != 0)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 182             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
          lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Recipient") ;
              /* strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;182:0:L;169:0:L") ; */
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;182:0:L") ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.Recipient);
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
      }


      /* Recipient : Value Out Of Range Error Check */
      FieldLength = 0 ;
      FieldLength = strlen(BCI.Recipient) ;

      if(FieldLength != 5)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 182             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
          lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Recipient") ;
              /* strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;182:0:L;169:0:L") ; */
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;182:0:L") ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.Recipient);
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
      }


      /* Recipient : Compare the BCI Recipient with Recipient on the FileName */
      if(strcmp(BCI.Recipient,gFileHplmnCode) != 0)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 100                 ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 182             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
          lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Recipient") ;
              /* strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;182:0:L;169:0:L") ;*/
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;182:0:L") ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"The item does not match the Recipient on the filename");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.Recipient);
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
      }


      if(strcmp(BCI.Recipient,gFileHplmnCode) != 0)
      {
           gValidateHPLMNPrefix = 0 ;
           gValidateHPLMNPrefix = fnCheckPLMNPrefix(BCI.Recipient) ;
           if(gValidateHPLMNPrefix != 0)
           {
              strcpy(BCI.Recipient,gFileHplmnCode);
           }
      }

   }
   else
   {
      strcpy(BCI.Recipient,gFileHplmnCode);
      REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 2                          ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
      lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Notification")      ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L")       ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Recipient missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }

   /* FileTypeIndicator : AsciiString */
   if(ASNOCTS_PRESENT(&DIC.a.notification->fileTypeIndicator))
   {
      strcpy(BCI.FileTypeIndicator,DIC.a.notification->fileTypeIndicator.octs);
      fnRemTrailSpaces(BCI.FileTypeIndicator) ;


      /* FileTypeIndicator : Syntax Error Check */
      ReturnValue = fnCheckSyntax(BCI.FileTypeIndicator,"AL") ;
      if(ReturnValue != 0)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 110             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
          lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FileTypeIndicator") ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;110:0:L") ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.FileTypeIndicator);
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
      }


      /* Recipient : Value Out Of Range Error Check */
      FieldLength = 0 ;
      FieldLength = strlen(BCI.FileTypeIndicator) ;

      if(FieldLength != 1)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 110             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
          lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FileTypeIndicator") ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;110:0:L") ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.FileTypeIndicator);
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
      }

   }
   else
   {
      strcpy(BCI.FileTypeIndicator,"C");
   }


   /* FileSequenceNumber : NumberString */
   if(ASNOCTS_PRESENT(&DIC.a.notification->fileSequenceNumber))
   {
      FileSequenceNumber[0]='\0';
      strcpy(FileSequenceNumber,DIC.a.notification->fileSequenceNumber.octs);
      fnRemTrailSpaces(FileSequenceNumber) ;
    
       /* FileSequenceNumber : Syntax Error Check */
      ReturnValue = fnCheckSyntax(FileSequenceNumber,"DI") ;
      if(ReturnValue != 0)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 109             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
          lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FileSequenceNumber") ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;109:0:L") ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],FileSequenceNumber);
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
      }

      BCI.FileSequenceNumber = atol(FileSequenceNumber);

      if ((BCI.FileSequenceNumber <= 0) || (BCI.FileSequenceNumber > 99999))
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 109             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
          lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FileSequenceNumber") ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;109:0:L") ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],FileSequenceNumber);
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
      }

      SeqNuminFileName = atol(gFileSequenceNumber) ;

     if(BCI.FileSequenceNumber != SeqNuminFileName)
     {
          REI.ERROR_CODE[gRejectedErrorNo]  = 100                 ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 109             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
          lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FileSequenceNumber") ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;109:0:L") ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"The item does not match the File Sequence Number on the filename");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],FileSequenceNumber);
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
     }


   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 2                          ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
      lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Notification")      ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L")       ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item File Sequence Number missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }



   /* FileCreationTimeStamp : DateTimeLong */
   if(NOT_NULL(DIC.a.notification->fileCreationTimeStamp))
   {
      BCIA.FileCreationTimeStamp = 1;

      if(ASNOCTS_PRESENT(&DIC.a.notification->fileCreationTimeStamp->localTimeStamp))
      {
         strcpy(BCI.FileCreationTimeStamp.LocalTimeStamp,
                DIC.a.notification->fileCreationTimeStamp->localTimeStamp.octs);
         fnRemTrailSpaces(BCI.FileCreationTimeStamp.LocalTimeStamp) ;
         
      }

      if(ASNOCTS_PRESENT(&DIC.a.notification->fileCreationTimeStamp->utcTimeOffset))
      {
         strcpy(BCI.FileCreationTimeStamp.UtcTimeOffset,
                DIC.a.notification->fileCreationTimeStamp->utcTimeOffset.octs);
         fnRemTrailSpaces(BCI.FileCreationTimeStamp.LocalTimeStamp) ;
      }
   }

   /* TransferCutOffTimeStamp : DateTimeLong */
   if(NOT_NULL(DIC.a.notification->transferCutOffTimeStamp))
   {
      if(ASNOCTS_PRESENT(&DIC.a.notification->transferCutOffTimeStamp->localTimeStamp))
      {
         strcpy(BCI.TransferCutOffTimeStamp.LocalTimeStamp,
                DIC.a.notification->transferCutOffTimeStamp->localTimeStamp.octs);
         fnRemTrailSpaces(BCI.TransferCutOffTimeStamp.LocalTimeStamp) ;

         ReturnValue = fnCheckSyntax(BCI.TransferCutOffTimeStamp.LocalTimeStamp,"DI") ;
         if(ReturnValue != 0)
         {
            REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
            REI.APPLICATION_TAG[gRejectedErrorNo] = 227             ;
            strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
            lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
            if(lValidateFlag == 0)
            {
                strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
                strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TransferCutOffTimeStamp") ;
                strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;227:0:L;16:0:L") ;
                fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.TransferCutOffTimeStamp.LocalTimeStamp);
                gRejectedErrorNo++ ;
            }
            ReturnValue = 0 ;
         }

         ReturnValue = fnDateRangeCheck(BCI.TransferCutOffTimeStamp.LocalTimeStamp);
         if(ReturnValue != 0)
         {
            REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
            REI.APPLICATION_TAG[gRejectedErrorNo] = 227             ;
            strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
            lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
            if(lValidateFlag == 0)
            {
                strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
                strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TransferCutOffTimeStamp") ;
                strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;227:0:L;16:0:L") ;
                fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.TransferCutOffTimeStamp.LocalTimeStamp);
                gRejectedErrorNo++ ;
            }
            ReturnValue = 0 ;
         }

      }

      if(ASNOCTS_PRESENT(&DIC.a.notification->transferCutOffTimeStamp->utcTimeOffset))
      {
         strcpy(BCI.TransferCutOffTimeStamp.UtcTimeOffset,
                DIC.a.notification->transferCutOffTimeStamp->utcTimeOffset.octs);
         fnRemTrailSpaces(BCI.TransferCutOffTimeStamp.UtcTimeOffset) ;

      }
      else
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 30                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 227             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
          lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
          if(lValidateFlag == 0)
          {
             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TransferCutOffTimeStamp") ;
             strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;227:0:L") ;
             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory associated item UTC Time Offset missing");
             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
             gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
      }

   }

   /* FileAvailableTimeStamp : DateTimeLong */
   if(NOT_NULL(DIC.a.notification->fileAvailableTimeStamp))
   {
      if(ASNOCTS_PRESENT(&DIC.a.notification->fileAvailableTimeStamp->localTimeStamp))
      {
         strcpy(BCI.FileAvailableTimeStamp.LocalTimeStamp,
                DIC.a.notification->fileAvailableTimeStamp->localTimeStamp.octs);
         fnRemTrailSpaces(BCI.FileAvailableTimeStamp.LocalTimeStamp) ;

         /* FileAvailableTimeStamp : Syntax Error Check */
         ReturnValue = fnCheckSyntax(BCI.FileAvailableTimeStamp.LocalTimeStamp,"DI") ;
         if(ReturnValue != 0)
         {
            REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
            REI.APPLICATION_TAG[gRejectedErrorNo] = 107             ;
            strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
            lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
            if(lValidateFlag == 0)
            {
                strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
                strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FileAvailableTimeStamp") ;
                strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;107:0:L;16:0:L") ;
                fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.FileAvailableTimeStamp.LocalTimeStamp);
                gRejectedErrorNo++ ;
            }
            ReturnValue = 0 ;
         }

         ReturnValue = fnDateRangeCheck(BCI.FileAvailableTimeStamp.LocalTimeStamp);
         if(ReturnValue != 0)
         {
            REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
            REI.APPLICATION_TAG[gRejectedErrorNo] = 107             ;
            strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
            lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
            if(lValidateFlag == 0)
            {
                strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
                strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FileAvailableTimeStamp") ;
                strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;107:0:L;16:0:L") ;
                fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.FileAvailableTimeStamp.LocalTimeStamp);
                gRejectedErrorNo++ ;
            }
            ReturnValue = 0 ;
         }

         if(strcmp(BCI.FileAvailableTimeStamp.LocalTimeStamp,BCI.TransferCutOffTimeStamp.LocalTimeStamp) < 0)
         {
            REI.ERROR_CODE[gRejectedErrorNo]  = 100                 ;
            REI.APPLICATION_TAG[gRejectedErrorNo] = 107             ;
            strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
            lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
            if(lValidateFlag == 0)
            {
                strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
                strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FileAvailableTimeStamp") ;
                strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;107:0:L;16:0:L") ;
                fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Timestamp is earlier than the Transfer Cut Off Timestamp");
                strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.FileAvailableTimeStamp.LocalTimeStamp);
                gRejectedErrorNo++ ;
            }
            ReturnValue = 0 ;
         }

         if(strcmp(BCI.FileAvailableTimeStamp.LocalTimeStamp,gSystemDate) > 0)
         {
            REI.ERROR_CODE[gRejectedErrorNo]  = 104                 ;
            REI.APPLICATION_TAG[gRejectedErrorNo] = 107             ;
            strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
            lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
            if(lValidateFlag == 0)
            {
                strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
                strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FileAvailableTimeStamp") ;
                strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;107:0:L;16:0:L") ;
                fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Timestamp is after the file received time at the HPMN");
                strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCI.FileAvailableTimeStamp.LocalTimeStamp);
                gRejectedErrorNo++ ;
            }
            ReturnValue = 0 ;
         }
      }
     

      if(ASNOCTS_PRESENT(&DIC.a.notification->fileAvailableTimeStamp->utcTimeOffset))
      {
         strcpy(BCI.FileAvailableTimeStamp.UtcTimeOffset,
                DIC.a.notification->fileAvailableTimeStamp->utcTimeOffset.octs);
         fnRemTrailSpaces(BCI.FileAvailableTimeStamp.UtcTimeOffset) ;
      }
      else
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 30                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 107             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
          lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"FileAvailableTimeStamp") ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;107:0:L") ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory associated item UTC Time Offset missing");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
      }

 
   }

   /* SpecificationVersionNumber : AsnInt */
   if(NOT_NULL(DIC.a.notification->specificationVersionNumber))
   {
      BCI.SpecificationVersionNumber = *DIC.a.notification->specificationVersionNumber;

      sprintf (TempNumtoChar,"%d",BCI.SpecificationVersionNumber);


      ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
      if(ReturnValue != 0)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 201             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
          lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SpecificationVersionNumber") ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;201:0:L") ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
      }

       /*Added by Anitha for 3.12
           Before if(BCI.SpecificationVersionNumber != 333)*/
       if(BCI.SpecificationVersionNumber != gTapSpecificationVersion)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 201             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
          lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SpecificationVersionNumber") ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;201:0:L") ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
      }

   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 33                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 2                          ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
      lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Notification")      ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L")       ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Specification Version Number missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }



   /* ReleaseVersionNumber : AsnInt */
   if(NOT_NULL(DIC.a.notification->releaseVersionNumber))
   {
      BCI.ReleaseVersionNumber = *DIC.a.notification->releaseVersionNumber;

       sprintf (TempNumtoChar,"%d",BCI.ReleaseVersionNumber);

      ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
      if(ReturnValue != 0)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 189             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
          lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ReleaseVersionNumber") ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;189:0:L") ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
      }

         /*printf("Release version %d",BCI.ReleaseVersionNumber);*/
        /*Added by Anitha for 3.12
           Before if(BCI.ReleaseVersionNumber != 11)*/

      if(BCI.ReleaseVersionNumber != gTapReleaseVersion)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 189             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
          lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ReleaseVersionNumber") ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L;189:0:L") ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
      }

   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 39                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 2                          ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
      lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Notification");
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Notification")      ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"2:0:L")       ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Release Version Number missing within group");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      } 
   }

   /* Get Recepient Name and File Sequence Number from File Name in case of Sender FATAL Error */
   ReturnValue = 0;
   ReturnValue = GetRAPPartnerInfo();

   if(ReturnValue != 0)
   {
      return -1;
   }



   if((gRejectedErrorNo > 0) && (strcmp(gGenerateFilesFlg,"N")!=0)) 
   {
       for(ErrorCount=0; ErrorCount<gRejectedErrorNo; ErrorCount++)
       {
           ErrorReturnValue = SetBulkErrorDetails(gBulkErrorDetailsIndex, ErrorCount, 2)   ;
           if(ErrorReturnValue == -1)
           {
               return -1;
           }
       }
   }
   gRejectedErrorNo = 0;


   return 0 ;

}

/*
**
** Function Name        : fnDconvhx()
**
** Abstract             : Function to covert hex string
**
** Input parameters`    : int dwlen, unsigned char *pszIn , char *pszOut, char cvtyp
**
** Return value         : Void
**
*/

void fnDconvhx (int dwlen, unsigned char *pszIn , char *pszOut, char cvtyp)
{
        int Index,LowByte = 0,HiByte = 1;
        for (Index = 0 ; Index < dwlen; Index++)
        {
                if (pszIn[Index] != 0xFF)
                {
                        if( cvtyp == 'R')
                        {
                          pszOut[LowByte]   = pszIn[Index] &  0x0F;
                          pszOut[HiByte]= pszIn[Index] >> 4;
                        }
                        else
                        {
                           pszOut[LowByte]    = pszIn[Index] >> 4;
                           pszOut[HiByte]= pszIn[Index] &  0x0F;

                        }

                   pszOut[LowByte] < 10 ? (pszOut[LowByte] += 48) : (pszOut[LowByte] += 55);
                   pszOut[HiByte] < 10 ? (pszOut[HiByte] += 48) : (pszOut[HiByte] += 55);
                   LowByte += 2;
                   HiByte += 2;

                }
        }


        pszOut[LowByte] = 0;
    if (pszOut[strlen(pszOut)-1] == 'F')
          pszOut[strlen(pszOut)-1] =' ';
        return;

} /*  fnDconvhx  */


int fnCheckUtcSyntax(char FieldName[100])
{
    int i, FieldLength = 0 ;

   /* Check: Argument is a digit between 0 and 9 */

   FieldLength = strlen(FieldName) ;
   for(i=0; i<FieldLength; i++)
   {
       if(i==0)
       {
           if ((FieldName[i] == '+') || (FieldName[i] == '-')) 
           {
             continue;
           }
           else
           {
              return -1; 
           }
       }
       else 
       {
          if(isdigit (FieldName[i]) == 0)
          {
            return -1;
          }
       }
   }

   return 0;

}

int fnCheckSyntax(char FieldName[100],char FieldType[3])
{
   int i,FieldLength = 0 ;
   char FieldValue[100];

   /* printf("FieldName:-%s-,FieldType-%s-\n",FieldName,FieldType) ; */

   /* Check::Argument is a numeric digit or a letter of the alphabet */

   if(strcmp(FieldType,"BT") == 0)
   {
       FieldLength = strlen(FieldName) ;
   
       for(i=0; i < FieldLength; i++)
       {
         if (isalnum (FieldName[i]) == 0)
         {
           return -1;  
         }
       }
   }

   /* Check: Argument is a digit between 0 and 9 */

   if(strcmp(FieldType,"DI") == 0)
   {
     /*sprintf(FieldValue,"%d",(abs(atoi(FieldName))));
       FieldLength = strlen(FieldValue) ; */
	   FieldLength = strlen(FieldName) ;

       if(atoi(FieldName)<0)
	   {
	     return 0;
       }
	   else
	   {
       for(i=0; i < FieldLength; i++)
       {
         if (isdigit (FieldName[i]) == 0)
         {
		            return -1;
         }
       }
	  }
  }  


   /* Check: Argument is decimal digit, or the upper or lower case letters 'A' through 'F' */

   if(strcmp(FieldType,"DX") == 0)
   {
       FieldLength = strlen(FieldName) ;

       for(i=0; i < FieldLength; i++)
       {
         if (isxdigit (FieldName[i]) == 0)
         {
           return -1;
         }
       }
   }



   /* Check: Argument is a letter */

   if(strcmp(FieldType,"AL") == 0)
   {
       FieldLength = strlen(FieldName) ;

       for(i=0; i < FieldLength; i++)
       {
         if (isalpha (FieldName[i]) == 0)
         {
           return -1;
         }
       }
   }

   /* Check: Argument is a ASCII Value */
   if(strcmp(FieldType,"AS") == 0)
   {
       FieldLength = strlen(FieldName) ;

       for(i=0; i < FieldLength; i++)
       {
         if (isascii (FieldName[i]) == 0)
         {
           return -1;
         }
       }
   }

   return 0 ;
}


int fnCheckDialNumSyntax(char FieldName[100],char FieldType[3])
{
   int i,FieldLength = 0 ;

   FieldLength = strlen(FieldName) ;

   if(strcmp(FieldType,"DI") == 0)
   {
       for(i=0; i < FieldLength; i++)
       {
          if ((isdigit (FieldName[i]) == 0) && (FieldName[i] != '+') && (FieldName[i] != '#') && (FieldName[i] != '*'))
          {
             return -1 ;
          }
       }

   }

   return 0 ;
}

int fnDateRangeCheck(char FieldName[15])
{

      char TempString[20];
   
 
      if(strlen(FieldName) != 14)
      {
         return -1;
      }

      /* Check for century. Range :: CC=century('19', '20',...) */
      TempString[0]='\0';
      sprintf(TempString,"%c%c",FieldName[0],FieldName[1]);

      if((atoi(TempString) != 20))
      {
          return -1;
      }

      /* Check for Years. Range :: YY=year('00' - '99') */
      TempString[0]='\0';
      sprintf(TempString,"%c%c",FieldName[2],FieldName[3]);

      if((atoi(TempString) < 0 || atoi(TempString) > 99))
      {
         return -2;
      }
      /* Check for Months. Range :: MM=month('01', '02', ... , '12')  */
      TempString[0]='\0';
      sprintf(TempString,"%c%c",FieldName[4],FieldName[5]);

      if((atoi(TempString) < 1 || atoi(TempString) > 12))
      {
         return -3;
      }
      /* Check for Days. Range :: DD=day('01', '02', ... , '31') */
      TempString[0]='\0';
      sprintf(TempString,"%c%c",FieldName[6],FieldName[7]);

      if((atoi(TempString) < 1 || atoi(TempString) > 31))
      {
         return -4;
      }
      /* Check for Hours. Range :: hh=hour('00', '01', ... , '24') */
      TempString[0]='\0';
      sprintf(TempString,"%c%c",FieldName[8],FieldName[9]);

      if((atoi(TempString) < 0 || atoi(TempString) > 23))
      {
         return -5;
      }

      /* Check for Minutes. Range :: mm=minutes  ('00', '01', ... , '59') */
      TempString[0]='\0';
      sprintf(TempString,"%c%c",FieldName[10],FieldName[11]);

      if((atoi(TempString) < 0 || atoi(TempString) > 59))
      {
         return -6;
      }

      /* Check for Seconds. Range :: ss=seconds  ('00', '01', ... , '59') */
      TempString[0]='\0';
      sprintf(TempString,"%c%c",FieldName[12],FieldName[13]);

      if((atoi(TempString) < 0 || atoi(TempString) > 59))
      {
         return -7;
      }

      return 0 ;
}


int fnUtcValueCheck(char FieldName[15])
{

      char TempString[20];

      TempString[0]='\0';
      sprintf(TempString,"%c",FieldName[0]);

/*
      if((TempString[0] != '+') && (TempString[0] != '-'))
      {
          return -1;
      }
*/

      /* Check for Hours. Range is -13 to +13 */
      TempString[0]='\0';
      sprintf(TempString,"%c%c",FieldName[1],FieldName[2]);

      if((atoi(TempString) < -13 || atoi(TempString) > 13))
      {
          return -1;
      }

      /* Check for Minutes. Range is 00 t0 59 */
      TempString[0]='\0';
      sprintf(TempString,"%c%c",FieldName[3],FieldName[4]);

      /* if((atoi(TempString) < 0 || atoi(TempString) > 59)) */
      if((atoi(TempString) != 0) && (atoi(TempString) != 15) && (atoi(TempString) != 30) && (atoi(TempString) != 45))
      {
          return -1;
      }


      return 0 ; 
}

//Static Memory assigned to String2 is comment and added dynamic memory by Harish on 10-APR-2014
void fnItemLevel (char *String1)
{


//  char String2[50] ;

  int i = 0, j = 1, heap=0;

  char *String2 ;

  heap = strlen(String1)+10;
  String2 = (char *)malloc( heap *sizeof(char));

  INIT_STR(String2) ;

  for(i = 0; i < strlen(String1); i++)
  {
    if(String1[i]== 'L')
    {
       sprintf(String2,"%s%d",String2,j);
       j++ ;
    }
    else
    {
       sprintf(String2,"%s%c",String2,String1[i]);
    }

  }

   /* printf("String2:%s\n",String2) ; */

  strcpy(String1,String2);
  free(String2);
  return;

}

int fnCheckCurrency(char FieldName[4])
{
    void *Pointer;

    Pointer = NULL;
   /* Added SDR under ISO currency list by Yogesh on 27th July 2012*/
    Pointer = strstr("AED:AFN:ALL:AMD:ANG:AOA:ARS:AUD:AWG:AZN:BAM:BBD:BDT:BGN:BHD:BIF:BMD:BND:BOB:BOV:BRL:BSD:BTN:BWP:BYR:BZD:CAD:CDF:CHE:CHW:CLF:CLP:CNY:COP:COU:CRC:CUC:CUP:CVE:CZK:DJF:DKK:DOP:DZD:EEK:EGP:ERN:ETB:EUR:FJD:FKP:GBP:GEL:GHS:GIP:GMD:GNF:GTQ:GWP:GYD:HKD:HNL:HRK:HTG:HUF:IDR:ILS:INR:IQD:IRR:ISK:JMD:JOD:JPY:KES:KGS:KHR:KMF:KPW:KRW:KWD:KYD:KZT:LAK:LBP:LKR:LRD:LSL:LTL:LVL:LYD:MAD:MDL:MGA:MKD:MMK:MNT:MOP:MRO:MUR:MVR:MWK:MXN:MXV:MYR:MZN:NAD:NGN:NIO:NOK:NPR:NZD:OMR:PAB:PEN:PGK:PHP:PKR:PLN:PYG:QAR:RON:RSD:RUB:RWF:SAR:SBD:SCR:SDG:SDR:SEK:SGD:SHP:SLL:SOS:SRD:STD:SVC:SYP:SZL:THB:TJS:TMT:TND:TOP:TRY:TTD:TWD:TZS:UAH:UGX:USD:USN:USS:UYI:UYU:UZS:VEF:VND:VUV:WST:XAF:XAG:XAU:XBA:XBB:XBC:XBD:XCD:XDR:XFU:XOF:XPD:XPF:XPT:XTS:XXX:YER:ZAR:ZMK:ZWL",FieldName);
    if(Pointer == NULL)
    {
       return -1;
    }

    return 0 ;
}


int fnCheckPLMNPrefix(char FieldName[6])
{
    void *Pointer;
    char LFieldName[4];

    printf("Length FieldName:-%d-\n",strlen(FieldName)) ;
    if(strlen(FieldName) != 5)
    {
       return -1;
    }
    sub_str(LFieldName,FieldName,1, 3) ;

    Pointer = NULL;
    Pointer = strstr("AFG:ALB:DZA:ASM:AND:AGO:AIA:ATA:ATG:ARG:ARM:ABW:AUS:AUT:AZE:BHS:BHR:BGD:BRB:BLR:BEL:BLZ:BEN:BMU:BTN:BOL:BIH:BWA:BVT:BRA:IOT:BRN:BGR:BFA:BDI:KHM:CMR:CAN:CPV:CYM:CAF:TCD:CHL:CHN:CXR:CCK:COL:COM:COG:COD:COK:CRI:CIV:HRV:CUB:CYP:CZE:DNK:DJI:DMA:DOM:TMP:ECU:EGY:SLV:GNQ:ERI:EST:ETH:FLK:FRO:FJI:FIN:FRA:FXX:GUF:PYF:ATF:GAB:GMB:GEO:DEU:GHA:GIB:GRC:GRL:GRD:GLP:GUM:GTM:GIN:GNB:GUY:HTI:HMD:HND:HKG:HUN:ISL:IND:IDN:IRN:IRQ:IRL:ISR:ITA:JAM:JPN:JOR:KAZ:KEN:KIR:PRK:KOR:KWT:KGZ:LAO:LVA:LBN:LSO:LBR:LBY:LIE:LTU:LUX:MAC:MKD:MDG:MWI:MYS:MDV:MLI:MLT:MHL:MTQ:MRT:MUS:MYT:MEX:FSM:MDA:MCO:MNG:MNE:MSR:MAR:MOZ:MMR:NAM:NRU:NPL:NLD:ANT:NCL:NZL:NIC:NER:NGA:NIU:NFK:MNP:NOR:OMN:PAK:PLW:PSE:PAN:PNG:PRY:PER:PHL:PCN:POL:PRT:PRI:QAT:REU:ROU:ROM:RUS:RWA:KNA:LCA:VCT:WSM:SMR:STP:SAU:SEN:SRB:SCG:SYC:SLE:SGP:SVK:SVN:SLB:SOM:ZAF:SGS:ESP:LKA:SHN:SHN:SPM:SDN:SUR:SJM:SWZ:SWE:CHE:SYR:TWN:TJK:TZA:THA:TGO:TKL:TON:TTO:TUN:TUR:TKM:TCA:TUV:UGA:UKR:ARE:GBR:USA:UMI:URY:UZB:VUT:VAT:VEN:VNM:VGB:VIR:WLF:ESH:YEM:YUG:ZMB:ZWE:NAA",LFieldName);
    if(Pointer == NULL)
    {
       return -1;
    }

    return 0 ;
}

int fnCountryCodeCheck(char FieldName[85])
{
   int i;
   void *Pointer;
   int CalledNumberFlg = 0 ;
//   char CalledNumberPrefix[10];
   int CalledNumberLength = 0;
   int CalledPrefixLength = 5;
   int SpareCodeFlag=0;

   CalledNumberLength = strlen(FieldName) ;

   if(CalledNumberLength < 5)
   {
      CalledPrefixLength  = CalledNumberLength ;
   }

    for(i = CalledPrefixLength; i > 0; i--)
    {
        CalledNumberFlg = 0;
        sub_str(FieldName,CalledNumberPrefix,1, i) ;
       
//  printf("called number Prefix %s",CalledNumberPrefix);

        Pointer = NULL;
        if(i == 5)
        {
            Pointer = strstr("88210:88211:88212:88213:88214:88215:88216:88217:88219:88220:88222:88223:88224:88226:88227:88228:88229:88230:88231",CalledNumberPrefix);
        }

        if(i == 4)
        {
            Pointer = strstr("8810:8811:8812:8813:8816:8817:8818:8819:3883",CalledNumberPrefix);
        }


        if(i == 3)
        {
           Pointer = strstr("212:213:215:216:218:220:221:381:381:222:223:224:225:226:227:228:229:230:231:232:233:234:235:236:237:238:239:240:241:242:243:244:245:246:247:248:249:250:251:252:253:254:255:256:257:258:260:261:262:263:264:265:266:267:268:269:290:291:297:298:299:370:371:372:373:374:375:376:377:378:379:380:381:382:383:384:385:386:387:388:389:350:351:352:353:354:355:356:357:358:359:420:421:422:423:424:425:426:427:428:429:500:501:502:503:504:505:506:507:508:509:590:591:592:593:594:595:596:597:598:599:670:671:672:673:674:675:676:677:678:679:680:681:682:683:684:685:686:687:688:689:690:691:692:693:694:695:696:697:698:699:800:801:802:803:804:805:806:807:808:809:830:831:832:833:834:835:836:837:838:839:850:851:852:853:854:855:856:857:858:859:870:871:872:873:874:878:880:881:882:883:884:885:887:889:960:961:962:963:964:965:966:967:968:971:972:973:974:975:976:977:979:991:992:993:994:995:996:998",CalledNumberPrefix);
			/* Validating for Spare Codes and Reserved Codes */
            if (Pointer == NULL)
			{
			  
             Pointer = strstr("210:211:214:217:219:259:280:281:282:283:284:285:286:287:288:289:292:293:294:295:296:382:383:384:422:424:425:426:427:428:429:671:684:693:694:695:696:697:698:699:801:802:803:804:805:806:807:809:830:831:832:833:834:835:836:837:838:839:851:854:857:858:859:883:884:885:887:889:890:891:892:893:894:895:896:897:898:899:978:990:997:886:970:875:876:877:969:888:879:999",CalledNumberPrefix);
                    if(Pointer!=NULL)
                    {
                     SpareCodeFlag =1 ;
                    }       

            }
        }

        if(i == 2)
        {
            Pointer = strstr("20:27:30:31:32:33:34:36:39:39:39:40:41:43:44:45:46:47:48:49:51:52:53:54:55:56:57:58:60:61:62:63:64:65:66:81:82:84:86:90:91:92:93:94:95:98",CalledNumberPrefix);
        }

        if(i == 1)
        {
            Pointer = strstr("1:7",CalledNumberPrefix);
        }

        if ((Pointer != NULL) && (SpareCodeFlag == 0 ))
        {
            CalledNumberFlg = 1 ;
            break ;
        }
     }


     if((CalledNumberFlg  == 0))
     {
        return -1 ;
		
     }


    return 0 ;

}

int fnImsiPrfxCheck(double FieldName)
{
    char   *tok;
    char   TempImsiString[101];
    char   TempImsiPrefix[20];
    char   CDRImsi[20];
    char   CDRImsiPrefix[20];
    int    ValidImsiFlag=0;

    /* Validate the IMSI Prefix of the CDR */
    memset(TempImsiString,'\0',sizeof(TempImsiString));
    memset(TempImsiPrefix,'\0',sizeof(TempImsiPrefix));
    memset(CDRImsi,'\0',sizeof(CDRImsi));
    memset(CDRImsiPrefix,'\0',sizeof(CDRImsiPrefix));


    strcpy(TempImsiString,gImsiPrefix);
    sprintf(CDRImsi,"%f",FieldName);
    strncpy(CDRImsiPrefix,CDRImsi,5);

    ValidImsiFlag=0;
    tok = strtok(TempImsiString,":");
    do
    {
        strcpy(TempImsiPrefix,tok);
        if(strcmp(TempImsiPrefix,CDRImsiPrefix)==0)
        {
            ValidImsiFlag=1;
            break;
        }
    }while(tok=(char *)strtok(NULL,":"));

    if(ValidImsiFlag==0)
    {
       return -1;
    }

    return 0;

}


void fnRemTrailSpaces (char *pszBuffer)
{
        int  Index  = 0;
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

        Index  = strlen(pszBuffer) -1;
        for ( ; Index  >= 0 ; --Index)
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


/* For LTE Voice  Calls */

int  ReadMSESS(struct MobileSession* mobileSession)
{
   int i=0,j=0;
   int SCICount=0;                       /* Session ChargeInformation Count */
   int ErrorReturnValue = 0 ;
   int ReturnValue = 0;
   int SetError = 0;
   int  ErrorCount = 0       ;
   char TempNumtoChar [20]   ;
   int  lValidateFlag = 0    ;
   unsigned char EventReference[31];
   SessionChargeInformation *SCI;
   void *Pointer;
   CalledFlag=0;  

   gErrorNode = 434 ;
  

   INIT_STR(stContext.CallEventType) ; 
   sprintf(stContext.CallEventType,"%s;434:0:L",stContext.CallEventDetails);
   fnRemTrailSpaces(stContext.CallEventType) ;

  strcpy(BCT.SERVICE_CODE,"300") ;
    

 /*Mobile Session Service */
 if(NOT_NULL(mobileSession->mobileSessionService))
   {
	  BCT.CALL_TYPE = *mobileSession->mobileSessionService;
  	  if (BCT.CALL_TYPE == 1)
	  BCT.CALL_TYPE = 2;
  	  else if (BCT.CALL_TYPE == 2)
          BCT.CALL_TYPE = 1 ;
          else if  ((BCT.CALL_TYPE == 3))
           {
          BCT.CALL_TYPE = 2 ;
          strcpy(BCT.SERVICE_CODE,"302") ;
           }
          sprintf (TempNumtoChar,"%d",BCT.CALL_TYPE );
          ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
   
          if(ReturnValue != 0)
            {
              REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 440             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
               {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MobileSession Service");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"440:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                    ReturnValue = 0 ;
            }

            
           if(BCT.CALL_TYPE >3)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 440             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MobileSession Service");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"440:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }
    }
   else 
     {
                REI.ERROR_CODE[gRejectedErrorNo]  = 30                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 434             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MobileSession");           
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)     ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mobile Session Service missing within group");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
     }

       /*  Charged Party */
    if(NOT_NULL(mobileSession->chargedParty))
 
      ReadChargedParty(mobileSession->chargedParty);

    else 
     {
                REI.ERROR_CODE[gRejectedErrorNo]  = 31                            ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 434             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MobileSession");
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Charged Party missing within group.");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
      }
  
	  /* Rap Sequence number */
   if(ASNOCTS_PRESENT(&mobileSession->rapFileSequenceNumber))
      {
         BCT.RAPFILE_SEQUENCE_NUMBER = atol(mobileSession->rapFileSequenceNumber.octs);
         sprintf (TempNumtoChar,"%d",BCT.RAPFILE_SEQUENCE_NUMBER );
         ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
         if(ReturnValue != 0)
           {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 181             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RapFileSequenceNumber") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"181:0:L")   ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }
  
                   ReturnValue = 0 ;
            }
       

         if(BCT.RAPFILE_SEQUENCE_NUMBER > 99999)
           {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 21                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 181             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   { 
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RapFileSequenceNumber") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"436:0:L;181:0:L")   ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }
 
                   ReturnValue = 0 ;
          }
     }
 

/* Event Reference */

    if(ASNOCTS_PRESENT(&mobileSession->eventReference))
     {
 
        strcpy(BCT.EVENT_REFERENCE,mobileSession->eventReference.octs);
        fnRemTrailSpaces(BCT.EVENT_REFERENCE);
     }
    else
     {
                REI.ERROR_CODE[gRejectedErrorNo]  = 32                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 434             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MobileSession");
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Event Reference missing within group");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
     }

/*Recording Entity code */

    if(NOT_NULL(mobileSession->recEntityCodeList))
      
     ReadRecEntityCodeList(mobileSession->recEntityCodeList);

    else
    {
                REI.ERROR_CODE[gRejectedErrorNo]  = 33                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 434             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MobileSession");
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Recording Entity Code missing within group.");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
    }
   
   if(NOT_NULL(mobileSession->serviceStartTimestamp))
   
     ReadServiceStartTimestamp(mobileSession->serviceStartTimestamp);
   
   else
   {
                 REI.ERROR_CODE[gRejectedErrorNo]  = 34                               ;
   		 REI.APPLICATION_TAG[gRejectedErrorNo] = 434                          ;
    		 strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
     		 lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
    		 if(lValidateFlag == 0)
      		 {
                      strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS")  ;
                      strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MobileSession")                 ;
                      strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)   ;
                      fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                      strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Service Start Timestamp missing within group");
                      strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                      gRejectedErrorNo++ ;
                 }
   }


   if(NOT_NULL(mobileSession->causeForTerm))
     {
        BCT.CAUSE_FOR_TERMINATION = *mobileSession->causeForTerm;
 
      /* CauseForTerm : Syntax Error Check */
        sprintf (TempNumtoChar,"%d",BCT.CAUSE_FOR_TERMINATION );
        ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
        if(ReturnValue != 0)
        {
                 REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
          	 REI.APPLICATION_TAG[gRejectedErrorNo] = 58             ;
           	 strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           	 lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          	 if(lValidateFlag == 0)
          	 {
              	      strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS");
                      strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CauseForTermination") ;
                      sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"58:0:L")   ;
                      fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                      strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                      strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                      gRejectedErrorNo++ ;
                  }
                   ReturnValue = 0 ;
        }


       Pointer = NULL;
       Pointer = strstr("1:5",TempNumtoChar);
       if(Pointer == NULL)
        {
               REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 58             ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CauseForTermination") ;
                   sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"58:0:L")        ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                   gRejectedErrorNo++ ;
               }
               ReturnValue = 0 ;
       }

   }
       /* TotalCallEventDuration : Value Out of Range */

   if(NOT_NULL(mobileSession->totalCallEventDuration))
    {
        BCT.CALL_DURATION = * mobileSession->totalCallEventDuration;

       /* TotalCallEventDuration : Syntax Error Check */

        sprintf (TempNumtoChar,"%d", BCT.CALL_DURATION);
        ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
        if(ReturnValue != 0)
        {
             REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 223             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalCallEventDuration") ;
                  sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"223:0:L")   ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
             }

              ReturnValue = 0 ;
         }


       /* TotalCallEventDuration : Value Out of Range */

        if (BCT.CALL_DURATION < 0 )
        {
           REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 223             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TotalCallEventDuration") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"223:0:L")   ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
               gRejectedErrorNo++ ;
           }
           ReturnValue = 0 ;
       }

   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 35                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 434                        ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Mobile Session")               ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Total Call Event Duration missing within group.");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }
   }
/* Non Charged Party */
 
   if(NOT_NULL(mobileSession->nonChargedParty))
   
       ReadNonChargedParty(mobileSession->nonChargedParty);
    
 
  else 
  {
     if (BCT.CALL_TYPE == 2)
     {
      REI.ERROR_CODE[gRejectedErrorNo]  = 40                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 434                        ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS")  ;
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Mobile Session")               ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Group Non Charged Party missing within group and Mobile Session Service is MO Voice over LTE");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
       }
    }
 }
/*  Session Charge Information */
 
if(NOT_NULL(mobileSession->sessionChargeInfoList))
         {
            FOR_EACH_LIST_ELMT(SCI,mobileSession->sessionChargeInfoList)
            {
               SCICount = 0;

               ReadSessionChargeInformationList(SCI,SCICount);

               SCICount++;
               BCT.CHARGE_INFORMATION_COUNT = SCICount;
            }
         }
         else
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 36                             ;
             REI.APPLICATION_TAG[gRejectedErrorNo] =  434                       ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS")  ;
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MobileSession")               ;
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Session Charge Information missing within group");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                 gRejectedErrorNo++ ;
             }
 
         }
   
        if (NOT_NULL(BCT.CALLED_CALLING_NUMBER ) && (CalledFlag == 1)  )
		{
		 
          ReturnValue = fnCountryCodeCheck(BCT.CALLED_CALLING_NUMBER) ;              
          fnRemTrailSpaces(gMobilePrfx);      
          if(strcmp(CalledNumberPrefix,gMobilePrfx)==0)
          {
  
              if(BCT.CALL_TYPE_LEVEL1!=1)
               {
                  REI.ERROR_CODE[gRejectedErrorNo]  = 201              ;
                  REI.APPLICATION_TAG[gRejectedErrorNo] =444             ;
                  strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")      ;
                  lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                  if(lValidateFlag == 0)
                  {
                         strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS")  ;
                         strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"NonChargedPartyNumber") ;
                         sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.NonChargedParty,"444:0:L") ;
                         fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                         strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"NonChargedPartyNumber is not inline with CallTypeLevel1");
                         strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CALLED_CALLING_NUMBER);
                         gRejectedErrorNo++ ;
                  }

                       ReturnValue = 0 ;
              }
         }
           
        else if (strcmp(CalledNumberPrefix,gMobilePrfx)!=0)
        { 

            if(BCT.CALL_TYPE_LEVEL1!=2)
           {
               REI.ERROR_CODE[gRejectedErrorNo]  = 201                  ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 444             ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
                {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS")  ;
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"NonChargedPartyNumber")               ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.NonChargedParty,"444:0:L")      ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"NonChargedPartyNumber is not inline with CallTypeLevel1");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CALLED_CALLING_NUMBER);
                       gRejectedErrorNo++ ;
                }

                      ReturnValue = 0 ;
           }
       }
   }
 stMSESS=mobileSession;


 if((gRejectedErrorNo > 0) && (gFatalErrorCount == 0) && (strcmp(gGenerateFilesFlg,"N")!=0))
   {
       gErrorCDRsCount = gErrorCDRsCount + 1 ;
       gErrorCDRsCharge = gErrorCDRsCharge + BCT.CHARGE + BCT.CAMEL_INVOCATION_FEE ;
       gErrorCDRsTax = gErrorCDRsTax + BCT.TAX_VALUE  ;
       gErrorCDRsDuration = gErrorCDRsDuration + BCT.CALL_DURATION ;
       gCDRErrorFlag = 1 ;

       for(ErrorCount=0; ErrorCount<gRejectedErrorNo; ErrorCount++)
       {
           ErrorReturnValue = SetBulkErrorDetails(gBulkErrorDetailsIndex, ErrorCount,434)   ;
           if(ErrorReturnValue == -1)
           {
              return -1;
           }
       }
   }
   gRejectedErrorNo = 0;


   return 0 ;


}


/* For LTE SMS Calls */

int  ReadMESG(struct MessagingEvent* messagingEvent)
{
   int i=0,j=0;
   int ErrorReturnValue = 0 ;
   int ReturnValue = 0;
   int SetError = 0;
   int  ErrorCount = 0       ;
   char TempNumtoChar [20]   ;
   int  lValidateFlag = 0    ;
   unsigned char EventReference[31];
   TaxInformation *TI;
   NetworkElement *NE;
   int lExchangeRateCodeFlag = 0;
   int k=0;
   int CDRExchangerateFlag =0;
   void *Pointer;
   int lChargeTypeFlag = 0 ;
   int  TICount=0;
   int CDRTaxCodeFlag = 0;
   int NECount = 0;

   gErrorNode = 433 ;
   INIT_STR(stContext.CallEventType) ; 
   sprintf(stContext.CallEventType,"%s;433:0:L",stContext.CallEventDetails);
   fnRemTrailSpaces(stContext.CallEventType) ;
   strcpy(BCT.SERVICE_CODE,"301") ;
    

 /*Messaging Event */
   if(NOT_NULL(messagingEvent->messagingEventService))
      {
         BCT.CALL_TYPE = *messagingEvent->messagingEventService;
  	 if (BCT.CALL_TYPE == 1)
 	 BCT.CALL_TYPE = 2;
  	 else if (BCT.CALL_TYPE == 2)
         BCT.CALL_TYPE = 1 ;
      

      	 sprintf (TempNumtoChar,"%d",BCT.CALL_TYPE );
      	 ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
   
         if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 439             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MessagingEvent Service");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"439:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }

            
           if(BCT.CALL_TYPE >3)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 439             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MessagingEvent Service");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"439:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }
       }
     
    else 
      {
             REI.ERROR_CODE[gRejectedErrorNo]  = 30                  ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 433             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
              {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MessagingEvent");
				   strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Messaging Event Service missing within group");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                   gRejectedErrorNo++ ;
              }
                ReturnValue = 0 ;
      }

       /*  Charged Party */
   if(NOT_NULL(messagingEvent->chargedParty))
    
     ReadChargedParty(messagingEvent->chargedParty);
    
   else 
      {
             REI.ERROR_CODE[gRejectedErrorNo]  = 31                            ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 433             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
               {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MessagingEvent");
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Charged Party missing within group.");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
      }
  
	  /* Rap Sequence number */
   if(ASNOCTS_PRESENT(&messagingEvent->rapFileSequenceNumber))
      {
          BCT.RAPFILE_SEQUENCE_NUMBER = atol(messagingEvent->rapFileSequenceNumber.octs);
          sprintf (TempNumtoChar,"%d",BCT.RAPFILE_SEQUENCE_NUMBER );
          ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
          if(ReturnValue != 0)
          {
                 REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
                 REI.APPLICATION_TAG[gRejectedErrorNo] = 181             ;
                 strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                 lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                 if(lValidateFlag == 0)
                  {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RapFileSequenceNumber") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"181:0:L")   ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }
  
                   ReturnValue = 0 ;
          }
       

         if(BCT.RAPFILE_SEQUENCE_NUMBER > 99999)
         {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 21                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 181             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   { 
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RapFileSequenceNumber") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"181:0:L")   ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }
 
                   ReturnValue = 0 ;
         }
    }
 

/* Event Reference */

    if(ASNOCTS_PRESENT(&messagingEvent->eventReference))
    {
      strcpy(BCT.EVENT_REFERENCE,messagingEvent->eventReference.octs);
      fnRemTrailSpaces(BCT.EVENT_REFERENCE);
    }
   else
    {
                REI.ERROR_CODE[gRejectedErrorNo]  = 32                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 433             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MessagingEvent");     
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory Event Reference missing within group");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
     }



/*Recording Entity code */

  if(NOT_NULL(messagingEvent->recEntityCodeList))
 
     ReadRecEntityCodeList(messagingEvent->recEntityCodeList);
  else
   {
                REI.ERROR_CODE[gRejectedErrorNo]  = 36                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 433             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"messagingEvent");      
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Recording Entity Code missing within group.");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
   }
   
/* Network Element List  */

   if(NOT_NULL(messagingEvent->networkElementList))
    {
     NECount = 0;
     FOR_EACH_LIST_ELMT(NE,messagingEvent->networkElementList)
        {
               
                 ReadNetworkElementList(NE,NECount);
               NECount++;       
        }
   }

/* Service Start time Stamp */

   if(NOT_NULL(messagingEvent->serviceStartTimestamp))
   
      ReadServiceStartTimestamp(messagingEvent->serviceStartTimestamp);
   
   else
   {
         REI.ERROR_CODE[gRejectedErrorNo]  = 33                               ;
     	 REI.APPLICATION_TAG[gRejectedErrorNo] = 433                          ;
     	 strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
     	 lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      	if(lValidateFlag == 0)
     	 {
             	strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG")  ;
             	strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MessagingEvent")                 ;
          	strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)   ;
         	fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
        	strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Service Start Timestamp missing within group");
        	strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
       		gRejectedErrorNo++ ;
         }
   }

/* Non Charged Party */
 
   if(NOT_NULL(messagingEvent->nonChargedParty))
  
       ReadNonChargedParty(messagingEvent->nonChargedParty);
   

 
lExchangeRateCodeFlag = 1 ;
/* Exchange RateCode */
  if(NOT_NULL(messagingEvent->exchangeRateCode))
    {
       BCT.TAP_EXCHANGE_RATE_CODE      = *messagingEvent->exchangeRateCode;
   
       lExchangeRateCodeFlag = 0 ;


       /* ExchangeRateCode : Syntax Error Check */
       sprintf (TempNumtoChar,"%d",BCT.TAP_EXCHANGE_RATE_CODE);
       ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
       if(ReturnValue != 0)
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 105             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ExchangeRateCode") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"105:0:L")        ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
               gRejectedErrorNo++ ;
           }
           ReturnValue = 0 ;
       }

        CDRExchangerateFlag = 0 ;

        /* Compare the CDR Exchange Rate Code with Group Currency Conversion */
        for(k=0; k<gExchangeRateCount; k++)
        {
           if(BCT.TAP_EXCHANGE_RATE_CODE == ACC.CurrencyConversionInfo[k].ExchangeRateCode)
           {
              CDRExchangerateFlag = 1 ;
              break;
           }
        }

        if(CDRExchangerateFlag == 0)
        {
           REI.ERROR_CODE[gRejectedErrorNo]  = 101                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 105             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ExchangeRateCode") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"105:0:L")        ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Specified Exchange Rate Code not defined in group Currency Conversion");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
               gRejectedErrorNo++ ;
           }
           ReturnValue = 0 ;
        }
  }
/* Read CallTypeGroup */

  if(NOT_NULL(messagingEvent->callTypeGroup))
        {   

            INIT_STR(stContext.CallTypeGroup) ;
            sprintf(stContext.CallTypeGroup,"%s;258:0:L",stContext.CallEventType);
            fnRemTrailSpaces(stContext.CallTypeGroup) ;

        
            if(NOT_NULL(messagingEvent->callTypeGroup->callTypeLevel1))
            {
                BCT.CALL_TYPE_LEVEL1          = *messagingEvent->callTypeGroup->callTypeLevel1;


                /* CallTypeLevel1 : Syntax Error Check */
                sprintf (TempNumtoChar,"%d",BCT.CALL_TYPE_LEVEL1);
                ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
                if(ReturnValue != 0)
                {
                    REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                    REI.APPLICATION_TAG[gRejectedErrorNo] = 259             ;
                    strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                    lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                    if(lValidateFlag == 0)
                    {
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG")  ;
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeLevel1")               ;
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallTypeGroup,"259:0:L")      ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                        gRejectedErrorNo++ ;
                    }

                    ReturnValue = 0 ;
                }
             
                     Pointer = NULL;
                     Pointer = strstr("1:2",TempNumtoChar);

                     if(Pointer == NULL && BCT.CALL_TYPE != 0)
                     {
                         REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                         REI.APPLICATION_TAG[gRejectedErrorNo] = 259             ;
                         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG")  ;
                             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeLevel1")               ;
                             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallTypeGroup,"259:0:L")      ;
                             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                             gRejectedErrorNo++ ;
                         }

                         ReturnValue = 0 ;
                     }                   
            }
            else
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 258                          ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG")  ;
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeGroup")               ;
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallTypeGroup)        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Call Type Level 1 missing within group");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                    gRejectedErrorNo++ ;
                }
            }


            if(NOT_NULL(messagingEvent->callTypeGroup->callTypeLevel2))
            {
                BCT.CALL_TYPE_LEVEL2          = *messagingEvent->callTypeGroup->callTypeLevel2;


                /* CallTypeLevel2 : Syntax Error Check */
                sprintf (TempNumtoChar,"%d",BCT.CALL_TYPE_LEVEL2);
                ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
                if(ReturnValue != 0)
                {
                    REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                    REI.APPLICATION_TAG[gRejectedErrorNo] = 255             ;
                    strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                    lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                    if(lValidateFlag == 0)
                    {
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG")  ;
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeLevel2")               ;
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallTypeGroup,"255:0:L")      ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                        gRejectedErrorNo++ ;
                    }

                    ReturnValue = 0 ;
                }
                Pointer = NULL;
                Pointer = strstr("0",TempNumtoChar);
		              
		
                if(Pointer == NULL && BCT.CALL_TYPE != 0)
                {
                    REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                    REI.APPLICATION_TAG[gRejectedErrorNo] = 255             ;
                    strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                    lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                    if(lValidateFlag == 0)
                    {
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG")  ;
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeLevel2")               ;
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallTypeGroup,"255:0:L")      ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                        gRejectedErrorNo++ ;
                    }

                    ReturnValue = 0 ;
                }
            }
            else
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 258                          ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG")  ;
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeGroup")               ;
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallTypeGroup)        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Call Type Level 2 missing within group");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                    gRejectedErrorNo++ ;
                }
            }


            if(NOT_NULL(messagingEvent->callTypeGroup->callTypeLevel3))
            {
                BCT.CALL_TYPE_LEVEL3          = *messagingEvent->callTypeGroup->callTypeLevel3;
 
                /* CallTypeLevel3 : Syntax Error Check */
                sprintf (TempNumtoChar,"%d",BCT.CALL_TYPE_LEVEL3);
                ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
                if(ReturnValue != 0)
                {
                    REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                    REI.APPLICATION_TAG[gRejectedErrorNo] = 256             ;
                    strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                    lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                    if(lValidateFlag == 0)
                    { 
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG")  ;
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeLevel3")               ;
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallTypeGroup,"256:0:L")      ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                        gRejectedErrorNo++ ;
                    }

                    ReturnValue = 0 ;
                }
            }
            else
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 258                          ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG")  ;
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeGroup")               ;
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallTypeGroup)        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Call Type Level 3 missing within group");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                    gRejectedErrorNo++ ;
                }
            }

        }
        else
        {
            REI.ERROR_CODE[gRejectedErrorNo]  = 34                             ;
            REI.APPLICATION_TAG[gRejectedErrorNo] = 433                          ;
            strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
            lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
            if(lValidateFlag == 0)
            {
                strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG")  ;
                strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MessagingEvent")  ;
                strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
                fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory group Call Type Group missing within group");
                strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                gRejectedErrorNo++ ;
            }
        }

  /* Read Charge */
	 
	 if(NOT_NULL(messagingEvent->charge))
         {
            
               BCT.CHARGE = BCT.CHARGE + *messagingEvent->charge;

               lChargeTypeFlag = 1 ;
 
	       char  ChargeContext[100] ;
               sprintf(ChargeContext,"%s",stContext.CallEventType);
               fnRemTrailSpaces(ChargeContext) ;
	       strcpy(gIOTChargeContext,ChargeContext);


               /* Charge : Syntax Error Check */
               sprintf (TempNumtoChar,"%d",*messagingEvent->charge);
               ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
               if(ReturnValue != 0)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 62              ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG");
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Charge");
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"62:0:L")        ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                        gRejectedErrorNo++ ;
                   }
                   ReturnValue = 0 ;
               }

               /* Charge : Value Out of Range */

               if (*messagingEvent->charge < 0) 
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 62              ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Charge");
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallEventType,"62:0:L")        ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }
                   ReturnValue = 0 ;
               }
                    
         }
         else
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 35                             ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 433                         ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG")  ;
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MessagingEvent")               ;
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Charge not present within group");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                 gRejectedErrorNo++ ;
             }
         }

if((BCT.CHARGE > 0) && (lExchangeRateCodeFlag == 1))
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 41                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 433                          ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG")  ;
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MessagingEvent")               ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType)        ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Item Exchange Rate Code missing within group and one or more Charge within an associated Charge Detail is greater than zero");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }

   }

   /* Tax List Information*/
/*gTaxListFlag variable  added to check Whether TaxInformation Node Present or not */

gTaxListFlag=0;
  
/* Loop through the TaxInformationList */
   if(NOT_NULL(messagingEvent->taxInformationList))
   {
    gTaxListFlag=1;

      FOR_EACH_LIST_ELMT(TI,messagingEvent->taxInformationList)
      {
         TICount = 0;
         INIT_STR(stContext.TaxInformation) ;
         sprintf(stContext.TaxInformation,"%s;214:%d:L;213:0:L",stContext.CallEventType,TICount+1);
         fnRemTrailSpaces(stContext.TaxInformation) ;

         strcpy(gIOTTaxContext,stContext.TaxInformation);

         if(NOT_NULL(TI->taxCode))
         {
             BCT.TAX_CODE = *TI->taxCode;

             /* TaxCode : Syntax Error Check */
             sprintf (TempNumtoChar,"%d",BCT.TAX_CODE);
             ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
             if(ReturnValue != 0)
             {
                 REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
                 REI.APPLICATION_TAG[gRejectedErrorNo] = 212             ;
                 strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                 lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                 if(lValidateFlag == 0)
                 {
                     strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG");
                     strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxCode");
                     sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.TaxInformation,"212:0:L")        ;
                     fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                     strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                     strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                     gRejectedErrorNo++ ;
                 }
                 ReturnValue = 0 ;
             }

            CDRTaxCodeFlag = 0;

            for(i=0;i<gTaxationCount;i++)
            {
                if(BCT.TAX_CODE == ACC.Taxation[i].TaxCode)
                {
                   CDRTaxCodeFlag = 1;
                    break;
                }
            }

            if(CDRTaxCodeFlag==0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 100                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 212             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxCode");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.TaxInformation,"212:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Specified Tax Rate Code was not defined in the group Taxation");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }


         }
         else
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 213                          ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG")  ;
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxInformation")               ;
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.TaxInformation)        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Tax Rate Code missing within group");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                 gRejectedErrorNo++ ;
             }
         }


         if(NOT_NULL(TI->taxValue))
         {
            /* Accumulate the TotalTax for the Call */
            BCT.TAX_VALUE = BCT.TAX_VALUE + *TI->taxValue;

            /* TaxValue : Syntax Error Check */
            sprintf (TempNumtoChar,"%d",BCT.TAX_VALUE);
            ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 397             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxValue");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.TaxInformation,"397:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }


            /* Taxvalue : Value Out of Range */

            if (BCT.TAX_VALUE < 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 397             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxValue");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.TaxInformation,"397:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }

         }
         else
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 31              ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 213         ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")   ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG")  ;
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxInformation")               ;
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.TaxInformation)        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Tax Value missing within group");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                 gRejectedErrorNo++ ;
             }
         }


         if(NOT_NULL(TI->taxableAmount))
         {
            /* Accumulate the TotalTaxable amount for the Call */
            BCT.TAXABLE_AMOUNT = BCT.TAXABLE_AMOUNT + *TI->taxableAmount;

            /* TaxableAmount : Syntax Error Check */
			//Below line is comment by harish on 10-APR-2014 as Tax value was more then int
            //sprintf (TempNumtoChar,"%d",BCT.TAXABLE_AMOUNT);
			sprintf (TempNumtoChar,"%ld",(unsigned long int)BCT.TAXABLE_AMOUNT);
            ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 398             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxableAmount");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.TaxInformation,"398:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }


            /* TaxableAmount : Value Out of Range */

            if (BCT.TAXABLE_AMOUNT <= 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 398             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxableAmount");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.TaxInformation,"398:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }


         }

         /* Added by Chetan on 14-May-2009 to store Tax Details */

         for(k=0; k<gTaxationCount; k++)
         {
            if((ACC.Taxation[k].TaxCode == BCT.TAX_CODE) && (BCT.TAX_VALUE > 0))
            {
               if(strlen(BCT.TAP_TAX_TYPE_RATE) < 100)
               {
                   sprintf(BCT.TAP_TAX_TYPE_RATE,"%s%s:%d;",BCT.TAP_TAX_TYPE_RATE,ACC.Taxation[k].TaxType,ACC.Taxation[k].TaxRate) ;
               }
               break ;
            }
         }

         TICount++;

         /* This count indicates if more than 1tax is present for the call */
         BCT.TAX_INFORMATION_COUNT    = BCT.TAX_INFORMATION_COUNT + 1;
   }

}
 if(( BCT.TAX_INFORMATION_COUNT>0) && (gTapinTaxFlag == 0))
       	 {
        	REI.ERROR_CODE[gRejectedErrorNo]  = 39                 ;
              	REI.APPLICATION_TAG[gRejectedErrorNo] = 214             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
              lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
              if(lValidateFlag == 0)
              {
                 
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MessagingEvent") ;
		          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType) ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Group Tax Information present within group but not expected in accordance with roaming agreement for the call/event and Tax Value referenced within the group is greater than 0 ");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                  gRejectedErrorNo++ ;
              }
         }


      if(( BCT.TAX_INFORMATION_COUNT==0) && (gTapinTaxFlag ==1))
        {
              REI.ERROR_CODE[gRejectedErrorNo]  = 38                ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 214             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
              lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
              if(lValidateFlag == 0)
              {
                
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MessagingEvent") ;
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType) ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Group Tax Information missing within group but expected in accordance with roaming agreement for that particular call. Tax Information group missing must be interpreted as Tax Value 0 ");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                  gRejectedErrorNo++ ;
              }
         }


stMESG=messagingEvent;


if((gRejectedErrorNo > 0) && (gFatalErrorCount == 0) && (strcmp(gGenerateFilesFlg,"N")!=0))
   {
       gErrorCDRsCount = gErrorCDRsCount + 1 ;
       gErrorCDRsCharge = gErrorCDRsCharge + BCT.CHARGE + BCT.CAMEL_INVOCATION_FEE ;
       gErrorCDRsTax = gErrorCDRsTax + BCT.TAX_VALUE  ;
       gErrorCDRsDuration = gErrorCDRsDuration + BCT.CALL_DURATION ;
       gCDRErrorFlag = 1 ;

       for(ErrorCount=0; ErrorCount<gRejectedErrorNo; ErrorCount++)
       {
           ErrorReturnValue = SetBulkErrorDetails(gBulkErrorDetailsIndex, ErrorCount,433)   ;
           if(ErrorReturnValue == -1)
           {
              return -1;
           }
       }
   }
   gRejectedErrorNo = 0; 
  
 
  return 0 ;

}   
void ReadNetworkElementList( NetworkElement *NE,int i)
{
   int  ReturnValue = 0 ;
   int  ErrorReturnValue = 0 ;
   char TempNumtoChar [46]   ;
   int  ErrorCount = 0       ;
   int  lValidateFlag = 0    ;
   char elementType[5];
   char ElementID[46];


	  INIT_STR(stContext.NetworkElement) ;
      	  sprintf(stContext.NetworkElement,"%s;441:0:L",stContext.CallEventType);
          fnRemTrailSpaces(stContext.NetworkElement) ;

         
	  if(NOT_NULL(NE->elementType))
           {
              elementType[i] = *NE->elementType;
              if(i==0)
	      BCT.NETWORK_ELEMENT_TYPE1= elementType[i];
              else
              BCT.NETWORK_ELEMENT_TYPE2= elementType[i];
	        
               /* Element Type : Syntax Error Check */
              sprintf (TempNumtoChar,"%d", elementType[i]);
              ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
			 
              if(ReturnValue != 0)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 438             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkElement");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"elementType") ;
         	       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.NetworkElement,"438:0:L") ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }

                   ReturnValue = 0 ;
               }
               
						  
                 /* Element Type:Value Out Of Range */
            

               if ((elementType[i] > 3) || (elementType[i]<=0))
               {
			     
                   REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 438             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;

                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
				     
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkElement");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"elementType") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.NetworkElement,"438:0:L") ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }

                   ReturnValue = 0 ;
               }
            }   
            else
            {
               REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
               REI.APPLICATION_TAG[gRejectedErrorNo] = 438                        ;
               strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                   ;
               lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
               if(lValidateFlag == 0)
               {
                   strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkInformation");
                   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityInfo")      ;
				   strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.NetworkElement)     ;
                   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item ElementType missing within group");
                   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                   gRejectedErrorNo++ ;
               }
            }


      if(ASNOCTS_PRESENT(&NE->elementId))
       {
	      if(i==0)
		{
	  	     strcpy(BCT.NETWORK_ELEMENT_ID1,NE->elementId.octs);
               	     fnRemTrailSpaces(BCT.NETWORK_ELEMENT_ID1);
	             sprintf (TempNumtoChar,"%s",BCT.NETWORK_ELEMENT_ID1);

				 
	        }
              
               else
		   {
                      strcpy(BCT.NETWORK_ELEMENT_ID2,NE->elementId.octs);
                      fnRemTrailSpaces(BCT.NETWORK_ELEMENT_ID2);
		      sprintf (TempNumtoChar,"%s",BCT.NETWORK_ELEMENT_ID2);
                }
              
			
               /* Element ID : Syntax Error Check  */

              
               ReturnValue = fnCheckSyntax(TempNumtoChar,"AS") ;
               if(ReturnValue != 0)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 437             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"NetworkElement") ;
	               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.NetworkElement,"437:0:L") ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }

                   ReturnValue = 0 ;
              }
          
		   strcpy(ElementID,TempNumtoChar);

             if(elementType[i] == 1)
               {
			     
				   ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ; 
                   if (ReturnValue != 0)
                   {
                         REI.ERROR_CODE[gRejectedErrorNo]  = 101                  ;
                         REI.APPLICATION_TAG[gRejectedErrorNo] = 441             ;
                         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG");
                             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"NetworkElement") ;
                             strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.NetworkElement)     ;
                             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Entity Type refers to SMSC and syntax of the associated Element ID does not conform to MSISDN");
                             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],ElementID);
                             gRejectedErrorNo++ ;
                         }

                       ReturnValue = 0 ;
		   }
               }


            else  if(elementType[i] == 2)
                 {
				    
                 if (((fnValidateIPV4(TempNumtoChar)!=0) && (fnValidateIPV6(TempNumtoChar)!=0 )))
			       {
						   
			             REI.ERROR_CODE[gRejectedErrorNo]  = 102                 ;
                	     REI.APPLICATION_TAG[gRejectedErrorNo] = 441             ;
                   	     strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                             if(lValidateFlag == 0)
                             {
                                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG");
                      		   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"NetworkElement") ;
                               strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.NetworkElement)     ;
                               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                      		   strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Entity Type refers to S-CSCF and syntax of the Element ID does not conform to Text Reresentation of IP Addresses.");
                     		   strcpy(REI.ERROR_VALUE[gRejectedErrorNo],ElementID);
                       		   gRejectedErrorNo++ ;
                             }
                                ReturnValue = 0 ;
		         }
                 }


            else   if(elementType[i] == 3)
                 { 
				  
                 if ((ReturnValue != 0) || ((fnValidateIPV4(TempNumtoChar)!=0) && (fnValidateIPV6(TempNumtoChar)!=0 )))
		          {
			  
		             REI.ERROR_CODE[gRejectedErrorNo]  = 103                  ;
                    	     REI.APPLICATION_TAG[gRejectedErrorNo] = 441             ;
                             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                             if(lValidateFlag == 0)
                             {
                               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MESG");
                    		   strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"NetworkElement") ;
							   strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.NetworkElement)     ;
                     		   fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Entity Type refers to SM-IP-GW and syntax of the Element ID does not conform to	Text Representation of IP Addresses.");
                               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],ElementID);
                               gRejectedErrorNo++ ;
                            }
                             ReturnValue = 0 ;
		        }
                   }             


            }   
            else
            {
               		REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
              		REI.APPLICATION_TAG[gRejectedErrorNo] = 441                        ;
              		strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                   ;
               		lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                        if(lValidateFlag == 0)
                       {
                  		 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"NetworkElement");
                  		 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"elementID")      ;
                         strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.NetworkElement)     ;
                		 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  		 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Element ID missing within group");
                  		 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                   		 gRejectedErrorNo++ ;
                        }
            }
          
            i++;
         
          
       /*  NI.TotalNetworkEntity   = i; */
       /*  gNetworkEntityInfoCount = i; */
  }
     


void  ReadChargedParty(struct ChargedParty* chargedParty)
{
   unsigned char Imsi[16];      /* AddressStringDigits */
   unsigned char Msisdn[17]; /* AddressStringDigits */
   int ReturnValue = 0;
   int ErrorReturnValue = 0 ;
   int  lValidateFlag = 0   ;
   unsigned char Temp_Imsi[26];
   unsigned char PublicUserId[46];

   INIT_STR(stContext.ChargedParty) ;
   sprintf(stContext.ChargedParty,"%s;436:0:L",stContext.CallEventType) ;
   fnRemTrailSpaces(stContext.ChargedParty) ;


/* Validate IMSI */

   if(ASNOCTS_PRESENT(&chargedParty->imsi))
   {

 	 fnDconvhx(chargedParty->imsi.octetLen,
                         chargedParty->imsi.octs,
                         Imsi,
                         'S');
               Imsi[15]='\0';
               fnRemTrailSpaces(Imsi);      

               BCT.IMSI = atof(Imsi);
            
   	       ReturnValue = fnCheckSyntax(Imsi,"DI") ;
               if(ReturnValue != 0)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 129             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Imsi") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargedParty,"436:0:L;129:0:L")   ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],Imsi);
                       gRejectedErrorNo++ ;
                   }
  
                   ReturnValue = 0 ;
               }


              fnDconvhx(chargedParty->imsi.octetLen,
                        chargedParty->imsi.octs,
                      Temp_Imsi,
                      'S');
               fnRemTrailSpaces(Temp_Imsi);
               Temp_Imsi[strlen(Temp_Imsi)]='\0';

               if(strlen(Temp_Imsi) > 15)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 129             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   { 
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Imsi") ;
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargedParty,"436:0:L;129:0:L")   ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],Temp_Imsi);
                       gRejectedErrorNo++ ;
                   }
 
                   ReturnValue = 0 ;
               }

            ReturnValue = fnImsiPrfxCheck(BCT.IMSI);

               if(ReturnValue != 0)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 200                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 129             ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Imsi") ;
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargedParty,"436:0:L;129:0:L")   ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"First characters are different from home operators MCC + MNC, or not as bilaterally agreed");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],Temp_Imsi);
                        gRejectedErrorNo++ ;
                   }
                   ReturnValue = 0 ;
               }

            }

   else
   {
          REI.ERROR_CODE[gRejectedErrorNo]  = 30                 ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 436             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Imsi") ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargedParty)     ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory Item IMSI not present within group ");   
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
     }

/*Validate MSISDN */

  if(ASNOCTS_PRESENT(&chargedParty->msisdn))
         {
            fnDconvhx(chargedParty->msisdn.octetLen,
                      chargedParty->msisdn.octs,
                      Msisdn,
                      'S');
            fnRemTrailSpaces(Msisdn);
            strcpy(BCT.MSISDN,Msisdn);
            fnRemTrailSpaces(BCT.MSISDN);
 
            ReturnValue = fnCountryCodeCheck(BCT.MSISDN) ;
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  =   23                            ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 152                          ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS/MSG")  ;
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Msisdn")                 ;
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargedParty,"436:0:L;152:0:L")   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Number not represented in international format and MSISDN expected in accordance with roaming agreement");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.MSISDN);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0;
            }

         }
/* Validate Public USerID */

    if(ASNOCTS_PRESENT(&chargedParty->publicUserId))
         {            
        	if (BCT.CALL_TYPE ==1)
 	         {
		  strcpy(BCT.B_USERID,chargedParty->publicUserId.octs);
                  fnRemTrailSpaces(BCT.B_USERID); 
                 }
		if  (BCT.CALL_TYPE ==2)
		{
		strcpy(BCT.A_USERID,chargedParty->publicUserId.octs);
                fnRemTrailSpaces(BCT.A_USERID); 		
                }
        }

}

void ReadServiceStartTimestamp(ServiceStartTimestamp *serviceStartTimestamp)
{
   int ErrorReturnValue = 0;
   int ReturnValue = 0;
   char TempNumtoChar [10]   ;
   int  k=0;
   int  CDRUtcOffsetCode=0 ;
   int  lValidateFlag = 0    ;

   INIT_STR(stContext.ServiceStartTimestamp) ;
   sprintf(stContext.ServiceStartTimestamp,"%s;447:0:L",stContext.CallEventType) ;
   fnRemTrailSpaces(stContext.ServiceStartTimestamp) ;

    
   if(ASNOCTS_PRESENT(&serviceStartTimestamp->localTimeStamp))
   {
      strcpy(BCT.CALL_DATE,serviceStartTimestamp->localTimeStamp.octs);
      fnRemTrailSpaces(BCT.CALL_DATE) ;

	
      /* ServiceStartTimeStamp : Syntax Error Check */
      ReturnValue = fnCheckSyntax(BCT.CALL_DATE,"DI") ;
      if(ReturnValue != 0)
      {
         REI.ERROR_CODE[gRejectedErrorNo]  = 10                   ;
         REI.APPLICATION_TAG[gRejectedErrorNo] = 447              ;
         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
         if(lValidateFlag == 0)
         {
             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS/MSG");
             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ServiceStartTimestamp") ;
             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ServiceStartTimestamp,"16:0:L")   ;
             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CALL_DATE);
             gRejectedErrorNo++ ;
         }

         ReturnValue = 0 ;
      }

      /* ServiceStartTimeStamp : Value Out of Range Check */
      ReturnValue = fnDateRangeCheck(BCT.CALL_DATE);
      if(ReturnValue != 0)
      {
         REI.ERROR_CODE[gRejectedErrorNo]  = 20             ;
         REI.APPLICATION_TAG[gRejectedErrorNo] = 447        ;
         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")  ;
         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
         if(lValidateFlag == 0)
         {
             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS/MSG");
             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ServiceStartTimestamp") ;
             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ServiceStartTimestamp,"16:0:L")   ;
             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CALL_DATE);
             gRejectedErrorNo++ ;
         }

         ReturnValue = 0 ;
      }

   }

   if(NOT_NULL(serviceStartTimestamp->utcTimeOffsetCode))
   {
      BCT.UTC_OFFSET_CODE = *serviceStartTimestamp->utcTimeOffsetCode;


      /* UtcTimeOffsetCode : Syntax Error Check */
      sprintf (TempNumtoChar,"%d", BCT.UTC_OFFSET_CODE);
      ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
      if(ReturnValue != 0)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 232             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"UtcTimeOffsetCode") ;
              sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ServiceStartTimestamp,"232:0:L")   ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
      }

      CDRUtcOffsetCode = 0;

      for(k=0; k<gUTCOffsetCount; k++)
      {
          if(BCT.UTC_OFFSET_CODE == NI.UtcTimeOffsetInfo[k].UtcTimeOffsetCode)
          {
              CDRUtcOffsetCode = 1;
              break;
          }
      }

      if(CDRUtcOffsetCode==0)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 100                  ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 232             ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"UtcTimeOffsetCode") ;
              sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ServiceStartTimestamp,"232:0:L")   ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Specified UTC Time Offset Code not defined in group UTC Time Offset Information");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
              gRejectedErrorNo++ ;
          }
          ReturnValue = 0 ;
      }


   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 30                  ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 447             ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
      lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS/MSG");
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ServiceStartTimestamp") ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ServiceStartTimestamp)   ;
          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory associated item UTC Time Offset Code missing");
          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
          gRejectedErrorNo++ ;
      }

      ReturnValue = 0 ;
   }


   /*
   printf("ServiceTime Details:\n");
   printf("   CallDate :-%s-\n",BCT.CALL_DATE);
   printf("    UTCCode :-%d-\n",BCT.UTC_OFFSET_CODE);  
   */

}


void ReadNonChargedParty(NonChargedParty* nonChargedParty)
{
   unsigned char NonChargedPartyNumber[87]; /* AddressStringDigits */
   unsigned char NonChargedPublicUserId[46];
   int ReturnValue = 0;
   int ErrorReturnValue = 0 ;
   int  lValidateFlag = 0    ;
   char TempNumtoChar [10]   ;
    int  NonChargedFlag =0;
   CalledFlag=0; 

   INIT_STR(stContext.NonChargedParty) ;
   sprintf(stContext.NonChargedParty,"%s;443:0:L",stContext.CallEventType) ;
   fnRemTrailSpaces(stContext.NonChargedParty) ;

   if(ASNOCTS_PRESENT(&nonChargedParty->nonChargedPartyNumber))
   {
       CalledFlag =1;   
       NonChargedFlag =1;
      fnDconvhx(nonChargedParty->nonChargedPartyNumber.octetLen,nonChargedParty->nonChargedPartyNumber.octs,NonChargedPartyNumber,'S');
      fnRemTrailSpaces(NonChargedPartyNumber);
      
     strcpy(BCT.CALLED_CALLING_NUMBER,NonChargedPartyNumber);
	 sprintf (TempNumtoChar,"%s", BCT.CALLED_CALLING_NUMBER);
	     	  
      if ((BCT.CALL_TYPE == 2) && (BCT.SERVICE_CODE != "301"))
	  {

	     ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
		     if(ReturnValue != 0)
     		 {
        		 REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
         		 REI.APPLICATION_TAG[gRejectedErrorNo] = 444             ;
      			 strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
         		 lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
       	     if(lValidateFlag == 0)
               {
             		 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS");
             		 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"NonChargedPartyNumber") ;
             		 sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.NonChargedParty,"444:0:L")   ;
           		     fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
            		 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error and Mobile Session Service is MO Voice over LTE.");
            		 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
             		 gRejectedErrorNo++ ;
               }
                     ReturnValue = 0 ;
          }

         ReturnValue = fnCountryCodeCheck(BCT.CALLED_CALLING_NUMBER) ;      
	     if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  =   20                            ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 444                          ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS")  ;
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"NonChargedPartyNumber")                 ;
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.NonChargedParty,"444:0:L")   ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
		    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range or number does not start with a valid country code as listed in  Assigned Country Codes and Mobile Session Service MO Voice over LTE");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CALLED_CALLING_NUMBER);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0;
            }       
     }
}


 if(ASNOCTS_PRESENT(&nonChargedParty->nonChargedPublicUserId))
  {

          NonChargedFlag=1;
          if (BCT.CALL_TYPE ==1)
	   {
            strcpy(BCT.A_USERID,nonChargedParty->nonChargedPublicUserId.octs);
	    fnRemTrailSpaces(BCT.A_USERID);
	 	
            }
	  if  (BCT.CALL_TYPE ==2)
           {
	    strcpy(BCT.B_USERID,nonChargedParty->nonChargedPublicUserId.octs);
	    fnRemTrailSpaces(BCT.B_USERID);
           }
  }

  if(NonChargedFlag == 0)
   {

                 REI.ERROR_CODE[gRejectedErrorNo]  =   30                            ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 443                          ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                    ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS/MSG")  ;
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"NonChargedParty")                 ;
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.NonChargedParty)     ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
		            strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Neither Non Charged Party Number nor Non Charged Public User ID present");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0;
         
   }

} 


void ReadSessionChargeInformationList(SessionChargeInformation *SCI,int SCICount)
{
   int	CDLCount=0; 	/* Count for ChargeDetailList within ChargeInformation */
   int  TICount=0;  	/* Count for TaxInformation within ChargeInformation   */
   ChargeDetail   *CD;
   TaxInformation *TI;
   int k=0, i=0, j=0 ;
   void *Pointer;
   int ErrorReturnValue = 0;
   int ReturnValue = 0;
   char TempNumtoChar [10]   ;
   int lChargeableUnitsFlag ;
   int lChargeTypeFlag = 0 ;
   int CDRExchangerateFlag= 0;
   int CDRTaxCodeFlag = 0;
   int CDRDiscountCodeFlag = 0 ;
   int CDROtherTypeChargeFlag = 0 ;
   int CDROtherTypeCharge = 0    ;
   int  lValidateFlag = 0    ;
   int lExchangeRateCodeFlag = 0;
   char ChargeTimeStamp[15];

   INIT_STR(stContext.SessionChargeInformation) ;
   sprintf(stContext.SessionChargeInformation,"%s;448:%d:L;449:0:L",stContext.CallEventType,SCICount+1);
   fnRemTrailSpaces(stContext.SessionChargeInformation) ;
   

   /* Read ChargedItem */
   if(ASNOCTS_PRESENT(&SCI->chargedItem))
   {
       strcpy(BCT.CHARGED_ITEM,SCI->chargedItem.octs);


       /* ChargedItem : Syntax Error Check */
       ReturnValue = fnCheckSyntax(BCT.CHARGED_ITEM,"AS") ;
       if(ReturnValue != 0)
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 66             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargedItem") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.SessionChargeInformation,"66:0:L")        ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CHARGED_ITEM);
               gRejectedErrorNo++ ;
           }

           ReturnValue = 0 ;
       }   

		  Pointer = NULL;
                  Pointer = strstr("A:D:F",BCT.CHARGED_ITEM);
                  if(Pointer == NULL)
                  {
                     REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                     REI.APPLICATION_TAG[gRejectedErrorNo] = 66             ;
                     strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                     lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                     if(lValidateFlag == 0)
                     {
                         strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                         strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargedItem") ;
                         sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.SessionChargeInformation,"66:0:L")        ;
                         fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                         strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                         strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CHARGED_ITEM);
                         gRejectedErrorNo++ ;
                     }
                     ReturnValue = 0 ;
                  }
           }

   
   else
   {
       REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
       REI.APPLICATION_TAG[gRejectedErrorNo] = 69                          ;
       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
       if(lValidateFlag == 0)
       {
           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SessionChargeInformation")               ;
           strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.SessionChargeInformation)        ;
           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Item Charged Item missing within group");
           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
           gRejectedErrorNo++ ;
       }
   }


   lExchangeRateCodeFlag = 1 ;

   /* Read ExchangeRateCode */
   if(NOT_NULL(SCI->exchangeRateCode))
   {
       BCT.TAP_EXCHANGE_RATE_CODE      = *SCI->exchangeRateCode;
   
       lExchangeRateCodeFlag = 0 ;


       /* ExchangeRateCode : Syntax Error Check */
       sprintf (TempNumtoChar,"%d",BCT.TAP_EXCHANGE_RATE_CODE);
       ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
       if(ReturnValue != 0)
       {
           REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 105             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ExchangeRateCode") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.SessionChargeInformation,"105:0:L")        ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
               gRejectedErrorNo++ ;
           }
           ReturnValue = 0 ;
       }

        CDRExchangerateFlag = 0 ;

        /* Compare the CDR Exchange Rate Code with Group Currency Conversion */
        for(k=0; k<gExchangeRateCount; k++)
        {
           if(BCT.TAP_EXCHANGE_RATE_CODE == ACC.CurrencyConversionInfo[k].ExchangeRateCode)
           {
              CDRExchangerateFlag = 1 ;
              break;
           }
        }

        if(CDRExchangerateFlag == 0)
        {
           REI.ERROR_CODE[gRejectedErrorNo]  = 101                  ;
           REI.APPLICATION_TAG[gRejectedErrorNo] = 105             ;
           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
           if(lValidateFlag == 0)
           {
               strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
               strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ExchangeRateCode") ;
               sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.SessionChargeInformation,"105:0:L")        ;
               fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
               strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Specified Exchange Rate Code not defined in group Currency Conversion");
               strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
               gRejectedErrorNo++ ;
           }
           ReturnValue = 0 ;
        }
}
 /* Read CallTypeGroup */
    
        if(NOT_NULL(SCI->callTypeGroup))
        {

            INIT_STR(stContext.CallTypeGroup) ;
            sprintf(stContext.CallTypeGroup,"%s;258:0:L",stContext.CallEventType);
            fnRemTrailSpaces(stContext.CallTypeGroup) ;

           
            if(NOT_NULL(SCI->callTypeGroup->callTypeLevel1))
            {
                BCT.CALL_TYPE_LEVEL1          = *SCI->callTypeGroup->callTypeLevel1;


                /* CallTypeLevel1 : Syntax Error Check */
                sprintf (TempNumtoChar,"%d",BCT.CALL_TYPE_LEVEL1);
                ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
                if(ReturnValue != 0)
                {
                    REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                    REI.APPLICATION_TAG[gRejectedErrorNo] = 259             ;
                    strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                    lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                    if(lValidateFlag == 0)
                    {
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/GPRS/MTC")  ;
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeLevel1")               ;
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallTypeGroup,"259:0:L")      ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                        gRejectedErrorNo++ ;
                    }

                    ReturnValue = 0 ;
                }
             
                    Pointer = NULL;
                    Pointer = strstr("0:1:2",TempNumtoChar);

                     if(Pointer == NULL && BCT.CALL_TYPE != 0)
                     {
                         REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                         REI.APPLICATION_TAG[gRejectedErrorNo] = 259             ;
                         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/GPRS/MTC/MSESS")  ;
                             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeLevel1")               ;
                             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallTypeGroup,"259:0:L")      ;
                             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                             gRejectedErrorNo++ ;
                         }

                         ReturnValue = 0 ;
                     }                   
                

            }
            else
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 258                          ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MobileSession")  ;
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeGroup")               ;
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallTypeGroup)        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Call Type Level 1 missing within group");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                    gRejectedErrorNo++ ;
                }
            }

    
            if(NOT_NULL(SCI->callTypeGroup->callTypeLevel2))
            {
                BCT.CALL_TYPE_LEVEL2          = *SCI->callTypeGroup->callTypeLevel2;


                /* CallTypeLevel2 : Syntax Error Check */
                sprintf (TempNumtoChar,"%d",BCT.CALL_TYPE_LEVEL2);
                ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
                if(ReturnValue != 0)
                {
                    REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                    REI.APPLICATION_TAG[gRejectedErrorNo] = 255             ;
                    strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                    lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                    if(lValidateFlag == 0)
                    {
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MobileSession")  ;
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeLevel2")               ;
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallTypeGroup,"255:0:L")      ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                        gRejectedErrorNo++ ;
                    }

                    ReturnValue = 0 ;
                }
                     Pointer = NULL;
                     if (BCT.CALL_TYPE == 1)
		             Pointer = strstr("0:7",TempNumtoChar);
		             else if (BCT.CALL_TYPE == 2)
                     Pointer = strstr("0:1:2:3:4:5",TempNumtoChar);               
		
                if(Pointer == NULL && BCT.CALL_TYPE != 0)
                {
                    REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                    REI.APPLICATION_TAG[gRejectedErrorNo] = 255             ;
                    strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                    lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                    if(lValidateFlag == 0)
                    {
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MobileSession")  ;
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeLevel2")               ;
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallTypeGroup,"255:0:L")      ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                        gRejectedErrorNo++ ;
                    }

                    ReturnValue = 0 ;
                }
            }
            else
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 258                          ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/GPRS/MTC")  ;
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeGroup")               ;
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallTypeGroup)        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Call Type Level 2 missing within group");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                    gRejectedErrorNo++ ;
                }
            }


            if(NOT_NULL(SCI->callTypeGroup->callTypeLevel3))
            {
                BCT.CALL_TYPE_LEVEL3          = *SCI->callTypeGroup->callTypeLevel3;
 
                /* CallTypeLevel3 : Syntax Error Check */
                sprintf (TempNumtoChar,"%d",BCT.CALL_TYPE_LEVEL3);
                ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
                if(ReturnValue != 0)
                {
                    REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                    REI.APPLICATION_TAG[gRejectedErrorNo] = 256             ;
                    strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                    lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                    if(lValidateFlag == 0)
                    { 
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/GPRS/MTC")  ;
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeLevel3")               ;
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.CallTypeGroup,"256:0:L")      ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                        gRejectedErrorNo++ ;
                    }

                    ReturnValue = 0 ;
                }
            }
            else
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 258                          ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/GPRS/MTC")  ;
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CallTypeGroup")               ;
                    strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallTypeGroup)        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Call Type Level 3 missing within group");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                    gRejectedErrorNo++ ;
                }
            }

        }
        else
        {
            REI.ERROR_CODE[gRejectedErrorNo]  = 32                             ;
            REI.APPLICATION_TAG[gRejectedErrorNo] = 69                          ;
            strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
            lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
            if(lValidateFlag == 0)
            {
                strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS")  ;
                strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"MSESS")  ;
                strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.SessionChargeInformation)        ;
                fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Item Call Type Group missing within group ");
                strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                gRejectedErrorNo++ ;
            }
        }

   
   /*
   printf("Charged Item   : -%s- \n",BCT.CHARGED_ITEM);
   printf("Exchange Rate  : -%d- \n",BCT.TAP_EXCHANGE_RATE_CODE);
   printf("CalltypeLevel1 : -%d- \n",BCT.CALL_TYPE_LEVEL1);
   printf("CalltypeLevel2 : -%d- \n",BCT.CALL_TYPE_LEVEL2);
   printf("CalltypeLevel3 : -%d- \n",BCT.CALL_TYPE_LEVEL3);
   */

/* Loop through the ChargeDetailList */

   lChargeTypeFlag = 0 ;
   INIT_STR(gIOTChargeContext)    ;
   INIT_STR(gIOTTaxContext)       ;
   INIT_STR(gIOTDiscountContext)  ;
   if(NOT_NULL(SCI->chargeDetailList))
   {
      FOR_EACH_LIST_ELMT(CD,SCI->chargeDetailList)
      {
         CDLCount = 0;
         lChargeableUnitsFlag = 0;

         INIT_STR(stContext.ChargeDetail) ;
         sprintf(stContext.ChargeDetail,"%s;64:%d:L;63:0:L",stContext.SessionChargeInformation,CDLCount+1);
         fnRemTrailSpaces(stContext.ChargeDetail) ;
        
         strcpy(gIOTChargeContext,stContext.ChargeDetail);


         if(ASNOCTS_PRESENT(&CD->chargeType))
         {
            strcpy(BCT.CHARGE_TYPE,CD->chargeType.octs);

            /* ChargeType : Syntax Error Check */
            ReturnValue = fnCheckSyntax(BCT.CHARGE_TYPE,"DI") ;
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 71              ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeType");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeDetail,"71:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CHARGE_TYPE);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }

            /* ChargeType :Value Out Of Range */

            Pointer = NULL;
            Pointer = strstr("00:01:02:03:04:21:50",BCT.CHARGE_TYPE);
            if(Pointer == NULL)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 71              ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeType");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeDetail,"71:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],BCT.CHARGE_TYPE);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }


         }
         else
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 38                             ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 63                         ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeDetail")               ;
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargeDetail)        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Charge Type not present within group");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                 gRejectedErrorNo++ ;
             }
         }


         if(NOT_NULL(CD->charge))
         {
            /* Accumulate Charge for ChargeType '00' within the ChargeDetailList */
            if(strcmp(BCT.CHARGE_TYPE,"00")==0)
            {
               BCT.CHARGE = BCT.CHARGE + *CD->charge;

               lChargeTypeFlag = 1 ;
               /* Charge : Syntax Error Check */
               sprintf (TempNumtoChar,"%d",*CD->charge);
               ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
               if(ReturnValue != 0)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 62              ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Charge");
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeDetail,"62:0:L")        ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                        gRejectedErrorNo++ ;
                   }
                   ReturnValue = 0 ;
               }

               /* Charge : Value Out of Range */

               if (*CD->charge < 0) 
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 62              ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Charge");
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeDetail,"62:0:L")        ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }
                   ReturnValue = 0 ;
               }
            }

            if((strcmp(BCT.CHARGE_TYPE,"01")==0) || (strcmp(BCT.CHARGE_TYPE,"03")==0) || (strcmp(BCT.CHARGE_TYPE,"04")==0) || (strcmp(BCT.CHARGE_TYPE,"21")==0))
            {
                CDROtherTypeChargeFlag = 1 ;
                CDROtherTypeCharge = CDROtherTypeCharge + *CD->charge ;
            }
     
         }
         else
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 39                             ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 63                         ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeDetail")               ;
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargeDetail)        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Charge not present within group");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                 gRejectedErrorNo++ ;
             }
         }

  if(NOT_NULL(CD->chargeableUnits))
         {
            lChargeableUnitsFlag = 1 ;
            /* Get the Chargeable Units for ChargeType '00' */
            if(strcmp(BCT.CHARGE_TYPE,"00")==0)
            {
               BCT.CHARGEABLE_UNITS = BCT.CHARGEABLE_UNITS + *CD->chargeableUnits;

               /* ChargeableUnits : Syntax Error Check */
               sprintf (TempNumtoChar,"%d",*CD->chargeableUnits);
               ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
               if(ReturnValue != 0)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 65              ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                       strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                       strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeableUnits");
                       sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeDetail,"65:0:L")        ;
                       fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                       strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                       strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                       gRejectedErrorNo++ ;
                   }
                   ReturnValue = 0 ;
               }

               /* ChargeableUnits : Value Out of Range */

               if (*CD->chargeableUnits < 0)
               {
                   REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                   REI.APPLICATION_TAG[gRejectedErrorNo] = 65              ;
                   strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                   lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                   if(lValidateFlag == 0)
                   {
                        strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                        strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeableUnits");
                        sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeDetail,"65:0:L")        ;
                        fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                        strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                        strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                        gRejectedErrorNo++ ;
                   }
                   ReturnValue = 0 ;
               }
            }


            if((strcmp(BCT.CHARGED_ITEM,"D") ==0) && (*CD->chargeableUnits > BCT.CALL_DURATION))
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 100                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 65              ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MOC/MTC/GPRS");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeableUnits");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.ChargeDetail,"65:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Chargeable Units for Charge Type '00' are greater than Total Call Event Duration for Charged Item 'D'");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }

           }          

         if(strcmp(BCT.CHARGED_ITEM,"D") ==0)
         {
             if(lChargeableUnitsFlag == 0)
             {
                 REI.ERROR_CODE[gRejectedErrorNo]  = 33                             ;
                 REI.APPLICATION_TAG[gRejectedErrorNo] = 63                         ;
                 strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
                 lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                 if(lValidateFlag == 0)
                 {
                     strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
                     strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ChargeDetail")               ;
                     strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ChargeDetail)        ;
                     fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                     strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Associated item Charged Item is one of D and item Chargeable Units not present");
                     strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                     gRejectedErrorNo++ ;
                 }
             }
         }

         if(NOT_NULL(CD->chargedUnits))
         {
            /* Get the ChargedUnits for ChargeType '00' */
            if(strcmp(BCT.CHARGE_TYPE,"00")==0)
            {
               BCT.CHARGED_UNITS = BCT.CHARGED_UNITS + *CD->chargedUnits;
            }
         }
      }


      if((BCT.CHARGE > 0) && (lExchangeRateCodeFlag == 1))
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 31                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 69                          ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SessionChargeInformation")               ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.SessionChargeInformation)        ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Item Exchange Rate Code missing within group and one or more Charge within an associated Charge Detail is grea	      ter than zero");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }


      if(lChargeTypeFlag == 0)
      {
          REI.ERROR_CODE[gRejectedErrorNo]  = 36                             ;
          REI.APPLICATION_TAG[gRejectedErrorNo] = 69                         ;
          strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
          if(lValidateFlag == 0)
          {
              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
              strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SessionChargeInformation")               ;
              strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.SessionChargeInformation)        ;
              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
              strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Occurrence of group Charge Detail containing Charge Type '00' missing within group");
              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
              gRejectedErrorNo++ ;
          }
      }

      if((lChargeTypeFlag == 1) && (CDROtherTypeChargeFlag == 1))
      {
          if(BCT.CHARGE != CDROtherTypeCharge)
          {
              REI.ERROR_CODE[gRejectedErrorNo]  = 39                             ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 69                         ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SessionChargeInformation")               ;
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.SessionChargeInformation)        ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"In accordance with roaming agreement, charges are defined in individual Charge Types, but the Charge for C                  harge Type 00 does not equal sum of Charges for the other Charge Types as stated within roaming agreement.");
                  sprintf (REI.ERROR_VALUE[gRejectedErrorNo],"%d",BCT.CHARGE);
                  gRejectedErrorNo++ ;
              }
          }
      }

    if(NOT_NULL(CD->chargeDetailTimeStamp))
   {
                      
    	 sprintf(ChargeTimeStamp,"%d",(*CD->chargeDetailTimeStamp));

    	 if (ChargeTimeStamp > BCT.CALL_DATE)
     	 {
              REI.ERROR_CODE[gRejectedErrorNo]  = 100                           ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 447                        ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS")  ;
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"ServiceStartTimeStamp")               ;
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.ServiceStartTimestamp)        ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Service Start Timestamp after Charge Detail Timestamp.");
                  sprintf (REI.ERROR_VALUE[gRejectedErrorNo],"%d",BCT.CALL_DATE);
                  gRejectedErrorNo++ ;
              }
          
         }       
     }
  }

      /*
      
printf("Charge Type : -%s- \n",BCT.CHARGE_TYPE);
      printf("Charge      : -%f- \n",BCT.CHARGE);
      printf("ChargableUnt: -%f- \n",BCT.CHARGEABLE_UNITS);
      printf("ChargedUnit : -%f- \n",BCT.CHARGED_UNITS);
      */

   else
   {
       REI.ERROR_CODE[gRejectedErrorNo]  = 33                             ;
       REI.APPLICATION_TAG[gRejectedErrorNo] = 69                          ;
       strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
       lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
       if(lValidateFlag == 0)
       {
           strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
           strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"SessionChargeInformation")               ;
           strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.SessionChargeInformation)        ;
           fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
           strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Group Charge Detail missing within group");
           strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
           gRejectedErrorNo++ ;
       }
   }

/*gTaxListFlag variable  added to check Whether TaxInformation Node Present or not */

gTaxListFlag=0;
 
/* Loop through the TaxInformationList */
   if(NOT_NULL(SCI->taxInformationList))
   {

   gTaxListFlag=1;
   FOR_EACH_LIST_ELMT(TI,SCI->taxInformationList)
      {
         TICount = 0;
         

         INIT_STR(stContext.TaxInformation) ;
         sprintf(stContext.TaxInformation,"%s;214:%d:L;213:0:L",stContext.SessionChargeInformation,TICount+1);
         fnRemTrailSpaces(stContext.TaxInformation) ;

         strcpy(gIOTTaxContext,stContext.TaxInformation);

         if(NOT_NULL(TI->taxCode))
         {
             BCT.TAX_CODE = *TI->taxCode;

             /* TaxCode : Syntax Error Check */
             sprintf (TempNumtoChar,"%d",BCT.TAX_CODE);
             ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
             if(ReturnValue != 0)
             {
                 REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
                 REI.APPLICATION_TAG[gRejectedErrorNo] = 212             ;
                 strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                 lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                 if(lValidateFlag == 0)
                 {
                     strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                     strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxCode");
                     sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.TaxInformation,"212:0:L")        ;
                     fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                     strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                     strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                     gRejectedErrorNo++ ;
                 }
                 ReturnValue = 0 ;
             }

            CDRTaxCodeFlag = 0;

            for(i=0;i<gTaxationCount;i++)
            {
                if(BCT.TAX_CODE == ACC.Taxation[i].TaxCode)
                {
                   CDRTaxCodeFlag = 1;
                    break;
                }
            }

            if(CDRTaxCodeFlag==0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 100                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 212             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxCode");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.TaxInformation,"212:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Specified Tax Rate Code was not defined in the group Taxation");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }


         }
         else
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 30                             ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 213                          ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")                  ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxInformation")               ;
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.TaxInformation)        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Tax Rate Code missing within group");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                 gRejectedErrorNo++ ;
             }
         }


         if(NOT_NULL(TI->taxValue))
         {
            /* Accumulate the TotalTax for the Call */
            BCT.TAX_VALUE = BCT.TAX_VALUE + *TI->taxValue;

            /* TaxValue : Syntax Error Check */
            sprintf (TempNumtoChar,"%d",BCT.TAX_VALUE);
            ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 397             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxValue");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.TaxInformation,"397:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }


            /* Taxvalue : Value Out of Range */

            if (BCT.TAX_VALUE < 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 397             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxValue");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.TaxInformation,"397:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }

         }
         else
         {
             REI.ERROR_CODE[gRejectedErrorNo]  = 31              ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 213         ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")   ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls")  ;
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxInformation")               ;
                 strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.TaxInformation)        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Mandatory item Tax Value missing within group");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                 gRejectedErrorNo++ ;
             }
         }


         if(NOT_NULL(TI->taxableAmount))
         {
            /* Accumulate the TotalTaxable amount for the Call */
            BCT.TAXABLE_AMOUNT = BCT.TAXABLE_AMOUNT + *TI->taxableAmount;

            /* TaxableAmount : Syntax Error Check */
            sprintf (TempNumtoChar,"%d",BCT.TAXABLE_AMOUNT);
            ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
            if(ReturnValue != 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 10                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 398             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxableAmount");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.TaxInformation,"398:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }


            /* TaxableAmount : Value Out of Range */

            if (BCT.TAXABLE_AMOUNT <= 0)
            {
                REI.ERROR_CODE[gRejectedErrorNo]  = 20                  ;
                REI.APPLICATION_TAG[gRejectedErrorNo] = 398             ;
                strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                if(lValidateFlag == 0)
                {
                    strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                    strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxableAmount");
                    sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",stContext.TaxInformation,"398:0:L")        ;
                    fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                    strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Value out of range");
                    strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                    gRejectedErrorNo++ ;
                }
                ReturnValue = 0 ;
            }


         }

         /* Added by Chetan on 14-May-2009 to store Tax Details */

         for(k=0; k<gTaxationCount; k++)
         {
            if((ACC.Taxation[k].TaxCode == BCT.TAX_CODE) && (BCT.TAX_VALUE > 0))
            {
               if(strlen(BCT.TAP_TAX_TYPE_RATE) < 100)
               {
                   sprintf(BCT.TAP_TAX_TYPE_RATE,"%s%s:%d;",BCT.TAP_TAX_TYPE_RATE,ACC.Taxation[k].TaxType,ACC.Taxation[k].TaxRate) ;
               }
               break ;
            }
         }

         TICount++;

         /* This count indicates if more than 1tax is present for the call */
         BCT.TAX_INFORMATION_COUNT    = BCT.TAX_INFORMATION_COUNT + 1;
   }

}


if(( BCT.TAX_INFORMATION_COUNT>0) && (gTapinTaxFlag ==0))
      	 {       
              REI.ERROR_CODE[gRejectedErrorNo]  = 40                 ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 213             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
              lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxGroup") ;
                  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType) ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Group Tax Information present within group but not expected in accordance with roaming agreement for the call/event and Tax Value referenced within the group is greater than 0 ");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                  gRejectedErrorNo++ ;
              }
         }


    	 if(( BCT.TAX_INFORMATION_COUNT==0) && (gTapinTaxFlag ==1) )
        	 {            
             
	   	          REI.ERROR_CODE[gRejectedErrorNo]  = 34                 ;
             	  REI.APPLICATION_TAG[gRejectedErrorNo] = 213             ;
             	  strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
             	  lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
             	 if(lValidateFlag == 0)
             	 {
                	  
                  	  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                 	  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxGroup") ;
                	  strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],stContext.CallEventType) ;
                 	  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                	  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Group Tax Information missing within group but expected in accordance with roaming agreement for that particular call. Tax Information group missing must be interpreted as Tax Value 0  ");
                 	 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],"Not Applicable");
                 	 gRejectedErrorNo++ ;
            	  }
        	}


}

void ReadRecEntityCodeList(RecEntityCodeList* recEntityCodeList)
{
   RecEntityCode *REC;
   int i=0,j=0;
   REC_ENTITY_COUNT = 0;
   int ErrorReturnValue = 0;
   int ReturnValue = 0;
   char TempNumtoChar [10]   ;
   int RecordingEntityFlag = 0 ;
   int  lValidateFlag = 0    ;
   char RecEntityId[46];

   INIT_STR(stContext.RecEntityCodeList);
   sprintf(stContext.RecEntityCodeList,"%s;117:0:L",stContext.CallEventType) ;
   fnRemTrailSpaces(stContext.RecEntityCodeList) ;
   
   if(NOT_NULL(recEntityCodeList))
      {
         FOR_EACH_LIST_ELMT(REC,recEntityCodeList)
         {
            RECORDING_ENTITY_CODES[i] = *REC;
            i++;
         }
      }



      REC_ENTITY_COUNT = i;

      for(j=0;j<REC_ENTITY_COUNT;j++)
      {
          /* RecEntityCode : Syntax Error Check */
          sprintf (TempNumtoChar,"%d", RECORDING_ENTITY_CODES[j]);
          ReturnValue = fnCheckSyntax(TempNumtoChar,"DI") ;
          if(ReturnValue != 0)
          {
              REI.ERROR_CODE[gRejectedErrorNo]  = 11                  ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 184             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
              lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
              if(lValidateFlag == 0)
              {
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"MSESS");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityCode") ;
                  sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;185:%d:L;184:0:L",stContext.RecEntityCodeList,j+1)        ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Syntax error");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }
              ReturnValue = 0 ;
          }
      }


      for(j=0;j<REC_ENTITY_COUNT;j++)
      {
          RecordingEntityFlag = 0 ;
          INIT_STR(TempNumtoChar) ;
          for(i=0;i<gRecEntityInfoCount;i++)
          {
		 
             if(RECORDING_ENTITY_CODES[j] == NI.RecEntityInfo[i].RecEntityCode)
             {
                  sprintf (TempNumtoChar,"%d", RECORDING_ENTITY_CODES[j]);
              
			  
                  if(NI.RecEntityInfo[i].RecEntityType == 7)
	           {		   
	                  strcpy(RecEntityId,NI.RecEntityInfo[i].RecEntityId);
        	     if((fnValidateIPV4(RecEntityId)!=0) && (fnValidateIPV6(RecEntityId)!=0 ))
	               {
			  REI.ERROR_CODE[gRejectedErrorNo]  = 106                  ;
                          REI.APPLICATION_TAG[gRejectedErrorNo] = 184             ;
                   	  strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                     	  lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                      if(lValidateFlag == 0)
                      {
                          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS/MSESS/MTC");
                          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityCode") ;
                      	  sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;185:%d:L;184:0:L",stContext.RecEntityCodeList,j+1)        ;
                          fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Entity Code refers to P-GW (Recording Entity Type 7) and syntax of the referenced Recording Entity Identification does not conform to Text Representation of IP Addresses.");
                          strcpy(REI.ERROR_VALUE[gRejectedErrorNo],NI.RecEntityInfo[i].RecEntityId);
                         gRejectedErrorNo++ ;
                     }
                      ReturnValue = 0 ;
		   }
               }
     		  else  if(NI.RecEntityInfo[i].RecEntityType == 8)
	    	  	{
		   	strcpy(RecEntityId,NI.RecEntityInfo[i].RecEntityId);   
                        if((fnValidateIPV4(RecEntityId)!=0) && (fnValidateIPV6(RecEntityId)!=0 ))
		         {
					
                           REI.ERROR_CODE[gRejectedErrorNo]  = 107                  ;
                           REI.APPLICATION_TAG[gRejectedErrorNo] = 184             ;
                           strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                           lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                           if(lValidateFlag == 0)
                           {
                              strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS/MSESS/MTC");
                   	      strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityCode") ;
                 	      sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;185:%d:L;184:0:L",stContext.RecEntityCodeList,j+1)        ;
                              fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                	      strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Entity Code refers to S-GW (Recording Entity Type 8) and syntax of the referenced Recording Entity Identification does not conform to Text Representation of IP Addresses.");
                 	      strcpy(REI.ERROR_VALUE[gRejectedErrorNo],NI.RecEntityInfo[i].RecEntityId);
                              gRejectedErrorNo++ ;
                           }
               	          ReturnValue = 0 ;
                        }
                      }
		else  if(NI.RecEntityInfo[i].RecEntityType == 9)
		  { 
			    strcpy(RecEntityId,NI.RecEntityInfo[i].RecEntityId);
                           if((fnValidateIPV4(RecEntityId)!=0) && (fnValidateIPV6(RecEntityId)!=0 ))
				  {
                     			  REI.ERROR_CODE[gRejectedErrorNo]  = 108                  ;
              				  REI.APPLICATION_TAG[gRejectedErrorNo] = 184             ;
             				  strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")        ;
                                          lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
       			       if(lValidateFlag == 0)
             			 {
                 			 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"GPRS/MSESS/MTC");
             				 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityCode") ;
            				 sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;185:%d:L;184:0:L",stContext.RecEntityCodeList,j+1)        ;
                			 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  			 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Entity Code refers to P-CSCF (Recording Entity Type 9) and syntax of the referenced Recording Entity Identification does not conform to Text Representation of IP Addresses.");
                  			 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],NI.RecEntityInfo[i].RecEntityId);
               			         gRejectedErrorNo++ ;
                                 }
                                ReturnValue = 0 ;
			  }
		  }
        
					 

                 RecordingEntityFlag = 1 ;                  
				 break;
             }
             }

       /*   sprintf (TempNumtoChar,"%d", RECORDING_ENTITY_CODES[j]);  */

          if(RecordingEntityFlag == 0)
          {
             REI.ERROR_CODE[gRejectedErrorNo]  = 100                 ;
             REI.APPLICATION_TAG[gRejectedErrorNo] = 184             ;
             strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
             lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
             if(lValidateFlag == 0)
             {
                 strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                 strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"RecEntityCode") ;
                 sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;185:%d:L;184:0:L",stContext.RecEntityCodeList,j+1)        ;
                 fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                 strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Specified recording entity code not defined in the Recording Entity Information");
                 strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                 gRejectedErrorNo++ ; 
             }
             ReturnValue = 0 ;
          }
      }
    }

int fnValidateIPV4(char FieldValue[46]) 
{
  char * pch;
  int count=0;
  int  ReturnValue = 0 ;
  pch = strtok (FieldValue,".");
  int Value;
  int Length =0;
  
  
  while (pch != NULL)
  {
    ReturnValue = fnCheckSyntax(pch,"DI") ;
	Value =atoi(pch);
	Length = strlen(pch) ;

	if(ReturnValue !=0 || Value>255 || Length >3 || Length == 0)
	{
	 return -1;
	 break;
	}
    pch = strtok (NULL, ".");
    count++;
  }
  
 if(ReturnValue ==0 )
  {
  if (count!=4)
  {
  return -1;
  }
  }
  return 0 ;

}

int fnValidateIPV6(char FieldValue[46]) 
{

  char * pch;
  int count=0;
  int  ReturnValue = 0 ;
  pch = strtok (FieldValue,":");
  int Length=0,i=0;


  while (pch != NULL)
  {
  Length = strlen(pch) ;

     ReturnValue = fnCheckSyntax(pch,"DX") ;
		 if(ReturnValue !=0 || Length>4 || Length ==0)
	    {
	      return -1;
	      break;
     	}
  
    pch = strtok (NULL, ":");
    count++;
	}
  
 
 if(ReturnValue ==0)
  {
  if (count!=8)
  {
  return -1;
  }
  }
  return 0 ;
 
}

