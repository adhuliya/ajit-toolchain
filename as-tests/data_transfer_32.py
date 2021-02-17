import sys
import os

from itertools import permutations

op1 = ["%g7", "%g2", "%g3","%g4", "%g5", "%g6","%o7", "%o2", "%o3","%o4", "%o5", "%o6","%o0","%o1","%i7","%i2","%i3","%i4","%i5","%i6","%i0","%i1","%l7", "%l2", "%l3","%l4", "%l5", "%l6","%l0","%l1"]
op2 = ['%g7', '%g2', '%g3','%g4', '%g5', '%g6','%o7', '%o2', '%o3','%o4', '%o5', '%o6','%o0','%o1','%i7','%i2','%i3','%i4','%i5','%i6','%i0','%i1','%l7', '%l2', '%l3','%l4', '%l5', '%l6','%l0','%l1']


# Print the obtained permutations  

sys.stdout = open('data_transfer_32.s','wt')

for x in op1:
  for y in op2:
    print "ld [" + x + " + 4], " + y
    print "ld [" + x + "], " + y
    print "lda [" + x + "]0x20, " + y
    print "ldd [" + x + "], " + y
    print "ldda [" + x + "]0x20, " + y
    print "ldsb [" + x + "], " + y
    print "ldsba [" + x + "]0x20, " + y
    print "ldsh [" + x + "], " + y
    print "ldsha [" + x + "]0x20, " + y
    print "ldub [" + x + "], " + y
    print "lduba [" + x + "]0x20, " + y
    print "lduh [" + x + "], " + y
    print "lduha [" + x + "]0x20, " + y
    print "st " + y + ", [" + x + " + 4] "
    print "st " + y + ", [" + x + "] " 
    print "sta " + y + ", [" + x + "]0x20 " 
    print "std " + y + ", [" + x + "] " 
    print "stda " + y + ", [" + x + "]0x20 " 
    print "stba " + y + ", [" + x + "]0x20 " 
    print "stha " + y + ", [" + x + "]0x20 " 
    print "stsb " + y + ", [" + x + "] " 
    print "stsh " + y + ", [" + x + "] " 
    print "stub " + y + ", [" + x + "] " 
    print "stuh " + y + ", [" + x + "] "
    print "ldstub [" + x + "], " + y
    print "ldstuba [" + x + "]0x20, " + y
    print "swap [" + x + "], " + y
    print "swapa [" + x + "]0x20, " + y



f1 = ['%f0', '%f1', '%f2', '%f3','%f4', '%f5','%f6', '%f7','%f8', '%f9','%f10', '%f11','%f12', '%f13','%f14', '%f15','%f16', '%f17','%f18', '%f19','%f20', '%f21','%f22', '%f23','%f24', '%f25','%f26', '%f27','%f28', '%f29', '%f30', '%f31']

for x in op1:
  for y in f1:
    print "ld [" + x + " + 4], " + y
    print "ld [" + x + "], " + y
    print "ld [" + x + "], %fsr"
    #print "ldd [" + x + "], " + y
    print "st " + y + ", [" + x + " + 4] "
    print "st " + y + ", [" + x + "] "
    print "st " + " %fsr"+ ", [" + x + "] "
   # print "std " + y + ", [" + x + "] "
   # print "std " + " %fq"+ ", [" + x + "] "
f2 = ['%f0', '%f2','%f4','%f6','%f8','%f10','%f12','%f14','%f16','%f18','%f20','%f22','%f24','%f26','%f28', '%f30']
for x in op1:
  for y in f2:
    print "ldd [" + x + "], " + y
    print "std " + y + ", [" + x + "] "
    print "std " + " %fq"+ ", [" + x + "] "



c1 = ['%c0', '%c1', '%c2', '%c3','%c4', '%c5','%c6', '%c7','%c8', '%c9','%c10', '%c11','%c12', '%c13','%c14', '%c15','%c16', '%c17','%c18', '%c19','%c20', '%c21','%c22', '%c23','%c24', '%c25','%c26', '%c27','%c28', '%c29', '%c30', '%c31']

for x in op1:
  for y in c1:
    print "ld [" + x + " + 4], " + y
    print "ld [" + x + "], " + y
    print "ld [" + x + "], %csr"
    print "ldd [" + x + "], " + y
    print "st " + y + ", [" + x + " + 4] "
    print "st " + y + ", [" + x + "] "
    print "st " + " %csr"+ ", [" + x + "] "
    print "std " + y + ", [" + x + "] "
    print "std " + " %cq"+ ", [" + x + "] "






