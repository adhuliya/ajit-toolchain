import sys
import os

from itertools import permutations


opf2 = ['%f0','%f2','%f4','%f6','%f8','%f10','%f12','%f14','%f16','%f18','%f20','%f22','%f24','%f26','%f28','%f30']
opf1 = ['%f1','%f3','%f5','%f7','%f9','%f11','%f13','%f15','%f17','%f19','%f21','%f23','%f25','%f27','%f29','%f31','%f0','%f2','%f4','%f6','%f8','%f10','%f12','%f14','%f16','%f18','%f20','%f22','%f24','%f26','%f28','%f30']
opf3 = ['%f0','%f4','%f8','%f12','%f16','%f20','%f24','%f28']
opg2 = permutations(['%g7', '%g0', '%g1','%g2', '%g3','%g4', '%g5', '%g6','%o7', '%o2', '%o3','%o4', '%o5', '%o6','%o0','%o1','%i7','%i2','%i3','%i4','%i5','%i6','%i0','%i1','%l7', '%l2', '%l3','%l4', '%l5', '%l6','%l0','%l1'], 2)
opg1 = ['%g7', '%g0', '%g1','%g2', '%g3','%g4', '%g5', '%g6','%o7', '%o2', '%o3','%o4', '%o5', '%o6','%o0','%o1','%i7','%i2','%i3','%i4','%i5','%i6','%i0','%i1','%l7', '%l2', '%l3','%l4', '%l5', '%l6','%l0','%l1']
sys.stdout = open('main.s','wt')
print 'main:'

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
            print "fsmuld " + i + ", " + i + ", " + j
            print "fdmulq " + j + ", " + j + ", " + k
            print "faddreduce16 " + j + ", " + i



for i in opg1: 
    print 'ld' + ' [' + i + '+ 0x00000], %fsr' 
    print 'ld' + ' [' + i + '+ 0x1fff], %fsr'
    print 'st %fsr, [' + i + '+ 0x00000]'
    print 'st %fsr, [' + i + '+ 0x1fff]'
    print 'std %fq, [' + i + '+ 0x00000]'
    print 'std %fq, [' + i + '+ 0x1fff]'
    for j in opf1:
        print 'ld' + ' [' + i + '+ 0x00000], ' + j
        print 'ld' + ' [' + i + '+ 0x1fff], ' + j
        print 'st ' + j +', [' + i + '+ 0x00000]'
        print 'st ' + j + ', [' + i + '+ 0x1fff]'
    for j in opf2:
        print 'ldd' + ' [' + i + '+ 0x00000], ' + j
        print 'ldd' + ' [' + i + '+ 0x1fff], ' + j
        print 'std ' + j +', [' + i + '+ 0x00000]'
        print 'std ' + j + ', [' + i + '+ 0x1fff]'

for i in opg2:
    print 'ld' + ' [' + i[0] + '+' + i[1] +'], %fsr'
    print 'st %fsr, [' + i[0] + '+' + i[1] + ']'
    print 'std %fq, [' + i[0] + '+' + i[1] +']'
    for j in opf1:
        print 'ld' + ' [' + i[0] + '+' + i[1] + '], ' + j
        print 'st ' + j +', [' + i[0] + '+' +i[1] + ']'
    for j in opf2:
        print 'ldd' + ' [' + i[0] + '+ ' + i[1] +'], ' + j
        print 'std ' + j + ', [' + i[0] + '+'+i[1]+']'




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
    print "fstoh " + ','.join(map(str, i))
    print "fhtos " + ','.join(map(str, i))


for i in list(permfd2):
    print "fsqrtd " + ','.join(map(str, i))
    print "fcmpd " + ','.join(map(str, i))
    print "fcmped " + ','.join(map(str, i))
    print "vfi16toh " + ','.join(map(str, i))
    print "vfhtoi16 " + ','.join(map(str, i))


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
    print "vfadd32 " + ','.join(map(str, i))
    print "vfadd16 " + ','.join(map(str, i))
    print "vfmul32 " + ','.join(map(str, i))
    print "vfmul16 " + ','.join(map(str, i))
    print "vfsub32 " + ','.join(map(str, i))
    print "vfsub16 " + ','.join(map(str, i))



for i in list(permfq3):
    print "faddq " + ','.join(map(str, i))
    print "fsubq " + ','.join(map(str, i))
    print "fmulq " + ','.join(map(str, i))
    print "fdivq " + ','.join(map(str, i))












