#include <iostream> //Printing trace
#include <string> //For passing strings to trace()
#include <iomanip> //For std::hex, setw()
#include <cstdlib> //for exit();
#include <fstream> //for file

using namespace std;


//Declare bitmasks
const int indexmask = 0x3;
const int addmodemask = 0x3C; //111100 in binary
const int opmask = 0xFC0;
const int addrmask = 0xFFF000;

//The 4096-word memory array from Globals.cpp
int memory[0xFFF]; 

//Values for addressing mode constants.
const int directam = 0;
const int immedam = 1;
const int indexam = 2;
const int indirectam = 4;
const int indexindirectam = 6;

//Global registers
int MAR;
int IC;
int X0;
int X1;
int X2;
int X3;
int ABUS;
int MDR;
int AC;
int ALU;
int IR;
int DBUS;

//Author: Grant Hill
//Parses the instuction from memory into address, opcode, and mode fields
instruc parseInstruc(int instruction);


void printInstruc(instruc instruction);
void switchFunction(  ); //Prototype for switch
void trace(string mnemonic);

//Opcode constants for other functions
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

//Declare processor instruction prototypes
void UnimplementedAddressing_Mode(instruc instr_data, string mnemonic);
void IllegalAddressing_Mode(instruc instr_data, string mnemonic);

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
	{ //Will end when program halts.

	ABUS = addmodemask & instruction;
	ABUS = ABUS >> 2;

	//Extract opcodes and addresses
	//Get the instruction
	IR = opmask & instruction;
	IR = IR >> 6; //Shift right after the mask is applied
	//And the proper memory address
	MAR = addrmask & instruction;
	MAR = MAR >> 12; 

	MDR = MDR;

	switch( IR )
	{
	case HALT:
		trace( "HALT" );
		cout << "Machine Halted - HALT instruction executed" << endl;
		exit(0);
		break;
	case NOP:
		trace( "NOP" );
		break;
	case LD:
		if( ABUS == directam )
		{
			AC = MDR;
			trace( "LD" );
		}
		else if( ABUS == immedam )
		{
			AC = MAR;
			trace( "LD");
		}
		else if ( ABUS >= indexam && ABUS <= indexindirectam )
		{
			UnimplementedAddressing_Mode( instr_data, "LD" );
		}
		else
		{
			IllegalAddressing_Mode( instr_data, "LD" );
		}
		break;
	case ST:
		if( ABUS == directam )
		{
			MDR = AC;
			trace( "ST" );
		}
		else if( ABUS == immedam )
		{
			IllegalAddressing_Mode( instr_data, "ST" );
		}
		else if ( ABUS >= indexam && ABUS <= indexindirectam )
		{
			UnimplementedAddressing_Mode( instr_data, "ST" );
		}
		else
		{
			IllegalAddressing_Mode( instr_data, "ST" );
		}
		break;
	case EM:
		if( ABUS == directam )
		{
			DBUS = AC;
			AC = MDR;
			MDR = DBUS;
			trace( "EM" );
		}
		else if( ABUS == immedam )
		{
			IllegalAddressing_Mode( instr_data, "ST" );
		}
		else if ( ABUS >= indexam && ABUS <= indexindirectam )
		{
			UnimplementedAddressing_Mode( instr_data, "ST" );
		}
		else
		{
			IllegalAddressing_Mode( instr_data, "ST" );
		}
		break;
	case LDX:
		trace( "LDX" );
		cout << "Machine Halted - unimplemented opcode" << endl;
		exit(1);
		break;
	case STX:
		trace( "LDX" );
		cout << "Machine Halted - unimplemented opcode" << endl;
		exit(1);
		break;
	case EMX:
		trace( "EMX" );
		cout << "Machine Halted - unimplemented opcode" << endl;
		exit(1);
		break;
	case ADD:
		if( ABUS == directam )
		{
			AC = AC + MDR;
			trace( "ADD" );
		}
		else if( ABUS == immedam )
		{
			AC = AC + MAR;
			trace( "ADD" );
		}
		else if ( ABUS >= indexam && ABUS <= indexindirectam )
		{
			UnimplementedAddressing_Mode( instr_data, "ADD" );
		}
		else
		{
			IllegalAddressing_Mode( instr_data, "ADD" );
		}
		break;
	case SUB:
		if( ABUS == directam )
		{
			AC = AC - MDR;
			trace( "SUB" );
		}
		else if( ABUS == immedam )
		{
			AC = AC - MAR;
			trace( "SUB" );
		}
		else if ( ABUS >= indexam && ABUS <= indexindirectam )
		{
			UnimplementedAddressing_Mode( instr_data, "SUB" );
		}
		else
		{
			IllegalAddressing_Mode( instr_data, "SUB" );
		}
		break;
	case CLR:
		//No addressing mode here, so it's ignored.
		//No address logic needed.
		AC = 0;
		trace("CLR");
		break;
	case COM:
		AC = ~AC;
		trace("COM");
		break;
	case AND:
		if( ABUS == directam )
		{
			AC = AC & MDR;
			trace( "AND" );
		}
		else if( ABUS == immedam )
		{
			AC = AC & MAR;
			trace( "AND" );
		}
		else if ( ABUS >= indexam && ABUS <= indexindirectam )
		{
			UnimplementedAddressing_Mode( instr_data, "AND" );
		}
		else
		{
			IllegalAddressing_Mode( instr_data, "AND" );
		}
		break;
	case OR:
		if( ABUS == directam )
		{
			AC = AC | MDR;
			trace( "OR" );
		}
		else if( ABUS == immedam )
		{
			AC = AC | MAR;
			trace( "OR" );
		}
		else if ( ABUS >= indexam && ABUS <= indexindirectam )
		{
			UnimplementedAddressing_Mode( instr_data, "OR" );
		}
		else
		{
			IllegalAddressing_Mode( instr_data, "OR" );
		}
		break;
	case XOR:
		if( ABUS == directam )
		{

			AC = AC ^ MDR;
			trace( "XOR" );
		}
		else if( ABUS == immedam )
		{
			AC = AC ^ MAR;
			trace( "XOR" );
		}
		else if ( ABUS >= indexam && ABUS <= indexindirectam )
		{
			UnimplementedAddressing_Mode( instr_data, "XOR" );
		}
		else
		{
			IllegalAddressing_Mode( instr_data, "XOR" );
		} 
		break;
	case ADDX:
		trace( "ADDX" );
		cout << "Machine Halted - unimplemented opcode" << endl;
		exit(1);
		break;
	case SUBX:
		trace( "SUBX" );
		cout << "Machine Halted - unimplemented opcode" << endl;
		exit(1);
		break;
	case CLRX:
		trace( "CLRX" );
		cout << "Machine Halted - unimplemented opcode" << endl;
		exit(1);
		break;
	case J:
		//Most of the jump logic is impemented in main.
		//So these just have to print a trace.
		if( ABUS == directam )
		{
			trace( "J");
		}
		else if( ABUS == immedam )
		{
			IllegalAddressing_Mode( instr_data, "J");
		}
		else if ( ABUS >= indexam && ABUS <= indexindirectam )
		{
			UnimplementedAddressing_Mode( instr_data, "J" );
		}
		else
		{
			IllegalAddressing_Mode( instr_data, "J" );
		}
		break;
	case JZ:
		//Most of the jump logic is impemented in main.
		//So these just have to print a trace.
		if( ABUS == directam )
		{
			trace( "JZ");
		}
		else if( ABUS == immedam )
		{
			IllegalAddressing_Mode( instr_data, "JZ");
		}
		else if ( ABUS >= indexam && ABUS <= indexindirectam )
		{
			UnimplementedAddressing_Mode( instr_data, "JZ" );
		}
		else
		{
			IllegalAddressing_Mode( instr_data, "JZ" );
		}
		break;
	case JN:
		//Most of the jump logic is impemented in main.
		//So these just have to print a trace.
 

		if( ABUS == directam )
		{
			trace( "JN");
		}
		else if( ABUS == immedam )
		{
			IllegalAddressing_Mode( instr_data, "JN");
		}
		else if ( ABUS >= indexam && ABUS <= indexindirectam )
		{
			UnimplementedAddressing_Mode( instr_data, "JN" );
		}
		else
		{
			IllegalAddressing_Mode( instr_data, "JN" );
		}
		break;
	case JP:
		 //Most of the jump logic is impemented in main.
		//So these just have to print a trace.
 		if( ABUS == directam )
		{
			trace( "JP");
		}
		else if( ABUS == immedam )
		{
			IllegalAddressing_Mode( instr_data, "JP");
		}
		else if ( ABUS >= indexam && ABUS <= indexindirectam )
		{
			UnimplementedAddressing_Mode( instr_data, "JP" );
		}
		else
		{
			IllegalAddressing_Mode( instr_data, "JP" );
		}
		break;
	default:
		trace( "???" );
		cout << "Machine Halted - undefined opcode" << endl;
		exit(2);
		break;
	}


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

//Print out trace
void trace(string mnemonic)
{ //Print out each line of trace


	cout << hex << setw(3) << setfill('0') << IC << ":  " << setw(6) <<  memory[IC] << " "
	 << setw(4) << setfill(' ') << left << mnemonic	<< " ";

	if ( (IR == ST && ABUS == immedam) || 
		(IR == EM && ABUS == immedam) || 
		(IR == J && ABUS == immedam) ||
		(IR == JZ && ABUS == immedam) ||
		(IR == JN && ABUS == immedam) ||
		(IR == JP && ABUS == immedam) ) 
		cout << "???"; //Handle illegal addressing modes by printing ???.
	else if(ABUS == immedam) //If the addressing mode is immediate, print IMM
		cout << "IMM";
	else if (IR == 0x0 || IR == 0x1 || IR == 0x18
		 || IR == 0x19 || IR == 0x1A || IR == 0x22
		  || IR == 0x23 || IR == 0x28 || IR == 0x29
			 || IR == 0x2A) //If no addressing mode, print three spaces
		cout << "   ";
	else
		cout << setw(3) << setfill('0') << right << hex << MAR; //Else, actually print the address


	cout << right << "  " << "AC[" << hex << setw(6) << setfill('0') << (AC & 0xffffff) << "]  X0[" << setw(3) << X0 <<
		"]  X1[" << setw(3) <<  X1 << "]  X2[" << setw(3) << X2 << "]  X3[" << setw(3) << X3 << "]" << endl;
	//And all the registers.

}

void UnimplementedAddressing_Mode(instruc instr_data, string mnemonic)
{
	trace( mnemonic );
	cout << "Machine Halted - unimplemented addressing mode";
	exit( 3 );
}

void IllegalAddressing_Mode(instruc instr_data, string mnemonic)
{
	trace( mnemonic );
	cout << "Machine Halted - illegal addressing mode";
	exit( 4 );
}
