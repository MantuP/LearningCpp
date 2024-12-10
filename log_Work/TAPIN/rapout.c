
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
#include <rap105.h>

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

#define DATA_MAX_SIZE           150485760 /* 20485760  1.5 MB memory alloted  1.5*1024*1024 = 1572864 */
#define INIT_STR(vc_x) (memset(vc_x,'\0',sizeof(vc_x)));
char data[DATA_MAX_SIZE];

extern long   gRapFileSequenceNumber ;
extern char   gUTCOffset[7];
extern int    gRapSpecificationVersion;
extern int    gRapReleaseVersion;
extern char   gFileHplmnCode[6] ;
extern char   gRapFileCreationTime[15] ;
extern double gIOTCharge ;

/*extern char StIOTCdr.CALL_DATE[30]; */



RapDataInterChange RDIC;


struct ReturnDetail **RD;
struct ErrorDetail **ACV;

/* This function will load the ReturnBatch sructure */
void EncodeReturnBatch()
{
   /* used to alloc part of value (Asn1Alloc & AsnListAppend) */
   InitNibbleMem (512,512);

   /* This Rap file is of returnbatch type */
   RDIC.choiceId = RAPDATAINTERCHANGE_RETURNBATCH;
   RDIC.a.returnBatch =(ReturnBatch*) Asn1Alloc(sizeof(ReturnBatch));
}

void EncodeRAPBatchControlInfo()
{
   unsigned char RFSN[6];
   unsigned char TFSN[6];

   sprintf(RFSN,"%.5d",gRapFileSequenceNumber);
   sprintf(TFSN,"%.5d",BCI.FileSequenceNumber);

   /* Allocate memory ,set length and load data into sender */
   RDIC.a.returnBatch->rapBatchControlInfoRap = (struct RapBatchControlInfo*) Asn1Alloc(sizeof(RapBatchControlInfo));
  
   RDIC.a.returnBatch->rapBatchControlInfoRap->sender.octs = (unsigned char*)Asn1Alloc(sizeof(gFileHplmnCode));
   strcpy(RDIC.a.returnBatch->rapBatchControlInfoRap->sender.octs,gFileHplmnCode);
   RDIC.a.returnBatch->rapBatchControlInfoRap->sender.octetLen = strlen(gFileHplmnCode);


   /* Allocate memory ,set length and load data into recipient */
   RDIC.a.returnBatch->rapBatchControlInfoRap->recipient.octs = (unsigned char*)Asn1Alloc(sizeof(BCI.Sender));
   strcpy(RDIC.a.returnBatch->rapBatchControlInfoRap->recipient.octs,BCI.Sender);
   RDIC.a.returnBatch->rapBatchControlInfoRap->recipient.octetLen = strlen(BCI.Sender);

   /* Allocate memory, load data and set length in fileSequenceNumber */
   RDIC.a.returnBatch->rapBatchControlInfoRap->rapFileSequenceNumber.octs = (unsigned char*)Asn1Alloc(sizeof(RFSN));
   strcpy(RDIC.a.returnBatch->rapBatchControlInfoRap->rapFileSequenceNumber.octs,RFSN);
   RDIC.a.returnBatch->rapBatchControlInfoRap->rapFileSequenceNumber.octetLen = strlen(RFSN);


   /* Allocate memory ,set length and load data into rapFileCreationTimeStamp */
   RDIC.a.returnBatch->rapBatchControlInfoRap->rapFileCreationTimeStamp = (RapFileCreationTimeStamp*) Asn1Alloc(sizeof(RapFileCreationTimeStamp));


   /* Allocate memory ,set length and load data into localTimeStamp which is a member of */
   /* rapFileCreationTimeStamp structure */
   RDIC.a.returnBatch->rapBatchControlInfoRap->rapFileCreationTimeStamp->localTimeStamp.octs = (unsigned char*)Asn1Alloc(sizeof(gRapFileCreationTime));
   strcpy(RDIC.a.returnBatch->rapBatchControlInfoRap->rapFileCreationTimeStamp->localTimeStamp.octs,gRapFileCreationTime);
   RDIC.a.returnBatch->rapBatchControlInfoRap->rapFileCreationTimeStamp->localTimeStamp.octetLen = strlen(gRapFileCreationTime);

   /* Allocate memory ,set length and load data into utcTimeOffset which is a member of */
   /* rapFileCreationTimeStamp structure */

   RDIC.a.returnBatch->rapBatchControlInfoRap->rapFileCreationTimeStamp->utcTimeOffset.octs = (unsigned char*)Asn1Alloc(sizeof(gUTCOffset));
   strcpy(RDIC.a.returnBatch->rapBatchControlInfoRap->rapFileCreationTimeStamp->utcTimeOffset.octs, gUTCOffset);
   RDIC.a.returnBatch->rapBatchControlInfoRap->rapFileCreationTimeStamp->utcTimeOffset.octetLen = strlen(gUTCOffset);


   /* Allocate memory ,set length and load data into rapFileAvailableTimeStamp */

   RDIC.a.returnBatch->rapBatchControlInfoRap->rapFileAvailableTimeStamp = (RapFileAvailableTimeStamp*) Asn1Alloc(sizeof(RapFileAvailableTimeStamp));


   /* Allocate memory ,set length and load data into localTimeStamp which is a member of */
   /* rapFileAvailableTimeStamp structure */

   RDIC.a.returnBatch->rapBatchControlInfoRap->rapFileAvailableTimeStamp->localTimeStamp.octs = (unsigned char*)Asn1Alloc(sizeof(gRapFileCreationTime));
   strcpy(RDIC.a.returnBatch->rapBatchControlInfoRap->rapFileAvailableTimeStamp->localTimeStamp.octs,gRapFileCreationTime);
   RDIC.a.returnBatch->rapBatchControlInfoRap->rapFileAvailableTimeStamp->localTimeStamp.octetLen = strlen(gRapFileCreationTime);

   /* Allocate memory ,set length and load data into utcTimeOffset which is a member of */
   /* rapFileAvailableTimeStamp structure */

   RDIC.a.returnBatch->rapBatchControlInfoRap->rapFileAvailableTimeStamp->utcTimeOffset.octs = (unsigned char*)Asn1Alloc(sizeof(gUTCOffset));
   strcpy(RDIC.a.returnBatch->rapBatchControlInfoRap->rapFileAvailableTimeStamp->utcTimeOffset.octs, gUTCOffset);
   RDIC.a.returnBatch->rapBatchControlInfoRap->rapFileAvailableTimeStamp->utcTimeOffset.octetLen = strlen(gUTCOffset);


  /* Allocate memory ,set length and load data into specificationVersionNumber */

   RDIC.a.returnBatch->rapBatchControlInfoRap->specificationVersionNumber = (SpecificationVersionNumber*) Asn1Alloc(sizeof(SpecificationVersionNumber));
   *RDIC.a.returnBatch->rapBatchControlInfoRap->specificationVersionNumber = BCI.SpecificationVersionNumber;



   /* Allocate memory ,set length and load data into releaseVersionNumber */

   RDIC.a.returnBatch->rapBatchControlInfoRap->releaseVersionNumber  = (ReleaseVersionNumber*) Asn1Alloc(sizeof(ReleaseVersionNumber));
   *RDIC.a.returnBatch->rapBatchControlInfoRap->releaseVersionNumber = BCI.ReleaseVersionNumber;

     /* Allocate memory ,set length and load data into tapdecimalplaces */     
     /* Added by Anitha for rap 1.5*/

      RDIC.a.returnBatch->rapBatchControlInfoRap->tapDecimalPlaces  = (TapDecimalPlaces*) Asn1Alloc(sizeof(TapDecimalPlaces));
     *RDIC.a.returnBatch->rapBatchControlInfoRap->tapDecimalPlaces = ACC.TapDecimalPlaces;



   /* Allocate memory ,set length and load data into rapSpecificationVersionNumber */


   RDIC.a.returnBatch->rapBatchControlInfoRap->rapSpecificationVersionNumber = (RapSpecificationVersionNumber*) Asn1Alloc(sizeof(RapSpecificationVersionNumber));
   RDIC.a.returnBatch->rapBatchControlInfoRap->rapSpecificationVersionNumber= gRapSpecificationVersion;



   /* Allocate memory ,set length and load data into rapReleaseVersionNumber */

   RDIC.a.returnBatch->rapBatchControlInfoRap->rapReleaseVersionNumber  = (RapReleaseVersionNumber*) Asn1Alloc(sizeof(RapReleaseVersionNumber));
   RDIC.a.returnBatch->rapBatchControlInfoRap->rapReleaseVersionNumber = gRapReleaseVersion;


   /* Allocate memory ,set length and load data into fileTypeIndicator only if filetypeIndicator is 'T'*/
   if(strcmp(BCI.FileTypeIndicator,"T") == 0)
   {
                RDIC.a.returnBatch->rapBatchControlInfoRap->fileTypeIndicator.octs = (unsigned char*)Asn1Alloc(sizeof(BCI.FileTypeIndicator));
                strcpy(RDIC.a.returnBatch->rapBatchControlInfoRap->fileTypeIndicator.octs,BCI.FileTypeIndicator);
                RDIC.a.returnBatch->rapBatchControlInfoRap->fileTypeIndicator.octetLen = strlen(BCI.FileTypeIndicator);
   }


/* Allocate memory ,set length and load data into TapCurrency */
/* Added by Anitha for RAP 1.5*/

 if((strcmp(ACC.TapCurrency,"SDR")!=0) && (ACC.TapCurrency[0] != '\0'))
   {
     RDIC.a.returnBatch->rapBatchControlInfoRap->tapCurrency.octs =
      (char *)Asn1Alloc(strlen(ACC.TapCurrency));

      strcpy(RDIC.a.returnBatch->rapBatchControlInfoRap->tapCurrency.octs,ACC.TapCurrency);

     RDIC.a.returnBatch->rapBatchControlInfoRap->tapCurrency.octetLen = strlen(ACC.TapCurrency);
   }

   RDIC.a.returnBatch->returnDetails = AsnListNew (sizeof(void*));

}

void EncodeReturnDetails(long TapFileSeqNumber, PM_RAP_DETAILS  *IOTDetails)
/*void EncodeReturnDetails(long TapFileSeqNumber, char *ErrorType) */
{
   unsigned char TFSN[6];
   unsigned char ICharge[10];
   sprintf(TFSN,"%.5d",TapFileSeqNumber);
  

   RD  = AsnListAppend(RDIC.a.returnBatch->returnDetails);
   *RD = (ReturnDetail*) Asn1Alloc (sizeof(ReturnDetail));

   if(strcmp(IOTDetails->ERROR_TYPE,"FATAL") == 0)
   {
        /* Allocate memory for fatal return struture */
        (*RD)->choiceId = RETURNDETAIL_FATALRETURN;
        (*RD)->a.fatalReturn = (FatalReturn*)Asn1Alloc (sizeof(FatalReturn));

        /* Allocate memeory for the file sequence number and load data */
        (*RD)->a.fatalReturn->fileSequenceNumber.octs = (unsigned char*)Asn1Alloc(sizeof(TFSN));
        strcpy((*RD)->a.fatalReturn->fileSequenceNumber.octs,TFSN);
        (*RD)->a.fatalReturn->fileSequenceNumber.octetLen = strlen(TFSN);
   }
   else if(strcmp(IOTDetails->ERROR_TYPE,"SEVERE") == 0)
  /*else if(strcmp(ErrorType,"SEVERE") == 0) */
   {
        /* Allocate memory for severe return struture */
        (*RD)->choiceId = RETURNDETAIL_SEVERERETURN;
        (*RD)->a.severeReturn = (SevereReturn*)Asn1Alloc (sizeof(SevereReturn));

        /* Allocate memeory for the file sequence number and load data */
        (*RD)->a.severeReturn->fileSequenceNumber.octs = (unsigned char*)Asn1Alloc(sizeof(TFSN));
        strcpy((*RD)->a.severeReturn->fileSequenceNumber.octs,TFSN);
        (*RD)->a.severeReturn->fileSequenceNumber.octetLen = strlen(TFSN);

        /* Allocate memeory for the calleventdetail of the severereturn */
        (*RD)->a.severeReturn->callEventDetail = (CallEventDetail*)Asn1Alloc(sizeof(CallEventDetail));

   
  }

}

/* To  Encode Operator Specific Information */ 
void EncodeOSI(PM_RAP_DETAILS  *IOTDetails)
{
   OperatorSpecInformation **OSI;
   OperatorSpecInformation OSIO;
   unsigned char OSD[20];
   unsigned char Operator[25];
   unsigned char octetOperator[20];  /* AddressStringDigits */
   unsigned int operatorLen=0;

   unsigned char OSCh[25];
   unsigned char OSC[101];
   OperatorSpecInformation OS;
	
   /* Allocate memory for the OperatorSpecific Information of the severereturn */
	
   /*(*RD)->a.severeReturn->operatorSpecList= (OperatorSpecList*)Asn1Alloc(sizeof(OperatorSpecList));*/
   (*RD)->a.severeReturn->operatorSpecList= AsnListNew (sizeof(void*));
   
   OSI = AsnListAppend((*RD)->a.severeReturn->operatorSpecList);
   *OSI = (OperatorSpecInformation*) Asn1Alloc(sizeof(OperatorSpecInformation));
   /* **OSI = OS; */

   /* Allocate memory to the Node for IOT Date */
  // char str1[9];
   
 char *str1 ;
 str1 = (char *)malloc( 110 *sizeof(char));
 INIT_STR(str1) ;

   strcpy( str1,"IOTDate:");
   
    
   strcpy(OSD, strcat (str1,IOTDetails->IOT_DATE));
   sprintf(Operator,"%s",OSD);
   
   /* Assign Value to the Node for OSI */
   
  OSIO.octs = (unsigned char*)Asn1Alloc(sizeof(OSD));
  strcpy(OSIO.octs, OSD);

  OSIO.octetLen = strlen(OSD);
  **OSI = OSIO; 

  /* Allocate memory For IOT Charge */

  OSI = AsnListAppend((*RD)->a.severeReturn->operatorSpecList);
  *OSI = (OperatorSpecInformation*) Asn1Alloc(sizeof(OperatorSpecInformation));
 
  /* Allocate memory to the Node for OSI */

// char *str2 ;
// str2 = (char *)malloc( 110 *sizeof(char));
 //INIT_STR(str2) ;
 
// char *IOTCharge ;
// IOTCharge = (char *)malloc( 110 *sizeof(char));
 //INIT_STR(IOTCharge) ;
 

  char str2[11];
  char IOTCharge[6];
  strcpy( str2,"ExpCharge:");

  sprintf(IOTCharge,"%ld",IOTDetails->IOT_CHARGE);
  printf("IOTCharge %ld",IOTDetails->IOT_CHARGE);
  strcpy(OSCh, strcat (str2,IOTCharge));
  sprintf(Operator,"%s",OSCh);

   /* Assign Value to the Node for OSI */
   
  OSIO.octs = (unsigned char*)Asn1Alloc(sizeof(OSCh));
  strcpy(OSIO.octs, OSCh);

  OSIO.octetLen = strlen(OSCh);
  **OSI = OSIO; 

  /* Allocate memory For IOT Calculation */

  OSI = AsnListAppend((*RD)->a.severeReturn->operatorSpecList);
  *OSI = (OperatorSpecInformation*) Asn1Alloc(sizeof(OperatorSpecInformation));
 /* **OSI = OS; */
 
 /* Allocate memory to the Node for OSI */


 char *str3 ;
 str3 = (char *)malloc( 110 *sizeof(char));
 INIT_STR(str3) ;
 
  sprintf(str3,"%s","Calculation:");
   strcpy(OSC, strcat (str3,IOTDetails->IOT_CALCULATION));
  sprintf(Operator,"%s",OSC);  
 
   /* Assign Value to the Node for OSI */

 
  OSIO.octs = (unsigned char*)Asn1Alloc(sizeof(OSC));
  strcpy(OSIO.octs, OSC);
  OSIO.octetLen = strlen(OSC);
  **OSI = OSIO; 

}



void EncodeRapAuditControlInfo(long TapFileSeqNumber,double totalSevereReturnValue,long returnDetailsCount)
{
           /* ReturnSummary **RSUM; */
           unsigned char TFSN[6];
           sprintf(TFSN,"%.5d",TapFileSeqNumber);

           RDIC.a.returnBatch->rapAuditControlInfo = (RapAuditControlInfo*) Asn1Alloc(sizeof(RapAuditControlInfo));

        /*   RDIC.a.returnBatch->rapAuditControlInfo->returnSummaryList = AsnListNew (sizeof(void*));
           RSUM = AsnListAppend(RDIC.a.returnBatch->rapAuditControlInfo->returnSummaryList);
          *RSUM = (ReturnSummary*) Asn1Alloc(sizeof(ReturnSummary));
           (*RSUM)->fileSequenceNumber.octs = (unsigned char*)Asn1Alloc(sizeof(TFSN));
           strcpy((*RSUM)->fileSequenceNumber.octs,TFSN);
           (*RSUM)->fileSequenceNumber.octetLen = strlen(TFSN);
        */

           RDIC.a.returnBatch->rapAuditControlInfo->totalSevereReturnValue = (TotalSevereReturnValue*)Asn1Alloc(sizeof(TotalSevereReturnValue));
           RDIC.a.returnBatch->rapAuditControlInfo->totalSevereReturnValue = totalSevereReturnValue;

           RDIC.a.returnBatch->rapAuditControlInfo->returnDetailsCount = (ReturnDetailsCount*)Asn1Alloc(sizeof(ReturnDetailsCount));
           RDIC.a.returnBatch->rapAuditControlInfo->returnDetailsCount = returnDetailsCount ;

/*           RDIC.a.returnBatch->rapAuditControlInfo->totalSevereReturnTax = (TotalSevereReturnTax*)Asn1Alloc(sizeof(TotalSevereReturnTax));
           RDIC.a.returnBatch->rapAuditControlInfo->totalSevereReturnTax = totalSevereReturnTax;
*/
}





void EncodeMOC(MobileOriginatedCall* MOC)
{
                (*RD)->a.severeReturn->callEventDetail->choiceId = CALLEVENTDETAIL_MOBILEORIGINATEDCALL;
                (*RD)->a.severeReturn->callEventDetail->a.mobileOriginatedCall =
                      (MobileOriginatedCall*) Asn1Alloc (sizeof(MobileOriginatedCall));

                 (*RD)->a.severeReturn->callEventDetail->a.mobileOriginatedCall = MOC;

                 /* Build the error detail list */
                (*RD)->a.severeReturn->errorDetail = AsnListNew (sizeof(void*));
     /*           ACV = AsnListAppend((*RD)->a.severeReturn->errorDetail); */
}

void EncodeMTC(MobileTerminatedCall* MTC)
{
        (*RD)->a.severeReturn->callEventDetail->choiceId = CALLEVENTDETAIL_MOBILETERMINATEDCALL;
        (*RD)->a.severeReturn->callEventDetail->a.mobileTerminatedCall =
                (MobileTerminatedCall*) Asn1Alloc (sizeof(MobileTerminatedCall));

        ((*RD)->a.severeReturn->callEventDetail->a.mobileTerminatedCall) = MTC;

        /* Build the error detail list */
        (*RD)->a.severeReturn->errorDetail = AsnListNew (sizeof(void*));
        /* ACV = AsnListAppend((*RD)->a.severeReturn->errorDetail);*/
}

void EncodeGPRS(GprsCall* GC)
{
            (*RD)->a.severeReturn->callEventDetail->choiceId = CALLEVENTDETAIL_GPRSCALL;
            (*RD)->a.severeReturn->callEventDetail->a.gprsCall =
                      (GprsCall*) Asn1Alloc (sizeof(GprsCall));

            ((*RD)->a.severeReturn->callEventDetail->a.gprsCall) = GC;

            /* Build the error detail list */
            (*RD)->a.severeReturn->errorDetail = AsnListNew (sizeof(void*));
            /* ACV = AsnListAppend((*RD)->a.severeReturn->errorDetail);*/
}


void EncodeSUP(SupplServiceEvent* SUP)
{
                (*RD)->a.severeReturn->callEventDetail->choiceId = CALLEVENTDETAIL_SUPPLSERVICEEVENT;
                (*RD)->a.severeReturn->callEventDetail->a.supplServiceEvent=
                      (SupplServiceEvent*) Asn1Alloc (sizeof(SupplServiceEvent));

                 (*RD)->a.severeReturn->callEventDetail->a.supplServiceEvent= SUP;

                 /* Build the error detail list */
                (*RD)->a.severeReturn->errorDetail = AsnListNew (sizeof(void*));
     /*           ACV = AsnListAppend((*RD)->a.severeReturn->errorDetail); */
}

/* Function used when fatal error is found in Transfer Batch */
/* Allocate memory and load data into Error Detail */
/* Input Parameters : NULL */
/* Return Values : Null */

void EncodeMSESS(MobileSession* MSESS)
{
    (*RD)->a.severeReturn->callEventDetail->choiceId = CALLEVENTDETAIL_MOBILESESSION;
            (*RD)->a.severeReturn->callEventDetail->a.mobileSession =
                      (MobileSession*) Asn1Alloc (sizeof(MobileSession));

            ((*RD)->a.severeReturn->callEventDetail->a.mobileSession) = MSESS;

            /* Build the error detail list */
            (*RD)->a.severeReturn->errorDetail = AsnListNew (sizeof(void*));
            /* ACV = AsnListAppend((*RD)->a.severeReturn->errorDetail);*/
}
void EncodeMESG(MessagingEvent* MESG)
{
    (*RD)->a.severeReturn->callEventDetail->choiceId = CALLEVENTDETAIL_MESSAGINGEVENT;
            (*RD)->a.severeReturn->callEventDetail->a.messagingEvent =
                      (MessagingEvent*) Asn1Alloc (sizeof(MessagingEvent));

            ((*RD)->a.severeReturn->callEventDetail->a.messagingEvent) = MESG;

            /* Build the error detail list */
            (*RD)->a.severeReturn->errorDetail = AsnListNew (sizeof(void*));
            /* ACV = AsnListAppend((*RD)->a.severeReturn->errorDetail);*/
}



void EncodeTransferBatchError()
{
        (*RD)->a.fatalReturn->transferBatchError = (TransferBatchError*) Asn1Alloc (sizeof(TransferBatchError));

        /* Build the error detail list */
        (*RD)->a.fatalReturn->transferBatchError->errorDetail = AsnListNew (sizeof(void*));
        /* ACV = AsnListAppend((*RD)->a.fatalReturn->transferBatchError->errorDetail); */
}


/* Function used when fatal error is found in Tap Batch Control Info */
/* Allocate memory and load data into Tap Batch Control Info & Error Detail */
/* Input Parameters : Tap Batch Control Info structure */
/* Return Values : Null */

void EncodeBatchControlInfoError(struct BatchControlInfo* BCI)
{
        (*RD)->a.fatalReturn->batchControlError = (BatchControlError*) Asn1Alloc (sizeof(BatchControlError));

        /* Allocate memory for batchControlInfo in BatchControlError */
        (*RD)->a.fatalReturn->batchControlError->batchControlInfo = (BatchControlInfo*) Asn1Alloc (sizeof(BatchControlInfo));

        (*RD)->a.fatalReturn->batchControlError->batchControlInfo = BCI;

        /* Build the error detail list */
        (*RD)->a.fatalReturn->batchControlError->errorDetail = AsnListNew (sizeof(void*));
      /*  ACV = AsnListAppend((*RD)->a.fatalReturn->batchControlError->errorDetail); */

}

/* Function used when fatal error is found in Tap Accounting Info */
/* Allocate memory and load data into Tap Accounting Info & Error Detail */
/* Input Parameters : Tap Accounting Info structure */
/* Return Values : Null */

void EncodeAccInfoError(struct AccountingInfo* AI)
{
        (*RD)->a.fatalReturn->accountingInfoError = (AccountingInfoError*) Asn1Alloc (sizeof(AccountingInfoError));

        /* Allocate memory for accountingInfo in AccountingInfoError */
        (*RD)->a.fatalReturn->accountingInfoError->accountingInfo = (AccountingInfo*) Asn1Alloc (sizeof(AccountingInfo));

        (*RD)->a.fatalReturn->accountingInfoError->accountingInfo = AI;

        /* Build the error detail list */

        (*RD)->a.fatalReturn->accountingInfoError->errorDetail = AsnListNew (sizeof(void*));
       /*  ACV = AsnListAppend((*RD)->a.fatalReturn->accountingInfoError->errorDetail); */
}

/* Function used when fatal error is found in Tap Network Info */
/* Allocate memory and load data into Tap Network Info & Error Detail */
/* Input Parameters : Tap Network Info structure */
/* Return Values : Null */

void EncodeNetworkInfoError(struct NetworkInfo* NI)
{
        (*RD)->a.fatalReturn->networkInfoError = (NetworkInfoError*) Asn1Alloc (sizeof(NetworkInfoError));
        /* Allocate memory for networkInfo in NetworkInfoError */
        (*RD)->a.fatalReturn->networkInfoError->networkInfo = (NetworkInfo*) Asn1Alloc (sizeof(NetworkInfo));
        (*RD)->a.fatalReturn->networkInfoError->networkInfo = NI;

        /* Build the error detail list */

        (*RD)->a.fatalReturn->networkInfoError->errorDetail = AsnListNew (sizeof(void*));
        /* ACV = AsnListAppend((*RD)->a.fatalReturn->networkInfoError->errorDetail); */
}


/* Function used when fatal error is found in Tap Audit Control Info */
/* Allocate memory and load data into Tap Audit Control Info & Error Detail */
/* Input Parameters : Tap Audit Control Info structure */
/* Return Values : Null */

void EncodeAuditControlInfoError(struct AuditControlInfo* ADIN)
{
        FILE *FP;
    /* printf("set_AuditControlInfoError 4 \n"); */

        (*RD)->a.fatalReturn->auditControlInfoError =
             (AuditControlInfoError*)Asn1Alloc (sizeof(AuditControlInfoError));

   /* Allocate memory for the auditControlInfo in AuditControlInfoError */
   (*RD)->a.fatalReturn->auditControlInfoError->auditControlInfo =
             (AuditControlInfo*)Asn1Alloc (sizeof(AuditControlInfo));
/*
   (*RD)->a.fatalReturn->auditControlInfoError->auditControlInfo = TapAuInfo;
*/

/* encode_AuditControlInfo((*RD)->a.fatalReturn->auditControlInfoError->auditControlInfo); */
  (*RD)->a.fatalReturn->auditControlInfoError->auditControlInfo = ADIN;

   /* Build the error detail list */

   (*RD)->a.fatalReturn->auditControlInfoError->errorDetail = AsnListNew (sizeof(void*));
  /*  ACV = AsnListAppend((*RD)->a.fatalReturn->auditControlInfoError->errorDetail); */

}



void EncodeAuditControlInfo(struct AuditControlInfo *ADIN)
{
/*
                printf("\n First call %s",AuInfo.FCDate);
                printf("\n Last call  %s",AuInfo.LCDate);
                printf("\n Rec count  %d",AuInfo.RecCount);
                printf("\n Tot Charge %d",AuInfo.TotCharge);
                printf("\n type %s",AuInfo.chrgType);
*/
        ADIN->earliestCallTimeStamp = (EarliestCallTimeStamp*) Asn1Alloc(sizeof(EarliestCallTimeStamp));
        ADIN->earliestCallTimeStamp->localTimeStamp.octs =
                         (unsigned char*)Asn1Alloc(sizeof(ACI.EarliestCallTimeStamp.LocalTimeStamp));
        strcpy(ADIN->earliestCallTimeStamp->localTimeStamp.octs,ACI.EarliestCallTimeStamp.LocalTimeStamp);
        ADIN->earliestCallTimeStamp->localTimeStamp.octetLen=strlen(ACI.EarliestCallTimeStamp.LocalTimeStamp);
        ADIN->earliestCallTimeStamp->utcTimeOffset.octs =
                                              (unsigned char*)Asn1Alloc(strlen(ACI.EarliestCallTimeStamp.UtcTimeOffset));
        strcpy(ADIN->earliestCallTimeStamp->utcTimeOffset.octs, ACI.EarliestCallTimeStamp.UtcTimeOffset);
        ADIN->earliestCallTimeStamp->utcTimeOffset.octetLen =
                        strlen(ADIN->earliestCallTimeStamp->utcTimeOffset.octs);

        ADIN->latestCallTimeStamp = (LatestCallTimeStamp*) Asn1Alloc(sizeof(LatestCallTimeStamp));
        ADIN->latestCallTimeStamp->localTimeStamp.octs =
                         (unsigned char*)Asn1Alloc(sizeof(ACI.LatestCallTimeStamp.LocalTimeStamp));
        strcpy(ADIN->latestCallTimeStamp->localTimeStamp.octs,ACI.LatestCallTimeStamp.LocalTimeStamp);
        ADIN->latestCallTimeStamp->localTimeStamp.octetLen=strlen(ACI.LatestCallTimeStamp.LocalTimeStamp);
        ADIN->latestCallTimeStamp->utcTimeOffset.octs =
                                              (unsigned char*)Asn1Alloc(strlen(ACI.LatestCallTimeStamp.UtcTimeOffset));
        strcpy(ADIN->latestCallTimeStamp->utcTimeOffset.octs, ACI.LatestCallTimeStamp.UtcTimeOffset);

        ADIN->latestCallTimeStamp->utcTimeOffset.octetLen =
                        strlen(ADIN->latestCallTimeStamp->utcTimeOffset.octs);

        ADIN->callEventDetailsCount = (CallEventDetailsCount*) Asn1Alloc(sizeof(CallEventDetailsCount));
        *ADIN->callEventDetailsCount = ACI.CallEventDetailsCount;

                ADIN->totalCharge = (TotalCharge *) Asn1Alloc (sizeof (TotalCharge));
                *ADIN->totalCharge = ACI.TotalCharge;

        ADIN->totalTaxValue = (AbsoluteAmount*) Asn1Alloc(sizeof(AbsoluteAmount));
        *ADIN->totalTaxValue = ACI.TotalTaxValue;

        ADIN->totalDiscountValue = (AbsoluteAmount*) Asn1Alloc(sizeof(AbsoluteAmount));
        *ADIN->totalDiscountValue = ACI.TotalDiscountValue;
}


void EncodeNotification(struct Notification* NOT)
{
        (*RD)->a.fatalReturn->notificationError = (NotificationError*) Asn1Alloc (sizeof(NotificationError));
        /* Allocate memory for notification in Notification */
        (*RD)->a.fatalReturn->notificationError->notification = (Notification*) Asn1Alloc (sizeof(Notification));
        (*RD)->a.fatalReturn->notificationError->notification = NOT;

        /* Build the error detail list */
        (*RD)->a.fatalReturn->notificationError->errorDetail = AsnListNew (sizeof(void*));
       /* ACV = AsnListAppend((*RD)->a.fatalReturn->notificationError->errorDetail); */
}

/* Allocate memory and load data into error code and context list */
/* Input Parameters : Error Code and Error context string (delimited by ; and :) */
/* Return Values : Null */

void EncodeErrorDetail(long errCode,char *ContextStr,char* errType, int errorNode)
{
   FILE *FP;
   ErrorContext **ECL;
   int errPath;
   int errLevel;
   int errOccurrence;
   char *contextToken,*tok;
   char delim[]=":;";
   char hop[100];
   int i=0,j=0;

   strcpy(hop,ContextStr);

   /* Build the error detail list */
  /*  (*RD)->a.fatalReturn->auditControlInfoError->errorDetail = AsnListNew (sizeof(void*));
    ACV = AsnListAppend((*RD)->a.fatalReturn->auditControlInfoError->errorDetail);
   */

   /* Initialise error code */
 

   if(strcmp(errType,"SEVERE") == 0)
   {
      
        ACV = AsnListAppend((*RD)->a.severeReturn->errorDetail);
     
   }
   else if(strcmp(errType,"FATAL") == 0)
   {
    
     
       if(errorNode == TRANSFER_BATCH_ERR)
       {
	   
           ACV = AsnListAppend((*RD)->a.fatalReturn->transferBatchError->errorDetail);
       }

       if(errorNode == NOTIFICATION_ERR)
       {
	   
           ACV = AsnListAppend((*RD)->a.fatalReturn->notificationError->errorDetail);
       } 
       else if(errorNode == BATCH_CONTROL_ERR)
       {
           
           ACV = AsnListAppend((*RD)->a.fatalReturn->batchControlError->errorDetail);
       }
       else if(errorNode == ACC_INFO_ERR)
       {
           
           ACV = AsnListAppend((*RD)->a.fatalReturn->accountingInfoError->errorDetail);
       }
       else if(errorNode == NETWORK_INFO_ERR)
       { 
	   
           ACV = AsnListAppend((*RD)->a.fatalReturn->networkInfoError->errorDetail); 
       }
       else if(errorNode == AUDIT_CONTROL_ERR)
       {
	   
           ACV = AsnListAppend((*RD)->a.fatalReturn->auditControlInfoError->errorDetail);
       }
   }
      *ACV = (ErrorDetail*) Asn1Alloc(sizeof(ErrorDetail));
   (*ACV)->errorContext = AsnListNew (sizeof(void*));
   (*ACV)->errorCode = (ErrorCode*) Asn1Alloc(sizeof(ErrorCode));
   (*ACV)->errorCode = errCode;


   /*  printf("hop -%s- \n",hop);  */
   /* Loop to build the errorcontext list */

   tok = strtok( hop , delim);
   while(( tok != NULL))
   {
        /* printf( "<%s>", tok ); */
        if(i == 0)
        {
               errPath = atoi(tok);
               i++;
        }
        else if(i == 1)
        {
               errOccurrence = atoi(tok);
               i++;
        }
        else if(i == 2)
        {
               errLevel = atoi(tok);
               i = 0;
/*             printf("errPath=%d errOccurrence=%d errLevel=%d \n",errPath,errOccurrence,errLevel);
 */     
        
         ECL = AsnListAppend((*ACV)->errorContext);
         *ECL = (ErrorContext*) Asn1Alloc(sizeof(ErrorContext));
         (*ECL)->pathItemId = (PathItemId*) Asn1Alloc(sizeof(PathItemId));
         (*ECL)->pathItemId = errPath;
         if(errOccurrence > 0)
         {
               (*ECL)->itemOccurrence = (ItemOccurrence*) Asn1Alloc(sizeof(ItemOccurrence));
               *(*ECL)->itemOccurrence = errOccurrence;
         }
         (*ECL)->itemLevel = (ItemLevel*) Asn1Alloc(sizeof(ItemLevel));
         (*ECL)->itemLevel = errLevel;
        }
        tok = strtok( NULL, delim);
   }
   
}


/*******************************************************************************************************/
/* Allocate Buffer Memory and Call the Encoding Function */

int EncodeRapout(FILE* fp)
{
   SBuf outputBuf;
   long encodedLen;
   long dataSize = DATA_MAX_SIZE;

   memset(data,'\0',sizeof(data));

   SBufInit (&outputBuf,data, dataSize);
   SBufResetInWriteRvsMode (&outputBuf);

   encodedLen =  BEncRapDataInterChangeContent((BUF_TYPE)&outputBuf, &RDIC);

   if ((encodedLen <= 0) || (SBufWriteError (&outputBuf)))
   {
      return -1;
   }

   SBufResetInReadMode (&outputBuf);
   for( ; encodedLen > 0; encodedLen--)
   {
      fputc (SBufGetByte (&outputBuf), fp);
   }

   FreeRapDataInterChange(&RDIC);

   /* Free all the allocated Nibble Memory */
   ResetNibbleMem();
   return 1;
}

void to_octet ( char* source, unsigned char *octet, int *length )
{
        unsigned char p1,p2,i,pt;
        int len;
        p1=p2=0;
        pt=0;

/*        printf("source :%s\n",source); */
        for ( i=0;source[i];)
        {
                /* printf("source :%c\n",source[i]); */
                p1=p2=15;
                p1 = source[i] - ((source[i] <= '9')?48:55);
                /* printf("p1 :-%u- source :-%c-\n",p1,source[i]); */
                i++;
                if (source[i])
                {
                        p2 = source[i] - ((source[i] <= '9')?48:55);
                        i++;
                }
                p1 <<= 4;
                octet[pt] = p1 | p2;
                if(octet[pt]!=0xf0)
                pt++;
                /* printf("pt :%d\n",pt); */
      }
      *length=pt;
}


