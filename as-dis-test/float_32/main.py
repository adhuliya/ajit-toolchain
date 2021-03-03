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
    permutations_all=list(itertools.permutations(all_regs, r=3))
    permutations_double=list(itertools.permutations(double_regs, r=3))
    permutations_quad=list(itertools.permutations(quad_reg, r=3))
    permutation_single=list(itertools.permutations(all_regs, r=2))
    permutation_double=list(itertools.permutations(double_regs, r=2))
    permutation_quad=list(itertools.permutations(quad_reg, r=2))
    instrs = []
    for per in permutations_all:
        statistics_generated['fadds'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('fadds %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations_double:
        statistics_generated['faddd'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('faddd %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations_quad:
        statistics_generated['faddq'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('faddq %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations_all:
        statistics_generated['fsubs'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('fsubs %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations_double:
        statistics_generated['fsubd'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('fsubd %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations_quad:
        statistics_generated['fsubq'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('fsubq %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations_all:
        statistics_generated['fmuls'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('fmuls %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations_double:
        statistics_generated['fmuld'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('fmuld %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations_quad:
        statistics_generated['fmulq'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('fmulq %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations_all:
        statistics_generated['fdivs'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('fdivs %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations_double:
        statistics_generated['fdivd'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('fdivd %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations_quad:
        statistics_generated['fdivq'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('fdivq %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutation_single:
        for per1 in double_regs:
            statistics_generated['fsmuld'] += 1
            statistics_generated[per[0]] += 1
            statistics_generated[per[1]] += 1
            statistics_generated[per1] += 1
            instrs.append('fsmuld %' + per[0] + ', %' + per[1] + ', %' + per1 + '\n')

    for per in permutation_double:
        for per1 in quad_reg:
            statistics_generated['fdmulq'] += 1
            statistics_generated[per[0]] += 1
            statistics_generated[per[1]] += 1
            statistics_generated[per1] += 1
            instrs.append('fdmulq %' + per[0] + ', %' + per[1] + ', %' + per1 + '\n')
    
    for per in permutation_single:
        statistics_generated['fmovs'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('fmovs %' + per[0] + ', %' + per[1] + '\n')

    for per in permutation_single:
        statistics_generated['fnegs'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('fnegs %' + per[0] + ', %' + per[1] + '\n')

    for per in permutation_single:
        statistics_generated['fabss'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('fabss %' + per[0] + ', %' + per[1] + '\n')

    for per in permutation_single:
        statistics_generated['fsqrts'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('fsqrts %' + per[0] + ', %' + per[1] + '\n')

    for per in permutation_double:
        statistics_generated['fsqrtd'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('fsqrtd %' + per[0] + ', %' + per[1] + '\n')

    for per in permutation_quad:
        statistics_generated['fsqrtq'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('fsqrtq %' + per[0] + ', %' + per[1] + '\n')

    for per in permutation_single:
        statistics_generated['fcmps'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('fcmps %' + per[0] + ', %' + per[1] + '\n')

    for per in permutation_single:
        statistics_generated['fcmpes'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('fcmpes %' + per[0] + ', %' + per[1] + '\n')

    for per in permutation_double:
        statistics_generated['fcmpd'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('fcmpd %' + per[0] + ', %' + per[1] + '\n')

    for per in permutation_double:
        statistics_generated['fcmped'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('fcmped %' + per[0] + ', %' + per[1] + '\n')

    for per in permutation_quad:
        statistics_generated['fcmpq'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('fcmpq %' + per[0] + ', %' + per[1] + '\n')

    for per in permutation_quad:
        statistics_generated['fcmpeq'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('fcmpeq %' + per[0] + ', %' + per[1] + '\n')

    for per in permutation_single:
        statistics_generated['fstoi'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('fstoi %' + per[0] + ', %' + per[1] + '\n')


    for per in permutation_single:
        statistics_generated['fitos'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('fitos %' + per[0] + ', %' + per[1] + '\n')

    for per in all_regs:
        for per1 in double_regs:
            statistics_generated['fitod'] += 1
            statistics_generated[per] += 1
            statistics_generated[per1] += 1
            instrs.append('fitod %' + per + ', %' + per1 + '\n')

    for per in all_regs:
        for per1 in double_regs:
            statistics_generated['fstod'] += 1
            statistics_generated[per] += 1
            statistics_generated[per1] += 1
            instrs.append('fstod %' + per + ', %' + per1 + '\n')

    for per in all_regs:
        for per1 in double_regs:
            statistics_generated['fdtoi'] += 1
            statistics_generated[per] += 1
            statistics_generated[per1] += 1
            instrs.append('fdtoi %' + per1 + ', %' + per + '\n')

    for per in all_regs:
        for per1 in double_regs:
            statistics_generated['fdtos'] += 1
            statistics_generated[per] += 1
            statistics_generated[per1] += 1
            instrs.append('fdtos %' + per1 + ', %' + per + '\n')

    for per in all_regs:
        for per1 in quad_reg:
            statistics_generated['fitoq'] += 1
            statistics_generated[per] += 1
            statistics_generated[per1] += 1
            instrs.append('fitoq %' + per + ', %' + per1 + '\n')

    for per in all_regs:
        for per1 in quad_reg:
            statistics_generated['fqtoi'] += 1
            statistics_generated[per] += 1
            statistics_generated[per1] += 1
            instrs.append('fqtoi %' + per1 + ', %' + per + '\n')

    for per in all_regs:
        for per1 in quad_reg:
            statistics_generated['fstoq'] += 1
            statistics_generated[per] += 1
            statistics_generated[per1] += 1
            instrs.append('fstoq %' + per + ', %' + per1 + '\n')

    for per in all_regs:
        for per1 in quad_reg:
            statistics_generated['fqtos'] += 1
            statistics_generated[per] += 1
            statistics_generated[per1] += 1
            instrs.append('fqtos %' + per1 + ', %' + per + '\n')

    for per in double_regs:
        for per1 in quad_reg:
            statistics_generated['fdtoq'] += 1
            statistics_generated[per] += 1
            statistics_generated[per1] += 1
            instrs.append('fdtoq %' + per + ', %' + per1 + '\n')

    for per in double_regs:
        for per1 in quad_reg:
            statistics_generated['fqtod'] += 1
            statistics_generated[per] += 1
            statistics_generated[per1] += 1
            instrs.append('fqtod %' + per1 + ', %' + per + '\n')




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
    main_asm.writelines(generate_reg_instrs())
    main_asm.close()
    check_statistics()
    print("done!")
