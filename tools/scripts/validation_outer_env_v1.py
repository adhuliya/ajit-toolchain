#!/usr/bin/env python


# The script creates a text file containing list of absolute paths of 
# all .vprj files in the given root directories. It then calls gnu 
# parallel with validation_inner_env_v1.py and text file and an option for 
# processor executable as the arguments, to start parallel jobs and 
# prints total number of failed cases and total time of execution 
# after complete execution of all the jobs.


# No. of parallel jobs and timeout of job can be set by user. The script
# provides help on usage, cleans compiled directory created during normal 
# execution and gives a list of unattneded but valid .c/.s files. The 
# script also generates terminal log file and jobs log file.


# Written by Piyush P. Soni
#
# Modified by Ashfaque Ahammed
#   Added option -l to generate a log of register writes
#
# Modified by Neha Karanjkar
#	Changed default behavior of -T option
#	specifying -T will generate a trace file in the Aa model.
#	else no trace file is generated.
#
# Modified by Neha Karanjkar(8 June 2016)
#	Added option -s
#	To run the Aa/VHDL/FPGA model in single-stepping mode.
# Modified by Neha Karanjkar(14 July 2016)
#	Added option -X
#	To run the twin-cpu testbench (with FPGA and C models
#	of the cpu running in sync)



import os
import sys
import shutil
import getopt
import os.path
import subprocess
import pdb

def reportError(err_message):
   print "Error: " + err_message



def setGlobals(work_dir):

   global ajit_project_home
   global validation_exec_location

   # get location of this script
   global script_pathname 
   global validation_script_path


   # absolute path of file to store .vprj paths
   global path_src_file_list_file_c 
   global path_src_file_list_file_Aa 
   global path_src_file_list_file_vhdl
   global path_src_file_list_file_FPGA

   # give the search file 
   global search_file

   # path of validation_parallel2.py
   global path_validation_inner 
 
   # path joblogfile
   global path_joblogfile_c 
   global path_joblogfile_Aa 
   global path_joblogfile_vhdl
   global path_joblogfile_FPGA

   # path terminal log file
   global path_term_log_c 
   global path_term_log_Aa 
   global path_term_log_vhdl
   global path_term_log_FPGA

   # give path of compile script
   global path_compileToSparc 
  
   # give path of processor executable
   global path_proc_exec_c 
   global path_proc_exec_c_with_logger
   global path_proc_exec_aa
   global path_proc_exec_aa_withoutFPU 
   global path_proc_exec_vhdl 
   global path_proc_exec_FPGA 
   global path_proc_exec_twin_cpu 

   ret_val = 0
   validation_exec_location = os.environ.get('AJIT_AA_VALIDATION_EXECUTABLE_LOCATION')
   ajit_project_home = os.environ.get('AJIT_PROJECT_HOME')
   if (ajit_project_home == None):
	reportError("environment variable AJIT_PROJECT_HOME not defined")
	ret_val = 1

   # absolute path of file to store .vprj paths
   path_src_file_list_file_c = work_dir + "/src_file_list_file_c.txt"
   path_src_file_list_file_Aa = work_dir + "/src_file_list_file_Aa.txt"
   path_src_file_list_file_vhdl = work_dir + "/src_file_list_file_vhdl.txt"
   path_src_file_list_file_FPGA = work_dir + "/src_file_list_file_FPGA.txt"

   # give the search file 
   search_file = '.vprj'

   # path of validation_parallel2.py
   path_validation_inner = ajit_project_home + "/tools/scripts/validation_inner_env_v1.py"
 
   # path joblogfile
   path_joblogfile_c = work_dir + "/validation.job.C.log.txt"
   path_joblogfile_Aa = work_dir + "/validation.job.Aa.log.txt"
   path_joblogfile_vhdl = work_dir + "/validation.job.vhdl.log.txt"
   path_joblogfile_FPGA = work_dir + "/validation.job.FPGA.log.txt"

   # path terminal log file
   path_term_log_c = work_dir + "/validation.console.C.log.txt"
   path_term_log_Aa = work_dir + "/validation.console.Aa.log.txt"
   path_term_log_vhdl = work_dir + "/validation.console.vhdl.log.txt"
   path_term_log_FPGA = work_dir + "/validation.console.FPGA.log.txt"

   # give path of compile script
   path_compileToSparc = "compileToSparc.py"
  
   # give path of processor executable
   path_proc_exec_c = ajit_project_home + "/processor/C/testbench/bin/AJIT_cpu_cache_mmu_testbench_doval"

   # give path of processor executable with logger enabled
   path_proc_exec_c_with_logger = ajit_project_home + "/processor/C/testbench/bin/AJIT_testbench_logger_Mmu_v2"

   # eventually, the two executables will not be needed (after Aa stuff is merged with the C).
   # give path of processor executable
   path_proc_exec_aa = validation_exec_location + "/ajit_cpu_uarch_SW_env_v1"

   path_proc_exec_aa_withoutFPU = ajit_project_home + "/processor/Aa_withoutFPU/cpu/tests/environments/testbenches/bin/ajit_cpu_uarch_test_doval"
   path_proc_exec_vhdl = validation_exec_location + "/ajit_cpu_uarch_test_doval_riffa_sockpipes"
   path_proc_exec_FPGA = validation_exec_location + "/ajit_cpu_uarch_HW_env_v1"
   path_proc_exec_twin_cpu = validation_exec_location + "/ajit_cpu_uarch_FPGA_C_compare_env_v1"

   return ret_val


def array (temp, dirname, names):

	# write absolute paths of .vprj in a text file
	# create directories once
	# compiled/ folder to store compiled files and .results
	# log/ folder for storing log files
	# trace_files/ folder for storing trace files

	
	srch_file = temp[0]
	obj = temp[1]
	ignore_fpu = temp[2]
	generate_trace = temp[3]
	
	# get paths of the search file
	for name in names:
		if name.endswith(srch_file):

			split_dirname = dirname.split("/") 
			fpu_related1 = split_dirname[len(split_dirname)-2]
			fpu_related2 = split_dirname[len(split_dirname)-3]

			if ignore_fpu == "-f" and (fpu_related1 == "fp" or fpu_related1 == "floating_point" or fpu_related2 == "fp_ld_st"):
					pass
			
			else:
				path_log_fold = os.path.join (dirname, "log")	
				if not os.path.exists (path_log_fold) :
					os.makedirs (path_log_fold)
					
				path_compiled_fold = os.path.join (dirname, "compiled")
				if not os.path.exists (path_compiled_fold) :
					os.makedirs (path_compiled_fold)

				path_trace_fold = os.path.join (dirname, "trace_files")
				if not os.path.exists (path_trace_fold) :
					os.makedirs (path_trace_fold)

				path_srch_file = os.path.join (dirname, name)		
						
				# write all .vprj paths in the file		
				obj.write(path_srch_file + "\n") 
	return
	

def clean_all (srch_file, dirname, names):
	
	# clear c, assembly, log directories generated by previous execution
	
	# get paths of the search file only once every loop
	for name in names:
		if srch_file in name:

			# delete compiled directory
			path_compiled_fold = os.path.join (dirname, "compiled")
			if os.path.exists (path_compiled_fold) :				
				shutil.rmtree (path_compiled_fold)
				
			# delete log directory
			path_assembly_fold = os.path.join (dirname, "log")
			if os.path.exists (path_assembly_fold) :				
				shutil.rmtree (path_assembly_fold)				
	return

#removing all trace-file directory
def clean_trace (srch_file, dirname, names):
	for name in names:
		if srch_file in name:
			path_trace_fold = os.path.join (dirname, "trace_files")
			if os.path.exists (path_trace_fold) :				
				shutil.rmtree (path_trace_fold)				
	return

#def clean (srch_file, dirname, names):
	
	## clear c, assembly directories
	
	## get paths of the search file only once every loop
	#for name in names:
		#if srch_file in name:

			## delete compiled directory
			#path_compiled_fold = os.path.join (dirname, "compiled")
			#if os.path.exists (path_compiled_fold) :				
				#shutil.rmtree (path_compiled_fold)
	#return

	
def help_sec ():

	print " "
	print " -----------------------------------------------------------------------------------------------------------"
	print " USAGE:"
	print "        validation_outer_env_v1.py [MODEL] [OPTIONS] [-t TIMEOUT_IN_SECONDS] [-j JOBS_TO_RUN_IN_PARALLEL]  PATHS..."
	print " -----------------------------------------------------------------------------------------------------------"
	print " MODEL:"
	print "      -C : C executable"
	print "      -A : Aa executable"
	print "      -V : VHDL model"
	print "      -F : FPGA model"
	print "      -X : Twin-cpu testbench (with C and FPGA models of the cpu running in lockstep)"
	print " ------------------------"
	print " OPTIONS:"
	print "      -f : ignore FPU instructions. Use without_FPU model."
	print ""
	print "      -l : Generate a log of register writes"
	print "            The files are generated in trace_files/ folder"
	print "            with extension .C_trace for C model and .Aa_trace for Aa model"
	print " "
	print "      -s : Run in single-stepping mode"
	print "            Relevant only for Aa/VHDL/FPGA model."
	print ""
	print "      -T : Generate a detailed trace of activity for each instruction "
	print "           The trace file is generated in trace_files/ folder"
	print "            with extension .long_trace"
	print "           (CAUTION : A trace file can get very large)"
	print " ------------------------"
	print " CLEANUP:"
	print "      validation_outer_env_v1.py -c PATHS..."
	print "           cleans up the compiled/ log/ and trace_files/ "
	print "           folders recursively from PATH"
	print " -----------------------------------------------------------------------------------------------------------"
	print "  "

	return
	

def main ():
	
	temp = []
	jobs = ""
	timeout = ""
	choice = ""
	absolute_path = []
	ignore_fpu = ""
	generate_detailed_trace = ""
	trace_option = ""
	single_stepping_enabled = ""
	generate_trace = 0

	# main logs will be created in work-dir
	work_dir = os.getcwd()
	glob_status = setGlobals(work_dir)
        if(glob_status):
		return 1

   	# get location of this script
   	script_pathname = os.path.dirname(sys.argv[0])        
   	validation_script_path= os.path.abspath(script_pathname) 	#script is stored in this directory

	# options
	arg_list = sys.argv[1:]
	opts,args = getopt.getopt(arg_list,'j:t:c,h,A,C,V,f,F,X,l,s,T')

	#print " all relative paths = %s" %args
	if(len(opts)==0 or (opts[0][0]=='-h')):
		#print help, and return,
		help_sec();
		return 1
	elif(len(args)==0):
		print "*** ERROR ***: no paths were provided"
		#print help, and return,
		help_sec();
		return 1
	
	# get absolute paths from relative paths
	for abs_path in args:
		absolute_path.append (os.path.abspath (abs_path))
		
	args = absolute_path
	#print "all absolute paths = %s" %args

	
	for option, parameter in opts : 
		#print "option = %s" %option; print "parameter = %s" %parameter; print "opts = %s" %opts; print "args = %s" %args; print "arg_list = %s" % arg_list
		# clear compiled directory
		if option == '-c' :	
			for topdir in args:
				if os.path.exists (topdir):
					os.path.walk (topdir, clean_all, search_file)
					# trace-files will be cleaned only when clean all
					os.path.walk (topdir, clean_trace, search_file)
				else:
					print "Error : directory path doesnt exist %s" %topdir
					
			print "\n--------------cleaned---------------\n"
			return 0
		
		if option == '-h' :
			help_sec ()
			return 0
						
		if option == '-j' :
			jobs = parameter

		if option == '-t' :
			timeout = parameter

		if option == '-A' :
			choice = option
			
		if option == '-C' :
			choice = option
			
		if option == '-V' :
			choice = option

		if option == '-f' :
			ignore_fpu = option

		if option == '-T' :
			generate_detailed_trace = option

		if option == '-F' :
			choice = option
		
		if option == '-X' :
			choice = option

		if option == '-s' :
			single_stepping_enabled = option

		if option == '-l' :
            		trace_option = option
			generate_trace = 1
			
	if choice != "-C" and choice != "-A" and choice != "-V" and choice != "-F" and choice != "-X":
		print "Error : Provide the executable option ie '-A' or '-C' or '-V' or '-F' or '-X' "
		return 1
			
	if jobs == "" :
		print "Error in Usage :"
		print "Use as - validation_outer_env_v1.py -choice -t <timeout> -j <parallel_jobs> <path1> <path2> ...\n"
		return 1
	
	if timeout == "" :
		print "Error in Usage :"
		print "Use as - validation_outer_env_v1.py -choice -t <timeout> -j <parallel_jobs> <path1> <path2> ...\n"
		return 1


	if not os.path.exists (path_proc_exec_c) and choice == '-C':
		print path_proc_exec_c
		print "Error : terminating validation, cannot find processor executable"
		return 1

	if not os.path.exists (path_proc_exec_c_with_logger) and choice == '-C' and generate_trace:
		print path_proc_exec_c_with_logger
		print "Error : terminating validation, cannot find processor executable"
		return 1
	
	if choice == '-A':
		if ignore_fpu == '-f':	
			if not os.path.exists (path_proc_exec_aa_withoutFPU):
				print path_proc_exec_aa_withoutFPU
				print "Error : terminating validation, cannot find processor executable"
				return 1
		else:
			if not os.path.exists (path_proc_exec_aa):
				print path_proc_exec_aa
				print "Error : terminating validation, cannot find processor executable"
				return 1
		
	if not os.path.exists (path_proc_exec_vhdl) and choice == '-V':
		print path_proc_exec_vhdl
		print "Error : terminating validation, cannot find processor executable"
		return 1

	if not os.path.exists (path_proc_exec_FPGA) and choice == '-F':
		print path_proc_exec_FPGA
		print "Error : terminating validation, cannot find processor executable"
		return 1
	
	if not os.path.exists (path_proc_exec_twin_cpu) and choice == '-X':
		print path_proc_exec_twin_cpu
		print "Error : terminating validation, cannot find processor executable"
		return 1

	if choice == "-C":
		joblog = path_joblogfile_c
		srch_file = path_src_file_list_file_c
		terminal_log = path_term_log_c

	elif choice == "-A" :
		joblog = path_joblogfile_Aa
		srch_file = path_src_file_list_file_Aa
		terminal_log = path_term_log_Aa

	elif choice == "-V" :
		joblog = path_joblogfile_vhdl
		srch_file = path_src_file_list_file_vhdl
		terminal_log = path_term_log_vhdl

	elif (choice == "-F" or choice=="-X"):
		joblog = path_joblogfile_FPGA
		srch_file = path_src_file_list_file_FPGA
		terminal_log = path_term_log_FPGA
	

	# clear compiled, log directories generated by previous execution
	# check whether root dirs exist or not
	
	for topdir in args:
		if os.path.exists (topdir):
			os.path.walk (topdir, clean_all, search_file)
		else:
			print "ERROR : directory path doesnt exist %s" %topdir
			
	# create a file to store .vprj paths
	obj =  open (srch_file, 'w')
	temp.append(search_file)
	temp.append(obj)
	temp.append(ignore_fpu)
	temp.append(generate_trace)


	# search in all root paths and write in file
	for topdir in args:
		os.path.walk (topdir, array, temp)
	obj.close()
	
		
	# call other script using parallel and test file as
	# argument, test file have absolute paths of
	# all .vprj files
	# "-j + x" - x is number of jobs
	# "--timeout x" - x is timeout time in secs, timeout accuracy is 2 secs
	# for ms enter like 0.2 ms = 0.0002 s
	
	timeout = str(timeout)
	jobs = str(jobs)		

	os.system ("time " + "parallel --gnu " + "--timeout " + timeout + " --joblog " + joblog + " -j" + jobs 
	+ " -a " + srch_file + " python " + path_validation_inner + " " + choice + " " + trace_option + " " + single_stepping_enabled + " "  + generate_detailed_trace + " 2>&1 |" + " tee " + terminal_log)
	

	# calculate run time and failed cases from
	# log file of jobs generated by parallel

	
	with open(joblog) as openfile:
		start = False
		failed_cases = 0
		total_time = 0
		for line in openfile:
			if start:
				temp = line.split("	")
				# 0-success
				if (int(temp[6]) != 0):
					failed_cases = failed_cases + 1
				total_time = total_time + float(temp[3])
			if not start:
				start = True

	# calculate total vprjs
	with open(srch_file) as obj:
		lines = len(obj.readlines())

	ret = failed_cases
	failed_cases = str(failed_cases)
	total_time = str(total_time)
	lines = str(lines)
	
	# tee -a => append
	os.system ("echo " + "Note : total failed cases = " + failed_cases + " |"  + " tee -a " + terminal_log)
	os.system ("echo " + "Note : total time taken by all jobs = " + total_time + " s"+ " |"  + " tee -a " + terminal_log)
	os.system ("echo " + "Note : total vprj = " + lines + " |"  + " tee -a " + terminal_log)
	#print "Note : See %s for exact status of each program" %joblog
	print "Note : In validation job log, Exitval = '0'-no error, '1'-error, '-1'-timeout (program hanging or testbench hanging)"
	return ret
	
if __name__ == '__main__':

	ret = main()
	sys.exit(ret)
