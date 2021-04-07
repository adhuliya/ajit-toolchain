import itertools
import random
import json

global_reg = ['g0', 'g1', 'g2', 'g3', 'g4', 'g5', 'g6', 'g7']
out_reg = ['o0', 'o1', 'o2', 'o3', 'o4', 'o5', 'sp', 'o7']
local_reg = ['l0', 'l1', 'l2', 'l3', 'l4', 'l5', 'l6', 'l7']
in_reg = ['i0', 'i1', 'i2', 'i3', 'i4', 'i5', 'fp', 'i7']
window_regs = global_reg + out_reg + local_reg + in_reg # all registers in current window
hex_digits = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f']

statistics_generated = {}

def init_statistics():
    file = open('expected_stats.json', 'r')
    expected_stats = json.load(file)
    for x in expected_stats.keys():
        statistics_generated[x] = 0
    file.close()

def generate_synth_instrs():
    # to get all possible combinations of window registers, taken 3 at a time
    permutations = list(itertools.permutations(window_regs, r=2))
    #permutation = list(itertools.permutations(window_regs, r=2))
    instrs = []
    for per in permutations:
        statistics_generated['cmp'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('cmp  %' + per[0] + ', %' + per[1] + '\n')
    
    for i in window_regs:
        statistics_generated["cmp"] += 1
        statistics_generated[i] += 1
        instrs.append(
            'cmp  %' + i + ', 0x' + random.choice(hex_digits) + random.choice(hex_digits) + '\n'
        ) # cmp %l0, 0xF

    for per in window_regs:
        statistics_generated['tst'] += 1
        statistics_generated[per] += 1
        instrs.append('tst  %' + per + '\n')

    for x in window_regs:
        statistics_generated["set"] += 1
        statistics_generated[x] += 1
        instrs.append(
            'set  0x' + random.choice(hex_digits) +
            random.choice(hex_digits) + random.choice(hex_digits) + random.choice(hex_digits) +
            ', %' + x + '\n'
        ) # set 0x1234, %l3

    for per in window_regs:
        statistics_generated['not'] += 1
        statistics_generated[per] += 1
        instrs.append('not  %' + per + '\n')

    for per in permutations:
        statistics_generated['not'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('not  %' + per[0] + ', %' + per[1] + '\n')

    for per in window_regs:
        statistics_generated['neg'] += 1
        statistics_generated[per] += 1
        instrs.append('neg  %' + per + '\n')
    
    for per in permutations:
        statistics_generated['neg'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('neg  %' + per[0] + ', %' + per[1] + '\n')

    for per in window_regs:
        statistics_generated['inc'] += 1
        statistics_generated[per] += 1
        instrs.append('inc  %' + per + '\n')

    for per in window_regs:
        statistics_generated['inccc'] += 1
        statistics_generated[per] += 1
        instrs.append('inccc  %' + per + '\n')

    for per in window_regs:
        statistics_generated['dec'] += 1
        statistics_generated[per] += 1
        instrs.append('dec  %' + per + '\n')

    for per in window_regs:
        statistics_generated['deccc'] += 1
        statistics_generated[per] += 1
        instrs.append('deccc  %' + per + '\n')

    for i in window_regs:
        statistics_generated["inc"] += 1
        statistics_generated[i] += 1
        instrs.append(
            'inc  0x' + random.choice(hex_digits) + random.choice(hex_digits) + ', %' + i +'\n'
        ) # cmp %l0, 0xF

    for i in window_regs:
        statistics_generated["inccc"] += 1
        statistics_generated[i] += 1
        instrs.append(
            'inccc  0x' + random.choice(hex_digits) + random.choice(hex_digits) + ', %' + i + '\n'
        ) # cmp %l0, 0xF

    for i in window_regs:
        statistics_generated["dec"] += 1
        statistics_generated[i] += 1
        instrs.append(
            'dec  0x' + random.choice(hex_digits) + random.choice(hex_digits) + ', %' + i + '\n'
        ) # cmp %l0, 0xF

    for i in window_regs:
        statistics_generated["deccc"] += 1
        statistics_generated[i] += 1
        instrs.append(
            'deccc  0x' + random.choice(hex_digits) + random.choice(hex_digits) + ', %' + i + '\n'
        ) # cmp %l0, 0xF

    for per in permutations:
        statistics_generated['btst'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('btst  %' + per[0] + ', %' + per[1] + '\n')

    for i in window_regs:
        statistics_generated["btst"] += 1
        statistics_generated[i] += 1
        instrs.append(
            'btst  0x' + random.choice(hex_digits) + random.choice(hex_digits) + ', %' + i + '\n'
        ) # cmp %l0, 0xF

    for per in permutations:
        statistics_generated['bset'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('bset  %' + per[0] + ', %' + per[1] + '\n')

    for i in window_regs:
        statistics_generated["bset"] += 1
        statistics_generated[i] += 1
        instrs.append(
            'bset  0x' + random.choice(hex_digits) + random.choice(hex_digits) + ', %' + i + '\n'
        ) # cmp %l0, 0xF

    for per in permutations:
        statistics_generated['bclr'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('bclr  %' + per[0] + ', %' + per[1] + '\n')

    for i in window_regs:
        statistics_generated["bclr"] += 1
        statistics_generated[i] += 1
        instrs.append(
            'bclr  0x' + random.choice(hex_digits) + random.choice(hex_digits) + ', %' + i + '\n'
        ) # cmp %l0, 0xF

    for per in permutations:
        statistics_generated['btog'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('btog  %' + per[0] + ', %' + per[1] + '\n')

    for i in window_regs:
        statistics_generated["btog"] += 1
        statistics_generated[i] += 1
        instrs.append(
            'btog  0x' + random.choice(hex_digits) + random.choice(hex_digits) + ', %' + i + '\n'
        ) # cmp %l0, 0xF

    for per in window_regs:
        statistics_generated['clr'] += 1
        statistics_generated[per] += 1
        instrs.append('clr  %' + per + '\n')

    for per in permutations:
        statistics_generated['mov'] += 1
        statistics_generated[per[0]] += 1
        statistics_generated[per[1]] += 1
        instrs.append('mov  %' + per[0] + ', %' + per[1] + '\n')

    return instrs


def generate_mov_asr_instrs():
    instrs = []
    for x in range(1, 32):
        for y in window_regs:
            statistics_generated["mov"] += 1
            statistics_generated[y] += 1
            statistics_generated["asr"] += 1
            instrs.append(
                'mov  %' + y + ', %' + 'asr' + str(x) + '\n'
            ) # wr %l0, %asr16

    for x in range(1, 32):
        for y in window_regs:
            statistics_generated["mov"] += 1
            statistics_generated[y] += 1
            statistics_generated["asr"] += 1
            instrs.append(
                'mov  %' + 'asr' + str(x) + ', %' + y + '\n'
            ) # mov %asr16, %o0
    return instrs

    for x in range(1, 32):
            statistics_generated["mov"] += 1
            statistics_generated["asr"] += 1
            instrs.append(
                'mov  0x' + random.choice(hex_digits) + random.choice(hex_digits) + ', %' + 'asr' + str(x) + '\n'
            ) # wr 0xFF, %asr16

    return instrs


def generate_mov_psr_instrs():
    instrs = []
    statistics_generated["mov"] += 1
    statistics_generated["psr"] += 1
    instrs.append(
            'mov  0x' + random.choice(hex_digits) + random.choice(hex_digits) + ', %' + 'psr' + '\n'
        ) # mov  0x0F, %psr

    for i in window_regs:
        statistics_generated["mov"] += 1
        statistics_generated[i] += 1
        statistics_generated["psr"] += 1
        instrs.append(
            'mov  %' + i + ', %' + 'psr' + '\n'
        ) # mov %l0, %psr

    for i in window_regs:
        statistics_generated["mov"] += 1
        statistics_generated[i] += 1
        statistics_generated["psr"] += 1
        instrs.append(
            'mov  %' + 'psr, %' + i + '\n'
        ) # mov %psr, %o0
    return instrs

def generate_mov_tbr_instrs():
    instrs = []
    statistics_generated["mov"] += 1
    statistics_generated["tbr"] += 1
    instrs.append(
            'mov  0x' + random.choice(hex_digits) + random.choice(hex_digits) + ', %' + 'tbr' + '\n'
        ) 


    for i in window_regs:
        statistics_generated["mov"] += 1
        statistics_generated[i] += 1
        statistics_generated["tbr"] += 1
        instrs.append(
            'mov  %' + i +', %' + 'tbr' + '\n'
        ) 


    for i in window_regs:
        statistics_generated["mov"] += 1
        statistics_generated[i] += 1
        statistics_generated["tbr"] += 1
        instrs.append(
            'mov  %' + 'tbr, %' + i + '\n'
        ) 
    return instrs

def generate_mov_wim_instrs():
    instrs = []
    for i in window_regs:
        statistics_generated["mov"] += 1
        statistics_generated["wim"] += 1
        instrs.append(
            'mov  0x' + random.choice(hex_digits) + random.choice(hex_digits) + ', %' + 'wim' + '\n'
        ) # wr %l0, 0x10, %wim

    for i in window_regs:
        statistics_generated["mov"] += 1
        statistics_generated[i] += 1
        statistics_generated["wim"] += 1
        instrs.append(
            'mov  %' + i + ', %' + 'wim' + '\n'
        ) # wr %l0, 0x10, %wim

    for i in window_regs:
        statistics_generated["mov"] += 1
        statistics_generated[i] += 1
        statistics_generated["wim"] += 1
        instrs.append(
            'mov  %' + 'wim, % ' + i + '\n'
        ) # rd %wim, %o0
    return instrs

def generate_mov_y_instrs():
    instrs = []
    statistics_generated["mov"] += 1
    statistics_generated["y"] += 1
    instrs.append(
            'mov  0x' + random.choice(hex_digits) + random.choice(hex_digits) + ', %y' +'\n'
        ) 

    for i in window_regs:
        statistics_generated["mov"] += 1
        statistics_generated[i] += 1
        statistics_generated["y"] += 1
        instrs.append(
            'mov  %' + i + ', %' + 'y' + '\n'
        ) # wr %l0, 0x10, %wim


    for i in window_regs:
        statistics_generated["mov"] += 1
        statistics_generated[i] += 1
        statistics_generated["y"] += 1
        instrs.append(
            'mov  %' + 'y, %' + i + '\n'
        ) # mov %y, %o1
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
    main_asm.write('main:\n')
    main_asm.write('retl\n')
    main_asm.write('ret\n')
    main_asm.write('restore\n')
    main_asm.write('save\n')
    main_asm.writelines(generate_synth_instrs())
    main_asm.writelines(generate_mov_asr_instrs())
    main_asm.writelines(generate_mov_asr_instrs())
    main_asm.writelines(generate_mov_psr_instrs())
    main_asm.writelines(generate_mov_tbr_instrs())
    main_asm.writelines(generate_mov_wim_instrs())
    main_asm.writelines(generate_mov_y_instrs())
    main_asm.close()
    check_statistics()
    print("done!")
