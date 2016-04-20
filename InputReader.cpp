#define _GLIBCXX_USE_CXX11_ABI 0
#include "InputReader.h"

InputReader::InputReader() {
	string line;
	ifstream myfile("grammar.txt");
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			cout << line << '\n';
		}
		myfile.close();
	}
}
