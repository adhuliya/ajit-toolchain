#!/usr/bin/env python
#
# buildGhdlSimulationModel.py constructs a GHDL 
# simdo file.
#
# Borrows lots from IMAGE RC.
#  (Thanks to Powai Labs).
#
# Brief Description:
#   The script walks the directory tree starting from the
#   working-directory = ./
#  
#   If a directory named vhdl/ is encountered:
#      - it searches for all subdirectories in vhdl/
#        for each subdirectory (say foo) in vhdl, it
#        looks for vhdl files (extension .vhdl) and adds
#        to library "foo".
#        (if the vhdl files have name *_test_bench.vhdl, then
#         they are ignored).
#
#   The VHDL files are then added to a simdo.do file, which can
#   then be executed to produce a GHDL model.
#
#
#
# Author: Madhav Desai
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

# run system command.
def execSysCmd(sys_cmd):
    logCommand(sys_cmd)
    ret_val = os.system(sys_cmd)
    return ret_val
    
# set global variables used in this script from environment
# variables.
def setGlobals(ahir_release_path, ajit_project_home):


    global AJIT_PROJECT_HOME
    global AJIT_CUSTOM_VHDL_LIB

    global AHIR_RELEASE
    global FUNCTIONLIB
    global XILINX_UNISIM
    global XILINX_SIMPRIM
    global AHIR_PTHREAD_UTILS_INCLUDE
    global AHIR_FUNCTIONLIB

    # Two versions of pipes, for software version, we
    # use pipeHandler, for ghdl simulation we use SocketLib.
    global SOCKETLIB_INCLUDE
    global SOCKETLIB_LIB
    global PIPEHANDLER_INCLUDE
    global PIPEHANDLER_LIB
    global AHIR_FUNCTIONLIB_INCLUDE

    # VHDL libraries from AHIR distro.
    global AHIR_VHDL_LIB
    global AHIR_VHDL_VHPI_LIB

    # VHDL, Aa results
    global VHDL
    global AA


    # SW version.
    global SW_INCLUDES
    global SW_LIB_PATHS
    global SW_LIBS

    # HW version..
    global HW_INCLUDES
        
    # CLANG includes
    global CLANG_INCLUDES
    
    # HW testbench for GHDL sim.
    global TB_INCLUDES
    global TB_LIB_PATHS
    global TB_LIBS

    # GHDL libraries to be linked to.
    global GHDL_LIB_OPTS

    # Ajit related
    AJIT_PROJECT_HOME=ajit_project_home
    AJIT_CUSTOM_VHDL_LIB=AJIT_PROJECT_HOME + "/processor/vhdl/lib/AjitCustom.vhdl"
    # AHIR-related
    AHIR_RELEASE=ahir_release_path
    FUNCTIONLIB=AHIR_RELEASE + "/functionLibrary"
    XILINX_UNISIM=AHIR_RELEASE + "/vhdl"
    XILINX_SIMPRIM=AHIR_RELEASE + "/vhdl"
    SOCKETLIB_INCLUDE=AHIR_RELEASE + "/include"
    SOCKETLIB_LIB=AHIR_RELEASE + "/lib"
    PIPEHANDLER_INCLUDE=AHIR_RELEASE + "/include"
    PIPEHANDLER_LIB=AHIR_RELEASE + "/lib"
    AHIR_VHDL_LIB=AHIR_RELEASE + "/vhdl"
    AHIR_VHDL_VHPI_LIB=AHIR_RELEASE + "/vhdl"
    AHIR_PTHREAD_UTILS_INCLUDE=AHIR_RELEASE + "/include"
    AHIR_FUNCTIONLIB=AHIR_RELEASE + "/functionLibrary"
    AHIR_FUNCTIONLIB_INCLUDE=AHIR_FUNCTIONLIB + "/include"

    
    #GHDL_LIB_OPTS = "-Wl,-L" + SOCKETLIB_LIB + " -Wl,-L" + RC_LIB + " -Wl,-lVhpi" + " -Wl,-lrcApiWithoutPlx" + " -Wl,-lrt"


# logging.
def logCommand(sys_cmd):
    print >> command_log_file, sys_cmd

def logInfo(mesg):
    print "Info: " + mesg

def logError(mesg):
    print "Error: " + mesg

def logWarning(mesg):
    print "Warning: " + mesg

# utility to make a directory or if exists, remove its contents.
def makeOrCleanDir(dest_dir):
    curr_path = os.getcwd()
    if(os.path.isdir(dest_dir) != 1):
        os.mkdir(dest_dir)
    else:
        execSysCmd("rm -rf " + curr_path + "/" + dest_dir + "/*")

def printUsage(app_name):
    print app_name + ''' 
     -r <root-directory>  (to start search for VHDL files)
     -o <output-directory> (destination for VHDL files)
     [-l <vhdl-lib>] (optional: only VHDL files in library vhdl-lib will be copied.
     -s  (do-not-print chip-top file).
          '''
def main():

    ahir_release = os.environ.get('AHIR_RELEASE')
    if(ahir_release == None):
       logError (" environment variable AHIR_RELEASE is not defined." )
       return 1
    ajit_project_home = os.environ.get('AJIT_PROJECT_HOME')
    if(ajit_project_home == None):
       logError (" environment variable AJIT_PROJECT_HOME is not defined." )
       return 1

    if len(sys.argv) < 2:
       printUsage(sys.argv[0])
       return 1

    arg_list = sys.argv[1:]

    selected_vhdl_lib = None
    output_directory = "./"
    root_directory = "./"
    opts,args = getopt.getopt(arg_list,'r:o:sl:')
    app_name = ""
    c_include_dirs = []
    cc_flags =  " "
    print_chip_with_io = True
    for option, parameter in opts:
        if option == '-r':
           root_directory = parameter
           logInfo("root_directory = " + parameter + ".")
        elif option ==  '-o':
           output_directory = parameter
           logInfo("output_directory = " + parameter + ".")
        elif option ==  '-s':
           print_chip_with_io = False
           logInfo("turn off printing chip with io")
        elif option == '-l':
           selected_vhdl_lib = parameter
           logInfo("only files in library " + selected_vhdl_lib + " will be copied." )
 	else:
	   logError("unknown-option " + option)
	   return 1
	
    work_area = "./"
    global command_log_file
    command_log_file = open(work_area + "/executed_command_log.txt","w")

    # set all the global constants (include-paths, libraries etc. etc.)
    setGlobals(ahir_release, ajit_project_home)


    global vhdl_lib_file
    vhdl_lib_file =  open(output_directory + "/VHDL_LIB_DESCR.TXT","w")
    # 0 = success.
    ret_status  = 0

    if (selected_vhdl_lib == None):
       # first the libraries nned to be cleaned up and copied.
       aieee_cpy_cmd = "cp " + ahir_release + "/vhdl/aHiR_ieee_proposed.vhdl " + output_directory  + "/aHiR_ieee_proposed.vhdl"
       execSysCmd (aieee_cpy_cmd)

       sed_cmd = "sed_synopsys_sync_set_reset.sh " + ahir_release + "/vhdl/ahirForAsic.umc65.vhdl " + output_directory + "/ahirASIC.vhdl"
       execSysCmd (sed_cmd)

       sal_cpy_cmd = "cp " + ajit_project_home + "/processor/vhdl/lib/simpleUartLib.vhdl " + output_directory + "/simpleUartLib.vhdl"
       execSysCmd (sal_cpy_cmd)

       ac_cpy_cmd = "sed_synopsys_sync_set_reset.sh " + ajit_project_home + "/processor/vhdl/lib/AjitCustomForAsic.vhdl " + output_directory + "/AjitCustomForAsic.vhdl"
       execSysCmd (ac_cpy_cmd)
    


    # walk and copy.
    for root, dirs, files in os.walk(root_directory, topdown=False, followlinks=True):
        for name in dirs:
           if(name == "vhdl"):
              full_name = os.path.join(root, name)
              for vhdl_lib in os.listdir(full_name):
                  vhdl_lib_dir = os.path.join(full_name, vhdl_lib)
                  if(os.path.isdir(vhdl_lib_dir)):
                     for vhdl_file in os.listdir(vhdl_lib_dir):
                        root, ext = os.path.splitext(vhdl_file) 
                        if((ext == ".vhdl") and (not "_test_bench" in root)):
                            if ((selected_vhdl_lib == None) or (selected_vhdl_lib == vhdl_lib)):
                               full_vhdl_file_path = os.path.join(vhdl_lib_dir, vhdl_file)
                               cp_cmd = "cp " + full_vhdl_file_path + " " + output_directory + "/"
                               execSysCmd (cp_cmd)
                               # vhdl libraries. 
			       print >> vhdl_lib_file, vhdl_lib + "\t\t" + vhdl_file 
                 
    
    command_log_file.close()
    return ret_status

if __name__ == '__main__':
    ret_val = main()
    sys.exit(ret_val)
