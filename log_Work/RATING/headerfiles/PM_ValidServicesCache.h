/***********************************************************
************************************************************
************************************************************
Agent Name:  PM_ValidServicesCache.h
Module Name: FrameWork Rating
Dated: 21/01/2010


************************************************************
************************************************************
***********************************************************/

#ifndef PM_ValidServicesCache_H
#define PM_ValidServicesCache_H

#include "ABL_DataCache.h"
#include "ABL_String.h"
#include "ABL_DateTime.h"
#include "ABL_DbDate.h"
#include "ABL_Date.h"
#include "Base_Registry.h"


class PM_ValidServicesCache : public ABL_DataCache
{
public:
	PM_ValidServicesCache(){}
	//added InTrafficType and OutTrafficType to the constructor for LTE usage for 4.3 release
	PM_ValidServicesCache(ABL_Date  pd_Valid_From ,ABL_Date  pd_Valid_To ,ABL_Date  pd_test_Start_Date, ABL_Date  pd_test_end_date,ABL_String ps_ServiceCode = "",ABL_String ps_OperatorCode = "", ABL_String ps_IncRateDirection = "",ABL_String ps_OutRateDirection = "",ABL_String ps_IncDefaultratezone = "",ABL_String ps_OutDefaultratezone = "",ABL_String ps_IncRateIntrConnect = "",ABL_String ps_OutRateIntrConnect = "",ABL_String ps_IncPaymentDirection = "",ABL_String ps_OutPaymentDirection = "",ABL_String ps_IncUnit = "",int pn_IncQtyUnit = 0,ABL_String ps_OutUnit = "",int pn_OutQtyUnit = 0,ABL_String ps_IncDestinationtype = "",ABL_String ps_OutDestinationtype = "",ABL_String ps_ServiceType = "",ABL_String ps_DataTypeIndicator = "",ABL_String ps_basic_service="",ABL_String ps_IncTrafficType = "", ABL_String ps_OutTrafficType = ""): md_Valid_From(pd_Valid_From),md_Valid_To(pd_Valid_To),md_test_Start_Date(pd_test_Start_Date), md_test_end_date(pd_test_end_date),  ms_ServiceCode(ps_ServiceCode), ms_OperatorCode(ps_OperatorCode), ms_IncRateDirection(ps_IncRateDirection), ms_OutRateDirection(ps_OutRateDirection), ms_IncDefaultratezone(ps_IncDefaultratezone), ms_OutDefaultratezone(ps_OutDefaultratezone), ms_IncRateIntrConnect(ps_IncRateIntrConnect), ms_OutRateIntrConnect(ps_OutRateIntrConnect), ms_IncPaymentDirection(ps_IncPaymentDirection), ms_OutPaymentDirection(ps_OutPaymentDirection), ms_IncUnit(ps_IncUnit), mn_IncQtyUnit(pn_IncQtyUnit), ms_OutUnit(ps_OutUnit), mn_OutQtyUnit(pn_OutQtyUnit), ms_IncDestinationtype(ps_IncDestinationtype), ms_OutDestinationtype(ps_OutDestinationtype), ms_ServiceType(ps_ServiceType), ms_DataTypeIndicator(ps_DataTypeIndicator), ms_basic_service(ps_basic_service),ms_IncTrafficType(ps_IncTrafficType),ms_OutTrafficType(ps_OutTrafficType) {}

	PM_ValidServicesCache(const PM_ValidServicesCache& p_copyObject);
	virtual ~PM_ValidServicesCache(){}
	virtual Base_Registry* mb_clone() { return ((Base_Registry*) new PM_ValidServicesCache()); }
	virtual long  mb_getSize(ABL_Service *p_ABL_ServicePtr, ABL_String p_filterCaluse) { return 1; }
	bool mb_isEqual(CBase* p_CBase_ptr);
	unsigned int mb_hash(){ return ms_OperatorCode.mb_hash(); }
	CBase* mb_createCopy();
	bool mb_loadData(data_container *p_container, ABL_Service *p_ABL_Service_ptr,ABL_String p_filterClause) ; 	
	void trim(ABL_String *ls_sIn) ;

	void mb_setValid_From(ABL_Date pd_Valid_From) { md_Valid_From = pd_Valid_From; }
    void mb_setValid_To(ABL_Date pd_Valid_To) { md_Valid_To = pd_Valid_To; }

    void mb_settest_Start_Date(ABL_Date pd_test_Start_Date) { md_test_Start_Date = pd_test_Start_Date; }
    void mb_settest_end_date(ABL_Date pd_test_end_date) { md_test_end_date = pd_test_end_date; }

    void mb_setServiceCode(ABL_String ps_ServiceCode) { ms_ServiceCode = ps_ServiceCode; }
	void mb_setOperatorCode(ABL_String ps_OperatorCode) { ms_OperatorCode = ps_OperatorCode; }
	void mb_setIncRateDirection(ABL_String ps_IncRateDirection) { ms_IncRateDirection = ps_IncRateDirection; }
	void mb_setOutRateDirection(ABL_String ps_OutRateDirection) { ms_OutRateDirection = ps_OutRateDirection; }
	void mb_setIncDefaultratezone(ABL_String ps_IncDefaultratezone) { ms_IncDefaultratezone = ps_IncDefaultratezone; }
	void mb_setDefaultratezone(ABL_String ps_OutDefaultratezone) { ms_OutDefaultratezone = ps_OutDefaultratezone; }
	void mb_setIncRateIntrConnect(ABL_String ps_IncRateIntrConnect) { ms_IncRateIntrConnect = ps_IncRateIntrConnect; }
	void mb_setOutRateIntrConnect(ABL_String ps_OutRateIntrConnect) { ms_OutRateIntrConnect = ps_OutRateIntrConnect; }
    void mb_setIncPaymentDirection(ABL_String ps_IncPaymentDirection) { ms_IncPaymentDirection = ps_IncPaymentDirection; }
	void mb_setOutPaymentDirection(ABL_String ps_OutPaymentDirection) { ms_OutPaymentDirection = ps_OutPaymentDirection; }       
    void mb_setIncUnit(ABL_String ps_IncUnit) { ms_IncUnit = ps_IncUnit; }

    void mb_setIncQtyUnit(int pn_IncQtyUnit) { mn_IncQtyUnit = pn_IncQtyUnit; }
	void mb_setOutUnit(ABL_String ps_OutUnit) { ms_OutUnit = ps_OutUnit; }
    void mb_setOutQtyUnit(int pn_OutQtyUnit) { mn_OutQtyUnit = pn_OutQtyUnit; }
	void mb_setIncDestinationtype(ABL_String ps_IncDestinationtype) { ms_IncDestinationtype = ps_IncDestinationtype; }
	void mb_setOutDestinationtype(ABL_String ps_OutDestinationtype) { ms_OutDestinationtype = ps_OutDestinationtype; }
	void mb_setServiceType(ABL_String ps_ServiceType) { ms_ServiceType = ps_ServiceType; }
    void mb_setDataTypeIndicator(ABL_String ps_DataTypeIndicator) { ms_DataTypeIndicator = ps_DataTypeIndicator; }
	void mb_setbasic_service(ABL_String ps_basic_service) { ms_basic_service = ps_basic_service; }
	//added as per LTE usage for 4.3 release
	void mb_setIncTrafficType(ABL_String ps_IncTrafficType) {ms_IncTrafficType = ps_IncTrafficType;}
	void mb_setOutTrafficType(ABL_String ps_OutTrafficType) {ms_OutTrafficType = ps_OutTrafficType;}
	//modification end
	
	ABL_Date  mb_getValid_From() { return md_Valid_From; }
    ABL_Date  mb_getValid_To() { return md_Valid_To; }
    ABL_Date  mb_gettest_Start_Date() { return md_test_Start_Date; }
    ABL_Date  mb_gettest_end_date() { return md_test_end_date; }

    ABL_String mb_getServiceCode() { return ms_ServiceCode; }
    ABL_String mb_getOperatorCodet() { return ms_OperatorCode;}
	ABL_String mb_getIncRateDirection() { return ms_IncRateDirection;}
	ABL_String mb_getOutRateDirection() { return ms_OutRateDirection;}
	ABL_String mb_getIncDefaultratezone() { return ms_IncDefaultratezone;}
    ABL_String mb_getOutDefaultratezone() { return ms_OutDefaultratezone;}
	ABL_String mb_getIncRateIntrConnect() { return ms_IncRateIntrConnect;}
	ABL_String mb_getOutRateIntrConnect() { return ms_OutRateIntrConnect;}
	ABL_String mb_getIncPaymentDirection() { return ms_IncPaymentDirection;}
	ABL_String mb_getOutPaymentDirection() { return ms_OutPaymentDirection;}
	ABL_String mb_getIncUnit() { return ms_IncUnit;}
    int mb_getIncQtyUnit() { return mn_IncQtyUnit;}
	ABL_String mb_getOutUnit() { return ms_OutUnit;}
    int mb_getOutQtyUnit() { return mn_OutQtyUnit;}
	ABL_String mb_getIncDestinationtype() { return ms_IncDestinationtype;}
    ABL_String mb_getOutDestinationtype() { return ms_OutDestinationtype;}
	ABL_String mb_getServiceType() { return ms_ServiceType;}
    ABL_String mb_getDataTypeIndicator() { return ms_DataTypeIndicator;}
	ABL_String mb_getbasic_service() { return ms_basic_service;}
	//added as per LTE usage
	ABL_String mb_getIncTrafficType() { return ms_IncTrafficType;}
	ABL_String mb_getOutTrafficType() { return ms_OutTrafficType;}
	//modification end


protected:	
	ABL_Date        md_Valid_From ;
    ABL_Date        md_Valid_To ;
    ABL_Date        md_test_Start_Date ;
    ABL_Date        md_test_end_date;

    ABL_String      ms_ServiceCode;
	ABL_String      ms_OperatorCode;
    ABL_String      ms_IncRateDirection;
	ABL_String      ms_OutRateDirection;
	ABL_String      ms_IncDefaultratezone;
    ABL_String      ms_OutDefaultratezone;
    ABL_String      ms_IncRateIntrConnect;
	ABL_String      ms_OutRateIntrConnect;
    ABL_String      ms_IncPaymentDirection;
	ABL_String      ms_OutPaymentDirection;
    ABL_String      ms_IncUnit;
    int             mn_IncQtyUnit;
    ABL_String      ms_OutUnit;
    int             mn_OutQtyUnit;
	ABL_String      ms_IncDestinationtype;
    ABL_String      ms_OutDestinationtype;     
    ABL_String      ms_ServiceType;
    ABL_String      ms_DataTypeIndicator;
    ABL_String      ms_basic_service;
	//added as per LTE usage for 4.3 release
	ABL_String ms_IncTrafficType;
	ABL_String ms_OutTrafficType;
	//modification end
};

extern "C" {EXPORT Base_Registry* gb_getPM_ValidServicesCache();}

#endif
