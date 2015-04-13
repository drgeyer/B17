#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	ifstream obj;
	int startAddress, toRead;


	obj.open(argv[1]);

	if(!obj)
	{
		cout << "Could not open " << argv[1] << endl;
		return -1;
	}

	obj >> hex >> startAddress >> toRead;



	return 0;
}

