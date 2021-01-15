
# generateMemoryMap.py

# DESCRIPTION :
#	Python module to generate a memory map
#	(for initializing memory in a processor model) 
#	from a hex dump of the executable.
#	This module is imported in sscript compileToSparc.py
#
# AUTHOR :
#	Neha Karanjkar (24 April 2015)



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
			print (("%x"%(byte_addr + i*4 + j)) +  ("\t%02x"%( (data[i] & (0xFF000000>>j*8)) >>(24-j*8))))
			
	return

#function to generate a byte-wise
#memory map from a hex dump file
# format of a line in the hexdump file is :
# <address> word <word> <word> <word> <ascii characters to be ignored>

def generate_memorymap(inputfile,outputfile) :
	try:
		of= open(outputfile, 'w')
	except IOError:
		print ("Error in opening file ", outputfile, "for writing")
		return True
	try:
		f = open(inputfile, 'r')
	except IOError:
		print ("Error in opening file ", inputfile, "for reading")
		return True
	remember_stdout=sys.stdout
	#set stdout to outputfile
	sys.stdout=of

	# Read the first line 
	line = f.readline()
	# keep reading line one at a time
	# till the file is empty
	
	while line:
		address=0
		data=[]
		words=line.split()
		if is_hex(words[0]) :
			address = int(words[0],16)
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


