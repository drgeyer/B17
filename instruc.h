#ifndef INSTRUC_H
#define INSTRUC_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct instruc //Struct to hold the parsed instruction
{
	int addr;
	int op;
	int am;
};

#edif /* INSTRUC_H */