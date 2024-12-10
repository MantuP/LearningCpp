###############################################################################################
#File name	: ReadExcelFile.py
#Author		: Prabina Pradhan
#Date		: 07/04/2022
#Purpose	:
# 1. Empty Excel sheet
# 2. rading the roes and columns of particular sheet
###############################################################################################
# Pre defined Modules
import logging
import os
import os.path

import Utility
import Orange_OR1_Manipulation
import Apelby_AP1_Manipulation
import Bharti_BH1_Manipulation
import Canar_CA1_Manipulation
import China_CH1_Manipulation
import Emira_EM1_Manipulation
import Etiuae_ET2_Manipulation
import Ibasis_IB1_Manipulation
import Idtglo_ID1_Manipulation
import Ipvoip_IP1_Manipulation
import Ittis_IT1_Manipulation
import Liquid_LI1_Manipulation
import Lycat_LY1_Manipulation
import Ote_OT1_Manipulation
import Pccw_PC1_Manipulation
import Telco_TE1_Manipulation
import Telias_TE4_Manipulation
import Telita_TE2_Manipulation
import Telnic_TE3_Manipulation
import Vasud_VA1_Manipulation

def readFiles():
	l_readFilePath   = Utility.getConfValue('downloadedPath')
	l_errorFilePath  = Utility.getConfValue('errorFilePath')
	l_upoladededPath = Utility.getConfValue('upoladededPath')
	l_bkp_downloadedPath = Utility.getConfValueUsingLevel('bkp_downloadedPath')
	
	if os.path.exists(l_readFilePath):
		logging.info("%s Path is exists.", l_readFilePath)
	else:
		logging.error("%s Path does not exists.", l_readFilePath)
	
	if os.path.exists(l_errorFilePath):
		logging.info("%s Path is exists.", l_errorFilePath)
	else:
		logging.error("%s Path does not exists.", l_errorFilePath)
	
	if os.path.exists(l_upoladededPath):
		logging.info("%s Path is exists.", l_upoladededPath)
	else:
		logging.error("%s Path does not exists.", l_upoladededPath)
		
	if os.path.exists(l_bkp_downloadedPath):
		logging.info("%s Path is exists.", l_bkp_downloadedPath)
	else:
		logging.error("%s Path does not exists.", l_bkp_downloadedPath)
	
	l_uploudPrefix = Utility.getConfValueUsingLevel('uploudPrefix')
	l_uploudExtension = Utility.getConfValueUsingLevel('uploudExtension')
	l_OutPutColumnsHeader = Utility.getConfValueUsingLevel('OutPutColumnsHeader')
	l_OutPutColumnsHeaderDelm = Utility.getConfValueUsingLevel('OutPutColumnsHeaderDelm')
		
	# Getting file prefix from the confg file
	l_FileNameOfThePtr_ORANGE = Utility.getConfValueUsingLevel('FileNameOfThePtr','ORANGE')
	#print(l_FileNameOfThePtr_ORANGE)
	l_FileNameOfThePtr_APELBY = Utility.getConfValueUsingLevel('FileNameOfThePtr','APELBY')
	l_FileNameOfThePtr_BHARTI = Utility.getConfValueUsingLevel('FileNameOfThePtr','BHARTI')
	l_FileNameOfThePtr_CANAR  = Utility.getConfValueUsingLevel('FileNameOfThePtr','CANAR')
	l_FileNameOfThePtr_CHINA  = Utility.getConfValueUsingLevel('FileNameOfThePtr','CHINA')
	l_FileNameOfThePtr_EMIRA  = Utility.getConfValueUsingLevel('FileNameOfThePtr','EMIRA')
	l_FileNameOfThePtr_ETIUAE = Utility.getConfValueUsingLevel('FileNameOfThePtr','ETIUAE')
	l_FileNameOfThePtr_IBASIS = Utility.getConfValueUsingLevel('FileNameOfThePtr','IBASIS')
	l_FileNameOfThePtr_IDTGLO = Utility.getConfValueUsingLevel('FileNameOfThePtr','IDTGLO')
	l_FileNameOfThePtr_IPVOIP = Utility.getConfValueUsingLevel('FileNameOfThePtr','IPVOIP')
	l_FileNameOfThePtr_LIQUID = Utility.getConfValueUsingLevel('FileNameOfThePtr','LIQUID')
	l_FileNameOfThePtr_LYCAT  = Utility.getConfValueUsingLevel('FileNameOfThePtr','LYCAT')
	l_FileNameOfThePtr_ITTIS  = Utility.getConfValueUsingLevel('FileNameOfThePtr','ITTIS')
	l_FileNameOfThePtr_OTE    = Utility.getConfValueUsingLevel('FileNameOfThePtr','OTE')
	l_FileNameOfThePtr_PCCW   = Utility.getConfValueUsingLevel('FileNameOfThePtr','PCCW')
	l_FileNameOfThePtr_TELCO  = Utility.getConfValueUsingLevel('FileNameOfThePtr','TELCO')
	l_FileNameOfThePtr_TELITA = Utility.getConfValueUsingLevel('FileNameOfThePtr','TELITA')
	l_FileNameOfThePtr_TELNIC = Utility.getConfValueUsingLevel('FileNameOfThePtr','TELNIC')
	l_FileNameOfThePtr_TELIAS = Utility.getConfValueUsingLevel('FileNameOfThePtr','TELIAS')
	l_FileNameOfThePtr_VASUD  = Utility.getConfValueUsingLevel('FileNameOfThePtr','VASUD')
	
	logging.info('Reading .xlsx files or .xls files and converting them into TT WBS Auto tariff upload formate.')
	
	os.chdir(l_readFilePath)
	for l_file1 in os.listdir():
		if l_file1.endswith(".xls"):
			Utility.Converting_xls_To_xlsx(l_readFilePath,l_bkp_downloadedPath,l_file1)
		
	# Change the directory
	os.chdir(l_readFilePath)
	for l_file in os.listdir():
		if l_file.endswith(".xlsx"):
			l_size = os.path.getsize(l_file)
			logging.info("The size of %s file is %d.", l_file , l_size)
			if(l_size == 0):
				Utility.fileMoveToErrorDir(l_readFilePath, l_errorFilePath, l_file, ", Error001 : Due to zero file size.")
			
			#Using substr file name get the different partner tariff sheet and manipulate. 
			
			#l_subStrFileName = l_file[0:11] #using char offset
			if "_" in l_file:
				l_file1 = l_file
				l_subStrFileName_x = l_file1.split("_")
				l_subStrFileName = l_subStrFileName_x[0] + "_" + l_subStrFileName_x[1] + "_"
				
				print("File name like :", l_subStrFileName)
				if(l_subStrFileName == l_FileNameOfThePtr_ORANGE  ):
					print("Call Orange_OR1_Manipulation.py ")
					Orange_OR1_Manipulation.readAndManipulation(l_file,l_uploudPrefix,l_uploudExtension,l_readFilePath,l_errorFilePath,l_upoladededPath,l_bkp_downloadedPath,l_OutPutColumnsHeader,l_OutPutColumnsHeaderDelm)
				elif(l_subStrFileName == l_FileNameOfThePtr_APELBY):
					Apelby_AP1_Manipulation.readAndManipulation(l_file,l_uploudPrefix,l_uploudExtension,l_readFilePath,l_errorFilePath,l_upoladededPath,l_bkp_downloadedPath,l_OutPutColumnsHeader,l_OutPutColumnsHeaderDelm)
				elif(l_subStrFileName == l_FileNameOfThePtr_BHARTI):
					Bharti_BH1_Manipulation.readAndManipulation(l_file,l_uploudPrefix,l_uploudExtension,l_readFilePath,l_errorFilePath,l_upoladededPath,l_bkp_downloadedPath,l_OutPutColumnsHeader,l_OutPutColumnsHeaderDelm)
				elif(l_subStrFileName == l_FileNameOfThePtr_CANAR ):
					Canar_CA1_Manipulation.readAndManipulation(l_file,l_uploudPrefix,l_uploudExtension,l_readFilePath,l_errorFilePath,l_upoladededPath,l_bkp_downloadedPath,l_OutPutColumnsHeader,l_OutPutColumnsHeaderDelm)
				elif(l_subStrFileName == l_FileNameOfThePtr_CHINA ):
					China_CH1_Manipulation.readAndManipulation(l_file,l_uploudPrefix,l_uploudExtension,l_readFilePath,l_errorFilePath,l_upoladededPath,l_bkp_downloadedPath,l_OutPutColumnsHeader,l_OutPutColumnsHeaderDelm)
				elif(l_subStrFileName == l_FileNameOfThePtr_EMIRA ):
					Emira_EM1_Manipulation.readAndManipulation(l_file,l_uploudPrefix,l_uploudExtension,l_readFilePath,l_errorFilePath,l_upoladededPath,l_bkp_downloadedPath,l_OutPutColumnsHeader,l_OutPutColumnsHeaderDelm)
				elif(l_subStrFileName == l_FileNameOfThePtr_ETIUAE):
					Etiuae_ET2_Manipulation.readAndManipulation(l_file,l_uploudPrefix,l_uploudExtension,l_readFilePath,l_errorFilePath,l_upoladededPath,l_bkp_downloadedPath,l_OutPutColumnsHeader,l_OutPutColumnsHeaderDelm)
				elif(l_subStrFileName == l_FileNameOfThePtr_IBASIS):
					Ibasis_IB1_Manipulation.readAndManipulation(l_file,l_uploudPrefix,l_uploudExtension,l_readFilePath,l_errorFilePath,l_upoladededPath,l_bkp_downloadedPath,l_OutPutColumnsHeader,l_OutPutColumnsHeaderDelm)
				elif(l_subStrFileName == l_FileNameOfThePtr_IDTGLO):
					Idtglo_ID1_Manipulation.readAndManipulation(l_file,l_uploudPrefix,l_uploudExtension,l_readFilePath,l_errorFilePath,l_upoladededPath,l_bkp_downloadedPath,l_OutPutColumnsHeader,l_OutPutColumnsHeaderDelm)
				elif(l_subStrFileName == l_FileNameOfThePtr_IPVOIP):
					Ipvoip_IP1_Manipulation.readAndManipulation(l_file,l_uploudPrefix,l_uploudExtension,l_readFilePath,l_errorFilePath,l_upoladededPath,l_bkp_downloadedPath,l_OutPutColumnsHeader,l_OutPutColumnsHeaderDelm)
				elif(l_subStrFileName == l_FileNameOfThePtr_LIQUID):
					Liquid_LI1_Manipulation.readAndManipulation(l_file,l_uploudPrefix,l_uploudExtension,l_readFilePath,l_errorFilePath,l_upoladededPath,l_bkp_downloadedPath,l_OutPutColumnsHeader,l_OutPutColumnsHeaderDelm)
				elif(l_subStrFileName == l_FileNameOfThePtr_LYCAT ):
					Lycat_LY1_Manipulation.readAndManipulation(l_file,l_uploudPrefix,l_uploudExtension,l_readFilePath,l_errorFilePath,l_upoladededPath,l_bkp_downloadedPath,l_OutPutColumnsHeader,l_OutPutColumnsHeaderDelm)
				elif(l_subStrFileName == l_FileNameOfThePtr_ITTIS ): 
					Ittis_IT1_Manipulation.readAndManipulation(l_file,l_uploudPrefix,l_uploudExtension,l_readFilePath,l_errorFilePath,l_upoladededPath,l_bkp_downloadedPath,l_OutPutColumnsHeader,l_OutPutColumnsHeaderDelm)
				elif(l_subStrFileName == l_FileNameOfThePtr_OTE   ):
					Ote_OT1_Manipulation.readAndManipulation(l_file,l_uploudPrefix,l_uploudExtension,l_readFilePath,l_errorFilePath,l_upoladededPath,l_bkp_downloadedPath,l_OutPutColumnsHeader,l_OutPutColumnsHeaderDelm)
				elif(l_subStrFileName == l_FileNameOfThePtr_PCCW  ):
					Pccw_PC1_Manipulation.readAndManipulation(l_file,l_uploudPrefix,l_uploudExtension,l_readFilePath,l_errorFilePath,l_upoladededPath,l_bkp_downloadedPath,l_OutPutColumnsHeader,l_OutPutColumnsHeaderDelm)
				elif(l_subStrFileName == l_FileNameOfThePtr_TELCO ):
					Telco_TE1_Manipulation.readAndManipulation(l_file,l_uploudPrefix,l_uploudExtension,l_readFilePath,l_errorFilePath,l_upoladededPath,l_bkp_downloadedPath,l_OutPutColumnsHeader,l_OutPutColumnsHeaderDelm)
				elif(l_subStrFileName == l_FileNameOfThePtr_TELITA):
					Telita_TE2_Manipulation.readAndManipulation(l_file,l_uploudPrefix,l_uploudExtension,l_readFilePath,l_errorFilePath,l_upoladededPath,l_bkp_downloadedPath,l_OutPutColumnsHeader,l_OutPutColumnsHeaderDelm)
				elif(l_subStrFileName == l_FileNameOfThePtr_TELNIC):
					Telnic_TE3_Manipulation.readAndManipulation(l_file,l_uploudPrefix,l_uploudExtension,l_readFilePath,l_errorFilePath,l_upoladededPath,l_bkp_downloadedPath,l_OutPutColumnsHeader,l_OutPutColumnsHeaderDelm)
				elif(l_subStrFileName == l_FileNameOfThePtr_TELIAS):
					Telias_TE4_Manipulation.readAndManipulation(l_file,l_uploudPrefix,l_uploudExtension,l_readFilePath,l_errorFilePath,l_upoladededPath,l_bkp_downloadedPath,l_OutPutColumnsHeader,l_OutPutColumnsHeaderDelm)
				elif(l_subStrFileName == l_FileNameOfThePtr_VASUD ):
					Vasud_VA1_Manipulation.readAndManipulation(l_file,l_uploudPrefix,l_uploudExtension,l_readFilePath,l_errorFilePath,l_upoladededPath,l_bkp_downloadedPath,l_OutPutColumnsHeader,l_OutPutColumnsHeaderDelm)
				#elif(l_subStrFileName == "Orange_OR9_"):
				#	print("Call Orange_OR9_Manipulation.py ")
				else:
					Utility.fileMoveToErrorDir(l_readFilePath, l_errorFilePath, l_file, ", Error002 : No operator specified for this excel sheet.")
			else:
				Utility.fileMoveToErrorDir(l_readFilePath, l_errorFilePath, l_file, ", Error005 : File name format mismatch.")
		else:
			Utility.fileMoveToErrorDir(l_readFilePath, l_errorFilePath, l_file, ", Error003 : Not a excel or CSV file.")
	#For end
#Function end readFiles()