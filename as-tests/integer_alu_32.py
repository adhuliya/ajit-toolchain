import sys
import os

from itertools import permutations

# Get all permutations of length 3
  
perm = permutations(['%g7', '%g2', '%g3','%g4', '%g5', '%g6','%o7', '%o2', '%o3','%o4', '%o5', '%o6','%o0','%o1','%i7','%i2','%i3','%i4','%i5','%i6','%i0','%i1','%l7', '%l2', '%l3','%l4', '%l5', '%l6','%l0','%l1'], 3)

sys.stdout = open('integer_alu_32.s','wt')
for i in list(perm):
    print "add " + ','.join(map(str, i))
    print "addcc " + ','.join(map(str, i))
    print "addx " + ','.join(map(str, i))
    print "addxcc " + ','.join(map(str, i))
    print "taddcc " + ','.join(map(str, i))
    print "taddcctv " + ','.join(map(str, i))
    print "sub " + ','.join(map(str, i))
    print "subcc " + ','.join(map(str, i))
    print "subx " + ','.join(map(str, i))
    print "subxcc " + ','.join(map(str, i))
    print "tsubdcc " + ','.join(map(str, i))
    print "tsubcctv " + ','.join(map(str, i))
    print "umul " + ','.join(map(str, i))
    print "smul " + ','.join(map(str, i))
    print "umulcc " + ','.join(map(str, i))
    print "smulcc " + ','.join(map(str, i))
    print "udiv " + ','.join(map(str, i))
    print "sdiv " + ','.join(map(str, i))
    print "udivcc " + ','.join(map(str, i))
    print "sdivcc " + ','.join(map(str, i))
    print "and " + ','.join(map(str, i))
    print "andcc " + ','.join(map(str, i))
    print "andn " + ','.join(map(str, i))
    print "andncc " + ','.join(map(str, i))
    print "or " + ','.join(map(str, i))
    print "orcc " + ','.join(map(str, i))
    print "orn " + ','.join(map(str, i))
    print "orncc " + ','.join(map(str, i))
    print "xor " + ','.join(map(str, i))
    print "xorcc " + ','.join(map(str, i))
    print "xnor " + ','.join(map(str, i))
    print "xnorcc " + ','.join(map(str, i))
    print "sll " + ','.join(map(str, i))
    print "srl " + ','.join(map(str, i))
    print "sra " + ','.join(map(str, i))


    

op1 = ["%g7", "%g2", "%g3","%g4", "%g5", "%g6","%o7", "%o2", "%o3","%o4", "%o5", "%o6","%o0","%o1","%i7","%i2","%i3","%i4","%i5","%i6","%i0","%i1","%l7", "%l2", "%l3","%l4", "%l5", "%l6","%l0","%l1"]
op2 = ['%g7', '%g2', '%g3','%g4', '%g5', '%g6','%o7', '%o2', '%o3','%o4', '%o5', '%o6','%o0','%o1','%i7','%i2','%i3','%i4','%i5','%i6','%i0','%i1','%l7', '%l2', '%l3','%l4', '%l5', '%l6','%l0','%l1']

for x in op1:
  for y in op2:
    print "add " + x + ", 0x3, " + y
    print "addcc " + x + ", 0x3, " + y
    print "addx " + x + ", 0x3, " + y
    print "addxcc " + x + ", 0x3, " + y
    print "taddcc " + x + ", 0x3, " + y
    print "taddcctv " + x + ", 0x3, " + y
    print "sub " + x + ", 0x3, " + y
    print "subcc " + x + ", 0x3, " + y
    print "subx " + x + ", 0x3, " + y
    print "subxcc " + x + ", 0x3, " + y
    print "tsubcc " + x + ", 0x3, " + y
    print "tsubcctv " + x + ", 0x3, " + y
    print "mulscc " + x + ", 0x3, " + y
    print "umul " + x + ", 0x3, " + y
    print "smul " + x + ", 0x3, " + y
    print "umulcc " + x + ", 0x3, " + y
    print "smulcc " + x + ", 0x3, " + y
    print "udiv " + x + ", 0x3, " + y
    print "sdiv " + x + ", 0x3, " + y
    print "udivcc " + x + ", 0x3, " + y
    print "sdivcc " + x + ", 0x3, " + y
    print "and " + x + ", 0x3, " + y
    print "andcc " + x + ", 0x3, " + y
    print "andn " + x + ", 0x3, " + y
    print "andncc " + x + ", 0x3, " + y
    print "or " + x + ", 0x3, " + y
    print "orcc " + x + ", 0x3, " + y
    print "orn " + x + ", 0x3, " + y
    print "orncc " + x + ", 0x3, " + y
    print "xor " + x + ", 0x3, " + y
    print "xorcc " + x + ", 0x3, " + y
    print "xnor " + x + ", 0x3, " + y
    print "xnorcc " + x + ", 0x3, " + y
    print "sll " + x + ", 0x3, " + y
    print "srl " + x + ", 0x3, " + y
    print "sra " + x + ", 0x3, " + y


