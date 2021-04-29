#! /usr/bin/env python

'''
 This script is the outer script to compare_traces_inner.pl, which does actual analysis
 Will search for directory named "trace_files", and look for
 *.C_trace (register-write-trace form C model) file inside that directory.
 Find the Aa trace file(*.Aa_trace) for *.C_trace (reference) file wich have the same name.
 Execute compare_traces_inner.pl script with reference and trace file as arguments,
 and create a report file named 'analysis_report', showing the result of execution of
 inner script for each refernce file (ie, each test case)

 author: Ashfaque Ahammed
'''

import os
import sys
import subprocess as sub
import glob
import time
import getopt
start_time = time.time()


# initializing variables
success = 0
fails = 0
warning = 0
count = 0
result = []
current_analysis_result = ""
ajit_project_home = os.environ.get('AJIT_PROJECT_HOME')
path_inner_script = ajit_project_home + "/tools/scripts/compare_traces_inner.pl"
cwd = os.getcwd()

if (ajit_project_home == None):
    reportError("environment variable AJIT_PROJECT_HOME not defined")
    ret_val = 1
    sys.exit()

# Main function. Execution starts form here
def main():
    trace = ""
    reference = "" 
    choice = ""
    result_file = "analysis_result.txt"
    report_file = "analysis_report.txt"

    arg_list = sys.argv[1:] 
    if len(arg_list) < 1:
        display_usage()
        sys.exit()
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
                sys.exit()
            else:
                reportError("Unknown argument")
    if not choice:
        reportError("Please give a choice")
        display_usage() 
        sys.exit()

    else:
        if(choice == "file"): 
            if not trace or not reference:
                reportError("You need to specify trace-file and reference-file")
                display_usage() 
                sys.exit()
            else:
                analyze_single_trace(reference, trace, result_file)

        elif(choice == "walk"):
            print "Executing form: " + cwd
            find_n_execute()
            generate_report(report_file)
            generate_summery()
            print "Script finished executing. Find '" + report_file + "' for more details."
            sys.exit()
#----------------------------------- End of Main function -------------------------------------#


def analyze_single_trace(reference, trace, result_file):
    # compare specified trace file with reference
    specified_ref  = cwd + "/" + reference
    specified_trace  = cwd + "/" + trace
    specified_result  = cwd + "/" + result_file
    # Both of this line below should be deleted | obsolete
    ref_line_count = sum(1 for line in open(specified_ref))
    trace_line_count = sum(1 for line in open(specified_trace))

    #Call inner script to compare trace
    command = "perl " + path_inner_script + " --trace " + specified_trace + " --ref " + specified_ref + " --result " + specified_result
    process = sub.Popen([command],stdout=sub.PIPE,stderr=sub.PIPE , shell=True)
    output, errors = process.communicate()
    return_val =  output.split("|");
    if(return_val[0] == 'FAIL'):
        if(return_val[2] == 'TRACE'):   # Trace file have less number of lines
            print "\nTest failed: Trace file have less number of lines than reference!"
        elif(return_val[2] == 'REF'):   # Trace file have more lines than reference
            print "\nTest failed: Trace file have more number of lines than reference!"
        elif(return_val[2] == 'ERROR'): # traces values does not match 
            print "\nTest failed with " + str(return_val[1]) + ( " errors"if (int(return_val[1]) >1) else " error" )
    elif(return_val[0] == "SUCCESS"):
        print "\nTest is successfull."
    elif(return_val[0] == "WARNING"):
        print "\nTest passed with " + str(return_val[1]) + ( " warnings"if (int(return_val[1]) >1) else " warning" )
    else:
        print "\nSome problem with inner script. retuned unexpected value!."
    # Finish exicution
    print "Script finished executing. Find '" + result_file + "' for more details."
    sys.exit()
#------------------------------------- End of analyze_single_trace----------------------------#

def find_n_execute():
    for root, dirs, files in os.walk(cwd):
    
        # Searching for directory named trace_files
        for dir_name in dirs:
            trace_file = reference_file = ''
            if dir_name == "trace_files":
                current_execution_path = root + "/trace_files/"
                print "\n-------------------- " + root + "--------------------"
                ref_file_list = []
    
                # Looking for reference files (*.C_trace)
                ref_file_path_list = glob.glob(current_execution_path + "*.C_trace")
                for ref_file_path in ref_file_path_list:
                    ref_file_list.append( (os.path.basename(ref_file_path)).split(".")[0] )
    
                for ref_file in ref_file_list:
                    trace_file_list = glob.glob(current_execution_path + ref_file + ".Aa_trace")
                    global count
                    count += 1
    
                    if not trace_file_list:
                        # Cannot find trace file(trace of Aa model) for corresponding reference file
                        print "There is no corresponding trace file for: " + ref_file + " | Directory: " + root
                        current_analysis_result = '{:>6}  {:<12}  {:<12} {:<5} {:<5}'.format ("[" + str(count) + "]", ref_file, "Failed", "Error_code: 4", root)
                        result.append(current_analysis_result)
                        global fails
                        fails += 1
    
                    else:
                        # Have trace and reference files ready to call inner script
                        trace_file_name     = trace_file_list[0]
                        ref_file_name       = glob.glob(current_execution_path + ref_file + ".C_trace")[0]  
                        result_file_name    = current_execution_path + ref_file + ".report"
                        cmd = "perl " + path_inner_script + " --trace " + trace_file_name + " --ref " + ref_file_name + " --result " + result_file_name
                        print "Executing " + ref_file_name
                        ref_num_lines = sum(1 for line in open(ref_file_name))
                        trace_num_lines = sum(1 for line in open(trace_file_name))

                        # Calling inner script
                        process = sub.Popen([cmd],stdout=sub.PIPE,stderr=sub.PIPE , shell=True)
                        output, errors = process.communicate()
                        return_val =  output.split("|");
    
                        if(return_val[0] == 'FAIL'):
                            if(return_val[2] == 'ERROR'):
                                # Analysis found some errors
                                current_analysis_result = '{:>6}  {:<12}  {:<12} {:<5}  {:<5}'.format ("[" + str(count) + "]", ref_file, "Failed", "Error_code: 1", root)
                            elif(return_val[2] == 'TRACE'):
                                # Trace file have less lines (u-arch model stuck ?!)
                                current_analysis_result = '{:>6}  {:<12}  {:<12} {:<5}  {:<5}'.format ("[" + str(count) + "]", ref_file, "Failed", "Error_code: 2", root)
                            elif(return_val[2] == 'REF'):
                                # Trace file have more entries than refeence
                                current_analysis_result = '{:>6}  {:<12}  {:<12} {:<5}  {:<5}'.format ("[" + str(count) + "]", ref_file, "Failed", "Error_code: 3", root)

                            # Mark this case as faild
                            fails += 1
    
                        elif(return_val[0] == "WARNING"):
                            # Test passed with warnings
                            current_analysis_result = '{:>6}  {:<12}  {:<12}  {:<5} {:<5}'.format ("[" + str(count) + "]", ref_file, "Passed with warnings", "", root)
                            global warning
                            warning += 1

                        elif(return_val[0] == "SUCCESS"):
                            # Innerscript notifies current run have no erros
                            current_analysis_result = '{:>6}  {:<12}  {:<12}  {:<5}'.format ("[" + str(count) + "]", ref_file, "Success", " ")
                            global success
                            success += 1
    
                        else:
                            # Only possible to reach here is, inner script have some problem
                            print "There was some problem with the script !!";
                            result.append(current_analysis_result)
                            fails += 1;
                            if not output:
                                print "The Inner script failed to return any value";
                                current_analysis_result = '{:>6}  {:<12}  {:<12} {:<5}  {:<5}'.format ("[" + str(count) + "]", ref_file, "Failed", "Error_code: 5", root)
                                
                            else:
                                print "The Inner script returned an unexpected value: " + output
                                current_analysis_result = '{:>6}  {:<12}  {:<12} {:<5} {:<5}'.format ("[" + str(count) + "]", ref_file, "Failed", "Error_code: 6", root)

                        # Prining analysis summery to report
                        result.append(current_analysis_result)
#-------------------------------------------_End of Find and Execute_--------------------------------------------#


#  pring error messages
def reportError(err_message):  
    print "\nError: " + err_message

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


# Generate report
def generate_report(report_file):
    report = open(report_file, 'w')
    global fails
    global count
    report.write("Register wtrite trace analysis results\n" + (38*"=") + "\n")
    report.write("\t\tFailed Cases: " + (str(fails) + "/" + str(count)) + "\n" + (38*"-") +"\n")
    report.write("Error codes:\n")
    report.write("\tError_code_1\t: Test failed because of Errors, pls check the *.report file for more details.\n")
    report.write("\tError_code_2\t: Trace file have less number of lines (u-arch model stuck ?!)\n")
    report.write("\tError_code_3\t: Trace-file have more entries than reference.\n")
    report.write("\tError_code_4\t: Trace-file is missing.\n")
    report.write("\tError_code_5\t: Something went wrong, Inner script returned No value.\n")
    report.write("\tError_code_6\t: Something went wrong, Inner script returned Unexpected values.\n"+(109*"=") +"\n")
    for p in result:
        report.write(p+"\n")


# Generate summery
def generate_summery():
    global fails
    global count
    global success 
    global warning
    print "====================_Analysis Summery_===================="
    failed_percent = 0 if (fails == 0) else ((float(fails)/count) * 100)
    print "\tFailed cases\t\t: %d [ %.2f%% ]" % (fails, failed_percent)
    print "\tPassed with warnings\t: " + str(warning)
    print "\tSuccess cases\t\t: " + str(success)
    print "\tTotal cases\t\t: " + str(count)
    print "\tExecution time\t\t: %s seconds" % round( ((time.time() - start_time)), 4)
    print "=========================================================="

if __name__ == '__main__':     # if the function is the main function ...
    main() # ...call main function

