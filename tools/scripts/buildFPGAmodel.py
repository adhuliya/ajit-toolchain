#!/usr/bin/env python
#
# 	buildFPGAModel.py constructs an .prj and .scr files for xilinx xst.
#
# 	Borrows a lot from buildGhdlSimulationModel.py.
#
#   The script walks the directory tree starting from the
#   working-directory = AJIT_PROJECT_HOME + "/processor/Aa"
#  
#   If a directory named vhdl/ is encountered:
#      - it searches for all subdirectories in vhdl/
#        for each subdirectory (say foo) in vhdl, it
#        looks for vhdl files (extension .vhdl) and adds
#        to library "foo".
#
#   The VHDL files are then added to a .prj file. The .prj file is then 
#	appened with riffa files. The .scr file carries the 
#	build info.
#
#
#	Author: Piyush P. Soni
# 	
#

import os
import os.path
import getopt
import sys
import glob
import commands
import pdb
import subprocess

    
# set global variables used in this script from environment
# variables.
def setGlobals(ahir_release_path, ajit_project_home_path):

    global AHIR_RELEASE
    global AJIT_PROJECT_HOME   
    global AHIR_VHDL_LIB

    AHIR_RELEASE=ahir_release_path
    AJIT_PROJECT_HOME=ajit_project_home_path
    AHIR_VHDL_LIB=AHIR_RELEASE + "/vhdl"


def logInfo(mesg):
    print "Info: " + mesg

def logError(mesg):
    print "Error: " + mesg

def logWarning(mesg):
    print "Warning: " + mesg


# VHDL -> simulation.
def printXilinxPrjFile(vhdl_lib_file_pairs, path_prj_file):

	 prj_file = open(path_prj_file,"w")

	 ghdl_cmd = "vhdl aHiR_ieee_proposed " + AHIR_VHDL_LIB + "/aHiR_ieee_proposed.vhdl"  
	 print >> prj_file, ghdl_cmd

	 ghdl_cmd = "vhdl ahir " + AHIR_VHDL_LIB + "/ahir.vhdl"  
	 print >> prj_file, ghdl_cmd

	 for ppair in vhdl_lib_file_pairs:
		vhdl_lib  = ppair[0]
		vhdl_file = ppair[1]
		
		
		# change the top module lib to work, same done in vhdl code also
		#if vhdl_lib == "sys_sys":
		#	vhdl_lib = "work"
		
		ghdl_cmd  = "vhdl " + vhdl_lib + " " + vhdl_file
		print >> prj_file, ghdl_cmd

	 prj_file.close()

	 return 0


# this function not needed if /xst/*.scr is used
def printXilinxScrFile (top_module, path_scr_file, path_prj_file):
	
	with open (path_scr_file, "w") as tmp:
		tmp.write ("""run
-ifn """ + path_prj_file + """
-ofn xilinx_synth
-ifmt mixed
-ofmt NGC
-p xc6vlx760-2-ff1760
-top """ + top_module + """
-write_timing_constraints yes
-hierarchy_separator _
-bus_delimiter <>
-fsm_extract no
-ram_extract yes
-rom_extract yes
-resource_sharing yes
-max_fanout 16
-register_duplication yes
-equivalent_register_removal yes
-optimize_primitives yes
-iuc yes
-keep_hierarchy yes
-opt_mode speed
-opt_level 2
-safe_implementation yes
-iobuf no
-use_new_parser yes
""")	
	return 0
	

def analyse_report (path_srp_file):

	for line in reversed(open (path_srp_file).readlines()):
		if "Number of Slice LUTs:" in line:
			print line
			
		if "Number of Slice Registers:" in line:
			print line

			return 0

	

def parseOptions(opts):
	work_area = os.getcwd()
        output_directory = work_area
    	for option, parameter in opts:
            if option ==  '-w':
 	       work_area = os.path.abspath (parameter)
               logInfo("work-area  = " + parameter + ".")
	    if option == '-o':
 	       output_directory = os.path.abspath (parameter)
               logInfo("output-directory  = " + parameter + ".")
             
	return work_area, output_directory

def main():
	ahir_release = os.environ.get('AHIR_RELEASE')
	ajit_project_home = os.environ.get('AJIT_PROJECT_HOME')
    
	if(ahir_release == None):
		logError (" environment variable AHIR_RELEASE is not defined." )
		return 1

	if(ajit_project_home == None):
		logError (" environment variable AJIT_PROJECT_HOME is not defined." )
		return 1

    	arg_list = sys.argv[1:]
    	opts,args = getopt.getopt(arg_list,'a:w:t:T:S:E:C:A:I:F:hs:RW:Do:')
	
	work_area, output_directory = parseOptions(opts)
	
	# set all the global constants (include-paths, libraries etc. etc.)
	setGlobals(ahir_release, ajit_project_home)

	xilinx_synth = output_directory
	if not (os.path.exists (xilinx_synth)):
		os.makedirs (xilinx_synth)
	
	path_scr_file = os.path.join (xilinx_synth, "xilinx_synth.scr")
	path_prj_file = os.path.join (xilinx_synth, "xilinx_synth.prj")
	path_srp_file = os.path.join (xilinx_synth, "xilinx_synth.srp")	
		

	# 0 = success.
	ret_status  = 0

	# vhdl lib-file pairs
	vhdl_lib_file_pairs = []


	top_vhdl_file = ""

	# as you walk, execute the makefiles that you
	# see.  This will produce aa2c directories 
	# and also hsys files.
	for root, dirs, files in os.walk(work_area, topdown=False, followlinks=True):
		for name in dirs:
		   if(name == "vhdl"):
			  full_name = os.path.join(root, name)
			  for vhdl_lib in os.listdir(full_name):
				  vhdl_lib_dir = os.path.join(full_name, vhdl_lib)
				  if(os.path.isdir(vhdl_lib_dir)):
					 for vhdl_file in os.listdir(vhdl_lib_dir):
						root, ext = os.path.splitext(vhdl_file) 
						if((ext == ".vhdl") and (not "_test_bench" in root)):
							# remember last vhdl-file seen (top will be the laaast).
							top_vhdl_file = vhdl_file 
							logInfo("added library,file pair " + vhdl_lib_dir + ", " + vhdl_file) 
							full_vhdl_file_path = os.path.join(vhdl_lib_dir, vhdl_file)
							ppair = (vhdl_lib, os.path.abspath(full_vhdl_file_path))
							vhdl_lib_file_pairs.append(ppair)
                 
    
   
	if(len(vhdl_lib_file_pairs) > 0):
		ret_status = printXilinxPrjFile(vhdl_lib_file_pairs, path_prj_file)

		# top entity?
		node_vhdl_file_name = os.path.basename (top_vhdl_file)
		
		top_module, extension = os.path.splitext (node_vhdl_file_name)
		# logInfo("top entity name = " + top_module)
		

		# Make the .scr file, by copying from /xst/pcieXST.scr
		#path_src_file = os.path.join (xilinx_synth, "xst/pcieXST.scr")
		#with open (path_src_file) as src:
		#	with open (path_scr_file, "w") as load:
		#		for line in src:
		#				load.write(line) 
								
								
		# Make .scr using the function in this python script
		# commented for now since scr is taken from xst
		# ret_status = printXilinxScrFile(top_module, path_scr_file, path_prj_file)

		# Now copy riffa related paths from /xst/pcie.prj to this .prj
		#path_src_file = os.path.join (xilinx_synth, "xst/pcie.prj")
		#with open (path_src_file) as src:
		#	with open (path_prj_file, "a") as load:
		#		for line in src:
		#				load.write(line) 

		
		# no need to do this since compile.pl is used						
		# generate ngc file using xilinx xst
		#subprocess.call ("source /CAD/Xilinx/14.2/ISE_DS/settings64.sh", shell=True)
		#current_dir = os.getcwd()
		#os.chdir (xilinx_synth)
		#os.system ("xst -ifn " + path_scr_file)
		#os.chdir(current_dir)
		
		#analyse_report (path_srp_file)
	
	else:
		logInfo("no VHDL files found.") 
		 
	return ret_status


if __name__ == '__main__':
    ret_val = main()
    sys.exit(ret_val)
