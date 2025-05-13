#!/usr/bin/env python
#
# generate_program_and_reset_scripts..py generates
#
# two tcl scripts
#   - to program and reset an FPGA prototype.
#   - to reset an FPGA prototype.
#  
# one ajit-debug-monitor script.
#
# when executed in vivado.
#
# Author: Madhav Desai
#
import os
import getopt
import sys
import glob
import subprocess
import pdb
import time

def execSysCmd(sys_cmd):
    logCommand(sys_cmd)
    ret_val = os.system(sys_cmd)
    return ret_val


# logging.
def logCommand(sys_cmd):
    #print(sys_cmd, file=command_log_file)
    print >> command_log_file, sys_cmd

def logInfo(mesg):
    print ("Info: " + mesg)

def logError(mesg):
    print ("Error: " + mesg)

def logWarning(mesg):
    print ("Warning: " + mesg)

# utility to make a directory or if exists, remove its contents.
def makeOrCleanDir(dest_dir):
    curr_path = os.getcwd()
    if(os.path.isdir(dest_dir) != 1):
        os.mkdir(dest_dir)
    else:
        execSysCmd("rm -rf " + curr_path + "/" + dest_dir + "/*")

def printUsage(app_name):
    print (app_name + ''' 
     -f <fpga-device-id>     (as labeled in vivado)
     -b <bit-file-name>      (full path)
     -p <probes-file-name>   (full path)
     -o <output-directory>   (relative path)
     -h    print-help-message-and-quit.
          '''
          )

def main():

    if len(sys.argv) < 8:
       printUsage(sys.argv[0])
       return 1

    arg_list = sys.argv[1:]

    output_directory = "./"
    opts,args = getopt.getopt(arg_list,'f:b:p:o:h')
    app_name = ""
    c_include_dirs = []
    cc_flags =  " "
    print_chip_with_io = True
    for option, parameter in opts:
        if option == '-f':
           fpga_device_id = parameter
           logInfo("fpga_device_id = " + parameter + ".")
        elif option ==  '-b':
           bit_file_name = parameter
           logInfo("bit_file_name = " + parameter + ".")
        elif option ==  '-p':
           probes_file_name = parameter
           logInfo("probes_file_name = " + parameter + ".")
        elif option ==  '-o':
           output_directory = parameter
           logInfo("output_directory = " + parameter + ".")
        elif option ==  '-h':
           printUsage(sys.argv[0])
           return 1
        else:
           logError("unknown-option " + option)
           return 1
	
    work_area = "./"
    global command_log_file
    command_log_file = open(work_area + "/executed_command_log.txt","w")

    program_tcl_file =  open(output_directory + "/program.tcl","w")
    reset_tcl_file  =  open(output_directory + "/reset.tcl","w")

    program_string =  "open_hw \n" + \
            "connect_hw_server\n" + \
            "open_hw_target\n" + \
            "current_hw_device [get_hw_devices " + fpga_device_id +  "]\n" + \
            "refresh_hw_device -update_hw_probes false [lindex [get_hw_devices " + fpga_device_id + "] 0]\n" +\
            "set_property PROBES.FILE {" + probes_file_name + "}  [get_hw_devices " + fpga_device_id + "]\n" + \
            "set_property FULL_PROBES.FILE {" + probes_file_name + "} [get_hw_devices " + fpga_device_id + "]\n" + \
            "set_property PROGRAM.FILE {" + bit_file_name + "}  [get_hw_devices " + fpga_device_id + "]\n" + \
            "program_hw_devices [get_hw_devices " + fpga_device_id +  "]\n" + \
            "refresh_hw_device [lindex [get_hw_devices " + fpga_device_id + "] 0]\n" + \
            "set_property OUTPUT_VALUE 1 [get_hw_probes reset_vio -of_objects [get_hw_vios -of_objects [get_hw_devices " +  fpga_device_id + "] -filter {CELL_NAME=~\"vio_inst\"}]]\n" + \
            "commit_hw_vio [get_hw_probes {reset_vio} -of_objects [get_hw_vios -of_objects [get_hw_devices " + fpga_device_id + "] -filter {CELL_NAME=~\"vio_inst\"}]]\n" + \
            "set_property OUTPUT_VALUE 0 [get_hw_probes reset_vio -of_objects [get_hw_vios -of_objects [get_hw_devices " + fpga_device_id + "] -filter {CELL_NAME=~\"vio_inst\"}]]\n" + \
            "commit_hw_vio [get_hw_probes {reset_vio} -of_objects [get_hw_vios -of_objects [get_hw_devices " + fpga_device_id + "] -filter {CELL_NAME=~\"vio_inst\"}]]\n"

    print >> program_tcl_file, program_string

    reset_string =  "open_hw\n" +  \
            "connect_hw_server\n" +  \
            "open_hw_target\n" +  \
            "current_hw_device [get_hw_devices " + fpga_device_id +  "]\n" +  \
            "refresh_hw_device -update_hw_probes false [lindex [get_hw_devices " + fpga_device_id  + "] 0]\n" + \
            "set_property PROBES.FILE {" + probes_file_name + "}  [get_hw_devices " + fpga_device_id + "]\n" +  \
            "refresh_hw_device [lindex [get_hw_devices " + fpga_device_id  + "] 0]\n" +  \
            "set_property OUTPUT_VALUE 1 [get_hw_probes reset_vio -of_objects [get_hw_vios -of_objects [get_hw_devices " +  fpga_device_id + "] -filter {CELL_NAME=~\"vio_inst\"}]]\n" +  \
            "commit_hw_vio [get_hw_probes {reset_vio} -of_objects [get_hw_vios -of_objects [get_hw_devices " + fpga_device_id  + "] -filter {CELL_NAME=~\"vio_inst\"}]]\n" +  \
            "set_property OUTPUT_VALUE 0 [get_hw_probes reset_vio -of_objects [get_hw_vios -of_objects [get_hw_devices " + fpga_device_id + "] -filter {CELL_NAME=~\"vio_inst\"}]]\n" +  \
            "commit_hw_vio [get_hw_probes {reset_vio} -of_objects [get_hw_vios -of_objects [get_hw_devices " + fpga_device_id + "] -filter {CELL_NAME=~\"vio_inst\"}]]\n"
    print >> reset_tcl_file, reset_string
    
    program_tcl_file.close()
    reset_tcl_file.close()
    command_log_file.close()

    return 0

if __name__ == '__main__':
    ret_val = main()
    sys.exit(ret_val)
