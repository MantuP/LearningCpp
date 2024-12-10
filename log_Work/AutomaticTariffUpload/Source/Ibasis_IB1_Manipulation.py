###############################################################################################
#File name	: Ibasis_IB1_Manipulation.py
#Author		: Prabina Pradhan
#Date		: 27/04/2022
#Purpose	: To convert Ibasis_IB1_ partner tariff sheet into TT WBS format.
#
#
###############################################################################################

from openpyxl import load_workbook
import logging
from datetime import datetime
import os.path
import pandas
import numpy as np

import UtilityForExcelFile
import Utility

def readAndManipulation(p_file,p_uploudPrefix,p_uploudExtension,p_readFilePath,p_errorFilePath,p_upoladededPath,p_bkp_downloadedPath,p_OutPutColumnsHeader,p_OutPutColumnsHeaderDelm):
	print("Call Ibasis_IB1_Manipulation.py.", p_file)
	logging.info("Called Ibasis_IB1_Manipulation.py for reading %s file and converting into TT WBS tariff upload formate.", p_file)
	
	l_One = 1
	l_loopVar = 0
	
	#Get the upload file name and upload path 
	l_filename = UtilityForExcelFile.getFileNameWithOutExtension(p_file)
	l_fileNameOnly = l_filename+p_uploudPrefix+p_uploudExtension	
	l_fullFileName = p_upoladededPath+l_filename+p_uploudPrefix+p_uploudExtension
	
	#getting the number of sheets and validation
	l_Rd_file_SheetCnt = UtilityForExcelFile.getTheSheetCount(p_readFilePath,p_file)
	l_NumberOfSheetInFileVal = Utility.getConfValueUsingLevel('l_NumberOfSheetInFile','IBASIS')
	#print(l_Rd_file_SheetCnt);print(l_NumberOfSheetInFileVal);
	if(l_Rd_file_SheetCnt < l_One or int(l_Rd_file_SheetCnt) != int(l_NumberOfSheetInFileVal)):
		logging.error("%s file have no sheet to read or less/more sheets.", p_file)
		Utility.fileMoveToErrorDir(p_readFilePath,p_errorFilePath,p_file,"Error, Value are mismatching.")
		return -1
	#print("After sheet number compare ",l_Rd_file_SheetCnt)
	
	#getting the number of sheets and col validation
	getTheSheetNames_list = UtilityForExcelFile.getTheSheetNames(p_readFilePath,p_file)
	l_ExcelFileNameList_Val = Utility.getConfValueUsingLevel('l_ExcelFileNameList','IBASIS')
	s1 = Utility.listToStringWithoutBracketsSinglequote(getTheSheetNames_list)
	s2 = l_ExcelFileNameList_Val
	#print ( s1 , " -> " , s2 ); print ( type(s1) , type(s2)); print ( s1 != s2 )
	if s1 != s2:
		logging.error("%s file have different sheet or sheet name mismatch is there please check it.", p_file)
		Utility.fileMoveToErrorDir(p_readFilePath,p_errorFilePath,p_file,"Error, Value are mismatching.")
		return -1
		
	#getting read file index using a particular sheet
	l_getCanarSheetName = Utility.getConfValueUsingLevel('l_SheetNameIndex','IBASIS')
	l_Rd_file_indexUsingShtName = UtilityForExcelFile.readExcelFileUsingShtIndex(p_readFilePath,p_file,l_getCanarSheetName)
	#print(l_getCanarSheetName);	print(l_Rd_file_indexUsingShtName)
	
	l_getCurrencyVal = Utility.getConfValueUsingLevel('l_CurrencyFromConf','IBASIS')
	#print(l_getCurrencyVal)
	
	#Get the reading start position
	l_getRadingStartPosRow = Utility.getConfValueUsingLevel('l_RadingStartPosRow','IBASIS')
	l_getRadingStartPosRow = int(l_getRadingStartPosRow) 
	#print(l_getRadingStartPosRow)
	
	l_getReadingEndPosRow = UtilityForExcelFile.getMaxRowFromSheet(l_Rd_file_indexUsingShtName)
	#print("MaxRow",l_getReadingEndPosRow)
	
	#Get the reading end position using search key words;
	#l_getSearchKeyWord = Utility.getConfValueUsingLevel('l_SearchKeyWordEndPos','IBASIS')
	#l_getSearchKeyWordGap = Utility.getConfValueUsingLevel('l_SearchKeyWordEndPosGap','IBASIS')
	#l_getSearchEndPosRow = UtilityForExcelFile.getIdUsingSearchValueInColumn(l_Rd_file_indexUsingShtName,l_getSearchKeyWord)
	#l_getReadingEndPosRow = int(l_getSearchEndPosRow[l_One]) - (int(l_getSearchKeyWordGap))
	#print(l_getSearchEndPosRow[l_One]); print(l_getReadingEndPosRow)

	# Get actual values in list
	l_DialCodePosVal = Utility.getConfValueUsingLevel('l_DialCodePos','IBASIS')
	l_DialCodePosList = UtilityForExcelFile.getExcelColumnValWithRange(l_Rd_file_indexUsingShtName,l_DialCodePosVal,int(l_getRadingStartPosRow),int(l_getReadingEndPosRow))
	#print(l_DialCodePosList); print(len(l_DialCodePosList))
	
	l_CheckFirstSepratorVal = Utility.getConfValueUsingLevel('l_CheckFirstSeprator','IBASIS')
	l_CheckSecondSepratorVal = Utility.getConfValueUsingLevel('l_CheckSecondSeprator','IBASIS')
	l_CheckFirstSepratorManualyVal = Utility.getConfValueUsingLevel('l_CheckFirstSepratorManualy','IBASIS')
	#print(l_CheckFirstSepratorVal); print(l_CheckSecondSepratorVal)
	
	if Utility.listToCheckSymbolPresentOrNotStr(l_DialCodePosList,l_CheckFirstSepratorVal) == l_One and l_CheckFirstSepratorManualyVal == l_One:
		l_loopVar = l_loopVar + l_One
		
	if Utility.listToCheckSymbolPresentOrNotStr(l_DialCodePosList,l_CheckSecondSepratorVal) == l_One:
		l_loopVar = l_loopVar + l_One
	#print(l_loopVar)
	
	l_EffectiveEndDateVal =  Utility.getConfValueUsingLevel('l_EffectiveEndDate','IBASIS')
	l_EffectiveEndDateValDate = UtilityForExcelFile.getConvertNumberToDateInDDMMYYYYHH24MISS(l_EffectiveEndDateVal)
	
	l_FetchColumnSequence1Val = Utility.getConfValueUsingLevel('l_FetchColumnSequence1','IBASIS')
	l_FetchColumnSequence2Val = Utility.getConfValueUsingLevel('l_FetchColumnSequence2','IBASIS')
	l_FetchColumnSequence3Val = Utility.getConfValueUsingLevel('l_FetchColumnSequence3','IBASIS')
	l_FetchColumnSequence4Val = Utility.getConfValueUsingLevel('l_FetchColumnSequence4','IBASIS')
	l_FetchColumnSequence5Val = Utility.getConfValueUsingLevel('l_FetchColumnSequence5','IBASIS')
	w_l = f"{l_FetchColumnSequence1Val},{l_FetchColumnSequence2Val},{l_FetchColumnSequence3Val},{l_FetchColumnSequence4Val},{l_FetchColumnSequence5Val}"  
	
	l_Rate_Zone_TypeSl				= Utility.getConfValueUsingLevel('Rate_Zone_Type')
	l_Traffic_TypeSl				= Utility.getConfValueUsingLevel('Traffic_Type')
	l_Number_TypeSl					= Utility.getConfValueUsingLevel('Number_Type')
	l_Zone_IDSl						= Utility.getConfValueUsingLevel('Zone_ID')
	l_CategorySl					= Utility.getConfValueUsingLevel('Category')
	l_Zone_CategorySl				= Utility.getConfValueUsingLevel('Zone_Category')
	l_Setup_ChargesSl				= Utility.getConfValueUsingLevel('Setup_Charges')
	l_Minimum_Chargeable_UnitsSl	= Utility.getConfValueUsingLevel('Minimum_Chargeable_Units')
	l_PulseSl						= Utility.getConfValueUsingLevel('Pulse')
	l_Unit_QtySl					= Utility.getConfValueUsingLevel('Unit_Qty')
	l_DirectionSl					= Utility.getConfValueUsingLevel('Direction')
	l_InvoiceSl						= Utility.getConfValueUsingLevel('Invoice')
	l_Round_UnitsSl					= Utility.getConfValueUsingLevel('Round_Units')
	l_Minimum_Chagreable_AmountSl	= Utility.getConfValueUsingLevel('Minimum_Chagreable_Amount')
	l_Tax_PercentSl					= Utility.getConfValueUsingLevel('Tax_Percent')
	l_Free_UnitsSl					= Utility.getConfValueUsingLevel('Free_Units')
	l_TierSl						= Utility.getConfValueUsingLevel('Tier')
	l_IDD_Unit_RateSl				= Utility.getConfValueUsingLevel('IDD_Unit_Rate')
	l_PtrnerNameSl					= str(Utility.getConfValueUsingLevel('l_PtrnerName','IBASIS'))
	l_destinationTypeSl				= str(Utility.getConfValueUsingLevel('destination_Type'))
	
	#print(l_PtrnerNameSl) 	print(w_l)
	
	# Read Excel Sheet and Updating into Data frame.
	excel_data_df = pandas.read_excel(p_readFilePath + p_file, sheet_name = int(l_getCanarSheetName), header = int(l_getRadingStartPosRow) - 2, index_col=None, usecols = w_l )

	excel_data_df.set_axis (['Destination_Description', 'Destination_Number', 'Start_Date', 'Unit_Rate','Rate_Change_Indicator'], axis = 1, inplace = True)
	excel_data_df.head()
	excel_data_df = excel_data_df.reindex(['Destination_Description','Destination_Number','Unit_Rate','Start_Date','Rate_Change_Indicator'], axis=1)
	excel_data_df.insert(5, 'End_Date', l_EffectiveEndDateValDate, True)
	excel_data_df.insert(6, 'Rate_Zone_Type', l_Rate_Zone_TypeSl, True)
	excel_data_df.insert(7, 'Traffic_Type', l_Traffic_TypeSl, True)
	excel_data_df.insert(8, 'Number_Type', l_Number_TypeSl, True)
	excel_data_df.insert(9, 'Zone_ID', l_Zone_IDSl, True)
	excel_data_df.insert(10, 'Category', l_CategorySl, True)
	excel_data_df.insert(11, 'Zone_Category', l_Zone_CategorySl, True)
	excel_data_df.insert(12, 'Setup_Charges', l_Setup_ChargesSl, True)
	excel_data_df.insert(13, 'Minimum_Chargeable_Units', l_Minimum_Chargeable_UnitsSl, True)
	excel_data_df.insert(14, 'Pulse', l_PulseSl, True)
	excel_data_df.insert(15, 'Unit_Qty', l_Unit_QtySl, True)
	excel_data_df.insert(16, 'Direction', l_DirectionSl, True)
	excel_data_df.insert(17, 'Currency_Code', l_getCurrencyVal, True)
	excel_data_df.insert(18, 'Invoice', l_InvoiceSl, True)
	excel_data_df.insert(19, 'Round_Units', l_Round_UnitsSl, True)
	excel_data_df.insert(20, 'Minimum_Chagreable_Amount', l_Minimum_Chagreable_AmountSl, True)
	excel_data_df.insert(21, 'Tax_Percent', l_Tax_PercentSl, True)
	excel_data_df.insert(22, 'Free_Units', l_Free_UnitsSl, True)
	excel_data_df.insert(23, 'Tier', l_TierSl, True)
	excel_data_df.insert(24, 'IDD_Unit_Rate', l_IDD_Unit_RateSl, True)
	excel_data_df.insert(25, 'File_name', l_fileNameOnly, True)
	excel_data_df.insert(26, 'Partner_Code', l_PtrnerNameSl, True)
	excel_data_df.insert(27, 'destination_type', l_destinationTypeSl, True)
	
	l_dropFromTailOfDataFreamVal	= str(Utility.getConfValueUsingLevel('l_dropFromTailOfDataFream','IBASIS'))
	#excel_data_df.drop(excel_data_df.tail(int(l_dropFromTailOfDataFreamVal)).index, inplace = True)	
	excel_data_df = excel_data_df.dropna(subset=['Destination_Number'])
	
	#date formate change for start date.
	excel_data_df['Start_Date'] = pandas.to_datetime(excel_data_df['Start_Date'])
	excel_data_df["Start_Date"]=excel_data_df["Start_Date"].dt.strftime('%Y-%m-%d')	
	#excel_data_df["Start_Date"]=excel_data_df["Start_Date"].dt.strftime('%m-%d-%Y')	
	
	excel_data_df.head(l_getReadingEndPosRow - (l_getRadingStartPosRow - 1)).to_csv(l_fullFileName, sep ='|', index = False ,header = True )
	#print(excel_data_df)
	
	l_PresentDifferSeparatorInUnitRateVal	= str(Utility.getConfValueUsingLevel('l_PresentDifferSeparatorInUnitRate','IBASIS'))
	if int(l_PresentDifferSeparatorInUnitRateVal) == l_One:
		l_PresentSeparatorInUnitRateVal	= str(Utility.getConfValueUsingLevel('l_PresentSeparatorInUnitRate','IBASIS'))
		excel_data_df["Unit_Rate"]=excel_data_df["Unit_Rate"].str.replace(l_PresentSeparatorInUnitRateVal,'.')	
		excel_data_df.head(l_getReadingEndPosRow - l_getRadingStartPosRow).to_csv(l_fullFileName, sep ='|', index = False ,header = True )		
		#print(excel_data_df)
	
	if l_loopVar == 1:
		excel_data_df["Destination_Number"]=excel_data_df["Destination_Number"].str.split(l_CheckFirstSepratorVal)
		#print(excel_data_df.explode("Destination_Number").reset_index(drop=True))
		excel_data_df.explode("Destination_Number").reset_index(drop=True).to_csv(l_fullFileName, sep ='|', index = False ,header = True )

	elif l_loopVar == 2:
		l_r = excel_data_df.Destination_Number.apply(Utility.parse_comma)
		l_new = np.concatenate(l_r.values)
		l_lens = l_r.str.len()
		#print(excel_data_df.loc[excel_data_df.index.repeat(l_lens)].assign( Destination_Number = l_new))
		excel_data_df.loc[excel_data_df.index.repeat(l_lens)].assign( Destination_Number = l_new).to_csv(l_fullFileName, sep ='|', index = False ,header = True )
		
	if os.path.exists(l_fullFileName) == True:
		Utility.fileMoveToBkpDownloadFormatDir(p_readFilePath,p_bkp_downloadedPath,p_file,"Successfully converted into TT WBS formate.")
		return 0
	else:
		Utility.fileMoveToErrorDir(p_readFilePath,p_errorFilePath,p_file,"Error, While converting the excel sheets.")
		return -1
		
	return 0