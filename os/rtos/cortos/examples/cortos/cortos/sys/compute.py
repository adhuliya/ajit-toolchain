#!/usr/bin/env python3

# Author: Anshuman Dhuliya (AD) (anshumandhuliya@gmail.com)

"""
Computes addresses needed to build the system.
"""
import re
from typing import List

from cortos.common import consts, util


def computeInitHeaderSizeInBytes() -> int:
  return consts.INIT_HEADER_SIZE


def computeAllocationAreaBaseAddr() -> int:
  """The base address of the allocation area."""
  return computeInitHeaderSizeInBytes()


def getEntryFuncNames() -> List[str]:
  """Returns the entry function names found in the current working directory."""
  output = util.runCommandGetOutput(consts.GREP_COMMAND)
  funcPattern = re.compile(consts.AJIT_ENTRY_FUNC_REGEX)

  funcList = []
  for line in output.split("\n"):
    match = funcPattern.search(line)
    if match:
      funcList.append(match.group("ajit_entry"))
  return funcList


