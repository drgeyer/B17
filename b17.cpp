#include <iostream>
#include <fstream>

using namespace std;

//The 4096-word memory array
int memory[0xFFF];

//Author: Grant Hill
//Parses object file and places values in memory
int main(int argc, char *argv[])
{
	ifstream obj;
	int startAddress, toRead, nextVal;

	obj.open(argv[1]);

	if(!obj)
	{
		cout << "Could not open " << argv[1] << endl;
		return -1;
	}

	obj >> hex >> startAddress >> toRead;

	for(int i = 0; i < toRead; i++)
		{
			obj >> nextVal;
			memory[startAddress + i] = nextVal;
		}

	return 0;
}

