#include <iostream>
#include <iomanip>
#include <fstream>
#include "instruc.h"
#include "switch.cpp";




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

