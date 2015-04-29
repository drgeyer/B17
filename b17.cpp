#include <fstream> //For reading .obj
#include "instruc.h"

void memstep(int startAddress);

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


	cout << "Program starts at: " << nextAddress << endl;
	//The nextAddress should have the address to start at.

	while(true)
	{ //The program should halt on its own when the proper instruction is used.
	//Call this a failsafe or whatever.

		instruc nextInstruc =  parseInstruc(nextAddress);
		switchFunction(nextInstruc);

		if(nextInstruc.op == J) //Branching implementation
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

	trace( "HALT", parseInstruc(0));
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

//Print out trace
void trace(string mnemonic, instruc instruction)
{ //Print out each line of trace

	cout << hex << setw(3) << setfill('0') << instruction.addr << ":  " << setw(6) <<  memory[IC] << "  "
	 << setw(3) << mnemonic	<< "   ";

	if(instruction.am == immedam) //If the addressing mode is immediate, print IMM
		cout << "IMM";
	else if (instruction.op == 0x0 || instruction.op == 0x1 || instruction.op == 0x18
		 || instruction.op == 0x19 || instruction.op == 0x1A || instruction.op == 0x22
		  || instruction.op == 0x23 || instruction.op == 0x28 || instruction.op == 0x29
			 || instruction.op == 0x2A) //If no addressing mode, print three spaces
		cout << "   ";
	else
		cout << setw(3) << setfill('0') << hex << instruction.addr; //Else, actually print the address


	cout << "  " << "AC[" << hex << setw(6) << setfill('0') << AC << "]  X0[" << setw(3) << X0 <<
		"]  X1[" << setw(3) <<  X1 << "]  X2[" << setw(3) << X2 << "]  X3[" << setw(3) << X3 << "]" << endl;
	//And all the registers.

}

instruc parseInstruc(int instruction)
{
	instruc struction; //Allocate a structure to hold the extracted parts

	//Declare bitmasks
	int addmodemask = 0x3F; //111111 in binary
	int opmask = 0xFC0;
	int addrmask = 0xFFF000;

	struction.am = addmodemask & instruction;
	struction.op = opmask & instruction;
	struction.op = struction.op >> 6; //Shift right after the mask is applied
	struction.addr = addrmask & instruction;
	struction.addr = struction.addr >> 12; 

	return struction;
}
