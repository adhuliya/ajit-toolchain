def register(i):
    switcher = {
        'f0': '00000',
        'f1': '00001',
        'f2': '00010',
        'f3': '00011',
        'f4': '00100',
        'f5': '00101',
        'f6': '00110',
        'f7': '00111',
        'f8': '01000',
        'f9': '01001',
        'f10': '01010',
        'f11': '01011',
        'f12': '01100',
        'f13': '01101',
        'f14': '01110',
        'f15': '01111',
        'f16': '10000',
        'f17': '10001',
        'f18': '10010',
        'f19': '10011',
        'f20': '10100',
        'f21': '10101',
        'f22': '10110',
        'f23': '10111',
        'f24': '11000',
        'f25': '11001',
        'f26': '11010',
        'f27': '11011',
        'f28': '11100',
        'f29': '11101',
        'f30': '11110',
        'f31': '11111',
        'g0': '00000',
        'g1': '00001',
        'g2': '00010',
        'g3': '00011',
        'g4': '00100',
        'g5': '00101',
        'g6': '00110',
        'g7': '00111',
        'o0': '01000',
        'o1': '01001',
        'o2': '01010',
        'o3': '01011',
        'o4': '01100',
        'o5': '01101',
        'o6': '01110',
        'o7': '01111',
        'l0': '10000',
        'l1': '10001',
        'l2': '10010',
        'l3': '10011',
        'l4': '10100',
        'l5': '10101',
        'l6': '10110',
        'l7': '10111',
        'i0': '11000',
        'i1': '11001',
        'i2': '11010',
        'i3': '11011',
        'i4': '11100',
        'i5': '11101',
        'i6': '11110',
        'i7': '11111'

    }
    return switcher.get(i, "Invalid register")

def Remove(tuples):
    tuples = [t for t in tuples if t]
    return tuples

import re
import string
import sys
from data import dict_float
with open("main.s", "r") as f:
    code = f.readlines()
    for instr in code:
        inst = instr.rstrip("\n")
        #data = inst.split('%')
        dat = re.split(r'[\[\];+,\s%]', inst)
        data = Remove(dat)
        itemsList = dict_float.items()
        for item in itemsList:
                    if item[0] == data[0]:
                        if (data[0][0] == 'l'):
                            if ('x' in data[2]):
                                imm=data[2].split('x')
                                res = bin(int(imm[1], 16))[2:].zfill(13)
                                if (data[3] == 'fsr'):
                                    print '1100000' + dict_float.get("ldfsr") + str(register(data[1])) + '1' + str(res)
                                else:
                                    print '11' + str(register(data[3])) + item[1] + str(register(data[1])) +'1'+ str(res)
                            else:
                                if (data[3] == 'fsr'):
                                    print '1100000' + dict_float.get("ldfsr") + str(register(data[1])) + '000000000' + str(register(data[2]))
                                else:
                                    print '11' + str(register(data[3])) + item[1] + str(register(data[1])) +'000000000' + str(register(data[2]))


                        elif (data[0][0] == 's'):
                            if ('x' in data[3]):
                                imm=data[3].split('x')
                                res = bin(int(imm[1], 16))[2:].zfill(13)
                                if (data[1] == 'fsr'):
                                    print '1100000' + dict_float.get("stfsr") + str(register(data[2])) + '1' + str(res)
                                elif(data[1] == 'fq'):
                                    print '1100000' + dict_float.get("stdfq") + str(register(data[2])) + '1' + str(res)
                                else:
                                    print '11' + str(register(data[1])) + item[1] + str(register(data[2])) +'1'+ str(res)
                            else:
                                if (data[1] == 'fsr'):
                                    print '1100000' + dict_float.get("stfsr") + str(register(data[2])) + '000000000' + str(register(data[3]))
                                elif(data[1] == 'fq'):
                                    print '1100000' + dict_float.get("stdfq") + str(register(data[2])) + '000000000' + str(register(data[3]))

                                else:
                                    print '11' + str(register(data[1])) + item[1] + str(register(data[2])) +'000000000' + str(register(data[3]))

                        elif (data[0] ==  'fadds' or data[0] == 'faddq' or data[0] == 'faddd' or data[0] ==  'fsubs' or data[0] == 'fsubq' or data[0] == 'fsubd' or data[0] ==  'fmuls' or data[0] == 'fmulq' or data[0] == 'fmuld' or data[0] ==  'fdivs' or data[0] == 'fdivq' or data[0] == 'fdivd' or data[0] ==  'fsmuld' or data[0] == 'fdmulq' or data[0] == 'vfadd32' or data[0] ==  'vfadd16' or data[0] == 'vfmul16' or data[0] == 'vfmul32' or data[0] ==  'vfsub16' or data[0] == 'vfsub32'):
                            print '10' + str(register(data[3])) + '110100' + str(register(data[1])) +item[1] + str(register(data[2])) 

                        elif (data[0] ==  'fcmps' or data[0] == 'fcmpd' or data[0] == 'fcmpq' or data[0] ==  'fcmpes' or data[0] == 'fcmped' or data[0] == 'fcmpeq'):
                            print '10' +  '00000110101' + str(register(data[1])) + item[1] + str(register(data[2]))
		        else:
                            print '10' + str(register(data[2])) + '11010000000' + item[1] + str(register(data[1]))
        
                        
                            



















