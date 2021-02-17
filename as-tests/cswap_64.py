import sys
import os

from itertools import permutations

op1 = ["%g7", "%g2", "%g3","%g4", "%g5", "%g6","%o7", "%o2", "%o3","%o4", "%o5", "%o6","%o0","%o1","%i7","%i2","%i3","%i4","%i5","%i6","%i0","%i1","%l7", "%l2", "%l3","%l4", "%l5", "%l6","%l0","%l1"]
op2 = ['%g7', '%g2', '%g3','%g4', '%g5', '%g6','%o7', '%o2', '%o3','%o4', '%o5', '%o6','%o0','%o1','%i7','%i2','%i3','%i4','%i5','%i6','%i0','%i1','%l7', '%l2', '%l3','%l4', '%l5', '%l6','%l0','%l1']
op3 = ['%g7', '%g2', '%g3','%g4', '%g5', '%g6','%o7', '%o2', '%o3','%o4', '%o5', '%o6','%o0','%o1','%i7','%i2','%i3','%i4','%i5','%i6','%i0','%i1','%l7', '%l2', '%l3','%l4', '%l5', '%l6','%l0','%l1']



# Print the obtained permutations  

sys.stdout = open('cswap_64.s','wt')

for x in op1:
  for y in op2:
    print "cswap [" + x + " + 0x3], " + y



for x in op1:
  for y in op2:
    for z in op3:
      print "cswap [" + x + " + " + y + "] 0x08, " + z
      print "cswapa [" + x + " + " + y + "] 0x0A, " + z




