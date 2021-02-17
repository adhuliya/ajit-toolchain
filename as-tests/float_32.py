import sys
import os

from itertools import permutations


opf2 = ['%f0','%f2','%f4','%f6','%f8','%f10','%f12','%f14','%f16','%f18','%f20','%f22','%f24','%f26','%f28','%f30']
opf1 = ['%f1','%f3','%f5','%f7','%f9','%f11','%f13','%f15','%f17','%f19','%f21','%f23','%f25','%f27','%f29','%f31','%f0','%f2','%f4','%f6','%f8','%f10','%f12','%f14','%f16','%f18','%f20','%f22','%f24','%f26','%f28','%f30']
opf3 = ['%f0','%f4','%f8','%f12','%f16','%f20','%f24','%f28']

sys.stdout = open('float_32.s','wt')

for i in opf1:
    for j in opf2:
        for k in opf3:
            print "fitod " + i + ", " + j  
            print "fitoq " + i + ", " + k
            print "fdtoi " + j + ", " + i 
            print "fqtoi " + k + ", " + i
            print "fstod " + i + ", " + j
            print "fstoq " + i + ", " + k
            print "fdtos " + j + ", " + i
            print "fdtoq " + j + ", " + k
            print "fqtos " + k + ", " + i
            print "fqtod " + k + ", " + j
            print "fsmuld " + i + ", " + j
            print "fdmulq " + j + ", " + k


            
permfd3 = permutations(['%f0','%f2','%f4','%f6','%f8','%f10','%f12','%f14','%f16','%f18','%f20','%f22','%f24','%f26','%f28','%f30'], 3)

permfd2 = permutations(['%f0','%f2','%f4','%f6','%f8','%f10','%f12','%f14','%f16','%f18','%f20','%f22','%f24','%f26','%f28','%f30'], 2)

permfs2 = permutations(['%f1','%f3','%f5','%f7','%f9','%f11','%f13','%f15','%f17','%f19','%f21','%f23','%f25','%f27','%f29','%f31','%f0','%f2','%f4','%f6','%f8','%f10','%f12','%f14','%f16','%f18','%f20','%f22','%f24','%f26','%f28','%f30'], 2)

permfs3 = permutations(['%f1','%f3','%f5','%f7','%f9','%f11','%f13','%f15','%f17','%f19','%f21','%f23','%f25','%f27','%f29','%f31','%f0','%f2','%f4','%f6','%f8','%f10','%f12','%f14','%f16','%f18','%f20','%f22','%f24','%f26','%f28','%f30'], 3)

permfq3 = permutations(['%f0','%f4','%f8','%f12','%f16','%f20','%f24','%f28'], 3)

permfq2 = permutations(['%f0','%f4','%f8','%f12','%f16','%f20','%f24','%f28'], 2)


for i in list(permfs2):
    print "fitos " + ','.join(map(str, i))
    print "fstoi " + ','.join(map(str, i))
    print "fmovs " + ','.join(map(str, i))
    print "fnegs " + ','.join(map(str, i))
    print "fabss " + ','.join(map(str, i))
    print "fsqrts " + ','.join(map(str, i))
    print "fcmps " + ','.join(map(str, i))
    print "fcmpes " + ','.join(map(str, i))

for i in list(permfd2):
    print "fsqrtd " + ','.join(map(str, i))
    print "fcmpd " + ','.join(map(str, i))
    print "fcmped " + ','.join(map(str, i))

for i in list(permfq2):
    print "fsqrtq " + ','.join(map(str, i))
    print "fcmpq " + ','.join(map(str, i))
    print "fcmpeq " + ','.join(map(str, i))

for i in list(permfs3):
    print "fadds " + ','.join(map(str, i))
    print "fsubs " + ','.join(map(str, i))
    print "fmuls " + ','.join(map(str, i))
    print "fdivs " + ','.join(map(str, i))

for i in list(permfd3):
    print "faddd " + ','.join(map(str, i))
    print "fsubd " + ','.join(map(str, i))
    print "fmuld " + ','.join(map(str, i))
    print "fdivd " + ','.join(map(str, i))

for i in list(permfq3):
    print "faddq " + ','.join(map(str, i))
    print "fsubq " + ','.join(map(str, i))
    print "fmulq " + ','.join(map(str, i))
    print "fdivq " + ','.join(map(str, i))
