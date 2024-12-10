/* Structure to hold Batch Control related information */

typedef struct gBatchControlInfo
{
        char            Sender[6];
        char            Recipient[6];
        long		FileSequenceNumber;
        gDateTimeLong   FileCreationTimeStamp;
        gDateTimeLong   TransferCutOffTimeStamp;
        gDateTimeLong   FileAvailableTimeStamp;
        int             SpecificationVersionNumber;
        int             ReleaseVersionNumber;
        char            FileTypeIndicator[2];
        long		RapFileSequenceNumber;
}gBatchControlInfo;

typedef struct gBatchControlInfoA
{
        int                     BatchControlInfo;
        int                     Sender;
        int                     Recipient;
        int                     FileSequenceNumber;
        int                     FileCreationTimeStamp;
        gDateTimeLongA		FileCreationTime;
        int                     TransferCutOffTimeStamp;
        gDateTimeLongA		TransferCutOffTime;
        int                     FileAvailableTimeStamp;
        gDateTimeLongA		FileAvailableTime;
        int                     SpecificationVersionNumber;
        int                     ReleaseVersionNumber;
        int                     FileTypeIndicator;
        int                     RapFileSequenceNumber;
}gBatchControlInfoA;
