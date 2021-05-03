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
                        if (data[0] ==  'slld' or data[0] == 'srld' or data[0] == 'srad' ):
                            if ("x" in data[2]):
                                imm=data[2].split('x')
                                res = "{0:06b}".format(int(imm[1], 16))
                                print '10' + str(register(data[3])) + item[1] + str(register(data[1])) +'10000010' + str(res)
                            else:
                                print '10' + str(register(data[3])) + item[1] + str(register(data[1])) +'000000100' + str(register(data[2])) 
                        elif (data[0] == 'vaddd8' or data[0] == 'vsubd8' or data[0]=='vumuld8' or data[0] == 'vsmuld8'):
                            print '10' + str(register(data[3])) + item[1] + str(register(data[1])) +'0000' +'001' + '10' + str(register(data[2]))
			elif (data[0] == "vaddd16" or data[0] == 'vsubd16' or data[0]=='vumuld16' or data[0] == 'vsmuld16'):
                            print '10' + str(register(data[3])) + item[1] + str(register(data[1])) +'0000' +'010' + '10' + str(register(data[2]))
			elif (data[0] == "vaddd32" or data[0] == 'vsubd32' or data[0]=='vumuld32' or data[0] == 'vsmuld32'):
                            print '10' + str(register(data[3])) + item[1] + str(register(data[1])) +'0000' +'100' + '10' + str(register(data[2]))
                        elif(data[0] == 'adddreduce8' or data[0] == 'anddreduce8' or data[0] == 'ordreduce8' or data[0] == 'xordreduce8'):
                            print '10' + str(register(data[3])) + item[1] + str(register(data[1])) +'0000'+ '001' +'00' + str(register(data[2]))
                        elif(data[0] == "adddreduce16" or data[0] == 'anddreduce16' or data[0] == 'ordreduce16' or data[0] == 'xordreduce16'):
                            print '10' + str(register(data[3])) + item[1] + str(register(data[1])) +'0000'+ '010' +'00' + str(register(data[2]))
                        elif(data[0] == 'zbytedpos'):
                            if ("x" in data[2]):
                                imm=data[2].split('x')
                                res = "{0:08b}".format(int(imm[1], 16))
                                print '10' + str(register(data[3])) + item[1] + str(register(data[1])) +'100000' + str(res)
                            else:
                                print '10' + str(register(data[3])) + item[1] + str(register(data[1])) +'000000000' + str(register(data[2]))
                        else:
                            print '10' + str(register(data[3])) + item[1] + str(register(data[1])) +'000000001' + str(register(data[2]))

                        
                            



















