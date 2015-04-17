CC=g++

CFLAGS=-c -g -Wall

all: globals instructions main
	g++ -o b17 globals.o instructions.o b17.o

globals:
	g++ -c -g Globals.cpp -o globals.o

instructions:
	g++ -c -g Instructions.cpp -o instructions.o

main:
	g++ -c -g b17.cpp -o b17.o

clean:
	rm *o b17
