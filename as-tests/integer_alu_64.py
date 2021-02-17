import sys
import os

from itertools import permutations  

# Get all permutations of length 3
# and length 3
perm = permutations(['%g7', '%g2', '%g3','%g4', '%g5', '%g6','%o7', '%o2', '%o3','%o4', '%o5', '%o6','%o0','%o1','%i7','%i2','%i3','%i4','%i5','%i6','%i0','%i1','%l7', '%l2', '%l3','%l4', '%l5', '%l6','%l0','%l1'], 3)

sys.stdout = open('integer_alu_64.s','wt')
for i in list(perm):  
    print "addd " + ','.join(map(str, i))
    print "adddcc " + ','.join(map(str, i))
    print "subd " + ','.join(map(str, i))
    print "subdcc " + ','.join(map(str, i))
    print "umuld " + ','.join(map(str, i))
    print "umuldcc " + ','.join(map(str, i))
    print "smuld " + ','.join(map(str, i))
    print "smuldcc " + ','.join(map(str, i))
    print "udivd " + ','.join(map(str, i))
    print "udivdcc " + ','.join(map(str, i))
    print "sdivd " + ','.join(map(str, i))
    print "sdivdcc " + ','.join(map(str, i))
    print "andd " + ','.join(map(str, i))
    print "anddcc " + ','.join(map(str, i))
    print "anddn " + ','.join(map(str, i))
    print "anddncc " + ','.join(map(str, i))
    print "ord " + ','.join(map(str, i))
    print "ordcc " + ','.join(map(str, i))
    print "ordn " + ','.join(map(str, i))
    print "ordncc " + ','.join(map(str, i))
    print "xord " + ','.join(map(str, i))
    print "xordcc " + ','.join(map(str, i))
    print "xnord " + ','.join(map(str, i))
    print "xnordcc " + ','.join(map(str, i))
    print "slld " + ','.join(map(str, i))
    print "srad " + ','.join(map(str, i))
    print "srld " + ','.join(map(str, i))
    print "vaddd8 " + ','.join(map(str, i))
    print "vaddd16 " + ','.join(map(str, i))
    print "vaddd32 " + ','.join(map(str, i))
    print "vsmuld8 " + ','.join(map(str, i))
    print "vsmuld16 " + ','.join(map(str, i))
    print "vsmuld32 " + ','.join(map(str, i))
    print "vsubd8 " + ','.join(map(str, i))
    print "vsubd16 " + ','.join(map(str, i))
    print "vsubd32 " + ','.join(map(str, i))
    print "vumuld8 " + ','.join(map(str, i))
    print "vumuld16 " + ','.join(map(str, i))
    print "vumuld32 " + ','.join(map(str, i))
    print "adddreduce8 " + ','.join(map(str, i))
    print "adddreduce16 " + ','.join(map(str, i))
    print "anddreduce8 " + ','.join(map(str, i))
    print "anddreduce16 " + ','.join(map(str, i))
    print "ordreduce8 " + ','.join(map(str, i))
    print "ordreduce16 " + ','.join(map(str, i))
    print "xordreduce8 " + ','.join(map(str, i))
    print "xordreduce16 " + ','.join(map(str, i))
    print "zbytedpos " + ','.join(map(str, i))


    
    op1 = ["%g7", "%g2", "%g3","%g4", "%g5", "%g6","%o7", "%o2", "%o3","%o4", "%o5", "%o6","%o0","%o1","%i7","%i2","%i3","%i4","%i5","%i6","%i0","%i1","%l7", "%l2", "%l3","%l4", "%l5", "%l6","%l0","%l1"]
op2 = ['%g7', '%g2', '%g3','%g4', '%g5', '%g6','%o7', '%o2', '%o3','%o4', '%o5', '%o6','%o0','%o1','%i7','%i2','%i3','%i4','%i5','%i6','%i0','%i1','%l7', '%l2', '%l3','%l4', '%l5', '%l6','%l0','%l1']

for x in op1:
  for y in op2:
    print "slld " + x + ", 0x3, " + y
    print "srad " + x + ", 0x3, " + y
    print "srld " + x + ", 0x3, " + y
    print "zbytedpos " + x + ", 0x3, " + y



