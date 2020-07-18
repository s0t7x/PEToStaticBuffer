// PE to static buffer
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

int main(int argC, char * argV[]) {
	if (argC < 2) {
		std::cout << "Usage: PEToStaticBuffer [path-to-portable-executeable]" << std::endl;
		return 1;
	}

	std::ifstream pEFile;
	pEFile.open(argV[1]);

	if (pEFile) {
		pEFile.seekg(0, pEFile.end);
		int pEBytes = (int)pEFile.tellg();
		pEFile.seekg(0, pEFile.beg);

		char * pEBuffer = new char[pEBytes];
		pEFile.read(pEBuffer, pEBytes);

		std::time_t timeStamp = std::time(NULL);

#pragma warning (disable: 4996)
		std::cout << "//PEStaticBuffer of \"" << argV[1] << "\"\n//Generated on " << std::asctime(std::localtime(&timeStamp)) << std::endl;
		std::cout << "#pragma once" << std::endl << std::endl;

		std::cout << "static char PE_BUFFER[] = {" << std::endl;

		for (int i = 0; i < (pEBytes - 1); i++) {
			std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << std::right << std::uppercase << (int)(uint8_t)pEBuffer[i] << ", ";
			if (i % 16 == 15)
				std::cout << std::endl;
		}

		std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << std::right << (int)(uint8_t)pEBuffer[pEBytes - 1] << std::endl;


		std::cout << "};" << std::endl;

		return 0;
	}
}