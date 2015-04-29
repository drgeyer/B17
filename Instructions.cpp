#include "instruc.h"

//Requires all registers
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


void UnimplementedAddressing_Mode(instruc instr_data, string mnemonic);
void IllegalAddressing_Mode(instruc instr_data, string mnemonic);

int not_used = 0;

//pass an instruction with the memory address, indexing mode, and op code
void HALT_Instr(instruc instr_data)
{
	trace( "HALT", instr_data );
	cout << "Machine Halted - HALT instruction executed" << endl;
	exit(0);
}

void NOP_Instr(instruc instr_data)
{
	trace( "NOP", instr_data );
	return;
}

void LD_Instr(instruc instr_data)
{
	//Do the operation
	if( instr_data.am == directam )
	{
		AC = memory[instr_data.addr];
		trace( "LD", instr_data );
	}
	else if( instr_data.am == immedam )
	{
		AC = instr_data.addr;
		trace( "LD", instr_data);
	}
	else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
	{
		UnimplementedAddressing_Mode( instr_data, "LD" );
	}
	else
	{
		IllegalAddressing_Mode( instr_data, "LD" );
	}
	
}

void ST_Instr(instruc instr_data)
{
	if( instr_data.am == directam )
	{
		memory[instr_data.addr] = AC;
		trace( "ST", instr_data );
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
}

void EM_Instr(instruc instr_data)
{
	if( instr_data.am == directam )
	{
		DBUS = AC;
		AC = memory[instr_data.addr];
		memory[instr_data.addr] = DBUS;
		trace( "EM", instr_data );
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
}

void ADD_Instr(instruc instr_data)
{
	if( instr_data.am == directam )
	{
		AC = AC + memory[instr_data.addr];
		trace( "ADD", instr_data );
	}
	else if( instr_data.am == immedam )
	{
		AC = AC + instr_data.addr;
		trace( "ADD", instr_data );
	}
	else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
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
	if( instr_data.am == directam )
	{
		AC = AC - memory[instr_data.addr];
		trace( "SUB", instr_data );
	}
	else if( instr_data.am == immedam )
	{
		AC = AC - instr_data.addr;
		trace( "SUB", instr_data );
	}
	else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
	{
		UnimplementedAddressing_Mode( instr_data, "SUB" );
	}
	else
	{
		IllegalAddressing_Mode( instr_data, "SUB" );
	}
}

void CLR_Instr(instruc instr_data)
{ //No addressing mode here, so it's ignored.
//No address logic needed.
	AC = 0;

	trace("CLR", instr_data);
}

void COM_Instr(instruc instr_data)
{
	AC = ~AC;

	trace("COM", instr_data);
}

void AND_Instr(instruc instr_data)
{
	if( instr_data.am == directam )
	{
		AC = AC & memory[instr_data.addr];
		trace( "AND", instr_data );
	}
	else if( instr_data.am == immedam )
	{
		AC = AC & instr_data.addr;
		trace( "AND", instr_data );
	}
	else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
	{
		UnimplementedAddressing_Mode( instr_data, "AND" );
	}
	else
	{
		IllegalAddressing_Mode( instr_data, "AND" );
	}
}

void OR_Instr(instruc instr_data)
{
	if( instr_data.am == directam )
	{
		AC = AC | memory[instr_data.addr];
		trace( "OR", instr_data );
	}
	else if( instr_data.am == immedam )
	{
		AC = AC | instr_data.addr;
		trace( "OR", instr_data );
	}
	else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
	{
		UnimplementedAddressing_Mode( instr_data, "OR" );
	}
	else
	{
		IllegalAddressing_Mode( instr_data, "OR" );
	}
}

void XOR_Instr(instruc instr_data)
{
	if( instr_data.am == directam )
	{
		AC = AC ^ memory[instr_data.addr];
		trace( "XOR", instr_data );
	}
	else if( instr_data.am == immedam )
	{
		AC = AC ^ instr_data.addr;
		trace( "XOR", instr_data );
	}
	else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
	{
		UnimplementedAddressing_Mode( instr_data, "XOR" );
	}
	else
	{
		IllegalAddressing_Mode( instr_data, "XOR" );
	}
}

void J_Instr(instruc instr_data)
{ //Most of the jump logic is impemented in main.
//So these just have to print a trace.

	if( instr_data.am == directam )
	{
		trace( instr_data, "J");
	}
	else if( instr_data.am == immedam )
	{
		IllegalAddressing_Mode( instr_data, "J")
	}
	else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
	{
		UnimplementedAddressing_Mode( instr_data, "J" );
	}
	else
	{
		IllegalAddressing_Mode( instr_data, "J" );
	}
	
}

void JZ_Instr(instruc instr_data)
{
 //Most of the jump logic is impemented in main.
 //So these just have to print a trace.
 
	if( instr_data.am == directam )
	{
		trace( instr_data, "JZ");
	}
	else if( instr_data.am == immedam )
	{
		IllegalAddressing_Mode( instr_data, "JZ")
	}
	else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
	{
		UnimplementedAddressing_Mode( instr_data, "JZ" );
	}
	else
	{
		IllegalAddressing_Mode( instr_data, "JZ" );
	}
}

void JN_Instr(instruc instr_data)
{
 //Most of the jump logic is impemented in main.
 //So these just have to print a trace.
 
	if( instr_data.am == directam )
	{
		trace( instr_data, "JN");
	}
	else if( instr_data.am == immedam )
	{
		IllegalAddressing_Mode( instr_data, "JN")
	}
	else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
	{
		UnimplementedAddressing_Mode( instr_data, "JN" );
	}
	else
	{
		IllegalAddressing_Mode( instr_data, "JN" );
	}
}

void JP_Instr(instruc instr_data)
{
 //Most of the jump logic is impemented in main.
 //So these just have to print a trace.
 
	if( instr_data.am == directam )
	{
		trace( instr_data, "JP");
	}
	else if( instr_data.am == immedam )
	{
		IllegalAddressing_Mode( instr_data, "JP")
	}
	else if ( instr_data.am >= indexam && instr_data.am <= indexindirectam )
	{
		UnimplementedAddressing_Mode( instr_data, "JP" );
	}
	else
	{
		IllegalAddressing_Mode( instr_data, "JP" );
	}
}

void UnimplementedAddressing_Mode(instruc instr_data, string mnemonic)
{
	trace( mnemonic, instr_data );
	cout << "Machine Halted - unimplemented addressing mode";
	exit( 3 );
}

void IllegalAddressing_Mode(instruc instr_data, string mnemonic)
{
	trace( mnemonic, instr_data );
	cout << "Machine Halted - illegal addressing mode";
	exit( 4 );
}
