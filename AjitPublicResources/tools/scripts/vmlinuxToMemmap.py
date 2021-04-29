#! /usr/bin/python

# vmlinuxToMemmap.py
#
# DESCRIPTION:
#	script to generate a memory map
#	(for initializing memory in a processor model)
#	from a hex dump of the bootloader and linux kernel image
#
# USAGE:
#	vmlinuxToMemmap.py [arguments] <bootloader executable> <vmlinux executable>
#	arguments:
#		-h, --help 
#		-o  --output directory where output files will be placed 
#			(default =./Output)
# OUTPUT:
#	creates the following files in specified output directory:
#		hex_file.txt : intermediate file for generating mem_map.txt
#		mem_map.txt  : memory map file used for initializing memory in a processor model
#		objdump.txt  : assembly object dump for debugging execution
#		vardump.txt  : a list of kernel symbols and their addresses useful for debugging
# AUTHOR :
#	Neha Karanjkar (24 April 2015)



# BOOTLOADER_OFFSET :
# offset to be subtracted from symbols in bootloader executable
# bootloader executable is generated with symbols starting from 0.
# and the bootloader has to be placed at physical address = 0x0.
# hence, offset=0
BOOTLOADER_OFFSET = 0

# KERNEL OFFSET :
# offset to be subtracted from symbols in kernel executable
# kernel executable is generated with symbols starting from 0xf0004000.
# and the kernel has to be placed at physical address = 0x00004000.
# hence, offset=0xf0000000
KERNEL_OFFSET=0xf0000000




import sys, os, subprocess

#cross compiler tools :
cross_compiler_prefix="sparc-linux"
Readelf_command = cross_compiler_prefix + "-readelf "
Objdump_command = cross_compiler_prefix + "-objdump -d "
Vardump_command = cross_compiler_prefix + "-readelf -a "


sections_to_dump = [".text", 
	".rodata",
	"__param", 
	"__modver", 
	".data", 
	".fixup", 
	"__ex_table", 
	".notes",
	".init.text",
	".init.data",
	".leon_1insn_patch",
	".bss"]

for i in sections_to_dump :
	Readelf_command += " --hex-dump="+i+" "


import string, sys, os

#check if a given string 
#is a valid hex number 
def is_hex(s):
	try:
		int(s, 16)
		return True
	except ValueError:
		return False

def printLine(address,data) :
	byte_addr=address
	for i in range(len(data)) : 
		for j in range(4) : #each word has 4 bytes
			#print byte address
			print"%x"%(byte_addr + i*4 + j),
			#print jth byte in data[i]
			print"\t%02x"%( (data[i] & (0xFF000000>>j*8)) >>(24-j*8))
			
	return


#function to generate a byte-wise
#memory map from a list
# [ (hexdump_file1, offset1), (hexdumpfile2, offset2), ...]

# format of a line in the hexdump file is :
# <address> word <word> <word> <word> <ascii characters to be ignored>


def generate_memorymap(hexdump_file_list,outputfile) :
	
	#try to open output file
	try:
		of= open(outputfile, 'w')
	except IOError:
		print "Error in opening file ", outputfile, "for writing"
		return True
	
	
	remember_stdout=sys.stdout
	#set stdout to outputfile
	sys.stdout=of

	#try to open each input file
	for i in range(len(hexdump_file_list)) :
		inputfile = hexdump_file_list[i][0]
		offset    = hexdump_file_list[i][1]
		try:
			f = open(inputfile, 'r')
		except IOError:
			print "Error in opening file ", inputfile, "for reading"
			return True

		# Read the first line 
		line = f.readline()
		# keep reading line one at a time
		# till the file is empty
		
		while line:
			address=0
			data=[]
			words=line.split()
			if is_hex(words[0]) :
				address = int(words[0],16) - int(offset)
				for word in words[1:5]:
					if is_hex(word) :
						data.append(int(word,16))
				# print the line read:
				#print"\n ---","%08x"%address,data
				printLine(address,data)
			line = f.readline()
	f.close()
	sys.stdout=remember_stdout
	of.close()
	return False


def generateHexdump(executable_name, hexdump_filename, objdump_filename, vardump_filename) :
	
	#hexdump file
	hexdump_command = Readelf_command+ " "+executable_name+" | grep 0x > "+ hexdump_filename
	print "Executing command:",hexdump_command,"\n"
	ret_val = os.system(hexdump_command)
	if (ret_val!=0):
		print "Error in generating hex dump file from ",executable_name
		return 1
	
	#objdump file
	objdump_command = Objdump_command+ " "+executable_name+" > "+objdump_filename 
	print "Executing command:",objdump_command,"\n"
	ret_val = os.system(objdump_command)
	if (ret_val!=0):
		print "Error in generating object dump file from ",executable_name
		return 1
	
	#vardump file
	vardump_command = Vardump_command+ " "+executable_name+" > "+vardump_filename 
	print "Executing command:",vardump_command,"\n"
	ret_val = os.system(vardump_command)
	if (ret_val!=0):
		print "Error in generating var dump file from ",executable_name
		return 1

	return 0


def generateMemMap(args):

	print "\nGenerating memory map into folder ", args.OUTPUT_DIR
	# create output directory if it doesn't already exist
	output_dir =args.OUTPUT_DIR
	if not os.path.exists(output_dir):
		print "Created directory ", output_dir
		os.makedirs(output_dir)
	
	# check if bootloader executable is present
	bootloader_file=args.BOOTLOADER_EXEC_FILE
	if not os.path.isfile(bootloader_file):
		print "Error: file ",bootloader_file," does not exist"
		return 1
	

	# check if vmlinux file is present
	vmlinux_file=args.VMLINUX_FILE
	if not os.path.isfile(vmlinux_file):
		print "Error: file ",vmlinux_file," does not exist"
		return 1
	
	#generate hexdump, objdump and vardump files for the bootloader:
	executable_name = bootloader_file
	bootloader_hexdump_filename = output_dir+ "/bootloader_hex_file.txt"
	objdump_filename = output_dir+ "/bootloader_objdump.txt"
	vardump_filename = output_dir+ "/bootloader_vardump.txt"
	generateHexdump(executable_name, bootloader_hexdump_filename, objdump_filename, vardump_filename)

	
	#generate hexdump, objdump and vardump files for the kernel:
	executable_name = vmlinux_file 
	kernel_hexdump_filename = output_dir+ "/kernel_hex_file.txt"
	objdump_filename = output_dir+ "/kernel_objdump.txt"
	vardump_filename = output_dir+ "/kernel_vardump.txt"
	generateHexdump(executable_name, kernel_hexdump_filename, objdump_filename, vardump_filename)


	#generate memory map from hexdump files
	memorymap_file = output_dir+"/mem_map.txt"
	print "Generating memory map ",memorymap_file
	
	hexdump_list = [(bootloader_hexdump_filename, BOOTLOADER_OFFSET) , (kernel_hexdump_filename, KERNEL_OFFSET)]
	ret_val = generate_memorymap(hexdump_list, memorymap_file)
	if not (ret_val == 0):
		print "Error in generaying memory map from hex dump files ",hexdump_list
		return 1
	return 0


	

def main():
	# parse command line arguments using argparse
	import argparse
	parser = argparse.ArgumentParser(description= "vmlinuxToMemmap.py - A script to convert an uncompressed linux kernel image to a memory map for use with a Sparc processor model")

	parser.add_argument('BOOTLOADER_EXEC_FILE', type=str, action='store', 
	help="name of bootloader executable file")
	parser.add_argument('VMLINUX_FILE', type=str, action='store', 
	help="name of vmlinux file")
	parser.add_argument("-o","--output", dest="OUTPUT_DIR", type=str, action='store', default="./Output",\
	help="directory where output files will be placed (default =./Output)")
	args= parser.parse_args()
	retval=generateMemMap(args)
	return retval


if __name__ == '__main__':
    ret_val = main()
    sys.exit(ret_val)


