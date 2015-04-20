#ifndef INSTRUC_H
#define INSTRUC_H
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct instruc //Struct to hold the parsed instruction
{
	int addr;
	int op;
	int am;
};


//The 4096-word memory array
int memory[0xFFF] = {0}; //Init to zero

//Values for addressing mode constants.
const int directam = 0;
const int immedam = 1;
const int indexam = 2;
const int indirectam = 4;
const int indexindirectam = 6;

extern int IC, AC, X0, X1, X2, X3;

void trace(string mnemonic, instruc instruction, int EA)
{


	cout << hex << instruction.addr << ":  " << memory[IC] << "  " << mnemonic
		<< "\t";

	if(instruction.am == immedam) //If the addressing mode is immediate, print IMM
		cout << "IMM";
	else if (instruction.op == 0x0 || instruction.op == 0x1 || instruction.op == 0x18
		 || instruction.op == 0x19 || instruction.op == 0x1A || instruction.op == 0x22
		  || instruction.op == 0x23 || instruction.op == 0x28 || instruction.op == 0x29
			 || instruction.op == 0x2A)
		cout << "   ";
	else
		cout << hex << EA;


	cout << "  " << "AC[" << hex << setw(6) << AC << "] X0[" << setw(3) << X0 <<
		"] X1[" << X1 << "] X2[" << X2 << "] X3[" << X3 << "]" << endl;


}


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

#endif /* INSTRUC_H */
