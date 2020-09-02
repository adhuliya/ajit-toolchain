#!/usr/bin/env python


# The script reads a mem_map file and makes the addresses contiguous
# within each 4KB page. It also computes the total number of pages
# and the startaddress and parity for each page.
#
# Written by Neha Karanjkar.
# 8 Nov 2016
#
# USAGE : 
#	$ ./bootloader_frontend.py <mem_map_filename>

#Generates output in the following output:

#------------------------------------------------
#	NUM_PAGES (32b): Total number of pages
#	PAGE_SIZE (32b): Size of each page
#
#	for(i=1;i<=NUM_PAGES;i++)
#	{
#
#		PAGE_START_ADDR (32b): start addr for page i
#
#		for(b=0;b<4096;b++)
#			BYTE[b] (8b) : byte in page i
#	
#		PAGE_PARITY (8b): xor of all bytes sent in page i
#
#		PAGE_TERMINATION(32b) : a unique termination string 
#	}
#
#------------------------------------------------


#Constants
PAGE_SIZE=0x100
PAGE_TERMINATION=0xdeadc0de   #magic termination string
STARTADDR=0xf0004000	      #kernel start address


#Global vars/lists
NUM_PAGES =0x0
PAGE_START_ADDR =[]
BYTES=[]
PAGE_PARITY=[]


import os
import sys
import getopt
import os.path


def help_sec ():
	print " "
	print " USAGE:"
	print "       ",os.path.basename(__file__)," -m <mem_map_filename>"
	print " OPTIONSL:"
	print "      -h : help"
	print "      -m : mem-map file"
	print "  "
	return


#get start addr of page containing this addr
def pageStart(addr):
	return (addr - (addr % PAGE_SIZE))

#get end addr of page containing this addr
def pageEnd(addr):
	return ((addr- (addr % PAGE_SIZE)) + (PAGE_SIZE-1))

#fill gap between two addresses with zeros
def fillGap(addr_low, addr_high, page):
	for i in range (addr_low, addr_high):
		BYTES[page].append(0)


#read a mem_map file and populate the 
#global lists
def readMemMapFile(mem_map_file):

	global NUM_PAGES
	global PAGE_START_ADDR
	global BYTES
	global PAGE_PARITY


	#open the mem_map file, count lines 
	lines = [line.rstrip('\n') for line in open(mem_map_file)]

	#read the first line
	addr, byte = [int(x,16) for x in lines[0].split()]

	#create the first page
	page=0
	NUM_PAGES+=1
	PAGE_START_ADDR.append(pageStart(addr))
	PAGE_PARITY.append(0)
	BYTES.append([])

	#fill zeros from start of page, upto addr
	fillGap(PAGE_START_ADDR[page], addr, page)

	#add byte at addr	
	BYTES[page].append(byte)
	PAGE_PARITY[page]^=byte
	next_addr=addr+1



	#now read subsequent lines:
	for i in range(1,len(lines)):
		
		#read line
		addr, byte = [int(x,16) for x in lines[i].split()]

		#does addr belong to current page?
		if(pageStart(addr)==PAGE_START_ADDR[page]):

			#fill gap, if any
			#between the next_addr and addr
			fillGap(next_addr,addr,page)

			#add byte at addr	
			BYTES[page].append(byte)
			PAGE_PARITY[page]^=byte
			next_addr=addr+1

		else:
			#addr belongs to a new page
			#fill gap, if any,
			#till the end of the previous page
			if(pageStart(next_addr)==PAGE_START_ADDR[page]) :
				fillGap(next_addr,pageEnd(next_addr)+1,page)
			
			#start a new page
			page+=1
			NUM_PAGES+=1
			PAGE_START_ADDR.append(pageStart(addr))
			PAGE_PARITY.append(0)
			BYTES.append([])

			#fill zeros from start of page, upto addr
			fillGap(PAGE_START_ADDR[page], addr, page)

			#add byte at addr	
			BYTES[page].append(byte)
			PAGE_PARITY[page]^=byte
			next_addr=addr+1

	
	#fill zeros from next_addr till the end of the page
	if(pageStart(next_addr)==PAGE_START_ADDR[page]) :
		fillGap(next_addr,pageEnd(addr)+1,page)
	
def sendDataToBootloader():
	#print "NUM_PAGES"
	print "{:08x}".format(NUM_PAGES)
	
	#print "PAGE_SIZE"
	print "{:08x}".format(PAGE_SIZE)
	
	for page in range(0,NUM_PAGES):
		
		#print "PAGE_START_ADDR"
		print "{:08x}".format(PAGE_START_ADDR[page])
		
		for b in range(0,PAGE_SIZE):
			print "{:02x}".format(BYTES[page][b])
		
		#print "PAGE_PARITY"
		print "{:02x}".format(PAGE_PARITY[page])

		#print "PAGE_TERM"
		print "{:08x}".format(PAGE_TERMINATION)

	#print "STARTADDR"
	print "{:08x}".format(STARTADDR)

def main():

	# get arguments
	arg_list = sys.argv[1:]
	opts,args = getopt.getopt(arg_list,'h:m')

	if(len(opts)!=1 or (opts[0][0]=='-h')):
		#print help, and return
		help_sec();
		return 1
	
	for option, parameter in opts : 
		if option == '-m' :
			for mfile in args:
				if (not(os.path.exists (mfile))):
					print "ERROR : Cannot find file ", mfile
					return 0
				else:
					mem_map_file = mfile
	
	#Read the mem_map_file and populate the data structures
	readMemMapFile(mem_map_file)
	
	##print out the lists for checking :
	#
	#print "NUM_PAGES	=", NUM_PAGES
	#print "BYTES            =", BYTES	
	#print "PAGE_START_ADDR  =", PAGE_START_ADDR
	#print "PAGE_PARITY      =", PAGE_PARITY

	#Send the information to the bootloader running
	#on the processor executable:
	sendDataToBootloader()


		
	
if __name__ == '__main__':

	ret = main()
	sys.exit(ret)
