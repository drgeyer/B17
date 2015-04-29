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


	//The nextAddress should have the address to start at.

	IC = nextAddress;

	while(true)
	{

		switchFunction();

		instruc nextInstruc = parseInstruc(memory[IC]);

		if(nextInstruc.op == J) //Branching implementation
			IC = nextInstruc.addr;
		else if(nextInstruc.op == JZ && AC == 0)
			IC = nextInstruc.addr;
		else if(nextInstruc.op == JN && AC < 0)
			IC = nextInstruc.addr;
		else if(nextInstruc.op == JP && AC > 0)
			IC = nextInstruc.addr;
		else
			IC++;
	}

	return 0; //If the program ends with no halt message, we missed one.
}


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
void trace(string mnemonic)
{ //Print out each line of trace

	instruc instruction = parseInstruc(memory[IC]);

	cout << hex << setw(3) << setfill('0') << IC << ":  " << setw(6) <<  memory[IC] << " "
	 << setw(4) << setfill(' ') << left << mnemonic	<< " ";

	if ( (instruction.op == ST && instruction.am == immedam) || 
		(instruction.op == EM && instruction.am == immedam) || 
		(instruction.op == J && instruction.am == immedam) ||
		(instruction.op == JZ && instruction.am == immedam) ||
		(instruction.op == JN && instruction.am == immedam) ||
		(instruction.op == JP && instruction.am == immedam) ) 
		cout << "???"; //Handle illegal addressing modes by printing ???.
	else if(instruction.am == immedam) //If the addressing mode is immediate, print IMM
		cout << "IMM";
	else if (instruction.op == 0x0 || instruction.op == 0x1 || instruction.op == 0x18
		 || instruction.op == 0x19 || instruction.op == 0x1A || instruction.op == 0x22
		  || instruction.op == 0x23 || instruction.op == 0x28 || instruction.op == 0x29
			 || instruction.op == 0x2A) //If no addressing mode, print three spaces
		cout << "   ";
	else
		cout << setw(3) << setfill('0') << right << hex << instruction.addr; //Else, actually print the address


	cout << right << "  " << "AC[" << hex << setw(6) << setfill('0') << (AC & 0xffffff) << "]  X0[" << setw(3) << X0 <<
		"]  X1[" << setw(3) <<  X1 << "]  X2[" << setw(3) << X2 << "]  X3[" << setw(3) << X3 << "]" << endl;
	//And all the registers.

}

instruc parseInstruc(int instruction)
{
	instruc struction; //Allocate a structure to hold the extracted parts

	//Declare bitmasks
	int indexmask = 0x3;
	int addmodemask = 0x3C; //111100 in binary
	int opmask = 0xFC0;
	int addrmask = 0xFFF000;

	struction.index = indexmask & instruction;
	struction.am = addmodemask & instruction;
	struction.am = struction.am >> 2;
	struction.op = opmask & instruction;
	struction.op = struction.op >> 6; //Shift right after the mask is applied
	struction.addr = addrmask & instruction;
	struction.addr = struction.addr >> 12; 

	return struction;
}


void printInstruc(instruc instruction)
{
	cout << "Index: " << instruction.index << endl;
	cout << "Addressing mode: " << instruction.am << endl;
	cout << "Opcode: " << instruction.op << endl;
	cout << "Address: " << instruction.addr << endl;

}
