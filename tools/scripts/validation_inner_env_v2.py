#!/usr/bin/env python

# This script is called by validation_outer.py.
# The argument to the script is absolute path of a .vprj file and an option 
# for processor executable given by gnu parallel. It parses .vprj to get sources
# (.c/.s), includes and defines and make .results file. It then calls compileToSparc.py 
# to build the sources of a .vprj, then loads the build on processor 
# model and logs. It creates seperate directories for all .vprj and for log files.
# It returns 0 as success, 1 as failure.


# Written by Piyush P. Soni
#
# Modified by Ashfaque Ahammed
#	Added register-write-trace logging
#	use -l to log the register writes


import os
import sys
import shutil
import getopt
import os.path
import subprocess


ajit_project_home = os.environ.get('AJIT_PROJECT_HOME')
validation_exec_location = os.environ.get('AJIT_AA_VALIDATION_EXECUTABLE_LOCATION')


# give path of processor executable
path_proc_exec_c = ajit_project_home + "/processor/C/testbench/bin/AJIT_testbench_doval_icache_dcache_aa2c_mmu_aa2c"

# give path of processor executable with register-write logger
# path_proc_exec_c_with_logger = ajit_project_home + "/processor/C/testbench/bin/AJIT_cpu_cache_mmu_testbench_logger"
path_proc_exec_c_with_logger = ajit_project_home + "/processor/C/testbench/bin/AJIT_testbench_logger_icache_dcache_aa2c_mmu_aa2c"

# give path of processor executable
path_proc_exec_aa = validation_exec_location + "/ajit_cpu_uarch_SW_env_v2"

path_proc_exec_aa_withoutFPU = ajit_project_home + "/processor/Aa_withoutFPU/cpu/tests/environments/testbenches/bin/ajit_cpu_uarch_test_doval"

path_proc_exec_vhdl = validation_exec_location + "/ajit_cpu_uarch_test_doval_riffa_sockpipes"

path_proc_exec_FPGA = validation_exec_location + "/ajit_cpu_uarch_HW_env_v2"
path_proc_exec_twin_cpu = validation_exec_location + "/ajit_cpu_uarch_FPGA_C_compare_env_v2"

# get currnet directory path
current_dir = os.getcwd()




#some mem_map files contain a save instruction 
#at the beginning (0xf0004000).
#replace this with a nop
import fileinput
import re
def replaceSaveInstructionWithNop(mem_map_file):
	replaced=False
	for line in fileinput.input(mem_map_file, inplace=True):
		if("f0004000 	9d") in line :
			print line.replace("f0004000 	9d","f0004000 	01"),
			replaced=True
		elif("f0004001 	e3") in line :
			print line.replace("f0004001 	e3","f0004001 	00"),
		elif("f0004002 	bf") in line :
			print line.replace("f0004002 	bf","f0004002 	00"),
		elif("f0004003 	a0") in line :
			print line.replace("f0004003 	a0","f0004003 	00"),
		else:
			print line,
	if replaced:
		print "NOTE : Replaced save instruction at 0xf0004000 with a nop in the memory map file"



def execSysCommand(cmd):
        print  "Note: executing command: " + cmd
	ret_val = os.system(cmd)
        return(ret_val);

def validate (fileName, choice, ignore_fpu, single_stepping_enabled, generate_detailed_trace, test_file_string, include_string, result_file, log_file, trace_file, path_test_file_fold, path_srch_file, define_string, enable_reg_write_trace, reg_write_trace):
	

	if (generate_detailed_trace == '-T'):
		trace_option = "-t"
	else:
		trace_file = ""
		trace_option = ""
	#ignore singel-stepping option for 
	#all models other than Aa/VHDL/FPGA
	if(single_stepping_enabled == '-s'):
		if(choice!='-A' and choice !='-V' and choice !='-F' and choice !='-X'):
			single_stepping_enabled=""

	
	else:
	#for the twin-cpu model (-X)
	#single stepping is compulsory.
	#the comparison does not make sense otherwise.
		if(choice=='-X'):
			print" Forcing single stepping mode for twin-cpu validation (-X option)"
			single_stepping_enabled='-s'
				
			
	
	command = ""; command1 = ""; command2 = ""	
	os.chdir (path_test_file_fold)
	
	# call compileTosparc.py
	command1 = "compileToSparc.py " + " -E " + fileName + ".elf" + " -V " + fileName + ".vars"
	command2 = " -H " + fileName + ".hex" + " -M " + fileName + ".mmap" + " -O " + fileName + ".objdump" + test_file_string + include_string + define_string
	command = command1 + command2
	
	# execute compileTosparc.py
	ret_code = execSysCommand(command)
	
	if ret_code != 0:
		print "ERROR : compile to sparc of %s is unsuccessful" %path_srch_file
	#else:
		#print "Note : compile to sparc of %s is successful" %path_srch_file   

	mem_map_file = os.path.join (path_test_file_fold, fileName + "." + "mmap")

	#some mem_map files contain a save instruction at the beginning (0xf0004000).
	#replace this with a nop
	replaceSaveInstructionWithNop(mem_map_file)

	# load on processor model
	# return_val = 0 is success 
    	c_reg_write_trace = reg_write_trace + ".C_trace"
    	aa_reg_write_trace = reg_write_trace + ".Aa_trace"
	
	if (choice == '-C') :
        	if(enable_reg_write_trace):
			print  "Note: executing " + path_proc_exec_c_with_logger + " " + mem_map_file + " " + result_file + " " + log_file + " " + c_reg_write_trace
			return_val = subprocess.call ([path_proc_exec_c_with_logger, mem_map_file, result_file, log_file, c_reg_write_trace])
        	else:
			print  "Note: executing " + path_proc_exec_c + " " + mem_map_file + " " + result_file + " " + log_file
			return_val = subprocess.call ([path_proc_exec_c, mem_map_file, result_file, log_file])
	
	if (choice == '-A') :
		if (ignore_fpu == '-f') :
			proc_exec = path_proc_exec_aa_withoutFPU
		else:
			proc_exec = path_proc_exec_aa
        	if(enable_reg_write_trace):
		    	print  "Note: executing " + proc_exec + " -m " + mem_map_file + " -r " + result_file + " -l " + log_file + " " + trace_option + " " + trace_file + " -w " + aa_reg_write_trace + ""+single_stepping_enabled 
		    	return_val = subprocess.call ([proc_exec, "-m", mem_map_file, "-r", result_file, "-l", log_file, trace_option, trace_file, "-w", aa_reg_write_trace,single_stepping_enabled])
        	else:
		    	print  "Note: executing " + proc_exec + " -m " + mem_map_file + " -r " + result_file + " -l " + log_file + " " + trace_option + " " + trace_file + " "  + single_stepping_enabled 
		    	return_val = subprocess.call ([proc_exec, "-m", mem_map_file, "-r", result_file, "-l", log_file, trace_option, trace_file,single_stepping_enabled])
		
	if (choice == '-V') :
        	if(enable_reg_write_trace):
		    	print  "Note: executing " + path_proc_exec_vhdl + " -m " + mem_map_file + " -r " + result_file + " -l " + log_file + " -w " + aa_reg_write_trace + " " + single_stepping_enabled
		    	return_val = subprocess.call ([path_proc_exec_vhdl, "-m", mem_map_file, "-r", result_file, "-l", log_file, "-w", aa_reg_write_trace,single_stepping_enabled])
        	else:
		    	print  "Note: executing " + path_proc_exec_vhdl + " -m " + mem_map_file + " -r " + result_file + " -l " + log_file + " " + single_stepping_enabled
		    	return_val = subprocess.call ([path_proc_exec_vhdl, "-m", mem_map_file, "-r", result_file, "-l", log_file,single_stepping_enabled])


	if (choice == '-F') :
        	if(enable_reg_write_trace):
		    	print  "Note: executing " + path_proc_exec_FPGA + " -m " + mem_map_file + " -r " + result_file + " -l " + log_file + " -w " + aa_reg_write_trace+ " " + single_stepping_enabled
		    	return_val = os.system (path_proc_exec_FPGA + " -m " + mem_map_file + " -r " + result_file + " -l " + log_file + " -w " + aa_reg_write_trace+ " " + single_stepping_enabled)
        	else:
		    	print  "Note: executing " + path_proc_exec_FPGA + " -m " + mem_map_file + " -r " + result_file + " -l " + log_file+ " " + single_stepping_enabled
		    	return_val = os.system (path_proc_exec_FPGA + " -m " + mem_map_file + " -r " + result_file + " -l " + log_file + " " + single_stepping_enabled)
	
	if (choice == '-X') :
        	if(enable_reg_write_trace):
		    	print  "Note: executing " + path_proc_exec_twin_cpu + " -m " + mem_map_file + " -r " + result_file + " -l " + log_file + " -w " + aa_reg_write_trace+ " " + single_stepping_enabled
		    	return_val = os.system (path_proc_exec_twin_cpu + " -m " + mem_map_file + " -r " + result_file + " -l " + log_file + " -w " + aa_reg_write_trace+ " " + single_stepping_enabled)
        	else:
		    	print  "Note: executing " + path_proc_exec_twin_cpu + " -m " + mem_map_file + " -r " + result_file + " -l " + log_file+ " " + single_stepping_enabled
		    	return_val = os.system (path_proc_exec_twin_cpu + " -m " + mem_map_file + " -r " + result_file + " -l " + log_file + " " + single_stepping_enabled)



	if return_val != 0:
		print "ERROR : validation of %s is unsuccessful" %path_srch_file
	else:
		print "Note: validation of  %s is successful" %path_srch_file   

	os.chdir (current_dir)
	return return_val
	

def mak_result_file (path_srch_file, result_file) :

	# strip out result part
	always_print = False
	with open (path_srch_file) as src:
		with open (result_file, "w") as load:
			for line in src:
				if always_print:
					load.write(line) 
				if not always_print and "RESULTS" in line:
					always_print = True
	return


def get_defines (path_srch_file) :
		
	#include = []
	defines = ""
	found = False
	with open(path_srch_file) as src:
		for line in src:
			
			if found and "RESULTS" in line:
				return defines
				
			if found:
				if line != "\n":
					temp = line.split("\n")
					defines += " -D " + temp[0] + " "

			if "DEFINES" in line:
				found = True
		return ""
		# if no includes field	
		

def get_include (path_srch_file) :
		
	#include = []
	include = ""
	found = False
	with open(path_srch_file) as src:
		for line in src:
			if (found and ("DEFINES" in line or "RESULTS" in line)):
				return include
				
			if found:
				if line != "\n":
					temp = line.split("\n")				
					include += " " + temp[0] + " "

			if "INCLUDES" in line:
				found = True
		return ""
		# if no includes field		
		

def get_test_file (path_srch_file) :
	
	test_file = []
	
	with open(path_srch_file) as openfile:
		for line in openfile:
			if "SOURCES" in line:
				for word in line.split():
					if ".c" in word or ".s" in word:
						test_file.append(word)
			return test_file
		return []
		# if no sources field

	
def main ():

	# options
	ignore_fpu = ""
	generate_detailed_trace = ""
	single_stepping_enabled = ""
	include_string = ""
	test_file_string = ""
	error_count = 0
    	generate_trace = 0
	
	arg_list = sys.argv[1:]
	opts,args = getopt.getopt(arg_list,'C,A,V,f,F,X,l,s,T')
	
	for option, parameter in opts :
		if option == '-f' :
			ignore_fpu = option
		elif option == '-T' :
			generate_detailed_trace = option
		elif option == '-s' :
			single_stepping_enabled = option
	        elif option == '-l' :
        		generate_trace = 1
        	else:
			if(option != '-l'):
				choice = option

	path_srch_file = args[0]
	
	dirname, name = os.path.split (path_srch_file)

	path_log_fold = os.path.join (dirname, "log")
		
	path_compiled_fold = os.path.join (dirname, "compiled")

    	path_trace_fold = os.path.join (dirname, "trace_files")
	
	# parse .vprj to get test file names
	test_file = get_test_file (path_srch_file)
	#print test_file
	
	if len(test_file) == 0:
		print "ERROR : 'SOURCES' list empty/not present in %s" %path_srch_file
		return 1
	
	for obj in test_file:
		
		fileName, fileExtension = os.path.splitext(obj)
		path_test_file = os.path.join (dirname, obj)
	
		if not os.path.exists (path_test_file):
			print "ERROR : test file doesnt exist : %s" %path_test_file
			return 1 
		
		if fileExtension == ".c":
			test_file_string += " -c " + path_test_file + " "
			
		if fileExtension == ".s":
			test_file_string += " -s " + path_test_file + " "
			
	#print test_file_string

	
	include_string = get_include (path_srch_file)
	#print "include = %s" %include_string 
	if include_string == "":
		print "Warning : 'INCLUDES' list empty/not present/incorrect in %s" %path_srch_file

		
	define_string = get_defines (path_srch_file)
	if define_string == "":
		print "Warning : 'DEFINES' list empty/not present in %s" %path_srch_file
	#print "define_string = %s" %define_string 
	
	
	# give log file location.	
	# create fold for each test file.
	# make .results file.
	# call validate function for the .vprj.
	
	fileName, fileExtension = os.path.splitext(name)
	path_log_file = os.path.join (path_log_fold, fileName + "." + "log")

	path_trace_file = os.path.join (path_trace_fold, fileName + "." + "long_trace")

    	path_reg_write_trace_file = os.path.join (path_trace_fold, fileName)

	path_test_file_fold = os.path.join (path_compiled_fold, fileName)				
	os.makedirs (path_test_file_fold)
					
	path_result_file = os.path.join (path_test_file_fold, fileName + "." + "results")
	mak_result_file (path_srch_file, path_result_file)
	
	if os.path.getsize (path_result_file) == 0:
		print "ERROR : 'RESULTS' section empty/not present in %s" %path_srch_file
		return 1
		
		
	# validate
	# error_count : failed_cases per job of parallel
	# which are stored in joblogfile.
	# return_val = 0
	
	print "Note: vprj %s has test files : %s" %(path_srch_file, test_file)
	
	return_val = validate (fileName, choice, ignore_fpu, single_stepping_enabled, generate_detailed_trace, test_file_string, include_string, path_result_file, 
	path_log_file, path_trace_file, path_test_file_fold, path_srch_file, define_string, generate_trace, path_reg_write_trace_file);

	if (return_val > 255):
		return_val = 255
	return return_val
	
if __name__ == '__main__':
	ret_val = main()
	sys.exit(ret_val)
