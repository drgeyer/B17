#include <iostream>
#include <iomanip>
#include <fstream>
#include "instruc.h"
#include "switch.cpp";


//Values for addressing mode constants.
//Can go in separate .h if needed.
const int directam = 0;
const int immedam = 1;
const int indexam = 2;
const int indirectam = 4;
const int indexindirectam = 6;

extern int IC, AC, X0, X1, X2, X3;

//The 4096-word memory array
int memory[0xFFF] = {0}; //Init to zero

void memstep(int startAddress);
instruc parseInstruc(int instruction);

//Author: Grant Hill
//Parses object file and places values in memory
int main(int argc, char *argv[])
{
	ifstream obj;
	int nextAddress, toRead, nextVal;

	obj.open(argv[1]);

	if(!obj)
	{
		cout << "Could not open " << argv[1] << endl;
		return -1;
	}


//This loop should read the object file into memory.	
	while(obj >> hex >> nextAddress)
	{
		if(obj >> hex >> toRead)
		{

			for(int i = 0; i < toRead; i++)
				{
					obj >> hex >> nextVal;
					memory[nextAddress + i] = nextVal;
				}

		}
	}

	//The nextAddress should have the address to start at.


	return 0;
}

//executeAt function?



//Author: Grant Hill
//Steps through memory and prints out hex values. Used for testing the object
//file parser.
void memstep(int startAddress)
{

	//Print out memory starting at start address
	while(memory[startAddress] != 0)
	{
		cout << hex << startAddress << " " << hex <<  memory[startAddress] << " ";
		startAddress++;
	}

}

