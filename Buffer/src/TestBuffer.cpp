#include "../includes/Buffer.h"
#include <iostream>
using namespace std;

void println(char const &ch) {
	cout << (int)ch << "\t : " << ch << endl;
}
void printToEnd(Buffer& buffer) {
	char c;
	while(( c = buffer.getChar() )!= '\0') {
			println(c);
		}
}

int main(int argc, char **argv) {
	if (argc != 2)
		return EXIT_FAILURE;

	Buffer buffer(argv[1], 4);

	printToEnd(buffer);
	cout << "---------------------------------" << endl;
	for(int i = 0; i < 6; i++) {
		println(buffer.ungetChar());
	}
	cout << "---------------------------------" << endl;
	printToEnd(buffer);

	return EXIT_SUCCESS;
}
