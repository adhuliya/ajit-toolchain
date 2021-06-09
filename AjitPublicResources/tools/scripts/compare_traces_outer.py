#! /usr/bin/env python
import os
import sys
import subprocess as sub
import glob
import time
import getopt

start_time = time.time()


# walk the directory, looking for subdirectories called trace_files.
# in each, find two files to compare and do the comparison.
success = 0
warning = 0
result = []
current_analysis_result = ""
ajit_project_home = os.environ.get('AJIT_PROJECT_HOME')
path_inner_script = ajit_project_home + "/tools/scripts/compare_traces_inner.py"
cwd = os.getcwd()

if (ajit_project_home == None):
    reportError("environment variable AJIT_PROJECT_HOME not defined")
    ret_val = 1
    sys.exit()

# Main function. Execution starts form here
def main():
    error_count = 0

    trace = ""
    reference = "" 
    choice = ""

    result_file = "analysis_result.txt"
    report_file = "analysis_report.txt"

    arg_list = sys.argv[1:] 
    if len(arg_list) < 1:
        display_usage()
        return(1)

    opts,args = getopt.getopt(arg_list,'t:r:l:fwh')
    for option, parameter in opts:
            if option ==  '-t':
                trace = parameter
            elif option ==  '-r':
                reference = parameter
            elif option ==  '-l':
                result_file = parameter
                report_file = parameter 
            elif option ==  '-w':
                choice = "walk"
            elif option ==  '-f':
                choice = "file"
            elif option ==  '-h':
                display_usage()
                return(1)
            else:
                reportError("Unknown argument")
                return(1)
    if not choice:
        reportError("Please give a choice")
        display_usage() 
        return(1)

    else:
        if(choice == "file"): 
            if not trace or not reference:
                reportError("You need to specify trace-file and reference-file")
                display_usage() 
                sys.exit()
            else:
                error_count = analyze_single_trace(reference, trace, result_file)

        elif(choice == "walk"):
            print "Executing from: " + cwd
            error_count = find_n_execute()

    if (error_count > 0):
       print "Error: there were " + str(error_count) + " failing cases."

    return error_count


#----------------------------------- End of Main function -------------------------------------#


def analyze_single_trace(reference, trace, result_file):

    #Call inner script to compare trace
    command = path_inner_script + " -t " + trace + " -r " + reference + " -o " + result_file
    return_val = os.system(command)

    if(return_val > 0):
       print "Error: trace-compare failed: ref=" + reference + ", trace=" + trace

    return return_val

def find_n_execute():
    error_count = 0

    for root, dirs, files in os.walk(cwd):
        # Searching for directory named trace_files
        for dir_name in dirs:
            trace_file = reference_file = ''
            if dir_name == "trace_files":
                current_execution_path = root + "/trace_files/"
                ref_file_list = []
    
                # Looking for reference files (*.C_trace)
                ref_file_path_list = glob.glob(current_execution_path + "*.C_trace")
                for ref_file_path in ref_file_path_list:
                    ref_file_list.append( (os.path.basename(ref_file_path)).split(".")[0] )
    
                for ref_file in ref_file_list:
                    trace_file_list = glob.glob(current_execution_path + ref_file + ".Aa_trace")
    
                    if not trace_file_list:
                        # Cannot find trace file(trace of Aa model) for corresponding reference file
                        print "There is no corresponding trace file for: " + ref_file + " | Directory: " + root
                        error_count += 1
                    else:
                        # Have trace and reference files ready to call inner script
                        trace_file_name     = trace_file_list[0]
                        ref_file_name       = glob.glob(current_execution_path + ref_file + ".C_trace")[0]  
                        result_file_name    = current_execution_path + ref_file + ".report"
                        lec = analyze_single_trace(ref_file_name, trace_file_name, result_file_name)
                        error_count = error_count  + lec
 
    return error_count
    
#-------------------------------------------_End of Find and Execute_--------------------------------------------#

# Help menu
def display_usage():
    script_name = os.path.basename(sys.argv[0])
    
    print ""
    print "======================================================================="
    print "USAGE: "
    print ""
    print "To walk through and execute recursively form current directory:"
    print "    ",script_name + " -w"
    print ""
    print "To compare two specific trace files:"
    print "    ",script_name + " -f -r <refernce-file-name> -t <trace-file-name>"
    print ""
    print "To display help menu (this message):"
    print "    ",script_name + " -h"
    print ""
    print "By default, a results file is created with name <test_name>.report"
    print "To specify the name of a result file, use: "
    print "     -l <result-file-name> "
    print "======================================================================="


if __name__ == '__main__':     # if the function is the main function ...
    main() # ...call main function

