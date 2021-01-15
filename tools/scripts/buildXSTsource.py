#!/usr/bin/env python

# Generates the .scr and .prj files necessary for Xilinx synthesis tool
# Written by : Titto Thomas
# Date : 4/12/2015


import os
import sys
import getopt
import os.path


current_dir = os.getcwd()
fpga_board = os.environ.get('fpga_board')

def logError(mesg):
    print ("Error: " + mesg)

def SetGlobals():
    global AHIR_RELEASE
    global AHIR_IEEE_LIBRARY
    global AHIR_LIBRARY
    
    AHIR_RELEASE = os.environ.get('AHIR_RELEASE')
    AHIR_IEEE_LIBRARY = AHIR_RELEASE + "/vhdl/aHiR_ieee_proposed.vhdl"
    AHIR_LIBRARY = AHIR_RELEASE + "/vhdl/ahir.vhdl"

def display_usage():
    print ("\n VHDL file is not provided. Please use\n")
    print ("$  buildXSTsource -s <input file name> -l <library name>\n")


def generatePRJ(vhdl_file, library_name):
    prj_file_name = ((os.path.split(vhdl_file)[1]).split("."))[0]
    
    if library_name == None :
        library_name = ((os.path.split(vhdl_file)[0]).split("/"))[-1]    

    prj_file = open( prj_file_name + ".prj","w")
    print >> prj_file, "vhdl aHiR_ieee_proposed " + AHIR_IEEE_LIBRARY
    print >> prj_file, "vhdl ahir " + AHIR_LIBRARY
    
    print >> prj_file, "vhdl " + library_name + " " + vhdl_file
    
    prj_file.close()
    
def generateSCR(vhdl_file, system_top):
    prj_file_name = ((os.path.split(vhdl_file)[1]).split("."))[0]
    library_name = ((os.path.split(vhdl_file)[0]).split("/"))[-1]
    
    scr_file = open( prj_file_name + ".scr","w")
    
    print >> scr_file, "run"
    #
    ########## for ml605 ##########
    if (fpga_board == "ml605"):
    	print >> scr_file, "-p xc6vlx240t-ff1156-1"
    #
    ########## for vc709 ##########
    if (fpga_board == "vc709"):
    	print >> scr_file, "-p xc7vx690t-ffg1761-2"
    #
    ########## for KC705 ##########
    if (fpga_board == "kc705"):
    	print >> scr_file, "-p xc7k325t-ffg900-2"
    #
    print >> scr_file, "-top " + prj_file_name
    print >> scr_file, "#-uc pcie.xcf"
    print >> scr_file, "-ifn ./" + prj_file_name + ".prj"
    print >> scr_file, "-ofn " + prj_file_name + ".ngc"
    print >> scr_file, "-opt_mode Speed"
    print >> scr_file, "-opt_level 1"
    print >> scr_file, "-power NO"
    print >> scr_file, "-max_fanout 16"
    print >> scr_file, "-iuc NO"
    print >> scr_file, "-ifmt mixed"
    if system_top:
        print >> scr_file, "-iobuf YES"
    else:
        print >> scr_file, "-iobuf NO"
    print >> scr_file, "-keep_hierarchy NO"
    print >> scr_file, "-use_new_parser yes"
    print >> scr_file, "-netlist_hierarchy As_Optimized"
    print >> scr_file, "-rtlview Yes"
    print >> scr_file, "-glob_opt AllClockNets"
    print >> scr_file, "-read_cores YES"
    print >> scr_file, "-write_timing_constraints NO"
    print >> scr_file, "-cross_clock_analysis NO"
    print >> scr_file, "-hierarchy_separator /"
    print >> scr_file, "-bus_delimiter <>"
    print >> scr_file, "-case Maintain"
    print >> scr_file, "-slice_utilization_ratio 100"
    print >> scr_file, "-bram_utilization_ratio 100"
    print >> scr_file, "-dsp_utilization_ratio 100"
    print >> scr_file, "-lc Auto"
    print >> scr_file, "-reduce_control_sets Auto"
    print >> scr_file, "-fsm_extract No -fsm_encoding Auto"
    print >> scr_file, "-safe_implementation Yes"
    print >> scr_file, "-fsm_style LUT"
    print >> scr_file, "-ram_extract Yes"
    print >> scr_file, "-ram_style Block"
    print >> scr_file, "-rom_extract Yes"
    print >> scr_file, "-shreg_extract Yes"
    print >> scr_file, "-rom_style Auto"
    print >> scr_file, "-auto_bram_packing NO"
    print >> scr_file, "-resource_sharing NO"
    print >> scr_file, "-async_to_sync NO"
    print >> scr_file, "-shreg_min_size 2"
    print >> scr_file, "-use_dsp48 NO"
    print >> scr_file, "-bufg 32"
    print >> scr_file, "-register_duplication YES"
    print >> scr_file, "-register_balancing Forward"
    print >> scr_file, "-move_first_stage Yes"
    print >> scr_file, "-move_last_stage Yes"
    print >> scr_file, "-optimize_primitives NO"
    print >> scr_file, "-use_clock_enable Auto"
    print >> scr_file, "-use_sync_set Auto"
    print >> scr_file, "-use_sync_reset Auto"
    print >> scr_file, "-iob Auto"
    print >> scr_file, "-equivalent_register_removal Yes"
    print >> scr_file, "-slice_utilization_ratio_maxmargin 5"
    scr_file.close()

def main ():
    SetGlobals()
    lib_name = None
    system_top = False
    if(AHIR_RELEASE == None):
        logError (" environment variable AHIR_RELEASE is not defined." )
        return 1
       
    if (len(sys.argv) < 2 ): 
        display_usage()
        return 1
    else :
        arg_list = sys.argv[1:]
        opts,args = getopt.getopt(arg_list,'l:s:h,t')
        for option, parameter in opts:
            if option ==  '-l':
                lib_name = parameter
            if option ==  '-s':
                file_path = parameter
            if option ==  '-h':
                display_usage()
                return 0
            if option ==  '-t':
                system_top = True
                
    vhdl_file_path = current_dir + "/" + file_path
    
    if ((fpga_board != "kc705") and (fpga_board != "vc709") and (fpga_board != "ml605")):
       print ("Error: Board not specified, source it through exports.sh")
       sys.exit(1)

    generatePRJ(vhdl_file_path, lib_name)
    generateSCR(vhdl_file_path, system_top)
        
    return 0





if __name__ == '__main__':
    ret = main()
    sys.exit(ret)
