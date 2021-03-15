import os
import filecmp
from sys import argv


run, filename = argv # Take the main.dis.s file as input argument.


# Edit diassembled file to contain only neumonics.
fin = open(filename)
fout = open(filename + '.tmp', 'w')
for line in fin:
    fout.write(line[23:])
fout.close()
fin.close()

with open(filename + '.tmp', 'r') as fin:
    data = fin.read().splitlines(True)
with open(filename, 'w') as fout:
    fout.writelines(data[2:])
    
# Compare the edited disassembled file to .s file (Currently showing error at first occurence '%')
# Should output True if files are same.
file_path = filename
file_name = os.path.basename(file_path)
index_of_dot = file_name.index('.')
file_name_with = file_name[:index_of_dot]
print(file_name_with)
print(filename)
comp = filecmp.cmp(file_name_with + '.s', filename , shallow = False)
print(comp)
