import re


fout = open( "main.dis.s.tmp", 'w')
with open("main.dis.s", "r") as f:
	for instr in f:
		instr = instr.rstrip("\n")
		opcode = re.search(r':\s[\da-z]*\s',instr)
		if opcode != None :
			opcode = re.search(r':(\s[\da-z]*\s[\da-z]*\s[\da-z]*\s[\da-z]*)',instr).group(1)
			opcode = opcode.lstrip()
                        data = opcode.replace(" ", "")
                        fout.write(data.upper())
                        fout.write("\n")
f.close()
fout.close()

fout = open( "main.as.s.tmp", 'w')
with open("main.as.s", "r") as f:
	for instr in f:
		opcode = re.search(r'\s[\da-z]+\s[\da-z]+\s([\dA-Z]+)',instr)
		if opcode != None  :
			opcode = re.search(r'\s[\da-z]+\s[\da-z]+\s([\dA-Z]+)',instr).group(1)
			opcode = opcode.rstrip("\n")
			fout.write(opcode)
                        fout.write("\n")
f.close()
fout.close()

fout = open( "main.gdbdis.s.tmp", 'w')
with open("main.gdbdis.s", "r") as f:
        for instr in f:
                instr = instr.rstrip("\n")
                opcode = re.search(r':\s[\da-z]*\s',instr)
                if opcode != None :
                        opcode = re.search(r':(\s[\da-z]*\s[\da-z]*\s[\da-z]*\s[\da-z]*)',instr).group(1)
                        opcode = opcode.lstrip()
                        data = opcode.replace(" ", "")
                        fout.write(data.upper())
                        fout.write("\n")
f.close()
fout.close()

                        
