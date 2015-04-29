#include "instruc.h"



	
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
		LD_Instr( instr_data );
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
