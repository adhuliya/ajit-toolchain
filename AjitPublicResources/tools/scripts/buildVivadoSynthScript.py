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
    print ("Setting globals")

    global AHIR_RELEASE
    global AHIR_IEEE_LIBRARY
    global AHIR_LIBRARY
    global AJIT_CUSTOM_VHDL
    global FPGA_PART
    
    AHIR_RELEASE = os.environ.get('AHIR_RELEASE')
    AHIR_IEEE_LIBRARY = AHIR_RELEASE + "/vhdl/aHiR_ieee_proposed.vhdl"
    AHIR_LIBRARY = AHIR_RELEASE + "/vhdl/ahir.vhdl"

    AJIT_PROJECT_HOME = os.environ.get('AJIT_PROJECT_HOME')
    AJIT_CUSTOM_VHDL  = AJIT_PROJECT_HOME + "/processor/vhdl/lib/AjitCustom.vhdl"

    FPGA_PART = None

    #
    ########## for ml605 ##########
    if (fpga_board == "ml605"):
    	FPGA_PART =  "xc6vlx240t-ff1156-1"
        print ("FPGA part set to " + FPGA_PART)
    #
    ########## for vc709 ##########
    if (fpga_board == "vc709"):
    	FPGA_PART = "xc7vx690t-ffg1761-2"
        print ("FPGA part set to " + FPGA_PART)
    #
    ########## for KC705 ##########
    if (fpga_board == "kc705"):
    	FPGA_PART = "xc7k325t-ffg900-2"
        print ("FPGA part set to " + FPGA_PART)
   
    

def display_usage():
    print ("\n VHDL file is not provided. Please use\n")
    print ("$  buildVivadoSynthScript.py -r <root-directory>  -t <top-entity-name> \n")
    print ("     -r <root-directory>  look for vhdl files under this directory for synthesis \n")
    print ("     -t <top-entity-name> top entity name \n")
    print ("     -f <fpga-part> top entity name \n")


def main ():

    SetGlobals()

    top_entity_name = None
    root_directory_path  = None

    if(AHIR_RELEASE == None):
        logError (" environment variable AHIR_RELEASE is not defined." )
        return 1
       

    if (len(sys.argv) < 2 ): 
        display_usage()
        return 1
    else :
        arg_list = sys.argv[1:]
        opts,args = getopt.getopt(arg_list,'r:t:hf:')
        for option, parameter in opts:
            if option ==  '-r':
                root_directory_path = parameter
                print "Info: set root directory path to "  + root_directory_path
            if option ==  '-h':
                display_usage()
                return 0
            if option ==  '-t':
                top_entity_name = parameter
                print "Info: set top entity name to "  + top_entity_name
            if option ==  '-f':
                O_FPGA_PART = parameter
                print "Info: set FPGA part id to "  + O_FPGA_PART

    if(FPGA_PART == None):
        logError (" environment variable fpga_board is not defined." )
        return 1
                
    tcl_file = open (top_entity_name + ".vivado_synth.tcl","w")

    print >>  tcl_file, "set AHIR_RELEASE $::env(AHIR_RELEASE)"
    print >>  tcl_file, "set AJIT_PROJECT_HOME $::env(AJIT_PROJECT_HOME)"

    
    print >> tcl_file, "read_vhdl -library aHiR_ieee_proposed " + "$AHIR_RELEASE/vhdl/aHiR_ieee_proposed.vhdl" 
    print >> tcl_file, "read_vhdl -library ahir " + "$AHIR_RELEASE/vhdl/ahir.vhdl" 
    print >> tcl_file, "read_vhdl -library simpleUartLib " + "$AJIT_PROJECT_HOME/processor/vhdl/lib/simpleUartLib.vhdl" 
    print >> tcl_file, "read_vhdl -library AjitCustom " + "$AJIT_PROJECT_HOME/processor/vhdl/lib/AjitCustom.vhdl" 

    for root, dirs, files in os.walk(root_directory_path, topdown=False, followlinks=True):
        for name in dirs:
           if(name == "vhdl"):
              full_name = os.path.join(root, name)
              for vhdl_lib in os.listdir(full_name):
                  vhdl_lib_dir = os.path.join(full_name, vhdl_lib)
                  if(os.path.isdir(vhdl_lib_dir)):
                     for vhdl_file in os.listdir(vhdl_lib_dir):
                        root, ext = os.path.splitext(vhdl_file) 
                        if((ext == ".vhdl") and (not "_test_bench" in root)):
                            full_vhdl_file_path = os.path.join(vhdl_lib_dir, vhdl_file)
			    print >> tcl_file, "read_vhdl -library " + vhdl_lib + " " + full_vhdl_file_path
                 
    xdc_file = open ("clocking.xdc","w")
    print >> xdc_file, "create_clock -add -name clk -period 10.00 -waveform {0 5}   [get_ports clk]"

    print >> tcl_file, "read_xdc ./clocking.xdc "
    print >> tcl_file, "synth_design -mode out_of_context -fsm_extraction off -top " + top_entity_name + " -part " +  FPGA_PART 
    print >> tcl_file, "write_edif -force " + top_entity_name + ".edn"
    print >> tcl_file, "report_timing_summary -file timing.postsynth.rpt -nworst 10"
    print >> tcl_file, "report_utilization -file utilization_post_synth.rpt"
    print >> tcl_file, "report_utilization -hierarchical -file utilization_post_synth.hierarchical.rpt"
        
    return 0





if __name__ == '__main__':
    ret = main()
    sys.exit(ret)
