#!/usr/bin/env python
#
# compileToSparc.py
#
# DESCRIPTION :
#      a script which takes a list of C files 
#      and/or assembly files and produces a linked binary, 
#      and optionally a memory map file to 
#      initialize memory contents of the processor model
#
# AUTHOR :
#    Madhav Desai
#
#    (modified by : Neha Karanjkar (5 April 2015)
#         added functionality to generate a 
#        memory map from the elf)
#    (modified by : Neha Karanjkar (5 April 2015)
#         added functionality to generate a 
#        memory map from the elf)
#    (modified by : Anshuman Dhuliya [AD] (1 Feb 2018)
#         added functionality to use glibc (-G option)
#    (modified by : Anshuman Dhuliya [AD] (1 Aug 2019)
#         replaced glibc with buildroot uclibc (-U option)




import os
import os.path
import shutil
import getopt
import sys
import glob
import subprocess
import threading 
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
          print("Error: could not make directory " + work_area)
          return 1
    execSysCmd("rm -rf " + work_area + "/sparc-assembly")
    execSysCmd("mkdir " + work_area + "/sparc-assembly")
    execSysCmd("rm -rf " + work_area + "/sparc-obj")
    execSysCmd("mkdir " + work_area + "/sparc-obj")
    return ret_val


#global variables
def setGlobals(ajit_uclibc, ajit_libgcc):

    global AJIT_UCLIBC_INSTALL_DIR
    AJIT_UCLIBC_INSTALL_DIR = ajit_uclibc

    global AJIT_LIBGCC_INSTALL_DIR
    AJIT_LIBGCC_INSTALL_DIR = ajit_libgcc

    
    #cross compiler prefix
    global COMPILER_PREFIX
    COMPILER_PREFIX = "sparc-linux-"

    #gcc
    global SPARC_CC
    SPARC_CC = COMPILER_PREFIX + "gcc "

    global SPARC_CC_FLAGS 
    #SPARC_CC_FLAGS =  " -S -Wall -Werror -m32 -mcpu=v8 -nostdlib -ffreestanding  "
    SPARC_CC_FLAGS =  " -S -m32 -mcpu=v8 -nostdlib -ffreestanding  "

    global SPARC_CC_OPT_FLAGS 
    SPARC_CC_OPT_FLAGS = " -ffreestanding " 
    
    #assembler (as)
    global SPARC_AS
    SPARC_AS =  COMPILER_PREFIX + "as "
    global SPARC_AS_FLAGS
    SPARC_AS_FLAGS = " -Av8 " 
    
    #loader
    global SPARC_LD
    SPARC_LD = COMPILER_PREFIX+"ld "
    global SPARC_LD_FLAGS
    SPARC_LD_FLAGS = " --verbose=5"
    SPARC_LD_FLAGS += " -L " + ajit_uclibc + "/lib/ -e main -T "
    #SPARC_LD_FLAGS =" -e main -T "

    #readelf utility     
    global SPARC_READELF
    SPARC_READELF=COMPILER_PREFIX+"readelf "
    global SPARC_READELF_FLAGS
    SPARC_READELF_FLAGS=" --hex-dump=.text --hex-dump=.rodata --hex-dump=.rodata.str1.8 --hex-dump=.data --hex-dump=.rodata.cst8 --hex-dump=.bss "
    
    global SPARC_OBJDUMP
    SPARC_OBJDUMP=COMPILER_PREFIX+"objdump -d "



# logging.
def logCommand(sys_cmd):
    print  ("Info: Executing:\n\t" +  sys_cmd)
    sys.stdout.flush()

def logInfo(mesg):
    print ("Info: " + mesg)
    sys.stdout.flush()

def logError(mesg):
    print ("Error: " + mesg)
    sys.stdout.flush()

def logWarning(mesg):
    print ("Warning: " + mesg)
    sys.stdout.flush()

    
# compile C and assembly files and create objects.
def  compileFiles(work_area, src_files,src_dirs,include_dirs,define_strings,assembly_files, assembly_dirs, debug_mode, opt_level, compile_options):
    
    #pdb.set_trace()

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
       for c_opts in compile_options:
          optimize_flags += " -" + c_opts + " "

    for sfile in all_src_files:
        spath,sfilename = os.path.split(sfile)
        name,extn = os.path.splitext(sfilename)
        if(extn == ".c"):
           cc_command = SPARC_CC + " -c " + SPARC_CC_FLAGS  + " " +  optimize_flags + " " + debug_mode + " " + include_string + define_string + " " + sfile  + " -o " + work_area + "/sparc-assembly/" + name + ".s"
           ret_val = execSysCmd(cc_command)
           if(ret_val != 0):
              logError("in compiling file " + ": command " + cc_command)
              return 1

    assembly_dirs.append(work_area + "/sparc-assembly")
    for adir in assembly_dirs:
        for asfile in os.listdir(adir):
            aspath,asfilename = os.path.split(asfile)
            name,extn = os.path.splitext(asfilename)
            if(extn == ".s"):
               #AD as_command = SPARC_AS + " " + SPARC_AS_FLAGS + work_area + "/sparc-assembly/" + name + ".s "  + " -o " + work_area + "/sparc-obj/" + name + ".o"
               as_command = SPARC_AS + " " + SPARC_AS_FLAGS + adir + "/" + asfile  + " -o " + work_area + "/sparc-obj/" + name + ".o"
               ret_val = execSysCmd(as_command)
               if(ret_val != 0):
                  logError("in assembling file " + sfile)
                  return 1
               else:
                  obj_files.append(work_area + "/sparc-obj/" + name + ".o")

    #pdb.set_trace()
    return obj_files


# python module to generate a memory map from a hex-dump file
import generateMemoryMap as gm


def buildExecutable(work_area, obj_files, linker_script_file, elf_file, hex_dump_file,variable_dump_file,memmap_file, objdump_file, uclibc_flag):
    
    if(not linker_script_file) :
        logError ("linker script file not specified")
        return 1

    # pick up all the object files listed in obj_files.
    obj_file_string = ""
    for objfile in obj_files:
       obj_file_string += " " +  objfile + " "

    obj_file_string += " "
    full_elf_file     = work_area + "/" + elf_file

    sparc_ld_command = SPARC_LD + SPARC_LD_FLAGS + linker_script_file
    sparc_ld_command +=  obj_file_string + " -o " + full_elf_file
    if (uclibc_flag):
      print("AJIT:", AJIT_UCLIBC_INSTALL_DIR)
      sparc_ld_command += " -L" + AJIT_UCLIBC_INSTALL_DIR + "/" + "/lib"
      sparc_ld_command += " -L" + AJIT_LIBGCC_INSTALL_DIR + " " # has libgcc.a
      sparc_ld_command += " -static -lm -lc -lgcc "
      sparc_ld_command += " --gc-sections"

    ret_val = execSysCmd(sparc_ld_command)
    if(ret_val != 0):
       logError("in building elf " + elf_file)
       return 1

    #pdb.set_trace()
    sparc_vardump_command = SPARC_READELF + " --symbols " + full_elf_file + "  > " + work_area + "/" + variable_dump_file
    ret_val = execSysCmd(sparc_vardump_command)
    if(ret_val != 0):
       logError("in generating variable-dump from elf " + elf_file)
       return 1
    
    #generate an object dump file for viewing disassembly
    if (not(objdump_file==None or elf_file==None)):
        full_objdump_file  = work_area + "/" + objdump_file
        sparc_objdump_command = SPARC_OBJDUMP + " " + full_elf_file +" > " + full_objdump_file
        ret_val = execSysCmd(sparc_objdump_command)
        if(ret_val != 0):
            logError("in building object dump from elf file " + elf_file)
            return 1
    return 0

            
def Usage():
    print ("arguments:  \n\
               (-h)? \n\
                -N application-name (required.. name of application, used to generate name.elf etc.. \n\
               (-W work-area)? (work-area to put compilation results) \n\
               (-L linker-script)? (Linker script to be used) \n\
               (-I include-dir)* (add include-dir to header search path) \n\
               (-C src_dir)* (add src-dir to list of directories from which C source is to be compiled)\n\
               (-c src_file)* (add src_file to list of C files to be compiled) \n\
               (-S assembly_dir)* (add assembly-dir to list of directories where assembly code is to assembled)\n\
               (-s assembly_file)* (add assembly_file to list of assembly files to be assembled to object code) \n\
               (-D define-string)* (add define-string as a define when compiling C files)\n\
               (-g )? (compile with debug -g flag) \n\
               (-U )? (compile with uclibc (in the buildroot) \n\
               (-V <vmap-file>) (generate page-table setup assembly code\n\
               (-F <compiler-option>)* \n\
               (-o <0/1/2/3>)* (compile with -O0/1/2/3)")
    return 0

#     (-h)?
#     (-N  application-name)
#     (-W work-area)?
#     (-L linker script)?
#     (-S  assembly-dir)?
#     (-s  assembly-file)?
#     (-I  include-dir)*
#     (-C  src-dir)*
#     (-c  src-file)*
#     (-D  define-string)*
#     (-T link-section)*
#     (-o 1/2/3)?
#     (-F compiler-option)*
#     (-g )? (compile with debug -g flag) \n\
#     (-o <0/1/2/3>)* (compile with -O0/1/2/3)"
#     (-U )? (enable uclibc) \n\
#     (-V <vmap-file>) (generate page-table setup assembly code\n\
def parseOptions(opts):
    work_area = "./"
    app_name = None
    help_flag = 0
    linker_script_file = None
    elf_file = None
    hex_file = None
    var_file = None
    vmap_file = None
    mmap_file = None
    objdump_file =None
    debug_mode = ""
    opt_level  = 0
    compile_options = []
    uclibc_flag = False

    assembly_dirs = []
    assembly_files = []
    src_dirs = []
    src_files = []
    include_dirs = []
    define_strings = []

    #pdb.set_trace ()

    for option, parameter in opts:
        if option == '-h':
           help_flag = 1
        if option == '-W':
           work_area = parameter
           logInfo("work_area  = " + parameter + ".")
        if option == '-V':
           vmap_file = parameter
           logInfo("vmap_file  = " + parameter + ".")
        if option == '-F':
           compile_options.append(parameter)
           logInfo("added-CC-option  = -" + parameter + ".")
        if option == '-L':
           linker_script_file = parameter
           logInfo("linker_script_file  = " + parameter + ".")
        if option == '-N':
           app_name = parameter
           logInfo("application name  = " + parameter + ".")
        if option == '-U':
           uclibc_flag = True
           logInfo("uclibc_flag enabled.")
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

    if (app_name != None):
       elf_file = app_name + ".elf"
       hex_file = app_name + ".hex"
       objdump_file = app_name + ".objdump"
       var_file = app_name + ".vars"
       mmap_file = app_name + ".mmap"

    return help_flag, work_area, linker_script_file, elf_file, hex_file, var_file, mmap_file, objdump_file, assembly_dirs, assembly_files,  src_dirs, src_files, include_dirs, define_strings , debug_mode, opt_level, compile_options, uclibc_flag, vmap_file

def main():
    ret_status = 0

    arg_list = sys.argv[1:]
    if(len(arg_list) < 1):
        print ("\nERROR: no arguments!")
        Usage()
        return 1

    ajit_uclibc_install_dir = os.environ.get("AJIT_UCLIBC_INSTALL_DIR")
    ajit_libgcc_install_dir = os.environ.get("AJIT_LIBGCC_INSTALL_DIR")

    setGlobals(ajit_uclibc_install_dir, ajit_libgcc_install_dir)

    arg_list = sys.argv[1:]
    opts,args = getopt.getopt(arg_list,'W:L:C:c:S:s:I:D:Uhgo:T:F:V:N:')
    help_flag, work_area, linker_script_file, elf_file, hex_file, var_file, mmap_file, objdump_file, assembly_dirs, assembly_files,  src_dirs, src_files, include_dirs, define_strings, debug_mode, opt_level,compiler_options,uclibc_flag,vmap_file  = parseOptions(opts)
    
    #pdb.set_trace()
    if(help_flag == 1):
       Usage()
       return 0

    makeWorkArea(work_area)
    if (vmap_file != None):
        op_file  = work_area + "/__genvmap_setup_page_tables.s"
        vmap_cmd = "genVmapAsm " + vmap_file + " "  + op_file
        vmap_status = execSysCmd (vmap_cmd)
        if (vmap_status != 0):
           logError(vmap_cmd + " failed")
           return 1
        else:
           assembly_files.append(op_file)

    obj_files =  compileFiles(work_area, src_files, src_dirs, include_dirs, define_strings, assembly_files, assembly_dirs, debug_mode, opt_level, compiler_options)
    if(len(obj_files)==0):
       print ("Error: compilation failed... no object files produced" )
       return 1

    if(elf_file != None):
       ret_status = buildExecutable(work_area, obj_files, linker_script_file, elf_file, hex_file, var_file, mmap_file, objdump_file, uclibc_flag)
       if(ret_status == 1):
          print ("Error: sparc-executable build failed." )
          return 1

    hexdump_cmd = SPARC_READELF + " `pt_load_sections.py " + elf_file + "` " + elf_file + " | grep 0x > " + hex_file
    execSysCmd(hexdump_cmd)
 
    gen_mmap_cmd = "generateMemoryMap_Byte " + hex_file +  " > " +  mmap_file
    egen = execSysCmd(gen_mmap_cmd)
    if(egen != 0):
       logError(gen_mmap_cmd + " failed")
       return 1
    
    if (vmap_file != None):
       remap_cmd = "remapMemmap " + vmap_file + " "  + mmap_file + " " + mmap_file + ".remapped"
       err_remap = execSysCmd (remap_cmd)
       if (err_remap != 0):
          logError(remap_cmd + "failed")
          return 1

    return ret_status


if __name__ == '__main__':
    ret_val = main()
    sys.exit(ret_val)
