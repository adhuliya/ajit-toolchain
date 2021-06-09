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

# logging.
def logCommand(sys_cmd):
    print  "Info: Executing:\n\t" +  sys_cmd

def logInfo(mesg):
    print "Info: " + mesg

def logError(mesg):
    print "Error: " + mesg

def logWarning(mesg):
    print "Warning: " + mesg



def Usage():
    print "arguments:  \n\
               (-h)?  print this message and exit.\n\
               -V vmap-file to be used after copying from flash to ram. \n\
               -B virtual memory map of boot program from flash.. \n\
               -M virtual memory map of program to be loaded.. \n\
	       -o output file (memory map of flash contents)."
    return 0
    
# -V vmap-file.
# -B boot mmap file.
# -M execute mmap file.
# -O output mmap file.
def parseOptions(opts):
    vmap_file = None
    boot_mmap_file = None
    program_mmap_file = None
    help_flag = 0

    for option, parameter in opts:
        if option == '-h':
           help_flag = 1
        if option == '-V':
           vmap_file = parameter
           logInfo("vmap-file  = " + parameter + ".")
        if option == '-B':
           boot_mmap_file = parameter
           logInfo("boot-mmap-file  = " + parameter + ".")
        if option == '-M':
           program_mmap_file = parameter
           logInfo("program-mmap-file  = " + parameter + ".")
        if option == '-O':
           program_mmap_file = parameter
           logInfo("output-file  = " + parameter + ".")

    return help_flag, vmap_file, boot_mmap_file, program_mmap_file
    
def main():
    ret_status = 0

    arg_list = sys.argv[1:]
    if(len(arg_list) < 1):
	print "\nERROR: no arguments!"
        Usage()
        return 1

    opts,args = getopt.getopt(arg_list,'hV:B:M:')
    help_flag, boot_mmap_file, program_mmap_file = parseOptions(opts)

    if(help_flag):
       Usage()
       return 1

    

if __name__ == '__main__':
    ret_val = main()
    sys.exit(ret_val)
