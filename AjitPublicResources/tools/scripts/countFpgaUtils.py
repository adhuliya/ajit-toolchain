#!/usr/bin/env python
#
# countFpgaUtils.py searches for utilization info in .srp files.
#
# Borrows lots from IMAGE RC.
#  (Thanks to Powai Labs).
#
# Brief Description:
#   The script walks the directory tree starting from the
#   working-directory = ./ and searches for the strings
#   "Number of Slice Registers" and "Number of Slice LUTs"
#   in the .srp file.
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
    ret_val = os.system(sys_cmd)
    return ret_val

# clean the work-area, remove all the stuff produced by the script.
def cleanWorkArea(work_area):

    execSysCmd("rm -rf " + work_area + "./objsw")
    execSysCmd("rm -f "  + work_area + "./lib")
    return 0


def main():

    work_area = "./"
    output_file_name = work_area + "/gate_counts.txt"

    # 0 = success.
    ret_status  = 0

    # vhdl lib-file pairs
    vhdl_lib_file_pairs = []

    # look for srp files and search in them.
    for root, dirs, files in os.walk(work_area, topdown=False, followlinks=True):
	for name in dirs:
            if (name == "xst_synthesis"):
                full_name = os.path.join(root,name)
                for srp_file in os.listdir(full_name):
                    root, ext = os.path.splitext(srp_file) 
                    if(ext == ".srp"):
                        full_srp_path = os.path.join(full_name, srp_file)
                        msg = "Info: found srp file " + full_srp_path
                        echo_cmd = "echo \"" + msg + "\""
                        execSysCmd(echo_cmd)
                        sff_cmd = "grep \"Number of Slice Registers\" " + full_srp_path
                        execSysCmd(sff_cmd)
                        s_lut_cmd = "grep \"Number of Slice LUTs\" " + full_srp_path
                        execSysCmd(s_lut_cmd)

                 
    
   
    return ret_status

if __name__ == '__main__':
    ret_val = main()
    sys.exit(ret_val)
