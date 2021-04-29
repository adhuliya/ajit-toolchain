#!/usr/bin/env python

# Searches for all implement directories generates '.prj' files and synthesizes the vhdl


import os
import sys
import getopt
import os.path


topdir = os.getcwd()
srch_fold = "implement"

def array (srch_fold, dirname, names):
	
	for name in names:
		if name == srch_fold:
			
			implement_path = os.path.join (dirname, srch_fold)
			if os.path.isdir (implement_path):
				#print "%s" %implement_path
				os.chdir (dirname)
				os.system ("buildFPGAmodel.py")
				os.system ("mv ./xilinx_synth.prj " + implement_path)
				os.chdir (implement_path)
				#os.system ("./implement_xst.sh")	

	return


def main ():

	os.path.walk (topdir, array, srch_fold)

	return 0

if __name__ == '__main__':

	ret = main()
	sys.exit(ret)
