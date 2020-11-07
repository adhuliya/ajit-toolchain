#!/usr/bin/env python

# Searches for all xst_synthesis direcories present in current working directory 
# and runs buildXST.sh present in them, which generates ngc, post synth vhd files and ngd files (if selected).
# The script also cleans the xst_synthesis directories except the buildXST.sh file.
# Use xilinx 14.2 with this script.
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
srch_fold = "xst_synthesis"
ngc_path = []

clean = False

def array (files_path, flag):

	temp = files_path.split("/")
	
	ret_val = 0
	if temp[-1]	== srch_fold:
		
		implement_path = os.path.join (topdir, files_path)
		#print implement_path
		current_dir = os.getcwd()
		os.chdir (implement_path)

		if clean:

			files = os.listdir (implement_path)
			for contents in files:
				if contents != "buildXST.sh" and contents != "buildFullNgc.sh" and contents != "KEEP.NGC":
					if os.path.isdir (contents):
						shutil.rmtree(contents)
					else:
						os.remove(contents)
                                                print "Info:xilinx_synth.py: removed " + contents
						
		else:
			ret_val = os.system ("./buildXST.sh " + flag)
			if ret_val != 0:
				print "Error : buildXST.sh failed in %s" %implement_path
				sys.exit(1)
				
		os.chdir (current_dir)
	return

def display_usage():
	print "\n Searches for all xst_synthesis direcories present in current working directory and runs buildXST.sh present in them, which generates ngc, post synth vhd files and ngd files (if selected). Use xilinx 14.2 with this script.\n"
	print "-N : To generate ngd files at non-leaf nodes\n"
	print "-c : to clean xst_synthesis directory except buildXST.sh\n"
	sys.exit(0)


def main ():

	flag = "No"
	global clean
	global ngc_path
	arg_list = sys.argv[1:]
	opts,args = getopt.getopt(arg_list,'h,c,N,')
	for option, parameter in opts:
		if option ==  '-h':
			display_usage()
		if option ==  '-c':
			clean = True
		if option ==  '-N':
			flag = "Y"

	for root, dirs, files in os.walk(".", topdown=False, followlinks=True):
		for name in dirs:
			files_path = os.path.join (root, name)
			#print files_path
			array (files_path, flag)

	return 0

if __name__ == '__main__':

	ret = main()
	sys.exit(ret)
