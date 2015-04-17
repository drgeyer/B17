#include <iostream>
#include <fstream>

using namespace std;

struct instruc //Struct to hold the parsed instruction
{
	int addr;
	int op;
	int am;
};

//Values for addressing mode constants.
//Can go in separate .h if needed.
const int directam = 0;
const int immedam = 1;
const int indexam = 2;
const int indirectam = 4;
const int indexdirectam = 6;



//The 4096-word memory array
int memory[0xFFF] = {0}; //Init to zero



instruc parseInstruc(int instruction);

//Author: Grant Hill
//Parses object file and places values in memory
int main(int argc, char *argv[])
{
	ifstream obj;
	int startAddress, nextAddress, toRead, nextVal;

	obj.open(argv[1]);

	if(!obj)
	{
		cout << "Could not open " << argv[1] << endl;
		return -1;
	}


//This loop should read the object file into memory.	
	while(obj >> hex >> nextAddress)
	{

		if(!obj.eof())
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
//Parses the instuction from memory into address, opcode, and mode fields
instruc parseInstruc(int instruction)
{
	instruc struction; //Allocate a structure to hold the extracted parts

	//Declare bitmasks
	int addmodemask = 63; //111111 in binary
	int opmask = 0xFC0;
	int addrmask = 0xFFF000;

	struction.am = addmodemask & instruction;
	struction.op = opmask & instruction;
	struction.op = struction.op >> 6; //Shift right after the mask is applied
	struction.addr = addrmask & instruction;
	struction.addr = struction.addr >> 12; 

	return struction;
}
