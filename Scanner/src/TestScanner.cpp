#include "../includes/Scanner.h"

#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char **argv) {

	Scanner* scanner;

	char const* filename = "input.txt";
	char const* logfile = "output.txt";
	ofstream out(logfile);

	scanner = new Scanner(filename, 1024, 1024, false);

	Token* nextToken;

	do {
		nextToken = scanner->nextToken();

		out << "TType: " << left << setw(20) << nextToken->getTypeAsString()
			<< " Line: " << nextToken->_line
			<< "\t Col: " << nextToken->_column << endl;

		cout << "TType: " << left << setw(20) << nextToken->getTypeAsString()
			<< " Line: " << nextToken->_line
			<< "\t Col: " << nextToken->_column << endl;

	} while (nextToken->_type != TOKEN_EOF);

	return 1;
}
