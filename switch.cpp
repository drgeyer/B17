#include "instruc.h"

void switchFunction()
{

	instruc instr_data = parseInstruc(memory[IC]);

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
		trace( "NOP" );
		cout << "Machine Halted - unimplemented opcode" << endl;
		exit(1);
		break;
	case STX:
		trace( "NOP" );
		cout << "Machine Halted - unimplemented opcode" << endl;
		exit(1);
		break;
	case EMX:
		trace( "NOP" );
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
		trace( "NOP" );
		cout << "Machine Halted - unimplemented opcode" << endl;
		exit(1);
		break;
	case SUBX:
		trace( "NOP" );
		cout << "Machine Halted - unimplemented opcode" << endl;
		exit(1);
		break;
	case CLRX:
		trace( "NOP" );
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
		trace( "???" );
		cout << "Machine Halted - undefined opcode" << endl;
		exit(2);
		break;
	}
}
