def register(i):
    switcher = {
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
from data import dict_arith
with open("integer_alu_64.s", "r") as f:
    code = f.readlines()
    for instr in code:
        inst = instr.rstrip("\n")
        #data = inst.split('%')
        dat = re.split(r'[;,\s%]', inst)
        data = Remove(dat)
        itemsList = dict_arith.items()
        for item in itemsList:
                    if item[0] == data[0]:
                        if ("x" in data[2]):
                            imm=data[2].split('x')
                            res = bin(int(imm[1], 16))[2:].zfill(13)
                            print '10' + str(register(data[3])) + item[1] + str(register(data[1])) + '1' + str(res)
                        else:
                            print '10' + str(register(data[3])) + item[1] + str(register(data[1])) +'000000000' + str(register(data[2])) 
                        
                        
                            



















