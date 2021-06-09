#!/usr/bin/env python

# Searches for all xst_synthesis direcories present in current working directory 
# and appends their paths with -sd option and passes this to ngdbuild. 
# Input is ngc file name of the non leaf node.
#
#
# Author : Piyush P. Soni
#
#

import os
import sys
import getopt
import os.path

topdir = os.getcwd()
topdir = os.path.join(topdir + "/../")
srch_fold = "xst_synthesis"
global ngc_path
ngc_path = []

def display_usage():
    print "\n NGC file name is not provided. Please use\n"
    print "$  buildNGD.py  <ngc file name>\n"
    return
    
def main ():

	if (len(sys.argv) < 2 ):
		display_usage()
		return 1
	else:
		ngc_file_name = sys.argv[1]
			
	for root, dirs, files in os.walk(topdir, topdown=False, followlinks=True):
	   for name in dirs:
              if (name == "xst_synthesis"):
	         full_dir_name = os.path.join (root, name)
                 ngc_path.append (" -sd " + full_dir_name)

	ngc_pth = ""
	ret_val = 1
	for X in ngc_path:
           ngc_pth += X

	print "Info : executing : ngdbuild", ngc_pth
	ret_val = os.system ("ngdbuild " + ngc_file_name + " " + ngc_pth)
	print ret_val
	return ret_val

if __name__ == '__main__':

	ret = main()
	if ret != 0:
		ret = 1
	else:
		ret = 0
	sys.exit(ret)
