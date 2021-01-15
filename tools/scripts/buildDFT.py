#!/usr/bin/env python

# Generates the .tcl files necessary for topographical synthesis using Design Compiler.
# Written by : Ch V kalyani
# Date : 23/04/2017


import os
import sys
import getopt
import os.path


current_dir = os.getcwd()

def logError(mesg):
    print "Error: " + mesg

def SetGlobals():
    global SCL_LIB1
    global SCL_LIB2
    global SCL_LIB3
    global SCL_LIB4
    global SCL_LIB5
    global SCL_LIB6
    global SCL_LIB7
    global SCL_LIB8
    global SCL_LIB9
    global SCL_LIB10
    global SCL_LIB11
    global SCL_LIB12
    global SCL_LIB13
    global SCL_LIB14
    global SCL_LIB15
    global SCL_LIB16
    global SCL_LIB17
    global SCL_LIB18
    global WORK_AREA
    global AJIT_ASIC_TAPEOUT_HOME

    #AJIT_ASIC_TAPEOUT_HOME=os.environ.get('AJIT_ASIC_TAPEOUT_HOME')
  


    SCL_LIB1 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/tsl18fs120_scl_ss.db "
    SCL_LIB2 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/tsl18_memory_max_16_4.db "
    SCL_LIB3 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/spram_32_16_max.db "
    SCL_LIB4 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/obc11_256x8_max.db "
    SCL_LIB5 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/tsl18_memory_max_512_24.db "
    SCL_LIB6 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/obc11_dpram_16x8_max.db "
    SCL_LIB7 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/tsl18_memory_max_DP_16x4.db "
    SCL_LIB8 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/tsl18_memory_max_DP_32x8.db "
    SCL_LIB9 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/tsl18fs120_scl_ff.db "
    SCL_LIB10 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/tsl18_memory_min_16_4.db "
    SCL_LIB11 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/tsl18_memory_min_SP_32x16.db "
    SCL_LIB12 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/obc11_256x8_min.db "
    SCL_LIB13 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/tsl18_memory_min_512_24.db "
    SCL_LIB14 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/obc11_dpram_16x8_min.db "
    SCL_LIB15 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/tsl18_memory_min_DP_16x4.db "
    SCL_LIB16 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/tsl18_memory_min_DP_32x8.db "
    SCL_LIB17 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/tsl18cio250_max.db "
    SCL_LIB18 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/tsl18cio250_min.db "

    WORK_AREA= "[pwd]/work"

def display_usage():
    print "\n Correct usage of the script is given below\n "
    print " $ buildDFT.py -l <library name> -d <design name> -p <clock period> -t <top y/n> \n"
    print "     with -d possible options: iunit/fpunit/cpu/icache/dcache/mmu/chip_with_io \n"
    print " -h <no parameter required. used to get help> \n"
    print " Note: IO pads are added to the design if the -t option is specified as 'y'"
    
    
def generateTCL(design, clock_period, library_name, top, hierarchical):
           
    if hierarchical:
        tcl_file_name = "dft_" + design + "_" + clock_period + "_" + top +  "_hierarchical.tcl" 
    else:
        tcl_file_name = "dft_" + design + "_" + clock_period + "_" + top +  ".tcl" 

    tcl_file = open(tcl_file_name,"w")
    print >> tcl_file, "set AJIT_ASIC_TAPEOUT_HOME $::env(AJIT_ASIC_TAPEOUT_HOME)"
    print >> tcl_file, "# setting the top-level design for the synthesis"
    print >> tcl_file, "set design "+ design
    print >> tcl_file, "\n# setting the name of svf file that is going to be used in Formality"  
    print >> tcl_file, "set_svf " + design +".svf\n"
    print >> tcl_file, "# search path for the liberty and layer map files in the Ajit repository"  
    print >> tcl_file, "set_app_var search_path {$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files $AJIT_ASIC_TAPEOUT_HOME/tech/scl180/tech_topo}\n"
    
    print >> tcl_file, "# specifying the target and link libraries for the synthesis"  
    print >> tcl_file, "set target_library " "\"" + SCL_LIB1 + SCL_LIB2 + SCL_LIB3 + SCL_LIB4+ SCL_LIB5 + SCL_LIB6 + SCL_LIB7 + SCL_LIB8 + SCL_LIB17 + SCL_LIB18 + "\""
    print >> tcl_file, "set link_library $target_library \n"
    
    print >> tcl_file, "# setting both max and min libraries for worst case timing analysis"   
    print >> tcl_file, "set_min_library " + SCL_LIB1 + " -min_version " + SCL_LIB9
    print >> tcl_file, "set_min_library " + SCL_LIB2 + " -min_version " + SCL_LIB10
    print >> tcl_file, "set_min_library " + SCL_LIB3 + " -min_version " + SCL_LIB11
    print >> tcl_file, "set_min_library " + SCL_LIB4 + " -min_version " + SCL_LIB12
    print >> tcl_file, "set_min_library " + SCL_LIB5 + " -min_version " + SCL_LIB13
    print >> tcl_file, "set_min_library " + SCL_LIB6 + " -min_version " + SCL_LIB14
    print >> tcl_file, "set_min_library " + SCL_LIB7 + " -min_version " + SCL_LIB15

    print >> tcl_file, "set_min_library " + SCL_LIB8 + " -min_version " + SCL_LIB16
    print >> tcl_file, "set_min_library " + SCL_LIB17 + " -min_version " + SCL_LIB18
    print >> tcl_file, "# setting the layer map and tluplus files"  
    print >> tcl_file, "set_tlu_plus_files -max_tluplus $AJIT_ASIC_TAPEOUT_HOME/tech/scl180/tech_topo/RCE_TS18SL_SCL_STAR_RCXT_4M1L_TYP.tlup -tech2itf_map $AJIT_ASIC_TAPEOUT_HOME/tech/scl180/tech_topo/RCE_TS18SL_SCL_STAR_RCXT_4M1L_TYP.map\n"
    # tech files hardwired to SCL 180nm... Need to make this more generic..
    topo_tech_file = "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/tech_topo/tsl18l4_30_ApII.tf"
    mw_reference_lib_io = "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/io_n_std/tsl18cio150_4lm_dv"
    mw_reference_lib_std = "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/io_n_std/tsl18fs120_4lm_fr"
    mw_memories = "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/memories_mw/milkyway" 
    mw_memories_obc11_256x8 = "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/memories_mw/obc11_256x8" 
    mw_memories_obc11_dpram_16x8 = "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/memories_mw/obc11_dpram_16x8" 
    mw_memories_spram_32x16 = "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/memories_mw/spram_32x16" 
    mw_memories_spram_512x24 = "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/memories_mw/spram_512X24" 
    mw_memories_spram_16x4 = "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/memories_mw/SPRAM_16x4" 

    print >> tcl_file, "# creating the milkyway physical library for floorplan generation of the design "  
    print >> tcl_file, "create_mw_lib -technology "+ topo_tech_file + " -mw_reference_library {"+ mw_reference_lib_io + " " + mw_reference_lib_std + " " + mw_memories + " " + mw_memories_obc11_256x8 + " " + mw_memories_obc11_dpram_16x8 + " " + mw_memories_spram_32x16 + " " + mw_memories_spram_512x24 + " " + mw_memories_spram_16x4 + "}  syn_topo\n"

    print >> tcl_file, "open_mw_lib syn_topo\n"

    if design == "cpu" and hierarchical:
       print >> tcl_file, "set_top_implementation_options -block_references {fpunit iunit}"
       iunit_ddc =  "./iunit_" + clock_period + "_op_data/iunit.ddc"
       fpunit_ddc =  "./fpunit_" + clock_period + "_op_data/fpunit.ddc"
       print >> tcl_file, "read_ddc " + iunit_ddc
       print >> tcl_file, "read_ddc " + fpunit_ddc

    if design == "chip_with_io":
       if hierarchical:
          print >> tcl_file, "set_top_implementation_options -block_references {cpu icache dcache mmu fpunit iunit}"
          iunit_ddc =  "./iunit_" + clock_period + "_op_data/iunit.ddc"
          fpunit_ddc =  "./fpunit_" + clock_period + "_op_data/fpunit.ddc"
          icache_ddc =  "./icache_" + clock_period + "_op_data/icache.ddc"
          dcache_ddc =  "./dcache_" + clock_period + "_op_data/dcache.ddc"
          mmu_ddc =  "./mmu_" + clock_period + "_op_data/mmu.ddc"
          cpu_ddc =  "./cpu_" + clock_period + "_op_data/cpu.ddc"
          print >> tcl_file, "read_ddc " + iunit_ddc
          print >> tcl_file, "read_ddc " + fpunit_ddc
          print >> tcl_file, "read_ddc " + icache_ddc
          print >> tcl_file, "read_ddc " + dcache_ddc
          print >> tcl_file, "read_ddc " + mmu_ddc
          print >> tcl_file, "read_ddc " + cpu_ddc


    print >> tcl_file, "# enabling the flags to report drc errors in the RTL"
    print >> tcl_file, "set hdlin_enable_rtldrc_info true"
    print >> tcl_file, "set fsm_auto_inferring TRUE"
    print >> tcl_file, "set hdlin_report_fsm TRUE"
    print >> tcl_file, "set enable_recovery_removal_arcs true\n"
    
    # lots of hardwired stuff here... need to generalize..
    print >> tcl_file, "# As per the foundry, below cells are not to be used"   
    print >> tcl_file, "set_dont_use tsl18fs120_scl_ss/slnht*"
    print >> tcl_file, "set_dont_use tsl18fs120_scl_ss/skbrb*"
    print >> tcl_file, "set_dont_use tsl18fs120_scl_ss/slbhb*"
    print >> tcl_file, "set_dont_use tsl18fs120_scl_ss/slnh*"
    print >> tcl_file, "set_dont_use tsl18fs120_scl_ss/slnln*"
    print >> tcl_file, "set_dont_use tsl18fs120_scl_ff/slnht*"
    print >> tcl_file, "set_dont_use tsl18fs120_scl_ff/skbrb*"
    print >> tcl_file, "set_dont_use tsl18fs120_scl_ff/slbhb*"
    print >> tcl_file, "set_dont_use tsl18fs120_scl_ff/slnh*"
    print >> tcl_file, "set_dont_use tsl18fs120_scl_ff/slnln*"
    print >> tcl_file, "set_dont_use tsl18fs120_scl_ff/jk*"
    print >> tcl_file, "set_dont_use tsl18fs120_scl_ss/jk*\n"	
    
    print >> tcl_file, "# defining the libraries into which the corresponding designs are going to be read"  
    print >> tcl_file, "define_design_lib default -path " + WORK_AREA 
    print >> tcl_file, "define_design_lib aHiR_ieee_proposed -path " + "./work/aHiR_ieee_proposed " 
    print >> tcl_file, "define_design_lib ahir -path " + "./work/ahir " 
    print >> tcl_file, "define_design_lib AjitCustom -path " + "./work/AjitCustom"

    print >> tcl_file, "define_design_lib core_cpu -path ./work/core_cpu"
    print >> tcl_file, "define_design_lib cpu_ccu -path ./work/cpu_ccu"
    print >> tcl_file, "define_design_lib cpu_debug_interface -path ./work/cpu_debug_interface"
    print >> tcl_file, "define_design_lib cpu_teu -path ./work/cpu_teu"
    print >> tcl_file, "define_design_lib teu_iexception -path ./work/teu_iexception"
    print >> tcl_file, "define_design_lib teu_idecode_idispatch -path ./work/teu_idecode_idispatch"
    print >> tcl_file, "define_design_lib teu_ifetch -path ./work/teu_ifetch"
    print >> tcl_file, "define_design_lib teu_iretire -path ./work/teu_iretire"
    print >> tcl_file, "define_design_lib teu_loadstore -path ./work/teu_loadstore"
    print >> tcl_file, "define_design_lib teu_stream_corrector -path ./work/teu_stream_corrector"
    print >> tcl_file, "define_design_lib teu_fpunit -path ./work/teu_fpunit"
    print >> tcl_file, "define_design_lib fpunit_exec -path ./work/fpunit_exec"
    print >> tcl_file, "define_design_lib fpunit_registers -path ./work/fpunit_registers"
    print >> tcl_file, "define_design_lib fpunit_writeback -path ./work/fpunit_writeback"
    print >> tcl_file, "define_design_lib teu_iunit -path ./work/teu_iunit"
    print >> tcl_file, "define_design_lib iunit_exec -path ./work/iunit_exec"
    print >> tcl_file, "define_design_lib iunit_registers -path ./work/iunit_registers"
    print >> tcl_file, "define_design_lib iunit_writeback_in_mux -path ./work/iunit_writeback_in_mux\n"

    print >> tcl_file, "define_design_lib core_cpu -path ./work/core_cpu"
    print >> tcl_file, "define_design_lib core_dcache -path ./work/core_dcache"
    print >> tcl_file, "define_design_lib core_icache -path ./work/core_icache"
    print >> tcl_file, "define_design_lib core_mmu -path ./work/core_mmu"
    print >> tcl_file, "define_design_lib core_biu -path ./work/core_biu\n"

    print >> tcl_file, "define_design_lib chip_core -path ./work/chip_core"
    print >> tcl_file, "define_design_lib chip_afb_bridge -path ./work/chip_afb_bridge"
    print >> tcl_file, "define_design_lib chip_debug_adapter -path ./work/chip_debug_adapter"
    print >> tcl_file, "define_design_lib chip_reset_pmode_stub -path ./work/chip_reset_pmode_stub"
    print >> tcl_file, "define_design_lib chip_logger_stub -path ./work/chip_logger_stub"
    print >> tcl_file, "define_design_lib chip_interrupt_stub -path ./work/chip_interrupt_stub"
    print >> tcl_file, "define_design_lib sys_chip -path ./work/sys_chip"
    print >> tcl_file, "define_design_lib chip_top -path ./work/chip_top\n"
   
    
    print >> tcl_file, "# reading the designs into the corresponding libraries"
    print >> tcl_file, "analyze -format vhdl -library aHiR_ieee_proposed ./vhdl_files/aHiR_ieee_proposed.vhdl"
    print >> tcl_file, "analyze -format vhdl -library ahir ./vhdl_files/ahirASIC.vhdl"
    print >> tcl_file, "analyze -format vhdl -library AjitCustom ./vhdl_files/AjitCustomForAsic.vhdl"

    if (design == "fpunit") or (((design == "cpu") or (design == "chip_with_io")) and (not hierarchical)):
       print >> tcl_file, "analyze -format vhdl -library fpunit_exec ./vhdl_files/exec.vhdl"
       print >> tcl_file, "analyze -format vhdl -library fpunit_registers ./vhdl_files/registers.vhdl"
       print >> tcl_file, "analyze -format vhdl -library fpunit_writeback ./vhdl_files/writeback.vhdl"
       print >> tcl_file, "analyze -format vhdl -library teu_fpunit ./vhdl_files/fpunit.vhdl"

    if (design == "iunit") or (((design == "cpu") or (design == "chip_with_io")) and (not hierarchical)):
       print >> tcl_file, "analyze -format vhdl -library iunit_exec ./vhdl_files/iu_exec.vhdl"
       print >> tcl_file, "analyze -format vhdl -library iunit_registers ./vhdl_files/iu_registers.vhdl"
       print >> tcl_file, "analyze -format vhdl -library iunit_writeback_in_mux ./vhdl_files/iu_writeback_in_mux.vhdl"
       print >> tcl_file, "analyze -format vhdl -library teu_iunit ./vhdl_files/iunit.vhdl"

    if design == "cpu" or ((design == "chip_with_io") and (not hierarchical)):
       print >> tcl_file, "analyze -format vhdl -library cpu_ccu ./vhdl_files/ccu.vhdl"
       print >> tcl_file, "analyze -format vhdl -library cpu_debug_interface ./vhdl_files/debug_interface.vhdl"
       print >> tcl_file, "analyze -format vhdl -library teu_iexception ./vhdl_files/iexception.vhdl"
       print >> tcl_file, "analyze -format vhdl -library teu_idecode_idispatch ./vhdl_files/idecode_idispatch.vhdl"
       print >> tcl_file, "analyze -format vhdl -library teu_ifetch ./vhdl_files/ifetch.vhdl"
       print >> tcl_file, "analyze -format vhdl -library teu_iretire ./vhdl_files/iretire.vhdl"
       print >> tcl_file, "analyze -format vhdl -library teu_loadstore ./vhdl_files/loadstore.vhdl"
       print >> tcl_file, "analyze -format vhdl -library teu_stream_corrector ./vhdl_files/stream_corrector.vhdl"
       print >> tcl_file, "analyze -format vhdl -library cpu_teu ./vhdl_files/teu.vhdl"
       print >> tcl_file, "analyze -format vhdl -library core_cpu ./vhdl_files/cpu.vhdl\n"
    
    if design == "mmu" or ((design == "chip_with_io") and (not hierarchical)): 
       print >> tcl_file, "analyze -format vhdl -library core_mmu ./vhdl_files/mmu.vhdl"

    if design == "icache" or ((design == "chip_with_io") and (not hierarchical)): 
       print >> tcl_file, "analyze -format vhdl -library core_mmu ./vhdl_files/mmu.vhdl"
       print >> tcl_file, "analyze -format vhdl -library core_icache ./vhdl_files/icache.vhdl"

    if design == "dcache" or ((design == "chip_with_io") and (not hierarchical)): 
       print >> tcl_file, "analyze -format vhdl -library core_dcache ./vhdl_files/dcache.vhdl"

    if design == "chip_with_io": 
       print >> tcl_file, "analyze -format vhdl -library core_biu ./vhdl_files/biu.vhdl"
       print >> tcl_file, "analyze -format vhdl -library chip_core ./vhdl_files/core.vhdl"
       print >> tcl_file, "analyze -format vhdl -library chip_afb_bridge ./vhdl_files/afb_bridge.vhdl"
       print >> tcl_file, "analyze -format vhdl -library chip_debug_adapter ./vhdl_files/debug_adapter.vhdl"
       print >> tcl_file, "analyze -format vhdl -library chip_interrupt_stub ./vhdl_files/interrupt_stub.vhdl"
       print >> tcl_file, "analyze -format vhdl -library chip_logger_stub ./vhdl_files/logger_stub.vhdl"
       print >> tcl_file, "analyze -format vhdl -library chip_reset_pmode_stub ./vhdl_files/reset_pmode_stub.vhdl"
       print >> tcl_file, "analyze -format vhdl -library sys_chip ./vhdl_files/chip.vhdl\n"
       print >> tcl_file, "analyze -format vhdl -library chip_top ./vhdl_files/chip_with_io.vhdl\n"
    
    print >> tcl_file, "# building the design and linking it with the standard cells in the liberty files"
    print >> tcl_file, "elaborate  $design -library " + library_name
    print >> tcl_file, "link\n"

    print >> tcl_file, "# flags to be set for icache and dcache for the formal verification to pass"
    print >> tcl_file, "set_verification_priority -high [ get_designs { DcacheFrontendDaemon_tag_length2 } ]"
    print >> tcl_file, "set_verification_priority -high [ get_designs { IcacheFrontendDaemon_tag_length2 } ]\n"
    print >> tcl_file, "# To remove the combinational loops, boundary optimization is disabled"
    print >> tcl_file, "set_boundary_optimization [get_designs *SplitGuardInterfaceBase*] false\n"

    print >> tcl_file, "current_design $design\n"
    
    print >> tcl_file, "# setting timing constraints on the clock"
    print >> tcl_file, "global clock_pin"
    print >> tcl_file, "set clock_pin clk" 
    print >> tcl_file, "set clk_period " + clock_period
    print >> tcl_file, "set clk_name $clock_pin"
    print >> tcl_file, "create_clock -period $clk_period -name clk [get_ports clk]"
    print >> tcl_file, "set_clock_uncertainty [expr $clk_period / 10] -setup [get_clock clk]"
    print >> tcl_file, "set_clock_uncertainty [expr $clk_period / 10] -hold  [get_clock clk]"
    print >> tcl_file, "set_clock_transition  [expr $clk_period / 10] [get_clock clk]"

    print >> tcl_file, "set_clock_latency  -max [expr $clk_period / 4] [get_clock clk]"
    print >> tcl_file, "set_clock_latency  -min [expr $clk_period / 6] [get_clock clk]"

   # print >> tcl_file, "set CLK_EXT_SOURCE_LATENCY_MAX     2.5"
   # print >> tcl_file, "set CLK_EXT_SOURCE_LATENCY_MIN     1.5"
   # print >> tcl_file, "set_clock_latency  -source  -max $CLK_EXT_SOURCE_LATENCY_MAX [get_clock clk]"
   # print >> tcl_file, "set_clock_latency  -source   -min $CLK_EXT_SOURCE_LATENCY_MIN [get_clock clk]"

    print >> tcl_file, "set input_delay_max_ns [expr $clk_period / 2]"
    print >> tcl_file, "set input_delay_min_ns 0.5"

    print >> tcl_file, "set output_delay_max_ns [expr $clk_period / 2]"
    print >> tcl_file, "set output_delay_min_ns 0.5"

    print >> tcl_file, "set_input_delay $input_delay_max_ns -max -clock clk [remove_from_collection [all_inputs] $clock_pin]"
    print >> tcl_file, "set_input_delay $input_delay_min_ns -min -clock clk [remove_from_collection [all_inputs] $clock_pin]"

    print >> tcl_file, "set_output_delay $output_delay_max_ns -max -clock clk [all_outputs]"
    print >> tcl_file, "set_output_delay $output_delay_min_ns -min -clock clk [all_outputs]\n"
 
    print >> tcl_file, "# grouping the similar types of paths for optimization"
    print >> tcl_file, "group_path -name INREG -from [all_inputs]"
    print >> tcl_file, "group_path -name REGOUT -to [all_outputs]"
    print >> tcl_file, "group_path -name INOUT -from [all_inputs] -to [all_outputs]\n"

    print >> tcl_file, "################### The DFT definitions ##################"
    print >> tcl_file, "set_scan_configuration -chain_count 10 -style multiplexed_flip_flop -max_length 10000\n"
    print >> tcl_file, "# setting the existing signals in the design to be used in scan insertion "
    print >> tcl_file, "set_dft_signal -view exist -type ScanClock -port clk -timing {45 55}"
    print >> tcl_file, "set_dft_signal -view exist -type CONSTANT -port reset -active_state 1"
    print >> tcl_file, "#set_dft_signal -view exist -type Reset -port reset -active_state 1\n"
    print >> tcl_file, "# specifying the non-existing connections to be made during scan insertion " 
    print >> tcl_file, "set_dft_signal -view spec  -type ScanEnable -port TEST_SE -usage scan -active_state 1" 
    print >> tcl_file, "set_dft_signal -view exist -type ScanEnable -port TEST_SE -active_state 1 "
    print >> tcl_file, "set_dft_signal -view spec  -type TESTMODE -port TEST_MODE -active_state 1"
    print >> tcl_file, "set_dft_signal -view exist -type CONSTANT -port TEST_MODE -active_state 1 \n"

    # scan chains..
   
    if top == 'y':
	print >> tcl_file, "# setting don't touch on the input ports corresponding to TEST_SE, TEST_MODE pins"
# setting don't touch on the input ports corresponding to TEST_SE, TEST_MODE pins
	print >> tcl_file, "set_dont_touch TEST_SE"
	print >> tcl_file, "set_dont_touch TEST_MODE"

# specifying scan_in, scan_out and scan_chain connections
	print >> tcl_file, "set_dft_signal -view spec  -type ScanDataIn  -port AFBRESP_DIN_9 -hookup_pin II_25/CIN"
	print >> tcl_file, "set_dft_signal -view spec  -type ScanDataIn  -port AFBRESP_DIN_8 -hookup_pin II_26/CIN"
	print >> tcl_file, "set_dft_signal -view spec  -type ScanDataIn  -port AFBRESP_DIN_7 -hookup_pin II_27/CIN"
	print >> tcl_file, "set_dft_signal -view spec  -type ScanDataIn  -port AFBRESP_DIN_6 -hookup_pin II_28/CIN"
	print >> tcl_file, "set_dft_signal -view spec  -type ScanDataIn  -port AFBRESP_DIN_5 -hookup_pin II_29/CIN"
	print >> tcl_file, "set_dft_signal -view spec  -type ScanDataIn  -port AFBRESP_DIN_4 -hookup_pin II_30/CIN"
	print >> tcl_file, "set_dft_signal -view spec  -type ScanDataIn  -port AFBRESP_DIN_3 -hookup_pin II_31/CIN"
	print >> tcl_file, "set_dft_signal -view spec  -type ScanDataIn  -port AFBRESP_DIN_2 -hookup_pin II_32/CIN"
	print >> tcl_file, "set_dft_signal -view spec  -type ScanDataIn  -port AFBRESP_DIN_1 -hookup_pin II_33/CIN"
	print >> tcl_file, "set_dft_signal -view spec  -type ScanDataIn  -port AFBRESP_DIN_0 -hookup_pin II_34/CIN"

	print >> tcl_file, "set_dft_signal -view spec  -type ScanDataOut -port AFBREQ_DOUT_9 -hookup_pin OO_66/I"
	print >> tcl_file, "set_dft_signal -view spec  -type ScanDataOut -port AFBREQ_DOUT_8 -hookup_pin OO_67/I"
	print >> tcl_file, "set_dft_signal -view spec  -type ScanDataOut -port AFBREQ_DOUT_7 -hookup_pin OO_68/I"
	print >> tcl_file, "set_dft_signal -view spec  -type ScanDataOut -port AFBREQ_DOUT_6 -hookup_pin OO_69/I"
	print >> tcl_file, "set_dft_signal -view spec  -type ScanDataOut -port AFBREQ_DOUT_5 -hookup_pin OO_70/I"
	print >> tcl_file, "set_dft_signal -view spec  -type ScanDataOut -port AFBREQ_DOUT_4 -hookup_pin OO_71/I"
	print >> tcl_file, "set_dft_signal -view spec  -type ScanDataOut -port AFBREQ_DOUT_3 -hookup_pin OO_72/I"
	print >> tcl_file, "set_dft_signal -view spec  -type ScanDataOut -port AFBREQ_DOUT_2 -hookup_pin OO_73/I"
	print >> tcl_file, "set_dft_signal -view spec  -type ScanDataOut -port AFBREQ_DOUT_1 -hookup_pin OO_74/I"
	print >> tcl_file, "set_dft_signal -view spec  -type ScanDataOut -port AFBREQ_DOUT_0 -hookup_pin OO_75/I"

	print >> tcl_file, "set_scan_path chain1 -view spec -scan_data_in AFBRESP_DIN_9 -scan_data_out AFBREQ_DOUT_9"
	print >> tcl_file, "set_scan_path chain2 -view spec -scan_data_in AFBRESP_DIN_8 -scan_data_out AFBREQ_DOUT_8"
	print >> tcl_file, "set_scan_path chain3 -view spec -scan_data_in AFBRESP_DIN_7 -scan_data_out AFBREQ_DOUT_7"
	print >> tcl_file, "set_scan_path chain4 -view spec -scan_data_in AFBRESP_DIN_6 -scan_data_out AFBREQ_DOUT_6"
	print >> tcl_file, "set_scan_path chain5 -view spec -scan_data_in AFBRESP_DIN_5 -scan_data_out AFBREQ_DOUT_5"
	print >> tcl_file, "set_scan_path chain6 -view spec -scan_data_in AFBRESP_DIN_4 -scan_data_out AFBREQ_DOUT_4"
	print >> tcl_file, "set_scan_path chain7 -view spec -scan_data_in AFBRESP_DIN_3 -scan_data_out AFBREQ_DOUT_3"
	print >> tcl_file, "set_scan_path chain8 -view spec -scan_data_in AFBRESP_DIN_2 -scan_data_out AFBREQ_DOUT_2"
	print >> tcl_file, "set_scan_path chain9 -view spec -scan_data_in AFBRESP_DIN_1 -scan_data_out AFBREQ_DOUT_1"
	print >> tcl_file, "set_scan_path chain10 -view spec -scan_data_in AFBRESP_DIN_0 -scan_data_out AFBREQ_DOUT_0"

    print >> tcl_file, "# auto fixing the errors related to reset"
    print >> tcl_file, "#set_autofix_configuration -type reset -control_signal TEST_SE -test_data reset -method gate"
    print >> tcl_file, "set_dft_drc_configuration -allow_se_set_reset_fix true"
    print >> tcl_file, "set_dft_configuration -fix_reset enable\n"
    print >> tcl_file, "create_test_protocol\n"
    print >> tcl_file, "set_app_var test_validate_test_model_connectivity true"
    print >> tcl_file, "set test_keep_connected_scan_en true\n" 
    print >> tcl_file, "# fix the violations reported after the below step"    
    print >> tcl_file, "dft_drc -verbose > pre_dft_drc_$design.rpt"
    
    print >> tcl_file, "set_operating_conditions -analysis_type on_chip_variation -max  tsl18cio250_max -min tsl18cio250_min -max_library {tsl18cio250_max} -min_library {tsl18cio250_min}\n"
    print >> tcl_file, "# set_case_analysis 1 for generating patterns in test mode"
    print >> tcl_file, "set_case_analysis 0 [get_ports TEST_SE]"
    print >> tcl_file, "set_case_analysis 0 [get_ports TEST_MODE]\n"
    print >> tcl_file, "set_ideal_network [get_ports clk]"
    print >> tcl_file, "set_ideal_network [get_ports reset]"
    print >> tcl_file, "set_ideal_network [get_ports TEST_SE]\n"
    print >> tcl_file, "set_cost_priority -delay"
    print >> tcl_file, "check_design"
    print >> tcl_file, "compile_ultra -spg -scan -timing_high_effort_script -no_autoungroup  \n"
    print >> tcl_file, "# previewing the design before scan insertion"
    print >> tcl_file, "preview_dft\n"
    print >> tcl_file, "insert_dft\n"
    print >> tcl_file, "current_design $design\n"
    print >> tcl_file, "# compiling the design for optimization of design constraints"  
    print >> tcl_file, "compile_ultra -scan -incr -timing_high_effort_script -no_autoungroup \n"
    print >> tcl_file, "# reporting the errors after DFT insertion"
    print >> tcl_file, "dft_drc -verbose > post_dft_drc_$design.rpt\n"
  
    print >> tcl_file, "set_svf off\n"
    print >> tcl_file, "# writing out the synthesized netlist and reports"
    print >> tcl_file, "write_scan_def -output ./" +design+"_"+clock_period+"_"+"op_data/${design}_scan.def"
    print >> tcl_file, "write_test_protocol -output ./"+design+"_"+clock_period+"_"+"op_data/${design}.spf"
    print >> tcl_file, "write -f verilog -hier -output ./"+design+"_"+clock_period+"_"+"op_data/${design}.v"
    print >> tcl_file, "write -f ddc -hier -output ./"+design+"_"+clock_period+"_"+"op_data/${design}.ddc"
    print >> tcl_file, "write_sdc ./"+design+"_"+clock_period+"_"+"op_data/${design}.sdc\n"
    print >> tcl_file, "report_timing -nets -cap -transition -nworst 2  -max_paths 40 > ./" +design+"_"+clock_period+"_"+"reports/timing_full.rpt"
    print >> tcl_file, "report_timing -loops -max_paths 50 > ./" +design+"_"+clock_period+"_"+"reports/loops.rpt"
    print >> tcl_file, "report_area > ./" +design+"_"+clock_period+"_"+"reports/area.rpt"
    print >> tcl_file, "report_constraint -all_violators > ./" +design+"_"+clock_period+"_"+"reports/constraint.rpt"
    print >> tcl_file, "report_cell > ./" +design+"_"+clock_period+"_"+"reports/cell.rpt"
    print >> tcl_file, "report_power > ./" +design+"_"+clock_period+"_"+"reports/power.rpt"
    print >> tcl_file, "report_qor > ./" +design+"_"+clock_period+"_"+"reports/qor.rpt"
    print >> tcl_file, "report_nets > ./" +design+"_"+clock_period+"_"+"reports/nets.rpt\n"
    print >> tcl_file, "# creating the block abstraction for use in the upper hierarchy"    
    print >> tcl_file, "set_app_var uniquify_naming_style ${design}_%s_%d"
    print >> tcl_file, "uniquify -force"
    print >> tcl_file, "change_names -rules verilog -hierarchy"
    print >> tcl_file, "create_block_abstraction" 
    print >> tcl_file, "write_file -format ddc -hierarchy -output ./"+design+"_"+clock_period+"_"+"op_data/${design}_block.ddc"

    print >> tcl_file, "quit"
    tcl_file.close()


def main ():
    SetGlobals()
    lib_name = None
    system_top = False
    hierarchical = False
      
    if (len(sys.argv) < 9 ): 
        display_usage()
        return 1
    else :
        arg_list = sys.argv[1:]
        opts,args = getopt.getopt(arg_list,'d:l:p:t:hH')
        for option, parameter in opts:
            if option ==  '-l':
                lib_name = parameter
            if option ==  '-d':
                design = parameter
            if option == '-p':
            	period = parameter
	    if option ==  '-t':
                top = parameter
	    if option ==  '-H':
                hierarchical = True
            if option ==  '-h':
                display_usage()
		return 0
            
                
    if (design != "iunit") and (design != "fpunit") and (design != "cpu") and (design != "chip_with_io") and (design != "mmu") and (design != "icache") and (design != "dcache"):
       print "ERROR: -d " + design + ": iunit/fpunit/cpu/chip_with_io/mmu/icache/dcache are the only possible options\n"
       return 0;

    generateTCL(design, period, lib_name, top, hierarchical)
        
    return 0





if __name__ == '__main__':
    ret = main()
    sys.exit(ret)
