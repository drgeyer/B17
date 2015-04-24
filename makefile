CC=g++

CFLAGS=-c -g -Wall -std=c++11

all: globals instructions switch main
	g++ -o b17  b17.cpp instruc.h switch.o globals.o instructions.o

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
