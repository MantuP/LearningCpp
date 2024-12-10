#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#ifndef  ENABLE_LOGGER_H
#define  ENABLE_LOGGER_H

#define LOG_TRUE_FLAG	 	1
#define LOG_FALSE_FLAG   	0
#define SIZE_BASED			2
#define DATE_BASED			3
		
struct Logger
{
  	int mFileOpen;		//Set true when open, false otherwise
  	char mFileName[150];	//Base file Name of the Log File
	char  mBaseName[100];
  	FILE *mFp;
  	int mRotationPolicy;	//SIZE_BASED, DATE_BASED
  	int mItrs;			// Check for ration after n iterations
	struct tm *l_tm;
	struct tm l_tm_a;
	time_t	l_time;
	
	struct  Rotate
  	{
    	struct LogRotate
    	{
      		int mSequence;
      		off_t  mRotationSize;
			int mRotationCounter;
    	}mLogRotate;
    	struct LogDate
    	{
      		time_t mLogFileCreationDate;	
      		long mNewFileCreationDurn;	
    	}mLogDate ;
 	 }mRotate;
};
struct Logger logger;
#if (ERROR_LOG_LEVEL < 1)
	#define TRACEENTRY(format, args...)     
#else
	#define TRACEENTRY(LEVEL, format, args...) if(LEVEL <= ERROR_LOG_LEVEL) { if(logger.mItrs++% 10 == 0) checkLogFile(&logger);logger.l_time = time(NULL); localtime_r(&logger.l_time,&logger.l_tm_a); logger.l_tm = &logger.l_tm_a; fprintf(logger.mFp,"|%02d:%02d:%02d|%02d/%02d/%04d| "format"%s",logger.l_tm->tm_hour,logger.l_tm->tm_min,logger.l_tm->tm_sec,logger.l_tm->tm_mday,(logger.l_tm->tm_mon+1),(logger.l_tm->tm_year+1900),args,"\n");fflush(logger.mFp); }
#endif
#endif

