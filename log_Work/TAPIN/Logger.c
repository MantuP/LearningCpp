#include "Logger.h"
/***
This Function to eliminate the Error
***/


void doNothing()
{}

/*
This Function Checks the size of the log file , if it exceeds the size then open the new log file for rotation (This Function Dynamically Opens the new log file when the log file size exceeds the rotation size) 
*/

int checkLogFile (struct Logger *loggerPtr)
{
	struct stat l_buf;
 	struct stat *l_bufPtr=&l_buf;
	int l_result;
	char l_tmp[6];
	char l_arr[100];

	if(logger.mRotationPolicy == DATE_BASED)
	{
		checkLogFileDateBased(loggerPtr);
	}
    if(loggerPtr->mFileOpen == LOG_TRUE_FLAG)
    {
		sprintf(l_tmp,".%04d",loggerPtr->mRotate.mLogRotate.mSequence);
		strcpy(l_arr,logger.mFileName);
		/*printf("File Name in The Stat Before cat   %s \n", l_arr);*/
		strcat(l_arr,l_tmp);
		/*printf("File Name in The Stat %s \n", l_arr);*/
		l_result = stat(l_arr,l_bufPtr);
		/*printf("Size of the file %d  rotation size %d \n",l_bufPtr->st_size,loggerPtr->mRotate.mLogRotate.mRotationSize);*/
		if(loggerPtr->mRotate.mLogRotate.mRotationSize  < l_bufPtr->st_size)
		{
			memset(l_arr,'\0',99);
			fclose(logger.mFp);
			loggerPtr->mRotate.mLogRotate.mSequence = loggerPtr->mRotate.mLogRotate.mSequence + 1;
		 	loggerPtr->mRotate.mLogRotate.mSequence = ((loggerPtr->mRotate.mLogRotate.mSequence)%loggerPtr->mRotate.mLogRotate.mRotationCounter);
			sprintf(l_tmp,".%04d",loggerPtr->mRotate.mLogRotate.mSequence);
			strcpy(l_arr,logger.mFileName);
			strcat(l_arr,l_tmp); 
			/*printf("In Rotation Change in the File  %s\n",l_arr);*/
			logger.mFp =  fopen(l_arr,"w+");
		}
  }
}
/***
 Function Name openLogFile
 Arguments    address of logger struture 
 opens the Recent Log file in append mode 
 if Recent Log file size is greater than rotation size then opens the 0th file in write mode
***/

int openLogFile(struct Logger *loggerPtr)
{
	char l_logfile[100];
	int l_counter=0;
	char l_arr[10];
 	struct stat l_buf;
 	struct stat *l_bufPtr=&l_buf;
	int l_result;
	off_t  l_rotationSize;
	
	loggerPtr->mRotate.mLogRotate.mSequence =0;
	
	for(l_counter=1;l_counter < (loggerPtr->mRotate.mLogRotate.mRotationCounter + 1) ;l_counter= l_counter +1)
	{/*begin for loop*/
		loggerPtr->mRotate.mLogRotate.mSequence = loggerPtr->mRotate.mLogRotate.mSequence + 1;
		loggerPtr->mRotate.mLogRotate.mSequence = ((loggerPtr->mRotate.mLogRotate.mSequence)%loggerPtr->mRotate.mLogRotate.mRotationCounter);
		memset(l_logfile,'\0',99);
		strcpy(l_logfile,loggerPtr->mFileName);
		sprintf(l_arr,".%04d",loggerPtr->mRotate.mLogRotate.mSequence);
		strcat(l_logfile,l_arr);
		/* Check the Existency of the Log file if exists get the size of the Log File */
		l_result = stat(l_logfile,l_bufPtr);
		if(l_result == -1)
		{
			loggerPtr->mFp  = fopen(l_logfile,"a+");
			loggerPtr->mFileOpen = LOG_TRUE_FLAG;
			return 0;
		}
	    l_rotationSize	= l_bufPtr->st_size;
		if((l_rotationSize  < loggerPtr->mRotate.mLogRotate.mRotationSize )||(l_counter == loggerPtr->mRotate.mLogRotate.mRotationCounter))
		{
			if(l_counter == ((loggerPtr->mRotate.mLogRotate.mRotationCounter)+1))
			{
				loggerPtr->mFp  = fopen(l_logfile,"w+");
			}
			else
			{
				loggerPtr->mFp  = fopen(l_logfile,"a+");
			}
			loggerPtr->mFileOpen = LOG_TRUE_FLAG;
			return 0;
		}
	}/* End of For Loop */	
}// End of Function openLogFile

/* Function Name checkLogFileDateBased 
   Argument Pointer to a Logger Structure
   checks whether day is changed and then opens the log file on the new day  format */
int checkLogFileDateBased(struct Logger *loggerPtr)
{
	struct tm l_buf;
	struct tm *l_some;
	time_t l_time;
	struct tm l_dbuf;
	struct tm *l_dsome;
	int l_dayOfMonth; 
	char l_tmp[25];
	char l_fileName[150];
	l_some = &l_buf;
	l_dsome = &l_dbuf;

	l_some = localtime(&loggerPtr->mRotate.mLogDate.mLogFileCreationDate);
	l_dayOfMonth = l_some->tm_mday ;
        loggerPtr->mRotate.mLogDate.mLogFileCreationDate = time(NULL);
	l_dsome  = localtime(&loggerPtr->mRotate.mLogDate.mLogFileCreationDate);
	/**
	if system date is changed (Next day)	
	**/
	if(l_dsome->tm_mday  == l_dayOfMonth)
	{
		return 0;		
	}
	sprintf(l_tmp,"_%02d_%02d_%04d",l_dsome->tm_mday,(l_dsome->tm_mon+1),(l_dsome->tm_year+1900));
	loggerPtr->mRotate.mLogRotate.mSequence = 0;
	strcpy(l_fileName,loggerPtr->mBaseName);
	strcpy(loggerPtr->mFileName,l_fileName);
	strcat(l_fileName,l_tmp);
	strcpy(loggerPtr->mFileName,l_fileName);
	
}// End of Function checkLogFileDateBased

/**
	Function name openFileOnDate
	Arguments : Pointer to the logger structure
	get the System Date and store in the Logger Structure and create the log file name format 
**/
int openFileOnDate(struct Logger *loggerPtr)
{

	struct tm l_buf;
	struct tm *l_some;
	char l_filename[150];
	char l_tmp[25];
	l_some = &l_buf;

	loggerPtr->mRotate.mLogDate.mLogFileCreationDate = time(NULL);
	loggerPtr->mRotate.mLogRotate.mRotationCounter= 1000;
	loggerPtr->mRotate.mLogRotate.mSequence =0;
	l_some = localtime(&loggerPtr->mRotate.mLogDate.mLogFileCreationDate);
	sprintf(l_tmp,"_%02d_%02d_%04d",l_some->tm_mday,(l_some->tm_mon+1),(l_some->tm_year+1900));
	strcat(loggerPtr->mFileName,l_tmp);
	openLogFile(loggerPtr);
}//End of function openFileOnDate


/** This Function contains the configuration details to start the logger for size based and Date Based 
	Function Name  startLogger 
 **/

/* void startLogger(void) */
void startLogger(char *path_in) 
{

#ifdef ERROR_LOG_LEVEL  
	/** 
		Configured Parameters 
		Base File Name for Log file Specify in logger.mFileName 
		Date Based (DATE_BASED)  or Size Based (SIZE_BASED)  Specify in logger.mRotationPolicy
		Specify Rotation Size    (Size of the Log File )
		For Size Based	
			Specify Rotation Counter (Number  of Log Files for Rotation)
	**/
   // Base Log File name with path 
/** copy the base of the log file to the logger structure **/ 
        strcpy(logger.mFileName,path_in);
	/* strcpy(logger.mFileName,"/usr/ability/PROVISIONING/log_dir/Log"); */
	strcpy(logger.mBaseName,logger.mFileName);
   // Specify Whether Size Based (SIZE_BASED)  or Date Based (DATE_BASED)  Logging 
	logger.mRotationPolicy = DATE_BASED;
	logger.mRotate.mLogRotate.mRotationCounter = 5;
	logger.mRotate.mLogRotate.mRotationSize    = 2000*1024*1024; //2 MB is Rotation Size 

	
	if(logger.mRotationPolicy == DATE_BASED)
	{
     /** In Date Based Logging Size for Rotation is set to Maximum Value **/
		logger.mRotate.mLogRotate.mRotationCounter = 1000;
		openFileOnDate(&logger);
	}
	else
	{
		openLogFile(&logger);
		if(logger.mFp != NULL)
		{
			logger.mFileOpen = LOG_TRUE_FLAG;
		}
  		else
  		{
			logger.mFileOpen = LOG_FALSE_FLAG;
		}
	}
 #endif

}// End of Function startLogger 

/*
int main ()
{
	int  l_count=0;
	struct tm l_tmStruct;
 	l_count = 1;
	startLogger("path");
	while(1)
 	{
  		TRACEENTRY (1, "%s %s","some message","hello");
  		TRACEENTRY (2, "%s", "some message");
  		TRACEENTRY (3, "%s", "some message");
  		TRACEENTRY (4, "%s", "some message");
  		TRACEENTRY (5, "%s", "some message");
		l_count = l_count + 1;
		if(l_count%7 == 0 )
		{
		}
 	}
 }
*/
