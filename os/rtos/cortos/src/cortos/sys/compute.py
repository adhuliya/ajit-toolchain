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

