gcc -g -c dotproduct.c -o dotproduct.o
gcc -g -c init_vec.c -o init_vec.o
gcc -g -o dotproduct dotproduct.o init_vec.o -lm
