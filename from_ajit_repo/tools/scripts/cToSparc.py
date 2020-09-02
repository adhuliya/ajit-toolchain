#!/usr/bin/env python

# cToSparc.py
#
# DESCRIPTION :
#	  This script is a wrapper around compileToSparc.py.
#	  It takes a single C program file,
#	  compiles it,  links it with sparc_stdio library,
#	  and generates a memory map from the executable
#	  that can be read by the C model of the processor.
#	  The memory map and all intermediate files
#	  are created inside an ./output/ folder.
#
# USAGE: 
#	 cToSparc.py <name of C file>
#
# AUTHOR :
#	Neha Karanjkar (5 April 2015)






#get directory that this script resides in
#append this to system's path variable, because this script
#uses some other scripts located in the same folder.
import os,sys
def getScriptPath():
    return os.path.dirname(os.path.realpath(sys.argv[0]))

sys.path.append(getScriptPath())
import compileToSparc 


# input : name of C file
# output : executable,memory map file and intermediate files
#generated inside ./output folder
def main():

    if(len(sys.argv) < 2):
	print "\nUSAGE: cToSparc.py <name of C file> \n"
        return 1
	
    # get name of file
    input_file = sys.argv[1]

    if(not (os.access(input_file, os.F_OK))) :
    	print "\n ERROR : cannot open", input_file
	return 1
    
    #strip off extension
    input_name = os.path.splitext(input_file)[0]
    
    #get location of pico kernel:
    ajit_project_home = os.environ.get('AJIT_PROJECT_HOME')
    if(ajit_project_home == None):
	print "\n ERROR : environment variable AJIT_PROJECT_HOME is not defined."
	return 1
	
    src_dir = ajit_project_home+"/os/kernels/pico/src"
    inc_dir1 = ajit_project_home+"/os/kernels/pico/include"
    inc_dir2 = ajit_project_home+"/processor/C/common/include"
	
    # call compileToSparc.py
    command = "compileToSparc.py "
    command += "-g -W ./output "
    command += "-E "+input_name+".elf "
    command += "-H "+input_name+"_hexdump.txt "
    command += "-V "+input_name+"_vardump.txt "
    command += "-M "+input_name+"_memmap.txt "
    command += "-O "+input_name+"_objdump.txt "
    command += "-c "+input_file+" " 
    command += "-I "+inc_dir1+" "
    command += "-I "+inc_dir2+" "
    command += "-C "+src_dir+" "
    
    ret_status = compileToSparc.execSysCmd(command)
    return ret_status


if __name__ == '__main__':
    ret_val = main()
    sys.exit(ret_val)
