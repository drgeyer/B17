#include <iomanip> //for std::hex, setw()
#include <fstream> //For opening obj
#include "instruc.h"
#include "switch.cpp"

void memstep(int startAddress);

//Author: Grant Hill
//Parses object file and places values in memory
int main(int argc, char *argv[])
{
	ifstream obj;
	int nextAddress, toRead, nextVal;

	obj.open(argv[1]); //File stuff

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
	} //Tested - works well enough

	//The nextAddress should have the address to start at.

	while(memory[nextAddress] != 0)
	{ //The program should halt on its own when the proper instruction is used.

		instruc nextInstruc =  parseInstruc(nextAddress);
		switchFunction(nextInstruc);

		if(nextInstruc.op == J)
			nextAddress = nextInstruc.addr;
		else if(nextInstruc.op == JZ && AC == 0)
			nextAddress = nextInstruc.addr;
		else if(nextInstruc.op == JN && AC < 0)
			nextAddress = nextInstruc.addr;
		else if(nextInstruc.op == JP && AC > 0)
			nextAddress = nextInstruc.addr;
		else
			nextAddress++;
	}

	return 0; //If the program ends with no halt message, we missed one.
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

