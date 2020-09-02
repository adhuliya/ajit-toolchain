#!/usr/bin/env python
#
# partitionHierarchicalModel.py is a top-level script which 
# searches for .hsys info in  a list of directories and 
# partitions the model into two .hsys files, one for HW, and
# one for SW.
#
# Borrows lots from IMAGE RC.
#  (Thanks to Powai Labs).
#
# Brief Description:
#   The script walks the directory tree starting from the
#   working-directory = ./, finds all .hsys files in the
#   tree, and partitions it based on the specified options.
#
#
# Author: Madhav Desai

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

# clean the work-area, remove all the stuff produced by the script.
def cleanWorkArea(work_area):

    execSysCmd("rm -rf " + work_area + "./objsw")
    execSysCmd("rm -f "  + work_area + "./lib")
    return 0

    
# set global variables used in this script from environment
# variables.
def setGlobals(ahir_release_path):


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

    

#
# Author: Madhav Desai 
#
# Brief Description:
#   The script walks the directory tree starting from the
#   root-directory and looks for .hsys info in that directory.
#   It then partitions the toplevel hsys file into two
#   partitions by keeping the instances specified by the
#   -i option into a HW partition and rest into a SW partition.
#
#
def printUsage():
    print ''' partitionHierarchicalModel.py 
               -h   help-message
               (-i <hw-instance-spec>)*
		aa-file-1 aa-file-2 .... aa-file-n
          '''
def main():

    ahir_release = os.environ.get('AHIR_RELEASE')
    if(ahir_release == None):
       logError (" environment variable AHIR_RELEASE is not defined." )
       return 1

    if len(sys.argv) < 2:
       printUsage()
       return 1
    arg_list = sys.argv[1:]

    hw_instances = []
    opts,args = getopt.getopt(arg_list,'hi:')
    for option, parameter in opts:
        if option ==  '-h':
           logInfo("help option selected.")
        elif option == '-i':
           logInfo("instance " + parameter + " to be in hardware")
           hw_instances.append(parameter)
 	else:
	   logError("unknown-option " + option)
	   return 1
	
    work_area = "./"
    global command_log_file
    command_log_file = open(work_area + "/executed_command_log.txt","a")


    # set all the global constants (include-paths, libraries etc. etc.)
    setGlobals(ahir_release)

    # 0 = success.
    ret_status  = 0

    # walk this directory.. note bottom up..
    hsys_list = []

    # as you walk, execute the makefiles that you
    # see.  This will produce aa2c directories 
    # and also hsys files.
    for root, dirs, files in os.walk(work_area, topdown=False):
        for fname in files:
           full_name = os.path.join(root, fname)

           rootfname, extn = os.path.splitext(fname)
           if(extn == ".hsys"):
              logInfo("found hsys file " + full_name)
              hsys_list.append(full_name)

   
    #
    # construct the hierarchical model from lower level constructs.
    #
    if(len(hsys_list) > 0):
        hiersysPartition_cmd = "hierSysPartition  " 
        for hw_inst_name in hw_instances:
            hiersysPartition_cmd += " -i " + hw_inst_name + " "
        for aa_file in args:
            hiersysPartition_cmd += aa_file + " " 
        for hsys_file in hsys_list:
            hiersysPartition_cmd += hsys_file + " " 
        hsysPartition_status = execSysCmd(hiersysPartition_cmd)
        if(hsysPartition_status):
            logError("hierSysPartition failed in " + root)
            return 1

    return ret_status


if __name__ == '__main__':
    ret_val = main()
    sys.exit(ret_val)
