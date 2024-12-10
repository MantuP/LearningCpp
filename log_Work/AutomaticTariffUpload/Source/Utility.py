###############################################################################################
# File name	: Utility.py
# Author		: Prabina Pradhan
# Date		: 08/04/2022
# Purpose	:
###############################################################################################
# Pre defined Modules
import logging
from configparser import ConfigParser
import os
import sys
import os.path
import shutil
import pyexcel as p
import UtilityForExcelFile
import numpy as np
import cx_Oracle
import datetime

# Added by Ashish Acharya
sys.path.insert(0, 'C:/ATU_PROD/ATU_Module_PROD/Partner_tariff_auto_upload/Global_conf')
import notification_email as ne
import db_config as dc
execution_date = datetime.date.today().strftime("%d/%m/%Y %I:%M:%S %p")


## Get value from conf file
## from configparser import ConfigParser
def getConfValue(p_str_1):
    """
    this function will get the value from config file.
    """
    config = ConfigParser(allow_no_value=True)
    # print(config.sections())
    # config.read('C:/Users/pradhpr/OneDrive - Tecnotree/Desktop/MyWBS/AssignedWork/9Mobile/!Drop_2_IMP/AutomaticTariffUpload/conf/PM_AutomaticTariffUpload_Converter.conf',encoding = 'utf8')
    config.read('C:/ATU_PROD/ATU_Module_PROD/Partner_tariff_auto_upload/TT_WBS_Format_Change/AutomaticTariffUpload/conf/PM_AutomaticTariffUpload_Converter.txt')
    # print(config.sections())
    # print(config['CONFIGPARSER']['logPath'])
    # print(config['CONFIGPARSER']['logFileName'])
    returnStr = config['CONFIGPARSER'][p_str_1]
    return returnStr


## Get value from conf file
## from configparser import ConfigParser using p_str_level_1
def getConfValueUsingLevel(p_str_1, p_str_level_1='CONFIGPARSER'):
    """
    this function will get the value from config file and second param is level.
    """
    config = ConfigParser(allow_no_value=True)
    # config.read('C:/Users/pradhpr/OneDrive - Tecnotree/Desktop/MyWBS/AssignedWork/9Mobile/!Drop_2_IMP/AutomaticTariffUpload/conf/PM_AutomaticTariffUpload_Converter.conf',encoding = 'utf8')
    config.read('C:/ATU_PROD/ATU_Module_PROD/Partner_tariff_auto_upload/TT_WBS_Format_Change/AutomaticTariffUpload/conf/PM_AutomaticTariffUpload_Converter.txt')
    returnStr = config[p_str_level_1][p_str_1]
    return returnStr


## Copy the file into error dir.
## import logging | import os |import os.path
def fileMoveToErrorDir(p_baseDir, p_destDir, p_strFilename, p_Msg):
    """
    this function will move the file into error dir.
    """
    # l_command = "move " + p_baseDir + p_strFilename + " " + p_destDir
    # os.system(l_command)
    # shutil.move( p_baseDir + p_strFilename, p_destDir)
    # Start :-- Added by Ashish
    aa_upload_prefix = getConfValue('uploudPrefix')
    aa_upload_extension = getConfValue('uploudExtension')
    split_attachment_name = os.path.splitext(p_strFilename)
    con_file_name = split_attachment_name[0] + aa_upload_prefix + aa_upload_extension

    dsn_tns = cx_Oracle.makedsn(dc.server, dc.port, service_name=dc.service_name)
    connection = cx_Oracle.connect(dc.username, dc.password, dsn_tns)
    cursor = connection.cursor()
    select_tab_pm_partner_email_attachment_dtls = "select systimestamp,a1.download_seq_no,a2.partner_name,a3.admin_email,a3.support_email from pm_partner_email_attachment_dtls a1,pm_partner a2,pm_partner_conf a3 where a1.partner_code=a2.partner_code and a2.partner_code=a3.partner_code and a1.tariff_sheet_after_download=:tariff_sheet_after_download"
    cursor.execute(select_tab_pm_partner_email_attachment_dtls, [p_strFilename])
    dwn_seq_no_date = cursor.fetchone()
    upt_tab_pm_partner_email_attachment_dtls = (
        "update pm_partner_email_attachment_dtls set status=:status where download_seq_no = :download_seq_no ")
    cursor.execute(upt_tab_pm_partner_email_attachment_dtls,
                   ['CE', dwn_seq_no_date[1]])
    cursor.close()
    connection.commit()
    connection.close()

    shutil.move(os.path.join(p_baseDir, p_strFilename), os.path.join(p_destDir, p_strFilename))
    ne.send_alert3('Automatic tariff upload progress status of partner ' + dwn_seq_no_date[0], email_id=str(dwn_seq_no_date[4]),
                   partner_name=dwn_seq_no_date[2], execution_date=execution_date, status='Failed',
                   failure_reasons="The tariff sheet conversion error. Process terminated.",action="The support team is checking this error. Will update you shortly.")
    # End :-- Added by Ashish
    logging.error("%s file moved into %s dir %s .", p_strFilename, p_destDir, p_Msg)


## Copy the file into error dir.
## import logging | import os |import os.path
def fileMoveToBkpDownloadFormatDir(p_baseDir, p_destDir, p_strFilename, p_Msg):
    """
    this function will move the file into error dir.
    """
    # l_command = "move " + p_baseDir + p_strFilename + " " + p_destDir
    # os.system(l_command)

    # Start :-- Added by Ashish
    aa_upload_prefix = getConfValue('uploudPrefix')
    aa_upload_extension = getConfValue('uploudExtension')
    split_attachment_name = os.path.splitext(p_strFilename)
    con_file_name = split_attachment_name[0] + aa_upload_prefix + aa_upload_extension

    dsn_tns = cx_Oracle.makedsn(dc.server, dc.port, service_name=dc.service_name)
    connection = cx_Oracle.connect(dc.username, dc.password, dsn_tns)
    cursor = connection.cursor()
    select_tab_pm_partner_email_attachment_dtls = "select systimestamp,download_seq_no from pm_partner_email_attachment_dtls where tariff_sheet_after_download=:tariff_sheet_after_download"
    cursor.execute(select_tab_pm_partner_email_attachment_dtls, [p_strFilename])
    dwn_seq_no_date = cursor.fetchone()
    # print(dwn_seq_no_date[0])
    # print(dwn_seq_no_date[1])
    upt_tab_pm_partner_email_attachment_dtls = (
        "update pm_partner_email_attachment_dtls set status=:status, conversion_date=:conversion_date,tariff_sheet_after_conversion=:tariff_sheet_after_conversion where download_seq_no = :download_seq_no ")
    cursor.execute(upt_tab_pm_partner_email_attachment_dtls,
                   ['CC', dwn_seq_no_date[0], con_file_name, dwn_seq_no_date[1]])
    cursor.close()
    connection.commit()
    connection.close()
    # End :-- Added by Ashish
    shutil.move(os.path.join(p_baseDir, p_strFilename), os.path.join(p_destDir, p_strFilename))
    logging.info("%s file moved into %s dir %s .", p_strFilename, p_destDir, p_Msg)


def Converting_xls_To_xlsx(p_readFilePath, p_destDir, p_filename):
    os.chdir(p_readFilePath)
    l_filename = UtilityForExcelFile.getFileNameWithOutExtension(p_filename)
    p.save_book_as(file_name=p_filename, dest_file_name=l_filename + '.xlsx')
    fileMoveToBkpDownloadFormatDir(p_readFilePath, p_destDir, p_filename, 'After Converting_xls_To_xlsx')


def listToStringWithoutBracketsSinglequote(list1):
    return str(list1).replace('[', '').replace(']', '').replace('\'', '')


def listToCheckSymbolPresentOrNot(l_list, l_symbol):
    for i in l_list:
        if l_symbol in i:
            return 1
    return 0


def listToCheckSymbolPresentOrNotStr(l_list, l_symbol):
    for i in str(l_list):
        if l_symbol in i:
            return 1
    return 0


def parse(o):
    mm = lambda i: slice(min(i), max(i) + 1)
    return np.r_.__getitem__(tuple(mm(list(map(int, s.strip().split('-')))) for s in str(o).split(';')))


def parse_comma(o):
    mm = lambda i: slice(min(i), max(i) + 1)
    return np.r_.__getitem__(tuple(mm(list(map(int, s.strip().split('-')))) for s in str(o).split(',')))


def ranger(mystr):
    return list(concat([int(i)] if '-' not in i else \
                           list(range(int(i.split('-')[0]), int(i.split('-')[-1]) + 1)) \
                       for i in mystr.split(';')))


# Remove end spaces
def remove_end_spaces(string):
    return "".join(string.rstrip())


# Remove first and  end spaces
def remove_first_end_spaces(string):
    return "".join(string.rstrip().lstrip())


# Remove all spaces
def remove_all_spaces(string):
    return "".join(string.split())


# Remove all extra spaces
def remove_all_extra_spaces(string):
    return " ".join(string.split())

#### XLSX TO CSV
##import openpyxl
##
##filename = 'appending.xlsx'
##
#### opening the xlsx file
##xlsx = openpyxl.load_workbook(filename)
##
#### opening the active sheet
##sheet = xlsx.active
##
#### getting the data from the sheet
##data = sheet.rows
##
#### creating a csv file
##csv = open("data.csv", "w+")
##
##for row in data:
##    l = list(row)
##    for i in range(len(l)):
##        if i == len(l) - 1:
##            csv.write(str(l[i].value))
##        else:
##            csv.write(str(l[i].value) + ',')
##        csv.write('/n')
##
#### close the csv file
##csv.close()
