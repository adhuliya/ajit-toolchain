#!/usr/bin/env python

# asmToSparc.py
#
# DESCRIPTION: 
#	  This script is a wrapper around compileToSparc.py.
#	  It takes a single assembly program file,
#	  assembles it,  links it with sparc_stdio library,
#	  and generates a memory map from the executable
#	  that can be read by the C model of the processor.
#	  The memory map and all intermediate files
#	  are created inside an ./output/ folder.
#
# USAGE: 
#	asmToSparc.py <name of asm file>
# AUTHOR :
#	Neha Karanjkar (5 April 2015)


import os,sys

#function to get directory that this script resides in
#get directory that this script resides in
#append this to system's path variable, because this script
#uses some other scripts located in the same folder.
def getScriptPath():
    return os.path.dirname(os.path.realpath(sys.argv[0]))

sys.path.append(getScriptPath())
import compileToSparc 



# input : name of asm file
# output : executable,memory map file and intermediate files
#generated inside ./output folder
def main():

    if(len(sys.argv) < 2):
	print "\nUSAGE: asmToSparc <name of assembly file> \n "
        return 1
	
    # get name of file
    input_file = sys.argv[1]

    if(not (os.access(input_file, os.F_OK))) :
    	print "\n ERROR : cannot open", input_file
	return 1
    
    #strip off extension
    input_name = os.path.splitext(input_file)[0]

    # call compileToSparc.py
    command = "compileToSparc.py "
    command += "-W ./output "
    command += "-E "+input_name+".elf "
    command += "-H "+input_name+"_hexdump.txt "
    command += "-V "+input_name+"_vardump.txt "
    command += "-M "+input_name+"_memmap.txt "
    command += "-O "+input_name+"_objdump.txt "
    command += "-s "+input_file 
    
    ret_status = compileToSparc.execSysCmd(command)
    return ret_status

if __name__ == '__main__':
    ret_val = main()
    sys.exit(ret_val)
