#!/usr/bin/env python3

# Author: Anshuman Dhuliya (AD) (anshumandhuliya@gmail.com)

"""
Main invocation of the ajit cortos system.
"""

from cortos.sys import driver


# mainentry - when this module is run
if __name__ == "__main__":
  print("CoRTOS: Started.")
  driver.main()


