
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
           char  filnam[17];
};
static struct sqlcxp sqlfpn =
{
    16,
    "ProcessStatus.pc"
};


static unsigned int sqlctx = 5196611;


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
            void  *sqhstv[5];
   unsigned int   sqhstl[5];
            int   sqhsts[5];
            void  *sqindv[5];
            int   sqinds[5];
   unsigned int   sqharm[5];
   unsigned int   *sqharc[5];
   unsigned short  sqadto[5];
   unsigned short  sqtdso[5];
} sqlstm = {12,5};

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

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* CUD (Compilation Unit Data) Array */
static short sqlcud0[] =
{12,4130,1,0,0,
5,0,0,1,0,0,32,28,0,0,0,0,0,1,0,
20,0,0,0,0,0,27,30,0,0,4,4,0,1,0,1,97,0,0,1,10,0,0,1,10,0,0,1,10,0,0,
51,0,0,3,120,0,5,123,0,0,1,1,0,1,0,1,3,0,0,
70,0,0,4,111,0,3,138,0,0,3,3,0,1,0,1,3,0,0,1,3,0,0,1,97,0,0,
97,0,0,5,119,0,5,151,0,0,1,1,0,1,0,1,3,0,0,
116,0,0,6,231,0,5,165,0,0,5,5,0,1,0,1,97,0,0,1,97,0,0,1,3,0,0,1,3,0,0,1,97,0,0,
151,0,0,7,0,0,29,180,0,0,0,0,0,1,0,
};


#include<global.h>
#include<Logger.h>
#include<signal.h>
#include <sqlca.h>
#define ERRCODE           sqlca.sqlcode
#define INIT_STR(x)                     (memset(x,'\0',sizeof(x)));

extern void UpdateProcess(int ProcessId,char Status);
extern long   gUnixPid;
extern char gProcessStartDate[15] ;
extern char   gErrorMessage[200] ;
extern char  gLockFilePathName[200];
extern long gSignalProcessId ;
extern char gConnectString[50] ;

void SignalHandler(int sig_num)
{
      /* re-set the signal handler again to catch_int, for next time */

      printf ("Caught signal %d\n", sig_num);

      INIT_STR(gErrorMessage) ;
/*
        Reason for DB Reconnection: If process is interupted(Killed,quit,interrupt..etc),DB connection will be disconnected when it is running inside cursor while loop.        So it is not possible to update the status of the process. 
        Solution: Release the work and reconnect to DB and then update the Process status 
*/

      /* EXEC SQL ROLLBACK WORK RELEASE; */ 

{
      struct sqlexd sqlstm;
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 0;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )5;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)4352;
      sqlstm.occurs = (unsigned int  )0;
      sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



      /* EXEC SQL CONNECT :gConnectString; */ 

{
      struct sqlexd sqlstm;
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 4;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.iters = (unsigned int  )10;
      sqlstm.offset = (unsigned int  )20;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)4352;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqhstv[0] = (         void  *)gConnectString;
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
         TRACEENTRY(1,"%s","SignalHandler: Error Connecting to the Database. Exiting from the Process.");
         TRACEENTRY(1,"%s : -%s-","SignalHandler: ConnectString Input: ",gConnectString);
         exit(0);
      }


      switch (sig_num)
      {
          case SIGHUP:
          {
             TRACEENTRY(1,"%s","SIGHUP Ignored");
             sprintf(gErrorMessage,"%s","SIGHUP Ignored");
             UpdateProcess(gSignalProcessId,'S');
             break;
          }
   /*     case SIGKILL:
          {
             TRACEENTRY(1,"%s","SIGKILL::Signal Kill");
             strcpy(gErrorMessage,"%s","SIGKILL::Signal Kill");
             printf("sigkilla");
             exit(0);
          }
   */     case SIGABRT:
          {
             TRACEENTRY(1,"%s","SIGABRT:: Abort Signal Generated.");
             sprintf(gErrorMessage,"%s","SIGABRT:: Abort Signal Generated.");
             UpdateProcess(gSignalProcessId,'S');
             exit(0);
          }
          case SIGINT:
          {
             TRACEENTRY(1,"%s","SIGINT:: Terminal interrupt signal.");
             sprintf(gErrorMessage,"%s","SIGINT:: Terminal interrupt signal.");
             UpdateProcess(gSignalProcessId,'S');
             exit(0);
          }
          case SIGQUIT:
          {
             TRACEENTRY(1,"%s","SIGQUIT:: Terminal quit signal encountered.");
             sprintf(gErrorMessage,"%s","SIGQUIT:: Terminal quit signal encountered.");
             UpdateProcess(gSignalProcessId,'S');
             exit(0);
          }
          case SIGSEGV:
          {
             TRACEENTRY(1,"%s","SIGSEGV:: Segmentation Fault encountered. Invalid memory referenced.");
             sprintf(gErrorMessage,"%s","SIGSEGV:: Segmentation Fault encountered. Invalid memory referenced.");
             UpdateProcess(gSignalProcessId,'S');
             exit(0);
          }
          case SIGTERM:
          {
             TRACEENTRY(1,"%s","SIGTERM:: Termination signal encountered. Exiting from the process.");
             sprintf(gErrorMessage,"%s","SIGTERM:: Termination signal encountered. Exiting from the process.");
             UpdateProcess(gSignalProcessId,'S');
             exit(0);
          }
          case SIGTSTP:
          {
             TRACEENTRY(1,"%s","SIGTSTP:: Terminal stop signal.");
             sprintf(gErrorMessage,"%s","SIGTSTP:: Terminal stop signal.");
             UpdateProcess(gSignalProcessId,'S');
             exit(0);
          }
          case SIGBUS:
          {
             TRACEENTRY(1,"%s","SIGBUS:: Bus error encountered. Process will be stopped.");
             sprintf(gErrorMessage,"%s","SIGBUS:: Bus error encountered. Process will be stopped.");
             UpdateProcess(gSignalProcessId,'S');
             exit(0);
          }
          case SIGSYS:
          {
             TRACEENTRY(1,"%s","SIGSYS:: Bad system call. Process will be stopped.");
             sprintf(gErrorMessage,"%s","SIGSYS:: Bad system call. Process will be stopped.");
             UpdateProcess(gSignalProcessId,'S');
             exit(0);
          }
      }
}


void UpdateProcess(int ProcessId,char Status)
{
   char r_lock[150] ;
   sprintf(r_lock,"rm %s",gLockFilePathName);

   if(Status == 'R')
   {
      /* EXEC SQL UPDATE PM_PROCESSES
                  SET START_STOP_FLG           = 'I',
                      PROCESS_STATUS           = 'R',
                      PROCESS_LAST_START_DATE  = CURRENT_DATE
                WHERE PROCESS_ID               = :ProcessId; */ 

{
      struct sqlexd sqlstm;
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 4;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.stmt = "update PM_PROCESSES  set START_STOP_FLG='I',PROCESS_STA\
TUS='R',PROCESS_LAST_START_DATE=CURRENT_DATE where PROCESS_ID=:b0";
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )51;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)4352;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqhstv[0] = (         void  *)&ProcessId;
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
      if((ERRCODE != 0))
      {
         TRACEENTRY(1,"%s-%d-","Main: Error Updating PM_PROCESSES for the ProcessId :",ProcessId);
         TRACEENTRY(1,"%s-%d-","Main: sqlca.sqlcode :",ERRCODE);
         unlink(gLockFilePathName) ;
         exit(0);
      }

      /* EXEC SQL INSERT
                 INTO PM_PROCESS_STATUS(PROCESS_ID, UNIX_PID, START_TIME)
               VALUES (:ProcessId ,:gUnixPid , TO_DATE(:gProcessStartDate,'YYYYMMDDHH24MISS')) ; */ 

{
      struct sqlexd sqlstm;
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 4;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.stmt = "insert into PM_PROCESS_STATUS (PROCESS_ID,UNIX_PID,STAR\
T_TIME) values (:b0,:b1,TO_DATE(:b2,'YYYYMMDDHH24MISS'))";
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )70;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)4352;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqhstv[0] = (         void  *)&ProcessId;
      sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[0] = (         int  )0;
      sqlstm.sqindv[0] = (         void  *)0;
      sqlstm.sqinds[0] = (         int  )0;
      sqlstm.sqharm[0] = (unsigned int  )0;
      sqlstm.sqadto[0] = (unsigned short )0;
      sqlstm.sqtdso[0] = (unsigned short )0;
      sqlstm.sqhstv[1] = (         void  *)&gUnixPid;
      sqlstm.sqhstl[1] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[1] = (         int  )0;
      sqlstm.sqindv[1] = (         void  *)0;
      sqlstm.sqinds[1] = (         int  )0;
      sqlstm.sqharm[1] = (unsigned int  )0;
      sqlstm.sqadto[1] = (unsigned short )0;
      sqlstm.sqtdso[1] = (unsigned short )0;
      sqlstm.sqhstv[2] = (         void  *)gProcessStartDate;
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



      if (ERRCODE != 0)
      {
         TRACEENTRY (1,"%s%d","UpdateProcess:Start: Error in inserting data to PM_PROCESS_STATUS. Error Code::",ERRCODE);
      }

      sprintf(gErrorMessage,"%s","Normal Exit");
   }
   else if(Status == 'S')
   {
      /* EXEC SQL UPDATE PM_PROCESSES
                  SET START_STOP_FLG           = 'I',
                      PROCESS_STATUS           = 'S',
                      PROCESS_LAST_STOP_DATE   = CURRENT_DATE
                WHERE PROCESS_ID               = :ProcessId; */ 

{
      struct sqlexd sqlstm;
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 4;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.stmt = "update PM_PROCESSES  set START_STOP_FLG='I',PROCESS_STA\
TUS='S',PROCESS_LAST_STOP_DATE=CURRENT_DATE where PROCESS_ID=:b0";
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )97;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)4352;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqhstv[0] = (         void  *)&ProcessId;
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
      if((ERRCODE != 0) &&(sqlca.sqlerrd[2]==0))
      {
         TRACEENTRY(1,"%s-%d-","UpdateProcess: Error Updating PM_PROCESSES for the ProcessId :",ProcessId);
         TRACEENTRY(1,"%s-%d-","UpdateProcess: sqlca.sqlcode :",ERRCODE);
      }


      /* EXEC SQL UPDATE PM_PROCESS_STATUS
                  SET STOP_TIME    = CURRENT_DATE,
                      ELAPSED_TIME = (CURRENT_DATE - TO_DATE(:gProcessStartDate,'YYYYMMDDHH24MISS'))*60*60*24,
                      REMARKS      = :gErrorMessage
                WHERE PROCESS_ID   = :ProcessId
                  AND UNIX_PID     = :gUnixPid 
                  AND START_TIME = TO_DATE(:gProcessStartDate,'YYYYMMDDHH24MISS') ; */ 

{
      struct sqlexd sqlstm;
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 5;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.stmt = "update PM_PROCESS_STATUS  set STOP_TIME=CURRENT_DATE,EL\
APSED_TIME=((((CURRENT_DATE-TO_DATE(:b0,'YYYYMMDDHH24MISS'))* 60)* 60)* 24),RE\
MARKS=:b1 where ((PROCESS_ID=:b2 and UNIX_PID=:b3) and START_TIME=TO_DATE(:b0,\
'YYYYMMDDHH24MISS'))";
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )116;
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
      sqlstm.sqhstv[1] = (         void  *)gErrorMessage;
      sqlstm.sqhstl[1] = (unsigned int  )200;
      sqlstm.sqhsts[1] = (         int  )0;
      sqlstm.sqindv[1] = (         void  *)0;
      sqlstm.sqinds[1] = (         int  )0;
      sqlstm.sqharm[1] = (unsigned int  )0;
      sqlstm.sqadto[1] = (unsigned short )0;
      sqlstm.sqtdso[1] = (unsigned short )0;
      sqlstm.sqhstv[2] = (         void  *)&ProcessId;
      sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[2] = (         int  )0;
      sqlstm.sqindv[2] = (         void  *)0;
      sqlstm.sqinds[2] = (         int  )0;
      sqlstm.sqharm[2] = (unsigned int  )0;
      sqlstm.sqadto[2] = (unsigned short )0;
      sqlstm.sqtdso[2] = (unsigned short )0;
      sqlstm.sqhstv[3] = (         void  *)&gUnixPid;
      sqlstm.sqhstl[3] = (unsigned int  )sizeof(long);
      sqlstm.sqhsts[3] = (         int  )0;
      sqlstm.sqindv[3] = (         void  *)0;
      sqlstm.sqinds[3] = (         int  )0;
      sqlstm.sqharm[3] = (unsigned int  )0;
      sqlstm.sqadto[3] = (unsigned short )0;
      sqlstm.sqtdso[3] = (unsigned short )0;
      sqlstm.sqhstv[4] = (         void  *)gProcessStartDate;
      sqlstm.sqhstl[4] = (unsigned int  )15;
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



      if (ERRCODE != 0)
      {
         TRACEENTRY (1,"%s%d","UpdateProcess:Stop: Error in Updating data to PM_PROCESS_STATUS. Error Code::",ERRCODE);
      }
      unlink(gLockFilePathName) ;
   }

   /* EXEC SQL COMMIT; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 5;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )151;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


}


