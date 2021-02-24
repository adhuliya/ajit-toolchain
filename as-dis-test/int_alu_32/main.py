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
        statistics_generated['add'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('add %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['addcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('addcc %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['sub'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('sub %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['subcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('subcc %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['srl'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('srl %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['sll'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('sll %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['sra'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('sra %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['umul'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('umul %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['umulcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('umulcc %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['smul'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('smul %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['smulcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('smulcc %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['udiv'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('udiv %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['udivcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('udivcc %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['sdiv'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('sdiv %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')
    
    for per in permutations:
        statistics_generated['sdivcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('sdivcc %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['and'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('and %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['andcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('andcc %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['andn'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('andn %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['andncc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('andncc %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['or'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('or %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['orcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('orcc %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['orn'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('orn %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['orncc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('orncc %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['xor'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xor %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['xorcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xorcc %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['xnor'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xnor %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['xnorcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('xnorcc %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')


    for per in permutations:
        statistics_generated['addx'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('addx %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['addxcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('addxcc %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['taddcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('taddcc %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['taddcctv'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('taddcctv %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['subx'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('subx %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['subxcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('subxcc %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['tsubcc'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('tsubcc %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')

    for per in permutations:
        statistics_generated['tsubcctv'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        statistics_generated[per[2]] += 1
        instrs.append('tsubcctv %' + per[0] + ', %' + per[1] + ', %' + per[2] + '\n')
        


        #instrs.append('\n\n\n')

    return instrs

def generate_imm_instrs():
    # to get all possible combinations of window registers, taken 3 at a time
    permutations = list(itertools.permutations(window_regs, r=2))
    instrs = []
    for per in permutations:
        statistics_generated["sll"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'sll %' + per[0] + ', 0x' + 
            random.choice(hex_digits) + 
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["srl"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'srl %' + per[0] + ', 0x' + 
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["sra"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'sra %' + per[0] + ', 0x' +
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["add"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'add %' + per[0] + ', 0x' + 
            random.choice(hex_digits) + 
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["addcc"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'addcc %' + per[0] + ', 0x' + 
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["addx"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'addx %' + per[0] + ', 0x' +
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        )
    for per in permutations:
        statistics_generated["addxcc"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'addxcc %' + per[0] + ', 0x' + 
            random.choice(hex_digits) + 
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["taddcc"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'taddcc %' + per[0] + ', 0x' + 
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["taddcctv"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'taddcctv %' + per[0] + ', 0x' +
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        )    
    for per in permutations:
        statistics_generated["sub"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'sub %' + per[0] + ', 0x' + 
            random.choice(hex_digits) + 
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["subcc"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'subcc %' + per[0] + ', 0x' + 
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["subx"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'subx %' + per[0] + ', 0x' +
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        )
    for per in permutations:
        statistics_generated["subxcc"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'subxcc %' + per[0] + ', 0x' + 
            random.choice(hex_digits) + 
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["tsubcc"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'tsubcc %' + per[0] + ', 0x' + 
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["tsubcctv"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'tsubcctv %' + per[0] + ', 0x' +
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        ) 


    for per in permutations:
        statistics_generated["and"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'and %' + per[0] + ', 0x' + 
            random.choice(hex_digits) + 
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["andcc"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'andcc %' + per[0] + ', 0x' + 
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["andn"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'andn %' + per[0] + ', 0x' +
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        )
    for per in permutations:
        statistics_generated["andncc"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'andncc %' + per[0] + ', 0x' + 
            random.choice(hex_digits) + 
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["or"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'or %' + per[0] + ', 0x' + 
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["orcc"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'orcc %' + per[0] + ', 0x' +
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        )    
    for per in permutations:
        statistics_generated["orn"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'orn %' + per[0] + ', 0x' + 
            random.choice(hex_digits) + 
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["orncc"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'orncc %' + per[0] + ', 0x' + 
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["xor"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'xor %' + per[0] + ', 0x' +
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        )
    for per in permutations:
        statistics_generated["xorcc"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'xorcc %' + per[0] + ', 0x' + 
            random.choice(hex_digits) + 
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["xnor"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'xnor %' + per[0] + ', 0x' + 
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["xnorcc"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'xnorcc %' + per[0] + ', 0x' +
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        ) 

    for per in permutations:
        statistics_generated["umul"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'umul %' + per[0] + ', 0x' + 
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["umulcc"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'umulcc %' + per[0] + ', 0x' +
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        )    
    for per in permutations:
        statistics_generated["smul"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'smul %' + per[0] + ', 0x' + 
            random.choice(hex_digits) + 
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["smulcc"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'smulcc %' + per[0] + ', 0x' + 
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["udiv"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'udiv %' + per[0] + ', 0x' +
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        )
    for per in permutations:
        statistics_generated["udivcc"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'udivcc %' + per[0] + ', 0x' + 
            random.choice(hex_digits) + 
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["sdiv"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'sdiv %' + per[0] + ', 0x' + 
            random.choice(hex_digits) +
            ', %' + per[1] + '\n'
        ) 
    for per in permutations:
        statistics_generated["sdivcc"] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append(
            'sdivcc %' + per[0] + ', 0x' +
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
  #  main_asm.write('! 9 Feb 2021\n\n\n')
    main_asm.writelines(generate_reg_instrs())
    main_asm.writelines(generate_imm_instrs())
    main_asm.close()
    check_statistics()
    print("done!")
