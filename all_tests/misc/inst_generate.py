import sys
import os
#from data import dict_arith
from itertools import permutations  

# Get all permutations of length 3
# and length 3
perm = permutations(['%g7', '%g0', '%g1','%g2', '%g3','%g4', '%g5', '%g6','%o7', '%o2', '%o3','%o4', '%o5', '%o6','%o0','%o1','%i7','%i2','%i3','%i4','%i5','%i6','%i0','%i1','%l7', '%l2', '%l3','%l4', '%l5', '%l6','%l0','%l1'], 3)

perm2 = permutations(['%g7', '%g0', '%g1','%g2', '%g3','%g4', '%g5', '%g6','%o7', '%o2', '%o3','%o4', '%o5', '%o6','%o0','%o1','%i7','%i2','%i3','%i4','%i5','%i6','%i0','%i1','%l7', '%l2', '%l3','%l4', '%l5', '%l6','%l0','%l1'], 2)

perm1 = ['%g7', '%g0', '%g1','%g2', '%g3','%g4', '%g5', '%g6','%o7', '%o2', '%o3','%o4', '%o5', '%o6','%o0','%o1','%i7','%i2','%i3','%i4','%i5','%i6','%i0','%i1','%l7', '%l2', '%l3','%l4', '%l5', '%l6','%l0','%l1']


opc2 = ['%c0','%c2','%c4','%c6','%c8','%c10','%c12','%c14','%c16','%c18','%c20','%c22','%c24','%c26','%c28','%c30']
opc1 = ['%c1','%c3','%c5','%c7','%c9','%c11','%c13','%c15','%c17','%c19','%c21','%c23','%c25','%c27','%c29','%c31','%c0','%c2','%c4','%c6','%c8','%c10','%c12','%c14','%c16','%c18','%c20','%c22','%c24','%c26','%c28','%c30']


sys.stdout = open('main.s','wt')
print 'main:'
print 'stbar'
print 'nop'
for i in list(perm1):
    print 'sethi ' + '0x3fffff, ' + i
    print 'sethi ' + '0x0, ' + i
    print 'unimp ' + '0x3fffff '
    print 'unimp ' + '0x0 '
    print 'sethi %hi(0x3fffff), ' + i
    print 'sethi %hi(0x0), ' + i
    print 'rett ' + i
    print 'rett ' + i + ' + 0x0'
    print 'rett ' + i + ' + 0x3ff'
    print 'flush ' + i
    print 'flush ' + i + ' + 0x0'
    print 'flush ' + i + ' + 0x3ff'
    print 'wr ' + i +', 0x0 , %y'
    print 'wr ' + i +', 0x0 , %tbr'
    print 'wr ' + i +', 0x0 , %wim'
    print 'wr ' + i +', 0x0 , %psr'
    print 'wr ' + i +', 0x3ff , %y'
    print 'wr ' + i +', 0x3ff , %tbr'
    print 'wr ' + i +', 0x3ff , %wim'
    print 'wr ' + i +', 0x3ff , %psr'
    print 'rd %y, ' + i
    print 'rd %psr, ' + i
    print 'rd %wim, ' + i
    print 'rd %tbr, ' + i
    for x in range(1, 32):
        print 'rd %asr'+str(x)+ ', ' + i
        print 'wr ' + i +', 0x0 , %asr' + str(x)
        print 'wr ' + i +', 0x3ff , %asr' + str (x)



for i in list(perm2):
    print 'rett ' + i[0] + ' + ' + i[1]
    print 'rett ' + i[0] + ' + ' + i[1]
    print 'flush ' + i[0] + ' + ' + i[1]
    print 'flush ' + i[0] + ' + ' + i[1]
    print 'jmpl ' + i[0] + ', ' + i[1]
    print 'jmpl ' + i[0] + '+ 0x0, ' + i[1]
    print 'jmpl ' + i[0] + '+ 0x3ff, ' + i[1]
    print 'wr ' + i[0] +', '+ i[1] + ', %y'
    print 'wr ' + i[0] +', '+ i[1] + ', %psr'
    print 'wr ' + i[0] +', '+ i[1] + ', %tbr'
    print 'wr ' + i[0] +', '+ i[1] + ', %wim'
    for x in range(1, 32):
        print 'wr ' + i[0] +', '+ i[1] + ', %asr' + str(x)

for i in list(perm):
    print 'jmpl ' + i[0] +' + ' + i[1] + ', ' + i[2]






for i in perm1:
    print 'ld' + ' [' + i + '+ 0x00000], %csr'
    print 'ld' + ' [' + i + '+ 0x1fff], %csr'
    print 'st %csr, [' + i + '+ 0x00000]'
    print 'st %csr, [' + i + '+ 0x1fff]'
    print 'std %cq, [' + i + '+ 0x00000]'
    print 'std %cq, [' + i + '+ 0x1fff]'
    for j in opc1:
        print 'ld' + ' [' + i + '+ 0x00000], ' + j
        print 'ld' + ' [' + i + '+ 0x1fff], ' + j
        print 'st ' + j +', [' + i + '+ 0x00000]'
        print 'st ' + j + ', [' + i + '+ 0x1fff]'
    for j in opc2:
        print 'ldd' + ' [' + i + '+ 0x00000], ' + j
        print 'ldd' + ' [' + i + '+ 0x1fff], ' + j
        print 'std ' + j +', [' + i + '+ 0x00000]'
        print 'std ' + j + ', [' + i + '+ 0x1fff]'

for i in perm2:
    print 'ld' + ' [' + i[0] + '+' + i[1] +'], %csr'
    print 'st %csr, [' + i[0] + '+' + i[1] + ']'
    print 'std %cq, [' + i[0] + '+' + i[1] +']'
    for j in opc1:
        print 'ld' + ' [' + i[0] + '+' + i[1] + '], ' + j
        print 'st ' + j +', [' + i[0] + '+' +i[1] + ']'
    for j in opc2:
        print 'ldd' + ' [' + i[0] + '+ ' + i[1] +'], ' + j
        print 'std ' + j + ', [' + i[0] + '+'+i[1]+']'


