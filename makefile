CC=g++

CFLAGS=-c -g -Wall 

all: proj

proj:  b17
	${CC} -g -Wall  b17.o -o b17

b17:
	${CC} ${CFLAGS} b17.cpp -o b17.o

clean:
	rm *o b17
