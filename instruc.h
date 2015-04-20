#ifndef INSTRUC_H
#define INSTRUC_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct instruc //Struct to hold the parsed instruction
{
	int addr;
	int op;
	int am;
};



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
