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

int not_used = 0;

//pass an instruction with the memory address, indexing mode, and op code
void HALT_Instr(instruc instr_data)
{
	trace( "HALT", instr_data, EA );
	cout << "Machine Halted - HALT instruction executed" << endl;
	exit(0);
}

void NOP_Instr(instruc instr_data)
{
	trace( "NOP", instr_data, EA );
	return;
}

void LD_Instr(void)
{
	instruc instr_data = parseInstruc(memory[IC]);
	//Do the operation 
	
	//print the trace of what the instruction does AFTER it has been executed
	trace("LD", instr_data, EA);
}

void ST_Instr(instruc instr_data)
{
	
}

void EM_Instr(instruc instr_data)
{
	
}

void ADD_Instr(instruc instr_data)
{
	if( instr_data.am == 0000 )
	{
		AC = AC + memory[instr_data.addr];
		trace( "ADD", instr_data );
	}
	else if( instr_data.am == 0001 )
	{
		AC = AC + instr_data.addr;
		trace( "ADD", instr_data );
	}
	else if ( instr_data.am >= 0010 && instr_data.am <= 0110 )
	{
		UnimplementedAddressing_Mode( instr_data, "ADD" );
	}
	else
	{
		IllegalAddressing_Mode( instr_data, "ADD" );
	}
}

void SUB_Instr(instruc instr_data)
{
	
}

void CLR_Instr(instruc instr_data)
{
	AC = 0;
}

void COM_Instr(instruc instr_data)
{
	AC = ~AC;
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

void UnimplementedAddressing_Mode(instruc instr_data, string mnemonic)
{
	trace( mnemonic, instr_data, EA );
	cout << "Machine Halted - unimplemented addressing mode";
	exit( 3 );
}

void IllegalAddressing_Mode(instruc instr_data, string mnemonic)
{
	trace( mnemonic, instr_data, EA );
	cout << "Machine Halted - illegal addressing mode";
	exit( 4 );
}