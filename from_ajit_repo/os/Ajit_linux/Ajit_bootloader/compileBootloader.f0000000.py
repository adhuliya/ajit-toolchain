#!/usr/bin/env python

# compileBootloader.f0000000.py
#
# DESCRIPTION :
#    This script is a wrapper around compileToSparc.py.
#
#    It takes the bootloader code (.c file), 
#    the device tree blob (.S file), compiles the two,
#    links them to generate an executable (elf).
#
#    It then generates a memory map from the executable
#    that can be used to populate the memoy of the processor model.
#    The memory map and all intermediate files
#    are created inside an ./output/ folder.
#
# USAGE: 
#   compileBootloader.f0000000.py <name of C file> <name of the device-tree.S file>
#
# AUTHOR :
#  Neha Karanjkar 
#  (5 April 2015)
#  modified: 5 Dec 2016 : added dev tree blob to the bootloader
#
# MODIFIED by MPD (hacked) to produce a variant that maps bootloader to f0000000
#






#get directory that this script resides in
#append this to system's path variable, because this script
#uses some other scripts located in the same folder.
import os,sys
def getScriptPath():
    return os.path.dirname(os.path.realpath(sys.argv[0]))

sys.path.append(getScriptPath())

#add path of other scripts such as compileToSparc.py
ajit_project_home = os.environ.get('AJIT_PROJECT_HOME')
if(ajit_project_home == None):
  print ("ERROR : environment variable AJIT_PROJECT_HOME is not defined.")
  exit(1)
scripts_path=ajit_project_home+"/tools/scripts"
sys.path.append(scripts_path)
import compileToSparc 


import os,sys
def getScriptPath():
    return os.path.dirname(os.path.realpath(sys.argv[0]))

sys.path.append(getScriptPath())


# input : name of C file
# output : executable,memory map file and intermediate files
#generated inside ./output folder
def main():

    if(len(sys.argv) < 3):
      print ("\nUSAGE: compileBootloader.py <path to Bootloader (.c) file> <path to device-tree-file (.S)> \n")
      return 1
  
    # get name of file
    input_file     = sys.argv[1]
    dev_tree_file = sys.argv[2] 

    if(not (os.access(input_file, os.F_OK))) :
      print ("\n ERROR : cannot open", input_file)
      return 1
    if(not (os.access(dev_tree_file, os.F_OK))) :
      print ("\n ERROR : cannot open", dev_tree_file)
      return 1
    
    #strip off extension
    input_name = os.path.splitext(input_file)[0]
    
    #get location of pico kernel:
    ajit_project_home = os.environ.get('AJIT_PROJECT_HOME')
    if(ajit_project_home == None):
      print ("\n ERROR : environment variable AJIT_PROJECT_HOME is not defined.")
      return 1
  
    # call compileToSparc.py
    command = "compileToSparc.py "
    command += "-W ./output.f0000000 "
    command += "-L ./BootloaderLinkerScript.f0000000.lnk "
    command += "-E "+input_name+".elf "
    command += "-H "+input_name+"_hexdump.txt "
    command += "-V "+input_name+"_vardump.txt "
    command += "-M "+input_name+"_memmap.txt "
    command += "-O "+input_name+"_objdump.txt "
    command += "-D MAPTOHIGH "
    command += "-c "+input_file+" "
    command += "-s "+dev_tree_file+" "
    
    ret_status = compileToSparc.execSysCmd(command)
    return ret_status


if __name__ == '__main__':
    ret_val = main()
    sys.exit(ret_val)
