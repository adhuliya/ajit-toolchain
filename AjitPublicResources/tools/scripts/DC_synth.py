#!/usr/bin/env python

# Searches for all dc_synthesis direcories present in current working directory 
# and runs buildDC.sh present in them, which generates post synth vhd files, timing, area, sdc reports.
# The script also cleans the work directory, dc_synthesis directories except the buildDC.sh file.
# 
#
# Author : Ch V Kalyani
#
#

import os
import sys
import getopt
import os.path
import shutil

topdir = os.getcwd()
srch_fold = "dc_synthesis"


clean = False

def SetGlobals():
    global AHIR_RELEASE
    global AHIR_IEEE_LIBRARY
    global AHIR_LIBRARY
    global AHIR_NoASSERTS
    global AJIT_PROJECT_HOME
    global work_dir

    AJIT_PROJECT_HOME=os.environ.get('AJIT_PROJECT_HOME')
    AHIR_RELEASE = os.environ.get('AHIR_RELEASE')
    AHIR_IEEE_LIBRARY = AHIR_RELEASE + "/vhdl/aHiR_ieee_proposed.vhdl"
    AHIR_LIBRARY = AHIR_RELEASE + "/vhdl/ahir.vhdl"
    AHIR_NoASSERTS = AHIR_RELEASE + "/vhdl/No_Asserts"
    work_dir=AJIT_PROJECT_HOME+"/processor/Aa_v2/work"

def array (files_path, period, sgib, mode):

	temp = files_path.split("/")
	
	ret_val = 0
	if temp[-1]	== srch_fold:
		
		implement_path = os.path.join (topdir, files_path)
		current_dir = os.getcwd()
		os.chdir (implement_path)

		if clean:
			
			if (os.path.exists(work_dir)):
				shutil.rmtree(work_dir)
			files = os.listdir (implement_path)
			for contents in files:
				if contents != "buildDC.sh":
					if os.path.isdir (contents):
						shutil.rmtree(contents)
					else:
						os.remove(contents)
						
		else:
			
			ret_val = os.system ("./buildDC.sh " + period + " " + sgib +" "+ mode +" ")
			
			if ret_val != 0:
				print "Error : buildDC.sh failed in %s" %implement_path
				sys.exit(1)
				
				
		os.chdir (current_dir)
	return

def delete_asserts(source, destination):
	ret_val = os.system("deleteAsserts.py -i "+source+" -o "+destination)
	if ret_val != 0:
		print "Error : deleteAsserts.py failed"
		sys.exit(1)
def generate_ddc_src_file(destination):
	ret_val = os.system("readDDCfiles.py"+" -o "+destination)
	if ret_val != 0:
		print "Error : readDDCfiles.py failed"
		sys.exit(1)

def display_usage():
	print "\n Searches for all dc_synthesis directories present in current working directory and runs buildDC.sh present in them, which generates post synth vhd, timing, area, sdc files. \n"
	print "-c : to clean work directory of design compiler and dc_synthesis directory except buildDC.sh\n"
	sys.exit(0)


def main ():
	SetGlobals()
	period= 5
	sgib='n'
	mode ='i'
	global clean
	
	delete_asserts(AHIR_IEEE_LIBRARY, AHIR_NoASSERTS+"/aHiR_ieee_proposed.vhdl")
	delete_asserts(AHIR_LIBRARY, AHIR_NoASSERTS+"/ahir.vhdl")
	generate_ddc_src_file(AJIT_PROJECT_HOME+"/processor/Aa_v2/cpu/dc_synthesis/top.tcl")
	arg_list = sys.argv[1:]
	opts,args = getopt.getopt(arg_list,'p:g:m:,h,c')
	for option, parameter in opts:
		if option == '-p':
			period = parameter
		if option == '-g':
			sgib = 'y'
		if option == '-m':
			mode = parameter
		if option ==  '-h':
			display_usage()
		if option ==  '-c':
			clean = True
		

	for root, dirs, files in os.walk(".", topdown=False, followlinks=True):
		for name in dirs:
			files_path = os.path.join (root, name)
			array (files_path, period, sgib, mode)

	return 0

if __name__ == '__main__':

	ret = main()
	sys.exit(ret)
