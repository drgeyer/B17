CC=g++

CFLAGS=-c -g -Wall 

all: b17

b17: globals instructions switch main
	${CC} -g -Wall  instruc.h  switch.o Globals.o Instructions.o b17.o -o b17

globals:
	${CC} ${CFLAGS} Globals.cpp -o Globals.o

instructions:
	${CC} ${CFLAGS} Instructions.cpp -o Instructions.o

switch:
	${CC} ${CFLAGS} switch.cpp  -o switch.o

main:
	${CC} ${CFLAGS} b17.cpp -o b17.o

clean:
	rm *o b17
