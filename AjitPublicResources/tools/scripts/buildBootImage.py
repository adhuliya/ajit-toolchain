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

# run system command.
def execSysCmd(sys_cmd):
    logCommand(sys_cmd)
    ret_val = os.system(sys_cmd)
    return ret_val

def printUsage(app_name):
    print app_name + ''' 
     -m <mmap-file>
     -a <start-address in hex-format>
     -s <size-of-image in hex-format> 
     -b <log-of-boot-bin-file in decimal-format> '''

def main():

    global command_log_file
    command_log_file = open("executed_command_log.txt","a")

    ahir_release = os.environ.get('AHIR_RELEASE')
    if(ahir_release == None):
       logError (" environment variable AHIR_RELEASE is not defined." )
       return 1
    ajit_project_home = os.environ.get('AJIT_PROJECT_HOME')
    if(ajit_project_home == None):
       logError (" environment variable AJIT_PROJECT_HOME is not defined." )
       return 1
    ajit_flash_image_dir = ajit_project_home + "/tools/flash_image"

    if len(sys.argv) < 2:
       printUsage(sys.argv[0])
       return 1

    arg_list = sys.argv[1:]
    mmap_file = None
    start_addr = 0
    size_of_image = 0
    log_boot_bin_size = 20

    opts,args = getopt.getopt(arg_list,'m:a:s:b:')
    for option, parameter in opts:
        if option ==  '-m':
 	   mmap_file = parameter
           logInfo("Memory map file = " + parameter + ".")
        elif option ==  '-a':
           start_addr = int(parameter, 16)
           logInfo("start-address in image = " + hex(start_addr))
        elif option ==  '-s':
           size_of_image = int(parameter, 16)
           logInfo("size of image = " + hex(size_of_image))
        elif option ==  '-b':
           log_boot_bin_size = int(parameter)
           logInfo("log-of-bin-file-size= " + hex(log_boot_bin_size))
 	else:
	   logError("unknown-option " + option)
	   return 1
	
    # 0 = success.
    ret_status  = 0

    mmap_to_assy_cmd = ajit_flash_image_dir + "/bin/mmapToAssyU64 " + mmap_file + " __copy_asm.s " + hex(start_addr) + " " + hex(size_of_image)
    mmap_status = execSysCmd (mmap_to_assy_cmd)
    if mmap_status:
       logError("Error in mmapToAssyU64")
       return

    make_linker_script_cmd = ajit_project_home + "/tools/linker/makeLinkerScript.py -t 0x0 -d 0x10000 -o .bootstrapLinkerScript.lnk "
    execSysCmd(make_linker_script_cmd)

    compile_bootstrap_cmd = ajit_project_home + "/tools/scripts/compileToSparcUclibc.py  "
    compile_bootstrap_cmd += " -N bootstrap -s " + ajit_flash_image_dir + "/asm/bootstrap_u64.s "
    compile_bootstrap_cmd += " -s __copy_asm.s -L .bootstrapLinkerScript.lnk "
    boots_status = execSysCmd(compile_bootstrap_cmd)

    bin_cmd = ajit_flash_image_dir + "/bin/mmapToBin " + hex(log_boot_bin_size) +  " bootstrap.mmap bootstrap.bin"
    return ret_status

if __name__ == '__main__':
    ret_val = main()
    sys.exit(ret_val)
