#!/usr/bin/env python3

# Author: Anshuman Dhuliya (AD) (anshumandhuliya@gmail.com)

# DEPENDENCY: pyelftools

"""
Operations on elf xfiles.

Install the elftools package:

    pip3 install pyelftools;

"""
import os
from typing import Tuple

from elftools.elf.elffile import ELFFile
import sys
from io import StringIO
from cortos.common import util, consts


# compute size of an elf file
CMD_ELF_SIZE: str = "sparc-linux-size {name}"


def getPtLoadSectionsNames(elfFile: str):
  """Returns the names of the sections that are loaded into memory."""

  sio = StringIO()

  f = open(elfFile, "rb")
  elfFile = ELFFile(f) # throws exception

  sections = [sec for sec in elfFile.iter_sections()]
  segments = [seg for seg in elfFile.iter_segments()]

  # only "PT_LOAD" segments need to be loaded
  loadSegs = [seg for seg in segments
              if seg.header["p_type"] == "PT_LOAD"]

  # there can be at most two loadable segments
  loadSecsNames = [sec.name for sec in sections
                   if loadSegs[0].section_in_segment(sec)]

  if (len(loadSegs) >= 2):
    loadSecsNames.extend([sec.name for sec in sections
                          if loadSegs[1].section_in_segment(sec)])

  for secName in loadSecsNames:
    if secName.strip():
      sio.write(f"{secName} ") # print("--hex-dump=", sec, sep="", end=" ")

  f.close() # at END only
  return sio.getvalue()


def getPtLoadSectionsSize(elfFile: str):
  """Calculates the size of loadable sections in the elf.

  It returns the tuple: totalSize, textSize, dataSize
  for the total size, text sections size, data sections size
  of the ELF.

  FIXME: text and data section size may be wrong.
  """
  f = open(elfFile, "rb")
  elfFile = ELFFile(f) # throws exception

  sections = [sec for sec in elfFile.iter_sections()]
  segments = [seg for seg in elfFile.iter_segments()]

  # only "PT_LOAD" segments need to be loaded
  loadSegs = [seg for seg in segments
              if seg.header["p_type"] == "PT_LOAD"]

  # there can be at most two loadable segments
  loadSecs = [sec for sec in sections
              if loadSegs[0].section_in_segment(sec)]

  if (len(loadSegs) >= 2):
    loadSecs.extend([sec for sec in sections
                     if loadSegs[1].section_in_segment(sec)])

  totalSize = 0
  for sec in loadSecs:
    totalSize += sec.data_size

  f.close() # at END only
  return totalSize


def getTextAndDataSize(elfFileName: str) -> Tuple[int, int]:
  """Returns number of bytes in text and data section of the elf.
  This function uses the `size` command.
  Example output of the size command.

      size a.out;
        text    data     bss     dec     hex filename
        1623     600       8    2231     8b7 a.out
  """
  output = util.runCommandGetOutput(CMD_ELF_SIZE.format(name=elfFileName))
  secondLine = output.split(os.linesep)[1] # get the second output line

  words = secondLine.split()
  #                        text      ,    data       +     bss
  textSize, dataSize = int(words[0]), int(words[1]) + int(words[2])
  return textSize, dataSize # in bytes


# def getPtLoadSectionsSize(elfFile: str):
#   """Calculates the size of loadable sections in the elf.
#
#   It returns the tuple: totalSize, textSize, dataSize
#   for the total size, text sections size, data sections size
#   of the ELF.
#
#   FIXME: text and data section size may be wrong.
#   """
#   f = open(elfFile, "rb")
#   elfFile = ELFFile(f) # throws exception
#
#   sections = [sec for sec in elfFile.iter_sections()]
#   segments = [seg for seg in elfFile.iter_segments()]
#
#   # only "PT_LOAD" segments need to be loaded
#   loadSegs = [seg for seg in segments
#               if seg.header["p_type"] == "PT_LOAD"]
#
#   # there can be at most two loadable segments
#   loadSecs = [sec for sec in sections
#               if loadSegs[0].section_in_segment(sec)]
#
#   if (len(loadSegs) >= 2):
#     loadSecs.extend([sec for sec in sections
#                      if loadSegs[1].section_in_segment(sec)])
#
#   totalSize, textSize, dataSize = 0, 0, 0
#   for sec in loadSecs:
#     totalSize += sec.data_size
#     if ( # FIXME: how to accurately determine a data section?
#         ".data" in sec.name
#         or ".rodata" in sec.name
#         or ".bss" in sec.name
#     ):
#       dataSize += sec.data_size
#     else:
#       textSize += sec.data_size
#
#   f.close() # at END only
#   return totalSize, textSize, dataSize


if __name__ == "__main__":
  import sys
  print(getPtLoadSectionsNames(sys.argv[1]))
  print(getPtLoadSectionsSize(sys.argv[1]))

