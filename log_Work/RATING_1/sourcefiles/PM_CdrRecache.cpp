#include "PM_CdrRecache.h"
#include "ABL_Exception.h"
#include "ABL_Service.h"
#include "ABL_Connection.h"
#include "ABL_Statement.h"
#include "ABL_ResultSet.h"
#include "ABL_String.h"



//////////////////////////////////////////////////////////////////////
// 
//		Construction/Destruction
//
//////////////////////////////////////////////////////////////////////

PM_CdrRecache::PM_CdrRecache()
{

	m_brefreshReq=false;
}

PM_CdrRecache::~PM_CdrRecache()
{
	//cout<<"ABL_RefreshCache Des"<<endl;
}

bool PM_CdrRecache::mb_checkRefreshReq(ABL_Service *p_ABL_ServicePtr)
{
	ABL_Service *l_ABL_Service=p_ABL_ServicePtr;

	ABL_String  l_status;
	ABL_Connection l_connection;
	l_connection.mb_createConnection(*p_ABL_ServicePtr);

	double process_id=l_ABL_Service->mb_getInt("PROCESS_ID");
	ABL_Statement l_statement;
	ABL_String l_sql("SELECT nvl(CACHE_RELOAD,'N') FROM PM_PROCESSES where  PROCESS_ID=:1 and rownum=1");
	l_statement = l_connection.mb_createStatement(l_sql);
	l_statement.mb_setDouble(1,process_id);
	ABL_ResultSet l_result = l_statement.mb_executeQuery();
	m_brefreshReq = false;
	l_status="N";

	while(l_result.mb_fetch())
	{

		 l_status = l_result.mb_getString(1);		
	}

	 l_statement.mb_closeResultSet(l_result)  ;
	l_connection.mb_terminateStatement(l_statement) ;

	if(l_status=="Y")
	{  
		m_brefreshReq = true;
	   try
	   {
			l_sql		        ="UPDATE PM_PROCESSES set CACHE_RELOAD='N' WHERE PROCESS_ID=:1";			
			l_statement     =	l_connection.mb_createStatement(l_sql);	
			l_statement.mb_setDouble(1,process_id);
			l_statement.mb_executeUpdate();
			l_connection.mb_terminateStatement(l_statement);
			l_connection.mb_commit();
	   }
       catch(ABL_Exception &e)
       {
		   return false;
	   }
	}
	

	return m_brefreshReq;
}

extern "C" 
{ EXPORT Base_Registry* gb_getPM_CdrRecache()
	{
		return (Base_Registry*) new PM_CdrRecache;	
	}
}

