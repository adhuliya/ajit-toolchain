# All possible register combinations for misc instructions
# Author : Prajwal Kamble
# 9 Feb 2021 

import itertools
import random
import json

global_reg = ['g0', 'g1', 'g2', 'g3', 'g4', 'g5', 'g6', 'g7']
out_reg = ['o0', 'o1', 'o2', 'o3', 'o4', 'o5', 'o6', 'o7']
local_reg = ['l0', 'l1', 'l2', 'l3', 'l4', 'l5', 'l6', 'l7']
in_reg = ['i0', 'i1', 'i2', 'i3', 'i4', 'i5', 'i6', 'i7']
window_regs = global_reg + out_reg + local_reg + in_reg # all registers in current window
hex_digits = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']

statistics_generated = {}

def init_statistics():
    file = open('expected_stats.json', 'r')
    expected_stats = json.load(file)
    for x in expected_stats.keys():
        statistics_generated[x] = 0
    file.close()

def generate_reg_instrs():
    # to get all possible combinations of window registers, taken 3 at a time
    permutations = list(itertools.permutations(window_regs, r=3))
    instrs = []
    for per in permutations:
        statistics_generated['addd'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('addd  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['adddcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('adddcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['subd'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('subd  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['subdcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('subdcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['srld'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('srld  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['slld'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('slld  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['srad'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('srad  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['umuld'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('umuld  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['umuldcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('umuldcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['smuld'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('smuld  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['smuldcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('smuldcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['udivd'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('udivd  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['udivdcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('udivdcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['sdivd'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('sdivd  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')
    
    for per in permutations:
        statistics_generated['sdivdcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('sdivdcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['andd'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('andd  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['anddcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('anddcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['anddn'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('anddn  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['anddncc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('anddncc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['ord'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('ord  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['ordcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('ordcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['ordn'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('ordn  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['ordncc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('ordncc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['xord'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xord  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['xordcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xordcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['xnord'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xnord  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['xnordcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xnordcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')


    for per in permutations:
        statistics_generated['vaddd8'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xord  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['vaddd16'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xordcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['vaddd32'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xnord  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['vsubd8'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xnordcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['vsubd16'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xord  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['vsubd32'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xordcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['vumuld8'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xnord  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['vumuld16'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xnordcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['vumuld32'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xord  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['vsmuld8'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xordcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['vsmuld16'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xnord  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['vsmuld32'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xnordcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')
    for per in permutations:
        statistics_generated['adddreduce8'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xordcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['adddreduce16'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xnord  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['anddreduce8'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xnordcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')
    for per in permutations:
        statistics_generated['anddreduce16'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xordcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['ordreduce8'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xnord  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['ordreduce16'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xnordcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')
    for per in permutations:
        statistics_generated['xordreduce8'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xordcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['xordreduce16'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xnord  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['zbytedpos'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xnordcc  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')





        #instrs.append('\n\n\n')

    return instrs

def generate_imm_instrs():
    # to get all possible combinations of window registers, taken 3 at a time
    permutations = list(itertools.permutations(window_regs, r=2))
    instrs = []
    for per in permutations:
        statistics_generated["slld"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'slld %' + per[0] + ', 0x' + 
            random.choice(hex_digits) + 
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["srld"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'srld %' + per[0] + ', 0x' + 
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["srad"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'srad %' + per[0] + ', 0x' +
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        ) 

    for per in permutations:
        statistics_generated["zbytedpos"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'srad %' + per[0] + ', 0x' +
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        )


    #instrs.append('\n\n\n')
    return instrs


def check_statistics():
    file = open('expected_stats.json', 'r')
    expected_stats = json.load(file)
    check_file = open('checked_stats', 'w')
    check_file.write("Entity")
    for i in range(35-6):
        check_file.write(" ")
    check_file.write("Expected Occurences")
    for i in range(35-19):
        check_file.write(" ")
    check_file.write("Generated Occurences")
    for i in range(35-20):
        check_file.write(" ")
    check_file.write("\n\n")

    for x in expected_stats.keys():
        check_file.write(x)
        for i in range(35-len(x)):
            check_file.write(" ")
        check_file.write(str(expected_stats[x]))
        for i in range(35-len(str(expected_stats[x]))):
            check_file.write(" ")
        check_file.write(str(statistics_generated[x]))
        for i in range(35-len(str(statistics_generated[x]))):
            check_file.write(" ")

        if(statistics_generated[x] == expected_stats[x]):
            check_file.write("Success")
        else:
            check_file.write("Failed")
            print("Occurences of " + x + " not Matched: Expected - " + str(expected_stats[x]) + " Got - " + str(statistics_generated[x]))
        check_file.write("\n")

    file.close()
    check_file.close()

if __name__=="__main__":
    init_statistics()
    main_asm = open('main.s', 'w')
  #  main_asm.write('! All possible register combinations for misc instructions\n')
  #  main_asm.write('! Author : Prajwal Kamble\n')
    main_asm.write('main:\n')
    main_asm.writelines(generate_reg_instrs())
    main_asm.writelines(generate_imm_instrs())
    main_asm.close()
    check_statistics()
    print("done!")
