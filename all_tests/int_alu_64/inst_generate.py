import sys
import os
from data import dict_arith
from itertools import permutations  

# Get all permutations of length 3
# and length 3
perm = permutations(['%g7', '%g0', '%g1','%g2', '%g3','%g4', '%g5', '%g6','%o7', '%o2', '%o3','%o4', '%o5', '%o6','%o0','%o1','%i7','%i2','%i3','%i4','%i5','%i6','%i0','%i1','%l7', '%l2', '%l3','%l4', '%l5', '%l6','%l0','%l1'], 3)

perm2 = permutations(['%g7', '%g0', '%g1','%g2', '%g3','%g4', '%g5', '%g6','%o7', '%o2', '%o3','%o4', '%o5', '%o6','%o0','%o1','%i7','%i2','%i3','%i4','%i5','%i6','%i0','%i1','%l7', '%l2', '%l3','%l4', '%l5', '%l6','%l0','%l1'], 2)

sys.stdout = open('integer_alu_64.s','wt')
print 'main:'
for i in list(perm):
    for key in dict_arith.keys():
        print str(key) + ' '+ ','.join(map(str, i))

for i in list(perm2):
    for key in dict_arith.keys():
        if ( key == "slld" or key == "srld" or key == "srad"):
            print str(key) + ' ' + i[0] + ', 0x000000, ' + i[1] 
            print str(key) + ' ' + i[0] + ', 0x3f, ' + i[1] 
            
        elif (key == "zbytedpos"):
            print str(key) + ' ' + i[0] + ', 0x00000000, ' + i[1]  
            print str(key) + ' ' + i[0] + ', 0xff, ' + i[1] 


