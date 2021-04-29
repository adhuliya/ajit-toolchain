FILENAME = proc_link
HEADER = $(FILENAME).h

default:$(FILENAME)

$(FILENAME).o: $(FILENAME).c $(HEADER)

	gcc -c $(FILENAME).c -o $(FILENAME).o

$(FILENAME): $(FILENAME).o
	
	gcc $(FILENAME).o -o $(FILENAME)

clean:

	rm -f $(FILENAME).o $(FILENAME)  	
