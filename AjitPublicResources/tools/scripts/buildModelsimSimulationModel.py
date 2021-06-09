#!/usr/bin/env python
#
# buildModelsimSimulationModel.py constructs a vsim 
# do file.
#
# Borrows lots from buildGhdlSimulationModel.py.
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
#   The VHDL files are then added to a *.do file, which can
#   then be executed.
#
#
#
# Author: Piyush P. Soni
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

# VHDL -> simulation.
def printGhdlDoFile(vhdl_lib_file_pairs, tb_vhdl_file, do_file_name):
    
     do_file = open(do_file_name,"w")

     vsim_cmd = "set AHIR_RELEASE $::env(AHIR_RELEASE)" 
     print >> do_file, vsim_cmd

     vsim_cmd = "set AJIT_PROJECT_HOME $::env(AJIT_PROJECT_HOME)" 
     print >> do_file, vsim_cmd

     vsim_cmd = "setenv LD_LIBRARY_PATH $AJIT_PROJECT_HOME/processor/Aa/modelsim/lib \n" 
     print >> do_file, vsim_cmd

     vsim_cmd = "vlib ModelsimLink"
     print >> do_file, vsim_cmd

     vsim_cmd = "vmap ModelsimLink ModelsimLink"
     print >> do_file, vsim_cmd

     vsim_cmd = "vcom -work ModelsimLink " + AHIR_VHDL_LIB + "/ModelsimLink.vhdl \n"  
     print >> do_file, vsim_cmd

     vsim_cmd = "vlib aHiR_ieee_proposed"
     print >> do_file, vsim_cmd

     vsim_cmd = "vmap aHiR_ieee_proposed aHiR_ieee_proposed"
     print >> do_file, vsim_cmd

     vsim_cmd = "vcom -work aHiR_ieee_proposed " + AHIR_VHDL_LIB + "/aHiR_ieee_proposed.vhdl \n"  
     print >> do_file, vsim_cmd

     vsim_cmd = "vlib ahir"
     print >> do_file, vsim_cmd

     vsim_cmd = "vmap ahir ahir"
     print >> do_file, vsim_cmd

     vsim_cmd = "vcom -work ahir " + AHIR_VHDL_LIB + "/ahir.vhdl \n"  
     print >> do_file, vsim_cmd


     for ppair in vhdl_lib_file_pairs:
        vhdl_lib  = ppair[0]
        vhdl_file = ppair[1]

        vsim_cmd = "vlib " + vhdl_lib
        print >> do_file, vsim_cmd

        vsim_cmd = "vmap " + vhdl_lib + " " +  vhdl_lib
        print >> do_file, vsim_cmd

        vsim_cmd = "vcom -work " + vhdl_lib + " " + vhdl_file + "\n"
        print >> do_file, vsim_cmd

     tb_path, tb_file = os.path.split(tb_vhdl_file)
     tb_name, extn = os.path.splitext(tb_file)
     
     vsim_cmd = "vlib work"
     print >> do_file, vsim_cmd

     vsim_cmd = "vmap work work"
     print >> do_file, vsim_cmd

     vsim_cmd = "vcom -work work " + os.path.abspath(tb_vhdl_file) + "\n"
     print >> do_file, vsim_cmd

     vsim_cmd = "vsim -novopt -t ps -foreign \"initForeign libFli.so\" work." + tb_name + "\n"
     print >> do_file, vsim_cmd

     vsim_cmd = "#Ignore integer warnings at time 0 \n"
     print >> do_file, vsim_cmd

     vsim_cmd = "set StdArithNoWarnings 1 \n"
     print >> do_file, vsim_cmd

     vsim_cmd = "run 100ns \n"
     print >> do_file, vsim_cmd

     vsim_cmd = "set StdArithNoWarnings 0 \n"
     print >> do_file, vsim_cmd

     vsim_cmd = "# comment following line to run for 100 ns \n"
     print >> do_file, vsim_cmd

     vsim_cmd = "run -all \n"
     print >> do_file, vsim_cmd

     do_file.close()
     return 0
    
def printUsage(app_name):
    print app_name + ''' 
     -o <output-do-file-name> 
     -t (testbench-file)
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
    hiersys2c_flag = False
    compile_aa2c_files = False
    make_flag = False
    clean_flag = False

    do_file = "ghdl.do"
    tb_vhdl_file = None
    opts,args = getopt.getopt(arg_list,'t:o:')
    app_name = ""
    c_include_dirs = []
    cc_flags =  " "
    for option, parameter in opts:
        if option ==  '-t':
 	   tb_vhdl_file = parameter
           logInfo("testbench-file  = " + parameter + ".")
        elif option ==  '-o':
           do_file = parameter
           logInfo("do-file = " + parameter + ".")
 	else:
	   logError("unknown-option " + option)
	   return 1
	
    work_area = "./"
    global command_log_file
    command_log_file = open(work_area + "/executed_command_log.txt","w")

    # set all the global constants (include-paths, libraries etc. etc.)
    setGlobals(ahir_release)

    # 0 = success.
    ret_status  = 0

    # vhdl lib-file pairs
    vhdl_lib_file_pairs = []

    # as you walk, execute the makefiles that you
    # see.  This will produce aa2c directories 
    # and also hsys files.
    for root, dirs, files in os.walk(work_area, topdown=False, followlinks=True):
	#print root
	#print dirs
	#print files
        for name in dirs:
           if(name == "vhdl"):
              full_name = os.path.join(root, name)
              for vhdl_lib in os.listdir(full_name):
                  vhdl_lib_dir = os.path.join(full_name, vhdl_lib)
                  if(os.path.isdir(vhdl_lib_dir)):
                     for vhdl_file in os.listdir(vhdl_lib_dir):
                        root, ext = os.path.splitext(vhdl_file) 
                        if((ext == ".vhdl") and (not "_test_bench" in root)):
                            logInfo("added library,file pair " + vhdl_lib_dir + ", " + vhdl_file) 
                            full_vhdl_file_path = os.path.join(vhdl_lib_dir, vhdl_file)
                            ppair = (vhdl_lib, os.path.abspath(full_vhdl_file_path))
                            vhdl_lib_file_pairs.append(ppair)
                 
    
   
    if(len(vhdl_lib_file_pairs) > 0):
        ret_status = printGhdlDoFile(vhdl_lib_file_pairs, tb_vhdl_file, do_file)
    else:
        logInfo("no VHDL files found.") 

    command_log_file.close()
    return ret_status

if __name__ == '__main__':
    ret_val = main()
    sys.exit(ret_val)
