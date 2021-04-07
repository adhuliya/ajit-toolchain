# All possible register combinations for misc instructions
# Author : Prajwal Kamble
# 9 Feb 2021 

import itertools
import random
import json

quad_reg = ['f0', 'f4', 'f8', 'f12', 'f16', 'f20', 'f24', 'f28']
single_reg = ['f1', 'f5', 'f9', 'f13', 'f17', 'f21', 'f25', 'f29']
double_reg = ['f2', 'f6', 'f10', 'f14', 'f18', 'f22', 'f26', 'f30']
singl_reg = ['f3', 'f7', 'f11', 'f15', 'f19', 'f23', 'f27', 'f31']
all_regs = quad_reg + double_reg + single_reg + singl_reg # all registers in current window
double_regs = quad_reg + double_reg
hex_digits = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f']

statistics_generated = {}

def init_statistics():
    file = open('expected_stats.json', 'r')
    expected_stats = json.load(file)
    for x in expected_stats.keys():
        statistics_generated[x] = 0
    file.close()

def generate_reg_instrs():
    # to get all possible combinations of window registers, taken 3 at a time
    permutations_all=list(itertools.permutations(all_regs, r=3))
    permutations_double=list(itertools.permutations(double_regs, r=3))
    permutation_single=list(itertools.permutations(all_regs, r=2))
    permutation_double=list(itertools.permutations(double_regs, r=2))
    instrs = []

    for per in permutations_double:
        statistics_generated['vfadd32'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('vfadd32  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations_double:
        statistics_generated['vfadd16'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('vfadd16  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')


    for per in permutations_double:
        statistics_generated['vfsub32'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('vfsub32  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations_double:
        statistics_generated['vfmul32'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('vfmul16  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')
    
    for per in permutations_double:
        statistics_generated['vfsub16'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('vfsub16  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')
    
    for per in permutations_double:
        statistics_generated['vfmul16'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('vfmul16  %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')


    for per in permutation_double:
        statistics_generated['vfhtoi16'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('vfhtoi16  %' + per[0] + ', %' + per[1] + '\n')

    for per in permutation_double:
        statistics_generated['vfi16toh'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('vfi16toh  %' + per[0] + ', %' + per[1] + '\n')

    for per in all_regs:
        for per1 in double_regs:
            statistics_generated['faddreduce16'] += 1
            statistics_generated[per] += 1
            statistics_generated[per1] += 1
            instrs.append('faddreduce16  %' + per1 + ', %' + per + '\n')

    for per in permutation_single:
        statistics_generated['fstoh'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('fstoh  %' + per[0] + ', %' + per[1] + '\n')

    for per in permutation_single:
        statistics_generated['fhtos'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('fhtos  %' + per[0] + ', %' + per[1] + '\n')





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
    main_asm.close()
    check_statistics()
    print("done!")
