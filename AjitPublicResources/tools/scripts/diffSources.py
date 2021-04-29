#!/usr/bin/env python
#
#
# goes down the tree, looks for all patches/diff.sh
# scripts and executes them.  This is a prelude
# to a git commit.
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
    print app_name
    print "  executes diff.sh scripts in the directory hierarchy starting from ./"

def main():

    printUsage(sys.argv[0])

    ajit_processor_root = os.environ.get('AJIT_PROCESSOR_ROOT')
    if(ajit_processor_root == None):
       logError (" environment variable AJIT_PROCESSOR_ROOT is not defined." )
       return 1


    arg_list = sys.argv[1:]

    output_directory = "./"
    root_directory = "./"

    work_area = "./"
    global command_log_file
    command_log_file = open(work_area + "/executed_command_log.txt","w")

    # 0 = success.
    ret_status  = 0

    # as you walk, execute the patches/patch.sh files that you encounter..
    for root, dirs, files in os.walk(root_directory, topdown=False, followlinks=True):
        for dir_name in dirs:
           if(dir_name == "patches"):
              full_name = os.path.join(root, dir_name)
              for script_file in os.listdir(full_name):
                 if(script_file == "diff.sh"):
                    cp_cmd = full_name + "/" + script_file + " " + full_name  
		    logInfo("executing " + cp_cmd)
                    execSysCmd(cp_cmd)
                 
    
    command_log_file.close()
    return ret_status

if __name__ == '__main__':
    ret_val = main()
    sys.exit(ret_val)
