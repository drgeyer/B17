CC=g++

CFLAGS=-c -g -Wall 

all: proj

proj: Globals Instructions switch b17
	${CC} -g -Wall  instruc.h  switch.o Globals.o Instructions.o b17.o -o b17

Globals:
	${CC} ${CFLAGS} Globals.cpp -o Globals.o

Instructions:
	${CC} ${CFLAGS} Instructions.cpp -o Instructions.o

switch:
	${CC} ${CFLAGS} switch.cpp  -o switch.o

b17:
	${CC} ${CFLAGS} b17.cpp -o b17.o

clean:
	rm *o b17
