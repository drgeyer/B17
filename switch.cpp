

void switchFunction( int oppCode );


void switchFunction( int oppCode )
{
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
	switch( oppCode )
	{
	case HALT:
	case NOP:
	case LD:
	case ST:
	case EM:
	case LDX:
	case STX:
	case EMX:
	case ADD:
	case SUB:
	case CLR:
	case COM:
	case AND:
	case OR:
	case XOR:
	case ADDX:
	case SUBX:
	case CLRX:
	case J:
	case JZ:
	case JN:
	case JP:
	}
}