#!/usr/bin/env python3

import random

SIZE = 1024 * 1024
MAX = 255
STEP = 8

print("{")
prefix=""
for i in range(SIZE):
  print(prefix, random.randint(0,MAX), end="")
  prefix = "," if not prefix else prefix
  if (i+1)%STEP == 0:
    print()

print("};")




