 
all: 	gcc -o fileoverwriter.o /fileoverwrite.c -lm
	gcc -o ramwiper.o /overwrite-ram.c
	gcc -o shredder.o /shredder.c -lm

install: all
