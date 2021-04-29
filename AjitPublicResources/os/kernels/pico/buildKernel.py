#!/usr/bin/env python
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
import popen2
import pdb
import time

# run system command.
def execSysCmd(sys_cmd):
    logCommand(sys_cmd)
    ret_val = os.system(sys_cmd)
    return ret_val

# clean the work-area, remove all the stuff produced by the script.
def cleanWorkArea(work_area):
    execSysCmd("rm -rf " + work_area + "/sparc-assembly/*")
    execSysCmd("rm -rf " + work_area + "/sparc-obj/*")
    return 0


def setGlobals(ajit_project_home):

    global AJIT_PROJECT_HOME
    AJIT_PROJECT_HOME = ajit_project_home

    global SPARC_CC
    SPARC_CC = "sparc-elf-gcc "

    global SPARC_CC_FLAGS 
    SPARC_CC_FLAGS =  " -O0 -S -Wall -m32 -mcpu=v8 -ffreestanding -nostdlib "


    global SPARC_AS
    SPARC_AS =  "sparc-elf-as "
    global SPARC_AS_FLAGS
    SPARC_AS_FLAGS = " -Av8 " 

# logging.
def logCommand(sys_cmd):
    print  "Info: Executing:\n\t" +  sys_cmd

def logInfo(mesg):
    print "Info: " + mesg

def logError(mesg):
    print "Error: " + mesg

def logWarning(mesg):
    print "Warning: " + mesg

    
def  compileFiles():
    include_string = " -I ./include "
        
    for sfile in os.listdir("./src"):
	name,extn = os.path.splitext(sfile)
        if(extn == ".c"):
           cc_command = SPARC_CC + " -c " + SPARC_CC_FLAGS  + " " + include_string + " ./src/" + sfile  + " -o " + "./sparc-assembly/" + name + ".s"
           ret_val = execSysCmd(cc_command)
           if(ret_val != 0):
              logError("in compiling file " + sfile)
	      return 1

           as_command = SPARC_AS + " " + SPARC_AS_FLAGS + "./sparc-assembly/" + name + ".s "  + " -o " + "./sparc-obj/" + name + ".o"
           ret_val = execSysCmd(as_command)
           if(ret_val != 0):
              logError("in assembling file " + sfile)
	      return 1
    return 0

def main():

    ajit_project_home = os.environ.get('AJIT_PROJECT_HOME')
    if(ajit_project_home == None):
       logError("environment variable AJIT_PROJECT_HOME is not defined." )
       return 1

    setGlobals(ajit_project_home)
    ret_status =  compileFiles()
    return ret_status


if __name__ == '__main__':
    ret_val = main()
    sys.exit(ret_val)
