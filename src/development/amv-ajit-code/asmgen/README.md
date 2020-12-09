# asmgen

Investigating the issues involved in generating the assembler from a given CPU data sheets. This, of course, needs to be further parameterized with respect to the overall target machine and the target toolchain.

The GNU Binutils port of the AJIT processor is underway.  It can now assemble the arithmetic and logical insns. However, we need a way to check if the binary instructions that are generated are correct. Hence the "opcode-lister.py" script.  This was started as a C program, but quickly moved to Python.

The "opcode-lister.py" is a throwaway Python 3.x program that takes as input a description of the instructions (insns, for short) in a CSV file, and a description of possible bit field arrangements in a CSV file, and produces a set of instruction codes in binary (printed in hexadecimal format), and (in future) a template of ASM instruction of that opcode.  This should help in checking the correctness of assembling to an object file. The assembler is implemented in the GNU Binutils port for AJIT.

