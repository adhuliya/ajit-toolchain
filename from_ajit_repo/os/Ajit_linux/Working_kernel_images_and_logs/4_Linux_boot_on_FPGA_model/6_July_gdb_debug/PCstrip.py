#!/usr/bin/env python

target = open('PC_with_traps.txt', 'w')
target.write( "   PC   " + "\t" + "   PSR   " + "\t" + "   TBR   " + "\n")

with open('gdb_log.txt') as f:
    content = f.read().splitlines()

new_list = []
for line_num in range (0,len(content)):
	if (content[line_num] == "Sending packet: $g#67...Ack"):
		new_list.append((content[line_num+1].split())[2])
		line_num += 1
	
n = 8	
for reg_values in new_list:
	reg_list = [reg_values[i:i+n] for i in range(0, len(reg_values), n)]
	target.write( reg_list[68] + "\t" + reg_list[65] + "\t" + reg_list[67] + "\n")
	
target.close()
