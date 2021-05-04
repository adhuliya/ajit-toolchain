import sys
import os
from data import dict_ct

sys.stdout = open('main.s','wt')
print 'main:'
for key in dict_ct.keys():
    if ("T" in key):
        print str(key) + ' '+ '0'
        print str(key) + ' ' + '127'
    else:
        print str(key) +' '+'label'


    if(key[0] != "T" and key != 'CALL'):
        print str(key) + ',a '+ 'label'
