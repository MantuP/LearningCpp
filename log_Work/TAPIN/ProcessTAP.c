
/* Result Sets Interface */
#ifndef SQL_CRSR
#  define SQL_CRSR
  struct sql_cursor
  {
    unsigned int curocn;
    void *ptr1;
    void *ptr2;
    unsigned int magic;
  };
  typedef struct sql_cursor sql_cursor;
  typedef struct sql_cursor SQL_CURSOR;
#endif /* SQL_CRSR */

/* Thread Safety */
typedef void * sql_context;
typedef void * SQL_CONTEXT;

/* Object support */
struct sqltvn
{
  unsigned char *tvnvsn; 
  unsigned short tvnvsnl; 
  unsigned char *tvnnm;
  unsigned short tvnnml; 
  unsigned char *tvnsnm;
  unsigned short tvnsnml;
};
typedef struct sqltvn sqltvn;

struct sqladts
{
  unsigned int adtvsn; 
  unsigned short adtmode; 
  unsigned short adtnum;  
  sqltvn adttvn[1];       
};
typedef struct sqladts sqladts;

static struct sqladts sqladt = {
  1,1,0,
};

/* Binding to PL/SQL Records */
struct sqltdss
{
  unsigned int tdsvsn; 
  unsigned short tdsnum; 
  unsigned char *tdsval[1]; 
};
typedef struct sqltdss sqltdss;
static struct sqltdss sqltds =
{
  1,
  0,
};

/* File name & Package Name */
struct sqlcxp
{
  unsigned short fillen;
           char  filnam[14];
};
static struct sqlcxp sqlfpn =
{
    13,
    "ProcessTAP.pc"
};


static unsigned int sqlctx = 649195;


static struct sqlexd {
   unsigned int   sqlvsn;
   unsigned int   arrsiz;
   unsigned int   iters;
   unsigned int   offset;
   unsigned short selerr;
   unsigned short sqlety;
   unsigned int   occurs;
            short *cud;
   unsigned char  *sqlest;
            char  *stmt;
   sqladts *sqladtp;
   sqltdss *sqltdsp;
            void  **sqphsv;
   unsigned int   *sqphsl;
            int   *sqphss;
            void  **sqpind;
            int   *sqpins;
   unsigned int   *sqparm;
   unsigned int   **sqparc;
   unsigned short  *sqpadto;
   unsigned short  *sqptdso;
   unsigned int   sqlcmax;
   unsigned int   sqlcmin;
   unsigned int   sqlcincr;
   unsigned int   sqlctimeout;
   unsigned int   sqlcnowait;
              int   sqfoff;
   unsigned int   sqcmod;
   unsigned int   sqfmod;
            void  *sqhstv[129];
   unsigned int   sqhstl[129];
            int   sqhsts[129];
            void  *sqindv[129];
            int   sqinds[129];
   unsigned int   sqharm[129];
   unsigned int   *sqharc[129];
   unsigned short  sqadto[129];
   unsigned short  sqtdso[129];
} sqlstm = {12,129};

/* SQLLIB Prototypes */
extern sqlcxt (/*_ void **, unsigned int *,
                   struct sqlexd *, struct sqlcxp * _*/);
extern sqlcx2t(/*_ void **, unsigned int *,
                   struct sqlexd *, struct sqlcxp * _*/);
extern sqlbuft(/*_ void **, char * _*/);
extern sqlgs2t(/*_ void **, char * _*/);
extern sqlorat(/*_ void **, unsigned int *, void * _*/);

/* Forms Interface */
static int IAPSUCC = 0;
static int IAPFAIL = 1403;
static int IAPFTL  = 535;
extern void sqliem(/*_ unsigned char *, signed int * _*/);

 static char *sq0031 = 
"select NVL(CALL_SEQUENCE,0) ,NVL(trim(ERROR_TYPE),' ') ,NVL(APPLICATION_TAG,\
0) ,NVL(trim(ERROR_FIELD_NAME),' ') ,NVL(ERROR_CODE,0) ,NVL(trim(ERROR_MESSAGE\
),' ') ,NVL(trim(ERROR_CONTEXT_DETAILS),' ') ,NVL(trim(CONTEXT_NAME),' ') ,NVL\
(ERROR_SEQUENCE,0) ,NVL(ERROR_NODE,0) ,NVL(trim(RAP_STATUS),' ') ,NVL(IOT_CHAR\
GE,0) ,NVL(trim(IOT_DATE),' ') ,NVL(trim(IOT_CALCULATION),' ') ,ROWID  from PM\
_RAP_DETAILS where (((((FILE_TRANSFER_DIRECTION=:b0 and HPLMN_CODE=:b1) and VP\
LMN_CODE=:b2) and FILE_TYPE_INDICATOR=:b3) and RAP_SEQUENCE_NUMBER=:b4) and NV\
L(RAP_STATUS,'Q')='Q') order by CALL_SEQUENCE,ERROR_NODE asc             ";

 static char *sq0046 = 
",0) ,nvl(IOT_DISCOUNT,0) ,nvl(TARIFF_ID,0) ,nvl(CDR_ERROR_FLAG,0) ,nvl(trim(\
CHARGE_CONTEXT),' ') ,nvl(trim(TAX_CONTEXT),' ') ,nvl(trim(DISCOUNT_CONTEXT),'\
 ') ,nvl(ERROR_NODE,0) ,nvl(trim(A_USERID),' ') ,nvl(trim(B_USERID),' ') ,nvl(\
trim(EVENT_REFERENCE),' ') ,nvl(to_char(IOT_DATE,'YYYYMMDD'),' ') ,nvl(trim(IO\
T_CALCULATION),' ') ,trim(ROWID)  from PM_TMP_TAP_CDRS where ((((FILE_TRANSFER\
_DIRECTION='I' and HPLMN_CODE=:b0) and VPLMN_CODE=:b1) and FILE_TYPE_INDICATOR\
=:b2) and FILE_SEQUENCE_NUMBER=:b3) order by CALL_SEQUENCE            ";

 static char *sq0051 = 
"select nvl(trim(HPLMN_CODE),' ') ,nvl(trim(ISO_CURNCY_CODE),' ') ,nvl(trim(T\
APOUT_CURNCY),' ') ,nvl(trim(UTC_OFFSET),' ') ,nvl(TAP_SPECIFICATION_VERSION,0\
) ,nvl(TAP_RELEASE_VERSION,0) ,nvl(RATE_MULT_FACT,0) ,nvl(HOME_CURNCY_ROUNDOFF\
_FACT,0) ,nvl(TAPIN_CDR_VALIDITY_DAYS,0) ,nvl(HOME_CURNCY_TAPIN_MULTFACT,0) ,n\
vl(TAPIN_EXCH_RATE_DECIMAL_PLACES,0) ,nvl(TAPIN_EXCH_RATE_MULT_FACT,0) ,nvl(HO\
ME_CURNCY,' ') ,nvl(IMSI_PREFIX_POSTPAID,' ') ,nvl(IMSI_PREFIX_PREPAID,' ') ,n\
vl(IMSI_PREFIX_POSTPAID_LEN,0) ,nvl(IMSI_PREFIX_PREPAID_LEN,0) ,nvl(RAP_SPECIF\
ICATION_VERSION,0) ,nvl(RAP_RELEASE_VERSION,0)  from PM_ROAMING_PREFERENCES   \
         ";

 static char *sq0055 = 
"select nvl(EXCHANGE_RATE_CODE,0) ,to_char(VALID_FROM,'YYYYMMDDHH24MISS') ,to\
_char(VALID_TILL,'YYYYMMDDHH24MISS') ,nvl(EXCHANGE_RATE,0)  from PM_CURRENCY_E\
XCHANGE_RATE where (trim(FROM_CURRENCY_CODE)=trim(:b0) and trim(TO_CURRENCY_CO\
DE)=trim(:b1)) order by VALID_FROM desc             ";

 static char *sq0058 = 
"select A.PARTNER_CODE ,NVL(DECODE(trim(B.CHECK_ALIAS_TADIG),'Y',trim(C.ALIAS\
_TADIG_CODE),trim(A.PARTNER_SHORT_CODE)),' ') ,nvl(trim(C.TAPIN_SURCHARGE_FLAG\
),' ') ,nvl(C.TAPIN_SURCHARGE_RATE,0) ,nvl(trim(C.TAPIN_TAX_FLAG),' ') ,nvl(tr\
im(C.TAPIN_DISCOUNT_FLAG),' ') ,nvl(C.TAPIN_DISCOUNT_RATE,0) ,nvl(C.TAPIN_TAX_\
RATE,0) ,nvl(B.CHECK_CALL_AGE_FLG,' ') ,nvl(B.CALL_AGE,0) ,nvl(B.CHECK_FILE_AG\
E_FLG,' ') ,nvl(B.FILE_AGE,0) ,nvl(C.IOT_CHECK,'N') ,nvl(B.FREQUENCY_IN_MINUTE\
,0) ,nvl(C.MOBL_PRFX_V,' ')  from PM_PARTNER A ,PM_ROAM_PARTNER_FILE_INFO B ,P\
M_ROAM_PARTNER_ADDN_INFO C where (((A.PARTNER_CODE=B.PARTNER_CODE and A.PARTNE\
R_CODE=C.PARTNER_CODE) and B.GENERATE_FILES_FLG='Y') and B.PROCESS_ID=:b0) ord\
er by A.PARTNER_CODE            ";

 static char *sq0061 = 
"select A.PARTNER_CODE ,NVL(DECODE(trim(B.CHECK_ALIAS_TADIG),'Y',trim(C.ALIAS\
_TADIG_CODE),trim(A.PARTNER_SHORT_CODE)),' ') ,nvl(trim(B.DATA_TYPE),' ') ,nvl\
(B.FILE_SEQUENCE_NUMBER,0) ,nvl(trim(B.GENERATE_FILES_FLG),' ') ,nvl(trim(B.US\
E_GLOBAL_PARAMS_FLG),' ') ,nvl(trim(B.FILES_DIRECTORY),' ') ,nvl(trim(B.SUCCES\
S_DIRECTORY),' ') ,nvl(trim(B.CHECK_CALL_AGE_FLG),' ') ,nvl(B.CALL_AGE,0)  fro\
m PM_PARTNER A ,PM_ROAM_PARTNER_FILE_INFO B ,PM_ROAM_PARTNER_ADDN_INFO C where\
 ((A.PARTNER_CODE=B.PARTNER_CODE and A.PARTNER_CODE=C.PARTNER_CODE) and B.PROC\
ESS_ID=:b0) order by A.PARTNER_CODE            ";

 static char *sq0064 = 
"select nvl(APPLICATION_TAG,0) ,nvl(trim(FIELD_NAME),' ') ,nvl(trim(ERROR_CON\
TEXT_NAME),' ') ,nvl(trim(ERROR_TYPE),' ') ,nvl(ERROR_CODE,0) ,nvl(trim(ERROR_\
MESSAGE),' ') ,nvl(trim(VALIDATE_TAG),' ')  from PM_TAG_ERROR_CODES where VALI\
DATE_TAG='N'           ";

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* CUD (Compilation Unit Data) Array */
static short sqlcud0[] =
{12,4130,1,0,0,
5,0,0,0,0,0,27,574,0,0,4,4,0,1,0,1,97,0,0,1,10,0,0,1,10,0,0,1,10,0,0,
36,0,0,2,44,0,1,608,0,0,0,0,0,1,0,
51,0,0,3,68,0,4,616,0,0,1,0,0,1,0,2,97,0,0,
70,0,0,4,44,0,1,629,0,0,0,0,0,1,0,
85,0,0,5,391,0,4,641,0,0,10,1,0,1,0,2,3,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,1,3,0,0,
140,0,0,6,63,0,4,770,0,0,1,0,0,1,0,2,97,0,0,
159,0,0,7,0,0,29,901,0,0,0,0,0,1,0,
174,0,0,8,0,0,31,1183,0,0,0,0,0,1,0,
189,0,0,9,0,0,31,1202,0,0,0,0,0,1,0,
204,0,0,10,0,0,31,1225,0,0,0,0,0,1,0,
219,0,0,11,0,0,31,1248,0,0,0,0,0,1,0,
234,0,0,12,0,0,31,1271,0,0,0,0,0,1,0,
249,0,0,13,0,0,31,1298,0,0,0,0,0,1,0,
264,0,0,14,0,0,31,1320,0,0,0,0,0,1,0,
279,0,0,15,0,0,31,1348,0,0,0,0,0,1,0,
294,0,0,16,0,0,31,1366,0,0,0,0,0,1,0,
309,0,0,17,0,0,31,1386,0,0,0,0,0,1,0,
324,0,0,18,0,0,31,1412,0,0,0,0,0,1,0,
339,0,0,19,0,0,31,1437,0,0,0,0,0,1,0,
354,0,0,20,0,0,31,1462,0,0,0,0,0,1,0,
369,0,0,21,29,0,2,1463,0,0,0,0,0,1,0,
384,0,0,22,0,0,29,1464,0,0,0,0,0,1,0,
399,0,0,23,0,0,31,1494,0,0,0,0,0,1,0,
414,0,0,24,0,0,31,1529,0,0,0,0,0,1,0,
429,0,0,25,0,0,31,1547,0,0,0,0,0,1,0,
444,0,0,26,0,0,31,1583,0,0,0,0,0,1,0,
459,0,0,27,0,0,31,1611,0,0,0,0,0,1,0,
474,0,0,28,0,0,29,1637,0,0,0,0,0,1,0,
489,0,0,29,0,0,29,1686,0,0,0,0,0,1,0,
504,0,0,30,212,0,4,1743,0,0,6,5,0,1,0,2,3,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,
0,0,1,3,0,0,
543,0,0,31,617,0,9,1788,0,0,5,5,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,
0,0,
578,0,0,31,0,0,13,1796,0,0,15,0,0,1,0,2,3,0,0,2,97,0,0,2,3,0,0,2,97,0,0,2,3,0,
0,2,97,0,0,2,97,0,0,2,97,0,0,2,3,0,0,2,3,0,0,2,97,0,0,2,3,0,0,2,97,0,0,2,97,0,
0,2,97,0,0,
653,0,0,32,57,0,5,1921,0,0,1,1,0,1,0,1,97,0,0,
672,0,0,33,0,0,31,1931,0,0,0,0,0,1,0,
687,0,0,31,0,0,15,1939,0,0,0,0,0,1,0,
702,0,0,34,0,0,31,2191,0,0,0,0,0,1,0,
717,0,0,35,0,0,31,2314,0,0,0,0,0,1,0,
732,0,0,36,96,0,6,2332,0,0,4,4,0,1,0,1,3,0,0,2,3,0,0,2,97,0,0,2,97,0,0,
763,0,0,37,0,0,31,2359,0,0,0,0,0,1,0,
778,0,0,38,29,0,2,2360,0,0,0,0,0,1,0,
793,0,0,39,0,0,29,2361,0,0,0,0,0,1,0,
808,0,0,40,0,0,31,2376,0,0,0,0,0,1,0,
823,0,0,41,0,0,31,2393,0,0,0,0,0,1,0,
838,0,0,42,363,0,4,3627,0,0,7,3,0,1,0,2,3,0,0,2,97,0,0,2,97,0,0,2,97,0,0,1,97,
0,0,1,97,0,0,1,3,0,0,
881,0,0,43,0,0,31,3675,0,0,0,0,0,1,0,
896,0,0,44,0,0,31,3899,0,0,0,0,0,1,0,
911,0,0,45,47,0,4,4014,0,0,1,0,0,1,0,2,3,0,0,
930,0,0,46,1560,0,9,4092,0,0,4,4,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,
961,0,0,46,0,0,13,4118,0,0,53,0,0,1,0,2,97,0,0,2,97,0,0,2,97,0,0,2,97,0,0,2,97,
0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,97,0,0,2,4,0,0,2,97,0,0,2,97,0,0,2,97,0,0,2,97,0,
0,2,4,0,0,2,97,0,0,2,97,0,0,2,97,0,0,2,4,0,0,2,4,0,0,2,4,0,0,2,3,0,0,2,3,0,0,2,
4,0,0,2,4,0,0,2,3,0,0,2,3,0,0,2,4,0,0,2,4,0,0,2,4,0,0,2,3,0,0,2,4,0,0,2,4,0,0,
2,4,0,0,2,4,0,0,2,4,0,0,2,4,0,0,2,3,0,0,2,4,0,0,2,4,0,0,2,4,0,0,2,3,0,0,2,3,0,
0,2,97,0,0,2,97,0,0,2,97,0,0,2,3,0,0,2,97,0,0,2,97,0,0,2,97,0,0,2,97,0,0,2,97,
0,0,2,97,0,0,
1188,0,0,47,0,0,31,4146,0,0,0,0,0,1,0,
1203,0,0,48,45,0,2,4321,0,0,1,1,0,1,0,1,97,0,0,
1222,0,0,49,0,0,31,4329,0,0,0,0,0,1,0,
1237,0,0,46,0,0,15,4351,0,0,0,0,0,1,0,
1252,0,0,50,54,0,4,4438,0,0,1,0,0,1,0,2,3,0,0,
1271,0,0,51,631,0,9,4512,0,0,0,0,0,1,0,
1286,0,0,51,0,0,13,4513,0,0,19,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,
2,3,0,0,2,4,0,0,2,4,0,0,2,3,0,0,2,4,0,0,2,4,0,0,2,4,0,0,2,5,0,0,2,5,0,0,2,5,0,
0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,
1377,0,0,51,0,0,15,4514,0,0,0,0,0,1,0,
1392,0,0,52,180,0,4,4750,0,0,3,2,0,1,0,2,3,0,0,1,5,0,0,1,5,0,0,
1419,0,0,53,44,0,1,4795,0,0,0,0,0,1,0,
1434,0,0,54,54,0,1,4796,0,0,0,0,0,1,0,
1449,0,0,55,284,0,9,4809,0,0,2,2,0,1,0,1,5,0,0,1,5,0,0,
1472,0,0,55,0,0,13,4810,0,0,4,0,0,1,0,2,3,0,0,2,5,0,0,2,5,0,0,2,4,0,0,
1503,0,0,55,0,0,15,4811,0,0,0,0,0,1,0,
1518,0,0,56,91,0,4,4851,0,0,2,0,0,1,0,2,5,0,0,2,3,0,0,
1541,0,0,57,227,0,4,4896,0,0,2,1,0,1,0,2,3,0,0,1,3,0,0,
1564,0,0,58,732,0,9,4969,0,0,1,1,0,1,0,1,3,0,0,
1583,0,0,58,0,0,13,4970,0,0,15,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,4,0,0,2,5,0,0,
2,5,0,0,2,4,0,0,2,4,0,0,2,5,0,0,2,3,0,0,2,5,0,0,2,3,0,0,2,5,0,0,2,3,0,0,2,97,0,
0,
1658,0,0,58,0,0,15,4971,0,0,0,0,0,1,0,
1673,0,0,59,767,0,4,5003,0,0,18,2,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,
0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,
0,0,2,5,0,0,1,3,0,0,1,3,0,0,
1760,0,0,60,196,0,4,5297,0,0,2,1,0,1,0,2,3,0,0,1,3,0,0,
1783,0,0,61,591,0,9,5370,0,0,1,1,0,1,0,1,3,0,0,
1802,0,0,61,0,0,13,5371,0,0,10,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,2,5,0,0,
2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,
1857,0,0,61,0,0,15,5372,0,0,0,0,0,1,0,
1872,0,0,62,767,0,4,5406,0,0,18,2,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,
0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,
0,0,2,5,0,0,1,3,0,0,1,3,0,0,
1959,0,0,63,72,0,4,5617,0,0,1,0,0,1,0,2,3,0,0,
1978,0,0,64,255,0,9,5670,0,0,0,0,0,1,0,
1993,0,0,64,0,0,13,5671,0,0,7,0,0,1,0,2,3,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,
2,5,0,0,2,5,0,0,
2036,0,0,64,0,0,15,5672,0,0,0,0,0,1,0,
2051,0,0,65,0,0,29,5713,0,0,0,0,0,1,0,
2066,0,0,66,2442,0,3,6126,0,0,103,103,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,
0,1,97,0,0,1,3,0,0,1,4,0,0,1,97,0,0,1,3,0,0,1,97,0,0,1,4,0,0,1,97,0,0,1,3,0,0,
1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,3,0,0,
1,97,0,0,1,3,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,4,0,0,1,4,0,0,1,97,0,0,1,97,0,0,1,
97,0,0,1,97,0,0,1,3,0,0,1,4,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,
3,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,4,0,
0,1,4,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,97,0,0,1,3,
0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,97,0,0,
1,4,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,4,0,0,1,3,0,0,1,3,0,0,1,4,0,
0,1,3,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,
0,0,1,4,0,0,1,3,0,0,1,4,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,
0,1,3,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,3,0,0,
2493,0,0,67,2912,0,3,6384,0,0,121,121,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,
0,1,97,0,0,1,3,0,0,1,4,0,0,1,97,0,0,1,3,0,0,1,97,0,0,1,4,0,0,1,97,0,0,1,3,0,0,
1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,
1,97,0,0,1,3,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,4,0,0,1,4,0,0,1,97,0,0,1,97,0,0,1,
97,0,0,1,97,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,
3,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,4,0,
0,1,4,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,97,0,0,1,3,
0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,97,0,0,
1,4,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,4,0,0,1,3,0,0,1,3,0,0,1,4,0,
0,1,3,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,
0,0,1,4,0,0,1,3,0,0,1,4,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,
0,1,3,0,0,1,97,0,0,1,4,0,0,1,97,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,97,0,0,1,3,0,0,1,
97,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,
3,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,3,0,0,
2992,0,0,68,1056,0,3,6658,0,0,48,48,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,
1,97,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,97,0,0,1,4,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,
97,0,0,1,4,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,3,
0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,3,0,0,1,
4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,97,0,
0,1,3,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,
3199,0,0,69,2959,0,3,6785,0,0,129,129,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,
0,1,97,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,97,0,0,1,3,0,0,1,97,0,0,1,4,0,0,1,
97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,97,0,0,1,4,0,0,1,
97,0,0,1,3,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,4,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,
97,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,
97,0,0,1,97,0,0,1,3,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,4,0,0,1,3,0,
0,1,4,0,0,1,4,0,0,1,3,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,97,0,0,1,3,0,0,1,3,0,0,1,3,
0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,3,0,0,1,4,0,0,
1,4,0,0,1,3,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,4,0,0,1,3,0,0,1,97,0,0,1,97,
0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,97,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,3,0,
0,1,97,0,0,1,3,0,0,1,97,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,
0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,4,0,0,
1,3,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,
1,3,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,3,0,0,1,97,0,0,1,97,0,0,
1,3,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,4,0,0,
3730,0,0,70,2682,0,3,7077,0,0,112,112,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,
0,1,97,0,0,1,3,0,0,1,4,0,0,1,97,0,0,1,3,0,0,1,97,0,0,1,4,0,0,1,97,0,0,1,3,0,0,
1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,
1,97,0,0,1,3,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,4,0,0,1,4,0,0,1,97,0,0,1,97,0,0,1,
97,0,0,1,97,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,
3,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,4,0,
0,1,4,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,97,0,0,1,3,
0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,97,0,0,
1,4,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,4,0,0,1,3,0,0,1,3,0,0,1,4,0,
0,1,3,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,
0,0,1,4,0,0,1,3,0,0,1,4,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,
0,1,3,0,0,1,97,0,0,1,4,0,0,1,97,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,97,0,0,1,3,0,0,1,
97,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,97,0,0,
4193,0,0,71,0,0,31,7312,0,0,0,0,0,1,0,
4208,0,0,72,2618,0,3,7430,0,0,114,114,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,
0,1,97,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,97,0,0,1,3,0,0,1,97,0,0,1,4,0,0,1,
97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,97,0,0,1,4,0,0,1,
97,0,0,1,3,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,4,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,
97,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,
97,0,0,1,97,0,0,1,3,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,4,0,0,1,3,0,
0,1,4,0,0,1,4,0,0,1,3,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,97,0,0,1,3,0,0,1,3,0,0,1,3,
0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,3,0,0,1,4,0,0,
1,4,0,0,1,3,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,4,0,0,1,3,0,0,1,97,0,0,1,97,
0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,97,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,3,0,
0,1,97,0,0,1,3,0,0,1,97,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,
0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,97,0,0,1,97,0,
0,1,3,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,97,0,0,
4679,0,0,73,943,0,3,7781,0,0,43,43,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,
97,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,97,0,0,1,4,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,
97,0,0,1,4,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,3,
0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,3,0,0,1,
4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,97,0,
0,1,3,0,0,
4866,0,0,74,73,0,4,32,1,0,1,0,0,1,0,2,97,0,0,
4885,0,0,75,2102,0,3,122,1,0,72,72,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,
3,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,
1,97,0,0,1,3,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,4,0,0,1,3,0,0,1,3,0,0,1,
97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,3,0,0,1,
3,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,
1,4,0,0,1,4,0,0,1,4,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,3,0,
0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,3,
0,0,1,97,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,97,0,0,1,3,0,0,1,3,0,0,
1,3,0,0,1,97,0,0,
5188,0,0,76,1480,0,3,385,1,0,53,53,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,
3,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,
3,0,0,1,97,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,3,0,
0,1,4,0,0,1,3,0,0,1,3,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,3,0,0,1,4,0,0,1,4,0,0,1,
4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,97,0,0,1,3,0,0,
1,4,0,0,1,4,0,0,1,4,0,0,1,97,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,0,1,4,0,
0,1,97,0,0,
5415,0,0,77,153,0,5,574,1,0,3,3,0,1,0,1,97,0,0,1,3,0,0,1,97,0,0,
5442,0,0,78,0,0,31,586,1,0,0,0,0,1,0,
5457,0,0,79,0,0,30,640,1,0,0,0,0,1,0,
5472,0,0,80,124,0,3,711,1,0,3,3,0,1,0,1,97,0,0,1,3,0,0,1,97,0,0,
5499,0,0,81,0,0,29,722,1,0,0,0,0,1,0,
5514,0,0,82,124,0,3,727,1,0,3,3,0,1,0,1,97,0,0,1,3,0,0,1,97,0,0,
5541,0,0,83,0,0,29,737,1,0,0,0,0,1,0,
5556,0,0,84,221,0,3,870,1,0,8,8,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,
0,0,1,97,0,0,1,97,0,0,1,97,0,0,
5603,0,0,85,265,0,4,912,1,0,6,3,0,1,0,2,3,0,0,2,97,0,0,2,3,0,0,1,97,0,0,1,97,0,
0,1,97,0,0,
5642,0,0,86,114,0,4,977,1,0,4,3,0,1,0,1,97,0,0,1,3,0,0,1,3,0,0,2,97,0,0,
5673,0,0,87,213,0,5,1013,1,0,4,4,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,
5704,0,0,88,90,0,5,1038,1,0,1,1,0,1,0,1,97,0,0,
5723,0,0,89,598,0,4,1091,1,0,15,4,0,1,0,2,4,0,0,2,4,0,0,2,4,0,0,2,4,0,0,2,4,0,
0,2,4,0,0,2,4,0,0,2,4,0,0,2,4,0,0,2,4,0,0,2,5,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,
3,0,0,
5798,0,0,90,657,0,4,1151,1,0,14,4,0,1,0,2,4,0,0,2,4,0,0,2,4,0,0,2,4,0,0,2,4,0,
0,2,4,0,0,2,4,0,0,2,4,0,0,2,4,0,0,2,4,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,
5869,0,0,91,100,0,4,1370,1,0,3,2,0,1,0,1,97,0,0,1,3,0,0,2,97,0,0,
5896,0,0,92,86,0,4,1385,1,0,2,1,0,1,0,1,3,0,0,2,97,0,0,
5919,0,0,93,114,0,4,1402,1,0,2,1,0,1,0,2,3,0,0,1,97,0,0,
5942,0,0,94,118,0,4,1429,1,0,2,1,0,1,0,2,3,0,0,1,97,0,0,
5965,0,0,95,109,0,4,1456,1,0,3,2,0,1,0,1,97,0,0,1,97,0,0,2,3,0,0,
5992,0,0,96,381,0,4,1563,1,0,5,4,0,1,0,2,3,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,
0,0,
6027,0,0,97,415,0,4,1587,1,0,5,4,0,1,0,2,4,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,
0,0,
};


/* Modified By Chetan on 15-MAY-2009 to store TAP Tax and Exchange rate details in a Database */
/* Modified By Chetan on 06-MAR-2009 to comment exchange rate count(25), now it will pick all the rows in the Exchange rate Table */ 
/* Modified By Chetan on 30-JUL-2009 to remove success file when HPLMN code is wrong */ 
/* Modified by Anitha on 12-JUN-2013 For LTE Calls */
/* Modified by Sangram to pick the ALIAS_TADIG_CODE if the CHECHK_ALIAS_TADIG flag is set to Y for a partner */
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
#include<signal.h>
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
#include "Logger.h"
#include <oraca.h>

/* Total Files to Read from the files directory */
#define TotalFilesToRead	100
#define FileNameSize		15
#define MAX_MISSING_FILES       150

#define ERRCODE           sqlca.sqlcode
#define NODATAFOUND       1403
#define MAX_NUM_FILES           500 /* 8024 */
#define MAX_FILE_SIZE           256
#define INIT_STR(vc_x) (memset(vc_x,'\0',sizeof(vc_x)));
#define BULK_INSERT 0
#define SINGLE_INSERT 1
#define MAX_EXCHANGE_RATES 24
#define MAX_TAXATION       30
#define MAX_DISCOUNTING    30
#define MAX_UTC_OFFSET     30
#define MAX_REC_ENTITY     30



/* Global Structure Declarations */

typedef struct stRoamingPreferences
{
        char   HPLMN_CODE[6];
        char   ISO_CURNCY_CODE[4];
        char   TAPOUT_CURNCY[6];
        char   UTC_OFFSET[7];
        int    TAP_SPECIFICATION_VERSION;
        int    TAP_RELEASE_VERSION;
        double RATE_MULT_FACT;
        double HOME_CURNCY_ROUNDOFF_FACT;
        int    TAPIN_CDR_VALIDITY_DAYS;
        double HOME_CURNCY_TAPIN_MULTFACT;
        double TAPIN_EXCH_RATE_DECIMAL_PLACES;
        double TAPIN_EXCH_RATE_MULT_FACT;
        char   HOME_CURNCY[21];
        char   IMSI_PREFIX_POSTPAID[101];
        char   IMSI_PREFIX_PREPAID[101];
        long   IMSI_PREFIX_POSTPAID_LEN;
        long   IMSI_PREFIX_PREPAID_LEN;
        int    RAP_SPECIFICATION_VERSION;
        int    RAP_RELEASE_VERSION;
}stRoamingPreferences;

typedef struct PM_APP_PREFERENCE
{
	char   IMSI_PRFX[101];
	long   IMSI_PRFX_LEN;
    }PM_APP_PREFERENCE;

typedef struct stExchangeRates
{
        long   EXCHANGE_RATE_CODE;
        char   VALID_FROM[15];
        char   VALID_TILL[15];
        double EXCHANGE_RATE;
}stExchangeRates;

typedef struct PM_PARTNERS
{
	char   PARTNER_CODE[4];
	char   PARTNER_SHORT_CODE[7];
        char   TAPIN_SURCHARGE_FLAG[2];
        double TAPIN_SURCHARGE_RATE;
        char   TAPIN_TAX_FLAG[2];
        char   TAPIN_DISCOUNT_FLAG[2];
        double TAPIN_DISCOUNT_RATE;
        double TAPIN_TAX_RATE;
        char   CHECK_CALL_AGE_FLG[2];
        int    CALL_AGE;
        char   CHECK_FILE_AGE_FLG[2];
        int    FILE_AGE;
        char   IOT_CHECK[2];
        int    FREQUENCY_IN_MINUTE;
        char   MOBL_PRFX_V[7];
	
}PM_PARTNERS;

typedef struct PM_ADD_INFO
{
        int    TAPIN_SURCHARGE_FLAG;
        double TAPIN_SURCHARGE_RATE;
        int    TAPIN_TAX_FLAG;
        int    TAPIN_DISCOUNT_FLAG;
        double TAPIN_DISCOUNT_RATE;
        double TAPIN_TAX_RATE;
}PM_ADD_INFO;

typedef struct PM_TAP_ERRORS
{
	char  PROCESS_DATE[15];
        char  FILE_NAME[31];
        long  ERROR_CODE;
        char  ERROR_DESC[151];
}PM_TAP_ERRORS;

typedef struct PM_MISSING_TAP_FILES
{
        char FILE_TRANSFER_DIRECTION[2];
        char HPLMN_CODE[6];
        char VPLMN_CODE[6];
        char FILE_TYPE_INDICATOR[2];
        long FILE_SEQUENCE_NUMBER;
        char FILE_STATUS[2];
        char FILE_AVAILABLE_TIME[15];
        char FILE_EXPECTED_TIME[15];
}PM_MISSING_TAP_FILES;

typedef struct SETTLEMENT_DTLS 
{
	long   SETTLEMENT_CALL_EVENTS;
        double SETTLEMENT_DURATION;
        double SETTLEMENT_OUTGOING_VOLUME;
        double SETTLEMENT_INCOMING_VOLUME;
	double SETTLEMENT_TAP_CURNCY_CHARGE;
        double SETTLEMENT_TAP_CURNCY_TAX;
	double SETTLEMENT_TAP_CURNCY_DISCOUNT;
     	double SETTLEMENT_LOCAL_CHARGE;
     	double SETTLEMENT_LOCAL_TAX;
     	double SETTLEMENT_LOCAL_DISCOUNT;
}SETTLEMENT_DTLS;

typedef struct IMSI_PREFIX
{
	long IMSI_PREFIX[30];
}IMSI_PREFIX;


typedef struct PM_PROCESS_DETAILS
{
        char CHARGE_FILE_TYPE_INDICATOR[2];
        char CHARGE_HOME_DIR_FLG[2];
        char CHARGE_HOME_DIR[101];
        char CHARGE_FILES_DIR[101];
        char CHARGE_PROCESS_FILES_DIR[101];
        char CHARGE_ERROR_FILES_DIR[101];
        char CHARGE_TOUCHFILES_FLG[2];
        char CHARGE_SUCCESS_FILES_DIR[101];
        char TEST_FILE_TYPE_INDICATOR[2];
        char TEST_HOME_DIR_FLG[2];
        char TEST_HOME_DIR[101];
        char TEST_FILES_DIR[101];
        char TEST_PROCESS_FILES_DIR[101];
        char TEST_ERROR_FILES_DIR[101];
        char TEST_TOUCHFILES_FLG[2];
        char TEST_SUCCESS_FILES_DIR[101];
}PM_PROCESS_DETAILS;

typedef struct stTapoutProcess
{
        int  PROCESS_ID;
        char FILE_TYPE_INDICATOR[2];
        char PROCESS_INPUT_START_DATE[15];
        char PROCESS_INPUT_END_DATE[15];
        char LOCK_FILE_PATH[126];
        char STOP_SIGNAL_DIR[100];
        char STOP_SIGNAL_FILE[26];
        char STOP_SIGNAL_PATH[126];
        char REQUEST_TYPE[2];
}stTapoutProcess;


typedef struct PM_RAP_PROCESS_DETAILS
{
        char CHARGE_FILE_TYPE_INDICATOR[2];
        char CHARGE_HOME_DIR_FLG[2];
        char CHARGE_HOME_DIR[101];
        char CHARGE_FILES_DIR[101];
        char CHARGE_PROCESS_FILES_DIR[101];
        char CHARGE_ERROR_FILES_DIR[101];
        char CHARGE_TOUCHFILES_FLG[2];
        char CHARGE_SUCCESS_FILES_DIR[101];
        char TEST_FILE_TYPE_INDICATOR[2];
        char TEST_HOME_DIR_FLG[2];
        char TEST_HOME_DIR[101];
        char TEST_FILES_DIR[101];
        char TEST_PROCESS_FILES_DIR[101];
        char TEST_ERROR_FILES_DIR[101];
        char TEST_TOUCHFILES_FLG[2];
        char TEST_SUCCESS_FILES_DIR[101];
}PM_RAP_PROCESS_DETAILS;


typedef struct PM_RAP_PARTNERS
{
        char   PARTNER_CODE[4];
        char   PARTNER_SHORT_CODE[7];
        char   DATA_TYPE[2];
        int    FILE_SEQUENCE_NUMBER;
        char   GENERATE_FILES_FLG[2];
        char   USE_GLOBAL_PARAMS_FLG[2];
        char   FILES_DIRECTORY[101];
        char   SUCCESS_DIRECTORY[101];
        char   CHECK_CALL_AGE_FLG[2];
        int    CALL_AGE;
}PM_RAP_PARTNERS;


typedef struct PM_TAG_ERROR_CODES
{
       int    APPLICATION_TAG;
       char   FIELD_NAME[51];
       char   ERROR_CONTEXT_NAME[51];
       char   ERROR_TYPE[9];
       int    ERROR_CODE;
       char   ERROR_MESSAGE[501];
       char   VALIDATE_TAG[2];
}PM_TAG_ERROR_CODES;

/*typedef struct PM_RAP_DETAILS
{
      long   CALL_SEQUENCE;
      char   ERROR_TYPE[9];
      int    APPLICATION_TAG;
      char   ERROR_FIELD_NAME[51];
      int    ERROR_CODE;
      char   ERROR_MESSAGE[501];
      char   ERROR_CONTEXT_DETAILS[101];
      char   CONTEXT_NAME[51];
      long   ERROR_SEQUENCE;
      int    ERROR_NODE;
      char   RAP_STATUS[2]; 
      char   ROWID[20];
}PM_RAP_DETAILS; */

DataInterChange DIC;
stRoamingPreferences            stRoamingPref,*ptRoamingPref1,*ptRoamingPref2;
PM_APP_PREFERENCE               stAppPref;
stExchangeRates                 *ptExchRates1,*ptExchRates2;
PM_PARTNERS			*ptPartners1,*ptPartners2;
PM_ADD_INFO                     stPartnerInfo;
TAPFileSummary                  FileSummary;
PM_TAP_ERRORS			stErrors;
PM_MISSING_TAP_FILES		stMissingFiles[MAX_MISSING_FILES];
SETTLEMENT_DTLS			stHomeChargeSumry;
IMSI_PREFIX			stImsiPrefix;
PM_PROCESS_DETAILS		stProcessDtls;
stTapoutProcess                 stProcess;
PM_RAP_PROCESS_DETAILS		stRAPProcessDtls;
PM_RAP_PARTNERS			*ptRAPPartners1,*ptRAPPartners2;
RAPFileSummaryDetails           RAPFileSummary;
PM_TAG_ERROR_CODES              *ptTagDetails1,*ptTagDetails2;
PM_TMP_TAP_CDRS                 StIOTCdr ; 
stTAPIOTError                   StIOTErrorCDR ;
PM_RAP_DETAILS                  stRAPDetails  ;
struct MobileOriginatedCall* stMOC1;
struct MobileTerminatedCall* stMTC1;
struct GprsCall* stGC;
struct SupplServiceEvent* stSUP1;
struct MobileSession* stMSESS;
struct MessagingEvent* stMESG;

int   gExchangeRateCount = 0;
int   gTaxationCount =0;
int   gDiscountingCount =0;
int   gUTCOffsetCount =0;
int   gRecEntityInfoCount =0;
char  gMobilePrfx[7];
char  gLocalCurrencyCode[4];
char  gTapoutCurrencyCode[4];
int ValidFlag =0;
int l=0,n=0;
int count =0;
int gTapinTaxFlag =0;
/* Pointer to Hold the Decoded Data */
/* char   *origData; */
int    gProcessId=0;
int    gRAPProcessId=0;
char   gHomeOperatorCode[6];
int    gExchCount=0;
char   gDataTypeIndicator[3];
char   gSystemDate[15];
double gTotalCallDuration=0;
long   gPartnerCount=0;
long   gRAPPartnerCount=0;
long   gTagErrorCodeCount=0;

int    g_fileCount = 0;
char*  g_fileNamesPtr[MAX_NUM_FILES];
char   gChargeFilesDir[250];
char   gChargeProcessFilesDir[250];
char   gChargeErrorFilesDir[250];
char   gChargeSuccessDir[250];
char   gTestFilesDir[250];
char   gTestProcessFilesDir[250];
char   gTestErrorFilesDir[250];
char   gTestSuccessDir[250];
char   gFilesDir[500];
char   gProcessedDir[500];
char   gErrorDir[500];
char   gSuccessDir[500];
char   gReadChargeFilePath[250];
char   gReadTestFilePath[250];
int    gHplmnCodeCount;
long   gUnixPid ;
char   gProcessStartDate[15] ;
char   gErrorMessage[200] ;
char   gLockFilePathName[200];
char   gConnectString[50] ;
char   gSignalProcessId=0;

char   gFileVplmnCode[6] ;
char   gFileHplmnCode[6] ;
char   gFileSequenceNumber[6] ;
extern long gBulkErrorDetailsIndex;
extern int gTaxListFlag;
long   gFatalErrorCount = 0;
long   gSevereErrorCount = 0;
char   gGenerateFilesFlg[2];
int    gRapFileSequenceNumber;
char   gTapFileName[18];
long   gTotalCdrsCount = 0;
int    gRejectedErrorNo = 0;
long   gProcessingCDRNo = 0;
long   gErrorCDRsCount = 0;
double gErrorCDRsCharge = 0;
double gErrorCDRsTax = 0;
double gErrorCDRsDiscount = 0;
double gErrorCDRsDuration = 0;
double gErrorCDRsIncVolume = 0;
double gErrorCDRsOutVolume = 0;
double gErrorCDRsLocalCharge = 0;
char   gImsiPrefix[101] ;
int    gCDRErrorFlag =0 ;
char   g_CdrStartDate[15]    ;
char   gFileStartDate[15]    ;
char   gCheckCallAgeFlag[2]  ;
int    gCallAge ;
char   gCheckFileAgeFlag[2]  ;
int    gFileAge ;
char   gIOTCheckFlag[2]  ;
char   gFileReceivedDate[15] ;
int    gTariffID ;
long   gCdrsArrayCount ;
long   gIotErrorCDRCount ;
long   gBulkInsertTapCdrs ;
char   gIOTChargeContext[80] ;
char   gIOTTaxContext[80] ;
char   gIOTDiscountContext[80] ;
extern int    gErrorNode   ;
double gIOTCharge   ;
double gIOTTax      ;
double gIOTDiscount ;
double gIOTChargeDiff;
double gIOTTaxDiff;
double gIOTDiscountDif;
char   gIOTDate[16];
char   gIOTCalculation[101];
char   gRAPChargeFilesDir[250];
char   gRAPChargeSuccessDir[250];
char   gRAPTestFilesDir[250];
char   gRAPTestSuccessDir[250];
char   gReadRAPChargeFilePath[250];
char   gReadRAPTestFilePath[250];
char   gRAPFileName[18] ;
char   gRAPFilesDir[500];
char   gRAPSuccessDir[500];
char   gRapFileCreationTime[15];
double ExpExchangeRate;
long   gBulkCDRIndex=0;
long   gBulkIOTCDRIndex=0;

long   gMultiIMSIPrefixFlg=0;
char   gUTCOffset[7]; 
int    gRapSpecificationVersion;
int    gRapReleaseVersion;
int    gTapSpecificationVersion;
int    gTapReleaseVersion;
int    gFrequencyInMinutes;

/* Global Function Declarations */
void   ProcessFiles(int g_fileCount);
void   InitialiseFiles();
void   fnSortDir(char **filename,int count);
int    fnDirFiles(char *pszDirName);
int    ReadDir(char *DirPath, char FileNames[TotalFilesToRead][FileNameSize]);
int    ReadCallEvents();
void   FreeMemory();
void   InitialiseCDR();
int    ProcessCDR(int CDRIndex);
int    InsertCDR();
void   SetTEMPBulkCDR(int i);
void   InitialiseBulkCDR();
void   InitialiseTEMPBulkCDR();
int    BulkInsertCDR(int TotalCDRS);
int    LoadMasterData();
void   ExitProcess(int Value);
void   InitialiseTAPFileSummary();
void   SetFileSummary();
int    InsertTAPFileSummary();
void   fnFreeMemory();
void   InitialiseLog();
void   LogError();
void   LogSuccess();
void   UpdateMissingFiles();
void   UpdateTAPErrors();
void   InitialiseMissingFiles();
void   SetMissingFiles(int TotalMissingFiles);
void   SignalHandler(int sig_num);
void   UpdateProcess(int ProcessId,char Status);
void   InitialiseTAPErrorSummary();
int    SetBulkErrorDetails(int i, int j, int k);
void   CheckBulkInsertRAPError(int TotalCDRS);
void   InitialiseErrorBulkCDR();
void   InitialiseRAPFileSummary();
void   SetRAPFileSummary();
int    InsertRAPFileSummary();
int    CheckRAPDuplicate(char FileName[31]);
int    GetRAPPartnerInfo();
void   InitialiseBulkIOTCDR();
void   SetIOTBulkCDR(int i);
void   CheckBulkInsertIOTError(int TotalIOTCDRS);
void   InitialiseIOTCDR();
void   fnSetRapDetails(char* ErrorType,int ErrorNode);
int    GenerateRAPFile();
void   InitialiseRAPDetails();

void   InitialiseACI();
void   InitialiseNI();
void   InitialiseACC();
void   InitialiseBCI();
int    fnCheckValidateFlag(int Error_Code,int Application_Tag, char Error_Type[9]);
int    SetTAPCDRsDetails();
int ValidateExchangeRate();

int    ReconcileSummary(
                       char FILE_TRANSFER_DIRECTION[2],
                       char HPLMN_CODE[7],
                       char VPLMN_CODE[7],
                       char FILE_TYPE_INDICATOR[2],
                       long FILE_SEQUENCE_NUMBER,
                       char DATA_TYPE_INDICATOR[2],
                       char PartnerCode[4]
                       );

int    ValidateBatchControlInfo();
void   CheckBulkInsertError(int TotalCDRS);
int    fnFilePresent(char* szFileName);
int    CheckDuplicate(char FileName[31]);
void sub_str(char *so,char *tr,int st_ps,int no_ch);
void InitRoamingPref();

main(int argc, char *argv[])
{
   int FnReturnValue = 0;
   int i=0;
   int Index=0;
   
   /* Declare Variables for main function parameters */
   char   iConnectString[50];
   int    iProcessId=0;
   char   iHomeOperatorCode[6];
   char   iLogFilePath[100];
   char   iLogFilePrefix[20];
   int    iRAPProcessId=0;

   /* Declare Local Variables */
   char   LogFilePathWithPrefix[121];
   DIR*   DirPtr;
   int    SetError=0;
   FILE   *tmpfp = NULL;
   FILE   *gFp   = NULL;
    /**********************************************************************/
    /* Catch Different Signals */

    signal(SIGINT , SignalHandler);
    signal(SIGKILL, SignalHandler);
    signal(SIGABRT, SignalHandler);
    signal(SIGTSTP, SignalHandler);
    signal(SIGSEGV, SignalHandler);
    signal(SIGTERM, SignalHandler);
    signal(SIGBUS , SignalHandler);
    signal(SIGSYS , SignalHandler);
    signal(SIGQUIT, SignalHandler);

   /**************************************************************************************/
   /*** Check for the number of arguments
        Argument1 is Connect String
        Argument2 is ProcessId for TAPIN Process
        Argument3 is HomeOperatorCode
        Argument4 is LogFilePath
        Argument5 is LogFilePrefix
   ***/

   if(argc != 7)
   {
      printf("Please pass the right number of Arguments\n");
      printf("Format : %s %s\n",argv[0],"ConnectString ProcessId HomeOperatorCode LogFilePath LogFilePrefix RAPProcessId");
      exit(0);
   }

   /**************************************************************************************/
   /*** Read the Input Arguments to Local Variables ***/
   iConnectString[0] ='\0';
   iLogFilePath[0]   ='\0';
   iLogFilePrefix[0] ='\0';

   sprintf(iConnectString,"%s",argv[1]);
   iProcessId = atoi(argv[2]);
   sprintf(iHomeOperatorCode,"%s",argv[3]);
   sprintf(iLogFilePath,"%s",argv[4]);
   sprintf(iLogFilePrefix,"%s",argv[5]);
   iRAPProcessId = atoi(argv[6]);

   /**************************************************************************************/
   /*** Validate all the Input Parameters ***/

   /* Validate the LogFilePath */
   DirPtr = opendir(iLogFilePath);

   if(!DirPtr)
   {
      printf("LogFilePath Specified:-%s-",iLogFilePath);
      perror("Invalid LogFilePath Specified. Exiting from the Process.");
      exit(1);
   }

   if(closedir(DirPtr) == -1)
   {
      perror("Error Closing the LogFilePath Directory");
      exit(1);
   }

   if(iLogFilePath[strlen(iLogFilePath)-1]=='/')
   {
      iLogFilePath[strlen(iLogFilePath)-1]='\0';
   }

   /* Prepare the LogFile Name with LogFilePath and LogFilePrefix */
   sprintf(LogFilePathWithPrefix,"%s/%s",iLogFilePath,iLogFilePrefix);

   /* Call the startLogger() routine to start the Logger */
   startLogger(LogFilePathWithPrefix);

   TRACEENTRY(1,"%s","------------- TAPIN Process Started");

   /* Validate the ConnectString */
   /* EXEC SQL CONNECT :iConnectString; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 4;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )10;
   sqlstm.offset = (unsigned int  )5;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)iConnectString;
   sqlstm.sqhstl[0] = (unsigned int  )50;
   sqlstm.sqhsts[0] = (         int  )50;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlstm.sqlcmax = (unsigned int )100;
   sqlstm.sqlcmin = (unsigned int )2;
   sqlstm.sqlcincr = (unsigned int )1;
   sqlstm.sqlctimeout = (unsigned int )0;
   sqlstm.sqlcnowait = (unsigned int )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   if(ERRCODE != 0)
   {
      TRACEENTRY(1,"%s","Main: Error Connecting to the Database. Exiting from the Process.");
      TRACEENTRY(1,"%s%s","Main: ConnectString Input: ",iConnectString);
      exit(0);
   }

   INIT_STR(gConnectString) ;
   strcpy(gConnectString,iConnectString) ;

   /* Validate the ProcessId */
   if(iProcessId==0)
   {
      TRACEENTRY(1,"%s","Main: Please specifiy the TAPIN ProcessId.");
      TRACEENTRY(1,"%s","Main: Exiting from the Process");
      exit(1);
   }

   if(iRAPProcessId==0)
   {
      TRACEENTRY(1,"%s","Main: Please specifiy the RAPOUT ProcessId.");
      TRACEENTRY(1,"%s","Main: Exiting from the Process");
      exit(1);
   }

   /* Assign ProcessId to Global Variable */

   gProcessId = iProcessId;
   strcpy(gHomeOperatorCode,iHomeOperatorCode);
   gRAPProcessId = iRAPProcessId;
   gSignalProcessId    = gProcessId;

   /* EXEC SQL ALTER SESSION SET NLS_CALENDAR = 'Gregorian'; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 4;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "alter SESSION SET NLS_CALENDAR = 'Gregorian'";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )36;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}

 

   /**********************************************************************/
   /* Update the Process Status to Start */
   INIT_STR(gProcessStartDate) ;

   gUnixPid = getpid() ;

   /* EXEC SQL SELECT TO_CHAR(CURRENT_DATE,'YYYYMMDDHH24MISS') INTO :gProcessStartDate FROM DUAL; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 4;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select TO_CHAR(CURRENT_DATE,'YYYYMMDDHH24MISS') into :b0  \
from DUAL ";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )51;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)gProcessStartDate;
   sqlstm.sqhstl[0] = (unsigned int  )15;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


   if (ERRCODE != 0)
   {
      TRACEENTRY (1,"%s%d","main : Error in getting CURRENT_DATE from Dual. Error Code::",ERRCODE);
      exit(0) ;
   }


   UpdateProcess(gProcessId,'R');

   /**************************************************************************************/
   /* Get the Process Details from PM_PROCESSES table for the input Process id */

   /* EXEC SQL ALTER SESSION SET NLS_CALENDAR = 'Gregorian'; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 4;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "alter SESSION SET NLS_CALENDAR = 'Gregorian'";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )70;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}

 

   stProcess.PROCESS_ID = 0;
   /* EXEC SQL VAR stProcess.FILE_TYPE_INDICATOR       IS STRING(11); */ 

   /* EXEC SQL VAR stProcess.PROCESS_INPUT_START_DATE  IS STRING(15); */ 

   /* EXEC SQL VAR stProcess.PROCESS_INPUT_END_DATE    IS STRING(15); */ 

   /* EXEC SQL VAR stProcess.LOCK_FILE_PATH            IS STRING(126); */ 

   /* EXEC SQL VAR stProcess.STOP_SIGNAL_DIR           IS STRING(100); */ 

   /* EXEC SQL VAR stProcess.STOP_SIGNAL_FILE          IS STRING(26); */ 

   /* EXEC SQL VAR stProcess.STOP_SIGNAL_PATH          IS STRING(126); */ 

   /* EXEC SQL VAR stProcess.REQUEST_TYPE              IS STRING(2); */ 


   /* EXEC SQL SELECT PROCESS_ID,
                   nvl(trim(FILE_TYPE_INDICATOR),' '),
                   nvl(to_char(PROCESS_INPUT_START_DATE,'YYYYMMDDHH24MISS'),' '),
                   nvl(to_char(PROCESS_INPUT_END_DATE,'YYYYMMDDHH24MISS'),' '),
                   nvl(trim(LOCK_FILE_PATH),' '),
                   nvl(trim(STOP_SIGNAL_DIR),' '),
                   nvl(trim(STOP_SIGNAL_FILE),' '),
                   ' ',
                   nvl(REQUEST_TYPE,' ')
              INTO :stProcess
              FROM PM_PROCESSES
             WHERE PROCESS_ID = :gProcessId; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 10;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select PROCESS_ID ,nvl(trim(FILE_TYPE_INDICATOR),' ') ,nvl\
(to_char(PROCESS_INPUT_START_DATE,'YYYYMMDDHH24MISS'),' ') ,nvl(to_char(PROCES\
S_INPUT_END_DATE,'YYYYMMDDHH24MISS'),' ') ,nvl(trim(LOCK_FILE_PATH),' ') ,nvl(\
trim(STOP_SIGNAL_DIR),' ') ,nvl(trim(STOP_SIGNAL_FILE),' ') ,' ' ,nvl(REQUEST_\
TYPE,' ') into :s1 ,:s2 ,:s3 ,:s4 ,:s5 ,:s6 ,:s7 ,:s8 ,:s9   from PM_PROCESSES\
 where PROCESS_ID=:b1";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )85;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&stProcess.PROCESS_ID;
   sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)stProcess.FILE_TYPE_INDICATOR;
   sqlstm.sqhstl[1] = (unsigned int  )11;
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)stProcess.PROCESS_INPUT_START_DATE;
   sqlstm.sqhstl[2] = (unsigned int  )15;
   sqlstm.sqhsts[2] = (         int  )0;
   sqlstm.sqindv[2] = (         void  *)0;
   sqlstm.sqinds[2] = (         int  )0;
   sqlstm.sqharm[2] = (unsigned int  )0;
   sqlstm.sqadto[2] = (unsigned short )0;
   sqlstm.sqtdso[2] = (unsigned short )0;
   sqlstm.sqhstv[3] = (         void  *)stProcess.PROCESS_INPUT_END_DATE;
   sqlstm.sqhstl[3] = (unsigned int  )15;
   sqlstm.sqhsts[3] = (         int  )0;
   sqlstm.sqindv[3] = (         void  *)0;
   sqlstm.sqinds[3] = (         int  )0;
   sqlstm.sqharm[3] = (unsigned int  )0;
   sqlstm.sqadto[3] = (unsigned short )0;
   sqlstm.sqtdso[3] = (unsigned short )0;
   sqlstm.sqhstv[4] = (         void  *)stProcess.LOCK_FILE_PATH;
   sqlstm.sqhstl[4] = (unsigned int  )126;
   sqlstm.sqhsts[4] = (         int  )0;
   sqlstm.sqindv[4] = (         void  *)0;
   sqlstm.sqinds[4] = (         int  )0;
   sqlstm.sqharm[4] = (unsigned int  )0;
   sqlstm.sqadto[4] = (unsigned short )0;
   sqlstm.sqtdso[4] = (unsigned short )0;
   sqlstm.sqhstv[5] = (         void  *)stProcess.STOP_SIGNAL_DIR;
   sqlstm.sqhstl[5] = (unsigned int  )100;
   sqlstm.sqhsts[5] = (         int  )0;
   sqlstm.sqindv[5] = (         void  *)0;
   sqlstm.sqinds[5] = (         int  )0;
   sqlstm.sqharm[5] = (unsigned int  )0;
   sqlstm.sqadto[5] = (unsigned short )0;
   sqlstm.sqtdso[5] = (unsigned short )0;
   sqlstm.sqhstv[6] = (         void  *)stProcess.STOP_SIGNAL_FILE;
   sqlstm.sqhstl[6] = (unsigned int  )26;
   sqlstm.sqhsts[6] = (         int  )0;
   sqlstm.sqindv[6] = (         void  *)0;
   sqlstm.sqinds[6] = (         int  )0;
   sqlstm.sqharm[6] = (unsigned int  )0;
   sqlstm.sqadto[6] = (unsigned short )0;
   sqlstm.sqtdso[6] = (unsigned short )0;
   sqlstm.sqhstv[7] = (         void  *)stProcess.STOP_SIGNAL_PATH;
   sqlstm.sqhstl[7] = (unsigned int  )126;
   sqlstm.sqhsts[7] = (         int  )0;
   sqlstm.sqindv[7] = (         void  *)0;
   sqlstm.sqinds[7] = (         int  )0;
   sqlstm.sqharm[7] = (unsigned int  )0;
   sqlstm.sqadto[7] = (unsigned short )0;
   sqlstm.sqtdso[7] = (unsigned short )0;
   sqlstm.sqhstv[8] = (         void  *)stProcess.REQUEST_TYPE;
   sqlstm.sqhstl[8] = (unsigned int  )2;
   sqlstm.sqhsts[8] = (         int  )0;
   sqlstm.sqindv[8] = (         void  *)0;
   sqlstm.sqinds[8] = (         int  )0;
   sqlstm.sqharm[8] = (unsigned int  )0;
   sqlstm.sqadto[8] = (unsigned short )0;
   sqlstm.sqtdso[8] = (unsigned short )0;
   sqlstm.sqhstv[9] = (         void  *)&gProcessId;
   sqlstm.sqhstl[9] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[9] = (         int  )0;
   sqlstm.sqindv[9] = (         void  *)0;
   sqlstm.sqinds[9] = (         int  )0;
   sqlstm.sqharm[9] = (unsigned int  )0;
   sqlstm.sqadto[9] = (unsigned short )0;
   sqlstm.sqtdso[9] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   /* Check for Error in Execution */
   if((ERRCODE != 0))
   {
      TRACEENTRY(1,"%s-%d-","Main: Error Fetching Count from PM_PROCESSES for the ProcessId :",gProcessId);
      TRACEENTRY(1,"%s-%d-","Main: sqlca.sqlcode :",ERRCODE);
      sprintf(gErrorMessage,"%s-%d-","Error Fetching Count from PM_PROCESSES for the ProcessId",ERRCODE) ;
      ExitProcess(-1);
   }

   /* Check if LOCK_FILE_PATH is Null */
   if(strcmp(stProcess.LOCK_FILE_PATH," ")==0)
   {
      TRACEENTRY(1,"%s","Main: Invalid LOCK_FILE_PATH specified in PM_PROCESSES table");
      TRACEENTRY(1,"%s-%s-","LOCK_FILE_PATH : ",stProcess.LOCK_FILE_PATH);
      sprintf(gErrorMessage,"%s-%s-","Invalid LOCK_FILE_PATH specified in PM_PROCESSES table",stProcess.LOCK_FILE_PATH) ;
      ExitProcess(-1);
   }

   /* Check if STOP_SIGNAL_DIR is Null */
   if(strcmp(stProcess.STOP_SIGNAL_DIR," ")==0)
   {
      TRACEENTRY(1,"%s","Main: Invalid STOP_SIGNAL_DIR specified in PM_PROCESSES table");
      TRACEENTRY(1,"%s-%s-","STOP_SIGNAL_DIR : ",stProcess.STOP_SIGNAL_DIR);
      sprintf(gErrorMessage,"%s-%s-","Invalid STOP_SIGNAL_DIR specified in PM_PROCESSES table",stProcess.STOP_SIGNAL_DIR) ;
      ExitProcess(-1);
   }

   /* Check if STOP_SIGNAL_FILE is Null */
   if(strcmp(stProcess.STOP_SIGNAL_FILE," ")==0)
   {
      TRACEENTRY(1,"%s","Main: Invalid STOP_SIGNAL_FILE specified in PM_PROCESSES table");
      TRACEENTRY(1,"%s-%s-","STOP_SIGNAL_FILE : ",stProcess.STOP_SIGNAL_FILE);
      sprintf(gErrorMessage,"%s-%s-","Invalid STOP_SIGNAL_FILE specified in PM_PROCESSES table",stProcess.STOP_SIGNAL_FILE) ;
      ExitProcess(-1);
   }

   /**************************************************************************************/
   /* Set the SignalFile if any */

   if(stProcess.STOP_SIGNAL_DIR[strlen(stProcess.STOP_SIGNAL_DIR)-1]=='/')
   {
      stProcess.STOP_SIGNAL_DIR[strlen(stProcess.STOP_SIGNAL_DIR)-1]='\0';
   }

   sprintf(stProcess.STOP_SIGNAL_PATH,"%s/%s",stProcess.STOP_SIGNAL_DIR,stProcess.STOP_SIGNAL_FILE);

   /**************************************************************************************/
   /* Check for Valid SignalFile Directory */

   DirPtr = NULL;
   DirPtr = opendir(stProcess.STOP_SIGNAL_DIR);

   /* Check if the Directory specified is Valid */
   if(!DirPtr)
   {
      TRACEENTRY(1,"%s","ERROR : Invalid Stop Signal Directory Specified in PM_PROCESSES table"); /* Done */
      TRACEENTRY(1,"%s -%s-","StopSignal Directory :",stProcess.STOP_SIGNAL_DIR);
      sprintf(gErrorMessage,"%s-%s-","Invalid Stop Signal Directory Specified in PM_PROCESSES table",stProcess.STOP_SIGNAL_DIR) ;
      ExitProcess(-1);
   }

   /* Close the Directory */
   closedir(DirPtr);
   DirPtr = NULL;

   /**************************************************************************************/
   /* Check if an other process is already running.  */

   if(fnFilePresent(stProcess.LOCK_FILE_PATH) == 1)
   {
      TRACEENTRY(1,"%s","main::Lock file detected. Process in progress. New Process wont be spawned.");
      TRACEENTRY(1,"%s","main::Exiting from the Process .....");
      exit(0);
   }

   /**************************************************************************************/
   /* Remove SignalFile if any */

   unlink(stProcess.STOP_SIGNAL_PATH);

   /**************************************************************************************/
   /* Create a lock file to lock the process */

   tmpfp = NULL;
   tmpfp = fopen(stProcess.LOCK_FILE_PATH,"w+");

   if(tmpfp == NULL)
   {
      TRACEENTRY(1,"%s","main::Error Opening the Lock File. Invalid LockFile Specified in PM_PROCESSES table");
      TRACEENTRY(1,"%s-%s-","LOCK_FILE_PATH : ",stProcess.LOCK_FILE_PATH);
      sprintf(gErrorMessage,"%s-%s-","Error Opening the Lock File. Invalid LockFile Specified in PM_PROCESSES table",stProcess.LOCK_FILE_PATH) ;
      ExitProcess(-1);
   }

   fclose(tmpfp);

   INIT_STR(gLockFilePathName) ;
   sprintf(gLockFilePathName,"%s",stProcess.LOCK_FILE_PATH) ;
   
   TRACEENTRY(1,"%s","main::Lock File created for the process");

   /**************************************************************************************/
   /* Load the MasterData */

   SetError = LoadMasterData();
    
  
   /* Check for Errors */
   if(SetError==-1)
   {
     /* LogError();*/
      ExitProcess(SetError);
   }

   /**************************************************************************************/
   /* Get the SystemDate */
   /* EXEC SQL SELECT TO_CHAR(SYSDATE,'YYYYMMDDHH24MISS')
              INTO :gSystemDate
              FROM DUAL; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 10;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select TO_CHAR(SYSDATE,'YYYYMMDDHH24MISS') into :b0  from \
DUAL ";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )140;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)gSystemDate;
   sqlstm.sqhstl[0] = (unsigned int  )15;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   /**************************************************************************************/
   /* Update the PM_PROCESS table status to R for the process */
   /*EXEC SQL UPDATE PM_PROCESSES
               SET START_STOP_FLG           = 'I',
                   PROCESS_STATUS           = 'R',
                   PROCESS_LAST_START_DATE  = SYSDATE
             WHERE PROCESS_ID = :gProcessId;

   if((ERRCODE != 0))
   {
      TRACEENTRY(1,"%s : -%d-","Main: Error Updating PM_PROCESSES for the ProcessId :",gProcessId);
      TRACEENTRY(1,"%s : -%d-","Main: sqlca.sqlcode :",ERRCODE);
   }*/

   /**************************************************************************************/
   /* Loop through Charge and test files */
   for(Index=0;Index<2;Index++)
   {
      /* Index==0, Read the Charge TAPIN Files */
      if(Index==0)
      {
         while(1)
         {
            g_fileCount = 0;
            INIT_STR(gFilesDir);
            INIT_STR(gProcessedDir);
            INIT_STR(gErrorDir);
            INIT_STR(gSuccessDir);

            SetError    = 0;
            SetError    = fnDirFiles(gReadChargeFilePath);

            if(SetError != 0)
            {
               TRACEENTRY(1,"%s","Main: Error Reading Files from the Specified Directory");
            }

            TRACEENTRY(1,"%s","----------------------------------------------------------");
            TRACEENTRY(1,"%s","Main: Reading TAPIN Charge Files--------------------------");

            if(g_fileCount == 0)
            {
               TRACEENTRY(1,"%s","Main: No more TAPIN Charge Files available for processing");
               break;
            }

            TRACEENTRY(1,"%s -%d-","Main: Total Files Read :",g_fileCount);

            strcpy(gFilesDir,gChargeFilesDir);
            strcpy(gProcessedDir,gChargeProcessFilesDir);
            strcpy(gErrorDir,gChargeErrorFilesDir);
            strcpy(gSuccessDir,gChargeSuccessDir);

            if(gFilesDir[strlen(gFilesDir)-1]=='/')
            {
               sprintf(gFilesDir,"%s%s",gFilesDir,"/");
            }

            if(gProcessedDir[strlen(gProcessedDir)-1]!='/')
            {
               sprintf(gProcessedDir,"%s%s",gProcessedDir,"/");
            }

            if(gErrorDir[strlen(gErrorDir)-1]!='/')
            {
               sprintf(gErrorDir,"%s%s",gErrorDir,"/");
            }

            ProcessFiles(g_fileCount);
         }
      }

      /* Index==1 Read the Test TAPIN Files */
      if(Index==1)
      {
         while(1)
         {
            g_fileCount = 0;
            INIT_STR(gFilesDir);
            INIT_STR(gProcessedDir);
            INIT_STR(gErrorDir);
            INIT_STR(gSuccessDir);

            SetError    = 0;
            SetError    = fnDirFiles(gReadTestFilePath);

            if(SetError != 0)
            {
               TRACEENTRY(1,"%s","Main: Error Reading Files from the Specified Directory");
            }

            TRACEENTRY(1,"%s","----------------------------------------------------------");
            TRACEENTRY(1,"%s","Main: Reading TAPIN Test Files--------------------------");

            if(g_fileCount == 0)
            {
               TRACEENTRY(1,"%s","Main: No More TAPIN Test Files available for processing");
               break;
            }

            TRACEENTRY(1,"%s -%d-","Main: Total Files Read :",g_fileCount);

            strcpy(gFilesDir,gTestFilesDir);
            strcpy(gProcessedDir,gTestProcessFilesDir);
            strcpy(gErrorDir,gTestErrorFilesDir);
            strcpy(gSuccessDir,gTestSuccessDir);

            if(gFilesDir[strlen(gFilesDir)-1]=='/')
            {
               gFilesDir[strlen(gFilesDir)-1]='\0';
            }

            if(gProcessedDir[strlen(gProcessedDir)-1]!='/')
            {
               sprintf(gProcessedDir,"%s%s",gProcessedDir,"/");
            }

            if(gErrorDir[strlen(gErrorDir)-1]!='/')
            {
               sprintf(gErrorDir,"%s%s",gErrorDir,"/");
            }

            ProcessFiles(g_fileCount);
         }
      }
   }

   /* EXEC SQL COMMIT; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 10;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )159;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   /**************************************************************************************/
   /* Update the PM_PROCESS table status to S for the process */
   ExitProcess(1);


}

void ProcessFiles(int g_fileCount)
{
   int   i=0, h=0;
   char  l_fileName[500];
   char  l_successfileName[500];

   int    SetError=0;
   char   MoveProcessed[500];
   char   MoveError[500];
   char   RemoveTouchFile[500];
   int    RemoveTouchFileFlag=0;
   int    FnReturnValue=0;
   char   FileHplmnCode[6];
   int    ValidFileHPLMNCode;
  


   /* Variables are Declared to Check file Size */
   struct stat buffer             ;
   int file_status=0              ;


   time_t rawtime;
   int fildes;
   struct stat buffer1;

   int         status;
   struct tm * timeinfo;
   char FileReceivedDate[15];


   /* Loop through the files */
   for(i=0;i<g_fileCount;i++)
   {
      /* Initialise the Global Variables for each file */
      gTotalCallDuration=0;
      INIT_STR(gDataTypeIndicator);
      INIT_STR(gUTCOffset) ;
      gRapSpecificationVersion = 0;
      gRapReleaseVersion = 0;
      gExchangeRateCount = 0;
      gTaxationCount =0;
      gDiscountingCount =0;
      gUTCOffsetCount =0;
      gRecEntityInfoCount =0;
      ValidFileHPLMNCode=0;
      gFatalErrorCount = 0;
      gSevereErrorCount = 0;  
      gBulkErrorDetailsIndex = 0;

      TRACEENTRY(1,"%s","---------------------------------------------------------------------------");

      /* Check for Signal File */
      if(fnFilePresent(stProcess.STOP_SIGNAL_PATH) == 1)
      {
         TRACEENTRY(1,"%s%s","ProcessFiles :: Signal File detected:",stProcess.STOP_SIGNAL_PATH);
         TRACEENTRY(1,"%s","ProcessFiles :: Exiting from the Process .....");
         sprintf(gErrorMessage,"%s-%s-","ProcessFiles :: Signal File detected",stProcess.STOP_SIGNAL_PATH) ;
	 ExitProcess(1);
      }

      /* Initialise the Local Variables for each file */
      INIT_STR(l_fileName);
      INIT_STR(l_successfileName);
      INIT_STR(MoveProcessed);
      INIT_STR(MoveError);
      INIT_STR(RemoveTouchFile);
      INIT_STR(FileHplmnCode) ;
      INIT_STR(gFileVplmnCode) ;
      INIT_STR(gFileHplmnCode) ;
      INIT_STR(gFileSequenceNumber);

      /* Initialise the Log Structure Members for each file */
      InitialiseLog();

      /* Get the FileName to local variable */
      sprintf(l_fileName,"%s/%s",gFilesDir,g_fileNamesPtr[i]);
      sprintf(l_successfileName,"%s/%s",gSuccessDir,g_fileNamesPtr[i]);

      /* Get File Received Date */
      /* printf("File Name:-%s-\n",l_fileName) ; */

      status=stat(l_fileName, &buffer1);

      INIT_STR(FileReceivedDate) ;
      INIT_STR(gFileReceivedDate) ;

      ctime ( &buffer1.st_ctime );
      timeinfo = localtime ( &buffer1.st_ctime );
      strftime (FileReceivedDate,15,"%G%m%d%H%M%S.",timeinfo);

      strcpy(gFileReceivedDate,FileReceivedDate) ;
      /* printf("FileReceivedDate:-%s-\n",FileReceivedDate) ; */

      TRACEENTRY(1,"%s : -%d- -%s-","Processing File",i+1,g_fileNamesPtr[i]);

      INIT_STR(gTapFileName) ;
      /* Set the error structure */
      strcpy(stErrors.FILE_NAME,g_fileNamesPtr[i]);
      strcpy(gTapFileName,g_fileNamesPtr[i]);

      /* Form the commands to move the file to process and error folders */
      sprintf(MoveProcessed,"mv %s %s",l_fileName,gProcessedDir);
      sprintf(MoveError,"mv %s %s",l_fileName,gErrorDir);
      sprintf(RemoveTouchFile,"rm %s",l_successfileName);

      /* Check for TouchFile Flag for Charge and Test Files */
      if( (strcmp(stProcessDtls.CHARGE_TOUCHFILES_FLG,"Y")==0) || (strcmp(stProcessDtls.TEST_TOUCHFILES_FLG,"Y")==0) )
      {
         RemoveTouchFileFlag=1;
      }

      /****************************************************************/
      /* Added to remove 0 byte File */
      file_status = 0;
      file_status = stat(l_fileName,&buffer);

      TRACEENTRY(1,"FileName -%s:%20s:%ld",l_fileName,"File Size:",(long int)buffer.st_size);

      /*** if ((long int)buffer.st_size==0)  ***/
      if ((long int)buffer.st_size==0 && (file_status==0))
      {
            TRACEENTRY(1,"%20s%s","Result:","Rejected:Moving the Data files and remove Success files");
            TRACEENTRY(1,"%20s%s","Reason:","The data file is of zero byte");
            system(MoveError);
            if(RemoveTouchFileFlag) system(RemoveTouchFile);
            continue;
      }

      /* Initialise the Roaming preference parameters */
      InitRoamingPref();

      /* Call Substring Function to Check HPLMN Code */
      sub_str(g_fileNamesPtr[i],gFileVplmnCode,3,5) ;
      sub_str(g_fileNamesPtr[i],FileHplmnCode,8,5) ;
      sub_str(g_fileNamesPtr[i],gFileSequenceNumber,13,5) ;
      strcpy(gFileHplmnCode,FileHplmnCode) ;
      /* Check if the HPLMN Code in the file is available in the system */
      h=0;
      for(h=0;h<gHplmnCodeCount;h++)
      {
         ptRoamingPref2 = (ptRoamingPref1 + h);
         if(strcmp(FileHplmnCode,ptRoamingPref2->HPLMN_CODE)==0)
         {
              strcpy(stRoamingPref.HPLMN_CODE, ptRoamingPref2->HPLMN_CODE)                                 ; 
              strcpy(stRoamingPref.ISO_CURNCY_CODE, ptRoamingPref2->ISO_CURNCY_CODE)                       ;             
              strcpy(stRoamingPref.TAPOUT_CURNCY , ptRoamingPref2->TAPOUT_CURNCY)                          ;
              strcpy(stRoamingPref.UTC_OFFSET, ptRoamingPref2->UTC_OFFSET)                                 ;            
              stRoamingPref.TAP_SPECIFICATION_VERSION = ptRoamingPref2->TAP_SPECIFICATION_VERSION          ; 
              stRoamingPref.TAP_RELEASE_VERSION = ptRoamingPref2->TAP_RELEASE_VERSION                      ;            
              stRoamingPref.RATE_MULT_FACT = ptRoamingPref2->RATE_MULT_FACT                                ;                     
              stRoamingPref.HOME_CURNCY_ROUNDOFF_FACT = ptRoamingPref2->HOME_CURNCY_ROUNDOFF_FACT          ; 
              stRoamingPref.TAPIN_CDR_VALIDITY_DAYS  = ptRoamingPref2->TAPIN_CDR_VALIDITY_DAYS             ;
              stRoamingPref.HOME_CURNCY_TAPIN_MULTFACT = ptRoamingPref2->HOME_CURNCY_TAPIN_MULTFACT        ;
              stRoamingPref.TAPIN_EXCH_RATE_DECIMAL_PLACES = ptRoamingPref2->TAPIN_EXCH_RATE_DECIMAL_PLACES;
              stRoamingPref.TAPIN_EXCH_RATE_MULT_FACT = ptRoamingPref2->TAPIN_EXCH_RATE_MULT_FACT          ;
              strcpy(stRoamingPref.HOME_CURNCY, ptRoamingPref2->HOME_CURNCY)                               ;          
              strcpy(stRoamingPref.IMSI_PREFIX_POSTPAID, ptRoamingPref2->IMSI_PREFIX_POSTPAID)             ;
              strcpy(stRoamingPref.IMSI_PREFIX_PREPAID, ptRoamingPref2->IMSI_PREFIX_PREPAID)               ; 
              stRoamingPref.IMSI_PREFIX_POSTPAID_LEN = ptRoamingPref2->IMSI_PREFIX_POSTPAID_LEN            ; 
              stRoamingPref.IMSI_PREFIX_PREPAID_LEN  = ptRoamingPref2->IMSI_PREFIX_PREPAID_LEN             ;
              stRoamingPref.RAP_SPECIFICATION_VERSION = ptRoamingPref2->RAP_SPECIFICATION_VERSION          ; 
              stRoamingPref.RAP_RELEASE_VERSION = ptRoamingPref2->RAP_RELEASE_VERSION                      ;            

              ValidFileHPLMNCode=1;
              break;
         }
      }

      /* Move the file to error directory, if HPLMN Code not found */ 
      if(ValidFileHPLMNCode==0)
      {
         TRACEENTRY(1,"%s","HPLMN Code specified in the file is not defined in PM_ROAMING_PREFERENCES");
         TRACEENTRY(1,"%s-%s-","HPLMN Code in the File :: ",FileHplmnCode);
         TRACEENTRY(1,"%20s%s","Result:","Rejected:Moving the Data files and remove Success files");
         system(MoveError);
         if(RemoveTouchFileFlag) system(RemoveTouchFile);
         continue;
      }

      strcpy(gUTCOffset,stRoamingPref.UTC_OFFSET) ; 
      gRapSpecificationVersion = stRoamingPref.RAP_SPECIFICATION_VERSION ;
      gRapReleaseVersion       = stRoamingPref.RAP_RELEASE_VERSION       ;
      gTapSpecificationVersion = stRoamingPref.TAP_SPECIFICATION_VERSION ;
      gTapReleaseVersion       = stRoamingPref.TAP_RELEASE_VERSION       ;

      /* Check for Filename Size. This should be 17 Characters CDVPLMNHPLMNXXXXX */
      if(strlen(g_fileNamesPtr[i]) > 17)
      {
         stErrors.ERROR_CODE = sqlca.sqlcode;
         strcpy(stErrors.ERROR_DESC,"FileName should of 17 Characters. Rename the file and Reprocess");
         LogError();
         TRACEENTRY(1,"%s","ERROR : FileName size expected is 17 Characters. Rename and Reprocess");
         
         system(MoveError);
         if(RemoveTouchFileFlag) system(RemoveTouchFile);
         continue;
      }

      /* Check for Duplicate File */
      FnReturnValue = 0;
      FnReturnValue = CheckDuplicate(stErrors.FILE_NAME);

      if(FnReturnValue > 0)
      {
         LogError();
         system(MoveError);
         if(RemoveTouchFileFlag) system(RemoveTouchFile);
         continue;
      }

      /* origData = NULL; */
      FnReturnValue = 0;
      FnReturnValue = CheckFileType(l_fileName);

      /* Check for Errors */
      if(FnReturnValue == FILE_OPEN_ERROR)
      {
         stErrors.ERROR_CODE = sqlca.sqlcode;
         strcpy(stErrors.ERROR_DESC,"Error Opening the File.");
         LogError();
         TRACEENTRY(1,"%s","ERROR : Error Opening the File");

         system(MoveError);
         if(RemoveTouchFileFlag) system(RemoveTouchFile);
         continue;
      }

      if(FnReturnValue == FILE_READ_ERROR)
      {
         stErrors.ERROR_CODE = sqlca.sqlcode;
         strcpy(stErrors.ERROR_DESC,"Error Reading the File.");
         LogError();
         TRACEENTRY(1,"%s","ERROR : Error Reading the File");

         system(MoveError);
         if(RemoveTouchFileFlag) system(RemoveTouchFile);
         continue;
      }

      if(FnReturnValue == FILE_DECODE_ERROR)
      {
         stErrors.ERROR_CODE = sqlca.sqlcode;
         strcpy(stErrors.ERROR_DESC,"Error Decoding the File");
         LogError();
         TRACEENTRY(1,"%s","ERROR : Decoding the File");

         system(MoveError);
         if(RemoveTouchFileFlag) system(RemoveTouchFile);
         continue;
      }

      /* InitialiseTAPFileSummary Structure Elements */
      InitialiseTAPFileSummary();
      InitialiseTAPErrorSummary();
      InitialiseRAPFileSummary() ;
      InitialiseErrorBulkCDR() ;


      /* Check the file type as Transferbatch or Notification file */
      if(DIC.choiceId == DATAINTERCHANGE_TRANSFERBATCH)
      {
          /* Step1: Initialise BatchControlInfo Structure Members */
          gCdrsArrayCount = 0 ;
          InitialiseBCI();

          /* Step2: Read BatchControlInfo into Local Structure */
          SetError = 0;
          SetError =  ReadBCI();

          /* Step3: Check for errors during processing the BatchControlInformation */
          if(SetError==-1)
          {
             /* EXEC SQL ROLLBACK; */ 

{
             struct sqlexd sqlstm;
             sqlstm.sqlvsn = 12;
             sqlstm.arrsiz = 10;
             sqlstm.sqladtp = &sqladt;
             sqlstm.sqltdsp = &sqltds;
             sqlstm.iters = (unsigned int  )1;
             sqlstm.offset = (unsigned int  )174;
             sqlstm.cud = sqlcud0;
             sqlstm.sqlest = (unsigned char  *)&sqlca;
             sqlstm.sqlety = (unsigned short)4352;
             sqlstm.occurs = (unsigned int  )0;
             sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



             /* Log the Error and free memory */
             LogError();
             ShutdownNibbleMem();

             /* Move the file to the error folder */
             system(MoveError);
             if(RemoveTouchFileFlag) system(RemoveTouchFile);
             continue;
          }

          SetError = 0;
          SetError = ValidateBatchControlInfo();
           
          
          /* Step3: Check for errors during processing the File BatchControl Summary */
          if(SetError==-1)
          {
             /* EXEC SQL ROLLBACK; */ 

{
             struct sqlexd sqlstm;
             sqlstm.sqlvsn = 12;
             sqlstm.arrsiz = 10;
             sqlstm.sqladtp = &sqladt;
             sqlstm.sqltdsp = &sqltds;
             sqlstm.iters = (unsigned int  )1;
             sqlstm.offset = (unsigned int  )189;
             sqlstm.cud = sqlcud0;
             sqlstm.sqlest = (unsigned char  *)&sqlca;
             sqlstm.sqlety = (unsigned short)4352;
             sqlstm.occurs = (unsigned int  )0;
             sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



             /* Log the Error and free memory */
             LogError();
             ShutdownNibbleMem();

             /* Move the file to the error folder */
             system(MoveError);
             if(RemoveTouchFileFlag) system(RemoveTouchFile);
             continue;
          }
          
          /* Step4: Initialise AccountingInfo Structure Members */
          InitialiseACC();
          

          /* Step5: Read AccountingInfo into Local Structure */
          SetError = 0;
          SetError =  ReadACC();

          /* Step3: Check for errors during processing the AccountingInformation */
          if(SetError==-1)
          {
             /* EXEC SQL ROLLBACK; */ 

{
             struct sqlexd sqlstm;
             sqlstm.sqlvsn = 12;
             sqlstm.arrsiz = 10;
             sqlstm.sqladtp = &sqladt;
             sqlstm.sqltdsp = &sqltds;
             sqlstm.iters = (unsigned int  )1;
             sqlstm.offset = (unsigned int  )204;
             sqlstm.cud = sqlcud0;
             sqlstm.sqlest = (unsigned char  *)&sqlca;
             sqlstm.sqlety = (unsigned short)4352;
             sqlstm.occurs = (unsigned int  )0;
             sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



             /* Log the Error and free memory */
             LogError();
             ShutdownNibbleMem();

             /* Move the file to the error folder */
             system(MoveError);
             if(RemoveTouchFileFlag) system(RemoveTouchFile);
             continue;
          }


          /* Step6: Initialise NetworkInfo Structure Members */
          InitialiseNI();
         
           /* Step7: Read NetworkInfo into Local Structure */
          SetError = 0;
          SetError = ReadNI();
       
          /* Step3: Check for errors during processing the NetworkInformation */
          if(SetError==-1)
          {
             /* EXEC SQL ROLLBACK; */ 

{
             struct sqlexd sqlstm;
             sqlstm.sqlvsn = 12;
             sqlstm.arrsiz = 10;
             sqlstm.sqladtp = &sqladt;
             sqlstm.sqltdsp = &sqltds;
             sqlstm.iters = (unsigned int  )1;
             sqlstm.offset = (unsigned int  )219;
             sqlstm.cud = sqlcud0;
             sqlstm.sqlest = (unsigned char  *)&sqlca;
             sqlstm.sqlety = (unsigned short)4352;
             sqlstm.occurs = (unsigned int  )0;
             sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



             /* Log the Error and free memory */
             LogError();
             ShutdownNibbleMem();

             /* Move the file to the error folder */
             system(MoveError);
             if(RemoveTouchFileFlag) system(RemoveTouchFile);
             continue;
          }


	    /* Step8: Initialise AudtiControlInfo Structure Members */
          InitialiseACI();

          /* Step8: Read AuditControlInfo into Local Structure */
          SetError = 0;
          SetError = ReadACI();

          /* Step8: Check for errors during processing the AuditControlInformation */
          if(SetError==-1)
          {
             /* EXEC SQL ROLLBACK; */ 

{
             struct sqlexd sqlstm;
             sqlstm.sqlvsn = 12;
             sqlstm.arrsiz = 10;
             sqlstm.sqladtp = &sqladt;
             sqlstm.sqltdsp = &sqltds;
             sqlstm.iters = (unsigned int  )1;
             sqlstm.offset = (unsigned int  )234;
             sqlstm.cud = sqlcud0;
             sqlstm.sqlest = (unsigned char  *)&sqlca;
             sqlstm.sqlety = (unsigned short)4352;
             sqlstm.occurs = (unsigned int  )0;
             sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



             /* Log the Error and free memory */
             LogError();
             ShutdownNibbleMem();

             /* Move the file to the error folder */
             system(MoveError);
             if(RemoveTouchFileFlag) system(RemoveTouchFile);
             continue;
          }

        
          
          /* Step9: Initialise the BulkCDR Structure Members */
          InitialiseBulkCDR();
            InitialiseTEMPBulkCDR() ;
         
	
          /* Step10: Read Calls into Local Structure */
          SetError = 0;
          SetError = ReadCallEvents();
 

          /* Step10: Check for errors during processing the Calls */
          if(SetError==-1)
          {
              /* EXEC SQL ROLLBACK; */ 

{
              struct sqlexd sqlstm;
              sqlstm.sqlvsn = 12;
              sqlstm.arrsiz = 10;
              sqlstm.sqladtp = &sqladt;
              sqlstm.sqltdsp = &sqltds;
              sqlstm.iters = (unsigned int  )1;
              sqlstm.offset = (unsigned int  )249;
              sqlstm.cud = sqlcud0;
              sqlstm.sqlest = (unsigned char  *)&sqlca;
              sqlstm.sqlety = (unsigned short)4352;
              sqlstm.occurs = (unsigned int  )0;
              sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



              /* Log the Error and free memory */
              LogError();
              ShutdownNibbleMem();

              /* Move the file to the error folder */
              system(MoveError);
              if(RemoveTouchFileFlag) system(RemoveTouchFile);
              continue;
          }

         strcpy(gDataTypeIndicator,"D");

          /* Step11: Validate Transfer Batch Group Information Details */
          SetError = 0;
          SetError = ValidateTBGroupInfo();


          /* Step11: Check for errors during Validation */
          if(SetError==-1)
          {
             /* EXEC SQL ROLLBACK; */ 

{
             struct sqlexd sqlstm;
             sqlstm.sqlvsn = 12;
             sqlstm.arrsiz = 10;
             sqlstm.sqladtp = &sqladt;
             sqlstm.sqltdsp = &sqltds;
             sqlstm.iters = (unsigned int  )1;
             sqlstm.offset = (unsigned int  )264;
             sqlstm.cud = sqlcud0;
             sqlstm.sqlest = (unsigned char  *)&sqlca;
             sqlstm.sqlety = (unsigned short)4352;
             sqlstm.occurs = (unsigned int  )0;
             sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



             /* Log the Error and free memory */
             LogError();
             ShutdownNibbleMem();

             /* Move the file to the error folder */
             system(MoveError);
             if(RemoveTouchFileFlag) system(RemoveTouchFile);
             continue;
          }


     }
      else if(DIC.choiceId == DATAINTERCHANGE_NOTIFICATION)
      {
         /* Step1: Initialise BatchControlInfo Structure Members */
         InitialiseBCI();
         InitialiseACC();
         InitialiseACI();
         InitialiseNI();

         /* Step2: Read BatchControlInfo into Local Structure */
         SetError = ReadNotification();

          /* Step3: Check for errors during processing the Notification File */
          if(SetError==-1)
          {
             /* EXEC SQL ROLLBACK; */ 

{
             struct sqlexd sqlstm;
             sqlstm.sqlvsn = 12;
             sqlstm.arrsiz = 10;
             sqlstm.sqladtp = &sqladt;
             sqlstm.sqltdsp = &sqltds;
             sqlstm.iters = (unsigned int  )1;
             sqlstm.offset = (unsigned int  )279;
             sqlstm.cud = sqlcud0;
             sqlstm.sqlest = (unsigned char  *)&sqlca;
             sqlstm.sqlety = (unsigned short)4352;
             sqlstm.occurs = (unsigned int  )0;
             sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



             /* Log the Error and free memory */
             LogError();
             ShutdownNibbleMem();

             /* Move the file to the error folder */
             system(MoveError);
             if(RemoveTouchFileFlag) system(RemoveTouchFile);
             continue;
          }

         SetError = 0;
         SetError = ValidateBatchControlInfo();

         /* Step3: Check for errors during processing the File BatchControl Summary */
         if(SetError==-1)
         {
            /* EXEC SQL ROLLBACK; */ 

{
            struct sqlexd sqlstm;
            sqlstm.sqlvsn = 12;
            sqlstm.arrsiz = 10;
            sqlstm.sqladtp = &sqladt;
            sqlstm.sqltdsp = &sqltds;
            sqlstm.iters = (unsigned int  )1;
            sqlstm.offset = (unsigned int  )294;
            sqlstm.cud = sqlcud0;
            sqlstm.sqlest = (unsigned char  *)&sqlca;
            sqlstm.sqlety = (unsigned short)4352;
            sqlstm.occurs = (unsigned int  )0;
            sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



            /* Log the Error and free memory */
            LogError();
            ShutdownNibbleMem();

            /* Move the file to the error folder */
            system(MoveError);
            if(RemoveTouchFileFlag) system(RemoveTouchFile);
            continue;
         }

         strcpy(gDataTypeIndicator,"N");

         SetError = 0;
         SetError = ValidateNTGroupInfo();

         /* Check for errors during Validation of Notification File */
         if(SetError==-1)
         {
            /* EXEC SQL ROLLBACK; */ 

{
            struct sqlexd sqlstm;
            sqlstm.sqlvsn = 12;
            sqlstm.arrsiz = 10;
            sqlstm.sqladtp = &sqladt;
            sqlstm.sqltdsp = &sqltds;
            sqlstm.iters = (unsigned int  )1;
            sqlstm.offset = (unsigned int  )309;
            sqlstm.cud = sqlcud0;
            sqlstm.sqlest = (unsigned char  *)&sqlca;
            sqlstm.sqlety = (unsigned short)4352;
            sqlstm.occurs = (unsigned int  )0;
            sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



            /* Log the Error and free memory */
            LogError();
            ShutdownNibbleMem();

            /* Move the file to the error folder */
            system(MoveError);
            if(RemoveTouchFileFlag) system(RemoveTouchFile);
            continue;
         }

      }


if ((strcmp(gDataTypeIndicator,"D")==0) && (strcmp(gGenerateFilesFlg,"N")!=0))
{
 SetError = 0;
 SetError = ValidateExchangeRate();

  if(SetError==-1)
                 {  
                 gBulkErrorDetailsIndex =0;
		 gFatalErrorCount =-1;
		 gSevereErrorCount = -1;
              /* Rollback the changes done to the database */
              /* EXEC SQL ROLLBACK; */ 

{
              struct sqlexd sqlstm;
              sqlstm.sqlvsn = 12;
              sqlstm.arrsiz = 10;
              sqlstm.sqladtp = &sqladt;
              sqlstm.sqltdsp = &sqltds;
              sqlstm.iters = (unsigned int  )1;
              sqlstm.offset = (unsigned int  )324;
              sqlstm.cud = sqlcud0;
              sqlstm.sqlest = (unsigned char  *)&sqlca;
              sqlstm.sqlety = (unsigned short)4352;
              sqlstm.occurs = (unsigned int  )0;
              sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



              /* Log the Error and free memory */
              LogError();
              ShutdownNibbleMem();

              /* Move the file to the error folder */ 
              system(MoveError);
              if(RemoveTouchFileFlag) system(RemoveTouchFile);
              continue;
           }


}

      /* Call BulkInsertCDR only if still CDRS are pending to be Bulk Inserted */
      if(gBulkInsertTapCdrs > 0)
      {
          /* Insert CDRS in bulk */
          SetError = BulkInsertCDR(gBulkInsertTapCdrs);

          if(SetError == -1)
          {
              /* Rollback the changes done to the database */
              TRACEENTRY(1,"%s","LastBulkInsert : All Transactions would be rolled back");
              /* EXEC SQL ROLLBACK; */ 

{
              struct sqlexd sqlstm;
              sqlstm.sqlvsn = 12;
              sqlstm.arrsiz = 10;
              sqlstm.sqladtp = &sqladt;
              sqlstm.sqltdsp = &sqltds;
              sqlstm.iters = (unsigned int  )1;
              sqlstm.offset = (unsigned int  )339;
              sqlstm.cud = sqlcud0;
              sqlstm.sqlest = (unsigned char  *)&sqlca;
              sqlstm.sqlety = (unsigned short)4352;
              sqlstm.occurs = (unsigned int  )0;
              sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



              /* Log the Error and free memory */
              LogError();
              ShutdownNibbleMem();

              /* Move the file to the error folder */
              system(MoveError);
              if(RemoveTouchFileFlag) system(RemoveTouchFile);
              continue;
          }

          /* Initialise the Index used for Bulk CDR Count */
          gBulkCDRIndex = 0;
          gBulkInsertTapCdrs = 0 ;

          /* Initialise the BulkCDR Structure Members */
          InitialiseBulkCDR();
      }
  

      if((gFatalErrorCount > 0))
      {
           gSevereErrorCount = 0 ;
           TRACEENTRY(1,"%s","RAP FATAL Error Present: CDR Transactions would be rolled back");
           /* EXEC SQL ROLLBACK; */ 

{
           struct sqlexd sqlstm;
           sqlstm.sqlvsn = 12;
           sqlstm.arrsiz = 10;
           sqlstm.sqladtp = &sqladt;
           sqlstm.sqltdsp = &sqltds;
           sqlstm.iters = (unsigned int  )1;
           sqlstm.offset = (unsigned int  )354;
           sqlstm.cud = sqlcud0;
           sqlstm.sqlest = (unsigned char  *)&sqlca;
           sqlstm.sqlety = (unsigned short)4352;
           sqlstm.occurs = (unsigned int  )0;
           sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


           /* EXEC SQL DELETE FROM PM_TMP_TAP_CDRS ; */ 

{
           struct sqlexd sqlstm;
           sqlstm.sqlvsn = 12;
           sqlstm.arrsiz = 10;
           sqlstm.sqladtp = &sqladt;
           sqlstm.sqltdsp = &sqltds;
           sqlstm.stmt = "delete  from PM_TMP_TAP_CDRS ";
           sqlstm.iters = (unsigned int  )1;
           sqlstm.offset = (unsigned int  )369;
           sqlstm.cud = sqlcud0;
           sqlstm.sqlest = (unsigned char  *)&sqlca;
           sqlstm.sqlety = (unsigned short)4352;
           sqlstm.occurs = (unsigned int  )0;
           sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


           /* EXEC SQL COMMIT ; */ 

{
           struct sqlexd sqlstm;
           sqlstm.sqlvsn = 12;
           sqlstm.arrsiz = 10;
           sqlstm.sqladtp = &sqladt;
           sqlstm.sqltdsp = &sqltds;
           sqlstm.iters = (unsigned int  )1;
           sqlstm.offset = (unsigned int  )384;
           sqlstm.cud = sqlcud0;
           sqlstm.sqlest = (unsigned char  *)&sqlca;
           sqlstm.sqlety = (unsigned short)4352;
           sqlstm.occurs = (unsigned int  )0;
           sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


      }



      /* Set the FileTypeIndicator in case of Notification File */
      if(strcmp(gDataTypeIndicator,"N")==0)
      {
         if(g_fileNamesPtr[i][0] == 'C')
         {
            strcpy(BCI.FileTypeIndicator,"C");
         }
         else if (g_fileNamesPtr[i][0] == 'T')
         {
            strcpy(BCI.FileTypeIndicator,"T");
         }
      }
 
 
      /* Call BulkInsertErrorDetails only if still Error Details are pending to be Bulk Inserted */
      if(gBulkErrorDetailsIndex > 0)
      {
          /* Insert Error CDRS in bulk */
          SetError = 0 ;
          SetError = BulkInsertErrorDetails(gBulkErrorDetailsIndex);
	 
	      if(SetError == -1)
          {
              /* Rollback the changes done to the database */
              TRACEENTRY(1,"%s","LastBulkInsert : All Transactions would be rolled back");
              /* EXEC SQL ROLLBACK; */ 

{
              struct sqlexd sqlstm;
              sqlstm.sqlvsn = 12;
              sqlstm.arrsiz = 10;
              sqlstm.sqladtp = &sqladt;
              sqlstm.sqltdsp = &sqltds;
              sqlstm.iters = (unsigned int  )1;
              sqlstm.offset = (unsigned int  )399;
              sqlstm.cud = sqlcud0;
              sqlstm.sqlest = (unsigned char  *)&sqlca;
              sqlstm.sqlety = (unsigned short)4352;
              sqlstm.occurs = (unsigned int  )0;
              sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


 
              /* Log the Error and free memory */
              LogError();
              ShutdownNibbleMem();

              /* Move the file to the error folder */
              system(MoveError);
              if(RemoveTouchFileFlag) system(RemoveTouchFile);
              continue;

          }

          /* Initialise the BulkCDRIndex */
          gBulkErrorDetailsIndex = 0;

          /* Reset the BulkCDR Array */
          InitialiseErrorBulkCDR();
      }

   
      /* Set the RAPFileSummary Structure Elements with the File Summary Data */
      if((gFatalErrorCount>0) || (gSevereErrorCount > 0))
      {
         
           SetRAPFileSummary();
           
           TRACEENTRY(1,"%s : -%s-","RAP File Name",RAPFileSummary.RAP_FILE_NAME);

	    strcpy(RAPFileSummary.TAP_FILE_NAME,g_fileNamesPtr[i]);
           
           SetError = GenerateRAPFile() ; 
           
           if(SetError==-1)
           {
               /* EXEC SQL ROLLBACK; */ 

{
               struct sqlexd sqlstm;
               sqlstm.sqlvsn = 12;
               sqlstm.arrsiz = 10;
               sqlstm.sqladtp = &sqladt;
               sqlstm.sqltdsp = &sqltds;
               sqlstm.iters = (unsigned int  )1;
               sqlstm.offset = (unsigned int  )414;
               sqlstm.cud = sqlcud0;
               sqlstm.sqlest = (unsigned char  *)&sqlca;
               sqlstm.sqlety = (unsigned short)4352;
               sqlstm.occurs = (unsigned int  )0;
               sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



               LogError();
               ShutdownNibbleMem();

               system(MoveError);
               if(RemoveTouchFileFlag) system(RemoveTouchFile);
               continue;
           }

           /* Insert the RAP File Summary to the Database */
           SetError = 0;
           SetError = InsertRAPFileSummary();

           /* Check for any errors */
           if(SetError==-1)
           {
               /* Rollback the changes done to the database */
               /* EXEC SQL ROLLBACK; */ 

{
               struct sqlexd sqlstm;
               sqlstm.sqlvsn = 12;
               sqlstm.arrsiz = 10;
               sqlstm.sqladtp = &sqladt;
               sqlstm.sqltdsp = &sqltds;
               sqlstm.iters = (unsigned int  )1;
               sqlstm.offset = (unsigned int  )429;
               sqlstm.cud = sqlcud0;
               sqlstm.sqlest = (unsigned char  *)&sqlca;
               sqlstm.sqlety = (unsigned short)4352;
               sqlstm.occurs = (unsigned int  )0;
               sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



               /* Log the Error and free memory */
               LogError();
               ShutdownNibbleMem();

               /* Move the file to the error folder */
               system(MoveError);
               if(RemoveTouchFileFlag) system(RemoveTouchFile);
               continue;
           }

      }
 

      if(strcmp(gGenerateFilesFlg,"N")==0)
      {
          TRACEENTRY(1,"%s","RAP File Generation Flag for this Partner is N(No)");
      }

      /* Set the TAFileSummary Structure Elements with the File Summary Data */
 
      if(gFatalErrorCount == 0)
      {
      
          SetFileSummary();
          strcpy(FileSummary.FILE_NAME,g_fileNamesPtr[i]);

          /* Insert the TAP File Summary to the Database */
          SetError = 0;
          SetError = InsertTAPFileSummary(); 

          /* Check for any errors */
          if(SetError==-1)
          {  
              /* Rollback the changes done to the database */
              /* EXEC SQL ROLLBACK; */ 

{
              struct sqlexd sqlstm;
              sqlstm.sqlvsn = 12;
              sqlstm.arrsiz = 10;
              sqlstm.sqladtp = &sqladt;
              sqlstm.sqltdsp = &sqltds;
              sqlstm.iters = (unsigned int  )1;
              sqlstm.offset = (unsigned int  )444;
              sqlstm.cud = sqlcud0;
              sqlstm.sqlest = (unsigned char  *)&sqlca;
              sqlstm.sqlety = (unsigned short)4352;
              sqlstm.occurs = (unsigned int  )0;
              sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



              /* Log the Error and free memory */
              LogError();
              ShutdownNibbleMem();

              /* Move the file to the error folder */ 
              system(MoveError);
              if(RemoveTouchFileFlag) system(RemoveTouchFile);
              continue;
          }

          /* Reconcile FileSummary with CallSummary for the Operator */
          if(strcmp(gDataTypeIndicator,"D")==0)
          {
               SetError = ReconcileSummary(
                                           FileSummary.FILE_TRANSFER_DIRECTION,
                                           FileSummary.HPLMN_CODE,
                                           FileSummary.VPLMN_CODE,
                                           FileSummary.FILE_TYPE_INDICATOR,
                                           FileSummary.FILE_SEQUENCE_NUMBER,
                                           FileSummary.DATA_TYPE_INDICATOR,
                                           FileSummary.PARTNER_CODE
                                          );

               if(SetError==-1)
               {
                   TRACEENTRY(1,"%s","LastBulkInsert : All Transactions would be rolled back");
                   /* EXEC SQL ROLLBACK; */ 

{
                   struct sqlexd sqlstm;
                   sqlstm.sqlvsn = 12;
                   sqlstm.arrsiz = 10;
                   sqlstm.sqladtp = &sqladt;
                   sqlstm.sqltdsp = &sqltds;
                   sqlstm.iters = (unsigned int  )1;
                   sqlstm.offset = (unsigned int  )459;
                   sqlstm.cud = sqlcud0;
                   sqlstm.sqlest = (unsigned char  *)&sqlca;
                   sqlstm.sqlety = (unsigned short)4352;
                   sqlstm.occurs = (unsigned int  )0;
                   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



                   /* Log the Error and free memory */
                   LogError();
                   ShutdownNibbleMem();

                   /* Move the file to the error folder */
                   system(MoveError);
                   if(RemoveTouchFileFlag) system(RemoveTouchFile);
                   continue;
               }
           }

           TRACEENTRY(1,"%s","Reconcilation Status : Success - FileSummary matches with CallSummary");

           /* Set the MissingFile Status */
           UpdateMissingFiles();  

           /* Update any previous error */
           UpdateTAPErrors();
      }

      /* Log the File Processing Status to the Database */
      /* LogSuccess(); */

      /* Commit all transactions to the Database for successfully processed files */
      /* EXEC SQL COMMIT; */ 

{
      struct sqlexd sqlstm;
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 10;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )474;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)4352;
      sqlstm.occurs = (unsigned int  )0;
      sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



      if((gFatalErrorCount>0) || (gSevereErrorCount > 0))
      {
         TRACEENTRY(1,"%s","ProcessFiles  : File has TAP Errors, RAP File would be generated");

/*         SetError = GenerateRAPFile() ;
         if(SetError==-1)
         {
             EXEC SQL ROLLBACK;

             LogError();
             ShutdownNibbleMem();

             system(MoveError);
             if(RemoveTouchFileFlag) system(RemoveTouchFile);
             continue;
         }
*/
      }



 if(SetError !=-1)
         {
          
      /* Release the Memory allocated to the File */
      ShutdownNibbleMem();
      }


      if(gFatalErrorCount>0)
      {
      
         /* Move the file to the error folder */
         system(MoveError);
         if(RemoveTouchFileFlag) system(RemoveTouchFile);
      }
         else if (gFatalErrorCount!=-1)
      {
         
         /* Move the file to the processed directory */
         system(MoveProcessed); 
         if(RemoveTouchFileFlag) system(RemoveTouchFile);
      }

   }
   
  
   /* EXEC SQL COMMIT; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 10;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )489;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


}


int GenerateRAPFile()
{

   /* Variables to fetch required number of CDRs from the Table */
   int   rows_to_fetch=0, rows_before=0, rows_this_time=0;
   int   SetError = 0;
   char   RAPDataFile[500]       ;
   char   RAPSuccessFile[500]    ;
   char   l_RAPtouchCommand[500] ;
   char   l_RAPRmDataFile[500]   ;
   char   l_RmSuccessFile[500]   ;
   int    SetErrorValue;
   long   CDRCount = 0 ;
   long   RapDetailsCount;
   int    i ;
   FILE *rFp ;
   int OldCallSequence = -1 ;
   int OldErrorNode    = -1 ;
   long lReturnDetailsCount ;
   double lTotalSevereReturnValue ;
   int  RemoveRAPTouchFileFlag =  0 ;
   char lc_TOTError;

   CallEventDetail *pCallEventDetail;

   
   /****************************************************************************************/
   /* Make the Remove File and Touch file Creation Command */
   sprintf(RAPDataFile,"%s%s",gRAPFilesDir,gRAPFileName) ;


   /* Form the Success File Name */
   sprintf(RAPSuccessFile,"%s%s",gRAPSuccessDir,gRAPFileName) ;

   /* Form the Touch File Command */
   sprintf(l_RAPtouchCommand,"%s%s","touch ",RAPSuccessFile);

   /* Form the Remove File Command */
   sprintf(l_RAPRmDataFile,"%s%s","rm ",RAPDataFile);

   /* Form the Remove Success File Command */
   sprintf(l_RmSuccessFile,"%s%s","rm ",RAPSuccessFile);


   /* Check for TouchFile Flag for Charge and Test Files */
   if( (strcmp(stRAPProcessDtls.CHARGE_TOUCHFILES_FLG,"Y")==0) || (strcmp(stRAPProcessDtls.TEST_TOUCHFILES_FLG,"Y")==0) )
   {
       RemoveRAPTouchFileFlag=1;
    }

   EncodeReturnBatch() ; 
   EncodeRAPBatchControlInfo() ; 

   /* EXEC SQL SELECT COUNT(*) 
              INTO :RapDetailsCount
              FROM PM_RAP_DETAILS
             WHERE FILE_TRANSFER_DIRECTION = :RAPFileSummary.FILE_TRANSFER_DIRECTION
               AND HPLMN_CODE              = :RAPFileSummary.HPLMN_CODE
               AND VPLMN_CODE              = :RAPFileSummary.VPLMN_CODE
               AND FILE_TYPE_INDICATOR     = :RAPFileSummary.FILE_TYPE_INDICATOR
               AND RAP_SEQUENCE_NUMBER     = :RAPFileSummary.FILE_SEQUENCE_NUMBER
               AND NVL(RAP_STATUS,'Q')     = 'Q'; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 10;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select count(*)  into :b0  from PM_RAP_DETAILS where (((((\
FILE_TRANSFER_DIRECTION=:b1 and HPLMN_CODE=:b2) and VPLMN_CODE=:b3) and FILE_T\
YPE_INDICATOR=:b4) and RAP_SEQUENCE_NUMBER=:b5) and NVL(RAP_STATUS,'Q')='Q')";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )504;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&RapDetailsCount;
   sqlstm.sqhstl[0] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)(RAPFileSummary.FILE_TRANSFER_DIRECTION);
   sqlstm.sqhstl[1] = (unsigned int  )2;
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)(RAPFileSummary.HPLMN_CODE);
   sqlstm.sqhstl[2] = (unsigned int  )6;
   sqlstm.sqhsts[2] = (         int  )0;
   sqlstm.sqindv[2] = (         void  *)0;
   sqlstm.sqinds[2] = (         int  )0;
   sqlstm.sqharm[2] = (unsigned int  )0;
   sqlstm.sqadto[2] = (unsigned short )0;
   sqlstm.sqtdso[2] = (unsigned short )0;
   sqlstm.sqhstv[3] = (         void  *)(RAPFileSummary.VPLMN_CODE);
   sqlstm.sqhstl[3] = (unsigned int  )7;
   sqlstm.sqhsts[3] = (         int  )0;
   sqlstm.sqindv[3] = (         void  *)0;
   sqlstm.sqinds[3] = (         int  )0;
   sqlstm.sqharm[3] = (unsigned int  )0;
   sqlstm.sqadto[3] = (unsigned short )0;
   sqlstm.sqtdso[3] = (unsigned short )0;
   sqlstm.sqhstv[4] = (         void  *)(RAPFileSummary.FILE_TYPE_INDICATOR);
   sqlstm.sqhstl[4] = (unsigned int  )2;
   sqlstm.sqhsts[4] = (         int  )0;
   sqlstm.sqindv[4] = (         void  *)0;
   sqlstm.sqinds[4] = (         int  )0;
   sqlstm.sqharm[4] = (unsigned int  )0;
   sqlstm.sqadto[4] = (unsigned short )0;
   sqlstm.sqtdso[4] = (unsigned short )0;
   sqlstm.sqhstv[5] = (         void  *)&(RAPFileSummary.FILE_SEQUENCE_NUMBER);
   sqlstm.sqhstl[5] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[5] = (         int  )0;
   sqlstm.sqindv[5] = (         void  *)0;
   sqlstm.sqinds[5] = (         int  )0;
   sqlstm.sqharm[5] = (unsigned int  )0;
   sqlstm.sqadto[5] = (unsigned short )0;
   sqlstm.sqtdso[5] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


 

   if(ERRCODE != 0)
   {
       TRACEENTRY(1,"%s","Error Getting Count from PM_RAP_DETAILS");
       TRACEENTRY(1,"%s-%d-","sqlca.sqlcode:",ERRCODE);
       TRACEENTRY(1,"%s","Cannot Proceed with this Operator. Please Rectify the Error(PM_RAP_DETAILS)");
       return -1;
   }

   /* EXEC SQL DECLARE RAPDetails CURSOR FOR
     SELECT NVL(CALL_SEQUENCE,0)                 ,
            NVL(TRIM(ERROR_TYPE),' ')            ,
            NVL(APPLICATION_TAG,0)               ,
            NVL(TRIM(ERROR_FIELD_NAME),' ')      ,
            NVL(ERROR_CODE,0)                    ,
            NVL(TRIM(ERROR_MESSAGE),' ')         ,
            NVL(TRIM(ERROR_CONTEXT_DETAILS),' ') ,
            NVL(TRIM(CONTEXT_NAME),' ')          ,
            NVL(ERROR_SEQUENCE,0)                ,
            NVL(ERROR_NODE,0)                    ,
            NVL(TRIM(RAP_STATUS),' ')            ,
	    NVL(IOT_CHARGE,0)                    ,
	    NVL(TRIM(IOT_DATE),' ')              ,
	    NVL(TRIM(IOT_CALCULATION),' ')       ,
            ROWID
       FROM PM_RAP_DETAILS
      WHERE FILE_TRANSFER_DIRECTION = :RAPFileSummary.FILE_TRANSFER_DIRECTION
        AND HPLMN_CODE              = :RAPFileSummary.HPLMN_CODE
        AND VPLMN_CODE              = :RAPFileSummary.VPLMN_CODE
        AND FILE_TYPE_INDICATOR     = :RAPFileSummary.FILE_TYPE_INDICATOR
        AND RAP_SEQUENCE_NUMBER     = :RAPFileSummary.FILE_SEQUENCE_NUMBER
        AND NVL(RAP_STATUS,'Q')     = 'Q'
   ORDER BY CALL_SEQUENCE,ERROR_NODE ASC; */ 


    
   /* EXEC SQL OPEN RAPDetails; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 10;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = sq0031;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )543;
   sqlstm.selerr = (unsigned short)20000;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqcmod = (unsigned int )0;
   sqlstm.sqhstv[0] = (         void  *)(RAPFileSummary.FILE_TRANSFER_DIRECTION);
   sqlstm.sqhstl[0] = (unsigned int  )2;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)(RAPFileSummary.HPLMN_CODE);
   sqlstm.sqhstl[1] = (unsigned int  )6;
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)(RAPFileSummary.VPLMN_CODE);
   sqlstm.sqhstl[2] = (unsigned int  )7;
   sqlstm.sqhsts[2] = (         int  )0;
   sqlstm.sqindv[2] = (         void  *)0;
   sqlstm.sqinds[2] = (         int  )0;
   sqlstm.sqharm[2] = (unsigned int  )0;
   sqlstm.sqadto[2] = (unsigned short )0;
   sqlstm.sqtdso[2] = (unsigned short )0;
   sqlstm.sqhstv[3] = (         void  *)(RAPFileSummary.FILE_TYPE_INDICATOR);
   sqlstm.sqhstl[3] = (unsigned int  )2;
   sqlstm.sqhsts[3] = (         int  )0;
   sqlstm.sqindv[3] = (         void  *)0;
   sqlstm.sqinds[3] = (         int  )0;
   sqlstm.sqharm[3] = (unsigned int  )0;
   sqlstm.sqadto[3] = (unsigned short )0;
   sqlstm.sqtdso[3] = (unsigned short )0;
   sqlstm.sqhstv[4] = (         void  *)&(RAPFileSummary.FILE_SEQUENCE_NUMBER);
   sqlstm.sqhstl[4] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[4] = (         int  )0;
   sqlstm.sqindv[4] = (         void  *)0;
   sqlstm.sqinds[4] = (         int  )0;
   sqlstm.sqharm[4] = (unsigned int  )0;
   sqlstm.sqadto[4] = (unsigned short )0;
   sqlstm.sqtdso[4] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}




   for(i=0;i<RapDetailsCount;i++)
   {
   
      InitialiseRAPDetails();

      /* EXEC SQL FETCH RAPDetails
                INTO :stRAPDetails.CALL_SEQUENCE,
                     :stRAPDetails.ERROR_TYPE,
                     :stRAPDetails.APPLICATION_TAG,
                     :stRAPDetails.ERROR_FIELD_NAME,
                     :stRAPDetails.ERROR_CODE,
                     :stRAPDetails.ERROR_MESSAGE,
                     :stRAPDetails.ERROR_CONTEXT_DETAILS,
                     :stRAPDetails.CONTEXT_NAME,
                     :stRAPDetails.ERROR_SEQUENCE,
                     :stRAPDetails.ERROR_NODE,
                     :stRAPDetails.RAP_STATUS,
		     :stRAPDetails.IOT_CHARGE,
		     :stRAPDetails.IOT_DATE,
		     :stRAPDetails.IOT_CALCULATION,
                     :stRAPDetails.ROWID; */ 

{
      struct sqlexd sqlstm;
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 15;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )578;
      sqlstm.selerr = (unsigned short)20000;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)4352;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqfoff = (           int )0;
      sqlstm.sqfmod = (unsigned int )2;
      sqlstm.sqhstv[0] = (         void  *)&(stRAPDetails.CALL_SEQUENCE);
      sqlstm.sqhstl[0] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[0] = (         int  )0;
      sqlstm.sqindv[0] = (         void  *)0;
      sqlstm.sqinds[0] = (         int  )0;
      sqlstm.sqharm[0] = (unsigned int  )0;
      sqlstm.sqadto[0] = (unsigned short )0;
      sqlstm.sqtdso[0] = (unsigned short )0;
      sqlstm.sqhstv[1] = (         void  *)(stRAPDetails.ERROR_TYPE);
      sqlstm.sqhstl[1] = (unsigned int  )9;
      sqlstm.sqhsts[1] = (         int  )0;
      sqlstm.sqindv[1] = (         void  *)0;
      sqlstm.sqinds[1] = (         int  )0;
      sqlstm.sqharm[1] = (unsigned int  )0;
      sqlstm.sqadto[1] = (unsigned short )0;
      sqlstm.sqtdso[1] = (unsigned short )0;
      sqlstm.sqhstv[2] = (         void  *)&(stRAPDetails.APPLICATION_TAG);
      sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[2] = (         int  )0;
      sqlstm.sqindv[2] = (         void  *)0;
      sqlstm.sqinds[2] = (         int  )0;
      sqlstm.sqharm[2] = (unsigned int  )0;
      sqlstm.sqadto[2] = (unsigned short )0;
      sqlstm.sqtdso[2] = (unsigned short )0;
      sqlstm.sqhstv[3] = (         void  *)(stRAPDetails.ERROR_FIELD_NAME);
      sqlstm.sqhstl[3] = (unsigned int  )51;
      sqlstm.sqhsts[3] = (         int  )0;
      sqlstm.sqindv[3] = (         void  *)0;
      sqlstm.sqinds[3] = (         int  )0;
      sqlstm.sqharm[3] = (unsigned int  )0;
      sqlstm.sqadto[3] = (unsigned short )0;
      sqlstm.sqtdso[3] = (unsigned short )0;
      sqlstm.sqhstv[4] = (         void  *)&(stRAPDetails.ERROR_CODE);
      sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[4] = (         int  )0;
      sqlstm.sqindv[4] = (         void  *)0;
      sqlstm.sqinds[4] = (         int  )0;
      sqlstm.sqharm[4] = (unsigned int  )0;
      sqlstm.sqadto[4] = (unsigned short )0;
      sqlstm.sqtdso[4] = (unsigned short )0;
      sqlstm.sqhstv[5] = (         void  *)(stRAPDetails.ERROR_MESSAGE);
      sqlstm.sqhstl[5] = (unsigned int  )501;
      sqlstm.sqhsts[5] = (         int  )0;
      sqlstm.sqindv[5] = (         void  *)0;
      sqlstm.sqinds[5] = (         int  )0;
      sqlstm.sqharm[5] = (unsigned int  )0;
      sqlstm.sqadto[5] = (unsigned short )0;
      sqlstm.sqtdso[5] = (unsigned short )0;
      sqlstm.sqhstv[6] = (         void  *)(stRAPDetails.ERROR_CONTEXT_DETAILS);
      sqlstm.sqhstl[6] = (unsigned int  )101;
      sqlstm.sqhsts[6] = (         int  )0;
      sqlstm.sqindv[6] = (         void  *)0;
      sqlstm.sqinds[6] = (         int  )0;
      sqlstm.sqharm[6] = (unsigned int  )0;
      sqlstm.sqadto[6] = (unsigned short )0;
      sqlstm.sqtdso[6] = (unsigned short )0;
      sqlstm.sqhstv[7] = (         void  *)(stRAPDetails.CONTEXT_NAME);
      sqlstm.sqhstl[7] = (unsigned int  )51;
      sqlstm.sqhsts[7] = (         int  )0;
      sqlstm.sqindv[7] = (         void  *)0;
      sqlstm.sqinds[7] = (         int  )0;
      sqlstm.sqharm[7] = (unsigned int  )0;
      sqlstm.sqadto[7] = (unsigned short )0;
      sqlstm.sqtdso[7] = (unsigned short )0;
      sqlstm.sqhstv[8] = (         void  *)&(stRAPDetails.ERROR_SEQUENCE);
      sqlstm.sqhstl[8] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[8] = (         int  )0;
      sqlstm.sqindv[8] = (         void  *)0;
      sqlstm.sqinds[8] = (         int  )0;
      sqlstm.sqharm[8] = (unsigned int  )0;
      sqlstm.sqadto[8] = (unsigned short )0;
      sqlstm.sqtdso[8] = (unsigned short )0;
      sqlstm.sqhstv[9] = (         void  *)&(stRAPDetails.ERROR_NODE);
      sqlstm.sqhstl[9] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[9] = (         int  )0;
      sqlstm.sqindv[9] = (         void  *)0;
      sqlstm.sqinds[9] = (         int  )0;
      sqlstm.sqharm[9] = (unsigned int  )0;
      sqlstm.sqadto[9] = (unsigned short )0;
      sqlstm.sqtdso[9] = (unsigned short )0;
      sqlstm.sqhstv[10] = (         void  *)(stRAPDetails.RAP_STATUS);
      sqlstm.sqhstl[10] = (unsigned int  )2;
      sqlstm.sqhsts[10] = (         int  )0;
      sqlstm.sqindv[10] = (         void  *)0;
      sqlstm.sqinds[10] = (         int  )0;
      sqlstm.sqharm[10] = (unsigned int  )0;
      sqlstm.sqadto[10] = (unsigned short )0;
      sqlstm.sqtdso[10] = (unsigned short )0;
      sqlstm.sqhstv[11] = (         void  *)&(stRAPDetails.IOT_CHARGE);
      sqlstm.sqhstl[11] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[11] = (         int  )0;
      sqlstm.sqindv[11] = (         void  *)0;
      sqlstm.sqinds[11] = (         int  )0;
      sqlstm.sqharm[11] = (unsigned int  )0;
      sqlstm.sqadto[11] = (unsigned short )0;
      sqlstm.sqtdso[11] = (unsigned short )0;
      sqlstm.sqhstv[12] = (         void  *)(stRAPDetails.IOT_DATE);
      sqlstm.sqhstl[12] = (unsigned int  )16;
      sqlstm.sqhsts[12] = (         int  )0;
      sqlstm.sqindv[12] = (         void  *)0;
      sqlstm.sqinds[12] = (         int  )0;
      sqlstm.sqharm[12] = (unsigned int  )0;
      sqlstm.sqadto[12] = (unsigned short )0;
      sqlstm.sqtdso[12] = (unsigned short )0;
      sqlstm.sqhstv[13] = (         void  *)(stRAPDetails.IOT_CALCULATION);
      sqlstm.sqhstl[13] = (unsigned int  )101;
      sqlstm.sqhsts[13] = (         int  )0;
      sqlstm.sqindv[13] = (         void  *)0;
      sqlstm.sqinds[13] = (         int  )0;
      sqlstm.sqharm[13] = (unsigned int  )0;
      sqlstm.sqadto[13] = (unsigned short )0;
      sqlstm.sqtdso[13] = (unsigned short )0;
      sqlstm.sqhstv[14] = (         void  *)(stRAPDetails.ROWID);
      sqlstm.sqhstl[14] = (unsigned int  )20;
      sqlstm.sqhsts[14] = (         int  )0;
      sqlstm.sqindv[14] = (         void  *)0;
      sqlstm.sqinds[14] = (         int  )0;
      sqlstm.sqharm[14] = (unsigned int  )0;
      sqlstm.sqadto[14] = (unsigned short )0;
      sqlstm.sqtdso[14] = (unsigned short )0;
      sqlstm.sqphsv = sqlstm.sqhstv;
      sqlstm.sqphsl = sqlstm.sqhstl;
      sqlstm.sqphss = sqlstm.sqhsts;
      sqlstm.sqpind = sqlstm.sqindv;
      sqlstm.sqpins = sqlstm.sqinds;
      sqlstm.sqparm = sqlstm.sqharm;
      sqlstm.sqparc = sqlstm.sqharc;
      sqlstm.sqpadto = sqlstm.sqadto;
      sqlstm.sqptdso = sqlstm.sqtdso;
      sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



      if (ERRCODE != 0)
      {
           SetError=-1;
           TRACEENTRY (1,"%s%d","main : Error in fetching data from PM_TAP_FILE_SUMRY .Error Code::",ERRCODE);
           break;
      }

      fnRemTrailSpaces(stRAPDetails.ERROR_TYPE);
      fnRemTrailSpaces(stRAPDetails.ROWID);
      fnRemTrailSpaces(stRAPDetails.ERROR_FIELD_NAME);
      fnRemTrailSpaces(stRAPDetails.ERROR_MESSAGE);
      fnRemTrailSpaces(stRAPDetails.ERROR_CONTEXT_DETAILS);
      fnRemTrailSpaces(stRAPDetails.CONTEXT_NAME);
      fnRemTrailSpaces(stRAPDetails.RAP_STATUS);
     /* fnRemTrailSpaces(stRAPDetails.IOT_CHARGE); */
      fnRemTrailSpaces(stRAPDetails.IOT_DATE);
      fnRemTrailSpaces(stRAPDetails.IOT_CALCULATION);




      CDRCount = 0 ;
    
        
      if(stRAPDetails.CALL_SEQUENCE > 0)
      {
          FOR_EACH_LIST_ELMT(pCallEventDetail,DIC.a.transferBatch->callEventDetails)
          {
             CDRCount = CDRCount + 1 ;
	                  
             if(CDRCount == stRAPDetails.CALL_SEQUENCE)
             {
                 if(stRAPDetails.ERROR_NODE == 9)
                 {
                    stMOC1 = pCallEventDetail->a.mobileOriginatedCall;
                    break ;
                 }
                 else if(stRAPDetails.ERROR_NODE == 10)
                 {
                    stMTC1 = pCallEventDetail->a.mobileTerminatedCall;
                    break ;
                 }
                 else if(stRAPDetails.ERROR_NODE == 14)
                 {
                    stGC = pCallEventDetail->a.gprsCall ;
                    break ;
                 }
                 else if(stRAPDetails.ERROR_NODE == 11)
                 {
                   stSUP1 = pCallEventDetail->a.supplServiceEvent;
		   break;
                 }
		 else if(stRAPDetails.ERROR_NODE == 433)
		 {
		  stMESG = pCallEventDetail->a.messagingEvent;
		  break;
                 }

        	 else if(stRAPDetails.ERROR_NODE == 434)
		 {
		 stMSESS = pCallEventDetail->a.mobileSession;
		 break;
		 } 
		
                 }
           
	      }
          }
  
      
      if((OldCallSequence != stRAPDetails.CALL_SEQUENCE) && (strcmp(stRAPDetails.ERROR_TYPE,"SEVERE") == 0))
      {
        lc_TOTError = 'N';
        EncodeReturnDetails(BCI.FileSequenceNumber,&stRAPDetails); 
        fnSetRapDetails(stRAPDetails.ERROR_TYPE,stRAPDetails.ERROR_NODE);
        OldCallSequence = stRAPDetails.CALL_SEQUENCE;
	
      }

   /* For Charge and TAX  Related IOT error */
      else if((OldCallSequence == stRAPDetails.CALL_SEQUENCE) && (strcmp(stRAPDetails.ERROR_TYPE,"SEVERE") == 0))
      {

	if((stRAPDetails.ERROR_CODE == 200) && ((stRAPDetails.APPLICATION_TAG ==62) || (stRAPDetails.APPLICATION_TAG ==397)))
	   if(lc_TOTError == 'N')
	   { 
	     lc_TOTError = 'Y';
             EncodeOSI(&stRAPDetails);
          
	   }
          }

      if((strcmp(stRAPDetails.ERROR_TYPE,"FATAL") == 0) && (OldErrorNode != stRAPDetails.ERROR_NODE))
      {

         if(OldErrorNode == -1)
         {
            EncodeReturnDetails(BCI.FileSequenceNumber,&stRAPDetails); 
         }
         fnSetRapDetails(stRAPDetails.ERROR_TYPE,stRAPDetails.ERROR_NODE);
         OldErrorNode = stRAPDetails.ERROR_NODE ;

      }
   

      EncodeErrorDetail(stRAPDetails.ERROR_CODE,stRAPDetails.ERROR_CONTEXT_DETAILS,stRAPDetails.ERROR_TYPE,stRAPDetails.ERROR_NODE) ;

      
    /* EXEC SQL UPDATE PM_RAP_DETAILS
                  SET RAP_STATUS = 'S'
                WHERE ROWID = :stRAPDetails.ROWID; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 15;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "update PM_RAP_DETAILS  set RAP_STATUS='S' where ROWID=:b0";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )653;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)(stRAPDetails.ROWID);
    sqlstm.sqhstl[0] = (unsigned int  )20;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         void  *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned int  )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



        if(ERRCODE != 0)
      {
         SetError=-1;
         TRACEENTRY(1,"%s","Error Updating the CDR Status");
         TRACEENTRY(1,"%s-%d-","sqlca.sqlcode:",ERRCODE);
         TRACEENTRY(1,"%s","Cannot Proceed with this Operator. Please Rectify the Error(PM_RAP_DETAILS)");
         /* EXEC SQL ROLLBACK; */ 

{
         struct sqlexd sqlstm;
         sqlstm.sqlvsn = 12;
         sqlstm.arrsiz = 15;
         sqlstm.sqladtp = &sqladt;
         sqlstm.sqltdsp = &sqltds;
         sqlstm.iters = (unsigned int  )1;
         sqlstm.offset = (unsigned int  )672;
         sqlstm.cud = sqlcud0;
         sqlstm.sqlest = (unsigned char  *)&sqlca;
         sqlstm.sqlety = (unsigned short)4352;
         sqlstm.occurs = (unsigned int  )0;
         sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


         break;
      }
    
   }
   

    
   /* EXEC SQL CLOSE RAPDetails; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 15;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )687;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}

 

   if(SetError==-1)
   {
      return -1 ;
   }
   SetErrorValue = 0;
   lReturnDetailsCount = 0 ;
   lTotalSevereReturnValue = 0 ;

   if(strcmp(RAPFileSummary.ERROR_TYPE,"SEVERE") == 0)
   {
       lReturnDetailsCount = gErrorCDRsCount;
       lTotalSevereReturnValue = gErrorCDRsCharge ;
   }
   else
   {
       lReturnDetailsCount = 1;
       lTotalSevereReturnValue = 0;
   }

  
   EncodeRapAuditControlInfo(BCI.FileSequenceNumber,lTotalSevereReturnValue,lReturnDetailsCount) ;
  

   rFp = NULL;
   rFp = fopen(RAPDataFile,"wb");

   if(!rFp)
   {
       TRACEENTRY(1,"%s","ERROR : Error Opening the File");
       TRACEENTRY(1,"%s -%s-","RAPDataFileName :",RAPDataFile);
       TRACEENTRY(1,"%s","Cannot Proceed with File Generation");
       return -1;
   }
  
   SetErrorValue = EncodeRapout(rFp);
   
   /* Check for encoding error, close the file and continue with other records */
   if(SetErrorValue==-1)
   {
       TRACEENTRY(1,"%s-%s-","Main: Error Encoding the File : ",RAPDataFile);
       TRACEENTRY(1,"%s","Main: Cannot Proceed with this File Generation");
       /* Close the File */
       fclose(rFp);
       system(l_RAPRmDataFile) ;
       return -1;
   }

   if(RemoveRAPTouchFileFlag) system(l_RAPtouchCommand) ;
}


void InitialiseRAPDetails()
{

   stRAPDetails.CALL_SEQUENCE = 0 ;
   INIT_STR(stRAPDetails.ERROR_TYPE) ;
   stRAPDetails.APPLICATION_TAG = 0 ;
   INIT_STR(stRAPDetails.ERROR_FIELD_NAME) ;
   stRAPDetails.ERROR_CODE = 0 ;
   INIT_STR(stRAPDetails.ERROR_MESSAGE) ;
   INIT_STR(stRAPDetails.ERROR_CONTEXT_DETAILS) ;
   INIT_STR(stRAPDetails.CONTEXT_NAME) ;
   stRAPDetails.ERROR_SEQUENCE = 0;
   stRAPDetails.ERROR_NODE = 0 ;
   INIT_STR(stRAPDetails.RAP_STATUS) ;
   stRAPDetails.IOT_CHARGE =0;
   INIT_STR(stRAPDetails.IOT_DATE) ;
   INIT_STR(stRAPDetails.IOT_CALCULATION) ;
   INIT_STR(stRAPDetails.ROWID) ;
 

}

int ReadDir(char *DirPath, char FileNames[TotalFilesToRead][FileNameSize])
{
   int     FileCount=0,d;
   DIR     *DirPtr;
   struct  dirent *DirStr;

   d=TotalFilesToRead;

   DirPtr = opendir(DirPath);

   while((DirStr = readdir(DirPtr)) != NULL && d)
   {
     if(d==0) break;

     if(strcmp(DirStr->d_name,".")==0 || strcmp(DirStr->d_name,"..")==0)
     {
        continue;
     }
     strcpy(FileNames[FileCount++],DirStr->d_name);
     d--;
   }

   closedir(DirPtr);

   return(FileCount);
}


void FreeMemory()
{
   /*
   if(origData != NULL)
   {
      free (origData);
   }
   */
}


int ReadCallEvents()
{

   int i=0;
   int SetError=0;
   int  ErrorReturnValue = 0 ;
   int ErrorCount=0;
   int  lValidateFlag = 0    ;
   int IotReturn = 0 ;
   CallEventDetail *pCallEventDetail;

   long     op_ExecStatus ;
   char     op_ErrCode[51], op_ErrMesg[201] ;
   int      l_TapDecimalPlaces = 0 ;

   gBulkCDRIndex = 0;
   gBulkIOTCDRIndex = 0;
   gTotalCdrsCount = 0;
   gProcessingCDRNo = 0;
   gRejectedErrorNo = 0;
   gErrorCDRsCount = 0 ;
   gErrorCDRsCharge = 0;
   gErrorCDRsLocalCharge = 0;
   gErrorCDRsTax = 0;
   gErrorCDRsDiscount = 0;
   gErrorCDRsDuration = 0;
   gErrorCDRsIncVolume = 0;
   gErrorCDRsOutVolume = 0;

   InitialiseBulkIOTCDR() ; 

   if(NOT_NULL(DIC.a.transferBatch->callEventDetails))
   {
      FOR_EACH_LIST_ELMT(pCallEventDetail,DIC.a.transferBatch->callEventDetails)
      {
         SetError=0;
         InitialiseCDR();
         gProcessingCDRNo = i+1 ;
         gCDRErrorFlag = 0 ;
  
         INIT_STR(stContext.CallEventDetails) ; 
         sprintf(stContext.CallEventDetails,"1:0:L;3:%d:L",i+1) ;
         fnRemTrailSpaces(stContext.CallEventDetails) ;

         switch(pCallEventDetail->choiceId)
         {
            case CALLEVENTDETAIL_MOBILEORIGINATEDCALL:
            {
                if(NOT_NULL(pCallEventDetail->a.mobileOriginatedCall))
                {
                   SetError = ReadMOC(pCallEventDetail->a.mobileOriginatedCall);
                }
                break;
            }

            case CALLEVENTDETAIL_MOBILETERMINATEDCALL:
            {
		if(NOT_NULL(pCallEventDetail->a.mobileTerminatedCall))
                {
                   SetError = ReadMTC(pCallEventDetail->a.mobileTerminatedCall); 
                }
               break;
            }

            case CALLEVENTDETAIL_SUPPLSERVICEEVENT:
            {
               if(NOT_NULL(pCallEventDetail->a.supplServiceEvent))
               {
                  SetError = ReadSUP(pCallEventDetail->a.supplServiceEvent); 
               }
               break;
            }

            case CALLEVENTDETAIL_SERVICECENTREUSAGE:
            {
               TRACEENTRY(1,"%s","ServiceCentreUsage Call present in the File");
               SetError=-1;
               break;
            }

            case CALLEVENTDETAIL_GPRSCALL:
            {
               if(NOT_NULL(pCallEventDetail->a.gprsCall))
               {
                  SetError = ReadGprsCall(pCallEventDetail->a.gprsCall);
               }
               break;
            }

            case CALLEVENTDETAIL_CONTENTTRANSACTION:
            {
               TRACEENTRY(1,"%s","ContentTransaction Call present in the File");
               SetError=-1;
               break;
            }

            case CALLEVENTDETAIL_LOCATIONSERVICE:
            {
               TRACEENTRY(1,"%s","LocationService Call present in the File");
               SetError=-1;
               break;
            }
           case CALLEVENTDETAIL_MOBILESESSION:
            {
               if(NOT_NULL(pCallEventDetail->a.mobileSession))
               {
                  SetError = ReadMSESS(pCallEventDetail->a.mobileSession);
               }
               break;
            }
              case CALLEVENTDETAIL_MESSAGINGEVENT:
            {
               if(NOT_NULL(pCallEventDetail->a.messagingEvent))
               {
                  SetError = ReadMESG(pCallEventDetail->a.messagingEvent);
               }
               break;
            }


         }

         /* Check for CDRS that are not currently processed */
         if(SetError==-1)
         {
            TRACEENTRY(1,"%s","Cannot Proceed with the File");
            return -1;
         }

         if(SetError==0) 
         {
            /* Process the CDR */
            SetError = 0;
            SetError = ProcessCDR(i); 

            if(SetError == -1)
            {
               TRACEENTRY(1,"%s","ProcessCDR : All Transactions would be rolled back");
               /* EXEC SQL ROLLBACK; */ 

{
               struct sqlexd sqlstm;
               sqlstm.sqlvsn = 12;
               sqlstm.arrsiz = 15;
               sqlstm.sqladtp = &sqladt;
               sqlstm.sqltdsp = &sqltds;
               sqlstm.iters = (unsigned int  )1;
               sqlstm.offset = (unsigned int  )702;
               sqlstm.cud = sqlcud0;
               sqlstm.sqlest = (unsigned char  *)&sqlca;
               sqlstm.sqlety = (unsigned short)4352;
               sqlstm.occurs = (unsigned int  )0;
               sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


             /*  LogError();*/
               return -1;
            }
          
            if(gCDRErrorFlag==0)
            {

                 /* Set the BulkCDR Array with the Processed CDR */
                 SetTEMPBulkCDR(gBulkCDRIndex);

                 /* Increment the BulkCDRIndex */
                 gBulkCDRIndex++;

                 /* Call BulkInsertCDR only if the count of CDR is equal to CDR array size */

               
               /*  if(gBulkCDRIndex == 4998) 
                 {
                      Insert CDRS in bulk 
                     SetError = BulkInsertCDR(gBulkCDRIndex);
                     if(SetError == -1)
                     {
                         TRACEENTRY(1,"%s","BatchBulkInsert : All Transactions would be rolled back");
                         LogError();
                         return -1;
                     }

                      Initialise the BulkCDRIndex 
                     gBulkCDRIndex = 0;

                      Reset the BulkCDR Array 
                     InitialiseBulkCDR();
                 }
              */
            }

            if(strcmp(gIOTCheckFlag,"Y") == 0)
            {
                SetIOTBulkCDR(gBulkIOTCDRIndex) ;
                gBulkIOTCDRIndex++ ;
              
               
              if(gBulkIOTCDRIndex == 4998)
          {
                     /* Insert CDRS in bulk */
                     SetError = BulkInsertIOTCDR(gBulkIOTCDRIndex);
                     if(SetError == -1)
                     {
                         TRACEENTRY(1,"%s","BatchIOTBulkInsert : All Transactions would be rolled back");
                         LogError();
                         return -1;
                     }

                     /* Initialise the BulkCDRIndex */
                     gBulkIOTCDRIndex = 0;

                     /* Reset the BulkCDR Array */
                     InitialiseBulkIOTCDR();
       }

            }

            /****
            SetError = 0;
            SetError = InsertCDR();

            if(SetError == -1)
            { 
               return -1;
            }
            ****/
         }

         /* Increment the LoopCount */
         i++;

      }
      gTotalCdrsCount = i ;
   }
   else
   {
      REI.ERROR_CODE[gRejectedErrorNo]  = 35                             ;
      REI.APPLICATION_TAG[gRejectedErrorNo] = 1                          ;
      strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")                   ;
      lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
      if(lValidateFlag == 0)
      {
          strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"TransferBatch");
          strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TransferBatch")     ;
          strcpy(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:1")        ;
          strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Group Call Event Details not present within group");
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
       gRejectedErrorNo = 0 ;
   }


   if((gBulkIOTCDRIndex > 0) && (strcmp(gIOTCheckFlag,"Y") == 0) && (strcmp(gGenerateFilesFlg,"N")!=0))
   {
        /* Insert IOT CDRS in bulk */
        TRACEENTRY(1,"IOT : Doing Bulk Insert => %s.", gTapFileName);
        SetError = BulkInsertIOTCDR(gBulkIOTCDRIndex);
        if(SetError == -1)
        {
             TRACEENTRY(1,"%s","BatchBulkIOTInsert : All Transactions would be rolled back");
             /* EXEC SQL ROLLBACK; */ 

{
             struct sqlexd sqlstm;
             sqlstm.sqlvsn = 12;
             sqlstm.arrsiz = 15;
             sqlstm.sqladtp = &sqladt;
             sqlstm.sqltdsp = &sqltds;
             sqlstm.iters = (unsigned int  )1;
             sqlstm.offset = (unsigned int  )717;
             sqlstm.cud = sqlcud0;
             sqlstm.sqlest = (unsigned char  *)&sqlca;
             sqlstm.sqlety = (unsigned short)4352;
             sqlstm.occurs = (unsigned int  )0;
             sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


             LogError();
             return -1;
        }

        /* Initialise the BulkIOTCDRIndex */
        gBulkIOTCDRIndex = 0;

        /* Reset the BulkIOTCDR Array */
        /* InitialiseBulkIOTCDR(); */

        l_TapDecimalPlaces = ACC.TapDecimalPlaces ;

        TRACEENTRY(1,"IOT : Calling IOT Procedure for file => %s.", gTapFileName);
        /* Calling IOT Procedure to Calculate the Charge, Tax and Discount in order to compare with the Partner TAPIN Details */
        memset(op_ErrCode,51,'\0');
        memset(op_ErrMesg,201,'\0');

        /* EXEC SQL EXECUTE
        BEGIN
             PR_TAP_RATING(:l_TapDecimalPlaces, :op_ExecStatus, :op_ErrCode, :op_ErrMesg) ;
        END ;
        END-EXEC ; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 12;
        sqlstm.arrsiz = 15;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "begin PR_TAP_RATING ( :l_TapDecimalPlaces , :op_ExecS\
tatus , :op_ErrCode , :op_ErrMesg ) ; END ;";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )732;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (         void  *)&l_TapDecimalPlaces;
        sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         void  *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned int  )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (         void  *)&op_ExecStatus;
        sqlstm.sqhstl[1] = (unsigned int  )sizeof(long);
        sqlstm.sqhsts[1] = (         int  )0;
        sqlstm.sqindv[1] = (         void  *)0;
        sqlstm.sqinds[1] = (         int  )0;
        sqlstm.sqharm[1] = (unsigned int  )0;
        sqlstm.sqadto[1] = (unsigned short )0;
        sqlstm.sqtdso[1] = (unsigned short )0;
        sqlstm.sqhstv[2] = (         void  *)op_ErrCode;
        sqlstm.sqhstl[2] = (unsigned int  )51;
        sqlstm.sqhsts[2] = (         int  )0;
        sqlstm.sqindv[2] = (         void  *)0;
        sqlstm.sqinds[2] = (         int  )0;
        sqlstm.sqharm[2] = (unsigned int  )0;
        sqlstm.sqadto[2] = (unsigned short )0;
        sqlstm.sqtdso[2] = (unsigned short )0;
        sqlstm.sqhstv[3] = (         void  *)op_ErrMesg;
        sqlstm.sqhstl[3] = (unsigned int  )201;
        sqlstm.sqhsts[3] = (         int  )0;
        sqlstm.sqindv[3] = (         void  *)0;
        sqlstm.sqinds[3] = (         int  )0;
        sqlstm.sqharm[3] = (unsigned int  )0;
        sqlstm.sqadto[3] = (unsigned short )0;
        sqlstm.sqtdso[3] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


                       
       
     
        TRACEENTRY(1,"IOT : Completed IOT Calculation for file => %s.", gTapFileName);
        
 
        if (op_ExecStatus == 0)
        {
            TRACEENTRY(1,"IOT : Procedure return status is => %d, Error Code => %s", op_ExecStatus, op_ErrCode);
            TRACEENTRY(1,"IOT : File %s is Repriced",gTapFileName);
	    IotReturn = LoadIOTCDRS() ; 
	     if(IotReturn != 0)
            {
                TRACEENTRY(1,"%s","----Error in IOT Details Checking----");
                return  -1;
            }
        }
        else
        {
            TRACEENTRY(1,"IOT : Procedure return status is => %d, Error Code => %s", op_ExecStatus, op_ErrCode);
            fnRemTrailSpaces(op_ErrMesg) ;
            TRACEENTRY (1,"IOT : %s%s","Error Message:: ",op_ErrMesg) ;
            /* EXEC SQL ROLLBACK; */ 

{
            struct sqlexd sqlstm;
            sqlstm.sqlvsn = 12;
            sqlstm.arrsiz = 15;
            sqlstm.sqladtp = &sqladt;
            sqlstm.sqltdsp = &sqltds;
            sqlstm.iters = (unsigned int  )1;
            sqlstm.offset = (unsigned int  )763;
            sqlstm.cud = sqlcud0;
            sqlstm.sqlest = (unsigned char  *)&sqlca;
            sqlstm.sqlety = (unsigned short)4352;
            sqlstm.occurs = (unsigned int  )0;
            sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


            /* EXEC SQL DELETE FROM PM_TMP_TAP_CDRS; */ 

{
            struct sqlexd sqlstm;
            sqlstm.sqlvsn = 12;
            sqlstm.arrsiz = 15;
            sqlstm.sqladtp = &sqladt;
            sqlstm.sqltdsp = &sqltds;
            sqlstm.stmt = "delete  from PM_TMP_TAP_CDRS ";
            sqlstm.iters = (unsigned int  )1;
            sqlstm.offset = (unsigned int  )778;
            sqlstm.cud = sqlcud0;
            sqlstm.sqlest = (unsigned char  *)&sqlca;
            sqlstm.sqlety = (unsigned short)4352;
            sqlstm.occurs = (unsigned int  )0;
            sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}

  
            /* EXEC SQL COMMIT; */ 

{
            struct sqlexd sqlstm;
            sqlstm.sqlvsn = 12;
            sqlstm.arrsiz = 15;
            sqlstm.sqladtp = &sqladt;
            sqlstm.sqltdsp = &sqltds;
            sqlstm.iters = (unsigned int  )1;
            sqlstm.offset = (unsigned int  )793;
            sqlstm.cud = sqlcud0;
            sqlstm.sqlest = (unsigned char  *)&sqlca;
            sqlstm.sqlety = (unsigned short)4352;
            sqlstm.occurs = (unsigned int  )0;
            sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}

 
            TRACEENTRY(1,"IOT : File %s is failed",gTapFileName);
            stErrors.ERROR_CODE = sqlca.sqlcode;
            strcpy(stErrors.ERROR_DESC,"IOT rating error::");
            return -1 ;
        }
   }

   SetError = 0 ;
   SetError = SetTAPCDRsDetails() ;
   if(SetError == -1)
   {
       /* Rollback the changes done to the database */
       TRACEENTRY(1,"%s","ReadCallEvents: Error in setting TAP CDRS Details");
       TRACEENTRY(1,"%s","ReadCallEvents: All Transactions would be rolled back");
       /* EXEC SQL ROLLBACK; */ 

{
       struct sqlexd sqlstm;
       sqlstm.sqlvsn = 12;
       sqlstm.arrsiz = 15;
       sqlstm.sqladtp = &sqladt;
       sqlstm.sqltdsp = &sqltds;
       sqlstm.iters = (unsigned int  )1;
       sqlstm.offset = (unsigned int  )808;
       sqlstm.cud = sqlcud0;
       sqlstm.sqlest = (unsigned char  *)&sqlca;
       sqlstm.sqlety = (unsigned short)4352;
       sqlstm.occurs = (unsigned int  )0;
       sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


       LogError();
       return -1;
   }


   /* Call BulkInsertErrorDetails only if any Severe Error Details are pending to be Bulk Inserted */
   if((gBulkErrorDetailsIndex > 0)  && (gFatalErrorCount == 0))
   {
       /* Insert Error CDRS in bulk */

       SetError = 0 ; 
       SetError = BulkInsertErrorDetails(gBulkErrorDetailsIndex);
          if(SetError == -1)
       {
           /* Rollback the changes done to the database */
           TRACEENTRY(1,"%s","ReadCallEvents: All Transactions would be rolled back");
           /* EXEC SQL ROLLBACK; */ 

{
           struct sqlexd sqlstm;
           sqlstm.sqlvsn = 12;
           sqlstm.arrsiz = 15;
           sqlstm.sqladtp = &sqladt;
           sqlstm.sqltdsp = &sqltds;
           sqlstm.iters = (unsigned int  )1;
           sqlstm.offset = (unsigned int  )823;
           sqlstm.cud = sqlcud0;
           sqlstm.sqlest = (unsigned char  *)&sqlca;
           sqlstm.sqlety = (unsigned short)4352;
           sqlstm.occurs = (unsigned int  )0;
           sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


           LogError();
           return -1;
       }

      /* Initialise the BulkCDRIndex */
      gBulkErrorDetailsIndex = 0;

      /* Reset the BulkCDR Array */
      InitialiseErrorBulkCDR();
   }
   


   return 0;
}


int  SetTAPCDRsDetails()
{
   int i,j,k ;
   int SetError = 0 ;
   int ErrorStatus = 0 ;

   i = 0 ;
   gBulkInsertTapCdrs = 0 ;
   for(j = 0; j < gBulkCDRIndex ; j++)
   {
        ErrorStatus = 0 ;
        /* Check for Any IOT Rejected CDRs */
        if(gIotErrorCDRCount > 0)
        {
            for(k = 0; k < gIotErrorCDRCount; k++)
            {
               /* If file has any IOT rejected CDRs then don't insert those details to PM_TAP_CDRS */
               if(TEMP_CALL_SEQUENCE[j] == StIOTErrorCDR.CallSequence[k])
               {
                  ErrorStatus = 1 ;
                  break ;
               }
            }
        }
   
        if(ErrorStatus == 1)
        {
           continue ;
        }

        /* Copy the Temporary Variables Values to PM_TAP_CDRs variables */
        strcpy(FILE_TRANSFER_DIRECTION[i],TEMP_FILE_TRANSFER_DIRECTION[j]);
        strcpy(HPLMN_CODE[i],TEMP_HPLMN_CODE[j]);
        strcpy(VPLMN_CODE[i],TEMP_VPLMN_CODE[j]);
        strcpy(PARTNER_CODE[i],TEMP_PARTNER_CODE[j]);
        strcpy(FILE_TYPE_INDICATOR[i],TEMP_FILE_TYPE_INDICATOR[j]);
        FILE_SEQUENCE_NUMBER[i]    = TEMP_FILE_SEQUENCE_NUMBER[j]; 
        CALL_SEQUENCE[i]           = TEMP_CALL_SEQUENCE[j];
        strcpy(CALLS_TYPE_INDICATOR[i],TEMP_CALLS_TYPE_INDICATOR[j]);
        CALL_TYPE[i]               = TEMP_CALL_TYPE[j];
        strcpy(SERVICE_CODE[i], TEMP_SERVICE_CODE[j]) ;
        IMSI[i]                    = TEMP_IMSI[j];
        strcpy(MSISDN[i],TEMP_MSISDN[j]);
        RAPFILE_SEQUENCE_NUMBER[i] = TEMP_RAPFILE_SEQUENCE_NUMBER[j];
        strcpy(CALLED_CALLING_NUMBER[i],TEMP_CALLED_CALLING_NUMBER[j]);
        strcpy(DIALLED_DIGITS[i],TEMP_DIALLED_DIGITS[j]);
        /*   strcpy(CALLED_PLACE[i],TEMP_CALLED_PLACE[j]); */
       strncpy(CALLED_PLACE[i],TEMP_CALLED_PLACE[j],30);
        strcpy(CALLED_REGION[i],TEMP_CALLED_REGION[j]);
        CLIR_INDICATOR[i]          = TEMP_CLIR_INDICATOR[j];
        strcpy(DESTINATION_NETWORK[i],TEMP_DESTINATION_NETWORK[j]);
        strcpy(CALL_DATE[i],TEMP_CALL_DATE[j]);
        strcpy(UTC_OFFSET_CODE[i],TEMP_UTC_OFFSET_CODE[j]); 
        CALL_DURATION[i]           = TEMP_CALL_DURATION[j];
        strcpy(SIM_TOOLKIT_INDICATOR[i],TEMP_SIM_TOOLKIT_INDICATOR[j]);
        RECORDING_ENTITY_CODE[i]   = TEMP_RECORDING_ENTITY_CODE[j];
        RECORDING_ENTITY_TYPE[i]   = TEMP_RECORDING_ENTITY_TYPE[j];
        strcpy(RECORDING_ENTITY_ID[i],TEMP_RECORDING_ENTITY_ID[j]);
        strcpy(CALL_REFERENCE[i],TEMP_CALL_REFERENCE[j]);
        LOCATION_AREA[i]           = TEMP_LOCATION_AREA[j];
        CELLID[i]                  = TEMP_CELLID[j];
        strcpy(SERVING_NETWORK[i],TEMP_SERVING_NETWORK[j]);
        strcpy(IMEI[i],TEMP_IMEI[j]);
        strcpy(BASIC_SERVICE_TYPE[i],TEMP_BASIC_SERVICE_TYPE[j]);
        strcpy(BASIC_SERVICE_CODE[i],TEMP_BASIC_SERVICE_CODE[j]);
        TRANSPARENCY_INDICATOR[i]       = TEMP_TRANSPARENCY_INDICATOR[j];
        FNUR[i]                         = TEMP_FNUR[j];
        USER_PROTOCOL_INDICATOR[i]      = TEMP_USER_PROTOCOL_INDICATOR[j];
        strcpy(GUARANTEED_BIT_RATE[i],TEMP_GUARANTEED_BIT_RATE[j]);
        strcpy(MAXIMUM_BIT_RATE[i],TEMP_MAXIMUM_BIT_RATE[j]);
        strcpy(HSCSD_INDICATOR[i],TEMP_HSCSD_INDICATOR[j]);
        SUPPLIMENTARY_ACTION_CODE[i]    = TEMP_SUPPLIMENTARY_ACTION_CODE[j];
        strcpy(SUPPLIMENTARY_SERVICE_PARAMS[i],TEMP_SUPPLIMENTARY_SERVICE_PARAMS[j]);
        strcpy(THIRD_PARTY_NUMBER[i],TEMP_THIRD_PARTY_NUMBER[j]);
        THIRD_PARTY_CLIR_INDICATOR[i]   = TEMP_THIRD_PARTY_CLIR_INDICATOR[j];
 
        CAMEL_USED_FLAG[i]              = TEMP_CAMEL_USED_FLAG[j];
        CAMEL_SERVICE_LEVEL[i]          = TEMP_CAMEL_SERVICE_LEVEL[j];
        CAMEL_SERVICE_KEY[i]            = TEMP_CAMEL_SERVICE_KEY[j];
        CAMEL_DEFAULT_CALL_HANDLING[i]  = TEMP_CAMEL_DEFAULT_CALL_HANDLING[j];
        CAMEL_EXCHANGE_RATE_CODE[i]     = TEMP_CAMEL_EXCHANGE_RATE_CODE[j];
        HOME_CAMEL_EXCHANGE_RATE[i]     = TEMP_HOME_CAMEL_EXCHANGE_RATE[j];
        CAMEL_INVOCATION_FEE[i]         = TEMP_CAMEL_INVOCATION_FEE[j];
        CAMEL_DISCOUNT_CODE[i]          = TEMP_CAMEL_DISCOUNT_CODE[j];
        CAMEL_DISCOUNT[i]               = TEMP_CAMEL_DISCOUNT[j];
        CAMEL_DISCOUNTABLE_AMOUNT[i]    = TEMP_CAMEL_DISCOUNTABLE_AMOUNT[j];
        CAMEL_TAX_INFORMATION_COUNT[i]  = TEMP_CAMEL_TAX_INFORMATION_COUNT[j];
        CAMEL_TAX_CODE[i]               = TEMP_CAMEL_TAX_CODE[j];
        CAMEL_TAX_VALUE[i]              = TEMP_CAMEL_TAX_VALUE[j];
        CAMEL_TAXABLE_AMOUNT[i]         = TEMP_CAMEL_TAXABLE_AMOUNT[j];
        strcpy(CAMEL_DESTINATION_NUMBER[i],TEMP_CAMEL_DESTINATION_NUMBER[j]);
        TAP_EXCHANGE_RATE[i]          = TEMP_TAP_EXCHANGE_RATE[j];
        TAP_EXCHANGE_RATE_DECIMAL[i]  = TEMP_TAP_EXCHANGE_RATE_DECIMAL[j];
        strcpy(TAP_TAX_TYPE_RATE[i], TEMP_TAP_TAX_TYPE_RATE[j]);
        CALL_TYPE_LEVEL1[i]             = TEMP_CALL_TYPE_LEVEL1[j];
        CALL_TYPE_LEVEL2[i]             = TEMP_CALL_TYPE_LEVEL2[j];
        CALL_TYPE_LEVEL3[i]             = TEMP_CALL_TYPE_LEVEL3[j];
        CHARGE_INFORMATION_COUNT[i]     = TEMP_CHARGE_INFORMATION_COUNT[j];
        strcpy(CHARGED_ITEM[i],TEMP_CHARGED_ITEM[j]); 
        strcpy(CHARGE_TYPE[i],TEMP_CHARGE_TYPE[j]); 
        CHARGEABLE_UNITS[i]             = TEMP_CHARGEABLE_UNITS[j];
        CHARGED_UNITS[i]                = TEMP_CHARGED_UNITS[j];
        CHARGE[i]                       = TEMP_CHARGE[j];
        TAX_INFORMATION_COUNT[i]        = TEMP_TAX_INFORMATION_COUNT[j];
        TAX_CODE[i]                     = TEMP_TAX_CODE[j] ;
        TAX_VALUE[i]                    = TEMP_TAX_VALUE[j];
        TAXABLE_AMOUNT[i]               = TEMP_TAXABLE_AMOUNT[j];
        DISCOUNT_INFORMATION_COUNT[i]   = TEMP_DISCOUNT_INFORMATION_COUNT[j]; 
        DISCOUNT_CODE[i]                = TEMP_DISCOUNT_CODE[j];
        DISCOUNT[i]                     = TEMP_DISCOUNT[j];
        DISCOUNTABLE_AMT[i]             = TEMP_DISCOUNTABLE_AMT[j];
        HOME_CURNCY_CAMEL_FEE[i]        = TEMP_HOME_CURNCY_CAMEL_FEE[j];
        HOME_CURNCY_CAMEL_TAX[i]        = TEMP_HOME_CURNCY_CAMEL_TAX[j];
        HOME_CURNCY_CAMEL_DISCOUNT[i]   = TEMP_HOME_CURNCY_CAMEL_DISCOUNT[j];
        HOME_CURNCY_CHARGE[i]           = TEMP_HOME_CURNCY_CHARGE[j] ;
        HOME_CURNCY_TAX[i]              = TEMP_HOME_CURNCY_TAX[j];
        HOME_CURNCY_DISCOUNT[i]         = TEMP_HOME_CURNCY_DISCOUNT[j];
        HOME_CURNCY_SURCHARGE[i]        = TEMP_HOME_CURNCY_SURCHARGE[j];
        HOME_CURNCY_CHARGE_WITH_TAX[i]  = TEMP_HOME_CURNCY_CHARGE_WITH_TAX[j];
        HOME_CURNCY_TOTAL_CHARGE[i]     = TEMP_HOME_CURNCY_TOTAL_CHARGE[j];
        HOME_EXCHANGE_RATE[i]           = TEMP_HOME_EXCHANGE_RATE[j];
        TAP_EXCHANGE_RATE_CODE[i]       = TEMP_TAP_EXCHANGE_RATE_CODE[j];
        strcpy(NETWORK_ACCESS_IDENTIFER[i],TEMP_NETWORK_ACCESS_IDENTIFER[j]);
        strcpy(PDP_ADDRESS[i],TEMP_PDP_ADDRESS[j]);
        strcpy(APN_NI[i],TEMP_APN_NI[j]);
        strcpy(APN_OI[i],TEMP_APN_OI[j]);
        CAUSE_FOR_TERMINATION[i]        = TEMP_CAUSE_FOR_TERMINATION[j];
        strcpy(PARTIAL_TYPE_INDICATOR[i],TEMP_PARTIAL_TYPE_INDICATOR[j]);
        CHARGING_ID[i]                  = TEMP_CHARGING_ID[j];
        strcpy(SERVING_LOCATION_DESC[i],TEMP_SERVING_LOCATION_DESC[j]);
        DATA_VOLUME_INCOMING[i]         = TEMP_DATA_VOLUME_INCOMING[j];
        DATA_VOLUME_OUTGOING[i]         = TEMP_DATA_VOLUME_OUTGOING[j];
        SGSN_RECORDING_ENTITY_CODE1[i]  = TEMP_SGSN_RECORDING_ENTITY_CODE1[j];
        strcpy(SGSN_RECORDING_ENTITY_ID1[i],TEMP_SGSN_RECORDING_ENTITY_ID1[j]);
        SGSN_RECORDING_ENTITY_CODE2[i]  = TEMP_SGSN_RECORDING_ENTITY_CODE2[j];
        strcpy(SGSN_RECORDING_ENTITY_ID2[i],TEMP_SGSN_RECORDING_ENTITY_ID2[j]);
        SGSN_RECORDING_ENTITY_CODE3[i]  = TEMP_SGSN_RECORDING_ENTITY_CODE3[j];
        strcpy(SGSN_RECORDING_ENTITY_ID3[i],TEMP_SGSN_RECORDING_ENTITY_ID3[j]);
        strcpy(CAMEL_APN_NI[i],TEMP_CAMEL_APN_NI[j]);
        strcpy(CAMEL_APN_OI[i],TEMP_CAMEL_APN_OI[j]);
        strcpy(A_USERID[i],TEMP_A_USERID[j]);
        strcpy(B_USERID[i],TEMP_B_USERID[j]);
	strcpy(EVENT_REFERENCE[i],TEMP_EVENT_REFERENCE[j]);
	NETWORK_ELEMENT_TYPE1[i]= TEMP_NETWORK_ELEMENT_TYPE1[j];
        NETWORK_ELEMENT_TYPE2[i]= TEMP_NETWORK_ELEMENT_TYPE2[j];
	strcpy(NETWORK_ELEMENT_ID1[i],TEMP_NETWORK_ELEMENT_ID1[j]);
        strcpy(NETWORK_ELEMENT_ID2[i],TEMP_NETWORK_ELEMENT_ID2[j]);
	SGSN_RECORDING_ENTITY_TYPE1[i] = TEMP_SGSN_RECORDING_ENTITY_TYPE1[j];
        SGSN_RECORDING_ENTITY_TYPE2[i] = TEMP_SGSN_RECORDING_ENTITY_TYPE2[j];
       /* Added below fields by Imam as per the ghana specific tapin while implementing the LTE */
        strcpy(CHARGE_TYPE1[i],TEMP_CHARGE_TYPE1[j]);
        CHARGEABLE_UNITS1[i]            = TEMP_CHARGEABLE_UNITS1[j];
        CHARGED_UNITS1[i]               = TEMP_CHARGED_UNITS1[j];
        CHARGE1[i]                      = TEMP_CHARGE1[j];
	
        i++ ;
        gBulkInsertTapCdrs++ ;


        if(gBulkInsertTapCdrs == 4998)
        {
            /* Insert CDRS in bulk */
            SetError = BulkInsertCDR(gBulkInsertTapCdrs);
            if(SetError == -1)
            {
                TRACEENTRY(1,"%s","BatchBulkInsert : All Transactions would be rolled back");
                LogError();
                return -1;
            }

            /* Initialise the BulkCDRIndex */
            i = 0;
            gBulkInsertTapCdrs = 0;

            /* Reset the BulkCDR Array */
            InitialiseBulkCDR();
        }

   }
   
   gBulkInsertTapCdrs = i;
   return 0 ;


}

void InitialiseCDR()
{
   int i=0;

        strcpy(BCT.FILE_TRANSFER_DIRECTION,"I");

        INIT_STR(BCT.HPLMN_CODE);
        strcpy(BCT.HPLMN_CODE,BCI.Recipient);

        INIT_STR(BCT.VPLMN_CODE);
        strcpy(BCT.VPLMN_CODE,BCI.Sender);

        INIT_STR(BCT.PARTNER_CODE);
        strcpy(BCT.PARTNER_CODE,FileSummary.PARTNER_CODE);

        INIT_STR(BCT.FILE_TYPE_INDICATOR);
        strcpy(BCT.FILE_TYPE_INDICATOR,BCI.FileTypeIndicator);

        BCT.FILE_SEQUENCE_NUMBER       = 0;
        BCT.FILE_SEQUENCE_NUMBER       = BCI.FileSequenceNumber;

        BCT.CALL_SEQUENCE              = 0;
        INIT_STR(BCT.CALLS_TYPE_INDICATOR);
        BCT.CALL_TYPE                  = 0;
        INIT_STR(BCT.SERVICE_CODE);
        BCT.IMSI                       = 0;
        INIT_STR(BCT.MSISDN);
        BCT.RAPFILE_SEQUENCE_NUMBER    = 0;

        INIT_STR(BCT.CALLED_CALLING_NUMBER);
        INIT_STR(BCT.DIALLED_DIGITS);
        INIT_STR(BCT.CALLED_PLACE);
        INIT_STR(BCT.CALLED_REGION);
        BCT.CLIR_INDICATOR             = 0;
        INIT_STR(BCT.DESTINATION_NETWORK);
        INIT_STR(BCT.CALL_DATE);
        INIT_STR(BCT.CHARGING_TIME_STAMP);
        BCT.UTC_OFFSET_CODE = 0;
        BCT.CALL_DURATION              = 0;
        INIT_STR(BCT.SIM_TOOLKIT_INDICATOR);

        BCT.RECORDING_ENTITY_CODE      = 0;
        BCT.RECORDING_ENTITY_TYPE      = 0;
        INIT_STR(BCT.RECORDING_ENTITY_ID);
        INIT_STR(BCT.CALL_REFERENCE);
        BCT.LOCATION_AREA              = 0;
        BCT.CELLID                     = 0;
        INIT_STR(BCT.SERVING_NETWORK);

        INIT_STR(BCT.IMEI);
        INIT_STR(BCT.BASIC_SERVICE_TYPE);
        INIT_STR(BCT.BASIC_SERVICE_CODE);
        BCT.TRANSPARENCY_INDICATOR          = 0;
        BCT.FNUR                            = 0;
        BCT.USER_PROTOCOL_INDICATOR         = 0;
        INIT_STR(BCT.GUARANTEED_BIT_RATE);
        INIT_STR(BCT.MAXIMUM_BIT_RATE);
        INIT_STR(BCT.HSCSD_INDICATOR);

        INIT_STR(BCT.SUPPLIMENTARY_SERVICE_CODE);
        BCT.SUPPLIMENTARY_ACTION_CODE       = 0;
        INIT_STR(BCT.SUPPLIMENTARY_SERVICE_PARAMS);
        INIT_STR(BCT.THIRD_PARTY_NUMBER);
        BCT.THIRD_PARTY_CLIR_INDICATOR      = 0;

        BCT.CAMEL_USED_FLAG                 = 0;
        BCT.CAMEL_SERVICE_LEVEL             = 0;
        BCT.CAMEL_SERVICE_KEY               = 0;
        BCT.CAMEL_DEFAULT_CALL_HANDLING     = 0;
        BCT.CAMEL_EXCHANGE_RATE_CODE        = 0;
        BCT.HOME_CAMEL_EXCHANGE_RATE        = 0;
        BCT.CAMEL_INVOCATION_FEE            = 0;
        BCT.CAMEL_DISCOUNT_CODE             = 0;
        BCT.CAMEL_DISCOUNT                  = 0;
        BCT.CAMEL_DISCOUNTABLE_AMOUNT       = 0;
        BCT.CAMEL_TAX_INFORMATION_COUNT     = 0;
        BCT.CAMEL_TAX_CODE                  = 0;
        BCT.CAMEL_TAX_VALUE                 = 0;
        BCT.CAMEL_TAXABLE_AMOUNT            = 0;
        INIT_STR(BCT.CAMEL_DESTINATION_NUMBER);

        BCT.CALL_TYPE_LEVEL1                = 0;
        BCT.CALL_TYPE_LEVEL2                = 0;
        BCT.CALL_TYPE_LEVEL3                = 0;
        BCT.CHARGE_INFORMATION_COUNT        = 0;       /* 1-single, >1 multiple */
        INIT_STR(BCT.CHARGED_ITEM);		       /* to be considered only when single charge information */
        INIT_STR(BCT.CHARGE_TYPE);                     /* always indicates 00 - total charge */
        BCT.CHARGEABLE_UNITS                = 0;       /* always indicates for total charge */
        BCT.CHARGED_UNITS                   = 0;
        BCT.CHARGE                          = 0;       /* always indicates total charge */
	
	/* Added below 4 fields as per the Ghana specific tapin while implementing the LTE */
	INIT_STR(BCT.CHARGE_TYPE1);                     /* always indicates 00 - total charge */
        BCT.CHARGEABLE_UNITS1               = 0;       /* always indicates for total charge */
        BCT.CHARGED_UNITS1                  = 0;
        BCT.CHARGE1                         = 0;       /* always indicates total charge */

        BCT.TAX_INFORMATION_COUNT           = 0;       /* 1-single, >1 multiple */
        BCT.TAX_CODE                        = 0;
        BCT.TAX_VALUE                       = 0;       /* Always Indicates total Tax */
        BCT.TAXABLE_AMOUNT                  = 0;       /* Always Indicates total taxable Amount */
        BCT.DISCOUNT_INFORMATION_COUNT      = 0;       /* 1-SINLGE, >1 MULTIPLE */
        BCT.DISCOUNT_CODE		    = 0;
        BCT.DISCOUNT                        = 0;       /* Always Indicates total Discount */
        BCT.DISCOUNTABLE_AMT                = 0;       /* Always Indicates total Discountable Amount */
        BCT.HOME_CURNCY_CAMEL_FEE           = 0;
        BCT.HOME_CURNCY_CAMEL_TAX           = 0;
        BCT.HOME_CURNCY_CAMEL_DISCOUNT      = 0;
        BCT.HOME_CURNCY_CHARGE              = 0;
        BCT.HOME_CURNCY_TAX                 = 0;
        BCT.HOME_CURNCY_DISCOUNT            = 0;
        BCT.HOME_CURNCY_SURCHARGE           = 0;
        BCT.HOME_CURNCY_CHARGE_WITH_TAX     = 0;       /* Charge with Tax */
        BCT.HOME_CURNCY_TOTAL_CHARGE        = 0;       /* Charge with Tax and Surcharge */
        BCT.HOME_EXCHANGE_RATE              = 0;
        BCT.TAP_EXCHANGE_RATE_CODE          = 0;
        BCT.TAP_EXCHANGE_RATE               = 0;
        BCT.TAP_EXCHANGE_RATE_DECIMAL       = 0;

        INIT_STR(BCT.NETWORK_ACCESS_IDENTIFER);
        INIT_STR(BCT.PDP_ADDRESS);
        INIT_STR(BCT.APN_NI);
        INIT_STR(BCT.APN_OI);
        BCT.CAUSE_FOR_TERMINATION           = 0;
        INIT_STR(BCT.PARTIAL_TYPE_INDICATOR);
        BCT.CHARGING_ID                     = 0;
        INIT_STR(BCT.SERVING_LOCATION_DESC);
        BCT.DATA_VOLUME_INCOMING            = 0;
        BCT.DATA_VOLUME_OUTGOING            = 0;
        BCT.SGSN_RECORDING_ENTITY_CODE1     = 0;
        INIT_STR(BCT.SGSN_RECORDING_ENTITY_ID1);
        BCT.SGSN_RECORDING_ENTITY_CODE2     = 0;
        INIT_STR(BCT.SGSN_RECORDING_ENTITY_ID2);
        BCT.SGSN_RECORDING_ENTITY_CODE3     = 0;
        INIT_STR(BCT.SGSN_RECORDING_ENTITY_ID3);
        INIT_STR(BCT.CAMEL_APN_NI);
        INIT_STR(BCT.CAMEL_APN_OI);
        INIT_STR(BCT.TAP_TAX_TYPE_RATE) ;
	INIT_STR(BCT.A_USERID);
	INIT_STR(BCT.B_USERID);
	INIT_STR(BCT.EVENT_REFERENCE);
	BCT.NETWORK_ELEMENT_TYPE1                   = 0;
	BCT.NETWORK_ELEMENT_TYPE2                   = 0;
	INIT_STR(BCT.NETWORK_ELEMENT_ID1);
	INIT_STR(BCT.NETWORK_ELEMENT_ID2);
	BCT.SGSN_RECORDING_ENTITY_TYPE1              =0;      
        BCT.SGSN_RECORDING_ENTITY_TYPE2              =0;
        gTariffID = 0 ;

   /* Initialise PM_TAP_CDR_CHARGE_INFO structure */
   for(i=0;i<30;i++)
   {
      CIN[i].FILE_TRANSFER_DIRECTION[0] = '\0';
      CIN[i].HPLMN_CODE[0]              = '\0';
      CIN[i].VPLMN_CODE[0]              = '\0';
      CIN[i].FILE_TYPE_INDICATOR[0]     = '\0';
      CIN[i].FILE_SEQUENCE_NUMBER       = 0;
      CIN[i].CALL_SEQUENCE              = 0;
      CIN[i].CHARGE_INFORMATION         = 0;
      CIN[i].CHARGED_ITEM[0]            = '\0';
      CIN[i].EXCHANGE_RATE_CODE         = 0;
      CIN[i].CALL_TYPE_LEVEL1           = 0;
      CIN[i].CALL_TYPE_LEVEL2           = 0;
      CIN[i].CALL_TYPE_LEVEL3           = 0;
      CIN[i].CHARGE_DETAIL              = 0;
      CIN[i].CHARGE_TYPE[0]             = '\0';
      CIN[i].CHARGE                     = 0;
      CIN[i].CHARGEABLE_UNITS           = 0;
      CIN[i].CHARGED_UNITS              = 0;
      /* Added below 4 fileds as per ghana specific tapin while implementing the LTE */
      CIN[i].CHARGE_TYPE1[0]            = '\0';
      CIN[i].CHARGE1                    = 0;
      CIN[i].CHARGEABLE_UNITS1          = 0;
      CIN[i].CHARGED_UNITS1             = 0;
   }

   /* Initialis PM_TAP_CDR_TAX_INFO structure */
   for(i=0;i<30;i++)
   {   
      TIN[i].FILE_TRANSFER_DIRECTION[0] = '\0';
      TIN[i].HPLMN_CODE[0]              = '\0';
      TIN[i].VPLMN_CODE[0]              = '\0';
      TIN[i].FILE_TYPE_INDICATOR[0]     = '\0';
      TIN[i].FILE_SEQUENCE_NUMBER       = 0;
      TIN[i].CALL_SEQUENCE              = 0;
      TIN[i].CHARGE_INFORMATION         = 0;
      TIN[i].TAX_INFORMATION            = 0;
      TIN[i].TAX_CODE                   = 0;
      TIN[i].TAX_VALUE                  = 0;
      TIN[i].TAXABLE_AMOUNT             = 0;
   }

   /* Initialis PM_TAP_CDR_DISCOUNT_INFO structure */
   for(i=0;i<30;i++)
   {
      DIN[i].FILE_TRANSFER_DIRECTION[0] = '\0';
      DIN[i].HPLMN_CODE[0]              = '\0';
      DIN[i].VPLMN_CODE[0]              = '\0';
      DIN[i].FILE_TYPE_INDICATOR[0]     = '\0';
      DIN[i].FILE_SEQUENCE_NUMBER       = 0;
      DIN[i].CALL_SEQUENCE              = 0;
      DIN[i].CHARGE_INFORMATION         = 0;
      DIN[i].DISCOUNT_INFORMATION       = 0;
      DIN[i].DISCOUNT_CODE              = 0;
      DIN[i].DISCOUNT                   = 0;
      DIN[i].DISCOUNTABLE_AMT           = 0;
   }

   /* Initialise PM_TAP_CDR_CAMEL_TAX_INFO structure */
   for(i=0;i<30;i++)
   {
      CAM[i].FILE_TRANSFER_DIRECTION[0] = '\0';
      CAM[i].HPLMN_CODE[0]              = '\0';
      CAM[i].VPLMN_CODE[0]              = '\0';
      CAM[i].FILE_TYPE_INDICATOR[0]     = '\0';
      CAM[i].FILE_SEQUENCE_NUMBER       = 0;
      CAM[i].CALL_SEQUENCE              = 0;
      CAM[i].TAX_INFORMATION            = 0;
      CAM[i].TAX_CODE                   = 0;
      CAM[i].TAX_VALUE                  = 0;
      CAM[i].TAXABLE_AMOUNT             = 0;
   }
}


void InitialiseBulkCDR()
{
   int i=0;

   for(i=0;i<gCdrsArrayCount;i++)
   {
        INIT_STR(FILE_TRANSFER_DIRECTION[i]);

        INIT_STR(HPLMN_CODE[i]);

        INIT_STR(VPLMN_CODE[i]);

        INIT_STR(PARTNER_CODE[i]);

        INIT_STR(FILE_TYPE_INDICATOR[i]);

        FILE_SEQUENCE_NUMBER[i]       = 0;

        CALL_SEQUENCE[i]              = 0;
        INIT_STR(CALLS_TYPE_INDICATOR[i]);
        CALL_TYPE[i]                  = 0;
        INIT_STR(SERVICE_CODE[i]);
        IMSI[i]                       = 0;
        INIT_STR(MSISDN[i]);
        RAPFILE_SEQUENCE_NUMBER[i]    = 0;

        INIT_STR(CALLED_CALLING_NUMBER[i]);
        INIT_STR(DIALLED_DIGITS[i]);
        INIT_STR(CALLED_PLACE[i]);
        INIT_STR(CALLED_REGION[i]);
        CLIR_INDICATOR[i]             = 0;
        INIT_STR(DESTINATION_NETWORK[i]);
        INIT_STR(CALL_DATE[i]);
        INIT_STR(UTC_OFFSET_CODE[i]);
        CALL_DURATION[i]              = 0;
        INIT_STR(SIM_TOOLKIT_INDICATOR[i]);

        RECORDING_ENTITY_CODE[i]      = 0;
        RECORDING_ENTITY_TYPE[i]      = 0;
        INIT_STR(RECORDING_ENTITY_ID[i]);
        INIT_STR(CALL_REFERENCE[i]);
        LOCATION_AREA[i]              = 0;
        CELLID[i]                     = 0;
        INIT_STR(SERVING_NETWORK[i]);

        INIT_STR(IMEI[i]);
        INIT_STR(BASIC_SERVICE_TYPE[i]);
        INIT_STR(BASIC_SERVICE_CODE[i]);
        TRANSPARENCY_INDICATOR[i]          = 0;
        FNUR[i]                            = 0;
        USER_PROTOCOL_INDICATOR[i]         = 0;
        INIT_STR(GUARANTEED_BIT_RATE[i]);
        INIT_STR(MAXIMUM_BIT_RATE[i]);
        INIT_STR(HSCSD_INDICATOR[i]);

        INIT_STR(SUPPLIMENTARY_SERVICE_CODE[i]);
        SUPPLIMENTARY_ACTION_CODE[i]       = 0;
        INIT_STR(SUPPLIMENTARY_SERVICE_PARAMS[i]);
        INIT_STR(THIRD_PARTY_NUMBER[i]);
        THIRD_PARTY_CLIR_INDICATOR[i]      = 0;

        CAMEL_USED_FLAG[i]                 = 0;
        CAMEL_SERVICE_LEVEL[i]             = 0;
        CAMEL_SERVICE_KEY[i]               = 0;
        CAMEL_DEFAULT_CALL_HANDLING[i]     = 0;
        CAMEL_EXCHANGE_RATE_CODE[i]        = 0;
        HOME_CAMEL_EXCHANGE_RATE[i]        = 0;
        CAMEL_INVOCATION_FEE[i]            = 0;
        CAMEL_DISCOUNT_CODE[i]             = 0;
        CAMEL_DISCOUNT[i]                  = 0;
        CAMEL_DISCOUNTABLE_AMOUNT[i]       = 0;
        CAMEL_TAX_INFORMATION_COUNT[i]     = 0;
        CAMEL_TAX_CODE[i]                  = 0;
        CAMEL_TAX_VALUE[i]                 = 0;
        CAMEL_TAXABLE_AMOUNT[i]            = 0;
        INIT_STR(CAMEL_DESTINATION_NUMBER[i]);

        CALL_TYPE_LEVEL1[i]                = 0;
        CALL_TYPE_LEVEL2[i]                = 0;
        CALL_TYPE_LEVEL3[i]                = 0;
        CHARGE_INFORMATION_COUNT[i]        = 0;       /* 1-single, >1 multiple */
        INIT_STR(CHARGED_ITEM[i]);                    /* to be considered only when single charge information */
        INIT_STR(CHARGE_TYPE[i]);                     /* always indicates 00 - total charge */
        CHARGEABLE_UNITS[i]                = 0;       /* always indicates for total charge */
        CHARGED_UNITS[i]                   = 0;
        CHARGE[i]                          = 0;       /* always indicates total charge */
   /* Added below 4 fields as per ghana specific while implementing the LTE */
	INIT_STR(CHARGE_TYPE1[i]);                     /* always indicates 00 - total charge */
        CHARGEABLE_UNITS1[i]                = 0;       /* always indicates for total charge */
        CHARGED_UNITS1[i]                   = 0;
        CHARGE1[i]                          = 0;       /* always indicates total charge */

        TAX_INFORMATION_COUNT[i]           = 0;       /* 1-single, >1 multiple */
        TAX_CODE[i]                        = 0;
        TAX_VALUE[i]                       = 0;       /* Always Indicates total Tax */
        TAXABLE_AMOUNT[i]                  = 0;       /* Always Indicates total taxable Amount */
        DISCOUNT_INFORMATION_COUNT[i]      = 0;       /* 1-SINLGE, >1 MULTIPLE */
        DISCOUNT_CODE[i]                   = 0;
        DISCOUNT[i]                        = 0;       /* Always Indicates total Discount */
        DISCOUNTABLE_AMT[i]                = 0;       /* Always Indicates total Discountable Amount */
        HOME_CURNCY_CAMEL_FEE[i]           = 0;
        HOME_CURNCY_CAMEL_TAX[i]           = 0;
        HOME_CURNCY_CAMEL_DISCOUNT[i]      = 0;
        HOME_CURNCY_CHARGE[i]              = 0;
        HOME_CURNCY_TAX[i]                 = 0;
        HOME_CURNCY_DISCOUNT[i]            = 0;
        HOME_CURNCY_SURCHARGE[i]           = 0;
        HOME_CURNCY_CHARGE_WITH_TAX[i]     = 0;       /* Charge with Tax */
        HOME_CURNCY_TOTAL_CHARGE[i]        = 0;       /* Charge with Tax and Surcharge */
        HOME_EXCHANGE_RATE[i]              = 0;
        TAP_EXCHANGE_RATE_CODE[i]          = 0;
        TAP_EXCHANGE_RATE[i]               = 0;
        TAP_EXCHANGE_RATE_DECIMAL[i]       = 0;

        INIT_STR(NETWORK_ACCESS_IDENTIFER[i]);
        INIT_STR(PDP_ADDRESS[i]);
        INIT_STR(APN_NI[i]);
        INIT_STR(APN_OI[i]);
	CAUSE_FOR_TERMINATION[i]           = 0;
	INIT_STR(PARTIAL_TYPE_INDICATOR[i]);
	CHARGING_ID[i]                     = 0;
	INIT_STR(SERVING_LOCATION_DESC[i]);
	DATA_VOLUME_INCOMING[i]            = 0;
	DATA_VOLUME_OUTGOING[i]            = 0;
	SGSN_RECORDING_ENTITY_CODE1[i]     = 0;
	INIT_STR(SGSN_RECORDING_ENTITY_ID1[i]);
	SGSN_RECORDING_ENTITY_CODE2[i]     = 0;
	INIT_STR(SGSN_RECORDING_ENTITY_ID2[i]);
	SGSN_RECORDING_ENTITY_CODE3[i]     = 0;
	INIT_STR(SGSN_RECORDING_ENTITY_ID3[i]);
	INIT_STR(CAMEL_APN_NI[i]);
	INIT_STR(CAMEL_APN_OI[i]);
        INIT_STR(TAP_TAX_TYPE_RATE[i]);

	INIT_STR(A_USERID[i]);
	INIT_STR(B_USERID[i]);
	INIT_STR(EVENT_REFERENCE[i]);
	NETWORK_ELEMENT_TYPE1[i]                    = 0;
	NETWORK_ELEMENT_TYPE2[i]                    = 0;
	INIT_STR(NETWORK_ELEMENT_ID1[i]);
	INIT_STR(NETWORK_ELEMENT_ID2[i]);
	SGSN_RECORDING_ENTITY_TYPE1[i]              =0;      
        SGSN_RECORDING_ENTITY_TYPE2[i]              =0;
   }
}



void InitialiseTEMPBulkCDR()
{
   int i=0;

   for(i=0;i<gCdrsArrayCount;i++)
   {
        INIT_STR(TEMP_FILE_TRANSFER_DIRECTION[i]);

        INIT_STR(TEMP_HPLMN_CODE[i]);

        INIT_STR(TEMP_VPLMN_CODE[i]);

        INIT_STR(TEMP_PARTNER_CODE[i]);

        INIT_STR(TEMP_FILE_TYPE_INDICATOR[i]);

        TEMP_FILE_SEQUENCE_NUMBER[i]       = 0;

        TEMP_CALL_SEQUENCE[i]              = 0;
        INIT_STR(TEMP_CALLS_TYPE_INDICATOR[i]);
        TEMP_CALL_TYPE[i]                  = 0;
        INIT_STR(TEMP_SERVICE_CODE[i]);
        TEMP_IMSI[i]                       = 0;
        INIT_STR(TEMP_MSISDN[i]);
        TEMP_RAPFILE_SEQUENCE_NUMBER[i]    = 0;

        INIT_STR(TEMP_CALLED_CALLING_NUMBER[i]);
        INIT_STR(TEMP_DIALLED_DIGITS[i]);
        INIT_STR(TEMP_CALLED_PLACE[i]);
        INIT_STR(TEMP_CALLED_REGION[i]);
        TEMP_CLIR_INDICATOR[i]             = 0;
        INIT_STR(TEMP_DESTINATION_NETWORK[i]);
        INIT_STR(TEMP_CALL_DATE[i]);
        INIT_STR(TEMP_UTC_OFFSET_CODE[i]);
        TEMP_CALL_DURATION[i]              = 0;
        INIT_STR(TEMP_SIM_TOOLKIT_INDICATOR[i]);

        TEMP_RECORDING_ENTITY_CODE[i]      = 0;
        TEMP_RECORDING_ENTITY_TYPE[i]      = 0;
        INIT_STR(TEMP_RECORDING_ENTITY_ID[i]);
        INIT_STR(TEMP_CALL_REFERENCE[i]);
        TEMP_LOCATION_AREA[i]              = 0;
        TEMP_CELLID[i]                     = 0;
        INIT_STR(TEMP_SERVING_NETWORK[i]);

        INIT_STR(TEMP_IMEI[i]);
        INIT_STR(TEMP_BASIC_SERVICE_TYPE[i]);
        INIT_STR(TEMP_BASIC_SERVICE_CODE[i]);
        TEMP_TRANSPARENCY_INDICATOR[i]          = 0;
        TEMP_FNUR[i]                            = 0;
        TEMP_USER_PROTOCOL_INDICATOR[i]         = 0;
        INIT_STR(TEMP_GUARANTEED_BIT_RATE[i]);
        INIT_STR(TEMP_MAXIMUM_BIT_RATE[i]);
        INIT_STR(TEMP_HSCSD_INDICATOR[i]);

        INIT_STR(TEMP_SUPPLIMENTARY_SERVICE_CODE[i]);
        TEMP_SUPPLIMENTARY_ACTION_CODE[i]       = 0;
        INIT_STR(TEMP_SUPPLIMENTARY_SERVICE_PARAMS[i]);
        INIT_STR(TEMP_THIRD_PARTY_NUMBER[i]);
        TEMP_THIRD_PARTY_CLIR_INDICATOR[i]      = 0;

        TEMP_CAMEL_USED_FLAG[i]                 = 0;
        TEMP_CAMEL_SERVICE_LEVEL[i]             = 0;
        TEMP_CAMEL_SERVICE_KEY[i]               = 0;
        TEMP_CAMEL_DEFAULT_CALL_HANDLING[i]     = 0;
        TEMP_CAMEL_EXCHANGE_RATE_CODE[i]        = 0;
        TEMP_HOME_CAMEL_EXCHANGE_RATE[i]        = 0;
        TEMP_CAMEL_INVOCATION_FEE[i]            = 0;
        TEMP_CAMEL_DISCOUNT_CODE[i]             = 0;
        TEMP_CAMEL_DISCOUNT[i]                  = 0;
        TEMP_CAMEL_DISCOUNTABLE_AMOUNT[i]       = 0;
        TEMP_CAMEL_TAX_INFORMATION_COUNT[i]     = 0;
        TEMP_CAMEL_TAX_CODE[i]                  = 0;
        TEMP_CAMEL_TAX_VALUE[i]                 = 0;
        TEMP_CAMEL_TAXABLE_AMOUNT[i]            = 0;
        INIT_STR(TEMP_CAMEL_DESTINATION_NUMBER[i]);

        TEMP_CALL_TYPE_LEVEL1[i]                = 0;
        TEMP_CALL_TYPE_LEVEL2[i]                = 0;
        TEMP_CALL_TYPE_LEVEL3[i]                = 0;
        TEMP_CHARGE_INFORMATION_COUNT[i]        = 0;       /* 1-single, >1 multiple */
        INIT_STR(TEMP_CHARGED_ITEM[i]);                    /* to be considered only when single charge information */
        INIT_STR(TEMP_CHARGE_TYPE[i]);                     /* always indicates 00 - total charge */
        TEMP_CHARGEABLE_UNITS[i]                = 0;       /* always indicates for total charge */
        TEMP_CHARGED_UNITS[i]                   = 0;
        TEMP_CHARGE[i]                          = 0;       /* always indicates total charge */

	/* Added below fileds as per the ghana specific tapin while implementing the LTE */	
	INIT_STR(TEMP_CHARGE_TYPE1[i]);                     /* always indicates 00 - total charge */
        TEMP_CHARGEABLE_UNITS1[i]                = 0;       /* always indicates for total charge */
        TEMP_CHARGED_UNITS1[i]                   = 0;
        TEMP_CHARGE1[i]                          = 0;       /* always indicates total charge */

        TEMP_TAX_INFORMATION_COUNT[i]           = 0;       /* 1-single, >1 multiple */
        TEMP_TAX_CODE[i]                        = 0;
        TEMP_TAX_VALUE[i]                       = 0;       /* Always Indicates total Tax */
        TEMP_TAXABLE_AMOUNT[i]                  = 0;       /* Always Indicates total taxable Amount */
        TEMP_DISCOUNT_INFORMATION_COUNT[i]      = 0;       /* 1-SINLGE, >1 MULTIPLE */
        TEMP_DISCOUNT_CODE[i]                   = 0;
        TEMP_DISCOUNT[i]                        = 0;       /* Always Indicates total Discount */
        TEMP_DISCOUNTABLE_AMT[i]                = 0;       /* Always Indicates total Discountable Amount */
        TEMP_HOME_CURNCY_CAMEL_FEE[i]           = 0;
        TEMP_HOME_CURNCY_CAMEL_TAX[i]           = 0;
        TEMP_HOME_CURNCY_CAMEL_DISCOUNT[i]      = 0;
        TEMP_HOME_CURNCY_CHARGE[i]              = 0;
        TEMP_HOME_CURNCY_TAX[i]                 = 0;
        TEMP_HOME_CURNCY_DISCOUNT[i]            = 0;
        TEMP_HOME_CURNCY_SURCHARGE[i]           = 0;
        TEMP_HOME_CURNCY_CHARGE_WITH_TAX[i]     = 0;       /* Charge with Tax */
        TEMP_HOME_CURNCY_TOTAL_CHARGE[i]        = 0;       /* Charge with Tax and Surcharge */
        TEMP_HOME_EXCHANGE_RATE[i]              = 0;
        TEMP_TAP_EXCHANGE_RATE_CODE[i]          = 0;
        TEMP_TAP_EXCHANGE_RATE[i]               = 0;
        TEMP_TAP_EXCHANGE_RATE_DECIMAL[i]       = 0;

        INIT_STR(TEMP_NETWORK_ACCESS_IDENTIFER[i]);
        INIT_STR(TEMP_PDP_ADDRESS[i]);
        INIT_STR(TEMP_APN_NI[i]);
        INIT_STR(TEMP_APN_OI[i]);
	TEMP_CAUSE_FOR_TERMINATION[i]           = 0;
	INIT_STR(TEMP_PARTIAL_TYPE_INDICATOR[i]);
	TEMP_CHARGING_ID[i]                     = 0;
	INIT_STR(TEMP_SERVING_LOCATION_DESC[i]);
	TEMP_DATA_VOLUME_INCOMING[i]            = 0;
	TEMP_DATA_VOLUME_OUTGOING[i]            = 0;
	TEMP_SGSN_RECORDING_ENTITY_CODE1[i]     = 0;
	INIT_STR(TEMP_SGSN_RECORDING_ENTITY_ID1[i]);
	TEMP_SGSN_RECORDING_ENTITY_CODE2[i]     = 0;
	INIT_STR(TEMP_SGSN_RECORDING_ENTITY_ID2[i]);
	TEMP_SGSN_RECORDING_ENTITY_CODE3[i]     = 0;
	INIT_STR(TEMP_SGSN_RECORDING_ENTITY_ID3[i]);
	INIT_STR(TEMP_CAMEL_APN_NI[i]);
	INIT_STR(TEMP_CAMEL_APN_OI[i]);
        INIT_STR(TEMP_TAP_TAX_TYPE_RATE[i]);
	INIT_STR(TEMP_A_USERID[i]);
	INIT_STR(TEMP_B_USERID[i]);
	INIT_STR(TEMP_EVENT_REFERENCE[i]);
	TEMP_NETWORK_ELEMENT_TYPE1[i]                    = 0;
	TEMP_NETWORK_ELEMENT_TYPE2[i]                    = 0;
	INIT_STR(TEMP_NETWORK_ELEMENT_ID1[i]);
	INIT_STR(TEMP_NETWORK_ELEMENT_ID2[i]);
	TEMP_SGSN_RECORDING_ENTITY_TYPE1[i]              = 0;
        TEMP_SGSN_RECORDING_ENTITY_TYPE2[i]              = 0;


   }
}


void InitialiseBulkIOTCDR()
{
   int i=0;

   for(i=0;i<4999;i++)
   {
        INIT_STR(IOT_FILE_TRANSFER_DIRECTION[i]) ;
        INIT_STR(IOT_HPLMN_CODE[i])              ;
        INIT_STR(IOT_VPLMN_CODE[i])              ;
        INIT_STR(IOT_PARTNER_CODE[i])            ;
        INIT_STR(IOT_FILE_TYPE_INDICATOR[i])     ;
        IOT_FILE_SEQUENCE_NUMBER[i]           = 0;
        IOT_CALL_SEQUENCE[i]                  = 0;
        IOT_CALL_TYPE[i]                      = 0;
        INIT_STR(IOT_SERVICE_CODE[i])            ;
        IOT_IMSI[i]                           = 0;
        INIT_STR(IOT_MSISDN[i])                  ;
        INIT_STR(IOT_CALLED_CALLING_NUMBER[i])   ;
        INIT_STR(IOT_DIALLED_DIGITS[i])          ;
        INIT_STR(IOT_CALL_DATE[i])               ;
        IOT_CALL_DURATION[i]                  = 0;
        INIT_STR(IOT_BASIC_SERVICE_TYPE[i])      ;
        INIT_STR(IOT_BASIC_SERVICE_CODE[i])      ;
        IOT_CALL_TYPE_LEVEL1[i]               = 0;
        INIT_STR(IOT_CHARGED_ITEM[i])            ;                  
        INIT_STR(IOT_CHARGE_TYPE[i])             ;                   
        IOT_CHARGEABLE_UNITS[i]               = 0;     
        IOT_CHARGED_UNITS[i]                  = 0;
        IOT_CHARGE[i]                         = 0;
        IOT_TAX_INFORMATION_COUNT[i]          = 0;
        IOT_TAX_CODE[i]                       = 0;
        IOT_TAX_VALUE[i]                      = 0;
        IOT_TAXABLE_AMOUNT[i]                 = 0;
        IOT_DISCOUNT_INFORMATION_COUNT[i]     = 0;
        IOT_DISCOUNT_CODE[i]                  = 0;
        IOT_DISCOUNT[i]                       = 0;
        IOT_DISCOUNTABLE_AMT[i]               = 0;
        IOT_TAP_EXCHANGE_RATE[i]              = 0;
        IOT_TAP_EXCHANGE_RATE_DECIMAL[i]      = 0;
        IOT_DATA_VOLUME_INCOMING[i]           = 0;
        IOT_DATA_VOLUME_OUTGOING[i]           = 0;
        IOT_HOME_CURNCY_CHARGE[i]             = 0;
        IOT_HOME_CURNCY_TAX[i]                = 0;
        IOT_HOME_CURNCY_DISCOUNT[i]           = 0;
        IOT_CAMEL_INVOCATION_FEE[i]           = 0;
        CDR_ERROR_FLAG[i]                     = 0;
        INIT_STR(IOT_CHARGE_CONTEXT[i])          ;
        INIT_STR(IOT_TAX_CONTEXT[i])             ;
        INIT_STR(IOT_DISCOUNT_CONTEXT[i])        ;
        IOT_ERROR_NODE[i]                     = 0;
   }

}

void InitialiseErrorBulkCDR()
{
   int i=0;

   for(i=0;i<4999;i++)
   {
      INIT_STR(ER_FILE_TRANSFER_DIRECTION[i])      ;
      INIT_STR(ER_HPLMN_CODE[i])                   ;
      INIT_STR(ER_VPLMN_CODE[i])                   ;
      INIT_STR(ER_PARTNER_CODE[i])                 ;
      INIT_STR(ER_FILE_TYPE_INDICATOR[i])          ;
      ER_FILE_SEQUENCE_NUMBER[i] = 0               ;
      ER_CALL_SEQUENCE[i] = 0                      ;
      ER_ERROR_SEQUENCE[i] = 0                     ;
      INIT_STR(ER_CALLS_TYPE_INDICATOR[i])         ;          
      INIT_STR(ER_MSISDN[i])                       ;                        
      INIT_STR(ER_CALLED_CALLING_NUMBER[i])        ;         
      INIT_STR(ER_DIALLED_DIGITS[i])               ;                
      INIT_STR(ER_DESTINATION_NETWORK[i])          ;           
      INIT_STR(ER_CALL_DATE[i])                    ;                     
      ER_UTC_OFFSET_CODE[i] = 0                    ;               
      INIT_STR(ER_UTC_OFFSET[i])                   ;
      INIT_STR(ER_SIM_TOOLKIT_INDICATOR[i])        ;         
      INIT_STR(ER_RECORDING_ENTITY_ID[i])          ;           
      INIT_STR(ER_CALL_REFERENCE[i])               ;                
      INIT_STR(ER_SERVING_NETWORK[i])              ;               
      INIT_STR(ER_IMEI[i])                         ;                          
      INIT_STR(ER_BASIC_SERVICE_TYPE[i])           ;            
      INIT_STR(ER_BASIC_SERVICE_CODE[i])           ;            
      INIT_STR(ER_GUARANTEED_BIT_RATE[i])          ;           
      INIT_STR(ER_MAXIMUM_BIT_RATE[i])             ;              
      INIT_STR(ER_HSCSD_INDICATOR[i])              ;               
      INIT_STR(ER_SUPPLIMENTARY_SERVICE_CODE[i])   ;    
      INIT_STR(ER_SUPPLIMENTARY_SERVICE_PARAMS[i]) ;  
      INIT_STR(ER_THIRD_PARTY_NUMBER[i])           ;            
      INIT_STR(ER_CAMEL_DESTINATION_NUMBER[i])     ;      
      INIT_STR(ER_CHARGED_ITEM[i])                 ;                  
      INIT_STR(ER_CHARGE_TYPE[i])                  ;                   
      INIT_STR(ER_TAP_TAX_TYPE_RATE[i])            ;             
      INIT_STR(ER_NETWORK_ACCESS_IDENTIFER[i])     ;      
      INIT_STR(ER_PDP_ADDRESS[i])                  ;                   
      INIT_STR(ER_APN_NI[i])                       ;                        
      INIT_STR(ER_APN_OI[i])                       ;                        
      INIT_STR(ER_PARTIAL_TYPE_INDICATOR[i])       ;        
      INIT_STR(ER_SGSN_RECORDING_ENTITY_ID1[i])    ;     
      INIT_STR(ER_SGSN_RECORDING_ENTITY_ID2[i])    ;     
      INIT_STR(ER_SGSN_RECORDING_ENTITY_ID3[i])    ;     
      INIT_STR(ER_CAMEL_APN_NI[i])                 ;                  
      INIT_STR(ER_CAMEL_APN_OI[i])                 ;                  
      INIT_STR(ER_FILE_CREATION_TIME[i])           ;
      INIT_STR(ER_FILE_TRANSFER_TIME[i])           ;
      INIT_STR(ER_FILE_AVAILABLE_TIME[i])          ;
      INIT_STR(ER_CHARGING_TIME_STAMP[i])          ;
      INIT_STR(ER_LOCAL_CURRENCY_CODE[i])          ;
      INIT_STR(ER_TAP_CURRENCY_CODE[i])            ;
      ER_TAP_DECIMAL_PLACES[i] = 0                 ;
      ER_TARIFF_ID[i] = 0                          ;
      INIT_STR(ER_IOT_CHARGE)                      ;
      INIT_STR(ER_IOT_TAX)                         ;
      INIT_STR(ER_IOT_DISCOUNT)                    ;
      ER_ERROR_CODE[i] = 0                         ;
      ER_APPLICATION_TAG[i] = 0                    ;
      INIT_STR(ER_ERROR_TYPE[i])                   ;
      INIT_STR(ER_CONTEXT_NAME[i])                 ;
      INIT_STR(ER_DATA_TYPE_INDICATOR[i])          ;
      INIT_STR(ER_ERROR_FIELD_NAME[i])             ;
      INIT_STR(ER_ERROR_CONTEXT_DETAILS[i])        ;
      INIT_STR(ER_ERROR_MESSAGE[i])                ;
      INIT_STR(ER_ERROR_VALUE[i])                  ;
      ER_ERROR_NODE[i]                        = 0  ;
      INIT_STR(ER_RAP_STATUS[i])                   ;
      ER_CALL_TYPE[i]                         = 0  ;                     
      INIT_STR(ER_SERVICE_CODE[i])                 ;
      ER_IMSI[i]                              = 0  ;                          
      ER_CLIR_INDICATOR[i]                    = 0  ;                
      ER_CALL_DURATION[i]                     = 0  ;                 
      ER_RECORDING_ENTITY_CODE[i]             = 0  ;         
      ER_RECORDING_ENTITY_TYPE[i]             = 0  ;         
      ER_CELLID[i]                            = 0  ;                        
      ER_TRANSPARENCY_INDICATOR[i]            = 0  ;        
      ER_FNUR[i]                              = 0  ;                          
      ER_USER_PROTOCOL_INDICATOR[i]           = 0  ;       
      ER_SUPPLIMENTARY_ACTION_CODE[i]         = 0  ;     
      ER_THIRD_PARTY_CLIR_INDICATOR[i]        = 0  ;    
      ER_CAMEL_USED_FLAG[i]                   = 0  ;               
      ER_CAMEL_SERVICE_LEVEL[i]               = 0  ;           
      ER_CAMEL_SERVICE_KEY[i]                 = 0  ;             
      ER_CAMEL_DEFAULT_CALL_HANDLING[i]       = 0  ;   
      ER_CAMEL_EXCHANGE_RATE_CODE[i]          = 0  ;      
      ER_CAMEL_INVOCATION_FEE[i]              = 0  ;          
      ER_CAMEL_DISCOUNT_CODE[i]               = 0  ;           
      ER_CAMEL_DISCOUNT[i]                    = 0  ;                
      ER_CAMEL_DISCOUNTABLE_AMT[i]            = 0  ;        
      ER_CAMEL_TAX_INFORMATION_COUNT[i]       = 0  ;   
      ER_CAMEL_TAX_CODE[i]                    = 0  ;                
      ER_CAMEL_TAX_VALUE[i]                   = 0  ;               
      ER_CAMEL_TAXABLE_AMOUNT[i]              = 0  ;          
      ER_CALL_TYPE_LEVEL1[i]                  = 0  ;              
      ER_CALL_TYPE_LEVEL2[i]                  = 0  ;              
      ER_CALL_TYPE_LEVEL3[i]                  = 0  ;              
      ER_CHARGE_INFORMATION_COUNT[i]     = 0  ;      
      ER_CHARGEABLE_UNITS[i]             = 0  ;              
      ER_CHARGED_UNITS[i]                = 0  ;                 
      ER_CHARGE[i]                       = 0  ;                        
      ER_TAX_INFORMATION_COUNT[i]             = 0  ;         
      ER_TAX_CODE[i]                          = 0  ;                      
      ER_TAX_VALUE[i]                         = 0  ;                     
      ER_TAXABLE_AMOUNT[i]                    = 0  ;                
      ER_DISCOUNT_INFORMATION_COUNT[i]        = 0  ;    
      ER_DISCOUNT_CODE[i]                     = 0  ;                 
      ER_DISCOUNT[i]                          = 0  ;                      
      ER_DISCOUNTABLE_AMT[i]                  = 0  ;              
      ER_TAP_EXCHANGE_RATE_CODE[i]            = 0  ;        
      ER_TAP_EXCHANGE_RATE_CODE[i]            = 0  ;        
      ER_TAP_EXCHANGE_RATE[i]                 = 0  ;             
      ER_TAP_EXCHANGE_RATE_DECIMAL[i]         = 0  ;     
      ER_CAUSE_FOR_TERMINATION[i]             = 0  ;         
      ER_CHARGING_ID[i]                  = 0  ;                   
      ER_DATA_VOLUME_INCOMING[i]              = 0  ;          
      ER_DATA_VOLUME_OUTGOING[i]              = 0  ;          
      ER_SGSN_RECORDING_ENTITY_CODE1[i]       = 0  ;   
      ER_SGSN_RECORDING_ENTITY_CODE2[i]       = 0  ;   
      ER_SGSN_RECORDING_ENTITY_CODE3[i]       = 0  ;   
      INIT_STR(ER_A_USERID[i])                   ;
      INIT_STR(ER_B_USERID[i])                   ;
      INIT_STR(ER_EVENT_REFERENCE[i])            ;
      ER_NETWORK_ELEMENT_TYPE1[i]            =  0 ;
      ER_NETWORK_ELEMENT_TYPE2[i]            =  0 ;
      INIT_STR(ER_NETWORK_ELEMENT_ID1[i])    ;
      INIT_STR(ER_NETWORK_ELEMENT_ID2[i])    ;
      ER_SGSN_RECORDING_ENTITY_TYPE1[i]      =  0;
      ER_SGSN_RECORDING_ENTITY_TYPE2[i]      =  0;
      INIT_STR(ER_IOT_DATE[i]);
      INIT_STR(ER_IOT_CALCULATION[i]);
      ER_EXP_EXCHANGE_RATE[i]                =  0;
   
   }

}

void  SetTEMPBulkCDR(int i)
{
   int j=0;
   int k=0;

        strcpy(TEMP_FILE_TRANSFER_DIRECTION[i],"I");

        strcpy(TEMP_HPLMN_CODE[i],BCI.Recipient);

        strcpy(TEMP_VPLMN_CODE[i],BCI.Sender);

        strcpy(TEMP_PARTNER_CODE[i],BCT.PARTNER_CODE);

        strcpy(TEMP_FILE_TYPE_INDICATOR[i],BCI.FileTypeIndicator);

        TEMP_FILE_SEQUENCE_NUMBER[i]    = BCI.FileSequenceNumber; 


        TEMP_CALL_SEQUENCE[i]           = BCT.CALL_SEQUENCE;
        strcpy(TEMP_CALLS_TYPE_INDICATOR[i],BCT.CALLS_TYPE_INDICATOR);
        TEMP_CALL_TYPE[i]               = BCT.CALL_TYPE;
        strcpy(TEMP_SERVICE_CODE[i], BCT.SERVICE_CODE) ;
        TEMP_IMSI[i]                    = BCT.IMSI;
        strcpy(TEMP_MSISDN[i],BCT.MSISDN);
        TEMP_RAPFILE_SEQUENCE_NUMBER[i] = BCT.RAPFILE_SEQUENCE_NUMBER;

        strcpy(TEMP_CALLED_CALLING_NUMBER[i],BCT.CALLED_CALLING_NUMBER);
        strcpy(TEMP_DIALLED_DIGITS[i],BCT.DIALLED_DIGITS);
       /* strcpy(TEMP_CALLED_PLACE[i],BCT.CALLED_PLACE);*/
       strncpy(TEMP_CALLED_PLACE[i],BCT.CALLED_PLACE,30);
        strcpy(TEMP_CALLED_REGION[i],BCT.CALLED_REGION);
        TEMP_CLIR_INDICATOR[i]          = BCT.CLIR_INDICATOR;
        strcpy(TEMP_DESTINATION_NETWORK[i],BCT.DESTINATION_NETWORK);
        strcpy(TEMP_CALL_DATE[i],BCT.CALL_DATE);

        /* Get the UTC Offset for the UTC Offset Code */
        for(k=0; k<gUTCOffsetCount; k++)
        {
           if(NI.UtcTimeOffsetInfo[k].UtcTimeOffsetCode == BCT.UTC_OFFSET_CODE)
           {
              strcpy(TEMP_UTC_OFFSET_CODE[i],NI.UtcTimeOffsetInfo[k].UtcTimeOffset); 
              break;
           }
        }

        TEMP_CALL_DURATION[i]           = BCT.CALL_DURATION;
        strcpy(TEMP_SIM_TOOLKIT_INDICATOR[i],BCT.SIM_TOOLKIT_INDICATOR);

        TEMP_RECORDING_ENTITY_CODE[i]   = BCT.RECORDING_ENTITY_CODE;
        TEMP_RECORDING_ENTITY_TYPE[i]   = BCT.RECORDING_ENTITY_TYPE;
	
	strcpy(TEMP_RECORDING_ENTITY_ID[i],BCT.RECORDING_ENTITY_ID);
        strcpy(TEMP_CALL_REFERENCE[i],BCT.CALL_REFERENCE);
        TEMP_LOCATION_AREA[i]           = BCT.LOCATION_AREA;
        TEMP_CELLID[i]                  = BCT.CELLID;
        strcpy(TEMP_SERVING_NETWORK[i],BCT.SERVING_NETWORK);

        strcpy(TEMP_IMEI[i],BCT.IMEI);
        strcpy(TEMP_BASIC_SERVICE_TYPE[i],BCT.BASIC_SERVICE_TYPE);
        strcpy(TEMP_BASIC_SERVICE_CODE[i],BCT.BASIC_SERVICE_CODE);
        TEMP_TRANSPARENCY_INDICATOR[i]       = BCT.TRANSPARENCY_INDICATOR;
        TEMP_FNUR[i]                         = BCT.FNUR;
        TEMP_USER_PROTOCOL_INDICATOR[i]      = BCT.USER_PROTOCOL_INDICATOR;
        strcpy(TEMP_GUARANTEED_BIT_RATE[i],BCT.GUARANTEED_BIT_RATE);
        strcpy(TEMP_MAXIMUM_BIT_RATE[i],BCT.MAXIMUM_BIT_RATE);
        strcpy(TEMP_HSCSD_INDICATOR[i],BCT.HSCSD_INDICATOR);

        /* Added by Chetan to select only 2 digit SS Code */
        sub_str(BCT.SUPPLIMENTARY_SERVICE_CODE,SUPPLIMENTARY_SERVICE_CODE[i],1,2);

/*        strcpy(SUPPLIMENTARY_SERVICE_CODE[i],BCT.SUPPLIMENTARY_SERVICE_CODE);  */

        TEMP_SUPPLIMENTARY_ACTION_CODE[i]    = BCT.SUPPLIMENTARY_ACTION_CODE;
        strcpy(TEMP_SUPPLIMENTARY_SERVICE_PARAMS[i],BCT.SUPPLIMENTARY_SERVICE_PARAMS);
        strcpy(TEMP_THIRD_PARTY_NUMBER[i],BCT.THIRD_PARTY_NUMBER);
        TEMP_THIRD_PARTY_CLIR_INDICATOR[i]   = BCT.THIRD_PARTY_CLIR_INDICATOR;

        TEMP_CAMEL_USED_FLAG[i]              = BCT.CAMEL_USED_FLAG;
        TEMP_CAMEL_SERVICE_LEVEL[i]          = BCT.CAMEL_SERVICE_LEVEL;
        TEMP_CAMEL_SERVICE_KEY[i]            = BCT.CAMEL_SERVICE_KEY;
        TEMP_CAMEL_DEFAULT_CALL_HANDLING[i]  = BCT.CAMEL_DEFAULT_CALL_HANDLING;
        TEMP_CAMEL_EXCHANGE_RATE_CODE[i]     = BCT.CAMEL_EXCHANGE_RATE_CODE;
        TEMP_HOME_CAMEL_EXCHANGE_RATE[i]     = BCT.HOME_CAMEL_EXCHANGE_RATE;
        TEMP_CAMEL_INVOCATION_FEE[i]         = BCT.CAMEL_INVOCATION_FEE;
        TEMP_CAMEL_DISCOUNT_CODE[i]          = BCT.CAMEL_DISCOUNT_CODE;
        TEMP_CAMEL_DISCOUNT[i]               = BCT.CAMEL_DISCOUNT;
        TEMP_CAMEL_DISCOUNTABLE_AMOUNT[i]    = BCT.CAMEL_DISCOUNTABLE_AMOUNT;
        TEMP_CAMEL_TAX_INFORMATION_COUNT[i]  = BCT.CAMEL_TAX_INFORMATION_COUNT;
        TEMP_CAMEL_TAX_CODE[i]               = BCT.CAMEL_TAX_CODE;
        TEMP_CAMEL_TAX_VALUE[i]              = BCT.CAMEL_TAX_VALUE;
        TEMP_CAMEL_TAXABLE_AMOUNT[i]         = BCT.CAMEL_TAXABLE_AMOUNT;
        strcpy(TEMP_CAMEL_DESTINATION_NUMBER[i],BCT.CAMEL_DESTINATION_NUMBER);


        /* Get the Exchange Rate for the Exchange Rate Code */
        for(k=0; k<gExchangeRateCount; k++)
        {
           if(ACC.CurrencyConversionInfo[k].ExchangeRateCode == BCT.TAP_EXCHANGE_RATE_CODE)
           {
              TEMP_TAP_EXCHANGE_RATE[i]          = ACC.CurrencyConversionInfo[k].ExchangeRate;
              TEMP_TAP_EXCHANGE_RATE_DECIMAL[i]  = ACC.CurrencyConversionInfo[k].NumberOfDecimalPlaces;
              break;
           }
        }

        strcpy(TEMP_TAP_TAX_TYPE_RATE[i], BCT.TAP_TAX_TYPE_RATE);
		

        TEMP_CALL_TYPE_LEVEL1[i]             = BCT.CALL_TYPE_LEVEL1;
        TEMP_CALL_TYPE_LEVEL2[i]             = BCT.CALL_TYPE_LEVEL2;
        TEMP_CALL_TYPE_LEVEL3[i]             = BCT.CALL_TYPE_LEVEL3;
        TEMP_CHARGE_INFORMATION_COUNT[i]     = BCT.CHARGE_INFORMATION_COUNT;
        strcpy(TEMP_CHARGED_ITEM[i],BCT.CHARGED_ITEM); 
        strcpy(TEMP_CHARGE_TYPE[i],BCT.CHARGE_TYPE); 
        TEMP_CHARGEABLE_UNITS[i]             = BCT.CHARGEABLE_UNITS;
        TEMP_CHARGED_UNITS[i]                = BCT.CHARGED_UNITS;
        TEMP_CHARGE[i]                       = BCT.CHARGE;

	/* Added below 4 fields as per ghana specific tapin while implementing the LTE*/
	strcpy(TEMP_CHARGE_TYPE1[i],BCT.CHARGE_TYPE1);
        TEMP_CHARGEABLE_UNITS1[i]            = BCT.CHARGEABLE_UNITS1;
        TEMP_CHARGED_UNITS1[i]               = BCT.CHARGED_UNITS1;
        TEMP_CHARGE1[i]                      = BCT.CHARGE1; 

        TEMP_TAX_INFORMATION_COUNT[i]        = BCT.TAX_INFORMATION_COUNT;
        TEMP_TAX_CODE[i]                     = BCT.TAX_CODE;
        TEMP_TAX_VALUE[i]                    = BCT.TAX_VALUE;
        TEMP_TAXABLE_AMOUNT[i]               = BCT.TAXABLE_AMOUNT;
        TEMP_DISCOUNT_INFORMATION_COUNT[i]   = BCT.DISCOUNT_INFORMATION_COUNT; 
        TEMP_DISCOUNT_CODE[i]                = BCT.DISCOUNT_CODE;
        TEMP_DISCOUNT[i]                     = BCT.DISCOUNT;
        TEMP_DISCOUNTABLE_AMT[i]             = BCT.DISCOUNTABLE_AMT;
        TEMP_HOME_CURNCY_CAMEL_FEE[i]        = BCT.HOME_CURNCY_CAMEL_FEE;
        TEMP_HOME_CURNCY_CAMEL_TAX[i]        = BCT.HOME_CURNCY_CAMEL_TAX;
        TEMP_HOME_CURNCY_CAMEL_DISCOUNT[i]   = BCT.HOME_CURNCY_CAMEL_DISCOUNT;
        TEMP_HOME_CURNCY_CHARGE[i]           = BCT.HOME_CURNCY_CHARGE;
        TEMP_HOME_CURNCY_TAX[i]              = BCT.HOME_CURNCY_TAX;
        TEMP_HOME_CURNCY_DISCOUNT[i]         = BCT.HOME_CURNCY_DISCOUNT;
        TEMP_HOME_CURNCY_SURCHARGE[i]        = BCT.HOME_CURNCY_SURCHARGE;
        TEMP_HOME_CURNCY_CHARGE_WITH_TAX[i]  = BCT.HOME_CURNCY_CHARGE_WITH_TAX;
        TEMP_HOME_CURNCY_TOTAL_CHARGE[i]     = BCT.HOME_CURNCY_TOTAL_CHARGE;
        TEMP_HOME_EXCHANGE_RATE[i]           = BCT.HOME_EXCHANGE_RATE;
        TEMP_TAP_EXCHANGE_RATE_CODE[i]       = BCT.TAP_EXCHANGE_RATE_CODE;
      
	strcpy(TEMP_NETWORK_ACCESS_IDENTIFER[i],BCT.NETWORK_ACCESS_IDENTIFER);
        strcpy(TEMP_PDP_ADDRESS[i],BCT.PDP_ADDRESS);
        strcpy(TEMP_APN_NI[i],BCT.APN_NI);
        strcpy(TEMP_APN_OI[i],BCT.APN_OI);
        TEMP_CAUSE_FOR_TERMINATION[i]        = BCT.CAUSE_FOR_TERMINATION;
        strcpy(TEMP_PARTIAL_TYPE_INDICATOR[i],BCT.PARTIAL_TYPE_INDICATOR);
        TEMP_CHARGING_ID[i]                  = BCT.CHARGING_ID;
        strcpy(TEMP_SERVING_LOCATION_DESC[i],BCT.SERVING_LOCATION_DESC);
        TEMP_DATA_VOLUME_INCOMING[i]         = BCT.DATA_VOLUME_INCOMING;
        TEMP_DATA_VOLUME_OUTGOING[i]         = BCT.DATA_VOLUME_OUTGOING;
        TEMP_SGSN_RECORDING_ENTITY_CODE1[i]  = BCT.SGSN_RECORDING_ENTITY_CODE1;
        strcpy(TEMP_SGSN_RECORDING_ENTITY_ID1[i],BCT.SGSN_RECORDING_ENTITY_ID1);
        TEMP_SGSN_RECORDING_ENTITY_CODE2[i]  = BCT.SGSN_RECORDING_ENTITY_CODE2;
        strcpy(TEMP_SGSN_RECORDING_ENTITY_ID2[i],BCT.SGSN_RECORDING_ENTITY_ID2);
        TEMP_SGSN_RECORDING_ENTITY_CODE3[i]  = BCT.SGSN_RECORDING_ENTITY_CODE3;
        strcpy(TEMP_SGSN_RECORDING_ENTITY_ID3[i],BCT.SGSN_RECORDING_ENTITY_ID3);
        strcpy(TEMP_CAMEL_APN_NI[i],BCT.CAMEL_APN_NI);
        strcpy(TEMP_CAMEL_APN_OI[i],BCT.CAMEL_APN_OI);
        strcpy(TEMP_A_USERID[i],BCT.A_USERID); 
	strcpy(TEMP_B_USERID[i],BCT.B_USERID); 
	strcpy(TEMP_EVENT_REFERENCE[i],BCT.EVENT_REFERENCE);    
	TEMP_NETWORK_ELEMENT_TYPE1[i] = BCT.NETWORK_ELEMENT_TYPE1;
        TEMP_NETWORK_ELEMENT_TYPE2[i] = BCT.NETWORK_ELEMENT_TYPE2;
	strcpy(TEMP_NETWORK_ELEMENT_ID1[i],BCT.NETWORK_ELEMENT_ID1);
        strcpy(TEMP_NETWORK_ELEMENT_ID2[i],BCT.NETWORK_ELEMENT_ID2);
	TEMP_SGSN_RECORDING_ENTITY_TYPE1[i]=BCT.SGSN_RECORDING_ENTITY_TYPE1;
        TEMP_SGSN_RECORDING_ENTITY_TYPE2[i]=BCT.SGSN_RECORDING_ENTITY_TYPE2;


}


void  SetIOTBulkCDR(int i)
{ 
   int j=0;
   int k=0;

        strcpy(IOT_FILE_TRANSFER_DIRECTION[i],"I");
        strcpy(IOT_HPLMN_CODE[i],BCI.Recipient);
        strcpy(IOT_VPLMN_CODE[i],BCI.Sender);
        strcpy(IOT_PARTNER_CODE[i],BCT.PARTNER_CODE);
        strcpy(IOT_FILE_TYPE_INDICATOR[i],BCI.FileTypeIndicator);
        IOT_FILE_SEQUENCE_NUMBER[i]    = BCI.FileSequenceNumber;
        IOT_CALL_SEQUENCE[i]           = BCT.CALL_SEQUENCE;
        IOT_CALL_TYPE[i]               = BCT.CALL_TYPE;
        strcpy(IOT_SERVICE_CODE[i], BCT.SERVICE_CODE) ;
        IOT_IMSI[i]                    = BCT.IMSI;
        strcpy(IOT_MSISDN[i],BCT.MSISDN);
        strcpy(IOT_CALLED_CALLING_NUMBER[i],BCT.CALLED_CALLING_NUMBER);
        strcpy(IOT_DIALLED_DIGITS[i],BCT.DIALLED_DIGITS);
        strcpy(IOT_CALL_DATE[i],BCT.CALL_DATE);
        IOT_CALL_DURATION[i]           = BCT.CALL_DURATION;
        strcpy(IOT_BASIC_SERVICE_TYPE[i],BCT.BASIC_SERVICE_TYPE);
        strcpy(IOT_BASIC_SERVICE_CODE[i],BCT.BASIC_SERVICE_CODE);
        strcpy(IOT_CHARGED_ITEM[i],BCT.CHARGED_ITEM);
        strcpy(IOT_CHARGE_TYPE[i],BCT.CHARGE_TYPE);
        IOT_CHARGEABLE_UNITS[i]             = BCT.CHARGEABLE_UNITS;
        IOT_CHARGED_UNITS[i]                = BCT.CHARGED_UNITS;
        IOT_CHARGE[i]                       = BCT.CHARGE;
        IOT_TAX_INFORMATION_COUNT[i]        = BCT.TAX_INFORMATION_COUNT;
        IOT_TAX_CODE[i]                     = BCT.TAX_CODE;
        IOT_TAX_VALUE[i]                    = BCT.TAX_VALUE;
        IOT_TAXABLE_AMOUNT[i]               = BCT.TAXABLE_AMOUNT;
        IOT_DISCOUNT_INFORMATION_COUNT[i]   = BCT.DISCOUNT_INFORMATION_COUNT;
        IOT_DISCOUNT_CODE[i]                = BCT.DISCOUNT_CODE;
        IOT_DISCOUNT[i]                     = BCT.DISCOUNT;
        IOT_DISCOUNTABLE_AMT[i]             = BCT.DISCOUNTABLE_AMT;

        /* Get the Exchange Rate for the Exchange Rate Code */
        for(k=0; k<gExchangeRateCount; k++)
        {
	  
           if(ACC.CurrencyConversionInfo[k].ExchangeRateCode == BCT.TAP_EXCHANGE_RATE_CODE)
           {
              IOT_TAP_EXCHANGE_RATE[i]          = ACC.CurrencyConversionInfo[k].ExchangeRate;
              IOT_TAP_EXCHANGE_RATE_DECIMAL[i]  = ACC.CurrencyConversionInfo[k].NumberOfDecimalPlaces;
              break;
           }
        }

        IOT_CALL_TYPE_LEVEL1[i]             = BCT.CALL_TYPE_LEVEL1;
        IOT_DATA_VOLUME_INCOMING[i]         = BCT.DATA_VOLUME_INCOMING;
        IOT_DATA_VOLUME_OUTGOING[i]         = BCT.DATA_VOLUME_OUTGOING;
        IOT_HOME_CURNCY_CHARGE[i]           = BCT.HOME_CURNCY_CHARGE;
        IOT_HOME_CURNCY_TAX[i]              = BCT.HOME_CURNCY_TAX;
        IOT_HOME_CURNCY_DISCOUNT[i]         = BCT.HOME_CURNCY_DISCOUNT;
        IOT_CAMEL_INVOCATION_FEE[i]         = BCT.CAMEL_INVOCATION_FEE;
        CDR_ERROR_FLAG[i]                   = gCDRErrorFlag ;
        strcpy(IOT_CHARGE_CONTEXT[i],gIOTChargeContext) ;
        strcpy(IOT_TAX_CONTEXT[i],gIOTTaxContext) ;
        strcpy(IOT_DISCOUNT_CONTEXT[i],gIOTDiscountContext) ;
        IOT_ERROR_NODE[i]                      = gErrorNode ;
       strcpy(IOT_A_USERID[i],BCT.A_USERID);
       strcpy(IOT_B_USERID[i],BCT.B_USERID);
       strcpy(IOT_EVENT_REFERENCE[i],BCT.EVENT_REFERENCE);
        strcpy(IOT_DATE[i],gIOTDate);
       strcpy(IOT_CALCULATION[i],gIOTCalculation);
}


int GetRAPPartnerInfo()
{

    char   GenerateFilesFlg[2];
    int    j=0, k=0;
    int    FnReturnValue ;

    INIT_STR(gGenerateFilesFlg);
    INIT_STR(GenerateFilesFlg) ; 
    INIT_STR(gRAPFileName) ;
    INIT_STR(gRAPFilesDir) ;
    INIT_STR(gRAPSuccessDir) ;
    INIT_STR(gMobilePrfx);
    INIT_STR(gLocalCurrencyCode);
    INIT_STR(gTapoutCurrencyCode);

    /* Check if the VPLMN Code in the file is available in the system for TAPIN entry */

    j=0;
    for(j=0;j<gPartnerCount;j++)
    {
        ptPartners2 = (ptPartners1 + j);
        if(strcmp(BCI.Sender,ptPartners2->PARTNER_SHORT_CODE)==0)
        {
            strcpy(FileSummary.PARTNER_CODE,ptPartners2->PARTNER_CODE);
            break;
        }
    }

    /* Set the FileTypeIndicator */
    if(gTapFileName[0] == 'C')
    {
        strcpy(BCI.FileTypeIndicator,"C");
    }
    else if (gTapFileName[0] == 'T')
    {
       strcpy(BCI.FileTypeIndicator,"T");

    }

    strcpy(GenerateFilesFlg,"N") ;

    /* Check if the VPLMN Code in the file is available in the system for RAPOUT entry */
   
/*   printf("Rap count %d\n",gRAPPartnerCount);
   printf("Partner short code %s\n",ptRAPPartners2->PARTNER_SHORT_CODE);
   printf("Sender %s\n",BCI.Sender);
   printf("File Indicator %s\n",BCI.FileTypeIndicator);
   printf("Data type %s\n",ptRAPPartners2->DATA_TYPE); */

    k=0;
    for(k=0;k<gRAPPartnerCount;k++)
    {
         ptRAPPartners2 = (ptRAPPartners1 + k);
      if((strcmp(BCI.Sender,ptRAPPartners2->PARTNER_SHORT_CODE)==0) && (strcmp(BCI.FileTypeIndicator,ptRAPPartners2->DATA_TYPE) == 0))
         {
            strcpy(RAPFileSummary.PARTNER_CODE,ptRAPPartners2->PARTNER_CODE);
            strcpy(GenerateFilesFlg,ptRAPPartners2->GENERATE_FILES_FLG) ;
            break;
         }
    }
     
    if(strcmp(GenerateFilesFlg,"N")==0)
    {
         TRACEENTRY(1,"%s","RAP File will not be generated for this Roaming Partner"); 
    }
    else
    {
        gRapFileSequenceNumber = 0;

        /* EXEC SQL SELECT FILE_SEQUENCE_NUMBER,MOBL_PRFX_V,LOCAL_CURRENCY_CODE,NVL(TAPOUT_CURRENCY_CODE,' ')
                   INTO :gRapFileSequenceNumber,
                        :gMobilePrfx  ,
			:gLocalCurrencyCode,
			:gTapoutCurrencyCode
                   FROM PM_PARTNER A, PM_ROAM_PARTNER_FILE_INFO B, PM_ROAM_PARTNER_ADDN_INFO C
                   WHERE A.PARTNER_CODE       = B.PARTNER_CODE
                    AND A.PARTNER_CODE       = C.PARTNER_CODE
                    AND B.DATA_TYPE          = :BCI.FileTypeIndicator
                    AND A.PARTNER_CODE       = :RAPFileSummary.PARTNER_CODE 
                    AND B.GENERATE_FILES_FLG = 'Y'
                    AND B.PROCESS_ID         = :gRAPProcessId; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 12;
        sqlstm.arrsiz = 15;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "select FILE_SEQUENCE_NUMBER ,MOBL_PRFX_V ,LOCAL_CURRE\
NCY_CODE ,NVL(TAPOUT_CURRENCY_CODE,' ') into :b0,:b1,:b2,:b3  from PM_PARTNER \
A ,PM_ROAM_PARTNER_FILE_INFO B ,PM_ROAM_PARTNER_ADDN_INFO C where (((((A.PARTN\
ER_CODE=B.PARTNER_CODE and A.PARTNER_CODE=C.PARTNER_CODE) and B.DATA_TYPE=:b4)\
 and A.PARTNER_CODE=:b5) and B.GENERATE_FILES_FLG='Y') and B.PROCESS_ID=:b6)";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )838;
        sqlstm.selerr = (unsigned short)1;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (         void  *)&gRapFileSequenceNumber;
        sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         void  *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned int  )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (         void  *)gMobilePrfx;
        sqlstm.sqhstl[1] = (unsigned int  )7;
        sqlstm.sqhsts[1] = (         int  )0;
        sqlstm.sqindv[1] = (         void  *)0;
        sqlstm.sqinds[1] = (         int  )0;
        sqlstm.sqharm[1] = (unsigned int  )0;
        sqlstm.sqadto[1] = (unsigned short )0;
        sqlstm.sqtdso[1] = (unsigned short )0;
        sqlstm.sqhstv[2] = (         void  *)gLocalCurrencyCode;
        sqlstm.sqhstl[2] = (unsigned int  )4;
        sqlstm.sqhsts[2] = (         int  )0;
        sqlstm.sqindv[2] = (         void  *)0;
        sqlstm.sqinds[2] = (         int  )0;
        sqlstm.sqharm[2] = (unsigned int  )0;
        sqlstm.sqadto[2] = (unsigned short )0;
        sqlstm.sqtdso[2] = (unsigned short )0;
        sqlstm.sqhstv[3] = (         void  *)gTapoutCurrencyCode;
        sqlstm.sqhstl[3] = (unsigned int  )4;
        sqlstm.sqhsts[3] = (         int  )0;
        sqlstm.sqindv[3] = (         void  *)0;
        sqlstm.sqinds[3] = (         int  )0;
        sqlstm.sqharm[3] = (unsigned int  )0;
        sqlstm.sqadto[3] = (unsigned short )0;
        sqlstm.sqtdso[3] = (unsigned short )0;
        sqlstm.sqhstv[4] = (         void  *)(BCI.FileTypeIndicator);
        sqlstm.sqhstl[4] = (unsigned int  )2;
        sqlstm.sqhsts[4] = (         int  )0;
        sqlstm.sqindv[4] = (         void  *)0;
        sqlstm.sqinds[4] = (         int  )0;
        sqlstm.sqharm[4] = (unsigned int  )0;
        sqlstm.sqadto[4] = (unsigned short )0;
        sqlstm.sqtdso[4] = (unsigned short )0;
        sqlstm.sqhstv[5] = (         void  *)(RAPFileSummary.PARTNER_CODE);
        sqlstm.sqhstl[5] = (unsigned int  )4;
        sqlstm.sqhsts[5] = (         int  )0;
        sqlstm.sqindv[5] = (         void  *)0;
        sqlstm.sqinds[5] = (         int  )0;
        sqlstm.sqharm[5] = (unsigned int  )0;
        sqlstm.sqadto[5] = (unsigned short )0;
        sqlstm.sqtdso[5] = (unsigned short )0;
        sqlstm.sqhstv[6] = (         void  *)&gRAPProcessId;
        sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
        sqlstm.sqhsts[6] = (         int  )0;
        sqlstm.sqindv[6] = (         void  *)0;
        sqlstm.sqinds[6] = (         int  )0;
        sqlstm.sqharm[6] = (unsigned int  )0;
        sqlstm.sqadto[6] = (unsigned short )0;
        sqlstm.sqtdso[6] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



        /* Check for Error in Execution */
        if(ERRCODE != 0)
        {
           TRACEENTRY(1,"%s","ERROR : Fetching RAP File Sequence Number from PM_ROAM_PARTNER_FILE_INFO table");
           TRACEENTRY(1,"sqlca.sqlcode -%d-",ERRCODE);
           stErrors.ERROR_CODE = sqlca.sqlcode;
           strcpy(stErrors.ERROR_DESC,"Fetching RAP File Sequence Number from PM_ROAM_PARTNER_FILE_INFO table");
           return -1;
        }
    }

   
    strcpy(gGenerateFilesFlg, GenerateFilesFlg);

    if(strcmp(GenerateFilesFlg,"Y")==0)
    {
        sprintf(gRAPFileName,"%1s%1s%5s%5s%05d","R",BCI.FileTypeIndicator,stRoamingPref.HPLMN_CODE,BCI.Sender,gRapFileSequenceNumber);

        if(strcmp(BCI.FileTypeIndicator,"C")==0)
        {
            strcpy(gRAPFilesDir,gRAPChargeFilesDir) ;
            strcpy(gRAPSuccessDir,gRAPChargeSuccessDir) ;
        }
        else
        {
            strcpy(gRAPFilesDir,gRAPTestFilesDir) ;
            strcpy(gRAPSuccessDir,gRAPTestSuccessDir) ;
        }

        FnReturnValue = 0;
        FnReturnValue = CheckRAPDuplicate(gRAPFileName);

        if(FnReturnValue > 0)
        {
            TRACEENTRY(1,"%s","Duplicate RAP File Check : All Transactions would be rolled back");
            /* EXEC SQL ROLLBACK; */ 

{
            struct sqlexd sqlstm;
            sqlstm.sqlvsn = 12;
            sqlstm.arrsiz = 15;
            sqlstm.sqladtp = &sqladt;
            sqlstm.sqltdsp = &sqltds;
            sqlstm.iters = (unsigned int  )1;
            sqlstm.offset = (unsigned int  )881;
            sqlstm.cud = sqlcud0;
            sqlstm.sqlest = (unsigned char  *)&sqlca;
            sqlstm.sqlety = (unsigned short)4352;
            sqlstm.occurs = (unsigned int  )0;
            sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


            LogError();
            return - 1;
        }

    }

    return 0;

}


int  SetBulkErrorDetails(int i, int j, int ErrorNode)
{

        int SetError=0;
        int k=0 ;

        ER_RAP_SEQUENCE_NUMBER[i] = gRapFileSequenceNumber ;

        if(ER_RAP_SEQUENCE_NUMBER[i] == 0)
        {
           TRACEENTRY(1,"%s","Invalid File Sequence Number is mentioned for RAPOUT Process");
           TRACEENTRY(1,"%s","ErrorReturnValue : All Transactions would be rolled back");
           LogError();
           return -1;
        }

        if(strcmp(REI.ERROR_TYPE[j],"FATAL") == 0)
        {
	 
           gFatalErrorCount++ ;
           ER_ERROR_SEQUENCE[i] = gFatalErrorCount ;
           gProcessingCDRNo = 0;
           gSevereErrorCount = 0;
        }
        else if(strcmp(REI.ERROR_TYPE[j],"SEVERE") == 0)
        {
           gSevereErrorCount++ ;
           ER_ERROR_SEQUENCE[i] = gSevereErrorCount ;
        }

        strcpy(ER_FILE_TRANSFER_DIRECTION[i],"O");
        
        strcpy(ER_HPLMN_CODE[i],BCI.Recipient);
        strcpy(ER_VPLMN_CODE[i],BCI.Sender);

        strcpy(ER_PARTNER_CODE[i],RAPFileSummary.PARTNER_CODE);
        strcpy(ER_FILE_TYPE_INDICATOR[i],BCI.FileTypeIndicator);
        ER_FILE_SEQUENCE_NUMBER[i]    = BCI.FileSequenceNumber;
        strcpy(ER_LOCAL_CURRENCY_CODE[i],ACC.LocalCurrency) ;
        strcpy(ER_TAP_CURRENCY_CODE[i],ACC.TapCurrency) ;
        ER_TAP_DECIMAL_PLACES[i] = ACC.TapDecimalPlaces ; 
        ER_EXP_EXCHANGE_RATE[i]  = ExpExchangeRate;
      
        if(strcmp(REI.ERROR_TYPE[j],"SEVERE") == 0)
        {        
            /* CDR Information */ 
            ER_CALL_SEQUENCE[i]     = gProcessingCDRNo;
            ER_CALL_TYPE[i]         = BCT.CALL_TYPE;
            strcpy(ER_SERVICE_CODE[i], BCT.SERVICE_CODE) ;
            ER_IMSI[i]              = BCT.IMSI ;
            strcpy(ER_MSISDN[i], BCT.MSISDN) ;
	    fnRemTrailSpaces(BCT.CALLED_CALLING_NUMBER);
            strcpy(ER_CALLED_CALLING_NUMBER[i],BCT.CALLED_CALLING_NUMBER) ;
	    fnRemTrailSpaces(BCT.DIALLED_DIGITS);
            strcpy(ER_DIALLED_DIGITS[i],BCT.DIALLED_DIGITS); 
	    strcpy(ER_CALL_DATE[i],BCT.CALL_DATE);
            ER_UTC_OFFSET_CODE[i]=BCT.UTC_OFFSET_CODE;

            /* Get the UTC Offset for the UTC Offset Code */
            if((REI.APPLICATION_TAG[j] != 44) && (REI.ERROR_CODE[j] != 30))
            {
                 for(k=0; k<gUTCOffsetCount; k++)
                 {
                    if(NI.UtcTimeOffsetInfo[k].UtcTimeOffsetCode == BCT.UTC_OFFSET_CODE)
                    {
                       strcpy(ER_UTC_OFFSET[i],NI.UtcTimeOffsetInfo[k].UtcTimeOffset);
                       break;
                    }
                 }
            }
   
            ER_CALL_DURATION[i] = BCT.CALL_DURATION;
	    ER_RECORDING_ENTITY_CODE[i] = BCT.RECORDING_ENTITY_CODE;
            ER_RECORDING_ENTITY_TYPE[i] = BCT.RECORDING_ENTITY_TYPE;
            strcpy(ER_RECORDING_ENTITY_ID[i],BCT.RECORDING_ENTITY_ID);
            strcpy(ER_CALL_REFERENCE[i],BCT.CALL_REFERENCE);
            strcpy(ER_IMEI[i],BCT.IMEI);
            strcpy(ER_BASIC_SERVICE_TYPE[i],BCT.BASIC_SERVICE_TYPE);
            strcpy(ER_BASIC_SERVICE_CODE[i],BCT.BASIC_SERVICE_CODE);
            ER_TRANSPARENCY_INDICATOR[i]       = BCT.TRANSPARENCY_INDICATOR;
            ER_FNUR[i]                         = BCT.FNUR;
            ER_USER_PROTOCOL_INDICATOR[i]      = BCT.USER_PROTOCOL_INDICATOR;
            strcpy(ER_GUARANTEED_BIT_RATE[i],BCT.GUARANTEED_BIT_RATE);
            strcpy(ER_MAXIMUM_BIT_RATE[i],BCT.MAXIMUM_BIT_RATE);
            strcpy(ER_HSCSD_INDICATOR[i],BCT.HSCSD_INDICATOR);

            sub_str(BCT.SUPPLIMENTARY_SERVICE_CODE,ER_SUPPLIMENTARY_SERVICE_CODE[i],1,2);

            ER_SUPPLIMENTARY_ACTION_CODE[i]    = BCT.SUPPLIMENTARY_ACTION_CODE;
            strcpy(ER_SUPPLIMENTARY_SERVICE_PARAMS[i],BCT.SUPPLIMENTARY_SERVICE_PARAMS);
            strcpy(ER_THIRD_PARTY_NUMBER[i],BCT.THIRD_PARTY_NUMBER);
            ER_THIRD_PARTY_CLIR_INDICATOR[i]   = BCT.THIRD_PARTY_CLIR_INDICATOR;

            ER_CAMEL_USED_FLAG[i]              = BCT.CAMEL_USED_FLAG;
            ER_CAMEL_SERVICE_LEVEL[i]          = BCT.CAMEL_SERVICE_LEVEL;
            ER_CAMEL_SERVICE_KEY[i]            = BCT.CAMEL_SERVICE_KEY;
            ER_CAMEL_DEFAULT_CALL_HANDLING[i]  = BCT.CAMEL_DEFAULT_CALL_HANDLING;
            ER_CAMEL_EXCHANGE_RATE_CODE[i]     = BCT.CAMEL_EXCHANGE_RATE_CODE;
            ER_CAMEL_INVOCATION_FEE[i]         = BCT.CAMEL_INVOCATION_FEE;
            ER_CAMEL_DISCOUNT_CODE[i]          = BCT.CAMEL_DISCOUNT_CODE;
            ER_CAMEL_DISCOUNT[i]               = BCT.CAMEL_DISCOUNT;
            ER_CAMEL_DISCOUNTABLE_AMT[i]       = BCT.CAMEL_DISCOUNTABLE_AMOUNT;
            ER_CAMEL_TAX_INFORMATION_COUNT[i]  = BCT.CAMEL_TAX_INFORMATION_COUNT;
            ER_CAMEL_TAX_CODE[i]               = BCT.CAMEL_TAX_CODE;
            ER_CAMEL_TAX_VALUE[i]              = BCT.CAMEL_TAX_VALUE;
            ER_CAMEL_TAXABLE_AMOUNT[i]         = BCT.CAMEL_TAXABLE_AMOUNT;
            strcpy(ER_CAMEL_DESTINATION_NUMBER[i],BCT.CAMEL_DESTINATION_NUMBER);


            /* Get the Exchange Rate for the Exchange Rate Code */
            for(k=0; k<gExchangeRateCount; k++)
            {
                if(ACC.CurrencyConversionInfo[k].ExchangeRateCode == BCT.TAP_EXCHANGE_RATE_CODE)
                {
                    ER_TAP_EXCHANGE_RATE[i]          = ACC.CurrencyConversionInfo[k].ExchangeRate;
                    ER_TAP_EXCHANGE_RATE_DECIMAL[i]  = ACC.CurrencyConversionInfo[k].NumberOfDecimalPlaces;
                    break;
                }
            }

            strcpy(ER_TAP_TAX_TYPE_RATE[i], BCT.TAP_TAX_TYPE_RATE);

            ER_CALL_TYPE_LEVEL1[i]             = BCT.CALL_TYPE_LEVEL1;
            ER_CALL_TYPE_LEVEL2[i]             = BCT.CALL_TYPE_LEVEL2;
            ER_CALL_TYPE_LEVEL3[i]             = BCT.CALL_TYPE_LEVEL3;
            ER_CHARGE_INFORMATION_COUNT[i]     = BCT.CHARGE_INFORMATION_COUNT;
            strcpy(ER_CHARGED_ITEM[i],BCT.CHARGED_ITEM);
            strcpy(ER_CHARGE_TYPE[i],BCT.CHARGE_TYPE);
            ER_CHARGEABLE_UNITS[i]             = BCT.CHARGEABLE_UNITS;
            ER_CHARGED_UNITS[i]                = BCT.CHARGED_UNITS;
            ER_CHARGE[i]                       = BCT.CHARGE;
            ER_TAX_INFORMATION_COUNT[i]        = BCT.TAX_INFORMATION_COUNT;
            ER_TAX_CODE[i]                     = BCT.TAX_CODE;
            ER_TAX_VALUE[i]                    = BCT.TAX_VALUE;
            ER_TAXABLE_AMOUNT[i]               = BCT.TAXABLE_AMOUNT;
            ER_DISCOUNT_INFORMATION_COUNT[i]   = BCT.DISCOUNT_INFORMATION_COUNT;
            ER_DISCOUNT_CODE[i]                = BCT.DISCOUNT_CODE;
            ER_DISCOUNT[i]                     = BCT.DISCOUNT;
            ER_DISCOUNTABLE_AMT[i]             = BCT.DISCOUNTABLE_AMT;
            ER_TAP_EXCHANGE_RATE_CODE[i]       = BCT.TAP_EXCHANGE_RATE_CODE;

            strcpy(ER_NETWORK_ACCESS_IDENTIFER[i],BCT.NETWORK_ACCESS_IDENTIFER);
            strcpy(ER_PDP_ADDRESS[i],BCT.PDP_ADDRESS);
            strcpy(ER_APN_NI[i],BCT.APN_NI);
            strcpy(ER_APN_OI[i],BCT.APN_OI);
            ER_CAUSE_FOR_TERMINATION[i]        = BCT.CAUSE_FOR_TERMINATION;
            strcpy(ER_PARTIAL_TYPE_INDICATOR[i],BCT.PARTIAL_TYPE_INDICATOR);
            ER_CHARGING_ID[i]                  = BCT.CHARGING_ID;
            ER_DATA_VOLUME_INCOMING[i]         = BCT.DATA_VOLUME_INCOMING;
            ER_DATA_VOLUME_OUTGOING[i]         = BCT.DATA_VOLUME_OUTGOING;
            ER_SGSN_RECORDING_ENTITY_CODE1[i]  = BCT.SGSN_RECORDING_ENTITY_CODE1;
            strcpy(ER_SGSN_RECORDING_ENTITY_ID1[i],BCT.SGSN_RECORDING_ENTITY_ID1);
            ER_SGSN_RECORDING_ENTITY_CODE2[i]  = BCT.SGSN_RECORDING_ENTITY_CODE2;
            strcpy(ER_SGSN_RECORDING_ENTITY_ID2[i],BCT.SGSN_RECORDING_ENTITY_ID2);
            ER_SGSN_RECORDING_ENTITY_CODE3[i]  = BCT.SGSN_RECORDING_ENTITY_CODE3;
            strcpy(ER_SGSN_RECORDING_ENTITY_ID3[i],BCT.SGSN_RECORDING_ENTITY_ID3);
            strcpy(ER_CAMEL_APN_NI[i],BCT.CAMEL_APN_NI);
            strcpy(ER_CAMEL_APN_OI[i],BCT.CAMEL_APN_OI);
            strcpy(ER_CHARGING_TIME_STAMP[i],BCT.CHARGING_TIME_STAMP) ;
            ER_TARIFF_ID[i]  = gTariffID ;
            ER_IOT_CHARGE[i] = gIOTCharge;
            ER_IOT_TAX[i] = gIOTTax;
            ER_IOT_DISCOUNT[i] = gIOTDiscount;
        }
        strcpy(ER_FILE_CREATION_TIME[i],BCI.FileCreationTimeStamp.LocalTimeStamp);
        strcpy(ER_FILE_TRANSFER_TIME[i],BCI.TransferCutOffTimeStamp.LocalTimeStamp);
        strcpy(ER_FILE_AVAILABLE_TIME[i],BCI.FileAvailableTimeStamp.LocalTimeStamp);

        ER_ERROR_CODE[i]      =  REI.ERROR_CODE[j]                       ;
        ER_APPLICATION_TAG[i] = REI.APPLICATION_TAG[j]                   ;
        strcpy(ER_ERROR_TYPE[i],REI.ERROR_TYPE[j])                       ;

        strcpy(ER_ERROR_CONTEXT_DETAILS[i],REI.ERROR_CONTEXT_DETAILS[j]) ;
        strcpy(ER_CONTEXT_NAME[i],REI.CONTEXT_NAME[j])                   ;
        strcpy(ER_DATA_TYPE_INDICATOR[i],"D")                            ;
        strcpy(ER_ERROR_FIELD_NAME[i],REI.ERROR_FIELD_NAME[j])           ;
        strcpy(ER_ERROR_MESSAGE[i],REI.ERROR_MESSAGE[j])                 ;
        strcpy(ER_ERROR_VALUE[i],REI.ERROR_VALUE[j])                     ;
        ER_ERROR_NODE[i]=ErrorNode                                       ;
        strcpy(ER_RAP_STATUS[i],"Q")                                     ;
	fnRemTrailSpaces(BCT.A_USERID);
	fnRemTrailSpaces(BCT.B_USERID);
	fnRemTrailSpaces(BCT.EVENT_REFERENCE);
        strcpy(ER_A_USERID[i],BCT.A_USERID)                              ;
        strcpy(ER_B_USERID[i],BCT.B_USERID)                              ;
	strcpy(ER_EVENT_REFERENCE[i],BCT.EVENT_REFERENCE)                ;
	ER_NETWORK_ELEMENT_TYPE1[i]=BCT.NETWORK_ELEMENT_TYPE1            ;
        ER_NETWORK_ELEMENT_TYPE2[i]=BCT.NETWORK_ELEMENT_TYPE2            ;
         strcpy(ER_NETWORK_ELEMENT_ID1[i],BCT.NETWORK_ELEMENT_ID1)         ;
        strcpy(ER_NETWORK_ELEMENT_ID2[i],BCT.NETWORK_ELEMENT_ID2)           ;
	ER_SGSN_RECORDING_ENTITY_TYPE1[i]= BCT.SGSN_RECORDING_ENTITY_TYPE1  ; 
	ER_SGSN_RECORDING_ENTITY_TYPE2[i]= BCT.SGSN_RECORDING_ENTITY_TYPE2  ;
	strcpy(ER_IOT_DATE[i],gIOTDate);
	strcpy(ER_IOT_CALCULATION[i],gIOTCalculation);
        


/*        printf("ERROR_CODE:-%d-,APPLICATION_TAG-%d-,ERROR_FIELD_NAME-%s-,ERROR_TYPE-%s-,ERROR_CONTEXT_DETAILS-%s-,ERROR_MESSAGE-%s-,ErrorNode:-%d-\n",REI.ERROR_CODE[j],REI.APPLICATION_TAG[j],REI.ERROR_FIELD_NAME[j],REI.ERROR_TYPE[j],REI.ERROR_CONTEXT_DETAILS[j],REI.ERROR_MESSAGE[j],ErrorNode) ;*/

        /* Increment the CDR Count */
        gBulkErrorDetailsIndex++ ;
       
     

        /* Call BulkInsertErrorDetails only if the count of CDR is equal to CDR array size */
        if((gBulkErrorDetailsIndex == 4998) && (gFatalErrorCount == 0))
        {
            /* Insert Error CDRS in bulk */
            SetError = BulkInsertErrorDetails(gBulkErrorDetailsIndex);
            if(SetError == -1)
            {
               TRACEENTRY(1,"%s","ErrorReturnValue : All Transactions would be rolled back");
               /* EXEC SQL ROLLBACK; */ 

{
               struct sqlexd sqlstm;
               sqlstm.sqlvsn = 12;
               sqlstm.arrsiz = 15;
               sqlstm.sqladtp = &sqladt;
               sqlstm.sqltdsp = &sqltds;
               sqlstm.iters = (unsigned int  )1;
               sqlstm.offset = (unsigned int  )896;
               sqlstm.cud = sqlcud0;
               sqlstm.sqlest = (unsigned char  *)&sqlca;
               sqlstm.sqlety = (unsigned short)4352;
               sqlstm.occurs = (unsigned int  )0;
               sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


               LogError();
               return -1;
            }

            /* Initialise the BulkCDRIndex */
            gBulkErrorDetailsIndex = 0;

            /* Reset the BulkCDR Array */
            InitialiseErrorBulkCDR();
        }
       
       return 0;

}

void fnSetRapDetails(char* ErrorType,int ErrorNode)
{
  int i=1;
        i++;

        /* set_ReturnDetails can be called multiple times for every severe error encountered */
        /* EncodeReturnDetails(BCI.FileSequenceNumber,ErrorType); */


        switch(ErrorNode)
        {
                case TRANSFER_BATCH_ERR:
                {
                        EncodeTransferBatchError(); 
                        break;
                }
                case NOTIFICATION_ERR:
                {
                        EncodeNotification(DIC.a.notification) ;
                        break;
                }
                case BATCH_CONTROL_ERR:
                {
                        EncodeBatchControlInfoError(DIC.a.transferBatch->batchControlInfo); 
                        break;
                }
                case ACC_INFO_ERR:
                {
                        EncodeAccInfoError(DIC.a.transferBatch->accountingInfo); 
                        break;
                }
                case NETWORK_INFO_ERR:
                {
                        EncodeNetworkInfoError(DIC.a.transferBatch->networkInfo); 
                        break;
                }
                case AUDIT_CONTROL_ERR:
                {
                        EncodeAuditControlInfoError(DIC.a.transferBatch->auditControlInfo); 
                        break;
                }
                case MOC_CALL_ERR:
                {
                        EncodeMOC(stMOC1);   
                        break;
                }
                case MTC_CALL_ERR:
                {
                        EncodeMTC(stMTC1); 
                        break;
                }
                case GPRS_CALL_ERR:
                {
                        EncodeGPRS(stGC);  
                        break;
                }
                case SUP_CALL_ERR:
                {
                        EncodeSUP(stSUP1) ;
                        break;
                }

		case MSESS_CALL_ERR:
		{
		     EncodeMSESS(stMSESS);
		     break;
                }
		case MESG_CALL_ERR:
		{
		    EncodeMESG(stMESG);
                    break;
                }
           	 
        }

}


int LoadIOTCDRS()
{

   /* Variables to fetch required number of CDRs from the Table */
   int   rows_to_fetch=0, rows_before=0, rows_this_time=0;
   int j = 0 ;
   long  IOTCDRsCount = 0 ;
   int SetError = 0 ;
   char TempNumtoChar[10] ;

   int ErrorReturnValue = 0;
   int lValidateFlag    = 0;
   int ErrorCount=0;
   int lIOTChargeFlag=0;
   int lIOTTaxFlag = 0;
   int lIOTDiscountFlag = 0;
   int ErrorStructure = 0 ;

   CallEventDetail *pCallEventDetail;


   /* EXEC SQL SELECT COUNT(1)
              INTO :IOTCDRsCount
              FROM PM_TMP_TAP_CDRS; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 15;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select count(1) into :b0  from PM_TMP_TAP_CDRS ";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )911;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&IOTCDRsCount;
   sqlstm.sqhstl[0] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   if(ERRCODE != 0 || IOTCDRsCount ==0)
   {
      TRACEENTRY(1,"%s","Error Fetching Count from PM_TMP_TAP_CDRS table");
      TRACEENTRY(1,"%s -%d-","sqlca.sqlcode",ERRCODE);
      return(-1);
   }


   gIotErrorCDRCount = 0 ;

 
   /* EXEC SQL DECLARE I CURSOR FOR
             SELECT nvl(trim(FILE_TRANSFER_DIRECTION),' ') ,
                    nvl(trim(HPLMN_CODE),' ')              ,
                    nvl(trim(VPLMN_CODE),' ')              ,
                    nvl(trim(PARTNER_CODE),' ')            ,
                    nvl(trim(FILE_TYPE_INDICATOR),' ')     ,
                    nvl(FILE_SEQUENCE_NUMBER,0)            ,
                    nvl(CALL_SEQUENCE,0)                   ,
                    nvl(CALL_TYPE,0)                       ,
                    nvl(trim(SERVICE_CODE),' ')            ,
                    nvl(IMSI,0)                            ,
                    nvl(MSISDN,' ')                        ,
                    nvl(CALLED_CALLING_NUMBER,' ')         ,
                    nvl(DIALLED_DIGITS,' ')                ,
                    to_char(CALL_DATE,'YYYYMMDDHH24MISS')  ,
                    nvl(CALL_DURATION,0)                   ,
                    nvl(BASIC_SERVICE_TYPE,' ')            ,
                    nvl(BASIC_SERVICE_CODE,' ')            ,
                    nvl(CHARGED_ITEM,' ')                  ,
                    nvl(CHARGEABLE_UNITS,0)                ,
                    nvl(CHARGED_UNITS,0)                   ,
                    nvl(CHARGE,0)                          ,
                    nvl(TAX_INFORMATION_COUNT,0)           ,
                    nvl(TAX_CODE,0)                        ,
                    nvl(TAX_VALUE,0)                       ,
                    nvl(TAXABLE_AMOUNT,0)                  ,
                    nvl(DISCOUNT_INFORMATION_COUNT,0)      , 
                    nvl(DISCOUNT_CODE,0)                   ,
                    nvl(DISCOUNT,0)                        ,
                    nvl(DISCOUNTABLE_AMT,0)                ,
                    nvl(TAP_EXCHANGE_RATE,0)               ,
                    nvl(TAP_EXCHANGE_RATE_DECIMAL,0)       ,
                    nvl(DATA_VOLUME_INCOMING,0)            ,
                    nvl(DATA_VOLUME_OUTGOING,0)            ,
                    nvl(HOME_CURNCY_CHARGE,0)              ,
                    nvl(HOME_CURNCY_TAX,0)                 ,
                    nvl(HOME_CURNCY_DISCOUNT,0)            ,
                    nvl(CAMEL_INVOCATION_FEE,0)            ,
                    nvl(CALL_TYPE_LEVEL1,0)                ,
                    nvl(IOT_CHARGE,0)                      ,
                    nvl(IOT_TAX,0)                         ,
                    nvl(IOT_DISCOUNT,0)                    ,
                    nvl(TARIFF_ID,0)                       ,
                    nvl(CDR_ERROR_FLAG,0)                  ,
                    nvl(TRIM(CHARGE_CONTEXT),' ')          ,
                    nvl(TRIM(TAX_CONTEXT),' ')             ,
                    nvl(TRIM(DISCOUNT_CONTEXT),' ')        ,
                    nvl(ERROR_NODE,0)                      ,
		    nvl(TRIM(A_USERID),' ')                ,
		    nvl(TRIM(B_USERID),' ')                ,
		    nvl(TRIM(EVENT_REFERENCE),' ')         ,
		    nvl(to_char(IOT_DATE,'YYYYMMDD'),' '),
		    nvl(TRIM(IOT_CALCULATION),' ')          ,
		    trim(ROWID) 
               FROM PM_TMP_TAP_CDRS                        
              WHERE FILE_TRANSFER_DIRECTION  = 'I'
                AND HPLMN_CODE               = :BCI.Recipient 
                AND VPLMN_CODE               = :BCI.Sender
                AND FILE_TYPE_INDICATOR      = :BCI.FileTypeIndicator
                AND FILE_SEQUENCE_NUMBER     = :BCI.FileSequenceNumber
           ORDER BY CALL_SEQUENCE ; */ 

        

   /* EXEC SQL OPEN I; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 15;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlbuft((void **)0, 
     "select nvl(trim(FILE_TRANSFER_DIRECTION),' ') ,nvl(trim(HPLMN_CODE),' \
') ,nvl(trim(VPLMN_CODE),' ') ,nvl(trim(PARTNER_CODE),' ') ,nvl(trim(FILE_TY\
PE_INDICATOR),' ') ,nvl(FILE_SEQUENCE_NUMBER,0) ,nvl(CALL_SEQUENCE,0) ,nvl(C\
ALL_TYPE,0) ,nvl(trim(SERVICE_CODE),' ') ,nvl(IMSI,0) ,nvl(MSISDN,' ') ,nvl(\
CALLED_CALLING_NUMBER,' ') ,nvl(DIALLED_DIGITS,' ') ,to_char(CALL_DATE,'YYYY\
MMDDHH24MISS') ,nvl(CALL_DURATION,0) ,nvl(BASIC_SERVICE_TYPE,' ') ,nvl(BASIC\
_SERVICE_CODE,' ') ,nvl(CHARGED_ITEM,' ') ,nvl(CHARGEABLE_UNITS,0) ,nvl(CHAR\
GED_UNITS,0) ,nvl(CHARGE,0) ,nvl(TAX_INFORMATION_COUNT,0) ,nvl(TAX_CODE,0) ,\
nvl(TAX_VALUE,0) ,nvl(TAXABLE_AMOUNT,0) ,nvl(DISCOUNT_INFORMATION_COUNT,0) ,\
nvl(DISCOUNT_CODE,0) ,nvl(DISCOUNT,0) ,nvl(DISCOUNTABLE_AMT,0) ,nvl(TAP_EXCH\
ANGE_RATE,0) ,nvl(TAP_EXCHANGE_RATE_DECIMAL,0) ,nvl(DATA_VOLUME_INCOMING,0) \
,nvl(DATA_VOLUME_OUTGOING,0) ,nvl(HOME_CURNCY_CHARGE,0) ,nvl(HOME_CURNCY_TAX\
,0) ,nvl(HOME_CURNCY_DISCOUNT,0) ,nvl(CAMEL_INVOCATION_FEE,0) ,nvl(CALL_TYPE\
_LEVEL1,0) ,nvl(IOT_CHARGE,0) ,nvl(IOT_TAX");
   sqlstm.stmt = sq0046;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )930;
   sqlstm.selerr = (unsigned short)20000;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqcmod = (unsigned int )0;
   sqlstm.sqhstv[0] = (         void  *)(BCI.Recipient);
   sqlstm.sqhstl[0] = (unsigned int  )6;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)(BCI.Sender);
   sqlstm.sqhstl[1] = (unsigned int  )6;
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)(BCI.FileTypeIndicator);
   sqlstm.sqhstl[2] = (unsigned int  )2;
   sqlstm.sqhsts[2] = (         int  )0;
   sqlstm.sqindv[2] = (         void  *)0;
   sqlstm.sqinds[2] = (         int  )0;
   sqlstm.sqharm[2] = (unsigned int  )0;
   sqlstm.sqadto[2] = (unsigned short )0;
   sqlstm.sqtdso[2] = (unsigned short )0;
   sqlstm.sqhstv[3] = (         void  *)&(BCI.FileSequenceNumber);
   sqlstm.sqhstl[3] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[3] = (         int  )0;
   sqlstm.sqindv[3] = (         void  *)0;
   sqlstm.sqinds[3] = (         int  )0;
   sqlstm.sqharm[3] = (unsigned int  )0;
   sqlstm.sqadto[3] = (unsigned short )0;
   sqlstm.sqtdso[3] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   /* EXEC SQL WHENEVER NOT FOUND CONTINUE; */ 

   rows_this_time = 1;
   rows_before    = 0;
   rows_to_fetch  = 1;

  while (rows_this_time == rows_to_fetch)
   {
         InitialiseIOTCDR(); 
         InitialiseCDR() ;

 

         gIOTCharge   =  0;
         gIOTTax      =  0;
         gIOTDiscount =  0;
         gIOTChargeDiff = 0;
	 gIOTTaxDiff = 0;
         gIOTDiscountDif = 0;
         lIOTChargeFlag   =  0;
         lIOTTaxFlag      =  0;
         lIOTDiscountFlag =  0;
       /* strcpy(gIOTDate,' ')  ;
	strcpy(gIOTCalculation,' ') ; */

         /* EXEC SQL FOR :rows_to_fetch  FETCH I INTO :StIOTCdr; */ 

{
         struct sqlexd sqlstm;
         sqlstm.sqlvsn = 12;
         sqlstm.arrsiz = 53;
         sqlstm.sqladtp = &sqladt;
         sqlstm.sqltdsp = &sqltds;
         sqlstm.iters = (unsigned int  )rows_to_fetch;
         sqlstm.offset = (unsigned int  )961;
         sqlstm.selerr = (unsigned short)20000;
         sqlstm.cud = sqlcud0;
         sqlstm.sqlest = (unsigned char  *)&sqlca;
         sqlstm.sqlety = (unsigned short)4352;
         sqlstm.occurs = (unsigned int  )0;
         sqlstm.sqfoff = (           int )0;
         sqlstm.sqfmod = (unsigned int )2;
         sqlstm.sqhstv[0] = (         void  *)StIOTCdr.FILE_TRANSFER_DIRECTION;
         sqlstm.sqhstl[0] = (unsigned int  )2;
         sqlstm.sqhsts[0] = (         int  )2;
         sqlstm.sqindv[0] = (         void  *)0;
         sqlstm.sqinds[0] = (         int  )0;
         sqlstm.sqharm[0] = (unsigned int  )0;
         sqlstm.sqadto[0] = (unsigned short )0;
         sqlstm.sqtdso[0] = (unsigned short )0;
         sqlstm.sqhstv[1] = (         void  *)StIOTCdr.HPLMN_CODE;
         sqlstm.sqhstl[1] = (unsigned int  )6;
         sqlstm.sqhsts[1] = (         int  )6;
         sqlstm.sqindv[1] = (         void  *)0;
         sqlstm.sqinds[1] = (         int  )0;
         sqlstm.sqharm[1] = (unsigned int  )0;
         sqlstm.sqadto[1] = (unsigned short )0;
         sqlstm.sqtdso[1] = (unsigned short )0;
         sqlstm.sqhstv[2] = (         void  *)StIOTCdr.VPLMN_CODE;
         sqlstm.sqhstl[2] = (unsigned int  )6;
         sqlstm.sqhsts[2] = (         int  )6;
         sqlstm.sqindv[2] = (         void  *)0;
         sqlstm.sqinds[2] = (         int  )0;
         sqlstm.sqharm[2] = (unsigned int  )0;
         sqlstm.sqadto[2] = (unsigned short )0;
         sqlstm.sqtdso[2] = (unsigned short )0;
         sqlstm.sqhstv[3] = (         void  *)StIOTCdr.PARTNER_CODE;
         sqlstm.sqhstl[3] = (unsigned int  )4;
         sqlstm.sqhsts[3] = (         int  )4;
         sqlstm.sqindv[3] = (         void  *)0;
         sqlstm.sqinds[3] = (         int  )0;
         sqlstm.sqharm[3] = (unsigned int  )0;
         sqlstm.sqadto[3] = (unsigned short )0;
         sqlstm.sqtdso[3] = (unsigned short )0;
         sqlstm.sqhstv[4] = (         void  *)StIOTCdr.FILE_TYPE_INDICATOR;
         sqlstm.sqhstl[4] = (unsigned int  )2;
         sqlstm.sqhsts[4] = (         int  )2;
         sqlstm.sqindv[4] = (         void  *)0;
         sqlstm.sqinds[4] = (         int  )0;
         sqlstm.sqharm[4] = (unsigned int  )0;
         sqlstm.sqadto[4] = (unsigned short )0;
         sqlstm.sqtdso[4] = (unsigned short )0;
         sqlstm.sqhstv[5] = (         void  *)&StIOTCdr.FILE_SEQUENCE_NUMBER;
         sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[5] = (         int  )sizeof(int);
         sqlstm.sqindv[5] = (         void  *)0;
         sqlstm.sqinds[5] = (         int  )0;
         sqlstm.sqharm[5] = (unsigned int  )0;
         sqlstm.sqadto[5] = (unsigned short )0;
         sqlstm.sqtdso[5] = (unsigned short )0;
         sqlstm.sqhstv[6] = (         void  *)&StIOTCdr.CALL_SEQUENCE;
         sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[6] = (         int  )sizeof(int);
         sqlstm.sqindv[6] = (         void  *)0;
         sqlstm.sqinds[6] = (         int  )0;
         sqlstm.sqharm[6] = (unsigned int  )0;
         sqlstm.sqadto[6] = (unsigned short )0;
         sqlstm.sqtdso[6] = (unsigned short )0;
         sqlstm.sqhstv[7] = (         void  *)&StIOTCdr.CALL_TYPE;
         sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[7] = (         int  )sizeof(int);
         sqlstm.sqindv[7] = (         void  *)0;
         sqlstm.sqinds[7] = (         int  )0;
         sqlstm.sqharm[7] = (unsigned int  )0;
         sqlstm.sqadto[7] = (unsigned short )0;
         sqlstm.sqtdso[7] = (unsigned short )0;
         sqlstm.sqhstv[8] = (         void  *)StIOTCdr.SERVICE_CODE;
         sqlstm.sqhstl[8] = (unsigned int  )4;
         sqlstm.sqhsts[8] = (         int  )4;
         sqlstm.sqindv[8] = (         void  *)0;
         sqlstm.sqinds[8] = (         int  )0;
         sqlstm.sqharm[8] = (unsigned int  )0;
         sqlstm.sqadto[8] = (unsigned short )0;
         sqlstm.sqtdso[8] = (unsigned short )0;
         sqlstm.sqhstv[9] = (         void  *)&StIOTCdr.IMSI;
         sqlstm.sqhstl[9] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[9] = (         int  )sizeof(double);
         sqlstm.sqindv[9] = (         void  *)0;
         sqlstm.sqinds[9] = (         int  )0;
         sqlstm.sqharm[9] = (unsigned int  )0;
         sqlstm.sqadto[9] = (unsigned short )0;
         sqlstm.sqtdso[9] = (unsigned short )0;
         sqlstm.sqhstv[10] = (         void  *)StIOTCdr.MSISDN;
         sqlstm.sqhstl[10] = (unsigned int  )26;
         sqlstm.sqhsts[10] = (         int  )26;
         sqlstm.sqindv[10] = (         void  *)0;
         sqlstm.sqinds[10] = (         int  )0;
         sqlstm.sqharm[10] = (unsigned int  )0;
         sqlstm.sqadto[10] = (unsigned short )0;
         sqlstm.sqtdso[10] = (unsigned short )0;
         sqlstm.sqhstv[11] = (         void  *)StIOTCdr.CALLED_CALLING_NUMBER;
         sqlstm.sqhstl[11] = (unsigned int  )87;
         sqlstm.sqhsts[11] = (         int  )87;
         sqlstm.sqindv[11] = (         void  *)0;
         sqlstm.sqinds[11] = (         int  )0;
         sqlstm.sqharm[11] = (unsigned int  )0;
         sqlstm.sqadto[11] = (unsigned short )0;
         sqlstm.sqtdso[11] = (unsigned short )0;
         sqlstm.sqhstv[12] = (         void  *)StIOTCdr.DIALLED_DIGITS;
         sqlstm.sqhstl[12] = (unsigned int  )87;
         sqlstm.sqhsts[12] = (         int  )87;
         sqlstm.sqindv[12] = (         void  *)0;
         sqlstm.sqinds[12] = (         int  )0;
         sqlstm.sqharm[12] = (unsigned int  )0;
         sqlstm.sqadto[12] = (unsigned short )0;
         sqlstm.sqtdso[12] = (unsigned short )0;
         sqlstm.sqhstv[13] = (         void  *)StIOTCdr.CALL_DATE;
         sqlstm.sqhstl[13] = (unsigned int  )15;
         sqlstm.sqhsts[13] = (         int  )15;
         sqlstm.sqindv[13] = (         void  *)0;
         sqlstm.sqinds[13] = (         int  )0;
         sqlstm.sqharm[13] = (unsigned int  )0;
         sqlstm.sqadto[13] = (unsigned short )0;
         sqlstm.sqtdso[13] = (unsigned short )0;
         sqlstm.sqhstv[14] = (         void  *)&StIOTCdr.CALL_DURATION;
         sqlstm.sqhstl[14] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[14] = (         int  )sizeof(double);
         sqlstm.sqindv[14] = (         void  *)0;
         sqlstm.sqinds[14] = (         int  )0;
         sqlstm.sqharm[14] = (unsigned int  )0;
         sqlstm.sqadto[14] = (unsigned short )0;
         sqlstm.sqtdso[14] = (unsigned short )0;
         sqlstm.sqhstv[15] = (         void  *)StIOTCdr.BASIC_SERVICE_TYPE;
         sqlstm.sqhstl[15] = (unsigned int  )2;
         sqlstm.sqhsts[15] = (         int  )2;
         sqlstm.sqindv[15] = (         void  *)0;
         sqlstm.sqinds[15] = (         int  )0;
         sqlstm.sqharm[15] = (unsigned int  )0;
         sqlstm.sqadto[15] = (unsigned short )0;
         sqlstm.sqtdso[15] = (unsigned short )0;
         sqlstm.sqhstv[16] = (         void  *)StIOTCdr.BASIC_SERVICE_CODE;
         sqlstm.sqhstl[16] = (unsigned int  )4;
         sqlstm.sqhsts[16] = (         int  )4;
         sqlstm.sqindv[16] = (         void  *)0;
         sqlstm.sqinds[16] = (         int  )0;
         sqlstm.sqharm[16] = (unsigned int  )0;
         sqlstm.sqadto[16] = (unsigned short )0;
         sqlstm.sqtdso[16] = (unsigned short )0;
         sqlstm.sqhstv[17] = (         void  *)StIOTCdr.CHARGED_ITEM;
         sqlstm.sqhstl[17] = (unsigned int  )4;
         sqlstm.sqhsts[17] = (         int  )4;
         sqlstm.sqindv[17] = (         void  *)0;
         sqlstm.sqinds[17] = (         int  )0;
         sqlstm.sqharm[17] = (unsigned int  )0;
         sqlstm.sqadto[17] = (unsigned short )0;
         sqlstm.sqtdso[17] = (unsigned short )0;
         sqlstm.sqhstv[18] = (         void  *)&StIOTCdr.CHARGEABLE_UNITS;
         sqlstm.sqhstl[18] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[18] = (         int  )sizeof(double);
         sqlstm.sqindv[18] = (         void  *)0;
         sqlstm.sqinds[18] = (         int  )0;
         sqlstm.sqharm[18] = (unsigned int  )0;
         sqlstm.sqadto[18] = (unsigned short )0;
         sqlstm.sqtdso[18] = (unsigned short )0;
         sqlstm.sqhstv[19] = (         void  *)&StIOTCdr.CHARGED_UNITS;
         sqlstm.sqhstl[19] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[19] = (         int  )sizeof(double);
         sqlstm.sqindv[19] = (         void  *)0;
         sqlstm.sqinds[19] = (         int  )0;
         sqlstm.sqharm[19] = (unsigned int  )0;
         sqlstm.sqadto[19] = (unsigned short )0;
         sqlstm.sqtdso[19] = (unsigned short )0;
         sqlstm.sqhstv[20] = (         void  *)&StIOTCdr.CHARGE;
         sqlstm.sqhstl[20] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[20] = (         int  )sizeof(double);
         sqlstm.sqindv[20] = (         void  *)0;
         sqlstm.sqinds[20] = (         int  )0;
         sqlstm.sqharm[20] = (unsigned int  )0;
         sqlstm.sqadto[20] = (unsigned short )0;
         sqlstm.sqtdso[20] = (unsigned short )0;
         sqlstm.sqhstv[21] = (         void  *)&StIOTCdr.TAX_INFORMATION_COUNT;
         sqlstm.sqhstl[21] = (unsigned int  )sizeof(long);
         sqlstm.sqhsts[21] = (         int  )sizeof(long);
         sqlstm.sqindv[21] = (         void  *)0;
         sqlstm.sqinds[21] = (         int  )0;
         sqlstm.sqharm[21] = (unsigned int  )0;
         sqlstm.sqadto[21] = (unsigned short )0;
         sqlstm.sqtdso[21] = (unsigned short )0;
         sqlstm.sqhstv[22] = (         void  *)&StIOTCdr.TAX_CODE;
         sqlstm.sqhstl[22] = (unsigned int  )sizeof(long);
         sqlstm.sqhsts[22] = (         int  )sizeof(long);
         sqlstm.sqindv[22] = (         void  *)0;
         sqlstm.sqinds[22] = (         int  )0;
         sqlstm.sqharm[22] = (unsigned int  )0;
         sqlstm.sqadto[22] = (unsigned short )0;
         sqlstm.sqtdso[22] = (unsigned short )0;
         sqlstm.sqhstv[23] = (         void  *)&StIOTCdr.TAX_VALUE;
         sqlstm.sqhstl[23] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[23] = (         int  )sizeof(double);
         sqlstm.sqindv[23] = (         void  *)0;
         sqlstm.sqinds[23] = (         int  )0;
         sqlstm.sqharm[23] = (unsigned int  )0;
         sqlstm.sqadto[23] = (unsigned short )0;
         sqlstm.sqtdso[23] = (unsigned short )0;
         sqlstm.sqhstv[24] = (         void  *)&StIOTCdr.TAXABLE_AMOUNT;
         sqlstm.sqhstl[24] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[24] = (         int  )sizeof(double);
         sqlstm.sqindv[24] = (         void  *)0;
         sqlstm.sqinds[24] = (         int  )0;
         sqlstm.sqharm[24] = (unsigned int  )0;
         sqlstm.sqadto[24] = (unsigned short )0;
         sqlstm.sqtdso[24] = (unsigned short )0;
         sqlstm.sqhstv[25] = (         void  *)&StIOTCdr.DISCOUNT_INFORMATION_COUNT;
         sqlstm.sqhstl[25] = (unsigned int  )sizeof(long);
         sqlstm.sqhsts[25] = (         int  )sizeof(long);
         sqlstm.sqindv[25] = (         void  *)0;
         sqlstm.sqinds[25] = (         int  )0;
         sqlstm.sqharm[25] = (unsigned int  )0;
         sqlstm.sqadto[25] = (unsigned short )0;
         sqlstm.sqtdso[25] = (unsigned short )0;
         sqlstm.sqhstv[26] = (         void  *)&StIOTCdr.DISCOUNT_CODE;
         sqlstm.sqhstl[26] = (unsigned int  )sizeof(long);
         sqlstm.sqhsts[26] = (         int  )sizeof(long);
         sqlstm.sqindv[26] = (         void  *)0;
         sqlstm.sqinds[26] = (         int  )0;
         sqlstm.sqharm[26] = (unsigned int  )0;
         sqlstm.sqadto[26] = (unsigned short )0;
         sqlstm.sqtdso[26] = (unsigned short )0;
         sqlstm.sqhstv[27] = (         void  *)&StIOTCdr.DISCOUNT;
         sqlstm.sqhstl[27] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[27] = (         int  )sizeof(double);
         sqlstm.sqindv[27] = (         void  *)0;
         sqlstm.sqinds[27] = (         int  )0;
         sqlstm.sqharm[27] = (unsigned int  )0;
         sqlstm.sqadto[27] = (unsigned short )0;
         sqlstm.sqtdso[27] = (unsigned short )0;
         sqlstm.sqhstv[28] = (         void  *)&StIOTCdr.DISCOUNTABLE_AMT;
         sqlstm.sqhstl[28] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[28] = (         int  )sizeof(double);
         sqlstm.sqindv[28] = (         void  *)0;
         sqlstm.sqinds[28] = (         int  )0;
         sqlstm.sqharm[28] = (unsigned int  )0;
         sqlstm.sqadto[28] = (unsigned short )0;
         sqlstm.sqtdso[28] = (unsigned short )0;
         sqlstm.sqhstv[29] = (         void  *)&StIOTCdr.TAP_EXCHANGE_RATE;
         sqlstm.sqhstl[29] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[29] = (         int  )sizeof(double);
         sqlstm.sqindv[29] = (         void  *)0;
         sqlstm.sqinds[29] = (         int  )0;
         sqlstm.sqharm[29] = (unsigned int  )0;
         sqlstm.sqadto[29] = (unsigned short )0;
         sqlstm.sqtdso[29] = (unsigned short )0;
         sqlstm.sqhstv[30] = (         void  *)&StIOTCdr.TAP_EXCHANGE_RATE_DECIMAL;
         sqlstm.sqhstl[30] = (unsigned int  )sizeof(long);
         sqlstm.sqhsts[30] = (         int  )sizeof(long);
         sqlstm.sqindv[30] = (         void  *)0;
         sqlstm.sqinds[30] = (         int  )0;
         sqlstm.sqharm[30] = (unsigned int  )0;
         sqlstm.sqadto[30] = (unsigned short )0;
         sqlstm.sqtdso[30] = (unsigned short )0;
         sqlstm.sqhstv[31] = (         void  *)&StIOTCdr.DATA_VOLUME_INCOMING;
         sqlstm.sqhstl[31] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[31] = (         int  )sizeof(double);
         sqlstm.sqindv[31] = (         void  *)0;
         sqlstm.sqinds[31] = (         int  )0;
         sqlstm.sqharm[31] = (unsigned int  )0;
         sqlstm.sqadto[31] = (unsigned short )0;
         sqlstm.sqtdso[31] = (unsigned short )0;
         sqlstm.sqhstv[32] = (         void  *)&StIOTCdr.DATA_VOLUME_OUTGOING;
         sqlstm.sqhstl[32] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[32] = (         int  )sizeof(double);
         sqlstm.sqindv[32] = (         void  *)0;
         sqlstm.sqinds[32] = (         int  )0;
         sqlstm.sqharm[32] = (unsigned int  )0;
         sqlstm.sqadto[32] = (unsigned short )0;
         sqlstm.sqtdso[32] = (unsigned short )0;
         sqlstm.sqhstv[33] = (         void  *)&StIOTCdr.HOME_CURNCY_CHARGE;
         sqlstm.sqhstl[33] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[33] = (         int  )sizeof(double);
         sqlstm.sqindv[33] = (         void  *)0;
         sqlstm.sqinds[33] = (         int  )0;
         sqlstm.sqharm[33] = (unsigned int  )0;
         sqlstm.sqadto[33] = (unsigned short )0;
         sqlstm.sqtdso[33] = (unsigned short )0;
         sqlstm.sqhstv[34] = (         void  *)&StIOTCdr.HOME_CURNCY_TAX;
         sqlstm.sqhstl[34] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[34] = (         int  )sizeof(double);
         sqlstm.sqindv[34] = (         void  *)0;
         sqlstm.sqinds[34] = (         int  )0;
         sqlstm.sqharm[34] = (unsigned int  )0;
         sqlstm.sqadto[34] = (unsigned short )0;
         sqlstm.sqtdso[34] = (unsigned short )0;
         sqlstm.sqhstv[35] = (         void  *)&StIOTCdr.HOME_CURNCY_DISCOUNT;
         sqlstm.sqhstl[35] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[35] = (         int  )sizeof(double);
         sqlstm.sqindv[35] = (         void  *)0;
         sqlstm.sqinds[35] = (         int  )0;
         sqlstm.sqharm[35] = (unsigned int  )0;
         sqlstm.sqadto[35] = (unsigned short )0;
         sqlstm.sqtdso[35] = (unsigned short )0;
         sqlstm.sqhstv[36] = (         void  *)&StIOTCdr.CAMEL_INVOCATION_FEE;
         sqlstm.sqhstl[36] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[36] = (         int  )sizeof(double);
         sqlstm.sqindv[36] = (         void  *)0;
         sqlstm.sqinds[36] = (         int  )0;
         sqlstm.sqharm[36] = (unsigned int  )0;
         sqlstm.sqadto[36] = (unsigned short )0;
         sqlstm.sqtdso[36] = (unsigned short )0;
         sqlstm.sqhstv[37] = (         void  *)&StIOTCdr.CALL_TYPE_LEVEL1;
         sqlstm.sqhstl[37] = (unsigned int  )sizeof(long);
         sqlstm.sqhsts[37] = (         int  )sizeof(long);
         sqlstm.sqindv[37] = (         void  *)0;
         sqlstm.sqinds[37] = (         int  )0;
         sqlstm.sqharm[37] = (unsigned int  )0;
         sqlstm.sqadto[37] = (unsigned short )0;
         sqlstm.sqtdso[37] = (unsigned short )0;
         sqlstm.sqhstv[38] = (         void  *)&StIOTCdr.IOT_CHARGE;
         sqlstm.sqhstl[38] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[38] = (         int  )sizeof(double);
         sqlstm.sqindv[38] = (         void  *)0;
         sqlstm.sqinds[38] = (         int  )0;
         sqlstm.sqharm[38] = (unsigned int  )0;
         sqlstm.sqadto[38] = (unsigned short )0;
         sqlstm.sqtdso[38] = (unsigned short )0;
         sqlstm.sqhstv[39] = (         void  *)&StIOTCdr.IOT_TAX;
         sqlstm.sqhstl[39] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[39] = (         int  )sizeof(double);
         sqlstm.sqindv[39] = (         void  *)0;
         sqlstm.sqinds[39] = (         int  )0;
         sqlstm.sqharm[39] = (unsigned int  )0;
         sqlstm.sqadto[39] = (unsigned short )0;
         sqlstm.sqtdso[39] = (unsigned short )0;
         sqlstm.sqhstv[40] = (         void  *)&StIOTCdr.IOT_DISCOUNT;
         sqlstm.sqhstl[40] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[40] = (         int  )sizeof(double);
         sqlstm.sqindv[40] = (         void  *)0;
         sqlstm.sqinds[40] = (         int  )0;
         sqlstm.sqharm[40] = (unsigned int  )0;
         sqlstm.sqadto[40] = (unsigned short )0;
         sqlstm.sqtdso[40] = (unsigned short )0;
         sqlstm.sqhstv[41] = (         void  *)&StIOTCdr.TARIFF_ID;
         sqlstm.sqhstl[41] = (unsigned int  )sizeof(long);
         sqlstm.sqhsts[41] = (         int  )sizeof(long);
         sqlstm.sqindv[41] = (         void  *)0;
         sqlstm.sqinds[41] = (         int  )0;
         sqlstm.sqharm[41] = (unsigned int  )0;
         sqlstm.sqadto[41] = (unsigned short )0;
         sqlstm.sqtdso[41] = (unsigned short )0;
         sqlstm.sqhstv[42] = (         void  *)&StIOTCdr.CDR_ERROR_FLAG;
         sqlstm.sqhstl[42] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[42] = (         int  )sizeof(int);
         sqlstm.sqindv[42] = (         void  *)0;
         sqlstm.sqinds[42] = (         int  )0;
         sqlstm.sqharm[42] = (unsigned int  )0;
         sqlstm.sqadto[42] = (unsigned short )0;
         sqlstm.sqtdso[42] = (unsigned short )0;
         sqlstm.sqhstv[43] = (         void  *)StIOTCdr.CHARGE_CONTEXT;
         sqlstm.sqhstl[43] = (unsigned int  )80;
         sqlstm.sqhsts[43] = (         int  )80;
         sqlstm.sqindv[43] = (         void  *)0;
         sqlstm.sqinds[43] = (         int  )0;
         sqlstm.sqharm[43] = (unsigned int  )0;
         sqlstm.sqadto[43] = (unsigned short )0;
         sqlstm.sqtdso[43] = (unsigned short )0;
         sqlstm.sqhstv[44] = (         void  *)StIOTCdr.TAX_CONTEXT;
         sqlstm.sqhstl[44] = (unsigned int  )80;
         sqlstm.sqhsts[44] = (         int  )80;
         sqlstm.sqindv[44] = (         void  *)0;
         sqlstm.sqinds[44] = (         int  )0;
         sqlstm.sqharm[44] = (unsigned int  )0;
         sqlstm.sqadto[44] = (unsigned short )0;
         sqlstm.sqtdso[44] = (unsigned short )0;
         sqlstm.sqhstv[45] = (         void  *)StIOTCdr.DISCOUNT_CONTEXT;
         sqlstm.sqhstl[45] = (unsigned int  )80;
         sqlstm.sqhsts[45] = (         int  )80;
         sqlstm.sqindv[45] = (         void  *)0;
         sqlstm.sqinds[45] = (         int  )0;
         sqlstm.sqharm[45] = (unsigned int  )0;
         sqlstm.sqadto[45] = (unsigned short )0;
         sqlstm.sqtdso[45] = (unsigned short )0;
         sqlstm.sqhstv[46] = (         void  *)&StIOTCdr.ERROR_NODE;
         sqlstm.sqhstl[46] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[46] = (         int  )sizeof(int);
         sqlstm.sqindv[46] = (         void  *)0;
         sqlstm.sqinds[46] = (         int  )0;
         sqlstm.sqharm[46] = (unsigned int  )0;
         sqlstm.sqadto[46] = (unsigned short )0;
         sqlstm.sqtdso[46] = (unsigned short )0;
         sqlstm.sqhstv[47] = (         void  *)StIOTCdr.A_USERID;
         sqlstm.sqhstl[47] = (unsigned int  )66;
         sqlstm.sqhsts[47] = (         int  )66;
         sqlstm.sqindv[47] = (         void  *)0;
         sqlstm.sqinds[47] = (         int  )0;
         sqlstm.sqharm[47] = (unsigned int  )0;
         sqlstm.sqadto[47] = (unsigned short )0;
         sqlstm.sqtdso[47] = (unsigned short )0;
         sqlstm.sqhstv[48] = (         void  *)StIOTCdr.B_USERID;
         sqlstm.sqhstl[48] = (unsigned int  )66;
         sqlstm.sqhsts[48] = (         int  )66;
         sqlstm.sqindv[48] = (         void  *)0;
         sqlstm.sqinds[48] = (         int  )0;
         sqlstm.sqharm[48] = (unsigned int  )0;
         sqlstm.sqadto[48] = (unsigned short )0;
         sqlstm.sqtdso[48] = (unsigned short )0;
         sqlstm.sqhstv[49] = (         void  *)StIOTCdr.EVENT_REFERENCE;
         sqlstm.sqhstl[49] = (unsigned int  )31;
         sqlstm.sqhsts[49] = (         int  )31;
         sqlstm.sqindv[49] = (         void  *)0;
         sqlstm.sqinds[49] = (         int  )0;
         sqlstm.sqharm[49] = (unsigned int  )0;
         sqlstm.sqadto[49] = (unsigned short )0;
         sqlstm.sqtdso[49] = (unsigned short )0;
         sqlstm.sqhstv[50] = (         void  *)StIOTCdr.IOT_DATE;
         sqlstm.sqhstl[50] = (unsigned int  )15;
         sqlstm.sqhsts[50] = (         int  )15;
         sqlstm.sqindv[50] = (         void  *)0;
         sqlstm.sqinds[50] = (         int  )0;
         sqlstm.sqharm[50] = (unsigned int  )0;
         sqlstm.sqadto[50] = (unsigned short )0;
         sqlstm.sqtdso[50] = (unsigned short )0;
         sqlstm.sqhstv[51] = (         void  *)StIOTCdr.IOT_CALCULATION;
         sqlstm.sqhstl[51] = (unsigned int  )100;
         sqlstm.sqhsts[51] = (         int  )100;
         sqlstm.sqindv[51] = (         void  *)0;
         sqlstm.sqinds[51] = (         int  )0;
         sqlstm.sqharm[51] = (unsigned int  )0;
         sqlstm.sqadto[51] = (unsigned short )0;
         sqlstm.sqtdso[51] = (unsigned short )0;
         sqlstm.sqhstv[52] = (         void  *)StIOTCdr.ROWID;
         sqlstm.sqhstl[52] = (unsigned int  )20;
         sqlstm.sqhsts[52] = (         int  )20;
         sqlstm.sqindv[52] = (         void  *)0;
         sqlstm.sqinds[52] = (         int  )0;
         sqlstm.sqharm[52] = (unsigned int  )0;
         sqlstm.sqadto[52] = (unsigned short )0;
         sqlstm.sqtdso[52] = (unsigned short )0;
         sqlstm.sqphsv = sqlstm.sqhstv;
         sqlstm.sqphsl = sqlstm.sqhstl;
         sqlstm.sqphss = sqlstm.sqhsts;
         sqlstm.sqpind = sqlstm.sqindv;
         sqlstm.sqpins = sqlstm.sqinds;
         sqlstm.sqparm = sqlstm.sqharm;
         sqlstm.sqparc = sqlstm.sqharc;
         sqlstm.sqpadto = sqlstm.sqadto;
         sqlstm.sqptdso = sqlstm.sqtdso;
         sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



          rows_this_time = sqlca.sqlerrd[2] - rows_before;
         rows_before = sqlca.sqlerrd[2];
 
         if(ERRCODE==28)
         {
            TRACEENTRY(1,"%s","The Oracle Session has been killed. The process should be restarted.");
            TRACEENTRY(1,"%s","main::Exiting from the Process .....");
            exit(0);
         }

         if(sqlca.sqlcode == 1403)
         {
            break;
         }

         if((sqlca.sqlcode!= 0) && (sqlca.sqlcode!=1403))
         {
               SetError=-1;
               TRACEENTRY(1,"%s","---------------Cursor Cache Statistics--------------");
               TRACEENTRY(1,"SQLCA.SQLCODE                  :%d",sqlca.sqlcode);
               TRACEENTRY(1,"sqlca.sqlerrd[2]               :%d",sqlca.sqlerrd[2]);
               TRACEENTRY(1,"Max Value of MAXOPENCURSORS    :%d",oraca.orahoc);
               TRACEENTRY(1,"Max Open Cursors Required      :%d",oraca.oramoc);
               TRACEENTRY(1,"Current No. of Open Cursors    :%d",oraca.oracoc);
               TRACEENTRY(1,"No. Of SQL statements executed :%d",oraca.oranex);
               TRACEENTRY(1,"%s","Cannot Proceed with this Operator. Please Rectify the Error (PM_TMP_TAP_CDRS)");
               /* EXEC SQL ROLLBACK; */ 

{
               struct sqlexd sqlstm;
               sqlstm.sqlvsn = 12;
               sqlstm.arrsiz = 53;
               sqlstm.sqladtp = &sqladt;
               sqlstm.sqltdsp = &sqltds;
               sqlstm.iters = (unsigned int  )1;
               sqlstm.offset = (unsigned int  )1188;
               sqlstm.cud = sqlcud0;
               sqlstm.sqlest = (unsigned char  *)&sqlca;
               sqlstm.sqlety = (unsigned short)4352;
               sqlstm.occurs = (unsigned int  )0;
               sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


               break;
         }


              /* Copy the CDRs to TAP Variables */
         strcpy(BCI.Recipient,StIOTCdr.HPLMN_CODE)                  ;
         strcpy(BCI.Sender,StIOTCdr.VPLMN_CODE)                     ;
         strcpy(BCT.PARTNER_CODE,StIOTCdr.PARTNER_CODE)             ;
         strcpy(BCI.FileTypeIndicator,StIOTCdr.FILE_TYPE_INDICATOR) ;
         BCI.FileSequenceNumber = StIOTCdr.FILE_SEQUENCE_NUMBER     ;
         BCT.CALL_SEQUENCE = StIOTCdr.CALL_SEQUENCE                 ;
         BCT.CALL_TYPE = StIOTCdr.CALL_TYPE                         ;
         strcpy(BCT.SERVICE_CODE,StIOTCdr.SERVICE_CODE)             ;
         BCT.IMSI = StIOTCdr.IMSI                                   ;
         strcpy(BCT.MSISDN,StIOTCdr.MSISDN)                         ;
         strcpy(BCT.CALLED_CALLING_NUMBER,StIOTCdr.CALLED_CALLING_NUMBER) ;
         strcpy(BCT.DIALLED_DIGITS,StIOTCdr.DIALLED_DIGITS)         ;
         strcpy(BCT.CALL_DATE,StIOTCdr.CALL_DATE)                   ;
         BCT.CALL_DURATION = StIOTCdr.CALL_DURATION                 ;
         strcpy(BCT.BASIC_SERVICE_TYPE,StIOTCdr.BASIC_SERVICE_TYPE) ;
         strcpy(BCT.BASIC_SERVICE_CODE,StIOTCdr.BASIC_SERVICE_CODE) ;
         strcpy(BCT.CHARGED_ITEM,StIOTCdr.CHARGED_ITEM)             ;
         BCT.CHARGEABLE_UNITS = StIOTCdr.CHARGEABLE_UNITS           ;                 
         BCT.CHARGED_UNITS = StIOTCdr.CHARGED_UNITS                 ;                    
         BCT.CHARGE = StIOTCdr.CHARGE                               ;                           
         BCT.TAX_INFORMATION_COUNT = StIOTCdr.TAX_INFORMATION_COUNT ;            
         BCT.TAX_CODE = StIOTCdr.TAX_CODE                           ;                         
         BCT.TAX_VALUE = StIOTCdr.TAX_VALUE                         ;                        
         BCT.TAXABLE_AMOUNT = StIOTCdr.TAXABLE_AMOUNT               ;                   
         BCT.DISCOUNT_INFORMATION_COUNT = StIOTCdr.DISCOUNT_INFORMATION_COUNT;       
         BCT.DISCOUNT_CODE = StIOTCdr.DISCOUNT_CODE                 ;                    
         BCT.DISCOUNT = StIOTCdr.DISCOUNT                           ;                         
         BCT.DISCOUNTABLE_AMT = StIOTCdr.DISCOUNTABLE_AMT           ;                 
         BCT.HOME_CURNCY_CHARGE = StIOTCdr.HOME_CURNCY_CHARGE       ;
         BCT.HOME_CURNCY_TAX = StIOTCdr.HOME_CURNCY_TAX             ;
         BCT.HOME_CURNCY_DISCOUNT = StIOTCdr.HOME_CURNCY_DISCOUNT   ;
         BCT.CAMEL_INVOCATION_FEE = StIOTCdr.CAMEL_INVOCATION_FEE   ;
         BCT.CALL_TYPE_LEVEL1 = StIOTCdr.CALL_TYPE_LEVEL1           ;
         BCT.DATA_VOLUME_INCOMING = StIOTCdr.DATA_VOLUME_INCOMING   ;
         BCT.DATA_VOLUME_OUTGOING = StIOTCdr.DATA_VOLUME_OUTGOING   ;
         gTariffID = StIOTCdr.TARIFF_ID                             ;

         gIOTCharge   =  StIOTCdr.IOT_CHARGE                        ;
         gIOTTax      =  StIOTCdr.IOT_TAX                           ; 
         gIOTDiscount =  StIOTCdr.IOT_DISCOUNT                      ;
         gProcessingCDRNo = BCT.CALL_SEQUENCE                       ;
	strcpy(gIOTDate,StIOTCdr.IOT_DATE)                          ;
	 strcpy(gIOTCalculation,StIOTCdr.IOT_CALCULATION)           ;
	   fnRemTrailSpaces(gIOTDate);
       fnRemTrailSpaces(gIOTCalculation);

	strcpy( BCT.A_USERID,StIOTCdr.A_USERID);
        strcpy(BCT.B_USERID,StIOTCdr.B_USERID);
        strcpy(BCT.EVENT_REFERENCE,StIOTCdr.EVENT_REFERENCE) ;
	
	/*strcpy(BCT.IOT_DATE,StIOTCdr.IOT_DATE)                ;
	strcpy(BCT.IOT_CALCLUATION,StIOTCdr.IOT_CALCULATION); */


         fnRemTrailSpaces(StIOTCdr.CHARGE_CONTEXT)                  ;
         fnRemTrailSpaces(StIOTCdr.TAX_CONTEXT)                     ;
         fnRemTrailSpaces(StIOTCdr.DISCOUNT_CONTEXT)                ;


 
         /* Do the IOT Comparision */


        /* Added not to report IOT error if the TAP charge is 0 */

       if ((BCT.CHARGE!=0) && ((strcmp(BCT.SERVICE_CODE,"000")!=0) || (strcmp(BCT.SERVICE_CODE,"300")!=0)))
        {

         INIT_STR(TempNumtoChar) ;
         sprintf (TempNumtoChar,"%lf",BCT.CHARGE);
         

         if( BCT.CHARGE/pow(10,ACC.TapDecimalPlaces) >= gIOTCharge/pow(10,ACC.TapDecimalPlaces) )
         {
          gIOTChargeDiff = BCT.CHARGE/pow(10,ACC.TapDecimalPlaces) - gIOTCharge/pow(10,ACC.TapDecimalPlaces);
         }
         else
         {
         gIOTChargeDiff = gIOTCharge/pow(10,ACC.TapDecimalPlaces) - BCT.CHARGE/pow(10,ACC.TapDecimalPlaces);
         }

         /*if(BCT.CHARGE != gIOTCharge)*/

        
        if (gIOTChargeDiff > (BCT.CHARGE/pow(10,ACC.TapDecimalPlaces))*0.02 || gIOTChargeDiff > (gIOTCharge/pow(10,ACC.TapDecimalPlaces))*0.02)
         {
             
              REI.ERROR_CODE[gRejectedErrorNo]  = 200                 ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 62              ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
              lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
              if(lValidateFlag == 0)
              {
               
                  lIOTChargeFlag = 1;
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"Charge") ;
                  sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",StIOTCdr.CHARGE_CONTEXT,"62:0:L") ; 
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Charge not in line with roaming agreement");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
               
              }
        
         }  

  }

     if((BCT.CHARGE!=0) && (BCT.TAX_VALUE!=0) && (BCT.CALL_TYPE!=1)&&((strcmp(BCT.SERVICE_CODE,"000")!=0) || (strcmp(BCT.SERVICE_CODE,"300")!=0)))
      { 
 
            INIT_STR(TempNumtoChar) ;
            sprintf (TempNumtoChar,"%d",BCT.TAX_VALUE);
             if( BCT.TAX_VALUE >= gIOTTax )
             {
              gIOTTaxDiff = BCT.TAX_VALUE - gIOTTax;
            }
            else
            {
              gIOTTaxDiff = gIOTTax - BCT.TAX_VALUE;
            }


         if (gIOTTaxDiff > (BCT.TAX_VALUE)*0.02 || gIOTTaxDiff > (gIOTTax)*0.02)
               {
              REI.ERROR_CODE[gRejectedErrorNo]  = 200                 ;
              REI.APPLICATION_TAG[gRejectedErrorNo] = 397             ;
              strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"SEVERE")       ;
              lValidateFlag = fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]) ;
              if(lValidateFlag == 0)
              {
                  lIOTTaxFlag = 1;
                  strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"Calls");
                  strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"TaxValue") ;
                  sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"%s;%s",StIOTCdr.TAX_CONTEXT,"397:0:L") ;
                  fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                  strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Tax Value is not in line with the roaming agreement at the corresponding call event date");
                  strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                  gRejectedErrorNo++ ;
              }
           }
      }


	
         /* Set Required Details */

         if(((lIOTChargeFlag == 1) || (lIOTTaxFlag == 1)) && (StIOTCdr.CDR_ERROR_FLAG == 0))
         {
             StIOTErrorCDR.CallSequence[gIotErrorCDRCount] = BCT.CALL_SEQUENCE ;
             gIotErrorCDRCount++ ;
             gErrorCDRsCount = gErrorCDRsCount + 1 ;
             gErrorCDRsCharge = gErrorCDRsCharge + BCT.CHARGE + BCT.CAMEL_INVOCATION_FEE ;
             gErrorCDRsTax = gErrorCDRsTax + BCT.TAX_VALUE  ;
             gErrorCDRsDiscount = gErrorCDRsDiscount + BCT.DISCOUNT  ;
             gErrorCDRsDuration = gErrorCDRsDuration + BCT.CALL_DURATION ;
             FileSummary.SETTLEMENT_DURATION        = FileSummary.SETTLEMENT_DURATION - BCT.CALL_DURATION;
             FileSummary.SETTLEMENT_OUTGOING_VOLUME = FileSummary.SETTLEMENT_OUTGOING_VOLUME - BCT.DATA_VOLUME_OUTGOING;
             FileSummary.SETTLEMENT_INCOMING_VOLUME = FileSummary.SETTLEMENT_INCOMING_VOLUME - BCT.DATA_VOLUME_INCOMING;
             FileSummary.SETTLEMENT_LOCAL_CHARGE    = FileSummary.SETTLEMENT_LOCAL_CHARGE - BCT.HOME_CURNCY_CHARGE;
             FileSummary.SETTLEMENT_LOCAL_TAX       = FileSummary.SETTLEMENT_LOCAL_TAX - BCT.HOME_CURNCY_TAX;
             FileSummary.SETTLEMENT_LOCAL_DISCOUNT  = FileSummary.SETTLEMENT_LOCAL_DISCOUNT - BCT.HOME_CURNCY_DISCOUNT;
         }

         SetError = 0 ;

         /* Delete the CDRs from PM_TMP_TAP_CDRS Table */
         fnRemTrailSpaces(StIOTCdr.ROWID) ;
        /* EXEC SQL DELETE FROM PM_TMP_TAP_CDRS WHERE ROWID = :StIOTCdr.ROWID; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 12;
        sqlstm.arrsiz = 53;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "delete  from PM_TMP_TAP_CDRS  where ROWID=:b0";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )1203;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (         void  *)(StIOTCdr.ROWID);
        sqlstm.sqhstl[0] = (unsigned int  )20;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         void  *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned int  )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}

  

         if(ERRCODE != 0)
         {
             SetError=-1;
             TRACEENTRY(1,"%s","Error Deleting the CDR from PM_TMP_TAP_CDRS Table ");
             TRACEENTRY(1,"%s-%d-","sqlca.sqlcode:",ERRCODE);
             TRACEENTRY(1,"%s","Cannot Proceed with this Operator. Please Rectify the Error(PM_TMP_TAP_CDRS)");
             /* EXEC SQL ROLLBACK; */ 

{
             struct sqlexd sqlstm;
             sqlstm.sqlvsn = 12;
             sqlstm.arrsiz = 53;
             sqlstm.sqladtp = &sqladt;
             sqlstm.sqltdsp = &sqltds;
             sqlstm.iters = (unsigned int  )1;
             sqlstm.offset = (unsigned int  )1222;
             sqlstm.cud = sqlcud0;
             sqlstm.sqlest = (unsigned char  *)&sqlca;
             sqlstm.sqlety = (unsigned short)4352;
             sqlstm.occurs = (unsigned int  )0;
             sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


             break;
         }
        
     
         if((gRejectedErrorNo > 0) && (gFatalErrorCount == 0) && (strcmp(gGenerateFilesFlg,"N")!=0))
         {
             gCDRErrorFlag = 1 ;

             for(ErrorCount=0; ErrorCount<gRejectedErrorNo; ErrorCount++)
             {
                 ErrorReturnValue = SetBulkErrorDetails(gBulkErrorDetailsIndex, ErrorCount,StIOTCdr.ERROR_NODE)   ;
                 if(ErrorReturnValue == -1)
                 {
                    return -1;
                 }
             }
         }
         gRejectedErrorNo = 0;

   }     

   /* EXEC SQL CLOSE I; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 53;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )1237;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   if(SetError != 0)
   {
      return SetError ;
   }


   return 0 ;

}

void InitialiseIOTCDR()
{
    INIT_STR(StIOTCdr.FILE_TRANSFER_DIRECTION) ;
    INIT_STR(StIOTCdr.HPLMN_CODE)              ;
    INIT_STR(StIOTCdr.VPLMN_CODE)              ;
    INIT_STR(StIOTCdr.PARTNER_CODE)            ;
    INIT_STR(StIOTCdr.FILE_TYPE_INDICATOR)     ;
    StIOTCdr.FILE_SEQUENCE_NUMBER           = 0;
    StIOTCdr.CALL_SEQUENCE                  = 0;
    StIOTCdr.CALL_TYPE                      = 0; 
    INIT_STR(StIOTCdr.SERVICE_CODE)            ;
    StIOTCdr.IMSI                           = 0;
    INIT_STR(StIOTCdr.MSISDN)                  ;
    INIT_STR(StIOTCdr.CALLED_CALLING_NUMBER)   ;
    INIT_STR(StIOTCdr.DIALLED_DIGITS)          ;
    INIT_STR(StIOTCdr.CALL_DATE)               ;
    StIOTCdr.CALL_DURATION                  = 0;
    INIT_STR(StIOTCdr.BASIC_SERVICE_TYPE)      ;
    INIT_STR(StIOTCdr.BASIC_SERVICE_CODE)      ;
    INIT_STR(StIOTCdr.CHARGED_ITEM)            ;
    StIOTCdr.CHARGEABLE_UNITS               = 0;
    StIOTCdr.CHARGED_UNITS                  = 0;
    StIOTCdr.CHARGE                         = 0;
    StIOTCdr.TAX_INFORMATION_COUNT          = 0;
    StIOTCdr.TAX_CODE                       = 0;
    StIOTCdr.TAX_VALUE                      = 0;
    StIOTCdr.TAXABLE_AMOUNT                 = 0;
    StIOTCdr.DISCOUNT_INFORMATION_COUNT     = 0;
    StIOTCdr.DISCOUNT_CODE                  = 0;
    StIOTCdr.DISCOUNT                       = 0;
    StIOTCdr.DISCOUNTABLE_AMT               = 0;
    StIOTCdr.TAP_EXCHANGE_RATE              = 0;
    StIOTCdr.TAP_EXCHANGE_RATE_DECIMAL      = 0;
    StIOTCdr.DATA_VOLUME_INCOMING           = 0;
    StIOTCdr.DATA_VOLUME_OUTGOING           = 0;
    StIOTCdr.CALL_TYPE_LEVEL1               = 0;
    StIOTCdr.IOT_CHARGE                     = 0;
    StIOTCdr.IOT_TAX                        = 0;
    StIOTCdr.IOT_DISCOUNT                   = 0;
    StIOTCdr.TARIFF_ID                      = 0;
    StIOTCdr.CDR_ERROR_FLAG                 = 0;
    INIT_STR(StIOTCdr.CHARGE_CONTEXT)          ;
    INIT_STR(StIOTCdr.TAX_CONTEXT)             ;
    INIT_STR(StIOTCdr.DISCOUNT_CONTEXT)        ;
    StIOTCdr.ERROR_NODE                     = 0;
    INIT_STR(StIOTCdr.IOT_DATE)               ;
    INIT_STR(StIOTCdr.IOT_CALCULATION)        ;
    INIT_STR(StIOTCdr.ROWID)                  ;
}


int LoadMasterData()
{
   /* Local Variables Declarations */
   int i=0,h=0;
   int SetError=0;
   int ExchCount=0;
   int ProcessDtlCount=0;
   int PartnerCount=0;
   int RAPPartnerCount=0;
   int TagErrorCodeCount=0;
   int HplmnCodeCount;

   long Temp=0;
   long x=0;
   char TempString[20];
   DIR*   DirPtr;
   char   TempDir[250];

   /**************************************************************************************/
   /* Get the Count of the HPLMN Codes */

   HplmnCodeCount  = 0 ;
   gHplmnCodeCount = 0 ;

   /* EXEC SQL SELECT COUNT(1)
              INTO :HplmnCodeCount
              FROM PM_ROAMING_PREFERENCES; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 53;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select count(1) into :b0  from PM_ROAMING_PREFERENCES ";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )1252;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&HplmnCodeCount;
   sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   /* Check for Error in Execution */
   if(ERRCODE != 0 || HplmnCodeCount ==0)
   {
      TRACEENTRY(1,"%s","Error Fetching Count from PM_ROAMING_PREFERENCES tables");
      TRACEENTRY(1,"%s -%d-","sqlca.sqlcode",ERRCODE);
      return(-1);
   }

   gHplmnCodeCount = HplmnCodeCount ;

   /* Allocate memmory to the Hplmn Codes */
   ptRoamingPref1 = (stRoamingPreferences*) \
                        malloc(HplmnCodeCount * sizeof(stRoamingPreferences));

   if(ptRoamingPref1 == NULL)
   {
      TRACEENTRY(1,"%s","Memory allocation error for HPLMN Code Details");
      return -1;
   }

   for(h=0;h<HplmnCodeCount;h++)
   {
      ptRoamingPref2 = (ptRoamingPref1 + h);
      /* EXEC SQL VAR ptRoamingPref2->HPLMN_CODE             IS STRING(6); */ 

      /* EXEC SQL VAR ptRoamingPref2->ISO_CURNCY_CODE        IS STRING(4); */ 

      /* EXEC SQL VAR ptRoamingPref2->TAPOUT_CURNCY          IS STRING(6); */ 

      /* EXEC SQL VAR ptRoamingPref2->UTC_OFFSET             IS STRING(7); */ 

      ptRoamingPref2->TAP_SPECIFICATION_VERSION           = 0;
      ptRoamingPref2->TAP_RELEASE_VERSION                 = 0;
      ptRoamingPref2->RATE_MULT_FACT                      = 0;
      ptRoamingPref2->HOME_CURNCY_ROUNDOFF_FACT           = 0;
      ptRoamingPref2->TAPIN_CDR_VALIDITY_DAYS             = 0;
      ptRoamingPref2->HOME_CURNCY_TAPIN_MULTFACT          = 0;
      ptRoamingPref2->TAPIN_EXCH_RATE_DECIMAL_PLACES      = 0;
      ptRoamingPref2->TAPIN_EXCH_RATE_MULT_FACT           = 0;
      /* EXEC SQL VAR ptRoamingPref2->HOME_CURNCY            IS STRING(21); */ 

      /* EXEC SQL VAR ptRoamingPref2->IMSI_PREFIX_POSTPAID   IS STRING(101); */ 

      /* EXEC SQL VAR ptRoamingPref2->IMSI_PREFIX_PREPAID    IS STRING(101); */ 

      ptRoamingPref2->IMSI_PREFIX_POSTPAID_LEN            = 0;
      ptRoamingPref2->IMSI_PREFIX_PREPAID_LEN             = 0;
      ptRoamingPref2->RAP_SPECIFICATION_VERSION           = 0;
      ptRoamingPref2->RAP_RELEASE_VERSION                 = 0;
   }


   /**************************************************************************************/
   /* Get the Details of Roaming Preferences for Each HPLMN Code */

   /* EXEC SQL DECLARE R CURSOR FOR
             SELECT nvl(trim(HPLMN_CODE),' '),
                    nvl(trim(ISO_CURNCY_CODE),' '),
                    nvl(trim(TAPOUT_CURNCY),' '),
                    nvl(trim(UTC_OFFSET),' '),
                    nvl(TAP_SPECIFICATION_VERSION,0),
                    nvl(TAP_RELEASE_VERSION,0),
                    nvl(RATE_MULT_FACT,0),
                    nvl(HOME_CURNCY_ROUNDOFF_FACT,0),
                    nvl(TAPIN_CDR_VALIDITY_DAYS,0),
                    nvl(HOME_CURNCY_TAPIN_MULTFACT,0),
                    nvl(TAPIN_EXCH_RATE_DECIMAL_PLACES,0),
                    nvl(TAPIN_EXCH_RATE_MULT_FACT,0),
                    nvl(HOME_CURNCY,' '),
                    nvl(IMSI_PREFIX_POSTPAID,' '),
                    nvl(IMSI_PREFIX_PREPAID,' '),
                    nvl(IMSI_PREFIX_POSTPAID_LEN,0),
                    nvl(IMSI_PREFIX_PREPAID_LEN,0),
                    nvl(RAP_SPECIFICATION_VERSION,0),
                    nvl(RAP_RELEASE_VERSION,0)
               FROM PM_ROAMING_PREFERENCES ; */ 
 

   /* EXEC SQL OPEN R; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 53;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = sq0051;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )1271;
   sqlstm.selerr = (unsigned short)20000;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqcmod = (unsigned int )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


   /* EXEC SQL FOR :HplmnCodeCount FETCH R INTO :ptRoamingPref1; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 53;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )HplmnCodeCount;
   sqlstm.offset = (unsigned int  )1286;
   sqlstm.selerr = (unsigned short)20000;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqfoff = (           int )0;
   sqlstm.sqfmod = (unsigned int )2;
   sqlstm.sqhstv[0] = (         void  *)ptRoamingPref1->HPLMN_CODE;
   sqlstm.sqhstl[0] = (unsigned int  )6;
   sqlstm.sqhsts[0] = (         int  )sizeof(struct stRoamingPreferences);
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)ptRoamingPref1->ISO_CURNCY_CODE;
   sqlstm.sqhstl[1] = (unsigned int  )4;
   sqlstm.sqhsts[1] = (         int  )sizeof(struct stRoamingPreferences);
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)ptRoamingPref1->TAPOUT_CURNCY;
   sqlstm.sqhstl[2] = (unsigned int  )6;
   sqlstm.sqhsts[2] = (         int  )sizeof(struct stRoamingPreferences);
   sqlstm.sqindv[2] = (         void  *)0;
   sqlstm.sqinds[2] = (         int  )0;
   sqlstm.sqharm[2] = (unsigned int  )0;
   sqlstm.sqadto[2] = (unsigned short )0;
   sqlstm.sqtdso[2] = (unsigned short )0;
   sqlstm.sqhstv[3] = (         void  *)ptRoamingPref1->UTC_OFFSET;
   sqlstm.sqhstl[3] = (unsigned int  )7;
   sqlstm.sqhsts[3] = (         int  )sizeof(struct stRoamingPreferences);
   sqlstm.sqindv[3] = (         void  *)0;
   sqlstm.sqinds[3] = (         int  )0;
   sqlstm.sqharm[3] = (unsigned int  )0;
   sqlstm.sqadto[3] = (unsigned short )0;
   sqlstm.sqtdso[3] = (unsigned short )0;
   sqlstm.sqhstv[4] = (         void  *)&ptRoamingPref1->TAP_SPECIFICATION_VERSION;
   sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[4] = (         int  )sizeof(struct stRoamingPreferences);
   sqlstm.sqindv[4] = (         void  *)0;
   sqlstm.sqinds[4] = (         int  )0;
   sqlstm.sqharm[4] = (unsigned int  )0;
   sqlstm.sqadto[4] = (unsigned short )0;
   sqlstm.sqtdso[4] = (unsigned short )0;
   sqlstm.sqhstv[5] = (         void  *)&ptRoamingPref1->TAP_RELEASE_VERSION;
   sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[5] = (         int  )sizeof(struct stRoamingPreferences);
   sqlstm.sqindv[5] = (         void  *)0;
   sqlstm.sqinds[5] = (         int  )0;
   sqlstm.sqharm[5] = (unsigned int  )0;
   sqlstm.sqadto[5] = (unsigned short )0;
   sqlstm.sqtdso[5] = (unsigned short )0;
   sqlstm.sqhstv[6] = (         void  *)&ptRoamingPref1->RATE_MULT_FACT;
   sqlstm.sqhstl[6] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[6] = (         int  )sizeof(struct stRoamingPreferences);
   sqlstm.sqindv[6] = (         void  *)0;
   sqlstm.sqinds[6] = (         int  )0;
   sqlstm.sqharm[6] = (unsigned int  )0;
   sqlstm.sqadto[6] = (unsigned short )0;
   sqlstm.sqtdso[6] = (unsigned short )0;
   sqlstm.sqhstv[7] = (         void  *)&ptRoamingPref1->HOME_CURNCY_ROUNDOFF_FACT;
   sqlstm.sqhstl[7] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[7] = (         int  )sizeof(struct stRoamingPreferences);
   sqlstm.sqindv[7] = (         void  *)0;
   sqlstm.sqinds[7] = (         int  )0;
   sqlstm.sqharm[7] = (unsigned int  )0;
   sqlstm.sqadto[7] = (unsigned short )0;
   sqlstm.sqtdso[7] = (unsigned short )0;
   sqlstm.sqhstv[8] = (         void  *)&ptRoamingPref1->TAPIN_CDR_VALIDITY_DAYS;
   sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[8] = (         int  )sizeof(struct stRoamingPreferences);
   sqlstm.sqindv[8] = (         void  *)0;
   sqlstm.sqinds[8] = (         int  )0;
   sqlstm.sqharm[8] = (unsigned int  )0;
   sqlstm.sqadto[8] = (unsigned short )0;
   sqlstm.sqtdso[8] = (unsigned short )0;
   sqlstm.sqhstv[9] = (         void  *)&ptRoamingPref1->HOME_CURNCY_TAPIN_MULTFACT;
   sqlstm.sqhstl[9] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[9] = (         int  )sizeof(struct stRoamingPreferences);
   sqlstm.sqindv[9] = (         void  *)0;
   sqlstm.sqinds[9] = (         int  )0;
   sqlstm.sqharm[9] = (unsigned int  )0;
   sqlstm.sqadto[9] = (unsigned short )0;
   sqlstm.sqtdso[9] = (unsigned short )0;
   sqlstm.sqhstv[10] = (         void  *)&ptRoamingPref1->TAPIN_EXCH_RATE_DECIMAL_PLACES;
   sqlstm.sqhstl[10] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[10] = (         int  )sizeof(struct stRoamingPreferences);
   sqlstm.sqindv[10] = (         void  *)0;
   sqlstm.sqinds[10] = (         int  )0;
   sqlstm.sqharm[10] = (unsigned int  )0;
   sqlstm.sqadto[10] = (unsigned short )0;
   sqlstm.sqtdso[10] = (unsigned short )0;
   sqlstm.sqhstv[11] = (         void  *)&ptRoamingPref1->TAPIN_EXCH_RATE_MULT_FACT;
   sqlstm.sqhstl[11] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[11] = (         int  )sizeof(struct stRoamingPreferences);
   sqlstm.sqindv[11] = (         void  *)0;
   sqlstm.sqinds[11] = (         int  )0;
   sqlstm.sqharm[11] = (unsigned int  )0;
   sqlstm.sqadto[11] = (unsigned short )0;
   sqlstm.sqtdso[11] = (unsigned short )0;
   sqlstm.sqhstv[12] = (         void  *)ptRoamingPref1->HOME_CURNCY;
   sqlstm.sqhstl[12] = (unsigned int  )21;
   sqlstm.sqhsts[12] = (         int  )sizeof(struct stRoamingPreferences);
   sqlstm.sqindv[12] = (         void  *)0;
   sqlstm.sqinds[12] = (         int  )0;
   sqlstm.sqharm[12] = (unsigned int  )0;
   sqlstm.sqadto[12] = (unsigned short )0;
   sqlstm.sqtdso[12] = (unsigned short )0;
   sqlstm.sqhstv[13] = (         void  *)ptRoamingPref1->IMSI_PREFIX_POSTPAID;
   sqlstm.sqhstl[13] = (unsigned int  )101;
   sqlstm.sqhsts[13] = (         int  )sizeof(struct stRoamingPreferences);
   sqlstm.sqindv[13] = (         void  *)0;
   sqlstm.sqinds[13] = (         int  )0;
   sqlstm.sqharm[13] = (unsigned int  )0;
   sqlstm.sqadto[13] = (unsigned short )0;
   sqlstm.sqtdso[13] = (unsigned short )0;
   sqlstm.sqhstv[14] = (         void  *)ptRoamingPref1->IMSI_PREFIX_PREPAID;
   sqlstm.sqhstl[14] = (unsigned int  )101;
   sqlstm.sqhsts[14] = (         int  )sizeof(struct stRoamingPreferences);
   sqlstm.sqindv[14] = (         void  *)0;
   sqlstm.sqinds[14] = (         int  )0;
   sqlstm.sqharm[14] = (unsigned int  )0;
   sqlstm.sqadto[14] = (unsigned short )0;
   sqlstm.sqtdso[14] = (unsigned short )0;
   sqlstm.sqhstv[15] = (         void  *)&ptRoamingPref1->IMSI_PREFIX_POSTPAID_LEN;
   sqlstm.sqhstl[15] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[15] = (         int  )sizeof(struct stRoamingPreferences);
   sqlstm.sqindv[15] = (         void  *)0;
   sqlstm.sqinds[15] = (         int  )0;
   sqlstm.sqharm[15] = (unsigned int  )0;
   sqlstm.sqadto[15] = (unsigned short )0;
   sqlstm.sqtdso[15] = (unsigned short )0;
   sqlstm.sqhstv[16] = (         void  *)&ptRoamingPref1->IMSI_PREFIX_PREPAID_LEN;
   sqlstm.sqhstl[16] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[16] = (         int  )sizeof(struct stRoamingPreferences);
   sqlstm.sqindv[16] = (         void  *)0;
   sqlstm.sqinds[16] = (         int  )0;
   sqlstm.sqharm[16] = (unsigned int  )0;
   sqlstm.sqadto[16] = (unsigned short )0;
   sqlstm.sqtdso[16] = (unsigned short )0;
   sqlstm.sqhstv[17] = (         void  *)&ptRoamingPref1->RAP_SPECIFICATION_VERSION;
   sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[17] = (         int  )sizeof(struct stRoamingPreferences);
   sqlstm.sqindv[17] = (         void  *)0;
   sqlstm.sqinds[17] = (         int  )0;
   sqlstm.sqharm[17] = (unsigned int  )0;
   sqlstm.sqadto[17] = (unsigned short )0;
   sqlstm.sqtdso[17] = (unsigned short )0;
   sqlstm.sqhstv[18] = (         void  *)&ptRoamingPref1->RAP_RELEASE_VERSION;
   sqlstm.sqhstl[18] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[18] = (         int  )sizeof(struct stRoamingPreferences);
   sqlstm.sqindv[18] = (         void  *)0;
   sqlstm.sqinds[18] = (         int  )0;
   sqlstm.sqharm[18] = (unsigned int  )0;
   sqlstm.sqadto[18] = (unsigned short )0;
   sqlstm.sqtdso[18] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


   /* EXEC SQL CLOSE R; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 53;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )1377;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}

 


   TRACEENTRY(1,"%s","LoadMasterData: Loading PM_ROAMING_PREFERENCES table");

   /* Check for Error in Execution */
   if(ERRCODE != 0)
   {
      TRACEENTRY(1,"%s","ERROR : Fetching Data from PM_ROAMING_PREFERENCES table");
      TRACEENTRY(1,"sqlca.sqlcode -%d-",ERRCODE);
      stErrors.ERROR_CODE = sqlca.sqlcode;
      strcpy(stErrors.ERROR_DESC,"Fetching Data from PM_ROAMING_PREFERENCES table");
      return(-1);
   }

   for(h=0;h<HplmnCodeCount;h++)
   {
      ptRoamingPref2 = (ptRoamingPref1 + h);

      TRACEENTRY(1,"%s-%s-","Validate Details for the HPLMN_CODE :: ",ptRoamingPref2->HPLMN_CODE);

      /* Validate HPLMN_CODE */
      if(strcmp(ptRoamingPref2->HPLMN_CODE," ")==0)
      {
         TRACEENTRY(1,"%s","HPLMN_CODE is null in PM_ROAMING_PREFERENCES table");
         stErrors.ERROR_CODE = sqlca.sqlcode;
         strcpy(stErrors.ERROR_DESC,"HPLMN_CODE is null in PM_ROAMING_PREFERENCES table");
         SetError=-1;
      }

      /* Validate the CDR Validity Days */
      if((ptRoamingPref2->TAPIN_CDR_VALIDITY_DAYS <0)) 
      {
         TRACEENTRY(1,"%s","TAPIN_CDR_VALIDITY_DAYS is Null or Negative in PM_ROAMING_PREFERENCES table");
         stErrors.ERROR_CODE = sqlca.sqlcode;
         strcpy(stErrors.ERROR_DESC,"TAPIN_CDR_VALIDITY_DAYS is Null or Negative in PM_ROAMING_PREFERENCES table");
         SetError=-1;
      }

      if(strcmp(ptRoamingPref2->UTC_OFFSET," ")==0)
      {
         TRACEENTRY(1,"%s","UTC_OFFSET is Null in PM_ROAMING_PREFERENCES table. Expected Format (+/-)HHMM");
         stErrors.ERROR_CODE = sqlca.sqlcode;
         strcpy(stErrors.ERROR_DESC,"UTC_OFFSET is Null in PM_ROAMING_PREFERENCES table. Expected Format (+/-)HHMM");
         SetError=-1;
      }
      else
      {
         /* Check for +/- as the first Character */
         TempString[0]='\0';
         sprintf(TempString,"%c",ptRoamingPref2->UTC_OFFSET[0]);

         if((TempString[0] != '+') && (TempString[0] != '-'))
         {
            TRACEENTRY(1,"%s","Invalid UTC_OFFSET in PM_ROAMING_PREFERENCES table. Expected Format (+/-)HHMM");
            stErrors.ERROR_CODE = sqlca.sqlcode;
            strcpy(stErrors.ERROR_DESC,"Invalid UTC_OFFSET in PM_ROAMING_PREFERENCES table. Expected Format (+/-)HHMM");
            SetError=-1;
         }

         /* Check for Hours. Range is -13 to +13 */
         TempString[0]='\0';
         sprintf(TempString,"%c%c",ptRoamingPref2->UTC_OFFSET[1],ptRoamingPref2->UTC_OFFSET[2]);

         if((atoi(TempString) < -13 || atoi(TempString) > 13))
         {
            TRACEENTRY(1,"%s","Invalid UTC_OFFSET in PM_ROAMING_PREFERENCES table. Expected Format (+/-)HHMM");
            stErrors.ERROR_CODE = sqlca.sqlcode;
            strcpy(stErrors.ERROR_DESC,"Invalid UTC_OFFSET in PM_ROAMING_PREFERENCES table. Expected Format (+/-)HHMM");
            SetError=-1;
         }
      
         /* Check for Minutes. Range is 00 t0 59 */
         TempString[0]='\0';
         sprintf(TempString,"%c%c",ptRoamingPref2->UTC_OFFSET[3],ptRoamingPref2->UTC_OFFSET[4]);

         if((atoi(TempString) < 0 || atoi(TempString) > 59))
         {
            TRACEENTRY(1,"%s","Invalid UTC_OFFSET in PM_ROAMING_PREFERENCES table. Expected Format (+/-)HHMM");
            stErrors.ERROR_CODE = sqlca.sqlcode;
            strcpy(stErrors.ERROR_DESC,"Invalid UTC_OFFSET in PM_ROAMING_PREFERENCES table. Expected Format (+/-)HHMM");
            SetError=-1;
         }
      }

      /* Validate the TAP Specification Version */
      if((ptRoamingPref2->TAP_SPECIFICATION_VERSION<=0))
      {
         TRACEENTRY(1,"%s","Invalid TAP_SPECIFICATION_VERSION in PM_ROAMING_PREFERENCES");
         stErrors.ERROR_CODE = sqlca.sqlcode;
         strcpy(stErrors.ERROR_DESC,"Invalid TAP_SPECIFICATION_VERSION in PM_ROAMING_PREFERENCES");
         SetError=-1;
      }

      /* Validate the TAP Specification Release */
      if((ptRoamingPref2->TAP_RELEASE_VERSION==0))
      {
         TRACEENTRY(1,"%s","Invalid TAP_RELEASE_VERSION in PM_ROAMING_PREFERENCES");
         stErrors.ERROR_CODE = sqlca.sqlcode;
         strcpy(stErrors.ERROR_DESC,"Invalid TAP_RELEASE_VERSION in PM_ROAMING_PREFERENCES");
         SetError=-1;
      }

      /* Validate Home Multiplication Factor for TAPIN. This has to be 1 or a multiple of 10 */
      if((ptRoamingPref2->HOME_CURNCY_TAPIN_MULTFACT<= 0))
      {
         TRACEENTRY(1,"%s","HOME_CURNCY_TAPIN_MULTFACT in PM_ROAMING_PREFERENCES is Null/Zero/Negative");
         stErrors.ERROR_CODE = sqlca.sqlcode;
         strcpy(stErrors.ERROR_DESC,"HOME_CURNCY_TAPIN_MULTFACT in PM_ROAMING_PREFERENCES is Null/Zero/Negative");
         SetError=-1;
      }
      else if((ptRoamingPref2->HOME_CURNCY_TAPIN_MULTFACT> 1) && (ptRoamingPref2->HOME_CURNCY_TAPIN_MULTFACT< 10))
      {
         TRACEENTRY(1,"%s","HOME_CURNCY_TAPIN_MULTFACT in PM_ROAMING_PREFERENCES should be 1 or Multiple of 10");
         stErrors.ERROR_CODE = sqlca.sqlcode;
         strcpy(stErrors.ERROR_DESC,"HOME_CURNCY_TAPIN_MULTFACT in PM_ROAMING_PREFERENCES should be 1 or Multiple of 10");
         SetError=-1;
      }
      else if((ptRoamingPref2->HOME_CURNCY_TAPIN_MULTFACT> 10) && (ptRoamingPref2->HOME_CURNCY_TAPIN_MULTFACT != 1))
      {
         /* Check if this is multiple of 10 */
         Temp = (long) ptRoamingPref2->HOME_CURNCY_TAPIN_MULTFACT;
         x    = 0;

        while(1)
        {
           x    = Temp/10;

           /* Break with Error, if MultiplicationFactor is Not a Multiple of 10 */
           if((x == 1) && (Temp > 10))
           {
              TRACEENTRY(1,"%s","HOME_CURNCY_TAPIN_MULTFACT in PM_ROAMING_PREFERENCES should be 1 or Multiple of 10");
              stErrors.ERROR_CODE = sqlca.sqlcode;
              strcpy(stErrors.ERROR_DESC,"HOME_CURNCY_TAPIN_MULTFACT in PM_ROAMING_PREFERENCES should be 1 or Multiple of 10");
              SetError=-1;
              break;
           }

           /* Break without Error, if MultiplicationFactor is a Multiple of 10 */
           if((x == 1) && (Temp == 10))
           {
              break;
           }

           Temp = Temp/10;
        }
      }

      /* Check Exchange Rate Decimal Places for TAPIN conversion to local currency */ 
      if(ptRoamingPref2->TAPIN_EXCH_RATE_DECIMAL_PLACES <0) 
      {
         TRACEENTRY(1,"%s","TAPIN_EXCH_RATE_DECIMAL_PLACES in PM_ROAMING_PREFERENCES is Negative");
         stErrors.ERROR_CODE = sqlca.sqlcode;
         strcpy(stErrors.ERROR_DESC,"TAPIN_EXCH_RATE_DECIMAL_PLACES in PM_ROAMING_PREFERENCES is Negative");
         SetError=-1;
      }

      /* Check the Exchange Rate Multiplicatin for TAPIN conversion to local currency */
      if((ptRoamingPref2->TAPIN_EXCH_RATE_MULT_FACT <= 0))
      {
         TRACEENTRY(1,"%s","TAPIN_EXCH_RATE_MULT_FACT in PM_ROAMING_PREFERENCES is Invalid");
         stErrors.ERROR_CODE = sqlca.sqlcode;
         strcpy(stErrors.ERROR_DESC,"TAPIN_EXCH_RATE_MULT_FACT in PM_ROAMING_PREFERENCES is Invalid");
         SetError=-1;
      }
      else if((ptRoamingPref2->TAPIN_EXCH_RATE_MULT_FACT > 1) && (ptRoamingPref2->TAPIN_EXCH_RATE_MULT_FACT < 10))
      {
         TRACEENTRY(1,"%s","TAPIN_EXCH_RATE_MULT_FACT in PM_ROAMING_PREFERENCES should be 1 or Multiple of 10");
         stErrors.ERROR_CODE = sqlca.sqlcode;
         strcpy(stErrors.ERROR_DESC,"TAPIN_EXCH_RATE_MULT_FACT in PM_ROAMING_PREFERENCES should be 1 or Multiple of 10");
         SetError=-1;
      }
      else if((ptRoamingPref2->TAPIN_EXCH_RATE_MULT_FACT > 10) && (ptRoamingPref2->TAPIN_EXCH_RATE_MULT_FACT != 1))
      {
         /* Check if this is multiple of 10 */
         Temp = (long) ptRoamingPref2->TAPIN_EXCH_RATE_MULT_FACT;
         x    = 0;

         while(1)
         {
            x    = Temp/10;

            /* Break with Error, if MultiplicationFactor is Not a Multiple of 10 */
            if((x == 1) && (Temp > 10))
            {
               TRACEENTRY(1,"%s","TAPIN_EXCH_RATE_MULT_FACT in PM_ROAMING_PREFERENCES should be 1 or Multiple of 10");
               stErrors.ERROR_CODE = sqlca.sqlcode;
               strcpy(stErrors.ERROR_DESC,"TAPIN_EXCH_RATE_MULT_FACT in PM_ROAMING_PREFERENCES should be 1 or Multiple of 10");
               SetError=-1;
               break;
            }

            /* Break without Error, if MultiplicationFactor is a Multiple of 10 */
            if((x == 1) && (Temp == 10))
            {
               break;
            }

            Temp = Temp/10;
         }
      }

      /* Validate the Home Currency.*/
      if((strcmp(ptRoamingPref2->HOME_CURNCY," ")==0))
      {
         TRACEENTRY(1,"%s","HOME_CURNCY in PM_ROAMING_PREFERENCES is NULL");
         stErrors.ERROR_CODE = sqlca.sqlcode;
         strcpy(stErrors.ERROR_DESC,"HOME_CURNCY in PM_ROAMING_PREFERENCES is NULL");
         SetError=-1;
      }

      /* Postpaid IMSI Prefix */

      /* Prepaid IMSI Prefix */

      /* Postpaid IMSI Prefix Length */

      /* Prepaid IMSI Prefix Length */

      if(SetError==-1)
      {
         return SetError;
      }
   }

   /**************************************************************************************/
   /* Load the Exchange Rates for the last 24Months */
   /* Here from currency is the Stadard SDR and te to currency is the one set in he master */


   for(h=0;h<1;h++)
   {
      ptRoamingPref2 = (ptRoamingPref1 + h);

      ExchCount = 0;

      /* EXEC SQL SELECT COUNT(*)
                 INTO :ExchCount
                 FROM PM_CURRENCY_EXCHANGE_RATE
                WHERE trim(FROM_CURRENCY_CODE) = trim(:ptRoamingPref2->TAPOUT_CURNCY)
                  AND trim(TO_CURRENCY_CODE) = trim(:ptRoamingPref2->HOME_CURNCY)
                  AND ROWNUM < 25
             ORDER BY VALID_FROM DESC; */ 

{
      struct sqlexd sqlstm;
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 53;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.stmt = "select count(*)  into :b0  from PM_CURRENCY_EXCHANGE_RA\
TE where ((trim(FROM_CURRENCY_CODE)=trim(:b1) and trim(TO_CURRENCY_CODE)=trim(\
:b2)) and ROWNUM<25) order by VALID_FROM desc  ";
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )1392;
      sqlstm.selerr = (unsigned short)1;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)4352;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqhstv[0] = (         void  *)&ExchCount;
      sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[0] = (         int  )0;
      sqlstm.sqindv[0] = (         void  *)0;
      sqlstm.sqinds[0] = (         int  )0;
      sqlstm.sqharm[0] = (unsigned int  )0;
      sqlstm.sqadto[0] = (unsigned short )0;
      sqlstm.sqtdso[0] = (unsigned short )0;
      sqlstm.sqhstv[1] = (         void  *)(ptRoamingPref2->TAPOUT_CURNCY);
      sqlstm.sqhstl[1] = (unsigned int  )6;
      sqlstm.sqhsts[1] = (         int  )0;
      sqlstm.sqindv[1] = (         void  *)0;
      sqlstm.sqinds[1] = (         int  )0;
      sqlstm.sqharm[1] = (unsigned int  )0;
      sqlstm.sqadto[1] = (unsigned short )0;
      sqlstm.sqtdso[1] = (unsigned short )0;
      sqlstm.sqhstv[2] = (         void  *)(ptRoamingPref2->HOME_CURNCY);
      sqlstm.sqhstl[2] = (unsigned int  )21;
      sqlstm.sqhsts[2] = (         int  )0;
      sqlstm.sqindv[2] = (         void  *)0;
      sqlstm.sqinds[2] = (         int  )0;
      sqlstm.sqharm[2] = (unsigned int  )0;
      sqlstm.sqadto[2] = (unsigned short )0;
      sqlstm.sqtdso[2] = (unsigned short )0;
      sqlstm.sqphsv = sqlstm.sqhstv;
      sqlstm.sqphsl = sqlstm.sqhstl;
      sqlstm.sqphss = sqlstm.sqhsts;
      sqlstm.sqpind = sqlstm.sqindv;
      sqlstm.sqpins = sqlstm.sqinds;
      sqlstm.sqparm = sqlstm.sqharm;
      sqlstm.sqparc = sqlstm.sqharc;
      sqlstm.sqpadto = sqlstm.sqadto;
      sqlstm.sqptdso = sqlstm.sqtdso;
      sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


        
   
      if(ERRCODE != 0 || ExchCount==0)
      {
         TRACEENTRY(1,"%s","ERROR : Error Fetching Count from PM_CURRENCY_EXCHANGE_RATE table");
         TRACEENTRY(1,"sqlca.sqlcode : -%d-",ERRCODE);
         TRACEENTRY(1,"FROM_CURRENCY_CODE : -%s-",ptRoamingPref2->TAPOUT_CURNCY);
         TRACEENTRY(1,"TO_CURRENCY_CODE   : -%s-",ptRoamingPref2->HOME_CURNCY);
         TRACEENTRY(1,"ExchangeRateCount : -%d-",ExchCount); 
         stErrors.ERROR_CODE = sqlca.sqlcode;
         strcpy(stErrors.ERROR_DESC,"Error Fetching Count from PM_CURRENCY_EXCHANGE_RATE table");
         return -1;
      }
/*  printf("from_currency %s\n,to_currency %s\n",ptRoamingPref2->TAPOUT_CURNCY,ptRoamingPref2->HOME_CURNCY);*/

      if(ExchCount>0)
      {
         /* Allocate memory for the pointer */
         ptExchRates1 = (stExchangeRates *) \
                           malloc(ExchCount * sizeof(stExchangeRates));

         if(ptExchRates1 == NULL)
         {
            TRACEENTRY(1,"%s","Memory allocation error for ExchangeRates");
            stErrors.ERROR_CODE = 0;
            strcpy(stErrors.ERROR_DESC,"Memory allocation error for ExchangeRates");
            return -1;
         }

         for(i=0;i<ExchCount;i++)
         {
            ptExchRates2 = (ptExchRates1 + i);
            ptExchRates2->EXCHANGE_RATE_CODE = 0;
            /* EXEC SQL VAR ptExchRates2->VALID_FROM IS STRING(15); */ 

            /* EXEC SQL VAR ptExchRates2->VALID_TILL IS STRING(15); */ 

            ptExchRates2->EXCHANGE_RATE      = 0;
         }

         /* EXEC SQL ALTER SESSION SET NLS_CALENDAR = 'Gregorian'; */ 

{
         struct sqlexd sqlstm;
         sqlstm.sqlvsn = 12;
         sqlstm.arrsiz = 53;
         sqlstm.sqladtp = &sqladt;
         sqlstm.sqltdsp = &sqltds;
         sqlstm.stmt = "alter SESSION SET NLS_CALENDAR = 'Gregorian'";
         sqlstm.iters = (unsigned int  )1;
         sqlstm.offset = (unsigned int  )1419;
         sqlstm.cud = sqlcud0;
         sqlstm.sqlest = (unsigned char  *)&sqlca;
         sqlstm.sqlety = (unsigned short)4352;
         sqlstm.occurs = (unsigned int  )0;
         sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


         /* EXEC SQL ALTER SESSION SET NLS_DATE_FORMAT = 'YYYYMMDDHH24MISS' ; */ 

{
         struct sqlexd sqlstm;
         sqlstm.sqlvsn = 12;
         sqlstm.arrsiz = 53;
         sqlstm.sqladtp = &sqladt;
         sqlstm.sqltdsp = &sqltds;
         sqlstm.stmt = "alter SESSION SET NLS_DATE_FORMAT = 'YYYYMMDDHH24MIS\
S'";
         sqlstm.iters = (unsigned int  )1;
         sqlstm.offset = (unsigned int  )1434;
         sqlstm.cud = sqlcud0;
         sqlstm.sqlest = (unsigned char  *)&sqlca;
         sqlstm.sqlety = (unsigned short)4352;
         sqlstm.occurs = (unsigned int  )0;
         sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



         /* EXEC SQL DECLARE D CURSOR FOR
                   SELECT nvl(EXCHANGE_RATE_CODE,0),
                          to_char(VALID_FROM,'YYYYMMDDHH24MISS'),
                          to_char(VALID_TILL,'YYYYMMDDHH24MISS'),
                          nvl(EXCHANGE_RATE,0)
                     FROM PM_CURRENCY_EXCHANGE_RATE
                    WHERE trim(FROM_CURRENCY_CODE) = trim(:ptRoamingPref2->TAPOUT_CURNCY)
                      AND trim(TO_CURRENCY_CODE) = trim(:ptRoamingPref2->HOME_CURNCY)
                     /o AND ROWNUM < 25 o/
                 ORDER BY VALID_FROM DESC; */ 

 
         /* EXEC SQL OPEN D; */ 

{
         struct sqlexd sqlstm;
         sqlstm.sqlvsn = 12;
         sqlstm.arrsiz = 53;
         sqlstm.sqladtp = &sqladt;
         sqlstm.sqltdsp = &sqltds;
         sqlstm.stmt = sq0055;
         sqlstm.iters = (unsigned int  )1;
         sqlstm.offset = (unsigned int  )1449;
         sqlstm.selerr = (unsigned short)20000;
         sqlstm.cud = sqlcud0;
         sqlstm.sqlest = (unsigned char  *)&sqlca;
         sqlstm.sqlety = (unsigned short)4352;
         sqlstm.occurs = (unsigned int  )0;
         sqlstm.sqcmod = (unsigned int )0;
         sqlstm.sqhstv[0] = (         void  *)(ptRoamingPref2->TAPOUT_CURNCY);
         sqlstm.sqhstl[0] = (unsigned int  )6;
         sqlstm.sqhsts[0] = (         int  )0;
         sqlstm.sqindv[0] = (         void  *)0;
         sqlstm.sqinds[0] = (         int  )0;
         sqlstm.sqharm[0] = (unsigned int  )0;
         sqlstm.sqadto[0] = (unsigned short )0;
         sqlstm.sqtdso[0] = (unsigned short )0;
         sqlstm.sqhstv[1] = (         void  *)(ptRoamingPref2->HOME_CURNCY);
         sqlstm.sqhstl[1] = (unsigned int  )21;
         sqlstm.sqhsts[1] = (         int  )0;
         sqlstm.sqindv[1] = (         void  *)0;
         sqlstm.sqinds[1] = (         int  )0;
         sqlstm.sqharm[1] = (unsigned int  )0;
         sqlstm.sqadto[1] = (unsigned short )0;
         sqlstm.sqtdso[1] = (unsigned short )0;
         sqlstm.sqphsv = sqlstm.sqhstv;
         sqlstm.sqphsl = sqlstm.sqhstl;
         sqlstm.sqphss = sqlstm.sqhsts;
         sqlstm.sqpind = sqlstm.sqindv;
         sqlstm.sqpins = sqlstm.sqinds;
         sqlstm.sqparm = sqlstm.sqharm;
         sqlstm.sqparc = sqlstm.sqharc;
         sqlstm.sqpadto = sqlstm.sqadto;
         sqlstm.sqptdso = sqlstm.sqtdso;
         sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


         /* EXEC SQL FOR :ExchCount FETCH D INTO :ptExchRates1; */ 

{
         struct sqlexd sqlstm;
         sqlstm.sqlvsn = 12;
         sqlstm.arrsiz = 53;
         sqlstm.sqladtp = &sqladt;
         sqlstm.sqltdsp = &sqltds;
         sqlstm.iters = (unsigned int  )ExchCount;
         sqlstm.offset = (unsigned int  )1472;
         sqlstm.selerr = (unsigned short)20000;
         sqlstm.cud = sqlcud0;
         sqlstm.sqlest = (unsigned char  *)&sqlca;
         sqlstm.sqlety = (unsigned short)4352;
         sqlstm.occurs = (unsigned int  )0;
         sqlstm.sqfoff = (           int )0;
         sqlstm.sqfmod = (unsigned int )2;
         sqlstm.sqhstv[0] = (         void  *)&ptExchRates1->EXCHANGE_RATE_CODE;
         sqlstm.sqhstl[0] = (unsigned int  )sizeof(long);
         sqlstm.sqhsts[0] = (         int  )sizeof(struct stExchangeRates);
         sqlstm.sqindv[0] = (         void  *)0;
         sqlstm.sqinds[0] = (         int  )0;
         sqlstm.sqharm[0] = (unsigned int  )0;
         sqlstm.sqadto[0] = (unsigned short )0;
         sqlstm.sqtdso[0] = (unsigned short )0;
         sqlstm.sqhstv[1] = (         void  *)ptExchRates1->VALID_FROM;
         sqlstm.sqhstl[1] = (unsigned int  )15;
         sqlstm.sqhsts[1] = (         int  )sizeof(struct stExchangeRates);
         sqlstm.sqindv[1] = (         void  *)0;
         sqlstm.sqinds[1] = (         int  )0;
         sqlstm.sqharm[1] = (unsigned int  )0;
         sqlstm.sqadto[1] = (unsigned short )0;
         sqlstm.sqtdso[1] = (unsigned short )0;
         sqlstm.sqhstv[2] = (         void  *)ptExchRates1->VALID_TILL;
         sqlstm.sqhstl[2] = (unsigned int  )15;
         sqlstm.sqhsts[2] = (         int  )sizeof(struct stExchangeRates);
         sqlstm.sqindv[2] = (         void  *)0;
         sqlstm.sqinds[2] = (         int  )0;
         sqlstm.sqharm[2] = (unsigned int  )0;
         sqlstm.sqadto[2] = (unsigned short )0;
         sqlstm.sqtdso[2] = (unsigned short )0;
         sqlstm.sqhstv[3] = (         void  *)&ptExchRates1->EXCHANGE_RATE;
         sqlstm.sqhstl[3] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[3] = (         int  )sizeof(struct stExchangeRates);
         sqlstm.sqindv[3] = (         void  *)0;
         sqlstm.sqinds[3] = (         int  )0;
         sqlstm.sqharm[3] = (unsigned int  )0;
         sqlstm.sqadto[3] = (unsigned short )0;
         sqlstm.sqtdso[3] = (unsigned short )0;
         sqlstm.sqphsv = sqlstm.sqhstv;
         sqlstm.sqphsl = sqlstm.sqhstl;
         sqlstm.sqphss = sqlstm.sqhsts;
         sqlstm.sqpind = sqlstm.sqindv;
         sqlstm.sqpins = sqlstm.sqinds;
         sqlstm.sqparm = sqlstm.sqharm;
         sqlstm.sqparc = sqlstm.sqharc;
         sqlstm.sqpadto = sqlstm.sqadto;
         sqlstm.sqptdso = sqlstm.sqtdso;
         sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


         /* EXEC SQL CLOSE D; */ 

{
         struct sqlexd sqlstm;
         sqlstm.sqlvsn = 12;
         sqlstm.arrsiz = 53;
         sqlstm.sqladtp = &sqladt;
         sqlstm.sqltdsp = &sqltds;
         sqlstm.iters = (unsigned int  )1;
         sqlstm.offset = (unsigned int  )1503;
         sqlstm.cud = sqlcud0;
         sqlstm.sqlest = (unsigned char  *)&sqlca;
         sqlstm.sqlety = (unsigned short)4352;
         sqlstm.occurs = (unsigned int  )0;
         sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



         if(ERRCODE != 0)
         {
            TRACEENTRY(1,"%s","ERROR : Error Fetching Data from PM_CURRENCY_EXCHANGE_RATE table");
            TRACEENTRY(1,"sqlca.sqlcode : -%d-",ERRCODE);
            TRACEENTRY(1,"FROM_CURRENCY_CODE : -%s-",ptRoamingPref2->TAPOUT_CURNCY);
            TRACEENTRY(1,"TO_CURRENCY_CODE   : -%s-",ptRoamingPref2->HOME_CURNCY);
            stErrors.ERROR_CODE = sqlca.sqlcode;
            strcpy(stErrors.ERROR_DESC,"Error Fetching Data from PM_CURRENCY_EXCHANGE_RATE table");
            return -1;
         }
      }

      /* Check if Exchange Rates are Greater than Zero */
      for(i=0;i<ExchCount;i++)
      {
         ptExchRates2 = (ptExchRates1 + i);
         if(ptExchRates2->EXCHANGE_RATE==0)
         {
            TRACEENTRY(1,"%s","Exchange Rate in PM_CURRENCY_EXCHANGE_RATE cannot be zero for any date range");
            stErrors.ERROR_CODE = 0;
            strcpy(stErrors.ERROR_DESC,"Exchange Rate in PM_CURRENCY_EXCHANGE_RATE cannot be zero for any date range");
            SetError=-1;
            break;
         }
      }

      /* Set the Global Variable for ExchangeRateCount to the Total Count of Exchange Rates */
      gExchCount = 0;
      gExchCount = ExchCount;

   }

   /**************************************************************************************/
   /* Load the Application Preference table */
   INIT_STR(gImsiPrefix) ;
   /* EXEC SQL VAR stAppPref.IMSI_PRFX          IS STRING(101); */ 

   stAppPref.IMSI_PRFX_LEN                   = 0;

   /* EXEC SQL SELECT nvl(trim(IMSI_PRFX),' '),
                   nvl(IMSI_PRFX_LEN,0) 
              INTO :stAppPref.IMSI_PRFX,
                   :stAppPref.IMSI_PRFX_LEN
              FROM PM_APP_PREFERENCE; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 53;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select nvl(trim(IMSI_PRFX),' ') ,nvl(IMSI_PRFX_LEN,0) into\
 :b0,:b1  from PM_APP_PREFERENCE ";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )1518;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)(stAppPref.IMSI_PRFX);
   sqlstm.sqhstl[0] = (unsigned int  )101;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)&(stAppPref.IMSI_PRFX_LEN);
   sqlstm.sqhstl[1] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}




   /* Check for Error in Execution */
   if(ERRCODE != 0)
   {
      TRACEENTRY(1,"%s","ERROR: Error Fetching Data from PM_APP_PREFERENCE table");
      TRACEENTRY(1,"%s -%d-","sqlca.sqlcode",ERRCODE);
      stErrors.ERROR_CODE = sqlca.sqlcode;
      strcpy(stErrors.ERROR_DESC,"Error Fetching Data from PM_APP_PREFERENCE table");
      return(-1);
   }

   /* Validate IMSI_PRFX */
   if(strcmp(stAppPref.IMSI_PRFX," ")==0)
   {
      TRACEENTRY(1,"%s","Invalid IMSI_PRFX specified in PM_APP_PREFERENCE");
      TRACEENTRY(1,"IMSI_PRFX : -%s-",stAppPref.IMSI_PRFX);
      stErrors.ERROR_CODE = sqlca.sqlcode;
      strcpy(stErrors.ERROR_DESC,"IMSI_PRFX in PM_APP_PREFERENCE is Null");
      SetError=-1;
   }

   /* Validate the IMSI Prefix Length */
   if((stAppPref.IMSI_PRFX_LEN <= 0))
   {
      TRACEENTRY(1,"%s","Invalid IMSI_PRFX_LEN specified in PM_APP_PREFERENCE");
      TRACEENTRY(1,"IMSI_PRFX_LEN : -%d-",stAppPref.IMSI_PRFX_LEN);
      stErrors.ERROR_CODE = sqlca.sqlcode;
      strcpy(stErrors.ERROR_DESC,"IMSI_PRFX_LEN in PM_APP_PREFERENCE is Null or Negative");
      SetError=-1;
   }

   strcpy(gImsiPrefix,stAppPref.IMSI_PRFX);
 

   /**************************************************************************************/
   /* Load the Partner Information */

   gPartnerCount=0;
   PartnerCount=0;
   /* EXEC SQL SELECT COUNT(1)
              INTO :PartnerCount
              FROM PM_PARTNER A, PM_ROAM_PARTNER_FILE_INFO B, PM_ROAM_PARTNER_ADDN_INFO C
             WHERE A.PARTNER_CODE       = B.PARTNER_CODE
               AND A.PARTNER_CODE       = C.PARTNER_CODE
               AND B.GENERATE_FILES_FLG = 'Y'
               AND B.PROCESS_ID         = :gProcessId; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 53;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select count(1) into :b0  from PM_PARTNER A ,PM_ROAM_PARTN\
ER_FILE_INFO B ,PM_ROAM_PARTNER_ADDN_INFO C where (((A.PARTNER_CODE=B.PARTNER_\
CODE and A.PARTNER_CODE=C.PARTNER_CODE) and B.GENERATE_FILES_FLG='Y') and B.PR\
OCESS_ID=:b1)";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )1541;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&PartnerCount;
   sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)&gProcessId;
   sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   /* Check for Error in Execution */
   if(ERRCODE != 0 || PartnerCount==0)
   {
      TRACEENTRY(1,"%s","Error Fetching Count from PM_PARTNER and PM_ROAM_PARTNER_FILE_INFO tables");
      TRACEENTRY(1,"%s -%d-","sqlca.sqlcode",ERRCODE);
      stErrors.ERROR_CODE = sqlca.sqlcode;
      strcpy(stErrors.ERROR_DESC,"Error Fetching Count from PM_PARTNER and PM_ROAM_PARTNER_FILE_INFO tables");
      return(-1);
   }

   /* Allocate memmory to the partners */
   ptPartners1 = (PM_PARTNERS*) \
                        malloc(PartnerCount * sizeof(PM_PARTNERS));

   if(ptPartners1 == NULL)
   {
      TRACEENTRY(1,"%s","Memory allocation error for ExchangeRates");
      stErrors.ERROR_CODE = 0;
      strcpy(stErrors.ERROR_DESC,"Memory allocation error for Partners");
      return -1;
   }

   for(i=0;i<PartnerCount;i++)
   {
      ptPartners2 = (ptPartners1 + i);
      /* EXEC SQL VAR ptPartners2->PARTNER_CODE         IS STRING(4); */ 

      /* EXEC SQL VAR ptPartners2->PARTNER_SHORT_CODE   IS STRING(7); */ 

      /* EXEC SQL VAR ptPartners2->TAPIN_SURCHARGE_FLAG IS STRING(2); */ 

      ptPartners2->TAPIN_SURCHARGE_RATE              = 0;
      /* EXEC SQL VAR ptPartners2->TAPIN_TAX_FLAG       IS STRING(2); */ 

      /* EXEC SQL VAR ptPartners2->TAPIN_DISCOUNT_FLAG  IS STRING(2); */ 

      ptPartners2->TAPIN_DISCOUNT_RATE		     = 0;
      ptPartners2->TAPIN_TAX_RATE		     = 0;
      /* EXEC SQL VAR ptPartners2->CHECK_CALL_AGE_FLG   IS STRING(2); */ 

      ptPartners2->CALL_AGE                          = 0;
      /* EXEC SQL VAR ptPartners2->CHECK_FILE_AGE_FLG   IS STRING(2); */ 

      ptPartners2->FILE_AGE                          = 0;
      /* EXEC SQL VAR ptPartners2->IOT_CHECK            IS STRING(2); */ 

      ptPartners2->FREQUENCY_IN_MINUTE               = 0;
   }

   /* Fetch the data into local array */
   /* EXEC SQL DECLARE E CURSOR FOR
             SELECT A.PARTNER_CODE,
		    NVL(DECODE(trim(B.CHECK_ALIAS_TADIG),'Y',trim(C.ALIAS_TADIG_CODE),trim(A.PARTNER_SHORT_CODE)),' '),
                    nvl(trim(C.TAPIN_SURCHARGE_FLAG),' '),
                    nvl(C.TAPIN_SURCHARGE_RATE,0),
                    nvl(trim(C.TAPIN_TAX_FLAG),' '),
                    nvl(trim(C.TAPIN_DISCOUNT_FLAG),' '),
                    nvl(C.TAPIN_DISCOUNT_RATE,0),
                    nvl(C.TAPIN_TAX_RATE,0),
                    nvl(B.CHECK_CALL_AGE_FLG,' '),
                    nvl(B.CALL_AGE,0),
                    nvl(B.CHECK_FILE_AGE_FLG,' '),
                    nvl(B.FILE_AGE,0),
                    nvl(C.IOT_CHECK,'N'),
                    nvl(B.FREQUENCY_IN_MINUTE,0),
                    nvl(C.MOBL_PRFX_V,' ')
	       FROM PM_PARTNER A, PM_ROAM_PARTNER_FILE_INFO B, PM_ROAM_PARTNER_ADDN_INFO C
              WHERE A.PARTNER_CODE       = B.PARTNER_CODE
                AND A.PARTNER_CODE       = C.PARTNER_CODE
                AND B.GENERATE_FILES_FLG = 'Y'
                AND B.PROCESS_ID         = :gProcessId
           ORDER BY A.PARTNER_CODE; */ 
   

   /* EXEC SQL OPEN E; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 53;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = sq0058;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )1564;
   sqlstm.selerr = (unsigned short)20000;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqcmod = (unsigned int )0;
   sqlstm.sqhstv[0] = (         void  *)&gProcessId;
   sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


   /* EXEC SQL FOR :PartnerCount FETCH E INTO :ptPartners1; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 53;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )PartnerCount;
   sqlstm.offset = (unsigned int  )1583;
   sqlstm.selerr = (unsigned short)20000;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqfoff = (           int )0;
   sqlstm.sqfmod = (unsigned int )2;
   sqlstm.sqhstv[0] = (         void  *)ptPartners1->PARTNER_CODE;
   sqlstm.sqhstl[0] = (unsigned int  )4;
   sqlstm.sqhsts[0] = (         int  )sizeof(struct PM_PARTNERS);
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)ptPartners1->PARTNER_SHORT_CODE;
   sqlstm.sqhstl[1] = (unsigned int  )7;
   sqlstm.sqhsts[1] = (         int  )sizeof(struct PM_PARTNERS);
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)ptPartners1->TAPIN_SURCHARGE_FLAG;
   sqlstm.sqhstl[2] = (unsigned int  )2;
   sqlstm.sqhsts[2] = (         int  )sizeof(struct PM_PARTNERS);
   sqlstm.sqindv[2] = (         void  *)0;
   sqlstm.sqinds[2] = (         int  )0;
   sqlstm.sqharm[2] = (unsigned int  )0;
   sqlstm.sqadto[2] = (unsigned short )0;
   sqlstm.sqtdso[2] = (unsigned short )0;
   sqlstm.sqhstv[3] = (         void  *)&ptPartners1->TAPIN_SURCHARGE_RATE;
   sqlstm.sqhstl[3] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[3] = (         int  )sizeof(struct PM_PARTNERS);
   sqlstm.sqindv[3] = (         void  *)0;
   sqlstm.sqinds[3] = (         int  )0;
   sqlstm.sqharm[3] = (unsigned int  )0;
   sqlstm.sqadto[3] = (unsigned short )0;
   sqlstm.sqtdso[3] = (unsigned short )0;
   sqlstm.sqhstv[4] = (         void  *)ptPartners1->TAPIN_TAX_FLAG;
   sqlstm.sqhstl[4] = (unsigned int  )2;
   sqlstm.sqhsts[4] = (         int  )sizeof(struct PM_PARTNERS);
   sqlstm.sqindv[4] = (         void  *)0;
   sqlstm.sqinds[4] = (         int  )0;
   sqlstm.sqharm[4] = (unsigned int  )0;
   sqlstm.sqadto[4] = (unsigned short )0;
   sqlstm.sqtdso[4] = (unsigned short )0;
   sqlstm.sqhstv[5] = (         void  *)ptPartners1->TAPIN_DISCOUNT_FLAG;
   sqlstm.sqhstl[5] = (unsigned int  )2;
   sqlstm.sqhsts[5] = (         int  )sizeof(struct PM_PARTNERS);
   sqlstm.sqindv[5] = (         void  *)0;
   sqlstm.sqinds[5] = (         int  )0;
   sqlstm.sqharm[5] = (unsigned int  )0;
   sqlstm.sqadto[5] = (unsigned short )0;
   sqlstm.sqtdso[5] = (unsigned short )0;
   sqlstm.sqhstv[6] = (         void  *)&ptPartners1->TAPIN_DISCOUNT_RATE;
   sqlstm.sqhstl[6] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[6] = (         int  )sizeof(struct PM_PARTNERS);
   sqlstm.sqindv[6] = (         void  *)0;
   sqlstm.sqinds[6] = (         int  )0;
   sqlstm.sqharm[6] = (unsigned int  )0;
   sqlstm.sqadto[6] = (unsigned short )0;
   sqlstm.sqtdso[6] = (unsigned short )0;
   sqlstm.sqhstv[7] = (         void  *)&ptPartners1->TAPIN_TAX_RATE;
   sqlstm.sqhstl[7] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[7] = (         int  )sizeof(struct PM_PARTNERS);
   sqlstm.sqindv[7] = (         void  *)0;
   sqlstm.sqinds[7] = (         int  )0;
   sqlstm.sqharm[7] = (unsigned int  )0;
   sqlstm.sqadto[7] = (unsigned short )0;
   sqlstm.sqtdso[7] = (unsigned short )0;
   sqlstm.sqhstv[8] = (         void  *)ptPartners1->CHECK_CALL_AGE_FLG;
   sqlstm.sqhstl[8] = (unsigned int  )2;
   sqlstm.sqhsts[8] = (         int  )sizeof(struct PM_PARTNERS);
   sqlstm.sqindv[8] = (         void  *)0;
   sqlstm.sqinds[8] = (         int  )0;
   sqlstm.sqharm[8] = (unsigned int  )0;
   sqlstm.sqadto[8] = (unsigned short )0;
   sqlstm.sqtdso[8] = (unsigned short )0;
   sqlstm.sqhstv[9] = (         void  *)&ptPartners1->CALL_AGE;
   sqlstm.sqhstl[9] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[9] = (         int  )sizeof(struct PM_PARTNERS);
   sqlstm.sqindv[9] = (         void  *)0;
   sqlstm.sqinds[9] = (         int  )0;
   sqlstm.sqharm[9] = (unsigned int  )0;
   sqlstm.sqadto[9] = (unsigned short )0;
   sqlstm.sqtdso[9] = (unsigned short )0;
   sqlstm.sqhstv[10] = (         void  *)ptPartners1->CHECK_FILE_AGE_FLG;
   sqlstm.sqhstl[10] = (unsigned int  )2;
   sqlstm.sqhsts[10] = (         int  )sizeof(struct PM_PARTNERS);
   sqlstm.sqindv[10] = (         void  *)0;
   sqlstm.sqinds[10] = (         int  )0;
   sqlstm.sqharm[10] = (unsigned int  )0;
   sqlstm.sqadto[10] = (unsigned short )0;
   sqlstm.sqtdso[10] = (unsigned short )0;
   sqlstm.sqhstv[11] = (         void  *)&ptPartners1->FILE_AGE;
   sqlstm.sqhstl[11] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[11] = (         int  )sizeof(struct PM_PARTNERS);
   sqlstm.sqindv[11] = (         void  *)0;
   sqlstm.sqinds[11] = (         int  )0;
   sqlstm.sqharm[11] = (unsigned int  )0;
   sqlstm.sqadto[11] = (unsigned short )0;
   sqlstm.sqtdso[11] = (unsigned short )0;
   sqlstm.sqhstv[12] = (         void  *)ptPartners1->IOT_CHECK;
   sqlstm.sqhstl[12] = (unsigned int  )2;
   sqlstm.sqhsts[12] = (         int  )sizeof(struct PM_PARTNERS);
   sqlstm.sqindv[12] = (         void  *)0;
   sqlstm.sqinds[12] = (         int  )0;
   sqlstm.sqharm[12] = (unsigned int  )0;
   sqlstm.sqadto[12] = (unsigned short )0;
   sqlstm.sqtdso[12] = (unsigned short )0;
   sqlstm.sqhstv[13] = (         void  *)&ptPartners1->FREQUENCY_IN_MINUTE;
   sqlstm.sqhstl[13] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[13] = (         int  )sizeof(struct PM_PARTNERS);
   sqlstm.sqindv[13] = (         void  *)0;
   sqlstm.sqinds[13] = (         int  )0;
   sqlstm.sqharm[13] = (unsigned int  )0;
   sqlstm.sqadto[13] = (unsigned short )0;
   sqlstm.sqtdso[13] = (unsigned short )0;
   sqlstm.sqhstv[14] = (         void  *)ptPartners1->MOBL_PRFX_V;
   sqlstm.sqhstl[14] = (unsigned int  )7;
   sqlstm.sqhsts[14] = (         int  )sizeof(struct PM_PARTNERS);
   sqlstm.sqindv[14] = (         void  *)0;
   sqlstm.sqinds[14] = (         int  )0;
   sqlstm.sqharm[14] = (unsigned int  )0;
   sqlstm.sqadto[14] = (unsigned short )0;
   sqlstm.sqtdso[14] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


   /* EXEC SQL CLOSE E; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 53;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )1658;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   if(ERRCODE != 0)
   {
      TRACEENTRY(1,"%s","Error Fetching Data from PM_PARTNER and PM_ROAM_PARTNER_FILE_INFO tables");
      TRACEENTRY(1,"%s -%d-","sqlca.sqlcode",ERRCODE);
      stErrors.ERROR_CODE = sqlca.sqlcode;
      strcpy(stErrors.ERROR_DESC,"Error Fetching Data from PM_PARTNER and PM_ROAM_PARTNER_FILE_INFO tables");
      return -1;
   }

   gPartnerCount = PartnerCount;

   /* Get the file directory information for charge and test files */
   /* EXEC SQL VAR stProcessDtls.CHARGE_FILE_TYPE_INDICATOR IS STRING(2); */ 

   /* EXEC SQL VAR stProcessDtls.CHARGE_HOME_DIR_FLG        IS STRING(2); */ 

   /* EXEC SQL VAR stProcessDtls.CHARGE_HOME_DIR	         IS STRING(101); */ 

   /* EXEC SQL VAR stProcessDtls.CHARGE_FILES_DIR           IS STRING(101); */ 

   /* EXEC SQL VAR stProcessDtls.CHARGE_PROCESS_FILES_DIR   IS STRING(101); */ 

   /* EXEC SQL VAR stProcessDtls.CHARGE_ERROR_FILES_DIR     IS STRING(101); */ 

   /* EXEC SQL VAR stProcessDtls.CHARGE_TOUCHFILES_FLG      IS STRING(2); */ 

   /* EXEC SQL VAR stProcessDtls.CHARGE_SUCCESS_FILES_DIR   IS STRING(101); */ 

   
   /* EXEC SQL VAR stProcessDtls.TEST_FILE_TYPE_INDICATOR   IS STRING(2); */ 

   /* EXEC SQL VAR stProcessDtls.TEST_HOME_DIR_FLG          IS STRING(2); */ 

   /* EXEC SQL VAR stProcessDtls.TEST_HOME_DIR              IS STRING(101); */ 

   /* EXEC SQL VAR stProcessDtls.TEST_FILES_DIR             IS STRING(101); */ 

   /* EXEC SQL VAR stProcessDtls.TEST_PROCESS_FILES_DIR     IS STRING(101); */ 

   /* EXEC SQL VAR stProcessDtls.TEST_ERROR_FILES_DIR       IS STRING(101); */ 

   /* EXEC SQL VAR stProcessDtls.TEST_TOUCHFILES_FLG        IS STRING(2); */ 

   /* EXEC SQL VAR stProcessDtls.TEST_SUCCESS_FILES_DIR     IS STRING(101); */ 


   /* EXEC SQL SELECT nvl(TRIM(A.FILE_TYPE_INDICATOR),' '),
                   nvl(TRIM(A.HOME_DIR_FLG),' '),
                   nvl(TRIM(A.HOME_DIR),' '),
                   nvl(TRIM(A.FILES_DIR),' '),
                   nvl(TRIM(A.PROCESS_FILES_DIR),' '),
                   nvl(TRIM(A.ERROR_FILES_DIR),' '),
		   NVL(TRIM(A.TOUCHFILES_FLG),' '),
                   NVL(TRIM(A.SUCCESS_FILES_DIR),' '),
                   nvl(TRIM(B.FILE_TYPE_INDICATOR),' '),
                   nvl(TRIM(B.HOME_DIR_FLG),' '),
                   nvl(TRIM(B.HOME_DIR),' '),
                   nvl(TRIM(B.FILES_DIR),' '),
                   nvl(TRIM(B.PROCESS_FILES_DIR),' '),
                   nvl(TRIM(B.ERROR_FILES_DIR),' '),
		   NVL(TRIM(B.TOUCHFILES_FLG),' '),
                   NVL(TRIM(B.SUCCESS_FILES_DIR),' ')
              INTO :stProcessDtls.CHARGE_FILE_TYPE_INDICATOR,
                   :stProcessDtls.CHARGE_HOME_DIR_FLG,
                   :stProcessDtls.CHARGE_HOME_DIR,
		   :stProcessDtls.CHARGE_FILES_DIR,
                   :stProcessDtls.CHARGE_PROCESS_FILES_DIR,
                   :stProcessDtls.CHARGE_ERROR_FILES_DIR,
                   :stProcessDtls.CHARGE_TOUCHFILES_FLG,
                   :stProcessDtls.CHARGE_SUCCESS_FILES_DIR,
		   :stProcessDtls.TEST_FILE_TYPE_INDICATOR,
                   :stProcessDtls.TEST_HOME_DIR_FLG,
                   :stProcessDtls.TEST_HOME_DIR,
                   :stProcessDtls.TEST_FILES_DIR,
                   :stProcessDtls.TEST_PROCESS_FILES_DIR,
                   :stProcessDtls.TEST_ERROR_FILES_DIR,
                   :stProcessDtls.TEST_TOUCHFILES_FLG,
                   :stProcessDtls.TEST_SUCCESS_FILES_DIR
              FROM PM_PROCESS_DETAILS A,PM_PROCESS_DETAILS B
             WHERE A.PROCESS_ID = :gProcessId 
               AND A.FILE_TYPE_INDICATOR='C'
               AND B.PROCESS_ID = :gProcessId 
               AND B.FILE_TYPE_INDICATOR='T'; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 53;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select nvl(trim(A.FILE_TYPE_INDICATOR),' ') ,nvl(trim(A.HO\
ME_DIR_FLG),' ') ,nvl(trim(A.HOME_DIR),' ') ,nvl(trim(A.FILES_DIR),' ') ,nvl(t\
rim(A.PROCESS_FILES_DIR),' ') ,nvl(trim(A.ERROR_FILES_DIR),' ') ,NVL(trim(A.TO\
UCHFILES_FLG),' ') ,NVL(trim(A.SUCCESS_FILES_DIR),' ') ,nvl(trim(B.FILE_TYPE_I\
NDICATOR),' ') ,nvl(trim(B.HOME_DIR_FLG),' ') ,nvl(trim(B.HOME_DIR),' ') ,nvl(\
trim(B.FILES_DIR),' ') ,nvl(trim(B.PROCESS_FILES_DIR),' ') ,nvl(trim(B.ERROR_F\
ILES_DIR),' ') ,NVL(trim(B.TOUCHFILES_FLG),' ') ,NVL(trim(B.SUCCESS_FILES_DIR)\
,' ') into :b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b11,:b12,:b13,:b14,:b\
15  from PM_PROCESS_DETAILS A ,PM_PROCESS_DETAILS B where (((A.PROCESS_ID=:b16\
 and A.FILE_TYPE_INDICATOR='C') and B.PROCESS_ID=:b16) and B.FILE_TYPE_INDICAT\
OR='T')";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )1673;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)(stProcessDtls.CHARGE_FILE_TYPE_INDICATOR);
   sqlstm.sqhstl[0] = (unsigned int  )2;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)(stProcessDtls.CHARGE_HOME_DIR_FLG);
   sqlstm.sqhstl[1] = (unsigned int  )2;
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)(stProcessDtls.CHARGE_HOME_DIR);
   sqlstm.sqhstl[2] = (unsigned int  )101;
   sqlstm.sqhsts[2] = (         int  )0;
   sqlstm.sqindv[2] = (         void  *)0;
   sqlstm.sqinds[2] = (         int  )0;
   sqlstm.sqharm[2] = (unsigned int  )0;
   sqlstm.sqadto[2] = (unsigned short )0;
   sqlstm.sqtdso[2] = (unsigned short )0;
   sqlstm.sqhstv[3] = (         void  *)(stProcessDtls.CHARGE_FILES_DIR);
   sqlstm.sqhstl[3] = (unsigned int  )101;
   sqlstm.sqhsts[3] = (         int  )0;
   sqlstm.sqindv[3] = (         void  *)0;
   sqlstm.sqinds[3] = (         int  )0;
   sqlstm.sqharm[3] = (unsigned int  )0;
   sqlstm.sqadto[3] = (unsigned short )0;
   sqlstm.sqtdso[3] = (unsigned short )0;
   sqlstm.sqhstv[4] = (         void  *)(stProcessDtls.CHARGE_PROCESS_FILES_DIR);
   sqlstm.sqhstl[4] = (unsigned int  )101;
   sqlstm.sqhsts[4] = (         int  )0;
   sqlstm.sqindv[4] = (         void  *)0;
   sqlstm.sqinds[4] = (         int  )0;
   sqlstm.sqharm[4] = (unsigned int  )0;
   sqlstm.sqadto[4] = (unsigned short )0;
   sqlstm.sqtdso[4] = (unsigned short )0;
   sqlstm.sqhstv[5] = (         void  *)(stProcessDtls.CHARGE_ERROR_FILES_DIR);
   sqlstm.sqhstl[5] = (unsigned int  )101;
   sqlstm.sqhsts[5] = (         int  )0;
   sqlstm.sqindv[5] = (         void  *)0;
   sqlstm.sqinds[5] = (         int  )0;
   sqlstm.sqharm[5] = (unsigned int  )0;
   sqlstm.sqadto[5] = (unsigned short )0;
   sqlstm.sqtdso[5] = (unsigned short )0;
   sqlstm.sqhstv[6] = (         void  *)(stProcessDtls.CHARGE_TOUCHFILES_FLG);
   sqlstm.sqhstl[6] = (unsigned int  )2;
   sqlstm.sqhsts[6] = (         int  )0;
   sqlstm.sqindv[6] = (         void  *)0;
   sqlstm.sqinds[6] = (         int  )0;
   sqlstm.sqharm[6] = (unsigned int  )0;
   sqlstm.sqadto[6] = (unsigned short )0;
   sqlstm.sqtdso[6] = (unsigned short )0;
   sqlstm.sqhstv[7] = (         void  *)(stProcessDtls.CHARGE_SUCCESS_FILES_DIR);
   sqlstm.sqhstl[7] = (unsigned int  )101;
   sqlstm.sqhsts[7] = (         int  )0;
   sqlstm.sqindv[7] = (         void  *)0;
   sqlstm.sqinds[7] = (         int  )0;
   sqlstm.sqharm[7] = (unsigned int  )0;
   sqlstm.sqadto[7] = (unsigned short )0;
   sqlstm.sqtdso[7] = (unsigned short )0;
   sqlstm.sqhstv[8] = (         void  *)(stProcessDtls.TEST_FILE_TYPE_INDICATOR);
   sqlstm.sqhstl[8] = (unsigned int  )2;
   sqlstm.sqhsts[8] = (         int  )0;
   sqlstm.sqindv[8] = (         void  *)0;
   sqlstm.sqinds[8] = (         int  )0;
   sqlstm.sqharm[8] = (unsigned int  )0;
   sqlstm.sqadto[8] = (unsigned short )0;
   sqlstm.sqtdso[8] = (unsigned short )0;
   sqlstm.sqhstv[9] = (         void  *)(stProcessDtls.TEST_HOME_DIR_FLG);
   sqlstm.sqhstl[9] = (unsigned int  )2;
   sqlstm.sqhsts[9] = (         int  )0;
   sqlstm.sqindv[9] = (         void  *)0;
   sqlstm.sqinds[9] = (         int  )0;
   sqlstm.sqharm[9] = (unsigned int  )0;
   sqlstm.sqadto[9] = (unsigned short )0;
   sqlstm.sqtdso[9] = (unsigned short )0;
   sqlstm.sqhstv[10] = (         void  *)(stProcessDtls.TEST_HOME_DIR);
   sqlstm.sqhstl[10] = (unsigned int  )101;
   sqlstm.sqhsts[10] = (         int  )0;
   sqlstm.sqindv[10] = (         void  *)0;
   sqlstm.sqinds[10] = (         int  )0;
   sqlstm.sqharm[10] = (unsigned int  )0;
   sqlstm.sqadto[10] = (unsigned short )0;
   sqlstm.sqtdso[10] = (unsigned short )0;
   sqlstm.sqhstv[11] = (         void  *)(stProcessDtls.TEST_FILES_DIR);
   sqlstm.sqhstl[11] = (unsigned int  )101;
   sqlstm.sqhsts[11] = (         int  )0;
   sqlstm.sqindv[11] = (         void  *)0;
   sqlstm.sqinds[11] = (         int  )0;
   sqlstm.sqharm[11] = (unsigned int  )0;
   sqlstm.sqadto[11] = (unsigned short )0;
   sqlstm.sqtdso[11] = (unsigned short )0;
   sqlstm.sqhstv[12] = (         void  *)(stProcessDtls.TEST_PROCESS_FILES_DIR);
   sqlstm.sqhstl[12] = (unsigned int  )101;
   sqlstm.sqhsts[12] = (         int  )0;
   sqlstm.sqindv[12] = (         void  *)0;
   sqlstm.sqinds[12] = (         int  )0;
   sqlstm.sqharm[12] = (unsigned int  )0;
   sqlstm.sqadto[12] = (unsigned short )0;
   sqlstm.sqtdso[12] = (unsigned short )0;
   sqlstm.sqhstv[13] = (         void  *)(stProcessDtls.TEST_ERROR_FILES_DIR);
   sqlstm.sqhstl[13] = (unsigned int  )101;
   sqlstm.sqhsts[13] = (         int  )0;
   sqlstm.sqindv[13] = (         void  *)0;
   sqlstm.sqinds[13] = (         int  )0;
   sqlstm.sqharm[13] = (unsigned int  )0;
   sqlstm.sqadto[13] = (unsigned short )0;
   sqlstm.sqtdso[13] = (unsigned short )0;
   sqlstm.sqhstv[14] = (         void  *)(stProcessDtls.TEST_TOUCHFILES_FLG);
   sqlstm.sqhstl[14] = (unsigned int  )2;
   sqlstm.sqhsts[14] = (         int  )0;
   sqlstm.sqindv[14] = (         void  *)0;
   sqlstm.sqinds[14] = (         int  )0;
   sqlstm.sqharm[14] = (unsigned int  )0;
   sqlstm.sqadto[14] = (unsigned short )0;
   sqlstm.sqtdso[14] = (unsigned short )0;
   sqlstm.sqhstv[15] = (         void  *)(stProcessDtls.TEST_SUCCESS_FILES_DIR);
   sqlstm.sqhstl[15] = (unsigned int  )101;
   sqlstm.sqhsts[15] = (         int  )0;
   sqlstm.sqindv[15] = (         void  *)0;
   sqlstm.sqinds[15] = (         int  )0;
   sqlstm.sqharm[15] = (unsigned int  )0;
   sqlstm.sqadto[15] = (unsigned short )0;
   sqlstm.sqtdso[15] = (unsigned short )0;
   sqlstm.sqhstv[16] = (         void  *)&gProcessId;
   sqlstm.sqhstl[16] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[16] = (         int  )0;
   sqlstm.sqindv[16] = (         void  *)0;
   sqlstm.sqinds[16] = (         int  )0;
   sqlstm.sqharm[16] = (unsigned int  )0;
   sqlstm.sqadto[16] = (unsigned short )0;
   sqlstm.sqtdso[16] = (unsigned short )0;
   sqlstm.sqhstv[17] = (         void  *)&gProcessId;
   sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[17] = (         int  )0;
   sqlstm.sqindv[17] = (         void  *)0;
   sqlstm.sqinds[17] = (         int  )0;
   sqlstm.sqharm[17] = (unsigned int  )0;
   sqlstm.sqadto[17] = (unsigned short )0;
   sqlstm.sqtdso[17] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   /* Validate the Home Directory if present for Charge Files */
   INIT_STR(gChargeFilesDir);
   INIT_STR(gChargeProcessFilesDir);
   INIT_STR(gChargeErrorFilesDir);
   INIT_STR(gChargeSuccessDir);
   INIT_STR(gReadChargeFilePath);
   INIT_STR(gReadTestFilePath);

   if(strcmp(stProcessDtls.CHARGE_HOME_DIR_FLG,"Y")==0)
   {
      DirPtr = NULL;
      DirPtr = opendir(stProcessDtls.CHARGE_HOME_DIR);
      if(!DirPtr)
      {
         TRACEENTRY(1,"%s","Invalid HOME_DIR Specified in PM_PROCESS_DETAILS table for Charge TAPIN Files");
         return -1;
      }
      closedir(DirPtr);

      if(stProcessDtls.CHARGE_HOME_DIR[strlen(stProcessDtls.CHARGE_HOME_DIR)-1]=='/')
      {
         stProcessDtls.CHARGE_HOME_DIR[strlen(stProcessDtls.CHARGE_HOME_DIR)-1]='\0';
      }

      /* Form the Charge File Directory */
      sprintf(gChargeFilesDir,"%s/%s",stProcessDtls.CHARGE_HOME_DIR,stProcessDtls.CHARGE_FILES_DIR);

      /* Form the Process File Directory */
      sprintf(gChargeProcessFilesDir,"%s/%s",stProcessDtls.CHARGE_HOME_DIR,stProcessDtls.CHARGE_PROCESS_FILES_DIR);

      /* Form the Error File Directory */
      sprintf(gChargeErrorFilesDir,"%s/%s",stProcessDtls.CHARGE_HOME_DIR,stProcessDtls.CHARGE_ERROR_FILES_DIR);

      /* Form the Success File Directory */
      if(strcmp(stProcessDtls.CHARGE_TOUCHFILES_FLG,"Y")==0)
      {
         sprintf(gChargeSuccessDir,"%s/%s",stProcessDtls.CHARGE_HOME_DIR,stProcessDtls.CHARGE_SUCCESS_FILES_DIR);
      }
   }
   else
   {
      /* Form the Charge File Directory */
      sprintf(gChargeFilesDir,"%s",stProcessDtls.CHARGE_FILES_DIR);

      /* Form the Process File Directory */
      sprintf(gChargeProcessFilesDir,"%s",stProcessDtls.CHARGE_PROCESS_FILES_DIR);

      /* Form the Error File Directory */
      sprintf(gChargeErrorFilesDir,"%s",stProcessDtls.CHARGE_ERROR_FILES_DIR);

      /* Form the Success File Directory */
      if(strcmp(stProcessDtls.CHARGE_TOUCHFILES_FLG,"Y")==0)
      {
         sprintf(gChargeSuccessDir,"%s",stProcessDtls.CHARGE_SUCCESS_FILES_DIR);
      }
   }

   /* Validate the Files Directory Path */
   DirPtr = NULL;
   DirPtr = opendir(gChargeFilesDir);
   if(!DirPtr)
   {
      TRACEENTRY(1,"%s-%s-","gChargeFilesDir :",gChargeFilesDir);
      TRACEENTRY(1,"%s","Invalid FILES_DIR Specified in PM_PROCESS_DETAILS table for Charge TAPIN Files");
      TRACEENTRY(1,"%s -%s-","FILE_TYPE_INDICATOR :",stProcessDtls.CHARGE_FILE_TYPE_INDICATOR);
      TRACEENTRY(1,"%s -%s-","FILES_DIR           :",stProcessDtls.CHARGE_FILES_DIR);
      return -1;
   }
   closedir(DirPtr);

   /* Validate the Charge Process Files Path */
   DirPtr = NULL;
   DirPtr = opendir(gChargeProcessFilesDir);

   if(!DirPtr)
   {
      TRACEENTRY(1,"%s-%s-","gChargeProcessFilesDir :",gChargeProcessFilesDir);
      TRACEENTRY(1,"%s","Invalid PROCESS_DIR Specified in PM_PROCESS_DETAILS table for Charge TAPIN Files");
      TRACEENTRY(1,"%s -%s-","FILE_TYPE_INDICATOR :",stProcessDtls.CHARGE_FILE_TYPE_INDICATOR);
      TRACEENTRY(1,"%s -%s-","PROCESS_FILES_DIR   :",stProcessDtls.CHARGE_PROCESS_FILES_DIR);
      return -1;
   }
   closedir(DirPtr);


   /* Validate the Charge Error Files Path */
   DirPtr = NULL;
   DirPtr = opendir(gChargeErrorFilesDir);

   if(!DirPtr)
   {
      TRACEENTRY(1,"%s-%s-","gChargeErrorFilesDir :",gChargeErrorFilesDir);
      TRACEENTRY(1,"%s","Invalid ERROR_DIR Specified in PM_PROCESS_DETAILS table for Charge TAPIN Files");
      TRACEENTRY(1,"%s -%s-","FILE_TYPE_INDICATOR :",stProcessDtls.CHARGE_FILE_TYPE_INDICATOR);
      TRACEENTRY(1,"%s -%s-","ERROR_FILES_DIR     :",stProcessDtls.CHARGE_ERROR_FILES_DIR);
      return -1;
   }
   closedir(DirPtr);

   /* Validate the Charge Success Files Path */
   if(strcmp(stProcessDtls.CHARGE_TOUCHFILES_FLG,"Y")==0)
   {
      DirPtr = NULL;
      DirPtr = opendir(gChargeSuccessDir);

      if(!DirPtr)
      {
         TRACEENTRY(1,"%s-%s-","gChargeSuccessDir :",gChargeSuccessDir);
         TRACEENTRY(1,"%s","Invalid SUCCESS_DIR Specified in PM_PROCESS_DETAILS table for Charge TAPIN Files");
         TRACEENTRY(1,"%s -%s-","FILE_TYPE_INDICATOR :",stProcessDtls.CHARGE_FILE_TYPE_INDICATOR);
         TRACEENTRY(1,"%s -%s-","ERROR_FILES_DIR     :",stProcessDtls.CHARGE_ERROR_FILES_DIR);
         return -1;
      }
      closedir(DirPtr);
   }

   /* Set the Success Path for Charge files if available */
   if(strcmp(stProcessDtls.CHARGE_TOUCHFILES_FLG,"Y")==0)
   {
      sprintf(gReadChargeFilePath,"%s",gChargeSuccessDir);
   }
   else
   {
      sprintf(gReadChargeFilePath,"%s",gChargeFilesDir);
   }

   /* Validate the Home Directory if present for Test Files */
   INIT_STR(gTestFilesDir);
   INIT_STR(gTestProcessFilesDir);
   INIT_STR(gTestErrorFilesDir);
   INIT_STR(gTestSuccessDir);

   if(strcmp(stProcessDtls.TEST_HOME_DIR_FLG,"Y")==0)
   {
      DirPtr = NULL;
      DirPtr = opendir(stProcessDtls.TEST_HOME_DIR);

      if(!DirPtr)
      {
         TRACEENTRY(1,"%s","Invalid HOME_DIR Specified in PM_PROCESS_DETAILS table for Test TAPIN Files");
         return -1;
      }
      closedir(DirPtr);

      if(stProcessDtls.TEST_HOME_DIR[strlen(stProcessDtls.TEST_HOME_DIR)-1]=='/')
      {
         stProcessDtls.TEST_HOME_DIR[strlen(stProcessDtls.TEST_HOME_DIR)-1]='\0';
      }

      /* Form the Test File Directory and then check if it is a valid path */
      sprintf(gTestFilesDir,"%s/%s",stProcessDtls.TEST_HOME_DIR,stProcessDtls.TEST_FILES_DIR);

      /* Form the Test Process File Directory */
      sprintf(gTestProcessFilesDir,"%s/%s",stProcessDtls.TEST_HOME_DIR,stProcessDtls.TEST_PROCESS_FILES_DIR);

      /* Form the Test Error File Directory */
      sprintf(gTestErrorFilesDir,"%s/%s",stProcessDtls.TEST_HOME_DIR,stProcessDtls.TEST_ERROR_FILES_DIR);

      /* Form the Success File Directory */
      if(strcmp(stProcessDtls.TEST_TOUCHFILES_FLG,"Y")==0)
      {
         sprintf(gTestSuccessDir,"%s/%s",stProcessDtls.TEST_HOME_DIR,stProcessDtls.TEST_SUCCESS_FILES_DIR);
      }
   }
   else
   {
      /* Form the Test File Directory */
      sprintf(gTestFilesDir,"%s",stProcessDtls.TEST_FILES_DIR);

      /* Form the Test Process File Directory */
      sprintf(gTestProcessFilesDir,"%s",stProcessDtls.TEST_PROCESS_FILES_DIR);

      /* Form the Test Error File Directory */
      sprintf(gTestErrorFilesDir,"%s",stProcessDtls.TEST_ERROR_FILES_DIR);

      /* Form the Success File Directory */
      if(strcmp(stProcessDtls.TEST_TOUCHFILES_FLG,"Y")==0)
      {
         sprintf(gTestSuccessDir,"%s",stProcessDtls.TEST_SUCCESS_FILES_DIR);
      }
   }

   /* Validate the Test Files Path */
   DirPtr = NULL;
   DirPtr = opendir(gTestFilesDir);
   if(!DirPtr)
   {
      TRACEENTRY(1,"%s-%s-","gTestFilesDir :",gTestFilesDir);
      TRACEENTRY(1,"%s","Invalid FILES_DIR Specified in PM_PROCESS_DETAILS table for Test TAPIN Files");
      TRACEENTRY(1,"%s -%s-","FILE_TYPE_INDICATOR :",stProcessDtls.TEST_FILE_TYPE_INDICATOR);
      TRACEENTRY(1,"%s -%s-","FILES_DIR           :",stProcessDtls.TEST_FILES_DIR);
      return -1;
   }
   closedir(DirPtr);

   /* Validate the Test Process Files Path */
   DirPtr = NULL;
   DirPtr = opendir(gTestProcessFilesDir);

   if(!DirPtr)
   {
      TRACEENTRY(1,"%s-%s-","gTestProcessFilesDir :",gTestProcessFilesDir);
      TRACEENTRY(1,"%s","Invalid PROCESS_DIR Specified in PM_PROCESS_DETAILS table for Test TAPIN Files");
      TRACEENTRY(1,"%s -%s-","FILE_TYPE_INDICATOR :",stProcessDtls.TEST_FILE_TYPE_INDICATOR);
      TRACEENTRY(1,"%s -%s-","PROCESS_FILES_DIR   :",stProcessDtls.TEST_PROCESS_FILES_DIR);
      return -1;
   }
   closedir(DirPtr);

   /* Validate the Test Error Files Path */
   DirPtr = NULL;
   DirPtr = opendir(gTestErrorFilesDir);

   if(!DirPtr)
   {
      TRACEENTRY(1,"%s-%s-","gTestErrorFilesDir :",gTestErrorFilesDir);
      TRACEENTRY(1,"%s","Invalid ERROR_DIR Specified in PM_PROCESS_DETAILS table for Test TAPIN Files");
      TRACEENTRY(1,"%s -%s-","FILE_TYPE_INDICATOR :",stProcessDtls.TEST_FILE_TYPE_INDICATOR);
      TRACEENTRY(1,"%s -%s-","ERROR_FILES_DIR     :",stProcessDtls.TEST_ERROR_FILES_DIR);
      return -1;
   }
   closedir(DirPtr);

   /* Validate the Test Success Files Path */
   if(strcmp(stProcessDtls.TEST_TOUCHFILES_FLG,"Y")==0)
   {
      DirPtr = NULL;
      DirPtr = opendir(gTestSuccessDir);

      if(!DirPtr)
      {
         TRACEENTRY(1,"%s-%s-","gTestSuccessDir :",gTestSuccessDir);
         TRACEENTRY(1,"%s","Invalid SUCESS_DIR Specified in PM_PROCESS_DETAILS table for Test TAPIN Files");
         TRACEENTRY(1,"%s -%s-","FILE_TYPE_INDICATOR :",stProcessDtls.CHARGE_FILE_TYPE_INDICATOR);
         TRACEENTRY(1,"%s -%s-","ERROR_FILES_DIR     :",stProcessDtls.CHARGE_ERROR_FILES_DIR);
         return -1;
      }
      closedir(DirPtr);
   }

   /* Set the Success Path for Test files if available */
   if(strcmp(stProcessDtls.TEST_TOUCHFILES_FLG,"Y")==0)
   {
      sprintf(gReadTestFilePath,"%s",gTestSuccessDir);
   }
   else
   {
      sprintf(gReadTestFilePath,"%s",gTestFilesDir);
   }


   /****************************************************************************************************/
   /* Get RAP Partner File Information Details */

   gRAPPartnerCount=0;
   RAPPartnerCount=0;
   /* EXEC SQL SELECT COUNT(1)
              INTO :RAPPartnerCount
              FROM PM_PARTNER A, PM_ROAM_PARTNER_FILE_INFO B, PM_ROAM_PARTNER_ADDN_INFO C
             WHERE A.PARTNER_CODE       = B.PARTNER_CODE
               AND A.PARTNER_CODE       = C.PARTNER_CODE
               /o AND B.GENERATE_FILES_FLG = 'Y' o/
               AND B.PROCESS_ID         = :gRAPProcessId; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 53;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select count(1) into :b0  from PM_PARTNER A ,PM_ROAM_PARTN\
ER_FILE_INFO B ,PM_ROAM_PARTNER_ADDN_INFO C where ((A.PARTNER_CODE=B.PARTNER_C\
ODE and A.PARTNER_CODE=C.PARTNER_CODE) and B.PROCESS_ID=:b1)";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )1760;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&RAPPartnerCount;
   sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)&gRAPProcessId;
   sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   /* Check for Error in Execution */
   if(RAPPartnerCount==0)
   {
      TRACEENTRY(1,"%s -%d-","Number of Partners for RAPOUT File Generation is Zero",RAPPartnerCount);
   }
   else if(ERRCODE != 0)
   {
      TRACEENTRY(1,"%s -%d-","Error Fetching Count from PM_PARTNER and PM_ROAM_PARTNER_FILE_INFO tables for RAP ProcessID",gRAPProcessId);
      TRACEENTRY(1,"%s -%d-","sqlca.sqlcode",ERRCODE);
      return -1;
   }

   if(RAPPartnerCount > 0)
   {
         /* Allocate memmory to the partners */
         ptRAPPartners1 = (PM_RAP_PARTNERS*) \
                             malloc(RAPPartnerCount * sizeof(PM_RAP_PARTNERS));

         if(ptRAPPartners1 == NULL)
         {
               TRACEENTRY(1,"%s","Memory allocation error for RAP Partners");
               stErrors.ERROR_CODE = 0;
               strcpy(stErrors.ERROR_DESC,"Memory allocation error for RAP Partners");
               return -1;
         }



         for(i=0;i<RAPPartnerCount;i++)
         {
             ptRAPPartners2 = (ptRAPPartners1 + i);
             /* EXEC SQL VAR ptRAPPartners2->PARTNER_CODE          IS STRING(4); */ 

             /* EXEC SQL VAR ptRAPPartners2->PARTNER_SHORT_CODE    IS STRING(7); */ 

             /* EXEC SQL VAR ptRAPPartners2->DATA_TYPE             IS STRING(2); */ 

             ptRAPPartners2->FILE_SEQUENCE_NUMBER               = 0;
             /* EXEC SQL VAR ptRAPPartners2->GENERATE_FILES_FLG    IS STRING(2); */ 

             /* EXEC SQL VAR ptRAPPartners2->USE_GLOBAL_PARAMS_FLG IS STRING(2); */ 

             /* EXEC SQL VAR ptRAPPartners2->FILES_DIRECTORY       IS STRING(101); */ 

             /* EXEC SQL VAR ptRAPPartners2->SUCCESS_DIRECTORY     IS STRING(101); */ 

             /* EXEC SQL VAR ptRAPPartners2->CHECK_CALL_AGE_FLG    IS STRING(2); */ 

             ptRAPPartners2->CALL_AGE                           = 0;
         }

         /* Fetch the data into local array */
         /* EXEC SQL DECLARE RP CURSOR FOR
                   SELECT A.PARTNER_CODE,
                          /otrim(A.PARTNER_SHORT_CODE),o/
                          /o NVL(trim(C.ALIAS_TADIG_CODE),trim(A.PARTNER_SHORT_CODE)),
			  Added by Sangram to pick the ALIAS_TADIG_CODE o/
			  NVL(DECODE(trim(B.CHECK_ALIAS_TADIG),'Y',trim(C.ALIAS_TADIG_CODE),trim(A.PARTNER_SHORT_CODE)),' '),
                          nvl(trim(B.DATA_TYPE),' '),
                          nvl(B.FILE_SEQUENCE_NUMBER,0),
                          nvl(trim(B.GENERATE_FILES_FLG),' '),
                          nvl(trim(B.USE_GLOBAL_PARAMS_FLG),' '),
                          nvl(trim(B.FILES_DIRECTORY),' '),
                          nvl(trim(B.SUCCESS_DIRECTORY),' '),
                          nvl(trim(B.CHECK_CALL_AGE_FLG),' '),
                          nvl(B.CALL_AGE,0)
                     FROM PM_PARTNER A, PM_ROAM_PARTNER_FILE_INFO B, PM_ROAM_PARTNER_ADDN_INFO C
                    WHERE A.PARTNER_CODE       = B.PARTNER_CODE
                      AND A.PARTNER_CODE       = C.PARTNER_CODE
                     /o AND B.GENERATE_FILES_FLG = 'Y' o/
                      AND B.PROCESS_ID         = :gRAPProcessId
                 ORDER BY A.PARTNER_CODE; */ 


         /* EXEC SQL OPEN RP; */ 

{
         struct sqlexd sqlstm;
         sqlstm.sqlvsn = 12;
         sqlstm.arrsiz = 53;
         sqlstm.sqladtp = &sqladt;
         sqlstm.sqltdsp = &sqltds;
         sqlstm.stmt = sq0061;
         sqlstm.iters = (unsigned int  )1;
         sqlstm.offset = (unsigned int  )1783;
         sqlstm.selerr = (unsigned short)20000;
         sqlstm.cud = sqlcud0;
         sqlstm.sqlest = (unsigned char  *)&sqlca;
         sqlstm.sqlety = (unsigned short)4352;
         sqlstm.occurs = (unsigned int  )0;
         sqlstm.sqcmod = (unsigned int )0;
         sqlstm.sqhstv[0] = (         void  *)&gRAPProcessId;
         sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[0] = (         int  )0;
         sqlstm.sqindv[0] = (         void  *)0;
         sqlstm.sqinds[0] = (         int  )0;
         sqlstm.sqharm[0] = (unsigned int  )0;
         sqlstm.sqadto[0] = (unsigned short )0;
         sqlstm.sqtdso[0] = (unsigned short )0;
         sqlstm.sqphsv = sqlstm.sqhstv;
         sqlstm.sqphsl = sqlstm.sqhstl;
         sqlstm.sqphss = sqlstm.sqhsts;
         sqlstm.sqpind = sqlstm.sqindv;
         sqlstm.sqpins = sqlstm.sqinds;
         sqlstm.sqparm = sqlstm.sqharm;
         sqlstm.sqparc = sqlstm.sqharc;
         sqlstm.sqpadto = sqlstm.sqadto;
         sqlstm.sqptdso = sqlstm.sqtdso;
         sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


         /* EXEC SQL FOR :RAPPartnerCount FETCH RP INTO :ptRAPPartners1; */ 

{
         struct sqlexd sqlstm;
         sqlstm.sqlvsn = 12;
         sqlstm.arrsiz = 53;
         sqlstm.sqladtp = &sqladt;
         sqlstm.sqltdsp = &sqltds;
         sqlstm.iters = (unsigned int  )RAPPartnerCount;
         sqlstm.offset = (unsigned int  )1802;
         sqlstm.selerr = (unsigned short)20000;
         sqlstm.cud = sqlcud0;
         sqlstm.sqlest = (unsigned char  *)&sqlca;
         sqlstm.sqlety = (unsigned short)4352;
         sqlstm.occurs = (unsigned int  )0;
         sqlstm.sqfoff = (           int )0;
         sqlstm.sqfmod = (unsigned int )2;
         sqlstm.sqhstv[0] = (         void  *)ptRAPPartners1->PARTNER_CODE;
         sqlstm.sqhstl[0] = (unsigned int  )4;
         sqlstm.sqhsts[0] = (         int  )sizeof(struct PM_RAP_PARTNERS);
         sqlstm.sqindv[0] = (         void  *)0;
         sqlstm.sqinds[0] = (         int  )0;
         sqlstm.sqharm[0] = (unsigned int  )0;
         sqlstm.sqadto[0] = (unsigned short )0;
         sqlstm.sqtdso[0] = (unsigned short )0;
         sqlstm.sqhstv[1] = (         void  *)ptRAPPartners1->PARTNER_SHORT_CODE;
         sqlstm.sqhstl[1] = (unsigned int  )7;
         sqlstm.sqhsts[1] = (         int  )sizeof(struct PM_RAP_PARTNERS);
         sqlstm.sqindv[1] = (         void  *)0;
         sqlstm.sqinds[1] = (         int  )0;
         sqlstm.sqharm[1] = (unsigned int  )0;
         sqlstm.sqadto[1] = (unsigned short )0;
         sqlstm.sqtdso[1] = (unsigned short )0;
         sqlstm.sqhstv[2] = (         void  *)ptRAPPartners1->DATA_TYPE;
         sqlstm.sqhstl[2] = (unsigned int  )2;
         sqlstm.sqhsts[2] = (         int  )sizeof(struct PM_RAP_PARTNERS);
         sqlstm.sqindv[2] = (         void  *)0;
         sqlstm.sqinds[2] = (         int  )0;
         sqlstm.sqharm[2] = (unsigned int  )0;
         sqlstm.sqadto[2] = (unsigned short )0;
         sqlstm.sqtdso[2] = (unsigned short )0;
         sqlstm.sqhstv[3] = (         void  *)&ptRAPPartners1->FILE_SEQUENCE_NUMBER;
         sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[3] = (         int  )sizeof(struct PM_RAP_PARTNERS);
         sqlstm.sqindv[3] = (         void  *)0;
         sqlstm.sqinds[3] = (         int  )0;
         sqlstm.sqharm[3] = (unsigned int  )0;
         sqlstm.sqadto[3] = (unsigned short )0;
         sqlstm.sqtdso[3] = (unsigned short )0;
         sqlstm.sqhstv[4] = (         void  *)ptRAPPartners1->GENERATE_FILES_FLG;
         sqlstm.sqhstl[4] = (unsigned int  )2;
         sqlstm.sqhsts[4] = (         int  )sizeof(struct PM_RAP_PARTNERS);
         sqlstm.sqindv[4] = (         void  *)0;
         sqlstm.sqinds[4] = (         int  )0;
         sqlstm.sqharm[4] = (unsigned int  )0;
         sqlstm.sqadto[4] = (unsigned short )0;
         sqlstm.sqtdso[4] = (unsigned short )0;
         sqlstm.sqhstv[5] = (         void  *)ptRAPPartners1->USE_GLOBAL_PARAMS_FLG;
         sqlstm.sqhstl[5] = (unsigned int  )2;
         sqlstm.sqhsts[5] = (         int  )sizeof(struct PM_RAP_PARTNERS);
         sqlstm.sqindv[5] = (         void  *)0;
         sqlstm.sqinds[5] = (         int  )0;
         sqlstm.sqharm[5] = (unsigned int  )0;
         sqlstm.sqadto[5] = (unsigned short )0;
         sqlstm.sqtdso[5] = (unsigned short )0;
         sqlstm.sqhstv[6] = (         void  *)ptRAPPartners1->FILES_DIRECTORY;
         sqlstm.sqhstl[6] = (unsigned int  )101;
         sqlstm.sqhsts[6] = (         int  )sizeof(struct PM_RAP_PARTNERS);
         sqlstm.sqindv[6] = (         void  *)0;
         sqlstm.sqinds[6] = (         int  )0;
         sqlstm.sqharm[6] = (unsigned int  )0;
         sqlstm.sqadto[6] = (unsigned short )0;
         sqlstm.sqtdso[6] = (unsigned short )0;
         sqlstm.sqhstv[7] = (         void  *)ptRAPPartners1->SUCCESS_DIRECTORY;
         sqlstm.sqhstl[7] = (unsigned int  )101;
         sqlstm.sqhsts[7] = (         int  )sizeof(struct PM_RAP_PARTNERS);
         sqlstm.sqindv[7] = (         void  *)0;
         sqlstm.sqinds[7] = (         int  )0;
         sqlstm.sqharm[7] = (unsigned int  )0;
         sqlstm.sqadto[7] = (unsigned short )0;
         sqlstm.sqtdso[7] = (unsigned short )0;
         sqlstm.sqhstv[8] = (         void  *)ptRAPPartners1->CHECK_CALL_AGE_FLG;
         sqlstm.sqhstl[8] = (unsigned int  )2;
         sqlstm.sqhsts[8] = (         int  )sizeof(struct PM_RAP_PARTNERS);
         sqlstm.sqindv[8] = (         void  *)0;
         sqlstm.sqinds[8] = (         int  )0;
         sqlstm.sqharm[8] = (unsigned int  )0;
         sqlstm.sqadto[8] = (unsigned short )0;
         sqlstm.sqtdso[8] = (unsigned short )0;
         sqlstm.sqhstv[9] = (         void  *)&ptRAPPartners1->CALL_AGE;
         sqlstm.sqhstl[9] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[9] = (         int  )sizeof(struct PM_RAP_PARTNERS);
         sqlstm.sqindv[9] = (         void  *)0;
         sqlstm.sqinds[9] = (         int  )0;
         sqlstm.sqharm[9] = (unsigned int  )0;
         sqlstm.sqadto[9] = (unsigned short )0;
         sqlstm.sqtdso[9] = (unsigned short )0;
         sqlstm.sqphsv = sqlstm.sqhstv;
         sqlstm.sqphsl = sqlstm.sqhstl;
         sqlstm.sqphss = sqlstm.sqhsts;
         sqlstm.sqpind = sqlstm.sqindv;
         sqlstm.sqpins = sqlstm.sqinds;
         sqlstm.sqparm = sqlstm.sqharm;
         sqlstm.sqparc = sqlstm.sqharc;
         sqlstm.sqpadto = sqlstm.sqadto;
         sqlstm.sqptdso = sqlstm.sqtdso;
         sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


         /* EXEC SQL CLOSE RP; */ 

{
         struct sqlexd sqlstm;
         sqlstm.sqlvsn = 12;
         sqlstm.arrsiz = 53;
         sqlstm.sqladtp = &sqladt;
         sqlstm.sqltdsp = &sqltds;
         sqlstm.iters = (unsigned int  )1;
         sqlstm.offset = (unsigned int  )1857;
         sqlstm.cud = sqlcud0;
         sqlstm.sqlest = (unsigned char  *)&sqlca;
         sqlstm.sqlety = (unsigned short)4352;
         sqlstm.occurs = (unsigned int  )0;
         sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}




         if(ERRCODE != 0)
         {
               TRACEENTRY(1,"%s","Error Fetching RAP Data from PM_PARTNER and PM_ROAM_PARTNER_FILE_INFO tables");
               TRACEENTRY(1,"%s -%d-","sqlca.sqlcode",ERRCODE);
               stErrors.ERROR_CODE = sqlca.sqlcode;
               strcpy(stErrors.ERROR_DESC,"Error Fetching RAP Data from PM_PARTNER and PM_ROAM_PARTNER_FILE_INFO tables");
               return -1;
         }

         gRAPPartnerCount = RAPPartnerCount;


         /* Get the file directory information for charge and test files */
         /* EXEC SQL VAR stRAPProcessDtls.CHARGE_FILE_TYPE_INDICATOR IS STRING(2)  ; */ 

         /* EXEC SQL VAR stRAPProcessDtls.CHARGE_HOME_DIR_FLG        IS STRING(2)  ; */ 

         /* EXEC SQL VAR stRAPProcessDtls.CHARGE_HOME_DIR	          IS STRING(101); */ 

         /* EXEC SQL VAR stRAPProcessDtls.CHARGE_FILES_DIR           IS STRING(101); */ 

         /* EXEC SQL VAR stRAPProcessDtls.CHARGE_PROCESS_FILES_DIR   IS STRING(101); */ 

         /* EXEC SQL VAR stRAPProcessDtls.CHARGE_ERROR_FILES_DIR     IS STRING(101); */ 

         /* EXEC SQL VAR stRAPProcessDtls.CHARGE_TOUCHFILES_FLG      IS STRING(2)  ; */ 

         /* EXEC SQL VAR stRAPProcessDtls.CHARGE_SUCCESS_FILES_DIR   IS STRING(101); */ 

   
         /* EXEC SQL VAR stRAPProcessDtls.TEST_FILE_TYPE_INDICATOR   IS STRING(2)  ; */ 

         /* EXEC SQL VAR stRAPProcessDtls.TEST_HOME_DIR_FLG          IS STRING(2)  ; */ 

         /* EXEC SQL VAR stRAPProcessDtls.TEST_HOME_DIR              IS STRING(101); */ 

         /* EXEC SQL VAR stRAPProcessDtls.TEST_FILES_DIR             IS STRING(101); */ 

         /* EXEC SQL VAR stRAPProcessDtls.TEST_PROCESS_FILES_DIR     IS STRING(101); */ 

         /* EXEC SQL VAR stRAPProcessDtls.TEST_ERROR_FILES_DIR       IS STRING(101); */ 

         /* EXEC SQL VAR stRAPProcessDtls.TEST_TOUCHFILES_FLG        IS STRING(2)  ; */ 

         /* EXEC SQL VAR stRAPProcessDtls.TEST_SUCCESS_FILES_DIR     IS STRING(101); */ 


         /* EXEC SQL SELECT nvl(TRIM(A.FILE_TYPE_INDICATOR),' ')   ,
                         nvl(TRIM(A.HOME_DIR_FLG),' ')          ,
                         nvl(TRIM(A.HOME_DIR),' ')              ,
                         nvl(TRIM(A.FILES_DIR),' ')             ,
                         nvl(TRIM(A.PROCESS_FILES_DIR),' ')     ,
                         nvl(TRIM(A.ERROR_FILES_DIR),' ')       ,
		         NVL(TRIM(A.TOUCHFILES_FLG),' ')        ,
                         NVL(TRIM(A.SUCCESS_FILES_DIR),' ')     ,
                         nvl(TRIM(B.FILE_TYPE_INDICATOR),' ')   ,
                         nvl(TRIM(B.HOME_DIR_FLG),' ')          ,
                         nvl(TRIM(B.HOME_DIR),' ')              ,
                         nvl(TRIM(B.FILES_DIR),' ')             ,
                         nvl(TRIM(B.PROCESS_FILES_DIR),' ')     ,
                         nvl(TRIM(B.ERROR_FILES_DIR),' ')       ,
                         NVL(TRIM(B.TOUCHFILES_FLG),' ')        ,
                         NVL(TRIM(B.SUCCESS_FILES_DIR),' ')
                   INTO :stRAPProcessDtls.CHARGE_FILE_TYPE_INDICATOR ,
                        :stRAPProcessDtls.CHARGE_HOME_DIR_FLG        ,
                        :stRAPProcessDtls.CHARGE_HOME_DIR            ,
                        :stRAPProcessDtls.CHARGE_FILES_DIR           ,
                        :stRAPProcessDtls.CHARGE_PROCESS_FILES_DIR   ,
                        :stRAPProcessDtls.CHARGE_ERROR_FILES_DIR     ,
                        :stRAPProcessDtls.CHARGE_TOUCHFILES_FLG      ,
                        :stRAPProcessDtls.CHARGE_SUCCESS_FILES_DIR   ,
	                :stRAPProcessDtls.TEST_FILE_TYPE_INDICATOR   ,
                        :stRAPProcessDtls.TEST_HOME_DIR_FLG          ,
                        :stRAPProcessDtls.TEST_HOME_DIR              ,
                        :stRAPProcessDtls.TEST_FILES_DIR             ,
                        :stRAPProcessDtls.TEST_PROCESS_FILES_DIR     ,
                        :stRAPProcessDtls.TEST_ERROR_FILES_DIR       ,
                        :stRAPProcessDtls.TEST_TOUCHFILES_FLG        ,
                        :stRAPProcessDtls.TEST_SUCCESS_FILES_DIR
                   FROM PM_PROCESS_DETAILS A,PM_PROCESS_DETAILS B
                  WHERE A.PROCESS_ID = :gRAPProcessId
                    AND A.FILE_TYPE_INDICATOR='C'
                    AND B.PROCESS_ID = :gRAPProcessId
                    AND B.FILE_TYPE_INDICATOR='T'; */ 

{
         struct sqlexd sqlstm;
         sqlstm.sqlvsn = 12;
         sqlstm.arrsiz = 53;
         sqlstm.sqladtp = &sqladt;
         sqlstm.sqltdsp = &sqltds;
         sqlstm.stmt = "select nvl(trim(A.FILE_TYPE_INDICATOR),' ') ,nvl(tri\
m(A.HOME_DIR_FLG),' ') ,nvl(trim(A.HOME_DIR),' ') ,nvl(trim(A.FILES_DIR),' ') \
,nvl(trim(A.PROCESS_FILES_DIR),' ') ,nvl(trim(A.ERROR_FILES_DIR),' ') ,NVL(tri\
m(A.TOUCHFILES_FLG),' ') ,NVL(trim(A.SUCCESS_FILES_DIR),' ') ,nvl(trim(B.FILE_\
TYPE_INDICATOR),' ') ,nvl(trim(B.HOME_DIR_FLG),' ') ,nvl(trim(B.HOME_DIR),' ')\
 ,nvl(trim(B.FILES_DIR),' ') ,nvl(trim(B.PROCESS_FILES_DIR),' ') ,nvl(trim(B.E\
RROR_FILES_DIR),' ') ,NVL(trim(B.TOUCHFILES_FLG),' ') ,NVL(trim(B.SUCCESS_FILE\
S_DIR),' ') into :b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b11,:b12,:b13,:\
b14,:b15  from PM_PROCESS_DETAILS A ,PM_PROCESS_DETAILS B where (((A.PROCESS_I\
D=:b16 and A.FILE_TYPE_INDICATOR='C') and B.PROCESS_ID=:b16) and B.FILE_TYPE_I\
NDICATOR='T')";
         sqlstm.iters = (unsigned int  )1;
         sqlstm.offset = (unsigned int  )1872;
         sqlstm.selerr = (unsigned short)1;
         sqlstm.cud = sqlcud0;
         sqlstm.sqlest = (unsigned char  *)&sqlca;
         sqlstm.sqlety = (unsigned short)4352;
         sqlstm.occurs = (unsigned int  )0;
         sqlstm.sqhstv[0] = (         void  *)(stRAPProcessDtls.CHARGE_FILE_TYPE_INDICATOR);
         sqlstm.sqhstl[0] = (unsigned int  )2;
         sqlstm.sqhsts[0] = (         int  )0;
         sqlstm.sqindv[0] = (         void  *)0;
         sqlstm.sqinds[0] = (         int  )0;
         sqlstm.sqharm[0] = (unsigned int  )0;
         sqlstm.sqadto[0] = (unsigned short )0;
         sqlstm.sqtdso[0] = (unsigned short )0;
         sqlstm.sqhstv[1] = (         void  *)(stRAPProcessDtls.CHARGE_HOME_DIR_FLG);
         sqlstm.sqhstl[1] = (unsigned int  )2;
         sqlstm.sqhsts[1] = (         int  )0;
         sqlstm.sqindv[1] = (         void  *)0;
         sqlstm.sqinds[1] = (         int  )0;
         sqlstm.sqharm[1] = (unsigned int  )0;
         sqlstm.sqadto[1] = (unsigned short )0;
         sqlstm.sqtdso[1] = (unsigned short )0;
         sqlstm.sqhstv[2] = (         void  *)(stRAPProcessDtls.CHARGE_HOME_DIR);
         sqlstm.sqhstl[2] = (unsigned int  )101;
         sqlstm.sqhsts[2] = (         int  )0;
         sqlstm.sqindv[2] = (         void  *)0;
         sqlstm.sqinds[2] = (         int  )0;
         sqlstm.sqharm[2] = (unsigned int  )0;
         sqlstm.sqadto[2] = (unsigned short )0;
         sqlstm.sqtdso[2] = (unsigned short )0;
         sqlstm.sqhstv[3] = (         void  *)(stRAPProcessDtls.CHARGE_FILES_DIR);
         sqlstm.sqhstl[3] = (unsigned int  )101;
         sqlstm.sqhsts[3] = (         int  )0;
         sqlstm.sqindv[3] = (         void  *)0;
         sqlstm.sqinds[3] = (         int  )0;
         sqlstm.sqharm[3] = (unsigned int  )0;
         sqlstm.sqadto[3] = (unsigned short )0;
         sqlstm.sqtdso[3] = (unsigned short )0;
         sqlstm.sqhstv[4] = (         void  *)(stRAPProcessDtls.CHARGE_PROCESS_FILES_DIR);
         sqlstm.sqhstl[4] = (unsigned int  )101;
         sqlstm.sqhsts[4] = (         int  )0;
         sqlstm.sqindv[4] = (         void  *)0;
         sqlstm.sqinds[4] = (         int  )0;
         sqlstm.sqharm[4] = (unsigned int  )0;
         sqlstm.sqadto[4] = (unsigned short )0;
         sqlstm.sqtdso[4] = (unsigned short )0;
         sqlstm.sqhstv[5] = (         void  *)(stRAPProcessDtls.CHARGE_ERROR_FILES_DIR);
         sqlstm.sqhstl[5] = (unsigned int  )101;
         sqlstm.sqhsts[5] = (         int  )0;
         sqlstm.sqindv[5] = (         void  *)0;
         sqlstm.sqinds[5] = (         int  )0;
         sqlstm.sqharm[5] = (unsigned int  )0;
         sqlstm.sqadto[5] = (unsigned short )0;
         sqlstm.sqtdso[5] = (unsigned short )0;
         sqlstm.sqhstv[6] = (         void  *)(stRAPProcessDtls.CHARGE_TOUCHFILES_FLG);
         sqlstm.sqhstl[6] = (unsigned int  )2;
         sqlstm.sqhsts[6] = (         int  )0;
         sqlstm.sqindv[6] = (         void  *)0;
         sqlstm.sqinds[6] = (         int  )0;
         sqlstm.sqharm[6] = (unsigned int  )0;
         sqlstm.sqadto[6] = (unsigned short )0;
         sqlstm.sqtdso[6] = (unsigned short )0;
         sqlstm.sqhstv[7] = (         void  *)(stRAPProcessDtls.CHARGE_SUCCESS_FILES_DIR);
         sqlstm.sqhstl[7] = (unsigned int  )101;
         sqlstm.sqhsts[7] = (         int  )0;
         sqlstm.sqindv[7] = (         void  *)0;
         sqlstm.sqinds[7] = (         int  )0;
         sqlstm.sqharm[7] = (unsigned int  )0;
         sqlstm.sqadto[7] = (unsigned short )0;
         sqlstm.sqtdso[7] = (unsigned short )0;
         sqlstm.sqhstv[8] = (         void  *)(stRAPProcessDtls.TEST_FILE_TYPE_INDICATOR);
         sqlstm.sqhstl[8] = (unsigned int  )2;
         sqlstm.sqhsts[8] = (         int  )0;
         sqlstm.sqindv[8] = (         void  *)0;
         sqlstm.sqinds[8] = (         int  )0;
         sqlstm.sqharm[8] = (unsigned int  )0;
         sqlstm.sqadto[8] = (unsigned short )0;
         sqlstm.sqtdso[8] = (unsigned short )0;
         sqlstm.sqhstv[9] = (         void  *)(stRAPProcessDtls.TEST_HOME_DIR_FLG);
         sqlstm.sqhstl[9] = (unsigned int  )2;
         sqlstm.sqhsts[9] = (         int  )0;
         sqlstm.sqindv[9] = (         void  *)0;
         sqlstm.sqinds[9] = (         int  )0;
         sqlstm.sqharm[9] = (unsigned int  )0;
         sqlstm.sqadto[9] = (unsigned short )0;
         sqlstm.sqtdso[9] = (unsigned short )0;
         sqlstm.sqhstv[10] = (         void  *)(stRAPProcessDtls.TEST_HOME_DIR);
         sqlstm.sqhstl[10] = (unsigned int  )101;
         sqlstm.sqhsts[10] = (         int  )0;
         sqlstm.sqindv[10] = (         void  *)0;
         sqlstm.sqinds[10] = (         int  )0;
         sqlstm.sqharm[10] = (unsigned int  )0;
         sqlstm.sqadto[10] = (unsigned short )0;
         sqlstm.sqtdso[10] = (unsigned short )0;
         sqlstm.sqhstv[11] = (         void  *)(stRAPProcessDtls.TEST_FILES_DIR);
         sqlstm.sqhstl[11] = (unsigned int  )101;
         sqlstm.sqhsts[11] = (         int  )0;
         sqlstm.sqindv[11] = (         void  *)0;
         sqlstm.sqinds[11] = (         int  )0;
         sqlstm.sqharm[11] = (unsigned int  )0;
         sqlstm.sqadto[11] = (unsigned short )0;
         sqlstm.sqtdso[11] = (unsigned short )0;
         sqlstm.sqhstv[12] = (         void  *)(stRAPProcessDtls.TEST_PROCESS_FILES_DIR);
         sqlstm.sqhstl[12] = (unsigned int  )101;
         sqlstm.sqhsts[12] = (         int  )0;
         sqlstm.sqindv[12] = (         void  *)0;
         sqlstm.sqinds[12] = (         int  )0;
         sqlstm.sqharm[12] = (unsigned int  )0;
         sqlstm.sqadto[12] = (unsigned short )0;
         sqlstm.sqtdso[12] = (unsigned short )0;
         sqlstm.sqhstv[13] = (         void  *)(stRAPProcessDtls.TEST_ERROR_FILES_DIR);
         sqlstm.sqhstl[13] = (unsigned int  )101;
         sqlstm.sqhsts[13] = (         int  )0;
         sqlstm.sqindv[13] = (         void  *)0;
         sqlstm.sqinds[13] = (         int  )0;
         sqlstm.sqharm[13] = (unsigned int  )0;
         sqlstm.sqadto[13] = (unsigned short )0;
         sqlstm.sqtdso[13] = (unsigned short )0;
         sqlstm.sqhstv[14] = (         void  *)(stRAPProcessDtls.TEST_TOUCHFILES_FLG);
         sqlstm.sqhstl[14] = (unsigned int  )2;
         sqlstm.sqhsts[14] = (         int  )0;
         sqlstm.sqindv[14] = (         void  *)0;
         sqlstm.sqinds[14] = (         int  )0;
         sqlstm.sqharm[14] = (unsigned int  )0;
         sqlstm.sqadto[14] = (unsigned short )0;
         sqlstm.sqtdso[14] = (unsigned short )0;
         sqlstm.sqhstv[15] = (         void  *)(stRAPProcessDtls.TEST_SUCCESS_FILES_DIR);
         sqlstm.sqhstl[15] = (unsigned int  )101;
         sqlstm.sqhsts[15] = (         int  )0;
         sqlstm.sqindv[15] = (         void  *)0;
         sqlstm.sqinds[15] = (         int  )0;
         sqlstm.sqharm[15] = (unsigned int  )0;
         sqlstm.sqadto[15] = (unsigned short )0;
         sqlstm.sqtdso[15] = (unsigned short )0;
         sqlstm.sqhstv[16] = (         void  *)&gRAPProcessId;
         sqlstm.sqhstl[16] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[16] = (         int  )0;
         sqlstm.sqindv[16] = (         void  *)0;
         sqlstm.sqinds[16] = (         int  )0;
         sqlstm.sqharm[16] = (unsigned int  )0;
         sqlstm.sqadto[16] = (unsigned short )0;
         sqlstm.sqtdso[16] = (unsigned short )0;
         sqlstm.sqhstv[17] = (         void  *)&gRAPProcessId;
         sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[17] = (         int  )0;
         sqlstm.sqindv[17] = (         void  *)0;
         sqlstm.sqinds[17] = (         int  )0;
         sqlstm.sqharm[17] = (unsigned int  )0;
         sqlstm.sqadto[17] = (unsigned short )0;
         sqlstm.sqtdso[17] = (unsigned short )0;
         sqlstm.sqphsv = sqlstm.sqhstv;
         sqlstm.sqphsl = sqlstm.sqhstl;
         sqlstm.sqphss = sqlstm.sqhsts;
         sqlstm.sqpind = sqlstm.sqindv;
         sqlstm.sqpins = sqlstm.sqinds;
         sqlstm.sqparm = sqlstm.sqharm;
         sqlstm.sqparc = sqlstm.sqharc;
         sqlstm.sqpadto = sqlstm.sqadto;
         sqlstm.sqptdso = sqlstm.sqtdso;
         sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


 
         /* Validate the Home Directory if present for Charge Files */
         INIT_STR(gRAPChargeFilesDir)        ;
         INIT_STR(gRAPChargeSuccessDir)      ;
         INIT_STR(gReadRAPChargeFilePath)    ;
         INIT_STR(gReadRAPTestFilePath)      ;

         if(strcmp(stRAPProcessDtls.CHARGE_HOME_DIR_FLG,"Y")==0)
         {
             DirPtr = NULL;
             DirPtr = opendir(stRAPProcessDtls.CHARGE_HOME_DIR);
             if(!DirPtr)
             {
                 TRACEENTRY(1,"%s","Invalid HOME_DIR Specified in PM_PROCESS_DETAILS table for Charge RAPOUT Files");
                 return -1;
             }
             closedir(DirPtr);

             if(stRAPProcessDtls.CHARGE_HOME_DIR[strlen(stRAPProcessDtls.CHARGE_HOME_DIR)-1]=='/')
             {
                 stRAPProcessDtls.CHARGE_HOME_DIR[strlen(stRAPProcessDtls.CHARGE_HOME_DIR)-1]='\0';
             }

             /* Form the Charge File Directory */
             sprintf(gRAPChargeFilesDir,"%s/%s",stRAPProcessDtls.CHARGE_HOME_DIR,stRAPProcessDtls.CHARGE_FILES_DIR);

             /* Form the Success File Directory */
             if(strcmp(stRAPProcessDtls.CHARGE_TOUCHFILES_FLG,"Y")==0)
             {
                 sprintf(gRAPChargeSuccessDir,"%s/%s",stRAPProcessDtls.CHARGE_HOME_DIR,stRAPProcessDtls.CHARGE_SUCCESS_FILES_DIR);
             }
         }
         else
         {
             /* Form the Charge File Directory */
             sprintf(gRAPChargeFilesDir,"%s",stRAPProcessDtls.CHARGE_FILES_DIR);

             /* Form the Success File Directory */
             if(strcmp(stRAPProcessDtls.CHARGE_TOUCHFILES_FLG,"Y")==0)
             {
                sprintf(gRAPChargeSuccessDir,"%s",stRAPProcessDtls.CHARGE_SUCCESS_FILES_DIR);
             }
         }

         /* Validate the Files Directory Path */
         DirPtr = NULL;
         DirPtr = opendir(gRAPChargeFilesDir);
         if(!DirPtr)
         {
             TRACEENTRY(1,"%s-%s-","gRAPChargeFilesDir :",gRAPChargeFilesDir);
             TRACEENTRY(1,"%s","Invalid FILES_DIR Specified in PM_PROCESS_DETAILS table for Charge RAPOUT Files");
             TRACEENTRY(1,"%s -%s-","FILE_TYPE_INDICATOR :",stRAPProcessDtls.CHARGE_FILE_TYPE_INDICATOR);
             TRACEENTRY(1,"%s -%s-","FILES_DIR           :",stRAPProcessDtls.CHARGE_FILES_DIR);
             return -1;
         }
         closedir(DirPtr);


         /* Validate the Charge Success Files Path */
         if(strcmp(stRAPProcessDtls.CHARGE_TOUCHFILES_FLG,"Y")==0)
         {
             DirPtr = NULL;
             DirPtr = opendir(gRAPChargeSuccessDir);

             if(!DirPtr)
             {
                 TRACEENTRY(1,"%s-%s-","gRAPChargeSuccessDir :",gRAPChargeSuccessDir);
                 TRACEENTRY(1,"%s","Invalid SUCCESS_DIR Specified in PM_PROCESS_DETAILS table for Charge RAPOUT Files");
                 TRACEENTRY(1,"%s -%s-","FILE_TYPE_INDICATOR :",stRAPProcessDtls.CHARGE_FILE_TYPE_INDICATOR);
                 TRACEENTRY(1,"%s -%s-","ERROR_FILES_DIR     :",stRAPProcessDtls.CHARGE_ERROR_FILES_DIR);
                 return -1;
             }
             closedir(DirPtr);
         }

         /* Set the Success Path for Charge files if available */
         if(strcmp(stRAPProcessDtls.CHARGE_TOUCHFILES_FLG,"Y")==0)
         {
             sprintf(gReadRAPChargeFilePath,"%s",gRAPChargeSuccessDir);
         }
         else
         {
             sprintf(gReadRAPChargeFilePath,"%s",gRAPChargeFilesDir);
         }

         /* Validate the Home Directory if present for Test Files */
         INIT_STR(gRAPTestFilesDir);
         INIT_STR(gRAPTestSuccessDir);

         if(strcmp(stRAPProcessDtls.TEST_HOME_DIR_FLG,"Y")==0)
         {
             DirPtr = NULL;
             DirPtr = opendir(stRAPProcessDtls.TEST_HOME_DIR);

             if(!DirPtr)
             {
                 TRACEENTRY(1,"%s","Invalid HOME_DIR Specified in PM_PROCESS_DETAILS table for Test RAPOUT Files");
                 return -1;
             }
             closedir(DirPtr);

             if(stRAPProcessDtls.TEST_HOME_DIR[strlen(stRAPProcessDtls.TEST_HOME_DIR)-1]=='/')
             {
                stRAPProcessDtls.TEST_HOME_DIR[strlen(stRAPProcessDtls.TEST_HOME_DIR)-1]='\0';
             }

             /* Form the Test File Directory and then check if it is a valid path */
             sprintf(gRAPTestFilesDir,"%s/%s",stRAPProcessDtls.TEST_HOME_DIR,stRAPProcessDtls.TEST_FILES_DIR);

             /* Form the Success File Directory */
             if(strcmp(stRAPProcessDtls.TEST_TOUCHFILES_FLG,"Y")==0)
             {
                 sprintf(gRAPTestSuccessDir,"%s/%s",stRAPProcessDtls.TEST_HOME_DIR,stRAPProcessDtls.TEST_SUCCESS_FILES_DIR);
             }
         }
         else
         {
             /* Form the Test File Directory */
             sprintf(gRAPTestFilesDir,"%s",stRAPProcessDtls.TEST_FILES_DIR);

             /* Form the Success File Directory */
             if(strcmp(stRAPProcessDtls.TEST_TOUCHFILES_FLG,"Y")==0)
             {
                sprintf(gRAPTestSuccessDir,"%s",stRAPProcessDtls.TEST_SUCCESS_FILES_DIR);
             }
         }

         /* Validate the Test Files Path */
         DirPtr = NULL;
         DirPtr = opendir(gRAPTestFilesDir);
         if(!DirPtr)
         {
             TRACEENTRY(1,"%s-%s-","gRAPTestFilesDir :",gRAPTestFilesDir);
             TRACEENTRY(1,"%s","Invalid FILES_DIR Specified in PM_PROCESS_DETAILS table for Test RAPOUT Files");
             TRACEENTRY(1,"%s -%s-","FILE_TYPE_INDICATOR :",stRAPProcessDtls.TEST_FILE_TYPE_INDICATOR);
             TRACEENTRY(1,"%s -%s-","FILES_DIR           :",stRAPProcessDtls.TEST_FILES_DIR);
             return -1;
         }
         closedir(DirPtr);

         /* Validate the Test Success Files Path */
         if(strcmp(stRAPProcessDtls.TEST_TOUCHFILES_FLG,"Y")==0)
         {
             DirPtr = NULL;
             DirPtr = opendir(gRAPTestSuccessDir);

             if(!DirPtr)
             {
                 TRACEENTRY(1,"%s-%s-","gRAPTestSuccessDir :",gRAPTestSuccessDir);
                 TRACEENTRY(1,"%s","Invalid SUCESS_DIR Specified in PM_PROCESS_DETAILS table for Test RAPOUT Files");
                 TRACEENTRY(1,"%s -%s-","FILE_TYPE_INDICATOR :",stRAPProcessDtls.CHARGE_FILE_TYPE_INDICATOR);
                 TRACEENTRY(1,"%s -%s-","ERROR_FILES_DIR     :",stRAPProcessDtls.CHARGE_ERROR_FILES_DIR);
                 return -1;
             }
             closedir(DirPtr);
         }

         /* Set the Success Path for Test files if available */
         if(strcmp(stRAPProcessDtls.TEST_TOUCHFILES_FLG,"Y")==0)
         {
             sprintf(gReadRAPTestFilePath,"%s",gRAPTestSuccessDir);
         }
         else
         {
             sprintf(gReadRAPTestFilePath,"%s",gRAPTestFilesDir);
         }
   }


   /****************************************************************************************************/
   /* Get Application Tag, Error Code and Validate Flag Details from PM_TAG_ERROR_CODES */

   gTagErrorCodeCount=0;
   TagErrorCodeCount=0;
   /* EXEC SQL SELECT COUNT(1)
              INTO :TagErrorCodeCount
              FROM PM_TAG_ERROR_CODES 
             WHERE VALIDATE_TAG = 'N'; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 53;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select count(1) into :b0  from PM_TAG_ERROR_CODES where VA\
LIDATE_TAG='N'";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )1959;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&TagErrorCodeCount;
   sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}

 

   /* Check for Error in Execution */
   if(ERRCODE != 0 || TagErrorCodeCount == 0)
   {
      TRACEENTRY(1,"%s","Error Fetching Count from PM_TAG_ERROR_CODES");
      TRACEENTRY(1,"%s -%d-","sqlca.sqlcode",ERRCODE);
      return -1;
   }

   if(TagErrorCodeCount > 0)
   {
         /* Allocate memmory to the partners */
         ptTagDetails1 = (PM_TAG_ERROR_CODES*) \
                             malloc(TagErrorCodeCount* sizeof(PM_TAG_ERROR_CODES));

         if(ptTagDetails1 == NULL)
         {
               TRACEENTRY(1,"%s","Memory allocation error for Tag and Error Codes");
               stErrors.ERROR_CODE = 0;
               strcpy(stErrors.ERROR_DESC,"Memory allocation error for Tag and Error Codes");
               return -1;
         }

         for(i=0;i<TagErrorCodeCount;i++)
         {
             ptTagDetails2 = (ptTagDetails1 + i);
             ptTagDetails2->APPLICATION_TAG                     = 0;
             /* EXEC SQL VAR ptTagDetails2->FIELD_NAME             IS STRING(51); */ 

             /* EXEC SQL VAR ptTagDetails2->ERROR_CONTEXT_NAME     IS STRING(51); */ 

             /* EXEC SQL VAR ptTagDetails2->ERROR_TYPE             IS STRING(9); */ 

             ptTagDetails2->ERROR_CODE                          = 0;
             /* EXEC SQL VAR ptTagDetails2->ERROR_MESSAGE          IS STRING(501); */ 

             /* EXEC SQL VAR ptTagDetails2->VALIDATE_TAG           IS STRING(2); */ 

         }


         /* Fetch the data into local array */
         /* EXEC SQL DECLARE TAG_ERRORS CURSOR FOR
                   SELECT nvl(APPLICATION_TAG,0)            ,
                          nvl(trim(FIELD_NAME),' ')         ,
                          nvl(trim(ERROR_CONTEXT_NAME),' ') ,
                          nvl(trim(ERROR_TYPE),' ')         ,
                          nvl(ERROR_CODE,0)                 ,
                          nvl(trim(ERROR_MESSAGE),' ')      ,
                          nvl(trim(VALIDATE_TAG),' ')
                     FROM PM_TAG_ERROR_CODES
                    WHERE VALIDATE_TAG = 'N'; */ 



         /* EXEC SQL OPEN TAG_ERRORS; */ 

{
         struct sqlexd sqlstm;
         sqlstm.sqlvsn = 12;
         sqlstm.arrsiz = 53;
         sqlstm.sqladtp = &sqladt;
         sqlstm.sqltdsp = &sqltds;
         sqlstm.stmt = sq0064;
         sqlstm.iters = (unsigned int  )1;
         sqlstm.offset = (unsigned int  )1978;
         sqlstm.selerr = (unsigned short)20000;
         sqlstm.cud = sqlcud0;
         sqlstm.sqlest = (unsigned char  *)&sqlca;
         sqlstm.sqlety = (unsigned short)4352;
         sqlstm.occurs = (unsigned int  )0;
         sqlstm.sqcmod = (unsigned int )0;
         sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


         /* EXEC SQL FOR :TagErrorCodeCount FETCH TAG_ERRORS INTO :ptTagDetails1; */ 

{
         struct sqlexd sqlstm;
         sqlstm.sqlvsn = 12;
         sqlstm.arrsiz = 53;
         sqlstm.sqladtp = &sqladt;
         sqlstm.sqltdsp = &sqltds;
         sqlstm.iters = (unsigned int  )TagErrorCodeCount;
         sqlstm.offset = (unsigned int  )1993;
         sqlstm.selerr = (unsigned short)20000;
         sqlstm.cud = sqlcud0;
         sqlstm.sqlest = (unsigned char  *)&sqlca;
         sqlstm.sqlety = (unsigned short)4352;
         sqlstm.occurs = (unsigned int  )0;
         sqlstm.sqfoff = (           int )0;
         sqlstm.sqfmod = (unsigned int )2;
         sqlstm.sqhstv[0] = (         void  *)&ptTagDetails1->APPLICATION_TAG;
         sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[0] = (         int  )sizeof(struct PM_TAG_ERROR_CODES);
         sqlstm.sqindv[0] = (         void  *)0;
         sqlstm.sqinds[0] = (         int  )0;
         sqlstm.sqharm[0] = (unsigned int  )0;
         sqlstm.sqadto[0] = (unsigned short )0;
         sqlstm.sqtdso[0] = (unsigned short )0;
         sqlstm.sqhstv[1] = (         void  *)ptTagDetails1->FIELD_NAME;
         sqlstm.sqhstl[1] = (unsigned int  )51;
         sqlstm.sqhsts[1] = (         int  )sizeof(struct PM_TAG_ERROR_CODES);
         sqlstm.sqindv[1] = (         void  *)0;
         sqlstm.sqinds[1] = (         int  )0;
         sqlstm.sqharm[1] = (unsigned int  )0;
         sqlstm.sqadto[1] = (unsigned short )0;
         sqlstm.sqtdso[1] = (unsigned short )0;
         sqlstm.sqhstv[2] = (         void  *)ptTagDetails1->ERROR_CONTEXT_NAME;
         sqlstm.sqhstl[2] = (unsigned int  )51;
         sqlstm.sqhsts[2] = (         int  )sizeof(struct PM_TAG_ERROR_CODES);
         sqlstm.sqindv[2] = (         void  *)0;
         sqlstm.sqinds[2] = (         int  )0;
         sqlstm.sqharm[2] = (unsigned int  )0;
         sqlstm.sqadto[2] = (unsigned short )0;
         sqlstm.sqtdso[2] = (unsigned short )0;
         sqlstm.sqhstv[3] = (         void  *)ptTagDetails1->ERROR_TYPE;
         sqlstm.sqhstl[3] = (unsigned int  )9;
         sqlstm.sqhsts[3] = (         int  )sizeof(struct PM_TAG_ERROR_CODES);
         sqlstm.sqindv[3] = (         void  *)0;
         sqlstm.sqinds[3] = (         int  )0;
         sqlstm.sqharm[3] = (unsigned int  )0;
         sqlstm.sqadto[3] = (unsigned short )0;
         sqlstm.sqtdso[3] = (unsigned short )0;
         sqlstm.sqhstv[4] = (         void  *)&ptTagDetails1->ERROR_CODE;
         sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[4] = (         int  )sizeof(struct PM_TAG_ERROR_CODES);
         sqlstm.sqindv[4] = (         void  *)0;
         sqlstm.sqinds[4] = (         int  )0;
         sqlstm.sqharm[4] = (unsigned int  )0;
         sqlstm.sqadto[4] = (unsigned short )0;
         sqlstm.sqtdso[4] = (unsigned short )0;
         sqlstm.sqhstv[5] = (         void  *)ptTagDetails1->ERROR_MESSAGE;
         sqlstm.sqhstl[5] = (unsigned int  )501;
         sqlstm.sqhsts[5] = (         int  )sizeof(struct PM_TAG_ERROR_CODES);
         sqlstm.sqindv[5] = (         void  *)0;
         sqlstm.sqinds[5] = (         int  )0;
         sqlstm.sqharm[5] = (unsigned int  )0;
         sqlstm.sqadto[5] = (unsigned short )0;
         sqlstm.sqtdso[5] = (unsigned short )0;
         sqlstm.sqhstv[6] = (         void  *)ptTagDetails1->VALIDATE_TAG;
         sqlstm.sqhstl[6] = (unsigned int  )2;
         sqlstm.sqhsts[6] = (         int  )sizeof(struct PM_TAG_ERROR_CODES);
         sqlstm.sqindv[6] = (         void  *)0;
         sqlstm.sqinds[6] = (         int  )0;
         sqlstm.sqharm[6] = (unsigned int  )0;
         sqlstm.sqadto[6] = (unsigned short )0;
         sqlstm.sqtdso[6] = (unsigned short )0;
         sqlstm.sqphsv = sqlstm.sqhstv;
         sqlstm.sqphsl = sqlstm.sqhstl;
         sqlstm.sqphss = sqlstm.sqhsts;
         sqlstm.sqpind = sqlstm.sqindv;
         sqlstm.sqpins = sqlstm.sqinds;
         sqlstm.sqparm = sqlstm.sqharm;
         sqlstm.sqparc = sqlstm.sqharc;
         sqlstm.sqpadto = sqlstm.sqadto;
         sqlstm.sqptdso = sqlstm.sqtdso;
         sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


         /* EXEC SQL CLOSE TAG_ERRORS; */ 

{
         struct sqlexd sqlstm;
         sqlstm.sqlvsn = 12;
         sqlstm.arrsiz = 53;
         sqlstm.sqladtp = &sqladt;
         sqlstm.sqltdsp = &sqltds;
         sqlstm.iters = (unsigned int  )1;
         sqlstm.offset = (unsigned int  )2036;
         sqlstm.cud = sqlcud0;
         sqlstm.sqlest = (unsigned char  *)&sqlca;
         sqlstm.sqlety = (unsigned short)4352;
         sqlstm.occurs = (unsigned int  )0;
         sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}




         if(ERRCODE != 0)
         {
               TRACEENTRY(1,"%s","Error Fetching TAG and Error Code Data from PM_TAG_ERROR_CODES table");
               TRACEENTRY(1,"%s -%d-","sqlca.sqlcode",ERRCODE);
               stErrors.ERROR_CODE = sqlca.sqlcode;
               strcpy(stErrors.ERROR_DESC,"Error Fetching TAG and Error Code Data from PM_TAG_ERROR_CODES table");
               return -1;
         }

         gTagErrorCodeCount = TagErrorCodeCount ;

   }

}


void ExitProcess(int Value)
{
   if(Value == -1)
   {
      TRACEENTRY(1,"%s","ExitProcess: Abnormal Exit. Please Check the Log and also the Process");
   }

   /* Update the PM_PROCESS table status to I for the process */
/*   EXEC SQL UPDATE PM_PROCESSES
               SET START_STOP_FLG           = 'I',
                   PROCESS_STATUS           = 'S',
                   PROCESS_LAST_STOP_DATE   = SYSDATE
             WHERE PROCESS_ID = :gProcessId;

     if((ERRCODE != 0))
   {
      TRACEENTRY(1,"%s : -%d-","ExitProcess : Error Updating PM_PROCESSES for the ProcessId :",gProcessId);
      TRACEENTRY(1,"%s : -%d-","ExitProcess : sqlca.sqlcode :",ERRCODE);
   }
*/
   UpdateProcess(gProcessId,'S');

   /* EXEC SQL COMMIT; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 53;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )2051;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   /* Remove the LockFile */
   TRACEENTRY(1,"%s","ExitProcess: LockFile and SignalFile if any, would be removed");

   unlink(stProcess.STOP_SIGNAL_PATH);
   unlink(stProcess.LOCK_FILE_PATH);

   exit(0);
}

void InitialiseLog()
{
     INIT_STR(stErrors.FILE_NAME);
     stErrors.ERROR_CODE=0;
     INIT_STR(stErrors.ERROR_DESC);
}


void InitRoamingPref()
{   
   /* EXEC SQL VAR stRoamingPref.HPLMN_CODE                     IS STRING(6); */ 

   /* EXEC SQL VAR stRoamingPref.ISO_CURNCY_CODE                IS STRING(4); */ 

   /* EXEC SQL VAR stRoamingPref.TAPOUT_CURNCY                  IS STRING(6); */ 

   /* EXEC SQL VAR stRoamingPref.UTC_OFFSET                     IS STRING(7); */ 

   stRoamingPref.TAP_SPECIFICATION_VERSION                   = 0;
   stRoamingPref.TAP_RELEASE_VERSION                         = 0;
   stRoamingPref.RATE_MULT_FACT                              = 0;
   stRoamingPref.HOME_CURNCY_ROUNDOFF_FACT                   = 0;
   stRoamingPref.TAPIN_CDR_VALIDITY_DAYS                     = 0;
   stRoamingPref.HOME_CURNCY_TAPIN_MULTFACT                  = 0;
   stRoamingPref.TAPIN_EXCH_RATE_DECIMAL_PLACES              = 0;
   stRoamingPref.TAPIN_EXCH_RATE_MULT_FACT                   = 0;
   /* EXEC SQL VAR stRoamingPref.HOME_CURNCY                    IS STRING(21); */ 

   /* EXEC SQL VAR stRoamingPref.IMSI_PREFIX_POSTPAID           IS STRING(101); */ 

   /* EXEC SQL VAR stRoamingPref.IMSI_PREFIX_PREPAID            IS STRING(101); */ 

   stRoamingPref.IMSI_PREFIX_POSTPAID_LEN                    = 0;
   stRoamingPref.IMSI_PREFIX_PREPAID_LEN                     = 0;
   stRoamingPref.RAP_SPECIFICATION_VERSION                   = 0;
   stRoamingPref.RAP_RELEASE_VERSION                         = 0;
}

int ProcessCDR(int CDRIndex)
{
   int    SetError=0;
   int    ExchCount=0;
   int    ExchangeRateFound=0;
   int    i=0;
   int    j=0;
   int    SetSGSN1=0, SetSGSN2=0, SetSGSN3=0;
   double TAPMultFactor=0;
   char   *tok;
   char   TempImsiString[101];
   char   TempImsiPrefix[20];
   char   CDRImsi[20];
   char   CDRImsiPrefix[20];
   int    ValidImsiFlag=0;

   typedef struct HomeCharge
   {
     double  CHARGE;
     double  CAMEL_FEE;
     double  CAMEL_TAX;
     double  CAMEL_DISCOUNT;
     double  TAX;
     double  DISCOUNT;
     double  CHARGE_WITH_TAX;
     double  TOTAL_CHARGE;
   }HomeCharge;

   typedef struct TAPCharge
   {
     double  CHARGE;
     double  CAMEL_FEE;
     double  CAMEL_TAX;
     double  CAMEL_DISCOUNT;
     double  TAX;               /* CallTax      + CamelTax      */
     double  DISCOUNT;          /* CallDiscount + CamelDiscount */
   }TAPCharge;

   HomeCharge stHomeCharge;
   TAPCharge  stTAPCharge;

   /***************************************************************************************/
   /* Derive the TAPDecimalPlaces */
   TAPMultFactor = pow(10,ACC.TapDecimalPlaces);

   /* Derive the Recording Entity Information for the CDR based on the Recording Entity Code */
   i=0;
   for(i=0;i<gRecEntityInfoCount;i++)
   {
       
      if(BCT.RECORDING_ENTITY_CODE == NI.RecEntityInfo[i].RecEntityCode)
      {
         BCT.RECORDING_ENTITY_TYPE = NI.RecEntityInfo[i].RecEntityType;
         strcpy(BCT.RECORDING_ENTITY_ID,NI.RecEntityInfo[i].RecEntityId);
	  break;
      }
   }
   i=0;

   if((strcmp(BCT.SERVICE_CODE,"005") == 0) || (strcmp(BCT.SERVICE_CODE,"305") == 0)) /* GPRS Call */
   {
      for(j=0;j<GPRS_REC_ENTITY_COUNT;j++)
      {
         for(i=0;i<gRecEntityInfoCount;i++)
         {
            if(GPRS_RECORDING_ENTITY_CODES[j] == NI.RecEntityInfo[i].RecEntityCode)
            {
               if((NI.RecEntityInfo[i].RecEntityType == 3) || (NI.RecEntityInfo[i].RecEntityType == 7))
               {
                  BCT.RECORDING_ENTITY_CODE = GPRS_RECORDING_ENTITY_CODES[j];
                  BCT.RECORDING_ENTITY_TYPE = NI.RecEntityInfo[i].RecEntityType;
                  strcpy(BCT.RECORDING_ENTITY_ID,NI.RecEntityInfo[i].RecEntityId);
                  break;
               }

               if(((NI.RecEntityInfo[i].RecEntityType == 4) && (SetSGSN1 == 0)) || (NI.RecEntityInfo[i].RecEntityType == 8) ) 
               {
                  BCT.SGSN_RECORDING_ENTITY_CODE1 = NI.RecEntityInfo[i].RecEntityCode;
		  BCT.SGSN_RECORDING_ENTITY_TYPE1 = NI.RecEntityInfo[i].RecEntityType;
                  strcpy(BCT.SGSN_RECORDING_ENTITY_ID1,NI.RecEntityInfo[i].RecEntityId);
                  SetSGSN1=1;
                  break;
               }

               if((NI.RecEntityInfo[i].RecEntityType == 4) && (SetSGSN2 == 0))
               {
                  BCT.SGSN_RECORDING_ENTITY_CODE2 = NI.RecEntityInfo[i].RecEntityCode;
		   BCT.SGSN_RECORDING_ENTITY_TYPE2 = NI.RecEntityInfo[i].RecEntityType;
                  strcpy(BCT.SGSN_RECORDING_ENTITY_ID2,NI.RecEntityInfo[i].RecEntityId);
                  SetSGSN2=1;
                  break;
               }

               if((NI.RecEntityInfo[i].RecEntityType == 4) && (SetSGSN3 == 0))
               {
                  BCT.SGSN_RECORDING_ENTITY_CODE3 = NI.RecEntityInfo[i].RecEntityCode;
                  strcpy(BCT.SGSN_RECORDING_ENTITY_ID3,NI.RecEntityInfo[i].RecEntityId);
                  SetSGSN3=1;
                  break;
               }
            }
         }
      }
   }

/* For LTE Calls */

 if ((strcmp(BCT.SERVICE_CODE,"300") == 0) || (strcmp(BCT.SERVICE_CODE,"301") == 0)) /* MobileSession Call & Messaging Event */
   {
      for(j=0;j<REC_ENTITY_COUNT;j++)
      {
         for(i=0;i<gRecEntityInfoCount;i++)
         {
             
	    if(RECORDING_ENTITY_CODES[j] == NI.RecEntityInfo[i].RecEntityCode)
            {
	      
               if(NI.RecEntityInfo[i].RecEntityType == 7)
               {
                  
                  BCT.RECORDING_ENTITY_CODE = RECORDING_ENTITY_CODES[j];
                  BCT.RECORDING_ENTITY_TYPE = NI.RecEntityInfo[i].RecEntityType;
		  strcpy(BCT.RECORDING_ENTITY_ID,NI.RecEntityInfo[i].RecEntityId);
                  break;
               }

               if(NI.RecEntityInfo[i].RecEntityType == 8) 
               { 
	          
                  BCT.SGSN_RECORDING_ENTITY_CODE1 = NI.RecEntityInfo[i].RecEntityCode;
                  BCT.SGSN_RECORDING_ENTITY_TYPE1 = NI.RecEntityInfo[i].RecEntityType;
                  strcpy(BCT.SGSN_RECORDING_ENTITY_ID1,NI.RecEntityInfo[i].RecEntityId);
		  break;
               }

               if(NI.RecEntityInfo[i].RecEntityType == 9) 
               {
	          
                  BCT.SGSN_RECORDING_ENTITY_CODE2 = NI.RecEntityInfo[i].RecEntityCode;
                  BCT.SGSN_RECORDING_ENTITY_TYPE2 = NI.RecEntityInfo[i].RecEntityType;
                  strcpy(BCT.SGSN_RECORDING_ENTITY_ID2,NI.RecEntityInfo[i].RecEntityId);
                  break;
               }
            }
         }
      }
    }
   
   /***************************************************************************************/
   /* Derive the ExchangeRate for the CDR based on the Call Date */
   ExchangeRateFound = 0;
   if(BCT.CALL_DATE[0] != '\0')
   {
      for(i=0;i<gExchCount;i++)
      {
         ptExchRates2 = (ptExchRates1 + i);
        
         if((strcmp(BCT.CALL_DATE,ptExchRates2->VALID_FROM) >= 0) &&
            (strcmp(BCT.CALL_DATE,ptExchRates2->VALID_TILL) <= 0))
         {
            ExchangeRateFound = 1;

            /* Set the HomeExchangeRate Code for the CDR */
            BCT.HOME_EXCHANGE_RATE = ptExchRates2->EXCHANGE_RATE;
            /* Added by Chetan on 08-AUG-2008 to get Exchange Rate Code also 
            BCT.TAP_EXCHANGE_RATE_CODE = ptExchRates2->EXCHANGE_RATE_CODE;*/
            break;
         }
      }

      if(ExchangeRateFound==0)
      {
         TRACEENTRY(1,"Exchange Rate not found for CallDate:-%s-,Index :-%d-",BCT.CALL_DATE,CDRIndex);
         stErrors.ERROR_CODE = 0;
         sprintf(stErrors.ERROR_DESC,"Exchange Rate not found for CallDate:-%s-,Index :-%d-",BCT.CALL_DATE,CDRIndex);
         return -1;
      }
   }

   /***************************************************************************************/
   /* Validate the IMSI Prefix of the CDR */

   /*  IMSI Prefix Checking is Commented because same property is added in RAP */
/*  
   memset(TempImsiString,'\0',sizeof(TempImsiString));
   memset(TempImsiPrefix,'\0',sizeof(TempImsiPrefix));
   memset(CDRImsi,'\0',sizeof(CDRImsi));
   memset(CDRImsiPrefix,'\0',sizeof(CDRImsiPrefix));

   strcpy(TempImsiString,stAppPref.IMSI_PRFX);
   sprintf(CDRImsi,"%f",BCT.IMSI);
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
      TRACEENTRY(1,"%s","Invalid Imsi Prefix in the CDR");
      TRACEENTRY(1,"Expected IMSI Prefix String : -%s-",stAppPref.IMSI_PRFX);
      TRACEENTRY(1,"IMSI                        : -%f-",BCT.IMSI);
      stErrors.ERROR_CODE = 0;
      sprintf(stErrors.ERROR_DESC,"%s -%d-","Invalid Imsi Prefix found in the CDR :",CDRIndex);
      return -1;
   }
*/
   /***************************************************************************************/
   /* Initilise the local structure members */
   stTAPCharge.CAMEL_FEE      = 0;
   stTAPCharge.CAMEL_TAX      = 0;
   stTAPCharge.CAMEL_DISCOUNT = 0;
   stTAPCharge.CHARGE         = 0;
   stTAPCharge.TAX            = 0;
   stTAPCharge.DISCOUNT       = 0;
   stHomeCharge.CAMEL_FEE     = 0;
   stHomeCharge.CAMEL_TAX     = 0;
   stHomeCharge.CAMEL_DISCOUNT= 0;
   stHomeCharge.CHARGE        = 0;
   stHomeCharge.TAX           = 0; 
   stHomeCharge.DISCOUNT      = 0;

   /***************************************************************************************/
   /* Set the CamelFee of the CDR */
   stTAPCharge.CAMEL_FEE      = (BCT.CAMEL_INVOCATION_FEE)/TAPMultFactor;

   /* Set the CamelTax of the CDR */
   stTAPCharge.CAMEL_TAX      = (BCT.CAMEL_TAX_VALUE)/TAPMultFactor;

   /* Set the CamelDiscount of the CDR */
   stTAPCharge.CAMEL_DISCOUNT = (BCT.CAMEL_DISCOUNT)/TAPMultFactor;

   /* Set the Total Charge of the CDR */
   stTAPCharge.CHARGE         = (BCT.CHARGE)/TAPMultFactor;

   /* Set the Total Tax of the CDR */
   stTAPCharge.TAX            = (BCT.TAX_VALUE)/TAPMultFactor;

   /* Set the Total Discount of the CDR */
   stTAPCharge.DISCOUNT       = (BCT.DISCOUNT)/TAPMultFactor;

   /***************************************************************************************/
   /* Convert the TAP CamelFee to Local Currency */
   if(stTAPCharge.CAMEL_FEE > 0)
   {
      stHomeCharge.CAMEL_FEE =
      (unsigned long) (((stTAPCharge.CAMEL_FEE * BCT.HOME_EXCHANGE_RATE) + stRoamingPref.HOME_CURNCY_ROUNDOFF_FACT) * 
              (stRoamingPref.HOME_CURNCY_TAPIN_MULTFACT));
   }

   /* Convert the TAP CamelTax to Local Currency */
   if(stTAPCharge.CAMEL_TAX > 0)
   {
      stHomeCharge.CAMEL_TAX =
      (unsigned long) (((stTAPCharge.CAMEL_TAX * BCT.HOME_EXCHANGE_RATE) + stRoamingPref.HOME_CURNCY_ROUNDOFF_FACT) * 
              (stRoamingPref.HOME_CURNCY_TAPIN_MULTFACT));
   }

   /* Convert the TAP CamelDiscount to Local Currency */
   if(stTAPCharge.CAMEL_DISCOUNT > 0)
   {
      stHomeCharge.CAMEL_DISCOUNT =
      (unsigned long) (((stTAPCharge.CAMEL_DISCOUNT * BCT.HOME_EXCHANGE_RATE) + stRoamingPref.HOME_CURNCY_ROUNDOFF_FACT) * 
              (stRoamingPref.HOME_CURNCY_TAPIN_MULTFACT));
   }

   /* Convert the TAP Charge to Local Currency */
   if(stTAPCharge.CHARGE > 0)
   {
      stHomeCharge.CHARGE =
      (unsigned long) (((stTAPCharge.CHARGE * BCT.HOME_EXCHANGE_RATE) + stRoamingPref.HOME_CURNCY_ROUNDOFF_FACT) * 
              (stRoamingPref.HOME_CURNCY_TAPIN_MULTFACT));
   }

   /* Convert the TAP Tax to Local Currency */
   if(stTAPCharge.TAX > 0)
   {
      stHomeCharge.TAX =
      (unsigned long) (((stTAPCharge.TAX * BCT.HOME_EXCHANGE_RATE) + stRoamingPref.HOME_CURNCY_ROUNDOFF_FACT) * 
              (stRoamingPref.HOME_CURNCY_TAPIN_MULTFACT));
   }

   /* Convert the TAP Discount to Local Currency */
   if(stTAPCharge.DISCOUNT > 0)
   {
      stHomeCharge.DISCOUNT =
      (unsigned long) (((stTAPCharge.DISCOUNT * BCT.HOME_EXCHANGE_RATE) + stRoamingPref.HOME_CURNCY_ROUNDOFF_FACT) * 
              (stRoamingPref.HOME_CURNCY_TAPIN_MULTFACT));
   }

   /***************************************************************************************/
   /* Set the CDR with the Calculated Charge */
   BCT.HOME_CURNCY_CAMEL_FEE		  = stHomeCharge.CAMEL_FEE;
   BCT.HOME_CURNCY_CAMEL_TAX		  = stHomeCharge.CAMEL_TAX;
   BCT.HOME_CURNCY_CAMEL_DISCOUNT	  = stHomeCharge.CAMEL_DISCOUNT;
   BCT.HOME_CURNCY_CHARGE		  = stHomeCharge.CHARGE;
   BCT.HOME_CURNCY_TAX			  = stHomeCharge.TAX;
   BCT.HOME_CURNCY_DISCOUNT		  = stHomeCharge.DISCOUNT;
   BCT.HOME_CURNCY_CHARGE_WITH_TAX	  = stHomeCharge.CHARGE + stHomeCharge.TAX;
   /* stHomeCharge.CAMEL_FEE +  stHomeCharge.CAMEL_TAX */

   /***************************************************************************************/
   /* Calculate Surcharge for the Call */

   BCT.HOME_CURNCY_SURCHARGE = 0;
   if((stPartnerInfo.TAPIN_SURCHARGE_FLAG == 1) && (BCT.HOME_CURNCY_CHARGE_WITH_TAX > 0))
   {
      BCT.HOME_CURNCY_SURCHARGE	=
      (unsigned long) (((BCT.HOME_CURNCY_CHARGE_WITH_TAX * stPartnerInfo.TAPIN_SURCHARGE_RATE)/100) +
              stRoamingPref.HOME_CURNCY_ROUNDOFF_FACT); 
   }

   /***************************************************************************************/
   /* Set the CDR with the Calculated Surcharge */
   BCT.HOME_CURNCY_TOTAL_CHARGE           = BCT.HOME_CURNCY_CHARGE_WITH_TAX + BCT.HOME_CURNCY_SURCHARGE;

   /***************************************************************************************/
   /* Prepare the FileSummary, by accumulating the Home Currency Charges */
   /* Added By Chetan on 21-NOV-2008 to Add CAMEL FEE in SUMMARY AMOUNT */

   FileSummary.HOME_CURNCY_CHARGE         = FileSummary.HOME_CURNCY_CHARGE + stHomeCharge.CHARGE + stHomeCharge.CAMEL_FEE;
   FileSummary.HOME_CURNCY_TAX            = FileSummary.HOME_CURNCY_TAX + stHomeCharge.TAX;
   FileSummary.HOME_CURNCY_DISCOUNT       = FileSummary.HOME_CURNCY_DISCOUNT + stHomeCharge.DISCOUNT;
   FileSummary.HOME_CURNCY_SURCHARGE      = FileSummary.HOME_CURNCY_SURCHARGE + BCT.HOME_CURNCY_SURCHARGE;
   FileSummary.TOTAL_DURATION             = FileSummary.TOTAL_DURATION + BCT.CALL_DURATION;
   FileSummary.TOTAL_OUTGOING_VOLUME      = FileSummary.TOTAL_OUTGOING_VOLUME + BCT.DATA_VOLUME_OUTGOING;
   FileSummary.TOTAL_INCOMING_VOLUME      = FileSummary.TOTAL_INCOMING_VOLUME + BCT.DATA_VOLUME_INCOMING;

/*
       FileSummary.SETTLEMENT_LOCAL_CHARGE    = FileSummary.HOME_CURNCY_CHARGE;
       FileSummary.SETTLEMENT_LOCAL_TAX       = FileSummary.HOME_CURNCY_TAX;
       FileSummary.SETTLEMENT_LOCAL_DISCOUNT  = FileSummary.HOME_CURNCY_DISCOUNT;
       FileSummary.SETTLEMENT_DURATION        = FileSummary.TOTAL_DURATION;
       FileSummary.SETTLEMENT_OUTGOING_VOLUME = FileSummary.TOTAL_OUTGOING_VOLUME;
       FileSummary.SETTLEMENT_INCOMING_VOLUME = FileSummary.TOTAL_INCOMING_VOLUME;
*/

   if(gCDRErrorFlag==0)
   {
       FileSummary.SETTLEMENT_LOCAL_CHARGE    = FileSummary.SETTLEMENT_LOCAL_CHARGE + stHomeCharge.CHARGE + stHomeCharge.CAMEL_FEE;
       FileSummary.SETTLEMENT_LOCAL_TAX       = FileSummary.SETTLEMENT_LOCAL_TAX + stHomeCharge.TAX;
       FileSummary.SETTLEMENT_LOCAL_DISCOUNT  = FileSummary.SETTLEMENT_LOCAL_DISCOUNT + stHomeCharge.DISCOUNT;
       FileSummary.SETTLEMENT_DURATION        = FileSummary.SETTLEMENT_DURATION + BCT.CALL_DURATION;
       FileSummary.SETTLEMENT_OUTGOING_VOLUME = FileSummary.SETTLEMENT_OUTGOING_VOLUME + BCT.DATA_VOLUME_OUTGOING;
       FileSummary.SETTLEMENT_INCOMING_VOLUME = FileSummary.SETTLEMENT_INCOMING_VOLUME + BCT.DATA_VOLUME_INCOMING;
   }
   else
   {
       gErrorCDRsLocalCharge = gErrorCDRsLocalCharge +  stHomeCharge.CHARGE + stHomeCharge.CAMEL_FEE;
   }

   /* Accumulate the Duration of all the Calls in the File */
   gTotalCallDuration = gTotalCallDuration + BCT.CALL_DURATION;

   /***************************************************************************************/
   /* Set the CDR Sequence */  
   BCT.CALL_SEQUENCE = CDRIndex + 1;

}

int InsertCDR()
{
   /* Insert the Final CDR to the PM_TAP_CDRS table */
   /* EXEC SQL INSERT INTO PM_TAP_CDRS
   (
          FILE_TRANSFER_DIRECTION        ,
          HPLMN_CODE                     ,
          VPLMN_CODE                     ,
          PARTNER_CODE                   ,
          FILE_TYPE_INDICATOR            ,
          FILE_SEQUENCE_NUMBER           ,
          CALL_SEQUENCE                  ,
          CALLS_TYPE_INDICATOR           ,
          CALL_TYPE                      ,
          SERVICE_CODE                   ,
          IMSI                           ,
          MSISDN                         ,
          RAPFILE_SEQUENCE_NUMBER        ,
          CALLED_CALLING_NUMBER          ,
          DIALLED_DIGITS                 ,
          CALLED_PLACE                   ,
          CALLED_REGION                  ,
          CLIR_INDICATOR                 ,
          DESTINATION_NETWORK            ,
          CALL_DATE                      ,
          UTC_OFFSET_CODE                ,
          CALL_DURATION                  ,
          SIM_TOOLKIT_INDICATOR          ,
          RECORDING_ENTITY_CODE          ,
          RECORDING_ENTITY_TYPE          ,
          RECORDING_ENTITY_ID            ,
          CALL_REFERENCE                 ,
          LOCATION_AREA                  ,
          CELLID                         ,
          SERVING_NETWORK                ,
          IMEI                           ,
          BASIC_SERVICE_TYPE             ,
          BASIC_SERVICE_CODE             ,
          TRANSPARENCY_INDICATOR         ,
          FNUR                           ,
          USER_PROTOCOL_INDICATOR        ,
          GUARANTEED_BIT_RATE            ,
          MAXIMUM_BIT_RATE               ,
          HSCSD_INDICATOR                ,
          SUPPLIMENTARY_SERVICE_CODE     ,
          SUPPLIMENTARY_ACTION_CODE      ,
          SUPPLIMENTARY_SERVICE_PARAMS   ,
          THIRD_PARTY_NUMBER             ,
          THIRD_PARTY_CLIR_INDICATOR     ,
          CAMEL_USED_FLAG                ,
          CAMEL_SERVICE_LEVEL            ,
          CAMEL_SERVICE_KEY              ,
          CAMEL_DEFAULT_CALL_HANDLING    ,
          CAMEL_EXCHANGE_RATE_CODE       ,
          HOME_CAMEL_EXCHANGE_RATE       ,
          CAMEL_INVOCATION_FEE           ,
          CAMEL_DISCOUNT_CODE            ,
          CAMEL_DISCOUNT                 ,
          CAMEL_DISCOUNTABLE_AMT         ,
          CAMEL_TAX_INFORMATION_COUNT    ,
          CAMEL_TAX_CODE                 ,
          CAMEL_TAX_VALUE                ,
          CAMEL_TAXABLE_AMOUNT           ,
          CAMEL_DESTINATION_NUMBER       ,
          CALL_TYPE_LEVEL1               ,
          CALL_TYPE_LEVEL2               ,
          CALL_TYPE_LEVEL3               ,
          CHARGE_INFORMATION_COUNT       ,
          CHARGED_ITEM                   ,
          CHARGE_TYPE                    ,
          CHARGEABLE_UNITS               ,
          CHARGED_UNITS                  ,
          CHARGE                         ,
	  CHARGE_TYPE1                   ,
          CHARGEABLE_UNITS1              ,
          CHARGED_UNITS1                 ,
          CHARGE1                        ,
          TAX_INFORMATION_COUNT          ,
          TAX_CODE                       ,
          TAX_VALUE                      ,
          TAXABLE_AMOUNT                 ,
          DISCOUNT_INFORMATION_COUNT     ,
          DISCOUNT_CODE                  ,
          DISCOUNT                       ,
          DISCOUNTABLE_AMT               ,
          HOME_CURNCY_CAMEL_FEE          ,
          HOME_CURNCY_CAMEL_TAX          ,
          HOME_CURNCY_CAMEL_DISCOUNT     ,
          HOME_CURNCY_CHARGE             ,
          HOME_CURNCY_TAX                ,
          HOME_CURNCY_DISCOUNT           ,
          HOME_CURNCY_SURCHARGE          ,
          HOME_CURNCY_CHARGE_WITH_TAX    ,
          HOME_CURNCY_TOTAL_CHARGE       ,
          HOME_EXCHANGE_RATE             ,
          TAP_EXCHANGE_RATE_CODE         ,
          TAP_EXCHANGE_RATE              ,
          TAP_EXCHANGE_RATE_DECIMAL      ,
          TAP_TAX_TYPE_RATE              ,
	  A_USERID                       ,
	  B_USERID                       ,
	  EVENT_REFERENCE                ,
	  NETWORK_ELEMENT_TYPE1          ,
          NETWORK_ELEMENT_TYPE2          ,
	  NETWORK_ELEMENT_ID1            ,
	  NETWORK_ELEMENT_ID2            ,
	  SGSN_RECORDING_ENTITY_TYPE1    ,
	  SGSN_RECORDING_ENTITY_TYPE2
   )
   VALUES
   (
        :BCT.FILE_TRANSFER_DIRECTION ,
        :BCT.HPLMN_CODE              ,
        :BCT.VPLMN_CODE              ,
        :BCT.PARTNER_CODE            ,
        :BCT.FILE_TYPE_INDICATOR     ,
        :BCT.FILE_SEQUENCE_NUMBER    ,
        :BCT.CALL_SEQUENCE           ,
        :BCT.CALLS_TYPE_INDICATOR    ,
        :BCT.CALL_TYPE               ,
        :BCT.SERVICE_CODE            ,
        :BCT.IMSI                    ,
        :BCT.MSISDN                  ,
        :BCT.RAPFILE_SEQUENCE_NUMBER ,
        :BCT.CALLED_CALLING_NUMBER   ,
        :BCT.DIALLED_DIGITS          ,
        substr(:BCT.CALLED_PLACE,1,30), 
        :BCT.CALLED_REGION           ,
        :BCT.CLIR_INDICATOR             ,
        :BCT.DESTINATION_NETWORK     ,
        to_date(:BCT.CALL_DATE,'YYYYMMDDHH24MISS') ,
        :BCT.UTC_OFFSET_CODE          ,
        :BCT.CALL_DURATION              ,
        :BCT.SIM_TOOLKIT_INDICATOR   ,
        :BCT.RECORDING_ENTITY_CODE      ,
        :BCT.RECORDING_ENTITY_TYPE      ,
        :BCT.RECORDING_ENTITY_ID     ,
        :BCT.CALL_REFERENCE          ,
        :BCT.LOCATION_AREA              ,
        :BCT.CELLID                     ,
        :BCT.SERVING_NETWORK              ,
        :BCT.IMEI                         ,
        :BCT.BASIC_SERVICE_TYPE           ,
        :BCT.BASIC_SERVICE_CODE           ,
        :BCT.TRANSPARENCY_INDICATOR          ,
        :BCT.FNUR                            ,
        :BCT.USER_PROTOCOL_INDICATOR         ,
        :BCT.GUARANTEED_BIT_RATE          ,
        :BCT.MAXIMUM_BIT_RATE             ,
        :BCT.HSCSD_INDICATOR              ,
        :BCT.SUPPLIMENTARY_SERVICE_CODE   ,
        :BCT.SUPPLIMENTARY_ACTION_CODE       ,
        :BCT.SUPPLIMENTARY_SERVICE_PARAMS ,
        :BCT.THIRD_PARTY_NUMBER           ,
        :BCT.THIRD_PARTY_CLIR_INDICATOR      ,
        :BCT.CAMEL_USED_FLAG                 ,
        :BCT.CAMEL_SERVICE_LEVEL             ,
        :BCT.CAMEL_SERVICE_KEY               ,
        :BCT.CAMEL_DEFAULT_CALL_HANDLING     ,
        :BCT.CAMEL_EXCHANGE_RATE_CODE        ,
        :BCT.HOME_CAMEL_EXCHANGE_RATE        ,
        :BCT.CAMEL_INVOCATION_FEE            ,
        :BCT.CAMEL_DISCOUNT_CODE             ,
        :BCT.CAMEL_DISCOUNT                  ,
        :BCT.CAMEL_DISCOUNTABLE_AMOUNT       ,
        :BCT.CAMEL_TAX_INFORMATION_COUNT     ,
        :BCT.CAMEL_TAX_CODE                  ,
        :BCT.CAMEL_TAX_VALUE                 ,
        :BCT.CAMEL_TAXABLE_AMOUNT            ,
        :BCT.CAMEL_DESTINATION_NUMBER        ,
        :BCT.CALL_TYPE_LEVEL1                ,
        :BCT.CALL_TYPE_LEVEL2                ,
        :BCT.CALL_TYPE_LEVEL3                ,
        :BCT.CHARGE_INFORMATION_COUNT        ,       
        :BCT.CHARGED_ITEM                    ,    
        :BCT.CHARGE_TYPE                     ,    
        :BCT.CHARGEABLE_UNITS                ,       
        :BCT.CHARGED_UNITS                   ,
        :BCT.CHARGE                          ,
	:BCT.CHARGE_TYPE1                    ,
        :BCT.CHARGEABLE_UNITS1                ,
        :BCT.CHARGED_UNITS1                   ,
        :BCT.CHARGE1                          ,
        :BCT.TAX_INFORMATION_COUNT           ,       
        :BCT.TAX_CODE                        ,
        :BCT.TAX_VALUE                       ,       
        :BCT.TAXABLE_AMOUNT                  ,       
        :BCT.DISCOUNT_INFORMATION_COUNT      ,       
        :BCT.DISCOUNT_CODE                   ,
        :BCT.DISCOUNT                        ,       
        :BCT.DISCOUNTABLE_AMT                ,       
        :BCT.HOME_CURNCY_CAMEL_FEE           ,
        :BCT.HOME_CURNCY_CAMEL_TAX           ,
        :BCT.HOME_CURNCY_CAMEL_DISCOUNT      ,
        :BCT.HOME_CURNCY_CHARGE              ,
        :BCT.HOME_CURNCY_TAX                 ,
        :BCT.HOME_CURNCY_DISCOUNT            ,
        :BCT.HOME_CURNCY_SURCHARGE           ,
        :BCT.HOME_CURNCY_CHARGE_WITH_TAX     ,       
        :BCT.HOME_CURNCY_TOTAL_CHARGE        ,       
        :BCT.HOME_EXCHANGE_RATE              ,
        :BCT.TAP_EXCHANGE_RATE_CODE          ,    
        :BCT.TAP_EXCHANGE_RATE               ,  
        :BCT.TAP_EXCHANGE_RATE_DECIMAL       ,   
        :BCT.TAP_TAX_TYPE_RATE               ,
	:BCT.A_USERID                       ,
	:BCT.B_USERID                       ,
	:BCT.EVENT_REFERENCE                ,
	:BCT.NETWORK_ELEMENT_TYPE1          ,
        :BCT.NETWORK_ELEMENT_TYPE2          ,
	:BCT.NETWORK_ELEMENT_ID1            ,
	:BCT.NETWORK_ELEMENT_ID2            ,
	:BCT.SGSN_RECORDING_ENTITY_TYPE1    ,
	:BCT.SGSN_RECORDING_ENTITY_TYPE2
   ); */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 103;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlbuft((void **)0, 
     "insert into PM_TAP_CDRS (FILE_TRANSFER_DIRECTION,HPLMN_CODE,VPLMN_CODE\
,PARTNER_CODE,FILE_TYPE_INDICATOR,FILE_SEQUENCE_NUMBER,CALL_SEQUENCE,CALLS_T\
YPE_INDICATOR,CALL_TYPE,SERVICE_CODE,IMSI,MSISDN,RAPFILE_SEQUENCE_NUMBER,CAL\
LED_CALLING_NUMBER,DIALLED_DIGITS,CALLED_PLACE,CALLED_REGION,CLIR_INDICATOR,\
DESTINATION_NETWORK,CALL_DATE,UTC_OFFSET_CODE,CALL_DURATION,SIM_TOOLKIT_INDI\
CATOR,RECORDING_ENTITY_CODE,RECORDING_ENTITY_TYPE,RECORDING_ENTITY_ID,CALL_R\
EFERENCE,LOCATION_AREA,CELLID,SERVING_NETWORK,IMEI,BASIC_SERVICE_TYPE,BASIC_\
SERVICE_CODE,TRANSPARENCY_INDICATOR,FNUR,USER_PROTOCOL_INDICATOR,GUARANTEED_\
BIT_RATE,MAXIMUM_BIT_RATE,HSCSD_INDICATOR,SUPPLIMENTARY_SERVICE_CODE,SUPPLIM\
ENTARY_ACTION_CODE,SUPPLIMENTARY_SERVICE_PARAMS,THIRD_PARTY_NUMBER,THIRD_PAR\
TY_CLIR_INDICATOR,CAMEL_USED_FLAG,CAMEL_SERVICE_LEVEL,CAMEL_SERVICE_KEY,CAME\
L_DEFAULT_CALL_HANDLING,CAMEL_EXCHANGE_RATE_CODE,HOME_CAMEL_EXCHANGE_RATE,CA\
MEL_INVOCATION_FEE,CAMEL_DISCOUNT_CODE,CAMEL_DISCOUNT,CAMEL_DISCOUNTABLE_AMT\
,CAMEL_TAX_INFORMATION_COUNT,CAMEL_TAX_COD");
   sqlbuft((void **)0, 
     "E,CAMEL_TAX_VALUE,CAMEL_TAXABLE_AMOUNT,CAMEL_DESTINATION_NUMBER,CALL_T\
YPE_LEVEL1,CALL_TYPE_LEVEL2,CALL_TYPE_LEVEL3,CHARGE_INFORMATION_COUNT,CHARGE\
D_ITEM,CHARGE_TYPE,CHARGEABLE_UNITS,CHARGED_UNITS,CHARGE,CHARGE_TYPE1,CHARGE\
ABLE_UNITS1,CHARGED_UNITS1,CHARGE1,TAX_INFORMATION_COUNT,TAX_CODE,TAX_VALUE,\
TAXABLE_AMOUNT,DISCOUNT_INFORMATION_COUNT,DISCOUNT_CODE,DISCOUNT,DISCOUNTABL\
E_AMT,HOME_CURNCY_CAMEL_FEE,HOME_CURNCY_CAMEL_TAX,HOME_CURNCY_CAMEL_DISCOUNT\
,HOME_CURNCY_CHARGE,HOME_CURNCY_TAX,HOME_CURNCY_DISCOUNT,HOME_CURNCY_SURCHAR\
GE,HOME_CURNCY_CHARGE_WITH_TAX,HOME_CURNCY_TOTAL_CHARGE,HOME_EXCHANGE_RATE,T\
AP_EXCHANGE_RATE_CODE,TAP_EXCHANGE_RATE,TAP_EXCHANGE_RATE_DECIMAL,TAP_TAX_TY\
PE_RATE,A_USERID,B_USERID,EVENT_REFERENCE,NETWORK_ELEMENT_TYPE1,NETWORK_ELEM\
ENT_TYPE2,NETWORK_ELEMENT_ID1,NETWORK_ELEMENT_ID2,SGSN_RECORDING_ENTITY_TYPE\
1,SGSN_RECORDING_ENTITY_TYPE2) values (:b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:\
b9,:b10,:b11,:b12,:b13,:b14,substr(:b15,1,30),:b16,:b17,:b18,to_date(:b19,'Y\
YYYMMDDHH24MISS'),:b20,:b21,:b22,:b23,:b24");
   sqlstm.stmt = ",:b25,:b26,:b27,:b28,:b29,:b30,:b31,:b32,:b33,:b34,:b35,:b\
36,:b37,:b38,:b39,:b40,:b41,:b42,:b43,:b44,:b45,:b46,:b47,:b48,:b49,:b50,:b51,\
:b52,:b53,:b54,:b55,:b56,:b57,:b58,:b59,:b60,:b61,:b62,:b63,:b64,:b65,:b66,:b6\
7,:b68,:b69,:b70,:b71,:b72,:b73,:b74,:b75,:b76,:b77,:b78,:b79,:b80,:b81,:b82,:\
b83,:b84,:b85,:b86,:b87,:b88,:b89,:b90,:b91,:b92,:b93,:b94,:b95,:b96,:b97,:b98\
,:b99,:b100,:b101,:b102)";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )2066;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)(BCT.FILE_TRANSFER_DIRECTION);
   sqlstm.sqhstl[0] = (unsigned int  )2;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)(BCT.HPLMN_CODE);
   sqlstm.sqhstl[1] = (unsigned int  )6;
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)(BCT.VPLMN_CODE);
   sqlstm.sqhstl[2] = (unsigned int  )6;
   sqlstm.sqhsts[2] = (         int  )0;
   sqlstm.sqindv[2] = (         void  *)0;
   sqlstm.sqinds[2] = (         int  )0;
   sqlstm.sqharm[2] = (unsigned int  )0;
   sqlstm.sqadto[2] = (unsigned short )0;
   sqlstm.sqtdso[2] = (unsigned short )0;
   sqlstm.sqhstv[3] = (         void  *)(BCT.PARTNER_CODE);
   sqlstm.sqhstl[3] = (unsigned int  )4;
   sqlstm.sqhsts[3] = (         int  )0;
   sqlstm.sqindv[3] = (         void  *)0;
   sqlstm.sqinds[3] = (         int  )0;
   sqlstm.sqharm[3] = (unsigned int  )0;
   sqlstm.sqadto[3] = (unsigned short )0;
   sqlstm.sqtdso[3] = (unsigned short )0;
   sqlstm.sqhstv[4] = (         void  *)(BCT.FILE_TYPE_INDICATOR);
   sqlstm.sqhstl[4] = (unsigned int  )2;
   sqlstm.sqhsts[4] = (         int  )0;
   sqlstm.sqindv[4] = (         void  *)0;
   sqlstm.sqinds[4] = (         int  )0;
   sqlstm.sqharm[4] = (unsigned int  )0;
   sqlstm.sqadto[4] = (unsigned short )0;
   sqlstm.sqtdso[4] = (unsigned short )0;
   sqlstm.sqhstv[5] = (         void  *)&(BCT.FILE_SEQUENCE_NUMBER);
   sqlstm.sqhstl[5] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[5] = (         int  )0;
   sqlstm.sqindv[5] = (         void  *)0;
   sqlstm.sqinds[5] = (         int  )0;
   sqlstm.sqharm[5] = (unsigned int  )0;
   sqlstm.sqadto[5] = (unsigned short )0;
   sqlstm.sqtdso[5] = (unsigned short )0;
   sqlstm.sqhstv[6] = (         void  *)&(BCT.CALL_SEQUENCE);
   sqlstm.sqhstl[6] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[6] = (         int  )0;
   sqlstm.sqindv[6] = (         void  *)0;
   sqlstm.sqinds[6] = (         int  )0;
   sqlstm.sqharm[6] = (unsigned int  )0;
   sqlstm.sqadto[6] = (unsigned short )0;
   sqlstm.sqtdso[6] = (unsigned short )0;
   sqlstm.sqhstv[7] = (         void  *)(BCT.CALLS_TYPE_INDICATOR);
   sqlstm.sqhstl[7] = (unsigned int  )2;
   sqlstm.sqhsts[7] = (         int  )0;
   sqlstm.sqindv[7] = (         void  *)0;
   sqlstm.sqinds[7] = (         int  )0;
   sqlstm.sqharm[7] = (unsigned int  )0;
   sqlstm.sqadto[7] = (unsigned short )0;
   sqlstm.sqtdso[7] = (unsigned short )0;
   sqlstm.sqhstv[8] = (         void  *)&(BCT.CALL_TYPE);
   sqlstm.sqhstl[8] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[8] = (         int  )0;
   sqlstm.sqindv[8] = (         void  *)0;
   sqlstm.sqinds[8] = (         int  )0;
   sqlstm.sqharm[8] = (unsigned int  )0;
   sqlstm.sqadto[8] = (unsigned short )0;
   sqlstm.sqtdso[8] = (unsigned short )0;
   sqlstm.sqhstv[9] = (         void  *)(BCT.SERVICE_CODE);
   sqlstm.sqhstl[9] = (unsigned int  )4;
   sqlstm.sqhsts[9] = (         int  )0;
   sqlstm.sqindv[9] = (         void  *)0;
   sqlstm.sqinds[9] = (         int  )0;
   sqlstm.sqharm[9] = (unsigned int  )0;
   sqlstm.sqadto[9] = (unsigned short )0;
   sqlstm.sqtdso[9] = (unsigned short )0;
   sqlstm.sqhstv[10] = (         void  *)&(BCT.IMSI);
   sqlstm.sqhstl[10] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[10] = (         int  )0;
   sqlstm.sqindv[10] = (         void  *)0;
   sqlstm.sqinds[10] = (         int  )0;
   sqlstm.sqharm[10] = (unsigned int  )0;
   sqlstm.sqadto[10] = (unsigned short )0;
   sqlstm.sqtdso[10] = (unsigned short )0;
   sqlstm.sqhstv[11] = (         void  *)(BCT.MSISDN);
   sqlstm.sqhstl[11] = (unsigned int  )26;
   sqlstm.sqhsts[11] = (         int  )0;
   sqlstm.sqindv[11] = (         void  *)0;
   sqlstm.sqinds[11] = (         int  )0;
   sqlstm.sqharm[11] = (unsigned int  )0;
   sqlstm.sqadto[11] = (unsigned short )0;
   sqlstm.sqtdso[11] = (unsigned short )0;
   sqlstm.sqhstv[12] = (         void  *)&(BCT.RAPFILE_SEQUENCE_NUMBER);
   sqlstm.sqhstl[12] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[12] = (         int  )0;
   sqlstm.sqindv[12] = (         void  *)0;
   sqlstm.sqinds[12] = (         int  )0;
   sqlstm.sqharm[12] = (unsigned int  )0;
   sqlstm.sqadto[12] = (unsigned short )0;
   sqlstm.sqtdso[12] = (unsigned short )0;
   sqlstm.sqhstv[13] = (         void  *)(BCT.CALLED_CALLING_NUMBER);
   sqlstm.sqhstl[13] = (unsigned int  )87;
   sqlstm.sqhsts[13] = (         int  )0;
   sqlstm.sqindv[13] = (         void  *)0;
   sqlstm.sqinds[13] = (         int  )0;
   sqlstm.sqharm[13] = (unsigned int  )0;
   sqlstm.sqadto[13] = (unsigned short )0;
   sqlstm.sqtdso[13] = (unsigned short )0;
   sqlstm.sqhstv[14] = (         void  *)(BCT.DIALLED_DIGITS);
   sqlstm.sqhstl[14] = (unsigned int  )87;
   sqlstm.sqhsts[14] = (         int  )0;
   sqlstm.sqindv[14] = (         void  *)0;
   sqlstm.sqinds[14] = (         int  )0;
   sqlstm.sqharm[14] = (unsigned int  )0;
   sqlstm.sqadto[14] = (unsigned short )0;
   sqlstm.sqtdso[14] = (unsigned short )0;
   sqlstm.sqhstv[15] = (         void  *)(BCT.CALLED_PLACE);
   sqlstm.sqhstl[15] = (unsigned int  )46;
   sqlstm.sqhsts[15] = (         int  )0;
   sqlstm.sqindv[15] = (         void  *)0;
   sqlstm.sqinds[15] = (         int  )0;
   sqlstm.sqharm[15] = (unsigned int  )0;
   sqlstm.sqadto[15] = (unsigned short )0;
   sqlstm.sqtdso[15] = (unsigned short )0;
   sqlstm.sqhstv[16] = (         void  *)(BCT.CALLED_REGION);
   sqlstm.sqhstl[16] = (unsigned int  )46;
   sqlstm.sqhsts[16] = (         int  )0;
   sqlstm.sqindv[16] = (         void  *)0;
   sqlstm.sqinds[16] = (         int  )0;
   sqlstm.sqharm[16] = (unsigned int  )0;
   sqlstm.sqadto[16] = (unsigned short )0;
   sqlstm.sqtdso[16] = (unsigned short )0;
   sqlstm.sqhstv[17] = (         void  *)&(BCT.CLIR_INDICATOR);
   sqlstm.sqhstl[17] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[17] = (         int  )0;
   sqlstm.sqindv[17] = (         void  *)0;
   sqlstm.sqinds[17] = (         int  )0;
   sqlstm.sqharm[17] = (unsigned int  )0;
   sqlstm.sqadto[17] = (unsigned short )0;
   sqlstm.sqtdso[17] = (unsigned short )0;
   sqlstm.sqhstv[18] = (         void  *)(BCT.DESTINATION_NETWORK);
   sqlstm.sqhstl[18] = (unsigned int  )7;
   sqlstm.sqhsts[18] = (         int  )0;
   sqlstm.sqindv[18] = (         void  *)0;
   sqlstm.sqinds[18] = (         int  )0;
   sqlstm.sqharm[18] = (unsigned int  )0;
   sqlstm.sqadto[18] = (unsigned short )0;
   sqlstm.sqtdso[18] = (unsigned short )0;
   sqlstm.sqhstv[19] = (         void  *)(BCT.CALL_DATE);
   sqlstm.sqhstl[19] = (unsigned int  )15;
   sqlstm.sqhsts[19] = (         int  )0;
   sqlstm.sqindv[19] = (         void  *)0;
   sqlstm.sqinds[19] = (         int  )0;
   sqlstm.sqharm[19] = (unsigned int  )0;
   sqlstm.sqadto[19] = (unsigned short )0;
   sqlstm.sqtdso[19] = (unsigned short )0;
   sqlstm.sqhstv[20] = (         void  *)&(BCT.UTC_OFFSET_CODE);
   sqlstm.sqhstl[20] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[20] = (         int  )0;
   sqlstm.sqindv[20] = (         void  *)0;
   sqlstm.sqinds[20] = (         int  )0;
   sqlstm.sqharm[20] = (unsigned int  )0;
   sqlstm.sqadto[20] = (unsigned short )0;
   sqlstm.sqtdso[20] = (unsigned short )0;
   sqlstm.sqhstv[21] = (         void  *)&(BCT.CALL_DURATION);
   sqlstm.sqhstl[21] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[21] = (         int  )0;
   sqlstm.sqindv[21] = (         void  *)0;
   sqlstm.sqinds[21] = (         int  )0;
   sqlstm.sqharm[21] = (unsigned int  )0;
   sqlstm.sqadto[21] = (unsigned short )0;
   sqlstm.sqtdso[21] = (unsigned short )0;
   sqlstm.sqhstv[22] = (         void  *)(BCT.SIM_TOOLKIT_INDICATOR);
   sqlstm.sqhstl[22] = (unsigned int  )2;
   sqlstm.sqhsts[22] = (         int  )0;
   sqlstm.sqindv[22] = (         void  *)0;
   sqlstm.sqinds[22] = (         int  )0;
   sqlstm.sqharm[22] = (unsigned int  )0;
   sqlstm.sqadto[22] = (unsigned short )0;
   sqlstm.sqtdso[22] = (unsigned short )0;
   sqlstm.sqhstv[23] = (         void  *)&(BCT.RECORDING_ENTITY_CODE);
   sqlstm.sqhstl[23] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[23] = (         int  )0;
   sqlstm.sqindv[23] = (         void  *)0;
   sqlstm.sqinds[23] = (         int  )0;
   sqlstm.sqharm[23] = (unsigned int  )0;
   sqlstm.sqadto[23] = (unsigned short )0;
   sqlstm.sqtdso[23] = (unsigned short )0;
   sqlstm.sqhstv[24] = (         void  *)&(BCT.RECORDING_ENTITY_TYPE);
   sqlstm.sqhstl[24] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[24] = (         int  )0;
   sqlstm.sqindv[24] = (         void  *)0;
   sqlstm.sqinds[24] = (         int  )0;
   sqlstm.sqharm[24] = (unsigned int  )0;
   sqlstm.sqadto[24] = (unsigned short )0;
   sqlstm.sqtdso[24] = (unsigned short )0;
   sqlstm.sqhstv[25] = (         void  *)(BCT.RECORDING_ENTITY_ID);
   sqlstm.sqhstl[25] = (unsigned int  )46;
   sqlstm.sqhsts[25] = (         int  )0;
   sqlstm.sqindv[25] = (         void  *)0;
   sqlstm.sqinds[25] = (         int  )0;
   sqlstm.sqharm[25] = (unsigned int  )0;
   sqlstm.sqadto[25] = (unsigned short )0;
   sqlstm.sqtdso[25] = (unsigned short )0;
   sqlstm.sqhstv[26] = (         void  *)(BCT.CALL_REFERENCE);
   sqlstm.sqhstl[26] = (unsigned int  )21;
   sqlstm.sqhsts[26] = (         int  )0;
   sqlstm.sqindv[26] = (         void  *)0;
   sqlstm.sqinds[26] = (         int  )0;
   sqlstm.sqharm[26] = (unsigned int  )0;
   sqlstm.sqadto[26] = (unsigned short )0;
   sqlstm.sqtdso[26] = (unsigned short )0;
   sqlstm.sqhstv[27] = (         void  *)&(BCT.LOCATION_AREA);
   sqlstm.sqhstl[27] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[27] = (         int  )0;
   sqlstm.sqindv[27] = (         void  *)0;
   sqlstm.sqinds[27] = (         int  )0;
   sqlstm.sqharm[27] = (unsigned int  )0;
   sqlstm.sqadto[27] = (unsigned short )0;
   sqlstm.sqtdso[27] = (unsigned short )0;
   sqlstm.sqhstv[28] = (         void  *)&(BCT.CELLID);
   sqlstm.sqhstl[28] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[28] = (         int  )0;
   sqlstm.sqindv[28] = (         void  *)0;
   sqlstm.sqinds[28] = (         int  )0;
   sqlstm.sqharm[28] = (unsigned int  )0;
   sqlstm.sqadto[28] = (unsigned short )0;
   sqlstm.sqtdso[28] = (unsigned short )0;
   sqlstm.sqhstv[29] = (         void  *)(BCT.SERVING_NETWORK);
   sqlstm.sqhstl[29] = (unsigned int  )6;
   sqlstm.sqhsts[29] = (         int  )0;
   sqlstm.sqindv[29] = (         void  *)0;
   sqlstm.sqinds[29] = (         int  )0;
   sqlstm.sqharm[29] = (unsigned int  )0;
   sqlstm.sqadto[29] = (unsigned short )0;
   sqlstm.sqtdso[29] = (unsigned short )0;
   sqlstm.sqhstv[30] = (         void  *)(BCT.IMEI);
   sqlstm.sqhstl[30] = (unsigned int  )21;
   sqlstm.sqhsts[30] = (         int  )0;
   sqlstm.sqindv[30] = (         void  *)0;
   sqlstm.sqinds[30] = (         int  )0;
   sqlstm.sqharm[30] = (unsigned int  )0;
   sqlstm.sqadto[30] = (unsigned short )0;
   sqlstm.sqtdso[30] = (unsigned short )0;
   sqlstm.sqhstv[31] = (         void  *)(BCT.BASIC_SERVICE_TYPE);
   sqlstm.sqhstl[31] = (unsigned int  )2;
   sqlstm.sqhsts[31] = (         int  )0;
   sqlstm.sqindv[31] = (         void  *)0;
   sqlstm.sqinds[31] = (         int  )0;
   sqlstm.sqharm[31] = (unsigned int  )0;
   sqlstm.sqadto[31] = (unsigned short )0;
   sqlstm.sqtdso[31] = (unsigned short )0;
   sqlstm.sqhstv[32] = (         void  *)(BCT.BASIC_SERVICE_CODE);
   sqlstm.sqhstl[32] = (unsigned int  )4;
   sqlstm.sqhsts[32] = (         int  )0;
   sqlstm.sqindv[32] = (         void  *)0;
   sqlstm.sqinds[32] = (         int  )0;
   sqlstm.sqharm[32] = (unsigned int  )0;
   sqlstm.sqadto[32] = (unsigned short )0;
   sqlstm.sqtdso[32] = (unsigned short )0;
   sqlstm.sqhstv[33] = (         void  *)&(BCT.TRANSPARENCY_INDICATOR);
   sqlstm.sqhstl[33] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[33] = (         int  )0;
   sqlstm.sqindv[33] = (         void  *)0;
   sqlstm.sqinds[33] = (         int  )0;
   sqlstm.sqharm[33] = (unsigned int  )0;
   sqlstm.sqadto[33] = (unsigned short )0;
   sqlstm.sqtdso[33] = (unsigned short )0;
   sqlstm.sqhstv[34] = (         void  *)&(BCT.FNUR);
   sqlstm.sqhstl[34] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[34] = (         int  )0;
   sqlstm.sqindv[34] = (         void  *)0;
   sqlstm.sqinds[34] = (         int  )0;
   sqlstm.sqharm[34] = (unsigned int  )0;
   sqlstm.sqadto[34] = (unsigned short )0;
   sqlstm.sqtdso[34] = (unsigned short )0;
   sqlstm.sqhstv[35] = (         void  *)&(BCT.USER_PROTOCOL_INDICATOR);
   sqlstm.sqhstl[35] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[35] = (         int  )0;
   sqlstm.sqindv[35] = (         void  *)0;
   sqlstm.sqinds[35] = (         int  )0;
   sqlstm.sqharm[35] = (unsigned int  )0;
   sqlstm.sqadto[35] = (unsigned short )0;
   sqlstm.sqtdso[35] = (unsigned short )0;
   sqlstm.sqhstv[36] = (         void  *)(BCT.GUARANTEED_BIT_RATE);
   sqlstm.sqhstl[36] = (unsigned int  )6;
   sqlstm.sqhsts[36] = (         int  )0;
   sqlstm.sqindv[36] = (         void  *)0;
   sqlstm.sqinds[36] = (         int  )0;
   sqlstm.sqharm[36] = (unsigned int  )0;
   sqlstm.sqadto[36] = (unsigned short )0;
   sqlstm.sqtdso[36] = (unsigned short )0;
   sqlstm.sqhstv[37] = (         void  *)(BCT.MAXIMUM_BIT_RATE);
   sqlstm.sqhstl[37] = (unsigned int  )6;
   sqlstm.sqhsts[37] = (         int  )0;
   sqlstm.sqindv[37] = (         void  *)0;
   sqlstm.sqinds[37] = (         int  )0;
   sqlstm.sqharm[37] = (unsigned int  )0;
   sqlstm.sqadto[37] = (unsigned short )0;
   sqlstm.sqtdso[37] = (unsigned short )0;
   sqlstm.sqhstv[38] = (         void  *)(BCT.HSCSD_INDICATOR);
   sqlstm.sqhstl[38] = (unsigned int  )4;
   sqlstm.sqhsts[38] = (         int  )0;
   sqlstm.sqindv[38] = (         void  *)0;
   sqlstm.sqinds[38] = (         int  )0;
   sqlstm.sqharm[38] = (unsigned int  )0;
   sqlstm.sqadto[38] = (unsigned short )0;
   sqlstm.sqtdso[38] = (unsigned short )0;
   sqlstm.sqhstv[39] = (         void  *)(BCT.SUPPLIMENTARY_SERVICE_CODE);
   sqlstm.sqhstl[39] = (unsigned int  )21;
   sqlstm.sqhsts[39] = (         int  )0;
   sqlstm.sqindv[39] = (         void  *)0;
   sqlstm.sqinds[39] = (         int  )0;
   sqlstm.sqharm[39] = (unsigned int  )0;
   sqlstm.sqadto[39] = (unsigned short )0;
   sqlstm.sqtdso[39] = (unsigned short )0;
   sqlstm.sqhstv[40] = (         void  *)&(BCT.SUPPLIMENTARY_ACTION_CODE);
   sqlstm.sqhstl[40] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[40] = (         int  )0;
   sqlstm.sqindv[40] = (         void  *)0;
   sqlstm.sqinds[40] = (         int  )0;
   sqlstm.sqharm[40] = (unsigned int  )0;
   sqlstm.sqadto[40] = (unsigned short )0;
   sqlstm.sqtdso[40] = (unsigned short )0;
   sqlstm.sqhstv[41] = (         void  *)(BCT.SUPPLIMENTARY_SERVICE_PARAMS);
   sqlstm.sqhstl[41] = (unsigned int  )46;
   sqlstm.sqhsts[41] = (         int  )0;
   sqlstm.sqindv[41] = (         void  *)0;
   sqlstm.sqinds[41] = (         int  )0;
   sqlstm.sqharm[41] = (unsigned int  )0;
   sqlstm.sqadto[41] = (unsigned short )0;
   sqlstm.sqtdso[41] = (unsigned short )0;
   sqlstm.sqhstv[42] = (         void  *)(BCT.THIRD_PARTY_NUMBER);
   sqlstm.sqhstl[42] = (unsigned int  )87;
   sqlstm.sqhsts[42] = (         int  )0;
   sqlstm.sqindv[42] = (         void  *)0;
   sqlstm.sqinds[42] = (         int  )0;
   sqlstm.sqharm[42] = (unsigned int  )0;
   sqlstm.sqadto[42] = (unsigned short )0;
   sqlstm.sqtdso[42] = (unsigned short )0;
   sqlstm.sqhstv[43] = (         void  *)&(BCT.THIRD_PARTY_CLIR_INDICATOR);
   sqlstm.sqhstl[43] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[43] = (         int  )0;
   sqlstm.sqindv[43] = (         void  *)0;
   sqlstm.sqinds[43] = (         int  )0;
   sqlstm.sqharm[43] = (unsigned int  )0;
   sqlstm.sqadto[43] = (unsigned short )0;
   sqlstm.sqtdso[43] = (unsigned short )0;
   sqlstm.sqhstv[44] = (         void  *)&(BCT.CAMEL_USED_FLAG);
   sqlstm.sqhstl[44] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[44] = (         int  )0;
   sqlstm.sqindv[44] = (         void  *)0;
   sqlstm.sqinds[44] = (         int  )0;
   sqlstm.sqharm[44] = (unsigned int  )0;
   sqlstm.sqadto[44] = (unsigned short )0;
   sqlstm.sqtdso[44] = (unsigned short )0;
   sqlstm.sqhstv[45] = (         void  *)&(BCT.CAMEL_SERVICE_LEVEL);
   sqlstm.sqhstl[45] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[45] = (         int  )0;
   sqlstm.sqindv[45] = (         void  *)0;
   sqlstm.sqinds[45] = (         int  )0;
   sqlstm.sqharm[45] = (unsigned int  )0;
   sqlstm.sqadto[45] = (unsigned short )0;
   sqlstm.sqtdso[45] = (unsigned short )0;
   sqlstm.sqhstv[46] = (         void  *)&(BCT.CAMEL_SERVICE_KEY);
   sqlstm.sqhstl[46] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[46] = (         int  )0;
   sqlstm.sqindv[46] = (         void  *)0;
   sqlstm.sqinds[46] = (         int  )0;
   sqlstm.sqharm[46] = (unsigned int  )0;
   sqlstm.sqadto[46] = (unsigned short )0;
   sqlstm.sqtdso[46] = (unsigned short )0;
   sqlstm.sqhstv[47] = (         void  *)&(BCT.CAMEL_DEFAULT_CALL_HANDLING);
   sqlstm.sqhstl[47] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[47] = (         int  )0;
   sqlstm.sqindv[47] = (         void  *)0;
   sqlstm.sqinds[47] = (         int  )0;
   sqlstm.sqharm[47] = (unsigned int  )0;
   sqlstm.sqadto[47] = (unsigned short )0;
   sqlstm.sqtdso[47] = (unsigned short )0;
   sqlstm.sqhstv[48] = (         void  *)&(BCT.CAMEL_EXCHANGE_RATE_CODE);
   sqlstm.sqhstl[48] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[48] = (         int  )0;
   sqlstm.sqindv[48] = (         void  *)0;
   sqlstm.sqinds[48] = (         int  )0;
   sqlstm.sqharm[48] = (unsigned int  )0;
   sqlstm.sqadto[48] = (unsigned short )0;
   sqlstm.sqtdso[48] = (unsigned short )0;
   sqlstm.sqhstv[49] = (         void  *)&(BCT.HOME_CAMEL_EXCHANGE_RATE);
   sqlstm.sqhstl[49] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[49] = (         int  )0;
   sqlstm.sqindv[49] = (         void  *)0;
   sqlstm.sqinds[49] = (         int  )0;
   sqlstm.sqharm[49] = (unsigned int  )0;
   sqlstm.sqadto[49] = (unsigned short )0;
   sqlstm.sqtdso[49] = (unsigned short )0;
   sqlstm.sqhstv[50] = (         void  *)&(BCT.CAMEL_INVOCATION_FEE);
   sqlstm.sqhstl[50] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[50] = (         int  )0;
   sqlstm.sqindv[50] = (         void  *)0;
   sqlstm.sqinds[50] = (         int  )0;
   sqlstm.sqharm[50] = (unsigned int  )0;
   sqlstm.sqadto[50] = (unsigned short )0;
   sqlstm.sqtdso[50] = (unsigned short )0;
   sqlstm.sqhstv[51] = (         void  *)&(BCT.CAMEL_DISCOUNT_CODE);
   sqlstm.sqhstl[51] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[51] = (         int  )0;
   sqlstm.sqindv[51] = (         void  *)0;
   sqlstm.sqinds[51] = (         int  )0;
   sqlstm.sqharm[51] = (unsigned int  )0;
   sqlstm.sqadto[51] = (unsigned short )0;
   sqlstm.sqtdso[51] = (unsigned short )0;
   sqlstm.sqhstv[52] = (         void  *)&(BCT.CAMEL_DISCOUNT);
   sqlstm.sqhstl[52] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[52] = (         int  )0;
   sqlstm.sqindv[52] = (         void  *)0;
   sqlstm.sqinds[52] = (         int  )0;
   sqlstm.sqharm[52] = (unsigned int  )0;
   sqlstm.sqadto[52] = (unsigned short )0;
   sqlstm.sqtdso[52] = (unsigned short )0;
   sqlstm.sqhstv[53] = (         void  *)&(BCT.CAMEL_DISCOUNTABLE_AMOUNT);
   sqlstm.sqhstl[53] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[53] = (         int  )0;
   sqlstm.sqindv[53] = (         void  *)0;
   sqlstm.sqinds[53] = (         int  )0;
   sqlstm.sqharm[53] = (unsigned int  )0;
   sqlstm.sqadto[53] = (unsigned short )0;
   sqlstm.sqtdso[53] = (unsigned short )0;
   sqlstm.sqhstv[54] = (         void  *)&(BCT.CAMEL_TAX_INFORMATION_COUNT);
   sqlstm.sqhstl[54] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[54] = (         int  )0;
   sqlstm.sqindv[54] = (         void  *)0;
   sqlstm.sqinds[54] = (         int  )0;
   sqlstm.sqharm[54] = (unsigned int  )0;
   sqlstm.sqadto[54] = (unsigned short )0;
   sqlstm.sqtdso[54] = (unsigned short )0;
   sqlstm.sqhstv[55] = (         void  *)&(BCT.CAMEL_TAX_CODE);
   sqlstm.sqhstl[55] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[55] = (         int  )0;
   sqlstm.sqindv[55] = (         void  *)0;
   sqlstm.sqinds[55] = (         int  )0;
   sqlstm.sqharm[55] = (unsigned int  )0;
   sqlstm.sqadto[55] = (unsigned short )0;
   sqlstm.sqtdso[55] = (unsigned short )0;
   sqlstm.sqhstv[56] = (         void  *)&(BCT.CAMEL_TAX_VALUE);
   sqlstm.sqhstl[56] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[56] = (         int  )0;
   sqlstm.sqindv[56] = (         void  *)0;
   sqlstm.sqinds[56] = (         int  )0;
   sqlstm.sqharm[56] = (unsigned int  )0;
   sqlstm.sqadto[56] = (unsigned short )0;
   sqlstm.sqtdso[56] = (unsigned short )0;
   sqlstm.sqhstv[57] = (         void  *)&(BCT.CAMEL_TAXABLE_AMOUNT);
   sqlstm.sqhstl[57] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[57] = (         int  )0;
   sqlstm.sqindv[57] = (         void  *)0;
   sqlstm.sqinds[57] = (         int  )0;
   sqlstm.sqharm[57] = (unsigned int  )0;
   sqlstm.sqadto[57] = (unsigned short )0;
   sqlstm.sqtdso[57] = (unsigned short )0;
   sqlstm.sqhstv[58] = (         void  *)(BCT.CAMEL_DESTINATION_NUMBER);
   sqlstm.sqhstl[58] = (unsigned int  )87;
   sqlstm.sqhsts[58] = (         int  )0;
   sqlstm.sqindv[58] = (         void  *)0;
   sqlstm.sqinds[58] = (         int  )0;
   sqlstm.sqharm[58] = (unsigned int  )0;
   sqlstm.sqadto[58] = (unsigned short )0;
   sqlstm.sqtdso[58] = (unsigned short )0;
   sqlstm.sqhstv[59] = (         void  *)&(BCT.CALL_TYPE_LEVEL1);
   sqlstm.sqhstl[59] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[59] = (         int  )0;
   sqlstm.sqindv[59] = (         void  *)0;
   sqlstm.sqinds[59] = (         int  )0;
   sqlstm.sqharm[59] = (unsigned int  )0;
   sqlstm.sqadto[59] = (unsigned short )0;
   sqlstm.sqtdso[59] = (unsigned short )0;
   sqlstm.sqhstv[60] = (         void  *)&(BCT.CALL_TYPE_LEVEL2);
   sqlstm.sqhstl[60] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[60] = (         int  )0;
   sqlstm.sqindv[60] = (         void  *)0;
   sqlstm.sqinds[60] = (         int  )0;
   sqlstm.sqharm[60] = (unsigned int  )0;
   sqlstm.sqadto[60] = (unsigned short )0;
   sqlstm.sqtdso[60] = (unsigned short )0;
   sqlstm.sqhstv[61] = (         void  *)&(BCT.CALL_TYPE_LEVEL3);
   sqlstm.sqhstl[61] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[61] = (         int  )0;
   sqlstm.sqindv[61] = (         void  *)0;
   sqlstm.sqinds[61] = (         int  )0;
   sqlstm.sqharm[61] = (unsigned int  )0;
   sqlstm.sqadto[61] = (unsigned short )0;
   sqlstm.sqtdso[61] = (unsigned short )0;
   sqlstm.sqhstv[62] = (         void  *)&(BCT.CHARGE_INFORMATION_COUNT);
   sqlstm.sqhstl[62] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[62] = (         int  )0;
   sqlstm.sqindv[62] = (         void  *)0;
   sqlstm.sqinds[62] = (         int  )0;
   sqlstm.sqharm[62] = (unsigned int  )0;
   sqlstm.sqadto[62] = (unsigned short )0;
   sqlstm.sqtdso[62] = (unsigned short )0;
   sqlstm.sqhstv[63] = (         void  *)(BCT.CHARGED_ITEM);
   sqlstm.sqhstl[63] = (unsigned int  )4;
   sqlstm.sqhsts[63] = (         int  )0;
   sqlstm.sqindv[63] = (         void  *)0;
   sqlstm.sqinds[63] = (         int  )0;
   sqlstm.sqharm[63] = (unsigned int  )0;
   sqlstm.sqadto[63] = (unsigned short )0;
   sqlstm.sqtdso[63] = (unsigned short )0;
   sqlstm.sqhstv[64] = (         void  *)(BCT.CHARGE_TYPE);
   sqlstm.sqhstl[64] = (unsigned int  )4;
   sqlstm.sqhsts[64] = (         int  )0;
   sqlstm.sqindv[64] = (         void  *)0;
   sqlstm.sqinds[64] = (         int  )0;
   sqlstm.sqharm[64] = (unsigned int  )0;
   sqlstm.sqadto[64] = (unsigned short )0;
   sqlstm.sqtdso[64] = (unsigned short )0;
   sqlstm.sqhstv[65] = (         void  *)&(BCT.CHARGEABLE_UNITS);
   sqlstm.sqhstl[65] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[65] = (         int  )0;
   sqlstm.sqindv[65] = (         void  *)0;
   sqlstm.sqinds[65] = (         int  )0;
   sqlstm.sqharm[65] = (unsigned int  )0;
   sqlstm.sqadto[65] = (unsigned short )0;
   sqlstm.sqtdso[65] = (unsigned short )0;
   sqlstm.sqhstv[66] = (         void  *)&(BCT.CHARGED_UNITS);
   sqlstm.sqhstl[66] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[66] = (         int  )0;
   sqlstm.sqindv[66] = (         void  *)0;
   sqlstm.sqinds[66] = (         int  )0;
   sqlstm.sqharm[66] = (unsigned int  )0;
   sqlstm.sqadto[66] = (unsigned short )0;
   sqlstm.sqtdso[66] = (unsigned short )0;
   sqlstm.sqhstv[67] = (         void  *)&(BCT.CHARGE);
   sqlstm.sqhstl[67] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[67] = (         int  )0;
   sqlstm.sqindv[67] = (         void  *)0;
   sqlstm.sqinds[67] = (         int  )0;
   sqlstm.sqharm[67] = (unsigned int  )0;
   sqlstm.sqadto[67] = (unsigned short )0;
   sqlstm.sqtdso[67] = (unsigned short )0;
   sqlstm.sqhstv[68] = (         void  *)(BCT.CHARGE_TYPE1);
   sqlstm.sqhstl[68] = (unsigned int  )4;
   sqlstm.sqhsts[68] = (         int  )0;
   sqlstm.sqindv[68] = (         void  *)0;
   sqlstm.sqinds[68] = (         int  )0;
   sqlstm.sqharm[68] = (unsigned int  )0;
   sqlstm.sqadto[68] = (unsigned short )0;
   sqlstm.sqtdso[68] = (unsigned short )0;
   sqlstm.sqhstv[69] = (         void  *)&(BCT.CHARGEABLE_UNITS1);
   sqlstm.sqhstl[69] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[69] = (         int  )0;
   sqlstm.sqindv[69] = (         void  *)0;
   sqlstm.sqinds[69] = (         int  )0;
   sqlstm.sqharm[69] = (unsigned int  )0;
   sqlstm.sqadto[69] = (unsigned short )0;
   sqlstm.sqtdso[69] = (unsigned short )0;
   sqlstm.sqhstv[70] = (         void  *)&(BCT.CHARGED_UNITS1);
   sqlstm.sqhstl[70] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[70] = (         int  )0;
   sqlstm.sqindv[70] = (         void  *)0;
   sqlstm.sqinds[70] = (         int  )0;
   sqlstm.sqharm[70] = (unsigned int  )0;
   sqlstm.sqadto[70] = (unsigned short )0;
   sqlstm.sqtdso[70] = (unsigned short )0;
   sqlstm.sqhstv[71] = (         void  *)&(BCT.CHARGE1);
   sqlstm.sqhstl[71] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[71] = (         int  )0;
   sqlstm.sqindv[71] = (         void  *)0;
   sqlstm.sqinds[71] = (         int  )0;
   sqlstm.sqharm[71] = (unsigned int  )0;
   sqlstm.sqadto[71] = (unsigned short )0;
   sqlstm.sqtdso[71] = (unsigned short )0;
   sqlstm.sqhstv[72] = (         void  *)&(BCT.TAX_INFORMATION_COUNT);
   sqlstm.sqhstl[72] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[72] = (         int  )0;
   sqlstm.sqindv[72] = (         void  *)0;
   sqlstm.sqinds[72] = (         int  )0;
   sqlstm.sqharm[72] = (unsigned int  )0;
   sqlstm.sqadto[72] = (unsigned short )0;
   sqlstm.sqtdso[72] = (unsigned short )0;
   sqlstm.sqhstv[73] = (         void  *)&(BCT.TAX_CODE);
   sqlstm.sqhstl[73] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[73] = (         int  )0;
   sqlstm.sqindv[73] = (         void  *)0;
   sqlstm.sqinds[73] = (         int  )0;
   sqlstm.sqharm[73] = (unsigned int  )0;
   sqlstm.sqadto[73] = (unsigned short )0;
   sqlstm.sqtdso[73] = (unsigned short )0;
   sqlstm.sqhstv[74] = (         void  *)&(BCT.TAX_VALUE);
   sqlstm.sqhstl[74] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[74] = (         int  )0;
   sqlstm.sqindv[74] = (         void  *)0;
   sqlstm.sqinds[74] = (         int  )0;
   sqlstm.sqharm[74] = (unsigned int  )0;
   sqlstm.sqadto[74] = (unsigned short )0;
   sqlstm.sqtdso[74] = (unsigned short )0;
   sqlstm.sqhstv[75] = (         void  *)&(BCT.TAXABLE_AMOUNT);
   sqlstm.sqhstl[75] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[75] = (         int  )0;
   sqlstm.sqindv[75] = (         void  *)0;
   sqlstm.sqinds[75] = (         int  )0;
   sqlstm.sqharm[75] = (unsigned int  )0;
   sqlstm.sqadto[75] = (unsigned short )0;
   sqlstm.sqtdso[75] = (unsigned short )0;
   sqlstm.sqhstv[76] = (         void  *)&(BCT.DISCOUNT_INFORMATION_COUNT);
   sqlstm.sqhstl[76] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[76] = (         int  )0;
   sqlstm.sqindv[76] = (         void  *)0;
   sqlstm.sqinds[76] = (         int  )0;
   sqlstm.sqharm[76] = (unsigned int  )0;
   sqlstm.sqadto[76] = (unsigned short )0;
   sqlstm.sqtdso[76] = (unsigned short )0;
   sqlstm.sqhstv[77] = (         void  *)&(BCT.DISCOUNT_CODE);
   sqlstm.sqhstl[77] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[77] = (         int  )0;
   sqlstm.sqindv[77] = (         void  *)0;
   sqlstm.sqinds[77] = (         int  )0;
   sqlstm.sqharm[77] = (unsigned int  )0;
   sqlstm.sqadto[77] = (unsigned short )0;
   sqlstm.sqtdso[77] = (unsigned short )0;
   sqlstm.sqhstv[78] = (         void  *)&(BCT.DISCOUNT);
   sqlstm.sqhstl[78] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[78] = (         int  )0;
   sqlstm.sqindv[78] = (         void  *)0;
   sqlstm.sqinds[78] = (         int  )0;
   sqlstm.sqharm[78] = (unsigned int  )0;
   sqlstm.sqadto[78] = (unsigned short )0;
   sqlstm.sqtdso[78] = (unsigned short )0;
   sqlstm.sqhstv[79] = (         void  *)&(BCT.DISCOUNTABLE_AMT);
   sqlstm.sqhstl[79] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[79] = (         int  )0;
   sqlstm.sqindv[79] = (         void  *)0;
   sqlstm.sqinds[79] = (         int  )0;
   sqlstm.sqharm[79] = (unsigned int  )0;
   sqlstm.sqadto[79] = (unsigned short )0;
   sqlstm.sqtdso[79] = (unsigned short )0;
   sqlstm.sqhstv[80] = (         void  *)&(BCT.HOME_CURNCY_CAMEL_FEE);
   sqlstm.sqhstl[80] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[80] = (         int  )0;
   sqlstm.sqindv[80] = (         void  *)0;
   sqlstm.sqinds[80] = (         int  )0;
   sqlstm.sqharm[80] = (unsigned int  )0;
   sqlstm.sqadto[80] = (unsigned short )0;
   sqlstm.sqtdso[80] = (unsigned short )0;
   sqlstm.sqhstv[81] = (         void  *)&(BCT.HOME_CURNCY_CAMEL_TAX);
   sqlstm.sqhstl[81] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[81] = (         int  )0;
   sqlstm.sqindv[81] = (         void  *)0;
   sqlstm.sqinds[81] = (         int  )0;
   sqlstm.sqharm[81] = (unsigned int  )0;
   sqlstm.sqadto[81] = (unsigned short )0;
   sqlstm.sqtdso[81] = (unsigned short )0;
   sqlstm.sqhstv[82] = (         void  *)&(BCT.HOME_CURNCY_CAMEL_DISCOUNT);
   sqlstm.sqhstl[82] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[82] = (         int  )0;
   sqlstm.sqindv[82] = (         void  *)0;
   sqlstm.sqinds[82] = (         int  )0;
   sqlstm.sqharm[82] = (unsigned int  )0;
   sqlstm.sqadto[82] = (unsigned short )0;
   sqlstm.sqtdso[82] = (unsigned short )0;
   sqlstm.sqhstv[83] = (         void  *)&(BCT.HOME_CURNCY_CHARGE);
   sqlstm.sqhstl[83] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[83] = (         int  )0;
   sqlstm.sqindv[83] = (         void  *)0;
   sqlstm.sqinds[83] = (         int  )0;
   sqlstm.sqharm[83] = (unsigned int  )0;
   sqlstm.sqadto[83] = (unsigned short )0;
   sqlstm.sqtdso[83] = (unsigned short )0;
   sqlstm.sqhstv[84] = (         void  *)&(BCT.HOME_CURNCY_TAX);
   sqlstm.sqhstl[84] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[84] = (         int  )0;
   sqlstm.sqindv[84] = (         void  *)0;
   sqlstm.sqinds[84] = (         int  )0;
   sqlstm.sqharm[84] = (unsigned int  )0;
   sqlstm.sqadto[84] = (unsigned short )0;
   sqlstm.sqtdso[84] = (unsigned short )0;
   sqlstm.sqhstv[85] = (         void  *)&(BCT.HOME_CURNCY_DISCOUNT);
   sqlstm.sqhstl[85] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[85] = (         int  )0;
   sqlstm.sqindv[85] = (         void  *)0;
   sqlstm.sqinds[85] = (         int  )0;
   sqlstm.sqharm[85] = (unsigned int  )0;
   sqlstm.sqadto[85] = (unsigned short )0;
   sqlstm.sqtdso[85] = (unsigned short )0;
   sqlstm.sqhstv[86] = (         void  *)&(BCT.HOME_CURNCY_SURCHARGE);
   sqlstm.sqhstl[86] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[86] = (         int  )0;
   sqlstm.sqindv[86] = (         void  *)0;
   sqlstm.sqinds[86] = (         int  )0;
   sqlstm.sqharm[86] = (unsigned int  )0;
   sqlstm.sqadto[86] = (unsigned short )0;
   sqlstm.sqtdso[86] = (unsigned short )0;
   sqlstm.sqhstv[87] = (         void  *)&(BCT.HOME_CURNCY_CHARGE_WITH_TAX);
   sqlstm.sqhstl[87] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[87] = (         int  )0;
   sqlstm.sqindv[87] = (         void  *)0;
   sqlstm.sqinds[87] = (         int  )0;
   sqlstm.sqharm[87] = (unsigned int  )0;
   sqlstm.sqadto[87] = (unsigned short )0;
   sqlstm.sqtdso[87] = (unsigned short )0;
   sqlstm.sqhstv[88] = (         void  *)&(BCT.HOME_CURNCY_TOTAL_CHARGE);
   sqlstm.sqhstl[88] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[88] = (         int  )0;
   sqlstm.sqindv[88] = (         void  *)0;
   sqlstm.sqinds[88] = (         int  )0;
   sqlstm.sqharm[88] = (unsigned int  )0;
   sqlstm.sqadto[88] = (unsigned short )0;
   sqlstm.sqtdso[88] = (unsigned short )0;
   sqlstm.sqhstv[89] = (         void  *)&(BCT.HOME_EXCHANGE_RATE);
   sqlstm.sqhstl[89] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[89] = (         int  )0;
   sqlstm.sqindv[89] = (         void  *)0;
   sqlstm.sqinds[89] = (         int  )0;
   sqlstm.sqharm[89] = (unsigned int  )0;
   sqlstm.sqadto[89] = (unsigned short )0;
   sqlstm.sqtdso[89] = (unsigned short )0;
   sqlstm.sqhstv[90] = (         void  *)&(BCT.TAP_EXCHANGE_RATE_CODE);
   sqlstm.sqhstl[90] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[90] = (         int  )0;
   sqlstm.sqindv[90] = (         void  *)0;
   sqlstm.sqinds[90] = (         int  )0;
   sqlstm.sqharm[90] = (unsigned int  )0;
   sqlstm.sqadto[90] = (unsigned short )0;
   sqlstm.sqtdso[90] = (unsigned short )0;
   sqlstm.sqhstv[91] = (         void  *)&(BCT.TAP_EXCHANGE_RATE);
   sqlstm.sqhstl[91] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[91] = (         int  )0;
   sqlstm.sqindv[91] = (         void  *)0;
   sqlstm.sqinds[91] = (         int  )0;
   sqlstm.sqharm[91] = (unsigned int  )0;
   sqlstm.sqadto[91] = (unsigned short )0;
   sqlstm.sqtdso[91] = (unsigned short )0;
   sqlstm.sqhstv[92] = (         void  *)&(BCT.TAP_EXCHANGE_RATE_DECIMAL);
   sqlstm.sqhstl[92] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[92] = (         int  )0;
   sqlstm.sqindv[92] = (         void  *)0;
   sqlstm.sqinds[92] = (         int  )0;
   sqlstm.sqharm[92] = (unsigned int  )0;
   sqlstm.sqadto[92] = (unsigned short )0;
   sqlstm.sqtdso[92] = (unsigned short )0;
   sqlstm.sqhstv[93] = (         void  *)(BCT.TAP_TAX_TYPE_RATE);
   sqlstm.sqhstl[93] = (unsigned int  )601;
   sqlstm.sqhsts[93] = (         int  )0;
   sqlstm.sqindv[93] = (         void  *)0;
   sqlstm.sqinds[93] = (         int  )0;
   sqlstm.sqharm[93] = (unsigned int  )0;
   sqlstm.sqadto[93] = (unsigned short )0;
   sqlstm.sqtdso[93] = (unsigned short )0;
   sqlstm.sqhstv[94] = (         void  *)(BCT.A_USERID);
   sqlstm.sqhstl[94] = (unsigned int  )66;
   sqlstm.sqhsts[94] = (         int  )0;
   sqlstm.sqindv[94] = (         void  *)0;
   sqlstm.sqinds[94] = (         int  )0;
   sqlstm.sqharm[94] = (unsigned int  )0;
   sqlstm.sqadto[94] = (unsigned short )0;
   sqlstm.sqtdso[94] = (unsigned short )0;
   sqlstm.sqhstv[95] = (         void  *)(BCT.B_USERID);
   sqlstm.sqhstl[95] = (unsigned int  )66;
   sqlstm.sqhsts[95] = (         int  )0;
   sqlstm.sqindv[95] = (         void  *)0;
   sqlstm.sqinds[95] = (         int  )0;
   sqlstm.sqharm[95] = (unsigned int  )0;
   sqlstm.sqadto[95] = (unsigned short )0;
   sqlstm.sqtdso[95] = (unsigned short )0;
   sqlstm.sqhstv[96] = (         void  *)(BCT.EVENT_REFERENCE);
   sqlstm.sqhstl[96] = (unsigned int  )31;
   sqlstm.sqhsts[96] = (         int  )0;
   sqlstm.sqindv[96] = (         void  *)0;
   sqlstm.sqinds[96] = (         int  )0;
   sqlstm.sqharm[96] = (unsigned int  )0;
   sqlstm.sqadto[96] = (unsigned short )0;
   sqlstm.sqtdso[96] = (unsigned short )0;
   sqlstm.sqhstv[97] = (         void  *)&(BCT.NETWORK_ELEMENT_TYPE1);
   sqlstm.sqhstl[97] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[97] = (         int  )0;
   sqlstm.sqindv[97] = (         void  *)0;
   sqlstm.sqinds[97] = (         int  )0;
   sqlstm.sqharm[97] = (unsigned int  )0;
   sqlstm.sqadto[97] = (unsigned short )0;
   sqlstm.sqtdso[97] = (unsigned short )0;
   sqlstm.sqhstv[98] = (         void  *)&(BCT.NETWORK_ELEMENT_TYPE2);
   sqlstm.sqhstl[98] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[98] = (         int  )0;
   sqlstm.sqindv[98] = (         void  *)0;
   sqlstm.sqinds[98] = (         int  )0;
   sqlstm.sqharm[98] = (unsigned int  )0;
   sqlstm.sqadto[98] = (unsigned short )0;
   sqlstm.sqtdso[98] = (unsigned short )0;
   sqlstm.sqhstv[99] = (         void  *)(BCT.NETWORK_ELEMENT_ID1);
   sqlstm.sqhstl[99] = (unsigned int  )46;
   sqlstm.sqhsts[99] = (         int  )0;
   sqlstm.sqindv[99] = (         void  *)0;
   sqlstm.sqinds[99] = (         int  )0;
   sqlstm.sqharm[99] = (unsigned int  )0;
   sqlstm.sqadto[99] = (unsigned short )0;
   sqlstm.sqtdso[99] = (unsigned short )0;
   sqlstm.sqhstv[100] = (         void  *)(BCT.NETWORK_ELEMENT_ID2);
   sqlstm.sqhstl[100] = (unsigned int  )46;
   sqlstm.sqhsts[100] = (         int  )0;
   sqlstm.sqindv[100] = (         void  *)0;
   sqlstm.sqinds[100] = (         int  )0;
   sqlstm.sqharm[100] = (unsigned int  )0;
   sqlstm.sqadto[100] = (unsigned short )0;
   sqlstm.sqtdso[100] = (unsigned short )0;
   sqlstm.sqhstv[101] = (         void  *)&(BCT.SGSN_RECORDING_ENTITY_TYPE1);
   sqlstm.sqhstl[101] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[101] = (         int  )0;
   sqlstm.sqindv[101] = (         void  *)0;
   sqlstm.sqinds[101] = (         int  )0;
   sqlstm.sqharm[101] = (unsigned int  )0;
   sqlstm.sqadto[101] = (unsigned short )0;
   sqlstm.sqtdso[101] = (unsigned short )0;
   sqlstm.sqhstv[102] = (         void  *)&(BCT.SGSN_RECORDING_ENTITY_TYPE2);
   sqlstm.sqhstl[102] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[102] = (         int  )0;
   sqlstm.sqindv[102] = (         void  *)0;
   sqlstm.sqinds[102] = (         int  )0;
   sqlstm.sqharm[102] = (unsigned int  )0;
   sqlstm.sqadto[102] = (unsigned short )0;
   sqlstm.sqtdso[102] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   if(ERRCODE!=0)
   {
      stErrors.ERROR_CODE = sqlca.sqlcode;
      strcpy(stErrors.ERROR_DESC,"Error Inserting Record into PM_TAP_CDRS");

      TRACEENTRY(1,"BCT.FILE_TRANSFER_DIRECTION		: -%s-",BCT.FILE_TRANSFER_DIRECTION);
      TRACEENTRY(1,"BCT.HPLMN_CODE			: -%s-",BCT.HPLMN_CODE);
      TRACEENTRY(1,"BCT.VPLMN_CODE			: -%s-",BCT.VPLMN_CODE);
      TRACEENTRY(1,"BCT.PARTNER_CODE            	: -%s-",BCT.PARTNER_CODE);
      TRACEENTRY(1,"BCT.FILE_TYPE_INDICATOR		: -%s-",BCT.FILE_TYPE_INDICATOR);
      TRACEENTRY(1,"BCT.CALLS_TYPE_INDICATOR    	: -%s-",BCT.CALLS_TYPE_INDICATOR);
      TRACEENTRY(1,"BCT.MSISDN                  	: -%s-",BCT.MSISDN);
      TRACEENTRY(1,"BCT.CALLED_CALLING_NUMBER		: -%s-",BCT.CALLED_CALLING_NUMBER);
      TRACEENTRY(1,"BCT.DIALLED_DIGITS			: -%s-",BCT.DIALLED_DIGITS);
      TRACEENTRY(1,"BCT.CALLED_PLACE			: -%s-",BCT.CALLED_PLACE);
      TRACEENTRY(1,"BCT.CALLED_REGION			: -%s-",BCT.CALLED_REGION);
      TRACEENTRY(1,"BCT.DESTINATION_NETWORK		: -%s-",BCT.DESTINATION_NETWORK);
      TRACEENTRY(1,"BCT.CALL_DATE			: -%s-",BCT.CALL_DATE);
      TRACEENTRY(1,"BCT.SIM_TOOLKIT_INDICATOR		: -%s-",BCT.SIM_TOOLKIT_INDICATOR);
      TRACEENTRY(1,"BCT.RECORDING_ENTITY_ID     	: -%s-",BCT.RECORDING_ENTITY_ID);
      TRACEENTRY(1,"BCT.CALL_REFERENCE			: -%s-",BCT.CALL_REFERENCE);
      TRACEENTRY(1,"BCT.SERVING_NETWORK			: -%s-",BCT.SERVING_NETWORK);
      TRACEENTRY(1,"BCT.IMEI                         	: -%s-",BCT.IMEI);
      TRACEENTRY(1,"BCT.BASIC_SERVICE_TYPE           	: -%s-",BCT.BASIC_SERVICE_TYPE);
      TRACEENTRY(1,"BCT.BASIC_SERVICE_CODE           	: -%s-",BCT.BASIC_SERVICE_CODE);
      TRACEENTRY(1,"BCT.GUARANTEED_BIT_RATE		: -%s-",BCT.GUARANTEED_BIT_RATE);
      TRACEENTRY(1,"BCT.MAXIMUM_BIT_RATE             	: -%s-",BCT.MAXIMUM_BIT_RATE);
      TRACEENTRY(1,"BCT.HSCSD_INDICATOR              	: -%s-",BCT.HSCSD_INDICATOR);
      TRACEENTRY(1,"BCT.SUPPLIMENTARY_SERVICE_CODE      : -%s-",BCT.SUPPLIMENTARY_SERVICE_CODE);
      TRACEENTRY(1,"BCT.SUPPLIMENTARY_SERVICE_PARAMS    : -%s-",BCT.SUPPLIMENTARY_SERVICE_PARAMS);
      TRACEENTRY(1,"BCT.THIRD_PARTY_NUMBER		: -%s-",BCT.THIRD_PARTY_NUMBER);
      TRACEENTRY(1,"BCT.CAMEL_DESTINATION_NUMBER	: -%s-",BCT.CAMEL_DESTINATION_NUMBER);
      TRACEENTRY(1,"BCT.CHARGED_ITEM                 	: -%s-",BCT.CHARGED_ITEM);
      TRACEENTRY(1,"BCT.CHARGE_TYPE                  	: -%s-",BCT.CHARGE_TYPE);
      return -1;
   }

   return 0;
}

int BulkInsertCDR(int TotalCDRS)
{
   int i=0;

   /* Insert the Final CDR to the PM_TAP_CDRS table */
   /* EXEC SQL FOR :TotalCDRS
   INSERT INTO PM_TAP_CDRS
   (
          FILE_TRANSFER_DIRECTION        ,
          HPLMN_CODE                     ,
          VPLMN_CODE                     ,
          PARTNER_CODE                   ,
          FILE_TYPE_INDICATOR            ,
          FILE_SEQUENCE_NUMBER           ,
          CALL_SEQUENCE                  ,
          CALLS_TYPE_INDICATOR           ,
          CALL_TYPE                      ,
          SERVICE_CODE                   ,
          IMSI                           ,
          MSISDN                         ,
          RAPFILE_SEQUENCE_NUMBER        ,
          CALLED_CALLING_NUMBER          ,
          DIALLED_DIGITS                 ,
          CALLED_PLACE                   ,
          CALLED_REGION                  ,
          CLIR_INDICATOR                 ,
          DESTINATION_NETWORK            ,
          CALL_DATE                      ,
          UTC_OFFSET_CODE                ,
          CALL_DURATION                  ,
          SIM_TOOLKIT_INDICATOR          ,
          RECORDING_ENTITY_CODE          ,
          RECORDING_ENTITY_TYPE          ,
          RECORDING_ENTITY_ID            ,
          CALL_REFERENCE                 ,
          LOCATION_AREA                  ,
          CELLID                         ,
          SERVING_NETWORK                ,
          IMEI                           ,
          BASIC_SERVICE_TYPE             ,
          BASIC_SERVICE_CODE             ,
          TRANSPARENCY_INDICATOR         ,
          FNUR                           ,
          USER_PROTOCOL_INDICATOR        ,
          GUARANTEED_BIT_RATE            ,
          MAXIMUM_BIT_RATE               ,
          HSCSD_INDICATOR                ,
          SUPPLIMENTARY_SERVICE_CODE     ,
          SUPPLIMENTARY_ACTION_CODE      ,
          SUPPLIMENTARY_SERVICE_PARAMS   ,
          THIRD_PARTY_NUMBER             ,
          THIRD_PARTY_CLIR_INDICATOR     ,
          CAMEL_USED_FLAG                ,
          CAMEL_SERVICE_LEVEL            ,
          CAMEL_SERVICE_KEY              ,
          CAMEL_DEFAULT_CALL_HANDLING    ,
          CAMEL_EXCHANGE_RATE_CODE       ,
          HOME_CAMEL_EXCHANGE_RATE       ,
          CAMEL_INVOCATION_FEE           ,
          CAMEL_DISCOUNT_CODE            ,
          CAMEL_DISCOUNT                 ,
          CAMEL_DISCOUNTABLE_AMT         ,
          CAMEL_TAX_INFORMATION_COUNT    ,
          CAMEL_TAX_CODE                 ,
          CAMEL_TAX_VALUE                ,
          CAMEL_TAXABLE_AMOUNT           ,
          CAMEL_DESTINATION_NUMBER       ,
          CALL_TYPE_LEVEL1               ,
          CALL_TYPE_LEVEL2               ,
          CALL_TYPE_LEVEL3               ,
          CHARGE_INFORMATION_COUNT       ,
          CHARGED_ITEM                   ,
          CHARGE_TYPE                    ,
          CHARGEABLE_UNITS               ,
          CHARGED_UNITS                  ,
          CHARGE                         ,
	  CHARGE_TYPE1                    ,
          CHARGEABLE_UNITS1               ,
          CHARGED_UNITS1                  ,
          CHARGE1                         ,
          TAX_INFORMATION_COUNT          ,
          TAX_CODE                       ,
          TAX_VALUE                      ,
          TAXABLE_AMOUNT                 ,
          DISCOUNT_INFORMATION_COUNT     ,
          DISCOUNT_CODE                  ,
          DISCOUNT                       ,
          DISCOUNTABLE_AMT               ,
          HOME_CURNCY_CAMEL_FEE          ,
          HOME_CURNCY_CAMEL_TAX          ,
          HOME_CURNCY_CAMEL_DISCOUNT     ,
          HOME_CURNCY_CHARGE             ,
          HOME_CURNCY_TAX                ,
          HOME_CURNCY_DISCOUNT           ,
          HOME_CURNCY_SURCHARGE          ,
          HOME_CURNCY_CHARGE_WITH_TAX    ,
          HOME_CURNCY_TOTAL_CHARGE       ,
          HOME_EXCHANGE_RATE             ,
          TAP_EXCHANGE_RATE_CODE         ,
          TAP_EXCHANGE_RATE              ,
          TAP_EXCHANGE_RATE_DECIMAL      ,
          TAP_TAX_TYPE_RATE              ,
  	  NETWORK_ACCESS_IDENTIFER	 ,
	  PDP_ADDRESS			 ,
	  APN_NI			 ,
	  APN_OI			 ,
	  CAUSE_FOR_TERMINATION		 ,
	  PARTIAL_TYPE_INDICATOR	 ,
	  CHARGING_ID			 ,
	  SERVING_LOCATION_DESC		 ,
	  DATA_VOLUME_INCOMING		 ,
	  DATA_VOLUME_OUTGOING		 ,
	  SGSN_RECORDING_ENTITY_CODE1	 ,
	  SGSN_RECORDING_ENTITY_ID1	 ,
	  SGSN_RECORDING_ENTITY_CODE2	 ,
	  SGSN_RECORDING_ENTITY_ID2	 ,
	  SGSN_RECORDING_ENTITY_CODE3	 ,
	  SGSN_RECORDING_ENTITY_ID3	 ,
	  CAMEL_APN_NI			 ,
	  CAMEL_APN_OI		         ,
	  A_USERID                       ,
	  B_USERID                       ,
	  EVENT_REFERENCE                ,
	  NETWORK_ELEMENT_TYPE1          ,
          NETWORK_ELEMENT_TYPE2          ,
	  NETWORK_ELEMENT_ID1            ,
	  NETWORK_ELEMENT_ID2            ,
	  SGSN_RECORDING_ENTITY_TYPE1    ,
	  SGSN_RECORDING_ENTITY_TYPE2
   )
   VALUES
   (
        :FILE_TRANSFER_DIRECTION ,
        :HPLMN_CODE              ,
        :VPLMN_CODE              ,
        :PARTNER_CODE            ,
        :FILE_TYPE_INDICATOR     ,
        :FILE_SEQUENCE_NUMBER    , 
        :CALL_SEQUENCE           ,
        :CALLS_TYPE_INDICATOR    ,
        :CALL_TYPE               ,
        :SERVICE_CODE            ,
        :IMSI                    ,
        :MSISDN                  ,
        :RAPFILE_SEQUENCE_NUMBER ,
        :CALLED_CALLING_NUMBER   ,
        :DIALLED_DIGITS          ,
         substr(:CALLED_PLACE,1,30),
        :CALLED_REGION           ,
        :CLIR_INDICATOR          ,
        :DESTINATION_NETWORK     ,
        to_date(:CALL_DATE,'YYYYMMDDHH24MISS') ,
        :UTC_OFFSET_CODE          ,
        :CALL_DURATION              ,
        :SIM_TOOLKIT_INDICATOR   ,
        :RECORDING_ENTITY_CODE      ,
        :RECORDING_ENTITY_TYPE      ,
        :RECORDING_ENTITY_ID     ,
        :CALL_REFERENCE          ,
        :LOCATION_AREA              ,
        :CELLID                     ,
        :SERVING_NETWORK              ,
        :IMEI                         ,
        :BASIC_SERVICE_TYPE           ,
        :BASIC_SERVICE_CODE           ,
        :TRANSPARENCY_INDICATOR          ,
        :FNUR                            ,
        :USER_PROTOCOL_INDICATOR         ,
        :GUARANTEED_BIT_RATE          ,
        :MAXIMUM_BIT_RATE             ,
        :HSCSD_INDICATOR              ,
        :SUPPLIMENTARY_SERVICE_CODE   ,
        :SUPPLIMENTARY_ACTION_CODE       ,
        :SUPPLIMENTARY_SERVICE_PARAMS ,
        :THIRD_PARTY_NUMBER           ,
        :THIRD_PARTY_CLIR_INDICATOR      ,
        :CAMEL_USED_FLAG                 ,
        :CAMEL_SERVICE_LEVEL             ,
        :CAMEL_SERVICE_KEY               ,
        :CAMEL_DEFAULT_CALL_HANDLING     ,
        :CAMEL_EXCHANGE_RATE_CODE        ,
        :HOME_CAMEL_EXCHANGE_RATE        ,
        :CAMEL_INVOCATION_FEE            ,
        :CAMEL_DISCOUNT_CODE             ,
        :CAMEL_DISCOUNT                  ,
        :CAMEL_DISCOUNTABLE_AMOUNT       ,
        :CAMEL_TAX_INFORMATION_COUNT     ,
        :CAMEL_TAX_CODE                  ,
        :CAMEL_TAX_VALUE                 ,
        :CAMEL_TAXABLE_AMOUNT            ,
        :CAMEL_DESTINATION_NUMBER     ,
        :CALL_TYPE_LEVEL1                ,
        :CALL_TYPE_LEVEL2                ,
        :CALL_TYPE_LEVEL3                ,
        :CHARGE_INFORMATION_COUNT        ,
        :CHARGED_ITEM                 ,
        :CHARGE_TYPE                  ,
        :CHARGEABLE_UNITS                ,
        :CHARGED_UNITS                   ,
        :CHARGE                          ,
	:CHARGE_TYPE1                    ,
        :CHARGEABLE_UNITS1               ,
        :CHARGED_UNITS1                  ,
        :CHARGE1                         ,
        :TAX_INFORMATION_COUNT           ,
        :TAX_CODE                        ,
        :TAX_VALUE                       ,
        :TAXABLE_AMOUNT                  ,
        :DISCOUNT_INFORMATION_COUNT      ,
        :DISCOUNT_CODE                   ,
        :DISCOUNT                        ,
        :DISCOUNTABLE_AMT                ,
        :HOME_CURNCY_CAMEL_FEE           ,
        :HOME_CURNCY_CAMEL_TAX           ,
        :HOME_CURNCY_CAMEL_DISCOUNT      ,
        :HOME_CURNCY_CHARGE              ,
        :HOME_CURNCY_TAX                 ,
        :HOME_CURNCY_DISCOUNT            ,
        :HOME_CURNCY_SURCHARGE           ,
        :HOME_CURNCY_CHARGE_WITH_TAX     ,
        :HOME_CURNCY_TOTAL_CHARGE        ,
        :HOME_EXCHANGE_RATE              ,
        :TAP_EXCHANGE_RATE_CODE          ,
        :TAP_EXCHANGE_RATE               ,
        :TAP_EXCHANGE_RATE_DECIMAL       ,
        :TAP_TAX_TYPE_RATE               ,
        :NETWORK_ACCESS_IDENTIFER        ,
        :PDP_ADDRESS                     ,
        :APN_NI                         ,
        :APN_OI                         ,
        :CAUSE_FOR_TERMINATION          ,
        :PARTIAL_TYPE_INDICATOR         ,
        :CHARGING_ID                    ,
        :SERVING_LOCATION_DESC          ,
        :DATA_VOLUME_INCOMING           ,
        :DATA_VOLUME_OUTGOING           ,
        :SGSN_RECORDING_ENTITY_CODE1    ,
        :SGSN_RECORDING_ENTITY_ID1      ,
        :SGSN_RECORDING_ENTITY_CODE2    ,
        :SGSN_RECORDING_ENTITY_ID2      ,
        :SGSN_RECORDING_ENTITY_CODE3    ,
        :SGSN_RECORDING_ENTITY_ID3      ,
        :CAMEL_APN_NI                   ,
        :CAMEL_APN_OI                   ,
	:A_USERID                       ,
	:B_USERID                       ,
	:EVENT_REFERENCE                ,
	:NETWORK_ELEMENT_TYPE1          ,
        :NETWORK_ELEMENT_TYPE2          ,
	:NETWORK_ELEMENT_ID1            ,
	:NETWORK_ELEMENT_ID2            ,
	:SGSN_RECORDING_ENTITY_TYPE1    ,
	:SGSN_RECORDING_ENTITY_TYPE2
   ); */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 121;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlbuft((void **)0, 
     "insert into PM_TAP_CDRS (FILE_TRANSFER_DIRECTION,HPLMN_CODE,VPLMN_CODE\
,PARTNER_CODE,FILE_TYPE_INDICATOR,FILE_SEQUENCE_NUMBER,CALL_SEQUENCE,CALLS_T\
YPE_INDICATOR,CALL_TYPE,SERVICE_CODE,IMSI,MSISDN,RAPFILE_SEQUENCE_NUMBER,CAL\
LED_CALLING_NUMBER,DIALLED_DIGITS,CALLED_PLACE,CALLED_REGION,CLIR_INDICATOR,\
DESTINATION_NETWORK,CALL_DATE,UTC_OFFSET_CODE,CALL_DURATION,SIM_TOOLKIT_INDI\
CATOR,RECORDING_ENTITY_CODE,RECORDING_ENTITY_TYPE,RECORDING_ENTITY_ID,CALL_R\
EFERENCE,LOCATION_AREA,CELLID,SERVING_NETWORK,IMEI,BASIC_SERVICE_TYPE,BASIC_\
SERVICE_CODE,TRANSPARENCY_INDICATOR,FNUR,USER_PROTOCOL_INDICATOR,GUARANTEED_\
BIT_RATE,MAXIMUM_BIT_RATE,HSCSD_INDICATOR,SUPPLIMENTARY_SERVICE_CODE,SUPPLIM\
ENTARY_ACTION_CODE,SUPPLIMENTARY_SERVICE_PARAMS,THIRD_PARTY_NUMBER,THIRD_PAR\
TY_CLIR_INDICATOR,CAMEL_USED_FLAG,CAMEL_SERVICE_LEVEL,CAMEL_SERVICE_KEY,CAME\
L_DEFAULT_CALL_HANDLING,CAMEL_EXCHANGE_RATE_CODE,HOME_CAMEL_EXCHANGE_RATE,CA\
MEL_INVOCATION_FEE,CAMEL_DISCOUNT_CODE,CAMEL_DISCOUNT,CAMEL_DISCOUNTABLE_AMT\
,CAMEL_TAX_INFORMATION_COUNT,CAMEL_TAX_COD");
   sqlbuft((void **)0, 
     "E,CAMEL_TAX_VALUE,CAMEL_TAXABLE_AMOUNT,CAMEL_DESTINATION_NUMBER,CALL_T\
YPE_LEVEL1,CALL_TYPE_LEVEL2,CALL_TYPE_LEVEL3,CHARGE_INFORMATION_COUNT,CHARGE\
D_ITEM,CHARGE_TYPE,CHARGEABLE_UNITS,CHARGED_UNITS,CHARGE,CHARGE_TYPE1,CHARGE\
ABLE_UNITS1,CHARGED_UNITS1,CHARGE1,TAX_INFORMATION_COUNT,TAX_CODE,TAX_VALUE,\
TAXABLE_AMOUNT,DISCOUNT_INFORMATION_COUNT,DISCOUNT_CODE,DISCOUNT,DISCOUNTABL\
E_AMT,HOME_CURNCY_CAMEL_FEE,HOME_CURNCY_CAMEL_TAX,HOME_CURNCY_CAMEL_DISCOUNT\
,HOME_CURNCY_CHARGE,HOME_CURNCY_TAX,HOME_CURNCY_DISCOUNT,HOME_CURNCY_SURCHAR\
GE,HOME_CURNCY_CHARGE_WITH_TAX,HOME_CURNCY_TOTAL_CHARGE,HOME_EXCHANGE_RATE,T\
AP_EXCHANGE_RATE_CODE,TAP_EXCHANGE_RATE,TAP_EXCHANGE_RATE_DECIMAL,TAP_TAX_TY\
PE_RATE,NETWORK_ACCESS_IDENTIFER,PDP_ADDRESS,APN_NI,APN_OI,CAUSE_FOR_TERMINA\
TION,PARTIAL_TYPE_INDICATOR,CHARGING_ID,SERVING_LOCATION_DESC,DATA_VOLUME_IN\
COMING,DATA_VOLUME_OUTGOING,SGSN_RECORDING_ENTITY_CODE1,SGSN_RECORDING_ENTIT\
Y_ID1,SGSN_RECORDING_ENTITY_CODE2,SGSN_RECORDING_ENTITY_ID2,SGSN_RECORDING_E\
NTITY_CODE3,SGSN_RECORDING_ENTITY_ID3,CAME");
   sqlstm.stmt = "L_APN_NI,CAMEL_APN_OI,A_USERID,B_USERID,EVENT_REFERENCE,NE\
TWORK_ELEMENT_TYPE1,NETWORK_ELEMENT_TYPE2,NETWORK_ELEMENT_ID1,NETWORK_ELEMENT_\
ID2,SGSN_RECORDING_ENTITY_TYPE1,SGSN_RECORDING_ENTITY_TYPE2) values (:b1,:b2,:\
b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b11,:b12,:b13,:b14,:b15,substr(:b16,1,30),:b1\
7,:b18,:b19,to_date(:b20,'YYYYMMDDHH24MISS'),:b21,:b22,:b23,:b24,:b25,:b26,:b2\
7,:b28,:b29,:b30,:b31,:b32,:b33,:b34,:b35,:b36,:b37,:b38,:b39,:b40,:b41,:b42,:\
b43,:b44,:b45,:b46,:b47,:b48,:b49,:b50,:b51,:b52,:b53,:b54,:b55,:b56,:b57,:b58\
,:b59,:b60,:b61,:b62,:b63,:b64,:b65,:b66,:b67,:b68,:b69,:b70,:b71,:b72,:b73,:b\
74,:b75,:b76,:b77,:b78,:b79,:b80,:b81,:b82,:b83,:b84,:b85,:b86,:b87,:b88,:b89,\
:b90,:b91,:b92,:b93,:b94,:b95,:b96,:b97,:b98,:b99,:b100,:b101,:b102,:b103,:b10\
4,:b105,:b106,:b107,:b108,:b109,:b110,:b111,:b112,:b113,:b114,:b115,:b116,:b11\
7,:b118,:b119,:b120,:b121)";
   sqlstm.iters = (unsigned int  )TotalCDRS;
   sqlstm.offset = (unsigned int  )2493;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)FILE_TRANSFER_DIRECTION;
   sqlstm.sqhstl[0] = (unsigned int  )2;
   sqlstm.sqhsts[0] = (         int  )2;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqharc[0] = (unsigned int   *)0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)HPLMN_CODE;
   sqlstm.sqhstl[1] = (unsigned int  )6;
   sqlstm.sqhsts[1] = (         int  )6;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqharc[1] = (unsigned int   *)0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)VPLMN_CODE;
   sqlstm.sqhstl[2] = (unsigned int  )6;
   sqlstm.sqhsts[2] = (         int  )6;
   sqlstm.sqindv[2] = (         void  *)0;
   sqlstm.sqinds[2] = (         int  )0;
   sqlstm.sqharm[2] = (unsigned int  )0;
   sqlstm.sqharc[2] = (unsigned int   *)0;
   sqlstm.sqadto[2] = (unsigned short )0;
   sqlstm.sqtdso[2] = (unsigned short )0;
   sqlstm.sqhstv[3] = (         void  *)PARTNER_CODE;
   sqlstm.sqhstl[3] = (unsigned int  )4;
   sqlstm.sqhsts[3] = (         int  )4;
   sqlstm.sqindv[3] = (         void  *)0;
   sqlstm.sqinds[3] = (         int  )0;
   sqlstm.sqharm[3] = (unsigned int  )0;
   sqlstm.sqharc[3] = (unsigned int   *)0;
   sqlstm.sqadto[3] = (unsigned short )0;
   sqlstm.sqtdso[3] = (unsigned short )0;
   sqlstm.sqhstv[4] = (         void  *)FILE_TYPE_INDICATOR;
   sqlstm.sqhstl[4] = (unsigned int  )2;
   sqlstm.sqhsts[4] = (         int  )2;
   sqlstm.sqindv[4] = (         void  *)0;
   sqlstm.sqinds[4] = (         int  )0;
   sqlstm.sqharm[4] = (unsigned int  )0;
   sqlstm.sqharc[4] = (unsigned int   *)0;
   sqlstm.sqadto[4] = (unsigned short )0;
   sqlstm.sqtdso[4] = (unsigned short )0;
   sqlstm.sqhstv[5] = (         void  *)FILE_SEQUENCE_NUMBER;
   sqlstm.sqhstl[5] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[5] = (         int  )sizeof(long);
   sqlstm.sqindv[5] = (         void  *)0;
   sqlstm.sqinds[5] = (         int  )0;
   sqlstm.sqharm[5] = (unsigned int  )0;
   sqlstm.sqharc[5] = (unsigned int   *)0;
   sqlstm.sqadto[5] = (unsigned short )0;
   sqlstm.sqtdso[5] = (unsigned short )0;
   sqlstm.sqhstv[6] = (         void  *)CALL_SEQUENCE;
   sqlstm.sqhstl[6] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[6] = (         int  )sizeof(double);
   sqlstm.sqindv[6] = (         void  *)0;
   sqlstm.sqinds[6] = (         int  )0;
   sqlstm.sqharm[6] = (unsigned int  )0;
   sqlstm.sqharc[6] = (unsigned int   *)0;
   sqlstm.sqadto[6] = (unsigned short )0;
   sqlstm.sqtdso[6] = (unsigned short )0;
   sqlstm.sqhstv[7] = (         void  *)CALLS_TYPE_INDICATOR;
   sqlstm.sqhstl[7] = (unsigned int  )2;
   sqlstm.sqhsts[7] = (         int  )2;
   sqlstm.sqindv[7] = (         void  *)0;
   sqlstm.sqinds[7] = (         int  )0;
   sqlstm.sqharm[7] = (unsigned int  )0;
   sqlstm.sqharc[7] = (unsigned int   *)0;
   sqlstm.sqadto[7] = (unsigned short )0;
   sqlstm.sqtdso[7] = (unsigned short )0;
   sqlstm.sqhstv[8] = (         void  *)CALL_TYPE;
   sqlstm.sqhstl[8] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[8] = (         int  )sizeof(long);
   sqlstm.sqindv[8] = (         void  *)0;
   sqlstm.sqinds[8] = (         int  )0;
   sqlstm.sqharm[8] = (unsigned int  )0;
   sqlstm.sqharc[8] = (unsigned int   *)0;
   sqlstm.sqadto[8] = (unsigned short )0;
   sqlstm.sqtdso[8] = (unsigned short )0;
   sqlstm.sqhstv[9] = (         void  *)SERVICE_CODE;
   sqlstm.sqhstl[9] = (unsigned int  )4;
   sqlstm.sqhsts[9] = (         int  )4;
   sqlstm.sqindv[9] = (         void  *)0;
   sqlstm.sqinds[9] = (         int  )0;
   sqlstm.sqharm[9] = (unsigned int  )0;
   sqlstm.sqharc[9] = (unsigned int   *)0;
   sqlstm.sqadto[9] = (unsigned short )0;
   sqlstm.sqtdso[9] = (unsigned short )0;
   sqlstm.sqhstv[10] = (         void  *)IMSI;
   sqlstm.sqhstl[10] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[10] = (         int  )sizeof(double);
   sqlstm.sqindv[10] = (         void  *)0;
   sqlstm.sqinds[10] = (         int  )0;
   sqlstm.sqharm[10] = (unsigned int  )0;
   sqlstm.sqharc[10] = (unsigned int   *)0;
   sqlstm.sqadto[10] = (unsigned short )0;
   sqlstm.sqtdso[10] = (unsigned short )0;
   sqlstm.sqhstv[11] = (         void  *)MSISDN;
   sqlstm.sqhstl[11] = (unsigned int  )26;
   sqlstm.sqhsts[11] = (         int  )26;
   sqlstm.sqindv[11] = (         void  *)0;
   sqlstm.sqinds[11] = (         int  )0;
   sqlstm.sqharm[11] = (unsigned int  )0;
   sqlstm.sqharc[11] = (unsigned int   *)0;
   sqlstm.sqadto[11] = (unsigned short )0;
   sqlstm.sqtdso[11] = (unsigned short )0;
   sqlstm.sqhstv[12] = (         void  *)RAPFILE_SEQUENCE_NUMBER;
   sqlstm.sqhstl[12] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[12] = (         int  )sizeof(long);
   sqlstm.sqindv[12] = (         void  *)0;
   sqlstm.sqinds[12] = (         int  )0;
   sqlstm.sqharm[12] = (unsigned int  )0;
   sqlstm.sqharc[12] = (unsigned int   *)0;
   sqlstm.sqadto[12] = (unsigned short )0;
   sqlstm.sqtdso[12] = (unsigned short )0;
   sqlstm.sqhstv[13] = (         void  *)CALLED_CALLING_NUMBER;
   sqlstm.sqhstl[13] = (unsigned int  )87;
   sqlstm.sqhsts[13] = (         int  )87;
   sqlstm.sqindv[13] = (         void  *)0;
   sqlstm.sqinds[13] = (         int  )0;
   sqlstm.sqharm[13] = (unsigned int  )0;
   sqlstm.sqharc[13] = (unsigned int   *)0;
   sqlstm.sqadto[13] = (unsigned short )0;
   sqlstm.sqtdso[13] = (unsigned short )0;
   sqlstm.sqhstv[14] = (         void  *)DIALLED_DIGITS;
   sqlstm.sqhstl[14] = (unsigned int  )87;
   sqlstm.sqhsts[14] = (         int  )87;
   sqlstm.sqindv[14] = (         void  *)0;
   sqlstm.sqinds[14] = (         int  )0;
   sqlstm.sqharm[14] = (unsigned int  )0;
   sqlstm.sqharc[14] = (unsigned int   *)0;
   sqlstm.sqadto[14] = (unsigned short )0;
   sqlstm.sqtdso[14] = (unsigned short )0;
   sqlstm.sqhstv[15] = (         void  *)CALLED_PLACE;
   sqlstm.sqhstl[15] = (unsigned int  )46;
   sqlstm.sqhsts[15] = (         int  )46;
   sqlstm.sqindv[15] = (         void  *)0;
   sqlstm.sqinds[15] = (         int  )0;
   sqlstm.sqharm[15] = (unsigned int  )0;
   sqlstm.sqharc[15] = (unsigned int   *)0;
   sqlstm.sqadto[15] = (unsigned short )0;
   sqlstm.sqtdso[15] = (unsigned short )0;
   sqlstm.sqhstv[16] = (         void  *)CALLED_REGION;
   sqlstm.sqhstl[16] = (unsigned int  )46;
   sqlstm.sqhsts[16] = (         int  )46;
   sqlstm.sqindv[16] = (         void  *)0;
   sqlstm.sqinds[16] = (         int  )0;
   sqlstm.sqharm[16] = (unsigned int  )0;
   sqlstm.sqharc[16] = (unsigned int   *)0;
   sqlstm.sqadto[16] = (unsigned short )0;
   sqlstm.sqtdso[16] = (unsigned short )0;
   sqlstm.sqhstv[17] = (         void  *)CLIR_INDICATOR;
   sqlstm.sqhstl[17] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[17] = (         int  )sizeof(long);
   sqlstm.sqindv[17] = (         void  *)0;
   sqlstm.sqinds[17] = (         int  )0;
   sqlstm.sqharm[17] = (unsigned int  )0;
   sqlstm.sqharc[17] = (unsigned int   *)0;
   sqlstm.sqadto[17] = (unsigned short )0;
   sqlstm.sqtdso[17] = (unsigned short )0;
   sqlstm.sqhstv[18] = (         void  *)DESTINATION_NETWORK;
   sqlstm.sqhstl[18] = (unsigned int  )7;
   sqlstm.sqhsts[18] = (         int  )7;
   sqlstm.sqindv[18] = (         void  *)0;
   sqlstm.sqinds[18] = (         int  )0;
   sqlstm.sqharm[18] = (unsigned int  )0;
   sqlstm.sqharc[18] = (unsigned int   *)0;
   sqlstm.sqadto[18] = (unsigned short )0;
   sqlstm.sqtdso[18] = (unsigned short )0;
   sqlstm.sqhstv[19] = (         void  *)CALL_DATE;
   sqlstm.sqhstl[19] = (unsigned int  )15;
   sqlstm.sqhsts[19] = (         int  )15;
   sqlstm.sqindv[19] = (         void  *)0;
   sqlstm.sqinds[19] = (         int  )0;
   sqlstm.sqharm[19] = (unsigned int  )0;
   sqlstm.sqharc[19] = (unsigned int   *)0;
   sqlstm.sqadto[19] = (unsigned short )0;
   sqlstm.sqtdso[19] = (unsigned short )0;
   sqlstm.sqhstv[20] = (         void  *)UTC_OFFSET_CODE;
   sqlstm.sqhstl[20] = (unsigned int  )6;
   sqlstm.sqhsts[20] = (         int  )6;
   sqlstm.sqindv[20] = (         void  *)0;
   sqlstm.sqinds[20] = (         int  )0;
   sqlstm.sqharm[20] = (unsigned int  )0;
   sqlstm.sqharc[20] = (unsigned int   *)0;
   sqlstm.sqadto[20] = (unsigned short )0;
   sqlstm.sqtdso[20] = (unsigned short )0;
   sqlstm.sqhstv[21] = (         void  *)CALL_DURATION;
   sqlstm.sqhstl[21] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[21] = (         int  )sizeof(long);
   sqlstm.sqindv[21] = (         void  *)0;
   sqlstm.sqinds[21] = (         int  )0;
   sqlstm.sqharm[21] = (unsigned int  )0;
   sqlstm.sqharc[21] = (unsigned int   *)0;
   sqlstm.sqadto[21] = (unsigned short )0;
   sqlstm.sqtdso[21] = (unsigned short )0;
   sqlstm.sqhstv[22] = (         void  *)SIM_TOOLKIT_INDICATOR;
   sqlstm.sqhstl[22] = (unsigned int  )2;
   sqlstm.sqhsts[22] = (         int  )2;
   sqlstm.sqindv[22] = (         void  *)0;
   sqlstm.sqinds[22] = (         int  )0;
   sqlstm.sqharm[22] = (unsigned int  )0;
   sqlstm.sqharc[22] = (unsigned int   *)0;
   sqlstm.sqadto[22] = (unsigned short )0;
   sqlstm.sqtdso[22] = (unsigned short )0;
   sqlstm.sqhstv[23] = (         void  *)RECORDING_ENTITY_CODE;
   sqlstm.sqhstl[23] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[23] = (         int  )sizeof(long);
   sqlstm.sqindv[23] = (         void  *)0;
   sqlstm.sqinds[23] = (         int  )0;
   sqlstm.sqharm[23] = (unsigned int  )0;
   sqlstm.sqharc[23] = (unsigned int   *)0;
   sqlstm.sqadto[23] = (unsigned short )0;
   sqlstm.sqtdso[23] = (unsigned short )0;
   sqlstm.sqhstv[24] = (         void  *)RECORDING_ENTITY_TYPE;
   sqlstm.sqhstl[24] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[24] = (         int  )sizeof(long);
   sqlstm.sqindv[24] = (         void  *)0;
   sqlstm.sqinds[24] = (         int  )0;
   sqlstm.sqharm[24] = (unsigned int  )0;
   sqlstm.sqharc[24] = (unsigned int   *)0;
   sqlstm.sqadto[24] = (unsigned short )0;
   sqlstm.sqtdso[24] = (unsigned short )0;
   sqlstm.sqhstv[25] = (         void  *)RECORDING_ENTITY_ID;
   sqlstm.sqhstl[25] = (unsigned int  )46;
   sqlstm.sqhsts[25] = (         int  )46;
   sqlstm.sqindv[25] = (         void  *)0;
   sqlstm.sqinds[25] = (         int  )0;
   sqlstm.sqharm[25] = (unsigned int  )0;
   sqlstm.sqharc[25] = (unsigned int   *)0;
   sqlstm.sqadto[25] = (unsigned short )0;
   sqlstm.sqtdso[25] = (unsigned short )0;
   sqlstm.sqhstv[26] = (         void  *)CALL_REFERENCE;
   sqlstm.sqhstl[26] = (unsigned int  )21;
   sqlstm.sqhsts[26] = (         int  )21;
   sqlstm.sqindv[26] = (         void  *)0;
   sqlstm.sqinds[26] = (         int  )0;
   sqlstm.sqharm[26] = (unsigned int  )0;
   sqlstm.sqharc[26] = (unsigned int   *)0;
   sqlstm.sqadto[26] = (unsigned short )0;
   sqlstm.sqtdso[26] = (unsigned short )0;
   sqlstm.sqhstv[27] = (         void  *)LOCATION_AREA;
   sqlstm.sqhstl[27] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[27] = (         int  )sizeof(double);
   sqlstm.sqindv[27] = (         void  *)0;
   sqlstm.sqinds[27] = (         int  )0;
   sqlstm.sqharm[27] = (unsigned int  )0;
   sqlstm.sqharc[27] = (unsigned int   *)0;
   sqlstm.sqadto[27] = (unsigned short )0;
   sqlstm.sqtdso[27] = (unsigned short )0;
   sqlstm.sqhstv[28] = (         void  *)CELLID;
   sqlstm.sqhstl[28] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[28] = (         int  )sizeof(double);
   sqlstm.sqindv[28] = (         void  *)0;
   sqlstm.sqinds[28] = (         int  )0;
   sqlstm.sqharm[28] = (unsigned int  )0;
   sqlstm.sqharc[28] = (unsigned int   *)0;
   sqlstm.sqadto[28] = (unsigned short )0;
   sqlstm.sqtdso[28] = (unsigned short )0;
   sqlstm.sqhstv[29] = (         void  *)SERVING_NETWORK;
   sqlstm.sqhstl[29] = (unsigned int  )6;
   sqlstm.sqhsts[29] = (         int  )6;
   sqlstm.sqindv[29] = (         void  *)0;
   sqlstm.sqinds[29] = (         int  )0;
   sqlstm.sqharm[29] = (unsigned int  )0;
   sqlstm.sqharc[29] = (unsigned int   *)0;
   sqlstm.sqadto[29] = (unsigned short )0;
   sqlstm.sqtdso[29] = (unsigned short )0;
   sqlstm.sqhstv[30] = (         void  *)IMEI;
   sqlstm.sqhstl[30] = (unsigned int  )21;
   sqlstm.sqhsts[30] = (         int  )21;
   sqlstm.sqindv[30] = (         void  *)0;
   sqlstm.sqinds[30] = (         int  )0;
   sqlstm.sqharm[30] = (unsigned int  )0;
   sqlstm.sqharc[30] = (unsigned int   *)0;
   sqlstm.sqadto[30] = (unsigned short )0;
   sqlstm.sqtdso[30] = (unsigned short )0;
   sqlstm.sqhstv[31] = (         void  *)BASIC_SERVICE_TYPE;
   sqlstm.sqhstl[31] = (unsigned int  )2;
   sqlstm.sqhsts[31] = (         int  )2;
   sqlstm.sqindv[31] = (         void  *)0;
   sqlstm.sqinds[31] = (         int  )0;
   sqlstm.sqharm[31] = (unsigned int  )0;
   sqlstm.sqharc[31] = (unsigned int   *)0;
   sqlstm.sqadto[31] = (unsigned short )0;
   sqlstm.sqtdso[31] = (unsigned short )0;
   sqlstm.sqhstv[32] = (         void  *)BASIC_SERVICE_CODE;
   sqlstm.sqhstl[32] = (unsigned int  )4;
   sqlstm.sqhsts[32] = (         int  )4;
   sqlstm.sqindv[32] = (         void  *)0;
   sqlstm.sqinds[32] = (         int  )0;
   sqlstm.sqharm[32] = (unsigned int  )0;
   sqlstm.sqharc[32] = (unsigned int   *)0;
   sqlstm.sqadto[32] = (unsigned short )0;
   sqlstm.sqtdso[32] = (unsigned short )0;
   sqlstm.sqhstv[33] = (         void  *)TRANSPARENCY_INDICATOR;
   sqlstm.sqhstl[33] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[33] = (         int  )sizeof(long);
   sqlstm.sqindv[33] = (         void  *)0;
   sqlstm.sqinds[33] = (         int  )0;
   sqlstm.sqharm[33] = (unsigned int  )0;
   sqlstm.sqharc[33] = (unsigned int   *)0;
   sqlstm.sqadto[33] = (unsigned short )0;
   sqlstm.sqtdso[33] = (unsigned short )0;
   sqlstm.sqhstv[34] = (         void  *)FNUR;
   sqlstm.sqhstl[34] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[34] = (         int  )sizeof(double);
   sqlstm.sqindv[34] = (         void  *)0;
   sqlstm.sqinds[34] = (         int  )0;
   sqlstm.sqharm[34] = (unsigned int  )0;
   sqlstm.sqharc[34] = (unsigned int   *)0;
   sqlstm.sqadto[34] = (unsigned short )0;
   sqlstm.sqtdso[34] = (unsigned short )0;
   sqlstm.sqhstv[35] = (         void  *)USER_PROTOCOL_INDICATOR;
   sqlstm.sqhstl[35] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[35] = (         int  )sizeof(double);
   sqlstm.sqindv[35] = (         void  *)0;
   sqlstm.sqinds[35] = (         int  )0;
   sqlstm.sqharm[35] = (unsigned int  )0;
   sqlstm.sqharc[35] = (unsigned int   *)0;
   sqlstm.sqadto[35] = (unsigned short )0;
   sqlstm.sqtdso[35] = (unsigned short )0;
   sqlstm.sqhstv[36] = (         void  *)GUARANTEED_BIT_RATE;
   sqlstm.sqhstl[36] = (unsigned int  )6;
   sqlstm.sqhsts[36] = (         int  )6;
   sqlstm.sqindv[36] = (         void  *)0;
   sqlstm.sqinds[36] = (         int  )0;
   sqlstm.sqharm[36] = (unsigned int  )0;
   sqlstm.sqharc[36] = (unsigned int   *)0;
   sqlstm.sqadto[36] = (unsigned short )0;
   sqlstm.sqtdso[36] = (unsigned short )0;
   sqlstm.sqhstv[37] = (         void  *)MAXIMUM_BIT_RATE;
   sqlstm.sqhstl[37] = (unsigned int  )6;
   sqlstm.sqhsts[37] = (         int  )6;
   sqlstm.sqindv[37] = (         void  *)0;
   sqlstm.sqinds[37] = (         int  )0;
   sqlstm.sqharm[37] = (unsigned int  )0;
   sqlstm.sqharc[37] = (unsigned int   *)0;
   sqlstm.sqadto[37] = (unsigned short )0;
   sqlstm.sqtdso[37] = (unsigned short )0;
   sqlstm.sqhstv[38] = (         void  *)HSCSD_INDICATOR;
   sqlstm.sqhstl[38] = (unsigned int  )4;
   sqlstm.sqhsts[38] = (         int  )4;
   sqlstm.sqindv[38] = (         void  *)0;
   sqlstm.sqinds[38] = (         int  )0;
   sqlstm.sqharm[38] = (unsigned int  )0;
   sqlstm.sqharc[38] = (unsigned int   *)0;
   sqlstm.sqadto[38] = (unsigned short )0;
   sqlstm.sqtdso[38] = (unsigned short )0;
   sqlstm.sqhstv[39] = (         void  *)SUPPLIMENTARY_SERVICE_CODE;
   sqlstm.sqhstl[39] = (unsigned int  )21;
   sqlstm.sqhsts[39] = (         int  )21;
   sqlstm.sqindv[39] = (         void  *)0;
   sqlstm.sqinds[39] = (         int  )0;
   sqlstm.sqharm[39] = (unsigned int  )0;
   sqlstm.sqharc[39] = (unsigned int   *)0;
   sqlstm.sqadto[39] = (unsigned short )0;
   sqlstm.sqtdso[39] = (unsigned short )0;
   sqlstm.sqhstv[40] = (         void  *)SUPPLIMENTARY_ACTION_CODE;
   sqlstm.sqhstl[40] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[40] = (         int  )sizeof(long);
   sqlstm.sqindv[40] = (         void  *)0;
   sqlstm.sqinds[40] = (         int  )0;
   sqlstm.sqharm[40] = (unsigned int  )0;
   sqlstm.sqharc[40] = (unsigned int   *)0;
   sqlstm.sqadto[40] = (unsigned short )0;
   sqlstm.sqtdso[40] = (unsigned short )0;
   sqlstm.sqhstv[41] = (         void  *)SUPPLIMENTARY_SERVICE_PARAMS;
   sqlstm.sqhstl[41] = (unsigned int  )46;
   sqlstm.sqhsts[41] = (         int  )46;
   sqlstm.sqindv[41] = (         void  *)0;
   sqlstm.sqinds[41] = (         int  )0;
   sqlstm.sqharm[41] = (unsigned int  )0;
   sqlstm.sqharc[41] = (unsigned int   *)0;
   sqlstm.sqadto[41] = (unsigned short )0;
   sqlstm.sqtdso[41] = (unsigned short )0;
   sqlstm.sqhstv[42] = (         void  *)THIRD_PARTY_NUMBER;
   sqlstm.sqhstl[42] = (unsigned int  )87;
   sqlstm.sqhsts[42] = (         int  )87;
   sqlstm.sqindv[42] = (         void  *)0;
   sqlstm.sqinds[42] = (         int  )0;
   sqlstm.sqharm[42] = (unsigned int  )0;
   sqlstm.sqharc[42] = (unsigned int   *)0;
   sqlstm.sqadto[42] = (unsigned short )0;
   sqlstm.sqtdso[42] = (unsigned short )0;
   sqlstm.sqhstv[43] = (         void  *)THIRD_PARTY_CLIR_INDICATOR;
   sqlstm.sqhstl[43] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[43] = (         int  )sizeof(long);
   sqlstm.sqindv[43] = (         void  *)0;
   sqlstm.sqinds[43] = (         int  )0;
   sqlstm.sqharm[43] = (unsigned int  )0;
   sqlstm.sqharc[43] = (unsigned int   *)0;
   sqlstm.sqadto[43] = (unsigned short )0;
   sqlstm.sqtdso[43] = (unsigned short )0;
   sqlstm.sqhstv[44] = (         void  *)CAMEL_USED_FLAG;
   sqlstm.sqhstl[44] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[44] = (         int  )sizeof(long);
   sqlstm.sqindv[44] = (         void  *)0;
   sqlstm.sqinds[44] = (         int  )0;
   sqlstm.sqharm[44] = (unsigned int  )0;
   sqlstm.sqharc[44] = (unsigned int   *)0;
   sqlstm.sqadto[44] = (unsigned short )0;
   sqlstm.sqtdso[44] = (unsigned short )0;
   sqlstm.sqhstv[45] = (         void  *)CAMEL_SERVICE_LEVEL;
   sqlstm.sqhstl[45] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[45] = (         int  )sizeof(double);
   sqlstm.sqindv[45] = (         void  *)0;
   sqlstm.sqinds[45] = (         int  )0;
   sqlstm.sqharm[45] = (unsigned int  )0;
   sqlstm.sqharc[45] = (unsigned int   *)0;
   sqlstm.sqadto[45] = (unsigned short )0;
   sqlstm.sqtdso[45] = (unsigned short )0;
   sqlstm.sqhstv[46] = (         void  *)CAMEL_SERVICE_KEY;
   sqlstm.sqhstl[46] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[46] = (         int  )sizeof(double);
   sqlstm.sqindv[46] = (         void  *)0;
   sqlstm.sqinds[46] = (         int  )0;
   sqlstm.sqharm[46] = (unsigned int  )0;
   sqlstm.sqharc[46] = (unsigned int   *)0;
   sqlstm.sqadto[46] = (unsigned short )0;
   sqlstm.sqtdso[46] = (unsigned short )0;
   sqlstm.sqhstv[47] = (         void  *)CAMEL_DEFAULT_CALL_HANDLING;
   sqlstm.sqhstl[47] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[47] = (         int  )sizeof(double);
   sqlstm.sqindv[47] = (         void  *)0;
   sqlstm.sqinds[47] = (         int  )0;
   sqlstm.sqharm[47] = (unsigned int  )0;
   sqlstm.sqharc[47] = (unsigned int   *)0;
   sqlstm.sqadto[47] = (unsigned short )0;
   sqlstm.sqtdso[47] = (unsigned short )0;
   sqlstm.sqhstv[48] = (         void  *)CAMEL_EXCHANGE_RATE_CODE;
   sqlstm.sqhstl[48] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[48] = (         int  )sizeof(long);
   sqlstm.sqindv[48] = (         void  *)0;
   sqlstm.sqinds[48] = (         int  )0;
   sqlstm.sqharm[48] = (unsigned int  )0;
   sqlstm.sqharc[48] = (unsigned int   *)0;
   sqlstm.sqadto[48] = (unsigned short )0;
   sqlstm.sqtdso[48] = (unsigned short )0;
   sqlstm.sqhstv[49] = (         void  *)HOME_CAMEL_EXCHANGE_RATE;
   sqlstm.sqhstl[49] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[49] = (         int  )sizeof(double);
   sqlstm.sqindv[49] = (         void  *)0;
   sqlstm.sqinds[49] = (         int  )0;
   sqlstm.sqharm[49] = (unsigned int  )0;
   sqlstm.sqharc[49] = (unsigned int   *)0;
   sqlstm.sqadto[49] = (unsigned short )0;
   sqlstm.sqtdso[49] = (unsigned short )0;
   sqlstm.sqhstv[50] = (         void  *)CAMEL_INVOCATION_FEE;
   sqlstm.sqhstl[50] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[50] = (         int  )sizeof(double);
   sqlstm.sqindv[50] = (         void  *)0;
   sqlstm.sqinds[50] = (         int  )0;
   sqlstm.sqharm[50] = (unsigned int  )0;
   sqlstm.sqharc[50] = (unsigned int   *)0;
   sqlstm.sqadto[50] = (unsigned short )0;
   sqlstm.sqtdso[50] = (unsigned short )0;
   sqlstm.sqhstv[51] = (         void  *)CAMEL_DISCOUNT_CODE;
   sqlstm.sqhstl[51] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[51] = (         int  )sizeof(long);
   sqlstm.sqindv[51] = (         void  *)0;
   sqlstm.sqinds[51] = (         int  )0;
   sqlstm.sqharm[51] = (unsigned int  )0;
   sqlstm.sqharc[51] = (unsigned int   *)0;
   sqlstm.sqadto[51] = (unsigned short )0;
   sqlstm.sqtdso[51] = (unsigned short )0;
   sqlstm.sqhstv[52] = (         void  *)CAMEL_DISCOUNT;
   sqlstm.sqhstl[52] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[52] = (         int  )sizeof(double);
   sqlstm.sqindv[52] = (         void  *)0;
   sqlstm.sqinds[52] = (         int  )0;
   sqlstm.sqharm[52] = (unsigned int  )0;
   sqlstm.sqharc[52] = (unsigned int   *)0;
   sqlstm.sqadto[52] = (unsigned short )0;
   sqlstm.sqtdso[52] = (unsigned short )0;
   sqlstm.sqhstv[53] = (         void  *)CAMEL_DISCOUNTABLE_AMOUNT;
   sqlstm.sqhstl[53] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[53] = (         int  )sizeof(double);
   sqlstm.sqindv[53] = (         void  *)0;
   sqlstm.sqinds[53] = (         int  )0;
   sqlstm.sqharm[53] = (unsigned int  )0;
   sqlstm.sqharc[53] = (unsigned int   *)0;
   sqlstm.sqadto[53] = (unsigned short )0;
   sqlstm.sqtdso[53] = (unsigned short )0;
   sqlstm.sqhstv[54] = (         void  *)CAMEL_TAX_INFORMATION_COUNT;
   sqlstm.sqhstl[54] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[54] = (         int  )sizeof(long);
   sqlstm.sqindv[54] = (         void  *)0;
   sqlstm.sqinds[54] = (         int  )0;
   sqlstm.sqharm[54] = (unsigned int  )0;
   sqlstm.sqharc[54] = (unsigned int   *)0;
   sqlstm.sqadto[54] = (unsigned short )0;
   sqlstm.sqtdso[54] = (unsigned short )0;
   sqlstm.sqhstv[55] = (         void  *)CAMEL_TAX_CODE;
   sqlstm.sqhstl[55] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[55] = (         int  )sizeof(long);
   sqlstm.sqindv[55] = (         void  *)0;
   sqlstm.sqinds[55] = (         int  )0;
   sqlstm.sqharm[55] = (unsigned int  )0;
   sqlstm.sqharc[55] = (unsigned int   *)0;
   sqlstm.sqadto[55] = (unsigned short )0;
   sqlstm.sqtdso[55] = (unsigned short )0;
   sqlstm.sqhstv[56] = (         void  *)CAMEL_TAX_VALUE;
   sqlstm.sqhstl[56] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[56] = (         int  )sizeof(double);
   sqlstm.sqindv[56] = (         void  *)0;
   sqlstm.sqinds[56] = (         int  )0;
   sqlstm.sqharm[56] = (unsigned int  )0;
   sqlstm.sqharc[56] = (unsigned int   *)0;
   sqlstm.sqadto[56] = (unsigned short )0;
   sqlstm.sqtdso[56] = (unsigned short )0;
   sqlstm.sqhstv[57] = (         void  *)CAMEL_TAXABLE_AMOUNT;
   sqlstm.sqhstl[57] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[57] = (         int  )sizeof(double);
   sqlstm.sqindv[57] = (         void  *)0;
   sqlstm.sqinds[57] = (         int  )0;
   sqlstm.sqharm[57] = (unsigned int  )0;
   sqlstm.sqharc[57] = (unsigned int   *)0;
   sqlstm.sqadto[57] = (unsigned short )0;
   sqlstm.sqtdso[57] = (unsigned short )0;
   sqlstm.sqhstv[58] = (         void  *)CAMEL_DESTINATION_NUMBER;
   sqlstm.sqhstl[58] = (unsigned int  )87;
   sqlstm.sqhsts[58] = (         int  )87;
   sqlstm.sqindv[58] = (         void  *)0;
   sqlstm.sqinds[58] = (         int  )0;
   sqlstm.sqharm[58] = (unsigned int  )0;
   sqlstm.sqharc[58] = (unsigned int   *)0;
   sqlstm.sqadto[58] = (unsigned short )0;
   sqlstm.sqtdso[58] = (unsigned short )0;
   sqlstm.sqhstv[59] = (         void  *)CALL_TYPE_LEVEL1;
   sqlstm.sqhstl[59] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[59] = (         int  )sizeof(long);
   sqlstm.sqindv[59] = (         void  *)0;
   sqlstm.sqinds[59] = (         int  )0;
   sqlstm.sqharm[59] = (unsigned int  )0;
   sqlstm.sqharc[59] = (unsigned int   *)0;
   sqlstm.sqadto[59] = (unsigned short )0;
   sqlstm.sqtdso[59] = (unsigned short )0;
   sqlstm.sqhstv[60] = (         void  *)CALL_TYPE_LEVEL2;
   sqlstm.sqhstl[60] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[60] = (         int  )sizeof(long);
   sqlstm.sqindv[60] = (         void  *)0;
   sqlstm.sqinds[60] = (         int  )0;
   sqlstm.sqharm[60] = (unsigned int  )0;
   sqlstm.sqharc[60] = (unsigned int   *)0;
   sqlstm.sqadto[60] = (unsigned short )0;
   sqlstm.sqtdso[60] = (unsigned short )0;
   sqlstm.sqhstv[61] = (         void  *)CALL_TYPE_LEVEL3;
   sqlstm.sqhstl[61] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[61] = (         int  )sizeof(long);
   sqlstm.sqindv[61] = (         void  *)0;
   sqlstm.sqinds[61] = (         int  )0;
   sqlstm.sqharm[61] = (unsigned int  )0;
   sqlstm.sqharc[61] = (unsigned int   *)0;
   sqlstm.sqadto[61] = (unsigned short )0;
   sqlstm.sqtdso[61] = (unsigned short )0;
   sqlstm.sqhstv[62] = (         void  *)CHARGE_INFORMATION_COUNT;
   sqlstm.sqhstl[62] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[62] = (         int  )sizeof(long);
   sqlstm.sqindv[62] = (         void  *)0;
   sqlstm.sqinds[62] = (         int  )0;
   sqlstm.sqharm[62] = (unsigned int  )0;
   sqlstm.sqharc[62] = (unsigned int   *)0;
   sqlstm.sqadto[62] = (unsigned short )0;
   sqlstm.sqtdso[62] = (unsigned short )0;
   sqlstm.sqhstv[63] = (         void  *)CHARGED_ITEM;
   sqlstm.sqhstl[63] = (unsigned int  )4;
   sqlstm.sqhsts[63] = (         int  )4;
   sqlstm.sqindv[63] = (         void  *)0;
   sqlstm.sqinds[63] = (         int  )0;
   sqlstm.sqharm[63] = (unsigned int  )0;
   sqlstm.sqharc[63] = (unsigned int   *)0;
   sqlstm.sqadto[63] = (unsigned short )0;
   sqlstm.sqtdso[63] = (unsigned short )0;
   sqlstm.sqhstv[64] = (         void  *)CHARGE_TYPE;
   sqlstm.sqhstl[64] = (unsigned int  )4;
   sqlstm.sqhsts[64] = (         int  )4;
   sqlstm.sqindv[64] = (         void  *)0;
   sqlstm.sqinds[64] = (         int  )0;
   sqlstm.sqharm[64] = (unsigned int  )0;
   sqlstm.sqharc[64] = (unsigned int   *)0;
   sqlstm.sqadto[64] = (unsigned short )0;
   sqlstm.sqtdso[64] = (unsigned short )0;
   sqlstm.sqhstv[65] = (         void  *)CHARGEABLE_UNITS;
   sqlstm.sqhstl[65] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[65] = (         int  )sizeof(double);
   sqlstm.sqindv[65] = (         void  *)0;
   sqlstm.sqinds[65] = (         int  )0;
   sqlstm.sqharm[65] = (unsigned int  )0;
   sqlstm.sqharc[65] = (unsigned int   *)0;
   sqlstm.sqadto[65] = (unsigned short )0;
   sqlstm.sqtdso[65] = (unsigned short )0;
   sqlstm.sqhstv[66] = (         void  *)CHARGED_UNITS;
   sqlstm.sqhstl[66] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[66] = (         int  )sizeof(double);
   sqlstm.sqindv[66] = (         void  *)0;
   sqlstm.sqinds[66] = (         int  )0;
   sqlstm.sqharm[66] = (unsigned int  )0;
   sqlstm.sqharc[66] = (unsigned int   *)0;
   sqlstm.sqadto[66] = (unsigned short )0;
   sqlstm.sqtdso[66] = (unsigned short )0;
   sqlstm.sqhstv[67] = (         void  *)CHARGE;
   sqlstm.sqhstl[67] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[67] = (         int  )sizeof(double);
   sqlstm.sqindv[67] = (         void  *)0;
   sqlstm.sqinds[67] = (         int  )0;
   sqlstm.sqharm[67] = (unsigned int  )0;
   sqlstm.sqharc[67] = (unsigned int   *)0;
   sqlstm.sqadto[67] = (unsigned short )0;
   sqlstm.sqtdso[67] = (unsigned short )0;
   sqlstm.sqhstv[68] = (         void  *)CHARGE_TYPE1;
   sqlstm.sqhstl[68] = (unsigned int  )4;
   sqlstm.sqhsts[68] = (         int  )4;
   sqlstm.sqindv[68] = (         void  *)0;
   sqlstm.sqinds[68] = (         int  )0;
   sqlstm.sqharm[68] = (unsigned int  )0;
   sqlstm.sqharc[68] = (unsigned int   *)0;
   sqlstm.sqadto[68] = (unsigned short )0;
   sqlstm.sqtdso[68] = (unsigned short )0;
   sqlstm.sqhstv[69] = (         void  *)CHARGEABLE_UNITS1;
   sqlstm.sqhstl[69] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[69] = (         int  )sizeof(double);
   sqlstm.sqindv[69] = (         void  *)0;
   sqlstm.sqinds[69] = (         int  )0;
   sqlstm.sqharm[69] = (unsigned int  )0;
   sqlstm.sqharc[69] = (unsigned int   *)0;
   sqlstm.sqadto[69] = (unsigned short )0;
   sqlstm.sqtdso[69] = (unsigned short )0;
   sqlstm.sqhstv[70] = (         void  *)CHARGED_UNITS1;
   sqlstm.sqhstl[70] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[70] = (         int  )sizeof(double);
   sqlstm.sqindv[70] = (         void  *)0;
   sqlstm.sqinds[70] = (         int  )0;
   sqlstm.sqharm[70] = (unsigned int  )0;
   sqlstm.sqharc[70] = (unsigned int   *)0;
   sqlstm.sqadto[70] = (unsigned short )0;
   sqlstm.sqtdso[70] = (unsigned short )0;
   sqlstm.sqhstv[71] = (         void  *)CHARGE1;
   sqlstm.sqhstl[71] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[71] = (         int  )sizeof(double);
   sqlstm.sqindv[71] = (         void  *)0;
   sqlstm.sqinds[71] = (         int  )0;
   sqlstm.sqharm[71] = (unsigned int  )0;
   sqlstm.sqharc[71] = (unsigned int   *)0;
   sqlstm.sqadto[71] = (unsigned short )0;
   sqlstm.sqtdso[71] = (unsigned short )0;
   sqlstm.sqhstv[72] = (         void  *)TAX_INFORMATION_COUNT;
   sqlstm.sqhstl[72] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[72] = (         int  )sizeof(long);
   sqlstm.sqindv[72] = (         void  *)0;
   sqlstm.sqinds[72] = (         int  )0;
   sqlstm.sqharm[72] = (unsigned int  )0;
   sqlstm.sqharc[72] = (unsigned int   *)0;
   sqlstm.sqadto[72] = (unsigned short )0;
   sqlstm.sqtdso[72] = (unsigned short )0;
   sqlstm.sqhstv[73] = (         void  *)TAX_CODE;
   sqlstm.sqhstl[73] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[73] = (         int  )sizeof(long);
   sqlstm.sqindv[73] = (         void  *)0;
   sqlstm.sqinds[73] = (         int  )0;
   sqlstm.sqharm[73] = (unsigned int  )0;
   sqlstm.sqharc[73] = (unsigned int   *)0;
   sqlstm.sqadto[73] = (unsigned short )0;
   sqlstm.sqtdso[73] = (unsigned short )0;
   sqlstm.sqhstv[74] = (         void  *)TAX_VALUE;
   sqlstm.sqhstl[74] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[74] = (         int  )sizeof(long);
   sqlstm.sqindv[74] = (         void  *)0;
   sqlstm.sqinds[74] = (         int  )0;
   sqlstm.sqharm[74] = (unsigned int  )0;
   sqlstm.sqharc[74] = (unsigned int   *)0;
   sqlstm.sqadto[74] = (unsigned short )0;
   sqlstm.sqtdso[74] = (unsigned short )0;
   sqlstm.sqhstv[75] = (         void  *)TAXABLE_AMOUNT;
   sqlstm.sqhstl[75] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[75] = (         int  )sizeof(double);
   sqlstm.sqindv[75] = (         void  *)0;
   sqlstm.sqinds[75] = (         int  )0;
   sqlstm.sqharm[75] = (unsigned int  )0;
   sqlstm.sqharc[75] = (unsigned int   *)0;
   sqlstm.sqadto[75] = (unsigned short )0;
   sqlstm.sqtdso[75] = (unsigned short )0;
   sqlstm.sqhstv[76] = (         void  *)DISCOUNT_INFORMATION_COUNT;
   sqlstm.sqhstl[76] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[76] = (         int  )sizeof(long);
   sqlstm.sqindv[76] = (         void  *)0;
   sqlstm.sqinds[76] = (         int  )0;
   sqlstm.sqharm[76] = (unsigned int  )0;
   sqlstm.sqharc[76] = (unsigned int   *)0;
   sqlstm.sqadto[76] = (unsigned short )0;
   sqlstm.sqtdso[76] = (unsigned short )0;
   sqlstm.sqhstv[77] = (         void  *)DISCOUNT_CODE;
   sqlstm.sqhstl[77] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[77] = (         int  )sizeof(long);
   sqlstm.sqindv[77] = (         void  *)0;
   sqlstm.sqinds[77] = (         int  )0;
   sqlstm.sqharm[77] = (unsigned int  )0;
   sqlstm.sqharc[77] = (unsigned int   *)0;
   sqlstm.sqadto[77] = (unsigned short )0;
   sqlstm.sqtdso[77] = (unsigned short )0;
   sqlstm.sqhstv[78] = (         void  *)DISCOUNT;
   sqlstm.sqhstl[78] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[78] = (         int  )sizeof(double);
   sqlstm.sqindv[78] = (         void  *)0;
   sqlstm.sqinds[78] = (         int  )0;
   sqlstm.sqharm[78] = (unsigned int  )0;
   sqlstm.sqharc[78] = (unsigned int   *)0;
   sqlstm.sqadto[78] = (unsigned short )0;
   sqlstm.sqtdso[78] = (unsigned short )0;
   sqlstm.sqhstv[79] = (         void  *)DISCOUNTABLE_AMT;
   sqlstm.sqhstl[79] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[79] = (         int  )sizeof(long);
   sqlstm.sqindv[79] = (         void  *)0;
   sqlstm.sqinds[79] = (         int  )0;
   sqlstm.sqharm[79] = (unsigned int  )0;
   sqlstm.sqharc[79] = (unsigned int   *)0;
   sqlstm.sqadto[79] = (unsigned short )0;
   sqlstm.sqtdso[79] = (unsigned short )0;
   sqlstm.sqhstv[80] = (         void  *)HOME_CURNCY_CAMEL_FEE;
   sqlstm.sqhstl[80] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[80] = (         int  )sizeof(double);
   sqlstm.sqindv[80] = (         void  *)0;
   sqlstm.sqinds[80] = (         int  )0;
   sqlstm.sqharm[80] = (unsigned int  )0;
   sqlstm.sqharc[80] = (unsigned int   *)0;
   sqlstm.sqadto[80] = (unsigned short )0;
   sqlstm.sqtdso[80] = (unsigned short )0;
   sqlstm.sqhstv[81] = (         void  *)HOME_CURNCY_CAMEL_TAX;
   sqlstm.sqhstl[81] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[81] = (         int  )sizeof(double);
   sqlstm.sqindv[81] = (         void  *)0;
   sqlstm.sqinds[81] = (         int  )0;
   sqlstm.sqharm[81] = (unsigned int  )0;
   sqlstm.sqharc[81] = (unsigned int   *)0;
   sqlstm.sqadto[81] = (unsigned short )0;
   sqlstm.sqtdso[81] = (unsigned short )0;
   sqlstm.sqhstv[82] = (         void  *)HOME_CURNCY_CAMEL_DISCOUNT;
   sqlstm.sqhstl[82] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[82] = (         int  )sizeof(double);
   sqlstm.sqindv[82] = (         void  *)0;
   sqlstm.sqinds[82] = (         int  )0;
   sqlstm.sqharm[82] = (unsigned int  )0;
   sqlstm.sqharc[82] = (unsigned int   *)0;
   sqlstm.sqadto[82] = (unsigned short )0;
   sqlstm.sqtdso[82] = (unsigned short )0;
   sqlstm.sqhstv[83] = (         void  *)HOME_CURNCY_CHARGE;
   sqlstm.sqhstl[83] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[83] = (         int  )sizeof(double);
   sqlstm.sqindv[83] = (         void  *)0;
   sqlstm.sqinds[83] = (         int  )0;
   sqlstm.sqharm[83] = (unsigned int  )0;
   sqlstm.sqharc[83] = (unsigned int   *)0;
   sqlstm.sqadto[83] = (unsigned short )0;
   sqlstm.sqtdso[83] = (unsigned short )0;
   sqlstm.sqhstv[84] = (         void  *)HOME_CURNCY_TAX;
   sqlstm.sqhstl[84] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[84] = (         int  )sizeof(double);
   sqlstm.sqindv[84] = (         void  *)0;
   sqlstm.sqinds[84] = (         int  )0;
   sqlstm.sqharm[84] = (unsigned int  )0;
   sqlstm.sqharc[84] = (unsigned int   *)0;
   sqlstm.sqadto[84] = (unsigned short )0;
   sqlstm.sqtdso[84] = (unsigned short )0;
   sqlstm.sqhstv[85] = (         void  *)HOME_CURNCY_DISCOUNT;
   sqlstm.sqhstl[85] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[85] = (         int  )sizeof(double);
   sqlstm.sqindv[85] = (         void  *)0;
   sqlstm.sqinds[85] = (         int  )0;
   sqlstm.sqharm[85] = (unsigned int  )0;
   sqlstm.sqharc[85] = (unsigned int   *)0;
   sqlstm.sqadto[85] = (unsigned short )0;
   sqlstm.sqtdso[85] = (unsigned short )0;
   sqlstm.sqhstv[86] = (         void  *)HOME_CURNCY_SURCHARGE;
   sqlstm.sqhstl[86] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[86] = (         int  )sizeof(double);
   sqlstm.sqindv[86] = (         void  *)0;
   sqlstm.sqinds[86] = (         int  )0;
   sqlstm.sqharm[86] = (unsigned int  )0;
   sqlstm.sqharc[86] = (unsigned int   *)0;
   sqlstm.sqadto[86] = (unsigned short )0;
   sqlstm.sqtdso[86] = (unsigned short )0;
   sqlstm.sqhstv[87] = (         void  *)HOME_CURNCY_CHARGE_WITH_TAX;
   sqlstm.sqhstl[87] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[87] = (         int  )sizeof(double);
   sqlstm.sqindv[87] = (         void  *)0;
   sqlstm.sqinds[87] = (         int  )0;
   sqlstm.sqharm[87] = (unsigned int  )0;
   sqlstm.sqharc[87] = (unsigned int   *)0;
   sqlstm.sqadto[87] = (unsigned short )0;
   sqlstm.sqtdso[87] = (unsigned short )0;
   sqlstm.sqhstv[88] = (         void  *)HOME_CURNCY_TOTAL_CHARGE;
   sqlstm.sqhstl[88] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[88] = (         int  )sizeof(double);
   sqlstm.sqindv[88] = (         void  *)0;
   sqlstm.sqinds[88] = (         int  )0;
   sqlstm.sqharm[88] = (unsigned int  )0;
   sqlstm.sqharc[88] = (unsigned int   *)0;
   sqlstm.sqadto[88] = (unsigned short )0;
   sqlstm.sqtdso[88] = (unsigned short )0;
   sqlstm.sqhstv[89] = (         void  *)HOME_EXCHANGE_RATE;
   sqlstm.sqhstl[89] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[89] = (         int  )sizeof(double);
   sqlstm.sqindv[89] = (         void  *)0;
   sqlstm.sqinds[89] = (         int  )0;
   sqlstm.sqharm[89] = (unsigned int  )0;
   sqlstm.sqharc[89] = (unsigned int   *)0;
   sqlstm.sqadto[89] = (unsigned short )0;
   sqlstm.sqtdso[89] = (unsigned short )0;
   sqlstm.sqhstv[90] = (         void  *)TAP_EXCHANGE_RATE_CODE;
   sqlstm.sqhstl[90] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[90] = (         int  )sizeof(long);
   sqlstm.sqindv[90] = (         void  *)0;
   sqlstm.sqinds[90] = (         int  )0;
   sqlstm.sqharm[90] = (unsigned int  )0;
   sqlstm.sqharc[90] = (unsigned int   *)0;
   sqlstm.sqadto[90] = (unsigned short )0;
   sqlstm.sqtdso[90] = (unsigned short )0;
   sqlstm.sqhstv[91] = (         void  *)TAP_EXCHANGE_RATE;
   sqlstm.sqhstl[91] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[91] = (         int  )sizeof(double);
   sqlstm.sqindv[91] = (         void  *)0;
   sqlstm.sqinds[91] = (         int  )0;
   sqlstm.sqharm[91] = (unsigned int  )0;
   sqlstm.sqharc[91] = (unsigned int   *)0;
   sqlstm.sqadto[91] = (unsigned short )0;
   sqlstm.sqtdso[91] = (unsigned short )0;
   sqlstm.sqhstv[92] = (         void  *)TAP_EXCHANGE_RATE_DECIMAL;
   sqlstm.sqhstl[92] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[92] = (         int  )sizeof(long);
   sqlstm.sqindv[92] = (         void  *)0;
   sqlstm.sqinds[92] = (         int  )0;
   sqlstm.sqharm[92] = (unsigned int  )0;
   sqlstm.sqharc[92] = (unsigned int   *)0;
   sqlstm.sqadto[92] = (unsigned short )0;
   sqlstm.sqtdso[92] = (unsigned short )0;
   sqlstm.sqhstv[93] = (         void  *)TAP_TAX_TYPE_RATE;
   sqlstm.sqhstl[93] = (unsigned int  )601;
   sqlstm.sqhsts[93] = (         int  )601;
   sqlstm.sqindv[93] = (         void  *)0;
   sqlstm.sqinds[93] = (         int  )0;
   sqlstm.sqharm[93] = (unsigned int  )0;
   sqlstm.sqharc[93] = (unsigned int   *)0;
   sqlstm.sqadto[93] = (unsigned short )0;
   sqlstm.sqtdso[93] = (unsigned short )0;
   sqlstm.sqhstv[94] = (         void  *)NETWORK_ACCESS_IDENTIFER;
   sqlstm.sqhstl[94] = (unsigned int  )31;
   sqlstm.sqhsts[94] = (         int  )31;
   sqlstm.sqindv[94] = (         void  *)0;
   sqlstm.sqinds[94] = (         int  )0;
   sqlstm.sqharm[94] = (unsigned int  )0;
   sqlstm.sqharc[94] = (unsigned int   *)0;
   sqlstm.sqadto[94] = (unsigned short )0;
   sqlstm.sqtdso[94] = (unsigned short )0;
   sqlstm.sqhstv[95] = (         void  *)PDP_ADDRESS;
   sqlstm.sqhstl[95] = (unsigned int  )46;
   sqlstm.sqhsts[95] = (         int  )46;
   sqlstm.sqindv[95] = (         void  *)0;
   sqlstm.sqinds[95] = (         int  )0;
   sqlstm.sqharm[95] = (unsigned int  )0;
   sqlstm.sqharc[95] = (unsigned int   *)0;
   sqlstm.sqadto[95] = (unsigned short )0;
   sqlstm.sqtdso[95] = (unsigned short )0;
   sqlstm.sqhstv[96] = (         void  *)APN_NI;
   sqlstm.sqhstl[96] = (unsigned int  )66;
   sqlstm.sqhsts[96] = (         int  )66;
   sqlstm.sqindv[96] = (         void  *)0;
   sqlstm.sqinds[96] = (         int  )0;
   sqlstm.sqharm[96] = (unsigned int  )0;
   sqlstm.sqharc[96] = (unsigned int   *)0;
   sqlstm.sqadto[96] = (unsigned short )0;
   sqlstm.sqtdso[96] = (unsigned short )0;
   sqlstm.sqhstv[97] = (         void  *)APN_OI;
   sqlstm.sqhstl[97] = (unsigned int  )66;
   sqlstm.sqhsts[97] = (         int  )66;
   sqlstm.sqindv[97] = (         void  *)0;
   sqlstm.sqinds[97] = (         int  )0;
   sqlstm.sqharm[97] = (unsigned int  )0;
   sqlstm.sqharc[97] = (unsigned int   *)0;
   sqlstm.sqadto[97] = (unsigned short )0;
   sqlstm.sqtdso[97] = (unsigned short )0;
   sqlstm.sqhstv[98] = (         void  *)CAUSE_FOR_TERMINATION;
   sqlstm.sqhstl[98] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[98] = (         int  )sizeof(long);
   sqlstm.sqindv[98] = (         void  *)0;
   sqlstm.sqinds[98] = (         int  )0;
   sqlstm.sqharm[98] = (unsigned int  )0;
   sqlstm.sqharc[98] = (unsigned int   *)0;
   sqlstm.sqadto[98] = (unsigned short )0;
   sqlstm.sqtdso[98] = (unsigned short )0;
   sqlstm.sqhstv[99] = (         void  *)PARTIAL_TYPE_INDICATOR;
   sqlstm.sqhstl[99] = (unsigned int  )2;
   sqlstm.sqhsts[99] = (         int  )2;
   sqlstm.sqindv[99] = (         void  *)0;
   sqlstm.sqinds[99] = (         int  )0;
   sqlstm.sqharm[99] = (unsigned int  )0;
   sqlstm.sqharc[99] = (unsigned int   *)0;
   sqlstm.sqadto[99] = (unsigned short )0;
   sqlstm.sqtdso[99] = (unsigned short )0;
   sqlstm.sqhstv[100] = (         void  *)CHARGING_ID;
   sqlstm.sqhstl[100] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[100] = (         int  )sizeof(double);
   sqlstm.sqindv[100] = (         void  *)0;
   sqlstm.sqinds[100] = (         int  )0;
   sqlstm.sqharm[100] = (unsigned int  )0;
   sqlstm.sqharc[100] = (unsigned int   *)0;
   sqlstm.sqadto[100] = (unsigned short )0;
   sqlstm.sqtdso[100] = (unsigned short )0;
   sqlstm.sqhstv[101] = (         void  *)SERVING_LOCATION_DESC;
   sqlstm.sqhstl[101] = (unsigned int  )46;
   sqlstm.sqhsts[101] = (         int  )46;
   sqlstm.sqindv[101] = (         void  *)0;
   sqlstm.sqinds[101] = (         int  )0;
   sqlstm.sqharm[101] = (unsigned int  )0;
   sqlstm.sqharc[101] = (unsigned int   *)0;
   sqlstm.sqadto[101] = (unsigned short )0;
   sqlstm.sqtdso[101] = (unsigned short )0;
   sqlstm.sqhstv[102] = (         void  *)DATA_VOLUME_INCOMING;
   sqlstm.sqhstl[102] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[102] = (         int  )sizeof(double);
   sqlstm.sqindv[102] = (         void  *)0;
   sqlstm.sqinds[102] = (         int  )0;
   sqlstm.sqharm[102] = (unsigned int  )0;
   sqlstm.sqharc[102] = (unsigned int   *)0;
   sqlstm.sqadto[102] = (unsigned short )0;
   sqlstm.sqtdso[102] = (unsigned short )0;
   sqlstm.sqhstv[103] = (         void  *)DATA_VOLUME_OUTGOING;
   sqlstm.sqhstl[103] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[103] = (         int  )sizeof(double);
   sqlstm.sqindv[103] = (         void  *)0;
   sqlstm.sqinds[103] = (         int  )0;
   sqlstm.sqharm[103] = (unsigned int  )0;
   sqlstm.sqharc[103] = (unsigned int   *)0;
   sqlstm.sqadto[103] = (unsigned short )0;
   sqlstm.sqtdso[103] = (unsigned short )0;
   sqlstm.sqhstv[104] = (         void  *)SGSN_RECORDING_ENTITY_CODE1;
   sqlstm.sqhstl[104] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[104] = (         int  )sizeof(long);
   sqlstm.sqindv[104] = (         void  *)0;
   sqlstm.sqinds[104] = (         int  )0;
   sqlstm.sqharm[104] = (unsigned int  )0;
   sqlstm.sqharc[104] = (unsigned int   *)0;
   sqlstm.sqadto[104] = (unsigned short )0;
   sqlstm.sqtdso[104] = (unsigned short )0;
   sqlstm.sqhstv[105] = (         void  *)SGSN_RECORDING_ENTITY_ID1;
   sqlstm.sqhstl[105] = (unsigned int  )46;
   sqlstm.sqhsts[105] = (         int  )46;
   sqlstm.sqindv[105] = (         void  *)0;
   sqlstm.sqinds[105] = (         int  )0;
   sqlstm.sqharm[105] = (unsigned int  )0;
   sqlstm.sqharc[105] = (unsigned int   *)0;
   sqlstm.sqadto[105] = (unsigned short )0;
   sqlstm.sqtdso[105] = (unsigned short )0;
   sqlstm.sqhstv[106] = (         void  *)SGSN_RECORDING_ENTITY_CODE2;
   sqlstm.sqhstl[106] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[106] = (         int  )sizeof(long);
   sqlstm.sqindv[106] = (         void  *)0;
   sqlstm.sqinds[106] = (         int  )0;
   sqlstm.sqharm[106] = (unsigned int  )0;
   sqlstm.sqharc[106] = (unsigned int   *)0;
   sqlstm.sqadto[106] = (unsigned short )0;
   sqlstm.sqtdso[106] = (unsigned short )0;
   sqlstm.sqhstv[107] = (         void  *)SGSN_RECORDING_ENTITY_ID2;
   sqlstm.sqhstl[107] = (unsigned int  )46;
   sqlstm.sqhsts[107] = (         int  )46;
   sqlstm.sqindv[107] = (         void  *)0;
   sqlstm.sqinds[107] = (         int  )0;
   sqlstm.sqharm[107] = (unsigned int  )0;
   sqlstm.sqharc[107] = (unsigned int   *)0;
   sqlstm.sqadto[107] = (unsigned short )0;
   sqlstm.sqtdso[107] = (unsigned short )0;
   sqlstm.sqhstv[108] = (         void  *)SGSN_RECORDING_ENTITY_CODE3;
   sqlstm.sqhstl[108] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[108] = (         int  )sizeof(long);
   sqlstm.sqindv[108] = (         void  *)0;
   sqlstm.sqinds[108] = (         int  )0;
   sqlstm.sqharm[108] = (unsigned int  )0;
   sqlstm.sqharc[108] = (unsigned int   *)0;
   sqlstm.sqadto[108] = (unsigned short )0;
   sqlstm.sqtdso[108] = (unsigned short )0;
   sqlstm.sqhstv[109] = (         void  *)SGSN_RECORDING_ENTITY_ID3;
   sqlstm.sqhstl[109] = (unsigned int  )46;
   sqlstm.sqhsts[109] = (         int  )46;
   sqlstm.sqindv[109] = (         void  *)0;
   sqlstm.sqinds[109] = (         int  )0;
   sqlstm.sqharm[109] = (unsigned int  )0;
   sqlstm.sqharc[109] = (unsigned int   *)0;
   sqlstm.sqadto[109] = (unsigned short )0;
   sqlstm.sqtdso[109] = (unsigned short )0;
   sqlstm.sqhstv[110] = (         void  *)CAMEL_APN_NI;
   sqlstm.sqhstl[110] = (unsigned int  )66;
   sqlstm.sqhsts[110] = (         int  )66;
   sqlstm.sqindv[110] = (         void  *)0;
   sqlstm.sqinds[110] = (         int  )0;
   sqlstm.sqharm[110] = (unsigned int  )0;
   sqlstm.sqharc[110] = (unsigned int   *)0;
   sqlstm.sqadto[110] = (unsigned short )0;
   sqlstm.sqtdso[110] = (unsigned short )0;
   sqlstm.sqhstv[111] = (         void  *)CAMEL_APN_OI;
   sqlstm.sqhstl[111] = (unsigned int  )66;
   sqlstm.sqhsts[111] = (         int  )66;
   sqlstm.sqindv[111] = (         void  *)0;
   sqlstm.sqinds[111] = (         int  )0;
   sqlstm.sqharm[111] = (unsigned int  )0;
   sqlstm.sqharc[111] = (unsigned int   *)0;
   sqlstm.sqadto[111] = (unsigned short )0;
   sqlstm.sqtdso[111] = (unsigned short )0;
   sqlstm.sqhstv[112] = (         void  *)A_USERID;
   sqlstm.sqhstl[112] = (unsigned int  )66;
   sqlstm.sqhsts[112] = (         int  )66;
   sqlstm.sqindv[112] = (         void  *)0;
   sqlstm.sqinds[112] = (         int  )0;
   sqlstm.sqharm[112] = (unsigned int  )0;
   sqlstm.sqharc[112] = (unsigned int   *)0;
   sqlstm.sqadto[112] = (unsigned short )0;
   sqlstm.sqtdso[112] = (unsigned short )0;
   sqlstm.sqhstv[113] = (         void  *)B_USERID;
   sqlstm.sqhstl[113] = (unsigned int  )66;
   sqlstm.sqhsts[113] = (         int  )66;
   sqlstm.sqindv[113] = (         void  *)0;
   sqlstm.sqinds[113] = (         int  )0;
   sqlstm.sqharm[113] = (unsigned int  )0;
   sqlstm.sqharc[113] = (unsigned int   *)0;
   sqlstm.sqadto[113] = (unsigned short )0;
   sqlstm.sqtdso[113] = (unsigned short )0;
   sqlstm.sqhstv[114] = (         void  *)EVENT_REFERENCE;
   sqlstm.sqhstl[114] = (unsigned int  )31;
   sqlstm.sqhsts[114] = (         int  )31;
   sqlstm.sqindv[114] = (         void  *)0;
   sqlstm.sqinds[114] = (         int  )0;
   sqlstm.sqharm[114] = (unsigned int  )0;
   sqlstm.sqharc[114] = (unsigned int   *)0;
   sqlstm.sqadto[114] = (unsigned short )0;
   sqlstm.sqtdso[114] = (unsigned short )0;
   sqlstm.sqhstv[115] = (         void  *)NETWORK_ELEMENT_TYPE1;
   sqlstm.sqhstl[115] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[115] = (         int  )sizeof(int);
   sqlstm.sqindv[115] = (         void  *)0;
   sqlstm.sqinds[115] = (         int  )0;
   sqlstm.sqharm[115] = (unsigned int  )0;
   sqlstm.sqharc[115] = (unsigned int   *)0;
   sqlstm.sqadto[115] = (unsigned short )0;
   sqlstm.sqtdso[115] = (unsigned short )0;
   sqlstm.sqhstv[116] = (         void  *)NETWORK_ELEMENT_TYPE2;
   sqlstm.sqhstl[116] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[116] = (         int  )sizeof(int);
   sqlstm.sqindv[116] = (         void  *)0;
   sqlstm.sqinds[116] = (         int  )0;
   sqlstm.sqharm[116] = (unsigned int  )0;
   sqlstm.sqharc[116] = (unsigned int   *)0;
   sqlstm.sqadto[116] = (unsigned short )0;
   sqlstm.sqtdso[116] = (unsigned short )0;
   sqlstm.sqhstv[117] = (         void  *)NETWORK_ELEMENT_ID1;
   sqlstm.sqhstl[117] = (unsigned int  )46;
   sqlstm.sqhsts[117] = (         int  )46;
   sqlstm.sqindv[117] = (         void  *)0;
   sqlstm.sqinds[117] = (         int  )0;
   sqlstm.sqharm[117] = (unsigned int  )0;
   sqlstm.sqharc[117] = (unsigned int   *)0;
   sqlstm.sqadto[117] = (unsigned short )0;
   sqlstm.sqtdso[117] = (unsigned short )0;
   sqlstm.sqhstv[118] = (         void  *)NETWORK_ELEMENT_ID2;
   sqlstm.sqhstl[118] = (unsigned int  )46;
   sqlstm.sqhsts[118] = (         int  )46;
   sqlstm.sqindv[118] = (         void  *)0;
   sqlstm.sqinds[118] = (         int  )0;
   sqlstm.sqharm[118] = (unsigned int  )0;
   sqlstm.sqharc[118] = (unsigned int   *)0;
   sqlstm.sqadto[118] = (unsigned short )0;
   sqlstm.sqtdso[118] = (unsigned short )0;
   sqlstm.sqhstv[119] = (         void  *)SGSN_RECORDING_ENTITY_TYPE1;
   sqlstm.sqhstl[119] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[119] = (         int  )sizeof(int);
   sqlstm.sqindv[119] = (         void  *)0;
   sqlstm.sqinds[119] = (         int  )0;
   sqlstm.sqharm[119] = (unsigned int  )0;
   sqlstm.sqharc[119] = (unsigned int   *)0;
   sqlstm.sqadto[119] = (unsigned short )0;
   sqlstm.sqtdso[119] = (unsigned short )0;
   sqlstm.sqhstv[120] = (         void  *)SGSN_RECORDING_ENTITY_TYPE2;
   sqlstm.sqhstl[120] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[120] = (         int  )sizeof(int);
   sqlstm.sqindv[120] = (         void  *)0;
   sqlstm.sqinds[120] = (         int  )0;
   sqlstm.sqharm[120] = (unsigned int  )0;
   sqlstm.sqharc[120] = (unsigned int   *)0;
   sqlstm.sqadto[120] = (unsigned short )0;
   sqlstm.sqtdso[120] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}




   if(ERRCODE!=0)
   {
      TRACEENTRY(1,"%s","Error Inserting Bulk Records into PM_TAP_CDRS table");
      TRACEENTRY(1,"%s -%d- -%d-","ERROR : sqlca.sqlcode sqlca.sqlerrd :",ERRCODE,sqlca.sqlerrd[2]);
      TRACEENTRY(1,"TotalCDRS in the file : -%d-",TotalCDRS);
      CheckBulkInsertError(sqlca.sqlerrd[2]); 

      stErrors.ERROR_CODE = sqlca.sqlcode;
      strcpy(stErrors.ERROR_DESC,"Error Inserting Bulk CDRS into PM_TAP_CDRS table");
      return -1;
   }

   return 0;
}



int BulkInsertIOTCDR(int TotalIOTCDRS)
{
   int i=0;

  
   /* Insert the Final CDR to the PM_TAP_CDRS table */
   /* EXEC SQL FOR :TotalIOTCDRS
   INSERT INTO PM_TMP_TAP_CDRS
   (
          FILE_TRANSFER_DIRECTION        ,
          HPLMN_CODE                     ,
          VPLMN_CODE                     ,
          PARTNER_CODE                   ,
          FILE_TYPE_INDICATOR            ,
          FILE_SEQUENCE_NUMBER           ,
          CALL_SEQUENCE                  ,
          CALL_TYPE                      ,
          SERVICE_CODE                   ,
          IMSI                           ,
          MSISDN                         ,
          CALLED_CALLING_NUMBER          ,
          DIALLED_DIGITS                 ,
          CALL_DATE                      ,
          CALL_DURATION                  ,
          BASIC_SERVICE_TYPE             ,
          BASIC_SERVICE_CODE             ,
          CHARGED_ITEM                   ,
          CHARGEABLE_UNITS               ,
          CHARGED_UNITS                  ,
          CHARGE                         ,
          TAX_INFORMATION_COUNT          ,
          TAX_CODE                       ,
          TAX_VALUE                      ,
          TAXABLE_AMOUNT                 ,
          DISCOUNT_INFORMATION_COUNT     ,
          DISCOUNT_CODE                  ,
          DISCOUNT                       ,
          DISCOUNTABLE_AMT               ,
          TAP_EXCHANGE_RATE              ,
          TAP_EXCHANGE_RATE_DECIMAL      ,
          CALL_TYPE_LEVEL1               ,
          DATA_VOLUME_INCOMING           ,
          DATA_VOLUME_OUTGOING           , 
          HOME_CURNCY_CHARGE             ,
          HOME_CURNCY_TAX                ,
          HOME_CURNCY_DISCOUNT           ,
          CAMEL_INVOCATION_FEE           ,
          CDR_ERROR_FLAG                 ,
          CHARGE_CONTEXT                 ,     
          TAX_CONTEXT                    ,
          DISCOUNT_CONTEXT               ,
          ERROR_NODE                     ,
	  A_USERID                       ,
	  B_USERID                       ,
	  EVENT_REFERENCE                ,
	  IOT_DATE                       ,
	  IOT_CALCULATION        
   )
   VALUES
   (
         :IOT_FILE_TRANSFER_DIRECTION     ,
         :IOT_HPLMN_CODE                  ,
         :IOT_VPLMN_CODE                  ,
         :IOT_PARTNER_CODE                ,
         :IOT_FILE_TYPE_INDICATOR         ,
         :IOT_FILE_SEQUENCE_NUMBER        ,
         :IOT_CALL_SEQUENCE               ,
         :IOT_CALL_TYPE                   ,
         :IOT_SERVICE_CODE                ,
         :IOT_IMSI                        ,
         :IOT_MSISDN                      ,
         :IOT_CALLED_CALLING_NUMBER       ,
         :IOT_DIALLED_DIGITS              ,
         to_date(:IOT_CALL_DATE,'YYYYMMDDHH24MISS'),
         :IOT_CALL_DURATION               ,
         :IOT_BASIC_SERVICE_TYPE          ,
         :IOT_BASIC_SERVICE_CODE          ,
         :IOT_CHARGED_ITEM                ,
         :IOT_CHARGEABLE_UNITS            ,
         :IOT_CHARGED_UNITS               ,
         :IOT_CHARGE                      ,
         :IOT_TAX_INFORMATION_COUNT       ,
         :IOT_TAX_CODE                    ,
         :IOT_TAX_VALUE                   ,
         :IOT_TAXABLE_AMOUNT              ,
         :IOT_DISCOUNT_INFORMATION_COUNT  ,
         :IOT_DISCOUNT_CODE               ,
         :IOT_DISCOUNT                    ,
         :IOT_DISCOUNTABLE_AMT            ,
         :IOT_TAP_EXCHANGE_RATE           ,
         :IOT_TAP_EXCHANGE_RATE_DECIMAL   ,
         :IOT_CALL_TYPE_LEVEL1            ,
         :IOT_DATA_VOLUME_INCOMING        ,
         :IOT_DATA_VOLUME_OUTGOING        ,
         :IOT_HOME_CURNCY_CHARGE          ,
         :IOT_HOME_CURNCY_TAX             ,
         :IOT_HOME_CURNCY_DISCOUNT        ,
         :IOT_CAMEL_INVOCATION_FEE        ,
         :CDR_ERROR_FLAG                  ,
         :IOT_CHARGE_CONTEXT              ,
         :IOT_TAX_CONTEXT                 , 
         :IOT_DISCOUNT_CONTEXT            ,
         :IOT_ERROR_NODE                  ,
	 :IOT_A_USERID                    ,
	 :IOT_B_USERID                    , 
	 :IOT_EVENT_REFERENCE             ,
	to_date(:IOT_DATE,'YYYYMMDDHH24MISS'),
	 :IOT_CALCULATION
   ); */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 121;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlbuft((void **)0, 
     "insert into PM_TMP_TAP_CDRS (FILE_TRANSFER_DIRECTION,HPLMN_CODE,VPLMN_\
CODE,PARTNER_CODE,FILE_TYPE_INDICATOR,FILE_SEQUENCE_NUMBER,CALL_SEQUENCE,CAL\
L_TYPE,SERVICE_CODE,IMSI,MSISDN,CALLED_CALLING_NUMBER,DIALLED_DIGITS,CALL_DA\
TE,CALL_DURATION,BASIC_SERVICE_TYPE,BASIC_SERVICE_CODE,CHARGED_ITEM,CHARGEAB\
LE_UNITS,CHARGED_UNITS,CHARGE,TAX_INFORMATION_COUNT,TAX_CODE,TAX_VALUE,TAXAB\
LE_AMOUNT,DISCOUNT_INFORMATION_COUNT,DISCOUNT_CODE,DISCOUNT,DISCOUNTABLE_AMT\
,TAP_EXCHANGE_RATE,TAP_EXCHANGE_RATE_DECIMAL,CALL_TYPE_LEVEL1,DATA_VOLUME_IN\
COMING,DATA_VOLUME_OUTGOING,HOME_CURNCY_CHARGE,HOME_CURNCY_TAX,HOME_CURNCY_D\
ISCOUNT,CAMEL_INVOCATION_FEE,CDR_ERROR_FLAG,CHARGE_CONTEXT,TAX_CONTEXT,DISCO\
UNT_CONTEXT,ERROR_NODE,A_USERID,B_USERID,EVENT_REFERENCE,IOT_DATE,IOT_CALCUL\
ATION) values (:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b11,:b12,:b13,to_da\
te(:b14,'YYYYMMDDHH24MISS'),:b15,:b16,:b17,:b18,:b19,:b20,:b21,:b22,:b23,:b2\
4,:b25,:b26,:b27,:b28,:b29,:b30,:b31,:b32,:b33,:b34,:b35,:b36,:b37,:b38,:b39\
,:b40,:b41,:b42,:b43,:b44,:b45,:b46,to_dat");
   sqlstm.stmt = "e(:b47,'YYYYMMDDHH24MISS'),:b48)";
   sqlstm.iters = (unsigned int  )TotalIOTCDRS;
   sqlstm.offset = (unsigned int  )2992;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)IOT_FILE_TRANSFER_DIRECTION;
   sqlstm.sqhstl[0] = (unsigned int  )2;
   sqlstm.sqhsts[0] = (         int  )2;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqharc[0] = (unsigned int   *)0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)IOT_HPLMN_CODE;
   sqlstm.sqhstl[1] = (unsigned int  )6;
   sqlstm.sqhsts[1] = (         int  )6;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqharc[1] = (unsigned int   *)0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)IOT_VPLMN_CODE;
   sqlstm.sqhstl[2] = (unsigned int  )6;
   sqlstm.sqhsts[2] = (         int  )6;
   sqlstm.sqindv[2] = (         void  *)0;
   sqlstm.sqinds[2] = (         int  )0;
   sqlstm.sqharm[2] = (unsigned int  )0;
   sqlstm.sqharc[2] = (unsigned int   *)0;
   sqlstm.sqadto[2] = (unsigned short )0;
   sqlstm.sqtdso[2] = (unsigned short )0;
   sqlstm.sqhstv[3] = (         void  *)IOT_PARTNER_CODE;
   sqlstm.sqhstl[3] = (unsigned int  )4;
   sqlstm.sqhsts[3] = (         int  )4;
   sqlstm.sqindv[3] = (         void  *)0;
   sqlstm.sqinds[3] = (         int  )0;
   sqlstm.sqharm[3] = (unsigned int  )0;
   sqlstm.sqharc[3] = (unsigned int   *)0;
   sqlstm.sqadto[3] = (unsigned short )0;
   sqlstm.sqtdso[3] = (unsigned short )0;
   sqlstm.sqhstv[4] = (         void  *)IOT_FILE_TYPE_INDICATOR;
   sqlstm.sqhstl[4] = (unsigned int  )2;
   sqlstm.sqhsts[4] = (         int  )2;
   sqlstm.sqindv[4] = (         void  *)0;
   sqlstm.sqinds[4] = (         int  )0;
   sqlstm.sqharm[4] = (unsigned int  )0;
   sqlstm.sqharc[4] = (unsigned int   *)0;
   sqlstm.sqadto[4] = (unsigned short )0;
   sqlstm.sqtdso[4] = (unsigned short )0;
   sqlstm.sqhstv[5] = (         void  *)IOT_FILE_SEQUENCE_NUMBER;
   sqlstm.sqhstl[5] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[5] = (         int  )sizeof(long);
   sqlstm.sqindv[5] = (         void  *)0;
   sqlstm.sqinds[5] = (         int  )0;
   sqlstm.sqharm[5] = (unsigned int  )0;
   sqlstm.sqharc[5] = (unsigned int   *)0;
   sqlstm.sqadto[5] = (unsigned short )0;
   sqlstm.sqtdso[5] = (unsigned short )0;
   sqlstm.sqhstv[6] = (         void  *)IOT_CALL_SEQUENCE;
   sqlstm.sqhstl[6] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[6] = (         int  )sizeof(long);
   sqlstm.sqindv[6] = (         void  *)0;
   sqlstm.sqinds[6] = (         int  )0;
   sqlstm.sqharm[6] = (unsigned int  )0;
   sqlstm.sqharc[6] = (unsigned int   *)0;
   sqlstm.sqadto[6] = (unsigned short )0;
   sqlstm.sqtdso[6] = (unsigned short )0;
   sqlstm.sqhstv[7] = (         void  *)IOT_CALL_TYPE;
   sqlstm.sqhstl[7] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[7] = (         int  )sizeof(long);
   sqlstm.sqindv[7] = (         void  *)0;
   sqlstm.sqinds[7] = (         int  )0;
   sqlstm.sqharm[7] = (unsigned int  )0;
   sqlstm.sqharc[7] = (unsigned int   *)0;
   sqlstm.sqadto[7] = (unsigned short )0;
   sqlstm.sqtdso[7] = (unsigned short )0;
   sqlstm.sqhstv[8] = (         void  *)IOT_SERVICE_CODE;
   sqlstm.sqhstl[8] = (unsigned int  )4;
   sqlstm.sqhsts[8] = (         int  )4;
   sqlstm.sqindv[8] = (         void  *)0;
   sqlstm.sqinds[8] = (         int  )0;
   sqlstm.sqharm[8] = (unsigned int  )0;
   sqlstm.sqharc[8] = (unsigned int   *)0;
   sqlstm.sqadto[8] = (unsigned short )0;
   sqlstm.sqtdso[8] = (unsigned short )0;
   sqlstm.sqhstv[9] = (         void  *)IOT_IMSI;
   sqlstm.sqhstl[9] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[9] = (         int  )sizeof(double);
   sqlstm.sqindv[9] = (         void  *)0;
   sqlstm.sqinds[9] = (         int  )0;
   sqlstm.sqharm[9] = (unsigned int  )0;
   sqlstm.sqharc[9] = (unsigned int   *)0;
   sqlstm.sqadto[9] = (unsigned short )0;
   sqlstm.sqtdso[9] = (unsigned short )0;
   sqlstm.sqhstv[10] = (         void  *)IOT_MSISDN;
   sqlstm.sqhstl[10] = (unsigned int  )26;
   sqlstm.sqhsts[10] = (         int  )26;
   sqlstm.sqindv[10] = (         void  *)0;
   sqlstm.sqinds[10] = (         int  )0;
   sqlstm.sqharm[10] = (unsigned int  )0;
   sqlstm.sqharc[10] = (unsigned int   *)0;
   sqlstm.sqadto[10] = (unsigned short )0;
   sqlstm.sqtdso[10] = (unsigned short )0;
   sqlstm.sqhstv[11] = (         void  *)IOT_CALLED_CALLING_NUMBER;
   sqlstm.sqhstl[11] = (unsigned int  )87;
   sqlstm.sqhsts[11] = (         int  )87;
   sqlstm.sqindv[11] = (         void  *)0;
   sqlstm.sqinds[11] = (         int  )0;
   sqlstm.sqharm[11] = (unsigned int  )0;
   sqlstm.sqharc[11] = (unsigned int   *)0;
   sqlstm.sqadto[11] = (unsigned short )0;
   sqlstm.sqtdso[11] = (unsigned short )0;
   sqlstm.sqhstv[12] = (         void  *)IOT_DIALLED_DIGITS;
   sqlstm.sqhstl[12] = (unsigned int  )87;
   sqlstm.sqhsts[12] = (         int  )87;
   sqlstm.sqindv[12] = (         void  *)0;
   sqlstm.sqinds[12] = (         int  )0;
   sqlstm.sqharm[12] = (unsigned int  )0;
   sqlstm.sqharc[12] = (unsigned int   *)0;
   sqlstm.sqadto[12] = (unsigned short )0;
   sqlstm.sqtdso[12] = (unsigned short )0;
   sqlstm.sqhstv[13] = (         void  *)IOT_CALL_DATE;
   sqlstm.sqhstl[13] = (unsigned int  )15;
   sqlstm.sqhsts[13] = (         int  )15;
   sqlstm.sqindv[13] = (         void  *)0;
   sqlstm.sqinds[13] = (         int  )0;
   sqlstm.sqharm[13] = (unsigned int  )0;
   sqlstm.sqharc[13] = (unsigned int   *)0;
   sqlstm.sqadto[13] = (unsigned short )0;
   sqlstm.sqtdso[13] = (unsigned short )0;
   sqlstm.sqhstv[14] = (         void  *)IOT_CALL_DURATION;
   sqlstm.sqhstl[14] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[14] = (         int  )sizeof(double);
   sqlstm.sqindv[14] = (         void  *)0;
   sqlstm.sqinds[14] = (         int  )0;
   sqlstm.sqharm[14] = (unsigned int  )0;
   sqlstm.sqharc[14] = (unsigned int   *)0;
   sqlstm.sqadto[14] = (unsigned short )0;
   sqlstm.sqtdso[14] = (unsigned short )0;
   sqlstm.sqhstv[15] = (         void  *)IOT_BASIC_SERVICE_TYPE;
   sqlstm.sqhstl[15] = (unsigned int  )2;
   sqlstm.sqhsts[15] = (         int  )2;
   sqlstm.sqindv[15] = (         void  *)0;
   sqlstm.sqinds[15] = (         int  )0;
   sqlstm.sqharm[15] = (unsigned int  )0;
   sqlstm.sqharc[15] = (unsigned int   *)0;
   sqlstm.sqadto[15] = (unsigned short )0;
   sqlstm.sqtdso[15] = (unsigned short )0;
   sqlstm.sqhstv[16] = (         void  *)IOT_BASIC_SERVICE_CODE;
   sqlstm.sqhstl[16] = (unsigned int  )4;
   sqlstm.sqhsts[16] = (         int  )4;
   sqlstm.sqindv[16] = (         void  *)0;
   sqlstm.sqinds[16] = (         int  )0;
   sqlstm.sqharm[16] = (unsigned int  )0;
   sqlstm.sqharc[16] = (unsigned int   *)0;
   sqlstm.sqadto[16] = (unsigned short )0;
   sqlstm.sqtdso[16] = (unsigned short )0;
   sqlstm.sqhstv[17] = (         void  *)IOT_CHARGED_ITEM;
   sqlstm.sqhstl[17] = (unsigned int  )4;
   sqlstm.sqhsts[17] = (         int  )4;
   sqlstm.sqindv[17] = (         void  *)0;
   sqlstm.sqinds[17] = (         int  )0;
   sqlstm.sqharm[17] = (unsigned int  )0;
   sqlstm.sqharc[17] = (unsigned int   *)0;
   sqlstm.sqadto[17] = (unsigned short )0;
   sqlstm.sqtdso[17] = (unsigned short )0;
   sqlstm.sqhstv[18] = (         void  *)IOT_CHARGEABLE_UNITS;
   sqlstm.sqhstl[18] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[18] = (         int  )sizeof(double);
   sqlstm.sqindv[18] = (         void  *)0;
   sqlstm.sqinds[18] = (         int  )0;
   sqlstm.sqharm[18] = (unsigned int  )0;
   sqlstm.sqharc[18] = (unsigned int   *)0;
   sqlstm.sqadto[18] = (unsigned short )0;
   sqlstm.sqtdso[18] = (unsigned short )0;
   sqlstm.sqhstv[19] = (         void  *)IOT_CHARGED_UNITS;
   sqlstm.sqhstl[19] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[19] = (         int  )sizeof(double);
   sqlstm.sqindv[19] = (         void  *)0;
   sqlstm.sqinds[19] = (         int  )0;
   sqlstm.sqharm[19] = (unsigned int  )0;
   sqlstm.sqharc[19] = (unsigned int   *)0;
   sqlstm.sqadto[19] = (unsigned short )0;
   sqlstm.sqtdso[19] = (unsigned short )0;
   sqlstm.sqhstv[20] = (         void  *)IOT_CHARGE;
   sqlstm.sqhstl[20] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[20] = (         int  )sizeof(double);
   sqlstm.sqindv[20] = (         void  *)0;
   sqlstm.sqinds[20] = (         int  )0;
   sqlstm.sqharm[20] = (unsigned int  )0;
   sqlstm.sqharc[20] = (unsigned int   *)0;
   sqlstm.sqadto[20] = (unsigned short )0;
   sqlstm.sqtdso[20] = (unsigned short )0;
   sqlstm.sqhstv[21] = (         void  *)IOT_TAX_INFORMATION_COUNT;
   sqlstm.sqhstl[21] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[21] = (         int  )sizeof(long);
   sqlstm.sqindv[21] = (         void  *)0;
   sqlstm.sqinds[21] = (         int  )0;
   sqlstm.sqharm[21] = (unsigned int  )0;
   sqlstm.sqharc[21] = (unsigned int   *)0;
   sqlstm.sqadto[21] = (unsigned short )0;
   sqlstm.sqtdso[21] = (unsigned short )0;
   sqlstm.sqhstv[22] = (         void  *)IOT_TAX_CODE;
   sqlstm.sqhstl[22] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[22] = (         int  )sizeof(long);
   sqlstm.sqindv[22] = (         void  *)0;
   sqlstm.sqinds[22] = (         int  )0;
   sqlstm.sqharm[22] = (unsigned int  )0;
   sqlstm.sqharc[22] = (unsigned int   *)0;
   sqlstm.sqadto[22] = (unsigned short )0;
   sqlstm.sqtdso[22] = (unsigned short )0;
   sqlstm.sqhstv[23] = (         void  *)IOT_TAX_VALUE;
   sqlstm.sqhstl[23] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[23] = (         int  )sizeof(double);
   sqlstm.sqindv[23] = (         void  *)0;
   sqlstm.sqinds[23] = (         int  )0;
   sqlstm.sqharm[23] = (unsigned int  )0;
   sqlstm.sqharc[23] = (unsigned int   *)0;
   sqlstm.sqadto[23] = (unsigned short )0;
   sqlstm.sqtdso[23] = (unsigned short )0;
   sqlstm.sqhstv[24] = (         void  *)IOT_TAXABLE_AMOUNT;
   sqlstm.sqhstl[24] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[24] = (         int  )sizeof(double);
   sqlstm.sqindv[24] = (         void  *)0;
   sqlstm.sqinds[24] = (         int  )0;
   sqlstm.sqharm[24] = (unsigned int  )0;
   sqlstm.sqharc[24] = (unsigned int   *)0;
   sqlstm.sqadto[24] = (unsigned short )0;
   sqlstm.sqtdso[24] = (unsigned short )0;
   sqlstm.sqhstv[25] = (         void  *)IOT_DISCOUNT_INFORMATION_COUNT;
   sqlstm.sqhstl[25] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[25] = (         int  )sizeof(long);
   sqlstm.sqindv[25] = (         void  *)0;
   sqlstm.sqinds[25] = (         int  )0;
   sqlstm.sqharm[25] = (unsigned int  )0;
   sqlstm.sqharc[25] = (unsigned int   *)0;
   sqlstm.sqadto[25] = (unsigned short )0;
   sqlstm.sqtdso[25] = (unsigned short )0;
   sqlstm.sqhstv[26] = (         void  *)IOT_DISCOUNT_CODE;
   sqlstm.sqhstl[26] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[26] = (         int  )sizeof(long);
   sqlstm.sqindv[26] = (         void  *)0;
   sqlstm.sqinds[26] = (         int  )0;
   sqlstm.sqharm[26] = (unsigned int  )0;
   sqlstm.sqharc[26] = (unsigned int   *)0;
   sqlstm.sqadto[26] = (unsigned short )0;
   sqlstm.sqtdso[26] = (unsigned short )0;
   sqlstm.sqhstv[27] = (         void  *)IOT_DISCOUNT;
   sqlstm.sqhstl[27] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[27] = (         int  )sizeof(double);
   sqlstm.sqindv[27] = (         void  *)0;
   sqlstm.sqinds[27] = (         int  )0;
   sqlstm.sqharm[27] = (unsigned int  )0;
   sqlstm.sqharc[27] = (unsigned int   *)0;
   sqlstm.sqadto[27] = (unsigned short )0;
   sqlstm.sqtdso[27] = (unsigned short )0;
   sqlstm.sqhstv[28] = (         void  *)IOT_DISCOUNTABLE_AMT;
   sqlstm.sqhstl[28] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[28] = (         int  )sizeof(double);
   sqlstm.sqindv[28] = (         void  *)0;
   sqlstm.sqinds[28] = (         int  )0;
   sqlstm.sqharm[28] = (unsigned int  )0;
   sqlstm.sqharc[28] = (unsigned int   *)0;
   sqlstm.sqadto[28] = (unsigned short )0;
   sqlstm.sqtdso[28] = (unsigned short )0;
   sqlstm.sqhstv[29] = (         void  *)IOT_TAP_EXCHANGE_RATE;
   sqlstm.sqhstl[29] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[29] = (         int  )sizeof(double);
   sqlstm.sqindv[29] = (         void  *)0;
   sqlstm.sqinds[29] = (         int  )0;
   sqlstm.sqharm[29] = (unsigned int  )0;
   sqlstm.sqharc[29] = (unsigned int   *)0;
   sqlstm.sqadto[29] = (unsigned short )0;
   sqlstm.sqtdso[29] = (unsigned short )0;
   sqlstm.sqhstv[30] = (         void  *)IOT_TAP_EXCHANGE_RATE_DECIMAL;
   sqlstm.sqhstl[30] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[30] = (         int  )sizeof(long);
   sqlstm.sqindv[30] = (         void  *)0;
   sqlstm.sqinds[30] = (         int  )0;
   sqlstm.sqharm[30] = (unsigned int  )0;
   sqlstm.sqharc[30] = (unsigned int   *)0;
   sqlstm.sqadto[30] = (unsigned short )0;
   sqlstm.sqtdso[30] = (unsigned short )0;
   sqlstm.sqhstv[31] = (         void  *)IOT_CALL_TYPE_LEVEL1;
   sqlstm.sqhstl[31] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[31] = (         int  )sizeof(long);
   sqlstm.sqindv[31] = (         void  *)0;
   sqlstm.sqinds[31] = (         int  )0;
   sqlstm.sqharm[31] = (unsigned int  )0;
   sqlstm.sqharc[31] = (unsigned int   *)0;
   sqlstm.sqadto[31] = (unsigned short )0;
   sqlstm.sqtdso[31] = (unsigned short )0;
   sqlstm.sqhstv[32] = (         void  *)IOT_DATA_VOLUME_INCOMING;
   sqlstm.sqhstl[32] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[32] = (         int  )sizeof(double);
   sqlstm.sqindv[32] = (         void  *)0;
   sqlstm.sqinds[32] = (         int  )0;
   sqlstm.sqharm[32] = (unsigned int  )0;
   sqlstm.sqharc[32] = (unsigned int   *)0;
   sqlstm.sqadto[32] = (unsigned short )0;
   sqlstm.sqtdso[32] = (unsigned short )0;
   sqlstm.sqhstv[33] = (         void  *)IOT_DATA_VOLUME_OUTGOING;
   sqlstm.sqhstl[33] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[33] = (         int  )sizeof(double);
   sqlstm.sqindv[33] = (         void  *)0;
   sqlstm.sqinds[33] = (         int  )0;
   sqlstm.sqharm[33] = (unsigned int  )0;
   sqlstm.sqharc[33] = (unsigned int   *)0;
   sqlstm.sqadto[33] = (unsigned short )0;
   sqlstm.sqtdso[33] = (unsigned short )0;
   sqlstm.sqhstv[34] = (         void  *)IOT_HOME_CURNCY_CHARGE;
   sqlstm.sqhstl[34] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[34] = (         int  )sizeof(double);
   sqlstm.sqindv[34] = (         void  *)0;
   sqlstm.sqinds[34] = (         int  )0;
   sqlstm.sqharm[34] = (unsigned int  )0;
   sqlstm.sqharc[34] = (unsigned int   *)0;
   sqlstm.sqadto[34] = (unsigned short )0;
   sqlstm.sqtdso[34] = (unsigned short )0;
   sqlstm.sqhstv[35] = (         void  *)IOT_HOME_CURNCY_TAX;
   sqlstm.sqhstl[35] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[35] = (         int  )sizeof(double);
   sqlstm.sqindv[35] = (         void  *)0;
   sqlstm.sqinds[35] = (         int  )0;
   sqlstm.sqharm[35] = (unsigned int  )0;
   sqlstm.sqharc[35] = (unsigned int   *)0;
   sqlstm.sqadto[35] = (unsigned short )0;
   sqlstm.sqtdso[35] = (unsigned short )0;
   sqlstm.sqhstv[36] = (         void  *)IOT_HOME_CURNCY_DISCOUNT;
   sqlstm.sqhstl[36] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[36] = (         int  )sizeof(double);
   sqlstm.sqindv[36] = (         void  *)0;
   sqlstm.sqinds[36] = (         int  )0;
   sqlstm.sqharm[36] = (unsigned int  )0;
   sqlstm.sqharc[36] = (unsigned int   *)0;
   sqlstm.sqadto[36] = (unsigned short )0;
   sqlstm.sqtdso[36] = (unsigned short )0;
   sqlstm.sqhstv[37] = (         void  *)IOT_CAMEL_INVOCATION_FEE;
   sqlstm.sqhstl[37] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[37] = (         int  )sizeof(double);
   sqlstm.sqindv[37] = (         void  *)0;
   sqlstm.sqinds[37] = (         int  )0;
   sqlstm.sqharm[37] = (unsigned int  )0;
   sqlstm.sqharc[37] = (unsigned int   *)0;
   sqlstm.sqadto[37] = (unsigned short )0;
   sqlstm.sqtdso[37] = (unsigned short )0;
   sqlstm.sqhstv[38] = (         void  *)CDR_ERROR_FLAG;
   sqlstm.sqhstl[38] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[38] = (         int  )sizeof(int);
   sqlstm.sqindv[38] = (         void  *)0;
   sqlstm.sqinds[38] = (         int  )0;
   sqlstm.sqharm[38] = (unsigned int  )0;
   sqlstm.sqharc[38] = (unsigned int   *)0;
   sqlstm.sqadto[38] = (unsigned short )0;
   sqlstm.sqtdso[38] = (unsigned short )0;
   sqlstm.sqhstv[39] = (         void  *)IOT_CHARGE_CONTEXT;
   sqlstm.sqhstl[39] = (unsigned int  )80;
   sqlstm.sqhsts[39] = (         int  )80;
   sqlstm.sqindv[39] = (         void  *)0;
   sqlstm.sqinds[39] = (         int  )0;
   sqlstm.sqharm[39] = (unsigned int  )0;
   sqlstm.sqharc[39] = (unsigned int   *)0;
   sqlstm.sqadto[39] = (unsigned short )0;
   sqlstm.sqtdso[39] = (unsigned short )0;
   sqlstm.sqhstv[40] = (         void  *)IOT_TAX_CONTEXT;
   sqlstm.sqhstl[40] = (unsigned int  )80;
   sqlstm.sqhsts[40] = (         int  )80;
   sqlstm.sqindv[40] = (         void  *)0;
   sqlstm.sqinds[40] = (         int  )0;
   sqlstm.sqharm[40] = (unsigned int  )0;
   sqlstm.sqharc[40] = (unsigned int   *)0;
   sqlstm.sqadto[40] = (unsigned short )0;
   sqlstm.sqtdso[40] = (unsigned short )0;
   sqlstm.sqhstv[41] = (         void  *)IOT_DISCOUNT_CONTEXT;
   sqlstm.sqhstl[41] = (unsigned int  )80;
   sqlstm.sqhsts[41] = (         int  )80;
   sqlstm.sqindv[41] = (         void  *)0;
   sqlstm.sqinds[41] = (         int  )0;
   sqlstm.sqharm[41] = (unsigned int  )0;
   sqlstm.sqharc[41] = (unsigned int   *)0;
   sqlstm.sqadto[41] = (unsigned short )0;
   sqlstm.sqtdso[41] = (unsigned short )0;
   sqlstm.sqhstv[42] = (         void  *)IOT_ERROR_NODE;
   sqlstm.sqhstl[42] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[42] = (         int  )sizeof(int);
   sqlstm.sqindv[42] = (         void  *)0;
   sqlstm.sqinds[42] = (         int  )0;
   sqlstm.sqharm[42] = (unsigned int  )0;
   sqlstm.sqharc[42] = (unsigned int   *)0;
   sqlstm.sqadto[42] = (unsigned short )0;
   sqlstm.sqtdso[42] = (unsigned short )0;
   sqlstm.sqhstv[43] = (         void  *)IOT_A_USERID;
   sqlstm.sqhstl[43] = (unsigned int  )66;
   sqlstm.sqhsts[43] = (         int  )66;
   sqlstm.sqindv[43] = (         void  *)0;
   sqlstm.sqinds[43] = (         int  )0;
   sqlstm.sqharm[43] = (unsigned int  )0;
   sqlstm.sqharc[43] = (unsigned int   *)0;
   sqlstm.sqadto[43] = (unsigned short )0;
   sqlstm.sqtdso[43] = (unsigned short )0;
   sqlstm.sqhstv[44] = (         void  *)IOT_B_USERID;
   sqlstm.sqhstl[44] = (unsigned int  )66;
   sqlstm.sqhsts[44] = (         int  )66;
   sqlstm.sqindv[44] = (         void  *)0;
   sqlstm.sqinds[44] = (         int  )0;
   sqlstm.sqharm[44] = (unsigned int  )0;
   sqlstm.sqharc[44] = (unsigned int   *)0;
   sqlstm.sqadto[44] = (unsigned short )0;
   sqlstm.sqtdso[44] = (unsigned short )0;
   sqlstm.sqhstv[45] = (         void  *)IOT_EVENT_REFERENCE;
   sqlstm.sqhstl[45] = (unsigned int  )31;
   sqlstm.sqhsts[45] = (         int  )31;
   sqlstm.sqindv[45] = (         void  *)0;
   sqlstm.sqinds[45] = (         int  )0;
   sqlstm.sqharm[45] = (unsigned int  )0;
   sqlstm.sqharc[45] = (unsigned int   *)0;
   sqlstm.sqadto[45] = (unsigned short )0;
   sqlstm.sqtdso[45] = (unsigned short )0;
   sqlstm.sqhstv[46] = (         void  *)IOT_DATE;
   sqlstm.sqhstl[46] = (unsigned int  )15;
   sqlstm.sqhsts[46] = (         int  )15;
   sqlstm.sqindv[46] = (         void  *)0;
   sqlstm.sqinds[46] = (         int  )0;
   sqlstm.sqharm[46] = (unsigned int  )0;
   sqlstm.sqharc[46] = (unsigned int   *)0;
   sqlstm.sqadto[46] = (unsigned short )0;
   sqlstm.sqtdso[46] = (unsigned short )0;
   sqlstm.sqhstv[47] = (         void  *)IOT_CALCULATION;
   sqlstm.sqhstl[47] = (unsigned int  )100;
   sqlstm.sqhsts[47] = (         int  )100;
   sqlstm.sqindv[47] = (         void  *)0;
   sqlstm.sqinds[47] = (         int  )0;
   sqlstm.sqharm[47] = (unsigned int  )0;
   sqlstm.sqharc[47] = (unsigned int   *)0;
   sqlstm.sqadto[47] = (unsigned short )0;
   sqlstm.sqtdso[47] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



  
   if(ERRCODE!=0)
   {
      TRACEENTRY(1,"%s","Error Inserting Bulk Records into PM_TMP_TAP_CDRS table");
      TRACEENTRY(1,"%s -%d- -%d-","ERROR : sqlca.sqlcode sqlca.sqlerrd :",ERRCODE,sqlca.sqlerrd[2]);
      TRACEENTRY(1,"TotalCDRS in the file : -%d-",TotalIOTCDRS);
      CheckBulkInsertIOTError(sqlca.sqlerrd[2]);

      stErrors.ERROR_CODE = sqlca.sqlcode;
      strcpy(stErrors.ERROR_DESC,"Error Inserting Bulk CDRS into PM_TMP_TAP_CDRS table");
      return -1;
   }

   return 0;
}

int BulkInsertErrorDetails(int TotalCDRS)
{

   int i = 0 ;


   /* Insert the Final CDR to the PM_RAP_DETAILS table */
   /* EXEC SQL FOR :TotalCDRS
   INSERT INTO PM_RAP_DETAILS
   (
       FILE_TRANSFER_DIRECTION         ,
       HPLMN_CODE                      ,  
       VPLMN_CODE                      ,  
       PARTNER_CODE                    ,  
       FILE_TYPE_INDICATOR             ,
       FILE_SEQUENCE_NUMBER            ,
       RAP_SEQUENCE_NUMBER             ,
       CALL_SEQUENCE                   ,
       ERROR_SEQUENCE                  ,
       CALLS_TYPE_INDICATOR            ,
       CALL_TYPE                       ,
       SERVICE_CODE                    ,
       IMSI                            ,
       MSISDN                          ,
       CALLED_CALLING_NUMBER           ,
       DIALLED_DIGITS                  ,
       CLIR_INDICATOR                  ,
       DESTINATION_NETWORK             ,
       CALL_DATE                       ,
       UTC_OFFSET_CODE                 , 
       UTC_OFFSET                      ,
       CALL_DURATION                   , 
       SIM_TOOLKIT_INDICATOR           ,
       RECORDING_ENTITY_CODE           ,
       RECORDING_ENTITY_TYPE           ,
       RECORDING_ENTITY_ID             ,
       CALL_REFERENCE                  ,
       CELLID                          ,
       SERVING_NETWORK                 ,
       IMEI                            ,
       BASIC_SERVICE_TYPE              ,
       BASIC_SERVICE_CODE              ,
       TRANSPARENCY_INDICATOR          ,
       FNUR                            ,
       USER_PROTOCOL_INDICATOR         ,
       GUARANTEED_BIT_RATE             ,
       MAXIMUM_BIT_RATE                ,
       HSCSD_INDICATOR                 ,
       SUPPLIMENTARY_SERVICE_CODE      ,
       SUPPLIMENTARY_ACTION_CODE       ,
       SUPPLIMENTARY_SERVICE_PARAMS    ,
       THIRD_PARTY_NUMBER              ,
       THIRD_PARTY_CLIR_INDICATOR      ,
       CAMEL_USED_FLAG                 ,
       CAMEL_SERVICE_LEVEL             ,
       CAMEL_SERVICE_KEY               ,
       CAMEL_DEFAULT_CALL_HANDLING     ,
       CAMEL_EXCHANGE_RATE_CODE        ,
       CAMEL_INVOCATION_FEE            ,
       CAMEL_DISCOUNT_CODE             ,
       CAMEL_DISCOUNT                  ,
       CAMEL_DISCOUNTABLE_AMT          ,
       CAMEL_TAX_INFORMATION_COUNT     ,
       CAMEL_TAX_CODE                  ,
       CAMEL_TAX_VALUE                 ,
       CAMEL_TAXABLE_AMOUNT            ,
       CAMEL_DESTINATION_NUMBER        ,
       CALL_TYPE_LEVEL1                ,
       CALL_TYPE_LEVEL2                ,
       CALL_TYPE_LEVEL3                ,
       CHARGE_INFORMATION_COUNT        ,
       CHARGED_ITEM                    ,
       CHARGE_TYPE                     ,
       CHARGEABLE_UNITS                ,
       CHARGED_UNITS                   ,
       CHARGE                          ,
       TAX_INFORMATION_COUNT           ,
       TAX_CODE                        ,
       TAX_VALUE                       ,
       TAXABLE_AMOUNT                  ,
       DISCOUNT_INFORMATION_COUNT      ,
       DISCOUNT_CODE                   ,
       DISCOUNT                        ,
       DISCOUNTABLE_AMT                ,
       TAP_EXCHANGE_RATE_CODE          ,
       TAP_EXCHANGE_RATE               ,
       TAP_EXCHANGE_RATE_DECIMAL       ,
       TAP_TAX_TYPE_RATE               ,
       NETWORK_ACCESS_IDENTIFER        ,
       PDP_ADDRESS                     ,
       APN_NI                          ,
       APN_OI                          ,
       CAUSE_FOR_TERMINATION           ,
       PARTIAL_TYPE_INDICATOR          ,
       CHARGING_ID                     ,                                 
       DATA_VOLUME_INCOMING            ,
       DATA_VOLUME_OUTGOING            ,
       SGSN_RECORDING_ENTITY_CODE1     ,
       SGSN_RECORDING_ENTITY_ID1       ,
       SGSN_RECORDING_ENTITY_CODE2     ,
       SGSN_RECORDING_ENTITY_ID2       ,
       SGSN_RECORDING_ENTITY_CODE3     ,
       SGSN_RECORDING_ENTITY_ID3       ,
       CAMEL_APN_NI                    ,
       CAMEL_APN_OI                    , 
       FILE_CREATION_TIME              ,
       FILE_TRANSFER_TIME              ,
       FILE_AVAILABLE_TIME             ,
       CHARGING_TIME_STAMP             ,
       LOCAL_CURRENCY_CODE             ,
       TAP_CURRENCY_CODE               ,
       TAP_DECIMAL_PLACES              ,
       TARIFF_ID                       ,
       IOT_CHARGE                      ,
       IOT_TAX                         ,
       IOT_DISCOUNT                    ,
       ERROR_CODE                      ,
       ERROR_TYPE                      ,
       ERROR_CONTEXT_DETAILS           ,
       APPLICATION_TAG                 ,
       CONTEXT_NAME                    ,
       DATA_TYPE_INDICATOR             ,
       ERROR_FIELD_NAME                ,
       ERROR_MESSAGE                   ,
       ERROR_VALUE                     ,
       ERROR_NODE                      ,
       RAP_STATUS                      ,
       A_USERID                        ,
       B_USERID                        ,
       EVENT_REFERENCE                 ,
       NETWORK_ELEMENT_TYPE1           ,
       NETWORK_ELEMENT_TYPE2           ,
       NETWORK_ELEMENT_ID1             ,
       NETWORK_ELEMENT_ID2             ,
       SGSN_RECORDING_ENTITY_TYPE1     ,
       SGSN_RECORDING_ENTITY_TYPE2     ,
       IOT_DATE                        ,
       IOT_CALCULATION                 ,
       EXP_EXCHANGE_RATE
       )
   VALUES
   (
       :ER_FILE_TRANSFER_DIRECTION       ,
       :ER_HPLMN_CODE                    ,
       :ER_VPLMN_CODE                    ,
       :ER_PARTNER_CODE                  ,
       :ER_FILE_TYPE_INDICATOR           ,
       :ER_FILE_SEQUENCE_NUMBER          ,
       :ER_RAP_SEQUENCE_NUMBER           ,
       :ER_CALL_SEQUENCE                 ,
       :ER_ERROR_SEQUENCE                ,
       :ER_CALLS_TYPE_INDICATOR          ,
       :ER_CALL_TYPE                     ,
       :ER_SERVICE_CODE                  ,
       :ER_IMSI                          ,
       :ER_MSISDN                        ,
       :ER_CALLED_CALLING_NUMBER         ,
       :ER_DIALLED_DIGITS                ,
       :ER_CLIR_INDICATOR                ,
       :ER_DESTINATION_NETWORK           ,
       :ER_CALL_DATE                     ,
       :ER_UTC_OFFSET_CODE               , 
       :ER_UTC_OFFSET                    ,
       :ER_CALL_DURATION                 ,
       :ER_SIM_TOOLKIT_INDICATOR         ,
       :ER_RECORDING_ENTITY_CODE         ,
       :ER_RECORDING_ENTITY_TYPE         ,
       :ER_RECORDING_ENTITY_ID           ,
       :ER_CALL_REFERENCE                ,
       :ER_CELLID                        ,
       :ER_SERVING_NETWORK               ,
       :ER_IMEI                          ,
       :ER_BASIC_SERVICE_TYPE            ,
       :ER_BASIC_SERVICE_CODE            ,
       :ER_TRANSPARENCY_INDICATOR        ,
       :ER_FNUR                          ,
       :ER_USER_PROTOCOL_INDICATOR       ,
       :ER_GUARANTEED_BIT_RATE           ,
       :ER_MAXIMUM_BIT_RATE              ,
       :ER_HSCSD_INDICATOR               ,
       :ER_SUPPLIMENTARY_SERVICE_CODE    ,
       :ER_SUPPLIMENTARY_ACTION_CODE     ,
       :ER_SUPPLIMENTARY_SERVICE_PARAMS  ,
       :ER_THIRD_PARTY_NUMBER            ,
       :ER_THIRD_PARTY_CLIR_INDICATOR    ,
       :ER_CAMEL_USED_FLAG               ,
       :ER_CAMEL_SERVICE_LEVEL           ,
       :ER_CAMEL_SERVICE_KEY             ,
       :ER_CAMEL_DEFAULT_CALL_HANDLING   ,
       :ER_CAMEL_EXCHANGE_RATE_CODE      ,
       :ER_CAMEL_INVOCATION_FEE          ,
       :ER_CAMEL_DISCOUNT_CODE           ,
       :ER_CAMEL_DISCOUNT                ,
       :ER_CAMEL_DISCOUNTABLE_AMT        ,
       :ER_CAMEL_TAX_INFORMATION_COUNT   ,
       :ER_CAMEL_TAX_CODE                ,
       :ER_CAMEL_TAX_VALUE               ,
       :ER_CAMEL_TAXABLE_AMOUNT          ,
       :ER_CAMEL_DESTINATION_NUMBER      ,
       :ER_CALL_TYPE_LEVEL1              ,
       :ER_CALL_TYPE_LEVEL2              ,
       :ER_CALL_TYPE_LEVEL3              ,
       :ER_CHARGE_INFORMATION_COUNT      ,
       :ER_CHARGED_ITEM                  ,
       :ER_CHARGE_TYPE                   ,
       :ER_CHARGEABLE_UNITS              ,
       :ER_CHARGED_UNITS                 ,
       :ER_CHARGE                        ,
       :ER_TAX_INFORMATION_COUNT         ,
       :ER_TAX_CODE                      ,
       :ER_TAX_VALUE                     ,
       :ER_TAXABLE_AMOUNT                ,
       :ER_DISCOUNT_INFORMATION_COUNT    ,
       :ER_DISCOUNT_CODE                 ,
       :ER_DISCOUNT                      ,
       :ER_DISCOUNTABLE_AMT              ,
       :ER_TAP_EXCHANGE_RATE_CODE        ,
       :ER_TAP_EXCHANGE_RATE             ,
       :ER_TAP_EXCHANGE_RATE_DECIMAL     ,
       :ER_TAP_TAX_TYPE_RATE             ,
       :ER_NETWORK_ACCESS_IDENTIFER      ,
       :ER_PDP_ADDRESS                   ,
       :ER_APN_NI                        ,
       :ER_APN_OI                        ,
       :ER_CAUSE_FOR_TERMINATION         ,
       :ER_PARTIAL_TYPE_INDICATOR        ,
       :ER_CHARGING_ID                   ,
       :ER_DATA_VOLUME_INCOMING          ,
       :ER_DATA_VOLUME_OUTGOING          ,
       :ER_SGSN_RECORDING_ENTITY_CODE1   ,
       :ER_SGSN_RECORDING_ENTITY_ID1     ,
       :ER_SGSN_RECORDING_ENTITY_CODE2   ,
       :ER_SGSN_RECORDING_ENTITY_ID2     ,
       :ER_SGSN_RECORDING_ENTITY_CODE3   ,
       :ER_SGSN_RECORDING_ENTITY_ID3     ,
       :ER_CAMEL_APN_NI                  ,
       :ER_CAMEL_APN_OI                  , 
       :ER_FILE_CREATION_TIME            ,
       :ER_FILE_TRANSFER_TIME            ,
       :ER_FILE_AVAILABLE_TIME           ,
       :ER_CHARGING_TIME_STAMP           ,
       :ER_LOCAL_CURRENCY_CODE           ,
       :ER_TAP_CURRENCY_CODE             ,
       :ER_TAP_DECIMAL_PLACES            ,
       :ER_TARIFF_ID                     ,
       :ER_IOT_CHARGE                    ,
       :ER_IOT_TAX                       ,
       :ER_IOT_DISCOUNT                  ,
       :ER_ERROR_CODE                    ,
       :ER_ERROR_TYPE                    ,
       :ER_ERROR_CONTEXT_DETAILS         ,
       :ER_APPLICATION_TAG               ,
       :ER_CONTEXT_NAME                  ,
       :ER_DATA_TYPE_INDICATOR           ,
       :ER_ERROR_FIELD_NAME              ,
       :ER_ERROR_MESSAGE                 , 
       :ER_ERROR_VALUE                   ,
       :ER_ERROR_NODE                    ,
       :ER_RAP_STATUS                    ,
       :ER_A_USERID                      ,
       :ER_B_USERID                      ,
       :ER_EVENT_REFERENCE               ,
       :ER_NETWORK_ELEMENT_TYPE1         ,
       :ER_NETWORK_ELEMENT_TYPE2         ,
       :ER_NETWORK_ELEMENT_ID1           ,
       :ER_NETWORK_ELEMENT_ID2           ,
       :ER_SGSN_RECORDING_ENTITY_TYPE1    ,
       :ER_SGSN_RECORDING_ENTITY_TYPE2    ,
       :ER_IOT_DATE                       ,
       :ER_IOT_CALCULATION                ,
       :ER_EXP_EXCHANGE_RATE 
   ); */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 129;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlbuft((void **)0, 
     "insert into PM_RAP_DETAILS (FILE_TRANSFER_DIRECTION,HPLMN_CODE,VPLMN_C\
ODE,PARTNER_CODE,FILE_TYPE_INDICATOR,FILE_SEQUENCE_NUMBER,RAP_SEQUENCE_NUMBE\
R,CALL_SEQUENCE,ERROR_SEQUENCE,CALLS_TYPE_INDICATOR,CALL_TYPE,SERVICE_CODE,I\
MSI,MSISDN,CALLED_CALLING_NUMBER,DIALLED_DIGITS,CLIR_INDICATOR,DESTINATION_N\
ETWORK,CALL_DATE,UTC_OFFSET_CODE,UTC_OFFSET,CALL_DURATION,SIM_TOOLKIT_INDICA\
TOR,RECORDING_ENTITY_CODE,RECORDING_ENTITY_TYPE,RECORDING_ENTITY_ID,CALL_REF\
ERENCE,CELLID,SERVING_NETWORK,IMEI,BASIC_SERVICE_TYPE,BASIC_SERVICE_CODE,TRA\
NSPARENCY_INDICATOR,FNUR,USER_PROTOCOL_INDICATOR,GUARANTEED_BIT_RATE,MAXIMUM\
_BIT_RATE,HSCSD_INDICATOR,SUPPLIMENTARY_SERVICE_CODE,SUPPLIMENTARY_ACTION_CO\
DE,SUPPLIMENTARY_SERVICE_PARAMS,THIRD_PARTY_NUMBER,THIRD_PARTY_CLIR_INDICATO\
R,CAMEL_USED_FLAG,CAMEL_SERVICE_LEVEL,CAMEL_SERVICE_KEY,CAMEL_DEFAULT_CALL_H\
ANDLING,CAMEL_EXCHANGE_RATE_CODE,CAMEL_INVOCATION_FEE,CAMEL_DISCOUNT_CODE,CA\
MEL_DISCOUNT,CAMEL_DISCOUNTABLE_AMT,CAMEL_TAX_INFORMATION_COUNT,CAMEL_TAX_CO\
DE,CAMEL_TAX_VALUE,CAMEL_TAXABLE_AMOUNT,CA");
   sqlbuft((void **)0, 
     "MEL_DESTINATION_NUMBER,CALL_TYPE_LEVEL1,CALL_TYPE_LEVEL2,CALL_TYPE_LEV\
EL3,CHARGE_INFORMATION_COUNT,CHARGED_ITEM,CHARGE_TYPE,CHARGEABLE_UNITS,CHARG\
ED_UNITS,CHARGE,TAX_INFORMATION_COUNT,TAX_CODE,TAX_VALUE,TAXABLE_AMOUNT,DISC\
OUNT_INFORMATION_COUNT,DISCOUNT_CODE,DISCOUNT,DISCOUNTABLE_AMT,TAP_EXCHANGE_\
RATE_CODE,TAP_EXCHANGE_RATE,TAP_EXCHANGE_RATE_DECIMAL,TAP_TAX_TYPE_RATE,NETW\
ORK_ACCESS_IDENTIFER,PDP_ADDRESS,APN_NI,APN_OI,CAUSE_FOR_TERMINATION,PARTIAL\
_TYPE_INDICATOR,CHARGING_ID,DATA_VOLUME_INCOMING,DATA_VOLUME_OUTGOING,SGSN_R\
ECORDING_ENTITY_CODE1,SGSN_RECORDING_ENTITY_ID1,SGSN_RECORDING_ENTITY_CODE2,\
SGSN_RECORDING_ENTITY_ID2,SGSN_RECORDING_ENTITY_CODE3,SGSN_RECORDING_ENTITY_\
ID3,CAMEL_APN_NI,CAMEL_APN_OI,FILE_CREATION_TIME,FILE_TRANSFER_TIME,FILE_AVA\
ILABLE_TIME,CHARGING_TIME_STAMP,LOCAL_CURRENCY_CODE,TAP_CURRENCY_CODE,TAP_DE\
CIMAL_PLACES,TARIFF_ID,IOT_CHARGE,IOT_TAX,IOT_DISCOUNT,ERROR_CODE,ERROR_TYPE\
,ERROR_CONTEXT_DETAILS,APPLICATION_TAG,CONTEXT_NAME,DATA_TYPE_INDICATOR,ERRO\
R_FIELD_NAME,ERROR_MESSAGE,ERROR_VALUE,ERR");
   sqlstm.stmt = "OR_NODE,RAP_STATUS,A_USERID,B_USERID,EVENT_REFERENCE,NETWO\
RK_ELEMENT_TYPE1,NETWORK_ELEMENT_TYPE2,NETWORK_ELEMENT_ID1,NETWORK_ELEMENT_ID2\
,SGSN_RECORDING_ENTITY_TYPE1,SGSN_RECORDING_ENTITY_TYPE2,IOT_DATE,IOT_CALCULAT\
ION,EXP_EXCHANGE_RATE) values (:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b11,:\
b12,:b13,:b14,:b15,:b16,:b17,:b18,:b19,:b20,:b21,:b22,:b23,:b24,:b25,:b26,:b27\
,:b28,:b29,:b30,:b31,:b32,:b33,:b34,:b35,:b36,:b37,:b38,:b39,:b40,:b41,:b42,:b\
43,:b44,:b45,:b46,:b47,:b48,:b49,:b50,:b51,:b52,:b53,:b54,:b55,:b56,:b57,:b58,\
:b59,:b60,:b61,:b62,:b63,:b64,:b65,:b66,:b67,:b68,:b69,:b70,:b71,:b72,:b73,:b7\
4,:b75,:b76,:b77,:b78,:b79,:b80,:b81,:b82,:b83,:b84,:b85,:b86,:b87,:b88,:b89,:\
b90,:b91,:b92,:b93,:b94,:b95,:b96,:b97,:b98,:b99,:b100,:b101,:b102,:b103,:b104\
,:b105,:b106,:b107,:b108,:b109,:b110,:b111,:b112,:b113,:b114,:b115,:b116,:b117\
,:b118,:b119,:b120,:b121,:b122,:b123,:b124,:b125,:b126,:b127,:b128,:b129)";
   sqlstm.iters = (unsigned int  )TotalCDRS;
   sqlstm.offset = (unsigned int  )3199;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)ER_FILE_TRANSFER_DIRECTION;
   sqlstm.sqhstl[0] = (unsigned int  )2;
   sqlstm.sqhsts[0] = (         int  )2;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqharc[0] = (unsigned int   *)0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)ER_HPLMN_CODE;
   sqlstm.sqhstl[1] = (unsigned int  )6;
   sqlstm.sqhsts[1] = (         int  )6;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqharc[1] = (unsigned int   *)0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)ER_VPLMN_CODE;
   sqlstm.sqhstl[2] = (unsigned int  )6;
   sqlstm.sqhsts[2] = (         int  )6;
   sqlstm.sqindv[2] = (         void  *)0;
   sqlstm.sqinds[2] = (         int  )0;
   sqlstm.sqharm[2] = (unsigned int  )0;
   sqlstm.sqharc[2] = (unsigned int   *)0;
   sqlstm.sqadto[2] = (unsigned short )0;
   sqlstm.sqtdso[2] = (unsigned short )0;
   sqlstm.sqhstv[3] = (         void  *)ER_PARTNER_CODE;
   sqlstm.sqhstl[3] = (unsigned int  )4;
   sqlstm.sqhsts[3] = (         int  )4;
   sqlstm.sqindv[3] = (         void  *)0;
   sqlstm.sqinds[3] = (         int  )0;
   sqlstm.sqharm[3] = (unsigned int  )0;
   sqlstm.sqharc[3] = (unsigned int   *)0;
   sqlstm.sqadto[3] = (unsigned short )0;
   sqlstm.sqtdso[3] = (unsigned short )0;
   sqlstm.sqhstv[4] = (         void  *)ER_FILE_TYPE_INDICATOR;
   sqlstm.sqhstl[4] = (unsigned int  )2;
   sqlstm.sqhsts[4] = (         int  )2;
   sqlstm.sqindv[4] = (         void  *)0;
   sqlstm.sqinds[4] = (         int  )0;
   sqlstm.sqharm[4] = (unsigned int  )0;
   sqlstm.sqharc[4] = (unsigned int   *)0;
   sqlstm.sqadto[4] = (unsigned short )0;
   sqlstm.sqtdso[4] = (unsigned short )0;
   sqlstm.sqhstv[5] = (         void  *)ER_FILE_SEQUENCE_NUMBER;
   sqlstm.sqhstl[5] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[5] = (         int  )sizeof(long);
   sqlstm.sqindv[5] = (         void  *)0;
   sqlstm.sqinds[5] = (         int  )0;
   sqlstm.sqharm[5] = (unsigned int  )0;
   sqlstm.sqharc[5] = (unsigned int   *)0;
   sqlstm.sqadto[5] = (unsigned short )0;
   sqlstm.sqtdso[5] = (unsigned short )0;
   sqlstm.sqhstv[6] = (         void  *)ER_RAP_SEQUENCE_NUMBER;
   sqlstm.sqhstl[6] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[6] = (         int  )sizeof(long);
   sqlstm.sqindv[6] = (         void  *)0;
   sqlstm.sqinds[6] = (         int  )0;
   sqlstm.sqharm[6] = (unsigned int  )0;
   sqlstm.sqharc[6] = (unsigned int   *)0;
   sqlstm.sqadto[6] = (unsigned short )0;
   sqlstm.sqtdso[6] = (unsigned short )0;
   sqlstm.sqhstv[7] = (         void  *)ER_CALL_SEQUENCE;
   sqlstm.sqhstl[7] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[7] = (         int  )sizeof(long);
   sqlstm.sqindv[7] = (         void  *)0;
   sqlstm.sqinds[7] = (         int  )0;
   sqlstm.sqharm[7] = (unsigned int  )0;
   sqlstm.sqharc[7] = (unsigned int   *)0;
   sqlstm.sqadto[7] = (unsigned short )0;
   sqlstm.sqtdso[7] = (unsigned short )0;
   sqlstm.sqhstv[8] = (         void  *)ER_ERROR_SEQUENCE;
   sqlstm.sqhstl[8] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[8] = (         int  )sizeof(long);
   sqlstm.sqindv[8] = (         void  *)0;
   sqlstm.sqinds[8] = (         int  )0;
   sqlstm.sqharm[8] = (unsigned int  )0;
   sqlstm.sqharc[8] = (unsigned int   *)0;
   sqlstm.sqadto[8] = (unsigned short )0;
   sqlstm.sqtdso[8] = (unsigned short )0;
   sqlstm.sqhstv[9] = (         void  *)ER_CALLS_TYPE_INDICATOR;
   sqlstm.sqhstl[9] = (unsigned int  )2;
   sqlstm.sqhsts[9] = (         int  )2;
   sqlstm.sqindv[9] = (         void  *)0;
   sqlstm.sqinds[9] = (         int  )0;
   sqlstm.sqharm[9] = (unsigned int  )0;
   sqlstm.sqharc[9] = (unsigned int   *)0;
   sqlstm.sqadto[9] = (unsigned short )0;
   sqlstm.sqtdso[9] = (unsigned short )0;
   sqlstm.sqhstv[10] = (         void  *)ER_CALL_TYPE;
   sqlstm.sqhstl[10] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[10] = (         int  )sizeof(long);
   sqlstm.sqindv[10] = (         void  *)0;
   sqlstm.sqinds[10] = (         int  )0;
   sqlstm.sqharm[10] = (unsigned int  )0;
   sqlstm.sqharc[10] = (unsigned int   *)0;
   sqlstm.sqadto[10] = (unsigned short )0;
   sqlstm.sqtdso[10] = (unsigned short )0;
   sqlstm.sqhstv[11] = (         void  *)ER_SERVICE_CODE;
   sqlstm.sqhstl[11] = (unsigned int  )4;
   sqlstm.sqhsts[11] = (         int  )4;
   sqlstm.sqindv[11] = (         void  *)0;
   sqlstm.sqinds[11] = (         int  )0;
   sqlstm.sqharm[11] = (unsigned int  )0;
   sqlstm.sqharc[11] = (unsigned int   *)0;
   sqlstm.sqadto[11] = (unsigned short )0;
   sqlstm.sqtdso[11] = (unsigned short )0;
   sqlstm.sqhstv[12] = (         void  *)ER_IMSI;
   sqlstm.sqhstl[12] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[12] = (         int  )sizeof(double);
   sqlstm.sqindv[12] = (         void  *)0;
   sqlstm.sqinds[12] = (         int  )0;
   sqlstm.sqharm[12] = (unsigned int  )0;
   sqlstm.sqharc[12] = (unsigned int   *)0;
   sqlstm.sqadto[12] = (unsigned short )0;
   sqlstm.sqtdso[12] = (unsigned short )0;
   sqlstm.sqhstv[13] = (         void  *)ER_MSISDN;
   sqlstm.sqhstl[13] = (unsigned int  )26;
   sqlstm.sqhsts[13] = (         int  )26;
   sqlstm.sqindv[13] = (         void  *)0;
   sqlstm.sqinds[13] = (         int  )0;
   sqlstm.sqharm[13] = (unsigned int  )0;
   sqlstm.sqharc[13] = (unsigned int   *)0;
   sqlstm.sqadto[13] = (unsigned short )0;
   sqlstm.sqtdso[13] = (unsigned short )0;
   sqlstm.sqhstv[14] = (         void  *)ER_CALLED_CALLING_NUMBER;
   sqlstm.sqhstl[14] = (unsigned int  )87;
   sqlstm.sqhsts[14] = (         int  )87;
   sqlstm.sqindv[14] = (         void  *)0;
   sqlstm.sqinds[14] = (         int  )0;
   sqlstm.sqharm[14] = (unsigned int  )0;
   sqlstm.sqharc[14] = (unsigned int   *)0;
   sqlstm.sqadto[14] = (unsigned short )0;
   sqlstm.sqtdso[14] = (unsigned short )0;
   sqlstm.sqhstv[15] = (         void  *)ER_DIALLED_DIGITS;
   sqlstm.sqhstl[15] = (unsigned int  )87;
   sqlstm.sqhsts[15] = (         int  )87;
   sqlstm.sqindv[15] = (         void  *)0;
   sqlstm.sqinds[15] = (         int  )0;
   sqlstm.sqharm[15] = (unsigned int  )0;
   sqlstm.sqharc[15] = (unsigned int   *)0;
   sqlstm.sqadto[15] = (unsigned short )0;
   sqlstm.sqtdso[15] = (unsigned short )0;
   sqlstm.sqhstv[16] = (         void  *)ER_CLIR_INDICATOR;
   sqlstm.sqhstl[16] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[16] = (         int  )sizeof(long);
   sqlstm.sqindv[16] = (         void  *)0;
   sqlstm.sqinds[16] = (         int  )0;
   sqlstm.sqharm[16] = (unsigned int  )0;
   sqlstm.sqharc[16] = (unsigned int   *)0;
   sqlstm.sqadto[16] = (unsigned short )0;
   sqlstm.sqtdso[16] = (unsigned short )0;
   sqlstm.sqhstv[17] = (         void  *)ER_DESTINATION_NETWORK;
   sqlstm.sqhstl[17] = (unsigned int  )7;
   sqlstm.sqhsts[17] = (         int  )7;
   sqlstm.sqindv[17] = (         void  *)0;
   sqlstm.sqinds[17] = (         int  )0;
   sqlstm.sqharm[17] = (unsigned int  )0;
   sqlstm.sqharc[17] = (unsigned int   *)0;
   sqlstm.sqadto[17] = (unsigned short )0;
   sqlstm.sqtdso[17] = (unsigned short )0;
   sqlstm.sqhstv[18] = (         void  *)ER_CALL_DATE;
   sqlstm.sqhstl[18] = (unsigned int  )15;
   sqlstm.sqhsts[18] = (         int  )15;
   sqlstm.sqindv[18] = (         void  *)0;
   sqlstm.sqinds[18] = (         int  )0;
   sqlstm.sqharm[18] = (unsigned int  )0;
   sqlstm.sqharc[18] = (unsigned int   *)0;
   sqlstm.sqadto[18] = (unsigned short )0;
   sqlstm.sqtdso[18] = (unsigned short )0;
   sqlstm.sqhstv[19] = (         void  *)ER_UTC_OFFSET_CODE;
   sqlstm.sqhstl[19] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[19] = (         int  )sizeof(long);
   sqlstm.sqindv[19] = (         void  *)0;
   sqlstm.sqinds[19] = (         int  )0;
   sqlstm.sqharm[19] = (unsigned int  )0;
   sqlstm.sqharc[19] = (unsigned int   *)0;
   sqlstm.sqadto[19] = (unsigned short )0;
   sqlstm.sqtdso[19] = (unsigned short )0;
   sqlstm.sqhstv[20] = (         void  *)ER_UTC_OFFSET;
   sqlstm.sqhstl[20] = (unsigned int  )6;
   sqlstm.sqhsts[20] = (         int  )6;
   sqlstm.sqindv[20] = (         void  *)0;
   sqlstm.sqinds[20] = (         int  )0;
   sqlstm.sqharm[20] = (unsigned int  )0;
   sqlstm.sqharc[20] = (unsigned int   *)0;
   sqlstm.sqadto[20] = (unsigned short )0;
   sqlstm.sqtdso[20] = (unsigned short )0;
   sqlstm.sqhstv[21] = (         void  *)ER_CALL_DURATION;
   sqlstm.sqhstl[21] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[21] = (         int  )sizeof(double);
   sqlstm.sqindv[21] = (         void  *)0;
   sqlstm.sqinds[21] = (         int  )0;
   sqlstm.sqharm[21] = (unsigned int  )0;
   sqlstm.sqharc[21] = (unsigned int   *)0;
   sqlstm.sqadto[21] = (unsigned short )0;
   sqlstm.sqtdso[21] = (unsigned short )0;
   sqlstm.sqhstv[22] = (         void  *)ER_SIM_TOOLKIT_INDICATOR;
   sqlstm.sqhstl[22] = (unsigned int  )2;
   sqlstm.sqhsts[22] = (         int  )2;
   sqlstm.sqindv[22] = (         void  *)0;
   sqlstm.sqinds[22] = (         int  )0;
   sqlstm.sqharm[22] = (unsigned int  )0;
   sqlstm.sqharc[22] = (unsigned int   *)0;
   sqlstm.sqadto[22] = (unsigned short )0;
   sqlstm.sqtdso[22] = (unsigned short )0;
   sqlstm.sqhstv[23] = (         void  *)ER_RECORDING_ENTITY_CODE;
   sqlstm.sqhstl[23] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[23] = (         int  )sizeof(long);
   sqlstm.sqindv[23] = (         void  *)0;
   sqlstm.sqinds[23] = (         int  )0;
   sqlstm.sqharm[23] = (unsigned int  )0;
   sqlstm.sqharc[23] = (unsigned int   *)0;
   sqlstm.sqadto[23] = (unsigned short )0;
   sqlstm.sqtdso[23] = (unsigned short )0;
   sqlstm.sqhstv[24] = (         void  *)ER_RECORDING_ENTITY_TYPE;
   sqlstm.sqhstl[24] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[24] = (         int  )sizeof(long);
   sqlstm.sqindv[24] = (         void  *)0;
   sqlstm.sqinds[24] = (         int  )0;
   sqlstm.sqharm[24] = (unsigned int  )0;
   sqlstm.sqharc[24] = (unsigned int   *)0;
   sqlstm.sqadto[24] = (unsigned short )0;
   sqlstm.sqtdso[24] = (unsigned short )0;
   sqlstm.sqhstv[25] = (         void  *)ER_RECORDING_ENTITY_ID;
   sqlstm.sqhstl[25] = (unsigned int  )46;
   sqlstm.sqhsts[25] = (         int  )46;
   sqlstm.sqindv[25] = (         void  *)0;
   sqlstm.sqinds[25] = (         int  )0;
   sqlstm.sqharm[25] = (unsigned int  )0;
   sqlstm.sqharc[25] = (unsigned int   *)0;
   sqlstm.sqadto[25] = (unsigned short )0;
   sqlstm.sqtdso[25] = (unsigned short )0;
   sqlstm.sqhstv[26] = (         void  *)ER_CALL_REFERENCE;
   sqlstm.sqhstl[26] = (unsigned int  )21;
   sqlstm.sqhsts[26] = (         int  )21;
   sqlstm.sqindv[26] = (         void  *)0;
   sqlstm.sqinds[26] = (         int  )0;
   sqlstm.sqharm[26] = (unsigned int  )0;
   sqlstm.sqharc[26] = (unsigned int   *)0;
   sqlstm.sqadto[26] = (unsigned short )0;
   sqlstm.sqtdso[26] = (unsigned short )0;
   sqlstm.sqhstv[27] = (         void  *)ER_CELLID;
   sqlstm.sqhstl[27] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[27] = (         int  )sizeof(double);
   sqlstm.sqindv[27] = (         void  *)0;
   sqlstm.sqinds[27] = (         int  )0;
   sqlstm.sqharm[27] = (unsigned int  )0;
   sqlstm.sqharc[27] = (unsigned int   *)0;
   sqlstm.sqadto[27] = (unsigned short )0;
   sqlstm.sqtdso[27] = (unsigned short )0;
   sqlstm.sqhstv[28] = (         void  *)ER_SERVING_NETWORK;
   sqlstm.sqhstl[28] = (unsigned int  )6;
   sqlstm.sqhsts[28] = (         int  )6;
   sqlstm.sqindv[28] = (         void  *)0;
   sqlstm.sqinds[28] = (         int  )0;
   sqlstm.sqharm[28] = (unsigned int  )0;
   sqlstm.sqharc[28] = (unsigned int   *)0;
   sqlstm.sqadto[28] = (unsigned short )0;
   sqlstm.sqtdso[28] = (unsigned short )0;
   sqlstm.sqhstv[29] = (         void  *)ER_IMEI;
   sqlstm.sqhstl[29] = (unsigned int  )21;
   sqlstm.sqhsts[29] = (         int  )21;
   sqlstm.sqindv[29] = (         void  *)0;
   sqlstm.sqinds[29] = (         int  )0;
   sqlstm.sqharm[29] = (unsigned int  )0;
   sqlstm.sqharc[29] = (unsigned int   *)0;
   sqlstm.sqadto[29] = (unsigned short )0;
   sqlstm.sqtdso[29] = (unsigned short )0;
   sqlstm.sqhstv[30] = (         void  *)ER_BASIC_SERVICE_TYPE;
   sqlstm.sqhstl[30] = (unsigned int  )2;
   sqlstm.sqhsts[30] = (         int  )2;
   sqlstm.sqindv[30] = (         void  *)0;
   sqlstm.sqinds[30] = (         int  )0;
   sqlstm.sqharm[30] = (unsigned int  )0;
   sqlstm.sqharc[30] = (unsigned int   *)0;
   sqlstm.sqadto[30] = (unsigned short )0;
   sqlstm.sqtdso[30] = (unsigned short )0;
   sqlstm.sqhstv[31] = (         void  *)ER_BASIC_SERVICE_CODE;
   sqlstm.sqhstl[31] = (unsigned int  )4;
   sqlstm.sqhsts[31] = (         int  )4;
   sqlstm.sqindv[31] = (         void  *)0;
   sqlstm.sqinds[31] = (         int  )0;
   sqlstm.sqharm[31] = (unsigned int  )0;
   sqlstm.sqharc[31] = (unsigned int   *)0;
   sqlstm.sqadto[31] = (unsigned short )0;
   sqlstm.sqtdso[31] = (unsigned short )0;
   sqlstm.sqhstv[32] = (         void  *)ER_TRANSPARENCY_INDICATOR;
   sqlstm.sqhstl[32] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[32] = (         int  )sizeof(long);
   sqlstm.sqindv[32] = (         void  *)0;
   sqlstm.sqinds[32] = (         int  )0;
   sqlstm.sqharm[32] = (unsigned int  )0;
   sqlstm.sqharc[32] = (unsigned int   *)0;
   sqlstm.sqadto[32] = (unsigned short )0;
   sqlstm.sqtdso[32] = (unsigned short )0;
   sqlstm.sqhstv[33] = (         void  *)ER_FNUR;
   sqlstm.sqhstl[33] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[33] = (         int  )sizeof(double);
   sqlstm.sqindv[33] = (         void  *)0;
   sqlstm.sqinds[33] = (         int  )0;
   sqlstm.sqharm[33] = (unsigned int  )0;
   sqlstm.sqharc[33] = (unsigned int   *)0;
   sqlstm.sqadto[33] = (unsigned short )0;
   sqlstm.sqtdso[33] = (unsigned short )0;
   sqlstm.sqhstv[34] = (         void  *)ER_USER_PROTOCOL_INDICATOR;
   sqlstm.sqhstl[34] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[34] = (         int  )sizeof(double);
   sqlstm.sqindv[34] = (         void  *)0;
   sqlstm.sqinds[34] = (         int  )0;
   sqlstm.sqharm[34] = (unsigned int  )0;
   sqlstm.sqharc[34] = (unsigned int   *)0;
   sqlstm.sqadto[34] = (unsigned short )0;
   sqlstm.sqtdso[34] = (unsigned short )0;
   sqlstm.sqhstv[35] = (         void  *)ER_GUARANTEED_BIT_RATE;
   sqlstm.sqhstl[35] = (unsigned int  )6;
   sqlstm.sqhsts[35] = (         int  )6;
   sqlstm.sqindv[35] = (         void  *)0;
   sqlstm.sqinds[35] = (         int  )0;
   sqlstm.sqharm[35] = (unsigned int  )0;
   sqlstm.sqharc[35] = (unsigned int   *)0;
   sqlstm.sqadto[35] = (unsigned short )0;
   sqlstm.sqtdso[35] = (unsigned short )0;
   sqlstm.sqhstv[36] = (         void  *)ER_MAXIMUM_BIT_RATE;
   sqlstm.sqhstl[36] = (unsigned int  )6;
   sqlstm.sqhsts[36] = (         int  )6;
   sqlstm.sqindv[36] = (         void  *)0;
   sqlstm.sqinds[36] = (         int  )0;
   sqlstm.sqharm[36] = (unsigned int  )0;
   sqlstm.sqharc[36] = (unsigned int   *)0;
   sqlstm.sqadto[36] = (unsigned short )0;
   sqlstm.sqtdso[36] = (unsigned short )0;
   sqlstm.sqhstv[37] = (         void  *)ER_HSCSD_INDICATOR;
   sqlstm.sqhstl[37] = (unsigned int  )4;
   sqlstm.sqhsts[37] = (         int  )4;
   sqlstm.sqindv[37] = (         void  *)0;
   sqlstm.sqinds[37] = (         int  )0;
   sqlstm.sqharm[37] = (unsigned int  )0;
   sqlstm.sqharc[37] = (unsigned int   *)0;
   sqlstm.sqadto[37] = (unsigned short )0;
   sqlstm.sqtdso[37] = (unsigned short )0;
   sqlstm.sqhstv[38] = (         void  *)ER_SUPPLIMENTARY_SERVICE_CODE;
   sqlstm.sqhstl[38] = (unsigned int  )21;
   sqlstm.sqhsts[38] = (         int  )21;
   sqlstm.sqindv[38] = (         void  *)0;
   sqlstm.sqinds[38] = (         int  )0;
   sqlstm.sqharm[38] = (unsigned int  )0;
   sqlstm.sqharc[38] = (unsigned int   *)0;
   sqlstm.sqadto[38] = (unsigned short )0;
   sqlstm.sqtdso[38] = (unsigned short )0;
   sqlstm.sqhstv[39] = (         void  *)ER_SUPPLIMENTARY_ACTION_CODE;
   sqlstm.sqhstl[39] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[39] = (         int  )sizeof(long);
   sqlstm.sqindv[39] = (         void  *)0;
   sqlstm.sqinds[39] = (         int  )0;
   sqlstm.sqharm[39] = (unsigned int  )0;
   sqlstm.sqharc[39] = (unsigned int   *)0;
   sqlstm.sqadto[39] = (unsigned short )0;
   sqlstm.sqtdso[39] = (unsigned short )0;
   sqlstm.sqhstv[40] = (         void  *)ER_SUPPLIMENTARY_SERVICE_PARAMS;
   sqlstm.sqhstl[40] = (unsigned int  )46;
   sqlstm.sqhsts[40] = (         int  )46;
   sqlstm.sqindv[40] = (         void  *)0;
   sqlstm.sqinds[40] = (         int  )0;
   sqlstm.sqharm[40] = (unsigned int  )0;
   sqlstm.sqharc[40] = (unsigned int   *)0;
   sqlstm.sqadto[40] = (unsigned short )0;
   sqlstm.sqtdso[40] = (unsigned short )0;
   sqlstm.sqhstv[41] = (         void  *)ER_THIRD_PARTY_NUMBER;
   sqlstm.sqhstl[41] = (unsigned int  )87;
   sqlstm.sqhsts[41] = (         int  )87;
   sqlstm.sqindv[41] = (         void  *)0;
   sqlstm.sqinds[41] = (         int  )0;
   sqlstm.sqharm[41] = (unsigned int  )0;
   sqlstm.sqharc[41] = (unsigned int   *)0;
   sqlstm.sqadto[41] = (unsigned short )0;
   sqlstm.sqtdso[41] = (unsigned short )0;
   sqlstm.sqhstv[42] = (         void  *)ER_THIRD_PARTY_CLIR_INDICATOR;
   sqlstm.sqhstl[42] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[42] = (         int  )sizeof(long);
   sqlstm.sqindv[42] = (         void  *)0;
   sqlstm.sqinds[42] = (         int  )0;
   sqlstm.sqharm[42] = (unsigned int  )0;
   sqlstm.sqharc[42] = (unsigned int   *)0;
   sqlstm.sqadto[42] = (unsigned short )0;
   sqlstm.sqtdso[42] = (unsigned short )0;
   sqlstm.sqhstv[43] = (         void  *)ER_CAMEL_USED_FLAG;
   sqlstm.sqhstl[43] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[43] = (         int  )sizeof(long);
   sqlstm.sqindv[43] = (         void  *)0;
   sqlstm.sqinds[43] = (         int  )0;
   sqlstm.sqharm[43] = (unsigned int  )0;
   sqlstm.sqharc[43] = (unsigned int   *)0;
   sqlstm.sqadto[43] = (unsigned short )0;
   sqlstm.sqtdso[43] = (unsigned short )0;
   sqlstm.sqhstv[44] = (         void  *)ER_CAMEL_SERVICE_LEVEL;
   sqlstm.sqhstl[44] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[44] = (         int  )sizeof(double);
   sqlstm.sqindv[44] = (         void  *)0;
   sqlstm.sqinds[44] = (         int  )0;
   sqlstm.sqharm[44] = (unsigned int  )0;
   sqlstm.sqharc[44] = (unsigned int   *)0;
   sqlstm.sqadto[44] = (unsigned short )0;
   sqlstm.sqtdso[44] = (unsigned short )0;
   sqlstm.sqhstv[45] = (         void  *)ER_CAMEL_SERVICE_KEY;
   sqlstm.sqhstl[45] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[45] = (         int  )sizeof(double);
   sqlstm.sqindv[45] = (         void  *)0;
   sqlstm.sqinds[45] = (         int  )0;
   sqlstm.sqharm[45] = (unsigned int  )0;
   sqlstm.sqharc[45] = (unsigned int   *)0;
   sqlstm.sqadto[45] = (unsigned short )0;
   sqlstm.sqtdso[45] = (unsigned short )0;
   sqlstm.sqhstv[46] = (         void  *)ER_CAMEL_DEFAULT_CALL_HANDLING;
   sqlstm.sqhstl[46] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[46] = (         int  )sizeof(double);
   sqlstm.sqindv[46] = (         void  *)0;
   sqlstm.sqinds[46] = (         int  )0;
   sqlstm.sqharm[46] = (unsigned int  )0;
   sqlstm.sqharc[46] = (unsigned int   *)0;
   sqlstm.sqadto[46] = (unsigned short )0;
   sqlstm.sqtdso[46] = (unsigned short )0;
   sqlstm.sqhstv[47] = (         void  *)ER_CAMEL_EXCHANGE_RATE_CODE;
   sqlstm.sqhstl[47] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[47] = (         int  )sizeof(long);
   sqlstm.sqindv[47] = (         void  *)0;
   sqlstm.sqinds[47] = (         int  )0;
   sqlstm.sqharm[47] = (unsigned int  )0;
   sqlstm.sqharc[47] = (unsigned int   *)0;
   sqlstm.sqadto[47] = (unsigned short )0;
   sqlstm.sqtdso[47] = (unsigned short )0;
   sqlstm.sqhstv[48] = (         void  *)ER_CAMEL_INVOCATION_FEE;
   sqlstm.sqhstl[48] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[48] = (         int  )sizeof(double);
   sqlstm.sqindv[48] = (         void  *)0;
   sqlstm.sqinds[48] = (         int  )0;
   sqlstm.sqharm[48] = (unsigned int  )0;
   sqlstm.sqharc[48] = (unsigned int   *)0;
   sqlstm.sqadto[48] = (unsigned short )0;
   sqlstm.sqtdso[48] = (unsigned short )0;
   sqlstm.sqhstv[49] = (         void  *)ER_CAMEL_DISCOUNT_CODE;
   sqlstm.sqhstl[49] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[49] = (         int  )sizeof(long);
   sqlstm.sqindv[49] = (         void  *)0;
   sqlstm.sqinds[49] = (         int  )0;
   sqlstm.sqharm[49] = (unsigned int  )0;
   sqlstm.sqharc[49] = (unsigned int   *)0;
   sqlstm.sqadto[49] = (unsigned short )0;
   sqlstm.sqtdso[49] = (unsigned short )0;
   sqlstm.sqhstv[50] = (         void  *)ER_CAMEL_DISCOUNT;
   sqlstm.sqhstl[50] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[50] = (         int  )sizeof(double);
   sqlstm.sqindv[50] = (         void  *)0;
   sqlstm.sqinds[50] = (         int  )0;
   sqlstm.sqharm[50] = (unsigned int  )0;
   sqlstm.sqharc[50] = (unsigned int   *)0;
   sqlstm.sqadto[50] = (unsigned short )0;
   sqlstm.sqtdso[50] = (unsigned short )0;
   sqlstm.sqhstv[51] = (         void  *)ER_CAMEL_DISCOUNTABLE_AMT;
   sqlstm.sqhstl[51] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[51] = (         int  )sizeof(double);
   sqlstm.sqindv[51] = (         void  *)0;
   sqlstm.sqinds[51] = (         int  )0;
   sqlstm.sqharm[51] = (unsigned int  )0;
   sqlstm.sqharc[51] = (unsigned int   *)0;
   sqlstm.sqadto[51] = (unsigned short )0;
   sqlstm.sqtdso[51] = (unsigned short )0;
   sqlstm.sqhstv[52] = (         void  *)ER_CAMEL_TAX_INFORMATION_COUNT;
   sqlstm.sqhstl[52] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[52] = (         int  )sizeof(long);
   sqlstm.sqindv[52] = (         void  *)0;
   sqlstm.sqinds[52] = (         int  )0;
   sqlstm.sqharm[52] = (unsigned int  )0;
   sqlstm.sqharc[52] = (unsigned int   *)0;
   sqlstm.sqadto[52] = (unsigned short )0;
   sqlstm.sqtdso[52] = (unsigned short )0;
   sqlstm.sqhstv[53] = (         void  *)ER_CAMEL_TAX_CODE;
   sqlstm.sqhstl[53] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[53] = (         int  )sizeof(long);
   sqlstm.sqindv[53] = (         void  *)0;
   sqlstm.sqinds[53] = (         int  )0;
   sqlstm.sqharm[53] = (unsigned int  )0;
   sqlstm.sqharc[53] = (unsigned int   *)0;
   sqlstm.sqadto[53] = (unsigned short )0;
   sqlstm.sqtdso[53] = (unsigned short )0;
   sqlstm.sqhstv[54] = (         void  *)ER_CAMEL_TAX_VALUE;
   sqlstm.sqhstl[54] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[54] = (         int  )sizeof(double);
   sqlstm.sqindv[54] = (         void  *)0;
   sqlstm.sqinds[54] = (         int  )0;
   sqlstm.sqharm[54] = (unsigned int  )0;
   sqlstm.sqharc[54] = (unsigned int   *)0;
   sqlstm.sqadto[54] = (unsigned short )0;
   sqlstm.sqtdso[54] = (unsigned short )0;
   sqlstm.sqhstv[55] = (         void  *)ER_CAMEL_TAXABLE_AMOUNT;
   sqlstm.sqhstl[55] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[55] = (         int  )sizeof(double);
   sqlstm.sqindv[55] = (         void  *)0;
   sqlstm.sqinds[55] = (         int  )0;
   sqlstm.sqharm[55] = (unsigned int  )0;
   sqlstm.sqharc[55] = (unsigned int   *)0;
   sqlstm.sqadto[55] = (unsigned short )0;
   sqlstm.sqtdso[55] = (unsigned short )0;
   sqlstm.sqhstv[56] = (         void  *)ER_CAMEL_DESTINATION_NUMBER;
   sqlstm.sqhstl[56] = (unsigned int  )87;
   sqlstm.sqhsts[56] = (         int  )87;
   sqlstm.sqindv[56] = (         void  *)0;
   sqlstm.sqinds[56] = (         int  )0;
   sqlstm.sqharm[56] = (unsigned int  )0;
   sqlstm.sqharc[56] = (unsigned int   *)0;
   sqlstm.sqadto[56] = (unsigned short )0;
   sqlstm.sqtdso[56] = (unsigned short )0;
   sqlstm.sqhstv[57] = (         void  *)ER_CALL_TYPE_LEVEL1;
   sqlstm.sqhstl[57] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[57] = (         int  )sizeof(long);
   sqlstm.sqindv[57] = (         void  *)0;
   sqlstm.sqinds[57] = (         int  )0;
   sqlstm.sqharm[57] = (unsigned int  )0;
   sqlstm.sqharc[57] = (unsigned int   *)0;
   sqlstm.sqadto[57] = (unsigned short )0;
   sqlstm.sqtdso[57] = (unsigned short )0;
   sqlstm.sqhstv[58] = (         void  *)ER_CALL_TYPE_LEVEL2;
   sqlstm.sqhstl[58] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[58] = (         int  )sizeof(long);
   sqlstm.sqindv[58] = (         void  *)0;
   sqlstm.sqinds[58] = (         int  )0;
   sqlstm.sqharm[58] = (unsigned int  )0;
   sqlstm.sqharc[58] = (unsigned int   *)0;
   sqlstm.sqadto[58] = (unsigned short )0;
   sqlstm.sqtdso[58] = (unsigned short )0;
   sqlstm.sqhstv[59] = (         void  *)ER_CALL_TYPE_LEVEL3;
   sqlstm.sqhstl[59] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[59] = (         int  )sizeof(long);
   sqlstm.sqindv[59] = (         void  *)0;
   sqlstm.sqinds[59] = (         int  )0;
   sqlstm.sqharm[59] = (unsigned int  )0;
   sqlstm.sqharc[59] = (unsigned int   *)0;
   sqlstm.sqadto[59] = (unsigned short )0;
   sqlstm.sqtdso[59] = (unsigned short )0;
   sqlstm.sqhstv[60] = (         void  *)ER_CHARGE_INFORMATION_COUNT;
   sqlstm.sqhstl[60] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[60] = (         int  )sizeof(long);
   sqlstm.sqindv[60] = (         void  *)0;
   sqlstm.sqinds[60] = (         int  )0;
   sqlstm.sqharm[60] = (unsigned int  )0;
   sqlstm.sqharc[60] = (unsigned int   *)0;
   sqlstm.sqadto[60] = (unsigned short )0;
   sqlstm.sqtdso[60] = (unsigned short )0;
   sqlstm.sqhstv[61] = (         void  *)ER_CHARGED_ITEM;
   sqlstm.sqhstl[61] = (unsigned int  )4;
   sqlstm.sqhsts[61] = (         int  )4;
   sqlstm.sqindv[61] = (         void  *)0;
   sqlstm.sqinds[61] = (         int  )0;
   sqlstm.sqharm[61] = (unsigned int  )0;
   sqlstm.sqharc[61] = (unsigned int   *)0;
   sqlstm.sqadto[61] = (unsigned short )0;
   sqlstm.sqtdso[61] = (unsigned short )0;
   sqlstm.sqhstv[62] = (         void  *)ER_CHARGE_TYPE;
   sqlstm.sqhstl[62] = (unsigned int  )4;
   sqlstm.sqhsts[62] = (         int  )4;
   sqlstm.sqindv[62] = (         void  *)0;
   sqlstm.sqinds[62] = (         int  )0;
   sqlstm.sqharm[62] = (unsigned int  )0;
   sqlstm.sqharc[62] = (unsigned int   *)0;
   sqlstm.sqadto[62] = (unsigned short )0;
   sqlstm.sqtdso[62] = (unsigned short )0;
   sqlstm.sqhstv[63] = (         void  *)ER_CHARGEABLE_UNITS;
   sqlstm.sqhstl[63] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[63] = (         int  )sizeof(double);
   sqlstm.sqindv[63] = (         void  *)0;
   sqlstm.sqinds[63] = (         int  )0;
   sqlstm.sqharm[63] = (unsigned int  )0;
   sqlstm.sqharc[63] = (unsigned int   *)0;
   sqlstm.sqadto[63] = (unsigned short )0;
   sqlstm.sqtdso[63] = (unsigned short )0;
   sqlstm.sqhstv[64] = (         void  *)ER_CHARGED_UNITS;
   sqlstm.sqhstl[64] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[64] = (         int  )sizeof(double);
   sqlstm.sqindv[64] = (         void  *)0;
   sqlstm.sqinds[64] = (         int  )0;
   sqlstm.sqharm[64] = (unsigned int  )0;
   sqlstm.sqharc[64] = (unsigned int   *)0;
   sqlstm.sqadto[64] = (unsigned short )0;
   sqlstm.sqtdso[64] = (unsigned short )0;
   sqlstm.sqhstv[65] = (         void  *)ER_CHARGE;
   sqlstm.sqhstl[65] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[65] = (         int  )sizeof(double);
   sqlstm.sqindv[65] = (         void  *)0;
   sqlstm.sqinds[65] = (         int  )0;
   sqlstm.sqharm[65] = (unsigned int  )0;
   sqlstm.sqharc[65] = (unsigned int   *)0;
   sqlstm.sqadto[65] = (unsigned short )0;
   sqlstm.sqtdso[65] = (unsigned short )0;
   sqlstm.sqhstv[66] = (         void  *)ER_TAX_INFORMATION_COUNT;
   sqlstm.sqhstl[66] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[66] = (         int  )sizeof(long);
   sqlstm.sqindv[66] = (         void  *)0;
   sqlstm.sqinds[66] = (         int  )0;
   sqlstm.sqharm[66] = (unsigned int  )0;
   sqlstm.sqharc[66] = (unsigned int   *)0;
   sqlstm.sqadto[66] = (unsigned short )0;
   sqlstm.sqtdso[66] = (unsigned short )0;
   sqlstm.sqhstv[67] = (         void  *)ER_TAX_CODE;
   sqlstm.sqhstl[67] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[67] = (         int  )sizeof(long);
   sqlstm.sqindv[67] = (         void  *)0;
   sqlstm.sqinds[67] = (         int  )0;
   sqlstm.sqharm[67] = (unsigned int  )0;
   sqlstm.sqharc[67] = (unsigned int   *)0;
   sqlstm.sqadto[67] = (unsigned short )0;
   sqlstm.sqtdso[67] = (unsigned short )0;
   sqlstm.sqhstv[68] = (         void  *)ER_TAX_VALUE;
   sqlstm.sqhstl[68] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[68] = (         int  )sizeof(double);
   sqlstm.sqindv[68] = (         void  *)0;
   sqlstm.sqinds[68] = (         int  )0;
   sqlstm.sqharm[68] = (unsigned int  )0;
   sqlstm.sqharc[68] = (unsigned int   *)0;
   sqlstm.sqadto[68] = (unsigned short )0;
   sqlstm.sqtdso[68] = (unsigned short )0;
   sqlstm.sqhstv[69] = (         void  *)ER_TAXABLE_AMOUNT;
   sqlstm.sqhstl[69] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[69] = (         int  )sizeof(double);
   sqlstm.sqindv[69] = (         void  *)0;
   sqlstm.sqinds[69] = (         int  )0;
   sqlstm.sqharm[69] = (unsigned int  )0;
   sqlstm.sqharc[69] = (unsigned int   *)0;
   sqlstm.sqadto[69] = (unsigned short )0;
   sqlstm.sqtdso[69] = (unsigned short )0;
   sqlstm.sqhstv[70] = (         void  *)ER_DISCOUNT_INFORMATION_COUNT;
   sqlstm.sqhstl[70] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[70] = (         int  )sizeof(long);
   sqlstm.sqindv[70] = (         void  *)0;
   sqlstm.sqinds[70] = (         int  )0;
   sqlstm.sqharm[70] = (unsigned int  )0;
   sqlstm.sqharc[70] = (unsigned int   *)0;
   sqlstm.sqadto[70] = (unsigned short )0;
   sqlstm.sqtdso[70] = (unsigned short )0;
   sqlstm.sqhstv[71] = (         void  *)ER_DISCOUNT_CODE;
   sqlstm.sqhstl[71] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[71] = (         int  )sizeof(long);
   sqlstm.sqindv[71] = (         void  *)0;
   sqlstm.sqinds[71] = (         int  )0;
   sqlstm.sqharm[71] = (unsigned int  )0;
   sqlstm.sqharc[71] = (unsigned int   *)0;
   sqlstm.sqadto[71] = (unsigned short )0;
   sqlstm.sqtdso[71] = (unsigned short )0;
   sqlstm.sqhstv[72] = (         void  *)ER_DISCOUNT;
   sqlstm.sqhstl[72] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[72] = (         int  )sizeof(double);
   sqlstm.sqindv[72] = (         void  *)0;
   sqlstm.sqinds[72] = (         int  )0;
   sqlstm.sqharm[72] = (unsigned int  )0;
   sqlstm.sqharc[72] = (unsigned int   *)0;
   sqlstm.sqadto[72] = (unsigned short )0;
   sqlstm.sqtdso[72] = (unsigned short )0;
   sqlstm.sqhstv[73] = (         void  *)ER_DISCOUNTABLE_AMT;
   sqlstm.sqhstl[73] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[73] = (         int  )sizeof(double);
   sqlstm.sqindv[73] = (         void  *)0;
   sqlstm.sqinds[73] = (         int  )0;
   sqlstm.sqharm[73] = (unsigned int  )0;
   sqlstm.sqharc[73] = (unsigned int   *)0;
   sqlstm.sqadto[73] = (unsigned short )0;
   sqlstm.sqtdso[73] = (unsigned short )0;
   sqlstm.sqhstv[74] = (         void  *)ER_TAP_EXCHANGE_RATE_CODE;
   sqlstm.sqhstl[74] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[74] = (         int  )sizeof(long);
   sqlstm.sqindv[74] = (         void  *)0;
   sqlstm.sqinds[74] = (         int  )0;
   sqlstm.sqharm[74] = (unsigned int  )0;
   sqlstm.sqharc[74] = (unsigned int   *)0;
   sqlstm.sqadto[74] = (unsigned short )0;
   sqlstm.sqtdso[74] = (unsigned short )0;
   sqlstm.sqhstv[75] = (         void  *)ER_TAP_EXCHANGE_RATE;
   sqlstm.sqhstl[75] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[75] = (         int  )sizeof(double);
   sqlstm.sqindv[75] = (         void  *)0;
   sqlstm.sqinds[75] = (         int  )0;
   sqlstm.sqharm[75] = (unsigned int  )0;
   sqlstm.sqharc[75] = (unsigned int   *)0;
   sqlstm.sqadto[75] = (unsigned short )0;
   sqlstm.sqtdso[75] = (unsigned short )0;
   sqlstm.sqhstv[76] = (         void  *)ER_TAP_EXCHANGE_RATE_DECIMAL;
   sqlstm.sqhstl[76] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[76] = (         int  )sizeof(long);
   sqlstm.sqindv[76] = (         void  *)0;
   sqlstm.sqinds[76] = (         int  )0;
   sqlstm.sqharm[76] = (unsigned int  )0;
   sqlstm.sqharc[76] = (unsigned int   *)0;
   sqlstm.sqadto[76] = (unsigned short )0;
   sqlstm.sqtdso[76] = (unsigned short )0;
   sqlstm.sqhstv[77] = (         void  *)ER_TAP_TAX_TYPE_RATE;
   sqlstm.sqhstl[77] = (unsigned int  )601;
   sqlstm.sqhsts[77] = (         int  )601;
   sqlstm.sqindv[77] = (         void  *)0;
   sqlstm.sqinds[77] = (         int  )0;
   sqlstm.sqharm[77] = (unsigned int  )0;
   sqlstm.sqharc[77] = (unsigned int   *)0;
   sqlstm.sqadto[77] = (unsigned short )0;
   sqlstm.sqtdso[77] = (unsigned short )0;
   sqlstm.sqhstv[78] = (         void  *)ER_NETWORK_ACCESS_IDENTIFER;
   sqlstm.sqhstl[78] = (unsigned int  )31;
   sqlstm.sqhsts[78] = (         int  )31;
   sqlstm.sqindv[78] = (         void  *)0;
   sqlstm.sqinds[78] = (         int  )0;
   sqlstm.sqharm[78] = (unsigned int  )0;
   sqlstm.sqharc[78] = (unsigned int   *)0;
   sqlstm.sqadto[78] = (unsigned short )0;
   sqlstm.sqtdso[78] = (unsigned short )0;
   sqlstm.sqhstv[79] = (         void  *)ER_PDP_ADDRESS;
   sqlstm.sqhstl[79] = (unsigned int  )46;
   sqlstm.sqhsts[79] = (         int  )46;
   sqlstm.sqindv[79] = (         void  *)0;
   sqlstm.sqinds[79] = (         int  )0;
   sqlstm.sqharm[79] = (unsigned int  )0;
   sqlstm.sqharc[79] = (unsigned int   *)0;
   sqlstm.sqadto[79] = (unsigned short )0;
   sqlstm.sqtdso[79] = (unsigned short )0;
   sqlstm.sqhstv[80] = (         void  *)ER_APN_NI;
   sqlstm.sqhstl[80] = (unsigned int  )66;
   sqlstm.sqhsts[80] = (         int  )66;
   sqlstm.sqindv[80] = (         void  *)0;
   sqlstm.sqinds[80] = (         int  )0;
   sqlstm.sqharm[80] = (unsigned int  )0;
   sqlstm.sqharc[80] = (unsigned int   *)0;
   sqlstm.sqadto[80] = (unsigned short )0;
   sqlstm.sqtdso[80] = (unsigned short )0;
   sqlstm.sqhstv[81] = (         void  *)ER_APN_OI;
   sqlstm.sqhstl[81] = (unsigned int  )66;
   sqlstm.sqhsts[81] = (         int  )66;
   sqlstm.sqindv[81] = (         void  *)0;
   sqlstm.sqinds[81] = (         int  )0;
   sqlstm.sqharm[81] = (unsigned int  )0;
   sqlstm.sqharc[81] = (unsigned int   *)0;
   sqlstm.sqadto[81] = (unsigned short )0;
   sqlstm.sqtdso[81] = (unsigned short )0;
   sqlstm.sqhstv[82] = (         void  *)ER_CAUSE_FOR_TERMINATION;
   sqlstm.sqhstl[82] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[82] = (         int  )sizeof(long);
   sqlstm.sqindv[82] = (         void  *)0;
   sqlstm.sqinds[82] = (         int  )0;
   sqlstm.sqharm[82] = (unsigned int  )0;
   sqlstm.sqharc[82] = (unsigned int   *)0;
   sqlstm.sqadto[82] = (unsigned short )0;
   sqlstm.sqtdso[82] = (unsigned short )0;
   sqlstm.sqhstv[83] = (         void  *)ER_PARTIAL_TYPE_INDICATOR;
   sqlstm.sqhstl[83] = (unsigned int  )2;
   sqlstm.sqhsts[83] = (         int  )2;
   sqlstm.sqindv[83] = (         void  *)0;
   sqlstm.sqinds[83] = (         int  )0;
   sqlstm.sqharm[83] = (unsigned int  )0;
   sqlstm.sqharc[83] = (unsigned int   *)0;
   sqlstm.sqadto[83] = (unsigned short )0;
   sqlstm.sqtdso[83] = (unsigned short )0;
   sqlstm.sqhstv[84] = (         void  *)ER_CHARGING_ID;
   sqlstm.sqhstl[84] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[84] = (         int  )sizeof(double);
   sqlstm.sqindv[84] = (         void  *)0;
   sqlstm.sqinds[84] = (         int  )0;
   sqlstm.sqharm[84] = (unsigned int  )0;
   sqlstm.sqharc[84] = (unsigned int   *)0;
   sqlstm.sqadto[84] = (unsigned short )0;
   sqlstm.sqtdso[84] = (unsigned short )0;
   sqlstm.sqhstv[85] = (         void  *)ER_DATA_VOLUME_INCOMING;
   sqlstm.sqhstl[85] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[85] = (         int  )sizeof(double);
   sqlstm.sqindv[85] = (         void  *)0;
   sqlstm.sqinds[85] = (         int  )0;
   sqlstm.sqharm[85] = (unsigned int  )0;
   sqlstm.sqharc[85] = (unsigned int   *)0;
   sqlstm.sqadto[85] = (unsigned short )0;
   sqlstm.sqtdso[85] = (unsigned short )0;
   sqlstm.sqhstv[86] = (         void  *)ER_DATA_VOLUME_OUTGOING;
   sqlstm.sqhstl[86] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[86] = (         int  )sizeof(double);
   sqlstm.sqindv[86] = (         void  *)0;
   sqlstm.sqinds[86] = (         int  )0;
   sqlstm.sqharm[86] = (unsigned int  )0;
   sqlstm.sqharc[86] = (unsigned int   *)0;
   sqlstm.sqadto[86] = (unsigned short )0;
   sqlstm.sqtdso[86] = (unsigned short )0;
   sqlstm.sqhstv[87] = (         void  *)ER_SGSN_RECORDING_ENTITY_CODE1;
   sqlstm.sqhstl[87] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[87] = (         int  )sizeof(long);
   sqlstm.sqindv[87] = (         void  *)0;
   sqlstm.sqinds[87] = (         int  )0;
   sqlstm.sqharm[87] = (unsigned int  )0;
   sqlstm.sqharc[87] = (unsigned int   *)0;
   sqlstm.sqadto[87] = (unsigned short )0;
   sqlstm.sqtdso[87] = (unsigned short )0;
   sqlstm.sqhstv[88] = (         void  *)ER_SGSN_RECORDING_ENTITY_ID1;
   sqlstm.sqhstl[88] = (unsigned int  )46;
   sqlstm.sqhsts[88] = (         int  )46;
   sqlstm.sqindv[88] = (         void  *)0;
   sqlstm.sqinds[88] = (         int  )0;
   sqlstm.sqharm[88] = (unsigned int  )0;
   sqlstm.sqharc[88] = (unsigned int   *)0;
   sqlstm.sqadto[88] = (unsigned short )0;
   sqlstm.sqtdso[88] = (unsigned short )0;
   sqlstm.sqhstv[89] = (         void  *)ER_SGSN_RECORDING_ENTITY_CODE2;
   sqlstm.sqhstl[89] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[89] = (         int  )sizeof(long);
   sqlstm.sqindv[89] = (         void  *)0;
   sqlstm.sqinds[89] = (         int  )0;
   sqlstm.sqharm[89] = (unsigned int  )0;
   sqlstm.sqharc[89] = (unsigned int   *)0;
   sqlstm.sqadto[89] = (unsigned short )0;
   sqlstm.sqtdso[89] = (unsigned short )0;
   sqlstm.sqhstv[90] = (         void  *)ER_SGSN_RECORDING_ENTITY_ID2;
   sqlstm.sqhstl[90] = (unsigned int  )46;
   sqlstm.sqhsts[90] = (         int  )46;
   sqlstm.sqindv[90] = (         void  *)0;
   sqlstm.sqinds[90] = (         int  )0;
   sqlstm.sqharm[90] = (unsigned int  )0;
   sqlstm.sqharc[90] = (unsigned int   *)0;
   sqlstm.sqadto[90] = (unsigned short )0;
   sqlstm.sqtdso[90] = (unsigned short )0;
   sqlstm.sqhstv[91] = (         void  *)ER_SGSN_RECORDING_ENTITY_CODE3;
   sqlstm.sqhstl[91] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[91] = (         int  )sizeof(long);
   sqlstm.sqindv[91] = (         void  *)0;
   sqlstm.sqinds[91] = (         int  )0;
   sqlstm.sqharm[91] = (unsigned int  )0;
   sqlstm.sqharc[91] = (unsigned int   *)0;
   sqlstm.sqadto[91] = (unsigned short )0;
   sqlstm.sqtdso[91] = (unsigned short )0;
   sqlstm.sqhstv[92] = (         void  *)ER_SGSN_RECORDING_ENTITY_ID3;
   sqlstm.sqhstl[92] = (unsigned int  )46;
   sqlstm.sqhsts[92] = (         int  )46;
   sqlstm.sqindv[92] = (         void  *)0;
   sqlstm.sqinds[92] = (         int  )0;
   sqlstm.sqharm[92] = (unsigned int  )0;
   sqlstm.sqharc[92] = (unsigned int   *)0;
   sqlstm.sqadto[92] = (unsigned short )0;
   sqlstm.sqtdso[92] = (unsigned short )0;
   sqlstm.sqhstv[93] = (         void  *)ER_CAMEL_APN_NI;
   sqlstm.sqhstl[93] = (unsigned int  )66;
   sqlstm.sqhsts[93] = (         int  )66;
   sqlstm.sqindv[93] = (         void  *)0;
   sqlstm.sqinds[93] = (         int  )0;
   sqlstm.sqharm[93] = (unsigned int  )0;
   sqlstm.sqharc[93] = (unsigned int   *)0;
   sqlstm.sqadto[93] = (unsigned short )0;
   sqlstm.sqtdso[93] = (unsigned short )0;
   sqlstm.sqhstv[94] = (         void  *)ER_CAMEL_APN_OI;
   sqlstm.sqhstl[94] = (unsigned int  )66;
   sqlstm.sqhsts[94] = (         int  )66;
   sqlstm.sqindv[94] = (         void  *)0;
   sqlstm.sqinds[94] = (         int  )0;
   sqlstm.sqharm[94] = (unsigned int  )0;
   sqlstm.sqharc[94] = (unsigned int   *)0;
   sqlstm.sqadto[94] = (unsigned short )0;
   sqlstm.sqtdso[94] = (unsigned short )0;
   sqlstm.sqhstv[95] = (         void  *)ER_FILE_CREATION_TIME;
   sqlstm.sqhstl[95] = (unsigned int  )15;
   sqlstm.sqhsts[95] = (         int  )15;
   sqlstm.sqindv[95] = (         void  *)0;
   sqlstm.sqinds[95] = (         int  )0;
   sqlstm.sqharm[95] = (unsigned int  )0;
   sqlstm.sqharc[95] = (unsigned int   *)0;
   sqlstm.sqadto[95] = (unsigned short )0;
   sqlstm.sqtdso[95] = (unsigned short )0;
   sqlstm.sqhstv[96] = (         void  *)ER_FILE_TRANSFER_TIME;
   sqlstm.sqhstl[96] = (unsigned int  )15;
   sqlstm.sqhsts[96] = (         int  )15;
   sqlstm.sqindv[96] = (         void  *)0;
   sqlstm.sqinds[96] = (         int  )0;
   sqlstm.sqharm[96] = (unsigned int  )0;
   sqlstm.sqharc[96] = (unsigned int   *)0;
   sqlstm.sqadto[96] = (unsigned short )0;
   sqlstm.sqtdso[96] = (unsigned short )0;
   sqlstm.sqhstv[97] = (         void  *)ER_FILE_AVAILABLE_TIME;
   sqlstm.sqhstl[97] = (unsigned int  )15;
   sqlstm.sqhsts[97] = (         int  )15;
   sqlstm.sqindv[97] = (         void  *)0;
   sqlstm.sqinds[97] = (         int  )0;
   sqlstm.sqharm[97] = (unsigned int  )0;
   sqlstm.sqharc[97] = (unsigned int   *)0;
   sqlstm.sqadto[97] = (unsigned short )0;
   sqlstm.sqtdso[97] = (unsigned short )0;
   sqlstm.sqhstv[98] = (         void  *)ER_CHARGING_TIME_STAMP;
   sqlstm.sqhstl[98] = (unsigned int  )15;
   sqlstm.sqhsts[98] = (         int  )15;
   sqlstm.sqindv[98] = (         void  *)0;
   sqlstm.sqinds[98] = (         int  )0;
   sqlstm.sqharm[98] = (unsigned int  )0;
   sqlstm.sqharc[98] = (unsigned int   *)0;
   sqlstm.sqadto[98] = (unsigned short )0;
   sqlstm.sqtdso[98] = (unsigned short )0;
   sqlstm.sqhstv[99] = (         void  *)ER_LOCAL_CURRENCY_CODE;
   sqlstm.sqhstl[99] = (unsigned int  )4;
   sqlstm.sqhsts[99] = (         int  )4;
   sqlstm.sqindv[99] = (         void  *)0;
   sqlstm.sqinds[99] = (         int  )0;
   sqlstm.sqharm[99] = (unsigned int  )0;
   sqlstm.sqharc[99] = (unsigned int   *)0;
   sqlstm.sqadto[99] = (unsigned short )0;
   sqlstm.sqtdso[99] = (unsigned short )0;
   sqlstm.sqhstv[100] = (         void  *)ER_TAP_CURRENCY_CODE;
   sqlstm.sqhstl[100] = (unsigned int  )4;
   sqlstm.sqhsts[100] = (         int  )4;
   sqlstm.sqindv[100] = (         void  *)0;
   sqlstm.sqinds[100] = (         int  )0;
   sqlstm.sqharm[100] = (unsigned int  )0;
   sqlstm.sqharc[100] = (unsigned int   *)0;
   sqlstm.sqadto[100] = (unsigned short )0;
   sqlstm.sqtdso[100] = (unsigned short )0;
   sqlstm.sqhstv[101] = (         void  *)ER_TAP_DECIMAL_PLACES;
   sqlstm.sqhstl[101] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[101] = (         int  )sizeof(long);
   sqlstm.sqindv[101] = (         void  *)0;
   sqlstm.sqinds[101] = (         int  )0;
   sqlstm.sqharm[101] = (unsigned int  )0;
   sqlstm.sqharc[101] = (unsigned int   *)0;
   sqlstm.sqadto[101] = (unsigned short )0;
   sqlstm.sqtdso[101] = (unsigned short )0;
   sqlstm.sqhstv[102] = (         void  *)ER_TARIFF_ID;
   sqlstm.sqhstl[102] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[102] = (         int  )sizeof(long);
   sqlstm.sqindv[102] = (         void  *)0;
   sqlstm.sqinds[102] = (         int  )0;
   sqlstm.sqharm[102] = (unsigned int  )0;
   sqlstm.sqharc[102] = (unsigned int   *)0;
   sqlstm.sqadto[102] = (unsigned short )0;
   sqlstm.sqtdso[102] = (unsigned short )0;
   sqlstm.sqhstv[103] = (         void  *)ER_IOT_CHARGE;
   sqlstm.sqhstl[103] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[103] = (         int  )sizeof(double);
   sqlstm.sqindv[103] = (         void  *)0;
   sqlstm.sqinds[103] = (         int  )0;
   sqlstm.sqharm[103] = (unsigned int  )0;
   sqlstm.sqharc[103] = (unsigned int   *)0;
   sqlstm.sqadto[103] = (unsigned short )0;
   sqlstm.sqtdso[103] = (unsigned short )0;
   sqlstm.sqhstv[104] = (         void  *)ER_IOT_TAX;
   sqlstm.sqhstl[104] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[104] = (         int  )sizeof(double);
   sqlstm.sqindv[104] = (         void  *)0;
   sqlstm.sqinds[104] = (         int  )0;
   sqlstm.sqharm[104] = (unsigned int  )0;
   sqlstm.sqharc[104] = (unsigned int   *)0;
   sqlstm.sqadto[104] = (unsigned short )0;
   sqlstm.sqtdso[104] = (unsigned short )0;
   sqlstm.sqhstv[105] = (         void  *)ER_IOT_DISCOUNT;
   sqlstm.sqhstl[105] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[105] = (         int  )sizeof(double);
   sqlstm.sqindv[105] = (         void  *)0;
   sqlstm.sqinds[105] = (         int  )0;
   sqlstm.sqharm[105] = (unsigned int  )0;
   sqlstm.sqharc[105] = (unsigned int   *)0;
   sqlstm.sqadto[105] = (unsigned short )0;
   sqlstm.sqtdso[105] = (unsigned short )0;
   sqlstm.sqhstv[106] = (         void  *)ER_ERROR_CODE;
   sqlstm.sqhstl[106] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[106] = (         int  )sizeof(int);
   sqlstm.sqindv[106] = (         void  *)0;
   sqlstm.sqinds[106] = (         int  )0;
   sqlstm.sqharm[106] = (unsigned int  )0;
   sqlstm.sqharc[106] = (unsigned int   *)0;
   sqlstm.sqadto[106] = (unsigned short )0;
   sqlstm.sqtdso[106] = (unsigned short )0;
   sqlstm.sqhstv[107] = (         void  *)ER_ERROR_TYPE;
   sqlstm.sqhstl[107] = (unsigned int  )8;
   sqlstm.sqhsts[107] = (         int  )8;
   sqlstm.sqindv[107] = (         void  *)0;
   sqlstm.sqinds[107] = (         int  )0;
   sqlstm.sqharm[107] = (unsigned int  )0;
   sqlstm.sqharc[107] = (unsigned int   *)0;
   sqlstm.sqadto[107] = (unsigned short )0;
   sqlstm.sqtdso[107] = (unsigned short )0;
   sqlstm.sqhstv[108] = (         void  *)ER_ERROR_CONTEXT_DETAILS;
   sqlstm.sqhstl[108] = (unsigned int  )101;
   sqlstm.sqhsts[108] = (         int  )101;
   sqlstm.sqindv[108] = (         void  *)0;
   sqlstm.sqinds[108] = (         int  )0;
   sqlstm.sqharm[108] = (unsigned int  )0;
   sqlstm.sqharc[108] = (unsigned int   *)0;
   sqlstm.sqadto[108] = (unsigned short )0;
   sqlstm.sqtdso[108] = (unsigned short )0;
   sqlstm.sqhstv[109] = (         void  *)ER_APPLICATION_TAG;
   sqlstm.sqhstl[109] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[109] = (         int  )sizeof(int);
   sqlstm.sqindv[109] = (         void  *)0;
   sqlstm.sqinds[109] = (         int  )0;
   sqlstm.sqharm[109] = (unsigned int  )0;
   sqlstm.sqharc[109] = (unsigned int   *)0;
   sqlstm.sqadto[109] = (unsigned short )0;
   sqlstm.sqtdso[109] = (unsigned short )0;
   sqlstm.sqhstv[110] = (         void  *)ER_CONTEXT_NAME;
   sqlstm.sqhstl[110] = (unsigned int  )51;
   sqlstm.sqhsts[110] = (         int  )51;
   sqlstm.sqindv[110] = (         void  *)0;
   sqlstm.sqinds[110] = (         int  )0;
   sqlstm.sqharm[110] = (unsigned int  )0;
   sqlstm.sqharc[110] = (unsigned int   *)0;
   sqlstm.sqadto[110] = (unsigned short )0;
   sqlstm.sqtdso[110] = (unsigned short )0;
   sqlstm.sqhstv[111] = (         void  *)ER_DATA_TYPE_INDICATOR;
   sqlstm.sqhstl[111] = (unsigned int  )2;
   sqlstm.sqhsts[111] = (         int  )2;
   sqlstm.sqindv[111] = (         void  *)0;
   sqlstm.sqinds[111] = (         int  )0;
   sqlstm.sqharm[111] = (unsigned int  )0;
   sqlstm.sqharc[111] = (unsigned int   *)0;
   sqlstm.sqadto[111] = (unsigned short )0;
   sqlstm.sqtdso[111] = (unsigned short )0;
   sqlstm.sqhstv[112] = (         void  *)ER_ERROR_FIELD_NAME;
   sqlstm.sqhstl[112] = (unsigned int  )51;
   sqlstm.sqhsts[112] = (         int  )51;
   sqlstm.sqindv[112] = (         void  *)0;
   sqlstm.sqinds[112] = (         int  )0;
   sqlstm.sqharm[112] = (unsigned int  )0;
   sqlstm.sqharc[112] = (unsigned int   *)0;
   sqlstm.sqadto[112] = (unsigned short )0;
   sqlstm.sqtdso[112] = (unsigned short )0;
   sqlstm.sqhstv[113] = (         void  *)ER_ERROR_MESSAGE;
   sqlstm.sqhstl[113] = (unsigned int  )501;
   sqlstm.sqhsts[113] = (         int  )501;
   sqlstm.sqindv[113] = (         void  *)0;
   sqlstm.sqinds[113] = (         int  )0;
   sqlstm.sqharm[113] = (unsigned int  )0;
   sqlstm.sqharc[113] = (unsigned int   *)0;
   sqlstm.sqadto[113] = (unsigned short )0;
   sqlstm.sqtdso[113] = (unsigned short )0;
   sqlstm.sqhstv[114] = (         void  *)ER_ERROR_VALUE;
   sqlstm.sqhstl[114] = (unsigned int  )101;
   sqlstm.sqhsts[114] = (         int  )101;
   sqlstm.sqindv[114] = (         void  *)0;
   sqlstm.sqinds[114] = (         int  )0;
   sqlstm.sqharm[114] = (unsigned int  )0;
   sqlstm.sqharc[114] = (unsigned int   *)0;
   sqlstm.sqadto[114] = (unsigned short )0;
   sqlstm.sqtdso[114] = (unsigned short )0;
   sqlstm.sqhstv[115] = (         void  *)ER_ERROR_NODE;
   sqlstm.sqhstl[115] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[115] = (         int  )sizeof(int);
   sqlstm.sqindv[115] = (         void  *)0;
   sqlstm.sqinds[115] = (         int  )0;
   sqlstm.sqharm[115] = (unsigned int  )0;
   sqlstm.sqharc[115] = (unsigned int   *)0;
   sqlstm.sqadto[115] = (unsigned short )0;
   sqlstm.sqtdso[115] = (unsigned short )0;
   sqlstm.sqhstv[116] = (         void  *)ER_RAP_STATUS;
   sqlstm.sqhstl[116] = (unsigned int  )101;
   sqlstm.sqhsts[116] = (         int  )101;
   sqlstm.sqindv[116] = (         void  *)0;
   sqlstm.sqinds[116] = (         int  )0;
   sqlstm.sqharm[116] = (unsigned int  )0;
   sqlstm.sqharc[116] = (unsigned int   *)0;
   sqlstm.sqadto[116] = (unsigned short )0;
   sqlstm.sqtdso[116] = (unsigned short )0;
   sqlstm.sqhstv[117] = (         void  *)ER_A_USERID;
   sqlstm.sqhstl[117] = (unsigned int  )66;
   sqlstm.sqhsts[117] = (         int  )66;
   sqlstm.sqindv[117] = (         void  *)0;
   sqlstm.sqinds[117] = (         int  )0;
   sqlstm.sqharm[117] = (unsigned int  )0;
   sqlstm.sqharc[117] = (unsigned int   *)0;
   sqlstm.sqadto[117] = (unsigned short )0;
   sqlstm.sqtdso[117] = (unsigned short )0;
   sqlstm.sqhstv[118] = (         void  *)ER_B_USERID;
   sqlstm.sqhstl[118] = (unsigned int  )66;
   sqlstm.sqhsts[118] = (         int  )66;
   sqlstm.sqindv[118] = (         void  *)0;
   sqlstm.sqinds[118] = (         int  )0;
   sqlstm.sqharm[118] = (unsigned int  )0;
   sqlstm.sqharc[118] = (unsigned int   *)0;
   sqlstm.sqadto[118] = (unsigned short )0;
   sqlstm.sqtdso[118] = (unsigned short )0;
   sqlstm.sqhstv[119] = (         void  *)ER_EVENT_REFERENCE;
   sqlstm.sqhstl[119] = (unsigned int  )66;
   sqlstm.sqhsts[119] = (         int  )66;
   sqlstm.sqindv[119] = (         void  *)0;
   sqlstm.sqinds[119] = (         int  )0;
   sqlstm.sqharm[119] = (unsigned int  )0;
   sqlstm.sqharc[119] = (unsigned int   *)0;
   sqlstm.sqadto[119] = (unsigned short )0;
   sqlstm.sqtdso[119] = (unsigned short )0;
   sqlstm.sqhstv[120] = (         void  *)ER_NETWORK_ELEMENT_TYPE1;
   sqlstm.sqhstl[120] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[120] = (         int  )sizeof(long);
   sqlstm.sqindv[120] = (         void  *)0;
   sqlstm.sqinds[120] = (         int  )0;
   sqlstm.sqharm[120] = (unsigned int  )0;
   sqlstm.sqharc[120] = (unsigned int   *)0;
   sqlstm.sqadto[120] = (unsigned short )0;
   sqlstm.sqtdso[120] = (unsigned short )0;
   sqlstm.sqhstv[121] = (         void  *)ER_NETWORK_ELEMENT_TYPE2;
   sqlstm.sqhstl[121] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[121] = (         int  )sizeof(long);
   sqlstm.sqindv[121] = (         void  *)0;
   sqlstm.sqinds[121] = (         int  )0;
   sqlstm.sqharm[121] = (unsigned int  )0;
   sqlstm.sqharc[121] = (unsigned int   *)0;
   sqlstm.sqadto[121] = (unsigned short )0;
   sqlstm.sqtdso[121] = (unsigned short )0;
   sqlstm.sqhstv[122] = (         void  *)ER_NETWORK_ELEMENT_ID1;
   sqlstm.sqhstl[122] = (unsigned int  )46;
   sqlstm.sqhsts[122] = (         int  )46;
   sqlstm.sqindv[122] = (         void  *)0;
   sqlstm.sqinds[122] = (         int  )0;
   sqlstm.sqharm[122] = (unsigned int  )0;
   sqlstm.sqharc[122] = (unsigned int   *)0;
   sqlstm.sqadto[122] = (unsigned short )0;
   sqlstm.sqtdso[122] = (unsigned short )0;
   sqlstm.sqhstv[123] = (         void  *)ER_NETWORK_ELEMENT_ID2;
   sqlstm.sqhstl[123] = (unsigned int  )46;
   sqlstm.sqhsts[123] = (         int  )46;
   sqlstm.sqindv[123] = (         void  *)0;
   sqlstm.sqinds[123] = (         int  )0;
   sqlstm.sqharm[123] = (unsigned int  )0;
   sqlstm.sqharc[123] = (unsigned int   *)0;
   sqlstm.sqadto[123] = (unsigned short )0;
   sqlstm.sqtdso[123] = (unsigned short )0;
   sqlstm.sqhstv[124] = (         void  *)ER_SGSN_RECORDING_ENTITY_TYPE1;
   sqlstm.sqhstl[124] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[124] = (         int  )sizeof(long);
   sqlstm.sqindv[124] = (         void  *)0;
   sqlstm.sqinds[124] = (         int  )0;
   sqlstm.sqharm[124] = (unsigned int  )0;
   sqlstm.sqharc[124] = (unsigned int   *)0;
   sqlstm.sqadto[124] = (unsigned short )0;
   sqlstm.sqtdso[124] = (unsigned short )0;
   sqlstm.sqhstv[125] = (         void  *)ER_SGSN_RECORDING_ENTITY_TYPE2;
   sqlstm.sqhstl[125] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[125] = (         int  )sizeof(long);
   sqlstm.sqindv[125] = (         void  *)0;
   sqlstm.sqinds[125] = (         int  )0;
   sqlstm.sqharm[125] = (unsigned int  )0;
   sqlstm.sqharc[125] = (unsigned int   *)0;
   sqlstm.sqadto[125] = (unsigned short )0;
   sqlstm.sqtdso[125] = (unsigned short )0;
   sqlstm.sqhstv[126] = (         void  *)ER_IOT_DATE;
   sqlstm.sqhstl[126] = (unsigned int  )15;
   sqlstm.sqhsts[126] = (         int  )15;
   sqlstm.sqindv[126] = (         void  *)0;
   sqlstm.sqinds[126] = (         int  )0;
   sqlstm.sqharm[126] = (unsigned int  )0;
   sqlstm.sqharc[126] = (unsigned int   *)0;
   sqlstm.sqadto[126] = (unsigned short )0;
   sqlstm.sqtdso[126] = (unsigned short )0;
   sqlstm.sqhstv[127] = (         void  *)ER_IOT_CALCULATION;
   sqlstm.sqhstl[127] = (unsigned int  )100;
   sqlstm.sqhsts[127] = (         int  )100;
   sqlstm.sqindv[127] = (         void  *)0;
   sqlstm.sqinds[127] = (         int  )0;
   sqlstm.sqharm[127] = (unsigned int  )0;
   sqlstm.sqharc[127] = (unsigned int   *)0;
   sqlstm.sqadto[127] = (unsigned short )0;
   sqlstm.sqtdso[127] = (unsigned short )0;
   sqlstm.sqhstv[128] = (         void  *)ER_EXP_EXCHANGE_RATE;
   sqlstm.sqhstl[128] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[128] = (         int  )sizeof(double);
   sqlstm.sqindv[128] = (         void  *)0;
   sqlstm.sqinds[128] = (         int  )0;
   sqlstm.sqharm[128] = (unsigned int  )0;
   sqlstm.sqharc[128] = (unsigned int   *)0;
   sqlstm.sqadto[128] = (unsigned short )0;
   sqlstm.sqtdso[128] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}





   if(ERRCODE!=0)
   {
      TRACEENTRY(1,"%s","Error Inserting Bulk Records into PM_RAP_DETAILS table");
      TRACEENTRY(1,"%s -%d- -%d-","ERROR : sqlca.sqlcode sqlca.sqlerrd :",ERRCODE,sqlca.sqlerrd[2]);
      TRACEENTRY(1,"TotalCDRS in the file : -%d-",TotalCDRS);
      CheckBulkInsertRAPError(sqlca.sqlerrd[2]);

      stErrors.ERROR_CODE = sqlca.sqlcode;
      strcpy(stErrors.ERROR_DESC,"Error Inserting Bulk CDRS into PM_RAP_DETAILS table");
      return -1;
   }

   return 0; 
} 

void CheckBulkInsertError(int TotalCDRS)
{
   int i=0;
   int Index=0;


   TRACEENTRY(1,"%s","Checking for Insert Errors");
   for(i=TotalCDRS;i<=TotalCDRS;i++)
   {
      /* EXEC SQL INSERT INTO PM_TAP_CDRS
      (
          FILE_TRANSFER_DIRECTION        ,
          HPLMN_CODE                     ,
          VPLMN_CODE                     ,
          PARTNER_CODE                   ,
          FILE_TYPE_INDICATOR            ,
          FILE_SEQUENCE_NUMBER           ,
          CALL_SEQUENCE                  ,
          CALLS_TYPE_INDICATOR           ,
          CALL_TYPE                      ,
          SERVICE_CODE                   ,
          IMSI                           ,
          MSISDN                         ,
          RAPFILE_SEQUENCE_NUMBER        ,
          CALLED_CALLING_NUMBER          ,
          DIALLED_DIGITS                 ,
          CALLED_PLACE                   ,
          CALLED_REGION                  ,
          CLIR_INDICATOR                 ,
          DESTINATION_NETWORK            ,
          CALL_DATE                      ,
          UTC_OFFSET_CODE                ,
          CALL_DURATION                  ,
          SIM_TOOLKIT_INDICATOR          ,
          RECORDING_ENTITY_CODE          ,
          RECORDING_ENTITY_TYPE          ,
          RECORDING_ENTITY_ID            ,
          CALL_REFERENCE                 ,
          LOCATION_AREA                  ,
          CELLID                         ,
          SERVING_NETWORK                ,
          IMEI                           ,
          BASIC_SERVICE_TYPE             ,
          BASIC_SERVICE_CODE             ,
          TRANSPARENCY_INDICATOR         ,
          FNUR                           ,
          USER_PROTOCOL_INDICATOR        ,
          GUARANTEED_BIT_RATE            ,
          MAXIMUM_BIT_RATE               ,
          HSCSD_INDICATOR               ,
          SUPPLIMENTARY_SERVICE_CODE     ,
          SUPPLIMENTARY_ACTION_CODE      ,
          SUPPLIMENTARY_SERVICE_PARAMS   ,
          THIRD_PARTY_NUMBER             ,
          THIRD_PARTY_CLIR_INDICATOR     ,
          CAMEL_USED_FLAG                ,
          CAMEL_SERVICE_LEVEL            ,
          CAMEL_SERVICE_KEY              ,
          CAMEL_DEFAULT_CALL_HANDLING    ,
          CAMEL_EXCHANGE_RATE_CODE       ,
          HOME_CAMEL_EXCHANGE_RATE       ,
          CAMEL_INVOCATION_FEE           ,
          CAMEL_DISCOUNT_CODE            ,
          CAMEL_DISCOUNT                 ,
          CAMEL_DISCOUNTABLE_AMT         ,
          CAMEL_TAX_INFORMATION_COUNT    ,
          CAMEL_TAX_CODE                 ,
          CAMEL_TAX_VALUE                ,
          CAMEL_TAXABLE_AMOUNT           ,
          CAMEL_DESTINATION_NUMBER       ,
          CALL_TYPE_LEVEL1               ,
          CALL_TYPE_LEVEL2               ,
          CALL_TYPE_LEVEL3               ,
          CHARGE_INFORMATION_COUNT       ,
          CHARGED_ITEM                   ,
          CHARGE_TYPE                    ,
          CHARGEABLE_UNITS               ,
          CHARGED_UNITS                  ,
          CHARGE                         ,
	  CHARGE_TYPE1                   ,
          CHARGEABLE_UNITS1              ,
          CHARGED_UNITS1                 ,
          CHARGE1                        ,
          TAX_INFORMATION_COUNT          ,
          TAX_CODE                       ,
          TAX_VALUE                      ,
          TAXABLE_AMOUNT                 ,
          DISCOUNT_INFORMATION_COUNT     ,
          DISCOUNT_CODE                  ,
          DISCOUNT                       ,
          DISCOUNTABLE_AMT               ,
          HOME_CURNCY_CAMEL_FEE          ,
          HOME_CURNCY_CAMEL_TAX          ,
          HOME_CURNCY_CAMEL_DISCOUNT     ,
          HOME_CURNCY_CHARGE             ,
          HOME_CURNCY_TAX                ,
          HOME_CURNCY_DISCOUNT           ,
          HOME_CURNCY_SURCHARGE          ,
          HOME_CURNCY_CHARGE_WITH_TAX    ,
          HOME_CURNCY_TOTAL_CHARGE       ,
          HOME_EXCHANGE_RATE             ,
          TAP_EXCHANGE_RATE_CODE         ,
          TAP_EXCHANGE_RATE              ,
          TAP_EXCHANGE_RATE_DECIMAL      ,
          TAP_TAX_TYPE_RATE              ,
          NETWORK_ACCESS_IDENTIFER       ,
          PDP_ADDRESS                    ,
          APN_NI                         ,
          APN_OI                         ,
          CAUSE_FOR_TERMINATION          ,
          PARTIAL_TYPE_INDICATOR         ,
          CHARGING_ID                    ,
          SERVING_LOCATION_DESC          ,
          DATA_VOLUME_INCOMING           ,
          DATA_VOLUME_OUTGOING           ,
          SGSN_RECORDING_ENTITY_CODE1    ,
          SGSN_RECORDING_ENTITY_ID1      ,
          SGSN_RECORDING_ENTITY_CODE2    ,
          SGSN_RECORDING_ENTITY_ID2      ,
          SGSN_RECORDING_ENTITY_CODE3    ,
          SGSN_RECORDING_ENTITY_ID3      ,
          CAMEL_APN_NI                   ,
          CAMEL_APN_OI 
      )
      VALUES
      (
        :FILE_TRANSFER_DIRECTION[i]    ,
        :HPLMN_CODE[i]                 ,
        :VPLMN_CODE[i]                 ,
        :PARTNER_CODE[i]               ,
        :FILE_TYPE_INDICATOR[i]        ,
        :FILE_SEQUENCE_NUMBER[i]       ,
        :CALL_SEQUENCE[i]              ,
        :CALLS_TYPE_INDICATOR[i]       ,
        :CALL_TYPE[i]                  ,
        :SERVICE_CODE[i]               ,
        :IMSI[i]                       ,
        :MSISDN[i]                     ,
        :RAPFILE_SEQUENCE_NUMBER[i]    ,
        :CALLED_CALLING_NUMBER[i]      ,
        :DIALLED_DIGITS[i]             ,
         substr(:CALLED_PLACE[i],1,30)   ,
        :CALLED_REGION[i]              ,
        :CLIR_INDICATOR[i]             ,
        :DESTINATION_NETWORK[i]        ,
        to_date(:CALL_DATE[i],'YYYYMMDDHH24MISS') ,
        :UTC_OFFSET_CODE[i]            ,
        :CALL_DURATION[i]              ,
        :SIM_TOOLKIT_INDICATOR[i]      ,
        :RECORDING_ENTITY_CODE[i]      ,
        :RECORDING_ENTITY_TYPE[i]      ,
        :RECORDING_ENTITY_ID[i]        ,
        :CALL_REFERENCE[i]             ,
        :LOCATION_AREA[i]              ,
        :CELLID[i]                     ,
        :SERVING_NETWORK[i]            ,
        :IMEI[i]                       ,
        :BASIC_SERVICE_TYPE[i]         ,
        :BASIC_SERVICE_CODE[i]         ,
        :TRANSPARENCY_INDICATOR[i]     ,
        :FNUR[i]                       ,
        :USER_PROTOCOL_INDICATOR[i]    ,
        :GUARANTEED_BIT_RATE[i]        ,
        :MAXIMUM_BIT_RATE[i]           ,
        :HSCSD_INDICATOR[i]            ,
        :SUPPLIMENTARY_SERVICE_CODE[i] ,
        :SUPPLIMENTARY_ACTION_CODE[i]  ,
        :SUPPLIMENTARY_SERVICE_PARAMS[i] ,
        :THIRD_PARTY_NUMBER[i]         ,
        :THIRD_PARTY_CLIR_INDICATOR[i] ,
        :CAMEL_USED_FLAG[i]            ,
        :CAMEL_SERVICE_LEVEL[i]        ,
        :CAMEL_SERVICE_KEY[i]          ,
        :CAMEL_DEFAULT_CALL_HANDLING[i],
        :CAMEL_EXCHANGE_RATE_CODE[i]   ,
        :HOME_CAMEL_EXCHANGE_RATE[i]   ,
        :CAMEL_INVOCATION_FEE[i]       ,
        :CAMEL_DISCOUNT_CODE[i]        ,
        :CAMEL_DISCOUNT[i]             ,
        :CAMEL_DISCOUNTABLE_AMOUNT[i]  ,
        :CAMEL_TAX_INFORMATION_COUNT[i],
        :CAMEL_TAX_CODE[i]             ,
        :CAMEL_TAX_VALUE[i]            ,
        :CAMEL_TAXABLE_AMOUNT[i]       ,
        :CAMEL_DESTINATION_NUMBER[i]   ,
        :CALL_TYPE_LEVEL1[i]           ,
        :CALL_TYPE_LEVEL2[i]           ,
        :CALL_TYPE_LEVEL3[i]           ,
        :CHARGE_INFORMATION_COUNT[i]   ,
        :CHARGED_ITEM[i]               ,
        :CHARGE_TYPE[i]                ,
        :CHARGEABLE_UNITS[i]           ,
        :CHARGED_UNITS[i]              ,
        :CHARGE[i]                     ,
	:CHARGE_TYPE1[i]               ,
        :CHARGEABLE_UNITS1[i]          ,
        :CHARGED_UNITS1[i]             ,
        :CHARGE1[i]                    ,
        :TAX_INFORMATION_COUNT[i]      ,
        :TAX_CODE[i]                   ,
        :TAX_VALUE[i]                  ,
        :TAXABLE_AMOUNT[i]             ,
        :DISCOUNT_INFORMATION_COUNT[i] ,
        :DISCOUNT_CODE[i]              ,
        :DISCOUNT[i]                   ,
        :DISCOUNTABLE_AMT[i]           ,
        :HOME_CURNCY_CAMEL_FEE[i]      ,
        :HOME_CURNCY_CAMEL_TAX[i]      ,
        :HOME_CURNCY_CAMEL_DISCOUNT[i] ,
        :HOME_CURNCY_CHARGE[i]         ,
        :HOME_CURNCY_TAX[i]            ,
        :HOME_CURNCY_DISCOUNT[i]       ,
        :HOME_CURNCY_SURCHARGE[i]      ,
        :HOME_CURNCY_CHARGE_WITH_TAX[i],
        :HOME_CURNCY_TOTAL_CHARGE[i]   ,
        :HOME_EXCHANGE_RATE[i]         ,
        :TAP_EXCHANGE_RATE_CODE[i]     ,
        :TAP_EXCHANGE_RATE[i]          ,
        :TAP_EXCHANGE_RATE_DECIMAL[i]  ,
        :TAP_TAX_TYPE_RATE[i]          ,
        :NETWORK_ACCESS_IDENTIFER[i]   ,
        :PDP_ADDRESS[i]                ,
        :APN_NI[i]                     ,
        :APN_OI[i]                     ,
        :CAUSE_FOR_TERMINATION[i]      ,
        :PARTIAL_TYPE_INDICATOR[i]     ,
        :CHARGING_ID[i]                ,
        :SERVING_LOCATION_DESC[i]      ,
        :DATA_VOLUME_INCOMING[i]       ,
        :DATA_VOLUME_OUTGOING[i]       ,
        :SGSN_RECORDING_ENTITY_CODE1[i],
        :SGSN_RECORDING_ENTITY_ID1[i]  ,
        :SGSN_RECORDING_ENTITY_CODE2[i],
        :SGSN_RECORDING_ENTITY_ID2[i]  ,
        :SGSN_RECORDING_ENTITY_CODE3[i],
        :SGSN_RECORDING_ENTITY_ID3[i]  ,
        :CAMEL_APN_NI[i]               ,
        :CAMEL_APN_OI[i]
      ); */ 

{
      struct sqlexd sqlstm;
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 129;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlbuft((void **)0, 
        "insert into PM_TAP_CDRS (FILE_TRANSFER_DIRECTION,HPLMN_CODE,VPLMN_C\
ODE,PARTNER_CODE,FILE_TYPE_INDICATOR,FILE_SEQUENCE_NUMBER,CALL_SEQUENCE,CALL\
S_TYPE_INDICATOR,CALL_TYPE,SERVICE_CODE,IMSI,MSISDN,RAPFILE_SEQUENCE_NUMBER,\
CALLED_CALLING_NUMBER,DIALLED_DIGITS,CALLED_PLACE,CALLED_REGION,CLIR_INDICAT\
OR,DESTINATION_NETWORK,CALL_DATE,UTC_OFFSET_CODE,CALL_DURATION,SIM_TOOLKIT_I\
NDICATOR,RECORDING_ENTITY_CODE,RECORDING_ENTITY_TYPE,RECORDING_ENTITY_ID,CAL\
L_REFERENCE,LOCATION_AREA,CELLID,SERVING_NETWORK,IMEI,BASIC_SERVICE_TYPE,BAS\
IC_SERVICE_CODE,TRANSPARENCY_INDICATOR,FNUR,USER_PROTOCOL_INDICATOR,GUARANTE\
ED_BIT_RATE,MAXIMUM_BIT_RATE,HSCSD_INDICATOR,SUPPLIMENTARY_SERVICE_CODE,SUPP\
LIMENTARY_ACTION_CODE,SUPPLIMENTARY_SERVICE_PARAMS,THIRD_PARTY_NUMBER,THIRD_\
PARTY_CLIR_INDICATOR,CAMEL_USED_FLAG,CAMEL_SERVICE_LEVEL,CAMEL_SERVICE_KEY,C\
AMEL_DEFAULT_CALL_HANDLING,CAMEL_EXCHANGE_RATE_CODE,HOME_CAMEL_EXCHANGE_RATE\
,CAMEL_INVOCATION_FEE,CAMEL_DISCOUNT_CODE,CAMEL_DISCOUNT,CAMEL_DISCOUNTABLE_\
AMT,CAMEL_TAX_INFORMATION_COUNT,CAMEL_TAX_COD");
      sqlbuft((void **)0, 
        "E,CAMEL_TAX_VALUE,CAMEL_TAXABLE_AMOUNT,CAMEL_DESTINATION_NUMBER,CAL\
L_TYPE_LEVEL1,CALL_TYPE_LEVEL2,CALL_TYPE_LEVEL3,CHARGE_INFORMATION_COUNT,CHA\
RGED_ITEM,CHARGE_TYPE,CHARGEABLE_UNITS,CHARGED_UNITS,CHARGE,CHARGE_TYPE1,CHA\
RGEABLE_UNITS1,CHARGED_UNITS1,CHARGE1,TAX_INFORMATION_COUNT,TAX_CODE,TAX_VAL\
UE,TAXABLE_AMOUNT,DISCOUNT_INFORMATION_COUNT,DISCOUNT_CODE,DISCOUNT,DISCOUNT\
ABLE_AMT,HOME_CURNCY_CAMEL_FEE,HOME_CURNCY_CAMEL_TAX,HOME_CURNCY_CAMEL_DISCO\
UNT,HOME_CURNCY_CHARGE,HOME_CURNCY_TAX,HOME_CURNCY_DISCOUNT,HOME_CURNCY_SURC\
HARGE,HOME_CURNCY_CHARGE_WITH_TAX,HOME_CURNCY_TOTAL_CHARGE,HOME_EXCHANGE_RAT\
E,TAP_EXCHANGE_RATE_CODE,TAP_EXCHANGE_RATE,TAP_EXCHANGE_RATE_DECIMAL,TAP_TAX\
_TYPE_RATE,NETWORK_ACCESS_IDENTIFER,PDP_ADDRESS,APN_NI,APN_OI,CAUSE_FOR_TERM\
INATION,PARTIAL_TYPE_INDICATOR,CHARGING_ID,SERVING_LOCATION_DESC,DATA_VOLUME\
_INCOMING,DATA_VOLUME_OUTGOING,SGSN_RECORDING_ENTITY_CODE1,SGSN_RECORDING_EN\
TITY_ID1,SGSN_RECORDING_ENTITY_CODE2,SGSN_RECORDING_ENTITY_ID2,SGSN_RECORDIN\
G_ENTITY_CODE3,SGSN_RECORDING_ENTITY_ID3,CAME");
      sqlstm.stmt = "L_APN_NI,CAMEL_APN_OI) values (:b0,:b1,:b2,:b3,:b4,:b5,\
:b6,:b7,:b8,:b9,:b10,:b11,:b12,:b13,:b14,substr(:b15,1,30),:b16,:b17,:b18,to_d\
ate(:b19,'YYYYMMDDHH24MISS'),:b20,:b21,:b22,:b23,:b24,:b25,:b26,:b27,:b28,:b29\
,:b30,:b31,:b32,:b33,:b34,:b35,:b36,:b37,:b38,:b39,:b40,:b41,:b42,:b43,:b44,:b\
45,:b46,:b47,:b48,:b49,:b50,:b51,:b52,:b53,:b54,:b55,:b56,:b57,:b58,:b59,:b60,\
:b61,:b62,:b63,:b64,:b65,:b66,:b67,:b68,:b69,:b70,:b71,:b72,:b73,:b74,:b75,:b7\
6,:b77,:b78,:b79,:b80,:b81,:b82,:b83,:b84,:b85,:b86,:b87,:b88,:b89,:b90,:b91,:\
b92,:b93,:b94,:b95,:b96,:b97,:b98,:b99,:b100,:b101,:b102,:b103,:b104,:b105,:b1\
06,:b107,:b108,:b109,:b110,:b111)";
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )3730;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)4352;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqhstv[0] = (         void  *)FILE_TRANSFER_DIRECTION[i];
      sqlstm.sqhstl[0] = (unsigned int  )2;
      sqlstm.sqhsts[0] = (         int  )0;
      sqlstm.sqindv[0] = (         void  *)0;
      sqlstm.sqinds[0] = (         int  )0;
      sqlstm.sqharm[0] = (unsigned int  )0;
      sqlstm.sqadto[0] = (unsigned short )0;
      sqlstm.sqtdso[0] = (unsigned short )0;
      sqlstm.sqhstv[1] = (         void  *)HPLMN_CODE[i];
      sqlstm.sqhstl[1] = (unsigned int  )6;
      sqlstm.sqhsts[1] = (         int  )0;
      sqlstm.sqindv[1] = (         void  *)0;
      sqlstm.sqinds[1] = (         int  )0;
      sqlstm.sqharm[1] = (unsigned int  )0;
      sqlstm.sqadto[1] = (unsigned short )0;
      sqlstm.sqtdso[1] = (unsigned short )0;
      sqlstm.sqhstv[2] = (         void  *)VPLMN_CODE[i];
      sqlstm.sqhstl[2] = (unsigned int  )6;
      sqlstm.sqhsts[2] = (         int  )0;
      sqlstm.sqindv[2] = (         void  *)0;
      sqlstm.sqinds[2] = (         int  )0;
      sqlstm.sqharm[2] = (unsigned int  )0;
      sqlstm.sqadto[2] = (unsigned short )0;
      sqlstm.sqtdso[2] = (unsigned short )0;
      sqlstm.sqhstv[3] = (         void  *)PARTNER_CODE[i];
      sqlstm.sqhstl[3] = (unsigned int  )4;
      sqlstm.sqhsts[3] = (         int  )0;
      sqlstm.sqindv[3] = (         void  *)0;
      sqlstm.sqinds[3] = (         int  )0;
      sqlstm.sqharm[3] = (unsigned int  )0;
      sqlstm.sqadto[3] = (unsigned short )0;
      sqlstm.sqtdso[3] = (unsigned short )0;
      sqlstm.sqhstv[4] = (         void  *)FILE_TYPE_INDICATOR[i];
      sqlstm.sqhstl[4] = (unsigned int  )2;
      sqlstm.sqhsts[4] = (         int  )0;
      sqlstm.sqindv[4] = (         void  *)0;
      sqlstm.sqinds[4] = (         int  )0;
      sqlstm.sqharm[4] = (unsigned int  )0;
      sqlstm.sqadto[4] = (unsigned short )0;
      sqlstm.sqtdso[4] = (unsigned short )0;
      sqlstm.sqhstv[5] = (         void  *)&FILE_SEQUENCE_NUMBER[i];
      sqlstm.sqhstl[5] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[5] = (         int  )0;
      sqlstm.sqindv[5] = (         void  *)0;
      sqlstm.sqinds[5] = (         int  )0;
      sqlstm.sqharm[5] = (unsigned int  )0;
      sqlstm.sqadto[5] = (unsigned short )0;
      sqlstm.sqtdso[5] = (unsigned short )0;
      sqlstm.sqhstv[6] = (         void  *)&CALL_SEQUENCE[i];
      sqlstm.sqhstl[6] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[6] = (         int  )0;
      sqlstm.sqindv[6] = (         void  *)0;
      sqlstm.sqinds[6] = (         int  )0;
      sqlstm.sqharm[6] = (unsigned int  )0;
      sqlstm.sqadto[6] = (unsigned short )0;
      sqlstm.sqtdso[6] = (unsigned short )0;
      sqlstm.sqhstv[7] = (         void  *)CALLS_TYPE_INDICATOR[i];
      sqlstm.sqhstl[7] = (unsigned int  )2;
      sqlstm.sqhsts[7] = (         int  )0;
      sqlstm.sqindv[7] = (         void  *)0;
      sqlstm.sqinds[7] = (         int  )0;
      sqlstm.sqharm[7] = (unsigned int  )0;
      sqlstm.sqadto[7] = (unsigned short )0;
      sqlstm.sqtdso[7] = (unsigned short )0;
      sqlstm.sqhstv[8] = (         void  *)&CALL_TYPE[i];
      sqlstm.sqhstl[8] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[8] = (         int  )0;
      sqlstm.sqindv[8] = (         void  *)0;
      sqlstm.sqinds[8] = (         int  )0;
      sqlstm.sqharm[8] = (unsigned int  )0;
      sqlstm.sqadto[8] = (unsigned short )0;
      sqlstm.sqtdso[8] = (unsigned short )0;
      sqlstm.sqhstv[9] = (         void  *)SERVICE_CODE[i];
      sqlstm.sqhstl[9] = (unsigned int  )4;
      sqlstm.sqhsts[9] = (         int  )0;
      sqlstm.sqindv[9] = (         void  *)0;
      sqlstm.sqinds[9] = (         int  )0;
      sqlstm.sqharm[9] = (unsigned int  )0;
      sqlstm.sqadto[9] = (unsigned short )0;
      sqlstm.sqtdso[9] = (unsigned short )0;
      sqlstm.sqhstv[10] = (         void  *)&IMSI[i];
      sqlstm.sqhstl[10] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[10] = (         int  )0;
      sqlstm.sqindv[10] = (         void  *)0;
      sqlstm.sqinds[10] = (         int  )0;
      sqlstm.sqharm[10] = (unsigned int  )0;
      sqlstm.sqadto[10] = (unsigned short )0;
      sqlstm.sqtdso[10] = (unsigned short )0;
      sqlstm.sqhstv[11] = (         void  *)MSISDN[i];
      sqlstm.sqhstl[11] = (unsigned int  )26;
      sqlstm.sqhsts[11] = (         int  )0;
      sqlstm.sqindv[11] = (         void  *)0;
      sqlstm.sqinds[11] = (         int  )0;
      sqlstm.sqharm[11] = (unsigned int  )0;
      sqlstm.sqadto[11] = (unsigned short )0;
      sqlstm.sqtdso[11] = (unsigned short )0;
      sqlstm.sqhstv[12] = (         void  *)&RAPFILE_SEQUENCE_NUMBER[i];
      sqlstm.sqhstl[12] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[12] = (         int  )0;
      sqlstm.sqindv[12] = (         void  *)0;
      sqlstm.sqinds[12] = (         int  )0;
      sqlstm.sqharm[12] = (unsigned int  )0;
      sqlstm.sqadto[12] = (unsigned short )0;
      sqlstm.sqtdso[12] = (unsigned short )0;
      sqlstm.sqhstv[13] = (         void  *)CALLED_CALLING_NUMBER[i];
      sqlstm.sqhstl[13] = (unsigned int  )87;
      sqlstm.sqhsts[13] = (         int  )0;
      sqlstm.sqindv[13] = (         void  *)0;
      sqlstm.sqinds[13] = (         int  )0;
      sqlstm.sqharm[13] = (unsigned int  )0;
      sqlstm.sqadto[13] = (unsigned short )0;
      sqlstm.sqtdso[13] = (unsigned short )0;
      sqlstm.sqhstv[14] = (         void  *)DIALLED_DIGITS[i];
      sqlstm.sqhstl[14] = (unsigned int  )87;
      sqlstm.sqhsts[14] = (         int  )0;
      sqlstm.sqindv[14] = (         void  *)0;
      sqlstm.sqinds[14] = (         int  )0;
      sqlstm.sqharm[14] = (unsigned int  )0;
      sqlstm.sqadto[14] = (unsigned short )0;
      sqlstm.sqtdso[14] = (unsigned short )0;
      sqlstm.sqhstv[15] = (         void  *)CALLED_PLACE[i];
      sqlstm.sqhstl[15] = (unsigned int  )46;
      sqlstm.sqhsts[15] = (         int  )0;
      sqlstm.sqindv[15] = (         void  *)0;
      sqlstm.sqinds[15] = (         int  )0;
      sqlstm.sqharm[15] = (unsigned int  )0;
      sqlstm.sqadto[15] = (unsigned short )0;
      sqlstm.sqtdso[15] = (unsigned short )0;
      sqlstm.sqhstv[16] = (         void  *)CALLED_REGION[i];
      sqlstm.sqhstl[16] = (unsigned int  )46;
      sqlstm.sqhsts[16] = (         int  )0;
      sqlstm.sqindv[16] = (         void  *)0;
      sqlstm.sqinds[16] = (         int  )0;
      sqlstm.sqharm[16] = (unsigned int  )0;
      sqlstm.sqadto[16] = (unsigned short )0;
      sqlstm.sqtdso[16] = (unsigned short )0;
      sqlstm.sqhstv[17] = (         void  *)&CLIR_INDICATOR[i];
      sqlstm.sqhstl[17] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[17] = (         int  )0;
      sqlstm.sqindv[17] = (         void  *)0;
      sqlstm.sqinds[17] = (         int  )0;
      sqlstm.sqharm[17] = (unsigned int  )0;
      sqlstm.sqadto[17] = (unsigned short )0;
      sqlstm.sqtdso[17] = (unsigned short )0;
      sqlstm.sqhstv[18] = (         void  *)DESTINATION_NETWORK[i];
      sqlstm.sqhstl[18] = (unsigned int  )7;
      sqlstm.sqhsts[18] = (         int  )0;
      sqlstm.sqindv[18] = (         void  *)0;
      sqlstm.sqinds[18] = (         int  )0;
      sqlstm.sqharm[18] = (unsigned int  )0;
      sqlstm.sqadto[18] = (unsigned short )0;
      sqlstm.sqtdso[18] = (unsigned short )0;
      sqlstm.sqhstv[19] = (         void  *)CALL_DATE[i];
      sqlstm.sqhstl[19] = (unsigned int  )15;
      sqlstm.sqhsts[19] = (         int  )0;
      sqlstm.sqindv[19] = (         void  *)0;
      sqlstm.sqinds[19] = (         int  )0;
      sqlstm.sqharm[19] = (unsigned int  )0;
      sqlstm.sqadto[19] = (unsigned short )0;
      sqlstm.sqtdso[19] = (unsigned short )0;
      sqlstm.sqhstv[20] = (         void  *)UTC_OFFSET_CODE[i];
      sqlstm.sqhstl[20] = (unsigned int  )6;
      sqlstm.sqhsts[20] = (         int  )0;
      sqlstm.sqindv[20] = (         void  *)0;
      sqlstm.sqinds[20] = (         int  )0;
      sqlstm.sqharm[20] = (unsigned int  )0;
      sqlstm.sqadto[20] = (unsigned short )0;
      sqlstm.sqtdso[20] = (unsigned short )0;
      sqlstm.sqhstv[21] = (         void  *)&CALL_DURATION[i];
      sqlstm.sqhstl[21] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[21] = (         int  )0;
      sqlstm.sqindv[21] = (         void  *)0;
      sqlstm.sqinds[21] = (         int  )0;
      sqlstm.sqharm[21] = (unsigned int  )0;
      sqlstm.sqadto[21] = (unsigned short )0;
      sqlstm.sqtdso[21] = (unsigned short )0;
      sqlstm.sqhstv[22] = (         void  *)SIM_TOOLKIT_INDICATOR[i];
      sqlstm.sqhstl[22] = (unsigned int  )2;
      sqlstm.sqhsts[22] = (         int  )0;
      sqlstm.sqindv[22] = (         void  *)0;
      sqlstm.sqinds[22] = (         int  )0;
      sqlstm.sqharm[22] = (unsigned int  )0;
      sqlstm.sqadto[22] = (unsigned short )0;
      sqlstm.sqtdso[22] = (unsigned short )0;
      sqlstm.sqhstv[23] = (         void  *)&RECORDING_ENTITY_CODE[i];
      sqlstm.sqhstl[23] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[23] = (         int  )0;
      sqlstm.sqindv[23] = (         void  *)0;
      sqlstm.sqinds[23] = (         int  )0;
      sqlstm.sqharm[23] = (unsigned int  )0;
      sqlstm.sqadto[23] = (unsigned short )0;
      sqlstm.sqtdso[23] = (unsigned short )0;
      sqlstm.sqhstv[24] = (         void  *)&RECORDING_ENTITY_TYPE[i];
      sqlstm.sqhstl[24] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[24] = (         int  )0;
      sqlstm.sqindv[24] = (         void  *)0;
      sqlstm.sqinds[24] = (         int  )0;
      sqlstm.sqharm[24] = (unsigned int  )0;
      sqlstm.sqadto[24] = (unsigned short )0;
      sqlstm.sqtdso[24] = (unsigned short )0;
      sqlstm.sqhstv[25] = (         void  *)RECORDING_ENTITY_ID[i];
      sqlstm.sqhstl[25] = (unsigned int  )46;
      sqlstm.sqhsts[25] = (         int  )0;
      sqlstm.sqindv[25] = (         void  *)0;
      sqlstm.sqinds[25] = (         int  )0;
      sqlstm.sqharm[25] = (unsigned int  )0;
      sqlstm.sqadto[25] = (unsigned short )0;
      sqlstm.sqtdso[25] = (unsigned short )0;
      sqlstm.sqhstv[26] = (         void  *)CALL_REFERENCE[i];
      sqlstm.sqhstl[26] = (unsigned int  )21;
      sqlstm.sqhsts[26] = (         int  )0;
      sqlstm.sqindv[26] = (         void  *)0;
      sqlstm.sqinds[26] = (         int  )0;
      sqlstm.sqharm[26] = (unsigned int  )0;
      sqlstm.sqadto[26] = (unsigned short )0;
      sqlstm.sqtdso[26] = (unsigned short )0;
      sqlstm.sqhstv[27] = (         void  *)&LOCATION_AREA[i];
      sqlstm.sqhstl[27] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[27] = (         int  )0;
      sqlstm.sqindv[27] = (         void  *)0;
      sqlstm.sqinds[27] = (         int  )0;
      sqlstm.sqharm[27] = (unsigned int  )0;
      sqlstm.sqadto[27] = (unsigned short )0;
      sqlstm.sqtdso[27] = (unsigned short )0;
      sqlstm.sqhstv[28] = (         void  *)&CELLID[i];
      sqlstm.sqhstl[28] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[28] = (         int  )0;
      sqlstm.sqindv[28] = (         void  *)0;
      sqlstm.sqinds[28] = (         int  )0;
      sqlstm.sqharm[28] = (unsigned int  )0;
      sqlstm.sqadto[28] = (unsigned short )0;
      sqlstm.sqtdso[28] = (unsigned short )0;
      sqlstm.sqhstv[29] = (         void  *)SERVING_NETWORK[i];
      sqlstm.sqhstl[29] = (unsigned int  )6;
      sqlstm.sqhsts[29] = (         int  )0;
      sqlstm.sqindv[29] = (         void  *)0;
      sqlstm.sqinds[29] = (         int  )0;
      sqlstm.sqharm[29] = (unsigned int  )0;
      sqlstm.sqadto[29] = (unsigned short )0;
      sqlstm.sqtdso[29] = (unsigned short )0;
      sqlstm.sqhstv[30] = (         void  *)IMEI[i];
      sqlstm.sqhstl[30] = (unsigned int  )21;
      sqlstm.sqhsts[30] = (         int  )0;
      sqlstm.sqindv[30] = (         void  *)0;
      sqlstm.sqinds[30] = (         int  )0;
      sqlstm.sqharm[30] = (unsigned int  )0;
      sqlstm.sqadto[30] = (unsigned short )0;
      sqlstm.sqtdso[30] = (unsigned short )0;
      sqlstm.sqhstv[31] = (         void  *)BASIC_SERVICE_TYPE[i];
      sqlstm.sqhstl[31] = (unsigned int  )2;
      sqlstm.sqhsts[31] = (         int  )0;
      sqlstm.sqindv[31] = (         void  *)0;
      sqlstm.sqinds[31] = (         int  )0;
      sqlstm.sqharm[31] = (unsigned int  )0;
      sqlstm.sqadto[31] = (unsigned short )0;
      sqlstm.sqtdso[31] = (unsigned short )0;
      sqlstm.sqhstv[32] = (         void  *)BASIC_SERVICE_CODE[i];
      sqlstm.sqhstl[32] = (unsigned int  )4;
      sqlstm.sqhsts[32] = (         int  )0;
      sqlstm.sqindv[32] = (         void  *)0;
      sqlstm.sqinds[32] = (         int  )0;
      sqlstm.sqharm[32] = (unsigned int  )0;
      sqlstm.sqadto[32] = (unsigned short )0;
      sqlstm.sqtdso[32] = (unsigned short )0;
      sqlstm.sqhstv[33] = (         void  *)&TRANSPARENCY_INDICATOR[i];
      sqlstm.sqhstl[33] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[33] = (         int  )0;
      sqlstm.sqindv[33] = (         void  *)0;
      sqlstm.sqinds[33] = (         int  )0;
      sqlstm.sqharm[33] = (unsigned int  )0;
      sqlstm.sqadto[33] = (unsigned short )0;
      sqlstm.sqtdso[33] = (unsigned short )0;
      sqlstm.sqhstv[34] = (         void  *)&FNUR[i];
      sqlstm.sqhstl[34] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[34] = (         int  )0;
      sqlstm.sqindv[34] = (         void  *)0;
      sqlstm.sqinds[34] = (         int  )0;
      sqlstm.sqharm[34] = (unsigned int  )0;
      sqlstm.sqadto[34] = (unsigned short )0;
      sqlstm.sqtdso[34] = (unsigned short )0;
      sqlstm.sqhstv[35] = (         void  *)&USER_PROTOCOL_INDICATOR[i];
      sqlstm.sqhstl[35] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[35] = (         int  )0;
      sqlstm.sqindv[35] = (         void  *)0;
      sqlstm.sqinds[35] = (         int  )0;
      sqlstm.sqharm[35] = (unsigned int  )0;
      sqlstm.sqadto[35] = (unsigned short )0;
      sqlstm.sqtdso[35] = (unsigned short )0;
      sqlstm.sqhstv[36] = (         void  *)GUARANTEED_BIT_RATE[i];
      sqlstm.sqhstl[36] = (unsigned int  )6;
      sqlstm.sqhsts[36] = (         int  )0;
      sqlstm.sqindv[36] = (         void  *)0;
      sqlstm.sqinds[36] = (         int  )0;
      sqlstm.sqharm[36] = (unsigned int  )0;
      sqlstm.sqadto[36] = (unsigned short )0;
      sqlstm.sqtdso[36] = (unsigned short )0;
      sqlstm.sqhstv[37] = (         void  *)MAXIMUM_BIT_RATE[i];
      sqlstm.sqhstl[37] = (unsigned int  )6;
      sqlstm.sqhsts[37] = (         int  )0;
      sqlstm.sqindv[37] = (         void  *)0;
      sqlstm.sqinds[37] = (         int  )0;
      sqlstm.sqharm[37] = (unsigned int  )0;
      sqlstm.sqadto[37] = (unsigned short )0;
      sqlstm.sqtdso[37] = (unsigned short )0;
      sqlstm.sqhstv[38] = (         void  *)HSCSD_INDICATOR[i];
      sqlstm.sqhstl[38] = (unsigned int  )4;
      sqlstm.sqhsts[38] = (         int  )0;
      sqlstm.sqindv[38] = (         void  *)0;
      sqlstm.sqinds[38] = (         int  )0;
      sqlstm.sqharm[38] = (unsigned int  )0;
      sqlstm.sqadto[38] = (unsigned short )0;
      sqlstm.sqtdso[38] = (unsigned short )0;
      sqlstm.sqhstv[39] = (         void  *)SUPPLIMENTARY_SERVICE_CODE[i];
      sqlstm.sqhstl[39] = (unsigned int  )21;
      sqlstm.sqhsts[39] = (         int  )0;
      sqlstm.sqindv[39] = (         void  *)0;
      sqlstm.sqinds[39] = (         int  )0;
      sqlstm.sqharm[39] = (unsigned int  )0;
      sqlstm.sqadto[39] = (unsigned short )0;
      sqlstm.sqtdso[39] = (unsigned short )0;
      sqlstm.sqhstv[40] = (         void  *)&SUPPLIMENTARY_ACTION_CODE[i];
      sqlstm.sqhstl[40] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[40] = (         int  )0;
      sqlstm.sqindv[40] = (         void  *)0;
      sqlstm.sqinds[40] = (         int  )0;
      sqlstm.sqharm[40] = (unsigned int  )0;
      sqlstm.sqadto[40] = (unsigned short )0;
      sqlstm.sqtdso[40] = (unsigned short )0;
      sqlstm.sqhstv[41] = (         void  *)SUPPLIMENTARY_SERVICE_PARAMS[i];
      sqlstm.sqhstl[41] = (unsigned int  )46;
      sqlstm.sqhsts[41] = (         int  )0;
      sqlstm.sqindv[41] = (         void  *)0;
      sqlstm.sqinds[41] = (         int  )0;
      sqlstm.sqharm[41] = (unsigned int  )0;
      sqlstm.sqadto[41] = (unsigned short )0;
      sqlstm.sqtdso[41] = (unsigned short )0;
      sqlstm.sqhstv[42] = (         void  *)THIRD_PARTY_NUMBER[i];
      sqlstm.sqhstl[42] = (unsigned int  )87;
      sqlstm.sqhsts[42] = (         int  )0;
      sqlstm.sqindv[42] = (         void  *)0;
      sqlstm.sqinds[42] = (         int  )0;
      sqlstm.sqharm[42] = (unsigned int  )0;
      sqlstm.sqadto[42] = (unsigned short )0;
      sqlstm.sqtdso[42] = (unsigned short )0;
      sqlstm.sqhstv[43] = (         void  *)&THIRD_PARTY_CLIR_INDICATOR[i];
      sqlstm.sqhstl[43] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[43] = (         int  )0;
      sqlstm.sqindv[43] = (         void  *)0;
      sqlstm.sqinds[43] = (         int  )0;
      sqlstm.sqharm[43] = (unsigned int  )0;
      sqlstm.sqadto[43] = (unsigned short )0;
      sqlstm.sqtdso[43] = (unsigned short )0;
      sqlstm.sqhstv[44] = (         void  *)&CAMEL_USED_FLAG[i];
      sqlstm.sqhstl[44] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[44] = (         int  )0;
      sqlstm.sqindv[44] = (         void  *)0;
      sqlstm.sqinds[44] = (         int  )0;
      sqlstm.sqharm[44] = (unsigned int  )0;
      sqlstm.sqadto[44] = (unsigned short )0;
      sqlstm.sqtdso[44] = (unsigned short )0;
      sqlstm.sqhstv[45] = (         void  *)&CAMEL_SERVICE_LEVEL[i];
      sqlstm.sqhstl[45] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[45] = (         int  )0;
      sqlstm.sqindv[45] = (         void  *)0;
      sqlstm.sqinds[45] = (         int  )0;
      sqlstm.sqharm[45] = (unsigned int  )0;
      sqlstm.sqadto[45] = (unsigned short )0;
      sqlstm.sqtdso[45] = (unsigned short )0;
      sqlstm.sqhstv[46] = (         void  *)&CAMEL_SERVICE_KEY[i];
      sqlstm.sqhstl[46] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[46] = (         int  )0;
      sqlstm.sqindv[46] = (         void  *)0;
      sqlstm.sqinds[46] = (         int  )0;
      sqlstm.sqharm[46] = (unsigned int  )0;
      sqlstm.sqadto[46] = (unsigned short )0;
      sqlstm.sqtdso[46] = (unsigned short )0;
      sqlstm.sqhstv[47] = (         void  *)&CAMEL_DEFAULT_CALL_HANDLING[i];
      sqlstm.sqhstl[47] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[47] = (         int  )0;
      sqlstm.sqindv[47] = (         void  *)0;
      sqlstm.sqinds[47] = (         int  )0;
      sqlstm.sqharm[47] = (unsigned int  )0;
      sqlstm.sqadto[47] = (unsigned short )0;
      sqlstm.sqtdso[47] = (unsigned short )0;
      sqlstm.sqhstv[48] = (         void  *)&CAMEL_EXCHANGE_RATE_CODE[i];
      sqlstm.sqhstl[48] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[48] = (         int  )0;
      sqlstm.sqindv[48] = (         void  *)0;
      sqlstm.sqinds[48] = (         int  )0;
      sqlstm.sqharm[48] = (unsigned int  )0;
      sqlstm.sqadto[48] = (unsigned short )0;
      sqlstm.sqtdso[48] = (unsigned short )0;
      sqlstm.sqhstv[49] = (         void  *)&HOME_CAMEL_EXCHANGE_RATE[i];
      sqlstm.sqhstl[49] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[49] = (         int  )0;
      sqlstm.sqindv[49] = (         void  *)0;
      sqlstm.sqinds[49] = (         int  )0;
      sqlstm.sqharm[49] = (unsigned int  )0;
      sqlstm.sqadto[49] = (unsigned short )0;
      sqlstm.sqtdso[49] = (unsigned short )0;
      sqlstm.sqhstv[50] = (         void  *)&CAMEL_INVOCATION_FEE[i];
      sqlstm.sqhstl[50] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[50] = (         int  )0;
      sqlstm.sqindv[50] = (         void  *)0;
      sqlstm.sqinds[50] = (         int  )0;
      sqlstm.sqharm[50] = (unsigned int  )0;
      sqlstm.sqadto[50] = (unsigned short )0;
      sqlstm.sqtdso[50] = (unsigned short )0;
      sqlstm.sqhstv[51] = (         void  *)&CAMEL_DISCOUNT_CODE[i];
      sqlstm.sqhstl[51] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[51] = (         int  )0;
      sqlstm.sqindv[51] = (         void  *)0;
      sqlstm.sqinds[51] = (         int  )0;
      sqlstm.sqharm[51] = (unsigned int  )0;
      sqlstm.sqadto[51] = (unsigned short )0;
      sqlstm.sqtdso[51] = (unsigned short )0;
      sqlstm.sqhstv[52] = (         void  *)&CAMEL_DISCOUNT[i];
      sqlstm.sqhstl[52] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[52] = (         int  )0;
      sqlstm.sqindv[52] = (         void  *)0;
      sqlstm.sqinds[52] = (         int  )0;
      sqlstm.sqharm[52] = (unsigned int  )0;
      sqlstm.sqadto[52] = (unsigned short )0;
      sqlstm.sqtdso[52] = (unsigned short )0;
      sqlstm.sqhstv[53] = (         void  *)&CAMEL_DISCOUNTABLE_AMOUNT[i];
      sqlstm.sqhstl[53] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[53] = (         int  )0;
      sqlstm.sqindv[53] = (         void  *)0;
      sqlstm.sqinds[53] = (         int  )0;
      sqlstm.sqharm[53] = (unsigned int  )0;
      sqlstm.sqadto[53] = (unsigned short )0;
      sqlstm.sqtdso[53] = (unsigned short )0;
      sqlstm.sqhstv[54] = (         void  *)&CAMEL_TAX_INFORMATION_COUNT[i];
      sqlstm.sqhstl[54] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[54] = (         int  )0;
      sqlstm.sqindv[54] = (         void  *)0;
      sqlstm.sqinds[54] = (         int  )0;
      sqlstm.sqharm[54] = (unsigned int  )0;
      sqlstm.sqadto[54] = (unsigned short )0;
      sqlstm.sqtdso[54] = (unsigned short )0;
      sqlstm.sqhstv[55] = (         void  *)&CAMEL_TAX_CODE[i];
      sqlstm.sqhstl[55] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[55] = (         int  )0;
      sqlstm.sqindv[55] = (         void  *)0;
      sqlstm.sqinds[55] = (         int  )0;
      sqlstm.sqharm[55] = (unsigned int  )0;
      sqlstm.sqadto[55] = (unsigned short )0;
      sqlstm.sqtdso[55] = (unsigned short )0;
      sqlstm.sqhstv[56] = (         void  *)&CAMEL_TAX_VALUE[i];
      sqlstm.sqhstl[56] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[56] = (         int  )0;
      sqlstm.sqindv[56] = (         void  *)0;
      sqlstm.sqinds[56] = (         int  )0;
      sqlstm.sqharm[56] = (unsigned int  )0;
      sqlstm.sqadto[56] = (unsigned short )0;
      sqlstm.sqtdso[56] = (unsigned short )0;
      sqlstm.sqhstv[57] = (         void  *)&CAMEL_TAXABLE_AMOUNT[i];
      sqlstm.sqhstl[57] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[57] = (         int  )0;
      sqlstm.sqindv[57] = (         void  *)0;
      sqlstm.sqinds[57] = (         int  )0;
      sqlstm.sqharm[57] = (unsigned int  )0;
      sqlstm.sqadto[57] = (unsigned short )0;
      sqlstm.sqtdso[57] = (unsigned short )0;
      sqlstm.sqhstv[58] = (         void  *)CAMEL_DESTINATION_NUMBER[i];
      sqlstm.sqhstl[58] = (unsigned int  )87;
      sqlstm.sqhsts[58] = (         int  )0;
      sqlstm.sqindv[58] = (         void  *)0;
      sqlstm.sqinds[58] = (         int  )0;
      sqlstm.sqharm[58] = (unsigned int  )0;
      sqlstm.sqadto[58] = (unsigned short )0;
      sqlstm.sqtdso[58] = (unsigned short )0;
      sqlstm.sqhstv[59] = (         void  *)&CALL_TYPE_LEVEL1[i];
      sqlstm.sqhstl[59] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[59] = (         int  )0;
      sqlstm.sqindv[59] = (         void  *)0;
      sqlstm.sqinds[59] = (         int  )0;
      sqlstm.sqharm[59] = (unsigned int  )0;
      sqlstm.sqadto[59] = (unsigned short )0;
      sqlstm.sqtdso[59] = (unsigned short )0;
      sqlstm.sqhstv[60] = (         void  *)&CALL_TYPE_LEVEL2[i];
      sqlstm.sqhstl[60] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[60] = (         int  )0;
      sqlstm.sqindv[60] = (         void  *)0;
      sqlstm.sqinds[60] = (         int  )0;
      sqlstm.sqharm[60] = (unsigned int  )0;
      sqlstm.sqadto[60] = (unsigned short )0;
      sqlstm.sqtdso[60] = (unsigned short )0;
      sqlstm.sqhstv[61] = (         void  *)&CALL_TYPE_LEVEL3[i];
      sqlstm.sqhstl[61] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[61] = (         int  )0;
      sqlstm.sqindv[61] = (         void  *)0;
      sqlstm.sqinds[61] = (         int  )0;
      sqlstm.sqharm[61] = (unsigned int  )0;
      sqlstm.sqadto[61] = (unsigned short )0;
      sqlstm.sqtdso[61] = (unsigned short )0;
      sqlstm.sqhstv[62] = (         void  *)&CHARGE_INFORMATION_COUNT[i];
      sqlstm.sqhstl[62] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[62] = (         int  )0;
      sqlstm.sqindv[62] = (         void  *)0;
      sqlstm.sqinds[62] = (         int  )0;
      sqlstm.sqharm[62] = (unsigned int  )0;
      sqlstm.sqadto[62] = (unsigned short )0;
      sqlstm.sqtdso[62] = (unsigned short )0;
      sqlstm.sqhstv[63] = (         void  *)CHARGED_ITEM[i];
      sqlstm.sqhstl[63] = (unsigned int  )4;
      sqlstm.sqhsts[63] = (         int  )0;
      sqlstm.sqindv[63] = (         void  *)0;
      sqlstm.sqinds[63] = (         int  )0;
      sqlstm.sqharm[63] = (unsigned int  )0;
      sqlstm.sqadto[63] = (unsigned short )0;
      sqlstm.sqtdso[63] = (unsigned short )0;
      sqlstm.sqhstv[64] = (         void  *)CHARGE_TYPE[i];
      sqlstm.sqhstl[64] = (unsigned int  )4;
      sqlstm.sqhsts[64] = (         int  )0;
      sqlstm.sqindv[64] = (         void  *)0;
      sqlstm.sqinds[64] = (         int  )0;
      sqlstm.sqharm[64] = (unsigned int  )0;
      sqlstm.sqadto[64] = (unsigned short )0;
      sqlstm.sqtdso[64] = (unsigned short )0;
      sqlstm.sqhstv[65] = (         void  *)&CHARGEABLE_UNITS[i];
      sqlstm.sqhstl[65] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[65] = (         int  )0;
      sqlstm.sqindv[65] = (         void  *)0;
      sqlstm.sqinds[65] = (         int  )0;
      sqlstm.sqharm[65] = (unsigned int  )0;
      sqlstm.sqadto[65] = (unsigned short )0;
      sqlstm.sqtdso[65] = (unsigned short )0;
      sqlstm.sqhstv[66] = (         void  *)&CHARGED_UNITS[i];
      sqlstm.sqhstl[66] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[66] = (         int  )0;
      sqlstm.sqindv[66] = (         void  *)0;
      sqlstm.sqinds[66] = (         int  )0;
      sqlstm.sqharm[66] = (unsigned int  )0;
      sqlstm.sqadto[66] = (unsigned short )0;
      sqlstm.sqtdso[66] = (unsigned short )0;
      sqlstm.sqhstv[67] = (         void  *)&CHARGE[i];
      sqlstm.sqhstl[67] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[67] = (         int  )0;
      sqlstm.sqindv[67] = (         void  *)0;
      sqlstm.sqinds[67] = (         int  )0;
      sqlstm.sqharm[67] = (unsigned int  )0;
      sqlstm.sqadto[67] = (unsigned short )0;
      sqlstm.sqtdso[67] = (unsigned short )0;
      sqlstm.sqhstv[68] = (         void  *)CHARGE_TYPE1[i];
      sqlstm.sqhstl[68] = (unsigned int  )4;
      sqlstm.sqhsts[68] = (         int  )0;
      sqlstm.sqindv[68] = (         void  *)0;
      sqlstm.sqinds[68] = (         int  )0;
      sqlstm.sqharm[68] = (unsigned int  )0;
      sqlstm.sqadto[68] = (unsigned short )0;
      sqlstm.sqtdso[68] = (unsigned short )0;
      sqlstm.sqhstv[69] = (         void  *)&CHARGEABLE_UNITS1[i];
      sqlstm.sqhstl[69] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[69] = (         int  )0;
      sqlstm.sqindv[69] = (         void  *)0;
      sqlstm.sqinds[69] = (         int  )0;
      sqlstm.sqharm[69] = (unsigned int  )0;
      sqlstm.sqadto[69] = (unsigned short )0;
      sqlstm.sqtdso[69] = (unsigned short )0;
      sqlstm.sqhstv[70] = (         void  *)&CHARGED_UNITS1[i];
      sqlstm.sqhstl[70] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[70] = (         int  )0;
      sqlstm.sqindv[70] = (         void  *)0;
      sqlstm.sqinds[70] = (         int  )0;
      sqlstm.sqharm[70] = (unsigned int  )0;
      sqlstm.sqadto[70] = (unsigned short )0;
      sqlstm.sqtdso[70] = (unsigned short )0;
      sqlstm.sqhstv[71] = (         void  *)&CHARGE1[i];
      sqlstm.sqhstl[71] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[71] = (         int  )0;
      sqlstm.sqindv[71] = (         void  *)0;
      sqlstm.sqinds[71] = (         int  )0;
      sqlstm.sqharm[71] = (unsigned int  )0;
      sqlstm.sqadto[71] = (unsigned short )0;
      sqlstm.sqtdso[71] = (unsigned short )0;
      sqlstm.sqhstv[72] = (         void  *)&TAX_INFORMATION_COUNT[i];
      sqlstm.sqhstl[72] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[72] = (         int  )0;
      sqlstm.sqindv[72] = (         void  *)0;
      sqlstm.sqinds[72] = (         int  )0;
      sqlstm.sqharm[72] = (unsigned int  )0;
      sqlstm.sqadto[72] = (unsigned short )0;
      sqlstm.sqtdso[72] = (unsigned short )0;
      sqlstm.sqhstv[73] = (         void  *)&TAX_CODE[i];
      sqlstm.sqhstl[73] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[73] = (         int  )0;
      sqlstm.sqindv[73] = (         void  *)0;
      sqlstm.sqinds[73] = (         int  )0;
      sqlstm.sqharm[73] = (unsigned int  )0;
      sqlstm.sqadto[73] = (unsigned short )0;
      sqlstm.sqtdso[73] = (unsigned short )0;
      sqlstm.sqhstv[74] = (         void  *)&TAX_VALUE[i];
      sqlstm.sqhstl[74] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[74] = (         int  )0;
      sqlstm.sqindv[74] = (         void  *)0;
      sqlstm.sqinds[74] = (         int  )0;
      sqlstm.sqharm[74] = (unsigned int  )0;
      sqlstm.sqadto[74] = (unsigned short )0;
      sqlstm.sqtdso[74] = (unsigned short )0;
      sqlstm.sqhstv[75] = (         void  *)&TAXABLE_AMOUNT[i];
      sqlstm.sqhstl[75] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[75] = (         int  )0;
      sqlstm.sqindv[75] = (         void  *)0;
      sqlstm.sqinds[75] = (         int  )0;
      sqlstm.sqharm[75] = (unsigned int  )0;
      sqlstm.sqadto[75] = (unsigned short )0;
      sqlstm.sqtdso[75] = (unsigned short )0;
      sqlstm.sqhstv[76] = (         void  *)&DISCOUNT_INFORMATION_COUNT[i];
      sqlstm.sqhstl[76] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[76] = (         int  )0;
      sqlstm.sqindv[76] = (         void  *)0;
      sqlstm.sqinds[76] = (         int  )0;
      sqlstm.sqharm[76] = (unsigned int  )0;
      sqlstm.sqadto[76] = (unsigned short )0;
      sqlstm.sqtdso[76] = (unsigned short )0;
      sqlstm.sqhstv[77] = (         void  *)&DISCOUNT_CODE[i];
      sqlstm.sqhstl[77] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[77] = (         int  )0;
      sqlstm.sqindv[77] = (         void  *)0;
      sqlstm.sqinds[77] = (         int  )0;
      sqlstm.sqharm[77] = (unsigned int  )0;
      sqlstm.sqadto[77] = (unsigned short )0;
      sqlstm.sqtdso[77] = (unsigned short )0;
      sqlstm.sqhstv[78] = (         void  *)&DISCOUNT[i];
      sqlstm.sqhstl[78] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[78] = (         int  )0;
      sqlstm.sqindv[78] = (         void  *)0;
      sqlstm.sqinds[78] = (         int  )0;
      sqlstm.sqharm[78] = (unsigned int  )0;
      sqlstm.sqadto[78] = (unsigned short )0;
      sqlstm.sqtdso[78] = (unsigned short )0;
      sqlstm.sqhstv[79] = (         void  *)&DISCOUNTABLE_AMT[i];
      sqlstm.sqhstl[79] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[79] = (         int  )0;
      sqlstm.sqindv[79] = (         void  *)0;
      sqlstm.sqinds[79] = (         int  )0;
      sqlstm.sqharm[79] = (unsigned int  )0;
      sqlstm.sqadto[79] = (unsigned short )0;
      sqlstm.sqtdso[79] = (unsigned short )0;
      sqlstm.sqhstv[80] = (         void  *)&HOME_CURNCY_CAMEL_FEE[i];
      sqlstm.sqhstl[80] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[80] = (         int  )0;
      sqlstm.sqindv[80] = (         void  *)0;
      sqlstm.sqinds[80] = (         int  )0;
      sqlstm.sqharm[80] = (unsigned int  )0;
      sqlstm.sqadto[80] = (unsigned short )0;
      sqlstm.sqtdso[80] = (unsigned short )0;
      sqlstm.sqhstv[81] = (         void  *)&HOME_CURNCY_CAMEL_TAX[i];
      sqlstm.sqhstl[81] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[81] = (         int  )0;
      sqlstm.sqindv[81] = (         void  *)0;
      sqlstm.sqinds[81] = (         int  )0;
      sqlstm.sqharm[81] = (unsigned int  )0;
      sqlstm.sqadto[81] = (unsigned short )0;
      sqlstm.sqtdso[81] = (unsigned short )0;
      sqlstm.sqhstv[82] = (         void  *)&HOME_CURNCY_CAMEL_DISCOUNT[i];
      sqlstm.sqhstl[82] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[82] = (         int  )0;
      sqlstm.sqindv[82] = (         void  *)0;
      sqlstm.sqinds[82] = (         int  )0;
      sqlstm.sqharm[82] = (unsigned int  )0;
      sqlstm.sqadto[82] = (unsigned short )0;
      sqlstm.sqtdso[82] = (unsigned short )0;
      sqlstm.sqhstv[83] = (         void  *)&HOME_CURNCY_CHARGE[i];
      sqlstm.sqhstl[83] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[83] = (         int  )0;
      sqlstm.sqindv[83] = (         void  *)0;
      sqlstm.sqinds[83] = (         int  )0;
      sqlstm.sqharm[83] = (unsigned int  )0;
      sqlstm.sqadto[83] = (unsigned short )0;
      sqlstm.sqtdso[83] = (unsigned short )0;
      sqlstm.sqhstv[84] = (         void  *)&HOME_CURNCY_TAX[i];
      sqlstm.sqhstl[84] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[84] = (         int  )0;
      sqlstm.sqindv[84] = (         void  *)0;
      sqlstm.sqinds[84] = (         int  )0;
      sqlstm.sqharm[84] = (unsigned int  )0;
      sqlstm.sqadto[84] = (unsigned short )0;
      sqlstm.sqtdso[84] = (unsigned short )0;
      sqlstm.sqhstv[85] = (         void  *)&HOME_CURNCY_DISCOUNT[i];
      sqlstm.sqhstl[85] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[85] = (         int  )0;
      sqlstm.sqindv[85] = (         void  *)0;
      sqlstm.sqinds[85] = (         int  )0;
      sqlstm.sqharm[85] = (unsigned int  )0;
      sqlstm.sqadto[85] = (unsigned short )0;
      sqlstm.sqtdso[85] = (unsigned short )0;
      sqlstm.sqhstv[86] = (         void  *)&HOME_CURNCY_SURCHARGE[i];
      sqlstm.sqhstl[86] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[86] = (         int  )0;
      sqlstm.sqindv[86] = (         void  *)0;
      sqlstm.sqinds[86] = (         int  )0;
      sqlstm.sqharm[86] = (unsigned int  )0;
      sqlstm.sqadto[86] = (unsigned short )0;
      sqlstm.sqtdso[86] = (unsigned short )0;
      sqlstm.sqhstv[87] = (         void  *)&HOME_CURNCY_CHARGE_WITH_TAX[i];
      sqlstm.sqhstl[87] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[87] = (         int  )0;
      sqlstm.sqindv[87] = (         void  *)0;
      sqlstm.sqinds[87] = (         int  )0;
      sqlstm.sqharm[87] = (unsigned int  )0;
      sqlstm.sqadto[87] = (unsigned short )0;
      sqlstm.sqtdso[87] = (unsigned short )0;
      sqlstm.sqhstv[88] = (         void  *)&HOME_CURNCY_TOTAL_CHARGE[i];
      sqlstm.sqhstl[88] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[88] = (         int  )0;
      sqlstm.sqindv[88] = (         void  *)0;
      sqlstm.sqinds[88] = (         int  )0;
      sqlstm.sqharm[88] = (unsigned int  )0;
      sqlstm.sqadto[88] = (unsigned short )0;
      sqlstm.sqtdso[88] = (unsigned short )0;
      sqlstm.sqhstv[89] = (         void  *)&HOME_EXCHANGE_RATE[i];
      sqlstm.sqhstl[89] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[89] = (         int  )0;
      sqlstm.sqindv[89] = (         void  *)0;
      sqlstm.sqinds[89] = (         int  )0;
      sqlstm.sqharm[89] = (unsigned int  )0;
      sqlstm.sqadto[89] = (unsigned short )0;
      sqlstm.sqtdso[89] = (unsigned short )0;
      sqlstm.sqhstv[90] = (         void  *)&TAP_EXCHANGE_RATE_CODE[i];
      sqlstm.sqhstl[90] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[90] = (         int  )0;
      sqlstm.sqindv[90] = (         void  *)0;
      sqlstm.sqinds[90] = (         int  )0;
      sqlstm.sqharm[90] = (unsigned int  )0;
      sqlstm.sqadto[90] = (unsigned short )0;
      sqlstm.sqtdso[90] = (unsigned short )0;
      sqlstm.sqhstv[91] = (         void  *)&TAP_EXCHANGE_RATE[i];
      sqlstm.sqhstl[91] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[91] = (         int  )0;
      sqlstm.sqindv[91] = (         void  *)0;
      sqlstm.sqinds[91] = (         int  )0;
      sqlstm.sqharm[91] = (unsigned int  )0;
      sqlstm.sqadto[91] = (unsigned short )0;
      sqlstm.sqtdso[91] = (unsigned short )0;
      sqlstm.sqhstv[92] = (         void  *)&TAP_EXCHANGE_RATE_DECIMAL[i];
      sqlstm.sqhstl[92] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[92] = (         int  )0;
      sqlstm.sqindv[92] = (         void  *)0;
      sqlstm.sqinds[92] = (         int  )0;
      sqlstm.sqharm[92] = (unsigned int  )0;
      sqlstm.sqadto[92] = (unsigned short )0;
      sqlstm.sqtdso[92] = (unsigned short )0;
      sqlstm.sqhstv[93] = (         void  *)TAP_TAX_TYPE_RATE[i];
      sqlstm.sqhstl[93] = (unsigned int  )601;
      sqlstm.sqhsts[93] = (         int  )0;
      sqlstm.sqindv[93] = (         void  *)0;
      sqlstm.sqinds[93] = (         int  )0;
      sqlstm.sqharm[93] = (unsigned int  )0;
      sqlstm.sqadto[93] = (unsigned short )0;
      sqlstm.sqtdso[93] = (unsigned short )0;
      sqlstm.sqhstv[94] = (         void  *)NETWORK_ACCESS_IDENTIFER[i];
      sqlstm.sqhstl[94] = (unsigned int  )31;
      sqlstm.sqhsts[94] = (         int  )0;
      sqlstm.sqindv[94] = (         void  *)0;
      sqlstm.sqinds[94] = (         int  )0;
      sqlstm.sqharm[94] = (unsigned int  )0;
      sqlstm.sqadto[94] = (unsigned short )0;
      sqlstm.sqtdso[94] = (unsigned short )0;
      sqlstm.sqhstv[95] = (         void  *)PDP_ADDRESS[i];
      sqlstm.sqhstl[95] = (unsigned int  )46;
      sqlstm.sqhsts[95] = (         int  )0;
      sqlstm.sqindv[95] = (         void  *)0;
      sqlstm.sqinds[95] = (         int  )0;
      sqlstm.sqharm[95] = (unsigned int  )0;
      sqlstm.sqadto[95] = (unsigned short )0;
      sqlstm.sqtdso[95] = (unsigned short )0;
      sqlstm.sqhstv[96] = (         void  *)APN_NI[i];
      sqlstm.sqhstl[96] = (unsigned int  )66;
      sqlstm.sqhsts[96] = (         int  )0;
      sqlstm.sqindv[96] = (         void  *)0;
      sqlstm.sqinds[96] = (         int  )0;
      sqlstm.sqharm[96] = (unsigned int  )0;
      sqlstm.sqadto[96] = (unsigned short )0;
      sqlstm.sqtdso[96] = (unsigned short )0;
      sqlstm.sqhstv[97] = (         void  *)APN_OI[i];
      sqlstm.sqhstl[97] = (unsigned int  )66;
      sqlstm.sqhsts[97] = (         int  )0;
      sqlstm.sqindv[97] = (         void  *)0;
      sqlstm.sqinds[97] = (         int  )0;
      sqlstm.sqharm[97] = (unsigned int  )0;
      sqlstm.sqadto[97] = (unsigned short )0;
      sqlstm.sqtdso[97] = (unsigned short )0;
      sqlstm.sqhstv[98] = (         void  *)&CAUSE_FOR_TERMINATION[i];
      sqlstm.sqhstl[98] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[98] = (         int  )0;
      sqlstm.sqindv[98] = (         void  *)0;
      sqlstm.sqinds[98] = (         int  )0;
      sqlstm.sqharm[98] = (unsigned int  )0;
      sqlstm.sqadto[98] = (unsigned short )0;
      sqlstm.sqtdso[98] = (unsigned short )0;
      sqlstm.sqhstv[99] = (         void  *)PARTIAL_TYPE_INDICATOR[i];
      sqlstm.sqhstl[99] = (unsigned int  )2;
      sqlstm.sqhsts[99] = (         int  )0;
      sqlstm.sqindv[99] = (         void  *)0;
      sqlstm.sqinds[99] = (         int  )0;
      sqlstm.sqharm[99] = (unsigned int  )0;
      sqlstm.sqadto[99] = (unsigned short )0;
      sqlstm.sqtdso[99] = (unsigned short )0;
      sqlstm.sqhstv[100] = (         void  *)&CHARGING_ID[i];
      sqlstm.sqhstl[100] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[100] = (         int  )0;
      sqlstm.sqindv[100] = (         void  *)0;
      sqlstm.sqinds[100] = (         int  )0;
      sqlstm.sqharm[100] = (unsigned int  )0;
      sqlstm.sqadto[100] = (unsigned short )0;
      sqlstm.sqtdso[100] = (unsigned short )0;
      sqlstm.sqhstv[101] = (         void  *)SERVING_LOCATION_DESC[i];
      sqlstm.sqhstl[101] = (unsigned int  )46;
      sqlstm.sqhsts[101] = (         int  )0;
      sqlstm.sqindv[101] = (         void  *)0;
      sqlstm.sqinds[101] = (         int  )0;
      sqlstm.sqharm[101] = (unsigned int  )0;
      sqlstm.sqadto[101] = (unsigned short )0;
      sqlstm.sqtdso[101] = (unsigned short )0;
      sqlstm.sqhstv[102] = (         void  *)&DATA_VOLUME_INCOMING[i];
      sqlstm.sqhstl[102] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[102] = (         int  )0;
      sqlstm.sqindv[102] = (         void  *)0;
      sqlstm.sqinds[102] = (         int  )0;
      sqlstm.sqharm[102] = (unsigned int  )0;
      sqlstm.sqadto[102] = (unsigned short )0;
      sqlstm.sqtdso[102] = (unsigned short )0;
      sqlstm.sqhstv[103] = (         void  *)&DATA_VOLUME_OUTGOING[i];
      sqlstm.sqhstl[103] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[103] = (         int  )0;
      sqlstm.sqindv[103] = (         void  *)0;
      sqlstm.sqinds[103] = (         int  )0;
      sqlstm.sqharm[103] = (unsigned int  )0;
      sqlstm.sqadto[103] = (unsigned short )0;
      sqlstm.sqtdso[103] = (unsigned short )0;
      sqlstm.sqhstv[104] = (         void  *)&SGSN_RECORDING_ENTITY_CODE1[i];
      sqlstm.sqhstl[104] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[104] = (         int  )0;
      sqlstm.sqindv[104] = (         void  *)0;
      sqlstm.sqinds[104] = (         int  )0;
      sqlstm.sqharm[104] = (unsigned int  )0;
      sqlstm.sqadto[104] = (unsigned short )0;
      sqlstm.sqtdso[104] = (unsigned short )0;
      sqlstm.sqhstv[105] = (         void  *)SGSN_RECORDING_ENTITY_ID1[i];
      sqlstm.sqhstl[105] = (unsigned int  )46;
      sqlstm.sqhsts[105] = (         int  )0;
      sqlstm.sqindv[105] = (         void  *)0;
      sqlstm.sqinds[105] = (         int  )0;
      sqlstm.sqharm[105] = (unsigned int  )0;
      sqlstm.sqadto[105] = (unsigned short )0;
      sqlstm.sqtdso[105] = (unsigned short )0;
      sqlstm.sqhstv[106] = (         void  *)&SGSN_RECORDING_ENTITY_CODE2[i];
      sqlstm.sqhstl[106] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[106] = (         int  )0;
      sqlstm.sqindv[106] = (         void  *)0;
      sqlstm.sqinds[106] = (         int  )0;
      sqlstm.sqharm[106] = (unsigned int  )0;
      sqlstm.sqadto[106] = (unsigned short )0;
      sqlstm.sqtdso[106] = (unsigned short )0;
      sqlstm.sqhstv[107] = (         void  *)SGSN_RECORDING_ENTITY_ID2[i];
      sqlstm.sqhstl[107] = (unsigned int  )46;
      sqlstm.sqhsts[107] = (         int  )0;
      sqlstm.sqindv[107] = (         void  *)0;
      sqlstm.sqinds[107] = (         int  )0;
      sqlstm.sqharm[107] = (unsigned int  )0;
      sqlstm.sqadto[107] = (unsigned short )0;
      sqlstm.sqtdso[107] = (unsigned short )0;
      sqlstm.sqhstv[108] = (         void  *)&SGSN_RECORDING_ENTITY_CODE3[i];
      sqlstm.sqhstl[108] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[108] = (         int  )0;
      sqlstm.sqindv[108] = (         void  *)0;
      sqlstm.sqinds[108] = (         int  )0;
      sqlstm.sqharm[108] = (unsigned int  )0;
      sqlstm.sqadto[108] = (unsigned short )0;
      sqlstm.sqtdso[108] = (unsigned short )0;
      sqlstm.sqhstv[109] = (         void  *)SGSN_RECORDING_ENTITY_ID3[i];
      sqlstm.sqhstl[109] = (unsigned int  )46;
      sqlstm.sqhsts[109] = (         int  )0;
      sqlstm.sqindv[109] = (         void  *)0;
      sqlstm.sqinds[109] = (         int  )0;
      sqlstm.sqharm[109] = (unsigned int  )0;
      sqlstm.sqadto[109] = (unsigned short )0;
      sqlstm.sqtdso[109] = (unsigned short )0;
      sqlstm.sqhstv[110] = (         void  *)CAMEL_APN_NI[i];
      sqlstm.sqhstl[110] = (unsigned int  )66;
      sqlstm.sqhsts[110] = (         int  )0;
      sqlstm.sqindv[110] = (         void  *)0;
      sqlstm.sqinds[110] = (         int  )0;
      sqlstm.sqharm[110] = (unsigned int  )0;
      sqlstm.sqadto[110] = (unsigned short )0;
      sqlstm.sqtdso[110] = (unsigned short )0;
      sqlstm.sqhstv[111] = (         void  *)CAMEL_APN_OI[i];
      sqlstm.sqhstl[111] = (unsigned int  )66;
      sqlstm.sqhsts[111] = (         int  )0;
      sqlstm.sqindv[111] = (         void  *)0;
      sqlstm.sqinds[111] = (         int  )0;
      sqlstm.sqharm[111] = (unsigned int  )0;
      sqlstm.sqadto[111] = (unsigned short )0;
      sqlstm.sqtdso[111] = (unsigned short )0;
      sqlstm.sqphsv = sqlstm.sqhstv;
      sqlstm.sqphsl = sqlstm.sqhstl;
      sqlstm.sqphss = sqlstm.sqhsts;
      sqlstm.sqpind = sqlstm.sqindv;
      sqlstm.sqpins = sqlstm.sqinds;
      sqlstm.sqparm = sqlstm.sqharm;
      sqlstm.sqparc = sqlstm.sqharc;
      sqlstm.sqpadto = sqlstm.sqadto;
      sqlstm.sqptdso = sqlstm.sqtdso;
      sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



     

      if(ERRCODE!=0)
      {
         /* EXEC SQL ROLLBACK; */ 

{
         struct sqlexd sqlstm;
         sqlstm.sqlvsn = 12;
         sqlstm.arrsiz = 129;
         sqlstm.sqladtp = &sqladt;
         sqlstm.sqltdsp = &sqltds;
         sqlstm.iters = (unsigned int  )1;
         sqlstm.offset = (unsigned int  )4193;
         sqlstm.cud = sqlcud0;
         sqlstm.sqlest = (unsigned char  *)&sqlca;
         sqlstm.sqlety = (unsigned short)4352;
         sqlstm.occurs = (unsigned int  )0;
         sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


         TRACEENTRY(1,"%s","Error Inserting the below Record into PM_TAP_CDRS table");
         TRACEENTRY(1,"%s -%d-","ERROR : sqlca.sqlcode :",ERRCODE);

         Index = i+1;

         TRACEENTRY(1,"%s","String Values Below ------------------");
         TRACEENTRY(1,"FILE_TRANSFER_DIRECTION         : -%d- -%s-",Index,FILE_TRANSFER_DIRECTION[i]);
         TRACEENTRY(1,"SERVICE_CODE                    : -%d- -%s-",Index,SERVICE_CODE[i]);
         TRACEENTRY(1,"HPLMN_CODE                      : -%d- -%s-",Index,HPLMN_CODE[i]);
         TRACEENTRY(1,"VPLMN_CODE                      : -%d- -%s-",Index,VPLMN_CODE[i]);
         TRACEENTRY(1,"PARTNER_CODE                    : -%d- -%s-",Index,PARTNER_CODE[i]);
         TRACEENTRY(1,"FILE_TYPE_INDICATOR             : -%d- -%s-",Index,FILE_TYPE_INDICATOR[i]);
         TRACEENTRY(1,"CALLS_TYPE_INDICATOR            : -%d- -%s-",Index,CALLS_TYPE_INDICATOR[i]);
         TRACEENTRY(1,"MSISDN                          : -%d- -%s-",Index,MSISDN[i]);
         TRACEENTRY(1,"CALLED_CALLING_NUMBER           : -%d- -%s-",Index,CALLED_CALLING_NUMBER[i]);
         TRACEENTRY(1,"DIALLED_DIGITS                  : -%d- -%s-",Index,DIALLED_DIGITS[i]);
         TRACEENTRY(1,"CALLED_PLACE                    : -%d- -%s-",Index,CALLED_PLACE[i]);
         TRACEENTRY(1,"CALLED_REGION                   : -%d- -%s-",Index,CALLED_REGION[i]);
         TRACEENTRY(1,"DESTINATION_NETWORK             : -%d- -%s-",Index,DESTINATION_NETWORK[i]);
         TRACEENTRY(1,"CALL_DATE                       : -%d- -%s-",Index,CALL_DATE[i]);
         TRACEENTRY(1,"UTC_OFFSET_CODE                 : -%d- -%s-",Index,UTC_OFFSET_CODE[i]);
         TRACEENTRY(1,"SIM_TOOLKIT_INDICATOR           : -%d- -%s-",Index,SIM_TOOLKIT_INDICATOR[i]);
         TRACEENTRY(1,"RECORDING_ENTITY_ID             : -%d- -%s-",Index,RECORDING_ENTITY_ID[i]);
         TRACEENTRY(1,"CALL_REFERENCE                  : -%d- -%s-",Index,CALL_REFERENCE[i]);
         TRACEENTRY(1,"SERVING_NETWORK                 : -%d- -%s-",Index,SERVING_NETWORK[i]);
         TRACEENTRY(1,"IMEI                            : -%d- -%s-",Index,IMEI[i]);
         TRACEENTRY(1,"BASIC_SERVICE_TYPE              : -%d- -%s-",Index,BASIC_SERVICE_TYPE[i]);
         TRACEENTRY(1,"BASIC_SERVICE_CODE              : -%d- -%s-",Index,BASIC_SERVICE_CODE[i]);
         TRACEENTRY(1,"GUARANTEED_BIT_RATE             : -%d- -%s-",Index,GUARANTEED_BIT_RATE[i]);
         TRACEENTRY(1,"MAXIMUM_BIT_RATE                : -%d- -%s-",Index,MAXIMUM_BIT_RATE[i]);
         TRACEENTRY(1,"HSCSD_INDICATOR                 : -%d- -%s-",Index,HSCSD_INDICATOR[i]);
         TRACEENTRY(1,"SUPPLIMENTARY_SERVICE_CODE      : -%d- -%s-",Index,SUPPLIMENTARY_SERVICE_CODE[i]);
         TRACEENTRY(1,"SUPPLIMENTARY_SERVICE_PARAMS    : -%d- -%s-",Index,SUPPLIMENTARY_SERVICE_PARAMS[i]);
         TRACEENTRY(1,"THIRD_PARTY_NUMBER              : -%d- -%s-",Index,THIRD_PARTY_NUMBER[i]);
         TRACEENTRY(1,"CAMEL_DESTINATION_NUMBER        : -%d- -%s-",Index,CAMEL_DESTINATION_NUMBER[i]);
         TRACEENTRY(1,"CHARGED_ITEM                    : -%d- -%s-",Index,CHARGED_ITEM[i]);
         TRACEENTRY(1,"CHARGE_TYPE                     : -%d- -%s-",Index,CHARGE_TYPE[i]);
         TRACEENTRY(1,"PDP_ADDRESS                     : -%d- -%s-",Index,PDP_ADDRESS[i]);
         TRACEENTRY(1,"APN_NI                          : -%d- -%s-",Index,APN_NI[i]);
         TRACEENTRY(1,"APN_OI                          : -%d- -%s-",Index,APN_OI[i]);

         TRACEENTRY(1,"%s","Number Values Below ------------------");
         TRACEENTRY(1,"FILE_SEQUENCE_NUMBER            : -%d- -%d-",Index,FILE_SEQUENCE_NUMBER[i]);
         TRACEENTRY(1,"CALL_SEQUENCE                   : -%d- -%f-",Index,CALL_SEQUENCE[i]);
         TRACEENTRY(1,"CALL_TYPE                       : -%d- -%d-",Index,CALL_TYPE[i]);
         TRACEENTRY(1,"IMSI                            : -%d- -%f-",Index,IMSI[i]);
         TRACEENTRY(1,"RAPFILE_SEQUENCE_NUMBER         : -%d- -%d-",Index,RAPFILE_SEQUENCE_NUMBER[i]);
         TRACEENTRY(1,"CLIR_INDICATOR                  : -%d- -%d-",Index,CLIR_INDICATOR[i]);
         TRACEENTRY(1,"CALL_DURATION                   : -%d- -%f-",Index,CALL_DURATION[i]);
         TRACEENTRY(1,"RECORDING_ENTITY_CODE           : -%d- -%d-",Index,RECORDING_ENTITY_CODE[i]);
         TRACEENTRY(1,"RECORDING_ENTITY_TYPE           : -%d- -%d-",Index,RECORDING_ENTITY_TYPE[i]);
         TRACEENTRY(1,"LOCATION_AREA                   : -%d- -%f-",Index,LOCATION_AREA[i]);
         TRACEENTRY(1,"CELLID                          : -%d- -%f-",Index,CELLID[i]);
         TRACEENTRY(1,"TRANSPARENCY_INDICATOR          : -%d- -%d-",Index,TRANSPARENCY_INDICATOR[i]);
         TRACEENTRY(1,"FNUR                            : -%d- -%f-",Index,FNUR[i]);
         TRACEENTRY(1,"USER_PROTOCOL_INDICATOR         : -%d- -%f-",Index,USER_PROTOCOL_INDICATOR[i]);
         TRACEENTRY(1,"SUPPLIMENTARY_ACTION_CODE       : -%d- -%d-",Index,SUPPLIMENTARY_ACTION_CODE[i]);
         TRACEENTRY(1,"THIRD_PARTY_CLIR_INDICATOR      : -%d- -%d-",Index,THIRD_PARTY_CLIR_INDICATOR[i]);
         TRACEENTRY(1,"CAMEL_USED_FLAG                 : -%d- -%d-",Index,CAMEL_USED_FLAG[i]);
         TRACEENTRY(1,"CAMEL_SERVICE_LEVEL             : -%d- -%f-",Index,CAMEL_SERVICE_LEVEL[i]);
         TRACEENTRY(1,"CAMEL_SERVICE_KEY               : -%d- -%f-",Index,CAMEL_SERVICE_KEY[i]);
         TRACEENTRY(1,"CAMEL_DEFAULT_CALL_HANDLING     : -%d- -%f-",Index,CAMEL_DEFAULT_CALL_HANDLING[i]);
         TRACEENTRY(1,"CAMEL_EXCHANGE_RATE_CODE        : -%d- -%d-",Index,CAMEL_EXCHANGE_RATE_CODE[i]);
         TRACEENTRY(1,"HOME_CAMEL_EXCHANGE_RATE        : -%d- -%f-",Index,HOME_CAMEL_EXCHANGE_RATE[i]);
         TRACEENTRY(1,"CAMEL_INVOCATION_FEE            : -%d- -%f-",Index,CAMEL_INVOCATION_FEE[i]);
         TRACEENTRY(1,"CAMEL_DISCOUNT_CODE             : -%d- -%d-",Index,CAMEL_DISCOUNT_CODE[i]);
         TRACEENTRY(1,"CAMEL_DISCOUNT                  : -%d- -%f-",Index,CAMEL_DISCOUNT[i]);
         TRACEENTRY(1,"CAMEL_DISCOUNTABLE_AMOUNT       : -%d- -%f-",Index,CAMEL_DISCOUNTABLE_AMOUNT[i]);
         TRACEENTRY(1,"CAMEL_TAX_INFORMATION_COUNT     : -%d- -%d-",Index,CAMEL_TAX_INFORMATION_COUNT[i]);
         TRACEENTRY(1,"CAMEL_TAX_CODE                  : -%d- -%d-",Index,CAMEL_TAX_CODE[i]);
         TRACEENTRY(1,"CAMEL_TAX_VALUE                 : -%d- -%f-",Index,CAMEL_TAX_VALUE[i]);
         TRACEENTRY(1,"CAMEL_TAXABLE_AMOUNT            : -%d- -%f-",Index,CAMEL_TAXABLE_AMOUNT[i]);
         TRACEENTRY(1,"CALL_TYPE_LEVEL1                : -%d- -%d-",Index,CALL_TYPE_LEVEL1[i]);
         TRACEENTRY(1,"CALL_TYPE_LEVEL2                : -%d- -%d-",Index,CALL_TYPE_LEVEL2[i]);
         TRACEENTRY(1,"CALL_TYPE_LEVEL3                : -%d- -%d-",Index,CALL_TYPE_LEVEL3[i]);
         TRACEENTRY(1,"CHARGE_INFORMATION_COUNT        : -%d- -%d-",Index,CHARGE_INFORMATION_COUNT[i]);
         TRACEENTRY(1,"CHARGEABLE_UNITS                : -%d- -%f-",Index,CHARGEABLE_UNITS[i]);
         TRACEENTRY(1,"CHARGED_UNITS                   : -%d- -%f-",Index,CHARGED_UNITS[i]);
         TRACEENTRY(1,"CHARGE                          : -%d- -%f-",Index,CHARGE[i]);
         TRACEENTRY(1,"TAX_INFORMATION_COUNT           : -%d- -%d-",Index,TAX_INFORMATION_COUNT[i]);
         TRACEENTRY(1,"TAX_CODE                        : -%d- -%d-",Index,TAX_CODE[i]);
         TRACEENTRY(1,"TAX_VALUE                       : -%d- -%f-",Index,TAX_VALUE[i]);
         TRACEENTRY(1,"TAXABLE_AMOUNT                  : -%d- -%f-",Index,TAXABLE_AMOUNT[i]);
         TRACEENTRY(1,"DISCOUNT_INFORMATION_COUNT      : -%d- -%d-",Index,DISCOUNT_INFORMATION_COUNT[i]);
         TRACEENTRY(1,"DISCOUNT_CODE                   : -%d- -%d-",Index,DISCOUNT_CODE[i]);
         TRACEENTRY(1,"DISCOUNT                        : -%d- -%f-",Index,DISCOUNT[i]);
         TRACEENTRY(1,"DISCOUNTABLE_AMT                : -%d- -%f-",Index,DISCOUNTABLE_AMT[i]);
         TRACEENTRY(1,"HOME_CURNCY_CAMEL_FEE           : -%d- -%f-",Index,HOME_CURNCY_CAMEL_FEE[i]);
         TRACEENTRY(1,"HOME_CURNCY_CAMEL_TAX           : -%d- -%f-",Index,HOME_CURNCY_CAMEL_TAX[i]);
         TRACEENTRY(1,"HOME_CURNCY_CAMEL_DISCOUNT      : -%d- -%f-",Index,HOME_CURNCY_CAMEL_DISCOUNT[i]);
         TRACEENTRY(1,"HOME_CURNCY_CHARGE              : -%d- -%f-",Index,HOME_CURNCY_CHARGE[i]);
         TRACEENTRY(1,"HOME_CURNCY_TAX                 : -%d- -%f-",Index,HOME_CURNCY_TAX[i]);
         TRACEENTRY(1,"HOME_CURNCY_DISCOUNT            : -%d- -%f-",Index,HOME_CURNCY_DISCOUNT[i]);
         TRACEENTRY(1,"HOME_CURNCY_SURCHARGE           : -%d- -%f-",Index,HOME_CURNCY_SURCHARGE[i]);
         TRACEENTRY(1,"HOME_CURNCY_CHARGE_WITH_TAX     : -%d- -%f-",Index,HOME_CURNCY_CHARGE_WITH_TAX[i]);
         TRACEENTRY(1,"HOME_CURNCY_TOTAL_CHARGE        : -%d- -%f-",Index,HOME_CURNCY_TOTAL_CHARGE[i]);
         TRACEENTRY(1,"HOME_EXCHANGE_RATE              : -%d- -%f-",Index,HOME_EXCHANGE_RATE[i]);
         TRACEENTRY(1,"TAP_EXCHANGE_RATE_CODE          : -%d- -%d-",Index,TAP_EXCHANGE_RATE_CODE[i]);
         TRACEENTRY(1,"TAP_EXCHANGE_RATE               : -%d- -%f-",Index,TAP_EXCHANGE_RATE[i]);
         TRACEENTRY(1,"TAP_EXCHANGE_RATE_DECIMAL       : -%d- -%d-",Index,TAP_EXCHANGE_RATE_DECIMAL[i]);
         TRACEENTRY(1,"TAP_TAX_TYPE_RATE               : -%d- -%s-",Index,TAP_TAX_TYPE_RATE[i]);
         break;
      }
   }
}


void CheckBulkInsertRAPError(int TotalErrors)
{

   int i=0 ;
   int Index=0;


   TRACEENTRY(1,"%s","Checking for Insert Errors");
   for(i=TotalErrors;i<=TotalErrors;i++)
   {
      /* EXEC SQL INSERT INTO PM_RAP_DETAILS 
      (
          FILE_TRANSFER_DIRECTION         ,
          HPLMN_CODE                      ,
          VPLMN_CODE                      ,
          PARTNER_CODE                    ,
          FILE_TYPE_INDICATOR             ,
          FILE_SEQUENCE_NUMBER            ,
          RAP_SEQUENCE_NUMBER             ,
          CALL_SEQUENCE                   ,
          ERROR_SEQUENCE                  ,
          CALLS_TYPE_INDICATOR            ,
          CALL_TYPE                       ,
          SERVICE_CODE                    ,
          IMSI                            ,
          MSISDN                          ,
          CALLED_CALLING_NUMBER           ,
          DIALLED_DIGITS                  ,
          CLIR_INDICATOR                  ,
          DESTINATION_NETWORK             ,
          CALL_DATE                       ,
          UTC_OFFSET_CODE                 ,
          UTC_OFFSET                      ,
          CALL_DURATION                   ,
          SIM_TOOLKIT_INDICATOR           ,
          RECORDING_ENTITY_CODE           ,
          RECORDING_ENTITY_TYPE           ,
          RECORDING_ENTITY_ID             ,
          CALL_REFERENCE                  ,
          CELLID                          ,
          SERVING_NETWORK                 ,
          IMEI                            ,
          BASIC_SERVICE_TYPE              ,
          BASIC_SERVICE_CODE              ,
          TRANSPARENCY_INDICATOR          ,
          FNUR                            ,
          USER_PROTOCOL_INDICATOR         ,
          GUARANTEED_BIT_RATE             ,
          MAXIMUM_BIT_RATE                ,
          HSCSD_INDICATOR                 ,
          SUPPLIMENTARY_SERVICE_CODE      ,
          SUPPLIMENTARY_ACTION_CODE       ,
          SUPPLIMENTARY_SERVICE_PARAMS    ,
          THIRD_PARTY_NUMBER              ,
          THIRD_PARTY_CLIR_INDICATOR      ,
          CAMEL_USED_FLAG                 ,
          CAMEL_SERVICE_LEVEL             ,
          CAMEL_SERVICE_KEY               ,
          CAMEL_DEFAULT_CALL_HANDLING     ,
          CAMEL_EXCHANGE_RATE_CODE        ,
          CAMEL_INVOCATION_FEE            ,
          CAMEL_DISCOUNT_CODE             ,
          CAMEL_DISCOUNT                  ,
          CAMEL_DISCOUNTABLE_AMT          ,
          CAMEL_TAX_INFORMATION_COUNT     ,
          CAMEL_TAX_CODE                  ,
          CAMEL_TAX_VALUE                 ,
          CAMEL_TAXABLE_AMOUNT            ,
          CAMEL_DESTINATION_NUMBER        ,
          CALL_TYPE_LEVEL1                ,
          CALL_TYPE_LEVEL2                ,
          CALL_TYPE_LEVEL3                ,
          CHARGE_INFORMATION_COUNT        ,
          CHARGED_ITEM                    ,
          CHARGE_TYPE                     ,
          CHARGEABLE_UNITS                ,
          CHARGED_UNITS                   ,
          CHARGE                          ,
          TAX_INFORMATION_COUNT           ,
          TAX_CODE                        ,
          TAX_VALUE                       ,
          TAXABLE_AMOUNT                  ,
          DISCOUNT_INFORMATION_COUNT      ,
          DISCOUNT_CODE                   ,
          DISCOUNT                        ,
          DISCOUNTABLE_AMT                ,
          TAP_EXCHANGE_RATE_CODE          ,
          TAP_EXCHANGE_RATE               ,
          TAP_EXCHANGE_RATE_DECIMAL       ,
          TAP_TAX_TYPE_RATE               ,
          NETWORK_ACCESS_IDENTIFER        ,
          PDP_ADDRESS                     ,
          APN_NI                          ,
          APN_OI                          ,
          CAUSE_FOR_TERMINATION           ,
          PARTIAL_TYPE_INDICATOR          ,
          CHARGING_ID                     ,
          DATA_VOLUME_INCOMING            ,
          DATA_VOLUME_OUTGOING            ,
          SGSN_RECORDING_ENTITY_CODE1     ,
          SGSN_RECORDING_ENTITY_ID1       ,
          SGSN_RECORDING_ENTITY_CODE2     ,
          SGSN_RECORDING_ENTITY_ID2       ,
          SGSN_RECORDING_ENTITY_CODE3     ,
          SGSN_RECORDING_ENTITY_ID3       ,
          CAMEL_APN_NI                    ,
          CAMEL_APN_OI                    ,
          FILE_CREATION_TIME              ,
          FILE_TRANSFER_TIME              ,
          FILE_AVAILABLE_TIME             ,
          CHARGING_TIME_STAMP             ,
          LOCAL_CURRENCY_CODE             ,
          TAP_CURRENCY_CODE               ,
          TAP_DECIMAL_PLACES              ,
          TARIFF_ID                       ,
          ERROR_CODE                      ,
          ERROR_TYPE                      ,
          ERROR_CONTEXT_DETAILS           ,
          APPLICATION_TAG                 ,
          CONTEXT_NAME                    ,
          DATA_TYPE_INDICATOR             ,
          ERROR_FIELD_NAME                ,
          ERROR_MESSAGE                   ,
          ERROR_VALUE                     ,
          ERROR_NODE                      ,
          RAP_STATUS
      )
      VALUES
      (
       :ER_FILE_TRANSFER_DIRECTION[i]       ,
       :ER_HPLMN_CODE[i]                    ,
       :ER_VPLMN_CODE[i]                    ,
       :ER_PARTNER_CODE[i]                  ,
       :ER_FILE_TYPE_INDICATOR[i]           ,
       :ER_FILE_SEQUENCE_NUMBER[i]          ,
       :ER_RAP_SEQUENCE_NUMBER[i]           ,
       :ER_CALL_SEQUENCE[i]                 ,
       :ER_ERROR_SEQUENCE[i]                ,
       :ER_CALLS_TYPE_INDICATOR[i]          ,
       :ER_CALL_TYPE[i]                     ,
       :ER_SERVICE_CODE[i]                  ,
       :ER_IMSI[i]                          ,
       :ER_MSISDN[i]                        ,
       :ER_CALLED_CALLING_NUMBER[i]         ,
       :ER_DIALLED_DIGITS[i]                ,
       :ER_CLIR_INDICATOR[i]                ,
       :ER_DESTINATION_NETWORK[i]           ,
       :ER_CALL_DATE[i]                     ,
       :ER_UTC_OFFSET_CODE[i]               ,
       :ER_UTC_OFFSET[i]                    ,
       :ER_CALL_DURATION[i]                 ,
       :ER_SIM_TOOLKIT_INDICATOR[i]         ,
       :ER_RECORDING_ENTITY_CODE[i]         ,
       :ER_RECORDING_ENTITY_TYPE[i]         ,
       :ER_RECORDING_ENTITY_ID[i]           ,
       :ER_CALL_REFERENCE[i]                ,
       :ER_CELLID[i]                        ,
       :ER_SERVING_NETWORK[i]               ,
       :ER_IMEI[i]                          ,
       :ER_BASIC_SERVICE_TYPE[i]            ,
       :ER_BASIC_SERVICE_CODE[i]            ,
       :ER_TRANSPARENCY_INDICATOR[i]        ,
       :ER_FNUR[i]                          ,
       :ER_USER_PROTOCOL_INDICATOR[i]       ,
       :ER_GUARANTEED_BIT_RATE[i]           ,
       :ER_MAXIMUM_BIT_RATE[i]              ,
       :ER_HSCSD_INDICATOR[i]               ,
       :ER_SUPPLIMENTARY_SERVICE_CODE[i]    ,
       :ER_SUPPLIMENTARY_ACTION_CODE[i]     ,
       :ER_SUPPLIMENTARY_SERVICE_PARAMS[i]  ,
       :ER_THIRD_PARTY_NUMBER[i]            ,
       :ER_THIRD_PARTY_CLIR_INDICATOR[i]    ,
       :ER_CAMEL_USED_FLAG[i]               ,
       :ER_CAMEL_SERVICE_LEVEL[i]           ,
       :ER_CAMEL_SERVICE_KEY[i]             ,
       :ER_CAMEL_DEFAULT_CALL_HANDLING[i]   ,
       :ER_CAMEL_EXCHANGE_RATE_CODE[i]      ,
       :ER_CAMEL_INVOCATION_FEE[i]          ,
       :ER_CAMEL_DISCOUNT_CODE[i]           ,
       :ER_CAMEL_DISCOUNT[i]                ,
       :ER_CAMEL_DISCOUNTABLE_AMT[i]        ,
       :ER_CAMEL_TAX_INFORMATION_COUNT[i]   ,
       :ER_CAMEL_TAX_CODE[i]                ,
       :ER_CAMEL_TAX_VALUE[i]               ,
       :ER_CAMEL_TAXABLE_AMOUNT[i]          ,
       :ER_CAMEL_DESTINATION_NUMBER[i]      ,
       :ER_CALL_TYPE_LEVEL1[i]              ,
       :ER_CALL_TYPE_LEVEL2[i]              ,
       :ER_CALL_TYPE_LEVEL3[i]              ,
       :ER_CHARGE_INFORMATION_COUNT[i]      ,
       :ER_CHARGED_ITEM[i]                  ,
       :ER_CHARGE_TYPE[i]                   ,
       :ER_CHARGEABLE_UNITS[i]              ,
       :ER_CHARGED_UNITS[i]                 ,
       :ER_CHARGE[i]                        ,
       :ER_TAX_INFORMATION_COUNT[i]         ,
       :ER_TAX_CODE[i]                      ,
       :ER_TAX_VALUE[i]                     ,
       :ER_TAXABLE_AMOUNT[i]                ,
       :ER_DISCOUNT_INFORMATION_COUNT[i]    ,
       :ER_DISCOUNT_CODE[i]                 ,
       :ER_DISCOUNT[i]                      ,
       :ER_DISCOUNTABLE_AMT[i]              ,
       :ER_TAP_EXCHANGE_RATE_CODE[i]        ,
       :ER_TAP_EXCHANGE_RATE[i]             ,
       :ER_TAP_EXCHANGE_RATE_DECIMAL[i]     ,
       :ER_TAP_TAX_TYPE_RATE[i]             ,
       :ER_NETWORK_ACCESS_IDENTIFER[i]      ,
       :ER_PDP_ADDRESS[i]                   ,
       :ER_APN_NI[i]                        ,
       :ER_APN_OI[i]                        ,
       :ER_CAUSE_FOR_TERMINATION[i]         ,
       :ER_PARTIAL_TYPE_INDICATOR[i]        ,
       :ER_CHARGING_ID[i]                   ,
       :ER_DATA_VOLUME_INCOMING[i]          ,
       :ER_DATA_VOLUME_OUTGOING[i]          ,
       :ER_SGSN_RECORDING_ENTITY_CODE1[i]   ,
       :ER_SGSN_RECORDING_ENTITY_ID1[i]     ,
       :ER_SGSN_RECORDING_ENTITY_CODE2[i]   ,
       :ER_SGSN_RECORDING_ENTITY_ID2[i]     ,
       :ER_SGSN_RECORDING_ENTITY_CODE3[i]   ,
       :ER_SGSN_RECORDING_ENTITY_ID3[i]     ,
       :ER_CAMEL_APN_NI[i]                  ,
       :ER_CAMEL_APN_OI[i]                  ,
       :ER_FILE_CREATION_TIME[i]            ,
       :ER_FILE_TRANSFER_TIME[i]            ,
       :ER_FILE_AVAILABLE_TIME[i]           ,
       :ER_CHARGING_TIME_STAMP[i]           ,
       :ER_LOCAL_CURRENCY_CODE[i]           ,
       :ER_TAP_CURRENCY_CODE[i]             ,
       :ER_TAP_DECIMAL_PLACES[i]            ,
       :ER_TARIFF_ID[i]                     ,
       :ER_ERROR_CODE[i]                    ,
       :ER_ERROR_TYPE[i]                    ,
       :ER_ERROR_CONTEXT_DETAILS[i]         ,
       :ER_APPLICATION_TAG[i]               ,
       :ER_CONTEXT_NAME[i]                  ,
       :ER_DATA_TYPE_INDICATOR[i]           ,
       :ER_ERROR_FIELD_NAME[i]              ,
       :ER_ERROR_MESSAGE[i]                 ,
       :ER_ERROR_VALUE[i]                   ,
       :ER_ERROR_NODE[i]                    ,
       :ER_RAP_STATUS[i]       
      ); */ 

{
      struct sqlexd sqlstm;
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 129;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlbuft((void **)0, 
        "insert into PM_RAP_DETAILS (FILE_TRANSFER_DIRECTION,HPLMN_CODE,VPLM\
N_CODE,PARTNER_CODE,FILE_TYPE_INDICATOR,FILE_SEQUENCE_NUMBER,RAP_SEQUENCE_NU\
MBER,CALL_SEQUENCE,ERROR_SEQUENCE,CALLS_TYPE_INDICATOR,CALL_TYPE,SERVICE_COD\
E,IMSI,MSISDN,CALLED_CALLING_NUMBER,DIALLED_DIGITS,CLIR_INDICATOR,DESTINATIO\
N_NETWORK,CALL_DATE,UTC_OFFSET_CODE,UTC_OFFSET,CALL_DURATION,SIM_TOOLKIT_IND\
ICATOR,RECORDING_ENTITY_CODE,RECORDING_ENTITY_TYPE,RECORDING_ENTITY_ID,CALL_\
REFERENCE,CELLID,SERVING_NETWORK,IMEI,BASIC_SERVICE_TYPE,BASIC_SERVICE_CODE,\
TRANSPARENCY_INDICATOR,FNUR,USER_PROTOCOL_INDICATOR,GUARANTEED_BIT_RATE,MAXI\
MUM_BIT_RATE,HSCSD_INDICATOR,SUPPLIMENTARY_SERVICE_CODE,SUPPLIMENTARY_ACTION\
_CODE,SUPPLIMENTARY_SERVICE_PARAMS,THIRD_PARTY_NUMBER,THIRD_PARTY_CLIR_INDIC\
ATOR,CAMEL_USED_FLAG,CAMEL_SERVICE_LEVEL,CAMEL_SERVICE_KEY,CAMEL_DEFAULT_CAL\
L_HANDLING,CAMEL_EXCHANGE_RATE_CODE,CAMEL_INVOCATION_FEE,CAMEL_DISCOUNT_CODE\
,CAMEL_DISCOUNT,CAMEL_DISCOUNTABLE_AMT,CAMEL_TAX_INFORMATION_COUNT,CAMEL_TAX\
_CODE,CAMEL_TAX_VALUE,CAMEL_TAXABLE_AMOUNT,CA");
      sqlbuft((void **)0, 
        "MEL_DESTINATION_NUMBER,CALL_TYPE_LEVEL1,CALL_TYPE_LEVEL2,CALL_TYPE_\
LEVEL3,CHARGE_INFORMATION_COUNT,CHARGED_ITEM,CHARGE_TYPE,CHARGEABLE_UNITS,CH\
ARGED_UNITS,CHARGE,TAX_INFORMATION_COUNT,TAX_CODE,TAX_VALUE,TAXABLE_AMOUNT,D\
ISCOUNT_INFORMATION_COUNT,DISCOUNT_CODE,DISCOUNT,DISCOUNTABLE_AMT,TAP_EXCHAN\
GE_RATE_CODE,TAP_EXCHANGE_RATE,TAP_EXCHANGE_RATE_DECIMAL,TAP_TAX_TYPE_RATE,N\
ETWORK_ACCESS_IDENTIFER,PDP_ADDRESS,APN_NI,APN_OI,CAUSE_FOR_TERMINATION,PART\
IAL_TYPE_INDICATOR,CHARGING_ID,DATA_VOLUME_INCOMING,DATA_VOLUME_OUTGOING,SGS\
N_RECORDING_ENTITY_CODE1,SGSN_RECORDING_ENTITY_ID1,SGSN_RECORDING_ENTITY_COD\
E2,SGSN_RECORDING_ENTITY_ID2,SGSN_RECORDING_ENTITY_CODE3,SGSN_RECORDING_ENTI\
TY_ID3,CAMEL_APN_NI,CAMEL_APN_OI,FILE_CREATION_TIME,FILE_TRANSFER_TIME,FILE_\
AVAILABLE_TIME,CHARGING_TIME_STAMP,LOCAL_CURRENCY_CODE,TAP_CURRENCY_CODE,TAP\
_DECIMAL_PLACES,TARIFF_ID,ERROR_CODE,ERROR_TYPE,ERROR_CONTEXT_DETAILS,APPLIC\
ATION_TAG,CONTEXT_NAME,DATA_TYPE_INDICATOR,ERROR_FIELD_NAME,ERROR_MESSAGE,ER\
ROR_VALUE,ERROR_NODE,RAP_STATUS) values (:b0,");
      sqlstm.stmt = ":b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b11,:b12,:b13\
,:b14,:b15,:b16,:b17,:b18,:b19,:b20,:b21,:b22,:b23,:b24,:b25,:b26,:b27,:b28,:b\
29,:b30,:b31,:b32,:b33,:b34,:b35,:b36,:b37,:b38,:b39,:b40,:b41,:b42,:b43,:b44,\
:b45,:b46,:b47,:b48,:b49,:b50,:b51,:b52,:b53,:b54,:b55,:b56,:b57,:b58,:b59,:b6\
0,:b61,:b62,:b63,:b64,:b65,:b66,:b67,:b68,:b69,:b70,:b71,:b72,:b73,:b74,:b75,:\
b76,:b77,:b78,:b79,:b80,:b81,:b82,:b83,:b84,:b85,:b86,:b87,:b88,:b89,:b90,:b91\
,:b92,:b93,:b94,:b95,:b96,:b97,:b98,:b99,:b100,:b101,:b102,:b103,:b104,:b105,:\
b106,:b107,:b108,:b109,:b110,:b111,:b112,:b113)";
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )4208;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)4352;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqhstv[0] = (         void  *)ER_FILE_TRANSFER_DIRECTION[i];
      sqlstm.sqhstl[0] = (unsigned int  )2;
      sqlstm.sqhsts[0] = (         int  )0;
      sqlstm.sqindv[0] = (         void  *)0;
      sqlstm.sqinds[0] = (         int  )0;
      sqlstm.sqharm[0] = (unsigned int  )0;
      sqlstm.sqadto[0] = (unsigned short )0;
      sqlstm.sqtdso[0] = (unsigned short )0;
      sqlstm.sqhstv[1] = (         void  *)ER_HPLMN_CODE[i];
      sqlstm.sqhstl[1] = (unsigned int  )6;
      sqlstm.sqhsts[1] = (         int  )0;
      sqlstm.sqindv[1] = (         void  *)0;
      sqlstm.sqinds[1] = (         int  )0;
      sqlstm.sqharm[1] = (unsigned int  )0;
      sqlstm.sqadto[1] = (unsigned short )0;
      sqlstm.sqtdso[1] = (unsigned short )0;
      sqlstm.sqhstv[2] = (         void  *)ER_VPLMN_CODE[i];
      sqlstm.sqhstl[2] = (unsigned int  )6;
      sqlstm.sqhsts[2] = (         int  )0;
      sqlstm.sqindv[2] = (         void  *)0;
      sqlstm.sqinds[2] = (         int  )0;
      sqlstm.sqharm[2] = (unsigned int  )0;
      sqlstm.sqadto[2] = (unsigned short )0;
      sqlstm.sqtdso[2] = (unsigned short )0;
      sqlstm.sqhstv[3] = (         void  *)ER_PARTNER_CODE[i];
      sqlstm.sqhstl[3] = (unsigned int  )4;
      sqlstm.sqhsts[3] = (         int  )0;
      sqlstm.sqindv[3] = (         void  *)0;
      sqlstm.sqinds[3] = (         int  )0;
      sqlstm.sqharm[3] = (unsigned int  )0;
      sqlstm.sqadto[3] = (unsigned short )0;
      sqlstm.sqtdso[3] = (unsigned short )0;
      sqlstm.sqhstv[4] = (         void  *)ER_FILE_TYPE_INDICATOR[i];
      sqlstm.sqhstl[4] = (unsigned int  )2;
      sqlstm.sqhsts[4] = (         int  )0;
      sqlstm.sqindv[4] = (         void  *)0;
      sqlstm.sqinds[4] = (         int  )0;
      sqlstm.sqharm[4] = (unsigned int  )0;
      sqlstm.sqadto[4] = (unsigned short )0;
      sqlstm.sqtdso[4] = (unsigned short )0;
      sqlstm.sqhstv[5] = (         void  *)&ER_FILE_SEQUENCE_NUMBER[i];
      sqlstm.sqhstl[5] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[5] = (         int  )0;
      sqlstm.sqindv[5] = (         void  *)0;
      sqlstm.sqinds[5] = (         int  )0;
      sqlstm.sqharm[5] = (unsigned int  )0;
      sqlstm.sqadto[5] = (unsigned short )0;
      sqlstm.sqtdso[5] = (unsigned short )0;
      sqlstm.sqhstv[6] = (         void  *)&ER_RAP_SEQUENCE_NUMBER[i];
      sqlstm.sqhstl[6] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[6] = (         int  )0;
      sqlstm.sqindv[6] = (         void  *)0;
      sqlstm.sqinds[6] = (         int  )0;
      sqlstm.sqharm[6] = (unsigned int  )0;
      sqlstm.sqadto[6] = (unsigned short )0;
      sqlstm.sqtdso[6] = (unsigned short )0;
      sqlstm.sqhstv[7] = (         void  *)&ER_CALL_SEQUENCE[i];
      sqlstm.sqhstl[7] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[7] = (         int  )0;
      sqlstm.sqindv[7] = (         void  *)0;
      sqlstm.sqinds[7] = (         int  )0;
      sqlstm.sqharm[7] = (unsigned int  )0;
      sqlstm.sqadto[7] = (unsigned short )0;
      sqlstm.sqtdso[7] = (unsigned short )0;
      sqlstm.sqhstv[8] = (         void  *)&ER_ERROR_SEQUENCE[i];
      sqlstm.sqhstl[8] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[8] = (         int  )0;
      sqlstm.sqindv[8] = (         void  *)0;
      sqlstm.sqinds[8] = (         int  )0;
      sqlstm.sqharm[8] = (unsigned int  )0;
      sqlstm.sqadto[8] = (unsigned short )0;
      sqlstm.sqtdso[8] = (unsigned short )0;
      sqlstm.sqhstv[9] = (         void  *)ER_CALLS_TYPE_INDICATOR[i];
      sqlstm.sqhstl[9] = (unsigned int  )2;
      sqlstm.sqhsts[9] = (         int  )0;
      sqlstm.sqindv[9] = (         void  *)0;
      sqlstm.sqinds[9] = (         int  )0;
      sqlstm.sqharm[9] = (unsigned int  )0;
      sqlstm.sqadto[9] = (unsigned short )0;
      sqlstm.sqtdso[9] = (unsigned short )0;
      sqlstm.sqhstv[10] = (         void  *)&ER_CALL_TYPE[i];
      sqlstm.sqhstl[10] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[10] = (         int  )0;
      sqlstm.sqindv[10] = (         void  *)0;
      sqlstm.sqinds[10] = (         int  )0;
      sqlstm.sqharm[10] = (unsigned int  )0;
      sqlstm.sqadto[10] = (unsigned short )0;
      sqlstm.sqtdso[10] = (unsigned short )0;
      sqlstm.sqhstv[11] = (         void  *)ER_SERVICE_CODE[i];
      sqlstm.sqhstl[11] = (unsigned int  )4;
      sqlstm.sqhsts[11] = (         int  )0;
      sqlstm.sqindv[11] = (         void  *)0;
      sqlstm.sqinds[11] = (         int  )0;
      sqlstm.sqharm[11] = (unsigned int  )0;
      sqlstm.sqadto[11] = (unsigned short )0;
      sqlstm.sqtdso[11] = (unsigned short )0;
      sqlstm.sqhstv[12] = (         void  *)&ER_IMSI[i];
      sqlstm.sqhstl[12] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[12] = (         int  )0;
      sqlstm.sqindv[12] = (         void  *)0;
      sqlstm.sqinds[12] = (         int  )0;
      sqlstm.sqharm[12] = (unsigned int  )0;
      sqlstm.sqadto[12] = (unsigned short )0;
      sqlstm.sqtdso[12] = (unsigned short )0;
      sqlstm.sqhstv[13] = (         void  *)ER_MSISDN[i];
      sqlstm.sqhstl[13] = (unsigned int  )26;
      sqlstm.sqhsts[13] = (         int  )0;
      sqlstm.sqindv[13] = (         void  *)0;
      sqlstm.sqinds[13] = (         int  )0;
      sqlstm.sqharm[13] = (unsigned int  )0;
      sqlstm.sqadto[13] = (unsigned short )0;
      sqlstm.sqtdso[13] = (unsigned short )0;
      sqlstm.sqhstv[14] = (         void  *)ER_CALLED_CALLING_NUMBER[i];
      sqlstm.sqhstl[14] = (unsigned int  )87;
      sqlstm.sqhsts[14] = (         int  )0;
      sqlstm.sqindv[14] = (         void  *)0;
      sqlstm.sqinds[14] = (         int  )0;
      sqlstm.sqharm[14] = (unsigned int  )0;
      sqlstm.sqadto[14] = (unsigned short )0;
      sqlstm.sqtdso[14] = (unsigned short )0;
      sqlstm.sqhstv[15] = (         void  *)ER_DIALLED_DIGITS[i];
      sqlstm.sqhstl[15] = (unsigned int  )87;
      sqlstm.sqhsts[15] = (         int  )0;
      sqlstm.sqindv[15] = (         void  *)0;
      sqlstm.sqinds[15] = (         int  )0;
      sqlstm.sqharm[15] = (unsigned int  )0;
      sqlstm.sqadto[15] = (unsigned short )0;
      sqlstm.sqtdso[15] = (unsigned short )0;
      sqlstm.sqhstv[16] = (         void  *)&ER_CLIR_INDICATOR[i];
      sqlstm.sqhstl[16] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[16] = (         int  )0;
      sqlstm.sqindv[16] = (         void  *)0;
      sqlstm.sqinds[16] = (         int  )0;
      sqlstm.sqharm[16] = (unsigned int  )0;
      sqlstm.sqadto[16] = (unsigned short )0;
      sqlstm.sqtdso[16] = (unsigned short )0;
      sqlstm.sqhstv[17] = (         void  *)ER_DESTINATION_NETWORK[i];
      sqlstm.sqhstl[17] = (unsigned int  )7;
      sqlstm.sqhsts[17] = (         int  )0;
      sqlstm.sqindv[17] = (         void  *)0;
      sqlstm.sqinds[17] = (         int  )0;
      sqlstm.sqharm[17] = (unsigned int  )0;
      sqlstm.sqadto[17] = (unsigned short )0;
      sqlstm.sqtdso[17] = (unsigned short )0;
      sqlstm.sqhstv[18] = (         void  *)ER_CALL_DATE[i];
      sqlstm.sqhstl[18] = (unsigned int  )15;
      sqlstm.sqhsts[18] = (         int  )0;
      sqlstm.sqindv[18] = (         void  *)0;
      sqlstm.sqinds[18] = (         int  )0;
      sqlstm.sqharm[18] = (unsigned int  )0;
      sqlstm.sqadto[18] = (unsigned short )0;
      sqlstm.sqtdso[18] = (unsigned short )0;
      sqlstm.sqhstv[19] = (         void  *)&ER_UTC_OFFSET_CODE[i];
      sqlstm.sqhstl[19] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[19] = (         int  )0;
      sqlstm.sqindv[19] = (         void  *)0;
      sqlstm.sqinds[19] = (         int  )0;
      sqlstm.sqharm[19] = (unsigned int  )0;
      sqlstm.sqadto[19] = (unsigned short )0;
      sqlstm.sqtdso[19] = (unsigned short )0;
      sqlstm.sqhstv[20] = (         void  *)ER_UTC_OFFSET[i];
      sqlstm.sqhstl[20] = (unsigned int  )6;
      sqlstm.sqhsts[20] = (         int  )0;
      sqlstm.sqindv[20] = (         void  *)0;
      sqlstm.sqinds[20] = (         int  )0;
      sqlstm.sqharm[20] = (unsigned int  )0;
      sqlstm.sqadto[20] = (unsigned short )0;
      sqlstm.sqtdso[20] = (unsigned short )0;
      sqlstm.sqhstv[21] = (         void  *)&ER_CALL_DURATION[i];
      sqlstm.sqhstl[21] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[21] = (         int  )0;
      sqlstm.sqindv[21] = (         void  *)0;
      sqlstm.sqinds[21] = (         int  )0;
      sqlstm.sqharm[21] = (unsigned int  )0;
      sqlstm.sqadto[21] = (unsigned short )0;
      sqlstm.sqtdso[21] = (unsigned short )0;
      sqlstm.sqhstv[22] = (         void  *)ER_SIM_TOOLKIT_INDICATOR[i];
      sqlstm.sqhstl[22] = (unsigned int  )2;
      sqlstm.sqhsts[22] = (         int  )0;
      sqlstm.sqindv[22] = (         void  *)0;
      sqlstm.sqinds[22] = (         int  )0;
      sqlstm.sqharm[22] = (unsigned int  )0;
      sqlstm.sqadto[22] = (unsigned short )0;
      sqlstm.sqtdso[22] = (unsigned short )0;
      sqlstm.sqhstv[23] = (         void  *)&ER_RECORDING_ENTITY_CODE[i];
      sqlstm.sqhstl[23] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[23] = (         int  )0;
      sqlstm.sqindv[23] = (         void  *)0;
      sqlstm.sqinds[23] = (         int  )0;
      sqlstm.sqharm[23] = (unsigned int  )0;
      sqlstm.sqadto[23] = (unsigned short )0;
      sqlstm.sqtdso[23] = (unsigned short )0;
      sqlstm.sqhstv[24] = (         void  *)&ER_RECORDING_ENTITY_TYPE[i];
      sqlstm.sqhstl[24] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[24] = (         int  )0;
      sqlstm.sqindv[24] = (         void  *)0;
      sqlstm.sqinds[24] = (         int  )0;
      sqlstm.sqharm[24] = (unsigned int  )0;
      sqlstm.sqadto[24] = (unsigned short )0;
      sqlstm.sqtdso[24] = (unsigned short )0;
      sqlstm.sqhstv[25] = (         void  *)ER_RECORDING_ENTITY_ID[i];
      sqlstm.sqhstl[25] = (unsigned int  )46;
      sqlstm.sqhsts[25] = (         int  )0;
      sqlstm.sqindv[25] = (         void  *)0;
      sqlstm.sqinds[25] = (         int  )0;
      sqlstm.sqharm[25] = (unsigned int  )0;
      sqlstm.sqadto[25] = (unsigned short )0;
      sqlstm.sqtdso[25] = (unsigned short )0;
      sqlstm.sqhstv[26] = (         void  *)ER_CALL_REFERENCE[i];
      sqlstm.sqhstl[26] = (unsigned int  )21;
      sqlstm.sqhsts[26] = (         int  )0;
      sqlstm.sqindv[26] = (         void  *)0;
      sqlstm.sqinds[26] = (         int  )0;
      sqlstm.sqharm[26] = (unsigned int  )0;
      sqlstm.sqadto[26] = (unsigned short )0;
      sqlstm.sqtdso[26] = (unsigned short )0;
      sqlstm.sqhstv[27] = (         void  *)&ER_CELLID[i];
      sqlstm.sqhstl[27] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[27] = (         int  )0;
      sqlstm.sqindv[27] = (         void  *)0;
      sqlstm.sqinds[27] = (         int  )0;
      sqlstm.sqharm[27] = (unsigned int  )0;
      sqlstm.sqadto[27] = (unsigned short )0;
      sqlstm.sqtdso[27] = (unsigned short )0;
      sqlstm.sqhstv[28] = (         void  *)ER_SERVING_NETWORK[i];
      sqlstm.sqhstl[28] = (unsigned int  )6;
      sqlstm.sqhsts[28] = (         int  )0;
      sqlstm.sqindv[28] = (         void  *)0;
      sqlstm.sqinds[28] = (         int  )0;
      sqlstm.sqharm[28] = (unsigned int  )0;
      sqlstm.sqadto[28] = (unsigned short )0;
      sqlstm.sqtdso[28] = (unsigned short )0;
      sqlstm.sqhstv[29] = (         void  *)ER_IMEI[i];
      sqlstm.sqhstl[29] = (unsigned int  )21;
      sqlstm.sqhsts[29] = (         int  )0;
      sqlstm.sqindv[29] = (         void  *)0;
      sqlstm.sqinds[29] = (         int  )0;
      sqlstm.sqharm[29] = (unsigned int  )0;
      sqlstm.sqadto[29] = (unsigned short )0;
      sqlstm.sqtdso[29] = (unsigned short )0;
      sqlstm.sqhstv[30] = (         void  *)ER_BASIC_SERVICE_TYPE[i];
      sqlstm.sqhstl[30] = (unsigned int  )2;
      sqlstm.sqhsts[30] = (         int  )0;
      sqlstm.sqindv[30] = (         void  *)0;
      sqlstm.sqinds[30] = (         int  )0;
      sqlstm.sqharm[30] = (unsigned int  )0;
      sqlstm.sqadto[30] = (unsigned short )0;
      sqlstm.sqtdso[30] = (unsigned short )0;
      sqlstm.sqhstv[31] = (         void  *)ER_BASIC_SERVICE_CODE[i];
      sqlstm.sqhstl[31] = (unsigned int  )4;
      sqlstm.sqhsts[31] = (         int  )0;
      sqlstm.sqindv[31] = (         void  *)0;
      sqlstm.sqinds[31] = (         int  )0;
      sqlstm.sqharm[31] = (unsigned int  )0;
      sqlstm.sqadto[31] = (unsigned short )0;
      sqlstm.sqtdso[31] = (unsigned short )0;
      sqlstm.sqhstv[32] = (         void  *)&ER_TRANSPARENCY_INDICATOR[i];
      sqlstm.sqhstl[32] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[32] = (         int  )0;
      sqlstm.sqindv[32] = (         void  *)0;
      sqlstm.sqinds[32] = (         int  )0;
      sqlstm.sqharm[32] = (unsigned int  )0;
      sqlstm.sqadto[32] = (unsigned short )0;
      sqlstm.sqtdso[32] = (unsigned short )0;
      sqlstm.sqhstv[33] = (         void  *)&ER_FNUR[i];
      sqlstm.sqhstl[33] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[33] = (         int  )0;
      sqlstm.sqindv[33] = (         void  *)0;
      sqlstm.sqinds[33] = (         int  )0;
      sqlstm.sqharm[33] = (unsigned int  )0;
      sqlstm.sqadto[33] = (unsigned short )0;
      sqlstm.sqtdso[33] = (unsigned short )0;
      sqlstm.sqhstv[34] = (         void  *)&ER_USER_PROTOCOL_INDICATOR[i];
      sqlstm.sqhstl[34] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[34] = (         int  )0;
      sqlstm.sqindv[34] = (         void  *)0;
      sqlstm.sqinds[34] = (         int  )0;
      sqlstm.sqharm[34] = (unsigned int  )0;
      sqlstm.sqadto[34] = (unsigned short )0;
      sqlstm.sqtdso[34] = (unsigned short )0;
      sqlstm.sqhstv[35] = (         void  *)ER_GUARANTEED_BIT_RATE[i];
      sqlstm.sqhstl[35] = (unsigned int  )6;
      sqlstm.sqhsts[35] = (         int  )0;
      sqlstm.sqindv[35] = (         void  *)0;
      sqlstm.sqinds[35] = (         int  )0;
      sqlstm.sqharm[35] = (unsigned int  )0;
      sqlstm.sqadto[35] = (unsigned short )0;
      sqlstm.sqtdso[35] = (unsigned short )0;
      sqlstm.sqhstv[36] = (         void  *)ER_MAXIMUM_BIT_RATE[i];
      sqlstm.sqhstl[36] = (unsigned int  )6;
      sqlstm.sqhsts[36] = (         int  )0;
      sqlstm.sqindv[36] = (         void  *)0;
      sqlstm.sqinds[36] = (         int  )0;
      sqlstm.sqharm[36] = (unsigned int  )0;
      sqlstm.sqadto[36] = (unsigned short )0;
      sqlstm.sqtdso[36] = (unsigned short )0;
      sqlstm.sqhstv[37] = (         void  *)ER_HSCSD_INDICATOR[i];
      sqlstm.sqhstl[37] = (unsigned int  )4;
      sqlstm.sqhsts[37] = (         int  )0;
      sqlstm.sqindv[37] = (         void  *)0;
      sqlstm.sqinds[37] = (         int  )0;
      sqlstm.sqharm[37] = (unsigned int  )0;
      sqlstm.sqadto[37] = (unsigned short )0;
      sqlstm.sqtdso[37] = (unsigned short )0;
      sqlstm.sqhstv[38] = (         void  *)ER_SUPPLIMENTARY_SERVICE_CODE[i];
      sqlstm.sqhstl[38] = (unsigned int  )21;
      sqlstm.sqhsts[38] = (         int  )0;
      sqlstm.sqindv[38] = (         void  *)0;
      sqlstm.sqinds[38] = (         int  )0;
      sqlstm.sqharm[38] = (unsigned int  )0;
      sqlstm.sqadto[38] = (unsigned short )0;
      sqlstm.sqtdso[38] = (unsigned short )0;
      sqlstm.sqhstv[39] = (         void  *)&ER_SUPPLIMENTARY_ACTION_CODE[i];
      sqlstm.sqhstl[39] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[39] = (         int  )0;
      sqlstm.sqindv[39] = (         void  *)0;
      sqlstm.sqinds[39] = (         int  )0;
      sqlstm.sqharm[39] = (unsigned int  )0;
      sqlstm.sqadto[39] = (unsigned short )0;
      sqlstm.sqtdso[39] = (unsigned short )0;
      sqlstm.sqhstv[40] = (         void  *)ER_SUPPLIMENTARY_SERVICE_PARAMS[i];
      sqlstm.sqhstl[40] = (unsigned int  )46;
      sqlstm.sqhsts[40] = (         int  )0;
      sqlstm.sqindv[40] = (         void  *)0;
      sqlstm.sqinds[40] = (         int  )0;
      sqlstm.sqharm[40] = (unsigned int  )0;
      sqlstm.sqadto[40] = (unsigned short )0;
      sqlstm.sqtdso[40] = (unsigned short )0;
      sqlstm.sqhstv[41] = (         void  *)ER_THIRD_PARTY_NUMBER[i];
      sqlstm.sqhstl[41] = (unsigned int  )87;
      sqlstm.sqhsts[41] = (         int  )0;
      sqlstm.sqindv[41] = (         void  *)0;
      sqlstm.sqinds[41] = (         int  )0;
      sqlstm.sqharm[41] = (unsigned int  )0;
      sqlstm.sqadto[41] = (unsigned short )0;
      sqlstm.sqtdso[41] = (unsigned short )0;
      sqlstm.sqhstv[42] = (         void  *)&ER_THIRD_PARTY_CLIR_INDICATOR[i];
      sqlstm.sqhstl[42] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[42] = (         int  )0;
      sqlstm.sqindv[42] = (         void  *)0;
      sqlstm.sqinds[42] = (         int  )0;
      sqlstm.sqharm[42] = (unsigned int  )0;
      sqlstm.sqadto[42] = (unsigned short )0;
      sqlstm.sqtdso[42] = (unsigned short )0;
      sqlstm.sqhstv[43] = (         void  *)&ER_CAMEL_USED_FLAG[i];
      sqlstm.sqhstl[43] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[43] = (         int  )0;
      sqlstm.sqindv[43] = (         void  *)0;
      sqlstm.sqinds[43] = (         int  )0;
      sqlstm.sqharm[43] = (unsigned int  )0;
      sqlstm.sqadto[43] = (unsigned short )0;
      sqlstm.sqtdso[43] = (unsigned short )0;
      sqlstm.sqhstv[44] = (         void  *)&ER_CAMEL_SERVICE_LEVEL[i];
      sqlstm.sqhstl[44] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[44] = (         int  )0;
      sqlstm.sqindv[44] = (         void  *)0;
      sqlstm.sqinds[44] = (         int  )0;
      sqlstm.sqharm[44] = (unsigned int  )0;
      sqlstm.sqadto[44] = (unsigned short )0;
      sqlstm.sqtdso[44] = (unsigned short )0;
      sqlstm.sqhstv[45] = (         void  *)&ER_CAMEL_SERVICE_KEY[i];
      sqlstm.sqhstl[45] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[45] = (         int  )0;
      sqlstm.sqindv[45] = (         void  *)0;
      sqlstm.sqinds[45] = (         int  )0;
      sqlstm.sqharm[45] = (unsigned int  )0;
      sqlstm.sqadto[45] = (unsigned short )0;
      sqlstm.sqtdso[45] = (unsigned short )0;
      sqlstm.sqhstv[46] = (         void  *)&ER_CAMEL_DEFAULT_CALL_HANDLING[i];
      sqlstm.sqhstl[46] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[46] = (         int  )0;
      sqlstm.sqindv[46] = (         void  *)0;
      sqlstm.sqinds[46] = (         int  )0;
      sqlstm.sqharm[46] = (unsigned int  )0;
      sqlstm.sqadto[46] = (unsigned short )0;
      sqlstm.sqtdso[46] = (unsigned short )0;
      sqlstm.sqhstv[47] = (         void  *)&ER_CAMEL_EXCHANGE_RATE_CODE[i];
      sqlstm.sqhstl[47] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[47] = (         int  )0;
      sqlstm.sqindv[47] = (         void  *)0;
      sqlstm.sqinds[47] = (         int  )0;
      sqlstm.sqharm[47] = (unsigned int  )0;
      sqlstm.sqadto[47] = (unsigned short )0;
      sqlstm.sqtdso[47] = (unsigned short )0;
      sqlstm.sqhstv[48] = (         void  *)&ER_CAMEL_INVOCATION_FEE[i];
      sqlstm.sqhstl[48] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[48] = (         int  )0;
      sqlstm.sqindv[48] = (         void  *)0;
      sqlstm.sqinds[48] = (         int  )0;
      sqlstm.sqharm[48] = (unsigned int  )0;
      sqlstm.sqadto[48] = (unsigned short )0;
      sqlstm.sqtdso[48] = (unsigned short )0;
      sqlstm.sqhstv[49] = (         void  *)&ER_CAMEL_DISCOUNT_CODE[i];
      sqlstm.sqhstl[49] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[49] = (         int  )0;
      sqlstm.sqindv[49] = (         void  *)0;
      sqlstm.sqinds[49] = (         int  )0;
      sqlstm.sqharm[49] = (unsigned int  )0;
      sqlstm.sqadto[49] = (unsigned short )0;
      sqlstm.sqtdso[49] = (unsigned short )0;
      sqlstm.sqhstv[50] = (         void  *)&ER_CAMEL_DISCOUNT[i];
      sqlstm.sqhstl[50] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[50] = (         int  )0;
      sqlstm.sqindv[50] = (         void  *)0;
      sqlstm.sqinds[50] = (         int  )0;
      sqlstm.sqharm[50] = (unsigned int  )0;
      sqlstm.sqadto[50] = (unsigned short )0;
      sqlstm.sqtdso[50] = (unsigned short )0;
      sqlstm.sqhstv[51] = (         void  *)&ER_CAMEL_DISCOUNTABLE_AMT[i];
      sqlstm.sqhstl[51] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[51] = (         int  )0;
      sqlstm.sqindv[51] = (         void  *)0;
      sqlstm.sqinds[51] = (         int  )0;
      sqlstm.sqharm[51] = (unsigned int  )0;
      sqlstm.sqadto[51] = (unsigned short )0;
      sqlstm.sqtdso[51] = (unsigned short )0;
      sqlstm.sqhstv[52] = (         void  *)&ER_CAMEL_TAX_INFORMATION_COUNT[i];
      sqlstm.sqhstl[52] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[52] = (         int  )0;
      sqlstm.sqindv[52] = (         void  *)0;
      sqlstm.sqinds[52] = (         int  )0;
      sqlstm.sqharm[52] = (unsigned int  )0;
      sqlstm.sqadto[52] = (unsigned short )0;
      sqlstm.sqtdso[52] = (unsigned short )0;
      sqlstm.sqhstv[53] = (         void  *)&ER_CAMEL_TAX_CODE[i];
      sqlstm.sqhstl[53] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[53] = (         int  )0;
      sqlstm.sqindv[53] = (         void  *)0;
      sqlstm.sqinds[53] = (         int  )0;
      sqlstm.sqharm[53] = (unsigned int  )0;
      sqlstm.sqadto[53] = (unsigned short )0;
      sqlstm.sqtdso[53] = (unsigned short )0;
      sqlstm.sqhstv[54] = (         void  *)&ER_CAMEL_TAX_VALUE[i];
      sqlstm.sqhstl[54] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[54] = (         int  )0;
      sqlstm.sqindv[54] = (         void  *)0;
      sqlstm.sqinds[54] = (         int  )0;
      sqlstm.sqharm[54] = (unsigned int  )0;
      sqlstm.sqadto[54] = (unsigned short )0;
      sqlstm.sqtdso[54] = (unsigned short )0;
      sqlstm.sqhstv[55] = (         void  *)&ER_CAMEL_TAXABLE_AMOUNT[i];
      sqlstm.sqhstl[55] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[55] = (         int  )0;
      sqlstm.sqindv[55] = (         void  *)0;
      sqlstm.sqinds[55] = (         int  )0;
      sqlstm.sqharm[55] = (unsigned int  )0;
      sqlstm.sqadto[55] = (unsigned short )0;
      sqlstm.sqtdso[55] = (unsigned short )0;
      sqlstm.sqhstv[56] = (         void  *)ER_CAMEL_DESTINATION_NUMBER[i];
      sqlstm.sqhstl[56] = (unsigned int  )87;
      sqlstm.sqhsts[56] = (         int  )0;
      sqlstm.sqindv[56] = (         void  *)0;
      sqlstm.sqinds[56] = (         int  )0;
      sqlstm.sqharm[56] = (unsigned int  )0;
      sqlstm.sqadto[56] = (unsigned short )0;
      sqlstm.sqtdso[56] = (unsigned short )0;
      sqlstm.sqhstv[57] = (         void  *)&ER_CALL_TYPE_LEVEL1[i];
      sqlstm.sqhstl[57] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[57] = (         int  )0;
      sqlstm.sqindv[57] = (         void  *)0;
      sqlstm.sqinds[57] = (         int  )0;
      sqlstm.sqharm[57] = (unsigned int  )0;
      sqlstm.sqadto[57] = (unsigned short )0;
      sqlstm.sqtdso[57] = (unsigned short )0;
      sqlstm.sqhstv[58] = (         void  *)&ER_CALL_TYPE_LEVEL2[i];
      sqlstm.sqhstl[58] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[58] = (         int  )0;
      sqlstm.sqindv[58] = (         void  *)0;
      sqlstm.sqinds[58] = (         int  )0;
      sqlstm.sqharm[58] = (unsigned int  )0;
      sqlstm.sqadto[58] = (unsigned short )0;
      sqlstm.sqtdso[58] = (unsigned short )0;
      sqlstm.sqhstv[59] = (         void  *)&ER_CALL_TYPE_LEVEL3[i];
      sqlstm.sqhstl[59] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[59] = (         int  )0;
      sqlstm.sqindv[59] = (         void  *)0;
      sqlstm.sqinds[59] = (         int  )0;
      sqlstm.sqharm[59] = (unsigned int  )0;
      sqlstm.sqadto[59] = (unsigned short )0;
      sqlstm.sqtdso[59] = (unsigned short )0;
      sqlstm.sqhstv[60] = (         void  *)&ER_CHARGE_INFORMATION_COUNT[i];
      sqlstm.sqhstl[60] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[60] = (         int  )0;
      sqlstm.sqindv[60] = (         void  *)0;
      sqlstm.sqinds[60] = (         int  )0;
      sqlstm.sqharm[60] = (unsigned int  )0;
      sqlstm.sqadto[60] = (unsigned short )0;
      sqlstm.sqtdso[60] = (unsigned short )0;
      sqlstm.sqhstv[61] = (         void  *)ER_CHARGED_ITEM[i];
      sqlstm.sqhstl[61] = (unsigned int  )4;
      sqlstm.sqhsts[61] = (         int  )0;
      sqlstm.sqindv[61] = (         void  *)0;
      sqlstm.sqinds[61] = (         int  )0;
      sqlstm.sqharm[61] = (unsigned int  )0;
      sqlstm.sqadto[61] = (unsigned short )0;
      sqlstm.sqtdso[61] = (unsigned short )0;
      sqlstm.sqhstv[62] = (         void  *)ER_CHARGE_TYPE[i];
      sqlstm.sqhstl[62] = (unsigned int  )4;
      sqlstm.sqhsts[62] = (         int  )0;
      sqlstm.sqindv[62] = (         void  *)0;
      sqlstm.sqinds[62] = (         int  )0;
      sqlstm.sqharm[62] = (unsigned int  )0;
      sqlstm.sqadto[62] = (unsigned short )0;
      sqlstm.sqtdso[62] = (unsigned short )0;
      sqlstm.sqhstv[63] = (         void  *)&ER_CHARGEABLE_UNITS[i];
      sqlstm.sqhstl[63] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[63] = (         int  )0;
      sqlstm.sqindv[63] = (         void  *)0;
      sqlstm.sqinds[63] = (         int  )0;
      sqlstm.sqharm[63] = (unsigned int  )0;
      sqlstm.sqadto[63] = (unsigned short )0;
      sqlstm.sqtdso[63] = (unsigned short )0;
      sqlstm.sqhstv[64] = (         void  *)&ER_CHARGED_UNITS[i];
      sqlstm.sqhstl[64] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[64] = (         int  )0;
      sqlstm.sqindv[64] = (         void  *)0;
      sqlstm.sqinds[64] = (         int  )0;
      sqlstm.sqharm[64] = (unsigned int  )0;
      sqlstm.sqadto[64] = (unsigned short )0;
      sqlstm.sqtdso[64] = (unsigned short )0;
      sqlstm.sqhstv[65] = (         void  *)&ER_CHARGE[i];
      sqlstm.sqhstl[65] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[65] = (         int  )0;
      sqlstm.sqindv[65] = (         void  *)0;
      sqlstm.sqinds[65] = (         int  )0;
      sqlstm.sqharm[65] = (unsigned int  )0;
      sqlstm.sqadto[65] = (unsigned short )0;
      sqlstm.sqtdso[65] = (unsigned short )0;
      sqlstm.sqhstv[66] = (         void  *)&ER_TAX_INFORMATION_COUNT[i];
      sqlstm.sqhstl[66] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[66] = (         int  )0;
      sqlstm.sqindv[66] = (         void  *)0;
      sqlstm.sqinds[66] = (         int  )0;
      sqlstm.sqharm[66] = (unsigned int  )0;
      sqlstm.sqadto[66] = (unsigned short )0;
      sqlstm.sqtdso[66] = (unsigned short )0;
      sqlstm.sqhstv[67] = (         void  *)&ER_TAX_CODE[i];
      sqlstm.sqhstl[67] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[67] = (         int  )0;
      sqlstm.sqindv[67] = (         void  *)0;
      sqlstm.sqinds[67] = (         int  )0;
      sqlstm.sqharm[67] = (unsigned int  )0;
      sqlstm.sqadto[67] = (unsigned short )0;
      sqlstm.sqtdso[67] = (unsigned short )0;
      sqlstm.sqhstv[68] = (         void  *)&ER_TAX_VALUE[i];
      sqlstm.sqhstl[68] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[68] = (         int  )0;
      sqlstm.sqindv[68] = (         void  *)0;
      sqlstm.sqinds[68] = (         int  )0;
      sqlstm.sqharm[68] = (unsigned int  )0;
      sqlstm.sqadto[68] = (unsigned short )0;
      sqlstm.sqtdso[68] = (unsigned short )0;
      sqlstm.sqhstv[69] = (         void  *)&ER_TAXABLE_AMOUNT[i];
      sqlstm.sqhstl[69] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[69] = (         int  )0;
      sqlstm.sqindv[69] = (         void  *)0;
      sqlstm.sqinds[69] = (         int  )0;
      sqlstm.sqharm[69] = (unsigned int  )0;
      sqlstm.sqadto[69] = (unsigned short )0;
      sqlstm.sqtdso[69] = (unsigned short )0;
      sqlstm.sqhstv[70] = (         void  *)&ER_DISCOUNT_INFORMATION_COUNT[i];
      sqlstm.sqhstl[70] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[70] = (         int  )0;
      sqlstm.sqindv[70] = (         void  *)0;
      sqlstm.sqinds[70] = (         int  )0;
      sqlstm.sqharm[70] = (unsigned int  )0;
      sqlstm.sqadto[70] = (unsigned short )0;
      sqlstm.sqtdso[70] = (unsigned short )0;
      sqlstm.sqhstv[71] = (         void  *)&ER_DISCOUNT_CODE[i];
      sqlstm.sqhstl[71] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[71] = (         int  )0;
      sqlstm.sqindv[71] = (         void  *)0;
      sqlstm.sqinds[71] = (         int  )0;
      sqlstm.sqharm[71] = (unsigned int  )0;
      sqlstm.sqadto[71] = (unsigned short )0;
      sqlstm.sqtdso[71] = (unsigned short )0;
      sqlstm.sqhstv[72] = (         void  *)&ER_DISCOUNT[i];
      sqlstm.sqhstl[72] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[72] = (         int  )0;
      sqlstm.sqindv[72] = (         void  *)0;
      sqlstm.sqinds[72] = (         int  )0;
      sqlstm.sqharm[72] = (unsigned int  )0;
      sqlstm.sqadto[72] = (unsigned short )0;
      sqlstm.sqtdso[72] = (unsigned short )0;
      sqlstm.sqhstv[73] = (         void  *)&ER_DISCOUNTABLE_AMT[i];
      sqlstm.sqhstl[73] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[73] = (         int  )0;
      sqlstm.sqindv[73] = (         void  *)0;
      sqlstm.sqinds[73] = (         int  )0;
      sqlstm.sqharm[73] = (unsigned int  )0;
      sqlstm.sqadto[73] = (unsigned short )0;
      sqlstm.sqtdso[73] = (unsigned short )0;
      sqlstm.sqhstv[74] = (         void  *)&ER_TAP_EXCHANGE_RATE_CODE[i];
      sqlstm.sqhstl[74] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[74] = (         int  )0;
      sqlstm.sqindv[74] = (         void  *)0;
      sqlstm.sqinds[74] = (         int  )0;
      sqlstm.sqharm[74] = (unsigned int  )0;
      sqlstm.sqadto[74] = (unsigned short )0;
      sqlstm.sqtdso[74] = (unsigned short )0;
      sqlstm.sqhstv[75] = (         void  *)&ER_TAP_EXCHANGE_RATE[i];
      sqlstm.sqhstl[75] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[75] = (         int  )0;
      sqlstm.sqindv[75] = (         void  *)0;
      sqlstm.sqinds[75] = (         int  )0;
      sqlstm.sqharm[75] = (unsigned int  )0;
      sqlstm.sqadto[75] = (unsigned short )0;
      sqlstm.sqtdso[75] = (unsigned short )0;
      sqlstm.sqhstv[76] = (         void  *)&ER_TAP_EXCHANGE_RATE_DECIMAL[i];
      sqlstm.sqhstl[76] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[76] = (         int  )0;
      sqlstm.sqindv[76] = (         void  *)0;
      sqlstm.sqinds[76] = (         int  )0;
      sqlstm.sqharm[76] = (unsigned int  )0;
      sqlstm.sqadto[76] = (unsigned short )0;
      sqlstm.sqtdso[76] = (unsigned short )0;
      sqlstm.sqhstv[77] = (         void  *)ER_TAP_TAX_TYPE_RATE[i];
      sqlstm.sqhstl[77] = (unsigned int  )601;
      sqlstm.sqhsts[77] = (         int  )0;
      sqlstm.sqindv[77] = (         void  *)0;
      sqlstm.sqinds[77] = (         int  )0;
      sqlstm.sqharm[77] = (unsigned int  )0;
      sqlstm.sqadto[77] = (unsigned short )0;
      sqlstm.sqtdso[77] = (unsigned short )0;
      sqlstm.sqhstv[78] = (         void  *)ER_NETWORK_ACCESS_IDENTIFER[i];
      sqlstm.sqhstl[78] = (unsigned int  )31;
      sqlstm.sqhsts[78] = (         int  )0;
      sqlstm.sqindv[78] = (         void  *)0;
      sqlstm.sqinds[78] = (         int  )0;
      sqlstm.sqharm[78] = (unsigned int  )0;
      sqlstm.sqadto[78] = (unsigned short )0;
      sqlstm.sqtdso[78] = (unsigned short )0;
      sqlstm.sqhstv[79] = (         void  *)ER_PDP_ADDRESS[i];
      sqlstm.sqhstl[79] = (unsigned int  )46;
      sqlstm.sqhsts[79] = (         int  )0;
      sqlstm.sqindv[79] = (         void  *)0;
      sqlstm.sqinds[79] = (         int  )0;
      sqlstm.sqharm[79] = (unsigned int  )0;
      sqlstm.sqadto[79] = (unsigned short )0;
      sqlstm.sqtdso[79] = (unsigned short )0;
      sqlstm.sqhstv[80] = (         void  *)ER_APN_NI[i];
      sqlstm.sqhstl[80] = (unsigned int  )66;
      sqlstm.sqhsts[80] = (         int  )0;
      sqlstm.sqindv[80] = (         void  *)0;
      sqlstm.sqinds[80] = (         int  )0;
      sqlstm.sqharm[80] = (unsigned int  )0;
      sqlstm.sqadto[80] = (unsigned short )0;
      sqlstm.sqtdso[80] = (unsigned short )0;
      sqlstm.sqhstv[81] = (         void  *)ER_APN_OI[i];
      sqlstm.sqhstl[81] = (unsigned int  )66;
      sqlstm.sqhsts[81] = (         int  )0;
      sqlstm.sqindv[81] = (         void  *)0;
      sqlstm.sqinds[81] = (         int  )0;
      sqlstm.sqharm[81] = (unsigned int  )0;
      sqlstm.sqadto[81] = (unsigned short )0;
      sqlstm.sqtdso[81] = (unsigned short )0;
      sqlstm.sqhstv[82] = (         void  *)&ER_CAUSE_FOR_TERMINATION[i];
      sqlstm.sqhstl[82] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[82] = (         int  )0;
      sqlstm.sqindv[82] = (         void  *)0;
      sqlstm.sqinds[82] = (         int  )0;
      sqlstm.sqharm[82] = (unsigned int  )0;
      sqlstm.sqadto[82] = (unsigned short )0;
      sqlstm.sqtdso[82] = (unsigned short )0;
      sqlstm.sqhstv[83] = (         void  *)ER_PARTIAL_TYPE_INDICATOR[i];
      sqlstm.sqhstl[83] = (unsigned int  )2;
      sqlstm.sqhsts[83] = (         int  )0;
      sqlstm.sqindv[83] = (         void  *)0;
      sqlstm.sqinds[83] = (         int  )0;
      sqlstm.sqharm[83] = (unsigned int  )0;
      sqlstm.sqadto[83] = (unsigned short )0;
      sqlstm.sqtdso[83] = (unsigned short )0;
      sqlstm.sqhstv[84] = (         void  *)&ER_CHARGING_ID[i];
      sqlstm.sqhstl[84] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[84] = (         int  )0;
      sqlstm.sqindv[84] = (         void  *)0;
      sqlstm.sqinds[84] = (         int  )0;
      sqlstm.sqharm[84] = (unsigned int  )0;
      sqlstm.sqadto[84] = (unsigned short )0;
      sqlstm.sqtdso[84] = (unsigned short )0;
      sqlstm.sqhstv[85] = (         void  *)&ER_DATA_VOLUME_INCOMING[i];
      sqlstm.sqhstl[85] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[85] = (         int  )0;
      sqlstm.sqindv[85] = (         void  *)0;
      sqlstm.sqinds[85] = (         int  )0;
      sqlstm.sqharm[85] = (unsigned int  )0;
      sqlstm.sqadto[85] = (unsigned short )0;
      sqlstm.sqtdso[85] = (unsigned short )0;
      sqlstm.sqhstv[86] = (         void  *)&ER_DATA_VOLUME_OUTGOING[i];
      sqlstm.sqhstl[86] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[86] = (         int  )0;
      sqlstm.sqindv[86] = (         void  *)0;
      sqlstm.sqinds[86] = (         int  )0;
      sqlstm.sqharm[86] = (unsigned int  )0;
      sqlstm.sqadto[86] = (unsigned short )0;
      sqlstm.sqtdso[86] = (unsigned short )0;
      sqlstm.sqhstv[87] = (         void  *)&ER_SGSN_RECORDING_ENTITY_CODE1[i];
      sqlstm.sqhstl[87] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[87] = (         int  )0;
      sqlstm.sqindv[87] = (         void  *)0;
      sqlstm.sqinds[87] = (         int  )0;
      sqlstm.sqharm[87] = (unsigned int  )0;
      sqlstm.sqadto[87] = (unsigned short )0;
      sqlstm.sqtdso[87] = (unsigned short )0;
      sqlstm.sqhstv[88] = (         void  *)ER_SGSN_RECORDING_ENTITY_ID1[i];
      sqlstm.sqhstl[88] = (unsigned int  )46;
      sqlstm.sqhsts[88] = (         int  )0;
      sqlstm.sqindv[88] = (         void  *)0;
      sqlstm.sqinds[88] = (         int  )0;
      sqlstm.sqharm[88] = (unsigned int  )0;
      sqlstm.sqadto[88] = (unsigned short )0;
      sqlstm.sqtdso[88] = (unsigned short )0;
      sqlstm.sqhstv[89] = (         void  *)&ER_SGSN_RECORDING_ENTITY_CODE2[i];
      sqlstm.sqhstl[89] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[89] = (         int  )0;
      sqlstm.sqindv[89] = (         void  *)0;
      sqlstm.sqinds[89] = (         int  )0;
      sqlstm.sqharm[89] = (unsigned int  )0;
      sqlstm.sqadto[89] = (unsigned short )0;
      sqlstm.sqtdso[89] = (unsigned short )0;
      sqlstm.sqhstv[90] = (         void  *)ER_SGSN_RECORDING_ENTITY_ID2[i];
      sqlstm.sqhstl[90] = (unsigned int  )46;
      sqlstm.sqhsts[90] = (         int  )0;
      sqlstm.sqindv[90] = (         void  *)0;
      sqlstm.sqinds[90] = (         int  )0;
      sqlstm.sqharm[90] = (unsigned int  )0;
      sqlstm.sqadto[90] = (unsigned short )0;
      sqlstm.sqtdso[90] = (unsigned short )0;
      sqlstm.sqhstv[91] = (         void  *)&ER_SGSN_RECORDING_ENTITY_CODE3[i];
      sqlstm.sqhstl[91] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[91] = (         int  )0;
      sqlstm.sqindv[91] = (         void  *)0;
      sqlstm.sqinds[91] = (         int  )0;
      sqlstm.sqharm[91] = (unsigned int  )0;
      sqlstm.sqadto[91] = (unsigned short )0;
      sqlstm.sqtdso[91] = (unsigned short )0;
      sqlstm.sqhstv[92] = (         void  *)ER_SGSN_RECORDING_ENTITY_ID3[i];
      sqlstm.sqhstl[92] = (unsigned int  )46;
      sqlstm.sqhsts[92] = (         int  )0;
      sqlstm.sqindv[92] = (         void  *)0;
      sqlstm.sqinds[92] = (         int  )0;
      sqlstm.sqharm[92] = (unsigned int  )0;
      sqlstm.sqadto[92] = (unsigned short )0;
      sqlstm.sqtdso[92] = (unsigned short )0;
      sqlstm.sqhstv[93] = (         void  *)ER_CAMEL_APN_NI[i];
      sqlstm.sqhstl[93] = (unsigned int  )66;
      sqlstm.sqhsts[93] = (         int  )0;
      sqlstm.sqindv[93] = (         void  *)0;
      sqlstm.sqinds[93] = (         int  )0;
      sqlstm.sqharm[93] = (unsigned int  )0;
      sqlstm.sqadto[93] = (unsigned short )0;
      sqlstm.sqtdso[93] = (unsigned short )0;
      sqlstm.sqhstv[94] = (         void  *)ER_CAMEL_APN_OI[i];
      sqlstm.sqhstl[94] = (unsigned int  )66;
      sqlstm.sqhsts[94] = (         int  )0;
      sqlstm.sqindv[94] = (         void  *)0;
      sqlstm.sqinds[94] = (         int  )0;
      sqlstm.sqharm[94] = (unsigned int  )0;
      sqlstm.sqadto[94] = (unsigned short )0;
      sqlstm.sqtdso[94] = (unsigned short )0;
      sqlstm.sqhstv[95] = (         void  *)ER_FILE_CREATION_TIME[i];
      sqlstm.sqhstl[95] = (unsigned int  )15;
      sqlstm.sqhsts[95] = (         int  )0;
      sqlstm.sqindv[95] = (         void  *)0;
      sqlstm.sqinds[95] = (         int  )0;
      sqlstm.sqharm[95] = (unsigned int  )0;
      sqlstm.sqadto[95] = (unsigned short )0;
      sqlstm.sqtdso[95] = (unsigned short )0;
      sqlstm.sqhstv[96] = (         void  *)ER_FILE_TRANSFER_TIME[i];
      sqlstm.sqhstl[96] = (unsigned int  )15;
      sqlstm.sqhsts[96] = (         int  )0;
      sqlstm.sqindv[96] = (         void  *)0;
      sqlstm.sqinds[96] = (         int  )0;
      sqlstm.sqharm[96] = (unsigned int  )0;
      sqlstm.sqadto[96] = (unsigned short )0;
      sqlstm.sqtdso[96] = (unsigned short )0;
      sqlstm.sqhstv[97] = (         void  *)ER_FILE_AVAILABLE_TIME[i];
      sqlstm.sqhstl[97] = (unsigned int  )15;
      sqlstm.sqhsts[97] = (         int  )0;
      sqlstm.sqindv[97] = (         void  *)0;
      sqlstm.sqinds[97] = (         int  )0;
      sqlstm.sqharm[97] = (unsigned int  )0;
      sqlstm.sqadto[97] = (unsigned short )0;
      sqlstm.sqtdso[97] = (unsigned short )0;
      sqlstm.sqhstv[98] = (         void  *)ER_CHARGING_TIME_STAMP[i];
      sqlstm.sqhstl[98] = (unsigned int  )15;
      sqlstm.sqhsts[98] = (         int  )0;
      sqlstm.sqindv[98] = (         void  *)0;
      sqlstm.sqinds[98] = (         int  )0;
      sqlstm.sqharm[98] = (unsigned int  )0;
      sqlstm.sqadto[98] = (unsigned short )0;
      sqlstm.sqtdso[98] = (unsigned short )0;
      sqlstm.sqhstv[99] = (         void  *)ER_LOCAL_CURRENCY_CODE[i];
      sqlstm.sqhstl[99] = (unsigned int  )4;
      sqlstm.sqhsts[99] = (         int  )0;
      sqlstm.sqindv[99] = (         void  *)0;
      sqlstm.sqinds[99] = (         int  )0;
      sqlstm.sqharm[99] = (unsigned int  )0;
      sqlstm.sqadto[99] = (unsigned short )0;
      sqlstm.sqtdso[99] = (unsigned short )0;
      sqlstm.sqhstv[100] = (         void  *)ER_TAP_CURRENCY_CODE[i];
      sqlstm.sqhstl[100] = (unsigned int  )4;
      sqlstm.sqhsts[100] = (         int  )0;
      sqlstm.sqindv[100] = (         void  *)0;
      sqlstm.sqinds[100] = (         int  )0;
      sqlstm.sqharm[100] = (unsigned int  )0;
      sqlstm.sqadto[100] = (unsigned short )0;
      sqlstm.sqtdso[100] = (unsigned short )0;
      sqlstm.sqhstv[101] = (         void  *)&ER_TAP_DECIMAL_PLACES[i];
      sqlstm.sqhstl[101] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[101] = (         int  )0;
      sqlstm.sqindv[101] = (         void  *)0;
      sqlstm.sqinds[101] = (         int  )0;
      sqlstm.sqharm[101] = (unsigned int  )0;
      sqlstm.sqadto[101] = (unsigned short )0;
      sqlstm.sqtdso[101] = (unsigned short )0;
      sqlstm.sqhstv[102] = (         void  *)&ER_TARIFF_ID[i];
      sqlstm.sqhstl[102] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[102] = (         int  )0;
      sqlstm.sqindv[102] = (         void  *)0;
      sqlstm.sqinds[102] = (         int  )0;
      sqlstm.sqharm[102] = (unsigned int  )0;
      sqlstm.sqadto[102] = (unsigned short )0;
      sqlstm.sqtdso[102] = (unsigned short )0;
      sqlstm.sqhstv[103] = (         void  *)&ER_ERROR_CODE[i];
      sqlstm.sqhstl[103] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[103] = (         int  )0;
      sqlstm.sqindv[103] = (         void  *)0;
      sqlstm.sqinds[103] = (         int  )0;
      sqlstm.sqharm[103] = (unsigned int  )0;
      sqlstm.sqadto[103] = (unsigned short )0;
      sqlstm.sqtdso[103] = (unsigned short )0;
      sqlstm.sqhstv[104] = (         void  *)ER_ERROR_TYPE[i];
      sqlstm.sqhstl[104] = (unsigned int  )8;
      sqlstm.sqhsts[104] = (         int  )0;
      sqlstm.sqindv[104] = (         void  *)0;
      sqlstm.sqinds[104] = (         int  )0;
      sqlstm.sqharm[104] = (unsigned int  )0;
      sqlstm.sqadto[104] = (unsigned short )0;
      sqlstm.sqtdso[104] = (unsigned short )0;
      sqlstm.sqhstv[105] = (         void  *)ER_ERROR_CONTEXT_DETAILS[i];
      sqlstm.sqhstl[105] = (unsigned int  )101;
      sqlstm.sqhsts[105] = (         int  )0;
      sqlstm.sqindv[105] = (         void  *)0;
      sqlstm.sqinds[105] = (         int  )0;
      sqlstm.sqharm[105] = (unsigned int  )0;
      sqlstm.sqadto[105] = (unsigned short )0;
      sqlstm.sqtdso[105] = (unsigned short )0;
      sqlstm.sqhstv[106] = (         void  *)&ER_APPLICATION_TAG[i];
      sqlstm.sqhstl[106] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[106] = (         int  )0;
      sqlstm.sqindv[106] = (         void  *)0;
      sqlstm.sqinds[106] = (         int  )0;
      sqlstm.sqharm[106] = (unsigned int  )0;
      sqlstm.sqadto[106] = (unsigned short )0;
      sqlstm.sqtdso[106] = (unsigned short )0;
      sqlstm.sqhstv[107] = (         void  *)ER_CONTEXT_NAME[i];
      sqlstm.sqhstl[107] = (unsigned int  )51;
      sqlstm.sqhsts[107] = (         int  )0;
      sqlstm.sqindv[107] = (         void  *)0;
      sqlstm.sqinds[107] = (         int  )0;
      sqlstm.sqharm[107] = (unsigned int  )0;
      sqlstm.sqadto[107] = (unsigned short )0;
      sqlstm.sqtdso[107] = (unsigned short )0;
      sqlstm.sqhstv[108] = (         void  *)ER_DATA_TYPE_INDICATOR[i];
      sqlstm.sqhstl[108] = (unsigned int  )2;
      sqlstm.sqhsts[108] = (         int  )0;
      sqlstm.sqindv[108] = (         void  *)0;
      sqlstm.sqinds[108] = (         int  )0;
      sqlstm.sqharm[108] = (unsigned int  )0;
      sqlstm.sqadto[108] = (unsigned short )0;
      sqlstm.sqtdso[108] = (unsigned short )0;
      sqlstm.sqhstv[109] = (         void  *)ER_ERROR_FIELD_NAME[i];
      sqlstm.sqhstl[109] = (unsigned int  )51;
      sqlstm.sqhsts[109] = (         int  )0;
      sqlstm.sqindv[109] = (         void  *)0;
      sqlstm.sqinds[109] = (         int  )0;
      sqlstm.sqharm[109] = (unsigned int  )0;
      sqlstm.sqadto[109] = (unsigned short )0;
      sqlstm.sqtdso[109] = (unsigned short )0;
      sqlstm.sqhstv[110] = (         void  *)ER_ERROR_MESSAGE[i];
      sqlstm.sqhstl[110] = (unsigned int  )501;
      sqlstm.sqhsts[110] = (         int  )0;
      sqlstm.sqindv[110] = (         void  *)0;
      sqlstm.sqinds[110] = (         int  )0;
      sqlstm.sqharm[110] = (unsigned int  )0;
      sqlstm.sqadto[110] = (unsigned short )0;
      sqlstm.sqtdso[110] = (unsigned short )0;
      sqlstm.sqhstv[111] = (         void  *)ER_ERROR_VALUE[i];
      sqlstm.sqhstl[111] = (unsigned int  )101;
      sqlstm.sqhsts[111] = (         int  )0;
      sqlstm.sqindv[111] = (         void  *)0;
      sqlstm.sqinds[111] = (         int  )0;
      sqlstm.sqharm[111] = (unsigned int  )0;
      sqlstm.sqadto[111] = (unsigned short )0;
      sqlstm.sqtdso[111] = (unsigned short )0;
      sqlstm.sqhstv[112] = (         void  *)&ER_ERROR_NODE[i];
      sqlstm.sqhstl[112] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[112] = (         int  )0;
      sqlstm.sqindv[112] = (         void  *)0;
      sqlstm.sqinds[112] = (         int  )0;
      sqlstm.sqharm[112] = (unsigned int  )0;
      sqlstm.sqadto[112] = (unsigned short )0;
      sqlstm.sqtdso[112] = (unsigned short )0;
      sqlstm.sqhstv[113] = (         void  *)ER_RAP_STATUS[i];
      sqlstm.sqhstl[113] = (unsigned int  )101;
      sqlstm.sqhsts[113] = (         int  )0;
      sqlstm.sqindv[113] = (         void  *)0;
      sqlstm.sqinds[113] = (         int  )0;
      sqlstm.sqharm[113] = (unsigned int  )0;
      sqlstm.sqadto[113] = (unsigned short )0;
      sqlstm.sqtdso[113] = (unsigned short )0;
      sqlstm.sqphsv = sqlstm.sqhstv;
      sqlstm.sqphsl = sqlstm.sqhstl;
      sqlstm.sqphss = sqlstm.sqhsts;
      sqlstm.sqpind = sqlstm.sqindv;
      sqlstm.sqpins = sqlstm.sqinds;
      sqlstm.sqparm = sqlstm.sqharm;
      sqlstm.sqparc = sqlstm.sqharc;
      sqlstm.sqpadto = sqlstm.sqadto;
      sqlstm.sqptdso = sqlstm.sqtdso;
      sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



      if(ERRCODE!=0)
      {
         TRACEENTRY(1,"%s","Error Inserting the below Record into PM_RAP_DETAILS table");
         TRACEENTRY(1,"%s -%d-","ERROR : sqlca.sqlcode :",ERRCODE);

         Index = i+1;

         TRACEENTRY(1,"%s","String Values Below ------------------");
         TRACEENTRY(1,"FILE_TRANSFER_DIRECTION         : -%d- -%s-",Index,ER_FILE_TRANSFER_DIRECTION[i]);
         TRACEENTRY(1,"SERVICE_CODE                    : -%d- -%s-",Index,ER_SERVICE_CODE[i]);
         TRACEENTRY(1,"HPLMN_CODE                      : -%d- -%s-",Index,ER_HPLMN_CODE[i]);
         TRACEENTRY(1,"VPLMN_CODE                      : -%d- -%s-",Index,ER_VPLMN_CODE[i]);
         TRACEENTRY(1,"PARTNER_CODE                    : -%d- -%s-",Index,ER_PARTNER_CODE[i]);
         TRACEENTRY(1,"FILE_TYPE_INDICATOR             : -%d- -%s-",Index,ER_FILE_TYPE_INDICATOR[i]);
         TRACEENTRY(1,"CALLS_TYPE_INDICATOR            : -%d- -%s-",Index,ER_CALLS_TYPE_INDICATOR[i]);
         TRACEENTRY(1,"MSISDN                          : -%d- -%s-",Index,ER_MSISDN[i]);
         TRACEENTRY(1,"CALLED_CALLING_NUMBER           : -%d- -%s-",Index,ER_CALLED_CALLING_NUMBER[i]);
         TRACEENTRY(1,"DIALLED_DIGITS                  : -%d- -%s-",Index,ER_DIALLED_DIGITS[i]);
         TRACEENTRY(1,"DESTINATION_NETWORK             : -%d- -%s-",Index,ER_DESTINATION_NETWORK[i]);
         TRACEENTRY(1,"CALL_DATE                       : -%d- -%s-",Index,ER_CALL_DATE[i]);
         TRACEENTRY(1,"UTC_OFFSET                      : -%d- -%s-",Index,ER_UTC_OFFSET[i]);
         TRACEENTRY(1,"SIM_TOOLKIT_INDICATOR           : -%d- -%s-",Index,ER_SIM_TOOLKIT_INDICATOR[i]);
         TRACEENTRY(1,"RECORDING_ENTITY_ID             : -%d- -%s-",Index,ER_RECORDING_ENTITY_ID[i]);
         TRACEENTRY(1,"CALL_REFERENCE                  : -%d- -%s-",Index,ER_CALL_REFERENCE[i]);
         TRACEENTRY(1,"SERVING_NETWORK                 : -%d- -%s-",Index,ER_SERVING_NETWORK[i]);
         TRACEENTRY(1,"IMEI                            : -%d- -%s-",Index,ER_IMEI[i]);
         TRACEENTRY(1,"BASIC_SERVICE_TYPE              : -%d- -%s-",Index,ER_BASIC_SERVICE_TYPE[i]);
         TRACEENTRY(1,"BASIC_SERVICE_CODE              : -%d- -%s-",Index,ER_BASIC_SERVICE_CODE[i]);
         TRACEENTRY(1,"GUARANTEED_BIT_RATE             : -%d- -%s-",Index,ER_GUARANTEED_BIT_RATE[i]);
         TRACEENTRY(1,"MAXIMUM_BIT_RATE                : -%d- -%s-",Index,ER_MAXIMUM_BIT_RATE[i]);
         TRACEENTRY(1,"HSCSD_INDICATOR                 : -%d- -%s-",Index,ER_HSCSD_INDICATOR[i]);
         TRACEENTRY(1,"SUPPLIMENTARY_SERVICE_CODE      : -%d- -%s-",Index,ER_SUPPLIMENTARY_SERVICE_CODE[i]);
         TRACEENTRY(1,"SUPPLIMENTARY_SERVICE_PARAMS    : -%d- -%s-",Index,ER_SUPPLIMENTARY_SERVICE_PARAMS[i]);
         TRACEENTRY(1,"THIRD_PARTY_NUMBER              : -%d- -%s-",Index,ER_THIRD_PARTY_NUMBER[i]);
         TRACEENTRY(1,"CAMEL_DESTINATION_NUMBER        : -%d- -%s-",Index,ER_CAMEL_DESTINATION_NUMBER[i]);
         TRACEENTRY(1,"CHARGED_ITEM                    : -%d- -%s-",Index,ER_CHARGED_ITEM[i]);
         TRACEENTRY(1,"CHARGE_TYPE                     : -%d- -%s-",Index,ER_CHARGE_TYPE[i]);
         TRACEENTRY(1,"PDP_ADDRESS                     : -%d- -%s-",Index,ER_PDP_ADDRESS[i]);
         TRACEENTRY(1,"APN_NI                          : -%d- -%s-",Index,ER_APN_NI[i]);
         TRACEENTRY(1,"APN_OI                          : -%d- -%s-",Index,ER_APN_OI[i]);
         TRACEENTRY(1,"TAP_TAX_TYPE_RATE               : -%d- -%s-",Index,ER_TAP_TAX_TYPE_RATE[i]);
         TRACEENTRY(1,"ERROR_TYPE                      : -%d- -%s-",Index,ER_ERROR_TYPE[i]);
         TRACEENTRY(1,"ERROR_CONTEXT_DETAILS           : -%d- -%s-",Index,ER_ERROR_CONTEXT_DETAILS[i]);
         TRACEENTRY(1,"CONTEXT_NAME                    : -%d- -%s-",Index,ER_CONTEXT_NAME[i]);
         TRACEENTRY(1,"ERROR_FIELD_NAME                : -%d- -%s-",Index,ER_ERROR_FIELD_NAME[i]);
         TRACEENTRY(1,"ERROR_MESSAGE                   : -%d- -%s-",Index,ER_ERROR_MESSAGE[i]);
         TRACEENTRY(1,"ERROR_VALUE                     : -%d- -%s-",Index,ER_ERROR_VALUE[i]);
         TRACEENTRY(1,"RAP_STATUS                      : -%d- -%s-",Index,ER_RAP_STATUS[i]);

         TRACEENTRY(1,"%s","Number Values Below ------------------");
         TRACEENTRY(1,"FILE_SEQUENCE_NUMBER            : -%d- -%d-",Index,ER_FILE_SEQUENCE_NUMBER[i]);
         TRACEENTRY(1,"CALL_SEQUENCE                   : -%d- -%f-",Index,ER_CALL_SEQUENCE[i]);
         TRACEENTRY(1,"ERROR_SEQUENCE                  : -%d- -%f-",Index,ER_ERROR_SEQUENCE[i]);
         TRACEENTRY(1,"CALL_TYPE                       : -%d- -%d-",Index,ER_CALL_TYPE[i]);
         TRACEENTRY(1,"IMSI                            : -%d- -%f-",Index,ER_IMSI[i]);
         TRACEENTRY(1,"RAPFILE_SEQUENCE_NUMBER         : -%d- -%d-",Index,ER_RAP_SEQUENCE_NUMBER[i]);
         TRACEENTRY(1,"CLIR_INDICATOR                  : -%d- -%d-",Index,ER_CLIR_INDICATOR[i]);
         TRACEENTRY(1,"CALL_DURATION                   : -%d- -%f-",Index,ER_CALL_DURATION[i]);
         TRACEENTRY(1,"UTC_OFFSET_CODE                 : -%d- -%d-",Index,ER_UTC_OFFSET_CODE[i]);
         TRACEENTRY(1,"RECORDING_ENTITY_CODE           : -%d- -%d-",Index,ER_RECORDING_ENTITY_CODE[i]);
         TRACEENTRY(1,"RECORDING_ENTITY_TYPE           : -%d- -%d-",Index,ER_RECORDING_ENTITY_TYPE[i]);
         TRACEENTRY(1,"LOCATION_AREA                   : -%d- -%f-",Index,ER_LOCATION_AREA[i]);
         TRACEENTRY(1,"CELLID                          : -%d- -%f-",Index,ER_CELLID[i]);
         TRACEENTRY(1,"TRANSPARENCY_INDICATOR          : -%d- -%d-",Index,ER_TRANSPARENCY_INDICATOR[i]);
         TRACEENTRY(1,"FNUR                            : -%d- -%f-",Index,ER_FNUR[i]);
         TRACEENTRY(1,"USER_PROTOCOL_INDICATOR         : -%d- -%f-",Index,ER_USER_PROTOCOL_INDICATOR[i]);
         TRACEENTRY(1,"SUPPLIMENTARY_ACTION_CODE       : -%d- -%d-",Index,ER_SUPPLIMENTARY_ACTION_CODE[i]);
         TRACEENTRY(1,"THIRD_PARTY_CLIR_INDICATOR      : -%d- -%d-",Index,ER_THIRD_PARTY_CLIR_INDICATOR[i]);
         TRACEENTRY(1,"CAMEL_USED_FLAG                 : -%d- -%d-",Index,ER_CAMEL_USED_FLAG[i]);
         TRACEENTRY(1,"CAMEL_SERVICE_LEVEL             : -%d- -%f-",Index,ER_CAMEL_SERVICE_LEVEL[i]);
         TRACEENTRY(1,"CAMEL_SERVICE_KEY               : -%d- -%f-",Index,ER_CAMEL_SERVICE_KEY[i]);
         TRACEENTRY(1,"CAMEL_DEFAULT_CALL_HANDLING     : -%d- -%f-",Index,ER_CAMEL_DEFAULT_CALL_HANDLING[i]);
         TRACEENTRY(1,"CAMEL_EXCHANGE_RATE_CODE        : -%d- -%d-",Index,ER_CAMEL_EXCHANGE_RATE_CODE[i]);
         TRACEENTRY(1,"CAMEL_INVOCATION_FEE            : -%d- -%f-",Index,ER_CAMEL_INVOCATION_FEE[i]);
         TRACEENTRY(1,"CAMEL_DISCOUNT_CODE             : -%d- -%d-",Index,ER_CAMEL_DISCOUNT_CODE[i]);
         TRACEENTRY(1,"CAMEL_DISCOUNT                  : -%d- -%f-",Index,ER_CAMEL_DISCOUNT[i]);
         TRACEENTRY(1,"CAMEL_DISCOUNTABLE_AMOUNT       : -%d- -%f-",Index,ER_CAMEL_DISCOUNTABLE_AMT[i]);
         TRACEENTRY(1,"CAMEL_TAX_INFORMATION_COUNT     : -%d- -%d-",Index,ER_CAMEL_TAX_INFORMATION_COUNT[i]);
         TRACEENTRY(1,"CAMEL_TAX_CODE                  : -%d- -%d-",Index,ER_CAMEL_TAX_CODE[i]);
         TRACEENTRY(1,"CAMEL_TAX_VALUE                 : -%d- -%f-",Index,ER_CAMEL_TAX_VALUE[i]);
         TRACEENTRY(1,"CAMEL_TAXABLE_AMOUNT            : -%d- -%f-",Index,ER_CAMEL_TAXABLE_AMOUNT[i]);
         TRACEENTRY(1,"CALL_TYPE_LEVEL1                : -%d- -%d-",Index,ER_CALL_TYPE_LEVEL1[i]);
         TRACEENTRY(1,"CALL_TYPE_LEVEL2                : -%d- -%d-",Index,ER_CALL_TYPE_LEVEL2[i]);
         TRACEENTRY(1,"CALL_TYPE_LEVEL3                : -%d- -%d-",Index,ER_CALL_TYPE_LEVEL3[i]);
         TRACEENTRY(1,"CHARGE_INFORMATION_COUNT        : -%d- -%d-",Index,ER_CHARGE_INFORMATION_COUNT[i]);
         TRACEENTRY(1,"CHARGEABLE_UNITS                : -%d- -%f-",Index,ER_CHARGEABLE_UNITS[i]);
         TRACEENTRY(1,"CHARGED_UNITS                   : -%d- -%f-",Index,ER_CHARGED_UNITS[i]);
         TRACEENTRY(1,"CHARGE                          : -%d- -%f-",Index,ER_CHARGE[i]);
         TRACEENTRY(1,"TAX_INFORMATION_COUNT           : -%d- -%d-",Index,ER_TAX_INFORMATION_COUNT[i]);
         TRACEENTRY(1,"TAX_CODE                        : -%d- -%d-",Index,ER_TAX_CODE[i]);
         TRACEENTRY(1,"TAX_VALUE                       : -%d- -%f-",Index,ER_TAX_VALUE[i]);
         TRACEENTRY(1,"TAXABLE_AMOUNT                  : -%d- -%f-",Index,ER_TAXABLE_AMOUNT[i]);
         TRACEENTRY(1,"DISCOUNT_INFORMATION_COUNT      : -%d- -%d-",Index,ER_DISCOUNT_INFORMATION_COUNT[i]);
         TRACEENTRY(1,"DISCOUNT_CODE                   : -%d- -%d-",Index,ER_DISCOUNT_CODE[i]);
         TRACEENTRY(1,"DISCOUNT                        : -%d- -%f-",Index,ER_DISCOUNT[i]);
         TRACEENTRY(1,"DISCOUNTABLE_AMT                : -%d- -%f-",Index,ER_DISCOUNTABLE_AMT[i]);
         TRACEENTRY(1,"TAP_EXCHANGE_RATE_CODE          : -%d- -%d-",Index,ER_TAP_EXCHANGE_RATE_CODE[i]);
         TRACEENTRY(1,"TAP_EXCHANGE_RATE               : -%d- -%f-",Index,ER_TAP_EXCHANGE_RATE[i]);
         TRACEENTRY(1,"TAP_EXCHANGE_RATE_DECIMAL       : -%d- -%d-",Index,ER_TAP_EXCHANGE_RATE_DECIMAL[i]);
         TRACEENTRY(1,"ERROR_CODE                      : -%d- -%d-",Index,ER_ERROR_CODE[i]);
         TRACEENTRY(1,"APPLICATION_TAG                 : -%d- -%d-",Index,ER_APPLICATION_TAG[i]);
         TRACEENTRY(1,"ERROR_NODE                      : -%d- -%d-",Index,ER_ERROR_NODE[i]);
         break;
      }
   }

}

void CheckBulkInsertIOTError(int TotalIOTCDRS)
{
   int i=0;
   int Index=0;

   TRACEENTRY(1,"%s","Checking for Insert Errors");
   for(i=TotalIOTCDRS;i<=TotalIOTCDRS;i++)
   {
      /* EXEC SQL INSERT INTO PM_TMP_TAP_CDRS
      (
          FILE_TRANSFER_DIRECTION        ,
          HPLMN_CODE                     ,
          VPLMN_CODE                     ,
          PARTNER_CODE                   ,
          FILE_TYPE_INDICATOR            ,
          FILE_SEQUENCE_NUMBER           ,
          CALL_SEQUENCE                  ,
          CALL_TYPE                      ,
          SERVICE_CODE                   ,
          IMSI                           ,
          MSISDN                         ,
          CALLED_CALLING_NUMBER          ,
          DIALLED_DIGITS                 ,
          CALL_DATE                      ,
          CALL_DURATION                  ,
          BASIC_SERVICE_TYPE             ,
          BASIC_SERVICE_CODE             ,
          CHARGED_ITEM                   ,
          CHARGEABLE_UNITS               ,
          CHARGED_UNITS                  ,
          CHARGE                         ,
          TAX_INFORMATION_COUNT          ,
          TAX_CODE                       ,
          TAX_VALUE                      ,
          TAXABLE_AMOUNT                 ,
          DISCOUNT_INFORMATION_COUNT     ,
          DISCOUNT_CODE                  ,
          DISCOUNT                       ,
          DISCOUNTABLE_AMT               ,
          TAP_EXCHANGE_RATE              ,
          TAP_EXCHANGE_RATE_DECIMAL      ,
          CALL_TYPE_LEVEL1               ,
          DATA_VOLUME_INCOMING           ,
          DATA_VOLUME_OUTGOING           ,
          HOME_CURNCY_CHARGE             ,
          HOME_CURNCY_TAX                ,
          HOME_CURNCY_DISCOUNT           ,
          CAMEL_INVOCATION_FEE           ,
          CDR_ERROR_FLAG                 ,
          CHARGE_CONTEXT                 ,               
          TAX_CONTEXT                    ,
          DISCOUNT_CONTEXT               ,
          ERROR_NODE  
      )
      VALUES
      (
         :IOT_FILE_TRANSFER_DIRECTION[i]    ,
         :IOT_HPLMN_CODE[i]                 ,
         :IOT_VPLMN_CODE[i]                 ,
         :IOT_PARTNER_CODE[i]               ,
         :IOT_FILE_TYPE_INDICATOR[i]        ,
         :IOT_FILE_SEQUENCE_NUMBER[i]       ,
         :IOT_CALL_SEQUENCE[i]              ,
         :IOT_CALL_TYPE[i]                  ,
         :IOT_SERVICE_CODE[i]               ,
         :IOT_IMSI[i]                       ,
         :IOT_MSISDN[i]                     ,
         :IOT_CALLED_CALLING_NUMBER[i]      ,
         :IOT_DIALLED_DIGITS[i]             ,
         to_date(:IOT_CALL_DATE[i],'YYYYMMDDHH24MISS'),
         :IOT_CALL_DURATION[i]              ,
         :IOT_BASIC_SERVICE_TYPE[i]         ,
         :IOT_BASIC_SERVICE_CODE[i]         ,
         :IOT_CHARGED_ITEM[i]               ,
         :IOT_CHARGEABLE_UNITS[i]           ,
         :IOT_CHARGED_UNITS[i]              ,
         :IOT_CHARGE[i]                     ,
         :IOT_TAX_INFORMATION_COUNT[i]      ,
         :IOT_TAX_CODE[i]                   ,
         :IOT_TAX_VALUE[i]                  ,
         :IOT_TAXABLE_AMOUNT[i]             ,
         :IOT_DISCOUNT_INFORMATION_COUNT[i] ,
         :IOT_DISCOUNT_CODE[i]              ,
         :IOT_DISCOUNT[i]                   ,
         :IOT_DISCOUNTABLE_AMT[i]           ,
         :IOT_TAP_EXCHANGE_RATE[i]          ,
         :IOT_TAP_EXCHANGE_RATE_DECIMAL[i]  ,
         :IOT_CALL_TYPE_LEVEL1[i]           ,
         :IOT_DATA_VOLUME_INCOMING[i]       ,
         :IOT_DATA_VOLUME_OUTGOING[i]       ,
         :IOT_HOME_CURNCY_CHARGE[i]         ,
         :IOT_HOME_CURNCY_TAX[i]            ,
         :IOT_HOME_CURNCY_DISCOUNT[i]       ,
         :IOT_CAMEL_INVOCATION_FEE[i]       ,
         :CDR_ERROR_FLAG[i]                 ,
         :IOT_CHARGE_CONTEXT[i]             ,
         :IOT_TAX_CONTEXT[i]                ,
         :IOT_DISCOUNT_CONTEXT[i]           ,
         :IOT_ERROR_NODE[i]
      ); */ 

{
      struct sqlexd sqlstm;
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 129;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.stmt = "insert into PM_TMP_TAP_CDRS (FILE_TRANSFER_DIRECTION,HP\
LMN_CODE,VPLMN_CODE,PARTNER_CODE,FILE_TYPE_INDICATOR,FILE_SEQUENCE_NUMBER,CALL\
_SEQUENCE,CALL_TYPE,SERVICE_CODE,IMSI,MSISDN,CALLED_CALLING_NUMBER,DIALLED_DIG\
ITS,CALL_DATE,CALL_DURATION,BASIC_SERVICE_TYPE,BASIC_SERVICE_CODE,CHARGED_ITEM\
,CHARGEABLE_UNITS,CHARGED_UNITS,CHARGE,TAX_INFORMATION_COUNT,TAX_CODE,TAX_VALU\
E,TAXABLE_AMOUNT,DISCOUNT_INFORMATION_COUNT,DISCOUNT_CODE,DISCOUNT,DISCOUNTABL\
E_AMT,TAP_EXCHANGE_RATE,TAP_EXCHANGE_RATE_DECIMAL,CALL_TYPE_LEVEL1,DATA_VOLUME\
_INCOMING,DATA_VOLUME_OUTGOING,HOME_CURNCY_CHARGE,HOME_CURNCY_TAX,HOME_CURNCY_\
DISCOUNT,CAMEL_INVOCATION_FEE,CDR_ERROR_FLAG,CHARGE_CONTEXT,TAX_CONTEXT,DISCOU\
NT_CONTEXT,ERROR_NODE) values (:b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b\
11,:b12,to_date(:b13,'YYYYMMDDHH24MISS'),:b14,:b15,:b16,:b17,:b18,:b19,:b20,:b\
21,:b22,:b23,:b24,:b25,:b26,:b27,:b28,:b29,:b30,:b31,:b32,:b33,:b34,:b35,:b36,\
:b37,:b38,:b39,:b40,:b41,:b42)";
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )4679;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)4352;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqhstv[0] = (         void  *)IOT_FILE_TRANSFER_DIRECTION[i];
      sqlstm.sqhstl[0] = (unsigned int  )2;
      sqlstm.sqhsts[0] = (         int  )0;
      sqlstm.sqindv[0] = (         void  *)0;
      sqlstm.sqinds[0] = (         int  )0;
      sqlstm.sqharm[0] = (unsigned int  )0;
      sqlstm.sqadto[0] = (unsigned short )0;
      sqlstm.sqtdso[0] = (unsigned short )0;
      sqlstm.sqhstv[1] = (         void  *)IOT_HPLMN_CODE[i];
      sqlstm.sqhstl[1] = (unsigned int  )6;
      sqlstm.sqhsts[1] = (         int  )0;
      sqlstm.sqindv[1] = (         void  *)0;
      sqlstm.sqinds[1] = (         int  )0;
      sqlstm.sqharm[1] = (unsigned int  )0;
      sqlstm.sqadto[1] = (unsigned short )0;
      sqlstm.sqtdso[1] = (unsigned short )0;
      sqlstm.sqhstv[2] = (         void  *)IOT_VPLMN_CODE[i];
      sqlstm.sqhstl[2] = (unsigned int  )6;
      sqlstm.sqhsts[2] = (         int  )0;
      sqlstm.sqindv[2] = (         void  *)0;
      sqlstm.sqinds[2] = (         int  )0;
      sqlstm.sqharm[2] = (unsigned int  )0;
      sqlstm.sqadto[2] = (unsigned short )0;
      sqlstm.sqtdso[2] = (unsigned short )0;
      sqlstm.sqhstv[3] = (         void  *)IOT_PARTNER_CODE[i];
      sqlstm.sqhstl[3] = (unsigned int  )4;
      sqlstm.sqhsts[3] = (         int  )0;
      sqlstm.sqindv[3] = (         void  *)0;
      sqlstm.sqinds[3] = (         int  )0;
      sqlstm.sqharm[3] = (unsigned int  )0;
      sqlstm.sqadto[3] = (unsigned short )0;
      sqlstm.sqtdso[3] = (unsigned short )0;
      sqlstm.sqhstv[4] = (         void  *)IOT_FILE_TYPE_INDICATOR[i];
      sqlstm.sqhstl[4] = (unsigned int  )2;
      sqlstm.sqhsts[4] = (         int  )0;
      sqlstm.sqindv[4] = (         void  *)0;
      sqlstm.sqinds[4] = (         int  )0;
      sqlstm.sqharm[4] = (unsigned int  )0;
      sqlstm.sqadto[4] = (unsigned short )0;
      sqlstm.sqtdso[4] = (unsigned short )0;
      sqlstm.sqhstv[5] = (         void  *)&IOT_FILE_SEQUENCE_NUMBER[i];
      sqlstm.sqhstl[5] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[5] = (         int  )0;
      sqlstm.sqindv[5] = (         void  *)0;
      sqlstm.sqinds[5] = (         int  )0;
      sqlstm.sqharm[5] = (unsigned int  )0;
      sqlstm.sqadto[5] = (unsigned short )0;
      sqlstm.sqtdso[5] = (unsigned short )0;
      sqlstm.sqhstv[6] = (         void  *)&IOT_CALL_SEQUENCE[i];
      sqlstm.sqhstl[6] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[6] = (         int  )0;
      sqlstm.sqindv[6] = (         void  *)0;
      sqlstm.sqinds[6] = (         int  )0;
      sqlstm.sqharm[6] = (unsigned int  )0;
      sqlstm.sqadto[6] = (unsigned short )0;
      sqlstm.sqtdso[6] = (unsigned short )0;
      sqlstm.sqhstv[7] = (         void  *)&IOT_CALL_TYPE[i];
      sqlstm.sqhstl[7] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[7] = (         int  )0;
      sqlstm.sqindv[7] = (         void  *)0;
      sqlstm.sqinds[7] = (         int  )0;
      sqlstm.sqharm[7] = (unsigned int  )0;
      sqlstm.sqadto[7] = (unsigned short )0;
      sqlstm.sqtdso[7] = (unsigned short )0;
      sqlstm.sqhstv[8] = (         void  *)IOT_SERVICE_CODE[i];
      sqlstm.sqhstl[8] = (unsigned int  )4;
      sqlstm.sqhsts[8] = (         int  )0;
      sqlstm.sqindv[8] = (         void  *)0;
      sqlstm.sqinds[8] = (         int  )0;
      sqlstm.sqharm[8] = (unsigned int  )0;
      sqlstm.sqadto[8] = (unsigned short )0;
      sqlstm.sqtdso[8] = (unsigned short )0;
      sqlstm.sqhstv[9] = (         void  *)&IOT_IMSI[i];
      sqlstm.sqhstl[9] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[9] = (         int  )0;
      sqlstm.sqindv[9] = (         void  *)0;
      sqlstm.sqinds[9] = (         int  )0;
      sqlstm.sqharm[9] = (unsigned int  )0;
      sqlstm.sqadto[9] = (unsigned short )0;
      sqlstm.sqtdso[9] = (unsigned short )0;
      sqlstm.sqhstv[10] = (         void  *)IOT_MSISDN[i];
      sqlstm.sqhstl[10] = (unsigned int  )26;
      sqlstm.sqhsts[10] = (         int  )0;
      sqlstm.sqindv[10] = (         void  *)0;
      sqlstm.sqinds[10] = (         int  )0;
      sqlstm.sqharm[10] = (unsigned int  )0;
      sqlstm.sqadto[10] = (unsigned short )0;
      sqlstm.sqtdso[10] = (unsigned short )0;
      sqlstm.sqhstv[11] = (         void  *)IOT_CALLED_CALLING_NUMBER[i];
      sqlstm.sqhstl[11] = (unsigned int  )87;
      sqlstm.sqhsts[11] = (         int  )0;
      sqlstm.sqindv[11] = (         void  *)0;
      sqlstm.sqinds[11] = (         int  )0;
      sqlstm.sqharm[11] = (unsigned int  )0;
      sqlstm.sqadto[11] = (unsigned short )0;
      sqlstm.sqtdso[11] = (unsigned short )0;
      sqlstm.sqhstv[12] = (         void  *)IOT_DIALLED_DIGITS[i];
      sqlstm.sqhstl[12] = (unsigned int  )87;
      sqlstm.sqhsts[12] = (         int  )0;
      sqlstm.sqindv[12] = (         void  *)0;
      sqlstm.sqinds[12] = (         int  )0;
      sqlstm.sqharm[12] = (unsigned int  )0;
      sqlstm.sqadto[12] = (unsigned short )0;
      sqlstm.sqtdso[12] = (unsigned short )0;
      sqlstm.sqhstv[13] = (         void  *)IOT_CALL_DATE[i];
      sqlstm.sqhstl[13] = (unsigned int  )15;
      sqlstm.sqhsts[13] = (         int  )0;
      sqlstm.sqindv[13] = (         void  *)0;
      sqlstm.sqinds[13] = (         int  )0;
      sqlstm.sqharm[13] = (unsigned int  )0;
      sqlstm.sqadto[13] = (unsigned short )0;
      sqlstm.sqtdso[13] = (unsigned short )0;
      sqlstm.sqhstv[14] = (         void  *)&IOT_CALL_DURATION[i];
      sqlstm.sqhstl[14] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[14] = (         int  )0;
      sqlstm.sqindv[14] = (         void  *)0;
      sqlstm.sqinds[14] = (         int  )0;
      sqlstm.sqharm[14] = (unsigned int  )0;
      sqlstm.sqadto[14] = (unsigned short )0;
      sqlstm.sqtdso[14] = (unsigned short )0;
      sqlstm.sqhstv[15] = (         void  *)IOT_BASIC_SERVICE_TYPE[i];
      sqlstm.sqhstl[15] = (unsigned int  )2;
      sqlstm.sqhsts[15] = (         int  )0;
      sqlstm.sqindv[15] = (         void  *)0;
      sqlstm.sqinds[15] = (         int  )0;
      sqlstm.sqharm[15] = (unsigned int  )0;
      sqlstm.sqadto[15] = (unsigned short )0;
      sqlstm.sqtdso[15] = (unsigned short )0;
      sqlstm.sqhstv[16] = (         void  *)IOT_BASIC_SERVICE_CODE[i];
      sqlstm.sqhstl[16] = (unsigned int  )4;
      sqlstm.sqhsts[16] = (         int  )0;
      sqlstm.sqindv[16] = (         void  *)0;
      sqlstm.sqinds[16] = (         int  )0;
      sqlstm.sqharm[16] = (unsigned int  )0;
      sqlstm.sqadto[16] = (unsigned short )0;
      sqlstm.sqtdso[16] = (unsigned short )0;
      sqlstm.sqhstv[17] = (         void  *)IOT_CHARGED_ITEM[i];
      sqlstm.sqhstl[17] = (unsigned int  )4;
      sqlstm.sqhsts[17] = (         int  )0;
      sqlstm.sqindv[17] = (         void  *)0;
      sqlstm.sqinds[17] = (         int  )0;
      sqlstm.sqharm[17] = (unsigned int  )0;
      sqlstm.sqadto[17] = (unsigned short )0;
      sqlstm.sqtdso[17] = (unsigned short )0;
      sqlstm.sqhstv[18] = (         void  *)&IOT_CHARGEABLE_UNITS[i];
      sqlstm.sqhstl[18] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[18] = (         int  )0;
      sqlstm.sqindv[18] = (         void  *)0;
      sqlstm.sqinds[18] = (         int  )0;
      sqlstm.sqharm[18] = (unsigned int  )0;
      sqlstm.sqadto[18] = (unsigned short )0;
      sqlstm.sqtdso[18] = (unsigned short )0;
      sqlstm.sqhstv[19] = (         void  *)&IOT_CHARGED_UNITS[i];
      sqlstm.sqhstl[19] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[19] = (         int  )0;
      sqlstm.sqindv[19] = (         void  *)0;
      sqlstm.sqinds[19] = (         int  )0;
      sqlstm.sqharm[19] = (unsigned int  )0;
      sqlstm.sqadto[19] = (unsigned short )0;
      sqlstm.sqtdso[19] = (unsigned short )0;
      sqlstm.sqhstv[20] = (         void  *)&IOT_CHARGE[i];
      sqlstm.sqhstl[20] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[20] = (         int  )0;
      sqlstm.sqindv[20] = (         void  *)0;
      sqlstm.sqinds[20] = (         int  )0;
      sqlstm.sqharm[20] = (unsigned int  )0;
      sqlstm.sqadto[20] = (unsigned short )0;
      sqlstm.sqtdso[20] = (unsigned short )0;
      sqlstm.sqhstv[21] = (         void  *)&IOT_TAX_INFORMATION_COUNT[i];
      sqlstm.sqhstl[21] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[21] = (         int  )0;
      sqlstm.sqindv[21] = (         void  *)0;
      sqlstm.sqinds[21] = (         int  )0;
      sqlstm.sqharm[21] = (unsigned int  )0;
      sqlstm.sqadto[21] = (unsigned short )0;
      sqlstm.sqtdso[21] = (unsigned short )0;
      sqlstm.sqhstv[22] = (         void  *)&IOT_TAX_CODE[i];
      sqlstm.sqhstl[22] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[22] = (         int  )0;
      sqlstm.sqindv[22] = (         void  *)0;
      sqlstm.sqinds[22] = (         int  )0;
      sqlstm.sqharm[22] = (unsigned int  )0;
      sqlstm.sqadto[22] = (unsigned short )0;
      sqlstm.sqtdso[22] = (unsigned short )0;
      sqlstm.sqhstv[23] = (         void  *)&IOT_TAX_VALUE[i];
      sqlstm.sqhstl[23] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[23] = (         int  )0;
      sqlstm.sqindv[23] = (         void  *)0;
      sqlstm.sqinds[23] = (         int  )0;
      sqlstm.sqharm[23] = (unsigned int  )0;
      sqlstm.sqadto[23] = (unsigned short )0;
      sqlstm.sqtdso[23] = (unsigned short )0;
      sqlstm.sqhstv[24] = (         void  *)&IOT_TAXABLE_AMOUNT[i];
      sqlstm.sqhstl[24] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[24] = (         int  )0;
      sqlstm.sqindv[24] = (         void  *)0;
      sqlstm.sqinds[24] = (         int  )0;
      sqlstm.sqharm[24] = (unsigned int  )0;
      sqlstm.sqadto[24] = (unsigned short )0;
      sqlstm.sqtdso[24] = (unsigned short )0;
      sqlstm.sqhstv[25] = (         void  *)&IOT_DISCOUNT_INFORMATION_COUNT[i];
      sqlstm.sqhstl[25] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[25] = (         int  )0;
      sqlstm.sqindv[25] = (         void  *)0;
      sqlstm.sqinds[25] = (         int  )0;
      sqlstm.sqharm[25] = (unsigned int  )0;
      sqlstm.sqadto[25] = (unsigned short )0;
      sqlstm.sqtdso[25] = (unsigned short )0;
      sqlstm.sqhstv[26] = (         void  *)&IOT_DISCOUNT_CODE[i];
      sqlstm.sqhstl[26] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[26] = (         int  )0;
      sqlstm.sqindv[26] = (         void  *)0;
      sqlstm.sqinds[26] = (         int  )0;
      sqlstm.sqharm[26] = (unsigned int  )0;
      sqlstm.sqadto[26] = (unsigned short )0;
      sqlstm.sqtdso[26] = (unsigned short )0;
      sqlstm.sqhstv[27] = (         void  *)&IOT_DISCOUNT[i];
      sqlstm.sqhstl[27] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[27] = (         int  )0;
      sqlstm.sqindv[27] = (         void  *)0;
      sqlstm.sqinds[27] = (         int  )0;
      sqlstm.sqharm[27] = (unsigned int  )0;
      sqlstm.sqadto[27] = (unsigned short )0;
      sqlstm.sqtdso[27] = (unsigned short )0;
      sqlstm.sqhstv[28] = (         void  *)&IOT_DISCOUNTABLE_AMT[i];
      sqlstm.sqhstl[28] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[28] = (         int  )0;
      sqlstm.sqindv[28] = (         void  *)0;
      sqlstm.sqinds[28] = (         int  )0;
      sqlstm.sqharm[28] = (unsigned int  )0;
      sqlstm.sqadto[28] = (unsigned short )0;
      sqlstm.sqtdso[28] = (unsigned short )0;
      sqlstm.sqhstv[29] = (         void  *)&IOT_TAP_EXCHANGE_RATE[i];
      sqlstm.sqhstl[29] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[29] = (         int  )0;
      sqlstm.sqindv[29] = (         void  *)0;
      sqlstm.sqinds[29] = (         int  )0;
      sqlstm.sqharm[29] = (unsigned int  )0;
      sqlstm.sqadto[29] = (unsigned short )0;
      sqlstm.sqtdso[29] = (unsigned short )0;
      sqlstm.sqhstv[30] = (         void  *)&IOT_TAP_EXCHANGE_RATE_DECIMAL[i];
      sqlstm.sqhstl[30] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[30] = (         int  )0;
      sqlstm.sqindv[30] = (         void  *)0;
      sqlstm.sqinds[30] = (         int  )0;
      sqlstm.sqharm[30] = (unsigned int  )0;
      sqlstm.sqadto[30] = (unsigned short )0;
      sqlstm.sqtdso[30] = (unsigned short )0;
      sqlstm.sqhstv[31] = (         void  *)&IOT_CALL_TYPE_LEVEL1[i];
      sqlstm.sqhstl[31] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[31] = (         int  )0;
      sqlstm.sqindv[31] = (         void  *)0;
      sqlstm.sqinds[31] = (         int  )0;
      sqlstm.sqharm[31] = (unsigned int  )0;
      sqlstm.sqadto[31] = (unsigned short )0;
      sqlstm.sqtdso[31] = (unsigned short )0;
      sqlstm.sqhstv[32] = (         void  *)&IOT_DATA_VOLUME_INCOMING[i];
      sqlstm.sqhstl[32] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[32] = (         int  )0;
      sqlstm.sqindv[32] = (         void  *)0;
      sqlstm.sqinds[32] = (         int  )0;
      sqlstm.sqharm[32] = (unsigned int  )0;
      sqlstm.sqadto[32] = (unsigned short )0;
      sqlstm.sqtdso[32] = (unsigned short )0;
      sqlstm.sqhstv[33] = (         void  *)&IOT_DATA_VOLUME_OUTGOING[i];
      sqlstm.sqhstl[33] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[33] = (         int  )0;
      sqlstm.sqindv[33] = (         void  *)0;
      sqlstm.sqinds[33] = (         int  )0;
      sqlstm.sqharm[33] = (unsigned int  )0;
      sqlstm.sqadto[33] = (unsigned short )0;
      sqlstm.sqtdso[33] = (unsigned short )0;
      sqlstm.sqhstv[34] = (         void  *)&IOT_HOME_CURNCY_CHARGE[i];
      sqlstm.sqhstl[34] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[34] = (         int  )0;
      sqlstm.sqindv[34] = (         void  *)0;
      sqlstm.sqinds[34] = (         int  )0;
      sqlstm.sqharm[34] = (unsigned int  )0;
      sqlstm.sqadto[34] = (unsigned short )0;
      sqlstm.sqtdso[34] = (unsigned short )0;
      sqlstm.sqhstv[35] = (         void  *)&IOT_HOME_CURNCY_TAX[i];
      sqlstm.sqhstl[35] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[35] = (         int  )0;
      sqlstm.sqindv[35] = (         void  *)0;
      sqlstm.sqinds[35] = (         int  )0;
      sqlstm.sqharm[35] = (unsigned int  )0;
      sqlstm.sqadto[35] = (unsigned short )0;
      sqlstm.sqtdso[35] = (unsigned short )0;
      sqlstm.sqhstv[36] = (         void  *)&IOT_HOME_CURNCY_DISCOUNT[i];
      sqlstm.sqhstl[36] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[36] = (         int  )0;
      sqlstm.sqindv[36] = (         void  *)0;
      sqlstm.sqinds[36] = (         int  )0;
      sqlstm.sqharm[36] = (unsigned int  )0;
      sqlstm.sqadto[36] = (unsigned short )0;
      sqlstm.sqtdso[36] = (unsigned short )0;
      sqlstm.sqhstv[37] = (         void  *)&IOT_CAMEL_INVOCATION_FEE[i];
      sqlstm.sqhstl[37] = (unsigned int  )sizeof(double);
      sqlstm.sqhsts[37] = (         int  )0;
      sqlstm.sqindv[37] = (         void  *)0;
      sqlstm.sqinds[37] = (         int  )0;
      sqlstm.sqharm[37] = (unsigned int  )0;
      sqlstm.sqadto[37] = (unsigned short )0;
      sqlstm.sqtdso[37] = (unsigned short )0;
      sqlstm.sqhstv[38] = (         void  *)&CDR_ERROR_FLAG[i];
      sqlstm.sqhstl[38] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[38] = (         int  )0;
      sqlstm.sqindv[38] = (         void  *)0;
      sqlstm.sqinds[38] = (         int  )0;
      sqlstm.sqharm[38] = (unsigned int  )0;
      sqlstm.sqadto[38] = (unsigned short )0;
      sqlstm.sqtdso[38] = (unsigned short )0;
      sqlstm.sqhstv[39] = (         void  *)IOT_CHARGE_CONTEXT[i];
      sqlstm.sqhstl[39] = (unsigned int  )80;
      sqlstm.sqhsts[39] = (         int  )0;
      sqlstm.sqindv[39] = (         void  *)0;
      sqlstm.sqinds[39] = (         int  )0;
      sqlstm.sqharm[39] = (unsigned int  )0;
      sqlstm.sqadto[39] = (unsigned short )0;
      sqlstm.sqtdso[39] = (unsigned short )0;
      sqlstm.sqhstv[40] = (         void  *)IOT_TAX_CONTEXT[i];
      sqlstm.sqhstl[40] = (unsigned int  )80;
      sqlstm.sqhsts[40] = (         int  )0;
      sqlstm.sqindv[40] = (         void  *)0;
      sqlstm.sqinds[40] = (         int  )0;
      sqlstm.sqharm[40] = (unsigned int  )0;
      sqlstm.sqadto[40] = (unsigned short )0;
      sqlstm.sqtdso[40] = (unsigned short )0;
      sqlstm.sqhstv[41] = (         void  *)IOT_DISCOUNT_CONTEXT[i];
      sqlstm.sqhstl[41] = (unsigned int  )80;
      sqlstm.sqhsts[41] = (         int  )0;
      sqlstm.sqindv[41] = (         void  *)0;
      sqlstm.sqinds[41] = (         int  )0;
      sqlstm.sqharm[41] = (unsigned int  )0;
      sqlstm.sqadto[41] = (unsigned short )0;
      sqlstm.sqtdso[41] = (unsigned short )0;
      sqlstm.sqhstv[42] = (         void  *)&IOT_ERROR_NODE[i];
      sqlstm.sqhstl[42] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[42] = (         int  )0;
      sqlstm.sqindv[42] = (         void  *)0;
      sqlstm.sqinds[42] = (         int  )0;
      sqlstm.sqharm[42] = (unsigned int  )0;
      sqlstm.sqadto[42] = (unsigned short )0;
      sqlstm.sqtdso[42] = (unsigned short )0;
      sqlstm.sqphsv = sqlstm.sqhstv;
      sqlstm.sqphsl = sqlstm.sqhstl;
      sqlstm.sqphss = sqlstm.sqhsts;
      sqlstm.sqpind = sqlstm.sqindv;
      sqlstm.sqpins = sqlstm.sqinds;
      sqlstm.sqparm = sqlstm.sqharm;
      sqlstm.sqparc = sqlstm.sqharc;
      sqlstm.sqpadto = sqlstm.sqadto;
      sqlstm.sqptdso = sqlstm.sqtdso;
      sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



      if(ERRCODE!=0)
      {
         TRACEENTRY(1,"%s","Error Inserting the below Record into PM_TMP_TAP_CDRS table");
         TRACEENTRY(1,"%s -%d-","ERROR : sqlca.sqlcode :",ERRCODE);

         Index = i+1;

         TRACEENTRY(1,"%s","String Values Below ------------------");
         TRACEENTRY(1,"FILE_TRANSFER_DIRECTION         : -%d- -%s-",Index,IOT_FILE_TRANSFER_DIRECTION[i]);
         TRACEENTRY(1,"SERVICE_CODE                    : -%d- -%s-",Index,IOT_SERVICE_CODE[i]);
         TRACEENTRY(1,"HPLMN_CODE                      : -%d- -%s-",Index,IOT_HPLMN_CODE[i]);
         TRACEENTRY(1,"VPLMN_CODE                      : -%d- -%s-",Index,IOT_VPLMN_CODE[i]);
         TRACEENTRY(1,"PARTNER_CODE                    : -%d- -%s-",Index,IOT_PARTNER_CODE[i]);
         TRACEENTRY(1,"FILE_TYPE_INDICATOR             : -%d- -%s-",Index,IOT_FILE_TYPE_INDICATOR[i]);
         TRACEENTRY(1,"SERVICE_CODE                    : -%d- -%s-",Index,IOT_SERVICE_CODE[i]);
         TRACEENTRY(1,"MSISDN                          : -%d- -%s-",Index,IOT_MSISDN[i]);
         TRACEENTRY(1,"CALLED_CALLING_NUMBER           : -%d- -%s-",Index,IOT_CALLED_CALLING_NUMBER[i]);
         TRACEENTRY(1,"DIALLED_DIGITS                  : -%d- -%s-",Index,IOT_DIALLED_DIGITS[i]);
         TRACEENTRY(1,"CALL_DATE                       : -%d- -%s-",Index,IOT_CALL_DATE[i]);
         TRACEENTRY(1,"CHARGED_ITEM                    : -%d- -%s-",Index,IOT_CHARGED_ITEM[i]);
         TRACEENTRY(1,"BASIC_SERVICE_TYPE              : -%d- -%s-",Index,IOT_BASIC_SERVICE_TYPE[i]);
         TRACEENTRY(1,"BASIC_SERVICE_CODE              : -%d- -%s-",Index,IOT_BASIC_SERVICE_CODE[i]);
	 TRACEENTRY(1,"IOT_CHARGE_CONTEXT              : -%d- -%s-",Index,IOT_CHARGE_CONTEXT[i]);
         TRACEENTRY(1,"IOT_TAX_CONTEXT                 : -%d- -%s-",Index,IOT_TAX_CONTEXT[i]);
         TRACEENTRY(1,"IOT_DISCOUNT_CONTEXT            : -%d- -%s-",Index,IOT_DISCOUNT_CONTEXT[i]);

         TRACEENTRY(1,"%s","Number Values Below ------------------");
         TRACEENTRY(1,"FILE_SEQUENCE_NUMBER            : -%d- -%d-",Index,IOT_FILE_SEQUENCE_NUMBER[i]);
         TRACEENTRY(1,"CALL_SEQUENCE                   : -%d- -%f-",Index,IOT_CALL_SEQUENCE[i]);
         TRACEENTRY(1,"CALL_TYPE                       : -%d- -%d-",Index,IOT_CALL_TYPE[i]);
         TRACEENTRY(1,"IMSI                            : -%d- -%f-",Index,IOT_IMSI[i]);
         TRACEENTRY(1,"CALL_DURATION                   : -%d- -%f-",Index,IOT_CALL_DURATION[i]);
         TRACEENTRY(1,"CHARGEABLE_UNITS                : -%d- -%f-",Index,IOT_CHARGEABLE_UNITS[i]);
         TRACEENTRY(1,"CHARGED_UNITS                   : -%d- -%f-",Index,IOT_CHARGED_UNITS[i]);
         TRACEENTRY(1,"CHARGE                          : -%d- -%f-",Index,IOT_CHARGE[i]);
         TRACEENTRY(1,"TAX_INFORMATION_COUNT           : -%d- -%d-",Index,IOT_TAX_INFORMATION_COUNT[i]);
         TRACEENTRY(1,"TAX_CODE                        : -%d- -%d-",Index,IOT_TAX_CODE[i]);
         TRACEENTRY(1,"TAX_VALUE                       : -%d- -%f-",Index,IOT_TAX_VALUE[i]);
         TRACEENTRY(1,"TAXABLE_AMOUNT                  : -%d- -%f-",Index,IOT_TAXABLE_AMOUNT[i]);
         TRACEENTRY(1,"DISCOUNT_INFORMATION_COUNT      : -%d- -%d-",Index,IOT_DISCOUNT_INFORMATION_COUNT[i]);
         TRACEENTRY(1,"DISCOUNT_CODE                   : -%d- -%d-",Index,IOT_DISCOUNT_CODE[i]);
         TRACEENTRY(1,"DISCOUNT                        : -%d- -%f-",Index,IOT_DISCOUNT[i]);
         TRACEENTRY(1,"DISCOUNTABLE_AMT                : -%d- -%f-",Index,IOT_DISCOUNTABLE_AMT[i]);
         TRACEENTRY(1,"TAP_EXCHANGE_RATE               : -%d- -%f-",Index,IOT_TAP_EXCHANGE_RATE[i]);
         TRACEENTRY(1,"TAP_EXCHANGE_RATE_DECIMAL       : -%d- -%d-",Index,IOT_TAP_EXCHANGE_RATE_DECIMAL[i]);
         TRACEENTRY(1,"CALL_TYPE_LEVEL1                : -%d- -%d-",Index,IOT_CALL_TYPE_LEVEL1[i]);
         TRACEENTRY(1,"DATA_VOLUME_INCOMING            : -%d- -%f-",Index,IOT_DATA_VOLUME_INCOMING[i]);
         TRACEENTRY(1,"DATA_VOLUME_OUTGOING            : -%d- -%f-",Index,IOT_DATA_VOLUME_OUTGOING[i]);
         TRACEENTRY(1,"HOME_CURNCY_CHARGE              : -%d- -%f-",Index,IOT_HOME_CURNCY_CHARGE[i]);
         TRACEENTRY(1,"HOME_CURNCY_TAX                 : -%d- -%f-",Index,IOT_HOME_CURNCY_TAX[i]);
         TRACEENTRY(1,"HOME_CURNCY_DISCOUNT            : -%d- -%f-",Index,IOT_HOME_CURNCY_DISCOUNT[i]);
         TRACEENTRY(1,"CAMEL_INVOCATION_FEE            : -%d- -%f-",Index,IOT_CAMEL_INVOCATION_FEE[i]);
         TRACEENTRY(1,"CDR_ERROR_FLAG                  : -%d- -%d-",Index,CDR_ERROR_FLAG[i]);
         TRACEENTRY(1,"ERROR_NODE                      : -%d- -%d-",Index,IOT_ERROR_NODE[i]);
      }
   }

}

void InitialiseTAPFileSummary()
{
	INIT_STR(FileSummary.FILE_TRANSFER_DIRECTION);
        INIT_STR(FileSummary.HPLMN_CODE);
	INIT_STR(FileSummary.VPLMN_CODE);
	INIT_STR(FileSummary.FILE_TYPE_INDICATOR);
	FileSummary.FILE_SEQUENCE_NUMBER		= 0;
	INIT_STR(FileSummary.FILE_NAME);
	INIT_STR(FileSummary.DATA_TYPE_INDICATOR);
	INIT_STR(FileSummary.CALLS_TYPE_INDICATOR);
	INIT_STR(FileSummary.FILE_CREATION_TIME);
	INIT_STR(FileSummary.FILE_CREATION_TIME_UTC_OFFSET);
	INIT_STR(FileSummary.FILE_TRANSFER_TIME);
	INIT_STR(FileSummary.FILE_TRANSFER_TIME_UTC_OFFSET);
	INIT_STR(FileSummary.FILE_AVAILABLE_TIME);
	INIT_STR(FileSummary.FILE_AVAILABLE_TIME_UTC_OFFSET);
	FileSummary.TAP_SPECIFICATION_VERSION		= 0;
	FileSummary.TAP_RELEASE_VERSION			= 0;
	INIT_STR(FileSummary.ISO_PLMN_CURNCY_CODE);
	INIT_STR(FileSummary.TAP_CURNCY_CODE);
	FileSummary.TAP_CURNCY_DECIMAL_PLACES		= 0;
	FileSummary.TAP_CURNCY_MULT_FACT		= 0;
	FileSummary.TAP_CURNCY_ROUNDOFF_DECIMAL		= 0;
	FileSummary.HOME_CURNCY_ROUNDOFF_DECIMAL	= 0;
	INIT_STR(FileSummary.FILE_PROCESS_DATE);
	INIT_STR(FileSummary.FILE_PROCESSED_BY_USER_ID);
	INIT_STR(FileSummary.FILE_PROCESS_STATUS);
	INIT_STR(FileSummary.EARLIEST_CALL_TIME);
	INIT_STR(FileSummary.EARLIEST_CALL_TIME_UTC_OFFSET);
	INIT_STR(FileSummary.LATEST_CALL_TIME);
        INIT_STR(FileSummary.LATEST_CALL_TIME_UTC_OFFSET);
        FileSummary.TOTAL_CALL_EVENTS			= 0;
        FileSummary.TOTAL_CALL_EVENTS_PROCESSED		= 0;
        FileSummary.TOTAL_PREPAID_CALL_EVENTS		= 0;
        FileSummary.TOTAL_POSTPAID_CALL_EVENTS		= 0;
        FileSummary.TOTAL_DURATION			= 0;
        FileSummary.TOTAL_OUTGOING_VOLUME		= 0;
        FileSummary.TOTAL_INCOMING_VOLUME		= 0;
        FileSummary.TAP_CURNCY_CHARGE			= 0;
        FileSummary.TAP_CURNCY_TAX			= 0;
        FileSummary.TAP_CURNCY_DISCOUNT			= 0;
        FileSummary.HOME_CURNCY_CHARGE			= 0;
        FileSummary.HOME_CURNCY_TAX			= 0;
        FileSummary.HOME_CURNCY_DISCOUNT		= 0;
        FileSummary.HOME_CURNCY_SURCHARGE		= 0;
        FileSummary.SURCHARGE_PERCENTAGE		= 0;
        FileSummary.REJECTED_CALL_EVENTS                = 0;
        FileSummary.REJECTED_DURATION                   = 0;
        FileSummary.REJECTED_OUTGOING_VOLUME            = 0;
        FileSummary.REJECTED_INCOMING_VOLUME            = 0;
        FileSummary.REJECTED_TAP_CURNCY_CHARGE          = 0;
        FileSummary.REJECTED_HOME_CURNCY_CHARGE         = 0;
        FileSummary.SETTLEMENT_CALL_EVENTS		= 0;
        FileSummary.SETTLEMENT_DURATION			= 0;
        FileSummary.SETTLEMENT_OUTGOING_VOLUME		= 0;
        FileSummary.SETTLEMENT_INCOMING_VOLUME		= 0;
        FileSummary.SETTLEMENT_TAP_CURNCY_CHARGE	= 0;
        FileSummary.SETTLEMENT_TAP_CURNCY_TAX		= 0;
        FileSummary.SETTLEMENT_TAP_CURNCY_DISCOUNT	= 0;
        FileSummary.SETTLEMENT_LOCAL_CHARGE		= 0;
        FileSummary.SETTLEMENT_LOCAL_TAX		= 0;
        FileSummary.SETTLEMENT_LOCAL_DISCOUNT		= 0;
        FileSummary.YEAR_MONTH				= 0;
        INIT_STR(FileSummary.PARTNER_CODE);
        FileSummary.UTC_OFFSET_COUNT                    = 0;
        FileSummary.REC_ENTITY_COUNT                    = 0;
        FileSummary.TAX_COUNT                           = 0;
        FileSummary.DISCOUNT_COUNT                      = 0;
        FileSummary.CURRENCY_COUNT                      = 0;
        INIT_STR(FileSummary.RAP_FILE_NAME);
        FileSummary.RAP_FILE_SEQUENCE_NUMBER            = 0;         
        FileSummary.RAP_SPECIFICATION_VERSION           = 0; 
        FileSummary.RAP_RELEASE_VERSION                 = 0;
        INIT_STR(FileSummary.FILE_CLEARING_STATUS) ;
}


void InitialiseRAPFileSummary()
{
	INIT_STR(RAPFileSummary.FILE_TRANSFER_DIRECTION)               ;
        INIT_STR(RAPFileSummary.HPLMN_CODE)                            ;
	INIT_STR(RAPFileSummary.VPLMN_CODE)                            ;
	INIT_STR(RAPFileSummary.FILE_TYPE_INDICATOR)                   ;
	RAPFileSummary.FILE_SEQUENCE_NUMBER		            = 0;
	INIT_STR(RAPFileSummary.RAP_FILE_NAME)                         ;
	INIT_STR(RAPFileSummary.TAP_FILE_NAME)                         ;
	INIT_STR(RAPFileSummary.DATA_TYPE_INDICATOR)                   ;
	INIT_STR(RAPFileSummary.FILE_CREATION_TIME)                    ;
	INIT_STR(RAPFileSummary.FILE_CREATION_TIME_UTC_OFFSET)         ;
	INIT_STR(RAPFileSummary.FILE_AVAILABLE_TIME)                   ;
	INIT_STR(RAPFileSummary.FILE_AVAILABLE_TIME_UTC_OFFSET)        ;
        RAPFileSummary.TOTAL_ERROR_COUNT			    = 0;
        INIT_STR(RAPFileSummary.ERROR_TYPE)                            ;
        RAPFileSummary.START_MISSING_SEQ_NO                         = 0;
        RAPFileSummary.END_MISSING_SEQ_NO                           = 0;
	RAPFileSummary.RAP_SPECIFICATION_VERSION		    = 0;
	RAPFileSummary.RAP_RELEASE_VERSION			    = 0;
	RAPFileSummary.TAP_SPECIFICATION_VERSION		    = 0;
	RAPFileSummary.TAP_RELEASE_VERSION			    = 0;
	INIT_STR(RAPFileSummary.ISO_PLMN_CURNCY_CODE)                  ;
	INIT_STR(RAPFileSummary.TAP_CURNCY_CODE)                       ;
	RAPFileSummary.TAP_CURNCY_DECIMAL_PLACES		    = 0;
	RAPFileSummary.TAP_CURNCY_MULT_FACT		            = 0;
	RAPFileSummary.TAP_CURNCY_ROUNDOFF_DECIMAL		    = 0;
	RAPFileSummary.HOME_CURNCY_ROUNDOFF_DECIMAL	            = 0;
	INIT_STR(RAPFileSummary.FILE_PROCESS_DATE)                     ;
	INIT_STR(RAPFileSummary.FILE_PROCESSED_BY)                     ;
	INIT_STR(RAPFileSummary.FILE_PROCESS_STATUS)                   ;
        RAPFileSummary.TOTAL_CALL_EVENTS			    = 0;
        RAPFileSummary.TOTAL_CALL_EVENTS_PROCESSED		    = 0;
        RAPFileSummary.TOTAL_DURATION			            = 0;
        RAPFileSummary.TOTAL_OUTGOING_VOLUME		            = 0;
        RAPFileSummary.TOTAL_INCOMING_VOLUME		            = 0;
        RAPFileSummary.TAP_CURNCY_CHARGE			    = 0;
        RAPFileSummary.TAP_CURNCY_TAX			            = 0;
        RAPFileSummary.TAP_CURNCY_DISCOUNT			    = 0;
        RAPFileSummary.HOME_CURNCY_CHARGE			    = 0;
        RAPFileSummary.HOME_CURNCY_TAX			            = 0;
        RAPFileSummary.HOME_CURNCY_DISCOUNT		            = 0;
        RAPFileSummary.HOME_CURNCY_SURCHARGE		            = 0;
        RAPFileSummary.SURCHARGE_PERCENTAGE		            = 0;
        INIT_STR(RAPFileSummary.PARTNER_CODE)                          ;
        RAPFileSummary.REJECTED_CALL_EVENTS                         = 0;
        RAPFileSummary.REJECTED_DURATION                            = 0;
        RAPFileSummary.REJECTED_OUTGOING_VOLUME                     = 0;
        RAPFileSummary.REJECTED_INCOMING_VOLUME                     = 0;
        INIT_STR(RAPFileSummary.RAP_ACKNOWLEDGEMENT_STATUS)            ;
        RAPFileSummary.REJ_TAP_CURNCY_CHARGE                        = 0;
        RAPFileSummary.REJ_TAP_CURNCY_TAX                           = 0;
        RAPFileSummary.REJ_TAP_CURNCY_DISCOUNT                      = 0;
        RAPFileSummary.REJ_HOME_CURNCY_CHARGE                       = 0;
        RAPFileSummary.REJ_HOME_CURNCY_TAX                          = 0;
        RAPFileSummary.REJ_HOME_CURNCY_DISCOUNT                     = 0;
        INIT_STR(RAPFileSummary.FILE_TYPE_GENERATION)                  ;


        gBulkCDRIndex             = 0;
        gTotalCdrsCount           = 0;
        gProcessingCDRNo          = 0;
        gRejectedErrorNo          = 0;
        gErrorCDRsCount           = 0;
        gErrorCDRsCharge          = 0;
        gErrorCDRsLocalCharge     = 0;
        gErrorCDRsTax             = 0;
        gErrorCDRsDiscount        = 0;
        gErrorCDRsDuration        = 0;
        gErrorCDRsIncVolume       = 0;
        gErrorCDRsOutVolume       = 0;

}


void InitialiseTAPErrorSummary()
{
   int i = 0 ;   
  
   for(i=0; i< REJECTEDCDRS; i++)
   {
       REI.ERROR_CODE[i]  = 0                 ;
       INIT_STR(REI.ERROR_TYPE[i])            ;
       INIT_STR(REI.ERROR_CONTEXT_DETAILS[i]) ;
       INIT_STR(REI.ERROR_VALUE[i])           ;
       REI.APPLICATION_TAG[i] = 0             ;
       INIT_STR(REI.CONTEXT_NAME[i])          ;
       INIT_STR(REI.ERROR_FIELD_NAME[i])      ;
       INIT_STR(REI.ERROR_MESSAGE[i])         ;
   }
}



void SetFileSummary()
{
   char temp[15];

   /* Set the FileSummary with Details from BatchControlInformation */
   strcpy(FileSummary.FILE_TRANSFER_DIRECTION,"I");
   strcpy(FileSummary.HPLMN_CODE,BCI.Recipient);
   strcpy(FileSummary.VPLMN_CODE,BCI.Sender);
   strcpy(FileSummary.FILE_TYPE_INDICATOR,BCI.FileTypeIndicator);
   FileSummary.FILE_SEQUENCE_NUMBER = BCI.FileSequenceNumber; 
   strcpy(FileSummary.FILE_NAME," ");
   strcpy(FileSummary.DATA_TYPE_INDICATOR,gDataTypeIndicator);
   strcpy(FileSummary.CALLS_TYPE_INDICATOR,"N");

   strcpy(FileSummary.FILE_CREATION_TIME,BCI.FileCreationTimeStamp.LocalTimeStamp);
   strcpy(FileSummary.FILE_CREATION_TIME_UTC_OFFSET,BCI.FileCreationTimeStamp.UtcTimeOffset);
   strcpy(FileSummary.FILE_TRANSFER_TIME,BCI.TransferCutOffTimeStamp.LocalTimeStamp);
   strcpy(FileSummary.FILE_TRANSFER_TIME_UTC_OFFSET,BCI.TransferCutOffTimeStamp.UtcTimeOffset);
   strcpy(FileSummary.FILE_AVAILABLE_TIME,BCI.FileAvailableTimeStamp.LocalTimeStamp);
   strcpy(FileSummary.FILE_AVAILABLE_TIME_UTC_OFFSET,BCI.FileAvailableTimeStamp.UtcTimeOffset);
   FileSummary.TAP_SPECIFICATION_VERSION           = BCI.SpecificationVersionNumber;
   FileSummary.TAP_RELEASE_VERSION                 = BCI.ReleaseVersionNumber;

   strcpy(FileSummary.FILE_PROCESS_DATE,gSystemDate);
   strcpy(FileSummary.FILE_PROCESSED_BY_USER_ID,"Backend");
   strcpy(FileSummary.FILE_PROCESS_STATUS,"S");
   strcpy(RAPFileSummary.FILE_TYPE_GENERATION,"A");

   /* Set the Below Details Only for Notification File */
   if(strcmp(FileSummary.DATA_TYPE_INDICATOR,"D")==0)
   {
      /* Set the FileSummary with Details from AccountingInformation */
      strcpy(FileSummary.ISO_PLMN_CURNCY_CODE,ACC.LocalCurrency);
      if(ACC.TapCurrency[0]=='\0')
      {
         strcpy(FileSummary.TAP_CURNCY_CODE,"SDR");
      }
      else
      {
         strcpy(FileSummary.TAP_CURNCY_CODE,ACC.TapCurrency);
      }

      FileSummary.TAP_CURNCY_DECIMAL_PLACES           = ACC.TapDecimalPlaces;
      FileSummary.TAP_CURNCY_MULT_FACT                = pow(10,ACC.TapDecimalPlaces);
      FileSummary.TAP_CURNCY_ROUNDOFF_DECIMAL         = 0;

      /* Set the FileSummary with AuditControlInformation */
      strcpy(FileSummary.EARLIEST_CALL_TIME,ACI.EarliestCallTimeStamp.LocalTimeStamp);
      strcpy(FileSummary.EARLIEST_CALL_TIME_UTC_OFFSET,ACI.EarliestCallTimeStamp.UtcTimeOffset);
      strcpy(FileSummary.LATEST_CALL_TIME,ACI.LatestCallTimeStamp.LocalTimeStamp);
      strcpy(FileSummary.LATEST_CALL_TIME_UTC_OFFSET,ACI.LatestCallTimeStamp.UtcTimeOffset);
      FileSummary.TOTAL_CALL_EVENTS                   = ACI.CallEventDetailsCount;
      FileSummary.TOTAL_CALL_EVENTS_PROCESSED         = ACI.CallEventDetailsCount - gErrorCDRsCount;
      FileSummary.TOTAL_PREPAID_CALL_EVENTS           = 0;
      FileSummary.TOTAL_POSTPAID_CALL_EVENTS          = 0;
      /* FileSummary.TOTAL_OUTGOING_VOLUME               = 0;
         FileSummary.TOTAL_INCOMING_VOLUME               = 0; */

     /*
      FileSummary.TOTAL_DURATION                      = FileSummary.TOTAL_DURATION + gErrorCDRsDuration;
      FileSummary.TOTAL_OUTGOING_VOLUME               = FileSummary.TOTAL_OUTGOING_VOLUME + gErrorCDRsOutVolume;
      FileSummary.TOTAL_INCOMING_VOLUME               = FileSummary.TOTAL_INCOMING_VOLUME + gErrorCDRsIncVolume;
     */

      FileSummary.TAP_CURNCY_CHARGE                   = ACI.TotalCharge;
      FileSummary.TAP_CURNCY_TAX                      = ACI.TotalTaxValue;
      FileSummary.TAP_CURNCY_DISCOUNT                 = ACI.TotalDiscountValue;

      FileSummary.SURCHARGE_PERCENTAGE                = stPartnerInfo.TAPIN_SURCHARGE_RATE;


      FileSummary.REJECTED_CALL_EVENTS                = gErrorCDRsCount;
      FileSummary.REJECTED_DURATION                   = gErrorCDRsDuration;
      FileSummary.REJECTED_OUTGOING_VOLUME            = gErrorCDRsOutVolume;
      FileSummary.REJECTED_INCOMING_VOLUME            = gErrorCDRsIncVolume;
      FileSummary.REJECTED_TAP_CURNCY_CHARGE          = gErrorCDRsCharge;
      FileSummary.REJECTED_HOME_CURNCY_CHARGE         = gErrorCDRsLocalCharge;

      FileSummary.SETTLEMENT_CALL_EVENTS              = FileSummary.TOTAL_CALL_EVENTS_PROCESSED;
/*
      FileSummary.SETTLEMENT_OUTGOING_VOLUME          = FileSummary.TOTAL_OUTGOING_VOLUME ;
      FileSummary.SETTLEMENT_INCOMING_VOLUME          = FileSummary.TOTAL_INCOMING_VOLUME;
*/
      FileSummary.SETTLEMENT_TAP_CURNCY_CHARGE        = FileSummary.TAP_CURNCY_CHARGE - gErrorCDRsCharge;
      FileSummary.SETTLEMENT_TAP_CURNCY_TAX           = FileSummary.TAP_CURNCY_TAX - gErrorCDRsTax;
      FileSummary.SETTLEMENT_TAP_CURNCY_DISCOUNT      = FileSummary.TAP_CURNCY_DISCOUNT - gErrorCDRsDiscount;

      FileSummary.YEAR_MONTH                          = 0;
      FileSummary.UTC_OFFSET_COUNT                    = gUTCOffsetCount;
      FileSummary.REC_ENTITY_COUNT                    = gRecEntityInfoCount;
      FileSummary.TAX_COUNT                           = gTaxationCount;
      FileSummary.DISCOUNT_COUNT                      = gDiscountingCount;
      FileSummary.CURRENCY_COUNT                      = gExchangeRateCount;

      if(gSevereErrorCount > 0)
      {
         strcpy(FileSummary.RAP_FILE_NAME, RAPFileSummary.RAP_FILE_NAME) ;
         FileSummary.RAP_FILE_SEQUENCE_NUMBER         = RAPFileSummary.FILE_SEQUENCE_NUMBER ;
         FileSummary.RAP_SPECIFICATION_VERSION        = RAPFileSummary.RAP_SPECIFICATION_VERSION;
         FileSummary.RAP_RELEASE_VERSION              = RAPFileSummary.RAP_RELEASE_VERSION;
         strcpy(FileSummary.FILE_CLEARING_STATUS,"P") ;
      }

      if(FileSummary.TOTAL_CALL_EVENTS_PROCESSED == 0)
      {
        strcpy(gDataTypeIndicator,"N") ;
        strcpy(FileSummary.DATA_TYPE_INDICATOR,gDataTypeIndicator);
      }

   }

}


void SetRAPFileSummary()
{
   
   int k = 0;
   INIT_STR(gRapFileCreationTime) ;

   /* EXEC SQL SELECT TO_CHAR(CURRENT_TIMESTAMP,'YYYYMMDDHH24MISS') INTO :gRapFileCreationTime FROM DUAL ; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 129;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select TO_CHAR(CURRENT_TIMESTAMP,'YYYYMMDDHH24MISS') into \
:b0  from DUAL ";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )4866;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)gRapFileCreationTime;
   sqlstm.sqhstl[0] = (unsigned int  )15;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   /* Set the RAP FileSummary with Details from BatchControlInformation */
   strcpy(RAPFileSummary.FILE_TRANSFER_DIRECTION,"O");
   strcpy(RAPFileSummary.HPLMN_CODE,stRoamingPref.HPLMN_CODE);
   strcpy(RAPFileSummary.VPLMN_CODE,BCI.Sender);
   strcpy(RAPFileSummary.FILE_TYPE_INDICATOR,BCI.FileTypeIndicator);
   RAPFileSummary.FILE_SEQUENCE_NUMBER = gRapFileSequenceNumber;

/*   k=0;
   for(k=0;k<gRAPPartnerCount;k++)
   {
       ptRAPPartners2 = (ptRAPPartners1 + k);
       if((strcmp(BCI.Sender,ptRAPPartners2->PARTNER_SHORT_CODE)==0) && (strcmp(BCI.FileTypeIndicator,ptRAPPartners2->DATA_TYPE) == 0))
       {
          strcpy(RAPFileSummary.PARTNER_CODE,ptRAPPartners2->PARTNER_CODE);
          RAPFileSummary.FILE_SEQUENCE_NUMBER = ptRAPPartners2->FILE_SEQUENCE_NUMBER ;
          break;
       }
   }
*/

/*
   sprintf(RAPFileSummary.RAP_FILE_NAME,"%1s%1s%5s%5s%05d","R",BCI.FileTypeIndicator,stRoamingPref.HPLMN_CODE,BCI.Sender,RAPFileSummary.FILE_SEQUENCE_NUMBER);
*/
   strcpy(RAPFileSummary.RAP_FILE_NAME,gRAPFileName) ;
   strcpy(RAPFileSummary.TAP_FILE_NAME," ");
   strcpy(RAPFileSummary.DATA_TYPE_INDICATOR,"D");

   strcpy(RAPFileSummary.FILE_CREATION_TIME_UTC_OFFSET,stRoamingPref.UTC_OFFSET);
   strcpy(RAPFileSummary.FILE_AVAILABLE_TIME_UTC_OFFSET,stRoamingPref.UTC_OFFSET);
   RAPFileSummary.RAP_SPECIFICATION_VERSION           = stRoamingPref.RAP_SPECIFICATION_VERSION;
   RAPFileSummary.RAP_RELEASE_VERSION                 = stRoamingPref.RAP_RELEASE_VERSION;
   RAPFileSummary.TAP_SPECIFICATION_VERSION           = BCI.SpecificationVersionNumber;
   RAPFileSummary.TAP_RELEASE_VERSION                 = BCI.ReleaseVersionNumber;

   strcpy(RAPFileSummary.FILE_PROCESSED_BY,"Backend");
   strcpy(RAPFileSummary.FILE_PROCESS_STATUS,"S");
   strcpy(RAPFileSummary.RAP_ACKNOWLEDGEMENT_STATUS,"N");
   
   if(gFatalErrorCount>0)
   {
      strcpy(RAPFileSummary.ERROR_TYPE,"FATAL") ;
      RAPFileSummary.TOTAL_ERROR_COUNT = gFatalErrorCount ;
   }
   else if((gSevereErrorCount>0) && (gFatalErrorCount == 0))
   {
      strcpy(RAPFileSummary.ERROR_TYPE,"SEVERE") ;
      RAPFileSummary.TOTAL_ERROR_COUNT = gSevereErrorCount ;
   }

   RAPFileSummary.TOTAL_CALL_EVENTS			    = gTotalCdrsCount;
  
   if(strcmp(RAPFileSummary.ERROR_TYPE,"FATAL") == 0)
   {
        RAPFileSummary.TOTAL_CALL_EVENTS_PROCESSED	    = 0;
   }
   else  if(strcmp(RAPFileSummary.ERROR_TYPE,"SEVERE") == 0)
   {
        RAPFileSummary.TOTAL_CALL_EVENTS_PROCESSED	    = gTotalCdrsCount - gErrorCDRsCount;
   }

/*
   RAPFileSummary.TOTAL_DURATION	                    = FileSummary.TOTAL_DURATION + gErrorCDRsDuration;
   RAPFileSummary.TOTAL_OUTGOING_VOLUME		            = FileSummary.TOTAL_OUTGOING_VOLUME + gErrorCDRsOutVolume;
   RAPFileSummary.TOTAL_INCOMING_VOLUME		            = FileSummary.TOTAL_INCOMING_VOLUME + gErrorCDRsIncVolume;
*/
   RAPFileSummary.TOTAL_DURATION	                    = FileSummary.TOTAL_DURATION ;
   RAPFileSummary.TOTAL_OUTGOING_VOLUME		            = FileSummary.TOTAL_OUTGOING_VOLUME ;
   RAPFileSummary.TOTAL_INCOMING_VOLUME		            = FileSummary.TOTAL_INCOMING_VOLUME ;
   RAPFileSummary.TAP_CURNCY_CHARGE			    = ACI.TotalCharge ;
   RAPFileSummary.TAP_CURNCY_TAX			    = ACI.TotalTaxValue;
   RAPFileSummary.TAP_CURNCY_DISCOUNT			    = ACI.TotalDiscountValue;
   if((gSevereErrorCount>0) && (gFatalErrorCount == 0))
   {
      RAPFileSummary.REJECTED_CALL_EVENTS      		    = gErrorCDRsCount;
      RAPFileSummary.REJECTED_DURATION                         = gErrorCDRsDuration;
      RAPFileSummary.REJECTED_OUTGOING_VOLUME                  = gErrorCDRsOutVolume;
      RAPFileSummary.REJECTED_INCOMING_VOLUME                  = gErrorCDRsIncVolume;
      RAPFileSummary.REJ_TAP_CURNCY_CHARGE                     = gErrorCDRsCharge;
      RAPFileSummary.REJ_TAP_CURNCY_TAX                        = gErrorCDRsTax;
      RAPFileSummary.REJ_TAP_CURNCY_DISCOUNT                   = gErrorCDRsDiscount;
   } 
}

int InsertTAPFileSummary()
{
   int i=0;
   double DiscountRate=0;
         /* Insert the Summary to the Table */
         /* EXEC SQL INSERT INTO PM_TAP_FILE_SUMRY
         (
    		FILE_TRANSFER_DIRECTION,
   		HPLMN_CODE,
   		VPLMN_CODE,
   		FILE_TYPE_INDICATOR,
   		FILE_SEQUENCE_NUMBER,
   		FILE_NAME,
   		DATA_TYPE_INDICATOR,
   		CALLS_TYPE_INDICATOR,
   		FILE_CREATION_TIME ,
   		FILE_CREATION_TIME_UTC_OFFSET,
   		FILE_TRANSFER_TIME,
   		FILE_TRANSFER_TIME_UTC_OFFSET,
   		FILE_AVAILABLE_TIME,
   		FILE_AVAILABLE_TIME_UTC_OFFSET,
   		TAP_SPECIFICATION_VERSION,
   		TAP_RELEASE_VERSION,
   		ISO_PLMN_CURNCY_CODE,
   		TAP_CURNCY_CODE,
   		TAP_CURNCY_DECIMAL_PLACES,
   		TAP_CURNCY_MULT_FACT,
   		TAP_CURNCY_ROUNDOFF_DECIMAL ,
   		HOME_CURNCY_ROUNDOFF_DECIMAL,
   		FILE_PROCESS_DATE,
   		FILE_PROCESSED_BY_USER_ID,
   		FILE_PROCESS_STATUS,
   		EARLIEST_CALL_TIME,
   		EARLIEST_CALL_TIME_UTC_OFFSET,
   		LATEST_CALL_TIME,
   		LATEST_CALL_TIME_UTC_OFFSET,
   		TOTAL_CALL_EVENTS,
   		TOTAL_CALL_EVENTS_PROCESSED,
   		TOTAL_PREPAID_CALL_EVENTS,
   		TOTAL_POSTPAID_CALL_EVENTS,
   		TOTAL_DURATION,
   		TOTAL_OUTGOING_VOLUME,
   		TOTAL_INCOMING_VOLUME,
   		TAP_CURNCY_CHARGE,
   		TAP_CURNCY_TAX,
   		TAP_CURNCY_DISCOUNT,
   		HOME_CURNCY_CHARGE,
   		HOME_CURNCY_TAX,
   		HOME_CURNCY_DISCOUNT,
   		HOME_CURNCY_SURCHARGE,
   		SURCHARGE_PERCENTAGE,
                REJECTED_CALL_EVENTS,
                REJECTED_DURATION,
                REJECTED_OUTGOING_VOLUME,
                REJECTED_INCOMING_VOLUME,
                REJECTED_TAP_CURNCY_CHARGE,
                REJECTED_HOME_CURNCY_CHARGE,
   		SETTLEMENT_CALL_EVENTS,
   		SETTLEMENT_DURATION,
   		SETTLEMENT_OUTGOING_VOLUME,
   		SETTLEMENT_INCOMING_VOLUME,
   		SETTLEMENT_TAP_CURNCY_CHARGE,
   		SETTLEMENT_TAP_CURNCY_TAX,
   		SETTLEMENT_TAP_CURNCY_DISCOUNT,
   		SETTLEMENT_LOCAL_CHARGE,
   		SETTLEMENT_LOCAL_TAX,
   		SETTLEMENT_LOCAL_DISCOUNT,
   		YEAR_MONTH,
                PARTNER_CODE,
                UTC_OFFSET_COUNT, 
                REC_ENTITY_COUNT, 
                TAX_COUNT, 
                DISCOUNT_COUNT, 
                CURRENCY_COUNT, 
                RAP_FILE_NAME,
                RAP_FILE_SEQUENCE_NUMBER,
                RAP_SPECIFICATION_VERSION,
                RAP_RELEASE_VERSION,
                FILE_CLEARING_STATUS
         )
         VALUES
         (
                   :FileSummary.FILE_TRANSFER_DIRECTION,
                   :FileSummary.HPLMN_CODE,
                   :FileSummary.VPLMN_CODE,
                   :FileSummary.FILE_TYPE_INDICATOR,
                   :FileSummary.FILE_SEQUENCE_NUMBER,
                   :FileSummary.FILE_NAME,
                   :FileSummary.DATA_TYPE_INDICATOR,
                   :FileSummary.CALLS_TYPE_INDICATOR,
                   to_date(:FileSummary.FILE_CREATION_TIME,'YYYYMMDDHH24MISS') ,
                   :FileSummary.FILE_CREATION_TIME_UTC_OFFSET,
                   to_date(:FileSummary.FILE_TRANSFER_TIME,'YYYYMMDDHH24MISS'),
                   :FileSummary.FILE_TRANSFER_TIME_UTC_OFFSET,
                   to_date(:FileSummary.FILE_AVAILABLE_TIME,'YYYYMMDDHH24MISS'),
                   :FileSummary.FILE_AVAILABLE_TIME_UTC_OFFSET,
                   :FileSummary.TAP_SPECIFICATION_VERSION,
                   :FileSummary.TAP_RELEASE_VERSION,
                   :FileSummary.ISO_PLMN_CURNCY_CODE,
                   :FileSummary.TAP_CURNCY_CODE,
                   :FileSummary.TAP_CURNCY_DECIMAL_PLACES,
                   :FileSummary.TAP_CURNCY_MULT_FACT,
                   :FileSummary.TAP_CURNCY_ROUNDOFF_DECIMAL ,
                   :FileSummary.HOME_CURNCY_ROUNDOFF_DECIMAL,
                   to_date(:FileSummary.FILE_PROCESS_DATE,'YYYYMMDDHH24MISS'),
                   :FileSummary.FILE_PROCESSED_BY_USER_ID,
                   :FileSummary.FILE_PROCESS_STATUS,
                   to_date(:FileSummary.EARLIEST_CALL_TIME,'YYYYMMDDHH24MISS'),
                   :FileSummary.EARLIEST_CALL_TIME_UTC_OFFSET,
                   to_date(:FileSummary.LATEST_CALL_TIME,'YYYYMMDDHH24MISS'),
                   :FileSummary.LATEST_CALL_TIME_UTC_OFFSET,
                   :FileSummary.TOTAL_CALL_EVENTS,
                   :FileSummary.TOTAL_CALL_EVENTS_PROCESSED,
                   :FileSummary.TOTAL_PREPAID_CALL_EVENTS,
                   :FileSummary.TOTAL_POSTPAID_CALL_EVENTS,
                   :FileSummary.TOTAL_DURATION,
                   :FileSummary.TOTAL_OUTGOING_VOLUME,
                   :FileSummary.TOTAL_INCOMING_VOLUME,
                   :FileSummary.TAP_CURNCY_CHARGE,
                   :FileSummary.TAP_CURNCY_TAX,
                   :FileSummary.TAP_CURNCY_DISCOUNT,
                   :FileSummary.HOME_CURNCY_CHARGE,
                   :FileSummary.HOME_CURNCY_TAX,
                   :FileSummary.HOME_CURNCY_DISCOUNT,
                   :FileSummary.HOME_CURNCY_SURCHARGE,
                   :FileSummary.SURCHARGE_PERCENTAGE,
                   :FileSummary.REJECTED_CALL_EVENTS,
                   :FileSummary.REJECTED_DURATION,
                   :FileSummary.REJECTED_OUTGOING_VOLUME,
                   :FileSummary.REJECTED_INCOMING_VOLUME,
                   :FileSummary.REJECTED_TAP_CURNCY_CHARGE,
                   :FileSummary.REJECTED_HOME_CURNCY_CHARGE,
                   :FileSummary.SETTLEMENT_CALL_EVENTS,
                   :FileSummary.SETTLEMENT_DURATION,
                   :FileSummary.SETTLEMENT_OUTGOING_VOLUME,
                   :FileSummary.SETTLEMENT_INCOMING_VOLUME,
                   :FileSummary.SETTLEMENT_TAP_CURNCY_CHARGE,
                   :FileSummary.SETTLEMENT_TAP_CURNCY_TAX,
                   :FileSummary.SETTLEMENT_TAP_CURNCY_DISCOUNT,
                   :FileSummary.SETTLEMENT_LOCAL_CHARGE,
                   :FileSummary.SETTLEMENT_LOCAL_TAX,
                   :FileSummary.SETTLEMENT_LOCAL_DISCOUNT,
                   :FileSummary.YEAR_MONTH,
                   :FileSummary.PARTNER_CODE,
                   :FileSummary.UTC_OFFSET_COUNT,
                   :FileSummary.REC_ENTITY_COUNT,
                   :FileSummary.TAX_COUNT,
                   :FileSummary.DISCOUNT_COUNT,
                   :FileSummary.CURRENCY_COUNT, 
                   :FileSummary.RAP_FILE_NAME,
                   :FileSummary.RAP_FILE_SEQUENCE_NUMBER,
                   :FileSummary.RAP_SPECIFICATION_VERSION,
                   :FileSummary.RAP_RELEASE_VERSION,
                   :FileSummary.FILE_CLEARING_STATUS
         ); */ 

{
         struct sqlexd sqlstm;
         sqlstm.sqlvsn = 12;
         sqlstm.arrsiz = 129;
         sqlstm.sqladtp = &sqladt;
         sqlstm.sqltdsp = &sqltds;
         sqlbuft((void **)0, 
           "insert into PM_TAP_FILE_SUMRY (FILE_TRANSFER_DIRECTION,HPLMN_COD\
E,VPLMN_CODE,FILE_TYPE_INDICATOR,FILE_SEQUENCE_NUMBER,FILE_NAME,DATA_TYPE_IN\
DICATOR,CALLS_TYPE_INDICATOR,FILE_CREATION_TIME,FILE_CREATION_TIME_UTC_OFFSE\
T,FILE_TRANSFER_TIME,FILE_TRANSFER_TIME_UTC_OFFSET,FILE_AVAILABLE_TIME,FILE_\
AVAILABLE_TIME_UTC_OFFSET,TAP_SPECIFICATION_VERSION,TAP_RELEASE_VERSION,ISO_\
PLMN_CURNCY_CODE,TAP_CURNCY_CODE,TAP_CURNCY_DECIMAL_PLACES,TAP_CURNCY_MULT_F\
ACT,TAP_CURNCY_ROUNDOFF_DECIMAL,HOME_CURNCY_ROUNDOFF_DECIMAL,FILE_PROCESS_DA\
TE,FILE_PROCESSED_BY_USER_ID,FILE_PROCESS_STATUS,EARLIEST_CALL_TIME,EARLIEST\
_CALL_TIME_UTC_OFFSET,LATEST_CALL_TIME,LATEST_CALL_TIME_UTC_OFFSET,TOTAL_CAL\
L_EVENTS,TOTAL_CALL_EVENTS_PROCESSED,TOTAL_PREPAID_CALL_EVENTS,TOTAL_POSTPAI\
D_CALL_EVENTS,TOTAL_DURATION,TOTAL_OUTGOING_VOLUME,TOTAL_INCOMING_VOLUME,TAP\
_CURNCY_CHARGE,TAP_CURNCY_TAX,TAP_CURNCY_DISCOUNT,HOME_CURNCY_CHARGE,HOME_CU\
RNCY_TAX,HOME_CURNCY_DISCOUNT,HOME_CURNCY_SURCHARGE,SURCHARGE_PERCENTAGE,REJ\
ECTED_CALL_EVENTS,REJECTED_DURATION,REJECTED_OUT");
         sqlbuft((void **)0, 
           "GOING_VOLUME,REJECTED_INCOMING_VOLUME,REJECTED_TAP_CURNCY_CHARGE\
,REJECTED_HOME_CURNCY_CHARGE,SETTLEMENT_CALL_EVENTS,SETTLEMENT_DURATION,SETT\
LEMENT_OUTGOING_VOLUME,SETTLEMENT_INCOMING_VOLUME,SETTLEMENT_TAP_CURNCY_CHAR\
GE,SETTLEMENT_TAP_CURNCY_TAX,SETTLEMENT_TAP_CURNCY_DISCOUNT,SETTLEMENT_LOCAL\
_CHARGE,SETTLEMENT_LOCAL_TAX,SETTLEMENT_LOCAL_DISCOUNT,YEAR_MONTH,PARTNER_CO\
DE,UTC_OFFSET_COUNT,REC_ENTITY_COUNT,TAX_COUNT,DISCOUNT_COUNT,CURRENCY_COUNT\
,RAP_FILE_NAME,RAP_FILE_SEQUENCE_NUMBER,RAP_SPECIFICATION_VERSION,RAP_RELEAS\
E_VERSION,FILE_CLEARING_STATUS) values (:b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,to_d\
ate(:b8,'YYYYMMDDHH24MISS'),:b9,to_date(:b10,'YYYYMMDDHH24MISS'),:b11,to_dat\
e(:b12,'YYYYMMDDHH24MISS'),:b13,:b14,:b15,:b16,:b17,:b18,:b19,:b20,:b21,to_d\
ate(:b22,'YYYYMMDDHH24MISS'),:b23,:b24,to_date(:b25,'YYYYMMDDHH24MISS'),:b26\
,to_date(:b27,'YYYYMMDDHH24MISS'),:b28,:b29,:b30,:b31,:b32,:b33,:b34,:b35,:b\
36,:b37,:b38,:b39,:b40,:b41,:b42,:b43,:b44,:b45,:b46,:b47,:b48,:b49,:b50,:b5\
1,:b52,:b53,:b54,:b55,:b56,:b57,:b58,:b59,:b60,:");
         sqlstm.stmt = "b61,:b62,:b63,:b64,:b65,:b66,:b67,:b68,:b69,:b70,:b7\
1)";
         sqlstm.iters = (unsigned int  )1;
         sqlstm.offset = (unsigned int  )4885;
         sqlstm.cud = sqlcud0;
         sqlstm.sqlest = (unsigned char  *)&sqlca;
         sqlstm.sqlety = (unsigned short)4352;
         sqlstm.occurs = (unsigned int  )0;
         sqlstm.sqhstv[0] = (         void  *)(FileSummary.FILE_TRANSFER_DIRECTION);
         sqlstm.sqhstl[0] = (unsigned int  )2;
         sqlstm.sqhsts[0] = (         int  )0;
         sqlstm.sqindv[0] = (         void  *)0;
         sqlstm.sqinds[0] = (         int  )0;
         sqlstm.sqharm[0] = (unsigned int  )0;
         sqlstm.sqadto[0] = (unsigned short )0;
         sqlstm.sqtdso[0] = (unsigned short )0;
         sqlstm.sqhstv[1] = (         void  *)(FileSummary.HPLMN_CODE);
         sqlstm.sqhstl[1] = (unsigned int  )6;
         sqlstm.sqhsts[1] = (         int  )0;
         sqlstm.sqindv[1] = (         void  *)0;
         sqlstm.sqinds[1] = (         int  )0;
         sqlstm.sqharm[1] = (unsigned int  )0;
         sqlstm.sqadto[1] = (unsigned short )0;
         sqlstm.sqtdso[1] = (unsigned short )0;
         sqlstm.sqhstv[2] = (         void  *)(FileSummary.VPLMN_CODE);
         sqlstm.sqhstl[2] = (unsigned int  )7;
         sqlstm.sqhsts[2] = (         int  )0;
         sqlstm.sqindv[2] = (         void  *)0;
         sqlstm.sqinds[2] = (         int  )0;
         sqlstm.sqharm[2] = (unsigned int  )0;
         sqlstm.sqadto[2] = (unsigned short )0;
         sqlstm.sqtdso[2] = (unsigned short )0;
         sqlstm.sqhstv[3] = (         void  *)(FileSummary.FILE_TYPE_INDICATOR);
         sqlstm.sqhstl[3] = (unsigned int  )2;
         sqlstm.sqhsts[3] = (         int  )0;
         sqlstm.sqindv[3] = (         void  *)0;
         sqlstm.sqinds[3] = (         int  )0;
         sqlstm.sqharm[3] = (unsigned int  )0;
         sqlstm.sqadto[3] = (unsigned short )0;
         sqlstm.sqtdso[3] = (unsigned short )0;
         sqlstm.sqhstv[4] = (         void  *)&(FileSummary.FILE_SEQUENCE_NUMBER);
         sqlstm.sqhstl[4] = (unsigned int  )sizeof(long);
         sqlstm.sqhsts[4] = (         int  )0;
         sqlstm.sqindv[4] = (         void  *)0;
         sqlstm.sqinds[4] = (         int  )0;
         sqlstm.sqharm[4] = (unsigned int  )0;
         sqlstm.sqadto[4] = (unsigned short )0;
         sqlstm.sqtdso[4] = (unsigned short )0;
         sqlstm.sqhstv[5] = (         void  *)(FileSummary.FILE_NAME);
         sqlstm.sqhstl[5] = (unsigned int  )18;
         sqlstm.sqhsts[5] = (         int  )0;
         sqlstm.sqindv[5] = (         void  *)0;
         sqlstm.sqinds[5] = (         int  )0;
         sqlstm.sqharm[5] = (unsigned int  )0;
         sqlstm.sqadto[5] = (unsigned short )0;
         sqlstm.sqtdso[5] = (unsigned short )0;
         sqlstm.sqhstv[6] = (         void  *)(FileSummary.DATA_TYPE_INDICATOR);
         sqlstm.sqhstl[6] = (unsigned int  )2;
         sqlstm.sqhsts[6] = (         int  )0;
         sqlstm.sqindv[6] = (         void  *)0;
         sqlstm.sqinds[6] = (         int  )0;
         sqlstm.sqharm[6] = (unsigned int  )0;
         sqlstm.sqadto[6] = (unsigned short )0;
         sqlstm.sqtdso[6] = (unsigned short )0;
         sqlstm.sqhstv[7] = (         void  *)(FileSummary.CALLS_TYPE_INDICATOR);
         sqlstm.sqhstl[7] = (unsigned int  )2;
         sqlstm.sqhsts[7] = (         int  )0;
         sqlstm.sqindv[7] = (         void  *)0;
         sqlstm.sqinds[7] = (         int  )0;
         sqlstm.sqharm[7] = (unsigned int  )0;
         sqlstm.sqadto[7] = (unsigned short )0;
         sqlstm.sqtdso[7] = (unsigned short )0;
         sqlstm.sqhstv[8] = (         void  *)(FileSummary.FILE_CREATION_TIME);
         sqlstm.sqhstl[8] = (unsigned int  )15;
         sqlstm.sqhsts[8] = (         int  )0;
         sqlstm.sqindv[8] = (         void  *)0;
         sqlstm.sqinds[8] = (         int  )0;
         sqlstm.sqharm[8] = (unsigned int  )0;
         sqlstm.sqadto[8] = (unsigned short )0;
         sqlstm.sqtdso[8] = (unsigned short )0;
         sqlstm.sqhstv[9] = (         void  *)(FileSummary.FILE_CREATION_TIME_UTC_OFFSET);
         sqlstm.sqhstl[9] = (unsigned int  )6;
         sqlstm.sqhsts[9] = (         int  )0;
         sqlstm.sqindv[9] = (         void  *)0;
         sqlstm.sqinds[9] = (         int  )0;
         sqlstm.sqharm[9] = (unsigned int  )0;
         sqlstm.sqadto[9] = (unsigned short )0;
         sqlstm.sqtdso[9] = (unsigned short )0;
         sqlstm.sqhstv[10] = (         void  *)(FileSummary.FILE_TRANSFER_TIME);
         sqlstm.sqhstl[10] = (unsigned int  )15;
         sqlstm.sqhsts[10] = (         int  )0;
         sqlstm.sqindv[10] = (         void  *)0;
         sqlstm.sqinds[10] = (         int  )0;
         sqlstm.sqharm[10] = (unsigned int  )0;
         sqlstm.sqadto[10] = (unsigned short )0;
         sqlstm.sqtdso[10] = (unsigned short )0;
         sqlstm.sqhstv[11] = (         void  *)(FileSummary.FILE_TRANSFER_TIME_UTC_OFFSET);
         sqlstm.sqhstl[11] = (unsigned int  )6;
         sqlstm.sqhsts[11] = (         int  )0;
         sqlstm.sqindv[11] = (         void  *)0;
         sqlstm.sqinds[11] = (         int  )0;
         sqlstm.sqharm[11] = (unsigned int  )0;
         sqlstm.sqadto[11] = (unsigned short )0;
         sqlstm.sqtdso[11] = (unsigned short )0;
         sqlstm.sqhstv[12] = (         void  *)(FileSummary.FILE_AVAILABLE_TIME);
         sqlstm.sqhstl[12] = (unsigned int  )15;
         sqlstm.sqhsts[12] = (         int  )0;
         sqlstm.sqindv[12] = (         void  *)0;
         sqlstm.sqinds[12] = (         int  )0;
         sqlstm.sqharm[12] = (unsigned int  )0;
         sqlstm.sqadto[12] = (unsigned short )0;
         sqlstm.sqtdso[12] = (unsigned short )0;
         sqlstm.sqhstv[13] = (         void  *)(FileSummary.FILE_AVAILABLE_TIME_UTC_OFFSET);
         sqlstm.sqhstl[13] = (unsigned int  )6;
         sqlstm.sqhsts[13] = (         int  )0;
         sqlstm.sqindv[13] = (         void  *)0;
         sqlstm.sqinds[13] = (         int  )0;
         sqlstm.sqharm[13] = (unsigned int  )0;
         sqlstm.sqadto[13] = (unsigned short )0;
         sqlstm.sqtdso[13] = (unsigned short )0;
         sqlstm.sqhstv[14] = (         void  *)&(FileSummary.TAP_SPECIFICATION_VERSION);
         sqlstm.sqhstl[14] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[14] = (         int  )0;
         sqlstm.sqindv[14] = (         void  *)0;
         sqlstm.sqinds[14] = (         int  )0;
         sqlstm.sqharm[14] = (unsigned int  )0;
         sqlstm.sqadto[14] = (unsigned short )0;
         sqlstm.sqtdso[14] = (unsigned short )0;
         sqlstm.sqhstv[15] = (         void  *)&(FileSummary.TAP_RELEASE_VERSION);
         sqlstm.sqhstl[15] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[15] = (         int  )0;
         sqlstm.sqindv[15] = (         void  *)0;
         sqlstm.sqinds[15] = (         int  )0;
         sqlstm.sqharm[15] = (unsigned int  )0;
         sqlstm.sqadto[15] = (unsigned short )0;
         sqlstm.sqtdso[15] = (unsigned short )0;
         sqlstm.sqhstv[16] = (         void  *)(FileSummary.ISO_PLMN_CURNCY_CODE);
         sqlstm.sqhstl[16] = (unsigned int  )4;
         sqlstm.sqhsts[16] = (         int  )0;
         sqlstm.sqindv[16] = (         void  *)0;
         sqlstm.sqinds[16] = (         int  )0;
         sqlstm.sqharm[16] = (unsigned int  )0;
         sqlstm.sqadto[16] = (unsigned short )0;
         sqlstm.sqtdso[16] = (unsigned short )0;
         sqlstm.sqhstv[17] = (         void  *)(FileSummary.TAP_CURNCY_CODE);
         sqlstm.sqhstl[17] = (unsigned int  )6;
         sqlstm.sqhsts[17] = (         int  )0;
         sqlstm.sqindv[17] = (         void  *)0;
         sqlstm.sqinds[17] = (         int  )0;
         sqlstm.sqharm[17] = (unsigned int  )0;
         sqlstm.sqadto[17] = (unsigned short )0;
         sqlstm.sqtdso[17] = (unsigned short )0;
         sqlstm.sqhstv[18] = (         void  *)&(FileSummary.TAP_CURNCY_DECIMAL_PLACES);
         sqlstm.sqhstl[18] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[18] = (         int  )0;
         sqlstm.sqindv[18] = (         void  *)0;
         sqlstm.sqinds[18] = (         int  )0;
         sqlstm.sqharm[18] = (unsigned int  )0;
         sqlstm.sqadto[18] = (unsigned short )0;
         sqlstm.sqtdso[18] = (unsigned short )0;
         sqlstm.sqhstv[19] = (         void  *)&(FileSummary.TAP_CURNCY_MULT_FACT);
         sqlstm.sqhstl[19] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[19] = (         int  )0;
         sqlstm.sqindv[19] = (         void  *)0;
         sqlstm.sqinds[19] = (         int  )0;
         sqlstm.sqharm[19] = (unsigned int  )0;
         sqlstm.sqadto[19] = (unsigned short )0;
         sqlstm.sqtdso[19] = (unsigned short )0;
         sqlstm.sqhstv[20] = (         void  *)&(FileSummary.TAP_CURNCY_ROUNDOFF_DECIMAL);
         sqlstm.sqhstl[20] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[20] = (         int  )0;
         sqlstm.sqindv[20] = (         void  *)0;
         sqlstm.sqinds[20] = (         int  )0;
         sqlstm.sqharm[20] = (unsigned int  )0;
         sqlstm.sqadto[20] = (unsigned short )0;
         sqlstm.sqtdso[20] = (unsigned short )0;
         sqlstm.sqhstv[21] = (         void  *)&(FileSummary.HOME_CURNCY_ROUNDOFF_DECIMAL);
         sqlstm.sqhstl[21] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[21] = (         int  )0;
         sqlstm.sqindv[21] = (         void  *)0;
         sqlstm.sqinds[21] = (         int  )0;
         sqlstm.sqharm[21] = (unsigned int  )0;
         sqlstm.sqadto[21] = (unsigned short )0;
         sqlstm.sqtdso[21] = (unsigned short )0;
         sqlstm.sqhstv[22] = (         void  *)(FileSummary.FILE_PROCESS_DATE);
         sqlstm.sqhstl[22] = (unsigned int  )15;
         sqlstm.sqhsts[22] = (         int  )0;
         sqlstm.sqindv[22] = (         void  *)0;
         sqlstm.sqinds[22] = (         int  )0;
         sqlstm.sqharm[22] = (unsigned int  )0;
         sqlstm.sqadto[22] = (unsigned short )0;
         sqlstm.sqtdso[22] = (unsigned short )0;
         sqlstm.sqhstv[23] = (         void  *)(FileSummary.FILE_PROCESSED_BY_USER_ID);
         sqlstm.sqhstl[23] = (unsigned int  )51;
         sqlstm.sqhsts[23] = (         int  )0;
         sqlstm.sqindv[23] = (         void  *)0;
         sqlstm.sqinds[23] = (         int  )0;
         sqlstm.sqharm[23] = (unsigned int  )0;
         sqlstm.sqadto[23] = (unsigned short )0;
         sqlstm.sqtdso[23] = (unsigned short )0;
         sqlstm.sqhstv[24] = (         void  *)(FileSummary.FILE_PROCESS_STATUS);
         sqlstm.sqhstl[24] = (unsigned int  )2;
         sqlstm.sqhsts[24] = (         int  )0;
         sqlstm.sqindv[24] = (         void  *)0;
         sqlstm.sqinds[24] = (         int  )0;
         sqlstm.sqharm[24] = (unsigned int  )0;
         sqlstm.sqadto[24] = (unsigned short )0;
         sqlstm.sqtdso[24] = (unsigned short )0;
         sqlstm.sqhstv[25] = (         void  *)(FileSummary.EARLIEST_CALL_TIME);
         sqlstm.sqhstl[25] = (unsigned int  )15;
         sqlstm.sqhsts[25] = (         int  )0;
         sqlstm.sqindv[25] = (         void  *)0;
         sqlstm.sqinds[25] = (         int  )0;
         sqlstm.sqharm[25] = (unsigned int  )0;
         sqlstm.sqadto[25] = (unsigned short )0;
         sqlstm.sqtdso[25] = (unsigned short )0;
         sqlstm.sqhstv[26] = (         void  *)(FileSummary.EARLIEST_CALL_TIME_UTC_OFFSET);
         sqlstm.sqhstl[26] = (unsigned int  )6;
         sqlstm.sqhsts[26] = (         int  )0;
         sqlstm.sqindv[26] = (         void  *)0;
         sqlstm.sqinds[26] = (         int  )0;
         sqlstm.sqharm[26] = (unsigned int  )0;
         sqlstm.sqadto[26] = (unsigned short )0;
         sqlstm.sqtdso[26] = (unsigned short )0;
         sqlstm.sqhstv[27] = (         void  *)(FileSummary.LATEST_CALL_TIME);
         sqlstm.sqhstl[27] = (unsigned int  )15;
         sqlstm.sqhsts[27] = (         int  )0;
         sqlstm.sqindv[27] = (         void  *)0;
         sqlstm.sqinds[27] = (         int  )0;
         sqlstm.sqharm[27] = (unsigned int  )0;
         sqlstm.sqadto[27] = (unsigned short )0;
         sqlstm.sqtdso[27] = (unsigned short )0;
         sqlstm.sqhstv[28] = (         void  *)(FileSummary.LATEST_CALL_TIME_UTC_OFFSET);
         sqlstm.sqhstl[28] = (unsigned int  )6;
         sqlstm.sqhsts[28] = (         int  )0;
         sqlstm.sqindv[28] = (         void  *)0;
         sqlstm.sqinds[28] = (         int  )0;
         sqlstm.sqharm[28] = (unsigned int  )0;
         sqlstm.sqadto[28] = (unsigned short )0;
         sqlstm.sqtdso[28] = (unsigned short )0;
         sqlstm.sqhstv[29] = (         void  *)&(FileSummary.TOTAL_CALL_EVENTS);
         sqlstm.sqhstl[29] = (unsigned int  )sizeof(long);
         sqlstm.sqhsts[29] = (         int  )0;
         sqlstm.sqindv[29] = (         void  *)0;
         sqlstm.sqinds[29] = (         int  )0;
         sqlstm.sqharm[29] = (unsigned int  )0;
         sqlstm.sqadto[29] = (unsigned short )0;
         sqlstm.sqtdso[29] = (unsigned short )0;
         sqlstm.sqhstv[30] = (         void  *)&(FileSummary.TOTAL_CALL_EVENTS_PROCESSED);
         sqlstm.sqhstl[30] = (unsigned int  )sizeof(long);
         sqlstm.sqhsts[30] = (         int  )0;
         sqlstm.sqindv[30] = (         void  *)0;
         sqlstm.sqinds[30] = (         int  )0;
         sqlstm.sqharm[30] = (unsigned int  )0;
         sqlstm.sqadto[30] = (unsigned short )0;
         sqlstm.sqtdso[30] = (unsigned short )0;
         sqlstm.sqhstv[31] = (         void  *)&(FileSummary.TOTAL_PREPAID_CALL_EVENTS);
         sqlstm.sqhstl[31] = (unsigned int  )sizeof(long);
         sqlstm.sqhsts[31] = (         int  )0;
         sqlstm.sqindv[31] = (         void  *)0;
         sqlstm.sqinds[31] = (         int  )0;
         sqlstm.sqharm[31] = (unsigned int  )0;
         sqlstm.sqadto[31] = (unsigned short )0;
         sqlstm.sqtdso[31] = (unsigned short )0;
         sqlstm.sqhstv[32] = (         void  *)&(FileSummary.TOTAL_POSTPAID_CALL_EVENTS);
         sqlstm.sqhstl[32] = (unsigned int  )sizeof(long);
         sqlstm.sqhsts[32] = (         int  )0;
         sqlstm.sqindv[32] = (         void  *)0;
         sqlstm.sqinds[32] = (         int  )0;
         sqlstm.sqharm[32] = (unsigned int  )0;
         sqlstm.sqadto[32] = (unsigned short )0;
         sqlstm.sqtdso[32] = (unsigned short )0;
         sqlstm.sqhstv[33] = (         void  *)&(FileSummary.TOTAL_DURATION);
         sqlstm.sqhstl[33] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[33] = (         int  )0;
         sqlstm.sqindv[33] = (         void  *)0;
         sqlstm.sqinds[33] = (         int  )0;
         sqlstm.sqharm[33] = (unsigned int  )0;
         sqlstm.sqadto[33] = (unsigned short )0;
         sqlstm.sqtdso[33] = (unsigned short )0;
         sqlstm.sqhstv[34] = (         void  *)&(FileSummary.TOTAL_OUTGOING_VOLUME);
         sqlstm.sqhstl[34] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[34] = (         int  )0;
         sqlstm.sqindv[34] = (         void  *)0;
         sqlstm.sqinds[34] = (         int  )0;
         sqlstm.sqharm[34] = (unsigned int  )0;
         sqlstm.sqadto[34] = (unsigned short )0;
         sqlstm.sqtdso[34] = (unsigned short )0;
         sqlstm.sqhstv[35] = (         void  *)&(FileSummary.TOTAL_INCOMING_VOLUME);
         sqlstm.sqhstl[35] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[35] = (         int  )0;
         sqlstm.sqindv[35] = (         void  *)0;
         sqlstm.sqinds[35] = (         int  )0;
         sqlstm.sqharm[35] = (unsigned int  )0;
         sqlstm.sqadto[35] = (unsigned short )0;
         sqlstm.sqtdso[35] = (unsigned short )0;
         sqlstm.sqhstv[36] = (         void  *)&(FileSummary.TAP_CURNCY_CHARGE);
         sqlstm.sqhstl[36] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[36] = (         int  )0;
         sqlstm.sqindv[36] = (         void  *)0;
         sqlstm.sqinds[36] = (         int  )0;
         sqlstm.sqharm[36] = (unsigned int  )0;
         sqlstm.sqadto[36] = (unsigned short )0;
         sqlstm.sqtdso[36] = (unsigned short )0;
         sqlstm.sqhstv[37] = (         void  *)&(FileSummary.TAP_CURNCY_TAX);
         sqlstm.sqhstl[37] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[37] = (         int  )0;
         sqlstm.sqindv[37] = (         void  *)0;
         sqlstm.sqinds[37] = (         int  )0;
         sqlstm.sqharm[37] = (unsigned int  )0;
         sqlstm.sqadto[37] = (unsigned short )0;
         sqlstm.sqtdso[37] = (unsigned short )0;
         sqlstm.sqhstv[38] = (         void  *)&(FileSummary.TAP_CURNCY_DISCOUNT);
         sqlstm.sqhstl[38] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[38] = (         int  )0;
         sqlstm.sqindv[38] = (         void  *)0;
         sqlstm.sqinds[38] = (         int  )0;
         sqlstm.sqharm[38] = (unsigned int  )0;
         sqlstm.sqadto[38] = (unsigned short )0;
         sqlstm.sqtdso[38] = (unsigned short )0;
         sqlstm.sqhstv[39] = (         void  *)&(FileSummary.HOME_CURNCY_CHARGE);
         sqlstm.sqhstl[39] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[39] = (         int  )0;
         sqlstm.sqindv[39] = (         void  *)0;
         sqlstm.sqinds[39] = (         int  )0;
         sqlstm.sqharm[39] = (unsigned int  )0;
         sqlstm.sqadto[39] = (unsigned short )0;
         sqlstm.sqtdso[39] = (unsigned short )0;
         sqlstm.sqhstv[40] = (         void  *)&(FileSummary.HOME_CURNCY_TAX);
         sqlstm.sqhstl[40] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[40] = (         int  )0;
         sqlstm.sqindv[40] = (         void  *)0;
         sqlstm.sqinds[40] = (         int  )0;
         sqlstm.sqharm[40] = (unsigned int  )0;
         sqlstm.sqadto[40] = (unsigned short )0;
         sqlstm.sqtdso[40] = (unsigned short )0;
         sqlstm.sqhstv[41] = (         void  *)&(FileSummary.HOME_CURNCY_DISCOUNT);
         sqlstm.sqhstl[41] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[41] = (         int  )0;
         sqlstm.sqindv[41] = (         void  *)0;
         sqlstm.sqinds[41] = (         int  )0;
         sqlstm.sqharm[41] = (unsigned int  )0;
         sqlstm.sqadto[41] = (unsigned short )0;
         sqlstm.sqtdso[41] = (unsigned short )0;
         sqlstm.sqhstv[42] = (         void  *)&(FileSummary.HOME_CURNCY_SURCHARGE);
         sqlstm.sqhstl[42] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[42] = (         int  )0;
         sqlstm.sqindv[42] = (         void  *)0;
         sqlstm.sqinds[42] = (         int  )0;
         sqlstm.sqharm[42] = (unsigned int  )0;
         sqlstm.sqadto[42] = (unsigned short )0;
         sqlstm.sqtdso[42] = (unsigned short )0;
         sqlstm.sqhstv[43] = (         void  *)&(FileSummary.SURCHARGE_PERCENTAGE);
         sqlstm.sqhstl[43] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[43] = (         int  )0;
         sqlstm.sqindv[43] = (         void  *)0;
         sqlstm.sqinds[43] = (         int  )0;
         sqlstm.sqharm[43] = (unsigned int  )0;
         sqlstm.sqadto[43] = (unsigned short )0;
         sqlstm.sqtdso[43] = (unsigned short )0;
         sqlstm.sqhstv[44] = (         void  *)&(FileSummary.REJECTED_CALL_EVENTS);
         sqlstm.sqhstl[44] = (unsigned int  )sizeof(long);
         sqlstm.sqhsts[44] = (         int  )0;
         sqlstm.sqindv[44] = (         void  *)0;
         sqlstm.sqinds[44] = (         int  )0;
         sqlstm.sqharm[44] = (unsigned int  )0;
         sqlstm.sqadto[44] = (unsigned short )0;
         sqlstm.sqtdso[44] = (unsigned short )0;
         sqlstm.sqhstv[45] = (         void  *)&(FileSummary.REJECTED_DURATION);
         sqlstm.sqhstl[45] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[45] = (         int  )0;
         sqlstm.sqindv[45] = (         void  *)0;
         sqlstm.sqinds[45] = (         int  )0;
         sqlstm.sqharm[45] = (unsigned int  )0;
         sqlstm.sqadto[45] = (unsigned short )0;
         sqlstm.sqtdso[45] = (unsigned short )0;
         sqlstm.sqhstv[46] = (         void  *)&(FileSummary.REJECTED_OUTGOING_VOLUME);
         sqlstm.sqhstl[46] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[46] = (         int  )0;
         sqlstm.sqindv[46] = (         void  *)0;
         sqlstm.sqinds[46] = (         int  )0;
         sqlstm.sqharm[46] = (unsigned int  )0;
         sqlstm.sqadto[46] = (unsigned short )0;
         sqlstm.sqtdso[46] = (unsigned short )0;
         sqlstm.sqhstv[47] = (         void  *)&(FileSummary.REJECTED_INCOMING_VOLUME);
         sqlstm.sqhstl[47] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[47] = (         int  )0;
         sqlstm.sqindv[47] = (         void  *)0;
         sqlstm.sqinds[47] = (         int  )0;
         sqlstm.sqharm[47] = (unsigned int  )0;
         sqlstm.sqadto[47] = (unsigned short )0;
         sqlstm.sqtdso[47] = (unsigned short )0;
         sqlstm.sqhstv[48] = (         void  *)&(FileSummary.REJECTED_TAP_CURNCY_CHARGE);
         sqlstm.sqhstl[48] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[48] = (         int  )0;
         sqlstm.sqindv[48] = (         void  *)0;
         sqlstm.sqinds[48] = (         int  )0;
         sqlstm.sqharm[48] = (unsigned int  )0;
         sqlstm.sqadto[48] = (unsigned short )0;
         sqlstm.sqtdso[48] = (unsigned short )0;
         sqlstm.sqhstv[49] = (         void  *)&(FileSummary.REJECTED_HOME_CURNCY_CHARGE);
         sqlstm.sqhstl[49] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[49] = (         int  )0;
         sqlstm.sqindv[49] = (         void  *)0;
         sqlstm.sqinds[49] = (         int  )0;
         sqlstm.sqharm[49] = (unsigned int  )0;
         sqlstm.sqadto[49] = (unsigned short )0;
         sqlstm.sqtdso[49] = (unsigned short )0;
         sqlstm.sqhstv[50] = (         void  *)&(FileSummary.SETTLEMENT_CALL_EVENTS);
         sqlstm.sqhstl[50] = (unsigned int  )sizeof(long);
         sqlstm.sqhsts[50] = (         int  )0;
         sqlstm.sqindv[50] = (         void  *)0;
         sqlstm.sqinds[50] = (         int  )0;
         sqlstm.sqharm[50] = (unsigned int  )0;
         sqlstm.sqadto[50] = (unsigned short )0;
         sqlstm.sqtdso[50] = (unsigned short )0;
         sqlstm.sqhstv[51] = (         void  *)&(FileSummary.SETTLEMENT_DURATION);
         sqlstm.sqhstl[51] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[51] = (         int  )0;
         sqlstm.sqindv[51] = (         void  *)0;
         sqlstm.sqinds[51] = (         int  )0;
         sqlstm.sqharm[51] = (unsigned int  )0;
         sqlstm.sqadto[51] = (unsigned short )0;
         sqlstm.sqtdso[51] = (unsigned short )0;
         sqlstm.sqhstv[52] = (         void  *)&(FileSummary.SETTLEMENT_OUTGOING_VOLUME);
         sqlstm.sqhstl[52] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[52] = (         int  )0;
         sqlstm.sqindv[52] = (         void  *)0;
         sqlstm.sqinds[52] = (         int  )0;
         sqlstm.sqharm[52] = (unsigned int  )0;
         sqlstm.sqadto[52] = (unsigned short )0;
         sqlstm.sqtdso[52] = (unsigned short )0;
         sqlstm.sqhstv[53] = (         void  *)&(FileSummary.SETTLEMENT_INCOMING_VOLUME);
         sqlstm.sqhstl[53] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[53] = (         int  )0;
         sqlstm.sqindv[53] = (         void  *)0;
         sqlstm.sqinds[53] = (         int  )0;
         sqlstm.sqharm[53] = (unsigned int  )0;
         sqlstm.sqadto[53] = (unsigned short )0;
         sqlstm.sqtdso[53] = (unsigned short )0;
         sqlstm.sqhstv[54] = (         void  *)&(FileSummary.SETTLEMENT_TAP_CURNCY_CHARGE);
         sqlstm.sqhstl[54] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[54] = (         int  )0;
         sqlstm.sqindv[54] = (         void  *)0;
         sqlstm.sqinds[54] = (         int  )0;
         sqlstm.sqharm[54] = (unsigned int  )0;
         sqlstm.sqadto[54] = (unsigned short )0;
         sqlstm.sqtdso[54] = (unsigned short )0;
         sqlstm.sqhstv[55] = (         void  *)&(FileSummary.SETTLEMENT_TAP_CURNCY_TAX);
         sqlstm.sqhstl[55] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[55] = (         int  )0;
         sqlstm.sqindv[55] = (         void  *)0;
         sqlstm.sqinds[55] = (         int  )0;
         sqlstm.sqharm[55] = (unsigned int  )0;
         sqlstm.sqadto[55] = (unsigned short )0;
         sqlstm.sqtdso[55] = (unsigned short )0;
         sqlstm.sqhstv[56] = (         void  *)&(FileSummary.SETTLEMENT_TAP_CURNCY_DISCOUNT);
         sqlstm.sqhstl[56] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[56] = (         int  )0;
         sqlstm.sqindv[56] = (         void  *)0;
         sqlstm.sqinds[56] = (         int  )0;
         sqlstm.sqharm[56] = (unsigned int  )0;
         sqlstm.sqadto[56] = (unsigned short )0;
         sqlstm.sqtdso[56] = (unsigned short )0;
         sqlstm.sqhstv[57] = (         void  *)&(FileSummary.SETTLEMENT_LOCAL_CHARGE);
         sqlstm.sqhstl[57] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[57] = (         int  )0;
         sqlstm.sqindv[57] = (         void  *)0;
         sqlstm.sqinds[57] = (         int  )0;
         sqlstm.sqharm[57] = (unsigned int  )0;
         sqlstm.sqadto[57] = (unsigned short )0;
         sqlstm.sqtdso[57] = (unsigned short )0;
         sqlstm.sqhstv[58] = (         void  *)&(FileSummary.SETTLEMENT_LOCAL_TAX);
         sqlstm.sqhstl[58] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[58] = (         int  )0;
         sqlstm.sqindv[58] = (         void  *)0;
         sqlstm.sqinds[58] = (         int  )0;
         sqlstm.sqharm[58] = (unsigned int  )0;
         sqlstm.sqadto[58] = (unsigned short )0;
         sqlstm.sqtdso[58] = (unsigned short )0;
         sqlstm.sqhstv[59] = (         void  *)&(FileSummary.SETTLEMENT_LOCAL_DISCOUNT);
         sqlstm.sqhstl[59] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[59] = (         int  )0;
         sqlstm.sqindv[59] = (         void  *)0;
         sqlstm.sqinds[59] = (         int  )0;
         sqlstm.sqharm[59] = (unsigned int  )0;
         sqlstm.sqadto[59] = (unsigned short )0;
         sqlstm.sqtdso[59] = (unsigned short )0;
         sqlstm.sqhstv[60] = (         void  *)&(FileSummary.YEAR_MONTH);
         sqlstm.sqhstl[60] = (unsigned int  )sizeof(long);
         sqlstm.sqhsts[60] = (         int  )0;
         sqlstm.sqindv[60] = (         void  *)0;
         sqlstm.sqinds[60] = (         int  )0;
         sqlstm.sqharm[60] = (unsigned int  )0;
         sqlstm.sqadto[60] = (unsigned short )0;
         sqlstm.sqtdso[60] = (unsigned short )0;
         sqlstm.sqhstv[61] = (         void  *)(FileSummary.PARTNER_CODE);
         sqlstm.sqhstl[61] = (unsigned int  )4;
         sqlstm.sqhsts[61] = (         int  )0;
         sqlstm.sqindv[61] = (         void  *)0;
         sqlstm.sqinds[61] = (         int  )0;
         sqlstm.sqharm[61] = (unsigned int  )0;
         sqlstm.sqadto[61] = (unsigned short )0;
         sqlstm.sqtdso[61] = (unsigned short )0;
         sqlstm.sqhstv[62] = (         void  *)&(FileSummary.UTC_OFFSET_COUNT);
         sqlstm.sqhstl[62] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[62] = (         int  )0;
         sqlstm.sqindv[62] = (         void  *)0;
         sqlstm.sqinds[62] = (         int  )0;
         sqlstm.sqharm[62] = (unsigned int  )0;
         sqlstm.sqadto[62] = (unsigned short )0;
         sqlstm.sqtdso[62] = (unsigned short )0;
         sqlstm.sqhstv[63] = (         void  *)&(FileSummary.REC_ENTITY_COUNT);
         sqlstm.sqhstl[63] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[63] = (         int  )0;
         sqlstm.sqindv[63] = (         void  *)0;
         sqlstm.sqinds[63] = (         int  )0;
         sqlstm.sqharm[63] = (unsigned int  )0;
         sqlstm.sqadto[63] = (unsigned short )0;
         sqlstm.sqtdso[63] = (unsigned short )0;
         sqlstm.sqhstv[64] = (         void  *)&(FileSummary.TAX_COUNT);
         sqlstm.sqhstl[64] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[64] = (         int  )0;
         sqlstm.sqindv[64] = (         void  *)0;
         sqlstm.sqinds[64] = (         int  )0;
         sqlstm.sqharm[64] = (unsigned int  )0;
         sqlstm.sqadto[64] = (unsigned short )0;
         sqlstm.sqtdso[64] = (unsigned short )0;
         sqlstm.sqhstv[65] = (         void  *)&(FileSummary.DISCOUNT_COUNT);
         sqlstm.sqhstl[65] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[65] = (         int  )0;
         sqlstm.sqindv[65] = (         void  *)0;
         sqlstm.sqinds[65] = (         int  )0;
         sqlstm.sqharm[65] = (unsigned int  )0;
         sqlstm.sqadto[65] = (unsigned short )0;
         sqlstm.sqtdso[65] = (unsigned short )0;
         sqlstm.sqhstv[66] = (         void  *)&(FileSummary.CURRENCY_COUNT);
         sqlstm.sqhstl[66] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[66] = (         int  )0;
         sqlstm.sqindv[66] = (         void  *)0;
         sqlstm.sqinds[66] = (         int  )0;
         sqlstm.sqharm[66] = (unsigned int  )0;
         sqlstm.sqadto[66] = (unsigned short )0;
         sqlstm.sqtdso[66] = (unsigned short )0;
         sqlstm.sqhstv[67] = (         void  *)(FileSummary.RAP_FILE_NAME);
         sqlstm.sqhstl[67] = (unsigned int  )18;
         sqlstm.sqhsts[67] = (         int  )0;
         sqlstm.sqindv[67] = (         void  *)0;
         sqlstm.sqinds[67] = (         int  )0;
         sqlstm.sqharm[67] = (unsigned int  )0;
         sqlstm.sqadto[67] = (unsigned short )0;
         sqlstm.sqtdso[67] = (unsigned short )0;
         sqlstm.sqhstv[68] = (         void  *)&(FileSummary.RAP_FILE_SEQUENCE_NUMBER);
         sqlstm.sqhstl[68] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[68] = (         int  )0;
         sqlstm.sqindv[68] = (         void  *)0;
         sqlstm.sqinds[68] = (         int  )0;
         sqlstm.sqharm[68] = (unsigned int  )0;
         sqlstm.sqadto[68] = (unsigned short )0;
         sqlstm.sqtdso[68] = (unsigned short )0;
         sqlstm.sqhstv[69] = (         void  *)&(FileSummary.RAP_SPECIFICATION_VERSION);
         sqlstm.sqhstl[69] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[69] = (         int  )0;
         sqlstm.sqindv[69] = (         void  *)0;
         sqlstm.sqinds[69] = (         int  )0;
         sqlstm.sqharm[69] = (unsigned int  )0;
         sqlstm.sqadto[69] = (unsigned short )0;
         sqlstm.sqtdso[69] = (unsigned short )0;
         sqlstm.sqhstv[70] = (         void  *)&(FileSummary.RAP_RELEASE_VERSION);
         sqlstm.sqhstl[70] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[70] = (         int  )0;
         sqlstm.sqindv[70] = (         void  *)0;
         sqlstm.sqinds[70] = (         int  )0;
         sqlstm.sqharm[70] = (unsigned int  )0;
         sqlstm.sqadto[70] = (unsigned short )0;
         sqlstm.sqtdso[70] = (unsigned short )0;
         sqlstm.sqhstv[71] = (         void  *)(FileSummary.FILE_CLEARING_STATUS);
         sqlstm.sqhstl[71] = (unsigned int  )2;
         sqlstm.sqhsts[71] = (         int  )0;
         sqlstm.sqindv[71] = (         void  *)0;
         sqlstm.sqinds[71] = (         int  )0;
         sqlstm.sqharm[71] = (unsigned int  )0;
         sqlstm.sqadto[71] = (unsigned short )0;
         sqlstm.sqtdso[71] = (unsigned short )0;
         sqlstm.sqphsv = sqlstm.sqhstv;
         sqlstm.sqphsl = sqlstm.sqhstl;
         sqlstm.sqphss = sqlstm.sqhsts;
         sqlstm.sqpind = sqlstm.sqindv;
         sqlstm.sqpins = sqlstm.sqinds;
         sqlstm.sqparm = sqlstm.sqharm;
         sqlstm.sqparc = sqlstm.sqharc;
         sqlstm.sqpadto = sqlstm.sqadto;
         sqlstm.sqptdso = sqlstm.sqtdso;
         sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


   
         if(ERRCODE != 0)
         {
             stErrors.ERROR_CODE = sqlca.sqlcode;
             strcpy(stErrors.ERROR_DESC,"Error Inserting Record into PM_TAP_FILE_SUMARY table");

             TRACEENTRY(1,"%s","Error Inserting Record into PM_TAP_FILE_SUMARY table");
             TRACEENTRY(1,"%s -%d-","ERROR : sqlca.sqlcode :",ERRCODE);
             if(ERRCODE != -1)
             {
                TRACEENTRY(1,"%s","String Values Below --------------");
                TRACEENTRY(1,"FILE_TRANSFER_DIRECTION          : -%s-",FileSummary.FILE_TRANSFER_DIRECTION);
                TRACEENTRY(1,"HPLMN_CODE                       : -%s-",FileSummary.HPLMN_CODE);
                TRACEENTRY(1,"VPLMN_CODE                       : -%s-",FileSummary.VPLMN_CODE);
                TRACEENTRY(1,"FILE_TYPE_INDICATOR              : -%s-",FileSummary.FILE_TYPE_INDICATOR);
                TRACEENTRY(1,"FILE_NAME                        : -%s-",FileSummary.FILE_NAME);
                TRACEENTRY(1,"DATA_TYPE_INDICATOR              : -%s-",FileSummary.DATA_TYPE_INDICATOR);
                TRACEENTRY(1,"CALLS_TYPE_INDICATOR             : -%s-",FileSummary.CALLS_TYPE_INDICATOR);
                TRACEENTRY(1,"FILE_CREATION_TIME               : -%s-",FileSummary.FILE_CREATION_TIME);
                TRACEENTRY(1,"FILE_CREATION_TIME_UTC_OFFSET    : -%s-",FileSummary.FILE_CREATION_TIME_UTC_OFFSET);
                TRACEENTRY(1,"FILE_TRANSFER_TIME               : -%s-",FileSummary.FILE_TRANSFER_TIME);
                TRACEENTRY(1,"FILE_TRANSFER_TIME_UTC_OFFSET    : -%s-",FileSummary.FILE_TRANSFER_TIME_UTC_OFFSET);
                TRACEENTRY(1,"FILE_AVAILABLE_TIME              : -%s-",FileSummary.FILE_AVAILABLE_TIME);
                TRACEENTRY(1,"FILE_AVAILABLE_TIME_UTC_OFFSET   : -%s-",FileSummary.FILE_AVAILABLE_TIME_UTC_OFFSET);
                TRACEENTRY(1,"ISO_PLMN_CURNCY_CODE             : -%s-",FileSummary.ISO_PLMN_CURNCY_CODE);
                TRACEENTRY(1,"TAP_CURNCY_CODE                  : -%s-",FileSummary.TAP_CURNCY_CODE);
                TRACEENTRY(1,"FILE_PROCESS_DATE                : -%s-",FileSummary.FILE_PROCESS_DATE);
                TRACEENTRY(1,"FILE_PROCESSED_BY_USER_ID        : -%s-",FileSummary.FILE_PROCESSED_BY_USER_ID);
                TRACEENTRY(1,"FILE_PROCESS_STATUS              : -%s-",FileSummary.FILE_PROCESS_STATUS);
                TRACEENTRY(1,"EARLIEST_CALL_TIME               : -%s-",FileSummary.EARLIEST_CALL_TIME);
                TRACEENTRY(1,"EARLIEST_CALL_TIME_UTC_OFFSET    : -%s-",FileSummary.EARLIEST_CALL_TIME_UTC_OFFSET);
                TRACEENTRY(1,"LATEST_CALL_TIME                 : -%s-",FileSummary.LATEST_CALL_TIME);
                TRACEENTRY(1,"LATEST_CALL_TIME_UTC_OFFSET      : -%s-",FileSummary.LATEST_CALL_TIME_UTC_OFFSET);
                TRACEENTRY(1,"PARTNER_CODE                     : -%s-",FileSummary.PARTNER_CODE);
                TRACEENTRY(1,"RAP_FILE_NAME                    : -%s-",FileSummary.RAP_FILE_NAME);
                TRACEENTRY(1,"FILE_CLEARING_STATUS             : -%s-",FileSummary.FILE_CLEARING_STATUS);

                TRACEENTRY(1,"%s","Number Values Below --------------");
                TRACEENTRY(1,"FILE_SEQUENCE_NUMBER	       : -%d-",FileSummary.FILE_SEQUENCE_NUMBER);
                TRACEENTRY(1,"TAP_SPECIFICATION_VERSION        : -%d-",FileSummary.TAP_SPECIFICATION_VERSION);
                TRACEENTRY(1,"TAP_RELEASE_VERSION	       : -%d-",FileSummary.TAP_RELEASE_VERSION);
                TRACEENTRY(1,"TAP_CURNCY_DECIMAL_PLACES        : -%d-",FileSummary.TAP_CURNCY_DECIMAL_PLACES);
                TRACEENTRY(1,"TAP_CURNCY_MULT_FACT	       : -%f-",FileSummary.TAP_CURNCY_MULT_FACT);
                TRACEENTRY(1,"TAP_CURNCY_ROUNDOFF_DECIMAL      : -%d-",FileSummary.TAP_CURNCY_ROUNDOFF_DECIMAL);
                TRACEENTRY(1,"HOME_CURNCY_ROUNDOFF_DECIMAL     : -%d-",FileSummary.HOME_CURNCY_ROUNDOFF_DECIMAL);
                TRACEENTRY(1,"TOTAL_CALL_EVENTS		       : -%d-",FileSummary.TOTAL_CALL_EVENTS);
                TRACEENTRY(1,"TOTAL_CALL_EVENTS_PROCESSED      : -%d-",FileSummary.TOTAL_CALL_EVENTS_PROCESSED);
                TRACEENTRY(1,"TOTAL_PREPAID_CALL_EVENTS	       : -%d-",FileSummary.TOTAL_PREPAID_CALL_EVENTS);
                TRACEENTRY(1,"TOTAL_POSTPAID_CALL_EVENTS       : -%d-",FileSummary.TOTAL_POSTPAID_CALL_EVENTS);
                TRACEENTRY(1,"TOTAL_DURATION		       : -%f-",FileSummary.TOTAL_DURATION);
                TRACEENTRY(1,"TOTAL_OUTGOING_VOLUME	       : -%f-",FileSummary.TOTAL_OUTGOING_VOLUME);
                TRACEENTRY(1,"TOTAL_INCOMING_VOLUME            : -%f-",FileSummary.TOTAL_INCOMING_VOLUME);
                TRACEENTRY(1,"TAP_CURNCY_CHARGE                : -%f-",FileSummary.TAP_CURNCY_CHARGE);
                TRACEENTRY(1,"TAP_CURNCY_TAX                   : -%f-",FileSummary.TAP_CURNCY_TAX);
                TRACEENTRY(1,"TAP_CURNCY_DISCOUNT              : -%f-",FileSummary.TAP_CURNCY_DISCOUNT);
                TRACEENTRY(1,"HOME_CURNCY_CHARGE               : -%f-",FileSummary.HOME_CURNCY_CHARGE);
                TRACEENTRY(1,"HOME_CURNCY_TAX                  : -%f-",FileSummary.HOME_CURNCY_TAX);
                TRACEENTRY(1,"HOME_CURNCY_DISCOUNT             : -%f-",FileSummary.HOME_CURNCY_DISCOUNT);
                TRACEENTRY(1,"HOME_CURNCY_SURCHARGE            : -%f-",FileSummary.HOME_CURNCY_SURCHARGE);
                TRACEENTRY(1,"SURCHARGE_PERCENTAGE             : -%f-",FileSummary.SURCHARGE_PERCENTAGE);
                TRACEENTRY(1,"REJECTED_CALL_EVENTS             : -%d-",FileSummary.REJECTED_CALL_EVENTS);
                TRACEENTRY(1,"REJECTED_DURATION                : -%f-",FileSummary.REJECTED_DURATION);
                TRACEENTRY(1,"REJECTED_OUTGOING_VOLUME         : -%f-",FileSummary.REJECTED_OUTGOING_VOLUME);
                TRACEENTRY(1,"REJECTED_INCOMING_VOLUME         : -%f-",FileSummary.REJECTED_INCOMING_VOLUME);
                TRACEENTRY(1,"REJECTED_TAP_CURNCY_CHARGE       : -%f-",FileSummary.REJECTED_TAP_CURNCY_CHARGE);
                TRACEENTRY(1,"REJECTED_HOME_CURNCY_CHARGE      : -%f-",FileSummary.REJECTED_HOME_CURNCY_CHARGE);
                TRACEENTRY(1,"SETTLEMENT_CALL_EVENTS           : -%d-",FileSummary.SETTLEMENT_CALL_EVENTS);
                TRACEENTRY(1,"SETTLEMENT_DURATION              : -%f-",FileSummary.SETTLEMENT_DURATION);
                TRACEENTRY(1,"SETTLEMENT_OUTGOING_VOLUME       : -%f-",FileSummary.SETTLEMENT_OUTGOING_VOLUME);
                TRACEENTRY(1,"SETTLEMENT_INCOMING_VOLUME       : -%f-",FileSummary.SETTLEMENT_INCOMING_VOLUME);
                TRACEENTRY(1,"SETTLEMENT_TAP_CURNCY_CHARGE     : -%f-",FileSummary.SETTLEMENT_INCOMING_VOLUME);
                TRACEENTRY(1,"SETTLEMENT_TAP_CURNCY_TAX        : -%f-",FileSummary.SETTLEMENT_TAP_CURNCY_TAX);
                TRACEENTRY(1,"SETTLEMENT_TAP_CURNCY_DISCOUNT   : -%f-",FileSummary.SETTLEMENT_TAP_CURNCY_DISCOUNT);
                TRACEENTRY(1,"SETTLEMENT_LOCAL_CHARGE          : -%f-",FileSummary.SETTLEMENT_LOCAL_CHARGE);
                TRACEENTRY(1,"SETTLEMENT_LOCAL_TAX             : -%f-",FileSummary.SETTLEMENT_LOCAL_TAX);
                TRACEENTRY(1,"SETTLEMENT_LOCAL_DISCOUNT        : -%f-",FileSummary.SETTLEMENT_LOCAL_DISCOUNT);
                TRACEENTRY(1,"YEAR_MONTH                       : -%d-",FileSummary.YEAR_MONTH);
                TRACEENTRY(1,"UTC_OFFSET_COUNT                 : -%d-",FileSummary.UTC_OFFSET_COUNT);
                TRACEENTRY(1,"REC_ENTITY_COUNT                 : -%d-",FileSummary.REC_ENTITY_COUNT);
                TRACEENTRY(1,"TAX_COUNT                        : -%d-",FileSummary.TAX_COUNT);
                TRACEENTRY(1,"DISCOUNT_COUNT                   : -%d-",FileSummary.DISCOUNT_COUNT);
                TRACEENTRY(1,"CURRENCY_COUNT                   : -%d-",FileSummary.CURRENCY_COUNT);
                TRACEENTRY(1,"RAP_SEQUENCE_NUMBER	       : -%d-",FileSummary.RAP_FILE_SEQUENCE_NUMBER);
                TRACEENTRY(1,"RAP_SPECIFICATION_VERSION        : -%d-",FileSummary.RAP_SPECIFICATION_VERSION);
                TRACEENTRY(1,"RAP_RELEASE_VERSION	       : -%d-",FileSummary.RAP_RELEASE_VERSION);
             }
             return -1;
         }

}


int InsertRAPFileSummary()
{
   int i=0;
   double DiscountRate=0;

   

   if(RAPFileSummary.RAP_SPECIFICATION_VERSION ==0)
   {
      TRACEENTRY(1,"%s -%d-","Invalid RAP Specification Version Specified",RAPFileSummary.RAP_SPECIFICATION_VERSION);
      return -1;
   }

   if(RAPFileSummary.RAP_RELEASE_VERSION ==0)
   {
      TRACEENTRY(1,"%s -%d-","Invalid RAP Release Version Specified",RAPFileSummary.RAP_RELEASE_VERSION);
      return -1;
   }


         /* Insert the Summary to the Table */
         /* EXEC SQL INSERT INTO PM_RAP_FILE_SUMRY
         (
    		FILE_TRANSFER_DIRECTION          ,
   		HPLMN_CODE                       ,
   		VPLMN_CODE                       ,
   		FILE_TYPE_INDICATOR              ,
   		FILE_SEQUENCE_NUMBER             ,
   		RAP_FILE_NAME                    ,
   		TAP_FILE_NAME                    ,
   		DATA_TYPE_INDICATOR              ,
   		FILE_CREATION_TIME               ,
   		FILE_CREATION_TIME_UTC_OFFSET    ,
   		FILE_AVAILABLE_TIME              ,
   		FILE_AVAILABLE_TIME_UTC_OFFSET   ,
                START_MISSING_SEQ_NO             ,
                END_MISSING_SEQ_NO               ,
                ERROR_TYPE                       ,
                TOTAL_ERROR_COUNT                ,
   		RAP_SPECIFICATION_VERSION        ,
   		RAP_RELEASE_VERSION              ,
   		TAP_SPECIFICATION_VERSION        ,
   		TAP_RELEASE_VERSION              ,
   		ISO_PLMN_CURNCY_CODE             ,
   		TAP_CURNCY_CODE                  ,
   		TAP_CURNCY_DECIMAL_PLACES        ,
   		TAP_CURNCY_MULT_FACT             ,
   		TAP_CURNCY_ROUNDOFF_DECIMAL      ,
   		HOME_CURNCY_ROUNDOFF_DECIMAL     ,
   		FILE_PROCESS_DATE                ,
   		FILE_PROCESSED_BY                ,
   		FILE_PROCESS_STATUS              ,
   		TOTAL_CALL_EVENTS                ,
   		TOTAL_CALL_EVENTS_PROCESSED      ,
   		TOTAL_DURATION                   ,
   		TOTAL_OUTGOING_VOLUME            ,
   		TOTAL_INCOMING_VOLUME            ,
   		TAP_CURNCY_CHARGE                ,
   		TAP_CURNCY_TAX                   ,
   		TAP_CURNCY_DISCOUNT              ,
   		HOME_CURNCY_CHARGE               ,
   		HOME_CURNCY_TAX                  ,
   		HOME_CURNCY_DISCOUNT             ,
   		HOME_CURNCY_SURCHARGE            ,
                PARTNER_CODE                     ,
                REJECTED_CALL_EVENTS             ,
                REJECTED_DURATION                ,
                REJECTED_OUTGOING_VOLUME         ,
                REJECTED_INCOMING_VOLUME         ,
                RAP_ACKNOWLEDGEMENT_STATUS       ,
                REJ_TAP_CURNCY_CHARGE            ,
                REJ_TAP_CURNCY_TAX               ,
                REJ_TAP_CURNCY_DISCOUNT          ,
                REJ_HOME_CURNCY_CHARGE           ,
                REJ_HOME_CURNCY_TAX              ,
                REJ_HOME_CURNCY_DISCOUNT         ,
                FILE_TYPE_GENERATION
         )
         VALUES
         (
                :RAPFileSummary.FILE_TRANSFER_DIRECTION                        ,
                :RAPFileSummary.HPLMN_CODE                                     ,
                :RAPFileSummary.VPLMN_CODE                                     ,
                :RAPFileSummary.FILE_TYPE_INDICATOR                            ,
                :RAPFileSummary.FILE_SEQUENCE_NUMBER                           ,
                :RAPFileSummary.RAP_FILE_NAME                                  ,
                :RAPFileSummary.TAP_FILE_NAME                                  ,
                :RAPFileSummary.DATA_TYPE_INDICATOR                            ,
                to_date(:gRapFileCreationTime,'YYYYMMDDHH24MISS')              ,
                :RAPFileSummary.FILE_CREATION_TIME_UTC_OFFSET                  ,
                to_date(:gRapFileCreationTime,'YYYYMMDDHH24MISS')              ,
                :RAPFileSummary.FILE_AVAILABLE_TIME_UTC_OFFSET                 ,
                :RAPFileSummary.START_MISSING_SEQ_NO                           ,
                :RAPFileSummary.END_MISSING_SEQ_NO                             ,
                :RAPFileSummary.ERROR_TYPE                                     ,
                :RAPFileSummary.TOTAL_ERROR_COUNT                              ,
                :RAPFileSummary.RAP_SPECIFICATION_VERSION                      ,
                :RAPFileSummary.RAP_RELEASE_VERSION                            ,
                :RAPFileSummary.TAP_SPECIFICATION_VERSION                      ,
                :RAPFileSummary.TAP_RELEASE_VERSION                            ,
                :RAPFileSummary.ISO_PLMN_CURNCY_CODE                           ,
                :RAPFileSummary.TAP_CURNCY_CODE                                ,
                :RAPFileSummary.TAP_CURNCY_DECIMAL_PLACES                      ,
                :RAPFileSummary.TAP_CURNCY_MULT_FACT                           ,
                :RAPFileSummary.TAP_CURNCY_ROUNDOFF_DECIMAL                    ,
                :RAPFileSummary.HOME_CURNCY_ROUNDOFF_DECIMAL                   ,
                 CURRENT_TIMESTAMP                                             ,
                :RAPFileSummary.FILE_PROCESSED_BY                              ,
                :RAPFileSummary.FILE_PROCESS_STATUS                            ,
                :RAPFileSummary.TOTAL_CALL_EVENTS                              ,
                :RAPFileSummary.TOTAL_CALL_EVENTS_PROCESSED                    ,
                :RAPFileSummary.TOTAL_DURATION                                 ,
                :RAPFileSummary.TOTAL_OUTGOING_VOLUME                          ,
                :RAPFileSummary.TOTAL_INCOMING_VOLUME                          ,
                :RAPFileSummary.TAP_CURNCY_CHARGE                              ,
                :RAPFileSummary.TAP_CURNCY_TAX                                 ,
                :RAPFileSummary.TAP_CURNCY_DISCOUNT                            ,
                :RAPFileSummary.HOME_CURNCY_CHARGE                             ,
                :RAPFileSummary.HOME_CURNCY_TAX                                ,
                :RAPFileSummary.HOME_CURNCY_DISCOUNT                           ,
                :RAPFileSummary.HOME_CURNCY_SURCHARGE                          ,
                :RAPFileSummary.PARTNER_CODE                                   ,
                :RAPFileSummary.REJECTED_CALL_EVENTS                           ,
                :RAPFileSummary.REJECTED_DURATION                              ,
                :RAPFileSummary.REJECTED_OUTGOING_VOLUME                       ,
                :RAPFileSummary.REJECTED_INCOMING_VOLUME                       ,
                :RAPFileSummary.RAP_ACKNOWLEDGEMENT_STATUS                     ,
                :RAPFileSummary.REJ_TAP_CURNCY_CHARGE                          ,
                :RAPFileSummary.REJ_TAP_CURNCY_TAX                             ,
                :RAPFileSummary.REJ_TAP_CURNCY_DISCOUNT                        ,
                :RAPFileSummary.REJ_HOME_CURNCY_CHARGE                         ,
                :RAPFileSummary.REJ_HOME_CURNCY_TAX                            ,
                :RAPFileSummary.REJ_HOME_CURNCY_DISCOUNT                       ,
                :RAPFileSummary.FILE_TYPE_GENERATION

         ); */ 

{
         struct sqlexd sqlstm;
         sqlstm.sqlvsn = 12;
         sqlstm.arrsiz = 129;
         sqlstm.sqladtp = &sqladt;
         sqlstm.sqltdsp = &sqltds;
         sqlbuft((void **)0, 
           "insert into PM_RAP_FILE_SUMRY (FILE_TRANSFER_DIRECTION,HPLMN_COD\
E,VPLMN_CODE,FILE_TYPE_INDICATOR,FILE_SEQUENCE_NUMBER,RAP_FILE_NAME,TAP_FILE\
_NAME,DATA_TYPE_INDICATOR,FILE_CREATION_TIME,FILE_CREATION_TIME_UTC_OFFSET,F\
ILE_AVAILABLE_TIME,FILE_AVAILABLE_TIME_UTC_OFFSET,START_MISSING_SEQ_NO,END_M\
ISSING_SEQ_NO,ERROR_TYPE,TOTAL_ERROR_COUNT,RAP_SPECIFICATION_VERSION,RAP_REL\
EASE_VERSION,TAP_SPECIFICATION_VERSION,TAP_RELEASE_VERSION,ISO_PLMN_CURNCY_C\
ODE,TAP_CURNCY_CODE,TAP_CURNCY_DECIMAL_PLACES,TAP_CURNCY_MULT_FACT,TAP_CURNC\
Y_ROUNDOFF_DECIMAL,HOME_CURNCY_ROUNDOFF_DECIMAL,FILE_PROCESS_DATE,FILE_PROCE\
SSED_BY,FILE_PROCESS_STATUS,TOTAL_CALL_EVENTS,TOTAL_CALL_EVENTS_PROCESSED,TO\
TAL_DURATION,TOTAL_OUTGOING_VOLUME,TOTAL_INCOMING_VOLUME,TAP_CURNCY_CHARGE,T\
AP_CURNCY_TAX,TAP_CURNCY_DISCOUNT,HOME_CURNCY_CHARGE,HOME_CURNCY_TAX,HOME_CU\
RNCY_DISCOUNT,HOME_CURNCY_SURCHARGE,PARTNER_CODE,REJECTED_CALL_EVENTS,REJECT\
ED_DURATION,REJECTED_OUTGOING_VOLUME,REJECTED_INCOMING_VOLUME,RAP_ACKNOWLEDG\
EMENT_STATUS,REJ_TAP_CURNCY_CHARGE,REJ_TAP_CURNC");
         sqlstm.stmt = "Y_TAX,REJ_TAP_CURNCY_DISCOUNT,REJ_HOME_CURNCY_CHARGE\
,REJ_HOME_CURNCY_TAX,REJ_HOME_CURNCY_DISCOUNT,FILE_TYPE_GENERATION) values (:b\
0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,to_date(:b8,'YYYYMMDDHH24MISS'),:b9,to_date(:b8,\
'YYYYMMDDHH24MISS'),:b11,:b12,:b13,:b14,:b15,:b16,:b17,:b18,:b19,:b20,:b21,:b2\
2,:b23,:b24,:b25,CURRENT_TIMESTAMP,:b26,:b27,:b28,:b29,:b30,:b31,:b32,:b33,:b3\
4,:b35,:b36,:b37,:b38,:b39,:b40,:b41,:b42,:b43,:b44,:b45,:b46,:b47,:b48,:b49,:\
b50,:b51,:b52)";
         sqlstm.iters = (unsigned int  )1;
         sqlstm.offset = (unsigned int  )5188;
         sqlstm.cud = sqlcud0;
         sqlstm.sqlest = (unsigned char  *)&sqlca;
         sqlstm.sqlety = (unsigned short)4352;
         sqlstm.occurs = (unsigned int  )0;
         sqlstm.sqhstv[0] = (         void  *)(RAPFileSummary.FILE_TRANSFER_DIRECTION);
         sqlstm.sqhstl[0] = (unsigned int  )2;
         sqlstm.sqhsts[0] = (         int  )0;
         sqlstm.sqindv[0] = (         void  *)0;
         sqlstm.sqinds[0] = (         int  )0;
         sqlstm.sqharm[0] = (unsigned int  )0;
         sqlstm.sqadto[0] = (unsigned short )0;
         sqlstm.sqtdso[0] = (unsigned short )0;
         sqlstm.sqhstv[1] = (         void  *)(RAPFileSummary.HPLMN_CODE);
         sqlstm.sqhstl[1] = (unsigned int  )6;
         sqlstm.sqhsts[1] = (         int  )0;
         sqlstm.sqindv[1] = (         void  *)0;
         sqlstm.sqinds[1] = (         int  )0;
         sqlstm.sqharm[1] = (unsigned int  )0;
         sqlstm.sqadto[1] = (unsigned short )0;
         sqlstm.sqtdso[1] = (unsigned short )0;
         sqlstm.sqhstv[2] = (         void  *)(RAPFileSummary.VPLMN_CODE);
         sqlstm.sqhstl[2] = (unsigned int  )7;
         sqlstm.sqhsts[2] = (         int  )0;
         sqlstm.sqindv[2] = (         void  *)0;
         sqlstm.sqinds[2] = (         int  )0;
         sqlstm.sqharm[2] = (unsigned int  )0;
         sqlstm.sqadto[2] = (unsigned short )0;
         sqlstm.sqtdso[2] = (unsigned short )0;
         sqlstm.sqhstv[3] = (         void  *)(RAPFileSummary.FILE_TYPE_INDICATOR);
         sqlstm.sqhstl[3] = (unsigned int  )2;
         sqlstm.sqhsts[3] = (         int  )0;
         sqlstm.sqindv[3] = (         void  *)0;
         sqlstm.sqinds[3] = (         int  )0;
         sqlstm.sqharm[3] = (unsigned int  )0;
         sqlstm.sqadto[3] = (unsigned short )0;
         sqlstm.sqtdso[3] = (unsigned short )0;
         sqlstm.sqhstv[4] = (         void  *)&(RAPFileSummary.FILE_SEQUENCE_NUMBER);
         sqlstm.sqhstl[4] = (unsigned int  )sizeof(long);
         sqlstm.sqhsts[4] = (         int  )0;
         sqlstm.sqindv[4] = (         void  *)0;
         sqlstm.sqinds[4] = (         int  )0;
         sqlstm.sqharm[4] = (unsigned int  )0;
         sqlstm.sqadto[4] = (unsigned short )0;
         sqlstm.sqtdso[4] = (unsigned short )0;
         sqlstm.sqhstv[5] = (         void  *)(RAPFileSummary.RAP_FILE_NAME);
         sqlstm.sqhstl[5] = (unsigned int  )18;
         sqlstm.sqhsts[5] = (         int  )0;
         sqlstm.sqindv[5] = (         void  *)0;
         sqlstm.sqinds[5] = (         int  )0;
         sqlstm.sqharm[5] = (unsigned int  )0;
         sqlstm.sqadto[5] = (unsigned short )0;
         sqlstm.sqtdso[5] = (unsigned short )0;
         sqlstm.sqhstv[6] = (         void  *)(RAPFileSummary.TAP_FILE_NAME);
         sqlstm.sqhstl[6] = (unsigned int  )18;
         sqlstm.sqhsts[6] = (         int  )0;
         sqlstm.sqindv[6] = (         void  *)0;
         sqlstm.sqinds[6] = (         int  )0;
         sqlstm.sqharm[6] = (unsigned int  )0;
         sqlstm.sqadto[6] = (unsigned short )0;
         sqlstm.sqtdso[6] = (unsigned short )0;
         sqlstm.sqhstv[7] = (         void  *)(RAPFileSummary.DATA_TYPE_INDICATOR);
         sqlstm.sqhstl[7] = (unsigned int  )2;
         sqlstm.sqhsts[7] = (         int  )0;
         sqlstm.sqindv[7] = (         void  *)0;
         sqlstm.sqinds[7] = (         int  )0;
         sqlstm.sqharm[7] = (unsigned int  )0;
         sqlstm.sqadto[7] = (unsigned short )0;
         sqlstm.sqtdso[7] = (unsigned short )0;
         sqlstm.sqhstv[8] = (         void  *)gRapFileCreationTime;
         sqlstm.sqhstl[8] = (unsigned int  )15;
         sqlstm.sqhsts[8] = (         int  )0;
         sqlstm.sqindv[8] = (         void  *)0;
         sqlstm.sqinds[8] = (         int  )0;
         sqlstm.sqharm[8] = (unsigned int  )0;
         sqlstm.sqadto[8] = (unsigned short )0;
         sqlstm.sqtdso[8] = (unsigned short )0;
         sqlstm.sqhstv[9] = (         void  *)(RAPFileSummary.FILE_CREATION_TIME_UTC_OFFSET);
         sqlstm.sqhstl[9] = (unsigned int  )6;
         sqlstm.sqhsts[9] = (         int  )0;
         sqlstm.sqindv[9] = (         void  *)0;
         sqlstm.sqinds[9] = (         int  )0;
         sqlstm.sqharm[9] = (unsigned int  )0;
         sqlstm.sqadto[9] = (unsigned short )0;
         sqlstm.sqtdso[9] = (unsigned short )0;
         sqlstm.sqhstv[10] = (         void  *)gRapFileCreationTime;
         sqlstm.sqhstl[10] = (unsigned int  )15;
         sqlstm.sqhsts[10] = (         int  )0;
         sqlstm.sqindv[10] = (         void  *)0;
         sqlstm.sqinds[10] = (         int  )0;
         sqlstm.sqharm[10] = (unsigned int  )0;
         sqlstm.sqadto[10] = (unsigned short )0;
         sqlstm.sqtdso[10] = (unsigned short )0;
         sqlstm.sqhstv[11] = (         void  *)(RAPFileSummary.FILE_AVAILABLE_TIME_UTC_OFFSET);
         sqlstm.sqhstl[11] = (unsigned int  )6;
         sqlstm.sqhsts[11] = (         int  )0;
         sqlstm.sqindv[11] = (         void  *)0;
         sqlstm.sqinds[11] = (         int  )0;
         sqlstm.sqharm[11] = (unsigned int  )0;
         sqlstm.sqadto[11] = (unsigned short )0;
         sqlstm.sqtdso[11] = (unsigned short )0;
         sqlstm.sqhstv[12] = (         void  *)&(RAPFileSummary.START_MISSING_SEQ_NO);
         sqlstm.sqhstl[12] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[12] = (         int  )0;
         sqlstm.sqindv[12] = (         void  *)0;
         sqlstm.sqinds[12] = (         int  )0;
         sqlstm.sqharm[12] = (unsigned int  )0;
         sqlstm.sqadto[12] = (unsigned short )0;
         sqlstm.sqtdso[12] = (unsigned short )0;
         sqlstm.sqhstv[13] = (         void  *)&(RAPFileSummary.END_MISSING_SEQ_NO);
         sqlstm.sqhstl[13] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[13] = (         int  )0;
         sqlstm.sqindv[13] = (         void  *)0;
         sqlstm.sqinds[13] = (         int  )0;
         sqlstm.sqharm[13] = (unsigned int  )0;
         sqlstm.sqadto[13] = (unsigned short )0;
         sqlstm.sqtdso[13] = (unsigned short )0;
         sqlstm.sqhstv[14] = (         void  *)(RAPFileSummary.ERROR_TYPE);
         sqlstm.sqhstl[14] = (unsigned int  )9;
         sqlstm.sqhsts[14] = (         int  )0;
         sqlstm.sqindv[14] = (         void  *)0;
         sqlstm.sqinds[14] = (         int  )0;
         sqlstm.sqharm[14] = (unsigned int  )0;
         sqlstm.sqadto[14] = (unsigned short )0;
         sqlstm.sqtdso[14] = (unsigned short )0;
         sqlstm.sqhstv[15] = (         void  *)&(RAPFileSummary.TOTAL_ERROR_COUNT);
         sqlstm.sqhstl[15] = (unsigned int  )sizeof(long);
         sqlstm.sqhsts[15] = (         int  )0;
         sqlstm.sqindv[15] = (         void  *)0;
         sqlstm.sqinds[15] = (         int  )0;
         sqlstm.sqharm[15] = (unsigned int  )0;
         sqlstm.sqadto[15] = (unsigned short )0;
         sqlstm.sqtdso[15] = (unsigned short )0;
         sqlstm.sqhstv[16] = (         void  *)&(RAPFileSummary.RAP_SPECIFICATION_VERSION);
         sqlstm.sqhstl[16] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[16] = (         int  )0;
         sqlstm.sqindv[16] = (         void  *)0;
         sqlstm.sqinds[16] = (         int  )0;
         sqlstm.sqharm[16] = (unsigned int  )0;
         sqlstm.sqadto[16] = (unsigned short )0;
         sqlstm.sqtdso[16] = (unsigned short )0;
         sqlstm.sqhstv[17] = (         void  *)&(RAPFileSummary.RAP_RELEASE_VERSION);
         sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[17] = (         int  )0;
         sqlstm.sqindv[17] = (         void  *)0;
         sqlstm.sqinds[17] = (         int  )0;
         sqlstm.sqharm[17] = (unsigned int  )0;
         sqlstm.sqadto[17] = (unsigned short )0;
         sqlstm.sqtdso[17] = (unsigned short )0;
         sqlstm.sqhstv[18] = (         void  *)&(RAPFileSummary.TAP_SPECIFICATION_VERSION);
         sqlstm.sqhstl[18] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[18] = (         int  )0;
         sqlstm.sqindv[18] = (         void  *)0;
         sqlstm.sqinds[18] = (         int  )0;
         sqlstm.sqharm[18] = (unsigned int  )0;
         sqlstm.sqadto[18] = (unsigned short )0;
         sqlstm.sqtdso[18] = (unsigned short )0;
         sqlstm.sqhstv[19] = (         void  *)&(RAPFileSummary.TAP_RELEASE_VERSION);
         sqlstm.sqhstl[19] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[19] = (         int  )0;
         sqlstm.sqindv[19] = (         void  *)0;
         sqlstm.sqinds[19] = (         int  )0;
         sqlstm.sqharm[19] = (unsigned int  )0;
         sqlstm.sqadto[19] = (unsigned short )0;
         sqlstm.sqtdso[19] = (unsigned short )0;
         sqlstm.sqhstv[20] = (         void  *)(RAPFileSummary.ISO_PLMN_CURNCY_CODE);
         sqlstm.sqhstl[20] = (unsigned int  )4;
         sqlstm.sqhsts[20] = (         int  )0;
         sqlstm.sqindv[20] = (         void  *)0;
         sqlstm.sqinds[20] = (         int  )0;
         sqlstm.sqharm[20] = (unsigned int  )0;
         sqlstm.sqadto[20] = (unsigned short )0;
         sqlstm.sqtdso[20] = (unsigned short )0;
         sqlstm.sqhstv[21] = (         void  *)(RAPFileSummary.TAP_CURNCY_CODE);
         sqlstm.sqhstl[21] = (unsigned int  )6;
         sqlstm.sqhsts[21] = (         int  )0;
         sqlstm.sqindv[21] = (         void  *)0;
         sqlstm.sqinds[21] = (         int  )0;
         sqlstm.sqharm[21] = (unsigned int  )0;
         sqlstm.sqadto[21] = (unsigned short )0;
         sqlstm.sqtdso[21] = (unsigned short )0;
         sqlstm.sqhstv[22] = (         void  *)&(RAPFileSummary.TAP_CURNCY_DECIMAL_PLACES);
         sqlstm.sqhstl[22] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[22] = (         int  )0;
         sqlstm.sqindv[22] = (         void  *)0;
         sqlstm.sqinds[22] = (         int  )0;
         sqlstm.sqharm[22] = (unsigned int  )0;
         sqlstm.sqadto[22] = (unsigned short )0;
         sqlstm.sqtdso[22] = (unsigned short )0;
         sqlstm.sqhstv[23] = (         void  *)&(RAPFileSummary.TAP_CURNCY_MULT_FACT);
         sqlstm.sqhstl[23] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[23] = (         int  )0;
         sqlstm.sqindv[23] = (         void  *)0;
         sqlstm.sqinds[23] = (         int  )0;
         sqlstm.sqharm[23] = (unsigned int  )0;
         sqlstm.sqadto[23] = (unsigned short )0;
         sqlstm.sqtdso[23] = (unsigned short )0;
         sqlstm.sqhstv[24] = (         void  *)&(RAPFileSummary.TAP_CURNCY_ROUNDOFF_DECIMAL);
         sqlstm.sqhstl[24] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[24] = (         int  )0;
         sqlstm.sqindv[24] = (         void  *)0;
         sqlstm.sqinds[24] = (         int  )0;
         sqlstm.sqharm[24] = (unsigned int  )0;
         sqlstm.sqadto[24] = (unsigned short )0;
         sqlstm.sqtdso[24] = (unsigned short )0;
         sqlstm.sqhstv[25] = (         void  *)&(RAPFileSummary.HOME_CURNCY_ROUNDOFF_DECIMAL);
         sqlstm.sqhstl[25] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[25] = (         int  )0;
         sqlstm.sqindv[25] = (         void  *)0;
         sqlstm.sqinds[25] = (         int  )0;
         sqlstm.sqharm[25] = (unsigned int  )0;
         sqlstm.sqadto[25] = (unsigned short )0;
         sqlstm.sqtdso[25] = (unsigned short )0;
         sqlstm.sqhstv[26] = (         void  *)(RAPFileSummary.FILE_PROCESSED_BY);
         sqlstm.sqhstl[26] = (unsigned int  )51;
         sqlstm.sqhsts[26] = (         int  )0;
         sqlstm.sqindv[26] = (         void  *)0;
         sqlstm.sqinds[26] = (         int  )0;
         sqlstm.sqharm[26] = (unsigned int  )0;
         sqlstm.sqadto[26] = (unsigned short )0;
         sqlstm.sqtdso[26] = (unsigned short )0;
         sqlstm.sqhstv[27] = (         void  *)(RAPFileSummary.FILE_PROCESS_STATUS);
         sqlstm.sqhstl[27] = (unsigned int  )2;
         sqlstm.sqhsts[27] = (         int  )0;
         sqlstm.sqindv[27] = (         void  *)0;
         sqlstm.sqinds[27] = (         int  )0;
         sqlstm.sqharm[27] = (unsigned int  )0;
         sqlstm.sqadto[27] = (unsigned short )0;
         sqlstm.sqtdso[27] = (unsigned short )0;
         sqlstm.sqhstv[28] = (         void  *)&(RAPFileSummary.TOTAL_CALL_EVENTS);
         sqlstm.sqhstl[28] = (unsigned int  )sizeof(long);
         sqlstm.sqhsts[28] = (         int  )0;
         sqlstm.sqindv[28] = (         void  *)0;
         sqlstm.sqinds[28] = (         int  )0;
         sqlstm.sqharm[28] = (unsigned int  )0;
         sqlstm.sqadto[28] = (unsigned short )0;
         sqlstm.sqtdso[28] = (unsigned short )0;
         sqlstm.sqhstv[29] = (         void  *)&(RAPFileSummary.TOTAL_CALL_EVENTS_PROCESSED);
         sqlstm.sqhstl[29] = (unsigned int  )sizeof(long);
         sqlstm.sqhsts[29] = (         int  )0;
         sqlstm.sqindv[29] = (         void  *)0;
         sqlstm.sqinds[29] = (         int  )0;
         sqlstm.sqharm[29] = (unsigned int  )0;
         sqlstm.sqadto[29] = (unsigned short )0;
         sqlstm.sqtdso[29] = (unsigned short )0;
         sqlstm.sqhstv[30] = (         void  *)&(RAPFileSummary.TOTAL_DURATION);
         sqlstm.sqhstl[30] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[30] = (         int  )0;
         sqlstm.sqindv[30] = (         void  *)0;
         sqlstm.sqinds[30] = (         int  )0;
         sqlstm.sqharm[30] = (unsigned int  )0;
         sqlstm.sqadto[30] = (unsigned short )0;
         sqlstm.sqtdso[30] = (unsigned short )0;
         sqlstm.sqhstv[31] = (         void  *)&(RAPFileSummary.TOTAL_OUTGOING_VOLUME);
         sqlstm.sqhstl[31] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[31] = (         int  )0;
         sqlstm.sqindv[31] = (         void  *)0;
         sqlstm.sqinds[31] = (         int  )0;
         sqlstm.sqharm[31] = (unsigned int  )0;
         sqlstm.sqadto[31] = (unsigned short )0;
         sqlstm.sqtdso[31] = (unsigned short )0;
         sqlstm.sqhstv[32] = (         void  *)&(RAPFileSummary.TOTAL_INCOMING_VOLUME);
         sqlstm.sqhstl[32] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[32] = (         int  )0;
         sqlstm.sqindv[32] = (         void  *)0;
         sqlstm.sqinds[32] = (         int  )0;
         sqlstm.sqharm[32] = (unsigned int  )0;
         sqlstm.sqadto[32] = (unsigned short )0;
         sqlstm.sqtdso[32] = (unsigned short )0;
         sqlstm.sqhstv[33] = (         void  *)&(RAPFileSummary.TAP_CURNCY_CHARGE);
         sqlstm.sqhstl[33] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[33] = (         int  )0;
         sqlstm.sqindv[33] = (         void  *)0;
         sqlstm.sqinds[33] = (         int  )0;
         sqlstm.sqharm[33] = (unsigned int  )0;
         sqlstm.sqadto[33] = (unsigned short )0;
         sqlstm.sqtdso[33] = (unsigned short )0;
         sqlstm.sqhstv[34] = (         void  *)&(RAPFileSummary.TAP_CURNCY_TAX);
         sqlstm.sqhstl[34] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[34] = (         int  )0;
         sqlstm.sqindv[34] = (         void  *)0;
         sqlstm.sqinds[34] = (         int  )0;
         sqlstm.sqharm[34] = (unsigned int  )0;
         sqlstm.sqadto[34] = (unsigned short )0;
         sqlstm.sqtdso[34] = (unsigned short )0;
         sqlstm.sqhstv[35] = (         void  *)&(RAPFileSummary.TAP_CURNCY_DISCOUNT);
         sqlstm.sqhstl[35] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[35] = (         int  )0;
         sqlstm.sqindv[35] = (         void  *)0;
         sqlstm.sqinds[35] = (         int  )0;
         sqlstm.sqharm[35] = (unsigned int  )0;
         sqlstm.sqadto[35] = (unsigned short )0;
         sqlstm.sqtdso[35] = (unsigned short )0;
         sqlstm.sqhstv[36] = (         void  *)&(RAPFileSummary.HOME_CURNCY_CHARGE);
         sqlstm.sqhstl[36] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[36] = (         int  )0;
         sqlstm.sqindv[36] = (         void  *)0;
         sqlstm.sqinds[36] = (         int  )0;
         sqlstm.sqharm[36] = (unsigned int  )0;
         sqlstm.sqadto[36] = (unsigned short )0;
         sqlstm.sqtdso[36] = (unsigned short )0;
         sqlstm.sqhstv[37] = (         void  *)&(RAPFileSummary.HOME_CURNCY_TAX);
         sqlstm.sqhstl[37] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[37] = (         int  )0;
         sqlstm.sqindv[37] = (         void  *)0;
         sqlstm.sqinds[37] = (         int  )0;
         sqlstm.sqharm[37] = (unsigned int  )0;
         sqlstm.sqadto[37] = (unsigned short )0;
         sqlstm.sqtdso[37] = (unsigned short )0;
         sqlstm.sqhstv[38] = (         void  *)&(RAPFileSummary.HOME_CURNCY_DISCOUNT);
         sqlstm.sqhstl[38] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[38] = (         int  )0;
         sqlstm.sqindv[38] = (         void  *)0;
         sqlstm.sqinds[38] = (         int  )0;
         sqlstm.sqharm[38] = (unsigned int  )0;
         sqlstm.sqadto[38] = (unsigned short )0;
         sqlstm.sqtdso[38] = (unsigned short )0;
         sqlstm.sqhstv[39] = (         void  *)&(RAPFileSummary.HOME_CURNCY_SURCHARGE);
         sqlstm.sqhstl[39] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[39] = (         int  )0;
         sqlstm.sqindv[39] = (         void  *)0;
         sqlstm.sqinds[39] = (         int  )0;
         sqlstm.sqharm[39] = (unsigned int  )0;
         sqlstm.sqadto[39] = (unsigned short )0;
         sqlstm.sqtdso[39] = (unsigned short )0;
         sqlstm.sqhstv[40] = (         void  *)(RAPFileSummary.PARTNER_CODE);
         sqlstm.sqhstl[40] = (unsigned int  )4;
         sqlstm.sqhsts[40] = (         int  )0;
         sqlstm.sqindv[40] = (         void  *)0;
         sqlstm.sqinds[40] = (         int  )0;
         sqlstm.sqharm[40] = (unsigned int  )0;
         sqlstm.sqadto[40] = (unsigned short )0;
         sqlstm.sqtdso[40] = (unsigned short )0;
         sqlstm.sqhstv[41] = (         void  *)&(RAPFileSummary.REJECTED_CALL_EVENTS);
         sqlstm.sqhstl[41] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[41] = (         int  )0;
         sqlstm.sqindv[41] = (         void  *)0;
         sqlstm.sqinds[41] = (         int  )0;
         sqlstm.sqharm[41] = (unsigned int  )0;
         sqlstm.sqadto[41] = (unsigned short )0;
         sqlstm.sqtdso[41] = (unsigned short )0;
         sqlstm.sqhstv[42] = (         void  *)&(RAPFileSummary.REJECTED_DURATION);
         sqlstm.sqhstl[42] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[42] = (         int  )0;
         sqlstm.sqindv[42] = (         void  *)0;
         sqlstm.sqinds[42] = (         int  )0;
         sqlstm.sqharm[42] = (unsigned int  )0;
         sqlstm.sqadto[42] = (unsigned short )0;
         sqlstm.sqtdso[42] = (unsigned short )0;
         sqlstm.sqhstv[43] = (         void  *)&(RAPFileSummary.REJECTED_OUTGOING_VOLUME);
         sqlstm.sqhstl[43] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[43] = (         int  )0;
         sqlstm.sqindv[43] = (         void  *)0;
         sqlstm.sqinds[43] = (         int  )0;
         sqlstm.sqharm[43] = (unsigned int  )0;
         sqlstm.sqadto[43] = (unsigned short )0;
         sqlstm.sqtdso[43] = (unsigned short )0;
         sqlstm.sqhstv[44] = (         void  *)&(RAPFileSummary.REJECTED_INCOMING_VOLUME);
         sqlstm.sqhstl[44] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[44] = (         int  )0;
         sqlstm.sqindv[44] = (         void  *)0;
         sqlstm.sqinds[44] = (         int  )0;
         sqlstm.sqharm[44] = (unsigned int  )0;
         sqlstm.sqadto[44] = (unsigned short )0;
         sqlstm.sqtdso[44] = (unsigned short )0;
         sqlstm.sqhstv[45] = (         void  *)(RAPFileSummary.RAP_ACKNOWLEDGEMENT_STATUS);
         sqlstm.sqhstl[45] = (unsigned int  )2;
         sqlstm.sqhsts[45] = (         int  )0;
         sqlstm.sqindv[45] = (         void  *)0;
         sqlstm.sqinds[45] = (         int  )0;
         sqlstm.sqharm[45] = (unsigned int  )0;
         sqlstm.sqadto[45] = (unsigned short )0;
         sqlstm.sqtdso[45] = (unsigned short )0;
         sqlstm.sqhstv[46] = (         void  *)&(RAPFileSummary.REJ_TAP_CURNCY_CHARGE);
         sqlstm.sqhstl[46] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[46] = (         int  )0;
         sqlstm.sqindv[46] = (         void  *)0;
         sqlstm.sqinds[46] = (         int  )0;
         sqlstm.sqharm[46] = (unsigned int  )0;
         sqlstm.sqadto[46] = (unsigned short )0;
         sqlstm.sqtdso[46] = (unsigned short )0;
         sqlstm.sqhstv[47] = (         void  *)&(RAPFileSummary.REJ_TAP_CURNCY_TAX);
         sqlstm.sqhstl[47] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[47] = (         int  )0;
         sqlstm.sqindv[47] = (         void  *)0;
         sqlstm.sqinds[47] = (         int  )0;
         sqlstm.sqharm[47] = (unsigned int  )0;
         sqlstm.sqadto[47] = (unsigned short )0;
         sqlstm.sqtdso[47] = (unsigned short )0;
         sqlstm.sqhstv[48] = (         void  *)&(RAPFileSummary.REJ_TAP_CURNCY_DISCOUNT);
         sqlstm.sqhstl[48] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[48] = (         int  )0;
         sqlstm.sqindv[48] = (         void  *)0;
         sqlstm.sqinds[48] = (         int  )0;
         sqlstm.sqharm[48] = (unsigned int  )0;
         sqlstm.sqadto[48] = (unsigned short )0;
         sqlstm.sqtdso[48] = (unsigned short )0;
         sqlstm.sqhstv[49] = (         void  *)&(RAPFileSummary.REJ_HOME_CURNCY_CHARGE);
         sqlstm.sqhstl[49] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[49] = (         int  )0;
         sqlstm.sqindv[49] = (         void  *)0;
         sqlstm.sqinds[49] = (         int  )0;
         sqlstm.sqharm[49] = (unsigned int  )0;
         sqlstm.sqadto[49] = (unsigned short )0;
         sqlstm.sqtdso[49] = (unsigned short )0;
         sqlstm.sqhstv[50] = (         void  *)&(RAPFileSummary.REJ_HOME_CURNCY_TAX);
         sqlstm.sqhstl[50] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[50] = (         int  )0;
         sqlstm.sqindv[50] = (         void  *)0;
         sqlstm.sqinds[50] = (         int  )0;
         sqlstm.sqharm[50] = (unsigned int  )0;
         sqlstm.sqadto[50] = (unsigned short )0;
         sqlstm.sqtdso[50] = (unsigned short )0;
         sqlstm.sqhstv[51] = (         void  *)&(RAPFileSummary.REJ_HOME_CURNCY_DISCOUNT);
         sqlstm.sqhstl[51] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[51] = (         int  )0;
         sqlstm.sqindv[51] = (         void  *)0;
         sqlstm.sqinds[51] = (         int  )0;
         sqlstm.sqharm[51] = (unsigned int  )0;
         sqlstm.sqadto[51] = (unsigned short )0;
         sqlstm.sqtdso[51] = (unsigned short )0;
         sqlstm.sqhstv[52] = (         void  *)(RAPFileSummary.FILE_TYPE_GENERATION);
         sqlstm.sqhstl[52] = (unsigned int  )2;
         sqlstm.sqhsts[52] = (         int  )0;
         sqlstm.sqindv[52] = (         void  *)0;
         sqlstm.sqinds[52] = (         int  )0;
         sqlstm.sqharm[52] = (unsigned int  )0;
         sqlstm.sqadto[52] = (unsigned short )0;
         sqlstm.sqtdso[52] = (unsigned short )0;
         sqlstm.sqphsv = sqlstm.sqhstv;
         sqlstm.sqphsl = sqlstm.sqhstl;
         sqlstm.sqphss = sqlstm.sqhsts;
         sqlstm.sqpind = sqlstm.sqindv;
         sqlstm.sqpins = sqlstm.sqinds;
         sqlstm.sqparm = sqlstm.sqharm;
         sqlstm.sqparc = sqlstm.sqharc;
         sqlstm.sqpadto = sqlstm.sqadto;
         sqlstm.sqptdso = sqlstm.sqtdso;
         sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


   
         if(ERRCODE != 0)
         {
             stErrors.ERROR_CODE = sqlca.sqlcode;
             strcpy(stErrors.ERROR_DESC,"Error Inserting Record into PM_RAP_FILE_SUMARY table");

             TRACEENTRY(1,"%s","Error Inserting Record into PM_RAP_FILE_SUMARY table");
             TRACEENTRY(1,"%s -%d-","ERROR : sqlca.sqlcode :",ERRCODE);
             if(ERRCODE != -1)
             {
                TRACEENTRY(1,"%s","String Values Below --------------");
                TRACEENTRY(1,"FILE_TRANSFER_DIRECTION          : -%s-",RAPFileSummary.FILE_TRANSFER_DIRECTION)         ;
                TRACEENTRY(1,"HPLMN_CODE                       : -%s-",RAPFileSummary.HPLMN_CODE)                      ;
                TRACEENTRY(1,"VPLMN_CODE                       : -%s-",RAPFileSummary.VPLMN_CODE)                      ;
                TRACEENTRY(1,"FILE_TYPE_INDICATOR              : -%s-",RAPFileSummary.FILE_TYPE_INDICATOR)             ;
                TRACEENTRY(1,"RAP_FILE_NAME                    : -%s-",RAPFileSummary.RAP_FILE_NAME)                   ;
                TRACEENTRY(1,"TAP_FILE_NAME                    : -%s-",RAPFileSummary.TAP_FILE_NAME)                   ;
                TRACEENTRY(1,"DATA_TYPE_INDICATOR              : -%s-",RAPFileSummary.DATA_TYPE_INDICATOR)             ;
                TRACEENTRY(1,"ERROR_TYPE                       : -%s-",RAPFileSummary.ERROR_TYPE)                      ;
                TRACEENTRY(1,"FILE_CREATION_TIME               : -%s-",RAPFileSummary.FILE_CREATION_TIME)              ;
                TRACEENTRY(1,"FILE_CREATION_TIME_UTC_OFFSET    : -%s-",RAPFileSummary.FILE_CREATION_TIME_UTC_OFFSET)   ;
                TRACEENTRY(1,"FILE_AVAILABLE_TIME              : -%s-",RAPFileSummary.FILE_AVAILABLE_TIME)             ;
                TRACEENTRY(1,"FILE_AVAILABLE_TIME_UTC_OFFSET   : -%s-",RAPFileSummary.FILE_AVAILABLE_TIME_UTC_OFFSET)  ;
                TRACEENTRY(1,"ISO_PLMN_CURNCY_CODE             : -%s-",RAPFileSummary.ISO_PLMN_CURNCY_CODE)            ;
                TRACEENTRY(1,"TAP_CURNCY_CODE                  : -%s-",RAPFileSummary.TAP_CURNCY_CODE)                 ;
                TRACEENTRY(1,"FILE_PROCESS_DATE                : -%s-",RAPFileSummary.FILE_PROCESS_DATE)               ;
                TRACEENTRY(1,"FILE_PROCESSED_BY                : -%s-",RAPFileSummary.FILE_PROCESSED_BY)               ;
                TRACEENTRY(1,"FILE_PROCESS_STATUS              : -%s-",RAPFileSummary.FILE_PROCESS_STATUS)             ;
                TRACEENTRY(1,"PARTNER_CODE                     : -%s-",RAPFileSummary.PARTNER_CODE)                    ;
                TRACEENTRY(1,"RAP_ACKNOWLEDGEMENT_STATUS       : -%s-",RAPFileSummary.RAP_ACKNOWLEDGEMENT_STATUS)      ;
                TRACEENTRY(1,"FILE_TYPE_GENERATION             : -%s-",RAPFileSummary.FILE_TYPE_GENERATION)            ;

                TRACEENTRY(1,"%s","Number Values Below --------------");
                TRACEENTRY(1,"FILE_SEQUENCE_NUMBER	       : -%d-",RAPFileSummary.FILE_SEQUENCE_NUMBER)            ;
                TRACEENTRY(1,"START_MISSING_SEQ_NO	       : -%d-",RAPFileSummary.START_MISSING_SEQ_NO)            ;
                TRACEENTRY(1,"END_MISSING_SEQ_NO	       : -%d-",RAPFileSummary.END_MISSING_SEQ_NO)              ;
                TRACEENTRY(1,"RAP_SPECIFICATION_VERSION        : -%d-",RAPFileSummary.RAP_SPECIFICATION_VERSION)       ;
                TRACEENTRY(1,"RAP_RELEASE_VERSION	       : -%d-",RAPFileSummary.RAP_RELEASE_VERSION)             ;
                TRACEENTRY(1,"TAP_SPECIFICATION_VERSION        : -%d-",RAPFileSummary.TAP_SPECIFICATION_VERSION)       ;
                TRACEENTRY(1,"TAP_RELEASE_VERSION	       : -%d-",RAPFileSummary.TAP_RELEASE_VERSION)             ;
                TRACEENTRY(1,"TAP_CURNCY_DECIMAL_PLACES        : -%d-",RAPFileSummary.TAP_CURNCY_DECIMAL_PLACES)       ;
                TRACEENTRY(1,"TAP_CURNCY_MULT_FACT	       : -%f-",RAPFileSummary.TAP_CURNCY_MULT_FACT)            ;
                TRACEENTRY(1,"TAP_CURNCY_ROUNDOFF_DECIMAL      : -%d-",RAPFileSummary.TAP_CURNCY_ROUNDOFF_DECIMAL)     ;
                TRACEENTRY(1,"HOME_CURNCY_ROUNDOFF_DECIMAL     : -%d-",RAPFileSummary.HOME_CURNCY_ROUNDOFF_DECIMAL)    ;
                TRACEENTRY(1,"TOTAL_ERROR_COUNT		       : -%d-",RAPFileSummary.TOTAL_ERROR_COUNT)               ;
                TRACEENTRY(1,"TOTAL_CALL_EVENTS		       : -%d-",RAPFileSummary.TOTAL_CALL_EVENTS)               ;
                TRACEENTRY(1,"TOTAL_CALL_EVENTS_PROCESSED      : -%d-",RAPFileSummary.TOTAL_CALL_EVENTS_PROCESSED)     ;
                TRACEENTRY(1,"TOTAL_DURATION		       : -%f-",RAPFileSummary.TOTAL_DURATION)                  ;
                TRACEENTRY(1,"TOTAL_OUTGOING_VOLUME	       : -%f-",RAPFileSummary.TOTAL_OUTGOING_VOLUME)           ;
                TRACEENTRY(1,"TOTAL_INCOMING_VOLUME            : -%f-",RAPFileSummary.TOTAL_INCOMING_VOLUME)           ;
                TRACEENTRY(1,"TAP_CURNCY_CHARGE                : -%f-",RAPFileSummary.TAP_CURNCY_CHARGE)               ;
                TRACEENTRY(1,"TAP_CURNCY_TAX                   : -%f-",RAPFileSummary.TAP_CURNCY_TAX)                  ;
                TRACEENTRY(1,"TAP_CURNCY_DISCOUNT              : -%f-",RAPFileSummary.TAP_CURNCY_DISCOUNT)             ;
                TRACEENTRY(1,"HOME_CURNCY_CHARGE               : -%f-",RAPFileSummary.HOME_CURNCY_CHARGE)              ;
                TRACEENTRY(1,"HOME_CURNCY_TAX                  : -%f-",RAPFileSummary.HOME_CURNCY_TAX)                 ; 
                TRACEENTRY(1,"HOME_CURNCY_DISCOUNT             : -%f-",RAPFileSummary.HOME_CURNCY_DISCOUNT)            ;
                TRACEENTRY(1,"HOME_CURNCY_SURCHARGE            : -%f-",RAPFileSummary.HOME_CURNCY_SURCHARGE)           ;
                TRACEENTRY(1,"SURCHARGE_PERCENTAGE             : -%f-",RAPFileSummary.SURCHARGE_PERCENTAGE)            ;
                TRACEENTRY(1,"REJECTED_CALL_EVENTS             : -%d-",RAPFileSummary.REJECTED_CALL_EVENTS)            ;
                TRACEENTRY(1,"REJECTED_DURATION                : -%f-",RAPFileSummary.REJECTED_DURATION)               ;
                TRACEENTRY(1,"REJECTED_OUTGOING_VOLUME         : -%f-",RAPFileSummary.REJECTED_OUTGOING_VOLUME)        ;
                TRACEENTRY(1,"REJECTED_INCOMING_VOLUME         : -%f-",RAPFileSummary.REJECTED_INCOMING_VOLUME)        ;
                TRACEENTRY(1,"REJ_TAP_CURNCY_CHARGE            : -%f-",RAPFileSummary.REJ_TAP_CURNCY_CHARGE)           ;
                TRACEENTRY(1,"REJ_TAP_CURNCY_TAX               : -%f-",RAPFileSummary.REJ_TAP_CURNCY_TAX)              ;
                TRACEENTRY(1,"REJ_TAP_CURNCY_DISCOUNT          : -%f-",RAPFileSummary.REJ_TAP_CURNCY_DISCOUNT)         ;
                TRACEENTRY(1,"REJ_HOME_CURNCY_CHARGE           : -%f-",RAPFileSummary.REJ_HOME_CURNCY_CHARGE)          ;
                TRACEENTRY(1,"REJ_HOME_CURNCY_TAX              : -%f-",RAPFileSummary.REJ_HOME_CURNCY_TAX)             ;
                TRACEENTRY(1,"REJ_HOME_CURNCY_DISCOUNT         : -%f-",RAPFileSummary.REJ_HOME_CURNCY_DISCOUNT)        ;
             }
             return -1;
         }


         /* Update the FileSequenceNumber for the Operator */
         /* EXEC SQL UPDATE PM_ROAM_PARTNER_FILE_INFO
                     SET FILE_SEQUENCE_NUMBER = FILE_SEQUENCE_NUMBER + 1
                   WHERE trim(PARTNER_CODE) = :RAPFileSummary.PARTNER_CODE
                     AND PROCESS_ID = :gRAPProcessId
                     AND DATA_TYPE = :RAPFileSummary.FILE_TYPE_INDICATOR; */ 

{
         struct sqlexd sqlstm;
         sqlstm.sqlvsn = 12;
         sqlstm.arrsiz = 129;
         sqlstm.sqladtp = &sqladt;
         sqlstm.sqltdsp = &sqltds;
         sqlstm.stmt = "update PM_ROAM_PARTNER_FILE_INFO  set FILE_SEQUENCE_\
NUMBER=(FILE_SEQUENCE_NUMBER+1) where ((trim(PARTNER_CODE)=:b0 and PROCESS_ID=\
:b1) and DATA_TYPE=:b2)";
         sqlstm.iters = (unsigned int  )1;
         sqlstm.offset = (unsigned int  )5415;
         sqlstm.cud = sqlcud0;
         sqlstm.sqlest = (unsigned char  *)&sqlca;
         sqlstm.sqlety = (unsigned short)4352;
         sqlstm.occurs = (unsigned int  )0;
         sqlstm.sqhstv[0] = (         void  *)(RAPFileSummary.PARTNER_CODE);
         sqlstm.sqhstl[0] = (unsigned int  )4;
         sqlstm.sqhsts[0] = (         int  )0;
         sqlstm.sqindv[0] = (         void  *)0;
         sqlstm.sqinds[0] = (         int  )0;
         sqlstm.sqharm[0] = (unsigned int  )0;
         sqlstm.sqadto[0] = (unsigned short )0;
         sqlstm.sqtdso[0] = (unsigned short )0;
         sqlstm.sqhstv[1] = (         void  *)&gRAPProcessId;
         sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[1] = (         int  )0;
         sqlstm.sqindv[1] = (         void  *)0;
         sqlstm.sqinds[1] = (         int  )0;
         sqlstm.sqharm[1] = (unsigned int  )0;
         sqlstm.sqadto[1] = (unsigned short )0;
         sqlstm.sqtdso[1] = (unsigned short )0;
         sqlstm.sqhstv[2] = (         void  *)(RAPFileSummary.FILE_TYPE_INDICATOR);
         sqlstm.sqhstl[2] = (unsigned int  )2;
         sqlstm.sqhsts[2] = (         int  )0;
         sqlstm.sqindv[2] = (         void  *)0;
         sqlstm.sqinds[2] = (         int  )0;
         sqlstm.sqharm[2] = (unsigned int  )0;
         sqlstm.sqadto[2] = (unsigned short )0;
         sqlstm.sqtdso[2] = (unsigned short )0;
         sqlstm.sqphsv = sqlstm.sqhstv;
         sqlstm.sqphsl = sqlstm.sqhstl;
         sqlstm.sqphss = sqlstm.sqhsts;
         sqlstm.sqpind = sqlstm.sqindv;
         sqlstm.sqpins = sqlstm.sqinds;
         sqlstm.sqparm = sqlstm.sqharm;
         sqlstm.sqparc = sqlstm.sqharc;
         sqlstm.sqpadto = sqlstm.sqadto;
         sqlstm.sqptdso = sqlstm.sqtdso;
         sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



         if(ERRCODE!=0)
         {
            TRACEENTRY(1,"%s-%s-","Error Updating PM_ROAM_PARTNER_FILE_INFO for PartnerCode :",RAPFileSummary.PARTNER_CODE);
            TRACEENTRY(1,"%s-%s-","DataTypeIndicator :",RAPFileSummary.FILE_TYPE_INDICATOR);
            TRACEENTRY(1,"%s-%d-","sqlca.sqlcode :",ERRCODE);
            TRACEENTRY(1,"%s","Cannot Proceed for this Operator");
            /* EXEC SQL ROLLBACK; */ 

{
            struct sqlexd sqlstm;
            sqlstm.sqlvsn = 12;
            sqlstm.arrsiz = 129;
            sqlstm.sqladtp = &sqladt;
            sqlstm.sqltdsp = &sqltds;
            sqlstm.iters = (unsigned int  )1;
            sqlstm.offset = (unsigned int  )5442;
            sqlstm.cud = sqlcud0;
            sqlstm.sqlest = (unsigned char  *)&sqlca;
            sqlstm.sqlety = (unsigned short)4352;
            sqlstm.occurs = (unsigned int  )0;
            sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


            return -1;
         }

         return 0;
}


void fnSortDir(char **filename,int count)
{
        char    tempname[MAX_FILE_SIZE]="";
        int k,i;

        for(i=0;i<count;i++)
        {
                for(k=i+1;k<count;k++)
                {
                        if(strcmp(filename[i],filename[k])>0)
                        {
                                strcpy(tempname,filename[i]);
                                strcpy(filename[i],filename[k]);
                                strcpy(filename[k],tempname);
                        }
                }
        }
}

int fnDirFiles(char *pszDirName)
{
        DIR *dirp;
        char tempbuf[1024];
        char  *pstr;
        int index;
        char szParentDir[1024] = {'\0'};
        char szFilePath[1024] = {'\0'};
        struct dirent *dp;
        struct stat statbuf;

        if (strlen(pszDirName) <= 0)
        {
                return 1;
        }

        fnFreeMemory();

        strcpy (szParentDir, pszDirName);

        /* Open directory */

        dirp = opendir(szParentDir);

        if (dirp == NULL)
        {
                perror("");
                /* EXEC SQL COMMIT WORK RELEASE; */ 

{
                struct sqlexd sqlstm;
                sqlstm.sqlvsn = 12;
                sqlstm.arrsiz = 129;
                sqlstm.sqladtp = &sqladt;
                sqlstm.sqltdsp = &sqltds;
                sqlstm.iters = (unsigned int  )1;
                sqlstm.offset = (unsigned int  )5457;
                sqlstm.cud = sqlcud0;
                sqlstm.sqlest = (unsigned char  *)&sqlca;
                sqlstm.sqlety = (unsigned short)4352;
                sqlstm.occurs = (unsigned int  )0;
                sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


                exit(1);
        }
        /*
        ** Read directory
        */

        while ((dp = readdir(dirp)) != NULL )
        {
                memset(szFilePath,0,sizeof(szFilePath));
                sprintf(szFilePath, "%s/%s",szParentDir, dp->d_name);
                if (stat(szFilePath, &statbuf) != 0)
                {
                        return 1;
                }
                if ( !(statbuf.st_mode & S_IFDIR))
                {
                        g_fileNamesPtr[g_fileCount] = malloc(MAX_FILE_SIZE);
                        INIT_STR(g_fileNamesPtr[g_fileCount]);

                        if (!g_fileNamesPtr[g_fileCount])
                        {
                                return 1;
                        }

                        strcpy (g_fileNamesPtr[g_fileCount], dp->d_name);
                        ++g_fileCount;

                        if(g_fileCount == MAX_NUM_FILES)
                        {
                        	break;
                        }
                }
        }

        closedir(dirp);

        fnSortDir(g_fileNamesPtr, g_fileCount) ;

        #ifdef DEBUG

        for (index = 0; index < g_fileCount; ++index)
        {
                sprintf(g_logBuf,"fnDirFiles:: Filename %s",g_fileNamesPtr[index]);
                fnLogMsg (g_logBuf,g_lfPtr);
        }

        #endif

        /* Done */

        return 0;

}

void fnFreeMemory()
{
        int index = 0;

        for(index = 0; index < g_fileCount; ++index)
        {
                if(g_fileNamesPtr[index])
                        free (g_fileNamesPtr[index]);
        }

        g_fileCount = 0;
        return;
}

void LogError()
{
   /* EXEC SQL INSERT INTO PM_TAP_ERRORS
   (PROCESS_DATE, FILE_NAME,FILE_STATUS, ERROR_CODE, ERROR_DESC)
   VALUES
   (
     TRUNC(SYSDATE),
     :stErrors.FILE_NAME,
     'F',
     :stErrors.ERROR_CODE,
     :stErrors.ERROR_DESC
   ); */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 129;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "insert into PM_TAP_ERRORS (PROCESS_DATE,FILE_NAME,FILE_STA\
TUS,ERROR_CODE,ERROR_DESC) values (TRUNC(SYSDATE),:b0,'F',:b1,:b2)";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )5472;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)(stErrors.FILE_NAME);
   sqlstm.sqhstl[0] = (unsigned int  )31;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)&(stErrors.ERROR_CODE);
   sqlstm.sqhstl[1] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)(stErrors.ERROR_DESC);
   sqlstm.sqhstl[2] = (unsigned int  )151;
   sqlstm.sqhsts[2] = (         int  )0;
   sqlstm.sqindv[2] = (         void  *)0;
   sqlstm.sqinds[2] = (         int  )0;
   sqlstm.sqharm[2] = (unsigned int  )0;
   sqlstm.sqadto[2] = (unsigned short )0;
   sqlstm.sqtdso[2] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   /* EXEC SQL COMMIT; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 129;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )5499;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


}

void LogSuccess()
{
   /* EXEC SQL INSERT INTO PM_TAP_ERRORS
   (PROCESS_DATE, FILE_NAME,FILE_STATUS, ERROR_CODE, ERROR_DESC)
   VALUES
   (
     TRUNC(SYSDATE),
     :stErrors.FILE_NAME,
     'S',
     :stErrors.ERROR_CODE,
     :stErrors.ERROR_DESC
   ); */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 129;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "insert into PM_TAP_ERRORS (PROCESS_DATE,FILE_NAME,FILE_STA\
TUS,ERROR_CODE,ERROR_DESC) values (TRUNC(SYSDATE),:b0,'S',:b1,:b2)";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )5514;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)(stErrors.FILE_NAME);
   sqlstm.sqhstl[0] = (unsigned int  )31;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)&(stErrors.ERROR_CODE);
   sqlstm.sqhstl[1] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)(stErrors.ERROR_DESC);
   sqlstm.sqhstl[2] = (unsigned int  )151;
   sqlstm.sqhsts[2] = (         int  )0;
   sqlstm.sqindv[2] = (         void  *)0;
   sqlstm.sqinds[2] = (         int  )0;
   sqlstm.sqharm[2] = (unsigned int  )0;
   sqlstm.sqadto[2] = (unsigned short )0;
   sqlstm.sqtdso[2] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


   /* EXEC SQL COMMIT; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 129;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )5541;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


}

void InitialiseBCI()
{
   /**** Initialise Structure Elements ****/
   INIT_STR(BCI.Sender);
   INIT_STR(BCI.Recipient);
   BCI.FileSequenceNumber = 0;
   INIT_STR(BCI.FileCreationTimeStamp.LocalTimeStamp);
   INIT_STR(BCI.FileCreationTimeStamp.UtcTimeOffset);
   INIT_STR(BCI.TransferCutOffTimeStamp.LocalTimeStamp);
   INIT_STR(BCI.TransferCutOffTimeStamp.UtcTimeOffset);
   INIT_STR(BCI.FileAvailableTimeStamp.LocalTimeStamp);
   INIT_STR(BCI.FileAvailableTimeStamp.UtcTimeOffset);
   BCI.SpecificationVersionNumber  = 0;
   BCI.ReleaseVersionNumber        = 0;
   INIT_STR(BCI.FileTypeIndicator);
   BCI.RapFileSequenceNumber       = 0;
}

void InitialiseACC()
{
   int i=0;

   /**** Initialise Structure Elements to Null or zero ****/
   for(i=0;i<TOTAL_TAX;i++)
   {
      ACC.Taxation[i].TaxCode    = 0;
      INIT_STR(ACC.Taxation[i].TaxType);
      ACC.Taxation[i].TaxRate    = 0;
      INIT_STR(ACC.Taxation[i].ChargeType);
   }

   for(i=0;i<TOTAL_DISCOUNT;i++)
   {
      ACC.Discounting[i].DiscountCode = 0;
      INIT_STR(ACC.Discounting[i].DiscountType);
      ACC.Discounting[i].FixedDiscountValue = 0;
      ACC.Discounting[i].DiscountRate       = 0;
   }

   INIT_STR(ACC.LocalCurrency);
   INIT_STR(ACC.TapCurrency);

   for(i=0;i<TOTAL_CURRENCY;i++)
   {
      ACC.CurrencyConversionInfo[i].ExchangeRateCode            =       0;
      ACC.CurrencyConversionInfo[i].NumberOfDecimalPlaces       =       0;
      ACC.CurrencyConversionInfo[i].ExchangeRate                =       0;
   }

   ACC.TapDecimalPlaces                                         =       0;
   ACC.TotalTax                                                 =       0;
   ACC.TotalDiscount                                            =       0;
   ACC.TotalCurrency                                            =       0;
}

void InitialiseNI()
{
   int i=0;

   /**** Initialise Structure Elements to Null or zero ****/
   for(i=0;i<TOTAL_UTC;i++)
   {
      NI.UtcTimeOffsetInfo[i].UtcTimeOffsetCode         = 0;
      INIT_STR(NI.UtcTimeOffsetInfo[i].UtcTimeOffset);
   }

   for(i=0;i<TOTAL_REC;i++)
   {
      NI.RecEntityInfo[i].RecEntityCode                 = 0;
      NI.RecEntityInfo[i].RecEntityType                 = 0;
      INIT_STR(NI.RecEntityInfo[i].RecEntityId);
   }

   NI.TotalUtc                                          = 0;
   NI.TotalRecEntity                                    = 0;
}

void InitialiseACI()
{
   int i=0;

   /**** Initialise Structure Elements to Null or zero ****/
   INIT_STR(ACI.EarliestCallTimeStamp.LocalTimeStamp);
   INIT_STR(ACI.EarliestCallTimeStamp.UtcTimeOffset);
   INIT_STR(ACI.LatestCallTimeStamp.LocalTimeStamp);
   INIT_STR(ACI.LatestCallTimeStamp.UtcTimeOffset);
   ACI.TotalCharge                             = 0;
   ACI.TotalChargeRefund                       = 0;
   ACI.TotalTaxRefund                          = 0;
   ACI.TotalTaxValue                           = 0;
   ACI.TotalDiscountValue                      = 0;
   ACI.TotalDiscountRefund                     = 0;

   for(i=0;i<TOTAL_ACV;i++)
   {
      INIT_STR(ACI.TotalAdvisedChargeValue[i].AdvisedChargeCurrency);
      ACI.TotalAdvisedChargeValue[i].TotalAdvisedCharge        = 0;
      ACI.TotalAdvisedChargeValue[i].TotalAdvisedChargeRefund  = 0;
      ACI.TotalAdvisedChargeValue[i].TotalCommission           = 0;
      ACI.TotalAdvisedChargeValue[i].TotalCommissionRefund     = 0;
   }

   ACI.CallEventDetailsCount                   = 0;
   ACI.TotalACValue                            = 0;
}


void InitialiseMissingFiles()
{
   int i=0;
   
   /* Initialise the Structure Members */
   for(i=0;i<MAX_MISSING_FILES;i++)
   {
      INIT_STR(stMissingFiles[i].FILE_TRANSFER_DIRECTION);
      INIT_STR(stMissingFiles[i].HPLMN_CODE);
      INIT_STR(stMissingFiles[i].VPLMN_CODE);
      INIT_STR(stMissingFiles[i].FILE_TYPE_INDICATOR);
      stMissingFiles[i].FILE_SEQUENCE_NUMBER = 0;
      INIT_STR(stMissingFiles[i].FILE_STATUS);
      INIT_STR(stMissingFiles[i].FILE_AVAILABLE_TIME);
      INIT_STR(stMissingFiles[i].FILE_EXPECTED_TIME);
   }
}

void SetMissingFiles(int TotalMissingFiles)
{
   int i=0;
 

   /* EXEC SQL FOR :TotalMissingFiles
   INSERT INTO PM_MISSING_TAP_FILES
   (
         FILE_TRANSFER_DIRECTION, HPLMN_CODE, VPLMN_CODE, FILE_TYPE_INDICATOR,
         FILE_SEQUENCE_NUMBER, FILE_STATUS, FILE_AVAILABLE_TIME, FILE_EXPECTED_TIME
   )
   VALUES
   (:stMissingFiles); */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 129;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "insert into PM_MISSING_TAP_FILES (FILE_TRANSFER_DIRECTION,\
HPLMN_CODE,VPLMN_CODE,FILE_TYPE_INDICATOR,FILE_SEQUENCE_NUMBER,FILE_STATUS,FIL\
E_AVAILABLE_TIME,FILE_EXPECTED_TIME) values (:s1 ,:s2 ,:s3 ,:s4 ,:s5 ,:s6 ,:s7\
 ,:s8 )";
   sqlstm.iters = (unsigned int  )TotalMissingFiles;
   sqlstm.offset = (unsigned int  )5556;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)stMissingFiles->FILE_TRANSFER_DIRECTION;
   sqlstm.sqhstl[0] = (unsigned int  )2;
   sqlstm.sqhsts[0] = (         int  )sizeof(struct PM_MISSING_TAP_FILES);
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqharc[0] = (unsigned int   *)0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)stMissingFiles->HPLMN_CODE;
   sqlstm.sqhstl[1] = (unsigned int  )6;
   sqlstm.sqhsts[1] = (         int  )sizeof(struct PM_MISSING_TAP_FILES);
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqharc[1] = (unsigned int   *)0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)stMissingFiles->VPLMN_CODE;
   sqlstm.sqhstl[2] = (unsigned int  )6;
   sqlstm.sqhsts[2] = (         int  )sizeof(struct PM_MISSING_TAP_FILES);
   sqlstm.sqindv[2] = (         void  *)0;
   sqlstm.sqinds[2] = (         int  )0;
   sqlstm.sqharm[2] = (unsigned int  )0;
   sqlstm.sqharc[2] = (unsigned int   *)0;
   sqlstm.sqadto[2] = (unsigned short )0;
   sqlstm.sqtdso[2] = (unsigned short )0;
   sqlstm.sqhstv[3] = (         void  *)stMissingFiles->FILE_TYPE_INDICATOR;
   sqlstm.sqhstl[3] = (unsigned int  )2;
   sqlstm.sqhsts[3] = (         int  )sizeof(struct PM_MISSING_TAP_FILES);
   sqlstm.sqindv[3] = (         void  *)0;
   sqlstm.sqinds[3] = (         int  )0;
   sqlstm.sqharm[3] = (unsigned int  )0;
   sqlstm.sqharc[3] = (unsigned int   *)0;
   sqlstm.sqadto[3] = (unsigned short )0;
   sqlstm.sqtdso[3] = (unsigned short )0;
   sqlstm.sqhstv[4] = (         void  *)&stMissingFiles->FILE_SEQUENCE_NUMBER;
   sqlstm.sqhstl[4] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[4] = (         int  )sizeof(struct PM_MISSING_TAP_FILES);
   sqlstm.sqindv[4] = (         void  *)0;
   sqlstm.sqinds[4] = (         int  )0;
   sqlstm.sqharm[4] = (unsigned int  )0;
   sqlstm.sqharc[4] = (unsigned int   *)0;
   sqlstm.sqadto[4] = (unsigned short )0;
   sqlstm.sqtdso[4] = (unsigned short )0;
   sqlstm.sqhstv[5] = (         void  *)stMissingFiles->FILE_STATUS;
   sqlstm.sqhstl[5] = (unsigned int  )2;
   sqlstm.sqhsts[5] = (         int  )sizeof(struct PM_MISSING_TAP_FILES);
   sqlstm.sqindv[5] = (         void  *)0;
   sqlstm.sqinds[5] = (         int  )0;
   sqlstm.sqharm[5] = (unsigned int  )0;
   sqlstm.sqharc[5] = (unsigned int   *)0;
   sqlstm.sqadto[5] = (unsigned short )0;
   sqlstm.sqtdso[5] = (unsigned short )0;
   sqlstm.sqhstv[6] = (         void  *)stMissingFiles->FILE_AVAILABLE_TIME;
   sqlstm.sqhstl[6] = (unsigned int  )15;
   sqlstm.sqhsts[6] = (         int  )sizeof(struct PM_MISSING_TAP_FILES);
   sqlstm.sqindv[6] = (         void  *)0;
   sqlstm.sqinds[6] = (         int  )0;
   sqlstm.sqharm[6] = (unsigned int  )0;
   sqlstm.sqharc[6] = (unsigned int   *)0;
   sqlstm.sqadto[6] = (unsigned short )0;
   sqlstm.sqtdso[6] = (unsigned short )0;
   sqlstm.sqhstv[7] = (         void  *)stMissingFiles->FILE_EXPECTED_TIME;
   sqlstm.sqhstl[7] = (unsigned int  )15;
   sqlstm.sqhsts[7] = (         int  )sizeof(struct PM_MISSING_TAP_FILES);
   sqlstm.sqindv[7] = (         void  *)0;
   sqlstm.sqinds[7] = (         int  )0;
   sqlstm.sqharm[7] = (unsigned int  )0;
   sqlstm.sqharc[7] = (unsigned int   *)0;
   sqlstm.sqadto[7] = (unsigned short )0;
   sqlstm.sqtdso[7] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   if(ERRCODE!=0)
   {
      i = sqlca.sqlerrd[2];

      TRACEENTRY(1,"%s","ERROR: Error Inserting Data into PM_MISSING_TAP_FILES table");
      TRACEENTRY(1,"%s -%d-","sqlca.sqlcode :",ERRCODE);
      TRACEENTRY(1,"FILE_TRANSFER_DIRECTION : -%s-",stMissingFiles[i].FILE_TRANSFER_DIRECTION);
      TRACEENTRY(1,"HPLMN_CODE              : -%s-",stMissingFiles[i].HPLMN_CODE);
      TRACEENTRY(1,"VPLMN_CODE              : -%s-",stMissingFiles[i].VPLMN_CODE);
      TRACEENTRY(1,"FILE_TYPE_INDICATOR     : -%s-",stMissingFiles[i].FILE_TYPE_INDICATOR);
      TRACEENTRY(1,"FILE_SEQUENCE_NUMBER    : -%d-",stMissingFiles[i].FILE_SEQUENCE_NUMBER);
      TRACEENTRY(1,"FILE_STATUS             : -%s-",stMissingFiles[i].FILE_STATUS);
      TRACEENTRY(1,"FILE_AVAILABLE_TIME     : -%s-",stMissingFiles[i].FILE_AVAILABLE_TIME);
      TRACEENTRY(1,"FILE_EXPECTED_TIME      : -%s-",stMissingFiles[i].FILE_EXPECTED_TIME);
   }
}

void UpdateMissingFiles()
{
   /* Declare Local Variables and Initialise the Data */
   int  i=0;
   int  j=0;
   int  TotalFilesReceived=0;
   int  MaxFileSequenceNumber=0;
   int  GenerateRecordsCount=0;
   int  GenerateFromSequence=0;
   int  GenerateTillSequence=0;
   char FileExpectedTime[15] ;
   long MissingFileCount ;

   INIT_STR(FileExpectedTime) ;

   /* Get the count from PM_MISSING_TAP_FILES for the operator for the FileTypeIndicator */
   /* EXEC SQL SELECT NVL(MAX(FILE_SEQUENCE_NUMBER),0),
                   TO_CHAR(NVL(MAX(FILE_EXPECTED_TIME),SYSDATE),'YYYYMMDDHH24MISS'),
                   COUNT(1)
              INTO :MaxFileSequenceNumber,
                   :FileExpectedTime,
                   :TotalFilesReceived
              FROM PM_MISSING_TAP_FILES
             WHERE FILE_TRANSFER_DIRECTION = 'I'
               AND HPLMN_CODE              = :FileSummary.HPLMN_CODE
               AND VPLMN_CODE              = :FileSummary.VPLMN_CODE
               AND FILE_TYPE_INDICATOR     = :FileSummary.FILE_TYPE_INDICATOR; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 129;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select NVL(max(FILE_SEQUENCE_NUMBER),0) ,TO_CHAR(NVL(max(F\
ILE_EXPECTED_TIME),SYSDATE),'YYYYMMDDHH24MISS') ,count(1) into :b0,:b1,:b2  fr\
om PM_MISSING_TAP_FILES where (((FILE_TRANSFER_DIRECTION='I' and HPLMN_CODE=:b\
3) and VPLMN_CODE=:b4) and FILE_TYPE_INDICATOR=:b5)";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )5603;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&MaxFileSequenceNumber;
   sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)FileExpectedTime;
   sqlstm.sqhstl[1] = (unsigned int  )15;
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)&TotalFilesReceived;
   sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[2] = (         int  )0;
   sqlstm.sqindv[2] = (         void  *)0;
   sqlstm.sqinds[2] = (         int  )0;
   sqlstm.sqharm[2] = (unsigned int  )0;
   sqlstm.sqadto[2] = (unsigned short )0;
   sqlstm.sqtdso[2] = (unsigned short )0;
   sqlstm.sqhstv[3] = (         void  *)(FileSummary.HPLMN_CODE);
   sqlstm.sqhstl[3] = (unsigned int  )6;
   sqlstm.sqhsts[3] = (         int  )0;
   sqlstm.sqindv[3] = (         void  *)0;
   sqlstm.sqinds[3] = (         int  )0;
   sqlstm.sqharm[3] = (unsigned int  )0;
   sqlstm.sqadto[3] = (unsigned short )0;
   sqlstm.sqtdso[3] = (unsigned short )0;
   sqlstm.sqhstv[4] = (         void  *)(FileSummary.VPLMN_CODE);
   sqlstm.sqhstl[4] = (unsigned int  )7;
   sqlstm.sqhsts[4] = (         int  )0;
   sqlstm.sqindv[4] = (         void  *)0;
   sqlstm.sqinds[4] = (         int  )0;
   sqlstm.sqharm[4] = (unsigned int  )0;
   sqlstm.sqadto[4] = (unsigned short )0;
   sqlstm.sqtdso[4] = (unsigned short )0;
   sqlstm.sqhstv[5] = (         void  *)(FileSummary.FILE_TYPE_INDICATOR);
   sqlstm.sqhstl[5] = (unsigned int  )2;
   sqlstm.sqhsts[5] = (         int  )0;
   sqlstm.sqindv[5] = (         void  *)0;
   sqlstm.sqinds[5] = (         int  )0;
   sqlstm.sqharm[5] = (unsigned int  )0;
   sqlstm.sqadto[5] = (unsigned short )0;
   sqlstm.sqtdso[5] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   if(ERRCODE!=0)
   {
      TRACEENTRY(1,"%s","ERROR: Error fetching count from PM_MISSING_TAP_FILES");
      TRACEENTRY(1,"%s -%d-","sqlca.sqlcode :",ERRCODE);
      TRACEENTRY(1,"%s -%s-","Query Parameter1 : FileSummary.HPLMN_CODE :",FileSummary.HPLMN_CODE);
      TRACEENTRY(1,"%s -%s-","Query Parameter2 : FileSummary.VPLMN_CODE :",FileSummary.VPLMN_CODE);
   }

   /* Check if the count is zero. This would apply for the first time for the operator */
   if(TotalFilesReceived == 0)
   {
      TRACEENTRY(1,"%s","Records to be inserted in PM_MISSING_TAP_FILES table, since no records available");
      GenerateFromSequence = 1; 
      GenerateTillSequence = FileSummary.FILE_SEQUENCE_NUMBER;
   }
   else
   {
      /* Check the FileSequence Received is greater than the Max FileSeqeuence in the system */
      if(FileSummary.FILE_SEQUENCE_NUMBER > MaxFileSequenceNumber)
      {
         TRACEENTRY(2,"%s","Records to be inserted in PM_MISSING_TAP_FILES table");
         GenerateFromSequence = MaxFileSequenceNumber + 1;
         GenerateTillSequence = FileSummary.FILE_SEQUENCE_NUMBER;

         /* File sequence number cannot be greater than 99999. Checking for this is not required */
         /* max 5 characters allocated for file sequence number */
      }
   }

 //printf("MissingFileCount:-%d-,FileExpectedTime:-%s-\n",MissingFileCount,FileExpectedTime) ;
   /* Prepare List of Files expected for the Operator */
   j=0;
   MissingFileCount = 0 ;
   if(GenerateFromSequence > 0 && GenerateTillSequence > 0)
   {
      for(i=GenerateFromSequence; i<=GenerateTillSequence; i++)
      {
         strcpy(stMissingFiles[j].FILE_TRANSFER_DIRECTION,"I");
         strcpy(stMissingFiles[j].HPLMN_CODE,FileSummary.HPLMN_CODE);
         strcpy(stMissingFiles[j].VPLMN_CODE,FileSummary.VPLMN_CODE);
         strcpy(stMissingFiles[j].FILE_TYPE_INDICATOR,FileSummary.FILE_TYPE_INDICATOR);
         stMissingFiles[j].FILE_SEQUENCE_NUMBER = i;
         strcpy(stMissingFiles[j].FILE_STATUS,"P");

         if(TotalFilesReceived > 0)
         {
              MissingFileCount = MissingFileCount + 1;
         }

        /* EXEC SQL SELECT TO_DATE(:FileExpectedTime,'YYYYMMDDHH24MISS')+:MissingFileCount*:gFrequencyInMinutes*60/86400
                    INTO :stMissingFiles[j].FILE_EXPECTED_TIME
                    FROM DUAL;
        */
         /* EXEC SQL SELECT TO_CHAR(TO_DATE(:FileExpectedTime,'YYYYMMDDHH24MISS') + :MissingFileCount*:gFrequencyInMinutes*60/86400, 'YYYYMMDDHH24MISS')
                    INTO :stMissingFiles[j].FILE_EXPECTED_TIME
                    FROM DUAL; */ 

{
         struct sqlexd sqlstm;
         sqlstm.sqlvsn = 12;
         sqlstm.arrsiz = 129;
         sqlstm.sqladtp = &sqladt;
         sqlstm.sqltdsp = &sqltds;
         sqlstm.stmt = "select TO_CHAR((TO_DATE(:b0,'YYYYMMDDHH24MISS')+(((:\
b1* :b2)* 60)/86400)),'YYYYMMDDHH24MISS') into :b3  from DUAL ";
         sqlstm.iters = (unsigned int  )1;
         sqlstm.offset = (unsigned int  )5642;
         sqlstm.selerr = (unsigned short)1;
         sqlstm.cud = sqlcud0;
         sqlstm.sqlest = (unsigned char  *)&sqlca;
         sqlstm.sqlety = (unsigned short)4352;
         sqlstm.occurs = (unsigned int  )0;
         sqlstm.sqhstv[0] = (         void  *)FileExpectedTime;
         sqlstm.sqhstl[0] = (unsigned int  )15;
         sqlstm.sqhsts[0] = (         int  )0;
         sqlstm.sqindv[0] = (         void  *)0;
         sqlstm.sqinds[0] = (         int  )0;
         sqlstm.sqharm[0] = (unsigned int  )0;
         sqlstm.sqadto[0] = (unsigned short )0;
         sqlstm.sqtdso[0] = (unsigned short )0;
         sqlstm.sqhstv[1] = (         void  *)&MissingFileCount;
         sqlstm.sqhstl[1] = (unsigned int  )sizeof(long);
         sqlstm.sqhsts[1] = (         int  )0;
         sqlstm.sqindv[1] = (         void  *)0;
         sqlstm.sqinds[1] = (         int  )0;
         sqlstm.sqharm[1] = (unsigned int  )0;
         sqlstm.sqadto[1] = (unsigned short )0;
         sqlstm.sqtdso[1] = (unsigned short )0;
         sqlstm.sqhstv[2] = (         void  *)&gFrequencyInMinutes;
         sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[2] = (         int  )0;
         sqlstm.sqindv[2] = (         void  *)0;
         sqlstm.sqinds[2] = (         int  )0;
         sqlstm.sqharm[2] = (unsigned int  )0;
         sqlstm.sqadto[2] = (unsigned short )0;
         sqlstm.sqtdso[2] = (unsigned short )0;
         sqlstm.sqhstv[3] = (         void  *)(stMissingFiles[j].FILE_EXPECTED_TIME);
         sqlstm.sqhstl[3] = (unsigned int  )15;
         sqlstm.sqhsts[3] = (         int  )0;
         sqlstm.sqindv[3] = (         void  *)0;
         sqlstm.sqinds[3] = (         int  )0;
         sqlstm.sqharm[3] = (unsigned int  )0;
         sqlstm.sqadto[3] = (unsigned short )0;
         sqlstm.sqtdso[3] = (unsigned short )0;
         sqlstm.sqphsv = sqlstm.sqhstv;
         sqlstm.sqphsl = sqlstm.sqhstl;
         sqlstm.sqphss = sqlstm.sqhsts;
         sqlstm.sqpind = sqlstm.sqindv;
         sqlstm.sqpins = sqlstm.sqinds;
         sqlstm.sqparm = sqlstm.sqharm;
         sqlstm.sqparc = sqlstm.sqharc;
         sqlstm.sqpadto = sqlstm.sqadto;
         sqlstm.sqptdso = sqlstm.sqtdso;
         sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



         if(ERRCODE!=0)
         {
              TRACEENTRY(1,"%s","ERROR: Error Calculating Expected Time from Dual;");
              TRACEENTRY(1,"%s -%d-","sqlca.sqlcode :",ERRCODE);
         }
/* printf("FILE_EXPECTED_TIME:-%s-,FileExpectedTime:-%s-\n",stMissingFiles[j].FILE_EXPECTED_TIME,FileExpectedTime) ;*/


         j=j+1;

         /* Insert data when count of missing files reaches the array size */
         if(j == MAX_MISSING_FILES)
         {
            GenerateRecordsCount = 0;
            GenerateRecordsCount = j;
            SetMissingFiles(GenerateRecordsCount);
            InitialiseMissingFiles();
            j=0;
         }
      }

      /* Insert data if still available */
      if(j > 0)
      {
         GenerateRecordsCount = 0;
         GenerateRecordsCount = j;
         SetMissingFiles(GenerateRecordsCount);
         InitialiseMissingFiles();
      }
   }

   /* Update the File Status for the TAPIN File */
   /* EXEC SQL UPDATE PM_MISSING_TAP_FILES
               SET FILE_STATUS = 'R',
                   FILE_AVAILABLE_TIME = SYSDATE
             WHERE FILE_TRANSFER_DIRECTION = 'I'
               AND HPLMN_CODE              = :FileSummary.HPLMN_CODE
               AND VPLMN_CODE              = :FileSummary.VPLMN_CODE
               AND FILE_TYPE_INDICATOR     = :FileSummary.FILE_TYPE_INDICATOR
               AND FILE_SEQUENCE_NUMBER    = :FileSummary.FILE_SEQUENCE_NUMBER; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 129;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "update PM_MISSING_TAP_FILES  set FILE_STATUS='R',FILE_AVAI\
LABLE_TIME=SYSDATE where ((((FILE_TRANSFER_DIRECTION='I' and HPLMN_CODE=:b0) a\
nd VPLMN_CODE=:b1) and FILE_TYPE_INDICATOR=:b2) and FILE_SEQUENCE_NUMBER=:b3)";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )5673;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)(FileSummary.HPLMN_CODE);
   sqlstm.sqhstl[0] = (unsigned int  )6;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)(FileSummary.VPLMN_CODE);
   sqlstm.sqhstl[1] = (unsigned int  )7;
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)(FileSummary.FILE_TYPE_INDICATOR);
   sqlstm.sqhstl[2] = (unsigned int  )2;
   sqlstm.sqhsts[2] = (         int  )0;
   sqlstm.sqindv[2] = (         void  *)0;
   sqlstm.sqinds[2] = (         int  )0;
   sqlstm.sqharm[2] = (unsigned int  )0;
   sqlstm.sqadto[2] = (unsigned short )0;
   sqlstm.sqtdso[2] = (unsigned short )0;
   sqlstm.sqhstv[3] = (         void  *)&(FileSummary.FILE_SEQUENCE_NUMBER);
   sqlstm.sqhstl[3] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[3] = (         int  )0;
   sqlstm.sqindv[3] = (         void  *)0;
   sqlstm.sqinds[3] = (         int  )0;
   sqlstm.sqharm[3] = (unsigned int  )0;
   sqlstm.sqadto[3] = (unsigned short )0;
   sqlstm.sqtdso[3] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   if(ERRCODE!=0)
   {
      TRACEENTRY(1,"%s","ERROR: Error Updating PM_MISSING_TAP_FILES table for the TAPIN File");
      TRACEENTRY(1,"%s -%d-","sqlca.sqlcode :",ERRCODE);
      TRACEENTRY(1,"%s -%d-","MaxFileSequenceNumber :",MaxFileSequenceNumber);
      TRACEENTRY(1,"%s -%d-","FileSequeceNumber     :",FileSummary.FILE_SEQUENCE_NUMBER);
      TRACEENTRY(1,"%s -%d-","GenerateFromSequence :",GenerateFromSequence);
      TRACEENTRY(1,"%s -%d-","GenerateTillSequence :",GenerateTillSequence);
      TRACEENTRY(1,"%s -%d-","GenerateRecordsCount :",GenerateRecordsCount);
   }
               
}


void UpdateTAPErrors()
{
   /* EXEC SQL UPDATE PM_TAP_ERRORS
               SET FILE_STATUS     = 'S',
                   REPROCESS_DATE  = SYSDATE
             WHERE TRIM(FILE_NAME) = :FileSummary.FILE_NAME; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 129;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "update PM_TAP_ERRORS  set FILE_STATUS='S',REPROCESS_DATE=S\
YSDATE where trim(FILE_NAME)=:b0";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )5704;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)(FileSummary.FILE_NAME);
   sqlstm.sqhstl[0] = (unsigned int  )18;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   if(ERRCODE==0)
   {
      TRACEENTRY(1,"%s","The previous reject status in PM_TAP_ERRORS has been updated to success");
   }
}


int ReconcileSummary(
                       char FILE_TRANSFER_DIRECTION[2],
                       char HPLMN_CODE[7],
                       char VPLMN_CODE[7],
                       char FILE_TYPE_INDICATOR[2],
                       long FILE_SEQUENCE_NUMBER,
                       char DATA_TYPE_INDICATOR[2],
                       char PartnerCode[4]
                    )
{
   typedef struct Summary
   {
      double SETTLEMENT_CALL_EVENTS;
      double SETTLEMENT_DURATION;
      double SETTLEMENT_OUTGOING_VOLUME;
      double SETTLEMENT_INCOMING_VOLUME;
      double SETTLEMENT_TAP_CURNCY_CHARGE;
      double SETTLEMENT_TAP_CURNCY_TAX;
      double SETTLEMENT_TAP_CURNCY_DISCOUNT;
      double SETTLEMENT_LOCAL_CHARGE;
      double SETTLEMENT_LOCAL_TAX;
      double SETTLEMENT_LOCAL_DISCOUNT;
      char   PARTNER_CODE[4];
   }Summary;

   Summary FileSumry, CallSummary;

   /* Initialise the FileSummary Structure members */
   FileSumry.SETTLEMENT_CALL_EVENTS         = 0;
   FileSumry.SETTLEMENT_DURATION            = 0;
   FileSumry.SETTLEMENT_OUTGOING_VOLUME     = 0;
   FileSumry.SETTLEMENT_INCOMING_VOLUME     = 0;
   FileSumry.SETTLEMENT_TAP_CURNCY_CHARGE   = 0;
   FileSumry.SETTLEMENT_TAP_CURNCY_TAX      = 0;
   FileSumry.SETTLEMENT_TAP_CURNCY_DISCOUNT = 0;
   FileSumry.SETTLEMENT_LOCAL_CHARGE        = 0;
   FileSumry.SETTLEMENT_LOCAL_TAX           = 0;
   FileSumry.SETTLEMENT_LOCAL_DISCOUNT      = 0;
   /* EXEC SQL VAR FileSumry.PARTNER_CODE      IS STRING(4); */ 


   /* Get the FileSummary from PM_TAP_FILE_SUMRY table */
   /* EXEC SQL SELECT NVL(SETTLEMENT_CALL_EVENTS,0),
                   NVL(SETTLEMENT_DURATION,0),
                   NVL(SETTLEMENT_OUTGOING_VOLUME,0),
                   NVL(SETTLEMENT_INCOMING_VOLUME,0),
                   NVL(SETTLEMENT_TAP_CURNCY_CHARGE,0),
                   NVL(SETTLEMENT_TAP_CURNCY_TAX,0),
                   NVL(SETTLEMENT_TAP_CURNCY_DISCOUNT,0),
                   NVL(SETTLEMENT_LOCAL_CHARGE,0),
                   NVL(SETTLEMENT_LOCAL_TAX,0),
                   NVL(SETTLEMENT_LOCAL_DISCOUNT,0),
                   PARTNER_CODE
              INTO :FileSumry.SETTLEMENT_CALL_EVENTS,
                   :FileSumry.SETTLEMENT_DURATION,
                   :FileSumry.SETTLEMENT_OUTGOING_VOLUME,
                   :FileSumry.SETTLEMENT_INCOMING_VOLUME,
                   :FileSumry.SETTLEMENT_TAP_CURNCY_CHARGE,
                   :FileSumry.SETTLEMENT_TAP_CURNCY_TAX,
                   :FileSumry.SETTLEMENT_TAP_CURNCY_DISCOUNT,
                   :FileSumry.SETTLEMENT_LOCAL_CHARGE,
                   :FileSumry.SETTLEMENT_LOCAL_TAX,
                   :FileSumry.SETTLEMENT_LOCAL_DISCOUNT,
                   :FileSumry.PARTNER_CODE
              FROM PM_TAP_FILE_SUMRY
             WHERE FILE_TRANSFER_DIRECTION='I'
               AND trim(HPLMN_CODE)     = trim(:HPLMN_CODE)
               AND trim(VPLMN_CODE)     = trim(:VPLMN_CODE)
               AND FILE_TYPE_INDICATOR  = trim(:FILE_TYPE_INDICATOR)
               AND FILE_SEQUENCE_NUMBER = :FILE_SEQUENCE_NUMBER; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 129;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select NVL(SETTLEMENT_CALL_EVENTS,0) ,NVL(SETTLEMENT_DURAT\
ION,0) ,NVL(SETTLEMENT_OUTGOING_VOLUME,0) ,NVL(SETTLEMENT_INCOMING_VOLUME,0) ,\
NVL(SETTLEMENT_TAP_CURNCY_CHARGE,0) ,NVL(SETTLEMENT_TAP_CURNCY_TAX,0) ,NVL(SET\
TLEMENT_TAP_CURNCY_DISCOUNT,0) ,NVL(SETTLEMENT_LOCAL_CHARGE,0) ,NVL(SETTLEMENT\
_LOCAL_TAX,0) ,NVL(SETTLEMENT_LOCAL_DISCOUNT,0) ,PARTNER_CODE into :b0,:b1,:b2\
,:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10  from PM_TAP_FILE_SUMRY where ((((FILE_TRANS\
FER_DIRECTION='I' and trim(HPLMN_CODE)=trim(:b11)) and trim(VPLMN_CODE)=trim(:\
b12)) and FILE_TYPE_INDICATOR=trim(:b13)) and FILE_SEQUENCE_NUMBER=:b14)";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )5723;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&(FileSumry.SETTLEMENT_CALL_EVENTS);
   sqlstm.sqhstl[0] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)&(FileSumry.SETTLEMENT_DURATION);
   sqlstm.sqhstl[1] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)&(FileSumry.SETTLEMENT_OUTGOING_VOLUME);
   sqlstm.sqhstl[2] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[2] = (         int  )0;
   sqlstm.sqindv[2] = (         void  *)0;
   sqlstm.sqinds[2] = (         int  )0;
   sqlstm.sqharm[2] = (unsigned int  )0;
   sqlstm.sqadto[2] = (unsigned short )0;
   sqlstm.sqtdso[2] = (unsigned short )0;
   sqlstm.sqhstv[3] = (         void  *)&(FileSumry.SETTLEMENT_INCOMING_VOLUME);
   sqlstm.sqhstl[3] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[3] = (         int  )0;
   sqlstm.sqindv[3] = (         void  *)0;
   sqlstm.sqinds[3] = (         int  )0;
   sqlstm.sqharm[3] = (unsigned int  )0;
   sqlstm.sqadto[3] = (unsigned short )0;
   sqlstm.sqtdso[3] = (unsigned short )0;
   sqlstm.sqhstv[4] = (         void  *)&(FileSumry.SETTLEMENT_TAP_CURNCY_CHARGE);
   sqlstm.sqhstl[4] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[4] = (         int  )0;
   sqlstm.sqindv[4] = (         void  *)0;
   sqlstm.sqinds[4] = (         int  )0;
   sqlstm.sqharm[4] = (unsigned int  )0;
   sqlstm.sqadto[4] = (unsigned short )0;
   sqlstm.sqtdso[4] = (unsigned short )0;
   sqlstm.sqhstv[5] = (         void  *)&(FileSumry.SETTLEMENT_TAP_CURNCY_TAX);
   sqlstm.sqhstl[5] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[5] = (         int  )0;
   sqlstm.sqindv[5] = (         void  *)0;
   sqlstm.sqinds[5] = (         int  )0;
   sqlstm.sqharm[5] = (unsigned int  )0;
   sqlstm.sqadto[5] = (unsigned short )0;
   sqlstm.sqtdso[5] = (unsigned short )0;
   sqlstm.sqhstv[6] = (         void  *)&(FileSumry.SETTLEMENT_TAP_CURNCY_DISCOUNT);
   sqlstm.sqhstl[6] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[6] = (         int  )0;
   sqlstm.sqindv[6] = (         void  *)0;
   sqlstm.sqinds[6] = (         int  )0;
   sqlstm.sqharm[6] = (unsigned int  )0;
   sqlstm.sqadto[6] = (unsigned short )0;
   sqlstm.sqtdso[6] = (unsigned short )0;
   sqlstm.sqhstv[7] = (         void  *)&(FileSumry.SETTLEMENT_LOCAL_CHARGE);
   sqlstm.sqhstl[7] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[7] = (         int  )0;
   sqlstm.sqindv[7] = (         void  *)0;
   sqlstm.sqinds[7] = (         int  )0;
   sqlstm.sqharm[7] = (unsigned int  )0;
   sqlstm.sqadto[7] = (unsigned short )0;
   sqlstm.sqtdso[7] = (unsigned short )0;
   sqlstm.sqhstv[8] = (         void  *)&(FileSumry.SETTLEMENT_LOCAL_TAX);
   sqlstm.sqhstl[8] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[8] = (         int  )0;
   sqlstm.sqindv[8] = (         void  *)0;
   sqlstm.sqinds[8] = (         int  )0;
   sqlstm.sqharm[8] = (unsigned int  )0;
   sqlstm.sqadto[8] = (unsigned short )0;
   sqlstm.sqtdso[8] = (unsigned short )0;
   sqlstm.sqhstv[9] = (         void  *)&(FileSumry.SETTLEMENT_LOCAL_DISCOUNT);
   sqlstm.sqhstl[9] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[9] = (         int  )0;
   sqlstm.sqindv[9] = (         void  *)0;
   sqlstm.sqinds[9] = (         int  )0;
   sqlstm.sqharm[9] = (unsigned int  )0;
   sqlstm.sqadto[9] = (unsigned short )0;
   sqlstm.sqtdso[9] = (unsigned short )0;
   sqlstm.sqhstv[10] = (         void  *)(FileSumry.PARTNER_CODE);
   sqlstm.sqhstl[10] = (unsigned int  )4;
   sqlstm.sqhsts[10] = (         int  )0;
   sqlstm.sqindv[10] = (         void  *)0;
   sqlstm.sqinds[10] = (         int  )0;
   sqlstm.sqharm[10] = (unsigned int  )0;
   sqlstm.sqadto[10] = (unsigned short )0;
   sqlstm.sqtdso[10] = (unsigned short )0;
   sqlstm.sqhstv[11] = (         void  *)HPLMN_CODE;
   sqlstm.sqhstl[11] = (unsigned int  )7;
   sqlstm.sqhsts[11] = (         int  )0;
   sqlstm.sqindv[11] = (         void  *)0;
   sqlstm.sqinds[11] = (         int  )0;
   sqlstm.sqharm[11] = (unsigned int  )0;
   sqlstm.sqadto[11] = (unsigned short )0;
   sqlstm.sqtdso[11] = (unsigned short )0;
   sqlstm.sqhstv[12] = (         void  *)VPLMN_CODE;
   sqlstm.sqhstl[12] = (unsigned int  )7;
   sqlstm.sqhsts[12] = (         int  )0;
   sqlstm.sqindv[12] = (         void  *)0;
   sqlstm.sqinds[12] = (         int  )0;
   sqlstm.sqharm[12] = (unsigned int  )0;
   sqlstm.sqadto[12] = (unsigned short )0;
   sqlstm.sqtdso[12] = (unsigned short )0;
   sqlstm.sqhstv[13] = (         void  *)FILE_TYPE_INDICATOR;
   sqlstm.sqhstl[13] = (unsigned int  )2;
   sqlstm.sqhsts[13] = (         int  )0;
   sqlstm.sqindv[13] = (         void  *)0;
   sqlstm.sqinds[13] = (         int  )0;
   sqlstm.sqharm[13] = (unsigned int  )0;
   sqlstm.sqadto[13] = (unsigned short )0;
   sqlstm.sqtdso[13] = (unsigned short )0;
   sqlstm.sqhstv[14] = (         void  *)&FILE_SEQUENCE_NUMBER;
   sqlstm.sqhstl[14] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[14] = (         int  )0;
   sqlstm.sqindv[14] = (         void  *)0;
   sqlstm.sqinds[14] = (         int  )0;
   sqlstm.sqharm[14] = (unsigned int  )0;
   sqlstm.sqadto[14] = (unsigned short )0;
   sqlstm.sqtdso[14] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


               /* AND trim(PARTNER_CODE)   = trim(:PartnerCode); */

   if(ERRCODE!=0)
   {
      TRACEENTRY(1,"%s","Error Querying PM_TAP_FILE_SUMRY for Reconcilation");
      TRACEENTRY(1,"%s-%d-","sqlca.sqlcode       :",sqlca.sqlcode);
      TRACEENTRY(1,"%s-%s-","HPLMN_CODE          :",HPLMN_CODE);
      TRACEENTRY(1,"%s-%s-","VPLMN_CODE          :",VPLMN_CODE);
      TRACEENTRY(1,"%s-%s-","FILE_TYPE_INDICATOR :",FILE_TYPE_INDICATOR);
      TRACEENTRY(1,"%s-%d-","FILE_SEQUENCE_NUMBER:",FILE_SEQUENCE_NUMBER);
      TRACEENTRY(1,"%s-%s-","PartnerCode         :",PartnerCode);
      TRACEENTRY(1,"%s","Cannot Proceed for this Operator");
      return -1;
   }


   /* Initialise the CallSummary Structure members */
   CallSummary.SETTLEMENT_CALL_EVENTS         = 0;
   CallSummary.SETTLEMENT_DURATION            = 0;
   CallSummary.SETTLEMENT_OUTGOING_VOLUME     = 0;
   CallSummary.SETTLEMENT_INCOMING_VOLUME     = 0;
   CallSummary.SETTLEMENT_TAP_CURNCY_CHARGE   = 0;
   CallSummary.SETTLEMENT_TAP_CURNCY_TAX      = 0;
   CallSummary.SETTLEMENT_TAP_CURNCY_DISCOUNT = 0;
   CallSummary.SETTLEMENT_LOCAL_CHARGE        = 0;
   CallSummary.SETTLEMENT_LOCAL_TAX           = 0;
   CallSummary.SETTLEMENT_LOCAL_DISCOUNT      = 0;
   /* EXEC SQL VAR CallSummary.PARTNER_CODE      IS STRING(4); */ 


   /* Get the CallSummary from PM_TAP_CDRS table */
   /* Modified by Chetan on 21-NOV-2008 to add Camel Invocation Fee in summary*/

   /* EXEC SQL SELECT COUNT(1),
                   NVL(sum(CALL_DURATION),0),
                   NVL(sum(DATA_VOLUME_OUTGOING),0),
                   NVL(sum(DATA_VOLUME_INCOMING),0), 
                   NVL(sum(CHARGE)+ sum(CAMEL_INVOCATION_FEE),0),
                   NVL(sum(TAX_VALUE),0),
                   NVL(sum(DISCOUNT),0),
                   NVL(sum(HOME_CURNCY_CHARGE) + sum(HOME_CURNCY_CAMEL_FEE),0),
                   NVL(sum(HOME_CURNCY_TAX),0),
                   NVL(sum(HOME_CURNCY_DISCOUNT),0)
                   /o PARTNER_CODE o/
              INTO :CallSummary.SETTLEMENT_CALL_EVENTS,
                   :CallSummary.SETTLEMENT_DURATION,
                   :CallSummary.SETTLEMENT_OUTGOING_VOLUME,
                   :CallSummary.SETTLEMENT_INCOMING_VOLUME,
                   :CallSummary.SETTLEMENT_TAP_CURNCY_CHARGE,
                   :CallSummary.SETTLEMENT_TAP_CURNCY_TAX,
                   :CallSummary.SETTLEMENT_TAP_CURNCY_DISCOUNT,
                   :CallSummary.SETTLEMENT_LOCAL_CHARGE,
                   :CallSummary.SETTLEMENT_LOCAL_TAX,
                   :CallSummary.SETTLEMENT_LOCAL_DISCOUNT
                   /o :CallSummary.PARTNER_CODE o/
              FROM PM_TAP_CDRS 
             WHERE FILE_TRANSFER_DIRECTION='I'
               AND trim(HPLMN_CODE)     = trim(:HPLMN_CODE)
               AND trim(VPLMN_CODE)     = trim(:VPLMN_CODE)
               AND FILE_TYPE_INDICATOR  = trim(:FILE_TYPE_INDICATOR)
               AND FILE_SEQUENCE_NUMBER = :FILE_SEQUENCE_NUMBER
               /o AND trim(PARTNER_CODE)= trim(:PartnerCode) o/
          GROUP BY FILE_TRANSFER_DIRECTION,HPLMN_CODE,VPLMN_CODE,FILE_TYPE_INDICATOR ,FILE_SEQUENCE_NUMBER; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 129;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select count(1) ,NVL(sum(CALL_DURATION),0) ,NVL(sum(DATA_V\
OLUME_OUTGOING),0) ,NVL(sum(DATA_VOLUME_INCOMING),0) ,NVL((sum(CHARGE)+sum(CAM\
EL_INVOCATION_FEE)),0) ,NVL(sum(TAX_VALUE),0) ,NVL(sum(DISCOUNT),0) ,NVL((sum(\
HOME_CURNCY_CHARGE)+sum(HOME_CURNCY_CAMEL_FEE)),0) ,NVL(sum(HOME_CURNCY_TAX),0\
) ,NVL(sum(HOME_CURNCY_DISCOUNT),0) into :b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:\
b9  from PM_TAP_CDRS where ((((FILE_TRANSFER_DIRECTION='I' and trim(HPLMN_CODE\
)=trim(:b10)) and trim(VPLMN_CODE)=trim(:b11)) and FILE_TYPE_INDICATOR=trim(:b\
12)) and FILE_SEQUENCE_NUMBER=:b13) group by FILE_TRANSFER_DIRECTION,HPLMN_COD\
E,VPLMN_CODE,FILE_TYPE_INDICATOR,FILE_SEQUENCE_NUMBER";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )5798;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&(CallSummary.SETTLEMENT_CALL_EVENTS);
   sqlstm.sqhstl[0] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)&(CallSummary.SETTLEMENT_DURATION);
   sqlstm.sqhstl[1] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)&(CallSummary.SETTLEMENT_OUTGOING_VOLUME);
   sqlstm.sqhstl[2] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[2] = (         int  )0;
   sqlstm.sqindv[2] = (         void  *)0;
   sqlstm.sqinds[2] = (         int  )0;
   sqlstm.sqharm[2] = (unsigned int  )0;
   sqlstm.sqadto[2] = (unsigned short )0;
   sqlstm.sqtdso[2] = (unsigned short )0;
   sqlstm.sqhstv[3] = (         void  *)&(CallSummary.SETTLEMENT_INCOMING_VOLUME);
   sqlstm.sqhstl[3] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[3] = (         int  )0;
   sqlstm.sqindv[3] = (         void  *)0;
   sqlstm.sqinds[3] = (         int  )0;
   sqlstm.sqharm[3] = (unsigned int  )0;
   sqlstm.sqadto[3] = (unsigned short )0;
   sqlstm.sqtdso[3] = (unsigned short )0;
   sqlstm.sqhstv[4] = (         void  *)&(CallSummary.SETTLEMENT_TAP_CURNCY_CHARGE);
   sqlstm.sqhstl[4] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[4] = (         int  )0;
   sqlstm.sqindv[4] = (         void  *)0;
   sqlstm.sqinds[4] = (         int  )0;
   sqlstm.sqharm[4] = (unsigned int  )0;
   sqlstm.sqadto[4] = (unsigned short )0;
   sqlstm.sqtdso[4] = (unsigned short )0;
   sqlstm.sqhstv[5] = (         void  *)&(CallSummary.SETTLEMENT_TAP_CURNCY_TAX);
   sqlstm.sqhstl[5] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[5] = (         int  )0;
   sqlstm.sqindv[5] = (         void  *)0;
   sqlstm.sqinds[5] = (         int  )0;
   sqlstm.sqharm[5] = (unsigned int  )0;
   sqlstm.sqadto[5] = (unsigned short )0;
   sqlstm.sqtdso[5] = (unsigned short )0;
   sqlstm.sqhstv[6] = (         void  *)&(CallSummary.SETTLEMENT_TAP_CURNCY_DISCOUNT);
   sqlstm.sqhstl[6] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[6] = (         int  )0;
   sqlstm.sqindv[6] = (         void  *)0;
   sqlstm.sqinds[6] = (         int  )0;
   sqlstm.sqharm[6] = (unsigned int  )0;
   sqlstm.sqadto[6] = (unsigned short )0;
   sqlstm.sqtdso[6] = (unsigned short )0;
   sqlstm.sqhstv[7] = (         void  *)&(CallSummary.SETTLEMENT_LOCAL_CHARGE);
   sqlstm.sqhstl[7] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[7] = (         int  )0;
   sqlstm.sqindv[7] = (         void  *)0;
   sqlstm.sqinds[7] = (         int  )0;
   sqlstm.sqharm[7] = (unsigned int  )0;
   sqlstm.sqadto[7] = (unsigned short )0;
   sqlstm.sqtdso[7] = (unsigned short )0;
   sqlstm.sqhstv[8] = (         void  *)&(CallSummary.SETTLEMENT_LOCAL_TAX);
   sqlstm.sqhstl[8] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[8] = (         int  )0;
   sqlstm.sqindv[8] = (         void  *)0;
   sqlstm.sqinds[8] = (         int  )0;
   sqlstm.sqharm[8] = (unsigned int  )0;
   sqlstm.sqadto[8] = (unsigned short )0;
   sqlstm.sqtdso[8] = (unsigned short )0;
   sqlstm.sqhstv[9] = (         void  *)&(CallSummary.SETTLEMENT_LOCAL_DISCOUNT);
   sqlstm.sqhstl[9] = (unsigned int  )sizeof(double);
   sqlstm.sqhsts[9] = (         int  )0;
   sqlstm.sqindv[9] = (         void  *)0;
   sqlstm.sqinds[9] = (         int  )0;
   sqlstm.sqharm[9] = (unsigned int  )0;
   sqlstm.sqadto[9] = (unsigned short )0;
   sqlstm.sqtdso[9] = (unsigned short )0;
   sqlstm.sqhstv[10] = (         void  *)HPLMN_CODE;
   sqlstm.sqhstl[10] = (unsigned int  )7;
   sqlstm.sqhsts[10] = (         int  )0;
   sqlstm.sqindv[10] = (         void  *)0;
   sqlstm.sqinds[10] = (         int  )0;
   sqlstm.sqharm[10] = (unsigned int  )0;
   sqlstm.sqadto[10] = (unsigned short )0;
   sqlstm.sqtdso[10] = (unsigned short )0;
   sqlstm.sqhstv[11] = (         void  *)VPLMN_CODE;
   sqlstm.sqhstl[11] = (unsigned int  )7;
   sqlstm.sqhsts[11] = (         int  )0;
   sqlstm.sqindv[11] = (         void  *)0;
   sqlstm.sqinds[11] = (         int  )0;
   sqlstm.sqharm[11] = (unsigned int  )0;
   sqlstm.sqadto[11] = (unsigned short )0;
   sqlstm.sqtdso[11] = (unsigned short )0;
   sqlstm.sqhstv[12] = (         void  *)FILE_TYPE_INDICATOR;
   sqlstm.sqhstl[12] = (unsigned int  )2;
   sqlstm.sqhsts[12] = (         int  )0;
   sqlstm.sqindv[12] = (         void  *)0;
   sqlstm.sqinds[12] = (         int  )0;
   sqlstm.sqharm[12] = (unsigned int  )0;
   sqlstm.sqadto[12] = (unsigned short )0;
   sqlstm.sqtdso[12] = (unsigned short )0;
   sqlstm.sqhstv[13] = (         void  *)&FILE_SEQUENCE_NUMBER;
   sqlstm.sqhstl[13] = (unsigned int  )sizeof(long);
   sqlstm.sqhsts[13] = (         int  )0;
   sqlstm.sqindv[13] = (         void  *)0;
   sqlstm.sqinds[13] = (         int  )0;
   sqlstm.sqharm[13] = (unsigned int  )0;
   sqlstm.sqadto[13] = (unsigned short )0;
   sqlstm.sqtdso[13] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   if(ERRCODE!=0)
   {
      stErrors.ERROR_CODE = sqlca.sqlcode;
      strcpy(stErrors.ERROR_DESC,"Error Querying PM_TAP_CDRS for Reconcilation");

      TRACEENTRY(1,"%s","Error Querying PM_TAP_CDRS for Reconcilation");
      TRACEENTRY(1,"%s :-%d-","sqlca.sqlcode",sqlca.sqlcode);
      TRACEENTRY(1,"%s","Cannot Proceed for this Operator");
      return -1;
   }


   /* Compare FileSummary and CallSummary */
   if(
      (FileSumry.SETTLEMENT_CALL_EVENTS         == CallSummary.SETTLEMENT_CALL_EVENTS) &&
      (FileSumry.SETTLEMENT_DURATION            == CallSummary.SETTLEMENT_DURATION) &&
      (FileSumry.SETTLEMENT_OUTGOING_VOLUME     == CallSummary.SETTLEMENT_OUTGOING_VOLUME) &&
      (FileSumry.SETTLEMENT_INCOMING_VOLUME     == CallSummary.SETTLEMENT_INCOMING_VOLUME) &&
      (FileSumry.SETTLEMENT_TAP_CURNCY_CHARGE   == CallSummary.SETTLEMENT_TAP_CURNCY_CHARGE) &&
      (FileSumry.SETTLEMENT_TAP_CURNCY_TAX      == CallSummary.SETTLEMENT_TAP_CURNCY_TAX) &&
     /*(FileSumry.SETTLEMENT_TAP_CURNCY_DISCOUNT == CallSummary.SETTLEMENT_TAP_CURNCY_DISCOUNT) &&*/
      (FileSumry.SETTLEMENT_LOCAL_CHARGE        == CallSummary.SETTLEMENT_LOCAL_CHARGE) &&
      (FileSumry.SETTLEMENT_LOCAL_TAX           == CallSummary.SETTLEMENT_LOCAL_TAX) 
     /*(FileSumry.SETTLEMENT_LOCAL_DISCOUNT      == CallSummary.SETTLEMENT_LOCAL_DISCOUNT) */
     )
   {
      return 1;
   }
   else
   {
      stErrors.ERROR_CODE = sqlca.sqlcode;
      strcpy(stErrors.ERROR_DESC,"Error FileSummary does not match with CallSummary.");

      TRACEENTRY(1,"%s","Reconcilation Status : ERROR - FileSummary does not match with CallSummary.");
      TRACEENTRY(1,"%s","Reconcilation Details Shown below");
      TRACEENTRY(1,"Calls        File -%20f- CDRS -%20f",FileSumry.SETTLEMENT_CALL_EVENTS,CallSummary.SETTLEMENT_CALL_EVENTS);
      TRACEENTRY(1,"Duration     File -%20f- CDRS -%20f",FileSumry.SETTLEMENT_DURATION,CallSummary.SETTLEMENT_DURATION);
      TRACEENTRY(1,"Out Volume   File -%20f- CDRS -%20f",FileSumry.SETTLEMENT_OUTGOING_VOLUME,CallSummary.SETTLEMENT_OUTGOING_VOLUME);
      TRACEENTRY(1,"Inc Volume   File -%20f- CDRS -%20f",FileSumry.SETTLEMENT_INCOMING_VOLUME,CallSummary.SETTLEMENT_INCOMING_VOLUME);
      TRACEENTRY(1,"HomeCharge   File -%20f- CDRS -%20f",FileSumry.SETTLEMENT_LOCAL_CHARGE,CallSummary.SETTLEMENT_LOCAL_CHARGE);
      TRACEENTRY(1,"HomeDiscount File -%20f- CDRS -%20f",FileSumry.SETTLEMENT_LOCAL_DISCOUNT,CallSummary.SETTLEMENT_LOCAL_DISCOUNT);
      TRACEENTRY(1,"HomeTax      File -%20f- CDRS -%20f",FileSumry.SETTLEMENT_LOCAL_TAX,CallSummary.SETTLEMENT_LOCAL_TAX);

      TRACEENTRY(1,"TAPCharge    File -%20f- CDRS -%20f",FileSumry.SETTLEMENT_TAP_CURNCY_CHARGE,CallSummary.SETTLEMENT_TAP_CURNCY_CHARGE);
      TRACEENTRY(1,"TAPDiscount  File -%20f- CDRS -%20f",FileSumry.SETTLEMENT_TAP_CURNCY_DISCOUNT,CallSummary.SETTLEMENT_TAP_CURNCY_DISCOUNT);
      TRACEENTRY(1,"TAPTax       File -%20f- CDRS -%20f",FileSumry.SETTLEMENT_TAP_CURNCY_TAX,CallSummary.SETTLEMENT_TAP_CURNCY_TAX);

      return -1;
   }

}

int ValidateBatchControlInfo()
{
   int i=0;
   int SetError=0;
   int ValidHPLMNCode=0;
   int ValidVPLMNCode=0;
   INIT_STR(gCheckCallAgeFlag) ;
   gCallAge = 0 ;
   INIT_STR(gCheckFileAgeFlag) ;
   gFileAge = 0 ;
   INIT_STR(gIOTCheckFlag) ;
   int ValidVersion =0;

   /* Check if the HPLMN Code in the file matches with Home Operators PLMN Code */
   if(strcmp(BCI.Recipient,stRoamingPref.HPLMN_CODE)==0)
   {
      ValidHPLMNCode=1;
   }

   /* Return Error if Home Operator PLMN Code is not matching */
   SetError=0;
   if(ValidHPLMNCode==0)
   {
      stErrors.ERROR_CODE = 0;
      strcpy(stErrors.ERROR_DESC,"Receiver in file not matching with the HPLMN_CODE defined in PM_ROAMING_PREFERENCES");
      TRACEENTRY(1,"%s","Receiver in the file is not matching with the HPLMN_CODE defined in PM_ROAMING_PREFERENCES");
      SetError = -1;
      return SetError;
   }

   /* Check if the VPLMN Code in the file is available in the system */
   i=0;
   for(i=0;i<gPartnerCount;i++)
   {
      ptPartners2 = (ptPartners1 + i);
      if(strcmp(BCI.Sender,ptPartners2->PARTNER_SHORT_CODE)==0)
      {
         strcpy(FileSummary.PARTNER_CODE,ptPartners2->PARTNER_CODE);
         ValidVPLMNCode=1;
         break;
      }
   }
   

   /* Return error if Partner not found */
   if(ValidVPLMNCode==0)
   {
      stErrors.ERROR_CODE = 0;
      strcpy(stErrors.ERROR_DESC,"Check for the Sender specified in file in PM_PARTNERS/PM_ROAM_PARTNER_FILE_INFO tables");
      TRACEENTRY(1,"%s-%s-","Sender specified in the file is not defined in PM_PARTNERS",BCI.Sender);
      TRACEENTRY(1,"%s","OR Verify if GENERATE_FILES_FLG in PM_ROAM_PARTNER_FILE_INFO table is 'Y'");
      SetError = -1;
      return SetError; 
   }


     /* validation for Tap specification and version - Lavanya */
   if((BCI.SpecificationVersionNumber == ptRoamingPref2->TAP_SPECIFICATION_VERSION) && (BCI.ReleaseVersionNumber == ptRoamingPref2->TAP_RELEASE_VERSION))
   {
        ValidVersion = 1;
   }
    if(ValidVersion==0)
   {
      stErrors.ERROR_CODE = 0;
      strcpy(stErrors.ERROR_DESC,"The TAP specification and versions are not matching with the defined values in  PM_ROAMING_PREFERENCES");
      TRACEENTRY(1,"TAP Specification Version -%d-",gTapSpecificationVersion);
      TRACEENTRY(1,"TAP Release Version -%d-",gTapReleaseVersion);
      TRACEENTRY(1,"%s","The TAP specification and versions are not matching with the values defined in  PM_ROAMING_PREFERENCES");
      SetError = -1;
      return SetError;
   }

   /* Initialise the Partner Additional Info Structure Members */
   stPartnerInfo.TAPIN_SURCHARGE_FLAG = 0;
   stPartnerInfo.TAPIN_SURCHARGE_RATE = 0;
   stPartnerInfo.TAPIN_TAX_FLAG       = 0;
   stPartnerInfo.TAPIN_DISCOUNT_FLAG  = 0;
   stPartnerInfo.TAPIN_DISCOUNT_RATE  = 0;
   stPartnerInfo.TAPIN_TAX_RATE       = 0;
   gFrequencyInMinutes = 0 ;
   i=0;
   gTapinTaxFlag=0;
   /* Get the Surcharge, Tax and Discount information for the operator */
   TRACEENTRY(1,"Sender -%s-",BCI.Sender);
   for(i=0;i<gPartnerCount;i++)
   {
      ptPartners2 = (ptPartners1 + i);

      if(strcmp(BCI.Sender,ptPartners2->PARTNER_SHORT_CODE)==0)
      {
         strcpy(gCheckCallAgeFlag,ptPartners2->CHECK_CALL_AGE_FLG) ;
         gCallAge = ptPartners2->CALL_AGE ;
         strcpy(gCheckFileAgeFlag,ptPartners2->CHECK_FILE_AGE_FLG) ;
         gFileAge = ptPartners2->FILE_AGE ;
         strcpy(gIOTCheckFlag,ptPartners2->IOT_CHECK) ;
 
         gFrequencyInMinutes          = ptPartners2->FREQUENCY_IN_MINUTE;

         if(strcmp(ptPartners2->TAPIN_SURCHARGE_FLAG,"Y")==0)
         {
            stPartnerInfo.TAPIN_SURCHARGE_FLAG = 1;
         }
         stPartnerInfo.TAPIN_SURCHARGE_RATE = ptPartners2->TAPIN_SURCHARGE_RATE;

         if(strcmp(ptPartners2->TAPIN_TAX_FLAG,"Y")==0)
         {
            stPartnerInfo.TAPIN_TAX_FLAG = 1;
	    gTapinTaxFlag=1;
         }

         if(strcmp(ptPartners2->TAPIN_DISCOUNT_FLAG,"Y")==0)
         {
            stPartnerInfo.TAPIN_DISCOUNT_FLAG = 1;
         }

         stPartnerInfo.TAPIN_DISCOUNT_RATE  = ptPartners2->TAPIN_DISCOUNT_RATE;
         stPartnerInfo.TAPIN_TAX_RATE       = ptPartners2->TAPIN_TAX_RATE;
         TRACEENTRY(1,"FileAgeFlag   : -%s-",gCheckFileAgeFlag);
         TRACEENTRY(1,"FileAge       : -%d-",gFileAge);
         TRACEENTRY(1,"CallAgeFlag   : -%s-",gCheckCallAgeFlag);
         TRACEENTRY(1,"CallAge       : -%d-",gCallAge);
         TRACEENTRY(1,"FrequencyInMin: -%d-",gFrequencyInMinutes);
         TRACEENTRY(1,"IOT Check     : -%s-",gIOTCheckFlag);
         TRACEENTRY(1,"SurchargeRate : -%f-",stPartnerInfo.TAPIN_SURCHARGE_RATE);
         break;
      }
   }
   
   

   /****************************************************************/
   /* Check the Start Date of the File Creation */

   INIT_STR(gFileStartDate) ;

   gFileAge = gFileAge + 1;
   /* EXEC SQL SELECT TO_CHAR(trunc(TO_DATE(:gFileReceivedDate,'YYYYMMDDhh24miss')) - :gFileAge,'YYYYMMDDHH24MISS') INTO :gFileStartDate FROM DUAL ; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 129;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select TO_CHAR((trunc(TO_DATE(:b0,'YYYYMMDDhh24miss'))-:b1\
),'YYYYMMDDHH24MISS') into :b2  from DUAL ";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )5869;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)gFileReceivedDate;
   sqlstm.sqhstl[0] = (unsigned int  )15;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)&gFileAge;
   sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)gFileStartDate;
   sqlstm.sqhstl[2] = (unsigned int  )15;
   sqlstm.sqhsts[2] = (         int  )0;
   sqlstm.sqindv[2] = (         void  *)0;
   sqlstm.sqinds[2] = (         int  )0;
   sqlstm.sqharm[2] = (unsigned int  )0;
   sqlstm.sqadto[2] = (unsigned short )0;
   sqlstm.sqtdso[2] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   if(ERRCODE != 0)
   {
       TRACEENTRY(1,"%s-%d-","Error in Getting File Start  Date. ErrorCode :: ",ERRCODE) ;
       return -1;
   }


   /* Added To Check Call Age in the File */
   INIT_STR(g_CdrStartDate) ;
   
   if(strcmp(gCheckCallAgeFlag,"Y") == 0)
   {
       gCallAge = gCallAge + 1;
       /* EXEC SQL SELECT TO_CHAR(trunc(CURRENT_TIMESTAMP) - :gCallAge,'YYYYMMDDHH24MISS') INTO :g_CdrStartDate FROM DUAL ; */ 

{
       struct sqlexd sqlstm;
       sqlstm.sqlvsn = 12;
       sqlstm.arrsiz = 129;
       sqlstm.sqladtp = &sqladt;
       sqlstm.sqltdsp = &sqltds;
       sqlstm.stmt = "select TO_CHAR((trunc(CURRENT_TIMESTAMP)-:b0),'YYYYMMD\
DHH24MISS') into :b1  from DUAL ";
       sqlstm.iters = (unsigned int  )1;
       sqlstm.offset = (unsigned int  )5896;
       sqlstm.selerr = (unsigned short)1;
       sqlstm.cud = sqlcud0;
       sqlstm.sqlest = (unsigned char  *)&sqlca;
       sqlstm.sqlety = (unsigned short)4352;
       sqlstm.occurs = (unsigned int  )0;
       sqlstm.sqhstv[0] = (         void  *)&gCallAge;
       sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
       sqlstm.sqhsts[0] = (         int  )0;
       sqlstm.sqindv[0] = (         void  *)0;
       sqlstm.sqinds[0] = (         int  )0;
       sqlstm.sqharm[0] = (unsigned int  )0;
       sqlstm.sqadto[0] = (unsigned short )0;
       sqlstm.sqtdso[0] = (unsigned short )0;
       sqlstm.sqhstv[1] = (         void  *)g_CdrStartDate;
       sqlstm.sqhstl[1] = (unsigned int  )15;
       sqlstm.sqhsts[1] = (         int  )0;
       sqlstm.sqindv[1] = (         void  *)0;
       sqlstm.sqinds[1] = (         int  )0;
       sqlstm.sqharm[1] = (unsigned int  )0;
       sqlstm.sqadto[1] = (unsigned short )0;
       sqlstm.sqtdso[1] = (unsigned short )0;
       sqlstm.sqphsv = sqlstm.sqhstv;
       sqlstm.sqphsl = sqlstm.sqhstl;
       sqlstm.sqphss = sqlstm.sqhsts;
       sqlstm.sqpind = sqlstm.sqindv;
       sqlstm.sqpins = sqlstm.sqinds;
       sqlstm.sqparm = sqlstm.sqharm;
       sqlstm.sqparc = sqlstm.sqharc;
       sqlstm.sqpadto = sqlstm.sqadto;
       sqlstm.sqptdso = sqlstm.sqtdso;
       sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



       if(ERRCODE != 0)
       {
          TRACEENTRY(1,"%s-%d-","Error in Getting Cdr Start Date. ErrorCode :: ",ERRCODE) ;
          return -1;
       }
   }

   return SetError;
}


int CheckDuplicate(char FileName[31])
{
   int FileCount=0;

   /* EXEC SQL SELECT COUNT(1)
              INTO :FileCount
              FROM PM_TAP_FILE_SUMRY
             WHERE FILE_TRANSFER_DIRECTION = 'I'
               AND trim(FILE_NAME) = trim(:FileName); */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 129;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select count(1) into :b0  from PM_TAP_FILE_SUMRY where (FI\
LE_TRANSFER_DIRECTION='I' and trim(FILE_NAME)=trim(:b1))";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )5919;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&FileCount;
   sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)FileName;
   sqlstm.sqhstl[1] = (unsigned int  )31;
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   if(ERRCODE!=0)
   {
      TRACEENTRY(1,"%s","Error checking duplicate record in PM_TAP_FILE_SUMRY table");
      TRACEENTRY(1,"%s :-%d-","sqlca.sqlcode",sqlca.sqlcode);
   }

   if(FileCount > 0)
   {
      stErrors.ERROR_CODE = sqlca.sqlcode;
      strcpy(stErrors.ERROR_DESC,"Duplicate TAP File found. Cannot Process the file");
      TRACEENTRY(1,"%s","Duplicate TAP File found. Cannot Process the file");
   }

   return FileCount;
}


int CheckRAPDuplicate(char FileName[31])
{
   int FileCount=0;

   /* EXEC SQL SELECT COUNT(1)
              INTO :FileCount
              FROM PM_RAP_FILE_SUMRY
             WHERE FILE_TRANSFER_DIRECTION = 'O'
               AND trim(RAP_FILE_NAME) = trim(:FileName); */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 129;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select count(1) into :b0  from PM_RAP_FILE_SUMRY where (FI\
LE_TRANSFER_DIRECTION='O' and trim(RAP_FILE_NAME)=trim(:b1))";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )5942;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&FileCount;
   sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)FileName;
   sqlstm.sqhstl[1] = (unsigned int  )31;
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   if(ERRCODE!=0)
   {
      TRACEENTRY(1,"%s","Error checking duplicate record in PM_RAP_FILE_SUMRY table");
      TRACEENTRY(1,"%s :-%d-","sqlca.sqlcode",sqlca.sqlcode);
   }

   if(FileCount > 0)
   {
      stErrors.ERROR_CODE = sqlca.sqlcode;
      strcpy(stErrors.ERROR_DESC,"Duplicate RAP File found. Cannot Process the file");
      TRACEENTRY(1,"%s -%s-","Duplicate RAP File found. Cannot Process the file",FileName);
   }

   return FileCount;
}


int fnCheckDateDifference(char Date1[15],char Date2[15])
{
  int DataDiffinSec = 0 ;

   /* EXEC SQL SELECT nvl(((to_date(:Date1,'yyyymmddhh24miss')-to_date(:Date2,'yyyymmddhh24miss'))*86400),0) 
              INTO :DataDiffinSec
              FROM DUAL; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 129;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select nvl(((to_date(:b0,'yyyymmddhh24miss')-to_date(:b1,'\
yyyymmddhh24miss'))* 86400),0) into :b2  from DUAL ";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )5965;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)Date1;
   sqlstm.sqhstl[0] = (unsigned int  )15;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)Date2;
   sqlstm.sqhstl[1] = (unsigned int  )15;
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)&DataDiffinSec;
   sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[2] = (         int  )0;
   sqlstm.sqindv[2] = (         void  *)0;
   sqlstm.sqinds[2] = (         int  )0;
   sqlstm.sqharm[2] = (unsigned int  )0;
   sqlstm.sqadto[2] = (unsigned short )0;
   sqlstm.sqtdso[2] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   /* Check for Error in Execution */
   if((ERRCODE != 0))
   {
      TRACEENTRY(1,"%s-%s-%s-%s-","Date1 :",Date1,"Date2 :",Date2);
      TRACEENTRY(1,"%s-%d-","Main: Error Getting Date difference from the Database :",gProcessId);
      TRACEENTRY(1,"%s-%d-","Main: sqlca.sqlcode :",ERRCODE);
      return 0 ;
   }

   return DataDiffinSec ;

}

int fnCheckValidateFlag(int Error_Code,int Application_Tag, char Error_Type[9])
{
     int k = 0;


        if(gTagErrorCodeCount > 0)
        {
           for(k=0;k<gTagErrorCodeCount;k++)
           {
               ptTagDetails2 = (ptTagDetails1 + k);
               if((Error_Code == ptTagDetails2->ERROR_CODE) && (Application_Tag == ptTagDetails2->APPLICATION_TAG) && (strcmp(Error_Type,ptTagDetails2->ERROR_TYPE) == 0))
               {
                  return -1 ;
                }
           }
        }

        return 0;
}

/*
** To check if the file is present or not
*/
int fnFilePresent(char* szFileName)
{
   FILE *fp;

   if(strlen(szFileName) == 0) 
   {
      return -1;
   }
   else
   {
      fp = fopen(szFileName,"r");
      if(!fp)
      {
         return -1;
      }
      else
      {
         fclose(fp);
         return 1;
      }
   }/* else */
}/* fnFilePresent */


/***************************************************************************************************************
Function Name : sub_str

Description : Copies the given total number of character from given starting position of source string
into destination string

Parameter 1 : Source String
Parameter 2 : Destination String
Parameter 3 : Starting position in the Source String
Parameter 4 : No of Characters from the Starting position
***************************************************************************************************************/
void sub_str(char *so,char *tr,int st_ps,int no_ch)
{
   int i=0;
   *tr=0;
   while(i<st_ps-1 && *so){so++;i++;}
   i=0;
   while(i<no_ch && *so)
   {
     *tr++=*so++;i++;
   }
   *tr=0;
}
/***************************************************************************************************************
   /* Function to Validate Exchange Rate - WBS4.3  */

int ValidateExchangeRate()
{
   double gExchangeRate[12];
   double ExpExchRate;
   int ExcErrorNode=0;
   char TempNumtoChar[10];
   ExcErrorNode=5;
   double diff[15];
   int p,q=0;
   double Exchdiff=0;
   int ErrorCount=0;
   int lValidateFlag = 0;
   int m=0;
   int ErrorReturnValue = 0;
   int SetError=0;


         /* EXEC SQL SELECT COUNT(*)
                  INTO  :gExchCount 
                  FROM PM_CURRENCY_EXCHANGE_RATE
	          WHERE trunc(VALID_FROM) >=trunc(to_date('01'||to_char(to_date(:ACI.EarliestCallTimeStamp.LocalTimeStamp,'yyyymmddhh24miss'),'mm/yyyy'),'dd/mm/yyyy'))
                  AND trunc(VALID_TILL) <= add_months(trunc(to_date('01'||to_char(to_date(:ACI.LatestCallTimeStamp.LocalTimeStamp,'yyyymmddhh24miss'),'mm/yyyy'),'dd/mm/yyyy')),1)-1
                  AND trim(FROM_CURRENCY_CODE) = trim(:gLocalCurrencyCode)
                  AND trim(TO_CURRENCY_CODE) = trim(:gTapoutCurrencyCode); */ 

{
         struct sqlexd sqlstm;
         sqlstm.sqlvsn = 12;
         sqlstm.arrsiz = 129;
         sqlstm.sqladtp = &sqladt;
         sqlstm.sqltdsp = &sqltds;
         sqlstm.stmt = "select count(*)  into :b0  from PM_CURRENCY_EXCHANGE\
_RATE where (((trunc(VALID_FROM)>=trunc(to_date(('01'||to_char(to_date(:b1,'yy\
yymmddhh24miss'),'mm/yyyy')),'dd/mm/yyyy')) and trunc(VALID_TILL)<=(add_months\
(trunc(to_date(('01'||to_char(to_date(:b2,'yyyymmddhh24miss'),'mm/yyyy')),'dd/\
mm/yyyy')),1)-1)) and trim(FROM_CURRENCY_CODE)=trim(:b3)) and trim(TO_CURRENCY\
_CODE)=trim(:b4))";
         sqlstm.iters = (unsigned int  )1;
         sqlstm.offset = (unsigned int  )5992;
         sqlstm.selerr = (unsigned short)1;
         sqlstm.cud = sqlcud0;
         sqlstm.sqlest = (unsigned char  *)&sqlca;
         sqlstm.sqlety = (unsigned short)4352;
         sqlstm.occurs = (unsigned int  )0;
         sqlstm.sqhstv[0] = (         void  *)&gExchCount;
         sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
         sqlstm.sqhsts[0] = (         int  )0;
         sqlstm.sqindv[0] = (         void  *)0;
         sqlstm.sqinds[0] = (         int  )0;
         sqlstm.sqharm[0] = (unsigned int  )0;
         sqlstm.sqadto[0] = (unsigned short )0;
         sqlstm.sqtdso[0] = (unsigned short )0;
         sqlstm.sqhstv[1] = (         void  *)((ACI.EarliestCallTimeStamp).LocalTimeStamp);
         sqlstm.sqhstl[1] = (unsigned int  )15;
         sqlstm.sqhsts[1] = (         int  )0;
         sqlstm.sqindv[1] = (         void  *)0;
         sqlstm.sqinds[1] = (         int  )0;
         sqlstm.sqharm[1] = (unsigned int  )0;
         sqlstm.sqadto[1] = (unsigned short )0;
         sqlstm.sqtdso[1] = (unsigned short )0;
         sqlstm.sqhstv[2] = (         void  *)((ACI.LatestCallTimeStamp).LocalTimeStamp);
         sqlstm.sqhstl[2] = (unsigned int  )15;
         sqlstm.sqhsts[2] = (         int  )0;
         sqlstm.sqindv[2] = (         void  *)0;
         sqlstm.sqinds[2] = (         int  )0;
         sqlstm.sqharm[2] = (unsigned int  )0;
         sqlstm.sqadto[2] = (unsigned short )0;
         sqlstm.sqtdso[2] = (unsigned short )0;
         sqlstm.sqhstv[3] = (         void  *)gLocalCurrencyCode;
         sqlstm.sqhstl[3] = (unsigned int  )4;
         sqlstm.sqhsts[3] = (         int  )0;
         sqlstm.sqindv[3] = (         void  *)0;
         sqlstm.sqinds[3] = (         int  )0;
         sqlstm.sqharm[3] = (unsigned int  )0;
         sqlstm.sqadto[3] = (unsigned short )0;
         sqlstm.sqtdso[3] = (unsigned short )0;
         sqlstm.sqhstv[4] = (         void  *)gTapoutCurrencyCode;
         sqlstm.sqhstl[4] = (unsigned int  )4;
         sqlstm.sqhsts[4] = (         int  )0;
         sqlstm.sqindv[4] = (         void  *)0;
         sqlstm.sqinds[4] = (         int  )0;
         sqlstm.sqharm[4] = (unsigned int  )0;
         sqlstm.sqadto[4] = (unsigned short )0;
         sqlstm.sqtdso[4] = (unsigned short )0;
         sqlstm.sqphsv = sqlstm.sqhstv;
         sqlstm.sqphsl = sqlstm.sqhstl;
         sqlstm.sqphss = sqlstm.sqhsts;
         sqlstm.sqpind = sqlstm.sqindv;
         sqlstm.sqpins = sqlstm.sqinds;
         sqlstm.sqparm = sqlstm.sqharm;
         sqlstm.sqparc = sqlstm.sqharc;
         sqlstm.sqpadto = sqlstm.sqadto;
         sqlstm.sqptdso = sqlstm.sqtdso;
         sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


 
               if(ERRCODE != 0 || gExchCount == 0)
               {
                 TRACEENTRY(1,"%s","ERROR : Fetching Count from PM_CURRENCY_EXCHANGE_RATE table");
                 TRACEENTRY(1,"sqlca.sqlcode -%d-",ERRCODE);
                 stErrors.ERROR_CODE = sqlca.sqlcode;
	         TRACEENTRY(1,"FromDate : -%s- ToDate : -%s-",ACI.EarliestCallTimeStamp.LocalTimeStamp,ACI.LatestCallTimeStamp.LocalTimeStamp);
		 TRACEENTRY(1,"FROM_CURRENCY_CODE : -%s-",gLocalCurrencyCode);
		 TRACEENTRY(1,"TO_CURRENCY_CODE   : -%s-",gTapoutCurrencyCode);
                 strcpy(stErrors.ERROR_DESC,"Fetching Count from PM_CURRENCY_EXCHANGE_RATE table");
                 return -1;
               }


   if(gExchCount>0)
   {
       
         /* EXEC SQL  SELECT EXCHANGE_RATE
                   INTO :gExchangeRate
                   FROM PM_CURRENCY_EXCHANGE_RATE
	           WHERE trunc(VALID_FROM) >= trunc(to_date('01'||to_char(to_date(:ACI.EarliestCallTimeStamp.LocalTimeStamp,'yyyymmddhh24miss'),'mm/yyyy'),'dd/mm/yyyy'))
                   AND trunc(VALID_TILL) <= add_months(trunc(to_date('01'||to_char(to_date(:ACI.LatestCallTimeStamp.LocalTimeStamp,'yyyymmddhh24miss'),'mm/yyyy'),'dd/mm/yyyy')),1)-1
                   AND trim(FROM_CURRENCY_CODE) = trim(:gLocalCurrencyCode)
                   AND trim(TO_CURRENCY_CODE) = trim(:gTapoutCurrencyCode)
	           ORDER BY EXCHANGE_RATE DESC; */ 

{
         struct sqlexd sqlstm;
         sqlstm.sqlvsn = 12;
         sqlstm.arrsiz = 129;
         sqlstm.sqladtp = &sqladt;
         sqlstm.sqltdsp = &sqltds;
         sqlstm.stmt = "select EXCHANGE_RATE into :b0  from PM_CURRENCY_EXCH\
ANGE_RATE where (((trunc(VALID_FROM)>=trunc(to_date(('01'||to_char(to_date(:b1\
,'yyyymmddhh24miss'),'mm/yyyy')),'dd/mm/yyyy')) and trunc(VALID_TILL)<=(add_mo\
nths(trunc(to_date(('01'||to_char(to_date(:b2,'yyyymmddhh24miss'),'mm/yyyy')),\
'dd/mm/yyyy')),1)-1)) and trim(FROM_CURRENCY_CODE)=trim(:b3)) and trim(TO_CURR\
ENCY_CODE)=trim(:b4)) order by EXCHANGE_RATE desc  ";
         sqlstm.iters = (unsigned int  )12;
         sqlstm.offset = (unsigned int  )6027;
         sqlstm.selerr = (unsigned short)1;
         sqlstm.cud = sqlcud0;
         sqlstm.sqlest = (unsigned char  *)&sqlca;
         sqlstm.sqlety = (unsigned short)4352;
         sqlstm.occurs = (unsigned int  )0;
         sqlstm.sqhstv[0] = (         void  *)gExchangeRate;
         sqlstm.sqhstl[0] = (unsigned int  )sizeof(double);
         sqlstm.sqhsts[0] = (         int  )sizeof(double);
         sqlstm.sqindv[0] = (         void  *)0;
         sqlstm.sqinds[0] = (         int  )0;
         sqlstm.sqharm[0] = (unsigned int  )0;
         sqlstm.sqharc[0] = (unsigned int   *)0;
         sqlstm.sqadto[0] = (unsigned short )0;
         sqlstm.sqtdso[0] = (unsigned short )0;
         sqlstm.sqhstv[1] = (         void  *)((ACI.EarliestCallTimeStamp).LocalTimeStamp);
         sqlstm.sqhstl[1] = (unsigned int  )15;
         sqlstm.sqhsts[1] = (         int  )15;
         sqlstm.sqindv[1] = (         void  *)0;
         sqlstm.sqinds[1] = (         int  )0;
         sqlstm.sqharm[1] = (unsigned int  )0;
         sqlstm.sqadto[1] = (unsigned short )0;
         sqlstm.sqtdso[1] = (unsigned short )0;
         sqlstm.sqhstv[2] = (         void  *)((ACI.LatestCallTimeStamp).LocalTimeStamp);
         sqlstm.sqhstl[2] = (unsigned int  )15;
         sqlstm.sqhsts[2] = (         int  )15;
         sqlstm.sqindv[2] = (         void  *)0;
         sqlstm.sqinds[2] = (         int  )0;
         sqlstm.sqharm[2] = (unsigned int  )0;
         sqlstm.sqadto[2] = (unsigned short )0;
         sqlstm.sqtdso[2] = (unsigned short )0;
         sqlstm.sqhstv[3] = (         void  *)gLocalCurrencyCode;
         sqlstm.sqhstl[3] = (unsigned int  )4;
         sqlstm.sqhsts[3] = (         int  )4;
         sqlstm.sqindv[3] = (         void  *)0;
         sqlstm.sqinds[3] = (         int  )0;
         sqlstm.sqharm[3] = (unsigned int  )0;
         sqlstm.sqadto[3] = (unsigned short )0;
         sqlstm.sqtdso[3] = (unsigned short )0;
         sqlstm.sqhstv[4] = (         void  *)gTapoutCurrencyCode;
         sqlstm.sqhstl[4] = (unsigned int  )4;
         sqlstm.sqhsts[4] = (         int  )4;
         sqlstm.sqindv[4] = (         void  *)0;
         sqlstm.sqinds[4] = (         int  )0;
         sqlstm.sqharm[4] = (unsigned int  )0;
         sqlstm.sqadto[4] = (unsigned short )0;
         sqlstm.sqtdso[4] = (unsigned short )0;
         sqlstm.sqphsv = sqlstm.sqhstv;
         sqlstm.sqphsl = sqlstm.sqhstl;
         sqlstm.sqphss = sqlstm.sqhsts;
         sqlstm.sqpind = sqlstm.sqindv;
         sqlstm.sqpins = sqlstm.sqinds;
         sqlstm.sqparm = sqlstm.sqharm;
         sqlstm.sqparc = sqlstm.sqharc;
         sqlstm.sqpadto = sqlstm.sqadto;
         sqlstm.sqptdso = sqlstm.sqtdso;
         sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}




                if(ERRCODE != 0 && (gExchangeRate[0] ==0 && ERRCODE ==1403))
               {
                   TRACEENTRY(1,"%s","ERROR : Fetching Exchange Rate from PM_CURRENCY_EXCHANGE_RATE table");
                   TRACEENTRY(1,"sqlca.sqlcode -%d-",ERRCODE);
                   stErrors.ERROR_CODE = sqlca.sqlcode;
		   TRACEENTRY(1,"FromDate : -%s- ToDate : -%s-",ACI.EarliestCallTimeStamp.LocalTimeStamp,ACI.LatestCallTimeStamp.LocalTimeStamp);
		   TRACEENTRY(1,"FROM_CURRENCY_CODE : -%s-",gLocalCurrencyCode);
		   TRACEENTRY(1,"TO_CURRENCY_CODE   : -%s-",gTapoutCurrencyCode);
                   strcpy(stErrors.ERROR_DESC,"Fetching Eschange Rate from PM_CURRENCY_EXCHANGE_RATE table");
                   return -1;
                }


    for (m = 0;m<gExchangeRateCount;m++)
    {
         p=0;
         for(n= 0;n<gExchCount;n++)
         {
           ValidFlag =0;
           if ((int)(ACC.CurrencyConversionInfo[m].ExchangeRate/pow(10,ACC.CurrencyConversionInfo[m].NumberOfDecimalPlaces) - gExchangeRate[n])==0)
           {
              ValidFlag =1 ;
              break;
           }
          else
          {
           diff[p] = ((double)ACC.CurrencyConversionInfo[m].ExchangeRate/pow(10,ACC.CurrencyConversionInfo[m].NumberOfDecimalPlaces)- gExchangeRate[n]);
           if(diff[p]<0)
           diff[p]= -diff[p];
           else
             {
               diff[p] = diff[p];
             }
             p++;
          }
         }

     if(ValidFlag !=1)
     {
        for(l=0;l<p;l++)
        {
           if(l ==0)
           Exchdiff = diff[l];
           else if(diff[l]<Exchdiff)
           {
             Exchdiff=diff[l];
             q=l;
           }
        }
      }


    if(Exchdiff!=0.00000)
     {
              if ((double)(ACC.CurrencyConversionInfo[m].ExchangeRate/pow(10,ACC.CurrencyConversionInfo[m].NumberOfDecimalPlaces)) > gExchangeRate[q] )
                 {       
		       
                         ExpExchangeRate = gExchangeRate[q];
		         sprintf (TempNumtoChar,"%d",ACC.CurrencyConversionInfo[m].ExchangeRate);
                         REI.ERROR_CODE[gRejectedErrorNo]      = 201            ;
                         REI.APPLICATION_TAG[gRejectedErrorNo] = 104               ;
                         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")        ;
                         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CurrencyConversion");
                             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;80:%d:L;106:0:L;104:0:L",m+1) ;
                             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Exchange Rate higher than expected and applied to one or more Charges.");
                             strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                             gRejectedErrorNo++ ;
			    
                         }
                        break;
			
                  }  
                 else  if((double)(ACC.CurrencyConversionInfo[m].ExchangeRate/pow(10,ACC.CurrencyConversionInfo[m].NumberOfDecimalPlaces)) < gExchangeRate[q])
                 {
		         
		         ExpExchangeRate = gExchangeRate[q];
		         sprintf (TempNumtoChar,"%d",ACC.CurrencyConversionInfo[m].ExchangeRate);
                         REI.ERROR_CODE[gRejectedErrorNo]      = 200           ;
                         REI.APPLICATION_TAG[gRejectedErrorNo] = 104             ;
                         strcpy(REI.ERROR_TYPE[gRejectedErrorNo],"FATAL")      ;
                         lValidateFlag=fnCheckValidateFlag(REI.ERROR_CODE[gRejectedErrorNo],REI.APPLICATION_TAG[gRejectedErrorNo],REI.ERROR_TYPE[gRejectedErrorNo]);
                         if(lValidateFlag == 0)
                         {
                             strcpy(REI.CONTEXT_NAME[gRejectedErrorNo],"AccountingInformation");
                             strcpy(REI.ERROR_FIELD_NAME[gRejectedErrorNo],"CurrencyConversion");
                             sprintf(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo],"1:0:L;5:0:L;80:%d:L;106:0:L;104:0:L",l+1) ;
                             fnItemLevel(REI.ERROR_CONTEXT_DETAILS[gRejectedErrorNo]) ;
                             strcpy(REI.ERROR_MESSAGE[gRejectedErrorNo],"Exchange Rate less than expected (see BA.11) and applied to one or more Charges and at least one of the Charges the Exchange Rate is applied to is greater than zero.");
                              strcpy(REI.ERROR_VALUE[gRejectedErrorNo],TempNumtoChar);
                             gRejectedErrorNo++ ;
			  
                         }
                       break;
		   
                 } 
	      
          }
    }


    if((gRejectedErrorNo > 0) && (strcmp(gGenerateFilesFlg,"N")!=0))
      {
         for(ErrorCount=0; ErrorCount<gRejectedErrorNo; ErrorCount++)
           {
              ErrorReturnValue = SetBulkErrorDetails(gBulkErrorDetailsIndex, ErrorCount,ExcErrorNode)   ;
              if(ErrorReturnValue == -1)
               {
                 return -1;
               }
           }
       }
   gRejectedErrorNo = 0;
 }
return SetError;


}

