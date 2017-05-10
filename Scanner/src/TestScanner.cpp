#include "../includes/Scanner.h"
#include <iostream>
#include <iomanip>
using namespace std;

#define EVER ;;

void printToken(Token* t, ostream &str) {
	str << "Token " << left << setw(20) << t->getTypeAsString();
	str << " Line: " << t->_line;
	str << " Column: " << t->_column;

	switch (t->_type) {
	case TOKEN_INTEGER:
		str << " Value: " << t->_integerValue;
		break;
	case TOKEN_IDENTIFIER:
		str << " Lexem: " << t->_info->getName();
		break;
	case TOKEN_UNKNOWN:
		str << " " << t->getUnknownReason();
		break;
	default:
		break;
	}

	str << endl;
}

int main(int argc, char *argv[]) {
	if (argc != 3)
		return EXIT_FAILURE;

#ifndef DEBUG
	//disable debug messages for release.
	clog.setstate(std::ios_base::failbit);
#endif

	Symboltable st;
	Scanner scanner(argv[1], st);
	ofstream out (argv[2]);

	for(EVER) {
		Token *t = scanner.nextToken();

		printToken(t, t->_type == TOKEN_UNKNOWN ? cerr : out);

		if (t->_type == TOKEN_EOF)
			break;

		delete t;
	}

	out.close();
	return EXIT_SUCCESS;
}
