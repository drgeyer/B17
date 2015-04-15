CC=g++

CFLAGS=-c -g -Wall

all:
	g++ -g b17.cpp -o B17

clean:
	rm *o B17
