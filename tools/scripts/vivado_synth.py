#!/usr/bin/env python

# Searches for all vivado_implement direcories present in current working directory 
# (eg:/processor/Aa_v2/) and runs on vivado, implement.tcl present in them, which 
# synthesizes the design and generates post synth vhd files and dcp files.
#
# The script then implements the entire processor model by using top level dcp file, 
# or cpu and aggregator ngc files along with riffa 2.2.0 and generates the bit file.
#
# Use vivado 2014.4 with this script
#
# Results of this implementation are stored in -  
#	/processor/FPGA/vc709/vc709_test_example_piyush/vivado_tcl/implement_processor/
#
# Options:
#	-c : to clean vivado_implement directories except for the implement.tcl file 
#	and implement_processor directory except for the chnl_tester.v file
#	
#	-x : to use xst synthesis results (results of xilinx_synth.py - cpu and aggregator 
#	ngc files) for implementation and bit file generation, default is vivado synthesis 
#	result (this script - sys dcp file). If this option is selected then synthesis using 
#	implement.tcl is bypassed and directly implementation starts, so run xilinx_synth.py 
#	before using this option. Use xilinx 14.2 with xilinx_synth.py.
#
#	-x -c: to clean xst_synthesis directories except for the buildXST.sh file and 
#	implement_processor directory except for the chnl_tester.v file
#
# Author : Piyush P. Soni
#
#

import os
import sys
import getopt
import os.path
import shutil

topdir = os.getcwd()
srch_fold = "vivado_implement"

ajit_project_home = os.environ.get('AJIT_PROJECT_HOME')
board = os.environ.get('fpga_board')

clean = False


def generate_tcl (xst, protoboard):
	#print dcp_file
	if protoboard:
		if (board == "vc709"):
			implement_processor = os.path.join (ajit_project_home + "/processor/FPGA/vc709/vc709_test_example_piyush/vivado_tcl/implement_processor_protoboard")
		if (board == "kc705"):
			implement_processor = os.path.join (ajit_project_home + "/processor/FPGA/KC705/implement_processor_protoboard")

	else:
		if (board == "vc709"):
			implement_processor = os.path.join (ajit_project_home + "/processor/FPGA/vc709/vc709_test_example_piyush/vivado_tcl/implement_processor")
		if (board == "kc705"):
			implement_processor = os.path.join (ajit_project_home + "/processor/FPGA/KC705/implement_processor")

	if clean:
		current_dir = os.getcwd()
		os.chdir (implement_processor)

		files = os.listdir (implement_processor)
		for contents in files:
			if ((contents != "chnl_tester.v") and (contents != "bitgen_riffa2.2.2.tcl") and (contents != "run.sh")):
				if os.path.isdir (contents):
					shutil.rmtree(contents)
				else:
					os.remove(contents)
		os.chdir (current_dir)

	else :
		processor_tcl = os.path.join (implement_processor + "/bitgen.tcl")

		tcl_file = open(processor_tcl,"w")

		print >> tcl_file, "\nset AHIR_RELEASE $::env(AHIR_RELEASE)"
		print >> tcl_file, "set AJIT_PROJECT_HOME $::env(AJIT_PROJECT_HOME) \n"

		print >> tcl_file, "############ RIFFA 2.2.0 HDL ############"
		print >> tcl_file, "read_verilog [glob ../hdl/riffa_hdl/*.v] "
		if (board == "vc709"):
			print >> tcl_file, "read_verilog ../hdl/riffa_wrapper_vc709.v"
			print >> tcl_file, "read_verilog ../hdl/VC709Gen1x8If64.v"
		if (board == "kc705"):
			print >> tcl_file, "read_verilog ../hdl/riffa_wrapper_kc705.v"
			print >> tcl_file, "read_verilog ../hdl/KC705_Gen1x8If64.v"

		print >> tcl_file, "read_verilog ./chnl_tester.v\n"

		print >> tcl_file, "########## RIFFA TO CPU BRIDGE ##########"
		print >> tcl_file, "read_verilog ../hdl/riffa_cpu_bridge.v"
		print >> tcl_file, "read_vhdl ../hdl/DualClockedQueue.vhdl\n"

		print >> tcl_file, "############# CONSTRAINT FILE ###########"
		if (board == "vc709"):
			print >> tcl_file, "read_xdc ../constraint/VC709_Top.xdc\n"
		if (board == "kc705"):
			print >> tcl_file, "read_xdc ../constraint/KC705_TOP.xdc\n"

		print >> tcl_file, "############# IP CORE FILES #############"
		
		if (board == "vc709"):
			print >> tcl_file, "set_property part xc7vx690tffg1761-2 [current_project]"
			print >> tcl_file, "set_property board_part xilinx.com:vc709:part0:1.5 [current_project]\n"

			print >> tcl_file, "read_ip ../ip/pcie_core/pcie3_7x_0.xci"
			print >> tcl_file, "synth_ip -force [get_files ../ip/pcie_core/pcie3_7x_0.xci]\n"

			print >> tcl_file, "read_ip ../ip/dual_clock_fifo/fifo_generator_v9_2.xci"
			print >> tcl_file, "synth_ip -force [get_files ../ip/dual_clock_fifo/fifo_generator_v9_2.xci]\n"

		if (board == "kc705"):
			print >> tcl_file, "set_property part xc7k325tffg900-2 [current_project]"
			print >> tcl_file, "set_property board_part xilinx.com:kc705:part0:1.1 [current_project]\n"

			print >> tcl_file, "read_ip ../ip/pcie_core/PCIeGen1x8If64.xci"
			print >> tcl_file, "synth_ip -force [get_files ../ip/pcie_core/PCIeGen1x8If64.xci]\n"

			print >> tcl_file, "read_ip ../ip/dual_clock_fifo/fifo_generator_0.xci"
			print >> tcl_file, "synth_ip -force [get_files ../ip/dual_clock_fifo/fifo_generator_0.xci]\n"

		print >> tcl_file, "############### USER DESIGN #############"
		if xst:
			current_dir = os.getcwd()
			sys_vhdl = os.path.join (current_dir + "/xst_synthesis/vhdl/sys.vhdl")
			print >> tcl_file, "read_vhdl -library aHiR_ieee_proposed $AHIR_RELEASE/vhdl/aHiR_ieee_proposed.vhdl"
			print >> tcl_file, "read_vhdl -library ahir $AHIR_RELEASE/vhdl/ahir.vhdl"
			print >> tcl_file, "read_vhdl -library sys_sys " + sys_vhdl

			ngc_file_cpu = os.path.join (current_dir + "/cpu/xst_synthesis/cpu.ngc")
			ngc_file_aggreagtor = os.path.join (current_dir + "/riffa_aggregator/xst_synthesis/aggregator.ngc")
			print >> tcl_file, "read_edif " + ngc_file_cpu
			print >> tcl_file, "read_edif " + ngc_file_aggreagtor + "\n"

			if protoboard:
				ngc_file_peripheral = os.path.join (current_dir + "/peripheral/xst_synthesis/peripheral.ngc")
				print >> tcl_file, "read_edif " + ngc_file_peripheral

		else:
			print >> tcl_file, "read_checkpoint " + dcp_file + "\n"

		print >> tcl_file, "############### SYNTHESIZE ##############"
		if (board == "vc709"):
			print >> tcl_file, "synth_design -top VC709Gen1x8If64 -part xc7vx690tffg1761-2 -include_dirs ../hdl/riffa_hdl/header/"
		if (board == "kc705"):
			print >> tcl_file, "synth_design -top KC705_Gen1x8If64 -part xc7k325tffg900-2 -include_dirs ../hdl/riffa_hdl/header/"
		print >> tcl_file, "report_utilization -file utilization_post_synth.rpt"
		print >> tcl_file, "opt_design"
		print >> tcl_file, "place_design"
		print >> tcl_file, "phys_opt_design"
		print >> tcl_file, "route_design"
		print >> tcl_file, "place_design -post_place_opt"
		print >> tcl_file, "route_design"
		print >> tcl_file, "report_timing_summary -file timing.rpt"
		print >> tcl_file, "report_utilization -file utilization_post_place_and_route.rpt"
		print >> tcl_file, "write_bitstream -force processor.bit"
	
		tcl_file.close()

		current_dir = os.getcwd()	
		os.chdir (implement_processor)
		os.system ("vivado -mode batch -source bitgen.tcl")	
		os.chdir (current_dir)

		print "\nInfo : Results of implementation are in " + implement_processor + "/\n"


def array (files_path):

	temp = files_path.split("/")
	global dcp_file

	ret_val = 0
	if temp[-1] == srch_fold:
		
		implement_path = os.path.join (topdir, files_path)
		#print implement_path
		current_dir = os.getcwd()
		os.chdir (implement_path)

		if clean:

			files = os.listdir (implement_path)
			for contents in files:
				if contents != "implement.tcl":
					if os.path.isdir (contents):
						shutil.rmtree(contents)
					else:
						os.remove(contents)
						
		else:
			ret_val = os.system ("vivado -mode batch -source implement.tcl")
			if ret_val != 0:
				print "Error : vivado -mode batch -source implement.tcl failed in %s" %implement_path
				sys.exit(1)
			
			files = os.listdir (implement_path)
			for contents in files:
				if contents.endswith(".dcp"):
					dcp_file = os.path.join (implement_path, contents)
					
		os.chdir (current_dir)
	return


def display_usage():
	print "------------------------------------------------------------------------------------------------------------------------"
	print "\nInfo:"
	print "-> Searches for all vivado_implement direcories present in current working directory (eg:/processor/Aa_v2/) and runs on vivado, implement.tcl present in them, which synthesizes the design and generates post synth vhd files and dcp files.\n"
	print "-> The script then implements the entire processor model by using top level dcp file or cpu and aggregator ngc files, along with riffa 2.2.0 and generates the bit file\n" 
	print "-> Results of this implementation are stored in /processor/FPGA/vc709/vc709_test_example_piyush/vivado_tcl/implement_processor/\n"
	print "------------------------------------------------------------------------------------------------------------------------"
	print "Options:"
	print "-c : to clean vivado_implement directories except for the implement.tcl file and implement_processor directory except for the chnl_tester.v file\n"
	print "-x : to use xst synthesis results (results of xilinx_synth.py - cpu and aggregator ngc files) for implementation and bit file generation, default is vivado synthesis result (this script - sys dcp file). If this option is selected then synthesis using implement.tcl is bypassed and directly implementation starts, so run xilinx_synth.py before using this option. Use xilinx 14.2 with xilinx_synth.py.\n"
	print "-x -c: to clean xst_synthesis directories except for the buildXST.sh file and implement_processor directory except for the chnl_tester.v file\n"
	print "-p: to generate bit file along with peripherals (cache, MMU, memory)\n"
	print "------------------------------------------------------------------------------------------------------------------------"
	sys.exit(0)


def main ():

	global clean
	xst = False
	ret_val = 0
	protoboard = False

	arg_list = sys.argv[1:]
	opts,args = getopt.getopt(arg_list,'h,c,x,p,')
	for option, parameter in opts:
		if option ==  '-h':
			display_usage()
		if option ==  '-c':
			clean = True
		if option ==  '-x':
			xst = True
		if option ==  '-p':
			protoboard = True


	if xst:
		if clean:
			ret_val = os.system ("xilinx_synth.py -c")
#		else:
#			ret_val = os.system ("xilinx_synth.py -N")
#
		if ret_val != 0:
			print "Error : xilinx_synth.py failed"
			sys.exit(1)

	else:
		# run implement.tcl in all nodes of processor
		for root, dirs, files in os.walk(".", topdown=False, followlinks=True):
			for name in dirs:
				files_path = os.path.join (root, name)
				#print files_path
				array (files_path)


	if ((board != "kc705") and (board != "vc709") and (board != "ml605")):
		print "Error: Board not specified, source it through exports.sh"
		sys.exit(1)

	generate_tcl (xst, protoboard)

	return 0


if __name__ == '__main__':

	ret = main()
	sys.exit(ret)
