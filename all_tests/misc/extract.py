import re

#get file object reference to the file
file = open("misc.s", "r")
#read content of file to string
data = file.read()
#get number of occurrences of the substring in the string
occurrences = data.count("zbytedpos")
print('Number of occurrences of the word :', occurrences)

with open("data.asm.s", "w") as f1:
    with open("opcodes.asm.s", "r") as f:
        for lines in f:
            lin=lines.strip("\\n")
            chunks = [lin[i:i+4] for i in range(0, 31, 4)]
            out = ""
            for data in chunks:
                line = hex(int(str(data), 2))[2:]
                out = out + line      
            f1.write(out.upper()+'\n')

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


