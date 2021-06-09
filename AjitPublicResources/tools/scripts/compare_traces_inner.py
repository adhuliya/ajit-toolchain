#! /usr/bin/env python
import os
import os.path
import shutil
import getopt
import sys
import glob
import commands
import threading 
import popen2
import pdb
import time

# run system command.
def getNonCommentLine(trace_file, lines_read_from_ref_trace):
    oline_count = lines_read_from_ref_trace
    while True:
        line =  trace_file.readline()
        if(len(line) == 0):
           return None, oline_count
        elif (line[0] != '/'):
           oline_count  = oline_count + 1
           return line, oline_count
        


def parseOptions(opts):
    ref_file = None
    cmp_file = None
    out_file = None
    for option, parameter in opts:
        if option == '-r':
           ref_file = parameter
        elif option == '-t':
           cmp_file = parameter
        elif option == '-o':
           out_file = parameter
        else:
           print "Error: unknown option"
    return ref_file, cmp_file, out_file

#
# compare triple-word traces.
# Author: Madhav Desai 
#
# Brief Description:
#   Specify two trace files to compare.  The script compares
#   them and returns the number of failures observed.
#
#
#     -r <ref-trace>
#     -t <comparison-trace>
#     -o <output-file>
#
#  returns the number of failures observed.
#
def printUsage():
    print ''' 
     -r <reference-triple-word-trace-file> 
     -t <triple-word-trace-file-to-compare-with-reference>
     -o <comparison-output-file>
          '''
def main():


    if len(sys.argv) < 3:
       printUsage()
       return 1

    arg_list = sys.argv[1:]
   
    opts,args = getopt.getopt(arg_list,'r:t:o:')
    ref_trace_file_name, compare_trace_file_name, output_file_name = parseOptions(opts)

    ref_trace_file = None
    if os.path.isfile(ref_trace_file_name):
      ref_trace_file = open(ref_trace_file_name,"r")
    else:
      print "Error: could not open trace file " + ref_trace_file_name
      return 1
      
    compare_trace_file = None
    if os.path.isfile(ref_trace_file_name):
      compare_trace_file = open(compare_trace_file_name,"r")
    else:
      print "Error: could not open trace file " + compare_trace_file_name
      return 1
    
    
    output_file = open(output_file_name,"w")
    if output_file == None:
      print "Error: could not output file " +  command
      return 1

    error_count = 0
    lines_read_from_ref_trace = 0
    lines_read_from_compare_trace = 0
    while True:
      ref_line, lines_read_from_ref_trace   = getNonCommentLine(ref_trace_file, lines_read_from_ref_trace)

      if ref_line == None:
          break

      trace_line, lines_read_from_compare_trace = getNonCommentLine(compare_trace_file, lines_read_from_compare_trace)
      if trace_line == None:
         print >> output_file, "Missing line in comparison-trace-file, reference-trace-file has " + ref_line
         error_count = error_count + 1
         break
      else:
         err_flag = 0
         if(trace_line != ref_line):
            print >> output_file, "Mismatch:\n reference-trace-line:\t" + ref_line + " compare-trace-line:\t" + trace_line
            error_count = error_count + 1
      
    if(error_count > 0): 
        print >> output_file, "There was/were " + str(error_count) + " error/errors"
        print "Error: in comparing " + ref_trace_file_name + " and " + compare_trace_file_name + ": " + str(error_count) + " error/errors"
    else:
        print >> output_file, "No errors"
        print "Info: no errors"

    ref_trace_file.close()
    compare_trace_file.close()
    output_file.close()
 
    return error_count 
    
       
if __name__ == '__main__':     # if the function is the main function ...
    main() # ...call main function
