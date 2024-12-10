#include "StopRating.h"
#include "ABL_AgentCommunicator.h"
#include "ABL_Exception.h"
#include <fstream>
#include "ABL_String.h"


extern "C" {EXPORT 
Base_Registry* gb_getStopRating()
{
	return ( (Base_Registry*) new StopRating);
}
}

StopRating::StopRating()
{
	//
}

StopRating::~StopRating()
{
	//
}

Base_Registry*	StopRating::mb_clone()
{
	return ( (Base_Registry*) new StopRating );
}

bool StopRating::mb_initProcess(ABL_Service *p_ABL_ServicePtr, ABL_AgentCommunicator *p_ABL_AgentCommunicatorPtr)
{
	m_ABL_ServicePtr = p_ABL_ServicePtr;
	
	try
	{
		p_ABL_AgentCommunicatorPtr->mb_getParameter("STOP_FILE",m_stopSignalFile);
	}
	catch(ABL_Exception &e)
	{
		*m_ABL_ServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
		return false;
	}
	return true;
}

bool StopRating::mb_pollToStop()
{

	std::ifstream inFile;  
	inFile.open(m_stopSignalFile.c_str(),std::ios::in);
	
	if (inFile.is_open()) 
	{
		inFile.close();
		//std::cout<<m_stopSignalFile.c_str()<<std::endl;
		//unlink(m_stopSignalFile.c_str());
		return true ;
	}	
	return false;
}
