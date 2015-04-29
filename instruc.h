#ifndef INSTRUC_H
#define INSTRUC_H
#include <iostream> //Printing trace
#include <string> //For passing strings to trace()
#include <iomanip> //For std::hex, setw()
#include <cstdlib> //for exit();

using namespace std;

struct instruc //Struct to hold the parsed instruction
{
	int addr;
	int op;
	int am;
};


//The 4096-word memory array from Globals.cpp
extern int memory[0xFFF]; //Init to zero

//Values for addressing mode constants.
const int directam = 0;
const int immedam = 1;
const int indexam = 2;
const int indirectam = 4;
const int indexindirectam = 6;

//Get these from Globals.cpp
extern int IC, AC, X0, X1, X2, X3;

void trace(string mnemonic, instruc instruction);

//Author: Grant Hill
//Parses the instuction from memory into address, opcode, and mode fields
instruc parseInstruc(int instruction);


void switchFunction( instruc instr_data ); //Prototype for switch

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

//Declare processor instructions
void UnimplementedAddressing_Mode(instruc instr_data, string mnemonic);
void IllegalAddressing_Mode(instruc instr_data, string mnemonic);
void HALT_Instr(instruc instr_data);
void NOP_Instr(instruc instr_data);
void LD_Instr(instruc instr_data);
void ST_Instr(instruc instr_data);
void EM_Instr(instruc instr_data);
void ADD_Instr(instruc instr_data);
void SUB_Instr(instruc instr_data);
void CLR_Instr(instruc instr_data);
void COM_Instr(instruc instr_data);
void AND_Instr(instruc instr_data);
void OR_Instr(instruc instr_data);
void XOR_Instr(instruc instr_data);
void J_Instr(instruc instr_data);
void JZ_Instr(instruc instr_data);
void JN_Instr(instruc instr_data);
void JP_Instr(instruc instr_data);
void UnimplementedAddressing_Mode(instruc instr_data, string mnemonic);
void IllegalAddressing_Mode(instruc instr_data, string mnemonic);

#endif
