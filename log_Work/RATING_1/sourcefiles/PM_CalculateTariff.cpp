#include "PM_CalculateTariff.h"

extern "C" {EXPORT 
Base_Registry* gb_getPM_CalculateTariff()
{
	return ( (Base_Registry*) new PM_CalculateTariff);
}
}

PM_CalculateTariff::PM_CalculateTariff()
{
	//
}

PM_CalculateTariff::~PM_CalculateTariff()
{
	//
}

PM_CalculateTariff::PM_CalculateTariff(const PM_CalculateTariff& p_copyObject)
{
	this->mo_ABLServicePtr				=	p_copyObject.mo_ABLServicePtr;
	this->mo_PMTariffCachePtr			=	(PM_Partner_TariffCache*)p_copyObject.mo_PMTariffCachePtr->mb_createCopy();
	this->mo_TariffCacheContainer		=	p_copyObject.mo_TariffCacheContainer;	
	this->mo_PMTariffSlabCachePtr		=	(PM_TariffSlabCache*)p_copyObject.mo_PMTariffSlabCachePtr->mb_createCopy();
	this->mo_TariffSlabCacheContainer	=	p_copyObject.mo_TariffSlabCacheContainer;
	this->ms_Stopsignalfile				=	p_copyObject.ms_Stopsignalfile;
	this->Rounding_fac_I                =   p_copyObject.Rounding_fac_I     ;
	this->Rounding_fac_R                =   p_copyObject.Rounding_fac_R     ;
}

Base_Registry* PM_CalculateTariff::mb_clone()
{
	return ( (Base_Registry*) new PM_CalculateTariff );
}

ABL_Process* PM_CalculateTariff::mb_createCopy()
{
	return ( new PM_CalculateTariff (*this));
}

bool PM_CalculateTariff::mb_initProcess(ABL_CacheManager* pABLCacheManagerPtr, ABL_AgentCommunicator *pABLAgentCommunicatorPtr, ABL_Service *pABLServicePtr)
{	
	try
	{
		pABLAgentCommunicatorPtr->mb_getParameter("STOP_FILE",ms_Stopsignalfile);
		mo_ABLServicePtr = pABLServicePtr;
		Rounding_fac_I=mo_ABLServicePtr->mb_getParameterValue("ROUNDING_FACTOR_I");
		Rounding_fac_R=mo_ABLServicePtr->mb_getParameterValue("ROUNDING_FACTOR_R");
	}
	catch(ABL_Exception &e)
	{
		*mo_ABLServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str());  
		return false;
	}
	catch(...)
	{
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str()); 	
		*mo_ABLServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}	
	return true;
}

bool PM_CalculateTariff::mb_getCache(ABL_CacheManager* pABLCacheManagerPtr)
{
	try
	{
		mo_PMTariffCachePtr				=	(PM_Partner_TariffCache*)mo_ABLServicePtr->mb_getObject("PM_Partner_TariffCache")->mb_clone();
		mo_PMTariffSlabCachePtr			=	(PM_TariffSlabCache*)mo_ABLServicePtr->mb_getObject("PM_TariffSlabCache")->mb_clone();
		mo_TariffCacheContainer			=	pABLCacheManagerPtr->mb_getCache("PM_Partner_TariffCache");
		mo_TariffSlabCacheContainer		=	pABLCacheManagerPtr->mb_getCache("PM_TariffSlabCache");
	}
	catch(ABL_Exception &e)
	{
		*mo_ABLServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str());  
		return false;
	}
	catch(...)
	{
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str()); 	
		*mo_ABLServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}	
	return true;
}

bool PM_CalculateTariff::mb_process(ABL_Job* &pABLJobPtr)
{
	PM_Job* lo_PMJobPtr = (PM_Job*)pABLJobPtr;	
	ABL_Statement	lo_ABLStatement;
	ABL_ResultSet	lo_ABLResultSet;

	ABL_String	lsql;
	ABL_String ls_PartialIndicator;
	double		ln_Charge;
	double		ln_TaxPercent;
	double      ln_RevenuePercent;
	double		ln_UnitsToRate;
	double		ln_RemainingUnits;
	double		ln_UnitInterval;
	

	ABL_String	ls_RejMesg ;
	bool lb_TariffRecordFound=false;
	bool lb_IsRecordFound=false;

	PM_Partner_TariffCache*     lo_PMTariffCachePtr;
	PM_TariffSlabCache*         lo_PMTariffSlabCachePtr;

	try
	{

                
		if ( lo_PMJobPtr->gs_FileStatus == "D" || lo_PMJobPtr->gs_FileStatus == "F" )
			{
				return true;
			}

		if (lo_PMJobPtr->ga_RatedCdrs.size()== 0) 
		{
			if (lo_PMJobPtr->gs_IsGPRSFile=="YES")
			{
				return true;
			}
                        else
			{
				*mo_ABLServicePtr << DEBUG <<"  No Cdrs found for tariff search for the file: " <<lo_PMJobPtr->gs_fileName<<Endl;	
				return true;          
			}
		}

		*mo_ABLServicePtr << DEBUG << "Start :" <<lo_PMJobPtr->gs_fileName <<" : "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;


		// if the array with events to rate is empty (ratedEventArr), then insert the rejected 
		// and dropped cdrs into database and finish rating for the agreement type
		ls_RejMesg  ="";

		if (mo_TariffCacheContainer->mb_size()==0)
		{
			rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
			*mo_ABLServicePtr << INFO << " There is no records in PM_TARIFF  Rating is  stopping...: "  << Endl;	
			ABL_String ls_command("touch ");
			ls_command +=ms_Stopsignalfile;
			system(ls_command.c_str()); 
			return false;
		}
		
		for (int i =0;i<lo_PMJobPtr->ga_RatedCdrs.size();i++)
		{
			try
			{
				if(lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus=="D" || lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus=="R")
				{
					continue;
				}

				lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeAmount=0.0;
				lb_IsRecordFound=false;
				lb_TariffRecordFound=false;
				if (lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection=="D" || lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection=="R" )
				{
					ls_RejMesg ="cannot find tariff for the partner =>" ;
					ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode	;

					ls_RejMesg +=" Tariff Plan Code => ";
					ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_TariffPlanCode;

					ls_RejMesg +=" Service =>  ";
					if(lo_PMJobPtr->ga_RatedCdrs[i].gs_DerivedServiceCode=="")
					{
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode ;
					}
					else
					{
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_DerivedServiceCode ;
					}
					
					ls_RejMesg +=" Rate Zone => ";
					ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationRateZone;
					ls_RejMesg +="Time Type => ";
					ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_TimeType ;
					ls_RejMesg +=" Call Direction => ";
					ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection ;
					ls_RejMesg +="Call Date => ";
					ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();
					
				}
				else if (lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection=="O" || lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection=="R" )
				{
					ls_RejMesg ="cannot find tariff for the partner =>" ;
					ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
					ls_RejMesg +=" Tariff Plan Code => ";
					ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_TariffPlanCode;
					ls_RejMesg +=" Service =>  ";
					if(lo_PMJobPtr->ga_RatedCdrs[i].gs_DerivedServiceCode=="")
					{
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode ;
					}
					else
					{
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_DerivedServiceCode ;
					}
					ls_RejMesg +=" Rate Zone => ";
					ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginRateZone;
					ls_RejMesg +="Time Type => ";
					ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_TimeType ;
					ls_RejMesg +=" Call Direction => ";
					ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection ;
					ls_RejMesg +="Call Date => ";
					ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();
							
				}
				else if (lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection=="B" )
                {
					
					ls_RejMesg ="cannot find tariff for the partner =>" ;
					ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartnerCode;
					ls_RejMesg +=" Tariff Plan Code => ";
					ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_TariffPlanCode;
					ls_RejMesg +=" Service =>  ";
                    ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode ;
					ls_RejMesg +=" Tier Id => ";
					ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_Tierid;
					ls_RejMesg +=" Time Type => ";
					ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_TimeType ;
					ls_RejMesg +=" Call Direction => ";
					ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection ;
					ls_RejMesg +=" Call Date => ";
					ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();
                }

				mo_PMTariffCachePtr->mb_setTariffPlanCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_TariffPlanCode);
				mo_PMTariffCachePtr->mb_setCallDirection(lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection);
				mo_PMTariffCachePtr->mb_setServiceCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode);

                if(lo_PMJobPtr->ga_RatedCdrs[i].gs_DerivedServiceCode=="")
				{
					mo_PMTariffCachePtr->mb_setServiceCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode);	
				}
				else
				{
					mo_PMTariffCachePtr->mb_setServiceCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_DerivedServiceCode);	
				}				
				
				if (lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection=="O")
				{
					mo_PMTariffCachePtr->mb_setRateZone(lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginRateZone);
					mo_PMTariffCachePtr->mb_setTier(" ");
				}
				else if(lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection=="D" || lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection=="R")
				{
					mo_PMTariffCachePtr->mb_setRateZone(lo_PMJobPtr->ga_RatedCdrs[i].gs_DestinationRateZone);
					mo_PMTariffCachePtr->mb_setTier(" ");
				}
				else if (lo_PMJobPtr->ga_RatedCdrs[i].gs_RateDirection=="B")
				{
					mo_PMTariffCachePtr->mb_setRateZone(" ");
                    mo_PMTariffCachePtr->mb_setTier(lo_PMJobPtr->ga_RatedCdrs[i].gs_Tierid);
				}
                 
                                if (lo_PMJobPtr->ga_RatedCdrs[i].gs_HolidayId=="")
                                {
                                        mo_PMTariffCachePtr->mb_setDayCode("ALL");  
                                }
                                else
                                {
                                       mo_PMTariffCachePtr->mb_setDayCode(lo_PMJobPtr->ga_RatedCdrs[i].gs_HolidayId);
                                }
				mo_PMTariffCachePtr->mb_setTimeType(lo_PMJobPtr->ga_RatedCdrs[i].gs_TimeType);
				mo_PMTariffCachePtr->mb_setValid_From(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
				mo_PMTariffCachePtr->mb_setValid_To(lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate);
				if(mo_TariffCacheContainer->mb_get((CBase*)mo_PMTariffCachePtr,(CBase*&)lo_PMTariffCachePtr))
				{		
					ln_TaxPercent=0;
					lo_PMJobPtr->ga_RatedCdrs[i].gn_TariffId = (unsigned int)lo_PMTariffCachePtr->mb_getTariffId ();
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ChargeType =lo_PMTariffCachePtr->mb_getChargeType ();
					lo_PMJobPtr->ga_RatedCdrs[i].gn_InitialFreeUnits = lo_PMTariffCachePtr->mb_getInitialFreeUnit();				
					lo_PMJobPtr->ga_RatedCdrs[i].gn_MinChargeableUnits = lo_PMTariffCachePtr->mb_getMinChargebleUnit();				
					lo_PMJobPtr->ga_RatedCdrs[i].gn_InitialFlatAmt = lo_PMTariffCachePtr->mb_getInitialFlatAmt();
					lo_PMJobPtr->ga_RatedCdrs[i].gn_MinAmt = lo_PMTariffCachePtr->mb_getMinAmount();
					lo_PMJobPtr->ga_RatedCdrs[i].gn_Unit_rate  = lo_PMTariffCachePtr->mb_getUnitRate();
					lo_PMJobPtr->ga_RatedCdrs[i].gn_unitQty = lo_PMTariffCachePtr->mb_getQtyPerUnit();
					lo_PMJobPtr->ga_RatedCdrs[i].gs_CurrencyCode = lo_PMTariffCachePtr->mb_getCurrencyCode();				
					lo_PMJobPtr->ga_RatedCdrs[i].gs_InvoiceEvent = lo_PMTariffCachePtr->mb_getInvoice();
					lo_PMJobPtr->ga_RatedCdrs[i].gs_CallTypeLevel3 = lo_PMTariffCachePtr->mb_getTariffType();
					ln_TaxPercent = lo_PMTariffCachePtr->mb_getTaxPercent();
					ln_RevenuePercent=0;
					ln_RevenuePercent = lo_PMTariffCachePtr->mb_getRevenueShare();

					ls_PartialIndicator="";
					ln_RemainingUnits =0;
					ln_UnitInterval=0;
					ln_Charge=(double)0;

					/* Get Tax Percentage on the tariff */
					ls_PartialIndicator=lo_PMJobPtr->ga_RatedCdrs[i].gs_PartialIndicator;
					if (lo_PMJobPtr->ga_RatedCdrs[i].gs_PartialIndicator =="")
					{
							ls_PartialIndicator="F";
					}
					

					//added as per LTE usage for 4.3 release
					if ( lo_PMJobPtr->ga_RatedCdrs[i].gs_RateUnit=="D")
					{
						lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeableUnits = lo_PMJobPtr->ga_RatedCdrs[i].gn_CallDuration;
						lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits = lo_PMJobPtr->ga_RatedCdrs[i].gn_CallDuration;
						if ( lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits <= 
						     lo_PMJobPtr->ga_RatedCdrs[i].gn_InitialFreeUnits &&ls_PartialIndicator == "F" )
						{
							lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits = 0;
						}
						else 
						{
							lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits = 
							lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits - lo_PMJobPtr->ga_RatedCdrs[i].gn_InitialFreeUnits; 
						}
						
						if( lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits <=
						    lo_PMJobPtr->ga_RatedCdrs[i].gn_MinChargeableUnits && ls_PartialIndicator == "F" )
						{
							lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits = lo_PMJobPtr->ga_RatedCdrs[i].gn_MinChargeableUnits;
						}

					}
					else if (lo_PMJobPtr->ga_RatedCdrs[i].gs_RateUnit=="X")
					{
						lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeableUnits = lo_PMJobPtr->ga_RatedCdrs[i].gn_DataVolume_inc + lo_PMJobPtr->ga_RatedCdrs[i].gn_DataVolume_out;
						 lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits = lo_PMJobPtr->ga_RatedCdrs[i].gn_DataVolume_inc + lo_PMJobPtr->ga_RatedCdrs[i].gn_DataVolume_out;
						 if ( lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeableUnits <= lo_PMJobPtr->ga_RatedCdrs[i].gn_MinChargeableUnits && ls_PartialIndicator == "F" )
						{
							lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeableUnits = 0;
						}
						if ( lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits <= lo_PMJobPtr->ga_RatedCdrs[i].gn_InitialFreeUnits && ls_PartialIndicator == "F" )
						{
							lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits = 0;
						}
						else
                                                {
                                                        lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits =
                                                        lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits - lo_PMJobPtr->ga_RatedCdrs[i].gn_InitialFreeUnits;
                                                }
                    //Comment By harish to keep up the Ghana logic of if chargeable unit less than min then chargeable unit is null
                                            /*   if( lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits <=
                                                    lo_PMJobPtr->ga_RatedCdrs[i].gn_MinChargeableUnits && ls_PartialIndicator == "F" )
                                                {
                                                        lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits = lo_PMJobPtr->ga_RatedCdrs[i].gn_MinChargeableUnits;
                                                } */
												
													if ( lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeableUnits <= lo_PMJobPtr->ga_RatedCdrs[i].gn_MinChargeableUnits && ls_PartialIndicator == "F" )
						                        {
							                     lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeableUnits = 0;
						                        }			

										
					}
					//modification end
					else if (lo_PMJobPtr->ga_RatedCdrs[i].gs_RateUnit=="E")
					{
						lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeableUnits = 1;
					//Added by Yogesh
						lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits = 1;
					}
					else
					{
						ls_RejMesg += " - Invalid Rate unit => ";
						ls_RejMesg +=	lo_PMJobPtr->ga_RatedCdrs[i].gs_RateUnit;
						throw ABL_Exception(-1,ls_RejMesg .c_str());
					}




					/*	Check for the Charge type if it is Flat/Slab/Incremental*/
					if ( lo_PMJobPtr->ga_RatedCdrs[i].gs_ChargeType == "F" ) //  per unit rate
					{
						if (lo_PMTariffCachePtr->mb_getRoundUnits()=="Y")// && lo_PMJobPtr->ls_PartialIndicator=="F" )
						{							
							lo_PMJobPtr->ga_RatedCdrs[i].gn_TotalUnits = ceil(lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits/lo_PMJobPtr->ga_RatedCdrs[i].gn_unitQty);
							lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits = (lo_PMJobPtr->ga_RatedCdrs[i].gn_TotalUnits * lo_PMJobPtr->ga_RatedCdrs[i].gn_unitQty);
						}
						else
						{

							lo_PMJobPtr->ga_RatedCdrs[i].gn_TotalUnits = fnRoundValue((double)lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits/lo_PMJobPtr->ga_RatedCdrs[i].gn_unitQty,5);
							//lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits = lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeableUnits;
						}				
						ln_Charge=(double)(lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits/lo_PMJobPtr->ga_RatedCdrs[i].gn_unitQty)* lo_PMJobPtr->ga_RatedCdrs[i].gn_Unit_rate;
					}
					else if ( lo_PMJobPtr->ga_RatedCdrs[i].gs_ChargeType == "S" )//-- slabs
					{
						ls_RejMesg ="Error fetching slabs for '||'Tariff Plan =>  ";
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_TariffPlanCode;
						ls_RejMesg +=" Service Code =>  ";
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode ;
						ls_RejMesg +="Origin Rate Zone => ";
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_OriginRateZone;
						ls_RejMesg +="Time Type => ";
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_TimeType ;
						ls_RejMesg +=" Call Direction => ";
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gs_CallDirection ;
						ls_RejMesg +="Call Date => ";
						ls_RejMesg +=lo_PMJobPtr->ga_RatedCdrs[i].gd_CallDate.mb_toString();
						
						mo_PMTariffSlabCachePtr->mb_setTariffId(lo_PMJobPtr->ga_RatedCdrs[i].gn_TariffId);
						mo_PMTariffSlabCachePtr->mb_setSlabFrom(lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits);
						mo_PMTariffSlabCachePtr->mb_setSlabTo(lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits);
						if(!(mo_TariffSlabCacheContainer->mb_get((CBase*)mo_PMTariffSlabCachePtr,(CBase*&)lo_PMTariffSlabCachePtr)))
						{
							throw ABL_Exception(-1,ls_RejMesg .c_str());
						} 
						if (lo_PMTariffCachePtr->mb_getRoundUnits()=="Y")
						{	
							lo_PMJobPtr->ga_RatedCdrs[i].gn_TotalUnits   = ceil((lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits)/lo_PMTariffSlabCachePtr->mb_getQtyPerUnit());
							lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits = (lo_PMJobPtr->ga_RatedCdrs[i].gn_TotalUnits * lo_PMTariffSlabCachePtr->mb_getQtyPerUnit());
						}
						else
						{	//Round the units upto 5 digits

							lo_PMJobPtr->ga_RatedCdrs[i].gn_TotalUnits=fnRoundValue((double)lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits/lo_PMTariffSlabCachePtr->mb_getQtyPerUnit(),5);
							//lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits = lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeableUnits;
						
						}
						ln_Charge=(double)(lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits/lo_PMTariffSlabCachePtr->mb_getQtyPerUnit())*lo_PMTariffSlabCachePtr->mb_getAmountPerUnit();
						//added as per LTE usage for 4.3 release
						lo_PMJobPtr->ga_RatedCdrs[i].gn_Unit_rate  = lo_PMTariffSlabCachePtr->mb_getAmountPerUnit();
						//modification end

					}
					else if (lo_PMJobPtr->ga_RatedCdrs[i].gs_ChargeType == "I" )// -- incremental
					{
						int     lcTierCount=0;
						double lcFirstUnitQty =0;
						int  fromSlab[1];
						int toSlab[1];
						int qtPerUnit[1];
						double amountPerUnit[1];
						ln_UnitsToRate=0;
						ls_RejMesg += " - Incremental Tariff not defined";
						lb_IsRecordFound =false;
						ln_RemainingUnits = lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits;
						//Set the charged units to zero for incremental tariff
						lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits=0;
						lsql="SELECT NVL(SLAB_FROM, 0),NVL(SLAB_TO, 999999),NVL(QTY_PER_UNIT, 0),NVL(AMOUNT_PER_UNIT,-1) ";
						lsql +=" FROM PM_TARIFF_SLAB  where (TARIFF_ID=:1) ORDER BY SLAB_FROM";
						lo_ABLStatement		=	lo_PMJobPtr->mb_getConnection()->mb_createStatement(lsql);
						lo_ABLStatement.mb_setInt(1,(int)lo_PMJobPtr->ga_RatedCdrs[i].gn_TariffId);	
						lcTierCount=0;
						try
						{
							lo_ABLResultSet = lo_ABLStatement.mb_executeQuery();
							lo_ABLResultSet.mb_setBulkCount(1);
							lo_ABLResultSet <<  fromSlab;
							lo_ABLResultSet << toSlab;
							lo_ABLResultSet << qtPerUnit;
							lo_ABLResultSet << amountPerUnit;								
							while(lo_ABLResultSet.mb_fetch())
							{
								lb_IsRecordFound =true;	
								if (ln_RemainingUnits <= 0 )
								{
									break;
								}

								lcTierCount=lcTierCount+1;
								if (lcTierCount==1)
								{
											
									lo_PMJobPtr->ga_RatedCdrs[i].gn_Unit_rate= amountPerUnit[0];											
									lcFirstUnitQty=qtPerUnit[0];
								}
								//if (lo_PMTariffCachePtr->mb_getRoundUnits()=="Y" && lcTierCount == 1 && lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits<=(toSlab[0] - fromSlab[0]+1) )
								/*if (lo_PMTariffCachePtr->mb_getRoundUnits()=="Y" && lcTierCount == 1 && ln_RemainingUnits <=(toSlab[0] - fromSlab[0]+1) )
								{
									ln_RemainingUnits =qtPerUnit[0];
								}

								ln_UnitInterval = (toSlab[0] - fromSlab[0]) + 1;*/

								//if ((toSlab[0] - fromSlab[0]+1)<=ln_RemainingUnits)
								if ((toSlab[0] - fromSlab[0]+1)<ln_RemainingUnits)
								{
									//ln_UnitsToRate = toSlab[0] - fromSlab[0]+1;
									ln_UnitsToRate = (toSlab[0] - fromSlab[0]+1)/qtPerUnit[0];
									//ln_RemainingUnits = ln_RemainingUnits - ln_UnitsToRate;
									ln_RemainingUnits = ln_RemainingUnits - (toSlab[0] - fromSlab[0]+1);
									// -- calculate rate
									lo_PMJobPtr->ga_RatedCdrs[i].gn_TotalUnits=lo_PMJobPtr->ga_RatedCdrs[i].gn_TotalUnits+ln_UnitsToRate;
									//ln_Charge=(double)(ln_Charge+(ln_UnitsToRate/qtPerUnit[0])*amountPerUnit[0]);
									ln_Charge=(double)(ln_Charge+(ln_UnitsToRate)*amountPerUnit[0]);
									//lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits=lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits+ln_UnitsToRate;
									lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits=lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits+ (toSlab[0]- fromSlab[0]+1);
								}
								else
								{
									if (lo_PMTariffCachePtr->mb_getRoundUnits()=="Y") //&& (lo_PMJobPtr->ls_PartialIndicator=="F" || lo_PMJobPtr->ls_PartialIndicator=="I"))
									{
										ln_UnitsToRate = ceil(ln_RemainingUnits/qtPerUnit[0]);
										lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits = lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits+(ln_UnitsToRate * qtPerUnit[0]);
										lo_PMJobPtr->ga_RatedCdrs[i].gn_TotalUnits = lo_PMJobPtr->ga_RatedCdrs[i].gn_TotalUnits +ln_UnitsToRate;
									}
									else
									{
										// Round the units to 5th decimal in case rounding is set to 'No' for units.
										ln_UnitsToRate = fnRoundValue((double)ln_RemainingUnits/qtPerUnit[0],5);
										lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits=lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits+ln_RemainingUnits;
										lo_PMJobPtr->ga_RatedCdrs[i].gn_TotalUnits =lo_PMJobPtr->ga_RatedCdrs[i].gn_TotalUnits +ln_UnitsToRate;
									}
									// If Amount per unit is not defined at slab level
									if (amountPerUnit[0]== -1)
									{
										ln_Charge = (double)(ln_Charge +((ln_UnitsToRate * lo_PMJobPtr->ga_RatedCdrs[i].gn_Unit_rate)/(lcFirstUnitQty/qtPerUnit[0])));
									}
									else
									{
										ln_Charge=(double)(ln_Charge + (ln_UnitsToRate * amountPerUnit[0]));
										
									}
									ln_RemainingUnits = ln_RemainingUnits - (ceil(ln_UnitsToRate)*qtPerUnit[0]);
									//ln_RemainingUnits = 0;
								/*	if (ln_RemainingUnits <= ln_UnitInterval )
									{
										break;	
									} */
								}//End else
								
							}//End While

							lo_ABLStatement.mb_closeResultSet(lo_ABLResultSet);
							lo_PMJobPtr->mb_getConnection()->mb_terminateStatement(lo_ABLStatement); 
							if (lb_IsRecordFound==false)
							{									
								ls_RejMesg += " -- Incremental Tariff not defined => ";  
								throw ABL_Exception(-1,ls_RejMesg .c_str());
							}

						 //added as per LTE usage for 4.3 release
                                                lo_PMJobPtr->ga_RatedCdrs[i].gn_Unit_rate  = 0;
                                                //modification end

						}//End Try
						catch(ABL_Exception &e)
						{
							rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
							*mo_ABLServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
							ABL_String l_command("touch ");
							l_command +=ms_Stopsignalfile;
							system(l_command.c_str());  
							return false;
						}
						catch(...)
						{
							rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
							ABL_String l_command("touch ");
							l_command +=ms_Stopsignalfile;
							system(l_command.c_str()); 	
							*mo_ABLServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
							return false;
						}
					}// End Incremental slab
					else
					{
						ls_RejMesg += " - Invalid Charge Type => ";
						ls_RejMesg += lo_PMJobPtr->ga_RatedCdrs[i].gs_ChargeType;
						throw ABL_Exception(-1,ls_RejMesg .c_str());
					}
					

					if (ls_PartialIndicator == "F")
					{
						ln_Charge = (double)(ln_Charge + lo_PMJobPtr->ga_RatedCdrs[i].gn_InitialFlatAmt);
					}

					if (lo_PMJobPtr->ga_RatedCdrs[i].gn_MinAmt > 0 && ln_Charge < lo_PMJobPtr->ga_RatedCdrs[i].gn_MinAmt &&  ls_PartialIndicator == "F") 
					{
						ln_Charge =(double) lo_PMJobPtr->ga_RatedCdrs[i].gn_MinAmt;
					}

					//if (lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeAmount < lo_PMJobPtr->ga_RatedCdrs[i].gn_MinAmt)
					//{
						//lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeAmount = lo_PMJobPtr->ga_RatedCdrs[i].gn_MinAmt;
					//}
  					
				//ln_Charge=(double)(lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargedUnits/lo_PMJobPtr->ga_RatedCdrs[i].gn_unitQty)* lo_PMJobPtr->ga_RatedCdrs[i].gn_Unit_rate;
					double ln_ChargeAmount=(double)(lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeAmount + (double)lo_PMJobPtr->ga_RatedCdrs[i].gn_MultFactor*ln_Charge);
					lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeAmount=0.00;
                                            
                    if (lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType == "R")                      
					
                    {				
				       if (Rounding_fac_R=="UP")
					{
                                          
                        double I_TEMP= ln_ChargeAmount;
                        ln_ChargeAmount =ceil( I_TEMP);
                                                                                          
					}

			         	else if(Rounding_fac_R=="DOWN")
					{
					    double Il_TEMP= ln_ChargeAmount;
			            ln_ChargeAmount =  floor(Il_TEMP);
                                    
					}
					else
					{
				        	ln_ChargeAmount=ln_ChargeAmount+0.5;
				            long long ln_TempChargeAmount=(long long)ln_ChargeAmount;
					    ln_ChargeAmount=0.0;
					    ln_ChargeAmount=(double)ln_TempChargeAmount;
					}
					}
					else
					{
                       if (Rounding_fac_I=="UP")
					{
                                          
                        double I_TEMP= ln_ChargeAmount;
                        ln_ChargeAmount =ceil( I_TEMP);
                                                                                          
					}

			         	else if(Rounding_fac_I=="DOWN")
					{
					    double Il_TEMP= ln_ChargeAmount;
			            ln_ChargeAmount =  floor(Il_TEMP);
                                    
					}
					else
					{
				        	ln_ChargeAmount=ln_ChargeAmount+0.5;
				            long long ln_TempChargeAmount=(long long)ln_ChargeAmount;
					    ln_ChargeAmount=0.0;
					    ln_ChargeAmount=(double)ln_TempChargeAmount;
					}
					}				
					
					
					lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeAmount=0.0;
					lo_PMJobPtr->ga_RatedCdrs[i].gn_ChargeAmount=ln_ChargeAmount;
                    



					//Calculate Tax Amount
					double ln_TaxAmount=(double)(ln_Charge * ln_TaxPercent/100);
					lo_PMJobPtr->ga_RatedCdrs[i].gn_TaxAmount=0.00;
					ln_TaxAmount=ln_TaxAmount*lo_PMJobPtr->ga_RatedCdrs[i].gn_MultFactor;
					
					if (lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType == "R")                      
				{
							 if (Rounding_fac_R=="UP")
					{
                        
						float T_Temp = ln_TaxAmount;
						ln_TaxAmount =  ceil(T_Temp);

					}
				else if(Rounding_fac_R=="DOWN")
					{

					float TT_TEMP= ln_TaxAmount;
				    ln_TaxAmount =  floor(TT_TEMP);
					
					}
					else
					{
						ln_TaxAmount=ln_TaxAmount+0.5;
						long long ln_TempTaxAmount=(long long)ln_TaxAmount;
					    ln_TaxAmount=0.0;
					    ln_TaxAmount=(double)ln_TempTaxAmount;
					}
				}
                    else					
				{
						 if (Rounding_fac_I=="UP")
					{
                        
						float T_Temp = ln_TaxAmount;
						ln_TaxAmount =  ceil(T_Temp);

					}
				else if(Rounding_fac_I=="DOWN")
					{

					float TT_TEMP= ln_TaxAmount;
				    ln_TaxAmount =  floor(TT_TEMP);
					
					}
					else
					{
						ln_TaxAmount=ln_TaxAmount+0.5;
						long long ln_TempTaxAmount=(long long)ln_TaxAmount;
					    ln_TaxAmount=0.0;
					    ln_TaxAmount=(double)ln_TempTaxAmount;
					}
                }						
						
					
						
			
					lo_PMJobPtr->ga_RatedCdrs[i].gn_TaxAmount = ln_TaxAmount;
                    
                   /*** Calculate Revenue share amount only for the agreement type of content ***************/

					if (lo_PMJobPtr->ga_RatedCdrs[i].gs_AgreementType=="V")
					{
                      lo_PMJobPtr->ga_RatedCdrs[i].gn_RevenueAmount =(double)(ln_ChargeAmount * ln_RevenuePercent/100);
					}

					

				}//End Tariff Found
				else
				{
					throw ABL_Exception(-1,ls_RejMesg .c_str());

				}

			}//End Try

			catch(ABL_Exception &e)
			{
				if (e.mb_getErrorCode()== -1)
				{

					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorCode="RATE-TARIFF-NF";
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorValue=lo_PMJobPtr->ga_RatedCdrs[i].gs_ServiceCode;
					lo_PMJobPtr->ga_RatedCdrs[i].gs_ErrorMessage=ls_RejMesg ; 
					lo_PMJobPtr->ga_RatedCdrs[i].gs_RDStatus="R";

				}//End If
				else
				{
					rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
					*mo_ABLServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
					ABL_String l_command("touch ");
					l_command +=ms_Stopsignalfile;
					system(l_command.c_str());  
					return false;
				}
			}//End Catch
			catch(...)
			{
				rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
				ABL_String l_command("touch ");
				l_command +=ms_Stopsignalfile;
				system(l_command.c_str()); 	
				*mo_ABLServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
				return false;
			}		
		}// End For Loop

	}//End Try	
	catch(ABL_Exception &e)
	{
		rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
		*mo_ABLServicePtr<<CRITICAL<<"Exception : "<<e.mb_getMessage()<<Endl;
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str());  		
	    return false;
	}	
	catch(...)
	{
		rename(lo_PMJobPtr->gs_SourceFilePath.c_str(),lo_PMJobPtr->gs_ErrorFile_Path.c_str());
		ABL_String l_command("touch ");
		l_command +=ms_Stopsignalfile;
		system(l_command.c_str()); 	
		*mo_ABLServicePtr<<CRITICAL<<"error no : "<<errno <<" error description: "<<strerror(errno) <<Endl;
		return false;
	}	

	*mo_ABLServicePtr<<DEBUG<<"End  :"<< lo_PMJobPtr->gs_fileName <<": "<<lo_PMJobPtr->ga_RatedCdrs.size()<< Endl;
	return true;
}// Function Close

bool PM_CalculateTariff::mb_stop()
{
	return true;
}

double PM_CalculateTariff ::fnRoundValue(double in_Value,int in_precesion_value)
{


		stringstream ss;
		ss<<fixed;
        ss<<setprecision(in_precesion_value)<<in_Value; // output the rounded number on the stream
        ss>> in_Value; 
		return in_Value;
	
}

long PM_CalculateTariff ::fn_Rev_Power(long Param1,long param2)
{

	 long lcParam1  = 0;
     long lcCount = 0;

	  lcParam1 = Param1;
     while (lcParam1 > 1)
	 {
        lcCount = lcCount + 1;
        lcParam1 = lcParam1/param2;
	 }

     return( lcCount);
}
