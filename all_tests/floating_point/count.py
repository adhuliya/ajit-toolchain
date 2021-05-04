


import re
text = open("main.s", "r")
d = dict()
for line in text:
    line = line.strip("\n")
    line = re.split(r'[\[\];+,\s%]', line)
    for word in line:
        if word in d:
            d[word] = d[word] + 1
        else:
            d[word] = 1

with open ("main.py" , "w") as f:
    f.write('dict_out ={')
    for key in list(d.keys()):
        out = '"' +  str(key) + '"' + ':' +  str(d[key]) +','
        f.write(out + '\n')
    f.write('}')


def compare(first, second):
    sharedKeys = set(first.keys()).intersection(second.keys())
    for key in sharedKeys:
        if first[key] != second[key]:
            print('Key: {}, Value 1: {}, Value 2: {}'.format(key, first[key], second[key]))


from data import dict_count
from main import dict_out
compare(dict_count, dict_out)
