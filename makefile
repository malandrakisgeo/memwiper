 
all: 	
	gcc -o fileoverwriter.o fileoverwriter.c -lm -I.
	gcc -o ramwiper.o ramwiper.c
	gcc -o shredder.o shredder.c -lm -I.

install: all

clean: 
	find  . -name \*.o -type f -delete
