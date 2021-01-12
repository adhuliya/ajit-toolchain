gcc -g -c -DHZ=50 -DDHRYOPT  utils.c
gcc -g -c -DHZ=50   dhry_1.c
gcc -g -c  -DHZ=50  dhry_2.c
gcc -g -o dhrystone dhry_1.o dhry_2.o utils.o
