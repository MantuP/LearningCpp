#ifndef STOPRATING_H
#define STOPRATING_H

#include "ABL_StopAgent.h"
#include "ABL_AgentCommunicator.h"

class StopRating  : public ABL_StopAgent
{
public:
	StopRating();								// Default constructor
	virtual			~StopRating();				// Default desctructor
	virtual Base_Registry*	mb_clone();	// Function to create a new object
	virtual bool mb_initProcess(ABL_Service *p_ABL_ServicePtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr);
	virtual bool mb_pollToStop();
protected:
	ABL_String	m_stopSignalFile;
};

extern "C" {EXPORT Base_Registry* gb_getStopRating();}

#endif  

