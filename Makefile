
all: test

test:
	gcc test.c -o test.o -c
	gcc dynarr.c -o dynarr.o -I. -c
	gcc -o testing test.o dynarr.o 

clean: 
	rm testing test.o dynarr.o