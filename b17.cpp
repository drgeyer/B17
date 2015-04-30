#include <iostream> //Printing trace
#include <string> //For passing strings to trace()
#include <iomanip> //For std::hex, setw()
#include <cstdlib> //for exit();
#include <fstream> //for file

using namespace std;

struct instruc //Struct to hold the parsed instruction
{
	int addr;
	int op;
	int am;
	int index;
};


//The 4096-word memory array from Globals.cpp
int memory[0xFFF]; 

//Values for addressing mode constants.
const int directam = 0;
const int immedam = 1;
const int indexam = 2;
const int indirectam = 4;
const int indexindirectam = 6;

//Get these from Globals.cpp
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

void memstep(int startAddress);
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

		instruc instr_data = parseInstruc(memory[IC]);

	switch( instr_data.op )
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
		if( instr_data.am == directam )
		{
			AC = memory[instr_data.addr];
			trace( "LD" );
		}
		else if( instr_data.am == immedam )
		{
			AC = instr_data.addr;
			trace( "LD");
		}
		else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
		{
			UnimplementedAddressing_Mode( instr_data, "LD" );
		}
		else
		{
			IllegalAddressing_Mode( instr_data, "LD" );
		}
		break;
	case ST:
		if( instr_data.am == directam )
		{
			memory[instr_data.addr] = AC;
			trace( "ST" );
		}
		else if( instr_data.am == immedam )
		{
			IllegalAddressing_Mode( instr_data, "ST" );
		}
		else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
		{
			UnimplementedAddressing_Mode( instr_data, "ST" );
		}
		else
		{
			IllegalAddressing_Mode( instr_data, "ST" );
		}
		break;
	case EM:
		if( instr_data.am == directam )
		{
			DBUS = AC;
			AC = memory[instr_data.addr];
			memory[instr_data.addr] = DBUS;
			trace( "EM" );
		}
		else if( instr_data.am == immedam )
		{
			IllegalAddressing_Mode( instr_data, "ST" );
		}
		else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
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
		if( instr_data.am == directam )
		{
			AC = AC + memory[instr_data.addr];
			trace( "ADD" );
		}
		else if( instr_data.am == immedam )
		{
			AC = AC + instr_data.addr;
			trace( "ADD" );
		}
		else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
		{
			UnimplementedAddressing_Mode( instr_data, "ADD" );
		}
		else
		{
			IllegalAddressing_Mode( instr_data, "ADD" );
		}
		break;
	case SUB:
		if( instr_data.am == directam )
		{
			AC = AC - memory[instr_data.addr];
			trace( "SUB" );
		}
		else if( instr_data.am == immedam )
		{
			AC = AC - instr_data.addr;
			trace( "SUB" );
		}
		else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
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
		if( instr_data.am == directam )
		{
			AC = AC & memory[instr_data.addr];
			trace( "AND" );
		}
		else if( instr_data.am == immedam )
		{
			AC = AC & instr_data.addr;
			trace( "AND" );
		}
		else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
		{
			UnimplementedAddressing_Mode( instr_data, "AND" );
		}
		else
		{
			IllegalAddressing_Mode( instr_data, "AND" );
		}
		break;
	case OR:
		if( instr_data.am == directam )
		{
			AC = AC | memory[instr_data.addr];
			trace( "OR" );
		}
		else if( instr_data.am == immedam )
		{
			AC = AC | instr_data.addr;
			trace( "OR" );
		}
		else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
		{
			UnimplementedAddressing_Mode( instr_data, "OR" );
		}
		else
		{
			IllegalAddressing_Mode( instr_data, "OR" );
		}
		break;
	case XOR:
		if( instr_data.am == directam )
		{

			AC = AC ^ memory[instr_data.addr];
			trace( "XOR" );
		}
		else if( instr_data.am == immedam )
		{
			AC = AC ^ instr_data.addr;
			trace( "XOR" );
		}
		else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
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
		if( instr_data.am == directam )
		{
			trace( "J");
		}
		else if( instr_data.am == immedam )
		{
			IllegalAddressing_Mode( instr_data, "J");
		}
		else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
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
		if( instr_data.am == directam )
		{
			trace( "JZ");
		}
		else if( instr_data.am == immedam )
		{
			IllegalAddressing_Mode( instr_data, "JZ");
		}
		else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
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
 

		if( instr_data.am == directam )
		{
			trace( "JN");
		}
		else if( instr_data.am == immedam )
		{
			IllegalAddressing_Mode( instr_data, "JN");
		}
		else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
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
 		if( instr_data.am == directam )
		{
			trace( "JP");
		}
		else if( instr_data.am == immedam )
		{
			IllegalAddressing_Mode( instr_data, "JP");
		}
		else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
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

		instruc nextInstruc = parseInstruc(memory[IC]);

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

	instruc instruction = parseInstruc(memory[IC]);

	cout << hex << setw(3) << setfill('0') << IC << ":  " << setw(6) <<  memory[IC] << " "
	 << setw(4) << setfill(' ') << left << mnemonic	<< " ";

	if ( (instruction.op == ST && instruction.am == immedam) || 
		(instruction.op == EM && instruction.am == immedam) || 
		(instruction.op == J && instruction.am == immedam) ||
		(instruction.op == JZ && instruction.am == immedam) ||
		(instruction.op == JN && instruction.am == immedam) ||
		(instruction.op == JP && instruction.am == immedam) ) 
		cout << "???"; //Handle illegal addressing modes by printing ???.
	else if(instruction.am == immedam) //If the addressing mode is immediate, print IMM
		cout << "IMM";
	else if (instruction.op == 0x0 || instruction.op == 0x1 || instruction.op == 0x18
		 || instruction.op == 0x19 || instruction.op == 0x1A || instruction.op == 0x22
		  || instruction.op == 0x23 || instruction.op == 0x28 || instruction.op == 0x29
			 || instruction.op == 0x2A) //If no addressing mode, print three spaces
		cout << "   ";
	else
		cout << setw(3) << setfill('0') << right << hex << instruction.addr; //Else, actually print the address


	cout << right << "  " << "AC[" << hex << setw(6) << setfill('0') << (AC & 0xffffff) << "]  X0[" << setw(3) << X0 <<
		"]  X1[" << setw(3) <<  X1 << "]  X2[" << setw(3) << X2 << "]  X3[" << setw(3) << X3 << "]" << endl;
	//And all the registers.

}

instruc parseInstruc(int instruction)
{
	instruc struction; //Allocate a structure to hold the extracted parts

	//Declare bitmasks
	int indexmask = 0x3;
	int addmodemask = 0x3C; //111100 in binary
	int opmask = 0xFC0;
	int addrmask = 0xFFF000;

	struction.index = indexmask & instruction;
	struction.am = addmodemask & instruction;
	struction.am = struction.am >> 2;
	struction.op = opmask & instruction;
	struction.op = struction.op >> 6; //Shift right after the mask is applied
	struction.addr = addrmask & instruction;
	struction.addr = struction.addr >> 12; 

	return struction;
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