#!/usr/bin/env python

# Searches for all xst_synthesis direcories present one level above the current working directory 
# and appends their paths with -sd option and passes this to ngcbuild. 
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
    print "$  buildNGC.py  <ngc file name>\n"
    return
    
def main ():

        arg_list = sys.argv[1:]
        opts,args = getopt.getopt(arg_list,'r')
        h_flag = ""
        for option, parameter in opts:
            if option == '-r':
               h_flag = " -insert_keep_hierarchy "

	if (len(args) < 1 ):
		display_usage()
		return 1
	else:
		ngc_file_name = args[0]
			

	for root, dirs, files in os.walk(topdir, topdown=False, followlinks=True):
	   for name in dirs:
              if (name == "xst_synthesis"):
	         full_dir_name = os.path.join (root, name)
                 ngc_path.append (" -sd " + full_dir_name)

	ngc_pth = ""
        ret_val = 1
	#print len(ngc_path)
	for X in ngc_path:
           ngc_pth += X
	print "Info : executing : ngcbuild", ngc_pth
	ret_val = os.system ("ngcbuild " + h_flag + ngc_file_name + " out.ngc " + ngc_pth)

	print ret_val
	return ret_val

if __name__ == '__main__':

	ret = main()
	if ret != 0:
		ret = 1
	else:
		ret = 0
	sys.exit(ret)
