#include "stdafx.h"

int main(int argc, char* argv[])
{
	int x = 666;
	/*std::ofstream fOut("bombom.txt");
	fOut << x << std::endl;*/

	/*std::ofstream fOut("bombom.bin", std::ios_base::binary);
	fOut.write((char*)&x, sizeof(int));*/

	int y;
	std::ifstream fIn("bombom.bin", std::ios_base::binary);
	fIn.read((char*)&y, sizeof(int));
	uint32_t tmp = 1 ^ 2;
	std::cout << tmp << std::endl;

	return 0;
}