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

float_single = ['f0','f1', 'f2','f3','f4','f5','f6','f7','f8','f9','f10','f11', 'f12','f13','f14','f15','f16','f17','f18','f19','f20','f21', 'f22','f23','f24','f25','f26','f27','f28','f29','f30','f31']
float_double = ['f0','f2','f4','f6','f8','f10', 'f12','f14','f16','f18','f20', 'f22','f24','f26','f28','f30']
cp_single = ['c0','c1', 'c2','c3','c4','c5','c6','c7','c8','c9','c10','c11', 'c12','c13','c14','c15','c16','c17','c18','c19','c20','c21', 'c22','c23','c24','c25','c26','c27','c28','c29','c30','c31']
cp_double = ['c0','c2','c4','c6','c8','c10', 'c12','c14','c16','c18','c20', 'c22','c24','c26','c28','c30']
statistics_generated = {}

def init_statistics():
    file = open('expected_stats.json', 'r')
    expected_stats = json.load(file)
    for x in expected_stats.keys():
        statistics_generated[x] = 0
    file.close()

def generate_reg_instrs():
    # to get all possible combinations of window registers, taken 2 at a time
    permutations = list(itertools.permutations(window_regs, r=2))
    permutation = list(itertools.permutations(window_regs, r=3))
    instrs = []
    for per in permutations:
        statistics_generated['ldsb'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('ldsb [%' + per[0] + '], %' + per[1] + '\n')

    for per in permutations:
        statistics_generated['ldsh'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('ldsh [%' + per[0] + '], %' + per[1] + '\n')

    for per in permutations:
        statistics_generated['ldub'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('ldub [%' + per[0] + '], %' + per[1] + '\n')

    for per in permutations:
        statistics_generated['lduh'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('lduh [%' + per[0] + '], %' + per[1] + '\n')

    for per in permutations:
        statistics_generated['ld'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('ld [%' + per[0] + '], %' + per[1] + '\n')

    for per in permutations:
        statistics_generated['ldd'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('ldd [%' + per[0] + '], %' + per[1] + '\n')

    for per in permutations:
        statistics_generated['ldsba'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('ldsba [%' + per[0] + ']0x20, %' + per[1] + '\n')

    for per in permutations:
        statistics_generated['ldsha'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('ldsha [%' + per[0] + ']0x20, %' + per[1] + '\n')

    for per in permutations:
        statistics_generated['lduba'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('lduba [%' + per[0] + ']0x20, %' + per[1] + '\n')

    for per in permutations:
        statistics_generated['lduha'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('lduha [%' + per[0] + ']0x20, %' + per[1] + '\n')

    for per in permutations:
        statistics_generated['lda'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('lda [%' + per[0] + ']0x20, %' + per[1] + '\n')

    for per in permutations:
        statistics_generated['ldda'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('ldda [%' + per[0] + ']0x20, %' + per[1] + '\n')

    for per in permutations:
        statistics_generated['ldstub'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('ldstub [%' + per[0] + '], %' + per[1] + '\n')

    for per in permutations:
        statistics_generated['ldstuba'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('ldstuba [%' + per[0] + ']0x20, %' + per[1] + '\n')

    for per in permutations:
        statistics_generated['swap'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('swap [%' + per[0] + '], %' + per[1] + '\n')

    for per in permutations:
        statistics_generated['swapa'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('swapa [%' + per[0] + ']0x20, %' + per[1] + '\n')


    for per in permutations:
        statistics_generated['stb'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('stb %' + per[0] + ', [%' + per[1] + ']' + '\n')

    for per in permutations:
        statistics_generated['sth'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('sth %' + per[0] + ', [%' + per[1] + ']' + '\n')

    for per in permutations:
        statistics_generated['st'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('st %' + per[0] + ', [%' + per[1] + ']' + '\n')

    for per in permutations:
        statistics_generated['std'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('std %' + per[0] + ', [%' + per[1] + ']' + '\n')

    for per in permutations:
        statistics_generated['stba'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('stba %' + per[0] + ', [%' + per[1] + ']0x20' + '\n')

    for per in permutations:
        statistics_generated['stha'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('stha %' + per[0] + ', [%' + per[1] + ']0x20' + '\n')

    for per in permutations:
        statistics_generated['sta'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('sta %' + per[0] + ', [%' + per[1] + ']0x20' + '\n')

    for per in permutations:
        statistics_generated['stda'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('stda %' + per[0] + ', [%' + per[1] + ']0x20' + '\n')


    for per in window_regs:
        for per1 in float_single:
            statistics_generated['ld'] += 1
            statistics_generated[per] += 1
            statistics_generated[per1] += 1
            instrs.append('ld [%' + per + '], %' + per1 + '\n')

    for per in window_regs:
        for per1 in float_double:
            statistics_generated['ldd'] += 1
            statistics_generated[per] += 1
            statistics_generated[per1] += 1
            instrs.append('ldd [%' + per + '], %' + per1 + '\n')

    for per in window_regs:
        statistics_generated['ld'] += 1
        statistics_generated[per] += 1
        statistics_generated[per1] += 1
        instrs.append('ld [%' + per + '], %fsr' + '\n')

    for per in window_regs:
        for per1 in float_single:
            statistics_generated['st'] += 1
            statistics_generated[per] += 1
            statistics_generated[per1] += 1
            instrs.append('st %' + per1 + ', [%' + per + ']' + '\n')

    for per in window_regs:
        for per1 in float_double:
            statistics_generated['std'] += 1
            statistics_generated[per] += 1
            statistics_generated[per1] += 1
            instrs.append('std %' + per1 + ', [%' + per + ']' + '\n')

    for per in window_regs:
        statistics_generated['st'] += 1
        statistics_generated[per] += 1
        instrs.append('st %fsr, [%' + per + ']' + '\n')

    for per in window_regs:
        statistics_generated['std'] += 1
        statistics_generated[per] += 1
        instrs.append('std %fq, [%' + per + ']' + '\n')


    for per in window_regs:
        for per1 in cp_single:
            statistics_generated['ld'] += 1
            statistics_generated[per] += 1
            statistics_generated[per1] += 1
            instrs.append('ld [%' + per + '], %' + per1 + '\n')

    for per in window_regs:
        for per1 in cp_double:
            statistics_generated['ldd'] += 1
            statistics_generated[per] += 1
            statistics_generated[per1] += 1
            instrs.append('ldd [%' + per + '], %' + per1 + '\n')

    for per in window_regs:
        statistics_generated['ld'] += 1
        statistics_generated[per] += 1
        statistics_generated[per1] += 1
        instrs.append('ld [%' + per + '], %csr' + '\n')

    for per in window_regs:
        for per1 in cp_single:
            statistics_generated['st'] += 1
            statistics_generated[per] += 1
            statistics_generated[per1] += 1
            instrs.append('st %' + per1 + ', [%' + per + ']' + '\n')

    for per in window_regs:
        for per1 in cp_double:
            statistics_generated['std'] += 1
            statistics_generated[per] += 1
            statistics_generated[per1] += 1
            instrs.append('std %' + per1 + ', [%' + per + ']' + '\n')

    for per in window_regs:
        statistics_generated['st'] += 1
        statistics_generated[per] += 1
        instrs.append('st %csr, [%' + per + ']' + '\n')

    for per in window_regs:
        statistics_generated['std'] += 1
        statistics_generated[per] += 1
        instrs.append('std %cq, [%' + per + ']' + '\n')


    for per in permutation:
        statistics_generated['cswap'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('cswap [%' + per[0] + '+ %' + per[1] +'] 0x08, %' + per[2] + '\n')

    for per in permutation:
        statistics_generated['cswapa'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('cswapa [%' + per[0] + '+ %' + per [1] + '] 0x0A, %' + per[2] + '\n')

    for per in permutation:
        statistics_generated["cswap"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'cswap [%' + per[0] + ' +  0x' +
            random.choice(hex_digits) + random.choice(hex_digits) +
            '], %' + per[1] + '\n'
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
  #  main_asm.write('! 9 Feb 2021\n\n\n')
    main_asm.writelines(generate_reg_instrs())
    main_asm.close()
    check_statistics()
    print("done!")
