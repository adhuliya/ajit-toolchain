#!/usr/bin/env python
#
# readDDCfiles.py constructs a tcl source file.
#
# Borrows lots from buildGhdlSimulationModel.py.
#
# Brief Description:
#   The script walks the directory tree starting from the
#   working-directory = ./
#  
#   If a directory named dc_synthesis/ is encountered:
#      -it will add a file path ending dc_synthesis folder and a file whose name is folder name 
#	above the dc_synthesis folder with .ddc extension.
#
#   The ddc files are then added to a *.tcl file, which can
#   then be executed.
#
#
#
# Author: Ch V Kalyani
#
import os
import os.path
import shutil
import getopt
import sys
import glob
import commands
import threading 
import subprocess
import pdb
import time


# logging.
def logCommand(sys_cmd):
    print >> command_log_file, sys_cmd

def logInfo(mesg):
    print "Info: " + mesg

def logError(mesg):
    print "Error: " + mesg

def logWarning(mesg):
    print "Warning: " + mesg

def printDDCsrcFile(ddc_lib_file,  src_file_name):
    
     src_file = open(src_file_name,"w")

     for pp in ddc_lib_file:
     	vsim_cmd ="read_ddc "+ pp+".ddc"+"\n"
        print >> src_file, vsim_cmd

     
     src_file.close()
     return 0
    
def printUsage(app_name):
    print app_name + ''' 
     -o <output-src-file-name> 
               '''
def main():

    ahir_release = os.environ.get('AHIR_RELEASE')
    if(ahir_release == None):
       logError (" environment variable AHIR_RELEASE is not defined." )
       return 1

    if len(sys.argv) < 2:
       printUsage(sys.argv[0])
       return 1

    arg_list = sys.argv[1:]
   
    src_file = "top.tcl"
   
    opts,args = getopt.getopt(arg_list,'o:')
    app_name = ""
    
    for option, parameter in opts:
        if option ==  '-o':
           src_file = parameter
           logInfo("do-file = " + parameter + ".")
 	else:
	   logError("unknown-option " + option)
	   return 1
	
    work_area = "./"
    global command_log_file
    command_log_file = open(work_area + "/executed_command_log.txt","w")

    # 0 = success.
    ret_status  = 0

    # ddc lib-file pairs
    ddc_lib_file = []

 
    for root, dirs, files in os.walk(work_area, topdown=False, followlinks=True):
        for name in dirs:
           if(name == "dc_synthesis"):
	      beg, end=os.path.split(root)
              full_name = os.path.join(root, name)
	      full=os.path.join(full_name, end)
	      full_paths=os.path.abspath(full)
	      if (end and not end.isspace()):
              	ddc_lib_file.append(full_paths)
                 
    
   
    if(len(ddc_lib_file) > 0):
        ret_status = printDDCsrcFile(ddc_lib_file, src_file)
    else:
        logInfo("no .ddc files found.") 

    command_log_file.close()
    return ret_status

if __name__ == '__main__':
    ret_val = main()
    sys.exit(ret_val)
