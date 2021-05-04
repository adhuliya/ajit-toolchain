def Remove(tuples):
    tuples = [t for t in tuples if t]
    return tuples
import re
import string
import sys
from data import dict_ct
with open("main.s", "r") as f:
    code = f.readlines()
    for instr in code:
        inst = instr.rstrip("\n")
        #data = inst.split('%')
        dat = re.split(r'[;\s%]', inst)
        data = Remove(dat)
        if ('a' in data[0]):
            an = '1'
        else:
            an ='0'
        if(data[0][0] != 'T'):
            conv = str(data[0])
            data = conv.split(',')

        if( data[0][0] == 'C'):
            op ='111'
        elif( data[0][0] == 'B'):
            op = '010'
        elif( data[0][0] == 'F'):
            op = '110'
        

        itemsList = dict_ct.items()
        for item in itemsList:
                    if item[0] == data[0]:
                        if (data[0] ==  'CALL' ):
                            res = bin(int(str(0), 16))[2:].zfill(30)
                            print '01' + str(res)
                        elif("T" in data[0]):
                            res = bin(int(data[1]))[2:].zfill(7)
                            print '100'+item[1] + '111010' + '000001000000'+ str(res)
                        else:
                            res = bin(int(str(0), 16))[2:].zfill(22)
                            print '00'+ an  + item[1]+ op  + str(res)

