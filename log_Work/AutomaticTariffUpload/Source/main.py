#############################################################################################################
#File name	: main.py
#Author		: Prabina Pradhan
#Date		: 07/04/2022
#Purpose	:
#############################################################################################################
# Pre defined Modules
import logging
from datetime import date
import os.path

# User defined file
import ReadExcelFile
import Utility

def main():
	## Get the log path and name from conf file
	## import logging
	## l_logFileName111 = Utility.getConfValueUsingLevel('bkp_downloadedPath','CONFIGPARSER')
	## print('AAA' ,l_logFileName111 )
	## l_logFileName222 = Utility.getConfValueUsingLevel('bkp_downloadedPath')
	## print('AAA 222' ,l_logFileName222 )
	
	l_LogPath = Utility.getConfValue('logPath')
	l_logFileName = Utility.getConfValue('logFileName')
	l_logFileExct = Utility.getConfValue('logFileNameExct')
	today = date.today()
	
	## For logging details
	if os.path.exists(l_LogPath) or os.path.isfile(l_LogPath):
		logging.basicConfig(filename=l_LogPath+l_logFileName+str(today)+l_logFileExct, format='%(asctime)s|%(name)s|%(filename)s|%(lineno)d|%(levelname)s| %(message)s', datefmt='%m/%d/%Y %I:%M:%S %p',level=logging.DEBUG)
	
	#logging.debug	 ('Example of debug message')
	#logging.info	 ('Example of info message')
	#logging.warning ('Example of warn message')
	#logging.error	 ('Example of error message')
	#logging.critical('Example of critical message')
	
	#signalPath=../signal/
	#signalFileName=PM_AutomaticTariffUpload_Converter_
	#signalFileNameExe=.lock
	
	l_signalPath = Utility.getConfValue('signalPath')
	l_signalFileName = Utility.getConfValue('signalFileName')
	l_signalFileNameExe = Utility.getConfValue('signalFileNameExe')
	today = date.today()
	lock_file = l_signalFileName + str(today) + l_signalFileNameExe
	if os.path.isfile(l_signalPath + lock_file):
		logging.error('This processes is already running check the input dir path or signal dir.')
		exit()
	else:
	
		logging.info ('---------Lock file created and started the ATC conversation.')
		with open(l_signalPath + lock_file, 'w') as file_open:
			pass
	
		##Actual Code
		print("Start of the program ******** .")
		logging.info('---------Started PM_AutomaticTariffUpload_Converter.---------')
		ReadExcelFile.readFiles()
		logging.info('---------End PM_AutomaticTariffUpload_Converter.---------')
		print("End of the program ******** .")
		
		logging.info ('---------Conversation processes completed and remove the luck file.')
		os.remove(l_signalPath + lock_file)
		

if __name__ == '__main__':

	# l_signalPath = Utility.getConfValue('signalPath')
	# l_signalFileName = Utility.getConfValue('signalFileName')
	# l_signalFileNameExe = Utility.getConfValue('signalFileNameExe')
	# today = date.today()
	# lock_file = l_signalFileName + str(today) + l_signalFileNameExe
	
	# if os.path.isfile(l_signalPath + lock_file):
		# logging.error('This processes is already running check the input dir path or signal dir.')
		# exit()
	# else:
		# pass
		
	main()

#############################################################################################################
		