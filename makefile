CC=g++

CFLAGS=-c -g -Wall

all: globals instructions switch main
	g++ -o b17 switch.o globals.o instructions.o b17.o instruc.h

globals:
	${CC} ${CFLAGS} Globals.cpp -o globals.o

instructions:
	${CC} ${CFLAGS} Instructions.cpp -o instructions.o

switch:
	${CC} ${CFLAGS} switch.cpp -o switch.o

main:
	${CC} ${CFLAGS} b17.cpp -o b17.o

clean:
	rm *o b17
