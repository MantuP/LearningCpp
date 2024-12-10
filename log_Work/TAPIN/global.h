/* Global Definitions of Structures used in TAP File Creation and Processing */
#include "CommonDefinitions.h"
#include "BatchControlInfo.h"
#include "AccountingInfo.h"
#include "NetworkInfo.h"
#include "BasicCallTypes.h"
#include "SupplimentaryEvent.h"
#include "AuditControlInfo.h"
#include "TAPFileSummary.h"
#include "TAPErrorSummary.h"
#include "RAPFileSummary.h"

/*****************************************************************************/
/* Global Structure Declarations */
extern struct MobileOriginatedCall      *stMOC1;
extern struct MobileTerminatedCall      *stMTC1;
extern struct GprsCall                  *stGC;
extern struct SupplServiceEvent         *stSUP1;
extern struct MobileSession             *stMSESS;
extern struct MessagingEvent            *stMESG;



/* RAPErrorInformation Structure Declarations */
stTAPErrorInfo                  REI;
stErrorContext                  stContext;

/* BatchControlInfo Structure Declarations */
gBatchControlInfo		BCI;
gBatchControlInfoA		BCIA;

/* AccountingInfo Structure Declarations */
gAccountingInfo                 ACC;
gAccountingInfoA		ACCA;

/* NetworkInfo Structure Declarations */
gNetworkInfo                    NI;
gNetworkInfoA			NIA;

/* AuditControlInfo Structure Declarations */
gAuditControlInfo               ACI;
gAuditControlInfoA		ACIA;

/* BasicCallTypes Structure Declarations */
/* gBasicCallTypes		BCT; */
gBasicCallTypesA		BCTA;

/* SupplimentaryEvent Structure Declarations */
gSupplServiceEvent		SSE;

/* ChargeInformation Structure Declaration */
/* 
gChargeInfo     		CIN[HTotalChargeInfo];
*/
gCamelService			CSU;

/* SupplimentaryServiceUsed Declaration */
gSupplServiceUsed		SSU;

/* CDR Structure Declarations */
PM_TAP_CDRS			BCT;
PM_TAP_CDRS			CDR[5000];
PM_TAP_CDR_CHARGE_INFO		CIN[30];
PM_TAP_CDR_TAX_INFO		TIN[30];
PM_TAP_CDR_DISCOUNT_INFO	DIN[30];
PM_TAP_CDR_CAMEL_TAX_INFO	CAM[30];

