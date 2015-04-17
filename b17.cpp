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

void trace(string mnemonic, instruc instruction, int EA)
{


	cout << hex << instruction.addr << ":  " << memory[IC] << "  " << mnemonic
		<< "\t";

	if(instruction.am = immedam) //If the addressing mode is immediate, print IMM
		cout << "IMM";
	else if (instruction.op == 0x0 || instruction.op == 0x1 || instruction.op == 0x18
		 || instruction.op == 0x19 || instruction.op == 0x1A || instructiom.op == 0x22
		  || instruction.op == 0x23 || instuction.op == 0x28 || instruction.op == 0x29
			 || instruction.op == 0x2A)
		cout << "   ";
	else
		cout << hex << EA;


	cout << "  " << "AC[" << hex << setw(6) << AC << "] X0[" << setw(3) << X0 <<
		"] X1[" << X1 << "] X2[" << X2 << "] X3[" << X3 << "]" << endl;


}
