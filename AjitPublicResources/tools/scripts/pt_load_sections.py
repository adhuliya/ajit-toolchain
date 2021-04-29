#!/usr/bin/env python3

# Author: Anshuman Dhuliya (dhuliya@cse.iitb.ac.in)

# DEPENDENCY: pyelftools

# This script extracts the section names that need
# to be loaded, and formats the output to be used as a command line
# argument to the `sparc-linux-readelf` program.

# A script to print the list of section names
# that are in the PT_LOAD segment.

# Install the elftools package.
#   pip3 install pyelftools
from elftools.elf.elffile import ELFFile
import sys

progName = sys.argv[0]

usage = "usage: {progName} <elf-file-name>"

if len(sys.argv) != 2:
  print(usage.format(progName=progName))
  exit(1)

fileName = sys.argv[1]

f = open(fileName, "rb")

elfFile = ELFFile(f) # throws exception

sections = [sec for sec in elfFile.iter_sections()]
segments = [seg for seg in elfFile.iter_segments()]

# only "PT_LOAD" segments need to be loaded
loadSegs = [seg for seg in segments if seg.header["p_type"] == "PT_LOAD"]

# there can be at most two loadable segments
loadSecs = [sec.name for sec in sections if loadSegs[0].section_in_segment(sec)]
if (len(loadSegs) >= 2):
  loadSecs.extend([sec.name for sec in sections if loadSegs[1].section_in_segment(sec)])

for sec in loadSecs:
  if sec.strip():
    print("--hex-dump=", sec, sep="", end=" ")
print()

f.close() # at END only

