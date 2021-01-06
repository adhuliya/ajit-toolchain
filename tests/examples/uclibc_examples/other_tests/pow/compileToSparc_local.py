#!/usr/bin/env python
#
# compileToSparc.py
#
# DESCRIPTION :
#	  a script which takes a list of C files 
#	  and/or assembly files and produces a linked binary, 
#	  and optionally a memory map file to 
#	  initialize memory contents of the processor model
#
# AUTHOR :
#	Madhav Desai
#
#	(modified by : Neha Karanjkar (5 April 2015)
# 		added functionality to generate a 
#	(modified by : Anshuman Dhuliya [AD] (1 Feb 2018)
# 		added functionality to use glibc (-G option)
#		memory map from the elf)




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
def makeWorkArea(work_area):
    ret_val = 0
    if(not os.path.isdir(work_area)):
       ret_val = execSysCmd("mkdir " + work_area)
       if(ret_val != 0):
          print "Error: could not make directory " + work_area
          return 1
    execSysCmd("rm -rf " + work_area + "/sparc-assembly")
    execSysCmd("mkdir " + work_area + "/sparc-assembly")
    execSysCmd("rm -rf " + work_area + "/sparc-obj")
    execSysCmd("mkdir " + work_area + "/sparc-obj")
    return ret_val


#global variables
def setGlobals(ajit_project_home, ajitcc):
	global AJIT_PROJECT_HOME
	AJIT_PROJECT_HOME = ajit_project_home
	
	#cross compiler prefix
	global COMPILER_PREFIX
        if(ajitcc == None):
	  COMPILER_PREFIX = "sparc-linux-"
        else:
	  COMPILER_PREFIX = ajitcc + "-"

	#gcc
	global SPARC_CC
	SPARC_CC = COMPILER_PREFIX + "gcc -v"

	global SPARC_CC_FLAGS 
	SPARC_CC_FLAGS =  " -S -Wall -Werror -m32 -mcpu=v8 -nostdlib -ffreestanding "

	global SPARC_CC_OPT_FLAGS 
        SPARC_CC_OPT_FLAGS = " -ffreestanding -fschedule-insns -fschedule-insns2 -frename-registers "
	
	#assembler (as)
	global SPARC_AS
	SPARC_AS =  COMPILER_PREFIX + "as "
	global SPARC_AS_FLAGS
	SPARC_AS_FLAGS = " -Av8 " 
	
	#linker
	global LINKER_SCRPT_LNK
	LINKER_SCRPT_LNK = ajit_project_home + "/tools/linker/LinkerScript.lnk"
	
	#loader
	global SPARC_LD
	SPARC_LD = COMPILER_PREFIX+"ld "
	global SPARC_LD_FLAGS
	SPARC_LD_FLAGS = " -L" + ajit_project_home + "/tools/cross-compiler/buildroot_cross_compiler/usr/sparc-buildroot-linux-uclibc/lib/ -e main -T "
	#AD SPARC_LD_FLAGS =" -e main -T "
	#GLIBC_INSTALL = AJIT_PROJECT_HOME + "/glibc/2-21/lib"
	#SPARC_LD_FLAGS =" -e main -L" + GLIBC_INSTALL + " -L/home/zeal/AjitRepoV2_cpy/tools/cross-compiler/release/lib/gcc/sparc-elf/4.4.3/ -static -lm -lc -lgcc -T "  #AD modified added -L...

	#readelf utility 	
	global SPARC_READELF
	SPARC_READELF=COMPILER_PREFIX+"readelf "
	global SPARC_READELF_FLAGS
	SPARC_READELF_FLAGS=" --hex-dump=.text --hex-dump=.rodata --hex-dump=.rodata.str1.8 --hex-dump=.data --hex-dump=.rodata.cst8 --hex-dump=.bss "
	
	global SPARC_OBJDUMP
	SPARC_OBJDUMP=COMPILER_PREFIX+"objdump -d "



# logging.
def logCommand(sys_cmd):
    print  "Info: Executing:\n\t" +  sys_cmd

def logInfo(mesg):
    print "Info: " + mesg

def logError(mesg):
    print "Error: " + mesg

def logWarning(mesg):
    print "Warning: " + mesg

    
# compile C and assembly files and create objects.
def  compileFiles(work_area, src_files,src_dirs,include_dirs,define_strings,assembly_files, assembly_dirs, debug_mode, opt_level):
    

    pdb.set_trace

    obj_files  = []
    include_string = ""
    for idir in include_dirs:
        include_string += " -I " + idir + " "

    define_string = ""
    for dstr in define_strings:
        define_string += " -D " + dstr + " "

    all_src_files  = []

    for afile in assembly_files:
        aspath, asfilename = os.path.split(afile)
	name,extn = os.path.splitext(asfilename)
        if(extn == ".s"):
           as_command = SPARC_AS + " " + SPARC_AS_FLAGS + " " + afile  + " -o " + work_area + "/sparc-obj/" + name + ".o"
           ret_val = execSysCmd(as_command)
           if(ret_val != 0):
              logError("in assembling file " + afile)
	      return 1
	   else:
              obj_files.append(work_area + "/sparc-obj/" + name + ".o")

    
    for src_file in src_files:
        all_src_files.append(src_file)


    for src_dir in src_dirs:
        for ssfile in os.listdir(src_dir):
	    name,extn = os.path.splitext(ssfile)
            if(extn == ".c"):
               all_src_files.append(src_dir + "/" + ssfile)
        
        
    optimize_flags = ""
    # do not optimize in debug mode... crazy things happen.
    if debug_mode != "-g":
       optimize_flags = " -O" + str(opt_level) + " " + SPARC_CC_OPT_FLAGS + " "

    for sfile in all_src_files:
        spath,sfilename = os.path.split(sfile)
	name,extn = os.path.splitext(sfilename)
        if(extn == ".c"):
           cc_command = SPARC_CC + " -c " + SPARC_CC_FLAGS  + " " +  optimize_flags + " " + debug_mode + " " + include_string + define_string + " " + sfile  + " -o " + work_area + "/sparc-assembly/" + name + ".s"
           ret_val = execSysCmd(cc_command)
           if(ret_val != 0):
              logError("in compiling file " + sfile)
	      return 1

    assembly_dirs.append(work_area + "/sparc-assembly")
    for adir in assembly_dirs:
        for asfile in os.listdir(adir):
            aspath,asfilename = os.path.split(asfile)
	    name,extn = os.path.splitext(asfilename)
            if(extn == ".s"):
               as_command = SPARC_AS + " " + SPARC_AS_FLAGS + work_area + "/sparc-assembly/" + name + ".s "  + " -o " + work_area + "/sparc-obj/" + name + ".o"
               ret_val = execSysCmd(as_command)
               if(ret_val != 0):
                  logError("in assembling file " + sfile)
	          return 1
	       else:
                  obj_files.append(work_area + "/sparc-obj/" + name + ".o")

    return obj_files


#AD added path for import generateMemoryMap to work
sys.path.append("/usr/local/ajit_release/tools/scripts") #AD

# python module to generate a memory map from a hex-dump file
import generateMemoryMap as gm


def buildExecutable(work_area, link_sections, obj_files, linker_script_file, elf_file, hex_dump_file,variable_dump_file,memmap_file, objdump_file, glibc_version):
    
    if(not linker_script_file) :
    	linker_script_file = LINKER_SCRPT_LNK

    # pick up all the object files listed in obj_files.
    obj_file_string = ""
    for objfile in obj_files:
       obj_file_string += " " +  objfile + " "

    obj_file_string += " "
    full_elf_file 	= work_area + "/" + elf_file
    sparc_ld_command = SPARC_LD+ " -static --gc-sections " + SPARC_LD_FLAGS+ linker_script_file  + obj_file_string
    if (glibc_version):
      GLIBC_INSTALL = " -L" + AJIT_PROJECT_HOME + "/glibc/" + glibc_version + "/lib"
      # sparc_ld_command += " --gc-sections "
      sparc_ld_command += GLIBC_INSTALL
      sparc_ld_command += " -L/home/zeal/AjitRepoV2/tools/cross-compiler/release/lib/gcc/sparc-elf/4.4.3/"
      # sparc_ld_command += " -static -lm -lc -lgcc"
      sparc_ld_command += " -lm -lc -lgcc"
      #sparc_ld_command += GLIBC_INSTALL + " -L/home/zeal/AjitRepoV2/tools/cross-compiler/release/lib/gcc/sparc-elf/4.4.3/ -static -lm -lc -lgcc "
    # sparc_ld_command += " -lgcc_s"
    # sparc_ld_command += " --gc-sections"
    sparc_ld_command += " -o " + full_elf_file
    ret_val = execSysCmd(sparc_ld_command)
    if(ret_val != 0):
       logError("in building elf " + elf_file)
       return 1

    additional_hex_dumps = " "
    for ls in link_sections:
       additional_hex_dumps += " --hex-dump=" + ls + " " 

    sparc_hexdump_command = SPARC_READELF+SPARC_READELF_FLAGS+additional_hex_dumps+ full_elf_file + " | tr -cd '\\11\\12\\15\\40-\\176' | grep 0x > "  +  work_area + "/" + hex_dump_file
    ret_val = execSysCmd(sparc_hexdump_command)
    if(ret_val != 0):
       logError("in generating hex-dump from elf " + elf_file)
       return 1

    sparc_vardump_command = SPARC_READELF+ " --symbols " + full_elf_file + "  > " + work_area + "/" + variable_dump_file
    ret_val = execSysCmd(sparc_vardump_command)
    if(ret_val != 0):
       logError("in generating variable-dump from elf " + elf_file)
       return 1
    
    #generate memory map from elf
    if (not(memmap_file==None or hex_dump_file==None)):
	    full_hexdump_file = work_area + "/" + hex_dump_file
	    full_memmap_file  = work_area + "/" + memmap_file
	    ret_val = gm.generate_memorymap(full_hexdump_file, full_memmap_file)
	    logCommand("Info: Generating memory map " + full_memmap_file)
	    if(ret_val != 0):
		logError("in generating memory map from hexdump " + elf_file)
		return 1

    #generate an object dump file for viewing disassembly
    if (not(objdump_file==None or elf_file==None)):
	    full_elf_file = work_area + "/" + elf_file
	    full_objdump_file  = work_area + "/" + objdump_file
	    sparc_objdump_command = SPARC_OBJDUMP + " " + full_elf_file +" > " + full_objdump_file
	    ret_val = execSysCmd(sparc_objdump_command)
	    if(ret_val != 0):
	    	logError("in building object dump from elf file " + elf_file)
		return 1
    return 0

            
def Usage():
    print "arguments:  \n\
               (-h)? \n\
               (-W work-area)? (work-area to put compilation results) \n\
	       (-L linker-script)? (Linker script to be used) \n\
               (-E bin-file)? (name of elf-file to be generated) \n\
                    if this option is absent, no elf-file will be generated \n\
               (-H hex-dump-file)? (name of hex-dump-file to be generated) \n\
               (-V var-dump-file)? (name of var-dump-file to be generated) \n\
	       (-M mem-map-file)? (name of memory map file to be generated) \n\
	       (-O objdump-file)? (name of object dump file to be generated) \n\
               (-I include-dir)* (add include-dir to header search path) \n\
               (-C src_dir)* (add src-dir to list of directories from which C source is to be compiled)\n\
               (-c src_file)* (add src_file to list of C files to be compiled) \n\
               (-S assembly_dir)* (add assembly-dir to list of directories where assembly code is to assembled)\n\
               (-s assembly_file)* (add assembly_file to list of assembly files to be assembled to object code) \n\
               (-D define-string)* (add define-string as a define when compiling C files)\n\
               (-g )? (compile with debug -g flag) \n\
               (-G )? (glibc_version e.g. use 2-21 for version 2.21) \n\
               (-o <0/1/2/3>)* (compile with -O0/1/2/3)"
    return 0

#     (-h)?
#     (-W work-area)?
#     (-L linker script)?
#     (-E  elf-file)?
#     (-H  hex-dump-file)?
#     (-V  var-dump-file)?
#     (-M  mem-map-file)?
#     (-O  object-dump-file)?
#     (-S  assembly-dir)?
#     (-s  assembly-file)?
#     (-I  include-dir)*
#     (-C  src-dir)*
#     (-c  src-file)*
#     (-D  define-string)*
#     (-T link-section)*
#     (-G glibc-version)*
#     (-o 1/2/3)?
def parseOptions(opts):
    work_area = "./"
    help_flag = 0
    linker_script_file = None
    elf_file = None
    hex_file = None
    var_file = None
    mmap_file = None
    objdump_file =None
    debug_mode = ""
    opt_level  = 0
    glibc_version = ""

    assembly_dirs = []
    assembly_files = []
    src_dirs = []
    src_files = []
    include_dirs = []
    define_strings = []
    link_sections = []

    for option, parameter in opts:
        if option == '-h':
           help_flag = 1
        if option == '-W':
           work_area = parameter
           logInfo("work_area  = " + parameter + ".")
	if option == '-L':
           linker_script_file = parameter
           logInfo("linker_script_file  = " + parameter + ".")
        if option == '-E':
           elf_file = parameter
           logInfo("elf-file to be produced  = " + parameter + ".")
        if option == '-H':
           hex_file = parameter
           logInfo("hex-dump-file to be produced  = " + parameter + ".")
        if option == '-G':
           glibc_version = parameter
           logInfo("glibc_version to be used  = " + parameter + ".")
        if option == '-T':
           link_sections.append( parameter)
           logInfo("link-section to be added to hex-dump  = " + parameter + ".")
        if option == '-V':
           var_file = parameter
           logInfo("var-dump-file to be produced  = " + parameter + ".")
        if option == '-M':
           mmap_file = parameter
           logInfo("memory-map-file to be produced  = " + parameter + ".")
	if option == '-O':
           objdump_file = parameter
           logInfo("object-dump-file to be produced  = " + parameter + ".")
        if option == '-c':
           src_files.append(parameter)
           logInfo("added src-file = " + parameter + ".")
        if option == '-C':
           src_dirs.append(parameter)
           logInfo("added src-directory = " + parameter + ".")
        if option == '-s':
           assembly_files.append(parameter)
           logInfo("added assembly-file = " + parameter + ".")
        if option == '-S':
           assembly_dirs.append(parameter)
           logInfo("added assembly-directory = " + parameter + ".")
        if option == '-I':
           include_dirs.append(parameter)
           logInfo("added include-directory = " + parameter + ".")
        if option == '-D':
           define_strings.append(parameter)
           logInfo("added define_string = " + parameter + ".")
        if option == '-g':
           debug_mode = "-g"
           logInfo("compile with -g.")
        if option == '-o':
           opt_level = int(parameter)
	   if opt_level > 0:
              logInfo("optimization level = " + str(opt_level))

    return help_flag, work_area, linker_script_file, elf_file, hex_file, var_file, mmap_file, objdump_file, assembly_dirs, assembly_files,  src_dirs, src_files, include_dirs, define_strings , debug_mode, opt_level, link_sections, glibc_version

def main():
    ret_status = 0

    arg_list = sys.argv[1:]
    if(len(arg_list) < 1):
	print "\nERROR: no arguments!"
        Usage()
        return 1

    ajit_project_home = os.environ.get('AJIT_PROJECT_HOME')
    ajit_project_cross_compiler = os.environ.get("AJIT_PROJECT_CROSS_COMPILER")

    if(ajit_project_home == None):
       logError("environment variable AJIT_PROJECT_HOME is not defined." )
       return 1

    setGlobals(ajit_project_home, ajit_project_cross_compiler)

    arg_list = sys.argv[1:]
    opts,args = getopt.getopt(arg_list,'W:L:C:c:S:s:I:D:E:H:V:M:O:hgo:T:G:')
    help_flag, work_area, linker_script_file, elf_file, hex_file, var_file, mmap_file, objdump_file, assembly_dirs, assembly_files,  src_dirs, src_files, include_dirs, define_strings, debug_mode, opt_level,link_sections,glibc_version  = parseOptions(opts)
    
    if(help_flag == 1):
       Usage()
       return 0

    makeWorkArea(work_area)
    obj_files =  compileFiles(work_area, src_files, src_dirs, include_dirs, define_strings, assembly_files, assembly_dirs, debug_mode, opt_level)
    if(len(obj_files)==0):
       print "Error: compilation failed." 
       return 1

    if(elf_file != None):
       ret_status = buildExecutable(work_area, link_sections, obj_files, linker_script_file, elf_file, hex_file, var_file, mmap_file, objdump_file,glibc_version)
       if(ret_status == 1):
          print "Error: sparc-executable build failed." 
          return 1

    return ret_status


if __name__ == '__main__':
    ret_val = main()
    sys.exit(ret_val)
