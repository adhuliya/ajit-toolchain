#!/usr/bin/env python
#
# This script is written for removing the assert/ report statements in vhdl files.
# Author: Ch V Kalyani
# Date  : 23-Sep-2016

import getopt
import sys

def usage():
    print "\n=============== Usage ================\n"
    print sys.argv[0] + " -i <input file name> -o <output file name>\n"

def main(): 
    input_filename = ''
    output_filename = ''
    if (len(sys.argv) < 5 ): 
        usage()
        sys.exit(2)
    else:
        arg_list = sys.argv[1:]
        opts,args = getopt.getopt(arg_list,'i:o:', [])
        for option, parameter in opts:
            if option ==  '-i':
                input_filename = parameter
            elif option ==  '-o':
                output_filename = parameter

    #--------------------------------------------#
        try:
            f = open(input_filename,"r")
        except IOError:
            print "Error: Could not read file:", input_filename
            sys.exit()
       	g = open(output_filename,"w")
        fense1 = False
	fense1_line = False
        d = f.readlines()
        for i in d:
		fense1_line = False
		if "assert" in i:		#starting of assert
			splitted = i.split()
			first=splitted[0]
			var=first[0:6]
			if var == "assert":
				fense1 = True
		elif "report" in i:     	#starting of report
			splitted = i.split()
			first=splitted[0]
			var=first[0:6]
			if var == "report":
				fense1 = True
		
		if "severity error;"  in i:	# Ending of assert/report
		        fense1 = False
		        fense1_line = True
		elif "severity warning;"  in i:	# Ending of assert/report
		        fense1 = False
		        fense1_line = True
		elif "severity failure;"  in i:	# Ending of assert/report
		        fense1 = False
		        fense1_line = True
		elif "severity note;"  in i:	# Ending of assert/report
		        fense1 = False
		        fense1_line = True
		elif "severity ERROR;" in i:	# Ending of assert/report
			fense1 = False
		        fense1_line = True
		if ((fense1 == False) and (fense1_line == False)):
		        g.write(i)
        	f.close()
    #--------------------------------------------#


if ( __name__ == "__main__" ): 
   main();

