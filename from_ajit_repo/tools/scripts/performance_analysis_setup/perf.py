#!/usr/bin/env python
#
# This script reads a dot file (icache.dot/dcache.dot/teu.dot) which 
# has a tree of data flow through the pipes and calculates latency and 
# throughput for the pipe writes from the modelsim transcript and generates 
# an output dot file with actual values of latency and throughput 
# and plots the results in a pdf file.
#
#
# Authors : Piyush P. Soni & Aswin Jith
#

import os
import re
import sys
import getopt
import os.path
import shutil
import commands
import pdb
#import pygraphviz as pgv

ajit_project_home = os.environ.get('AJIT_PROJECT_HOME')
performance_analysis_setup = ajit_project_home + "/tools/scripts/performance_analysis_setup/"


from math import sqrt
 
def standard_deviation(lst):
	num_items = len(lst)
	mean = sum(lst) / float(num_items)
	differences = [x - mean for x in lst]
	sq_differences = [d ** 2 for d in differences]
	ssd = sum(sq_differences)
	sd = ""
	variance = ssd / float(num_items - 1)
	sd = sqrt(variance)
	#print sd
	#print('The standard deviation is {}.'.format(sd))		#########
	return(sd)


def calculate_cycles (ip_file1, ip_file2, instrn_no_1, instrn_no_2) :

	print "\n Info: calculating latency by comparing events in " + ip_file1 + ", " + ip_file2, instrn_no_1, instrn_no_2
	ip_file1_open = open(ip_file1,"r")
	ip_file1_open_lines=ip_file1_open.readlines()
	time_ip_file1 = ip_file1_open_lines[int(instrn_no_1)].split(' ')[0]
	
	ip_file2_open = open(ip_file2,"r")
	ip_file2_open_lines=ip_file2_open.readlines()
	time_ip_file2 = ip_file2_open_lines[int(instrn_no_2)].split(' ')[0]
	
	time_op_ip = (int(time_ip_file2) - int(time_ip_file1))/10

	return time_op_ip


def calculate_throughput (ip_file, instrn_no1, instrn_no2) :

	#pdb.set_trace()
	#print "\n Info: calculating throughputs in " + ip_file, instrn_no1, instrn_no2

	ip_file_open = open(ip_file,"r")
	ip_file_open_lines=ip_file_open.readlines()
	time_ip_file_instrn_no1 = ip_file_open_lines[int(instrn_no1)].split(' ')[0]
	time_ip_file_instrn_no2 = ip_file_open_lines[int(instrn_no2)].split(' ')[0]
               	
	time_op_ip = (int(time_ip_file_instrn_no2) - int(time_ip_file_instrn_no1))/10

	return time_op_ip



def help_sec ():

	print " "
	print " -----------------------------------------------------------------------------------------------------------"
	print " PLEASE USE AS FOLLOWS: perf.py -I -v transcript -n NO_OF_INSTRUCTIONS -s STARTING_INSTRUCTION_NUMBER -p PIPE_NAME"
	print " SCRIPT IS UNDER PROGRESS"
	print " -----------------------------------------------------------------------------------------------------------"
	print " "
	print " "
	print " "
	#print " -----------------------------------------------------------------------------------------------------------"
	#print " USAGE:"
	#print "        perf.py [CHOICE] [-s STARTING_INSTRUCTION_NUMBER ] [-n NO_OF_INSTRUCTIONS] [-v TRANSCRIPT] [-p PIPE_NAME] "
	#print " -----------------------------------------------------------------------------------------------------------"
	#print " CHOICE:"
	#print "      -t : TEU"
	#print "      -i : ICACHE"
	#print "      -d : DCACHE"
	#print "      -I : IUNIT"
	#print "      -L : LOADSTORE"	
	#print " -----------------------------------------------------------------------------------------------------------"
	print "  TRANSCRIPT: absolute path of modelsim transcript containing pipe logs"
	print " -----------------------------------------------------------------------------------------------------------"
	print " STARTING_INSTRUCTION_NUMBER: graph analyses the instructions starting from this index"
	print " 			     eg: '-s 100' starts from 100th pipe write" 	
	print "				  if unspecified, default value is zero"	
	print " -----------------------------------------------------------------------------------------------------------"
	print "  NO_OF_INSTRUCTIONS: the number of instructions for which to analyse,"
	print "  		      eg: '-n 2' will analyse two instructions from the starting instruction number"
	print " -----------------------------------------------------------------------------------------------------------"
	print " PIPE_NAME : specify the name of the pipe for which throughput has to be printed \n"
	print " -----------------------------------------------------------------------------------------------------------\n"
	print " *** Pre-requisite for the script:"
	print " \t\t\t 1. Gnuplot."
	print " \t\t\t 2. libwxgtk2.8: install using -"
	print " \t\t\t\t\t\t sudo apt-get install libwxgtk2.8-dev libwxgtk2.8-dbg"
	print " \t\t\t 3. dot."
	print " -----------------------------------------------------------------------------------------------------------\n"

	return


def execCmd (cmd):
        print "\n Info: executing command " 
        print cmd
	os.system(cmd)

def main ():

	# paths of source  files
	pipe_list = performance_analysis_setup + "pipe.list"
	teu_dot_file = performance_analysis_setup + "teu.dot"
	iunit_dot_file = performance_analysis_setup + "iunit.dot"
	loadstore_dot_file = performance_analysis_setup + "loadstore.dot"
	icache_dot_file = performance_analysis_setup + "icache.dot"
	dcache_dot_file = performance_analysis_setup + "dcache.dot"

	arg_list = sys.argv[1:]
	opts,args = getopt.getopt(arg_list,'t,i,d,h,I,L,n:v:p:s:')

	choice = ""
	instrn_no = ""
	transcript = ""
	print_pipe = ""
	print_val = ""
	div8 = False
	div8_bar = False
	start_inst = 0

	for option, parameter in opts :
		if option == '-h' :
			help_sec ()
			return 0
		if option == '-t' :
			choice = option
			print "\n Info : TEU selected."
		if option == '-I' :
			choice = option
			print "\n Info : IUNIT selected."
		if option == '-L' :
			choice = option
			print "\n Info : LOADSTORE selected."			
		if option == '-i' :
			choice = option
			print "\n Info : ICACHE selected."
		if option == '-d' :
			choice = option
			print "\n Info : DCACHE selected."
		if option == '-n' :
			instrn_no = parameter
			print "\n Info : Number of instructions to be logged = ", instrn_no
		if option == '-v' :
			transcript = parameter
			print "\n Info : Transcript file is  " +  transcript
		if option == '-p' :
			print_pipe = parameter
			print "\n Info : Focus on pipe " +  print_pipe
		if option == '-s' :
			start_inst = int(parameter)
			print "\n Info : Start instruction index = ", start_inst
	

	if choice != "-t" and choice != "-i" and choice != "-d" and choice != "-I" and choice != "-L":
		print "\n Error : Specify -t or -i or -d or -I or -L!"
		help_sec ()
		return 1

	if transcript == "" or instrn_no == "":
		print "\n Error : specify transcript file (-v)  and number of instructions to be logged (-n)!"
		help_sec ()
		return 1


	os.system("rm -rf optimization")
	os.system("rm -rf gnuplotsThroughput")
	os.system("rm -rf gnuplotsLatency")
	os.mkdir ("optimization")
	os.mkdir ("optimization/PipeList/")
	os.mkdir ("optimization/PipeListSorted")
	os.mkdir ("optimization/gnuplotFilesThrput")
	os.mkdir ("optimization/gnuplotFilesLatency")
	os.mkdir ("optimization/gnuplotScriptsThroughput")
	os.mkdir ("optimization/gnuplotScriptsLatency")
	os.mkdir ("gnuplotsThroughput")
	os.mkdir ("gnuplotsLatency")


	# grep rxB0-bufPipe and remove "\n" from transcript before "** NOTE"
	os.system ("grep -B 1 rxB0-bufPipe " + transcript + " | grep -B 1 requester | grep -B 1 WPIPE > ./optimization/transcript")
	with open("./optimization/transcript") as src:
			with open("./optimization/transcript_temp", "w") as load:
				for line in src:
					newline = line.replace("\n", "")
					newline2 = newline.replace("--", "\n")
					load.write(newline2)
	
	os.system("rm ./optimization/transcript")
	os.system("mv ./optimization/transcript_temp ./optimization/transcript")
    
	# extract logs of all the pipes in seperate files under dir = PipeList.
	# further refine these logs by keeping necessary info under dir = PipeListSorted.
	with open(pipe_list) as src:
			for line in src:
				pipe_name = line.split('\n')[0]
				print "\n Info: searching for pipe " + pipe_name + " in " + transcript
				cmd1 = "grep " + pipe_name + "-rxB0-bufPipe ./optimization/transcript | grep requester | grep WPIPE > optimization/PipeList/" + pipe_name
				cmd2 = "cut -d ' ' -f6,17,18,19,20 ./optimization/PipeList/" + pipe_name + " > ./optimization/PipeListSorted/" + pipe_name
				execCmd (cmd1)
				execCmd (cmd2)


	# paths of output files
	if choice == '-t':
		dot_file_in = teu_dot_file
 		dot_file_latency = "./optimization/teu_latency.dot"
		op_file_latency = "teu_latency.pdf"
 		dot_file_throughput = "./optimization/teu_throughput.dot"
		op_file_throughput = "teu_throughput.pdf"

	if choice == '-i':
		dot_file_in = icache_dot_file
 		dot_file_latency = "./optimization/icache_latency.dot"
		op_file_latency = "icache_latency.pdf"
 		dot_file_throughput = "./optimization/icache_throughput.dot"
		op_file_throughput = "icache_throughput.pdf"

	if choice == '-d':
		dot_file_in = dcache_dot_file
 		dot_file_latency = "./optimization/dache_latency.dot"
		op_file_latency = "dache_latency.pdf"
 		dot_file_throughput = "./optimization/dcache_throughput.dot"
		op_file_throughput = "dcache_throughput.pdf"

	if choice == '-I':
		dot_file_in = iunit_dot_file
 		dot_file_latency = "./optimization/iunit_latency.dot"
		op_file_latency = "iunit_latency.pdf"
 		dot_file_throughput = "./optimization/iunit_throughput.dot"
		op_file_throughput = "iunit_throughput.pdf"

	if choice == '-L':
		dot_file_in = loadstore_dot_file
 		dot_file_latency = "./optimization/loadstore_latency.dot"
		op_file_latency = "loadstore_latency.pdf"
 		dot_file_throughput = "./optimization/loadstore_throughput.dot"
		op_file_throughput = "loadstore_throughput.pdf"



	# parse source dot file to calculate latency and throughput
	# values and generate an output dot file for number of instructions
	# equal to the value entered by the user
	
	with open(dot_file_in) as src:
		with open (dot_file_latency, "w") as load:
			print "\n Info: filling latency dot file " + dot_file_latency
			for line in src:
				if not "->" in line:
					load.write(line) 

				if "->" in line:
					words = line.split(" ")
					length_words = len(words)

					# flag to determine whether to divide by 8 or not
					# useful for mmu access
					if words[length_words-1].split("\n")[0] == "div8":
						div8 = True
					if words[length_words-1].split("\n")[0] == "div8_bar":
						div8_bar = True

					ip_file1 = "./optimization/PipeListSorted/" + words[0] 
					ip_file2 = "./optimization/PipeListSorted/" + words[2] 

					print "\n Info: comparing events in files " + ip_file1 + ", " + ip_file2
					
					#print ip_file1
					#print ip_file2
					
					status, command_output1 = commands.getstatusoutput("wc -l "+ip_file1)
					status, command_output2 = commands.getstatusoutput("wc -l "+ip_file2)
					no_rows1 = int(command_output1.split(" ")[0])
					no_rows2 = int(command_output2.split(" ")[0])

					if (start_inst >= no_rows1 or start_inst >= no_rows2):
						print "\n Error! \n Number of writes to the pipes lesser than the starting instruction specified \n Max number of writes to teu_pipes = " + str(min(no_rows1,no_rows2)) +"\n"
						help_sec ()
						return 1	

					val_limit1 = min (int(instrn_no),no_rows1 - start_inst,no_rows2 - start_inst)	
					
					load.write( words[0] + ' -> ' + words[2] + ' [label= "')
				
					for i in range(start_inst, val_limit1 + start_inst  ) :
						if div8:
							k = i
							j = i/8
						elif div8_bar:
							k = i/8
							j = i
						else:
							j = i
							k = i
						time_op_ip = calculate_cycles (ip_file1, ip_file2, j, k)
						load.write(str(time_op_ip) + ',')
					div8 = False
					div8_bar = False
					load.write('"]'+"\n")
		load.close()
	src.close()

	with open(dot_file_in) as src:
		with open (dot_file_throughput, "w") as load:
			print "\n Info: filling throughput dot file " + dot_file_throughput
			for line in src:
				if not "->" in line:
					load.write(line) 

				if "->" in line:
					words = line.split(" ")
					ip_file = "./optimization/PipeListSorted/" + words[0] 
					load.write( words[0] + ' -> ' + words[2] + ' [label= "')
					
					status, command_output3 = commands.getstatusoutput("wc -l "+ip_file)
					no_rows = int(command_output3.split(" ")[0])  
					val_limit2 = min(no_rows - start_inst,int(instrn_no)) 

					if (start_inst >= no_rows):
						print "\n Error! \n  Number of writes to the pipes lesser than the starting instruction specified \n Max number of writes to teu_pipes = " + str(no_rows) +"\n"
						help_sec ()
						return 1	
						
					time_op_ip_throughput = []
					for i in range(start_inst, val_limit2 + start_inst -1) :
						time_op_ip = calculate_throughput (ip_file, i, i+1)
						
						time_op_ip_throughput.append(time_op_ip)
						
						#load.write(str(time_op_ip) + ',')
						
					#print time_op_ip_throughput
					#print min(time_op_ip_throughput)
					#print max(time_op_ip_throughput)
					#print(sum(time_op_ip_throughput) / float(len(time_op_ip_throughput)))
					#print (standard_deviation(time_op_ip_throughput))

					if time_op_ip_throughput != []:
						min_val = min(time_op_ip_throughput)
						max_val = max(time_op_ip_throughput)
						mean_val = sum(time_op_ip_throughput) / float(len(time_op_ip_throughput))
						mean_val_truncated = "%.2f" % mean_val
						std_dev = standard_deviation(time_op_ip_throughput)
						std_dev_truncated = "%.2f" % std_dev
					else :
						min_val = 0
						max_val = 0
						mean_val = 0
						mean_val_truncated = 0
						std_dev = 0
						std_dev_truncated = 0
											
					load.write('min=' + str(min_val) + ',max=' + str(max_val) + ',mean=' + str(mean_val_truncated) + ',std_dev=' + str(std_dev_truncated))
										
					load.write('"]'+"\n")
		load.close()	
	src.close()

	#plot the flowcharts
	#G1 = pgv.AGraph(dot_file_latency)
	#G1.graph_attr['epsilon']='0.001'		# adjust a graph parameter
	##print(G.string()) 				# print dot file to standard output
	#G1.layout('dot')				# layout with dot
	#G1.draw(op_file_latency)	
	graph_cmd1 = "dot -Tpdf " + dot_file_latency + " > " + op_file_latency
	execCmd (graph_cmd1)
        #G2 = pgv.AGraph(dot_file_throughput)
	#G2.graph_attr['epsilon']='0.001'		# adjust a graph parameter
	#G2.layout('dot')				# layout with dot
	#G2.draw(op_file_throughput)	
 	graph_cmd2 = "dot -Tpdf " + dot_file_throughput + " > " + op_file_throughput
	execCmd (graph_cmd2)  
	
	
	# generating throughput files for gnuplot
	with open(pipe_list) as src:
		for line in src:
			pipe_name = line.split("\n")[0]
			pipe_file_path = "./optimization/PipeListSorted/" + pipe_name
			gnuplot_file_path = "./optimization/gnuplotFilesThrput/" + pipe_name
			
			print "\n Info: filling data for gnu plot in " + gnuplot_file_path
			
			status, command_output = commands.getstatusoutput("wc -l "+pipe_file_path)
			no_rows = int(command_output.split(" ")[0])  
			if (start_inst >= no_rows):
				val_limit = no_rows
				start_val = 0	
			else:
				val_limit = min(no_rows - start_inst,int(instrn_no)) 
				start_val = start_inst
				
									
			gnuplot_file = open(gnuplot_file_path,"w")
			print >> gnuplot_file, "#Index\t\tThroughput"
			for i in range(start_val, val_limit + start_val -1) :
				thrput = calculate_throughput (pipe_file_path, i, i+1)
				print >> gnuplot_file, str(i) + "\t\t" + str(thrput)
			gnuplot_file.close()
	src.close()


	# generating latency files for gnuplot for specified input dot file
	with open(dot_file_in) as src:
		for line in src:

			if "->" in line:
				words = line.split(" ")
				length_words = len(words)

				## flag to determine whether to divide by 8 or not
				## useful for mmu access
				if words[length_words-1].split("\n")[0] == "div8":
					div8 = True
				if words[length_words-1].split("\n")[0] == "div8_bar":
					div8_bar = True

				ip_file1 = "./optimization/PipeListSorted/" + words[0] 
				ip_file2 = "./optimization/PipeListSorted/" + words[2] 

				out_file = "./optimization/gnuplotFilesLatency/" + words[0] + "__TO__" + words[2] 
				
				print "\n Info: filling data for gnu plot in " + out_file

				with open (out_file, "w") as load:
					
					status, command_output1 = commands.getstatusoutput("wc -l "+ip_file1)
					status, command_output2 = commands.getstatusoutput("wc -l "+ip_file2)
					no_rows1 = int(command_output1.split(" ")[0])
					no_rows2 = int(command_output2.split(" ")[0])

					if (start_inst >= no_rows1 or start_inst >= no_rows2):
						val_limit = no_rows
						start_val = 0	
					else:
						val_limit = min(no_rows - start_inst,int(instrn_no)) 
						start_val = start_inst
								
					val_limit = min (int(instrn_no),no_rows1 - start_inst,no_rows2 - start_inst)	
					load.write("#Index\t\tLayency\n")				
					for i in range(start_inst, val_limit + start_inst  ) :
						if div8:
							k = i
							j = i/8
						elif div8_bar:
							k = i/8
							j = i
						else:
							j = i
							k = i
						time_op_ip = calculate_cycles (ip_file1, ip_file2, j, k)
						load.write(str(i) + "\t\t" + str(time_op_ip) + "\n")
					div8 = False
					div8_bar = False
		load.close()
	src.close()
	
	
	# generating throughput scripts for gnuplot
	with open(pipe_list) as src:
		for line in src:
			pipe_name = line.split("\n")[0]
			gnuplot_script_throughput = "./optimization/gnuplotScriptsThroughput/" + pipe_name + ".p"
			gnuplot_file_path_throughput = "./optimization/gnuplotFilesThrput/" + pipe_name
			gnuplots_path_throughput = "gnuplotsThroughput/" + pipe_name			
			print "\n Info: Creating gnu plot script: " + gnuplot_script_throughput
		
			gnuplot_throughput = open(gnuplot_script_throughput,"w")
			
			print >> gnuplot_throughput, "# Gnuplot script file for plotting data in a file"
			print >> gnuplot_throughput, "set autoscale                        # scale axes automatically"
			print >> gnuplot_throughput, "unset log                              # remove any log-scaling"
			print >> gnuplot_throughput, "unset label                            # remove any previous labels"
			print >> gnuplot_throughput, "set xtic auto                          # set xtics automatically"
			print >> gnuplot_throughput, "set ytic auto                          # set ytics automatically"
			print >> gnuplot_throughput, "set title \"Throughput vs Time index\""
			print >> gnuplot_throughput, "set xlabel \"Time index\""
			print >> gnuplot_throughput, "set ylabel \"Throughput\""
			print >> gnuplot_throughput, "set term pdf"
			print >> gnuplot_throughput, "set output \"" + gnuplots_path_throughput + ".pdf\""
			print >> gnuplot_throughput, "plot \"" + gnuplot_file_path_throughput + "\" with linespoints"
						
			gnuplot_file.close()
	src.close()


	# generating latency scripts for gnuplot
	with open(dot_file_in) as src:
		for line in src:
			if "->" in line:
				words = line.split(" ")
				gnuplot_script_latency = "./optimization/gnuplotScriptsLatency/" + words[0] + "__TO__" + words[2] + ".p"
				gnuplot_file_path_latency = "./optimization/gnuplotFilesLatency/" + words[0] + "__TO__" + words[2]
				gnuplots_path_latency = "gnuplotsLatency/" + words[0] + "__TO__" + words[2]
				gnuplot_latency = open(gnuplot_script_latency,"w")
				print "\n Info: Creating gnu plot script: " + gnuplot_script_latency
	
				print >> gnuplot_latency, "# Gnuplot script file for plotting data in a file"
				print >> gnuplot_latency, "set autoscale                        # scale axes automatically"
				print >> gnuplot_latency, "unset log                              # remove any log-scaling"
				print >> gnuplot_latency, "unset label                            # remove any previous labels"
				print >> gnuplot_latency, "set xtic auto                          # set xtics automatically"
				print >> gnuplot_latency, "set ytic auto                          # set ytics automatically"
				print >> gnuplot_latency, "set title \"Latency vs Time index\""
				print >> gnuplot_latency, "set xlabel \"Time index\""
				print >> gnuplot_latency, "set ylabel \"Latency\""
				print >> gnuplot_latency, "set term pdf"
				print >> gnuplot_latency, "set output \"" + gnuplots_path_latency + ".pdf\""
				print >> gnuplot_latency, "plot \"" + gnuplot_file_path_latency + "\" with linespoints"
				
				gnuplot_file.close()		
	src.close()
	
	
	# running gnuplot throughput scripts to generate the plots
	with open(pipe_list) as src:
		for line in src:
			pipe_name = line.split("\n")[0]
			gnuplot_script_throughput = "./optimization/gnuplotScriptsThroughput/" + pipe_name + ".p"			
			cmd = "gnuplot -p " + gnuplot_script_throughput
			execCmd (cmd)
	src.close()

	# running gnuplot latency scripts to generate the plots
	with open(dot_file_in) as src:
		for line in src:
			if "->" in line:
				words = line.split(" ")
				gnuplot_script_latency = "./optimization/gnuplotScriptsLatency/" + words[0] + "__TO__" + words[2] + ".p"
				cmd = "gnuplot -p " + gnuplot_script_latency
				execCmd (cmd)		
	src.close()

	with open(pipe_list) as src:
	        for line in src:
	                words = line.split("\n")
	                ip_file = "./optimization/PipeListSorted/" + words[0] 
	                status, command_output4 = commands.getstatusoutput("wc -l "+ip_file)
	                no_rows = int(command_output4.split(" ")[0])
			if (print_pipe == words[0]) :
				for i in range(0, no_rows-1) :
					time_op_ip = calculate_throughput (ip_file, i, i+1)
					if (print_pipe == words[0]) :
						print_val = print_val + str(time_op_ip) + ',' 
				print "Throughput for pipe " + print_pipe +" : "
				print print_val
				        
	return 0


if __name__ == '__main__':
	ret_val = main()
	sys.exit(ret_val)
