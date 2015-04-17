#include <iostream>
#include <fstream>

using namespace std;

struct instruc //Struct to hold the parsed instruction
{
	int addr;
	int op;
	int am;
};

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

	obj >> hex >> startAddress >> toRead;
	
	nextAddress = startAddress;
//This loop should read the object file into memory.	
do{

	for(int i = 0; i < toRead; i++)
		{
			obj >> hex >> nextVal;
			memory[nextAddress + i] = nextVal;
		}

	}while(obj >> hex >> nextAddress);

	return 0;
}

//executeAt function?


//Author: Grant Hill
//Parses the instuction from memory into address, opcode, and mode fields
instruc parseInstruc(int instruction);
{
	instruc struction; //Allocate a structure to hold the extracted parts

	//Declare bitmasks
	int addmodemask = 63; //111111 in binary
	int opmask = 0xFC0;
	int addrmask = 0xFFF000

	struction.am = addmodemask & instruction;
	struction.opmask = opmask & instruction;
	struction.opmask = struction.opmask >> 6; //Shift right after the mask is applied
	struction.addr = addrmask & instruction;
	struction.addr = struction.addr >> 12; 

	return struction;
}
