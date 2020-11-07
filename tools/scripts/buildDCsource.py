#!/usr/bin/env python

# Generates the .tcl files necessary for Design Compiler synthesis tool
# Written by : Ch V kalyani
# Date : 06/08/2016


import os
import sys
import getopt
import os.path


current_dir = os.getcwd()

def logError(mesg):
    print "Error: " + mesg

def SetGlobals():
    global AHIR_RELEASE
    global AHIR_IEEE_LIBRARY
    global AHIR_LIBRARY
    global SCL_LIB1
    global SCL_LIB2
    global SCL_LIB3
    global SCL_LIB4
    global SCL_LIB5
    global SCL_LIB6
    global SCL_LIB7
    global SCL_LIB8
    global WORK_AREA
    global AJIT_PROJECT_HOME
    AJIT_PROJECT_HOME=os.environ.get('AJIT_PROJECT_HOME')
    AHIR_RELEASE = os.environ.get('AHIR_RELEASE')
    AHIR_IEEE_LIBRARY = AHIR_RELEASE + "/vhdl/No_Asserts/aHiR_ieee_proposed.vhdl"
    AHIR_LIBRARY = AHIR_RELEASE + "/vhdl/No_Asserts/ahir.vhdl"
    SCL_LIB1 = AHIR_RELEASE + "/tech_lib/tsl18fs120_scl_ss.db "
    SCL_LIB2 = AHIR_RELEASE + "/tech_lib/tsl18_memory_max_16_4.db "
    SCL_LIB3 = AHIR_RELEASE + "/tech_lib/spram_32_16_max.db "
    SCL_LIB4 = AHIR_RELEASE + "/tech_lib/obc11_256x8_max.db "
    SCL_LIB5 = AHIR_RELEASE + "/tech_lib/tsl18_memory_max_512_24.db "
    SCL_LIB6 = AHIR_RELEASE + "/tech_lib/obc11_dpram_16x8_max.db "
    SCL_LIB7 = AHIR_RELEASE + "/tech_lib/tsl18_memory_max_DP_16x4.db "
    SCL_LIB8 = AHIR_RELEASE + "/tech_lib/tsl18_memory_max_DP_32x8.db "
    WORK_AREA= AJIT_PROJECT_HOME +"/processor/Aa_v3/work"

def display_usage():
    print "\n VHDL file is not provided. Please use\n"
    print "$  buildDCsource.py -l <library name> -s <input file name> \n"
    print " -p <clock period> -g <sgib y/n> -m <mode - alltogether(a)/ individual(i) synthesis and integrate>"
    print " -h <no parameter required. used to get help> \n"
    print " -t <no parameter required. specify if the current design is top module>\n"

    
def generateTCL(vhdl_file, system_top, clock_period, library_name, sgib, mode ):
    prj_file_name = ((os.path.split(vhdl_file)[1]).split("."))[0]
        
    tcl_file = open( "syn.tcl","a")
    print >> tcl_file, "set design "+ prj_file_name  
    print >> tcl_file, "set_svf " + prj_file_name +".svf"
    print >> tcl_file, "set target_library " + "\"" + SCL_LIB1 + SCL_LIB2 + SCL_LIB3 + SCL_LIB4+ SCL_LIB5 + SCL_LIB6 + SCL_LIB7 + SCL_LIB8 + "\""
    print >> tcl_file, "set link_library "  + "\"" + SCL_LIB1 + SCL_LIB2 + SCL_LIB3 + SCL_LIB4+ SCL_LIB5 + SCL_LIB6 + SCL_LIB7 + SCL_LIB8 + "\""

    print >> tcl_file, "define_design_lib default -path " +WORK_AREA 
   
    print >> tcl_file, "set clock_pin clk "
    print >> tcl_file, "set clk_period " + clock_period
    print >> tcl_file, "define_design_lib aHiR_ieee_proposed -path " + WORK_AREA + "/aHiR_ieee_proposed " 
    print >> tcl_file, "define_design_lib ahir -path " + WORK_AREA + "/ahir " 
    print >> tcl_file, "define_design_lib AjitCustom -path " + WORK_AREA + "/AjitCustom" 
    print >> tcl_file, "define_design_lib "+ library_name + " -path " + WORK_AREA + "/"+ library_name
    print >> tcl_file, "analyze -format vhdl -library aHiR_ieee_proposed " + AHIR_IEEE_LIBRARY
    print >> tcl_file, "analyze -format vhdl -library ahir " + AHIR_LIBRARY
    print >> tcl_file, "analyze -format vhdl -library AjitCustom " + AJIT_PROJECT_HOME + "/processor/vhdl/lib/AjitCustomForAsic.vhdl"
    print >> tcl_file, "analyze -format vhdl -library " + library_name +" "+ vhdl_file
    
    if (system_top == True):
    	print >> tcl_file, "source top.tcl"
    print >> tcl_file, "elaborate  $design -library " + library_name
    print >> tcl_file, "link"
    #after SGIB

    if sgib == 'y':
	 print >> tcl_file, "set SGIB [get_designs *SplitGuardInterfaceBase*]"
	 print >> tcl_file, "foreach_in_collection a $SGIB {"
	 print >> tcl_file, "current_design $a" 
	 print >> tcl_file, "rename_design $a -prefix ${design}_ }"
	 print >> tcl_file, "set SGIB_rename [get_designs *SplitGuardInterfaceBase*]"
	 print >> tcl_file, "foreach_in_collection a $SGIB_rename {"
	 print >> tcl_file, "current_design $a" 
	 print >> tcl_file, "global clock_pin"
    	 print >> tcl_file, "set clk_pin clk"
    	 print >> tcl_file, "set clk_name $clock_pin"
    	 print >> tcl_file, "create_clock -period $clk_period $clk_name"
    	 print >> tcl_file, "set input_delay_ns [expr $clk_period / 2]"
    	 print >> tcl_file, "set output_delay_ns [expr $clk_period / 2]"
    	 print >> tcl_file, "set clk_latency [expr $clk_period / 3]"
    	 print >> tcl_file, "set clk_uncertainty [expr $clk_period / 10]"
    	 print >> tcl_file, "set vperiod $clk_period"
    	 print >> tcl_file, "set vclk_uncertainty $clk_uncertainty"
    	 print >> tcl_file, "set clk_name vclk"
    	 print >> tcl_file, "create_clock -period $vperiod -name $clk_name"
    	 print >> tcl_file, "set_input_delay $input_delay_ns -clock vclk [remove_from_collection [all_inputs] $clock_pin]"
    	 print >> tcl_file, "set_output_delay $output_delay_ns -clock vclk [all_outputs]"
    	 print >> tcl_file, "set_clock_uncertainty -from $clk_name -to $clk_name $clk_uncertainty"
    	 print >> tcl_file, "set_clock_uncertainty -from vclk -to $clk_name $vclk_uncertainty"
    	 print >> tcl_file, "set_clock_uncertainty -from $clk_name -to vclk $vclk_uncertainty"
    	 print >> tcl_file, "set_clock_uncertainty -from vclk -to vclk $vclk_uncertainty"
    	 print >> tcl_file, "compile -map_effort medium"
	 print >> tcl_file, "set QB [get_designs -hierarchical QueueBase*]"
	 print >> tcl_file, "foreach_in_collection b $QB {" 
	 print >> tcl_file, "rename_design $b -prefix ${design}_ }"
	 print >> tcl_file, "set_dont_touch $a }"
    
   
    print >> tcl_file,"current_design " + prj_file_name 
   
    if (mode == 'i' or system_top == True):
	print >> tcl_file, "ungroup -all -flatten "
        print >> tcl_file, "uniquify"
    	print >> tcl_file, "global clock_pin"
    	print >> tcl_file, "set clk_pin clk"
    	print >> tcl_file, "set clk_name $clock_pin"
    	print >> tcl_file, "create_clock -period $clk_period $clk_name"
    	print >> tcl_file, "set input_delay_ns [expr $clk_period / 2]"
    	print >> tcl_file, "set output_delay_ns [expr $clk_period / 2]"
    	print >> tcl_file, "set clk_latency [expr $clk_period / 3]"
    	print >> tcl_file, "set clk_uncertainty [expr $clk_period / 10]"
    	print >> tcl_file, "set vperiod $clk_period"
    	print >> tcl_file, "set vclk_uncertainty $clk_uncertainty"
    	print >> tcl_file, "set clk_name vclk"
    	print >> tcl_file, "create_clock -period $vperiod -name $clk_name"
    	print >> tcl_file, "set_input_delay $input_delay_ns -clock vclk [remove_from_collection [all_inputs] $clock_pin]"
    	print >> tcl_file, "set_output_delay $output_delay_ns -clock vclk [all_outputs]"
    	print >> tcl_file, "set_clock_uncertainty -from $clk_name -to $clk_name $clk_uncertainty"
    	print >> tcl_file, "set_clock_uncertainty -from vclk -to $clk_name $vclk_uncertainty"
    	print >> tcl_file, "set_clock_uncertainty -from $clk_name -to vclk $vclk_uncertainty"
    	print >> tcl_file, "set_clock_uncertainty -from vclk -to vclk $vclk_uncertainty"
    	print >> tcl_file, "compile -map_effort medium"
        print >> tcl_file, "write -f verilog -hier -output ./op_data_"+clock_period+"ns/${design}.v"
        print >> tcl_file, "write -f vhdl -hier -output ./op_data_"+clock_period+"ns/${design}.vhd"
        print >> tcl_file, "write_sdc -version 1.2 ./op_data_"+clock_period+"ns/${design}.sdc"
        print >> tcl_file, "report_timing -nets -cap -transition -nworst 1  -max_paths 10 > ./reports_"+clock_period+"ns/timing_full.rpt"
        print >> tcl_file, "report_timing -nets -cap -transition -nworst 1  -max_paths 10 > ./reports_"+clock_period+"ns/timing_reg2reg.rpt"
        print >> tcl_file, "report_timing -loops -max_paths 50 > ./reports_"+clock_period+"ns/loops.rpt"
        print >> tcl_file, "report_area > ./reports_"+clock_period+"ns/area.rpt"
    	print >> tcl_file, "report_constraint -all_violators > ./reports_"+clock_period+"ns/constraint.rpt"
    	print >> tcl_file, "report_cell > ./reports_"+clock_period+"ns/cell.rpt"
    	print >> tcl_file, "report_power > ./reports_"+clock_period+"ns/power.rpt"
	print >> tcl_file, "report_nets > ./reports_"+clock_period+"ns/cap.rpt"
    print >> tcl_file, "write -f ddc -hier -output ./${design}.ddc"
    if ((system_top == True)):
	print >> tcl_file, "gui_start"
    else:
    	print >> tcl_file, "quit"
    tcl_file.close()


def main ():
    SetGlobals()
    lib_name = None
    system_top = False
    if(AHIR_RELEASE == None):
        logError (" environment variable AHIR_RELEASE is not defined." )
        return 1
       
    if (len(sys.argv) < 4 ): 
        display_usage()
        return 1
    else :
        arg_list = sys.argv[1:]
        opts,args = getopt.getopt(arg_list,'l:s:p:g:m:h,t')
        for option, parameter in opts:
            if option ==  '-l':
                lib_name = parameter
            if option ==  '-s':
                file_path = parameter
            if option == '-p':
            	period = parameter
	    if option ==  '-g':
                sgib = parameter
	    if option == '-m':
		mode = parameter
            if option ==  '-h':
                display_usage()
		return 0
            if option ==  '-t':
                system_top = True
            
                
    vhdl_file_path = current_dir + "/" + file_path
  
    generateTCL(vhdl_file_path, system_top, period, lib_name, sgib, mode)
        
    return 0





if __name__ == '__main__':
    ret = main()
    sys.exit(ret)
