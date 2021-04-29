#!/usr/bin/env python
#
# ImageRCBuild.py is a top-level script which integrates
# the entire IMAGE RC mapping flow, starting from a
# a user project and ending with hexfiles, a test application
# and a shared library.
#
# The script can be stopped at various natural points.
# The organization of the project files and ways to 
# to use the generated products of the script are 
# explained in detail in the IMAGE-RC user-guide.
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
import popen2
import pdb
import time

# run system command.
def execSysCmd(sys_cmd):
    logCommand(sys_cmd)
    ret_val = os.system(sys_cmd)
    return ret_val

# clean the work-area, remove all the stuff produced by the script.
def cleanWorkArea(work_area):
    execSysCmd("rm -rf " + work_area + "./bin/*")
    execSysCmd("rm -rf " + work_area + "./lib/*")
    execSysCmd("rm -rf " + work_area + "./hexfiles/*")
    execSysCmd("rm -rf " + work_area + "./App/obj/*")
    execSysCmd("rm -rf " + work_area + "./App/objsw/*")
    execSysCmd("rm -rf " + work_area + "./App/objsim/*")

    fpga_list = []
    fpga_list.append("fpga00") 
    fpga_list.append("fpga01") 
    fpga_list.append("fpga11") 
    fpga_list.append("fpga10") 

    for fpga_name in fpga_list:
    	execSysCmd("rm -rf " + work_area + "./FpgaCode/" + fpga_name + "/objsw/*")
    	execSysCmd("rm -rf " + work_area + "./FpgaCode/" + fpga_name + "/objhw/*")
    	execSysCmd("rm -rf " + work_area + "./FpgaCode/" + fpga_name + "/Aa/*")
    	execSysCmd("rm -rf " + work_area + "./FpgaCode/" + fpga_name + "/Aa/.*.*aa")
    	execSysCmd("rm -rf " + work_area + "./FpgaCode/" + fpga_name + "/vC/*")
    	execSysCmd("rm -rf " + work_area + "./FpgaCode/" + fpga_name + "/vC/.*.*vc")
    	execSysCmd("rm -rf " + work_area + "./FpgaCode/" + fpga_name + "/vhdl/*")
    	execSysCmd("rm -rf " + work_area + "./FpgaCode/" + fpga_name + "/vhdl/.*.*vhdl")

    return 0


     

    
# set global variables used in this script from environment
# variables.
def setGlobals(image_install_dir, ahir_release_path, rc_release_path):

    global IMAGE_LIB
    global IMAGE_INCLUDE

    global AHIR_RELEASE
    global FUNCTIONLIB
    global XILINX_UNISIM
    global XILINX_SIMPRIM
    global AHIR_PTHREAD_UTILS_INCLUDE
    global AHIR_FUNCTIONLIB

    # RC stuff
    global RC_RELEASE
    global RC_LIB
    global RC_INCLUDE
    global RC_VHDL
    global RC_AA
    
    global FPGA_LIB_PATH
    global HOST_LIB_PATH

    # Two versions of pipes, for software version, we
    # use pipeHandler, for ghdl simulation we use SocketLib.
    global SOCKETLIB_INCLUDE
    global SOCKETLIB_LIB
    global PIPEHANDLER_INCLUDE
    global PIPEHANDLER_LIB
    global FUNCTIONLIB_INCLUDE

    # VHDL libraries from AHIR distro.
    global AHIR_VHDL_LIB
    global AHIR_VHDL_VHPI_LIB


    # source files.
    # FPGA source files.
    global SRCFPGASIDE
    # application source files (includes testbench).
    global SRCAPP

    # VHDL, Aa results
    global VHDL
    global AA


    # SW version.
    global SW_INCLUDES
    global SW_LIB_PATHS
    global SW_LIBS

    # HW version..
    global HW_INCLUDES
        
    # CLANG includes
    global CLANG_INCLUDES
    
    # HW testbench for GHDL sim.
    global TB_INCLUDES
    global TB_LIB_PATHS
    global TB_LIBS

    # GHDL libraries to be linked to.
    global GHDL_LIB_OPTS

    global FPGA00_AA
    global UPLINK_AA
    global FPGA01_AA
    global FPGA10_AA
    global FPGA11_AA
    #pdb.set_trace()

    # IMAGE-related
    IMAGE_LIB=image_install_dir + "/lib"
    IMAGE_INCLUDE=image_install_dir + "/include"

    # AHIR-related
    AHIR_RELEASE=ahir_release_path
    FUNCTIONLIB=AHIR_RELEASE + "/functionLibrary"
    XILINX_UNISIM=AHIR_RELEASE + "/vhdl"
    XILINX_SIMPRIM=AHIR_RELEASE + "/vhdl"
    SOCKETLIB_INCLUDE=AHIR_RELEASE + "/CtestBench/include"
    SOCKETLIB_LIB=AHIR_RELEASE + "/CtestBench/lib"
    PIPEHANDLER_INCLUDE=AHIR_RELEASE + "/pipeHandler/include"
    PIPEHANDLER_LIB=AHIR_RELEASE + "/pipeHandler/lib"
    AHIR_VHDL_LIB=AHIR_RELEASE + "/vhdl"
    AHIR_VHDL_VHPI_LIB=AHIR_RELEASE + "/CtestBench/vhdl"
    AHIR_PTHREAD_UTILS_INCLUDE=AHIR_RELEASE + "/pthreadUtils/include"
    AHIR_FUNCTIONLIB=AHIR_RELEASE + "/functionLibrary"
    
    # RC related. 
    RC_RELEASE=rc_release_path
    RC_LIB=rc_release_path + "/lib"
    RC_INCLUDE=rc_release_path + "/include"
    RC_VHDL=rc_release_path + "/vhdl"
    RC_AA=rc_release_path + "/Aa"
    FPGA00_AA=RC_AA + "/fpga00.aa"
    UPLINK_AA=RC_AA + "/uplinkMemory.aa"
    FPGA01_AA=RC_AA + "/fpga01.aa"
    FPGA10_AA=RC_AA + "/fpga10.aa"
    FPGA11_AA=RC_AA + "/fpga11.aa"
    FPGA_LIB_PATH = "-L" + RC_LIB 
    HOST_LIB_PATH = "-L" + RC_LIB

    GHDL_LIB_OPTS = "-Wl,-L" + SOCKETLIB_LIB + " -Wl,-L" + RC_LIB + " -Wl,-lVhpi" + " -Wl,-lrcApiWithoutPlx" + " -Wl,-lrt"


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

    
# compile function
#  CC = compiler, SRC_DIRS = src-directory-list, OBJ = obj-dir, CFLAGS, list-of-includes, list-of-defines.
def  compileFiles(CC, SRC_DIRS, OBJ, CFLAGS, INCLUDE_LIST, DEFINES):
    err_flag = 0
    include_string = ""
    for incldir in INCLUDE_LIST:
   	include_string += " -I " +   incldir + " "

    define_string = ""
    for defs  in DEFINES:
        define_string += "-D" + defs

    # make object directory if needed.       
    if(os.path.isdir(OBJ) != 1): 
    	os.mkdir(OBJ)

        
    cc_command = ""
    for src_dir in SRC_DIRS:
        for sfile in os.listdir(src_dir):
	    name,extn = os.path.splitext(sfile)
            if(extn == ".c"):
               cc_command = CC + " -c " + CFLAGS  + " " + include_string + " " +  define_string + " " + src_dir + "/" + sfile  + " -o " + OBJ + "/" + name + ".o"
	       logInfo("executing compile-command\n\t " + cc_command)
               ret_val = execSysCmd(cc_command)
               if(ret_val != 0):
                   logError("in compiling file " + sfile)
	           err_flag = 1
	
    return err_flag

    
# link-function
#   linker, bin-dir, exe-name, list-of-object-dirs, link-flags, list-of-shared-libs, list-of-static-libs
def linkAndBuildExecutable(LD, BIN, EXE, OBJDIRS, LDFLAGS, SHAREDLIBS, STATICLIBS):
    err_flag = 0
    ld_string = LDFLAGS
    for solib in SHAREDLIBS:
       ld_string += " -l" + solib
     
    static_libs = ""
    for stlib in STATICLIBS:
       static_libs += " " + stlib 

    ld_command = LD + " -o " + BIN + "/" + EXE + " " + ld_string
    for objdir in OBJDIRS:
        obj_files = os.listdir(objdir)
        for obj_file in obj_files:
            root,ext = os.path.splitext(obj_file)
            if(ext == ".o"):
               ld_command += " " + objdir + "/" +  obj_file
    
    ld_command += static_libs
    logInfo("executing link-command\n\t " + ld_command)
    err_flag = execSysCmd(ld_command)

    return(err_flag)

# compile VHDL test-bench to verify generated VHDL.
def makeVhdlTb(fpga_count, bin_dir, exec_name):

    logInfo("making RTL Simulation test-bench")

    OBJDIR = "../App/objsim"
    makeOrCleanDir(OBJDIR)

    OBJDIRS = [] 
    OBJDIRS.append(OBJDIR)


    SRCDIRS= []
    SRCDIRS.append("../Shared/src/")
    SRCDIRS.append("../App/src/testbench")
    SRCDIRS.append("../App/src/api")

    DEFINES=""

    INCLUDE_LIST=[]
    INCLUDE_LIST.append("../Shared/include")
    INCLUDE_LIST.append("../App/include")
    INCLUDE_LIST.append(SOCKETLIB_INCLUDE)
    INCLUDE_LIST.append(RC_INCLUDE)
    INCLUDE_LIST.append(AHIR_RELEASE)

    ret_status = compileFiles("gcc",SRCDIRS,OBJDIR,"-g ",INCLUDE_LIST,DEFINES)
    if(ret_status != 0):
       return 1

    ld_flags = " -L" + SOCKETLIB_LIB + " -L" + RC_LIB 
    shared_libs = []
    shared_libs.append("SocketLib")
    shared_libs.append("pthread")
    shared_libs.append("rcApiWithoutPlx")
    shared_libs.append("rt")
    static_libs = []

    ret_status = linkAndBuildExecutable("gcc", bin_dir, exec_name, OBJDIRS, ld_flags, shared_libs, static_libs)
    return ret_status


# compile hardware VHDL files for RTL simulation.
def makeVhdlHwSimModel(fpga_count,bin_dir,exec_name):
    ret_val = 0

    logInfo("making HW Sim-model")

    execSysCmd("ghdl --clean")
    execSysCmd("ghdl --remove")
    execSysCmd("ghdl -i --work=GhdlLink " + AHIR_VHDL_LIB + "/GhdlLink.vhdl")
    execSysCmd("ghdl -i --work=ahir " + AHIR_VHDL_LIB + "/ahir.vhdl")
    execSysCmd("ghdl -i --work=ahir_ieee_proposed " + AHIR_VHDL_LIB + "/aHiR_ieee_proposed.vhdl")
    execSysCmd("ghdl -i --work=unisim " + RC_VHDL + "/Simulation/unisim.vhdl ")
    execSysCmd("ghdl -i --work=work " + RC_VHDL + "/Simulation/plx_vhpi_model.vhdl ")
    execSysCmd("ghdl -i --work=work " + RC_VHDL + "/Simulation/BoardSimModel.vhdl ")
    execSysCmd("ghdl -i --work=work " + RC_VHDL + "/rc/rc.vhdl")

    if (fpga_count == 4):
  	fpga_toplevel_package =RC_VHDL + "/TopLevelPackages/FourFpgaConstants.vhdl"
    else:
  	fpga_toplevel_package =RC_VHDL + "/TopLevelPackages/SingleFpgaConstants.vhdl"
    execSysCmd("ghdl -i --work=work " + fpga_toplevel_package)
    fpga_list = []
    fpga_list.append("fpga00")
    if(fpga_count == 4):
	fpga_list.append("fpga01")
	fpga_list.append("fpga11")
	fpga_list.append("fpga10")

    for fpga in fpga_list:
	cmd_status = execSysCmd("ghdl -i --work=work ../FpgaCode/" + fpga + "/vhdl/" + fpga + "_global_package.vhdl")
        if(cmd_status != 0):
		logError("compilation of " + fpga + "_global_package.vhdl failed")
		ret_val = 1
	cmd_status = execSysCmd("ghdl -i --work=work ../FpgaCode/" + fpga + "/vhdl/" + fpga + ".vhdl")
	if(cmd_status != 0):
		logError("compilation of " + fpga + ".vhdl failed")
		ret_val = 1

    if(ret_val == 0):
        ghdl_cmd = "ghdl -m --work=work -Wc,-g " +  GHDL_LIB_OPTS + " BoardSimModel"
        logInfo("executing ghdl-make\n\t " + ghdl_cmd)
        cmd_status = execSysCmd(ghdl_cmd)
	if(cmd_status != 0):
		logError("GHDL build of HW RTL Simulation model failed ")
		ret_val = 1
	else:
		execSysCmd("mv boardsimmodel " + bin_dir + "/" + exec_name)

    return ret_val
        

# make the TB and HW simulation models.
# both must be run simultaneously in separate processes
# to run the simulation.
def makeVhdlSim(fpga_count):
    logInfo("in makeVhdlSim (" + str(fpga_count) + ")")

    cwd_dir = os.getcwd()
    makeOrCleanDir("./.ghdl")

    os.chdir("./.ghdl")

    ret_val = makeVhdlTb(fpga_count, "../bin", "rtlSimTestBench")
    if(ret_val != 0):
	logError("compilation of RTL simulation Testbench failed ")
	os.chdir(cwd_dir)
	return 1

    ret_val = makeVhdlHwSimModel(fpga_count, "../bin", "rtlSimHardwareModel")
    if(ret_val != 0):
	logError("compilation of RTL hardware simulation model failed ")
	os.chdir(cwd_dir)
	return 1
	
    os.chdir(cwd_dir)
    execSysCmd("rm -rf ./.ghdl")
    return 0
    

# dummy hex-files are copied in the 1-FPGA case.
def copyDummyHexFiles(fpga_type):
    if(fpga_type == "xc3s5000-fg1156-4"):
	execSysCmd("cp -f " + RC_RELEASE + "/dummyHexFiles/spartan3/*.hex ./hexfiles")
	return 0
    else:
	logError("unsupported fpga-type " + fpga_type)
        return 1
   

# build hex files using Xilinx ISE tools.
def makeHexFile(fpga_count, fpga_name, fpga_type):

    logInfo("in makeHexFile (" + str(fpga_count) + ", " +  fpga_name + ", " + fpga_type + ")")
    cwd_path = os.getcwd()
    os.chdir("./hexfiles")   

   
    STATIC_VHDL=RC_RELEASE + "/vhdl"

    scr_file_name = fpga_name + ".scr"
    prj_file_name = fpga_name + ".prj"

    # make script file.
    scr_file = open(scr_file_name,"w")
    print >> scr_file, "run -ifn " + prj_file_name + " "
    print >> scr_file, "-ofn " + fpga_name + "Top"
    print >> scr_file, "-ifmt mixed"
    print >> scr_file, "-ofmt NGC"
    print >> scr_file, "-p " + fpga_type 
    print >> scr_file, "-top " + fpga_name + "Top"
    print >> scr_file, "-write_timing_constraints yes"
    print >> scr_file, "-hierarchy_separator _"
    print >> scr_file, "-bus_delimiter <>"
    print >> scr_file, "-fsm_extract no"
    print >> scr_file, "-ram_extract yes"
    print >> scr_file, "-rom_extract yes"
    print >> scr_file, "-mux_extract yes"
    print >> scr_file, "-decoder_extract yes"
    print >> scr_file, "-priority_extract yes"
    print >> scr_file, "-shreg_extract yes"
    print >> scr_file, "-shift_extract no"
    print >> scr_file, "-xor_collapse yes"
    print >> scr_file, "-resource_sharing yes"
    print >> scr_file, "-max_fanout 16"
    print >> scr_file, "-register_duplication yes"
    print >> scr_file, "-equivalent_register_removal yes"
    print >> scr_file, "-optimize_primitives yes"
    print >> scr_file, "-iuc yes"
    print >> scr_file, "-keep_hierarchy yes"
    print >> scr_file, "-opt_mode speed"
    print >> scr_file, "-opt_level 2"
    print >> scr_file, "-safe_implementation yes"
    scr_file.close()
     
    # make project file.
    prj_file = open(prj_file_name,"w")
    print >> prj_file, "vhdl ahir_ieee_proposed " + AHIR_VHDL_LIB + "/aHiR_ieee_proposed.vhdl"
    print >> prj_file, "vhdl ahir " + AHIR_VHDL_LIB + "/ahir.vhdl"
    if(fpga_count == 4):
	print >> prj_file, "vhdl work  " + RC_VHDL + "/TopLevelPackages/FourFpgaConstants.vhdl"
    else:
	print >> prj_file, "vhdl work  " + RC_VHDL + "/TopLevelPackages/SingleFpgaConstants.vhdl"

    print >> prj_file, "vhdl work " + RC_VHDL + "/rc/rc.vhdl"
    print >> prj_file, "vhdl work " + cwd_path + "/FpgaCode/" + fpga_name + "/vhdl/" + fpga_name + "_global_package.vhdl"
    print >> prj_file, "vhdl work " + cwd_path + "/FpgaCode/" + fpga_name + "/vhdl/" + fpga_name + ".vhdl"
    prj_file.close()

    # run xst
    xst_command = "xst -intstyle xflow -ifn " + scr_file_name
    logInfo("running xst\n\t " + xst_command)
    xst_status  = execSysCmd(xst_command)
    if(xst_status != 0):
	logError("xst failed for " + fpga_name)
	os.chdir(cwd_path)
	return 1

    # run ngdbuild
    ngdbuild_cmd  = "ngdbuild -intstyle xflow -insert_keep_hierarchy -sd edf_ngc -dd ./_ngo -p " + fpga_type
    ngdbuild_cmd += " -uc " + STATIC_VHDL + "/ucf/spartan3/" + fpga_name + "Top.ucf " + fpga_name + "Top.ngc " + fpga_name + "Top.ngd"
    logInfo("running ngdbuild\n\t " + ngdbuild_cmd)
    ngdbuild_status = execSysCmd(ngdbuild_cmd)
    if(ngdbuild_status != 0):
	logError("ngdbuild failed for " + fpga_name)
	os.chdir(cwd_path)
	return 1
    
    # run map
    map_cmd  = "map -intstyle xflow -ignore_keep_hierarchy -p " + fpga_type  + " " 
    map_cmd += "-pr b -o " + fpga_name + "Top.ncd " +  fpga_name + "Top.ngd " +  fpga_name + "Top.pcf"
    logInfo("running map\n\t " + map_cmd)
    map_status = execSysCmd(map_cmd)
    if(map_status != 0):
	logError("map failed for " + fpga_name)
	os.chdir(cwd_path)
	return 1

    # run par
    par_cmd = "par -w -intstyle xflow -ol high -t 1 " +  fpga_name + "Top.ncd " + fpga_name + "Top.par.ncd " +  fpga_name + "Top.pcf"
    logInfo("running par\n\t " + par_cmd)
    par_status = execSysCmd(par_cmd)
    if(par_status != 0):
	logError("par failed for " + fpga_name)
	os.chdir(cwd_path)
	return 1


    # run bitgen
    bitgen_cmd = "bitgen -w -d -intstyle xflow " + fpga_name + "Top.par.ncd " + fpga_name + "Top.bit " + fpga_name + "Top.pcf"
    logInfo("running bitgen\n\t " + bitgen_cmd)
    bitgen_status = execSysCmd(bitgen_cmd)
    if(bitgen_status != 0):
	logError("bitgen failed for " + fpga_name)
	os.chdir(cwd_path)
	return 1

    # run promgen
    promgen_cmd = "promgen -w -p hex -c FF -o " + fpga_name + ".hex  -u 0 " + fpga_name + "Top.bit"
    logInfo("running promgen\n\t " + promgen_cmd)
    promgen_status = execSysCmd(promgen_cmd)
    if(promgen_status != 0):
	logError("promgen failed for " + fpga_name)
	os.chdir(cwd_path)
	return 1
   
    os.chdir(cwd_path)
    return 0

# netgen. make post-synthesis netlist.
def postSynthNetgen(fpga, synth_stage):
    cwd_path = os.getcwd()
    os.chdir("./hexfiles")   

    netgen_cmd =  "netgen -fn -w -ofmt vhdl "
    if(synth_stage == "xst"):
	netgen_cmd += fpga + "Top.ngc " + fpga + "TopSynth.vhd"
    elif (synth_stage == "map"):
	netgen_cmd += fpga + "Top.ncd " + fpga + "TopMap.vhd"
    elif (synth_stage == "par"):
	netgen_cmd += fpga + "Top.par.ncd " + fpga + "TopPAR.vhd"
    else:
	netgen_cmd += fpga + "Top.ngc " + fpga + "TopSynth.vhd"
    
    logInfo("executing netgen\n\t " + netgen_cmd)
    ret_val = execSysCmd(netgen_cmd)
    return(ret_val)

# run the timing verifier on the mapped FPGAs
def checkTiming(fpga_name):
    cwd_path = os.getcwd()
    os.chdir("./hexfiles")   

    trce_cmd = "trce -intstyle ise -e 3 -u 3 -l 3 -xml " + fpga_name + "Top.twx " +  fpga_name + "Top.par.ncd " + fpga_name + "Top.pcf"
    logInfo ("executing trce command\n\t " + trce_cmd)
    
    trce_status = execSysCmd(trce_cmd)
    if(trce_status != 0):
	logError("trce failed for "  + fpga_name)
        os.chdir(cwd_path)
	return 1

    os.chdir(cwd_path)
    return 0

# make a shared library for the application.
def makeAppSharedLibrary(app_name):
    logInfo("in makeAppSharedLibrary (" + app_name + ")")
    work_dir = os.getcwd()

    objs = ""
    for srcfile in os.listdir(work_dir + "/App/src/api"):
	name,extn = os.path.splitext(srcfile)
	if(extn == ".c"):
		objs += " " + work_dir + "/App/obj/" + name + ".o "


    incl_libs = " -L" + IMAGE_LIB + " -L" + RC_LIB + " " 
    shared_libs = " -ldl -lm -lrt -lImageApi -lrcApi "
    lib_cmd = "g++ -shared -o " + "./lib/lib" + app_name + ".so "  + incl_libs + shared_libs + objs
    logInfo("executing shared-lib build command\n\t " + lib_cmd)
    lib_status = execSysCmd(lib_cmd)
    if(lib_status != 0):
	logError("failed to build App shared-library")
	return 1

    return 0
		
	
   
# make the application test-bench.
def makeAppTb(app_name, optimize_flag):
    logInfo("in makeAppTb (" + app_name + ", " + str(optimize_flag) + ")")
    work_dir = os.getcwd()

    if(optimize_flag):
    	cflags    = " -O3 "
    else:
        cflags    = " -g "

    include_directory_list = []
    include_directory_list.append(work_dir + "/App/include")
    include_directory_list.append(IMAGE_INCLUDE)
    include_directory_list.append(RC_INCLUDE)
    include_directory_list.append(work_dir + "/Shared/include")
   
    define_list = [] 
    obj_dir_list = []

    src_dirs = []
    src_dirs.append(work_dir + "/App/src/testbench/")
    src_dirs.append(work_dir + "/App/src/api/")
    src_dirs.append(work_dir + "/Shared/src/")

    ret_status = compileFiles("gcc", src_dirs, work_dir + "/App/obj", cflags, include_directory_list, define_list)
    if(ret_status != 0):
       return 1

    obj_dir_list.append(work_dir + "/App/obj")

    link_flags = " -L" + IMAGE_LIB + " -L" + RC_LIB + " " 
    shared_libs = []
    shared_libs.append("dl")
    shared_libs.append("m")
    shared_libs.append("rt")
    shared_libs.append("ImageApi")
    shared_libs.append("rcApi")
    shared_libs.append("pthread")
    static_libs = []
    ret_status = linkAndBuildExecutable("gcc", "./bin", app_name, obj_dir_list, link_flags, shared_libs, static_libs)
    if(ret_status != 0):
       return 1

    return 0

# make an executable of the software description of the system + tb.
def makeSWExec(exec_name, work_dir, ahir_fn_libs, fpga_count):
    logInfo("in makeSWExec (" + work_dir  +  ")")
    cflags = " -g "

    include_directory_list = []
    include_directory_list.append(work_dir + "/App/include")
    include_directory_list.append(RC_INCLUDE)

    include_directory_list.append(PIPEHANDLER_INCLUDE)
    include_directory_list.append(AHIR_PTHREAD_UTILS_INCLUDE)
    include_directory_list.append(AHIR_FUNCTIONLIB + "/include")
    include_directory_list.append(work_dir + "/Shared/include/")
    include_directory_list.append(work_dir + "/FpgaCode/shared/include")
    include_directory_list.append(work_dir + "/FpgaCode/fpga00/include")

    
    if(fpga_count == 4):
    	include_directory_list.append(work_dir + "/FpgaCode/fpga01/include")
    	include_directory_list.append(work_dir + "/FpgaCode/fpga11/include")
    	include_directory_list.append(work_dir + "/FpgaCode/fpga10/include")
   
    define_list = []
    define_list.append("SW")

    obj_dir_list = []

    src_dirs = []
    src_dirs.append(work_dir + "/App/src/testbench/")
    src_dirs.append(work_dir + "/App/src/api/")
    src_dirs.append(work_dir + "/Shared/src/")
 
    if (len(ahir_fn_libs) > 0):
	src_dirs.append(AHIR_FUNCTIONLIB + "/src")

    ret_status = compileFiles("gcc", src_dirs, work_dir + "/App/objsw", cflags, include_directory_list, define_list)
    if(ret_status != 0):
       return 1

    obj_dir_list.append(work_dir + "/App/objsw")

    # compile all the FPGA-sources.
    fpga_list = []
    fpga_list.append("shared")
    fpga_list.append("fpga00")
    if (fpga_count == 4):
    	fpga_list.append("fpga01")
    	fpga_list.append("fpga11")
    	fpga_list.append("fpga10")

    for fpga in fpga_list:
        fpga_src_dirs = []
	src_dir = work_dir + "/FpgaCode/" + fpga + "/src"
	fpga_src_dirs.append(src_dir)
	obj_dir = work_dir + "/FpgaCode/" + fpga + "/objsw"
    	ret_status = compileFiles("gcc", fpga_src_dirs, obj_dir, cflags, include_directory_list, define_list)
    	if(ret_status != 0):
       		return 1
    	obj_dir_list.append(obj_dir)


    link_flags  = "-L" + PIPEHANDLER_LIB + " "
    link_flags += "-L" + RC_LIB + " "

    shared_libs = []
    shared_libs.append("PipeHandler")
    shared_libs.append("pthread")
    shared_libs.append("HostUtils")
    shared_libs.append("rcApiSW")
    shared_libs.append("rt")
    shared_libs.append("dl")
    shared_libs.append("fpga00")

    if(fpga_count == 4):
    	shared_libs.append("fpga01")
    	shared_libs.append("fpga11")
    	shared_libs.append("fpga10")


    # for the moment no static libs.
    static_libs = []
    ret_status = linkAndBuildExecutable("gcc", work_dir + "/bin", "execSW", obj_dir_list, link_flags, shared_libs, static_libs)
    if(ret_status):
       return 1

    return 0


# C->llvm
def makeC2Llvm(fpga_name):
    logInfo("in makeC2Llvm (" + fpga_name +  ")")

    include_directory_list = []
    include_directory_list.append(RC_INCLUDE)
    include_directory_list.append(PIPEHANDLER_INCLUDE)
    include_directory_list.append(SOCKETLIB_INCLUDE)
    include_directory_list.append(AHIR_PTHREAD_UTILS_INCLUDE)
    include_directory_list.append(AHIR_FUNCTIONLIB + "/include")
    include_directory_list.append("./Shared/include")
    include_directory_list.append("./FpgaCode/shared/include")
    include_directory_list.append("./FpgaCode/" + fpga_name + "/include")

    define_list = []

    src_dirs = []
    src_dirs.append("./Shared/src")
    src_dirs.append("./FpgaCode/shared/src")
    src_dirs.append("./FpgaCode/" + fpga_name + "/src")

    obj_dir = "./FpgaCode/" + fpga_name + "/objhw"
    makeOrCleanDir(obj_dir)
   
    clang_flags = "-std=gnu89 -emit-llvm -c " 
    ret_val = compileFiles("clang", src_dirs, obj_dir, clang_flags, include_directory_list, define_list)
    
    if (ret_val): 
        logError("Error: in converting C to LLVM for " + fpga_name)


    logInfo("optimizing LLVM object files for " + fpga_name)
    for objfile in os.listdir(obj_dir):
	objname,extn = os.path.splitext(objfile)
        if(extn == ".o"):
    		opt_command = "opt -O3 --instnamer " + obj_dir + "/" + objfile + " > " + obj_dir + "/" + objname + ".O"
		logInfo("running optimization:\n\t " + opt_command)
		opt_status = execSysCmd(opt_command)
		if(opt_status != 0):
          		logError("opt-command failed:" + opt_command)
			ret_val = 1
 
    return ret_val
    
# llvm -> Aa
def makeLlvm2Aa(fpga_name,ahir_fn_libs):
    logInfo("in makeLlvm2Aa (" + fpga_name +  ")")
    ret_val = 0


    obj_dir = "./FpgaCode/" + fpga_name + "/objhw/"
    aa_dir  = "./FpgaCode/" + fpga_name + "/Aa/"

    makeOrCleanDir(aa_dir)

    llvm2aa_opts="-extract_do_while=true"

    files_to_link = []
    files_to_link 

    for obj_file in os.listdir(obj_dir):
    	#pdb.set_trace()
        root,ext = os.path.splitext(obj_file) 
        if(ext == ".O"):
            llvm2aa_cmd = "llvm2aa " + llvm2aa_opts + " " + obj_dir + "/" + obj_file + " > " + aa_dir  + "/." + root + ".uaa " 
            logInfo("executing llvm2aa\n\t " + llvm2aa_cmd)
            cmd_stat = execSysCmd(llvm2aa_cmd)
            if(cmd_stat != 0):
		logError("command failed " + llvm2aa_cmd)
                ret_val = 1
	    else:
		fmt_file = "." + root + ".aa"
		format_cmd = "vcFormat < " + aa_dir +  "/." + root + ".uaa " + " > " + aa_dir + "/" + fmt_file
                execSysCmd(format_cmd)
		files_to_link.append(aa_dir + "/" + fmt_file)
                


    if (ret_val): 
        logError("Error: in converting LLVM to Aa for " + fpga_name)
        return 1

    if (len(ahir_fn_libs) > 0):
	for ahir_lib in ahir_fn_libs:
	    files_to_link.append(AHIR_FUNCTIONLIB + "/Aa/" + ahir_lib + ".aa")

    ret_val = makeAaLink(fpga_name,files_to_link)

    return ret_val

# Aa -> Aa
def makeAaLink(fpga_name,files_to_link):

    logInfo("in makeAaLink (" + fpga_name +  ",..)")
    ret_val = 0
    aa_dir = "./FpgaCode/" + fpga_name + "/Aa/"

    aa_link_cmd = "AaLinkExtMem -I 1024 -E default_mem_pool " 
    for aa_file in files_to_link:
       aa_link_cmd +=  " " + aa_file + " "

    if(fpga_name == "fpga00"):
	aa_link_cmd += FPGA00_AA + " " + UPLINK_AA + " "
    elif(fpga_name == "fpga01"):
	aa_link_cmd += FPGA01_AA + " " 
    elif(fpga_name == "fpga11"):
	aa_link_cmd += FPGA11_AA + " " 
    elif(fpga_name == "fpga10"):
	aa_link_cmd += FPGA10_AA + " " 
    
     
    aa_link_cmd += " > " + aa_dir +  "/." + fpga_name + ".laa"
    logInfo("running link command\n\t " + aa_link_cmd)

    cmd_status = execSysCmd(aa_link_cmd)
    if(cmd_status != 0):
	logError("Aa-link command failed: " + aa_link_cmd)
        ret_val = 1

    if(ret_val != 0):
	return 1

    fmt_cmd = "vcFormat < " + aa_dir + "/." + fpga_name + ".laa > " + aa_dir + "/" +  fpga_name + ".aa"
    execSysCmd(fmt_cmd)
    
    return 0

# Aa -> vC
def makeAa2Vc(fpga_name):
    logInfo("in makeAa2Vc (" + fpga_name +  ")")
    ret_val = 0

    aa_dir = "./FpgaCode/" + fpga_name + "/Aa/"
    vc_dir = "./FpgaCode/" + fpga_name + "/vC/"

    aa2vc_cmd = "Aa2VC -O -C " 
    aa2vc_cmd += aa_dir + "/" + fpga_name + ".aa  > " + vc_dir + "/." + fpga_name + ".uvc"
    logInfo("executing command\n\t " + aa2vc_cmd)
    cmd_status = execSysCmd(aa2vc_cmd)
    if (cmd_status != 0): 
        logError("Error: in converting Aa to vC for " + fpga_name)
	ret_val = 1
 
    fmt_cmd = "vcFormat < " + vc_dir + "/." + fpga_name + ".uvc > " + vc_dir + "/" + fpga_name + ".vc"
    logInfo("executing command\n\t " + fmt_cmd)
  
    execSysCmd(fmt_cmd)

    # get rid of some junk.
    execSysCmd("rm -rf vhdlCStubs.*")

    return ret_val

# vC -> VHDL
def makeVc2Vhdl(fpga_name, top_modules, top_daemon_modules, ahir_fn_libs):
    logInfo("in makeVc2Vhdl (" + fpga_name +  ")")
    vhdl_dir = "./FpgaCode/" + fpga_name + "/vhdl"

    cwd_dir = os.getcwd()
    makeOrCleanDir(vhdl_dir)
    os.chdir(vhdl_dir)

    ret_val = 0
   
    vc_dir = "../vC"

    vc2vhdl_cmd = "vc2vhdl -q -a -C -O -e " + fpga_name + " -w -s ghdl " 

    for ahir_lib in ahir_fn_libs:
	vc2vhdl_cmd += " -L " + AHIR_FUNCTIONLIB + "/" +  ahir_lib + ".list "

    top_module_string = ""
    for tm in top_modules:
       vc2vhdl_cmd += " -t " + tm
    for tdm in top_daemon_modules:
       vc2vhdl_cmd  += " -T " + tdm 

    vc2vhdl_cmd += " -f " + vc_dir + "/" + fpga_name + ".vc"
    logInfo("executing vc->vhdl\n\t " + vc2vhdl_cmd)
    cmd_status = execSysCmd(vc2vhdl_cmd)

    if(cmd_status != 0):
	logError("vc2vhdl failed for " + fpga_name)
	os.chdir(cwd_dir)
	return 1
	

    for vf in os.listdir("./"):
        pref,ext = os.path.splitext(vf)
 	if(ext == ".unformatted_vhdl"):
    	    fmt_command = "vhdlFormat < " + vf + " > " + pref + ".vhdl"
	    execSysCmd(fmt_command)

    os.chdir(cwd_dir)
    return ret_val



#     -a <app-name> 
#     -w <work-area>
#     (-t (<fpga-name>:<top-module>)*  (note: multiple top-modules can be specified)
#     (-T (<fpga-name>:<top-daemon-module>)*  (note: multiple top-modules can be specified)
#     (-I  <ahir-function-library-to-include>)*
#     -n  <number-of-FPGAs (1 or 4)> 
#     -f  <type-of-FPGA>  (default is Spartan 3 xc3s5000 as in the IMAGE board).
#     -S  <start-point> (one of { "", build_sw_exec, to_llvm, to_aa, to_vc, to_vhdl, to_hexfiles} ) 
#     -E  <end-point> (one of {build_sw_exec, to_llvm, to_aa, to_vc, to_vhdl} ) 
#     -O  (optimize-flag: use this option to build optimized App).
#     -h  (print help message)
#     -C  (clean/remove all build-products in the work-area)
#     -N  <synth-stage>  (generate post-synth netlists)
#
def parseOptions(opts):
    app_name = ""
    work_area = "./"
    ahir_fn_libs = []
    top_modules_dict = { 'fpga00':[], 'fpga01': [] , 'fpga11': [] , 'fpga10': [] }
    top_daemon_modules_dict = { 'fpga00':[], 'fpga01': [] , 'fpga11': [] , 'fpga10': [] }
    fpga_count = 4
    fpga_type =  "xc3s5000-fg1156-4"
    start_point = ""
    end_point = ""
    optimize_flag = 0
    help_flag = 0
    err_flag  = 0
    clean_flag = 0
    netgen_stage = ""

 
    for option, parameter in opts:
        if option ==  '-a':
 	   app_name = parameter
           logInfo("application-name  = " + parameter + ".")
        elif option ==  '-w':
 	   work_area = parameter
           logInfo("set project work-area = " + parameter + ".")
        elif option ==  '-t':
           fpga_name,module_name = parameter.split(':')
           top_modules_dict[fpga_name].append(module_name)
           logInfo("for " + fpga_name + ", added top-module = " + module_name + ".")
        elif option ==  '-T':
           fpga_name,module_name = parameter.split(':')
           top_daemon_modules_dict[fpga_name].append(module_name)
           logInfo("for "  + fpga_name + " added top-daemon-module = " + module_name + ".")
        elif option == '-f':
           fpga_type = parameter
           logInfo("fpga-type = " + parameter + ".")
        elif option == '-I':
           ahir_fn_libs.append(parameter)
           logInfo("added ahir-function-lib  " + parameter + ".")
        elif option == '-n':
           fpga_count = int(parameter)
	   if ((fpga_count != 1) and (fpga_count != 4)):
             logError("FPGA count must be either 1 or 4")
             err_flag = 1
           else:
             logInfo("fpga-count = " + str(fpga_count) + ".")
        elif option == '-N':
           logInfo("netgen-stage = " + parameter + ".")
	   netgen_stage = parameter
        elif option == '-S':
	   start_point = parameter
           logInfo("start-point = " + parameter + ".")
        elif option == '-E':
	   end_point = parameter
           logInfo("end-point = " + parameter + ".")
        elif option == '-h':
           optimize_flag = 1
        elif option == '-h':
           help_flag = 1
        elif option == '-C':
           clean_flag = 1
    
    return app_name, work_area, top_modules_dict, top_daemon_modules_dict, fpga_count, fpga_type, start_point, end_point, optimize_flag, help_flag, clean_flag, err_flag, ahir_fn_libs, netgen_stage


# The top-level script for the Image RC builder.
#
# Author: Madhav Desai 
#
# Brief Description:
#   The IMAGE RC Builder script automates the compilation
#   of an IMAGE RC project described in the standard form.
#
#   ImageRCBuild.py
#     -a <application-name> (the name of the RC application)
#     -w <project-directory> (the place where the script should run..)
#     (-t  <fpga-name>:<top-module>)*  (note: multiple top-modules can be specified)
#     (-T  <fpga-name>:<top-daemon-module>)*  (note: multiple top-modules can be specified)
#     (-I  <ahir-function-library-to-include>)*
#     -f   <number-of-FPGAs (1 or 4)> 
#     -p   <type-of-FPGA>  (default is Spartan 3 xc3s5000 as in the IMAGE board).
#     -S  <start-point> (one of { "", build_sw_exec, to_llvm, to_aa, to_vc, to_vhdl, to_hexfiles} ) 
#     -E  <end-point> (one of {build_sw_exec, to_llvm, to_aa, to_vc, to_vhdl} ) 
#     -h  (print help message)
#     -C  (clean/remove all build-products in the work-area)
#     (-N  <synth-stage> (post xst/map/par RTL generation) )?
#
def printUsage():
    print ''' 
   ImageRCBuild.py
      -a   app-name (name of the RC app: required)
      -w   work_directory (optional, default is "./")
      (-t  <fpga-name>:<top-module>)*
      (-T  <fpga-name>:<top-daemon-module>)*
                 Note: at least one of the top-module and top-daemon-module sets must be non-empty.
      (-I  <ahir-function-library-to-include>)*
      -n   <number-of-FPGAs (1 or 4)> 
      -f   <type-of-FPGA>
      -S  <start-point> (one of { "", build_sw_exec, to_llvm, to_aa, to_vc, to_vhdl, to_vhdlsim, to_hexfiles, check_timing, to_app} ) 
      -E  <end-point> (one of {build_sw_exec, to_llvm, to_aa, to_vc, to_vhdl, to_vhdlsim, to_hexfiles, check_timing, to_app} ) 
      -O  (optimize-flag:  use option to build optimized App)
      -h  (print help message)
      -C  (clean/remove all build-products in the work-area)
      (-N  <synth-stage> (post xst/map/par RTL generation) )?
          '''
def main():

    image_rc_release = os.environ.get('IMAGERC_RELEASE')
    if(image_rc_release == None):
       logError("environment variable IMAGERC_RELEASE is not defined." )
       return 1

    image_install_dir = os.environ.get('IMAGE_INSTALL_DIR')
    if(image_install_dir == None):
       logError("environment variable IMAGE_INSTALL_DIR is not defined." )
       return 1

    ahir_release = os.environ.get('AHIR_RELEASE')
    if(ahir_release == None):
       logError (" environment variable AHIR_RELEASE is not defined." )
       return 1

    if len(sys.argv) < 2:
       printUsage()
       return 1

    arg_list = sys.argv[1:]
   
    opts,args = getopt.getopt(arg_list,'a:w:t:T:n:f:S:E:hCOI:')
    app_name, work_area, top_modules_dict, top_daemon_modules_dict, number_of_fpgas, fpga_type, start_point, stop_point, optimize_flag, help_flag, clean_flag, err_flag, ahir_fn_libs, netgen_stage = parseOptions(opts)
   
    global command_log_file
    command_log_file = open(work_area + "/executed_command_log.txt","w")

    if(clean_flag):
        cleanWorkArea(work_area)
        command_log_file.close()
	return 0

    if(app_name == ""):
	logError("specify an application name ")
       	printUsage()
        command_log_file.close()
       	return 1

    if((len(top_modules_dict) == 0) and (len(top_daemon_modules_dict) == 0)):
       	logError("top-module and top-daemon-module sets cannot both be empty. ")
        command_log_file.close()
	return 1

    saved_cwd = os.getcwd()
    if(os.path.isdir(work_area) != 1):
       logError("project-directory " + work_area + " not found")
       logError("project directory " + work_area + " not found")
       command_log_file.close()
       return 1
   
    if(err_flag == 1):
        command_log_file.close()
        return 1

    if(help_flag == 1):
        printUsage()
        command_log_file.close()
        return 0

	
    fpga_list = [ "fpga00" ]
    if(number_of_fpgas == 4):
	fpga_list.append("fpga01")
	fpga_list.append("fpga11")
	fpga_list.append("fpga10")

    #     set all the global constants (include-paths, libraries etc. etc.)
    setGlobals(image_install_dir, ahir_release, image_rc_release)

    # change to work-area.
    os.chdir(work_area)


    if((start_point == "") or (start_point == "build_sw_exec")):
        logInfo("building SW executable.")
        ret_val = makeSWExec("execSW", "./", ahir_fn_libs, 4)
        if(ret_val == 1):
           logError("Error: in building software-executable ")
           os.chdir(saved_cwd)
	   command_log_file.close()
           return 1

    if(stop_point == "build_sw_exec"):
        os.chdir(saved_cwd)
	command_log_file.close()
        return 0

   
    if((start_point == "") or (start_point == "build_sw_exec")  or  (start_point == "to_llvm")):
       
        for fpga in fpga_list:
           ret_val = makeC2Llvm(fpga)
           if(ret_val):
              os.chdir(saved_cwd)
	      command_log_file.close()
              return 1
    
    if(stop_point == "to_llvm"):
        os.chdir(saved_cwd)
	command_log_file.close()
	return 0

    if((start_point == "") or (start_point == "build_sw_exec")  or (start_point == "to_llvm") or (start_point == "to_aa")):
        for fpga in fpga_list:
            ret_val = makeLlvm2Aa(fpga, ahir_fn_libs)
            if(ret_val):
              os.chdir(saved_cwd)
	      command_log_file.close()
              return 1
    
    if(stop_point == "to_aa"):
        os.chdir(saved_cwd)
	command_log_file.close()
	return 0

    if((start_point == "") or (start_point == "build_sw_exec")  or 
               (start_point == "to_llvm") or (start_point == "to_aa") or (start_point == "to_vc")):
	for fpga in fpga_list:
       	  ret_val = makeAa2Vc(fpga)
          if(ret_val):
             os.chdir(saved_cwd)
	     command_log_file.close()
             return 1
    
    if(stop_point == "to_vc"):
        os.chdir(saved_cwd)
        command_log_file.close()
	return 0

    if((start_point == "") or (start_point == "build_sw_exec")  or 
               (start_point == "to_llvm") or (start_point == "to_aa") or (start_point == "to_vc") or (start_point == "to_vhdl")):
        for fpga in fpga_list:
          ret_val = makeVc2Vhdl(fpga, top_modules_dict[fpga], top_daemon_modules_dict[fpga], ahir_fn_libs)
          if(ret_val):
             os.chdir(saved_cwd)
             command_log_file.close()
             return 1
    

    if(stop_point == "to_vhdl"):
        os.chdir(saved_cwd)
        command_log_file.close()
	return 0

    if((start_point == "") or (start_point == "build_sw_exec")  or (start_point == "to_llvm") or 
			(start_point == "to_aa") or (start_point == "to_vc") or (start_point == "to_vhdl") or (start_point == "to_vhdlsim")):
	ret_val = makeVhdlSim(number_of_fpgas)

    if(stop_point == "to_vhdlsim"):
        os.chdir(saved_cwd)
        command_log_file.close()
	return 0
    
    if((start_point == "") or (start_point == "build_sw_exec")  or (start_point == "to_llvm") or 
			(start_point == "to_aa") or (start_point == "to_vc") or (start_point == "to_vhdl") or 
			(start_point == "to_vhdlsim") or (start_point == "to_hexfiles")):
	# clean up the hexfiles area.
        execSysCmd("rm -rf ./hexfiles/*")
        for fpga in fpga_list:
          ret_val = makeHexFile(number_of_fpgas, fpga, fpga_type)
          if(ret_val):
            os.chdir(saved_cwd)
            command_log_file.close()
            return 1
	  if(netgen_stage != ""):
	    ret_val = postSynthNetgen(fpga, netgen_stage)
            if(ret_val):
	       os.chdir(saved_cwd)
               command_log_file.close()
               return 1
         

        if(number_of_fpgas == 1):
          ret_val = copyDummyHexFiles(fpga_type)
          if(ret_val):
            os.chdir(saved_cwd)
            command_log_file.close()
            return 1

    if(stop_point == "to_hexfiles"):
        os.chdir(saved_cwd)
        command_log_file.close()
	return 0

    if((start_point == "") or (start_point == "build_sw_exec")  or (start_point == "to_llvm") or 
			(start_point == "to_aa") or (start_point == "to_vc") or (start_point == "to_vhdl") or 
			(start_point == "to_vhdlsim") or (start_point == "to_hexfiles") or (start_point == "check_timing")):
        for fpga in fpga_list:
          ret_val = checkTiming(fpga)
          if(ret_val):
            os.chdir(saved_cwd)
            command_log_file.close()
            return 1

    # board-clock-div-count will be set to 1 by default. Advise the user
    # to modify it manually if things dont work the first time.
    execSysCmd("echo 1 >> ./hexfiles/.BoardClkDivCount.txt")

    if(stop_point == "check_timing"):
        command_log_file.close()
	return 0
    

    if((start_point == "") or (start_point == "build_sw_exec")  or (start_point == "to_llvm") or 
			(start_point == "to_aa") or (start_point == "to_vc") or (start_point == "to_vhdl") or 
			(start_point == "to_vhdlsim") or (start_point == "to_hexfiles") or (start_point == "check_timing") or 
			(start_point == "to_app")):
	ret_val = makeAppTb(app_name, optimize_flag)
	if(ret_val != 0):
            os.chdir(saved_cwd)
            command_log_file.close()
            return 1
	ret_val = makeAppSharedLibrary(app_name)
	if(ret_val != 0):
            os.chdir(saved_cwd)
            command_log_file.close()
            return 1

    os.chdir(saved_cwd)
    command_log_file.close()
    return 0

if __name__ == '__main__':
    ret_val = main()
    sys.exit(ret_val)
