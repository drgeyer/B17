#include "instruc.h"
#include "Instructions.cpp"

const int HALT = 0x0;
const int NOP = 0x1;
const int LD = 0x10;
const int ST = 0x11;
const int EM = 0x12;
const int LDX = 0x18;
const int STX = 0x19;
const int EMX = 0x1a;
const int ADD = 0x20;
const int SUB = 0x21;
const int CLR = 0x22;
const int COM = 0x23;
const int AND = 0x24;
const int OR  = 0x25;
const int XOR = 0x26;
const int ADDX = 0x28;
const int SUBX = 0x29;
const int CLRX = 0x2a;
const int J   = 0x30;
const int JZ  = 0x31;
const int JN  = 0x32;
const int JP  = 0x33;


void switchFunction( instruc instr_data );
	
void switchFunction( instruc instr_data )
{

	switch( instr_data.op )
	{
	case HALT:
		HALT_Instr( instr_data );
		break;
	case NOP:
		NOP_Instr( instr_data );
		break;
	case LD:
		LD_Instr();
		break;
	case ST:
		ST_Instr( instr_data );
		break;
	case EM:
		EM_Instr( instr_data );
		break;
	case LDX:
		trace( "NOP", instr_data );
		cout << "Machine Halted - unimplemented opcode" << endl;
		exit(1);
		break;
	case STX:
		trace( "NOP", instr_data );
		cout << "Machine Halted - unimplemented opcode" << endl;
		exit(1);
		break;
	case EMX:
		trace( "NOP", instr_data );
		cout << "Machine Halted - unimplemented opcode" << endl;
		exit(1);
		break;
	case ADD:
		ADD_Instr( instr_data );
		break;
	case SUB:
		SUB_Instr( instr_data );
		break;
	case CLR:
		CLR_Instr( instr_data );
		break;
	case COM:
		COM_Instr( instr_data );
		break;
	case AND:
		AND_Instr( instr_data );
		break;
	case OR:
		OR_Instr( instr_data );
		break;
	case XOR:
		XOR_Instr( instr_data );
		break;
	case ADDX:
		trace( "NOP", instr_data );
		cout << "Machine Halted - unimplemented opcode" << endl;
		exit(1);
		break;
	case SUBX:
		trace( "NOP", instr_data );
		cout << "Machine Halted - unimplemented opcode" << endl;
		exit(1);
		break;
	case CLRX:
		trace( "NOP", instr_data );
		cout << "Machine Halted - unimplemented opcode" << endl;
		exit(1);
		break;
	case J:
		J_Instr( instr_data );
		break;
	case JZ:
		JZ_Instr( instr_data );
		break;
	case JN:
		JN_Instr( instr_data );
		break;
	case JP:
		JP_Instr( instr_data );
		break;
	default:
		trace( "???", instr_data );
		cout << "Machine Halted - undefined opcode" << endl;
		exit(2);
		break;
	}
}
