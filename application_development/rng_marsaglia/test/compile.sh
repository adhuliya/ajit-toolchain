gcc -g -c -D DEBUG__  -I ../include ../src/rng_marsaglia.c -o rng_marsaglia.o
gcc -g -c -I ../include -I ./ main.c
gcc -g -o test_rng rng_marsaglia.o main.o -lm 
