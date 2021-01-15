#!/usr/bin/env python

# Generates the .tcl files necessary for IC Compiler place and route tool
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
   # global AJIT_ASIC_TAPEOUT_HOME
   # AJIT_ASIC_TAPEOUT_HOME=os.environ.get('AJIT_ASIC_TAPEOUT_HOME')
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
    print "\n Correct usage of the script is given below. \n"
    print " $ buildICC.py -d < design name > -p < clock period -t <top> -f <top-floorplan-util-factor> -l <leaf-floorplan-util-factor>\n"
    print " e.g. buildICC.py -d cpu -p -15 -t n -f 0.7 -l 0.5 \n"
    print " -h < no parameter required. used to get help > \n"
    print " Note: If -t option is set to 'y', pads are added to the design"
    

    
def generateTCL(design, period, top, fp_util, leaf_util, hierarchical):
           
    reports_dir = "./" + design + "_" + period + "_" + fp_util + "_" + leaf_util +  "_pnr_reports"
    op_data_dir = "./" + design + "_" + period + "_" + fp_util +  "_" + leaf_util + "_pnr_op_data"
    synth_op_data_dir = "./" + design + "_" + period + "_op_data"
    cpu_op_data_dir  = "./cpu_" + period + "_op_data"
    icache_op_data_dir  = "./icache_" + period + "_op_data"
    dcache_op_data_dir  = "./dcache_" + period + "_op_data"
    mmu_op_data_dir  = "./mmu_" + period + "_op_data"

    if hierarchical:
       tcl_file_name = "icc_" + design + "_" + period + "_" + top + "_" + fp_util +  "_" + leaf_util + "_hierarchical.tcl" 
    else:
       tcl_file_name = "icc_" + design + "_" + period + "_" + top + "_" + fp_util +  "_" + leaf_util + ".tcl" 

    tcl_file = open(tcl_file_name,"w")
    print >> tcl_file, "set AJIT_ASIC_TAPEOUT_HOME $::env(AJIT_ASIC_TAPEOUT_HOME)"
    print >> tcl_file, "set design " + design
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

    if design == "cpu":
       if hierarchical:
          print >> tcl_file, "set_top_implementation_options -block_references {fpunit iunit}"

    if design == "chip_with_io":
       if hierarchical:
          print >> tcl_file, "set_top_implementation_options -block_references {cpu icache dcache mmu fpunit iunit}"

    print >> tcl_file, "# reading the synthesized design's ddc, scandef files from synthesis output directory"
    print >> tcl_file, "read_ddc "  + synth_op_data_dir + "/" + design + ".ddc"
    print >> tcl_file, "read_def "  + synth_op_data_dir + "/" + design + "_scan.def\n"
       
    print >> tcl_file, "# linking the design to standard cells in the liberty files"
    print >> tcl_file, "link -force\n"
    print >> tcl_file, "current_design " + design
    print >> tcl_file, "uniquify_fp_mw_cel\n"

    print >> tcl_file, "# setting timing constraints on the clock"
    print >> tcl_file, "global clock_pin"
    print >> tcl_file, "set clock_pin clk" 
    print >> tcl_file, "set clk_period " + period
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
    if top == 'y':
	print >> tcl_file, "# creating corner and power pads"
	print >> tcl_file, "create_cell { corner_pad1 corner_pad2 corner_pad3 corner_pad4  } pfrelr" 
	print >> tcl_file, "set_pad_physical_constraints -pad_name "+"\""+"corner_pad1"+"\""+" -side 1"
	print >> tcl_file, "set_pad_physical_constraints -pad_name "+"\""+"corner_pad2"+"\""+" -side 2"
	print >> tcl_file, "set_pad_physical_constraints -pad_name "+"\""+"corner_pad3"+"\""+" -side 3"
	print >> tcl_file, "set_pad_physical_constraints -pad_name "+"\""+"corner_pad4"+"\""+" -side 4"
	print >> tcl_file, "create_cell { VDD VDDX } pvdi" 
	print >> tcl_file, "create_cell { VSS } pv0i" 
	print >> tcl_file, "create_cell { VSSO1 VSSO2 } pv0a"
	print >> tcl_file, "create_cell { VDDO1 VDDO2 } pvda\n"

    print >> tcl_file, "link -force\n"
    print >> tcl_file, "######################## Floor Planning #########################"
    print >> tcl_file, "set_user_grid -user_grid {{0 0} {0.005 0.005}}\n"
    print >> tcl_file, "create_floorplan -control_type aspect_ratio -core_aspect_ratio 1 -core_utilization " + fp_util + " -left_io2core 100 -bottom_io2core 100 -right_io2core 100 -top_io2core 100 \n"
    print >> tcl_file, "#############  creating pins of VDD VSS VDDO VSSO ###############"
    if top == 'y':
    	print >> tcl_file, "derive_pg_connection -power_net {VDDO} -ground_net {VSSO} -power_pin {VDDO} -ground_pin {VSSO} -create_ports top"
    print >> tcl_file, "derive_pg_connection -power_net {VDD} -ground_net {VSS} -power_pin {VDD} -ground_pin {VSS} -create_ports top"
    print >> tcl_file, "derive_pg_connection -power_net {VDD} -ground_net {VSS} -tie\n"
    print >> tcl_file, "############## creating power rings around the core area ########"
    print >> tcl_file, "create_rectilinear_rings -around core -nets  {VSS VDD}  -offset {10 10} -width {5 5} -space {10 10} -layers {M3 TOP_M}\n"
    print >> tcl_file, "########### Connects pins in instances to power and ground targets ######"
    print >> tcl_file, "preroute_instances  -route_pins_on_layer M2 -primary_routing_layer specified -specified_horizontal_layer M2\n"
    print >> tcl_file, "### Connects power, ground, and tie-off pins to the specified power and ground nets #############"
    print >> tcl_file, "derive_pg_connection -power_net {VDD} -ground_net {VSS} -power_pin {VDD} -ground_pin {VSS}"
    print >> tcl_file, "derive_pg_connection -power_net {VDD} -ground_net {VSS} -tie\n"
    print >> tcl_file, "#### check for both recovery and removal arcs #####"
    print >> tcl_file, "#### enables the acceptance of recovery and removal arcs specified in the technology library###########"
    print >> tcl_file, "set_app_var enable_recovery_removal_arcs true\n"
    print >> tcl_file, "set_operating_conditions -analysis_type on_chip_variation -max tsl18cio250_max  -min tsl18cio250_min -max_library tsl18cio250_max -min_library tsl18cio250_min\n"
    print >> tcl_file, "set_app_var timing_remove_clock_reconvergence_pessimism true"
    print >> tcl_file, "set_fix_hold [all_clocks]\n"
    print >> tcl_file, "derive_pg_connection -power_net {VDD} -ground_net {VSS} -power_pin {VDD} -ground_pin {VSS}"
    if top == 'y':    
	print >> tcl_file, "derive_pg_connection -power_net {VDDO} -ground_net {VSSO} -power_pin {VDDO} -ground_pin {VSSO}"
    print >> tcl_file, "derive_pg_connection -power_net {VDD} -ground_net {VSS} -tie\n"
    print >> tcl_file, "#################################################################"
    print >> tcl_file, "########################### Placement ###########################"
    print >> tcl_file, "#################################################################"
    print >> tcl_file, "set_ideal_network [all_fanout -flat -clock_tree]\n"
    print >> tcl_file, "set_fp_placement_strategy -auto_grouping medium -macro_orientation all -macro_setup_only off -min_distance_between_macros 50.4 -IO_net_weight 8 -force_auto_detect_hierarchy true -macros_on_edge auto -pin_routing_aware true -snap_macros_to_user_grid on -congestion_effort medium -virtual_IPO true \n"
    print >> tcl_file, "create_fp_placement -effort low -optimize_pins -congestion_driven -timing_driven"
    print >> tcl_file, "set_attribute [all_macro_cells] is_fixed true \n"
    print >> tcl_file, "# generating power and ground rings around the macros"
    print >> tcl_file, "set_power_ring_strategy strategy_1 -nets {VDD VSS}  -macros [all_macro_cells] -template macro_rings.tpl:ring_around_macro"
    print >> tcl_file, "compile_power_plan -ring -strategy strategy_1\n"
    print >> tcl_file, "legalize_placement\n"
    print >> tcl_file, "####### Laying the M1 Power lines for cells horizontal direction ###### "
    print >> tcl_file, "preroute_standard_cells -connect horizontal  -fill_empty_rows  -port_filter_mode off -cell_master_filter_mode off -cell_instance_filter_mode off -voltage_area_filter_mode off -route_type {P/G Std. Cell Pin Conn} -do_not_route_over_macros -fill_empty_sites -extend_for_multiple_connections\n"
   
    print >> tcl_file, "place_opt\n"
    
    print >> tcl_file, "derive_pg_connection -power_net {VDD} -ground_net {VSS} -power_pin {VDD} -ground_pin {VSS}"
    print >> tcl_file, "derive_pg_connection -power_net {VDD} -ground_net {VSS} -power_pin {VDD} -ground_pin {VSS} -tie"
    print >> tcl_file, "# generating reports after placement"
    print >> tcl_file, "report_placement_utilization > " + reports_dir + "/" + design + "_fp_util.rpt"

    print >> tcl_file, "check_timing"
    print >> tcl_file, "check_legality"
    print >> tcl_file, "report_timing -nworst 2 -max_paths 40 > " + reports_dir + "/"+ design + "_placed_timing.rpt"
    print >> tcl_file, "report_qor > " + reports_dir + "/"+ design + "_after_place_qor.rpt\n"
    print >> tcl_file, "###############################################################"
    print >> tcl_file, "#################### Clock Tree Synthesis #####################"
    print >> tcl_file, "###############################################################"
    print >> tcl_file, "check_physical_design -stage pre_clock_opt -output ./pre_cts_check\n"
    print >> tcl_file, "set_si_options -delta_delay true -route_xtalk_prevention true -static_noise true"
    print >> tcl_file, "remove_ideal_network -all\n"
    print >> tcl_file, "derive_pg_connection -power_net {VDD} -ground_net {VSS} -power_pin {VDD} -ground_pin {VSS}"

    print >> tcl_file, "derive_pg_connection -power_net {VDD} -ground_net {VSS} -tie\n"
    print >> tcl_file, "############# Set Zroute common options for routing##############"
    print >> tcl_file, "set_route_zrt_common_options -read_user_metal_blockage_layer true"
    print >> tcl_file, "set_route_zrt_global_options -effort medium -timing_driven true -crosstalk_driven true\n"
    print >> tcl_file, "set_app_var timing_enable_multiple_clocks_per_reg true\n"
    print >> tcl_file, "######## DRC fixing during optimization of clock tree ############"
    print >> tcl_file, "set_app_var cto_enable_drc_fixing true\n"
    print >> tcl_file, "set_clock_tree_optimization_options -enable_multicorner_optimization all"
    print >> tcl_file, "set_fix_hold [all_clocks]\n"
    print >> tcl_file, "########################## Routing rule #############################"
    print >> tcl_file, "define_routing_rule dsdw -spacings { M2 0.4 M3 0.4 TOP_M 0.5} -widths { M2 0.4 M3 0.4 TOP_M 0.5}"
    print >> tcl_file, "set_clock_tree_options -routing_rule dsdw -layer_list {M2 M3 TOP_M}\n"
    print >> tcl_file, "################## Clock Optimization ###############################"
    print >> tcl_file, "clock_opt -fix_hold_all_clocks -update_clock_latency -continue_on_missing_scandef -congestion "

    print >> tcl_file, "set_propagated_clock [all_clocks]\n"
    print >> tcl_file, "report_timing -nworst 2 -max_paths 40 > " + reports_dir + "/"+ design + "_cts_timing.rpt\n"
    print >> tcl_file, "derive_pg_connection -power_net {VDD} -ground_net {VSS} -power_pin {VDD} -ground_pin {VSS}"
    print >> tcl_file, "derive_pg_connection -power_net {VDD} -ground_net {VSS} -power_pin {VDD} -ground_pin {VSS} -tie"
    if top == 'y':
	print >> tcl_file, "# inserting pad fillers"
	print >> tcl_file, "insert_pad_filler -cell {pfeed30000 pfeed10000 pfeed02000 pfeed01000 pfeed00540 pfeed00120 pfeed00040 pfeed00010}\n"
    print >> tcl_file, "report_congestion > " + reports_dir + "/"+design + "_congestion_b4_routing.rpt\n"
    print >> tcl_file, "#######################################################################"
    print >> tcl_file, "########################### Routing ###################################"
    print >> tcl_file, "#######################################################################\n"

    print >> tcl_file, "define_routing_rule double_spacing -spacings {M2 0.4 M3 0.4 TOP_M 0.5}"
    print >> tcl_file, "set_net_routing_rule -rule double_spacing [remove_from_collection [get_nets *] [get_nets -hierarchical -filter "+"\""+"net_type == Clock"+"\""+"]]\n"
    print >> tcl_file, "check_routeability -error_cell block_withpad.err"
    print >> tcl_file, "set lib [current_mw_lib]"
    print >> tcl_file, "remove_antenna_rules $lib\n"

    print >> tcl_file, "define_antenna_rule $lib -mode 4 -diode_mode 2 -metal_ratio 350 -cut_ratio 20"
    print >> tcl_file, "define_antenna_layer_rule $lib -mode 4 -layer "+"\""+"M1"+"\""+" -ratio 350 -diode_ratio { 0.203 0 400 2200}"
    print >> tcl_file, "define_antenna_layer_rule $lib -mode 4 -layer "+"\""+"M2"+"\""+" -ratio 350 -diode_ratio { 0.203 0 400 2200}"
    print >> tcl_file, "define_antenna_layer_rule $lib -mode 4 -layer "+"\""+"M3"+"\""+" -ratio 350 -diode_ratio { 0.203 0 400 2200}"
    print >> tcl_file, "define_antenna_layer_rule $lib -mode 4 -layer "+"\""+"TOP_M"+"\""+ " -ratio 350 -diode_ratio {0.203 0 8000 30000}"
    print >> tcl_file, "define_antenna_layer_rule $lib -mode 4 -layer "+"\""+"V2"+"\""+" -ratio 20 -diode_ratio {0.203 0 83.33 75}"
    print >> tcl_file, "define_antenna_layer_rule $lib -mode 4 -layer "+"\""+"V3"+"\""+" -ratio 20 -diode_ratio {0.203 0 83.33 75}"
    print >> tcl_file, "define_antenna_layer_rule $lib -mode 4 -layer "+"\""+"TOP_V"+"\""+" -ratio 20 -diode_ratio {0.203 0 83.33 75}"
    print >> tcl_file, "set input_port [get_ports [all_inputs]]\n"

    print >> tcl_file, "foreach_in_collection itr $input_port {"
    print >> tcl_file, "set port "+"\""+"[get_object_name $itr]"+"\""
    print >> tcl_file, "define_io_gate_size  -pin_name  $port -values {0.01}}"
    print >> tcl_file, "set_si_options -delta_delay true -static_noise true\n"
    
    print >> tcl_file, "route_opt"
    print >> tcl_file, "report_congestion > "  + reports_dir + "/" + design + "_congestion_aftr_routing.rpt"
    print >> tcl_file, "report_qor > " + reports_dir + "/"+ design + "_after_place_qor.rpt\n" 
    print >> tcl_file, "insert_stdcell_filler  -cell_without_metal {feedth9 feedth3 feedth}  -cell_with_metal {feedth9 feedth3 feedth}  -connect_to_power {VDD}  -connect_to_ground {VSS}\n "

    print >> tcl_file, "derive_pg_connection -power_net {VDD} -ground_net {VSS} -power_pin {VDD} -ground_pin {VSS}"
    if top == 'y':    
	print >> tcl_file, "derive_pg_connection -power_net {VDDO} -ground_net {VSSO} -power_pin {VDDO} -ground_pin {VSSO}"
    print >> tcl_file, "derive_pg_connection -power_net {VDD} -ground_net {VSS} -tie\n"
    print >> tcl_file, "define_name_rules my_rule -case_insensitive"
    print >> tcl_file, "report_name_rules my_rule"
    print >> tcl_file, "change_names -rules my_rule -hierarchy\n"
    print >> tcl_file, "# saving the design after routing"
    print >> tcl_file, "save_mw_cel -as ${design} -hierarchy\n"
    print >> tcl_file, "report_timing -delay_type max -max_paths 40 -nworst 2 >" + reports_dir + "/"+design + "_final_setup_timing.rpt"
    print >> tcl_file, "report_timing -delay_type min -max_paths 40 -nworst 2 >" + reports_dir + "/"+design + "_final_hold_timing.rpt"
    print >> tcl_file, "report_constraint -all_violators > " + reports_dir + "/"+ design + "_final_violators.rpt"
    print >> tcl_file, "report_power > " + reports_dir + "/"+ design + "_final_power.rpt\n"
    print >> tcl_file, "# writing the output GDSII file"
    print >> tcl_file, "set_write_stream_options -skip_ref_lib_cells -output_pin geometry -output_pin text -keep_data_type -map_layer $AJIT_ASIC_TAPEOUT_HOME/tech/scl180//tech_topo/RCE_TS18SL_SCL_STAR_RCXT_4M1L_TYP.map\n"
    print >> tcl_file, "write_stream -format gds -lib_name syn_topo " + op_data_dir + "/"+ design + ".gds\n"
    print >> tcl_file, "write_verilog -pg -no_corner_pad_cells -no_pad_filler_cells -no_core_filler_cells -supply_statement all -force_no_output_references {feedth9 feedth3 feedth} " + op_data_dir + "/"+design+"_icc_out.v\n"
    print >> tcl_file, "write_verilog  -no_corner_pad_cells -no_pad_filler_cells -no_core_filler_cells  -force_no_output_references {feedth9 feedth3 feedth} " + op_data_dir + "/"+ design +"_no_pg_icc_out.v\n"
    print >> tcl_file, "write_sdc " + op_data_dir + "/"+design+"_icc.sdc"
    print >> tcl_file, "write_def -output " + op_data_dir + "/"+design+"_icc.def"
    print >> tcl_file, "write_parasitics -format SPEF -compress -output " + op_data_dir + "/"+design+"_icc.gzip\n"
    print >> tcl_file, "# creating block abstraction for use in upper hierarchy"
    print >> tcl_file, "save_mw_cel -hierarchy -as ${design}"
    print >> tcl_file, "create_block_abstraction"
    print >> tcl_file, "save_mw_cel -hierarchy -as ${design}"
    print >> tcl_file, "quit"
    tcl_file.close()


def main ():
    SetGlobals()
    lib_name = None
    system_top = False
    fp_util = "0.7"
    leaf_util = "0.7"
    hierarchical = False
      
    if (len(sys.argv) < 9 ): 
        display_usage()
        return 1
    else :
        arg_list = sys.argv[1:]
        opts,args = getopt.getopt(arg_list,'d:p:t:f:l:hH')
        for option, parameter in opts:
            if option ==  '-d':
                design = parameter
            if option == '-p':
            	period = parameter
            if option == '-t':
            	top = parameter
            if option == '-f':
            	fp_util = parameter
            if option == '-l':
            	leaf_util = parameter
            if option ==  '-H':
                hierarchical = True
            if option ==  '-h':
                display_usage()
		return 0
            
                
    generateTCL(design, period, top, fp_util, leaf_util, hierarchical)
        
    return 0





if __name__ == '__main__':
    ret = main()
    sys.exit(ret)
