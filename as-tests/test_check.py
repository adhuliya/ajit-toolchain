import os
from sys import argv

run, filename = argv



fin = open(filename, 'w+')
fout = open(filename + '.tmp', 'w')
#lines = fin.readlines()
for line in fin:
    #type = line.split(":")
    #res = type[1]
    fout.write(line[19:])
fout.close()
fin.close()
