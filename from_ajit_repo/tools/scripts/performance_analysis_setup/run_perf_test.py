#!/usr/bin/env python

# The script compiles the test case using validation_outer_env_Aa_v3.py
# script and generates InitValPackage.vhdl using genInitValPackFromMemmap
# from mmap file. The script also generates modelsim do file and simulates
# the vhdl model of AJIT processor by running modelsim in one process and 
# c executable in another process.
#
#
#
# Author : Piyush P. Soni & Aswin Jith
#
#

import os
import subprocess
import sys
import getopt
import signal
import os.path
import shutil

AJIT_PROJECT_HOME = os.environ.get('AJIT_PROJECT_HOME')
VSIM_PATH = AJIT_PROJECT_HOME+"/processor/Aa_v3/sys/modelsim/"
reference_do_file = AJIT_PROJECT_HOME+"/tools/scripts/performance_analysis_setup/vsimInitMem_perf.do"
VHDL_SIMULATOR = os.environ.get('AJIT_DEFAULT_VHDL_SIMULATOR')

def execCmd (cmd):
        print "\n Info: executing command " 
        print cmd
	os.system(cmd)

def help_sec ():
	print " "
	print " -----------------------------------------------------------------------------------------------------------"
	print " USAGE:"
	print "        run_perf_test.py [-r TIME IN ns ] [-t TEST CASE .s FILE] [-M number_of_address_bits for genInitValPackFromMemmap]"
	print " CLEAN UP:"
	print "        run_perf_test.py [-c path ] "
	print " -----------------------------------------------------------------------------------------------------------"
	print " EXAMPLE:"
	print "        run_perf_test.py -r 2000 -t ../../add.s -M 16"
	print "        run_perf_test.py -c ./"
	print " -----------------------------------------------------------------------------------------------------------\n"

	return

def RepresentsInt(s):
    try: 
        int(s)
        return True
    except ValueError:
        return False
        
def clean_all (srch_file, dirname, names):
	for name in names:
		if srch_file in name:
			print "\n Info : Current search directory is ", dirname
			print "\n Info : Found ", srch_file 
			if (os.path.exists (dirname + "/InitValPackage.vhdl")):
				print "\n Info : Found  InitValPackage.vhdl"
				print "\n Info : Deleting ", dirname
				shutil.rmtree (dirname)
			else:
				print "\n Info : InitValPackage.vhdl not found"
				print "\n Info : " + dirname + " IS NOT DELETED"
	return
		
def main():
	
	arg_list = sys.argv[1:]
	opts,args = getopt.getopt(arg_list,'r:t:M:h,c:')
	
	run_time = ""
	test_case = ""
	number_of_address_bits = ""
	cleaning_path = ""
	clean = False
	
	for option, parameter in opts :
		if option == '-c' :
			clean = True	
			cleaning_path = parameter
		if option == '-r' :
			run_time = parameter
		if option == '-t' :
			test_case = parameter
		if option == '-M' :
			number_of_address_bits = parameter			
		if option == '-h' :
			help_sec ()
			return 0		

	if clean:
		print "\n Info : Cleaning selected: seraching for performance_characterization directories and deleting it"
		if cleaning_path == "":
			print "\n Error : specify path!"
			help_sec ()
			return 1
		else:
			abs_cleaning_path = os.path.abspath (cleaning_path)
			print "\n Info : Searching for performance_characterization directories in ", abs_cleaning_path + " area"
			if os.path.exists (abs_cleaning_path):
				os.path.walk (abs_cleaning_path, clean_all, "vsimInitMem_perf.do")
				return 0
			else:
				print "Error : directory path doesnt exist %s" %abs_cleaning_path
				return 1
				
	if run_time == "":
		print "\n Error : specify run time!"
		help_sec ()
		return 1

	if not(RepresentsInt(run_time)):
		print "\n Error : specify run time correctly! Entered value = ",run_time
		help_sec ()
		return 1		
		
	if test_case == "":
		print "\n Error : specify test case!"
		help_sec ()
		return 1

	if number_of_address_bits == "":
		print "\n Error : specify number_of_address_bits for genInitValPackFromMemmap!"
		help_sec ()
		return 1

	if VHDL_SIMULATOR != "modelsim":
		print "\n Error : Set the default simulator to modelsim from exports.sh"
		return 1			
							
	test_case_directory = os.path.dirname(test_case)
	test_case_abs_path = os.path.abspath (test_case_directory)
	test_case_filename =  os.path.basename(test_case).split(".")[0]
	
	if not (os.path.exists (test_case_abs_path + "/" + test_case_filename + ".vprj")):
		print "Error : " + test_case_filename + ".vprj not found, create " + test_case_filename + ".vprj and try again!"	
		return 1 
			
	print "\n INFO: Running for", run_time ,"ns "
	print "\n INFO: number_of_address_bits selected is ", number_of_address_bits
	print "\n INFO: Running testcase ", test_case_filename
	print "\n INFO: VHDL Simulator selected is ", VHDL_SIMULATOR
	print "\n INFO: Test case directory is ", test_case_abs_path
										
	if os.path.exists ("performance_characterization"):
		print ("\n Info: Removing old performance_characterization directory")
		rm_cmd = "rm -rf performance_characterization"
		execCmd (rm_cmd)
		
	os.mkdir ("performance_characterization")
	print ("\n Info: Creating performance_characterization directory")
	os.chdir ("performance_characterization")
	print ("\n Info: Changing to performance_characterization directory")
			

	print "\n INFO: Compiling the test case using validation script"	
	validation_cmd = "validation_outer_env_v3.py -t 2 -j 1 -A "+ test_case_abs_path
	execCmd(validation_cmd)

	mmap_path = test_case_abs_path +"/compiled/"+test_case_filename+"/"+test_case_filename+".mmap"
	if not(os.path.exists(mmap_path)):
		print " \n Error: mmap file could not be generated - ", mmap_path
		return 1
		
	genInit_cmd = "genInitValPackFromMemmap " + number_of_address_bits + " < " + mmap_path + " > " + "InitValPackage.vhdl"
	execCmd(genInit_cmd)

	print "\n INFO: Creating modelsim do file from ", reference_do_file
	output_do_file = os.getcwd() + "/vsimInitMem_perf.do"
	with open(reference_do_file) as src:
		with open (output_do_file, "w") as load:
			for line in src:
				if not "run ---ns" in line:
					load.write(line)
				else:
					load.write("run " + run_time + "ns \n")	
		
	if (os.path.exists("InitValPackage.vhdl")):
		print "\n INFO: Found InitValPackage.vhdl"
		p2 = subprocess.Popen(["ajit_chip_vhdl_sim_testbench","-m",mmap_path])
		p1 = subprocess.Popen(["run_modelsim.sh",output_do_file])
		p1.wait()
		#os.kill(p2.pid,signal.SIGTERM)
		p2.terminate()
	else:
		print"\n ERROR: InitValPackage.vhdl not found"
		return 1

	return 0

if __name__ == '__main__':
	ret_val = main()
	sys.exit(ret_val)
