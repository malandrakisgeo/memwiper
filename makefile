 
all: 	gcc -o fileoverwriter.o /fileoverwrite.c -lm
	gcc -o ramwiper.o /ramwiper.c
	gcc -o shredder.o /shredder.c -lm

install: all

