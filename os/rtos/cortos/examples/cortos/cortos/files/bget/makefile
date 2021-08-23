# building bget (just for reference)

CC = cc
COPTS = -O

bget:	bget.c.tpl bget.h.tpl
	$(CC) $(COPTS) bget.c -o bget -lm
	rm -f core

lint:
	lint bget.c -lm

clean:
	rm -f bget core *.o *.bak *.exe *.obj *.swp
