CFLAGS=-O -Wuninitialized -Werror  -I include/

all: example-codelock example-buffer example-small

example-codelock: util/example-codelock.c  include/pt.h include/lc.h 
	gcc -o bin/example-codelock $(CFLAGS) util/example-codelock.c 

example-buffer: util/example-buffer.c  include/pt.h include/lc.h
	gcc -o bin/example-buffer $(CFLAGS) util/example-buffer.c 

example-small: util/example-small.c include/pt.h include/lc.h
	gcc -o bin/example-small $(CFLAGS) util/example-small.c 

clean:
	rm -f bin/*
