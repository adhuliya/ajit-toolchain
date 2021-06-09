#!/usr/bin/env python 
#
# buildHierarchicalModel.py is a top-level script which 
# searches for useful info in  a list of directories and builds a C
# model.
#
# Borrows lots from IMAGE RC.
#  (Thanks to Powai Labs).
#
# Brief Description:
#   The script walks the directory tree starting from the
#   working-directory = ./, and collects all *.hsys file
#   
#   It then creates a components package for the specified
#   libraries by using hierSysGenVhdlComp... from AHIR
#
#
# Author: Madhav Desai
# 
from __future__ import division, print_function

import os
import os.path
import shutil
import getopt
import sys
import glob
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
    print (sys_cmd, file=command_log_file)

def logInfo(mesg):
    print ("Info: " + mesg, file=sys.stderr)

def logError(mesg):
    print ("Error: " + mesg, file=sys.stderr)

def logWarning(mesg):
    print ("Warning: " + mesg, file=sys.stderr)

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
# Brief Description: (see above)
#
def printUsage():
    print ('''Usage: buildVhdlComponentsPackage.py  -l <lib-name> ''')


def main():

    #pdb.set_trace()

    ahir_release = os.environ.get('AHIR_RELEASE')
    if(ahir_release == None):
       logError (" environment variable AHIR_RELEASE is not defined." )
       return 1

    if len(sys.argv) < 2:
       printUsage()
       return 1

    arg_list = sys.argv[1:]

    vhdl_lib = None
    opts,args = getopt.getopt(arg_list,'l:')
    for option, parameter in opts:
        if option ==  '-l':
           vhdl_lib = parameter
           logInfo("vhdl-lib  = " + parameter + ".")
        else:
           logError("unknown-option " + option)
           return 1

    work_area = "./"

    global command_log_file
    command_log_file = open(work_area + "/executed_command_log.txt","a")


    if(vhdl_lib == None):
        logError("specify a vhdl lib.")
        printUsage()
        command_log_file.close()
        return 1

    # set all the global constants (include-paths, libraries etc. etc.)
    setGlobals(ahir_release)

    # 0 = success.
    ret_status  = 0

    # walk this directory.. note bottom up..
    hsys_list = []

    # as you walk, collect the hsys files that you see.
    for root, dirs, files in os.walk(work_area, topdown=False, followlinks=True):
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
        hiersys_cmd = "hierSysGenVhdlComponentsPackage -l " + vhdl_lib  + " "

        for hsys_file in hsys_list:
            hiersys_cmd += hsys_file + " " 

        hiersys_status = execSysCmd(hiersys_cmd)
        if(hiersys_status):
            logError("hierSyGenVhdlComponentsPackage failed. ")
            return 1
    else:
        logError("no hsys files found under ./")

    return ret_status

if __name__ == '__main__':
    ret_val = main()
    sys.exit(ret_val)
