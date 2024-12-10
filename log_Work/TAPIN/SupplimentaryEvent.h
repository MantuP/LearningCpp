/* Structure to hold SupplimentaryServiceEvent Details */

typedef struct gSupplServiceEvent
{
		char		TransferDirection[2];		/* Inbound or Outbound CDRs   	*/
		char		Plmn[6];
		char		FileSequenceNo[6];
		char		CallDirection[2];		/* Incoming or Outgoing Calls	*/
        /* BasicCallInformation Start    */
           /* ChargeableSubscriber Start */
                char            Imsi[16];                       /* AddressStringDigits          */
                char            Msisdn[16];                     /* AddressStringDigits          */
                char            Min[30];                        /* NumberString                 */
                char            Mdn[30];
           /* ChargeableSubscriber End   */
                int             RapFileSequenceNumber;
        /* LocationInformation Start     */
           /* Network Location Start     */
                int             RecEntityCode;                  /* AsnInt                       */
        	int     	RecEntityType;			/* AsnInt 			*/
        	char    	RecEntityId[25];		/* AsciiString Assumption	*/
                char            CallReference[15];              /* AsnOcts 6Octets              */
                int             LocationArea;                   /* AsnInt                       */
                int             CellId;                         /* AsnInt 00000 to 65535        */
           /* Network Location End       */
           /* Home Location Start        */
                char            HomeBid[15];                    /* AsciiString Length Assumed   */
                char            HomeLocationDescription[25];    /* AsciiString Length Assumed   */
           /* Home Location End          */
           /* Geographical Location Start*/
                char            ServingNetwork[10];             /* AsciiString PLMN Code        */
                char            ServingBid[15];                 /* AsciiString Length Assumed   */
                char            ServingLocationDescription[25]; /* AsciiString Length Assumed   */
           /* Geographical Location End  */
        /* LocationInformation End       */
        /* LocationInformation End       */
        /* EquipmentIdentifier Start     */
                char            IMEI[16];
                char            ESN[20];
        /* EquipmentIdentifier End       */
	/* SupplServiceUsed Start	 */
		char            SupplServiceCode[3];            /* HexString                    */
		int		SupplServiceActionCode;		/* AsnInt                       */
		char		SsParameters[25];		/* AsciiString Length Assumed   */
                gDateTimeLong   ChargingTimeStamp;
                gChargeInfo     ChargeInformationList[HTotalChargeInfo];
                char            BasicServiceType;               /* T-teleservice, B-bearerservice */
                char            BasicServiceCode[3];
        /* SupplServiceUsed End	         */
}gSupplServiceEvent;

/*
Event is duplicate. Chargeable subscriber, Recording Entity Type and Identification, charging timestamp, supplementary service code and action match call record already processed and the call reference is identical in both call records

	1.	ChargeableSubscriber
	2.	RecordingEntityType
	3.	RecordingEntityIdentification
	4.	ChargingTimeStamp
	5.	SupplimentaryServiceCode
	6.	SupplimentaryServiceAction
	7.	CallReferenceNumber
*/
