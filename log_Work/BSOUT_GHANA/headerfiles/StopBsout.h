#ifndef STOPBSOUT_H
#define STOPBSOUT_H

#include "ABL_StopAgent.h"
#include "ABL_AgentCommunicator.h"

class StopBsout  : public ABL_StopAgent
{
	public:
		StopBsout();	// Default constructor
		virtual	~StopBsout();	// Default desctructor
		virtual Base_Registry*	mb_clone();	// Function to create a new object
		virtual bool mb_initProcess(ABL_Service *p_ABL_ServicePtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr);
		virtual bool mb_pollToStop();

	protected:
		ABL_String	m_stopSignalFile;
};

extern "C" 
{
	EXPORT Base_Registry* gb_getStopBsout();
}

#endif  
