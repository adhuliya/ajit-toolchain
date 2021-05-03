import sys
import os
from data import dict_ld
from data import dict_st
from itertools import permutations  

# Get all permutations of length 3
# and length 3
perm = permutations(['%g7', '%g0', '%g1','%g2', '%g3','%g4', '%g5', '%g6','%o7', '%o2', '%o3','%o4', '%o5', '%o6','%o0','%o1','%i7','%i2','%i3','%i4','%i5','%i6','%i0','%i1','%l7', '%l2', '%l3','%l4', '%l5', '%l6','%l0','%l1'], 3)

perm2 = permutations(['%g7', '%g0', '%g1','%g2', '%g3','%g4', '%g5', '%g6','%o7', '%o2', '%o3','%o4', '%o5', '%o6','%o0','%o1','%i7','%i2','%i3','%i4','%i5','%i6','%i0','%i1','%l7', '%l2', '%l3','%l4', '%l5', '%l6','%l0','%l1'], 2)

sys.stdout = open('ld_st.s','wt')
print 'main:'
for i in list(perm):
    for key in dict_ld.keys():
        if (key[-1:] == 'a' or key == 'cswap'):
            print str(key) + ' ['+ i[0] + '+' + i[1] + ']0x0A, ' + i[2]
        else:
            print str(key) + ' ['+ i[0] + '+' + i[1] + '], ' + i[2]

for i in list(perm2):
    for key in dict_ld.keys():
        if (key[-1:] == 'a' and key != 'cswapa'):
            print str(key) + ' [' + i[0] + ']0x0A, ' + i[1]                
        else: 
            print str(key) + ' [' + i[0] + '+ 0x00000], ' + i[1]
            print str(key) + ' [' + i[0] + '+ 0x1fff], ' + i[1]
            if (key != 'cswap' and  key != 'cswapa'):
                print str(key) + ' [' + i[0] + '], ' + i[1]

for i in list(perm):
    for key in dict_st.keys():
        if (key[-1:] == 'a'):
            print str(key) + ' '+ i[0] + ', [' + i[1] + '+' + i[2] + ']0x0A '
        else:
            print str(key) + ' '+ i[0] + ', [' + i[1] + '+' + i[2] + '] '

for i in list(perm2):
    for key in dict_st.keys():
        if (key[-1:] == 'a'):
            print str(key) + ' ' + i[1] + ', [' + i[0] + ']0x0A'
        else:
            print str(key) + ' ' + i[1] + ', [' + i[0] + ']'
            print str(key) + ' '+ i[0]+ ', [' + i[1] + '+ 0x00000]'
            print str(key) +i[0] + ' , [' + i[1]+ '+ 0x1fff]'

