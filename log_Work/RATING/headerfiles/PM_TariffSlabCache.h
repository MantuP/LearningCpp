#ifndef PM_TariffSlabCache_H
#define PM_TariffSlabCache_H

#include "ABL_DataCache.h"
#include "ABL_String.h"
#include "Base_Registry.h"

class PM_TariffSlabCache : public ABL_DataCache
{
public:
	PM_TariffSlabCache(double pn_TariffId = 0,double pn_SlabFrom = 0, double pn_SlabTo=0,double pn_QtyPerUnit=0,double pn_AmountPerUnit=0,double pn_TariffSlabSearchString=0) : mn_TariffId(pn_TariffId), mn_SlabFrom(pn_SlabFrom), mn_SlabTo(pn_SlabTo), mn_QtyPerUnit(pn_QtyPerUnit) , mn_AmountPerUnit(pn_AmountPerUnit), mn_TariffSlabSearchString(pn_TariffSlabSearchString) {}
	PM_TariffSlabCache(const PM_TariffSlabCache& pcopyObject);
	virtual ~PM_TariffSlabCache(){}
	virtual Base_Registry* mb_clone() { return ((Base_Registry*) new PM_TariffSlabCache()); }
	virtual long mb_getSize(ABL_Service *pABLServicePtr, ABL_String pfilterCaluse) { return 1; }
	bool mb_isEqual(CBase* pCBaseptr);
	unsigned int mb_hash();//{ return (unsigned int)mn_TariffId; }
	CBase* mb_createCopy();
	bool mb_loadData(data_container *pcontainer, ABL_Service *pABLServiceptr,ABL_String pfilterClause) ; 	
	void trim(ABL_String *ls_sIn) ;

	void mb_setTariffId(double pn_TariffId) { mn_TariffId = pn_TariffId; }
	void mb_setSlabFrom(double pn_SlabFrom) { mn_SlabFrom = pn_SlabFrom; }

	void mb_setSlabTo(double pn_SlabTo) { mn_SlabTo = pn_SlabTo; }

	void mb_setQtyPerUnit(double pn_QtyPerUnit) { mn_QtyPerUnit = pn_QtyPerUnit; }

	void mb_setAmountPerUnit(double pn_AmountPerUnit) { mn_AmountPerUnit = pn_AmountPerUnit; }
	void mb_setTariffSlabSearchString(double pn_TariffSlabSearchString) { mn_TariffSlabSearchString = pn_TariffSlabSearchString; }

	double mb_getTariffId() { return mn_TariffId; }
	double mb_getSlabFrom() { return mn_SlabFrom; }
	double mb_getSlabTo() { return mn_SlabTo; }
	double mb_getQtyPerUnit() { return mn_QtyPerUnit; }
	double mb_getAmountPerUnit() { return mn_AmountPerUnit; }
	double mb_getTariffSlabSearchString() { return mn_TariffSlabSearchString; }
protected:
	double mn_TariffId;
	double mn_SlabFrom;
	double mn_SlabTo;
	double mn_QtyPerUnit;
	double mn_AmountPerUnit;
	double mn_TariffSlabSearchString;
};

extern "C" {EXPORT Base_Registry* gb_getPM_TariffSlabCache();}

#endif
