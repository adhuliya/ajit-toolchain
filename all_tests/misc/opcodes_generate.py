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
        'i7': '11111',
        'c0': '00000',
        'c1': '00001',
        'c2': '00010',
        'c3': '00011',
        'c4': '00100',
        'c5': '00101',
        'c6': '00110',
        'c7': '00111',
        'c8': '01000',
        'c9': '01001',
        'c10': '01010',
        'c11': '01011',
        'c12': '01100',
        'c13': '01101',
        'c14': '01110',
        'c15': '01111',
        'c16': '10000',
        'c17': '10001',
        'c18': '10010',
        'c19': '10011',
        'c20': '10100',
        'c21': '10101',
        'c22': '10110',
        'c23': '10111',
        'c24': '11000',
        'c25': '11001',
        'c26': '11010',
        'c27': '11011',
        'c28': '11100',
        'c29': '11101',
        'c30': '11110',
        'c31': '11111'

    }
    return switcher.get(i, "Invalid register")
def Remove(tuples):
    tuples = [t for t in tuples if t]
    return tuples

def merge_names(lst):
   for l in lst:
      l[0:2] = [' '.join(l[0:2])]

import re
import string
import sys
from data import dict_misc
with open("main.s", "r") as f:
    code = f.readlines()
    for instr in code:
        inst = instr.rstrip("\n")
        #data = inst.split('%')
        dat = re.split(r'[\[\];+(),\s%]', inst)
        data = Remove(dat)
        length = len(data)
        if (data[0] == 'rd'):
            if("a" in data[1]):
                asr= re.findall(r'[A-Za-z]+|\d+', data[1])
                data[1] = asr[0]
                rs = str( bin(int(asr[1]))[2:].zfill(5))
                
            else:
                rs = '00000'
            data[0] = data[0] + data.pop(1)    

        if (data[0] == 'wr'):
            if("a" in data[3]):
                asr= re.findall(r'[A-Za-z]+|\d+', data[3])
                data[3] = asr[0]
                rd =str( bin(int(asr[1]))[2:].zfill(5))
            else:
                rd ='00000'
            data[0] = data[0] + data.pop(3)

        itemsList = dict_misc.items()
        for item in itemsList:
                    if item[0] == data[0]:
                        if (data[0][0] == 'l'):
                            if ('x' in data[2]):
                                imm=data[2].split('x')
                                res = bin(int(imm[1], 16))[2:].zfill(13)
                                if (data[3] == 'csr'):
                                    print '1100000' + dict_misc.get("ldcsr") + str(register(data[1])) + '1' + str(res)
                                else:
                                    print '11' + str(register(data[3])) + item[1] + str(register(data[1])) +'1'+ str(res)
                            else:
                                if (data[3] == 'csr'):
                                    print '1100000' + dict_misc.get("ldcsr") + str(register(data[1])) + '000000000' + str(register(data[2]))
                                else:
                                    print '11' + str(register(data[3])) + item[1] + str(register(data[1])) +'000000000' + str(register(data[2]))


                        elif (data[0] == 'st' or data[0] == 'std'):
                            if ('x' in data[3]):
                                imm=data[3].split('x')
                                res = bin(int(imm[1], 16))[2:].zfill(13)
                                if (data[1] == 'csr'):
                                    print '1100000' + dict_misc.get("stcsr") + str(register(data[2])) + '1' + str(res)
                                elif(data[1] == 'cq'):
                                    print '1100000' + dict_misc.get("stdcq") + str(register(data[2])) + '1' + str(res)
                                else:
                                    print '11' + str(register(data[1])) + item[1] + str(register(data[2])) +'1'+ str(res)
                            else:
                                if (data[1] == 'csr'):
                                    print '1100000' + dict_misc.get("stcsr") + str(register(data[2])) + '000000000' + str(register(data[3]))
                                elif(data[1] == 'cq'):
                                    print '1100000' + dict_misc.get("stdcq") + str(register(data[2])) + '000000000' + str(register(data[3]))

                                else:
                                    print '11' + str(register(data[1])) + item[1] + str(register(data[2])) +'000000000' + str(register(data[3]))

                        if (data[0] == 'unimp'):
                            imm=data[1].split('x')
                            val = bin(int(imm[1], 16))[2:].zfill(22)
                            print '0000000000' + str(val)
                        elif(data[0] == 'sethi'):
                            if (length == 3):
                                imm=data[1].split('x')
                                val = bin(int(imm[1], 16))[2:].zfill(22)
                                print '00' + str(register(data[2])) + '100' + str(val)
                            else:
                                imm=data[2].split('x')
                                value = bin(int(imm[1], 16))[2:].zfill(12)
                                val = value[0:12] 
                                print '00' + str(register(data[3])) + '1000000000000' + str(val)
                        elif(data[0] == 'nop'):
                            val = bin(int(str(0), 16))[2:].zfill(24)
                            print '00000001' + str(val)
                        elif(data[0] == 'stbar'):
                            val = bin(int(str(0), 16))[2:].zfill(14)
                            print '1000000' + item[1] + '01111' +str(val)
                        elif(data[0] == 'flush' or data[0] == 'rett'):
                            if (length == 2):
                                val = bin(int(str(0), 16))[2:].zfill(14)
                                print '1000000' + item[1] + str(register(data[1])) + str(val)
                            elif("x" in data[2]):
                                imm=data[2].split('x')
                                val  = bin(int(imm[1], 16))[2:].zfill(13)
                                print '1000000' + item[1] + str(register(data[1])) + '1' + str(val)
                            else:
                                print '1000000' + item[1] + str(register(data[1])) + '000000000' + str(register(data[2])) 
                        elif(data[0] == 'jmpl'):
                            if (length == 3):
                                print '10' + str(register(data[2])) + item[1] + str(register(data[1])) +'00000000000000'
                            elif(length == 4):
                                if ("x" in data[2]):
                                    imm=data[2].split('x')
                                    res = bin(int(imm[1], 16))[2:].zfill(13)
                                    print '10' + str(register(data[3])) + item[1] + str(register(data[1])) +'1' + str(res)
                                else:
                                    print '10' + str(register(data[3])) + item[1] + str(register(data[1])) +'000000000' + str(register(data[2]))
                        elif("rd" in data[0]):
                            val = bin(int(str(0), 16))[2:].zfill(14)
                            print '10' + str(register(data[1])) + item[1] + rs + str(val)
                        elif("wr" in data[0]):
                            if ("x" in data[2]):
                                imm=data[2].split('x')
                                res = bin(int(imm[1], 16))[2:].zfill(13)
                                print '10' + rd + item[1] + str(register(data[1])) +'1' + str(res)
                            else:
                                print '10' + rd + item[1] + str(register(data[1])) + '000000000' + str(register(data[2]))


                                    
                           
                           

                            

                    




















                        
















