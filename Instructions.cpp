#include "instruc.h"

using namespace std;
//this file requires access to the memory space + all registers
extern int memory[0xFFF];

extern int MAR;
extern int IC;
extern int X0;
extern int X1;
extern int X2;
extern int X3;
extern int ABUS;
extern int MDR;
extern int AC;
extern int ALU;
extern int IR;
extern int DBUS;

//pass an instruction with the memory address, indexing mode, and op code
void HALT_Instr(instruc instr_data)
{
	
}

void NOP_Instr(instruc instr_data)
{
	
}

void LD_Instr(void)
{
	instruc instr_data = parseInstruc(memory[IC]);
	//Do the operation 
	
	//print the trace of what the instruction does AFTER it has been executed
	trace("LD", instr_data)
}

void ST_Instr(instruc instr_data)
{
	
}

void EM_Instr(instruc instr_data)
{
	
}

void ADD_Instr(instruc instr_data)
{
	
}

void SUB_Instr(instruc instr_data)
{
	
}

void CLR_Instr(instruc instr_data)
{
	
}

void COM_Instr(instruc instr_data)
{
	
}

void AND_Instr(instruc instr_data)
{
	
}

void OR_Instr(instruc instr_data)
{
	
}

void XOR_Instr(instruc instr_data)
{
	
}

void J_Instr(instruc instr_data)
{
	
}

void JZ_Instr(instruc instr_data)
{
	
}

void JN_Instr(instruc instr_data)
{
	
}

void JP_Instr(instruc instr_data)
{
	
}

void UnimplementedAddressing_Mode(instruc instr_data)
{
	
}

void IllegalAddressing_Mode(instruc instr_data)
{
	
}