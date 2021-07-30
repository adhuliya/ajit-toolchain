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
# Modified by Madhav Desai
#	for v3
#
#Modified by Gauri Patrikar

import os
import sys
import shutil
import getopt
import os.path
import subprocess
import pdb
import re

# get current directory path
current_dir = os.getcwd()


#some mem_map files contain a save instruction 
#at the beginning (0xf0004000).
#replace this with a nop
import fileinput
import re

ajit_project_home = os.environ.get('AJIT_PROJECT_HOME')

def setGlobals():

   global path_proc_exec

   path_proc_exec = " ";

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

def validate (exec_path, vals,  fileName, choice, single_stepping_enabled, generate_detailed_trace, test_file_string, include_string, result_file, log_file, trace_file, path_test_file_fold, path_srch_file, define_string, enable_reg_write_trace, reg_write_trace, generate_remap, new_link_script):
	

	if (generate_detailed_trace == '-T'):
		trace_option = "-t"
	else:
		trace_file = ""
		trace_option = ""
			
	
	command = ""; command1 = ""; command2 = ""	
	os.chdir (path_test_file_fold)
	
	# call compileTosparc.py
        if(new_link_script):
            command1 = "compileToSparc.ForValidation.py  " + " -E " + fileName + ".elf" + " -V " + fileName + ".vars"
            command2 = " -H " + fileName + ".hex" + " -M " + fileName + ".mmap" + " -O " + fileName + ".objdump" + test_file_string + include_string + define_string
            linker_opt = " -L ../../LinkerScript.lnk"
            command = command1 + command2 + linker_opt

        else:

	    command1 = "compileToSparc.ForValidation.py  " + " -E " + fileName + ".elf" + " -V " + fileName + ".vars"
	    command2 = " -H " + fileName + ".hex" + " -M " + fileName + ".mmap" + " -O " + fileName + ".objdump" + test_file_string + include_string + define_string
            linker_opt = " -L " + ajit_project_home + "/tools/linker/validationLinkerScript.lnk"
	    command = command1 + command2 + linker_opt
	
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
    	C_reg_write_trace = reg_write_trace + ".trace"

	return_val = 1;	

	#C model
    
	trace_option=""
	trace_file=""


	if(generate_detailed_trace):
		trace_option ="-v" #the verbose flag enables creation of a long trace in the C model.
	proc_exec = exec_path
        if(enable_reg_write_trace):
	    print  "Note: executing " + proc_exec + " -n " + vals[0] + " -t " + vals[1] + " -d -m " + mem_map_file + " -r " + result_file + " -l " + log_file + " -u " + vals[2] + trace_option + " " + trace_file + " -w " + C_reg_write_trace + " "
	    return_val = subprocess.call ([proc_exec,"-n", vals[0], "-t", vals[1],"-d", "-m", mem_map_file, "-r", result_file, "-l", log_file,"-u", vals[2], trace_option, trace_file,single_stepping_enabled, "-w", C_reg_write_trace])

        elif(generate_remap):
            mem_remap_file = os.path.join (path_test_file_fold, fileName + "." + "mmap" + "." + "remapped")
            hex_file = os.path.join (path_test_file_fold, fileName + "." + "hex")
            command3 = "generateMemoryMap_Byte "+  hex_file + " > " +  mem_map_file
            execSysCommand(command3)
            command4 = "remapMemmap ../../vmap.txt " +  mem_map_file +" " + mem_remap_file
            execSysCommand(command4)
            proc_exec = exec_path
            print  "Note: executing " + proc_exec + " -n " + vals[0] + " -t " + vals[1] + " -d -m " + mem_remap_file + " -r " + result_file + " -l " + log_file + " -u " + vals[2] + trace_option + " " + trace_file + " -w " + C_reg_write_trace + " "
            return_val = subprocess.call ([proc_exec,"-n", vals[0], "-t", vals[1], "-d", "-m", mem_remap_file, "-r", result_file, "-l", log_file,"-u", vals[2], trace_option, trace_file,single_stepping_enabled,"-w", C_reg_write_trace])
        
        
        
        else:
            print  "Note: executing " + proc_exec + " -n " + vals[0] + " -t " + vals[1] + " -d -m " + mem_map_file + " -r " + result_file + " -l " + log_file + " -u " + vals[2] + trace_option + " " + trace_file + " -w " + C_reg_write_trace + " "
            return_val = subprocess.call ([proc_exec,"-n", vals[0], "-t", vals[1], "-d", "-m", mem_map_file, "-r", result_file, "-l", log_file,"-u", vals[2], trace_option, trace_file,single_stepping_enabled])
 

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
		
def get_cores (path_srch_file) :

        #include = []
        cores = '1'
        threads = '1'
        version = '32'
        with open(path_srch_file) as src:
                for line in src:
                        if "CORES" in line:
                           cores = (re.split(r"[\n=\s]*", line)[1])
                           print cores 
                        if "THREADS" in line:
                            threads = (re.split(r"[\n=\s]*", line)[1])

                        if "VERSION" in line:
                            version = (re.split(r"[\n=\s]*", line)[1])
                    
                        
                return (cores, threads, version)


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

	setGlobals()

	# options
	generate_detailed_trace = ""
	single_stepping_enabled = ""
	include_string = ""
	test_file_string = ""
	error_count = 0
    	generate_trace = 0
	generate_remap = 0
        new_link_script = 0
	arg_list = sys.argv[1:]
        opts,args = getopt.getopt(arg_list,'E:l,s,T,p,L')
	
        exec_path = None
        choice  = None
        
	for option, parameter in opts :
                #print "option = %s" %option; 
                #print "parameter = %s" %parameter; print "opts = %s" %opts; print "args = %s" %args; print "arg_list = %s" % arg_list
	        if   option == '-T' :
                        generate_detailed_trace = option
                elif option == '-s' :
                        single_stepping_enabled = option
                elif option == '-l' :
                        generate_trace = 1
                elif option == '-p' :
                        generate_remap = 1
                elif option == '-L' :
                    new_link_script = 1

                elif option == '-E' :
			exec_path = parameter
                        print "Info: override execution path to " + parameter


        print exec_path
        print "Info: execution path is " + exec_path

	path_srch_file = args[0]
	
	dirname, name = os.path.split (path_srch_file)

	path_log_fold = os.path.join (dirname, "log")
		
	path_compiled_fold = os.path.join (dirname, "compiled")

    	path_trace_fold = os.path.join (dirname, "trace_files")
	
	# parse .vprj to get test file names
	test_file = get_test_file (path_srch_file)
        vals = get_cores (path_srch_file)
        print "Info : CORES=%s, THREADS=%s, VERSION=%s" %vals

	
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
	
	return_val = validate (exec_path, vals, fileName, choice, single_stepping_enabled, generate_detailed_trace, test_file_string, include_string, path_result_file, path_log_file, path_trace_file, path_test_file_fold, path_srch_file, define_string, generate_trace, path_reg_write_trace_file, generate_remap, new_link_script);

	if (return_val > 255):
		return_val = 255
	return return_val
	
if __name__ == '__main__':
	ret_val = main()
	sys.exit(ret_val)
