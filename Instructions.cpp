#include "instruc.h"

///////////////////////////////////////////////////////////////////////////////
//		EXTERNAL GLOBAL VARIABLES - REGISTERS
///////////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////
//	FUNCTION PROTOTYPES
///////////////////////////////////////////////////////////////////////////////
void UnimplementedAddressing_Mode(instruc instr_data, string mnemonic);
void IllegalAddressing_Mode(instruc instr_data, string mnemonic);

int not_used = 0;

/**************************************************************************************************
* Function:	
*
* Authors:	
*
* Description:	
*
* Parameters:	
*
* Returns:	
**************************************************************************************************/
void HALT_Instr(instruc instr_data)
{
	trace( "HALT" );
	cout << "Machine Halted - HALT instruction executed" << endl;
	exit(0);
}

/**************************************************************************************************
* Function:	
*
* Authors:	
*
* Description:	
*
* Parameters:	
*
* Returns:	
**************************************************************************************************/
void NOP_Instr(instruc instr_data)
{
	trace( "NOP" );
	return;
}

/**************************************************************************************************
* Function:	
*
* Authors:	
*
* Description:	
*
* Parameters:	
*
* Returns:	
**************************************************************************************************/
void LD_Instr(instruc instr_data)
{
	//Do the operation
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
	
}

/**************************************************************************************************
* Function:	
*
* Authors:	
*
* Description:	
*
* Parameters:	
*
* Returns:	
**************************************************************************************************/
void ST_Instr(instruc instr_data)
{
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
}

/**************************************************************************************************
* Function:	
*
* Authors:	
*
* Description:	
*
* Parameters:	
*
* Returns:	
**************************************************************************************************/
void EM_Instr(instruc instr_data)
{
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
}

/**************************************************************************************************
* Function:	
*
* Authors:	
*
* Description:	
*
* Parameters:	
*
* Returns:	
**************************************************************************************************/
void ADD_Instr(instruc instr_data)
{
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
}

/**************************************************************************************************
* Function:	
*
* Authors:	
*
* Description:	
*
* Parameters:	
*
* Returns:	
**************************************************************************************************/
void SUB_Instr(instruc instr_data)
{
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
}

/**************************************************************************************************
* Function:	
*
* Authors:	
*
* Description:	
*
* Parameters:	
*
* Returns:	
**************************************************************************************************/
void CLR_Instr(instruc instr_data)
{ //No addressing mode here, so it's ignored.
//No address logic needed.
	AC = 0;

	trace("CLR");
}

/**************************************************************************************************
* Function:	
*
* Authors:	
*
* Description:	
*
* Parameters:	
*
* Returns:	
**************************************************************************************************/
void COM_Instr(instruc instr_data)
{
	AC = ~AC;

	trace("COM");
}

/**************************************************************************************************
* Function:	
*
* Authors:	
*
* Description:	
*
* Parameters:	
*
* Returns:	
**************************************************************************************************/
void AND_Instr(instruc instr_data)
{
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
}

/**************************************************************************************************
* Function:	
*
* Authors:	
*
* Description:	
*
* Parameters:	
*
* Returns:	
**************************************************************************************************/
void OR_Instr(instruc instr_data)
{
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
}

/**************************************************************************************************
* Function:	
*
* Authors:	
*
* Description:	
*
* Parameters:	
*
* Returns:	
**************************************************************************************************/
void XOR_Instr(instruc instr_data)
{
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
}

/**************************************************************************************************
* Function:	
*
* Authors:	
*
* Description:	
*
* Parameters:	
*
* Returns:	
**************************************************************************************************/
void J_Instr(instruc instr_data)
{ //Most of the jump logic is impemented in main.
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
	
}

/**************************************************************************************************
* Function:	
*
* Authors:	
*
* Description:	
*
* Parameters:	
*
* Returns:	
**************************************************************************************************/
void JZ_Instr(instruc instr_data)
{
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
}

/**************************************************************************************************
* Function:	
*
* Authors:	
*
* Description:	
*
* Parameters:	
*
* Returns:	
**************************************************************************************************/
void JN_Instr(instruc instr_data)
{
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
}

/**************************************************************************************************
* Function:	
*
* Authors:	
*
* Description:	
*
* Parameters:	
*
* Returns:	
**************************************************************************************************/
void JP_Instr(instruc instr_data)
{
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
}

/**************************************************************************************************
* Function:	
*
* Authors:	
*
* Description:	
*
* Parameters:	
*
* Returns:	
**************************************************************************************************/
void UnimplementedAddressing_Mode(instruc instr_data, string mnemonic)
{
	trace( mnemonic );
	cout << "Machine Halted - unimplemented addressing mode";
	exit( 3 );
}

/**************************************************************************************************
* Function:	
*
* Authors:	
*
* Description:	
*
* Parameters:	
*
* Returns:	
**************************************************************************************************/
void IllegalAddressing_Mode(instruc instr_data, string mnemonic)
{
	trace( mnemonic );
	cout << "Machine Halted - illegal addressing mode";
	exit( 4 );
}
