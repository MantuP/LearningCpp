/*****************************************************************************/
/* Structure to hold Network related information */

typedef struct gNetworkInfo
{
        gUtcTimeOffsetInfoList  UtcTimeOffsetInfo[TOTAL_UTC];
        gRecEntityInfoList      RecEntityInfo[TOTAL_REC];
        int                     TotalUtc;
        int                     TotalRecEntity;
}gNetworkInfo;

typedef struct gNetworkInfoA
{
        int                             NetworkInfo;
        int                             UtcTimeOffsetInfoList;
        gUtcTimeOffsetInfoListA		UtcTimeOffsetInfo[TOTAL_UTC];
        int                             RecEntityInfoList;
        gRecEntityInfoListA		RecEntityInfo[TOTAL_REC];
}gNetworkInfoA;
