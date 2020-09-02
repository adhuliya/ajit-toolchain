#!/usr/bin/env python
#
# This script accepts text files, read line by line and remove the text 
# between starting and ending of fense (-->>>>> and --<<<<< )
# Author: Ashfaque Ahammed
# Date  : 25-Nov-2015

import getopt
import sys

def usage(): #{
    print "\n=============== Usage ================\n"
    print sys.argv[0] + " -i <input file name> -o <output file name>\n"
#}

def main(): #{
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
        fense = False
        fense_line = False
        d = f.readlines()
        for i in d:
	        fense_line = False
	        if "-->>>>>" in i:          # Starting of fense
		        fense = True
	        if "--<<<<<" in i:          # Ending of fense
		        fense = False
		        fense_line = True
	        if ((fense == False) and (fense_line == False)):
		        g.write(i)    
        f.close()
    #--------------------------------------------#

#}
if ( __name__ == "__main__" ): #{
   main();
#}
