import sys
import os

from itertools import permutations


permf3 = permutations(['%f1','%f3','%f5','%f7','%f9','%f11','%f13','%f15','%f17','%f19','%f21','%f23','%f25','%f27','%f29','%f31','%f0','%f2','%f4','%f6','%f8','%f10','%f12','%f14','%f16','%f18','%f20','%f22','%f24','%f26','%f28','%f30'], 2)

sys.stdout = open('output.s','wt')

for i in list(permf3):
    print "fstoh " + ','.join(map(str, i))
    print "fhtos " + ','.join(map(str, i))

opf1 = ['%f0','%f2','%f4','%f6','%f8','%f10','%f12','%f14','%f16','%f18','%f20','%f22','%f24','%f26','%f28','%f30']
opf2 = ['%f1','%f3','%f5','%f7','%f9','%f11','%f13','%f15','%f17','%f19','%f21','%f23','%f25','%f27','%f29','%f31','%f0','%f2','%f4','%f6','%f8','%f10','%f12','%f14','%f16','%f18','%f20','%f22','%f24','%f26','%f28','%f30']

for i in opf1:
    for j in opf2:
        print "faddreduce16 " + i + ", " + j

permf = permutations(['%f0','%f2','%f4','%f6','%f8','%f10','%f12','%f14','%f16','%f18','%f20','%f22','%f24','%f26','%f28','%f30'], 3)

for i in list(permf):
    print "vfadd32 " + ','.join(map(str, i))
    print "vfadd16 " + ','.join(map(str, i))
    print "vfmul32 " + ','.join(map(str, i))
    print "vfmul16 " + ','.join(map(str, i))
    print "vfsub32 " + ','.join(map(str, i))
    print "vfsub16 " + ','.join(map(str, i))


permf2 = permutations(['%f0','%f2','%f4','%f6','%f8','%f10','%f12','%f14','%f16','%f18','%f20','%f22','%f24','%f26','%f28','%f30'], 2)

for i in list(permf2):
    print "vfi16toh " + ','.join(map(str, i))
    print "vfhtoi16 " + ','.join(map(str, i))

    
        
    
