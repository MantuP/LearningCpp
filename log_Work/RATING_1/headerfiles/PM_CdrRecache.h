#include "ABL_ReloadCache.h"
#include "ABL_Service.h"

#ifndef CDRRECACHE_H
#define CDRRECACHE_H

class PM_CdrRecache : public ABL_ReloadCache
{
	public:
		PM_CdrRecache();
		 ~PM_CdrRecache();
		 Base_Registry* mb_clone() { return (Base_Registry*) new PM_CdrRecache; }
		 PM_CdrRecache* mb_createCopy() {return new PM_CdrRecache;} 
		 bool mb_checkRefreshReq(ABL_Service *p_ABL_Service);				//
 		 void mb_reSetRefreshReq(){m_brefreshReq = false;}				//
	private:
		bool m_brefreshReq;
};

extern "C" {EXPORT Base_Registry* gb_getPM_CdrRecache();}	//Global function used for dynamic loading

#endif
