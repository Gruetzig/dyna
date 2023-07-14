
all: test

test:
	gcc test.c -o test.o -c
	gcc dyna.c -o dyna.o -I. -c
	gcc -o testing test.o dyna.o 

clean: 
	rm testing test.o dyna.o